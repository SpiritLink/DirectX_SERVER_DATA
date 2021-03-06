#include "stdafx.h"
#include "cTimeManager.h"

cTimeManager::cTimeManager()
	: IsQuit(false)
	, SaveTimer(0)
	, ShowAllLog(false)
	, ShowThread(false)
{
	m_stTimer = time(NULL);				// 현재 시각을 초 단위로 얻습니다.
	localtime_s(&m_stT, &m_stTimer);	// 초 단위의 시간을 분리하여 구조체에 넣기
}


cTimeManager::~cTimeManager()
{
}

/* 현재 시간을 문자열로 반환합니다 */
string cTimeManager::GetLocalTime_String()
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

/* 현재 시간을 Unsigned int형으로 반환합니다 (구버전) */
unsigned int cTimeManager::GetLocalTime_UINT()
{
	m_stTimer = time(NULL);
	localtime_s(&m_stT, &m_stTimer);

	unsigned int Result = 0;
	Result += m_stT.tm_hour * MINUTE * SECOND;
	Result += m_stT.tm_min * SECOND;
	Result += m_stT.tm_sec;
	return Result;
}
