//////////////////////////////////////////////
// 程序名称：迷宫
// 程序作者：祝融
// 作者邮箱：211103376@qq.com
// 编译环境：Visual Studio 2017 + EasyX 20180727(beta)
// 发布时间：2019-2-10
// 最后修改：2019-2-13
//
#include <graphics.h>
#include <stack>
#include <vector>
using std::stack;				// 使用STL的栈
using std::vector;				// 使用STL的数组容器


// 游戏信息
#define WIN_WIDTH	400			// 窗口的宽度(单位：像素)
#define WIN_HEIGHT	300			// 窗口的高度(单位：像素)
// !!注：由于随机生成算法的原因，地图宽高只能为奇数
#define GAME_WIDTH	41			// 地图的宽度(单位：块)
#define GAME_HEIGHT	51			// 地图的高度(单位：块)

#define WALL		1			// 墙壁的数字标记
#define GROUND		0			// 地面的数字标记
#define FILLSTATE	2			// 加油站的数字标记
#define ENDPOS		3			// 终点的数字标记

#define MAXVIEW		8.0			// 最大的视野
#define MINVIEW		1			// 最小的视野
#define FILLNUM		10			// 加油站的数量
#define DARKTIME	12			// 视野下降1图块所需的时间

// 全局变量列表
int		g_BlockSize;			// 块大小
int		g_GameMap[GAME_HEIGHT][GAME_WIDTH];	// 地图(宽高单位为块)
POINT	g_EndPos;				// 终点位置
POINT   g_PlayerPos;			// 玩家在地图上的位置
POINT	g_CameraPos;			// 摄像机(屏幕左上角)在地图上的位置
IMAGE	g_MapImage;				// 地图的图片(由于地图是固定的，在不改变缩放的情况下只需要绘制一次)
double	g_ViewArray;			// 视野
UINT	g_BeginTime;			// 游戏开始时的时间
UINT	g_LastFillTime;			// 上次为油灯加油的时间


// 函数列表
void initGame();				// 初始化游戏
void endGame();					// 结束游戏
void draw();					// 绘制函数
bool upDate();					// 数据更新函数
void absDelay(int delay);		// 绝对延迟

bool canMove(POINT pos);		// 判断某个位置是否可以移动
void computeCameraPos();		// 计算摄像机在地图上的位置
void rePaintMap();				// 重绘地图

void drawWall(POINT pos);		// 绘制墙壁图块的函数
void drawGround(POINT pos);		// 绘制地面图块的函数
void drawFillState(POINT pos);	// 绘制油灯图块的函数
void drawEndPos(POINT pos);		// 绘制终点
void drawPlayer();				// 绘制人物的函数
void drawView();				// 绘制视野

int main()
{
	initGame();

	while (1)
	{
		if (!upDate()) break;	// 更新
		draw();					// 绘制
		absDelay(16);			// 绝对延迟 16 毫秒，控制每秒 60 帧
	}

	endGame();
	return 0;
}

