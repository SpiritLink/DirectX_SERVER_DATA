#pragma once
class cObject
{
protected:
	float fX;
	float fY;
	float fZ;
	float fAngle;
public:
	cObject();
	virtual ~cObject();
	virtual void SetPosition(float x, float y, float z, float Angle);
};

