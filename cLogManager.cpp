#include "stdafx.h"
#include "cLogManager.h"


cLogManager::cLogManager()
{
	CreateFolder(FOLDER_SEND_NETWORKID);
	CreateFolder(FOLDER_SEND_ROOMNAME);
	CreateFolder(FOLDER_SEND_ALL_DATA);
	CreateFolder(FOLDER_SEND_GENDER);
	CreateFolder(FOLDER_SEND_POSITION);
	CreateFolder(FOLDER_SEND_OBJECT_DATA);

	CreateFolder(FOLDER_RECV_NETWORKID);
	CreateFolder(FOLDER_RECV_POSITION);
	CreateFolder(FOLDER_RECV_OBJECT_DATA);
	CreateFolder(FOLDER_RECV_INVENTORY_DATA);

	CreateFolder(FOLDER_PROCESS_GENDER);
}


cLogManager::~cLogManager()
{
}

void cLogManager::CreateLog_SendNetworkID(int nNetworkID)
{
	string szFullPath_User = FOLDER_ROOT + string("/") + g_pNetworkManager->m_mapID[nNetworkID] + string(".txt");
	string szFullPath_Root = FOLDER_ROOT + string("/") + string("ALL_LOG.txt");
	ofstream UserLog(szFullPath_User.data(),ios::app);
	ofstream AllLog(szFullPath_Root.data(), ios::app);

	string IP = inet_ntoa(g_pNetworkManager->m_mapAddr[nNetworkID].sin_addr);
	string RoomName = g_pNetworkManager->m_mapID[nNetworkID];

	UserLog << g_pTime->GetLocalTime_String() << " " << "IP : " << IP << " ROOM : " << RoomName << endl;
	AllLog << g_pTime->GetLocalTime_String() << " " << "IP : " << IP << " ROOM : " << RoomName << endl;

	UserLog.close();
	AllLog.close();
}

void cLogManager::CreateLog_SendRoomName(int nNetworkID)
{
	string szFullPath_User = FOLDER_ROOT + string("/") + g_pNetworkManager->m_mapID[nNetworkID] + string(".txt");
	string szFullPath_Root = FOLDER_ROOT + string("/") + string("ALL_LOG.txt");

	ofstream UserLog(szFullPath_User.data(), ios::app);
	ofstream AllLog(szFullPath_Root.data(), ios::app);

	string IP = inet_ntoa(g_pNetworkManager->m_mapAddr[nNetworkID].sin_addr);
	string RoomName = g_pNetworkManager->m_mapID[nNetworkID];

	UserLog << g_pTime->GetLocalTime_String() << " " << "IP : " << IP << " ROOM : " << RoomName << endl;
	AllLog << g_pTime->GetLocalTime_String() << " " << "IP : " << IP << " ROOM : " << RoomName << endl;

	UserLog.close();
	AllLog.close();
}

void cLogManager::CreateLog_SendAllData(int nNetworkID)
{
	string szFullPath_User = FOLDER_ROOT + string("/") + g_pNetworkManager->m_mapID[nNetworkID] + string(".txt");
	string szFullPath_Root = FOLDER_ROOT + string("/") + string("ALL_LOG.txt");

	ofstream UserLog(szFullPath_User.data(), ios::app);
	ofstream AllLog(szFullPath_Root.data(), ios::app);

	string IP = inet_ntoa(g_pNetworkManager->m_mapAddr[nNetworkID].sin_addr);
	string RoomName = g_pNetworkManager->m_mapID[nNetworkID];

	UserLog << g_pTime->GetLocalTime_String() << " " << "IP : " << IP << " ROOM : " << RoomName << endl;
	AllLog << g_pTime->GetLocalTime_String() << " " << "IP : " << IP << " ROOM : " << RoomName << endl;

	UserLog.close();
	AllLog.close();
}

void cLogManager::CreateLog_SendGender(int nNetworkID)
{
	string szFullPath_User = FOLDER_ROOT + string("/") + g_pNetworkManager->m_mapID[nNetworkID] + string(".txt");
	string szFullPath_Root = FOLDER_ROOT + string("/") + string("ALL_LOG.txt");

	ofstream UserLog(szFullPath_User.data(), ios::app);
	ofstream AllLog(szFullPath_Root.data(), ios::app);

	string IP = inet_ntoa(g_pNetworkManager->m_mapAddr[nNetworkID].sin_addr);
	string RoomName = g_pNetworkManager->m_mapID[nNetworkID];

	UserLog << g_pTime->GetLocalTime_String() << " " << "IP : " << IP << " ROOM : " << RoomName << endl;
	AllLog << g_pTime->GetLocalTime_String() << " " << "IP : " << IP << " ROOM : " << RoomName << endl;

	UserLog.close();
	AllLog.close();
}

