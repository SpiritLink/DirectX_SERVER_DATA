#pragma once
class cObject
{
protected:
	float fX;		// << : Position
	float fY;
	float fZ;
	float fAngle;	// << : Rotation
public:
	cObject();
	virtual ~cObject();
	void SetPosition(IN float x, IN float y, IN float z, IN float Angle);
	void GetPosition(OUT float* x, OUT float* y, OUT float* z, OUT float* Angle);
	void SetX(IN float Value);
	void SetY(IN float Value);
	void SetZ(IN float Value);
	void SetAngle(IN float Value);


};

