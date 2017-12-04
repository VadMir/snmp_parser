#pragma once
#include <string>
#include <memory>
#include <vector>
enum ber_type {
	BER_INTEGER	=			0x02,
	BER_OCTET_STRING=		0x04,
	BER_OBJECT_IDENTIFIER = 0x06,
	BER_NULL =				0x05,
	BER_SEQUENCE =			0x30,
	BER_IP_ADDRESS =		0x40,
	BER_COUNTER =			0x41,
	BER_GAUGE =				0x42,
	BER_TIMETICKS =			0x43
};
enum pdu_type {
	GETNEXTREQUEST = 0xA1,
	RESPONSE = 0xA2,
	SETREQUEST = 0xA3,
	GETBULKREQUEST = 0xA5,
	INFORMREQUEST = 0xA6,
	TRAP = 0xA7,
	REPORT = 0xA8
};
 class BER {
 public:
	 BER();
	 BER(unsigned char* el, short t);
	 ~BER();
	 

	 ber_type type;
	 unsigned length;
	 short len_offset;
	 short count;

	 short level;

	 std::vector<std::shared_ptr<BER>> value_arr;
	 std::vector<unsigned char> value_oid;
	 uint32_t value_int;
	 std::string value_str;

 };

