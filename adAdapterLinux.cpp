#ifdef __linux__

#include "libAdLinux.h"

#include <stdint.h>
#include <iostream>
#include <string>
#include <stdlib.h>

#include <ldap.h>

int authLinux(
	char *username,
	char *password,
	char *host,
	char *domain,
	int  *port
) {
	#ifdef DEBUG
	std::cout << "(DEBUG) Provided port number (if any) has been disregarded and using default (=389)" << std::endl;
	#endif
	
	// Declarations
	int conn_status, version(LDAP_VERSION3), bind, unbind;
	char *server;

	// LDAP Handler
	LDAP *ld;
	
	// Handler initialisation
	server = strdup(std::string("ldap://").append(host).c_str()); // Adds `ldap://` prefix to host
	conn_status = ldap_initialize(&ld, server);
	if (conn_status != LDAP_SUCCESS) {
		std::cerr << "Error Code = " << conn_status << " Message = " << ldap_err2string(conn_status) << std::endl;
	}
	ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &version);

	// Append domain to username
	username = strdup((std::string(username).append("@").append(domain)).c_str());  // <sAMAccountName>@<domain>

	// Execute bind
	berval credentials;
	berval *srv = NULL;
	credentials.bv_val = password;
	credentials.bv_len = strlen(password);

	bind = ldap_sasl_bind_s(
        ld,
        username, // DN ==>    <sAMAccountName>@<domain>
        LDAP_SASL_SIMPLE,
        &credentials,
        NULL,
        NULL,
        &srv
	);

	if (bind != LDAP_SUCCESS) {
		std::cerr << "Bind failed. Error Code: " << bind << " | Message: " << ldap_err2string(bind) << std::endl;
		return bind;
	} else {
		#ifdef DEBUG
		std::cout << "Bind success !" << std::endl;
		#endif
	}

	// Unbind
	unbind = ldap_unbind_ext_s(ld, NULL, NULL);
	if (unbind != LDAP_SUCCESS) {
		std::cerr << "Unbind failed. Error Code: " << unbind << " | Message: " << ldap_err2string(bind) << std::endl;
	} else {
		#ifdef DEBUG
		std::cout << "Unbind success !" << std::endl;
		#endif
	}
    return bind;
}

#endif
