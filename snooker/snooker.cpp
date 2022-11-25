/*****************************
*
*	为了突出更新内容，将旧的注视删掉。
*	改版注释的内容即为此次修改部分
*
*	主要修改：
*	1、使用更精准的计时器 QueryPerformanceFrequency(),QueryPerformanceCounter()
*	2、增加游戏结束后的弹出窗口。
*
******************************/

#include "graphics.h"
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include "circleball.h"
#include <mmsystem.h>
#pragma comment( lib, "winmm.lib" )



struct BALL
{

	double X, Y, dir, gapt;
	int kind;
	bool stop, goin;

	LARGE_INTEGER litmp;		// 定义计时数据结构的一个对象
	LONGLONG Lt1, Lt2;			// 获取时钟计数（频率与时间(秒)的乘积）
	double Freq;				// 获取时钟频率

}Ball[22];


IMAGE get[8], ball[8];
ExMessage m;
IMAGE img, Img[7];
bool game = true, poweron = true;
int mx1 = -40, my1 = -40, mx2 = -40, my2 = -40;
double power = 0, powert1, powert2, linex = 500, dx = 1;
double R = 3;


int iix[22] = { 0,
				1, 1,
				2, 2, 2,
				3, 3, 3, 3,
				4, 4, 4, 4, 4,
				180, 180, 180, 400, 581, 740, -80 };

int iiy[22] = { 0,
				-1, 1,
				-2, 0, 2,
				-3, -1, 1, 3,
				-4, -2, 0, 2, 4,
				350, 150, 250, 250, 250, 250, -250 };

double slow[6] = { 0.01, 0.02, 0.05, 0.1, 0.11, 0.14 };


void Load();
void InitTable();
void DrawBall();
void Play();
void LButton(ExMessage );
void Move();
void Check(int id);
void Slow(int sid);
void PowerLine();







void main()
{
	initgraph(800, 500, SHOWCONSOLE);

	Load();
	InitTable();
	DrawBall();
	Play();

	closegraph();
}


void Load()
{
	for (int jj = 0; jj < 8; jj++)
	{
		TCHAR c[20];
		_stprintf_s(c, _T("./ball/%d.jpg"), jj);
		loadimage(&get[jj], c, 28, 28);
	}

	for (int kk = 0; kk <= 7; kk++)
		CircleImg(&ball[kk], 0x076f22, &get[kk], 13, SRCINVERT);

	powert1 = timeGetTime();
}


void InitTable()
{

	setbkcolor(0x076f22);
	cleardevice();

	//setwritemode(R2_XORPEN);


	setcolor(0x16242C);
	setlinestyle(0, 50);
	rectangle(0, 0, 800, 500);
	setlinestyle(0, 1);

	setcolor(LIGHTGREEN);
	rectangle(498, 483, 601, 491);
	outtextxy(605, 478, _T("( P )"));

	setcolor(WHITE);
	line(180, 25, 180, 475);
	arc(80, 150, 280, 350, 1.57, 4.71);

	//setwritemode(R2_COPYPEN);
	setcolor(0);
	setfillcolor(0);
	setfillstyle(0);
	fillcircle(28, 28, 13);
	fillcircle(28, 472, 13);
	fillcircle(400, 25, 13);
	fillcircle(400, 475, 13);
	fillcircle(772, 28, 13);
	fillcircle(772, 472, 13);
	//setwritemode(R2_XORPEN);
}


void DrawBall()
{
	int i;

	for (i = 0; i < 15; i++)
	{
		Ball[i].X = 610 + (int)(iix[i] * 13 * sqrt(3.2));
		Ball[i].Y = 250 + iiy[i] * 13.7;
		Ball[i].stop = true;
		Ball[i].goin = false;
		Ball[i].kind = 7;
		Ball[i].gapt = 99999;

		QueryPerformanceFrequency(&Ball[i].litmp);	// 获取时钟频率
		Ball[i].Freq = (double)Ball[i].litmp.QuadPart;
		QueryPerformanceCounter(&Ball[i].litmp);		// 获取时钟计数(频率与时间的乘积)
		Ball[i].Lt1 = Ball[i].litmp.QuadPart;

		putcircle(Ball[i].X, Ball[i].Y, &ball[Ball[i].kind], SRCINVERT);
	}

	for (i = 15; i <= 21; i++)
	{
		Ball[i].X = iix[i];
		Ball[i].Y = iiy[i];
		Ball[i].kind = i - 15;
		Ball[i].stop = true;
		Ball[i].gapt = 99999;

		QueryPerformanceFrequency(&Ball[i].litmp);	// 获取时钟频率
		Ball[i].Freq = (double)Ball[i].litmp.QuadPart;
		QueryPerformanceCounter(&Ball[i].litmp);		// 获取时钟计数(频率与时间的乘积)
		Ball[i].Lt1 = Ball[i].litmp.QuadPart;

		if (i == 21)
			Ball[i].goin = true;
		else
			Ball[i].goin = false;

		putcircle(Ball[i].X, Ball[i].Y, &ball[Ball[i].kind], SRCINVERT);
	}
}


