/*
 *　　作者：孙小鱼
 *　　ＱＱ：1226598193
 *实现原理：https://www.bilibili.com/video/BV1vt411N7Ti
 */
#include <graphics.h>
#include <conio.h>
#include <vector>
#include <cmath>
#include <algorithm>


#define X(x) ( (x) + (xScreen * 0.5f))
#define Y(y) (-(y) + (yScreen * 0.5f))		// 绘图坐标转换

using namespace std;

const int xScreen = 800;					// 屏幕宽度
const int yScreen = 800;					// 屏幕高度
const float PI = 3.1415927f;

#pragma region 图形绘制
struct point
{
	float x, y;
};

void syLine(const point& start, const point& end, COLORREF color = WHITE)
{
	setlinecolor(color);
	line(X((int)(start.x + 0.5f)), Y((int)(start.y + 0.5f)), X((int)(end.x + 0.5f)), Y((int)(end.y + 0.5f)));
}

void syCircle(const point& center, float radius, COLORREF color = WHITE)
{
	setlinecolor(color);
	circle(X((int)(center.x + 0.5f)), Y((int)(center.y + 0.5f)), (int)(radius + 0.5f));
}

#pragma endregion

#pragma region 数学

/* 复数结构 */
struct complex
{
	union
	{
		struct { float r, i; };
		struct { float really, imaginary; };	// 实部、虚部
	};

	complex(float _really = 0.0f, float _imaginary = 0.0f)
		: r(_really), i(_imaginary)
	{}

	complex(const complex& cmp)
	{
		r = cmp.r;
		i = cmp.i;
	}
	complex& operator=(const complex& cmp)
	{
		r = cmp.r;
		i = cmp.i;
		return *this;
	}
	
	point ToPoint()
	{
		return { r, i };
	}

	float abs()
	{
		return sqrtf(r * r + i * i);
	}
};

inline complex operator*(const complex& a, const complex& b)
{
	return { a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r };
}

inline complex operator+(const complex& a, const complex& b)
{
	return { a.r + b.r, a.i + b.i };
}

inline complex operator/(const complex& a, float b)
{
	if (b != 0.0f)
	{
		return { a.r / b, a.i / b };
	}
	return a;
}

// 欧拉公式
complex ExpComplex(float x)
{
	return { cosf(x), sinf(x) };
}

// 求 [0，1）区间上的积分, k E [-N, N],（N = ft.size()）
complex Integrate(vector<complex> ft, int k)
{
	complex ret = { 0.0f, 0.0f };
	float N = (float)ft.size();
	float dt = 1.0f / N;
	for (int i = 0; i < ft.size(); ++i)
	{
		ret = ret + ft[i] * ExpComplex(-2.0f * PI * k * ((i+1) / N)) * dt;
	}
	return ret;
}

// 对 in 做离散傅里叶变换，out 为变换的结果，返回变换是否成功
bool DFT(vector<complex>& in, vector<complex>& out)
{
	int N = in.size();
	int M = out.size() / 2;
	for (int k = -M; k <= M; ++k)
	{
		int index = k + M;
		out[index] = Integrate(in, k);
	}
	return true;
}
#pragma endregion

