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

/* ������ �������� ������ ��ȯ�մϴ� */
int cPlayer::GetItem(int Index)
{
	if (Index >= INVENTORY_SIZE) return -1;
	return (int)Inventory[Index];
}

StuffCode* cPlayer::GetInventory()
{
	return Inventory;
}

/* �������� �����մϴ� */
void cPlayer::SetItem(int Index, int Type)
{
	if (Index >= INVENTORY_SIZE) return;

	Inventory[Index] = (StuffCode)Type;
}

void cPlayer::SetInventory(ST_INVENTORY_DATA stData)
{
	for (int i = 0; i < INVENTORY_SIZE; ++i)
	{
		Inventory[i] = stData.Stuff[i];
	}
}

/* ȸ������ �����մϴ� */
void cPlayer::SetAngle(float Value)
{
	fAngle = Value;
}

/* ȸ������ ��ȯ�մϴ� */
float cPlayer::GetAngle()
{
	return fAngle;
}
