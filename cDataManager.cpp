#include "stdafx.h"
#include "cDataManager.h"
#include "cContainer.h"

cDataManager::cDataManager()
	:IsQuit(false)
{
}


cDataManager::~cDataManager()
{
}
void cDataManager::Setup()
{
}

void cDataManager::ReceiveData(ST_PLAYER_POSITION stRecv)
{
	string key = string(stRecv.szRoomName);
	if (m_mapContainer[key] == NULL)
	{
		m_mapContainer[key] = new cContainer;
		m_mapContainer[key]->Setup(key);
	}
	m_mapContainer[key]->UpdateData(stRecv);
}

ST_PLAYER_POSITION cDataManager::GetPlayerData(string key, int nIndex)
{
	ST_PLAYER_POSITION stResult;

	if (m_mapContainer[key] == NULL)
		return ST_PLAYER_POSITION();
	if (nIndex == 1)
	{
		stResult = m_mapContainer[key]->GetData(2);
		stResult.nPlayerIndex = 2;
	}
	if (nIndex == 2)
	{
		stResult = m_mapContainer[key]->GetData(1);
		stResult.nPlayerIndex = 1;
	}

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
