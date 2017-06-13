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

void Server_DATA::Setup_Prev()
{
	InitializeCriticalSection(&CS_DATA);
	EnterCriticalSection(&CS_DATA);
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		cout << "Server_DATA WSAStartup() Error!" << endl;

	hMutex_DATA = CreateMutex(NULL, FALSE, NULL);
	hServSock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;	// << : IPV4 �Ҵ�
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = PORT_DATA;

	if (bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
		cout << "Server_DATA bind() Error" << endl;
	if (listen(hServSock, CLIENT_NUM) == SOCKET_ERROR)
		cout << "Server_DATA listen() error" << endl;
	LeaveCriticalSection(&CS_DATA);
	while (true)
	{
		/* Ŭ���̾�Ʈ�� ������ �õ������� ó���ϴ� �κ� */
		clntAdrSz = sizeof(clntAdr);
		hClntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &clntAdrSz);
		ST_SOCKET_ADDR Recv;
		Recv.stSocket = hClntSock;
		Recv.stAddr = clntAdr;
		//cout << inet_ntoa(Recv.stAddr.sin_addr) << endl;
		if (hClntSock > 0)
		{
			if(g_pTime->GetShowAllLog()) cout << "accept IP :" << inet_ntoa(clntAdr.sin_addr) << endl;
			hThread = (HANDLE)_beginthreadex(NULL, 0, PROCESS_RECV, (void*)&Recv, 0, NULL);
			g_nThreadCount++;
			if(g_pTime->GetShowThread()) cout << "Add Thread Count : " << g_nThreadCount << endl;
		}
		if (g_pTime->GetQuit()) break;
	}
}

void Server_DATA::Setup_Current()
{
	wsaData2;
	hServSock2, hClntSock2;
	servAdr2, clntAdr2;

	InitializeCriticalSection(&CS_DATA2);
	EnterCriticalSection(&CS_DATA2);
	if (WSAStartup(MAKEWORD(2, 2), &wsaData2) != 0)
		cout << "Server_DATA WSAStartup() Error!" << endl;

	hMutex_DATA2 = CreateMutex(NULL, FALSE, NULL);
	hServSock2 = socket(PF_INET, SOCK_STREAM, 0);

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr2.sin_family = AF_INET;	// << : IPV4 �Ҵ�
	servAdr2.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr2.sin_port = PORT_CLIENT;

	if (bind(hServSock2, (SOCKADDR*)&servAdr2, sizeof(servAdr2)) == SOCKET_ERROR)
		cout << "Server_DATA bind() Error" << endl;
	if (listen(hServSock2, CLIENT_NUM) == SOCKET_ERROR)
		cout << "Server_DATA listen() error" << endl;
	LeaveCriticalSection(&CS_DATA2);
	while (true)
	{
		/* Ŭ���̾�Ʈ�� ������ �õ������� ó���ϴ� �κ� */
		clntAdrSz2 = sizeof(clntAdr);
		hClntSock2 = accept(hServSock2, (SOCKADDR*)&clntAdr2, &clntAdrSz2);
		ST_SOCKET_ADDR Recv;
		Recv.stSocket = hClntSock2;
		Recv.stAddr = clntAdr2;
		if (hClntSock2 > 0)
		{
			hThread_RECV = (HANDLE)_beginthreadex(NULL, 0, Recv_From_Client, (void*)&Recv, 0, NULL);
			g_nThreadCount++;
		}
		if (g_pTime->GetQuit()) break;
	}

}

void Server_DATA::Update()
{
	// << : 10�ʿ� �ѹ� ��� �����͸� ���Ϸ� �����մϴ�.
	if (g_pTime->GetSaveTimer() + (ONE_SECOND * 10) < clock())
	{
		g_pTime->SetSaveTimer(clock());
		g_pDataManager->SaveAllData();
		cout << g_pTime->GetLocalTime_String() << " : Save Data" << endl;
	}

	if (GetAsyncKeyState(VK_NUMPAD7) & 0x0001)
	{
		cout << "���� ������ ���� : " << g_nThreadCount << endl;
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
	ST_SOCKET_ADDR RecvSocket = *(ST_SOCKET_ADDR*)arg;	// << : ���ϰ� IP �ּ�
	ST_PLAYER_POSITION RecvData;			/// << : ������ ���� ����
	SOCKET hClntSock = RecvSocket.stSocket;	/// << : SOCKET ���� �޾ƿ�
	int strLen = 0;

	strLen = recv(hClntSock, (char*)&RecvData, sizeof(ST_PLAYER_POSITION), 0);

	/* �������� �����϶� */
	if ( strLen != 0 && strLen != -1)
	{
		WaitForSingleObject(hMutex_DATA, INFINITE);	// << : Wait Mutex
		g_pDataManager->ReceiveData(RecvData,RecvSocket.stAddr);
		if (RecvData.nPlayerIndex & IN_PLAYER1 && g_pTime->GetShowAllLog()) cout << "�÷��̾� 1 ";
		if (RecvData.nPlayerIndex & IN_PLAYER2 && g_pTime->GetShowAllLog()) cout << "�÷��̾� 2 ";
		if (g_pTime->GetShowAllLog()) cout << RecvData.fX << " " << RecvData.fY << " " << RecvData.fZ << " " << RecvData.fAngle << " �ִϸ��̼� : " << RecvData.eAnimState << endl;
		ReleaseMutex(hMutex_DATA);					// << : Release Mutex
	}
	/* ���������� �����϶� */
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
	ST_SOCKET_ADDR Recv = *(ST_SOCKET_ADDR*)arg;
	SOCKET ClntSock = Recv.stSocket;
	char szBuffer[BUF_SIZE * 10] = { 0, };
	int strLen1,strLen2, i;

	while ((strLen1 = recv(ClntSock, szBuffer, sizeof(int), 0)) != 0)
	{
		if (strLen1 == -1) break;

		int nFlag = *(char*)szBuffer;

		switch (nFlag)
		{
		case FLAG_POSITION:
		{
			recv(ClntSock, szBuffer, sizeof(ST_PLAYER_POSITION), 0);
			ST_PLAYER_POSITION data = *(ST_PLAYER_POSITION*)szBuffer;
			cout << data.fX << endl;
			cout << data.fY << endl;
			cout << data.fZ << endl;
			cout << "���� ���� �Ϸ�" << endl;
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


