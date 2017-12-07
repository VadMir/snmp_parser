#pragma once
#ifndef MODULE_H
#define MODULE_H

#include <memory>


#include <prefs\prefs.h>

#include <stdio.h>
#include <memory>
#include "BER.h"
#include "SNMP_PDU.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
// TODO: reference additional headers your program requires here







class module
	// : msw::noncopyable
{
public:
	module();
	~module();
	bool session_data(guint8 const* in_buf, size_t in_len, guint8** out_buf, size_t* out_len);
	void restart(char*, char*);
	//gconstpchar (MSCU_CALL_PREFIX * TPref_validator)
	static	TPref_validator OID_validator(preference_p preference, gint action);
	TPref_validator(__cdecl * validator)(preference_p, gint);// = module::OID_validator;

															 //  std::unique_ptr<core> core_;
	char OID[PREFS_MAX_PATH];
	char VALUE[PREFS_MAX_PATH];
private:
};

#endif