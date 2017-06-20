#include "stdafx.h"
#include "cContainer.h"

cContainer::cContainer()
	: m_nManTime(0)
	, m_nWomanTime(0)
{
}


cContainer::~cContainer()
{
}

/* ������ ����ü�� ������ �����̳ʿ� �����մϴ� */
void cContainer::ReceivePosition(int nNetworkID, ST_PLAYER_POSITION stRecv)
{
	float x = stRecv.fX;
	float y = stRecv.fY;
	float z = stRecv.fZ;
	float Angle = stRecv.fAngle;
	int nGender = g_pNetworkManager->m_mapGender[nNetworkID];

	if (nGender & IN_PLAYER1)
	{
		m_stMan.SetPosition(x, y, z);
		m_stMan.SetAngle(Angle);
		m_stMan.SetAnimState(stRecv.eAnimState);
		m_nManTime = clock();
	}
	else if (nGender & IN_PLAYER2)
	{
		m_stWoman.SetPosition(x, y, z);
		m_stWoman.SetAngle(Angle);
		m_stWoman.SetAnimState(stRecv.eAnimState);
		m_nWomanTime = clock();
	}
}

void cContainer::ReceiveMap(ST_OBJECT_DATA stData)
{
	// �� ���� ����
	for (int i = 0; i < SWITCH_LASTNUM; ++i)
	{
		m_aStuff[i].SetPosition(stData.mapX[i], stData.mapY[i], stData.mapZ[i]);
		m_aStuff[i].SetRotate(stData.mapRotX[i], stData.mapRotY[i], stData.mapRotZ[i]);
		m_aStuff[i].SetIsRunning(stData.mapIsRunning[i]);
	}

	// ��� ���� ����
	m_stMapStatus.bValve1 = stData.bValve1;
	m_stMapStatus.bValve2 = stData.bValve2;
	m_stMapStatus.nFValve1Count = stData.nFValve1Count;
	m_stMapStatus.nFValve2Count = stData.nFValve2Count;
	m_stMapStatus.nBrickCount = stData.nBrickCount;
}

/* �ε����� ���� �÷��̾��� ��ǥ�� ��ȯ�մϴ� */
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

	return result;
}

/* ���� ����, ������ ���� �����ߴ��� Ȯ���մϴ� (������) */
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

/* ���� ĳ������ ��ǥ�� ��ȯ�մϴ� */
void cContainer::GetManPosition(OUT float * x, OUT float * y, OUT float * z, OUT float * angle)
{
	m_stMan.GetPosition(x, y, z);
	*angle = m_stMan.GetAngle();
}

void cContainer::GetManInventory(OUT int * nArr)
{
	for (int i = 0; i < INVENTORY_SIZE; ++i)
	{
		nArr[i] = m_stMan.GetInventory()[i];
	}
}

animationState cContainer::GetManAnim()
{
	return m_stMan.GetAnimState();
}

/* ���� ĳ������ ��ǥ�� ��ȯ�մϴ� */
void cContainer::GetWomanPosition(OUT float * x, OUT float * y, OUT float * z, OUT float * angle)
{
	m_stWoman.GetPosition(x, y, z);
	*angle = m_stWoman.GetAngle();
}

void cContainer::GetWomanInventory(OUT int * nArr)
{
	for (int i = 0; i < INVENTORY_SIZE; ++i)
	{
		nArr[i] = m_stWoman.GetInventory()[i];
	}
}

animationState cContainer::GetWomanAnim()
{
	return m_stWoman.GetAnimState();
}

/* �ʵ����͸� ��ȯ�մϴ� */
void cContainer::GetStuff(OUT float* X, OUT float* Y, OUT float* Z, OUT float* rotX, OUT float* rotY, OUT float* rotZ, OUT bool* IsRun)
{
	for (int i = 0; i < SWITCH_LASTNUM; ++i)
	{
		m_aStuff[i].GetPosition(&X[i], &Y[i], &Z[i]);
		m_aStuff[i].GetRotate(&rotX[i], &rotY[i], &rotZ[i]);
		IsRun[i] = m_aStuff[i].GetIsRunning();
	}
}

ST_MAP_STATUS cContainer::GetMapStatus()
{
	return m_stMapStatus;
}

