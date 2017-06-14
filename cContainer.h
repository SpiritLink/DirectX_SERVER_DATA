#pragma once
#include "cPlayer.h"
#include "cStuff.h"
#define CONNECT_TIME 5

class cContainer
{
private:
	string	m_sRoomName;		// 방이름
	cPlayer m_cPlayer1;			// 플레이어 1 데이터
	cPlayer m_cPlayer2;			// 플레이어 2 데이터

	clock_t m_nPlayer1Time;	// 플레이어 1 최근 접속 시간
	clock_t m_nPlayer2Time;	// 플레이어 2 최근 접속 시간

	std::vector<cStuff> m_vecStuffPosition;	// << : 오브젝트

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

