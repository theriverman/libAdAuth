#include "include/libAdWindows.hpp"

#include <iostream>
#include <Windows.h>
#include <winldap.h>
#include <stdlib.h>
#include <string>
#include <sstream>

#include <memory>
#include <stdexcept>

wchar_t *charToLPCWSTR(char *charArray)
{
	wchar_t *s = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, s, 4096);
	return s;
}

int authWindows(
	char *username,
	char *password,
	char *host,
	char *domain,
	int *port
) {

#ifdef DEBUG
	std::cout << "(DEBUG :: libAdAuth) username = " << username << std::endl;
	std::cout << "(DEBUG :: libAdAuth) password[0] = " << password[0] << std::endl;
	std::cout << "(DEBUG :: libAdAuth) host = " << host << std::endl;
	std::cout << "(DEBUG :: libAdAuth) domain = " << domain << std::endl;
	std::cout << "(DEBUG :: libAdAuth) port = " << *port << std::endl;
#endif

	// Security Guards
	if (!username || !password || !host || !domain) {
		std::cerr << "Missing value: username, password, host or domain" << std::endl;
		return LDAP_OTHER;
	}

	// Initialise & Open LDAP Connection
	wchar_t *wHostName = charToLPCWSTR(host);
	LDAP *ld = ldap_init(wHostName, *port);  // ld is the LDAP connection
	LDAP_TIMEVAL connTimeout = { 5, 0 }; // 5sec 0ms timeout for LDAP connection
	ULONG conn = ldap_connect(ld, &connTimeout);
	delete wHostName;
	if (conn == LDAP_SUCCESS) {
#ifdef DEBUG
		std::cout << "(DEBUG :: libAdAuth) Successful connection to LDAP server..." << std::endl;
#endif // DEBUG
	}
	else {
		std::cerr << "libAdAuth > Failed to connect to LDAP. Error: " << conn << std::endl;
		return conn;
	}

	// Compile <username>@<domain> to be used for BIND
	char *DN = _strdup((username + std::string("@") + domain).c_str());

	// Bind As User
	wchar_t *wDN = charToLPCWSTR(DN);
	wchar_t *wPW = charToLPCWSTR(password);
	ULONG bind = ldap_simple_bind_s(
		ld,
		wDN, // <username>@<domain>
		wPW  // <password>
	);
	delete DN;
	delete wDN;
	delete wPW;

	switch (bind)
	{
	case LDAP_SUCCESS:
#ifdef DEBUG
		std::cout << "(DEBUG :: libAdAuth) Successful BIND to LDAP server..." << std::endl;
#endif // DEBUG
		break;
	case LDAP_INVALID_CREDENTIALS:
		std::cout << "libAdAuth > Invalid Credentials..." << std::endl;
		break;
	default:
		char hexString[20];
		_itoa_s(bind, hexString, 20);
		std::cerr << "libAdAuth > Failed to BIND to LDAP. Error: " << bind << " Hex: " << hexString << std::endl;
		break;
	}
	ldap_unbind(ld);  //terminate the LDAP session

	return (int)bind;
}
