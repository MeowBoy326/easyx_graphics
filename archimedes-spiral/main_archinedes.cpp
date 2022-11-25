////////////////////////////////////////
// 程序：阿基米德螺旋线
// 作者：Gary
// 编译环境：Visual C++ 2010，EasyX_20211109
// 编写日期：2021-1-24

# include <math.h>
# include <graphics.h>
# include <string>

static double pi = acos(-1.0);			// 圆周率 π
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

// 定义一个结构体，有理数
struct Node2
{
	int outnum;							// 每一位的小数
	int nestnum;						// 每一位的余数
};

// 定义一个类
class Gary
{
public:
	void carry();				// 主进程
	void initialization();		// 初始化
	void draw_scene();			// 绘制界面函数
	void move();				// 窗口主视角

	// 计算函数
	void calculation_pi();		// π的计算
	void calculation_e();		// e 的计算
	void calculation_num();	// 有理数的计算
	// 绘制函数
	void draw_helical_line();	// 绘制螺旋线函数
	void draw_walking_line();	// 绘制行走的直线函数
	void draw_palette(int a);	// 调色盘绘制函数

	int num_button;				// 按钮数量参数
	int exit_carry;				// 主循函数控制参数
	int exit_move;				// 开始界面控制参数

	int box_pi[10000];			// π存放
	int box_e[10000];			// e 存放
	Node2 box_num[10000];		// 有理数存放
	int A, B;					// 有理数的分子，分母
	int flag_start, flag_end;	// 有理数第一个循环节开始和结束位置

	int draw_mod;				// 绘制模式参数，两种：螺旋线模式和行走线模式
	int num_mod;				// 数字模式参数，三种：无理数 π，无理数 e 和有理数

	// 螺旋线模式
	double initial_position;	// 初始位置
	double linear_velocity;		// 线速度
	double angular_velocity;	// 角速度
	double d;					// 螺旋线上小圆半径

	// 行走线模式
	double step_size;			// 步长

	Node1 boxm[30];				// 按钮，预制 30 个	
};

// π的计算函数，默认计算 1000 位
void Gary::calculation_pi()
{
	int j, k, h, g, m;
	// 临时存放
	int box[10000];
	// 计算位数
	int t = 1000;

	// π 的泰勒公式展开
	// pi/2 = 1+1/3+1/3 * 2/5 + 1/3 * 2/5 * 3/7 + 1/3 * 2/5 * 3/7 *4/9+...

	// 前两项和 2.666...
	box_pi[0] = 2;
	m = 1;
	while (m <= t)
	{
		box_pi[m] = 6;
		m++;
	}

	// 初始化 1/3
	box[0] = 0;
	m = 1;
	while (m <= t)
	{
		box[m] = 6;
		m++;
	}
	// 初始是第二项
	j = 2;
	k = 1;
	while (k != 0)
	{
		// 第 j 次运算，乘 j/(2j+1)
		// 先乘，初始化进位符
		// 从低到高，超十进位
		for (h = t; h >= 0; h--)
		{
			// 每位都乘 j
			box[h] *= j;
		}
		// 后除，初始化余数
		g = 0;
		// 从高到低，取余数乘十加到后一位
		for (h = 0; h <= t; h++)
		{
			// 加上一位的余数乘十
			box[h] += g * 10;
			// 取这一位的余数
			g = box[h] % (2 * j + 1);
			// 每位都除以(2j+1)
			box[h] /= (2 * j + 1);
		}

		// 每一项都是小于一的，所以每一位都是小于十的，进位符最大是一
		// 从需要的位数开始，向前加数
		g = 0;
		k = 0;
		for (h = t; h >= 0; h--)
		{
			// 从低到高，加每一项同位的数，加进位符
			box_pi[h] += box[h];
			box_pi[h] += g;
			// 进位符判断，需要进位则减十
			g = 0;
			if (box_pi[h] >= 10) { box_pi[h] -= 10; g = 1; }
			// 退出判断
			// 某次运算时，需要位数前全是零，则表示余项足够小，已经影响不到需要位数之前的位数了
			if (box[h] != 0) { k++; }
		}

		// 退出判断，不退出则进行下一项
		if (k != 0)
		{
			j++;
		}

	}

	// 无理数没有循坏节
	flag_start = 0; flag_end = t - 1;
	// 最后一次运算，已经影响不到需要位数之前的位数
}

