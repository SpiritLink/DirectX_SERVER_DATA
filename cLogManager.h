#pragma once
#include "stdafx.h"

#define g_pLog cLogManager::GetInstance()

class cLogManager
{
private:
	SINGLETONE(cLogManager);
	list<cContainer*> m_listRequest;
public:
	void EnqueueLog(cContainer* pTarget);
	void PROCESS_QUEUE();
};

