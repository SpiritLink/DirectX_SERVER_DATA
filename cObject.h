#pragma once

/* 좌표에 대한 정보를 지닌 클래스 입니다 */
class cObject
{
protected:
	float fX;		// << : Position
	float fY;
	float fZ;
public:
	cObject();
	virtual ~cObject();
	void SetPosition(IN float x, IN float y, IN float z);
	void GetPosition(OUT float* x, OUT float* y, OUT float* z);
	void SetX(IN float Value);
	void SetY(IN float Value);
	void SetZ(IN float Value);
};

