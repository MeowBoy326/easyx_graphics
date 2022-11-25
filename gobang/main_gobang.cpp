////////////////////////////////////////////////////////
// 程序名称：博弈五子棋
// 编译环境：Visual C++ 2019		EasyX_2020-3-15(beta)
// 作　　者：陈可佳 <emil09_chen@126.com>
// 最后修改：2020-4-28
//
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>



// 类定义

// 保存位置的类
class seat
{
public:
	int i = 0;      // y 坐标
	int j = 0;      // x 坐标
	int number = 0; // 分数

	seat(){
	}
	seat(int x, int y, int k) :i(x), j(y), number(k){
	}
};

// 保存棋盘的类
class box
{
public:
	void draw();            // 绘制
public:
	int x = 0;              // x 坐标
	int y = 0;              // y 坐标
	int value = -1;         // 值（黑棋：1，白棋：0，空位：-1）
	int modle = 0;          // 模式
	bool isnew = false;     // 是否有选择框
	COLORREF color = WHITE; // 棋盘背景色
};


// 函数声明
void draw();                  // 绘制
void init();                  // 初始化
seat findbestseat(int color, int c); // 寻找最佳位置
void isWIN();                 // 判断输赢
void game();                  // 游戏主函数



// main函数
int main()
{
	initgraph(700, 700); // 初始化绘图环境
	setbkcolor(WHITE);
	cleardevice();
	setbkmode(TRANSPARENT); // 设置透明文字输出背景
	while (1)
	{
		init(); // 初始化
		game(); // 游戏开始
		cleardevice();
	}
}



// 全局变量
box BOX[19][19];      // 棋盘
int win = -1;         // 谁赢了（0：白棋，1：黑棋，2：平局）
int whoplay = 0;      // 轮到谁下棋了
int playercolor = 0;  // 玩家颜色
int dx[4]{ 1,0,1,1 }; // - | \ / 四个方向
int dy[4]{ 0,1,1,-1 };
int Score[3][5] = //评分表
{
	{ 0, 80, 250, 500, 500 }, // 防守0子
	{ 0, 0,  80,  250, 500 }, // 防守1子
	{ 0, 0,  0,   80,  500 }  // 防守2子
};
int MAXxs[361];   //最优x坐标
int MAXys[361];   //最优y坐标
int mylength = 0; //最优解数

// 类函数定义

