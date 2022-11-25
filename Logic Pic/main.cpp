/*
* 作者	:慢热友人
* QQ	:1171879350
* 邮箱	:1171879350@qq.com
* 最后修改	:2021-3-15
* 编译环境	: Visual Studio 2019
* EasyX版本	: EasyX 2021-1-15
*/

#include"GUI.h"

int main()
{
	HWND hWnd = initgraph(500, 650, EW_NOCLOSE
#ifdef _DEBUG
		| EW_SHOWCONSOLE
#endif // _DEBUG
		);

	//设置窗口位置
	SetWindowPos(hWnd, NULL, 350, 20, 0, 0, SWP_NOSIZE);

	setbkcolor(0xffcc66);
	cleardevice();

	GUI::GetGUI()->Run();

	//释放资源
	delete GUI::GetGUI();

	return 0;
}