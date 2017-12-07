/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/*
 * ВНИМАНИЕ! Данный файл распространяется под авторским правом РАЗРАБОТЧИКА данного файла.
 * Любые изменения в данном файле СТОРОННИМИ разработчиками НЕДОПУСТИМЫ.
 * Для использования данного файла просто включите его в проект с помощью директивы #include.
 */
/* общие требования к плагинам
 *   - плагины должны быть выполнены в виде динамически исполняемых библиотек (DLL)
 *   - DLL-модули могут иметь любое имя и расширение ".dll"
 *   - DLL-модули должны быть расположены в каталоге '<каталог EXE-модуля>\plugins' или
 *       в его подкаталогах любого уровня вложения
 *   - функции, экспортируемые библиотекой, должны иметь недекорируемые (naked) имена
 *   - функции, экспортируемые библиотекой, должны поддерживать MSCU_CALL_PREFIX - stdcall (__stdcall) соглашение о вызове
 */
/* swine_api.h
 *
 * Plugin API for Swine 0.9 (War Pig 0.9, War Hog 0.8)
 *
 * War Pig (wrpg) - Network Protocol Dissector
 * Copyright (C) 2002-2017 MSC, ORG
 */
//
// Изменения
// ---------
/// - [+] 2017-11-04 - Добавлено - поле TPacketInfo::session_id (см. документацию);
/// - [+] 2017-08-30 - Добавлено - новые типы данных - PDT_ISTAT1, PDT_ISTAT2, PDT_ISTAT3 (см. документацию);
/// - [*] 2017-07-13 - Изменено - описание констант SWINE_PI_FLAG_XXX для TPacketInfo::flags (см. документацию);
/// - [*] 2017-07-13 - Изменено - описание функции plug_proto_ack_raw (см. документацию);
/// - [+] 2017-06-13 - Добавлено - функция plug_proto_complex_teri_match_retro (см. документацию);
/// - [+] 2017-06-02 - Добавлено - функция plug_proto_ack_raw (см. документацию);
/// - [+] 2017-06-02 - Добавлено - функция plug_proto_complex_teri_match (см. документацию);
/// - [+] 2016-11-30 - Добавлено: новый тип данных - PDT_IDLE (см. документацию);
/// - [+] 2016-11-24 - Добавлено - функция plug_proto_srm_set_secondary_token2 (см. документацию);
/// - [+] 2016-11-24 - Добавлено - функция plug_proto_srm_set_secondary_token (см. документацию);
/// - [+] 2016-11-13 - Добавлено - функция packet_info_tokens_clone;
/// - [+] 2016-10-23 - Добавлено - функция plug_proto_add_filter_2
/// - [+] 2016-10-23 - Добавлено - функция plug_proto_sub_filter_2
/// - [+] 2016-07-13 - Добавлено - field <offset> to the tvbuff_t structure
/// - [+] 2016-05-11 - Добавлено - функция plug_packet_info_set_id_token_path;
/// - [+] 2016-05-11 - Добавлено - функция plug_packet_info_set_id_token_path;
/// - [+] 2016-05-11 - Добавлено - поле token_items в структуру _TPacketInfo
/// - [+] 2016-04-10 - Добавлено - функция plug_proto_srm_teri_match
/// - 2015-06-01 - Добавлено - поддержка кодировки UTF-8 в значениях атрибутов;
/// - 2015-02-05 - Изменено - поле is_p2p структуры _TPacketInfo переименовано в is_p2p_or_ext и теперь содержит значение поля Ext заголовка <Паровоз>
/// - 2014-07-21 - Добавлено - поле tv2 в структуру _TPacketInfo
/// - 2014-06-27 - добавлено - функция plug_proto_dissector_try_heuristic_and_ack_ex_svc
/// - 2014-06-27 - добавлено - функция plug_proto_dissector_try_port_and_ack_ex_svc
/// - 2014-06-27 - добавлено - функция plug_proto_forward_packet_and_ack_ex_svc
/// - 2014-06-27 - добавлено - функция plug_proto_ack_ex_svc
/// - 2012-08-16 - добавлено - новый тип данных - PDT_RAW_IP - регистрация IP-пакетов (для служебных целей);
/// - 2012-05-02 - добавлено - функция Tplug_file_read plug_file_read;
/// - 2011-05-11 - добавлено - функция plug_proto_add_filter
/// - 2011-05-11 - добавлено - функция plug_proto_sub_filter
/// - 2011-01-04 - изменено - описание функции Tpacket_info_ex_set_ident_info
/// - 2010-08-20 - изменено - поведение функции plug_heur (отменен вызов plug_crop - см. документацию)
/// - 2010-06-25 - добавлено - новый тип данных - PDT_ISTAT - статистические данные (идентификаторы);
/// - 2010-06-02 - добавлено - новый тип данных - PDT_STAT - статистические данные;
/// - 2010-05-24 - удалено - функция plug_proto_forward_packet_interlocked из структуры TSWINEStandartFunctions
/// - 2010-05-24 - удалено - функция plug_proto_dissector_try_port_interlocked из структуры TSWINEStandartFunctions
/// - 2010-05-24 - удалено - функция plug_proto_dissector_try_heuristic_interlocked из структуры TSWINEStandartFunctions
/// - 2010-05-24 - удалено - функция plug_proto_forward_packet_and_ack_interlocked из структуры TSWINEStandartFunctions
/// - 2010-05-24 - удалено - функция plug_proto_dissector_try_port_and_ack_interlocked из структуры TSWINEStandartFunctions
/// - 2010-05-24 - удалено - функция plug_proto_dissector_try_heuristic_and_ack_interlocked из структуры TSWINEStandartFunctions
/// - 2010-05-24 - удалено - функция plug_proto_forward_packet_and_ack_ex_interlocked из структуры TSWINEStandartFunctions
/// - 2010-05-24 - удалено - функция plug_proto_dissector_try_port_and_ack_ex_interlocked из структуры TSWINEStandartFunctions
/// - 2010-05-24 - удалено - функция plug_proto_dissector_try_heuristic_and_ack_ex_interlocked из структуры TSWINEStandartFunctions
/// - 2010-05-24 - переход в однопоточный режим работы
/// - 2010-05-23 - функция - plug_file_close - реализована
/// - 2010-05-23 - функция - plug_file_write - реализована
/// - 2010-05-23 - функция - plug_file_create - реализована
/// - 2010-04-19 - добавлена новая функциональность XXX_ack_XXX
/// - 2010-04-19 - добавлено - функция Tplug_file_create plug_file_create;
/// - 2010-04-19 - добавлено - функция Tplug_file_write plug_file_write;
/// - 2010-04-19 - добавлено - функция Tplug_file_close plug_file_close;
/// - 2010-04-19 - удалено - константы MT_XXX (типы сообщений) - определены в mscu_types.h
/// - 2010-02-27 - удалено - функции Tplug_g_malloc, Tplug_g_malloc0, Tplug_g_realloc, Tplug_g_free
/// - 2010-02-24 - изменено - функции Tplug_packet_info_XXX переименованы в Tpacket_info_XXX
/// - 2010-02-17 - добавлено - тип Tplug_proto_find_stuff_by_dissector
/// - 2010-02-17 - добавлено - тип Tset_swine_current_module_name
/// - 2010-02-17 - добавлено - тип Tplug_proto_register_protocol_wud_always_enabled
/// - 2010-02-17 - добавлено - тип Tplug_proto_register_protocol_wud
/// - 2010-02-17 - добавлено - тип Tplug_proto_register_protocol_always_enabled
/// - 2010-02-17 - добавлено - тип Tplug_prefs_register_protocol_always_enabled
/// - 2010-02-17 - добавлено - тип Tplug_create_wud
/// - 2010-02-15 - незначительные изменения типов
/// - 2009-12-02 - добавлено - AT_DVB_MAC
/// - 2009-11-01 - добавлено - функция wtap_encap_register (!Изменения несовместимы с предыдущим API!)
/// - 2009-11-01 - добавлено - функция wtap_encap_get_vals (!Изменения несовместимы с предыдущим API!)
/// - 2009-10-14 - добавлено - функция register_field_info (!Изменения несовместимы с предыдущим API!)
/// - 2009-08-02 - добавлено - команда PERFORM_COMMAND_START_TEST (для декодеров)
/// - 2009-08-02 - добавлено - команда PERFORM_COMMAND_STOP_TEST (для декодеров)
/// - 2009-08-02 - изменено - названия полей TPluginProtoClass
/// - 2009-07-31 - имзменено - новая трактовка поля cbSize в структуре TSWINEStandartFunctions.
/// - 2009-07-31 - добавлено - интерфейс для декодеров. !ВНИМАНИЕ! Добавлены новые функции в TSWINEStandartFunctions.
/// - 2009-05-14 - удалено - PREFS_XXX-функции из структуры TSWINEStandartFunctions
/// - 2009-05-14 - добавлено - Tplug_packet_info_set_token_path
/// - 2009-02-23 - добавлено - Tplug_packet_info_set_token_path
/// - 2009-02-23 - добавлено - Tplug_packet_info_set_token_entry
/// - 2009-02-23 - Tplug_packet_info_set_description -> Tplug_packet_info_ex_set_description
/// - 2009-02-23 - Tplug_packet_info_set_generic_name -> Tplug_packet_info_ex_set_generic_name
/// - 2009-02-23 - перестановка полей - PacketInfo <-> PacketInfoEx
/// - 2009-02-23 - Tplug_packet_info_set_content_type -> Tplug_packet_info_ex_set_content_type
/// - 2009-02-23 - Tplug_packet_info_set_auth_info -> Tplug_packet_info_ex_set_auth_info
/// - 2009-02-23 - Tplug_packet_info_set_ident_info -> Tplug_packet_info_ex_set_ident_info
/// - 2009-02-22 - добавлено - Tplug_packet_info_ex_clone
/// - 2009-02-22 - добавлено - Tplug_packet_info_ex_clear
/// - 2009-02-22 - добавлено - Tplug_packet_info_ex_free
/// - 2009-02-22 - добавлено - Tplug_packet_info_ex_malloc
/// - 2009-02-21 - добавлено - TPacketInfoEx
/// - 2009-02-21 - добавлено - ack_ex-функция
/// - 2009-02-21 - добавлено - and_ack_ex-функции
/// - 2009-02-21 - добавлено - and_ack-функции
/// - 2009-02-21 - добавлено - interlocked-функции
/// - 2009-01-27 - добавлено - prefs_XXX-функции
/// - 2008-10-29 - TPacketInfo - удалено поле "packetlen"
/// - 2008-10-29 - TPacketInfo - удалено поле "file_size"
/// - 2008-10-29 - TPacketInfo - поля "flags" и "tcp_flags" - объединение
/// - 2008-10-29 - TPacketInfo - добавлено "CT_ODLC"
/// - 2008-10-29 - TPacketInfo - удалено поле "odlc_addr"
/// - 2008-10-29 - TPacketInfo - удалено поле "odlc_session"
/// - 2008-10-29 - TPacketInfo - удалено поле "ethertype"
/// - 2008-10-29 - TPacketInfo - удалено поле "packetcounter"
/// - 2008-10-29 - TPacketInfo - удалено поле "packettype"
/// - 2008-10-29 - TPacketInfo - удалено поле "hec_err"
/// - 2008-10-29 - TPacketInfo - "token_entry" -> "token_enries"
/// - 2008-11-14 - добавлена функция Tplug_add_log
/// - 2008-11-14 - добавлена типы сообщений для Tplug_add_log
/// - 2008-11-14 - функция Tplug_perform - изменение параметров
/// - 2008-11-14 - функция Tplug_ack - изменение параметров
/// - 2008-12-10 - добавлено - prefs_XXX-функции
//
///TODO:
/// - добавить file_read
/// - удалить cache
#pragma once

