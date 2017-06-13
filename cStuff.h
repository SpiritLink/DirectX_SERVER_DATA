#pragma once
#include "cObject.h"

class cStuff : public cObject
{
protected:
	StuffCode	m_eType;
	bool		IsRunning;
	float RotateX;
	float RotateY;
	float RotateZ;
public:
	cStuff();
	virtual ~cStuff() override;
	void SetItemType(StuffCode eType);
	void SetIsRunning(bool Value);
};


