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

/* IsRunning (Ȱ��ȭ ����)�� �����մϴ� */
void cStuff::SetIsRunning(bool Value)
{
	IsRunning = Value;
}

/* ȸ���� (����)�� �����մϴ� */
void cStuff::SetRotate(float x, float y, float z)
{
	RotateX = x;
	RotateY = y;
	RotateZ = z;
}

/* ȸ���� (����)�� ��ȯ�մϴ� */
void cStuff::GetRotate(float * x, float * y, float * z)
{
	*x = RotateX;
	*y = RotateY;
	*z = RotateZ;
}

/* Ȱ��ȭ ���� (IsRunning)�� ��ȯ�մϴ� */
bool cStuff::GetIsRunning()
{
	return IsRunning;
}