#if !defined(SWINE_PLUG_IF_INC)
#define SWINE_PLUG_IF_INC

#include <mscu_types.h>
#include <teri_bis/teri_bis.h>
#include <prefs/prefs.h>
#include <ffsrm.h>
#include <vector>

/******************************************************************************/
/*                                                                            */
/*                    алгоритм работы сервера плагинов                        */
/*                                                                            */
/******************************************************************************/

/*
 * 1. После запуска сервер сканирует подкаталог "plugins" каталога, где расположен exe-файл (включая
 *    подкаталоги), на предмет наличия dll-файлов с расширением ".dll". Очередной найденный файл
 *    загружается и в нем проверяется наличие определенных экспортируемых функций
 *      swine_plugin_init
 *
 * 2. Вызывается функция swine_plugin_init.
 */

/******************************************************************************/
/*                                                                            */
/*                      интерфейс плагина-обработчика                         */
/*                                                                            */
/******************************************************************************/

/*
 * в библиотеке должны быть реализованы следующие экспортируемые функции (обязательно все!):
 * "swine_plugin_init"
 */

/*****************************************************************************/

const gconstpchar SWINE_VERSION = "swine 0.8.7";

/* заглушки внутренних типов данных */
typedef gpointer PkrTreeNode;
class TProtoReg;
typedef TProtoReg * PProtoReg;
/*void*/class TkrProtocol;

#define SWINE_STR_SIZE 128 /* размер буферов строк с завершающим нулем, передаваемых в функцию init_buf */

/* структура буфера, с которым работают декодеры и обработчики протоколов  */
STRUCT_PACKED_BEGIN
typedef struct STRUCT_PACKED_ATTRIBUTE _tvbuff {
  gsize_t len; /* размер данных */
  guint8* buf; /* сами данные (пока в таком виде) */
	gsize_t offset; // data link offset (number of bytes to the "left" of buf pointer)
} tvbuff_t;
STRUCT_PACKED_END

/***********************************************************************************/
// направление
// первое значение - всегда 0
#define P2P_DIR_UNKNOWN   0
#define P2P_DIR_SENT      1
#define P2P_DIR_RECV      2

#define P2P_DIR_COUNT     3

// размеры строк
#define PI_SRC_SIZE     32        // источник
#define PI_DST_SIZE     32        // назначение
#define PI_CONTENT_SIZE 12        // тип данных

/* packet data type */
#define PDT_AUX     0
#define PDT_INFO    1
#define PDT_VPN     2 // !ready to delete!
#define PDT_VOIP    3 // !ready to delete!
#define PDT_AUTH    4
#define PDT_STAT    5 // statistics
#define PDT_ISTAT   6 // статистические данные (идентификационная информация) - общее назначение
#define PDT_RAW_IP  7 // raw ip packets - auxiliary
#define PDT_IDLE    8 // service idle packet - no data
#define PDT_ISTAT1  6 // статистические данные (идентификационная информация) - в формате <2И> (соответствует PDT_ISTAT)
#define PDT_ISTAT2  9 // статистические данные (идентификационная информация) - в формате <Приказ 83>
#define PDT_ISTAT3  10 // статистические данные (идентификационная информация) - в формате <НТ>

/* известные типы состояния CRC */
typedef enum _TCRCType {
  CRC_NONE,              /* нет CRC */
  CRC_OK,               /* хорошее CRC */
  CRC_BAD             /* CRC плохое */
} TCRCType;

/* IP-адрес */
STRUCT_PACKED_BEGIN
typedef struct STRUCT_PACKED_ATTRIBUTE _SunB {
  gbyte s_b1, s_b2, s_b3, s_b4;
} SunB;
STRUCT_PACKED_END

STRUCT_PACKED_BEGIN
typedef struct STRUCT_PACKED_ATTRIBUTE _SunW {
  gword s_w1, s_w2;
} SunW;
STRUCT_PACKED_END

STRUCT_PACKED_BEGIN
typedef struct STRUCT_PACKED_ATTRIBUTE _TInAddr {
  union {
    SunB S_un_b;
    SunW S_un_w;
    guint32 S_addr;
  };
} TInAddr, * PInAddr;
STRUCT_PACKED_END

STRUCT_PACKED_BEGIN
typedef struct STRUCT_PACKED_ATTRIBUTE _TIn6Addr {
  union {
    guint8    bytes[16];
    guint16   words[8];
    guint32  qwords[4];
  };
} TIn6Addr, * PIn6Addr;
STRUCT_PACKED_END

// Ethernet-адрес
STRUCT_PACKED_BEGIN
typedef struct STRUCT_PACKED_ATTRIBUTE _TEthAddr {
  guint8 s_b[6];
} TEthAddr, * PEthAddr;
STRUCT_PACKED_END

// "неизвестный"-адрес
typedef union _TAddrPad {
  guint8 s_b[16];
  guint16 s_w[8];
} TAddrPad, * PAddrPad;

/* типы известных адресов */
typedef enum _TAddressType {
  AT_NONE,              /* no link-layer address */
  AT_ETHER,             /* MAC (Ethernet, 802.x, FDDI) address */
  AT_IPv4,              /* IPv4 */
  AT_IPv6,              /* IPv6 */
  AT_IPX,               /* IPX */
  AT_SNA,               /* SNA */
  AT_ATALK,             /* Appletalk DDP */
  AT_VINES,             /* Banyan Vines */
  AT_OSI,               /* OSI NSAP */
  AT_ARCNET,            /* ARCNET */
  AT_FC,                /* Fibre Channel */
  AT_SS7PC,             /* SS7 Point Code */
  AT_DVB_MAC            /* DVB DSM-CC MPE MAC address */
} TAddressType;

/* обобщенная структура адреса */
typedef union _TAddress {
  TInAddr in_addr;
  TIn6Addr in6_addr;
  TEthAddr eth_addr;
  TAddrPad pad;
} TAddress, * PAddress;

/* типы портов */
typedef enum _TPortType {
  PT_NONE,              /* no port number */
  PT_SCTP,              /* SCTP */
  PT_TCP,               /* TCP */
  PT_UDP,               /* UDP */
  PT_IPX,               /* IPX sockets */
  PT_NCP,               /* NCP connection */
  PT_EXCHG,             /* Fibre Channel exchange */
  PT_DDP                /* DDP AppleTalk connection */
} TPortType;

/* типы идентификаторов цепи */
typedef enum _TCircuitType {
  CT_NONE,              /* no port number */
  CT_DLCI,              /* Frame Relay DLCI */
  CT_ISDN,              /* ISDN channel number */
  CT_X25,               /* X.25 logical channel number */
  CT_MPEG_TS,           /* MPEG-TS PID number */
  CT_ODLC               /* ODLC session */
  /* Could also have ATM VPI/VCI pairs */
} TCircuitType;

/* жанр пакета */
#define PG_OK        0 /* готовый */
#define PG_BAD       1 /* плохой */
#define PG_UNKNOWN   2 /* неизвестный */
#define PG_NONE      3 /* неопределенный */

/* флаги TCP-сессии */
#define SF_HAS_SYN1         0x0001 /* был флаг SYN 1 */
#define SF_HAS_SYN2         0x0002 /* был флаг SYN 2 */
#define SF_HAS_FIN1         0x0004 /* был флаг FIN 1 */
#define SF_HAS_FIN2         0x0008 /* был флаг FIN 2 */
#define SF_HAS_SYN          0x0010 /* был флаг SYN */
#define SF_HAS_SYN_ACK      0x0020 /* был флаг SYN/ACK */
#define SF_HAS_DIRECT       0x0040 /* были данные прямого направления */
#define SF_HAS_INDIRECT     0x0080 /* были данные обратного направления */
#define SF_HOLES            0x0100 /* были дырки */
#define SF_HAS_ACK_TO_FIN1  0x0200 /* был флаг ACK на FIN 1 */
#define SF_HAS_ACK_TO_FIN2  0x0400 /* был флаг ACK на FIN 2 */
#define SF_HAS_ADD_SUB_FILTER_BLOCKING  0x0800 /* блокирование команд добавления/удаления хэш-фильтра */

//   /* заголовок пакета */
// STRUCT_PACKED_BEGIN
// typedef struct STRUCT_PACKED_ATTRIBUTE _TPacketHeader {
//   gpchar buf; /* данные заголовка */
//   gsize_t len; /* размер данных */
//   _TPacketHeader * next; /* указатель на следующий (внутренний) заголовок */
// } TPacketHeader, * PPacketHeader;
// STRUCT_PACKED_END

//   /* концевик пакета */
// STRUCT_PACKED_BEGIN
// typedef struct STRUCT_PACKED_ATTRIBUTE _TPacketTrailer {
//   gpchar buf; /* данные концевика */
//   gsize_t len; /* размер данных */
//   _TPacketTrailer * next; /* указатель на следующий (внешний) концевик */
// } TPacketTrailer, * PPacketTrailer;
// STRUCT_PACKED_END

STRUCT_PACKED_BEGIN
typedef struct STRUCT_PACKED_ATTRIBUTE { /* массив вхожений */
  gpchar buf; /* указатель на первый символ вхождения (не внутри буфера поиска!) */
  gint32 len; /* количество символов во вхождении */
} Ttoken_entry;
STRUCT_PACKED_END

typedef Ttoken_entry Ttoken_entries[8];

// 2016-05-11
struct _Tpacket_info_token_item; // forward declaration

// 2016-05-11
STRUCT_PACKED_BEGIN
typedef struct STRUCT_PACKED_ATTRIBUTE _Tpacket_info_token_item {
  guint32 token_id;								// token identifier
  gpchar token_path;							// token path
  Ttoken_entries token_entries;		// entries array
	_Tpacket_info_token_item * next;	// pointer to the next item
} Tpacket_info_token_item;
STRUCT_PACKED_END

/* информация о пакете
   Не рекомендуется использовать данную структуру по значению (только по указателю)
   Для создания, удаления, очистки и клонирования экземпляра необходимо использовать функции
     Tpacket_info_malloc, Tpacket_info_free, Tpacket_info_clear, Tpacket_info_clone
 */
