#ifdef __linux__

#include <iostream>
#include "include/libAdLinux.h"


#ifdef DEBUG
SOEXPORT int foo() {
	std::cout << "Hello from foo()" << std::endl;
	return 0;
}
#endif // DEBUG


SOEXPORT int auth(char *username, char *password, char *host, char *domain, int *port) {
	return authLinux(username, password, host, domain, port);
}

#endif
