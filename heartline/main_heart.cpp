////////////////////////////////////////////
// ����������
// ���ߣ�����������־
// ���뻷����Visual Studio 2019��EasyX_20211109
// ��д���ڣ�2022-1-13

#include <graphics.h>
#include <conio.h>
#include <math.h>

#define WIDTH	640					// ���ڿ��
#define HEIGHT	480					// ���ڸ߶�
#define PI		3.14159265			// ��
#define DISPLAY 3					// չʾ������Բ�붨Բ�Ľ��㼰�����ߵ�ǰ���ڵ�ĳߴ�
#define ARROW	5					// ��ͷ�ĳߴ�
#define COPIES	600					// ��������Ҫ����������ϵĶ��ٸ���
#define SECONDS 5					// ����һȦ������
using namespace std;

// �������
void drawCoordinateAxis()
{
	setlinecolor(DARKGRAY);
	line(WIDTH / 2, HEIGHT / 10, WIDTH / 2, HEIGHT / 10 * 9);
	line(WIDTH / 2, HEIGHT / 10, WIDTH / 2 + ARROW, HEIGHT / 10 + ARROW);
	line(WIDTH / 2, HEIGHT / 10, WIDTH / 2 - ARROW, HEIGHT / 10 + ARROW);

	line(WIDTH / 5, HEIGHT / 2, WIDTH / 5 * 4, HEIGHT / 2);
	line(WIDTH / 5 * 4, HEIGHT / 2, WIDTH / 5 * 4 - ARROW, HEIGHT / 2 - ARROW);
	line(WIDTH / 5 * 4, HEIGHT / 2, WIDTH / 5 * 4 - ARROW, HEIGHT / 2 + ARROW);
}

int main()
{
	initgraph(WIDTH, HEIGHT);
	BeginBatchDraw();
	setlinecolor(BLUE);

	// �������ᣬ��Բ
	double r = min(WIDTH, HEIGHT) / 9;
	circle(WIDTH / 2, HEIGHT / 2, r);
	drawCoordinateAxis();

	setrop2(R2_XORPEN);

	double lastX = WIDTH / 2.0, lastY = HEIGHT / 2 - r;					// ��һ�������ߵĵ�� x��y ֵ����ʼֵΪ y ���������Ͼ�ԭ�� a ����λ���ȵĵ�
	for (double a = 0; !_kbhit(); a += PI / COPIES * 2)					// a Ϊ��ǰ����
	{
		double x = cos(3.0 / 2.0 * PI + a) * 2 * r + WIDTH / 2;			// ��Բ��һ��ѭ����Բ�ĵ� x ֵ
		double y = sin(3.0 / 2.0 * PI + a) * 2 * r + HEIGHT / 2;		// ��Բ��һ��ѭ����Բ�ĵ� y ֵ
		double FixedPoint_X = cos(PI / 2.0 + a * 2) * r + x;			// ��ǰѭ����Բ�Ķ����Ӧ�� x ֵ
		double FixedPoint_Y = sin(PI / 2.0 + a * 2) * r + y;			// ��ǰѭ����Բ�Ķ����Ӧ�� y ֵ
		double Contact_X = cos(PI / 2.0 + a) * r + x;					// ��ǰѭ����Բ�е��ڶ�Բ�϶�Ӧ�� x ֵ
		double Contact_Y = sin(PI / 2.0 + a) * r + y;					// ��ǰѭ����Բ�е��ڶ�Բ�϶�Ӧ�� y ֵ

		// ���������ߣ�ֻ�û���һ��ѭ���ĵ����һ��ѭ���ĵ���߾���
		setrop2(R2_COPYPEN);
		setlinecolor(YELLOW);
		line(lastX, lastY, FixedPoint_X, FixedPoint_Y);
		setrop2(R2_XORPEN);
		lastX = FixedPoint_X;
		lastY = FixedPoint_Y;

		// ��Բ�붨Բ���е�
		setfillcolor(GREEN);
		solidcircle(Contact_X, Contact_Y, DISPLAY);

		// �����ߵ�ǰ��
		setfillcolor(LIGHTRED);
		solidcircle(lastX, lastY, DISPLAY);

		// ��Բ
		setlinecolor(BLUE);
		circle(x, y, r);

		FlushBatchDraw();
		Sleep((double)(1000 * SECONDS) / (double)COPIES + 0.5);

		// ������Բ
		setlinecolor(BLUE);
		circle(x, y, r);

		// ������Բ�붨Բ�Ľ���
		setfillcolor(GREEN);
		solidcircle(Contact_X, Contact_Y, DISPLAY);

		// ���������ߵ�ǰ���ڵ�
		setfillcolor(LIGHTRED);
		solidcircle(lastX, lastY, DISPLAY);
	}

	_getch();
	EndBatchDraw();
	return 0;
}