#include "stdafx.h"
#include "cNetworkManager.h"


cNetworkManager::cNetworkManager()
{
}


cNetworkManager::~cNetworkManager()
{
}

/* 네트워크 아이디에 해당하는 방이름을 묶어서 등록합니다 */
void cNetworkManager::addID(int ID, string RoomName)
{
	WaitForSingleObject(g_hMutex_Net, INFINITE);
	if (m_mapRoom[RoomName].size() < MAXCLIENT_ROOM)	// << : 인원을 넘지 않을때만 등록함
	{
		m_mapID[ID] = RoomName;
		m_mapRoom[RoomName].push_back(ID);
	}
	ReleaseMutex(g_hMutex_Net);
}

/* 네트워크 아이디에 해당하는 IP주소를 묶어서 등록합니다 */
void cNetworkManager::addAddr(int ID, SOCKADDR_IN stAddr)
{
	WaitForSingleObject(g_hMutex_Net, INFINITE);
	m_mapAddr[ID] = stAddr;
	cout << "등록된 IP : " << inet_ntoa(stAddr.sin_addr) << endl;
	ReleaseMutex(g_hMutex_Net);
}

/* 한개의 방(컨테이너)에 몇명이 접속했는지 확인하는 함수입니다 */
int cNetworkManager::GetClntNum(string RoomName)
{
	return m_mapRoom[RoomName].size();
}

/* 다른 유저가 현재 어떤 성별을 선택했는지 확인하는 함수입니다*/
void cNetworkManager::SendGender(string Key)
{
	WaitForSingleObject(g_hMutex_Net, INFINITE);
	vector<int> vecUser = m_mapRoom[Key];
	
	for (int i = 0; i < vecUser.size(); ++i)
	{
		m_mapSwitch[vecUser[i]] = 2;	// << : 스레드에서 성별을 보내라로 인식합니다.
	}
	ReleaseMutex(g_hMutex_Net);
}

void cNetworkManager::Quit(int Id)
{
	WaitForSingleObject(g_hMutex_Net, INFINITE);
	string szTarget = m_mapID[Id];
	// 1. 아이디와 방이름 제거
	// 2. 방이름에서 아이디 제거
	{
		map<int, string>::iterator Iter;
		for (Iter = m_mapID.begin(); Iter != m_mapID.end();)
		{
			if (Iter->first == Id)
				m_mapID.erase(Iter++);
			else
				++Iter;
		}
	}
	{
		for (int i = 0; i < m_mapRoom[szTarget].size();)
		{
			if (m_mapRoom[szTarget][i] == Id)
				m_mapRoom[szTarget].erase(m_mapRoom[szTarget].begin() + i);
			else
				i++;
		}
	}
	ReleaseMutex(g_hMutex_Net);
}
