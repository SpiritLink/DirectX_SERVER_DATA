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

	SYNTHESIZE(ST_SOCKET_ADDR, Player1Sock, Player1Sock);
	SYNTHESIZE(ST_SOCKET_ADDR, Player2Sock, Player2Sock);

	SYNTHESIZE(bool, SwitchAddr1P, SwitchAddr1P);	// << : ��뿡�� �ּҸ� �����ؾ� �ϴ°� ?
	SYNTHESIZE(bool, SwitchAddr2P, SwitchAddr2P);

	HANDLE hThread1P, hThread2P;
	
public:
	cContainer();
	~cContainer();

	ST_PLAYER_POSITION GetData(int nIndex);
	int GetOnlineUser();
	void Setup(string key);
	void SaveData();
	void SetDefault();
	void Update();
	void UpdateData(ST_PLAYER_POSITION stRecv, ST_SOCKET_ADDR stAddr);
	void UpdateData(ST_PLAYER_POSITION stRecv);
};

