#pragma once
#include "cPlayer.h"
#include "cStuff.h"
#define ONE_SECOND 1000

class cContainer
{
private:
	string	m_sRoomName;		// 방이름
	cPlayer m_cPlayer1;			// 플레이어 1 데이터
	cPlayer m_cPlayer2;			// 플레이어 2 데이터

	DWORD	m_dwPlayer1Time;	// 플레이어 1 최근 접속 시간
	DWORD	m_dwPlayer2Time;	// 플레이어 2 최근 접속 시간

	// << : 아이템에 대한 정보를 저장할 공간이 필요 (최대 아이템 개수 10개)
public:
	cContainer();
	~cContainer();

	void Setup(string key);
	void UpdateData(ST_PLAYER_POSITION stRecv);
	ST_PLAYER_POSITION GetData(int nIndex);
	int GetOnlineUser();
	void SaveData();
	void SetDefault();
};

