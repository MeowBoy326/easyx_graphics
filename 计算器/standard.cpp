#include"standard.h"

using namespace std;

/************************全局变量**************************/
T ZFC[1000] = { 0 };                    	// 记录输入的每一个数字
T ZFC1[1000] = { 0 };                   	// 记录输入的算式
T ZFC2[1000] = { 0 };                   	// 存储中缀表达式转换为后缀的结果
T ZFC3[1000] = { 0 };                   	// 记录计算结果
int D(-1);                              	// 输入数字的长度
int D1(0);                              	// 输入的算式的长度
int kh(0);                              	// 计算左括号的数量
int hds(0);                             	// 标记字符串多长就可以滑动
int screenmove(0);                      	// 由于算式不能完全显示。算式的左右移动像素
int fx(0), fy(0);                       	// 判断是否可以左或者有移动算式
int color(0), color1(0);                	// 如果左或者右可以移动，颜色变化
bool hd(false), hd1(false);             	// 判断是否可以滑动
bool xsd(false);                        	// 判断是否可以按小数点

typedef struct node                   		// 栈的结构体
{
	T data;
	struct node *next;
}Stack;
Stack *t = NULL;


void screenmovehd()
{
	if (hd && hds < 60)		{		hds += 10;		screenmove += 10;	}
	if (hds >= 60)			{		hd = false;		hds = 0;			}
	if (hd1 && hds < 60)	{		hds += 10;		screenmove -= 10;	}
	if (hds >= 60)			{		hd1 = false;	hds = 0;			}
}


// 计算fps
float getfps()
{
	static int i(0);
	static DWORD oldtime = GetTickCount();
	static float fps(0);
	if (i > 8)
	{
		i = 0;
		int newtime = GetTickCount();
		int elapsedtime = newtime - oldtime;
		fps = 8 / (elapsedtime / 1000.0f);
		oldtime = newtime;
	}
	i++;
	return fps;
}

