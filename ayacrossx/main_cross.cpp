/////////////////////////////////////////////////////////
// �������ƣ�AyaCrossX��ʮ��������Ϸ��
// ���뻷����Visual C++ 6.0 / 2012��EasyX 2013˪����
// ��    �ߣ�ls9512 <http://www.baidu.com/p/ls9512>
// ����޸ģ�2013-11-2
//

//ϵͳ������
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <math.h>
#include <time.h>
//EasyXͼ�ο�
#include <graphics.h>


//////////////////////////////������ �궨����� //////////////////////////////
#define WIN_WIDTH		600					//��Ļ���
#define WIN_HEIGHT		430					//��Ļ�߶�
#define WIN_BLANKTOP	45					//��Ļ�����ձ�
#define WIN_BLANK		25					//��Ļ��Ե����
#define G_BN			20					//�����������
#define G_BM			12					//������������
#define G_BW			20					//������
#define G_BS			8					//���������
#define G_BSELECT		3					//����ѡ�д�С
#define G_FLOATW		4					//ѡ�и�����С
#define G_BDWO			1					//��ʧ��ʼ��С
#define G_BDW			6					//��ʧ��С
#define G_CN			10					//��ɫ����
#define G_BUL			25					//���������̶�
#define C_BLOCKPANEL	RGB(255, 255, 221)	//�װ���ɫ
#define C_HPBAR			RGB(255, 170, 255)	//HP����ɫ


//////////////////////////////���������ݽṹ����//////////////////////////////
//����ṹ
struct Block{
	COLORREF color;				//��ɫ
	float	 FLOAT;				//������С
	float	 DIS;				//�����ӳ�
	bool	 isDIS;				//�Ƿ���ʧ��
	bool	 isClick;			//�Ƿ񱻵��
};

//��ṹ
struct Point{
	int x;
	int y;
};

//���νṹ
struct Rect{
	int x;
	int y;
	int w;
	int h;
};


//////////////////////////////������  ȫ�ֱ���  //////////////////////////////
int GamePhase = 0;				//��Ϸ�׶� 0 ׼�� 1 ���� 2 ���� 3 ��������
int isShowFPS = 0;				//�Ƿ���ʾ֡��
int mouseX;						//���λ������X
int mouseY;						//���λ������Y
int time_max;					//����Ϸʱ��
int time_now;					//��ǰʣ��ʱ��
int level;						//�ȼ�
int score;						//����
bool isMouseDown;				//��갴��
Block block[G_BM][G_BN];		//��������
COLORREF Defcolor[G_CN];		//��ѡ��ɫ����


//////////////////////////////������  ��������  //////////////////////////////
float	GetFPS();						//��ȡ֡��
void	HpSleep(DWORD ms);				//������ʱ
Point	GetMouseLocal(int x, int y);	//��ȡ�����������
void	AddBlock(int n);				//���ָ��������δѡ�з���
void	Init();							//��ʼ��
void	DisCheck(int x, int y);			//���ָ��λ�õ�����
int		CountBlock();					//ͳ�Ʒ������
void	Manager();						//�߼�����
void	Draw();							//��ͼ����
void	StartDraw();					//��Ϸ��ʼ��ͼ
void	GamingDraw();					//��Ϸ�����л�ͼ
void	EndDraw();						//��Ϸ������ͼ
void	HelpDraw();						//��Ϸ������ͼ
void	EndFrame();						//֡��������
bool	IsInRect(int x, int y, Rect r);	//�Ƿ��ھ�����


//////////////////////////////�����Ǹ������ܺ���//////////////////////////////
//���㻭��FPS(ÿ��֡��)
float GetFPS()
{
#define FPS_COUNT 8
	static int i = 0;
	static DWORD oldTime = GetTickCount();
	static float fps;
	if (i > FPS_COUNT)
	{
		i = 0;
		int newTime = GetTickCount();
		int elapsedTime = newTime - oldTime;
		fps = FPS_COUNT / (elapsedTime / 1000.0f);
		oldTime = newTime;
	}
	i++;
	return fps;
}

//������ʱ
void HpSleep(DWORD ms)
{
	static clock_t oldclock = clock();		// ��̬��������¼��һ�� tick

	oldclock += ms * CLOCKS_PER_SEC / 1000;	// ���� tick

	if (clock() > oldclock)					// ����Ѿ���ʱ��������ʱ
		oldclock = clock();
	else
		while (clock() < oldclock)			// ��ʱ
			Sleep(1);						// �ͷ� CPU ����Ȩ������ CPU ռ����
}

