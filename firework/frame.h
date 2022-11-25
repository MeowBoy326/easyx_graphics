#pragma once
#include <iostream>
#include <ctime>
#include <windows.h>
namespace sy 
{
	/************进行帧率的控制和计算**********/
	class frame
	{
	public:
		unsigned Value() { return theFrame; }
	public:
		frame(int f = 0);
		void Begin();		// 开始时调用
		void Flush();		// 每帧调用
		void Sleep(unsigned int ms);	// 睡眠 ms 毫秒 

	private:
		int theFrame;		// 当前帧数
		int defaultFrame;	// 0代表不进行控制
		int defaultDt;		// 默认每帧的时间差
		
		LARGE_INTEGER curTick;		// 计时使用
		LARGE_INTEGER tickPerSecond;// 每秒时钟滴答声数
	public:
	};
}