// 绘制函数
void box::draw()
{
	COLORREF thefillcolor = getfillcolor(); // 备份填充颜色
	setlinestyle(PS_SOLID, 2);              // 线样式设置
	setfillcolor(color);                    // 填充颜色设置
	solidrectangle(x, y, x + 30, y + 30);   // 绘制无边框的正方形
	if (isnew)
	{
		// 如果是新下的
		// 绘制边框线
		setlinecolor(LIGHTGRAY);
		line(x + 1, y + 2, x + 8, y + 2);
		line(x + 2, y + 1, x + 2, y + 8);
		line(x + 29, y + 2, x + 22, y + 2);
		line(x + 29, y + 1, x + 29, y + 8);
		line(x + 2, y + 29, x + 8, y + 29);
		line(x + 2, y + 22, x + 2, y + 29);
		line(x + 29, y + 29, x + 22, y + 29);
		line(x + 29, y + 22, x + 29, y + 29);
	}
	setlinecolor(BLACK);
	switch (modle)
	{
		// 以下是不同位置棋盘的样式
	case 0:
		line(x + 15, y, x + 15, y + 30);
		line(x - 1, y + 15, x + 30, y + 15);
		break;
		//  *
		// ***
		//  *
	case 1:
		line(x + 14, y + 15, x + 30, y + 15);
		setlinestyle(PS_SOLID, 3);
		line(x + 15, y, x + 15, y + 30);
		setlinestyle(PS_SOLID, 2);
		break;
		// *
		// ***
		// *
	case 2:
		line(x - 1, y + 15, x + 15, y + 15);
		setlinestyle(PS_SOLID, 3);
		line(x + 15, y, x + 15, y + 30);
		setlinestyle(PS_SOLID, 2);
		break;
		//   *
		// ***
		//   *
	case 3:
		line(x + 15, y + 15, x + 15, y + 30);
		setlinestyle(PS_SOLID, 3);
		line(x - 1, y + 15, x + 30, y + 15);
		setlinestyle(PS_SOLID, 2);
		break;
		// ***
		//  *
		//  *
	case 4:
		line(x + 15, y, x + 15, y + 15);
		setlinestyle(PS_SOLID, 3);
		line(x - 1, y + 15, x + 30, y + 15);
		setlinestyle(PS_SOLID, 2);
		break;
		//  *
		//  *
		// ***
	case 5:
		setlinestyle(PS_SOLID, 3);
		line(x + 15, y, x + 15, y + 15);
		line(x + 15, y + 15, x + 30, y + 15);
		setlinestyle(PS_SOLID, 2);
		break;
		// *
		// *
		// ***
	case 6:
		setlinestyle(PS_SOLID, 3);
		line(x + 15, y, x + 15, y + 15);
		line(x - 1, y + 15, x + 15, y + 15);
		setlinestyle(PS_SOLID, 2);
		break;
		//   *
		//   *
		// ***
	case 7:
		setlinestyle(PS_SOLID, 3);
		line(x - 1, y + 15, x + 15, y + 15);
		line(x + 15, y + 15, x + 15, y + 30);
		setlinestyle(PS_SOLID, 2);
		break;
		// ***
		//   *
		//   *
	case 8:
		setlinestyle(PS_SOLID, 3);
		line(x + 15, y + 15, x + 30, y + 15);
		line(x + 15, y + 15, x + 15, y + 30);
		setlinestyle(PS_SOLID, 2);
		break;
		// ***
		// *
		// *
	case 9:
		line(x + 15, y, x + 15, y + 30);
		line(x - 1, y + 15, x + 30, y + 15);
		setfillcolor(BLACK);
		setlinestyle(PS_SOLID, 1);
		fillcircle(x + 15, y + 15, 4);
		break;
		//  *
		// *O*
		//  *
	}
	switch (value)
	{
	case 0: // 白棋
		setfillcolor(WHITE);
		setlinestyle(PS_SOLID, 1);
		fillcircle(x + 15, y + 15, 13);
		break;
	case 1: // 黑棋
		setfillcolor(BLACK);
		setlinestyle(PS_SOLID, 1);
		fillcircle(x + 15, y + 15, 13);
		break;
	}
	setfillcolor(thefillcolor); // 还原填充色
}



// 其他函数定义

// 绘制棋盘
void draw()
{
	int number = 0; // 坐标输出的位置
	// 坐标（数值）
	TCHAR strnum[19][3] = { _T("1"),_T("2") ,_T("3") ,_T("4"),_T("5") ,_T("6") ,_T("7"),_T("8"),_T("9"),_T("10"), _T("11"),_T("12") ,_T("13") ,_T("14"),_T("15") ,_T("16") ,_T("17"),_T("18"),_T("19") };
	// 坐标（字母）
	TCHAR strabc[19][3] = { _T("A"),_T("B") ,_T("C") ,_T("D"),_T("E") ,_T("F") ,_T("G"),_T("H"),_T("I"),_T("J"), _T("K"),_T("L") ,_T("M") ,_T("N"),_T("O") ,_T("P") ,_T("Q"),_T("R"),_T("S") };
	LOGFONT nowstyle;
	gettextstyle(&nowstyle);
	settextstyle(0, 0, NULL);
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			BOX[i][j].draw(); // 绘制
			if (BOX[i][j].isnew == true)
			{
				BOX[i][j].isnew = false; // 把上一个下棋位置的黑框清除
			}
		}
	}
	// 画坐标
	for (int i = 0; i < 19; i++)
	{
		outtextxy(75 + number, 35, strnum[i]);
		outtextxy(53, 55 + number, strabc[i]);
		number += 30;
	}
	settextstyle(&nowstyle);
}

