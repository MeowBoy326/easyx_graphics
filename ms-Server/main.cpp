/*
	程序名称：
			扫雷联网对战版 - 服务器

	简介：
			联网匹配对战的扫雷程序，左键按下翻开方块，翻开雷判输，或翻开最后一个方块判赢

	环境：
			VS2019 + EasyX_20210115(beta)

	时间：
			2021.1.18

	作者：
			Teternity(QQ:1926594835)

	版权：
			作者原创，无抄袭，不涉及版权问题，仅用作学习
*/


/* ----------头文件---------- */
#include "WinsockTcp.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <unordered_map>
#include <easyx.h>

using std::cout;
using std::endl;


/* ----------线程安全队列---------- */
class ThreadSafeQueue
{
public:
	// 默认构造
	ThreadSafeQueue() = default;

	// 入队列
	void push(const std::pair<SOCKET, ULONG>& par)
	{
		std::lock_guard<std::mutex> lg(mut);
		que.push(par);
	}
	void push(const std::pair<SOCKET, ULONG>&& par)
	{
		std::lock_guard<std::mutex> lg(mut);
		que.push(par);
	}

	// 出队列
	void pop(std::pair<SOCKET, ULONG>* par)
	{
		std::lock_guard<std::mutex> lg(mut);
		if (par != nullptr) *par = que.front();
		que.pop();
	}

	// 获取队头元素
	std::pair<SOCKET, ULONG> front()
	{
		std::lock_guard<std::mutex> lg(mut);
		if (que.empty()) return { INVALID_SOCKET,0 };
		return que.front();
	}

	// 检查队列元素个数
	int size()
	{
		std::lock_guard<std::mutex> lg(mut);
		return que.size();
	}

private:
	std::mutex mut;
	std::queue<std::pair<SOCKET, ULONG>> que;
};

// 创建全局线程安全队列对象
ThreadSafeQueue sockQueue;


/* ----------全局数据---------- */
// 参数设定
const int nRow = 30;				// 横向格子数
const int nCol = 20;				// 纵向格子数
const int munMine = 108;			// 雷数目

// 定义格子值
// '0' 表示空白，'1' - '8' 表示方块周围雷数目，值 1 表示雷
const char MINE = 1;

// 定义信息结构体
struct Info
{
	int code;			// 状态码，1 代表正常进行，2 代表正常结束，3 代表断开
	unsigned int uMsg;	// 鼠标消息 uMsg
	int x;				// 鼠标位置 x
	int y;				// 鼠标位置 y;
};

// IP Map
std::unordered_map<ULONG, int> ipMap;
std::mutex ipMapMutex;


/* ----------线程函数：维护连接请求---------- */
void Conn(WinsockTcp& Server, std::pair<SOCKET, ULONG> p1, std::pair<SOCKET, ULONG> p2)
{
	auto closeSockets = [&]()
	{
		ipMapMutex.lock();
		--ipMap[p1.second];
		--ipMap[p2.second];
		ipMapMutex.unlock();

		Server.CloseSocket(p1.first);
		Server.CloseSocket(p2.first);
	};

	int fcode = 0;

	while (fcode != 3)
	{
		// 生成地图
		char* Map = new char[nRow * nCol];
		memset(Map, 0, nRow * nCol);
		// 生成雷区
		for (int i = 0; i < munMine; ++i) Map[i] = MINE;
		// 打乱雷区
		std::random_shuffle(Map, Map + nRow * nCol);
		// 遍历确认每个格子值
		for (int j = 0; j < nCol; ++j)
		{
			for (int i = 0; i < nRow; ++i)
			{
				if (Map[j * nRow + i] != MINE)
				{
					char nMine = 0;
					for (int y = -1; y <= 1; ++y)
					{
						for (int x = -1; x <= 1; ++x)
						{
							if (x == 0 && y == 0) continue;
							if ((i + x) >= 0 && (i + x) < nRow && (j + y) >= 0 && (j + y) < nCol && Map[(j + y) * nRow + (i + x)] == MINE) ++nMine;
						}
					}
					Map[j * nRow + i] = '0' + nMine;
				}
			}
		}

		// 向两方发送地图数据
		int ret1 = Server.Send(p1.first, Map, nRow * nCol);
		int ret2 = Server.Send(p2.first, Map, nRow * nCol);
		if (ret1 == SOCKET_ERROR || ret2 == SOCKET_ERROR)
		{
			closeSockets();
			return;
		}

		delete[] Map;

		// 发送先手信息，'1' 先手
		char ch1 = '1', ch2 = '0';
		ret1 = Server.Send(p1.first, &ch1, 1);
		ret2 = Server.Send(p2.first, &ch2, 1);
		if (ret1 == SOCKET_ERROR || ret2 == SOCKET_ERROR)
		{
			closeSockets();
			return;
		}

		// 设置接收超时
		Server.SetRecvTimeOut(p1.first, 1000 * 18);
		Server.SetRecvTimeOut(p2.first, 1000 * 18);

		Info info{};

		// 循环转发消息
		while (true)
		{
			// 接收 p1 发来的点击信息
			ret1 = Server.Recv(p1.first, (char*)&info, sizeof(info), true);
			if (ret1 <= 0)
			{
				info.code = htonl(3);
				Server.Send(p2.first, (char*)&info, sizeof(info));
				break;
			}
			else if (ntohl(info.code) == 1 && Server.Send(p2.first, (char*)&info, sizeof(info)) == SOCKET_ERROR)
			{
				info.code = htonl(3);
				break;
			}
			if (ntohl(info.code) == 2 || ntohl(info.code) == 3) break;

			// 接收 p2 发来的点击信息
			ret2 = Server.Recv(p2.first, (char*)&info, sizeof(info), true);
			if (ret2 <= 0)
			{
				info.code = htonl(3);
				Server.Send(p1.first, (char*)&info, sizeof(info));
				break;
			}
			else if (ntohl(info.code) == 1 && Server.Send(p1.first, (char*)&info, sizeof(info)) == SOCKET_ERROR)
			{
				info.code = htonl(3);
				break;
			}
			if (ntohl(info.code) == 2 || ntohl(info.code) == 3) break;
		}

		fcode = ntohl(info.code);
		std::pair<SOCKET, ULONG> temp = p1;
		p1 = p2;
		p2 = temp;
	}

	Sleep(100);
	closeSockets();
}


