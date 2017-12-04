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

	it = (*(it + 2))->value_arr.begin();

	pdu->pdutype = (*it)->value_int;
	pdu->request_id = (*(it+1))->value_int;
	pdu->error_status = (*(it+2))->value_int;
	pdu->error_index= (*(it+3))->value_int;



	for (auto i =(*(it + 4))->value_arr.begin(); i != (*(it + 4))->value_arr.end(); ++i) {
		
		pdu->variable_bindings.insert(pair<string, std::shared_ptr<BER>>(oidtostr((*i)->value_oid),*(++i)));
		
	}
	return pdu;

}