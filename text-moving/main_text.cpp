#include <graphics.h>
#include <conio.h>


// ������������ƻ�������
// ������
//  x, y: ������ֵ�λ��
//  s: ������ֵ�ָ�롣���ָ��Ϊ NULL����ʾ�ָ�������
void myouttextxy(int x, int y, LPCTSTR s)
{
	static IMAGE tmp;				// �������汻���ָ��ǵ����򱳾�

	if (s == NULL)
	{
		// �ָ�����
		putimage(x, y, &tmp);
	}
	else
	{
		int w = textwidth(s);		// ��ȡ�ַ���ռ�õĿ��
		int h = textheight(s);		// ��ȡ�ַ���ռ�õĸ߶�

		// ��������
		getimage(&tmp, x, y, w, h);

		// �������
		outtextxy(x, y, s);
	}
}


// ������
void main()
{
	// �����ַ���
	TCHAR s[] = _T("��������");

	// ������ͼ����
	initgraph(640, 480);

	// ���Ʊ���
	for (int i = 0; i < 640; i++)
	{
		setlinecolor(HSLtoRGB((float)i, 1.0, 0.25));
		line(i, 0, i, 479);
	}

	// ��������Ч��
	settextcolor(WHITE);		// ����������ɫΪ��ɫ
	setbkmode(TRANSPARENT);		// �������ֱ���Ϊ͸��ɫ

	// �����ƶ�������
	for (int j = 0; j < 600; j++)
	{
		// ��������
		myouttextxy(j, 100, s);

		Sleep(20);

		// ��������
		myouttextxy(j, 100, NULL);
	}

	// �˳�
	_getch();
	closegraph();
}