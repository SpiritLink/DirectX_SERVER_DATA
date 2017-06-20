#include "stdafx.h"
#include "Server_DATA.h"

CRITICAL_SECTION CS_SERVER;

// << : 스레드 함수
unsigned int _stdcall RECV_REQUEST(void* arg);	// << : 수신
unsigned int _stdcall SEND_REQUEST(void* arg);	// << : 전송

// << : 일반 함수
void SendNetworkID(ST_SOCKET_ADDR* stData, bool* bConnected);
void SendRoomName(SOCKET* pSocket, ST_FLAG* flag, bool* bConnected);
void SendAllData(SOCKET* pSocket, ST_FLAG* flag, bool* bConnected);
void SendGender(SOCKET* pSocket, int* nNetworkID, bool* bConnected);
void SendPosition(SOCKET* pSocket, int* nNetworkID, bool* bConnected);
void SendObjectData(SOCKET* pSocket, int* nNetworkID, bool* bConnected);

void RecvNetworkID(SOCKET* pSocket,FLAG* pFlag, int* nNetworkID, bool* bConnected);
void RecvPosition(SOCKET* pSocket, ST_FLAG* flag);
void RecvObjectData(SOCKET* pSocket, ST_FLAG* pFlag, int* nNetworkID, bool* bConnected);

void ProcessGender(SOCKET* pSocket);

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
			cout << "accept IP :" << inet_ntoa(clntAdr_RECV.sin_addr) << endl;
			hTestRecv = (HANDLE)_beginthreadex(NULL, 0, RECV_REQUEST, (void*)&RecvSock, 0, NULL);
			g_nThreadCount++;
			cout << " Thread Count : " << g_nThreadCount << endl;
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
			cout << "accept IP :" << inet_ntoa(clntAdr_SEND.sin_addr) << endl;
			hTestSend = (HANDLE)_beginthreadex(NULL, 0, SEND_REQUEST, (void*)&SendSock, 0, NULL);
			g_nThreadCount++;
			cout << "Thread Count : " << g_nThreadCount << endl;
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
		g_pTime->SetSaveTimer(clock());
		g_pDataManager->SaveAllData();
		cout << g_pTime->GetLocalTime_String() << " : Save Data" << endl;
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
}

void Server_DATA::Destroy()
{
	closesocket(hServSock_RECV);
	closesocket(hServSock_SEND);
	WSACleanup();
}

/* 요청을 대기하는 스레드 함수입니다 */
unsigned int _stdcall RECV_REQUEST(void* arg)
{
	ST_SOCKET_ADDR RecvSocket = *(ST_SOCKET_ADDR*)arg;
	SOCKET ClntSock = RecvSocket.stSocket;
	char szBuffer[BUF_SIZE * 10] = { 0, };
	int strLen, nNetworkID;
	bool IsConnected = true;

	while (IsConnected)
	{
		strLen = recv(ClntSock, szBuffer, sizeof(ST_FLAG), 0);
		if (strLen == -1) IsConnected = false;

		ST_FLAG stFlag = *(ST_FLAG*)szBuffer;
		nNetworkID = stFlag.nNetworkID;
		switch (stFlag.eFlag)
		{
		case FLAG_NONE:	// << : 접속 확인용 ?
			break;
		case FLAG_NETWORK_ID:
			SendNetworkID(&RecvSocket,&IsConnected);
			break;
		case FLAG_ROOM_NAME:
			SendRoomName(&ClntSock,&stFlag, &IsConnected);
			break;
		case FLAG_ALL_DATA:
			SendAllData(&ClntSock, &stFlag, &IsConnected);
			break;
		case FLAG_GENDER:
			ProcessGender(&ClntSock);
			break;
		case FLAG_POSITION:
			RecvPosition(&ClntSock, &stFlag);
			break;
		case FLAG_OBJECT_DATA:
			RecvObjectData(&ClntSock, &stFlag, &nNetworkID,&IsConnected);
			break;
		}
		continue;
	}

	g_pNetworkManager->Quit(nNetworkID);
	closesocket(ClntSock);

	g_nThreadCount--;
	cout << "Thread Count : " << g_nThreadCount << endl;
	return 0;
}

