#pragma once


#define _WINSOCK_DEPRECATED_NO_WARNINGS


/* ----------头文件---------- */
#include <WinSock2.h>
#pragma comment (lib, "ws2_32")
#include <exception>


/* ----------封装 WinSock TCP 操作---------- */
class WinsockTcp
{
public:
	// 定义 WinsockTcp 实例用途，服务器或者客户端
	enum class Purpose :bool { SERVER, CLIENT };

public:
	// 初始化 WinSock 库
	static bool Startup();

	// 释放 WinSock 库
	static void Cleanup() { WSACleanup(); }

	// 析构函数
	virtual ~WinsockTcp();

	// 构造函数，确定用途
	WinsockTcp(Purpose pup);

	// 检查实例是否创建成功
	bool isCreated() const { return succeed; }

	// 绑定，仅用于服务器，ip 为 nullptr 时表示让系统选取可用地址
	int Bind(const char* ip, unsigned short port);

	// 监听，仅用于服务器
	int Listen(int n);

	// 连接，仅用于客户端
	int Connect(const char* ip, unsigned short port);

	// 接受，仅用于服务器
	SOCKET Accept(sockaddr_in* addr = nullptr);

	// 关闭连接，仅用于服务器
	int CloseSocket(SOCKET s);

	// 发送数据，该版本仅用于客户端
	int Send(const char* buf, int len);
	// 发送数据，该版本仅用于服务器，参数 s 为 Accept 返回值
	int Send(SOCKET s, const char* buf, int len);

	// 接收数据，该版本仅用于客户端，flag 为 true 表示需要接收 len 长度才返回
	int Recv(char* buf, int len, bool flag = false);
	// 接收数据，该版本仅用于服务器，参数 s 为 Accept 返回值，flag 为 true 表示需要接收 len 长度才返回
	int Recv(SOCKET s, char* buf, int len, bool flag = false);

	// 设置接收超时，该版本仅用于客户端
	int SetRecvTimeOut(DWORD ms);
	// 设置接收超时，该版本仅用于服务器，参数 s 为 Accept 返回值
	int SetRecvTimeOut(SOCKET s, DWORD ms);

	// 设置发送超时，该版本仅用于客户端
	int SetSendTimeOut(DWORD ms);
	// 设置发送超时，该版本仅用于服务器，参数 s 为 Accept 返回值
	int SetSendTimeOut(SOCKET s, DWORD ms);

	// 关闭发送，该版本仅用于客户端
	int ShutdownSend();
	// 关闭发送，该版本仅用于服务器，参数 s 为 Accept 返回值
	int ShutdownSend(SOCKET s);

	// 关闭接收，该版本仅用于客户端
	int ShutdownRecv();
	// 关闭接收，该版本仅用于服务器，参数 s 为 Accept 返回值
	int ShutdownRecv(SOCKET s);

	// 同时关闭发送和接收，该版本仅用于客户端
	int ShutdownSendRecv();
	// 同时关闭接收和发送，该版本仅用于服务器，参数 s 为 Accept 返回值
	int ShutdownSendRecv(SOCKET s);

private:
	SOCKET sockListen{};		// 监听套接字
	SOCKET sockConnect{};		// 连接套接字
	Purpose purpos;				// 用途
	bool succeed;				// 对象是否创建成功
};


/* ----------函数实现---------- */

bool WinsockTcp::Startup()
{
	WSADATA wsaData;
	return WSAStartup(MAKEWORD(2, 2), &wsaData) == 0;
}


WinsockTcp::~WinsockTcp()
{
	if (purpos == Purpose::CLIENT) closesocket(sockConnect);
	if (purpos == Purpose::SERVER) closesocket(sockListen);
}


WinsockTcp::WinsockTcp(Purpose pup)
{
	purpos = pup;
	if (purpos == Purpose::SERVER)
	{
		// 创建服务器监听套接字
		sockListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sockListen == INVALID_SOCKET)
		{
			succeed = false;
			return;
		}
	}
	else if (purpos == Purpose::CLIENT)
	{
		// 创建客户端连接套接字
		sockConnect = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sockConnect == INVALID_SOCKET)
		{
			succeed = false;
			return;
		}
	}
	else
	{
		succeed = false;
		return;
	}

	succeed = true;
}


int WinsockTcp::Bind(const char* ip, unsigned short port)
{
	if (purpos != Purpose::SERVER) throw std::exception("Bind 函数仅用于服务器...");

	// 服务器本地地址
	sockaddr_in addrServer{};
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(port);
	addrServer.sin_addr.S_un.S_addr = ip == nullptr ? htonl(INADDR_ANY) : inet_addr(ip);

	return bind(sockListen, (sockaddr*)&addrServer, sizeof(addrServer));
}


int WinsockTcp::Listen(int n)
{
	if (purpos != Purpose::SERVER) throw std::exception("Listen 函数仅用于服务器...");
	return listen(sockListen, n);
}