void updatewithinput_()
{
	MOUSEMSG m;	// 定义鼠标消息
	while (MouseHit())	// 检查是否有鼠标消息
	{
		m = GetMouseMsg();
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (m.x > i * 102 + 3 && m.x < i * 102 + 90 && m.y>340 + j * 52 && m.y < 385 + j * 52)
				{
					button[i][j] = true;
					if (m.uMsg == WM_LBUTTONDOWN)
					{
						if (ZFC3[0] != '\0')
						{
							memset(ZFC, 0, sizeof(ZFC));
							memset(ZFC3, 0, sizeof(ZFC3));
						}
						if (D < 17)
						{
							if (j == 3 && i == 0)ZFC[++D] = '1';
							else if (j == 3 && i == 1)ZFC[++D] = '2';
							else if (j == 3 && i == 2)ZFC[++D] = '3';
							else if (j == 2 && i == 0)ZFC[++D] = '4';
							else if (j == 2 && i == 1)ZFC[++D] = '5';
							else if (j == 2 && i == 2)ZFC[++D] = '6';
							else if (j == 1 && i == 0)ZFC[++D] = '7';
							else if (j == 1 && i == 1)ZFC[++D] = '8';
							else if (j == 1 && i == 2)ZFC[++D] = '9';
							else if (j == 0 && i == 1)ZFC[++D] = '0';
							else if (j == 4 && i == 1)
							{
								if (!xsd&&ZFC[D] >= '0'&&ZFC[D] <= '9')
								{
									ZFC[++D] = '.';
									xsd = true;
								}
							}
						}
						if (j == 4 && i == 0) 
						{
							memset(ZFC, 0, sizeof(ZFC));
							ZFC[++D] = '(';
							xsd = false;
							D = -1;kh++;
						}
						else if (j == 0 && i == 0)
						{
							memset(ZFC, 0, sizeof(ZFC));
							memset(ZFC1, 0, sizeof(ZFC1));
							D = -1; D1 = 0; xsd = false;
						}
						else if (j == 0 && i == 2)
						{
							if (ZFC[D] == '.')xsd = false;
							if (D >= 0)ZFC[D--] = '\0';
						}
						else if (j == 4 && i == 2 && ZFC[D] != '.')
						{
							if (kh > 0) {
								ZFC[++D] = ')';
								kh--;
							}
						}
						else if (j == 0 && i == 3 && ZFC[D] != '.')
						{
							_tcscat_s(ZFC1, ZFC); D1 += D;
							if (D != -1) 
								ZFC1[++D1] = L'÷';
							else 
								ZFC1[D1] = L'÷';
							D = -1, ZFC1[++D1] = '\0';
							xsd = false;
							memset(ZFC, 0, sizeof(ZFC));
						}
						else if (j == 1 && i == 3 && ZFC[D] != '.')
						{
							_tcscat_s(ZFC1, ZFC), D1 += D;
							if (D != -1)
								ZFC1[++D1] = L'×';
							else 
								ZFC1[D1] = L'×';
							D = -1, ZFC1[++D1] = '\0';
							xsd = false;
							memset(ZFC, 0, sizeof(ZFC));
						}
						else if (j == 2 && i == 3 && ZFC[D] != '.')
						{
							_tcscat_s(ZFC1, ZFC), D1 += D;
							if (D != -1) 
								ZFC1[++D1] = '-';
							else 
								ZFC1[D1] = '-';
							D = -1, ZFC1[++D1] = '\0';
							xsd = false;
							memset(ZFC, 0, sizeof(ZFC));
						}
						else if (j == 3 && i == 3 && ZFC[D] != '.')
						{
							_tcscat_s(ZFC1, ZFC), D1 += D;
							if (D != -1) 
								ZFC1[++D1] = '+';
							else 
								ZFC1[D1] = '+';
							D = -1, ZFC1[++D1] = '\0';
							xsd = false;
							memset(ZFC, 0, sizeof(ZFC));
						}
						else if (j == 4 && i == 3)
						{
							fx = 0, fy = 0;
							screenmove = 0;
							_tcscat_s(ZFC1, ZFC);
							D1 += D;
							if (!(ZFC1[D1] >= '0'&&ZFC1[D1] <= '9') && ZFC1[D1] != ')'&&ZFC1[D1] != '(') 
								ZFC1[++D1] = '0';
							D1 = 0, D = -1;
							xsd = false;
							change();
							memset(ZFC1, 0, sizeof(ZFC1));
							memset(ZFC, 0, sizeof(ZFC));
						}

					}
				}
				else button[i][j] = false;
			}
		}

		if (m.x > 5 && m.x < 40 && m.y > 0 && m.y < 35)	// 设置
		{
			help[0] = true;
			if (m.uMsg == WM_LBUTTONDOWN) software[0] = -1, software[2] = 2, fx = 0, fy = 0, screenmove = 0;
		}
		else help[0] = false;

		if (m.x >= 5 && m.x < 40 && m.y>80 && m.y < 110 && fx == 1)
		{
			color = 1;
			if (m.uMsg == WM_LBUTTONDOWN)
				hd = true;
		}
		else color = 0;

		if (m.x >= 375 && m.x < 395 && m.y>80 && m.y < 110 && fy == 1)
		{
			color1 = 1;
			if (m.uMsg == WM_LBUTTONDOWN)
				hd1 = true;
		}
		else color1 = 0;
	}
}


