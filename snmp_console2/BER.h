#pragma once
#include <string>
#include <memory>
#include <vector>

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

