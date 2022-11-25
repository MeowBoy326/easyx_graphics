///////////////////////////////////////////////////
// �������ƣ����� DDA �㷨������б�ʵ�ֱ��
// ���뻷����Visual C++ 6.0 / 2010��EasyX 2011���ݰ�
// �������ߣ�yangw80 <yw80@qq.com>
// ����޸ģ�2011-4-26
//
#include <graphics.h>
#include <conio.h>

// ��������
int Round(float x)
{
	return (int)(x < 0 ? x - 0.5 : x + 0.5);
}

// ʹ�� DDA �㷨������б�ʵ�ֱ�ߣ�������ʼ�㣬��������ֹ�㣩
void Line_DDA(int x1, int y1, int x2, int y2, int color)
{
	float x, y;		// ��ǰ�����
	float cx, cy;	// x��y �����ϵ�����

	int steps = abs(x2 - x1) > abs(y2 - y1) ? abs(x2 - x1) : abs(y2 - y1);

	x = (float)x1;
	y = (float)y1;
	cx = (float)(x2 - x1) / steps;
	cy = (float)(y2 - y1) / steps;

	for (int i = 0; i < steps; i++)
	{
		putpixel(Round(x), Round(y), color);	// ������ (x, y) ����һ�� color ��ɫ�ĵ�
		x += cx;
		y += cy;
	}
}

// ������
int main()
{
	initgraph(640, 480);

	// ���Ի���
	Line_DDA(100, 1, 1, 478, GREEN);
	Line_DDA(1, 478, 638, 1, GREEN);

	// ��������˳�
	_getch();
	closegraph();
	return 0;
}