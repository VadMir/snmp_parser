#include "stdafx.h"
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
void SNMP_PDU::SNMP_PDUtoBER(vector<unsigned char> *vec) {

	//ValSeq
	for (auto it = variable_bindings.begin(); it != variable_bindings.end(); ++it) {
		shared_ptr<BER> b = shared_ptr<BER>(new BER());

		cout << it->first << endl;
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
		case BER_IP_ADDRESS: {

			break;
		}
		case BER_OBJECT_IDENTIFIER: {
			
			vec->insert(vec->begin(), it->second->value_oid.begin(), it->second->value_oid.end());

			BER::stamp_BER_length(vec, getLength(&it->second->value_oid));

			vec->insert(vec->begin(), it->second->type);
			break;
		}


		default: {cout << "UNKNOWN SECOND TYPE" << endl;  break; }
		}

		vector<unsigned char> oid = oid_parse(it->first);

		vec->insert(vec->begin(), oid.begin(), oid.end());

		BER::stamp_BER_length(vec, getLength(&oid));
		vec->insert(vec->begin(), BER_OBJECT_IDENTIFIER);
	}
	
	
	//VarBind
	BER::stamp_BER_length(vec, getLength(vec));
	vec->insert(vec->begin(), BER_SEQUENCE);

	//VarBindList
	BER::stamp_BER_length(vec, getLength(vec));
	vec->insert(vec->begin(), BER_SEQUENCE);
	  
	//»ндекс ошибки
	BER::BER_insert_integer(vec, this->error_index, BER_INTEGER);

	//—осто€ие ошибки
	BER::BER_insert_integer(vec, this->error_status, BER_INTEGER);

	//ID запроса
	BER::BER_insert_integer(vec, this->request_id, BER_INTEGER);

	//PDU
	BER::stamp_BER_length(vec, getLength(vec));
	vec->insert(vec->begin(), pdutype);

	//Community
	BER::BER_insert_octet_string(vec, community);

	//SNMP version
	BER::BER_insert_integer(vec, version, BER_INTEGER);

	//PDU
	BER::stamp_BER_length(vec, getLength(vec));
	vec->insert(vec->begin(), BER_SEQUENCE);

}