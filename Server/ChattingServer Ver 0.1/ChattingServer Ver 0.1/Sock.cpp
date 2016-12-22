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
		err_quit("[에러] 위치 : Sock::Init, 이유 : WSAStartup() 함수 실패");
		return false;
	}

	// socket()
	listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == listen_sock){
		err_quit("[에러] 위치 : Sock::Init, 이유 : socket() 함수 실패");
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
		err_quit("[에러] 위치 : Sock::Init, 이유 : bind() 함수 실패");
		return false;
	}
	return true;
	

}

void Sock::Close(SOCKET* psock, bool bIsForce)
{
	struct linger stLinger = { 0, 0 };
	// 강제 종료
	if (true == bIsForce)
		stLinger.l_onoff = 1;
	// 송수신 중단
	shutdown(*psock, SD_BOTH);
	// 옵션 설정
	setsockopt(*psock, SOL_SOCKET, SO_LINGER, (char*)&stLinger, sizeof(stLinger));
	// 연결 종료
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
		err_quit("[에러] 위치 : Sock::Listen, 이유 : listen() 함수 실패");
		return false;
	}
	return true;
}
bool Sock::Start(Sock& sock)
{
	cout << "서버 시작" << endl;

	int retval{};
	SOCKADDR_IN clientaddr;
	int addrlen = sizeof(clientaddr);
	while (true) {
		SOCKET client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
		if (INVALID_SOCKET == client_sock) {
			err_display("[에러] 위치 : Sock::Start, 이유 : accept() 함수 실패");
			return false;
		}
		socklist.emplace_back(client_sock);

		//접속한 클라이언트 정보 출력
		//int retval = setsockopt(client_sock, SOL_SOCKET, SO_KEEPALIVE, (char*)&bEnable, sizeof(bEnable));
		//if (retval == SOCKET_ERROR)err_quit("setsockopt()");
		printf("클라 접속: ip=%s,포트=%d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
		loginthread = (HANDLE)_beginthreadex(NULL, 0, LoginFunc,&sock, NULL, 0);
		WaitForSingleObject(loginthread, INFINITE);
	}
		return true;

}

unsigned int __stdcall Sock::LoginFunc(LPVOID lpVoid)
{
	
	Sock* sock = static_cast<Sock*>(lpVoid);
	sock->RecvType(sock);

	return false;

}
bool Sock::Send(char* data, int len)
{
	int retval{};
	// sending data(fixed)
	retval = send(*iters, (char*)&len, sizeof(len), 0);
	if (SOCKET_ERROR == retval) {
		err_display("[에러] 위치 : Sock::Send, 이유 : send() 함수 실패");
		return false;
	}
	// sending data(flexible)
	retval = send(*iters, data, len, 0);
	if (SOCKET_ERROR == retval) {
		err_display("[에러] 위치 : Sock::Send, 이유 : send() 함수 실패");
		return false;
	}

	else if (0 == retval) {
		err_display("[에러] 위치 : Sock::Send, 이유 : 연결 종료");
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
		err_display("[에러] 위치 : Sock::RecvType, 이유 : Recvn() 함수 실패");
		return false;
	}
	else if (0 == retval) {
		err_display("[에러] 위치 : Sock::RecvType, 이유 : 연결 종료");
		return false;
	}

	if (ENROLL == datatype) {
		User user;
		sock->Recv((char*)&user, sizeof(user), 0);
		return true;
	}
	return true;
}

std::vector<User>* Sock::GetUserlist()
{
	return &userlist;

}
bool Sock::Recv(char* data, int len, int flags)
{

	int retval{};
	// receive data(fixed)
	retval = Recvn((char*)&len, sizeof(len), flags);
	if (SOCKET_ERROR == retval)
	{
		err_display("[에러] 위치 : Sock::Recv, 이유 : Recvn() 함수 실패");
		return false;
	}
	else if (0 == retval) {
		err_display("[에러] 위치 : Sock::Recv, 이유 : 연결 종료");
		return false;
	}
	// received data(flexible)
	retval = Recvn(data, len, flags);
	if (SOCKET_ERROR == retval)
	{
		err_display("[에러] 위치 : Sock::Recv, 이유 : Recvn() 함수 실패");
		return false;
	}

	else if (0 == retval) {
		err_display("[에러] 위치 : Sock::Recv, 이유 : 연결 종료");
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
