#pragma once

#define PORT_DATA 1234
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

	HANDLE hThread, hThread_SAVE, hThread_RECV, hThread_SEND;
public:
	Server_DATA();
	~Server_DATA();

	void Setup_Prev();
	void Setup_Current();
	void Update();
	void Destroy();
};

enum FLAG
{
	FLAG_NONE = 1 << 0,
	FLAG_IP = 1 << 1,
	FLAG_POSITION = 1 << 2,
	FLAG_OBJECT_DATA = 1 << 3,
	FLAG_ALL = 1 << 4,
};

struct ST_FLAG
{
	char szRoomName[50] = { 0, };
	int nPlayerIndex;
	int eFlag;
};