/* ----------线程函数：维护连接请求---------- */
void Manage(WinsockTcp& Server)
{
	clock_t ct = 0;
	SOCKET s = INVALID_SOCKET;

	while (true)
	{
		// 队列中长时间 (30s) 只有一个元素时，超时后断开该连接
		if (sockQueue.size() == 1)
		{
			if (s == INVALID_SOCKET)
			{
				ct = clock();
				s = sockQueue.front().first;
			}
			else
			{
				if (s != sockQueue.front().first) s = INVALID_SOCKET;
				else if (clock() - ct > 1000 * 30)
				{
					ULONG ipaddr = sockQueue.front().second;
					sockQueue.pop(nullptr);
					ipMapMutex.lock();
					--ipMap[ipaddr];
					ipMapMutex.unlock();
					Server.CloseSocket(s);
					s = INVALID_SOCKET;
				}
			}
		}

		// 队列中大于等于两个成员时
		if (sockQueue.size() > 1)
		{
			std::pair<SOCKET, ULONG> p1, p2;
			sockQueue.pop(&p1);
			sockQueue.pop(&p2);

			// 创建线程管理一对连接
			std::thread th(Conn, std::ref(Server), p1, p2);
			th.detach();
		}

		Sleep(1);
	}
}


/* ----------主函数---------- */
int main()
{
	if (!WinsockTcp::Startup()) return -1;

	// 创建服务器
	WinsockTcp Server(WinsockTcp::Purpose::SERVER);
	if (!Server.isCreated()) return -1;

	// 绑定
	if (Server.Bind(nullptr, 9999) != 0) return -1;

	// 监听
	if (Server.Listen(5) != 0) return -1;

	// 创建线程管理连接
	std::thread th(Manage, std::ref(Server));
	th.detach();

	cout << "----------正在监听----------" << endl;
	while (true)
	{
		// 从连接请求队列中取出排在最前面的一个客户请求，如果队列为空就阻塞
		sockaddr_in addrClient{};
		SOCKET sockConn = Server.Accept(&addrClient);
		if (sockConn == INVALID_SOCKET) continue;

		cout << "用户接入：" << inet_ntoa(addrClient.sin_addr) << " - " << ntohs(addrClient.sin_port) << endl;

		ULONG ipaddr = ntohl(addrClient.sin_addr.S_un.S_addr);
		std::lock_guard<std::mutex> lg(ipMapMutex);
		++ipMap[ipaddr];
		if (ipMap[ipaddr] > 2)
		{
			--ipMap[ipaddr];
			Server.CloseSocket(sockConn);
		}
		else sockQueue.push({ sockConn,ipaddr });
	}

	WinsockTcp::Cleanup();
	return 0;
}
