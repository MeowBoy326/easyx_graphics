#include <graphics.h>
#include <iostream>
#include <time.h>
#include<stdlib.h>
#include<stdio.h>
#include <conio.h>
#include<algorithm>
#include<math.h>
#include <map>

using namespace std;

#define WINDOWS_X 1200	//���ڴ�СX
#define WINDOWS_Y 800	//���ڴ�СY

#define PX 280			//����ƫ����X
#define PY 80			//����ƫ����Y
#define BBLACK 80		//�ո��С

#define CHESSSIZE 25	//���Ӵ�С
#define SIZE 8			//���̸���

#define ESC 27
#define ESCEXIT (_kbhit()&&_getch()==ESC)

#pragma comment (lib,"ws2_32.lib")						// ���� Windows Multimedia API
#pragma comment(lib,"Winmm.lib")

const int black = 1;	//����
const int white = 0;	//����

int mapp[SIZE][SIZE];		//���̾���洢
const int MOVE[8][2] = { { -1, 0 },{ 1, 0 },{ 0, -1 },{ 0, 1 },{ -1, -1 },{ 1, -1 },{ 1, 1 },{ -1, 1 } };	//��λ
const int MAPPOINTCOUNT[8][8] =												//���̸���Ȩֵ��ֵ
{
	{90,-60,10,10,10,10,-60,90},
	{-60,-80,5,5,5,5,-80,-60},
	{10,5,1,1,1,1,5,10},
	{10,5,1,1,1,1,5,10},
	{10,5,1,1,1,1,5,10},
	{10,5,1,1,1,1,5,10},
	{-60,-80,5,5,5,5,-80,-60},
	{90,-60,10,10,10,10,-60,90}
};
IMAGE MAPIMAGE[SIZE][SIZE];
IMAGE COUNT[2];

int expect[SIZE][SIZE];

SOCKET sockSer;
SOCKET sockConn;

bool TOINTERNET;						//�Ƿ�����������
int MYCOLOR;							//�ҵ���ɫ 1��ɫ 0��ɫ -1����
int NOWCOLOR;							//��ǰִ����ɫ
bool TIANEYES;							//����ģʽ

void gameStart();						//��������
class POINT2
{
public:
	void WIN2MAP(POINT2 &MAP)			//��������������ӳ���ϵ
	{
		MAP.x = (x - PX) / BBLACK;
		MAP.y = (y - PY) / BBLACK;
	}
	void MAP2WIN(POINT2 &WIN)			//�������������̵�ӳ���ϵ
	{
		WIN.x = PX + x*BBLACK + BBLACK / 2;
		WIN.y = PY + y*BBLACK + BBLACK / 2;
	}
	void INIT(int x, int y)				//����Ԫ��
	{
		this->x = x;
		this->y = y;
	}
	void ADD(int x, int y)				//�����
	{
		this->x += x;
		this->y += y;
	}
	int MAP2WINX()
	{
		return PX + x*BBLACK + BBLACK / 2;
	}
	int MAP2WINY()
	{
		return PY + y*BBLACK + BBLACK / 2;
	}
	int WIN2MAPX()
	{
		return (x - PX) / BBLACK;
	}
	int WIN2MAPY()
	{
		return (y - PY) / BBLACK;
	}
	int x, y;
};

POINT2 LASTCH;								//��һ�����ӷ�λ

void mappadd(int x, int y, int color,int MAP[SIZE][SIZE])		//���ͼ���������
{
	POINT2 WINDOWS2, MAP2;
	WINDOWS2.INIT(x, y);
	WINDOWS2.WIN2MAP(MAP2);
	MAP[MAP2.x][MAP2.y] = color ? 1 : -1;
}

void printcircle(int x, int y, int color,int MAP[SIZE][SIZE])				//��������
{
	mappadd(x, y, color,MAP);
																			//ע����Ϊ��Ч��
	/*POINT2 X;
	X.INIT(x, y);
	X.WIN2MAP(X);
	POINT2 ZS, YS, ZX, YX, ZZS, ZZX, ZYS, ZYX;
	ZS.INIT(x - BBLACK / 2+1, y - BBLACK / 2+1);
	ZX.INIT(x - BBLACK / 2+1, y + BBLACK / 2 - 1);
	YS.INIT(x + BBLACK / 2-1, y - BBLACK / 2+1);
	YX.INIT(x + BBLACK / 2 - 1, y + BBLACK / 2 - 1);
	ZZS.INIT(x, y - BBLACK / 2+1);
	ZZX.INIT(x, y + BBLACK / 2 - 1);
	ZYS = ZZS, ZYX = ZZX;

	for (int i = 0; i < BBLACK; i++)
	{
	POINT points1[4] = { { ZS.x,ZS.y },{ ZZS.x,ZZS.y },{ ZZX.x,ZZX.y },{ ZX.x,ZX.y }};			//�����
	POINT points2[4] = { { YS.x,YS.y },{ ZYS.x,ZYS.y },{ ZYX.x,ZYX.y },{ YX.x,YX.y }};			//��һ��
	setfillcolor(LIGHTRED);																		//��ת������ɫ
	putimage(ZS.x - 1, ZS.y - 1, &MAPIMAGE[X.x][X.y]);											//ʹ��ԭͼ����
	solidpolygon(points1, 4);
	solidpolygon(points2, 4);
	if (ZZS.x <= x - BBLACK / 2 + 1)break;
	ZZS.x-=3;
	++ZZS.y;
	++ZYS.y;
	ZYS.x += 3;
	--ZYX.y;
	ZYX.x += 3;
	ZZX.x-=3;
	--ZZX.y;

	Sleep(2);
	}*/
	setfillcolor(color ? BLACK : WHITE);					//���м�Ŵ�任
	for (int i = 0; i <= CHESSSIZE; ++i)
	{
		solidcircle(x, y, i);
		Sleep(1);
	}
}

void init()															//��������
{
	memset(mapp, 0, sizeof(mapp));									//��ʼ��
	memset(expect, 0, sizeof(expect));
	TIANEYES = false;												//�ر�����ģʽ
	MYCOLOR = -1;
	LASTCH.INIT(0, 0);

	settextstyle(15, 0, "����");
	loadimage(NULL, "1.jpg");										//����ͼƬ
	for (int x = PX; x < PX + BBLACK*(SIZE + 1); x += BBLACK)		//�������� ����
	{
		if ((x / BBLACK % 2) == 0)setlinecolor(BLACK);
		else setlinecolor(RED);
		line(x, PY, x, PY + BBLACK*SIZE);
	}
	for (int y = PY; y <PY + BBLACK*(SIZE + 1); y += BBLACK)		//�������� ����
	{
		if (y / BBLACK % 2 == 0)setlinecolor(BLACK);
		else setlinecolor(RED);
		line(PX, y, PX + BBLACK*SIZE, y);
	}
	for (int i = PX; i <= PX + BBLACK*SIZE; i += BBLACK)			//��ȡÿ����ͼƬ������ͼƬָ����
	{
		for (int j = PY; j <= PY + BBLACK*SIZE; j += BBLACK)
		{
			POINT2 DATA;
			DATA.INIT(i, j);
			DATA.WIN2MAP(DATA);
			getimage(&MAPIMAGE[DATA.x][DATA.y], i, j, BBLACK, BBLACK);
		}
	}

	printcircle(PX + (SIZE / 2 - 1)* BBLACK + BBLACK / 2, PY + (SIZE / 2 - 1) * BBLACK + BBLACK / 2, white,mapp);		//��ʼ����ö����
	printcircle(PX + (SIZE / 2 - 1) * BBLACK + BBLACK / 2, PY + (SIZE / 2) * BBLACK + BBLACK / 2, black, mapp);
	printcircle(PX + (SIZE / 2) * BBLACK + BBLACK / 2, PY + (SIZE / 2) * BBLACK + BBLACK / 2, white, mapp);
	printcircle(PX + (SIZE / 2) * BBLACK + BBLACK / 2, PY + (SIZE / 2 - 1) * BBLACK + BBLACK / 2, black, mapp);


	getimage(COUNT, WINDOWS_X / 30, WINDOWS_Y - WINDOWS_Y / 6, 230, 40);											//�ɼ��������򱳾�ͼƬָ��
	getimage(COUNT + 1, WINDOWS_X - WINDOWS_X / 5, WINDOWS_Y - WINDOWS_Y / 6, 230, 40);

	LOGFONT f;
	gettextstyle(&f);												// ��ȡ������ʽ
	f.lfHeight = 35;												// ��������߶�
	strcpy_s(f.lfFaceName, _T("����Ҧ��"));							// ��������
	f.lfQuality = ANTIALIASED_QUALITY;								// �������Ч��Ϊ�����  
	settextstyle(&f);												// ����������ʽ

	settextcolor(WHITE);
	outtextxy(BBLACK / 4, BBLACK / 2, "����ִ��");
	outtextxy(BBLACK / 4, BBLACK / 4 + BBLACK, "��ǰִ��");
}

int Judge(int x, int y, int color,int MAP[SIZE][SIZE])									//Ԥ�е�ǰλ���ܷ�����
{
	if (MAP[x][y])return 0;																//�����ǰλ���Ѿ�������
	int me = color ? 1 : -1;															//׼������������ɫ
	POINT2 star;
	int count = 0, flag;																//countΪ��λ�ÿ���ת���������Ӹ���
	for (int i = 0; i < SIZE; ++i)														//����
	{
		flag = 0;
		star.INIT(x + MOVE[i][0], y + MOVE[i][1]);
		while (star.x >= 0 && star.x < SIZE&&star.y >= 0 && star.y < SIZE&&MAP[star.x][star.y])
		{
			if (MAP[star.x][star.y] == -me)flag++;
			else
			{
				count += flag;
				break;
			}
			star.ADD(MOVE[i][0], MOVE[i][1]);
		}
	}
	return count;																		//���ظõ�ת���Է����Ӹ���
}

void Change(POINT2 NOW,int MAP[SIZE][SIZE],bool F)												//���Ӻ�ı�����״̬ FΪ�Ƿ��������Ļ
{
	int me = MAP[NOW.x][NOW.y];																	//��ǰ����������ɫ
	bool flag;
	POINT2 a, b;
	for (int i = 0; i<SIZE; ++i)																//����
	{
		flag = false;
		a.INIT(NOW.x + MOVE[i][0], NOW.y + MOVE[i][1]);
		while (a.x >= 0 && a.x<SIZE&&a.y >= 0 && a.y<SIZE&&MAP[a.x][a.y])
		{
			if (MAP[a.x][a.y] == -me)flag = true;
			else
			{
				if (flag)
				{
					a.ADD(-MOVE[i][0], -MOVE[i][1]);
					b.INIT(NOW.x + MOVE[i][0], NOW.y + MOVE[i][1]);
					while (((NOW.x <= b.x && b.x <= a.x) || (a.x <= b.x && b.x <= NOW.x)) && ((NOW.y <= b.y && b.y <= a.y) || (a.y <= b.y && b.y <= NOW.y)))
					{
						if(F)printcircle(b.MAP2WINX(), b.MAP2WINY(), (me == 1) ? black : white,MAP);	//�ı�����
						if (!F)mappadd(b.MAP2WINX(), b.MAP2WINY(), (me == 1) ? black : white, MAP);		//������������Ļ���ı��ͼ����
						b.ADD(MOVE[i][0], MOVE[i][1]);
					}
				}
				break;
			}
			a.ADD(MOVE[i][0], MOVE[i][1]);
		}
	}
}

int Statistics(int color)														//Ԥ��ÿ��λ�ÿ���ת���������Ӹ���
{
	int NOWEXPECT = 0;															//�ܵ�ת�����Ӹ���
	for (int i = 0; i < SIZE; ++i)												//����
		for (int j = 0; j < SIZE; ++j)
		{
			expect[i][j] = Judge(i, j, color,mapp);									//�洢��λ�ÿ���ת�����Ӹ���
			if (expect[i][j])
			{
				++NOWEXPECT;

				POINT2 a;
				a.INIT(i, j);
				setfillcolor(RGB(96, 96, 96));
				circle(a.MAP2WINX(), a.MAP2WINY(), CHESSSIZE / 4);
				circle(a.MAP2WINX(), a.MAP2WINY(), CHESSSIZE / 4 - 1);

				if (TIANEYES)														//�����������ģʽ
				{
					settextstyle(15, 0, "����");
					TCHAR s[20];													//����ģʽ
					_stprintf_s(s, _T("%d"), expect[i][j]);
					outtextxy(a.MAP2WINX(), a.MAP2WINY() + 10, s);
				}
			}
		}
	return NOWEXPECT;
}

void CleanStatistics()										//�����������ʾ
{
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			if (expect[i][j] && !mapp[i][j])				//�����ǰ��û�����ӻ���������
			{
				POINT2 a;
				a.INIT(i, j);								//��¼����
				putimage(a.MAP2WINX() - BBLACK / 2, a.MAP2WINY() - BBLACK / 2, &MAPIMAGE[i][j]);	//����ֲ�����
			}
		}
	}
}

string INTTOCHI(int num, int color)											//��ǰ���Ƴɼ��������
{
	string number[10] = { "","һ","��","��","��","��","��","��","��","��" };
	string data = "";
	if (num >= 10)
	{
		data += number[num / 10 % 10];
		data += "ʮ";
	}
	data += number[num % 10];
	return (color ? "���壺" : "���壺") + data;							//num>=0&&num<=64
}

void Printcount(int balckcount, int whitecount, int nowcolor)		//�����ǰ����
{
	settextcolor(DARKGRAY);											//����������ɫ
	settextstyle(35, 0, "����Ҧ��");

	putimage(WINDOWS_X / 30, WINDOWS_Y - WINDOWS_Y / 6, COUNT);		//����ԭ���ۼ�
	putimage(WINDOWS_X - WINDOWS_X / 5, WINDOWS_Y - WINDOWS_Y / 6, COUNT + 1);

	outtextxy(WINDOWS_X / 30, WINDOWS_Y - WINDOWS_Y / 6, INTTOCHI(whitecount, white).data());	//�����ǰ�ɼ�
	outtextxy(WINDOWS_X - WINDOWS_X / 5, WINDOWS_Y - WINDOWS_Y / 6, INTTOCHI(balckcount, black).data());

	setfillcolor(MYCOLOR == 1 ? BLACK : MYCOLOR == 0 ? WHITE : LIGHTCYAN);						//���м�Ŵ�任
	solidcircle(BBLACK * 2 + 10, BBLACK * 3 / 4, CHESSSIZE * 3 / 4);
	setfillcolor((!nowcolor || balckcount + whitecount == 4) ? BLACK : WHITE);
	NOWCOLOR = (!nowcolor || balckcount + whitecount == 4) ? black : white;						//��¼��ǰִ��
	for (int i = 0; i <= CHESSSIZE * 3 / 4; ++i)
	{
		solidcircle(BBLACK * 2 + 10, BBLACK * 3 / 2, i);
		Sleep(1);
	}
}

void WIN(int YOURCOLOR, int balckcount, int whitecount)			//�ж���Ӯ
{
	HWND wnd = GetHWnd();										//��ȡ���ھ��
	if (balckcount>whitecount)
	{
		MessageBox(wnd, YOURCOLOR == black ? "��ϲ�㣬ʤ����~" : YOURCOLOR == white ? "���˰�~����������ģ��´�һ������Ӯ�ģ�" : "�ڷ���ʤ~", "Result", MB_OK);
	}
	else if (balckcount<whitecount)
	{
		MessageBox(wnd, YOURCOLOR == white ? "��ϲ�㣬ʤ����~" : YOURCOLOR == black ? "���˰�~����������ģ��´�һ������Ӯ�ģ�" : "�׷���ʤ", "Result", MB_OK);
	}
	else
	{
		MessageBox(wnd, "��~ƽ�ְ���Ҫ��Ҫ����һ���أ�", "Result", MB_OK);
	}
}

void HL(int NOWWJ)
{
	if (NOWWJ != -1)
	{
		HWND wnd = GetHWnd();										//��ȡ���ھ��
		MessageBox(wnd, NOWWJ == MYCOLOR ? "��û�п����µ��ӣ�" : "�Է������ӿ��£�", "�غ�����", MB_OK);
	}
}

POINT2 Easy()										//�˻���ս��AI
{
	POINT2 MAX;										//�����Լ���ʼ�����Ž�
	MAX.INIT(0, 0);
	int maxx = 0;
	for (int i = 0; i < SIZE; ++i)
		for (int j = 0; j < SIZE; ++j)
		{
			if (expect[i][j] >= maxx)				//Ѱ�ҿ���ת���������ĵ���Ϊ���Ž�
			{
				maxx = expect[i][j];
				MAX.INIT(i, j);
			}
		}
	if (ESCEXIT)gameStart();
	Sleep(800);										//��Ъ
	return MAX;										//�������Ž�
}

void copymap(int one[SIZE][SIZE], int last[SIZE][SIZE])						//������ͼ
{
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			one[i][j] = last[i][j];
}

