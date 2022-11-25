///////////////////////////////////////////////////
// �������ƣ��Ӿ��������3
// ���뻷����Visual C++ 6.0 / 2010��EasyX_20210730
// �������ߣ�yangw80 <yw80@qq.com>
// ����޸ģ�2014-7-14
//
#include <graphics.h>
#include <conio.h>


// ����ص�
void (*callback)(int x, int y);


// Բ�е�ÿ����(�ص�����)
void CirclePoints(int x, int y)
{
	if (x < y)
	{
		COLORREF c1 = getpixel(x, y);
		COLORREF c2 = getpixel(y, x);
		putpixel(x, y, c2);
		putpixel(y, x, c1);
	}
}


// ���� Bresenham �㷨�����Բ
// �޸��� www.easyx.cn, yw80@qq.com
void FillCircle_Bresenham(int x, int y, int r)
{
	int tx = 0, ty = r, d = 3 - 2 * r, i;

	while (tx < ty)
	{
		// ��ˮƽ��������(<45��)
		for (i = x - ty; i <= x + ty; i++)
		{
			CirclePoints(i, y - tx);
			if (tx != 0)	// ��ֹˮƽ���ظ�����
				CirclePoints(i, y + tx);
		}

		if (d < 0)			// ȡ����ĵ�
			d += 4 * tx + 6;
		else				// ȡ����ĵ�
		{
			// ��ˮƽ��������(>45��)
			for (i = x - tx; i <= x + tx; i++)
			{
				CirclePoints(i, y - ty);
				CirclePoints(i, y + ty);
			}

			d += 4 * (tx - ty) + 10, ty--;
		}

		tx++;
	}

	if (tx == ty)			// ��ˮƽ��������(=45��)
		for (i = x - ty; i <= x + ty; i++)
		{
			CirclePoints(i, y - tx);
			CirclePoints(i, y + tx);
		}
}


// ������
int main()
{
	// ������ͼ����
	initgraph(640, 480);
	setbkcolor(LIGHTGRAY);
	cleardevice();
	setorigin(320, 240);

	// ������ĺڰ׿�
	setlinecolor(BLACK);
	rectangle(-201, -201, 200, 200);
	for (int x = 0; x < 10; x++)
		for (int y = 0; y < 40; y++)
		{
			setfillcolor((((x + y) % 2) == 1) ? BLACK : WHITE);
			solidrectangle(x * 40 - 200, y * 10 - 200, x * 40 + 39 - 200, y * 10 + 9 - 200);
		}

	// ���Բ�ں���ȡ��
	FillCircle_Bresenham(0, 0, 120);

	// ��������˳�
	_getch();
	closegraph();
	return 0;
}