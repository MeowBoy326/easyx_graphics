#pragma once

class CBullet
{
public:
	int m_nRow;
	int m_nCol;

	CBullet(int nRow, int nCol);
	void MoveUp();					
	void ShowYellow();
	void ShowClear();					// �����ӵ�
	void MoveDown();					// �ӵ�����
	void ShowRed();
};
