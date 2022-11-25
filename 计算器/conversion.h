#pragma once
#include<stack>
#include<easyx.h>
#include<iostream>
#include"bignumber.h"
#include"transformation.h"


/*-------------------------------函数声明-------------------------------------*/

void conversion(char *sss, long long x, int n);        //利用栈进行进制转换
void memse();                                          //初始化
void everone(int n = 2);                               //分别计算各个进制
void updatewithinput3();                               //进制转换：与输入有关的更新
void showscreen3();                                    //进制转换：显示函数
void changecolor(int Left, int Right, int Top,
	int Bottom, float l = 0.0008f,
	float k = 1.0f, bool t = false);                   //改变颜色

/*----------------------------------------------------------------------------*/


