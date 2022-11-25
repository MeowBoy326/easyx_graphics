#include"science.h"


#define  N 922337203685477580						// 初始化sum1
#define  M 999999999.5f								// 初始化sum2

bool dy(false);										// 判断是否可以结束此次运算
bool qf(false);										// 数字取反的标志
int number(0);										// 读取按下的数字 0-9
int whatnumber(-1), whatnumber1(-1);				// 记录上次输入的哪个运算方式
long long sum(0);									// 记录上一次运算结果
long long sum1(N);									// 记录上一次运算结果
long double sum2(M);								// 记录运算是小数的结果
MyChar zfc[25];										// 显示运算结果(显示必须要用字符串显示)

void judge(int &n, int &m, int k = 0)
{
	if (n == 1)sum1 += sum, sum = 0, n = m;
	else if (n == 2)sum1 -= sum, sum = 0, n = m;
	else if (n == 3)sum1 *= sum, sum = 0, n = m;
	else if (n == 5)sum1 %= sum, sum = 0, n = m;
}


/*******************************科学计算器******************************************/
void updatewithinput()	// 与输入有关的更新
{
	MOUSEMSG m;			// 定义鼠标消息
	while (MouseHit())	// 检查是否有鼠标消息
	{
		m = GetMouseMsg();

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				if (m.x > i * 102 && m.x < i * 102 + 95 && m.y>240 + j * 52 && m.y < 285 + j * 52)
				{

					button[i][j] = true;

					if (m.uMsg == WM_LBUTTONDOWN)	// 如果按下左键
					{
						if (j >= 3 && j < 6 && i <= 2 || j == 6 && i == 1)
						{
							if (dy)sum = 0, sum1 = N, sum2 = M, dy = false;
							if (j == 5)
							{
								if (i == 0)number = 1;
								else if (i == 1)number = 2;
								else if (i == 2)number = 3;
							}
							if (j == 4)
							{
								if (i == 0)number = 4;
								else if (i == 1)number = 5;
								else if (i == 2)number = 6;
							}
							if (j == 3)
							{
								if (i == 0)number = 7;
								else if (i == 1)number = 8;
								else if (i == 2)number = 9;
							}
							if (j == 6 && i == 1)number = 0;
							if (sum <= N)
							{
								if (qf)sum = sum * 10 - number;
								else sum = sum * 10 + number;
							}
							else sum = 0;
						}
						else
						{
							if (j == 5 && i == 3 && whatnumber != 4)	// 加法
							{
								if (sum1 == N)
									sum1 = sum, sum = 0, whatnumber = 1, whatnumber1 = 1;
								else
								{
									whatnumber = 1;
									if (whatnumber == whatnumber1)
										sum1 += sum, sum = 0, whatnumber = 1;
									else judge(whatnumber1, whatnumber);
								}
							}
							else if (j == 4 && i == 3 && whatnumber != 4)	// 减法
							{
								if (sum1 == N)
									sum1 = sum, sum = 0, whatnumber = 2, whatnumber1 = 2;
								else
								{
									whatnumber = 2;
									if (whatnumber == whatnumber1)
										sum1 -= sum, sum = 0, whatnumber = 2;
									else judge(whatnumber1, whatnumber);
								}
							}
							else if (j == 3 && i == 3 && whatnumber != 4)	// 乘法
							{
								if (sum1 == N)
									sum1 = sum, sum = 0, whatnumber = 3, whatnumber1 = 3;
								else {
									whatnumber = 3;
									if (whatnumber == whatnumber1)
										sum1 *= sum, sum = 0, whatnumber = 3;
									else judge(whatnumber1, whatnumber);
								}
							}
							else if (j == 2 && i == 3 && whatnumber != 4)	// 除法
							{
								whatnumber = 4;
								if (sum1 == N)sum1 = sum, sum = 0;
							}
							else if (j == 1 && i == 3 && whatnumber != 4)	// 取余
							{
								if (sum1 == N)
									sum1 = sum, sum = 0, whatnumber = 5, whatnumber1 = 5;
								else
								{
									whatnumber = 5;
									if (whatnumber == whatnumber1)
										sum1 %= sum, sum = 0, whatnumber = 5;
									else judge(whatnumber1, whatnumber);
								}
							}
							else if (j == 6 && i == 0 && whatnumber != 4)	// 取反
							{
								static int a = 0;
								a++;
								if (a % 2)qf = true;
								else qf = false;
								sum = -sum;
							}
							else if (j == 6 && i == 2 && whatnumber != 4)
							{
								if (sum)sum2 = sum * 3.1415926535897932;
								else sum2 = 3.1415926535897932;
								dy = true;
							}
							else if (j == 1 && i == 0 && whatnumber != 4) sum2 = log(sum), dy = true;	// ln函数
							else if (j == 1 && i == 1 && whatnumber != 4)sum2 = log10(sum), dy = true;	// log函数
							else if (j == 1 && i == 2 && whatnumber != 4)sum2 = sqrt(sum), dy = true;	// sqrt函数
							else if (j == 0 && i == 0 && whatnumber != 4)sum2 = sin(sum), dy = true;	// sin函数
							else if (j == 0 && i == 1 && whatnumber != 4)sum2 = cos(sum), dy = true;	// cos函数
							else if (j == 0 && i == 2 && whatnumber != 4)sum2 = tan(sum), dy = true;	// tan函数
							else if (j == 0 && i == 3 && whatnumber != 4)sum2 = exp(sum), dy = true;	// exp函数
							else if (j == 2 && i == 2)sum /= 10;	// 删除
							else if (j == 2 && i == 1)sum = 0, sum1 = N, sum2 = M, whatnumber = -1, whatnumber1 = -1;	// 清零
							else if (j == 2 && i == 0 && whatnumber != 4)sum1 = (long long)pow(2, sum), dy = true;	// 2^n次
							if (j == 6 && i == 3)	// 等于
							{
								if (whatnumber == 1)sum1 += sum;
								else if (whatnumber == 2)sum1 -= sum;
								else if (whatnumber == 3)sum1 *= sum;
								else if (whatnumber == 4)sum2 = sum1 / (double)sum, sum1 = N;
								else if (whatnumber == 5)sum1 %= sum;
								dy = true;
								whatnumber = -1, whatnumber1 = -1;
							}
						}
					}
				}
				else button[i][j] = false;
			}
		}
		if (m.x > 5 && m.x < 40 && m.y > 0 && m.y < 35)	// 设置
		{
			help[0] = true;
			if (m.uMsg == WM_LBUTTONDOWN) software[0] = -1, software[2] = 3;
		}
		else help[0] = false;
	}
}


