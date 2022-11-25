/********************************************************
*														*
*	�������ƣ�ף���̻���ף������						*
*	���뻷����VC++6.0 && easyx(������)					*
*	������أ�yy�H�H__<837943056@qq.com>				*
*	����޸ģ�2012.11.22								*
*														*
********************************************************/
#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <Mmsystem.h>		// ʹ�øü�ʱ������������ļ�
#pragma comment ( lib, "Winmm.lib" )

/***** �궨���� ******/

#define NUM		13			// �̻����������궨��

/***** �ṹ������ **********/

// �̻��ṹ
struct FIRE
{
	int r;					// ��ǰ��ը�뾶
	int max_r;				// ��ը���ľ����Ե���뾶
	int x, y;				// ��ը�����ڴ��ڵ�����
	int cen_x, cen_y;		// ��ը�������ͼƬ���Ͻǵ�����
	int width, height;		// ͼƬ�Ŀ���
	int xy[240][240];		// ����ͼƬ���ص�

	bool show;				// �Ƿ�����
	bool draw;				// ��ʼ������ص�
	DWORD t1, t2, dt;		// �����ٶ�
}Fire[NUM];

// �̻����ṹ
struct JET
{
	int x, y;				// ���������
	int hx, hy;				// ��ߵ�����------����ֵ�� FIRE ����� x, y
	int height;				// �̻��߶�
	bool shoot;				// �Ƿ���Է���

	DWORD t1, t2, dt;		// �����ٶ�
	IMAGE img[2];			// ���滨��һ��һ��ͼƬ
	byte n : 1;				// ͼƬ�±�
}Jet[NUM];

// happy birthday �����ֽṹ
struct HAPPY				// ���� Happy Birthday ������ͼƬ
{
	int x, y;				// ÿ���ֵ�ͼƬ�����Ͻ�����
	IMAGE img;				// ���浥����ͼƬ
	static int num;			// ��ĸ���
}Happy[NUM];
int HAPPY::num = 0;

// For.2012��زŮ �ṹ
struct WISH					// ����ף��ͼƬ�ṹ
{
	int x, y;				// ͼƬ���Ͻ�����
	DWORD t1, t2, dt;		// ͼƬ�˶�ʱ����
	IMAGE img;				// ����ͼƬ
	int dxy;				// ÿ�ε��ƶ���
	byte dir : 1;			// ����������������
}Wish;

/**** ���������� ****/

void Init	( int	 );		// ��ʼ���̻�
void Load	(		 );		// �����̻�ͼƬ
void Shoot	(		 );		// �����̻�
void Chose	( DWORD& );		// ɸѡ�̻�
void Wishing(		 );		// ����ף��
void Style	( DWORD& );		// ������ʽ
void Show	( DWORD* );		// �����̻�


// ������
void main()
{
	initgraph( 1200, 800 );
	srand( time(0) );

	// ���ű�������
	mciSendString( "open ./fire/bk.mp3 alias bk", 0, 0, 0 );
	mciSendString( "play bk repeat", 0, 0, 0 );

	setfillstyle( 0	);
	setfont		( 36, 0, "����"	);
	setcolor	( YELLOW );
	outtextxy	( 370, 100, "yy�H�H__���� .... ^_^" );

	DWORD t1	= timeGetTime();		// ɸѡ�̻���ʱ
	DWORD st1	= timeGetTime();		// ���Ż�����ʱ
	DWORD* pMem = GetImageBuffer();		// ��ȡ�����Դ�ָ��

	for ( int i = 0; i < NUM; i++ )		// ��ʼ���̻�
	{
		Init( i );
	}
	Load();								// ���̻�ͼƬ��Ϣ���ؽ���Ӧ�ṹ��
	BeginBatchDraw();					// ��ʼ������ͼ

	while ( !kbhit() )
	{
		Sleep( 10 );

		// ���ѡ�� 4000 �����ص����
		for ( int clr = 0; clr < 1000; clr++ )
		{
			for ( int j = 0; j < 2; j++ )
			{
				int px1 = rand() % 1200;
				int py1 = rand() % 800;

				if ( py1 < 799 )				// ��ֹԽ��
					pMem[py1 * 1200 + px1] = pMem[py1 * 1200 + px1 + 1] = BLACK;	// ���Դ渳ֵ�������ص�
			}
		}
		Chose	( t1	);		// ɸѡ�̻�
		Shoot	(		);		// �����̻�
		Show	( pMem	);		// �����̻�
		Wishing	(		);		// �����ַ�
		Style	( st1	);		// ��������
		FlushBatchDraw(	);		// ��ʾǰ������л�ͼ����
	}
}


