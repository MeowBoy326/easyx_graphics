///////////////////////////////////////////////////
// 程序名称：数独解题器
// 编译环境：Mictosoft Visual Studio 2013, EasyX_20200315(beta)
// 作　　者：luoyh <2864292458@qq.com>
// 最后修改：2020-4-4
// 可以解决 9 * 9 的数独问题，使用回溯法
//

#include <graphics.h>
#define WIDTH 480
#define HEIGHT 640
const wchar_t wPROGRAMINFO[] = _T("程序名称：数独辅助器 \n程序作者：罗寅虎 \n制作时间：2020年4月7日 \n联系邮箱：2864292458@qq.com\n\n操作说明：\n1.鼠标左击下方不同的数字进行选取 \n2.再左击九宫格相应位置进行填入 \n3.选择后可重复填入 \n4.点击求解键后开始处理数独 \n4.点击清空将清除掉九宫格内的数\n");


int matrix[9][9] = { 0 };								// 定义一个二维数组储存数独
void drawframe();										// 绘制九宫格及修饰的相关图形
void grain();											// 纹路
void Prompt();											// 绘制提示符
void Solution();										// 求解按钮
void ClearButton();										// 清空按钮
void OUTTEXT(int i, int x, int y);						// 绘制输出数字
int MouseMessage(int *m_x, int *m_y);					// 处理鼠标消息，返回数与鼠标的坐标
void retrace(int number, COLORREF color);				// 重新复原边框颜色等
void save(int n, int x, int y);							// 储存和输出
void ClearScreen();										// 清空九宫格
bool FirstCheck();										// 初次判断检查
void Output();											// 输出答案
int MouseNumber = 0;
int sum = 0;											// 数独多解的记录
int trace(int x, int y);								// 算法的核心回溯法
int check(int x, int y);								// 每次判断
bool newmatrix[9][9];
void Tofalse();											// 将数组全部置为 false
int CheckNumber(int n);									// 判断里面有没有这个数
int Totrue(int n);
bool SecondCheck();										// 第二次判断
bool Point[3][3];


int main()
{
	initgraph(WIDTH, HEIGHT);
	drawframe();										// 绘制表格框架
	while (true)
	{
		while (true)
		{
			int m_x, m_y, number;
			number = MouseMessage(&m_x, &m_y);			// 鼠标消息

			if (number == 10)
			{
				MouseNumber = 0;
				if (FirstCheck() == false)
					continue;
				else
					break;
			}
			save(number, m_x, m_y);
			if (FirstCheck() == false)
			{
				settextstyle(20, 0, _T("楷体"));
				settextcolor(0xf4b1a4);
				outtextxy(120, 99, _T("输入有误，请检查！"));

			}
			if (FirstCheck() == true)
			{
				settextstyle(20, 0, _T("楷体"));
				outtextxy(120, 99, _T("                  "));
			}
		}
		settextcolor(0xf4b1a4);
		settextstyle(20, 0, _T("楷体"));
		outtextxy(120, 99, _T("求解中......"));
		if (SecondCheck() == true)		// 第二次检查，防止不必要的死循环
		{
			trace(0, 0);				// 溯回法判断
		}
		else sum = 0;

		if (sum == 0)
		{
			setbkmode(OPAQUE);
			settextcolor(0xf4b1a4);
			settextstyle(20, 0, _T("楷体"));
			outtextxy(120, 99, _T("               "));
			outtextxy(120, 99, _T("该数独无解！"));
			continue;
		}

		if (sum == 1)
		{
			setbkmode(OPAQUE);
			settextcolor(0xf4b1a4);
			settextstyle(20, 0, _T("楷体"));
			outtextxy(120, 99, _T("               "));
			outtextxy(120, 99, _T("该数独只有一个解"));
			sum = 0;
			continue;
		}

		if (sum > 1)
		{
			setbkmode(OPAQUE);
			settextcolor(0xf4b1a4);
			settextstyle(20, 0, _T("楷体"));
			outtextxy(120, 99, _T("               "));
			outtextxy(120, 99, _T("该数独有多个解"));
			sum = 0;
			continue;
		}
	}

	closegraph();
	return 0;
}