// 自定义需要绘画图形的外轮廓点(坐标取复平面坐标)，这里我们以 4 角星的轮廓做例子，当然你可以修改为任意其它坐标点，坐标单位（像素点），画图坐标已经做了笛卡尔坐标系的转换
vector<complex> origin =
{
	{ -0.65,  7.46 }, { -0.91,  7.46 }, { -1.11,  7.43 }, { -1.23,  7.35 }, { -1.31,  7.23 }, { -1.48,  7.09 }, { -1.77,  7.03 }, { -2.02,  6.83 }, { -2.12,  6.69 },
	{ -2.23,  6.49 }, { -2.29,  6.32 }, { -2.35,  6.15 }, { -2.60,  5.89 }, { -2.62,  5.65 }, { -2.65,  5.40 }, { -2.63,  5.12 }, { -2.74,  4.94 }, { -2.88,  4.77 }, { -2.85,  4.40 },
	{ -2.68,  4.22 }, { -2.85,  3.92 }, { -2.88,  3.60 }, { -2.66,  3.14 }, { -2.57,  2.77 }, { -2.40,  2.43 }, { -2.03,  2.25 }, { -2.05,  2.03 }, { -2.35,  1.77 }, { -2.42,  1.43 },
	{ -2.57,  0.52 }, { -3.11, -0.32 }, { -3.32, -0.57 }, { -4.34, -1.42 }, { -5.26, -2.32 }, { -5.85, -3.15 }, { -6.22, -4.06 }, { -6.31, -6.74 }, { -4.63, -7.37 }, { -3.25, -7.83 },
	{ -2.49, -7.95 }, { -2.52, -6.74 }, { -2.68, -6.25 }, { -2.62, -5.66 }, { -2.42, -5.20 }, { -2.52, -4.32 }, { -2.35, -5.22 }, { -2.32, -6.40 }, { -2.40, -7.82 }, { -2.31, -8.14 },
	{ -2.11, -8.35 }, { -1.80, -8.26 }, { -0.35, -8.37 }, {  0.40, -8.46 }, {  1.25, -8.49 }, {  2.05, -8.31 }, {  2.26, -8.00 }, {  2.17, -6.66 }, {  2.05, -6.60 }, {  1.75, -6.92 },
	{  1.42, -7.00 }, {  1.17, -6.66 }, {  1.25, -6.34 }, {  1.69, -6.18 }, {  1.91, -6.38 }, {  2.06, -6.48 }, {  2.00, -5.82 }, {  1.68, -4.97 }, {  1.48, -4.42 }, {  1.26, -4.46 },
	{  0.97, -4.82 }, {  0.72, -4.77 }, {  0.54, -4.60 }, {  0.57, -4.28 }, {  0.77, -4.18 }, {  1.09, -4.22 }, {  1.32, -4.35 }, {  1.32, -4.08 }, {  1.22, -3.68 }, {  0.69, -2.65 },
	{  0.48, -2.42 }, {  0.32, -2.43 }, {  0.26, -2.74 }, {  0.02, -2.97 }, { -0.28, -2.89 }, { -0.35, -2.54 }, { -0.25, -2.40 }, {  0.12, -2.28 }, {  0.32, -2.34 }, {  0.32, -1.88 },
	{ -0.05, -1.49 }, { -0.32, -1.02 }, { -0.71,  0.02 }, { -1.14,  0.66 }, { -1.69,  0.94 }, { -2.11,  1.43 }, { -2.15,  1.69 }, { -1.86,  1.71 }, { -1.40,  1.17 }, { -0.94,  0.77 },
	{ -0.29, -0.14 }, {  0.29, -1.14 }, {  0.57, -1.66 }, {  1.91, -1.46 }, {  2.02, -0.83 }, {  2.02, -0.15 }, {  2.18,  0.32 }, {  2.40,  0.51 }, {  2.75,  0.26 }, {  3.00, -0.69 },
	{  3.29, -1.98 }, {  3.89, -2.52 }, {  3.82, -3.77 }, {  3.97, -4.46 }, {  3.65, -5.17 }, {  3.49, -5.42 }, {  3.26, -6.09 }, {  2.92, -6.42 }, {  2.89, -7.03 }, {  2.97, -7.37 },
	{  3.00, -8.17 }, {  3.60, -8.29 }, {  4.32, -8.03 }, {  4.92, -7.65 }, {  5.49, -7.08 }, {  6.15, -6.35 }, {  5.98, -4.14 }, {  4.66, -1.72 }, {  4.38, -1.52 }, {  3.80, -1.32 },
	{  3.51, -0.71 }, {  3.29,  0.29 }, {  3.05,  0.49 }, {  2.82,  0.49 }, {  2.58,  0.74 }, {  2.49,  1.26 }, {  2.46,  1.46 }, {  2.69,  2.20 }, {  1.95,  0.52 }, {  1.77,  0.28 },
	{  1.31,  0.12 }, {  0.78,  0.32 }, { -0.08,  0.85 }, { -0.85,  1.11 }, { -1.34,  1.51 }, { -1.40,  1.85 }, { -1.97,  2.38 }, { -2.15,  2.72 }, { -2.20,  3.09 }, { -1.86,  3.31 },
	{ -1.58,  2.92 }, { -1.42,  2.68 }, { -1.38,  3.31 }, { -1.09,  3.26 }, { -0.52,  3.51 }, { -0.34,  3.66 }, {  0.22,  3.85 }, {  0.60,  3.71 }, {  0.62,  3.54 }, {  0.45,  3.52 },
	{  0.20,  3.54 }, {  0.11,  3.38 }, { -0.17,  3.48 }, { -0.38,  3.32 }, {  0.22,  3.15 }, {  0.57,  3.43 }, {  0.69,  3.68 }, {  0.68,  4.23 }, { -0.25,  4.20 }, { -1.11,  3.63 },
	{ -1.18,  4.09 }, { -1.51,  4.63 }, { -0.69,  4.62 }, { -1.15,  4.89 }, { -0.71,  4.95 }, { -0.82,  5.14 }, { -0.75,  5.51 }, { -0.57,  5.57 }, { -0.17,  5.29 }, {  0.46,  5.32 },
	{  0.98,  5.65 }, {  1.40,  5.29 }, {  1.63,  4.78 }, {  1.75,  4.98 }, {  1.97,  4.80 }, {  2.11,  4.54 }, {  2.65,  4.45 }, {  2.52,  3.85 }, {  2.15,  4.17 }, {  1.75,  4.17 },
	{  1.40,  3.95 }, {  1.45,  3.62 }, {  1.75,  2.49 }, {  1.66,  2.20 }, {  1.23,  2.17 }, {  1.15,  2.37 }, {  0.89,  2.23 }, {  0.74,  2.52 }, {  0.38,  2.26 }, {  0.18,  1.65 },
	{  0.69,  1.74 }, {  1.15,  1.80 }, {  1.77,  1.71 }, {  1.28,  1.37 }, {  0.80,  1.54 }, {  1.12,  1.82 }, {  2.05,  1.78 }, {  1.95,  2.34 }, {  1.71,  2.60 }, {  1.57,  3.20 },
	{  2.02,  3.06 }, {  2.35,  3.37 }, {  2.18,  3.69 }, {  1.91,  3.82 }, {  1.65,  3.80 }, {  1.58,  3.52 }, {  1.88,  3.32 }, {  1.86,  3.58 }, {  2.06,  3.58 }, {  2.40,  3.34 },
	{  2.54,  3.22 }, {  2.72,  2.82 }, {  3.18,  2.88 }, {  3.20,  3.54 }, {  3.09,  3.88 }, {  3.57,  4.09 }, {  3.31,  4.17 }, {  3.43,  4.45 }, {  3.43,  4.72 }, {  3.26,  4.92 },
	{  3.14,  5.66 }, {  3.03,  6.00 }, {  2.75,  6.20 }, {  2.69,  6.08 }, {  2.58,  6.69 }, {  2.37,  6.89 }, {  2.20,  6.89 }, {  1.98,  7.20 }, {  1.74,  7.32 }, {  1.48,  7.32 },
	{  1.14,  7.23 }, {  1.03,  7.48 }, {  0.92,  7.78 }, {  0.75,  7.46 }, {  0.62,  7.26 }, {  0.32,  7.46 }, { -0.17,  7.57 }, { -0.51,  7.62 },
};

