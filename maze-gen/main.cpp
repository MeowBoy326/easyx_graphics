/*
	程序名称：
			迷宫算法演示

	简介：
			包含迷宫生成算法和寻路算法
			迷宫生成算法：
				DFS、十字分割、随机Prim
			寻路算法：
				A*寻路、DFS（随机方向和指定优先方向）

	环境：
			VS2019 + EasyX_20200109(beta)

	时间：
			2020.2.23

	作者：
			Teternity(QQ:1926594835)

	版权：
			作者原创，无抄袭，不涉及版权问题，仅用作学习
*/



/* ********** 头文件 ********** */
#include <ctime>
#include <graphics.h>
#include "MazeAlgorithm.h"




/* ********** 全局鼠标消息 ********** */
MOUSEMSG msg;



/* ********** 简单按钮 ********** */
class Button
{
public:
	// 创建一个简单的文字按钮
	Button(int _l, int _t, const TCHAR* _text, COLORREF _up, COLORREF _down) :text(_text)
	{
		left = _l;
		top = _t;
		upColor = _up;
		downColor = _down;
	}

	// 输出抬起按下状态
	void Up()
	{
		if (!upState)
		{
			clearrectangle(left, top, left + textwidth(text), top + textheight(text));
			settextcolor(upColor);
			outtextxy(left, top, text);
			upState = true;
		}
	}
	void Down()
	{
		if (upState)
		{
			clearrectangle(left, top, left + textwidth(text), top + textheight(text));
			settextcolor(downColor);
			outtextxy(left, top, text);
			upState = false;
		}
	}

	// 鼠标是否在按钮内
	inline bool InButton()
	{
		return (msg.x >= left && msg.x <= left + textwidth(text) && msg.y >= top && msg.y <= top + textheight(text)) ? true : false;
	}

	// 自动判断并输出按钮状态，有效抬起时表示该按键被有效的点击，返回 true
	bool Operate()
	{
		if (InButton() && msg.uMsg == WM_LBUTTONUP && key) { key = false; Up(); return true; }
		if (InButton() && msg.uMsg == WM_LBUTTONDOWN) { key = true; }
		else if ((msg.uMsg == WM_LBUTTONUP || !msg.mkLButton) && key) key = false;
		InButton() ? setlinecolor(RGB(0, 255, 0)) : setlinecolor(getbkcolor());
		line(left, top + textheight(text), left + textwidth(text), top + textheight(text));
		if (InButton() && key) Down();
		else Up();
		return false;
	}

	inline void ReSet()
	{
		key = upState = false;
	}

private:
	int left = 0;			// 按钮左边坐标
	int top = 0;			// 按钮上边坐标
	bool key = false;		// 是否有效按下
	bool upState = false;	// 是否抬起状态
	COLORREF upColor;		// 抬起时字体颜色
	COLORREF downColor;		// 按下时字体颜色
	const TCHAR* text;		// 按钮文字
};



/* ********** 主函数 ********** */
int main()
{
	srand((unsigned)time(nullptr));
	MazeDemonstration maze(31, 31);

	settextstyle(24, 0, _T("Microsoft YaHei UI"));
	LOGFONT style;
	gettextstyle(&style);
	style.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&style);

	std::vector<Button> vb;
	auto text0 = _T("退出");
	auto text1 = _T("1. DFS生成 + A*寻路");
	auto text2 = _T("2. DFS生成 + DFS寻路");
	auto text3 = _T("3. DFS生成 + 随机方向DFS寻路");
	auto text4 = _T("4. 分割生成 + A*寻路");
	auto text5 = _T("5. 分割生成 + DFS寻路");
	auto text6 = _T("6. 分割生成 + 随机方向DFS寻路");
	auto text7 = _T("7. Prim生成 + A*寻路");
	auto text8 = _T("8. Prim生成 + DFS寻路");
	auto text9 = _T("9. Prim生成 + 随机方向DFS寻路");
	vb.push_back(Button(maze.SW - textwidth(text0) - 20, 10, text0, BLACK, BROWN));
	vb.push_back(Button(maze.SW / 3 - 20, maze.SW / 10 + 40 * 0, text1, BLACK, BROWN));
	vb.push_back(Button(maze.SW / 3 - 20, maze.SW / 10 + 40 * 1, text2, BLACK, BROWN));
	vb.push_back(Button(maze.SW / 3 - 20, maze.SW / 10 + 40 * 2, text3, BLACK, BROWN));
	vb.push_back(Button(maze.SW / 3 - 20, maze.SW / 10 + 40 * 3, text4, BLACK, BROWN));
	vb.push_back(Button(maze.SW / 3 - 20, maze.SW / 10 + 40 * 4, text5, BLACK, BROWN));
	vb.push_back(Button(maze.SW / 3 - 20, maze.SW / 10 + 40 * 5, text6, BLACK, BROWN));
	vb.push_back(Button(maze.SW / 3 - 20, maze.SW / 10 + 40 * 6, text7, BLACK, BROWN));
	vb.push_back(Button(maze.SW / 3 - 20, maze.SW / 10 + 40 * 7, text8, BLACK, BROWN));
	vb.push_back(Button(maze.SW / 3 - 20, maze.SW / 10 + 40 * 8, text9, BLACK, BROWN));

	int i = 0;
	bool draw = false;
	while (!(GetAsyncKeyState(VK_ESCAPE) & 0x8000))
	{
		while (MouseHit()) msg = GetMouseMsg();

		for (i = 0; i < 10; ++i)
		{
			if (vb[i].Operate())
			{
				if (i == 0) return 0;
				draw = true;
				break;
			}
		}

		if (draw)
		{
			draw = false;
			if (i == 1) { maze.DFS_generate(); maze.A_find(); }
			else if (i == 2) { maze.DFS_generate(); maze.DFS_find(); }
			else if (i == 3) { maze.DFS_generate(); maze.DFS_find(true); }
			else if (i == 4) { maze.Division_generate(); maze.A_find(); }
			else if (i == 5) { maze.Division_generate(); maze.DFS_find(); }
			else if (i == 6) { maze.Division_generate(); maze.DFS_find(true); }
			else if (i == 7) { maze.Prim_generate(); maze.A_find(); }
			else if (i == 8) { maze.Prim_generate(); maze.DFS_find(); }
			else if (i == 9) { maze.Prim_generate(); maze.DFS_find(true); }
			Button but(20, 10, _T("返回"), BLACK, BROWN);

			while (true)
			{
				while (MouseHit()) msg = GetMouseMsg();
				if (but.Operate()) break;
				Sleep(10);
			}

			cleardevice();
			for (auto& bt : vb) bt.ReSet();
		}

		Sleep(10);
	}

	return 0;
}