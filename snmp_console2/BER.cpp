


#include "stdafx.h"
BER::BER() {}
BER::BER(vector<unsigned char> el, short lev) {
	new BER(reinterpret_cast<unsigned char*>(el.data()), lev);
}
BER::BER(unsigned char* el,short lev) {
	level= 1+lev;
	type = (ber_type)*el;
	length = *(el + 1);
	len_offset = 1;
	if (length > 127) {
		len_offset = length - 127;
		unsigned char* i = new unsigned char[sizeof(int)];
		memset(i, 0, sizeof(int));
		memcpy(i, el+2, len_offset-1);
		//reverse(i, i + len_offset-1);
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
		cout  << "INTEGER	" << value_int<< endl ;
		break;
	}
	case 0x04:  
	{
		unsigned char* value = (unsigned char*)malloc((length + 2)* sizeof(unsigned char));
		memset(value, 0, length + 2);
		memcpy(value, el+ len_offset+1, length);
		value_str=string( reinterpret_cast<char*>(value));
		cout  << "OCTET STRING	" << (unsigned char*)value<<endl;
		free(value);
		break;
	}
	case 0x06: //cout << tab << "OBJECT IDENTIFIER" << endl << tab;
	{
		//value = (unsigned char*)malloc((length ) * sizeof(unsigned char));
		//memset(value, 0, length);
		//memcpy(value, el+ len_offset+1, length);
		cout << "OBJECT IDENTIFIER	"; count = 0;
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
			count++;


		}
		cout << endl;
		break; 
	}
	case 0x05: //cout << tab << "NULL"; 
		value_int = 0;
		break;
	case 0x30: //cout << tab << "SEQUENCE";
	{
		cout << "SEQUENCE			" << count << endl;

		count= ber_sequence_parse(el + len_offset+1,length,&value_arr,level);
		cout << "SEQUENCE			" << count << endl;
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
		count = ber_sequence_parse(el + len_offset + 1, length, &value_arr,level);
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
void BER::stamp_BER_length(vector<unsigned char>*vec, uint32_t len) {
	unsigned char* lch = reinterpret_cast<unsigned char*>(&len);

	if (len < 128) {
		vec->insert(vec->begin(), lch, lch + 1);
	}
	else {
		if (len > 0xFFFFFF) {
			vec->insert(vec->begin(), lch, lch + 4);
			vec->insert(vec->begin(), 4 + 128);
		}
		else if (len > 0xFFFF) {
			vec->insert(vec->begin(), lch , lch + 3);
			vec->insert(vec->begin(), 3 + 128);
		}
		else if (len > 0xFF) {
			vec->insert(vec->begin(), lch, lch + 2);
			vec->insert(vec->begin(), 2 + 128);
		}
		else {
			vec->insert(vec->begin(), lch , lch + 1);
			vec->insert(vec->begin(), 1 + 128);
		}

	}
}

void BER::BER_insert_integer(vector<unsigned char>*vec, uint32_t val, ber_type type) {
	unsigned char* ch = reinterpret_cast<unsigned char*>(&val);

	if (val > 0xFFFFFF) {
		vec->insert(vec->begin(), ch, ch + 4);
		vec->insert(vec->begin(), 4);
		vec->insert(vec->begin(), type);
		
	}else
	if (val > 0xFFFF) {
		vec->insert(vec->begin(), ch, ch + 3);
		vec->insert(vec->begin(), 3);
		vec->insert(vec->begin(), type); 
	}else
	if (val > 0xFF) {
		vec->insert(vec->begin(), ch, ch+2);
		vec->insert(vec->begin(), 2);
		vec->insert(vec->begin(), type); 
	}
	else {
		vec->insert(vec->begin(), ch, ch + 1);
		vec->insert(vec->begin(), 1);
		vec->insert(vec->begin(), type);
	}
}
void BER::BER_insert_octet_string(vector<unsigned char>*vec, string str) {
	
	vec->insert(vec->begin(), str.begin(), str.end());//Внесли данные
	BER::stamp_BER_length(vec, str.length());
	vec->insert(vec->begin(), BER_OCTET_STRING);
}
BER::~BER()
{
	
}
