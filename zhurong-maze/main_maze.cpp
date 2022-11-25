//////////////////////////////////////////////
// �������ƣ��Թ�
// �������ߣ�ף��
// �������䣺211103376@qq.com
// ���뻷����Visual Studio 2017 + EasyX 20180727(beta)
// ����ʱ�䣺2019-2-10
// ����޸ģ�2019-2-13
//
#include <graphics.h>
#include <stack>
#include <vector>
using std::stack;				// ʹ��STL��ջ
using std::vector;				// ʹ��STL����������


// ��Ϸ��Ϣ
#define WIN_WIDTH	400			// ���ڵĿ��(��λ������)
#define WIN_HEIGHT	300			// ���ڵĸ߶�(��λ������)
// !!ע��������������㷨��ԭ�򣬵�ͼ���ֻ��Ϊ����
#define GAME_WIDTH	41			// ��ͼ�Ŀ��(��λ����)
#define GAME_HEIGHT	51			// ��ͼ�ĸ߶�(��λ����)

#define WALL		1			// ǽ�ڵ����ֱ��
#define GROUND		0			// ��������ֱ��
#define FILLSTATE	2			// ����վ�����ֱ��
#define ENDPOS		3			// �յ�����ֱ��

#define MAXVIEW		8.0			// ������Ұ
#define MINVIEW		1			// ��С����Ұ
#define FILLNUM		10			// ����վ������
#define DARKTIME	12			// ��Ұ�½�1ͼ�������ʱ��

// ȫ�ֱ����б�
int		g_BlockSize;			// ���С
int		g_GameMap[GAME_HEIGHT][GAME_WIDTH];	// ��ͼ(��ߵ�λΪ��)
POINT	g_EndPos;				// �յ�λ��
POINT   g_PlayerPos;			// ����ڵ�ͼ�ϵ�λ��
POINT	g_CameraPos;			// �����(��Ļ���Ͻ�)�ڵ�ͼ�ϵ�λ��
IMAGE	g_MapImage;				// ��ͼ��ͼƬ(���ڵ�ͼ�ǹ̶��ģ��ڲ��ı����ŵ������ֻ��Ҫ����һ��)
double	g_ViewArray;			// ��Ұ
UINT	g_BeginTime;			// ��Ϸ��ʼʱ��ʱ��
UINT	g_LastFillTime;			// �ϴ�Ϊ�͵Ƽ��͵�ʱ��


// �����б�
void initGame();				// ��ʼ����Ϸ
void endGame();					// ������Ϸ
void draw();					// ���ƺ���
bool upDate();					// ���ݸ��º���
void absDelay(int delay);		// �����ӳ�

bool canMove(POINT pos);		// �ж�ĳ��λ���Ƿ�����ƶ�
void computeCameraPos();		// ����������ڵ�ͼ�ϵ�λ��
void rePaintMap();				// �ػ��ͼ

void drawWall(POINT pos);		// ����ǽ��ͼ��ĺ���
void drawGround(POINT pos);		// ���Ƶ���ͼ��ĺ���
void drawFillState(POINT pos);	// �����͵�ͼ��ĺ���
void drawEndPos(POINT pos);		// �����յ�
void drawPlayer();				// ��������ĺ���
void drawView();				// ������Ұ

int main()
{
	initGame();

	while (1)
	{
		if (!upDate()) break;	// ����
		draw();					// ����
		absDelay(16);			// �����ӳ� 16 ���룬����ÿ�� 60 ֡
	}

	endGame();
	return 0;
}

