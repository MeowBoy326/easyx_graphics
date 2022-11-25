#pragma once
#ifndef __RECURSIVESEGMENTATION_H__
#define __RECURSIVESEGMENTATION_H__
class Division {
	private:
		char** _Map;
		int _width;
		int _height;
		void _algorithm(int tlx,int tly,int rbx,int rby);
		bool _judgePoint(int x, int y);
	public:
		int width;//ˮƽ���ȼ�Ϊx�ĳ���
		int height;//��ֱ���ȼ�Ϊy�ĳ���
		Division(int width, int height);//���캯��
		~Division();//��������
		void printMap(void);//��ӡ��ͼ
		void setPoint(int x, int y, char val);
		char getPoint(int x, int y);
		void createMaze(void);//ˢ���Թ�
		void resetMap(void);//�����Թ�
};


#endif