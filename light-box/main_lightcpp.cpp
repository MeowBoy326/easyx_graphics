/****************************************************************
*																*
*	程序名称：	《涂格子游戏》									*
*	编译环境：	VC++6.0 && && EasyX_v20120603b					*
*	作者相关：	Made In China by xiongfj <837942056@qq.com>		*
*	最后修改：	2012.09.12										*
*																*
****************************************************************/

#include <graphics.h>
#include <conio.h>

// 常量定义
#define GLENGTH 30						// 每个小格子的边长
#define MAXGRID 15						// 最大单边格子数

// 全局变量定义
int i, numgrid = 4, level = 4;			// 初始格子数与级别
int xleft, xright, yup, ydown;			// 分别代表正方形框架的左右上下四个顶点的坐标
MOUSEMSG m;

// 函数申明
bool grid[MAXGRID][MAXGRID];			// 格子状态
void Draw(int numgrid);					// 游戏框架
int SetMouseMsg();						// 总的鼠标信息
int Lbutton(int numgrid, MOUSEMSG);		// 鼠标左键信息
int Pass();								// 检查是否通关
int Cheat();							// 作弊函数，不怕不通关



// 主函数
void main()
{
	initgraph(780, 640);
	Draw(numgrid);
	int x = 0;

	while (!kbhit())					// 单击一次，函数走完一循环
	{
		if (numgrid > 15)
		{
			setfont(20, 0, "黑体");
			setcolor(LIGHTGREEN);
			setwritemode(R2_XORPEN);
			outtextxy(20, 580, "按任意键退出。");
			outtextxy(630, 610, "小熊出厂(⊙o⊙)");

			while (!kbhit())
			{
				outtextxy(x, 320, "真是千年难见天才也，这都能通关！");
				Sleep(14);
				outtextxy(x, 320, "真是千年难见天才也，这都能通关！");
				x += 2;
				if (x>780)
					x = 0;
			}
			break;
		}

		// 如果 numgrid++ 进入下一关
		if (numgrid > level)
		{
			Draw(numgrid);
			level = numgrid;
		}
		SetMouseMsg();
	}

	getch();
	closegraph();
}



// 画游戏基本框架
void Draw(int numgrid)
{
	cleardevice();

	xleft = 390 - numgrid * GLENGTH / 2;			// 格子最左边界的 x 坐标
	xright = 390 + numgrid * GLENGTH / 2;
	yup = 320 - numgrid * GLENGTH / 2;			// 格子最上边界的 y 坐标
	ydown = 320 + numgrid * GLENGTH / 2;

	setlinestyle(PS_SOLID, 1);
	setcolor(LIGHTGREEN);

	for (i = xleft; i <= xright; i += GLENGTH)		line(i, yup, i, ydown);		// 画竖线
	for (i = yup; i <= ydown; i += GLENGTH)		line(xleft, i, xright, i);	// 画横线

	setfont(15, 0, "楷体");
	setcolor(RGB(111, 211, 0));

	// 输出操作说明
	outtextxy(11, 10, "1、单击空格子，同时给上下中左右的空格子换色。");
	outtextxy(11, 27, "2、全部格子都上完颜色过关。");
	outtextxy(11, 44, "3、按任意键退出游戏。");
	outtextxy(11, 61, "4、右击重来，Ctrl 作弊键。");

	setlinestyle(PS_SOLID, 10);
	setcolor(LIGHTGREEN);

	// 框架边边加粗(纯修饰)
	line(xleft - 5, yup - 5, xright + 5, yup - 5);
	line(xleft - 5, ydown + 5, xright + 5, ydown + 5);
	line(xleft - 5, yup - 5, xleft - 5, ydown + 5);
	line(xright + 5, yup - 5, xright + 5, ydown + 5);

	// 每次重绘框架时标记每个格子，0 为空，1 为有色
	for (i = 0; i < numgrid; i++)
		for (int y = 0; y < numgrid; y++)
			grid[i][y] = 0;
}



// 分解鼠标按键信息
int SetMouseMsg()
{
	m = GetMouseMsg();

	switch (m.uMsg)
	{
	case WM_LBUTTONDOWN:
		if (m.mkCtrl)
			Cheat(); 				// 作弊函数
		else
			Lbutton(numgrid, m);	// 左击函数
		break;

		// 右击重绘格子
	case WM_RBUTTONDOWN:
		Draw(numgrid);
		break;

	default:
		break;
	}
	return 0;
}



