#pragma once

class Server_DATA
{
private:
	int clntAdrSz;
	
	// << : ���� ������ ���� ����
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAdr, clntAdr;

	// << : ���� ���ο� ������ ���� ����
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


