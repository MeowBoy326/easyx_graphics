/*
* ����	:��������
* QQ	:1171879350
* ����	:1171879350@qq.com
* ����޸�	:2021-3-15
* ���뻷��	: Visual Studio 2019
* EasyX�汾	: EasyX 2021-1-15
*/

#include"GUI.h"

int main()
{
	HWND hWnd = initgraph(500, 650, EW_NOCLOSE
#ifdef _DEBUG
		| EW_SHOWCONSOLE
#endif // _DEBUG
		);

	//���ô���λ��
	SetWindowPos(hWnd, NULL, 350, 20, 0, 0, SWP_NOSIZE);

	setbkcolor(0xffcc66);
	cleardevice();

	GUI::GetGUI()->Run();

	//�ͷ���Դ
	delete GUI::GetGUI();

	return 0;
}