/****************************************************************
*																*
*	�������ƣ�	��Ϳ������Ϸ��									*
*	���뻷����	VC++6.0 && && EasyX_v20120603b					*
*	������أ�	Made In China by xiongfj <837942056@qq.com>		*
*	����޸ģ�	2012.09.12										*
*																*
****************************************************************/

#include <graphics.h>
#include <conio.h>

// ��������
#define GLENGTH 30						// ÿ��С���ӵı߳�
#define MAXGRID 15						// ��󵥱߸�����

// ȫ�ֱ�������
int i, numgrid = 4, level = 4;			// ��ʼ�������뼶��
int xleft, xright, yup, ydown;			// �ֱ���������ο�ܵ����������ĸ����������
MOUSEMSG m;

// ��������
bool grid[MAXGRID][MAXGRID];			// ����״̬
void Draw(int numgrid);					// ��Ϸ���
int SetMouseMsg();						// �ܵ������Ϣ
int Lbutton(int numgrid, MOUSEMSG);		// ��������Ϣ
int Pass();								// ����Ƿ�ͨ��
int Cheat();							// ���׺��������²�ͨ��



// ������
void main()
{
	initgraph(780, 640);
	Draw(numgrid);
	int x = 0;

	while (!kbhit())					// ����һ�Σ���������һѭ��
	{
		if (numgrid > 15)
		{
			setfont(20, 0, "����");
			setcolor(LIGHTGREEN);
			setwritemode(R2_XORPEN);
			outtextxy(20, 580, "��������˳���");
			outtextxy(630, 610, "С�ܳ���(��o��)");

			while (!kbhit())
			{
				outtextxy(x, 320, "����ǧ���Ѽ����Ҳ���ⶼ��ͨ�أ�");
				Sleep(14);
				outtextxy(x, 320, "����ǧ���Ѽ����Ҳ���ⶼ��ͨ�أ�");
				x += 2;
				if (x>780)
					x = 0;
			}
			break;
		}

		// ��� numgrid++ ������һ��
		if (numgrid > level)
		{
			Draw(numgrid);
			level = numgrid;
		}
		SetMouseMsg();
	}

	getch();
	closegraph();
}



// ����Ϸ�������
void Draw(int numgrid)
{
	cleardevice();

	xleft = 390 - numgrid * GLENGTH / 2;			// ��������߽�� x ����
	xright = 390 + numgrid * GLENGTH / 2;
	yup = 320 - numgrid * GLENGTH / 2;			// �������ϱ߽�� y ����
	ydown = 320 + numgrid * GLENGTH / 2;

	setlinestyle(PS_SOLID, 1);
	setcolor(LIGHTGREEN);

	for (i = xleft; i <= xright; i += GLENGTH)		line(i, yup, i, ydown);		// ������
	for (i = yup; i <= ydown; i += GLENGTH)		line(xleft, i, xright, i);	// ������

	setfont(15, 0, "����");
	setcolor(RGB(111, 211, 0));

	// �������˵��
	outtextxy(11, 10, "1�������ո��ӣ�ͬʱ�����������ҵĿո��ӻ�ɫ��");
	outtextxy(11, 27, "2��ȫ�����Ӷ�������ɫ���ء�");
	outtextxy(11, 44, "3����������˳���Ϸ��");
	outtextxy(11, 61, "4���һ�������Ctrl ���׼���");

	setlinestyle(PS_SOLID, 10);
	setcolor(LIGHTGREEN);

	// ��ܱ߱߼Ӵ�(������)
	line(xleft - 5, yup - 5, xright + 5, yup - 5);
	line(xleft - 5, ydown + 5, xright + 5, ydown + 5);
	line(xleft - 5, yup - 5, xleft - 5, ydown + 5);
	line(xright + 5, yup - 5, xright + 5, ydown + 5);

	// ÿ���ػ���ʱ���ÿ�����ӣ�0 Ϊ�գ�1 Ϊ��ɫ
	for (i = 0; i < numgrid; i++)
		for (int y = 0; y < numgrid; y++)
			grid[i][y] = 0;
}



// �ֽ���갴����Ϣ
int SetMouseMsg()
{
	m = GetMouseMsg();

	switch (m.uMsg)
	{
	case WM_LBUTTONDOWN:
		if (m.mkCtrl)
			Cheat(); 				// ���׺���
		else
			Lbutton(numgrid, m);	// �������
		break;

		// �һ��ػ����
	case WM_RBUTTONDOWN:
		Draw(numgrid);
		break;

	default:
		break;
	}
	return 0;
}



