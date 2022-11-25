///////////////////////////////////////////////////
// 程序名称：多个小球在方框内的碰撞运动
// 编译环境：Visual C++ 6.0，EasyX 2013冬至版
// 作　　者：可可 
// 最后修改：2014-03-18
//
#include <graphics.h>
#include <conio.h>
#include <math.h>
#define	 XN	640
#define	 YN	480						// 设置图形窗口的大小
#define	 N	40						// 设置球的个数，最多 90 个
#define	 V	20						// 设置球的速度

// 画出一个球
void Ball(int x, int y)
{
	fillcircle(x, YN - y, 20);		// 转换成常用的坐标
}

// 判定是否发生二维平面小球完全弹性碰撞(速度较大)
// (当速度很小时，不服从。因为计算后的结果因为保留有限位而比真实情况小，很快衰减到 0)
int PerfectElasticCollision(float v1[2], float v2[2], float u[2])
{
	float t, v11[2], v12[2], v21[2], v22[2];			// 保存球心连线上和垂直于连线的速度分量
	v11[0] = (v1[0] * u[0] + v1[1] * u[1]) * u[0] / (u[0] * u[0] + u[1] * u[1]);
	v11[1] = (v1[0] * u[0] + v1[1] * u[1]) * u[1] / (u[0] * u[0] + u[1] * u[1]);
	v12[0] = v1[0] - v11[0];
	v12[1] = v1[1] - v11[1];
	v21[0] = (v2[0] * u[0] + v2[1] * u[1]) * u[0] / (u[0] * u[0] + u[1] * u[1]);
	v21[1] = (v2[0] * u[0] + v2[1] * u[1]) * u[1] / (u[0] * u[0] + u[1] * u[1]);
	v22[0] = v2[0] - v21[0];
	v22[1] = v2[1] - v21[1];
	if ((((fabs(v11[0]) <= fabs(v21[0])) && (v11[0] * u[0] >= 0) && (v11[0] * v21[0] >= 0)) ||
		((v11[0] * v21[0] <= 0) && (v21[0] * u[0] >= 0)) ||
		((fabs(v11[0]) >= fabs(v21[0])) && (v21[0] * u[0] >= 0) && (v11[0] * v21[0] >= 0))) &&
		(((fabs(v11[1]) <= fabs(v21[1])) && (v11[1] * u[1] >= 0) && (v11[1] * v21[1] >= 0)) ||
		((v11[1] * v21[1] <= 0) && (v21[1] * u[1] >= 0)) ||
		((fabs(v11[1]) >= fabs(v21[1])) && (v21[1] * u[1] <= 0) && (v11[1] * v21[1] >= 0))))
		return 0;					// 不会发生碰撞的情况就直接返回

	// 在球心连线上速度交换
	t = v11[0];
	v11[0] = v21[0];
	v21[0] = t;
	t = v11[1];
	v11[1] = v21[1];
	v21[1] = t;

	// 得到新的速度
	v1[0] = v11[0] + v12[0];
	v1[1] = v11[1] + v12[1];
	v2[0] = v21[0] + v22[0];
	v2[1] = v21[1] + v22[1];

	return 1;
}

// 最小时间单位内的位移变化  
int BallMove(float x[], float y[], float a[], float b[], int n)
{
	for (int i = 0; i < n; i++)
	{
		x[i] += a[i] / 100;			// 对最小长度(这里指一个像素点的抽象的边长)的分割
		y[i] += b[i] / 100;
	}
	return 0;
}

// 碰撞判定
void Judge(float x[], float y[], float a[], float b[], int n)
{
	int i = 0, j = 0;
	float v1[2], v2[2], u[2];		// 保存相碰两小球的初速度和碰撞方向
	while (i < n)					// 小球是否相碰
	{

		for (j = i + 1; j < n; j++)
		{
			if (((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]) <= 1600))
			{
				u[0] = x[j] - x[i];		// 保存两小球的初速度和碰撞方向
				u[1] = y[j] - y[i];
				v1[0] = a[i];
				v1[1] = b[i];
				v2[0] = a[j];
				v2[1] = b[j];

				// 判定两相切小球是否相碰
				if (PerfectElasticCollision(v1, v2, u))
				{
					a[i] = v1[0];			// 碰撞后两小球的速度的改变
					b[i] = v1[1];
					a[j] = v2[0];
					b[j] = v2[1];
				}
			}
		}
		i++;
	}
	i = 0;
	while (i < n)		// 小球是否碰壁
	{
		if ((x[i] - 21) <= 0 || ((XN - 21) - x[i]) <= 0)
			if ((y[i] - 21) <= 0 || (y[i] - (YN - 21)) >= 0)
			{
				a[i] = -a[i];
				b[i] = -b[i];
			}
			else
				a[i] = -a[i];
		if ((y[i] - 21) <= 0 || (y[i] - (YN - 21)) >= 0)
			b[i] = -b[i];
		i++;
	}
	return;
}

// 主函数
void main()
{
	int i = 0, j = 0, n = N;
	float x[N] = { 0 }, y[N] = { 0 }, a[N] = { 0 }, b[N] = { 0 };

	// 初始化坐标位置(x[], y[])和速度向量(a[], b[]), 速度向量
	for (i = 0; i < n; i += 1)
	{
		x[i] = (float)50 * (i % 10) + 50;
		y[i] = (float)50 * (i / 10) + 50;
		a[i] = (float)V;
		b[i] = (float)-V * (i % 2);
	}

	initgraph(XN, YN);
	BeginBatchDraw();
	setrop2(R2_XORPEN);
	setfillcolor(RED);

	while (true)
	{
		for (i = 0; i<n; i++)
			Ball((int)x[i], (int)y[i]);
		FlushBatchDraw();
		Sleep(1);
		for (i = 0; i<n; i++)
			Ball((int)x[i], (int)y[i]);
		Judge(x, y, a, b, n);			// 判定是否相碰或碰壁，若有，改变速度向量
		BallMove(x, y, a, b, n);		// 最小时间单位坐标位置的变动
	}

	EndBatchDraw();
	getch();
	closegraph();
}