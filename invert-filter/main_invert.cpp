/////////////////////////////////////////////////////////
// 程序名称：底片效果
// 编译环境：Visual C++ 6.0 / 2010，EasyX_20200727
// 作    者：krissi <zh@easyx.cn>
// 最后修改：2013-1-20
//
#include <graphics.h>
#include <conio.h>

// 底片效果
void ColorInvert(IMAGE *pimg)
{
	// 获取指向显示缓冲区的指针
	DWORD* pMem = GetImageBuffer(pimg);

	// 直接对显示缓冲区赋值
	for (int i = pimg->getwidth() * pimg->getheight() - 1; i >= 0; i--)
		pMem[i] = (~pMem[i]) & 0x00FFFFFF;
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
	// 任意键执行
	_getch();
	// 底片效果
	ColorInvert(&img);
	// 显示处理后的图像
	putimage(0, 0, &img);
	// 任意键关闭绘图环境
	_getch();
	closegraph();
}