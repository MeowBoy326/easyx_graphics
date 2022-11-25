#pragma once
#include"conversion.h"

extern bool button[20][20];							// 屏幕按键标志
extern bool help[10];								// 是否打开功能选项
extern int software[3];								// 判断选择的是哪个功能（科学计算还是普通计算？...)
extern int fly, fly1;								// 上下滑动控制变量
extern float H;										// 色相

void updatewithinput5();							// 数据转换：与输入有关的更新
void updatewithinput6();							// 长度转换：与输入有关的更新
void updatewithinput7();							// 面积转换：与输入有关的更新
void updatewithinput8();							// 体积转换：与输入有关的更新
void updatewithinput9();							// 时间转换：与输入有关的更新
void updatewithinput10();							// 温度转换：与输入有关的更新
void updatewithinput11();							// 速度转换：与输入有关的更新
void updatewithinput12();							// 重量转换：与输入有关的更新
void updatewithinput13();							// 能量转换：与输入有关的更新
void updatewithinput14();							// 功率转换：与输入有关的更新
void updatewithinput15();							// 压力转换：与输入有关的更新
void updatewithinput16();							// 角度转换：与输入有关的更新

void showscreen5();									// 数据转换：显示函数
void showscreen6();									// 长度转换：显示函数
void showscreen7();									// 面积转换：显示函数
void showscreen8();									// 体积转换：显示函数
void showscreen9();									// 时间转换：显示函数
void showscreen10();								// 温度转换：显示函数
void showscreen11();								// 速度转换：显示函数
void showscreen12();								// 重量转换：显示函数
void showscreen13();								// 能量转换：显示函数
void showscreen14();								// 功率转换：显示函数
void showscreen15();								// 压力转换：显示函数
void showscreen16();								// 角度转换：显示函数

void Transform();									// 数据转换：实现函数
void Transform1();									// 长度转换：实现函数
void Transform2();									// 面积转换：实现函数
void Transform3();									// 体积转换：实现函数
void Transform4();									// 时间转换：实现函数
void Transform5();									// 温度转换：实现函数
void Transform6();									// 速度转换：实现函数
void Transform7();									// 重量转换：实现函数
void Transform8();									// 能量转换：实现函数
void Transform9();									// 功率转换：实现函数
void Transform10();									// 压力转换：实现函数
void Transform11();									// 角度转换：实现函数

void Input(int lens, int number);					// 输入
void Output(int lens);								// 输出
void Output1(MyChar Tra[][40], LPCTSTR s);			// 输出
void MemStr();										// 初始化
void WhatC(int lens);								// 判断转换
void BlStr();										// 科学计数法输出
void callen(MyChar *zfc);							// 计算字符串长度
void callen1(MyChar *zfc);							// 计算字符串长度
void callen2(MyChar *zfc);							// 计算字符串长度
void bignumber(MyChar *s4, MyChar *s5);				// 进行大数的乘法
void LsJJ(MyChar *s4, bool t);                      // 整数部分加减一
