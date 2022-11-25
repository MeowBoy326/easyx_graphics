// 程序名称：Hilbert (希尔伯特)曲线 (基于 L 系统绘制)
// 编译环境：Visual C++ 6.0，EasyX 2011惊蛰版
// 最后修改：2011-3-7
//
#include <graphics.h>
#include <conio.h>

int g_len;	// Hilbert 曲线的单位长度

// 递归绘制 Hilbert 曲线
void hilbert(LPCTSTR cmd, int level)
{
	static BYTE d = 0;								// 方向
	static POINT c[4] = { 1, 0, 0, -1, -1, 0, 0, 1 };	// 方向对应的轴系数

	if (level < 0) return;

	// 处理命令字符串
	int i = 0;
	while (cmd[i])
	{
		switch (cmd[i++])
		{
		case '+':	d = (d + 1) & 3;							break;
		case '-':	d = (d - 1) & 3;							break;
		case 'X':	hilbert("+YF-XFX-FY+", level - 1);			break;
		case 'Y':	hilbert("-XF+YFY+FX-", level - 1);			break;
		case 'F':	linerel(c[d].x * g_len, c[d].y * g_len);	break;
		}
	}
}

// 主函数
void main()
{
	// 设置绘图环境
	initgraph(1024, 1024);						// 设置窗口大小
	outtextxy(20, 20, "按 1～8 显示不同级别的 Hilbert 曲线，按 ESC 退出。");
	rectangle(0, 0, 1024, 1024);				// 绘制表示范围的矩形框
	setorigin(0, 0);							// 设置原点坐标
	setcolor(RED);								// 设置颜色
	setfillstyle(BLACK);
	int level = '6';							// 设置初始级别
	do
	{
		if (level >= '1' && level <= '9')		// 仅处理 1～9
		{
			level -= '0';						// 转换为对应的数字值
			bar(0, 0, 1024, 1024);				// 清空绘图区
			g_len = 1024 >> level;				// 计算单位长度
			moveto(g_len / 2, 1024 - g_len / 2);	// 设定起点
			hilbert("X", level);				// 递归绘制 Hilbert 曲线
		}
	} while ((level = getch()) != 27);			// 按 ESC 退出

	closegraph();
}