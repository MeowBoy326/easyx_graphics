///////////////////////////////////////////////////
// 程序名称：基于中点算法画圆
// 编译环境：Visual C++ 6.0 / 2010，EasyX_20210730
// 作　　者：YangW <yw80@qq.com>
// 最后修改：2011-4-29
//
#include <graphics.h>
#include <conio.h>

// 中点画圆法
void Circle_Midpoint(int x, int y, int r, int color)
{
	int tx = 0, ty = r, d = 1 - r;

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

		if (d < 0)
			d += 2 * tx + 3;
		else
			d += 2 * (tx - ty) + 5, ty--;

		tx++;
	}
}

// 主函数
int main()
{
	initgraph(640, 480);

	// 测试画圆
	Circle_Midpoint(320, 240, 200, RED);
	Circle_Midpoint(320, 240, 101, RED);

	// 按任意键退出
	_getch();
	closegraph();
	return 0;
}