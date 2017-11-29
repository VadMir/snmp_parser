


#include "stdafx.h"

BER::BER(unsigned char* el) {
	type = *el;
	length = *(el + 1);
	len_offset = 1;
	if (length > 127) {
		len_offset = length - 127;
		unsigned char* t = new unsigned char[sizeof(int)];
		memset(t, 0, sizeof(int));
		memcpy(t, el, len_offset);
		reverse(t, t + len_offset);
		length = *(int*)t;
	}


	switch (*el) {
	case 0x02: //cout << tab << "INTEGER" << endl << tab;
	{
		unsigned char* t = new unsigned char[sizeof(int)];
		memset(t, 0, sizeof(int));
		memcpy(t, el+ len_offset+1, length);
		reverse(t, t + length);
		int i = (*(int*)t);
		value = &i;
		//value = (void*)t;
		//cout << (*(int*)t);
		delete t;
		break;
	}
	case 0x04: //cout << tab << "OCTET STRING" << endl << tab; 
	{
		value = new unsigned char[length + 2];
		memset(value, 0, length + 2);
		memcpy(value, el+ len_offset+1, length);
		//	cout << t; 
		//value = (void*)t;
		//delete t;
		break;
	}
	case 0x06: //cout << tab << "OBJECT IDENTIFIER" << endl << tab;
	{
		unsigned char* t = new unsigned char[length];
		memset(t, 0, length);
		memcpy(t, el+ len_offset+1, length);
	/*	for (ptrdiff_t i = 0; i < length; i++)
		{
			if ((short)*(t + i) == 0x2b) {
				//	cout <<  "1.3.";
			}
			else {
				//	cout << (short)*(t + i) << ".";
			}
		}*/
		value = t;
		delete t;
		break; 
	}
	case 0x05: //cout << tab << "NULL"; 
		value = NULL;
		break;
	case 0x30: //cout << tab << "SEQUENCE";
	{
		ber_sequence_parse(el + len_offset+1,length,value);
		break;

		
	}
	case 0x40: //cout << tab << "IP ADDRESS"; 
		break;
	case 0x41: //cout << tab << "COUNTER"; 
		break;
	case 0x42: //cout << tab << "GAUGE"; 
		break;
	case 0x43: //cout << tab << "TIMETICKS";
		break;

	case 0xA0: //cout << tab << "GetRequest"; 
		break;
	case 0xA1: //cout << tab << "GetNextRequest";
		break;
	case 0xA2: //cout << tab << "Response";
		break;
	case 0xA3: //cout << tab << "SetRequest"; 
		break;
	case 0xA5: //cout << tab << "GetBulkRequest";
		break;
	case 0xA6:// cout << tab << "InformRequest";
		break;
	case 0xA7:// cout << tab << "Trap "; 
		break;
	case 0xA8: //cout << tab << "Report";
		break;

	default:// cout << tab << "UNKNOWN"; 
		break;
	}

}

BER::~BER()
{
	delete value;
}
