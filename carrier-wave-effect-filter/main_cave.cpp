///////////////////////////////////////////////////
// �������ƣ�ͼƬ�˾�ϵ�У������ߵ���Ч��
// ���뻷����Visual C++ 6.0 / 2010��EasyX_20220610
// �������ߣ������� <yw80@qq.com>
// ����޸ģ�2011-7-25
//
#include <graphics.h>
#include <conio.h>
#include <math.h>

#define PI		3.141592654
#define PEN		0x4d8399		// ��ͼ��ɫ(��ɫ)
#define RATIO	GetBValue		// ��ȡ PEN ����Ҫ��ɫ����

IMAGE g_img;					// ������ͼƬ��ȫ�� IMAGE ����


// ����(���ӷ�) (͸�� 0 <= alpha <= 1 ��͸��)
void mixpixel(int x, int y, double alpha)
{
	double f1 = (0xff - RATIO(getpixel(x, y))) / (float)(0xff - RATIO(PEN));
	double f = f1 + alpha;
	if (f > 1)	f = 1;

	COLORREF c = RGB(GetRValue(PEN) + (0xff - GetRValue(PEN)) * (1 - f),
		GetGValue(PEN) + (0xff - GetGValue(PEN)) * (1 - f),
		GetBValue(PEN) + (0xff - GetBValue(PEN)) * (1 - f));

	putpixel(x, y, c);
}


// ����(֧�ָ��� y ����)
void mypixel(int x, double y)
{
	int y1 = (int)floor(y);
	int y2 = y1 + 1;

	mixpixel(x, y1, y2 - y);
	mixpixel(x, y2, y - y1);
}


// ��������
void myline(int x, double y)
{
	// ��ȡ�Ҷ�ͼƬָ��λ�õ���ɫƽ��ֵ
	SetWorkingImage(&g_img);
	int sum = 0;
	int count = 0;
	for (int i = (int)(y - 2 + 0.5); i <= (int)(y + 2 + 0.5); i++)
		if (i >= 0)
		{
			count++;
			sum += (0xff & getpixel(x, i));
		}
	if (count > 0)
		sum = (int)(sum / (float)count + 0.5);
	SetWorkingImage(NULL);

	// ���ݻ�ȡ������ɫֵ������Ч��
	if (sum >= 192)
		mypixel(x, y);
	else
	{
		int y1 = (int)y;
		sum += (int)(64 * (1 - (y - y1)));
		mixpixel(x, y1, (1 - (y - y1)));
		while (sum < 192)
		{
			sum += 64;
			mixpixel(x, ++y1, 1);
		}
		mixpixel(x, ++y1, 1 - (sum - 191) / 64.0);
	}
}


// ������
int main()
{
	// ��ʼ��
	initgraph(640, 640);				// ������ͼ����
	loadimage(&g_img, _T("c:\\test.jpg"));;	// ����ͼƬ������Ϊ 640 x 480��
	setbkcolor(0xffffff);
	cleardevice();

	// ��ͼƬת��Ϊ�Ҷ�ͼƬ
	DWORD* buf = GetImageBuffer(&g_img);
	for (int i = 0; i < 640 * 640; i++)
	{
		buf[i] = BGR(RGBtoGRAY(BGR(buf[i])));
	}

	// �������������ߣ����ڴ˻����ϵ���ͼ��
	for (int x = 0; x < 640; x++)
	{
		double y1 = sin(x / 30.0 / PI) * 20.8;
		for (double y = y1 - 20; y < 640; y += 5)
			myline(x, y);
	}

	// ��������˳�
	_getch();
	closegraph();
	return 0;
}