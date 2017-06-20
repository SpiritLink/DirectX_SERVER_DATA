#pragma once

#include "cStuff.h"

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

struct ST_ALL_DATA
{
	// << : 플레이어 데이터
	float manX;
	float manY;
	float manZ;
	float manAngle;
	int manAnim;
	int manItem[INVENTORY_SIZE];

	float womanX;
	float womanY;
	float womanZ;
	float womanAngle;
	int womanAnim;
	int womanItem[INVENTORY_SIZE];

	// << : 맵 데이터
	float mapX[SWITCH_LASTNUM];
	float mapY[SWITCH_LASTNUM];
	float mapZ[SWITCH_LASTNUM];
	float mapRotX[SWITCH_LASTNUM];
	float mapRotY[SWITCH_LASTNUM];
	float mapRotZ[SWITCH_LASTNUM];
	bool mapIsRunning[SWITCH_LASTNUM];
};