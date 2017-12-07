#include "module.hpp"
//#include "SNMP_PDU.h"


SNMP_PDU::SNMP_PDU() {
	


}
SNMP_PDU::~SNMP_PDU() {
}
SNMP_PDU* SNMP_PDU::ParseBERtoSNMP_PDU(std::shared_ptr<BER> ber) {
	SNMP_PDU* pdu = new SNMP_PDU();
	vector<shared_ptr<BER>>::iterator it = ber->value_arr.begin();
	pdu->version = (*it)->value_int;
	pdu->community = (*(it + 1))->value_str;
	pdu->pdutype = (*(it + 2))->type;
	
	it = (*(it + 2))->value_arr.begin();

	
	pdu->request_id = (*(it))->value_int;
	pdu->error_status = (*(it+1))->value_int;
	pdu->error_index= (*(it+2))->value_int;

	it = (*(it + 3))->value_arr.begin();

	for (auto i =(*it)->value_arr.begin(); i != (*it)->value_arr.end(); ++i) {
		
		string oid = oidtostr((*i)->value_oid);
	//	cout << oid << endl;
		pdu->variable_bindings.insert(pair<string, std::shared_ptr<BER>>(oid,*(++i)));
		
	}
	return pdu;

}
void SNMP_PDU::SNMP_PDUtoBER(vector<guint8> *vec) {

	//ValSeq
	for (auto it = variable_bindings.begin(); it != variable_bindings.end(); ++it) {
		shared_ptr<BER> b = shared_ptr<BER>(new BER());

		//cout << it->first << endl;
		switch (it->second->type) {
		case BER_INTEGER:
		case BER_GAUGE:
		case BER_TIMETICKS: {
			BER::BER_insert_integer(vec, it->second->value_int, it->second->type);

			break; }
		case BER_OCTET_STRING: {
			BER::BER_insert_octet_string(vec, it->second->value_str);

			
			break;

		}
		case BER_NULL: {
			vec->insert(vec->begin(), 0);
			vec->insert(vec->begin(), it->second->type);


			break;

		}
	
		case BER_OBJECT_IDENTIFIER: {
			
			vec->insert(vec->begin(), it->second->value_oid.begin(), it->second->value_oid.end());

			BER::stamp_BER_length(vec, BER::getLength(&it->second->value_oid));

			vec->insert(vec->begin(), it->second->type);
			break;
		}
		case BER_IP_ADDRESS: 

		default: {cout << "UNKNOWN SECOND TYPE" << endl;  break; }
		}

		vector<guint8> oid = oid_parse(it->first);

		vec->insert(vec->begin(), oid.begin(), oid.end());

		BER::stamp_BER_length(vec, BER::getLength(&oid));
		vec->insert(vec->begin(), BER_OBJECT_IDENTIFIER);
	}
	
	
	//VarBind
	BER::stamp_BER_length(vec, BER::getLength(vec));
	vec->insert(vec->begin(), BER_SEQUENCE);

	//VarBindList
	BER::stamp_BER_length(vec, BER::getLength(vec));
	vec->insert(vec->begin(), BER_SEQUENCE);
	  
	//»ндекс ошибки
	BER::BER_insert_integer(vec, this->error_index, BER_INTEGER);

	//—осто€ие ошибки
	BER::BER_insert_integer(vec, this->error_status, BER_INTEGER);

	//ID запроса
	BER::BER_insert_integer(vec, this->request_id, BER_INTEGER);

	//PDU
	BER::stamp_BER_length(vec, BER::getLength(vec));
	vec->insert(vec->begin(), pdutype);

	//Community
	BER::BER_insert_octet_string(vec, community);
/*
	//SNMP version
	BER::BER_insert_integer(vec, version, BER_INTEGER);

	//PDU
	BER::stamp_BER_length(vec, getLength(vec));
	vec->insert(vec->begin(), BER_SEQUENCE);
	*/
}
string SNMP_PDU::oidtostr(vector<guint8>oid) {
	vector<guint8>::iterator it;// = oid.begin();
	string out = "";
	for (it = oid.begin(); it != oid.end(); ++it)
	{
		string s;
		if (*it < 128) { s = std::to_string(*it); }
		else {
			uint32_t temp = 0;
			while (*it > 127) {
				//cout << hex << temp<<endl;
				temp = (uint32_t)(temp*(pow(2, 7)));
				temp += (*it) & 127;
				//cout << hex << temp << endl;
				it++;
			}
			temp = (uint32_t)(temp*(pow(2, 7)));
			temp += (*it) & 127;
			s = to_string(temp);
		}
		out += s + ".";
	}
	out.replace(0, 2, "1.3");
	out.pop_back();
	return out;
}
vector<guint8> SNMP_PDU::oid_parse(string oid) {
	uint16_t count = 0;
	vector<guint8> val;
	if (oid.find("1.3") != 0) return val;
	oid.replace(0, 3, "43");
	//cout << "OID" << oid;

	vector<std::string> sv = split(oid, '.');
	std::vector<guint8>::iterator it = val.begin();
	for each (std::string var in sv)
	{
		int i = std::stoi(var);
		if (i > 127) {
			bool begin = false;
			while (i > 0) {
				guint8 t = (begin ? 128 : 0) + (i & 127);
				begin = true;
				it = val.insert(it, t);
				i = i / (pow(2, 7));
			}
		}
		else {
			val.push_back((guint8)i);
			it = val.end();
		}

	}
	return val;
}
std::vector<std::string> SNMP_PDU::split(std::string strToSplit, char delimeter)
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