STRUCT_PACKED_BEGIN
typedef struct STRUCT_PACKED_ATTRIBUTE {
//   gsize_t cb;

  /*gpointer*/TkrProtocol * pred_proto; /* указатель на обработчик предыдущего протокола */
  gpointer pred_node; /* указатель на предыдущий элемент дерева */

  guint32 pid; // PID
  guint32 lid; // LID

  Ttimeval tv; /* packet arrival time - метка времени - начало */

  guint32  pattern; /* значение, по которому было перенаправление */

  guint8  lnk_t;            /* Per-packet encapsulation/data-link type */
  guint8  genre;            /* жанр пакета. по-умолчанию PG_POST (0). рекомендуется устанавливать только при отправке пакета */
  guint8  p2p_dir;          /* направление передачи */
  guint8  packet_data_type; /* тип пакета: служебный/информационный */
  guint8  is_p2p_or_ext;    /* буфер пакета содержит два направления или значение поля Ext заголовка <Паровоз> */
  guint8 quality;           /* packet quality multiplied by 100, 0 means undefined value */
  guint8 crctype;           /* тип (состояние) CRC (checksum) */

  guint8  ipproto;                /* IP-протокол (для не-IP пакетов - другое применение) */
  guint32  flags;                 /* набор флагов 2017-06-10 константы типа SWINE_PI_FLAG_XXX, SGN_ADD_DATA_FLAG_XXX */

  // address block
  guint8 ctype;                /* type of circuit, for protocols with a VC identifier */
  guint8 dltype;               /* type of address */
  guint8 nettype;              /* type of address */
  guint8 ptype;                   /* тип порта */
  guint32 circuit_id;                /* circuit ID, for protocols with a VC identifier */
  TAddress  dl_src;                   /* link-layer source address */
  TAddress  dl_dst;                   /* link-layer destination address */
  TAddress  net_src;                  /* network-layer source address (network-format) */
  TAddress  net_dst;                  /* network-layer destination address (network-format) */
  guint32 srcport;                   /* порт источника (host-format) */
  guint32 destport;                  /* порт приемника (host-format) */

//   gchar content[PI_CONTENT_SIZE]; /* краткое описание - для готовых пакетов /ANSI/ */
//   gpchar description; /* краткое описание - для готовых пакетов; описание ошибки - для плохих и неизвестных пакетов /ANSI/ */
//   gpchar generic_name; /* реальное имя файла */
//   gpchar content_type; /* content-type */
//   gpchar auth_info; /* auth_info */
//   gpchar ident_info; /* ident_info */
  gpchar  header;     /* заголовок */
  guint32 header_len; /* длина заголовка */

  Ttoken_entries* token_entries;
  gpchar token_path; /* путь */

//   PPacketHeader headers; /* заголовки пакета */
//   PPacketTrailer trailers; /* концевики пакета */

//   gpchar private_data;        // дополнительные данные
//   guint32 private_len;        // длина дополнительных данных

  // added: 2014-07-21
  Ttimeval tv2; /* packet departure time - метка времени - завершение */

  // added: 2016-05-11
	Tpacket_info_token_item * token_items;

	// added: 2017-07-21
#define PACKED_INFO_CACHED_UINS_COUNT	4
  guint32 ack_raw_uins[PACKED_INFO_CACHED_UINS_COUNT]; /*  */
	std::vector<guint32> * ack_raw_uins2_or_size; // if size is from 0 to PACKED_INFO_CACHED_UINS_COUNT - uins are in ack_raw_uins

	// added: 2017-11-04
  guint32 session_id;                /* transport level session id (TCP, UDP); if not 0 - defines unique number of current session */
} TPacketInfo, * PPacketInfo;
STRUCT_PACKED_END

/* информация о пакете (дополнительная)
   Не рекомендуется использовать данную структуру по значению (только по указателю)
   Для создания, удаления, очистки и клонирования экземпляра необходимо использовать функции
     Tpacket_info_ex_malloc, Tpacket_info_ex_free, Tpacket_info_ex_clear, Tpacket_info_ex_clone
 */
STRUCT_PACKED_BEGIN
typedef struct STRUCT_PACKED_ATTRIBUTE {
  gchar content[PI_CONTENT_SIZE]; /* краткое описание - для готовых пакетов /ANSI/ */
  gpchar description; /* краткое описание - для готовых пакетов; описание ошибки - для плохих и неизвестных пакетов /ANSI/ */
  gpchar generic_name; /* реальное имя файла */
  gpchar content_type; /* content-type */
  gpchar auth_info; /* auth_info */
  gpchar ident_info; /* ident_info */
} TPacketInfoEx, * PPacketInfoEx;
STRUCT_PACKED_END

/* экземпляр класса "протокол" */
STRUCT_PACKED_BEGIN
struct STRUCT_PACKED_ATTRIBUTE TPluginProtoStuff {
  gpointer plug_inst; /* экземпляр плагина */
  gpointer swine_inst; /* экземпляр плагина внутри SWINE */
};
STRUCT_PACKED_END
typedef TPluginProtoStuff* PPluginProtoStuff;

/* key/field type for dissector table */
// #define KT_UINT8   0
// #define KT_UINT16  1
typedef enum {
  KT_UINT8,
  KT_UINT16
} TKeyType;

/* типы функций для реализации классов "протокол" внутри плагина
 * параметр stuff - экземпляр обработчика
 */

/// \name Спецификация буфера данных для функций register_XXX, ack_XXX
/// \{

/// буфер данных содержит имя файла (строка с завершающим нулем), файл после использования не удаляется
#define SWINE_DATA_BUFFER_FILE_NAME               gsize_t(-1)
/// буфер данных содержит имя файла (строка с завершающим нулем), файл после использования должен быть удален
#define SWINE_DATA_BUFFER_FILE_NAME_UNLINK        gsize_t(-2)
/// буфер данных содержит дескриптор файла, созданного функциями XXX_file_create_XXX, дескриптор и файл после использования не удаляются
#define SWINE_DATA_BUFFER_FILE_HANDLE             gsize_t(-3)
/// буфер данных содержит дескриптор файла, созданного функциями XXX_file_create_XXX, дескриптор и файл после использования должны быть удалены
#define SWINE_DATA_BUFFER_FILE_HANDLE_UNLINK      gsize_t(-4)

/// \}

/// \name Команды для функции perform
/// \{
/// \sa Ttcpcat_plug_perform

/// построение обработчиков
#define PERFORM_COMMAND_BUILD       0
/// связывание обработчиков
#define PERFORM_COMMAND_BIND        1
/// команда, предписывающая обработчику запустить режим обработки
#define PERFORM_COMMAND_START       2
/// команда, предписывающая обработчику остановить режим обработки
#define PERFORM_COMMAND_STOP        3
/// команда, предписывающая обработчику запустить режим теста
#define PERFORM_COMMAND_START_TEST  4
/// команда, предписывающая обработчику остановить режим теста
#define PERFORM_COMMAND_STOP_TEST   5
/// команда, предписывающая обработчику выполнить фоновые операции
#define PERFORM_COMMAND_IDLE        6
/// команда, предписывающая обработчику завершить обработку с регистрацией данных ("мягкое" завершение)
#define PERFORM_COMMAND_FLUSH       7
/// команда, предписывающая обработчику приостановить возможные таймеры
#define PERFORM_COMMAND_SUSPEND     8
/// команда, предписывающая обработчику возобновить работу возможных таймеры
#define PERFORM_COMMAND_RESUME      9
/// команда, предписывающая обработчику очистить статистику
#define PERFORM_COMMAND_CLEAN      10

/// \}

/// константы для использования внутри ack_raw::flags (SGN_DATA_READY_FLAG_DO_MULTICAST_COPY внутри wrlr)
#define SWINE_ACK_RAW_AAA_DO_MULTICAST_COPY   0x00000001 // предписывает приложению, помимо отправки пакета на выход, также передать его на вход остальным SGN-обработчикам
                                                         // в других функционирующих приложениях с флагом SGN_ADD_DATA_FLAG_DO_NOT_MULTICAST_COPY
#define SGN_DATA_READY_FLAG_DO_MULTICAST_COPY	0x00000001 // deprecated: для совместимости


/// константы для использования внутри TPacketInfo::flags (SGN_AddData_p::flags)
/// в основном используются при вызове plug_crop, plug_heur
#define SWINE_PI_FLAG_SGN_DO_NOT_MULTICAST_COPY 0x00000001 // запрещает SGN-обработчику посылать данный пакет на выход с флагом SGN_DATA_READY_FLAG_DO_MULTICAST_COPY
                                                           // используется, если пакет уже был передан другим SGN-обработчиком с флагом SGN_DATA_READY_FLAG_DO_MULTICAST_COPY
                                                           // данный флаг необходим для предотвращения зацикливания между WRLR
#define SGN_ADD_DATA_FLAG_DO_NOT_MULTICAST_COPY 0x00000001 // deprecated: для совместимости

#define SWINE_PI_FLAG_SGN_REQUEST_USER_INFO 0x00000002		 // команда запроса информации по абоненту
                                                           // предполагается, что входной буфер содержит данные одноименной команды протокола СОРМ-САЛО #7 (поля UNI, Ext, Data),
                                                           // за исключением общих полей: UNI-C,TvSec, TvUSec, Length (см. описание протокола)
#define SGN_ADD_DATA_FLAG_REQUEST_USER_INFO 0x00000002		 // deprecated: для совместимости

#define SWINE_PI_FLAG_SGN_REQUEST_USER_LOCATION 0x00000004 // команда запроса текущего местоположения абонента
                                                           // предполагается, что входной буфер содержит данные одноименной команды протокола СОРМ-САЛО #8 (поле UNI),
                                                           // за исключением общих полей: UNI-C,TvSec, TvUSec, Length (см. описание протокола)
#define SGN_ADD_DATA_FLAG_REQUEST_USER_LOCATION 0x00000004 // deprecated: для совместимости

/* конструктор
 * вызывается при создании экземпляра данного класса
 * результат:
 *   адрес на выделенный плагином экземпляр внутренних данных (записывается в поле SWINEStuff.plug_inst)
 */
typedef gpointer (MSCU_CALL_PREFIX * Tplug_create)(PPluginProtoStuff stuff);
/* конструктор
 * вызывается при создании экземпляра данного класса
 * user_data - параметр, переданной в функцию proto_register_protocol_wud
 * результат:
 *   адрес на выделенный плагином экземпляр внутренних данных (записывается в поле SWINEStuff.plug_inst)
 */
typedef gpointer (MSCU_CALL_PREFIX * Tplug_create_wud)(PPluginProtoStuff stuff, gpointer user_data);
/* деструктор
 *   должен освободить выделенный плагином экземпляр внутренних данных (адрес находится в поле SWINEStuff.plug_inst)
 */
typedef void (MSCU_CALL_PREFIX * Tplug_destroy)(PPluginProtoStuff stuff);
/* выполнение дествия (зависит от command)
 * PERFORM_COMMAND_BUILD
 *   используется для регистрации обработчиков и таблиц (plug_proto_register_dissector,
 *   plug_proto_register_dissector_table, plug_proto_register_heur_dissector_list)
 * PERFORM_COMMAND_BIND
 *   связка обработчиков
 *   используется для поиска обработчиков и добавления обработчиков в таблицы (plug_proto_find_dissector,
 *   plug_proto_dissector_add, plug_proto_heur_dissector_add)
 * PERFORM_COMMAND_START
 *   запуск обработчика
 *   вызывается в начале процесса обработки
 * PERFORM_COMMAND_STOP
 *   останов обработчика
 *   вызывается в конце процесса обработки
 * PERFORM_COMMAND_START_TEST
 *   запуск обработчика в тестовом режиме (только для декодеров)
 *   вызывается в начале процесса анализа
 * PERFORM_COMMAND_STOP_TEST
 *   останов обработчика в тестовом режиме (только для декодеров)
 *   вызывается в конце процесса анализа
 * PERFORM_COMMAND_IDLE
 *   простой, выполнение действий по таймауту
 * 	 вызывается с периодом, равным 1 сек или 100 мсек
 * PERFORM_COMMAND_FLUSH
 *   очистка внутренных буферов ожидания обработчика перед завершением режима обработки
 * PERFORM_COMMAND_SUSPEND
 *   приостановка обработки, резервирование временных меток
 * PERFORM_COMMAND_RESUME
 *   возобновление обработки, корректировка временных меток, зарезервированных при последнем PERFORM_COMMAND_SUSPEND
 *
 * результат:
 *   если 0, операция завершилась с ошибками
 *   если не 0, операция прошла успешно
 */