void initGame()
{
	g_BlockSize = 32;			// 初始图块大小为 32 个像素
	srand(GetTickCount());		// 初始化随机数生成

	// 初始化间隔室
	for (int i = 0; i < GAME_HEIGHT; i++)
	{
		for (int j = 0; j < GAME_WIDTH; j++)
		{
			if (i % 2 == 0 || j % 2 == 0)	// 奇数行奇数列设为墙壁
				g_GameMap[i][j] = WALL;
			else
				g_GameMap[i][j] = GROUND;
		}
	}

	// 随机生成地图(使用深度优先遍历)
	stack<POINT> stepStack;		// 步骤栈
	vector<POINT>  stepPoint;	// 四周的点
	POINT nowPoint;				// 当前步的所在点
	stepStack.push({ 1, 1 });	// 写入初始点 (1,1) 作为起点
	nowPoint = { 1, 1 };
	g_GameMap[1][1] = 0xFFFF;	// 标记这个点
	while (!stepStack.empty())	// 只要步骤栈不空就继续循环
	{
		// 得到四周的点
		POINT tempPoint;
		for (int i = -1; i <= 1; i += 2)
		{
			tempPoint = { nowPoint.x, nowPoint.y + i * 2 };	// 计算点
			// 判断坐标是否合法
			if (tempPoint.x >= 0 && tempPoint.x <= GAME_WIDTH - 1 &&
				tempPoint.y >= 0 && tempPoint.y <= GAME_HEIGHT - 1 &&
				g_GameMap[tempPoint.y][tempPoint.x] != 0xFFFF)
			{
				stepPoint.push_back(tempPoint);
			}
			tempPoint = { nowPoint.x + i * 2, nowPoint.y };	// 计算点
			// 判断坐标是否合法
			if (tempPoint.x >= 0 && tempPoint.x <= GAME_WIDTH - 1 &&
				tempPoint.y >= 0 && tempPoint.y <= GAME_HEIGHT - 1 &&
				g_GameMap[tempPoint.y][tempPoint.x] != 0xFFFF)
			{
				stepPoint.push_back(tempPoint);
			}
		}

		// 根据周围点的量选择操作
		if (stepPoint.empty())				// 如果周围点都被遍历过了
		{
			stepStack.pop();				// 出栈当前点
			if (!stepStack.empty())
				nowPoint = stepStack.top();	// 更新当前点
		}
		else
		{
			stepStack.push(stepPoint[rand() % stepPoint.size()]);	// 入栈当前点
			g_GameMap[(nowPoint.y + stepStack.top().y) / 2][(nowPoint.x + stepStack.top().x) / 2] = 0;	// 打通墙壁
			nowPoint = stepStack.top();		// 更新当前点
			g_GameMap[nowPoint.y][nowPoint.x] = 0xFFFF;				// 标记当前点
		}
		stepPoint.clear();					// 清空周围点以便下一次循环
	}

	// 清洗标记点
	for (int i = 0; i < GAME_HEIGHT; i++)
	{
		for (int j = 0; j < GAME_WIDTH; j++)
		{
			if (g_GameMap[i][j] == 0xFFFF)
				g_GameMap[i][j] = 0;
		}
	}

	// 随机生成加油站的位置
	for (int i = 0; i < FILLNUM; i++)
	{
		POINT fillPoint = { rand() % GAME_WIDTH, rand() % GAME_HEIGHT };
		// 保证在空地生成加油站
		while (g_GameMap[fillPoint.y][fillPoint.x] != GROUND)
			fillPoint = { rand() % GAME_WIDTH, rand() % GAME_HEIGHT };
		// 标记油灯
		g_GameMap[fillPoint.y][fillPoint.x] = FILLSTATE;
	}

	g_GameMap[GAME_HEIGHT - 2][GAME_WIDTH - 2] = ENDPOS;		// 标记终点
	g_EndPos = { GAME_WIDTH - 2, GAME_HEIGHT - 2 };				// 确定终点位置
	g_ViewArray = MAXVIEW;				// 初始视野是最大的
	g_BeginTime = GetTickCount();		// 开始计时
	g_LastFillTime = GetTickCount();	// 油灯加油的时间
	rePaintMap();						// 绘制地图
	g_PlayerPos = { g_BlockSize * 3 / 2, g_BlockSize * 3 / 2 };	// 初始化人的位置
	computeCameraPos();					// 计算摄像机的位置
	initgraph(WIN_WIDTH, WIN_HEIGHT);	// 初始化画布
	setbkmode(TRANSPARENT);				// 设置背景为透明
	BeginBatchDraw();					// 开始缓冲绘制
}

void endGame()
{
	EndBatchDraw();						// 结束缓冲绘制
	closegraph();						// 关闭画布
}

