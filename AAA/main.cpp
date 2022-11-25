/*
	程序名称：
			炸金花小游戏

	简介：
			用 EasyX 实现的一个简单的炸金花小游戏
			似乎市面上的炸金花小游戏均被禁了，宅在家连炸金花小游戏都没有
			因此简单制作了该小游戏

	环境：
			VS2019 + EasyX_20200109(beta)

	时间：
			2020.2.16

	作者：
			Teternity(QQ:1926594835)

	版权：
			作者原创，无抄袭，不涉及版权问题，仅用作学习
*/

#include "Controller.h"

int main()
{
	srand((unsigned)time(nullptr));
	Controller* ctrl = Controller::GetInstance();

	while (!(GetAsyncKeyState(VK_ESCAPE) & 0x8000))
	{
		ctrl->Flush();
		Sleep(10);
	}

	delete ctrl;
	return 0;
}