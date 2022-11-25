#pragma once



/* ********** ͷ�ļ� ********** */
#include <set>
#include <stack>
#include <vector>
#include <algorithm>
#include <iostream>
#include <easyx.h>



/* ********** ȫ������ ********** */
// ��ά��
struct Point2
{
	int x = 0;
	int y = 0;
	Point2() = default;
	Point2(int _x, int _y) :x(_x), y(_y) {}
	bool operator == (const Point2& _p2) { return x == _p2.x && y == _p2.y; }
};
// ��ά�㣬���ڷָ��������
struct Point4
{
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;
	Point4() = default;
	Point4(int _x1, int _x2, int _y1, int _y2) :x1(_x1), x2(_x2), y1(_y1), y2(_y2) {}
};
// �Թ�����״̬
enum CellState��int { PATH = 0, WALL, FLAG };



/* ********** �Թ����� ********** */
class MazeGraph
{
public:
	MazeGraph() = default;
	~MazeGraph() { closegraph(); }

	// �����Թ�������������Եһ����ǽ����Ե������ǽ��·��������
	void Init(int _sw, int _sh, int _row, int _col, bool _wall = true)
	{
		setlinecolor(DARKGRAY);
		width = _sh / _row;
		edog_x = (_sw - width * _row) / 2;
		edog_y = (_sh - width * _col) / 2;
		for (int i = 0; i < _row; ++i)
			for (int j = 0; j < _col; ++j)
				(_wall || i == 0 || j == 0 || i == _row - 1 || j == _col - 1) ? DrawWall(i, j) : DrawPath(i, j);
	}

	// ��ǽ
	void DrawWall(int _row, int _col) { Draw(_row, _col, LIGHTGRAY, true); }
	// ��·
	void DrawPath(int _row, int _col) { Draw(_row, _col, BLACK, false); }
	// ����ָ����ʽ�ķ���
	void Draw(int _row, int _col, COLORREF _co, bool _frame = true)
	{
		setfillcolor(_co);
		auto DrawRectangle = solidrectangle;
		if (_frame) DrawRectangle = fillrectangle;
		DrawRectangle(edog_x + _col * width, edog_y + _row * width, edog_x + _col * width + width - 1, edog_y + _row * width + width - 1);
	}

private:
	int width = 0;		// �Թ�����߿�
	int edog_x = 0;		// �Թ���Եλ��
	int edog_y = 0;		// �Թ���Եλ��
};



/* ********** A*Ѱ·���� ********** */
class A_Container
{
	struct Node
	{
		int x, y;
		int gVal, hVal, fVal;
		Node* parent;
		Node(int _x, int _y, int _g, int _h, Node* _p) :x(_x), y(_y), gVal(_g), hVal(_h), fVal(_g + _h), parent(_p) {}
	};

public:
	A_Container(const Point2& _start) :destPos(_start) {}
	~A_Container()
	{
		for (auto& no : openList) delete no;
		for (auto& no : closeList) delete no;
	}

	// ��ǰ�ڵ���ھӼ��� openList
	void pushOpenList(const Point2 _p2)
	{
		int gVal = 0;
		Node* par = nullptr;
		if (!closeList.empty()) { par = *(--closeList.end()); gVal = par->gVal + 1; }
		Node* temp = new Node(_p2.x, _p2.y, gVal, abs(_p2.x - destPos.x) + abs(_p2.y - destPos.y), par);
		if (_p2.x == destPos.x && _p2.y == destPos.y) p_destNode = temp;
		openList.insert(temp);
		temp = nullptr;
	}

	// �� openList ��ȡ�� fVal ֵ��С�Ľڵ���� closeList
	Point2 getMinNode()
	{
		auto it = openList.begin();
		Point2 ret((*it)->x, (*it)->y);
		closeList.push_back(*it);
		openList.erase(it);
		return ret;
	}

	// ��ȡѰ·�յ㣬���ڻ��ݵõ����·��
	Node* getDestNode() { return p_destNode; }

	// ���� multiset �Ƚ� �ĺ�������
	struct Compare
	{
		bool operator ()(const Node* _n1, const Node* _n2) const { return _n1->fVal < _n2->fVal; }
	};

private:
	Point2 destPos;								// Ŀ��λ��
	std::vector<Node*> closeList;				// closeList ����
	std::multiset<Node*, Compare> openList;		// openList �Զ�����
	Node* p_destNode = nullptr;					// ���ڷ����յ��λ��ָ��
};



