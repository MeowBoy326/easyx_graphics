/////////////////////////////////////////////////////////
// 程序名称：彩色图片转换为灰阶图片
// 编译环境：Visual C++ 6.0 / 2010，EasyX 20130322(beta)
// 作    者：krissi <zh@easyx.cn>
// 最后修改：2013-1-19
//
#include <graphics.h>
#include <conio.h>


// 彩色图像转换为灰度图像
void  ColorToGray(IMAGE *pimg)
{
	DWORD *p = GetImageBuffer(pimg);	// 获取显示缓冲区指针
	COLORREF c;

	// 逐个像素点读取计算
	for (int i = pimg->getwidth() * pimg->getheight() - 1; i >= 0; i--)
	{
		c = BGR(p[i]);
		c = (GetRValue(c) * 299 + GetGValue(c) * 587 + GetBValue(c) * 114 + 500) / 1000;
		p[i] = RGB(c, c, c);	// 由于是灰度值，无需再执行 BGR 转换
	}
}


// 主函数
int main()
{
	// 初始化绘图环境
	initgraph(640, 640);
	// 获取图像
	IMAGE img;
	loadimage(&img, _T("c:\\test.jpg"));
	// 显示原始图像
	putimage(0, 0, &img);
	// 按任意键转换为灰度图像
	_getch();
	// 处理图像为灰度
	ColorToGray(&img);
	// 显示处理后的图像
	putimage(0, 0, &img);
	// 关闭绘图环境
	_getch();
	closegraph();
	return 0;
}