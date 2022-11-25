/*
��Ŀ���ƣ�
RollingBall
���ߣ�
tzdhu.z@qq.com (1926594835)
���뻷����
Visual Studio 2017��EasyX_20190219(beta)
�������ڣ�
2019-2-2
����޸ģ�
2019-2-23
��Ŀ���ܣ�
�������ɵ������ģʽ RollingBall ���м̳� BallAndPlank
protected ������������ʻ������ݳ�Ա
ģ����ɫ�����λ�����
�����ɳ�ʼ�������С���ƣ���ѧ�߿����и���
��Ȩ������
��������ȫ���������������漰�κ���Ȩ��Ϊ��������ѧϰ
*/

// ͷ�ļ�
#include <graphics.h>
#include <conio.h>
#include <ctime>



// ȫ�ֱ���
const COLORREF BKCOLOR = BLACK;															// ��ͼ���ڱ�����ɫ
const int max_x = 640;																	// ��ͼ�������ؿ��
const int max_y = 480;																	// ��ͼ�������ظ߶�
const int max_smx = GetSystemMetrics(SM_CXSCREEN);										// ������Ļ���ؿ��
const int max_smy = GetSystemMetrics(SM_CYSCREEN);										// ������Ļ���ظ߶�
const int inverse_operate_score = 600;													// ���������������
static IMAGE img_start(80, 40), id_start(80, 40), img_exit(80, 40), id_exit(80, 40);	// ���ڰ�ťЧ���� IMAGE



////////////////////////////////////////////////////
// С���ľ����
class BallAndPlank
{
	//С��ṹ��
	typedef struct BALL
	{
		int ball_x;						// С������λ�� x
		int ball_y;						// С������λ�� y
	}Ball;

	//ľ��ṹ��
	typedef struct PLANK
	{
		int plank_x;					// ľ�����λ�� x
		int plank_y;					// ľ��λ�� y
		int plank_len;					// ľ�峤��
		COLORREF plank_color;			// ľ����ɫ
		int thorn_x;					// ������λ�� x
		bool is_thorn;					// ľ���Ƿ��м��
	}Plank;

public:
	// ���캯����ʼ������
	BallAndPlank()
	{
		// С��
		ball_r = 4;
		ball_ddx = 1;
		ball_dx_min = 0;
		ball_dx_max = 8;
		left_right = STOP;
		ball_dx = ball_dx_min;
		ball_dy = ball_dx_min;
		ball_color = RGB(255, 0, 0);

		// ľ��
		plank_dy = 1;
		plank_len_min = 50;
		plank_len_max = 150;
		thorn_len = 32;
		thorn_h = 4;
		plank_gap = (max_y - 1) / plank_num;
	}

	~BallAndPlank()
	{
		// δ����
	}

	// С����ɫ����С��
	void DrawBall(int x, int y)
	{
		setfillcolor(ball_color);
		solidcircle(x, y, ball_r);
	}

	// ������ɫ���С��
	void CleanBall(int x, int y)
	{
		setfillcolor(BKCOLOR);
		solidcircle(x, y, ball_r);
	}

	bool IsThorn()
	{
		return (rand() % 1000 > 600) ? true : false;
	}

	// ľ����ɫ����ľ��
	void DrawPlank()
	{
		for (int i = 0; i < plank_num; i++)
		{
			setlinecolor(plank[i].plank_color);
			line(plank[i].plank_x, plank[i].plank_y, plank[i].plank_x + plank[i].plank_len, plank[i].plank_y);
			if (plank[i].is_thorn == true)
			{
				for (int j = plank[i].thorn_x; j < plank[i].thorn_x + thorn_len; j += 2 * thorn_h)
				{
					line(j, plank[i].plank_y, j + thorn_h, plank[i].plank_y - thorn_h - 1);
					line(j + thorn_h, plank[i].plank_y - thorn_h - 1, j + 2 * thorn_h, plank[i].plank_y);
				}
			}
		}
	}

