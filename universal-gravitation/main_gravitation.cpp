////////////////////////////////////////
// �������������˶�
// ���ߣ�Gary
// ���뻷����Visual C++ 6.0��EasyX_20211109
// ��д���ڣ�2020-2-5

# include <math.h>
# include <graphics.h>
# include <string>
# include <stdlib.h>
# include <time.h>

static double pi = acos(-1);			// Բ���� ��
static HWND hOut;						// ����

// ����һ���ṹ�壬��ť
struct Node1
{
	int posx1, posy1, posx2, posy2;		// ����
	int mod;							// ģʽ
	double r;							// Բ��ť�뾶
	COLORREF color;						// ��ɫ
	LPTSTR text;						// ����
};

// ����һ���ṹ�壬С��
struct Node2
{
	double numx, numy;					// ����
	double m;							// ����
	double fx, fy;						// ����
	double vx, vy;						// �ٶ�
	double ax, ay;						// ���ٶ�
	COLORREF color;						// ��ɫ
};

// ����һ����
class Gary
{
public:
	void carry();						// ������
	void initialization();				// ��ʼ��
	void move();						// �������ӽ�
	void draw_scene();					// ���ƽ��溯��
	void draw_palette(int a);			// ���Ƶ�ɫ�̺���
	void draw_parameter();				// ���Ʋ�������
	void draw_box();					// ����С����
	void draw_mouse();					// ������꺯��
	void creact_box();					// ����С����
	void refresh_parameter();			// ���²�������
	Node1 boxm[50];						// ��ť��Ԥ��
	Node2 box[500];						// С��Ԥ��
	int exit_carry;						// ��ѭ�������Ʋ���
	int exit_move;						// ��ʼ������Ʋ���
	int num_button;						// ��ť��������
	int num_box;						// С����������
	int flag_box;						// С����
	int mouse_or_not;					// ����Ƿ�������
	int flash_or_not;					// �����Ƿ�������
	double gravitational_constant;		// ��������
	double ease_distance;				// ���;���
	double differential_time;			// ΢��ʱ��
	double mouse_quality;				// �������
};


