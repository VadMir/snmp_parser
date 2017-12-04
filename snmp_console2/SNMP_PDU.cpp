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
		
		pdu->variable_bindings.insert(pair<string, std::shared_ptr<BER>>(oidtostr((*i)->value_oid),*(++i)));
		
	}
	return pdu;

}
void SNMP_PDU::SNMP_PDUtoBER(vector<unsigned char> *vector) {
	for (auto it = variable_bindings.begin(); it != variable_bindings.end(); ++it) {
		shared_ptr<BER> b = shared_ptr<BER>(new BER());
		switch (it->second->type) {
		case BER_INTEGER:break;
		case BER_GAUGE:break;
		case BER_TIMETICKS: {
			unsigned char* ch = reinterpret_cast<unsigned char*>(&it->second->value_int);
			if (it->second->value_int > 0xFFFFFF) *vector->insert(*vector->begin(), &ch, &(ch + 3));



			break; }
		case BER_OCTET_STRING:
		case BER_OBJECT_IDENTIFIER:break;
		case BER_IP_ADDRESS:
		default:break;

		}
	}

}