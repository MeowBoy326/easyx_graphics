#pragma once


#define _WINSOCK_DEPRECATED_NO_WARNINGS


/* ----------ͷ�ļ�---------- */
#include <WinSock2.h>
#pragma comment (lib, "ws2_32")
#include <exception>


/* ----------��װ WinSock TCP ����---------- */
class WinsockTcp
{
public:
	// ���� WinsockTcp ʵ����;�����������߿ͻ���
	enum class Purpose :bool { SERVER, CLIENT };

public:
	// ��ʼ�� WinSock ��
	static bool Startup();

	// �ͷ� WinSock ��
	static void Cleanup() { WSACleanup(); }

	// ��������
	virtual ~WinsockTcp();

	// ���캯����ȷ����;
	WinsockTcp(Purpose pup);

	// ���ʵ���Ƿ񴴽��ɹ�
	bool isCreated() const { return succeed; }

	// �󶨣������ڷ�������ip Ϊ nullptr ʱ��ʾ��ϵͳѡȡ���õ�ַ
	int Bind(const char* ip, unsigned short port);

	// �����������ڷ�����
	int Listen(int n);

	// ���ӣ������ڿͻ���
	int Connect(const char* ip, unsigned short port);

	// ���ܣ������ڷ�����
	SOCKET Accept(sockaddr_in* addr = nullptr);

	// �ر����ӣ������ڷ�����
	int CloseSocket(SOCKET s);

	// �������ݣ��ð汾�����ڿͻ���
	int Send(const char* buf, int len);
	// �������ݣ��ð汾�����ڷ����������� s Ϊ Accept ����ֵ
	int Send(SOCKET s, const char* buf, int len);

	// �������ݣ��ð汾�����ڿͻ��ˣ�flag Ϊ true ��ʾ��Ҫ���� len ���Ȳŷ���
	int Recv(char* buf, int len, bool flag = false);
	// �������ݣ��ð汾�����ڷ����������� s Ϊ Accept ����ֵ��flag Ϊ true ��ʾ��Ҫ���� len ���Ȳŷ���
	int Recv(SOCKET s, char* buf, int len, bool flag = false);

	// ���ý��ճ�ʱ���ð汾�����ڿͻ���
	int SetRecvTimeOut(DWORD ms);
	// ���ý��ճ�ʱ���ð汾�����ڷ����������� s Ϊ Accept ����ֵ
	int SetRecvTimeOut(SOCKET s, DWORD ms);

	// ���÷��ͳ�ʱ���ð汾�����ڿͻ���
	int SetSendTimeOut(DWORD ms);
	// ���÷��ͳ�ʱ���ð汾�����ڷ����������� s Ϊ Accept ����ֵ
	int SetSendTimeOut(SOCKET s, DWORD ms);

	// �رշ��ͣ��ð汾�����ڿͻ���
	int ShutdownSend();
	// �رշ��ͣ��ð汾�����ڷ����������� s Ϊ Accept ����ֵ
	int ShutdownSend(SOCKET s);

	// �رս��գ��ð汾�����ڿͻ���
	int ShutdownRecv();
	// �رս��գ��ð汾�����ڷ����������� s Ϊ Accept ����ֵ
	int ShutdownRecv(SOCKET s);

	// ͬʱ�رշ��ͺͽ��գ��ð汾�����ڿͻ���
	int ShutdownSendRecv();
	// ͬʱ�رս��պͷ��ͣ��ð汾�����ڷ����������� s Ϊ Accept ����ֵ
	int ShutdownSendRecv(SOCKET s);

private:
	SOCKET sockListen{};		// �����׽���
	SOCKET sockConnect{};		// �����׽���
	Purpose purpos;				// ��;
	bool succeed;				// �����Ƿ񴴽��ɹ�
};


/* ----------����ʵ��---------- */

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
		// ���������������׽���
		sockListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sockListen == INVALID_SOCKET)
		{
			succeed = false;
			return;
		}
	}
	else if (purpos == Purpose::CLIENT)
	{
		// �����ͻ��������׽���
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
	if (purpos != Purpose::SERVER) throw std::exception("Bind ���������ڷ�����...");

	// ���������ص�ַ
	sockaddr_in addrServer{};
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(port);
	addrServer.sin_addr.S_un.S_addr = ip == nullptr ? htonl(INADDR_ANY) : inet_addr(ip);

	return bind(sockListen, (sockaddr*)&addrServer, sizeof(addrServer));
}


