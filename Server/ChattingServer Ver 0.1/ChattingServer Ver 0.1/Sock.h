#pragma once
#include <iostream>
#include <vector>
#include <winsock2.h>
using namespace std;
class Sock
{
private:
	std::vector<SOCKET> socklist;
	SOCKET listen_sock;
	enum { SERVERPORT = 9190 };
public:
	Sock(void);
	~Sock(void);
	bool Init(void);
	void Close(SOCKET*,bool bIsForce=false);
	SOCKET* GetListenSock(void);
	bool Listen(void);
	bool Start(void);
	template<typename data, typename size>
	int Send(SOCKET, data, size) const;
	template<typename data, typename size>
	int Recvn(SOCKET, data, size, int) const;
	void err_quit(char*) const;
	void err_display(char*) const;



};