// �������ƣ�Բ����϶��ɵ�����ͼ��
// ���뻷����Visual C++ 6.0��EasyX 2011���ݰ�
// �����£�2010-10-28
//
#include <graphics.h>
#include <conio.h>
#include <math.h>

#define	PI	3.1415926536

void main()
{
	int x, y, y1, r = 50, r1;

	// ��ʼ��ͼ��ģʽ
	initgraph(640, 480);
	// ����ԭ��Ϊ��Ļ����
	setorigin(320, 240);
	// ���û�ͼ��ɫΪ��ɫ
	setcolor(RED);

	// ����ѧ�������ö��Բ������γ�����ͼ��
	y1 = 240 - r;
	for (double a = 0; a < 2 * PI; a += PI / 18)
	{
		x = (int)(r * cos(a));
		y = (int)(r * sin(a));
		r1 = (int)(sqrt((double)(x * x + (y + r) * (y + r))));
		circle(x, y, r1);
	}

	getch();
	closegraph();
}