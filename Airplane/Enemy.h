#pragma once
#include "easyx.h"
#include "control.h"
#include "GameRole.h"

class CEnemy :public CGameRole
{
public:
	CEnemy::CEnemy(int nRow, int nCol, int nLife);
	~CEnemy();
	
	char direction;		        // �л�����
	int m_nStartHight;			// �л���ʼ�߶�
	int m_Move;					// �л��ƶ�״̬
	int m_Fire;                 // �л������ӵ�״̬

	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void ShowClear();			// �ڸǵл�
	void Show();				// ���Ƶл�
	void ShowClearLife();		// �ڸǵл�Ѫ��
	void ShowLife();			// ��ʾ�л�Ѫ��
	void GetHit();				// �л��е�
	void ShowBoom();			// ��ʾ��ը	
};

