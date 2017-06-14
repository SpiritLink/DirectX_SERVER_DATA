#include "stdafx.h"
#include "Server_DATA.h"

HANDLE hMutex_DATA;
HANDLE hMutex_DATA2;
unsigned int _stdcall PROCESS_RECV(void * arg);

unsigned int _stdcall PROCESS_SEND(void* arg);
unsigned int _stdcall PROCESS_RECV2(void* arg);
unsigned int _stdcall Recv_From_Client(void* arg);
unsigned int _stdcall Send_From_Server(void* arg);
CRITICAL_SECTION CS_DATA;
CRITICAL_SECTION CS_DATA2;

Server_DATA::Server_DATA()
{
}


Server_DATA::~Server_DATA()
{
}

void Server_DATA::Setup()
{

	InitializeCriticalSection(&CS_DATA2);
	EnterCriticalSection(&CS_DATA2);
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		cout << "Server_DATA WSAStartup() Error!" << endl;

	hMutex_DATA2 = CreateMutex(NULL, FALSE, NULL);
	hServSock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;	// << : IPV4 할당
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = PORT_DATA_RECV;
	bool bValid = 1;
	setsockopt(hServSock, SOL_SOCKET, SO_REUSEADDR, (const char *)&bValid, sizeof(bValid));

	if (bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
		cout << "Server_DATA bind() Error" << endl;
	if (listen(hServSock, CLIENT_NUM) == SOCKET_ERROR)
		cout << "Server_DATA listen() error" << endl;
	LeaveCriticalSection(&CS_DATA2);
	while (true)
	{
		/* 클라이언트가 연결을 시도했을때 처리하는 부분 */
		clntAdrSz = sizeof(clntAdr);
		hClntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &clntAdrSz);
		ST_SOCKET_ADDR Recv;
		Recv.stSocket = hClntSock;
		Recv.stAddr = clntAdr;
		if (hClntSock > 0)
		{
			if (g_pTime->GetShowAllLog()) cout << "accept IP :" << inet_ntoa(clntAdr.sin_addr) << endl;
			hThread_RECV = (HANDLE)_beginthreadex(NULL, 0, Recv_From_Client, (void*)&Recv, 0, NULL);
			g_nThreadCount++;
			if (g_pTime->GetShowThread()) cout << "Add Thread Count : " << g_nThreadCount << endl;
		}
		if (g_pTime->GetQuit()) break;
	}

}

void Server_DATA::Update()
{
	// << : 10초에 한번 모든 데이터를 파일로 저장합니다.
	if (g_pTime->GetSaveTimer() + (ONE_SECOND * 10) < clock())
	{
		WaitForSingleObject(g_hMutex_DATA, INFINITE);
		g_pTime->SetSaveTimer(clock());
		g_pDataManager->SaveAllData();
		cout << g_pTime->GetLocalTime_String() << " : Save Data" << endl;
		ReleaseMutex(g_hMutex_DATA);
	}

	if (GetAsyncKeyState(VK_NUMPAD3) & 0x0001)
	{
		g_pDataManager->Update();
	}

	if (GetAsyncKeyState(VK_NUMPAD7) & 0x0001)
	{
		cout << "현재 스레드 개수 : " << g_nThreadCount << endl;
	}
	
	if (GetAsyncKeyState(VK_NUMPAD8) & 0x0001)
	{
		if (g_pTime->GetShowAllLog())
			g_pTime->SetShowAllLog(false);
		else if (!g_pTime->GetShowAllLog())
			g_pTime->SetShowAllLog(true);
	}
	if (GetAsyncKeyState(VK_NUMPAD9) & 0x0001)
	{
		g_pTime->SetQuit(true);
	}
}

void Server_DATA::Destroy()
{
	closesocket(hServSock);
	WSACleanup();
}

