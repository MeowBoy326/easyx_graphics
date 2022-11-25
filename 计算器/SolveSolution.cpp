#include"SolveSolution.h"


/*---------------------------全局变量---------------------------------*/
MyChar xzfc[10000] = { 0 };								// 存储输入的字符串数字
MyChar Zfc[10000] = { 0 };								// 进行运算时的暂存
MyChar s[10000] = { 0 };								// 进行运算时的暂存
MyChar name[100] = { 0 };								// 存储未知数（变量）
MyChar solution[10000] = { 0 };							// 存储最后显示的结果
double bsum(0), zsum(0), xbsum(0), fsum(0);				// 分别存储方程左右两边的正负数
int n(0);												// 未知数的长度
int E(-1);												// 输入数的长度
int blx(0);												// 保证变量为一种
bool dyy(false);										// 保证一个方程中只有一个等于号
bool xxs(false);										// 保证一个数中只有一个小数点

/********************************解方程***********************************/
void updatewithinput2()
{
	MOUSEMSG m;	// 定义鼠标消息
	while (MouseHit())	// 检查是否有鼠标消息
	{
		m = GetMouseMsg();
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (m.x > i * 102 && m.x < i * 102 + 95 && m.y>340 + j * 52 && m.y < 385 + j * 52)
				{
					button[i][j] = true;
					if (m.uMsg == WM_LBUTTONDOWN)
					{
						if (solution[0] != '\0')memset(solution, 0, sizeof(solution));
						if (j == 3 && i == 0 && xzfc[E] != 'a' && xzfc[E] != 'b' && xzfc[E] != 'c')xzfc[++E] = '1';
						else if (j == 3 && i == 1 && xzfc[E] != 'a' && xzfc[E] != 'b' && xzfc[E] != 'c')xzfc[++E] = '2';
						else if (j == 3 && i == 2 && xzfc[E] != 'a' && xzfc[E] != 'b' && xzfc[E] != 'c')xzfc[++E] = '3';
						else if (j == 2 && i == 0 && xzfc[E] != 'a' && xzfc[E] != 'b' && xzfc[E] != 'c')xzfc[++E] = '4';
						else if (j == 2 && i == 1 && xzfc[E] != 'a' && xzfc[E] != 'b' && xzfc[E] != 'c')xzfc[++E] = '5';
						else if (j == 2 && i == 2 && xzfc[E] != 'a' && xzfc[E] != 'b' && xzfc[E] != 'c')xzfc[++E] = '6';
						else if (j == 1 && i == 0 && xzfc[E] != 'a' && xzfc[E] != 'b' && xzfc[E] != 'c')xzfc[++E] = '7';
						else if (j == 1 && i == 1 && xzfc[E] != 'a' && xzfc[E] != 'b' && xzfc[E] != 'c')xzfc[++E] = '8';
						else if (j == 1 && i == 2 && xzfc[E] != 'a' && xzfc[E] != 'b' && xzfc[E] != 'c')xzfc[++E] = '9';
						else if (j == 0 && i == 1 && xzfc[E] != 'a' && xzfc[E] != 'b' && xzfc[E] != 'c')xzfc[++E] = '0';
						else if (j == 2 && i == 3)
						{
							if (xzfc[E] != '-' && xzfc[E] != '+'&& xzfc[E] != '.')xzfc[++E] = '-';
							else xzfc[E] = '-';
							xxs = false;
						}
						else if (j == 3 && i == 3)
						{
							if (xzfc[E] != '-' && xzfc[E] != '+'&& xzfc[E] != '.')xzfc[++E] = '+';
							else xzfc[E] = '+';
							xxs = false;
						}
						else if (j == 4 && i == 1 && xzfc[E] != '.')
						{
							if (blx == 0 || blx == 2)
							{
								xzfc[++E] = 'b';
								blx = 2;
							}
						}
						else if (j == 4 && i == 0 && xzfc[E] != '.')
						{
							if (blx == 0 || blx == 1)
							{
								xzfc[++E] = 'a';
								blx = 1;
							}
						}
						else if (j == 4 && i == 2 && xzfc[E] != '.')
						{
							if (blx == 0 || blx == 3)
							{
								xzfc[++E] = 'c';
								blx = 3;
							}
						}
						else if (j == 4 && i == 3 && xzfc[E] != '.')
						{
							if (!dyy)xzfc[++E] = '=';
							dyy = true, xxs = false;
						}
						else if (j == 1 && i == 3) {
							if (!xxs&&xzfc[E] >= '0'&&xzfc[E] <= '9')
							{
								xzfc[++E] = '.';
								xxs = true;
							}
						}
						else if (j == 0 && i == 0)
						{
							memset(xzfc, 0, sizeof(xzfc));
							memset(solution, 0, sizeof(solution));
							E = -1, blx = 0, dyy = false, xxs = false;
							screenmove = 0;
						}
						else if (j == 0 && i == 2)
						{
							if (xzfc[E] == 'a' || xzfc[E] == 'b' || xzfc[E] == 'c')blx = 0;
							if (xzfc[E] == '=')dyy = false;
							if (xzfc[E] == '.')xxs = false;
							if (E >= 0)xzfc[E--] = '\0';
						}
						else if (j == 0 && i == 3)
						{
							E = -1;
							blx = 0, dyy = false, xxs = false;
							slovesolution();
							memset(xzfc, 0, sizeof(xzfc));
						}
					}
				}
				else button[i][j] = false;
			}
		}

		if (m.x > 5 && m.x < 40 && m.y > 0 && m.y < 35)	// 设置
		{
			help[0] = true;
			if (m.uMsg == WM_LBUTTONDOWN) software[0] = -1, software[2] = 5, fx = 0, fy = 0, screenmove = 0;
		}
		else help[0] = false;

		if (m.x > 350 && m.x < 380 && m.y>15 && m.y < 45)button1[5] = true;
		else button1[5] = false;

		if (m.x >= 5 && m.x < 40 && m.y>200 && m.y < 235 && fx == 1)
		{
			color = 1;
			if (m.uMsg == WM_LBUTTONDOWN)
				hd = true;
		}
		else color = 0;

		if (m.x >= 375 && m.x < 395 && m.y>200 && m.y < 235 && fy == 1)
		{
			color1 = 1;
			if (m.uMsg == WM_LBUTTONDOWN)
				hd1 = true;
		}
		else color1 = 0;
	}
}