void Play()
{
	int lx1 = Ball[21].X, ly1 = Ball[21].Y, lx2 = Ball[21].X, ly2 = Ball[21].Y;
	bool num = false;

	BeginBatchDraw();

	while (game)
	{
		InitTable();



		bool has_msg = peekmessage(&m);
		//	if (!has_msg)
			//运动缓慢	Sleep(1);

		int num2 = 0;
		for (int xx = 0; xx <= 20; xx++)	// 扫描桌面是否没球了
		{
			if (Ball[xx].goin != true)
				num2++;
		}

		if (num2 == 0)								// 如果球全部 goin 了
		{
			HWND hwnd = GetHWnd();
			if (IDYES == MessageBox(hwnd, _T("你想再来一局？"), _T("曾哥"), MB_ICONQUESTION | MB_YESNO))
			{
				cleardevice();
				InitTable();
				setfillstyle(0xf9f9f9);
				fillcircle(m.x, m.y, 12);

				setcolor(YELLOW);
				setlinestyle(0, 4);
				line(500, 487, linex, 487);
				setlinestyle(0, 1);
			}
			else
				game = false;
		}

		powert2 = timeGetTime();

		for (int fd = 0; fd < 22; fd++)
		{
			QueryPerformanceCounter(&Ball[fd].litmp);		// 获取时钟计数(频率与时间的乘积)
			Ball[fd].Lt2 = Ball[fd].litmp.QuadPart;
		}


		if (has_msg)
		{
			if (!num)
				mx1 = lx1 = m.x, my1 = ly1 = m.y;
			if (num)
				mx2 = lx2 = m.x, my2 = ly2 = m.y;

			switch (m.message)
			{
			case WM_LBUTTONUP:

				if (Ball[21].goin == false && Ball[21].stop == true)
				{
					setcolor(WHITE);
					setlinestyle(0, 1);

					if (!num)
						line(lx2, ly2, Ball[21].X, Ball[21].Y);
					else
						line(lx1, ly1, Ball[21].X, Ball[21].Y);
				}

				LButton(m);
				break;

			case WM_MOUSEMOVE:

				if (!num)	mx1 = lx1 = m.x, my1 = ly1 = m.y;
				if (num) mx2 = lx2 = m.x, my2 = ly2 = m.y;
				break;

			case WM_RBUTTONDOWN:
				game = false;
				break;
			case WM_CHAR:
				if (m.ch == 112)	// p 按键
				{
					poweron = !poweron;

					setcolor(YELLOW);
					setlinestyle(0, 4);
					line(500, 487, linex, 487);
					setlinestyle(0, 1);
				}
			default:	break;
			}
			num = !num;
		}

		Move();
		PowerLine();

		if (Ball[21].goin == false && Ball[21].stop == true)
		{
			setcolor(WHITE);
			line(lx2, ly2, Ball[21].X, Ball[21].Y);
		}
		if (Ball[21].stop == true)
		{
			setcolor(WHITE);
			setlinestyle(0, 1);
			circle(lx2, ly2, 12);
		}

		if(Ball[21].goin == false)
			putcircle(Ball[21].X, Ball[21].Y, &ball[Ball[21].kind], SRCINVERT);

		for (int i = 0; i < 21; i++)
		{
			putcircle(Ball[i].X, Ball[i].Y, &ball[Ball[i].kind], SRCINVERT);
		}

		FlushBatchDraw();
	}
}


void LButton(ExMessage m)
{
	if (Ball[21].goin == true)
	{
		double x1, x2, x3, x4;
		double y1, y2;

		x1 = (m.x - 180) * (m.x - 180);
		y1 = 250 - sqrt(10000 - x1);
		y2 = 250 + sqrt(10000 - x1);

		x2 = (m.x - Ball[15].X) * (m.x - Ball[15].X) + (m.y - Ball[15].Y) * (m.y - Ball[15].Y) - 26 * 26;
		x3 = (m.x - Ball[16].X) * (m.x - Ball[16].X) + (m.y - Ball[16].Y) * (m.y - Ball[16].Y) - 26 * 26;
		x4 = (m.x - Ball[17].X) * (m.x - Ball[17].X) + (m.y - Ball[17].Y) * (m.y - Ball[17].Y) - 26 * 26;

		if (m.x >= 80 && m.x <= 180 && m.y >= y1 && m.y <= y2 && x2 > 0 && x3 > 0 && x4 > 0)
		{
			Ball[21].goin = false;
			Ball[21].X = m.x;
			Ball[21].Y = m.y;

			setcolor(0);
			setfillstyle(0xf9f9f9);
			fillcircle(m.x, m.y, 12);
			setcolor(WHITE);
			circle(m.x, m.y, 12);

			putcircle(Ball[21].X, Ball[21].Y, &ball[Ball[21].kind], SRCINVERT);
		}
	}
	else
	{
		mciSendString(_T("close shoot"), 0, 0, 0);
		mciSendString(_T("open ./sound/shoot.wav	alias shoot"), 0, 0, 0);
		mciSendString(_T("play shoot"), 0, 0, 0);

		Ball[21].dir = atan2(Ball[21].Y - m.y, m.x - Ball[21].X);
		Ball[21].stop = false;
		Ball[21].gapt = power;
	}
}



