#pragma once
struct User {
	char* id = nullptr;
	char* nickname = nullptr;
	char* pwd = nullptr;
	int num = 0;
	SOCKET sock = INVALID_SOCKET;

};
struct UserS {
	char* id = nullptr;
	char* pwd = nullptr;
	int num = 0;
	SOCKET sock = INVALID_SOCKET;
};