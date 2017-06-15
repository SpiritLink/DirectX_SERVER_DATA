#include "stdafx.h"
#include "cPlayer.h"


cPlayer::cPlayer()
	: m_eAnimState(ANIM_IDLE)
{
	for (int i = 0; i < INVENTORY_SIZE; ++i)
		Inventory[i] = STUFF_NONE;
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
