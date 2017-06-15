#include "stdafx.h"
#include "cContainer.h"

#define WOMAN "Woman"
#define MAN "Man"
#define POSITION "Position"
#define INVENTORY_INDEX "InventoryIndex"

cContainer::cContainer()
	: m_nManTime(0)
	, m_nWomanTime(0)
	, nPlayer1NetID(-1)
	, nPlayer2NetID(-1)
{
}


cContainer::~cContainer()
{
}

void cContainer::UpdateData(ST_PLAYER_POSITION stRecv, ST_SOCKET_ADDR stAddr)
{
	float x = stRecv.fX;
	float y = stRecv.fY;
	float z = stRecv.fZ;
	float Angle = stRecv.fAngle;

	if (stRecv.nPlayerIndex & IN_PLAYER1)
	{
		m_stMan.SetPosition(x, y, z);
		m_stMan.SetAngle(Angle);
		m_stMan.SetAnimState(stRecv.eAnimState);
		Player1Sock = stAddr;
		m_nManTime = clock();
		cout << inet_ntoa(Player1Sock.stAddr.sin_addr) << endl;
	}
	else if (stRecv.nPlayerIndex & IN_PLAYER2)
	{
		m_stWoman.SetPosition(x, y, z);
		m_stWoman.SetAngle(Angle);
		m_stWoman.SetAnimState(stRecv.eAnimState);
		Player2Sock = stAddr;
		cout << inet_ntoa(Player2Sock.stAddr.sin_addr) << endl;
		m_nWomanTime = clock();
	}
}

void cContainer::UpdateData(ST_PLAYER_POSITION stRecv)
{
	float x = stRecv.fX;
	float y = stRecv.fY;
	float z = stRecv.fZ;
	float Angle = stRecv.fAngle;

	if (stRecv.nPlayerIndex & IN_PLAYER1)
	{
		m_stMan.SetPosition(x, y, z);
		m_stMan.SetAngle(Angle);
		m_stMan.SetAnimState(stRecv.eAnimState);
		m_nManTime = clock();
	}
	else if (stRecv.nPlayerIndex & IN_PLAYER2)
	{
		m_stWoman.SetPosition(x, y, z);
		m_stWoman.SetAngle(Angle);
		m_stWoman.SetAnimState(stRecv.eAnimState);
		m_nWomanTime = clock();
	}
}

ST_PLAYER_POSITION cContainer::GetData(int nIndex)
{
	ST_PLAYER_POSITION result;
	if (nIndex == 1)
	{
		m_stMan.GetPosition(&result.fX, &result.fY, &result.fZ);
		result.fAngle = m_stMan.GetAngle();
		result.eAnimState = m_stMan.GetAnimState();
	}
	if (nIndex == 2)
	{
		m_stWoman.GetPosition(&result.fX, &result.fY, &result.fZ);
		result.fAngle = m_stWoman.GetAngle();
		result.eAnimState = m_stWoman.GetAnimState();
	}
	sprintf_s(result.szRoomName, "%s", "FROM SERVER",11);

	return result;
}

int cContainer::GetOnlineUser()
{
	int nResult = 0;

	if (m_nManTime + (ONE_SECOND * 5) > clock())
	{
		nResult = nResult | (OUT_PLAYER1);
		cout << "1P ���� Ȯ��" << endl;
	}
	if (m_nWomanTime + (ONE_SECOND * 5) > clock())
	{
		nResult = nResult | (OUT_PLAYER2);
		cout << "2P ���� Ȯ��" << endl;
	}
		
	return nResult;
}

void cContainer::GetManPosition(OUT float * x, OUT float * y, OUT float * z, OUT float * angle)
{
	m_stMan.GetPosition(x, y, z);
	*angle = m_stMan.GetAngle();
}

void cContainer::GetWomanPosition(OUT float * x, OUT float * y, OUT float * z, OUT float * angle)
{
	m_stWoman.GetPosition(x, y, z);
	*angle = m_stWoman.GetAngle();
}

void cContainer::GetMap(OUT cStuff * arrStuff)
{
	arrStuff = m_aStuff;
}

