#pragma once
class cObject
{
protected:
	float fX;		// << : Position
	float fY;
	float fZ;
	float fAngleX;	// << : Rotation
	float fAngleY;
	float fAngleZ;
public:
	cObject();
	virtual ~cObject();
	void SetPosition(IN float x, IN float y, IN float z, IN float AngleX, IN float AngleY, IN float AngleZ);
	void GetPosition(OUT float* x, OUT float* y, OUT float* z, OUT float* AngleX, OUT float* AngleY, OUT float* AngleZ);
	void SetX(IN float Value);
	void SetY(IN float Value);
	void SetZ(IN float Value);
	void SetAngleX(IN float Value);
	void SetAngleY(IN float Value);
	void SetAngleZ(IN float Value);


};