/* 요청을 전송하는 스레드 함수입니다 */
unsigned int _stdcall SEND_REQUEST(void* arg)
{
	ST_SOCKET_ADDR RecvSocket = *(ST_SOCKET_ADDR*)arg;
	SOCKET ClntSock = RecvSocket.stSocket;
	char szBuffer[BUF_SIZE * 10] = { 0, };
	int strLen1;
	int nNetworkID = -1;
	bool IsConnected = true;
	clock_t prevTime = clock();
	FLAG eFlag = FLAG_NETWORK_ID;

	while (IsConnected)
	{
		switch (eFlag)
		{
		case FLAG::FLAG_NONE:
		{
			int nSwitch = g_pNetworkManager->m_mapSwitch[nNetworkID];
			if (nSwitch == 0)
				eFlag = FLAG::FLAG_NETWORK_ID;
			if (nSwitch == 1)
				if (nNetworkID == -1) continue;
			if (nSwitch == 2)
				eFlag = FLAG::FLAG_GENDER;
			if (nSwitch == 3)
				eFlag = FLAG::FLAG_POSITION;
			if (nSwitch == 4)
				eFlag = FLAG::FLAG_OBJECT_DATA;
		}
		break;
		case FLAG::FLAG_NETWORK_ID:	// << : 클라이언트가 네트워크 아이디를 제대로 할당 받았을때까지 검사해야함
			RecvNetworkID(&ClntSock, &eFlag, &nNetworkID, &IsConnected);
			break;
		case FLAG::FLAG_GENDER:
			SendGender(&ClntSock, &nNetworkID, &IsConnected);
			eFlag = FLAG::FLAG_NONE;
			g_pNetworkManager->m_mapSwitch[nNetworkID] = 0;
			break;
		case FLAG::FLAG_POSITION:
			if (prevTime + ONE_SECOND < clock())	// << : 상대 좌표 전송 간격
			{
				prevTime = clock();
				SendPosition(&ClntSock, &nNetworkID, &IsConnected);
			}
			break;
		case FLAG::FLAG_OBJECT_DATA:
			SendObjectData(&ClntSock, &nNetworkID, &IsConnected);
			eFlag = FLAG::FLAG_NONE;
			g_pNetworkManager->m_mapSwitch[nNetworkID] = 3;	// << : 다시 좌표를 전송하게 함
			break;
		}
	}
	// << : NetworkManager에서 정보 제거해야함
	// << : 네트워크 매니저에 ID를 넣어주면 알아서 제거한다 ?
	g_pNetworkManager->Quit(nNetworkID);
	closesocket(ClntSock);

	g_nThreadCount--;
	cout << "Thread Count : " << g_nThreadCount << endl;

	return 0;
}

/* 클라이언트 에게 또다른 클라이언트의 IP주소를 알려줍니다 */
void SendNetworkID(ST_SOCKET_ADDR* stData, bool* bConnected)
{
	ST_SOCKET_ADDR* pData = stData;
	int ID = ++g_nNetworkID;
	int result;
	result = send(pData->stSocket, (char*)&ID, sizeof(int), 0);
	g_pNetworkManager->addAddr(ID, pData->stAddr);		// << : 네트워크 아이디에 주소를 묶어서 등록합니다.
	if (result == -1) *bConnected = false;
}

/* 연결 가능한 방인지 확인하고 알려줍니다 */
void SendRoomName(SOCKET* pSocket,ST_FLAG* flag, bool* bConnected)
{
	int IsOk = 0;
	int result;
	string RoomName = flag->szRoomName;
	if (g_pNetworkManager->GetClntNum(RoomName) < MAXCLIENT_ROOM)	// << : 접속 가능한 상황
	{
		IsOk = true;
		result = send(*pSocket, (char*)&IsOk, sizeof(int), 0);
		if(flag->nNetworkID != -1)	// << : NetwordID가 제대로 할당된 유저라면
			g_pNetworkManager->addID(flag->nNetworkID, string(flag->szRoomName));
	}
	else
	{
		IsOk = false;
		result = send(*pSocket, (char*)&IsOk, sizeof(int), 0);
		cout << "현재 방인원수 : " << g_pNetworkManager->m_mapRoom[RoomName].size() << "방 이름 : " << RoomName << endl;
	}
	if (result == -1) *bConnected = false;
}

