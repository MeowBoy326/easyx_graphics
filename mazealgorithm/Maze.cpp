// Maze.cpp : ���򿪶��ļ�

#include "Game.h"						// ��Ϸͷ�ļ�

// ����������
int main()
{
	srand((unsigned int)time(NULL));	// �������

	initgraph(640, 480);				// ����ͼ�λ�����

	CAdventrue* bed = new CAdventrue();
	bed->game();						// ��ʼ��Ϸ

	delete bed;
	bed = NULL;

	closegraph();
	return 0;							// ��Ϸ����
}