//��ȡ���ѡ�е�
Point GetMouseLocal(int x, int y)
{
	Point p;
	x = (x - WIN_BLANK) / (G_BW + G_BS);
	y = (y - WIN_BLANK - WIN_BLANKTOP) / (G_BW + G_BS);
	if (x < 0 || x >= G_BN) x = -1;
	if (y < 0 || y >= G_BM) y = -1;
	p.x = x;
	p.y = y;
	return p;
}

//�Ƿ��ھ�����
bool IsInRect(int x, int y, Rect r)
{
	return ((x >= r.x && x <= r.w) && (y >= r.y && y <= r.h));
}

//����ƶ�������δѡ�з���
void AddBlock(int n)
{
	//������ɷ���
	int num = 0, x1, y1, x2, y2;
	int num_max = n;
	while (num < num_max)
	{
		x1 = rand() % G_BN;
		y1 = rand() % G_BM;
		x2 = rand() % G_BN;
		y2 = rand() % G_BM;
		if (block[y1][x1].isClick && block[y2][x2].isClick)
		{
			COLORREF color = Defcolor[rand() % G_CN];
			block[y1][x1].color = color;
			block[y1][x1].isClick = false;
			block[y1][x1].FLOAT = 0;
			block[y1][x1].DIS = 0;
			block[y1][x1].isDIS = false;
			block[y2][x2].color = color;
			block[y2][x2].isClick = false;
			block[y2][x2].FLOAT = 0;
			block[y2][x2].DIS = 0;
			block[y2][x2].isDIS = false;
			num += 2;
		}
	}
}

//��ʼ��
void Init()
{
	//Ԥ����ɫ
	Defcolor[0] = RGB(255, 153, 0);
	Defcolor[1] = RGB(204, 102, 0);
	Defcolor[2] = RGB(27, 118, 255);
	Defcolor[3] = RGB(255, 136, 255);
	Defcolor[4] = RGB(204, 204, 102);
	Defcolor[5] = RGB(104, 204, 204);
	Defcolor[6] = RGB(255, 125, 125);
	Defcolor[7] = RGB(204, 104, 204);
	Defcolor[8] = RGB(190, 190, 190);
	Defcolor[9] = RGB(0, 204, 0);

	//��ʼ��ʱ��
	time_max = 10000;
	time_now = 10000;

	//��ʼ������
	score = 0;

	//��ȫѡ��
	for (int i = 0; i < G_BM; i++)
	{
		for (int j = 0; j < G_BN; j++)
		{
			block[i][j].isClick = true;
			block[i][j].FLOAT = 0;
			block[i][j].DIS = 0;
		}
	}

	//��ӷ���
	AddBlock(G_BN * G_BM * 2 / 3);

	//��������Ϣ����
	FlushMouseMsgBuffer();
}

//ͳ�Ʒ������
int CountBlock()
{
	int n = 0;
	for (int i = 0; i < G_BN; i++)
	{
		for (int j = 0; j < G_BM; j++)
		{
			if (!block[j][i].isClick) n++;
		}
	}
	return n;
}

//���ָ��λ������
void DisCheck(int x, int y)
{
	//��¼�������ķ���
	Block* b[4];
	int i, j, n = 0;

	//����
	for (i = x; i >= 0; i--)
	{
		if (!block[y][i].isClick)
		{
			b[n] = &block[y][i];
			n++;
			break;
		}
	}

	//����
	for (i = x; i < G_BN; i++)
	{
		if (!block[y][i].isClick)
		{
			b[n] = &block[y][i];
			n++;
			break;
		}
	}

	//����
	for (j = y; j >= 0; j--)
	{
		if (!block[j][x].isClick)
		{
			b[n] = &block[j][x];
			n++;
			break;
		}
	}

	//����
	for (j = y; j < G_BM; j++)
	{
		if (!block[j][x].isClick)
		{
			b[n] = &block[j][x];
			n++;
			break;
		}
	}

	//����
	for (i = 0; i < n; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			if (b[i]->color == b[j]->color)
			{
				if (!b[i]->isDIS){
					b[i]->DIS = G_BDWO;
					b[i]->isDIS = true;
				}
				if (!b[j]->isDIS){
					b[j]->DIS = G_BDWO;
					b[j]->isDIS = true;
				}
			}
		}
	}
	isMouseDown = false;
}

