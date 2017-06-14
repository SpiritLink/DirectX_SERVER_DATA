#pragma once
#include "stdafx.h"

#define g_pNetworkManager cNetworkManager::GetInstance()
class cNetworkManager
{
private:
	SINGLETONE(cNetworkManager);
	map<int, string>		 m_mapID;	// ID�� ���̸��� ��� �����մϴ�.
	map<string, vector<int>> m_mapRoom;	// ���̸��� ID�� ��� �����մϴ�.
public:
	void addID(int ID, string RoomName);
};

