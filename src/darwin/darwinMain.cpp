/*
	DEVELOPMENT-ONLY FILE
*/
#ifdef __APPLE__

#include <iostream>
#include "libAdDarwin.hpp"

int main()
{
  // Credentials provided directly in source file during development
  // Cast const char * -> char *

  auto username = (char *)"************";
  auto password = (char *)"************";
  auto host = (char *)"****************";
  auto domain = (char *)"**************";
  auto port = 389;

  int auth = authDarwin(username, password, host, domain, &port);
  return auth;
}
#endif