void initGame()
{
	g_BlockSize = 32;			// ��ʼͼ���СΪ 32 ������
	srand(GetTickCount());		// ��ʼ�����������

	// ��ʼ�������
	for (int i = 0; i < GAME_HEIGHT; i++)
	{
		for (int j = 0; j < GAME_WIDTH; j++)
		{
			if (i % 2 == 0 || j % 2 == 0)	// ��������������Ϊǽ��
				g_GameMap[i][j] = WALL;
			else
				g_GameMap[i][j] = GROUND;
		}
	}

	// ������ɵ�ͼ(ʹ��������ȱ���)
	stack<POINT> stepStack;		// ����ջ
	vector<POINT>  stepPoint;	// ���ܵĵ�
	POINT nowPoint;				// ��ǰ�������ڵ�
	stepStack.push({ 1, 1 });	// д���ʼ�� (1,1) ��Ϊ���
	nowPoint = { 1, 1 };
	g_GameMap[1][1] = 0xFFFF;	// ��������
	while (!stepStack.empty())	// ֻҪ����ջ���վͼ���ѭ��
	{
		// �õ����ܵĵ�
		POINT tempPoint;
		for (int i = -1; i <= 1; i += 2)
		{
			tempPoint = { nowPoint.x, nowPoint.y + i * 2 };	// �����
			// �ж������Ƿ�Ϸ�
			if (tempPoint.x >= 0 && tempPoint.x <= GAME_WIDTH - 1 &&
				tempPoint.y >= 0 && tempPoint.y <= GAME_HEIGHT - 1 &&
				g_GameMap[tempPoint.y][tempPoint.x] != 0xFFFF)
			{
				stepPoint.push_back(tempPoint);
			}
			tempPoint = { nowPoint.x + i * 2, nowPoint.y };	// �����
			// �ж������Ƿ�Ϸ�
			if (tempPoint.x >= 0 && tempPoint.x <= GAME_WIDTH - 1 &&
				tempPoint.y >= 0 && tempPoint.y <= GAME_HEIGHT - 1 &&
				g_GameMap[tempPoint.y][tempPoint.x] != 0xFFFF)
			{
				stepPoint.push_back(tempPoint);
			}
		}

		// ������Χ�����ѡ�����
		if (stepPoint.empty())				// �����Χ�㶼����������
		{
			stepStack.pop();				// ��ջ��ǰ��
			if (!stepStack.empty())
				nowPoint = stepStack.top();	// ���µ�ǰ��
		}
		else
		{
			stepStack.push(stepPoint[rand() % stepPoint.size()]);	// ��ջ��ǰ��
			g_GameMap[(nowPoint.y + stepStack.top().y) / 2][(nowPoint.x + stepStack.top().x) / 2] = 0;	// ��ͨǽ��
			nowPoint = stepStack.top();		// ���µ�ǰ��
			g_GameMap[nowPoint.y][nowPoint.x] = 0xFFFF;				// ��ǵ�ǰ��
		}
		stepPoint.clear();					// �����Χ���Ա���һ��ѭ��
	}

	// ��ϴ��ǵ�
	for (int i = 0; i < GAME_HEIGHT; i++)
	{
		for (int j = 0; j < GAME_WIDTH; j++)
		{
			if (g_GameMap[i][j] == 0xFFFF)
				g_GameMap[i][j] = 0;
		}
	}

	// ������ɼ���վ��λ��
	for (int i = 0; i < FILLNUM; i++)
	{
		POINT fillPoint = { rand() % GAME_WIDTH, rand() % GAME_HEIGHT };
		// ��֤�ڿյ����ɼ���վ
		while (g_GameMap[fillPoint.y][fillPoint.x] != GROUND)
			fillPoint = { rand() % GAME_WIDTH, rand() % GAME_HEIGHT };
		// ����͵�
		g_GameMap[fillPoint.y][fillPoint.x] = FILLSTATE;
	}

	g_GameMap[GAME_HEIGHT - 2][GAME_WIDTH - 2] = ENDPOS;		// ����յ�
	g_EndPos = { GAME_WIDTH - 2, GAME_HEIGHT - 2 };				// ȷ���յ�λ��
	g_ViewArray = MAXVIEW;				// ��ʼ��Ұ������
	g_BeginTime = GetTickCount();		// ��ʼ��ʱ
	g_LastFillTime = GetTickCount();	// �͵Ƽ��͵�ʱ��
	rePaintMap();						// ���Ƶ�ͼ
	g_PlayerPos = { g_BlockSize * 3 / 2, g_BlockSize * 3 / 2 };	// ��ʼ���˵�λ��
	computeCameraPos();					// �����������λ��
	initgraph(WIN_WIDTH, WIN_HEIGHT);	// ��ʼ������
	setbkmode(TRANSPARENT);				// ���ñ���Ϊ͸��
	BeginBatchDraw();					// ��ʼ�������
}

void endGame()
{
	EndBatchDraw();						// �����������
	closegraph();						// �رջ���
}

void draw()
{
	// ����豸
	cleardevice();
	// ������Ұ
	drawView();
	// ������
	drawPlayer();
	// ����ʱ��
	TCHAR timeStr[256];
	int loseTime = GetTickCount() - g_BeginTime;	// ������ʧ��ʱ��
	_stprintf_s(timeStr, _T("��Ϸʱ��:%02d:%02d"), loseTime / 1000 / 60, loseTime / 1000 % 60);
	settextcolor(RGB(140, 140, 140));
	outtextxy((WIN_WIDTH - textwidth(timeStr)) / 2, 3, timeStr);

	FlushBatchDraw();	// ˢ����Ļ
}

