#include "transparent.h"

// copy img2 to img1
void copy_img(IMAGE* img1, IMAGE* img2)
{
	IMAGE* now_working = GetWorkingImage();
	Resize(img1, img2->getwidth(), img2->getheight());
	SetWorkingImage(img2);
	getimage(img1, 0, 0, img1->getwidth(), img1->getheight());
	SetWorkingImage(now_working);
}

// ��ͼ����
// ����:
//		dstX,dstY:��ͼ��������
//		*pimg��ͼƬָ��
//		avoid_color��͸����ɫ
//		deviation��͸����ϸ��
//		light�����ȼӳɣ�1 ���䣩
//		tp(transparency)��͸���ȣ��� 0 �� 100
//		effect��Ч����1 Ϊ���࣬2 Ϊ�ڰף�����Ϊ�ޣ�
void my_putimage(int dstX, int dstY, IMAGE *pimg, int avoid_color, int deviation, double light, int tp, int effect)
{
	int x, y, num;
	int R, G, B;			// ��¼��ͼĳ��ɫ��
	// ��¼�ų���ɫɫ��
	int avoid_r = GetRValue(avoid_color);
	int avoid_g = GetGValue(avoid_color);
	int avoid_b = GetBValue(avoid_color);
	IMAGE pSrcImg;			// ����ͼ
	IMAGE tempimg;			// ��ʱ��ͼ
	copy_img(&tempimg, pimg);
	SetWorkingImage(NULL);	// ��Ĭ�ϻ�ͼ���ڵĻ�ͼ����
	getimage(&pSrcImg, dstX, dstY, pimg->getwidth(), pimg->getheight());

	// ͸�����ݴ�
	if (tp < 0)tp = 0;
	else if (tp > 100)tp = 100;

	// ��ȡ����ָ���Դ��ָ��
	DWORD* bk_pMem = GetImageBuffer(&pSrcImg);

	// ��ͼָ���Դ��ָ��
	DWORD* pMem = GetImageBuffer(&tempimg);
	for (y = 0; y < pimg->getheight(); y++)
	{
		for (x = 0; x < pimg->getwidth(); x++)
		{
			num = y * pimg->getwidth() + x;
			R = GetRValue(pMem[num]);
			G = GetGValue(pMem[num]);
			B = GetBValue(pMem[num]);
			if ((abs(R - avoid_r) <= deviation) && (abs(G - avoid_g) <= deviation) && (abs(B - avoid_b) <= deviation))
			{
				pMem[num] = bk_pMem[num];
			}
			else
			{
				if (light > 0 && light < 1)
				{
					R = int(R * light);
					G = int(G * light);
					B = int(B * light);
				}
				else if (light > 1)
				{
					R = min(int(R * light), 255);
					G = min(int(G * light), 255);
					B = min(int(B * light), 255);
				}
				if (effect == 1)//����
				{
					pMem[num] = 0xffffff - pMem[num];
					continue;
				}
				else if (effect == 2)//�ڰ�
				{
					R = G = B = int(R * 0.299 + G * 0.587 + B * 0.114);
				}
				pMem[num] = RGB((R * tp + GetRValue(bk_pMem[num]) * (100 - tp)) / 100,
								(G * tp + GetGValue(bk_pMem[num]) * (100 - tp)) / 100,
								(B * tp + GetBValue(bk_pMem[num]) * (100 - tp)) / 100);
			}
		}
	}
	putimage(dstX, dstY, &tempimg);
}