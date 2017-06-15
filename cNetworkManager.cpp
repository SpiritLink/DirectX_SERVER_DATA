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
	if (m_mapRoom[RoomName].size() < MAXCLIENT_ROOM)	// << : 인원을 넘지 않을때만 등록함
	{
		m_mapID[ID] = RoomName;
		m_mapRoom[RoomName].push_back(ID);
	}
}
void cNetworkManager::addAddr(int ID, SOCKADDR_IN stAddr)
{
	m_mapAddr[ID] = stAddr;
	cout << "등록된 IP : " << inet_ntoa(stAddr.sin_addr) << endl;
}

int cNetworkManager::GetClntNum(string RoomName)
{
	return m_mapRoom[RoomName].size();
}