void cContainer::SaveData()
{
	// << : ���� ���� ��Ȳ ����ó��
	string szFullPath = "DATA/" + m_sRoomName + ".txt";
	ofstream outFile(szFullPath.data(), ios::trunc);
	if (!outFile.is_open())
	{
		char strFolderPath[] = "DATA";
		int nResult = _mkdir(strFolderPath);
		if (nResult == 0)
			cout << "���� ���� ����" << endl;
		else if (nResult == -1)
		{
			perror("���� ���� ���� - ������ �̹� �ְų� ����Ȯ�� \n");
			cout << "errorno :" << errno << endl;
		}
		outFile.open(szFullPath.data(), ios::trunc);
	}

	// << : ������ ���� (�÷��̾� ��ǥ)
	float x, y, z, angle;

	m_stMan.GetPosition(&x, &y, &z);
	angle = m_stMan.GetAngle();
	outFile << "Man " << "Position " << "X " << x << endl;
	outFile << "Man " << "Position " << "Y " << y << endl;
	outFile << "Man " << "Position " << "Z " << z << endl;
	outFile << "Man " << "Position " << "Angle " << angle << endl;
	outFile << endl;

	m_stWoman.GetPosition(&x, &y, &z);
	angle = m_stWoman.GetAngle();
	outFile << "Woman " << "Position " << "X " << x << endl;
	outFile << "Woman " << "Position " << "Y " << y << endl;
	outFile << "Woman " << "Position " << "Z " << z << endl;
	outFile << "Woman " << "Position " << "Angle " << angle << endl;
	outFile << endl;

	// << : ������ ���� (�κ��丮 ����)
	for (int i = 0; i < INVENTORY_SIZE; ++i)	// << : ���� �κ��丮 ����
	{
		outFile << "Man " << "InventoryIndex " << i << " " << m_stMan.GetItem(i) << endl;
		if (i == INVENTORY_SIZE - 1) outFile << endl;
	}

	for (int i = 0; i < INVENTORY_SIZE; ++i)	// << : ���� �κ��丮 ����
	{
		outFile << "Woman " << "InventoryIndex " << i << " " << m_stWoman.GetItem(i) << endl;
		if (i == INVENTORY_SIZE - 1) outFile << endl;
	}

	outFile.close();
}

void cContainer::SetDefault()
{
	m_stMan.SetX(0);
	m_stMan.SetY(0);
	m_stMan.SetZ(0);
	m_stMan.SetAngle(0);

	m_stWoman.SetX(0);
	m_stWoman.SetY(0);
	m_stWoman.SetZ(0);
	m_stWoman.SetAngle(0);

	// << : �ʱ� �����۰� ���õ� ����
	for (int i = 0; i < SWITCH_LASTNUM; ++i)	// << : ������ Ȱ��ȭ ����
		m_aStuff[i].SetIsRunning(false);

	m_aStuff[SWITCH_ONMAP_CROWBAR].SetIsRunning(true);
	m_aStuff[SWITCH_ONMAP_CROWBAR].SetPosition(-40, 12, 12);
	m_aStuff[SWITCH_ONMAP_CROWBAR].SetRotate(0, D3DX_PI / 2.2f, 0);

	m_aStuff[SWITCH_ONMAP_PAPER1].SetIsRunning(true);
	m_aStuff[SWITCH_ONMAP_PAPER1].SetPosition(10, 0.7f, 18);
	m_aStuff[SWITCH_ONMAP_PAPER1].SetRotate(0, 0, 0);

	m_aStuff[SWITCH_ONMAP_PAPER2].SetIsRunning(true);
	m_aStuff[SWITCH_ONMAP_PAPER2].SetPosition(-38, 12.7f, -6);
	m_aStuff[SWITCH_ONMAP_PAPER2].SetRotate(0, 0, 0);

	m_aStuff[SWITCH_ONMAP_PAPER3].SetIsRunning(true);
	m_aStuff[SWITCH_ONMAP_PAPER3].SetPosition(-17.5f, 27.7f, -10.5f);
	m_aStuff[SWITCH_ONMAP_PAPER3].SetRotate(0, 0, 0);

	m_aStuff[SWITCH_ONMAP_KEY1].SetIsRunning(true);
	m_aStuff[SWITCH_ONMAP_KEY1].SetPosition(-14.0f, 0.3f, 1.5f);
	m_aStuff[SWITCH_ONMAP_KEY1].SetRotate(0, D3DX_PI / 2.5f, 0);

	m_aStuff[SWITCH_ONMAP_KEY2].SetIsRunning(true);
	m_aStuff[SWITCH_ONMAP_KEY2].SetPosition(-30, 12.3f, -13);
	m_aStuff[SWITCH_ONMAP_KEY2].SetRotate(0, 0.3f, 0);

	m_aStuff[SWITCH_ONMAP_KEY3].SetIsRunning(false);
	m_aStuff[SWITCH_ONMAP_CROWBAR].SetPosition(0, 0, 0);
	m_aStuff[SWITCH_ONMAP_CROWBAR].SetRotate(0, 0, 0);

	for (int i = SWITCH_ONMAP_BRICK1; i <= SWITCH_ONMAP_BRICK5; ++i)
	{
		m_aStuff[i].SetIsRunning(false);
		m_aStuff[i].SetPosition(0, 0, 0);
		m_aStuff[i].SetRotate(0, 0, 0);
	}

	m_aStuff[SWITCH_FIRSTFLOOR_WOODBOARD1].SetPosition(-7, 12, 19.5f);
}

void cContainer::Update()
{
}

