#pragma once
#include <math.h>
#include <conio.h>
#include <graphics.h>

void copy_img(IMAGE* img1, IMAGE* img2);		// copy img2 to img1

// ��ͼ����
// ����:
//		dstX,dstY:��ͼ��������
//		*pimg��ͼƬָ��
//		avoid_color��͸����ɫ
//		deviation��͸����ϸ��
//		light�����ȼӳɣ�1 ���䣩
//		tp(transparency)��͸���ȣ��� 0 �� 100
//		effect��Ч����1 Ϊ���࣬2 Ϊ�ڰף�����Ϊ�ޣ�
void my_putimage(int dstX, int dstY, IMAGE *pimg, int avoid_color, int deviation, double light, int tp, int effect);
