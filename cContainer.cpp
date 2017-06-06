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
}

