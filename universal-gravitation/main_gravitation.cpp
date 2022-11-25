////////////////////////////////////////
// 程序：万有引力运动
// 作者：Gary
// 编译环境：Visual C++ 6.0，EasyX_20211109
// 编写日期：2020-2-5

# include <math.h>
# include <graphics.h>
# include <string>
# include <stdlib.h>
# include <time.h>

static double pi = acos(-1);			// 圆周率 π
static HWND hOut;						// 画布

// 定义一个结构体，按钮
struct Node1
{
	int posx1, posy1, posx2, posy2;		// 坐标
	int mod;							// 模式
	double r;							// 圆按钮半径
	COLORREF color;						// 颜色
	LPTSTR text;						// 文字
};

// 定义一个结构体，小球
struct Node2
{
	double numx, numy;					// 坐标
	double m;							// 质量
	double fx, fy;						// 引力
	double vx, vy;						// 速度
	double ax, ay;						// 加速度
	COLORREF color;						// 颜色
};

// 定义一个类
class Gary
{
public:
	void carry();						// 主进程
	void initialization();				// 初始化
	void move();						// 窗口主视角
	void draw_scene();					// 绘制界面函数
	void draw_palette(int a);			// 绘制调色盘函数
	void draw_parameter();				// 绘制参数函数
	void draw_box();					// 绘制小球函数
	void draw_mouse();					// 绘制鼠标函数
	void creact_box();					// 生成小球函数
	void refresh_parameter();			// 更新参数函数
	Node1 boxm[50];						// 按钮，预制
	Node2 box[500];						// 小球，预制
	int exit_carry;						// 主循函数控制参数
	int exit_move;						// 开始界面控制参数
	int num_button;						// 按钮数量参数
	int num_box;						// 小球数量参数
	int flag_box;						// 小球编号
	int mouse_or_not;					// 鼠标是否开启参数
	int flash_or_not;					// 动画是否开启参数
	double gravitational_constant;		// 引力常数
	double ease_distance;				// 缓和距离
	double differential_time;			// 微分时间
	double mouse_quality;				// 鼠标质量
};


