#include "mysql.h"
#include <iostream>
using namespace std;
bool Mysql::Init(void)
{
	// DB ����
	mysql_init(&mysql);
	if (!mysql_real_connect(&mysql, DB_ADDRESS, DB_ID, DB_PASS, DB_NAME, 3306, 0, 0)) {
		cout << "db ���� ����" << endl;
		return false;
	}
	return true;


}

bool Mysql::Enroll(void)
{
	// ���� ����
	char Query[600]{};
	int Query_Status{};

	sprintf_s(Query, "insert into chattingdb.userinfo values ('%s','%s','%s')",user.id, user.pwd, user.nickname);
			
	Query_Status = mysql_query(&mysql, Query);
	if (Query_Status){
	cout <<"ID: "<<user.id<<" ȸ�� ���� ����" << endl;
	return false;
	}
	cout << "ID: " << user.id << " ���� ����" << endl;
	return true;
	

}
bool Mysql::Secession(void)
{
	char Query[256]{};
	int Query_Status{};

	sprintf_s(Query, "delete from chattingdb.userinfo where ID = '%s' and PWD = 's' ", users.id, users.pwd);
	Query_Status = mysql_query(&mysql, Query);
	if (Query_Status){
		cout << "ID: " << users.id << " ȸ�� Ż�� ����" << endl;
		return false;
	}
	cout << "ID: " << users.id << " Ż�� ����" << endl;
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