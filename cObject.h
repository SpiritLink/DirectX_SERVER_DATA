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
	void SetPosition(IN float x, IN float y, IN float z, IN float Angle);
	void GetPosition(OUT float* x, OUT float* y, OUT float* z, OUT float* Angle);
};

