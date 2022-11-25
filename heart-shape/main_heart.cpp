// 程序名称：圆形组合而成的心形图案
// 编译环境：Visual C++ 6.0，EasyX 2011惊蛰版
// 最后更新：2010-10-28
//
#include <graphics.h>
#include <conio.h>
#include <math.h>

#define	PI	3.1415926536

void main()
{
	int x, y, y1, r = 50, r1;

	// 初始化图形模式
	initgraph(640, 480);
	// 设置原点为屏幕中央
	setorigin(320, 240);
	// 设置绘图颜色为红色
	setcolor(RED);

	// 用数学方法，用多个圆形组合形成心形图案
	y1 = 240 - r;
	for (double a = 0; a < 2 * PI; a += PI / 18)
	{
		x = (int)(r * cos(a));
		y = (int)(r * sin(a));
		r1 = (int)(sqrt((double)(x * x + (y + r) * (y + r))));
		circle(x, y, r1);
	}

	getch();
	closegraph();
}