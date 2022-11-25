///////////////////////////////////////////////////
// �������ƣ����С���ڷ����ڵ���ײ�˶�
// ���뻷����Visual C++ 6.0��EasyX 2013������
// �������ߣ��ɿ� 
// ����޸ģ�2014-03-18
//
#include <graphics.h>
#include <conio.h>
#include <math.h>
#define	 XN	640
#define	 YN	480						// ����ͼ�δ��ڵĴ�С
#define	 N	40						// ������ĸ�������� 90 ��
#define	 V	20						// ��������ٶ�

// ����һ����
void Ball(int x, int y)
{
	fillcircle(x, YN - y, 20);		// ת���ɳ��õ�����
}

// �ж��Ƿ�����άƽ��С����ȫ������ײ(�ٶȽϴ�)
// (���ٶȺ�Сʱ�������ӡ���Ϊ�����Ľ����Ϊ��������λ������ʵ���С���ܿ�˥���� 0)
int PerfectElasticCollision(float v1[2], float v2[2], float u[2])
{
	float t, v11[2], v12[2], v21[2], v22[2];			// �������������Ϻʹ�ֱ�����ߵ��ٶȷ���
	v11[0] = (v1[0] * u[0] + v1[1] * u[1]) * u[0] / (u[0] * u[0] + u[1] * u[1]);
	v11[1] = (v1[0] * u[0] + v1[1] * u[1]) * u[1] / (u[0] * u[0] + u[1] * u[1]);
	v12[0] = v1[0] - v11[0];
	v12[1] = v1[1] - v11[1];
	v21[0] = (v2[0] * u[0] + v2[1] * u[1]) * u[0] / (u[0] * u[0] + u[1] * u[1]);
	v21[1] = (v2[0] * u[0] + v2[1] * u[1]) * u[1] / (u[0] * u[0] + u[1] * u[1]);
	v22[0] = v2[0] - v21[0];
	v22[1] = v2[1] - v21[1];
	if ((((fabs(v11[0]) <= fabs(v21[0])) && (v11[0] * u[0] >= 0) && (v11[0] * v21[0] >= 0)) ||
		((v11[0] * v21[0] <= 0) && (v21[0] * u[0] >= 0)) ||
		((fabs(v11[0]) >= fabs(v21[0])) && (v21[0] * u[0] >= 0) && (v11[0] * v21[0] >= 0))) &&
		(((fabs(v11[1]) <= fabs(v21[1])) && (v11[1] * u[1] >= 0) && (v11[1] * v21[1] >= 0)) ||
		((v11[1] * v21[1] <= 0) && (v21[1] * u[1] >= 0)) ||
		((fabs(v11[1]) >= fabs(v21[1])) && (v21[1] * u[1] <= 0) && (v11[1] * v21[1] >= 0))))
		return 0;					// ���ᷢ����ײ�������ֱ�ӷ���

	// �������������ٶȽ���
	t = v11[0];
	v11[0] = v21[0];
	v21[0] = t;
	t = v11[1];
	v11[1] = v21[1];
	v21[1] = t;

	// �õ��µ��ٶ�
	v1[0] = v11[0] + v12[0];
	v1[1] = v11[1] + v12[1];
	v2[0] = v21[0] + v22[0];
	v2[1] = v21[1] + v22[1];

	return 1;
}

// ��Сʱ�䵥λ�ڵ�λ�Ʊ仯  
int BallMove(float x[], float y[], float a[], float b[], int n)
{
	for (int i = 0; i < n; i++)
	{
		x[i] += a[i] / 100;			// ����С����(����ָһ�����ص�ĳ���ı߳�)�ķָ�
		y[i] += b[i] / 100;
	}
	return 0;
}

// ��ײ�ж�
void Judge(float x[], float y[], float a[], float b[], int n)
{
	int i = 0, j = 0;
	float v1[2], v2[2], u[2];		// ����������С��ĳ��ٶȺ���ײ����
	while (i < n)					// С���Ƿ�����
	{

		for (j = i + 1; j < n; j++)
		{
			if (((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]) <= 1600))
			{
				u[0] = x[j] - x[i];		// ������С��ĳ��ٶȺ���ײ����
				u[1] = y[j] - y[i];
				v1[0] = a[i];
				v1[1] = b[i];
				v2[0] = a[j];
				v2[1] = b[j];

				// �ж�������С���Ƿ�����
				if (PerfectElasticCollision(v1, v2, u))
				{
					a[i] = v1[0];			// ��ײ����С����ٶȵĸı�
					b[i] = v1[1];
					a[j] = v2[0];
					b[j] = v2[1];
				}
			}
		}
		i++;
	}
	i = 0;
	while (i < n)		// С���Ƿ�����
	{
		if ((x[i] - 21) <= 0 || ((XN - 21) - x[i]) <= 0)
			if ((y[i] - 21) <= 0 || (y[i] - (YN - 21)) >= 0)
			{
				a[i] = -a[i];
				b[i] = -b[i];
			}
			else
				a[i] = -a[i];
		if ((y[i] - 21) <= 0 || (y[i] - (YN - 21)) >= 0)
			b[i] = -b[i];
		i++;
	}
	return;
}

// ������
void main()
{
	int i = 0, j = 0, n = N;
	float x[N] = { 0 }, y[N] = { 0 }, a[N] = { 0 }, b[N] = { 0 };

	// ��ʼ������λ��(x[], y[])���ٶ�����(a[], b[]), �ٶ�����
	for (i = 0; i < n; i += 1)
	{
		x[i] = (float)50 * (i % 10) + 50;
		y[i] = (float)50 * (i / 10) + 50;
		a[i] = (float)V;
		b[i] = (float)-V * (i % 2);
	}

	initgraph(XN, YN);
	BeginBatchDraw();
	setrop2(R2_XORPEN);
	setfillcolor(RED);

	while (true)
	{
		for (i = 0; i<n; i++)
			Ball((int)x[i], (int)y[i]);
		FlushBatchDraw();
		Sleep(1);
		for (i = 0; i<n; i++)
			Ball((int)x[i], (int)y[i]);
		Judge(x, y, a, b, n);			// �ж��Ƿ����������ڣ����У��ı��ٶ�����
		BallMove(x, y, a, b, n);		// ��Сʱ�䵥λ����λ�õı䶯
	}

	EndBatchDraw();
	getch();
	closegraph();
}