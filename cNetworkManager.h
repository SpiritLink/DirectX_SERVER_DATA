#pragma once
#include "stdafx.h"

#define g_pNetworkManager cNetworkManager::GetInstance()

class cNetworkManager
{
private:
	SINGLETONE(cNetworkManager);
	map<int, string>		 m_mapID;	// ID와 방이름을 묶어서 관리합니다.
	map<string, vector<int>> m_mapRoom;	// 방이름과 ID를 묶어서 관리합니다.
	map<int, SOCKADDR_IN> m_mapAddr;	// 네트워크 아이디와 IP주소를 묶어서 관리합니다.
public:
	void addID(int ID, string RoomName);
	void addAddr(int ID, SOCKADDR_IN stAddr);
	int GetClntNum(string RoomName);
};

