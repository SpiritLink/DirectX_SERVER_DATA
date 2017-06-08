#include "stdafx.h"
#include "cStuff.h"


cStuff::cStuff()
	: m_eType(STUFF_NONE)
	, IsRunning(false)
{
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