// ������ƺ���
void Gary::draw_scene()
{
	TCHAR s[5];
	int i, j;
	// ��������
	setbkcolor(WHITE);
	cleardevice();

	// ���Χ����
	setfillcolor(WHITE);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	line(0, 0, 500, 0);
	line(0, 0, 0, 500);
	line(0, 500, 500, 500);
	fillrectangle(11, 11, 489, 429);
	fillrectangle(500, 0, 800, 500);
	line(600, 0, 600, 500);
	line(600, 145, 800, 145);
	line(600, 75, 700, 75);
	line(600, 215, 700, 215);
	line(600, 285, 800, 285);
	line(600, 355, 700, 355);
	line(700, 0, 700, 75);
	line(700, 145, 700, 215);
	line(700, 355, 700, 499);

	// ���ò���
	setlinecolor(RGB(125, 125, 125));
	setbkcolor(WHITE);
	settextcolor(BLACK);
	settextstyle(25, 9, _T("Consolas"));
	setlinestyle(PS_SOLID, 2);

	// ���ݰ�ť��������ť���Ͳ�������
	for (i = 0; i < num_button; i++)
	{
		// Բ��ť
		if (boxm[i].mod == 0)
		{
			setfillcolor(boxm[i].color);
			// ȦȦ
			fillcircle(boxm[i].posx1, boxm[i].posy1, boxm[i].r);
		}
		// ���ΰ�ť
		else if (boxm[i].mod == 1)
		{
			setfillcolor(WHITE);
			// �߿�
			fillrectangle(boxm[i].posx1, boxm[i].posy1, boxm[i].posx2, boxm[i].posy2);
			// ����
			outtextxy(boxm[i].posx1 + (boxm[i].posx2 - boxm[i].posx1) / 2 - textwidth(boxm[i].text) / 2, boxm[i].posy1 + 6, boxm[i].text);
		}
		// �ı�
		else if (boxm[i].mod == 2)
		{
			setlinecolor(WHITE);
			setfillcolor(WHITE);
			// �߿�
			fillrectangle(boxm[i].posx1, boxm[i].posy1, boxm[i].posx2, boxm[i].posy2);
			// ����
			outtextxy(boxm[i].posx1 + (boxm[i].posx2 - boxm[i].posx1) / 2 - textwidth(boxm[i].text) / 2, boxm[i].posy1 + 6, boxm[i].text);
			setlinecolor(RGB(125, 125, 125));
		}
	}

	// С�����
	draw_box();

	// ���ֻ���
	setbkcolor(WHITE);
	settextcolor(BLACK);
	for (i = 0; i < 10; i++)
	{
		_stprintf(s, _T("%0.1d"), i * 10);
		outtextxy(boxm[i].posx1 + 22, boxm[i].posy1 - 15, s);
		outtextxy(boxm[i].posx1 + 42, boxm[i].posy1 - 15, _T("~"));
		_stprintf(s, _T("%0.1d"), i * 10 + 9);
		outtextxy(boxm[i].posx1 + 52, boxm[i].posy1 - 15, s);
	}

	// ��������
	i = 24; j = 30;
	if (mouse_or_not == 0) { outtextxy(boxm[20].posx1 + 30, boxm[20].posy1 + j, _T("��")); }
	else if (mouse_or_not == 1) { outtextxy(boxm[20].posx1 + 30, boxm[20].posy1 + j, _T("��")); }
	_stprintf(s, _T("%0.1f"), gravitational_constant);	outtextxy(boxm[19].posx1 + i, boxm[19].posy1 + j, s);
	_stprintf(s, _T("%0.1f"), ease_distance);				outtextxy(boxm[21].posx1 + i, boxm[21].posy1 + j, s);
	_stprintf(s, _T("%0.2f"), differential_time);			outtextxy(boxm[23].posx1 + i, boxm[23].posy1 + j, s);
	_stprintf(s, _T("%0.1f"), mouse_quality);				outtextxy(boxm[22].posx1 + i, boxm[22].posy1 + j, s);

	// ����δ��ʾ״̬������ѡ��С�����
	if (flash_or_not == 0)
	{
		draw_parameter();
	}

	FlushBatchDraw();
}

// С����ƺ���
void Gary::draw_box()
{
	int i;
	// ���Χ����
	setfillcolor(WHITE);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	fillrectangle(11, 11, 489, 429);
	// С�����
	for (i = 0; i < num_box; i++)
	{
		if (box[i].numx > 11 && box[i].numx < 489 && box[i].numy>11 && box[i].numy < 429)
		{
			setfillcolor(box[i].color);
			solidcircle(box[i].numx, box[i].numy, 10);
		}
	}
	FlushBatchDraw();
}

// �����ƺ���
void Gary::draw_mouse()
{
	setfillcolor(box[num_box - 1].color);
	solidcircle(box[num_box - 1].numx, box[num_box - 1].numy, 10);
	FlushBatchDraw();
}

// �������ƺ���������ֹͣ״̬����
void Gary::draw_parameter()
{
	int i, j;
	TCHAR s[5];
	// ѡ��Ŀ��С�����
	setlinecolor(LIGHTRED);
	setfillcolor(box[flag_box].color);
	fillcircle(box[flag_box].numx, box[flag_box].numy, 10);
	// ��������
	i = 24; j = 30;
	_stprintf(s, _T("%0.1d"), flag_box);					outtextxy(boxm[10].posx1 + i, boxm[10].posy1 + j, s);
	_stprintf(s, _T("%0.1f"), box[flag_box].numx);		outtextxy(boxm[11].posx1 + i, boxm[11].posy1 + j, s);
	_stprintf(s, _T("%0.1f"), box[flag_box].numy);		outtextxy(boxm[13].posx1 + i, boxm[13].posy1 + j, s);
	_stprintf(s, _T("%0.1f"), box[flag_box].vx);			outtextxy(boxm[15].posx1 + i, boxm[15].posy1 + j, s);
	_stprintf(s, _T("%0.1f"), box[flag_box].vy);			outtextxy(boxm[17].posx1 + i, boxm[17].posy1 + j, s);
	_stprintf(s, _T("%0.1f"), box[flag_box].m);			outtextxy(boxm[14].posx1 + i, boxm[14].posy1 + j, s);
}

