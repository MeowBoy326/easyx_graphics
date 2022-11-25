/*
	�������ƣ�
			ɨ��������ս�� - ������

	��飺
			����ƥ���ս��ɨ�׳���������·������飬���������䣬�򷭿����һ��������Ӯ

	������
			VS2019 + EasyX_20210115(beta)

	ʱ�䣺
			2021.1.18

	���ߣ�
			Teternity(QQ:1926594835)

	��Ȩ��
			����ԭ�����޳�Ϯ�����漰��Ȩ���⣬������ѧϰ
*/


/* ----------ͷ�ļ�---------- */
#include "WinsockTcp.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <unordered_map>
#include <easyx.h>

using std::cout;
using std::endl;


/* ----------�̰߳�ȫ����---------- */
class ThreadSafeQueue
{
public:
	// Ĭ�Ϲ���
	ThreadSafeQueue() = default;

	// �����
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

	// ������
	void pop(std::pair<SOCKET, ULONG>* par)
	{
		std::lock_guard<std::mutex> lg(mut);
		if (par != nullptr) *par = que.front();
		que.pop();
	}

	// ��ȡ��ͷԪ��
	std::pair<SOCKET, ULONG> front()
	{
		std::lock_guard<std::mutex> lg(mut);
		if (que.empty()) return { INVALID_SOCKET,0 };
		return que.front();
	}

	// ������Ԫ�ظ���
	int size()
	{
		std::lock_guard<std::mutex> lg(mut);
		return que.size();
	}

private:
	std::mutex mut;
	std::queue<std::pair<SOCKET, ULONG>> que;
};

// ����ȫ���̰߳�ȫ���ж���
ThreadSafeQueue sockQueue;


/* ----------ȫ������---------- */
// �����趨
const int nRow = 30;				// ���������
const int nCol = 20;				// ���������
const int munMine = 108;			// ����Ŀ

// �������ֵ
// '0' ��ʾ�հף�'1' - '8' ��ʾ������Χ����Ŀ��ֵ 1 ��ʾ��
const char MINE = 1;

// ������Ϣ�ṹ��
struct Info
{
	int code;			// ״̬�룬1 �����������У�2 ��������������3 ����Ͽ�
	unsigned int uMsg;	// �����Ϣ uMsg
	int x;				// ���λ�� x
	int y;				// ���λ�� y;
};

// IP Map
std::unordered_map<ULONG, int> ipMap;
std::mutex ipMapMutex;


/* ----------�̺߳�����ά����������---------- */
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
		// ���ɵ�ͼ
		char* Map = new char[nRow * nCol];
		memset(Map, 0, nRow * nCol);
		// ��������
		for (int i = 0; i < munMine; ++i) Map[i] = MINE;
		// ��������
		std::random_shuffle(Map, Map + nRow * nCol);
		// ����ȷ��ÿ������ֵ
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

		// ���������͵�ͼ����
		int ret1 = Server.Send(p1.first, Map, nRow * nCol);
		int ret2 = Server.Send(p2.first, Map, nRow * nCol);
		if (ret1 == SOCKET_ERROR || ret2 == SOCKET_ERROR)
		{
			closeSockets();
			return;
		}

		delete[] Map;

		// ����������Ϣ��'1' ����
		char ch1 = '1', ch2 = '0';
		ret1 = Server.Send(p1.first, &ch1, 1);
		ret2 = Server.Send(p2.first, &ch2, 1);
		if (ret1 == SOCKET_ERROR || ret2 == SOCKET_ERROR)
		{
			closeSockets();
			return;
		}

		// ���ý��ճ�ʱ
		Server.SetRecvTimeOut(p1.first, 1000 * 18);
		Server.SetRecvTimeOut(p2.first, 1000 * 18);

		Info info{};

		// ѭ��ת����Ϣ
		while (true)
		{
			// ���� p1 �����ĵ����Ϣ
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

			// ���� p2 �����ĵ����Ϣ
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


/* ----------�̺߳�����ά����������---------- */
void Manage(WinsockTcp& Server)
{
	clock_t ct = 0;
	SOCKET s = INVALID_SOCKET;

	while (true)
	{
		// �����г�ʱ�� (30s) ֻ��һ��Ԫ��ʱ����ʱ��Ͽ�������
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

		// �����д��ڵ���������Աʱ
		if (sockQueue.size() > 1)
		{
			std::pair<SOCKET, ULONG> p1, p2;
			sockQueue.pop(&p1);
			sockQueue.pop(&p2);

			// �����̹߳���һ������
			std::thread th(Conn, std::ref(Server), p1, p2);
			th.detach();
		}

		Sleep(1);
	}
}


/* ----------������---------- */
int main()
{
	if (!WinsockTcp::Startup()) return -1;

	// ����������
	WinsockTcp Server(WinsockTcp::Purpose::SERVER);
	if (!Server.isCreated()) return -1;

	// ��
	if (Server.Bind(nullptr, 9999) != 0) return -1;

	// ����
	if (Server.Listen(5) != 0) return -1;

	// �����̹߳�������
	std::thread th(Manage, std::ref(Server));
	th.detach();

	cout << "----------���ڼ���----------" << endl;
	while (true)
	{
		// ���������������ȡ��������ǰ���һ���ͻ������������Ϊ�վ�����
		sockaddr_in addrClient{};
		SOCKET sockConn = Server.Accept(&addrClient);
		if (sockConn == INVALID_SOCKET) continue;

		cout << "�û����룺" << inet_ntoa(addrClient.sin_addr) << " - " << ntohs(addrClient.sin_port) << endl;

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
