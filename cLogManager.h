#pragma once
#include "stdafx.h"

#define g_pLogManager cLogManager::GetInstance()
#define FOLDER_ROOT "LOG"
#define FOLDER_SEND_NETWORKID "SendNetworkID"
#define FOLDER_SEND_ROOMNAME "SendRoomName"
#define FOLDER_SEND_ALL_DATA "SendAllData"
#define FOLDER_SEND_GENDER "SendGender"
#define FOLDER_SEND_POSITION "SendPosition"
#define FOLDER_SEND_OBJECT_DATA "SendObjectData"

#define FOLDER_RECV_NETWORKID "RecvNetworkID"
#define FOLDER_RECV_POSITION "RecvPosition"
#define FOLDER_RECV_OBJECT_DATA "RecvObjectData"
#define FOLDER_RECV_INVENTORY_DATA "RecvInventoryData"

#define FOLDER_PROCESS_GENDER "ProcessGender"

struct ST_TASK_LOG;
enum TAG;

class cLogManager
{
private:
	SINGLETONE(cLogManager);
	list<ST_TASK_LOG> m_listQueue;
	
	void CreateLog_SendNetworkID(ST_TASK_LOG stTask);
	void CreateLog_SendRoomName(ST_TASK_LOG stTask);
	void CreateLog_SendAllData(ST_TASK_LOG stTask);
	void CreateLog_SendGender(ST_TASK_LOG stTask);
	void CreateLog_SendPosition(ST_TASK_LOG stTask);
	void CreateLog_SendObjectData(ST_TASK_LOG stTask);

	void CreateLog_RecvNetworkID(ST_TASK_LOG stTask);
	void CreateLog_RecvPosition(ST_TASK_LOG stTask);
	void CreateLog_RecvObjectData(ST_TASK_LOG stTask);
	void CreateLog_RecvInventoryData(ST_TASK_LOG stTask);

	void CreateLog_ProcessGender(ST_TASK_LOG stTask);

	void CreateFolder(string FolderName);
public:
	void SendNetworkID(int nID);
	void SendRoomName(int nID);
	void SendAllData(int nID);
	void SendGender(int nID);
	void SendPosition(int nID);
	void SendObjectData(int nID);

	void RecvNetworkID(int nID);
	void RecvPosition(int nID);
	void RecvObjectData(int nID);
	void RecvInventoryData(int nID);
	
	void ProcessGender(int nID);

	void Update();
};

struct ST_TASK_LOG
{
	TAG key;
	int ID;
};
enum TAG
{
	SEND_NETWORKID,
	SEND_ROOMNAME,
	SEND_ALL_DATA,
	SEND_GENDER,
	SEND_POSITION,
	SEND_OBJECT_DATA,
	RECV_NETWORKID,
	RECV_POSITION,
	RECV_OBJECT_DATA,
	RECV_INVENTORY_DATA,
	PROCESS_GENDER
};



