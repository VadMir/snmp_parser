/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
///
///
/// ffsrm.h : Fielgat's headers.
///
/// Changelog:
/// [+] 2017-01-12 - Добавлено: S10G_FILTER_ITEM_STRUCT_2_PACKED, S10G_ADD_FILTER_2_PACKED;
/// [+] 2016-10-22 - Добавлено: S10G_ADD_FILTER_2, S10G_UPDATE_FILTERS_2, S10G_FILTER_ITEM_STRUCT_2 (с поддержкой IPv6);
///
/// Copyright (C) MSC, ORG 2009-2017
///

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#ifndef FFSRM_H
#define FFSRM_H

#include <mscu_types.h>

//Возможные виды пакетов (все виды, в паравозе могут быть не все):
// enum
// {
//      TRAIN_ENCAP_SRM_UNI     = 0x9a, //SRM UNI packet - Уже выбран и имеет правильный LID, был выбран по заданному IP фильтру, MAC адресу, номеру VLAN.
//              //IP адрес может быть как в "обычныом" IP пакете, так и инкапулированным во VLAN, Q-in-Q, MPLS, VLAN-MPLS, Q-in-Q - VLAN - MPLS
//      TRAIN_ENCAP_SRM_MAIL    = 0x9b, //Пакет TCP порт 25/110/119/143 (E-Mail)
//      TRAIN_ENCAP_SRM_FTP     = 0x9c, //Пакет TCP порт 20/21 (FTP)
//      TRAIN_ENCAP_SRM_TCPVOIP = 0x9d, //Пакет TCP порт 1720 (VoIP)
//      TRAIN_ENCAP_SRM_UDPVOIP = 0x9e, //Пакет UDP порт 5060 (VoIP)
//      TRAIN_ENCAP_SRM_ICQ     = 0x9f, //Пакет TCP порт 5190 (ICQ)
//      TRAIN_ENCAP_SRM_WMSG    = 0xa0, //Пакет TCP порт 3235/1863 (W-MSG)
//      TRAIN_ENCAP_SRM_MRAGENT = 0xa1, //Пакет TCP порт 2041/2042 (MailruAgent)
//      TRAIN_ENCAP_SRM_GGLTALK = 0xa2, //Пакет TCP порт 443 (GoogleTalk)
//      TRAIN_ENCAP_SRM_RADIUS  = 0xa3, //Пакет UDP порт 1812/1813/1645/1646 (RADIUS)
//      TRAIN_ENCAP_SRM_TACACS  = 0xa4, //Пакет TCP порт 49 / Пакет UDP порт 49 (TACACS)
//      TRAIN_ENCAP_SRM_DIAMETR = 0xa5, //Пакет TCP порт 3868 (DIAMETR)
//      TRAIN_ENCAP_SRM_UDP     = 0xa6, //Пакет UDP
// //   TRAIN_ENCAP_SRM_UNI_    = 0xa7, //Пакет отобран фильтром «по типу», имеет правильный LID - вместо него сейчас 0x9a
//      TRAIN_ENCAP_SRM_RESERV  = 0xa8, //резерв
//      TRAIN_ENCAP_SRM_NOIP    = 0xa9, //PPPoE (0x8863, 0x8864) & broadcasts (MAC2 = ff:ff:ff:ff:ff:ff)
//      TRAIN_ENCAP_SRM_UNKNOWN = 0xaa, //Пакет неопознанного типа
// }

//Предварительные структуры для связи по сети со съемником:
//Сигнатуры пакетов
enum {
        S10G_ADD_FILTER				= 0x09081818,   //добавить фильтр (S10G_FILTER_ITEM_STRUCT)
        S10G_UPDATE_FILTERS		= 0x09081819,   //обновить список активных фильтров
                                      // каждый пакет с данной сигнатурой содержит заголовок S10G_UPDATE_FILTERS_HEADER_STRUCT
                                      // и определенное количество записей типа S10G_FILTER_ITEM_STRUCT
                                      // алгоритм передачи:
                                      //  полный список фильтров не может уместиться в одном пакете с сигнатурой S10G_UPDATE_FILTERS (для UDP-пакетов)
                                      //  поэтому список сессий разбивается на части и передается группой пакетов
                                      //  в группе пакетов: значение поля sequence первого пакета равно 0
                                      //  в группе пакетов: значение поля count последнего пакета равно 0
                                      //  в группе пакетов: значение поля sequence очередного пакета равно значению (count+sequence) предыдущего пакета
        S10G_RES_FILTER				= 0x0908181a,   //возвращаемый от съемника ответ на изменение фильтра

