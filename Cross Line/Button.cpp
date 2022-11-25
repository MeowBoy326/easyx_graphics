#include "Game_Class.h"



extern MOUSEMSG msg;	// �����Ϣ



//***** ��ť���Ա����ʵ�� *****//

CButton::CButton() {}															// ���캯��
CButton::~CButton() {}															// ��������
void CButton::set_X_Y(int x, int y) { this->x = x;	this->y = y; }				// ��������
void CButton::set_Image(IMAGE image) { this->image = image; }					// �������
int CButton::get_X() const { return this->x; }									// ��ȡX����
int CButton::get_Y() const { return this->y; }									// ��ȡY����
IMAGE CButton::get_Image() const { return this->image; }							// ��ȡ���
void CButton::draw_Button() const { putimage(this->x, this->y, &this->image); }	// ���ư�ť



// ��ť��
bool CButton::if_Mouse_On(MOUSEMSG &m) const
{
	if (m.x > this->x && m.x < this->x + this->image.getwidth() &&
		m.y > this->y && m.y < this->y + this->image.getheight())
		return true;
	return false;
}
// ��ť��

//***** ��ť���Ա����ʵ�� *****//
