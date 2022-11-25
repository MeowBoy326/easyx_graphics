#pragma once
#include <easyx.h>
#include <stack>
#include "loadimage.h"
#include "transparent.h"
#include "transformation.h"


#define  A 1000000000
typedef MyChar T;

/************************函数声明**************************/
void push(T c);								// 入栈
void pop();									// 出栈
T top();									// 取栈顶元素
bool empty();								// 判断栈是否为空
void clearstack();							// 清空栈
void change();								// 中缀表达式转换为后缀表达式
void calculate();							// 计算后缀表达式的值
void updatewithinput_();					// 普通计算：与输入有关的更新
void showscreen_();							// 普通计算：显示函数
void screenmovehd();						// 字符串滑动动画
float getfps();								// 计算 fps

extern int fx, fy;							// 判断是否可以左或者有移动算式
extern int color, color1;					// 如果左或者右可以移动，颜色变化
extern int screenmove;						// 由于算式不能完全显示。算式的左右移动像素
extern bool hd, hd1;						// 判断是否可以滑动
