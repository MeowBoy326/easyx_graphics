/////////////////////////////////////////////////////////
// �������ƣ�Χס��è
// ���뻷��  Visual Studio2019(C++���Ա�׼ѡ��C++17),EasyX
// ���ߣ��ײ���<508222866@qq.com> <QQ:508222866>
// ����޸ģ�2020-5-26

#include <graphics.h>
#include <queue>
#include <cstring>
#include <ctime>
#include <vector>

#pragma comment( lib, "MSIMG32.LIB")
#define pix		 50			// ���ر���
#define hight	(14 * pix)
#define width	(10 * pix)
using namespace std;

int stepS;					// ��¼�Ѿ��ߵĲ���
int startBarrier;			// ��ʼ���ϰ�����Ŀ
wchar_t Score_[30];
MOUSEMSG m;					// ������
IMAGE pig, bkimg;;			// ����ͼƬ


enum class picture
{
	none, barrier
};

struct XY
{
	int x, y;
	int lastX, lastY;	//��¼��һ���������
}cat;

struct node
{
	int x, y;			//����,Բ��λ��
	picture pic;		//��ǰλ�õ�ͼƬ����
};

node canvas[10][10];	//  ��ͼ
bool visit[10][10];		//	��¼�Ƿ���ʹ���ͼ�е�Ԫ��
int path[10][10][2];	//  ��¼��һ��λ��


//ע�⣺��Ϊ��ͼ�ǽ������еģ���������ż����è���ƶ���ͬ
int dirOdd[6][2]{ 1, 0, -1, 0, 0, 1, 0, -1, -1, -1, -1, 1 };	//���Ʒ���������
int dirEven[6][2]{ 1, 0, -1, 0, 0, 1, 0, -1, 1, -1, 1, 1 };	//���Ʒ���ż����

int main();

//��ͼ����
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, int direction)
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = 50;
	int h = 100;

	// ʹ�� Windows GDI ����ʵ��͸��λͼ
	if (direction == 0)
		TransparentBlt(dstDC, x, y, w, h, srcDC, 0, 0, w, h, 0);
	else
		TransparentBlt(dstDC, x, y, w, h, srcDC, 10, 187, w, h, 0);
}

//��Ϸ��ʼ��
void initial()
{
	srand(time(0));
	stepS = 0;
	startBarrier = rand() % 6 + 8;	//�ϰ�������
	loadimage(&pig, L"pig.png");
	loadimage(&bkimg, L"bkground.jpg", width, hight, true);
	initgraph(width, hight);
	HWND wnd = GetHWnd();
	SetWindowText(wnd, L"Χס��è");//�������±���
	for (int i = 1; i <= 9; ++i)
		for (int j = 1; j <= 9; ++j)
		{
			if (i & 1)	//�����������
				canvas[i][j] = node{ j * pix - pix / 4, pix * 4 + i * pix, picture::none };
			else
				canvas[i][j] = node{ j * pix + pix / 4, pix * 4 + i * pix, picture::none };
		}

	cat.x = 5; cat.y = 5;	//è�ʼ�ĵط�
	while (startBarrier--)
	{
		int bx, by;			//���ó�ʼ�ϰ�
		do
		{
			bx = rand() % 10;
			by = rand() % 10;
		} while (canvas[by][bx].pic == picture::barrier || (by == cat.y && bx == cat.x));
		canvas[by][bx].pic = picture::barrier;
	}
	setbkmode(TRANSPARENT);
	BeginBatchDraw();
}


//������Ϸ����, ��ɫ����  ��ɫ���ϰ��� 
void show()
{
	putimage(0, 0, &bkimg);
	setbkcolor(WHITE);
	settextstyle(20, 0, L"΢���ź�");
	outtextxy(200, 170, L"����");
	outtextxy(250, 180, L"����: ");
	swprintf(Score_, 29, L"%d", stepS);
	outtextxy(290, 180, Score_);
	for (int i = 1; i <= 9; ++i)
	{
		for (int j = 1; j <= 9; ++j)
		{
			if (canvas[i][j].pic == picture::barrier)
				setfillcolor(YELLOW);
			else
				setfillcolor(LIGHTGRAY);
			solidcircle(canvas[i][j].x, canvas[i][j].y, (pix - 4) / 2);
		}
	}
	if (cat.y & 1)	//������
		transparentimage(NULL, cat.x * pix - pix / 4 - 25, pix * 3 + cat.y * pix - 21, &pig, 0);
	else			//ż����
		transparentimage(NULL, cat.x * pix - 25 + pix / 4, pix * 3 + cat.y * pix - 21, &pig, 1);
	FlushBatchDraw();
}


