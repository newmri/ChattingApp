#pragma once
#include <Windows.h>
#pragma comment(lib,"ws2_32")
class ClientSocket {
private:
	SOCKET sock;
	SOCKADDR_IN serveraddr;
	char* SERVERIP = "127.0.0.1";
	enum { SERVERPORT = 9190 };
public:
	ClientSocket(void);
	~ClientSocket(void);

	void Init(void);
	int Connect(void);
	void Close(void);
	int Send(const char*buf, int size);
	int Recv(char*buf, int size);
	void err_quit(char*) const;
	void err_display(char*) const;

};
