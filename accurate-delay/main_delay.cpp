// �������ƣ���ȷ��΢�����ʱ�ࣨ���ڶ�ý�嶨ʱ����
// �����д��yangw80 <yw80@qq.com>
// ����޸ģ�2011-5-4
// ����������2013-11-2 �޸�Ϊ��̬����
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
	static LARGE_INTEGER m_clk;			// ����ʱ����Ϣ
	static LONGLONG m_oldclk;			// ���濪ʼʱ�Ӻͽ���ʱ��
	static int m_freq;					// ʱ��Ƶ��(ʱ��ʱ�任����)��ʱ���

public:
	static void Sleep(int ms);
};

LARGE_INTEGER MMTimer::m_clk;
LONGLONG MMTimer::m_oldclk;
int MMTimer::m_freq = 0;

// ��ʱ
void MMTimer::Sleep(int ms)
{
	if (m_oldclk == 0)
	{
		QueryPerformanceFrequency(&m_clk);
		m_freq = (int)m_clk.QuadPart / 1000;	// ��ü�������ʱ��Ƶ��

		// ��ʼ��ʱ
		QueryPerformanceCounter(&m_clk);
		m_oldclk = m_clk.QuadPart;				// ��ÿ�ʼʱ��
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
			//			::Sleep(0);							// ���߾��ȡ����� CPU ռ����
			QueryPerformanceCounter(&m_clk);	// �����ֹʱ��
		} while (m_clk.QuadPart < m_oldclk);
}


// ��ȷ��ʱ����(���Ծ�ȷ�� 1ms������ ��1ms)
// by yangw80<yw80@qq.com>, 2011-5-4
void HpSleep(int ms)
{
	static clock_t oldclock = clock();		// ��̬��������¼��һ�� tick

	oldclock += ms * CLOCKS_PER_SEC / 1000;	// ���� tick

	if (clock() > oldclock)					// ����Ѿ���ʱ��������ʱ
		oldclock = clock();
	else
		while (clock() < oldclock)			// ��ʱ
			Sleep(1);						// �ͷ� CPU ����Ȩ������ CPU ռ���ʣ����� 10~16ms
	//			Sleep(0);						// ���߾��ȡ����� CPU ռ���ʣ����� 1ms
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