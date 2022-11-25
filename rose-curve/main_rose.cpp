////////////////////////////////////////////
// �������ƣ��ߵ���ѧͼ�Σ�õ������
// ���뻷����Visual C++ 6.0 / 2010��EasyX 2011���ݰ�
// �����д��yangw80 <yw80@qq.com>
// �����£�2011-7-11
//
#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

#define PI 3.14159265

// ��õ������
// ������
//		k = n / d: õ�����߷��̲���
//		r: �뾶
void DrawRoseCurve(int n, int d, int r)
{
	int x, y;

	bar(-240, -240, 239, 239);
	setcolor(GREEN);
	moveto(0, 0);
	for (double i = 0; i <= PI * 2; i += 0.001)
	{
		x = int(r * sin(n * PI * i) * cos(d * PI * i));
		y = int(r * sin(n * PI * i) * sin(d * PI * i));
		lineto(x, y);
	}
}

// ������
void main()
{
	initgraph(640, 480);	// ��ʼ����ͼ����
	setorigin(240, 240);	// ��������ԭ��Ϊ��Ļ����
	setfillstyle(BLACK);	// �������ɫΪ��ɫ

	// �����ʾ��Ϣ
	line(240, -240, 240, 239);
	RECT r = { 245, -200, 395, 220 };
	setfont(13, 0, "Consolas");
	drawtext("õ������ ( Rose curve )\n\n[���]\n�����ڼ�����ϵ�У����·��̱�ʾ�����߳�Ϊõ��			���ߣ�\n����r = sin ( k �� )\n������\n����r = cos ( k �� )\n������ k ������ʱ��õ			�������� k �����ꣻ\n������ k ��ż��ʱ��õ�������� 2k �����ꡣ\n\n[����]\n����k = 			n / d\n����a-z: ���� n Ϊ 1-26\n����A-Z: ���� d Ϊ 1-26\n����ESC: �˳�\n\n[��ǰֵ]			\n����k = n / d\n������= 2 / 1", &r, DT_WORDBREAK);

	char cmd = 'b';
	char tmp[20];
	int n = 2;
	int d = 1;
	while (cmd != 27)
	{
		if (cmd >= 'a' && cmd <= 'z')
			n = cmd - 'a' + 1;
		else if (cmd >= 'A' && cmd <= 'Z')
			d = cmd - 'A' + 1;

		sprintf(tmp, "������= %d / %d��", n, d);
		setcolor(WHITE);
		outtextxy(245, 86, tmp);

		DrawRoseCurve(n, d, 200);
		cmd = getch();
	}

	closegraph();
}