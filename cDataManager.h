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
	void ReceiveData(ST_PLAYER_POSITION stRecv);
	ST_PLAYER_POSITION GetPlayerData(string key, int nIndex);
	void SaveAllData();
	void Destroy();
};

