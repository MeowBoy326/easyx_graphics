///////////////////////////////////////////////////
// �������ƣ�̰���� 1.6
// ���뻷����Microsoft Visual studio 2017��EasyX_20200727
// �������ߣ�����
// �ʡ����䣺2190038793@qq.com
// �������ڣ�2019-2-10
// ����޸ģ�2019-2-15
//
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <wchar.h>

#define WIDTH		1024			// ��Ļ��
#define HEIGHT		576				// ��Ļ��
#define MAPW		(WIDTH * 4)		// ��ͼ��
#define MAPH		(HEIGHT * 4)	// ��ͼ��
#define AINUM       100				// AI ����
#define FNUM        2000			// FOOD ����
#define PTIME       180				// ��Ȧˢ��ʱ��
#define DISTANCE(x1, y1, x2, y2)	(sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)))

struct FOOD
{
	bool		eat;
	COLORREF	color;		// ��ɫ
	int			x, y;		// ����
	char		type;
};

struct BALL					// ����С��ṹ
{
	bool		life;		// ����
	COLORREF	color;		// ��ɫ
	int			x, y;		// ����
	float		r;			// �뾶
};

FOOD food[FNUM];								// ʳ��
BALL mover = { 1, RGB(0, 0, 0), 0, 0, 0 };	// ���
BALL ai[AINUM] = { 1, RGB(0, 0, 0), 0, 0, 0 };	// �������

void move(BALL* ball);				// ����ƶ�
void draw();						// ��ͼ
void start();						// ��Ϸ��ʼ
void setall();						// ��ʼ������
void AI();							// AI
void Food();						// ʳ��
void delay(DWORD ms);				// ������ʱ

DWORD* pBuffer;						// ��ʾ������ָ��
int eaten = 0;						// �� AI ������
int ai_eaten = 0;					// AI �� AI������
int lx = -20, ly = MAPH + 20, rx = MAPW + 20, ry = -20;		// ����λ��
int relx = -20, rely = MAPH + 20, rerx = MAPW + 20, rery = -20;		// ����λ��
float asp = 1;						// ��������
float Time = 0;						// ʱ��

int main()
{
	initgraph(WIDTH, HEIGHT);
	start();
	setall();				// ��Ϸ��ʼ��

	BeginBatchDraw();
	while (true)
	{
		move(&mover);		// ����ƶ�
		AI();
		Food();
		draw();				// ��ͼ
		FlushBatchDraw();	// ��ʾ����Ļ�������
		delay(20);			// �����ӳ�
	}
}

void move(BALL* ball)
{
	if (ball->r <= 0)	ball->life = false;

	if (ball->life == false)			// �ж���Ϸ�Ƿ����
	{
		HWND hwnd = GetHWnd();
		MessageBox(hwnd, _T("�㱻����"), _T("��Ϸ����"), MB_OK | MB_ICONEXCLAMATION);	// ����
		closegraph();
		exit(0);
	}

	if (eaten + ai_eaten == AINUM)	// �Ƿ�Ե����� AI
	{
		HWND hwnd = GetHWnd();
		MessageBox(hwnd, _T("��ϲ����"), _T("��Ϸ����"), MB_OK | MB_ICONEXCLAMATION);	// ����
		closegraph();
		exit(0);
	}

	if (ball->x > (MAPW - ball->r) || ball->x - ball->r < 0 || ball->y - ball->r < 0 || ball->y >(MAPH - ball->r))
		ball->r -= 0.1f;

	for (int i = 0; i < AINUM; i++)	// ��ҳ� AI �ж�
	{
		if (ball->r >= ai[i].r)
		{
			if (ai[i].life == 0) continue;

			if (DISTANCE((float)ball->x, (float)ball->y, (float)ai[i].x, (float)ai[i].y) < (4 / 5.0 * (ball->r + ai[i].r)))
			{
				ai[i].life = 0;		// �Ե�
				ball->r += (ai[i].r * ai[i].r / 2) / ball->r;  // �������: pai * ball->r*ball->r += pai*ai[i].r*ai[i].r;   ��r*r=��r*r+��ai[i].r*ai[i].r
				eaten++;
			}
		}
	}

	for (int n = 0; n < FNUM; n++)			// ��ҳ�ʳ��
	{
		if (food[n].eat == 0) continue;

		if (DISTANCE((float)ball->x, (float)ball->y, (float)food[n].x, (float)food[n].y) < ball->r)
		{
			ball->r += 4 / ball->r;			// �������
			food[n].eat = 0;				// ʳ�ﱻ��
		}
	}

	static int mx = 0, my = 0;			// ��¼ƫ����
	if (GetAsyncKeyState(65) & 0x8000)	{ ball->x -= 2;	mx += 2; }	//���
	if (GetAsyncKeyState(87) & 0x8000)	{ ball->y -= 2;	my += 2; }	//����
	if (GetAsyncKeyState(83) & 0x8000)	{ ball->y += 2;	my -= 2; }	//����
	if (GetAsyncKeyState(68) & 0x8000)	{ ball->x += 2;	mx -= 2; }	//�ұ�
	setorigin(mx, my);					// ��������
}

