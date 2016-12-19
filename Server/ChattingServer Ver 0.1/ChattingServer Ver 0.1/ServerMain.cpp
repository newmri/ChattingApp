#include "Sock.h"
#pragma comment(lib,"ws2_32")
int main()
{

	Sock sock;
	sock.Init();
	sock.Listen();
	while (TRUE) {

		sock.Accept();

	}




}