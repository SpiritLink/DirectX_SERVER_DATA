#pragma once
#include "cObject.h"

/* 물체에 대한 정보를 지닌 클래스입니다 cObject클래스를 상속합니다 */
class cStuff : public cObject
{
protected:
	bool  IsRunning;
	float RotateX;
	float RotateY;
	float RotateZ;
public:
	cStuff();
	virtual ~cStuff() override;
	void SetIsRunning(bool Value);
	void SetRotate(float x, float y, float z);
	void GetRotate(float* x, float* y, float* z);
	bool GetIsRunning();
};


