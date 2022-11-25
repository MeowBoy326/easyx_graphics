////////////////////////////////////////////
// 程序名称：钟表模拟程序(表针形式)
// 编译环境：Visual C++ 6.0 ~ 2019，EasyX_20210730
// 程序编写：BestAns <BestAns@qq.com>
// 最后更新：2010-10-30
//
#include <graphics.h>
#include <conio.h>
#include <math.h>

#define	PI	3.1415926536

void DrawHand(int hour, int minute, int second)
{
	double a_hour, a_min, a_sec;					// 时、分、秒针的弧度值
	int x_hour, y_hour, x_min, y_min, x_sec, y_sec;	// 时、分、秒针的末端位置

	// 计算时、分、秒针的弧度值
	a_sec = second * 2 * PI / 60;
	a_min = minute * 2 * PI / 60 + a_sec / 60;
	a_hour = hour * 2 * PI / 12 + a_min / 12;

	// 计算时、分、秒针的末端位置
	x_sec = int(120 * sin(a_sec));	y_sec = int(120 * cos(a_sec));
	x_min = int(100 * sin(a_min));	y_min = int(100 * cos(a_min));
	x_hour = int(70 * sin(a_hour));	y_hour = int(70 * cos(a_hour));

	// 画时针
	setlinestyle(PS_SOLID, 10);
	setlinecolor(WHITE);
	line(320 + x_hour, 240 - y_hour, 320 - x_hour / 7, 240 + y_hour / 7);

	// 画分针
	setlinestyle(PS_SOLID, 6);
	setlinecolor(LIGHTGRAY);
	line(320 + x_min, 240 - y_min, 320 - x_min / 5, 240 + y_min / 5);

	// 画秒针
	setlinestyle(PS_SOLID, 2);
	setlinecolor(RED);
	line(320 + x_sec, 240 - y_sec, 320 - x_sec / 3, 240 + y_sec / 3);
}

void DrawDial()
{
	// 绘制一个简单的表盘
	circle(320, 240, 2);
	circle(320, 240, 60);
	circle(320, 240, 160);
	outtextxy(296, 310, _T("BestAns"));

	// 绘制刻度
	int x, y;
	for (int i = 0; i < 60; i++)
	{
		x = 320 + int(145 * sin(PI * 2 * i / 60));
		y = 240 + int(145 * cos(PI * 2 * i / 60));

		if (i % 15 == 0)
			solidrectangle(x - 5, y - 5, x + 5, y + 5);
		else if (i % 5 == 0)
			circle(x, y, 3);
		else
			putpixel(x, y, WHITE);
	}
}

int main()
{
	initgraph(640, 480);		// 初始化 640 x 480 的绘图窗口

	DrawDial();					// 绘制表盘

	setrop2(R2_XORPEN);	// 设置 XOR 绘图模式

	// 绘制表针
	SYSTEMTIME ti;				// 定义变量保存当前时间
	while (!_kbhit())				// 按任意键退出钟表程序
	{
		GetLocalTime(&ti);		// 获取当前时间
		DrawHand(ti.wHour, ti.wMinute, ti.wSecond);	// 画表针
		Sleep(1000);			// 延时 1 秒
		DrawHand(ti.wHour, ti.wMinute, ti.wSecond);	// 擦表针（擦表针和画表针的过程是一样的）
	}

	closegraph();				// 关闭绘图窗口
	return 0;
}