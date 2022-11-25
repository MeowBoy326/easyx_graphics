///////////////////////////////////////////////////
// 程序名称：计算扇形的最小包围矩形
// 编译环境：Visual C++ 6.0 / 2019，EasyX 20210730
// 作　　者：yangw80 <yw80@qq.com>
// 最后修改：2013-11-14
//
#include <graphics.h>
#include <math.h>

const double PI = 3.1415926536;

// 求扇形的最小包围矩形
// 参数：
//	x, y:   圆心
//	r:      半径
//	a1, a2: 起始角、终止角的弧度
RECT GetPieMinimumRect(int x, int y, int r, double a1, double a2)
{
	// 定义变量
	int i;
	double a;

	// 规范化弧度，确保起始角小于终止角
	if (a1 > a2)
		a2 += PI * 2;

	// 计算扇形区域的最小包围矩形
	// 方法：获得 7 个点的最大最小值，得到最小包围矩形
	// 7 个点包括：圆心、圆弧两端、圆弧与坐标轴的交点(最多 4 个)

	// 第一步：初始化 7 个点
	POINT pt[7];
	pt[0].x = x;							pt[0].y = y;
	pt[1].x = int(x + r * cos(a1) + 0.5);	pt[1].y = int(y - r * sin(a1) + 0.5);
	pt[2].x = int(x + r * cos(a2) + 0.5);	pt[2].y = int(y - r * sin(a2) + 0.5);

	for (a = ceil(a1 * 4 / (2 * PI)) * (PI / 2), i = 3; a < a2; a += PI / 2, i++)
	{
		pt[i].x = int(x + r * cos(a) + 0.5);
		pt[i].y = int(y - r * sin(a) + 0.5);
	}

	// 第二步：获取 7 个点的最大最小值，得到最小包围矩形
	i--;
	RECT rect = { pt[i].x, pt[i].y, pt[i].x, pt[i].y };

	for (--i; i >= 0; i--)
	{
		if (pt[i].x < rect.left)	rect.left = pt[i].x;
		if (pt[i].x > rect.right)	rect.right = pt[i].x;
		if (pt[i].y < rect.top)		rect.top = pt[i].y;
		if (pt[i].y > rect.bottom)	rect.bottom = pt[i].y;
	}

	// 返回最小包围矩形
	return rect;
}

// 获取指定坐标的角度
double GetAngle(int x, int y)
{
	int dx = x - 320;
	int dy = 240 - y;

	double a;

	if (dx == 0 && dy == 0)
		a = 0;
	else if (dx != 0 && dy != 0)
		a = atan((double)(dy) / dx);
	else if (dx == 0)
		a = (dy > 0) ? PI / 2 : PI * 3 / 2;
	else
		a = 0;
	if (dx < 0)	a += PI;
	if (a < 0)	a += PI * 2;

	return a;
}

// 绘制扇形及最小包围矩形
void Draw(double a1, double a2, int r)
{
	cleardevice();

	// 绘制扇形
	setlinecolor(GREEN);
	setfillcolor(GREEN);
	setfillstyle(BS_HATCHED, HS_BDIAGONAL);
	fillpie(320 - 100, 240 - 100, 320 + 100, 240 + 100, a1, a2);

	// 绘制矩形
	RECT rect = GetPieMinimumRect(320, 240, r, a1, a2);
	setlinecolor(YELLOW);
	rectangle(rect.left, rect.top, rect.right, rect.bottom);
}

// 主程序
int main()
{
	// 创建绘图窗口
	initgraph(640, 480);

	// 初始化
	double a1 = 0;			// 扇形起始角的弧度
	double a2 = PI * 3 / 4;	// 扇形终止角的弧度
	int r = 100;			// 扇形半径

	Draw(a1, a2, r);		// 绘制初始状态
	BeginBatchDraw();		// 启用批量绘图防止闪烁

	ExMessage msg;

	do
	{
		// 获取鼠标消息
		msg = getmessage();

		if (msg.lbutton)				// 左键按下调整终止角的角度
		{
			// 计算鼠标角度
			if (msg.shift)				// 按下 Shift 键调整起始角的角度
				a1 = GetAngle(msg.x, msg.y);
			else
				a2 = GetAngle(msg.x, msg.y);

			// 绘制扇形和最小包围矩形
			Draw(a1, a2, r);

			// 刷新显示
			FlushBatchDraw();
		}
	} while (msg.message != WM_RBUTTONUP);	// 按鼠标右键退出

	// 关闭图形窗口
	EndBatchDraw();
	closegraph();
	return 0;
}