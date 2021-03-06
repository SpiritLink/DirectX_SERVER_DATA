#pragma once
#include "stdafx.h"

#define g_pNetworkManager cNetworkManager::GetInstance()

/* 클라이언트의 IP 및 Switch(FLAG) 를 관리합니다*/
class cNetworkManager
{
private:
	SINGLETONE(cNetworkManager);
	map<int, string>		 m_mapID;	// ID와 방이름을 묶어서 관리합니다.
	map<string, vector<int>> m_mapRoom;	// 방이름과 ID를 묶어서 관리합니다.
	map<int, SOCKADDR_IN> m_mapAddr;	// 네트워크 아이디와 IP주소를 묶어서 관리합니다.
	map<int, int>	m_mapGender;		// 플레이어의 성별을 관리합니다.
	map<int, int>	m_mapSwitch;		// 스레드가 어떤 데이터를 보내야 할지 구분하는 변수입니다.
	map<int, bool>	m_mapDisconnect;	// 연결이 종료된 아이디들을 저장합니다.
public:
	void addID(int ID, string RoomName);
	void addAddr(int ID, SOCKADDR_IN stAddr);
	void AddFlag(int ID, FLAG eFlag);
	int GetClntNum(string RoomName);
	void SendGender(string Key);
	void SendPosition(int nNetworkID);
	void SendObject(string Key);
	void SendObject(int ID);
	void SendInventory(int ID);
	void SubFlag(int ID, FLAG eFlag);
	void Quit(int Id);
};

