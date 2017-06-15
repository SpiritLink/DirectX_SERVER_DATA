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
	void SetItem(int Index, int Type);
	void SetAngle(float Value);
	float GetAngle();
};

