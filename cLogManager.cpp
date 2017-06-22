#include "stdafx.h"
#include "cLogManager.h"


cLogManager::cLogManager()
{
	CreateFolder("SendNetworkID");
}


cLogManager::~cLogManager()
{
}

void cLogManager::CreateLog_SendNetworkID(ST_TASK_LOG stTask)
{
}

void cLogManager::CreateLog_SendRoomName(ST_TASK_LOG stTask)
{
}

void cLogManager::CreateLog_SendAllData(ST_TASK_LOG stTask)
{
}

void cLogManager::CreateLog_SendGender(ST_TASK_LOG stTask)
{
}

void cLogManager::CreateLog_SendPosition(ST_TASK_LOG stTask)
{
}

void cLogManager::CreateLog_SendObjectData(ST_TASK_LOG stTask)
{
}

void cLogManager::CreateLog_RecvNetworkID(ST_TASK_LOG stTask)
{
}

void cLogManager::CreateLog_RecvPosition(ST_TASK_LOG stTask)
{
}

void cLogManager::CreateLog_RecvObjectData(ST_TASK_LOG stTask)
{
}

void cLogManager::CreateLog_RecvInventoryData(ST_TASK_LOG stTask)
{
}

void cLogManager::CreateLog_ProcessGender(ST_TASK_LOG stTask)
{
}

void cLogManager::CreateFolder(string FolderName)
{
	char strFolderPath[] = ROOT_FOLDER;
	int nResult = _mkdir(strFolderPath);
	if (nResult == 0)
		cout << strFolderPath << "폴더 생성 성공" << endl;
	else if (nResult == -1)
		cout << strFolderPath << "는 이미 존재하거나 부정확 합니다." << endl;
	string szFullPath = string(strFolderPath) + "/" + string(FolderName);

	char FullPath[1024] = { 0, };
	sprintf_s(FullPath, "%s", szFullPath.c_str(), sizeof(FullPath));

	nResult = _mkdir(FullPath);
	if (nResult == 0)
		cout << FullPath << "폴더 생성 성공" << endl;
	else if (nResult == -1)
		cout << FullPath << "는 이미 존재하거나 부정확 합니다." << endl;
}

void cLogManager::SendNetworkID(int nID)
{
	ST_TASK_LOG stTask;
	stTask.key = TAG::SEND_NETWORKID;
	stTask.ID = nID;
	m_listQueue.push_back(stTask);
}

void cLogManager::SendRoomName(int nID)
{
	ST_TASK_LOG stTask;
	stTask.key = TAG::SEND_ROOMNAME;
	stTask.ID = nID;
	m_listQueue.push_back(stTask);
}

void cLogManager::SendAllData(int nID)
{
	ST_TASK_LOG stTask;
	stTask.key = TAG::SEND_ALL_DATA;
	stTask.ID = nID;
	m_listQueue.push_back(stTask);
}

void cLogManager::SendGender(int nID)
{
	ST_TASK_LOG stTask;
	stTask.key = TAG::SEND_GENDER;
	stTask.ID = nID;
	m_listQueue.push_back(stTask);
}

void cLogManager::SendPosition(int nID)
{
	ST_TASK_LOG stTask;
	stTask.key = TAG::SEND_POSITION;
	stTask.ID = nID;
	m_listQueue.push_back(stTask);
}

void cLogManager::SendObjectData(int nID)
{
	ST_TASK_LOG stTask;
	stTask.key = TAG::SEND_OBJECT_DATA;
	stTask.ID = nID;
	m_listQueue.push_back(stTask);
}

void cLogManager::RecvNetworkID(int nID)
{
	ST_TASK_LOG stTask;
	stTask.key = TAG::RECV_NETWORKID;
	stTask.ID = nID;
	m_listQueue.push_back(stTask);
}

void cLogManager::RecvPosition(int nID)
{
	ST_TASK_LOG stTask;
	stTask.key = TAG::RECV_POSITION;
	stTask.ID = nID;
	m_listQueue.push_back(stTask);
}

void cLogManager::RecvObjectData(int nID)
{
	ST_TASK_LOG stTask;
	stTask.key = TAG::RECV_OBJECT_DATA;
	stTask.ID = nID;
	m_listQueue.push_back(stTask);
}

void cLogManager::RecvInventoryData(int nID)
{
	ST_TASK_LOG stTask;
	stTask.key = TAG::RECV_INVENTORY_DATA;
	stTask.ID = nID;
	m_listQueue.push_back(stTask);
}

void cLogManager::ProcessGender(int nID)
{
	ST_TASK_LOG stTask;
	stTask.key = TAG::PROCESS_GENDER;
	stTask.ID = nID;
	m_listQueue.push_back(stTask);
}

void cLogManager::Update()
{
	if (m_listQueue.empty())
		return;
	
	ST_TASK_LOG stTask = m_listQueue.front();
	m_listQueue.pop_front();

	switch (stTask.ID)
	{
	case TAG::SEND_NETWORKID:
		CreateLog_SendNetworkID(stTask);
		break;
	case TAG::SEND_ROOMNAME:
		CreateLog_SendRoomName(stTask);
		break;
	case TAG::SEND_ALL_DATA:
		CreateLog_SendAllData(stTask);
		break;
	case TAG::SEND_GENDER:
		CreateLog_SendGender(stTask);
		break;
	case TAG::SEND_POSITION:
		CreateLog_SendPosition(stTask);
		break;
	case TAG::SEND_OBJECT_DATA:
		CreateLog_SendObjectData(stTask);
		break;
	case TAG::RECV_NETWORKID:
		CreateLog_RecvNetworkID(stTask);
		break;
	case TAG::RECV_POSITION:
		CreateLog_RecvPosition(stTask);
		break;
	case TAG::RECV_OBJECT_DATA:
		CreateLog_RecvObjectData(stTask);
		break;
	case TAG::RECV_INVENTORY_DATA:
		CreateLog_RecvInventoryData(stTask);
		break;
	case TAG::PROCESS_GENDER:
		CreateLog_ProcessGender(stTask);
		break;
	}
}

