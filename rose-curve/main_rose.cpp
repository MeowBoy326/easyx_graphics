////////////////////////////////////////////
// 程序名称：高等数学图形：玫瑰曲线
// 编译环境：Visual C++ 6.0 / 2010，EasyX 2011惊蛰版
// 程序编写：yangw80 <yw80@qq.com>
// 最后更新：2011-7-11
//
#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

#define PI 3.14159265

// 画玫瑰曲线
// 参数：
//		k = n / d: 玫瑰曲线方程参数
//		r: 半径
void DrawRoseCurve(int n, int d, int r)
{
	int x, y;

	bar(-240, -240, 239, 239);
	setcolor(GREEN);
	moveto(0, 0);
	for (double i = 0; i <= PI * 2; i += 0.001)
	{
		x = int(r * sin(n * PI * i) * cos(d * PI * i));
		y = int(r * sin(n * PI * i) * sin(d * PI * i));
		lineto(x, y);
	}
}

// 主函数
void main()
{
	initgraph(640, 480);	// 初始化绘图窗口
	setorigin(240, 240);	// 设置坐标原点为屏幕中央
	setfillstyle(BLACK);	// 设置填充色为黑色

	// 输出提示信息
	line(240, -240, 240, 239);
	RECT r = { 245, -200, 395, 220 };
	setfont(13, 0, "Consolas");
	drawtext("玫瑰曲线 ( Rose curve )\n\n[简介]\n　　在极坐标系中，以下方程表示的曲线称为玫瑰			曲线：\n　　r = sin ( k θ )\n　　或\n　　r = cos ( k θ )\n　　当 k 是奇数时，玫			瑰曲线有 k 个花瓣；\n　　当 k 是偶数时，玫瑰曲线有 2k 个花瓣。\n\n[控制]\n　　k = 			n / d\n　　a-z: 设置 n 为 1-26\n　　A-Z: 设置 d 为 1-26\n　　ESC: 退出\n\n[当前值]			\n　　k = n / d\n　　　= 2 / 1", &r, DT_WORDBREAK);

	char cmd = 'b';
	char tmp[20];
	int n = 2;
	int d = 1;
	while (cmd != 27)
	{
		if (cmd >= 'a' && cmd <= 'z')
			n = cmd - 'a' + 1;
		else if (cmd >= 'A' && cmd <= 'Z')
			d = cmd - 'A' + 1;

		sprintf(tmp, "　　　= %d / %d　", n, d);
		setcolor(WHITE);
		outtextxy(245, 86, tmp);

		DrawRoseCurve(n, d, 200);
		cmd = getch();
	}

	closegraph();
}