#include "Sock.h"
#pragma comment(lib,"ws2_32")

// ����̽�..
// ��Ƽ ���� �����Ϸ� ������
// ���� ���� �Ұ�
// ��Ƽ ���� ä�� ���α׷� -> 1:1 echo ���α׷����� �ٲ�.
int main()
{


	Sock sock;
	sock.MysqlInit();
	sock.Init();
	sock.Listen();
	sock.Start(sock);
	
	sock.Close(sock.GetListenSock());



}