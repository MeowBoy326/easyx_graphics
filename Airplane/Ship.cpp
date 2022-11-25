#include "Ship.h"
#include "control.h"
#include "easyx.h"
#include "View.h"

CShip::CShip(int nRow, int nCol, int nLife)
{
	m_nRow = nRow;
	m_nCol = nCol;
	m_nLife = nLife;
}

CShip::~CShip()
{

}

void CShip::ShowClear()				// �ڸǷɴ�
{
	putimage(m_nRow, m_nCol, &ship1, SRCAND);
}

void CShip::ShowClearLife()			// �ڸǷɴ�Ѫ��
{
	setfillcolor(BLACK);
	fillrectangle(GAMEWIDTH / 2 - 50, GAMEHIGHT - 10, GAMEWIDTH / 2 - 50 + m_nLife, GAMEHIGHT - 5);
}

void CShip::ShowLife()				// ��ʾ�ɴ�Ѫ��
{
	setfillcolor(BLUE);
	fillrectangle(GAMEWIDTH / 2 - 50, GAMEHIGHT - 10, GAMEWIDTH / 2 - 50 + m_nLife, GAMEHIGHT - 5);
}

void CShip::GetHit()				// �ɴ��ܵ��˺�
{
	if (m_nLife > 0)
	{
		m_nLife -= 25;
	}
}

void CShip::Show()					// ��ʾ�ɴ�
{
	putimage(m_nRow, m_nCol, &ship, SRCPAINT);
}

void CShip::ShowBoom()				// ��ʾ��ը
{
	if (m_Boom >= 1 && m_Boom <= 3)
	{
		putimage(m_nRow, m_nCol, ship.getwidth(),
			ship.getheight(), &smallboom1, 0, 0);
	}

	if (m_Boom >= 4 && m_Boom <= 6)
	{
		putimage(m_nRow, m_nCol, ship.getwidth(),
			ship.getheight(), &smallboom2, 0, 0);
	}

	if (m_Boom >= 7 && m_Boom <= 9)
	{
		putimage(m_nRow, m_nCol, ship.getwidth(),
			ship.getheight(), &smallboom3, 0, 0);
	}

	if (m_Boom >= 10 && m_Boom <= 12)
	{
		putimage(m_nRow, m_nCol, ship.getwidth(),
			ship.getheight(), &smallboom4, 0, 0);
	}

	if (m_Boom == 14)
	{
		cleardevice();
		m_Boom = 15;
	}
}