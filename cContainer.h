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