// 绘制数独框架，可以进一步美化
void drawframe()
{
	setbkcolor(0x3a0a0a);
	cleardevice();
	grain();
	setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 0);
	setlinecolor(0x5555FF);
	int x = 60;
	int y = 120;

	// 绘制九宫格，左上角坐标为（x ，y）每隔40画一条横线，并画一条竖线
	for (int i = 0; i <= 9; i++)
	{
		line(x, y + i * 40, 420, y + i * 40);
		line(x + i * 40, y, x + i * 40, 480);
	}

	setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 3);
	setlinecolor(0xFF5555);

	// 分割为九份，左上角坐标为（x , y）每隔120画一条横线，并画一条竖线
	for (int i = 0; i < 4; i++)
	{
		line(x, y + i * 120, 420, y + i * 120);
		line(x + i * 120, y, x + i * 120, 480);
	}

	// 绘制汉字修饰符
	settextcolor(0xf4b1a4);
	setbkmode(TRANSPARENT);
	settextstyle(76, 0, _T("楷体"));
	outtextxy(60, 22, _T("数独辅助器"));
	settextstyle(20, 0, _T("楷体"));
	outtextxy(40, 490, _T("请选择你需要填入的数："));

	// 绘制下边的框格
	line(40, 520, 440, 520);
	line(40, 560, 440, 560);
	for (int i = 0; i <= 10; i++)
	{
		line(40 + 40 * i, 520, 40 + 40 * i, 560);
	}

	// 给框格内填入数字
	for (int i = 0; i <= 9; i++)
	{
		setbkmode(TRANSPARENT);
		OUTTEXT(i, 40 + 40 * i + 12, 522);
	}

	settextcolor(0xf4b1a4);
	// 绘制求解键
	Solution();
	// 绘制提示说明符
	Prompt();
	// 绘制清屏按钮
	ClearButton();
	settextstyle(20, 0, _T("楷体"));
	outtextxy(60, 99, _T("提示："));
}


// 绘制提示说明符
void Prompt()
{
	setbkmode(TRANSPARENT);
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 2);
	settextstyle(42, 0, L"Webdings");
	wchar_t c = 0x69;
	outtextxy(438, 0, c);
}


// 求解按钮
void Solution()
{
	setbkmode(TRANSPARENT);
	rectangle(360, 580, 440, 620);
	setbkmode(TRANSPARENT);
	settextstyle(36, 0, _T("楷体"));
	outtextxy(364, 582, _T("求解"));
}


// 清空按钮
void ClearButton()
{
	setbkmode(TRANSPARENT);
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 3);
	rectangle(280, 580, 360, 620);
	settextstyle(36, 0, _T("楷体"));
	outtextxy(284, 582, _T("清空"));
}