void cLogManager::CreateLog_SendPosition(int nNetworkID)
{
	string szFullPath_User = FOLDER_ROOT + string("/") + g_pNetworkManager->m_mapID[nNetworkID] + string(".txt");
	string szFullPath_Root = FOLDER_ROOT + string("/") + string("ALL_LOG.txt");

	ofstream UserLog(szFullPath_User.data(), ios::app);
	ofstream AllLog(szFullPath_Root.data(), ios::app);

	string IP = inet_ntoa(g_pNetworkManager->m_mapAddr[nNetworkID].sin_addr);
	string RoomName = g_pNetworkManager->m_mapID[nNetworkID];

	UserLog << g_pTime->GetLocalTime_String() << " " << "IP : " << IP << " ROOM : " << RoomName << endl;
	AllLog << g_pTime->GetLocalTime_String() << " " << "IP : " << IP << " ROOM : " << RoomName << endl;

	UserLog.close();
	AllLog.close();
}

void cLogManager::CreateLog_SendObjectData(int nNetworkID)
{
	string szFullPath_User = FOLDER_ROOT + string("/") + g_pNetworkManager->m_mapID[nNetworkID] + string(".txt");
	string szFullPath_Root = FOLDER_ROOT + string("/") + string("ALL_LOG.txt");

	ofstream UserLog(szFullPath_User.data(), ios::app);
	ofstream AllLog(szFullPath_Root.data(), ios::app);

	string IP = inet_ntoa(g_pNetworkManager->m_mapAddr[nNetworkID].sin_addr);
	string RoomName = g_pNetworkManager->m_mapID[nNetworkID];

	UserLog << g_pTime->GetLocalTime_String() << " " << "IP : " << IP << " ROOM : " << RoomName << endl;
	AllLog << g_pTime->GetLocalTime_String() << " " << "IP : " << IP << " ROOM : " << RoomName << endl;

	UserLog.close();
	AllLog.close();
}

void cLogManager::CreateLog_RecvNetworkID(int nNetworkID)
{
	string szFullPath_User = FOLDER_ROOT + string("/") + g_pNetworkManager->m_mapID[nNetworkID] + string(".txt");
	string szFullPath_Root = FOLDER_ROOT + string("/") + string("ALL_LOG.txt");

	ofstream UserLog(szFullPath_User.data(), ios::app);
	ofstream AllLog(szFullPath_Root.data(), ios::app);

	string IP = inet_ntoa(g_pNetworkManager->m_mapAddr[nNetworkID].sin_addr);
	string RoomName = g_pNetworkManager->m_mapID[nNetworkID];

	UserLog << g_pTime->GetLocalTime_String() << " " << "IP : " << IP << " ROOM : " << RoomName << endl;
	AllLog << g_pTime->GetLocalTime_String() << " " << "IP : " << IP << " ROOM : " << RoomName << endl;

	UserLog.close();
	AllLog.close();
}

void cLogManager::CreateLog_RecvPosition(int nNetworkID)
{
	string szFullPath_User = FOLDER_ROOT + string("/") + g_pNetworkManager->m_mapID[nNetworkID] + string(".txt");
	string szFullPath_Root = FOLDER_ROOT + string("/") + string("ALL_LOG.txt");

	ofstream UserLog(szFullPath_User.data(), ios::app);
	ofstream AllLog(szFullPath_Root.data(), ios::app);

	string IP = inet_ntoa(g_pNetworkManager->m_mapAddr[nNetworkID].sin_addr);
	string RoomName = g_pNetworkManager->m_mapID[nNetworkID];

	UserLog << g_pTime->GetLocalTime_String() << " " << "IP : " << IP << " ROOM : " << RoomName << endl;
	AllLog << g_pTime->GetLocalTime_String() << " " << "IP : " << IP << " ROOM : " << RoomName << endl;

	UserLog.close();
	AllLog.close();
}

void cLogManager::CreateLog_RecvObjectData(int nNetworkID)
{
	string szFullPath_User = FOLDER_ROOT + string("/") + g_pNetworkManager->m_mapID[nNetworkID] + string(".txt");
	string szFullPath_Root = FOLDER_ROOT + string("/") + string("ALL_LOG.txt");

	ofstream UserLog(szFullPath_User.data(), ios::app);
	ofstream AllLog(szFullPath_Root.data(), ios::app);

	string IP = inet_ntoa(g_pNetworkManager->m_mapAddr[nNetworkID].sin_addr);
	string RoomName = g_pNetworkManager->m_mapID[nNetworkID];

	UserLog << g_pTime->GetLocalTime_String() << " " << "IP : " << IP << " ROOM : " << RoomName << endl;
	AllLog << g_pTime->GetLocalTime_String() << " " << "IP : " << IP << " ROOM : " << RoomName << endl;

	UserLog.close();
	AllLog.close();
}