int main()
{
	initgraph(xScreen, yScreen);
	BeginBatchDraw();
	for (auto &it : origin)
	{
		it.r *= 40;
		it.i *= 40;
	}
	vector<complex> initParam((origin.size() / 2) * 2 + 1);
	vector<complex> allCircle(initParam.size());
	// 傅里叶变换，得到圆圈的相位、幅值信息
	DFT(origin, initParam);

	IMAGE buffer(xScreen, yScreen);
	DWORD* pBuffer = GetImageBuffer(&buffer);
	complex start, end, center;
	complex f;
	bool first = true;
	float t = 0.0f;
	while (!_kbhit())
	{
		// 清屏、初始化中间变量
		cleardevice();
		center = { 0.0f, 0.0f };
		f = 0.0f;

		// 获取线条
		setlinecolor(WHITE);
		putimage(0, 0, &buffer);
		int M = initParam.size() / 2;
		for (int k = -M; k <= M; ++k)
		{
			int index = k + M;
			allCircle[index] = initParam[index] * ExpComplex(2 * PI * k * t);
			f = f + allCircle[index];
		}
		if (first)
		{
			start = end = f;
			first = false;
		}
		else
		{
			end = f;
			syLine(start.ToPoint(), end.ToPoint(), YELLOW);
			start = f;
		}
		getimage(&buffer, 0, 0, xScreen, yScreen);
		cleardevice();

		// 绘制圆圈
		putimage(0, 0, &buffer);
		std::sort(allCircle.begin(), allCircle.end(), [](complex a, complex b)->bool {return a.abs() > b.abs(); });
		for (int i = 0; i < allCircle.size(); ++i)
		{
			syLine(center.ToPoint(), (center + allCircle[i]).ToPoint());
			syCircle(center.ToPoint(), allCircle[i].abs(), BLUE);
			center = center + allCircle[i];
		}

		// 每次绘制的 dt，可以控制绘制的快慢，越大越快
		t += 0.0005f;

		// 显示
		FlushBatchDraw();
	}
	EndBatchDraw();
	closegraph();
	return 0;
}