POINT2 Middle()										//�˻���ս�е�AI
{
	int ME = 0;										//AIȨֵ
	int maxx = 0;

	struct _ADD
	{
		int x;										//X����
		int y;										//Y����
		int w;										//Ȩֵ
		void init(int x, int y, int w)
		{
			this->x = x;
			this->y = y;
			this->w = w;
		}
		bool operator < (_ADD a)					//���رȽ������
		{
			return w>a.w;
		}
		POINT2 INTOPOINT2()							//ת��ΪPOINT2����
		{
			POINT2 data;
			data.INIT(x, y);
			return data;
		}
	}WEA[SIZE*SIZE];

	int expectnow[SIZE][SIZE],mapnow[SIZE][SIZE];	
	if (ESCEXIT)gameStart();												//��ESC�˳�
	Sleep(800);																//��Ъ0.8S
	
	for (int i = 0; i < SIZE; ++i)
		for (int j = 0; j < SIZE; ++j)
		{
			if (expect[i][j])												//�����ǰ���������
			{
				ME = MAPPOINTCOUNT[i][j]+expect[i][j];						//���㱾���ڸõ�Ȩֵ
				copymap(mapnow, mapp);
				mapnow[i][j] = NOWCOLOR ? 1 : -1;							//ģ������
				POINT2 NOWPOINT;
				NOWPOINT.INIT(i, j);
				if ((i == 0 && j == 0 )||( i == 0 && j == SIZE - 1) ||( i == SIZE - 1 && j == SIZE - 1) ||( i == SIZE - 1 && j == 0))
				{
					return NOWPOINT;										//����ڽǣ����ؽ�����
				}

				Change(NOWPOINT, mapnow,false);								//ģ�����������ı��ͼ
				int YOU = -1050;											//֪̽�����ж��������
				for (int k = 0; k < SIZE; ++k)
					for (int l = 0; l < SIZE; ++l)
					{
						expectnow[k][l] = Judge(k, l, !NOWCOLOR, mapnow);	//�ж϶�������
						if (expectnow[k][l])
						{
							YOU = YOU < MAPPOINTCOUNT[k][l] + expectnow[k][l] ? MAPPOINTCOUNT[k][l] + expectnow[k][l] : YOU;
						}
					}
				WEA[maxx++].init(i, j, ME - YOU);							//��ṹ������
			}
		}
	sort(WEA, WEA + maxx);													//����Ȩֵ����
	for (int i = 0; i < maxx; ++i)
	{
		if ((WEA[i].x < 2 && WEA[i].y < 2) || (WEA[i].x < 2 && SIZE - WEA[i].y - 1 < 2) || (SIZE - 1 - WEA[i].x < 2 && WEA[i].y < 2) || (SIZE - 1 - WEA[i].x < 2 && SIZE - 1 - WEA[i].y < 2))continue;
		return WEA[i].INTOPOINT2();											//���طǽǱ����Ž�
	}
	return WEA[0].INTOPOINT2();												//���ؽǱ����Ž�
}


int difai(int x,int y,int mapnow[SIZE][SIZE],int expectnow[SIZE][SIZE],int depin,int depinmax)						//����С����
{
	if (depin >= depinmax)return 0;											//�ݹ����

	int maxx = -10005;														//���Ȩֵ
	POINT2 NOW;
	int expectnow2[SIZE][SIZE] , mapnow2[SIZE][SIZE],mapnext[SIZE][SIZE],expectlast[SIZE][SIZE];					//������ʱ����

	copymap(mapnow2, mapnow);												//���Ƶ�ǰ����

	mapnow2[x][y] = NOWCOLOR ? 1 : -1;										//ģ���ڵ�ǰ����������
	int ME = MAPPOINTCOUNT[x][y] + expectnow[x][y];							//��ǰ����Ȩ
	NOW.INIT(x,y);

	Change(NOW, mapnow2, false);											//�ı�����AI����

	int MAXEXPECT = 0, LINEEXPECT = 0, COUNT = 0;
	for (int i = 0; i < SIZE; ++i)
		for (int j = 0; j < SIZE; ++j)
		{
			expectnow2[i][j] = Judge(i, j, !NOWCOLOR, mapnow2);				//Ԥ�жԷ��Ƿ��������
			if (expectnow2[i][j])
			{
				++MAXEXPECT;
				if ((i == 0 && j == 0) || (i == 0 && j == SIZE - 1) || (i == SIZE - 1 && j == SIZE - 1) || (i == SIZE - 1 && j == 0))return -1800;	//����Է���ռ�ǵĿ���
				if ((i < 2 && j < 2) || (i < 2 && SIZE - j - 1 < 2) || (SIZE - 1 - i < 2 && j < 2) || (SIZE - 1 - i < 2 && SIZE - 1 - j < 2))++LINEEXPECT;
			}
		}
	if (LINEEXPECT * 10 > MAXEXPECT * 7)return 1400;						//����Է��ߵ�����״̬�϶� ��֦

	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (expectnow2[i][j])											//����Է���������
			{
				int YOU = MAPPOINTCOUNT[i][j] + expectnow2[i][j];			//��ǰȨֵ
				copymap(mapnext, mapnow2);									//������ͼ
				mapnext[i][j] = (!NOWCOLOR) ? 1 : -1;						//ģ��Է�����
				NOW.INIT(i, j);
				Change(NOW, mapnext, false);								//�ı�����

				for (int k = 0; k < SIZE; k++)
					for (int l = 0; l < SIZE; l++)
						expectlast[k][l] = Judge(k, l, NOWCOLOR, mapnext);	//Ѱ��AI���е�

				for (int k = 0; k < SIZE; k++)
					for (int l = 0; l < SIZE;l++)
						if (expectlast[k][l])
						{
							int nowm = ME - YOU + difai(k, l, mapnext, expectlast, depin + 1, depinmax);
							maxx = maxx < nowm ? nowm : maxx;
						}
			}
	return maxx;
}

/*
POINT2 MIDDLE()									//�˻���ս�е�AI
{
	POINT2 MAX;
	int maxx = -10005;
	MAX.INIT(0, 0);
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
		{
			if (expect[i][j])
			{
				if ((i == 0 && j == 0) || (i == 0 && j == SIZE - 1) || (i == SIZE - 1 && j == SIZE - 1) || (i == SIZE - 1 && j == 0))
				{
					MAX.INIT(i, j);
					return MAX;										//����ڽǣ����ؽ�����
				}
				int k = difai(i, j, mapp, expect, 0, 1);					//�ݹ����� ��������
				if (k >= maxx)
				{
					maxx = k;
					MAX.INIT(i, j);
				}
			}
		}
	return MAX;
}
*/

POINT2 Difficult()									//�˻���ս����AI
{
	POINT2 MAX;
	int maxx = -10005;
	MAX.INIT(0, 0);
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
		{
			if (expect[i][j])
			{
				if ((i == 0 && j == 0) || (i == 0 && j == SIZE - 1) || (i == SIZE - 1 && j == SIZE - 1) || (i == SIZE - 1 && j == 0))
				{
					MAX.INIT(i, j);
					return MAX;										//����ڽǣ����ؽ�����
				}
				int k = difai(i,j,mapp,expect,0,3);					//�ݹ����� ��������
				if (k >= maxx)
				{
					maxx = k;
					MAX.INIT(i, j);
				}
			}
		}
	return MAX;
}

POINT2 MOUSE()										//����¼�
{
	MOUSEMSG m;
	while (true)
	{
		m = GetMouseMsg();							//��ȡ�����Ϣ
		switch (m.uMsg)
		{
		case(WM_LBUTTONDOWN) :						//������������ʱ
		{
			POINT2 NOWMOUSE;
			NOWMOUSE.INIT(m.x, m.y);
			if (TOINTERNET)							//�������������ս״̬ ���͵�ǰ����
			{
				char Toyou[50] = { 0 };
				sprintf_s(Toyou, "%d,%d", m.x, m.y);
				send(sockConn, Toyou, sizeof(Toyou) , 0);		//��������
			}
			return NOWMOUSE;						//�����������
			break;
		}
		case(WM_MOUSEMOVE) :								//���� ������λ��
		{
			if (ESCEXIT)gameStart();
			break;
		}
		case(WM_RBUTTONDOWN) :								//�������Ҽ�����ʱ
		{
			TIANEYES = !TIANEYES;							//����OR�ر�����ģʽ
			break;
		}
		}
	}
}

