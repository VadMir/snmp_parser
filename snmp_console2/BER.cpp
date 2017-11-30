


#include "stdafx.h"

BER::BER(unsigned char* el,string tab) {
	t= "\t"+tab;
	type = *el;
	length = *(el + 1);
	len_offset = 1;
	if (length > 127) {
		len_offset = length - 127;
		unsigned char* i = new unsigned char[sizeof(int)];
		memset(i, 0, sizeof(int));
		memcpy(i, el, len_offset);
		reverse(i, i + len_offset);
		length = *(int*)i;
	}


	switch (*el) {
	case 0x02: 
	{
		unsigned char* i = new unsigned char[sizeof(int)];
		memset(i, 0, sizeof(int));
		memcpy(i, el+ len_offset+1, length);
		reverse(i, i + length);
		int in = (*(int*)i);
		value = &in;
		
		delete i;
		//cout << t << "INTEGER	" << *(int*)value<< endl ;
		break;
	}
	case 0x04:  
	{
		value = (unsigned char*)malloc((length + 2)* sizeof(unsigned char));
		memset(value, 0, length + 2);
		memcpy(value, el+ len_offset+1, length);
		//cout << t << "OCTET STRING	" << (unsigned char*)value<<endl;
		break;
	}
	case 0x06: //cout << tab << "OBJECT IDENTIFIER" << endl << tab;
	{
		value = (unsigned char*)malloc((length ) * sizeof(unsigned char));
		memset(value, 0, length);
		memcpy(value, el+ len_offset+1, length);
		/*cout << t << "OBJECT IDENTIFIER	";
		for (ptrdiff_t i = 0; i < length; i++)
		{
			if ((short)*((unsigned char*)value + i) == 0x2b) {
					cout <<  "1.3.";
			}
			else {
					cout << (short)*((unsigned char*)value + i) << ".";
			}
		}
		cout << endl;*/
		break; 
	}
	case 0x05: //cout << tab << "NULL"; 
		value = NULL;
		break;
	case 0x30: //cout << tab << "SEQUENCE";
	{
		//cout <<t<< "SEQUENCE			" << count << endl;

		count= ber_sequence_parse(el + len_offset+1,length,value,t);
		//cout <<t<< "SEQUENCE			" << count << endl;
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
		//cout << t << "RESPONSE			" << count << endl;
	//	count = ber_sequence_parse(el + len_offset + 1, length, value,t);
		//cout << t << "RESPONSE			" << count << endl;
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
void BER::CLEAN() {
	
}

BER::~BER()
{
	if ((type == 0x30)&&(type == 0xA2)) {
		for (size_t i = 0; i < count; i++)
		{
			((BER*)value + i)->~BER();
		}
		free(value);
	}
	delete value;
}
