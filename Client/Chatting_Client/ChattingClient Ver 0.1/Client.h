#pragma once
#include <WinSock2.h>
#pragma comment(lib,"ws2_32")
class Sock {
private:
	SOCKET sock;
	SOCKADDR_IN serveraddr;
	char* SERVERIP = "127.0.0.1";
	enum { SERVERPORT = 9190 };
	enum { ENROLL = 1 };
public:
	Sock(void);
	~Sock(void);

	bool Init(void);
	bool Connect(void);
	void Close(SOCKET*, bool);
	bool SendType(int);
	bool Send(char*,int);
	bool Recv(char*, int, int);
	int Recvn(char*, int, int);
	void err_quit(char*) const;
	void err_display(char*) const;

};