bool putmouse(POINT2 &m)									//�ض����������
{
	bool flag = true;
	int mouseinx[SIZE + 1], mouseiny[SIZE + 1];
	for (int i = 0; i < SIZE + 1; ++i)						//��ȷ������
	{
		mouseinx[i] = PX + i*BBLACK;
		mouseiny[i] = PY + i*BBLACK;
	}
	if (m.x < PX || m.x>PX + SIZE*BBLACK || m.y < PY || m.y>PY + SIZE*BBLACK)flag = false;	//��������������
	else
	{
		for (int i = 0; i<SIZE; ++i)
		{
			if (m.x >= mouseinx[i] && m.x <= mouseinx[i + 1])
			{
				if (m.x - mouseinx[i]>BBLACK / 8 && mouseinx[i + 1] - m.x>BBLACK / 8)		//�ض���X
				{
					m.x = (mouseinx[i] + mouseinx[i + 1]) / 2;
				}
				else flag = false;
			}
		}
		for (int i = 0; i<SIZE; ++i)
		{
			if (m.y >= mouseiny[i] && m.y <= mouseiny[i + 1])
			{
				if (m.y - mouseiny[i]>BBLACK / 8 && mouseiny[i + 1] - m.y > BBLACK / 8)		//�ض���Y
				{
					m.y = (mouseiny[i] + mouseiny[i + 1]) / 2;
				}
				else flag = false;
			}
		}
	}
	return flag;											//���ص�ǰλ���ܷ�����
}

void CleanLast(POINT2 WINDOWS2, int F)						//��¼��һ������λ��
{
	if (LASTCH.x > SIZE&&LASTCH.y > SIZE)					//����ȡ����һ�����
	{
		setfillcolor(getpixel(LASTCH.x, LASTCH.y));			//��ȡԭ��������ɫ
		putimage(LASTCH.x - BBLACK / 2, LASTCH.y - BBLACK / 2, &MAPIMAGE[LASTCH.WIN2MAPX()][LASTCH.WIN2MAPY()]);		
		solidcircle(LASTCH.x, LASTCH.y, CHESSSIZE);
	}

	setfillcolor(RGB(49, 153, 182));						//����Ϊ��䵱ǰ����
	LASTCH.INIT(WINDOWS2.x, WINDOWS2.y);

	solidrectangle(WINDOWS2.x - BBLACK / 2 + 2, WINDOWS2.y - BBLACK / 2 + 2, WINDOWS2.x + BBLACK / 2 - 2, WINDOWS2.y + BBLACK / 2 - 2);		//��������
	setfillcolor(F ? BLACK : WHITE);
	solidcircle(WINDOWS2.x, WINDOWS2.y, CHESSSIZE);			//������
}

int Playchess(int F, POINT2 WINDOWS2, int &balckcount, int &whitecount)	//��ʼ
{
	//F �ڷ�Ϊ1  �׷�Ϊ0
	POINT2 MAP2;

	if (WINDOWS2.x < SIZE&&WINDOWS2.y < SIZE)					//������������Ϊ��������
	{
		MAP2 = WINDOWS2;
		WINDOWS2.MAP2WIN(WINDOWS2);								//����ת����ʵ��չʾ����
	}
	else
	{
		if (!putmouse(WINDOWS2))return 0;						//������������ض���
		WINDOWS2.WIN2MAP(MAP2);									//�洢�ض���֮��ľ�������
	}
	if (expect[MAP2.x][MAP2.y])									//��λ�ÿ���
	{
		CleanStatistics();										//�����Ļ��ʾ
		if (F)													//�ж����Ϊ����÷�
		{
			balckcount += expect[MAP2.x][MAP2.y] + 1;
			whitecount -= expect[MAP2.x][MAP2.y];
		}
		else
		{
			whitecount += expect[MAP2.x][MAP2.y] + 1;
			balckcount -= expect[MAP2.x][MAP2.y];
		}

		printcircle(WINDOWS2.x, WINDOWS2.y, F,mapp);			//������ mappΪ��������
		CleanLast(WINDOWS2, F);									//��ǰ����������ʾ
		Change(MAP2,mapp,true);									//��ת���� trueΪ��ʾ����Ļ
		Printcount(balckcount, whitecount, F);	//��ӡ����

		if (balckcount + whitecount >= SIZE*SIZE || !balckcount || !whitecount)return 3;	//���ʤ���ѷ�
		if (!Statistics(!F))									//����Է��޷�����
		{
			if (Statistics(F))									//�ж��Լ��Ƿ��������
			{
				HL(!F);											//�Լ�����������Է��޷�������Ϣ
				return 2;
			}
			else return 3;										//˫�����޷�����
		}
		return 1;
	}
	return 0;
}

void STARTVS(int YOURCOLOR, POINT2 P1(), POINT2 P2())			//��ʼ��ս
{
	int balckcount = 2, whitecount = 2;							//��ʼ�����ŵ�����

	MYCOLOR = YOURCOLOR;

	Printcount(balckcount, whitecount, black);					//��ǰ����
	Statistics(black);
	while (true)
	{
	CX1:														//���غϺ���
		int PD = Playchess(black, (*P1)(), balckcount, whitecount);
		switch (PD)
		{
		case 0:
			goto CX1;											//����ʧ���������
			break;
		case 1:
			break;												//��������
		case 2:
			goto CX1;											//���ԶԷ�
			break;
		case 3:
			goto ED;											//��ֽ���
			break;
		}
	CX2:															//���غϺ���
		PD = Playchess(!black, (*P2)(), balckcount, whitecount);
		switch (PD)
		{
		case 0:
			goto CX2;
			break;
		case 1:
			break;
		case 2:
			goto CX2;
			break;
		case 3:
			goto ED;
			break;
		}
	}
ED:																	//����
	WIN(YOURCOLOR, balckcount, whitecount);
	_getch();
	if (TOINTERNET)
	{
		closesocket(sockSer);
		closesocket(sockConn);
	}
	gameStart();
}

char *ip;												//����IP��ַ���� 
void Get_ip()											//��ȡ����IP��ַ
{
	WSADATA wsaData;
	char name[255];										//�������ڴ�Ż�õ��������ı���
	PHOSTENT hostinfo;									//���Winsock�汾����ȷֵ
	if (WSAStartup(MAKEWORD(2, 0), &wsaData) == 0)		//���Ǽ���Winsock�⣬���WSAStartup������������ֵΪ0��˵�����سɹ���������Լ���
	{
		if (gethostname(name, sizeof(name)) == 0)		//�ɹ��ؽ������������������name����ָ���Ļ�������
		{
			if ((hostinfo = gethostbyname(name)) != NULL) //���ǻ�ȡ������
			{
				settextstyle(BBLACK / 2, 0, "����Ҧ��");
				outtextxy(WINDOWS_X / 2 - 5 * BBLACK / 2, BBLACK * 2, "ī������ �������Ѵ���");
				settextstyle(BBLACK / 4, 0, "����");
				ip = inet_ntoa(*(struct in_addr *)*hostinfo->h_addr_list);   //����inet_ntoa������������hostinfo�ṹ�����е�h_addr_listת��Ϊ��׼�ĵ�ֱ�ʾ��IP
				char c[250] = { "1.�������ͬѧ���ip��ַ�Ϳ���������~" };
				strcat_s(c, ip);
				outtextxy(WINDOWS_X / 2 - 3 * BBLACK, BBLACK * 7 / 2, c);
				outtextxy(WINDOWS_X / 2 - 3 * BBLACK, BBLACK * 4, "2.����Ҫ��ȷ��������ͬһ����������Ŷ��");
			}
		}
		WSACleanup();										//ж��Winsock�⣬���ͷ�������Դ
	}
}

POINT2 OURCLASS()									//�����Է����͵�����
{
	POINT2 YOU;
	char data[50] = { 0 };
	int x = 0, y = 0;
	int p = recv(sockConn, data, 50, 0);
	if (p == SOCKET_ERROR)
	{
		HWND wnd = GetHWnd();
		MessageBox(wnd, "�Է����жϳ�����ѵ���,����������", "�����ж�", MB_OK | MB_ICONWARNING);
		exit(0);
	}
	sscanf_s(data, "%d,%d", &x, &y);				//�����ڱ�����
	YOU.INIT(x, y);
	return YOU;
}