/* 게임 시작에 필요한 초기 데이터를 전송합니다 */
void SendAllData(SOCKET* pSocket, ST_FLAG* flag, bool* bConnected)
{
	ST_ALL_DATA stData;
	string key = string(flag->szRoomName);
	int result;
	// 플레이어 정보 , 인벤토리 정보, 맵정보
	g_pDataManager->GetManPosition(key, &stData.manX, &stData.manY, &stData.manZ, &stData.manAngle);
	g_pDataManager->GetWomanPosition(string(flag->szRoomName), &stData.womanX, &stData.womanY, &stData.womanZ, &stData.womanAngle);

	g_pDataManager->GetManInventory(key, stData.manItem);
	g_pDataManager->GetWomanInventory(key, stData.womanItem);

	g_pDataManager->GetMapData(string(flag->szRoomName),stData.mapX,stData.mapY,stData.mapZ,stData.mapRotX, stData.mapRotY, stData.mapRotZ,stData.mapIsRunning);

	result = send(*pSocket, (char*)&stData, sizeof(ST_ALL_DATA), 0);	// << : 클라이언트에게 전송
	if (result == -1) *bConnected = false;
}

/* 상대가 어떤 성별을 골랐는지 확인, 전송합니다 */
void SendGender(SOCKET* pSocket, int* nNetworkID, bool* bConnected)
{
	// << : 클라이언트에게 전송할 데이터를 알려줍니다.
	FLAG eFlag = FLAG::FLAG_GENDER;
	send(*pSocket, (char*)&eFlag, sizeof(FLAG), 0);

	int Gender;
	string key = g_pNetworkManager->m_mapID[*nNetworkID];

	if (g_pNetworkManager->m_mapRoom[key].size() < MAXCLIENT_ROOM)
		Gender = 0;
	else
	{
		int ClntID;
		for (int i = 0; i < g_pNetworkManager->m_mapRoom[key].size(); ++i)
		{
			if (g_pNetworkManager->m_mapRoom[key][i] == *nNetworkID)
				continue;
			ClntID = g_pNetworkManager->m_mapRoom[key][i];
		}

		Gender = g_pNetworkManager->m_mapGender[ClntID];
	}
	
	g_pNetworkManager->m_mapSwitch[*nNetworkID] = 3; // < : 성별 그만 보내게 함
	int result;
	result = send(*pSocket, (char*)&Gender, sizeof(int), 0);

	// 연결이 끊긴 상황 예외처리
	if (result == -1)
		*bConnected = false;

	cout << "성별 : " << Gender << endl;
}

/* 클라이언트에게 상대의 좌표를 전송합니다.*/
void SendPosition(SOCKET* pSocket, int* nNetworkID, bool* bConnected)
{
	FLAG eFlag = FLAG::FLAG_POSITION;
	send(*pSocket, (char*)&eFlag, sizeof(FLAG), 0);

	int nGender = g_pNetworkManager->m_mapGender[*nNetworkID];
	cout << "성별 : " << nGender << endl;
	string szKey = g_pNetworkManager->m_mapID[*nNetworkID];
	// << : ID로 성별을 조회
	ST_PLAYER_POSITION stData;
	stData.nPlayerIndex = -1;
	if (nGender == IN_PLAYER1)
	{
		stData.nPlayerIndex = OUT_PLAYER2;
		g_pDataManager->GetWomanPosition(szKey, &stData.fX, &stData.fY, &stData.fZ, &stData.fAngle);
	}
	else if (nGender == IN_PLAYER2)
	{
		stData.nPlayerIndex = OUT_PLAYER1;
		g_pDataManager->GetManPosition(szKey, &stData.fX, &stData.fZ, &stData.fZ, &stData.fAngle);
	}
	
	int result = send(*pSocket, (char*)&stData, sizeof(ST_PLAYER_POSITION), 0);
	if (result == -1) 
		*bConnected = false;

	cout << "Room : " << szKey;
	cout << " X : " << stData.fX;
	cout << " Y : " << stData.fY;
	cout << " Z : " << stData.fZ;
	cout << " Angle : " << stData.fAngle;

}

