#include "loadimage.h"

IMAGE  setimage(int wigth, int height, COLORREF rgb)
{
	IMAGE blacks(wigth, height);	// 创建 img 对象

	SetWorkingImage(&blacks);		// 设置绘图目标为 img 对象
	setfillcolor(rgb);
	solidrectangle(0, 0, wigth, height);

	SetWorkingImage();				// 设置绘图目标为绘图窗口

	return blacks;
}