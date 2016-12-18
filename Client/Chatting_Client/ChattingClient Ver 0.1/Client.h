#pragma once
#include<WinSock2.h>

class ClientSocket {
public:
	ClientSocket(SOCKET sock = INVALID_SOCKET);
	~ClientSocket();

	//void Attach(SOCKET sock);
	bool Create();
	bool Connect(const char *ip, unsigned short port);
	bool IsValid() {
		return mSock != INVALID_SOCKET;
	}
	void Close();
	int Send(const char*buf, int size);
	int Recv(char*buf, int size);
public:
	SOCKET mSock;
};
