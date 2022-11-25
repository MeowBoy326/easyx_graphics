///////////////////////////////////
// 程序名称：贪吃蛇
// 编译环境：Visual C++ 6.0 / 2008，EasyX 2013冬至版
// 作者：王垣恒 QQ：646361765
// 最后修改：2014-5-20
// 操作方式：以蛇为第一视角，左 左转；右 右转；下 暂停；上 快进。
// 状态： 黄色 蛇头；红色 蛇身；绿色 食物。
//
#include <graphics.h>
#include <string.h>
#include <time.h>
#define NUM_R 10		//半径
#define NUM_X 25		//横向个数
#define NUM_Y 25		//纵向个数
#define NUM 30			//所需节点个数
void exe(int x, int y, int f);
int  GetCommand();
void eat(int x, int y);
void clear();
void set();
void flush();
void over(bool a);

struct pos				//建立链表储存每个关节的位置
{
	int x;
	int y;
	struct pos*next;
};
struct pos*head = (pos*)malloc(sizeof(pos));	//建立头指针
int n = 0;				//记录节点个数

void main()				//初始化游戏
{
	int x, y, f;			//储存初始化点的位置方向
	srand((unsigned)time(NULL));			//初始化随机库
	do
	{
		x = rand() % NUM_X*NUM_R * 2 + NUM_R;
		y = rand() % NUM_Y*NUM_R * 2 + NUM_R;
	} while (x<4 * NUM_R || y<4 * NUM_R || 2 * NUM_R*(NUM_X - 2)<x || 2 * NUM_R*(NUM_Y - 2)<y);		//产生不在矩形边缘的初始点
	f = rand() % 4;										//随机方向
	struct pos*a = (pos*)malloc(sizeof(pos)), *p = head; //建立链表第一个节点
	a->x = x;					//指针a储存第一个点数据
	a->y = y;
	head->next = a;			//接链
	a->next = NULL;			//结尾
	initgraph(2 * NUM_R*NUM_X, 2 * NUM_R*NUM_Y + 50);		//初始绘图窗口
	setcolor(WHITE);
	line(0, 2 * NUM_R*NUM_Y + 1, 2 * NUM_R*NUM_X, 2 * NUM_R*NUM_Y + 1);
	setcolor(getbkcolor());	//取消圆的边缘
	setfillcolor(YELLOW);	//设置填充颜色
	fillcircle(x, y, NUM_R);	//绘出初始点
	set();					//产生食物
	exe(x, y, f);				//进入控制函数
}

void exe(int x, int y, int f)			//操作游戏
{
	int xf, yf, c, i;
	while (1)						//进入循环
	{
		c = 0;						//初始化方向
		for (i = 0; i<5; i++)			//循环5次获取命令
		{
			Sleep(100 - 50 * n / NUM);	//等待
			if (c == 0)				//若没获取到命令就进行获取
			{
				c = GetCommand();
				if (c == 4)			//返回4时退出循环等待
					break;
			}
		}
		f = f + c;						//改变方向
		if (f>3)						//溢出处理
			f = f - 4;
		xf = yf = 0;					//初始化方向参数
		switch (f)
		{
		case 0:xf = 1; break;			//方向向右时 x坐标增加
		case 1:yf = 1; break;			//方向向右时 y坐标增加
		case 2:xf = -1; break;			//方向向右时 x坐标减少
		case 3:yf = -1; break;			//方向向右时 y坐标减少
		}
		x = x + 2 * NUM_R*xf;				//x坐标变化
		y = y + 2 * NUM_R*yf;				//y坐标变化
		if (getpixel(x, y) == RED || x<0 || y<0 || 2 * NUM_X*NUM_R<x || 2 * NUM_Y*NUM_R<y)		//判断是否遇到自身或碰到边界
			over(0);					//结束游戏
		else							//不结束进行下步运算
		{
			if (getpixel(x, y) == GREEN)	//判断前方是否为食物
				set();					//产生新食物
			else
				clear();				//清除尾结点
			eat(x, y);					//在前方生成新结点
			if (n>NUM - 1)					//判断胜利条件
				over(1);				//结束游戏
		}
	}
}

int GetCommand()				//获取方向
{
	int c = 0;					//初始化方向变量
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)	c = 1;		//右转为1
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)	c = 3;		//左转为3
	if (GetAsyncKeyState(VK_UP) & 0x8000)	c = 4;		//按上为4 快进
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)	system("pause");	//按下则暂停
	return c;
}

void eat(int x, int y)				//增加新结点
{
	struct pos*a = (pos*)malloc(sizeof(pos)), *p = head;		//声明指针变量
	while (p->next != NULL)			//寻找链表尾节点
		p = p->next;
	a->x = x;							//把数据储存到结点
	a->y = y;
	p->next = a;						//指针a接到尾节点后
	a->next = NULL;					//结尾
	setcolor(getbkcolor());			//取消圆的边缘
	setfillcolor(RED);				//设置填充颜色
	fillcircle(p->x, p->y, NUM_R);	//绘制新结点
	setfillcolor(YELLOW);			//设置填充颜色
	fillcircle(x, y, NUM_R);			//绘制新结点
}

void clear()							//清除尾结点
{
	setcolor(getbkcolor());				//取消圆的边缘
	setfillcolor(getbkcolor());			//设置填充颜色
	fillcircle(head->next->x, head->next->y, NUM_R);    //擦除结点
	head->next = head->next->next;		//删除节点数据
}

void set()			//产生食物和胜利判断
{
	flush();
	int x, y;		//声明变量
	do
	{
		x = rand() % NUM_X*NUM_R * 2 + NUM_R;
		y = rand() % NUM_Y*NUM_R * 2 + NUM_R;
	} while (getpixel(x, y) == RED);		//随机产生食物在非蛇的位置
	setcolor(getbkcolor());
	setfillcolor(GREEN);				//设置填充颜色
	fillcircle(x, y, NUM_R);				//产生食物
}

void flush()
{
	n++;			//节点计数累加
	char strnum[20], string[10] = "进度:";
	itoa(n, strnum, 10);					//转换
	strcat(string, strnum);				//链接
	strcpy(strnum, "/");					//赋值
	strcat(string, strnum);				//连接
	itoa(NUM, strnum, 10);
	strcat(string, strnum);
	setcolor(WHITE);
	settextstyle(32, 0, _T("宋体"));		//设置字体类型
	outtextxy(20, 2 * NUM_R*NUM_Y + 2, "          ");
	outtextxy(20, 2 * NUM_R*NUM_Y + 2, string);
}

void over(bool a)						//结束游戏
{
	setcolor(WHITE);                    //设置字体颜色
	settextstyle(48, 0, _T("宋体"));		//设置字体类型
	if (a)								//判断条件
		outtextxy(NUM_X*NUM_R - 20, NUM_Y*NUM_R - 20, "胜利");		//输出结果
	else
		outtextxy(NUM_X*NUM_R - 20, NUM_Y*NUM_R - 20, "失败");		//输出结果
	Sleep(2000);
	system("pause");
	exit(0);
}