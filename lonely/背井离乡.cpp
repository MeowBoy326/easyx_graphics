#include <graphics.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <stdio.h>
#pragma comment(lib,"Winmm.lib")

#define WATERSPEED	12.0									// ����ٶ�
#define BUILDINGNUM	30										// ����������
#define RAINNUM		300										// �������
#define CARSPEED	3.0										// �ƶ��ٶ�
#define TIME		5										// ����ʱ��

struct water
{
	double waterx;											// �������
	double watery;
};

struct build
{
	int howx;												// �������С�����������ʹ�С���Լ��������λ��
	int howy;
	int windownumx;
	int windownumy;
	int maxmin;
	double wherex;
};

water rain[RAINNUM];
IMAGE built[BUILDINGNUM];
build building[BUILDINGNUM];

bool ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName)
{
	// �����ļ�
	HANDLE hFile = ::CreateFile(strDstFile, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return false;

	// ������Դ�ļ��С�������Դ���ڴ桢�õ���Դ��С
	HRSRC	hRes	= ::FindResource(NULL, strResName, strResType);
	HGLOBAL	hMem	= ::LoadResource(NULL, hRes);
	DWORD	dwSize	= ::SizeofResource(NULL, hRes);
	
	// д���ļ�
	DWORD dwWrite = 0;			// ����д���ֽ�
	::WriteFile(hFile, hMem, dwSize, &dwWrite, NULL);
	::CloseHandle(hFile);

	return true;
}

void start()
{
	int a;
	void creator(int);
	initgraph(640, 480);
	setbkcolor(RGB(50, 50, 50));
	srand(time(NULL));
	BeginBatchDraw();
	for(a = 0; a < RAINNUM; a++)							// ��ʼ�� ���ͽ�����
	{
		rain[a].waterx = rand() % int(639 + (CARSPEED / WATERSPEED) * 480) - (CARSPEED / WATERSPEED) * 480;
		rain[a].watery = rand() % 480;
	}
	for(a = 0; a < BUILDINGNUM; a++)
	{
		creator(a);
		building[a].wherex = rand () % (639 + building[a].howx) - building[a].howx;
	}
}

void creator(int gate)
{
	int m,n,z,men;											// ��ʼ��������Ԫ�ز���������������С���γ�ͼ��
	building[gate].maxmin = rand() % 6 + 8;
	building[gate].windownumx = rand() % 4 + 2;
	building[gate].windownumy = rand() % 8 + 2;
	building[gate].howx = building[gate].maxmin * (2 * building[gate].windownumx + 1);
	building[gate].howy = building[gate].maxmin * (2 * building[gate].windownumy + 1);
	m=rand () % 31 + 70;
	setfillcolor(RGB(m, m, m));
	solidrectangle(0, 0, building[gate].howx, 479 - building[gate].howy);
	for(m = 1; m <= building[gate].windownumx; m++)
	{
		for(n = 1; n <= building[gate].windownumy; n++)
		{
			z = rand() % 5;
			switch(z)
			{
				case 0:
					men = rand() % 21 + 40;
					setfillcolor(RGB(men, men, men));
					break;
				case 1:
					men = rand() % 21 + 40;
					setfillcolor(RGB(men, men, men));
					break;
				case 2:
					men = rand() % 21 + 40;
					setfillcolor(RGB(men, men, men));
					break;
				case 3:
					men = rand() % 21 + 40;
					setfillcolor(RGB(men, men, men));
					break;
				case 4:
					setfillcolor(RGB(255, 193, 37));
					break;
			}
			solidrectangle(building[gate].maxmin * (m * 2 - 1),	building[gate].maxmin * (n * 2 - 1),
						   building[gate].maxmin * (m * 2),		building[gate].maxmin * (n * 2));
		}
	}
	getimage(&built[gate], 0, 0, building[gate].howx, building[gate].howy);
}

void draw()
{
	int a;													// ��齨�����Ƿ񳬳����ڱ߽磬��������ʼ��������
	for(a = 0; a < BUILDINGNUM; a++)
	{
		building[a].wherex = building[a].wherex + CARSPEED / TIME;
		if (building[a].wherex > 639) 
		{
			creator(a);
	     	building[a].wherex = - building[a].howx;
		}
	}
	cleardevice();
	for(a = 0; a < RAINNUM; a++)							// ͬ��
	{
		rain[a].waterx = rain[a].waterx + CARSPEED / TIME;
		rain[a].watery = rain[a].watery + WATERSPEED / TIME;
		if (rain[a].waterx > 639 || rain[a].watery > 479) 
		{
			rain[a].waterx = rand() % int(639 + (CARSPEED / WATERSPEED) * 480) - (CARSPEED / WATERSPEED) * 480;
			rain[a].watery = 0 ;
		}

	}
	for(a = 0; a < BUILDINGNUM; a++)						// ����ͼ��
		putimage(int(building[a].wherex), 479 - building[a].howy, &built[a]);
	for(a = 0; a < RAINNUM; a++)
		putpixel(int(rain[a].waterx), int(rain[a].watery), RGB(255, 255, 255));
}

int main()
{
	start();
	char s[300];
	char tmpmid[_MAX_PATH];									// ����
	::GetTempPath(_MAX_PATH, tmpmid);
	strcat(tmpmid, "playmid_background.mid");
	ExtractResource(tmpmid, _T("MUSIC"), _T("1.mid"));

	sprintf(s, "open \"%s\" alias mymusic", tmpmid);
	mciSendString(s, NULL, 0, NULL);
	mciSendString(_T("play mymusic"), NULL, 0, NULL);
	while(1)
	{
		draw();

		FlushBatchDraw();
		Sleep(5);
	}
	EndBatchDraw();
	closegraph();
	mciSendString(_T("stop mymusic"), NULL, 0, NULL);
	mciSendString(_T("close mymusic"), NULL, 0, NULL);
	DeleteFile(tmpmid);
	return 0;
}