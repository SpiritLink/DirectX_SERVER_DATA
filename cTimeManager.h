#pragma once
#include "stdafx.h"

#define g_pTime cTimeManager::GetInstance()
#define MINUTE 60
#define SECOND 60

class cTimeManager
{
private:
	SINGLETONE(cTimeManager);
	time_t m_stTimer;
	struct tm m_stT;
	SYNTHESIZE(bool, IsQuit, Quit);
	SYNTHESIZE(unsigned int, SaveTimer, SaveTimer);
public:
	string GetLocalTime_String();
	unsigned int GetLocalTime_UINT();
};

