///////////////////////////////////////////////////
// 程序名称：基于 Bresenham 算法画圆
// 编译环境：Visual C++ 6.0 / 2010，EasyX_20210730
// 作　　者：YangW <yw80@qq.com>
// 最后修改：2011-5-3
//
#include <graphics.h>
#include <conio.h>

// 使用 Bresenham 画圆法
void Circle_Bresenham(int x, int y, int r, int color)
{
	int tx = 0, ty = r, d = 3 - 2 * r;

	while (tx <= ty)
	{
		// 利用圆的八分对称性画点
		putpixel(x + tx, y + ty, color);
		putpixel(x + tx, y - ty, color);
		putpixel(x - tx, y + ty, color);
		putpixel(x - tx, y - ty, color);
		putpixel(x + ty, y + tx, color);
		putpixel(x + ty, y - tx, color);
		putpixel(x - ty, y + tx, color);
		putpixel(x - ty, y - tx, color);

		if (d < 0)		// 取上面的点
			d += 4 * tx + 6;
		else			// 取下面的点
			d += 4 * (tx - ty) + 10, ty--;

		tx++;
	}
}

// 主函数
int main()
{
	initgraph(640, 480);

	// 测试画圆
	Circle_Bresenham(320, 240, 200, RED);
	Circle_Bresenham(320, 240, 101, RED);

	// 按任意键退出
	_getch();
	closegraph();
	return 0;
}
