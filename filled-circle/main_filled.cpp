///////////////////////////////////////////////////
// �������ƣ����� Bresenham �㷨�����Բ
// ���뻷����Visual C++ 6.0 / 2013��EasyX 20140321(beta)
// �������ߣ�yangw80 <yw80@qq.com>
// ����޸ģ�2014-7-14
//
#include <graphics.h>
#include <conio.h>

// ���� Bresenham �㷨�����Բ
void FillCircle_Bresenham(int x, int y, int r, COLORREF color)
{
	int tx = 0, ty = r, d = 3 - 2 * r, i;

	while (tx < ty)
	{
		// ��ˮƽ��������(<45��)
		for (i = x - ty; i <= x + ty; i++)
		{
			putpixel(i, y - tx, color);
			if (tx != 0)	// ��ֹˮƽ���ظ�����
				putpixel(i, y + tx, color);
		}

		if (d < 0)			// ȡ����ĵ�
			d += 4 * tx + 6;
		else				// ȡ����ĵ�
		{
			// ��ˮƽ��������(>45��)
			for (i = x - tx; i <= x + tx; i++)
			{
				putpixel(i, y - ty, color);
				putpixel(i, y + ty, color);
			}

			d += 4 * (tx - ty) + 10, ty--;
		}

		tx++;
	}

	if (tx == ty)			// ��ˮƽ��������(=45��)
		for (i = x - ty; i <= x + ty; i++)
		{
			putpixel(i, y - tx, color);
			putpixel(i, y + tx, color);
		}
}

// ������
int main()
{
	// ������ͼ����
	initgraph(640, 480);

	// ���Ի����Բ
	FillCircle_Bresenham(320, 240, 100, GREEN);

	// ��������˳�
	getch();
	closegraph();
	return 0;
}

