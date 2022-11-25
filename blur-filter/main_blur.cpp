/////////////////////////////////////////////////////////////////////////
// 程序名称：将图片进行模糊处理
// 编译环境：Visual C++ 6.0 ~ 2017，EasyX 20180727(beta)
// 作　　者：krissi <zh@easyx.cn>
// 发布日期：2013-1-19
// 最后修改：2018-10-5
//
#include <graphics.h>
#include <conio.h>				

// 将图片进行模糊处理
void Blur(IMAGE *pimg)
{
	DWORD*	pMem = GetImageBuffer(pimg);

	int	r, g, b;
	int m;
	int	num = 0;
	int	width = pimg->getwidth();
	int	height = pimg->getheight();
	int step = width - 1, f, t;


	// 计算 9 格方向系数
	int	cell[9] = { -(width + 1), -1, width - 1, -width, 0, width, -(width - 1), 1, width + 1 };

	// 逐个像素点读取计算
	for (int i = width * height - 1; i >= 0; i--)
	{
		// 重置变量
		r = g = b = 0;
		m = 9;

		// 根据像素位置，决定周围格子的计算范围
		if (step == width - 1)
			t = 5, m = 6;
		else
			t = 8;

		if (step == 0)
			f = 3, m = 6, step = width;
		else
			f = 0;

		step--;

		// 累加周围格子的颜色值
		for (int n = f; n <= t; n++)
		{
			// 位置定位
			num = i + cell[n];

			// 判断位置值是否越界
			if (num < 0 || num >= width * height)
				m--;						// 统计越界像素数
			else
			{
				// 累加颜色值
				r += GetRValue(pMem[num]);
				g += GetGValue(pMem[num]);
				b += GetBValue(pMem[num]);
			}
		}

		// 将平均值赋值该像素
		pMem[i] = RGB(r / m, g / m, b / m);
	}
}

// 主函数
void main()
{
	// 初始化绘图环境
	initgraph(640, 640);

	// 获取图像
	IMAGE img;
	loadimage(&img, _T("c:\\test.jpg"));

	// 显示原始图像
	putimage(0, 0, &img);

	// 逐渐模糊
	for (int m = 0; m < 100; m++)
	{
		Blur(&img);
		// 显示处理后的图像
		putimage(320, 0, &img);
		Sleep(20);
	}

	// 任意键关闭绘图环境
	_getch();
	closegraph();
}