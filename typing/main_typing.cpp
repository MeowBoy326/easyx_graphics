//////////////////////////////////////////////////////
// �������ƣ�C ������ũר�õĴ�����ϰ����
// ���뻷����Visual C++ 2008, EasyX_20190415(beta) 
// �������ߣ���������һ��
// ������QQ��1677376433
// ����޸ģ�2019-5-10
//
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <stdio.h>

const int WIDTH = 640;			// ������
const int HEIGHT = 500;			// ����߶�


//////////////////////////////////////////////////////
// ������Ϸ��ʱ����
class GameClock
{
private:
	clock_t clockBegin;
	clock_t clockNow;
	int		timeMax;
	int		timeNow;

public:
	// ���캯������ʼ��ʱ��
	GameClock(int max)
	{
		clockBegin = clock();
		clockNow = 0;
		timeMax = max;
		timeNow = max;
	}

	// ���ص�ǰʣ������
	int Now()
	{
		return timeNow;
	}

	// �����Ѿ����ĵ�����
	int Elapse()
	{
		return timeMax - timeNow;
	}

	// �ж��Ƿ��ʱ��ֹ
	bool IsStop()
	{
		return timeNow > 0;
	}

	// ��Ϸ��ѭ��ִ��һ��ʱ������
	void Tick()
	{
		clockNow = clock();
		timeNow = timeMax - (clockNow - clockBegin) / 1000;
	}
};


//////////////////////////////////////////////////////
// �����ı������
class TextBox
{
private:
	int		m_x1, m_y1, m_x2, m_y2;		// �ı���λ��
	wchar_t	m_text[10];					// �û�������ַ���
	int		m_textlen;					// �û������ַ����ĳ���
	int		m_fps;						// ÿ����ö��ٴΣ������˹����˸�ٶȣ�

public:
	// ���캯��
	TextBox(int x1, int  y1, int x2, int y2, int fps)
	{
		m_x1 = x1;	m_y1 = y1;	m_x2 = x2;	m_y2 = y2;
		m_text[0] = '\0';
		m_textlen = 0;
		m_fps = fps;
	}

	// ����һ���ַ������Խ����˸�
	void Append(wchar_t c)
	{
		if (c != 8)
		{
			if (m_textlen < 9)
			{
				m_text[m_textlen] = c;
				m_text[m_textlen + 1] = '\0';
				m_textlen++;
			}
		}
		else
		{
			if (m_textlen > 0)
			{
				m_textlen--;
				m_text[m_textlen] = '\0';
			}
		}
	}

	// ����������ַ���ָ��
	wchar_t* Text()
	{
		return m_text;
	}

	// ���������ַ���
	void Empty()
	{
		m_textlen = 0;
		m_text[0] = '\0';
	}

	// �����ı���
	void Draw()
	{
		static int fps = 0;				// ͳ����ĸ����������λ��

		// �������������ʽ
		settextstyle(20, 0, L"Verdana");

		// ���߿�
		setlinecolor(WHITE);
		rectangle(m_x1, m_y1, m_x2, m_y2);

		// ����û�������ַ���
		outtextxy(m_x1 + 30, m_y1 + (m_y2 - m_y1 - 20) / 2, m_text);

		// ���ƹ�� 
		fps++;
		if (fps < (m_fps / 4))
		{
			setlinecolor(WHITE);
			int sx = m_x1 + 31 + textwidth(m_text);
			line(sx, m_y1 + (m_y2 - m_y1 - 20) / 2, sx, m_y1 + (m_y2 - m_y1 - 20) / 2 + 20);
		}
		else if (fps >(m_fps / 2))
			fps = 0;
	}
};


// Ŀ�굥�ʵĽṹ��
struct TARGET
{
	int x;
	int y;
	wchar_t* p;
};


// ��ȡ�û����루������Ӣ����ĸ���˸����
wchar_t Input()
{
	wchar_t c = 0;

	if (_kbhit())
	{
		c = _getwch();
		if (c >= 'A' && c <= 'Z')
			c = c + 32;
		else if (!(c >= 'a' && c <= 'z') && c != 8)
			c = 0;
	}
	return c;
}


// ��ʼ��Ŀ�굥��
void InitTarget(TARGET words[], int n)
{
	static wchar_t ss[28][10] = { L"main", L"include", L"void", L"while", L"true", L"char", L"break", L"else", L"false", L"switch",
		L"double", L"struct", L"long", L"case", L"enum", L"return", L"union", L"const", L"float", L"for",
		L"unsigned", L"continue", L"default", L"short", L"static", L"if", L"register", L"sizeof" };

	words[n].p = ss[rand() % 28];
	// �ж�������ɵ��ַ����Ƿ���ͬ(��ͬ���������ɵ���)
	while (words[n].p == words[(n + 1) % 3].p || words[n].p == words[(n + 2) % 3].p)
		words[n].p = ss[rand() % 28];

	settextstyle(20, 0, L"Verdana");
	words[n].x = rand() % (WIDTH - 100 - textwidth(words[n].p));
	words[n].y = -20;
}


