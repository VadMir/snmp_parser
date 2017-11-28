#pragma once


 class BER {
 public:
	 BER(unsigned char* el);
	 ~BER();
	 
	 unsigned char type;
	 unsigned length;
	 void* value;

};

