#include "Sock.h"

Sock::Sock(void) : socklist(),loginthread(),iters(), userlist(),listen_sock(INVALID_SOCKET) {};
Sock::~Sock(void)
{
	WSACleanup();
	CloseHandle(loginthread);
}

bool Sock::Init(void)
{


	int retval;
	// winsock initial
	WSADATA wsa;
	if (0!= WSAStartup(MAKEWORD(2, 2), &wsa)){
		err_quit("[����] ��ġ : Sock::Init, ���� : WSAStartup() �Լ� ����");
		return false;
	}

	// socket()
	listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == listen_sock){
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
	if (SOCKET_ERROR == retval) {
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
	if (SOCKET_ERROR == retval) {
		err_quit("[����] ��ġ : Sock::Listen, ���� : listen() �Լ� ����");
		return false;
	}
	return true;
}
bool Sock::Start(Sock& sock)
{
	cout << "���� ����" << endl;

	int retval{};
	SOCKADDR_IN clientaddr;
	int addrlen = sizeof(clientaddr);
	while (true) {
		SOCKET client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
		if (INVALID_SOCKET == client_sock) {
			err_display("[����] ��ġ : Sock::Start, ���� : accept() �Լ� ����");
			return false;
		}
		
		socklist.emplace_back(client_sock);

		//������ Ŭ���̾�Ʈ ���� ���
		//int retval = setsockopt(client_sock, SOL_SOCKET, SO_KEEPALIVE, (char*)&bEnable, sizeof(bEnable));
		//if (retval == SOCKET_ERROR)err_quit("setsockopt()");
		printf("Ŭ�� ����: ip=%s,��Ʈ=%d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
		loginthread = (HANDLE)_beginthreadex(NULL, 0, LoginFunc,&sock, NULL, 0);
		WaitForSingleObject(loginthread, INFINITE);
	}
		return true;

}

unsigned int __stdcall Sock::LoginFunc(LPVOID lpVoid)
{
	while (true)
	{
		Sock* sock = static_cast<Sock*>(lpVoid);
		sock->RecvType(sock);
	}
	return false;

}
bool Sock::Send(char* data, int len)
{
	int retval{};
	// sending data(fixed)
	retval = send(*iters, (char*)&len, sizeof(len), 0);
	if (SOCKET_ERROR == retval) {
		err_display("[����] ��ġ : Sock::Send, ���� : send() �Լ� ����");
		return false;
	}
	// sending data(flexible)
	retval = send(*iters, data, len, 0);
	if (SOCKET_ERROR == retval) {
		err_display("[����] ��ġ : Sock::Send, ���� : send() �Լ� ����");
		return false;
	}

	else if (0 == retval) {
		err_display("[����] ��ġ : Sock::Send, ���� : ���� ����");
		return false;
	}

	return true;
}
bool Sock::RecvType(Sock* sock)
{
	int retval{};
	// receive datatype
	retval = Recvn((char*)&datatype, sizeof(datatype),0);

	if (SOCKET_ERROR == retval)
	{
		err_display("[����] ��ġ : Sock::RecvType, ���� : Recvn() �Լ� ����");
		return false;
	}
	else if (0 == retval) {
		err_display("[����] ��ġ : Sock::RecvType, ���� : ���� ����");
		return false;
	}

	retval = sock->Recv(buf, 0);
	if (ENROLL == datatype){
		sock->DivideUser();
		sock->mysql.SetUser(user);
		bool ret=sock->mysql.Enroll();
		sock->Send((char*)&ret, sizeof(ret));
	}
	else if (SECESSION == datatype || LOGIN == datatype) {
		sock->DivideUserS();
		sock->mysql.SetUserS(users);
		bool ret=sock->mysql.Login();
		sock->Send((char*)&ret, sizeof(ret));
	}
	if(retval)
	return true;
	else if (!retval)
	return false;

}

std::vector<User>* Sock::GetUserlist()
{
	return &userlist;

}

bool Sock::Recv(char* data,int flags)
{
	int retval{};
	int len{};
	// receive data(fixed)
	retval = Recvn((char*)&len,sizeof(int), flags);
	if (SOCKET_ERROR == retval)
	{
		err_display("[����] ��ġ : Sock::Recv, ���� : Recvn() �Լ� ����");
		return false;
	}
	else if (0 == retval) {
		err_display("[����] ��ġ : Sock::Recv, ���� : ���� ����");
		return false;
	}
	// received data(flexible)
	retval = Recvn(data, len, flags);
	if (SOCKET_ERROR == retval)
	{
		err_display("[����] ��ġ : Sock::Recv, ���� : Recvn() �Լ� ����");
		return false;
	}

	else if (0 == retval) {
		err_display("[����] ��ġ : Sock::Recv, ���� : ���� ����");
		return false;
	}

	return true;


}
int Sock::Recvn(char* buf, int len, int flags)
{
	int received;
	char* ptr = buf;
	int left = len;
	iters = socklist.begin();
	while (left > 0)
	{
		received = recv(*iters, ptr, left, flags);
		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if (received == 0)
			break;
		left -= received;
		ptr += received;
	}
	return(len - left);


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

bool Sock::DivideUser(void)
{
	char* result = nullptr;
	int count{};
	result = strtok(buf, " ");
	while (NULL != result) {
		switch (count)
		{
		case 0:
			user.id = result;
			break;
		case 1:
			user.pwd = result;
			break;
		case 2:
			user.nickname = result;
			break;
		}
		count++;
		result = strtok(NULL, " ");
	}
	return true;

}

bool Sock::DivideUserS(void)
{
	char* result = nullptr;
	int count{};
	result = strtok(buf, " ");
	while (NULL != result) {
		switch (count)
		{
		case 0:
			users.id = result;
			break;
		case 1:
			users.pwd = result;
			break;
		}
		count++;
		result = strtok(NULL, " ");
	}
	return true;

}
bool Sock::MysqlInit(void)
{
	bool retval=mysql.Init();
	if (retval)
		return true;
	else
		return false;


}