#define SOEXPORT extern "C"

#ifdef __APPLE__

#include <stdint.h>

int authDarwin(
	char *username,
	char *password,
	char *host,
	char *domain,
	int *port
);

SOEXPORT int auth(char *username, char *password, char *host, char *domain, int *port);

#endif
