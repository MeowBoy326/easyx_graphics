#pragma once


/* ----------ͷ�ļ�---------- */
#include <iostream>
#include <easyx.h>
#include <graphics.h>  


/* ----------ȫ������---------- */
// ���ڴ�С
int win_width = 640;
int win_height = 480;

// �����Ϣ
MOUSEMSG msg;

// ����״̬
enum class PState :int { HOME, RUM, END };

// ��ս������
enum class FinishCode :int { WIN, LOSE, BREAK, ESCAPE };

// ������Ϣ�ṹ��
struct Info
{
	int code;			// ״̬�룬1 �����������У�2 ��������������3 ����Ͽ�
	unsigned int uMsg;	// �����Ϣ uMsg
	int x;				// ���λ�� x
	int y;				// ���λ�� y;
};

// �������ֵ
// '0' ��ʾ�հף�'1' - '8' ��ʾ������Χ����Ŀ��ֵ 1 ��ʾ�ף�ֵ 2 ��ʾ������
char MINE = 1;
char CLICKED = 2;

// ͼ����Դ
int imgSize = 16;	// ͼ����Ӵ�С
IMAGE imgBlank;				// �հ�
IMAGE imgUnclicked;			// δ�����
IMAGE imgMine;				// ��
IMAGE imgMineClicked;		// ��������
IMAGE imgNums[8];			// ����

// ������ɫ
COLORREF TextColor[8] = { RGB(0,0,200),RGB(0,150,0),RGB(255,0,0),RGB(0,0,100),RGB(130,0,0),RGB(0,150,150),RGB(80,50,20),RGB(0,0,0) };

// ��ʼ��ͼ����Դ
void initImages()
{
	// ���� imgBlank
	imgBlank.Resize(imgSize, imgSize);
	SetWorkingImage(&imgBlank);
	setbkcolor(LIGHTGRAY);
	cleardevice();
	setlinecolor(DARKGRAY);
	line(imgSize - 1, 0, imgSize - 1, imgSize - 1);
	line(0, imgSize - 1, imgSize - 1, imgSize - 1);

	// ���� imgUnclicked
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

	// ���� imgMine
	imgMine = imgBlank;
	SetWorkingImage(&imgMine);
	setfillcolor(BLACK);
	solidcircle((imgSize - 1) / 2, (imgSize - 1) / 2, (imgSize - 1) / 2 - 2);
	setfillcolor(WHITE);
	solidcircle((imgSize - 1) / 3, (imgSize - 1) / 3, 1);

	// ���� imgMineClicked
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

	// ���� imgNums
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
