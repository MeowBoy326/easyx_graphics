////////////////////////////////////////
// ���򣺰����׵�������
// ���ߣ�Gary
// ���뻷����Visual C++ 2010��EasyX_20211109
// ��д���ڣ�2021-1-24

# include <math.h>
# include <graphics.h>
# include <string>

static double pi = acos(-1.0);			// Բ���� ��
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

// ����һ���ṹ�壬������
struct Node2
{
	int outnum;							// ÿһλ��С��
	int nestnum;						// ÿһλ������
};

// ����һ����
class Gary
{
public:
	void carry();				// ������
	void initialization();		// ��ʼ��
	void draw_scene();			// ���ƽ��溯��
	void move();				// �������ӽ�

	// ���㺯��
	void calculation_pi();		// �еļ���
	void calculation_e();		// e �ļ���
	void calculation_num();	// �������ļ���
	// ���ƺ���
	void draw_helical_line();	// ���������ߺ���
	void draw_walking_line();	// �������ߵ�ֱ�ߺ���
	void draw_palette(int a);	// ��ɫ�̻��ƺ���

	int num_button;				// ��ť��������
	int exit_carry;				// ��ѭ�������Ʋ���
	int exit_move;				// ��ʼ������Ʋ���

	int box_pi[10000];			// �д��
	int box_e[10000];			// e ���
	Node2 box_num[10000];		// ���������
	int A, B;					// �������ķ��ӣ���ĸ
	int flag_start, flag_end;	// ��������һ��ѭ���ڿ�ʼ�ͽ���λ��

	int draw_mod;				// ����ģʽ���������֣�������ģʽ��������ģʽ
	int num_mod;				// ����ģʽ���������֣������� �У������� e ��������

	// ������ģʽ
	double initial_position;	// ��ʼλ��
	double linear_velocity;		// ���ٶ�
	double angular_velocity;	// ���ٶ�
	double d;					// ��������СԲ�뾶

	// ������ģʽ
	double step_size;			// ����

	Node1 boxm[30];				// ��ť��Ԥ�� 30 ��	
};

// �еļ��㺯����Ĭ�ϼ��� 1000 λ
void Gary::calculation_pi()
{
	int j, k, h, g, m;
	// ��ʱ���
	int box[10000];
	// ����λ��
	int t = 1000;

	// �� ��̩�չ�ʽչ��
	// pi/2 = 1+1/3+1/3 * 2/5 + 1/3 * 2/5 * 3/7 + 1/3 * 2/5 * 3/7 *4/9+...

	// ǰ����� 2.666...
	box_pi[0] = 2;
	m = 1;
	while (m <= t)
	{
		box_pi[m] = 6;
		m++;
	}

	// ��ʼ�� 1/3
	box[0] = 0;
	m = 1;
	while (m <= t)
	{
		box[m] = 6;
		m++;
	}
	// ��ʼ�ǵڶ���
	j = 2;
	k = 1;
	while (k != 0)
	{
		// �� j �����㣬�� j/(2j+1)
		// �ȳˣ���ʼ����λ��
		// �ӵ͵��ߣ���ʮ��λ
		for (h = t; h >= 0; h--)
		{
			// ÿλ���� j
			box[h] *= j;
		}
		// �������ʼ������
		g = 0;
		// �Ӹߵ��ͣ�ȡ������ʮ�ӵ���һλ
		for (h = 0; h <= t; h++)
		{
			// ����һλ��������ʮ
			box[h] += g * 10;
			// ȡ��һλ������
			g = box[h] % (2 * j + 1);
			// ÿλ������(2j+1)
			box[h] /= (2 * j + 1);
		}

		// ÿһ���С��һ�ģ�����ÿһλ����С��ʮ�ģ���λ�������һ
		// ����Ҫ��λ����ʼ����ǰ����
		g = 0;
		k = 0;
		for (h = t; h >= 0; h--)
		{
			// �ӵ͵��ߣ���ÿһ��ͬλ�������ӽ�λ��
			box_pi[h] += box[h];
			box_pi[h] += g;
			// ��λ���жϣ���Ҫ��λ���ʮ
			g = 0;
			if (box_pi[h] >= 10) { box_pi[h] -= 10; g = 1; }
			// �˳��ж�
			// ĳ������ʱ����Ҫλ��ǰȫ���㣬���ʾ�����㹻С���Ѿ�Ӱ�첻����Ҫλ��֮ǰ��λ����
			if (box[h] != 0) { k++; }
		}

		// �˳��жϣ����˳��������һ��
		if (k != 0)
		{
			j++;
		}

	}

	// ������û��ѭ����
	flag_start = 0; flag_end = t - 1;
	// ���һ�����㣬�Ѿ�Ӱ�첻����Ҫλ��֮ǰ��λ��
}