/* ********** �Թ��㷨��ʾ ********** */
class MazeDemonstration
{
public:
	// �����Թ���С������յ㣬�Թ���С�����Ϊ����
	MazeDemonstration(int _row, int _col)
	{
		initgraph(SW, SH);
		setbkmode(TRANSPARENT);
		setbkcolor(LIGHTGRAY);
		cleardevice();
		// ������ż���������Ϊ����
		if ((_row & 1) == 0) ++_row;
		if ((_col & 1) == 0) ++_col;
		if (_row <= 5 || _col <= 5) _row = _col = 31;
		if (_row != _col) _row = _col;
		row = _row;
		col = _col;
		start = Point2(1, 0);
		end = Point2(row - 2, col - 1);
	}

	// ����ӿڣ�DFS��ǽ �����Թ�
	void DFS_generate(bool _iteration = false)
	{
		Clear();
		for (int i = 0; i < row; ++i) map.push_back(std::vector<int>());
		for (int i = 0; i < row; ++i)
			for (int j = 0; j < col; ++j)
				map[i].push_back(WALL);

		maze.Init(SW, SH, row, col);
		maze.Draw(end.x, end.y, RGB(0, 255, 0));
		maze.Draw(start.x, start.y, RGB(255, 0, 0));
		map[start.x][start.y] = map[end.x][end.y] = PATH;
		if (_iteration) DFS_iterative_generator();
		else DFS_generator((rand() % (row - 2) + 1) | 1, (rand() % (col - 2) + 1) | 1);
	}

	// ����ӿ� �ָǽ �����Թ�
	void Division_generate(bool _iteration = false)
	{
		Clear();
		for (int i = 0; i < row; ++i) map.push_back(std::vector<int>());
		for (int i = 0; i < row; ++i)
			for (int j = 0; j < col; ++j)
				(i == 0 || j == 0 || i == row - 1 || j == col - 1) ? map[i].push_back(WALL) : map[i].push_back(PATH);

		maze.Init(SW, SH, row, col, false);
		maze.Draw(end.x, end.y, RGB(0, 255, 0));
		maze.Draw(start.x, start.y, RGB(255, 0, 0));
		map[start.x][start.y] = map[end.x][end.y] = PATH;
		if (_iteration) Division_generator();
		else Division_generator(1, row - 2, 1, col - 2);
	}

	// ����ӿ� ��� Prim ��ǽ �����Թ�
	void Prim_generate()
	{
		Clear();
		for (int i = 0; i < row; ++i) map.push_back(std::vector<int>());
		for (int i = 0; i < row; ++i)
			for (int j = 0; j < col; ++j)
				map[i].push_back(WALL);

		maze.Init(SW, SH, row, col);
		maze.Draw(end.x, end.y, RGB(0, 255, 0));
		maze.Draw(start.x, start.y, RGB(255, 0, 0));
		map[start.x][start.y] = map[end.x][end.y] = PATH;
		Prim_generator();
	}

	// ����ӿ� DFS Ѱ·
	// ��������ȷ���Ƿ�����������
	void DFS_find(bool _rand = false)
	{
		// �������ϴ����������Ŀ��λ�ò���������·���Ӧ�޸Ĵ���ʹ���㷨����Ч��
		std::vector<std::vector<int>> dir{ {1,0},{0,1},{-1,0},{0,-1} };
		// ����ջ����
		std::stack<Point2> sp;
		Point2 temp = start;
		sp.push(temp);
		// �������㷨���ƣ����� DFS ����
		while (!sp.empty())
		{
			if (_rand) std::random_shuffle(dir.begin(), dir.end());
			int i = 0;
			// ��������������ǰ���������
			for (; i < 4; ++i)
			{
				if (temp.x + dir[i][0] >= 0 && temp.x + dir[i][0] <= row - 1 && temp.y + dir[i][1] >= 0 && temp.y + dir[i][1] <= col - 1
					&& map[temp.x + dir[i][0]][temp.y + dir[i][1]] == PATH)
				{
					maze.Draw(temp.x, temp.y, RGB(255, 255, 0));
					// ���߹���·���б��
					map[temp.x][temp.y] = FLAG;
					temp.x += dir[i][0];
					temp.y += dir[i][1];
					sp.push(temp);
					maze.Draw(temp.x, temp.y, RGB(255, 0, 0));
					if (temp == end) return;
					Sleep(delayMs);
					break;
				}
			}
			// ��·����ʱ����
			if (i == 4)
			{
				maze.DrawPath(temp.x, temp.y);
				map[temp.x][temp.y] = FLAG;
				sp.pop();
				if (!sp.empty())
				{
					temp = sp.top();
					maze.Draw(temp.x, temp.y, RGB(255, 0, 0));
					Sleep(delayMs);
				}
			}
		}
		// ������ǵ�ͨ·��ԭ
		for (auto& v1 : map)
			for (auto& v2 : v1)
				if (v2 == FLAG) v2 = PATH;
	}

