#include"prim.h"
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<ctime>
using namespace std;
//Prim��������Թ����캯��
Prim::Prim(int width, int height) {
	_width = width;
	_height = height;
	_Map = (char**)malloc(sizeof(char*) * height);
	for (int i = 0; i < height; i++) {
		*(_Map + i) = (char*)malloc(sizeof(char) * width);
	}
	for (int i = 0; i < height; i++) {//��ʼ��ȫ����Ϊ'0'
		for (int j = 0; j < width; j++) {
			_Map[i][j] = '0';
		}
	}
}
Prim::~Prim() {
	for (int i = 0; i < _height; i++) {
		free(*(_Map + i));
	}
	free(_Map);
}




/*
Prim��������Թ��㷨
1.���Թ�ȫ��ǽ�� ʵ��: �ⲿ���� Prim::createMaze��
2.ѡһ����Ԫ����Ϊ�Թ���ͨ·(�ڴ�ѡ�����)��Ȼ���������ǽ���������ң������б�
3.���б����滹��ǽʱ:
��.���б������ѡһ��ǽ���������ǽ�ָ���������Ԫ��ֻ��һ����Ԫ�񱻷��ʹ�
	��a�����б������Ƴ�����ǽ�������Ͱ�ǽ��ͨ�ˣ���Ϊ���ʹ��ĵ�Ԫ���Ϊ�Թ���ͨ·
	��b����������ӵ�ǽ�����б�
��.���ǽ����ĵ�Ԫ���Ѿ������ʹ�������ͨ�ˣ����Ǿʹ��б����Ƴ�����ǽ
*/      
void Prim::_algorithm(void) {
	srand((unsigned)time(NULL));//���������
	Point start, end;
	struct Block pathfinder;
	start.x = 1;//���
	start.y = 1;
	pathfinder.x = start.x;//̽·��
	pathfinder.y = start.y;
	end.x = _width - 2;//�յ�
	end.y = _height - 2;
	vector<struct Block> list;//��ŵ�
	//ѡ�����Ϊ�Թ���ͨ·�����������������ҷ����б�
	_addBlockToList(list, pathfinder);
	while (list.size()) {
		int randnum = rand() % list.size();
		Block selectBlock = list[randnum];
		//̽·��������ѡ���ǽ������
		pathfinder = selectBlock;
		//���ݵ�ǰѡ���ǽ�ķ�����к�������
		//��ʱ����ʼ�� ѡ���ǽ Ŀ��� ����������ͬһֱ����
		//�����ÿ󹤴ӡ�ѡ���ǽ������ǰ������Ŀ��顱
		//���д�ǽ���� ��)
		switch (selectBlock.direction) {
			case 1: {//��
				pathfinder.y++;
				break;
			}
			case 3: {//��
				pathfinder.x++;
				break;
			}
			case 2: {//��
				pathfinder.x--;
				break;
			}
			case 0: {//��
				pathfinder.y--;
				break;
			}
		}
		//Ŀ��������ǽ
		if (_Map[pathfinder.y][pathfinder.x] == '1') {
			//��ͨǽ��Ŀ���
			_Map[selectBlock.y][selectBlock.x] = _Map[pathfinder.y][pathfinder.x] = '0';
			//�ٴ��ҳ���󹤵�ǰλ�����ڵ�ǽ
			_addBlockToList(list, pathfinder);
		}
		else {//��������أ�˵�����ǵĿ��ڵ���һ���տ���ͨ·���� ��Ϣһ�¾ͺ���
			//relax
		}
		//ɾ�����ǽ(���ò��˵�ǽɾ�ˣ�������Щ�Ѿ�ʩ�����˲�����ʩ���ˣ�ͬʱҲ��ȷ������������ѭ��)
		list.erase(list.begin() + randnum);
	}
}

//��ָ���ĵ���������ҺϷ��ĵ���뵽�б���
void Prim::_addBlockToList(vector<struct Block>&list, struct Block center) {
	struct Block p;
	p.x = center.x + 1;//��
	p.y = center.y;
	if (p.x >= 1 && p.y >= 1 && p.x <= _width - 2 && p.y <= _height - 2&&_Map[p.y][p.x]=='1') {
		p.direction = 3;
		list.push_back(p);
	}
	p.x = center.x - 1;//��
	p.y = center.y;
	if (p.x >= 1 && p.y >= 1 && p.x <= _width - 2 && p.y <= _height - 2 && _Map[p.y][p.x] == '1') {
		p.direction = 2;
		list.push_back(p);
	}
	p.x = center.x;//��
	p.y = center.y-1;
	if (p.x >= 1 && p.y >= 1 && p.x <= _width - 2 && p.y <= _height - 2 && _Map[p.y][p.x] == '1') {
		p.direction = 0;
		list.push_back(p);
	}
	p.x = center.x;//��
	p.y = center.y + 1;
	if (p.x >= 1 && p.y >= 1 && p.x <= _width - 2 && p.y <= _height - 2 && _Map[p.y][p.x] == '1') {
		p.direction = 1;
		list.push_back(p);
	}
}













bool Prim::_judgePoint(int x, int y) {
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


void Prim::printMap(void) {
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

void Prim::setPoint(int x, int y, char val) {
	_Map[y][x] = val;
}
char Prim::getPoint(int x, int y) {
	return _Map[y][x];
}


//ˢ���Թ�����
void Prim::createMaze(void) {
	//���Թ�ȫ����Ϊǽ
	for (int i = 0; i < _height; i++) {
		for (int j = 0; j < _width; j++) {
			_Map[i][j] = '1';
		}
	}
	_Map[1][0] = '1';
	_Map[_height - 2][_width - 1] = '0';//����λ��
	//�����Ϊ'0'
	_Map[1][1] = '0';
	_algorithm();//Prim��������Թ��㷨
}

void Prim::resetMap() {
	for (int i = 0; i < _height; i++) {
		for (int j = 0; j < _width; j++) {
			_Map[i][j] = '0';
		}
	}
}