void cLogManager::CreateLog_RecvInventoryData(int nNetworkID)
{
	string szFullPath_User = FOLDER_ROOT + string("/") + g_pNetworkManager->m_mapID[nNetworkID] + string(".txt");
	string szFullPath_Root = FOLDER_ROOT + string("/") + string("ALL_LOG.txt");

	ofstream UserLog(szFullPath_User.data(), ios::app);
	ofstream AllLog(szFullPath_Root.data(), ios::app);

	string IP = inet_ntoa(g_pNetworkManager->m_mapAddr[nNetworkID].sin_addr);
	string RoomName = g_pNetworkManager->m_mapID[nNetworkID];

	UserLog << g_pTime->GetLocalTime_String() << " " << "IP : " << IP << " ROOM : " << RoomName << endl;
	AllLog << g_pTime->GetLocalTime_String() << " " << "IP : " << IP << " ROOM : " << RoomName << endl;

	UserLog.close();
	AllLog.close();
}

void cLogManager::CreateLog_ProcessGender(int nNetworkID)
{
	string szFullPath_User = FOLDER_ROOT + string("/") + g_pNetworkManager->m_mapID[nNetworkID] + string(".txt");
	string szFullPath_Root = FOLDER_ROOT + string("/") + string("ALL_LOG.txt");

	ofstream UserLog(szFullPath_User.data(), ios::app);
	ofstream AllLog(szFullPath_Root.data(), ios::app);

	string IP = inet_ntoa(g_pNetworkManager->m_mapAddr[nNetworkID].sin_addr);
	string RoomName = g_pNetworkManager->m_mapID[nNetworkID];

	UserLog << g_pTime->GetLocalTime_String() << " " << "IP : " << IP << " ROOM : " << RoomName << endl;
	AllLog << g_pTime->GetLocalTime_String() << " " << "IP : " << IP << " ROOM : " << RoomName << endl;

	UserLog.close();
	AllLog.close();
}

void cLogManager::CreateFolder(string FolderName)
{
	char strFolderPath[] = FOLDER_ROOT;
	int nResult = _mkdir(strFolderPath);
	if (nResult == 0)
		cout << strFolderPath << "���� ���� ����" << endl;
	else if (nResult == -1)
		cout << strFolderPath << "�� �̹� �����ϰų� ����Ȯ �մϴ�." << endl;
	string szFullPath = string(strFolderPath) + "/" + string(FolderName);

	char FullPath[1024] = { 0, };
	sprintf_s(FullPath, "%s", szFullPath.c_str(), sizeof(FullPath));

	nResult = _mkdir(FullPath);
	if (nResult == 0)
		cout << FullPath << "���� ���� ����" << endl;
	else if (nResult == -1)
		cout << FullPath << "�� �̹� �����ϰų� ����Ȯ �մϴ�." << endl;
}

void cLogManager::SendNetworkID(int nID)
{
	ST_TASK_LOG stTask;
	stTask.key = TAG::SEND_NETWORKID;
	stTask.ID = nID;
	WaitForSingleObject(g_hMutex_LOG,INFINITE);
	m_listQueue.push_back(stTask);
	ReleaseMutex(g_hMutex_LOG);
}

void cLogManager::SendRoomName(int nID)
{
	ST_TASK_LOG stTask;
	stTask.key = TAG::SEND_ROOMNAME;
	stTask.ID = nID;
	WaitForSingleObject(g_hMutex_LOG, INFINITE);
	m_listQueue.push_back(stTask);
	ReleaseMutex(g_hMutex_LOG);
}

void cLogManager::SendAllData(int nID)
{
	ST_TASK_LOG stTask;
	stTask.key = TAG::SEND_ALL_DATA;
	stTask.ID = nID;
	WaitForSingleObject(g_hMutex_LOG, INFINITE);
	m_listQueue.push_back(stTask);
	ReleaseMutex(g_hMutex_LOG);
}

void cLogManager::SendGender(int nID)
{
	ST_TASK_LOG stTask;
	stTask.key = TAG::SEND_GENDER;
	stTask.ID = nID;
	WaitForSingleObject(g_hMutex_LOG, INFINITE);
	m_listQueue.push_back(stTask);
	ReleaseMutex(g_hMutex_LOG);
}

