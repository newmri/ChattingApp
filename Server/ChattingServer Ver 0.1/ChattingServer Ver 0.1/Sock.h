#pragma once
#include <iostream>
#include <vector>
#include <winsock2.h>
using namespace std;
class Sock
{
private:
	std::vector<SOCKET> socklist;
	std::vector<SOCKET>::iterator itor = socklist.begin();
	SOCKET listen_sock;
	enum { SERVERPORT = 9190 };
	enum { ENROLL = 1 };
	int datatype{};
public:
	Sock(void);
	~Sock(void);
	bool Init(void);
	void Close(SOCKET*,bool bIsForce=false);
	SOCKET* GetListenSock(void);
	bool Listen(void);
	bool Start(void);
	bool Send(char*, int);
	bool RecvType(void);
	bool Recv(char*, int, int);
	int Recvn(char*, int, int);
	void err_quit(char*) const;
	void err_display(char*) const;



};