typedef gboolean (MSCU_CALL_PREFIX * Tplug_perform)(PPluginProtoStuff stuff, gint command);
/* обработка входящего пакета
 * параметры:
 *   tvb - буфер с содержимым пакета
 *   pi - информация о пакете; содержит как внутреннюю служебную информацию, так и специфическую
 *        для конкретных стеков протоколов
 *   tree - информационное дерево пакета; если nil, то нужно произвести обработку пакета;
 *          если не nil, то пакет считается обработанным и в tree можно добавить информацию о пакете для
 *          визуального отображения
 */
typedef void (MSCU_CALL_PREFIX * Tplug_crop)(PPluginProtoStuff stuff, tvbuff_t* tvb, PPacketInfo pi, PkrTreeNode tree);
/* эвристическое обнаружение обработчиком "своего" пакета
 * параметры:
 *   tvb - буфер с содержимым пакета
 *   pi - информация о пакете; содержит как внутреннюю служебную информацию, так и специфическую
 *        для конкретных стеков протоколов
 * результат:
 *   если не 0, то обработчик считает, что это его пакет, после чего ядро, НЕ НАПРАВЛЯЕТ этот пакет
 *   в метод plug_crop данного обработчика (считается, что он уже вызван внутри plug_heur)
 *   Примечание. Если планируется возвращать 0, при этом модифицируя pi (включая вызов ack-функций),
 *   то необходимо предварительно склонировать pi при помощи packet_info_clone (с последующим удалением по packet_info_free)
 *   и использовать клон в своих целях, оставляя оригинальный pi неизмененным.
 */
typedef gboolean (MSCU_CALL_PREFIX * Tplug_heur)(PPluginProtoStuff stuff, tvbuff_t* tvb, PPacketInfo pi);
/* получение состояния работы обработчика
 * параметры:
 *   tree - информационное дерево, в которое нужно занести информацию о состоянии
 */
typedef void (MSCU_CALL_PREFIX * Tplug_info)(PPluginProtoStuff stuff, PkrTreeNode tree);

/* функции класса "протокол" */
STRUCT_PACKED_BEGIN
struct STRUCT_PACKED_ATTRIBUTE TPluginProtoClass {
  Tplug_create  plug_create; // при wud - Tplug_create_wud
  Tplug_destroy plug_destroy;
  Tplug_perform plug_perform;
  Tplug_crop    plug_crop;
  Tplug_heur    plug_heur;
  Tplug_info    plug_info;
};
STRUCT_PACKED_END
typedef TPluginProtoClass* PPluginProtoClass;

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/* стандартные функции */

// возвращает строку, соответствующюю целому значению
typedef gconstpchar (MSCU_CALL_PREFIX * Tplug_val_to_str)(gint32 value, const value_string* glossary, gconstpchar default_value);

// поиск обработчика
//   для данной функции видны только обработчики, зарегистрированные с помощью plug_proto_register_dissector
typedef PPluginProtoStuff (MSCU_CALL_PREFIX * Tplug_proto_find_stuff_by_dissector)(gpointer dissector);

// установка имени текущего модуля регистрации
typedef void (MSCU_CALL_PREFIX * Tset_swine_current_module_name)(gconstpchar name);

/* функции-регистраторы (вызываются из DLL-функции plugin_init) */
// регистратор нового протокола
//   name, short_name, filter_name - полное (для отображения), краткое (для отображения) и внутреннее имя
//   внутреннее имя должно быть уникальным
//   description - описание (для отображения)
//   plug_class - адреса методов класса обработчика (после вызова плагином данной функции, структуру plug_class можно удалять, т.к. содержимое структуры запоминается в ядре обработки)
//   возвращает адрес внутренней структуры, который может быть использован в других функциях
//   !Внимание! если обработчик с данным внутренним именем уже создан, выдается предупреждение и возвращается адрес внутренней структуры, созданной ранее
typedef PProtoReg (MSCU_CALL_PREFIX * Tplug_proto_register_protocol)(gconstpchar name, gconstpchar short_name, gconstpchar filter_name, gconstpchar description, PPluginProtoClass plug_class);
typedef PProtoReg (MSCU_CALL_PREFIX * Tplug_proto_register_protocol_always_enabled)(gconstpchar name, gconstpchar short_name, gconstpchar filter_name, gconstpchar description, PPluginProtoClass plug_class); // 2010-02-17

typedef PProtoReg (MSCU_CALL_PREFIX * Tplug_proto_register_protocol_wud)(gconstpchar name, gconstpchar short_name, gconstpchar filter_name, gconstpchar description, PPluginProtoClass plug_class, gpointer user_data);
typedef PProtoReg (MSCU_CALL_PREFIX * Tplug_proto_register_protocol_wud_always_enabled)(gconstpchar name, gconstpchar short_name, gconstpchar filter_name, gconstpchar description, PPluginProtoClass plug_class, gpointer user_data); // 2010-02-17
// регистратор модуля параметров протокола
// возвращает адрес внутренней структуры, который может быть использован при регистрации параметров
typedef preference_p (MSCU_CALL_PREFIX * Tplug_prefs_register_protocol)(PProtoReg proto);
typedef preference_p (MSCU_CALL_PREFIX * Tplug_prefs_register_protocol_always_enabled)(PProtoReg proto); // 2010-02-17

// регистратор нового декодера
//   name, short_name, filter_name - полное (для отображения), краткое (для отображения) и внутреннее имя
//   внутреннее имя должно быть уникальным
//   description - описание (для отображения)
//   plug_class - адреса методов класса обработчика (после вызова плагином данной функции, структуру plug_class можно удалять, т.к. содержимое структуры запоминается в ядре обработки)
//   возвращает адрес внутренней структуры, который может быть использован в других функциях
//   !Внимание! если обработчик с данным внутренним именем уже создан, выдается предупреждение и возвращается адрес внутренней структуры, созданной ранее
typedef PProtoReg (MSCU_CALL_PREFIX * Tplug_deco_register_decoder)(gconstpchar name, gconstpchar short_name, gconstpchar filter_name, gconstpchar description, PPluginProtoClass plug_class);
// регистратор модуля параметров протокола
// возвращает адрес внутренней структуры, который может быть использован при регистрации параметров
typedef preference_p (MSCU_CALL_PREFIX * Tplug_prefs_register_decoder)(PProtoReg proto);

/* работа со структурой TPacketInfo */
// динамическое создание записи информации о пакете
typedef PPacketInfo (MSCU_CALL_PREFIX * Tpacket_info_malloc)();
// удаление записи
typedef void (MSCU_CALL_PREFIX * Tpacket_info_free)(PPacketInfo PacketInfo);
// очищение полей записи
typedef void (MSCU_CALL_PREFIX * Tpacket_info_clear)(PPacketInfo PacketInfo);
// клонирование записи (создание новой записи с содержимым старой записи)
typedef PPacketInfo (MSCU_CALL_PREFIX * Tpacket_info_clone)(PPacketInfo PacketInfo);
// клонирование признаков записи
typedef void (MSCU_CALL_PREFIX * Tpacket_info_tokens_clone)(PPacketInfo src, PPacketInfo dst);
/* работа со структурой TPacketInfoEx */
// динамическое создание записи информации о пакете
typedef PPacketInfoEx (MSCU_CALL_PREFIX * Tpacket_info_ex_malloc)();
// удаление записи
typedef void (MSCU_CALL_PREFIX * Tpacket_info_ex_free)(PPacketInfoEx PacketInfoEx);
// очищение полей записи
typedef void (MSCU_CALL_PREFIX * Tpacket_info_ex_clear)(PPacketInfoEx PacketInfoEx);
// клонирование записи (создание новой записи с содержимым старой записи)
typedef PPacketInfoEx (MSCU_CALL_PREFIX * Tpacket_info_ex_clone)(PPacketInfoEx PacketInfoEx);
/* изменение описания
 * если buf == 0, то имя очищается
 */
typedef void (MSCU_CALL_PREFIX * Tpacket_info_ex_set_description)(PPacketInfoEx PacketInfoEx, gconstpchar buf);
/* изменение имени файла
 * если buf = nil, то имя очищается
 */
typedef void (MSCU_CALL_PREFIX * Tpacket_info_ex_set_generic_name)(PPacketInfoEx PacketInfoEx, gconstpchar buf);
/* изменение content-type
 * если buf = nil, то имя очищается
 */
typedef void (MSCU_CALL_PREFIX * Tpacket_info_ex_set_content_type)(PPacketInfoEx PacketInfoEx, gconstpchar buf);
/* изменение auth_info
 * если (buf == 0), то имя очищается
 */
typedef void (MSCU_CALL_PREFIX * Tpacket_info_ex_set_auth_info)(PPacketInfoEx PacketInfoEx, gconstpchar buf);
/* изменение идентификационной информации ident_info
 *
 * buf - атрибуты данных в текстовом виде (строка с завершающим нулем), может быть 0
 *       задаются в виде: <АТРИБУТ_1>;<АТРИБУТ_2>;...;<АТРИБУТ_N>
 *       значение \c <АТРИБУТ>, содержащее символы "точка с запятой", "двойные кавычки", обрамляется двойными кавычками: \code "<АТРИБУТ>" \endcode.
 *       при этом, двойные кавычки, содержащиеся в значении \c <АТРИБУТ>, дублируются: \code "I:MAIL_SUBJECT=subject;""mail delivery""" \endcode
 *       допустимы следующие виды атрибутов:
 *       - адресная часть (идентификаторы) - IDENTIFIER:
 *           I:<ИМЯ>[/<НАПРАВЛЕНИЕ>][/<ПРОТОКОЛ>]=<ЗНАЧЕНИЕ>
 *
 *           <ИМЯ> - название параметра (заглавные символы): IP, PORT
 *           <НАПРАВЛЕНИЕ> - CALL или ANSW (принадлежность параметра к прямому или обратному направлению)
 *           <ПРОТОКОЛ> - принадлежность параметра к определенному протоколу
 *           <ЗНАЧЕНИЕ> - значение параметра (если значение начинается с символов 0xEF,0xBB,0xBF - считается, что кодировка - UTF-8, иначе - WIN1251)
 *
 *           пример: "I:IP/CALL=195.200.200.1"
 *
 * если (buf == 0), то идентификационная информация очищается
 */
typedef void (MSCU_CALL_PREFIX * Tpacket_info_ex_set_ident_info)(PPacketInfoEx PacketInfoEx, gconstpchar buf);
/* изменение header
 * если buf = nil, то имя очищается
 */
typedef void (MSCU_CALL_PREFIX * Tpacket_info_set_header)(PPacketInfo PacketInfo, gpchar buf, guint32 len);

