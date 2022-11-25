#pragma once



#include "Head.h"



//***** �� *****//

// ��Ϸ����
class CGame
{
public:
	CGame();								// ���캯��
	~CGame();								// ��������

	virtual void inter_Face_Running() = 0;	// ����ӿ�
	
protected:
	void clear_Board();						// ���Ʊ���
};
// ��Ϸ����



// ��ʼ������
class CBegin : public CGame
{
public:
	CBegin();					// ���캯��
	~CBegin();					// ��������

	void inter_Face_Running();	// ��ʼ����

private:
	void draw_Title();			// ���Ʊ���
};
// ��ʼ������



// ���ڽ�����
class CAbout : public CGame
{
public:
	CAbout();					// ���캯��
	~CAbout();					// ��������

	void inter_Face_Running();	// ���ڽ���

private:
	void draw_Text();			// �������
};
// ���ڽ�����



// �ؿ�������
class CLevel : public CGame
{
public:
	CLevel();					// ���캯��
	~CLevel();					// ��������

	void inter_Face_Running();	// �ؿ�����

private:
	int stat();					// ͳ�ƹؿ�
};
// �ؿ�������



// ��Ϸ������
class CPlay : public CGame
{
public:
	CPlay();						// ���캯��
	~CPlay();						// ��������

	void inter_Face_Running();		// ��Ϸ����
	void read_Level();				// ��ȡ�ؿ�
	void draw_Title();				// ���Ʊ���
	void draw_Paper();				// ����ֽ��
	void draw_Graph();				// ����ͼ
	void point_Move(int point_id);	// �ƶ���
	void clear();					// ���
	bool if_Win();					// ʤ���ж�
	
	static int point_num, line_num;	// ����������
};
// ��Ϸ������



// ���ؽ�����
class CWin : public CGame
{
public:
	CWin();						// ���캯��
	~CWin();					// ��������

	void inter_Face_Running();	// ���ؽ���

private:
	void change_Best_Time();	// �޸����ʱ��
	void draw_Title();			// ���Ʊ���
};
// ���ؽ�����



// ����
class CPoint
{
public:
	CPoint( int x = 0, int y = 0, 
			bool move = 1, bool moving = 0);	// ���캯��
	~CPoint();									// ��������

	int x, y;									// ����
	bool move;									// �Ƿ���ƶ����Ƿ������ƶ�
};
// ����



// ����
class CLine
{
public:
	CLine(int a = 0, int b = 0);				// ���캯��
	~CLine();									// ��������

	double vector_Mult(int a, int b, int c);	// �������
	bool line_Cross(CLine l);					// �ж��߶��Ƿ񽻲�

	int a, b;									// ���
};
// ����



// ��ť��
class CButton
{
public:
	CButton();								// ���캯��
	~CButton();								// ��������

	void set_X_Y(int x, int y);				// ��������
	void set_Image(IMAGE image);			// �������
	int get_X() const; int get_Y() const;	// ��ȡ����
	IMAGE get_Image() const;				// ��ȡ���
	void draw_Button() const;				// ���ư�ť
	bool if_Mouse_On(MOUSEMSG &m) const;	// ��ť��

private:
	int x, y;								// ��ť����
	IMAGE image;							// ��ť���
};
// ��ť��



// ��ťͼ����
class CButton_Image
{
public:
	CButton_Image();																// ���캯��
	~CButton_Image();																// ��������

	IMAGE start_Button(COLORREF color);												// ��ʼ��ťͼ��
	IMAGE help_Button(COLORREF color);												// ������ťͼ��
	IMAGE close_Button(COLORREF color);												// �رհ�ťͼ��
	IMAGE level_Button(const wchar_t num[], const wchar_t tim[], COLORREF color);	// �ؿ���ťͼ��
	IMAGE return_Button(COLORREF color);											// ���ذ�ťͼ��
	IMAGE again_Button(COLORREF color);												// ������ťͼ��
	IMAGE next_Button(COLORREF color);												// ��һ�ذ�ťͼ��
	IMAGE ok_Button(COLORREF color);												// O K ��ťͼ��
};
// ��ťͼ����

//***** �� *****//