	// ����ӿ� A* Ѱ·
	void A_find()
	{
		// ��Ŀ��λ�ÿ�ʼѰ����㣬֮����ݼ��ɵõ���㵽�յ��·��
		Point2 temp = end;
		// ������Ч����
		A_Container cont(start);
		// ��Ŀ��λ�ü��� openList
		cont.pushOpenList(temp);
		// �����������У����� A* Ѱ·�������ø�Ч����Ѱ�����·��
		while (true)
		{
			maze.Draw(temp.x, temp.y, RGB(0, 255, 255));
			// �� openList �� F ֵ��С�Ľڵ�ŵ� closeList ��
			temp = cont.getMinNode();
			// ��ǽڵ���뵽 openList �еĽڵ�
			map[temp.x][temp.y] = FLAG;
			maze.Draw(temp.x, temp.y, RGB(0, 0, 255));
			// ���� if ����Χͨ·���� openList
			if (temp.x - 1 >= 0 && map[temp.x - 1][temp.y] == PATH)
			{
				map[temp.x - 1][temp.y] = FLAG;
				cont.pushOpenList(Point2(temp.x - 1, temp.y));
				maze.Draw(temp.x - 1, temp.y, RGB(0, 255, 255));
				if (start == Point2(temp.x - 1, temp.y)) break;
			}
			if (temp.y - 1 >= 0 && map[temp.x][temp.y - 1] == PATH)
			{
				map[temp.x][temp.y - 1] = FLAG;
				cont.pushOpenList(Point2(temp.x, temp.y - 1));
				maze.Draw(temp.x, temp.y - 1, RGB(0, 255, 255));
				if (start == Point2(temp.x, temp.y - 1)) break;
			}
			if (temp.x + 1 <= row - 1 && map[temp.x + 1][temp.y] == PATH)
			{
				map[temp.x + 1][temp.y] = FLAG;
				cont.pushOpenList(Point2(temp.x + 1, temp.y));
				maze.Draw(temp.x + 1, temp.y, RGB(0, 255, 255));
				if (start == Point2(temp.x + 1, temp.y)) break;
			}
			if (temp.y + 1 <= col - 1 && map[temp.x][temp.y + 1] == PATH)
			{
				map[temp.x][temp.y + 1] = FLAG;
				cont.pushOpenList(Point2(temp.x, temp.y + 1));
				maze.Draw(temp.x, temp.y + 1, RGB(0, 255, 255));
				if (start == Point2(temp.x, temp.y + 1)) break;
			}
			Sleep(delayMs);
		}

		// �ҵ����󣬻�ȡ��Ч�����е���㣬���ݵõ����·��
		auto st = cont.getDestNode();
		while (st->parent != nullptr)
		{
			maze.Draw(st->x, st->y, RGB(255, 255, 0));
			st = st->parent;
			maze.Draw(st->x, st->y, RGB(255, 0, 0));
			Sleep(delayMs);
		}
		// ������ǵ�ͨ·��ԭ
		for (auto& v1 : map)
			for (auto& v2 : v1)
				if (v2 == FLAG) v2 = PATH;
	}