        S10G_GET_PARAMS				= 0x0908181b,   //Получить параметры со съемника - команда посылается на съемник
        S10G_REQ_PARAMS				= 0x0908181c,   //Получить параметры со съемника - возвращаемые данные со съемника
        S10G_SET_FILTER_PARAM = 0x10051418,	// Передать настройки механизма фильтрации на съемник
        S10G_ADD_FILTER_2     = 0x0908181d,	//добавить фильтр (S10G_FILTER_ITEM_STRUCT_2)
        S10G_UPDATE_FILTERS_2 = 0x0908181e, // обновить список активных фильтров
																						// каждый пакет с данной сигнатурой содержит заголовок S10G_UPDATE_FILTERS_HEADER_STRUCT
																						// и определенное количество записей типа S10G_FILTER_ITEM_STRUCT_2_PACKED
																						// алгоритм передачи:	см. S10G_UPDATE_FILTERS
																						// Важное замечание заключается в том, что фактически передаются
																						// только те поля, которые несут нагрузку. При этом используется выравнивание до 4 байт.
																						// поля proto и flags передаются всегда. Остальные поля передаются в зависимости от значения поля proto:
																						//	 значение proto										|	  передаваемые поля
																						// S10G_FILTER_PROTO_4_IP							| ip4.ip1
																						// S10G_FILTER_PROTO_4_IP_IP					| ip4.ip1 ip4.ip2
																						// S10G_FILTER_PROTO_4_IP_TCP					| ip4.ip1 port1 2_byte_alignment
																						// S10G_FILTER_PROTO_4_IP_UDP					| ip4.ip1 port1 2_byte_alignment
																						// S10G_FILTER_PROTO_4_IP_TCP_IP_TCP	| ip4.ip1 ip4.ip2 port1 port2
																						// S10G_FILTER_PROTO_4_IP_UDP_IP_UDP	| ip4.ip1 ip4.ip2	port1	port2
																						// S10G_FILTER_PROTO_6_IP							| ip6.ip1
																						// S10G_FILTER_PROTO_6_IP_IP					| ip6.ip1 ip6.ip2
																						// S10G_FILTER_PROTO_6_IP_TCP					| ip6.ip1 port1 2_byte_alignment
																						// S10G_FILTER_PROTO_6_IP_UDP					| ip6.ip1 port2 2_byte_alignment
																						// S10G_FILTER_PROTO_6_IP_TCP_IP_TCP	| ip6.ip1 ip6.ip2 port1	port2
																						// S10G_FILTER_PROTO_6_IP_UDP_IP_UDP	| ip6.ip1 ip6.ip2 port1	port2
        S10G_ADD_FILTER_2_PACKED = 0x0908181f,	//добавить фильтр - упакованный вариант (S10G_FILTER_ITEM_STRUCT_2_PACKED)
};

//описание фильтра
// если определенное поле равно 0, значит поле не участвует в фильтрации (любое значение)
// возможны любые варианты, с любым количеством нулевых полей, например:
//  - ip1,port1,ip2,port2
//  - ip1,port1,ip2 (в этом случае port2 передается как нулевой)
//  - ip1,ip2 (в этом случае port1, port2 передаются как нулевые)
//  - ip1,port1 (в этом случае ip2, port2 передаются как нулевые)
//  - ip1 (в этом случае port1, ip2, port2 передаются как нулевые)
// фильтры должны предполагать оба направления передачи, например:
//   ip1,ip2 - отбирает пакеты ip_src==ip1,ip_dst==ip2 и ip_src==ip2,ip_dst==ip1
STRUCT_PACKED_BEGIN // устанавливаем выравнивание структур в 1 байт
typedef struct STRUCT_PACKED_ATTRIBUTE {
#define S10G_FILTER_PROTO_AAA 0x00
#define S10G_FILTER_PROTO_TCP 0x01
#define S10G_FILTER_PROTO_UDP 0x02
#define S10G_FILTER_PROTO_TCP_IGNORE_SESSION 0x03 // 2013-07-04 HTTP-request functionality
#define S10G_FILTER_PROTO_UDP_IGNORE_SESSION 0x04 // 2014-03-11 HTTP-request functionality

  guint32 proto; //протокол (тип передаваемых данных)

  guint32 ip1;   //IP-адрес в сетевом порядке
  guint32 ip2;   //IP-адрес в сетевом порядке
  guint16 port1; //TCP/UDP-порт в сетевом порядке
  guint16 port2; //TCP/UDP-порт в сетевом порядке
} S10G_FILTER_ITEM_STRUCT; //описание фильтра
STRUCT_PACKED_END // восстанавливаем выравнивание структур по умолчанию

