#include"set.h"

#define H_XS (int)round(fly1/(double)40)			// 处理上下滑动所致的坐标不精确

bool buttons[101] = { false };						// 选择哪个功能的标志
int colors(0);										// 随机颜色变量

/****************************设置**************************************/

void updatewithinput0()
{
	MOUSEMSG m;				// 定义鼠标消息
	while (MouseHit())		// 检查是否有鼠标消息
	{
		m = GetMouseMsg();
		for (int i = 2 + H_XS + 50; i < 21 + H_XS + 50; i++)
		{
			if (m.x > 0 && m.x<300 && m.y>(i - 50) * 40 && m.y < 40 + (i - 50) * 40 && m.y>80 && m.y < 600)
			{
				buttons[i] = true;
				if (m.uMsg == WM_LBUTTONDOWN)
				{
					if (i != 20 + H_XS + 50)
					{
						software[0] = i - 2 - H_XS - 50;
						software[1] = i - 2 - H_XS - 50;
						software[2] = i - H_XS - 50;
					}
					if (i == 20 + H_XS + 50)
					{
						buttons[100] = true;
						software[2] = i - H_XS - 50;
					}
					else buttons[100] = false;
				}
			}
			else buttons[i] = false;
		}

		if (m.x > 5 && m.x < 40 && m.y > 0 && m.y < 35)	// 设置
		{
			buttons[99] = true;
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				software[0] = software[1];
				static int n;
				n++;
				if (n % 2)help[1] = false;
				else
				{
					help[1] = true;
					buttons[100] = false;
				}
			}
		}
		else
		{
			buttons[99] = false;
			if (m.uMsg == WM_LBUTTONDOWN && m.x > 300)
			{
				software[0] = software[1];
				help[1] = true;
				buttons[100] = false;
			}
		}
		if (m.uMsg == WM_MOUSEWHEEL)
		{
			if (m.wheel < 0)
				fly1 -= 40;
			else
				fly1 += 40;
		}
	}

	if (fly1 > 0)
		fly1 -= fly1 / 2;
	if (fly1 < -240)
		fly1 += -((fly1 + 240) / 2);
}


