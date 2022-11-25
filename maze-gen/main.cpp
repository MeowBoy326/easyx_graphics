/*
	�������ƣ�
			�Թ��㷨��ʾ

	��飺
			�����Թ������㷨��Ѱ·�㷨
			�Թ������㷨��
				DFS��ʮ�ַָ���Prim
			Ѱ·�㷨��
				A*Ѱ·��DFS����������ָ�����ȷ���

	������
			VS2019 + EasyX_20200109(beta)

	ʱ�䣺
			2020.2.23

	���ߣ�
			Teternity(QQ:1926594835)

	��Ȩ��
			����ԭ�����޳�Ϯ�����漰��Ȩ���⣬������ѧϰ
*/



/* ********** ͷ�ļ� ********** */
#include <ctime>
#include <graphics.h>
#include "MazeAlgorithm.h"




/* ********** ȫ�������Ϣ ********** */
MOUSEMSG msg;



/* ********** �򵥰�ť ********** */
class Button
{
public:
	// ����һ���򵥵����ְ�ť
	Button(int _l, int _t, const TCHAR* _text, COLORREF _up, COLORREF _down) :text(_text)
	{
		left = _l;
		top = _t;
		upColor = _up;
		downColor = _down;
	}

	// ���̧����״̬
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

	// ����Ƿ��ڰ�ť��
	inline bool InButton()
	{
		return (msg.x >= left && msg.x <= left + textwidth(text) && msg.y >= top && msg.y <= top + textheight(text)) ? true : false;
	}

	// �Զ��жϲ������ť״̬����Ч̧��ʱ��ʾ�ð�������Ч�ĵ�������� true
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
	int left = 0;			// ��ť�������
	int top = 0;			// ��ť�ϱ�����
	bool key = false;		// �Ƿ���Ч����
	bool upState = false;	// �Ƿ�̧��״̬
	COLORREF upColor;		// ̧��ʱ������ɫ
	COLORREF downColor;		// ����ʱ������ɫ
	const TCHAR* text;		// ��ť����
};



/* ********** ������ ********** */
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
	auto text0 = _T("�˳�");
	auto text1 = _T("1. DFS���� + A*Ѱ·");
	auto text2 = _T("2. DFS���� + DFSѰ·");
	auto text3 = _T("3. DFS���� + �������DFSѰ·");
	auto text4 = _T("4. �ָ����� + A*Ѱ·");
	auto text5 = _T("5. �ָ����� + DFSѰ·");
	auto text6 = _T("6. �ָ����� + �������DFSѰ·");
	auto text7 = _T("7. Prim���� + A*Ѱ·");
	auto text8 = _T("8. Prim���� + DFSѰ·");
	auto text9 = _T("9. Prim���� + �������DFSѰ·");
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
			Button but(20, 10, _T("����"), BLACK, BROWN);

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