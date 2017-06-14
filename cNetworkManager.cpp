#include "stdafx.h"
#include "cNetworkManager.h"


cNetworkManager::cNetworkManager()
{
}


cNetworkManager::~cNetworkManager()
{
}

void cNetworkManager::addID(int ID, string RoomName)
{
	m_mapID[ID] = RoomName;
}