// e 的计算函数，默认计算 1000 位
void Gary::calculation_e()
{
	int j, k, h, g, m;
	// 临时存放
	int box[10000];
	// 计算位数
	int t = 1000;

	// e 的泰勒公式展开
	// e=1+1/2!+1/3!+1/4!+...

	// 前四项和 1+1/2!+1/3!=2.666...
	box_e[0] = 2;
	m = 1;
	while (m <= t)
	{
		box_e[m] = 6;
		m++;
	}

	// 初始化 1/3!
	box[0] = 0;
	box[1] = 1;
	m = 2;
	while (m <= t)
	{
		box[m] = 6;
		m++;
	}

	// 初始是第四项
	k = 1;
	j = 4;
	while (k != 0)
	{
		// 第 j 次运算，乘 1/j
		// 只需要除
		g = 0;
		// 从高到低，取余数乘十加到后一位
		for (h = 0; h <= t; h++)
		{
			// 加上一位的余数乘十
			box[h] += g * 10;
			// 取这一位的余数
			g = box[h] % j;
			// 每位都除以 j
			box[h] /= j;
		}

		// 从需要的位数开始，向前加数
		g = 0;
		k = 0;
		for (h = t; h >= 0; h--)
		{
			// 从低到高，加每一项同位的数，加进位符
			box_e[h] += box[h];
			box_e[h] += g;
			// 进位符判断，需要进位则减十
			g = 0;
			if (box_e[h] >= 10) { box_e[h] -= 10; g = 1; }
			// 退出判断
			// 某次运算时，需要位数前全是零，则表示余项足够小，已经影响不到需要位数之前的位数了
			if (box[h] != 0) { k++; }
		}

		// 退出判断，不退出则进行下一项
		if (k != 0)
		{
			j++;
		}
	}

	// 无理数没有循坏节
	flag_start = 0; flag_end = t - 1;
	// 最后一次运算，已经影响不到需要位数之前的位数
}

// 有理数的计算函数
void Gary::calculation_num()
{
	int a, flag, i, j;
	a = A;
	while (A / B == 0)
	{
		A *= 10;
	}

	// 算循环节，并输出 1000 位
	flag = 0; flag_end = 0;
	j = 0;
	while (j < 1000)
	{
		// 除以的结果
		box_num[j].outnum = A / B;
		// 余数
		box_num[j].nestnum = A % B;
		// 余数乘十
		A = box_num[j].nestnum * 10;
		// 判断循环节是否找到了
		if (flag_end == 0)
		{
			// 余数一致，进入循环，或余数为零，整除，都结束运算
			// 如此已知，分母为 B 时，循环节长度至多为 B - 1
			for (i = 0; i < flag; i++)
			{
				if (box_num[i].nestnum == box_num[flag].nestnum || box_num[i].nestnum == 0)
				{
					// 循环节长度为 flag-i
					flag_start = i;
					flag_end = flag - 1;
					break;
				}
			}
		}
		flag++;
		j++;
	}

	A = a;
}

