#pragma once

#include <cmath>
#include <cstdio>
#include <easyx.h>
#include "loadimage.h"
#include "conversion.h"
#include "transparent.h"
#include "transformation.h"


/**********************************函数声明******************************/

void bignumberadd();						// 超大数加法
void bignumbersubtract();					// 超大数减法
void bignumbermuit();						// 超大数乘法
void bignumberdiv();						// 超大数除法
void updatewithinput1();					// 超大数：与输入有关的更新
void showscreen1();							// 超大数：显示函数

extern bool button1[10];
