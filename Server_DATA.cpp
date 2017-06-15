#include "stdafx.h"
#include "Server_DATA.h"

CRITICAL_SECTION CS_SERVER;

// << : 스레드 함수
unsigned int _stdcall RECV_REQUEST(void* arg);	// << : 수신
unsigned int _stdcall SEND_REQUEST(void* arg);	// << : 전송
// << : 일반 함수
void ProcessPosition(void* arg, string RoomName);

void RecvPosition();

void SendNetworkID(SOCKET* pSocket);
void SendRoomName(SOCKET* pSocket, ST_FLAG* flag);
void SendAllData(SOCKET* pSocket, ST_FLAG* flag);
void SendPosition(SOCKET* pSocket, ST_FLAG* flag);

Server_DATA::Server_DATA()
{
}


Server_DATA::~Server_DATA()
{
}

void Server_DATA::Setup_RECV()
{
	InitializeCriticalSection(&CS_SERVER);
	EnterCriticalSection(&CS_SERVER);
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		cout << "Server_DATA WSAStartup() Error!" << endl;
	bool bValid = 1;

	/* RECV Sock 초기화 */
	hServSock_RECV = socket(PF_INET, SOCK_STREAM, 0);

	memset(&servAddr_RECV, 0, sizeof(servAddr_RECV));
	servAddr_RECV.sin_family = AF_INET;	// << : IPV4 할당
	servAddr_RECV.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr_RECV.sin_port = PORT_DATA_IN;

	setsockopt(hServSock_RECV, SOL_SOCKET, SO_REUSEADDR, (const char *)&bValid, sizeof(bValid));

	if (bind(hServSock_RECV, (SOCKADDR*)&servAddr_RECV, sizeof(servAddr_RECV)) == SOCKET_ERROR)
		cout << "RECV bind() Error" << endl;
	if (listen(hServSock_RECV, CLIENT_NUM) == SOCKET_ERROR)
		cout << "RECV listen() error" << endl;

	LeaveCriticalSection(&CS_SERVER);

	while (true)
	{
		/* 클라이언트가 연결을 시도했을때 처리하는 부분 */
		clntAdrSz_RECV = sizeof(clntAdr_RECV);
		hClntSock_RECV = accept(hServSock_RECV, (SOCKADDR*)&clntAdr_RECV, &clntAdrSz_RECV);
		ST_SOCKET_ADDR RecvSock;
		RecvSock.stSocket = hClntSock_RECV;
		RecvSock.stAddr = clntAdr_RECV;
		if (hClntSock_RECV > 0)
		{
			if (g_pTime->GetShowAllLog()) cout << "accept IP :" << inet_ntoa(clntAdr_RECV.sin_addr) << endl;
			hTestRecv = (HANDLE)_beginthreadex(NULL, 0, RECV_REQUEST, (void*)&RecvSock, 0, NULL);
			if (g_pTime->GetShowThread()) cout << "Add Thread Count : " << g_nThreadCount << endl;
			g_nThreadCount++;
		}
		if (g_pTime->GetQuit()) break;
	}

}

void Server_DATA::Setup_SEND()
{
	InitializeCriticalSection(&CS_SERVER);
	EnterCriticalSection(&CS_SERVER);

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		cout << "Server_DATA WSAStartup() Error!" << endl;
	bool bValid = 1;

	/* SEND Sock 초기화 */
	hServSock_SEND = socket(PF_INET, SOCK_STREAM, 0);

	memset(&servAddr_SEND, 0, sizeof(servAddr_SEND));
	servAddr_SEND.sin_family = AF_INET;
	servAddr_SEND.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr_SEND.sin_port = PORT_DATA_OUT;

	setsockopt(hServSock_SEND, SOL_SOCKET, SO_REUSEADDR, (const char *)&bValid, sizeof(bValid));

	if (bind(hServSock_SEND, (SOCKADDR*)&servAddr_SEND, sizeof(servAddr_SEND)) == SOCKET_ERROR)
		cout << "SEND bind() Error" << endl;
	if (listen(hServSock_SEND, CLIENT_NUM) == SOCKET_ERROR)
		cout << "SEND listen() error" << endl;

	while (true)
	{
		/* 클라이언트가 연결을 시도했을때 처리하는 부분 */
		clntAdrSz_SEND = sizeof(clntAdr_SEND);
		hClntSock_SEND = accept(hServSock_SEND, (SOCKADDR*)&clntAdr_SEND, &clntAdrSz_SEND);
		ST_SOCKET_ADDR SendSock;
		SendSock.stSocket = hClntSock_SEND;
		SendSock.stAddr = clntAdr_SEND;
		if (hClntSock_SEND > 0)
		{
			if (g_pTime->GetShowAllLog()) cout << "accept IP :" << inet_ntoa(clntAdr_SEND.sin_addr) << endl;
			hTestSend = (HANDLE)_beginthreadex(NULL, 0, SEND_REQUEST, (void*)&SendSock, 0, NULL);
			g_nThreadCount++;
			if (g_pTime->GetShowThread()) cout << "Add Thread Count : " << g_nThreadCount << endl;
		}
		if (g_pTime->GetQuit()) break;
	}

	LeaveCriticalSection(&CS_SERVER);
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
	closesocket(hServSock_RECV);
	closesocket(hServSock_SEND);
	WSACleanup();
}

