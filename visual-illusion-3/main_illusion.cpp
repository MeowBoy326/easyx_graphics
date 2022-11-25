///////////////////////////////////////////////////
// 程序名称：视觉错觉艺术3
// 编译环境：Visual C++ 6.0 / 2010，EasyX_20210730
// 作　　者：yangw80 <yw80@qq.com>
// 最后修改：2014-7-14
//
#include <graphics.h>
#include <conio.h>


// 定义回调
void (*callback)(int x, int y);


// 圆中的每个点(回调函数)
void CirclePoints(int x, int y)
{
	if (x < y)
	{
		COLORREF c1 = getpixel(x, y);
		COLORREF c2 = getpixel(y, x);
		putpixel(x, y, c2);
		putpixel(y, x, c1);
	}
}


// 基于 Bresenham 算法画填充圆
// 修改自 www.easyx.cn, yw80@qq.com
void FillCircle_Bresenham(int x, int y, int r)
{
	int tx = 0, ty = r, d = 3 - 2 * r, i;

	while (tx < ty)
	{
		// 画水平两点连线(<45度)
		for (i = x - ty; i <= x + ty; i++)
		{
			CirclePoints(i, y - tx);
			if (tx != 0)	// 防止水平线重复绘制
				CirclePoints(i, y + tx);
		}

		if (d < 0)			// 取上面的点
			d += 4 * tx + 6;
		else				// 取下面的点
		{
			// 画水平两点连线(>45度)
			for (i = x - tx; i <= x + tx; i++)
			{
				CirclePoints(i, y - ty);
				CirclePoints(i, y + ty);
			}

			d += 4 * (tx - ty) + 10, ty--;
		}

		tx++;
	}

	if (tx == ty)			// 画水平两点连线(=45度)
		for (i = x - ty; i <= x + ty; i++)
		{
			CirclePoints(i, y - tx);
			CirclePoints(i, y + tx);
		}
}


// 主函数
int main()
{
	// 创建绘图窗口
	initgraph(640, 480);
	setbkcolor(LIGHTGRAY);
	cleardevice();
	setorigin(320, 240);

	// 画间隔的黑白块
	setlinecolor(BLACK);
	rectangle(-201, -201, 200, 200);
	for (int x = 0; x < 10; x++)
		for (int y = 0; y < 40; y++)
		{
			setfillcolor((((x + y) % 2) == 1) ? BLACK : WHITE);
			solidrectangle(x * 40 - 200, y * 10 - 200, x * 40 + 39 - 200, y * 10 + 9 - 200);
		}

	// 填充圆内横竖取反
	FillCircle_Bresenham(0, 0, 120);

	// 按任意键退出
	_getch();
	closegraph();
	return 0;
}