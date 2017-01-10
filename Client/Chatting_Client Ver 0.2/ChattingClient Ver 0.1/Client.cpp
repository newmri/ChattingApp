#include "Client.h"
#include<iostream>
Sock::Sock(void) : sock(), serveraddr() {}
Sock::~Sock()
{
	WSACleanup();
}

bool Sock::Init(void)
{
	WSADATA wsa;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsa)) {
		err_quit("[에러] 위치 : Sock::Init, 이유 : WSAStartup() 함수 실패");
		return false;
	}
	
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
	serveraddr.sin_port = htons(SERVERPORT);
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sock) {
		err_quit("[에러] 위치 : Sock::Init, 이유 : socket() 함수 실패");
		return false;
	}
	return true;
}
bool Sock::setHandle(HANDLE hWnd)
{
	m_hWnd = hWnd;
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

bool Sock::Connect(void)
{
	int retval{};
	retval = connect(sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (SOCKET_ERROR==retval){
		err_quit("[에러] 위치 : Sock::Connect, 이유 : connect() 함수 실패");
		return false;
	}
	return true;
	
		

}
int& Sock::getNum(void)
{
	return num;
}
SOCKET& Sock::getSocket(void)
{
	return sock;
}
User& Sock::getUser(void)
{
	return user;
}
bool Sock::SendType(int datatype)
{
	int retval{};
	// sending data(fixed)
	retval = send(sock, (char*)&datatype, sizeof(datatype), 0);
	if (SOCKET_ERROR == retval) {
		err_display("[에러] 위치 : Sock::SendType, 이유 : send() 함수 실패");
		return false;
	}

	return true;


}

bool Sock::Send(char* data, int len)
{
	int retval{};
	 // sending data(flexible)
	retval = send(sock,data, len, 0);
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
bool Sock::Recv(char* data, int len, int flags)
{
	int retval{};


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
	while (left > 0)
	{
		received = recv(sock, ptr, left, flags);
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
bool Sock::CheckEnroll(void)
{
	if (_tcslen(user.id) == 0 || _tcslen(user.pwd) == 0 || _tcslen(user.nickname) == 0)
	{
		MessageBox(NULL,_T("회원가입에 필요한 항목 중 기입하지 않은 항목이 있습니다."), _T("회원가입 실패"),0);
		return false;
	}
	else if (_tcslen(user.id) < 2 || _tcslen(user.pwd) < 2 || _tcslen(user.nickname) < 2)
	{
		MessageBox(NULL,_T("아이디, 비밀번호, 별명은 2자 이상으로 기입해주세요."), _T("회원가입 실패"),0);
		return 0;
	}
	else if (_tcslen(user.id) > 10 || _tcslen(user.pwd) > 10 || _tcslen(user.nickname) > 10)
	{
		MessageBox(NULL,_T("아이디, 비밀번호, 별명은 최대 10자 까지 가능합니다."), _T("회원가입 실패"),0);
		return 0;
	}


	else return true;

}