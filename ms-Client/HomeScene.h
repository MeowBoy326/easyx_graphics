#pragma once


/* ----------ͷ�ļ�---------- */
#include "Datas.h"
#include "Button.h"


/* ----------��ʼ����---------- */
class HomeScene
{
public:
	static PState create()
	{
		cleardevice();

		// �������
		settextcolor(DARKGRAY);
		settextstyle(48, 0, _T("΢���ź�"));
		const TCHAR* text = _T("ɨ�ס���ս��");
		outtextxy((win_width - textwidth(text)) / 2, win_height / 5 - textheight(text) / 2, text);

		// ��Ϸ����
		settextstyle(20, 0, _T("΢���ź�"));
		const TCHAR* rule = _T("������·������飬���������䣬�򷭿����һ��������Ӯ");
		outtextxy((win_width - textwidth(rule)) / 2, win_height / 10 * 9 - textheight(rule) / 2, rule);

		// ��ʼƥ�䰴ť
		text = _T("��ʼƥ��");
		settextstyle(24, 0, _T("΢���ź�"));
		Button butStart(win_width / 2, win_height / 4 * 3, text);

		// �˳���ť
		text = _T("�˳�");
		settextstyle(20, 0, _T("΢���ź�"));
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
