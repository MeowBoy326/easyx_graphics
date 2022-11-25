///////////////////////////////////////////////////
// 程序名称：贪婪球 1.6
// 编译环境：Microsoft Visual studio 2017，EasyX_20200727
// 作　　者：奶酪
// 邮　　箱：2190038793@qq.com
// 发布日期：2019-2-10
// 最后修改：2019-2-15
//
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <wchar.h>

#define WIDTH		1024			// 屏幕宽
#define HEIGHT		576				// 屏幕高
#define MAPW		(WIDTH * 4)		// 地图宽
#define MAPH		(HEIGHT * 4)	// 地图高
#define AINUM       100				// AI 数量
#define FNUM        2000			// FOOD 数量
#define PTIME       180				// 毒圈刷新时间
#define DISTANCE(x1, y1, x2, y2)	(sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)))

struct FOOD
{
	bool		eat;
	COLORREF	color;		// 颜色
	int			x, y;		// 坐标
	char		type;
};

struct BALL					// 定义小球结构
{
	bool		life;		// 生命
	COLORREF	color;		// 颜色
	int			x, y;		// 坐标
	float		r;			// 半径
};

FOOD food[FNUM];								// 食物
BALL mover = { 1, RGB(0, 0, 0), 0, 0, 0 };	// 玩家
BALL ai[AINUM] = { 1, RGB(0, 0, 0), 0, 0, 0 };	// 机器大军

void move(BALL* ball);				// 玩家移动
void draw();						// 绘图
void start();						// 游戏开始
void setall();						// 初始化数据
void AI();							// AI
void Food();						// 食物
void delay(DWORD ms);				// 绝对延时

DWORD* pBuffer;						// 显示缓冲区指针
int eaten = 0;						// 吃 AI 的数量
int ai_eaten = 0;					// AI 吃 AI的数量
int lx = -20, ly = MAPH + 20, rx = MAPW + 20, ry = -20;		// 毒的位置
int relx = -20, rely = MAPH + 20, rerx = MAPW + 20, rery = -20;		// 毒的位置
float asp = 1;						// 缩放因子
float Time = 0;						// 时间

int main()
{
	initgraph(WIDTH, HEIGHT);
	start();
	setall();				// 游戏初始化

	BeginBatchDraw();
	while (true)
	{
		move(&mover);		// 玩家移动
		AI();
		Food();
		draw();				// 绘图
		FlushBatchDraw();	// 显示缓存的绘制内容
		delay(20);			// 绝对延迟
	}
}

void move(BALL* ball)
{
	if (ball->r <= 0)	ball->life = false;

	if (ball->life == false)			// 判定游戏是否接束
	{
		HWND hwnd = GetHWnd();
		MessageBox(hwnd, _T("你被吃了"), _T("游戏结束"), MB_OK | MB_ICONEXCLAMATION);	// 结束
		closegraph();
		exit(0);
	}

	if (eaten + ai_eaten == AINUM)	// 是否吃掉所以 AI
	{
		HWND hwnd = GetHWnd();
		MessageBox(hwnd, _T("恭喜过关"), _T("游戏结束"), MB_OK | MB_ICONEXCLAMATION);	// 结束
		closegraph();
		exit(0);
	}

	if (ball->x > (MAPW - ball->r) || ball->x - ball->r < 0 || ball->y - ball->r < 0 || ball->y >(MAPH - ball->r))
		ball->r -= 0.1f;

	for (int i = 0; i < AINUM; i++)	// 玩家吃 AI 判定
	{
		if (ball->r >= ai[i].r)
		{
			if (ai[i].life == 0) continue;

			if (DISTANCE((float)ball->x, (float)ball->y, (float)ai[i].x, (float)ai[i].y) < (4 / 5.0 * (ball->r + ai[i].r)))
			{
				ai[i].life = 0;		// 吃掉
				ball->r += (ai[i].r * ai[i].r / 2) / ball->r;  // 推理过程: pai * ball->r*ball->r += pai*ai[i].r*ai[i].r;   πr*r=πr*r+πai[i].r*ai[i].r
				eaten++;
			}
		}
	}

	for (int n = 0; n < FNUM; n++)			// 玩家吃食物
	{
		if (food[n].eat == 0) continue;

		if (DISTANCE((float)ball->x, (float)ball->y, (float)food[n].x, (float)food[n].y) < ball->r)
		{
			ball->r += 4 / ball->r;			// 增加面积
			food[n].eat = 0;				// 食物被吃
		}
	}

	static int mx = 0, my = 0;			// 记录偏移量
	if (GetAsyncKeyState(65) & 0x8000)	{ ball->x -= 2;	mx += 2; }	//左边
	if (GetAsyncKeyState(87) & 0x8000)	{ ball->y -= 2;	my += 2; }	//上面
	if (GetAsyncKeyState(83) & 0x8000)	{ ball->y += 2;	my -= 2; }	//下面
	if (GetAsyncKeyState(68) & 0x8000)	{ ball->x += 2;	mx -= 2; }	//右边
	setorigin(mx, my);					// 坐标修正
}

