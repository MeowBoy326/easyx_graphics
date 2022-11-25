///////////////////////////////////
// �������ƣ�̰����
// ���뻷����Visual C++ 6.0 / 2008��EasyX 2013������
// ���ߣ���ԫ�� QQ��646361765
// ����޸ģ�2014-5-20
// ������ʽ������Ϊ��һ�ӽǣ��� ��ת���� ��ת���� ��ͣ���� �����
// ״̬�� ��ɫ ��ͷ����ɫ ������ɫ ʳ�
//
#include <graphics.h>
#include <string.h>
#include <time.h>
#define NUM_R 10		//�뾶
#define NUM_X 25		//�������
#define NUM_Y 25		//�������
#define NUM 30			//����ڵ����
void exe(int x, int y, int f);
int  GetCommand();
void eat(int x, int y);
void clear();
void set();
void flush();
void over(bool a);

struct pos				//����������ÿ���ؽڵ�λ��
{
	int x;
	int y;
	struct pos*next;
};
struct pos*head = (pos*)malloc(sizeof(pos));	//����ͷָ��
int n = 0;				//��¼�ڵ����

void main()				//��ʼ����Ϸ
{
	int x, y, f;			//�����ʼ�����λ�÷���
	srand((unsigned)time(NULL));			//��ʼ�������
	do
	{
		x = rand() % NUM_X*NUM_R * 2 + NUM_R;
		y = rand() % NUM_Y*NUM_R * 2 + NUM_R;
	} while (x<4 * NUM_R || y<4 * NUM_R || 2 * NUM_R*(NUM_X - 2)<x || 2 * NUM_R*(NUM_Y - 2)<y);		//�������ھ��α�Ե�ĳ�ʼ��
	f = rand() % 4;										//�������
	struct pos*a = (pos*)malloc(sizeof(pos)), *p = head; //���������һ���ڵ�
	a->x = x;					//ָ��a�����һ��������
	a->y = y;
	head->next = a;			//����
	a->next = NULL;			//��β
	initgraph(2 * NUM_R*NUM_X, 2 * NUM_R*NUM_Y + 50);		//��ʼ��ͼ����
	setcolor(WHITE);
	line(0, 2 * NUM_R*NUM_Y + 1, 2 * NUM_R*NUM_X, 2 * NUM_R*NUM_Y + 1);
	setcolor(getbkcolor());	//ȡ��Բ�ı�Ե
	setfillcolor(YELLOW);	//���������ɫ
	fillcircle(x, y, NUM_R);	//�����ʼ��
	set();					//����ʳ��
	exe(x, y, f);				//������ƺ���
}

void exe(int x, int y, int f)			//������Ϸ
{
	int xf, yf, c, i;
	while (1)						//����ѭ��
	{
		c = 0;						//��ʼ������
		for (i = 0; i<5; i++)			//ѭ��5�λ�ȡ����
		{
			Sleep(100 - 50 * n / NUM);	//�ȴ�
			if (c == 0)				//��û��ȡ������ͽ��л�ȡ
			{
				c = GetCommand();
				if (c == 4)			//����4ʱ�˳�ѭ���ȴ�
					break;
			}
		}
		f = f + c;						//�ı䷽��
		if (f>3)						//�������
			f = f - 4;
		xf = yf = 0;					//��ʼ���������
		switch (f)
		{
		case 0:xf = 1; break;			//��������ʱ x��������
		case 1:yf = 1; break;			//��������ʱ y��������
		case 2:xf = -1; break;			//��������ʱ x�������
		case 3:yf = -1; break;			//��������ʱ y�������
		}
		x = x + 2 * NUM_R*xf;				//x����仯
		y = y + 2 * NUM_R*yf;				//y����仯
		if (getpixel(x, y) == RED || x<0 || y<0 || 2 * NUM_X*NUM_R<x || 2 * NUM_Y*NUM_R<y)		//�ж��Ƿ���������������߽�
			over(0);					//������Ϸ
		else							//�����������²�����
		{
			if (getpixel(x, y) == GREEN)	//�ж�ǰ���Ƿ�Ϊʳ��
				set();					//������ʳ��
			else
				clear();				//���β���
			eat(x, y);					//��ǰ�������½��
			if (n>NUM - 1)					//�ж�ʤ������
				over(1);				//������Ϸ
		}
	}
}

int GetCommand()				//��ȡ����
{
	int c = 0;					//��ʼ���������
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)	c = 1;		//��תΪ1
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)	c = 3;		//��תΪ3
	if (GetAsyncKeyState(VK_UP) & 0x8000)	c = 4;		//����Ϊ4 ���
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)	system("pause");	//��������ͣ
	return c;
}

void eat(int x, int y)				//�����½��
{
	struct pos*a = (pos*)malloc(sizeof(pos)), *p = head;		//����ָ�����
	while (p->next != NULL)			//Ѱ������β�ڵ�
		p = p->next;
	a->x = x;							//�����ݴ��浽���
	a->y = y;
	p->next = a;						//ָ��a�ӵ�β�ڵ��
	a->next = NULL;					//��β
	setcolor(getbkcolor());			//ȡ��Բ�ı�Ե
	setfillcolor(RED);				//���������ɫ
	fillcircle(p->x, p->y, NUM_R);	//�����½��
	setfillcolor(YELLOW);			//���������ɫ
	fillcircle(x, y, NUM_R);			//�����½��
}

void clear()							//���β���
{
	setcolor(getbkcolor());				//ȡ��Բ�ı�Ե
	setfillcolor(getbkcolor());			//���������ɫ
	fillcircle(head->next->x, head->next->y, NUM_R);    //�������
	head->next = head->next->next;		//ɾ���ڵ�����
}

void set()			//����ʳ���ʤ���ж�
{
	flush();
	int x, y;		//��������
	do
	{
		x = rand() % NUM_X*NUM_R * 2 + NUM_R;
		y = rand() % NUM_Y*NUM_R * 2 + NUM_R;
	} while (getpixel(x, y) == RED);		//�������ʳ���ڷ��ߵ�λ��
	setcolor(getbkcolor());
	setfillcolor(GREEN);				//���������ɫ
	fillcircle(x, y, NUM_R);				//����ʳ��
}

void flush()
{
	n++;			//�ڵ�����ۼ�
	char strnum[20], string[10] = "����:";
	itoa(n, strnum, 10);					//ת��
	strcat(string, strnum);				//����
	strcpy(strnum, "/");					//��ֵ
	strcat(string, strnum);				//����
	itoa(NUM, strnum, 10);
	strcat(string, strnum);
	setcolor(WHITE);
	settextstyle(32, 0, _T("����"));		//������������
	outtextxy(20, 2 * NUM_R*NUM_Y + 2, "          ");
	outtextxy(20, 2 * NUM_R*NUM_Y + 2, string);
}

void over(bool a)						//������Ϸ
{
	setcolor(WHITE);                    //����������ɫ
	settextstyle(48, 0, _T("����"));		//������������
	if (a)								//�ж�����
		outtextxy(NUM_X*NUM_R - 20, NUM_Y*NUM_R - 20, "ʤ��");		//������
	else
		outtextxy(NUM_X*NUM_R - 20, NUM_Y*NUM_R - 20, "ʧ��");		//������
	Sleep(2000);
	system("pause");
	exit(0);
}