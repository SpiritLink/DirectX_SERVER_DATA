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
	if (m_mapRoom[RoomName].size() < MAXCLIENT_ROOM)	// << : �ο��� ���� �������� �����
	{
		m_mapID[ID] = RoomName;
		m_mapRoom[RoomName].push_back(ID);
	}
}
void cNetworkManager::addAddr(int ID, SOCKADDR_IN stAddr)
{
	m_mapAddr[ID] = stAddr;
	cout << "��ϵ� IP : " << inet_ntoa(stAddr.sin_addr) << endl;
}

int cNetworkManager::GetClntNum(string RoomName)
{
	return m_mapRoom[RoomName].size();
}
