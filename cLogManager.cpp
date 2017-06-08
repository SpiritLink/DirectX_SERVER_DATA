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
	while (!m_listRequest.empty())	// << : ��û�� ���������� ó���մϴ�.
	{
		cContainer* target = m_listRequest.front();	// << : ���� ���� ���� ��û�� ó���մϴ�.
		m_listRequest.pop_front();
		target->SaveData();
	}
}

