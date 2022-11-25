#include"libPage.h"
#include"RecursiveSegmentation.h"//�ݹ�ָ�
#include"prim.h"//Prim
#include"recursionTracing.h"//�ݹ����
#include"MazePathFind.h"//dfsѰ��

//972 251 1241 299

LibPage::LibPage(MatrixUI& UI):UI(UI){//���캯��
	for (int i = 0; i < 41; i++) {
		for (int j = 0; j < 29; j++) {
			_Map[j][i] = '0';
		}
	}
}

int LibPage::process(void) {
	//��ҳ��ͼ
	IMAGE img;
	loadimage(&img, _T("./img/libPage.png"));
	putimage(0, 0, &img);
	//������,�����Թ��ı߽��
	setlinecolor(RGB(212,123,66));
	rectangle(18,18,926,662);
	//ʵ����Ĭ�ϵ���Prim�����Թ�
	_defaultInit();

	MOUSEMSG m;//����¼�
	while (1) {
		//����Ƿ񵽴����յ�
		if (_body.x == 40 && _body.y == 27) {
			_WinPoPWindow();//����
			_setRandomBody();//�������������λ��
		}
		ExMessage message;
		if (peekmessage(&message, EM_CHAR | EM_MOUSE)) {//�а�������
			if (_game && message.message == WM_CHAR) {
				char input = message.ch;
				switch (input)
				{
				case 'w'://��
					_moveBody(_body.x, _body.y - 1);
					break;
				case 's'://��
					_moveBody(_body.x, _body.y + 1);
					break;
				case 'a'://��
					_moveBody(_body.x - 1, _body.y);
					break;
				case 'd'://��
					_moveBody(_body.x + 1, _body.y);
					break;
				default:
					break;
				}
			}
			if (message.lbutton)//����¼�
			{
				if (_judgeInRect(message, _buttonRange[5])) {//�˳�
					_game = false;
					return 0;
				}
				if (_judgeInRect(message, _buttonRange[2])) {//�ݹ�ָ�
					reverseStatus = false;
					_createMap(3);
					//�˵������ʼ��
					_setRandomBody();
					//��������
					_setLiangCang();
				}
				else if (_judgeInRect(message, _buttonRange[1])) {//�ݹ����
					reverseStatus = false;
					_createMap(2);
					//�˵������ʼ��
					_setRandomBody();
					//��������
					_setLiangCang();
				}
				else if (_judgeInRect(message, _buttonRange[0])) {//Prim�����Թ�
					reverseStatus = false;
					_createMap(1);
					//�˵������ʼ��
					_setRandomBody();
					//��������
					_setLiangCang();
				}
				else if (_judgeInRect(message, _buttonRange[3])) {
					reverseStatus = false;
					_game = _game ? false : true;
				}
				else if (_judgeInRect(message, _buttonRange[4]) && reverseStatus == false) {//�Թ�Ѱ��
					_findRoadAndShow();
					//��������
					_setLiangCang();
				}
				else if (_judgeInRect(message, _buttonRange[6])) {//��ת�Թ�
					reverseStatus = !reverseStatus;
					cout << "��ת�Թ�\n";
					_reverseMap();
				}
			}
		}
	}

}//process



void LibPage::_setBlockColor(int x, int y, char r, char g, char b) {
	//��22����Ϊ����
	struct Point point;
	//���Ͻ�Ϊ��20��20��
	int tlx = (x+1)*22;
	int tly = (y+1)*22;
	int rbx = tlx+22;
	int rby = tly + 22;
	for (int i = tlx; i < rbx; i++) {
		for (int j = tly; j < rby; j++) {
			point.x = i;
			point.y = j;
			_setUIBuffer(point, r, g, b);
		}
	}
}

void LibPage::_setUIBuffer(struct Point point, char r, char g, char b) {
	// ��ȡָ����ʾ��������ָ��
	DWORD* pMem = GetImageBuffer();
	// ֱ�Ӷ���ʾ��������ֵ
	pMem[1280 * point.y + point.x] = BGR(RGB(r, g, b));
}


