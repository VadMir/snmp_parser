#pragma once
#include <string>
#include <memory>
#include <vector>

#define BER_INTEGER				0xA0;
#define BER_OCTET_STRING		0xA0;
#define BER_OBJECT_IDENTIFIER	0xA0;
#define BER_NULL				0xA0;
#define BER_SEQUENCE			0xA0;
#define BER_OBJECT_IDENTIFIER	0xA0;
#define BER_INTEGER				0xA0;
#define BER_OCTET_STRING		0xA0;
#define BER_OBJECT_IDENTIFIER	0xA0;
#define BER_INTEGER		0xA0;
#define GETNEXTREQUEST	0xA1;
#define RESPONSE		0xA2;
#define SETREQUEST		0xA3;
#define GETBULKREQUEST	0xA5;
#define INFORMREQUEST	0xA6;
#define TRAP			0xA7;
#define REPORT			0xA8;

 class BER {
 public:
	 BER(unsigned char* el,short t);
	 ~BER();
	 

	 unsigned char type;
	 unsigned length;
	 short len_offset;
	 short count;

	 short level;

	 std::vector<std::shared_ptr<BER>> value_arr;
	 std::vector<unsigned char> value_oid;
	 uint32_t value_int;
	 std::string value_str;

 };

