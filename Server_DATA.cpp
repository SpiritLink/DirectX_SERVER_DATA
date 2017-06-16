#include "stdafx.h"
#include "Server_DATA.h"

CRITICAL_SECTION CS_SERVER;

// << : ������ �Լ�
unsigned int _stdcall RECV_REQUEST(void* arg);	// << : ����
unsigned int _stdcall SEND_REQUEST(void* arg);	// << : ����
// << : �Ϲ� �Լ�

void SendNetworkID(ST_SOCKET_ADDR* stData);
void SendRoomName(SOCKET* pSocket, ST_FLAG* flag);
void SendAllData(SOCKET* pSocket, ST_FLAG* flag);
void SendGender(SOCKET* pSocket, int* nNetworkID);
void SendPosition(SOCKET* pSocket, ST_FLAG* flag);

void RecvNetworkID(SOCKET* pSocket,FLAG* pFlag, int* nNetworkID);
void RecvPosition();

void ProcessPosition(void* arg, string RoomName);
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

	/* RECV Sock �ʱ�ȭ */
	hServSock_RECV = socket(PF_INET, SOCK_STREAM, 0);

	memset(&servAddr_RECV, 0, sizeof(servAddr_RECV));
	servAddr_RECV.sin_family = AF_INET;	// << : IPV4 �Ҵ�
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
		/* Ŭ���̾�Ʈ�� ������ �õ������� ó���ϴ� �κ� */
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

	/* SEND Sock �ʱ�ȭ */
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
		/* Ŭ���̾�Ʈ�� ������ �õ������� ó���ϴ� �κ� */
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
	// << : 10�ʿ� �ѹ� ��� �����͸� ���Ϸ� �����մϴ�.
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
		case FLAG_NONE:	// << : ���� Ȯ�ο� ?
			break;
		case FLAG_NETWORK_ID:
			SendNetworkID(&RecvSocket);
			break;
		case FLAG_ROOM_NAME:
			SendRoomName(&ClntSock,&stFlag);
			break;
		case FLAG_ALL_DATA:
			SendAllData(&ClntSock, &stFlag);
			break;
		case FLAG_GENDER:
			ProcessGender(&ClntSock);
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
	int strLen1;
	int nNetworkID = -1;
	clock_t prevTime = clock();
	FLAG eFlag = FLAG_NETWORK_ID;

	while (true)
	{
		switch (eFlag)
		{
		case FLAG::FLAG_NONE:
		{
			switch (g_pNetworkManager->m_mapSwitch[nNetworkID])
			{
			case 0: eFlag = FLAG::FLAG_NETWORK_ID; 
				break;
			case 1:
				if(nNetworkID == -1)
					continue;
				break;
			case 2: eFlag = FLAG::FLAG_GENDER;
				break;
			default:
				break;
			}
		}
			break;
		case FLAG::FLAG_NETWORK_ID:	// << : Ŭ���̾�Ʈ�� ��Ʈ��ũ ���̵� ����� �Ҵ� �޾��������� �˻��ؾ���
			RecvNetworkID(&ClntSock, &eFlag, &nNetworkID);
			break;
		case FLAG::FLAG_GENDER:
			SendGender(&ClntSock, &nNetworkID);
			break;
		case FLAG::FLAG_POSITION:
			break;
		case FLAG::FLAG_OBJECT_DATA:
			break;
		}
		
		// << : ���� ��Ʈ��ũ ���̵� -1�̶�� �����ϰ� ������ ���� �ʴ´�.
	}

	closesocket(ClntSock);
	return 0;
}

/* Ŭ���̾�Ʈ�� NetworkID�� ���ɴϴ� */
void RecvNetworkID(SOCKET* pSocket, FLAG* pFlag, int* nNetworkID)
{
	int eFlag = FLAG::FLAG_NETWORK_ID;
	int NetworkID;
	send(*pSocket, (char*)&eFlag, sizeof(FLAG), 0);
	recv(*pSocket, (char*)&NetworkID, sizeof(int), 0);
	if (NetworkID != -1)
	{
		*nNetworkID = NetworkID;
		g_pNetworkManager->m_mapSwitch[NetworkID] = 1;
		*pFlag = FLAG::FLAG_NONE;
	}
}

void RecvPosition()
{

}

void SendNetworkID(ST_SOCKET_ADDR* stData)
{
	ST_SOCKET_ADDR* pData = stData;
	int ID = ++g_nNetworkID;
	send(pData->stSocket, (char*)&ID, sizeof(int), 0);
	g_pNetworkManager->addAddr(ID, pData->stAddr);		// << : ��Ʈ��ũ ���̵� �ּҸ� ��� ����մϴ�.
}

