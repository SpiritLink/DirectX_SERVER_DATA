#pragma once
#include "stdafx.h"

#define g_pDataManager	cDataManager::GetInstance()

class cContainer;

class cDataManager
{
private:
	SINGLETONE(cDataManager);
	map<string, cContainer*> m_mapContainer;
	SYNTHESIZE(bool, Option1, Option1);
	SYNTHESIZE(bool, Option2, Option2);
	SYNTHESIZE(bool, Option3, Option3);
public:
	SYNTHESIZE(bool, IsQuit, Quit);

	void Setup();
	void ReceiveData(ST_PLAYER_POSITION stRecv);
	ST_PLAYER_POSITION GetPlayerData(string key, int nIndex);
	void SaveAllData();
	void Destroy();
};

