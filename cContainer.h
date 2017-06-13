#pragma once
#include "cPlayer.h"
#include "cStuff.h"
#define CONNECT_TIME 5

class cContainer
{
private:
	string	m_sRoomName;		// ���̸�
	cPlayer m_cPlayer1;			// �÷��̾� 1 ������
	cPlayer m_cPlayer2;			// �÷��̾� 2 ������

	unsigned int m_nPlayer1Time;	// �÷��̾� 1 �ֱ� ���� �ð�
	unsigned int m_nPlayer2Time;	// �÷��̾� 2 �ֱ� ���� �ð�

	std::vector<cStuff> m_vecStuffPosition;	// << : ������Ʈ

	bool SwitchPlayer1;			// << : �÷��̾� 1 ����ġ
	bool SwitchPlayer2;			// << : �÷��̾� 2 ����ġ
public:
	cContainer();
	~cContainer();

	ST_PLAYER_POSITION GetData(int nIndex);
	int GetOnlineUser();
	void OnSwitch();
	void Setup(string key);
	void SaveData();
	void SetDefault();
	void UpdateData(ST_PLAYER_POSITION stRecv);
};

