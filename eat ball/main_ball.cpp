/*
程序名称：
大球吃小球
简介：
模拟小游戏，左键按下状态拖动小球进行移动，躲避大球的同时尽量多吃小球
环境：
VS2019 + EasyX_20210115(beta)
时间：
2021.2.4
作者：
Teternity(QQ:1926594835)
版权：
作者原创，无抄袭，不涉及版权问题，仅用作学习
*/
#pragma warning(default: 4996)

/* ---------------头文件--------------- */
#include <graphics.h>  
#include <iostream>
#include <vector>
#include <mutex>
#include <future>
#include <easyx.h>
#include <conio.h>


/* ---------------全局量--------------- */
const int win_width = 640;			// 窗口宽
const int win_height = 468;			// 窗口高
const int ir = 5;					// 玩家控制的小球初始半径
int r = ir;							// 玩家控制的小球半径
int score = 0;						// 得分：所吃小球的半径之和
const int nBall = 38;				// 小球数
int px = 320, py = 240;				// 玩家控制的小球位置
const COLORREF color = WHITE;		// 玩家控制的小球颜色
bool finished = false;	// 是否结束
std::mutex drawMut;					// 绘制锁


/* ---------------小球数据结构--------------- */
struct Ball
{
	int r;							// 半径
	int px, py;						// 位置
	int dx, dy;						// 方向
	COLORREF color;					// 颜色
	clock_t speed, tcur, tborn;		// 速度、当前刷新时间、创建时间
};


/* ---------------新建小球--------------- */
void NewBall(Ball& ball)
{
	ball.r = rand() % 20 + 3;
	ball.px = rand() % 640;
	ball.py = rand() % 480;
	ball.dx = (rand() % 3 + 1) * ((rand() % 100) > 50 ? 1 : -1);
	ball.dy = (rand() % 3 + 1) * ((rand() % 100) > 50 ? 1 : -1);
	ball.color = HSVtoRGB(rand() % 360, (rand() % 50 + 50) / 100.0f, (rand() % 50 + 50) / 100.0f);
	ball.speed = rand() % 20 + 30;
	ball.tcur = clock();
	ball.tborn = clock();
}


/* ---------------根据小球颜色绘制小球--------------- */
void DrawBall(int x, int y, int r, COLORREF c, bool self = false)
{
	drawMut.lock();
	setfillcolor(c);
	solidcircle(x, y, r);
	if (self) circle(x, y, r + 4);
	drawMut.unlock();
}


/* ---------------运行--------------- */
void RunThread()
{
	srand((unsigned)time(nullptr));
	// 创建小球并显示
	std::vector<Ball> vb;
	vb.resize(nBall);
	for (int i = 0; i < nBall; ++i)
	{
		Ball ball{};
		NewBall(ball);
		vb[i] = ball;
	}
	for (auto& val : vb) DrawBall(val.px, val.py, val.r, val.color);
	FlushBatchDraw();

	auto it = vb.begin();
	while (true)
	{
		if (it == vb.end()) it = vb.begin();

		// 可以刷新位置
		if (clock() - it->tcur >= it->speed)
		{
			DrawBall(it->px, it->py, it->r, it->color);
			it->px += it->dx;
			it->py += it->dy;
			DrawBall(it->px, it->py, it->r, it->color);
			FlushBatchDraw();
			it->tcur = clock();
		}
		// 小球相撞
		if (sqrt((px - it->px) * (px - it->px) + (py - it->py) * (py - it->py)) <= 1.0 * r + it->r)
		{
			// 结束
			if (it->r >= r && clock() - it->tborn > 800)
			{
				finished = true;
				return;
			}
			// 玩家吃到
			else if (it->r < r && clock() - it->tborn > 500)
			{
				score += it->r;
				DrawBall(it->px, it->py, it->r, it->color);
				NewBall(*it);
				DrawBall(it->px, it->py, it->r, it->color);
				FlushBatchDraw();
			}
		}
		// 小球出边界
		else if (it->px < -it->r / 2 || it->px > 639 + it->r / 2 || it->py < -it->r / 2 || it->py > 479 + it->r / 2)
		{
			DrawBall(it->px, it->py, it->r, it->color);
			NewBall(*it);
			DrawBall(it->px, it->py, it->r, it->color);
			FlushBatchDraw();
		}

		++it;
	}
}


/* ---------------开始界面--------------- */
bool Start()
{
	settextcolor(RGB(220, 140, 0));
	settextstyle(48, 0, _T("楷体"));
	const TCHAR* text = _T("大球吃小球");
	outtextxy((win_width - textwidth(text)) / 2, (win_height - textheight(text)) / 8, text);

	settextstyle(24, 0, _T("楷体"));
	text = _T("左键按下开始游戏，右键按下退出");
	outtextxy((win_width - textwidth(text)) / 2, (win_height - textheight(text)) / 2, text);

	settextstyle(20, 0, _T("楷体"));
	text = _T("左键按下拖动小球，躲避大球的同时尽量多的吃小球");
	outtextxy((win_width - textwidth(text)) / 2, (win_height - textheight(text)) / 8 * 7, text);

	MOUSEMSG msg{};
	bool quit = true;
	while (true)
	{
		if (MouseHit())
		{
			while (MouseHit()) msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				quit = false;
				break;
			}
			else if (msg.uMsg == WM_RBUTTONDOWN) break;
		}
		Sleep(1);
	}

	return !quit;
}


/* ---------------主程序--------------- */
int main()
{
	initgraph(win_width, win_height, EX_NOMINIMIZE);
	setrop2(R2_XORPEN);

	if (Start()) cleardevice();
	else
	{
		closegraph();
		return 0;
	}

	while (true)
	{
		// 重置数据
		r = ir;
		score = 0;
		px = 320;
		py = 240;
		finished = false;

		// 绘制小球并运行线程
		cleardevice();
		setlinecolor(LIGHTGRAY);
		DrawBall(px, py, r, color, true);

		BeginBatchDraw();
		std::thread(RunThread).detach();

		// 游戏循环
		bool ldown = false;
		MOUSEMSG msg{};
		int mx = -1, my = -1;
		while (!finished)
		{
			if (MouseHit())
			{
				while (MouseHit()) msg = GetMouseMsg();
				// 左键按下
				if (msg.uMsg == WM_LBUTTONDOWN)
				{
					ldown = true;
					mx = msg.x;
					my = msg.y;
				}
				// 左键按下状态拖动鼠标
				else if (ldown && msg.mkLButton && msg.uMsg == WM_MOUSEMOVE)
				{
					if (finished) break;
					DrawBall(px, py, r, color, true);
					px += msg.x - mx;
					py += msg.y - my;
					int temp = ir + score / 20;
					if (temp < 20) r = temp;
					DrawBall(px, py, r, color, true);
					FlushBatchDraw();
					mx = msg.x;
					my = msg.y;
				}
				// 左键抬起
				else if (msg.uMsg == WM_LBUTTONUP)
				{
					mx = -1;
					my = -1;
				}
			}
			Sleep(1);
		}
		EndBatchDraw();

		// 结束弹窗
		TCHAR text[128]{};
		_stprintf_s(text, _T("恭喜你得分 %d，是否继续游戏？"), score);
		if (IDNO == MessageBox(GetHWnd(), text, _T("游戏结束"), MB_YESNO)) break;
	}

	closegraph();
	return 0;
}