typedef void (MSCU_CALL_PREFIX * Tpacket_info_set_token_path)(PPacketInfo PacketInfo, gpchar buf);
typedef void (MSCU_CALL_PREFIX * Tpacket_info_set_token_entry)(PPacketInfo PacketInfo, gint idx, gpchar buf, guint32 len);

// added 2016-05-11
typedef void (MSCU_CALL_PREFIX * Tpacket_info_set_id_token_path)(PPacketInfo PacketInfo, guint32 id, gpchar buf);
typedef void (MSCU_CALL_PREFIX * Tpacket_info_set_id_token_entry)(PPacketInfo PacketInfo, guint32 id, gint idx, gpchar buf, guint32 len);

// добавление строки в дерево описания пакета
//   AParent - узел-владелец
//   возвращает новый созданный узел, который также может быть владельцем для
//     позже созданных узлов
typedef PkrTreeNode (MSCU_CALL_PREFIX * Tplug_tree_add)(PkrTreeNode AParent, gconstpchar AText);

// вывод информационного сообщения
/// !данная функция является устаревшей, используйте msculib::klogf(MT_XXX, "[<название_модуля>] <сообщение>" <параметры>) вместо нее!
/// \param message_type - одна из констант MT_XXX	(определены в mscu_types.h)
typedef void (MSCU_CALL_PREFIX * Tplug_proto_add_log)(PPluginProtoStuff stuff, gconstpchar message, gint message_type);

// передача пакета на выход (обработка завершена)
//   пакет передается на выход в следующих случаях:
//     - пакет испорчен (плохой CRC, длина и т.д.) и не удален
//     - неизвестный идентификатор протокола следующего уровня обработка (пакет неизвестен)
//     - пакет готовый к употреблению (закончены все этапы обработки)
/// \param tvb.buf - указатель на буфер данных/имя файла/дескриптор файла (используется совместно с флагами SWINE_DATA_BUFFER_XXX)
/// \param tvb.len - количество байт в буфере данных/тип буфера (используются значения флагов SWINE_DATA_BUFFER_XXX)
typedef void (MSCU_CALL_PREFIX * Tplug_proto_ack)(PPluginProtoStuff stuff, tvbuff_t* tvb, PPacketInfo pi);

// передача пакета на выход (обработка завершена)
//   пакет передается на выход в следующих случаях:
//     - пакет испорчен (плохой CRC, длина и т.д.) и не удален
//     - неизвестный идентификатор протокола следующего уровня обработка (пакет неизвестен)
//     - пакет готовый к употреблению (закончены все этапы обработки)
/// \param tvb.buf - указатель на буфер данных/имя файла/дескриптор файла (используется совместно с флагами SWINE_DATA_BUFFER_XXX)
/// \param tvb.len - количество байт в буфере данных/тип буфера (используются значения флагов SWINE_DATA_BUFFER_XXX)
// pi_ex - дополнительная информация о пакете (может быть 0)
//   должна быть создана вызывающим с помощью packet_info_ex_malloc
//   после вызова данной функции значение pi_ex становится недействительным
typedef void (MSCU_CALL_PREFIX * Tplug_proto_ack_ex)(PPluginProtoStuff stuff, tvbuff_t* tvb, PPacketInfo pi, PPacketInfoEx pi_ex);

/// передача пакета на выход (обработка завершена)
///
/// аналогична функции Tplug_proto_ack_ex (см. выше), за исключением дополнительного параметра
///
/// \param tvb_svc.buf - указатель на буфер данных служебного заголовка (заголовков)
/// \param tvb_svc.len - количество байт в буфере tvb_svc.buf
///
typedef void (MSCU_CALL_PREFIX * Tplug_proto_ack_ex_svc)(PPluginProtoStuff stuff, tvbuff_t* tvb, PPacketInfo pi, PPacketInfoEx pi_ex, tvbuff_t* tvb_svc);

/// передача сырых пакетов на выход (обработка завершена)
///
/// аналогична функции Tplug_proto_ack_ex (см. выше), за исключением
///
/// \param tvb - входной буфер (нулевое значение предписывает использовать буфер последнего вызова crop/heur)
/// \param pi - используется поле tv в случае, если параметр tv равен 0
///							(т.е. pi может быть равен 0 в случае, если tv не равен 0)
/// \param in uins - массив значений UIN, по которым отправляется пакет
/// \param in uins_ext - массив значений UIN_EXT, по которым отправляется пакет
/// \param in uins_count - количество элементов в массивах
/// \param in tv - временная метка для отправки пакетов, если равна 0, то используется временная метка из pi
/// \param flags - флаги пакета, набор констант SWINE_ACK_RAW_XXX (см.выше)
///
/// пакет будет отправляться только при содержании в uins_ext флагов:
///   TERI_ID_EXT_RF_RAW_MAC - отправка со смещением - с заголовком канального уровня
///   TERI_ID_EXT_RF_RAW_IP  - отправка IP-пакета без заголовка канального уровня (игнорируется поле offset в tvb)
///
typedef void (MSCU_CALL_PREFIX * Tplug_proto_ack_raw)(PPluginProtoStuff stuff, tvbuff_t* tvb, PPacketInfo pi, guint32 * uins, guint32 * uins_ext, guint32 uins_count, Ttimeval * tv, guint32 flags);

// передача пакета на обработку следующему протоколу (по цепочке)
// stuff может быть равен 0
//   например, протокол Van Jacobson после обработки пакета (восстановления TCP/IP) заголовка
//   передает пакет протоколу PPP для дальнейшей обработки
typedef gboolean (MSCU_CALL_PREFIX * Tplug_proto_forward_packet)(PPluginProtoStuff stuff, gpointer proto, tvbuff_t* tvb, PPacketInfo pi);
// поиск в таблице обработчика по порту и передача ему пакета для обработки
//   например, протокол TCP формирует таблицу портов в plug_create при помощи функции plug_proto_register_dissector_table,
//   а в процессе обработки вызывает данную функцию для поиска обработчика, "висящего" на определенном порту (HTTP, SMTP и т.д.),
//   и передачи пакета найденному обработчику
typedef gboolean (MSCU_CALL_PREFIX * Tplug_proto_dissector_try_port)(PPluginProtoStuff stuff, gpointer sub_dissectors, guint32 port, tvbuff_t* tvb, PPacketInfo pi);
// поиск в эвристической таблице обработчика по порту и передача ему пакета для обработки
//   например, протокол TCP формирует таблицу эвристических портов в plug_create при помощи функции plug_proto_register_heur_dissector_list,
//   а в процессе обработки вызывает данную функцию для поиска обработчика;
//   функция поочередно вызывает все зарегистрированные эвристические обработчики (plug_try_heuristic)
//   и в случае положительного отклика одного из них прекращает поиск
typedef gboolean (MSCU_CALL_PREFIX * Tplug_proto_dissector_try_heuristic)(PPluginProtoStuff stuff, gpointer sub_dissectors, tvbuff_t* tvb, PPacketInfo pi);
// передача пакета на обработку следующему протоколу (по цепочке) - регистрация без обработки
//   например, протокол Van Jacobson после обработки пакета (восстановления TCP/IP) заголовка
//   передает пакет протоколу PPP для дальнейшей обработки
/// \param tvb.buf - указатель на буфер данных/имя файла/дескриптор файла (используется совместно с флагами SWINE_DATA_BUFFER_XXX)
/// \param tvb.len - количество байт в буфере данных/тип буфера (используются значения флагов SWINE_DATA_BUFFER_XXX)
typedef gboolean (MSCU_CALL_PREFIX * Tplug_proto_forward_packet_and_ack)(PPluginProtoStuff stuff, gpointer proto, tvbuff_t* tvb, PPacketInfo pi);
// поиск в таблице обработчика по порту и передача ему пакета для обработки - регистрация без обработки
//   например, протокол TCP формирует таблицу портов в plug_create при помощи функции plug_proto_register_dissector_table,
//   а в процессе обработки вызывает данную функцию для поиска обработчика, "висящего" на определенном порту (HTTP, SMTP и т.д.),
//   и передачи пакета найденному обработчику
/// \param tvb.buf - указатель на буфер данных/имя файла/дескриптор файла (используется совместно с флагами SWINE_DATA_BUFFER_XXX)
/// \param tvb.len - количество байт в буфере данных/тип буфера (используются значения флагов SWINE_DATA_BUFFER_XXX)
typedef gboolean (MSCU_CALL_PREFIX * Tplug_proto_dissector_try_port_and_ack)(PPluginProtoStuff stuff, gpointer sub_dissectors, guint32 port, tvbuff_t* tvb, PPacketInfo pi);
// поиск в эвристической таблице обработчика по порту и передача ему пакета для обработки - регистрация без обработки
//   например, протокол TCP формирует таблицу эвристических портов в plug_create при помощи функции plug_proto_register_heur_dissector_list,
//   а в процессе обработки вызывает данную функцию для поиска обработчика;
//   функция поочередно вызывает все зарегистрированные эвристические обработчики (plug_try_heuristic)
//   и в случае положительного отклика одного из них прекращает поиск
/// \param tvb.buf - указатель на буфер данных/имя файла/дескриптор файла (используется совместно с флагами SWINE_DATA_BUFFER_XXX)
/// \param tvb.len - количество байт в буфере данных/тип буфера (используются значения флагов SWINE_DATA_BUFFER_XXX)
typedef gboolean (MSCU_CALL_PREFIX * Tplug_proto_dissector_try_heuristic_and_ack)(PPluginProtoStuff stuff, gpointer sub_dissectors, tvbuff_t* tvb, PPacketInfo pi);

// передача пакета на обработку следующему протоколу (по цепочке) - регистрация без обработки
//   например, протокол Van Jacobson после обработки пакета (восстановления TCP/IP) заголовка
//   передает пакет протоколу PPP для дальнейшей обработки
/// \param tvb.buf - указатель на буфер данных/имя файла/дескриптор файла (используется совместно с флагами SWINE_DATA_BUFFER_XXX)
/// \param tvb.len - количество байт в буфере данных/тип буфера (используются значения флагов SWINE_DATA_BUFFER_XXX)
// pi_ex - дополнительная информация о пакете (может быть 0)
//   должна быть создана вызывающим с помощью packet_info_ex_malloc
//   после вызова данной функции значение pi_ex становится недействительным
typedef gboolean (MSCU_CALL_PREFIX * Tplug_proto_forward_packet_and_ack_ex)(PPluginProtoStuff stuff, gpointer proto, tvbuff_t* tvb, PPacketInfo pi, PPacketInfoEx pi_ex);

/// передача пакета на обработку следующему протоколу (по цепочке) - регистрация без обработки
///
/// аналогична функции Tplug_proto_forward_packet_and_ack_ex (см. выше), за исключением дополнительного параметра
///
/// \param tvb_svc.buf - указатель на буфер данных служебного заголовка (заголовков)
/// \param tvb_svc.len - количество байт в буфере tvb_svc.buf
///
typedef gboolean (MSCU_CALL_PREFIX * Tplug_proto_forward_packet_and_ack_ex_svc)(PPluginProtoStuff stuff, gpointer proto, tvbuff_t* tvb, PPacketInfo pi, PPacketInfoEx pi_ex, tvbuff_t* tvb_svc);

