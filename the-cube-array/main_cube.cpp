//��Ŀ����		������
//����			����1704
//email			1479245050@qq.com
//��ϵ��ʽ		qq 1479245050
//����			һ����������ת�ƶ��Ķ�̬Ч��
//���뻷��		win10 64λ + vs2017 + easyx��ver: 20180727(beta)
////////////////////////

#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>

////////////�궨��
//	����
#define PI					3.1415926535898							//	Բ����
#define	square_root_two		1.4142135623731
#define	square_root_three	1.7320508075689
#define square_root_six		2.4494897427832
//	������С
#define	drawingboard_x		600										//	��
#define	drawingboard_y		600										//	��
#define	center_x			drawingboard_x/2
#define	center_y			drawingboard_y/2
#define	bkColor				BLACK									//	������ɫ
#define lColor				WHITE									//	������ɫ

//	����
#define	layernum			10										//	����
#define	cube_slength		42										//	������߳�

//	ʱ�䳤��
#define	FPS					60										//	֡��
#define	beginDelay			1000									//	������ʼʱ�ľ�ֹʱ��
#define	endDelay			1000									//	��������ʱ�ľ�ֹʱ��
#define turn_times			90										//	��ת��ʮ�ȹ�����Ҫ��ת�Ĵ���
#define	everyturndeg		PI/2/turn_times							//	ÿ��ת���ĽǶ�	
#define	yi_stop				15										//	stoptime��num����ʱ
#define	er_stop				4										//	stoptime��num1����ʱ

