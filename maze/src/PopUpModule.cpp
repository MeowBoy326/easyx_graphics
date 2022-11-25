#include"PopUpModule.h"
void PopUpModule::reset(void) {
	putimage(
		(_screenWidth - _popWidth) / 2,
		(_screenHeight - _popHeight) / 2,
		&_oldImg
	);
}
void PopUpModule::show(const wchar_t *filename) {
	IMAGE img;
	loadimage(&img,filename);
	_newImg = img;
	_popWidth = img.getwidth();
	_popHeight = img.getheight();
	_backButton = { 776+ (_screenWidth - _popWidth) / 2,800+ (_screenWidth - _popWidth) / 2,0+ (_screenHeight - _popHeight) / 2,22+ (_screenHeight - _popHeight) / 2 };
	//��ȡ��Ļ�����ͼ��
	getimage(
		&_oldImg,
		(_screenWidth - _popWidth) / 2,
		(_screenHeight-_popHeight)/2,
		_popWidth,
		_popHeight
	);
	//������������Ļ��
	// ����ͼ��
	cout << "show" << endl;
	putimage(
		(_screenWidth - _popWidth) / 2,
		(_screenHeight - _popHeight) / 2,
		&_newImg		
	);
}
void PopUpModule::getBackButton(int*point) {
	point[0] = _backButton.ltx;
	point[1] = _backButton.rbx;
	point[2] = _backButton.lty;
	point[3] = _backButton.rby;
}


