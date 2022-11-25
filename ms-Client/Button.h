#pragma once


/* ----------头文件---------- */
#include <easyx.h>


/* ----------简单按钮---------- */
class Button
{
public:
	// 构造函数
	Button(int x, int y, const TCHAR* text)
	{
		px = x;
		py = y;
		width = textwidth(text) + textheight(text) * 2;
		height = textheight(text) * 3 / 2;
		RECT rect{ 0,0,width,height };

		LOGFONT fnt;
		gettextstyle(&fnt);

		// 绘制 imgUp
		imgUp.Resize(width, height);
		SetWorkingImage(&imgUp);
		setbkcolor(LIGHTGRAY);
		cleardevice();
		setlinecolor(DARKGRAY);
		line(width - 1, 0, width - 1, height - 1);
		line(0, height - 1, width - 1, height - 1);
		line(width - 2, 1, width - 2, height - 2);
		line(1, height - 2, width - 2, height - 2);
		setlinecolor(WHITE);
		line(0, 0, width - 2, 0);
		line(0, 0, 0, height - 2);
		line(1, 1, width - 3, 1);
		line(1, 1, 1, height - 3);
		settextstyle(&fnt);
		settextcolor(DARKGRAY);
		drawtext(text, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		// 绘制 imgDown
		imgDown.Resize(width, height);
		SetWorkingImage(&imgDown);
		setbkcolor(LIGHTGRAY);
		cleardevice();
		setlinecolor(DARKGRAY);
		line(width - 1, 0, width - 1, height - 1);
		line(0, height - 1, width - 1, height - 1);
		line(0, 0, width - 2, 0);
		line(0, 0, 0, height - 2);
		line(1, 1, width - 3, 1);
		line(1, 1, 1, height - 3);
		settextstyle(&fnt);
		settextcolor(DARKGRAY);
		drawtext(text, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		SetWorkingImage();
		setUp();
	}

	// 检查状态
	bool check(MOUSEMSG& msg)
	{
		if (select && msg.uMsg == WM_LBUTTONUP)
		{
			setUp();
			select = false;
			if (inBox(msg))
			{
				Sleep(100);
				return true;
			}
		}
		if (inBox(msg))
		{
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				select = true;
				setDown();
			}
			else if (select && state == Button::State::UP) setDown();
		}
		else setUp();
		return false;
	}

private:
	// 按钮抬起
	void setUp()
	{
		putimage(px - width / 2, py - height / 2, &imgUp);
		state = State::UP;
	}

	// 按钮按下
	void setDown()
	{
		putimage(px - width / 2, py - height / 2, &imgDown);
		state = State::DOWN;
	}

	// 检查鼠标是否在按钮内
	bool inBox(MOUSEMSG& msg)
	{
		int left = px - width / 2;
		return msg.x >= px - width / 2 && msg.x < px + width / 2 && msg.y >= py - height / 2 && msg.y < py + height / 2;
	}

private:
	IMAGE imgUp;					// 按钮抬起状态图片
	IMAGE imgDown;					// 按钮按下状态图片
	int px, py;						// 按钮矩形中心位置
	int width, height;				// 按钮矩形宽高
	enum class State { UP, DOWN };
	State state = State::UP;		// 按钮状态
	bool select = false;			// 按钮是否有效选择
};