// 界面绘制函数
void Gary::draw_scene()
{
	TCHAR s[5];
	int i, j;
	// 背景绘制
	setbkcolor(WHITE);
	cleardevice();

	// 框框范围绘制
	setfillcolor(WHITE);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	line(0, 0, 500, 0);
	line(0, 0, 0, 500);
	line(0, 500, 500, 500);
	fillrectangle(11, 11, 489, 429);
	fillrectangle(500, 0, 800, 500);
	line(600, 0, 600, 500);
	line(600, 145, 800, 145);
	line(600, 75, 700, 75);
	line(600, 215, 700, 215);
	line(600, 285, 800, 285);
	line(600, 355, 700, 355);
	line(700, 0, 700, 75);
	line(700, 145, 700, 215);
	line(700, 355, 700, 499);

	// 设置参数
	setlinecolor(RGB(125, 125, 125));
	setbkcolor(WHITE);
	settextcolor(BLACK);
	settextstyle(25, 9, _T("Consolas"));
	setlinestyle(PS_SOLID, 2);

	// 根据按钮数量，按钮类型参数绘制
	for (i = 0; i < num_button; i++)
	{
		// 圆按钮
		if (boxm[i].mod == 0)
		{
			setfillcolor(boxm[i].color);
			// 圈圈
			fillcircle(boxm[i].posx1, boxm[i].posy1, boxm[i].r);
		}
		// 矩形按钮
		else if (boxm[i].mod == 1)
		{
			setfillcolor(WHITE);
			// 边框
			fillrectangle(boxm[i].posx1, boxm[i].posy1, boxm[i].posx2, boxm[i].posy2);
			// 文字
			outtextxy(boxm[i].posx1 + (boxm[i].posx2 - boxm[i].posx1) / 2 - textwidth(boxm[i].text) / 2, boxm[i].posy1 + 6, boxm[i].text);
		}
		// 文本
		else if (boxm[i].mod == 2)
		{
			setlinecolor(WHITE);
			setfillcolor(WHITE);
			// 边框
			fillrectangle(boxm[i].posx1, boxm[i].posy1, boxm[i].posx2, boxm[i].posy2);
			// 文字
			outtextxy(boxm[i].posx1 + (boxm[i].posx2 - boxm[i].posx1) / 2 - textwidth(boxm[i].text) / 2, boxm[i].posy1 + 6, boxm[i].text);
			setlinecolor(RGB(125, 125, 125));
		}
	}

	// 小球绘制
	draw_box();

	// 数字绘制
	setbkcolor(WHITE);
	settextcolor(BLACK);
	for (i = 0; i < 10; i++)
	{
		_stprintf(s, _T("%0.1d"), i * 10);
		outtextxy(boxm[i].posx1 + 22, boxm[i].posy1 - 15, s);
		outtextxy(boxm[i].posx1 + 42, boxm[i].posy1 - 15, _T("~"));
		_stprintf(s, _T("%0.1d"), i * 10 + 9);
		outtextxy(boxm[i].posx1 + 52, boxm[i].posy1 - 15, s);
	}

	// 参数绘制
	i = 24; j = 30;
	if (mouse_or_not == 0) { outtextxy(boxm[20].posx1 + 30, boxm[20].posy1 + j, _T("否")); }
	else if (mouse_or_not == 1) { outtextxy(boxm[20].posx1 + 30, boxm[20].posy1 + j, _T("是")); }
	_stprintf(s, _T("%0.1f"), gravitational_constant);	outtextxy(boxm[19].posx1 + i, boxm[19].posy1 + j, s);
	_stprintf(s, _T("%0.1f"), ease_distance);				outtextxy(boxm[21].posx1 + i, boxm[21].posy1 + j, s);
	_stprintf(s, _T("%0.2f"), differential_time);			outtextxy(boxm[23].posx1 + i, boxm[23].posy1 + j, s);
	_stprintf(s, _T("%0.1f"), mouse_quality);				outtextxy(boxm[22].posx1 + i, boxm[22].posy1 + j, s);

	// 动画未演示状态，绘制选定小球参数
	if (flash_or_not == 0)
	{
		draw_parameter();
	}

	FlushBatchDraw();
}

// 小球绘制函数
void Gary::draw_box()
{
	int i;
	// 框框范围绘制
	setfillcolor(WHITE);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	fillrectangle(11, 11, 489, 429);
	// 小球绘制
	for (i = 0; i < num_box; i++)
	{
		if (box[i].numx > 11 && box[i].numx < 489 && box[i].numy>11 && box[i].numy < 429)
		{
			setfillcolor(box[i].color);
			solidcircle(box[i].numx, box[i].numy, 10);
		}
	}
	FlushBatchDraw();
}

// 鼠标绘制函数
void Gary::draw_mouse()
{
	setfillcolor(box[num_box - 1].color);
	solidcircle(box[num_box - 1].numx, box[num_box - 1].numy, 10);
	FlushBatchDraw();
}

// 参数绘制函数，仅在停止状态绘制
void Gary::draw_parameter()
{
	int i, j;
	TCHAR s[5];
	// 选定目标小球绘制
	setlinecolor(LIGHTRED);
	setfillcolor(box[flag_box].color);
	fillcircle(box[flag_box].numx, box[flag_box].numy, 10);
	// 参数绘制
	i = 24; j = 30;
	_stprintf(s, _T("%0.1d"), flag_box);					outtextxy(boxm[10].posx1 + i, boxm[10].posy1 + j, s);
	_stprintf(s, _T("%0.1f"), box[flag_box].numx);		outtextxy(boxm[11].posx1 + i, boxm[11].posy1 + j, s);
	_stprintf(s, _T("%0.1f"), box[flag_box].numy);		outtextxy(boxm[13].posx1 + i, boxm[13].posy1 + j, s);
	_stprintf(s, _T("%0.1f"), box[flag_box].vx);			outtextxy(boxm[15].posx1 + i, boxm[15].posy1 + j, s);
	_stprintf(s, _T("%0.1f"), box[flag_box].vy);			outtextxy(boxm[17].posx1 + i, boxm[17].posy1 + j, s);
	_stprintf(s, _T("%0.1f"), box[flag_box].m);			outtextxy(boxm[14].posx1 + i, boxm[14].posy1 + j, s);
}

