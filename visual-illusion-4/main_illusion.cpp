///////////////////////////////////////////////////
// 程序名称：视觉错觉艺术4
// 编译环境：Visual C++ 6.0 / 2013，EasyX 20140321(beta)
// 作　　者：yangw80 <yw80@qq.com>
// 最后修改：2014-7-15
//
#include <graphics.h>
#include <conio.h>


// 定义回调
void(*callback)(int x, int y);


// 画方块上的小方块
void DrawSmallBox(int x, int y, bool lt, bool rt, bool lb, bool rb)
{
	int nx = x * 26 - 13;
	int ny = y * 26 - 13;
	if (lt) solidrectangle(nx + 1, ny + 1, nx + 1 + 6, ny + 1 + 6);
	if (rt) solidrectangle(nx + 24, ny + 1, nx + 24 - 6, ny + 1 + 6);
	if (lb) solidrectangle(nx + 1, ny + 24, nx + 1 + 6, ny + 24 - 6);
	if (rb) solidrectangle(nx + 24, ny + 24, nx + 24 - 6, ny + 24 - 6);
}


// 圆中的每个点(回调函数)
void CirclePoints(int x, int y)
{
	if (x == 0 && y < 0)
		DrawSmallBox(x, y, false, false, true, true);
	else if (x == 0 && y > 0)
		DrawSmallBox(x, y, true, true, false, false);
	else if (x < 0 && y == 0)
		DrawSmallBox(x, y, false, true, false, true);
	else if (x > 0 && y == 0)
		DrawSmallBox(x, y, true, false, true, false);
	else if (x == 0 && y == 0)
		;
	else if ((x < 0 && y < 0) || (x > 0 && y > 0))
		DrawSmallBox(x, y, false, true, true, false);
	else
		DrawSmallBox(x, y, true, false, false, true);
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
void main()
{
	// 创建绘图窗口
	initgraph(640, 480);
	setbkcolor(LIGHTGRAY);
	cleardevice();
	setorigin(320, 240);

	// 画 15 x 15 的间隔黑白块，每块 26 x 26，共 390 x 390
	setlinecolor(BLACK);
	setfillcolor(WHITE);
	fillrectangle(-210, -210, 209, 209);
	COLORREF fc = WHITE;
	for (int x = -195; x < 195; x += 26)
		for (int y = -195; y < 195; y += 26)
		{
			fc = (~fc) & 0xffffff;
			setfillcolor(fc);
			solidrectangle(x, y, x + 25, y + 25);
		}

	// 在填充圆内的方块内画小方块
	setrop2(R2_XORPEN);
	setfillcolor(WHITE);
	FillCircle_Bresenham(0, 0, 6);

	// 按任意键退出
	getch();
	closegraph();
}