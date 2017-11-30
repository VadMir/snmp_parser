// snmp_console2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
unsigned char mas[]{
	0x30, 0x3c, 0x02, 0x01, 0x01, 0x04, 0x06, 0x70, 
	0x75, 0x62, 0x6c, 0x69, 0x63, 0xa2, 0x2f, 0x02, 
	0x04, 0x67, 0x91, 0x77, 0xf5, 0x02, 0x01, 0x00, 
	0x02, 0x01, 0x00, 0x30, 0x21, 0x30, 0x1f, 0x06, 
	0x08, 0x2b, 0x06, 0x01, 0x02, 0x01, 0x01, 0x04, 
	0x00, 0x04, 0x13, 0x4d, 0x65, 0x20, 0x3c, 0x6d, 
	0x65, 0x40, 0x65, 0x78, 0x61, 0x6d, 0x70, 0x6c, 
	0x65, 0x2e, 0x6f, 0x72, 0x67, 0x3e
};
std::string oid = "1.3.6.1.4.1.9585.1.0";


//std::string tab="\t";
std::vector<std::string> split(std::string strToSplit, char delimeter)
{
	std::stringstream ss(strToSplit);
	std::string item;
	std::vector<std::string> splittedStrings;
	while (std::getline(ss, item, delimeter))
	{
		splittedStrings.push_back(item);
	}
	return splittedStrings;
}

vector<unsigned char> oid_parse(string oid) {
	uint16_t count = 0;
	vector<unsigned char> val;
	if (oid.find("1.3") != 0) return val;
	oid.replace(0, 3, "43");
	cout << "OID" << oid;

	vector<std::string> sv = split(oid, '.');
	std::vector<unsigned char>::iterator it = val.begin();
	for each (std::string var in sv)
	{
		int i=std::stoi(var);
		if (i > 127) {
			bool begin=false;
			while (i > 0) {
				unsigned char t = (begin?128:0) + (i & 127);
				begin = true;
				it=val.insert(it,t);
				i = i / (pow(2, 7));
			}
		}
		else {
			val.push_back((unsigned char)i);
			it = val.end();
		}

	}
	return val;
}

short ber_sequence_parse(unsigned char *el,int length, void *value,std::string tab) {
	int count = 0;
	int pos = 0;
	vector<BER*> bers; 
	while (pos<length-1) {
		
		bers.push_back(new BER(el + pos, tab));
		
		count++;
		
		pos += bers.back()->length + bers.back()->len_offset + 1;
		
	}
	value = &bers;
	return count;
}

/*void getval(unsigned char* el, unsigned char type, unsigned len) {

	switch (type) {
	case 0x02: {
		unsigned char* t = new unsigned char[sizeof(int)];
		memset(t, 0, sizeof(int));
		memcpy(t, el, len);
		reverse(t, t + len);

		//cout << (*(int*)t);
		delete t;
		break;
	}
	case 0x04: {
		unsigned char* t = new unsigned char[len+2];
		memset(t, 0, len+2);
		memcpy(t, el, len);
	//	cout << t; 

		//cout << tab << "OCTET STRING";
		delete t;
		break; }
	case 0x06: //cout << tab << "OBJECT IDENTIFIER"; 
	{
		unsigned char* t = new unsigned char[len];
		memset(t, 0, len);
		memcpy(t, el, len);
		for (ptrdiff_t  i = 0; i < len; i++)
		{
			if ((short)*(t + i) == 0x2b) {
			//	cout <<  "1.3.";
			}
			else {
			//	cout << (short)*(t + i) << ".";
			}
		}
		delete t;
		 

	break; }
	//case 0x05: cout << tab << "NULL"; break;
	//case 0x30: cout << tab << "SEQUENCE"; break;
	//case 0x40: cout << tab << "IP ADDRESS"; break;
	//case 0x41: cout << tab << "COUNTER"; break;
	//case 0x42: cout << tab << "GAUGE"; break;
	//case 0x43: cout << tab << "TIMETICKS"; break;

	//case 0xA0: cout << tab << "GetRequest"; break;
	//case 0xA1: cout << tab << "GetNextRequest"; break;
	//case 0xA2: cout << tab << "Response"; break;
	//case 0xA3: cout << tab << "SetRequest"; break;
	//case 0xA5: cout << tab << "GetBulkRequest"; break;
	//case 0xA6: cout << tab << "InformRequest"; break;
	//case 0xA7: cout << tab << "Trap "; break;
	//case 0xA8: cout << tab << "Report"; break;

	//default: /*cout << tab << "UNKNOWN"; break;
	}
}*/
/*void rec(unsigned char* el,unsigned pos, unsigned size) {
	if (pos >= size) 
		return;
	unsigned length = (unsigned)(*(el + 1));
	switch (*el) {
	case 0x02: //cout << tab << "INTEGER" << endl << tab;
		getval(el+2, *el, length); break; 
	case 0x04: //cout << tab << "OCTET STRING" << endl << tab; 
		getval(el + 2, *el, length); break;
	case 0x06: //cout << tab << "OBJECT IDENTIFIER" << endl << tab;
		getval(el + 2, *el, length); break;
	case 0x05: //cout << tab << "NULL"; 
		break;
	case 0x30: //cout << tab << "SEQUENCE";
		break;
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

	//cout  <<endl<<tab<< "LENGTH: "<<hex <<(short)(*(el+1))<<endl<<endl;

	pos += length + 2;

	if (((*el)!=0x30)&&((*el)<0xA0)) rec(el + 2 + length,pos, size);
	else {
		tab += "\t";
		unsigned char *value=new unsigned char[length];
		memcpy(value, el + 2, length);
		rec(value, 0, length);
		delete value;
	}
	tab = tab.substr(0, tab.size() - 1);
}
*/
int main()
{
	for (size_t i = 0; i < 100000; i++)
	{
		BER* ber = new BER(&mas[0],"\t");
		//ber->CLEAN();
		ber->~BER();
	}
	vector<unsigned char> val=oid_parse(oid);
	cout << endl;
	for each (unsigned char var in val)
	{
		cout << hex << (int)var <<" ";
	}
	
	//BER* ber = new BER(&mas[0]);
	/*for each (unsigned char i in mas)
	{
		cout << (short)i <<endl;
	}
	*/
	cout << "ok";
	getchar();
    return 0;
}

