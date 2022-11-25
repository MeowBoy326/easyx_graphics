#include"RecursiveSegmentation.h"
#include<cstdlib>
#include<cstdio>

//���캯��
Division::Division(int width, int height) {
	_width = width;
	_height = height;
	this->width = width;
	this->height = height;
	_Map = (char**)malloc(sizeof(char*) * height);
	for (int i = 0; i < height; i++) {
		*(_Map + i) = (char*)malloc(sizeof(char) * width);
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			_Map[i][j] = '0';
		}
	}
}

//��������
Division::~Division() {
	for (int i = 0; i < _height; i++) {
		free(*(_Map + i));
	}
	free(_Map);
}

void Division::printMap(void) {
	if (!_Map) {
		return;
	}
	for (int i = 0; i < _height; i++) {
		for (int j = 0; j < _width; j++) {
			printf("%c", _Map[i][j]);
		}
		printf("\n");
	}
}

void Division::setPoint(int x, int y, char val) {
	_Map[y][x] = val;
}
char Division::getPoint(int x, int y) {
	return _Map[y][x];
}


//ˢ���Թ�����
void Division::createMaze(void) {
	//������һȦΪǽ
	for (int i = 0; i < _height; i++) {
		_Map[i][0] = '1';
		_Map[i][_width-1] = '1';
	}
	for (int i = 0; i < _width; i++) {
		_Map[0][i] = '1';
		_Map[_height - 1][i] = '1';
	}
	//���ó��������
	_Map[_height - 2][_width - 1] = '0';
	//�����Թ�
	_Map[1][0] = '1';
	_algorithm(1, 1, _width - 2, _height - 2);
}

void Division::resetMap() {
	for (int i = 0; i < _height; i++) {
		for (int j = 0; j < _width; j++) {
			_Map[i][j] = '0';
		}
	}
}

//�ݹ�ָ������Թ��㷨
void Division::_algorithm(int ltx, int lty, int rbx, int rby) {
	////�ж��Ƿ��ܼ����ָ�
	if (rbx - ltx <= 1 || rby - lty <= 1) {//�ݹ����
		return;
	}
	//���ȥһ���㣬ʮ�ֻ��ֵ�ʮ������,���ĵ�ֻ����ż������ż����
	int x = ltx + 1 + rand() % (rbx - ltx - 1);
	int y = lty + 1 + rand() % (rby - lty - 1);


	//BUG���:2020/12/27 �����̫æ�ˣ�
	while (x % 2 != 0 || y % 2 != 0) {
		x = ltx + 1 + rand() % (rbx - ltx - 1);
		y = lty + 1 + rand() % (rby - lty - 1);
	}

	//��ǽ���ܰ���һ�δ�Ķ�����ס
	for (int i = ltx; i <= rbx; i++) {//���Ż�ǽ
		_Map[y][i] = '1';
	}
	for (int i = lty; i <= rby; i++) {//���Ż�ǽ
		_Map[i][x] = '1';
	}
	////�ݹ�ָ�
	_algorithm(ltx, lty, x - 1, y - 1);
	_algorithm(x + 1, y + 1, rbx, rby);
	_algorithm(x + 1, lty, rbx, y - 1);
	_algorithm(ltx, y + 1, x - 1, rby);

	////���ȡ���е�����ǽ
	int randWall[4] = { 0 };
	randWall[rand() % 4] = 1;

	////��ǽ�����ȡ���
	for (int i = 0; i < 4; i++) {
		if (randWall[i] == 0) {//Ҫ��
			int rx = x;
			int ry = y;
			switch (i)
			{
				//�жϸ�λ���Ƿ���ȷ����ͨ�������������ж����ݣ���������λ�����ֻ������ǽ
			case 0:
				do {
					rx = ltx + rand() % (x - ltx);
				} while (_judgePoint(rx,y));
				break;
			case 1:
				do {
					ry = y + 1 + rand() % (rby - y);
				} while (_judgePoint(x, ry));
				break;
			case 2:
				do {
					rx = x + 1 + rand() % (rbx - x);
				} while (_judgePoint(rx, y));
				break;
			case 3:
				do {
					ry = lty + rand() % (y-lty);
				} while ( _judgePoint(x, ry));
				break;
			default:
				break;
			}
			_Map[ry][rx] = '0';
		}
	}




}

bool Division::_judgePoint(int x, int y) {
	int sum = 0;
	if (_Map[y - 1][x] == '0') {
		sum++;
	}
	if (_Map[y + 1][x] == '0') {
		sum++;
	}
	if (_Map[y][x - 1] == '0') {
		sum++;
	}
	if (_Map[y][x + 1] == '0') {
		sum++;
	}
	if (sum < 2) {//������Χ��ǽС�ڵ���2��
		return 1;
	}
	else {
		return 0;
	}
}

