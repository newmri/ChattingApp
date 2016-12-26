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
	MYSQL_ROW row;		// mysql 의 행을 맡는다.
	MYSQL_RES *m_res;	// mysql의 결과를 받아온다
	MYSQL mysql;		// mysql의 전체적인 연동을 담당한다.
public:
	bool Init(void);
	bool Enroll(void);


};