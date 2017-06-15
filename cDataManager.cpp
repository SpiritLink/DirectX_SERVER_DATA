#include "stdafx.h"
#include "cDataManager.h"
#include "cContainer.h"
#include "cPlayer.h"
#include "cStuff.h"

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

void cDataManager::ReceiveSocket(ST_FLAG stFlag, ST_SOCKET_ADDR stSocket)
{
	/* 공간 동적할당 */
	string key = string(stFlag.szRoomName);
	if (m_mapContainer[key] == NULL)
	{
		m_mapContainer[key] = new cContainer;
		m_mapContainer[key]->Setup(key);
	}

	/* 클라이언트 정보 저장 */
	if (stFlag.nPlayerIndex & IN_PLAYER1)
		m_mapContainer[key]->SetPlayer1Sock(stSocket);
	else if (stFlag.nPlayerIndex & IN_PLAYER2)
		m_mapContainer[key]->SetPlayer2Sock(stSocket);
}

ST_SOCKET_ADDR cDataManager::GetSocket(ST_FLAG stFlag)
{
	if (stFlag.nPlayerIndex == 1)
		return g_pDataManager->m_mapContainer[string(stFlag.szRoomName)]->GetPlayer2Sock();
	else if(stFlag.nPlayerIndex == 2)
		return g_pDataManager->m_mapContainer[string(stFlag.szRoomName)]->GetPlayer1Sock();

	return ST_SOCKET_ADDR();
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
	cout << stRecv.nPlayerIndex << " ";
	cout << stRecv.fX << " ";
	cout << stRecv.fY << " ";
	cout << stRecv.fZ << " ";
	cout << stRecv.fAngle << endl;
	LeaveCriticalSection(&cs);
}

void cDataManager::ReceiveData(ST_PLAYER_POSITION stRecv,SOCKADDR_IN stAddr)
{
	EnterCriticalSection(&cs);
	string key = string(stRecv.szRoomName);
	if (m_mapContainer[key] == NULL)
	{
		m_mapContainer[key] = new cContainer;
		m_mapContainer[key]->Setup(key);
	}
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
	return stResult;
}

void cDataManager::GetManData(IN string key, OUT float * x, OUT float * y, OUT float * z, OUT float * angle)
{
	m_mapContainer[key]->GetManPosition(x, y, z, angle);
}

void cDataManager::GetWomanData(IN string key, OUT float * x, OUT float * y, OUT float * z, OUT float * angle)
{
	m_mapContainer[key]->GetWomanPosition(x, y, z, angle);
}

void cDataManager::GetMapData(IN string key, OUT float * X, OUT float * Y, OUT float * Z, OUT float * rotX, OUT float * rotY, OUT float * rotZ, OUT bool * IsRun)
{
	
}

void cDataManager::SaveAllData()
{
	map<string, cContainer*>::iterator iter;
	for (iter = m_mapContainer.begin(); iter != m_mapContainer.end(); ++iter)
	{
		iter->second->SaveData();	// << : SaveLog
	}
}

void cDataManager::Update()
{
	for each(auto p in m_mapContainer)
	{
		p.second->Update();
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
