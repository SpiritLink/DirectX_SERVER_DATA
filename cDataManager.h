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
	void ReceivePosition(ST_PLAYER_POSITION stRecv);
	void ReceiveObject(string key, ST_OBJECT_DATA stObjectData);
	ST_PLAYER_POSITION GetPlayerData(string key, int nIndex);
	ST_MAP_STATUS GetMapStatus(string key);
	void GetManPosition(IN string key, OUT float * x, OUT float * y, OUT float * z, OUT float * angle);
	void GetManInventory(IN string key, OUT int * arr);
	void GetWomanPosition(IN string key, OUT float * x, OUT float * y, OUT float * z, OUT float * angle);
	void GetWomanInventory(IN string key, OUT int * arr);
	void GetMapData(IN string key, OUT float* X, OUT float* Y, OUT float* Z, OUT float* rotX, OUT float* rotY, OUT float* rotZ, OUT bool* IsRun);
	void Update();
	void Destroy();
};

