#include <conio.h>
#include <easyx.h>
#include "control.h"
#include "Enemy.h"
#include "view.h"
#include "SmallEnemy.h"
#include "GameControl.h"

CShip myship(GAMEWIDTH / 2 - 20, GAMEHIGHT - 60, 100);		// �ɴ�λ�ã�Ѫ��
CEnemy myenemy(GAMEWIDTH / 2 - 50, 0, 100);					// �л�λ�ã�Ѫ��
CSmallEnemy mysmallenemy(0 , 0);							// С�л�
CGameControl mygamecontrol;									// ��Ϸ����

IMAGE background, ship, ship1, enemy, enemy1, smallenemy, smallenemy1;
vector<CBullet*> VectorBullets;
vector<CBullet*> VectorEnenyBullets;
vector<CBullet*>::iterator Iter;
vector<CGameRole*> RoleVector;

clock_t ClkMakeBulletStart = clock();
clock_t ClkMakeBulletFinish = clock();						// �ɴ������ӵ�

bool GameOver()
{
	// �ɻ��͵�����ײ
	if (((myship.m_nRow >= myenemy.m_nRow) && (myship.m_nRow <= myenemy.m_nRow + enemy.getwidth()))
		&& ((myship.m_nCol <= myenemy.m_nCol + enemy.getheight()) && ((myship.m_nCol >= myenemy.m_nCol))))
	{
		return true;
	}

	// �л������±�Ե
	if (myenemy.m_nCol + enemy.getheight() > GAMEHIGHT)
	{
		return true;
	}

	// �ɴ�Ѫ��Ϊ0
	if (myship.m_nLife <= 0)
	{
		if (myship.m_Boom == 15)
		{
			return true;
		}
		if (myship.m_Boom == 0)
		{
			myship.m_Boom = 1;
		}	
	}
	return false;
}

int HandleGameOver()
{
	if (GameOver())
	{
		mciSendString(_T("close MySong"), NULL, 0, NULL);
		
		// �������
		for (size_t i = 0; i < VectorBullets.size(); i++)
		{
			VectorBullets.pop_back();
		}

		// �������
		for (size_t i = 0; i < VectorEnenyBullets.size(); i++)
		{
			VectorEnenyBullets.pop_back();
		}
		
		cleardevice();

		// ��Ϸ������ʾ
		mygamecontrol.ShowScore();
		setbkmode(TRANSPARENT);			// ����͸��
		settextcolor(RED);	
		settextstyle(40, 30, _T("����"));
		outtextxy(GAMEWIDTH / 2 - 140, 20, _T("GAME OVER"));
		outtextxy(GAMEWIDTH / 2 - 80, 80, _T("loser!"));
		outtextxy(GAMEWIDTH / 2 - 180, 140, _T("��ײ���˵л�"));
		outtextxy(GAMEWIDTH / 2 - 30, 200, _T("or"));
		outtextxy(GAMEWIDTH / 2 - 180, 260, _T("�ɴ�Ѫ��Ϊ0"));	
		outtextxy(GAMEWIDTH / 2 - 160, 320, _T("ESC�˳�"));
		outtextxy(GAMEWIDTH / 2 - 160, 380, _T("R���¿�ʼ"));
		while (_kbhit())
		{
			_getch();
		}

		char chInPut = '\0';
		chInPut = _getch();

		if (chInPut == 'R' || chInPut == 'r')
		{
			return -2;
		}
		if (chInPut == 27)
		{
			return -1;
		}
	}
	return 1;
}

int myinput = NOINPUT;

void GetOrder()
{	
	ClkMakeBulletFinish = clock();		// �ɴ��ӵ�����ʱ���
	
	if (GetAsyncKeyState('W') & 0x8000)
	{
		myinput |= UPINPUT;
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		myinput |= DOWNINPUT;
	}

	if (GetAsyncKeyState('A') & 0x8000)
	{
		myinput |= LEFTINPUT;
	}

	if (GetAsyncKeyState('D') & 0x8000)
	{
		myinput |= RIGHTINPUT;
	}
	
	if (GetAsyncKeyState('K') & 0x8000 && (ClkMakeBulletFinish - ClkMakeBulletStart > 200))
	{
		// �ɴ��ӵ�
		myinput |= FIREINPUT;
		ClkMakeBulletStart = ClkMakeBulletFinish;
	}

	if (GetAsyncKeyState(' ') & 0x8000)
	{
		myinput |= SPACEINPUT;
	}

	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		myinput |= ESCINPUT;
	}
}

