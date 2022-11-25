// ��Ŀ������ѧģ��ʵ��
// ���ߣ��������׷�(QQ��1375989292)
// ʱ�䣺2019.12.19
// ������VC6.0

// ѧ����ѧ��ͳ�������ʱ��������һ������ģ��������ӵ��˶�����������ֱ�۵ؼ����Щ����ѧ��ʽ����ȷ�ԡ�
// ���������Ƴ���������֮��������ǳ��������Ӻͱ߽�֮��Ҳ�г����������ڶ�άƽ���˶���

// ��Ȩ������ԭ�����޳�Ϯ�����漰��Ȩ���⣬������ѧϰ

#include <graphics.h>						// ����ͼ�ο�ͷ�ļ�
#include <stdio.h>
#include <conio.h>
#include <math.h>
#define Round(d)	int(floor(d + 0.5))		// ��������궨��

#define Xsize	960
#define Ysize	960


class Vector2D		// �����ά������
{
public:
	Vector2D(){};

	Vector2D(double a, double b)
	{
		x = a;
		y = b;
		length = sqrt(x * x + y * y);
	};

	void vectorAB(double ax, double ay, double bx, double by)	// ���� A B ����
	{
		x = bx - ax;
		y = by - ay;
		length = sqrt(x * x + y * y);
	};

	void minusVector(Vector2D v)		// ��ɸ�����
	{
		x = -v.x;
		y = -v.y;
		length = v.length;
	};

	void zeroVector()	// ������
	{
		x = 0;
		y = 0;
		length = 0;
	};

public:
	double x, y;
	double length;		// ��������
};


class Particle
{
public:
	Particle(){};

	void initParticle(double paraa, double parab, double parac, double parad)
	{
		x = paraa;
		y = parab;
		vx = parac;
		vy = parad;
		dt = 0.2;	// ʱ���� 1 ����
	};

	void nextT()	// ֻ����Ʊ߽�������������Ӳ�Խ����
	{
		x = x + (vx + ax * dt / 2) * dt;
		vx = vx + ax * dt;
		y = y + (vy + ay * dt / 2) * dt;
		vy = vy + ay * dt;
	};

public:
	double x, y;		// ��¼��ǰλ��
	double vx, vy;		// ��¼��ǰ�ٶ�
	double ax, ay;		// ��¼��ǰ�ϼ��ٶ�
	double dt;
};


class Boundary
{
public:
	// ���캯�����������ӳ�ʼ״̬��������Ӧ�ڴ�ռ�
	Boundary(Particle *p, int n, double g, int a, int b, int c, int d)
	{
		left = a;			// ���������˶��߽�
		top = b;
		right = c;
		bottom = d;
		G = g;				// ���ó���ϵ��
		num = n;
		particle = p;		// ���ñ߽��ڵ�����
		space = new Vector2D *[num];		// �����ά����
		for (i = 0; i < num; i++)
			space[i] = new Vector2D[num];		// ������
		for (i = 0; i < num; i++)
			space[i][i].zeroVector();		// ����Խ��������ӵ��Լ��ľ��룬Ϊ������
	};

	// �����������ͷ�ָ����ڴ棬��ֹ�ڴ�й©
	~Boundary()
	{
		if (particle != NULL)
		{
			delete[] particle;
			particle = NULL;
		}
		for (i = 0; i < num; i++)		// ע�⳷������,���к���,�������෴
		{
			delete[] space[i];
			space[i] = NULL;
		}
		delete[] space;
		space = NULL;
	};

	// ������Ӽ�������
	void calculate()
	{
		for (i = 0; i < num; i++)		// ����������Ӽ������
		{
			for (j = i + 1; j < num; j++)
			{
				space[i][j].vectorAB(particle[i].x, particle[i].y, particle[j].x, particle[j].y);
				space[j][i].minusVector(space[i][j]);
				//	printf(" %d , %d , %f , %f , %f\n", i, j, particle[i].x, particle[i].y, space[j][i].length);
			}
		}

		double F;
		for (i = 0; i < num; i++)	// ������Ӽ�����������޸����Ĺ�ʽ���Ը�����ѧģ��
		{
			particle[i].ax = 0;
			particle[i].ay = 0;
			for (j = 0; j < i; j++)
			{
				F = -G / (space[i][j].length * space[i][j].length);			// ���ǳ����������Ĵ�С�����ƽ���ɷ���
				//	printf(" %d , %d , %f\n", i, j, F);
				particle[i].ax += F * space[i][j].x / space[i][j].length;	// �������Ӽ��ٶ�
				particle[i].ay += F * space[i][j].y / space[i][j].length;
			}
			for (j = i + 1; j < num; j++)
			{
				F = -G / (space[i][j].length * space[i][j].length);			//���ǳ����������Ĵ�С�����ƽ���ɷ���
				particle[i].ax += F * space[i][j].x / space[i][j].length;
				particle[i].ay += F * space[i][j].y / space[i][j].length;
			}

			F = G / (particle[i].x - left) + G / (particle[i].x - right);	// ����߽����������߽������������ɷ���
			particle[i].ax += F;
			F = G / (particle[i].y - top) + G / (particle[i].y - bottom);	// ����߽�������
			particle[i].ay += F;

			particle[i].nextT();	// ����������һ��λ�ã����滹Ҫ��ֹ�����ܳ��߽磬��Ծ���߽磬����Ϊ�ڱ߽��Ϸ���������ײ����
			if (particle[i].x < left)
			{
				particle[i].vx = -particle[i].vx;
				particle[i].x = left - particle[i].x;
			}
			if (particle[i].x > right)
			{
				particle[i].vx = -particle[i].vx;
				particle[i].x = right - (particle[i].x - right);
			}
			if (particle[i].y < top)
			{
				particle[i].vy = -particle[i].vy;
				particle[i].y = top - particle[i].y;
			}
			if (particle[i].y > bottom)
			{
				particle[i].vy = -particle[i].vy;
				particle[i].y = bottom - (particle[i].y - bottom);
			}
		}
	};

public:
	double left, top, right, bottom;
	double dt;
	Particle *particle;		// �����������
	int num;				// �������������

private:
	Vector2D **space;		// ��¼���Ӽ�� ��Ϊ num * num �ľ���
	int i, j, k;			// �����м����
	double G;				// ����Ӽ������ G / (r * r).

};


void main()
{
	initgraph(Xsize, Ysize, SHOWCONSOLE);	// ������ͼ���ڣ���СΪ 640x480 ����

	Particle partical[100];
	for (int i = 0; i < 100; i++)
	{
		partical[i].initParticle(i / 10 * 50.0 + 400, i % 10 * 50.0 + 400, 0, 0);
	}
	Boundary bound(partical, 100, 9.80, 0, 0, Xsize, Ysize);	// �������Ӻͱ߽�

	IMAGE image(Xsize, Ysize);		// ����ͼƬ����ֹ��������
	while (1)
	{
		SetWorkingImage(&image);
		clearrectangle(0, 0, Xsize, Ysize);
		bound.calculate();
		for (int i = 0; i < 100; i++)
		{
			circle(Round(partical[i].x), Round(partical[i].y), 5);		// ��������
		}
		SetWorkingImage();
		putimage(0, 0, &image);
		Sleep(1);
	}
	closegraph();				// �رջ�ͼ����
}