unsigned int _stdcall RECV_REQUEST(void* arg)
{
	ST_SOCKET_ADDR RecvSocket = *(ST_SOCKET_ADDR*)arg;
	SOCKET ClntSock = RecvSocket.stSocket;
	char szBuffer[BUF_SIZE * 10] = { 0, };
	int strLen;

	while ((strLen = recv(ClntSock, szBuffer, sizeof(ST_FLAG), 0)) != 0)
	{
		if (strLen == -1) break;

		ST_FLAG stFlag = *(ST_FLAG*)szBuffer;
		switch (stFlag.eFlag)
		{
		case FLAG_NONE:	// << : 접속 확인용 ?
			break;
		case FLAG_NETWORK_ID:
			SendNetworkID(&ClntSock);
			break;
		case FLAG_ROOM_NAME:
			SendRoomName(&ClntSock,&stFlag);
			break;
		case FLAG_ALL_DATA:
			SendAllData(&ClntSock, &stFlag);
			break;
		case FLAG_IP:
			break;
		case FLAG_POSITION:
			//ProcessPosition(&RecvSocket, string(stFlag.szRoomName));
			SendPosition(&ClntSock, &stFlag);
			break;
		case FLAG_OBJECT_DATA:
			break;
		}
		continue;
	}

	closesocket(ClntSock);
	return 0;
}

unsigned int _stdcall SEND_REQUEST(void* arg)
{
	ST_SOCKET_ADDR RecvSocket = *(ST_SOCKET_ADDR*)arg;
	SOCKET ClntSock = RecvSocket.stSocket;
	char szBuffer[BUF_SIZE * 10] = { 0, };
	int strLen1, strLen2, i;
	clock_t prevTime = clock();
	ST_FLAG stFlag;

	while (true)
	{
		// << : 여기서 컨테이너를 확인, 얻어야할 정보가 있다면 얻어오는 식으로
		if (prevTime + (ONE_SECOND * 2) > clock()) continue;
		prevTime = clock();

		stFlag.eFlag = FLAG_NONE;
		stFlag.nPlayerIndex = 1000;
		sprintf_s(stFlag.szRoomName, "SERVER", 6);

		send(ClntSock, (char*)&stFlag, sizeof(ST_FLAG), 0);	// << : 플래그 전송

		switch (stFlag.eFlag)
		{
		case FLAG_NONE:
			break;
		case FLAG_IP:
			break;
		case FLAG_POSITION:
			break;
		case FLAG_OBJECT_DATA:
			break;
		}
		
		// << : 만약 네트워크 아이디가 -1이라면 수신하고 적용은 하지 않는다.
	}

	closesocket(ClntSock);
	return 0;
}

void ProcessPosition(void* arg, string RoomName)
{
	SOCKET ClntSock = *(SOCKET*)arg;
	char szBuffer[1000] = { 0, };
	recv(ClntSock, szBuffer, sizeof(ST_PLAYER_POSITION), 0);
	ST_PLAYER_POSITION RecvPosition = *(ST_PLAYER_POSITION*)szBuffer;
	WaitForSingleObject(g_hMutex_DATA, INFINITE);
	g_pDataManager->ReceiveData(RecvPosition);

	cout << "FLAG_POSITION 좌표 수신" << endl;
	ST_PLAYER_POSITION SendPosition;
	int nIndex;
	SendPosition = g_pDataManager->GetPlayerData(RoomName, RecvPosition.nPlayerIndex);
	ReleaseMutex(g_hMutex_DATA);
	send(ClntSock, (char*)&SendPosition, sizeof(ST_PLAYER_POSITION), 0);
	cout << "FLAG_POSITION 좌표 전송" << endl;

}

void RecvPosition()
{

}

void SendNetworkID(SOCKET* pSocket)
{
	int ID = g_nNetworkID++;
	send(*pSocket, (char*)&ID, sizeof(int), 0);
}

void SendRoomName(SOCKET* pSocket,ST_FLAG* flag)
{
	int IsOk = 0;
	string RoomName = flag->szRoomName;
	if (g_pNetworkManager->m_mapRoom[RoomName].size() < MAXCLIENT_ROOM)	// << : 접속 가능한 상황
	{
		IsOk = true;
		send(*pSocket, (char*)&IsOk, sizeof(int), 0);
		if(flag->nNetworkID != -1)
			g_pNetworkManager->m_mapRoom[RoomName].push_back(flag->nNetworkID);
	}
	else
	{
		IsOk = false;
		send(*pSocket, (char*)&IsOk, sizeof(int), 0);
		cout << "현재 방인원수 : " << g_pNetworkManager->m_mapRoom[RoomName].size() << "방 이름 : " << RoomName << endl;
	}
}

void SendAllData(SOCKET* pSocket, ST_FLAG* flag)
{
	ST_ALL_DATA stData;
	// << : 플레이어 정보
	g_pDataManager->GetManData(string(flag->szRoomName), &stData.manX, &stData.manY, &stData.manZ, &stData.manAngle);
	g_pDataManager->GetWomanData(string(flag->szRoomName), &stData.womanX, &stData.womanY, &stData.womanZ, &stData.womanAngle);
	// << : 맵 정보
	// << : float에 담아주는 식으로 처리해야함.
	g_pDataManager->GetMapData(string(flag->szRoomName),stData.mapX,stData.mapY,stData.mapZ,stData.mapRotX, stData.mapRotY, stData.mapRotZ,stData.mapIsRunning);
	// << : 해당 내용을 전송한다.

	send(*pSocket, (char*)&stData, sizeof(ST_ALL_DATA), 0);	// << : 클라이언트에게 전송
}

void SendPosition(SOCKET* pSocket, ST_FLAG* flag)
{
	string key = (flag->szRoomName);
	ST_PLAYER_POSITION stSend = g_pDataManager->GetPlayerData(key, IN_PLAYER1);
	send(*pSocket, (char*)&stSend, sizeof(ST_PLAYER_POSITION), 0);	// << : 플레이어에게 데이터 전송
}


