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
