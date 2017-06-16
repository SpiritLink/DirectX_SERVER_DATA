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

/* �������� �����մϴ� */
void cPlayer::SetItem(int Index, int Type)
{
	if (Index >= INVENTORY_SIZE) return;

	Inventory[Index] = (StuffCode)Type;
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
