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


void cObject::SetPosition(float x, float y, float z, float Angle)
{
	fX = x;
	fY = y;
	fZ = z;
	fAngle = Angle;
}
