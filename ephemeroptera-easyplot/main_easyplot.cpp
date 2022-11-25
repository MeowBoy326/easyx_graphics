/******************************************************************************************/
// EasyPlot �ǻ��� EasyX ��ͼ�⣨https://www.easyx.cn������д�ģ���ʵʱ�źŽ��л��Ƶ�һ������
// ���´���Ϊ�˱���ѧϰ��Դ�ļ���ʽչʾ�����Ӧ���ڹ��̽������ͷ�ļ���ʽ��װ
// ���Ĳ���Unicode�ַ�����ANSI�����Ķ���ע����صط���ʽ��ת��
// ���ߣ�Ephemeroptera
// �ص㣺���մ�ѧ
// ��ϵ��ʽ��605686962@qq.com
// ����޸�ʱ�䣺2018-11-29
/*******************************************************************************************/
#include <iostream>
#include <easyx.h>
#include <conio.h>
#include <sstream>
#include <string>
#define PI 3.141592

/*************** ���嶯̬ X ����ṹ�� ************************/
struct AxisX {
	double index; // ����
	double label; // ��ǩ
};
/*************** ��������ת LPWSTR �ַ��ͺ��� ****************/
void num2WSTR(double x, wchar_t* &buffer);

/*************** �����ࣺ��̬���� ****************************************************************************/
// ˵������̬����ʵ�ֻ���ʵʱ�źŵ�ԭ����ʵ�ǽ���ǰ�ź����붨������ DynaQue,
//      ����ÿһ֡���л��ƣ����ж��г����ɷֱ��ʾ��������ֱ���Ӧ�� <= COLS
//      ���磺DynaQue[xResolution+1] = {DynaQue[0],DynaQue[1,..,DynaQue[xRelolution]}������ DynaQue[N] Ϊ����ź�
//            ��ô���ڵ����Ϊ��COLS/xResolution
// ��Ȼ X ����Ҳ��Ҫ��̬���£�ͬ������Ҳ�����˶��� xAxis ���������ͬ������
//      ���磺xAxis[xSegment+1] = {xAxis[0],xAxis[1],..,xAxis[xSegment]}������ xAxis[N] ������� AxisX ����
//             ��ô���ڿ̶Ⱦ��룺COLS/xSegment
/***************************************************************************************************************/
class DynaWin {
public:
	DynaWin(double XLIM, double YLIM, unsigned short xSegment, unsigned short ySegment, int xResolution);	// ������
	void UpateWin(double y);	// ���´���
	void ShowWin();				// ���ƴ���
	void InitBackGround();		// ������ʼ������̬���ڣ�

private:
	const int CENTERX = 50;		// ����ԭ��
	const int CENTERY = 200;
	const int ROWS = 150;		// ����߳�
	const int COLS = 1000;

	double XLIM;				// ���� X ������
	double YLIM;				// ���� Y ������
	unsigned short xSegment;	// ��������Ŀ̶�
	unsigned short ySegment;
	int xResolution;			// x��ֱ���(���� Dynaque �ĳ���)
	int DynaNum = 0;			// �Ѷ��źŸ���
	double* DynaQue;			// ʵʱ�źŶ���
	AxisX* xAxis;				// ʵʱ�������
	IMAGE* canvas;				// ��ǰ����
	IMAGE local;				// �ֲ�����

	void UpdateAxisX();			// ��������

};
/*************************** MAIN ���� *********************************/
int main()
{
	// ���嶯̬���ڣ�
	//            X ���꣺���� = 2 * PI��	10 ���̶ȣ�500 �ֱ��ʣ������㣩
	//            Y ���꣺���� = 1��		5 ���̶�
	DynaWin win(2 * PI, 1, 10, 5, 500);
	win.InitBackGround(); //������ʼ��
	int i = 0;

	// �������ƣ�����һ��y=sin(wt)������ w = 2*��*f , t = n*T0 =n/Fs���������ǻ��� f = 5 �������ź�
	BeginBatchDraw();
	while (1)
	{
		win.UpateWin(sin(2 * PI * 5 * i / 500));	// ���´�
		win.ShowWin();								// ��ʾ��
		FlushBatchDraw();
		Sleep(10);
		++i;
	}

	EndBatchDraw();
	// ��������˳�
	_getch();
	closegraph();
	return 0;
}

/******************* ��������ط����ľ���ʵ�� **************************/
// ����ת LPWSTR �ַ�
void num2WSTR(double x, wchar_t* &buffer)
{
	// NUM TO WSS TO WSTR
	std::wstringstream ss;
	ss << x;
	size_t size = ss.str().length();
	buffer = new wchar_t[size + 1];
	ss >> buffer;
	buffer[size] = 0;
}

// DynaWin ���캯��
DynaWin::DynaWin(double XLIM, double YLIM, unsigned short xSegment, unsigned short ySegment, int xResolution)
{
	this->XLIM = XLIM;
	this->YLIM = YLIM;
	this->xSegment = xSegment;
	this->ySegment = ySegment;
	this->xResolution = xResolution;
	this->DynaQue = new double[xResolution + 1];
	this->xAxis = new AxisX[xSegment + 1];
}

