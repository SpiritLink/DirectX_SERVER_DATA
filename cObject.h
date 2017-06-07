#pragma once
class cObject
{
protected:
	float fX;
	float fY;
	float fZ;
	float fAngleX;
	float fAngleY;
	float fAngleZ;
public:
	cObject();
	virtual ~cObject();
	void SetPosition(IN float x, IN float y, IN float z, IN float AngleX, IN float AngleY, IN float AngleZ);
	void GetPosition(OUT float* x, OUT float* y, OUT float* z, OUT float* AngleX, OUT float* AngleY, OUT float* AngleZ);
};