// С�����ɺ���
void Gary::creact_box()
{
	double j, k;
	// λ�����
	k = rand() % (2 * num_box);
	j = rand() % 15;
	box[num_box].numx = 250 + 100 * sin((k / double(num_box) + j / 180.0) * pi);
	box[num_box].numy = 220 + 100 * cos((k / double(num_box) + j / 180.0) * pi);
	// ��������ɫ���ٶȳ�ʼ��
	box[num_box].color = boxm[0].color;
	box[num_box].m = 2; box[num_box].vx = 0.0; box[num_box].vy = 0.0;
	num_box++;
}

// �������º���
void Gary::refresh_parameter()
{
	int i, j;
	double G, S, dt;
	G = gravitational_constant;		// ��������
	S = ease_distance;				// ���;���
	dt = differential_time;			// ΢��ʱ��
	// ��������
	for (i = 0; i < num_box; i++)
	{
		// ������ʼ��
		box[i].fx = 0;
		box[i].fy = 0;
		// ��������
		for (j = 0; j < num_box; j++)
		{
			if (box[j].numx > 11 && box[j].numx < 489 && box[j].numy>11 && box[j].numy < 429)
			{
				box[i].fx += G * box[i].m * box[j].m / ((box[i].numx - box[j].numx) * (box[i].numx - box[j].numx) + (box[i].numy - box[j].numy) * (box[i].numy - box[j].numy) + S) * ((box[j].numx - box[i].numx) / sqrt((box[i].numx - box[j].numx) * (box[i].numx - box[j].numx) + (box[i].numy - box[j].numy) * (box[i].numy - box[j].numy) + S));
				box[i].fy += G * box[i].m * box[j].m / ((box[i].numx - box[j].numx) * (box[i].numx - box[j].numx) + (box[i].numy - box[j].numy) * (box[i].numy - box[j].numy) + S) * ((box[j].numy - box[i].numy) / sqrt((box[i].numx - box[j].numx) * (box[i].numx - box[j].numx) + (box[i].numy - box[j].numy) * (box[i].numy - box[j].numy) + S));
			}
		}
		// ͨ����������ٶȣ��ٶȣ���������
		box[i].ax = box[i].fx / box[i].m;
		box[i].ay = box[i].fy / box[i].m;
		box[i].vx = box[i].vx + box[i].ax * dt;
		box[i].vy = box[i].vy + box[i].ay * dt;
		box[i].numx = box[i].numx + box[i].vx * dt;
		box[i].numy = box[i].numy + box[i].vy * dt;
		// ���ڷ���
		if (box[i].numx <= 30 || box[i].numx >= 470)
		{
			box[i].vx = -box[i].vx;
		}
		if (box[i].numy <= 30 || box[i].numy >= 410)
		{
			box[i].vy = -box[i].vy;
		}
	}
}

// ��ɫ�̻��ƺ���
void Gary::draw_palette(int a)
{
	int D = 50;			// ���
	int R = 10;			// СԲ�뾶
	double size = 10;	// �ߴ�
	int posx, posy;
	int i, j, k;

	// ����
	setfillcolor(WHITE);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	fillrectangle(0, 0, 500, 500);
	FlushBatchDraw();

	// ��ά����
	for (i = 0; i <= 255; i = i + D)
	{
		for (j = 0; j <= 255; j = j + D)
		{
			for (k = 0; k <= 255; k = k + D)
			{
				posy = 250 - i / D * size * 2.0 + j / D * size * 1.0 + k / D * size * 1.0;
				posx = 250 + j / D * size * 1.8 - k / D * size * 1.8;
				setfillcolor(RGB(i, j, k));
				solidcircle(posx, posy, R);
			}
		}
	}

	FlushBatchDraw();

	// ��궨��
	ExMessage m;

	int exit_palette = 0;

	while (exit_palette == 0)
	{
		if (peekmessage(&m, EM_MOUSE | EM_KEY))
		{
			// ��������ж�
			if (m.message == WM_LBUTTONDOWN)
			{
				// ��ť��ɫ����
				boxm[a].color = getpixel(m.x, m.y);
				exit_palette = 1;
			}
		}
	}
	// С����ɫ����
	for (i = 0; i < num_box; i++)
	{
		if (int(box[i].m / 10) == a)
		{
			box[i].color = boxm[a].color;
		}
	}
}

