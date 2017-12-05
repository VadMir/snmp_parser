// snmp_console2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

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
		int i = std::stoi(var);
		if (i > 127) {
			bool begin = false;
			while (i > 0) {
				unsigned char t = (begin ? 128 : 0) + (i & 127);
				begin = true;
				it = val.insert(it, t);
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
string oidtostr(vector<unsigned char>oid) {
	vector<unsigned char>::iterator it;// = oid.begin();
	string out = "";
	for (it=oid.begin(); it!=oid.end();++it)
	{
		string s;
		if (*it < 128) { s = std::to_string(*it); }
		else {
			uint32_t temp=0;
			while (*it > 127) {
				cout << hex << temp<<endl;
				temp = (uint32_t)(temp*(pow(2, 7)));
				temp+=(*it) & 127;
				cout << hex << temp << endl;
				it++;
			}
			temp = (uint32_t)(temp*(pow(2, 7)));
			temp  += (*it) & 127;
			s = to_string(temp);
		}
		out += s + ".";
	}
	out.replace(0, 2, "1.3");
	out.pop_back();
	return out;
}

short ber_sequence_parse(unsigned char *el,int length, vector<shared_ptr<BER>> *value,short lev) {
	int count = 0;
	int pos = 0;
	//vector<BER*> bers; 
	while (pos<length-1) {
		
		std::shared_ptr<BER> ber = std::shared_ptr<BER>(new BER(el + pos, lev));
		value->push_back(ber);
		
		count++;
		
		pos += value->back()->length + value->back()->len_offset + 1;
		
	}
	//value = &bers;
	return count;
}


int main()
{
	for (size_t i = 0; i < 1; i++)
	{
		shared_ptr<BER> ber = std::shared_ptr<BER>(new BER(&mas[0],0));
		SNMP_PDU* pdau = SNMP_PDU::ParseBERtoSNMP_PDU(ber);
	}
	vector<unsigned char> val=oid_parse(oid);
	cout << endl;
	for each (unsigned char var in val)
	{
		cout << hex << (int)var <<" ";
	}
	
	cout << endl;
	cout << oidtostr(val);

	cout << "ok";
	getchar();
    return 0;
}