// 小球生成函数
void Gary::creact_box()
{
	double j, k;
	// 位置随机
	k = rand() % (2 * num_box);
	j = rand() % 15;
	box[num_box].numx = 250 + 100 * sin((k / double(num_box) + j / 180.0) * pi);
	box[num_box].numy = 220 + 100 * cos((k / double(num_box) + j / 180.0) * pi);
	// 质量，颜色，速度初始化
	box[num_box].color = boxm[0].color;
	box[num_box].m = 2; box[num_box].vx = 0.0; box[num_box].vy = 0.0;
	num_box++;
}

// 参数更新函数
void Gary::refresh_parameter()
{
	int i, j;
	double G, S, dt;
	G = gravitational_constant;		// 引力常数
	S = ease_distance;				// 缓和距离
	dt = differential_time;			// 微分时间
	// 参数更新
	for (i = 0; i < num_box; i++)
	{
		// 引力初始化
		box[i].fx = 0;
		box[i].fy = 0;
		// 引力计算
		for (j = 0; j < num_box; j++)
		{
			if (box[j].numx > 11 && box[j].numx < 489 && box[j].numy>11 && box[j].numy < 429)
			{
				box[i].fx += G * box[i].m * box[j].m / ((box[i].numx - box[j].numx) * (box[i].numx - box[j].numx) + (box[i].numy - box[j].numy) * (box[i].numy - box[j].numy) + S) * ((box[j].numx - box[i].numx) / sqrt((box[i].numx - box[j].numx) * (box[i].numx - box[j].numx) + (box[i].numy - box[j].numy) * (box[i].numy - box[j].numy) + S));
				box[i].fy += G * box[i].m * box[j].m / ((box[i].numx - box[j].numx) * (box[i].numx - box[j].numx) + (box[i].numy - box[j].numy) * (box[i].numy - box[j].numy) + S) * ((box[j].numy - box[i].numy) / sqrt((box[i].numx - box[j].numx) * (box[i].numx - box[j].numx) + (box[i].numy - box[j].numy) * (box[i].numy - box[j].numy) + S));
			}
		}
		// 通过引力算加速度，速度，更新坐标
		box[i].ax = box[i].fx / box[i].m;
		box[i].ay = box[i].fy / box[i].m;
		box[i].vx = box[i].vx + box[i].ax * dt;
		box[i].vy = box[i].vy + box[i].ay * dt;
		box[i].numx = box[i].numx + box[i].vx * dt;
		box[i].numy = box[i].numy + box[i].vy * dt;
		// 触壁反弹
		if (box[i].numx <= 30 || box[i].numx >= 470)
		{
			box[i].vx = -box[i].vx;
		}
		if (box[i].numy <= 30 || box[i].numy >= 410)
		{
			box[i].vy = -box[i].vy;
		}
	}
}

