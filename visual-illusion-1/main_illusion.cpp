///////////////////////////////////////////////////
// 程序名称：视觉错觉艺术1
// 编译环境：Visual C++ 6.0，EasyX 2013霜降版
// 作　　者：yangw80 <yw80@qq.com>
// 最后修改：2013-12-16
//
#include <graphics.h>
#include <conio.h>

// 定义常量
#define	UNIT		15
#define OFFSET_X	122
#define OFFSET_Y	23

// 画每个小单元
void DrawUnit(int x, int y, int shape)
{
	// 定义颜色
	static COLORREF c[4] = {0x0000ff, 0x0077ff, 0x00ddff, 0x0077ff};

	// 画背景白色角块
	setfillcolor(WHITE);
	switch(shape)
	{
		case 0:
			solidrectangle(x, y, x + UNIT - 1, y + UNIT - 1);
			break;
		case 1:
			solidrectangle(x, y + UNIT / 2, x + UNIT / 2, y + UNIT - 1);
			break;
		case 3:
			solidrectangle(x + UNIT / 2, y, x + UNIT - 1, y + UNIT / 2);
			break;
	}

	// 画彩色角块
	setfillcolor(c[shape]);
	if (shape % 2 == 0)
	{
		solidrectangle(x, y + UNIT / 2, x + UNIT / 2, y + UNIT - 1);
		solidrectangle(x + UNIT / 2, y, x + UNIT - 1, y + UNIT / 2);
	}
	else
	{
		solidrectangle(x, y, x + UNIT / 2, y + UNIT / 2);
		solidrectangle(x + UNIT / 2, y + UNIT / 2, x + UNIT - 1, y + UNIT - 1);
	}

	// 画圆角矩形
	solidroundrect(x, y, x + UNIT - 1, y + UNIT - 1, 9, 9);
}

// 主函数
void main()
{
	// 创建绘图窗体
	initgraph(800, 600);
	// 设置坐标原点
	setorigin(OFFSET_X, OFFSET_Y);

	int x, y;

	// 画背景及灰色边框
	setbkcolor(WHITE);
	cleardevice();
	setfillcolor(0xf3f3f3);
	solidrectangle(-8, -8, UNIT * 37 + 8 - 1, UNIT * 37 + 8 - 1);
	setfillcolor(BLACK);
	solidrectangle(0, 0, UNIT * 37 - 1, UNIT * 37 - 1);

	// 生成规律的图案
	for (y = 0; y < 37; y++)
	{
		int shape = (4 - y % 4) & 3;
		for (x = 0; x < 37; x++)
		{
			DrawUnit(x * UNIT, y * UNIT, shape++);
			shape &= 0x3;
		}
	}

	// 中央部分左右颠倒
	COLORREF c1, c2;
	for (y = 8 * UNIT + UNIT / 2; y < (37 - 8) * UNIT - UNIT / 2; y++)
		for (x = 8 * UNIT + UNIT / 2; x < 37 * UNIT / 2; x++)
		{
			c1 = getpixel(x, y);
			c2 = getpixel(37 * UNIT - x - 1, y);
			putpixel(x, y, c2);
			putpixel(37 * UNIT - x - 1, y, c1);
		}

	// 按任意键退出
	getch();
	closegraph();
}