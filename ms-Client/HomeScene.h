#pragma once


/* ----------头文件---------- */
#include "Datas.h"
#include "Button.h"


/* ----------初始场景---------- */
class HomeScene
{
public:
	static PState create()
	{
		cleardevice();

		// 输出标题
		settextcolor(DARKGRAY);
		settextstyle(48, 0, _T("微软雅黑"));
		const TCHAR* text = _T("扫雷·对战版");
		outtextxy((win_width - textwidth(text)) / 2, win_height / 5 - textheight(text) / 2, text);

		// 游戏规则
		settextstyle(20, 0, _T("微软雅黑"));
		const TCHAR* rule = _T("左键按下翻开方块，翻开雷判输，或翻开最后一个方块判赢");
		outtextxy((win_width - textwidth(rule)) / 2, win_height / 10 * 9 - textheight(rule) / 2, rule);

		// 开始匹配按钮
		text = _T("开始匹配");
		settextstyle(24, 0, _T("微软雅黑"));
		Button butStart(win_width / 2, win_height / 4 * 3, text);

		// 退出按钮
		text = _T("退出");
		settextstyle(20, 0, _T("微软雅黑"));
		Button butEnd(win_width - 50, 30, text);

		while (!(GetAsyncKeyState(VK_ESCAPE) & 0x8000))
		{
			while (MouseHit()) msg = GetMouseMsg();
			if (butStart.check(msg)) return PState::RUM;
			if (butEnd.check(msg)) return PState::END;
			Sleep(1);
		}

		return PState::END;
	}
};
