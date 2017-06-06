#pragma once
#include "cPlayer.h"
#include "cStuff.h"

class cContainer
{
private:
	string	m_sRoomName;		// 방이름
	cPlayer m_cPlayer1;			// 플레이어 1 데이터
	cPlayer m_cPlayer2;			// 플레이어 2 데이터

	DWORD	m_dwPlayer1Time;	// 플레이어 1 최근 접속 시간
	DWORD	m_dwPlayer2Time;	// 플레이어 2 최근 접속 시간
public:
	cContainer();
	~cContainer();

	void Setup(string key);
	void UpdateData(ST_PLAYER_POSITION stRecv);
	ST_PLAYER_POSITION GetData(int nIndex);
	void SaveData();
};