int WinsockTcp::Listen(int n)
{
	if (purpos != Purpose::SERVER) throw std::exception("Listen ���������ڷ�����...");
	return listen(sockListen, n);
}


int WinsockTcp::Connect(const char* ip, unsigned short port)
{
	if (purpos != Purpose::CLIENT) throw std::exception("Connect ���������ڿͻ���...");

	// ��������ַ
	sockaddr_in addrServer{};
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(port);
	addrServer.sin_addr.S_un.S_addr = inet_addr(ip);
	return connect(sockConnect, (sockaddr*)&addrServer, sizeof(addrServer));
}


SOCKET WinsockTcp::Accept(sockaddr_in* addr)
{
	if (purpos != Purpose::SERVER) throw std::exception("Accept ���������ڷ�����...");

	sockaddr_in addrClient{};
	int addrLen = sizeof(addrClient);
	SOCKET ret = accept(sockListen, (sockaddr*)&addrClient, &addrLen);
	if (addr != nullptr) *addr = addrClient;

	return ret;
}


int WinsockTcp::CloseSocket(SOCKET s)
{
	if (purpos != Purpose::SERVER) throw std::exception("�ú��������ڷ�����...");
	return closesocket(s);
}


int WinsockTcp::Send(const char* buf, int len)
{
	if (purpos != Purpose::CLIENT) throw std::exception("�ú��������ڿͻ���...");
	return send(sockConnect, buf, len, 0);
}
int WinsockTcp::Send(SOCKET s, const char* buf, int len)
{
	if (purpos != Purpose::SERVER) throw std::exception("�ú��������ڷ�����...");
	return send(s, buf, len, 0);
}


int WinsockTcp::Recv(char* buf, int len, bool flag)
{
	if (purpos != Purpose::CLIENT) throw std::exception("�ú��������ڿͻ���...");

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
	if (purpos != Purpose::SERVER) throw std::exception("�ú��������ڷ�����...");

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
	if (purpos != Purpose::CLIENT) throw std::exception("�ú��������ڿͻ���...");
	return setsockopt(sockConnect, SOL_SOCKET, SO_RCVTIMEO, (char*)&ms, sizeof(ms));
}
int WinsockTcp::SetRecvTimeOut(SOCKET s, DWORD ms)
{
	if (purpos != Purpose::SERVER) throw std::exception("�ú��������ڷ�����...");
	return setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char*)&ms, sizeof(ms));
}


int WinsockTcp::SetSendTimeOut(DWORD ms)
{
	if (purpos != Purpose::CLIENT) throw std::exception("�ú��������ڿͻ���...");
	return setsockopt(sockConnect, SOL_SOCKET, SO_SNDTIMEO, (char*)&ms, sizeof(ms));
}
int WinsockTcp::SetSendTimeOut(SOCKET s, DWORD ms)
{
	if (purpos != Purpose::SERVER) throw std::exception("�ú��������ڷ�����...");
	return setsockopt(s, SOL_SOCKET, SO_SNDTIMEO, (char*)&ms, sizeof(ms));
}


int WinsockTcp::ShutdownSend()
{
	if (purpos != Purpose::CLIENT) throw std::exception("�ú��������ڿͻ���...");
	return shutdown(sockConnect, SD_SEND);
}
int WinsockTcp::ShutdownSend(SOCKET s)
{
	if (purpos != Purpose::SERVER) throw std::exception("�ú��������ڷ�����...");
	return shutdown(s, SD_SEND);
}


int WinsockTcp::ShutdownRecv()
{
	if (purpos != Purpose::CLIENT) throw std::exception("�ú��������ڿͻ���...");
	return shutdown(sockConnect, SD_RECEIVE);
}
int WinsockTcp::ShutdownRecv(SOCKET s)
{
	if (purpos != Purpose::SERVER) throw std::exception("�ú��������ڷ�����...");
	return shutdown(s, SD_RECEIVE);
}


int WinsockTcp::ShutdownSendRecv()
{
	if (purpos != Purpose::CLIENT) throw std::exception("�ú��������ڿͻ���...");
	return shutdown(sockConnect, SD_BOTH);
}
int WinsockTcp::ShutdownSendRecv(SOCKET s)
{
	if (purpos != Purpose::SERVER) throw std::exception("�ú��������ڷ�����...");
	return shutdown(s, SD_BOTH);
}
