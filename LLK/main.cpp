/************************************************************************
*
*	��������������
*	by��xiongfj(837943056@qq.com)
*
*	�� 0�����������ֺ����߰�����Ч��������
*	�� 1���ռ���QQ����ŭ��С��ֲ���ս��ʬ��ϲ���󡢻�����������ͼ����
*	�� 2��vc++6.0	&&	graphics.h(201206)
*	�� 3������޸� 2012-09-26
*
************************************************************************/

#include <graphics.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>			// for PlaySound() / mciSendString() ����
#pragma comment (lib, "winmm.lib")
#include "LLK.h"

// ��������
#define GLENGTH		40			// ���ӳ�
#define GWIDTH		30			// ���ӿ�

#define PLENGTH		36			// Img ��Сͼ����ʵ�ʳ���
#define PWIDTH		28			// Img ��Сͼ����ʵ�ʿ��

#define BIGL		40			// Img ���ͼ����ʵ�ʿ�
#define BIGW		50			// Img ���ͼ����ʵ�ʿ�

enum Kind { QQ, BIRD, PLANT, PET, SHEEP, KAVAI, ALL };				// ͼ������

// ix, iy ��ʾ��ͼ���� Img ���������
struct IMG
{
	int ix, iy;
}ixy[19][12];

// ��������
IMAGE Img, Img2;								// load ͼ��
ExMessage m;
Kind kind = PET;								// ͼ������
HWND hwnd;

bool game;										// ��Ϊѭ��������
TCHAR c, bom[10], ref[10], snum[10], mark[10];	// �����������ʣ��ը����ˢ�¡�ͼ�� / ����
TCHAR n[10];										// ����ؿ�
int xy[19][12], F = 1;							// ����״̬��ÿ�� F ��Ӧ Map() �����һ����ͼ
int x, y, i;									// for ѭ��
int t1, t2, tx, T = 300;						// ���ʱ�䡢ʱ�����߶����
int mhitnum = 0;								// ��¼�������
int mx1, my1, mx2 = -20, my2 = -20;				// -20 ��Ϊ�˽��ó�ʼֵ��Ч���ŵ���Ļ֮��
int bomb, refr, SNum, Mark;						// ����ը����ˢ�¡�ʣ��ͼ���� / ��ǰ����ֵ
int bkcolor = RGB(212, 164, 72);				// ���� setbkcolor() ����
int r = 212, g = 164, b = 72;					// ���� InputBox ת���������
int s;											// ����ѡ�񱳾�����



// ��������
void Frame();											// ��Ϸ��ʼ����Ϣ
void Putimg(int, Kind);									// ���ͼ��
void Start();											// ��ʼ����
void LButton();											// �������
void Clear(int, int, int bx, int by);					// ����ͼ��
void Bomb();											// ը������
void Refresh();											// ˢ��ͼ��
void Time();											// ������Ϸʱ��
void ChangeBk();										// ���ñ���ɫ����
void Draw();											// �ú������������Ļ��Ϣ (ʵʱ��Ϸ��Ϣ)
void Openmusic();
void Playmusic();
void Closemusic();
int  Maxx(int, int, int c = 0, int d = 0);				// ȡ���ֵ����ȡ��ߵ� y ���ϱߵ� x
int  Minn(int, int, int c = 0, int d = 0);				// ȡ��Сֵ����ȡ�ұߵ� y ���±ߵ� x
bool Check(int, int, int, int, bool, int);				// ���·�� �� �Ƿ����� 1 ����0 ����
bool GameOver();										// �����Ϸ�Ƿ����



// ������
void main()
{
	initgraph(800, 600, SHOWCONSOLE);
	loadimage(&Img, _T(".\\photo\\p.jpg"));
	loadimage(&Img2, _T(".\\photo\\introduction.jpg"));

	hwnd = GetHWnd();

	putimage(0, 0, &Img2);					// ��Ϸ�������
	_getch();
	mciSendString(_T("close 11"), 0, 0, 0);		// �ص� Welcome() �򿪵�����

	srand(time(0));							// ��������
	setorigin(50, 100);						// ����ԭ��
	Frame();								// ȷ����Ϸ��ܣ�����ͼ
	Start();								// ��Ϸ��ʼ

	closegraph();
}



// ����Ϸ����һЩ��ʼ������
void Frame()
{
	int num;				// ÿ�ֿ�ܿɷŵ�ͼ���� / 2
	Closemusic();

	// ��ʼ������
	tx = -45;				// ʱ�����ĳ�ʼ x ����λ��
	t1 = clock();			// ��Ϸ��ʼ��ʱ�������߶�ʱ����
	game = true;			// ��Ϸ���� or ����
	bomb = 5;				// ÿ���� 5 ��ը��
	refr = 5;				// ÿ���� 5 ��ˢ��
	Mark = 0;				// ��ʼ������

	// ÿ����Ϸ���¿�ʼ��Ҫ�ȹ�����Ϸ��
	for (x = 0; x < 19; x++)
		for (y = 0; y < 12; y++)
		{
			xy[x][y] = 0;
			ixy[x][y].ix = ixy[x][y].iy = 0;
		}

	if (F > 113)
	{
		MessageBox(hwnd, _T("�ף�����ǿ��ľ�е�ͼ�ˣ���ȥ��KAVAIģʽ�ɣ�"), _T("Notice"), MB_OK);
		F = 1;
	}

	// ���� 29 �غ�ÿ����΢�ӿ�ʱ�����ٶ�
	if (F > 29)
		T -= 2;

	// Map() �������� F ȷ��һ�ֵ�ͼ�����ظõ�ͼ��ͼ���� / 2
	num = Map(F, xy);

	SNum = 2 * num;		// SNum �������ʣ��ͼ����

	Draw();				// �ú������� Frame() ���ʼ���ĸ������ݣ���������ʵ����

	Putimg(num, kind);

	Openmusic();
	Playmusic();		// ���ű�������
}


