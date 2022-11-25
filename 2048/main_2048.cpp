// �������ƣ�2048Game
// ���뻷����Visual C++ 2013, EasyX_20200315(beta)
// �������ߣ����ˡ <2928947343@qq.com> <QQ:2928947343>
// ����޸ģ�2021-1-25

#include <graphics.h>
#include <cstring>
#include <cstdio>
#include <ctime>
#include <conio.h>
using namespace std;

const COLORREF BGC = RGB(250, 248, 239);	// ���屳��ɫ����
int score, best, a[5][5], b[5][5];			// score Ϊ���ַ�����best Ϊ��ǰ��Ѽ�¼��a ����Ϊ���̣�b ����Ϊ a �ı���
bool mov[5][5];								// �����ϵĵ��Ƿ��ѱ��ƶ����������ظ��ƶ���

// �����ʼ��
void init()
{
	setbkcolor(BGC);
	setbkmode(TRANSPARENT);
	score = 0;
	memset(a, 0, sizeof(a));
	int x1 = rand() % 4 + 1, y1 = rand() % 4 + 1, x2 = rand() % 4 + 1, y2 = rand() % 4 + 1;	// �������������ʼ��
	a[x1][y1] = a[x2][y2] = 2;				// ��ʼ���ʼ��Ϊ 2
}


