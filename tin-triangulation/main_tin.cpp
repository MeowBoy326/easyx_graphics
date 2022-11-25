///////////////////////////////////////////////////
// �������ƣ�TIN ����������
// ���뻷����Mictosoft Visual Studio 2013, EasyX_20200315(beta)
// �������ߣ�luoyh <2864292458@qq.com>
// ����޸ģ�2020-4-1
// �������� TIN ������ʵ�����Բ�㷨
//

#include <graphics.h>
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#define WIDTH 640										// ���ɴ��ڵĴ�С
#define HEIGHT 480 
#define NUMBER 50										// �����ĸ���
int X[NUMBER];											// ���� X ��������������
int Y[NUMBER];											// ���� Y ��������������
bool LineXY[(1 + NUMBER) * NUMBER / 2] = { false };		// Ϊ���ж������Ƿ����߶����һά����


//�ж����������Ƿ�����
bool IsLinked(int p1, int p2)
{
	if (p1 >= p2)
		return LineXY[(1 + p1) * p1 / 2 + p2];
	else
		return LineXY[(1 + p2) * p2 / 2 + p1];
}


//�����Ѿ����ƹ�����
void Link(int p1, int p2)
{
	if (p1 >= p2)
		LineXY[(1 + p1) * p1 / 2 + p2] = true;
	else
		LineXY[(1 + p2) * p2 / 2 + p1] = true;
}


// ���������
void drawpoint(int x, int y, float z)
{
	float S = 1, L = 0.5;
	setfillcolor(HSLtoRGB(z, S, L));
	solidcircle(x, y, 4);
}


