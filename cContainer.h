#pragma once
#include "cPlayer.h"
#include "cStuff.h"
#define CONNECT_TIME 5
#define D3DX_PI 3.141592654f

class cContainer
{
private:
	string	m_sRoomName;		// 방이름
	cPlayer m_stMan;			// 남자 데이터
	cPlayer m_stWoman;			// 여자 데이터

	clock_t m_nManTime;			// 남자 최근 접속 시간
	clock_t m_nWomanTime;		// 여자 최근 접속 시간

	cStuff m_aStuff[SWITCH_LASTNUM];	// << : 오브젝트

	SYNTHESIZE(int, nPlayer1NetID, Player1NetID);
	SYNTHESIZE(int, nPlayer2NetID, Player2NetID);

	SYNTHESIZE(ST_SOCKET_ADDR, Player1Sock, Player1Sock);
	SYNTHESIZE(ST_SOCKET_ADDR, Player2Sock, Player2Sock);

	HANDLE hThread1P, hThread2P;
	
public:
	cContainer();
	~cContainer();

	ST_PLAYER_POSITION GetData(int nIndex);
	int GetOnlineUser();
	void GetManPosition(OUT float * x, OUT float * y, OUT float * z, OUT float * angle);
	void GetWomanPosition(OUT float * x, OUT float * y, OUT float * z, OUT float * angle);
	void GetMap(OUT float* X, OUT float* Y, OUT float* Z, OUT float* rotX, OUT float* rotY, OUT float* rotZ, OUT bool* IsRun);
	void Setup(string key)
	{
		m_sRoomName = key;
		string szFullPath = "Server/" + key + ".txt";
		char szBuffer[1000];

		char Key1[100] = { 0, };
		char Key2[100] = { 0, };
		char Key3Str[100] = { 0, };
		int Key3Int = 0;
		float Key4Float = 0;
		float Key4Int = 0;

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
			sscanf_s(szBuffer, "%s %s", &Key1, 100, &Key2, 100);
			if (strlen(szBuffer) <= 0) continue;

			if (string(Key1) == MAN)
				pTarget = &m_stMan;
			else if (string(Key1) == WOMAN)
				pTarget = &m_stWoman;

			if (pTarget == NULL) continue;

			if (string(Key2) == POSITION)
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
			else if (string(Key2) == INVENTORY_INDEX)
			{
				int Index = 0;
				int ItemType = 0;
				sscanf_s(szBuffer, "%*s %*s %d %d", &Index, &ItemType);
				pTarget->SetItem(Index, ItemType);
			}

			cout << " 파일 로딩 " << endl;
		}
	}
	void SaveData();
	void SetDefault();
	void Update();
	void UpdateData(ST_PLAYER_POSITION stRecv, ST_SOCKET_ADDR stAddr);
	void UpdateData(ST_PLAYER_POSITION stRecv);
};

