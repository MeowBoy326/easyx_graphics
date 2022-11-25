// ��Ŀ����		������ת��̬
// ����			����1704
// email		1479245050@qq.com
// ��ϵ��ʽ		qq 1479245050
// ����			����ά�ռ�ĵ�ͶӰ����άƽ�棬������ά���������ת���Ӿ�ʢ��
//				��ʱ������㣬�Ժ�Ҫ�޸ĵĻ���Ӧ����2019���6���ˡ�
// ���뻷��		win10 64λ + vs2017 + easyx��ver: 20180727(beta)
//
#include <graphics.h>
#include <math.h>

#define		Db_x				640
#define		Db_y				640 
#define		center_x			Db_x/2
#define		center_y			Db_y/2
#define		square_root_two		1.4142135623731
#define		square_root_three	1.7320508075689
#define     square_root_six		2.4494897427832
#define		PI					3.1415926535898
#define		cubenum				29						// ����������
#define		LineCOLOR			BLACK
#define		bkCOLOR				WHITE
#define		turnrate			3						// ������֮����ת�ȴ�
#define		Stardelay			800
#define		Enddelay			1000
#define		FPS					50						// ֡��
#define		sidegap				8						// ������߲�


///////////////////////
// �ṹ����

// ������ά��
class POINT3D
{
public:
	double x, y, z;
	POINT3D() {}
	POINT3D(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	POINT3D(POINT3D &P) {
		x = P.x;
		y = P.y;
		z = P.z;
	}
private:
};

//	����������
struct  Cube
{
	double		side_length;	// �߳�
	POINT3D P[8];				// ��ǰ����
	POINT3D tP[8];				// ��ʼ����
	POINT	p[8];				// ͶӰ����
	int		taking;				// �Ƿ��ڿ����˶� 0��1�� ��ʼΪ1 �˶�����Ϊ0
	int		shoptime;			// ��ͣʱ��
	int		haddone;			// �����֡������ FPSֵ ֹͣ taking��Ϊ0
}cube[cubenum];					// cubenum��	�߳���Ϊ10 ����10
int end;						// 0Ϊ��ʼֵ������������ֹͣ��end��Ϊ1
int temp;						// ��ʱ���������������



///////////////////////
// ��������

// ���ܺ���
POINT projection(POINT3D &P3);								// ��άͶӰ�õ���ʼ��ά����
// ���̺���
void Initcube();											// ��ʼ��������������Ϣ
void rotation();											// ��ת
void Drawcube();											// �������
void changing();											// �����ά��
void ifend();												// �ж��Ƿ����



///////////////////////
// ��������
int main()
{
	// ���û��������Ϣ
	initgraph(Db_x, Db_y);
	setbkcolor(bkCOLOR);
	setbkmode(TRANSPARENT);
	setlinecolor(BLACK);

	BeginBatchDraw();
	while (true)
	{
		cleardevice();
		Initcube();

		// ��̬���
		Drawcube();
		FlushBatchDraw();
		Sleep(Stardelay);

		// ��ʼ����
		while (end == 0)
		{
			cleardevice();
			rotation();
			changing();
			Drawcube();
			FlushBatchDraw();
			ifend();
			Sleep(1000 / FPS);		          // 1000/֡�� = �ӳ�ʱ��
		}
		Sleep(Enddelay);
	}
	EndBatchDraw();
	closegraph();
	return 0;
}

// ��ʼ��������������Ϣ
void Initcube()
{
	end = 0;
	for (int num = 0; num < cubenum; num++)
	{
		// ���ñ߳�
		cube[num].side_length = square_root_two * (num + 1) * sidegap;

		// ������ά��
		cube[num].tP[0] = { 0, 0, 0 };
		cube[num].tP[1] = { cube[num].side_length / square_root_two,
			cube[num].side_length / square_root_two,
			0 };
		cube[num].tP[2] = { 0,
			cube[num].side_length * square_root_two,
			0 };
		cube[num].tP[3] = { cube[num].side_length / square_root_two * (-1),
			cube[num].side_length / square_root_two,
			0 };
		for (int num1 = 4; num1 < 9; num1++)
		{
			cube[num].P[(num1 - 4)] = cube[num].tP[(num1 - 4)];
			cube[num].tP[num1] = { cube[num].P[(num1 - 4)].x, cube[num].P[(num1 - 4)].y,
				cube[num].P[(num1 - 4)].z + cube[num].side_length };
			cube[num].P[num1] = cube[num].tP[num1];
		}

		cube[num].taking = 1;
		cube[num].shoptime = (int)(num * turnrate);
		cube[num].haddone = 0;
	}
	// ת���õ�ͶӰ��
	changing();
}

// ��ת
void rotation()
{
	// ��ת���Ϊ��0��cube[num].side_length / square_root_two��z)
	for (int num = 0; num < cubenum; num++)
	{
		if (cube[num].taking == 1)
		{
			if (cube[num].shoptime == 0)
			{
				// ��������ת����
				for (int num1 = 0; num1 < 4; num1++)
				{
					cube[num].P[num1].x = (cube[num].tP[num1].x - 0) * cos(-cube[num].haddone*PI / FPS) - (cube[num].tP[num1].y - cube[num].side_length / square_root_two)*sin(-cube[num].haddone*PI / FPS) + 0;
					cube[num].P[num1].y = (cube[num].tP[num1].x - 0) * sin(-cube[num].haddone*PI / FPS) + (cube[num].tP[num1].y - cube[num].side_length / square_root_two)*cos(-cube[num].haddone*PI / FPS) + cube[num].side_length / square_root_two;
				}

				// ����
				for (int num2 = 4; num2 < 8; num2++)
				{
					cube[num].P[num2].x = cube[num].P[(num2 - 4)].x;
					cube[num].P[num2].y = cube[num].P[(num2 - 4)].y;
					cube[num].P[num2].z = cube[num].P[(num2 - 4)].z + cube[num].side_length;
				}

				cube[num].haddone++;
				if (cube[num].haddone == (FPS + 1))
					cube[num].taking = 0;
			}
			else	cube[num].shoptime--;
		}
	}
}

// �����ά��
void changing()
{
	for (int num = 0; num < cubenum; num++)
		for (int num1 = 0; num1 < 8; num1++)
			cube[num].p[num1] = projection(cube[num].P[num1]);
}

// �������
void Drawcube()
{
	for (int num = 0; num < cubenum; num++)
	{
		for (int num1 = 0; num1 < 4; num1++)
		{
			// �ײ�
			temp = ((num1 + 1) == 4) ? 0 : (num1 + 1);
			line(cube[num].p[num1].x, cube[num].p[num1].y, cube[num].p[temp].x, cube[num].p[temp].y);

			// ����
			temp = num1 + 4;
			line(cube[num].p[num1].x, cube[num].p[num1].y, cube[num].p[temp].x, cube[num].p[temp].y);

			// ����
			temp = ((num1 + 5) == 8) ? 4 : (num1 + 5);
			line(cube[num].p[(num1 + 4)].x, cube[num].p[(num1 + 4)].y, cube[num].p[temp].x, cube[num].p[temp].y);
		}
	}
}

// �ж��Ƿ����
void ifend()
{
	if (cube[(cubenum - 1)].taking == 0)
		end = 1;
}

// ͶӰ�õ���ʼ��ά����
POINT projection(POINT3D &p3)
{
	POINT p2;
	// xֱ��ȡֵ
	p2.x = (long)p3.x + center_x;
	// y�õ㵽ֱ�߹�ʽ
	p2.y = (long)((p3.y * square_root_two - p3.z * 2) / square_root_six + center_y);
	return p2;
}