void AI()
{
	for (int i = 0; i < AINUM; i++)
	{
		if (ai[i].r > mover.r)			// AI �����
		{
			if (DISTANCE((float)mover.x, (float)mover.y, (float)ai[i].x, (float)ai[i].y) < 2 / 3.0 * ai[i].r + mover.r)
			{
				ai[i].r += (mover.r * mover.r) / ai[i].r;
				mover.life = 0;
				mover.r = 0;
			}
		}

		for (int j = 0; j < AINUM; j++)	// AI �� AI
		{
			if (ai[i].r > ai[j].r)
			{
				if (ai[j].life == 0) continue;

				if (DISTANCE((float)ai[i].x, (float)ai[i].y, (float)ai[j].x, (float)ai[j].y) < 4 / 5.0 * ai[i].r + ai[j].r)
				{
					ai[i].r += (ai[j].r * ai[j].r) / ai[i].r;		// �������
					ai[j].life = 0;
					ai[j].r = 0;
					ai_eaten++;
				}
			}
		}

		double min_DISTANCE = 100000;
		int min = -1;
		for (int k = 0; k < AINUM; k++)		// AI ���� AI
		{
			if (ai[i].r > ai[k].r && ai[k].life == 1)
			{
				if (DISTANCE((float)ai[i].x, (float)ai[k].x, (float)ai[i].y, (float)ai[k].y) < min_DISTANCE)
				{
					min_DISTANCE = DISTANCE((float)ai[i].x, (float)ai[k].x, (float)ai[i].y, (float)ai[k].y);
					min = k;
				}
			}
		}

		if ((min != -1) && (rand() % 2 == 1))
		{
			if (rand() % 2)
			{
				if (ai[i].x < ai[min].x) ai[i].x++;
				else ai[i].x--;
			}
			else
			{
				if (ai[i].y < ai[min].y) ai[i].y++;
				else ai[i].y--;
			}
		}

		for (int n = 0; n < FNUM; n++)		// AI ��ʳ��
		{
			if (food[n].eat == 0) continue;

			if (DISTANCE((float)ai[i].x, (float)ai[i].y, (float)food[n].x, (float)food[n].y) < ai[i].r)
			{
				ai[i].r += 4 / ai[i].r;
				food[n].eat = 0;
			}
		}
	}
}

