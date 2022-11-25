/*
	�������ƣ�
			ɨ��������ս�� - �ͻ���

	��飺
			����ƥ���ս��ɨ�׳���������·������飬���������䣬�򷭿����һ��������Ӯ

	������
			VS2019 + EasyX_20210115(beta)

	ʱ�䣺
			2021.1.18

	���ߣ�
			Teternity(QQ:1926594835)

	��Ȩ��
			����ԭ�����޳�Ϯ�����漰��Ȩ���⣬������ѧϰ
*/


/* ----------ͷ�ļ�---------- */
#include "RunningScene.h"
#include "HomeScene.h"


/* ----------������---------- */
int main()
{
	if (!WinsockTcp::Startup()) return -1;

	initgraph(win_width, win_height, EW_NOMINIMIZE | EW_NOCLOSE);
	setbkcolor(LIGHTGRAY);
	initImages();

	PState state = PState::HOME;
	while (true)
	{
		if (state == PState::END) break;
		else if (state == PState::HOME) state = HomeScene::create();
		else state = RunningScene::create();
	}

	closegraph();

	WinsockTcp::Cleanup();
	return 0;
}