bool LibPage::_judgeInRect(ExMessage& m, struct Rect rect) {
	if (m.x >= rect.ltx && m.x <= rect.rbx && m.y >= rect.lty && m.y <= rect.rby) {
		return true;
	}
	else {
		return false;
	}
}


void LibPage::_createMap(int type) {
	if (type == 1) {//���prim
		Prim map(41, 29);
		map.createMaze();
		//���½�����ʾ
		for (int i = 0; i < 41; i++) {
			for (int j = 0; j < 29; j++) {
				if (map.getPoint(i, j) == '1') {//ǽ
					_setBlockColor(i, j, 234, 123, 78);
				}
				else if (map.getPoint(i, j) == '0') {//��
					_setBlockColor(i, j, 255, 255, 255);
				}
			}
		}
		//����_Map
		for (int i = 0; i < 41; i++) {
			for (int j = 0; j < 29; j++) {
				_Map[j][i] = map.getPoint(i, j);
			}
		}
		this->printMap();//��ӡ��ͼ		
	}
	else if (type == 2) {//���ݵݹ�
		RecursionTracing map(41, 29);
		map.createMaze();
		//���½�����ʾ
		for (int i = 0; i < 41; i++) {
			for (int j = 0; j < 29; j++) {
				if (map.getPoint(i, j) == '1') {//ǽ
					_setBlockColor(i, j, 234, 123, 78);
				}
				else if (map.getPoint(i, j) == '0') {//��
					_setBlockColor(i, j, 255, 255, 255);
				}
			}
		}
		//����_Map
		for (int i = 0; i < 41; i++) {
			for (int j = 0; j < 29; j++) {
				_Map[j][i] = map.getPoint(i, j);
			}
		}
		this->printMap();//��ӡ��ͼ	
	}
	else if (type == 3) {//�ݹ�ָ�
		Division map(41, 29);
		map.createMaze();
		//���½�����ʾ
		for (int i = 0; i < 41; i++) {
			for (int j = 0; j < 29; j++) {
				if (map.getPoint(i, j) == '1') {//ǽ
					_setBlockColor(i, j, 234, 123, 78);
				}
				else if (map.getPoint(i, j) == '0') {//��
					_setBlockColor(i, j, 255, 255, 255);
				}
			}
		}
		//����_Map
		for (int i = 0; i < 41; i++) {
			for (int j = 0; j < 29; j++) {
				_Map[j][i] = map.getPoint(i, j);
			}
		}
		this->printMap();//��ӡ��ͼ
	}
}

void LibPage::printMap(void) {
	for (int i = 0; i < 29; i++) {
		for (int j = 0; j < 41; j++) {
			printf("%c", _Map[i][j]);
		}
		printf("\n");
	}
}

//��body�ƶ�
void LibPage::_moveBody(int x, int y) {
	if (x < 0 || x>40 || y < 0 || y>28) {//���Ϸ�λ��
		return;
	}
	if (_Map[y][x] != '1') {
		//�����ڵ�body����ʾ
		_setBlockColor(_body.x, _body.y, 255, 255, 255);
		//����λ�ú��body������ʾ
		_body.x = x;
		_body.y = y;
		_setBodyImg(_body.x, _body.y);
	}
}

//����Ŀ�ĵصĵ���
void LibPage::_WinPoPWindow(void) {
	PopUpModule popWindow;
	popWindow.show(L"./img/popWindow.png");
	int points[4];
	popWindow.getBackButton(points);
	Rect backButton = { points[0],points[1], points[2], points[3] };
	ExMessage message;
	while (1) {
		if (peekmessage(&message)) {
			if (message.lbutton) {
				if (_judgeInRect(message, backButton)) {//�˳�
					cout << "������\n";
					popWindow.reset();
					//�˻ص��յ㲢���յ�Ϳ��
					_setBlockColor(_body.x, _body.y, 255, 0, 0);
					_body.x = 0;
					_body.y = 1;
					//������������
					_setLiangCang();
					return;
				}
			}
		}
	}	
}


