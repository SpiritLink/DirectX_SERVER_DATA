#pragma once

#define PORT_DATA 1234
#define PORT_CLIENT 10111
#define WAIT_MILLISECOND 5000
#define ONE_SECOND 1000

class Server_DATA
{
private:
	int clntAdrSz;
	
	// << : 기존 연결을 위한 정보
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAdr, clntAdr;

	// << : 현재 새로운 연결을 위한 정보
	int clntAdrSz2;
	WSADATA wsaData2;
	SOCKET hServSock2, hClntSock2;
	SOCKADDR_IN servAdr2, clntAdr2;

	HANDLE hThread, hThread_SAVE, hThread_RECV;
public:
	Server_DATA();
	~Server_DATA();

	void Setup_Prev();
	void Setup_Current();
	void Update();
	void Destroy();
};

