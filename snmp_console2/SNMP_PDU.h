#pragma once
#include <string>
#include <memory>
#include <vector>
#include <map>

#include "BER.h"

typedef uint32_t PDUType;

#define GETREQUEST		0xA0;
#define GETNEXTREQUEST	0xA1;
#define RESPONSE		0xA2;
#define SETREQUEST		0xA3;
#define GETBULKREQUEST	0xA5;
#define INFORMREQUEST	0xA6;
#define TRAP			0xA7;
#define REPORT			0xA8;

#define noError		0		//��� ������
#define	TooBig		1		//������� ������� ����� ��� ���������� � ����� ���������
#define	NoSuchName	2		//���������� �� ����������
#define	BadValue	3		//��������, ������� ������ ���� ���������, �����������
#define	readOnly	4		//�������� �� ����� ���� ��������
#define	genErr		5		//������ ������

class SNMP_PDU {
	public:
	SNMP_PDU();
	~SNMP_PDU();

	uint32_t version;
	std::string community;

	
	PDUType pdutype;
	uint32_t request_id;
	uint32_t error_status;
	uint32_t error_index;
	
	std::map<std::string, std::shared_ptr<BER>>variable_bindings;


	static SNMP_PDU* SNMP_PDU::ParseBERtoSNMP_PDU(std::shared_ptr<BER>);
	void SNMP_PDU::SNMP_PDUtoBER(std::vector<unsigned char> *vector);
};