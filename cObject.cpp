#include "stdafx.h"
#include "cObject.h"


cObject::cObject()
	: fX(0.0f)
	, fY(0.0f)
	, fZ(0.0f)
	, fAngle(0.0f)
{
}


cObject::~cObject()
{
}


void cObject::SetPosition(IN float x, IN float y, IN float z, IN float Angle)
{
	fX = x;
	fY = y;
	fZ = z;
	fAngle = Angle;
}

void cObject::GetPosition(OUT float* x, OUT float* y, OUT float* z, OUT float* Angle)
{
	*x = fX;
	*y = fY;
	*z = fZ;
	*Angle = fAngle;
}

