/*
	DEVELOPMENT-ONLY FILE
*/
#include <iostream>
#include "libAdWindows.h"

int main()
{
	// Credentials provided directly in source file during development
	const char *dn = "************";
	const char *pw = "************";
	const char *hst = "***********";
	const char *dmn = "***********";

	// Cast const char * -> char *
	auto username = (char*)dn;
	auto password = (char*)pw;
	auto host = (char*)hst;
	auto domain = (char*)dmn;

	int res = auth(username, password, host, domain, 0);

	return res;
}