// 调色盘绘制函数
void Gary::draw_palette(int a)
{
	int D = 50;			// 间隔
	int R = 10;			// 小圆半径
	double size = 10;	// 尺寸
	int posx, posy;
	int i, j, k;

	// 清屏
	setfillcolor(WHITE);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	fillrectangle(0, 0, 500, 500);
	FlushBatchDraw();

	// 三维绘制
	for (i = 0; i <= 255; i = i + D)
	{
		for (j = 0; j <= 255; j = j + D)
		{
			for (k = 0; k <= 255; k = k + D)
			{
				posy = 250 - i / D * size * 2.0 + j / D * size * 1.0 + k / D * size * 1.0;
				posx = 250 + j / D * size * 1.8 - k / D * size * 1.8;
				setfillcolor(RGB(i, j, k));
				solidcircle(posx, posy, R);
			}
		}
	}

	FlushBatchDraw();

	// 鼠标定义
	ExMessage m;

	int exit_palette = 0;

	while (exit_palette == 0)
	{
		if (peekmessage(&m, EM_MOUSE | EM_KEY))
		{
			// 左键单击判断
			if (m.message == WM_LBUTTONDOWN)
			{
				// 按钮颜色更替
				boxm[a].color = getpixel(m.x, m.y);
				exit_palette = 1;
			}
		}
	}
	// 小球颜色更替
	for (i = 0; i < num_box; i++)
	{
		if (int(box[i].m / 10) == a)
		{
			box[i].color = boxm[a].color;
		}
	}
}

// 初始化函数
void Gary::initialization()
{
	int i;
	// 按钮的初始化
	num_button = 30;
	// 圆形颜色按钮
	boxm[0].posx1 = 525; boxm[0].posy1 = 25;	boxm[0].mod = 0;	boxm[0].r = 20; boxm[0].color = RGB(165, 207, 229);
	boxm[1].posx1 = 525; boxm[1].posy1 = 75;	boxm[1].mod = 0;	boxm[1].r = 20; boxm[1].color = RGB(30, 120, 180);
	boxm[2].posx1 = 525; boxm[2].posy1 = 125;	boxm[2].mod = 0;	boxm[2].r = 20; boxm[2].color = RGB(180, 220, 140);
	boxm[3].posx1 = 525; boxm[3].posy1 = 175;	boxm[3].mod = 0;	boxm[3].r = 20; boxm[3].color = RGB(50, 160, 70);
	boxm[4].posx1 = 525; boxm[4].posy1 = 225;	boxm[4].mod = 0;	boxm[4].r = 20; boxm[4].color = RGB(250, 150, 150);
	boxm[5].posx1 = 525; boxm[5].posy1 = 275;	boxm[5].mod = 0;	boxm[5].r = 20; boxm[5].color = RGB(230, 30, 40);
	boxm[6].posx1 = 525; boxm[6].posy1 = 325;	boxm[6].mod = 0;	boxm[6].r = 20; boxm[6].color = RGB(250, 190, 110);
	boxm[7].posx1 = 525; boxm[7].posy1 = 375;	boxm[7].mod = 0;	boxm[7].r = 20; boxm[7].color = RGB(250, 130, 30);
	boxm[8].posx1 = 525; boxm[8].posy1 = 425;	boxm[8].mod = 0;	boxm[8].r = 20; boxm[8].color = RGB(200, 180, 220);
	boxm[9].posx1 = 525; boxm[9].posy1 = 475;	boxm[9].mod = 0;	boxm[9].r = 20; boxm[9].color = RGB(100, 60, 150);

	// 矩形按钮
	for (i = 0; i < 14; i++)
	{
		boxm[i + 10].posx1 = 610 + i % 2 * 100;
		boxm[i + 10].posy1 = 10 + i / 2 * 70;
		boxm[i + 10].posx2 = 690 + i % 2 * 100;
		boxm[i + 10].posy2 = 70 + i / 2 * 70;
		boxm[i + 10].mod = 1;
	}

	boxm[10].text = _T("小球编号");
	boxm[11].text = _T("水平坐标");
	boxm[12].text = _T("初始位置:");	boxm[12].mod = 2;
	boxm[13].text = _T("垂直坐标");
	boxm[14].text = _T("小球质量");
	boxm[15].text = _T("水平速度");
	boxm[16].text = _T("初始速度:");	boxm[16].mod = 2;
	boxm[17].text = _T("垂直速度");
	boxm[18].text = _T("高级设置:");	boxm[18].mod = 2;
	boxm[19].text = _T("引力常数");
	boxm[20].text = _T("鼠标跟随");
	boxm[21].text = _T("缓和距离");
	boxm[22].text = _T("鼠标质量");
	boxm[23].text = _T("微分时间");

	for (i = 0; i < 6; i++)
	{
		boxm[i + 24].posx1 = 10 + 82 * i;
		boxm[i + 24].posy1 = 440;
		boxm[i + 24].posx2 = 80 + 82 * i;
		boxm[i + 24].posy2 = 490;
		boxm[i + 24].mod = 1;
	}

	boxm[24].text = _T("增加");
	boxm[25].text = _T("减少");
	boxm[26].text = _T("刷新");
	boxm[27].text = _T("开始");
	boxm[28].text = _T("停止");
	boxm[29].text = _T("退出");

	num_box = 3;
	// 小球初始化
	box[0].numx = 250 + 100 * sin(120.0 / 180.0 * pi);
	box[0].numy = 220 + 100 * cos(120.0 / 180.0 * pi);
	box[0].m = 2; box[0].vx = 0.10; box[0].vy = 0;
	box[0].color = boxm[0].color;

	box[1].numx = 250 + 100 * sin(0);
	box[1].numy = 220 + 100 * cos(0);
	box[1].m = 2; box[1].vx = 0; box[1].vy = 0.10;
	box[1].color = boxm[0].color;

	box[2].numx = 250 + 100 * sin(240.0 / 180.0 * pi);
	box[2].numy = 220 + 100 * cos(240.0 / 180.0 * pi);
	box[2].m = 2; box[2].vx = 0.20; box[2].vy = 0;
	box[2].color = boxm[0].color;

	// 常量初始化
	flag_box = 0;
	mouse_or_not = 0;				// 鼠标演示未开启
	flash_or_not = 0;				// 动画演示未开启

	gravitational_constant = 50;	// 引力常数
	ease_distance = 100;			// 缓和距离
	differential_time = 0.05;		// 微分时间
	mouse_quality = 20;				// 鼠标质量

	// 绘制
	draw_scene();
}

