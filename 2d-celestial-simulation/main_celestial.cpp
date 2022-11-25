////////////////////////////////////////////////////////
// �������ƣ���ά����ģ��
// �������ߣ�Visual Studio 2019��EasyX 20190529(beta)
// ��Ŀ���ͣ�Windows Consoal Application
// �������ߣ���Զ�Ĳ��
// ������QQ��2237505658
//    Email��2237505658@qq.com
// �������ڣ�2020-1-6
// ����޸ģ�2020-1-6
//
#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include <list>
#include <vector>
#include <graphics.h>

using std::wstring;
using std::list;
using std::vector;
using std::to_wstring;
using std::cout;
using std::wcout;
using std::endl;

 double PI = 3.14159265358;
 double G = 0.1;
 double T = 0.5;
 int WIDTH = 960;
 int HEIGHT = 640;
 int BODYNUMS = 200;			// ������Ĭ������
 int MAXLENGTH = 100;			// �������󳤶�

// ������
class Body
{
private:
	double x;
	double y;
	double m;
	double r;
	double vx;
	double vy;
	COLORREF color;
	int name;

	list<double> listx;					// ������������� x
	list<double> listy;					// ������������� y
public:
	Body();
	Body(double X, double Y, double M, double VX, double VY, COLORREF C, const int N);

	double CaiR();
	void Move();
	void Show()const;
	void ShowPath()const;
	wstring Message()const;
	COLORREF PutColor()const ;
	friend void Gravitation(Body& bthis, Body& other);
};


int Choose();
void MultiBody(vector<Body>& bodys);
void ThreeBody(vector<Body>& bodys);
void Draw(vector<Body>& p, const int nums);
void FpsTime(const time_t* t0, time_t* t1, const time_t* t2);



int main()
{
	srand(time(nullptr) & 0xFFFFFFFF);		// �����������
	initgraph(WIDTH, HEIGHT);
	while (true)
	{
		vector<Body> bodys;					// ��������
		int BodyNums = 0;					// ��������
		int mode = -1;
		mode = Choose();
		if (mode == 0)
		{
			closegraph();					// �رմ���
			return 0;						// �˳�����
		}
		else if (mode == 1)
		{
			BodyNums = BODYNUMS;			// ��������Ϊ����
			MultiBody(bodys);				// ��ʼ��������
		}
		else if (mode == 2)
		{
			BodyNums = 3;					// ��������Ϊ����
			ThreeBody(bodys);				// ��ʼ������
		}

		BeginBatchDraw();
		const time_t start = time(nullptr);
		time_t justnow = time(nullptr);
		time_t now = time(nullptr);

		MOUSEMSG Mouse = GetMouseMsg();
		while (true)
		{
			if (MouseHit())
			{
				Mouse = GetMouseMsg();
				if (Mouse.mkRButton && Mouse.x > 0 && Mouse.x < WIDTH && Mouse.y>0 && Mouse.y < HEIGHT)
					break;					// ��⵽�����ϢΪ�Ҽ����£����ڻ�ͼ�����ڣ����˳�
			}

			Draw(bodys, BodyNums);
			now = time(nullptr);
			FpsTime(&start, &justnow, &now);
			FlushBatchDraw();
			Sleep(10);
		}
		EndBatchDraw();
	}
	return 0;
}



Body::Body()
{
	x = rand() % WIDTH;
	y = rand() % HEIGHT;
	m = rand() % 3000 + 1000.0;
	r = CaiR();
	vx = (rand() & 1 ? 1 : -1) * ((rand() % 401) / 200.0);	// �ٶ� -2.00 ~ +2.00
	vy = (rand() & 1 ? 1 : -1) * ((rand() % 401) / 200.0);
	color = RGB(rand() % 256, rand() % 256, rand() % 256);	// ������� RGB ��ɫ
	name = rand() % 200 + 100;
}

Body::Body(double X, double Y, double M, double VX, double VY, COLORREF C, const int N)
:m(M), vx(VX), vy(VY), x(X), y(Y), color(C), name(N)
{
	r = CaiR();												// ��ʼ���뾶
}


double Body::CaiR()									// ����뾶
{
	return pow((m / PI) * (3.0 / 4.0), 1.0 / 3.0);			// pow(sqrt(3m/4PI),1/3)
}

void Body::Show()const
{
	if (m > 0)												// ����Ϊ 0 �Ĳ���ʾ
	{
		setfillcolor(color);								// �������ɫ,����������ɫ
		// ������
		solidcircle(static_cast<int>(x), static_cast<int>(y), static_cast<int>(r));
		setbkmode(TRANSPARENT);								// ���屳��͸��
		settextstyle(14, 0, L"����");						// ����������ʽ
		settextcolor(WHITE);								// ����������ɫ
		// ��ʾ��������
		outtextxy(static_cast<int>(x), static_cast<int>(y), to_wstring(name).c_str());
	}
}

