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
	if (m_mapContainer[key] == NULL)
		return ST_PLAYER_POSITION();

	return ST_PLAYER_POSITION();
}
