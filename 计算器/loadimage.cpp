#include "loadimage.h"

IMAGE  setimage(int wigth, int height, COLORREF rgb)
{
	IMAGE blacks(wigth, height);	// ���� img ����

	SetWorkingImage(&blacks);		// ���û�ͼĿ��Ϊ img ����
	setfillcolor(rgb);
	solidrectangle(0, 0, wigth, height);

	SetWorkingImage();				// ���û�ͼĿ��Ϊ��ͼ����

	return blacks;
}