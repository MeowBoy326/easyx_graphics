#pragma once
#include <graphics.h>
#include <ctime>

namespace sy
{

	// 缓慢清除屏幕， 这里使用将所有点与周围像素点进行平均，这样像素点会逐渐趋于全局最小值，也就是黑色（0）
	/*
	* pScreen 显示缓存
	* screenW 宽度
	* screenH 高度
	*/
	void ClearScreen(DWORD* pScreen, int screenW, int screenH);


	/***************************用于产生随机数***********************/
	class Random
	{
	private:
		unsigned int seed;	// 随机数种子

	public:
		Random(unsigned int s)
		{
			seed = s;
			srand(seed);
		}

		int Value()
		{
			seed = rand();
			srand(static_cast<unsigned>(time(nullptr)) - seed);
			return seed;
		}

		/***************产生一个[low,gight]范围的整数*****************/
		int GetInt(int low, int hight)
		{
			return Value() % (hight - low + 1) + low;
		}

		/***************产生一个[low,gight]范围的浮点数，精确到百分位*****************/
		double GetDouble(double low, double hight)
		{
			double tmp = GetInt(static_cast<int>(low * 100), static_cast<int>(hight * 100));
			return tmp / 100.0;
		}
	};


}