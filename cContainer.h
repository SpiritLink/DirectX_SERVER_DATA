#pragma once
#include "cPlayer.h"
#include "cStuff.h"
#define CONNECT_TIME 5
#define D3DX_PI 3.141592654f

class cContainer
{
private:
	string	m_sRoomName;		// ���̸�
	cPlayer m_stMan;			// ���� ������
	cPlayer m_stWoman;			// ���� ������

	clock_t m_nManTime;			// ���� �ֱ� ���� �ð�
	clock_t m_nWomanTime;		// ���� �ֱ� ���� �ð�

	cStuff m_aStuff[SWITCH_LASTNUM];	// << : ������Ʈ

	SYNTHESIZE(int, nPlayer1NetID, Player1NetID);
	SYNTHESIZE(int, nPlayer2NetID, Player2NetID);

	SYNTHESIZE(ST_SOCKET_ADDR, Player1Sock, Player1Sock);
	SYNTHESIZE(ST_SOCKET_ADDR, Player2Sock, Player2Sock);

	HANDLE hThread1P, hThread2P;
	
public:
	cContainer();
	~cContainer();

	ST_PLAYER_POSITION GetData(int nIndex);
	int GetOnlineUser();
	void Setup(string key);
	void SaveData();
	void SetDefault();
	void Update();
	void UpdateData(ST_PLAYER_POSITION stRecv, ST_SOCKET_ADDR stAddr);
	void UpdateData(ST_PLAYER_POSITION stRecv);
};

