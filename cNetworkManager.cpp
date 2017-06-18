#include "stdafx.h"
#include "cNetworkManager.h"


cNetworkManager::cNetworkManager()
{
}


cNetworkManager::~cNetworkManager()
{
}

/* ��Ʈ��ũ ���̵� �ش��ϴ� ���̸��� ��� ����մϴ� */
void cNetworkManager::addID(int ID, string RoomName)
{
	if (m_mapRoom[RoomName].size() < MAXCLIENT_ROOM)	// << : �ο��� ���� �������� �����
	{
		m_mapID[ID] = RoomName;
		m_mapRoom[RoomName].push_back(ID);
	}
}

/* ��Ʈ��ũ ���̵� �ش��ϴ� IP�ּҸ� ��� ����մϴ� */
void cNetworkManager::addAddr(int ID, SOCKADDR_IN stAddr)
{
	m_mapAddr[ID] = stAddr;
	cout << "��ϵ� IP : " << inet_ntoa(stAddr.sin_addr) << endl;
}

/* �Ѱ��� ��(�����̳�)�� ����� �����ߴ��� Ȯ���ϴ� �Լ��Դϴ� */
int cNetworkManager::GetClntNum(string RoomName)
{
	return m_mapRoom[RoomName].size();
}

/* �ٸ� ������ ���� � ������ �����ߴ��� Ȯ���ϴ� �Լ��Դϴ�*/
void cNetworkManager::SendGender(string Key)
{
	vector<int> vecUser = m_mapRoom[Key];
	
	for (int i = 0; i < vecUser.size(); ++i)
	{
		m_mapSwitch[vecUser[i]] = 2;	// << : �����忡�� ������ ������� �ν��մϴ�.
	}
}

void cNetworkManager::Quit(int Id)
{
	map<int, string>		 m_mapID;	// ID�� ���̸��� ��� �����մϴ�.
	map<string, vector<int>> m_mapRoom;	// ���̸��� ID�� ��� �����մϴ�.
	string szTarget = m_mapID[Id];
	// 1. ���̵�� ���̸� ����
	// 2. ���̸����� ���̵� ����
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
}
