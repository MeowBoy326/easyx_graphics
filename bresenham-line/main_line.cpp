///////////////////////////////////////////////////
// 程序名称：基于 Bresenham 算法画任意斜率的直线
// 编译环境：Visual C++ 6.0 / 2010，EasyX 2011惊蛰版
// 作　　者：yangw80 <yw80@qq.com>
// 发布日期：2011-4-26
//
#include <graphics.h>
#include <conio.h>

// 使用 Bresenham 算法画任意斜率的直线（包括起始点，不包括终止点）
void Line_Bresenham(int x1, int y1, int x2, int y2, int color)
{
	int x = x1;
	int y = y1;
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int s1 = x2 > x1 ? 1 : -1;
	int s2 = y2 > y1 ? 1 : -1;

	bool interchange = false;	// 默认不互换 dx、dy
	if (dy > dx)				// 当斜率大于 1 时，dx、dy 互换
	{
		int temp = dx;
		dx = dy;
		dy = temp;
		interchange = true;
	}

	int p = 2 * dy - dx;
	for (int i = 0; i < dx; i++)
	{
		putpixel(x, y, color);
		if (p >= 0)
		{
			if (!interchange)		// 当斜率 < 1 时，选取上下象素点
				y += s2;
			else					// 当斜率 > 1 时，选取左右象素点
				x += s1;
			p -= 2 * dx;
		}
		if (!interchange)
			x += s1;				// 当斜率 < 1 时，选取 x 为步长
		else
			y += s2;				// 当斜率 > 1 时，选取 y 为步长
		p += 2 * dy;
	}
}

// 主函数
int main()
{
	initgraph(640, 480);

	// 测试画线
	Line_Bresenham(100, 1, 1, 478, GREEN);
	Line_Bresenham(1, 478, 638, 1, GREEN);

	// 按任意键退出
	_getch();
	closegraph();
	return 0;
}