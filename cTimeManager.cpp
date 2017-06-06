#include "stdafx.h"
#include "cTimeManager.h"

cTimeManager::cTimeManager()
{
	m_stTimer = time(NULL);				// ���� �ð��� �� ������ ����ϴ�.
	localtime_s(&m_stT, &m_stTimer);	// �� ������ �ð��� �и��Ͽ� ����ü�� �ֱ�
}


cTimeManager::~cTimeManager()
{
}

string cTimeManager::GetLocalTime()
{
	m_stTimer = time(NULL);
	localtime_s(&m_stT, &m_stTimer);

	std::string sTime;
	sTime = to_string(m_stT.tm_year + 1900) + "-"
		+	to_string(m_stT.tm_mon + 1) + "-"
		+	to_string(m_stT.tm_mday) + " "
		+	to_string(m_stT.tm_hour) + ":"
		+	to_string(m_stT.tm_min) + ":"
		+	to_string(m_stT.tm_sec);

	return sTime;
}
