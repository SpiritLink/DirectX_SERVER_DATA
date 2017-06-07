#include "stdafx.h"
#include "Server_DATA.h"

// >> : 구현되지 못한 부분입니다.
HANDLE hMutex_DATA;

unsigned int _stdcall SEND_PROCESS(void * arg);
unsigned int _stdcall SEND_Position(void * arg);
unsigned int _stdcall SEND_ItemObject(void* arg);
unsigned int _stdcall SEND_All(void* arg);
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
	SOCKET hClntSock = *((SOCKET*)arg);	/// << : SOCKET 정보 받아옴
	int strLen = 0;
	ST_PLAYER_POSITION stPosition;		/// << : 데이터 수신 버퍼
	ST_SOCKET_POSITION stSendData;		/// << : 소켓과 데이터 정보를 담은 구조체
	stSendData.pSocket = hClntSock;
	HANDLE hProcess = NULL;

	///* 정상적인 연결일때 요청을 처리합니다 */
	if (strLen = recv(hClntSock, (char*)&stPosition, sizeof(ST_PLAYER_POSITION), 0) > 0)
	{
		///* 수신한 데이터를 적용합니다. */
		WaitForSingleObject(hMutex_DATA, INFINITE);	// << : Wait Mutex
		g_pDataManager->ReceiveData(stPosition);
		ReleaseMutex(hMutex_DATA);					// << : Release Mutex
		sprintf(stSendData.szRoomName, "%s", stPosition.szRoomName);	// << : copy Room Name
		stSendData.nPlayerIndex = stPosition.nPlayerIndex;
																					
		switch (stPosition.nFROM_CLIENT)			///* 클라이언트가 원하는 데이터에 맞춰 스레드로 전송합니다. */			
		{
		case 0:
			hProcess = (HANDLE)_beginthreadex(NULL, 0, SEND_Position, (void*)&stSendData, 0, NULL);
			break;
		case 1:
			hProcess = (HANDLE)_beginthreadex(NULL, 0, SEND_ItemObject, (void*)&stSendData, 0, NULL);
			break;
		case 2:
			hProcess = (HANDLE)_beginthreadex(NULL, 0, SEND_All, (void*)&stSendData, 0, NULL);
			break;
		}
	}
	///* 비정상적인 연결을 해제합니다. */
	else
	{
		closesocket(hClntSock);
	}

	WaitForSingleObject(hProcess, WAIT_MILLISECOND);	// << : 5초간 기다려도 처리되지 않으면 종료합니다.
	CloseHandle(hProcess);
	nCnt--;
	cout << nCnt << endl;
	return 0;
}

unsigned int _stdcall SEND_Position(void * arg)
{
	ST_SOCKET_POSITION stData = *((ST_SOCKET_POSITION*)arg);	// << : type conversion
	SOCKET hClntSock = stData.pSocket;
	int strLen = 0;
	ST_PLAYER_POSITION stPosition;
	stPosition = g_pDataManager->GetPlayerData(string(stData.szRoomName), stData.nPlayerIndex);
	
	// >> :
	string text = "FROM SERVER";
	sprintf(stPosition.szRoomName, "%s", text.c_str());

	// << :



	if (hClntSock != SOCKET_ERROR)
	{
		send(hClntSock, (char*)&stPosition, sizeof(ST_PLAYER_POSITION), 0);	// << : send Function
		cout << "SEND_Position" << endl;
	}
	closesocket(hClntSock);				// << : Close Socket
	return 0;
}
unsigned int _stdcall SEND_ItemObject(void* arg)
{
	SOCKET hClntSock = *((SOCKET*)arg);	// << : Init Socket
	closesocket(hClntSock);				// << : Close Socket
	return 0;
}

unsigned int _stdcall SEND_All(void* arg)
{
	SOCKET hClntSock = *((SOCKET*)arg);	// << : Init Socket
	closesocket(hClntSock);				// << : Close Socket

	return 0;
}