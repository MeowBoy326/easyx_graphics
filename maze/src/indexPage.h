#pragma once
#ifndef __INDEXPAGE_H__
#define __INDEXPAGE_H__
#include"matrixUI.h"
#include"breakthroughPage.h"
#include<ctime>
class IndexPage {
struct Rect {
		int ltx;
		int rbx;
		int lty;
		int rby;
};	
private:
	MatrixUI& UI;
	struct Rect _buttonRange[3];
	void _buttonHover(bool button[3], MOUSEMSG& m);
	bool _judgeInRect(MOUSEMSG& m, struct Rect rect);//�ж�����Ƿ��ھ��η�Χ��
	bool _lastHoverStatus[3];//������һ���ƶ�����hover״̬
	bool _diffHoverStatus(bool button[3]);//�ж���һ������һ���Ƿ��б仯
	void _setLastHoverStatus(bool button[3]);//������һ�ε�hover״̬
	void _resetAll(void);//���ý��棬��������ʱ
public:
	IndexPage(MatrixUI& UI);
	int process(void);
};








#endif