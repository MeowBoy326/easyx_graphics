/////////////////////////////////////////////////////////////////////////
// �������ƣ���ͼƬ����ģ������
// ���뻷����Visual C++ 6.0 ~ 2017��EasyX 20180727(beta)
// �������ߣ�krissi <zh@easyx.cn>
// �������ڣ�2013-1-19
// ����޸ģ�2018-10-5
//
#include <graphics.h>
#include <conio.h>				

// ��ͼƬ����ģ������
void Blur(IMAGE *pimg)
{
	DWORD*	pMem = GetImageBuffer(pimg);

	int	r, g, b;
	int m;
	int	num = 0;
	int	width = pimg->getwidth();
	int	height = pimg->getheight();
	int step = width - 1, f, t;


	// ���� 9 ����ϵ��
	int	cell[9] = { -(width + 1), -1, width - 1, -width, 0, width, -(width - 1), 1, width + 1 };

	// ������ص��ȡ����
	for (int i = width * height - 1; i >= 0; i--)
	{
		// ���ñ���
		r = g = b = 0;
		m = 9;

		// ��������λ�ã�������Χ���ӵļ��㷶Χ
		if (step == width - 1)
			t = 5, m = 6;
		else
			t = 8;

		if (step == 0)
			f = 3, m = 6, step = width;
		else
			f = 0;

		step--;

		// �ۼ���Χ���ӵ���ɫֵ
		for (int n = f; n <= t; n++)
		{
			// λ�ö�λ
			num = i + cell[n];

			// �ж�λ��ֵ�Ƿ�Խ��
			if (num < 0 || num >= width * height)
				m--;						// ͳ��Խ��������
			else
			{
				// �ۼ���ɫֵ
				r += GetRValue(pMem[num]);
				g += GetGValue(pMem[num]);
				b += GetBValue(pMem[num]);
			}
		}

		// ��ƽ��ֵ��ֵ������
		pMem[i] = RGB(r / m, g / m, b / m);
	}
}

// ������
void main()
{
	// ��ʼ����ͼ����
	initgraph(640, 640);

	// ��ȡͼ��
	IMAGE img;
	loadimage(&img, _T("c:\\test.jpg"));

	// ��ʾԭʼͼ��
	putimage(0, 0, &img);

	// ��ģ��
	for (int m = 0; m < 100; m++)
	{
		Blur(&img);
		// ��ʾ������ͼ��
		putimage(320, 0, &img);
		Sleep(20);
	}

	// ������رջ�ͼ����
	_getch();
	closegraph();
}