// �������ʵ��
int Lbutton(int numgrid, MOUSEMSG m)
{
	for (i = 0; i < numgrid; i++)												// �ж� x ����
	{
		if (m.x > xleft + GLENGTH * i && m.x < xleft + GLENGTH * (i + 1))		// ��� m.x ��ĳ������
		{
			for (int y = 0; y < numgrid; y++)									// �ж� y ����
				if (m.y > yup + GLENGTH * y && m.y < yup + GLENGTH * (y + 1))		// ��� m.y Ҳ��ĳ��������
				{
					if (grid[i][y] == 0)											// ���������ڸ���δ��ɫ
						setfillstyle(RED);
					else
						setfillstyle(0);
					bar(xleft + GLENGTH * i + 1, yup + GLENGTH * y + 1,
						xleft + GLENGTH * (i + 1) - 1, yup + GLENGTH * (y + 1) - 1);
					grid[i][y] = !grid[i][y];

					// Ϳ��
					if (m.x - xleft > GLENGTH)
					{
						if (grid[i - 1][y] == 0)
							setfillstyle(RED);
						else
							setfillstyle(0);
						bar(xleft + GLENGTH * (i - 1) + 1, yup + GLENGTH * y + 1,
							xleft + GLENGTH * i - 1, yup + GLENGTH * (y + 1) - 1);
						grid[i - 1][y] = !grid[i - 1][y];
					}

					// Ϳ��
					if (xright - m.x > GLENGTH)
					{
						if (grid[i + 1][y] == 0)
							setfillstyle(RED);
						else
							setfillstyle(0);
						bar(xleft + GLENGTH * (i + 1) + 1, yup + GLENGTH * y + 1,
							xleft + GLENGTH * (i + 2) - 1, yup + GLENGTH * (y + 1) - 1);
						grid[i + 1][y] = !grid[i + 1][y];
					}

					// Ϳ��
					if (m.y - yup > GLENGTH)
					{
						if (grid[i][y - 1] == 0)
							setfillstyle(RED);
						else
							setfillstyle(0);
						bar(xleft + GLENGTH * i + 1, yup + GLENGTH * (y - 1) + 1,
							xleft + GLENGTH * (i + 1) - 1, yup + GLENGTH * y - 1);
						grid[i][y - 1] = !grid[i][y - 1];
					}

					// Ϳ��
					if (ydown - m.y > GLENGTH)
					{
						if (grid[i][y + 1] == 0)
							setfillstyle(RED);
						else
							setfillstyle(0);
						bar(xleft + GLENGTH * i + 1, yup + GLENGTH * (y + 1) + 1,
							xleft + GLENGTH * (i + 1) - 1, yup + GLENGTH * (y + 2) - 1);
						grid[i][y + 1] = !grid[i][y + 1];
					}

					// ����Ƿ����
					Pass();
				}
		}
	}
	return 0;
}



// ����Ƿ����
int Pass()
{
	int a = 1;

	for (i = 0; i < numgrid; i++)			// ɨ�����и���״̬
	{
		for (int y = 0; y < numgrid; y++)
			a = a * grid[i][y];
	}
	if (a == 1)								// �������ȫ����ɫ
	{
		numgrid++;							// ��һ�ظ�����
		setfont(20, 0, "����");
		outtextxy(250, 30, "���˸����䣬��Ҳ�У�����������һ�ء�");

		for (i = 0; i < 780; i++)
		{
			setcolor(LIGHTGREEN);
			line(i, 237, i, 243);
			Sleep(2);
		}
		return 1;
	}
	else
		return 0;
}



// ���׺�����ʵ��
int Cheat()
{
	// ɨ�� m.x ����һ��������
	for (i = 0; i < numgrid; i++)
	{
		if (m.x > xleft + GLENGTH * i && m.x < xleft + GLENGTH * (i + 1))
		{
			// ɨ�� m.y ����һ�и�����
			for (int y = 0; y < numgrid; y++)
			{
				if (m.y > yup + GLENGTH * y && m.y < yup + GLENGTH * (y + 1))
				{
					setfillstyle(GREEN);
					bar(xleft + GLENGTH * i + 1, yup + GLENGTH * y + 1,
						xleft + GLENGTH * (i + 1) - 1, yup + GLENGTH * (y + 1) - 1);

					if (grid[i][y] == 0)					// ��������ĸ���δ���Ϊ 1
						grid[i][y] = !grid[i][y];			// ���ø��ӱ��Ϊ 0

					// ����Ƿ����
					Pass();
				}
			}
		}
	}
	return 0;
}