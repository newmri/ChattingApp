#include "mysql.h"
#include <iostream>
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

using namespace std;
bool Mysql::Init(void)
{
	// DB 연결
	mysql_init(&mysql);
	if (!mysql_real_connect(&mysql, DB_ADDRESS, DB_ID, DB_PASS, DB_NAME, 3306, 0, 0)) {
		return false;
	}
	else return true;


}

bool Mysql::Enroll(void)
{
	// 유저 가입
	Init();
	char Query[600]{};
	int Query_Status{};
	sprintf_s(Query, "insert into chattingdb.userinfo values ('%s','%s','%s')", user.id, user.pwd, user.nickname);
	
	Query_Status = mysql_query(&mysql, Query);
	if (Query_Status) {
		cout << mysql_error(&mysql) << endl;
		return false;
	}
	
	else return true;


}
bool Mysql::Secession(void)
{
	Init();
	char Query[256]{};
	int Query_Status{};

	sprintf_s(Query, "select* from chattingdb.userinfo where ID = '%s' and PWD = '%s' ", users.id, users.pwd);
	Query_Status = mysql_query(&mysql, Query);

	m_res = mysql_use_result(&mysql);
	row = mysql_fetch_row(m_res);

	Init();

	sprintf_s(Query, "delete from chattingdb.userinfo where ID = '%s' and PWD = '%s' ", users.id, users.pwd);
	Query_Status = mysql_query(&mysql, Query);

	

	if (m_res->row_count) return true;
	else return false;
	
}

bool Mysql::Login(void)
{
	Init();
	char Query[256]{};
	int Query_Status{};

	sprintf_s(Query, "select* from chattingdb.userinfo where ID = '%s' and PWD = '%s' ", users.id, users.pwd);
	Query_Status = mysql_query(&mysql, Query);
	
	m_res = mysql_use_result(&mysql);
	row = mysql_fetch_row(m_res);

	if (m_res->row_count) return true;
	else return false;

}
void Mysql::SetUser(User& other)
{
	memcpy(&user, &other, sizeof(User));
	return;
}

void Mysql::SetUserS(UserS& other)
{
	memcpy(&users, &other, sizeof(UserS));
	return;

}

char* Mysql::GetUserNickName(void)
{
	Init();
	char Query[256]{};
	int Query_Status{};
	sprintf_s(Query, "select NickName from chattingdb.userinfo where ID = '%s' ", users.id);
	Query_Status = mysql_query(&mysql, Query);

	m_res = mysql_use_result(&mysql);
	row = mysql_fetch_row(m_res);

	char* nickname = "a";
	return nickname;


}