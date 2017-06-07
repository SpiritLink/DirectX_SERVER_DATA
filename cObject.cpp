#include "stdafx.h"
#include "cObject.h"


cObject::cObject()
	: fX(0.0f)
	, fY(0.0f)
	, fZ(0.0f)
	, fAngleX(0.0f)
	, fAngleY(0.0f)
	, fAngleZ(0.0f)
{
}


cObject::~cObject()
{
}


void cObject::SetPosition(IN float x, IN float y, IN float z, IN float AngleX, IN float AngleY, IN float AngleZ)
{
	fX = x;
	fY = y;
	fZ = z;
	fAngleX = AngleX;
	fAngleY = AngleY;
	fAngleZ = AngleZ;
}

void cObject::GetPosition(OUT float* x, OUT float* y, OUT float* z, OUT float* AngleX, OUT float* AngleY, OUT float* AngleZ)
{
	*x = fX;
	*y = fY;
	*z = fZ;
	*AngleX = fAngleX;
	*AngleY = fAngleY;
	*AngleZ = fAngleZ;
}

