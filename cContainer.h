#pragma once
#include "cPlayer.h"
#include "cStuff.h"
#define CONNECT_TIME 5
#define D3DX_PI 3.141592654f

class cContainer
{
private:
	string	m_sRoomName;		// 방이름
	cPlayer m_stMan;			// 남자 데이터
	cPlayer m_stWoman;			// 여자 데이터

	clock_t m_nManTime;			// 남자 최근 접속 시간
	clock_t m_nWomanTime;		// 여자 최근 접속 시간

	cStuff m_aStuff[SWITCH_LASTNUM];	// << : 오브젝트
	ST_MAP_STATUS m_stMapStatus;		// << : 밸브 회전 상태
public:
	cContainer();
	~cContainer();

	ST_PLAYER_POSITION GetData(int nIndex);
	int GetOnlineUser();
	void GetManPosition(OUT float * x, OUT float * y, OUT float * z, OUT float * angle);
	void GetManInventory(OUT int * nArr);
	void GetWomanPosition(OUT float * x, OUT float * y, OUT float * z, OUT float * angle);
	void GetWomanInventory(OUT int * nArr);
	void GetStuff(OUT float* X, OUT float* Y, OUT float* Z, OUT float* rotX, OUT float* rotY, OUT float* rotZ, OUT bool* IsRun);
	ST_MAP_STATUS GetMapStatus();
	void Setup(string key);
	void SaveData();
	void SetDefault();
	void Update();
	void ReceivePosition(ST_PLAYER_POSITION stRecv);
	void ReceiveMap(ST_OBJECT_DATA stData);
};

