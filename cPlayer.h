#pragma once
#include "cObject.h"
class cPlayer : public cObject
{
protected:
	SYNTHESIZE(animationState, m_eAnimState, AnimState);
	float fAngle;	// << : Rotation
public:
	cPlayer();
	virtual ~cPlayer() override;
	void SetAngle(float Value);
	float GetAngle();
};

