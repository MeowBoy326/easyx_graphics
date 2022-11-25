///////////////////////////////////////////////////
// �������ƣ����� Bresenham �㷨��Բ
// ���뻷����Visual C++ 6.0 / 2010��EasyX_20210730
// �������ߣ�YangW <yw80@qq.com>
// ����޸ģ�2011-5-3
//
#include <graphics.h>
#include <conio.h>

// ʹ�� Bresenham ��Բ��
void Circle_Bresenham(int x, int y, int r, int color)
{
	int tx = 0, ty = r, d = 3 - 2 * r;

	while (tx <= ty)
	{
		// ����Բ�İ˷ֶԳ��Ի���
		putpixel(x + tx, y + ty, color);
		putpixel(x + tx, y - ty, color);
		putpixel(x - tx, y + ty, color);
		putpixel(x - tx, y - ty, color);
		putpixel(x + ty, y + tx, color);
		putpixel(x + ty, y - tx, color);
		putpixel(x - ty, y + tx, color);
		putpixel(x - ty, y - tx, color);

		if (d < 0)		// ȡ����ĵ�
			d += 4 * tx + 6;
		else			// ȡ����ĵ�
			d += 4 * (tx - ty) + 10, ty--;

		tx++;
	}
}

// ������
int main()
{
	initgraph(640, 480);

	// ���Ի�Բ
	Circle_Bresenham(320, 240, 200, RED);
	Circle_Bresenham(320, 240, 101, RED);

	// ��������˳�
	_getch();
	closegraph();
	return 0;
}
