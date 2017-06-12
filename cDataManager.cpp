#include "stdafx.h"
#include "cDataManager.h"
#include "cContainer.h"
CRITICAL_SECTION cs;

cDataManager::cDataManager()
{
}


cDataManager::~cDataManager()
{
}
void cDataManager::Setup()
{
	InitializeCriticalSection(&cs);
}

void cDataManager::ReceiveData(ST_PLAYER_POSITION stRecv)
{
	EnterCriticalSection(&cs);
	string key = string(stRecv.szRoomName);
	if (m_mapContainer[key] == NULL)
	{
		m_mapContainer[key] = new cContainer;
		m_mapContainer[key]->Setup(key);
	}
	m_mapContainer[key]->UpdateData(stRecv);
	LeaveCriticalSection(&cs);
}

ST_PLAYER_POSITION cDataManager::GetPlayerData(string key, int nIndex)
{
	ST_PLAYER_POSITION stResult;

	if (m_mapContainer[key] == NULL)
		return ST_PLAYER_POSITION();
	
	stResult.nPlayerIndex = 0;
	if (nIndex & IN_PLAYER1)
		stResult = m_mapContainer[key]->GetData(2);
	if(nIndex & IN_PLAYER2)
		stResult = m_mapContainer[key]->GetData(1);

	stResult.nPlayerIndex = m_mapContainer[key]->GetOnlineUser();
	stResult.nFROM_CLIENT = 0;
	stResult.nFROM_SERVER = 0;
	return stResult;
}
void cDataManager::SaveAllData()
{
	map<string, cContainer*>::iterator iter;
	for (iter = m_mapContainer.begin(); iter != m_mapContainer.end(); ++iter)
	{
		iter->second->SaveData();	// << : SaveLog
	}
}

void cDataManager::Destroy()
{
	for each(auto p in m_mapContainer)
	{
		p.second->SaveData();
		SAFE_DELETE(p.second);
	}
}
