///////////////////////////////////////////////////
// �������ƣ����� Bresenham �㷨������б�ʵ�ֱ��
// ���뻷����Visual C++ 6.0 / 2010��EasyX 2011���ݰ�
// �������ߣ�yangw80 <yw80@qq.com>
// �������ڣ�2011-4-26
//
#include <graphics.h>
#include <conio.h>

// ʹ�� Bresenham �㷨������б�ʵ�ֱ�ߣ�������ʼ�㣬��������ֹ�㣩
void Line_Bresenham(int x1, int y1, int x2, int y2, int color)
{
	int x = x1;
	int y = y1;
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int s1 = x2 > x1 ? 1 : -1;
	int s2 = y2 > y1 ? 1 : -1;

	bool interchange = false;	// Ĭ�ϲ����� dx��dy
	if (dy > dx)				// ��б�ʴ��� 1 ʱ��dx��dy ����
	{
		int temp = dx;
		dx = dy;
		dy = temp;
		interchange = true;
	}

	int p = 2 * dy - dx;
	for (int i = 0; i < dx; i++)
	{
		putpixel(x, y, color);
		if (p >= 0)
		{
			if (!interchange)		// ��б�� < 1 ʱ��ѡȡ�������ص�
				y += s2;
			else					// ��б�� > 1 ʱ��ѡȡ�������ص�
				x += s1;
			p -= 2 * dx;
		}
		if (!interchange)
			x += s1;				// ��б�� < 1 ʱ��ѡȡ x Ϊ����
		else
			y += s2;				// ��б�� > 1 ʱ��ѡȡ y Ϊ����
		p += 2 * dy;
	}
}

// ������
int main()
{
	initgraph(640, 480);

	// ���Ի���
	Line_Bresenham(100, 1, 1, 478, GREEN);
	Line_Bresenham(1, 478, 638, 1, GREEN);

	// ��������˳�
	_getch();
	closegraph();
	return 0;
}