// 纹路
void grain()
{
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 2);
	setlinecolor(0xb82727);
	line(61, 486, 0, 547);
	line(94, 486, 0, 580);
	line(140, 486, 7, 619);
	line(158, 486, 15, 629);
	line(170, 491, 24, 638);
	line(170, 491, 212, 491);
	line(212, 491, 280, 560);
	line(280, 560, 400, 560);
	line(400, 560, 480, 480);
	line(228, 486, 271, 530);
	line(271, 530, 352, 530);
	line(352, 530, 396, 486);
	line(40, 640, 105, 575);
	line(105, 575, 114, 575);
	line(114, 575, 168, 520);
	line(168, 520, 220, 520);
	line(220, 520, 300, 600);
	line(300, 600, 360, 600);
	setfillcolor(WHITE);
	solidcircle(360, 600, 4);
	line(60, 640, 110, 590);
	line(110, 590, 119, 590);
	line(119, 590, 177, 530);
	line(177, 530, 211, 530);
	line(211, 530, 290, 608);
	line(290, 608, 290, 632);
	solidcircle(290, 632, 4);
	circle(137, 593, 3);
	line(139, 591, 179, 551);
	line(179, 551, 213, 551);
	line(213, 551, 242, 582);
	line(242, 582, 242, 605);
	solidcircle(242, 605, 4);
	circle(159, 592, 3);
	line(161, 589, 171, 579);
	line(171, 579, 213, 579);
	line(213, 579, 220, 585);
	line(220, 585, 220, 592);
	circle(220, 595, 3);
	circle(110, 600, 3);
	line(113, 604, 128, 619);
	line(128, 619, 260, 619);
	line(260, 619, 280, 639);
	line(280, 639, 339, 639);
	line(339, 639, 379, 600);
	line(379, 600, 379, 576);
	circle(379, 573, 3);
	circle(77, 637, 3);
	line(80, 633, 95, 619);
	line(95, 619, 117, 619);
	line(117, 619, 125, 626);
	line(125, 626, 210, 626);
	line(210, 626, 222, 640);
	line(88, 640, 93, 634);
	line(93, 634, 199, 634);
	line(199, 634, 202, 640);
	line(358, 639, 397, 599);
	line(397, 599, 438, 599);
	line(438, 599, 470, 568);
	circle(472, 565, 3);
	line(379, 639, 398, 619);
	line(398, 619, 420, 619);
	circle(423, 619, 3);
	circle(426, 568, 3);
	line(429, 565, 480, 516);
	line(458, 638, 467, 630);
	line(467, 630, 480, 630);
	line(0, 184, 26, 210);
	line(26, 210, 26, 369);
	line(26, 369, 0, 393);
	line(0, 205, 7, 211);
	line(7, 211, 7, 270);
	circle(7, 273, 3);
	line(0, 463, 5, 457);
	line(5, 457, 5, 430);
	line(5, 430, 51, 383);
	line(51, 174, 40, 163);
	line(40, 163, 40, 16);
	circle(40, 13, 3);
	line(52, 0, 69, 18);
	line(69, 18, 69, 52);
	circle(69, 55, 3);
	line(257, 0, 144, 111);
	line(144, 111, 144, 120);
	line(310, 0, 190, 120);
	line(238, 120, 263, 94);
	line(263, 94, 329, 94);
	line(329, 94, 424, 0);
	line(423, 461, 423, 421);
	line(423, 421, 445, 397);
	circle(451, 392, 3);
	line(420, 358, 480, 358);
	line(420, 136, 480, 74);
	line(420, 186, 443, 186);
	line(443, 186, 480, 147);
	line(420, 207, 450, 206);
	line(450, 206, 480, 179);
	line(420, 254, 480, 254);
	line(420, 261, 480, 261);
	// 粗白线

	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 4);
	line(70, 120, 70, 107);
	line(70, 107, 138, 40);
	line(138, 40, 138, 0);
	line(133, 120, 133, 95);
	line(212, 120, 331, 0);
	line(420, 168, 429, 168);
	line(429, 168, 480, 117);
	line(420, 227, 462, 227);
	line(462, 227, 480, 208);
	line(0, 145, 45, 190);
	line(45, 190, 45, 368);
	line(45, 368, 0, 412);
	line(133, 95, 227, 0);
	line(344, 120, 460, 0);
	line(119, 486, 0, 605);

	setlinecolor(0xf4b1a4);
	line(420, 268, 480, 268);
	line(48, 471, 0, 520);
	circle(464, 612, 3);
	line(467, 609, 480, 597);
}


// 输出相应位置对应的相应的数
void OUTTEXT(int i, int x, int y)
{
	settextstyle(36, 0, _T("consolas"));
	switch (i)
	{
	case 0: settextcolor(0xFFFFFF); outtextxy(x, y, _T(" ")); break;
	case 1: settextcolor(0xEFFFFE); outtextxy(x, y, _T("1")); break;
	case 2: settextcolor(0xDFFFFD); outtextxy(x, y, _T("2")); break;
	case 3: settextcolor(0xCFFFFC); outtextxy(x, y, _T("3")); break;
	case 4: settextcolor(0xBFFFFB); outtextxy(x, y, _T("4")); break;
	case 5: settextcolor(0xAFFFFA); outtextxy(x, y, _T("5")); break;
	case 6: settextcolor(0x9FFFF9); outtextxy(x, y, _T("6")); break;
	case 7: settextcolor(0x8FFFF8); outtextxy(x, y, _T("7")); break;
	case 8: settextcolor(0x7FFFF7); outtextxy(x, y, _T("8")); break;
	case 9: settextcolor(0x6FFFF6); outtextxy(x, y, _T("9")); break;
	}
}