// 场景绘制函数
void Gary::draw_scene()
{
	TCHAR s[25];
	int i, j;
	// 背景绘制
	setbkcolor(WHITE);
	cleardevice();

	// 线绘制
	if (draw_mod == 0)
	{
		setlinestyle(PS_SOLID, 1);
		draw_helical_line();
	}
	else if (draw_mod == 1)
	{
		setlinestyle(PS_SOLID, 2);
		draw_walking_line();
	}

	// 框框范围绘制
	setfillcolor(WHITE);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	line(0, 0, 500, 0);
	line(0, 0, 0, 500);
	line(0, 500, 500, 500);
	fillrectangle(500, 0, 800, 500);
	line(600, 0, 600, 500);
	line(600, 145, 800, 145);
	line(600, 355, 800, 355);
	line(700, 355, 700, 500);

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
			fillcircle(int(boxm[i].posx1), int(boxm[i].posy1), int(boxm[i].r));
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
	}

	// 数字绘制
	setbkcolor(WHITE);
	settextcolor(BLACK);
	for (i = 0; i < 10; i++)
	{
		_stprintf_s(s, _T("%0.1d"), i);
		outtextxy(boxm[i].posx1 + 40, boxm[i].posy1 - 15, s);
	}

	outtextxy(670, 160, _T("螺旋线"));
	outtextxy(620, 370, _T("行走线"));

	i = 24; j = 30;
	_stprintf_s(s, _T("%0.1d"), A);						outtextxy(boxm[10].posx1 + i, boxm[10].posy1 + j, s);
	_stprintf_s(s, _T("%0.1d"), B);						outtextxy(boxm[11].posx1 + i, boxm[11].posy1 + j, s);
	_stprintf_s(s, _T("%0.1f"), initial_position);		outtextxy(boxm[14].posx1 + i, boxm[14].posy1 + j, s);
	_stprintf_s(s, _T("%0.1f"), linear_velocity);		outtextxy(boxm[15].posx1 + i, boxm[15].posy1 + j, s);
	_stprintf_s(s, _T("%0.1f"), angular_velocity / pi);	outtextxy(boxm[16].posx1 + i, boxm[16].posy1 + j, s);
	_stprintf_s(s, _T("%0.1f"), d);						outtextxy(boxm[17].posx1 + i, boxm[17].posy1 + j, s);
	_stprintf_s(s, _T("%0.1f"), step_size);				outtextxy(boxm[18].posx1 + i, boxm[18].posy1 + j, s);

	FlushBatchDraw();
}

// 绘制螺旋线函数
void Gary::draw_helical_line()
{
	int k;

	double i, posx, posy, r, w;
	i = angular_velocity;
	r = initial_position + linear_velocity * angular_velocity;
	k = 0;
	// r>d 是画到原点，r>i 是画到初始位置点
	while (r > d && r > initial_position && k < 1000)
	{
		// 根据螺旋线半径和线上小圆半径算螺旋线旋转角度，近似直角三角形，sin(w)= w
		// 可见接近原点时会不准确，提高 i 值，让螺旋线不接近原点
		w = d / r;
		// 角度旋转
		angular_velocity = angular_velocity - w;
		// 距离更新
		r = initial_position + linear_velocity * angular_velocity;
		// 坐标更新
		posx = r * cos(angular_velocity);
		posy = r * sin(angular_velocity);
		// 可串小圆绘制
		if (num_mod == 0) { setfillcolor(boxm[box_pi[k]].color);			setlinecolor(boxm[box_pi[k]].color); }
		else if (num_mod == 1) { setfillcolor(boxm[box_e[k]].color);			setlinecolor(boxm[box_e[k]].color); }
		else if (num_mod == 2) { setfillcolor(boxm[box_num[k].outnum].color);	setlinecolor(boxm[box_num[k].outnum].color); }
		fillcircle(int(250 + posx), int(250 + posy), int(d / 2));
		k++;
	}
	angular_velocity = i;
	r = initial_position + linear_velocity * angular_velocity;

	FlushBatchDraw();
}

// 绘制行走的直线函数
void Gary::draw_walking_line()
{
	int i, k, a;
	double w, posx, posy;
	w = 0; posx = 250; posy = 250;

	setlinecolor(BLACK);

	// 数字模式
	if (num_mod == 0) { a = 1; }
	else if (num_mod == 1) { a = 1; }
	else if (num_mod == 2) { a = 20; }

	// 绘制
	for (k = 0; k < a; k++)
	{
		for (i = flag_start; i <= flag_end; i++)
		{
			// 改方向
			if (num_mod == 0) { w = int(w - 90 + 36 * box_pi[i]) % 360; }
			else if (num_mod == 1) { w = int(w - 90 + 36 * box_e[i]) % 360; }
			else if (num_mod == 2) { w = int(w - 90 + 36 * box_num[i].outnum) % 360; }
			// 绘制线
			line(int(posx), int(posy), int(posx + step_size * cos(w * pi / 180.0)), int(posy + step_size * sin(w * pi / 180.0)));
			// 更新坐标
			posx += step_size * cos(w * pi / 180.0);
			posy += step_size * sin(w * pi / 180.0);
			// Sleep(20); FlushBatchDraw();
		}
	}

	FlushBatchDraw();
}

