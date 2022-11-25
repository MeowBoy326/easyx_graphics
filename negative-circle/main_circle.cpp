///////////////////////////////////////////////////
// 程序名称：基于正负算法画圆
// 编译环境：Visual C++ 6.0 / 2010，EasyX_20210115
// 作　　者：YangW <yw80@qq.com>
// 最后修改：2011-5-3
//
#include <graphics.h>
#include <conio.h>

// 正负画圆法
void Circle_PN(int x, int y, int r, int color)
{
	int tx = 0, ty = r, f = 0;

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

		if (f <= 0)
			f = f + 2 * tx + 1, tx++;
		else
			f = f - 2 * ty + 1, ty--;
	}
}

// 主函数
int main()
{
	initgraph(640, 480);

	// 测试画圆
	Circle_PN(320, 240, 200, RED);
	Circle_PN(320, 240, 101, RED);

	// 按任意键退出
	_getch();
	closegraph();
	return 0;
}