/************************************************************************
*
*	名：《连连看》
*	by：xiongfj(837943056@qq.com)
*
*	附 0：带背景音乐和乱七八糟音效的连连看
*	附 1：收集了QQ、愤怒的小鸟、植物大战僵尸、喜洋洋、还有两个其他图案。
*	附 2：vc++6.0	&&	graphics.h(201206)
*	附 3：最后修改 2012-09-26
*
************************************************************************/

#include <graphics.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>			// for PlaySound() / mciSendString() 函数
#pragma comment (lib, "winmm.lib")
#include "LLK.h"

// 常量定义
#define GLENGTH		40			// 格子长
#define GWIDTH		30			// 格子宽

#define PLENGTH		36			// Img 里小图案的实际长度
#define PWIDTH		28			// Img 里小图案的实际宽度

#define BIGL		40			// Img 里大图案的实际宽
#define BIGW		50			// Img 里大图案的实际宽

enum Kind { QQ, BIRD, PLANT, PET, SHEEP, KAVAI, ALL };				// 图案种类

// ix, iy 表示该图案在 Img 里面的坐标
struct IMG
{
	int ix, iy;
}ixy[19][12];

// 变量定义
IMAGE Img, Img2;								// load 图案
ExMessage m;
Kind kind = PET;								// 图案类型
HWND hwnd;

bool game;										// 作为循环的条件
TCHAR c, bom[10], ref[10], snum[10], mark[10];	// 数组用于输出剩余炸弹、刷新、图案 / 积分
TCHAR n[10];										// 输出关卡
int xy[19][12], F = 1;							// 格子状态、每个 F 对应 Map() 里面的一个地图
int x, y, i;									// for 循环
int t1, t2, tx, T = 300;						// 输出时间、时间条走动间隔
int mhitnum = 0;								// 记录点击次数
int mx1, my1, mx2 = -20, my2 = -20;				// -20 是为了将该初始值的效果放到屏幕之外
int bomb, refr, SNum, Mark;						// 可用炸弹、刷新、剩余图案数 / 当前积分值
int bkcolor = RGB(212, 164, 72);				// 用于 setbkcolor() 函数
int r = 212, g = 164, b = 72;					// 接收 InputBox 转换后的数字
int s;											// 用于选择背景音乐



// 函数申明
void Frame();											// 游戏初始化信息
void Putimg(int, Kind);									// 输出图案
void Start();											// 开始连连
void LButton();											// 左击函数
void Clear(int, int, int bx, int by);					// 消掉图案
void Bomb();											// 炸弹函数
void Refresh();											// 刷新图案
void Time();											// 赠送游戏时间
void ChangeBk();										// 设置背景色函数
void Draw();											// 该函数用于输出屏幕信息 (实时游戏信息)
void Openmusic();
void Playmusic();
void Closemusic();
int  Maxx(int, int, int c = 0, int d = 0);				// 取最大值，与取左边的 y 或上边的 x
int  Minn(int, int, int c = 0, int d = 0);				// 取最小值，与取右边的 y 或下边的 x
bool Check(int, int, int, int, bool, int);				// 检测路线 与 是否连线 1 连，0 不连
bool GameOver();										// 检测游戏是否结束



// 主函数
void main()
{
	initgraph(800, 600, SHOWCONSOLE);
	loadimage(&Img, _T(".\\photo\\p.jpg"));
	loadimage(&Img2, _T(".\\photo\\introduction.jpg"));

	hwnd = GetHWnd();

	putimage(0, 0, &Img2);					// 游戏界面介绍
	_getch();
	mciSendString(_T("close 11"), 0, 0, 0);		// 关掉 Welcome() 打开的音乐

	srand(time(0));							// 设置种子
	setorigin(50, 100);						// 设置原点
	Frame();								// 确定游戏框架，画地图
	Start();								// 游戏开始

	closegraph();
}



// 画游戏区及一些初始化数据
void Frame()
{
	int num;				// 每种框架可放的图案数 / 2
	Closemusic();

	// 初始化数据
	tx = -45;				// 时间条的初始 x 坐标位置
	t1 = clock();			// 游戏开始计时，用于走动时间条
	game = true;			// 游戏继续 or 结束
	bomb = 5;				// 每局有 5 个炸弹
	refr = 5;				// 每局有 5 次刷新
	Mark = 0;				// 初始化积分

	// 每次游戏重新开始都要先归零游戏区
	for (x = 0; x < 19; x++)
		for (y = 0; y < 12; y++)
		{
			xy[x][y] = 0;
			ixy[x][y].ix = ixy[x][y].iy = 0;
		}

	if (F > 113)
	{
		MessageBox(hwnd, _T("亲，你真强大，木有地图了！快去玩KAVAI模式吧！"), _T("Notice"), MB_OK);
		F = 1;
	}

	// 大于 29 关后，每关稍微加快时间条速度
	if (F > 29)
		T -= 2;

	// Map() 函数根据 F 确定一种地图，返回该地图的图案数 / 2
	num = Map(F, xy);

	SNum = 2 * num;		// SNum 用于输出剩余图案数

	Draw();				// 该函数根据 Frame() 里初始化的各种数据，将他们现实出来

	Putimg(num, kind);

	Openmusic();
	Playmusic();		// 播放背景音乐
}


