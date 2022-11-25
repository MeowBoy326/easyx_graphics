#include"conversion.h"

/*------------------------全局变量-------------------------*/

MyChar S[65][100];                          //记录输入的数字
MyChar s0[] = { _T("再玩就玩坏了！！！") };    //错误反馈
int ZH(-1);                                 //输入数字的长度
bool button3[10] = { true };              //标记选择的是哪个进制
bool button2[10] = { false };             //标记选择的是哪个进制
 

/***********************************进制转换**************************************/

bool input(int n) 
{
	for (int i = 8; i >= 0; i--) 
	{
		if (button3[i])
		{
			if (n < 10 - i)
				return true;
			else 
				return false;
		}
	}
	return false;
}
void updatewithinput3()
{
	MOUSEMSG m;//定义鼠标消息
	while (MouseHit()) //检查是否有鼠标消息
	{
		m = GetMouseMsg();
		for (int i = 0; i < 4 && !button1[7]; i++) 
		{
			for (int j = 0; j < 3; j++) 
			{
				if (m.x > i * 102 && m.x < i * 102 + 95 && m.y>445 + j * 52 && m.y < 495 + j * 52) 
				{
					button[i][j] = true;
					if (m.uMsg == WM_LBUTTONDOWN) 
					{
						if (ZH < 18 || ZH < 18 && button3[0] || ZH < 60 && button3[8] || ZH < 39 && button3[7] ||
							ZH < 30 && button3[6] || ZH < 26 && button3[5] || ZH < 23 && button3[4] || ZH < 21 && button3[3] ||
							ZH < 19 && button3[2]) 
						{
							if (j == 2 && i == 0)S[0][++ZH] = '1';
							else if (j == 2 && i == 1 && input(2))S[0][++ZH] = '2';
							else if (j == 2 && i == 2 && input(3))S[0][++ZH] = '3';
							else if (j == 1 && i == 0 && input(4))S[0][++ZH] = '4';
							else if (j == 1 && i == 1 && input(5))S[0][++ZH] = '5';
							else if (j == 1 && i == 2 && input(6))S[0][++ZH] = '6';
							else if (j == 0 && i == 0 && input(7))S[0][++ZH] = '7';
							else if (j == 0 && i == 1 && input(8))S[0][++ZH] = '8';
							else if (j == 0 && i == 2 && input(9))S[0][++ZH] = '9';
							else if (j == 1 && i == 3)S[0][++ZH] = '0';
							everone();
						}
						if (j == 0 && i == 3 && ZH >= 0) 
						{
							S[0][ZH--] = '\0';
							everone();
						}
						else if (j == 2 && i == 3)
						{
							memset(S[0], 0, sizeof(S[0]));
							everone();
							ZH = -1;
						}
					}
				}
				else button[i][j] = false;
			}
		}
		if (button1[7]) 
		{
			for (int i = 0; i < 9; i++)
			{
				if (m.y >= 55 + 40 * i&&m.y <= 95 + 40 * i)
				{
					button2[i] = true;
					if (m.uMsg == WM_LBUTTONDOWN) {
						button1[7] = false;
						button3[i] = true;
						memset(S[0], 0, sizeof(S[0]));
						everone();
						ZH = -1;
						for (int j = 0; j < 9; j++)
							if (i != j)
								button3[j] = false;
					}
				}
				else 
				{
					button2[i] = false;
					if (m.uMsg == WM_LBUTTONDOWN)
						button1[7] = false;
				}
			}
			if (m.uMsg == WM_MOUSEWHEEL)
			{
				if (m.wheel < 0)
					fly1 -= 80;
				else
					fly1 += 80;
			}
		}
		if (m.x > 5 && m.x < 40 && m.y > 0 && m.y < 35) //设置
		{
			help[0] = true;
			if (m.uMsg == WM_LBUTTONDOWN) software[0] = -1, software[2] = 6;
		}
		else help[0] = false;

		if (m.x > 350 && m.x < 380 && m.y>15 && m.y < 45)button1[5] = true;
		else button1[5] = false;

		if (m.x > 382 && m.x < 400 && m.y>405 && m.y < 425) 
		{
			button1[6] = true;
			if (m.uMsg == WM_LBUTTONDOWN) 
			{
				button1[7] = true;
			}
		}
		else button1[6] = false;
		if (m.uMsg == WM_MOUSEWHEEL && !button1[7]) 
		{
			if (m.wheel < 0)
				fly -= 40;
			else
				fly += 40;
		}
	}
	if (fly > 0)
		fly -= (fly / 3);
	if (fly < -1470)
		fly += -(fly + 1470) / 3;

	if (fly1 > 0)
		fly1 -= (fly1 / 3);
	if (fly1 < 0)
		fly1 += -fly1 / 3;
}

