


#include "stdafx.h"

BER::BER(unsigned char* el) {
	type = *el;
	length = *(el + 1);
	if (length > 127) {
		short lb = length - 127;
		unsigned char* t = new unsigned char[sizeof(int)];
		memset(t, 0, sizeof(int));
		memcpy(t, el, lb);
		reverse(t, t + lb);
		length = *(int*)t;
	}

}

BER::~BER()
{
}