// 显示数据。初始化与显示数据分开，可以避免有时候不需要初始化的更新屏幕，那么就可以单独调用该函数
void Draw()
{
	setbkcolor(bkcolor);			// 用背景色清屏才会改变原来的背景色
	cleardevice();

	setfillstyle(RED);				// 时间结束点
	setcolor(RED);
	fillcircle(705, -87, 5);

	setcolor(0X00C78C);				// 游戏矩形框架
	setlinestyle(0, 6);
	rectangle(-6, -6, 575, 488);

	/******* 制作窗口效果 *************/
	setfillstyle(BLACK);
	setcolor(0x90d2d2);
	setlinestyle(0, 2);

	rectangle(649, 6, 732, 29);	// 积分
	rectangle(649, 56, 712, 79);	// 剩余图案数
	rectangle(649, 106, 712, 129);	// 炸弹
	rectangle(649, 156, 712, 179);	// 刷新
	rectangle(649, 206, 712, 229);	// 企鹅
	rectangle(649, 256, 712, 279);	// 小鸟
	rectangle(649, 306, 712, 329);	// 植物
	rectangle(649, 356, 712, 379);	// 鸭子
	rectangle(649, 406, 712, 429);	// 羊头
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
	outtextxy(600, 10, _T("积分："));
	outtextxy(600, 60, _T("剩余："));

	// 纯修饰
	fillcircle(590, 42, 3);
	fillcircle(590, 92, 3);
	line(590, 42, 730, 42);
	line(590, 92, 710, 92);


	/******* 显示竖向按钮 *********************************/
	setcolor(0x00aaff);
	setbkmode(TRANSPARENT);


	_stprintf_s(mark, _T("%08d"), Mark);		// 积分栏
	outtextxy(662, 10, mark);

	_stprintf_s(snum, _T("%03d"), SNum);		// 剩余图案栏
	outtextxy(667, 60, snum);

	putimage(600, 100, PWIDTH, PLENGTH, &Img, 21 * PWIDTH, 0 * PLENGTH);		// 炸弹栏
	_stprintf_s(bom, _T("%02d"), bomb);
	outtextxy(672, 110, bom);

	putimage(600, 150, PWIDTH, PLENGTH, &Img, 31 * PWIDTH, 0 * PLENGTH);		// 刷新栏
	_stprintf_s(ref, _T("%02d"), refr);
	outtextxy(672, 160, ref);

	putimage(600, 200, PWIDTH, PLENGTH, &Img, 2 * PWIDTH, 5 * PLENGTH);		// 扣扣模式
	outtextxy(672, 210, ref);

	putimage(600, 250, PWIDTH, PLENGTH, &Img, 4 * PWIDTH, 5 * PLENGTH);		// 小鸟模式
	outtextxy(672, 260, ref);

	putimage(600, 300, PWIDTH, PLENGTH, &Img, 6 * PWIDTH, 5 * PLENGTH);		// 植物模式
	outtextxy(672, 310, ref);

	putimage(600, 350, PWIDTH, PLENGTH, &Img, 8 * PWIDTH, 5 * PLENGTH);		// 宠物模式
	outtextxy(672, 360, ref);

	putimage(600, 400, PWIDTH, PLENGTH, &Img, 10 * PWIDTH, 5 * PLENGTH);		// 羊头模式
	outtextxy(672, 410, ref);

	putimage(600, 450, PWIDTH, PLENGTH, &Img, 12 * PWIDTH, 5 * PLENGTH);		// 卡哇伊模式
	outtextxy(672, 460, ref);
	/******* 显示竖向按钮 *********************************/


		/********* 显示横向按钮*********/
	putimage(-10, -60, BIGW, BIGL, &Img, 0 * 50, 6 * PLENGTH);		// 背景色设置

	putimage(70, -60, BIGW, BIGL, &Img, 2 * 50, 6 * PLENGTH);		// 下一关

	putimage(150, -60, BIGW, BIGL, &Img, 4 * 50, 6 * PLENGTH);		// 关闭游戏

	putimage(330, -60, BIGW, BIGL, &Img, 6 * 50, 6 * PLENGTH);		// 上一关

	putimage(590, -60, BIGW, BIGL, &Img, 8 * 50, 6 * PLENGTH);		// ALL 模式

	setcolor(BLUE);
	outtextxy(230, -55, _T("第"));			// 当前关卡
	_stprintf_s(n, _T("%03d"), F);
	outtextxy(255, -55, n);
	outtextxy(290, -55, _T("关"));
	/********* 显示横向按钮*********/
}



// 放多少图案 (num * 2) 以及放何种图案 (k)
void Putimg(int num, Kind k)
{
	int x1, y1, x2, y2;
	int srcx, srcy;		// 从对象 Img 获取图片的左上角坐标

	// 循环 num 次后放完所有位置
	for (i = 0; i < num; i++)
	{
		// 选取一个随机的 -1 位置
		do
		{
			x1 = rand() % 19;
			y1 = rand() % 12;
		} while (xy[x1][y1] != -1);

		// 选取第二个随机 -1 位置
		do
		{
			x2 = rand() % 19;
			y2 = rand() % 12;
		} while (xy[x2][y2] != -1 || (x1 == x2 && y1 == y2)); // 扫描出地图

		if (k == ALL)					// 如果要从所有种类中选取
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

		// 从 Img 里面截取第 0 行、0~32 的随机图案
		if (k == QQ)
		{
			srcy = 0;
			srcx = rand() % 33;
		}

		// 第 1 行的 0~13 为小鸟图案
		if (k == BIRD)
		{
			srcy = 1;
			srcx = rand() % 14;
		}

		// 第 1 行的 14~30 为植物图案
		if (k == PLANT)
		{
			srcy = 1;
			srcx = rand() % 17 + 14;
		}

		// 第 2 行的 0~24 为动物图案
		if (k == PET)
		{
			srcy = 2;
			srcx = rand() % 25;
		}

		// 第 3 行的 0~21 为羊头图案
		if (k == SHEEP)
		{
			srcy = 3;
			srcx = rand() % 22;
		}

		// 第 4 行的 0~38 为KAVAI 图案
		if (k == KAVAI)
		{
			srcy = 4;
			srcx = rand() % 39;
		}

		// 在两个随机位置放置同样的图案
		putimage(x1 * GWIDTH + 1, y1 * GLENGTH + 1, PWIDTH, PLENGTH, &Img, srcx * PWIDTH, srcy * PLENGTH);
		putimage(x2 * GWIDTH + 1, y2 * GLENGTH + 1, PWIDTH, PLENGTH, &Img, srcx * PWIDTH, srcy * PLENGTH);

		xy[x1][y1] = xy[x2][y2] = -2;	// -2 表示已有图案的位置

		// 将图案在 Img 里面的位置与数组 ixy[][] 一一对应
		ixy[x1][y1].ix = ixy[x2][y2].ix = srcx + 1;	// 防止 = 0
		ixy[x1][y1].iy = ixy[x2][y2].iy = srcy + 1;
	}
}



