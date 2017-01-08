#pragma
#define MAX_STRINGLEN 10
// 가입 하기 위한 유저 정보
struct User {
	int type;
	char id[MAX_STRINGLEN];
	char nickname[MAX_STRINGLEN];
	char pwd[MAX_STRINGLEN];
};
// 로그인 및 탈퇴 위한 유저 정보
struct UserS {
	int type;
	char id[MAX_STRINGLEN];
	char pwd[MAX_STRINGLEN];
};