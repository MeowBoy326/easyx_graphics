#include "tools.h"

void sy::ClearScreen(DWORD* pScreen, int screenW, int screenH)
{
	int i = 0;
	for (; i < screenW; i++)
	{
		pScreen[i] = 0;
	}
	for (; i < screenW * (screenH - 1); i++) 
	{
		int left = i - 1;		// 左
		int right = i + 1;		// 右
		int up = i - screenW;	// 上
		int bottom = i + screenW;	// 下

		int r = int(((double)GetRValue(pScreen[i]) + (double)GetRValue(pScreen[left]) + (double)GetRValue(pScreen[right]) + (double)GetRValue(pScreen[up]) + (double)GetRValue(pScreen[bottom])) / 5.8);
		int g = int(((double)GetGValue(pScreen[i]) + (double)GetGValue(pScreen[left]) + (double)GetGValue(pScreen[right]) + (double)GetGValue(pScreen[up]) + (double)GetGValue(pScreen[bottom])) / 5.8);
		int b = int(((double)GetBValue(pScreen[i]) + (double)GetBValue(pScreen[left]) + (double)GetBValue(pScreen[right]) + (double)GetBValue(pScreen[up]) + (double)GetBValue(pScreen[bottom])) / 5.8);

		pScreen[i] = RGB(r, g, b);
	}
	for (; i < screenW * screenH; i++) 
	{
		pScreen[i] = 0;
	}
}