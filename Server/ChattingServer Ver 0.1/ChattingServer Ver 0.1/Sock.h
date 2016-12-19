#pragma once
#include <iostream>
#include <winsock2.h>
#include <vector>
using namespace std;
class Sock
{
private:
	vector<SOCKET> socklist;
	SOCKET listen_sock;
	enum { SERVERPORT = 9190 };
public:
	Sock(void);
	void Init(void);
	void Close(void);
	void Listen(void);
	void Accept(void);
	template<typename data, typename size>
	int Send(SOCKET, data, size) const;
	template<typename data, typename size>
	int Recvn(SOCKET, data, size, int) const;
	void err_quit(char*) const;
	void err_display(char*) const;



};