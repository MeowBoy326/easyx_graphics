#include <graphics.h>
#include <conio.h>

int main()
{
	initgraph(200, 200);			// 初始化图形窗口
	HWND hWnd = GetHWnd();			// 获取窗口句柄

	// 获取窗口边框宽高
	RECT rcClient, rcWind;
	GetClientRect(hWnd, &rcClient);
	GetWindowRect(hWnd, &rcWind);
	int cx = ((rcWind.right - rcWind.left) - rcClient.right) / 2;
	int cy = ((rcWind.bottom - rcWind.top + GetSystemMetrics(SM_CYCAPTION)) - rcClient.bottom) / 2;

	// 设置圆形区域
	HRGN rgn = CreateEllipticRgn(0 + cx, 0 + cy, 200 + cx, 200 + cy);
	SetWindowRgn(hWnd, rgn, true);

	// 画彩虹球
	setlinestyle(PS_SOLID, 2);
	for (int r = 99; r > 0; r--)
	{
		setlinecolor(HSLtoRGB(360 - r * 3.6f, 1, 0.5));
		circle(99, 99, r);
	}

	ExMessage m;						// 定义鼠标消息

	while (true)
	{
		m = getmessage(EM_MOUSE);		// 获取一条鼠标消息

		switch (m.message)
		{
		case WM_LBUTTONDOWN:
			// 如果左键按下，欺骗 windows 点在了标题栏上
			PostMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(m.x, m.y));
			break;

		case WM_RBUTTONUP:			// 按鼠标右键退出程序
			closegraph();
			return 0;
		}
	}
}