int WinsockTcp::Connect(const char* ip, unsigned short port)
{
	if (purpos != Purpose::CLIENT) throw std::exception("Connect 函数仅用于客户端...");

	// 服务器地址
	sockaddr_in addrServer{};
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(port);
	addrServer.sin_addr.S_un.S_addr = inet_addr(ip);
	return connect(sockConnect, (sockaddr*)&addrServer, sizeof(addrServer));
}


SOCKET WinsockTcp::Accept(sockaddr_in* addr)
{
	if (purpos != Purpose::SERVER) throw std::exception("Accept 函数仅用于服务器...");

	sockaddr_in addrClient{};
	int addrLen = sizeof(addrClient);
	SOCKET ret = accept(sockListen, (sockaddr*)&addrClient, &addrLen);
	if (addr != nullptr) *addr = addrClient;

	return ret;
}


int WinsockTcp::CloseSocket(SOCKET s)
{
	if (purpos != Purpose::SERVER) throw std::exception("该函数仅用于服务器...");
	return closesocket(s);
}


int WinsockTcp::Send(const char* buf, int len)
{
	if (purpos != Purpose::CLIENT) throw std::exception("该函数仅用于客户端...");
	return send(sockConnect, buf, len, 0);
}
int WinsockTcp::Send(SOCKET s, const char* buf, int len)
{
	if (purpos != Purpose::SERVER) throw std::exception("该函数仅用于服务器...");
	return send(s, buf, len, 0);
}


int WinsockTcp::Recv(char* buf, int len, bool flag)
{
	if (purpos != Purpose::CLIENT) throw std::exception("该函数仅用于客户端...");

	if (!flag) return recv(sockConnect, buf, len, 0);
	else
	{
		int total = len;
		while (total > 0)
		{
			int ret = recv(sockConnect, buf + (len - total), total, 0);
			if (ret < 1) return ret;
			else total -= ret;
		}
	}

	return len;
}
int WinsockTcp::Recv(SOCKET s, char* buf, int len, bool flag)
{
	if (purpos != Purpose::SERVER) throw std::exception("该函数仅用于服务器...");

	if (!flag) return recv(s, buf, len, 0);
	else
	{
		int total = len;
		while (total > 0)
		{
			int ret = recv(s, buf + (len - total), total, 0);
			if (ret < 1) return ret;
			else total -= ret;
		}
	}

	return len;
}


int WinsockTcp::SetRecvTimeOut(DWORD ms)
{
	if (purpos != Purpose::CLIENT) throw std::exception("该函数仅用于客户端...");
	return setsockopt(sockConnect, SOL_SOCKET, SO_RCVTIMEO, (char*)&ms, sizeof(ms));
}
int WinsockTcp::SetRecvTimeOut(SOCKET s, DWORD ms)
{
	if (purpos != Purpose::SERVER) throw std::exception("该函数仅用于服务器...");
	return setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char*)&ms, sizeof(ms));
}


int WinsockTcp::SetSendTimeOut(DWORD ms)
{
	if (purpos != Purpose::CLIENT) throw std::exception("该函数仅用于客户端...");
	return setsockopt(sockConnect, SOL_SOCKET, SO_SNDTIMEO, (char*)&ms, sizeof(ms));
}
int WinsockTcp::SetSendTimeOut(SOCKET s, DWORD ms)
{
	if (purpos != Purpose::SERVER) throw std::exception("该函数仅用于服务器...");
	return setsockopt(s, SOL_SOCKET, SO_SNDTIMEO, (char*)&ms, sizeof(ms));
}


int WinsockTcp::ShutdownSend()
{
	if (purpos != Purpose::CLIENT) throw std::exception("该函数仅用于客户端...");
	return shutdown(sockConnect, SD_SEND);
}
int WinsockTcp::ShutdownSend(SOCKET s)
{
	if (purpos != Purpose::SERVER) throw std::exception("该函数仅用于服务器...");
	return shutdown(s, SD_SEND);
}


int WinsockTcp::ShutdownRecv()
{
	if (purpos != Purpose::CLIENT) throw std::exception("该函数仅用于客户端...");
	return shutdown(sockConnect, SD_RECEIVE);
}
int WinsockTcp::ShutdownRecv(SOCKET s)
{
	if (purpos != Purpose::SERVER) throw std::exception("该函数仅用于服务器...");
	return shutdown(s, SD_RECEIVE);
}


int WinsockTcp::ShutdownSendRecv()
{
	if (purpos != Purpose::CLIENT) throw std::exception("该函数仅用于客户端...");
	return shutdown(sockConnect, SD_BOTH);
}
int WinsockTcp::ShutdownSendRecv(SOCKET s)
{
	if (purpos != Purpose::SERVER) throw std::exception("该函数仅用于服务器...");
	return shutdown(s, SD_BOTH);
}
