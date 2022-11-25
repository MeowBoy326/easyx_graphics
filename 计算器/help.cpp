#include"help.h"

MyChar SS[100000] = { 0 };				// 缓存文件

/***********************************帮助**************************************/

void loadtext()
{
	FILE *p;
	if (_tfopen_s(&p, _T("help.txt"), _T("rb"))	)	// 打开文件
	{
		int i = 0;
		while (!feof(p))SS[i++] = _fgettc(p);	// 读取
		fclose(p);
	}
	else
		_tcscpy_s(SS, _T("              打开文件失败！\n\n     请检查程序目录下是否含有help.txt。\n\n      请包含help.txt文件后再重新打开。"));
}

void updatewithinput4()
{
	MOUSEMSG m;	// 定义鼠标消息
	while (MouseHit())	// 检查是否有鼠标消息
	{
		m = GetMouseMsg();
		if (m.x > 5 && m.x < 40 && m.y > 0 && m.y < 35)	// 设置
		{
			help[0] = true;
			if (m.uMsg == WM_LBUTTONDOWN) software[0] = -1, software[2] = 19;
		}
		else help[0] = false;

		if (m.uMsg == WM_MOUSEWHEEL)
		{
			if (m.wheel < 0)
				fly -= 20;
			else
				fly += 20;
		}	
	}
	int len = (int)(_tcslen(SS) / 42.0 + 1) * 18 - 18;	// 字符串长度

	if (fly > 0)
		fly -= fly / 2;
	if (fly - 450 + (int)round(1.8f * len) < -len)
		fly += -((fly - 450 + (int)round(1.8f * len) + len) / 2);
}

void showscreen4()
{
	BeginBatchDraw();	// 开始批量绘图
	setbkmode(TRANSPARENT);
	
	changecolor(0, 400, 100, 550);
	IMAGE blacks = setimage(400, 450, RGB(0, 0, 0));	// 设置绘图
	my_putimage(0, 100, &blacks, RGB(255, 255, 255), 0, 1, 60, 0);

	settextcolor(WHITE);
	settextstyle(18, 0, _T("宋体"), 0, 0, 200, false, false, false);
	RECT r = { 10, 100 + fly, 390, 1500 + fly };
	
	drawtext(SS, &r, DT_LEFT | DT_WORDBREAK);	// 写文字

	changecolor(0, 400, 0, 100);
	blacks = setimage(400, 101, RGB(0, 0, 0));	// 设置绘图
	my_putimage(0, 0, &blacks, RGB(255, 255, 255), 0, 1, 60, 0);
	settextstyle(40, 0, _T("华文行楷"));
	outtextxy(160, 50, _T("简介"));

	changecolor(0, 400, 550,  600);
	blacks = setimage(400, 50, RGB(0, 0, 0));	// 设置绘图
	my_putimage(0, 550, &blacks , RGB(255, 255, 255), 0, 1, 60, 0);

	settextcolor(WHITE);
	settextstyle(30, 0, _T("微软雅黑"));
	outtextxy(40, 10, _T("帮助"));
	if (help[0])settextcolor(RGB(0, 255, 255));
	else settextcolor(WHITE);
	settextstyle(30, 28, _T("微软雅黑"));
	outtextxy(0, 10, _T("≡"));
	settextstyle(50, 10, _T("微软雅黑"));

	EndBatchDraw();
}