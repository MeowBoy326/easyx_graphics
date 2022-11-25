/***************
			�ú��������ڱ���ɫ�ϴ������
			��������Ҫ��ʾ����Ļ�ϵ�����Ч��ͼƬ�뱳�� XOR ����
			����ȡ�������Ч��ͼ���ô�Ч��ͼ�����뱳�� XOR �������Ч��ͼ
									****************************/

#include "circleball.h"


									// �� p ͼƬ�����Ļ�ȡ�뾶Ϊ r ��Բ�β��֣�����ɫ color λ������õ�����ͼƬ����� Img
void CircleImg(IMAGE* Img, COLORREF color, IMAGE* p, int r, DWORD dwRop)
{
	IMAGE* save = GetWorkingImage();				// ��¼֮ǰ�Ļ�ͼ�豸����������ʱ����ص����豸!!

	SetWorkingImage(p);							// �ڴ������Ķ����ϲ���
	int width = getwidth();						// ��ȡ�� img �Ĵ�С
	int height = getheight();

	Resize(Img, 2 * r, 2 * r);					// �����������ս��
	IMAGE newimg(2 * r, 2 * r);					// ����Բ�����򣬸������� bkimg ����õ� Img

	IMAGE bkimg(2 * r, 2 * r);					// ����һ������ɫ�� img
	SetWorkingImage(&bkimg);
	setbkcolor(color);
	cleardevice();

	for (int ix = 0; ix < 2 * r; ix++)		// ɨ�����е㣬Բ����ñ���ɫ��Բ�ڸ��� p ����Ķ�Ӧ����
	{
		for (int iy = 0; iy < 2 * r; iy++)
		{
			double Lx = ix - r;
			double Ly = iy - r;

			if (Lx * Lx + Ly * Ly > r * r)		// ������Բ��Ĳ���
			{
				SetWorkingImage(&newimg);
				putpixel(ix, iy, color);			// Բ��Ū�ɱ���ɫ�������뱳�� img �Ժ�ͻ�õ���ɫ��
			}
			else									// ������԰�ڵĲ���
			{
				SetWorkingImage(p);				// �� p ��ȡ԰�ڵĲ���
				int pix2 = getpixel(ix + width / 2 - r, iy + height / 2 - r);

				SetWorkingImage(&newimg);
				putpixel(ix, iy, pix2);
			}
		}
	}

	SetWorkingImage(&bkimg);					// ��������ͼƬ�뱳��ɫ���
	putimage(0, 0, &newimg, dwRop);

	getimage(Img, 0, 0, 2 * r, 2 * r);		// ���������Ľ����� Img
	SetWorkingImage(save);
}


// ��Բ�� x��y �������Բ�� img  
void putcircle(int x, int y, IMAGE* img, DWORD dwRop)
{
	IMAGE* sav = GetWorkingImage();
	SetWorkingImage(img);
	int r = getwidth() / 2;

	SetWorkingImage(sav);
	putimage(x - r, y - r, img, dwRop);
}