/*
	程序名称：
			扫雷联网对战版 - 客户端

	简介：
			联网匹配对战的扫雷程序，左键按下翻开方块，翻开雷判输，或翻开最后一个方块判赢

	环境：
			VS2019 + EasyX_20210115(beta)

	时间：
			2021.1.18

	作者：
			Teternity(QQ:1926594835)

	版权：
			作者原创，无抄袭，不涉及版权问题，仅用作学习
*/


/* ----------头文件---------- */
#include "RunningScene.h"
#include "HomeScene.h"


/* ----------主函数---------- */
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
