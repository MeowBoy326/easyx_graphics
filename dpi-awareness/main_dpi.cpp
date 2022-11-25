// 编译环境：Win10 + VS2019 + EasyX_20200727
//

// 设定操作系统版本为 Win10（需要放到 #include <graphics.h> 前面）
#define WINVER 0x0A00
#define _WIN32_WINNT 0x0A00

#include <graphics.h>
#include <conio.h>
#include <ShellScalingApi.h>		// 引用头文件
#pragma comment(lib, "Shcore.lib")	// 链接库文件

int main()
{
	// 设置该进程不受系统 DPI 设置影响
	SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);

	// 创建图形窗口，并画一个圆
	initgraph(640, 480);
	circle(320, 240, 200);

	// 按任意键关闭绘图窗口
	_getch();
	closegraph();
	return 0;
}