void showscreen()
{
	BeginBatchDraw();	// 开始批量绘图

	changecolor(0, 400, 0, 600);

	setfillstyle(BS_SOLID);
	IMAGE blacks = setimage(400, 600, RGB(0, 0, 0));	// 设置绘图
	my_putimage(0, 0, &blacks, RGB(255, 255, 255), 0, 1, 30, 0);

	blacks = setimage(100, 50, RGB(0, 0, 0));	// 设置绘图

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (j >= 3 && j < 6 && i <= 2 || j == 6 && i == 1)
			{
				if (!button[i][j])
					my_putimage(i * 102, 236 + j * 52, &blacks, RGB(255, 255, 255), 0, 1, 90, 0);
				else
					my_putimage(i * 102, 236 + j * 52, &blacks, RGB(255, 255, 255), 0, 1, 50, 0);
			}
			else
			{
				if (whatnumber == 4)
				{
					if (i == 3 && j == 6 || j == 2 && i == 2 || j == 2 && i == 1)
					{
						if (!button[i][j])
							;
						else
						{
							IMAGE black = setimage(100, 50, RGB(240, 0, 0));	// 设置绘图
							my_putimage(i * 102, 236 + j * 52, &black, RGB(255, 255, 255), 0, 1, 50, 0);
						}
					}
				}
				if (!button[i][j] || whatnumber == 4)
					my_putimage(i * 102, 236 + j * 52, &blacks, RGB(255, 255, 255), 0, 1, 80, 0);
				else
				{
					if (i == 3 && j == 6 || j == 2 && i == 2 || j == 2 && i == 1)
					{
						IMAGE black = setimage(100, 50, RGB(240, 0, 0));	// 设置绘图
						my_putimage(i * 102, 236 + j * 52, &black, RGB(255, 255, 255), 0, 1, 50, 0);
					}
					else if (j == 6 && i == 0 || j == 6 && i == 2 || j <= 5 && j >= 1 && i == 3)
					{
						IMAGE green = setimage(100, 50, GREEN);	// 设置绘图
						my_putimage(i * 102, 236 + j * 52, &green, RGB(255, 255, 255), 0, 1, 50, 0);
					}
					else
					{
						IMAGE black = setimage(100, 50, RGB(225,100, 26));	// 设置绘图
						my_putimage(i * 102, 236 + j * 52, &black, RGB(255, 255, 255), 0, 1, 50, 0);
					}
				}
			}
		}
	}
	settextstyle(30, 0, _T("微软雅黑"), 0, 0, 900, 0, 0, 0);
	settextcolor(RGB(255, 255, 255));
	setbkmode(TRANSPARENT);
	settextstyle(20, 0, _T("Consolas"));
	outtextxy(33, 360, _T("2^x"));
	settextstyle(26, 0, _T("Consolas"));
	outtextxy(346, 305, '%');
	settextstyle(30, 0, _T("Consolas"));
	outtextxy(142, 355, 'C');
	outtextxy(142, 560, '0');
	outtextxy(40, 560, _T("±"));
	outtextxy(40, 508, '1');
	outtextxy(142, 508, '2');
	outtextxy(244, 508, '3');
	outtextxy(40, 456, '4');
	outtextxy(142, 456, '5');
	outtextxy(244, 456, '6');
	outtextxy(40, 404, '7');
	outtextxy(142, 404, '8');
	outtextxy(244, 404, '9');
	settextstyle(40, 0, _T("Consolas"));
	outtextxy(342, 500, '+');
	outtextxy(342, 344, _T("÷"));
	outtextxy(342, 396, _T("×"));
	outtextxy(342, 552, '=');
	settextstyle(40, 25, _T("Consolas"));
	outtextxy(339, 448, '-');
	settextstyle(22, 0, _T("Consolas"));
	outtextxy(223, 358, _T("delete"));
	outtextxy(232, 305, _T("sqrt"));
	outtextxy(38, 305, _T("ln"));
	outtextxy(135, 305, _T("log"));
	outtextxy(33, 255, _T("sin"));
	outtextxy(133, 255, _T("cos"));
	outtextxy(235, 255, _T("tan"));
	outtextxy(335, 255, _T("exp"));
	settextstyle(35, 15, _T("Consolas"), 0, 0, 10, false, false, false);
	outtextxy(244, 556, _T("π"));

	settextcolor(WHITE);
	settextstyle(30, 0, _T("微软雅黑"), 0, 0, 900, 0, 0, 0);
	outtextxy(40, 10, _T("科学"));
	if (help[0])settextcolor(RGB(0, 255, 255));
	else settextcolor(WHITE);
	settextstyle(30, 30, _T("微软雅黑"));
	outtextxy(0, 10, _T("≡"));

	RECT r = { 10, 150 ,380, 200 };
	_stprintf_s(zfc, _T("%I64d"), sum);
	callen(zfc);	// 计算字符串长度
	settextcolor(WHITE);
	drawtext(zfc, &r, DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_MODIFYSTRING);

	if (sum1 != N && sum2 == M)
	{
		RECT r1 = { 10, 50 ,380, 100 };
		_stprintf_s(zfc, _T("%I64d"), sum1);
		callen(zfc);	// 计算字符串长度
		drawtext(zfc, &r1, DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_MODIFYSTRING);
	}
	if (sum2 != M && sum1 == N)
	{
		RECT r1 = { 10, 50 ,380, 100 };
		_stprintf_s(zfc, _T("%.15f"), sum2);
		callen(zfc);	// 计算字符串长度
		drawtext(zfc, &r1, DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_MODIFYSTRING);
	}

	if (help[2])
	{
		setlinecolor(RGB(0, 238, 238));
		rectangle(315, 45, 355, 65);
		settextcolor(RGB(194, 203, 223));
		settextstyle(20, 0, _T("微软雅黑"));
		outtextxy(320, 45, _T("换肤"));
	}

	EndBatchDraw();
}