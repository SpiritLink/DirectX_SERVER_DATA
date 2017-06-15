#pragma once
#include "stdafx.h"

#define g_pDataManager	cDataManager::GetInstance()

class cContainer;
class cPlayer;
class cStuff;

class cDataManager
{
private:
	SINGLETONE(cDataManager);
	map<string, cContainer*> m_mapContainer;
public:
	void SaveAllData();
	void Setup();
	void ReceiveSocket(ST_FLAG stFlag, ST_SOCKET_ADDR stSocket);
	ST_SOCKET_ADDR GetSocket(ST_FLAG stFlag);
	void ReceiveData(ST_PLAYER_POSITION stRecv);
	void ReceiveData(ST_PLAYER_POSITION stRecv, SOCKADDR_IN stAddr);
	ST_PLAYER_POSITION GetPlayerData(string key, int nIndex);
	void GetManData(IN string key, OUT float * x, OUT float * y, OUT float * z, OUT float * angle);
	void GetWomanData(IN string key, OUT float * x, OUT float * y, OUT float * z, OUT float * angle);
	void GetMapData(IN string key, OUT cStuff* arrMap);
	void Update();
	void Destroy();
};

