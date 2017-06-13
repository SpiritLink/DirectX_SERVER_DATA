#include "stdafx.h"
#include "cObject.h"


cObject::cObject()
	: fX(0.0f)
	, fY(0.0f)
	, fZ(0.0f)
{
}


cObject::~cObject()
{
}


void cObject::SetPosition(IN float x, IN float y, IN float z)
{
	fX = x;
	fY = y;
	fZ = z;
}

void cObject::GetPosition(OUT float* x, OUT float* y, OUT float* z)
{
	*x = fX;
	*y = fY;
	*z = fZ;
}

void cObject::SetX(IN float Value)
{
	fX = Value;
}

void cObject::SetY(IN float Value)
{
	fY = Value;
}

void cObject::SetZ(IN float Value)
{
	fZ = Value;
}