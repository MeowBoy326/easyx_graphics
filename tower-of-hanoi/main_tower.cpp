///////////////////////////////////////////////////
// �������ƣ���ŵ���ƶ�����
// ���뻷����Visual C++ 6.0��EasyX_20130506(beta)
// �������ߣ�Ronald         Email��ryl910527@gmail.com
// ����޸ģ�2011-5-26
//
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#define MAX 64				// Բ�̵������Ŀ
#define NULL 0


// ����ջ
struct STKNODE
{
	int a[4];
};

struct STK
{
	STKNODE*	stack[MAX];
	int			top;
};


// ����ȫ�ֱ���
STK s[3];					// ��������ջ���ֱ����һ�Ŷ������Ÿ�����Բ�̵�״̬
int v = 5;					// �����ٶ�



// ��������
void Initstk(STK* s);							// ��ʼ��ջ
void Hannoi(int n, char a, char b, char c);		// ��ŵ���ݹ�
void start();									// ��ʼ����
void Move(int n, char a, char b);				// �ƶ�����
int switchab(char a);							// ���ظ����
void adjust();									// �����ٶ���ͣ



// ������
void main()
{
	int n, ta[4] = { 115, 500, 285, 518 };			// ��һ��Բ�̵�λ��
	printf("����С��16\n");							// ��Ϊ����ʮ��ʱ�ͻ���ʾ���󣬵����������������
	printf("�����뺺ŵ���Ĳ�����1~64����");
	scanf("%d", &n);
	STKNODE** p;
	p = (STKNODE**)malloc(n * sizeof(STKNODE **));	// ����һ��Ԫ��Ϊ n ���Ķ�̬ STKNODE ��ָ������
	for (int i2 = 0; i2 < n; i2++)
	{
		p[i2] = (STKNODE *)malloc(sizeof(STKNODE));	// Ϊÿһ��ָ������ռ�
	}
	Initstk(&s[0]);
	Initstk(&s[1]);
	Initstk(&s[2]);									// ������ջ��ʼ��
	start();										// ���ֿ�ʼ����
	setfillcolor(GREEN);							// Բ�̵���ɫ
	for (int i = 0; i < n; i++)
	{
		ta[0] += 5;
		ta[1] -= 20;
		ta[2] -= 5;
		ta[3] -= 20;
		solidrectangle(ta[0], ta[1], ta[2], ta[3]);			// ����n���Ӵ�Сһ�ε��ŵĻ�ɫԲ��
		++s[0].top;									// ��ջ
		for (int i1 = 0; i1 < 4; i1++)
		{
			p[i]->a[i1] = ta[i1];
			s[0].stack[s[0].top] = p[i];			// ��¼ÿ�����ε�λ�ã�topΪԲ�̵ĸ���
		}
	}
	Hannoi(n, 'a', 'b', 'c');						// ��ŵ���ݹ麯��
	system("pause");
	printf("\t\t\t\tGame Over!\n");
}



///////////////////////////////////////////////////
// ��������

// ��ŵ���ĵݹ�
void Hannoi(int n, char a, char b, char c)
{
	if (n == 1)
		Move(1, a, c);
	else
	{
		Hannoi(n - 1, a, c, b);
		Move(n, a, c);
		Hannoi(n - 1, b, a, c);
	}
}

// ջ�ĳ�ʼ��
void Initstk(STK *s)
{
	int i;
	s->top = 0;
	for (i = 0; i <= MAX; i++)
		s->stack[++s->top] = NULL;
	s->top = 0;
}

