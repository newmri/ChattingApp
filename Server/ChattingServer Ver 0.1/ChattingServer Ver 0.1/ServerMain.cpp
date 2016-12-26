#include "Sock.h"
#pragma comment(lib,"ws2_32")


int main()
{


	Sock sock;
	sock.MysqlInit();
	sock.Init();
	sock.Listen();
	sock.Start(sock);
	
	sock.Close(sock.GetListenSock());



}