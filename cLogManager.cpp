#include "stdafx.h"
#include "cLogManager.h"
#include "cContainer.h"

cLogManager::cLogManager()
{
}


cLogManager::~cLogManager()
{
}

void cLogManager::EnqueueLog(cContainer * pTarget)
{
	m_listRequest.push_back(pTarget);
}

void cLogManager::PROCESS_QUEUE()
{
	while (!m_listRequest.empty())	// << : 요청이 없을때까지 처리합니다.
	{
		cContainer* target = m_listRequest.front();	// << : 제일 먼저 들어온 요청을 처리합니다.
		m_listRequest.pop_front();
		target->SaveData();
	}
}

