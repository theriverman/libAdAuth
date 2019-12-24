/*
	DEVELOPMENT-ONLY FILE
*/
#ifdef __linux__

#include <iostream>

#define LDAP_DEPRECATED 1 // Enable deprecated
#include <ldap.h>

int main()
{
	// Credentials provided directly in source file during development
	const char *dn = "************";
	const char *pw = "************";
	const char *hst = "********.uk";
	const char *dmn = "********.uk";

	// Cast const char * -> char *
	auto username = dn;
	auto password = (char*)pw;
	auto host = (char*)hst;
	auto domain = (char*)dmn;

	// LDAP Handler
	LDAP *ld;
	
	// Handler initialisation
	int status = ldap_initialize(&ld, "ldap://******.uk");
	if (status != LDAP_SUCCESS) {
		std::cout << "Error Code = " << status << " Message = " << ldap_err2string(status) << std::endl;
	}
	int version(LDAP_VERSION3);
	ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &version);

	// Execute bind
	// int res = ldap_sasl_bind_s(ld, dn, LDAP_SASL_AUTOMATIC, &credentials, NULL, NULL, NULL);  // SASL [NOK]
	// int res = ldap_gssapi_bind_s(ldapHandler, username, pw); // GSSAPI [NOK]
	/*
		LDAP_F( int )
		ldap_simple_bind_s LDAP_P((
			LDAP *ld,
			LDAP_CONST char *who,
			LDAP_CONST char *passwd ));
	*/
	int res = ldap_simple_bind_s(ld, dn, pw);  // [deprecated - OK]
	if(res != LDAP_SUCCESS) {
		std::cout << "Bind failed. Error Code: " << res << " | Message: " << ldap_err2string(res) << std::endl;
	} else {
		std::cout << "Bind success !" << std::endl;
	}
    	
    return 0;
}
#endif
