#pragma once
#include"matrixUI.h"
#ifndef __POPUPMODULE_H__
#define __POPUPMODULE_H__
class PopUpModule {
	struct Rect {
		int ltx;
		int rbx;
		int lty;
		int rby;
	};
private:
	int _screenWidth=1280, _screenHeight=720;
	int _popWidth, _popHeight;
	IMAGE _oldImg;
	IMAGE _newImg;
	struct Rect _backButton;
public:
	void reset(void);//�رյ���
	void show(const wchar_t* filename);//��ʾ����
	void getBackButton(int *point);//�����˳���ť
};
#endif