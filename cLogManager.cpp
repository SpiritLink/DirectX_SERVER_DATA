#include "stdafx.h"
#include "cLogManager.h"

/* �α׸� ������ ������ �����մϴ� */
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

/* SendNetworkID�Լ��� ȣ�������� txt ���Ͽ� ����մϴ� */
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

/* SendRoomName�Լ��� ȣ�������� txt ���Ͽ� ����մϴ� */
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

/* SendAllData �Լ��� ȣ�������� txt ���Ͽ� ����մϴ� */
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

/* SendGender �Լ��� ȣ�������� txt ���Ͽ� ����մϴ� */
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

/* SendPosition �Լ��� ȣ�������� txt ���Ͽ� ����մϴ� */
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

/* SendObjectData �Լ��� ȣ�������� txt���Ͽ� ����մϴ� */
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

/* RecvNetworkID�� ȣ�������� txt ���Ͽ� ����մϴ� */
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

/* RecvPosition �Լ��� ȣ�������� txt���Ͽ� ����մϴ� */
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

/* RecvObjectData �Լ��� ȣ�������� txt���Ͽ� ����մϴ� */
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

/* RecvInventoryData �Լ��� ȣ�������� txt���Ͽ� ����մϴ� */
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

/* ProcessGender �Լ��� ȣ�������� txt���Ͽ� ����մϴ� */
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

/* ������ �����ϴ� �Լ��Դϴ� */
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

/* ť�� SendNetworkID �Լ��� ȣ���ٰ� ����մϴ� */
void cLogManager::SendNetworkID(int nID)
{
	ST_TASK_LOG stTask;
	stTask.key = TAG::SEND_NETWORKID;
	stTask.ID = nID;
	WaitForSingleObject(g_hMutex_LOG,INFINITE);
	m_listQueue.push_back(stTask);
	ReleaseMutex(g_hMutex_LOG);
}

/* ť�� SendRoomName �Լ��� ȣ���ٰ� ����մϴ� */
void cLogManager::SendRoomName(int nID)
{
	ST_TASK_LOG stTask;
	stTask.key = TAG::SEND_ROOMNAME;
	stTask.ID = nID;
	WaitForSingleObject(g_hMutex_LOG, INFINITE);
	m_listQueue.push_back(stTask);
	ReleaseMutex(g_hMutex_LOG);
}

/* ť�� SendAllData �Լ��� ȣ���ٰ� ����մϴ� */
void cLogManager::SendAllData(int nID)
{
	ST_TASK_LOG stTask;
	stTask.key = TAG::SEND_ALL_DATA;
	stTask.ID = nID;
	WaitForSingleObject(g_hMutex_LOG, INFINITE);
	m_listQueue.push_back(stTask);
	ReleaseMutex(g_hMutex_LOG);
}

/* ť�� SendGender �Լ��� ȣ���ٰ� ����մϴ� */
void cLogManager::SendGender(int nID)
{
	ST_TASK_LOG stTask;
	stTask.key = TAG::SEND_GENDER;
	stTask.ID = nID;
	WaitForSingleObject(g_hMutex_LOG, INFINITE);
	m_listQueue.push_back(stTask);
	ReleaseMutex(g_hMutex_LOG);
}

/* ť�� SendPosition �Լ��� ȣ���ٰ� ����մϴ� */
void cLogManager::SendPosition(int nID)
{
	ST_TASK_LOG stTask;
	stTask.key = TAG::SEND_POSITION;
	stTask.ID = nID;
	WaitForSingleObject(g_hMutex_LOG, INFINITE);
	m_listQueue.push_back(stTask);
	ReleaseMutex(g_hMutex_LOG);
}

/* ť�� SendObjectData �Լ��� ȣ���ٰ� ����մϴ� */
void cLogManager::SendObjectData(int nID)
{
	ST_TASK_LOG stTask;
	stTask.key = TAG::SEND_OBJECT_DATA;
	stTask.ID = nID;
	WaitForSingleObject(g_hMutex_LOG, INFINITE);
	m_listQueue.push_back(stTask);
	ReleaseMutex(g_hMutex_LOG);
}

/* ť�� RecvNetworkID �Լ��� ȣ���ٰ� ����մϴ� */
void cLogManager::RecvNetworkID(int nID)
{
	ST_TASK_LOG stTask;
	stTask.key = TAG::RECV_NETWORKID;
	stTask.ID = nID;
	WaitForSingleObject(g_hMutex_LOG, INFINITE);
	m_listQueue.push_back(stTask);
	ReleaseMutex(g_hMutex_LOG);
}

/* ť�� RecvPosition �Լ��� ȣ���ٰ� ����մϴ� */
void cLogManager::RecvPosition(int nID)
{
	ST_TASK_LOG stTask;
	stTask.key = TAG::RECV_POSITION;
	stTask.ID = nID;
	WaitForSingleObject(g_hMutex_LOG, INFINITE);
	m_listQueue.push_back(stTask);
	ReleaseMutex(g_hMutex_LOG);
}

/* ť�� RecvObjectData �Լ��� ȣ���ٰ� ����մϴ� */
void cLogManager::RecvObjectData(int nID)
{
	ST_TASK_LOG stTask;
	stTask.key = TAG::RECV_OBJECT_DATA;
	stTask.ID = nID;
	WaitForSingleObject(g_hMutex_LOG, INFINITE);
	m_listQueue.push_back(stTask);
	ReleaseMutex(g_hMutex_LOG);
}

/* ť�� RecvInventoryData �Լ��� ȣ���ٰ� ����մϴ� */
void cLogManager::RecvInventoryData(int nID)
{
	ST_TASK_LOG stTask;
	stTask.key = TAG::RECV_INVENTORY_DATA;
	stTask.ID = nID;
	WaitForSingleObject(g_hMutex_LOG, INFINITE);
	m_listQueue.push_back(stTask);
	ReleaseMutex(g_hMutex_LOG);
}

/* ť�� ProcessGender �Լ��� ȣ���ٰ� ����մϴ� */
void cLogManager::ProcessGender(int nID)
{
	ST_TASK_LOG stTask;
	stTask.key = TAG::PROCESS_GENDER;
	stTask.ID = nID;
	WaitForSingleObject(g_hMutex_LOG, INFINITE);
	m_listQueue.push_back(stTask);
	ReleaseMutex(g_hMutex_LOG);
}

/* ------------------------------------------------------------------------
ť�� �α׸� ���ܾ��� ������ �ִ��� Ȯ���մϴ�. ť�� ����ִٸ� �Լ��� �����մϴ�. 
ť�� ù��°�� �̾Ƴ��� �ش��ϴ� �α׸� �ۼ��մϴ�
 *///----------------------------------------------------------------------
void cLogManager::Update()
{
	WaitForSingleObject(g_hMutex_LOG, INFINITE);
	if (m_listQueue.empty())
	{
		ReleaseMutex(g_hMutex_LOG);
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

