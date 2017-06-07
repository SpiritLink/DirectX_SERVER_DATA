#include "stdafx.h"
#include "cContainer.h"

cContainer::cContainer()
	: m_dwPlayer1Time(0)
	, m_dwPlayer2Time(0)
{
}


cContainer::~cContainer()
{
}

void cContainer::Setup(string key)
{
	m_sRoomName = key;
	// >> : ������ ���� �ش��ϴ� �����͸� ����
}

void cContainer::UpdateData(ST_PLAYER_POSITION stRecv)
{
	float x = stRecv.fX;
	float y = stRecv.fY;
	float z = stRecv.fZ;
	float AngleX = stRecv.fAngleX;
	float AngleY = stRecv.fAngleY;
	float AngleZ = stRecv.fAngleZ;

	if (stRecv.nPlayerIndex == 1)
	{
		m_cPlayer2.SetPosition(x, y, z, AngleX, AngleY, AngleZ);
		m_dwPlayer2Time = GetTickCount();
	}
	else
	{
		m_cPlayer1.SetPosition(x, y, z, AngleX, AngleY, AngleZ);
		m_dwPlayer1Time = GetTickCount();
	}
}

ST_PLAYER_POSITION cContainer::GetData(int nIndex)
{
	float x, y, z, AngleX, AngleY, AngleZ;
	if (nIndex == 1)
		m_cPlayer1.GetPosition(&x, &y, &z, &AngleX, &AngleY, &AngleZ);
	if (nIndex == 2)
		m_cPlayer2.GetPosition(&x, &y, &z, &AngleX, &AngleY, &AngleZ);
	ST_PLAYER_POSITION result(x, y, z, AngleX, AngleY, AngleZ);
	sprintf(result.szRoomName, "%s", "FROM SERVER");
	return result;
}

void cContainer::SaveData()
{
	// << : ���� ���� ��Ȳ ����ó��
	string szFullPath = "Server/" + m_sRoomName + ".txt";
	ofstream outFile(szFullPath.data(), ios::trunc);
	if (!outFile.is_open())
	{
		char strFolderPath[] = "Server";
		int nResult = mkdir(strFolderPath);
		if (nResult == 0)
			cout << "���� ���� ����" << endl;
		else if (nResult == -1)
		{
			perror("���� ���� ���� - ������ �̹� �ְų� ����Ȯ�� \n");
			cout << "errorno :" << errno << endl;
		}
		outFile.open(szFullPath.data(), ios::trunc);
	}

	// << : ������ ����
	float x, y, z, angleX, angleY, angleZ;

	outFile << m_sRoomName << endl;
	m_cPlayer1.GetPosition(&x, &y, &z, &angleX, &angleY, &angleZ);
	outFile << "Player1 X " << x << endl;
	outFile << "Player1 Y " << y << endl;
	outFile << "Player1 Z " << z << endl;
	outFile << "Player1 AngleX " << angleX << endl;
	outFile << "Player1 AngleY " << angleY << endl;
	outFile << "Player1 AngleZ " << angleZ << endl;

	m_cPlayer2.GetPosition(&x, &y, &z, &angleX, &angleY, &angleZ);
	outFile << "Player2 X " << x << endl;
	outFile << "Player2 Y " << y << endl;
	outFile << "Player2 Z " << z << endl;
	outFile << "Player2 AngleX " << angleX << endl;
	outFile << "Player2 AngleY " << angleY << endl;
	outFile << "Player2 AngleZ " << angleZ << endl;

	outFile.close();
}

