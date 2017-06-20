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

/* 클라이언트의 IP주소를 네트워크 아이디에 맞춰 저장합니다 */
void cDataManager::ReceiveSocket(ST_FLAG stFlag, ST_SOCKET_ADDR stSocket)
{
	/* 공간 동적할당 */
	string key = string(stFlag.szRoomName);
	if (m_mapContainer[key] == NULL)
	{
		m_mapContainer[key] = new cContainer;
		m_mapContainer[key]->Setup(key);
	}
}

/* 플레이어의 좌표 정보를 컨테이너에 적용합니다 */
void cDataManager::ReceivePosition(ST_PLAYER_POSITION stRecv)
{
	WaitForSingleObject(g_hMutex_DATA, INFINITE);
	EnterCriticalSection(&cs);
	string key = string(stRecv.szRoomName);
	if (m_mapContainer[key] == NULL)
	{
		m_mapContainer[key] = new cContainer;
		m_mapContainer[key]->Setup(key);
	}
	m_mapContainer[key]->ReceivePosition(stRecv);
	cout << stRecv.nPlayerIndex << " ";
	cout << stRecv.fX << " ";
	cout << stRecv.fY << " ";
	cout << stRecv.fZ << " ";
	cout << stRecv.fAngle << endl;
	LeaveCriticalSection(&cs);
	ReleaseMutex(g_hMutex_DATA);
}

void cDataManager::ReceiveObject(string key, ST_OBJECT_DATA stObjectData)
{
	// << : 키를 통해 컨테이너에 접근하고 수신한 데이터를 적용합니다.
	WaitForSingleObject(g_hMutex_DATA, INFINITE);
	m_mapContainer[key]->ReceiveMap(stObjectData);
	ReleaseMutex(g_hMutex_DATA);

	//<< : 수신한 데이터를 전부 적용했으니 이제 해당하는 플레이어가 수신하게 해야함
}

/* 컨테이너에서 플레이어의 정보를 확인, 반환합니다 */
ST_PLAYER_POSITION cDataManager::GetPlayerData(string key, int nIndex)
{
	WaitForSingleObject(g_hMutex_DATA, INFINITE);
	ST_PLAYER_POSITION stResult;

	if (m_mapContainer[key] == NULL)
		return ST_PLAYER_POSITION();
	
	stResult.nPlayerIndex = 0;
	if (nIndex & IN_PLAYER1)
		stResult = m_mapContainer[key]->GetData(2);
	if(nIndex & IN_PLAYER2)
		stResult = m_mapContainer[key]->GetData(1);

	stResult.nPlayerIndex = m_mapContainer[key]->GetOnlineUser();
	ReleaseMutex(g_hMutex_DATA);
	return stResult;
	
}

ST_MAP_STATUS cDataManager::GetMapStatus(string key)
{
	return m_mapContainer[key]->GetMapStatus();
}

/* 남자 캐릭터의 정보를 얻어냅니다 */
void cDataManager::GetManPosition(IN string key, OUT float * x, OUT float * y, OUT float * z, OUT float * angle)
{
	WaitForSingleObject(g_hMutex_DATA, INFINITE);
	if (m_mapContainer[key] == NULL)
	{
		m_mapContainer[key] = new cContainer;
		m_mapContainer[key]->Setup(key);
	}
	m_mapContainer[key]->GetManPosition(x, y, z, angle);
	ReleaseMutex(g_hMutex_DATA);
}

void cDataManager::GetManInventory(IN string key, OUT int * arr)
{
	WaitForSingleObject(g_hMutex_DATA, INFINITE);
	if (m_mapContainer[key] == NULL)
	{
		m_mapContainer[key] = new cContainer;
		m_mapContainer[key]->Setup(key);
	}
	m_mapContainer[key]->GetManInventory(arr);
	ReleaseMutex(g_hMutex_DATA);
}

animationState cDataManager::GetManAnim(IN string key)
{
	return m_mapContainer[key]->GetManAnim();
}

/* 여자 캐릭터의 정보를 얻어냅니다 */
void cDataManager::GetWomanPosition(IN string key, OUT float * x, OUT float * y, OUT float * z, OUT float * angle)
{
	WaitForSingleObject(g_hMutex_DATA, INFINITE);
	if (m_mapContainer[key] == NULL)
	{
		m_mapContainer[key] = new cContainer;
		m_mapContainer[key]->Setup(key);
	}
	m_mapContainer[key]->GetWomanPosition(x, y, z, angle);
	ReleaseMutex(g_hMutex_DATA);
}

void cDataManager::GetWomanInventory(IN string key, OUT int * arr)
{
	WaitForSingleObject(g_hMutex_DATA, INFINITE);
	if (m_mapContainer[key] == NULL)
	{
		m_mapContainer[key] = new cContainer;
		m_mapContainer[key]->Setup(key);
	}
	m_mapContainer[key]->GetWomanInventory(arr);
	ReleaseMutex(g_hMutex_DATA);
}

animationState cDataManager::GetWomanAnim(IN string key)
{
	return m_mapContainer[key]->GetWomanAnim();
}

/* 맵의 정보를 얻어냅니다 */
void cDataManager::GetMapData(IN string key, OUT float * X, OUT float * Y, OUT float * Z, OUT float * rotX, OUT float * rotY, OUT float * rotZ, OUT bool * IsRun)
{
	m_mapContainer[key]->GetStuff(X, Y, Z, rotX, rotY, rotZ, IsRun);
}

/* 모든 컨테이너의 정보를 파일로 저장합니다 */
void cDataManager::SaveAllData()
{
	WaitForSingleObject(g_hMutex_DATA, INFINITE);
	map<string, cContainer*>::iterator iter;
	for (iter = m_mapContainer.begin(); iter != m_mapContainer.end(); ++iter)
	{
		iter->second->SaveData();	// << : SaveLog
	}
	ReleaseMutex(g_hMutex_DATA);
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
	WaitForSingleObject(g_hMutex_DATA, INFINITE);
	for each(auto p in m_mapContainer)
	{
		p.second->SaveData();
		SAFE_DELETE(p.second);
	}
	ReleaseMutex(g_hMutex_DATA);
}
