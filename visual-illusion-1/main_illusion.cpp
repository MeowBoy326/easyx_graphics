///////////////////////////////////////////////////
// �������ƣ��Ӿ��������1
// ���뻷����Visual C++ 6.0��EasyX 2013˪����
// �������ߣ�yangw80 <yw80@qq.com>
// ����޸ģ�2013-12-16
//
#include <graphics.h>
#include <conio.h>

// ���峣��
#define	UNIT		15
#define OFFSET_X	122
#define OFFSET_Y	23

// ��ÿ��С��Ԫ
void DrawUnit(int x, int y, int shape)
{
	// ������ɫ
	static COLORREF c[4] = {0x0000ff, 0x0077ff, 0x00ddff, 0x0077ff};

	// ��������ɫ�ǿ�
	setfillcolor(WHITE);
	switch(shape)
	{
		case 0:
			solidrectangle(x, y, x + UNIT - 1, y + UNIT - 1);
			break;
		case 1:
			solidrectangle(x, y + UNIT / 2, x + UNIT / 2, y + UNIT - 1);
			break;
		case 3:
			solidrectangle(x + UNIT / 2, y, x + UNIT - 1, y + UNIT / 2);
			break;
	}

	// ����ɫ�ǿ�
	setfillcolor(c[shape]);
	if (shape % 2 == 0)
	{
		solidrectangle(x, y + UNIT / 2, x + UNIT / 2, y + UNIT - 1);
		solidrectangle(x + UNIT / 2, y, x + UNIT - 1, y + UNIT / 2);
	}
	else
	{
		solidrectangle(x, y, x + UNIT / 2, y + UNIT / 2);
		solidrectangle(x + UNIT / 2, y + UNIT / 2, x + UNIT - 1, y + UNIT - 1);
	}

	// ��Բ�Ǿ���
	solidroundrect(x, y, x + UNIT - 1, y + UNIT - 1, 9, 9);
}

// ������
void main()
{
	// ������ͼ����
	initgraph(800, 600);
	// ��������ԭ��
	setorigin(OFFSET_X, OFFSET_Y);

	int x, y;

	// ����������ɫ�߿�
	setbkcolor(WHITE);
	cleardevice();
	setfillcolor(0xf3f3f3);
	solidrectangle(-8, -8, UNIT * 37 + 8 - 1, UNIT * 37 + 8 - 1);
	setfillcolor(BLACK);
	solidrectangle(0, 0, UNIT * 37 - 1, UNIT * 37 - 1);

	// ���ɹ��ɵ�ͼ��
	for (y = 0; y < 37; y++)
	{
		int shape = (4 - y % 4) & 3;
		for (x = 0; x < 37; x++)
		{
			DrawUnit(x * UNIT, y * UNIT, shape++);
			shape &= 0x3;
		}
	}

	// ���벿�����ҵߵ�
	COLORREF c1, c2;
	for (y = 8 * UNIT + UNIT / 2; y < (37 - 8) * UNIT - UNIT / 2; y++)
		for (x = 8 * UNIT + UNIT / 2; x < 37 * UNIT / 2; x++)
		{
			c1 = getpixel(x, y);
			c2 = getpixel(37 * UNIT - x - 1, y);
			putpixel(x, y, c2);
			putpixel(37 * UNIT - x - 1, y, c1);
		}

	// ��������˳�
	getch();
	closegraph();
}