// added 2016-10-22

STRUCT_PACKED_BEGIN // устанавливаем выравнивание структур в 1 байт
typedef struct STRUCT_PACKED_ATTRIBUTE {
	union {
		guint8    bytes[4];
		guint16   words[2];
		guint32   qword;
	}; // IP-адрес в сетевом порядке
} S10G_IPv4;
STRUCT_PACKED_END // восстанавливаем выравнивание структур по умолчанию

STRUCT_PACKED_BEGIN // устанавливаем выравнивание структур в 1 байт
typedef struct STRUCT_PACKED_ATTRIBUTE {
	union {
		guint8    bytes[16];
		guint16   words[8];
		guint32  qwords[4];
	}; // IP-адрес в сетевом порядке
} S10G_IPv6;
STRUCT_PACKED_END // восстанавливаем выравнивание структур по умолчанию

// описание фильтра
// не нужно проверять поле на равенство 0, для этого используются уточненные значения	поля proto
// возможны любые варианты, с любым количеством нулевых полей, например:
//  - ip1,port1,ip2,port2
//  - ip1,port1,ip2 (в этом случае port2 передается как нулевой)
//  - ip1,ip2 (в этом случае port1, port2 передаются как нулевые)
//  - ip1,port1 (в этом случае ip2, port2 передаются как нулевые)
//  - ip1 (в этом случае port1, ip2, port2 передаются как нулевые)
// фильтры должны предполагать оба направления передачи, например:
//   ip1,ip2 - отбирает пакеты ip_src==ip1,ip_dst==ip2 и ip_src==ip2,ip_dst==ip1
STRUCT_PACKED_BEGIN // устанавливаем выравнивание структур в 1 байт
typedef struct STRUCT_PACKED_ATTRIBUTE {
	// S10G_FILTER_PROTO_4_XXX - IP version 4 is used
#define S10G_FILTER_PROTO_4_IP						0x0000
#define S10G_FILTER_PROTO_4_IP_IP					0x0001
#define S10G_FILTER_PROTO_4_IP_TCP				0x0002
#define S10G_FILTER_PROTO_4_IP_UDP				0x0003
#define S10G_FILTER_PROTO_4_IP_TCP_IP_TCP 0x0004
#define S10G_FILTER_PROTO_4_IP_UDP_IP_UDP 0x0005
	// S10G_FILTER_PROTO_6_XXX - IP version 6 is used
#define S10G_FILTER_PROTO_6_IP						0x0006
#define S10G_FILTER_PROTO_6_IP_IP					0x0007
#define S10G_FILTER_PROTO_6_IP_TCP				0x0008
#define S10G_FILTER_PROTO_6_IP_UDP				0x000a
#define S10G_FILTER_PROTO_6_IP_TCP_IP_TCP 0x000b
#define S10G_FILTER_PROTO_6_IP_UDP_IP_UDP 0x000c
	guint16 proto; // содержимое - S10G_FILTER_PROTO_XXX (сетевой порядок байт)
#define S10G_FILTER_FLAG_IGNORE 0x0001
	guint16 flags; // флаги - комбинация S10G_FILTER_FLAG_XXX (сетевой порядок байт)
	union	{
		struct STRUCT_PACKED_ATTRIBUTE {
			S10G_IPv4 ip1; // IP-адрес в сетевом порядке
			S10G_IPv4 ip2; // IP-адрес в сетевом порядке
		} ip4;
		struct STRUCT_PACKED_ATTRIBUTE {
			S10G_IPv6 ip1; // IP-адрес в сетевом порядке
			S10G_IPv6 ip2; // IP-адрес в сетевом порядке
		} ip6;
	};
	guint16 port1; // TCP/UDP-порт в сетевом порядке
	guint16 port2; // TCP/UDP-порт в сетевом порядке
} S10G_FILTER_ITEM_STRUCT_2; //описание фильтра
STRUCT_PACKED_END // восстанавливаем выравнивание структур по умолчанию