bool upDate()
{
	POINT nextPos = g_PlayerPos;		// ��һ��λ��

	// ������һ��λ��
	if (GetKeyState(VK_UP) & 0x8000)	nextPos.y -= 2;
	if (GetKeyState(VK_DOWN) & 0x8000)	nextPos.y += 2;
	if (GetKeyState(VK_LEFT) & 0x8000)	nextPos.x -= 2;
	if (GetKeyState(VK_RIGHT) & 0x8000)	nextPos.x += 2;

	// �����һ��λ�ò��Ϸ�
	if (!canMove(nextPos))
	{
		if (canMove({ g_PlayerPos.x, nextPos.y }))		// y ���ƶ��Ϸ�
			nextPos = { g_PlayerPos.x, nextPos.y };
		else if (canMove({ nextPos.x, g_PlayerPos.y }))	// x ���ƶ��Ϸ�
			nextPos = { nextPos.x, g_PlayerPos.y };
		else											// �����Ϸ�
			nextPos = g_PlayerPos;
	}

	// ������͵������ʱ��
	if (g_GameMap[nextPos.y / g_BlockSize][nextPos.x / g_BlockSize] == FILLSTATE)
		g_LastFillTime = GetTickCount();
	// ������յ���ͨ��
	else if (g_GameMap[nextPos.y / g_BlockSize][nextPos.x / g_BlockSize] == ENDPOS)
	{
		outtextxy(WIN_WIDTH / 2 - 40, WIN_HEIGHT / 2 - 12, _T("��ϲ���أ�"));
		FlushBatchDraw();
		Sleep(1000);
		return false;
	}
	g_PlayerPos = nextPos;						// ����λ��
	computeCameraPos();							// �����������λ��

	// ����ʱ��������Ұ
	static unsigned int lastTime = GetTickCount();
	int loseTime = GetTickCount() - g_LastFillTime;			// ������ʧ��ʱ��
	g_ViewArray = MAXVIEW - loseTime / 1000.0 / DARKTIME;	// ÿһ��ʱ���͵Ƶ����������½�һ��ͼ��
	if (g_ViewArray < MINVIEW) g_ViewArray = MINVIEW;

	// ���������Ϣ
	MOUSEMSG mouseMsg;							// �����Ϣ
	int lastBlockSize = g_BlockSize;			// ����ԭ���Ĵ�С
	while (MouseHit())
	{
		mouseMsg = GetMouseMsg();
		if (mouseMsg.uMsg = WM_MOUSEWHEEL)		// ������Ϣ
		{
			g_BlockSize += mouseMsg.wheel / 120;
		}
	}

	// ���û�й�����Ϣ���˳�
	if (lastBlockSize == g_BlockSize) return true;
	// ���������Ϣ
	if (g_BlockSize >= 10 && g_BlockSize <= 50)	// ���Сû�дﵽ����ֵ
	{
		// ��֤���ź�ĵ�ͼ����ȴ���С
		if (GAME_WIDTH * g_BlockSize < WIN_WIDTH ||
			GAME_HEIGHT * g_BlockSize < WIN_HEIGHT)
			g_BlockSize = lastBlockSize;
		rePaintMap();							// �ػ��ͼ
		// ���¼�������ڵ�ͼ�ϵ�λ��
		POINT mapPos = { g_PlayerPos.x / lastBlockSize, g_PlayerPos.y / lastBlockSize };	// �����ڵ�ͼ�ϵ�λ��
		g_PlayerPos.x = mapPos.x * g_BlockSize + g_BlockSize / 2;	// ����ӳ����λ��
		g_PlayerPos.y = mapPos.y * g_BlockSize + g_BlockSize / 2;	// ����ӳ����λ��
		computeCameraPos();						// ���¼��������λ��
	}
	// ��֤ͼ�鲻�����͹�С
	if (g_BlockSize < 10) g_BlockSize = 10;
	if (g_BlockSize > 50) g_BlockSize = 50;

	return true;
}

void absDelay(int delay)
{
	static int curtime = GetTickCount();
	static int pretime = GetTickCount();
	while (curtime - pretime < delay)
	{
		curtime = GetTickCount();
		Sleep(1);
	}
	pretime = curtime;
}

bool canMove(POINT pos)
{
	// ֻҪ��Ӿ��ε��ĸ����㲻��ǽ���ھͱض��Ϸ�
	return	g_GameMap[(pos.y - 3) / g_BlockSize][(pos.x - 3) / g_BlockSize] != WALL &&
		g_GameMap[(pos.y + 3) / g_BlockSize][(pos.x + 3) / g_BlockSize] != WALL &&
		g_GameMap[(pos.y - 3) / g_BlockSize][(pos.x + 3) / g_BlockSize] != WALL &&
		g_GameMap[(pos.y + 3) / g_BlockSize][(pos.x - 3) / g_BlockSize] != WALL;
}