// e �ļ��㺯����Ĭ�ϼ��� 1000 λ
void Gary::calculation_e()
{
	int j, k, h, g, m;
	// ��ʱ���
	int box[10000];
	// ����λ��
	int t = 1000;

	// e ��̩�չ�ʽչ��
	// e=1+1/2!+1/3!+1/4!+...

	// ǰ����� 1+1/2!+1/3!=2.666...
	box_e[0] = 2;
	m = 1;
	while (m <= t)
	{
		box_e[m] = 6;
		m++;
	}

	// ��ʼ�� 1/3!
	box[0] = 0;
	box[1] = 1;
	m = 2;
	while (m <= t)
	{
		box[m] = 6;
		m++;
	}

	// ��ʼ�ǵ�����
	k = 1;
	j = 4;
	while (k != 0)
	{
		// �� j �����㣬�� 1/j
		// ֻ��Ҫ��
		g = 0;
		// �Ӹߵ��ͣ�ȡ������ʮ�ӵ���һλ
		for (h = 0; h <= t; h++)
		{
			// ����һλ��������ʮ
			box[h] += g * 10;
			// ȡ��һλ������
			g = box[h] % j;
			// ÿλ������ j
			box[h] /= j;
		}

		// ����Ҫ��λ����ʼ����ǰ����
		g = 0;
		k = 0;
		for (h = t; h >= 0; h--)
		{
			// �ӵ͵��ߣ���ÿһ��ͬλ�������ӽ�λ��
			box_e[h] += box[h];
			box_e[h] += g;
			// ��λ���жϣ���Ҫ��λ���ʮ
			g = 0;
			if (box_e[h] >= 10) { box_e[h] -= 10; g = 1; }
			// �˳��ж�
			// ĳ������ʱ����Ҫλ��ǰȫ���㣬���ʾ�����㹻С���Ѿ�Ӱ�첻����Ҫλ��֮ǰ��λ����
			if (box[h] != 0) { k++; }
		}

		// �˳��жϣ����˳��������һ��
		if (k != 0)
		{
			j++;
		}
	}

	// ������û��ѭ����
	flag_start = 0; flag_end = t - 1;
	// ���һ�����㣬�Ѿ�Ӱ�첻����Ҫλ��֮ǰ��λ��
}

// �������ļ��㺯��
void Gary::calculation_num()
{
	int a, flag, i, j;
	a = A;
	while (A / B == 0)
	{
		A *= 10;
	}

	// ��ѭ���ڣ������ 1000 λ
	flag = 0; flag_end = 0;
	j = 0;
	while (j < 1000)
	{
		// ���ԵĽ��
		box_num[j].outnum = A / B;
		// ����
		box_num[j].nestnum = A % B;
		// ������ʮ
		A = box_num[j].nestnum * 10;
		// �ж�ѭ�����Ƿ��ҵ���
		if (flag_end == 0)
		{
			// ����һ�£�����ѭ����������Ϊ�㣬����������������
			// �����֪����ĸΪ B ʱ��ѭ���ڳ�������Ϊ B - 1
			for (i = 0; i < flag; i++)
			{
				if (box_num[i].nestnum == box_num[flag].nestnum || box_num[i].nestnum == 0)
				{
					// ѭ���ڳ���Ϊ flag-i
					flag_start = i;
					flag_end = flag - 1;
					break;
				}
			}
		}
		flag++;
		j++;
	}

	A = a;
}