// added 2017-01-12

// Описание фильтра - упакованный вид
// Фактическая длина структуры зависит от значения поля proto (т.е. от тех полей, которые несут нагрузку).
// При этом используется выравнивание до 4 байт.
// Поля proto и flags передаются всегда. Остальные поля передаются в зависимости от значения поля proto:
//	 значение proto										|		передаваемые поля							|	размер структуры (байт)
// S10G_FILTER_PROTO_4_IP							| ip4.ip1													|				 8
// S10G_FILTER_PROTO_4_IP_IP					| ip4.ip1 ip4.ip2									|				12
// S10G_FILTER_PROTO_4_IP_TCP					| ip4.ip1 port1 2_byte_alignment	|				12
// S10G_FILTER_PROTO_4_IP_UDP					| ip4.ip1 port1 2_byte_alignment	|				12
// S10G_FILTER_PROTO_4_IP_TCP_IP_TCP	| ip4.ip1 ip4.ip2 port1 port2			|				16
// S10G_FILTER_PROTO_4_IP_UDP_IP_UDP	| ip4.ip1 ip4.ip2	port1	port2			|				16
// S10G_FILTER_PROTO_6_IP							| ip6.ip1													|				20
// S10G_FILTER_PROTO_6_IP_IP					| ip6.ip1 ip6.ip2									|				36
// S10G_FILTER_PROTO_6_IP_TCP					| ip6.ip1 port1 2_byte_alignment	|				24
// S10G_FILTER_PROTO_6_IP_UDP					| ip6.ip1 port2 2_byte_alignment	|				24
// S10G_FILTER_PROTO_6_IP_TCP_IP_TCP	| ip6.ip1 ip6.ip2 port1	port2			|				40
// S10G_FILTER_PROTO_6_IP_UDP_IP_UDP	| ip6.ip1 ip6.ip2 port1	port2			|				40
STRUCT_PACKED_BEGIN // устанавливаем выравнивание структур в 1 байт
typedef struct STRUCT_PACKED_ATTRIBUTE {
	guint16 proto; // содержимое - S10G_FILTER_PROTO_XXX (сетевой порядок байт)
	guint16 flags; // флаги - комбинация S10G_FILTER_FLAG_XXX (сетевой порядок байт)
	union {
// S10G_FILTER_PROTO_4_IP							| ip4.ip1													|				 8
		struct STRUCT_PACKED_ATTRIBUTE {
			S10G_IPv4 ip1; // IP-адрес в сетевом порядке
		} ip4;
// S10G_FILTER_PROTO_4_IP_IP					| ip4.ip1 ip4.ip2									|				12
		struct STRUCT_PACKED_ATTRIBUTE {
			S10G_IPv4 ip1; // IP-адрес в сетевом порядке
			S10G_IPv4 ip2; // IP-адрес в сетевом порядке
		} ip4_ip4;
// S10G_FILTER_PROTO_4_IP_TCP					| ip4.ip1 port1 2_byte_alignment	|				12
// S10G_FILTER_PROTO_4_IP_UDP					| ip4.ip1 port1 2_byte_alignment	|				12
		struct STRUCT_PACKED_ATTRIBUTE {
			S10G_IPv4 ip1; // IP-адрес в сетевом порядке
			guint16 port1; // TCP/UDP-порт в сетевом порядке
			guint16 stub; // reserved - fill to 4 byte boundary
		} ip4_port;
// S10G_FILTER_PROTO_4_IP_TCP_IP_TCP	| ip4.ip1 ip4.ip2 port1 port2			|				16
// S10G_FILTER_PROTO_4_IP_UDP_IP_UDP	| ip4.ip1 ip4.ip2	port1	port2			|				16
		struct STRUCT_PACKED_ATTRIBUTE {
			S10G_IPv4 ip1; // IP-адрес в сетевом порядке
			S10G_IPv4 ip2; // IP-адрес в сетевом порядке
			guint16 port1; // TCP/UDP-порт в сетевом порядке
			guint16 port2; // TCP/UDP-порт в сетевом порядке
		} ip4_ip4_port_port;
// S10G_FILTER_PROTO_6_IP							| ip6.ip1													|				20
		struct STRUCT_PACKED_ATTRIBUTE {
			S10G_IPv6 ip1; // IP-адрес в сетевом порядке
		} ip6;
// S10G_FILTER_PROTO_6_IP_IP					| ip6.ip1 ip6.ip2									|				36
		struct STRUCT_PACKED_ATTRIBUTE {
			S10G_IPv6 ip1; // IP-адрес в сетевом порядке
			S10G_IPv6 ip2; // IP-адрес в сетевом порядке
		} ip6_ip6;
// S10G_FILTER_PROTO_6_IP_TCP					| ip6.ip1 port1 2_byte_alignment	|				24
// S10G_FILTER_PROTO_6_IP_UDP					| ip6.ip1 port2 2_byte_alignment	|				24
		struct STRUCT_PACKED_ATTRIBUTE {
			S10G_IPv6 ip1; // IP-адрес в сетевом порядке
			guint16 port1; // TCP/UDP-порт в сетевом порядке
			guint16 stub; // reserved - fill to 4 byte boundary
		} ip6_port;
// S10G_FILTER_PROTO_6_IP_TCP_IP_TCP	| ip6.ip1 ip6.ip2 port1	port2			|				40
// S10G_FILTER_PROTO_6_IP_UDP_IP_UDP	| ip6.ip1 ip6.ip2 port1	port2			|				40
		struct STRUCT_PACKED_ATTRIBUTE {
			S10G_IPv6 ip1; // IP-адрес в сетевом порядке
			S10G_IPv6 ip2; // IP-адрес в сетевом порядке
			guint16 port1; // TCP/UDP-порт в сетевом порядке
			guint16 port2; // TCP/UDP-порт в сетевом порядке
		} ip6_ip6_port_port;
	};
} S10G_FILTER_ITEM_STRUCT_2_PACKED; //описание фильтра - упакованная структура
STRUCT_PACKED_END // восстанавливаем выравнивание структур по умолчанию

