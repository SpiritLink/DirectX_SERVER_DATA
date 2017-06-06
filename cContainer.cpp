#include "stdafx.h"
#include "cContainer.h"
#include "cPlayer.h"
#include "cStuff.h"
#include "cObject.h"

cContainer::cContainer()
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


void cContainer::SaveData()
{
}

