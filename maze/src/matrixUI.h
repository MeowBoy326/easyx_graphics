#pragma once
#ifndef __MATRIXUI_H__
#define __MATRIXUI_H__
#include<iostream>
#include <graphics.h>
#include <conio.h>
#include <easyx.h>
#include<windows.h>
using namespace std;
struct Point {
		int x;
		int y;
};
class MatrixUI {

public:
	MatrixUI();
	void init(int width, int height);//��������
	void close(void);//�رս���
	bool getInitFlag(void);//����Ƿ񴴽��˽���
	void setBkColor(char r,char g,char b);//���ñ���ͼ����ɫ
	void setUIBuffer(struct Point, char r, char g, char b);//����������ɫ
	int	 getWidth(void);
	int	 getHeight(void);
private:
	bool _initFlag = false;//�Ƿ񴴽��˽���
	int _width = 0;
	int _height = 0;
};



#endif
