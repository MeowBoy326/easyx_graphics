#include "Game_Class.h"



extern MOUSEMSG msg;	// �����Ϣ



//***** ��ʼ�������Ա����ʵ�� *****//

CGame::CGame() {}	// ���캯��
CGame::~CGame() {}	// ��������



// ���Ʊ���
void CGame::clear_Board()
{
	setbkcolor(BKCOLOR);
	cleardevice();
}
// ���Ʊ���

//***** ��ʼ�������Ա����ʵ�� *****//
