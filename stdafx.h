// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <Windows.h>
#include <process.h>
#include <map>
#include <time.h>

#define MAX_CLNT 256
#define BUF_SIZE 100
#define CLIENT_NUM 5

using namespace std;



#define SINGLETONE(class_name) \
		private :	\
			class_name(void) ;	\
			~class_name(void) ;	\
		public :\
			static class_name* GetInstance()	\
			{	\
				static class_name instance ;	\
				return &instance;	\
			}

#define SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: inline varType Get##funName(void) const { return varName; }\
public: inline void Set##funName(varType var) { varName = var; }

// TODO: 프로그램에 필요한 구조체는 여기에서 참조합니다.
struct ST_PLAYER_POSITION
{
	char  szRoomName[50] = { 0, };
	int	  nFROM_SERVER;
	int   nFROM_CLIENT;
	int	  nPlayerIndex;
	float fX;
	float fY;
	float fZ;
	float fAngle;
	ST_PLAYER_POSITION() :nFROM_SERVER(0), nFROM_CLIENT(0), fX(0.0f), fY(0.0f), fZ(0.0f), fAngle(0.0f) {};
};

struct ST_SOCKET_POSITION
{
	SOCKET pSocket;
	char szRoomName[50] = { 0, };
	int  nPlayerIndex;
};

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include "cDataManager.h"
