/*
	�������ƣ�
			ը��С��Ϸ

	��飺
			�� EasyX ʵ�ֵ�һ���򵥵�ը��С��Ϸ
			�ƺ������ϵ�ը��С��Ϸ�������ˣ�լ�ڼ���ը��С��Ϸ��û��
			��˼������˸�С��Ϸ

	������
			VS2019 + EasyX_20200109(beta)

	ʱ�䣺
			2020.2.16

	���ߣ�
			Teternity(QQ:1926594835)

	��Ȩ��
			����ԭ�����޳�Ϯ�����漰��Ȩ���⣬������ѧϰ
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