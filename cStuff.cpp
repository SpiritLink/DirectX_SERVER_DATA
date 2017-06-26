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

/* IsRunning (활성화 상태)을 변경합니다 */
void cStuff::SetIsRunning(bool Value)
{
	IsRunning = Value;
}

/* 회전값 (벡터)을 설정합니다 */
void cStuff::SetRotate(float x, float y, float z)
{
	RotateX = x;
	RotateY = y;
	RotateZ = z;
}

/* 회전값 (벡터)을 반환합니다 */
void cStuff::GetRotate(float * x, float * y, float * z)
{
	*x = RotateX;
	*y = RotateY;
	*z = RotateZ;
}

/* 활성화 상태 (IsRunning)를 반환합니다 */
bool cStuff::GetIsRunning()
{
	return IsRunning;
}

