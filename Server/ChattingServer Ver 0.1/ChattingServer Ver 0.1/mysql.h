#pragma once
#include <WinSock2.h>
#include <mysql.h>
#include "User.h"
#pragma comment(lib,"libmysql.lib")

#define DB_ADDRESS "localhost"
#define DB_ID "root"
#define DB_PASS "a123123"
#define DB_NAME "chattingdb"

class Mysql
{
	User user;
	MYSQL_ROW row;		// mysql �� ���� �ô´�.
	MYSQL_RES *m_res;	// mysql�� ����� �޾ƿ´�
	MYSQL mysql;		// mysql�� ��ü���� ������ ����Ѵ�.
public:
	bool Init(void);
	bool Enroll(void);


};