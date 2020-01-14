#define DLLEXPORT extern "C" __declspec(dllexport)

#ifdef _WIN32

#pragma once


int authWindows(
	char *username,
	char *password,
	char *host,
	char *domain,
	int  *port
);

DLLEXPORT int auth(char *username, char *password, char *host, char *domain, int *port);

#endif