// ������Ϸ����
void drawmap()
{
	// ��ʼ������ͼ
	BeginBatchDraw();

	// ���ƽ�������
	cleardevice();
	settextcolor(RGB(119, 110, 101));
	settextstyle(50, 0, L"΢���ź�");
	outtextxy(10, 10, L"2048");
	settextstyle(20, 0, L"΢���ź�", 0, 0, 550, false, false, false);
	outtextxy(10, 65, L"Join the numbers and get to the 2048 tile!");

	setfillcolor(RGB(187, 173, 160));

	// ���Ƶ�ǰ����
	solidroundrect(200, 15, 290, 60, 5, 5);
	settextcolor(RGB(230, 220, 210));
	settextstyle(15, 0, L"΢���ź�", 0, 0, 600, false, false, false);
	outtextxy(230, 20, L"SCORE");
	wchar_t sc[10] = L"";
	swprintf_s(sc, L"%d", score);
	settextcolor(WHITE);
	settextstyle(25, 0, L"΢���ź�", 0, 0, 600, false, false, false);
	RECT r = { 200, 30, 290, 60 };
	drawtext(sc, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	// ������Ѽ�¼
	solidroundrect(295, 15, 385, 60, 5, 5);
	settextcolor(RGB(230, 220, 210));
	settextstyle(15, 0, L"΢���ź�", 0, 0, 600, false, false, false);
	outtextxy(330, 20, L"BEST");
	wchar_t bs[10] = L"";
	swprintf_s(bs, L"%d", best);
	settextcolor(WHITE);
	settextstyle(25, 0, L"΢���ź�", 0, 0, 600, false, false, false);
	r = { 295, 30, 385, 60 };
	drawtext(bs, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	// ������������
	solidroundrect(10, 90, 390, 470, 5, 5);
	settextstyle(23, 0, L"΢���ź�");
	settextcolor(WHITE);
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			if (a[i][j])			// �����λ��û�����֣��򲻻���
			{
				// �����ƹ�ϣ�ķ�����Ϊÿ�����ּ������Ӧ����ɫ
				setfillcolor(RGB((unsigned int)(BGC - 3 * (a[i][j] ^ 29)) % 256, (unsigned int)(BGC - 11 * (a[i][j] ^ 23)) % 256, (unsigned int)(BGC + 7 * (a[i][j] ^ 37)) % 256));
				solidroundrect(94 * j - 80, 94 * i, 94 * j + 10, 94 * i + 90, 5, 5);
				wchar_t num[10] = L"";
				swprintf_s(num, L"%d", a[i][j]);
				r = { 94 * j - 80, 94 * i, 94 * j + 10, 94 * i + 90 };
				drawtext(num, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}

	// ����������ͼ
	EndBatchDraw();
}

// ��Ҳ���
void move()
{
	memcpy(b, a, sizeof(a));			// �� a ������ b
	memset(mov, false, sizeof(mov));	// ��ʼ�� mov Ϊ false�����е��δ�ƶ���
	// ��ȡ�û�����
	char userkey = _getch();
	if (userkey == -32)
		userkey = -_getch();
	// �ƶ����̣��ƶ� a ���飩
	switch (userkey)
	{
		// ����
	case 'w':
	case 'W':
	case -72:
		for (int j = 1; j <= 4; j++)
			for (int i = 2; i <= 4; i++)
			{
				if (!a[i][j])continue;
				int k = i;
				while (!a[k - 1][j] && k >= 2)
				{
					a[k - 1][j] = a[k][j];
					a[k][j] = 0;
					k--;
				}
				if (a[k][j] == a[k - 1][j] && !mov[k - 1][j])
				{
					a[k - 1][j] = 2 * a[k][j];
					a[k][j] = 0;
					mov[k - 1][j] = true;
					score += a[k - 1][j];
				}
			}
		break;
		// ����
	case 's':
	case 'S':
	case -80:
		for (int j = 1; j <= 4; j++)
			for (int i = 3; i >= 1; i--)
			{
				if (!a[i][j])continue;
				int k = i;
				while (!a[k + 1][j] && k <= 3)
				{
					a[k + 1][j] = a[k][j];
					a[k][j] = 0;
					k++;
				}
				if (a[k][j] == a[k + 1][j] && !mov[k + 1][j])
				{
					a[k + 1][j] = 2 * a[k][j];
					a[k][j] = 0;
					mov[k + 1][j] = true;
					score += a[k + 1][j];
				}
			}
		break;
		// ����
	case 'a':
	case 'A':
	case -75:
		for (int i = 1; i <= 4; i++)
			for (int j = 2; j <= 4; j++)
			{
				if (!a[i][j])continue;
				int k = j;
				while (!a[i][k - 1] && k >= 2)
				{
					a[i][k - 1] = a[i][k];
					a[i][k] = 0;
					k--;
				}
				if (a[i][k] == a[i][k - 1] && !mov[i][k - 1])
				{
					a[i][k - 1] = 2 * a[i][k];
					a[i][k] = 0;
					mov[i][k - 1] = true;
					score += a[i][k - 1];
				}
			}
		break;
		// ����
	case 'd':
	case 'D':
	case -77:
		for (int i = 1; i <= 4; i++)
			for (int j = 3; j >= 1; j--)
			{
				if (!a[i][j])continue;
				int k = j;
				while (!a[i][k + 1] && k <= 3)
				{
					a[i][k + 1] = a[i][k];
					a[i][k] = 0;
					k++;
				}
				if (a[i][k] == a[i][k + 1] && !mov[i][k + 1])
				{
					a[i][k + 1] = 2 * a[i][k];
					a[i][k] = 0;
					mov[i][k + 1] = true;
					score += a[i][k + 1];
				}
			}
		break;
	}
	bool change = false;				// �жϾ����ƶ��������Ƿ�ı�
	// �Ƚϵ�ǰ�������ƶ�ǰ��b ���飩����
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			if (a[i][j] != b[i][j])
			{
				change = true;
				break;
			}
	if (!change)return;					// �������û�иı䣬�˳�
	// ����һ�������֣��Ҳ������������غϣ�
	int x, y;
	do
	{
		x = rand() % 4 + 1;
		y = rand() % 4 + 1;
	} while (a[x][y]);
	// �� 1/6 �ļ�����������Ϊ 4�����������������Ϊ 2
	int n = rand() % 6;
	if (n == 5)a[x][y] = 4;
	else a[x][y] = 2;
	// ������Ѽ�¼
	best = max(best, score);
}

// �ж���Ϸ����
bool gameover()
{
	// ��������һ��λ�ã���λ��Ϊ�� �� ������λ���ϵ��������λ����������ȣ�˵���ɼ����ƶ�����Ϸ�ɼ�����
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			if (!a[i][j] || a[i][j] == a[i + 1][j] || a[i][j] == a[i - 1][j] || a[i][j] == a[i][j + 1] || a[i][j] == a[i][j - 1])return false;
	// ������Ϸ����
	return true;
}

// �ж�ʤ��
bool win()
{
	// ������һ��λ�ôﵽ 2048����ʤ��
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			if (a[i][j] == 2048)return true;
	return false;
}

int main()
{
	bool ctn = true;					// ��ֵ�����Ƿ��ؿ��¾�
	initgraph(400, 480);				// ��ʼ��ͼ�ν���
	srand((unsigned)time(NULL));
	while (ctn)
	{
		init();							// �µ�һ�֣������ʼ��
		drawmap();						// ���ƽ���
		int endmode = 0;				// ������ʽ��1 ����ʤ����2 ����ʧ��
		while (1)
		{
			move();						// ��Ҳ���
			drawmap();					// ���ƽ���
			if (win())					// ʤ��
			{
				endmode = 1;
				break;
			}
			if (gameover())				// ʧ��
			{
				endmode = 2;
				break;
			}
		}
		int t;							// ��ȡ�û�ѡ��İ�ť
		if (endmode == 1)				// ʤ��
			t = MessageBox(0, L"You win!\n����һ�֣�", L"����", MB_OKCANCEL);
		if (endmode == 2)				// ʧ��
			t = MessageBox(0, L"Game over!\n����һ�֣�", L"����", MB_OKCANCEL);
		if (t == IDCANCEL)ctn = false;	// ���û�ѡ�� ȡ���������¿���
	}
	closegraph();						// �ر�ͼ�ν���
	return 0;
}