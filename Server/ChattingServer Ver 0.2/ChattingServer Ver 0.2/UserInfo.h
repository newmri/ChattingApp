#pragma
#define MAX_STRINGLEN 10
// ���� �ϱ� ���� ���� ����
struct User {
	int type;
	char id[MAX_STRINGLEN];
	char nickname[MAX_STRINGLEN];
	char pwd[MAX_STRINGLEN];
};
// �α��� �� Ż�� ���� ���� ����
struct UserS {
	int type;
	char id[MAX_STRINGLEN];
	char pwd[MAX_STRINGLEN];
};