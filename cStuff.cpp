#include "stdafx.h"
#include "cStuff.h"


cStuff::cStuff()
	: m_eType(STUFF_NONE)
	, IsRunning(false)
	, RotateX(0.0f)
	, RotateY(0.0f)
	, RotateZ(0.0f)
{
	m_eType = STUFF_NONE;
}


cStuff::~cStuff()
{
}

void cStuff::SetItemType(StuffCode eType)
{
	m_eType = eType;
}

void cStuff::SetIsRunning(bool Value)
{
	IsRunning = Value;
}
