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

/* 좌표를 설정합니다 */
void cObject::SetPosition(IN float x, IN float y, IN float z)
{
	fX = x;
	fY = y;
	fZ = z;
}

/* 좌표를 반환합니다 */
void cObject::GetPosition(OUT float* x, OUT float* y, OUT float* z)
{
	*x = fX;
	*y = fY;
	*z = fZ;
}

/* X좌표를 설정합니다 */
void cObject::SetX(IN float Value)
{
	fX = Value;
}

/* Y좌표를 설정합니다 */
void cObject::SetY(IN float Value)
{
	fY = Value;
}

/* Z좌표를 설정합니다 */
void cObject::SetZ(IN float Value)
{
	fZ = Value;
}