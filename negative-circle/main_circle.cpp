///////////////////////////////////////////////////
// �������ƣ����������㷨��Բ
// ���뻷����Visual C++ 6.0 / 2010��EasyX_20210115
// �������ߣ�YangW <yw80@qq.com>
// ����޸ģ�2011-5-3
//
#include <graphics.h>
#include <conio.h>

// ������Բ��
void Circle_PN(int x, int y, int r, int color)
{
	int tx = 0, ty = r, f = 0;

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

		if (f <= 0)
			f = f + 2 * tx + 1, tx++;
		else
			f = f - 2 * ty + 1, ty--;
	}
}

// ������
int main()
{
	initgraph(640, 480);

	// ���Ի�Բ
	Circle_PN(320, 240, 200, RED);
	Circle_PN(320, 240, 101, RED);

	// ��������˳�
	_getch();
	closegraph();
	return 0;
}