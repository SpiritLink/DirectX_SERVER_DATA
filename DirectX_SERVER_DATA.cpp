// DirectX_SERVER_DATA.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Server_DATA.h"

unsigned int _stdcall RECV_REQUEST_CLIENT(LPVOID lpParam);
unsigned int _stdcall SEND_REQUEST_CLIENT(LPVOID lpParam);

int g_nNetworkID = 0;
int g_nThreadCount;
HANDLE g_hMutex_DATA;

int main()
{
	g_hMutex_DATA = CreateMutex(NULL, FALSE, NULL);
	g_pDataManager->Setup();
	DWORD dwThID1, dwThID2;
	HANDLE hThread_RECV, hThread_SEND;
	unsigned long ulStackSize = 0;
	g_nThreadCount = 0;
	
	Server_DATA* pServerData = new Server_DATA;
	hThread_RECV = (HANDLE)_beginthreadex(NULL, 0, (unsigned(_stdcall*)(void*)) RECV_REQUEST_CLIENT, (void*)&pServerData, 0, (unsigned*)&dwThID1);	// << : 데이터 수신 스레드
	hThread_SEND = (HANDLE)_beginthreadex(NULL, 0, (unsigned(_stdcall*)(void*)) SEND_REQUEST_CLIENT, (void*)&pServerData, 0, (unsigned*)&dwThID2);	// << : 데이터 전송 스레드
	
	while (true)
	{
		pServerData->Update();
		if (g_pTime->GetQuit()) break;
	}

	WaitForSingleObject(hThread_RECV, INFINITE);
	WaitForSingleObject(hThread_SEND, INFINITE);

	CloseHandle(hThread_RECV);
	CloseHandle(hThread_SEND);

	pServerData->Destroy();	
	SAFE_DELETE(pServerData);

	return 0;
}
unsigned int _stdcall RECV_REQUEST_CLIENT(LPVOID lpParam)
{
	Server_DATA * pServerData = ((Server_DATA*)lpParam);
	pServerData->Setup_RECV();
	return 0;
}

unsigned int _stdcall SEND_REQUEST_CLIENT(LPVOID lpParam)
{
	Server_DATA * pServerData = ((Server_DATA*)lpParam);
	pServerData->Setup_SEND();
	return 0;
}
