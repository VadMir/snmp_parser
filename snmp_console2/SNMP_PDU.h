#pragma once

#ifndef SNMP_PDU_H
#define SNMP_PDU_H

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

typedef uint32_t PDUType;



#define noError		0		//Нет ошибки
#define	TooBig		1		//Слишком большой ответ для размещения в одном сообщении
#define	NoSuchName	2		//Переменная не существует
#define	BadValue	3		//Значение, которое должно быть сохранено, недопустимо
#define	readOnly	4		//Значение не может быть изменено
#define	genErr		5		//Другие ошибки

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
	
	std::unordered_map<std::string, std::shared_ptr<BER>>variable_bindings;


	static SNMP_PDU* SNMP_PDU::ParseBERtoSNMP_PDU(std::shared_ptr<BER>);
	void SNMP_PDU::SNMP_PDUtoBER(std::vector<guint8> *vector);
	static string SNMP_PDU::oidtostr(vector<guint8>oid);
	static vector<guint8> SNMP_PDU::oid_parse(string oid);
	static std::vector<std::string> SNMP_PDU::split(std::string strToSplit, char delimeter);
};

#endif