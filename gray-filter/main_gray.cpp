/////////////////////////////////////////////////////////
// �������ƣ���ɫͼƬת��Ϊ�ҽ�ͼƬ
// ���뻷����Visual C++ 6.0 / 2010��EasyX 20130322(beta)
// ��    �ߣ�krissi <zh@easyx.cn>
// ����޸ģ�2013-1-19
//
#include <graphics.h>
#include <conio.h>


// ��ɫͼ��ת��Ϊ�Ҷ�ͼ��
void  ColorToGray(IMAGE *pimg)
{
	DWORD *p = GetImageBuffer(pimg);	// ��ȡ��ʾ������ָ��
	COLORREF c;

	// ������ص��ȡ����
	for (int i = pimg->getwidth() * pimg->getheight() - 1; i >= 0; i--)
	{
		c = BGR(p[i]);
		c = (GetRValue(c) * 299 + GetGValue(c) * 587 + GetBValue(c) * 114 + 500) / 1000;
		p[i] = RGB(c, c, c);	// �����ǻҶ�ֵ��������ִ�� BGR ת��
	}
}


// ������
int main()
{
	// ��ʼ����ͼ����
	initgraph(640, 640);
	// ��ȡͼ��
	IMAGE img;
	loadimage(&img, _T("c:\\test.jpg"));
	// ��ʾԭʼͼ��
	putimage(0, 0, &img);
	// �������ת��Ϊ�Ҷ�ͼ��
	_getch();
	// ����ͼ��Ϊ�Ҷ�
	ColorToGray(&img);
	// ��ʾ������ͼ��
	putimage(0, 0, &img);
	// �رջ�ͼ����
	_getch();
	closegraph();
	return 0;
}