//Ѱ����һ�����λ��
struct LastOrder
{
	int x, y;
};

vector<LastOrder> vec;

void findNextXY(int x, int y)
{
	if (x == cat.x && y == cat.y)
	{
		vec.push_back({ x, y });
		return;
	}
	else
	{
		findNextXY(path[y][x][0], path[y][x][1]);
		vec.push_back({ x, y });
	}
}


//���ù���������������·����xyΪ�����i,j�±꣬ע�⴫��
void bfs(XY xy)
{
	//ÿ������ʱ��ʼ������
	memset(visit, false, sizeof(visit));
	memset(path, 0, sizeof(path));
	bool tag = true;
	queue<XY> que;
	que.push(xy);
	visit[xy.y][xy.x] = true;
	while (!que.empty())
	{
		XY temp = que.front();
		que.pop();
		//����ҵ�����
		if (temp.x == 1 || temp.x == 9 || temp.y == 1 || temp.y == 9)
		{
			findNextXY(temp.x, temp.y);
			cat.x = vec[1].x;
			cat.y = vec[1].y;
			vec.clear();
			tag = false;
			break;
		}
		int dx, dy;
		//Ѱ�ҿ��ߵ�·
		for (int i = 0; i < 6; ++i)
		{
			if (temp.y & 1)
			{
				dx = temp.x + dirOdd[i][0];
				dy = temp.y + dirOdd[i][1];
			}
			else
			{
				dx = temp.x + dirEven[i][0];
				dy = temp.y + dirEven[i][1];
			}
			if (dx >= 1 && dx <= 9 && dy >= 1 && dy <= 9 && !visit[dy][dx] && canvas[dy][dx].pic == picture::none)
			{
				visit[dy][dx] = true;
				path[dy][dx][0] = temp.x;
				path[dy][dx][1] = temp.y;
				que.push({ dx, dy, temp.x, temp.y });
			}
		}
	}
	if (tag)					//���û�ҵ�����
	{
		show();
		HWND wnd = GetHWnd();
		swprintf(Score_, 29, L"�㹲����%d��������һ����", stepS);
		FlushBatchDraw();
		if (MessageBox(wnd, Score_, L"�ɹ�", MB_YESNO | MB_ICONQUESTION) == IDYES)
			main();
		else
			exit(-1);
	}
}


//������
void dataChangeWithMouseHit()
{
	while (true)
	{
		m = GetMouseMsg();
		if (m.x >= 200 && m.x <= 230 && m.y >= 170 && m.y <= 200)
			settextcolor(BLACK);
		else
			settextcolor(WHITE);
		outtextxy(200, 170, L"����");
		FlushBatchDraw();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (m.x >= 200 && m.x <= 230 && m.y >= 170 && m.y <= 200)
				main();
			for (int i = 1; i <= 9; ++i)
				for (int j = 1; j <= 9; ++j)
					//����ڵ�ǰ������,��ı���Ϣ
					if (canvas[i][j].pic != picture::barrier && (m.x - canvas[i][j].x) * (m.x - canvas[i][j].x) +
						(m.y - canvas[i][j].y) * (m.y - canvas[i][j].y) <= (pix - 4) * (pix - 4) / 4)
					{
						canvas[i][j].pic = picture::barrier;
						stepS++;
						bfs({ cat.x, cat.y, 0, 0 });
						return;
					}
		}
	}
}


//����Ҫ���Ĳ������ж�è�Ƿ��ܵ�
void dataChangeWithoutMouseHit()
{
	if (cat.x == 1 || cat.y == 1 || cat.x == 9 || cat.y == 9)
	{
		show();
		HWND wnd = GetHWnd();
		if (MessageBox(wnd, L"��Ϸ������\n��è�ܵ��ˣ�,����һ����", L"ѯ��", MB_YESNO | MB_ICONQUESTION) == IDYES)
			main();
		else
			exit(-1);
	}
}


int main()
{
	initial();
	while (true)
	{
		show();
		dataChangeWithMouseHit();
		dataChangeWithoutMouseHit();
		Sleep(20);
	}
	return 0;
}