// ��ʼ������
void Gary::initialization()
{
	int i;
	// ��ť�ĳ�ʼ��
	num_button = 30;
	// Բ����ɫ��ť
	boxm[0].posx1 = 525; boxm[0].posy1 = 25;	boxm[0].mod = 0;	boxm[0].r = 20; boxm[0].color = RGB(165, 207, 229);
	boxm[1].posx1 = 525; boxm[1].posy1 = 75;	boxm[1].mod = 0;	boxm[1].r = 20; boxm[1].color = RGB(30, 120, 180);
	boxm[2].posx1 = 525; boxm[2].posy1 = 125;	boxm[2].mod = 0;	boxm[2].r = 20; boxm[2].color = RGB(180, 220, 140);
	boxm[3].posx1 = 525; boxm[3].posy1 = 175;	boxm[3].mod = 0;	boxm[3].r = 20; boxm[3].color = RGB(50, 160, 70);
	boxm[4].posx1 = 525; boxm[4].posy1 = 225;	boxm[4].mod = 0;	boxm[4].r = 20; boxm[4].color = RGB(250, 150, 150);
	boxm[5].posx1 = 525; boxm[5].posy1 = 275;	boxm[5].mod = 0;	boxm[5].r = 20; boxm[5].color = RGB(230, 30, 40);
	boxm[6].posx1 = 525; boxm[6].posy1 = 325;	boxm[6].mod = 0;	boxm[6].r = 20; boxm[6].color = RGB(250, 190, 110);
	boxm[7].posx1 = 525; boxm[7].posy1 = 375;	boxm[7].mod = 0;	boxm[7].r = 20; boxm[7].color = RGB(250, 130, 30);
	boxm[8].posx1 = 525; boxm[8].posy1 = 425;	boxm[8].mod = 0;	boxm[8].r = 20; boxm[8].color = RGB(200, 180, 220);
	boxm[9].posx1 = 525; boxm[9].posy1 = 475;	boxm[9].mod = 0;	boxm[9].r = 20; boxm[9].color = RGB(100, 60, 150);

	// ���ΰ�ť
	for (i = 0; i < 14; i++)
	{
		boxm[i + 10].posx1 = 610 + i % 2 * 100;
		boxm[i + 10].posy1 = 10 + i / 2 * 70;
		boxm[i + 10].posx2 = 690 + i % 2 * 100;
		boxm[i + 10].posy2 = 70 + i / 2 * 70;
		boxm[i + 10].mod = 1;
	}

	boxm[10].text = _T("С����");
	boxm[11].text = _T("ˮƽ����");
	boxm[12].text = _T("��ʼλ��:");	boxm[12].mod = 2;
	boxm[13].text = _T("��ֱ����");
	boxm[14].text = _T("С������");
	boxm[15].text = _T("ˮƽ�ٶ�");
	boxm[16].text = _T("��ʼ�ٶ�:");	boxm[16].mod = 2;
	boxm[17].text = _T("��ֱ�ٶ�");
	boxm[18].text = _T("�߼�����:");	boxm[18].mod = 2;
	boxm[19].text = _T("��������");
	boxm[20].text = _T("������");
	boxm[21].text = _T("���;���");
	boxm[22].text = _T("�������");
	boxm[23].text = _T("΢��ʱ��");

	for (i = 0; i < 6; i++)
	{
		boxm[i + 24].posx1 = 10 + 82 * i;
		boxm[i + 24].posy1 = 440;
		boxm[i + 24].posx2 = 80 + 82 * i;
		boxm[i + 24].posy2 = 490;
		boxm[i + 24].mod = 1;
	}

	boxm[24].text = _T("����");
	boxm[25].text = _T("����");
	boxm[26].text = _T("ˢ��");
	boxm[27].text = _T("��ʼ");
	boxm[28].text = _T("ֹͣ");
	boxm[29].text = _T("�˳�");

	num_box = 3;
	// С���ʼ��
	box[0].numx = 250 + 100 * sin(120.0 / 180.0 * pi);
	box[0].numy = 220 + 100 * cos(120.0 / 180.0 * pi);
	box[0].m = 2; box[0].vx = 0.10; box[0].vy = 0;
	box[0].color = boxm[0].color;

	box[1].numx = 250 + 100 * sin(0);
	box[1].numy = 220 + 100 * cos(0);
	box[1].m = 2; box[1].vx = 0; box[1].vy = 0.10;
	box[1].color = boxm[0].color;

	box[2].numx = 250 + 100 * sin(240.0 / 180.0 * pi);
	box[2].numy = 220 + 100 * cos(240.0 / 180.0 * pi);
	box[2].m = 2; box[2].vx = 0.20; box[2].vy = 0;
	box[2].color = boxm[0].color;

	// ������ʼ��
	flag_box = 0;
	mouse_or_not = 0;				// �����ʾδ����
	flash_or_not = 0;				// ������ʾδ����

	gravitational_constant = 50;	// ��������
	ease_distance = 100;			// ���;���
	differential_time = 0.05;		// ΢��ʱ��
	mouse_quality = 20;				// �������

	// ����
	draw_scene();
}

