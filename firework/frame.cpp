#include "frame.h"
#include <windows.h>

sy::frame::frame(int f) :
	defaultFrame(f),
	defaultDt(int((1000.0 / f) + 0.5)),
	theFrame(0)
{
	QueryPerformanceFrequency(&tickPerSecond);
	QueryPerformanceCounter(&curTick);
}

void sy::frame::Begin()
{
	QueryPerformanceCounter(&curTick);
}

void sy::frame::Flush()
{
	LARGE_INTEGER old = curTick, tmp;
	QueryPerformanceCounter(&curTick);

	int curFrame = int(tickPerSecond.QuadPart / (curTick.QuadPart - old.QuadPart));
	if (defaultFrame != 0) 
	{
		theFrame = min(curFrame, defaultFrame);
	}
	else
	{
		theFrame = curFrame;
	}
		
	if (defaultFrame != 0 && theFrame == defaultFrame)
	{
		QueryPerformanceCounter(&tmp);
		double ms = double(1000.0 / double(defaultFrame)) - 1000.0 / (double(tickPerSecond.QuadPart / (curTick.QuadPart - old.QuadPart)));
		int t = max(0,int(ms));
		this->Sleep(t);
	}
}

void sy::frame::Sleep(unsigned int ms)
{
	if (ms == 0) return;
	LARGE_INTEGER start, end;
	QueryPerformanceCounter(&start);
	while (1) 
	{
		QueryPerformanceCounter(&end);
		if ((double(end.QuadPart - start.QuadPart) / double(tickPerSecond.QuadPart) ) > (double(ms) / 1000.0)) {
			break;
		}
	}
}


