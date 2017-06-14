#include "stdafx.h"
#include "cContainer.h"

cContainer::cContainer()
	: m_nPlayer1Time(0)
	, m_nPlayer2Time(0)
	, nPlayer1NetID(-1)
	, nPlayer2NetID(-1)
{
	m_vecStuffPosition.resize(SWITCH_LASTNUM);
}


cContainer::~cContainer()
{
}

void cContainer::Setup(string key)
{
	m_sRoomName = key;
	string szFullPath = "Server/" + key + ".txt";
	char szBuffer[1000];

	char first[100] = { 0, };
	char second[100] = { 0, };
	float third;

	fstream openFile(szFullPath.data());
	if (!openFile.is_open())	// << : 파일이 열리지 않는 상황입니다.
	{
		SetDefault();
		return;
	}

	while (!openFile.eof())		// << : Parsing Data
	{
		cPlayer* pTarget = NULL;
		openFile.getline(szBuffer, 1000);
		sscanf_s(szBuffer, "%s %s %f", &first,100, &second,100, &third);
		if (strlen(szBuffer) <= 0) continue;

		if (string(first) == "Player1")
			pTarget = &m_cPlayer1;
		else if (string(first) == "Player2")
			pTarget = &m_cPlayer2;

		if (pTarget == NULL) continue;		
		
		if (string(second) == "X")
		{
			pTarget->SetX(third);
		}
		else if (string(second) == "Y")
		{
			pTarget->SetY(third);
		}
		else if (string(second) == "Z")
		{
			pTarget->SetZ(third);
		}
		else if (string(second) == "Angle")
		{
			pTarget->SetAngle(third);
		}
		cout << " 파일 로딩 " << endl;
	}
}

void cContainer::UpdateData(ST_PLAYER_POSITION stRecv, ST_SOCKET_ADDR stAddr)
{
	float x = stRecv.fX;
	float y = stRecv.fY;
	float z = stRecv.fZ;
	float Angle = stRecv.fAngle;

	if (stRecv.nPlayerIndex & IN_PLAYER1)
	{
		m_cPlayer1.SetPosition(x, y, z);
		m_cPlayer1.SetAngle(Angle);
		m_cPlayer1.SetAnimState(stRecv.eAnimState);
		Player1Sock = stAddr;
		m_nPlayer1Time = clock();
		cout << inet_ntoa(Player1Sock.stAddr.sin_addr) << endl;
	}
	else if (stRecv.nPlayerIndex & IN_PLAYER2)
	{
		m_cPlayer2.SetPosition(x, y, z);
		m_cPlayer2.SetAngle(Angle);
		m_cPlayer2.SetAnimState(stRecv.eAnimState);
		Player2Sock = stAddr;
		cout << inet_ntoa(Player2Sock.stAddr.sin_addr) << endl;
		m_nPlayer2Time = clock();
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
		m_cPlayer1.SetPosition(x, y, z);
		m_cPlayer1.SetAngle(Angle);
		m_cPlayer1.SetAnimState(stRecv.eAnimState);
		m_nPlayer1Time = clock();
	}
	else if (stRecv.nPlayerIndex & IN_PLAYER2)
	{
		m_cPlayer2.SetPosition(x, y, z);
		m_cPlayer2.SetAngle(Angle);
		m_cPlayer2.SetAnimState(stRecv.eAnimState);
		m_nPlayer2Time = clock();
	}
}

ST_PLAYER_POSITION cContainer::GetData(int nIndex)
{
	ST_PLAYER_POSITION result;
	if (nIndex == 1)
	{
		m_cPlayer1.GetPosition(&result.fX, &result.fY, &result.fZ);
		result.fAngle = m_cPlayer1.GetAngle();
		result.eAnimState = m_cPlayer1.GetAnimState();
	}
	if (nIndex == 2)
	{
		m_cPlayer2.GetPosition(&result.fX, &result.fY, &result.fZ);
		result.fAngle = m_cPlayer2.GetAngle();
		result.eAnimState = m_cPlayer2.GetAnimState();
	}
	sprintf_s(result.szRoomName, "%s", "FROM SERVER",11);

	return result;
}

int cContainer::GetOnlineUser()
{
	int nResult = 0;

	if (m_nPlayer1Time + (ONE_SECOND * 5) > clock())
	{
		nResult = nResult | (OUT_PLAYER1);
		cout << "1P 접속 확인" << endl;
	}
	if (m_nPlayer2Time + (ONE_SECOND * 5) > clock())
	{
		nResult = nResult | (OUT_PLAYER2);
		cout << "2P 접속 확인" << endl;
	}
		
	return nResult;
}

void cContainer::SaveData()
{
	// << : 폴더 없는 상황 예외처리
	string szFullPath = "Server/" + m_sRoomName + ".txt";
	ofstream outFile(szFullPath.data(), ios::trunc);
	if (!outFile.is_open())
	{
		char strFolderPath[] = "Server";
		int nResult = _mkdir(strFolderPath);
		if (nResult == 0)
			cout << "폴더 생성 성공" << endl;
		else if (nResult == -1)
		{
			perror("폴더 생성 실패 - 폴더가 이미 있거나 부정확함 \n");
			cout << "errorno :" << errno << endl;
		}
		outFile.open(szFullPath.data(), ios::trunc);
	}

	// << : 데이터 저장
	float x, y, z, angle;

	m_cPlayer1.GetPosition(&x, &y, &z);
	angle = m_cPlayer1.GetAngle();
	outFile << "Player1 X " << x << endl;
	outFile << "Player1 Y " << y << endl;
	outFile << "Player1 Z " << z << endl;
	outFile << "Player1 Angle " << angle << endl;

	m_cPlayer2.GetPosition(&x, &y, &z);
	angle = m_cPlayer2.GetAngle();
	outFile << "Player2 X " << x << endl;
	outFile << "Player2 Y " << y << endl;
	outFile << "Player2 Z " << z << endl;
	outFile << "Player2 Angle " << angle << endl;

	outFile.close();
}

void cContainer::SetDefault()
{
	m_cPlayer1.SetX(0);
	m_cPlayer1.SetY(0);
	m_cPlayer1.SetZ(0);
	m_cPlayer1.SetAngle(0);

	m_cPlayer2.SetX(0);
	m_cPlayer2.SetY(0);
	m_cPlayer2.SetZ(0);
	m_cPlayer2.SetAngle(0);
}

void cContainer::Update()
{
}

