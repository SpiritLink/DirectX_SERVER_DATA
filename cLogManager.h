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
	
	void CreateLog_SendNetworkID(int nNetworkID);
	void CreateLog_SendRoomName(int nNetworkID);
	void CreateLog_SendAllData(int nNetworkID);
	void CreateLog_SendGender(int nNetworkID);
	void CreateLog_SendPosition(int nNetworkID);
	void CreateLog_SendObjectData(int nNetworkID);

	void CreateLog_RecvNetworkID(int nNetworkID);
	void CreateLog_RecvPosition(int nNetworkID);
	void CreateLog_RecvObjectData(int nNetworkID);
	void CreateLog_RecvInventoryData(int nNetworkID);

	void CreateLog_ProcessGender(int nNetworkID);

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




