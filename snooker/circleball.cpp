/***************
			该函数适用于背景色较纯的情况
			将你所想要显示在屏幕上的最终效果图片与背景 XOR 操作
			并截取该异或后的效果图，用此效果图即可与背景 XOR 操作获得效果图
									****************************/

#include "circleball.h"


									// 从 p 图片的中心获取半径为 r 的圆形部分，与颜色 color 位操作后得到的新图片，存进 Img
void CircleImg(IMAGE* Img, COLORREF color, IMAGE* p, int r, DWORD dwRop)
{
	IMAGE* save = GetWorkingImage();				// 记录之前的绘图设备，函数结束时必须回到该设备!!

	SetWorkingImage(p);							// 在传进来的对象上操作
	int width = getwidth();						// 获取该 img 的大小
	int height = getheight();

	Resize(Img, 2 * r, 2 * r);					// 用来储存最终结果
	IMAGE newimg(2 * r, 2 * r);					// 制作圆形区域，该区域与 bkimg 异或后得到 Img

	IMAGE bkimg(2 * r, 2 * r);					// 制作一个背景色的 img
	SetWorkingImage(&bkimg);
	setbkcolor(color);
	cleardevice();

	for (int ix = 0; ix < 2 * r; ix++)		// 扫描所有点，圆外点用背景色，圆内复制 p 里面的对应部分
	{
		for (int iy = 0; iy < 2 * r; iy++)
		{
			double Lx = ix - r;
			double Ly = iy - r;

			if (Lx * Lx + Ly * Ly > r * r)		// 绘制在圆外的部分
			{
				SetWorkingImage(&newimg);
				putpixel(ix, iy, color);			// 圆外弄成背景色，后面与背景 img 以后就会得到黑色。
			}
			else									// 绘制在园内的部分
			{
				SetWorkingImage(p);				// 从 p 获取园内的部分
				int pix2 = getpixel(ix + width / 2 - r, iy + height / 2 - r);

				SetWorkingImage(&newimg);
				putpixel(ix, iy, pix2);
			}
		}
	}

	SetWorkingImage(&bkimg);					// 将完整的图片与背景色异或
	putimage(0, 0, &newimg, dwRop);

	getimage(Img, 0, 0, 2 * r, 2 * r);		// 将最终异或的结果存进 Img
	SetWorkingImage(save);
}


// 在圆心 x，y 出输出该圆形 img  
void putcircle(int x, int y, IMAGE* img, DWORD dwRop)
{
	IMAGE* sav = GetWorkingImage();
	SetWorkingImage(img);
	int r = getwidth() / 2;

	SetWorkingImage(sav);
	putimage(x - r, y - r, img, dwRop);
}