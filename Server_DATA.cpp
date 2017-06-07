#include "stdafx.h"
#include "Server_DATA.h"

// >> : �������� ���� �κ��Դϴ�.
HANDLE hMutex_DATA;

unsigned int _stdcall SEND_PROCESS(void * arg);
CRITICAL_SECTION CS_DATA;

int nCnt = 0;

Server_DATA::Server_DATA()
{
}


Server_DATA::~Server_DATA()
{
}

void Server_DATA::Setup()
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
		clntAdrSz = sizeof(clntAdr);
		hClntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &clntAdrSz);
		if (hClntSock > 0)
		{
			cout << "accept IP :" << inet_ntoa(clntAdr.sin_addr) << endl;
			hThread = (HANDLE)_beginthreadex(NULL, 0, SEND_PROCESS, (void*)&hClntSock, 0, NULL);
			nCnt++;
			cout << nCnt << endl;
		}
		if (g_pTime->GetQuit()) break;
	}
}

void Server_DATA::Update()
{
	if (GetAsyncKeyState(VK_NUMPAD9) & 0x0001)
	{
		g_pTime->SetQuit(true);
	}

	if (GetAsyncKeyState(VK_NUMPAD7) & 0x0001)
	{
		cout << nCnt << endl;
	}
}

void Server_DATA::Destroy()
{
	closesocket(hServSock);
	WSACleanup();
}
unsigned int _stdcall SEND_PROCESS(void * arg)
{
	SOCKET hClntSock = *((SOCKET*)arg);	/// << : SOCKET ���� �޾ƿ�
	int strLen = 0;
	ST_PLAYER_POSITION RecvData;		/// << : ������ ���� ����
	ST_SOCKET_POSITION stSendData;		/// << : ���ϰ� ������ ������ ���� ����ü
	stSendData.pSocket = hClntSock;
	HANDLE hProcess = NULL;

	/* �������� �����϶� */
	strLen = recv(hClntSock, (char*)&RecvData, sizeof(ST_PLAYER_POSITION), 0);
	if ( strLen != 0 && strLen != -1)
	{
		WaitForSingleObject(hMutex_DATA, INFINITE);	// << : Wait Mutex
		g_pDataManager->ReceiveData(RecvData);
		ReleaseMutex(hMutex_DATA);					// << : Release Mutex
		sprintf(stSendData.szRoomName, "%s", RecvData.szRoomName);	// << : copy Room Name
		stSendData.nPlayerIndex = RecvData.nPlayerIndex;																					
	}
	/* ���������� �����϶� */
	else
	{
		closesocket(hClntSock);
		nCnt--;
		return 0;
	}

	switch (RecvData.nFROM_CLIENT)			///* Ŭ���̾�Ʈ�� ���ϴ� �����Ϳ� ���� ������� �����մϴ�. */			
	{
	case 0:
		{
			ST_PLAYER_POSITION stPosition;
			stPosition = g_pDataManager->GetPlayerData(string(RecvData.szRoomName), RecvData.nPlayerIndex);
			string text = "FROM SERVER";
			sprintf(RecvData.szRoomName, "%s", text.c_str());
			send(hClntSock, (char*)&stPosition, sizeof(ST_PLAYER_POSITION), 0);	// << : send Function
			cout << "SEND_Position" << endl;
		}
		break;
	}
	nCnt--;
	cout << nCnt << endl;
	return 0;
}