// 调色盘函数
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
				posy = int(250 - i / D * size * 2.0 + j / D * size * 1.0 + k / D * size * 1.0);
				posx = int(250 + j / D * size * 1.8 - k / D * size * 1.8);
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
				boxm[a].color = getpixel(m.x, m.y);
				exit_palette = 1;
			}
		}
	}

	draw_scene();
	FlushBatchDraw();
}

// 初始化函数
void Gary::initialization()
{
	// 按钮的初始化
	num_button = 21;
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
	boxm[10].posx1 = 610; boxm[10].posy1 = 10;	boxm[10].posx2 = 690; boxm[10].posy2 = 70;	boxm[10].mod = 1; boxm[10].text = _T("分子");
	boxm[11].posx1 = 710; boxm[11].posy1 = 10;	boxm[11].posx2 = 790; boxm[11].posy2 = 70;	boxm[11].mod = 1; boxm[11].text = _T("分母");
	boxm[12].posx1 = 610; boxm[12].posy1 = 80;	boxm[12].posx2 = 690; boxm[12].posy2 = 140; boxm[12].mod = 1; boxm[12].text = _T("π");
	boxm[13].posx1 = 710; boxm[13].posy1 = 80;	boxm[13].posx2 = 790; boxm[13].posy2 = 140; boxm[13].mod = 1; boxm[13].text = _T("e");
	boxm[14].posx1 = 610; boxm[14].posy1 = 220; boxm[14].posx2 = 690; boxm[14].posy2 = 280; boxm[14].mod = 1; boxm[14].text = _T("初始位置");
	boxm[15].posx1 = 710; boxm[15].posy1 = 220; boxm[15].posx2 = 790; boxm[15].posy2 = 280; boxm[15].mod = 1; boxm[15].text = _T("线速度");
	boxm[16].posx1 = 610; boxm[16].posy1 = 290; boxm[16].posx2 = 690; boxm[16].posy2 = 350; boxm[16].mod = 1; boxm[16].text = _T("角速度");
	boxm[17].posx1 = 710; boxm[17].posy1 = 290; boxm[17].posx2 = 790; boxm[17].posy2 = 350; boxm[17].mod = 1; boxm[17].text = _T("小圆半径");
	boxm[18].posx1 = 610; boxm[18].posy1 = 430; boxm[18].posx2 = 690; boxm[18].posy2 = 490; boxm[18].mod = 1; boxm[18].text = _T("步长");
	boxm[19].posx1 = 710; boxm[19].posy1 = 430; boxm[19].posx2 = 790; boxm[19].posy2 = 490; boxm[19].mod = 1; boxm[19].text = _T("退出");
	boxm[20].posx1 = 710; boxm[20].posy1 = 360; boxm[20].posx2 = 790; boxm[20].posy2 = 420; boxm[20].mod = 1; boxm[20].text = _T("重置");

	// 第一次先画 π 的螺旋线，各种参数初始化
	num_mod = 0;
	draw_mod = 0;
	A = 1; B = 3;
	calculation_pi();
	initial_position = 0;
	linear_velocity = 1.5;
	angular_velocity = 30 * pi;
	step_size = 50;
	d = 7;

	// 绘制
	draw_scene();
}