//�߼�����
void Manager()
{
	//�������Ϸ��
	if (GamePhase == 1)
	{
		Point p = GetMouseLocal(mouseX, mouseY);
		int x = p.x, y = p.y;
		//���ѡ��
		if (p.x != -1 && p.y != -1)
		{
			//�������
			if (isMouseDown && block[y][x].isClick)
			{
				//�����������
				DisCheck(x, y);
			}
		}
		//����·��������������·���
		if (CountBlock() < G_BN * G_BM / 3)
		{
			AddBlock((rand() % 15 + 15) * 2);
			//ʱ��ָ�
			time_now += 500;
			if (time_now > time_max) time_now = time_max;
		}
	}
}

//��ʼ��ͼ
void StartDraw()
{
	settextstyle(52, 30, _T("Impact"));
	//����
	settextcolor(RGB(255, 17, 102));
	outtextxy(143, 93, _T("AyaCrossX"));
	settextcolor(RGB(255, 153, 238));
	outtextxy(140, 90, _T("AyaCrossX"));
	//�汾
	settextstyle(22, 10, _T("Verdana"));
	settextcolor(RGB(255, 51, 68));
	outtextxy(340, 153, _T("v0.91 By:ls9512"));
	//��ʼ��Ϸ��ť
	Rect r;
	r.x = 240;
	r.y = 220;
	r.w = r.x + 125;
	r.h = r.y + 35;
	setlinecolor(RGB(255, 17, 102));
	if (IsInRect(mouseX, mouseY, r))
	{
		setfillcolor(RGB(255, 187, 119));
		//��ʼ��Ϸ������Ӧ
		if (isMouseDown)
		{
			Init();
			GamePhase = 1;
			isMouseDown = false;
		}
	}
	else
		setfillcolor(RGB(255, 255, 204));
	fillrectangle(r.x, r.y, r.w, r.h);
	settextstyle(25, 10, _T("Verdana"));
	settextcolor(RGB(255, 51, 68));
	outtextxy(r.x + 5, r.y + 5, _T("PLAY GAME"));

	//������Ϸ��ť
	r.x = 240;
	r.y = 270;
	r.w = r.x + 125;
	r.h = r.y + 35;
	setlinecolor(RGB(255, 17, 102));
	if (IsInRect(mouseX, mouseY, r))
	{
		setfillcolor(RGB(255, 187, 119));
		//����������Ӧ
		if (isMouseDown) GamePhase = 3;
	}
	else
		setfillcolor(RGB(255, 255, 204));
	fillrectangle(r.x, r.y, r.w, r.h);
	settextstyle(25, 10, _T("Verdana"));
	settextcolor(RGB(255, 51, 68));
	outtextxy(r.x + 5, r.y + 5, _T("HELP INFO"));
	//�˳���Ϸ��ť
	r.x = 240;
	r.y = 320;
	r.w = r.x + 125;
	r.h = r.y + 35;
	setlinecolor(RGB(255, 17, 102));
	if (IsInRect(mouseX, mouseY, r))
	{
		setfillcolor(RGB(255, 187, 119));
		//�˳�������Ӧ
		if (isMouseDown) exit(0);
	}
	else
		setfillcolor(RGB(255, 255, 204));
	fillrectangle(r.x, r.y, r.w, r.h);
	settextstyle(25, 10, _T("Verdana"));
	settextcolor(RGB(255, 51, 68));
	outtextxy(r.x + 5, r.y + 5, _T("EXIT GAME"));
	//˵��
	settextstyle(16, 5, _T("Verdana"));
	settextcolor(RGB(255, 51, 68));
	outtextxy(175, 400, _T("Programing By VC++ & EasyX     Date:2013.11.01"));
}

