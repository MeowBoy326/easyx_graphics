///////////////////////////////////////////////////
// �������ƣ������˶��ĵ�
// ���뻷����Visual C++ 6.0 / 2010��EasyX_20200727
// �������ߣ�yangw80 <yw80@qq.com>
// ����޸ģ�2011-5-3
//
#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#define AMOUNT 64

// ȫ��ģ������
// ��Ϊ�˼򻯷������ú�����ȥ����Ļ��һ�к����һ�еĴ���
void Blur(DWORD* pMem)
{
	for (int i = 640; i < 640 * 479; i++)
	{
		pMem[i] = RGB(
			(GetRValue(pMem[i]) + GetRValue(pMem[i - 640]) + GetRValue(pMem[i - 1]) + GetRValue(pMem[i + 1]) + GetRValue(pMem[i + 640])) / 5,
			(GetGValue(pMem[i]) + GetGValue(pMem[i - 640]) + GetGValue(pMem[i - 1]) + GetGValue(pMem[i + 1]) + GetGValue(pMem[i + 640])) / 5,
			(GetBValue(pMem[i]) + GetBValue(pMem[i - 640]) + GetBValue(pMem[i - 1]) + GetBValue(pMem[i + 1]) + GetBValue(pMem[i + 640])) / 5);
	}
}

// ��Ľṹ
struct SPOT
{
	int x, y;
	int targetx, targety;
	int dx, dy;
	COLORREF color;
};

// ��ȷ��ʱ����(���Ծ�ȷ�� 1ms������ ��1ms)
// ��ԭ���� www.easyx.cn ��������ϸ���ͣ�
void HpSleep(int ms)
{
	static clock_t oldclock = clock();		// ��̬��������¼��һ�� tick

	oldclock += ms * CLOCKS_PER_SEC / 1000;	// ���� tick

	if (clock() > oldclock)					// ����Ѿ���ʱ��������ʱ
		oldclock = clock();
	else
		while (clock() < oldclock)			// ��ʱ
			Sleep(1);						// �ͷ� CPU ����Ȩ������ CPU ռ����
}

// ������
int main()
{
	// ��ʼ��
	initgraph(640, 480);			// ������ͼ����
	srand((unsigned)time(NULL));	// �����������
	DWORD* pMem = GetImageBuffer();	// ��ȡ��ʾ��������ַ

	// �������е�
	SPOT spots[AMOUNT];

	// ��ʼ��ÿ����
	for (int i = 0; i < AMOUNT; i++)
	{
		spots[i].x = spots[i].targetx = rand() % 600 + 20;
		spots[i].y = spots[i].targety = rand() % 440 + 20;
		spots[i].dx = rand() % 40 - 20;
		spots[i].dy = (int)sqrt((float)(400 - spots[i].dx * spots[i].dx)) * ((rand() % 2) * 2 - 1);
		spots[i].color = HSLtoRGB((float)(rand() % 360), 1.0, 0.5);
	}

	while (!_kbhit())
	{
		for (int i = 0; i < AMOUNT; i++)
		{
			setcolor(spots[i].color);
			moveto(spots[i].x, spots[i].y);

			spots[i].targetx += spots[i].dx;
			spots[i].targety += spots[i].dy;

			// �ж��Ƿ�Խ�磬�Լ�Խ�紦��
			if (spots[i].targetx <= 0)
			{
				spots[i].dx = rand() % 20;
				spots[i].dy = (int)sqrt((float)(400 - spots[i].dx * spots[i].dx)) * ((rand() % 2) * 2 - 1);
			}
			else if (spots[i].targetx >= 639)
			{
				spots[i].dx = -rand() % 20;
				spots[i].dy = (int)sqrt((float)(400 - spots[i].dx * spots[i].dx)) * ((rand() % 2) * 2 - 1);
			}

			if (spots[i].targety <= 0)
			{
				spots[i].dx = rand() % 40 - 20;
				spots[i].dy = (int)sqrt((float)(400 - spots[i].dx * spots[i].dx));
			}
			else if (spots[i].targety >= 479)
			{
				spots[i].dx = rand() % 40 - 20;
				spots[i].dy = -(int)sqrt((float)(400 - spots[i].dx * spots[i].dx));
			}

			// δԽ��ʱ���� 10% �ĸ��ʸı����з���
			if (rand() % 10 < 1)
			{
				spots[i].dx = rand() % 40 - 20;
				spots[i].dy = (int)sqrt((float)(400 - spots[i].dx * spots[i].dx)) * ((rand() % 2) * 2 - 1);
			}

			// �����µ����꣬����
			spots[i].x += (int)((spots[i].targetx - spots[i].x) * 0.1);
			spots[i].y += (int)((spots[i].targety - spots[i].y) * 0.1);
			lineto(spots[i].x, spots[i].y);
		}

		// ȫ��ģ������
		Blur(pMem);

		// ��ʱ
		HpSleep(33);
	}

	// ��������˳�
	closegraph();
	return 0;
}