void AI()
{
	for (int i = 0; i < AINUM; i++)
	{
		if (ai[i].r > mover.r)			// AI 吃玩家
		{
			if (DISTANCE((float)mover.x, (float)mover.y, (float)ai[i].x, (float)ai[i].y) < 2 / 3.0 * ai[i].r + mover.r)
			{
				ai[i].r += (mover.r * mover.r) / ai[i].r;
				mover.life = 0;
				mover.r = 0;
			}
		}

		for (int j = 0; j < AINUM; j++)	// AI 吃 AI
		{
			if (ai[i].r > ai[j].r)
			{
				if (ai[j].life == 0) continue;

				if (DISTANCE((float)ai[i].x, (float)ai[i].y, (float)ai[j].x, (float)ai[j].y) < 4 / 5.0 * ai[i].r + ai[j].r)
				{
					ai[i].r += (ai[j].r * ai[j].r) / ai[i].r;		// 面积增加
					ai[j].life = 0;
					ai[j].r = 0;
					ai_eaten++;
				}
			}
		}

		double min_DISTANCE = 100000;
		int min = -1;
		for (int k = 0; k < AINUM; k++)		// AI 靠近 AI
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

		for (int n = 0; n < FNUM; n++)		// AI 吃食物
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
	for (int i = 0; i < FNUM; i++)			// 食物重新生成
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
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 20);	// 改笔的颜色、状态
	setlinecolor(RGB(0, 100, 0));
	line(relx, rely, relx, rery);	// 左竖
	line(relx, rely, rerx, rely);	// 上横
	line(relx, rery, rerx, rery);	// 下横
	line(rerx, rery, rerx, rely);	// 右竖
	setfillcolor(GREEN);

	if (mover.x - 0.5 * WIDTH / asp < relx)		floodfill(relx - 11, mover.y, RGB(0, 100, 0));
	if (mover.x + 0.5 * WIDTH / asp > rerx)		floodfill(rerx + 11, mover.y, RGB(0, 100, 0));
	if (mover.y - 0.5 * HEIGHT / asp < rery)		floodfill(mover.x, rery - 11, RGB(0, 100, 0));
	if (mover.y + 0.5 * HEIGHT / asp > rely)		floodfill(mover.x, rely + 11, RGB(0, 100, 0));

	setlinecolor(WHITE);			// 改笔颜色   状态
	setlinestyle(PS_NULL);

	for (int i = 0; i < FNUM; i++)	// 画出食物
	{
		if (food[i].eat == 0) continue;
		setfillcolor(food[i].color);
		switch (food[i].type)		// 形状
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

	for (int i = 0; i < AINUM; i++)	// 画 AI
	{
		if (ai[i].life == 0) continue;
		setfillcolor(ai[i].color);
		fillcircle(ai[i].x, ai[i].y, int(ai[i].r + 0.5));
	}

	setfillcolor(mover.color);		// 画玩家
	fillcircle(mover.x, mover.y, int(mover.r + 0.5));

	IMAGE map(150, 100);			// 小地图
	SetWorkingImage(&map);
	setbkcolor(RGB(120, 165, 209));	// 浅灰色背景
	cleardevice();

	for (int i = 0; i < AINUM; i++)	// 画 AI
	{
		if (ai[i].life == 0) continue;
		setfillcolor(ai[i].color);
		fillcircle(ai[i].x * 150 / WIDTH / 4, ai[i].y * 100 / HEIGHT / 4, int(ai[i].r / 28 + 0.5));
	}

	setfillcolor(mover.color);		// 画玩家
	fillcircle(mover.x * 150 / WIDTH / 4, mover.y * 100 / HEIGHT / 4, int(mover.r / 28 + 0.5));
	setlinecolor(RGB(0, 100, 0));

	if (lx != rx && ly != rx)
	{
		line(lx * 150 / WIDTH, ly * 100 / HEIGHT, lx * 150 / WIDTH, ry * 100 / HEIGHT);	// 左竖
		line(lx * 150 / WIDTH, ly * 100 / HEIGHT, rx * 150 / WIDTH, ly * 100 / HEIGHT);	// 上横
		line(lx * 150 / WIDTH, ry * 100 / HEIGHT, rx * 150 / WIDTH, ry * 100 / HEIGHT);	// 下横
		line(rx * 150 / WIDTH, ry * 100 / HEIGHT, rx * 150 / WIDTH, ly * 100 / HEIGHT);	// 右竖
	}

	setfillcolor(GREEN);
	floodfill(lx - 11, ly - 11, RGB(0, 100, 0));

	SetWorkingImage();			// 恢复绘图背景
	putimage(mover.x + int(0.5 * WIDTH) - 150, mover.y - int(0.5 * HEIGHT), 150, 100, &map, 0, 0);						// 画出小地图
	setlinecolor(LIGHTBLUE);	// 改笔颜色   状态
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 4);
	line(mover.x + int(0.5 * WIDTH) - 151, mover.y - int(0.5 * HEIGHT), mover.x + int(0.5 * WIDTH) - 151, mover.y - int(0.5 * HEIGHT) + 99);	// 地图边框线
	line(mover.x + int(0.5 * WIDTH) - 151, mover.y - int(0.5 * HEIGHT) + 99, mover.x + int(0.5 * WIDTH), mover.y - int(0.5 * HEIGHT) + 99);	// 地图边框线

	setlinestyle(PS_NULL);		// 恢复笔
	TCHAR str[32];
	swprintf_s(str, _T("质量:%.1f  击杀:%d"), mover.r, eaten);
	settextcolor(BLUE);			// 改字体
	outtextxy(mover.x - int(0.5 * WIDTH), mover.y - int(0.5 * HEIGHT), str);
	settextcolor(BLUE);			// 改字体
	outtextxy(mover.x - 36, mover.y - 8, _T("作者:奶酪"));
}

