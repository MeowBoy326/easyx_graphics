///////////////////////////////////////////////////
// �������ƣ������е��㷨��Բ
// ���뻷����Visual C++ 6.0 / 2010��EasyX_20210730
// �������ߣ�YangW <yw80@qq.com>
// ����޸ģ�2011-4-29
//
#include <graphics.h>
#include <conio.h>

// �е㻭Բ��
void Circle_Midpoint(int x, int y, int r, int color)
{
	int tx = 0, ty = r, d = 1 - r;

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

		if (d < 0)
			d += 2 * tx + 3;
		else
			d += 2 * (tx - ty) + 5, ty--;

		tx++;
	}
}

// ������
int main()
{
	initgraph(640, 480);

	// ���Ի�Բ
	Circle_Midpoint(320, 240, 200, RED);
	Circle_Midpoint(320, 240, 101, RED);

	// ��������˳�
	_getch();
	closegraph();
	return 0;
}