// ���ڼ�������ľ���
double distance(double x1, double y1, int x2, int y2)
{
	return sqrt((double)((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}


// ���ڲ��������
void Randompoint(int width, int height, int *lx, int *ly, int n)
{
	int i;
	bool T;
	while (true)
	{
		i = 0;
		*lx = (rand() % (width - 60) + 30);
		*ly = (rand() % (height - 60) + 30);
		while (true)
		{
			if (i >= n)
			{
				T = true;
				break;
			}
			if (distance(*lx, *ly, X[i], Y[i]) < 20)			// ���ڿ��������֮��ľ���
			{
				T = false;
				break;
			}
			i++;
		}
		if (T == false)
			continue;
		else
			break;
	}
}


// ��������������������������γ����Բ��Բ�ĺͰ뾶
double CircleCenter(int x1, int y1, int x2, int y2, int x3, int y3, double *x, double *y, double *r)
{
	if ((2.0 * (x1 * (y2 - y3) - y1 * (x2 - x3) + x2 * y3 - x3 * y2)) == 0)
	{
		*x = 0;
		*y = 0;
		*r = 0;
		return *r;
	}
	*x = ((x1 * x1 + y1 * y1) * (y2 - y3) + (x2 * x2 + y2 * y2) * (y3 - y1) + (x3 * x3 + y3 * y3) * (y1 - y2)) / (2.0 * (x1 * (y2 - y3) - y1 * (x2 - x3) + x2 * y3 - x3 * y2));
	*y = ((x1 * x1 + y1 * y1) * (x3 - x2) + (x2 * x2 + y2 * y2) * (x1 - x3) + (x3 * x3 + y3 * y3) * (x2 - x1)) / (2.0 * (x1 * (y2 - y3) - y1 * (x2 - x3) + x2 * y3 - x3 * y2));
	*r = sqrt((*x - x1) * (*x - x1) + (*y - y1) * (*y - y1));
	return *r;
}


int main()
{
	initgraph(WIDTH, HEIGHT);
	float G[NUMBER];								// ���治ͬ����ɫ�����ڿ�����������߳�
	int Z[NUMBER];									// �����жϹ��ĵ������
	double max = WIDTH * HEIGHT * WIDTH;			// �ô��ڵĳ��Ϳ�������һ����Դ����
	int lx;											// ������ʱ X ��������ı���
	int ly;											// ������ʱ Y ��������ı���
	int li;											// ���ڴ�����ʱ�жϹ��ĵ���±���

	srand((unsigned)time(NULL));					// ��ʼ�������
	for (int i = 0; i < NUMBER; i++)
	{
		Randompoint(WIDTH, HEIGHT, &lx, &ly, i);
		X[i] = lx;									// ���� X ����������
		Y[i] = ly;									// ���� Y ����������
		G[i] = float(rand() % 240);					// ������ͬ����ɫ������������ڿ���������ʾ�̣߳�
		drawpoint(X[i], Y[i], G[i]);				// ���������
	}

	float H = 60, S = 1, L = 0.5;
	setlinecolor(HSLtoRGB(H, S, L));

	// ��������ɵĵ��������жϣ��ҳ�������̵�������
	for (int i = 0; i < NUMBER; i++)
	{
		for (int j = i + 1; j < NUMBER; j++)
		{
			if (max > distance(X[i], Y[i], X[j], Y[j]))
			{
				lx = i;
				ly = j;
				max = distance(X[i], Y[i], X[j], Y[j]);
			}
		}
	}

	line(X[lx], Y[lx], X[ly], Y[ly]);
	Link(lx, ly);
	Z[0] = lx;
	Z[1] = ly;

	int n = 2;
	while (true)
	{
		if (n >= NUMBER)
			break;

		int m = 0;
		double rad, Xd, Yd, Rd;
		bool OK = false;
		max = WIDTH * HEIGHT * WIDTH;

		// ��ʼ�ж�������ɵ�ÿһ����
		for (int i = 0; i < NUMBER; i++)
		{
			m = 0;
			OK = false;

			// �ж�������Ƿ��Ѿ��жϹ�������Ѿ��жϹ��������ж���һ���㣬������ڣ���������
			while (true)
			{
				if (m >= n)
				{
					m = 0;
					break;
				}
				if (i == Z[m])
				{
					OK = true;
					break;
				}
				m++;
			}
			if (OK == true)
				continue;

			// ���Ѿ�ȷ�����������δȷ���ĵ���м��������γ������εĵİ뾶�����ж��γɵ�Բ�����������ĵ�
			// ���������ĵ㣬��������ߣ����������ĵ㣬������ж���һ����
			for (int j = 0; j < n; j++)
			{
				for (int k = 0; k < n; k++)
				{
					rad = CircleCenter(X[Z[j]], Y[Z[j]], X[Z[k]], Y[Z[k]], X[i], Y[i], &Xd, &Yd, &Rd);
					int cc = 0;
					OK = false;
					while (true)
					{
						if (cc >= NUMBER)
							break;

						// �ж�Բ�����������㣬����������жϵĵ㲻��Ϊ�γ����Բ����������㣬����������㣬��������ѭ��
						if (distance(Xd, Yd, X[cc], Y[cc]) <= Rd && cc != Z[k] && cc != Z[j] && cc != i)
						{
							OK = true;
							break;
						}
						cc++;
					}

					// ��ΪԲ���������㣬��������ѭ��
					if (OK == true)
						continue;

					if (max >= rad && rad != 0)					// ��������Χ��Բ��û�е��ҵ��뾶��С��
					{
						lx = Z[j];
						ly = Z[k];

						if (rad >= WIDTH)
							continue;
						else
						{
							if (IsLinked(i, lx) == false)		// �����߶Σ������ж�����߶��Ƿ��Ѿ����ƹ�
							{
								Link(i, lx);
								line(X[i], Y[i], X[lx], Y[lx]);
								/*Sleep(100);*/					// �����Ҫ�鿴���ƹ��̣�ȥ��ע��
							}
							if (IsLinked(i, ly) == false)
							{
								Link(i, ly);
								line(X[i], Y[i], X[ly], Y[ly]);
								/*Sleep(100);*/					// �����Ҫ�鿴���ƹ��̣�ȥ��ע��
							}
							if (IsLinked(lx, ly) == false)
							{
								Link(lx, ly);
								line(X[lx], Y[lx], X[ly], Y[ly]);
								/*Sleep(100);*/					// �����Ҫ�鿴���ƹ��̣�ȥ��ע��
							}
							li = i;
						}
					}
				}
			}
		}
		Z[n] = li;
		n++;
	}

	//�������
	for (int i = 0; i < NUMBER; i++)
	{
		drawpoint(X[i], Y[i], G[i]);
	}

	_getch();
	return 0;
}