void showscreen3() 
{
	BeginBatchDraw();//开始批量绘图

	setbkmode(TRANSPARENT);
	setfillstyle(BS_SOLID);
	
	changecolor(0, 400, 45, 400, 0.0008f, 0.3f);//改变背景颜色

	settextcolor(RGB(194, 203, 223));
	settextstyle(20, 0, _T("微软雅黑"), 0, 0, 50, false, false, false);
	if (int(_tcslen(S[1]) < 45))outtextxy(5, 50 + fly, _T("  2 :"));
	else outtextxy(5, 46 + fly, _T("  2 :"));
	for (int i = 3; i < 63; i++) 
	{
		_stprintf_s(S[64], _T("%3d :"), i);
		outtextxy(5, 80 + 30 * (i - 3) + fly, S[64]);
	}

	if (S[0][0] == '\0') 
	{
		for (int i = 0; i < 61; i++)
			outtextxy(40, 50 + 30 * i + fly, _T("0"));
	}
	else {
		if (int(_tcslen(S[1]) < 44)) 
		{
			RECT r1 = { 40 ,50 + fly ,395,70 + fly };
			drawtext(S[1], &r1, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_MODIFYSTRING);
		}
		else 
		{
			RECT r1 = { 40 ,45 + fly ,395,80 + fly };
			drawtext(S[1], &r1, DT_WORDBREAK | DT_INTERNAL);
		}
		for (int i = 0; i < 60; i++) 
		{
			RECT r1 = { 40,80 + i * 30 + fly,400,100 + i * 30 + fly };
			drawtext(S[i + 2], &r1, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_MODIFYSTRING);
		}
	}

	if (button1[7]) 
	{
		IMAGE blacks = setimage(400, 360, RGB(0, 0, 0));//设置绘图
		my_putimage(0, 45, &blacks, RGB(255, 255, 255), 0, 1, 80, 0);
		settextstyle(25, 0, _T("微软雅黑"), 0, 0, 50, false, false, false);
		for (int i = 0; i < 9; i++) 
		{
			if (button2[8-i])
				settextcolor(HSLtoRGB(190, 1, 0.5));
			else 
				settextcolor(WHITE);
			if (button3[i])
			{
				setfillcolor(RGB(100, 100, 100));
				setfillstyle(BS_SOLID);
				solidrectangle(0, fly1 + 47 + 40 * i, 400, fly1 + 85 + 40 * i);
			}
			MyChar s[30];
			_stprintf_s(s, _T("输入%d进制数"), i + 2);
			outtextxy(150, 55 + 40 * (8 - i) + fly1, s);
		}
	}

	changecolor(0, 400, 0, 45, 0.0008f, 0.3f);
	changecolor(0, 400, 400, 600, 0.0008f, 0.3f);

	settextcolor(WHITE);
	settextstyle(30, 0, _T("微软雅黑"), 0, 0, 900, 0, 0, 0);
	outtextxy(40, 10, _T("进制转换"));
	if (help[0])settextcolor(RGB(0, 255, 255));
	else settextcolor(WHITE);
	settextstyle(30, 30, _T("微软雅黑"));
	outtextxy(0, 10, _T("≡"));
	settextstyle(50, 10, _T("微软雅黑"));

	IMAGE blacks = setimage(100, 50, RGB(0, 0, 0));//设置绘图

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (j < 3 && i <= 2 || j == 1 && i == 3) 
			{
				if (!button[i][j])my_putimage(i * 102, 444 + j * 52, &blacks, RGB(255, 255, 255), 0, 1, 90, 0);
				else my_putimage(i * 102, 444 + j * 52, &blacks, RGB(255, 255, 255), 0, 1, 50, 0);
			}
			else
			{
				if (!button[i][j])my_putimage(i * 102, 444 + j * 52, &blacks, RGB(255, 255, 255), 0, 1, 80, 0);
				else
				{
					IMAGE black = setimage(100, 50, RGB(240, 0, 0));//设置绘图
					my_putimage(i * 102, 444 + j * 52, &black, RGB(255, 255, 255), 0, 1, 70, 0);
				}
			}
		}
	}

	settextstyle(30, 0, _T("微软雅黑"), 0, 0, 900, 0, 0, 0);
	settextcolor(RGB(255, 255, 255));
	setbkmode(TRANSPARENT);
	settextstyle(22, 0, _T("Consolas"));
	outtextxy(322, 459, _T("delete"));
	settextstyle(30, 0, _T("Consolas"));
	outtextxy(40, 560, '1');
	outtextxy(142, 560, '2');
	outtextxy(244, 560, '3');
	outtextxy(40, 508, '4');
	outtextxy(142, 508, '5');
	outtextxy(244, 508, '6');
	outtextxy(40, 456, '7');
	outtextxy(142, 456, '8');
	outtextxy(244, 456, '9');
	outtextxy(346, 560, 'C');
	outtextxy(346, 508, '0');

	settextstyle(25, 0, _T("微软雅黑"), 0, 0, 50, false, false, false);
	if (!button1[6])settextcolor(WHITE);
	else settextcolor(HSLtoRGB(190, 1, 0.5));
	if (!button1[7])outtextxy(380, 405, _T("▲"));
	else outtextxy(380, 405, _T("▼"));

	if (ZH == -1) 
	{
		settextcolor(WHITE);
		RECT r1 = { 10,390 ,380,450 };
		settextstyle(60, 0, _T("微软雅黑"), 0, 0, 900, false, false, false);
		drawtext('0', &r1, DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_MODIFYSTRING);
	}
	else if (ZH < 18 || ZH < 18 && button3[0] || ZH < 60 && button3[8] || ZH < 39 && button3[7] ||
		ZH < 30 && button3[6] || ZH < 26 && button3[5] || ZH < 23 && button3[4] || ZH < 21 && button3[3] ||
		ZH < 19 && button3[2])
	{
		settextcolor(WHITE);
		RECT r1 = { 10 ,390 ,380,450 };
		callen1(S[0]);//计算字符串长度
		drawtext(S[0], &r1, DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_MODIFYSTRING);
	}
	else
	{
		settextcolor(WHITE);
		RECT r1 = { 10 ,390 ,380,450 };
		settextstyle(35, 0, _T("微软雅黑"));
		drawtext(s0, &r1, DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_MODIFYSTRING);
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
		
		IMAGE blacks = setimage(180, 130, RGB(0, 0, 0));//设置绘图
		my_putimage(210, 50, &blacks, RGB(255, 255, 255), 0, 0, 80, 0);

		setlinecolor(RGB(0, 238, 238));
		rectangle(210, 50, 390, 180);
		settextcolor(RGB(194, 203, 223));
		settextstyle(22, 0, _T("微软雅黑"));
		outtextxy(220, 55, _T("输入n进制数可以转换"));
		outtextxy(220, 80, _T("为其他进制的数( 2-62"));
		outtextxy(220, 105, _T("进制),用小写字母a-z"));
		outtextxy(220, 130, _T("表示10-35，大写字母"));
		outtextxy(220, 155, _T("A-Z表示36-61。"));
	}
	EndBatchDraw();
}