// 窗口主视角函数，获取用户操作
void Gary::move()
{
	// 鼠标定义
	ExMessage m;
	TCHAR ss[10];
	int i, k;
	float j;
	// 控制参数置零
	exit_move = 0;

	while (exit_move == 0)
	{
		if (peekmessage(&m, EM_MOUSE | EM_KEY))
		{
			// 左键单击判断
			if (m.message == WM_LBUTTONDOWN)
			{
				// 动画未演示时，点击小球将切换选定的小球，点击绘制范围将移动选定的小球
				if (flash_or_not == 0)
				{
					// 判断是否点击了小球
					k = 0;
					for (i = 0; i < num_box; i++)
					{
						// 小球
						if ((m.x - box[i].numx) * (m.x - box[i].numx) + (m.y - box[i].numy) * (m.y - box[i].numy) < 101)
						{
							flag_box = i;
							k = 1;
							break;
						}
					}
					// 判断是否点击绘制范围内
					if (m.x > 11 && m.x < 489 && m.y>11 && m.y < 429 && k == 0)
					{
						box[flag_box].numx = m.x;
						box[flag_box].numy = m.y;
					}
				}

				// 判断是否点击了按钮
				for (i = 0; i < num_button; i++)
				{
					// 矩形按钮
					if (boxm[i].mod == 1 && m.x > boxm[i].posx1 && m.y > boxm[i].posy1 && m.x < boxm[i].posx2 && m.y < boxm[i].posy2)
					{
						break;
					}
					// 圆按钮
					else if (boxm[i].mod == 0 && (m.x - boxm[i].posx1) * (m.x - boxm[i].posx1) + (m.y - boxm[i].posy1) * (m.y - boxm[i].posy1) < boxm[i].r * boxm[i].r)
					{
						break;
					}
				}

				// 动画演示时，只能点击停止按钮
				if (flash_or_not == 1)
				{
					// 点击矩形按钮
					switch (i)
					{
						// 停止按钮：flash_or_not
					case 28:
					{
						// 动画控制参数置零
						flash_or_not = 0;
						// 选择小球编号初始化
						flag_box = 0;
						// 鼠标跟随打开时
						// 在动画关闭时，需要将最后一个小球删去
						if (mouse_or_not == 1)
						{
							num_box--;
						}

						break;
					}
					default:break;
					}
				}
				// 动画未演示时，可以点击其他按钮
				else if (flash_or_not == 0)
				{
					// 点击圆形按钮
					if (i >= 0 && i < 10)
					{
						draw_palette(i);
					}
					// 点击矩形按钮
					switch (i)
					{
						// 小球编号按钮：flag_box
					case 10:
					{
						InputBox(ss, 10, _T("输入小球编号(0 ~ 小球总数)"));
						_stscanf(ss, _T("%d"), &i);
						if (i >= 0 && i < num_box) { flag_box = i; }
						else { MessageBox(hOut, _T("输入错误，不在范围内"), _T("来自小豆子的提醒"), MB_OK); }
						break;
					}
					// 水平坐标按钮：box[flag_box].numx
					case 11:
					{
						InputBox(ss, 10, _T("输入水平坐标(12 ~ 488)"));
						_stscanf(ss, _T("%d"), &i);
						if (i >= 12 && i <= 488) { box[flag_box].numx = i; }
						else { MessageBox(hOut, _T("输入错误，不在范围内"), _T("来自小豆子的提醒"), MB_OK); }
						break;
					}

					// 垂直坐标按钮：box[flag_box].numy
					case 13:
					{
						InputBox(ss, 10, _T("输入垂直坐标(12 ~ 428)"));
						_stscanf(ss, _T("%d"), &i);
						if (i >= 12 && i <= 428) { box[flag_box].numy = i; }
						else { MessageBox(hOut, _T("输入错误，不在范围内"), _T("来自小豆子的提醒"), MB_OK); }
						break;
					}

					// 小球质量按钮：box[flag_box].m
					case 14:
					{
						InputBox(ss, 10, _T("输入小球质量(1 ~ 99)"));
						_stscanf(ss, _T("%d"), &i);
						if (i >= 1 && i <= 99) { box[flag_box].m = i; }
						else { MessageBox(hOut, _T("输入错误，不在范围内"), _T("来自小豆子的提醒"), MB_OK); }
						// 颜色随之改变
						box[flag_box].color = boxm[int(box[flag_box].m / 10)].color;
						break;
					}
					// 水平速度按钮：box[flag_box].vx
					case 15:
					{
						InputBox(ss, 10, _T("输入水平速度(-9 ~ 9)"));
						_stscanf(ss, _T("%f"), &j);
						if (j >= -9 && j <= 9) { box[flag_box].vx = j; }
						else { MessageBox(hOut, _T("输入错误，不在范围内"), _T("来自小豆子的提醒"), MB_OK); }
						break;
					}
					// 垂直速度按钮：box[flag_box].vy
					case 17:
					{
						InputBox(ss, 10, _T("输入水平速度(-9 ~ 9)"));
						_stscanf(ss, _T("%f"), &j);
						if (j >= -9 && j <= 9) { box[flag_box].vy = j; }
						else { MessageBox(hOut, _T("输入错误，不在范围内"), _T("来自小豆子的提醒"), MB_OK); }
						break;
					}
					// 引力常数按钮：gravitational_constant
					case 19:
					{
						InputBox(ss, 10, _T("输入引力常数(10 ~ 100)"));
						_stscanf(ss, _T("%f"), &j);
						if (j >= 10 && j <= 100) { gravitational_constant = j; }
						else { MessageBox(hOut, _T("输入错误，不在范围内"), _T("来自小豆子的提醒"), MB_OK); }
						break;
					}
					// 鼠标演示按钮：mouse_or_not
					case 20:
					{
						mouse_or_not = mouse_or_not == 0 ? 1 : 0;
						break;
					}
					// 缓和距离按钮：ease_distance
					case 21:
					{
						InputBox(ss, 10, _T("输入缓和距离(20 ~ 100)"));
						_stscanf(ss, _T("%f"), &j);
						if (j >= 20 && j <= 100) { ease_distance = j; }
						else { MessageBox(hOut, _T("输入错误，不在范围内"), _T("来自小豆子的提醒"), MB_OK); }
						break;
					}
					// 鼠标质量按钮：mouse_quality
					case 22:
					{
						InputBox(ss, 10, _T("输入鼠标质量(0 ~ 99)"));
						_stscanf(ss, _T("%f"), &j);
						if (j >= 0 && j <= 99) { mouse_quality = j; }
						else { MessageBox(hOut, _T("输入错误，不在范围内"), _T("来自小豆子的提醒"), MB_OK); }
						break;
					}
					// 微分时间按钮：differential_time
					case 23:
					{
						InputBox(ss, 10, _T("输入微分时间(0.01 ~ 0.1)"));
						_stscanf(ss, _T("%f"), &j);
						if (j >= 0.01 && j <= 0.1) { differential_time = j; }
						else { MessageBox(hOut, _T("输入错误，不在范围内"), _T("来自小豆子的提醒"), MB_OK); }
						break;
					}
					// 增加按钮
					case 24:
					{
						// 不超过预制情况下，可增加
						if (num_box < 498)
						{
							creact_box();
							draw_box();
						}
						else
						{
							MessageBox(hOut, "已达最大值", "来自小豆子的提醒", MB_OK);
						}
						break;
					}
					// 减少按钮
					case 25:
					{
						// 不小于两个的情况下，可减少
						if (num_box > 2)
						{
							num_box--;
							draw_box();
						}
						else
						{
							MessageBox(hOut, "已达最小值", "来自小豆子的提醒", MB_OK);
						}
						break;
					}
					// 刷新按钮
					case 26:
					{
						// 主循控制参数置一，结束主循
						exit_move = 1;
						break;
					}
					// 开始按钮：flash_or_not
					case 27:
					{
						// 动画控制参数
						flash_or_not = 1;
						// 根据鼠标跟随控制参数给最后一个小球赋值
						// 开启状态
						if (mouse_or_not == 1)
						{
							box[num_box].numx = m.x;
							box[num_box].numy = m.y;
							box[num_box].m = mouse_quality;
							box[num_box].color = boxm[int(mouse_quality / 10)].color;
							box[num_box].vx = 0.0; box[num_box].vy = 0.0;
							num_box++;
						}
						break;
					}
					// 退出按钮
					case 29:
					{
						// 主循控制参数置一，结束主循
						exit_move = 1;
						exit_carry = 1;
						break;
					}
					default:break;
					}
				}
				// 绘制
				draw_scene();
			}
		}

		// 动画演示开启
		if (flash_or_not == 1)
		{
			// 参数更新函数
			refresh_parameter();
			// 小球绘制函数
			draw_box();
			// 鼠标跟随开启，且鼠标处于绘制区
			if (mouse_or_not == 1 && m.x > 21 && m.x < 479 && m.y>21 && m.y < 419)
			{
				box[num_box - 1].numx = m.x;
				box[num_box - 1].numy = m.y;
				draw_mouse();
			}
			// 鼠标跟随开启，且鼠标处于非绘制区
			else if (mouse_or_not == 1)
			{
				box[num_box - 1].numx = 800;
				box[num_box - 1].numy = 800;
			}
		}
	}
}

// 主进程
void Gary::carry()
{
	// 窗口定义
	hOut = initgraph(801, 501);
	SetWindowText(hOut, _T("万有引力"));
	// 进程控制参数
	exit_carry = 0;
	// 随机种子初始化
	srand((unsigned)time(NULL));
	BeginBatchDraw();
	while (exit_carry == 0)
	{
		initialization();
		move();
		// 刷新，重置，返回按钮，进程控制参数置零
		// 退出按钮，进程控制参数置一
	}
	EndBatchDraw();
	closegraph();
}

// 主函数
int main(void)
{
	// 创建类对象
	Gary G;
	// 进入类对象主循函数
	G.carry();
	return 0;
}