//������ʼ��
void DynaWin::InitBackGround()
{
	// ���廭��
	initgraph(1100, 400, EX_SHOWCONSOLE);
	// ��ʼ������
	setlinecolor(RED);
	setlinestyle(PS_SOLID | PS_ENDCAP_ROUND | PS_JOIN_ROUND, 3);
	// ��������ԭ���Լ�����
	setorigin(CENTERX, CENTERY);
	setaspectratio(1, -1);
	// ���ƾ�̬����
	rectangle(0, 150, 1000, -150);
	line(0, 0, 1000, 0);
	// ��ע˵��
	setbkmode(TRANSPARENT);
	settextcolor(YELLOW);
	setaspectratio(1, 1);// �������嵹��
	settextstyle(30, 0, L"����");
	outtextxy(450, -185, L"EasyPlot");
	settextstyle(10, 0, L"����");
	outtextxy(850, 160, L"Author:Ephemeroptera");
	outtextxy(870, 180, L"Version:1.2.0");
	// ���ƿ̶�
	unsigned short yVertex = 2 * ySegment + 1;
	double yUnit = YLIM / ySegment;
	setbkmode(TRANSPARENT);
	settextcolor(YELLOW);
	settextstyle(15, 0, L"10");
	setlinestyle(PS_DASH, 1);				// ����
	// ˮƽ�̶���
	for (int i = 1; i <= yVertex; ++i)
	{
		// ���� y �̶�ֵ
		double label = YLIM - (i - 1)*yUnit;
		wchar_t* buffer;
		num2WSTR(label, buffer);
		outtextxy(-30, (int)((i - ySegment - 1)*(ROWS / ySegment)) - 10, buffer);
		delete[] buffer;
		buffer = (wchar_t*)NULL;

		// ��������
		line(0, (int)((i - ySegment - 1)*(ROWS / ySegment)), 1000, (int)((i - ySegment - 1)*(ROWS / ySegment)));
	}
	setaspectratio(1, -1);					// �ָ����귽��
	canvas = GetWorkingImage();				// �����ַ
	getimage(&local, -50, -160, 1100, 320);	// ����ֲ�����
}


// ���´�
void DynaWin::UpateWin(double y)	// ���� win
{
	++DynaNum;										// ��Ϣ����
	UpdateAxisX();									// ����AxisX

	if (DynaNum <= xResolution + 1)					// ����δ��
		DynaQue[DynaNum - 1] = y;

	else	// ��������
	{
		for (int i = 0; i <= xResolution - 1; ++i)	// ������
		{
			DynaQue[i] = DynaQue[i + 1];			// ������λ
		}
		DynaQue[xResolution] = y;					// β�������Ԫ��
	}
}

// ���ƴ�
void DynaWin::ShowWin()
{
	// ѡ������
	SetWorkingImage(canvas);

	// ��������	
	putimage(-50, -160, &local);

	// (1) ��ʾ AxisX
	setlinecolor(RED);
	setlinestyle(PS_DASH, 2);
	for (int j = 0; j <= xSegment - 1; ++j)
	{
		// ��������
		line((int)xAxis[j].index, -150, (int)xAxis[j].index, 150);
		// ���Ʊ�ע
		setaspectratio(1, 1);
		setbkmode(TRANSPARENT);
		settextcolor(YELLOW);
		settextstyle(15, 0, L"10");
		double label = xAxis[j].label;
		wchar_t* wstr;
		num2WSTR(label, wstr);
		outtextxy((int)xAxis[j].index - 10, 0, wstr);
		delete[] wstr;
		wstr = NULL;
		setaspectratio(1, -1);						// �ظ�����ϵ
	}

	// (2) ��ʾ DynaQue
	setlinecolor(WHITE);
	setlinestyle(PS_SOLID | PS_ENDCAP_ROUND | PS_JOIN_ROUND, 2);
	if (DynaNum <= xResolution)						// ����δ��
	{
		for (int i = 0; i <= DynaNum - 2; ++i)		// 0 to DynaNum-1 (DynaNum ��)
		{
			line((int)(i*COLS / xResolution), (int)(DynaQue[i] / YLIM * ROWS), (int)((i + 1)*COLS / xResolution), (int)(DynaQue[i + 1] / YLIM * ROWS));
		}
	}
	else	// ��������
	{
		for (int i = 0; i <= xResolution - 1; ++i)	// 0 to xResolution (xResolution + 1 ��) ����ʾȫ�� DynaQue
		{
			line((int)(i * COLS / xResolution), (int)(DynaQue[i] / YLIM * ROWS), (int)((i + 1)*COLS / xResolution), (int)(DynaQue[i + 1] / YLIM * ROWS));
		}
	}
}

// ��������
void DynaWin::UpdateAxisX()
{
	if (DynaNum <= xResolution)										// ����δ��
		for (int i = 0; i <= xSegment - 1; ++i)
		{
			xAxis[i].index = (i + 1)*COLS / xSegment;
			xAxis[i].label = (i + 1)*XLIM / xSegment;
		}
	else	// ��������
	{

		for (int i = 0; i <= xSegment - 1; ++i)						// �����ƶ�
		{
			xAxis[i].index -= COLS / xResolution;
		}
		if (xAxis[0].index <= 0)									// AxisX ��̬����
		{
			int j;
			for (j = 0; j <= xSegment - 2; ++j)						// ���и���
			{
				xAxis[j].index = xAxis[j + 1].index;
				xAxis[j].label = xAxis[j + 1].label;
			}
			xAxis[j].index = xAxis[j - 1].index + COLS / xSegment;	// β�������Ԫ��
			xAxis[j].label = xAxis[j - 1].label + XLIM / xSegment;
		}
	}
}