#ifdef __linux__

#include "libAdLinux.h"

#include <stdint.h>
#include <iostream>
#include <string>
#include <stdlib.h>

#define LDAP_DEPRECATED 1 // Enable deprecated
#include <ldap.h>

int authLinux(
	char *username,
	char *password,
	char *host,
	char *domain,
	int  *port
) {
	#ifdef DEBUG
		std::cout << "Auth running in adAdapterLinux.cpp" << std::endl;
		std::cout << "DEBUG>> On Linux, only simple is suppored over port 389" << std::endl;
		std::cout << "DEBUG>> Provided port number (if any) has been disregarded and using default (=389)" << std::endl;
	#endif
	
	// LDAP Handler
	LDAP *ld;
	
	// Handler initialisation
	std::string _server = std::string("ldap://") + host;  // <username>@<domain>
	char* SERVER = strdup(_server.c_str());  // cast std::string -> char*

	int status = ldap_initialize(&ld, SERVER);
	if (status != LDAP_SUCCESS) {
		std::cerr << "Error Code = " << status << " Message = " << ldap_err2string(status) << std::endl;
	}
	int version(LDAP_VERSION3);
	ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &version);

	// Interpolate username + domain into a DN username
	std::string _DN = username + std::string("@") + domain;  // <username>@<domain>
	char* DN = strdup(_DN.c_str());

	// Execute bind
	// int res = ldap_sasl_bind_s(ld, DN, LDAP_SASL_AUTOMATIC, &credentials, NULL, NULL, NULL);  // SASL [NOK]
	// int res = ldap_gssapi_bind_s(ldapHandler, DN, pw); // GSSAPI [NOK]
	/*
		LDAP_F( int )
		ldap_simple_bind_s LDAP_P((
			LDAP *ld,
			LDAP_CONST char *who,
			LDAP_CONST char *passwd ));
	*/
	int res = ldap_simple_bind_s(ld, DN, password);  // [deprecated - OK]
	if(res != LDAP_SUCCESS) {
		std::cerr << "Bind failed. Error Code: " << res << " | Message: " << ldap_err2string(res) << std::endl;
	} else {
		std::cout << "Bind success !" << std::endl;
	}
    return res;
}

#endif
