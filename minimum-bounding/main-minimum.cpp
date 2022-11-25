///////////////////////////////////////////////////
// �������ƣ��������ε���С��Χ����
// ���뻷����Visual C++ 6.0 / 2019��EasyX 20210730
// �������ߣ�yangw80 <yw80@qq.com>
// ����޸ģ�2013-11-14
//
#include <graphics.h>
#include <math.h>

const double PI = 3.1415926536;

// �����ε���С��Χ����
// ������
//	x, y:   Բ��
//	r:      �뾶
//	a1, a2: ��ʼ�ǡ���ֹ�ǵĻ���
RECT GetPieMinimumRect(int x, int y, int r, double a1, double a2)
{
	// �������
	int i;
	double a;

	// �淶�����ȣ�ȷ����ʼ��С����ֹ��
	if (a1 > a2)
		a2 += PI * 2;

	// ���������������С��Χ����
	// ��������� 7 ����������Сֵ���õ���С��Χ����
	// 7 ���������Բ�ġ�Բ�����ˡ�Բ����������Ľ���(��� 4 ��)

	// ��һ������ʼ�� 7 ����
	POINT pt[7];
	pt[0].x = x;							pt[0].y = y;
	pt[1].x = int(x + r * cos(a1) + 0.5);	pt[1].y = int(y - r * sin(a1) + 0.5);
	pt[2].x = int(x + r * cos(a2) + 0.5);	pt[2].y = int(y - r * sin(a2) + 0.5);

	for (a = ceil(a1 * 4 / (2 * PI)) * (PI / 2), i = 3; a < a2; a += PI / 2, i++)
	{
		pt[i].x = int(x + r * cos(a) + 0.5);
		pt[i].y = int(y - r * sin(a) + 0.5);
	}

	// �ڶ�������ȡ 7 ����������Сֵ���õ���С��Χ����
	i--;
	RECT rect = { pt[i].x, pt[i].y, pt[i].x, pt[i].y };

	for (--i; i >= 0; i--)
	{
		if (pt[i].x < rect.left)	rect.left = pt[i].x;
		if (pt[i].x > rect.right)	rect.right = pt[i].x;
		if (pt[i].y < rect.top)		rect.top = pt[i].y;
		if (pt[i].y > rect.bottom)	rect.bottom = pt[i].y;
	}

	// ������С��Χ����
	return rect;
}

// ��ȡָ������ĽǶ�
double GetAngle(int x, int y)
{
	int dx = x - 320;
	int dy = 240 - y;

	double a;

	if (dx == 0 && dy == 0)
		a = 0;
	else if (dx != 0 && dy != 0)
		a = atan((double)(dy) / dx);
	else if (dx == 0)
		a = (dy > 0) ? PI / 2 : PI * 3 / 2;
	else
		a = 0;
	if (dx < 0)	a += PI;
	if (a < 0)	a += PI * 2;

	return a;
}

// �������μ���С��Χ����
void Draw(double a1, double a2, int r)
{
	cleardevice();

	// ��������
	setlinecolor(GREEN);
	setfillcolor(GREEN);
	setfillstyle(BS_HATCHED, HS_BDIAGONAL);
	fillpie(320 - 100, 240 - 100, 320 + 100, 240 + 100, a1, a2);

	// ���ƾ���
	RECT rect = GetPieMinimumRect(320, 240, r, a1, a2);
	setlinecolor(YELLOW);
	rectangle(rect.left, rect.top, rect.right, rect.bottom);
}

// ������
int main()
{
	// ������ͼ����
	initgraph(640, 480);

	// ��ʼ��
	double a1 = 0;			// ������ʼ�ǵĻ���
	double a2 = PI * 3 / 4;	// ������ֹ�ǵĻ���
	int r = 100;			// ���ΰ뾶

	Draw(a1, a2, r);		// ���Ƴ�ʼ״̬
	BeginBatchDraw();		// ����������ͼ��ֹ��˸

	ExMessage msg;

	do
	{
		// ��ȡ�����Ϣ
		msg = getmessage();

		if (msg.lbutton)				// ������µ�����ֹ�ǵĽǶ�
		{
			// �������Ƕ�
			if (msg.shift)				// ���� Shift ��������ʼ�ǵĽǶ�
				a1 = GetAngle(msg.x, msg.y);
			else
				a2 = GetAngle(msg.x, msg.y);

			// �������κ���С��Χ����
			Draw(a1, a2, r);

			// ˢ����ʾ
			FlushBatchDraw();
		}
	} while (msg.message != WM_RBUTTONUP);	// ������Ҽ��˳�

	// �ر�ͼ�δ���
	EndBatchDraw();
	closegraph();
	return 0;
}