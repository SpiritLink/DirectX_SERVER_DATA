// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
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
#include <vector>
#include <WinSock2.h>
#include <Windows.h>

#define MAX_CLNT 256
#define BUF_SIZE 100
#define CLIENT_NUM 5
#define IN_PLAYER1 1 << 4
#define IN_PLAYER2 1 << 5
#define INVENTORY_SIZE 25
#define OUT_PLAYER1 1 << 0
#define OUT_PLAYER2 1 << 1
#define ONE_SECOND 1000
#define MAXCLIENT_ROOM 2

#define PORT_DATA_IN 1234
#define PORT_DATA_OUT 1235
#define WAIT_MILLISECOND 5000
#define ONE_SECOND 1000

#define WOMAN "Woman"
#define MAN "Man"
#define STUFF "Stuff"
#define POSITION "Pos"
#define ROTATION "Rot"
#define ISRUNNING "IsRun"
#define INVENTORY_INDEX "InvenIDX"
#define STUFF_INDEX "StuffIDX"

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

// TODO: 프로그램에 필요한 구조체는 여기에서 참조합니다.
enum animationState
{
	ANIM_IDLE,
	ANIM_WALK,
	ANIM_ATTACK,
	ANIM_DEATH,
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

enum SwitchInfo
{
	SWITCH_STARTNUM,

	SWITCH_ONMAP_CROWBAR,
	SWITCH_ONMAP_PAPER1,
	SWITCH_ONMAP_PAPER2,
	SWITCH_ONMAP_PAPER3,
	SWITCH_ONMAP_KEY1,
	SWITCH_ONMAP_KEY2,
	SWITCH_ONMAP_KEY3,
	SWITCH_ONMAP_KEY4,
	SWITCH_ONMAP_KEY5,
	SWITCH_ONMAP_BRICK1,
	SWITCH_ONMAP_BRICK2,
	SWITCH_ONMAP_BRICK3,
	SWITCH_ONMAP_BRICK4,
	SWITCH_ONMAP_BRICK5,

	SWITCH_BASEMENT_BOX1,
	SWITCH_BASEMENT_CHEST,
	SWITCH_FIRSTFLOOR_TRAP,
	SWITCH_FIRSTFLOOR_WOODBOARD1,
	SWITCH_FIRSTFLOOR_WOODBOARD2,
	SWITCH_FIRSTFLOOR_BLOCK,
	SWITCH_SECONDFLOOR_VALVE1,
	SWITCH_SECONDFLOOR_VALVE2,
	SWITCH_SECONDFLOOR_BUTTON1,
	SWITCH_SECONDFLOOR_BUTTON2,

	SWITCH_DOOR_PRISON,
	SWITCH_DOOR_1STROOM,
	SWITCH_DOOR_1STTOILET,
	SWITCH_DOOR_2NDROOM1,
	SWITCH_DOOR_2NDROOM2,

	SWITCH_LASTNUM
};

enum FLAG
{
	FLAG_NONE = 1 << 0,
	FLAG_NETWORK_ID = 1 << 1,
	FLAG_ROOM_NAME = 1 << 2,
	FLAG_ALL_DATA = 1 << 3,
	FLAG_GENDER = 1 << 4,
	FLAG_POSITION = 1 << 5,
	FLAG_OBJECT_DATA = 1 << 6
};

struct ST_FLAG
{
	char szRoomName[50] = { 0, };
	int nNetworkID;
	int nPlayerIndex;
	int eFlag;
};

struct ST_SOCKET_ADDR
{
	SOCKET stSocket;
	SOCKADDR_IN stAddr;
};

struct ST_PLAYER_POSITION
{
	// << : 
	char  szRoomName[50] = { 0, };	// << : Key
	int	  nPlayerIndex;				// << : Current Player Index
	animationState eAnimState;		// << : Animation index
	float fX;						
	float fY;
	float fZ;
	float fAngle;
	ST_PLAYER_POSITION() : nPlayerIndex(0), eAnimState(ANIM_IDLE), fX(0.0f), fY(0.0f), fZ(0.0f), fAngle(0.0f) {};
	ST_PLAYER_POSITION(float x, float y, float z, float angle) { fX = x, fY = y, fZ = z, fAngle = angle; };
};


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include "cDataManager.h"
#include "cTimeManager.h"
#include "cNetworkManager.h"

extern int g_nNetworkID;
extern int g_nThreadCount;
extern HANDLE g_hMutex_DATA;
extern HANDLE g_hMutex_Net;