#include "Client.h"

ClientSocket::ClientSocket(SOCKET sock) :mSock(sock) {}
ClientSocket::~ClientSocket()
{
	Close();
}

bool ClientSocket::Create()
{
	if (IsValid() == true)
		return true;

	mSock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	return mSock != INVALID_SOCKET;
}

void ClientSocket::Close()
{
	if (IsValid() == true)
	{
		::closesocket(mSock);
		mSock = INVALID_SOCKET;
	}
}

bool ClientSocket::Connect(const char *ip, unsigned short port)
{
	if (IsValid() == false)
		return false;

	sockaddr_in addr{ 0 };

//	addr.sin_addr.S_un.S_addr = inet_addr(ip);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);

	int ret = ::connect(mSock, (sockaddr*)&addr, sizeof(addr));

	if (ret == SOCKET_ERROR)
		Close();

	return ret != SOCKET_ERROR;
}

int ClientSocket::Send(const char* buf, int size)
{
	if (IsValid() == false)
		return SOCKET_ERROR;

	return ::send(mSock, buf, size, 0);
}

int ClientSocket::Recv(char *buf, int size)
{
	if (IsValid() == false)
		return SOCKET_ERROR;

	return ::recv(mSock, buf, size, 0);
}
