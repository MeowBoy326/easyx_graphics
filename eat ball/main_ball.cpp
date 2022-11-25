/*
�������ƣ�
�����С��
��飺
ģ��С��Ϸ���������״̬�϶�С������ƶ�����ܴ����ͬʱ�������С��
������
VS2019 + EasyX_20210115(beta)
ʱ�䣺
2021.2.4
���ߣ�
Teternity(QQ:1926594835)
��Ȩ��
����ԭ�����޳�Ϯ�����漰��Ȩ���⣬������ѧϰ
*/
#pragma warning(default: 4996)

/* ---------------ͷ�ļ�--------------- */
#include <graphics.h>  
#include <iostream>
#include <vector>
#include <mutex>
#include <future>
#include <easyx.h>
#include <conio.h>


/* ---------------ȫ����--------------- */
const int win_width = 640;			// ���ڿ�
const int win_height = 468;			// ���ڸ�
const int ir = 5;					// ��ҿ��Ƶ�С���ʼ�뾶
int r = ir;							// ��ҿ��Ƶ�С��뾶
int score = 0;						// �÷֣�����С��İ뾶֮��
const int nBall = 38;				// С����
int px = 320, py = 240;				// ��ҿ��Ƶ�С��λ��
const COLORREF color = WHITE;		// ��ҿ��Ƶ�С����ɫ
bool finished = false;	// �Ƿ����
std::mutex drawMut;					// ������


/* ---------------С�����ݽṹ--------------- */
struct Ball
{
	int r;							// �뾶
	int px, py;						// λ��
	int dx, dy;						// ����
	COLORREF color;					// ��ɫ
	clock_t speed, tcur, tborn;		// �ٶȡ���ǰˢ��ʱ�䡢����ʱ��
};


/* ---------------�½�С��--------------- */
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


/* ---------------����С����ɫ����С��--------------- */
void DrawBall(int x, int y, int r, COLORREF c, bool self = false)
{
	drawMut.lock();
	setfillcolor(c);
	solidcircle(x, y, r);
	if (self) circle(x, y, r + 4);
	drawMut.unlock();
}


/* ---------------����--------------- */
void RunThread()
{
	srand((unsigned)time(nullptr));
	// ����С����ʾ
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

		// ����ˢ��λ��
		if (clock() - it->tcur >= it->speed)
		{
			DrawBall(it->px, it->py, it->r, it->color);
			it->px += it->dx;
			it->py += it->dy;
			DrawBall(it->px, it->py, it->r, it->color);
			FlushBatchDraw();
			it->tcur = clock();
		}
		// С����ײ
		if (sqrt((px - it->px) * (px - it->px) + (py - it->py) * (py - it->py)) <= 1.0 * r + it->r)
		{
			// ����
			if (it->r >= r && clock() - it->tborn > 800)
			{
				finished = true;
				return;
			}
			// ��ҳԵ�
			else if (it->r < r && clock() - it->tborn > 500)
			{
				score += it->r;
				DrawBall(it->px, it->py, it->r, it->color);
				NewBall(*it);
				DrawBall(it->px, it->py, it->r, it->color);
				FlushBatchDraw();
			}
		}
		// С����߽�
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


/* ---------------��ʼ����--------------- */
bool Start()
{
	settextcolor(RGB(220, 140, 0));
	settextstyle(48, 0, _T("����"));
	const TCHAR* text = _T("�����С��");
	outtextxy((win_width - textwidth(text)) / 2, (win_height - textheight(text)) / 8, text);

	settextstyle(24, 0, _T("����"));
	text = _T("������¿�ʼ��Ϸ���Ҽ������˳�");
	outtextxy((win_width - textwidth(text)) / 2, (win_height - textheight(text)) / 2, text);

	settextstyle(20, 0, _T("����"));
	text = _T("��������϶�С�򣬶�ܴ����ͬʱ������ĳ�С��");
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


/* ---------------������--------------- */
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
		// ��������
		r = ir;
		score = 0;
		px = 320;
		py = 240;
		finished = false;

		// ����С�������߳�
		cleardevice();
		setlinecolor(LIGHTGRAY);
		DrawBall(px, py, r, color, true);

		BeginBatchDraw();
		std::thread(RunThread).detach();

		// ��Ϸѭ��
		bool ldown = false;
		MOUSEMSG msg{};
		int mx = -1, my = -1;
		while (!finished)
		{
			if (MouseHit())
			{
				while (MouseHit()) msg = GetMouseMsg();
				// �������
				if (msg.uMsg == WM_LBUTTONDOWN)
				{
					ldown = true;
					mx = msg.x;
					my = msg.y;
				}
				// �������״̬�϶����
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
				// ���̧��
				else if (msg.uMsg == WM_LBUTTONUP)
				{
					mx = -1;
					my = -1;
				}
			}
			Sleep(1);
		}
		EndBatchDraw();

		// ��������
		TCHAR text[128]{};
		_stprintf_s(text, _T("��ϲ��÷� %d���Ƿ������Ϸ��"), score);
		if (IDNO == MessageBox(GetHWnd(), text, _T("��Ϸ����"), MB_YESNO)) break;
	}

	closegraph();
	return 0;
}