void Body::ShowPath()const
{
	if (m > 0)
	{
		setlinecolor(color);								// ���û�����ɫ
		auto beginx = listx.begin();						// ��ʼ��������
		auto beginy = listy.begin();
		double ax = *beginx;
		double ay = *beginy;
		double bx = 0;
		double by = 0;
		for (vector<double>::size_type i = 0; i < listx.size(); i++)
		{
			ax = *beginx;
			ay = *beginy;
			bx = 0;
			by = 0;
			if (i + 1 == listx.size())
			{
				bx = *beginx;
				by = *beginy;
			}
			else
			{
				bx = *(++beginx);
				by = *(++beginy);

				setfillstyle(BS_SOLID);
				// �������
				line(static_cast<int>(ax), static_cast<int>(ay), static_cast<int>(bx), static_cast<int>(by));
			}
		}
	}
}

void Body::Move()
{
	x += vx * T;						// �ƶ�����
	y += vy * T;

	listx.push_back(x);					// ��¼λ�ã�������β���
	listy.push_back(y);
	if (listx.size() > MAXLENGTH)		// ���������󳤶ȣ�������ͷɾ��Ԫ��
	{
		listx.pop_front();
		listy.pop_front();
	}
}

wstring Body::Message()const
{
	wstring str(L"Body #");
	str += to_wstring(name);
	str += wstring(L" Mass: ");
	str += to_wstring((int)m);

	return str;
}

COLORREF Body::PutColor()const 
{
	return color;
}

void Gravitation(Body& bthis, Body& other)			// �������໥����
{
	if (bthis.m > 0 && other.m > 0)							// ��������Ϊ 0 �ķ�������
	{														// �����ж� s<sqrt((x1-x2)^2+(y1-y2)^2) û����ײ
		if (bthis.r + other.r < sqrt(pow((other.x - bthis.x), 2) + pow((other.y - bthis.y), 2)))
		{
			// ax=(G*m2)/(r^2)*cos(atan((y1-y2)/(x1-x2)))
			const double ax = ((G * other.m) / (pow((other.x - bthis.x), 2) + pow((other.y - bthis.y), 2)))
				* cos(atan(fabs((other.y - bthis.y) / (other.x - bthis.x))));

			// ay=(G*m2)/(r^2)*sin(atan((y1-y2)/(x1-x2)))
			const double ay = ((G * other.m) / (pow((other.x - bthis.x), 2) + pow((other.y - bthis.y), 2)))
				* sin(atan(fabs((other.y - bthis.y) / (other.x - bthis.x))));

			if (other.x > bthis.x)
				bthis.vx = bthis.vx + ax * T;				// vx=v0+axt
			else if (other.x < bthis.x)
				bthis.vx = bthis.vx - ax * T;				// vx=v0-axt
			else
				bthis.vx = bthis.vx;						// vx=vx0

			if (other.y > bthis.y)
				bthis.vy = bthis.vy + ay * T;				// vy=v0+ayt
			else if (other.y < bthis.y)
				bthis.vy = bthis.vy - ay * T;				// vy=v0-ayt
			else
				bthis.vy = bthis.vy;						// vy=vy0
		}
		else												// ������ײ
		{
			if (bthis.m >= other.m)							// bthis ���� other
			{
				// ������ϵ v=(m1*v1+m2*v2)/(m1+m2)
				bthis.vx = (bthis.m * bthis.vx + other.m * other.vx) / (bthis.m + other.m);
				bthis.vy = (bthis.m * bthis.vy + other.m * other.vy) / (bthis.m + other.m);
				bthis.m += other.m;							// ��������
				bthis.r = bthis.CaiR();						// ���°뾶

				other.m = 0;								// ������ m,r,v ����
				other.r = 0;
				other.vx = 0;
				other.vy = 0;
			}
			else											// other ���� bthis
			{

				other.vx = (bthis.m * bthis.vx + other.m * other.vx) / (bthis.m + other.m);
				other.vy = (bthis.m * bthis.vy + other.m * other.vy) / (bthis.m + other.m);
				other.m += bthis.m;
				other.r = other.CaiR();

				bthis.m = 0;
				bthis.r = 0;
				bthis.vx = 0;
				bthis.vy = 0;
			}
		}
	}
}