/* ������ �ִ��� Ȯ���ϰ� �ִٸ� �ش����Ͽ��� �ε�, ���ٸ� �⺻ �����Լ��� ȣ���մϴ� */
void cContainer::Setup(string key)
{
	m_sRoomName = key;
	string szFullPath = "DATA/" + key + ".txt";
	char szBuffer[1000];

	char Key1[100] = { 0, };
	char Key2[100] = { 0, };

	fstream openFile(szFullPath.data());
	if (!openFile.is_open())	// << : ������ ������ �ʴ� ��Ȳ�Դϴ�.
	{
		SetDefault();
		return;
	}

	while (!openFile.eof())		// << : Parsing Data
	{
		cPlayer* pTarget = NULL;
		openFile.getline(szBuffer, 1000);
		sscanf_s(szBuffer, "%s %s", &Key1, 100, &Key2, 100);
		if (strlen(szBuffer) <= 0) continue;

		// << : �÷��̾� ������ ���
		if (string(Key1) == MAN)
			pTarget = &m_stMan;
		else if (string(Key1) == WOMAN)
			pTarget = &m_stWoman;

		if (string(Key2) == POSITION && pTarget != NULL)
		{
			char Key[100] = { 0, };
			float Value = 0;
			sscanf_s(szBuffer, "%*s %*s %s %f", &Key, 100, &Value);
			string Keyword = string(Key);

			if (Keyword == "X")
				pTarget->SetX(Value);
			else if (Keyword == "Y")
				pTarget->SetY(Value);
			else if (Keyword == "Z")
				pTarget->SetZ(Value);
			else if (Keyword == "Angle")
				pTarget->SetAngle(Value);
		}
		else if (string(Key2) == INVENTORY_INDEX && pTarget != NULL)
		{
			int Index = 0;
			int ItemType = 0;
			sscanf_s(szBuffer, "%*s %*s %d %d", &Index, &ItemType);
			pTarget->SetItem(Index, ItemType);
		}
		// << : �� ������ ���
		if (string(Key1) == STUFF)
		{
			char szBuf1[100] = { 0, };
			char szBuf2[100] = { 0, };
			int Index;
			sscanf_s(szBuffer, "%*s %s %d %s", szBuf1, 100, &Index, szBuf2, 100);
			string keyword1 = string(szBuf1);
			string keyword2 = string(szBuf2);

			if (keyword1 == STUFF_INDEX && keyword2 == POSITION)
			{
				float fX, fY, fZ;
				sscanf_s(szBuffer, "%*s %*s %*d %*s %f %f %f", &fX, &fY, &fZ);
				m_aStuff[Index].SetPosition(fX, fY, fZ);
			}
			else if (keyword1 == STUFF_INDEX && keyword2 == ROTATION)
			{
				float fX, fY, fZ;
				sscanf_s(szBuffer, "%*s %*s %*d %*s %f %f %f", &fX, &fY, &fZ);
				m_aStuff[Index].SetRotate(fX, fY, fZ);
			}
			else if (keyword1 == STUFF_INDEX && keyword2 == ISRUNNING)
			{
				int IsRunning;
				sscanf_s(szBuffer, "%*s %*s %*d %*s %d", &IsRunning);
				m_aStuff[Index].SetIsRunning((bool)IsRunning);
			}
		}

		// << : �� ���� �����ϰ��
		if (string(Key1) == MAPSTATUS)
		{
			int nNum1, nNum2;
			sscanf_s(szBuffer, "%*s %d %d", &nNum1, &nNum2);
			switch (nNum1)
			{
			case 1:
				m_stMapStatus.bValve1 = (bool)nNum2;
				break;
			case 2:
				m_stMapStatus.bValve2 = (bool)nNum2;
				break;
			case 3:
				m_stMapStatus.nFValve1Count = nNum2;
				break;
			case 4:
				m_stMapStatus.nFValve2Count = nNum2;
				break;
			case 5:
				m_stMapStatus.nBrickCount = nNum2;
				break;
			}
			cout << nNum2 << endl;
		}
	}
	if (openFile.eof())
		cout << szFullPath << " : " << " ���� �ε�" << endl;

}