void DealInPut()
{
	if ((myinput & UPINPUT) && (myship.m_nCol >= 10))
	{
		myship.m_nCol -= 2;
	}

	if ((myinput & DOWNINPUT) && (myship.m_nCol <= GAMEHIGHT - ship.getheight() - 10))
	{
		myship.m_nCol += 2;
	}

	if ((myinput & LEFTINPUT) && (myship.m_nRow >= 10))
	{
		myship.m_nRow -= 2;
	}

	if ((myinput & RIGHTINPUT) && (myship.m_nRow <= GAMEWIDTH - ship.getwidth() - 10))
	{
		myship.m_nRow += 2;
	}

	if (myinput & FIREINPUT)
	{
		CBullet* pNewBullet = new CBullet(myship.m_nRow + ((ship.getwidth() / 2)), myship.m_nCol - 5);
		VectorBullets.push_back(pNewBullet);
	}

	if (myinput & SPACEINPUT)
	{
		_getch();
	}

	if (myinput & ESCINPUT)
	{
		exit(0);
	}

	myinput = NOINPUT;	
}

void EnemyMove()
{
	// �ڸǵл�
	myenemy.ShowClear();

	// �ڸǵл���Ѫ��
	myenemy.ShowClearLife();

	if (myenemy.m_Move % 10 == 0)
	{
		cleardevice();
		if (myenemy.m_nCol < 0)
		{
			myenemy.MoveDown();
		}

		if (myenemy.direction == DOWN)
		{
			myenemy.MoveDown();
			
			if (myenemy.m_nCol >= myenemy.m_nStartHight + 20)
			{
				myenemy.direction = Right;
			}
		}

		if (myenemy.direction == Right)
		{
			myenemy.MoveRight();

			if (myenemy.m_nRow >= GAMEWIDTH - enemy.getwidth())
			{
				myenemy.direction = Left;
			}
		}

		if (myenemy.direction == Left)
		{
			myenemy.MoveLeft();

			if (myenemy.m_nRow <= 0)
			{
				myenemy.direction = DOWN;
				myenemy.m_nStartHight = myenemy.m_nCol;
			}
		}				
		// �ڸ�С�л�
		mysmallenemy.ShowClear();
		
		// ���С�л����Զ�����
		if (mysmallenemy.m_Boom == 0)
		{
			mysmallenemy.MoveDown();
		}		
	}
}

void MakeEnemyBullet()
{
	if (myenemy.m_Fire % 50 ==  0)
	{
		// ����л��ӵ�
		CBullet * pNewEnemyBullet = new CBullet((myenemy.m_nRow + enemy.getwidth() / 2), myenemy.m_nCol + enemy.getheight());
		VectorEnenyBullets.push_back(pNewEnemyBullet);
	}
}

void DeleteMemory()
{
	// �ɴ��ӵ����ϱ߽��ͷ�
	for (vector<CBullet*>::iterator Iter = VectorBullets.begin(); Iter != VectorBullets.end();)
	{
		if (VectorBullets.size() == 0)
		{
			break;
		}
		if (*Iter == nullptr)
		{
			break;
		}
		if ((*Iter)->m_nCol < 0)
		{
			(*Iter)->ShowClear();
			delete *Iter;
			*Iter = nullptr;
			VectorBullets.erase(Iter);
			Iter = VectorBullets.begin();
		}

		if (VectorBullets.size() != 0)
		{
			Iter++;
		}
	}

	// �л��ӵ����ײ��ͷ�
	for (vector<CBullet*>::iterator Iter = VectorEnenyBullets.begin(); Iter != VectorEnenyBullets.end();)
	{	
		if (VectorEnenyBullets.size() == 0)
		{
			break;
		}
		if (*Iter == nullptr)
		{
			break;
		}
		if ((*Iter)->m_nCol > GAMEHIGHT)
		{
			(*Iter)->ShowClear();
			delete *Iter;
			*Iter = nullptr;
			VectorEnenyBullets.erase(Iter);
			Iter = VectorEnenyBullets.begin();
		}

		if (VectorEnenyBullets.size() != 0)
		{
			Iter++;
		}
	}
}