void Food()
{
	for (int i = 0; i < FNUM; i++)			// ʳ����������
	{
		if (food[i].eat == 0)
		{
			food[i].eat = 1;
			food[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
			food[i].x = rand() % MAPW;
			food[i].y = rand() % MAPH;
			food[i].type = rand() % 10 + 1;
		}
	}
}

void draw()
{
	clearcliprgn();
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 20);	// �ıʵ���ɫ��״̬
	setlinecolor(RGB(0, 100, 0));
	line(relx, rely, relx, rery);	// ����
	line(relx, rely, rerx, rely);	// �Ϻ�
	line(relx, rery, rerx, rery);	// �º�
	line(rerx, rery, rerx, rely);	// ����
	setfillcolor(GREEN);

	if (mover.x - 0.5 * WIDTH / asp < relx)		floodfill(relx - 11, mover.y, RGB(0, 100, 0));
	if (mover.x + 0.5 * WIDTH / asp > rerx)		floodfill(rerx + 11, mover.y, RGB(0, 100, 0));
	if (mover.y - 0.5 * HEIGHT / asp < rery)		floodfill(mover.x, rery - 11, RGB(0, 100, 0));
	if (mover.y + 0.5 * HEIGHT / asp > rely)		floodfill(mover.x, rely + 11, RGB(0, 100, 0));

	setlinecolor(WHITE);			// �ı���ɫ   ״̬
	setlinestyle(PS_NULL);

	for (int i = 0; i < FNUM; i++)	// ����ʳ��
	{
		if (food[i].eat == 0) continue;
		setfillcolor(food[i].color);
		switch (food[i].type)		// ��״
		{
		case 1:		solidellipse(food[i].x, food[i].y, food[i].x + 2, food[i].y + 4);				break;
		case 2:		solidellipse(food[i].x, food[i].y, food[i].x + 4, food[i].y + 2);				break;
		case 3:		solidrectangle(food[i].x, food[i].y, food[i].x + 4, food[i].y + 2);				break;
		case 4:		solidrectangle(food[i].x, food[i].y, food[i].x + 2, food[i].y + 4);				break;
		case 5:		solidroundrect(food[i].x, food[i].y, food[i].x + 2, food[i].y + 4, 2, 2);		break;
		case 6:		solidroundrect(food[i].x, food[i].y, food[i].x + 4, food[i].y + 2, 2, 2);		break;
		case 7:		solidroundrect(food[i].x, food[i].y, food[i].x + 4, food[i].y + 2, 4, 2);		break;
		case 8:		solidroundrect(food[i].x, food[i].y, food[i].x + 4, food[i].y + 2, 2, 4);		break;
		case 9:		solidroundrect(food[i].x, food[i].y, food[i].x + 4, food[i].y + 2, 1, 1);		break;
		case 10:	fillcircle(food[i].x, food[i].y, 4);										break;
		}
	}

	for (int i = 0; i < AINUM; i++)	// �� AI
	{
		if (ai[i].life == 0) continue;
		setfillcolor(ai[i].color);
		fillcircle(ai[i].x, ai[i].y, int(ai[i].r + 0.5));
	}

	setfillcolor(mover.color);		// �����
	fillcircle(mover.x, mover.y, int(mover.r + 0.5));

	IMAGE map(150, 100);			// С��ͼ
	SetWorkingImage(&map);
	setbkcolor(RGB(120, 165, 209));	// ǳ��ɫ����
	cleardevice();

	for (int i = 0; i < AINUM; i++)	// �� AI
	{
		if (ai[i].life == 0) continue;
		setfillcolor(ai[i].color);
		fillcircle(ai[i].x * 150 / WIDTH / 4, ai[i].y * 100 / HEIGHT / 4, int(ai[i].r / 28 + 0.5));
	}

	setfillcolor(mover.color);		// �����
	fillcircle(mover.x * 150 / WIDTH / 4, mover.y * 100 / HEIGHT / 4, int(mover.r / 28 + 0.5));
	setlinecolor(RGB(0, 100, 0));

	if (lx != rx && ly != rx)
	{
		line(lx * 150 / WIDTH, ly * 100 / HEIGHT, lx * 150 / WIDTH, ry * 100 / HEIGHT);	// ����
		line(lx * 150 / WIDTH, ly * 100 / HEIGHT, rx * 150 / WIDTH, ly * 100 / HEIGHT);	// �Ϻ�
		line(lx * 150 / WIDTH, ry * 100 / HEIGHT, rx * 150 / WIDTH, ry * 100 / HEIGHT);	// �º�
		line(rx * 150 / WIDTH, ry * 100 / HEIGHT, rx * 150 / WIDTH, ly * 100 / HEIGHT);	// ����
	}

	setfillcolor(GREEN);
	floodfill(lx - 11, ly - 11, RGB(0, 100, 0));

	SetWorkingImage();			// �ָ���ͼ����
	putimage(mover.x + int(0.5 * WIDTH) - 150, mover.y - int(0.5 * HEIGHT), 150, 100, &map, 0, 0);						// ����С��ͼ
	setlinecolor(LIGHTBLUE);	// �ı���ɫ   ״̬
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 4);
	line(mover.x + int(0.5 * WIDTH) - 151, mover.y - int(0.5 * HEIGHT), mover.x + int(0.5 * WIDTH) - 151, mover.y - int(0.5 * HEIGHT) + 99);	// ��ͼ�߿���
	line(mover.x + int(0.5 * WIDTH) - 151, mover.y - int(0.5 * HEIGHT) + 99, mover.x + int(0.5 * WIDTH), mover.y - int(0.5 * HEIGHT) + 99);	// ��ͼ�߿���

	setlinestyle(PS_NULL);		// �ָ���
	TCHAR str[32];
	swprintf_s(str, _T("����:%.1f  ��ɱ:%d"), mover.r, eaten);
	settextcolor(BLUE);			// ������
	outtextxy(mover.x - int(0.5 * WIDTH), mover.y - int(0.5 * HEIGHT), str);
	settextcolor(BLUE);			// ������
	outtextxy(mover.x - 36, mover.y - 8, _T("����:����"));
}