// 对局初始化
void init()
{
	win = -1;// 谁赢了
	for (int i = 0, k = 0; i < 570; i += 30)
	{
		for (int j = 0, g = 0; j < 570; j += 30)
		{
			int modle = 0;  // 棋盘样式
			BOX[k][g].value = -1;
			BOX[k][g].color = RGB(255, 205, 150);// 棋盘底色
			// x、y 坐标
			BOX[k][g].x = 65 + j;
			BOX[k][g].y = 50 + i;
			// 棋盘样式的判断
			if (k == 0 && g == 0)
			{
				modle = 8;
			}
			else if (k == 0 && g == 18)
			{
				modle = 7;
			}
			else if (k == 18 && g == 18)
			{
				modle = 6;
			}
			else if (k == 18 && g == 0)
			{
				modle = 5;
			}
			else if (k == 0)
			{
				modle = 3;
			}
			else if (k == 18)
			{
				modle = 4;
			}
			else if (g == 0)
			{
				modle = 1;
			}
			else if (g == 18)
			{
				modle = 2;
			}
			else  if ((k == 3 && g == 3) || (k == 3 && g == 15) || (k == 15 && g == 3) || (k == 15 && g == 15) || (k == 3 && g == 9) || (k == 9 && g == 3) || (k == 15 && g == 9) || (k == 9 && g == 15) || (k == 9 && g == 9))
			{
				modle = 9;
			}
			else
			{
				modle = 0;
			}
			BOX[k][g].modle = modle;
			g++;
		}
		k++;
	}
}



// 核心函数