	// ����̨�������
	friend std::ostream& operator << (std::ostream& _os, const MazeDemonstration& _gen)
	{
		for (auto& v1 : _gen.map)
		{
			for (auto& v2 : v1) _os << v2 << " ";
			_os << std::endl;
		}
		return _os;
	}

private:
	// �ݹ�汾 ����������� ��ǽ���ɣ�Ҫ���ʼʱ���з���Ϊǽ��
	// Ҫ�����Ϊ����
	void DFS_generator(int _x, int _y)
	{
		// ���巽������
		std::vector<std::vector<int>> dir{ {1,0},{-1,0},{0,1},{0,-1} };
		// ������ҷ���
		std::random_shuffle(dir.begin(), dir.end());
		// �����ݹ������Թ���������
		maze.DrawPath(_x, _y);
		map[_x][_y] = PATH;
		Sleep(delayMs);
		for (int i = 0; i < 4; ++i)
		{
			if (_x + 2 * dir[i][0] >= 1 && _x + 2 * dir[i][0] <= row - 2 && _y + 2 * dir[i][1] >= 1 && _y + 2 * dir[i][1] <= col - 2
				&& map[_x + 2 * dir[i][0]][_y + 2 * dir[i][1]] == WALL)
			{
				maze.DrawPath(_x + dir[i][0], _y + dir[i][1]);
				map[_x + dir[i][0]][_y + dir[i][1]] = PATH;
				Sleep(delayMs);
				DFS_generator(_x + 2 * dir[i][0], _y + 2 * dir[i][1]);
			}
		}
	}

	// �ǵݹ�汾 ����������� ��ǽ����
	void DFS_iterative_generator()
	{
		// ����ջ����
		std::stack<Point2> sp;
		// ���巽������
		std::vector<std::vector<int>> dir{ {1,0},{-1,0},{0,1},{0,-1} };
		// Ҫ�����Ϊ����
		Point2 temp((rand() % (row - 2) + 1) | 1, (rand() % (col - 2) + 1) | 1);
		sp.push(temp);
		// �������������Թ���������
		while (!sp.empty())
		{
			if (map[temp.x][temp.y] != PATH)
			{
				maze.DrawPath(temp.x, temp.y);
				map[temp.x][temp.y] = PATH;
				Sleep(delayMs);
			}
			// ������ҷ���
			std::random_shuffle(dir.begin(), dir.end());
			int i = 0;
			for (; i < 4; ++i)
			{
				if (temp.x + 2 * dir[i][0] >= 1 && temp.x + 2 * dir[i][0] <= row - 2 && temp.y + 2 * dir[i][1] >= 1 && temp.y + 2 * dir[i][1] <= col - 2
					&& map[temp.x + 2 * dir[i][0]][temp.y + 2 * dir[i][1]] == WALL)
				{
					maze.DrawPath(temp.x + dir[i][0], temp.y + dir[i][1]);
					map[temp.x + dir[i][0]][temp.y + dir[i][1]] = PATH;
					temp.x += 2 * dir[i][0];
					temp.y += 2 * dir[i][1];
					sp.push(temp);
					Sleep(delayMs);
					break;
				}
			}
			if (i == 4) sp.pop();
			if (!sp.empty()) temp = sp.top();
		}
	}

	// �ݹ�� �ָ� ��ǽ����
	// Ҫ�����Ϊ����
	void Division_generator(int _l, int _r, int _t, int _b)
	{
		// ������� 1 ʱ�ɷָ�
		if (_r - _l > 1 && _b - _t > 1)
		{
			int i = 0;
			// Ҫ��ָ�� px,py Ϊż��
			int px = ((rand() % (_r - _l) + _l + 1) | 1) - 1;
			int py = ((rand() % (_b - _t) + _t + 1) | 1) - 1;
			while (px + i <= _r || px - i >= _l || py + i <= _b || py - i >= _t)
			{
				if (px + i <= _r) { maze.DrawWall(px + i, py); map[px + i][py] = WALL; }
				if (px - i >= _l) { maze.DrawWall(px - i, py); map[px - i][py] = WALL; }
				if (py + i <= _b) { maze.DrawWall(px, py + i); map[px][py + i] = WALL; }
				if (py - i >= _t) { maze.DrawWall(px, py - i); map[px][py - i] = WALL; }
				Sleep(delayMs);
				++i;
			}
			// ���巽�����������������ǽ�Ͽ���
			// Ҫ�󿪶�λ��������
			std::vector<int> dir{ 0,1,2,3 };
			std::random_shuffle(dir.begin(), dir.end());
			for (int i = 0; i < 3; ++i)
			{
				if (dir[i] == 0)
				{
					int xx = (rand() % (px - _l) + _l) | 1;
					maze.DrawPath(xx, py);
					map[xx][py] = PATH;
				}
				else if (dir[i] == 1)
				{
					int xx = (rand() % (_r - px) + px) | 1;
					maze.DrawPath(xx, py);
					map[xx][py] = PATH;
				}
				else if (dir[i] == 2)
				{
					int yy = (rand() % (py - _t) + _t) | 1;
					maze.DrawPath(px, yy);
					map[px][yy] = PATH;
				}
				else if (dir[i] == 3)
				{
					int yy = (rand() % (_b - py) + py) | 1;
					maze.DrawPath(px, yy);
					map[px][yy] = PATH;
				}
			}
			Sleep(delayMs);
			// �ݹ�ָ�
			Division_generator(_l, px - 1, _t, py - 1);
			Division_generator(px + 1, _r, _t, py - 1);
			Division_generator(_l, px - 1, py + 1, _b);
			Division_generator(px + 1, _r, py + 1, _b);
		}
	}