void setall()
{
	srand((unsigned)time(NULL));		// �����
	mover.color = RGB(rand() % 256, rand() % 256, rand() % 256);	// �����ɫ
	mover.life = 1;					// ͳͳ����ֵ
	mover.x = int(WIDTH * 0.5);
	mover.y = int(HEIGHT * 0.5);
	mover.r = 20;

	for (int i = 0; i < AINUM; i++)		// AI ��
	{
		ai[i].life = 1;
		ai[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
		ai[i].r = float(rand() % 10 + 10);
		ai[i].x = rand() % (MAPW - int(ai[i].r + 0.5)) + int(ai[i].r + 0.5);
		ai[i].y = rand() % (MAPH - int(ai[i].r + 0.5)) + int(ai[i].r + 0.5);
	}

	for (int i = 0; i < FNUM; i++)		// ʳ���
	{
		food[i].eat = 1;
		food[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
		food[i].x = rand() % MAPW;
		food[i].y = rand() % MAPH;
		food[i].type = rand() % 10 + 1;
	}

	pBuffer = GetImageBuffer(NULL);	// ��ȡ��ʾ������ָ��
	setbkcolor(WHITE);				// ��ɫ����
	cleardevice();					// ��ʼ������
	settextcolor(LIGHTRED);			// ������
	setbkmode(TRANSPARENT);
	settextstyle(16, 0, _T("����"));
}

void delay(DWORD ms)				// ������ʱ
{
	static DWORD oldtime = GetTickCount();

	while (GetTickCount() - oldtime < ms)
		Sleep(1);

	oldtime = GetTickCount();
}

void start()
{
	setbkcolor(WHITE);		// ��ɫ����
	cleardevice();			// ��ʼ������
	settextcolor(RED);		// ������
	setbkmode(TRANSPARENT);
	settextstyle(128, 0, _T("����"));
	outtextxy(320, 40, _T("̰����"));
	settextstyle(32, 0, _T("����"));
	outtextxy(740, 135, _T("Ver 1.6"));
	settextcolor(BLUE);		// ������
	outtextxy(304, 240, _T("W���ơ�S���ơ�A���ơ�D����"));
	outtextxy(112, 340, _T("��ܴ��򡡡���׷��С�򡡡���̰��ʳ�������ǿʵ��"));
	settextcolor(BLACK);	//������
	settextstyle(32, 0, _T("����"));
	outtextxy(384, 500, _T("���������ʼ��Ϸ"));
	settextstyle(20, 0, _T("����"));
	outtextxy(810, 10, _T("���� QQ: 2190038793"));
	_getch();
}