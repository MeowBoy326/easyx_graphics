///////////////////////////////////////////////////
// �������ƣ�������Ϸ
// ���뻷����Visual C++ 6.0��EasyX 2011���ݰ�
// �������ߣ�yangw80 <yw80@qq.com>
// ����޸ģ�2011-5-22
//
#include <graphics.h>
#include <conio.h>
#include <time.h>



// ����ȫ�ֱ���
__int8 world[102][102] = { 0 };	// �����ά����
IMAGE imgLive, imgEmpty;		// �����ϸ������ϸ�������ͼ��



// ��������
void Init();					// ��ʼ��
void SquareWorld();				// ����һ��ϸ���Է��ηֲ�������
void RandWorld();				// ����һ��ϸ������ֲ�������
void PaintWorld();				// ��������
void Evolution();				// ����



// ������
int main()
{
	Init();
	int Speed = 500;			// ��Ϸ�ٶȣ����룩

	while (true)
	{
		if (kbhit() || Speed == 900)
		{
			char c = getch();

			if (c == ' ' && Speed != 900)
				c = getch();

			if (c >= '0' && c <= '9')
				Speed = ('9' - c) * 100;

			switch (c)
			{
			case 's':
			case 'S':
				SquareWorld();	// ����Ĭ�ϵ�ϸ���Է��ηֲ�������
				break;

			case 'r':
			case 'R':
				RandWorld();	// ����Ĭ�ϵ�ϸ���Է��ηֲ�������
				break;

			case VK_ESCAPE:
				goto END;
			}
		}

		Evolution();			// ����
		PaintWorld();			// ��������

		if (Speed != 900)		// �ٶ�Ϊ 900 ʱ��Ϊ�����������ִ��
			Sleep(Speed);
	}

END:
	closegraph();
	return 0;
}



///////////////////////////////////////////////////
// ��������

// ��ʼ��
void Init()
{
	// ������ͼ����
	initgraph(640, 480);

	// �����������
	srand((unsigned)time(NULL));

	// ��������ͼ���Ĵ�С
	Resize(&imgLive, 4, 4);
	Resize(&imgEmpty, 4, 4);

	// ���������������ͼ��
	SetWorkingImage(&imgLive);
	setcolor(GREEN);
	setfillstyle(GREEN);
	fillellipse(0, 0, 3, 3);

	// ���������������ͼ��
	SetWorkingImage(&imgEmpty);
	setcolor(DARKGRAY);
	rectangle(1, 1, 2, 2);

	// �ָ���Ĭ�ϴ��ڵĻ�ͼ
	SetWorkingImage(NULL);

	// �����˵��
	setfont(24, 0, "����");
	outtextxy(254, 18, "�� �� �� Ϸ");
	RECT r = { 440, 60, 620, 460 };
	setfont(12, 0, "����");
	drawtext("������Ϸ��飺\n����������Ϸ����һ����ά�������磬��������е�ÿ�������ס		��һ�����ŵĻ����˵�ϸ����һ��ϸ������һ��ʱ������ȡ�������ڰ˸������л��ŵ�ϸ��		�����������һ��ϸ����Χ�Ļ�ϸ���������� 3 �������ϸ������Ϊ��Դ�ѷ�������һ��ʱ		����ȥ�����һ��λ����Χ�� 3 ����ϸ�������λ������һ��ʱ�̽�����һ���µ�ϸ������		��һ��λ����Χ�� 2 ����ϸ�������λ�õ�ϸ������״̬���ֲ��䣻���һ��ϸ����Χ�Ļ�		ϸ������ 2 ������ô���ϸ������̫�µ�����ȥ������������������Ų�����̫��������ӵ		��������һ�ֶ�̬��ƽ�⡣\n\n��Ϸ���ƣ�\n 0-9: �����ٶ�(��--��)\n ESC: �˳�\n�ո�: 		��ͣ|����\n   S: ����ϸ���Է��ηֲ�������\n   R: ����ϸ������ֲ�������",
		&r, DT_WORDBREAK);

	// ����Ĭ�ϵ�ϸ���Է��ηֲ�������
	SquareWorld();
}

// ����һ��ϸ���Է��ηֲ�������
void SquareWorld()
{
	memset(world, 0, 102 * 102 * sizeof(__int8));

	for (int x = 1; x <= 100; x++)
		world[x][1] = world[x][100] = 1;

	for (int y = 1; y <= 100; y++)
		world[1][y] = world[100][y] = 1;
}

// ����һ��ϸ������ֲ�������
void RandWorld()
{
	for (int x = 1; x <= 100; x++)
		for (int y = 1; y <= 100; y++)
			world[x][y] = rand() % 2;
}

// ��������
void PaintWorld()
{
	for (int x = 1; x <= 100; x++)
		for (int y = 1; y <= 100; y++)
			putimage(16 + x * 4, 56 + y * 4, world[x][y] ? &imgLive : &imgEmpty);
}

// ����
void Evolution()
{
	__int8 tmp[102][102] = { 0 };		// ��ʱ����
	int sum;

	for (int x = 1; x <= 100; x++)
	{
		for (int y = 1; y <= 100; y++)
		{
			// ������Χ���ŵ���������
			sum = world[x + 1][y] + world[x + 1][y - 1] + world[x][y - 1] + world[x - 1][y - 1]
				+ world[x - 1][y] + world[x - 1][y + 1] + world[x][y + 1] + world[x + 1][y + 1];

			// ���㵱ǰλ�õ�����״̬
			switch (sum)
			{
			case 3:		tmp[x][y] = 1;				break;
			case 2:		tmp[x][y] = world[x][y];	break;
			default:	tmp[x][y] = 0;				break;
			}
		}
	}

	// ����ʱ����ָ�Ϊ����
	memcpy(world, tmp, 102 * 102 * sizeof(__int8));
}