int Choose()
{
	cleardevice();											// ����
	settextcolor(0x5555FF);
	settextstyle(14, 0, L"����");
	outtextxy(190, 620, L"��ʾ���������ѡ�� �ڶ�����ģ���£���������Ĭ��Ϊ200�� ����ģ�������Ҽ��˳�ģ��");

	setlinecolor(WHITE);
	settextcolor(WHITE);
	settextstyle(20, 0, L"����");
	rectangle(120, 280, 320, 380);							// ���߿�
	rectangle(380, 280, 580, 380);
	rectangle(640, 280, 840, 380);
	outtextxy(420, 140, L"��ά����ģ��");
	outtextxy(180, 320, L"����ģ��");
	outtextxy(430, 320, L"������ģ��");
	outtextxy(720, 320, L"�˳�");

	MOUSEMSG Mouse = GetMouseMsg();
	while (true)
	{
		Mouse = GetMouseMsg();
		if (Mouse.mkLButton)								// ����Ƿ���
		{													// ����ģ��
			if (Mouse.x >= 100 && Mouse.x <= 300 && Mouse.y >= 300 && Mouse.y <= 420)
			{
				FlushMouseMsgBuffer();						// ��������Ϣ����
				return 2;
			}
			// ������ģ��
			if (Mouse.x >= 360 && Mouse.x <= 560 && Mouse.y >= 300 && Mouse.y <= 420)
			{
				FlushMouseMsgBuffer();						// ��������Ϣ����
				return 1;
			}
			// �˳�
			if (Mouse.x >= 620 && Mouse.x <= 820 && Mouse.y >= 300 && Mouse.y <= 420)
			{
				setfillcolor(WHITE);
				settextcolor(RED);
				setbkmode(TRANSPARENT);						// ����͸��
				settextstyle(20, 0, L"����");
				solidroundrect(320, 260, 640, 420, 80, 100);// ������Բ�Ǿ���
				outtextxy(440, 330, L"���˳�!");
				Sleep(1000);
				closegraph();								// �رմ���
				return 0;
			}
		}
	}
}


void MultiBody(vector<Body>& bodys)							// ��ʼ��������
{
	for (int i = 0; i < BODYNUMS; i++)
	{														// ��ʼ������
		bodys.push_back(Body(rand() % WIDTH, rand() % HEIGHT, rand() % 500 + 10.0, 0, 0,
			COLORREF(RGB(rand() % 256, rand() % 256, rand() % 256)), i));
	}
	// ��������
	bodys.at(0) = Body(WIDTH / 2, HEIGHT / 2, 20000, 0, 0, RED, 0);
}


void ThreeBody(vector<Body>& bodys)							// ��ʼ������
{
	// ����ٶ�-1.50~+1.50
	const double temp_vx = (rand() & 1 ? 1 : -1) * (rand() % 151 / 100.0);
	const double temp_vy = (rand() & 1 ? 1 : -1) * (rand() % 151 / 100.0);
	const int temp_m = rand() % 5001 + 5000;				// �������5000~10000

	// ��������������������ٶȴ�С��ȣ��ٶȷ����෴����ϵͳ�ܶ���Ϊ0
	// ���ǣ���Ϊ���������к�����ϵͳ�ܶ�����Ϊ0
	// ͬ���ģ��ڶ�����ģ���У���ʼʱ��ϵͳ�ܶ���Ϊ0
	// ��ֻ�����������������£�Ҳ���������к�ϵͳ�ܶ�����Ϊ0

	// ���λ�ã���������ɫ
	bodys.push_back(Body(rand() % (WIDTH - 240) + 120.0, rand() % (HEIGHT - 240) + 120.0, rand() % 5001 + 5000.0, 0, 0,
		COLORREF(RGB(rand() % 256, rand() % 256, rand() % 256)), 0));

	bodys.push_back(Body(rand() % (WIDTH - 240) + 120.0, rand() % (HEIGHT - 240) + 120.0, temp_m, temp_vx, temp_vy,
		COLORREF(RGB(rand() % 256, rand() % 256, rand() % 256)), 1));

	bodys.push_back(Body(rand() % (WIDTH - 240) + 120.0, rand() % (HEIGHT - 240) + 120.0, temp_m, -temp_vx, -temp_vy,
		COLORREF(RGB(rand() % 256, rand() % 256, rand() % 256)), 2));
}


void Draw(vector<Body>& p, const int nums)
{
	cleardevice();
	settextcolor(WHITE);									// ����������ɫ
	int num = 1;
	for (int i = 0; i < nums; i++)
	{
		p.at(i).Show();										// ������
		p.at(i).Move();										// �ƶ�
		p.at(i).ShowPath();									// ���켣��
		if (p.at(i).CaiR() > 0)								// �������������(�뾶)����ʾ��Ϣ
		{
			settextcolor(p.at(i).PutColor());
			// ��ʾ������Ϣ
			outtextxy(0, num * 12, p.at(i).Message().c_str());
			num++;
		}

		for (int j = 0; j < nums; j++)
		{
			if (i != j)										// �����Լ���������
				Gravitation(p.at(i), p.at(j));				// ������֮���໥����
		}
	}
}


void FpsTime(const time_t* t0, time_t* t1, const time_t* t2)// ������ʾFPS
{
	if (!t0 || !t1 || !t2)									// ��ָ����
		return;
	static int FPS = 0;										// ������ʾ��FPS
	static int fps = 0;										// ����ʹ�õ�fps
	static wstring fpsTime;

	if (*t2 - *t1 == 1)										// ��ʼ����ֵ
	{
		FPS = ++fps;
	}

	fpsTime = L"FPS: ";
	fpsTime += to_wstring(FPS);
	fpsTime += L" ����ʱ��: ";
	fpsTime += to_wstring(*t2 - *t0);
	fpsTime += L"s";
	settextcolor(LIGHTMAGENTA);
	outtextxy(0, 0, fpsTime.c_str());

	if (*t2 - *t1 == 1)
	{
		fps = 0;
		*t1 = time(nullptr);
	}
	else
	{
		fps++;
	}
}