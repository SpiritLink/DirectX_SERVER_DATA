#include "stdafx.h"
#include "Server_DATA.h"

// >> : 구현되지 못한 부분입니다.
HANDLE hMutex_DATA;

unsigned int _stdcall PROCESS_RECV(void * arg);
CRITICAL_SECTION CS_DATA;

int nCnt = 0;

Server_DATA::Server_DATA()
	: m_dwSaveTick(0)
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
	servAdr.sin_family = AF_INET;	// << : IPV4 할당
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
			hThread = (HANDLE)_beginthreadex(NULL, 0, PROCESS_RECV, (void*)&hClntSock, 0, NULL);
			nCnt++;
			cout << "Add Thread Count : " << nCnt << endl;
		}
		if (g_pTime->GetQuit()) break;
	}
}

void Server_DATA::Update()
{
	// << : 10초에 한번 모든 데이터를 파일로 저장합니다.
	//if (m_dwSaveTick + (ONE_SECOND * 10) < GetTickCount())
	//{
	//	m_dwSaveTick = GetTickCount();
	//	g_pDataManager->SaveAllData();
	//}
	if (GetAsyncKeyState(VK_NUMPAD7) & 0x0001)
	{
		cout << nCnt << endl;
	}
	
	if (GetAsyncKeyState(VK_NUMPAD8) & 0x0001)
	{
		g_pDataManager->SaveAllData();
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
	SOCKET hClntSock = *((SOCKET*)arg);	/// << : SOCKET 정보 받아옴
	int strLen = 0;
	ST_PLAYER_POSITION RecvData;		/// << : 데이터 수신 버퍼
	HANDLE hProcess = NULL;

	/* 정상적인 연결일때 */
	strLen = recv(hClntSock, (char*)&RecvData, sizeof(ST_PLAYER_POSITION), 0);
	if ( strLen != 0 && strLen != -1)
	{
		WaitForSingleObject(hMutex_DATA, INFINITE);	// << : Wait Mutex
		g_pDataManager->ReceiveData(RecvData);
		ReleaseMutex(hMutex_DATA);					// << : Release Mutex
	}
	/* 비정상적인 연결일때 */
	else
	{
		closesocket(hClntSock);
		nCnt--;
		cout << "Sub Thread Count : " << nCnt << endl;
		return 0;
	}

	switch (RecvData.nFROM_CLIENT)			///* 클라이언트가 원하는 데이터에 맞춰 스레드로 전송합니다. */			
	{
	case 0:
		{
			ST_PLAYER_POSITION stPosition;
			stPosition = g_pDataManager->GetPlayerData(string(RecvData.szRoomName), RecvData.nPlayerIndex);
			sprintf_s(RecvData.szRoomName, "%s", "FROM_SERVER",11);
			send(hClntSock, (char*)&stPosition, sizeof(ST_PLAYER_POSITION), 0);	// << : send Function
			cout << "SEND_Position" << endl;
		}
		break;
	}
	nCnt--;
	cout << "Sub Thread Count : " << nCnt << endl;
	return 0;
}