void showscreen2()
{
	BeginBatchDraw();	// 开始批量绘图

	setbkmode(TRANSPARENT);
	setfillstyle(BS_SOLID);
	
	changecolor(0, 400, 0, 600, 0.001f);

	IMAGE black = setimage(400, 600, RGB(0, 0, 0));	// 设置绘图
	my_putimage(0, 0, &black, RGB(255, 255, 255), 0, 1, 30, 0);

	black = setimage(100, 50, RGB(0, 0, 0));	// 设置绘图

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (j >= 1 && j < 4 && i <= 2 || j == 0 && i == 1)
			{
				if (!button[i][j])
					my_putimage(i * 102, 340 + j * 52, &black, RGB(255, 255, 255), 0, 1, 90, 0);
				else
					my_putimage(i * 102, 340 + j * 52, &black, RGB(255, 255, 255), 0, 1, 50, 0);
			}
			else
			{
				if (!button[i][j])
					my_putimage(i * 102, 340 + j * 52, &black, RGB(255, 255, 255), 0, 1, 80, 0);
				else
				{
					if (i == 3 && j == 4 || j == 0 && i == 2 || j == 0 && i == 0)
					{
						IMAGE black = setimage(100, 50, RGB(240, 0, 0));	// 设置绘图
						my_putimage(i * 102, 340 + j * 52, &black, RGB(255, 255, 255), 0, 1, 50, 0);
					}
					else if (j <= 4 && j >= 2 && i == 3)
					{
						IMAGE green = setimage(100, 50, GREEN);	// 设置绘图
						my_putimage(i * 102, 340 + j * 52, &green, RGB(255, 255, 255), 0, 1, 60, 0);
					}
					else if (j == 0 && i == 3)
					{
						IMAGE black = setimage(100, 50, RGB(64, 0, 128));	// 设置绘图
						my_putimage(i * 102, 340 + j * 52, &black, RGB(255, 255, 255), 0, 1, 50, 0);
					}
					else
					{
						IMAGE black = setimage(100, 50, RGB(225, 100, 26));	// 设置绘图
						my_putimage(i * 102, 340 + j * 52, &black, RGB(255, 255, 255), 0, 1, 50, 0);
					}
				}
			}
		}
	}
	settextstyle(30, 0, _T("微软雅黑"), 0, 0, 900, 0, 0, 0);
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(23, 0, _T("Consolas"));
	outtextxy(220, 355, _T("delete"));
	outtextxy(320, 355, _T("result"));
	settextstyle(30, 0, _T("Consolas"));
	outtextxy(40, 350, 'C');
	outtextxy(142, 557, 'b');
	outtextxy(144, 350, '0');
	outtextxy(40, 557, 'a');
	outtextxy(40, 508, '1');
	outtextxy(142, 508, '2');
	outtextxy(244, 508, '3');
	outtextxy(40, 456, '4');
	outtextxy(142, 456, '5');
	outtextxy(244, 456, '6');
	outtextxy(40, 404, '7');
	outtextxy(142, 404, '8');
	outtextxy(244, 404, '9');
	outtextxy(244, 557, 'c');
	outtextxy(344, 400, '.');
	settextstyle(40, 0, _T("Consolas"));
	outtextxy(342, 500, '+');
	outtextxy(342, 552, '=');
	settextstyle(40, 25, _T("Consolas"));
	outtextxy(339, 448, '-');

	settextstyle(30, 0, _T("微软雅黑"));
	outtextxy(40, 10, _T("解一元一次方程"));
	if (help[0])settextcolor(RGB(0, 255, 255));
	else settextcolor(WHITE);
	settextstyle(30, 30, _T("微软雅黑"));
	outtextxy(0, 10, _T("≡"));
	settextstyle(50, 10, _T("微软雅黑"));

	settextcolor(WHITE);
	if ((int)(_tcslen(xzfc) * 17) > 400 + screenmove)fx = 1;
	else fx = 0;

	if (screenmove > 0)fy = 1;
	else fy = 0;

	if (fx != 0)
	{
		settextstyle(30, 0, _T("微软雅黑"));
		if (!color)settextcolor(WHITE);
		else settextcolor(RGB(0, 255, 255));
		outtextxy(10, 208, _T("<"));
	}
	if (fy != 0)
	{
		settextstyle(30, 0, _T("微软雅黑"));
		if (!color1)settextcolor(WHITE);
		else settextcolor(RGB(0, 255, 255));
		outtextxy(370, 208, _T(">"));
	}
	screenmovehd();

	settextcolor(WHITE);
	if (solution[0] == '\0')
	{
		if (E == -1)
		{
			RECT r1 = { 10,200 ,380,300 };
			settextstyle(60, 0, _T("微软雅黑"), 0, 0, 900, false, false, false);
			drawtext('0', &r1, DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_MODIFYSTRING);
		}
		else
		{
			RECT r1 = { -10000 ,200 ,380 + screenmove,300 };
			callen(xzfc);	// 计算字符串长度
			drawtext(xzfc, &r1, DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_MODIFYSTRING);
		}
	}
	else
	{
		screenmove = 0;
		RECT r1 = { 10,100 ,400,150 };
		if (_tcscmp(solution, _T("违规操作！请正确输入方程！ "))&& _tcscmp(solution, _T("违规操作！方程中无可解的未知量！ ")))
			callen(solution);
		else
			settextstyle(30, 0, _T("微软雅黑"), 0, 0, 900, false, false, false);
		drawtext(solution, &r1, DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_MODIFYSTRING);
	}

	if (!button1[5])
	{
		settextcolor(BLACK);
		settextstyle(40, 0, _T("微软雅黑"));
		outtextxy(350, 5, _T("★"));
	}
	else
	{
		settextcolor(RED);
		settextstyle(40, 0, _T("微软雅黑"));
		outtextxy(350, 5, _T("★"));

		IMAGE black = setimage(180, 130, RGB(0, 0, 0));	// 设置绘图
		my_putimage(210, 50, &black, RGB(255, 255, 255), 0, 0, 80, 0);

		setlinecolor(RGB(0, 238, 238));
		rectangle(210, 50, 390, 180);
		settextcolor(RGB(194, 203, 223));
		settextstyle(22, 0, _T("微软雅黑"));
		outtextxy(220, 55, _T("由于个人能力和时间有"));
		outtextxy(220, 80, _T("限所以很遗憾暂时只支"));
		outtextxy(220, 105, _T("持解一元一次方程。a,"));
		outtextxy(220, 130, _T("b,c,是未知量。a,b,c，"));
		outtextxy(220, 155, _T("一个方程只限用一种。"));
	}

	EndBatchDraw();
}


