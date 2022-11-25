///////////////////////////////////////////////////
// 程序名称：基于中点算法画任意斜率的直线
// 编译环境：Visual C++ 6.0 / 2010，EasyX 2011惊蛰版
// 作　　者：yangw80 <yw80@qq.com>
// 最后修改：2011-4-26
//
#include <graphics.h>
#include <conio.h>

// 使用中点算法画任意斜率的直线（包括起始点，不包括终止点）
void Line_Midpoint(int x1, int y1, int x2, int y2, int color)
{
	int x = x1, y = y1;
	int a = y1 - y2, b = x2 - x1;
	int cx = (b >= 0 ? 1 : (b = -b, -1));
	int cy = (a <= 0 ? 1 : (a = -a, -1));

	int d, d1, d2;
	if (-a <= b)		// 斜率绝对值 <= 1
	{
		d = 2 * a + b;
		d1 = 2 * a;
		d2 = 2 * (a + b);
		while (x != x2)
		{
			putpixel(x, y, color);

			if (d < 0)
				y += cy, d += d2;
			else
				d += d1;
			x += cx;
		}
	}
	else				// 斜率绝对值 > 1
	{
		d = 2 * b + a;
		d1 = 2 * b;
		d2 = 2 * (a + b);
		while (y != y2)
		{
			putpixel(x, y, color);

			if (d < 0)
				d += d1;
			else
				x += cx, d += d2;
			y += cy;
		}
	}
}

// 主函数
int main()
{
	initgraph(640, 480);

	// 测试画线
	Line_Midpoint(100, 1, 1, 478, GREEN);
	Line_Midpoint(1, 478, 638, 1, GREEN);

	Line_Midpoint(100, 100, 200, 100, GREEN);
	Line_Midpoint(200, 102, 200, 200, GREEN);
	Line_Midpoint(100, 102, 100, 200, GREEN);



	// 按任意键退出
	_getch();
	closegraph();
	return 0;
}