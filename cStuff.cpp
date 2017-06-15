#include "stdafx.h"
#include "cStuff.h"


cStuff::cStuff()
	: IsRunning(false)
	, RotateX(0.0f)
	, RotateY(0.0f)
	, RotateZ(0.0f)
{
}


cStuff::~cStuff()
{
}

void cStuff::SetItemType(StuffCode eType)
{
}

void cStuff::SetIsRunning(bool Value)
{
	IsRunning = Value;
}

void cStuff::SetRotate(float x, float y, float z)
{
	RotateX = x;
	RotateY = y;
	RotateZ = z;
}

void cStuff::GetRotate(float * x, float * y, float * z)
{
	*x = RotateX;
	*y = RotateY;
	*z = RotateZ;
}

bool cStuff::GetIsRunning()
{
	return IsRunning;
}