////////////����ȫ�ֱ������ṹ��
class POINT3D												// ������ά��
{
public:
	long x, y, z;
	POINT3D() {}
	POINT3D(long x, long y, long z) {
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
struct  Cube												//	����������
{
	POINT3D tP3[8];											//	��ʼ����
	POINT3D P3[8];											//	��ǰ����
	POINT3D P1ST[8];										//	��һ����
	POINT3D P2ED[8];										//	�ڶ�����
	POINT3D P3RD[8];										//	��������

	POINT	cen_p2;											//	������������
	POINT	p2[8];											//	ͶӰ����
	POINT	p1st[8];										//	��һ����
	POINT	p2ed[8];										//	�ڶ�����
	POINT	p3rd[8];										//	��������

	int		Taking;											//	�Ƿ��ڿ����˶� 0��1�� ��ʼΪ1 �˶�����Ϊ0
	int		Stoptime;										//	��ת�ȴ�
	int		Haddone;										//	�����֡������PI/2ֵ ֹͣ taking��Ϊ0
}cube[(layernum * layernum)];
long	temp;												//	��ʱ����ʹ��
int		end;												//	0Ϊ��ʼֵ������������ֹͣ��end��Ϊ1


////////////��������
//	���ܺ���
POINT projection(POINT3D &p3);								//	ͶӰ�õ���ʼ��ά����

//	���̺���
void Init();												//	��ʼ��
void rotation();											//	��ת
void Drawcube();											//	�������
void reflection();											//	����������Ӱ������õ����� ����ת��

////////////��������
//	�������
int main()
{
	//	��ʼ����������
	initgraph(drawingboard_x, drawingboard_y);
	setbkcolor(bkColor);
	setbkmode(TRANSPARENT);
	setlinecolor(lColor);
	setlinestyle(PS_SOLID | PS_ENDCAP_ROUND | PS_JOIN_ROUND, 1, NULL, 0);
	setfillcolor(bkColor);

	//	����
	BeginBatchDraw();
	while (1)
	{
		cleardevice();
		Init();
		//	��̬���
		Drawcube();
		FlushBatchDraw();
		Sleep(beginDelay);
		//	��ʼ����
		while (end == 0)
		{
			cleardevice();
			rotation();
			reflection();
			Drawcube();

			FlushBatchDraw();
			Sleep(1000 / FPS);
		}
		Sleep(endDelay);
	}
	EndBatchDraw();
	closegraph();
	return 0;
}

//	����������Ӱ������õ����� ����ת��
void reflection()
{
	for (int num = 0; num < layernum; num++) {
		for (int num1 = 0; num1 < (2 * num + 1); num1++) {
			for (int num2 = 0; num2 < 8; num2++) {
				// ��һ����
				cube[(num*num + num1)].P1ST[num2] = { cube[(num*num + num1)].P3[num2].x,
					cube[(num*num + num1)].P3[num2].y - 2 * cube[(num*num + num1)].cen_p2.y,
					cube[(num*num + num1)].P3[num2].z };
				cube[(num*num + num1)].p1st[num2] = projection(cube[(num*num + num1)].P1ST[num2]);
				// �ڶ�����
				cube[(num*num + num1)].P2ED[num2] = { cube[(num*num + num1)].P3[num2].x - 2 * cube[(num*num + num1)].cen_p2.x,
					cube[(num*num + num1)].P3[num2].y - 2 * cube[(num*num + num1)].cen_p2.y,
					cube[(num*num + num1)].P3[num2].z };
				cube[(num*num + num1)].p2ed[num2] = projection(cube[(num*num + num1)].P2ED[num2]);
				// ��������
				cube[(num*num + num1)].P3RD[num2] = { cube[(num*num + num1)].P3[num2].x - 2 * cube[(num*num + num1)].cen_p2.x,
					cube[(num*num + num1)].P3[num2].y,
					cube[(num*num + num1)].P3[num2].z };
				cube[(num*num + num1)].p3rd[num2] = projection(cube[(num*num + num1)].P3RD[num2]);
			}
		}
	}
}

//	��ת
void rotation()
{
	for (int num = 0; num < layernum; num++) {
		for (int num1 = 0; num1 < (2 * num + 1); num1++) {
			if (cube[(num*num + num1)].Taking == 1)
			{
				if (cube[(num*num + num1)].Stoptime != 0)
				{
					cube[(num*num + num1)].Stoptime--;
				}
				else {
					cube[(num*num + num1)].Haddone++;

					for (int num2 = 0; num2 < 8; num2++)
					{
						cube[(num*num + num1)].P3[num2].x = (long)((cube[(num*num + num1)].tP3[num2].x - cube[(num*num + num1)].cen_p2.x) * cos(cube[(num*num + num1)].Haddone * everyturndeg)
							- (cube[(num*num + num1)].tP3[num2].y - cube[(num*num + num1)].cen_p2.y) * sin(cube[(num*num + num1)].Haddone * everyturndeg) + cube[(num*num + num1)].cen_p2.x);
						cube[(num*num + num1)].P3[num2].y = (long)((cube[(num*num + num1)].tP3[num2].x - cube[(num*num + num1)].cen_p2.x) * sin(cube[(num*num + num1)].Haddone * everyturndeg)
							+ (cube[(num*num + num1)].tP3[num2].y - cube[(num*num + num1)].cen_p2.y) * cos(cube[(num*num + num1)].Haddone * everyturndeg) + cube[(num*num + num1)].cen_p2.y);
						cube[(num*num + num1)].P3[num2].y -= (long)(cube[(num*num + num1)].Haddone * 4 * cube_slength / turn_times / square_root_two);

						cube[(num*num + num1)].p2[num2] = projection(cube[(num*num + num1)].P3[num2]);
					}
				}
			}
			if (cube[(num*num + num1)].Haddone == turn_times)
				cube[(num*num + num1)].Taking = 0;
		}
	}
	if (cube[(layernum*layernum - 1)].Taking == 0)
		end = 1;
}

//	�������
void Drawcube()
{
	//	��һ����
	for (int num = (layernum - 1); num >= 0; num--) {
		for (int num1 = 0; num1 < (2 * num); num1++) {
			POINT pts[] = { cube[(num*num + num1)].p1st[4], cube[(num*num + num1)].p1st[5], cube[(num*num + num1)].p1st[6], cube[(num*num + num1)].p1st[7] };
			fillpolygon(pts, 4);
			if (cube[(num*num + num1)].Haddone <= (int)(turn_times / 2))
			{
				POINT pts1[] = { cube[(num*num + num1)].p1st[1], cube[(num*num + num1)].p1st[2], cube[(num*num + num1)].p1st[6], cube[(num*num + num1)].p1st[5] };
				POINT pts2[] = { cube[(num*num + num1)].p1st[2], cube[(num*num + num1)].p1st[3], cube[(num*num + num1)].p1st[7], cube[(num*num + num1)].p1st[6] };
				fillpolygon(pts1, 4);
				fillpolygon(pts2, 4);
			}
			else
			{
				POINT pts1[] = { cube[(num*num + num1)].p1st[2], cube[(num*num + num1)].p1st[3], cube[(num*num + num1)].p1st[7], cube[(num*num + num1)].p1st[6] };
				POINT pts2[] = { cube[(num*num + num1)].p1st[3], cube[(num*num + num1)].p1st[0], cube[(num*num + num1)].p1st[4], cube[(num*num + num1)].p1st[7] };
				fillpolygon(pts1, 4);
				fillpolygon(pts2, 4);
			}
		}
	}
	//	�ڶ�����
	for (int num = (layernum - 1); num >= 0; num--) {
		for (int num1 = 1; num1 < (2 * num + 1); num1++) {
			POINT pts[] = { cube[(num*num + num1)].p2ed[4], cube[(num*num + num1)].p2ed[5], cube[(num*num + num1)].p2ed[6], cube[(num*num + num1)].p2ed[7] };
			fillpolygon(pts, 4);
			if (cube[(num*num + num1)].Haddone <= (int)(turn_times / 2))
			{
				POINT pts1[] = { cube[(num*num + num1)].p2ed[1], cube[(num*num + num1)].p2ed[2], cube[(num*num + num1)].p2ed[6], cube[(num*num + num1)].p2ed[5] };
				POINT pts2[] = { cube[(num*num + num1)].p2ed[2], cube[(num*num + num1)].p2ed[3], cube[(num*num + num1)].p2ed[7], cube[(num*num + num1)].p2ed[6] };
				fillpolygon(pts1, 4);
				fillpolygon(pts2, 4);
			}
			else
			{
				POINT pts1[] = { cube[(num*num + num1)].p2ed[2], cube[(num*num + num1)].p2ed[3], cube[(num*num + num1)].p2ed[7], cube[(num*num + num1)].p2ed[6] };
				POINT pts2[] = { cube[(num*num + num1)].p2ed[3], cube[(num*num + num1)].p2ed[0], cube[(num*num + num1)].p2ed[4], cube[(num*num + num1)].p2ed[7] };
				fillpolygon(pts1, 4);
				fillpolygon(pts2, 4);
			}
		}
	}
	//	��������
	for (int num = (layernum - 1); num >= 0; num--) {
		for (int num1 = 1; num1 < (2 * num); num1++) {
			POINT pts[] = { cube[(num*num + num1)].p3rd[4], cube[(num*num + num1)].p3rd[5], cube[(num*num + num1)].p3rd[6], cube[(num*num + num1)].p3rd[7] };
			fillpolygon(pts, 4);
			if (cube[(num*num + num1)].Haddone <= (int)(turn_times / 2))
			{
				POINT pts1[] = { cube[(num*num + num1)].p3rd[1], cube[(num*num + num1)].p3rd[2], cube[(num*num + num1)].p3rd[6], cube[(num*num + num1)].p3rd[5] };
				POINT pts2[] = { cube[(num*num + num1)].p3rd[2], cube[(num*num + num1)].p3rd[3], cube[(num*num + num1)].p3rd[7], cube[(num*num + num1)].p3rd[6] };
				fillpolygon(pts1, 4);
				fillpolygon(pts2, 4);
			}
			else
			{
				POINT pts1[] = { cube[(num*num + num1)].p3rd[2], cube[(num*num + num1)].p3rd[3], cube[(num*num + num1)].p3rd[7], cube[(num*num + num1)].p3rd[6] };
				POINT pts2[] = { cube[(num*num + num1)].p3rd[3], cube[(num*num + num1)].p3rd[0], cube[(num*num + num1)].p3rd[4], cube[(num*num + num1)].p3rd[7] };
				fillpolygon(pts1, 4);
				fillpolygon(pts2, 4);
			}
		}
	}
	//	��������
	for (int num = (layernum - 1); num >= 0; num--) {
		for (int num1 = 0; num1 < (2 * num + 1); num1++) {
			POINT pts[] = { cube[(num*num + num1)].p2[4], cube[(num*num + num1)].p2[5], cube[(num*num + num1)].p2[6], cube[(num*num + num1)].p2[7] };
			fillpolygon(pts, 4);
			if (cube[(num*num + num1)].Haddone <= (int)(turn_times / 2))
			{
				POINT pts1[] = { cube[(num*num + num1)].p2[1], cube[(num*num + num1)].p2[2], cube[(num*num + num1)].p2[6], cube[(num*num + num1)].p2[5] };
				POINT pts2[] = { cube[(num*num + num1)].p2[2], cube[(num*num + num1)].p2[3], cube[(num*num + num1)].p2[7], cube[(num*num + num1)].p2[6] };
				fillpolygon(pts1, 4);
				fillpolygon(pts2, 4);
			}
			else
			{
				POINT pts1[] = { cube[(num*num + num1)].p2[2], cube[(num*num + num1)].p2[3], cube[(num*num + num1)].p2[7], cube[(num*num + num1)].p2[6] };
				POINT pts2[] = { cube[(num*num + num1)].p2[3], cube[(num*num + num1)].p2[0], cube[(num*num + num1)].p2[4], cube[(num*num + num1)].p2[7] };
				fillpolygon(pts1, 4);
				fillpolygon(pts2, 4);
			}
		}
	}
}

//	��ʼ��
void Init()
{
	end = 0;

	for (int num = 0; num < layernum; num++)
	{
		for (int num1 = 0; num1 < (2 * num + 1); num1++)
		{
			cube[(num*num + num1)].Haddone = 0;
			cube[(num*num + num1)].Taking = 1;

			temp = 2 * num - num1;
			if (temp == 0)
				cube[(num*num + num1)].Stoptime = num * yi_stop + num1 * er_stop;
			else
				cube[(num*num + num1)].Stoptime = num * yi_stop + (temp - 1) * er_stop;

			//	�������� Ϊ��������꾫�ȣ��ȷŴ�����С����
			//	��������
			cube[(num*num + num1)].cen_p2.x = (long)(num1 * cube_slength * square_root_two);
			cube[(num*num + num1)].cen_p2.y = (long)(-cube[(num*num + num1)].cen_p2.x + 2 * num * cube_slength * square_root_two);

			temp = (long)(cube_slength / 2 * square_root_two);
			//	�˸�����
			cube[(num*num + num1)].tP3[0] = { cube[(num*num + num1)].cen_p2.x, cube[(num*num + num1)].cen_p2.y - temp, 0 };
			cube[(num*num + num1)].tP3[1] = { cube[(num*num + num1)].cen_p2.x - temp, cube[(num*num + num1)].cen_p2.y, 0 };
			cube[(num*num + num1)].tP3[2] = { cube[(num*num + num1)].cen_p2.x, cube[(num*num + num1)].cen_p2.y + temp, 0 };
			cube[(num*num + num1)].tP3[3] = { cube[(num*num + num1)].cen_p2.x + temp, cube[(num*num + num1)].cen_p2.y, 0 };
			for (int num2 = 0; num2 < 4; num2++)
				cube[(num*num + num1)].tP3[num2 + 4] = { cube[(num*num + num1)].tP3[num2].x, cube[(num*num + num1)].tP3[num2].y, cube_slength };

			//	ת������
			for (int num3 = 0; num3 < 8; num3++)
			{
				cube[(num*num + num1)].P3[num3] = cube[(num*num + num1)].tP3[num3];
				cube[(num*num + num1)].p2[num3] = projection(cube[(num*num + num1)].P3[num3]);
			}
		}
	}
	reflection();
}

//	ͶӰ�õ���ʼ��ά����
POINT projection(POINT3D &p3)
{
	POINT p2;
	//	xֱ��ȡֵ
	p2.x = (long)p3.x + center_x;
	//	y�õ㵽ֱ�߹�ʽ
	p2.y = (long)((p3.y * square_root_two - p3.z * 2) / square_root_six + center_y);
	return p2;
}