void cLogManager::SendPosition(int nID)
{
	ST_TASK_LOG stTask;
	stTask.key = TAG::SEND_POSITION;
	stTask.ID = nID;
	WaitForSingleObject(g_hMutex_LOG, INFINITE);
	m_listQueue.push_back(stTask);
	ReleaseMutex(g_hMutex_LOG);
}

void cLogManager::SendObjectData(int nID)
{
	ST_TASK_LOG stTask;
	stTask.key = TAG::SEND_OBJECT_DATA;
	stTask.ID = nID;
	WaitForSingleObject(g_hMutex_LOG, INFINITE);
	m_listQueue.push_back(stTask);
	ReleaseMutex(g_hMutex_LOG);
}

void cLogManager::RecvNetworkID(int nID)
{
	ST_TASK_LOG stTask;
	stTask.key = TAG::RECV_NETWORKID;
	stTask.ID = nID;
	WaitForSingleObject(g_hMutex_LOG, INFINITE);
	m_listQueue.push_back(stTask);
	ReleaseMutex(g_hMutex_LOG);
}

void cLogManager::RecvPosition(int nID)
{
	ST_TASK_LOG stTask;
	stTask.key = TAG::RECV_POSITION;
	stTask.ID = nID;
	WaitForSingleObject(g_hMutex_LOG, INFINITE);
	m_listQueue.push_back(stTask);
	ReleaseMutex(g_hMutex_LOG);
}

void cLogManager::RecvObjectData(int nID)
{
	ST_TASK_LOG stTask;
	stTask.key = TAG::RECV_OBJECT_DATA;
	stTask.ID = nID;
	WaitForSingleObject(g_hMutex_LOG, INFINITE);
	m_listQueue.push_back(stTask);
	ReleaseMutex(g_hMutex_LOG);
}

void cLogManager::RecvInventoryData(int nID)
{
	ST_TASK_LOG stTask;
	stTask.key = TAG::RECV_INVENTORY_DATA;
	stTask.ID = nID;
	WaitForSingleObject(g_hMutex_LOG, INFINITE);
	m_listQueue.push_back(stTask);
	ReleaseMutex(g_hMutex_LOG);
}

void cLogManager::ProcessGender(int nID)
{
	ST_TASK_LOG stTask;
	stTask.key = TAG::PROCESS_GENDER;
	stTask.ID = nID;
	WaitForSingleObject(g_hMutex_LOG, INFINITE);
	m_listQueue.push_back(stTask);
	ReleaseMutex(g_hMutex_LOG);
}

void cLogManager::Update()
{
	WaitForSingleObject(g_hMutex_LOG, INFINITE);
	if (m_listQueue.empty())
	{
		ReleaseMutex(g_hMutex_LOG);
		int a = 3;
		return;
	}
	
	ST_TASK_LOG stTask = m_listQueue.front();
	m_listQueue.pop_front();
	ReleaseMutex(g_hMutex_LOG);

	switch (stTask.key)
	{
	case TAG::SEND_NETWORKID:
		CreateLog_SendNetworkID(stTask.ID);
		cout << "Log Send Net work" << endl;
		break;
	case TAG::SEND_ROOMNAME:
		CreateLog_SendRoomName(stTask.ID);
		cout << "Log Send Room Name" << endl;
		break;
	case TAG::SEND_ALL_DATA:
		CreateLog_SendAllData(stTask.ID);
		cout << "Log Send All Data" << endl;
		break;
	case TAG::SEND_GENDER:
		CreateLog_SendGender(stTask.ID);
		cout << "Log Send Gender" << endl;
		break;
	case TAG::SEND_POSITION:
		CreateLog_SendPosition(stTask.ID);
		cout << "Log Send Position" << endl;
		break;
	case TAG::SEND_OBJECT_DATA:
		CreateLog_SendObjectData(stTask.ID);
		cout << "Log Send Object Data " << endl;
		break;
	case TAG::RECV_NETWORKID:
		CreateLog_RecvNetworkID(stTask.ID);
		cout << "Log Recv NetworkID " << endl;
		break;
	case TAG::RECV_POSITION:
		CreateLog_RecvPosition(stTask.ID);
		cout << "Log Recv Position " << endl;
		break;
	case TAG::RECV_OBJECT_DATA:
		CreateLog_RecvObjectData(stTask.ID);
		cout << "Log Recv Object Data " << endl;
		break;
	case TAG::RECV_INVENTORY_DATA:
		CreateLog_RecvInventoryData(stTask.ID);
		cout << "Log Recv Inventory Data " << endl;
		break;
	case TAG::PROCESS_GENDER:
		CreateLog_ProcessGender(stTask.ID);
		cout << "Log Process Gender" << endl;
		break;
	}
}