// �������ƺ���
void Gary::draw_scene()
{
	TCHAR s[25];
	int i, j;
	// ��������
	setbkcolor(WHITE);
	cleardevice();

	// �߻���
	if (draw_mod == 0)
	{
		setlinestyle(PS_SOLID, 1);
		draw_helical_line();
	}
	else if (draw_mod == 1)
	{
		setlinestyle(PS_SOLID, 2);
		draw_walking_line();
	}

	// ���Χ����
	setfillcolor(WHITE);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	line(0, 0, 500, 0);
	line(0, 0, 0, 500);
	line(0, 500, 500, 500);
	fillrectangle(500, 0, 800, 500);
	line(600, 0, 600, 500);
	line(600, 145, 800, 145);
	line(600, 355, 800, 355);
	line(700, 355, 700, 500);

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
			fillcircle(int(boxm[i].posx1), int(boxm[i].posy1), int(boxm[i].r));
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
	}

	// ���ֻ���
	setbkcolor(WHITE);
	settextcolor(BLACK);
	for (i = 0; i < 10; i++)
	{
		_stprintf_s(s, _T("%0.1d"), i);
		outtextxy(boxm[i].posx1 + 40, boxm[i].posy1 - 15, s);
	}

	outtextxy(670, 160, _T("������"));
	outtextxy(620, 370, _T("������"));

	i = 24; j = 30;
	_stprintf_s(s, _T("%0.1d"), A);						outtextxy(boxm[10].posx1 + i, boxm[10].posy1 + j, s);
	_stprintf_s(s, _T("%0.1d"), B);						outtextxy(boxm[11].posx1 + i, boxm[11].posy1 + j, s);
	_stprintf_s(s, _T("%0.1f"), initial_position);		outtextxy(boxm[14].posx1 + i, boxm[14].posy1 + j, s);
	_stprintf_s(s, _T("%0.1f"), linear_velocity);		outtextxy(boxm[15].posx1 + i, boxm[15].posy1 + j, s);
	_stprintf_s(s, _T("%0.1f"), angular_velocity / pi);	outtextxy(boxm[16].posx1 + i, boxm[16].posy1 + j, s);
	_stprintf_s(s, _T("%0.1f"), d);						outtextxy(boxm[17].posx1 + i, boxm[17].posy1 + j, s);
	_stprintf_s(s, _T("%0.1f"), step_size);				outtextxy(boxm[18].posx1 + i, boxm[18].posy1 + j, s);

	FlushBatchDraw();
}

// ���������ߺ���
void Gary::draw_helical_line()
{
	int k;

	double i, posx, posy, r, w;
	i = angular_velocity;
	r = initial_position + linear_velocity * angular_velocity;
	k = 0;
	// r>d �ǻ���ԭ�㣬r>i �ǻ�����ʼλ�õ�
	while (r > d && r > initial_position && k < 1000)
	{
		// ���������߰뾶������СԲ�뾶����������ת�Ƕȣ�����ֱ�������Σ�sin(w)= w
		// �ɼ��ӽ�ԭ��ʱ�᲻׼ȷ����� i ֵ���������߲��ӽ�ԭ��
		w = d / r;
		// �Ƕ���ת
		angular_velocity = angular_velocity - w;
		// �������
		r = initial_position + linear_velocity * angular_velocity;
		// �������
		posx = r * cos(angular_velocity);
		posy = r * sin(angular_velocity);
		// �ɴ�СԲ����
		if (num_mod == 0) { setfillcolor(boxm[box_pi[k]].color);			setlinecolor(boxm[box_pi[k]].color); }
		else if (num_mod == 1) { setfillcolor(boxm[box_e[k]].color);			setlinecolor(boxm[box_e[k]].color); }
		else if (num_mod == 2) { setfillcolor(boxm[box_num[k].outnum].color);	setlinecolor(boxm[box_num[k].outnum].color); }
		fillcircle(int(250 + posx), int(250 + posy), int(d / 2));
		k++;
	}
	angular_velocity = i;
	r = initial_position + linear_velocity * angular_velocity;

	FlushBatchDraw();
}

// �������ߵ�ֱ�ߺ���
void Gary::draw_walking_line()
{
	int i, k, a;
	double w, posx, posy;
	w = 0; posx = 250; posy = 250;

	setlinecolor(BLACK);

	// ����ģʽ
	if (num_mod == 0) { a = 1; }
	else if (num_mod == 1) { a = 1; }
	else if (num_mod == 2) { a = 20; }

	// ����
	for (k = 0; k < a; k++)
	{
		for (i = flag_start; i <= flag_end; i++)
		{
			// �ķ���
			if (num_mod == 0) { w = int(w - 90 + 36 * box_pi[i]) % 360; }
			else if (num_mod == 1) { w = int(w - 90 + 36 * box_e[i]) % 360; }
			else if (num_mod == 2) { w = int(w - 90 + 36 * box_num[i].outnum) % 360; }
			// ������
			line(int(posx), int(posy), int(posx + step_size * cos(w * pi / 180.0)), int(posy + step_size * sin(w * pi / 180.0)));
			// ��������
			posx += step_size * cos(w * pi / 180.0);
			posy += step_size * sin(w * pi / 180.0);
			// Sleep(20); FlushBatchDraw();
		}
	}

	FlushBatchDraw();
}