unsigned int _stdcall PROCESS_RECV(void * arg)
{
	ST_SOCKET_ADDR RecvSocket = *(ST_SOCKET_ADDR*)arg;	// << : 소켓과 IP 주소
	ST_PLAYER_POSITION RecvData;			/// << : 데이터 수신 버퍼
	SOCKET hClntSock = RecvSocket.stSocket;	/// << : SOCKET 정보 받아옴
	int strLen = 0;

	strLen = recv(hClntSock, (char*)&RecvData, sizeof(ST_PLAYER_POSITION), 0);

	/* 정상적인 연결일때 */
	if ( strLen != 0 && strLen != -1)
	{
		WaitForSingleObject(hMutex_DATA, INFINITE);	// << : Wait Mutex
		g_pDataManager->ReceiveData(RecvData,RecvSocket.stAddr);
		if (RecvData.nPlayerIndex & IN_PLAYER1 && g_pTime->GetShowAllLog()) cout << "플레이어 1 ";
		if (RecvData.nPlayerIndex & IN_PLAYER2 && g_pTime->GetShowAllLog()) cout << "플레이어 2 ";
		if (g_pTime->GetShowAllLog()) cout << RecvData.fX << " " << RecvData.fY << " " << RecvData.fZ << " " << RecvData.fAngle << " 애니메이션 : " << RecvData.eAnimState << endl;
		ReleaseMutex(hMutex_DATA);					// << : Release Mutex
	}
	/* 비정상적인 연결일때 */
	else
	{
		closesocket(hClntSock);
		g_nThreadCount--;
		if(g_pTime->GetShowThread()) cout << "Sub Thread Count : " << g_nThreadCount << endl;
		return 0;
	}

	ST_PLAYER_POSITION stPosition;
	stPosition = g_pDataManager->GetPlayerData(string(RecvData.szRoomName), RecvData.nPlayerIndex);
	sprintf_s(RecvData.szRoomName, "%s", "FROM_SERVER", 11);
	send(hClntSock, (char*)&stPosition, sizeof(ST_PLAYER_POSITION), 0);	// << : send Function
	g_nThreadCount--;
	if(g_pTime->GetShowThread()) cout << "Sub Thread Count : " << g_nThreadCount << endl;
	return 0;
}

unsigned int _stdcall PROCESS_SEND(void* arg)
{
	return 0;
}
unsigned int _stdcall PROCESS_RECV2(void* arg)
{
	ST_SOCKET_ADDR Recv = *(ST_SOCKET_ADDR*)arg;
	SOCKET ClntSock = Recv.stSocket;
	SOCKADDR_IN RecvAdr;
	int strLen, i;

	while ((strLen = recv(ClntSock, (char*)&RecvAdr, sizeof(SOCKADDR_IN), 0)) != 0)
	{
		if (strLen == -1) break;
		cout << inet_ntoa(RecvAdr.sin_addr) << endl;
		continue;
	}

	closesocket(ClntSock);
	return 0;
}
unsigned int _stdcall Recv_From_Client(void* arg)
{
	ST_SOCKET_ADDR RecvSocket = *(ST_SOCKET_ADDR*)arg;
	SOCKET ClntSock = RecvSocket.stSocket;
	char szBuffer[BUF_SIZE * 10] = { 0, };
	int strLen1,strLen2, i;

	while ((strLen1 = recv(ClntSock, szBuffer, sizeof(ST_FLAG), 0)) != 0)
	{
		if (strLen1 == -1) break;

		ST_FLAG stFlag = *(ST_FLAG*)szBuffer;
		switch (stFlag.eFlag)
		{
		case FLAG_POSITION:
		{
			recv(ClntSock, szBuffer, sizeof(ST_PLAYER_POSITION), 0);
			ST_PLAYER_POSITION RecvPosition = *(ST_PLAYER_POSITION*)szBuffer;
			WaitForSingleObject(g_hMutex_DATA, INFINITE);
			g_pDataManager->ReceiveData(RecvPosition);

			cout << "FLAG_POSITION 좌표 수신" << endl;
			ST_PLAYER_POSITION SendPosition;
			int nIndex;
			SendPosition = g_pDataManager->GetPlayerData(string(stFlag.szRoomName), RecvPosition.nPlayerIndex);
			ReleaseMutex(g_hMutex_DATA);
			send(ClntSock, (char*)&SendPosition, sizeof(ST_PLAYER_POSITION), 0);
			cout << "FLAG_POSITION 좌표 전송" << endl;
		}
			break;
		}
		continue;
	}

	closesocket(ClntSock);
	return 0;
}
unsigned int _stdcall Send_From_Server(void* arg)
{
	return 0;
}