// ��ʼ���̻�����
void Init( int i )
{
	// �ֱ�Ϊ���̻����ĵ�ͼƬ��Ե����Զ���롢�̻����ĵ�ͼƬ���Ͻǵľ��� (x��y) ��������
	int r[13] = { 120, 120, 155, 123, 130, 147, 138, 138, 130, 135, 140, 132, 155 };
	int x[13] = { 120, 120, 110, 117, 110, 93,  102, 102, 110, 105, 100, 108, 110 };
	int y[13] = { 120, 120, 85,  118, 120, 103, 105, 110, 110, 120, 120, 104, 85  };

	/**** ��ʼ���̻� *****/

	Fire[i].x		= 0;				// �̻���������
	Fire[i].y		= 0;
	Fire[i].width	= 240;				// ͼƬ��
	Fire[i].height	= 240;				// ͼƬ��
	Fire[i].max_r	= r[i];				// ���뾶
	Fire[i].cen_x	= x[i];				// ���ľ����ϽǾ���
	Fire[i].cen_y	= y[i];
	Fire[i].show	= false;			// �Ƿ�����
	Fire[i].dt		= 5;				// ����ʱ����
	Fire[i].t1		= timeGetTime();
	Fire[i].r		= 0;				// �� 0 ��ʼ����

	/**** ��ʼ���̻��� *****/

	Jet[i].x		= -240;				// �̻������Ͻ�����
	Jet[i].y		= -240;
	Jet[i].hx		= -240;				// �̻���������ߵ�����
	Jet[i].hy		= -240;
	Jet[i].height	= 0;				// ����߶�
	Jet[i].t1		= timeGetTime();
	Jet[i].dt		= rand() % 10;		// �����ٶ�ʱ����
	Jet[i].n		= 0;				// �̻�����˸ͼƬ�±�
	Jet[i].shoot	= false;			// �Ƿ���
}


// ����ͼƬ
void Load()
{
/**** �����̻������ص���ɫ ****/
	IMAGE fm, gm;
	loadimage( &fm, "./fire/flower.jpg", 3120, 240 );

	for ( int i = 0; i < 13; i++ )
	{
		SetWorkingImage( &fm );
		getimage( &gm, i * 240, 0, 240, 240 );
		SetWorkingImage( &gm );

		for ( int a = 0; a < 240; a++ )
			for ( int b = 0; b < 240; b++ )
				Fire[i].xy[a][b] = getpixel( a, b );
	}

/**** �����̻��� ************/
	IMAGE sm;
	loadimage( &sm, "./fire/shoot.jpg", 200, 50 );

	for (int i = 0; i < 13; i++ )
	{
		SetWorkingImage( &sm );
		int n = rand() % 5;

		getimage( &Jet[i].img[0], n * 20, 0, 20, 50 );			// ��
		getimage( &Jet[i].img[1], (n + 5) * 20, 0, 20, 50 );	// ��
	}

/***** ���� Happy Birthday ͼƬ ********/
	IMAGE hm;
	loadimage( &hm, "./fire/happy.jpg", 689, 115 );
	SetWorkingImage( &hm );

	for (int i = 0; i < 13; i++ )
	{
		Happy[i].x = i * 90;
		Happy[i].y = rand() % 100 + 500;
		getimage( &Happy[i].img, i * 53, 0, 53, 115 );
	}

/***** ���� For.2012��زŮ ͼƬ *********/
	Wish.x		= 0;
	Wish.y		= 100;
	Wish.t1		= timeGetTime();
	Wish.dt		= 46;
	Wish.dir	= 0;
	Wish.dxy	= rand() % 8 + 1;
	loadimage( &Wish.img, "./fire/yaojing.jpg", 490, 100 );
	putimage( Wish.x, Wish.y, &Wish.img, SRCINVERT );

	SetWorkingImage();		// ���ûػ�ͼ����
}