// �������ӽǺ�������ȡ�û�����
void Gary::move()
{
	// ��궨��
	ExMessage m;
	TCHAR ss[10];
	int i, k;
	float j;
	// ���Ʋ�������
	exit_move = 0;

	while (exit_move == 0)
	{
		if (peekmessage(&m, EM_MOUSE | EM_KEY))
		{
			// ��������ж�
			if (m.message == WM_LBUTTONDOWN)
			{
				// ����δ��ʾʱ�����С���л�ѡ����С�򣬵�����Ʒ�Χ���ƶ�ѡ����С��
				if (flash_or_not == 0)
				{
					// �ж��Ƿ�����С��
					k = 0;
					for (i = 0; i < num_box; i++)
					{
						// С��
						if ((m.x - box[i].numx) * (m.x - box[i].numx) + (m.y - box[i].numy) * (m.y - box[i].numy) < 101)
						{
							flag_box = i;
							k = 1;
							break;
						}
					}
					// �ж��Ƿ������Ʒ�Χ��
					if (m.x > 11 && m.x < 489 && m.y>11 && m.y < 429 && k == 0)
					{
						box[flag_box].numx = m.x;
						box[flag_box].numy = m.y;
					}
				}

				// �ж��Ƿ����˰�ť
				for (i = 0; i < num_button; i++)
				{
					// ���ΰ�ť
					if (boxm[i].mod == 1 && m.x > boxm[i].posx1 && m.y > boxm[i].posy1 && m.x < boxm[i].posx2 && m.y < boxm[i].posy2)
					{
						break;
					}
					// Բ��ť
					else if (boxm[i].mod == 0 && (m.x - boxm[i].posx1) * (m.x - boxm[i].posx1) + (m.y - boxm[i].posy1) * (m.y - boxm[i].posy1) < boxm[i].r * boxm[i].r)
					{
						break;
					}
				}

				// ������ʾʱ��ֻ�ܵ��ֹͣ��ť
				if (flash_or_not == 1)
				{
					// ������ΰ�ť
					switch (i)
					{
						// ֹͣ��ť��flash_or_not
					case 28:
					{
						// �������Ʋ�������
						flash_or_not = 0;
						// ѡ��С���ų�ʼ��
						flag_box = 0;
						// �������ʱ
						// �ڶ����ر�ʱ����Ҫ�����һ��С��ɾȥ
						if (mouse_or_not == 1)
						{
							num_box--;
						}

						break;
					}
					default:break;
					}
				}
				// ����δ��ʾʱ�����Ե��������ť
				else if (flash_or_not == 0)
				{
					// ���Բ�ΰ�ť
					if (i >= 0 && i < 10)
					{
						draw_palette(i);
					}
					// ������ΰ�ť
					switch (i)
					{
						// С���Ű�ť��flag_box
					case 10:
					{
						InputBox(ss, 10, _T("����С����(0 ~ С������)"));
						_stscanf(ss, _T("%d"), &i);
						if (i >= 0 && i < num_box) { flag_box = i; }
						else { MessageBox(hOut, _T("������󣬲��ڷ�Χ��"), _T("����С���ӵ�����"), MB_OK); }
						break;
					}
					// ˮƽ���갴ť��box[flag_box].numx
					case 11:
					{
						InputBox(ss, 10, _T("����ˮƽ����(12 ~ 488)"));
						_stscanf(ss, _T("%d"), &i);
						if (i >= 12 && i <= 488) { box[flag_box].numx = i; }
						else { MessageBox(hOut, _T("������󣬲��ڷ�Χ��"), _T("����С���ӵ�����"), MB_OK); }
						break;
					}

					// ��ֱ���갴ť��box[flag_box].numy
					case 13:
					{
						InputBox(ss, 10, _T("���봹ֱ����(12 ~ 428)"));
						_stscanf(ss, _T("%d"), &i);
						if (i >= 12 && i <= 428) { box[flag_box].numy = i; }
						else { MessageBox(hOut, _T("������󣬲��ڷ�Χ��"), _T("����С���ӵ�����"), MB_OK); }
						break;
					}

					// С��������ť��box[flag_box].m
					case 14:
					{
						InputBox(ss, 10, _T("����С������(1 ~ 99)"));
						_stscanf(ss, _T("%d"), &i);
						if (i >= 1 && i <= 99) { box[flag_box].m = i; }
						else { MessageBox(hOut, _T("������󣬲��ڷ�Χ��"), _T("����С���ӵ�����"), MB_OK); }
						// ��ɫ��֮�ı�
						box[flag_box].color = boxm[int(box[flag_box].m / 10)].color;
						break;
					}
					// ˮƽ�ٶȰ�ť��box[flag_box].vx
					case 15:
					{
						InputBox(ss, 10, _T("����ˮƽ�ٶ�(-9 ~ 9)"));
						_stscanf(ss, _T("%f"), &j);
						if (j >= -9 && j <= 9) { box[flag_box].vx = j; }
						else { MessageBox(hOut, _T("������󣬲��ڷ�Χ��"), _T("����С���ӵ�����"), MB_OK); }
						break;
					}
					// ��ֱ�ٶȰ�ť��box[flag_box].vy
					case 17:
					{
						InputBox(ss, 10, _T("����ˮƽ�ٶ�(-9 ~ 9)"));
						_stscanf(ss, _T("%f"), &j);
						if (j >= -9 && j <= 9) { box[flag_box].vy = j; }
						else { MessageBox(hOut, _T("������󣬲��ڷ�Χ��"), _T("����С���ӵ�����"), MB_OK); }
						break;
					}
					// ����������ť��gravitational_constant
					case 19:
					{
						InputBox(ss, 10, _T("������������(10 ~ 100)"));
						_stscanf(ss, _T("%f"), &j);
						if (j >= 10 && j <= 100) { gravitational_constant = j; }
						else { MessageBox(hOut, _T("������󣬲��ڷ�Χ��"), _T("����С���ӵ�����"), MB_OK); }
						break;
					}
					// �����ʾ��ť��mouse_or_not
					case 20:
					{
						mouse_or_not = mouse_or_not == 0 ? 1 : 0;
						break;
					}
					// ���;��밴ť��ease_distance
					case 21:
					{
						InputBox(ss, 10, _T("���뻺�;���(20 ~ 100)"));
						_stscanf(ss, _T("%f"), &j);
						if (j >= 20 && j <= 100) { ease_distance = j; }
						else { MessageBox(hOut, _T("������󣬲��ڷ�Χ��"), _T("����С���ӵ�����"), MB_OK); }
						break;
					}
					// ���������ť��mouse_quality
					case 22:
					{
						InputBox(ss, 10, _T("�����������(0 ~ 99)"));
						_stscanf(ss, _T("%f"), &j);
						if (j >= 0 && j <= 99) { mouse_quality = j; }
						else { MessageBox(hOut, _T("������󣬲��ڷ�Χ��"), _T("����С���ӵ�����"), MB_OK); }
						break;
					}
					// ΢��ʱ�䰴ť��differential_time
					case 23:
					{
						InputBox(ss, 10, _T("����΢��ʱ��(0.01 ~ 0.1)"));
						_stscanf(ss, _T("%f"), &j);
						if (j >= 0.01 && j <= 0.1) { differential_time = j; }
						else { MessageBox(hOut, _T("������󣬲��ڷ�Χ��"), _T("����С���ӵ�����"), MB_OK); }
						break;
					}
					// ���Ӱ�ť
					case 24:
					{
						// ������Ԥ������£�������
						if (num_box < 498)
						{
							creact_box();
							draw_box();
						}
						else
						{
							MessageBox(hOut, "�Ѵ����ֵ", "����С���ӵ�����", MB_OK);
						}
						break;
					}
					// ���ٰ�ť
					case 25:
					{
						// ��С������������£��ɼ���
						if (num_box > 2)
						{
							num_box--;
							draw_box();
						}
						else
						{
							MessageBox(hOut, "�Ѵ���Сֵ", "����С���ӵ�����", MB_OK);
						}
						break;
					}
					// ˢ�°�ť
					case 26:
					{
						// ��ѭ���Ʋ�����һ��������ѭ
						exit_move = 1;
						break;
					}
					// ��ʼ��ť��flash_or_not
					case 27:
					{
						// �������Ʋ���
						flash_or_not = 1;
						// ������������Ʋ��������һ��С��ֵ
						// ����״̬
						if (mouse_or_not == 1)
						{
							box[num_box].numx = m.x;
							box[num_box].numy = m.y;
							box[num_box].m = mouse_quality;
							box[num_box].color = boxm[int(mouse_quality / 10)].color;
							box[num_box].vx = 0.0; box[num_box].vy = 0.0;
							num_box++;
						}
						break;
					}
					// �˳���ť
					case 29:
					{
						// ��ѭ���Ʋ�����һ��������ѭ
						exit_move = 1;
						exit_carry = 1;
						break;
					}
					default:break;
					}
				}
				// ����
				draw_scene();
			}
		}

		// ������ʾ����
		if (flash_or_not == 1)
		{
			// �������º���
			refresh_parameter();
			// С����ƺ���
			draw_box();
			// �����濪��������괦�ڻ�����
			if (mouse_or_not == 1 && m.x > 21 && m.x < 479 && m.y>21 && m.y < 419)
			{
				box[num_box - 1].numx = m.x;
				box[num_box - 1].numy = m.y;
				draw_mouse();
			}
			// �����濪��������괦�ڷǻ�����
			else if (mouse_or_not == 1)
			{
				box[num_box - 1].numx = 800;
				box[num_box - 1].numy = 800;
			}
		}
	}
}

// ������
void Gary::carry()
{
	// ���ڶ���
	hOut = initgraph(801, 501);
	SetWindowText(hOut, _T("��������"));
	// ���̿��Ʋ���
	exit_carry = 0;
	// ������ӳ�ʼ��
	srand((unsigned)time(NULL));
	BeginBatchDraw();
	while (exit_carry == 0)
	{
		initialization();
		move();
		// ˢ�£����ã����ذ�ť�����̿��Ʋ�������
		// �˳���ť�����̿��Ʋ�����һ
	}
	EndBatchDraw();
	closegraph();
}

// ������
int main(void)
{
	// ���������
	Gary G;
	// �����������ѭ����
	G.carry();
	return 0;
}
