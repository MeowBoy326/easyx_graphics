#pragma once
#include "GameRole.h"

class CShip :public CGameRole
{
public:
	CShip(int nRow, int nCol, int nLife);
	~CShip();
	void ShowClear();				// �ڸǷɴ�
	void Show();					// ��ʾ�ɴ�
	void ShowClearLife();			// �ڸǷɴ�Ѫ��
	void GetHit();					// �ɴ��յ��˺�
	void ShowLife();				// ��ʾ�ɴ�Ѫ��
	void ShowBoom();                // ��ʾ��ը	
};


