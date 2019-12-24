/*
	DEVELOPMENT-ONLY FILE
*/
#include <iostream>
#include "libAdWindows.h"

int main()
{
	// Credentials provided directly in source file during development
	// Cast const char * -> char *
	auto username = (char*)"************";
	auto password = (char*)"************";
	auto host     = (char*)"************";
	auto domain   = (char*)"************";

	int res = auth(username, password, host, domain, 0);

	return res;
}
