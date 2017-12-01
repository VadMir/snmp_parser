


#include "stdafx.h"

BER::BER(unsigned char* el,short lev) {
	level= 1+lev;
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
		//std::shared_ptr<unsigned char> i =std::shared_ptr<unsigned char>(new unsigned char[sizeof(int)]);
		unsigned char* i= new unsigned char[sizeof(int)];
		memset(i, 0, sizeof(int));
		memcpy(i, el+ len_offset+1, length);
		reverse(i, i + length);
		value_int = (*(int*)i);
		//value =unique_ptr<void>(in);
		
		delete i;
		//cout << t << "INTEGER	" << *(int*)value<< endl ;
		break;
	}
	case 0x04:  
	{
		unsigned char* value = (unsigned char*)malloc((length + 2)* sizeof(unsigned char));
		memset(value, 0, length + 2);
		memcpy(value, el+ len_offset+1, length);
		value_str=string( reinterpret_cast<char*>(value));
		//cout << t << "OCTET STRING	" << (unsigned char*)value<<endl;
		free(value);
		break;
	}
	case 0x06: //cout << tab << "OBJECT IDENTIFIER" << endl << tab;
	{
		//value = (unsigned char*)malloc((length ) * sizeof(unsigned char));
		//memset(value, 0, length);
		//memcpy(value, el+ len_offset+1, length);
		/*cout << t << "OBJECT IDENTIFIER	";*/
		for (ptrdiff_t i = 0; i < length; i++)
		{
			short sh = (short)*((unsigned char*)el + len_offset + 1 + i);
			if ( sh== 0x2b) {
					cout <<  "1.3.";
			}
			else {
					cout <<hex<< sh << ".";
			}
			value_oid.push_back(sh);


		}
		cout << endl;
		break; 
	}
	case 0x05: //cout << tab << "NULL"; 
		value_int = 0;
		break;
	case 0x30: //cout << tab << "SEQUENCE";
	{
		//cout <<t<< "SEQUENCE			" << count << endl;

		count= ber_sequence_parse(el + len_offset+1,length,value_arr,level);
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


BER::~BER()
{
	
}
