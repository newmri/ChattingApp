#include "mysql.h"
#include <iostream>
using namespace std;
bool Mysql::Init(void)
{
	// DB 연결
	mysql_init(&mysql);
	if (!mysql_real_connect(&mysql, DB_ADDRESS, DB_ID, DB_PASS, DB_NAME, 3306, 0, 0)) {
		cout << "db 접속 실패" << endl;
		return false;
	}
	return true;


}

bool Mysql::Enroll(void)
{
	// 유저 가입
	char Query[600]{};
	int Query_Status{};

	sprintf_s(Query, "insert into chattingdb.userinfo values ('%s','%s','%s')",user.id, user.pwd, user.nickname);
			
	Query_Status = mysql_query(&mysql, Query);
	if (Query_Status){
	cout <<"ID: "<<user.id<<" 회원 가입 실패" << endl;
	return false;
	}
	cout << "ID: " << user.id << " 가입 성공" << endl;
	return true;
	

}
bool Mysql::Secession(void)
{
	char Query[256]{};
	int Query_Status{};

	sprintf_s(Query, "delete from chattingdb.userinfo where ID = '%s' and PWD = 's' ", users.id, users.pwd);
	Query_Status = mysql_query(&mysql, Query);
	if (Query_Status){
		cout << "ID: " << users.id << " 회원 탈퇴 실패" << endl;
		return false;
	}
	cout << "ID: " << users.id << " 탈퇴 성공" << endl;
	return true;

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