void LibPage::_findRoadAndShow(void) {
	char** temp=NULL;
	//�Ƚ�_Map����һ���������ܽ���ַ�����ⲿ
	temp = (char**)malloc(sizeof(char*) * _height);
	for (int i = 0; i < _height; ++i) {
		temp[i] = (char*)malloc(sizeof(char) * _width);
	}
	//����
	for (int i = 0; i < _height; ++i) {
		for (int j = 0; j < _width; ++j) {
			temp[i][j] = _Map[i][j];
		}
	}
	cout << "����dfs\n";
	//����dfs
	MazePathFind FindPath(temp, _width, _height);
	//����findPath����
	Road niceRoad=FindPath.findPath(_body.x,_body.y,_width-2,_height-2);
	if (!niceRoad) {//û�л����ȷ·����������
		cout << "û���ҵ�·��\n" << endl;
		return;
	}
	else {//����Ӧ�Թ�·����ʾ��������ȥ
		Road temp = niceRoad->next;//niceRoad�ڵ�Ϊbody���ڽڵ�
		while (temp) {
			//cout << "[" << temp->x << "," << temp->y << "]";
			//show color
			_setBlockColor(temp->x, temp->y, 0, 153, 51);
			temp = temp->next;
		}
		//��Road�����ڴ�����ͷ�
		temp = niceRoad;
		while (temp) {
			Road freeNode = temp;
			temp = temp->next;
			free(freeNode);
		}
	}


	//�ͷ���ʱ��ͼ�洢�ռ�
	for (int i = 0; i < _height; ++i) {
		free(temp[i]);
	}
	free(temp);
}


//Ĭ���Թ�����
void LibPage::_defaultInit(void) {
	_createMap(1);
	//�˵������ʼ��
	_setRandomBody();
	//��������
	_setLiangCang();
}

//��ʾ����
void LibPage::_setBodyImg(int x,int y) {
	if (x < 0 || x>40 || y < 0 || y>28) {//���Ϸ�λ��
		return;
	}
	_body.x = x;
	_body.y = y;
	//��22����Ϊ����
	struct Point point;
	//���Ͻ�Ϊ��20��20��
	int tlx = (x + 1) * 22;
	int tly = (y + 1) * 22;
	int rbx = tlx + 22;
	int rby = tly + 22;
	//��������ͼƬ
	IMAGE body;
	loadimage(&body, L"./img/cat.png");
	putimage(tlx, tly, &body);
}

//��������ͼƬ
void LibPage::_setLiangCang() {
	int x=40, y=27;
	_Map[y][x] = '0';
	//��22����Ϊ����
	struct Point point;
	//���Ͻ�Ϊ��20��20��
	int tlx = (x + 1) * 22;
	int tly = (y + 1) * 22;
	int rbx = tlx + 22;
	int rby = tly + 22;
	//��������ͼƬ
	IMAGE liangcang;
	loadimage(&liangcang, L"./img/liangcang.png");
	putimage(tlx, tly, &liangcang);
}

//�����������λ����������λ��,���λ�������㲻��ǽ
void LibPage::_setRandomBody() {
	//int center
	int target_x = (rand() % (20 - 14 + 1)) + 14, target_y = (rand() % (20 - 10 + 1)) + 10;
	while (_Map[target_y][target_x] == '1') {
		target_x = (rand() % (20 - 14 + 1)) + 14, target_y = (rand() % (20 - 10 + 1)) + 10;
	}
	//��������λ��
	_setBodyImg(target_x,target_y);
}

//��ת�Թ������������֣��Լ�����λ�õ�
void LibPage::_reverseMap() {
	//��תMap
	for (int i = 0; i <= 40; i++) {
		for (int j = 0; j <= 28; j++) {
			if (_Map[j][i] == '1') {
				_Map[j][i] = '0';
			}
			else {
				_Map[j][i] = '1';
			}
		}
	}
	//������ͼ
	//���½�����ʾ
	for (int i = 0; i <= 40; i++) {
		for (int j = 0; j <= 28; j++) {
			if (_Map[j][i] == '1') {//ǽ
				_setBlockColor(i, j, 234, 123, 78);
			}
			else if (_Map[j][i] == '0') {//��
				_setBlockColor(i, j, 255, 255, 255);
			}
		}
	}
	//��������
	_setRandomBody();
	//��������
	_setLiangCang();
	printMap();
}