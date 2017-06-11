#pragma once

#define PORT_DATA 1234
#define WAIT_MILLISECOND 5000
#define ONE_SECOND 1000

class Server_DATA
{
private:
	int clntAdrSz;

	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAdr, clntAdr;
	HANDLE hThread, hThread_SAVE;
	DWORD m_dwSaveTick;
public:
	Server_DATA();
	~Server_DATA();

	void Setup();
	void Update();
	void Destroy();
};

