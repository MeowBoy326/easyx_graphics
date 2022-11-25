#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

#define R 30		// 定义球的半径

int main()
{
	// 创建图形窗口，禁用“关闭”按钮，以防止无法正确保存配置文件
	initgraph(640, 480, EW_NOCLOSE);

	// 读取上一次的位置
	int x, y;
	x = GetPrivateProfileInt(_T("Ball"), _T("x"), 320, _T(".\\test.ini"));
	y = GetPrivateProfileInt(_T("Ball"), _T("y"), 240, _T(".\\test.ini"));

	// 设置球的颜色，并绘制
	setfillcolor(GREEN);
	solidcircle(x, y, R);

	MOUSEMSG msg;			// 鼠标消息
	int mx, my;				// 鼠标上一次的位置
	bool keydown = false;	// 左键是否按下

	// 主循环
	while (!_kbhit())
	{
		while (MouseHit())
		{
			msg = GetMouseMsg();		// 获取鼠标消息
			switch (msg.uMsg)
			{
				// 按下鼠标左键，开始拖动
			case WM_LBUTTONDOWN:
				if (sqrt((double)((msg.x - x) * (msg.x - x) + (msg.y - y) * (msg.y - y))) < R)
				{
					keydown = true;
					mx = msg.x;
					my = msg.y;
				}
				break;

				// 抬起鼠标左键，停止拖动
			case WM_LBUTTONUP:
				keydown = false;
				break;

				// 鼠标移动，处理拖动
			case WM_MOUSEMOVE:
				if (keydown)
				{
					clearcircle(x, y, R);
					x += (msg.x - mx);
					y += (msg.y - my);
					mx = msg.x;
					my = msg.y;
					solidcircle(x, y, R);
				}
				break;
			}
		}

		// 延时，降低 cpu 占用率
		Sleep(10);
	}

	// 保存坐标到配置文件
	TCHAR s[20];
	_stprintf(s, _T("%d"), x);			// vc6 的写法
	//	_stprintf_s(s, _T("%d"), x);	// >= vc6 的写法
	::WritePrivateProfileString(_T("Ball"), _T("x"), s, _T(".\\test.ini"));

	_stprintf(s, _T("%d"), y);			// vc6 的写法
	//	_stprintf_s(s, _T("%d"), y);	// >= vc6 的写法
	::WritePrivateProfileString(_T("Ball"), _T("y"), s, _T(".\\test.ini"));

	// 关闭绘图窗口
	closegraph();
	return 0;
}