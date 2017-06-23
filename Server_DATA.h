#pragma once

#include "cStuff.h"

#define SLEEP_TIME 100

struct ST_ALL_DATA;

class Server_DATA
{
private:
	int clntAdrSz_RECV, clntAdrSz_SEND;
	WSADATA wsaData;
	SOCKET hServSock_RECV, hServSock_SEND, hClntSock_RECV, hClntSock_SEND;
	SOCKADDR_IN servAddr_RECV,servAddr_SEND, clntAdr_RECV, clntAdr_SEND;

	HANDLE hThread, hThread_SAVE, hThread_RECV, hThread_SEND;
	HANDLE hTestRecv, hTestSend;
public:
	Server_DATA();
	~Server_DATA();

	void Setup_RECV();
	void Setup_SEND();
	void Update();
	void Destroy();
};