/* �����̳��� ������ ���Ϸ� �����մϴ� */
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
	outFile << MAN << " " << POSITION << " " << "X " << x << endl;
	outFile << MAN << " " << POSITION << " " << "Y " << y << endl;
	outFile << MAN << " " << POSITION << " " << "Z " << z << endl;
	outFile << MAN << " " << POSITION << " " << "Angle " << angle << endl;
	outFile << endl;

	m_stWoman.GetPosition(&x, &y, &z);
	angle = m_stWoman.GetAngle();
	outFile << WOMAN << " " << POSITION << " " << "X " << x << endl;
	outFile << WOMAN << " " << POSITION << " " << "Y " << y << endl;
	outFile << WOMAN << " " << POSITION << " " << "Z " << z << endl;
	outFile << WOMAN << " " << POSITION << " " << "Angle " << angle << endl;
	outFile << endl;

	// << : �κ��丮 ������ ����
	for (int i = 0; i < INVENTORY_SIZE; ++i)	// << : ���� �κ��丮 ����
	{
		outFile << MAN << " " << INVENTORY_INDEX << " " << i << " " << m_stMan.GetItem(i) << endl;
		if (i == INVENTORY_SIZE - 1) outFile << endl;
	}

	for (int i = 0; i < INVENTORY_SIZE; ++i)	// << : ���� �κ��丮 ����
	{
		outFile << WOMAN << " " << INVENTORY_INDEX << " " << i << " " << m_stWoman.GetItem(i) << endl;
		if (i == INVENTORY_SIZE - 1) outFile << endl;
	}

	// << : �� ������ ����
	for (int i = 0; i < SWITCH_LASTNUM; ++i)
	{
		float fX, fY, fZ;
		float fRotX, fRotY, fRotZ;
		bool IsRunning;

		m_aStuff[i].GetPosition(&fX, &fY, &fZ);
		m_aStuff[i].GetRotate(&fRotX, &fRotY, &fRotZ);
		IsRunning = m_aStuff[i].GetIsRunning();

		outFile << STUFF << " " << STUFF_INDEX << " " << i << " " << POSITION << " " << fX << " " << fY << " " << fZ << endl;
		outFile << STUFF << " " << STUFF_INDEX << " " << i << " " << ROTATION << " " << fRotX << " " << fRotY << " " << fRotZ << endl;
		outFile << STUFF << " " << STUFF_INDEX << " " << i << " " << ISRUNNING << " " << IsRunning << endl;
		outFile << endl;
	}

	outFile << MAPSTATUS << " " << 1 << " " << m_stMapStatus.bValve1 << endl;
	outFile << MAPSTATUS << " " << 2 << " " << m_stMapStatus.bValve2 << endl;
	outFile << MAPSTATUS << " " << 3 << " " << m_stMapStatus.nFValve1Count << endl;
	outFile << MAPSTATUS << " " << 4 << " " << m_stMapStatus.nFValve2Count << endl;
	outFile << MAPSTATUS << " " << 5 << " " << m_stMapStatus.nBrickCount << endl;

	outFile.close();
}

/* �ε��� ������ ������ �⺻ �����ϴ� �Լ��Դϴ�. */
void cContainer::SetDefault()
{
	m_stMan.SetX(DEFAULT_MAN_STARTX);
	m_stMan.SetY(DEFAULT_MAN_STARTY);
	m_stMan.SetZ(DEFAULT_MAN_STARTZ);
	m_stMan.SetAngle(0);

	m_stWoman.SetX(DEFAULT_WOMAN_STARTX);
	m_stWoman.SetY(DEFAULT_WOMAN_STARTY);
	m_stWoman.SetZ(DEFAULT_WOMAN_STARTZ);
	m_stWoman.SetAngle(0);

	// << : �ʱ� �����۰� ���õ� ����
	for (int i = 0; i < SWITCH_LASTNUM; ++i)	// << : ������ Ȱ��ȭ ����
		m_aStuff[i].SetIsRunning(false);

	m_aStuff[SWITCH_ONMAP_CROWBAR].SetIsRunning(true);
	m_aStuff[SWITCH_ONMAP_CROWBAR].SetPosition(-40, 12.2f, 12);
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
	m_aStuff[SWITCH_ONMAP_KEY3].SetPosition(0, 0, 0);
	m_aStuff[SWITCH_ONMAP_KEY3].SetRotate(0, 0, 0);

	for (int i = SWITCH_ONMAP_BRICK1; i <= SWITCH_ONMAP_BRICK5; ++i)
	{
		m_aStuff[i].SetIsRunning(false);
		m_aStuff[i].SetPosition(0, 0, 0);
		m_aStuff[i].SetRotate(0, 0, 0);
	}

	m_aStuff[SWITCH_FIRSTFLOOR_WOODBOARD1].SetPosition(-7, 12, 19.5f);
	
	m_stMapStatus.bValve1 = false;
	m_stMapStatus.bValve2 = false;
	m_stMapStatus.nFValve1Count = 0;
	m_stMapStatus.nFValve2Count = 0;
	m_stMapStatus.nBrickCount = 0;
}

void cContainer::SetManInventory(ST_INVENTORY_DATA stData)
{
	m_stMan.SetInventory(stData);
}

void cContainer::SetWomanInventory(ST_INVENTORY_DATA stData)
{
	m_stWoman.SetInventory(stData);
}

void cContainer::Update()
{
}