// 有鼠标获取相应位置相应的数
int MouseMessage(int *myx, int *myy)
{
	MOUSEMSG m;																// 定义鼠标消息
	bool T = true;
	while (T)
	{
		m = GetMouseMsg();													// 获取一个鼠标消息
		setlinecolor(RED);
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
			if (m.x >= 40 && m.x <= 440 && m.y >= 520 && m.y <= 560)		// 如果左键按下的范围在下方选择的范围内
			{
				if (MouseNumber >= 0)										// 如果这个鼠标已经过数，继续点击，需要使得画过的颜色复原
				{
					retrace(MouseNumber, 0xFF5555);
				}
				retrace((m.x - 40) / 40, RED);
				MouseNumber = (m.x - 40) / 40;
			}

			if (m.x >= 60 && m.x <= 420 && m.y >= 120 && m.y <= 480)		// 坐标点在九宫格内就将给点坐标按地址值传出
			{
				*myx = m.x;
				*myy = m.y;
				T = false;
			}

			if (m.x >= 360 && m.x <= 440 && m.y >= 580 && m.y <= 620)		// 确定键按按下
			{
				setlinecolor(RED);
				settextcolor(RED);
				Solution();
				retrace(MouseNumber, 0xFF5555);
				settextstyle(20, 0, _T("楷体"));
				outtextxy(120, 99, _T("                  "));
				break;
			}

			if (m.x >= 436 && m.x <= 480 && m.y >= 0 && m.y <= 44)			// 提示符按下
			{
				settextcolor(RED);
				setlinecolor(RED);
				Prompt();
				break;
			}
			if (m.x >= 280 && m.x <= 360 && m.y >= 580 && m.y <= 620)		// 清屏按下
			{
				setlinecolor(RED);
				settextcolor(RED);
				ClearButton();
				retrace(MouseNumber, 0xFF5555);
				setbkmode(OPAQUE);
				settextstyle(20, 0, _T("楷体"));
				outtextxy(120, 99, _T("                  "));
				break;
			}
		case WM_LBUTTONUP:													// 左键抬起
			if (m.x >= 360 && m.x <= 440 && m.y >= 580 && m.y <= 620)		// 确定键抬起
			{
				setlinecolor(0xFF5555);
				settextcolor(0xf4b1a4);
				Solution();
				MouseNumber = 10;
				return MouseNumber;
			}

			if (m.x >= 436 && m.x <= 480 && m.y >= 0 && m.y <= 44)			// 提示符抬起弹出操作说明
			{
				settextcolor(0xFF5555);
				setlinecolor(0xFF5555);
				Prompt();
				MessageBox(NULL, wPROGRAMINFO, _T("关于"), MB_OK | MB_ICONASTERISK);
			}
			if (m.x >= 280 && m.x <= 360 && m.y >= 580 && m.y <= 620)		// 清屏抬起
			{
				settextcolor(0xf4b1a4);
				setlinecolor(0xFF5555);
				ClearButton();
				ClearScreen();
				sum = 0;
				break;
			}
		}
	}

	return MouseNumber;
}


// 重新描矩形，给人按钮的感觉
void retrace(int number, COLORREF color)
{
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 3);
	setlinecolor(color);
	switch (number)
	{
	case 0: rectangle(40 + 40 * 0, 520, 80 + 40 * 0, 560); break;
	case 1: rectangle(40 + 40 * 1, 520, 80 + 40 * 1, 560); break;
	case 2: rectangle(40 + 40 * 2, 520, 80 + 40 * 2, 560); break;
	case 3: rectangle(40 + 40 * 3, 520, 80 + 40 * 3, 560); break;
	case 4: rectangle(40 + 40 * 4, 520, 80 + 40 * 4, 560); break;
	case 5: rectangle(40 + 40 * 5, 520, 80 + 40 * 5, 560); break;
	case 6: rectangle(40 + 40 * 6, 520, 80 + 40 * 6, 560); break;
	case 7: rectangle(40 + 40 * 7, 520, 80 + 40 * 7, 560); break;
	case 8: rectangle(40 + 40 * 8, 520, 80 + 40 * 8, 560); break;
	case 9: rectangle(40 + 40 * 9, 520, 80 + 40 * 9, 560); break;
	}
}


// 对相应数的填入和储存
void save(int n, int x, int y)
{
	int myx, myy;
	myx = ((x - 60) / 40) * 40 + 60 + 12;
	myy = ((y - 120) / 40) * 40 + 120 + 2;
	setbkmode(OPAQUE);
	OUTTEXT(n, myx, myy);
	int mx, my;
	mx = (x - 60) / 40;
	my = (y - 120) / 40;
	matrix[mx][my] = n;
}


// 将九宫格内的数清空
void ClearScreen()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			setbkmode(OPAQUE);
			OUTTEXT(0, i * 40 + 60 + 12, j * 40 + 120 + 2);
			matrix[i][j] = 0;
		}
	}
	MouseNumber = 0;
}


// 将答案输出
void Output()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			setbkmode(OPAQUE);
			OUTTEXT(matrix[i][j], 60 + i * 40 + 12, 120 + j * 40 + 2);
		}
	}
}


