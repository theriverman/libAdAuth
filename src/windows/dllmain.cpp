// dllmain.cpp : Defines the entry point for the DLL application.

#ifdef _WIN32

#include "include/stdafx.hpp"
#include "include/libAdWindows.hpp"
#include <iostream>

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

#ifdef DEBUG
DLLEXPORT int foo() {
	std::cout << "Hello from foo()" << std::endl;
	return 0;
}
#endif // DEBUG


DLLEXPORT int auth(char *username, char *password, char *host, char *domain, int *port) {
	return authWindows(username, password, host, domain, port);
}
#endif