// 开始游戏
void Start()
{
	while (game)
	{
		t2 = clock();

		// 画走动的时间条
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
				LButton();			// 调用左击函数
				break;
			case WM_LBUTTONUP:

				// 这些是为了在道具用光后保持按钮效果
				if (m.x >= 650 && m.x <= 680 && m.y >= 200 && m.y <= 240)
					putimage(600, 100, PWIDTH, PLENGTH, &Img, 21 * PWIDTH, 0 * PLENGTH);	// 弹起炸弹

				if (m.x >= 650 && m.x <= 680 && m.y >= 250 && m.y <= 290)
					putimage(600, 150, PWIDTH, PLENGTH, &Img, 31 * PWIDTH, 0 * PLENGTH);	// 弹起刷新

				if (m.x >= 650 && m.x <= 680 && m.y >= 300 && m.y <= 340)
					putimage(600, 200, PWIDTH, PLENGTH, &Img, 2 * PWIDTH, 5 * PLENGTH);		// 弹起扣扣

				if (m.x >= 650 && m.x <= 680 && m.y >= 350 && m.y <= 390)
					putimage(600, 250, PWIDTH, PLENGTH, &Img, 4 * PWIDTH, 5 * PLENGTH);		// 弹起小鸟

				if (m.x >= 650 && m.x <= 680 && m.y >= 400 && m.y <= 440)
					putimage(600, 300, PWIDTH, PLENGTH, &Img, 6 * PWIDTH, 5 * PLENGTH);		// 弹起植物

				if (m.x >= 650 && m.x <= 680 && m.y >= 450 && m.y <= 490)
					putimage(600, 350, PWIDTH, PLENGTH, &Img, 8 * PWIDTH, 5 * PLENGTH);		// 弹起宠物

				if (m.x >= 650 && m.x <= 680 && m.y >= 500 && m.y <= 540)
					putimage(600, 400, PWIDTH, PLENGTH, &Img, 10 * PWIDTH, 5 * PLENGTH);	// 弹起羊头

				if (m.x >= 650 && m.x <= 680 && m.y >= 550 && m.y <= 590)
					putimage(600, 450, PWIDTH, PLENGTH, &Img, 12 * PWIDTH, 5 * PLENGTH);	// 弹起卡哇伊

				break;
			default:
				break;
			}
		}
		if (!GameOver())								// 检测是否消掉所有图案
			game = false;
		Sleep(5);
	}
}

/***************************************************
					m.x / m.y 不受 setorigin() 影响！
					******************************************************************/

					// 左击函数