// 窗口主视角函数，获取用户操作
void Gary::move()
{
	// 鼠标定义
	ExMessage m;
	TCHAR ss[25];
	int i;
	float j;
	exit_move = 0;

	while (exit_move == 0)
	{
		if (peekmessage(&m, EM_MOUSE | EM_KEY))
		{
			// 左键单击判断
			if (m.message == WM_LBUTTONDOWN)
			{
				// 判断是否点击了按钮
				for (i = 0; i < num_button; i++)
				{
					if (boxm[i].mod == 1 && m.x > boxm[i].posx1 && m.y > boxm[i].posy1 && m.x < boxm[i].posx2 && m.y < boxm[i].posy2)
					{
						break;
					}
					else if (boxm[i].mod == 0 && (m.x - boxm[i].posx1) * (m.x - boxm[i].posx1) + (m.y - boxm[i].posy1) * (m.y - boxm[i].posy1) < boxm[i].r * boxm[i].r)
					{
						break;
					}
				}

				// 点击不同模式范围
				if (m.x > 600 && m.y > 145 && m.x < 800 && m.y < 355) { draw_mod = 0; }
				else if (m.x > 600 && m.y > 355 && m.x < 700 && m.y < 500) { draw_mod = 1; }

				// 点击圆形按钮
				if (i >= 0 && i < 10)
				{
					draw_palette(i);
				}

				// 点击矩形按钮
				switch (i)
				{
					// 设置分子按钮：A
				case 10:
				{
					num_mod = 2;
					InputBox(ss, 10, _T("输入分子(1 ~ 分母)"));
					_stscanf_s(ss, _T("%d"), &i);
					if (i >= 1 && i < B) { A = i; }
					else { MessageBox(hOut, _T("输入错误，不在范围内"), _T("来自小豆子的提醒"), MB_OK); }
					calculation_num();
					break;
				}

				// 设置分母按钮：B
				case 11:
				{
					num_mod = 2;
					InputBox(ss, 10, _T("输入分母(分子 ~ 9999)"));
					_stscanf_s(ss, _T("%d"), &i);
					if (i > A && i <= 9999) { B = i; }
					else { MessageBox(hOut, _T("输入错误，不在范围内"), _T("来自小豆子的提醒"), MB_OK); }
					calculation_num();
					break;
				}

				// π 按钮
				case 12:
				{
					num_mod = 0;
					flag_start = 0;
					flag_end = 999;
					break;
				}

				// e 按钮
				case 13:
				{
					num_mod = 1;
					flag_start = 0;
					flag_end = 999;
					break;
				}

				// 设置初始位置按钮：initial_position
				case 14:
				{
					InputBox(ss, 10, _T("输入初始位置(0 ~ 100)"));
					_stscanf_s(ss, _T("%f"), &j); if (j >= 0 && j <= 100) { initial_position = j; }
					else { MessageBox(hOut, _T("输入错误，不在范围内"), _T("来自小豆子的提醒"), MB_OK); }
					break;
				}

				// 设置线速度按钮：linear_velocity
				case 15:
				{
					InputBox(ss, 10, _T("输入线速度(0 ~ 100)"));
					_stscanf_s(ss, _T("%f"), &j); if (j >= 0 && j <= 100) { linear_velocity = j; }
					else { MessageBox(hOut, _T("输入错误，不在范围内"), _T("来自小豆子的提醒"), MB_OK); }
					break;
				}

				// 设置角速度按钮：angular_velocity
				case 16:
				{
					InputBox(ss, 10, _T("输入角速度(0 ~ 100)"));
					_stscanf_s(ss, _T("%f"), &j); if (j >= 0 && j <= 100) { angular_velocity = j * pi; }
					else { MessageBox(hOut, _T("输入错误，不在范围内"), _T("来自小豆子的提醒"), MB_OK); }
					break;
				}

				// 设置小圆半径按钮：d
				case 17:
				{
					InputBox(ss, 10, _T("输入小圆半径(0 ~ 100)"));
					_stscanf_s(ss, _T("%f"), &j); if (j >= 0 && j <= 100) { d = j; }
					else { MessageBox(hOut, _T("输入错误，不在范围内"), _T("来自小豆子的提醒"), MB_OK); }
					break;
				}

				// 设置步长按钮：step_size
				case 18:
				{
					InputBox(ss, 10, _T("输入步长(0 ~ 300)"));
					_stscanf_s(ss, _T("%f"), &j); if (j >= 0 && j <= 300) { step_size = j; }
					else { MessageBox(hOut, _T("输入错误，不在范围内"), _T("来自小豆子的提醒"), MB_OK); }
					break;
				}

				// 退出按钮
				case 19:
				{
					exit_move = 1;
					exit_carry = 1;
					break;
				}

				// 重置按钮
				case 20:
				{
					exit_move = 1;
					break;
				}

				default:break;
				}

				// 绘制
				draw_scene();

			}
		}
	}
}

// 主进程
void Gary::carry()
{
	// 窗口定义
	hOut = initgraph(801, 501);
	SetWindowText(hOut, _T("阿基米德螺旋线"));
	// 进程控制
	exit_carry = 0;

	calculation_pi();
	calculation_e();

	BeginBatchDraw();
	while (exit_carry == 0)
	{
		initialization();
		move();
	}
	EndBatchDraw();
	closegraph();
}

// 主函数
int main(void)
{
	Gary G;
	G.carry();
	return 0;
}

