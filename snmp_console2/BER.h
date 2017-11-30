#pragma once


 class BER {
 public:
	 BER(unsigned char* el);
	 ~BER();
	 void CLEAN();

	 unsigned char type;
	 unsigned length;
	 void* value;
	 short len_offset;
	 short count;

};

