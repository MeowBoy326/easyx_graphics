////////////////////////////////////////////
// 程序名称：万花尺（又名万花规）模拟程序
// 编译环境：Visual C++ 6.0，EasyX 2011惊蛰版
// 程序编写：yangw80 <yw80@qq.com>
// 最后更新：2011-2-26
//
#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#define PI 3.1415926536

void main()
{
	int R;		// 外部静圆半径
	int r;		// 内部动圆半径
	int dr;		// 内部动圆上的作图点到圆心的距离

begin:
	// 获取用户输入
	printf("请输入外部静圆半径（小于 240）：");
	scanf("%d", &R);
	printf("请输入内部动圆半径（小于静圆半径）：");
	scanf("%d", &r);
	printf("请输入内部动圆上的作图点到圆心的距离（小于动圆半径）：");
	scanf("%d", &dr);
	system("cls");

	// 求执行次数（最小公倍数/静圆半径）
	int m = R, n = r;
	int tmp;
	while (n != 0)
	{
		tmp = m % n;
		m = n;
		n = tmp;
	}
	double maxdegree = r / m * 2 * PI;

	// 初始化
	initgraph(640, 480);	// 创建绘图窗口
	setorigin(320, 240);	// 设定圆心坐标

	// 绘图
	int x, y;
	for (double degree = 0; degree < maxdegree; degree += 0.01)
	{
		x = (int)(dr * cos(degree*(double(R) / r - 1)) + (R - r) * cos(degree));
		y = (int)(dr * sin(degree*(double(R) / r - 1)) - (R - r) * sin(degree));
		putpixel(x, y, GREEN);
	}
	outtextxy(-320, 220, _T("绘制完毕，按 ESC 退出，按其他键重新开始"));

	// 重新开始，或退出程序
	char c = getch();
	closegraph();
	if (c != 27) goto begin;
}