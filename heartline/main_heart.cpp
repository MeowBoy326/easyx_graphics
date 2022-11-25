////////////////////////////////////////////
// 程序：心脏线
// 作者：我想做三国志
// 编译环境：Visual Studio 2019，EasyX_20211109
// 编写日期：2022-1-13

#include <graphics.h>
#include <conio.h>
#include <math.h>

#define WIDTH	640					// 窗口宽度
#define HEIGHT	480					// 窗口高度
#define PI		3.14159265			// π
#define DISPLAY 3					// 展示出来动圆与定圆的交点及心脏线当前所在点的尺寸
#define ARROW	5					// 箭头的尺寸
#define COPIES	600					// 份数，看要获得心脏线上的多少个点
#define SECONDS 5					// 跑完一圈的秒数
using namespace std;

// 画坐标抽
void drawCoordinateAxis()
{
	setlinecolor(DARKGRAY);
	line(WIDTH / 2, HEIGHT / 10, WIDTH / 2, HEIGHT / 10 * 9);
	line(WIDTH / 2, HEIGHT / 10, WIDTH / 2 + ARROW, HEIGHT / 10 + ARROW);
	line(WIDTH / 2, HEIGHT / 10, WIDTH / 2 - ARROW, HEIGHT / 10 + ARROW);

	line(WIDTH / 5, HEIGHT / 2, WIDTH / 5 * 4, HEIGHT / 2);
	line(WIDTH / 5 * 4, HEIGHT / 2, WIDTH / 5 * 4 - ARROW, HEIGHT / 2 - ARROW);
	line(WIDTH / 5 * 4, HEIGHT / 2, WIDTH / 5 * 4 - ARROW, HEIGHT / 2 + ARROW);
}

int main()
{
	initgraph(WIDTH, HEIGHT);
	BeginBatchDraw();
	setlinecolor(BLUE);

	// 画坐标轴，定圆
	double r = min(WIDTH, HEIGHT) / 9;
	circle(WIDTH / 2, HEIGHT / 2, r);
	drawCoordinateAxis();

	setrop2(R2_XORPEN);

	double lastX = WIDTH / 2.0, lastY = HEIGHT / 2 - r;					// 上一个心脏线的点的 x，y 值，初始值为 y 轴正方向上距原点 a 个单位长度的点
	for (double a = 0; !_kbhit(); a += PI / COPIES * 2)					// a 为当前弧度
	{
		double x = cos(3.0 / 2.0 * PI + a) * 2 * r + WIDTH / 2;			// 动圆这一个循环的圆心的 x 值
		double y = sin(3.0 / 2.0 * PI + a) * 2 * r + HEIGHT / 2;		// 动圆这一个循环的圆心的 y 值
		double FixedPoint_X = cos(PI / 2.0 + a * 2) * r + x;			// 当前循环动圆的定点对应的 x 值
		double FixedPoint_Y = sin(PI / 2.0 + a * 2) * r + y;			// 当前循环动圆的定点对应的 y 值
		double Contact_X = cos(PI / 2.0 + a) * r + x;					// 当前循环两圆切点在动圆上对应的 x 值
		double Contact_Y = sin(PI / 2.0 + a) * r + y;					// 当前循环两圆切点在动圆上对应的 y 值

		// 画出心脏线，只用画这一个循环的点和上一个循环的点的线就行
		setrop2(R2_COPYPEN);
		setlinecolor(YELLOW);
		line(lastX, lastY, FixedPoint_X, FixedPoint_Y);
		setrop2(R2_XORPEN);
		lastX = FixedPoint_X;
		lastY = FixedPoint_Y;

		// 动圆与定圆的切点
		setfillcolor(GREEN);
		solidcircle(Contact_X, Contact_Y, DISPLAY);

		// 心脏线当前点
		setfillcolor(LIGHTRED);
		solidcircle(lastX, lastY, DISPLAY);

		// 动圆
		setlinecolor(BLUE);
		circle(x, y, r);

		FlushBatchDraw();
		Sleep((double)(1000 * SECONDS) / (double)COPIES + 0.5);

		// 消除动圆
		setlinecolor(BLUE);
		circle(x, y, r);

		// 消除动圆与定圆的交点
		setfillcolor(GREEN);
		solidcircle(Contact_X, Contact_Y, DISPLAY);

		// 消除心脏线当前所在点
		setfillcolor(LIGHTRED);
		solidcircle(lastX, lastY, DISPLAY);
	}

	_getch();
	EndBatchDraw();
	return 0;
}