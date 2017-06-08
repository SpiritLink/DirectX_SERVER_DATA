#pragma once
#include "cObject.h"

class cStuff : public cObject
{
protected:
	StuffCode	m_eType;
	bool		IsRunning;
public:
	cStuff();
	virtual ~cStuff() override;
	void SetItemType(StuffCode eType);
	void SetIsRunning(bool Value);
};


