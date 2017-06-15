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

int cPlayer::GetItem(int Index)
{
	if (Index >= INVENTORY_SIZE) return -1;
	return Inventory[Index];
}

void cPlayer::SetAngle(float Value)
{
	fAngle = Value;
}

float cPlayer::GetAngle()
{
	return fAngle;
}