// поиск в таблице обработчика по порту и передача ему пакета для обработки - регистрация без обработки
//   например, протокол TCP формирует таблицу портов в plug_create при помощи функции plug_proto_register_dissector_table,
//   а в процессе обработки вызывает данную функцию для поиска обработчика, "висящего" на определенном порту (HTTP, SMTP и т.д.),
//   и передачи пакета найденному обработчику
/// \param tvb.buf - указатель на буфер данных/имя файла/дескриптор файла (используется совместно с флагами SWINE_DATA_BUFFER_XXX)
/// \param tvb.len - количество байт в буфере данных/тип буфера (используются значения флагов SWINE_DATA_BUFFER_XXX)
// pi_ex - дополнительная информация о пакете (может быть 0)
//   должна быть создана вызывающим с помощью packet_info_ex_malloc
//   после вызова данной функции значение pi_ex становится недействительным
typedef gboolean (MSCU_CALL_PREFIX * Tplug_proto_dissector_try_port_and_ack_ex)(PPluginProtoStuff stuff, gpointer sub_dissectors, guint32 port, tvbuff_t* tvb, PPacketInfo pi, PPacketInfoEx pi_ex);

/// поиск в таблице обработчика по порту и передача ему пакета для обработки - регистрация без обработки
///
/// аналогична функции Tplug_proto_dissector_try_port_and_ack_ex (см. выше), за исключением дополнительного параметра
///
/// \param tvb_svc.buf - указатель на буфер данных служебного заголовка (заголовков)
/// \param tvb_svc.len - количество байт в буфере tvb_svc.buf
///
typedef gboolean (MSCU_CALL_PREFIX * Tplug_proto_dissector_try_port_and_ack_ex_svc)(PPluginProtoStuff stuff, gpointer sub_dissectors, guint32 port, tvbuff_t* tvb, PPacketInfo pi, PPacketInfoEx pi_ex, tvbuff_t* tvb_svc);

// поиск в эвристической таблице обработчика по порту и передача ему пакета для обработки - регистрация без обработки
//   например, протокол TCP формирует таблицу эвристических портов в plug_create при помощи функции plug_proto_register_heur_dissector_list,
//   а в процессе обработки вызывает данную функцию для поиска обработчика;
//   функция поочередно вызывает все зарегистрированные эвристические обработчики (plug_try_heuristic)
//   и в случае положительного отклика одного из них прекращает поиск
/// \param tvb.buf - указатель на буфер данных/имя файла/дескриптор файла (используется совместно с флагами SWINE_DATA_BUFFER_XXX)
/// \param tvb.len - количество байт в буфере данных/тип буфера (используются значения флагов SWINE_DATA_BUFFER_XXX)
// pi_ex - дополнительная информация о пакете (может быть 0)
//   должна быть создана вызывающим с помощью packet_info_ex_malloc
//   после вызова данной функции значение pi_ex становится недействительным
typedef gboolean (MSCU_CALL_PREFIX * Tplug_proto_dissector_try_heuristic_and_ack_ex)(PPluginProtoStuff stuff, gpointer sub_dissectors, tvbuff_t* tvb, PPacketInfo pi, PPacketInfoEx pi_ex);

/// поиск в эвристической таблице обработчика по порту и передача ему пакета для обработки - регистрация без обработки
///
/// аналогична функции Tplug_proto_dissector_try_heuristic_and_ack_ex (см. выше), за исключением дополнительного параметра
///
/// \param tvb_svc.buf - указатель на буфер данных служебного заголовка (заголовков)
/// \param tvb_svc.len - количество байт в буфере tvb_svc.buf
///
typedef gboolean (MSCU_CALL_PREFIX * Tplug_proto_dissector_try_heuristic_and_ack_ex_svc)(PPluginProtoStuff stuff, gpointer sub_dissectors, tvbuff_t* tvb, PPacketInfo pi, PPacketInfoEx pi_ex, tvbuff_t* tvb_svc);

//////////////////////////////////////////////////////////////////////////

/// Поиск известной сигнатуры данных в областях поиска spots буферов bufs (с длинами lens).
/// Если признак найден, вызывается функция обратного вызова cb (для каждого найденного признака) - в этом случае token->id содержит UIN
/// В режиме СОРМ сессия в случае успеха ставится на отбор по найденным признакам.
/// Если режим СОРМ отключен, функция работает в режиме уточняющего отбора, когда сессия в случае успеха на отбор по найденным признакам не ставится.
/// В режиме уточняющего отбора модуль должен регистрировать только данные, отобранные данной функцией (положительное возвращаемое значение).
///
/// \param in stuff - параметр, передаваемый при вызове функций \ref Tplug_create, и определяющий экземпляр обработчика
/// \param in pi		- метаинформация контекста обработки
/// \param in count - количество буферов поиска
/// \param in bufs - массив буферов поиска
/// \param in lens - массив длин буферов поиска
/// \param in spots - массив областей поиска \ref teri_bis.h
/// \param in cb - адрес функции обратного вызова (\ref teri_bis.h)
/// \param in ud - первый параметр функции обратного вызова
///
/// !Внимание! В режиме СОРМ данную функцию можно использовать только внутри вызова plug_session_begin.
///
/// !Внимание! В режиме уточняющего отбора функция обратного вызова может быть ни разу не вызвана при положительном возвращаемом значении.
///
/// \return в случае успеха возвращается количество найденных вхождений
/// \return в случае неудачи возвращается отрицательное значение (код ошибки)
///
typedef gint (MSCU_CALL_PREFIX * Tplug_proto_srm_teri_match)(PPluginProtoStuff stuff, PPacketInfo pi, gint count, gconstpointer* bufs, guint* lens, guint* spots, Tteri_bis_match_callback cb, void *ud);

//////////////////////////////////////////////////////////////////////////
// определяет, что вызывающий модуль модуль способен регистрировать только сырые пакеты
// использование данного параметра позволяет ускорить обработку, т.к. в таком случае информация о найденых признаках не заносится
// в метаинформацию контекста обработки пакета
#define COMPLEX_TERI_MATCH_RF_RAW_ONLY 1

/// Сложный отбор
/// Поиск известной сигнатуры данных в областях поиска spots буферов bufs (с длинами lens).
/// Если признак найден, вызывается функция обратного вызова cb (для каждого найденного признака) - в этом случае token->id содержит UIN, token->id_ext содержит UIN_EXT
/// Если найдены признаки с флагами TERI_ID_EXT_RF_RAW_MAC/TERI_ID_EXT_RF_RAW_IP, то в режиме обработки TCP-сессии, сессия автоматически ставится на отбор по найденным признакам.
/// Если найдены признаки с флагами TERI_ID_EXT_RF_RAW_MAC/TERI_ID_EXT_RF_RAW_IP, то модуль должен произвести отправку данных с помощью функции plug_proto_ack_raw.
/// Если найдены признаки с флагами TERI_ID_EXT_RF_DECODED, вызывающий модуль должен декодировать и зарегистрировать данные.
/// В противном случае модуль должен отказаться от регистрации данных.
///
/// \param in stuff - параметр, передаваемый при вызове функций \ref Tplug_create, и определяющий экземпляр обработчика
/// \param in flags - флаги режима поиска, константы COMPLEX_TERI_MATCH_XXX
/// \param in pi		- метаинформация контекста обработки
/// \param in count - количество буферов поиска
/// \param in bufs - массив буферов поиска
/// \param in lens - массив длин буферов поиска
/// \param in spots - массив областей поиска \ref teri_bis.h
/// \param in cb - адрес функции обратного вызова (\ref teri_bis.h)
/// \param in ud - первый параметр функции обратного вызова
/// \param out has_rf_decoded - указатель на флаг того, что были найдены DECODED-признаки (адрес может быть равен 0)
/// \param out has_rf_raw - указатель на флаг того, что были найдены RAW-признаки (адрес может быть равен 0)
/// \param out out_uins	- указатель на массив значений UNI найденных признаков (адрес может быть равен 0) - значения актуальны вплоть до следующего вызова данной функции
/// \param out out_uins_ext - указатель на массив значений UNI_EXT найденных признаков (адрес может быть равен 0) - значения актуальны вплоть до следующего вызова данной функции
/// \param out out_uins_count - указатель на значение количества найденных признаков - размер массивов out_uins/out_uins_ext (адрес может быть равен 0) - значения актуальны вплоть до следующего вызова данной функции
///
/// !Внимание! Данную функцию можно использовать только внутри вызова функции обработки.
///
/// \return в случае успеха возвращается количество найденных вхождений
/// \return в случае неудачи возвращается отрицательное значение (код ошибки)
///
typedef gint (MSCU_CALL_PREFIX * Tplug_proto_complex_teri_match)(PPluginProtoStuff stuff, guint32 flags, PPacketInfo pi, gint count, gconstpchar* bufs, gint32* lens, guint32* spots, Tteri_bis_match_callback cb, void *ud, gboolean * has_rf_decoded, gboolean * has_rf_raw, guint32 ** out_uins, guint32 ** out_uins_ext, guint32 * out_uins_count);

/// отличие от предыдущей функции
/// \param in bufs - массив буферов поиска
/// \param in lens - массив длин буферов поиска
/// \param in spots - массив областей поиска \ref teri_bis.h
typedef gint (MSCU_CALL_PREFIX * Tplug_proto_complex_teri_match_retro)(PPluginProtoStuff stuff, guint32 flags, PPacketInfo pi, gint count, gconstpointer* bufs, guint* lens, guint* spots, Tteri_bis_match_callback cb, void *ud, gboolean * has_rf_decoded, gboolean * has_rf_raw, guint32 ** out_uins, guint32 ** out_uins_ext, guint32 * out_uins_count);
//////////////////////////////////////////////////////////////////////////

/* функции, используемые в Create */
// регистрация обработчика
//   необходима для того, чтобы созданный экземпляр обработчика протокола
//   (dissector - в действительности TPluginProtoStuff.swine_inst) стал виден другим обработчикам
//   при помощи функции plug_proto_find_dissector под имененм name
typedef void (MSCU_CALL_PREFIX * Tplug_proto_register_dissector)(PPluginProtoStuff stuff, gconstpchar name);
// регистрация таблицы обработчиков
//   после создания в нее можно добавлять обработчики при помощи функции plug_proto_dissector_add,
//   а затем использовать с помощью функции plug_proto_dissector_try_port
typedef gpointer (MSCU_CALL_PREFIX * Tplug_proto_register_dissector_table)(PPluginProtoStuff stuff, gconstpchar name, gint key_type);
// регистрация таблицы эвристики
//   после создания в нее можно добавлять обработчики при помощи функции plug_proto_heur_dissector_add,
//   а затем использовать с помощью функции plug_proto_dissector_try_heuristic
typedef gpointer (MSCU_CALL_PREFIX * Tplug_proto_register_heur_dissector_list)(PPluginProtoStuff stuff, gconstpchar name);
// регистрация поля
//   после создания можно использовать для взаимодействия между обработчиками:
//   один обработчик с помощью данной функции регистрирует адрес на свои данные
//   другой с помощью функции plug_proto_find_field_info получает этот адрес для использования
typedef void (MSCU_CALL_PREFIX * Tplug_proto_register_field_info)(PPluginProtoStuff stuff, gconstpchar name, gpointer value);