	// ������ɫ���ľ��
	void CleanPlank()
	{
		setlinecolor(BKCOLOR);
		for (int i = 0; i < plank_num; i++)
		{
			line(plank[i].plank_x, plank[i].plank_y, plank[i].plank_x + plank[i].plank_len, plank[i].plank_y);
			if (plank[i].is_thorn == true)
			{
				for (int j = plank[i].thorn_x; j < plank[i].thorn_x + thorn_len; j += 2 * thorn_h)
				{
					line(j, plank[i].plank_y, j + thorn_h, plank[i].plank_y - thorn_h - 1);
					line(j + thorn_h, plank[i].plank_y - thorn_h - 1, j + 2 * thorn_h, plank[i].plank_y);
				}
			}
		}
	}

protected:												// ��������������������ݳ�Ա
	// С������
	enum Left_Right { STOP, LEFT, RIGHT };				// ö��С�����ҷ���
	int ball_r;											// С��뾶
	int ball_ddx;										// ����ΪС����ٶ�
	int ball_dx_min;									// С�� x ������С����
	int ball_dx_max;									// С�� x ������󲽳�
	int left_right;										// С�����ҷ���
	int ball_dx;										// ����ΪС�� x �����ٶ�
	int ball_dy;										// ����ΪС�� y �����ٶ�
	COLORREF ball_color;								// С����ɫ
	Ball ball;											// С��ṹ����

	// ľ������
	enum Plank_Num { plank_num = 7 };					// ö�ٳ�ʼ��ľ������
	int plank_dy;										// ����Ϊľ���ٶ�
	int plank_len_min;									// ľ����С����
	int plank_len_max;									// ľ����󳤶�
	int plank_gap;										// ľ����
	int thorn_len;										// ��̳���
	int thorn_h;										// ��̸߶�
	Plank plank[plank_num];								// ľ��ṹ��������
};



////////////////////////////////////////////////////
// �������ģʽ RollingBall������
class RollingBall : public BallAndPlank
{
public:
	~RollingBall()
	{
		// δ����
	}

	// ��ȡ����ָ��
	static RollingBall *GetInstance()
	{
		static RollingBall RB;
		return &RB;
	}

	// ��ʼǰ���ܽ���
	void Introduce()
	{
		setbkcolor(BKCOLOR);
		cleardevice();
		settextcolor(LIGHTMAGENTA);
		settextstyle(50, 0, _T("����"));
		outtextxy((max_x - textwidth(_T("RollingBall"))) / 2, max_y / 5, _T("RollingBall"));
		settextcolor(GREEN);
		settextstyle(25, 0, _T("����"));
		outtextxy((max_x - textwidth(_T("ESC�˳�,�ո���ͣ"))) / 2, max_y / 5 * 2 + 20, _T("ESC�˳�,�ո���ͣ"));
		outtextxy((max_x - textwidth(_T("���Ʒ���:���ҷ����,AD,������Ҽ�"))) / 2, max_y / 5 * 2 + 60, _T("���Ʒ���:���ҷ����,AD,������Ҽ�"));

		SetWorkingImage(&img_start);
		setbkcolor(LIGHTGRAY);
		cleardevice();
		settextcolor(BROWN);
		settextstyle(25, 0, _T("����"));
		outtextxy((80 - textwidth(_T("��ʼ"))) / 2, (40 - textheight(_T("��ʼ"))) / 2, _T("��ʼ"));

		SetWorkingImage(&id_start);
		setbkcolor(DARKGRAY);
		cleardevice();
		settextcolor(BROWN);
		settextstyle(25, 0, _T("����"));
		outtextxy((80 - textwidth(_T("��ʼ"))) / 2, (40 - textheight(_T("��ʼ"))) / 2, _T("��ʼ"));

		SetWorkingImage(&img_exit);
		setbkcolor(LIGHTGRAY);
		cleardevice();
		settextcolor(BROWN);
		settextstyle(25, 0, _T("����"));
		outtextxy((80 - textwidth(_T("�˳�"))) / 2, (40 - textheight(_T("�˳�"))) / 2, _T("�˳�"));

		SetWorkingImage(&id_exit);
		setbkcolor(DARKGRAY);
		cleardevice();
		settextcolor(BROWN);
		settextstyle(25, 0, _T("����"));
		outtextxy((80 - textwidth(_T("�˳�"))) / 2, (40 - textheight(_T("�˳�"))) / 2, _T("�˳�"));

		SetWorkingImage();
		int yy = max_y / 4 * 3;
		int exit_x = max_x / 2 - 200;
		int start_x = max_x / 2 + 120;
		putimage(start_x, yy, &img_start);
		putimage(exit_x, yy, &img_exit);

		// ����Ƿ�����ذ�ť������
		MOUSEMSG msg;
		bool selected = false;
		while (!selected)
		{
			while (MouseHit())
			{
				msg = GetMouseMsg();

				if ((msg.x >= start_x && msg.x <= start_x + 80 && msg.y >= yy && msg.y <= yy + 40 && msg.uMsg == WM_LBUTTONDOWN) || GetAsyncKeyState(VK_RETURN) & 0x8000)
				{
					putimage(start_x, yy, &id_start);
					Sleep(200);
					putimage(start_x, yy, &img_start);
					Sleep(100);
					selected = true;
					break;
				}
				else if ((msg.x >= exit_x && msg.x <= exit_x + 80 && msg.y >= yy && msg.y <= yy + 40 && msg.uMsg == WM_LBUTTONDOWN) || GetAsyncKeyState(VK_ESCAPE) & 0x8000)
				{
					putimage(exit_x, yy, &id_exit);
					Sleep(200);
					putimage(exit_x, yy, &img_exit);
					Sleep(100);
					exit(0);
				}
			}

			Sleep(16);
		}
	}

