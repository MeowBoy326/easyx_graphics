////////////////////////////////////////
// �����Ӿ���������صİ���
// ���ߣ�BestAns
// ���뻷����VS2019��EasyX_20211109
// ��д���ڣ�2021-11-29
//
#include <graphics.h> 
#include <conio.h>

const int UNIT = 43;

// ��������Ԫ����
void DrawBlock(int x, int y, bool odd)
{
	int c1, c2;
	if (odd) { c1 = BLACK; c2 = WHITE; }
	else	 { c1 = WHITE; c2 = BLACK; }

	setlinecolor(c1);
	line(x, y, x + UNIT - 1, y);
	line(x + UNIT - 1, y, x + UNIT - 1, y + UNIT - 1);
	setlinecolor(c2);
	line(x, y, x, y + UNIT - 1);
	line(x, y + UNIT - 1, x + UNIT - 1, y + UNIT - 1);

	setfillcolor(c1);
	POINT ps[3] = { x, y, x + 8, y, x, y + 8 };			// ����
	solidpolygon(ps, 3);
	ps[0].x = x + UNIT;		ps[0].y = y;				// ����
	ps[1].x = ps[0].x - 8;	ps[1].y = ps[0].y;
	ps[2].x = ps[0].x;		ps[2].y = ps[0].y + 8;
	solidpolygon(ps, 3);
	ps[0].x = x + UNIT;		ps[0].y = y + UNIT - 1;		// ����
	ps[1].x = ps[0].x - 8;	ps[1].y = ps[0].y;
	ps[2].x = ps[0].x;		ps[2].y = ps[0].y - 8;
	solidpolygon(ps, 3);

	setfillcolor(c2);
	ps[0].x = x;			ps[0].y = y;				// ����
	ps[1].x = ps[0].x + 4;	ps[1].y = ps[0].y + 4;
	ps[2].x = ps[0].x;		ps[2].y = ps[0].y + 8;
	solidpolygon(ps, 3);
	ps[0].x = x + UNIT;		ps[0].y = y + UNIT - 1;		// ����
	ps[1].x = ps[0].x - 8;	ps[1].y = ps[0].y;
	ps[2].x = ps[0].x - 4;	ps[2].y = ps[0].y - 4;
	solidpolygon(ps, 3);
	ps[0].x = x;			ps[0].y = y + UNIT - 1;		// ����
	ps[1].x = ps[0].x + 8;	ps[1].y = ps[0].y;
	ps[2].x = ps[0].x;		ps[2].y = ps[0].y - 8;
	solidpolygon(ps, 3);

	setlinecolor(0x888888);
	line(x, y, x + 3, y + 3);
	line(x + UNIT - 1, y + UNIT - 1, x + UNIT - 4, y + UNIT - 4);
}

int main()
{
	initgraph(774, 774);	// ����ͼ�δ���

	setbkcolor(0xa6a6a6);
	cleardevice();

	//////////////////////
	// ������
	setorigin(387 - UNIT / 2, 387 - UNIT / 2);
	for (int x = -9; x <= 9; x++)
		for (int y = -9; y <= 9; y++)
			DrawBlock(x * UNIT, y * UNIT, (x + y) % 2);
	setorigin(0, 0);

	//////////////////////
	// ������ͼ
	IMAGE img(774, 774);
	SetWorkingImage(&img);
	setbkcolor(BLACK);
	cleardevice();
	// ���ģ�ֻ��Ҫ�����ࣩ
	POINT ps[4] = { 387, 236, 321, 167, 129, 419, 387, 666 };
	setfillcolor(WHITE);
	solidpolygon(ps, 4);
	solidellipse(76, 124, 368, 456);
	SetWorkingImage(NULL);

	//////////////////////
	// ���ݸ���ͼ��������ͼ�а�ɫ�������Ҳ�ߵ�
	DWORD* ref = GetImageBuffer(&img);
	DWORD* bk = GetImageBuffer(NULL);
	int t;
	for (int y = 0; y < 774; y++)
		for (int x = 0; x < 774 / 2; x++)
			if (ref[y * 774 + x] != BLACK)
			{
				t = bk[y * 774 + x];
				bk[y * 774 + x] = bk[y * 774 + 774 - x];
				bk[y * 774 + 774 - x] = t;
			}

	_getch();
	closegraph();

	return 0;
}