// 左击函数实现
int Lbutton(int numgrid, MOUSEMSG m)
{
	for (i = 0; i < numgrid; i++)												// 判断 x 方向
	{
		if (m.x > xleft + GLENGTH * i && m.x < xleft + GLENGTH * (i + 1))		// 如果 m.x 在某格子内
		{
			for (int y = 0; y < numgrid; y++)									// 判断 y 方向，
				if (m.y > yup + GLENGTH * y && m.y < yup + GLENGTH * (y + 1))		// 如果 m.y 也在某个格子内
				{
					if (grid[i][y] == 0)											// 如果鼠标所在格子未填色
						setfillstyle(RED);
					else
						setfillstyle(0);
					bar(xleft + GLENGTH * i + 1, yup + GLENGTH * y + 1,
						xleft + GLENGTH * (i + 1) - 1, yup + GLENGTH * (y + 1) - 1);
					grid[i][y] = !grid[i][y];

					// 涂左
					if (m.x - xleft > GLENGTH)
					{
						if (grid[i - 1][y] == 0)
							setfillstyle(RED);
						else
							setfillstyle(0);
						bar(xleft + GLENGTH * (i - 1) + 1, yup + GLENGTH * y + 1,
							xleft + GLENGTH * i - 1, yup + GLENGTH * (y + 1) - 1);
						grid[i - 1][y] = !grid[i - 1][y];
					}

					// 涂右
					if (xright - m.x > GLENGTH)
					{
						if (grid[i + 1][y] == 0)
							setfillstyle(RED);
						else
							setfillstyle(0);
						bar(xleft + GLENGTH * (i + 1) + 1, yup + GLENGTH * y + 1,
							xleft + GLENGTH * (i + 2) - 1, yup + GLENGTH * (y + 1) - 1);
						grid[i + 1][y] = !grid[i + 1][y];
					}

					// 涂上
					if (m.y - yup > GLENGTH)
					{
						if (grid[i][y - 1] == 0)
							setfillstyle(RED);
						else
							setfillstyle(0);
						bar(xleft + GLENGTH * i + 1, yup + GLENGTH * (y - 1) + 1,
							xleft + GLENGTH * (i + 1) - 1, yup + GLENGTH * y - 1);
						grid[i][y - 1] = !grid[i][y - 1];
					}

					// 涂下
					if (ydown - m.y > GLENGTH)
					{
						if (grid[i][y + 1] == 0)
							setfillstyle(RED);
						else
							setfillstyle(0);
						bar(xleft + GLENGTH * i + 1, yup + GLENGTH * (y + 1) + 1,
							xleft + GLENGTH * (i + 1) - 1, yup + GLENGTH * (y + 2) - 1);
						grid[i][y + 1] = !grid[i][y + 1];
					}

					// 检查是否过关
					Pass();
				}
		}
	}
	return 0;
}



// 检测是否过关
int Pass()
{
	int a = 1;

	for (i = 0; i < numgrid; i++)			// 扫描所有格子状态
	{
		for (int y = 0; y < numgrid; y++)
			a = a * grid[i][y];
	}
	if (a == 1)								// 如果格子全部上色
	{
		numgrid++;							// 下一关格子数
		setfont(20, 0, "宋体");
		outtextxy(250, 30, "喵了个咪咪，这也行！即将进入下一关。");

		for (i = 0; i < 780; i++)
		{
			setcolor(LIGHTGREEN);
			line(i, 237, i, 243);
			Sleep(2);
		}
		return 1;
	}
	else
		return 0;
}



// 作弊函数的实现
int Cheat()
{
	// 扫描 m.x 在哪一竖格子内
	for (i = 0; i < numgrid; i++)
	{
		if (m.x > xleft + GLENGTH * i && m.x < xleft + GLENGTH * (i + 1))
		{
			// 扫描 m.y 在哪一行格子内
			for (int y = 0; y < numgrid; y++)
			{
				if (m.y > yup + GLENGTH * y && m.y < yup + GLENGTH * (y + 1))
				{
					setfillstyle(GREEN);
					bar(xleft + GLENGTH * i + 1, yup + GLENGTH * y + 1,
						xleft + GLENGTH * (i + 1) - 1, yup + GLENGTH * (y + 1) - 1);

					if (grid[i][y] == 0)					// 如果单击的格子未标记为 1
						grid[i][y] = !grid[i][y];			// 将该格子标记为 0

					// 检查是否过关
					Pass();
				}
			}
		}
	}
	return 0;
}