// fis_p - pointer to the filter_item_struct pointer
#define get_S10G_FILTER_ITEM_STRUCT_2_PACKED_size(fis_p, result) \
	switch (g_ntohs(fis_p->proto)) { \
	case S10G_FILTER_PROTO_4_IP: \
		result = 8; \
		break; \
	case S10G_FILTER_PROTO_4_IP_IP: \
		result = 12; \
		break; \
	case S10G_FILTER_PROTO_4_IP_TCP: \
	case S10G_FILTER_PROTO_4_IP_UDP: \
		result = 12; \
		break; \
	case S10G_FILTER_PROTO_4_IP_TCP_IP_TCP: \
	case S10G_FILTER_PROTO_4_IP_UDP_IP_UDP: \
		result = 16; \
		break; \
	case S10G_FILTER_PROTO_6_IP: \
		result = 20; \
		break; \
	case S10G_FILTER_PROTO_6_IP_IP: \
		result = 36; \
		break; \
	case S10G_FILTER_PROTO_6_IP_TCP: \
	case S10G_FILTER_PROTO_6_IP_UDP: \
		result = 24; \
		break; \
	case S10G_FILTER_PROTO_6_IP_TCP_IP_TCP: \
	case S10G_FILTER_PROTO_6_IP_UDP_IP_UDP: \
		result = 40; \
		break; \
	default: \
		result = 4; \
	}

//заголовок данных, следующих за сигнатурой S10G_UPDATE_FILTERS/S10G_UPDATE_FILTERS_2
STRUCT_PACKED_BEGIN // устанавливаем выравнивание структур в 1 байт
typedef struct STRUCT_PACKED_ATTRIBUTE {
  guint32 sequence; // 0 - начало передачи группы пакетов, содержащих единый список сессий; пакет, содержащий count == 0, явлется последним в группе
  guint32 count; // количество элементов (описателей сессий) в массиве, следующим за данной структурой в принимаемых данных,
								 // тип элемента - S10G_FILTER_ITEM_STRUCT (S10G_UPDATE_FILTERS),  S10G_FILTER_ITEM_STRUCT_2 (S10G_UPDATE_FILTERS_2)
}	S10G_UPDATE_FILTERS_HEADER_STRUCT; //обновить список активных TCP/IP(UDP/IP)-сессий
STRUCT_PACKED_END // восстанавливаем выравнивание структур по умолчанию

