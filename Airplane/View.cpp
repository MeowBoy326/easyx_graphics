#include "view.h"
#include "easyx.h"
#include "Enemy.h"
#include "SmallEnemy.h"

IMAGE boom1, boom2, boom3, boom4;
IMAGE smallboom1, smallboom2, smallboom3, smallboom4;

void LoadBoom()
{	
	loadimage(&boom1, _T("res\\boom\\boom1.png"));
	loadimage(&boom2, _T("res\\boom\\boom2.png"));
	loadimage(&boom3, _T("res\\boom\\boom3.png"));
	loadimage(&boom4, _T("res\\boom\\boom4.png"));

	loadimage(&smallboom1, _T("res\\boom\\smallboom1.png"));
	loadimage(&smallboom2, _T("res\\boom\\smallboom2.png"));
	loadimage(&smallboom3, _T("res\\boom\\smallboom3.png"));
	loadimage(&smallboom4, _T("res\\boom\\smallboom4.png"));
}

void InitGame()
{
	LoadBoom();
	mciSendString(_T("open res\\music.mp3 alias mysong"), NULL, 0, NULL);		// ������
	mciSendString(_T("play MySong repeat"), NULL, 0, NULL);         			// ѭ������

	// ��ʼ����ʼ���洰��
	loadimage(&background, _T("res\\sky2.jpg"), GAMEWIDTH, GAMEHIGHT, true);
	putimage(0, 0, &background);		// ��ʼ����

	setbkmode(TRANSPARENT);				// ����͸��
	settextcolor(BLUE);
	settextstyle(50, 20, _T("����"));
	outtextxy(GAMEWIDTH / 2 - 100, 20, _T("�ɻ���ս 1.0"));
	settextstyle(30, 20, _T("����"));
	outtextxy(GAMEWIDTH / 2 - 100, 280, _T("W��S��A��D �ƶ�"));
	outtextxy(GAMEWIDTH / 2 - 100, 320, _T("K �����ӵ�"));
	outtextxy(GAMEWIDTH / 2 - 100, 360, _T("�ո���ͣ"));
	outtextxy(GAMEWIDTH / 2 - 100, 400, _T("�����������"));
	outtextxy(GAMEWIDTH / 2 + 50, 440, _T(" BY LHX"));
	system("pause");
	cleardevice();

	// ���طɻ�
	loadimage(&ship, _T("res\\redship.png"));
	loadimage(&ship1, _T("res\\redship1.png"));

	// ���صл�
	loadimage(&enemy, _T("res\\enemy.png"));	
	loadimage(&enemy1, _T("res\\enemy1.png"));
	// ����С�л�
	loadimage(&smallenemy, _T("res\\smallenemy.png"));
	loadimage(&smallenemy1, _T("res\\smallenemy1.png"));

	myenemy.direction = DOWN;
	myenemy.m_nStartHight = 0;
	myenemy.m_Move = 0;
	myenemy.m_Fire = 0;
	myenemy.m_Boom = 0;	
}

void ShowBullet()
{
	// ��ʾ�ɴ��ӵ�
	for (Iter = VectorBullets.begin(); Iter != VectorBullets.end(); Iter++)
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
		(*Iter)->MoveUp();
		(*Iter)->ShowYellow();
	}

	// ��ʾ�л��ӵ�
	for (Iter = VectorEnenyBullets.begin(); Iter != VectorEnenyBullets.end(); Iter++)
	{
		if (VectorEnenyBullets.size() == 0)
		{
			break;
		}
		if (*Iter == nullptr)
		{
			break;
		}
		(*Iter)->ShowClear();
		(*Iter)->MoveDown();
		(*Iter)->ShowRed();
	}
}

void ShowInPut()
{
	if (myinput & UPINPUT)
	{
		myship.ShowClear();
	}

	if (myinput & DOWNINPUT)
	{
		myship.ShowClear();
	}

	if (myinput & LEFTINPUT)
	{
		myship.ShowClear();
	}

	if (myinput & RIGHTINPUT)
	{
		myship.ShowClear();
	}
}