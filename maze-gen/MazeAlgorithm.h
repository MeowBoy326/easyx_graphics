#pragma once



/* ********** 头文件 ********** */
#include <set>
#include <stack>
#include <vector>
#include <algorithm>
#include <iostream>
#include <easyx.h>



/* ********** 全局数据 ********** */
// 二维点
struct Point2
{
	int x = 0;
	int y = 0;
	Point2() = default;
	Point2(int _x, int _y) :x(_x), y(_y) {}
	bool operator == (const Point2& _p2) { return x == _p2.x && y == _p2.y; }
};
// 四维点，用于分割矩形区间
struct Point4
{
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;
	Point4() = default;
	Point4(int _x1, int _x2, int _y1, int _y2) :x1(_x1), x2(_x2), y1(_y1), y2(_y2) {}
};
// 迷宫方格状态
enum CellState：int { PATH = 0, WALL, FLAG };



/* ********** 迷宫绘制 ********** */
class MazeGraph
{
public:
	MazeGraph() = default;
	~MazeGraph() { closegraph(); }

	// 传递迷宫长宽方格数，边缘一定是墙，边缘以内是墙是路参数决定
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

	// 画墙
	void DrawWall(int _row, int _col) { Draw(_row, _col, LIGHTGRAY, true); }
	// 画路
	void DrawPath(int _row, int _col) { Draw(_row, _col, BLACK, false); }
	// 绘制指定样式的方块
	void Draw(int _row, int _col, COLORREF _co, bool _frame = true)
	{
		setfillcolor(_co);
		auto DrawRectangle = solidrectangle;
		if (_frame) DrawRectangle = fillrectangle;
		DrawRectangle(edog_x + _col * width, edog_y + _row * width, edog_x + _col * width + width - 1, edog_y + _row * width + width - 1);
	}

private:
	int width = 0;		// 迷宫方格高宽
	int edog_x = 0;		// 迷宫边缘位置
	int edog_y = 0;		// 迷宫边缘位置
};



/* ********** A*寻路容器 ********** */
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

	// 当前节点的邻居加入 openList
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

	// 从 openList 中取出 fVal 值最小的节点加入 closeList
	Point2 getMinNode()
	{
		auto it = openList.begin();
		Point2 ret((*it)->x, (*it)->y);
		closeList.push_back(*it);
		openList.erase(it);
		return ret;
	}

	// 获取寻路终点，用于回溯得到最短路径
	Node* getDestNode() { return p_destNode; }

	// 用于 multiset 比较 的函数对象
	struct Compare
	{
		bool operator ()(const Node* _n1, const Node* _n2) const { return _n1->fVal < _n2->fVal; }
	};

private:
	Point2 destPos;								// 目标位置
	std::vector<Node*> closeList;				// closeList 容器
	std::multiset<Node*, Compare> openList;		// openList 自动排序
	Node* p_destNode = nullptr;					// 用于返回终点的位置指针
};



/* ********** 迷宫算法演示 ********** */
class MazeDemonstration
{
public:
	// 构造迷宫大小及起点终点，迷宫大小必须均为奇数
	MazeDemonstration(int _row, int _col)
	{
		initgraph(SW, SH);
		setbkmode(TRANSPARENT);
		setbkcolor(LIGHTGRAY);
		cleardevice();
		// 若传递偶数，则调整为奇数
		if ((_row & 1) == 0) ++_row;
		if ((_col & 1) == 0) ++_col;
		if (_row <= 5 || _col <= 5) _row = _col = 31;
		if (_row != _col) _row = _col;
		row = _row;
		col = _col;
		start = Point2(1, 0);
		end = Point2(row - 2, col - 1);
	}

	// 对外接口，DFS挖墙 生成迷宫
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

	// 对外接口 分割补墙 生成迷宫
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

	// 对外接口 随机 Prim 挖墙 生成迷宫
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