STRUCT_PACKED_BEGIN // устанавливаем выравнивание структур в 1 байт
typedef struct STRUCT_PACKED_ATTRIBUTE {
	guint32 data;  //data - может быть одним из:
#define S10G_FILTER_SUB_OK 0x0908181f
#define S10G_FILTER_ADD_OK 0x09081820
#define S10G_FILTER_TOOMANYFILTERS 0x09081821   //Ошибка - слишком много фильтров установлено, установка не выполнена
#define S10G_NEED_PARAMS  0x09081822    //Команда вернуть данные
} S10G_RES_FILTER_STRUCT, S10G_GET_PARAMS_STRUCT; //ответ съемника или короткая команда на съемник
STRUCT_PACKED_END // восстанавливаем выравнивание структур по умолчанию

STRUCT_PACKED_BEGIN // устанавливаем выравнивание структур в 1 байт
typedef struct STRUCT_PACKED_ATTRIBUTE {
	unsigned char t1;       //температура_процессора_1 ГРАДУС
	unsigned char t2;       //температура_процессора_2 ГРАДУС
	unsigned char tb;       //температура_системного_блока ГРАДУС
	unsigned char s1;       //скорости_вращения_вентилятора_1 ОБ/МИН
	unsigned char s2;       //скорости_вращения_вентилятора_2 ОБ/МИН
	unsigned char s3;       //скорости_вращения_вентилятора_3 ОБ/МИН
	unsigned char s4;       //скорости_вращения_вентилятора_4 ОБ/МИН
	unsigned char s5;       //скорости_вращения_вентилятора_5 ОБ/МИН
	unsigned char tx;       //работоспособности_сетевых_интерфейсов 1 ИЛИ 0
	unsigned char rx;       //работоспособности_сетевых_интерфейсов 1 ИЛИ 0
	unsigned char rx1;      //объем_информации_проходящей_через_интерфейсы_съема_и_принятый байт/сек
	unsigned char rx2;      //объем_информации_проходящей_по_контролируемой_сети байт/сек
} S10G_REQ_PARAMS_STRUCT; //Возвращаемые параметры работы со съемника
STRUCT_PACKED_END // восстанавливаем выравнивание структур по умолчанию

STRUCT_PACKED_BEGIN // устанавливаем выравнивание структур в 1 байт
typedef struct STRUCT_PACKED_ATTRIBUTE {
  guint32 update_period; // период посылки сообщений типа S10G_UPDATE_FILTERS (S10G_UPDATE_HASH)
                                  // задается в миллисекундах
}	S10G_SET_FILTER_PARAM_STRUCT; //параметры функции активной фильтрации
STRUCT_PACKED_END // восстанавливаем выравнивание структур по умолчанию

STRUCT_PACKED_BEGIN // устанавливаем выравнивание структур в 1 байт
typedef struct STRUCT_PACKED_ATTRIBUTE {
	guint32 signature;
	union	{																						// сигнатура								| контейнер
		S10G_FILTER_ITEM_STRUCT add;										// S10G_ADD_FILTER					| добавить фильтр
		S10G_FILTER_ITEM_STRUCT_2 add_2;								// S10G_ADD_FILTER_2				| добавить фильтр
		S10G_FILTER_ITEM_STRUCT_2_PACKED add_2_packed;	// S10G_ADD_FILTER_2_PACKED	| добавить фильтр - упакованный вариант
		S10G_UPDATE_FILTERS_HEADER_STRUCT upd;					// S10G_UPDATE_FILTERS			| обновить список активных фильтров
																										// S10G_UPDATE_FILTERS_2		| обновить список активных фильтров
		S10G_RES_FILTER_STRUCT res;											// S10G_RES_FILTER					| возвращаемый от съемника ответ на изменение фильтра
		S10G_GET_PARAMS_STRUCT get;											// S10G_GET_PARAMS					| получить параметры со съемника - команда посылается на съемник
		S10G_REQ_PARAMS_STRUCT req;											// S10G_REQ_PARAMS					| получить параметры со съемника - возвращаемые данные со съемника
		S10G_SET_FILTER_PARAM_STRUCT set;								// S10G_SET_FILTER_PARAM		| передать параметры фильтрации на съемник
	};
}	S10G_NETWORK_PROTOCOL;
STRUCT_PACKED_END // восстанавливаем выравнивание структур по умолчанию

//съемник принимает UDP пакеты с таким содержимым и отсылает их на тот-же адрес, откуда пришел пакет
//один пакет - одна команда
//если размер пакета неправильный (сейчас это 16 байт и 8 байт) или сигнатура-команда несоответствуют - то он просто молчит
//Вот такие мысли пока

#endif
