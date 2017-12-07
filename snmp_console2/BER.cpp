

#include "module.hpp"
BER::BER() {}
BER::BER(vector<guint8> el, short lev) {
	BER(reinterpret_cast<guint8*>(el.data()), lev);
}
BER::BER(guint8 const* el,short lev) {
	level= 1+lev;
	type = (ber_type)*el;
	length = *(el + 1);
	len_offset = 1;
	if (length > 127) {
		len_offset = length - 127;
		guint8* i = new guint8[sizeof(int)];
		memset(i, 0, sizeof(int));
		memcpy(i, el+2, len_offset-1);
		length = *(int*)i;
	}
	//cout << length << endl;


	switch (*el) {
	case 0x02: 
	{
		guint8* i= new guint8[sizeof(int)];
		memset(i, 0, sizeof(int));
		memcpy(i, el+ len_offset+1, length);
		reverse(i, i + length);
		value_int = (*(int*)i);
				
		delete i;
		//cout  << "INTEGER	" << value_int<< endl ;
		break;
	}
	case 0x04:  
	{
		guint8* value = (guint8*)malloc((length + 2)* sizeof(guint8));
		memset(value, 0, length + 2);
		memcpy(value, el+ len_offset+1, length);
		value_str=string( reinterpret_cast<char*>(value));
		//cout  << "OCTET STRING	" << (guint8*)value<<endl;
		free(value);
		break;
	}
	case 0x06: //cout << tab << "OBJECT IDENTIFIER" << endl << tab;
	{
		//value = (guint8*)malloc((length ) * sizeof(guint8));
		//memset(value, 0, length);
		//memcpy(value, el+ len_offset+1, length);
		//cout << "OBJECT IDENTIFIER	"; count = 0;
		for (ptrdiff_t i = 0; i < length; i++)
		{
			short sh = (short)*((guint8*)el + len_offset + 1 + i);
			if ( sh== 0x2b) {
					//cout <<  "1.3.";
			}
			else {
					//cout <<hex<< sh << ".";
			}
			value_oid.push_back(sh);
			//count++;


		}
		//cout << endl;
		break; 
	}
	case 0x05: //cout << tab << "NULL"; 
		value_int = 0;
		break;
	case 0x30: //cout << tab << "SEQUENCE";
	{
	

		
	}
	case 0x40: //cout << tab << "IP ADDRESS"; 
		
	case 0x41: //cout << tab << "COUNTER"; 
		
	case 0x42: //cout << tab << "GAUGE"; 
		
	case 0x43: //cout << tab << "TIMETICKS";
		
	case 0xA0: //cout << tab << "GetRequest"; 
		
	case 0xA1: //cout << tab << "GetNextRequest";
		
	case 0xA2: //cout << tab << "Response";
		
		
	case 0xA3: //cout << tab << "SetRequest"; 
		
	case 0xA5: //cout << tab << "GetBulkRequest";
		
	case 0xA6:// cout << tab << "InformRequest";
		
	case 0xA7:// cout << tab << "Trap "; 
		
	case 0xA8: //cout << tab << "Report";
		

	default:// cout << tab << "UNKNOWN"; 
			//cout << "SEQUENCE			" << count << endl;

		ber_sequence_parse(el + len_offset + 1, length, &value_arr, level);
		//cout << "SEQUENCE			" << count << endl;
		break;;
	}




}
void BER::stamp_BER_length(vector<guint8>*vec, uint32_t len) {
	guint8* lch = reinterpret_cast<guint8*>(&len);

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
	//free(lch);
}

void BER::BER_insert_integer(vector<guint8>*vec, uint32_t val, ber_type type) {
	guint8* ch = reinterpret_cast<guint8*>(&val);

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
void BER::BER_insert_octet_string(vector<guint8>*vec, string str) {
	
	vec->insert(vec->begin(), str.begin(), str.end());//Внесли данные
	BER::stamp_BER_length(vec, str.length());
	vec->insert(vec->begin(), BER_OCTET_STRING);
}
BER::~BER()
{
	
}
short BER::ber_sequence_parse(const guint8 *el, int length, vector<shared_ptr<BER>> *value, short lev) {
	int count = 0;
	int pos = 0;
	//vector<BER*> bers; 
	while (pos<length - 1) {

		std::shared_ptr<BER> ber = std::shared_ptr<BER>(new BER(el + pos, lev));
		value->push_back(ber);

		count++;

		pos += value->back()->length + value->back()->len_offset + 1;

	}
	//value = &bers;
	return count;
}
uint32_t BER::getLength(vector<guint8>*vec) {
	return std::distance(vec->begin(), vec->end());
}
