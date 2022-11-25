// 代码名称：精确到微秒的延时类（基于多媒体定时器）
// 代码编写：yangw80 <yw80@qq.com>
// 最后修改：2011-5-4
// 　　　　　2013-11-2 修改为静态调用
//
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <sys/timeb.h>

class MMTimer
{
private:
	static LARGE_INTEGER m_clk;			// 保存时钟信息
	static LONGLONG m_oldclk;			// 保存开始时钟和结束时钟
	static int m_freq;					// 时钟频率(时钟时间换算率)，时间差

public:
	static void Sleep(int ms);
};

LARGE_INTEGER MMTimer::m_clk;
LONGLONG MMTimer::m_oldclk;
int MMTimer::m_freq = 0;

// 延时
void MMTimer::Sleep(int ms)
{
	if (m_oldclk == 0)
	{
		QueryPerformanceFrequency(&m_clk);
		m_freq = (int)m_clk.QuadPart / 1000;	// 获得计数器的时钟频率

		// 开始计时
		QueryPerformanceCounter(&m_clk);
		m_oldclk = m_clk.QuadPart;				// 获得开始时钟
	}

	unsigned int c = ms * m_freq;

	m_oldclk += c;

	QueryPerformanceCounter(&m_clk);

	if (m_clk.QuadPart > m_oldclk)
		m_oldclk = m_clk.QuadPart;
	else
		do
		{
			::Sleep(1);
			//			::Sleep(0);							// 更高精度、更高 CPU 占用率
			QueryPerformanceCounter(&m_clk);	// 获得终止时钟
		} while (m_clk.QuadPart < m_oldclk);
}


// 精确延时函数(可以精确到 1ms，精度 ±1ms)
// by yangw80<yw80@qq.com>, 2011-5-4
void HpSleep(int ms)
{
	static clock_t oldclock = clock();		// 静态变量，记录上一次 tick

	oldclock += ms * CLOCKS_PER_SEC / 1000;	// 更新 tick

	if (clock() > oldclock)					// 如果已经超时，无需延时
		oldclock = clock();
	else
		while (clock() < oldclock)			// 延时
			Sleep(1);						// 释放 CPU 控制权，降低 CPU 占用率，精度 10~16ms
	//			Sleep(0);						// 更高精度、更高 CPU 占用率，精度 1ms
}


char*   log_Time(void)
{
	struct  tm      *ptm;
	struct  timeb   stTimeb;
	static  char    szTime[19];

	ftime(&stTimeb);
	ptm = localtime(&stTimeb.time);
	sprintf(szTime, "%02d-%02d %02d:%02d:%02d.%03d",ptm->tm_mon + 1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec, stTimeb.millitm);
	szTime[18] = 0;
	return szTime;
}


int main()
{

	time_t rawtime;
	struct tm *ptminfo;

	time(&rawtime);
	ptminfo = localtime(&rawtime);
	printf("current: %02d-%02d-%02d %02d:%02d:%02d\n",ptminfo->tm_year + 1900, ptminfo->tm_mon + 1, ptminfo->tm_mday,ptminfo->tm_hour, ptminfo->tm_min, ptminfo->tm_sec);
	
	printf("[%s]\n", log_Time());
	HpSleep(500);
	printf("[%s]\n", log_Time());
	
	time(&rawtime);
	ptminfo = localtime(&rawtime);
	printf("current: %02d-%02d-%02d %02d:%02d:%02d\n", ptminfo->tm_year + 1900, ptminfo->tm_mon + 1, ptminfo->tm_mday, ptminfo->tm_hour, ptminfo->tm_min, ptminfo->tm_sec);
	
	printf("---------------------------------------\n");
	
	time(&rawtime);
	ptminfo = localtime(&rawtime);
	printf("current: %02d-%02d-%02d %02d:%02d:%02d\n", ptminfo->tm_year + 1900, ptminfo->tm_mon + 1, ptminfo->tm_mday, ptminfo->tm_hour, ptminfo->tm_min, ptminfo->tm_sec);

	printf("[%s]\n", log_Time());
	MMTimer::Sleep(500);
	printf("[%s]\n", log_Time());

	time(&rawtime);
	ptminfo = localtime(&rawtime);
	printf("current: %02d-%02d-%02d %02d:%02d:%02d\n", ptminfo->tm_year + 1900, ptminfo->tm_mon + 1, ptminfo->tm_mday, ptminfo->tm_hour, ptminfo->tm_min, ptminfo->tm_sec);

	
	getchar();
}