void setall()
{
	srand((unsigned)time(NULL));		// 随机数
	mover.color = RGB(rand() % 256, rand() % 256, rand() % 256);	// 随机颜色
	mover.life = 1;					// 统统赋初值
	mover.x = int(WIDTH * 0.5);
	mover.y = int(HEIGHT * 0.5);
	mover.r = 20;

	for (int i = 0; i < AINUM; i++)		// AI 的
	{
		ai[i].life = 1;
		ai[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
		ai[i].r = float(rand() % 10 + 10);
		ai[i].x = rand() % (MAPW - int(ai[i].r + 0.5)) + int(ai[i].r + 0.5);
		ai[i].y = rand() % (MAPH - int(ai[i].r + 0.5)) + int(ai[i].r + 0.5);
	}

	for (int i = 0; i < FNUM; i++)		// 食物的
	{
		food[i].eat = 1;
		food[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
		food[i].x = rand() % MAPW;
		food[i].y = rand() % MAPH;
		food[i].type = rand() % 10 + 1;
	}

	pBuffer = GetImageBuffer(NULL);	// 获取显示缓冲区指针
	setbkcolor(WHITE);				// 白色背景
	cleardevice();					// 初始化背景
	settextcolor(LIGHTRED);			// 改字体
	setbkmode(TRANSPARENT);
	settextstyle(16, 0, _T("宋体"));
}

void delay(DWORD ms)				// 绝对延时
{
	static DWORD oldtime = GetTickCount();

	while (GetTickCount() - oldtime < ms)
		Sleep(1);

	oldtime = GetTickCount();
}

void start()
{
	setbkcolor(WHITE);		// 白色背景
	cleardevice();			// 初始化背景
	settextcolor(RED);		// 改字体
	setbkmode(TRANSPARENT);
	settextstyle(128, 0, _T("宋体"));
	outtextxy(320, 40, _T("贪婪球"));
	settextstyle(32, 0, _T("宋体"));
	outtextxy(740, 135, _T("Ver 1.6"));
	settextcolor(BLUE);		// 改字体
	outtextxy(304, 240, _T("W上移　S下移　A左移　D右移"));
	outtextxy(112, 340, _T("躲避大球　　　追补小球　　　贪吃食物　　　增强实力"));
	settextcolor(BLACK);	//改字体
	settextstyle(32, 0, _T("宋体"));
	outtextxy(384, 500, _T("按任意键开始游戏"));
	settextstyle(20, 0, _T("宋体"));
	outtextxy(810, 10, _T("作者 QQ: 2190038793"));
	_getch();
}