// ��һ����Χ��ɸѡ�ɷ�����̻�������ʼ���������������̻�������Ļ����������
void Chose( DWORD& t1 )
{
	DWORD t2 = timeGetTime();

	if ( t2 - t1 > 100 )
	{
		int n = rand() % 20;

		if ( n < 13 && Jet[n].shoot == false && Fire[n].show == false )
		{
			/**** �����̻�����Ԥ������ *****/
			Jet[n].x		= rand() % 1200;
			Jet[n].y		= rand() % 100 + 600;
			Jet[n].hx		= Jet[n].x;
			Jet[n].hy		= rand() % 400;
			Jet[n].height	= Jet[n].y - Jet[n].hy;
			Jet[n].shoot	= true;
			putimage( Jet[n].x, Jet[n].y, &Jet[n].img[Jet[n].n], SRCINVERT );

			/**** ����ÿ���̻��������� *****/
			char c1[50], c2[30], c3[30];
			sprintf( c1, "open ./fire/shoot.mp3 alias s%d", n );
			sprintf( c2, "play s%d", n );
			sprintf( c3, "close n%d", n );

			mciSendString( c3, 0, 0, 0 );
			mciSendString( c1, 0, 0, 0 );
			mciSendString( c2, 0, 0, 0 );
		}
		t1 = t2;
	}
}


// ɨ���̻���������
void Shoot()
{
	for ( int i = 0; i < 13; i++ )
	{
		Jet[i].t2 = timeGetTime();

		if ( Jet[i].t2 - Jet[i].t1 > Jet[i].dt && Jet[i].shoot == true )
		{
			/**** �̻��������� *****/
			putimage( Jet[i].x, Jet[i].y, &Jet[i].img[Jet[i].n], SRCINVERT );

			if ( Jet[i].y > Jet[i].hy )
			{
				Jet[i].n++;
				Jet[i].y -= 5;
			}

			putimage( Jet[i].x, Jet[i].y, &Jet[i].img[Jet[i].n], SRCINVERT );

			/**** �������߶ȵ� 3 / 4������ *****/
			if ( (Jet[i].y - Jet[i].hy) * 4 < Jet[i].height )
				Jet[i].dt = rand() % 4 + 10 ;

			/**** ���������߶� *****/
			if ( Jet[i].y <= Jet[i].hy )
			{
				// ���ű�ը��
				char c1[50], c2[30], c3[30];
				sprintf( c1, "open ./fire/bomb.wav alias n%d", i );
				sprintf( c2, "play n%d", i );
				sprintf( c3, "close s%d", i );

				mciSendString( c3, 0, 0, 0 );
				mciSendString( c1, 0, 0, 0 );
				mciSendString( c2, 0, 0, 0 );

				putimage( Jet[i].x, Jet[i].y, &Jet[i].img[Jet[i].n], SRCINVERT );	// �����̻���
				Fire[i].x = Jet[i].hx + 10;											// ���̻����м䱬ը
				Fire[i].y = Jet[i].hy;												// ����ߵ�����
				Fire[i].show = true;					// ��ʼ����
				Jet[i].shoot = false;					// ֹͣ����

				// ��ʾ��Ӧ��ĸ
				putimage( Happy[HAPPY::num].x, Happy[HAPPY::num].y, &Happy[HAPPY::num].img, SRCINVERT );
				HAPPY::num++;

				if ( HAPPY::num > 12 )
					HAPPY::num = 0;
			}
			Jet[i].t1 = Jet[i].t2;
		}
	}
}


// ����ˮƽ����ֱ�ƶ���ͼƬ
void Wishing()
{
	Wish.t2 = timeGetTime();

	if ( Wish.t2 - Wish.t1 > Wish.dt )
	{
		/**** ͼƬ���ƶ� *****/
		putimage( Wish.x, Wish.y, &Wish.img, SRCINVERT );

		if ( Wish.dir == 0 )
			Wish.x += Wish.dxy;
		else
			Wish.y -= Wish.dxy;

		putimage( Wish.x, Wish.y, &Wish.img, SRCINVERT );

		/**** ͼƬ����� *****/
		if ( Wish.x > 1200 || Wish.y < 0 )
		{
			Wish.dir = rand() % 2;			// ��ȡ�������

			if ( Wish.dir == 0 )			// ��������˶�
			{
				Wish.y = rand() % 700;		// ��ʼλ��
				Wish.x = -490;
				Wish.dxy = rand() % 7 + 1;	// ����˶�����
			}
			else							// �����˶�
			{
				Wish.dxy = rand() % 7 + 1;
				Wish.x = rand() % 700;
				Wish.y = 800;
			}
		}
		Wish.t1 = Wish.t2;
	}
}


