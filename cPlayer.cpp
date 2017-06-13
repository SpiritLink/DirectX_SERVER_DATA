#include "stdafx.h"
#include "cPlayer.h"


cPlayer::cPlayer()
	: m_eAnimState(ANIM_IDLE)
{
}


cPlayer::~cPlayer()
{
}

void cPlayer::SetAngle(float Value)
{
	fAngle = Value;
}

float cPlayer::GetAngle()
{
	return fAngle;
}