// ��ɫ�̺���
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
				posy = int(250 - i / D * size * 2.0 + j / D * size * 1.0 + k / D * size * 1.0);
				posx = int(250 + j / D * size * 1.8 - k / D * size * 1.8);
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
				boxm[a].color = getpixel(m.x, m.y);
				exit_palette = 1;
			}
		}
	}

	draw_scene();
	FlushBatchDraw();
}

// ��ʼ������
void Gary::initialization()
{
	// ��ť�ĳ�ʼ��
	num_button = 21;
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
	boxm[10].posx1 = 610; boxm[10].posy1 = 10;	boxm[10].posx2 = 690; boxm[10].posy2 = 70;	boxm[10].mod = 1; boxm[10].text = _T("����");
	boxm[11].posx1 = 710; boxm[11].posy1 = 10;	boxm[11].posx2 = 790; boxm[11].posy2 = 70;	boxm[11].mod = 1; boxm[11].text = _T("��ĸ");
	boxm[12].posx1 = 610; boxm[12].posy1 = 80;	boxm[12].posx2 = 690; boxm[12].posy2 = 140; boxm[12].mod = 1; boxm[12].text = _T("��");
	boxm[13].posx1 = 710; boxm[13].posy1 = 80;	boxm[13].posx2 = 790; boxm[13].posy2 = 140; boxm[13].mod = 1; boxm[13].text = _T("e");
	boxm[14].posx1 = 610; boxm[14].posy1 = 220; boxm[14].posx2 = 690; boxm[14].posy2 = 280; boxm[14].mod = 1; boxm[14].text = _T("��ʼλ��");
	boxm[15].posx1 = 710; boxm[15].posy1 = 220; boxm[15].posx2 = 790; boxm[15].posy2 = 280; boxm[15].mod = 1; boxm[15].text = _T("���ٶ�");
	boxm[16].posx1 = 610; boxm[16].posy1 = 290; boxm[16].posx2 = 690; boxm[16].posy2 = 350; boxm[16].mod = 1; boxm[16].text = _T("���ٶ�");
	boxm[17].posx1 = 710; boxm[17].posy1 = 290; boxm[17].posx2 = 790; boxm[17].posy2 = 350; boxm[17].mod = 1; boxm[17].text = _T("СԲ�뾶");
	boxm[18].posx1 = 610; boxm[18].posy1 = 430; boxm[18].posx2 = 690; boxm[18].posy2 = 490; boxm[18].mod = 1; boxm[18].text = _T("����");
	boxm[19].posx1 = 710; boxm[19].posy1 = 430; boxm[19].posx2 = 790; boxm[19].posy2 = 490; boxm[19].mod = 1; boxm[19].text = _T("�˳�");
	boxm[20].posx1 = 710; boxm[20].posy1 = 360; boxm[20].posx2 = 790; boxm[20].posy2 = 420; boxm[20].mod = 1; boxm[20].text = _T("����");

	// ��һ���Ȼ� �� �������ߣ����ֲ�����ʼ��
	num_mod = 0;
	draw_mod = 0;
	A = 1; B = 3;
	calculation_pi();
	initial_position = 0;
	linear_velocity = 1.5;
	angular_velocity = 30 * pi;
	step_size = 50;
	d = 7;

	// ����
	draw_scene();
}

