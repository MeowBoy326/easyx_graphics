#pragma once
#include"graphics.h"

class control
{
private:
	int key;
private:
    int GetCommand();
	void pauseClick();
public:
	control(void);
	~control(void);
	int getKey();//��ȡ��Ұ��µļ�	
	void gameStart();//��Ϸ��ʼ����
	void showScore(int score);
	void showLevel(int level);
	void showDied(int life);     //��������ʱ�Ķ���
	void showGameOver();         //��Ϸ����ʱ�Ķ���
	void showPassed(int word);   //���ǹ���ʱ�Ķ���
	void showPassedAll();        //ͨ��ʱ�Ķ���
};