//��Ϸ�л�ͼ
void GameingDraw()
{
	int x, y;
	COLORREF c, c2;

	//ʱ����
	x = WIN_BLANK;
	y = WIN_BLANK;
	int HPBARW = (G_BW + G_BS) * G_BN - 200;
	setlinecolor(RGB(255, 17, 255));
	setfillcolor(WHITE);
	fillrectangle(x, y, x + HPBARW, y + 10);
	setfillcolor(C_HPBAR);
	fillrectangle(x, y, x + (int)(HPBARW * (1.0 * time_now / time_max)), y + 10);

	//�װ�
	setlinecolor(RGB(255, 25, 22));
	setfillcolor(C_BLOCKPANEL);
	x = WIN_BLANK - G_BS;
	y = WIN_BLANK + WIN_BLANKTOP - G_BS;
	fillrectangle(x, y, x + (G_BW + G_BS) * G_BN + G_BS, y + (G_BW + G_BS) * G_BM + G_BS);

	//������
	for (int i = 0; i < G_BM; i++)
	{
		for (int j = 0; j < G_BN; j++)
		{
			if (!block[i][j].isClick)
			{
				c = block[i][j].color;
				c = RGB(GetRValue(c) - (BYTE)G_BUL, GetGValue(c) - (BYTE)G_BUL, GetBValue(c) - (BYTE)G_BUL);
				int fw = (int)block[i][j].FLOAT;
				int fd = (int)block[i][j].DIS;
				setlinecolor(c);
				setfillcolor(block[i][j].color);
				x = j * (G_BW + G_BS) + WIN_BLANK - fw - fd;
				y = i * (G_BW + G_BS) + WIN_BLANK + WIN_BLANKTOP - fw - fd;
				fillrectangle(x, y, x + G_BW + 2 * (fw + fd), y + G_BW + 2 * (fw + fd));
				//��������
				if (block[i][j].FLOAT > 0) block[i][j].FLOAT -= 0.4f;
				//��ʧ�ӳ�
				if (block[i][j].isDIS)
				{
					if (block[i][j].DIS < G_BDW)
						block[i][j].DIS += 0.4f;
					else
					{
						//����
						block[i][j].isClick = true;
						//�ӷ�
						score += 100;
						time_now += 25;
						if (time_now > time_max) time_now = time_max;
					}
				}
			}
		}
	}

	//��ȡ���λ��
	Point p = GetMouseLocal(mouseX, mouseY);

	//���������
	if (p.x != -1 && p.y != -1)
	{
		c = RED;
		x = p.x, y = p.y;
		int fw;
		if (block[y][x].isClick) fw = 0;
		else fw = (int)block[y][x].FLOAT;
		x = x * (G_BW + G_BS) + WIN_BLANK - G_BSELECT - fw;
		y = y * (G_BW + G_BS) + WIN_BLANK + WIN_BLANKTOP - G_BSELECT - fw;
		//ѡ�з������
		if (!block[p.y][p.x].isClick)
		{
			//�ø�����С
			block[p.y][p.x].FLOAT = G_FLOATW;
			c2 = block[p.y][p.x].color;
		}
		else
		{
			c2 = C_BLOCKPANEL;
		}
		setlinecolor(c);
		setfillcolor(c2);
		fillrectangle(x, y, x + G_BW + 2 * (G_BSELECT + fw), y + G_BW + 2 * (G_BSELECT + fw));
	}

	//��������
	settextstyle(25, 10, _T("Verdana"));
	settextcolor(RGB(155, 51, 68));
	TCHAR b[10];
#if _MSC_VER > 1200
	_stprintf_s(b, _T("%d"), score);
#else
	_stprintf(b, _T("%d"), score);
#endif
	outtextxy(390, 15, _T("����:"));
	settextcolor(RGB(255, 51, 68));
	outtextxy(440, 16, b);
}

//��Ϸ������ͼ
void EndDraw()
{
	//����
	settextstyle(52, 30, _T("Impact"));
	settextcolor(RGB(255, 17, 102));
	outtextxy(143, 103, _T("GAME OVER"));
	settextcolor(RGB(215, 193, 238));
	outtextxy(140, 100, _T("GAME OVER"));

	//�汾
	settextstyle(34, 12, _T("Verdana"));
	settextcolor(RGB(255, 51, 68));
	TCHAR b[10];
#if _MSC_VER > 1200
	_stprintf_s(b, _T("%d"), score);
#else
	_stprintf(b, _T("%d"), score);
#endif
	outtextxy(232, 173, _T("����:"));
	outtextxy(290, 173, b);

	//���¿�ʼ��Ϸ��ť
	Rect r;
	r.x = 240;
	r.y = 240;
	r.w = r.x + 125;
	r.h = r.y + 35;
	setlinecolor(RGB(255, 17, 102));
	if (IsInRect(mouseX, mouseY, r))
	{
		setfillcolor(RGB(255, 187, 119));
		//��ʼ��Ϸ������Ӧ
		if (isMouseDown)
		{
			Init();
			GamePhase = 1;
		}
	}
	else
		setfillcolor(RGB(255, 255, 204));
	fillrectangle(r.x, r.y, r.w, r.h);
	settextstyle(25, 10, _T("Verdana"));
	settextcolor(RGB(255, 51, 68));
	outtextxy(r.x + 5, r.y + 5, _T("   REPLAY"));

	//�˳�
	r.x = 240;
	r.y = 290;
	r.w = r.x + 125;
	r.h = r.y + 35;
	setlinecolor(RGB(255, 17, 102));
	if (IsInRect(mouseX, mouseY, r))
	{
		setfillcolor(RGB(255, 187, 119));
		//�˳�������Ӧ
		if (isMouseDown) exit(0);
	}
	else
		setfillcolor(RGB(255, 255, 204));
	fillrectangle(r.x, r.y, r.w, r.h);
	settextstyle(25, 10, _T("Verdana"));
	settextcolor(RGB(255, 51, 68));
	outtextxy(r.x + 5, r.y + 5, _T("EXIT GAME"));
}

