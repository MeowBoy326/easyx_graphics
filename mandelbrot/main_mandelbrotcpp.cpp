// �������ƣ�����ѧ - Mandelbrot Set (���²����ؼ�)
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
	// ���� Mandelbrot Set (���²����ؼ�)
	/////////////////////////////////////////////////
	COMPLEX z, c;
	int x, y, k;	// ����ѭ������
	for (x = 0; x < 640; x++)
	{
		c.re = -2.1 + (1.1 - -2.1) * (x / 640.0);
		for (y = 0; y < 480; y++)
		{
			c.im = -1.2 + (1.2 - -1.2) * (y / 480.0);
			z.re = z.im = 0;
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