// �ƶ�����
void Move(int n, char a, char b)
{
	int i3, i4 = 0, i5 = 0;
	i3 = b - a;												// Ŀ�ĸ�����Դ�����λ�ò�ֵ
	i4 = switchab(a);										// Դ��������
	i5 = switchab(b);										// Ŀ�ĸ����
	STKNODE *q1, *q0;										// �����м�������Դջ��Ŀ��ջ���ֵ�ô��ݣ�q1ΪĿ��ջ��q0ΪԴջ
	q1 = (STKNODE *)malloc(sizeof(STKNODE));
	q0 = (STKNODE *)malloc(sizeof(STKNODE));

	// Դջ��Ŀ��ջֵ�Ĵ���
	q0 = s[i4].stack[s[i4].top];
	++s[i5].top;											// ��ջ
	q1->a[0] = q0->a[0] + i3 * 200;
	q1->a[1] = 500 - s[i5].top * 20;
	q1->a[2] = q0->a[2] + i3 * 200;
	q1->a[3] = 500 - s[i5].top * 20 + 18;
	s[i5].stack[s[i5].top] = q1;
	--s[i4].top;											// ��ջ

	// �����˶�
	while (q0->a[1] >= 100)
	{
		setfillcolor(GREEN);
		solidrectangle(q0->a[0], q0->a[1], q0->a[2], q0->a[3]);
		adjust();											// ��������
		Sleep(10 * v);										// ��ͣ��ms��
		setfillcolor(WHITE);
		solidrectangle(q0->a[0], q0->a[1], q0->a[2], q0->a[3]);
		setlinecolor(RED);
		line((q0->a[0] + q0->a[2]) / 2, q0->a[1], (q0->a[0] + q0->a[2]) / 2, q0->a[3]);	// ���»��ϱ�����ԭ�еĺ���
		q0->a[1] -= 10;
		q0->a[3] -= 10;
	}

	// ��������˶����� i3 �������й�
	while (q0->a[2] != q1->a[2])
	{
		setfillcolor(GREEN);
		solidrectangle(q0->a[0], q0->a[1], q0->a[2], q0->a[3]);
		adjust();
		Sleep(10 * v);
		setfillcolor(WHITE);
		solidrectangle(q0->a[0], q0->a[1], q0->a[2], q0->a[3]);
		if (i3 < 0)											// i3<0������
		{
			q0->a[0] -= 20;
			q0->a[2] -= 20;
		}
		else												// i3>0������
		{
			q0->a[0] += 20;
			q0->a[2] += 20;
		}
	}

	// �����˶�
	while (q0->a[3] <= q1->a[3])
	{
		setfillcolor(GREEN);
		solidrectangle(q0->a[0], q0->a[1], q0->a[2], q0->a[3]);
		adjust();
		Sleep(10 * v);
		setfillcolor(WHITE);
		solidrectangle(q0->a[0], q0->a[1], q0->a[2], q0->a[3]);
		setlinecolor(RED);
		if (q0->a[1] > 100)									// �ػ��������ĺ���
		{
			line((q0->a[0] + q0->a[2]) / 2, q0->a[1], (q0->a[0] + q0->a[2]) / 2, q0->a[3]);
		}
		q0->a[1] += 10;
		q0->a[3] += 10;
	}

	// ��Ŀ�ĸ����ϵ���Ӧλ�û��Ƴ���ɫ���ο�
	setfillcolor(GREEN);
	solidrectangle(q1->a[0], q1->a[1], q1->a[2], q1->a[3]);
}

// ���ƿ�ʼ����
void start()
{

	// ��ʼ�������С
	initgraph(800, 650);

	// ������Ϊ��ɫ
	setbkcolor(WHITE);

	// �ð�ɫ�����������
	cleardevice();

	// ���Ʋʺ磬�γ�һ���ʺ磬ժ�� easyx �����ĵ�ʾ������
	float H, S, L;
	H = 0;			// ɫ��
	S = 1;			// ���Ͷ�
	L = 0.5f;		// ����
	setlinestyle(PS_SOLID, 2);								// �����߿�Ϊ 2
	for (int r = 600; r > 544; r--)
	{
		H += 5;
		setlinecolor(HSLtoRGB(H, S, L));
		circle(750, 900, r);
	}

	// ˵��
	settextstyle(50, 0, "���Ŀ���");
	settextcolor(RED);
	outtextxy(200, 150, "��ŵ���ƶ�����");
	settextstyle(20, 0, "����");
	outtextxy(600, 200, "BY:Ronald");
	outtextxy(500, 200, "�汾V1.1");
	settextstyle(50, 0, "����");
	settextcolor(GREEN);
	outtextxy(200, 350, "��㰴һ������ʼ�ɣ�");

	// �������û�
	getch();

	// ��տ�ʼ����
	cleardevice();

	// �����˶�����ĵĻ���
	setlinecolor(RED);

	// ������ɫ�߶���Ϊ����
	line(400, 110, 400, 500);
	line(600, 110, 600, 500);
	line(200, 110, 200, 500);

	// �������εĵ���
	setfillcolor(LIGHTGRAY);
	fillrectangle(80, 501, 720, 510);

	// ��ͣ��ť
	solidrectangle(360, 540, 440, 580);
	settextstyle(30, 0, "����");
	settextcolor(GREEN);
	outtextxy(370, 550, "��ͣ");
	settextstyle(20, 0, "����");
	settextcolor(RED);
	outtextxy(300, 580, "�����ͣ���밴�ո����");

	// ���ٰ�ť
	solidrectangle(160, 540, 240, 580);
	settextstyle(30, 0, "����");
	settextcolor(GREEN);
	outtextxy(170, 550, "����");
	settextstyle(20, 0, "����");
	settextcolor(RED);
	outtextxy(170, 580, "�밴 d");

	// ���ٰ�ť
	solidrectangle(560, 540, 640, 580);
	settextstyle(30, 0, "����");
	settextcolor(GREEN);
	outtextxy(570, 550, "����");
	settextstyle(20, 0, "����");
	settextcolor(RED);
	outtextxy(570, 580, "�밴 a");

	// ˵��
	settextstyle(50, 0, "����");
	settextcolor(GREEN);
	outtextxy(10, 10, "���ڽ����������ͣ�");
}

