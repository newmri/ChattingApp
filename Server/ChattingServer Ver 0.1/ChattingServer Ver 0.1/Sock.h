#pragma once
#include <iostream>
#include <vector>
#include <process.h>
#include "mysql.h"
#pragma comment(lib, "user32.lib") 
using namespace std;


class Sock
{
private:
	std::vector<SOCKET> socklist;
	std::vector<SOCKET>::iterator iters;
	std::vector<User> userlist;
	SOCKET listen_sock;
	Mysql mysql;
	User user;
	UserS users;
	char buf[128]{};
	HANDLE loginthread;
	enum { SERVERPORT = 9190 };
	enum { ENROLL = 1, SECESSION, LOGIN };
	int datatype{};
public:
	Sock(void);
	~Sock(void);
	bool Init(void);
	void Close(SOCKET*,bool bIsForce=false);
	SOCKET* GetListenSock(void);
	bool Listen(void);
	bool Start(Sock&);
	bool Send(char*, int);
	bool RecvType(Sock*);
	std::vector<User>* GetUserlist();
	bool Recv(char*,int);
	int Recvn(char*, int, int);
	void err_quit(char*) const;
	void err_display(char*) const;
	static unsigned int __stdcall LoginFunc(LPVOID);

	// ---------mysql------------ //
	bool MysqlInit(void);
	bool DivideUser(void);
	bool DivideUserS(void);


};