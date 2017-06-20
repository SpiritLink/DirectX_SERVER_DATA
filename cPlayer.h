#pragma once
#include "cObject.h"


class cPlayer : public cObject
{
protected:
	SYNTHESIZE(animationState, m_eAnimState, AnimState);
	float fAngle;	// << : Rotation
	StuffCode Inventory[INVENTORY_SIZE];
public:
	cPlayer();
	virtual ~cPlayer() override;
	int GetItem(int Index);
	StuffCode* GetInventory();
	void SetItem(int Index, int Type);
	void SetInventory(ST_INVENTORY_DATA stData);
	void SetAngle(float Value);
	float GetAngle();
};