void IsEnenmyHurt()
{
	// �жϵл��Ƿ��е�
	for (vector<CBullet*>::iterator Iter = VectorBullets.begin(); Iter != VectorBullets.end(); Iter++)
	{
		if (VectorBullets.size() == 0)
		{
			break;
		}
		if (*Iter == nullptr)
		{
			break;
		}
		if (((*Iter)->m_nRow >= myenemy.m_nRow && (*Iter)->m_nRow <= myenemy.m_nRow + enemy.getwidth())
			&& ((*Iter)->m_nCol <= myenemy.m_nCol + enemy.getheight() && (*Iter)->m_nCol >= myenemy.m_nCol))
		{
			if (VectorBullets.size() == 0)
			{
				break;
			}
			if (*Iter == nullptr)
			{
				break;
			}
			(*Iter)->ShowClear();
			delete *Iter;
			*Iter = nullptr;
			VectorBullets.erase(Iter);
			Iter = VectorBullets.begin();
			// �ڸǵл�Ѫ��
			myenemy.ShowClearLife();
			// �л�����Ѫ����5
			myenemy.GetHit();
			break;
		}
	}
}

void IsShipHurt()
{
	// �жϷɴ��Ƿ��е�	
	for (vector<CBullet*>::iterator Iter = VectorEnenyBullets.begin(); Iter != VectorEnenyBullets.end(); Iter++)
	{
		if (VectorEnenyBullets.size() == 0)
		{
			break;
		}
		if (*Iter == nullptr)
		{
			break;
		}
		if (((*Iter)->m_nRow >= myship.m_nRow && (*Iter)->m_nRow <= myship.m_nRow + ship.getwidth())
			&& ((*Iter)->m_nCol <= myship.m_nCol + ship.getheight() && (*Iter)->m_nCol >= myship.m_nCol))
		{
			(*Iter)->ShowClear();
			delete *Iter;
			*Iter = nullptr;
			VectorEnenyBullets.erase(Iter);
			Iter = VectorEnenyBullets.begin();

			// �ڸǷɴ�Ѫ��		
			myship.ShowClearLife();		
			myship.GetHit();
			cleardevice();
			if (VectorEnenyBullets.size() == 0)
			{
				break;
			}
		}
	}
}

void SmallHitShip()
{
	// �ж�С�л��Ƿ�ײ���ɴ���ײ����ɴ�Ѫ�����٣�С�л���ʧ�ؽ�
	if (((myship.m_nRow + (ship.getwidth() / 2) >= mysmallenemy.m_nRow) && (myship.m_nRow <= mysmallenemy.m_nRow + smallenemy.getwidth()))
		&& ((myship.m_nCol <= mysmallenemy.m_nCol + smallenemy.getheight()) && ((myship.m_nCol >= mysmallenemy.m_nCol))))
	{
		// �ڸ�С�л�
		mysmallenemy.ShowClear();

		// ������С�л�
		mysmallenemy.m_nRow = rand() % (GAMEWIDTH - smallenemy.getwidth());
		mysmallenemy.m_nCol = 0;

		// �ڸǷɴ�Ѫ��
		myship.ShowClearLife();
		// �ɴ�Ѫ������
		myship.GetHit();
		cleardevice();
	}
}