void draw()
{
	// 清空设备
	cleardevice();
	// 绘制视野
	drawView();
	// 绘制人
	drawPlayer();
	// 绘制时间
	TCHAR timeStr[256];
	int loseTime = GetTickCount() - g_BeginTime;	// 计算流失的时间
	_stprintf_s(timeStr, _T("游戏时间:%02d:%02d"), loseTime / 1000 / 60, loseTime / 1000 % 60);
	settextcolor(RGB(140, 140, 140));
	outtextxy((WIN_WIDTH - textwidth(timeStr)) / 2, 3, timeStr);

	FlushBatchDraw();	// 刷新屏幕
}

bool upDate()
{
	POINT nextPos = g_PlayerPos;		// 下一个位置

	// 计算下一个位置
	if (GetKeyState(VK_UP) & 0x8000)	nextPos.y -= 2;
	if (GetKeyState(VK_DOWN) & 0x8000)	nextPos.y += 2;
	if (GetKeyState(VK_LEFT) & 0x8000)	nextPos.x -= 2;
	if (GetKeyState(VK_RIGHT) & 0x8000)	nextPos.x += 2;

	// 如果下一个位置不合法
	if (!canMove(nextPos))
	{
		if (canMove({ g_PlayerPos.x, nextPos.y }))		// y 轴移动合法
			nextPos = { g_PlayerPos.x, nextPos.y };
		else if (canMove({ nextPos.x, g_PlayerPos.y }))	// x 轴移动合法
			nextPos = { nextPos.x, g_PlayerPos.y };
		else											// 都不合法
			nextPos = g_PlayerPos;
	}

	// 如果是油灯则更新时间
	if (g_GameMap[nextPos.y / g_BlockSize][nextPos.x / g_BlockSize] == FILLSTATE)
		g_LastFillTime = GetTickCount();
	// 如果是终点则通关
	else if (g_GameMap[nextPos.y / g_BlockSize][nextPos.x / g_BlockSize] == ENDPOS)
	{
		outtextxy(WIN_WIDTH / 2 - 40, WIN_HEIGHT / 2 - 12, _T("恭喜过关！"));
		FlushBatchDraw();
		Sleep(1000);
		return false;
	}
	g_PlayerPos = nextPos;						// 更新位置
	computeCameraPos();							// 计算摄像机的位置

	// 根据时间缩减视野
	static unsigned int lastTime = GetTickCount();
	int loseTime = GetTickCount() - g_LastFillTime;			// 计算流失的时间
	g_ViewArray = MAXVIEW - loseTime / 1000.0 / DARKTIME;	// 每一段时间油灯的照明力会下降一个图块
	if (g_ViewArray < MINVIEW) g_ViewArray = MINVIEW;

	// 处理鼠标消息
	MOUSEMSG mouseMsg;							// 鼠标信息
	int lastBlockSize = g_BlockSize;			// 保存原本的大小
	while (MouseHit())
	{
		mouseMsg = GetMouseMsg();
		if (mouseMsg.uMsg = WM_MOUSEWHEEL)		// 滚轮消息
		{
			g_BlockSize += mouseMsg.wheel / 120;
		}
	}

	// 如果没有滚轮消息就退出
	if (lastBlockSize == g_BlockSize) return true;
	// 处理滚轮消息
	if (g_BlockSize >= 10 && g_BlockSize <= 50)	// 块大小没有达到极限值
	{
		// 保证缩放后的地图不会比窗口小
		if (GAME_WIDTH * g_BlockSize < WIN_WIDTH ||
			GAME_HEIGHT * g_BlockSize < WIN_HEIGHT)
			g_BlockSize = lastBlockSize;
		rePaintMap();							// 重绘地图
		// 重新计算玩家在地图上的位置
		POINT mapPos = { g_PlayerPos.x / lastBlockSize, g_PlayerPos.y / lastBlockSize };	// 计算在地图上的位置
		g_PlayerPos.x = mapPos.x * g_BlockSize + g_BlockSize / 2;	// 计算映射后的位置
		g_PlayerPos.y = mapPos.y * g_BlockSize + g_BlockSize / 2;	// 计算映射后的位置
		computeCameraPos();						// 重新计算摄像机位置
	}
	// 保证图块不会过大和过小
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
	// 只要外接矩形的四个顶点不在墙壁内就必定合法
	return	g_GameMap[(pos.y - 3) / g_BlockSize][(pos.x - 3) / g_BlockSize] != WALL &&
		g_GameMap[(pos.y + 3) / g_BlockSize][(pos.x + 3) / g_BlockSize] != WALL &&
		g_GameMap[(pos.y - 3) / g_BlockSize][(pos.x + 3) / g_BlockSize] != WALL &&
		g_GameMap[(pos.y + 3) / g_BlockSize][(pos.x - 3) / g_BlockSize] != WALL;
}

