#pragma once
#include "stdafx.h"

#define g_pDataManager	cDataManager::GetInstance()

class cContainer;

class cDataManager
{
private:
	SINGLETONE(cDataManager);
	map<string, cContainer*> m_mapContainer;
public:
	void Setup();
	void ReceiveSocket(ST_FLAG stFlag, ST_SOCKET_ADDR stSocket);
	ST_SOCKET_ADDR GetSocket(ST_FLAG stFlag);
	void ReceiveData(ST_PLAYER_POSITION stRecv, SOCKADDR_IN stAddr);
	ST_PLAYER_POSITION GetPlayerData(string key, int nIndex);
	void SaveAllData();
	void Update();
	void Destroy();
};