void showscreen_()
{
	BeginBatchDraw();

	setbkmode(TRANSPARENT);
	setfillstyle(BS_SOLID);
	settextstyle(60, 0, _T("微软雅黑"), 0, 0, 900, false, false, false, 
	             DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
		         PROOF_QUALITY, DEFAULT_PITCH);
	changecolor(0, 400, 0, 600);

	IMAGE black = setimage(400, 600, RGB(0, 0, 0));	// 设置绘图
	my_putimage(0, 0, &black, RGB(255, 255, 255), 0, 1, 30, 0);

	settextstyle(17, 0, _T("微软雅黑"), 0, 0, 20, false, false, false);
	MyChar fps[20];
	_stprintf_s(fps, _T("fps : %.2lf"), getfps());
	outtextxy(4, 0, fps);

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
					else if (j == 4 && i == 0 || j == 4 && i == 2 || j <= 4 && j >= 0 && i == 3)
					{
						IMAGE green = setimage(100, 50, GREEN);	// 设置绘图
						my_putimage(i * 102, 340 + j * 52, &green, RGB(255, 255, 255), 0, 1, 60, 0);
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
	settextcolor(RGB(255, 255, 255));
	setbkmode(TRANSPARENT);
	settextstyle(23, 0,_T("Consolas") );
	outtextxy(223, 355, _T("delete"));
	settextstyle(30, 0, _T("Consolas"));
	outtextxy(40, 350, 'C');
	outtextxy(142, 560, '.');
	outtextxy(142, 350, '0');
	outtextxy(36, 560, '(');
	outtextxy(40, 508, '1');
	outtextxy(142, 508, '2');
	outtextxy(244, 508, '3');
	outtextxy(40, 456, '4');
	outtextxy(142, 456, '5');
	outtextxy(244, 456, '6');
	outtextxy(40, 404, '7');
	outtextxy(142, 404, '8');
	outtextxy(244, 404, '9');
	outtextxy(248, 560, ')');
	settextstyle(40, 0, _T("Consolas"));
	outtextxy(342, 500, '+');
	outtextxy(342, 344, _T("÷"));
	outtextxy(342, 396, _T("×"));
	outtextxy(342, 552, '=');
	settextstyle(40, 25, _T("Consolas"));
	outtextxy(339, 448, '-');
	settextcolor(WHITE);
	settextstyle(30, 0, _T("微软雅黑"), 0, 0, 900, 0, 0, 0);
	outtextxy(40, 10, _T("标准"));
	if (help[0])settextcolor(RGB(0, 255, 255));
	else settextcolor(WHITE);

	settextstyle(30, 30, _T("微软雅黑"));
	outtextxy(0, 10, _T("≡"));

	screenmovehd();	// 字符串滑动动画

	if ((int)(_tcslen(ZFC1) * 16) >= 400 + screenmove)fx = 1;
	else fx = 0;

	if (screenmove > 0)fy = 1;
	else fy = 0;

	if (fx != 0)
	{
		settextstyle(30, 00, _T("微软雅黑"));
		if (!color)settextcolor(WHITE);
		else settextcolor(RGB(0, 255, 255));
		outtextxy(10, 83, _T("<"));
	}

	if (fy != 0)
	{
		settextstyle(30, 00, _T("微软雅黑"));
		if (!color1)settextcolor(WHITE);
		else settextcolor(RGB(0, 255, 255));
		outtextxy(370, 83, _T(">"));
	}

	if (help[2])
	{
		setlinecolor(RGB(0, 238, 238));
		rectangle(315, 45, 355, 65);
		settextcolor(RGB(194, 203, 223));
		settextstyle(20, 0, _T("微软雅黑"));
		outtextxy(320, 45, _T("换肤"));
	}

	settextcolor(WHITE);
	if (ZFC3[0] == '\0')
	{
		if (D == -1)
		{
			RECT r1 = { 10,200 ,380,300 };
			settextstyle(60, 0, _T("微软雅黑"), 0, 0, 900, false, false, false);
			drawtext('0', &r1, DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_MODIFYSTRING);
		}
		else
		{
			RECT r1 = { 10,200 ,380,300 };
			callen(ZFC);	// 计算字符串长度
			drawtext(ZFC, &r1, DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_MODIFYSTRING);
		}

		if (D1 != 0)
		{
			RECT r1 = { -10010,100 ,400 + screenmove,150 };
			callen(ZFC1);	// 计算字符串长度
			drawtext(ZFC1, &r1, DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_MODIFYSTRING);
		}
	}
	else
	{
		RECT r1 = { 10,100 ,400,150 };
		callen(ZFC3);
		drawtext(ZFC3, &r1, DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_MODIFYSTRING);
	}
	EndBatchDraw();
}


void push(T c)	// 入栈
{
	Stack *s;
	s = (Stack*)malloc(sizeof(Stack));
	s->data = c;
	s->next = t;
	t = s;
}


bool empty()	// 判断栈是否为空
{
	if (!t)return true;
	return false;
}


void pop()		// 出栈
{
	Stack *s;
	if (!empty())
	{
		s = t->next;
		free(t);
		t = s;
	}
}


T top()	// 取栈顶元素
{
	T s;
	s = '#';
	if (!empty()) s = t->data;
	return s;
}


void clearstack()	// 清空栈
{
	Stack *s;
	while (!empty()) {
		s = t->next;
		free(t);
		t = s;
	}
}


void calculate()	// 计算后缀表达式的值
{
	clearstack();
	double sum(A);
	MyChar s[100];
	stack<double> p;
	for (int i = 0; i < (int)(_tcslen(ZFC2)); i++)
	{
		if (ZFC2[i] >= '0'&&ZFC2[i] <= '9')
		{
			memset(s, 0, sizeof(s));
			int n(0);
			for (int j = i; j < (int)(_tcslen(ZFC2)); j++)
			{
				if (ZFC2[j] == '.' || ZFC2[j] >= '0'&&ZFC2[j] <= '9')
					s[n++] = ZFC2[j];
				else
				{
					i = j;
					break;
				}
			}
			s[n] = '\0';
			_stscanf_s(s, _T("%15lf"), &sum);
		}
		if (ZFC2[i] == '#'&&sum != A)
		{
			p.push(sum);
			sum = A;
		}

		double a, b;
		if (ZFC2[i] == '+')		{	a = p.top(); p.pop();	b = p.top(); p.pop();	p.push(a + b);	}
		if (ZFC2[i] == '-')		{	a = p.top(); p.pop();	b = p.top(); p.pop();	p.push(b - a);	}
		if (ZFC2[i] == '*')		{	a = p.top(); p.pop();	b = p.top(); p.pop();	p.push(a*b);	}
		if (ZFC2[i] == '/')		{	a = p.top(); p.pop();	b = p.top(); p.pop();	p.push(b / a);	}
	}
	if (p.top() != '#')
	{
		double x = p.top();
		_stprintf_s(ZFC3, _T("%.10lf"), x);
	}
	else _tcscpy_s(ZFC3, _T("违规操作！输入有误！"));
}


void change()	// 中缀表达式变为后缀表达式
{
	int a = (int)_tcslen(ZFC1), k(0);
	memset(ZFC2, 0, sizeof(ZFC2));
	for (int i = 0; i < a; i++)
	{
		if (ZFC1[i] >= '0'&&ZFC1[i] <= '9' || ZFC1[i] == '.')ZFC2[k++] = ZFC1[i];
		else if (ZFC1[i] == '(')push(ZFC1[i]), ZFC2[k++] = '#';
		else if (ZFC1[i] == '+' || ZFC1[i] == '-')
		{
			ZFC2[k++] = '#';
			while (top() == '-' || top() == '*' || top() == '/' || top() == '+'&&top() != '(')
			{
				ZFC2[k++] = top(), ZFC2[k++] = '#';
				pop();
			}
			push(ZFC1[i]);
		}
		else if (ZFC1[i] == '*' || ZFC1[i] == '/')
		{
			ZFC2[k++] = '#';
			while (top() == '*' || top() == '/'&&top() != '(')
			{
				ZFC2[k++] = '#', ZFC2[k++] = top();
				pop();
			}
			push(ZFC1[i]);
		}
		else if (ZFC1[i] == ')')
		{
			while (top() != '(' && !empty())
			{
				if (top() >= '0'&&top() <= '9')ZFC2[k++] = top();
				else if (top() == '+' || top() == '-' || top() == '*' || top() == '/')
				{
					ZFC2[k++] = '#';
					ZFC2[k++] = top();
				}
				pop();
			}
			pop();
		}
	}
	while (!empty())
	{
		ZFC2[k++] = '#';
		ZFC2[k++] = top();
		pop();
	}
	ZFC2[k++] = '#';
	calculate();
}