void LButton()
{
	PlaySound(_T(".\\sound\\click.wav"), 0, SND_ASYNC);
	setlinestyle(PS_DASH, 1);
	setcolor(BLUE);

	// 如果点击的是 ALL 模式-------------
	if (m.x >= 640 && m.x <= 690 && m.y >= 40 && m.y <= 80)
	{
		putimage(590, -60, BIGW, BIGL, &Img, 9 * 50, 6 * PLENGTH);	// 按下

		if (kind == ALL)
		{
			Plantsound(1);
			MessageBox(hwnd, _T("小样，苦海无边，回头非岸"), _T("提示"), MB_OK);
			putimage(590, -60, BIGW, BIGL, &Img, 8 * 50, 6 * PLENGTH);
			return;
		}

		if (MessageBox(hwnd, _T("亲，你做好随时牺牲的准备了嚒？"), _T("提示"), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			Plantsound(1);
			kind = ALL;
			refr++;						// 进入 ALL 模式不减刷新次数
			Refresh();
		}
		putimage(590, -60, BIGW, BIGL, &Img, 8 * 50, 6 * PLENGTH);	// 弹起
	}

	// 如果点击的是上一关按钮---------------
	if (m.x >= 380 && m.x <= 430 && m.y >= 40 && m.y <= 80)
	{
		putimage(330, -60, BIGW, BIGL, &Img, 7 * 50, 6 * PLENGTH);	// 按下
		if (MessageBox(hwnd, _T("你确定要回到上一关吗？"), _T("提示"), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			if (F > 1)
			{
				Qqsound(1);
				F--;
				Frame();
			}
			else
				MessageBox(hwnd, _T("亲，已经是第一关了。"), _T("提示"), MB_OK | MB_ICONWARNING);
		}
		else
			putimage(330, -60, BIGW, BIGL, &Img, 6 * 50, 6 * PLENGTH);	// 弹起上一关
	}

	// 如果点击的是关闭游戏按钮--------------
	if (m.x >= 200 && m.x <= 250 && m.y >= 40 && m.y <= 80)
	{
		putimage(150, -60, BIGW, BIGL, &Img, 5 * 50, 6 * PLENGTH);		// 按下
		if (MessageBox(hwnd, _T("你确定要关闭游戏吗？"), _T("提示"), MB_YESNO | MB_ICONQUESTION) == IDYES)
			game = 0;
		else
			putimage(150, -60, BIGW, BIGL, &Img, 4 * 50, 6 * PLENGTH);	// 弹起关闭
	}

	// 如果点击的是下一关按钮---------------
	if (m.x >= 120 && m.x <= 170 && m.y >= 40 && m.y <= 80)
	{
		putimage(70, -60, BIGW, BIGL, &Img, 3 * 50, 6 * PLENGTH);

		if (MessageBox(hwnd, _T("你确定要进入下一关吗？"), _T("提示"), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			Qqsound(1);
			F++;
			Frame();
		}
		else
			putimage(70, -60, BIGW, BIGL, &Img, 2 * 50, 6 * PLENGTH);	// 弹起下一关
	}
	// 如果点击的是背景颜色设置按钮--------------
	if (m.x >= 40 && m.x <= 90 && m.y >= 40 && m.y <= 80)
	{
		putimage(-10, -60, BIGW, BIGL, &Img, 1 * 50, 6 * PLENGTH);		// 按下
		ChangeBk();
	}

	// 如果点击的是炸弹道具---------------
	if (m.x >= 650 && m.x <= 680 && m.y >= 200 && m.y <= 240)
	{
		putimage(600, 100, PWIDTH, PLENGTH, &Img, 0 * PWIDTH, 5 * PLENGTH);		// 按下
		Bomb();
	}

	// 如果点击的是刷新道具-----------------
	if (m.x >= 650 && m.x <= 680 && m.y >= 250 && m.y <= 290)
	{
		putimage(600, 150, PWIDTH, PLENGTH, &Img, 1 * PWIDTH, 5 * PLENGTH);		// 按下
		Refresh();
	}

	// 如果点击的是扣扣模式------------------
	if (m.x >= 650 && m.x <= 680 && m.y >= 300 && m.y <= 340)
	{
		putimage(600, 200, PWIDTH, PLENGTH, &Img, 3 * PWIDTH, 5 * PLENGTH);		// 按下

		if (kind == QQ)
		{
			Qqsound(1);
			MessageBox(hwnd, _T("摆脱，姐姐不是公仔！"), _T("提示"), MB_OK);
			putimage(600, 200, PWIDTH, PLENGTH, &Img, 2 * PWIDTH, 5 * PLENGTH);	// 弹起
			return;
		}

		if (refr < 1)						// 如果刷新用光
		{
			Diongsound();
			return;
		}

		if (IDYES == MessageBox(hwnd, _T("那个啥，偶不系公仔！"), _T("Notice"), MB_YESNO | MB_ICONQUESTION))
		{
			Qqsound(1);
			kind = QQ;
			Refresh();
		}
		putimage(600, 200, PWIDTH, PLENGTH, &Img, 2 * PWIDTH, 5 * PLENGTH);		// 弹起
	}

	// 如果点击的是小鸟模式------------------------
	if (m.x >= 650 && m.x <= 680 && m.y >= 350 && m.y <= 390)
	{
		putimage(600, 250, PWIDTH, PLENGTH, &Img, 5 * PWIDTH, 5 * PLENGTH);		// 按下

		if (kind == BIRD)
		{
			Birdsound(1);
			MessageBox(hwnd, _T("丢，再点我、我跟你急！"), _T("提示"), MB_OK);
			putimage(600, 250, PWIDTH, PLENGTH, &Img, 4 * PWIDTH, 5 * PLENGTH);
			return;
		}

		if (refr < 1)						// 如果刷新用光
		{
			Diongsound();
			return;
		}

		if (IDYES == MessageBox(hwnd, _T("傻鸟，你真的想大战猪头？"), _T("Notice"), MB_YESNO | MB_ICONQUESTION))
		{
			Birdsound(1);
			kind = BIRD;
			Refresh();
		}
		putimage(600, 250, PWIDTH, PLENGTH, &Img, 4 * PWIDTH, 5 * PLENGTH);		// 弹起
	}

	// 如果点击的是植物模式---------------------
	if (m.x >= 650 && m.x <= 680 && m.y >= 400 && m.y <= 440)
	{
		putimage(600, 300, PWIDTH, PLENGTH, &Img, 7 * PWIDTH, 5 * PLENGTH);		// 按下

		if (kind == PLANT)
		{
			Plantsound(1);
			MessageBox(hwnd, _T("别急，僵尸快来了！"), _T("Notice"), MB_OK);
			putimage(600, 300, PWIDTH, PLENGTH, &Img, 6 * PWIDTH, 5 * PLENGTH);	// 弹起
			return;
		}

		if (refr < 1)						// 如果刷新用光
		{
			Diongsound();
			return;
		}

		if (IDYES == MessageBox(hwnd, _T("Are You 真的要大战僵尸？"), _T("Notice"), MB_YESNO | MB_ICONQUESTION))
		{
			Plantsound(1);
			kind = PLANT;
			Refresh();
		}
		putimage(600, 300, PWIDTH, PLENGTH, &Img, 6 * PWIDTH, 5 * PLENGTH);		// 弹起
	}

	// 如果点击的是鸭子模式-----------------------
	if (m.x >= 650 && m.x <= 680 && m.y >= 450 && m.y <= 490)
	{
		putimage(600, 350, PWIDTH, PLENGTH, &Img, 9 * PWIDTH, 5 * PLENGTH);		// 按下

		if (kind == PET)
		{
			Petsound(1);
			MessageBox(hwnd, _T("亲，丑小鸭不能再变丑了！"), _T("Notice"), MB_OK);
			putimage(600, 350, PWIDTH, PLENGTH, &Img, 8 * PWIDTH, 5 * PLENGTH);	// 弹起
			return;
		}

		if (refr < 1)						// 如果刷新用光
		{
			Diongsound();
			return;
		}

		if (IDYES == MessageBox(hwnd, _T("亲，别看我只是一只鸭！"), _T("Notice"), MB_YESNO | MB_ICONQUESTION))
		{
			Petsound(1);
			kind = PET;
			Refresh();
		}
		putimage(600, 350, PWIDTH, PLENGTH, &Img, 8 * PWIDTH, 5 * PLENGTH);		// 弹起
	}

	// 如果点击的是羊头模式-------------------------
	if (m.x >= 650 && m.x <= 680 && m.y >= 500 && m.y <= 540)
	{
		putimage(600, 400, PWIDTH, PLENGTH, &Img, 11 * PWIDTH, 5 * PLENGTH);		// 按下

		if (kind == SHEEP)
		{
			Sheepsound(1);
			MessageBox(hwnd, _T("灰太狼，再惹我，小心我打你pp！"), _T("Notice"), MB_OK);
			putimage(600, 400, PWIDTH, PLENGTH, &Img, 10 * PWIDTH, 5 * PLENGTH);	// 弹起
			return;
		}

		if (refr < 1)						// 如果刷新用光
		{
			Diongsound();
			return;
		}

		if (IDYES == MessageBox(hwnd, _T("亲，别看我只是一只羊！"), _T("Notice"), MB_YESNO | MB_ICONQUESTION))
		{
			Sheepsound(1);
			kind = SHEEP;
			Refresh();
		}
		putimage(600, 400, PWIDTH, PLENGTH, &Img, 10 * PWIDTH, 5 * PLENGTH);		// 弹起
	}

	// 如果点击的是卡哇伊模式-------------------------
	if (m.x >= 650 && m.x <= 680 && m.y >= 550 && m.y <= 590)
	{
		putimage(600, 450, PWIDTH, PLENGTH, &Img, 13 * PWIDTH, 5 * PLENGTH);		// 按下

		if (kind == KAVAI)					// 如果已经是该模式
		{
			Kavaisound(1);
			MessageBox(hwnd, _T("亲，你知道柳州哪里有意大利面条卖吗？Tell Me(924553536@qq.com)"), _T("Notice"), MB_OK);
			putimage(600, 450, PWIDTH, PLENGTH, &Img, 12 * PWIDTH, 5 * PLENGTH);	// 弹起
			return;
		}

		if (refr < 1)						// 如果刷新用光
		{
			Diongsound();
			return;
		}

		if (IDYES == MessageBox(hwnd, _T("爱三来了，爱四还远吗？"), _T("Notice"), MB_YESNO | MB_ICONQUESTION))
		{
			Kavaisound(1);
			kind = KAVAI;
			Refresh();
		}
		putimage(600, 450, PWIDTH, PLENGTH, &Img, 12 * PWIDTH, 5 * PLENGTH);		// 弹起
	}

	// 如果鼠标点击范围在图案区内 ***********************
	if (m.x > 50 && m.x < 620 && m.y > 100 && m.y < 580)
	{
		if (mhitnum % 2 == 0)		// 单击一次记录在m1
		{
			// 擦掉上次鼠标点击时的虚框，mx(y)2 的初始值 -20 已经放到屏幕外了。
			setcolor(getbkcolor());
			rectangle(mx2 * GWIDTH, my2 * GLENGTH, (mx2 + 1) * GWIDTH - 1, (my2 + 1) * GLENGTH - 2);

			mx1 = (m.x - 50) / 30;	// 由鼠标坐标求出鼠标所在的格子
			my1 = (m.y - 100) / 40;	// 除法运算符只取整数，不做四舍五入

			setcolor(BLUE);			// 画选择虚框
			rectangle(mx1 * GWIDTH, my1 * GLENGTH, (mx1 + 1) * GWIDTH - 1, (my1 + 1) * GLENGTH - 2);
		}
		else						// 再单击一次记录在m2
		{
			setcolor(getbkcolor());	// 擦掉上次鼠标点击时的虚框
			rectangle(mx1 * GWIDTH, my1 * GLENGTH, (mx1 + 1) * GWIDTH - 1, (my1 + 1) * GLENGTH - 2);

			mx2 = (m.x - 50) / 30;
			my2 = (m.y - 100) / 40;

			setcolor(BLUE);			// 画选择虚框
			rectangle(mx2 * GWIDTH, my2 * GLENGTH, (mx2 + 1) * GWIDTH - 1, (my2 + 1) * GLENGTH - 2);
		}
		mhitnum++;					// 将鼠标的坐标轮流赋予 mx(y)1、 mx(y)2

		// 如果点击的是两个不同位置的相同图案
		if (ixy[mx1][my1].ix == ixy[mx2][my2].ix
			&& ixy[mx1][my1].iy == ixy[mx2][my2].iy
			&& (mx1 != mx2 || my1 != my2)
			&& xy[mx1][my1] != 0 /*这个是为了避免点击的是两个空白图案*/)
		{
			// 如果点击的是两个相邻的相同图案(左右相邻、上下相邻)
			if ((Minn(mx1, mx2) + 1 == Maxx(mx1, mx2) && my1 == my2) || (mx1 == mx2 && Minn(my1, my2) + 1 == Maxx(my1, my2)))
			{
				// 直接消掉返回函数
				Clear(mx1, my1, mx2, my2);
				Degemsound();
				return;
			}

			// 如果可消
			if (Check(mx1, my1, mx2, my2, true, 200))	// true 代表连线， 200 代表连线显示的时间
			{
				if (kind == KAVAI)
					Kavaisound(2);
				Clear(mx1, my1, mx2, my2);
			}
		}
	}
}



// 取被点击的图案所在坐标的：最大值、左边的 y 值、上边的 x 值
int Maxx(int a, int b, int c, int d)
{
	int max;
	max = (a > b) ? a : b;

	if (c < d)		// (c, a)/(d, b) 比较 x 坐标，返回 y 坐标
		return a;
	if (c > d)
		return b;
	else
		return max;
}



// 取最小值、右边的 y 值、下边的 x 值
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



// 检测相消路线，t 用于显示连线的时间长短
bool Check(int mx1, int my1, int mx2, int my2, bool line, int t)
{
	int mx, my;			// 表示转折点的坐标
	int a, b, c;
	setlinestyle(PS_SOLID, 2);

	// 检测第一种路线(mx 在 mx1, mx2 之间)-------------------------
	for (mx = Minn(mx1, mx2) + 1; mx < Maxx(mx1, mx2); mx++)
	{
		// 每次扫描开始都要重置初始值
		a = 0, b = 0, c = 0;

		// 扫描在 Minn(my1, my2) 处从 Minn(mx1, mx2) + 1 到 mx 的行 
		for (x = Minn(mx1, mx2) + 1; x <= mx; x++)
			a += xy[x][Maxx(my1, my2, mx1, mx2)];	// 取左边的 y

		// 扫描在 mx 处从 Minn(my1, my2) 到 Maxx(my1, my2) 的列
		for (y = Minn(my1, my2); y <= Maxx(my1, my2); y++)
			b += xy[mx][y];

		// 扫描在 Maxx(my1, my2) 处从 mx 到 Maxx(mx1, mx2) - 1 的行
		for (x = mx; x < Maxx(mx1, mx2); x++)
			c += xy[x][Minn(my1, my2, mx1, mx2)];	// 取右边的 y

		// 检测 a->b->c 这条路是否通
		if (a + b + c == 0)
		{
			if (line)
			{
				if (kind == BIRD)					// 设置不同的音效
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

	// 检测另一条 a->b->c 的路线(my 在 my1, my2 之间)-------------------------
	for (my = Minn(my1, my2) + 1; my < Maxx(my1, my2); my++)
	{
		// 每次扫描开始都要重置初始值
		a = 0, b = 0, c = 0;

		// 扫描在 Minn(mx1, mx2) 处从 Minn(my1, my2) + 1 到 my 的列
		for (y = Minn(my1, my2) + 1; y <= my; y++)
			a += xy[Maxx(mx1, mx2, my1, my2)][y];		// 取上边的 x

		// 扫描在 my 处从 Minn(mx1, mx2) 到 Maxx(mx1, mx2) 的行
		for (x = Minn(mx1, mx2); x <= Maxx(mx1, mx2); x++)
			b += xy[x][my];

		// 扫描在 Maxx(mx1, mx2) 处从 my 到 Maxx(my1, my2) - 1 的列
		for (y = my; y < Maxx(my1, my2); y++)
			c += xy[Minn(mx1, mx2, my1, my2)][y];		// 取下边的 x

		// 检测 a->b->c 这条路是否通
		if (a + b + c == 0)
		{
			if (line)
			{
				if (kind == BIRD)					// 设置不同的音效
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

	// 检测第三条路线(mx 在 mx1, mx2 左边)----------------------------
	for (mx = 0; mx < Minn(mx1, mx2); mx++)
	{
		a = 0, b = 0, c = 0;

		// 扫描在左边的 y 处从 mx 到 Minn(mx1, mx2) - 1 的行
		for (x = mx; x < Minn(mx1, mx2); x++)
			a += xy[x][Maxx(my1, my2, mx1, mx2)];	// 取左边的 y

		// 扫描在 mx 处从 Minn(my1, my2) 到 Maxx(my1, my2) 的列 
		for (y = Minn(my1, my2); y <= Maxx(my1, my2); y++)
			b += xy[mx][y];

		// 扫描在右边的 y 处从 mx 到 Maxx(mx1, mx2) - 1 的行
		for (x = mx; x < Maxx(mx1, mx2); x++)
			c += xy[x][Minn(my1, my2, mx1, mx2)];	// 取右边的 y

		if (a + b + c == 0)
		{
			if (line)
			{
				if (kind == BIRD)					// 设置不同的音效
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

	// 当转折点 mx = Minn(mx1, mx2) 的时候扫描两种路径--------------------------------
	for (mx = Minn(mx1, mx2); mx <= Minn(mx1, mx2); mx++)
	{
		a = 0, b = 0, c = 0;

		// 扫描在右边的 y 处从 mx 到 Maxx(mx1, mx2) - 1 的行
		for (x = mx; x < Maxx(mx1, mx2); x++)
			a += xy[x][Minn(my1, my2, mx1, mx2)];	// 取右边的 y

		// 扫描在 mx 处从 Minn(my1, my2) + 1 到 Maxx(my1, my2) 的列 
		for (y = Minn(my1, my2) + 1; y <= Maxx(my1, my2); y++)
			b += xy[mx][y];

		// 扫描在 mx 处从 Minn(my1, my2) 到 Maxx(my1 ,my2) - 1 的列
		for (y = Minn(my1, my2); y < Maxx(my1, my2); y++)
			c += xy[mx][y];

		if (a + b == 0 || a + c == 0)
		{
			if (line)
			{
				if (kind == BIRD)					// 设置不同的音效
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

	// 检测第四条路线(mx 在 mx1, mx2 的右边)-------------------------------
	for (mx = Maxx(mx1, mx2) + 1; mx < 19; mx++)
	{
		a = 0, b = 0, c = 0;

		// 扫描在左边的 y 处从 Minn(mx1, mx2) + 1 到 mx 的行
		for (x = Minn(mx1, mx2) + 1; x <= mx; x++)
			a += xy[x][Maxx(my1, my2, mx1, mx2)];		// 左边的 y 

		// 扫描在 mx 处从 Minn(my1, my2) 到 Maxx(my1, my2) 的列
		for (y = Minn(my1, my2); y <= Maxx(my1, my2); y++)
			b += xy[mx][y];

		// 扫描在右边的 y 处从 Maxx(mx1, mx2) + 1 到 mx 的行
		for (x = Maxx(mx1, mx2) + 1; x <= mx; x++)
			c += xy[x][Minn(my1, my2, mx1, mx2)];		// 右边的 y

		if (a + b + c == 0)
		{
			if (line)
			{
				if (kind == BIRD)					// 设置不同的音效
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

	// 当转折点 mx = Maxx(mx1, mx2) 的时候扫描两种路径------------------------------
	for (mx = Maxx(mx1, mx2); mx <= Maxx(mx1, mx2); mx++)
	{
		a = 0, b = 0, c = 0;

		// 扫描在左边的 y 处从 Minn(mx1, mx2) + 1 到 mx 的行
		for (x = Minn(mx1, mx2) + 1; x <= mx; x++)
			a += xy[x][Maxx(my1, my2, mx1, mx2)];		// 左边的 y

		// 扫描在 mx 处从 Minn(my1, my2) 到 Maxx(my1, my2) - 1 的列
		for (y = Minn(my1, my2); y < Maxx(my1, my2); y++)
			b += xy[mx][y];

		// 扫描在 mx 处从 Minn(my1, my2) + 1 到 Maxx(my1, my2) 的列
		for (y = Minn(my1, my2) + 1; y <= Maxx(my1, my2); y++)
			c += xy[mx][y];

		// 只要有一种路线行得通
		if (a + b == 0 || a + c == 0)
		{
			if (line)
			{
				if (kind == BIRD)					// 设置不同的音效
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

	// 检测第五条路线(my 在 my1, my2 的上面)-----------------------------
	for (my = 0; my < Minn(my1, my2); my++)
	{
		a = 0, b = 0, c = 0;

		// 扫描在上边 x 处从 my 到 Minn(my1, my2) - 1 的列
		for (y = my; y < Minn(my1, my2); y++)
			a += xy[Maxx(mx1, mx2, my1, my2)][y];		// 取上边的 x

		// 扫描在 my 处从 Minn(mx1, mx2) 到 Maxx(mx1, mx2) 的行
		for (x = Minn(mx1, mx2); x <= Maxx(mx1, mx2); x++)
			b += xy[x][my];

		// 扫描在下边 x 处从 my 到 Maxx(my1, my2) - 1 的列
		for (y = my; y < Maxx(my1, my2); y++)
			c += xy[Minn(mx1, mx2, my1, my2)][y];		// 取下边的 x

		if (a + b + c == 0)
		{
			if (line)
			{
				if (kind == BIRD)					// 设置不同的音效
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

	// 检测第六条路线(my 在 my1, my2 的下面)---------------------------
	for (my = Maxx(my1, my2) + 1; my < 12; my++)
	{
		a = 0, b = 0, c = 0;

		// 扫描在上边 x 处从 Minn(my1, my2) + 1 到 my 的列
		for (y = Minn(my1, my2) + 1; y <= my; y++)
			a += xy[Maxx(mx1, mx2, my1, my2)][y];		// 取上边的 x

		// 扫描在 my 处从 Minn(mx1, mx2) 到 Maxx(mx1, mx2) 的行
		for (x = Minn(mx1, mx2); x <= Maxx(mx1, mx2); x++)
			b += xy[x][my];

		// 扫描在下边 x 处从 Maxx(my1, my2) + 1 到 my 的列
		for (y = Maxx(my1, my2) + 1; y <= my; y++)
			c += xy[Minn(mx1, mx2, my1, my2)][y];		// 取下边的 x

		if (a + b + c == 0)
		{
			if (line)									// 如果需要连线
			{
				if (kind == BIRD)					// 设置不同的音效
				{
					Birdsound(2);
				}
				else if (kind != KAVAI)
				{
					Degemsound();
				}
				// 连线之前播放声音可以避免声音被下面的 Sleep(t) 延时

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



// 消掉 (ax, ay) 和 (bx, by) 两个的图案
void Clear(int ax, int ay, int bx, int by)
{
	setfillstyle(BLACK);
	setcolor(0x90d2d2);
	setlinestyle(0, 2);

	// 剩余图案数
	bar(650, 57, 710, 77);

	// 擦掉积分
	bar(650, 7, 730, 27);

	// 输出剩余数
	SNum -= 2;
	setcolor(0x00aaff);
	_stprintf_s(snum, _T("%03d"), SNum);
	outtextxy(667, 60, snum);

	// 输出积分
	Mark += 1007;
	_stprintf_s(mark, _T("%08d"), Mark);
	outtextxy(662, 10, mark);

	// 擦掉传递过来的两个图案
	setfillcolor(getbkcolor());
	bar(ax * GWIDTH + 1, ay * GLENGTH + 1, (ax + 1) * GWIDTH - 2, (ay + 1) * GLENGTH - 3);
	bar(bx * GWIDTH + 1, by * GLENGTH + 1, (bx + 1) * GWIDTH - 2, (by + 1) * GLENGTH - 3);

	// 消掉过后标记该两位置为 0
	xy[ax][ay] = 0;
	xy[bx][by] = 0;

	// 释放数组 ixy[][] 与 Img 里面图案的一一对应关系
	ixy[ax][ay].ix = ixy[bx][by].ix = 0;
	ixy[ax][ay].iy = ixy[bx][by].iy = 0;

	Time();			// 检测积分，是否可以赠送时间
}



// 检测游戏结束与否
bool GameOver()
{
	int sum = 0;

	for (x = 0; x < 19; x++)
		for (y = 0; y < 12; y++)
			sum += xy[x][y];	// ix, iy 都一样

	if (sum == 0)
	{
		// 分类播放声音
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

		MessageBox(hwnd, _T("WAHOO! Continue"), _T("提示"), MB_OK);

		F++;
		Frame();			// 开始新游戏
		return true;
	}

	if (tx > 700)
	{
		Amengsound();
		if (MessageBox(hwnd, _T("真水！你系不系一头水货？"), _T("TimeOver"), MB_YESNO | MB_ICONQUESTION) == IDYES)
			return false;
		else
		{
			Frame();
			return true;
		}
	}
	return true;
}



// 炸弹函数
void Bomb()
{
	int xa, ya, xb, yb;
	int t1, t2;				// 防止出现死局，导致无限循环
	t1 = clock();

	if (bomb < 1)			// 如果炸弹用光
	{
		Diongsound();
		return;
	}

	// 扫描可以炸掉的图案
	do
	{
		xa = rand() % 19;
		ya = rand() % 12;
		xb = rand() % 19;
		yb = rand() % 12;

		// 如果该位置记录的图案相同并且 非空
		if (ixy[xa][ya].ix == ixy[xb][yb].ix
			&& ixy[xa][ya].iy == ixy[xb][yb].iy
			&& xy[xa][ya] != 0)
		{
			// 如果扫描得到的是两个相邻的相同图案(左右相邻、上下相邻)
			if ((Minn(xa, xb) + 1 == Maxx(xa, xb) && ya == yb) || (xa == xb && Minn(ya, yb) + 1 == Maxx(ya, yb)))
				break;	// 直接退出循环
		}

		t2 = clock();
		if (t2 - t1 > 2000)		// 如果两秒钟还没有找到可以相连的图案 / 则死局，只能刷新
		{
			Amengsound();
			MessageBox(hwnd, _T("啊偶，木有可连的，等死吧！"), _T("注意"), MB_OK | MB_ICONWARNING);
			return;
		}

	} while (!Check(xa, ya, xb, yb, 0, 0)
		|| ixy[xa][ya].ix != ixy[xb][yb].ix
		|| ixy[xa][ya].iy != ixy[xb][yb].iy
		|| (xa == xb && ya == yb)
		|| xy[xa][ya] == 0
		|| xy[xb][yb] == 0);
	// 如果 不可连、两个图案不是同一种图案、两者压根儿就是同一位置的图案、该位置没有图案 / 都要重新循环


	// 连线并显示 500 毫秒
	Check(xa, ya, xb, yb, true, 500);
	if (kind == KAVAI)
		Kavaisound(2);
	Bombsound();
	Clear(xa, ya, xb, yb);

	// 擦掉旧数据
	setfillstyle(BLACK);
	setcolor(0x90d2d2);
	setlinestyle(0, 2);
	bar(650, 107, 710, 127);

	// 输出剩余炸弹数
	bomb--;
	_stprintf_s(bom, _T("%02d"), bomb);
	setcolor(0x00aaff);
	outtextxy(672, 110, bom);
}



// 刷新图案
void Refresh()
{
	int photo = 0;		// 记录原有图案数

	if (refr < 1)		// 如果刷新用光
	{
		Diongsound();
		return;
	}

	// 扫描出剩余图案数
	for (y = 0; y < 12; y++)
	{
		for (x = 0; x < 19; x++)
		{
			// 如果该位置有图案
			if (xy[x][y] != 0)
			{
				photo++;				// 数量 + 1
				xy[x][y] = -1;		// 重新标记该位置为 -1，待放新图案
			}
		}
	}

	// 在原来的所有位置重新放置随机图案
	Putimg(photo / 2, kind);

	/********* 擦掉原来的 ************/

	setfillstyle(BLACK);
	setcolor(0x90d2d2);
	setlinestyle(0, 2);

	bar(650, 157, 710, 177);	// 刷新次数
	bar(650, 207, 710, 227);	// 企鹅模式
	bar(650, 257, 710, 277);	// 小鸟模式
	bar(650, 307, 710, 327);	// 植物模式
	bar(650, 357, 710, 377);	// 鸭子模式
	bar(650, 407, 710, 427);	// 羊头模式
	bar(650, 457, 710, 477);	// kavai模式

/********* 擦掉原来的 ************/


	// 输出更新后的信息
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



// 用于减缓时间流逝
void Time()
{
	if (Mark % 15105 == 0 && Mark != 0)	// 如果每消掉 15 对图案后
	{
		setfillstyle(getbkcolor());
		bar(tx - 50, -90, tx, -85);
		tx -= 50;						// 每消掉 15 对时间往回退 50 单位
	}
}



// 设置背景色
void ChangeBk()
{
	TCHAR bkr[20], bkg[20], bkb[20];		// 接收字符串

	// 如果用户点击了取消则不改变曾经的 r, g, b 值
	if (InputBox(bkr, 20, NULL, _T("亲，输入RGB中的(0~255)红色数值。"), _T("212"), 0, 0, 0))
		_tscanf_s(bkr, _T("%d"), &r);			// 将字符串转为数字

	if (InputBox(bkg, 20, NULL, _T("(0~255)绿色数值。"), _T("164"), 0, 0, 0))
		_tscanf_s(bkg, _T("%d"), &g);

	if (InputBox(bkb, 20, NULL, _T("亲，输入RGB中的(0~255)蓝色数值。--------"), _T("72"), 0, 0, 0))
		_tscanf_s(bkb, _T("%d"), &b);

	bkcolor = RGB(r, g, b);
	Draw();

	setfillstyle(LIGHTGREEN);			// 用于还原已经过去了的时间条
	bar(-45, -90, tx, -85);

	for (x = 0; x <= 18; x++)
		for (y = 0; y <= 11; y++)
		{
			if (xy[x][y] != 0)
				putimage(x * GWIDTH + 1, y * GLENGTH + 1, PWIDTH, PLENGTH, &Img, (ixy[x][y].ix - 1) * PWIDTH, (ixy[x][y].iy - 1) * PLENGTH);
		}

	putimage(-10, -60, BIGW, BIGL, &Img, 0 * 50, 6 * PLENGTH);		// 弹起
}



// 打开随机背景音乐预备播放
void Openmusic()
{
	s = rand() % 5;

	switch (s)
	{
		// 背景音乐、别名
	case 0:	mciSendString(_T("open .\\sound\\别看我只是一只羊.mp3	alias bmusic1"), 0, 0, 0);	break;
	case 1:	mciSendString(_T("open .\\sound\\flower.mp3			alias bmusic2"), 0, 0, 0);	break;
	case 2:	mciSendString(_T("open .\\sound\\luvletter.mp3			alias bmusic3"), 0, 0, 0);	break;
	case 3:	mciSendString(_T("open .\\sound\\thedeath.mp3			alias bmusic4"), 0, 0, 0);	break;
	case 4: mciSendString(_T("open \".\\sound\\the truth.mp3\"		alias bmusic5"), 0, 0, 0);	break;	// 文件名有空格的写法
	default:	break;
	}
}



// 播放背景音乐
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



// 停止播放背景音乐
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