void Move()
{
	double drt;
	for (int nu = 0; nu <= 21; nu++)
	{
		// 将获取的时间计数与频率相除得到时间(秒)，并转换成毫秒,并计算两次计时的时间差
		drt = ((double)((Ball[nu].Lt2 - Ball[nu].Lt1) * 1000)) / Ball[nu].Freq;

		if (drt > Ball[nu].gapt && Ball[nu].stop == false && Ball[nu].goin == false)
		{
			Check(nu);
			Slow(nu);

			Ball[nu].Lt1 = Ball[nu].Lt2;
		}
	}
}


void Check(int id)
{
	double cx = Ball[id].X;
	double cy = Ball[id].Y;
	double a, b;

	cx += R * cos(Ball[id].dir);
	cy -= R * sin(Ball[id].dir);

	if (cx <= 44 && cy <= 44 || cx <= 44 && cy >= 456 || cx >= 756 && cy <= 44 || cx >= 756 && cy >= 456
		|| cx >= 390 && cx <= 410 && cy <= 40 || cx >= 390 && cx <= 410 && cy >= 460)
	{
		if (id == 21)
		{
			mciSendString(_T("close shoot"), 0, 0, 0);
			mciSendString(_T("open ./sound/GG.wav	alias shoot"), 0, 0, 0);
			mciSendString(_T("play shoot"), 0, 0, 0);

			Ball[21].goin = true;
			Ball[21].stop = true;
			return;
		}
		else
		{
			PlaySound(_T("./sound/in.wav"), 0, SND_ASYNC);
			Ball[id].X = -50;
			Ball[id].goin = true;
			return;
		}
	}


	if (cx > 38 && cx < 762 && cy > 38 && cy < 462)
	{
		for (int j = 0; j <= 21; j++)
		{
			if (j != id)
			{
				a = cx - Ball[j].X;
				b = cy - Ball[j].Y;

				if (a * a + b * b < 676)
				{
					PlaySound(_T("./sound/hit.wav"), 0, SND_ASYNC);
					BALL* slow = 0;
					BALL* fast = 0;

					if (Ball[id].gapt >= Ball[j].gapt && Ball[j].stop == false)
					{
						slow = &Ball[id];
						fast = &Ball[j];
					}

					if (Ball[id].gapt < Ball[j].gapt && Ball[j].stop == false)
					{
						slow = &Ball[j];
						fast = &Ball[id];
					}

					if (Ball[j].stop == true)
					{
						slow = &Ball[j];
						fast = &Ball[id];
						Ball[j].stop = false;
					}

						fast->gapt *= 1.4;
						slow->gapt = fast->gapt * 1.2;
						slow->dir = atan2(fast->Y - slow->Y, slow->X - fast->X);

					if (fast->dir > slow->dir)
					{
						if (slow->dir < 0 && fast->dir > 1.57)
							fast->dir = slow->dir + 4.71;
						else
							fast->dir = slow->dir + 1.57;
					}
					else
					{
						if (slow->dir > 0 && fast->dir < -1.57)
							fast->dir = slow->dir - 4.71;
						else
							fast->dir = slow->dir - 1.57;
					}

					Ball[id].X += R * cos(Ball[id].dir);
					Ball[id].Y -= R * sin(Ball[id].dir);
				}
				else
				{
					Ball[id].X = cx;
					Ball[id].Y = cy;
				}
			}
		}
	}
	else if (cx <= 38 || cx >= 762)
		Ball[id].dir = 3.14 - Ball[id].dir;
	else if (cy <= 38 || cy >= 462)
		Ball[id].dir = -Ball[id].dir;
}



void Slow(int sid)
{
	double s = Ball[sid].gapt;

	if (s < 18)
		Ball[sid].gapt += slow[(int)s / 3];
	else
	{
		R = 2;
		Ball[sid].gapt += 0.17;
	}

	if (s > 45)
	{
		if (sid == 21)
		{
			setcolor(WHITE);
			setlinestyle(0, 1);

			mx1 = m.x, my1 = m.y;
			mx2 = m.x, my2 = m.y;
			line(m.x, m.y, Ball[21].X, Ball[21].Y);
		}
		Ball[sid].stop = true;
	}
}



void PowerLine()
{
	if (poweron)
	{
		if (powert2 - powert1 > 20)
		{
			linex += dx;

			if (linex >= 600)
				dx = -1;

			if (linex <= 500)
				dx = 1;

			power = (double)(600 - linex) / 36;

			powert1 = powert2;
		}
	}
			setcolor(GREEN);
			setlinestyle(0, 4);
			line(500, 487, linex, 487);
			setlinestyle(0, 1);
}