bool IsBullertHitSmall()
{
	// С�л����ٴβ��������е����ߵ�����Ļ�ײ�
	for (vector<CBullet*>::iterator Iter = VectorBullets.begin(); Iter != VectorBullets.end(); Iter++)
	{
		if (VectorBullets.size() == 0)
		{
			break;
		}
		if (*Iter == nullptr)
		{
			break;
		}
		if (((*Iter)->m_nRow >= mysmallenemy.m_nRow && (*Iter)->m_nRow <= mysmallenemy.m_nRow + smallenemy.getwidth())
			&& ((*Iter)->m_nCol <= mysmallenemy.m_nCol + smallenemy.getheight() && (*Iter)->m_nCol >= mysmallenemy.m_nCol))
		{
			(*Iter)->ShowClear();
			delete *Iter;
			*Iter = nullptr;
			VectorBullets.erase(Iter);
			if (mysmallenemy.m_Boom == 0)
			{
				mysmallenemy.m_Boom = 1;
			}
			mygamecontrol.m_nScore += 10;
			return true;
		}
	}
	return false;
}

bool SmallHitLow()
{
	if (mysmallenemy.m_nCol >= GAMEHIGHT)
	{
		return true;
	}
	return false;
}

void GetNewShip()
{
	// �����·ɴ�
	myship.m_nRow = GAMEWIDTH / 2 - 20;
	myship.m_nCol = GAMEHIGHT - 60;
	myship.m_nLife = 100;
	myship.m_Boom = 0;
}

void GetNewSmallEnemy()
{
	// ������С�л�
	mysmallenemy.m_nRow = rand() % (GAMEWIDTH - smallenemy.getwidth());
	mysmallenemy.m_nCol = 0;
	mysmallenemy.m_Boom = 0;
}

void GetNewEnemy()
{
	// �л��ݻٺ��½�һ���л�
	// �����µл�
	setfillcolor(BLACK);
	solidrectangle(myenemy.m_nRow, myenemy.m_nCol - 10, myenemy.m_nRow + myenemy.m_nLife, myenemy.m_nCol - 5);
	myenemy.m_nRow = rand() % (GAMEWIDTH - enemy.getwidth());
	myenemy.m_nCol = -enemy.getheight();

	myenemy.m_nLife = 100;
	myenemy.direction = DOWN;
	myenemy.m_nStartHight = myenemy.m_nCol;
	myenemy.m_Boom = 0;
	myenemy.m_Move = 0;
	myenemy.m_Fire = 0;
}

void HpSleep(int ms)
{
	static clock_t ClkGameFinish = clock();
	ClkGameFinish += ms*CLOCKS_PER_SEC / 1000;

	if (clock() > ClkGameFinish)
	{
		ClkGameFinish = clock();
	}
	else
	{
		while (clock() < ClkGameFinish)
		{
			Sleep(1);
		}
	}
}

void HandleBoom()
{
	if (myenemy.m_Boom >= 1 && myenemy.m_Boom <= 14)
	{
		myenemy.m_Boom++;
	}

	if (mysmallenemy.m_Boom >= 1 && mysmallenemy.m_Boom <= 13)
	{
		mysmallenemy.m_Boom++;
	}

	// ����µл�
	if (myenemy.m_nLife <= 0 && myenemy.m_Boom == 15)
	{
		cleardevice();
		GetNewEnemy();					
	}

	// �л���ը��ʼ����
	if (myenemy.m_nLife <= 0 && myenemy.m_Boom == 0)
	{
		mygamecontrol.m_nScore += 100;
		myenemy.m_Boom = 1;
	}

	if (mysmallenemy.m_Boom == 0 && SmallHitLow() == true)
	{
		GetNewSmallEnemy();
	}

	if (mysmallenemy.m_Boom == 14)
	{
		// ������С�л�
		GetNewSmallEnemy();
	}

	// ��ʾ�л��ͷɴ�
	if (myenemy.m_Boom == 0)
	{
		myenemy.Show();
	}

	// ��ʾ���С�л�		
	if (mysmallenemy.m_Boom == 0)
	{
		mysmallenemy.Show();
	}
	
	if (myship.m_Boom >= 1 && myship.m_Boom <= 13)
	{
		myship.m_Boom++;
	}
		
	myenemy.m_Move++;
	myenemy.m_Fire++;
}