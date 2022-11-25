// 程序名称：分形学 - Julia Set (茱莉亚集)
// 编译环境：Visual C++ 6.0，EasyX_20200902
// 最后更新：2010-9-9
//
#include <graphics.h>
#include <conio.h>

/////////////////////////////////////////////////
// 定义复数及乘、加运算
/////////////////////////////////////////////////

// 定义复数
struct COMPLEX
{
	double re;
	double im;
};

// 定义复数“乘”运算
COMPLEX operator * (COMPLEX a, COMPLEX b)
{
	COMPLEX c;
	c.re = a.re * b.re - a.im * b.im;
	c.im = a.im * b.re + a.re * b.im;
	return c;
}

// 定义复数“加”运算
COMPLEX operator + (COMPLEX a, COMPLEX b)
{
	COMPLEX c;
	c.re = a.re + b.re;
	c.im = a.im + b.im;
	return c;
}


/////////////////////////////////////////////////
// 主函数
/////////////////////////////////////////////////
int main()
{
	// 初始化绘图窗口
	initgraph(640, 480);

	/////////////////////////////////////////////////
	// 绘制 Julia Set (茱莉亚集)
	/////////////////////////////////////////////////
	COMPLEX z, c;
	c.re = -0.75, c.im = 0;	// 设置迭代初值

	int x, y, k;			// 定义循环变量
	for (x = 0; x < 640; x++)
	{
		for (y = 0; y < 480; y++)
		{
			z.re = -1.6 + 3.2 * (x / 640.0);
			z.im = -1.2 + 2.4 * (y / 480.0);
			for (k = 0; k < 180; k++)
			{
				if (z.re * z.re + z.im * z.im > 4.0)	break;
				z = z * z + c;
			}
			putpixel(x, y, (k >= 180) ? 0 : HSLtoRGB((float)((k << 5) % 360), 1.0, 0.5));
		}
	}

	// 按任意键退出
	getch();
	closegraph();
	return 0;
}