#pragma once
#include "cObject.h"

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
	void SetItemType(StuffCode eType);
	void SetIsRunning(bool Value);
	void SetRotate(float x, float y, float z);
	void GetRotate(float* x, float* y, float* z);
	bool GetIsRunning();
};