void SendRoomName(SOCKET* pSocket,ST_FLAG* flag)
{
	int IsOk = 0;
	string RoomName = flag->szRoomName;
	if (g_pNetworkManager->GetClntNum(RoomName) < MAXCLIENT_ROOM)	// << : ���� ������ ��Ȳ
	{
		IsOk = true;
		send(*pSocket, (char*)&IsOk, sizeof(int), 0);
		if(flag->nNetworkID != -1)	// << : NetwordID�� ����� �Ҵ�� �������
			g_pNetworkManager->addID(flag->nNetworkID, string(flag->szRoomName));
	}
	else
	{
		IsOk = false;
		send(*pSocket, (char*)&IsOk, sizeof(int), 0);
		cout << "���� ���ο��� : " << g_pNetworkManager->m_mapRoom[RoomName].size() << "�� �̸� : " << RoomName << endl;
	}
}

void SendAllData(SOCKET* pSocket, ST_FLAG* flag)
{
	ST_ALL_DATA stData;
	// << : �÷��̾� ����
	g_pDataManager->GetManData(string(flag->szRoomName), &stData.manX, &stData.manY, &stData.manZ, &stData.manAngle);
	g_pDataManager->GetWomanData(string(flag->szRoomName), &stData.womanX, &stData.womanY, &stData.womanZ, &stData.womanAngle);
	// << : ������
	g_pDataManager->GetMapData(string(flag->szRoomName),stData.mapX,stData.mapY,stData.mapZ,stData.mapRotX, stData.mapRotY, stData.mapRotZ,stData.mapIsRunning);
	send(*pSocket, (char*)&stData, sizeof(ST_ALL_DATA), 0);	// << : Ŭ���̾�Ʈ���� ����
}

void SendGender(SOCKET* pSocket, int* nNetworkID)
{
	// << : Ŭ���̾�Ʈ���� ������ �����͸� �˷��ݴϴ�.
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
	
	send(*pSocket, (char*)&Gender, sizeof(int), 0);
	cout << "���� : " << Gender << endl;
}

void SendPosition(SOCKET* pSocket, ST_FLAG* flag)
{
	string key = (flag->szRoomName);
	ST_PLAYER_POSITION stSend = g_pDataManager->GetPlayerData(key, IN_PLAYER1);
	send(*pSocket, (char*)&stSend, sizeof(ST_PLAYER_POSITION), 0);	// << : �÷��̾�� ������ ����
}

void ProcessPosition(void* arg, string RoomName)
{
	SOCKET ClntSock = *(SOCKET*)arg;
	char szBuffer[1000] = { 0, };
	recv(ClntSock, szBuffer, sizeof(ST_PLAYER_POSITION), 0);
	ST_PLAYER_POSITION RecvPosition = *(ST_PLAYER_POSITION*)szBuffer;
	WaitForSingleObject(g_hMutex_DATA, INFINITE);
	g_pDataManager->ReceiveData(RecvPosition);

	cout << "FLAG_POSITION ��ǥ ����" << endl;
	ST_PLAYER_POSITION SendPosition;
	int nIndex;
	SendPosition = g_pDataManager->GetPlayerData(RoomName, RecvPosition.nPlayerIndex);
	ReleaseMutex(g_hMutex_DATA);
	send(ClntSock, (char*)&SendPosition, sizeof(ST_PLAYER_POSITION), 0);
	cout << "FLAG_POSITION ��ǥ ����" << endl;

}

/* ������ ������ �����ϰ� �ش� ������ �����ϰ� �մϴ�.*/
void ProcessGender(SOCKET* pSocket)
{
	ST_FLAG stRecv;
	recv(*pSocket, (char*)&stRecv, sizeof(ST_FLAG), 0);	// << : ������ �����Ѵ�

	// << : ������ ������ �����Ѵ�.
	if (stRecv.nPlayerIndex == IN_PLAYER1)
		g_pNetworkManager->m_mapGender[stRecv.nNetworkID] = IN_PLAYER1;
	else if (stRecv.nPlayerIndex == IN_PLAYER2)
		g_pNetworkManager->m_mapGender[stRecv.nNetworkID] = IN_PLAYER2;
	else
		g_pNetworkManager->m_mapGender[stRecv.nNetworkID] = 0;

	// << : ������ �濡�ִ� ��� �������� �������� ó���Ѵ�.
	g_pNetworkManager->SendGender(string(stRecv.szRoomName));
}