// �������ӽǺ�������ȡ�û�����
void Gary::move()
{
	// ��궨��
	ExMessage m;
	TCHAR ss[25];
	int i;
	float j;
	exit_move = 0;

	while (exit_move == 0)
	{
		if (peekmessage(&m, EM_MOUSE | EM_KEY))
		{
			// ��������ж�
			if (m.message == WM_LBUTTONDOWN)
			{
				// �ж��Ƿ����˰�ť
				for (i = 0; i < num_button; i++)
				{
					if (boxm[i].mod == 1 && m.x > boxm[i].posx1 && m.y > boxm[i].posy1 && m.x < boxm[i].posx2 && m.y < boxm[i].posy2)
					{
						break;
					}
					else if (boxm[i].mod == 0 && (m.x - boxm[i].posx1) * (m.x - boxm[i].posx1) + (m.y - boxm[i].posy1) * (m.y - boxm[i].posy1) < boxm[i].r * boxm[i].r)
					{
						break;
					}
				}

				// �����ͬģʽ��Χ
				if (m.x > 600 && m.y > 145 && m.x < 800 && m.y < 355) { draw_mod = 0; }
				else if (m.x > 600 && m.y > 355 && m.x < 700 && m.y < 500) { draw_mod = 1; }

				// ���Բ�ΰ�ť
				if (i >= 0 && i < 10)
				{
					draw_palette(i);
				}

				// ������ΰ�ť
				switch (i)
				{
					// ���÷��Ӱ�ť��A
				case 10:
				{
					num_mod = 2;
					InputBox(ss, 10, _T("�������(1 ~ ��ĸ)"));
					_stscanf_s(ss, _T("%d"), &i);
					if (i >= 1 && i < B) { A = i; }
					else { MessageBox(hOut, _T("������󣬲��ڷ�Χ��"), _T("����С���ӵ�����"), MB_OK); }
					calculation_num();
					break;
				}

				// ���÷�ĸ��ť��B
				case 11:
				{
					num_mod = 2;
					InputBox(ss, 10, _T("�����ĸ(���� ~ 9999)"));
					_stscanf_s(ss, _T("%d"), &i);
					if (i > A && i <= 9999) { B = i; }
					else { MessageBox(hOut, _T("������󣬲��ڷ�Χ��"), _T("����С���ӵ�����"), MB_OK); }
					calculation_num();
					break;
				}

				// �� ��ť
				case 12:
				{
					num_mod = 0;
					flag_start = 0;
					flag_end = 999;
					break;
				}

				// e ��ť
				case 13:
				{
					num_mod = 1;
					flag_start = 0;
					flag_end = 999;
					break;
				}

				// ���ó�ʼλ�ð�ť��initial_position
				case 14:
				{
					InputBox(ss, 10, _T("�����ʼλ��(0 ~ 100)"));
					_stscanf_s(ss, _T("%f"), &j); if (j >= 0 && j <= 100) { initial_position = j; }
					else { MessageBox(hOut, _T("������󣬲��ڷ�Χ��"), _T("����С���ӵ�����"), MB_OK); }
					break;
				}

				// �������ٶȰ�ť��linear_velocity
				case 15:
				{
					InputBox(ss, 10, _T("�������ٶ�(0 ~ 100)"));
					_stscanf_s(ss, _T("%f"), &j); if (j >= 0 && j <= 100) { linear_velocity = j; }
					else { MessageBox(hOut, _T("������󣬲��ڷ�Χ��"), _T("����С���ӵ�����"), MB_OK); }
					break;
				}

				// ���ý��ٶȰ�ť��angular_velocity
				case 16:
				{
					InputBox(ss, 10, _T("������ٶ�(0 ~ 100)"));
					_stscanf_s(ss, _T("%f"), &j); if (j >= 0 && j <= 100) { angular_velocity = j * pi; }
					else { MessageBox(hOut, _T("������󣬲��ڷ�Χ��"), _T("����С���ӵ�����"), MB_OK); }
					break;
				}

				// ����СԲ�뾶��ť��d
				case 17:
				{
					InputBox(ss, 10, _T("����СԲ�뾶(0 ~ 100)"));
					_stscanf_s(ss, _T("%f"), &j); if (j >= 0 && j <= 100) { d = j; }
					else { MessageBox(hOut, _T("������󣬲��ڷ�Χ��"), _T("����С���ӵ�����"), MB_OK); }
					break;
				}

				// ���ò�����ť��step_size
				case 18:
				{
					InputBox(ss, 10, _T("���벽��(0 ~ 300)"));
					_stscanf_s(ss, _T("%f"), &j); if (j >= 0 && j <= 300) { step_size = j; }
					else { MessageBox(hOut, _T("������󣬲��ڷ�Χ��"), _T("����С���ӵ�����"), MB_OK); }
					break;
				}

				// �˳���ť
				case 19:
				{
					exit_move = 1;
					exit_carry = 1;
					break;
				}

				// ���ð�ť
				case 20:
				{
					exit_move = 1;
					break;
				}

				default:break;
				}

				// ����
				draw_scene();

			}
		}
	}
}

// ������
void Gary::carry()
{
	// ���ڶ���
	hOut = initgraph(801, 501);
	SetWindowText(hOut, _T("�����׵�������"));
	// ���̿���
	exit_carry = 0;

	calculation_pi();
	calculation_e();

	BeginBatchDraw();
	while (exit_carry == 0)
	{
		initialization();
		move();
	}
	EndBatchDraw();
	closegraph();
}

// ������
int main(void)
{
	Gary G;
	G.carry();
	return 0;
}

