/*
* 程序名称：	烟花
* 环   境：	VS2019, EasyX 2021 版 , C++11
* 作   者：  孙小鱼（QQ:1226598193）
* 版   权：  作者原创，无抄袭，不涉及版权问题
* 完成时间： 2021-02-18
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <conio.h>

#include "global.h"
#include "tools.h"
#include "raise.h"
#include "bomb.h"
#include "firework.h"
#include "frame.h"

// 设置坐标系统
void InitPositionSystem()
{
	setaspectratio(static_cast<float>(sy::asp), static_cast<float>(-sy::asp));	// 设置缩放比例 以及坐标方向
	setorigin(0, sy::scrH);				// 设置坐标原点
}

// 显示帧数
void DrawFrame(int Value, int x = 5, int y = 5)
{
	setbkmode(TRANSPARENT);			// 透明文字
	settextcolor(RGB(0, 255, 0));
	settextstyle(20, 0, TEXT("新宋体"));


	setaspectratio(1.0,1.0);		// 设置缩放比例 以及坐标方向， 在这里不设置回来的话，文字输出是镜面反转的
	setorigin(0, 0);				// 设置坐标原点
	TCHAR buff[256];
	wsprintf(buff, _T("%d FPS"), Value);
	outtextxy(x, y, buff);

	InitPositionSystem();
}

int main()
{
	initgraph(sy::scrW, sy::scrH);
	InitPositionSystem();
	BeginBatchDraw();
	DWORD* pScreen = GetImageBuffer(nullptr);	// 获取屏幕显存
	sy::frame calFrame(30);			// 限制帧数为60, 若改为0则不限制帧数 
	calFrame.Begin();

	const int maxFireNums = 30;		// 最大烟花个数
	std::list<sy::firework> arr;

	srand(static_cast<unsigned>(time(nullptr)));
	for (int i = 0; i < 3; ++i)		// 初始化3个烟花
	{	
		sy::firework tmp;
		arr.push_back(tmp);
	}

	while (!_kbhit()) 
	{
		sy::ClearScreen(pScreen, sy::scrW, sy::scrH);

		// 所有的烟花每帧进行更新烟花属性和绘画
		for (std::list<sy::firework>::iterator it = arr.begin(); it != arr.end();) 
		{
			it->Update();
			it->Draw();
			if (it->IsStop())
			{ 
				it = arr.erase(it); 
			}
			else 
			{ 
				it++; 
			}
		}
		
		//绘制帧数 
		DrawFrame(calFrame.Value());
		
		FlushBatchDraw();
		calFrame.Flush();

		if (!sy::genRand.GetInt(0, 20) && arr.size() < maxFireNums) // 随机生成数字 0,1,2,...,40  数字为0的话，随机生成一个烟花
		{	
			sy::firework tmp;
			arr.push_back(tmp);
		}
	}
	EndBatchDraw();
	while (!_kbhit());
	return 0;
}