	// �ǵݹ�� �ָ� ��ǽ����
	void Division_generator()
	{
		// ����ջ����
		std::stack<Point4> sp;
		// ���巽������
		std::vector<int> dir{ 0,1,2,3 };
		// Ҫ�����Ϊ����
		Point4 temp(1, row - 2, 1, col - 2);
		sp.push(temp);
		// �������������Թ��������ƣ��㷨ͬ�ݹ�棩
		while (!sp.empty())
		{
			sp.pop();
			if (temp.x2 - temp.x1 > 1 && temp.y2 - temp.y1 > 1)
			{
				int i = 0;
				int px = ((rand() % (temp.x2 - temp.x1) + temp.x1 + 1) | 1) - 1;
				int py = ((rand() % (temp.y2 - temp.y1) + temp.y1 + 1) | 1) - 1;
				while (px + i <= temp.x2 || px - i >= temp.x1 || py + i <= temp.y2 || py - i >= temp.y1)
				{
					if (px + i <= temp.x2) { maze.DrawWall(px + i, py); map[px + i][py] = WALL; }
					if (px - i >= temp.x1) { maze.DrawWall(px - i, py); map[px - i][py] = WALL; }
					if (py + i <= temp.y2) { maze.DrawWall(px, py + i); map[px][py + i] = WALL; }
					if (py - i >= temp.y1) { maze.DrawWall(px, py - i); map[px][py - i] = WALL; }
					Sleep(delayMs);
					++i;
				}
				// ���������ǽ�Ͽ�����Ҫ�󿪶�λ��������
				std::random_shuffle(dir.begin(), dir.end());
				for (int i = 0; i < 3; ++i)
				{
					if (dir[i] == 0)
					{
						int xx = (rand() % (px - temp.x1) + temp.x1) | 1;
						maze.DrawPath(xx, py);
						map[xx][py] = PATH;
					}
					else if (dir[i] == 1)
					{
						int xx = (rand() % (temp.x2 - px) + px) | 1;
						maze.DrawPath(xx, py);
						map[xx][py] = PATH;
					}
					else if (dir[i] == 2)
					{
						int yy = (rand() % (py - temp.y1) + temp.y1) | 1;
						maze.DrawPath(px, yy);
						map[px][yy] = PATH;
					}
					else if (dir[i] == 3)
					{
						int yy = (rand() % (temp.y2 - py) + py) | 1;
						maze.DrawPath(px, yy);
						map[px][yy] = PATH;
					}
				}
				Sleep(delayMs);
				// ����������������ջ
				sp.push(Point4(px + 1, temp.x2, py + 1, temp.y2));
				sp.push(Point4(temp.x1, px - 1, py + 1, temp.y2));
				sp.push(Point4(px + 1, temp.x2, temp.y1, py - 1));
				temp.x2 = px - 1;
				temp.y2 = py - 1;
				sp.push(temp);
			}
			else if (!sp.empty()) { temp = sp.top(); }
		}
	}

