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
	// >> : 파일을 연뒤 해당하는 데이터를 적용
}

void cContainer::UpdateData(ST_PLAYER_POSITION stRecv)
{
	float x = stRecv.fX;
	float y = stRecv.fY;
	float z = stRecv.fZ;
	float Angle = stRecv.fAngle;

	if (stRecv.nPlayerIndex == 1)
	{
		m_cPlayer2.SetPosition(x, y, z, Angle);
		m_dwPlayer2Time = GetTickCount();
	}
	else
	{
		m_cPlayer1.SetPosition(x, y, z, Angle);
		m_dwPlayer1Time = GetTickCount();
	}
}

ST_PLAYER_POSITION cContainer::GetData(int nIndex)
{
	float x, y, z, Angle;
	if (nIndex == 1)
		m_cPlayer1.GetPosition(&x, &y, &z, &Angle);
	if (nIndex == 2)
		m_cPlayer2.GetPosition(&x, &y, &z, &Angle);
	ST_PLAYER_POSITION result(x, y, z, Angle);
	sprintf(result.szRoomName, "%s", "FROM SERVER");
	return result;
}

void cContainer::SaveData()
{
	// << : 폴더 없는 상황 예외처리
	string szFullPath = "Server/" + m_sRoomName + ".txt";
	ofstream outFile(szFullPath.data(), ios::trunc);
	if (!outFile.is_open())
	{
		char strFolderPath[] = "Server";
		int nResult = mkdir(strFolderPath);
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

