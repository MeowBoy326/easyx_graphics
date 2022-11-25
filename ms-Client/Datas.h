#pragma once


/* ----------头文件---------- */
#include <iostream>
#include <easyx.h>
#include <graphics.h>  


/* ----------全局数据---------- */
// 窗口大小
int win_width = 640;
int win_height = 480;

// 鼠标消息
MOUSEMSG msg;

// 程序状态
enum class PState :int { HOME, RUM, END };

// 对战结束码
enum class FinishCode :int { WIN, LOSE, BREAK, ESCAPE };

// 定义信息结构体
struct Info
{
	int code;			// 状态码，1 代表正常进行，2 代表正常结束，3 代表断开
	unsigned int uMsg;	// 鼠标消息 uMsg
	int x;				// 鼠标位置 x
	int y;				// 鼠标位置 y;
};

// 定义格子值
// '0' 表示空白，'1' - '8' 表示方块周围雷数目，值 1 表示雷，值 2 表示被翻开
char MINE = 1;
char CLICKED = 2;

// 图像资源
int imgSize = 16;	// 图像格子大小
IMAGE imgBlank;				// 空白
IMAGE imgUnclicked;			// 未点击的
IMAGE imgMine;				// 雷
IMAGE imgMineClicked;		// 翻开的雷
IMAGE imgNums[8];			// 数字

// 数字颜色
COLORREF TextColor[8] = { RGB(0,0,200),RGB(0,150,0),RGB(255,0,0),RGB(0,0,100),RGB(130,0,0),RGB(0,150,150),RGB(80,50,20),RGB(0,0,0) };

// 初始化图像资源
void initImages()
{
	// 绘制 imgBlank
	imgBlank.Resize(imgSize, imgSize);
	SetWorkingImage(&imgBlank);
	setbkcolor(LIGHTGRAY);
	cleardevice();
	setlinecolor(DARKGRAY);
	line(imgSize - 1, 0, imgSize - 1, imgSize - 1);
	line(0, imgSize - 1, imgSize - 1, imgSize - 1);

	// 绘制 imgUnclicked
	imgUnclicked = imgBlank;
	SetWorkingImage(&imgUnclicked);
	setlinecolor(DARKGRAY);
	line(imgSize - 2, 1, imgSize - 2, imgSize - 2);
	line(1, imgSize - 2, imgSize - 2, imgSize - 2);
	setlinecolor(WHITE);
	line(0, 0, imgSize - 2, 0);
	line(0, 0, 0, imgSize - 2);
	line(1, 1, imgSize - 3, 1);
	line(1, 1, 1, imgSize - 3);

	// 绘制 imgMine
	imgMine = imgBlank;
	SetWorkingImage(&imgMine);
	setfillcolor(BLACK);
	solidcircle((imgSize - 1) / 2, (imgSize - 1) / 2, (imgSize - 1) / 2 - 2);
	setfillcolor(WHITE);
	solidcircle((imgSize - 1) / 3, (imgSize - 1) / 3, 1);

	// 绘制 imgMineClicked
	imgMineClicked.Resize(imgSize, imgSize);
	SetWorkingImage(&imgMineClicked);
	setbkcolor(RGB(255, 0, 0));
	cleardevice();
	setlinecolor(DARKGRAY);
	line(imgSize - 1, 0, imgSize - 1, imgSize - 1);
	line(0, imgSize - 1, imgSize - 1, imgSize - 1);
	setfillcolor(BLACK);
	solidcircle((imgSize - 1) / 2, (imgSize - 1) / 2, (imgSize - 1) / 2 - 2);
	setfillcolor(WHITE);
	solidcircle((imgSize - 1) / 3, (imgSize - 1) / 3, 1);

	// 绘制 imgNums
	for (int i = 0; i < 8; ++i)
	{
		TCHAR valBuf[2];
		_stprintf_s(valBuf, _T("%d"), i + 1);
		imgNums[i] = imgBlank;
		SetWorkingImage(&imgNums[i]);
		settextstyle(imgSize - 1, 0, _T("Consolas"), 0, 0, FW_BLACK, false, false, false);
		settextcolor(TextColor[i]);
		setbkmode(TRANSPARENT);
		outtextxy((imgSize - 1 - textwidth(valBuf)) / 2, (imgSize - 1 - textheight(valBuf)) / 2, valBuf);
	}

	SetWorkingImage();
}