//��Ϸ������ͼ
void HelpDraw()
{
	//����
	settextstyle(52, 30, _T("Impact"));
	settextcolor(RGB(255, 17, 152));
	outtextxy(233, 33, _T("HELP"));
	settextcolor(RGB(215, 193, 238));
	outtextxy(230, 30, _T("HELP"));

	//�װ�
	setlinecolor(RGB(255, 17, 204));
	setfillcolor(RGB(255, 221, 255));
	fillrectangle(60, 100, 550, 280);

	//�汾
	settextstyle(18, 10, _T("����"));
	settextcolor(RGB(245, 126, 92));
	outtextxy(70, 110, _T("ʮ��������һ���������С��Ϸ��"));
	outtextxy(70, 145, _T("���淨��"));
	outtextxy(80, 170, _T("1.����հ״�,���ں���ʮ������ͬɫ����ᱻ������"));
	outtextxy(80, 195, _T("2.����������ۼӵ÷�,���ָ�һ������ʱ��."));
	outtextxy(80, 220, _T("3.������������ĳ��ֵ������·��鲢�ظ�ʱ��."));
	outtextxy(80, 245, _T("4.ʱ��ľ�ʱ����Ϸ����."));

	//����
	Rect r;
	r.x = 240;
	r.y = 360;
	r.w = r.x + 125;
	r.h = r.y + 35;
	setlinecolor(RGB(255, 17, 102));
	if (IsInRect(mouseX, mouseY, r))
	{
		setfillcolor(RGB(255, 187, 119));
		//���ذ�����Ӧ
		if (isMouseDown) GamePhase = 0;
	}
	else
		setfillcolor(RGB(255, 255, 204));
	fillrectangle(r.x, r.y, r.w, r.h);
	settextstyle(25, 9, _T("Verdana"));
	settextcolor(RGB(255, 51, 68));
	outtextxy(r.x + 5, r.y + 5, _T("BACK MENU"));
}

//���֡��
void DrawFPS()
{
	//���֡��
	if (isShowFPS)
	{
		settextcolor(RED);
		settextstyle(14, 0, _T("����"));
		TCHAR s[5];
#if _MSC_VER > 1200
		_stprintf_s(s, _T("%.1f"), GetFPS());
#else
		_stprintf(s, _T("%.1f"), GetFPS());
#endif
		outtextxy(0, 0, s);
	}
}

//��ͼ
void Draw()
{
	//����
	setlinecolor(WHITE);
	setfillcolor(WHITE);
	fillrectangle(0, 0, WIN_WIDTH, WIN_HEIGHT);
	switch (GamePhase)
	{
	case 0:	StartDraw();	break;
	case 1:	GameingDraw();	break;
	case 2:	EndDraw();		break;
	case 3:	HelpDraw();		break;
	}
	DrawFPS();
}

//֡��������
void EndFrame()
{
	time_now -= 2;
	//��Ϸ����
	if (time_now <= 0 && GamePhase == 1)
	{
		GamePhase = 2;
	}
}

//����ں���
int main()
{
	//�����������
	srand((unsigned)time(NULL));
	//��ʼ���豸������ͼƬ
	initgraph(WIN_WIDTH, WIN_HEIGHT);
	//���ô��ڱ���
	SetWindowText(GetHWnd(), _T("AyaCrossX v0.91 By:ls9512"));
	cleardevice();
	//���ú�ɫ����
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	//����˫����,��ֹ����
	BeginBatchDraw();
	// �����Ϣ����
	MOUSEMSG mmsg;

	//��ʼ��
	Init();

	while (true)
	{
		//���������Ϣ
		while (MouseHit())
		{
			mmsg = GetMouseMsg();
			switch (mmsg.uMsg)
			{
			case WM_MOUSEMOVE:		mouseX = mmsg.x; mouseY = mmsg.y;	break;
			case WM_LBUTTONDOWN:	isMouseDown = true;					break;
			case WM_LBUTTONUP:		isMouseDown = false;				break;
			}
		}
		//�߼�����
		Manager();
		//��ͼ����
		Draw();
		//��ʾ����Ļ�������
		FlushBatchDraw();
		//֡��������
		EndFrame();
		//�ӳ�,֡������
		HpSleep(18);
	}

	// �ر�
	EndBatchDraw();
	closegraph();
	return 0;
}