void TOI(bool FUORKE)								//����ģʽ
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err, res = 0;
	wVersionRequested = MAKEWORD(1, 1);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) return;
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		return;
	}
	SOCKADDR_IN addrSer;
	if (FUORKE)
	{
		Get_ip();										//����������
		sockSer = socket(AF_INET, SOCK_STREAM, 0);
	}
	else
	{
		settextstyle(BBLACK / 2, 0, "����Ҧ��");
		outtextxy(WINDOWS_X / 2 - 3 * BBLACK / 2, BBLACK * 3 / 2, "ī�����������");
		settextstyle(BBLACK / 4, 0, "����");
		outtextxy(WINDOWS_X / 2 - 2 * BBLACK, BBLACK * 5 / 2, "1����ȷ�����������������");
		outtextxy(WINDOWS_X / 2 - 2 * BBLACK, BBLACK * 3, "2����ȷ�����������ͬһ��������");
		ip = (char*)malloc(sizeof(char) * 50);
		InputBox(ip, 50, "���������˵�IP��ַ");
		sockConn = socket(AF_INET, SOCK_STREAM, 0);
	}
	addrSer.sin_family = AF_INET;
	addrSer.sin_port = htons(5050);
	addrSer.sin_addr.S_un.S_addr = inet_addr(ip);
	if (FUORKE)											//���Ϊ�����
	{
		SOCKADDR_IN addrCli;
		bind(sockSer, (SOCKADDR*)&addrSer, sizeof(SOCKADDR));
		listen(sockSer, 5);
		int len = sizeof(SOCKADDR);
		settextstyle(BBLACK / 4, 0, "����");
		outtextxy(WINDOWS_X / 2 - 2 * BBLACK, BBLACK * 5, "�������Ѵ������ȴ�������...");
		sockConn = accept(sockSer, (SOCKADDR*)&addrCli, &len);
	}
	else res = connect(sockConn, (SOCKADDR*)&addrSer, sizeof(SOCKADDR));
	if (sockConn == INVALID_SOCKET || res)
	{
		outtextxy(2 * BBLACK, BBLACK * 6, "����ʧ�ܣ�");
		_getch();
		gameStart();									//����������
	}
	else
	{
		outtextxy(2 * BBLACK, BBLACK * 6, "���ӳɹ�����������������Ϸ~");
		_getch();
	}
}

