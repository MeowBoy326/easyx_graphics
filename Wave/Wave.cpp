/********************************************************
 * �������ƣ�ʵ��ˮ������ʾ								*
 * ���뻷����Visual C++ 6.0 / 2010��EasyX_20200315(beta)	*
 * �������ߣ��� (QQ: 415051674)							*
 * �����㷨���ο������㷨									*
 * �������ڣ�2013/3/20									*
 ********************************************************/


#include <graphics.h>     
#include <conio.h>
#include <stdio.h>

#define PIC_WIDTH  800
#define PIC_HEIGHT 600
#define FPS_COUNT  8

void FrameFun();									// ֡�߼�����������ÿһ֡���߼�
void RenderFun();									// ֡��Ⱦ���������ÿһ֡����ʾ�豸

IMAGE src_img;										// ԭλͼ		
IMAGE dest_img(PIC_WIDTH, PIC_HEIGHT);				// ��������ʾ��λͼ
DWORD* img_ptr1;									// ԭͼƬƬ�ڴ�ָ��
DWORD* img_ptr2;									// ��������ʾ��λͼ�ڴ�ָ��


// �������� buf Ϊÿһ����Ĳ�����ǰ��Ϊ��ǰ����������Ϊ��һ��ʱ�̵Ĳ�����
short* buf = new short[PIC_HEIGHT * PIC_WIDTH + PIC_WIDTH];
short* buf2 = new short[PIC_HEIGHT * PIC_WIDTH + PIC_WIDTH];


void main()
{
	// ��ʼ���豸������ͼƬ
	initgraph(PIC_WIDTH, PIC_HEIGHT);
	BeginBatchDraw();						// ˫����
	loadimage(&src_img, _T("water.jpg"), PIC_WIDTH, PIC_HEIGHT);	// ����ͼƬ����С��800*600
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(20, 0, _T("Arial"));

	// ����ڴ�ָ��
	img_ptr1 = GetImageBuffer(&src_img);
	img_ptr2 = GetImageBuffer(&dest_img);

	// ��ʼ����������
	memset(buf, 0, (PIC_HEIGHT * PIC_WIDTH + PIC_WIDTH) * sizeof(short));
	memset(buf2, 0, (PIC_HEIGHT * PIC_WIDTH + PIC_WIDTH) * sizeof(short));

	// Let's Go!
	while (true)
	{
		FrameFun();
		RenderFun();
		FlushBatchDraw();
		Sleep(1);
	}
}

// �������һ��ʱ�����е�Ĳ���
void nextFrame()
{
	for (int i = PIC_WIDTH; i < PIC_HEIGHT * (PIC_WIDTH - 1); i++)
	{
		// ��ʽ��X0'= (X1+X2+X3+X4) / 2 - X0
		buf2[i] = ((buf[i - PIC_WIDTH] + buf[i + PIC_WIDTH] + buf[i - 1] + buf[i + 1]) >> 1) - buf2[i];

		// ����˥��
		buf2[i] -= buf2[i] >> 5;
	}

	short* ptmp = buf;
	buf = buf2;
	buf2 = ptmp;
}

// ������ǰʱ�̲���Ӱ��֮���λͼ�������� dest_img ��
void RenderRipple()
{
	int i = 0;
	for (int y = 0; y < PIC_HEIGHT; y++)
	{
		for (int x = 0; x < PIC_WIDTH; x++)
		{
			short data = 1024 - buf[i];

			// ƫ��
			int a = ((x - PIC_WIDTH / 2) * data / 1024) + PIC_WIDTH / 2;
			int b = ((y - PIC_HEIGHT / 2) * data / 1024) + PIC_HEIGHT / 2;

			// �߽紦��
			if (a >= PIC_WIDTH)		a = PIC_WIDTH - 1;
			if (a < 0)				a = 0;
			if (b >= PIC_HEIGHT)	b = PIC_HEIGHT - 1;
			if (b < 0)				b = 0;

			// ����ƫ�� 
			img_ptr2[i] = img_ptr1[a + (b * PIC_WIDTH)];
			i++;
		}
	}
}

// ���ģ��Ͷʯͷ
// ����˵����
// (x, y): �������
// stonesize: ��ʯͷ���Ĵ�С
// stoneweight: Ͷ��ʯͷ��������
// Ps: �����������һ���������Խ�����£������������ʯͷ���Ĵ�С�͡�ʯͷ��������
void disturb(int x, int y, int stonesize, int stoneweight)
{
	// ͻ�Ʊ߽粻����
	if ((x >= PIC_WIDTH - stonesize) ||
		(x < stonesize) ||
		(y >= PIC_HEIGHT - stonesize) ||
		(y < stonesize))
		return;

	for (int posx = x - stonesize; posx < x + stonesize; posx++)
	{
		for (int posy = y - stonesize; posy < y + stonesize; posy++)
		{
			if ((posx - x) * (posx - x) + (posy - y) * (posy - y) < stonesize * stonesize)
			{
				buf[PIC_WIDTH * posy + posx] += stoneweight;
			}
		}
	}
}

// ����fps
float getFps()
{
	static int i = 0;
	static int oldTime = GetTickCount();
	static float fps;

	if (i > FPS_COUNT)
	{
		i = 0;
		int newTime = GetTickCount();
		int elapsedTime = newTime - oldTime;
		fps = FPS_COUNT / (elapsedTime / 1000.0f);
		oldTime = newTime;
	}
	i++;
	return fps;
}

// ��Ⱦ
void RenderFun()
{
	RenderRipple();
	putimage(0, 0, &dest_img);

	outtextxy(0, 0, _T("Wave - ˮ����Ч�����������һ��ˮ���ƣ��ƶ������������ˮ���ƣ�"));
	TCHAR s[20];
#if _MSC_VER > 1200
	_stprintf_s(s, _T("FPS: %.1f"), getFps());
#else
	_stprintf(s, _T("FPS: %.1f"), getFps());
#endif
	outtextxy(0, 20, s);
}

// �߼�
void FrameFun()
{
	// ���
	if (MouseHit())
	{
		MOUSEMSG msg = GetMouseMsg();
		if (msg.uMsg == WM_MOUSEMOVE)
		{
			disturb(msg.x, msg.y, 3, 256);
		}
		else if (msg.uMsg == WM_LBUTTONDOWN)
		{
			disturb(msg.x, msg.y, 3, 2560);
		}
		FlushMouseMsgBuffer();
	}

	// ������һ֡�Ĳ���
	nextFrame();
}