// ��ʾ���ݡ���ʼ������ʾ���ݷֿ������Ա�����ʱ����Ҫ��ʼ���ĸ�����Ļ����ô�Ϳ��Ե������øú���
void Draw()
{
	setbkcolor(bkcolor);			// �ñ���ɫ�����Ż�ı�ԭ���ı���ɫ
	cleardevice();

	setfillstyle(RED);				// ʱ�������
	setcolor(RED);
	fillcircle(705, -87, 5);

	setcolor(0X00C78C);				// ��Ϸ���ο��
	setlinestyle(0, 6);
	rectangle(-6, -6, 575, 488);

	/******* ��������Ч�� *************/
	setfillstyle(BLACK);
	setcolor(0x90d2d2);
	setlinestyle(0, 2);

	rectangle(649, 6, 732, 29);	// ����
	rectangle(649, 56, 712, 79);	// ʣ��ͼ����
	rectangle(649, 106, 712, 129);	// ը��
	rectangle(649, 156, 712, 179);	// ˢ��
	rectangle(649, 206, 712, 229);	// ���
	rectangle(649, 256, 712, 279);	// С��
	rectangle(649, 306, 712, 329);	// ֲ��
	rectangle(649, 356, 712, 379);	// Ѽ��
	rectangle(649, 406, 712, 429);	// ��ͷ
	rectangle(649, 456, 712, 479);	// kavai

	bar(650, 7, 730, 27);
	bar(650, 57, 710, 77);
	bar(650, 107, 710, 127);
	bar(650, 157, 710, 177);
	bar(650, 207, 710, 227);
	bar(650, 257, 710, 277);
	bar(650, 307, 710, 327);
	bar(650, 357, 710, 377);
	bar(650, 407, 710, 427);
	bar(650, 457, 710, 477);
	/***********************************/


	setcolor(BLUE);
	setfillstyle(BLUE);
	outtextxy(600, 10, _T("���֣�"));
	outtextxy(600, 60, _T("ʣ�ࣺ"));

	// ������
	fillcircle(590, 42, 3);
	fillcircle(590, 92, 3);
	line(590, 42, 730, 42);
	line(590, 92, 710, 92);


	/******* ��ʾ����ť *********************************/
	setcolor(0x00aaff);
	setbkmode(TRANSPARENT);


	_stprintf_s(mark, _T("%08d"), Mark);		// ������
	outtextxy(662, 10, mark);

	_stprintf_s(snum, _T("%03d"), SNum);		// ʣ��ͼ����
	outtextxy(667, 60, snum);

	putimage(600, 100, PWIDTH, PLENGTH, &Img, 21 * PWIDTH, 0 * PLENGTH);		// ը����
	_stprintf_s(bom, _T("%02d"), bomb);
	outtextxy(672, 110, bom);

	putimage(600, 150, PWIDTH, PLENGTH, &Img, 31 * PWIDTH, 0 * PLENGTH);		// ˢ����
	_stprintf_s(ref, _T("%02d"), refr);
	outtextxy(672, 160, ref);

	putimage(600, 200, PWIDTH, PLENGTH, &Img, 2 * PWIDTH, 5 * PLENGTH);		// �ۿ�ģʽ
	outtextxy(672, 210, ref);

	putimage(600, 250, PWIDTH, PLENGTH, &Img, 4 * PWIDTH, 5 * PLENGTH);		// С��ģʽ
	outtextxy(672, 260, ref);

	putimage(600, 300, PWIDTH, PLENGTH, &Img, 6 * PWIDTH, 5 * PLENGTH);		// ֲ��ģʽ
	outtextxy(672, 310, ref);

	putimage(600, 350, PWIDTH, PLENGTH, &Img, 8 * PWIDTH, 5 * PLENGTH);		// ����ģʽ
	outtextxy(672, 360, ref);

	putimage(600, 400, PWIDTH, PLENGTH, &Img, 10 * PWIDTH, 5 * PLENGTH);		// ��ͷģʽ
	outtextxy(672, 410, ref);

	putimage(600, 450, PWIDTH, PLENGTH, &Img, 12 * PWIDTH, 5 * PLENGTH);		// ������ģʽ
	outtextxy(672, 460, ref);
	/******* ��ʾ����ť *********************************/


		/********* ��ʾ����ť*********/
	putimage(-10, -60, BIGW, BIGL, &Img, 0 * 50, 6 * PLENGTH);		// ����ɫ����

	putimage(70, -60, BIGW, BIGL, &Img, 2 * 50, 6 * PLENGTH);		// ��һ��

	putimage(150, -60, BIGW, BIGL, &Img, 4 * 50, 6 * PLENGTH);		// �ر���Ϸ

	putimage(330, -60, BIGW, BIGL, &Img, 6 * 50, 6 * PLENGTH);		// ��һ��

	putimage(590, -60, BIGW, BIGL, &Img, 8 * 50, 6 * PLENGTH);		// ALL ģʽ

	setcolor(BLUE);
	outtextxy(230, -55, _T("��"));			// ��ǰ�ؿ�
	_stprintf_s(n, _T("%03d"), F);
	outtextxy(255, -55, n);
	outtextxy(290, -55, _T("��"));
	/********* ��ʾ����ť*********/
}



// �Ŷ���ͼ�� (num * 2) �Լ��ź���ͼ�� (k)
void Putimg(int num, Kind k)
{
	int x1, y1, x2, y2;
	int srcx, srcy;		// �Ӷ��� Img ��ȡͼƬ�����Ͻ�����

	// ѭ�� num �κ��������λ��
	for (i = 0; i < num; i++)
	{
		// ѡȡһ������� -1 λ��
		do
		{
			x1 = rand() % 19;
			y1 = rand() % 12;
		} while (xy[x1][y1] != -1);

		// ѡȡ�ڶ������ -1 λ��
		do
		{
			x2 = rand() % 19;
			y2 = rand() % 12;
		} while (xy[x2][y2] != -1 || (x1 == x2 && y1 == y2)); // ɨ�����ͼ

		if (k == ALL)					// ���Ҫ������������ѡȡ
		{
			srcy = rand() % 5;
			switch (srcy)
			{
			case 0:	srcx = rand() % 33;	break;
			case 1:	srcx = rand() % 31;	break;
			case 2:	srcx = rand() % 25;	break;
			case 3:	srcx = rand() % 22;	break;
			case 4:	srcx = rand() % 39;	break;
			default:	break;
			}
		}

		// �� Img �����ȡ�� 0 �С�0~32 �����ͼ��
		if (k == QQ)
		{
			srcy = 0;
			srcx = rand() % 33;
		}

		// �� 1 �е� 0~13 ΪС��ͼ��
		if (k == BIRD)
		{
			srcy = 1;
			srcx = rand() % 14;
		}

		// �� 1 �е� 14~30 Ϊֲ��ͼ��
		if (k == PLANT)
		{
			srcy = 1;
			srcx = rand() % 17 + 14;
		}

		// �� 2 �е� 0~24 Ϊ����ͼ��
		if (k == PET)
		{
			srcy = 2;
			srcx = rand() % 25;
		}

		// �� 3 �е� 0~21 Ϊ��ͷͼ��
		if (k == SHEEP)
		{
			srcy = 3;
			srcx = rand() % 22;
		}

		// �� 4 �е� 0~38 ΪKAVAI ͼ��
		if (k == KAVAI)
		{
			srcy = 4;
			srcx = rand() % 39;
		}

		// ���������λ�÷���ͬ����ͼ��
		putimage(x1 * GWIDTH + 1, y1 * GLENGTH + 1, PWIDTH, PLENGTH, &Img, srcx * PWIDTH, srcy * PLENGTH);
		putimage(x2 * GWIDTH + 1, y2 * GLENGTH + 1, PWIDTH, PLENGTH, &Img, srcx * PWIDTH, srcy * PLENGTH);

		xy[x1][y1] = xy[x2][y2] = -2;	// -2 ��ʾ����ͼ����λ��

		// ��ͼ���� Img �����λ�������� ixy[][] һһ��Ӧ
		ixy[x1][y1].ix = ixy[x2][y2].ix = srcx + 1;	// ��ֹ = 0
		ixy[x1][y1].iy = ixy[x2][y2].iy = srcy + 1;
	}
}



