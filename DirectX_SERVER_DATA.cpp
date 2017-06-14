// DirectX_SERVER_DATA.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "Server_DATA.h"

unsigned int _stdcall ThData_ACCEPT(LPVOID lpParam);
int g_nThreadCount;
HANDLE g_hMutex_DATA;

int main()
{
	g_hMutex_DATA = CreateMutex(NULL, FALSE, NULL);
	g_pDataManager->Setup();
	DWORD dwThID;
	HANDLE hThread;
	unsigned long ulStackSize = 0;
	g_nThreadCount = 0;
	
	Server_DATA* pServerData = new Server_DATA;
	hThread = (HANDLE)_beginthreadex(NULL, 0, (unsigned(_stdcall*)(void*)) ThData_ACCEPT, (void*)&pServerData, 0, (unsigned*)&dwThID);	// << : ������ ���� ������

	while (true)
	{
		pServerData->Update();
		if (g_pTime->GetQuit()) break;
	}

	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	pServerData->Destroy();	
	return 0;
}
unsigned int _stdcall ThData_ACCEPT(LPVOID lpParam)
{
	Server_DATA * pServerData = ((Server_DATA*)lpParam);
	pServerData->Setup_RECV();
	return 0;
}