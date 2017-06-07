// DirectX_SERVER_DATA.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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
	hThread = (HANDLE)_beginthreadex(NULL, 0, (unsigned(_stdcall*)(void*)) ThData_ACCEPT, (void*)&pServerData, 0, (unsigned*)&dwThID);	// << : ������ ���� ������

	WaitForSingleObject(hThread, INFINITE);

	CloseHandle(hThread);

	pServerData->Destroy();	
	return 0;
}