void showscreen0()
{
	BeginBatchDraw();

	float H = float(colors++);	// 色相
	float S = 1;				// 饱和度
	float L = 0.4f;				// 亮度
	if (colors > 360)colors = 1;
	for (int y = 0; y < 300; y++)
	{
		L -= 0.001f;
		setlinecolor(HSLtoRGB(H, S, L));
		line(y, 50, y, 600);
	}

	for (int i = 2 + H_XS + 50; i < 21 + H_XS + 50; i++)
	{
		if (buttons[i])
		{
			float H = float((colors + 100) % 360);	// 色相
			setlinecolor(HSLtoRGB(50, 1, 0.5));
			setfillcolor(HSLtoRGB(H, 1, 0.5));
			solidrectangle(0, 40 * (i - 50), 299, 40 + 40 * (i - 50));
			line(0, 40 * (i - 50), 299, 40 * (i - 50));
			line(0, 40 + 40 * (i - 50), 299, 40 + 40 * (i - 50));
		}
		for (int j = 0; j < 6; j++)
		{
			setlinecolor(HSLtoRGB(60, 1, 0.5));
			line(j, 40 * software[2] + 5 + fly1, j, 35 + 40 * software[2] + fly1);
		}
		
	}
	settextstyle(25, 0, _T("微软雅黑"), 0, 0, 900, false, false, false);
	settextcolor(WHITE);
	outtextxy(20, 85 + fly1, _T("⑴"));
	outtextxy(20, 125 + fly1, _T("⑵"));
	outtextxy(20, 165 + fly1, _T("⑶"));
	outtextxy(20, 205 + fly1, _T("⑷"));
	outtextxy(20, 245 + fly1, _T("⑸"));
	outtextxy(20, 285 + fly1, _T("⑹"));
	outtextxy(20, 325 + fly1, _T("⑺"));
	outtextxy(20, 365 + fly1, _T("⑻"));
	outtextxy(20, 405 + fly1, _T("⑼"));
	outtextxy(20, 445 + fly1, _T("⑽"));
	outtextxy(20, 485 + fly1, _T("⑾"));
	outtextxy(20, 525 + fly1, _T("⑿"));
	outtextxy(20, 565 + fly1, _T("⒀"));
	outtextxy(20, 605 + fly1, _T("⒁"));
	outtextxy(20, 645 + fly1, _T("⒂"));
	outtextxy(20, 685 + fly1, _T("⒃"));
	outtextxy(20, 725 + fly1, _T("⒄"));
	outtextxy(20, 765 + fly1, _T("⒅"));
	outtextxy(20, 805 + fly1, _T("⒆"));

	outtextxy(20, 85 + fly1, _T("      标准"));
	outtextxy(20, 125 + fly1, _T("      科学"));
	outtextxy(20, 165 + fly1, _T("      超大数运算"));
	outtextxy(20, 205 + fly1, _T("      解一元一次方程"));
	outtextxy(20, 245 + fly1, _T("      进制转换"));
	outtextxy(20, 285 + fly1, _T("      数据转换"));
	outtextxy(20, 325 + fly1, _T("      长度转换"));
	outtextxy(20, 365 + fly1, _T("      面积转换"));
	outtextxy(20, 405 + fly1, _T("      体积转换"));
	outtextxy(20, 445 + fly1, _T("      时间转换"));
	outtextxy(20, 485 + fly1, _T("      温度转换"));
	outtextxy(20, 525 + fly1, _T("      速度转换"));
	outtextxy(20, 565 + fly1, _T("      重量转换"));
	outtextxy(20, 605 + fly1, _T("      能量转换"));
	outtextxy(20, 645 + fly1, _T("      功率转换"));
	outtextxy(20, 685 + fly1, _T("      压力转换"));
	outtextxy(20, 725 + fly1, _T("      角度转换"));
	outtextxy(20, 765 + fly1, _T("      帮助"));
	outtextxy(20, 805 + fly1, _T("      关于"));

	float l = 0.4f;					// 亮度
	for (int y = 0; y < 300; y++)
	{
		l -= 0.001f;
		setlinecolor(HSLtoRGB(H, S, l));
		line(y, 0, y, 80);
	}
	if (buttons[99])settextcolor(RGB(0, 255, 255));
	else settextcolor(WHITE);

	settextstyle(30, 30, _T("微软雅黑"));
	outtextxy(0, 10, _T("≡"));
	settextstyle(25, 0, _T("微软雅黑"));
	settextcolor(WHITE);
	outtextxy(20, 45, _T("计算器"));

	if (buttons[100])
	{
		IMAGE black = setimage(350, 300, RGB(0, 0, 0));	// 设置绘图
		my_putimage(0, 260, &black, RGB(255, 255, 255), 0, 1, 90, 0);
		setlinecolor(RGB(0, 238, 238));
		rectangle(0, 260, 350, 560);
		settextcolor(RGB(194, 203, 223));
		settextstyle(27, 0, _T("Consolas"));
		outtextxy(150, 270, _T("关于"));
		settextstyle(22, 0, _T("Consolas"));
		outtextxy(10, 320, _T("名    称：计算器"));
		outtextxy(10, 360, _T("作    者：尔灵尔亿"));
		outtextxy(10, 400, _T("编译环境：VS 2017 Community"));
		outtextxy(10, 440, _T("图 形 库：EasyX_20190219(beta)"));
		outtextxy(10, 480, _T("时    间：2019.1.20 — 2019.2.28"));
		outtextxy(10, 520, _T("最后修改：2019.2.28"));
	}
	else buttons[100] = false;

	EndBatchDraw();	// 结束批量绘图
}