void computeCameraPos()
{
	// 以人物位置为中心计算摄像机的理论位置
	g_CameraPos.x = g_PlayerPos.x - WIN_WIDTH / 2;
	g_CameraPos.y = g_PlayerPos.y - WIN_HEIGHT / 2;

	// 防止摄像机越界
	if (g_CameraPos.x < 0)										g_CameraPos.x = 0;
	if (g_CameraPos.y < 0)										g_CameraPos.y = 0;
	if (g_CameraPos.x > GAME_WIDTH * g_BlockSize - WIN_WIDTH)	g_CameraPos.x = GAME_WIDTH * g_BlockSize - WIN_WIDTH;
	if (g_CameraPos.y > GAME_HEIGHT * g_BlockSize - WIN_HEIGHT)	g_CameraPos.y = GAME_HEIGHT * g_BlockSize - WIN_HEIGHT;
}

void rePaintMap()
{
	g_MapImage.Resize(GAME_WIDTH * g_BlockSize, GAME_HEIGHT * g_BlockSize);	// 重置地图图片大小
	SetWorkingImage(&g_MapImage);								// 设置地图图片为当前工作图片
	for (int i = 0; i < GAME_HEIGHT; i++)
	{
		for (int j = 0; j < GAME_WIDTH; j++)
		{
			switch (g_GameMap[i][j])
			{
			case WALL:
				drawWall({ j*g_BlockSize, i*g_BlockSize });		// 绘制墙壁
				break;
			case FILLSTATE:
				drawFillState({ j*g_BlockSize, i*g_BlockSize });	// 绘制加油站
				break;
			case GROUND:
				drawGround({ j*g_BlockSize, i*g_BlockSize });	// 绘制地面
				break;
			case ENDPOS:
				drawEndPos({ j*g_BlockSize, i*g_BlockSize });
				break;
			}
		}
	}
	SetWorkingImage();	// 复位工作图片
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

	// 绘制圆角矩形
	pos.x += g_BlockSize / 5;
	pos.y += g_BlockSize / 5;
	setfillcolor(RGB(252, 213, 11));
	solidroundrect(pos.x, pos.y, pos.x + g_BlockSize / 5 * 3, pos.y + g_BlockSize / 5 * 3, g_BlockSize / 8, g_BlockSize / 8);
}

void drawEndPos(POINT pos)
{
	drawGround(pos);

	// 绘制圆角矩形
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
	// 锁定视野
	HRGN viewArr;
	int r = int(g_BlockSize * g_ViewArray + 0.5);	// 计算视野半径
	POINT orgin = g_PlayerPos;
	orgin.x -= g_CameraPos.x;						// 计算在屏幕上的位置
	orgin.y -= g_CameraPos.y;						// 计算在屏幕上的位置
	viewArr = CreateEllipticRgn(orgin.x - r, orgin.y - r, orgin.x + r, orgin.y + r);	// 创建一个圆形的区域
	setcliprgn(viewArr);							// 锁定区域

	// 绘制地图
	putimage(0, 0, WIN_WIDTH, WIN_HEIGHT, &g_MapImage, g_CameraPos.x, g_CameraPos.y);

	// 删除区域
	DeleteObject(viewArr);
	// 消除区域
	setcliprgn(NULL);
}