	// ��ʼ����Ϸ����
	void Initialize()
	{
		setbkcolor(BKCOLOR);
		cleardevice();
		setlinecolor(DARKGRAY);
		line(0, 0, 0, max_y - 1);
		line(max_y, 0, max_y, max_y - 1);
		line(0, 0, max_y - 1, 0);
		line(0, max_y - 1, max_y - 1, max_y - 1);

		for (int i = 0; i < max_y; i += 2 * die_top)
		{
			line(i, 0, i + die_top, die_top);
			line(i + die_top, die_top, i + 2 * die_top, 0);
		}

		for (int i = 0; i < plank_num; i++)
		{
			plank[i].plank_y = (i + 1) * plank_gap;
			plank[i].plank_len = rand() % (plank_len_max - plank_len_min) + plank_len_min + 1;
			plank[i].plank_x = rand() % (max_y - plank[i].plank_len);
			plank[i].plank_color = HSVtoRGB(float(rand() % 360), float(1.0), float(1.0));
			plank[i].is_thorn = IsThorn();
			if (plank[i].is_thorn == true)
				plank[i].thorn_x = plank[i].plank_x + rand() % (plank[i].plank_len - thorn_len);
		}

		plank[3].is_thorn = false;
		ball.ball_x = plank[3].plank_x + plank[3].plank_len / 2;
		ball.ball_y = plank[3].plank_y - 1 - ball_r;
		DrawBall(ball.ball_x, ball.ball_y);
		DrawPlank();
		Sleep(sleep_time);
	}

	// ����Ƿ�����
	bool IsDead()
	{
		if (ball.ball_y <= die_top + ball_r || ball.ball_y >= max_y - 1 - ball_r || is_dead)
		{
			is_dead = true;
			return true;
		}
		else
			return false;
	}

	// ��ӡ����,�ٶȼ��Ƿ����������
	void PrintScore()
	{
		settextcolor(RED);
		settextstyle(16, 0, _T("����"));
		score = time_num / 5;
		TCHAR str[20];
		_stprintf_s(str, _T("��ǰ�÷�: %d"), score);
		outtextxy(max_y + 5, max_y / 6 * 5 + 10, str);

		if (score < 50)	plank_dy = 1;
		else if (score < 200)	plank_dy = 2;
		else if (score < 500)	plank_dy = 3;
		else if (score < 1000)	plank_dy = 4;
		else if (score < 1500)	plank_dy = 5;
		else					plank_dy = 6;

		_stprintf_s(str, _T("��ǰ�ٶ�: %d/6"), plank_dy);
		outtextxy(max_y + 5, max_y / 2 - 10, str);
		if (score > inverse_operate_score)
			outtextxy(max_y + 5, max_y / 11, _T("������� �ѿ���"));
		else
			outtextxy(max_y + 5, max_y / 11, _T("������� δ����"));
	}