// 检查一行一列中的数，和九宫格中
int check(int x, int y)
{
	int flag = 1;
	for (int i = 0; i<9; i++)
	{
		if (matrix[x][i] == matrix[x][y] && i != y)
		{

			flag = 0;
		}
		if (matrix[i][y] == matrix[x][y] && i != x)
		{
			flag = 0;
		}
	}
	int xi = x / 3, yi = y / 3;

	for (int i = xi * 3; i<(xi + 1) * 3; i++)
	{
		for (int j = yi * 3; j<(yi + 1) * 3; j++)
		{
			if (i != x && j != y && matrix[i][j] == matrix[x][y])
			{
				flag = 0;
			}
		}
	}

	return flag;
}


// 核心算法，回溯法
int trace(int x, int y)
{
	if (x == 9)
	{
		Output();
		sum++;
	}
	if (sum > 1)
		return 0;
	if (matrix[x][y] == 0)
	{
		for (int j = 1; j <= 9; j++)
		{
			matrix[x][y] = j;

			if (check(x, y))
			{
				trace(x + (y + 1) / 9, (y + 1) % 9);

			}
			matrix[x][y] = 0;
		}
	}
	else
	{
		trace(x + (y + 1) / 9, (y + 1) % 9);
	}
	return 0;
}


// 初步进行判断数独的正确性
bool FirstCheck()
{
	int a[9];											// 行
	int b[9];											// 列
	int c[9];											// 块

	// 判断每一行是否符合条件
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			a[j] = matrix[i][j];
			if (j == 8)
			{
				for (int q = 0; q < 9; q++)
				{
					for (int p = q + 1; p < 9; p++)
					{
						if (p < 9)
						{
							if (a[q] != 0 && a[p] != 0)
							{
								if (a[q] == a[p])
									return false;
							}
						}
					}
				}

			}
		}
	}

	// 判断每一列是否符合条件
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			b[j] = matrix[j][i];
			if (j == 8)
			{
				for (int q = 0; q < 9; q++)
				{
					for (int p = q + 1; p < 9; p++)
					{
						if (p < 9)
						{
							if (b[q] != 0 && b[p] != 0)
							{
								if (b[q] == b[p])
									return false;
							}
						}
					}
				}
			}
		}
	}

	// 用于判断九宫格中每一个块中有无重复的
	int ns = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int p = 0; p < 3; p++)
			{
				for (int q = 0; q < 3; q++)
				{
					c[ns] = matrix[i * 3 + p][j * 3 + q];
					ns++;
					if (ns == 9)
					{
						for (int w = 0; w < 9; w++)
						{
							for (int z = w + 1; z < 9; z++)
							{
								if (z < 9)
								{
									if (c[w] != 0 && c[z] != 0)
									{
										if (c[w] == c[z])
											return false;
									}
								}
							}
						}
						ns = 0;
					}
				}
			}
		}
	}

	// 如果依次判断后，无重复，则返回正确
	return true;
}


// 将数组全部置为 false
void Tofalse()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			newmatrix[i][j] = false;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Point[i][j] = false;
		}
	}
}


// 判断九宫格里面有没有这个数
int CheckNumber(int n)
{
	int c[9];
	int ns = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int p = 0; p < 3; p++)
			{
				for (int q = 0; q < 3; q++)
				{
					c[ns] = matrix[i * 3 + p][j * 3 + q];
					ns++;
					if (ns == 9)		//将每一宫中的数存储到一个一维数组中进行判断
					{
						for (int w = 0; w < 9; w++)
						{
							if (c[w] == n)
								Point[i][j] = true;
						}
						ns = 0;
					}
				}
			}
		}
	}
	return 0;
}


// 对行列进行赋值
int Totrue(int number)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (matrix[i][j] == number)
			{
				for (int p = 0; p < 9; p++)
				{
					newmatrix[i][p] = true;
					newmatrix[p][j] = true;
				}
			}
			if (matrix[i][j] != 0)
			{
				newmatrix[i][j] = true;
			}
		}
	}
	return 0;
}


// 第二次判断
bool SecondCheck()
{
	for (int number = 1; number < 10; number++)
	{
		Tofalse();					// 将数组初始化为假
		CheckNumber(number);		// 将有这个数的宫格进行赋值
		Totrue(number);				// 将含有这个数的行列都赋为真

		// 开始判断第一个宫格是否存在这个数，如果存在，则判断下一个，如果存在，判断它里面是否为假
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (Point[i][j] == false)
				{
					int nums = 0;
					for (int p = 0; p < 3; p++)
					{
						for (int q = 0; q < 3; q++)
						{
							if (newmatrix[i * 3 + p][j * 3 + q] == false)
							{
								nums++;
							}
						}
					}
					if (nums>0)
					{
						nums = 0;
					}
					else
						return false;
				}
			}
		}
	}
	return true;
}