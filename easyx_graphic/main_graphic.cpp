#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

// ���������֮��ľ���
float Dist2Points(float x1, float y1, float x2, float y2)
{
	float result;
	result = sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
	return result;
}

// �ж�����Բ�Ƿ��ཻ
int isTwoCirclesIntersect(float x1, float y1, float r1, float x2, float y2, float r2)
{
	if (Dist2Points(x1, y1, x2, y2)<r1 + r2)
		return 1;
	return 0;
}

// ����ɫԲ����
void DrawCircles1(float x, float y, float r)
{
	setlinecolor(RGB(0, 0, 0));
	setfillcolor(RGB(255, 255, 0));
	fillcircle(x, y, r);
}

// ��������ɫԲ����
void DrawCircles2(float x, float y, float r)
{
	float h = rand() % 360;
	COLORREF  color = HSVtoRGB(h, 0.6, 0.8);
	setlinecolor(RGB(255, 255, 255));
	setfillcolor(color);
	fillcircle(x, y, r);
}

// ��������ɫͬ��Բ����
void DrawCircles3(float x, float y, float r)
{
	while (r>0)
	{
		float h = rand() % 360;
		COLORREF  color = HSVtoRGB(h, 0.6, 0.8);
		setlinecolor(RGB(255, 255, 255));
		setfillcolor(color);
		fillcircle(x, y, r);
		r = r - 5;
	}
}

// �����ɫͬ��Բ��������
void DrawCircles4(float x, float y, float r)
{
	while (r>0)
	{
		float h = rand() % 360;
		COLORREF  color = HSVtoRGB(h, 0.9, 0.8);
		setlinecolor(color);
		circle(x, y, r);
		r = r - 5;
	}
}

int main() // ������
{
	int width = 600; // ���ڿ��
	int height = 600; // ���ڸ߶�
	initgraph(width, height); // �¿�һ������
	setbkcolor(RGB(255, 255, 255)); // ������ɫΪ��ɫ
	cleardevice(); // �Ա�����ɫ��ձ���
	srand(time(0));  // ������Ӻ���

	int xArray[200]; // ����洢����Բ�ĵ�x����
	int yArray[200]; // ����洢����Բ�ĵ�y���� 
	int rArray[200]; // ����洢����Բ�İ뾶 
	int rmin = 8; // Բ����С�뾶
	int rmax = 50; // Բ�����뾶
	int circleNum = 0; // ���ɵ�Բ�ĸ���
	float x, y, r; // ����Բ��Բ�����ꡢ�뾶
	int isNewCircleOK; // �����ж������ɵ�Բ�Ƿ������
	int i, j;
	int drawMode = 3; // �����趨4�ֲ�ͬ�Ļ���ģʽ����ʼ��Ϊ3

	while (circleNum<200) // ��Բ�ĸ���С��100ʱ��ѭ������
	{
		isNewCircleOK = 0; // ���迪ʼ��OK

		while (isNewCircleOK == 0) // �������ɵ�Բ��Okʱ���ظ�������Բ���бȽ�
		{
			if (kbhit()) // ������ʱ
			{
				char input = _getch(); // ����û�����
				if (input == ' ') // �ո��
				{
					circleNum = 0; // Բ�ĸ���Ϊ0���൱�ڻ�������������е�ԲȦ
					cleardevice(); // ����
					drawMode = drawMode + 1; // ������һ�ֻ�ͼģʽ
					if (drawMode>4) // �������4�����»ص���1�ֻ�ͼģʽ
						drawMode = 1;
				}
			}

			x = rand() % width; // ��Բ��Բ��x����
			y = rand() % height; // ��Բ��Բ��y����
			r = rmin; // ��Բ�İ뾶��ʼ��Ϊ��С�뾶

			for (i = 0; i<circleNum; i++)   // ������Բ����
				if (isTwoCirclesIntersect(xArray[i], yArray[i], rArray[i], x, y, r))
					break; // �������Բ����Բ�ཻ,����ѭ������ʱi<circleNum

			if (i == circleNum) // �������for��䶼��������˵��i����circleNum
				isNewCircleOK = 1; //  ��������ɵ�Բ������Բ�����ཻ
		}

		isNewCircleOK = 0; // ������Ϊ��OK������Ҫ�������Բ�İ뾶���
		while (isNewCircleOK == 0 && r<rmax) // ����ok��������Բ�İ뾶С�����뾶ʱ
		{
			r++; // �ð뾶+1
			for (j = 0; j<circleNum; j++) // �����о�Բ����
			{
				if (isTwoCirclesIntersect(xArray[j], yArray[j], rArray[j], x, y, r))
				{
					isNewCircleOK = 1; // һ����һ����Բ�ཻ����ʱ��ԲOk
					break; // ��Ϊ��Բ�뾶�Ѿ��ﵽ�����������ʱ����ѭ��
				}
			}
		}

		xArray[circleNum] = x; // ����Բ��Բ��������ӵ�������
		yArray[circleNum] = y; //
		rArray[circleNum] = r; // ����Բ�İ뾶��ӵ�������
		circleNum++; // Բ�ĸ���+1

		// ���ݲ�ͬ��ͼģʽ���л���		
		if (drawMode == 1)
			DrawCircles1(x, y, r);
		if (drawMode == 2)
			DrawCircles2(x, y, r);
		if (drawMode == 3)
			DrawCircles3(x, y, r);
		if (drawMode == 4)
			DrawCircles4(x, y, r);

		Sleep(10); // ��ͣ���ɺ���
	}

	_getch();	// �ȴ���������
	closegraph();  // �رմ���
	return 0;
}