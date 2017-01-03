#include "Sock.h"
#pragma comment(lib,"ws2_32")

// 설계미스..
// 멀티 유저 지원하려 했으나
// 소켓 구분 불가
// 멀티 유저 채팅 프로그램 -> 1:1 echo 프로그램으로 바뀜.
int main()
{


	Sock sock;
	sock.MysqlInit();
	sock.Init();
	sock.Listen();
	sock.Start(sock);
	
	sock.Close(sock.GetListenSock());



}