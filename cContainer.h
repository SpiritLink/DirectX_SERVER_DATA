#pragma once
#include "cPlayer.h"
#include "cStuff.h"
#define ONE_SECOND 1000

class cContainer
{
private:
	string	m_sRoomName;		// ���̸�
	cPlayer m_cPlayer1;			// �÷��̾� 1 ������
	cPlayer m_cPlayer2;			// �÷��̾� 2 ������

	DWORD	m_dwPlayer1Time;	// �÷��̾� 1 �ֱ� ���� �ð�
	DWORD	m_dwPlayer2Time;	// �÷��̾� 2 �ֱ� ���� �ð�

	// << : �����ۿ� ���� ������ ������ ������ �ʿ� (�ִ� ������ ���� 10��)
public:
	cContainer();
	~cContainer();

	void Setup(string key);
	void UpdateData(ST_PLAYER_POSITION stRecv);
	ST_PLAYER_POSITION GetData(int nIndex);
	int GetOnlineUser();
	void SaveData();
	void SetDefault();
};

