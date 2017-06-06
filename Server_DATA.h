#pragma once

#define PORT_DATA 1234
#define WAIT_MILLISECOND 5000
class Server_DATA
{
private:
	int clntAdrSz;

	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAdr, clntAdr;
	HANDLE hThread;
public:
	Server_DATA();
	~Server_DATA();

	void Setup();
	void Update();
	void Destroy();
};

