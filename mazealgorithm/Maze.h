// Maze.h : ��ʼ��ͷ�ļ�

// Start
#pragma once			// ��ֹ��ͷ�ļ�����ε���

// Head
#include <time.h>		// ʱ����Ϊ�����������
#include <conio.h>		// ��ȡ������Ϣ��
#include <vector>		// ʹ�� STL vector
#include <algorithm>	// ʹ�� random_shuffle ����
#include <graphics.h>	// ����ͼ�ο�ͷ�ļ�

// Block
enum BLOCK {WALL = 1, END, YOU, ROAD};	// ǽ���յ㣬��㣬·

// Box
#define MY_OK 0							// ֻ�С�ȷ������ť
#define MY_YESNO 1						// �С��ǡ���ť�͡��񡱰�ť

//Other
#define INF 2147483647					// ���޴� Prim ��������Թ���