void gameStart()
{
	IMAGE MM[11] = { 0 }, MB[3] = { 0 };
	initgraph(WINDOWS_X, WINDOWS_Y);
	setbkmode(TRANSPARENT);					//͸������

	HWND hwnd = GetHWnd();					// ���ô��ڱ�������
	SetWindowText(hwnd, "ī������ --- ǧǧ");
	loadimage(NULL, "0.jpg");

	const int bblack = 10;

	LOGFONT f;
	gettextstyle(&f);												// ��ȡ������ʽ
	f.lfHeight = BBLACK;												// ��������߶�
	strcpy_s(f.lfFaceName, _T("����Ҧ��"));								// ��������
	f.lfQuality = ANTIALIASED_QUALITY;								// �������Ч��Ϊ�����  
	settextstyle(&f);												// ����������ʽ
	RECT r1 = { 0, 0, WINDOWS_X, WINDOWS_Y / 3 };
	drawtext("ī �� �� ��", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	settextstyle(BBLACK / 4, 0, "����Ҧ��");
	RECT r2 = { WINDOWS_X / 2 - BBLACK,WINDOWS_Y / 3,WINDOWS_X / 2 + BBLACK ,WINDOWS_Y / 3 + BBLACK / 2 };
	rectangle(WINDOWS_X / 2 - BBLACK, WINDOWS_Y / 3, WINDOWS_X / 2 + BBLACK, WINDOWS_Y / 3 + BBLACK / 2);
	drawtext("����ģʽ", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT r3 = { WINDOWS_X / 2 - BBLACK,WINDOWS_Y / 3 + BBLACK / 2 + bblack,WINDOWS_X / 2 + BBLACK,WINDOWS_Y / 3 + BBLACK + bblack };
	rectangle(WINDOWS_X / 2 - BBLACK, WINDOWS_Y / 3 + BBLACK / 2 + bblack, WINDOWS_X / 2 + BBLACK, WINDOWS_Y / 3 + BBLACK + bblack);
	drawtext("˫��ģʽ", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT r4 = { WINDOWS_X / 2 - BBLACK,WINDOWS_Y / 3 + BBLACK + 2 * bblack,WINDOWS_X / 2 + BBLACK,(int)(WINDOWS_Y / 3 + BBLACK*1.5 + 2 * bblack) };
	rectangle(WINDOWS_X / 2 - BBLACK, WINDOWS_Y / 3 + BBLACK + 2 * bblack, WINDOWS_X / 2 + BBLACK, (int)(WINDOWS_Y / 3 + BBLACK*1.5 + 2 * bblack));
	drawtext("������ս", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT r5 = { WINDOWS_X / 2 - BBLACK,(int)(WINDOWS_Y / 3 + BBLACK*1.5 + 3 * bblack),WINDOWS_X / 2 + BBLACK,WINDOWS_Y / 3 + BBLACK * 2 + 3 * bblack };
	rectangle(WINDOWS_X / 2 - BBLACK, (int)(WINDOWS_Y / 3 + BBLACK*1.5 + 3 * bblack), WINDOWS_X / 2 + BBLACK, WINDOWS_Y / 3 + BBLACK * 2 + 3 * bblack);
	drawtext("��սģʽ", &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT r6 = { WINDOWS_X / 2 - BBLACK,WINDOWS_Y / 3 + BBLACK * 2 + 4 * bblack,WINDOWS_X / 2 + BBLACK,(int)(WINDOWS_Y / 3 + BBLACK * 2.5 + 4 * bblack) };
	rectangle(WINDOWS_X / 2 - BBLACK, WINDOWS_Y / 3 + BBLACK * 2 + 4 * bblack, WINDOWS_X / 2 + BBLACK, (int)(WINDOWS_Y / 3 + BBLACK * 2.5 + 4 * bblack));
	drawtext("��Ϸ����", &r6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT r7 = { WINDOWS_X / 2 - BBLACK,(int)(WINDOWS_Y / 3 + BBLACK * 2.5 + 5 * bblack),WINDOWS_X / 2 + BBLACK,WINDOWS_Y / 3 + BBLACK * 3 + 5 * bblack };
	rectangle(WINDOWS_X / 2 - BBLACK, (int)(WINDOWS_Y / 3 + BBLACK * 2.5 + 5 * bblack), WINDOWS_X / 2 + BBLACK, WINDOWS_Y / 3 + BBLACK * 3 + 5 * bblack);
	drawtext("����˵��", &r7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT r8 = { WINDOWS_X / 2 - BBLACK,WINDOWS_Y / 3 + BBLACK * 3 + 6 * bblack,WINDOWS_X / 2 + BBLACK,(int)(WINDOWS_Y / 3 + BBLACK * 3.5 + 6 * bblack) };
	rectangle(WINDOWS_X / 2 - BBLACK, WINDOWS_Y / 3 + BBLACK * 3 + 6 * bblack, WINDOWS_X / 2 + BBLACK, (int)(WINDOWS_Y / 3 + BBLACK * 3.5 + 6 * bblack));
	drawtext("��    ��", &r8, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT r9 = { WINDOWS_X / 2 - BBLACK,(int)(WINDOWS_Y / 3 + BBLACK * 3.5 + 7 * bblack),WINDOWS_X / 2 + BBLACK,WINDOWS_Y / 3 + BBLACK * 4 + 7 * bblack };
	rectangle(WINDOWS_X / 2 - BBLACK, (int)(WINDOWS_Y / 3 + BBLACK * 3.5 + 7 * bblack), WINDOWS_X / 2 + BBLACK, WINDOWS_Y / 3 + BBLACK * 4 + 7 * bblack);
	drawtext("�˳���Ϸ", &r9, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	for (int i = 0; i < 8; i++)																						//���水ťͼƬ
		getimage(MM + i, WINDOWS_X / 2 - BBLACK, WINDOWS_Y / 3 + i*bblack + i*BBLACK / 2, 2 * BBLACK, BBLACK / 2);
	getimage(MM + 8, WINDOWS_X - BBLACK, WINDOWS_Y - BBLACK / 2, BBLACK - 11, BBLACK / 2 - 11);

	bool _HOME = true, _INTRODUCTION = false, _OPERATION = false, _ABOUT = false, _TOINTERNET = false, _DRMS = false;			//TRUE��ʾ���ڵ�ǰҳ��
	MOUSEMSG m;
	while (_HOME)
	{
		BeginBatchDraw();
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:												//������������ʱ
			EndBatchDraw();
			if (m.x>WINDOWS_X / 2 - BBLACK && m.x<WINDOWS_X / 2 + BBLACK && m.y>WINDOWS_Y / 3 && m.y<WINDOWS_Y / 3 + BBLACK / 2 && _HOME  && !_INTRODUCTION  && !_OPERATION&&!_ABOUT&&!_TOINTERNET&&!_DRMS)//����ģʽ
			{
				_DRMS = true;									//�뿪HOME����
				cleardevice();
				loadimage(NULL, "0.jpg");				//����
				rectangle(BBLACK, BBLACK, WINDOWS_X - BBLACK, WINDOWS_Y - BBLACK);

				RECT r1 = { WINDOWS_X / 2 - BBLACK,WINDOWS_Y / 3,WINDOWS_X / 2 + BBLACK ,WINDOWS_Y / 3 + BBLACK / 2 };
				rectangle(WINDOWS_X / 2 - BBLACK, WINDOWS_Y / 3, WINDOWS_X / 2 + BBLACK, WINDOWS_Y / 3 + BBLACK / 2);
				drawtext("��    ��", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

				RECT r2 = { WINDOWS_X / 2 - BBLACK,WINDOWS_Y / 3 + BBLACK + 2 * bblack,WINDOWS_X / 2 + BBLACK,(int)(WINDOWS_Y / 3 + BBLACK*1.5 + 2 * bblack) };
				rectangle(WINDOWS_X / 2 - BBLACK, WINDOWS_Y / 3 + BBLACK + 2 * bblack, WINDOWS_X / 2 + BBLACK, (int)(WINDOWS_Y / 3 + BBLACK*1.5 + 2 * bblack));
				drawtext("��    ��", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

				RECT r3 = { WINDOWS_X / 2 - BBLACK,WINDOWS_Y / 3 + BBLACK * 2 + 4 * bblack,WINDOWS_X / 2 + BBLACK,(int)(WINDOWS_Y / 3 + BBLACK * 2.5 + 4 * bblack) };
				rectangle(WINDOWS_X / 2 - BBLACK, WINDOWS_Y / 3 + BBLACK * 2 + 4 * bblack, WINDOWS_X / 2 + BBLACK, (int)(WINDOWS_Y / 3 + BBLACK * 2.5 + 4 * bblack));
				drawtext("��    ��", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

				for (int i = 0; i < 3; i++)
				{
					getimage(MB + i, WINDOWS_X / 2 - BBLACK, WINDOWS_Y / 3 + BBLACK*i + 2 * i * bblack, 2 * BBLACK, BBLACK / 2);
				}

				RECT R = { WINDOWS_X - BBLACK,WINDOWS_Y - BBLACK / 2,WINDOWS_X - 10,WINDOWS_Y - 10 };
				rectangle(WINDOWS_X - BBLACK, WINDOWS_Y - BBLACK / 2, WINDOWS_X - 10, WINDOWS_Y - 10);
				drawtext("����", &R, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			}
			else if (m.x>WINDOWS_X / 2 - BBLACK && m.x<WINDOWS_X / 2 + BBLACK && m.y>WINDOWS_Y / 3 && m.y<WINDOWS_Y / 3 + BBLACK / 2 && _DRMS)			//��
			{
				_HOME = false;
				cleardevice();
				init();
				STARTVS(black, MOUSE, Easy);							//���˼�ģʽ
				break;
			}
			else if (m.x>WINDOWS_X / 2 - BBLACK && m.x<WINDOWS_X / 2 + BBLACK && m.y>WINDOWS_Y / 3 + BBLACK + 2 * bblack && m.y<(int)(WINDOWS_Y / 3 + BBLACK*1.5 + 2 * bblack) && _DRMS)			//�е�
			{
				_HOME = false;
				cleardevice();
				init();
				STARTVS(black, MOUSE, Middle);							//�����е�ģʽ
				break;
			}
			else if (m.x>WINDOWS_X / 2 - BBLACK && m.x<WINDOWS_X / 2 + BBLACK && m.y> WINDOWS_Y / 3 + BBLACK * 2 + 4 * bblack && m.y<(int)(WINDOWS_Y / 3 + BBLACK * 2.5 + 4 * bblack) && _DRMS)			//����
			{
				_HOME = false;
				cleardevice();
				init();
				STARTVS(black, MOUSE, Difficult);							//��������ģʽ
				break;
			}
			else if (m.x>WINDOWS_X / 2 - BBLACK && m.x<WINDOWS_X / 2 + BBLACK && m.y>WINDOWS_Y / 3 + BBLACK / 2 + bblack && m.y<WINDOWS_Y / 3 + BBLACK + bblack && _HOME  && !_INTRODUCTION  && !_OPERATION&&!_ABOUT&&!_TOINTERNET&&!_DRMS)//˫��ģʽ
			{
				_HOME = false;									//�뿪HOME����
				init();
				STARTVS(-1, MOUSE, MOUSE);							//˫��ģʽ
				break;
			}
			else if (m.x>WINDOWS_X / 2 - BBLACK && m.x<WINDOWS_X / 2 + BBLACK && m.y>WINDOWS_Y / 3 + BBLACK + 2 * bblack && m.y<(int)(WINDOWS_Y / 3 + BBLACK*1.5 + 2 * bblack) && _HOME   && !_OPERATION&&!_ABOUT && !_INTRODUCTION&&!_TOINTERNET&&!_DRMS)//������ս
			{
				_TOINTERNET = true;
				cleardevice();
				loadimage(NULL, "0.jpg");				//����
				rectangle(BBLACK, BBLACK, WINDOWS_X - BBLACK, WINDOWS_Y - BBLACK);
				RECT R1 = { WINDOWS_X / 4, WINDOWS_Y / 2 + BBLACK, WINDOWS_X / 4 + 2 * BBLACK , WINDOWS_Y / 2 + 2 * BBLACK };
				RECT R3 = { WINDOWS_X - WINDOWS_X / 4 - 2 * BBLACK, WINDOWS_Y / 2 + BBLACK, WINDOWS_X - WINDOWS_X / 4, WINDOWS_Y / 2 + 2 * BBLACK };
				rectangle(WINDOWS_X / 4, WINDOWS_Y / 2 + BBLACK, WINDOWS_X / 4 + 2 * BBLACK, WINDOWS_Y / 2 + 2 * BBLACK);
				rectangle(WINDOWS_X - WINDOWS_X / 4 - 2 * BBLACK, WINDOWS_Y / 2 + BBLACK, WINDOWS_X - WINDOWS_X / 4, WINDOWS_Y / 2 + 2 * BBLACK);
				drawtext("��Ҫ����", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				drawtext("��Ҫ����", &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				getimage(MM + 9, WINDOWS_X / 4, WINDOWS_Y / 2 + BBLACK, 2 * BBLACK, BBLACK);
				getimage(MM + 10, WINDOWS_X - WINDOWS_X / 4 - 2 * BBLACK, WINDOWS_Y / 2 + BBLACK, 2 * BBLACK, BBLACK);

				outtextxy(WINDOWS_X / 3 - 50, 150, "����˵����");
				outtextxy(WINDOWS_X / 3, 185, "1���������Ҫ����������������");
				outtextxy(WINDOWS_X / 3, 220, "2����������ѽ��롰��Ҫ���ӡ�");
				outtextxy(WINDOWS_X / 3, 255, "3�����������ip��ַ");
				outtextxy(WINDOWS_X / 3, 290, "4��������Ϸ");
				outtextxy(WINDOWS_X / 3, 325, "*��ȷ��������ͬһ����������Ŷ~");
				RECT R2 = { WINDOWS_X - BBLACK,WINDOWS_Y - BBLACK / 2,WINDOWS_X - 10,WINDOWS_Y - 10 };
				rectangle(WINDOWS_X - BBLACK, WINDOWS_Y - BBLACK / 2, WINDOWS_X - 10, WINDOWS_Y - 10);
				drawtext("����", &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			}
			else if (m.x>WINDOWS_X / 4 && m.x<WINDOWS_X / 4 + 2 * BBLACK  && m.y>WINDOWS_Y / 2 + BBLACK && m.y<WINDOWS_Y / 2 + 2 * BBLACK && _TOINTERNET)//��Ҫ����
			{
				TOINTERNET = true;
				cleardevice();
				loadimage(NULL, "0.jpg");				//����
				rectangle(BBLACK, BBLACK, WINDOWS_X - BBLACK, WINDOWS_Y - BBLACK);
				TOI(true);								//����������
				init();
				STARTVS(white, OURCLASS, MOUSE);
				break;
			}
			else if (m.x>WINDOWS_X - WINDOWS_X / 4 - 2 * BBLACK && m.x<WINDOWS_X - WINDOWS_X / 4 && m.y>WINDOWS_Y / 2 + BBLACK && m.y<WINDOWS_Y / 2 + 2 * BBLACK && _TOINTERNET)//��Ҫ����
			{
				TOINTERNET = true;
				cleardevice();
				loadimage(NULL, "0.jpg");				//����
				rectangle(BBLACK, BBLACK, WINDOWS_X - BBLACK, WINDOWS_Y - BBLACK);
				TOI(false);								//���ӷ�����
				init();
				STARTVS(black, MOUSE, OURCLASS);
				break;
			}
			else if (m.x>WINDOWS_X / 2 - BBLACK && m.x<WINDOWS_X / 2 + BBLACK && m.y>(int)(WINDOWS_Y / 3 + BBLACK*1.5 + 3 * bblack) && m.y<WINDOWS_Y / 3 + BBLACK * 2 + 3 * bblack && _HOME  &&!_OPERATION&&!_ABOUT && !_INTRODUCTION&&!_TOINTERNET&&!_DRMS)		//��սģʽ
			{
				_HOME = false;										//�뿪HOME����
				init();
				STARTVS(-1, Middle,Difficult );								//��սģʽ
				break;
			}
			else if (m.x>WINDOWS_X / 2 - BBLACK && m.x<WINDOWS_X / 2 + BBLACK && m.y> WINDOWS_Y / 3 + BBLACK * 2 + 4 * bblack && m.y<(int)(WINDOWS_Y / 3 + BBLACK * 2.5 + 4 * bblack) && _HOME &&!_INTRODUCTION&&!_ABOUT&&!_OPERATION&&!_TOINTERNET&&!_DRMS)	//��Ϸ����
			{
				_INTRODUCTION = true;
				cleardevice();
				loadimage(NULL, "0.jpg");				//����
				string data[16] = {
					"��Ϸ���ܣ�" ,
					"�岽֮�ڣ����˲���",
					"ʮ��ĥ����һ������",
					"ǧ��Ӹ꣬���ڸ���",
					"�ĺ���������������",
					"ÿһ������ī�ʵ��� ��������ѡ��",
					"���½԰� Ψ�Ҷ���",
					"����Ϳ̿ ��֮����",
					"ī�ž��� �˶�����",
					"�˺���� �氮ƽ��",
					"ī�����ŷǹ��氮 Ҫ���ʤ��",
					"����һ��Ҫͨ��ɱ¾ ����Ϊ�� ����Ϊ��",
					"ī����� ������Ȼ����",
					"���ǵ���˫����ת�� ȴ��ǧ���� ��������",
				};

				rectangle(BBLACK, BBLACK, WINDOWS_X - BBLACK, WINDOWS_Y - BBLACK);
				settextstyle(BBLACK / 2 - 5, 0, "����Ҧ��");
				settextcolor(RGB(0, 255, 255));
				outtextxy(WINDOWS_X / 3 - 100, 90, data[0].data());
				settextstyle(BBLACK / 4, 0, "����Ҧ��");
				settextcolor(WHITE);
				int LEFT, TOP = 115;
				for (int i = 1; i < 16; i++)
				{
					LEFT = WINDOWS_X / 3;
					if (i == 5 || i >= 10)LEFT -= 25;
					if (i == 5 || i == 10 || i == 6)TOP += 30;
					outtextxy(LEFT, TOP + 35 * i, data[i].data());
				}
				RECT R1 = { WINDOWS_X - BBLACK,WINDOWS_Y - BBLACK / 2,WINDOWS_X - 10,WINDOWS_Y - 10 };
				rectangle(WINDOWS_X - BBLACK, WINDOWS_Y - BBLACK / 2, WINDOWS_X - 10, WINDOWS_Y - 10);
				drawtext("����", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			}
			else if (m.x>WINDOWS_X / 2 - BBLACK && m.x<WINDOWS_X / 2 + BBLACK && m.y>(int)(WINDOWS_Y / 3 + BBLACK * 2.5 + 5 * bblack) && m.y<WINDOWS_Y / 3 + BBLACK * 3 + 5 * bblack && _HOME &&!_INTRODUCTION &&!_OPERATION&&!_ABOUT&&!_TOINTERNET&&!_DRMS)	//����˵��
			{
				_OPERATION = true;
				cleardevice();
				loadimage(NULL, "0.jpg");				//����
				string data[16] = {
					"����˵����" ,
					"���ʦ��",
					"����֮���� ������ͨ�����",
					"���Ǹ��ݱ��ž�ѧ������ƶ��ɵ�ī������",
					"ī��������Χ�����ԵĲ�ͬ����",
					"ī������в������κ����ӱ�ɱ��",
					"��һ�������ӱ���һ������ǰ��Χ��",
					"����Щ���Ӿ�ת������һ��",
					"��Ȼ �����Щ�����ֱ�Χ��ʱ",
					"�������ٴ�ת��",
					"�����ʮ�ĸ����̲���ʱ�Ϳ�˫��˭������������",
					"��һ���ͻ�ʤ",
					"ī����� ÿһ�����ӱ���Ҫ�γ�ת��",
					"����Է�û�пɱ�ת��������ʱ",
					"������� ������ֻ�ܷ�����һ�ֳ���",
					"�ܹ��Ѷ��ֱ����������� �ͽ������� ��������������",
				};

				rectangle(BBLACK, BBLACK, WINDOWS_X - BBLACK, WINDOWS_Y - BBLACK);
				settextstyle(BBLACK / 2 - 5, 0, "����Ҧ��");
				settextcolor(RGB(0, 255, 255));
				outtextxy(WINDOWS_X / 3 - 100, 90, data[0].data());
				settextstyle(BBLACK / 4, 0, "����Ҧ��");
				settextcolor(WHITE);
				int LEFT, TOP = 115;
				for (int i = 1; i < 16; i++)
				{
					LEFT = WINDOWS_X / 3;
					if (i == 1)LEFT -= 50;
					if (i == 6 || i == 10)LEFT -= 25;
					if (i == 12)TOP += 30;
					outtextxy(LEFT, TOP + 35 * i, data[i].data());
				}
				RECT R3 = { WINDOWS_X - BBLACK,WINDOWS_Y - BBLACK / 2,WINDOWS_X - 10,WINDOWS_Y - 10 };
				rectangle(WINDOWS_X - BBLACK, WINDOWS_Y - BBLACK / 2, WINDOWS_X - 10, WINDOWS_Y - 10);
				drawtext("����", &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			}
			else if (m.x > WINDOWS_X / 2 - BBLACK && m.x<WINDOWS_X / 2 + BBLACK && m.y>WINDOWS_Y / 3 + BBLACK * 3 + 6 * bblack && m.y < (int)(WINDOWS_Y / 3 + BBLACK * 3.5 + 6 * bblack) && _HOME  && !_INTRODUCTION  && !_OPERATION&&!_ABOUT&&!_TOINTERNET&&!_DRMS)//����
			{
				_ABOUT = true;
				cleardevice();
				loadimage(NULL, "0.jpg");				//����
				string data[16] = {
					"����:" ,
					"�о������������ҳ����˶��ǹ��� ǧǧ ����Ӵ��",
					"��ô˵ǧǧҲ���������ǣ�",
					"�¶���֪�о�ʱ�������ĺÿ죬��֪������Ҫ�ȹ���һ��~",
					"ֻ�ǲ����ڿ���֮�󿴵��Լ���ҿ� o(�s���t)o",
					"ÿ�θ���ͷ�񶼻��Һܾúܾ���",
					"ǧǧ�������أ�����˵������~ ��Ϊ�Լ�Ҳ��֪��",
					"������ߵ�ÿ���˿���~ �Ͼ�����Ҳ�������ҿ��Ĺ�~",
					"#More ���ա���",
					"ǧǧ������������ǧ��~",
					"�Ͼ������ð���Ψһһ��ϲ��ǧ����Ů�������ƺ�������~",
					"��Ȼ������ǧǧҲû����~ �Ҳ������Ĩr(�s���t)�q[����]  @����",
					"ǧǧ�Ǹ�90����~",
					"������ô˵����98��~",
					"ǧǧ������������ĵ����� n(*�R���Q*)n",
					"����˵Ԫ�����ֵ�ͬʱҲ����Happy  birthday  to  me!",
				};

				rectangle(BBLACK, BBLACK, WINDOWS_X - BBLACK, WINDOWS_Y - BBLACK);
				settextstyle(BBLACK / 2 - 5, 0, "����Ҧ��");
				settextcolor(RGB(0, 255, 255));
				outtextxy(WINDOWS_X / 3 - 100, 90, data[0].data());
				settextstyle(BBLACK / 4, 0, "����Ҧ��");
				settextcolor(WHITE);
				int LEFT, TOP = 115;
				for (int i = 1; i < 16; i++)
				{
					LEFT = WINDOWS_X / 3;
					if (i == 1 || i == 9)LEFT -= 50;
					else if (i == 2 || i == 8)LEFT -= 25;
					if (i == 9)TOP += 30;
					outtextxy(LEFT, TOP + 35 * i, data[i].data());
				}
				RECT R3 = { WINDOWS_X - BBLACK,WINDOWS_Y - BBLACK / 2,WINDOWS_X - 10,WINDOWS_Y - 10 };
				rectangle(WINDOWS_X - BBLACK, WINDOWS_Y - BBLACK / 2, WINDOWS_X - 10, WINDOWS_Y - 10);
				drawtext("����", &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				settextstyle(BBLACK / 4, 0, "΢���ź�");
				string author[5] = {
					"Author: ǧǧ",
					"Age: 18",
					"Constellation: Capricorn",
					"Email: qian1335661317@qq.com",
					"Domain:https://www.dreamwings.cn"
				};
				for (int i = 0; i < 5; i++)
				{
					outtextxy(5 * BBLACK / 4, WINDOWS_Y - (7 - i) * BBLACK / 2, author[i].data());
				}
				settextstyle(BBLACK / 4, 0, "����Ҧ��");
				break;
			}
			else if (m.x>WINDOWS_X - BBLACK && m.x<WINDOWS_X - 10 && m.y>WINDOWS_Y - BBLACK / 2 && m.y<WINDOWS_Y - 10 && (_INTRODUCTION || _OPERATION || _ABOUT || _TOINTERNET || _DRMS))					//����
			{
				cleardevice();
				_HOME = false, _INTRODUCTION = false, _OPERATION = false, _ABOUT = false, _TOINTERNET = false, _DRMS = false;
				gameStart();
			}
			else if (m.x>WINDOWS_X / 2 - BBLACK && m.x<WINDOWS_X / 2 + BBLACK && m.y>(int)(WINDOWS_Y / 3 + BBLACK*3.5 + 7 * bblack) && m.y<WINDOWS_Y / 3 + BBLACK * 4 + 7 * bblack && _HOME  && !_INTRODUCTION  && !_OPERATION&&!_ABOUT&&!_TOINTERNET&&!_DRMS)//�˳���Ϸ
			{
				exit(0);
			}
			else break;
		case WM_MOUSEMOVE:									//�ƶ����
			RECT r;
			if (_INTRODUCTION || _OPERATION || _ABOUT || _TOINTERNET || _DRMS)				//�����ǰ������Ϸ���� ����˵�� ���߹��ڽ��� ����������ս���� ���ߵ���ģʽ����
			{
				if (ESCEXIT)gameStart();							//���ֽ��水ESC�˳�
				if (m.x>WINDOWS_X - BBLACK && m.x<WINDOWS_X - 10 && m.y>WINDOWS_Y - BBLACK / 2 && m.y<WINDOWS_Y - 10)
				{
					r.left = WINDOWS_X - BBLACK;
					r.top = WINDOWS_Y - BBLACK / 2;
					r.right = WINDOWS_X - 10;
					r.bottom = WINDOWS_Y - 10;
					POINT points[8] = { { r.left,r.top },{ r.right,r.top },{ r.right,r.bottom },{ r.left,r.bottom } };
					setfillcolor(RED);
					fillpolygon(points, 4);
					setbkmode(TRANSPARENT);
					drawtext("����", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else
				{
					if (getpixel(WINDOWS_X - BBLACK + 1, WINDOWS_Y - BBLACK / 2 + 1) == RED)
					{
						putimage(WINDOWS_X - BBLACK + 1, WINDOWS_Y - BBLACK / 2 + 1, MM + 8);
						setbkmode(TRANSPARENT);
						drawtext("����", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					}
				}
				if (_DRMS)
				{
					for (int i = 0; i < 3; i++)
					{
						if (m.x > WINDOWS_X / 2 - BBLACK && m.x<WINDOWS_X / 2 + BBLACK && m.y>WINDOWS_Y / 3 + BBLACK*i + 2 * i * bblack && m.y < WINDOWS_Y / 3 + BBLACK*i + 2 * i * bblack + BBLACK / 2)
						{
							r.left = WINDOWS_X / 2 - BBLACK;
							r.top = WINDOWS_Y / 3 + BBLACK*i + 2 * i * bblack;
							r.right = WINDOWS_X / 2 + BBLACK;
							r.bottom = WINDOWS_Y / 3 + BBLACK*i + 2 * i * bblack + BBLACK / 2;
							POINT points[8] = { { r.left,r.top },{ r.right,r.top },{ r.right,r.bottom },{ r.left,r.bottom } };
							setfillcolor(RED);
							fillpolygon(points, 4);
							setbkmode(TRANSPARENT);
							switch (i)
							{
							case 0:
								drawtext("��    ��", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
								break;
							case 1:
								drawtext("��    ��", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
								break;
							case 2:
								drawtext("��    ��", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
								break;
							}
						}
						else
						{
							if (getpixel(WINDOWS_X / 2 - BBLACK + 1, WINDOWS_Y / 3 + BBLACK*i + 2 * i * bblack + 1) == RED)
							{
								putimage(WINDOWS_X / 2 - BBLACK, WINDOWS_Y / 3 + BBLACK*i + 2 * i * bblack, MB + i);	//���ԭ��ͼƬ
							}
						}
					}
				}
				if (_TOINTERNET)											//����������
				{
					if (m.x > WINDOWS_X / 4 && m.x<WINDOWS_X / 4 + 2 * BBLACK  && m.y>WINDOWS_Y / 2 + BBLACK && m.y < WINDOWS_Y / 2 + 2 * BBLACK)
					{
						r.left = WINDOWS_X / 4;
						r.top = WINDOWS_Y / 2 + BBLACK;
						r.right = WINDOWS_X / 4 + 2 * BBLACK;
						r.bottom = WINDOWS_Y / 2 + 2 * BBLACK;
						POINT points[8] = { { r.left,r.top },{ r.right,r.top },{ r.right,r.bottom },{ r.left,r.bottom } };
						setfillcolor(RED);
						fillpolygon(points, 4);
						setbkmode(TRANSPARENT);
						drawtext("��Ҫ����", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					}
					else
					{
						if (getpixel(WINDOWS_X / 4 + 1, WINDOWS_Y / 2 + BBLACK + 1) == RED)
						{
							putimage(WINDOWS_X / 4, WINDOWS_Y / 2 + BBLACK, MM + 9);
						}
					}
					if (m.x>WINDOWS_X - WINDOWS_X / 4 - 2 * BBLACK && m.x<WINDOWS_X - WINDOWS_X / 4 && m.y>WINDOWS_Y / 2 + BBLACK && m.y<WINDOWS_Y / 2 + 2 * BBLACK)
					{
						r.left = WINDOWS_X - WINDOWS_X / 4 - 2 * BBLACK;
						r.top = WINDOWS_Y / 2 + BBLACK;
						r.right = WINDOWS_X - WINDOWS_X / 4;
						r.bottom = WINDOWS_Y / 2 + 2 * BBLACK;
						POINT points[8] = { { r.left,r.top },{ r.right,r.top },{ r.right,r.bottom },{ r.left,r.bottom } };
						setfillcolor(RED);
						fillpolygon(points, 4);
						setbkmode(TRANSPARENT);
						drawtext("��Ҫ����", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					}
					else
					{
						if (getpixel(WINDOWS_X - WINDOWS_X / 4 - 2 * BBLACK + 1, WINDOWS_Y / 2 + BBLACK + 1) == RED)
						{
							putimage(WINDOWS_X - WINDOWS_X / 4 - 2 * BBLACK, WINDOWS_Y / 2 + BBLACK, MM + 10);
						}
					}
				}
			}
			else
			{
				for (int i = 0; i<8; i++)
				{
					if (m.x>WINDOWS_X / 2 - BBLACK && m.x<WINDOWS_X / 2 + BBLACK && m.y>WINDOWS_Y / 3 + i*bblack + i*BBLACK / 2 && m.y<WINDOWS_Y / 3 + i*bblack + i*BBLACK / 2 + BBLACK / 2)
					{
						r.left = WINDOWS_X / 2 - BBLACK;
						r.top = WINDOWS_Y / 3 + i*bblack + i*BBLACK / 2;
						r.right = WINDOWS_X / 2 + BBLACK;
						r.bottom = WINDOWS_Y / 3 + i*bblack + i*BBLACK / 2 + BBLACK / 2;
						POINT points[8] = { { r.left,r.top },{ r.right,r.top },{ r.right,r.bottom },{ r.left,r.bottom } };
						setfillcolor(RED);
						fillpolygon(points, 4);
						setbkmode(TRANSPARENT);
						switch (i)
						{
						case 0:
							drawtext("����ģʽ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 1:
							drawtext("˫��ģʽ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 2:
							drawtext("������ս", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 3:
							drawtext("��սģʽ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 4:
							drawtext("��Ϸ����", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 5:
							drawtext("����˵��", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 6:
							drawtext("��    ��", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 7:
							drawtext("�˳���Ϸ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						}
					}
					else
					{
						if (getpixel(WINDOWS_X / 2 - BBLACK + 1, WINDOWS_Y / 3 + i*bblack + i*BBLACK / 2 + 1) == RED)
						{
							putimage(WINDOWS_X / 2 - BBLACK, WINDOWS_Y / 3 + i*bblack + i*BBLACK / 2, MM + i);	//���ԭ��ͼƬ
						}
					}
				}
			}
			FlushBatchDraw();
			break;
		default: break;
		}
	}
	gameStart();
}

int main()
{
	gameStart();					//������
	closegraph();					//�ر�ͼ�λ�����
	return 0;
}