// ��ʾ����
void Style( DWORD& st1 )
{
	DWORD st2 = timeGetTime();

	if ( st2 - st1 > 266000 )		// һ�׸��ʱ��
	{
		// ��������
		int x[13] = { 60, 75, 91, 100, 95, 75, 60, 45, 25, 15, 25, 41, 60 };
		int y[13] = { 65, 53, 40, 22, 5, 4, 20, 4, 5, 22, 40, 53, 65 };
		for ( int i = 0; i < NUM; i++ )
		{
			cleardevice();
			/**** ���ɷֲ��̻��� ***/
			Jet[i].x		= x[i] * 10;
			Jet[i].y		= ( y[i] + 75 ) * 10;
			Jet[i].hx		= Jet[i].x;
			Jet[i].hy		= y[i] * 10;
			Jet[i].height	= Jet[i].y - Jet[i].hy;
			Jet[i].shoot	= true;
			Jet[i].dt		= 7;
			putimage( Jet[i].x, Jet[i].y, &Jet[i].img[Jet[i].n], SRCINVERT );	// ��ʾ�̻���

			/**** �����̻����� ***/
			Fire[i].x		= Jet[i].x + 10;
			Fire[i].y		= Jet[i].hy;
			Fire[i].show	= false;
			Fire[i].r		= 0;

			/**** ���ŷ������� ***/
			char c1[50], c2[30], c3[30];
			sprintf( c1, "open ./fire/shoot.mp3 alias s%d", i );
			sprintf( c2, "play s%d", i );
			sprintf( c3, "close n%d", i );

			mciSendString( c3, 0, 0, 0 );
			mciSendString( c1, 0, 0, 0 );
			mciSendString( c2, 0, 0, 0 );
		}
		st1 = st2;
	}
}


// �����̻�
void Show( DWORD* pMem )
{
	// �̻����׶�����ʱ������������������Ч��
	int drt[16] = { 5, 5, 5, 5, 5, 6, 25, 25, 25, 25, 55, 55, 55, 55, 55 };

	for ( int i = 0; i < NUM; i++ )
	{
		Fire[i].t2 = timeGetTime();

		// ���ӱ�ը�뾶�������̻�������ʱ����������Ч��
		if ( Fire[i].t2 - Fire[i].t1 > Fire[i].dt && Fire[i].show == true )
		{
			if ( Fire[i].r < Fire[i].max_r )
			{
				Fire[i].r++;
				Fire[i].dt = drt[Fire[i].r / 10];
				Fire[i].draw = true;
			}

			if ( Fire[i].r >= Fire[i].max_r - 1 )
			{
				Fire[i].draw = false;
				Init( i );
			}
			Fire[i].t1 = Fire[i].t2;
		}

		// ����ú��ڻ��ɱ�ը�����ݵ�ǰ��ը�뾶���̻�����ɫֵ�ӽ���ɫ�Ĳ������
		if ( Fire[i].draw )
		{
			for ( double a = 0; a <= 6.28; a += 0.01 )
			{
				int x1 = (int)( Fire[i].cen_x + Fire[i].r * cos(a) );				// �����ͼƬ���Ͻǵ�����
				int y1 = (int)( Fire[i].cen_y - Fire[i].r * sin(a) );

				if ( x1 > 0 && x1 < Fire[i].width && y1 > 0 && y1 < Fire[i].height )	// ֻ���ͼƬ�ڵ����ص�
				{
					int b = Fire[i].xy[x1][y1] & 0xff;
					int g = ( Fire[i].xy[x1][y1] >> 8 ) & 0xff;
					int r = ( Fire[i].xy[x1][y1] >> 16 );

					// �̻����ص��ڴ����ϵ�����
					int xx = (int)( Fire[i].x + Fire[i].r * cos(a) );
					int yy = (int)( Fire[i].y - Fire[i].r * sin(a) );

					// �ϰ������ص㲻�������ֹԽ��
					if ( r > 0x20 && g > 0x20 && b > 0x20 && xx > 0 && xx < 1200 && yy > 0 && yy < 800 )
						pMem[yy * 1200 + xx] = BGR( Fire[i].xy[x1][y1] );	// �Դ���������̻�
				}
			}
			Fire[i].draw = false;
		}
	}
}