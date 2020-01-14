/*
	DEVELOPMENT-ONLY FILE
*/
#ifdef __linux__

#include <iostream>
#include "libAdLinux.hpp"

int main()
{
	// Credentials provided directly in source file during development
	// Cast const char * -> char *
	auto username = (char*)"************";
	auto password = (char*)"************";
	auto host     = (char*)"************";
	auto domain   = (char*)"************";

	int auth = authLinux(username, password, host, domain, 0);
    	
    return auth;
}
#endif
