/*
	DEVELOPMENT-ONLY FILE
*/
#include <iostream>
#include "include/libAdWindows.hpp"

int main()
{
	// Credentials provided directly in source file during development
	// Cast const char * -> char *
	auto username = (char *)"************";
	auto password = (char *)"************";
	auto host = (char *)"****************";
	auto domain = (char *)"**************";
	auto port = 389;

	int res = auth(username, password, host, domain, &port);

	return res;
}