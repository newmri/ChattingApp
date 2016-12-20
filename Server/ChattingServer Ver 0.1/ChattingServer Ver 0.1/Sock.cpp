#include "Sock.h"

Sock::Sock(void) : socklist(),listen_sock(INVALID_SOCKET) {};
Sock::~Sock(void)
{
	WSACleanup();
}

bool Sock::Init(void)
{


	int retval;
	// winsock initial
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0){
		err_quit("[����] ��ġ : Sock::Init, ���� : WSAStartup() �Լ� ����");
		return false;
	}

	// socket()
	listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET){
		err_quit("[����] ��ġ : Sock::Init, ���� : socket() �Լ� ����");
		return false;
	}

	// bind()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) {
		err_quit("[����] ��ġ : Sock::Init, ���� : bind() �Լ� ����");
		return false;
	}
	return true;
	

}

void Sock::Close(SOCKET* psock, bool bIsForce)
{
	struct linger stLinger = { 0, 0 };
	// ���� ����
	if (true == bIsForce)
		stLinger.l_onoff = 1;
	// �ۼ��� �ߴ�
	shutdown(*psock, SD_BOTH);
	// �ɼ� ����
	setsockopt(*psock, SOL_SOCKET, SO_LINGER, (char*)&stLinger, sizeof(stLinger));
	// ���� ����
	closesocket(*psock);
	*psock = INVALID_SOCKET;
}
SOCKET* Sock::GetListenSock(void)
{
	SOCKET* sock = &listen_sock;
	return sock;
}
bool Sock::Listen(void)
{

	int retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) {
		err_quit("[����] ��ġ : Sock::Listen, ���� : listen() �Լ� ����");
		return false;
	}
	return true;
}
bool Sock::Start(void)
{
	cout << "���� ����" << endl;

	int retval{};
	SOCKADDR_IN clientaddr;
	int addrlen = sizeof(clientaddr);
	SOCKET client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
	if (client_sock == INVALID_SOCKET){
		err_display("[����] ��ġ : Sock::Start, ���� : accept() �Լ� ����");
		return false;
	}
	socklist.emplace_back(client_sock);
	
		//������ Ŭ���̾�Ʈ ���� ���
		//int retval = setsockopt(client_sock, SOL_SOCKET, SO_KEEPALIVE, (char*)&bEnable, sizeof(bEnable));
		//if (retval == SOCKET_ERROR)err_quit("setsockopt()");
		printf("Ŭ�� ����: ip=%s,��Ʈ=%d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
		return true;

}

void Sock::err_quit(char* msg) const
{
	LPVOID lpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, (LPCSTR)msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

void Sock::err_display(char* msg) const
{
	LPVOID lpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, (LPCSTR)msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
}