// ��ʼ��Ϸ
void Start()
{
	while (game)
	{
		t2 = clock();

		// ���߶���ʱ����
		if (t2 - t1 > T)
		{
			if (tx == 570)
			{
				setcolor(0);
				outtextxy(685, -75, _T("Warning"));
				setcolor(LIGHTGREEN);
			}
			else
				setcolor(LIGHTGREEN);

			setlinestyle(PS_SOLID, 1);
			line(tx, -90, tx, -85);
			tx++;
			t1 = t2;
		}

		if (peekmessage(&m))
		{
			switch (m.message)
			{
			case WM_LBUTTONDOWN:
				LButton();			// �����������
				break;
			case WM_LBUTTONUP:

				// ��Щ��Ϊ���ڵ����ù�󱣳ְ�ťЧ��
				if (m.x >= 650 && m.x <= 680 && m.y >= 200 && m.y <= 240)
					putimage(600, 100, PWIDTH, PLENGTH, &Img, 21 * PWIDTH, 0 * PLENGTH);	// ����ը��

				if (m.x >= 650 && m.x <= 680 && m.y >= 250 && m.y <= 290)
					putimage(600, 150, PWIDTH, PLENGTH, &Img, 31 * PWIDTH, 0 * PLENGTH);	// ����ˢ��

				if (m.x >= 650 && m.x <= 680 && m.y >= 300 && m.y <= 340)
					putimage(600, 200, PWIDTH, PLENGTH, &Img, 2 * PWIDTH, 5 * PLENGTH);		// ����ۿ�

				if (m.x >= 650 && m.x <= 680 && m.y >= 350 && m.y <= 390)
					putimage(600, 250, PWIDTH, PLENGTH, &Img, 4 * PWIDTH, 5 * PLENGTH);		// ����С��

				if (m.x >= 650 && m.x <= 680 && m.y >= 400 && m.y <= 440)
					putimage(600, 300, PWIDTH, PLENGTH, &Img, 6 * PWIDTH, 5 * PLENGTH);		// ����ֲ��

				if (m.x >= 650 && m.x <= 680 && m.y >= 450 && m.y <= 490)
					putimage(600, 350, PWIDTH, PLENGTH, &Img, 8 * PWIDTH, 5 * PLENGTH);		// �������

				if (m.x >= 650 && m.x <= 680 && m.y >= 500 && m.y <= 540)
					putimage(600, 400, PWIDTH, PLENGTH, &Img, 10 * PWIDTH, 5 * PLENGTH);	// ������ͷ

				if (m.x >= 650 && m.x <= 680 && m.y >= 550 && m.y <= 590)
					putimage(600, 450, PWIDTH, PLENGTH, &Img, 12 * PWIDTH, 5 * PLENGTH);	// ��������

				break;
			default:
				break;
			}
		}
		if (!GameOver())								// ����Ƿ���������ͼ��
			game = false;
		Sleep(5);
	}
}

/***************************************************
					m.x / m.y ���� setorigin() Ӱ�죡
					******************************************************************/

					// �������
