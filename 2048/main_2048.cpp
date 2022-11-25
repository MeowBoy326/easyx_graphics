// 程序名称：2048Game
// 编译环境：Visual C++ 2013, EasyX_20200315(beta)
// 作　　者：李大恕 <2928947343@qq.com> <QQ:2928947343>
// 最后修改：2021-1-25

#include <graphics.h>
#include <cstring>
#include <cstdio>
#include <ctime>
#include <conio.h>
using namespace std;

const COLORREF BGC = RGB(250, 248, 239);	// 定义背景色常量
int score, best, a[5][5], b[5][5];			// score 为本局分数，best 为当前最佳纪录，a 数组为棋盘，b 数组为 a 的备份
bool mov[5][5];								// 棋盘上的点是否已被移动过（避免重复移动）

// 程序初始化
void init()
{
	setbkcolor(BGC);
	setbkmode(TRANSPARENT);
	score = 0;
	memset(a, 0, sizeof(a));
	int x1 = rand() % 4 + 1, y1 = rand() % 4 + 1, x2 = rand() % 4 + 1, y2 = rand() % 4 + 1;	// 随机生成两个初始点
	a[x1][y1] = a[x2][y2] = 2;				// 初始点初始化为 2
}


// 绘制游戏界面
void drawmap()
{
	// 开始批量绘图
	BeginBatchDraw();

	// 绘制界面主体
	cleardevice();
	settextcolor(RGB(119, 110, 101));
	settextstyle(50, 0, L"微软雅黑");
	outtextxy(10, 10, L"2048");
	settextstyle(20, 0, L"微软雅黑", 0, 0, 550, false, false, false);
	outtextxy(10, 65, L"Join the numbers and get to the 2048 tile!");

	setfillcolor(RGB(187, 173, 160));

	// 绘制当前分数
	solidroundrect(200, 15, 290, 60, 5, 5);
	settextcolor(RGB(230, 220, 210));
	settextstyle(15, 0, L"微软雅黑", 0, 0, 600, false, false, false);
	outtextxy(230, 20, L"SCORE");
	wchar_t sc[10] = L"";
	swprintf_s(sc, L"%d", score);
	settextcolor(WHITE);
	settextstyle(25, 0, L"微软雅黑", 0, 0, 600, false, false, false);
	RECT r = { 200, 30, 290, 60 };
	drawtext(sc, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	// 绘制最佳纪录
	solidroundrect(295, 15, 385, 60, 5, 5);
	settextcolor(RGB(230, 220, 210));
	settextstyle(15, 0, L"微软雅黑", 0, 0, 600, false, false, false);
	outtextxy(330, 20, L"BEST");
	wchar_t bs[10] = L"";
	swprintf_s(bs, L"%d", best);
	settextcolor(WHITE);
	settextstyle(25, 0, L"微软雅黑", 0, 0, 600, false, false, false);
	r = { 295, 30, 385, 60 };
	drawtext(bs, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	// 绘制数字棋盘
	solidroundrect(10, 90, 390, 470, 5, 5);
	settextstyle(23, 0, L"微软雅黑");
	settextcolor(WHITE);
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			if (a[i][j])			// 如果该位置没有数字，则不绘制
			{
				// 用类似哈希的方法，为每个数字计算出对应的颜色
				setfillcolor(RGB((unsigned int)(BGC - 3 * (a[i][j] ^ 29)) % 256, (unsigned int)(BGC - 11 * (a[i][j] ^ 23)) % 256, (unsigned int)(BGC + 7 * (a[i][j] ^ 37)) % 256));
				solidroundrect(94 * j - 80, 94 * i, 94 * j + 10, 94 * i + 90, 5, 5);
				wchar_t num[10] = L"";
				swprintf_s(num, L"%d", a[i][j]);
				r = { 94 * j - 80, 94 * i, 94 * j + 10, 94 * i + 90 };
				drawtext(num, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}

	// 结束批量绘图
	EndBatchDraw();
}

// 玩家操作
void move()
{
	memcpy(b, a, sizeof(a));			// 将 a 备份至 b
	memset(mov, false, sizeof(mov));	// 初始化 mov 为 false（所有点均未移动）
	// 获取用户操作
	char userkey = _getch();
	if (userkey == -32)
		userkey = -_getch();
	// 移动棋盘（移动 a 数组）
	switch (userkey)
	{
		// 向上
	case 'w':
	case 'W':
	case -72:
		for (int j = 1; j <= 4; j++)
			for (int i = 2; i <= 4; i++)
			{
				if (!a[i][j])continue;
				int k = i;
				while (!a[k - 1][j] && k >= 2)
				{
					a[k - 1][j] = a[k][j];
					a[k][j] = 0;
					k--;
				}
				if (a[k][j] == a[k - 1][j] && !mov[k - 1][j])
				{
					a[k - 1][j] = 2 * a[k][j];
					a[k][j] = 0;
					mov[k - 1][j] = true;
					score += a[k - 1][j];
				}
			}
		break;
		// 向下
	case 's':
	case 'S':
	case -80:
		for (int j = 1; j <= 4; j++)
			for (int i = 3; i >= 1; i--)
			{
				if (!a[i][j])continue;
				int k = i;
				while (!a[k + 1][j] && k <= 3)
				{
					a[k + 1][j] = a[k][j];
					a[k][j] = 0;
					k++;
				}
				if (a[k][j] == a[k + 1][j] && !mov[k + 1][j])
				{
					a[k + 1][j] = 2 * a[k][j];
					a[k][j] = 0;
					mov[k + 1][j] = true;
					score += a[k + 1][j];
				}
			}
		break;
		// 向左
	case 'a':
	case 'A':
	case -75:
		for (int i = 1; i <= 4; i++)
			for (int j = 2; j <= 4; j++)
			{
				if (!a[i][j])continue;
				int k = j;
				while (!a[i][k - 1] && k >= 2)
				{
					a[i][k - 1] = a[i][k];
					a[i][k] = 0;
					k--;
				}
				if (a[i][k] == a[i][k - 1] && !mov[i][k - 1])
				{
					a[i][k - 1] = 2 * a[i][k];
					a[i][k] = 0;
					mov[i][k - 1] = true;
					score += a[i][k - 1];
				}
			}
		break;
		// 向右
	case 'd':
	case 'D':
	case -77:
		for (int i = 1; i <= 4; i++)
			for (int j = 3; j >= 1; j--)
			{
				if (!a[i][j])continue;
				int k = j;
				while (!a[i][k + 1] && k <= 3)
				{
					a[i][k + 1] = a[i][k];
					a[i][k] = 0;
					k++;
				}
				if (a[i][k] == a[i][k + 1] && !mov[i][k + 1])
				{
					a[i][k + 1] = 2 * a[i][k];
					a[i][k] = 0;
					mov[i][k + 1] = true;
					score += a[i][k + 1];
				}
			}
		break;
	}
	bool change = false;				// 判断经过移动，棋盘是否改变
	// 比较当前棋盘与移动前（b 数组）棋盘
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			if (a[i][j] != b[i][j])
			{
				change = true;
				break;
			}
	if (!change)return;					// 如果棋盘没有改变，退出
	// 生成一个新数字（且不与已有数字重合）
	int x, y;
	do
	{
		x = rand() % 4 + 1;
		y = rand() % 4 + 1;
	} while (a[x][y]);
	// 有 1/6 的几率生成数字为 4，其余情况生成数字为 2
	int n = rand() % 6;
	if (n == 5)a[x][y] = 4;
	else a[x][y] = 2;
	// 更新最佳纪录
	best = max(best, score);
}

// 判断游戏结束
bool gameover()
{
	// 对于任意一个位置，该位置为空 或 四周有位置上的数字与该位置上数字相等，说明可继续移动（游戏可继续）
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			if (!a[i][j] || a[i][j] == a[i + 1][j] || a[i][j] == a[i - 1][j] || a[i][j] == a[i][j + 1] || a[i][j] == a[i][j - 1])return false;
	// 否则游戏结束
	return true;
}

// 判断胜利
bool win()
{
	// 有任意一个位置达到 2048，则胜利
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			if (a[i][j] == 2048)return true;
	return false;
}

int main()
{
	bool ctn = true;					// 该值代表是否重开新局
	initgraph(400, 480);				// 初始化图形界面
	srand((unsigned)time(NULL));
	while (ctn)
	{
		init();							// 新的一局，程序初始化
		drawmap();						// 绘制界面
		int endmode = 0;				// 结束方式，1 代表胜利，2 代表失败
		while (1)
		{
			move();						// 玩家操作
			drawmap();					// 绘制界面
			if (win())					// 胜利
			{
				endmode = 1;
				break;
			}
			if (gameover())				// 失败
			{
				endmode = 2;
				break;
			}
		}
		int t;							// 获取用户选择的按钮
		if (endmode == 1)				// 胜利
			t = MessageBox(0, L"You win!\n再来一局？", L"继续", MB_OKCANCEL);
		if (endmode == 2)				// 失败
			t = MessageBox(0, L"Game over!\n再来一局？", L"继续", MB_OKCANCEL);
		if (t == IDCANCEL)ctn = false;	// 若用户选择 取消，则不重新开局
	}
	closegraph();						// 关闭图形界面
	return 0;
}