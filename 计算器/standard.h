#pragma once
#include <easyx.h>
#include <stack>
#include "loadimage.h"
#include "transparent.h"
#include "transformation.h"


#define  A 1000000000
typedef MyChar T;

/************************��������**************************/
void push(T c);								// ��ջ
void pop();									// ��ջ
T top();									// ȡջ��Ԫ��
bool empty();								// �ж�ջ�Ƿ�Ϊ��
void clearstack();							// ���ջ
void change();								// ��׺���ʽת��Ϊ��׺���ʽ
void calculate();							// �����׺���ʽ��ֵ
void updatewithinput_();					// ��ͨ���㣺�������йصĸ���
void showscreen_();							// ��ͨ���㣺��ʾ����
void screenmovehd();						// �ַ�����������
float getfps();								// ���� fps

extern int fx, fy;							// �ж��Ƿ������������ƶ���ʽ
extern int color, color1;					// ���������ҿ����ƶ�����ɫ�仯
extern int screenmove;						// ������ʽ������ȫ��ʾ����ʽ�������ƶ�����
extern bool hd, hd1;						// �ж��Ƿ���Ի���
