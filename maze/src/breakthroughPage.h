#pragma once
#ifndef __BREAKTHROUGHPAGE_H__
#define __BREAKTHROUGHPAGE_H__
#include"matrixUI.h"
#include"levelPage.h"
class BreakthroughPage {
	struct Rect {
		int ltx;
		int rbx;
		int lty;
		int rby;
	};
private:
	MatrixUI UI;
	struct Rect _buttonRange[9];
	bool _lastHoverStatus[9];//保存上一次移动鼠标的hover状态
	bool _judgeInRect(MOUSEMSG& m, struct Rect rect);
	void _buttonHover(bool button[9], MOUSEMSG& m);
	void _resizeButton(bool button[9],int target);
	int _mClick(MOUSEMSG& m);
	void _resetUI(void);
public:
	BreakthroughPage(MatrixUI& UI);
	int process(void);
};


#endif