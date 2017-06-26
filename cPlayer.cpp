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

/* 인벤토리 정보를 반환합니다 */
StuffCode* cPlayer::GetInventory()
{
	return Inventory;
}

/* 인덱스에 맞춰 아이템을 설정합니다 */
void cPlayer::SetItem(int Index, int Type)
{
	if (Index >= INVENTORY_SIZE) return;

	Inventory[Index] = (StuffCode)Type;
}

/* 인벤토리 구조체의 정보를 플레이어 인벤토리에 적용합니다 */
void cPlayer::SetInventory(ST_INVENTORY_DATA stData)
{
	for (int i = 0; i < INVENTORY_SIZE; ++i)
	{
		Inventory[i] = stData.Stuff[i];
	}
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