	// ��� Prim ��ǽ����
	void Prim_generator()
	{
		// ����ǽ����ͨ·���Թ���������Ϊͨ·
		for (int i = 1; i <= row - 2; i += 2)
		{
			for (int j = 1; j <= row - 2; j += 2)
			{
				maze.DrawPath(i, j);
				map[i][j] = PATH;
			}
		}
		Sleep(delayMs);
		// ά��һ��ǽ����
		std::vector<Point2> vp;
		// �������һ��ͨ·
		Point2 temp((rand() % (row - 2) + 1) | 1, (rand() % (col - 2) + 1) | 1);
		// ����Χǽ��ջ
		if (temp.x - 1 >= 2) vp.push_back(Point2(temp.x - 1, temp.y));
		if (temp.x + 1 <= row - 3) vp.push_back(Point2(temp.x + 1, temp.y));
		if (temp.y - 1 >= 2) vp.push_back(Point2(temp.x, temp.y - 1));
		if (temp.y + 1 <= col - 3) vp.push_back(Point2(temp.x, temp.y + 1));
		// ��Ǹ�ͨ·
		map[temp.x][temp.y] = FLAG;
		int pos = 0;
		// �������������Թ�
		while (!vp.empty())
		{
			// ��ǽ���������ѡȡһ��ǽ
			pos = rand() % vp.size();
			temp = vp[pos];
			// ��¼��ǽ�Ƿ��ͨ
			bool flag = false;
			// ���� if else �ж�ǽ������ͨ·�����һ������£����ж��Ƿ��ͨ
			if (map[temp.x + 1][temp.y] == WALL)
			{
				if (map[temp.x][temp.y - 1] != map[temp.x][temp.y + 1])
				{
					maze.DrawPath(temp.x, temp.y);
					map[temp.x][temp.y] = PATH;
					// ���¼����ͨ·���б��
					if (map[temp.x][temp.y - 1] == FLAG) { map[temp.x][temp.y + 1] = FLAG; ++temp.y; }
					else { map[temp.x][temp.y - 1] = FLAG; --temp.y; }
					flag = true;
				}
			}
			else
			{
				if (map[temp.x - 1][temp.y] != map[temp.x + 1][temp.y])
				{
					maze.DrawPath(temp.x, temp.y);
					map[temp.x][temp.y] = PATH;
					// ���¼����ͨ·���б��
					if (map[temp.x - 1][temp.y] == FLAG) { map[temp.x + 1][temp.y] = FLAG; ++temp.x; }
					else { map[temp.x - 1][temp.y] = FLAG; --temp.x; }
					flag = true;
				}
			}
			// �����ͨ��ǽ�����������ͨ·��Χ��ǽ������
			if (flag)
			{
				if (temp.x - 1 >= 2 && map[temp.x - 1][temp.y] == WALL) vp.push_back(Point2(temp.x - 1, temp.y));
				if (temp.x + 1 <= row - 3 && map[temp.x + 1][temp.y] == WALL) vp.push_back(Point2(temp.x + 1, temp.y));
				if (temp.y - 1 >= 2 && map[temp.x][temp.y - 1] == WALL) vp.push_back(Point2(temp.x, temp.y - 1));
				if (temp.y + 1 <= col - 3 && map[temp.x][temp.y + 1] == WALL) vp.push_back(Point2(temp.x, temp.y + 1));
				Sleep(delayMs);
			}
			vp[pos] = *(vp.end() - 1);
			vp.pop_back();
		}
		// ������ǵ�ͨ·��ԭ
		for (auto& v1 : map)
			for (auto& v2 : v1)
				if (v2 == FLAG) v2 = PATH;
	}

	// �Թ��Ѿ�����ʱ���ٴ�����ǰ��Ҫ������е� map ����
	void Clear()
	{
		cleardevice();
		if (!map.empty())
		{
			for (auto& v1 : map) v1.clear();
			map.clear();
		}
	}

private:
	int delayMs = 20;						// ��ʱ���뼶
	int row, col;							// �Թ���������
	Point2 end;								// �Թ��յ�
	Point2 start;							// �Թ����
	MazeGraph maze;							// �Թ���ͼ
	std::vector<std::vector<int>> map;		// �Թ���ά����

public:
	int SW = 640;							// ���ڿ��
	int SH = 480;							// ���ڸ߶�
};
