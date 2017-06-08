#include "stdafx.h"
#include "cStuff.h"


cStuff::cStuff()
	: IsRunning(false)
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