void computeCameraPos()
{
	// ������λ��Ϊ���ļ��������������λ��
	g_CameraPos.x = g_PlayerPos.x - WIN_WIDTH / 2;
	g_CameraPos.y = g_PlayerPos.y - WIN_HEIGHT / 2;

	// ��ֹ�����Խ��
	if (g_CameraPos.x < 0)										g_CameraPos.x = 0;
	if (g_CameraPos.y < 0)										g_CameraPos.y = 0;
	if (g_CameraPos.x > GAME_WIDTH * g_BlockSize - WIN_WIDTH)	g_CameraPos.x = GAME_WIDTH * g_BlockSize - WIN_WIDTH;
	if (g_CameraPos.y > GAME_HEIGHT * g_BlockSize - WIN_HEIGHT)	g_CameraPos.y = GAME_HEIGHT * g_BlockSize - WIN_HEIGHT;
}

void rePaintMap()
{
	g_MapImage.Resize(GAME_WIDTH * g_BlockSize, GAME_HEIGHT * g_BlockSize);	// ���õ�ͼͼƬ��С
	SetWorkingImage(&g_MapImage);								// ���õ�ͼͼƬΪ��ǰ����ͼƬ
	for (int i = 0; i < GAME_HEIGHT; i++)
	{
		for (int j = 0; j < GAME_WIDTH; j++)
		{
			switch (g_GameMap[i][j])
			{
			case WALL:
				drawWall({ j*g_BlockSize, i*g_BlockSize });		// ����ǽ��
				break;
			case FILLSTATE:
				drawFillState({ j*g_BlockSize, i*g_BlockSize });	// ���Ƽ���վ
				break;
			case GROUND:
				drawGround({ j*g_BlockSize, i*g_BlockSize });	// ���Ƶ���
				break;
			case ENDPOS:
				drawEndPos({ j*g_BlockSize, i*g_BlockSize });
				break;
			}
		}
	}
	SetWorkingImage();	// ��λ����ͼƬ
}

void drawWall(POINT pos)
{
	setfillcolor(RGB(254, 109, 19));
	solidrectangle(pos.x, pos.y, pos.x + g_BlockSize, pos.y + g_BlockSize);
}

void drawGround(POINT pos)
{
	setfillcolor(RGB(255, 255, 255));
	solidrectangle(pos.x, pos.y, pos.x + g_BlockSize, pos.y + g_BlockSize);
}

void drawFillState(POINT pos)
{
	drawGround(pos);

	// ����Բ�Ǿ���
	pos.x += g_BlockSize / 5;
	pos.y += g_BlockSize / 5;
	setfillcolor(RGB(252, 213, 11));
	solidroundrect(pos.x, pos.y, pos.x + g_BlockSize / 5 * 3, pos.y + g_BlockSize / 5 * 3, g_BlockSize / 8, g_BlockSize / 8);
}

void drawEndPos(POINT pos)
{
	drawGround(pos);

	// ����Բ�Ǿ���
	pos.x += g_BlockSize / 5;
	pos.y += g_BlockSize / 5;
	setfillcolor(RGB(87, 116, 48));
	solidroundrect(pos.x, pos.y, pos.x + g_BlockSize / 5 * 3, pos.y + g_BlockSize / 5 * 3, g_BlockSize / 8, g_BlockSize / 8);
}

void drawPlayer()
{
	setfillcolor(RGB(252, 213, 11));
	solidcircle(g_PlayerPos.x - g_CameraPos.x, g_PlayerPos.y - g_CameraPos.y, 3);
}

void drawView()
{
	// ������Ұ
	HRGN viewArr;
	int r = int(g_BlockSize * g_ViewArray + 0.5);	// ������Ұ�뾶
	POINT orgin = g_PlayerPos;
	orgin.x -= g_CameraPos.x;						// ��������Ļ�ϵ�λ��
	orgin.y -= g_CameraPos.y;						// ��������Ļ�ϵ�λ��
	viewArr = CreateEllipticRgn(orgin.x - r, orgin.y - r, orgin.x + r, orgin.y + r);	// ����һ��Բ�ε�����
	setcliprgn(viewArr);							// ��������

	// ���Ƶ�ͼ
	putimage(0, 0, WIN_WIDTH, WIN_HEIGHT, &g_MapImage, g_CameraPos.x, g_CameraPos.y);

	// ɾ������
	DeleteObject(viewArr);
	// ��������
	setcliprgn(NULL);
}