#pragma once
#include <Windows.h>
#include "tools.h"
#include "sound.h"

namespace sy 
{
	extern const double g;			// 重力加速度			(m/s^2)
	extern double		a_windx;	// 水平方向风阻系数		(m/s^2)
	extern const double v_max;		// 最大烟花一阶段初速度	(  m/s)
	extern const double v_min;		// 最小烟花一阶段初速度	(  m/s)
	extern const double h_max;		// 最大高度				(    m)
	extern const double w_max;		// 最大宽度              (    m)

	extern int scrW;				// 屏幕宽度
	extern int scrH;				// 屏幕高度
		
	extern Random genRand;			// 用于产生随机数的实例

	extern double       asp;		// 缩放因子
	extern const int	posRate;	// 烟花坐标映射到屏幕坐标的乘数因子

	extern const int max_alive_time;// 爆炸粒子最大生存时间 （ms）
	extern const int min_alive_time;// 爆炸粒子最小生存时间 （ms）

	sy::sound& raiseSound();		// 全局使用一个 raise.wav 实例
	sy::sound& bombSound();			// 全局使用一个  bomb.wav 实例

	struct position
	{
		double x;
		double y;
		position() :x(0.0f), y(0.0f) {}
		position(double _X,double _Y):x(_X),y(_Y){}
	};
}