#pragma once



#include <graphics.h>
#include <conio.h>
#include <cmath>
#include <ctime>
#include <fstream>



//***** ���� *****//

#define WIN_WIDTH			480					// ���ڿ��
#define WIN_HEIGHT			640					// ���ڸ߶�
#define BKCOLOR				RGB(246, 231, 184)	// ������ɫ
#define GAME_NAME			TEXT("������")		// ��Ϸ����
#define TEXT_COLOR			RGB(42, 19, 0)		// ������ɫ
#define BASE_COLOR			RGB(105, 85, 70)	// ������ɫ
#define INF					2147483647			// �����
#define PAPER_POINT_WIDTH	10					// ֽ������
#define PAPER_POINT_HEIGHT	11					// ֽ�������
#define DISLEN				40					// ֽ�̸����
#define PAPER_WIDTH			440					// ֽ�̿��
#define PAPER_HEIGHT		480					// ֽ�̸߶�
#define BIG_POINT_R			15					// ���뾶
#define SMALL_POINT_R		7					// С��뾶
#define PAPER_POINT_R		2					// ���뾶



const double	PI		= acos(-1);							// Բ����
const int		BEGIN_X = (WIN_WIDTH -  PAPER_WIDTH) / 2;	// ֽ�̿�ʼ����
const int		BEGIN_Y = (WIN_HEIGHT - PAPER_HEIGHT) / 2;	// ֽ�̽�������

//***** ���� *****//