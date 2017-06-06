#include "stdafx.h"
#include "cTimeManager.h"

cTimeManager::cTimeManager()
{
	m_stTimer = time(NULL);				// 현재 시각을 초 단위로 얻습니다.
	localtime_s(&m_stT, &m_stTimer);	// 초 단위의 시간을 분리하여 구조체에 넣기
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
