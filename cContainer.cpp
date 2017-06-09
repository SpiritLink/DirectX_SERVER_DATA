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
	string szFullPath = "Server/" + key + ".txt";
	char szBuffer[1000];

	char first[100] = { 0, };
	char second[100] = { 0, };
	float third;

	fstream openFile(szFullPath.data());
	if (!openFile.is_open())	// << : ������ ������ �ʴ� ��Ȳ�Դϴ�.
	{
		SetDefault();
		return;
	}

	while (!openFile.eof())		// << : Parsing Data
	{
		cPlayer* pTarget = NULL;
		openFile.getline(szBuffer, 1000);
		sscanf(szBuffer, "%s %s %f", &first, &second, &third);
		if (string(first) == "player1")
			pTarget = &m_cPlayer1;
		if (string(first) == "player2")
			pTarget = &m_cPlayer2;

		if (pTarget == NULL) continue;		
		
		if (string(second) == "X")		
			pTarget->SetX(third);
		else if (string(second) == "Y")
			pTarget->SetY(third);
		else if (string(second) == "Z")
			pTarget->SetZ(third);
		else if (string(second) == "Angle")
			pTarget->SetAngle(third);
	}
}

void cContainer::UpdateData(ST_PLAYER_POSITION stRecv)
{
	float x = stRecv.fX;
	float y = stRecv.fY;
	float z = stRecv.fZ;
	float Angle = stRecv.fAngle;

	switch (stRecv.nPlayerIndex)
	{
	case 1:
		m_cPlayer1.SetPosition(x, y, z, Angle);
		m_dwPlayer1Time = GetTickCount();
		break;
	case 2:
		m_cPlayer2.SetPosition(x, y, z, Angle);
		m_dwPlayer2Time = GetTickCount();
		break;
	default:
		// << : ���� �����ϴ� �κ��� �����ϴ�.
		break;
	}
}

ST_PLAYER_POSITION cContainer::GetData(int nIndex)
{
	float x, y, z, Angle;
	if (nIndex == 1)
		m_cPlayer2.GetPosition(&x, &y, &z, &Angle);
	if (nIndex == 2)
		m_cPlayer1.GetPosition(&x, &y, &z, &Angle);
	ST_PLAYER_POSITION result(x, y, z, Angle);
	sprintf_s(result.szRoomName, "%s", "FROM SERVER",11);
	return result;
}

int cContainer::GetOnlineUser()
{
	int nResult = 0;

	if (GetTickCount() - m_dwPlayer1Time < ONE_SECOND)	// << 1�÷��̾ 1�ʾȿ� ���� �Ǿ����ٸ�
	{
		nResult = nResult | (1 << 0);
	}

	if (GetTickCount() - m_dwPlayer2Time < ONE_SECOND)	// << 2�÷��̾ 1�ʾȿ� ���� �Ǿ����ٸ�
	{
		nResult = nResult | (1 << 1);
	}

	cout << nResult << endl;
		
	return nResult;
}

void cContainer::SaveData()
{
	// << : ���� ���� ��Ȳ ����ó��
	string szFullPath = "Server/" + m_sRoomName + ".txt";
	ofstream outFile(szFullPath.data(), ios::trunc);
	if (!outFile.is_open())
	{
		char strFolderPath[] = "Server";
		int nResult = _mkdir(strFolderPath);
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
	float x, y, z, angle;

	outFile << m_sRoomName << endl;
	m_cPlayer1.GetPosition(&x, &y, &z, &angle);
	outFile << "Player1 X " << x << endl;
	outFile << "Player1 Y " << y << endl;
	outFile << "Player1 Z " << z << endl;
	outFile << "Player1 Angle " << angle << endl;

	m_cPlayer2.GetPosition(&x, &y, &z, &angle);
	outFile << "Player2 X " << x << endl;
	outFile << "Player2 Y " << y << endl;
	outFile << "Player2 Z " << z << endl;
	outFile << "Player2 Angle " << angle << endl;

	outFile.close();
}

void cContainer::SetDefault()
{
	m_cPlayer1.SetX(0);
	m_cPlayer1.SetY(0);
	m_cPlayer1.SetZ(0);
	m_cPlayer1.SetAngle(0);

	m_cPlayer2.SetX(0);
	m_cPlayer2.SetY(0);
	m_cPlayer2.SetZ(0);
	m_cPlayer2.SetAngle(0);
}
