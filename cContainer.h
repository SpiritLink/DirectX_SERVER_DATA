#pragma once
class cPlayer;
class cStuff;

class cContainer
{
private:
	string	m_sRoomName;		// ���̸�
	cPlayer m_cPlayer1;			// �÷��̾� 1 ������
	cPlayer m_cPlayer2;			// �÷��̾� 2 ������

	DWORD	m_dwPlayer1Time;	// �÷��̾� 1 �ֱ� ���� �ð�
	DWORD	m_dwPlayer2Time;	// �÷��̾� 2 �ֱ� ���� �ð�
public:
	cContainer();
	~cContainer();

	void Setup(string key);
	void UpdateData(ST_PLAYER_POSITION stRecv);
	void SaveData();
};

