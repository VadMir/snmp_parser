#pragma once
#include <string>

 class BER {
 public:
	 BER(unsigned char* el,std::string t);
	 ~BER();
	 void CLEAN();

	 unsigned char type;
	 unsigned length;
	 void* value;
	 short len_offset;
	 short count;

	 std::string t;

};

