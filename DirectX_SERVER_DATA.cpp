// DirectX_SERVER_DATA.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Server_DATA.h"

unsigned int _stdcall ThData_ACCEPT(LPVOID lpParam)
{
	Server_DATA * pServerData = ((Server_DATA*)lpParam);
	pServerData->Setup();
	return 0;
}

int main()
{
	DWORD dwThID;
	HANDLE hThread;
	unsigned long ulStackSize = 0;

	Server_DATA* pServerData = new Server_DATA;
	hThread = (HANDLE)_beginthreadex(NULL, 0, (unsigned(_stdcall*)(void*)) ThData_ACCEPT, (void*)&pServerData, 0, (unsigned*)&dwThID);	// << : 데이터 전송 스레드

	WaitForSingleObject(hThread, INFINITE);

	CloseHandle(hThread);

	pServerData->Destroy();	
	return 0;
}

