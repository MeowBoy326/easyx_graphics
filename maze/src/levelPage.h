#pragma once
#ifndef __LEVELPAGE_H__
#define __LEVELPAGE_H__
#include"matrixUI.h"
#include"mapread.h"
#include<ctime>
#include <sstream>
#include <string>
#include <iostream>
#include <locale>
#include <cstdlib>
class LevelPage {
	struct Rect {
		int ltx;
		int rbx;
		int lty;
		int rby;
	};

private:
	//��ͼ�ļ���ȡ
	MapRead _MapRead;
	//@����ҳ��ı���ͼƬ
	const wchar_t *_backgroundSrc=L"./img/levelPage/1.png";
	//����λ��
	struct Rect _buttonDatas[2];
	//��ʱ�Ĺؿ�
	char _NOWLEVEL;
	int _getMouseState(ExMessage& m);
	bool _judgeInRect(ExMessage& m, struct Rect rect);
	//�洢�˵�λ��
	Point _body;
	//�洢�Թ���ͼ
	char _Map[29][41];
	void _setBodyImg(int x, int y);//��ʾ����
	void _setBlockColor(int x, int y, char r, char g, char b);//�����Թ�����ɫ
	void _setUIBuffer(struct Point point, char r, char g, char b);//����ָ�����
	void _moveBody(int x, int y);
	void _WinPoPWindow(clock_t& start, int& ss);
	void _showTime(clock_t& start,int&ss, RECT* r);
	void _setLiangCang();
	void _alertOver();
public:
	LevelPage(unsigned char level);
	void process(void);
};
#endif
