#include "global.h"

namespace sy
{
	const double g     = 9.8;	// 重力加速度			(m/s^2)
	double a_windx     = 0.0;  // 水平风阻系数			(m/s^2)
	const double v_max = 28.0;	// 最大烟花一阶段初速度	(  m/s)
	const double v_min = 15.8;	// 最小烟花一阶段初速度	(  m/s)
	const double h_max = 40.0;  // 最大高度				(    m)
	const double w_max = 70.0;	// 最大宽度              (    m)

	//int scrW = GetSystemMetrics(SM_CXSCREEN);	// 屏幕宽度
	//int scrH = GetSystemMetrics(SM_CYSCREEN);	// 屏幕高度

	int scrW = 800;		// 屏幕宽度
	int scrH = 600;		// 屏幕高度

	const int posRate = 100;  // 烟花坐标映射到的乘数因子屏幕坐标
	double	  asp     = min(scrW / (w_max * posRate), scrH / (h_max * posRate)); // 缩放因子
	

	Random genRand((unsigned int)time(nullptr));	// 用于产生随机数

	const int max_alive_time = 1400;
	const int min_alive_time = 1200;

	sy::sound& raiseSound()
	{
		static sy::sound sound(L"raise.wav", 0, 1000);
		return sound;
	}

	sy::sound& bombSound()
	{
		static sy::sound sound(L"bomb.wav", 0, 1000);
		return sound;
	}

}