void conversion(MyChar *sss, long long x, int n)
{

	std::stack<int> t;//声明栈

	while (x) 
	{
		t.push(x%n);//入栈
		x /= n;
	}
	memset(sss, 0, sizeof(sss));//初始化sss
	int i(0);
	while (!t.empty()) //如果不为空
	{
		int k = t.top();
		char s;
		t.pop();
		if (k <= 9)s = k + '0';
		else if (k > 9 && k <= 35)s = k - 10 + 'a';
		else s = k - 36 + 'A';
		if (i == 44)sss[i++] = '\n';
		sss[i++] = s;
	}
}

void memse()//初始化函数
{
	for (int i = 1; i < 61; i++)
		memset(S[i], 0, sizeof(S[i]));
}

void everone(int n) 
{
	memse();

	int t(0);
	for (int i = 0; i < 9; i++)
	{
		if (button3[i]) 
		{
			t = i;
			break;
		}
	}
	long long sum(0);
	for (int i = 0; i < (int)_tcslen(S[0]); i++) 
	{
		sum += sum * (9 - t) + S[0][i] - '0';
	}
	for (int i = 1; i < 62; i++)
		conversion(S[i], sum, i + 1);//进制
}

void changecolor(int Left, int Right, int Top, int Bottom, float l, float k, bool t)
{

	H += k;	                    // 色相
	float S = 1;		        // 饱和度
	float L = 0.2f;		        // 亮度
	if (H > 360)H = 0;
	for (int y = Left; y < Right; y++) 
	{
		if (!t)
		{
			L += l;
			setlinecolor(HSLtoRGB(H, S, L));
		}
		else 
		{
			L += l;
			setlinecolor(HSLtoRGB(float(((int)H + 150) % 360), S, L));
		}
		line(y, Top, y, Bottom);
	}
}
