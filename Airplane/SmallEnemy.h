#pragma once
#include "GameRole.h"

class CSmallEnemy : public CGameRole
{
public:
	CSmallEnemy::CSmallEnemy(int nRow, int nCol);
	~CSmallEnemy();

	void ShowClear();				// �ڸǽ�ɫ
	void Show();					// ��ʾ��ɫ
	void ShowClearLife();			// �ڸǽ�ɫѪ��
	void ShowLife();				// ��ʾ��ɫѪ��
	void ShowBoom();				// ��ʾС�л���ը
	void GetNew();					// ��ȡ�µ�
	void MoveDown();				//����		
};

