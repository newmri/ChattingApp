#include "Sock.h"
#include "mysql.h"
#pragma comment(lib,"ws2_32")

int main()
{
	Mysql mysql;
	mysql.Init();

	Sock sock;
	sock.Init();
	sock.Listen();
	sock.Start(sock);
	
	sock.Close(sock.GetListenSock());



}