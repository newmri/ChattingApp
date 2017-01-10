#pragma once
#pragma comment(lib, "libmysql.lib")
#include "stdafx.h"
#include <WinSock2.h>
#include <mysql.h>
#include "UserInfo.h"
#include <afxsock.h>



#define MAX_STRINGLEN 10
#define DB_ADDRESS "localhost"
#define DB_ID "root"
#define DB_PASS "a123123"
#define DB_NAME "chattingdb"
class Mysql
{
private:
	User user;
	UserS users;
	MYSQL_ROW row;		// mysql �� ���� �ô´�.
	MYSQL_RES *m_res;	// mysql�� ����� �޾ƿ´�
	MYSQL mysql;		// mysql�� ��ü���� ������ ����Ѵ�.
public:
	bool Init(void);
	bool Enroll(void);
	bool Secession(void);
	bool Login(void);
	void SetUser(User&);
	void SetUserS(UserS&);
	char* GetUserNickName(void);

};