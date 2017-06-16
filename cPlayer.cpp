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

/* 소지한 아이템의 정보를 반환합니다 */
int cPlayer::GetItem(int Index)
{
	if (Index >= INVENTORY_SIZE) return -1;
	return (int)Inventory[Index];
}

/* 아이템을 설정합니다 */
void cPlayer::SetItem(int Index, int Type)
{
	if (Index >= INVENTORY_SIZE) return;

	Inventory[Index] = (StuffCode)Type;
}

/* 회전값을 설정합니다 */
void cPlayer::SetAngle(float Value)
{
	fAngle = Value;
}

/* 회전값을 반환합니다 */
float cPlayer::GetAngle()
{
	return fAngle;
}
