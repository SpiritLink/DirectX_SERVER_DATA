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

	unsigned int m_nPlayer1Time;	// 플레이어 1 최근 접속 시간
	unsigned int m_nPlayer2Time;	// 플레이어 2 최근 접속 시간

	std::vector<cStuff> m_vecStuffPosition;	// << : 오브젝트

	bool SwitchPlayer1;			// << : 플레이어 1 스위치
	bool SwitchPlayer2;			// << : 플레이어 2 스위치
public:
	cContainer();
	~cContainer();

	ST_PLAYER_POSITION GetData(int nIndex);
	int GetOnlineUser();
	void OnSwitch();
	void Setup(string key);
	void SaveData();
	void SetDefault();
	void UpdateData(ST_PLAYER_POSITION stRecv);
};

