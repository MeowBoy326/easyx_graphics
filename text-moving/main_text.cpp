#include <graphics.h>
#include <conio.h>


// 文字输出（不破坏背景）
// 参数：
//  x, y: 输出文字的位置
//  s: 输出文字的指针。如果指针为 NULL，表示恢复背景。
void myouttextxy(int x, int y, LPCTSTR s)
{
	static IMAGE tmp;				// 用来保存被文字覆盖的区域背景

	if (s == NULL)
	{
		// 恢复区域
		putimage(x, y, &tmp);
	}
	else
	{
		int w = textwidth(s);		// 获取字符串占用的宽度
		int h = textheight(s);		// 获取字符串占用的高度

		// 保存区域
		getimage(&tmp, x, y, w, h);

		// 文字输出
		outtextxy(x, y, s);
	}
}


// 主函数
void main()
{
	// 定义字符串
	TCHAR s[] = _T("测试文字");

	// 创建绘图窗口
	initgraph(640, 480);

	// 绘制背景
	for (int i = 0; i < 640; i++)
	{
		setlinecolor(HSLtoRGB((float)i, 1.0, 0.25));
		line(i, 0, i, 479);
	}

	// 设置文字效果
	settextcolor(WHITE);		// 设置文字颜色为白色
	setbkmode(TRANSPARENT);		// 设置文字背景为透明色

	// 绘制移动的文字
	for (int j = 0; j < 600; j++)
	{
		// 绘制文字
		myouttextxy(j, 100, s);

		Sleep(20);

		// 擦掉文字
		myouttextxy(j, 100, NULL);
	}

	// 退出
	_getch();
	closegraph();
}