// 寻找最佳位置
seat findbestseat(int color, int c)
{
	if (c == 0)
	{
		//如果是第一层
		//清空数组
		mylength = 0;
	}
	int MAXnumber = -1e9;    //最佳分数
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			if (BOX[i][j].value == -1) {
				//遍历每一个空位置
				int length;        //当前方向长度
				int emeny;         //当前方向敌子
				int nowi = 0;      //现在遍历到的y坐标
				int nowj = 0;      //现在遍历到的x坐标
				int thescore = 0;  //这个位置的初始分数
				//判断周边有没有棋子
				int is = 0;
				for (int k = 0; k < 4; k++)
				{
					nowi = i;
					nowj = j;
					nowi += dx[k];
					nowj += dy[k];
					if (nowi >= 0 && nowj >= 0
						&& nowi <= 18 && nowj <= 18
						&& BOX[nowi][nowj].value != -1)
					{
						is = 1;
						break;
					}
					nowi = i;
					nowj = j;
					nowi += dx[k];
					nowj += dy[k];
					if (nowi >= 0 && nowj >= 0
						&& nowi <= 18 && nowj <= 18
						&& BOX[nowi][nowj].value != -1)
					{
						is = 1;
						break;
					}
					nowi = i;
					nowj = j;
					nowi -= dx[k];
					nowj -= dy[k];
					if (nowi >= 0 && nowj >= 0
						&& nowi <= 18 && nowj <= 18
						&& BOX[nowi][nowj].value != -1)
					{
						is = 1;
						break;
					}
					nowi = i;
					nowj = j;
					nowi -= dx[k];
					nowj -= dy[k];
					if (nowi >= 0 && nowj >= 0
						&& nowi <= 18 && nowj <= 18
						&& BOX[nowi][nowj].value != -1)
					{
						is = 1;
						break;
					}
				}
				if (!is)
				{
					//如果周围没有棋子，就不用递归了
					continue;
				}
				//自己
				BOX[i][j].value = color;//尝试下在这里
				for (int k = 0; k < 4; k++)
				{
					//检测四个方向
					length = 0;
					emeny = 0;
					nowi = i;
					nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].value == color)
					{
						length++;
						nowj += dy[k];
						nowi += dx[k];
					}
					if (nowi < 0 || nowj < 0 || nowi > 18 || nowj > 18 || BOX[nowi][nowj].value == !color)
					{
						emeny++;
					}
					nowi = i;
					nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].value == color)
					{
						length++;
						nowj -= dy[k];
						nowi -= dx[k];
					}
					if (nowi < 0 || nowj < 0 || nowi > 18 || nowj > 18 || BOX[nowi][nowj].value == !color)
					{
						emeny++;
					}
					length -= 2;//判断长度
					if (length > 4)
					{
						length = 4;
					}
					if (Score[emeny][length] == 500)
					{
						//己方胜利，结束递归
						BOX[i][j].value = -1;
						return { i,j,Score[emeny][length] };
					}
					thescore += Score[emeny][length];
					length = 0;
					emeny = 0;
				}
				//敌人（原理同上）
				BOX[i][j].value = !color;
				for (int k = 0; k < 4; k++)
				{
					length = 0;
					emeny = 0;
					nowi = i;
					nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].value == !color)
					{
						length++;
						nowj += dy[k];
						nowi += dx[k];
					}
					if (nowi < 0 || nowj < 0 || nowi > 18 || nowj > 18 || BOX[nowi][nowj].value == color)
					{
						emeny++;
					}
					nowi = i;
					nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].value == !color)
					{
						length++;
						nowj -= dy[k];
						nowi -= dx[k];
					}
					if (nowi < 0 || nowj < 0 || nowi > 18 || nowj > 18 || BOX[nowi][nowj].value == color)
					{
						emeny++;
					}
					length -= 2;
					if (length > 4)
					{
						length = 4;
					}
					if (Score[emeny][length] == 500)
					{
						BOX[i][j].value = -1;
						return{ i,j,Score[emeny][length] };
					}
					thescore += Score[emeny][length];
					length = 0;
					emeny = 0;
				}
				BOX[i][j].value = -1;
				//如果已经比最高分数小，就没必要递归了
				if (thescore >= MAXnumber)
				{
					if (c < 3)
					{
						//只能找4层，否则时间太长
						BOX[i][j].value = color;
						//递归寻找对方分数
						int nowScore = thescore - findbestseat(!color, c + 1).number;//递归求出这个位置的分值
						BOX[i][j].value = -1;
						if (nowScore > MAXnumber)
						{
							//比最高分值大
							MAXnumber = nowScore;
							if (c == 0)
							{
								//第一层
								mylength = 0;//清空数组
							}
						}
						if (c == 0)
						{
							//第一层
							if (nowScore >= MAXnumber)
							{
								//把当前位置加入数组
								MAXxs[mylength] = i;
								MAXys[mylength] = j;
								mylength++;
							}
						}
					}
					else {
						//如果递归到了最后一层
						if (thescore > MAXnumber)
						{
							//直接更新
							MAXnumber = thescore;
						}
					}
				}
			}
		}
	}
	if (c == 0)
	{
		//第一层
		//随机化落子位置
		int mynum = rand() % mylength;
		return { MAXxs[mynum],MAXys[mynum],MAXnumber };
	}
	//其他层
	return { 0,0,MAXnumber };
}

// 判断输赢
void isWIN()
{
	bool isfull = true; // 棋盘是否满了
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			if (BOX[i][j].value != -1)
			{
				// 遍历每个可能的位置
				int nowcolor = BOX[i][j].value; // 现在遍历到的颜色
				int length[4] = { 0,0,0,0 };    // 四个方向的长度
				for (int k = 0; k < 4; k++)
				{
					// 原理同寻找最佳位置
					int nowi = i;
					int nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].value == nowcolor)
					{
						length[k]++;
						nowj += dx[k];
						nowi += dy[k];
					}
					nowi = i;
					nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].value == 1 - nowcolor)
					{
						length[k]++;
						nowj -= dx[k];
						nowi -= dy[k];
					}
				}
				for (int k = 0; k < 4; k++)
				{
					if (length[k] >= 5) {
						// 如果满五子
						if (nowcolor == playercolor)
						{
							win = playercolor; // 玩家胜
						}
						if (nowcolor == 1 - playercolor)
						{
							win = 1 - playercolor; // 电脑胜
						}
					}
				}
			}
			else
			{
				//如果为空
				isfull = false;//棋盘没满
			}
		}
	}
	if (isfull)
	{
		// 如果棋盘满了
		win = 2; // 平局
	}
}

