#pragma once
#include "cObject.h"
class cPlayer : public cObject
{
protected:
	SYNTHESIZE(animationState, m_eAnimState, AnimState);
public:
	cPlayer();
	virtual ~cPlayer() override;
};