	// ��ESC����ʱ��ʾ���շ���
	void Finish()
	{
		if (is_dead)
		{
			TCHAR str[50];
			_stprintf_s(str, _T("\t     �������յ÷�Ϊ: %d\t\t"), score);
			MessageBox(GetHWnd(), str, _T("��Ϸ����"), MB_OK);
		}
	}

	// ��Ϸ���д���
	void GameRunning()
	{
		// ���С���ľ��
		CleanBall(ball.ball_x, ball.ball_y);
		CleanPlank();

		// ����ľ��λ��
		for (int i = 0; i < plank_num; i++)
			plank[i].plank_y -= plank_dy;

		// ��ľ���Ƿ���ʧ���� ������βľ��
		if (plank[0].plank_y < die_top + ball_r + 1)
		{
			for (int i = 0; i < plank_num - 1; i++)
				plank[i] = plank[i + 1];
			plank[plank_num - 1].plank_y = (plank_num)* plank_gap;
			plank[plank_num - 1].plank_len = rand() % (plank_len_max - plank_len_min) + plank_len_min + 1;
			plank[plank_num - 1].plank_x = rand() % (max_y - plank[plank_num - 1].plank_len);
			plank[plank_num - 1].plank_color = HSVtoRGB(float(rand() % 360), float(1.0), float(1.0));
			plank[plank_num - 1].is_thorn = IsThorn();
			if (plank[plank_num - 1].is_thorn == true)
				plank[plank_num - 1].thorn_x = plank[plank_num - 1].plank_x + rand() % (plank[plank_num - 1].plank_len - thorn_len);
		}

		// ����С������ x λ��(�Ӽ���Ч��)
		if ((GetAsyncKeyState(VK_LEFT) & 0x8000) || (GetAsyncKeyState('A') & 0x8000) || (GetAsyncKeyState(VK_LBUTTON) & 0x8000))
		{
			if (score < inverse_operate_score)
			{
				if (left_right == LEFT)
					ball_dx = (ball_dx += ball_ddx) > ball_dx_max ? ball_dx_max : ball_dx;
				else
				{
					ball_dx = ball_dx_min;
					left_right = LEFT;
				}
				ball.ball_x = (ball.ball_x -= ball_dx) < ball_r ? ball_r : ball.ball_x;
			}
			else
			{
				if (left_right == RIGHT)
					ball_dx = (ball_dx += ball_ddx) > ball_dx_max ? ball_dx_max : ball_dx;
				else
				{
					ball_dx = ball_dx_min;
					left_right = RIGHT;
				}
				ball.ball_x = (ball.ball_x += ball_dx) > (max_y - 1 - ball_r) ? max_y - 1 - ball_r : ball.ball_x;
			}
		}
		else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) || (GetAsyncKeyState('D') & 0x8000) || (GetAsyncKeyState(VK_RBUTTON) & 0x8000))
		{
			if (score > inverse_operate_score)
			{
				if (left_right == LEFT)
					ball_dx = (ball_dx += ball_ddx) > ball_dx_max ? ball_dx_max : ball_dx;
				else
				{
					ball_dx = ball_dx_min;
					left_right = LEFT;
				}
				ball.ball_x = (ball.ball_x -= ball_dx) < ball_r ? ball_r : ball.ball_x;
			}
			else
			{
				if (left_right == RIGHT)
					ball_dx = (ball_dx += ball_ddx) > ball_dx_max ? ball_dx_max : ball_dx;
				else
				{
					ball_dx = ball_dx_min;
					left_right = RIGHT;
				}
				ball.ball_x = (ball.ball_x += ball_dx) > (max_y - 1 - ball_r) ? max_y - 1 - ball_r : ball.ball_x;
			}
		}
		else
		{
			ball_dx -= ball_ddx;
			if (ball_dx > ball_dx_min)
			{
				if (left_right == LEFT)
					ball.ball_x = (ball.ball_x -= ball_dx) < ball_r ? ball_r : ball.ball_x;
				else if (left_right == RIGHT)
					ball.ball_x = (ball.ball_x += ball_dx) > (max_y - 1 - ball_r) ? max_y - 1 - ball_r : ball.ball_x;
			}
			else
			{
				ball_dx = ball_dx_min;
				left_right = STOP;
			}
		}

		// ����С������ y λ��(����Ч��)
		int ii = 0;	// ����ȷ��С��λ���Ŀ�ľ���Ϸ�
		while (ball.ball_y - plank_dy > plank[ii].plank_y - 1 - ball_r)
			ii++;

		if (ii < plank_num &&
			ball.ball_x >= plank[ii].plank_x && ball.ball_x <= plank[ii].plank_x + plank[ii].plank_len
			&& (ball.ball_y - plank_dy == plank[ii].plank_y - 1 - ball_r || ball.ball_y >= plank[ii].plank_y - 1 - ball_r))
		{
			ball.ball_y = plank[ii].plank_y - 1 - ball_r;
			ball_dy = ball_dx_min;
		}
		else
		{
			ball_dy = (ball_dy += ball_ddx) > ball_dx_max ? ball_dx_max : ball_dy;
			ball.ball_y += ball_dy;
			if (ii < plank_num &&
				ball.ball_x >= plank[ii].plank_x && ball.ball_x <= plank[ii].plank_x + plank[ii].plank_len && ball.ball_y >= plank[ii].plank_y - 1 - ball_r)
			{
				ball.ball_y = plank[ii].plank_y - 1 - ball_r;
				ball_dy = ball_dx_min;
			}
			else if (ball.ball_y > max_y - 1 - ball_r)
				ball.ball_y = max_y - 1 - ball_r;
		}

		// �ж�С���Ƿ������
		if (ball.ball_x >= plank[ii].thorn_x - ball_r / 2 && ball.ball_x <= plank[ii].thorn_x + thorn_len + ball_r / 2
			&& ball.ball_y == plank[ii].plank_y - 1 - ball_r && plank[ii].is_thorn)
			is_dead = true;

		// ����ľ���С��
		DrawPlank();
		DrawBall(ball.ball_x, ball.ball_y);
		FlushBatchDraw();
		time_num++;

		// ��ӡ����,�ٶȼ��Ƿ����������
		PrintScore();
		Sleep(sleep_time);
	}

private:
	// ���캯����ʼ������
	RollingBall()
	{
		score = 0;
		die_top = 5;
		time_num = 0;
		sleep_time = 20;
		is_dead = false;
	}

	RollingBall(const RollingBall &rb) {}							// ��ֹ��������
	RollingBall &operator = (const RollingBall &rb) {}				// ��ֹ��ֵ����
	int sleep_time;													// ��Ϸˢ��ʱ����
	int time_num;													// ��¼��Ϸˢ�´���
	int die_top;													// �������λ��
	int score;														// ��¼����
	bool is_dead;													// �Ƿ�����
};



////////////////////////////////////////////////////
// main ������
int main()
{
	initgraph(max_x, max_y, NOMINIMIZE);
	srand((unsigned)time(NULL));

	// ��ȡ����ָ��
	RollingBall *rb = RollingBall::GetInstance();

	rb->Introduce();
	rb->Initialize();
	BeginBatchDraw();

	while (!(GetAsyncKeyState(VK_ESCAPE) & 0x8000))
	{
		rb->GameRunning();
		if (rb->IsDead())
			break;
		if (_kbhit() && _getwch() == ' ')
			_getwch();
	}

	EndBatchDraw();
	rb->Finish();

	closegraph();
	return 0;
}