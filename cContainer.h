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

	clock_t m_nPlayer1Time;	// �÷��̾� 1 �ֱ� ���� �ð�
	clock_t m_nPlayer2Time;	// �÷��̾� 2 �ֱ� ���� �ð�

	std::vector<cStuff> m_vecStuffPosition;	// << : ������Ʈ

	bool SwitchPlayer1;			// << : �÷��̾� 1 ����ġ
	bool SwitchPlayer2;			// << : �÷��̾� 2 ����ġ

	SOCKADDR_IN Player1Adr;		// << : �÷��̾� 1 �ּ�
	SOCKADDR_IN Player2Adr;		// << : �÷��̾� 2 �ּ�
public:
	cContainer();
	~cContainer();

	ST_PLAYER_POSITION GetData(int nIndex);
	int GetOnlineUser();
	void OnSwitch();
	void Setup(string key);
	void SaveData();
	void SetDefault();
	void UpdateData(ST_PLAYER_POSITION stRecv, SOCKADDR_IN stAddr);
};

