#include "mysql.h"
#include <iostream>
using namespace std;
bool Mysql::Init(void)
{
	//// DB 연결
	mysql_init(&mysql);
	if (!mysql_real_connect(&mysql, DB_ADDRESS, DB_ID, DB_PASS, DB_NAME, 3306, 0, 0)) {
		cout << "db 접속 실패" << endl;
		return false;
	}
	return true;


}