// ��ָ��λ���������
void outintxy(int x, int y, const wchar_t* format, int n)
{
	wchar_t tmp[11];

	swprintf(tmp, 11, format, n);
	outtextxy(x, y, tmp);
}


// ��ָ��λ�����������
void outdoublexy(int x, int y, const wchar_t* format, double n)
{
	wchar_t tmp[11];

	swprintf(tmp, 11, format, n);
	outtextxy(x, y, tmp);
}


// �ж� src �Ƿ���ĳ�� word ��ǰ׺
bool isprefix(wchar_t src[], TARGET words[])
{
	for (int i = 0; i < 3; i++)
	{
		if (wcsstr(words[i].p, src) == words[i].p)
			return true;
	}
	return false;
}


//////////////////////////////////////////////////////
// ��Ϸ��ѭ��
void Game()
{
	TextBox textbox(10, HEIGHT - 40, WIDTH - 110, HEIGHT - 10, 50);	// �ı������
	TARGET words[3];												// ����� 3 ������
	GameClock gameclock(60);										// ��Ϸ��ʱ����

	wchar_t	key;					// �û������Ӣ��
	int		right = 0, wrong = 0;	// �û��������ȷ���������
	int		v = 0;					// �����ٶ�
	double	s;						// ��ȷ��

	// ������ɵ�����ַ���
	for (int n = 0; n < 3; n++)
	{
		InitTarget(words, n);
		words[n].y = -15 - n * 30;
	}

	// ��Ϸ��ѭ��
	while (gameclock.IsStop())
	{
		// ��ȡ����/////////////////////////////////////////////////////

		key = Input();


		// ����////////////////////////////////////////////////////////

		// ִ��һ����Ϸʱ��
		gameclock.Tick();

		// �ж��û�����
		if (key != 0)
		{
			textbox.Append(key);

			// �ж��û������Ƿ���ȷ��ͳ����ȷ������
			if (key != 8)
			{
				if (isprefix(textbox.Text(), words))
					right++;
				else
					wrong++;
			}

			// �ж�������ַ����Ƿ��������ַ������
			for (int i = 0; i < 3; i++)
				if (wcscmp(textbox.Text(), words[i].p) == 0)
				{
					InitTarget(words, i);
					textbox.Empty();
				}
		}

		// ��������ٶ�
		v = (gameclock.Elapse() == 0) ? 0 : right * 60 / gameclock.Elapse();

		// ���ʵ��䲢�����ж��Ƿ񳬳���Ļ���䷶Χ
		for (int n = 0; n < 3; n++)
		{
			words[n].y += 2;

			if (words[n].y > HEIGHT - 40)
				InitTarget(words, n);
		}

		// ������ȷ��
		if (wrong + right == 0)
			s = 0;
		else
			s = (double)right / (wrong + right) * 100;


		// ����////////////////////////////////////////////////////////

		// �����Ļ
		cleardevice();

		// ��������ַ�������ʾ��ʽ
		settextstyle(20, 0, L"Verdana");
		setbkmode(TRANSPARENT);
		settextcolor(WHITE);

		// ����ͳ������
		setfillcolor(RGB(50, 50, 50));
		solidrectangle(WIDTH - 100, 0, WIDTH - 2, HEIGHT);

		// �������ĵ���
		for (int n = 0; n < 3; n++)
			outtextxy(words[n].x, words[n].y, words[n].p);

		// ���� TextBox
		textbox.Draw();

		// �Ҳ���ȷ����ͳ��
		outtextxy(WIDTH - 90, 25, L"��ȷ��");
		outintxy(WIDTH - 80, 50, L"%d", right);

		// �Ҳ��������ͳ��
		outtextxy(WIDTH - 90, 85, L"������");
		outintxy(WIDTH - 80, 110, L"%d", wrong);

		// �Ҳ���ȷ�ʵļ���
		outtextxy(WIDTH - 90, 145, L"��ȷ��");
		outdoublexy(WIDTH - 80, 170, L"%.1f %%", s);

		// �Ҳ�����ٶȵļ���
		outtextxy(WIDTH - 90, 205, L"�����ٶ�");
		outintxy(WIDTH - 80, 230, L"%d kpm", v);

		// �Ҳ�����ĵ���ʱ
		outtextxy(WIDTH - 90, 265, L"����ʱ");
		outintxy(WIDTH - 80, 290, L"%d s", gameclock.Now());

		FlushBatchDraw();

		Sleep(20);
	}
}


// ������
int main()
{
	srand((unsigned)time(NULL));
	initgraph(WIDTH, HEIGHT);

	BeginBatchDraw();

	while (true)
	{
		Game();

		// ��ʾ��Ϸ����
		setfillcolor(RGB(200, 200, 200));
		solidrectangle(150, 200, 450, 300);
		settextcolor(BLACK);
		outtextxy(220, 225, L"���¿�ʼ�밴 �ո�");
		outtextxy(220, 255, L"�˳���Ϸ�밴 Esc");
		FlushBatchDraw();

		// ʵ�ְ��ո��������� ESC �˳�
		wchar_t ch = 0;
		while (ch != 27 && ch != ' ')
			ch = _getwch();

		if (ch == 27)
			break;
	}

	EndBatchDraw();

	closegraph();
	return 0;
}