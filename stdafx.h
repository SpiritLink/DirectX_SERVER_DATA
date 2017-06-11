// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "targetver.h"

#include <direct.h>
#include <errno.h>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <process.h>
#include <stdio.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <time.h>
#include <WinSock2.h>
#include <Windows.h>

#define MAX_CLNT 256
#define BUF_SIZE 100
#define CLIENT_NUM 5
#define IN_PLAYER1 1 << 4
#define IN_PLAYER2 1 << 5
#define OUT_PLAYER1 1 << 0
#define OUT_PLAYER2 1 << 1

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

#define SAFE_DELETE(p) {if(p) delete p; p = NULL;}

// TODO: ���α׷��� �ʿ��� ����ü�� ���⿡�� �����մϴ�.
struct ST_PLAYER_POSITION
{
	// << : 
	char  szRoomName[50] = { 0, };	// << : Key
	int	  nFROM_SERVER;				// << : SERVER FLAG
	int   nFROM_CLIENT;				// << : CLIENT FLAG
	int	  nPlayerIndex;				// << : Current Player Index
	float fX;						
	float fY;
	float fZ;
	float fAngle;
	ST_PLAYER_POSITION() :nFROM_SERVER(0), nFROM_CLIENT(0), fX(0.0f), fY(0.0f), fZ(0.0f), fAngle(0.0f) {};
	ST_PLAYER_POSITION(float x, float y, float z, float angle) { fX = x, fY = y, fZ = z, fAngle = angle; };
};
enum StuffCode
{
	STUFF_NONE,
	STUFF_BOARDBLOCK,
	STUFF_BOX1,
	STUFF_BRICK,
	STUFF_BRICKPILE,

	STUFF_CHEST2,
	STUFF_CHEST3,
	STUFF_CROWBAR,
	STUFF_DOOR1,
	STUFF_EMPTYBOX,
	STUFF_KEY1,
	STUFF_KEY2,
	STUFF_KEY3,
	STUFF_KEY4,
	STUFF_KEY5,
	STUFF_NOTE4,
	STUFF_PAPER1,
	STUFF_PAPER2,
	STUFF_PAPER3,
	STUFF_POSTER1,
	STUFF_POSTER2,
	STUFF_POSTER3,
	STUFF_POSTER4,
	STUFF_ROCK1,
	STUFF_ROCK2,
	STUFF_VALVE1,
	STUFF_WOOD1,
	STUFF_WOOD2,
	STUFF_WOOD3,
	STUFF_WOODBOARD1,
	STUFF_WOODBOARD2
};

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include "cDataManager.h"
#include "cTimeManager.h"

extern int g_nThreadCount;