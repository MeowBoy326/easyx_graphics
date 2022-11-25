// �������ƣ�����ѧ - Julia Set (�����Ǽ�)
// ���뻷����Visual C++ 6.0��EasyX_20200902
// �����£�2010-9-9
//
#include <graphics.h>
#include <conio.h>

/////////////////////////////////////////////////
// ���帴�����ˡ�������
/////////////////////////////////////////////////

// ���帴��
struct COMPLEX
{
	double re;
	double im;
};

// ���帴�����ˡ�����
COMPLEX operator * (COMPLEX a, COMPLEX b)
{
	COMPLEX c;
	c.re = a.re * b.re - a.im * b.im;
	c.im = a.im * b.re + a.re * b.im;
	return c;
}

// ���帴�����ӡ�����
COMPLEX operator + (COMPLEX a, COMPLEX b)
{
	COMPLEX c;
	c.re = a.re + b.re;
	c.im = a.im + b.im;
	return c;
}


/////////////////////////////////////////////////
// ������
/////////////////////////////////////////////////
int main()
{
	// ��ʼ����ͼ����
	initgraph(640, 480);

	/////////////////////////////////////////////////
	// ���� Julia Set (�����Ǽ�)
	/////////////////////////////////////////////////
	COMPLEX z, c;
	c.re = -0.75, c.im = 0;	// ���õ�����ֵ

	int x, y, k;			// ����ѭ������
	for (x = 0; x < 640; x++)
	{
		for (y = 0; y < 480; y++)
		{
			z.re = -1.6 + 3.2 * (x / 640.0);
			z.im = -1.2 + 2.4 * (y / 480.0);
			for (k = 0; k < 180; k++)
			{
				if (z.re * z.re + z.im * z.im > 4.0)	break;
				z = z * z + c;
			}
			putpixel(x, y, (k >= 180) ? 0 : HSLtoRGB((float)((k << 5) % 360), 1.0, 0.5));
		}
	}

	// ��������˳�
	getch();
	closegraph();
	return 0;
}