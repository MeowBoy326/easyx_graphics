////////////////////////////////////////////
// �������ƣ��򻨳ߣ������򻨹棩ģ�����
// ���뻷����Visual C++ 6.0��EasyX 2011���ݰ�
// �����д��yangw80 <yw80@qq.com>
// �����£�2011-2-26
//
#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#define PI 3.1415926536

void main()
{
	int R;		// �ⲿ��Բ�뾶
	int r;		// �ڲ���Բ�뾶
	int dr;		// �ڲ���Բ�ϵ���ͼ�㵽Բ�ĵľ���

begin:
	// ��ȡ�û�����
	printf("�������ⲿ��Բ�뾶��С�� 240����");
	scanf("%d", &R);
	printf("�������ڲ���Բ�뾶��С�ھ�Բ�뾶����");
	scanf("%d", &r);
	printf("�������ڲ���Բ�ϵ���ͼ�㵽Բ�ĵľ��루С�ڶ�Բ�뾶����");
	scanf("%d", &dr);
	system("cls");

	// ��ִ�д�������С������/��Բ�뾶��
	int m = R, n = r;
	int tmp;
	while (n != 0)
	{
		tmp = m % n;
		m = n;
		n = tmp;
	}
	double maxdegree = r / m * 2 * PI;

	// ��ʼ��
	initgraph(640, 480);	// ������ͼ����
	setorigin(320, 240);	// �趨Բ������

	// ��ͼ
	int x, y;
	for (double degree = 0; degree < maxdegree; degree += 0.01)
	{
		x = (int)(dr * cos(degree*(double(R) / r - 1)) + (R - r) * cos(degree));
		y = (int)(dr * sin(degree*(double(R) / r - 1)) - (R - r) * sin(degree));
		putpixel(x, y, GREEN);
	}
	outtextxy(-320, 220, _T("������ϣ��� ESC �˳��������������¿�ʼ"));

	// ���¿�ʼ�����˳�����
	char c = getch();
	closegraph();
	if (c != 27) goto begin;
}