// 游戏主函数
void game()
{
	bool isinit;
	// 上一个鼠标停的坐标
	int oldi = 0;
	int oldj = 0;
	// 随机化玩家颜色
	srand(time(NULL));
	playercolor = rand() % 2;
	// 绘制背景
	setfillcolor(RGB(255, 205, 150));
	solidrectangle(40, 25, 645, 630);
	// 设置字体样式
	settextstyle(30, 15, 0, 0, 0, 1000, false, false, false);
	settextcolor(BLACK);
	// 输出标示语
	if (playercolor == 0)
	{
		isinit = 1;
		outtextxy(150, 650, _T("玩家执白后行，电脑执黑先行"));
		whoplay = 1;
	}
	else
	{
		isinit = 0;
		outtextxy(150, 650, _T("玩家执黑先行，电脑执白后行"));
		whoplay = 0;
	}
	draw(); // 绘制
	while (1)
	{
	NEXTPLAYER:
		if (whoplay == 0)
		{
			// 玩家下棋
			MOUSEMSG mouse = GetMouseMsg(); // 获取鼠标信息
			for (int i = 0; i < 19; i++)
			{
				for (int j = 0; j < 19; j++)
				{
					if (mouse.x > BOX[i][j].x && mouse.x<BOX[i][j].x + 30//判断x坐标
						&& mouse.y>BOX[i][j].y && mouse.y < BOX[i][j].y + 30//判断y坐标
						&& BOX[i][j].value == -1)//判断是否是空位置
					{
						// 如果停在某一个空位置上面
						if (mouse.mkLButton)
						{
							// 如果按下了
							BOX[i][j].value = playercolor; // 下棋
							BOX[i][j].isnew = true;        // 新位置更新
							oldi = -1;
							oldj = -1;
							// 下一个玩家
							whoplay = 1;
							goto DRAW;
						}
						// 更新选择框
						BOX[oldi][oldj].isnew = false;
						BOX[oldi][oldj].draw();
						BOX[i][j].isnew = true;
						BOX[i][j].draw();
						oldi = i;
						oldj = j;
					}
				}
			}
		}
		else
		{
			// 电脑下棋
			if (isinit)
			{
				// 开局情况
				isinit = 0;
				int drawi = 9;
				int drawj = 9;
				while (BOX[drawi][drawj].value != -1)
				{
					drawi--;
					drawj++;
				}
				BOX[drawi][drawj].value = 1 - playercolor;
				BOX[drawi][drawj].isnew = true;
			}
			else
			{
				seat best;
				best = findbestseat(1 - playercolor, 0); // 寻找最佳位置
				BOX[best.i][best.j].value = 1 - playercolor;//下在最佳位置
				BOX[best.i][best.j].isnew = true;
			}
			whoplay = 0;
			goto DRAW; // 轮到下一个
		}
	}
DRAW: // 绘制
	isWIN(); // 检测输赢
	draw();
	oldi = 0;
	oldj = 0;
	if (win == -1)
	{
		// 如果没有人胜利
		Sleep(500);
		goto NEXTPLAYER; // 前往下一个玩家
	}
	// 胜利处理
	settextcolor(RGB(0, 255, 0));
	Sleep(1000);
	if (win == 0)
	{
		outtextxy(320, 320, _T("白胜"));
	}
	if (win == 1)
	{
		outtextxy(320, 320, _T("黑胜"));
	}
	if (win == 2)
	{
		outtextxy(320, 320, _T("平局"));
	}
	// 给反应时间
	Sleep(5000);
	return;
}