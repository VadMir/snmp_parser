// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <memory>
#include <tchar.h>
#include "BER.h"
#include <iostream>
using namespace std;
// TODO: reference additional headers your program requires here
short ber_sequence_parse(unsigned char *el, int length,vector<shared_ptr<BER>> value,short tab);
std::string tab = "\t";