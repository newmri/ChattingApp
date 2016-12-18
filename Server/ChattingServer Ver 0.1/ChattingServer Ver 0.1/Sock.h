#pragma once
#include"Common.h"
class Sock
{
private:
	vector<SOCKET> sock;
	SOCKET listen_sock;
public:
	void Init(void);
	void Close(void);
	int Listen(void);
	void Accept(void);
	template<typename data, typename size>
	int Send(SOCKET, data, size) const;
	template<typename data, typename size>
	int Recvn(SOCKET, data, size, int) const;
	void err_quit(char*) const;
	void err_display(char*) const;



};