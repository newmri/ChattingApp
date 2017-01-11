#pragma once
#include <afx.h>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32")
enum { ENROLL = 1, SECESSION, LOGIN, CHATTINGDATA,USERLIST};
struct User {
	int type{};
	CString id;
	CString nickname;
	CString pwd;
};
struct UserS {
	int type{};
	CString id;
	CString pwd;
};
class Sock {
private:
	SOCKET sock;
	SOCKADDR_IN serveraddr;
	User user;
	UserS users;
	HANDLE m_hWnd;
	int num{};
	const char* const SERVERIP = "127.0.0.1";
	enum { SERVERPORT = 8000 };
public:
	Sock(void);
	~Sock(void);
	char m_buf[1024]{};
	bool Init(void);
	bool setHandle(HANDLE);
	bool Connect(void);
	int& getNum(void);
	SOCKET& getSocket(void);
	void Close(SOCKET*, bool);
	bool CheckEnroll(void);
	User& getUser(void);
	bool SendType(int);
	bool Send(char*,int);
	bool Recv(char*,int,int);
	int Recvn(char*, int, int);
	void err_quit(char*) const;
	void err_display(char*) const;

};
