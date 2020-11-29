#ifdef __linux__

#include "include/libAdLinux.hpp"

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
	int *port)
{
#ifdef DEBUG
	std::cout << "(DEBUG :: libAdAuth) username = " << username << std::endl;
	std::cout << "(DEBUG :: libAdAuth) password[0] = " << password[0] << std::endl;
	std::cout << "(DEBUG :: libAdAuth) host = " << host << std::endl;
	std::cout << "(DEBUG :: libAdAuth) domain = " << domain << std::endl;
	std::cout << "(DEBUG :: libAdAuth) port = " << *port << std::endl;
#endif

	// Security Guards
	if (!username || !password || !host || !domain || *port == 0)
	{
		std::cerr << "Missing value(s): username, password, host, domain or port" << std::endl;
		return LDAP_OTHER;
	}

	// Declarations
	int conn_status, version(LDAP_VERSION3), bind, unbind;
	char *server;

	// LDAP Handler
	LDAP *ld;

	// Compile host address
	// Wraps host between ldap:// and :<port>
	server = strdup(std::string("ldap://")
						.append(host)
						.append(":")
						.append(std::to_string(*port))
						.c_str());

#ifdef DEBUG
	std::cout << "(DEBUG :: libAdAuth) server = " << server << std::endl;
#endif

	conn_status = ldap_initialize(&ld, server);
	delete server;
	if (conn_status != LDAP_SUCCESS)
	{
		std::cerr << "Error Code = " << conn_status << " Message = " << ldap_err2string(conn_status) << std::endl;
	}
	ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &version);

	// Append domain to username
	username = strdup((std::string(username).append("@").append(domain)).c_str()); // <sAMAccountName>@<domain>

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
		&srv);
	delete username;
	delete srv;

	if (bind != LDAP_SUCCESS)
	{
		std::cerr << "Bind failed. Error Code: " << bind << " | Message: " << ldap_err2string(bind) << std::endl;
		return bind;
	}
	else
	{
#ifdef DEBUG
		std::cout << "(DEBUG :: libAdAuth) Bind Success" << std::endl;
#endif
	}

	// Unbind
	unbind = ldap_unbind_ext_s(ld, NULL, NULL);
	if (unbind != LDAP_SUCCESS)
	{
		std::cerr << "Unbind failed. Error Code: " << unbind << " | Message: " << ldap_err2string(bind) << std::endl;
	}
	else
	{
#ifdef DEBUG
		std::cout << "(DEBUG :: libAdAuth) Unbind Success" << std::endl;
#endif
	}
	return bind;
}

#endif
