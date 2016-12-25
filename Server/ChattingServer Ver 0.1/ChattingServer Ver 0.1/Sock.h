#pragma once

#include <iostream>
#include <afx.h>
#include <vector>
#include <winsock2.h>
#include<process.h>
using namespace std;

class User {
public:
	CString id;
	CString nickname;
	CString pwd;
};
class Sock
{
private:
	std::vector<SOCKET> socklist;
	std::vector<SOCKET>::iterator iters;
	std::vector<User> userlist;
	SOCKET listen_sock;
	char buf[128]{};
	HANDLE loginthread;
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
	bool Start(Sock&);
	bool Send(char*, int);
	bool RecvType(Sock*);
	std::vector<User>* GetUserlist();
	bool Recv(char*,int);
	int Recvn(char*, int, int);
	void err_quit(char*) const;
	void err_display(char*) const;
	static unsigned int __stdcall LoginFunc(LPVOID);



};