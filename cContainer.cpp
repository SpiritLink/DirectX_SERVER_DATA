#include "stdafx.h"
#include "cContainer.h"

cContainer::cContainer()
	: m_nPlayer1Time(0)
	, m_nPlayer2Time(0)
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
	if (!openFile.is_open())	// << : 파일이 열리지 않는 상황입니다.
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
		m_nPlayer1Time = g_pTime->GetLocalTime_UINT();
		break;
	case 2:
		m_cPlayer2.SetPosition(x, y, z, Angle);
		m_nPlayer2Time = g_pTime->GetLocalTime_UINT();
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

	// << : 해당 부분을 UINT로 변경해야 합니다. (time.h 이용 시간 변경)
	if (g_pTime->GetLocalTime_UINT() - m_nPlayer1Time < CONNECT_TIME)
		nResult = nResult | (1 << 4);
	if (g_pTime->GetLocalTime_UINT() - m_nPlayer2Time < CONNECT_TIME)
		nResult = nResult | (1 << 5);
		
	return nResult;
}

void cContainer::SaveData()
{
	// << : 폴더 없는 상황 예외처리
	string szFullPath = "Server/" + m_sRoomName + ".txt";
	ofstream outFile(szFullPath.data(), ios::trunc);
	if (!outFile.is_open())
	{
		char strFolderPath[] = "Server";
		int nResult = _mkdir(strFolderPath);
		if (nResult == 0)
			cout << "폴더 생성 성공" << endl;
		else if (nResult == -1)
		{
			perror("폴더 생성 실패 - 폴더가 이미 있거나 부정확함 \n");
			cout << "errorno :" << errno << endl;
		}
		outFile.open(szFullPath.data(), ios::trunc);
	}

	// << : 데이터 저장
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
