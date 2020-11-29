#include "include/libAdWindows.hpp"

#include <iostream>
#include <Windows.h>
#include <winldap.h>
#include <stdlib.h>
#include <string>
#include <sstream>

#include <memory>
#include <stdexcept>

wchar_t *convertCharArrayToLPCWSTR(char *charArray)
{
	wchar_t *wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
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

	if (!port) {  // NOT nullptr
		port = new int;		// allocate memory, because port points to NULL
		*port = LDAP_PORT;	// assign default value
	}

	// Initialise & Open LDAP Connection
	LDAP *ld = ldap_init(convertCharArrayToLPCWSTR(host), *port);  // ld is the LDAP connection
	LDAP_TIMEVAL connTimeout = { 5, 0 }; // 5sec 0ms timeout for LDAP connection
	ULONG conn = ldap_connect(ld, &connTimeout);
	if (conn == LDAP_SUCCESS) {
		#ifdef DEBUG
				std::cout << "Successful connection to LDAP server..." << std::endl;
		#endif // DEBUG
	}
	else {
		char hexString[20];
		std::cerr << "Failed to connect to LDAP. Error: " << conn << " Hex: " << hexString << std::endl;
		return conn;
	}

	// Interpolate username + domain into a DN username
	std::string _DN = username + std::string("@") + domain;
	char *DN = _strdup(_DN.c_str());

	// Bind As User
	ULONG bind = ldap_simple_bind_s(
		ld,
		convertCharArrayToLPCWSTR(DN), // <username>@<domain>
		convertCharArrayToLPCWSTR(password) // Password
	);

	switch(bind)
	{
	case LDAP_SUCCESS:
		#ifdef DEBUG
			std::cout << "Successful BIND to LDAP server..." << std::endl;
		#endif // DEBUG
		break;
	case LDAP_INVALID_CREDENTIALS:
		std::cout << "Invalid Credentials..." << std::endl;
		break;
	default:
		char hexString[20];
		_itoa_s(bind, hexString, 20);
		std::cerr << "Failed to BIND to LDAP. Error: " << bind << " Hex: " << hexString << std::endl;
		break;
	}
	ldap_unbind(ld);  //terminate the LDAP session 

	return (int)bind;
}
