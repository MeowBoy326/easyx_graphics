///////////////////////////////////////////////////
// 程序名称：基于 Bresenham 算法画填充圆
// 编译环境：Visual C++ 6.0 / 2013，EasyX 20140321(beta)
// 作　　者：yangw80 <yw80@qq.com>
// 最后修改：2014-7-14
//
#include <graphics.h>
#include <conio.h>

// 基于 Bresenham 算法画填充圆
void FillCircle_Bresenham(int x, int y, int r, COLORREF color)
{
	int tx = 0, ty = r, d = 3 - 2 * r, i;

	while (tx < ty)
	{
		// 画水平两点连线(<45度)
		for (i = x - ty; i <= x + ty; i++)
		{
			putpixel(i, y - tx, color);
			if (tx != 0)	// 防止水平线重复绘制
				putpixel(i, y + tx, color);
		}

		if (d < 0)			// 取上面的点
			d += 4 * tx + 6;
		else				// 取下面的点
		{
			// 画水平两点连线(>45度)
			for (i = x - tx; i <= x + tx; i++)
			{
				putpixel(i, y - ty, color);
				putpixel(i, y + ty, color);
			}

			d += 4 * (tx - ty) + 10, ty--;
		}

		tx++;
	}

	if (tx == ty)			// 画水平两点连线(=45度)
		for (i = x - ty; i <= x + ty; i++)
		{
			putpixel(i, y - tx, color);
			putpixel(i, y + tx, color);
		}
}

// 主函数
int main()
{
	// 创建绘图窗口
	initgraph(640, 480);

	// 测试画填充圆
	FillCircle_Bresenham(320, 240, 100, GREEN);

	// 按任意键退出
	getch();
	closegraph();
	return 0;
}