void LButton()
{
	PlaySound(_T(".\\sound\\click.wav"), 0, SND_ASYNC);
	setlinestyle(PS_DASH, 1);
	setcolor(BLUE);

	// ���������� ALL ģʽ-------------
	if (m.x >= 640 && m.x <= 690 && m.y >= 40 && m.y <= 80)
	{
		putimage(590, -60, BIGW, BIGL, &Img, 9 * 50, 6 * PLENGTH);	// ����

		if (kind == ALL)
		{
			Plantsound(1);
			MessageBox(hwnd, _T("С�����ຣ�ޱߣ���ͷ�ǰ�"), _T("��ʾ"), MB_OK);
			putimage(590, -60, BIGW, BIGL, &Img, 8 * 50, 6 * PLENGTH);
			return;
		}

		if (MessageBox(hwnd, _T("�ף���������ʱ������׼���ˇ���"), _T("��ʾ"), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			Plantsound(1);
			kind = ALL;
			refr++;						// ���� ALL ģʽ����ˢ�´���
			Refresh();
		}
		putimage(590, -60, BIGW, BIGL, &Img, 8 * 50, 6 * PLENGTH);	// ����
	}

	// ������������һ�ذ�ť---------------
	if (m.x >= 380 && m.x <= 430 && m.y >= 40 && m.y <= 80)
	{
		putimage(330, -60, BIGW, BIGL, &Img, 7 * 50, 6 * PLENGTH);	// ����
		if (MessageBox(hwnd, _T("��ȷ��Ҫ�ص���һ����"), _T("��ʾ"), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			if (F > 1)
			{
				Qqsound(1);
				F--;
				Frame();
			}
			else
				MessageBox(hwnd, _T("�ף��Ѿ��ǵ�һ���ˡ�"), _T("��ʾ"), MB_OK | MB_ICONWARNING);
		}
		else
			putimage(330, -60, BIGW, BIGL, &Img, 6 * 50, 6 * PLENGTH);	// ������һ��
	}

	// ���������ǹر���Ϸ��ť--------------
	if (m.x >= 200 && m.x <= 250 && m.y >= 40 && m.y <= 80)
	{
		putimage(150, -60, BIGW, BIGL, &Img, 5 * 50, 6 * PLENGTH);		// ����
		if (MessageBox(hwnd, _T("��ȷ��Ҫ�ر���Ϸ��"), _T("��ʾ"), MB_YESNO | MB_ICONQUESTION) == IDYES)
			game = 0;
		else
			putimage(150, -60, BIGW, BIGL, &Img, 4 * 50, 6 * PLENGTH);	// ����ر�
	}

	// ������������һ�ذ�ť---------------
	if (m.x >= 120 && m.x <= 170 && m.y >= 40 && m.y <= 80)
	{
		putimage(70, -60, BIGW, BIGL, &Img, 3 * 50, 6 * PLENGTH);

		if (MessageBox(hwnd, _T("��ȷ��Ҫ������һ����"), _T("��ʾ"), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			Qqsound(1);
			F++;
			Frame();
		}
		else
			putimage(70, -60, BIGW, BIGL, &Img, 2 * 50, 6 * PLENGTH);	// ������һ��
	}
	// ���������Ǳ�����ɫ���ð�ť--------------
	if (m.x >= 40 && m.x <= 90 && m.y >= 40 && m.y <= 80)
	{
		putimage(-10, -60, BIGW, BIGL, &Img, 1 * 50, 6 * PLENGTH);		// ����
		ChangeBk();
	}

	// ����������ը������---------------
	if (m.x >= 650 && m.x <= 680 && m.y >= 200 && m.y <= 240)
	{
		putimage(600, 100, PWIDTH, PLENGTH, &Img, 0 * PWIDTH, 5 * PLENGTH);		// ����
		Bomb();
	}

	// ����������ˢ�µ���-----------------
	if (m.x >= 650 && m.x <= 680 && m.y >= 250 && m.y <= 290)
	{
		putimage(600, 150, PWIDTH, PLENGTH, &Img, 1 * PWIDTH, 5 * PLENGTH);		// ����
		Refresh();
	}

	// ���������ǿۿ�ģʽ------------------
	if (m.x >= 650 && m.x <= 680 && m.y >= 300 && m.y <= 340)
	{
		putimage(600, 200, PWIDTH, PLENGTH, &Img, 3 * PWIDTH, 5 * PLENGTH);		// ����

		if (kind == QQ)
		{
			Qqsound(1);
			MessageBox(hwnd, _T("���ѣ���㲻�ǹ��У�"), _T("��ʾ"), MB_OK);
			putimage(600, 200, PWIDTH, PLENGTH, &Img, 2 * PWIDTH, 5 * PLENGTH);	// ����
			return;
		}

		if (refr < 1)						// ���ˢ���ù�
		{
			Diongsound();
			return;
		}

		if (IDYES == MessageBox(hwnd, _T("�Ǹ�ɶ��ż��ϵ���У�"), _T("Notice"), MB_YESNO | MB_ICONQUESTION))
		{
			Qqsound(1);
			kind = QQ;
			Refresh();
		}
		putimage(600, 200, PWIDTH, PLENGTH, &Img, 2 * PWIDTH, 5 * PLENGTH);		// ����
	}

	// ����������С��ģʽ------------------------
	if (m.x >= 650 && m.x <= 680 && m.y >= 350 && m.y <= 390)
	{
		putimage(600, 250, PWIDTH, PLENGTH, &Img, 5 * PWIDTH, 5 * PLENGTH);		// ����

		if (kind == BIRD)
		{
			Birdsound(1);
			MessageBox(hwnd, _T("�����ٵ��ҡ��Ҹ��㼱��"), _T("��ʾ"), MB_OK);
			putimage(600, 250, PWIDTH, PLENGTH, &Img, 4 * PWIDTH, 5 * PLENGTH);
			return;
		}

		if (refr < 1)						// ���ˢ���ù�
		{
			Diongsound();
			return;
		}

		if (IDYES == MessageBox(hwnd, _T("ɵ����������ս��ͷ��"), _T("Notice"), MB_YESNO | MB_ICONQUESTION))
		{
			Birdsound(1);
			kind = BIRD;
			Refresh();
		}
		putimage(600, 250, PWIDTH, PLENGTH, &Img, 4 * PWIDTH, 5 * PLENGTH);		// ����
	}

	// ����������ֲ��ģʽ---------------------
	if (m.x >= 650 && m.x <= 680 && m.y >= 400 && m.y <= 440)
	{
		putimage(600, 300, PWIDTH, PLENGTH, &Img, 7 * PWIDTH, 5 * PLENGTH);		// ����

		if (kind == PLANT)
		{
			Plantsound(1);
			MessageBox(hwnd, _T("�𼱣���ʬ�����ˣ�"), _T("Notice"), MB_OK);
			putimage(600, 300, PWIDTH, PLENGTH, &Img, 6 * PWIDTH, 5 * PLENGTH);	// ����
			return;
		}

		if (refr < 1)						// ���ˢ���ù�
		{
			Diongsound();
			return;
		}

		if (IDYES == MessageBox(hwnd, _T("Are You ���Ҫ��ս��ʬ��"), _T("Notice"), MB_YESNO | MB_ICONQUESTION))
		{
			Plantsound(1);
			kind = PLANT;
			Refresh();
		}
		putimage(600, 300, PWIDTH, PLENGTH, &Img, 6 * PWIDTH, 5 * PLENGTH);		// ����
	}

	// ����������Ѽ��ģʽ-----------------------
	if (m.x >= 650 && m.x <= 680 && m.y >= 450 && m.y <= 490)
	{
		putimage(600, 350, PWIDTH, PLENGTH, &Img, 9 * PWIDTH, 5 * PLENGTH);		// ����

		if (kind == PET)
		{
			Petsound(1);
			MessageBox(hwnd, _T("�ף���СѼ�����ٱ���ˣ�"), _T("Notice"), MB_OK);
			putimage(600, 350, PWIDTH, PLENGTH, &Img, 8 * PWIDTH, 5 * PLENGTH);	// ����
			return;
		}

		if (refr < 1)						// ���ˢ���ù�
		{
			Diongsound();
			return;
		}

		if (IDYES == MessageBox(hwnd, _T("�ף�����ֻ��һֻѼ��"), _T("Notice"), MB_YESNO | MB_ICONQUESTION))
		{
			Petsound(1);
			kind = PET;
			Refresh();
		}
		putimage(600, 350, PWIDTH, PLENGTH, &Img, 8 * PWIDTH, 5 * PLENGTH);		// ����
	}

	// ������������ͷģʽ-------------------------
	if (m.x >= 650 && m.x <= 680 && m.y >= 500 && m.y <= 540)
	{
		putimage(600, 400, PWIDTH, PLENGTH, &Img, 11 * PWIDTH, 5 * PLENGTH);		// ����

		if (kind == SHEEP)
		{
			Sheepsound(1);
			MessageBox(hwnd, _T("��̫�ǣ������ң�С���Ҵ���pp��"), _T("Notice"), MB_OK);
			putimage(600, 400, PWIDTH, PLENGTH, &Img, 10 * PWIDTH, 5 * PLENGTH);	// ����
			return;
		}

		if (refr < 1)						// ���ˢ���ù�
		{
			Diongsound();
			return;
		}

		if (IDYES == MessageBox(hwnd, _T("�ף�����ֻ��һֻ��"), _T("Notice"), MB_YESNO | MB_ICONQUESTION))
		{
			Sheepsound(1);
			kind = SHEEP;
			Refresh();
		}
		putimage(600, 400, PWIDTH, PLENGTH, &Img, 10 * PWIDTH, 5 * PLENGTH);		// ����
	}

	// ���������ǿ�����ģʽ-------------------------
	if (m.x >= 650 && m.x <= 680 && m.y >= 550 && m.y <= 590)
	{
		putimage(600, 450, PWIDTH, PLENGTH, &Img, 13 * PWIDTH, 5 * PLENGTH);		// ����

		if (kind == KAVAI)					// ����Ѿ��Ǹ�ģʽ
		{
			Kavaisound(1);
			MessageBox(hwnd, _T("�ף���֪�������������������������Tell Me(924553536@qq.com)"), _T("Notice"), MB_OK);
			putimage(600, 450, PWIDTH, PLENGTH, &Img, 12 * PWIDTH, 5 * PLENGTH);	// ����
			return;
		}

		if (refr < 1)						// ���ˢ���ù�
		{
			Diongsound();
			return;
		}

		if (IDYES == MessageBox(hwnd, _T("�������ˣ����Ļ�Զ��"), _T("Notice"), MB_YESNO | MB_ICONQUESTION))
		{
			Kavaisound(1);
			kind = KAVAI;
			Refresh();
		}
		putimage(600, 450, PWIDTH, PLENGTH, &Img, 12 * PWIDTH, 5 * PLENGTH);		// ����
	}

	// ����������Χ��ͼ������ ***********************
	if (m.x > 50 && m.x < 620 && m.y > 100 && m.y < 580)
	{
		if (mhitnum % 2 == 0)		// ����һ�μ�¼��m1
		{
			// �����ϴ������ʱ�����mx(y)2 �ĳ�ʼֵ -20 �Ѿ��ŵ���Ļ���ˡ�
			setcolor(getbkcolor());
			rectangle(mx2 * GWIDTH, my2 * GLENGTH, (mx2 + 1) * GWIDTH - 1, (my2 + 1) * GLENGTH - 2);

			mx1 = (m.x - 50) / 30;	// ������������������ڵĸ���
			my1 = (m.y - 100) / 40;	// ���������ֻȡ������������������

			setcolor(BLUE);			// ��ѡ�����
			rectangle(mx1 * GWIDTH, my1 * GLENGTH, (mx1 + 1) * GWIDTH - 1, (my1 + 1) * GLENGTH - 2);
		}
		else						// �ٵ���һ�μ�¼��m2
		{
			setcolor(getbkcolor());	// �����ϴ������ʱ�����
			rectangle(mx1 * GWIDTH, my1 * GLENGTH, (mx1 + 1) * GWIDTH - 1, (my1 + 1) * GLENGTH - 2);

			mx2 = (m.x - 50) / 30;
			my2 = (m.y - 100) / 40;

			setcolor(BLUE);			// ��ѡ�����
			rectangle(mx2 * GWIDTH, my2 * GLENGTH, (mx2 + 1) * GWIDTH - 1, (my2 + 1) * GLENGTH - 2);
		}
		mhitnum++;					// ������������������ mx(y)1�� mx(y)2

		// ����������������ͬλ�õ���ͬͼ��
		if (ixy[mx1][my1].ix == ixy[mx2][my2].ix
			&& ixy[mx1][my1].iy == ixy[mx2][my2].iy
			&& (mx1 != mx2 || my1 != my2)
			&& xy[mx1][my1] != 0 /*�����Ϊ�˱��������������հ�ͼ��*/)
		{
			// �����������������ڵ���ͬͼ��(�������ڡ���������)
			if ((Minn(mx1, mx2) + 1 == Maxx(mx1, mx2) && my1 == my2) || (mx1 == mx2 && Minn(my1, my2) + 1 == Maxx(my1, my2)))
			{
				// ֱ���������غ���
				Clear(mx1, my1, mx2, my2);
				Degemsound();
				return;
			}

			// �������
			if (Check(mx1, my1, mx2, my2, true, 200))	// true �������ߣ� 200 ����������ʾ��ʱ��
			{
				if (kind == KAVAI)
					Kavaisound(2);
				Clear(mx1, my1, mx2, my2);
			}
		}
	}
}



// ȡ�������ͼ����������ģ����ֵ����ߵ� y ֵ���ϱߵ� x ֵ
int Maxx(int a, int b, int c, int d)
{
	int max;
	max = (a > b) ? a : b;

	if (c < d)		// (c, a)/(d, b) �Ƚ� x ���꣬���� y ����
		return a;
	if (c > d)
		return b;
	else
		return max;
}



// ȡ��Сֵ���ұߵ� y ֵ���±ߵ� x ֵ
int Minn(int a, int b, int c, int d)
{
	int min;
	min = (a > b) ? b : a;

	if (c > d)
		return a;
	if (c < d)
		return b;
	else
		return min;
}



// �������·�ߣ�t ������ʾ���ߵ�ʱ�䳤��
bool Check(int mx1, int my1, int mx2, int my2, bool line, int t)
{
	int mx, my;			// ��ʾת�۵������
	int a, b, c;
	setlinestyle(PS_SOLID, 2);

	// ����һ��·��(mx �� mx1, mx2 ֮��)-------------------------
	for (mx = Minn(mx1, mx2) + 1; mx < Maxx(mx1, mx2); mx++)
	{
		// ÿ��ɨ�迪ʼ��Ҫ���ó�ʼֵ
		a = 0, b = 0, c = 0;

		// ɨ���� Minn(my1, my2) ���� Minn(mx1, mx2) + 1 �� mx ���� 
		for (x = Minn(mx1, mx2) + 1; x <= mx; x++)
			a += xy[x][Maxx(my1, my2, mx1, mx2)];	// ȡ��ߵ� y

		// ɨ���� mx ���� Minn(my1, my2) �� Maxx(my1, my2) ����
		for (y = Minn(my1, my2); y <= Maxx(my1, my2); y++)
			b += xy[mx][y];

		// ɨ���� Maxx(my1, my2) ���� mx �� Maxx(mx1, mx2) - 1 ����
		for (x = mx; x < Maxx(mx1, mx2); x++)
			c += xy[x][Minn(my1, my2, mx1, mx2)];	// ȡ�ұߵ� y

		// ��� a->b->c ����·�Ƿ�ͨ
		if (a + b + c == 0)
		{
			if (line)
			{
				if (kind == BIRD)					// ���ò�ͬ����Ч
				{
					Birdsound(2);
				}

				else if (kind != KAVAI)
				{
					Degemsound();
				}

				POINT p[] = { (Minn(mx1, mx2) + 1) * GWIDTH,	Maxx(my1, my2, mx1, mx2) * GLENGTH + 20,
							mx * GWIDTH + 15,				Maxx(my1, my2, mx1, mx2) * GLENGTH + 20,
							mx * GWIDTH + 15,				Minn(my1, my2, mx1, mx2) * GLENGTH + 20,
							Maxx(mx1, mx2) * GWIDTH,		Minn(my1, my2, mx1, mx2) * GLENGTH + 20 };
				polyline(p, 4);
				Sleep(t);
				setcolor(getbkcolor());
				polyline(p, 4);
			}
			return true;
		}
	}

	// �����һ�� a->b->c ��·��(my �� my1, my2 ֮��)-------------------------
	for (my = Minn(my1, my2) + 1; my < Maxx(my1, my2); my++)
	{
		// ÿ��ɨ�迪ʼ��Ҫ���ó�ʼֵ
		a = 0, b = 0, c = 0;

		// ɨ���� Minn(mx1, mx2) ���� Minn(my1, my2) + 1 �� my ����
		for (y = Minn(my1, my2) + 1; y <= my; y++)
			a += xy[Maxx(mx1, mx2, my1, my2)][y];		// ȡ�ϱߵ� x

		// ɨ���� my ���� Minn(mx1, mx2) �� Maxx(mx1, mx2) ����
		for (x = Minn(mx1, mx2); x <= Maxx(mx1, mx2); x++)
			b += xy[x][my];

		// ɨ���� Maxx(mx1, mx2) ���� my �� Maxx(my1, my2) - 1 ����
		for (y = my; y < Maxx(my1, my2); y++)
			c += xy[Minn(mx1, mx2, my1, my2)][y];		// ȡ�±ߵ� x

		// ��� a->b->c ����·�Ƿ�ͨ
		if (a + b + c == 0)
		{
			if (line)
			{
				if (kind == BIRD)					// ���ò�ͬ����Ч
				{
					Birdsound(2);
				}
				else if (kind != KAVAI)
				{
					Degemsound();
				}

				POINT p[] = { Maxx(mx1, mx2, my1, my2) * GWIDTH + 15,		(Minn(my1, my2) + 1) * GLENGTH,
							Maxx(mx1, mx2, my1, my2) * GWIDTH + 15,		my * GLENGTH + 20,
							Minn(mx1, mx2, my1, my2) * GWIDTH + 15,		my * GLENGTH + 20,
							Minn(mx1, mx2, my1, my2) * GWIDTH + 15,		Maxx(my1, my2) * GLENGTH };
				polyline(p, 4);
				Sleep(t);
				setcolor(getbkcolor());
				polyline(p, 4);
			}
			return true;
		}
	}

	// ��������·��(mx �� mx1, mx2 ���)----------------------------
	for (mx = 0; mx < Minn(mx1, mx2); mx++)
	{
		a = 0, b = 0, c = 0;

		// ɨ������ߵ� y ���� mx �� Minn(mx1, mx2) - 1 ����
		for (x = mx; x < Minn(mx1, mx2); x++)
			a += xy[x][Maxx(my1, my2, mx1, mx2)];	// ȡ��ߵ� y

		// ɨ���� mx ���� Minn(my1, my2) �� Maxx(my1, my2) ���� 
		for (y = Minn(my1, my2); y <= Maxx(my1, my2); y++)
			b += xy[mx][y];

		// ɨ�����ұߵ� y ���� mx �� Maxx(mx1, mx2) - 1 ����
		for (x = mx; x < Maxx(mx1, mx2); x++)
			c += xy[x][Minn(my1, my2, mx1, mx2)];	// ȡ�ұߵ� y

		if (a + b + c == 0)
		{
			if (line)
			{
				if (kind == BIRD)					// ���ò�ͬ����Ч
				{
					Birdsound(2);
				}
				else if (kind != KAVAI)
				{
					Degemsound();
				}

				POINT p[] = { Minn(mx1, mx2) * GWIDTH, Maxx(my1, my2, mx1, mx2) * GLENGTH + 20,
							mx * GWIDTH + 15,		 Maxx(my1, my2, mx1, mx2) * GLENGTH + 20,
							mx * GWIDTH + 15,		 Minn(my1, my2, mx1, mx2) * GLENGTH + 20,
							Maxx(mx1, mx2) * GWIDTH, Minn(my1, my2, mx1, mx2) * GLENGTH + 20 };
				polyline(p, 4);
				Sleep(t);
				setcolor(getbkcolor());
				polyline(p, 4);
			}
			return true;
		}
	}

	// ��ת�۵� mx = Minn(mx1, mx2) ��ʱ��ɨ������·��--------------------------------
	for (mx = Minn(mx1, mx2); mx <= Minn(mx1, mx2); mx++)
	{
		a = 0, b = 0, c = 0;

		// ɨ�����ұߵ� y ���� mx �� Maxx(mx1, mx2) - 1 ����
		for (x = mx; x < Maxx(mx1, mx2); x++)
			a += xy[x][Minn(my1, my2, mx1, mx2)];	// ȡ�ұߵ� y

		// ɨ���� mx ���� Minn(my1, my2) + 1 �� Maxx(my1, my2) ���� 
		for (y = Minn(my1, my2) + 1; y <= Maxx(my1, my2); y++)
			b += xy[mx][y];

		// ɨ���� mx ���� Minn(my1, my2) �� Maxx(my1 ,my2) - 1 ����
		for (y = Minn(my1, my2); y < Maxx(my1, my2); y++)
			c += xy[mx][y];

		if (a + b == 0 || a + c == 0)
		{
			if (line)
			{
				if (kind == BIRD)					// ���ò�ͬ����Ч
				{
					Birdsound(2);
				}
				else if (kind != KAVAI)
				{
					Degemsound();
				}

				POINT p[] = { mx * GWIDTH + 15,		 Maxx(my1, my2, mx1, mx2) * GLENGTH + 20,
							mx * GWIDTH + 15,		 Minn(my1, my2, mx1, mx2) * GLENGTH + 20,
							Maxx(mx1, mx2) * GWIDTH, Minn(my1, my2, mx1, mx2) * GLENGTH + 20 };
				polyline(p, 3);
				Sleep(t);
				setcolor(getbkcolor());
				polyline(p, 3);
			}
			return true;
		}
	}

	// ��������·��(mx �� mx1, mx2 ���ұ�)-------------------------------
	for (mx = Maxx(mx1, mx2) + 1; mx < 19; mx++)
	{
		a = 0, b = 0, c = 0;

		// ɨ������ߵ� y ���� Minn(mx1, mx2) + 1 �� mx ����
		for (x = Minn(mx1, mx2) + 1; x <= mx; x++)
			a += xy[x][Maxx(my1, my2, mx1, mx2)];		// ��ߵ� y 

		// ɨ���� mx ���� Minn(my1, my2) �� Maxx(my1, my2) ����
		for (y = Minn(my1, my2); y <= Maxx(my1, my2); y++)
			b += xy[mx][y];

		// ɨ�����ұߵ� y ���� Maxx(mx1, mx2) + 1 �� mx ����
		for (x = Maxx(mx1, mx2) + 1; x <= mx; x++)
			c += xy[x][Minn(my1, my2, mx1, mx2)];		// �ұߵ� y

		if (a + b + c == 0)
		{
			if (line)
			{
				if (kind == BIRD)					// ���ò�ͬ����Ч
				{
					Birdsound(2);
				}
				else if (kind != KAVAI)
				{
					Degemsound();
				}

				POINT p[] = { (Minn(mx1, mx2) + 1) * GWIDTH,	Maxx(my1, my2, mx1, mx2) * GLENGTH + 20,
							mx * GWIDTH + 15,				Maxx(my1, my2, mx1, mx2) * GLENGTH + 20,
							mx * GWIDTH + 15,				Minn(my1, my2, mx1, mx2) * GLENGTH + 20,
							(Maxx(mx1, mx2) + 1) * GWIDTH,	Minn(my1, my2, mx1, mx2) * GLENGTH + 20 };
				polyline(p, 4);
				Sleep(t);
				setcolor(getbkcolor());
				polyline(p, 4);
			}
			return true;
		}
	}

	// ��ת�۵� mx = Maxx(mx1, mx2) ��ʱ��ɨ������·��------------------------------
	for (mx = Maxx(mx1, mx2); mx <= Maxx(mx1, mx2); mx++)
	{
		a = 0, b = 0, c = 0;

		// ɨ������ߵ� y ���� Minn(mx1, mx2) + 1 �� mx ����
		for (x = Minn(mx1, mx2) + 1; x <= mx; x++)
			a += xy[x][Maxx(my1, my2, mx1, mx2)];		// ��ߵ� y

		// ɨ���� mx ���� Minn(my1, my2) �� Maxx(my1, my2) - 1 ����
		for (y = Minn(my1, my2); y < Maxx(my1, my2); y++)
			b += xy[mx][y];

		// ɨ���� mx ���� Minn(my1, my2) + 1 �� Maxx(my1, my2) ����
		for (y = Minn(my1, my2) + 1; y <= Maxx(my1, my2); y++)
			c += xy[mx][y];

		// ֻҪ��һ��·���е�ͨ
		if (a + b == 0 || a + c == 0)
		{
			if (line)
			{
				if (kind == BIRD)					// ���ò�ͬ����Ч
				{
					Birdsound(2);
				}
				else if (kind != KAVAI)
				{
					Degemsound();
				}

				POINT p[] = { (Minn(mx1, mx2) + 1) * GWIDTH,	Maxx(my1, my2, mx1, mx2) * GLENGTH + 20,
							mx * GWIDTH + 15,				Maxx(my1, my2, mx1, mx2) * GLENGTH + 20,
							mx * GWIDTH + 15,				Minn(my1, my2, mx1, mx2) * GLENGTH + 20 };
				polyline(p, 3);
				Sleep(t);
				setcolor(getbkcolor());
				polyline(p, 3);
			}
			return true;
		}
	}

	// ��������·��(my �� my1, my2 ������)-----------------------------
	for (my = 0; my < Minn(my1, my2); my++)
	{
		a = 0, b = 0, c = 0;

		// ɨ�����ϱ� x ���� my �� Minn(my1, my2) - 1 ����
		for (y = my; y < Minn(my1, my2); y++)
			a += xy[Maxx(mx1, mx2, my1, my2)][y];		// ȡ�ϱߵ� x

		// ɨ���� my ���� Minn(mx1, mx2) �� Maxx(mx1, mx2) ����
		for (x = Minn(mx1, mx2); x <= Maxx(mx1, mx2); x++)
			b += xy[x][my];

		// ɨ�����±� x ���� my �� Maxx(my1, my2) - 1 ����
		for (y = my; y < Maxx(my1, my2); y++)
			c += xy[Minn(mx1, mx2, my1, my2)][y];		// ȡ�±ߵ� x

		if (a + b + c == 0)
		{
			if (line)
			{
				if (kind == BIRD)					// ���ò�ͬ����Ч
				{
					Birdsound(2);
				}
				else if (kind != KAVAI)
				{
					Degemsound();
				}

				POINT p[] = { Maxx(mx1, mx2, my1, my2) * GWIDTH + 15, Minn(my1, my2) * GLENGTH,
							Maxx(mx1, mx2, my1, my2) * GWIDTH + 15, my * GLENGTH + 20,
							Minn(mx1, mx2, my1, my2) * GWIDTH + 15, my * GLENGTH + 20,
							Minn(mx1, mx2, my1, my2) * GWIDTH + 15, Maxx(my1, my2) * GLENGTH };
				polyline(p, 4);
				Sleep(t);
				setcolor(getbkcolor());
				polyline(p, 4);
			}
			return true;
		}
	}

	// ��������·��(my �� my1, my2 ������)---------------------------
	for (my = Maxx(my1, my2) + 1; my < 12; my++)
	{
		a = 0, b = 0, c = 0;

		// ɨ�����ϱ� x ���� Minn(my1, my2) + 1 �� my ����
		for (y = Minn(my1, my2) + 1; y <= my; y++)
			a += xy[Maxx(mx1, mx2, my1, my2)][y];		// ȡ�ϱߵ� x

		// ɨ���� my ���� Minn(mx1, mx2) �� Maxx(mx1, mx2) ����
		for (x = Minn(mx1, mx2); x <= Maxx(mx1, mx2); x++)
			b += xy[x][my];

		// ɨ�����±� x ���� Maxx(my1, my2) + 1 �� my ����
		for (y = Maxx(my1, my2) + 1; y <= my; y++)
			c += xy[Minn(mx1, mx2, my1, my2)][y];		// ȡ�±ߵ� x

		if (a + b + c == 0)
		{
			if (line)									// �����Ҫ����
			{
				if (kind == BIRD)					// ���ò�ͬ����Ч
				{
					Birdsound(2);
				}
				else if (kind != KAVAI)
				{
					Degemsound();
				}
				// ����֮ǰ�����������Ա�������������� Sleep(t) ��ʱ

				POINT p[] = { Minn(mx1, mx2, my1, my2) * GWIDTH + 15, (Maxx(my1, my2) + 1) * GLENGTH,
							Minn(mx1, mx2, my1, my2) * GWIDTH + 15, my * GLENGTH + 20,
							Maxx(mx1, mx2, my1, my2) * GWIDTH + 15, my * GLENGTH + 20,
							Maxx(mx1, mx2, my1, my2) * GWIDTH + 15, (Minn(my1, my2) + 1) * GLENGTH };
				polyline(p, 4);
				Sleep(t);
				setcolor(getbkcolor());
				polyline(p, 4);
			}
			return true;
		}
	}
	return false;
}



// ���� (ax, ay) �� (bx, by) ������ͼ��
void Clear(int ax, int ay, int bx, int by)
{
	setfillstyle(BLACK);
	setcolor(0x90d2d2);
	setlinestyle(0, 2);

	// ʣ��ͼ����
	bar(650, 57, 710, 77);

	// ��������
	bar(650, 7, 730, 27);

	// ���ʣ����
	SNum -= 2;
	setcolor(0x00aaff);
	_stprintf_s(snum, _T("%03d"), SNum);
	outtextxy(667, 60, snum);

	// �������
	Mark += 1007;
	_stprintf_s(mark, _T("%08d"), Mark);
	outtextxy(662, 10, mark);

	// �������ݹ���������ͼ��
	setfillcolor(getbkcolor());
	bar(ax * GWIDTH + 1, ay * GLENGTH + 1, (ax + 1) * GWIDTH - 2, (ay + 1) * GLENGTH - 3);
	bar(bx * GWIDTH + 1, by * GLENGTH + 1, (bx + 1) * GWIDTH - 2, (by + 1) * GLENGTH - 3);

	// ���������Ǹ���λ��Ϊ 0
	xy[ax][ay] = 0;
	xy[bx][by] = 0;

	// �ͷ����� ixy[][] �� Img ����ͼ����һһ��Ӧ��ϵ
	ixy[ax][ay].ix = ixy[bx][by].ix = 0;
	ixy[ax][ay].iy = ixy[bx][by].iy = 0;

	Time();			// �����֣��Ƿ��������ʱ��
}



// �����Ϸ�������
bool GameOver()
{
	int sum = 0;

	for (x = 0; x < 19; x++)
		for (y = 0; y < 12; y++)
			sum += xy[x][y];	// ix, iy ��һ��

	if (sum == 0)
	{
		// ���ಥ������
		if (kind == PLANT)
			Plantsound(0);

		if (kind == PET)
			Petsound(0);

		if (kind == BIRD)
			Birdsound(0);

		if (kind == QQ)
			Qqsound(0);

		if (kind == SHEEP)
			Sheepsound(0);

		if (kind == KAVAI)
			Kavaisound(0);

		if (kind == ALL)
			Dekaronsound();

		MessageBox(hwnd, _T("WAHOO! Continue"), _T("��ʾ"), MB_OK);

		F++;
		Frame();			// ��ʼ����Ϸ
		return true;
	}

	if (tx > 700)
	{
		Amengsound();
		if (MessageBox(hwnd, _T("��ˮ����ϵ��ϵһͷˮ����"), _T("TimeOver"), MB_YESNO | MB_ICONQUESTION) == IDYES)
			return false;
		else
		{
			Frame();
			return true;
		}
	}
	return true;
}



// ը������
void Bomb()
{
	int xa, ya, xb, yb;
	int t1, t2;				// ��ֹ�������֣���������ѭ��
	t1 = clock();

	if (bomb < 1)			// ���ը���ù�
	{
		Diongsound();
		return;
	}

	// ɨ�����ը����ͼ��
	do
	{
		xa = rand() % 19;
		ya = rand() % 12;
		xb = rand() % 19;
		yb = rand() % 12;

		// �����λ�ü�¼��ͼ����ͬ���� �ǿ�
		if (ixy[xa][ya].ix == ixy[xb][yb].ix
			&& ixy[xa][ya].iy == ixy[xb][yb].iy
			&& xy[xa][ya] != 0)
		{
			// ���ɨ��õ������������ڵ���ͬͼ��(�������ڡ���������)
			if ((Minn(xa, xb) + 1 == Maxx(xa, xb) && ya == yb) || (xa == xb && Minn(ya, yb) + 1 == Maxx(ya, yb)))
				break;	// ֱ���˳�ѭ��
		}

		t2 = clock();
		if (t2 - t1 > 2000)		// ��������ӻ�û���ҵ�����������ͼ�� / �����֣�ֻ��ˢ��
		{
			Amengsound();
			MessageBox(hwnd, _T("��ż��ľ�п����ģ������ɣ�"), _T("ע��"), MB_OK | MB_ICONWARNING);
			return;
		}

	} while (!Check(xa, ya, xb, yb, 0, 0)
		|| ixy[xa][ya].ix != ixy[xb][yb].ix
		|| ixy[xa][ya].iy != ixy[xb][yb].iy
		|| (xa == xb && ya == yb)
		|| xy[xa][ya] == 0
		|| xy[xb][yb] == 0);
	// ��� ������������ͼ������ͬһ��ͼ��������ѹ��������ͬһλ�õ�ͼ������λ��û��ͼ�� / ��Ҫ����ѭ��


	// ���߲���ʾ 500 ����
	Check(xa, ya, xb, yb, true, 500);
	if (kind == KAVAI)
		Kavaisound(2);
	Bombsound();
	Clear(xa, ya, xb, yb);

	// ����������
	setfillstyle(BLACK);
	setcolor(0x90d2d2);
	setlinestyle(0, 2);
	bar(650, 107, 710, 127);

	// ���ʣ��ը����
	bomb--;
	_stprintf_s(bom, _T("%02d"), bomb);
	setcolor(0x00aaff);
	outtextxy(672, 110, bom);
}



// ˢ��ͼ��
void Refresh()
{
	int photo = 0;		// ��¼ԭ��ͼ����

	if (refr < 1)		// ���ˢ���ù�
	{
		Diongsound();
		return;
	}

	// ɨ���ʣ��ͼ����
	for (y = 0; y < 12; y++)
	{
		for (x = 0; x < 19; x++)
		{
			// �����λ����ͼ��
			if (xy[x][y] != 0)
			{
				photo++;				// ���� + 1
				xy[x][y] = -1;		// ���±�Ǹ�λ��Ϊ -1��������ͼ��
			}
		}
	}

	// ��ԭ��������λ�����·������ͼ��
	Putimg(photo / 2, kind);

	/********* ����ԭ���� ************/

	setfillstyle(BLACK);
	setcolor(0x90d2d2);
	setlinestyle(0, 2);

	bar(650, 157, 710, 177);	// ˢ�´���
	bar(650, 207, 710, 227);	// ���ģʽ
	bar(650, 257, 710, 277);	// С��ģʽ
	bar(650, 307, 710, 327);	// ֲ��ģʽ
	bar(650, 357, 710, 377);	// Ѽ��ģʽ
	bar(650, 407, 710, 427);	// ��ͷģʽ
	bar(650, 457, 710, 477);	// kavaiģʽ

/********* ����ԭ���� ************/


	// ������º����Ϣ
	refr--;
	setcolor(0x00aaff);
	_stprintf_s(ref, _T("%02d"), refr);
	outtextxy(672, 160, ref);
	outtextxy(672, 210, ref);
	outtextxy(672, 260, ref);
	outtextxy(672, 310, ref);
	outtextxy(672, 360, ref);
	outtextxy(672, 410, ref);
	outtextxy(672, 460, ref);
}



// ���ڼ���ʱ������
void Time()
{
	if (Mark % 15105 == 0 && Mark != 0)	// ���ÿ���� 15 ��ͼ����
	{
		setfillstyle(getbkcolor());
		bar(tx - 50, -90, tx, -85);
		tx -= 50;						// ÿ���� 15 ��ʱ�������� 50 ��λ
	}
}



// ���ñ���ɫ
void ChangeBk()
{
	TCHAR bkr[20], bkg[20], bkb[20];		// �����ַ���

	// ����û������ȡ���򲻸ı������� r, g, b ֵ
	if (InputBox(bkr, 20, NULL, _T("�ף�����RGB�е�(0~255)��ɫ��ֵ��"), _T("212"), 0, 0, 0))
		_tscanf_s(bkr, _T("%d"), &r);			// ���ַ���תΪ����

	if (InputBox(bkg, 20, NULL, _T("(0~255)��ɫ��ֵ��"), _T("164"), 0, 0, 0))
		_tscanf_s(bkg, _T("%d"), &g);

	if (InputBox(bkb, 20, NULL, _T("�ף�����RGB�е�(0~255)��ɫ��ֵ��--------"), _T("72"), 0, 0, 0))
		_tscanf_s(bkb, _T("%d"), &b);

	bkcolor = RGB(r, g, b);
	Draw();

	setfillstyle(LIGHTGREEN);			// ���ڻ�ԭ�Ѿ���ȥ�˵�ʱ����
	bar(-45, -90, tx, -85);

	for (x = 0; x <= 18; x++)
		for (y = 0; y <= 11; y++)
		{
			if (xy[x][y] != 0)
				putimage(x * GWIDTH + 1, y * GLENGTH + 1, PWIDTH, PLENGTH, &Img, (ixy[x][y].ix - 1) * PWIDTH, (ixy[x][y].iy - 1) * PLENGTH);
		}

	putimage(-10, -60, BIGW, BIGL, &Img, 0 * 50, 6 * PLENGTH);		// ����
}



// �������������Ԥ������
void Openmusic()
{
	s = rand() % 5;

	switch (s)
	{
		// �������֡�����
	case 0:	mciSendString(_T("open .\\sound\\����ֻ��һֻ��.mp3	alias bmusic1"), 0, 0, 0);	break;
	case 1:	mciSendString(_T("open .\\sound\\flower.mp3			alias bmusic2"), 0, 0, 0);	break;
	case 2:	mciSendString(_T("open .\\sound\\luvletter.mp3			alias bmusic3"), 0, 0, 0);	break;
	case 3:	mciSendString(_T("open .\\sound\\thedeath.mp3			alias bmusic4"), 0, 0, 0);	break;
	case 4: mciSendString(_T("open \".\\sound\\the truth.mp3\"		alias bmusic5"), 0, 0, 0);	break;	// �ļ����пո��д��
	default:	break;
	}
}



// ���ű�������
void Playmusic()
{
	switch (s)
	{
	case 0:	mciSendString(_T("play bmusic1 repeat"), 0, 0, 0);	break;
	case 1:	mciSendString(_T("play bmusic2 repeat"), 0, 0, 0);	break;
	case 2:	mciSendString(_T("play bmusic3 repeat"), 0, 0, 0);	break;
	case 3:	mciSendString(_T("play bmusic4 repeat"), 0, 0, 0);	break;
	case 4:	mciSendString(_T("play bmusic5 repeat"), 0, 0, 0);	break;
	default:	break;
	}
}



// ֹͣ���ű�������
void Closemusic()
{
	switch (s)
	{
	case 0:	mciSendString(_T("close bmusic1"), 0, 0, 0);	break;
	case 1:	mciSendString(_T("close bmusic2"), 0, 0, 0);	break;
	case 2:	mciSendString(_T("close bmusic3"), 0, 0, 0);	break;
	case 3:	mciSendString(_T("close bmusic4"), 0, 0, 0);	break;
	case 4:	mciSendString(_T("close bmusic5"), 0, 0, 0);	break;
	default:	break;
	}
}