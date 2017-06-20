#pragma once
#include "stdafx.h"

#define g_pNetworkManager cNetworkManager::GetInstance()

class cNetworkManager
{
private:
	SINGLETONE(cNetworkManager);
	map<int, string>		 m_mapID;	// ID�� ���̸��� ��� �����մϴ�.
	map<string, vector<int>> m_mapRoom;	// ���̸��� ID�� ��� �����մϴ�.
	map<int, SOCKADDR_IN> m_mapAddr;	// ��Ʈ��ũ ���̵�� IP�ּҸ� ��� �����մϴ�.
	map<int, int>	m_mapGender;		// �÷��̾��� ������ �����մϴ�.
	map<int, int>	m_mapSwitch;		// �����尡 � �����͸� ������ ���� �����ϴ� �����Դϴ�.
public:
	void addID(int ID, string RoomName);
	void addAddr(int ID, SOCKADDR_IN stAddr);
	void AddFlag(int ID, FLAG eFlag);
	int GetClntNum(string RoomName);
	void SendGender(string Key);
	void SendObject(string Key);
	void SubFlag(int ID, FLAG eFlag);
	void Quit(int Id);
};

