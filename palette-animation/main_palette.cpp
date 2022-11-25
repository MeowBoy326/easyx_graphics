///////////////////////////////////////////////////
// �������ƣ����� EasyX �ĵ�ɫ�嶯������
// ���뻷����VC6.0 / VC2010��EasyX 2011���ݰ�
// �������ߣ�krissi <zh@easyx.cn>
// ����޸ģ�2012-1-4
//
#include <graphics.h>
#include <conio.h>
#include <math.h>

#define	WIDTH	640
#define	HEIGHT	480
#define	PI		3.1415926535

HPALETTE	g_hPal, g_hOldPal;	// ��ɫ����
LOGPALETTE*	g_pLOGPAL;			// ��ɫ����Ϣ�ṹ��
HDC			g_hDC;				// EasyX ���ڵ� DC ���


// ��ʼ��
void Init()
{
	initgraph(WIDTH, HEIGHT);	// ������ͼ����
	g_hDC = GetImageHDC();		// ��ȡ��ͼ���ڵľ��

	// �趨����ɫϵ
	int r = 216;
	int g = 0;
	int b = 0;

	///////////////////
	// ��ʼ����ɫ��

	// Ϊ��ɫ��ṹ������ڴ�(�õ�ɫ�庬�� 32 ����ɫ)
	// ��ʵ�ʶ��ĸ��ֽ��������� palVersion �� palNumEntries ������Ա��
	// ��� MSDN �� LOGPALETTE �Ķ���
	g_pLOGPAL = (LOGPALETTE*)new PALETTEENTRY[33];
	g_pLOGPAL->palVersion = 0x300;
	g_pLOGPAL->palNumEntries = 32;

	for (int i = 0; i < 32; i++)
	{
		g_pLOGPAL->palPalEntry[i].peRed = BYTE(r * sin(PI * i / 32));
		g_pLOGPAL->palPalEntry[i].peGreen = BYTE(g * sin(PI * i / 32));
		g_pLOGPAL->palPalEntry[i].peBlue = BYTE(b * sin(PI * i / 32));
		g_pLOGPAL->palPalEntry[i].peFlags = PC_RESERVED;
	}

	g_hPal = CreatePalette(g_pLOGPAL);					// ������ɫ��
	g_hOldPal = SelectPalette(g_hDC, g_hPal, false);	// ѡ���ɫ��
}


// �ı��ɫ��
void ChangePal()
{
	// ʹ��ɫ�����ɫѭ������
	PALETTEENTRY t = g_pLOGPAL->palPalEntry[0];
	for (int i = 0; i < 31; i++)
		g_pLOGPAL->palPalEntry[i] = g_pLOGPAL->palPalEntry[i + 1];
	g_pLOGPAL->palPalEntry[31] = t;

	// ʹ��ɫ����޸���Ч
	AnimatePalette(g_hPal, 0, 32, g_pLOGPAL->palPalEntry);
	RealizePalette(g_hDC);
}


// ��ͼ��
void Draw()
{
	HBRUSH hBrush;
	int x1, y1;
	COLORREF c;

	for (int y = 0; y < 64; y++)
		for (int x = 0; x < 64; x++)
		{
			RECT rt = { x * WIDTH / 64 + 1,
				y * HEIGHT / 64 + 1,
				(x + 1) * WIDTH / 64,
				(y + 1) * HEIGHT / 64 };

			x1 = x > 31 ? 63 - x : x;
			y1 = y > 31 ? 63 - y : y;
			c = PALETTEINDEX(min(x1, y1));

			hBrush = CreateSolidBrush(c);
			FillRect(g_hDC, &rt, hBrush);
			DeleteObject(hBrush);
		}
}


// �˳�
void Quit()
{
	SelectPalette(g_hDC, g_hOldPal, false);
	DeleteObject(g_hPal);

	delete[] g_pLOGPAL;

	closegraph();
}


// ������
void main()
{
	Init();					// ��ʼ��

	while (!_kbhit())		// ��������˳�
	{
		ChangePal();		// �ı��ɫ��
		Draw();				// ��ͼ��(ÿ�λ��Ķ�һ������̬ͼ������Ϊ��ɫ��ĸı�)
		FlushBatchDraw();	// ʹ GDI ��ͼ������Ч
		Sleep(33);			// ��ʱ
	}

	Quit();					// �˳�
}