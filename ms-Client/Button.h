#pragma once


/* ----------ͷ�ļ�---------- */
#include <easyx.h>


/* ----------�򵥰�ť---------- */
class Button
{
public:
	// ���캯��
	Button(int x, int y, const TCHAR* text)
	{
		px = x;
		py = y;
		width = textwidth(text) + textheight(text) * 2;
		height = textheight(text) * 3 / 2;
		RECT rect{ 0,0,width,height };

		LOGFONT fnt;
		gettextstyle(&fnt);

		// ���� imgUp
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

		// ���� imgDown
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

	// ���״̬
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
	// ��ţ̌��
	void setUp()
	{
		putimage(px - width / 2, py - height / 2, &imgUp);
		state = State::UP;
	}

	// ��ť����
	void setDown()
	{
		putimage(px - width / 2, py - height / 2, &imgDown);
		state = State::DOWN;
	}

	// �������Ƿ��ڰ�ť��
	bool inBox(MOUSEMSG& msg)
	{
		int left = px - width / 2;
		return msg.x >= px - width / 2 && msg.x < px + width / 2 && msg.y >= py - height / 2 && msg.y < py + height / 2;
	}

private:
	IMAGE imgUp;					// ��ţ̌��״̬ͼƬ
	IMAGE imgDown;					// ��ť����״̬ͼƬ
	int px, py;						// ��ť��������λ��
	int width, height;				// ��ť���ο��
	enum class State { UP, DOWN };
	State state = State::UP;		// ��ť״̬
	bool select = false;			// ��ť�Ƿ���Чѡ��
};
