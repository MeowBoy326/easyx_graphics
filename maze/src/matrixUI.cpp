#include"matrixUI.h"
//���캯��
MatrixUI::MatrixUI() {

}

//˽�з���
bool MatrixUI::getInitFlag(void) {//����Ƿ��Ѿ���������
	return _initFlag;
}
void MatrixUI::init(int width, int height) {//��������
	if (width < 500 || width>10000 || height < 500 || height>10000) {
		return;
	}
	if (_initFlag == false) {//ֻ�ܴ���һ��ͼ�ν���
		initgraph(width, height, EW_SHOWCONSOLE);
		//initgraph(width, height);
		_initFlag = true;
		_width = width;
		_height = height;
		setorigin(0,0);//����ԭ������
	}
}
void MatrixUI::close(void) {//�رս���
	if (getInitFlag()) {
		closegraph();
		_initFlag = false;
		_width = 0;
		_height = 0;
	}
}

void MatrixUI::setBkColor(char r, char g, char b) {//���ñ���ͼ����ɫ
	if (getInitFlag() == false) {
		return;
	}
	// ���ñ���ɫΪ��ɫ
	setbkcolor(RGB(r,g,b));
	// �ñ���ɫ�����Ļ
	cleardevice();
}

void MatrixUI::setUIBuffer(struct Point point, char r, char g, char b) {
	if (_initFlag == false || point.x < 0 || point.x >= _width || point.y < 0 || point.y >= _height) {
		return;
	}
	// ��ȡָ����ʾ��������ָ��
	DWORD* pMem = GetImageBuffer();
	// ֱ�Ӷ���ʾ��������ֵ
	pMem[_width * point.y + point.x] = BGR(RGB(r, g, b));
}

int	 MatrixUI::getWidth(void) {
	return _width;
}
int	 MatrixUI::getHeight(void) {
	return _height;
}
