#pragma once

class Server_DATA
{
private:
	int clntAdrSz;
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAdr, clntAdr;

	HANDLE hThread, hThread_SAVE, hThread_RECV, hThread_SEND;
public:
	Server_DATA();
	~Server_DATA();

	void Setup();
	void Update();
	void Destroy();
};