/* функции, используемые в Bind */

// поиск обработчика
//   для данной функции видны только обработчики, зарегистрированные с помощью plug_proto_register_dissector
typedef gpointer (MSCU_CALL_PREFIX * Tplug_proto_find_dissector)(PPluginProtoStuff stuff, gconstpchar name);
//   для данной функции видны только обработчики, зарегистрированные с помощью plug_proto_register_dissector_table
typedef gpointer (MSCU_CALL_PREFIX * Tplug_proto_find_dissector_table)(PPluginProtoStuff stuff, gconstpchar name);
//   для данной функции видны только обработчики, зарегистрированные с помощью plug_proto_register_heur_dissector_list
typedef gpointer (MSCU_CALL_PREFIX * Tplug_proto_find_heur_dissector_list)(PPluginProtoStuff stuff, gconstpchar name);
// поиск зарегистрированного поля
typedef gpointer (MSCU_CALL_PREFIX * Tplug_proto_find_field_info)(PPluginProtoStuff stuff, gconstpchar name);
// добавление обработчика в таблицу
//   данная функция сопоставляет порт pattern обработчику proto в таблице с именем name для дальнейшего использования функцией plug_proto_dissector_try_port
typedef void (MSCU_CALL_PREFIX * Tplug_proto_dissector_add)(PPluginProtoStuff stuff, gconstpchar name, guint32 pattern);
// добавление обработчика в таблицу эвристики
//   данная функция обработчик proto в таблицу с именем name для дальнейшего использования функцией plug_proto_dissector_try_heuristic
typedef void (MSCU_CALL_PREFIX * Tplug_proto_heur_dissector_add)(PPluginProtoStuff stuff, gconstpchar name);

/// Создание файла.
///
/// В случае удачного выполнения записывает в fhandle дескрипор созданного файла.
///
/// Для записи в файл используется \ref Tplug_file_write.
///
/// Для чтения из файла используется \ref Tplug_file_read.
///
/// Для закрытия и удаления файла используется \ref Tplug_file_close.
///
/// Для регистрации файла используется \ref Tplug_XXX_ack.
///
/// \param in stuff - параметр, передаваемый при вызове функций \ref Tplug_register, и определяющий текущий контекст вызова
/// \param in flags - набор флагов - не используется (зарезервировано)
/// \param[out] fhandle - дескриптор созданного файла (используется функциями: \ref Tplug_XXX_ack,
///   \ref Tplug_file_write, \ref Tplug_file_read, \ref Tplug_file_close).
///
/// \return в случае успеха возвращает 0, в fhandle записывается дескриптор созданного файла
/// \return в случае неудачи возвращает отрицательное значение
///
typedef gint (MSCU_CALL_PREFIX * Tplug_file_create)(PPluginProtoStuff stuff, gint flags, void ** fhandle);

/// запись данных в файл
/// производит запись данных в файл по определенной позиции
///
/// \param in stuff - параметр, передаваемый при вызове функций \ref Tplug_register, и определяющий текущий контекст вызова
/// \param in fhandle - дескриптор созданного файла (создается с помощью \ref Tplug_callback_file_create)
/// \param in buf - буфер для записи
/// \param in len - длина буфера для записи в байтах
/// \param in offset - стартовая позиция записи, задается в байтах от начала файла (значение -1 определяет текущую позицию)
///
/// \return в случае успеха возвращает 0
/// \return в случае неудачи возвращает отрицательное значение
///
typedef gint (MSCU_CALL_PREFIX * Tplug_file_write)(PPluginProtoStuff stuff, void * fhandle, void * buf, gsize_t len, gint64 offset);

/// чтение данных из файла
/// производит чтение данных из файла по определенной позиции
///
/// \param in stuff - параметр, передаваемый при вызове функций \ref Tplug_register, и определяющий текущий контекст вызова
/// \param in fhandle - дескриптор созданного файла (создается с помощью \ref Tplug_callback_file_create)
/// \param in buf - буфер для чтения
/// \param in len - длина буфера для чтения в байтах
/// \param in offset - стартовая позиция чтения, задается в байтах от начала файла (значение -1 определяет текущую позицию)
///
/// \return в случае успеха возвращает 0
/// \return в случае неудачи возвращает отрицательное значение
///
typedef gint (MSCU_CALL_PREFIX * Tplug_file_read)(PPluginProtoStuff stuff, void * fhandle, void * buf, gsize_t len, gint64 offset);

/// закрытие файла
/// освобождает дескриптор и удаляет файл
///
/// \param in stuff - параметр, передаваемый при вызове функций \ref Tplug_register, и определяющий текущий контекст вызова
/// \param in fhandle - дескриптор созданного файла (создается с помощью \ref Tplug_callback_file_create)
///
/// \return в случае успеха возвращает 0
/// \return в случае неудачи возвращает отрицательное значение
///
typedef gint (MSCU_CALL_PREFIX * Tplug_file_close)(PPluginProtoStuff stuff, void * fhandle);

/// \name Функции поиска
///@{

/// Поиск известной сигнатуры данных в области поиска (area) буфера buf (длиной len).
/// Если заголовок найден, возвращается указатель на
/// константную строку с именем расширения (вместе с точкой), в found_pos заносится позиция совпадения.
/// В случае неудачи возвращает nil.
///
/// \param buf - буфер, в котором производится поиск
/// \param len - размер буфера в байтах
/// \param area - область поиска в байтах
/// \param[out] found_pos - позиция начала совпадения
///
/// \return в случае успеха возвращает расширение (вместе с точкой), в found_pos заносится позиция совпадения (начиная с 0)
/// \return в случае неудачи возвращает 0 (nil/NULL)
///
typedef gconstpchar (MSCU_CALL_PREFIX * Tenum_file_find)(gconstpchar buf, guint len, guint area, guint * found_pos);

/// производит поиск общепринятого названия по номеру TCP-порта
///
/// \param port - номер порта
///
/// \return если port найден, возвращается указатель на константную строку с названием
/// \return в случае неудачи возвращает nil
///
typedef gconstpchar (MSCU_CALL_PREFIX * Tenum_service_tcp_find)(guint32 port);

/// производит поиск общепринятого названия по номеру UDP-порта
///
/// \param port - номер порта
///
/// \return если port найден, возвращается указатель на константную строку с названием
/// \return в случае неудачи возвращает nil
///
typedef gconstpchar (MSCU_CALL_PREFIX * Tenum_service_udp_find)(guint32 port);

/// поиск типа файла по mime-типу (значению content-type)
///
/// \param mime_type - значение content-type в строковом виде с завершающим нулем
///
/// \return в случае успеха возвращает расширение (вместе с точкой)
/// \return в случае неудачи возвращает 0 (nil/NULL)
///
typedef gconstpchar (MSCU_CALL_PREFIX * Tenum_mime_find)(gconstpchar mime_type);

/// производит поиск известного названия по IP-адресу
///
/// \param ip - IP-адрес в цифровом формате
///
/// \return если IP найден, возвращается указатель на константную строку с названием
/// \return в случае неудачи возвращает nil
///
typedef gconstpchar (MSCU_CALL_PREFIX * Tenum_ip_find)(guint32 ip);

/// производит поиск известного названия организации по OUI
///
/// \param oui - указатель на 3 байта, определяющих OUI
///
/// \return если OUI найден, возвращается указатель на константную строку с именем организации
/// \return в случае неудачи возвращает nil
///
typedef gconstpchar (MSCU_CALL_PREFIX * Tenum_oui_find)(gconstpointer oui);

/// производит поиск известного названия по PID
///
/// \param pid - номер PID
///
/// \return если PID найден, возвращается указатель на константную строку с названием
/// \return в случае неудачи возвращает nil
///
typedef gconstpchar (MSCU_CALL_PREFIX * Tenum_pid_find)(guint32 pid);

/// @}

// получение value_string-таблицы "wtap_encap" (для декодеров)
typedef value_string* (MSCU_CALL_PREFIX* Twtap_encap_get_vals)();

typedef guint (MSCU_CALL_PREFIX* Twtap_encap_register)(gconstpchar name, gconstpchar filter_name);

// установка сети (для декодеров)
// связывание данного декодера с определенным обработчиком
// декодер должен использовать для network WTAP_ENCAP_XXX-значения, определенные в файле "wtap_encap.h"
// связываемый обработчик должен быть зарегистрирован в таблице "wtap_encap" с соответствующим значением (network)
typedef void (MSCU_CALL_PREFIX * Tplug_proto_set_network)(PPluginProtoStuff stuff, gint32 network);

// регистрация выделенного кадра (для декодеров)
// декодер с помощью функции crop получает поток байт, выделяет кадры (пакеты) и регистрирует их с помощью данной функции
typedef void (MSCU_CALL_PREFIX * Tplug_proto_ack_frame)(PPluginProtoStuff stuff, tvbuff_t* tvb, PPacketInfo pi);

/// производит добавление нового фильтра
/// Данная функция является устаревшей. Используйте Tplug_proto_add_filter_2 вместо нее.
///
/// \param in stuff - параметр, передаваемый при вызове функций \ref Tplug_register, и определяющий текущий контекст вызова
/// \param in filter - структура, содержащая адрес фильтра (см. соответствующее описание в ffsrm.h)
///
typedef void (MSCU_CALL_PREFIX * Tplug_proto_add_filter)(PPluginProtoStuff stuff, S10G_FILTER_ITEM_STRUCT* filter_item);

/// производит удаление ранее добавленного фильтра
/// Данная функция является устаревшей. Используйте Tplug_proto_sub_filter_2 вместо нее.
///
/// \param in stuff - параметр, передаваемый при вызове функций \ref Tplug_register, и определяющий текущий контекст вызова
/// \param in filter - структура, содержащая адрес фильтра (см. соответствующее описание в ffsrm.h)
///
typedef void (MSCU_CALL_PREFIX * Tplug_proto_sub_filter)(PPluginProtoStuff stuff, S10G_FILTER_ITEM_STRUCT* filter_item);

/// производит добавление нового фильтра
///
/// \param in stuff - параметр, передаваемый при вызове функций \ref Tplug_register, и определяющий текущий контекст вызова
/// \param in filter - структура, содержащая адрес фильтра (см. соответствующее описание в ffsrm.h)
///
typedef void (MSCU_CALL_PREFIX * Tplug_proto_add_filter_2)(PPluginProtoStuff stuff, S10G_FILTER_ITEM_STRUCT_2 * filter_item);

/// производит удаление ранее добавленного фильтра
///
/// \param in stuff - параметр, передаваемый при вызове функций \ref Tplug_register, и определяющий текущий контекст вызова
/// \param in filter - структура, содержащая адрес фильтра (см. соответствующее описание в ffsrm.h)
///
typedef void (MSCU_CALL_PREFIX * Tplug_proto_sub_filter_2)(PPluginProtoStuff stuff, S10G_FILTER_ITEM_STRUCT_2 * filter_item);

