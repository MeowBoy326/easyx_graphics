#include"help.h"

MyChar SS[100000] = { 0 };				// �����ļ�

/***********************************����**************************************/

void loadtext()
{
	FILE *p;
	if (_tfopen_s(&p, _T("help.txt"), _T("rb"))	)	// ���ļ�
	{
		int i = 0;
		while (!feof(p))SS[i++] = _fgettc(p);	// ��ȡ
		fclose(p);
	}
	else
		_tcscpy_s(SS, _T("              ���ļ�ʧ�ܣ�\n\n     �������Ŀ¼���Ƿ���help.txt��\n\n      �����help.txt�ļ��������´򿪡�"));
}

void updatewithinput4()
{
	MOUSEMSG m;	// ���������Ϣ
	while (MouseHit())	// ����Ƿ��������Ϣ
	{
		m = GetMouseMsg();
		if (m.x > 5 && m.x < 40 && m.y > 0 && m.y < 35)	// ����
		{
			help[0] = true;
			if (m.uMsg == WM_LBUTTONDOWN) software[0] = -1, software[2] = 19;
		}
		else help[0] = false;

		if (m.uMsg == WM_MOUSEWHEEL)
		{
			if (m.wheel < 0)
				fly -= 20;
			else
				fly += 20;
		}	
	}
	int len = (int)(_tcslen(SS) / 42.0 + 1) * 18 - 18;	// �ַ�������

	if (fly > 0)
		fly -= fly / 2;
	if (fly - 450 + (int)round(1.8f * len) < -len)
		fly += -((fly - 450 + (int)round(1.8f * len) + len) / 2);
}

void showscreen4()
{
	BeginBatchDraw();	// ��ʼ������ͼ
	setbkmode(TRANSPARENT);
	
	changecolor(0, 400, 100, 550);
	IMAGE blacks = setimage(400, 450, RGB(0, 0, 0));	// ���û�ͼ
	my_putimage(0, 100, &blacks, RGB(255, 255, 255), 0, 1, 60, 0);

	settextcolor(WHITE);
	settextstyle(18, 0, _T("����"), 0, 0, 200, false, false, false);
	RECT r = { 10, 100 + fly, 390, 1500 + fly };
	
	drawtext(SS, &r, DT_LEFT | DT_WORDBREAK);	// д����

	changecolor(0, 400, 0, 100);
	blacks = setimage(400, 101, RGB(0, 0, 0));	// ���û�ͼ
	my_putimage(0, 0, &blacks, RGB(255, 255, 255), 0, 1, 60, 0);
	settextstyle(40, 0, _T("�����п�"));
	outtextxy(160, 50, _T("���"));

	changecolor(0, 400, 550,  600);
	blacks = setimage(400, 50, RGB(0, 0, 0));	// ���û�ͼ
	my_putimage(0, 550, &blacks , RGB(255, 255, 255), 0, 1, 60, 0);

	settextcolor(WHITE);
	settextstyle(30, 0, _T("΢���ź�"));
	outtextxy(40, 10, _T("����"));
	if (help[0])settextcolor(RGB(0, 255, 255));
	else settextcolor(WHITE);
	settextstyle(30, 28, _T("΢���ź�"));
	outtextxy(0, 10, _T("��"));
	settextstyle(50, 10, _T("΢���ź�"));

	EndBatchDraw();
}