void mem()
{
	memset(Zfc, 0, sizeof(Zfc));
	memset(s, 0, sizeof(s));
	memset(name, 0, sizeof(name));
	memset(solution, 0, sizeof(solution));
	bsum = 0, zsum = 0, xbsum = 0, fsum = 0;
	E = -1, blx = 0;
}


void slovesolution()
{
	mem();	// 初始化

	if (Zfc[0] != '-')
		for (int i = 0; i <= (int)(_tcslen(xzfc)); i++)
			Zfc[i + 1] = xzfc[i];
	Zfc[0] = '+';
	MyChar *p = NULL;
	p = _tcschr(Zfc, '=');
	if (p == NULL || Zfc[_tcslen(Zfc) - 1] == '=')
	{
		_tcscpy_s(solution, _T("违规操作！请正确输入方程！ "));
		return;
	}

	int flag(0);
	for (int i = 0; i < (int)(_tcslen(xzfc)); i++)
	{
		if (xzfc[i] == 'a' || xzfc[i] == 'b' || xzfc[i] == 'c')
		{
			flag = 1;
			break;
		}
	}

	if (!flag)
	{
		_tcscpy_s(solution, _T("违规操作！方程中无可解的未知量！ "));
		return;
	}

	for (int i = 0; i < p - Zfc; i++)
	{
		if (Zfc[i] == '+')
		{
			int flag(0), m(0);
			for (int j = i + 1; j < p - Zfc; j++)
			{
				if (Zfc[j] == '-' || Zfc[j] == '+')flag = 1;
				if (flag == 0)s[m++] = Zfc[j];
			}
			s[m] = '\0';
			double t(0);
			if (s[_tcslen(s) - 1] >= 'a'&&s[_tcslen(s) - 1] <= 'z')
			{
				MyChar ss[10];
				if (_tcslen(s) == 1)bsum += 1;
				else
				{
					for (int j = 0; j < (int)(_tcslen(s) - 1); j++)ss[j] = s[j];
					ss[_tcslen(s) - 1] = '\0';
					_stscanf_s(ss, _T("%10lf"), &t);
					bsum += t;
				}
			}
			else
			{
				_stscanf_s(s, _T("%10lf"), &t);
				zsum += t;
			}
		}
		if (Zfc[i] == '-')
		{
			int flag(0), m(0);
			for (int j = i + 1; j < p - Zfc; j++)
			{
				if (Zfc[j] == '-' || Zfc[j] == '+')
				{
					flag = 1;
					break;
				}
				if (flag == 0)s[m++] = Zfc[j];
			}
			s[m] = '\0';
			double t(0);
			if (s[_tcslen(s) - 1] >= 'a'&&s[_tcslen(s) - 1] <= 'z')
			{
				MyChar ss[10];
				if (_tcslen(s) == 1)bsum -= 1;
				else
				{
					for (int j = 0; j < (int)(_tcslen(s) - 1); j++)
						ss[j] = s[j];
					ss[_tcslen(s) - 1] = '\0';
					_stscanf_s(ss, _T("%10lf"), &t);
					bsum -= t;
				}
			}
			else
			{
				_stscanf_s(s, _T("%10lf"), &t);
				zsum -= t;
			}
		}
	}
	if (Zfc[p - Zfc + 1] != '-')Zfc[p - Zfc] = '+';
	for (int i = (int)(p - Zfc); i < (int)(_tcslen(Zfc)); i++)
	{
		if (Zfc[i] == '+')
		{
			int flag(0), m(0);
			for (int j = i + 1; j < (int)(_tcslen(Zfc)); j++)
			{
				if (Zfc[j] == '-' || Zfc[j] == '+')flag = 1;
				if (flag == 0)s[m++] = Zfc[j];
			}
			s[m] = '\0';
			double t(0);
			if (s[_tcslen(s) - 1] >= 'a'&&s[_tcslen(s) - 1] <= 'z')
			{
				MyChar ss[10];
				if (_tcslen(s) == 1)xbsum += 1;
				else
				{
					for (int j = 0; j < (int)(_tcslen(s) - 1); j++)
						ss[j] = s[j];
					ss[_tcslen(s) - 1] = '\0';
					_stscanf_s(ss, _T("%10lf"), &t);
					xbsum += t;
				}
			}
			else
			{
				_stscanf_s(s, _T("%10lf"), &t);
				fsum += t;
			}
		}
		if (Zfc[i] == '-')
		{
			int flag(0), m(0);
			for (int j = i + 1; j < (int)(_tcslen(Zfc)); j++)
			{
				if (Zfc[j] == '-' || Zfc[j] == '+')
				{
					flag = 1;
					break;
				}
				if (flag == 0)s[m++] = Zfc[j];
			}
			s[m] = '\0';
			double t(0);
			if (s[_tcslen(s) - 1] >= 'a'&&s[_tcslen(s) - 1] <= 'z')
			{
				MyChar ss[10];
				if (_tcslen(s) == 1)xbsum -= 1;
				else
				{
					for (int j = 0; j < (int)(_tcslen(s) - 1); j++)
						ss[j] = s[j];
					ss[_tcslen(s) - 1] = '\0';
					_stscanf_s(ss, _T("%10lf"), &t);
					xbsum -= t;
				}
			}
			else
			{
				_stscanf_s(s, _T("%10lf"), &t);
				fsum -= t;
			}
		}
	}
	n = 0;
	memset(name, 0, sizeof(name));
	for (int i = 0; i < (int)(_tcslen(Zfc)); i++)
		if (Zfc[i] >= 'a' && Zfc[i] <= 'z')
		{
			for (int j = i; j < (int)(_tcslen(Zfc)); j++)
			{
				if (Zfc[j] >= 'a' && Zfc[j] <= 'z')
					name[n++] = Zfc[j];
				else break;
			}
			if (n)break;
		}

	name[n] = '\0';
	memset(solution, 0, sizeof(solution));
	_tcscat_s(solution, name);
	_tcscat_s(solution, _T("="));
	if (zsum - fsum == 0)
		_tcscat_s(solution, _T("0.00"));
	else
	{
		MyChar s[100] = { 0 };
		_stprintf_s(s, _T("%.10lf"), (zsum - fsum) / double(xbsum - bsum));
		_tcscat_s(solution, s);
	}
}