/// 2016-11-24
/// Добавление вторичного признака в подсистему отбора.
/// Включенный флаг token_is_indirect используется для добавления признака автоподстановки (когда существующий признак инициирует добавление активности новых фигурантов).
/// Выключенный флаг token_is_indirect используется для добавления признака привязки (когда существующий признак меняет свое значение в процессе изменения активности).
///
/// \param in stuff - параметр, передаваемый при вызове функций \ref Tplug_register, и определяющий текущий контекст вызова
/// \param in token_buf - буфер с данными признака
/// \param in token_len - длина буфера с данными признака
/// \param in token_spot - областей поиска \ref teri_bis.h
/// \param in token_is_indirect - тип признака: 0 - не косвенный (приоритет token->prio найденного признака данного типа не равен 2), !0 - косвенный (приоритет token->prio найденного признака данного типа равен 2, такой признак не может в дальнейшем порождать аналогичные вызовы)
/// \param in uins - массив значений UIN, к которым относится добавляемый признак
/// \param in uins_count - количество элементов в массиве uins
///
typedef void (MSCU_CALL_PREFIX * Tplug_proto_srm_set_secondary_token)(PPluginProtoStuff stuff, gconstpointer token_buf, guint token_len, guint token_spot, gboolean token_is_indirect, guint32 * uins, guint32 uins_count);

/// 2016-11-24
/// Добавление вторичного признака в подсистему отбора.
///
/// \param in stuff - параметр, передаваемый при вызове функций \ref Tplug_register, и определяющий текущий контекст вызова
/// \param in filter_item - структура, содержащая ip-адреса (1 или 2)
/// \param in tv - TimeStamp
/// \param in unis - массив значений UNI, к которым относится добавляемый признак
/// \param in unis_count - количество элементов в массиве uins
///
typedef void (MSCU_CALL_PREFIX * Tplug_proto_srm_set_secondary_token2)(PPluginProtoStuff stuff, S10G_FILTER_ITEM_STRUCT_2 * filter_item, Ttimeval* tv, guint32* unis, gsize_t unis_count);

/* структура, содержащая адреса стандартных функций */
STRUCT_PACKED_BEGIN // устанавливаем выравнивание структур в 1 байт
struct STRUCT_PACKED_ATTRIBUTE TSWINEStandartFunctions {
  // размер структуры.
  // Плагин является совместимым с Сервером, если размер структуры в нем не больше, чем в приложении.
  // проверка внутри экспортируемой функции плагина swine_plugin_init должна иметь вид:
  //   assert(sizeof(TSWINEStandartFunctions) <= SWINEStuff->cbSize);
  guint32 cbSize;

  // поиск обработчика
  Tplug_proto_find_stuff_by_dissector plug_proto_find_stuff_by_dissector;
  // установка имени текущего модуля регистрации
  Tset_swine_current_module_name set_swine_current_module_name;
  /* регистраторы протоколов */
  Tplug_proto_register_protocol                 plug_proto_register_protocol;
  Tplug_proto_register_protocol_always_enabled  plug_proto_register_protocol_always_enabled; // 2010-02-17

  Tplug_proto_register_protocol_wud                 plug_proto_register_protocol_wud; // 2010-02-17
  Tplug_proto_register_protocol_wud_always_enabled  plug_proto_register_protocol_wud_always_enabled; // 2010-02-17

  Tplug_prefs_register_protocol                 plug_prefs_register_protocol;
  Tplug_prefs_register_protocol_always_enabled  plug_prefs_register_protocol_always_enabled; // 2010-02-17
  /* работа с записью информации о пакете */
  Tpacket_info_malloc              packet_info_malloc;
  Tpacket_info_free                packet_info_free;
  Tpacket_info_clear               packet_info_clear;
  Tpacket_info_clone               packet_info_clone;
  Tpacket_info_ex_malloc           packet_info_ex_malloc;
  Tpacket_info_ex_free             packet_info_ex_free;
  Tpacket_info_ex_clear            packet_info_ex_clear;
  Tpacket_info_ex_clone            packet_info_ex_clone;
  Tpacket_info_ex_set_description  packet_info_ex_set_description;
  Tpacket_info_ex_set_generic_name packet_info_ex_set_generic_name;
  Tpacket_info_ex_set_content_type packet_info_ex_set_content_type;
  Tpacket_info_ex_set_auth_info    packet_info_ex_set_auth_info;
  Tpacket_info_ex_set_ident_info   packet_info_ex_set_ident_info;
  Tpacket_info_set_header          packet_info_set_header;
  Tpacket_info_set_token_path      packet_info_set_token_path;
  Tpacket_info_set_token_entry     packet_info_set_token_entry;
  /* работа с деревом свойств */
  Tplug_tree_add plug_tree_add;
  /* работа с value_string */
  Tplug_val_to_str plug_val_to_str; // !!можно убрать (есть в swine_utils.h/cpp)
  /* общие функции протокола */
  Tplug_proto_add_log                 plug_proto_add_log;
  /* функции протокола */
  Tplug_proto_ack                     plug_proto_ack;
  Tplug_proto_ack_ex                  plug_proto_ack_ex;

  Tplug_proto_forward_packet                      plug_proto_forward_packet;
  Tplug_proto_dissector_try_port                  plug_proto_dissector_try_port;
  Tplug_proto_dissector_try_heuristic             plug_proto_dissector_try_heuristic;

  Tplug_proto_forward_packet_and_ack                       plug_proto_forward_packet_and_ack;
  Tplug_proto_dissector_try_port_and_ack                   plug_proto_dissector_try_port_and_ack;
  Tplug_proto_dissector_try_heuristic_and_ack              plug_proto_dissector_try_heuristic_and_ack;

  Tplug_proto_forward_packet_and_ack_ex                       plug_proto_forward_packet_and_ack_ex;
  Tplug_proto_dissector_try_port_and_ack_ex                   plug_proto_dissector_try_port_and_ack_ex;
  Tplug_proto_dissector_try_heuristic_and_ack_ex              plug_proto_dissector_try_heuristic_and_ack_ex;
  /* функции, используемые в Create */
  Tplug_proto_register_dissector            plug_proto_register_dissector;
  Tplug_proto_register_dissector_table      plug_proto_register_dissector_table;
  Tplug_proto_register_heur_dissector_list  plug_proto_register_heur_dissector_list;
  Tplug_proto_register_field_info           plug_proto_register_field_info;
  /* функции, используемые в Bind */
  Tplug_proto_find_dissector            plug_proto_find_dissector;
  Tplug_proto_find_dissector_table      plug_proto_find_dissector_table;
  Tplug_proto_find_heur_dissector_list  plug_proto_find_heur_dissector_list;
  Tplug_proto_find_field_info           plug_proto_find_field_info;
  Tplug_proto_dissector_add             plug_proto_dissector_add;
  Tplug_proto_heur_dissector_add        plug_proto_heur_dissector_add;

  Tplug_file_create                     plug_file_create;
  Tplug_file_write                      plug_file_write;
  Tplug_file_close                      plug_file_close;

  Tenum_file_find                      enum_file_find;
  Tenum_service_tcp_find               enum_service_tcp_find;
  Tenum_service_udp_find               enum_service_udp_find;
  Tenum_mime_find                      enum_mime_find;
  Tenum_ip_find                        enum_ip_find;
  Tenum_oui_find                       enum_oui_find;
  Tenum_pid_find                       enum_pid_find;

  // добавлено: 2009-07-31
  // только для декодеров
  /* регистраторы декодеров */
  Tplug_deco_register_decoder plug_deco_register_decoder;
  Tplug_prefs_register_decoder plug_prefs_register_decoder;

  Twtap_encap_get_vals wtap_encap_get_vals;
  Twtap_encap_register wtap_encap_register;

  // установка сети
  Tplug_proto_set_network plug_proto_set_network;
  // регистрация выделенного кадра
  Tplug_proto_ack_frame plug_proto_ack_frame;

  // добавление фильтра - добавлено 2011-05-11
  Tplug_proto_add_filter plug_proto_add_filter; /// Данная функция является устаревшей. Используйте Tplug_proto_add_filter_2 вместо нее.
  // удаление фильтра - добавлено 2011-05-11
  Tplug_proto_sub_filter plug_proto_sub_filter; /// Данная функция является устаревшей. Используйте Tplug_proto_sub_filter_2 вместо нее.

  // чтение файла - добавлено 2012-05-02
  Tplug_file_read                       plug_file_read;

  // добавлено 2014-06-27
  Tplug_proto_ack_ex_svc                              plug_proto_ack_ex_svc;
  Tplug_proto_forward_packet_and_ack_ex_svc           plug_proto_forward_packet_and_ack_ex_svc;
  Tplug_proto_dissector_try_port_and_ack_ex_svc       plug_proto_dissector_try_port_and_ack_ex_svc;
  Tplug_proto_dissector_try_heuristic_and_ack_ex_svc  plug_proto_dissector_try_heuristic_and_ack_ex_svc;

	// добавлено 2016-04-10
	Tplug_proto_srm_teri_match plug_proto_srm_teri_match;

	// добавлено 2016-05-11
  Tpacket_info_set_id_token_path      packet_info_set_id_token_path;
  Tpacket_info_set_id_token_entry     packet_info_set_id_token_entry;

  // добавление фильтра - добавлено 2016-10-23
  Tplug_proto_add_filter_2 plug_proto_add_filter_2;
  // удаление фильтра - добавлено 2016-10-23
  Tplug_proto_sub_filter_2 plug_proto_sub_filter_2;

	// 2016-11-13
	// клонирование признаков записи
  Tpacket_info_tokens_clone               packet_info_tokens_clone;

	/// 2016-11-24
  Tplug_proto_srm_set_secondary_token		plug_proto_srm_set_secondary_token;
  Tplug_proto_srm_set_secondary_token2	plug_proto_srm_set_secondary_token2;

	// добавлено 2017-06-02
	Tplug_proto_complex_teri_match plug_proto_complex_teri_match;
	Tplug_proto_ack_raw						 plug_proto_ack_raw;
	// добавлено 2017-06-13
	Tplug_proto_complex_teri_match_retro plug_proto_complex_teri_match_retro;
};
STRUCT_PACKED_END // восстанавливаем выравнивание структур по умолчанию
typedef TSWINEStandartFunctions * PSWINEStandartFunctions;

/* тип экспортируемой функции плагина
 * название функции в таблице экспорта DLL - swine_plugin_init (naked - без декорации)
 * функция вызывается однажды, при загрузке библиотеки
 * параметры:
 *   SWINEStuff: адрес на структуру, содержащую адреса стандартных функций SWINE
 *   adescription: описание плагина, размер - SWINE_STR_SIZE, заполняется плагином
 *   aversion: версия плагина в формате "n.n.n" или "n.n", размер - SWINE_STR_SIZE, заполняется плагином
 * задачи функции:
 *   - заполнить adescription и aversion соответствующими значениями
 *   - запомнить во внутренней переменной адрес структуры стандартных функций (сама структура располагается
 *     внутри ядра и хранится все время жизни SWINE)
 *   - зарегистрировать классы декодеров и протоколов, реализованных в плагине, а также параметры к ним
 *     (функции: plug_proto_register_protocol, plug_prefs_register_protocol,
 *      plug_prefs_register_uint_preference, plug_prefs_register_uint_hidden_preference
 *      plug_prefs_register_bool_preference, plug_prefs_register_bool_hidden_preference)
 */
typedef void (MSCU_CALL_PREFIX * TPluginInit)(PSWINEStandartFunctions SWINEStuff, gpchar adescription, gpchar aversion);

#endif