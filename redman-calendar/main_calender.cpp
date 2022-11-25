/************************************************************
* 本程序名叫万年历:										*
* 顾名思义可以查询很多年份的日历							*
* 按键介绍:												*
* q 年份加 1, a 年份减 1									*
* w 年份加 10, s 年份减 10									*
* e 年份加 100, d 年份减 100								*
* r 年份加 1000, f 年份减 1000								*
* t 月份加 1, g 月份减 1									*
* 其他按键均为错误或者年份, 月份不能再减或者加了, 都会报警	*
*															*
* 编译环境：VC6 + EasyX									*
* 最后修改：2012-9-19										*
************************************************************/

#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <time.h>

int x1[13] = { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };						// 闰年的每月天数
int x2[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };						// 平年的每月天数

char *Week[] = { "星期天", "星期一", "星期二", "星期三", "星期四", "星期五", "星期六" };	// 定义星期
char num[3];																			// 定义 num 字符串
char xy[30];																			// 定义 xy 字符串,

struct Time										// 定义了一个结构体
{
	int year, month;							// 年月
	int yearFlag, monthFlag;					// 用来标记年月是否改变
};


// 初始化
void Init()
{
	// 初始化绘图窗口
	initgraph(640, 640);
	setbkcolor(0x0055ff);
	cleardevice();
}

// 绘制星期
void DrawWeek()
{
	char str[7];
	int x1 = 0;

	settextstyle(18, 0, "宋体");
	for (int i = 0; i < 7; i++)
	{
		sprintf(str, "%s", Week[i]);
		outtextxy(120 + x1, 100, str);
		x1 += 60;
	}
}

// 计算现在的年月
void CalDate(Time& tm, char x)
{
	switch (x)
	{
	case 'q':	tm.year++;				break;
	case 'w':	tm.year += 10;			break;
	case 'e':	tm.year += 100;			break;
	case 'r':	tm.year += 1000;		break;
	case 't':	if (tm.month < 12)		tm.month++;			break;
	case 'a':	if (tm.year > 0)		tm.year--;			break;
	case 's':	if (tm.year >= 10)		tm.year -= 10;		break;
	case 'd':	if (tm.year >= 100)		tm.year -= 100;		break;
	case 'f':	if (tm.year >= 1000)	tm.year -= 1000;	break;
	case 'g':	if (tm.month > 1)		tm.month--;			break;
	}
}

// 判断年份和月份是否更改
bool DateFlag(int y1, int y2, int m1, int m2)
{
	return (y1 != y2 || m1 != m2);
}

// 判断是闰年还是平年
bool CalYear(int year)
{
	return ((year % 4 == 0 && year % 10 != 0) || year % 400 == 0);
}

// 绘制当月日历
void DrawDate(Time &tm)
{
	int y = 0, z = 0;
	int s;

	sprintf(xy, "这是公元 %d 年 %d 月的日历", tm.year, tm.month);
	settextstyle(18, 0, "宋体");
	outtextxy(20, 50, xy);

	s = (5 + (tm.year + 1) + (tm.year - 1) / 4 - (tm.year - 1)
		/ 100 + (tm.year - 1) / 400) % 7;

	if (CalYear(tm.year))                       // 如果当前年份是闰年
	{
		for (int i = 1; i < tm.month; i++)
		{
			s = (x1[i] + s) % 7;
		}

		if (s / 6 != 1)
		{
			y = (s + 1) * 60;
		}

		settextstyle(36, 0, "Arial");
		for (int i = 1; i <= x1[tm.month]; i++)
		{
			sprintf(num, " %d ", i);
			outtextxy(130 + y, 150 + z, num);
			y += 60;
			if ((i + s) % 7 == 6 && (i + s) >= 6)
			{
				z += 85;
				y = 0;
			}
		}
	}
	else									 // 如果当前年份不是闰年
	{
		for (int i = 1; i < tm.month; i++)
		{
			s = (x2[i] + s) % 7;
		}

		if (s / 6 != 1)
		{
			y = (s + 1) * 60;
		}

		settextstyle(36, 0, "Arial");
		for (int i = 1; i <= x2[tm.month]; i++)
		{
			sprintf(num, "%2d", i);
			outtextxy(130 + y, 150 + z, num);
			y += 60;
			if ((i + s) % 7 == 6)
			{
				z += 85;
				y = 0;
			}
		}
	}
}


// 主函数
int main()
{
	char add;
	tm *t;										// 在 time.h 中有定义为一个结构体，用法见 MSDN
	time_t Clock;								// 在 time.h 中有定义为一个结构体，用法见 MSDN
	Time tm;									// 结构体 tm

	// 初始化
	Init();

	// 获取结构体 Clock 的参数
	time(&Clock);

	// 获取时间
	t = localtime(&Clock);

	tm.year = t->tm_year + 1900;				// 当前系统时间所处年份, 至于为什么加 1900, 见 MSDN
	tm.month = t->tm_mon + 1;					// 获取系统时间所在月份, 至于为什么加 1, 见 MSDN
	tm.yearFlag = tm.year;						// 标记当前年份份
	tm.monthFlag = tm.month;					// 标记当前月份

	// 绘制星期
	DrawWeek();

	// 绘制当月的日历
	DrawDate(tm);

	// 主循环
	while (1)
	{
		// 从键盘获取按键
		add = getch();

		// 计算现在的年月
		CalDate(tm, add);

		// 判断年月是否更改, 改则进入 if 语句
		if (DateFlag(tm.year, tm.yearFlag, tm.month, tm.monthFlag))
		{
			// 清除屏幕
			cleardevice();

			// 从新绘制星期
			DrawWeek();

			// 从新绘制当月日历
			DrawDate(tm);

			tm.yearFlag = tm.year;				// 更改新标记年份
			tm.monthFlag = tm.month;			// 更改新标记月份
		}
	}

	// 返回
	return 0;
}