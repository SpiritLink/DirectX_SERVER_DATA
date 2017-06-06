// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
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

// TODO: ���α׷��� �ʿ��� ����ü�� ���⿡�� �����մϴ�.
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

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include "cDataManager.h"