	// 对外接口 DFS 寻路
	// 参数用于确定是否随机方向进行
	void DFS_find(bool _rand = false)
	{
		// 右下左上次序遍历（若目标位置不在起点右下方，应修改次序使得算法更高效）
		std::vector<std::vector<int>> dir{ {1,0},{0,1},{-1,0},{0,-1} };
		// 定义栈容器
		std::stack<Point2> sp;
		Point2 temp = start;
		sp.push(temp);
		// 与生成算法相似，迭代 DFS 遍历
		while (!sp.empty())
		{
			if (_rand) std::random_shuffle(dir.begin(), dir.end());
			int i = 0;
			// 若可向其他方向前进，则继续
			for (; i < 4; ++i)
			{
				if (temp.x + dir[i][0] >= 0 && temp.x + dir[i][0] <= row - 1 && temp.y + dir[i][1] >= 0 && temp.y + dir[i][1] <= col - 1
					&& map[temp.x + dir[i][0]][temp.y + dir[i][1]] == PATH)
				{
					maze.Draw(temp.x, temp.y, RGB(255, 255, 0));
					// 对走过的路进行标记
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
			// 无路可走时回溯
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
		// 将被标记的通路还原
		for (auto& v1 : map)
			for (auto& v2 : v1)
				if (v2 == FLAG) v2 = PATH;
	}

	// 对外接口 A* 寻路
	void A_find()
	{
		// 从目标位置开始寻找起点，之后回溯即可得到起点到终点的路径
		Point2 temp = end;
		// 创建高效容器
		A_Container cont(start);
		// 将目标位置加入 openList
		cont.pushOpenList(temp);
		// 后续迭代进行，根据 A* 寻路规则，利用高效容器寻找最短路径
		while (true)
		{
			maze.Draw(temp.x, temp.y, RGB(0, 255, 255));
			// 将 openList 中 F 值最小的节点放到 closeList 中
			temp = cont.getMinNode();
			// 标记节点加入到 openList 中的节点
			map[temp.x][temp.y] = FLAG;
			maze.Draw(temp.x, temp.y, RGB(0, 0, 255));
			// 后续 if 将周围通路加入 openList
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

		// 找到起点后，获取高效容器中的起点，回溯得到最短路径
		auto st = cont.getDestNode();
		while (st->parent != nullptr)
		{
			maze.Draw(st->x, st->y, RGB(255, 255, 0));
			st = st->parent;
			maze.Draw(st->x, st->y, RGB(255, 0, 0));
			Sleep(delayMs);
		}
		// 将被标记的通路还原
		for (auto& v1 : map)
			for (auto& v2 : v1)
				if (v2 == FLAG) v2 = PATH;
	}

	// 控制台输出测试
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
	// 递归版本 深度优先搜索 挖墙生成（要求初始时所有方格为墙）
	// 要求参数为奇数
	void DFS_generator(int _x, int _y)
	{
		// 定义方向容器
		std::vector<std::vector<int>> dir{ {1,0},{-1,0},{0,1},{0,-1} };
		// 随机打乱方向
		std::random_shuffle(dir.begin(), dir.end());
		// 后续递归生成迷宫，并绘制
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

	// 非递归版本 深度优先搜索 挖墙生成
	void DFS_iterative_generator()
	{
		// 定义栈容器
		std::stack<Point2> sp;
		// 定义方向容器
		std::vector<std::vector<int>> dir{ {1,0},{-1,0},{0,1},{0,-1} };
		// 要求参数为奇数
		Point2 temp((rand() % (row - 2) + 1) | 1, (rand() % (col - 2) + 1) | 1);
		sp.push(temp);
		// 后续迭代生成迷宫，并绘制
		while (!sp.empty())
		{
			if (map[temp.x][temp.y] != PATH)
			{
				maze.DrawPath(temp.x, temp.y);
				map[temp.x][temp.y] = PATH;
				Sleep(delayMs);
			}
			// 随机打乱方向
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

	// 递归版 分割 补墙生成
	// 要求参数为奇数
	void Division_generator(int _l, int _r, int _t, int _b)
	{
		// 间隔大于 1 时可分割
		if (_r - _l > 1 && _b - _t > 1)
		{
			int i = 0;
			// 要求分割点 px,py 为偶数
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
			// 定义方向容器，随机在三面墙上开洞
			// 要求开洞位置是奇数
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
			// 递归分割
			Division_generator(_l, px - 1, _t, py - 1);
			Division_generator(px + 1, _r, _t, py - 1);
			Division_generator(_l, px - 1, py + 1, _b);
			Division_generator(px + 1, _r, py + 1, _b);
		}
	}

	// 非递归版 分割 补墙生成
	void Division_generator()
	{
		// 定义栈容器
		std::stack<Point4> sp;
		// 定义方向容器
		std::vector<int> dir{ 0,1,2,3 };
		// 要求参数为奇数
		Point4 temp(1, row - 2, 1, col - 2);
		sp.push(temp);
		// 后续迭代生成迷宫，并绘制（算法同递归版）
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
				// 随机在三面墙上开洞，要求开洞位置是奇数
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
				// 将三个方块区间入栈
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

	// 随机 Prim 挖墙生成
	void Prim_generator()
	{
		// 构建墙隔开通路的迷宫，奇数点为通路
		for (int i = 1; i <= row - 2; i += 2)
		{
			for (int j = 1; j <= row - 2; j += 2)
			{
				maze.DrawPath(i, j);
				map[i][j] = PATH;
			}
		}
		Sleep(delayMs);
		// 维护一个墙容器
		std::vector<Point2> vp;
		// 先随机找一个通路
		Point2 temp((rand() % (row - 2) + 1) | 1, (rand() % (col - 2) + 1) | 1);
		// 将周围墙入栈
		if (temp.x - 1 >= 2) vp.push_back(Point2(temp.x - 1, temp.y));
		if (temp.x + 1 <= row - 3) vp.push_back(Point2(temp.x + 1, temp.y));
		if (temp.y - 1 >= 2) vp.push_back(Point2(temp.x, temp.y - 1));
		if (temp.y + 1 <= col - 3) vp.push_back(Point2(temp.x, temp.y + 1));
		// 标记该通路
		map[temp.x][temp.y] = FLAG;
		int pos = 0;
		// 后续迭代生成迷宫
		while (!vp.empty())
		{
			// 在墙容器中随机选取一堵墙
			pos = rand() % vp.size();
			temp = vp[pos];
			// 记录该墙是否打通
			bool flag = false;
			// 后续 if else 判断墙所隔离通路在左右还是上下，并判断是否打通
			if (map[temp.x + 1][temp.y] == WALL)
			{
				if (map[temp.x][temp.y - 1] != map[temp.x][temp.y + 1])
				{
					maze.DrawPath(temp.x, temp.y);
					map[temp.x][temp.y] = PATH;
					// 对新加入的通路进行标记
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
					// 对新加入的通路进行标记
					if (map[temp.x - 1][temp.y] == FLAG) { map[temp.x + 1][temp.y] = FLAG; ++temp.x; }
					else { map[temp.x - 1][temp.y] = FLAG; --temp.x; }
					flag = true;
				}
			}
			// 如果打通了墙，将进加入的通路周围的墙入容器
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
		// 将被标记的通路还原
		for (auto& v1 : map)
			for (auto& v2 : v1)
				if (v2 == FLAG) v2 = PATH;
	}

	// 迷宫已经生成时想再次生成前需要清除已有的 map 容器
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
	int delayMs = 20;						// 延时毫秒级
	int row, col;							// 迷宫长宽方格数
	Point2 end;								// 迷宫终点
	Point2 start;							// 迷宫起点
	MazeGraph maze;							// 迷宫绘图
	std::vector<std::vector<int>> map;		// 迷宫二维容器

public:
	int SW = 640;							// 窗口宽度
	int SH = 480;							// 窗口高度
};