/* 맵 정보를 전송합니다 */
void SendObjectData(SOCKET* pSocket, int* nNetworkID, bool* bConnected)
{
	FLAG eFlag = FLAG::FLAG_OBJECT_DATA;
	send(*pSocket, (char*)&eFlag, sizeof(FLAG), 0);

	string szKey = g_pNetworkManager->m_mapID[*nNetworkID];
	ST_OBJECT_DATA stData;
	g_pDataManager->GetMapData(szKey, stData.mapX, stData.mapY, stData.mapZ, stData.mapRotX, stData.mapRotY, stData.mapRotZ, stData.mapIsRunning);
	
	ST_MAP_STATUS stMapStatus;
	stMapStatus = g_pDataManager->GetMapStatus(szKey);
	stData.bValve1 = stMapStatus.bValve1;
	stData.bValve2 = stMapStatus.bValve2;
	stData.nFValve1Count = stMapStatus.nFValve1Count;
	stData.nFValve2Count = stMapStatus.nFValve2Count;
	stData.nBrickCount = stMapStatus.nBrickCount;

	int result = send(*pSocket, (char*)&stData, sizeof(ST_OBJECT_DATA), 0);
	if (result == -1) *bConnected = false;

	g_pNetworkManager->m_mapSwitch[*nNetworkID] = 3; // < : 좌표를 다시 전송하게 함
}

/* 클라이언트의 NetworkID를 얻어옵니다 */
void RecvNetworkID(SOCKET* pSocket, FLAG* pFlag, int* nNetworkID, bool* bConnected)
{
	int eFlag = FLAG::FLAG_NETWORK_ID;
	int NetworkID;
	int result;
	send(*pSocket, (char*)&eFlag, sizeof(FLAG), 0);
	result = recv(*pSocket, (char*)&NetworkID, sizeof(int), 0);
	if (NetworkID != -1)
	{
		*nNetworkID = NetworkID;
		g_pNetworkManager->m_mapSwitch[NetworkID] = 1;
		*pFlag = FLAG::FLAG_NONE;
	}
	if (result == -1)
		*bConnected = false;
}

/* 플레이어의 좌표를 수신합니다. */
void RecvPosition(SOCKET* pSocket, ST_FLAG* flag)
{
	ST_PLAYER_POSITION stData;
	recv(*pSocket, (char*)&stData, sizeof(ST_PLAYER_POSITION), 0);
	g_pDataManager->ReceivePosition(stData);
	string key = (flag->szRoomName);
	g_pNetworkManager->m_mapSwitch[flag->nNetworkID] = 3;
}

/* 맵정보를 수신합니다 */
void RecvObjectData(SOCKET* pSocket, ST_FLAG* pFlag, int* nNetworkID, bool* bConnected)
{
	ST_OBJECT_DATA stData;
	string key = pFlag->szRoomName;

	int result = recv(*pSocket, (char*)&stData, sizeof(ST_OBJECT_DATA), 0);
	// >> 수신한 데이터를 컨테이너에 적용시키고 영향받는 유저들의 스위치를 변경합니다.
	if (result == -1) *bConnected = false;
	g_pDataManager->ReceiveObject(key, stData);

}

/* 성별을 서버에 적용하고 해당 내용을 전송하게 합니다.*/
void ProcessGender(SOCKET* pSocket)
{
	ST_FLAG stRecv;
	recv(*pSocket, (char*)&stRecv, sizeof(ST_FLAG), 0);	// << : 성별을 수신한다

	// << : 성별을 서버에 적용한다.
	if (stRecv.nPlayerIndex == IN_PLAYER1)
		g_pNetworkManager->m_mapGender[stRecv.nNetworkID] = IN_PLAYER1;
	else if (stRecv.nPlayerIndex == IN_PLAYER2)
		g_pNetworkManager->m_mapGender[stRecv.nNetworkID] = IN_PLAYER2;
	else
		g_pNetworkManager->m_mapGender[stRecv.nNetworkID] = 0;
	cout << "Recv Gender : " << stRecv.nPlayerIndex << endl;
	// << : 성별을 방에있는 모든 유저에게 날리도록 처리한다.
	g_pNetworkManager->SendGender(string(stRecv.szRoomName));
}


