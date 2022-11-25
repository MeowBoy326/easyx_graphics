////////////////////////////////////////////
// 程序名称：3 辆行驶的小车
// 编译环境：Visual C++ 6.0，EasyX_20120603(beta) 
// 程序编写：E_SHARE <501748772@qq.com>
// 编写时间：2012-6-26
////////////////////////////////////////////
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>

// 声明需要使用的函数
void carstart(int x, int y, int z);
void drawbus();
void init();

// 定义全局变量
IMAGE img;


////////////////////////////////////////////
void main()
{
	init();
	int x = 0, y = 0, z = 0;
	BeginBatchDraw();

	while (!kbhit())
	{
		x += 2;
		y++;
		z += 3;
		if (x > 600)	x = -200;
		if (y > 600)	y = -200;
		if (z > 600)	z = -200;

		carstart(x, y, z);
		FlushBatchDraw();
		Sleep(5);
	}

	EndBatchDraw();
	closegraph();
}


////////////////////////////////////////////
// 初始化函数，初始化窗口大小，获取所画图片
void init()
{
	// 初始化窗口大小
	initgraph(600, 600);

	outtextxy(70, 250, "大家好，新手来报到，希望大家多多指教");
	outtextxy(70, 270, "下面你们会看到我程序的效果，程序很简单");
	outtextxy(70, 290, "希望以后再跟大家的交流中学到更多，希望自己以后能编出更好的程序");
	outtextxy(70, 320, "请按任意键进观看程序执行效果");

	// 等待按键按下
	getch();

	cleardevice();						// 清除上面的文字进入运行效果画面
	drawbus();							// 调用绘图函数，绘制 BUS
	getimage(&img, 80, 40, 180, 90);	// 获取 BUS 图片位置，保存在 img 变量中
}


//////////////////////////////////////////////////////////////
// 车辆行驶程序，通过 putimge 函数，改变移动的像素来达到图片移动
void carstart(int x, int y, int z)
{
	cleardevice();
	putimage(x, 40, &img);
	setlinestyle(PS_SOLID,  10);   //设置画线的大小
	line(0, 135, 600, 135);
	putimage(y, 220, &img);
	line(0, 315, 600, 315);
	putimage(z, 380, &img);
	line(0, 475, 600, 475);
}


//////////////////////////////////////////////////////////////
// 绘制 BUS 函数，通过画一些线条，组合它们的位置，组合成一辆小车
void drawbus()
{
	setcolor(RED);
	setfillstyle(BLUE);

	fillcircle(120, 120, 10); 		// 画车的轮胎
	fillcircle(200, 120, 10); 		// 画车的轮胎
	line(80, 120, 110, 120);		// 画车的底部车板
	line(80, 40, 80, 120); 		// 画车的四周车板
	line(130, 120, 190, 120);		// 画车的底部车板
	line(210, 120, 250, 120);		// 画车的底部车板
	line(250, 40, 250, 120); 		// 画车的四周车板
	line(80, 40, 250, 40);		// 画车的顶部车板

	// 画车窗
	for (int x = 90, y = 100; x < 190 && y < 190; x += 15, y += 15)
	{
		rectangle(x, 60, y, 70);
	}

	// 画车门
	rectangle(220, 60, 240, 120);
	line(230, 60, 230, 120);
	circle(230, 90, 5);
}