// �ж�Ŀ�ĸ�����Դ����ĸ���ŷ��ظ����
int switchab(char a)
{
	switch (a)
	{
	case 'a':
		return 0;
	case 'b':
		return 1;
	case 'c':
		return 2;
	default:
		return 0;
	}
}

// ����������ʵ�ּ��٣����٣���ͣ
void adjust()
{
	char f='\0';												// ���ռ����ý�ȥ�İ�ť�������ʱ����ı仯ֵ

	// �� f ���ܼ��̵ļ���ֵ
	if (kbhit())
		f = getch();

	// ��������Ϣ
	if (MouseHit() == true)
	{

		// ���������Ϣ
		MOUSEMSG Mouse;
		Mouse = GetMouseMsg();

		// ��Ӧ�����Ϣ
		if (Mouse.x >= 360 && Mouse.x <= 440 && Mouse.y >= 540 && Mouse.y <= 580 && Mouse.mkLButton)
		{
			f = ' ';
		}
		if (Mouse.x >= 160 && Mouse.x <= 240 && Mouse.y >= 540 && Mouse.y <= 580 && Mouse.mkLButton)
		{
			f = 'd';
		}
		if (Mouse.x >= 560 && Mouse.x <= 640 && Mouse.y >= 540 && Mouse.y <= 580 && Mouse.mkLButton)
		{
			f = 'a';
		}
	}

	// �����ڶ���
	switch (f)
	{

		// ��ͣ
	case ' ':

		// �á����������ǡ���ͣ��  
		settextstyle(30, 0, "����");
		settextcolor(GREEN);
		outtextxy(370, 550, "����");
		getch();

		// ����������ʾ����ͣ��
		settextstyle(30, 0, "����");
		settextcolor(GREEN);
		outtextxy(370, 550, "��ͣ");
		break;

		// ����
	case 'a':

		// �������ʱ�������١�λ����һ��
		setfillcolor(LIGHTGRAY);
		solidrectangle(560, 540, 640, 580);
		settextstyle(30, 0, "����");
		settextcolor(GREEN);
		outtextxy(575, 545, "����");
		Sleep(30);

		// ����
		v++;

		// ��ԭλ
		setfillcolor(LIGHTGRAY);
		solidrectangle(560, 540, 640, 580);
		settextstyle(30, 0, "����");
		settextcolor(GREEN);
		outtextxy(570, 550, "����");
		break;

		// ����
	case 'd':
		setfillcolor(LIGHTGRAY);
		solidrectangle(160, 540, 240, 580);
		settextstyle(30, 0, "����");
		settextcolor(GREEN);
		outtextxy(165, 545, "����");
		Sleep(30);
		setfillcolor(LIGHTGRAY);
		solidrectangle(160, 540, 240, 580);
		settextstyle(30, 0, "����");
		settextcolor(GREEN);
		outtextxy(170, 550, "����");

		// ����
		v--;

		// v ��СΪ1
		if (v <= 0)
		{
			v = 1;
		}
		break;

	default:
		break;
	}

	f = 'r';									// f ��ʼ��Ϊ r
	FlushMouseMsgBuffer();						// ��������Ϣ
}