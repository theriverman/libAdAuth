#define SOEXPORT extern "C"

#ifdef __linux__

#include <stdint.h>

int authLinux(
	char *username,
	char *password,
	char *host,
	char *domain,
	int *port
);

SOEXPORT int auth(char *username, char *password, char *host, char *domain, int *port);

#endif
