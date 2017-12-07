/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/*
 * ��������! ������ ���� ���������������� ��� ��������� ������ ������������ ������� �����.
 * ����� ��������� � ������ ����� ���������� �������������� �����������.
 * ��� ������������� ������� ����� ������ �������� ��� � ������ � ������� ��������� #include.
 */
/* ����� ���������� � ��������
 *   - ������� ������ ���� ��������� � ���� ����������� ����������� ��������� (DLL)
 *   - DLL-������ ����� ����� ����� ��� � ���������� ".dll"
 *   - DLL-������ ������ ���� ����������� � �������� '<������� EXE-������>\plugins' ���
 *       � ��� ������������ ������ ������ ��������
 *   - �������, �������������� �����������, ������ ����� �������������� (naked) �����
 *   - �������, �������������� �����������, ������ ������������ MSCU_CALL_PREFIX - stdcall (__stdcall) ���������� � ������
 */
/* swine_api.h
 *
 * Plugin API for Swine 0.9 (War Pig 0.9, War Hog 0.8)
 *
 * War Pig (wrpg) - Network Protocol Dissector
 * Copyright (C) 2002-2017 MSC, ORG
 */
//
// ���������
// ---------
/// - [+] 2017-11-04 - ��������� - ���� TPacketInfo::session_id (��. ������������);
/// - [+] 2017-08-30 - ��������� - ����� ���� ������ - PDT_ISTAT1, PDT_ISTAT2, PDT_ISTAT3 (��. ������������);
/// - [*] 2017-07-13 - �������� - �������� �������� SWINE_PI_FLAG_XXX ��� TPacketInfo::flags (��. ������������);
/// - [*] 2017-07-13 - �������� - �������� ������� plug_proto_ack_raw (��. ������������);
/// - [+] 2017-06-13 - ��������� - ������� plug_proto_complex_teri_match_retro (��. ������������);
/// - [+] 2017-06-02 - ��������� - ������� plug_proto_ack_raw (��. ������������);
/// - [+] 2017-06-02 - ��������� - ������� plug_proto_complex_teri_match (��. ������������);
/// - [+] 2016-11-30 - ���������: ����� ��� ������ - PDT_IDLE (��. ������������);
/// - [+] 2016-11-24 - ��������� - ������� plug_proto_srm_set_secondary_token2 (��. ������������);
/// - [+] 2016-11-24 - ��������� - ������� plug_proto_srm_set_secondary_token (��. ������������);
/// - [+] 2016-11-13 - ��������� - ������� packet_info_tokens_clone;
/// - [+] 2016-10-23 - ��������� - ������� plug_proto_add_filter_2
/// - [+] 2016-10-23 - ��������� - ������� plug_proto_sub_filter_2
/// - [+] 2016-07-13 - ��������� - field <offset> to the tvbuff_t structure
/// - [+] 2016-05-11 - ��������� - ������� plug_packet_info_set_id_token_path;
/// - [+] 2016-05-11 - ��������� - ������� plug_packet_info_set_id_token_path;
/// - [+] 2016-05-11 - ��������� - ���� token_items � ��������� _TPacketInfo
/// - [+] 2016-04-10 - ��������� - ������� plug_proto_srm_teri_match
/// - 2015-06-01 - ��������� - ��������� ��������� UTF-8 � ��������� ���������;
/// - 2015-02-05 - �������� - ���� is_p2p ��������� _TPacketInfo ������������� � is_p2p_or_ext � ������ �������� �������� ���� Ext ��������� <�������>
/// - 2014-07-21 - ��������� - ���� tv2 � ��������� _TPacketInfo
/// - 2014-06-27 - ��������� - ������� plug_proto_dissector_try_heuristic_and_ack_ex_svc
/// - 2014-06-27 - ��������� - ������� plug_proto_dissector_try_port_and_ack_ex_svc
/// - 2014-06-27 - ��������� - ������� plug_proto_forward_packet_and_ack_ex_svc
/// - 2014-06-27 - ��������� - ������� plug_proto_ack_ex_svc
/// - 2012-08-16 - ��������� - ����� ��� ������ - PDT_RAW_IP - ����������� IP-������� (��� ��������� �����);
/// - 2012-05-02 - ��������� - ������� Tplug_file_read plug_file_read;
/// - 2011-05-11 - ��������� - ������� plug_proto_add_filter
/// - 2011-05-11 - ��������� - ������� plug_proto_sub_filter
/// - 2011-01-04 - �������� - �������� ������� Tpacket_info_ex_set_ident_info
/// - 2010-08-20 - �������� - ��������� ������� plug_heur (������� ����� plug_crop - ��. ������������)
/// - 2010-06-25 - ��������� - ����� ��� ������ - PDT_ISTAT - �������������� ������ (��������������);
/// - 2010-06-02 - ��������� - ����� ��� ������ - PDT_STAT - �������������� ������;
/// - 2010-05-24 - ������� - ������� plug_proto_forward_packet_interlocked �� ��������� TSWINEStandartFunctions
/// - 2010-05-24 - ������� - ������� plug_proto_dissector_try_port_interlocked �� ��������� TSWINEStandartFunctions
/// - 2010-05-24 - ������� - ������� plug_proto_dissector_try_heuristic_interlocked �� ��������� TSWINEStandartFunctions
/// - 2010-05-24 - ������� - ������� plug_proto_forward_packet_and_ack_interlocked �� ��������� TSWINEStandartFunctions
/// - 2010-05-24 - ������� - ������� plug_proto_dissector_try_port_and_ack_interlocked �� ��������� TSWINEStandartFunctions
/// - 2010-05-24 - ������� - ������� plug_proto_dissector_try_heuristic_and_ack_interlocked �� ��������� TSWINEStandartFunctions
/// - 2010-05-24 - ������� - ������� plug_proto_forward_packet_and_ack_ex_interlocked �� ��������� TSWINEStandartFunctions
/// - 2010-05-24 - ������� - ������� plug_proto_dissector_try_port_and_ack_ex_interlocked �� ��������� TSWINEStandartFunctions
/// - 2010-05-24 - ������� - ������� plug_proto_dissector_try_heuristic_and_ack_ex_interlocked �� ��������� TSWINEStandartFunctions
/// - 2010-05-24 - ������� � ������������ ����� ������
/// - 2010-05-23 - ������� - plug_file_close - �����������
/// - 2010-05-23 - ������� - plug_file_write - �����������
/// - 2010-05-23 - ������� - plug_file_create - �����������
/// - 2010-04-19 - ��������� ����� ���������������� XXX_ack_XXX
/// - 2010-04-19 - ��������� - ������� Tplug_file_create plug_file_create;
/// - 2010-04-19 - ��������� - ������� Tplug_file_write plug_file_write;
/// - 2010-04-19 - ��������� - ������� Tplug_file_close plug_file_close;
/// - 2010-04-19 - ������� - ��������� MT_XXX (���� ���������) - ���������� � mscu_types.h
/// - 2010-02-27 - ������� - ������� Tplug_g_malloc, Tplug_g_malloc0, Tplug_g_realloc, Tplug_g_free
/// - 2010-02-24 - �������� - ������� Tplug_packet_info_XXX ������������� � Tpacket_info_XXX
/// - 2010-02-17 - ��������� - ��� Tplug_proto_find_stuff_by_dissector
/// - 2010-02-17 - ��������� - ��� Tset_swine_current_module_name
/// - 2010-02-17 - ��������� - ��� Tplug_proto_register_protocol_wud_always_enabled
/// - 2010-02-17 - ��������� - ��� Tplug_proto_register_protocol_wud
/// - 2010-02-17 - ��������� - ��� Tplug_proto_register_protocol_always_enabled
/// - 2010-02-17 - ��������� - ��� Tplug_prefs_register_protocol_always_enabled
/// - 2010-02-17 - ��������� - ��� Tplug_create_wud
/// - 2010-02-15 - �������������� ��������� �����
/// - 2009-12-02 - ��������� - AT_DVB_MAC
/// - 2009-11-01 - ��������� - ������� wtap_encap_register (!��������� ������������ � ���������� API!)
/// - 2009-11-01 - ��������� - ������� wtap_encap_get_vals (!��������� ������������ � ���������� API!)
/// - 2009-10-14 - ��������� - ������� register_field_info (!��������� ������������ � ���������� API!)
/// - 2009-08-02 - ��������� - ������� PERFORM_COMMAND_START_TEST (��� ���������)
/// - 2009-08-02 - ��������� - ������� PERFORM_COMMAND_STOP_TEST (��� ���������)
/// - 2009-08-02 - �������� - �������� ����� TPluginProtoClass
/// - 2009-07-31 - ��������� - ����� ��������� ���� cbSize � ��������� TSWINEStandartFunctions.
/// - 2009-07-31 - ��������� - ��������� ��� ���������. !��������! ��������� ����� ������� � TSWINEStandartFunctions.
/// - 2009-05-14 - ������� - PREFS_XXX-������� �� ��������� TSWINEStandartFunctions
/// - 2009-05-14 - ��������� - Tplug_packet_info_set_token_path
/// - 2009-02-23 - ��������� - Tplug_packet_info_set_token_path
/// - 2009-02-23 - ��������� - Tplug_packet_info_set_token_entry
/// - 2009-02-23 - Tplug_packet_info_set_description -> Tplug_packet_info_ex_set_description
/// - 2009-02-23 - Tplug_packet_info_set_generic_name -> Tplug_packet_info_ex_set_generic_name
/// - 2009-02-23 - ������������ ����� - PacketInfo <-> PacketInfoEx
/// - 2009-02-23 - Tplug_packet_info_set_content_type -> Tplug_packet_info_ex_set_content_type
/// - 2009-02-23 - Tplug_packet_info_set_auth_info -> Tplug_packet_info_ex_set_auth_info
/// - 2009-02-23 - Tplug_packet_info_set_ident_info -> Tplug_packet_info_ex_set_ident_info
/// - 2009-02-22 - ��������� - Tplug_packet_info_ex_clone
/// - 2009-02-22 - ��������� - Tplug_packet_info_ex_clear
/// - 2009-02-22 - ��������� - Tplug_packet_info_ex_free
/// - 2009-02-22 - ��������� - Tplug_packet_info_ex_malloc
/// - 2009-02-21 - ��������� - TPacketInfoEx
/// - 2009-02-21 - ��������� - ack_ex-�������
/// - 2009-02-21 - ��������� - and_ack_ex-�������
/// - 2009-02-21 - ��������� - and_ack-�������
/// - 2009-02-21 - ��������� - interlocked-�������
/// - 2009-01-27 - ��������� - prefs_XXX-�������
/// - 2008-10-29 - TPacketInfo - ������� ���� "packetlen"
/// - 2008-10-29 - TPacketInfo - ������� ���� "file_size"
/// - 2008-10-29 - TPacketInfo - ���� "flags" � "tcp_flags" - �����������
/// - 2008-10-29 - TPacketInfo - ��������� "CT_ODLC"
/// - 2008-10-29 - TPacketInfo - ������� ���� "odlc_addr"
/// - 2008-10-29 - TPacketInfo - ������� ���� "odlc_session"
/// - 2008-10-29 - TPacketInfo - ������� ���� "ethertype"
/// - 2008-10-29 - TPacketInfo - ������� ���� "packetcounter"
/// - 2008-10-29 - TPacketInfo - ������� ���� "packettype"
/// - 2008-10-29 - TPacketInfo - ������� ���� "hec_err"
/// - 2008-10-29 - TPacketInfo - "token_entry" -> "token_enries"
/// - 2008-11-14 - ��������� ������� Tplug_add_log
/// - 2008-11-14 - ��������� ���� ��������� ��� Tplug_add_log
/// - 2008-11-14 - ������� Tplug_perform - ��������� ����������
/// - 2008-11-14 - ������� Tplug_ack - ��������� ����������
/// - 2008-12-10 - ��������� - prefs_XXX-�������
//
///TODO:
/// - �������� file_read
/// - ������� cache
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
/*                    �������� ������ ������� ��������                        */
/*                                                                            */
/******************************************************************************/

/*
 * 1. ����� ������� ������ ��������� ���������� "plugins" ��������, ��� ���������� exe-���� (�������
 *    �����������), �� ������� ������� dll-������ � ����������� ".dll". ��������� ��������� ����
 *    ����������� � � ��� ����������� ������� ������������ �������������� �������
 *      swine_plugin_init
 *
 * 2. ���������� ������� swine_plugin_init.
 */

/******************************************************************************/
/*                                                                            */
/*                      ��������� �������-�����������                         */
/*                                                                            */
/******************************************************************************/

/*
 * � ���������� ������ ���� ����������� ��������� �������������� ������� (����������� ���!):
 * "swine_plugin_init"
 */

/*****************************************************************************/

const gconstpchar SWINE_VERSION = "swine 0.8.7";

/* �������� ���������� ����� ������ */
typedef gpointer PkrTreeNode;
class TProtoReg;
typedef TProtoReg * PProtoReg;
/*void*/class TkrProtocol;

#define SWINE_STR_SIZE 128 /* ������ ������� ����� � ����������� �����, ������������ � ������� init_buf */

/* ��������� ������, � ������� �������� �������� � ����������� ����������  */
STRUCT_PACKED_BEGIN
typedef struct STRUCT_PACKED_ATTRIBUTE _tvbuff {
  gsize_t len; /* ������ ������ */
  guint8* buf; /* ���� ������ (���� � ����� ����) */
	gsize_t offset; // data link offset (number of bytes to the "left" of buf pointer)
} tvbuff_t;
STRUCT_PACKED_END

/***********************************************************************************/
// �����������
// ������ �������� - ������ 0
#define P2P_DIR_UNKNOWN   0
#define P2P_DIR_SENT      1
#define P2P_DIR_RECV      2

#define P2P_DIR_COUNT     3

// ������� �����
#define PI_SRC_SIZE     32        // ��������
#define PI_DST_SIZE     32        // ����������
#define PI_CONTENT_SIZE 12        // ��� ������

/* packet data type */
#define PDT_AUX     0
#define PDT_INFO    1
#define PDT_VPN     2 // !ready to delete!
#define PDT_VOIP    3 // !ready to delete!
#define PDT_AUTH    4
#define PDT_STAT    5 // statistics
#define PDT_ISTAT   6 // �������������� ������ (����������������� ����������) - ����� ����������
#define PDT_RAW_IP  7 // raw ip packets - auxiliary
#define PDT_IDLE    8 // service idle packet - no data
#define PDT_ISTAT1  6 // �������������� ������ (����������������� ����������) - � ������� <2�> (������������� PDT_ISTAT)
#define PDT_ISTAT2  9 // �������������� ������ (����������������� ����������) - � ������� <������ 83>
#define PDT_ISTAT3  10 // �������������� ������ (����������������� ����������) - � ������� <��>

/* ��������� ���� ��������� CRC */
typedef enum _TCRCType {
  CRC_NONE,              /* ��� CRC */
  CRC_OK,               /* ������� CRC */
  CRC_BAD             /* CRC ������ */
} TCRCType;

/* IP-����� */
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

// Ethernet-�����
STRUCT_PACKED_BEGIN
typedef struct STRUCT_PACKED_ATTRIBUTE _TEthAddr {
  guint8 s_b[6];
} TEthAddr, * PEthAddr;
STRUCT_PACKED_END

// "�����������"-�����
typedef union _TAddrPad {
  guint8 s_b[16];
  guint16 s_w[8];
} TAddrPad, * PAddrPad;

/* ���� ��������� ������� */
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

/* ���������� ��������� ������ */
typedef union _TAddress {
  TInAddr in_addr;
  TIn6Addr in6_addr;
  TEthAddr eth_addr;
  TAddrPad pad;
} TAddress, * PAddress;

/* ���� ������ */
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

/* ���� ��������������� ���� */
typedef enum _TCircuitType {
  CT_NONE,              /* no port number */
  CT_DLCI,              /* Frame Relay DLCI */
  CT_ISDN,              /* ISDN channel number */
  CT_X25,               /* X.25 logical channel number */
  CT_MPEG_TS,           /* MPEG-TS PID number */
  CT_ODLC               /* ODLC session */
  /* Could also have ATM VPI/VCI pairs */
} TCircuitType;

/* ���� ������ */
#define PG_OK        0 /* ������� */
#define PG_BAD       1 /* ������ */
#define PG_UNKNOWN   2 /* ����������� */
#define PG_NONE      3 /* �������������� */

/* ����� TCP-������ */
#define SF_HAS_SYN1         0x0001 /* ��� ���� SYN 1 */
#define SF_HAS_SYN2         0x0002 /* ��� ���� SYN 2 */
#define SF_HAS_FIN1         0x0004 /* ��� ���� FIN 1 */
#define SF_HAS_FIN2         0x0008 /* ��� ���� FIN 2 */
#define SF_HAS_SYN          0x0010 /* ��� ���� SYN */
#define SF_HAS_SYN_ACK      0x0020 /* ��� ���� SYN/ACK */
#define SF_HAS_DIRECT       0x0040 /* ���� ������ ������� ����������� */
#define SF_HAS_INDIRECT     0x0080 /* ���� ������ ��������� ����������� */
#define SF_HOLES            0x0100 /* ���� ����� */
#define SF_HAS_ACK_TO_FIN1  0x0200 /* ��� ���� ACK �� FIN 1 */
#define SF_HAS_ACK_TO_FIN2  0x0400 /* ��� ���� ACK �� FIN 2 */
#define SF_HAS_ADD_SUB_FILTER_BLOCKING  0x0800 /* ������������ ������ ����������/�������� ���-������� */

//   /* ��������� ������ */
// STRUCT_PACKED_BEGIN
// typedef struct STRUCT_PACKED_ATTRIBUTE _TPacketHeader {
//   gpchar buf; /* ������ ��������� */
//   gsize_t len; /* ������ ������ */
//   _TPacketHeader * next; /* ��������� �� ��������� (����������) ��������� */
// } TPacketHeader, * PPacketHeader;
// STRUCT_PACKED_END

//   /* �������� ������ */
// STRUCT_PACKED_BEGIN
// typedef struct STRUCT_PACKED_ATTRIBUTE _TPacketTrailer {
//   gpchar buf; /* ������ ��������� */
//   gsize_t len; /* ������ ������ */
//   _TPacketTrailer * next; /* ��������� �� ��������� (�������) �������� */
// } TPacketTrailer, * PPacketTrailer;
// STRUCT_PACKED_END

STRUCT_PACKED_BEGIN
typedef struct STRUCT_PACKED_ATTRIBUTE { /* ������ �������� */
  gpchar buf; /* ��������� �� ������ ������ ��������� (�� ������ ������ ������!) */
  gint32 len; /* ���������� �������� �� ��������� */
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

/* ���������� � ������
   �� ������������� ������������ ������ ��������� �� �������� (������ �� ���������)
   ��� ��������, ��������, ������� � ������������ ���������� ���������� ������������ �������
     Tpacket_info_malloc, Tpacket_info_free, Tpacket_info_clear, Tpacket_info_clone
 */
STRUCT_PACKED_BEGIN
typedef struct STRUCT_PACKED_ATTRIBUTE {
//   gsize_t cb;

  /*gpointer*/TkrProtocol * pred_proto; /* ��������� �� ���������� ����������� ��������� */
  gpointer pred_node; /* ��������� �� ���������� ������� ������ */

  guint32 pid; // PID
  guint32 lid; // LID

  Ttimeval tv; /* packet arrival time - ����� ������� - ������ */

  guint32  pattern; /* ��������, �� �������� ���� ��������������� */

  guint8  lnk_t;            /* Per-packet encapsulation/data-link type */
  guint8  genre;            /* ���� ������. ��-��������� PG_POST (0). ������������� ������������� ������ ��� �������� ������ */
  guint8  p2p_dir;          /* ����������� �������� */
  guint8  packet_data_type; /* ��� ������: ���������/�������������� */
  guint8  is_p2p_or_ext;    /* ����� ������ �������� ��� ����������� ��� �������� ���� Ext ��������� <�������> */
  guint8 quality;           /* packet quality multiplied by 100, 0 means undefined value */
  guint8 crctype;           /* ��� (���������) CRC (checksum) */

  guint8  ipproto;                /* IP-�������� (��� ��-IP ������� - ������ ����������) */
  guint32  flags;                 /* ����� ������ 2017-06-10 ��������� ���� SWINE_PI_FLAG_XXX, SGN_ADD_DATA_FLAG_XXX */

  // address block
  guint8 ctype;                /* type of circuit, for protocols with a VC identifier */
  guint8 dltype;               /* type of address */
  guint8 nettype;              /* type of address */
  guint8 ptype;                   /* ��� ����� */
  guint32 circuit_id;                /* circuit ID, for protocols with a VC identifier */
  TAddress  dl_src;                   /* link-layer source address */
  TAddress  dl_dst;                   /* link-layer destination address */
  TAddress  net_src;                  /* network-layer source address (network-format) */
  TAddress  net_dst;                  /* network-layer destination address (network-format) */
  guint32 srcport;                   /* ���� ��������� (host-format) */
  guint32 destport;                  /* ���� ��������� (host-format) */

//   gchar content[PI_CONTENT_SIZE]; /* ������� �������� - ��� ������� ������� /ANSI/ */
//   gpchar description; /* ������� �������� - ��� ������� �������; �������� ������ - ��� ������ � ����������� ������� /ANSI/ */
//   gpchar generic_name; /* �������� ��� ����� */
//   gpchar content_type; /* content-type */
//   gpchar auth_info; /* auth_info */
//   gpchar ident_info; /* ident_info */
  gpchar  header;     /* ��������� */
  guint32 header_len; /* ����� ��������� */

  Ttoken_entries* token_entries;
  gpchar token_path; /* ���� */

//   PPacketHeader headers; /* ��������� ������ */
//   PPacketTrailer trailers; /* ��������� ������ */

//   gpchar private_data;        // �������������� ������
//   guint32 private_len;        // ����� �������������� ������

  // added: 2014-07-21
  Ttimeval tv2; /* packet departure time - ����� ������� - ���������� */

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

/* ���������� � ������ (��������������)
   �� ������������� ������������ ������ ��������� �� �������� (������ �� ���������)
   ��� ��������, ��������, ������� � ������������ ���������� ���������� ������������ �������
     Tpacket_info_ex_malloc, Tpacket_info_ex_free, Tpacket_info_ex_clear, Tpacket_info_ex_clone
 */
STRUCT_PACKED_BEGIN
typedef struct STRUCT_PACKED_ATTRIBUTE {
  gchar content[PI_CONTENT_SIZE]; /* ������� �������� - ��� ������� ������� /ANSI/ */
  gpchar description; /* ������� �������� - ��� ������� �������; �������� ������ - ��� ������ � ����������� ������� /ANSI/ */
  gpchar generic_name; /* �������� ��� ����� */
  gpchar content_type; /* content-type */
  gpchar auth_info; /* auth_info */
  gpchar ident_info; /* ident_info */
} TPacketInfoEx, * PPacketInfoEx;
STRUCT_PACKED_END

/* ��������� ������ "��������" */
STRUCT_PACKED_BEGIN
struct STRUCT_PACKED_ATTRIBUTE TPluginProtoStuff {
  gpointer plug_inst; /* ��������� ������� */
  gpointer swine_inst; /* ��������� ������� ������ SWINE */
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

/* ���� ������� ��� ���������� ������� "��������" ������ �������
 * �������� stuff - ��������� �����������
 */

/// \name ������������ ������ ������ ��� ������� register_XXX, ack_XXX
/// \{

/// ����� ������ �������� ��� ����� (������ � ����������� �����), ���� ����� ������������� �� ���������
#define SWINE_DATA_BUFFER_FILE_NAME               gsize_t(-1)
/// ����� ������ �������� ��� ����� (������ � ����������� �����), ���� ����� ������������� ������ ���� ������
#define SWINE_DATA_BUFFER_FILE_NAME_UNLINK        gsize_t(-2)
/// ����� ������ �������� ���������� �����, ���������� ��������� XXX_file_create_XXX, ���������� � ���� ����� ������������� �� ���������
#define SWINE_DATA_BUFFER_FILE_HANDLE             gsize_t(-3)
/// ����� ������ �������� ���������� �����, ���������� ��������� XXX_file_create_XXX, ���������� � ���� ����� ������������� ������ ���� �������
#define SWINE_DATA_BUFFER_FILE_HANDLE_UNLINK      gsize_t(-4)

/// \}

/// \name ������� ��� ������� perform
/// \{
/// \sa Ttcpcat_plug_perform

/// ���������� ������������
#define PERFORM_COMMAND_BUILD       0
/// ���������� ������������
#define PERFORM_COMMAND_BIND        1
/// �������, �������������� ����������� ��������� ����� ���������
#define PERFORM_COMMAND_START       2
/// �������, �������������� ����������� ���������� ����� ���������
#define PERFORM_COMMAND_STOP        3
/// �������, �������������� ����������� ��������� ����� �����
#define PERFORM_COMMAND_START_TEST  4
/// �������, �������������� ����������� ���������� ����� �����
#define PERFORM_COMMAND_STOP_TEST   5
/// �������, �������������� ����������� ��������� ������� ��������
#define PERFORM_COMMAND_IDLE        6
/// �������, �������������� ����������� ��������� ��������� � ������������ ������ ("������" ����������)
#define PERFORM_COMMAND_FLUSH       7
/// �������, �������������� ����������� ������������� ��������� �������
#define PERFORM_COMMAND_SUSPEND     8
/// �������, �������������� ����������� ����������� ������ ��������� �������
#define PERFORM_COMMAND_RESUME      9
/// �������, �������������� ����������� �������� ����������
#define PERFORM_COMMAND_CLEAN      10

/// \}

/// ��������� ��� ������������� ������ ack_raw::flags (SGN_DATA_READY_FLAG_DO_MULTICAST_COPY ������ wrlr)
#define SWINE_ACK_RAW_AAA_DO_MULTICAST_COPY   0x00000001 // ������������ ����������, ������ �������� ������ �� �����, ����� �������� ��� �� ���� ��������� SGN-������������
                                                         // � ������ ��������������� ����������� � ������ SGN_ADD_DATA_FLAG_DO_NOT_MULTICAST_COPY
#define SGN_DATA_READY_FLAG_DO_MULTICAST_COPY	0x00000001 // deprecated: ��� �������������


/// ��������� ��� ������������� ������ TPacketInfo::flags (SGN_AddData_p::flags)
/// � �������� ������������ ��� ������ plug_crop, plug_heur
#define SWINE_PI_FLAG_SGN_DO_NOT_MULTICAST_COPY 0x00000001 // ��������� SGN-����������� �������� ������ ����� �� ����� � ������ SGN_DATA_READY_FLAG_DO_MULTICAST_COPY
                                                           // ������������, ���� ����� ��� ��� ������� ������ SGN-������������ � ������ SGN_DATA_READY_FLAG_DO_MULTICAST_COPY
                                                           // ������ ���� ��������� ��� �������������� ������������ ����� WRLR
#define SGN_ADD_DATA_FLAG_DO_NOT_MULTICAST_COPY 0x00000001 // deprecated: ��� �������������

#define SWINE_PI_FLAG_SGN_REQUEST_USER_INFO 0x00000002		 // ������� ������� ���������� �� ��������
                                                           // ��������������, ��� ������� ����� �������� ������ ����������� ������� ��������� ����-���� #7 (���� UNI, Ext, Data),
                                                           // �� ����������� ����� �����: UNI-C,TvSec, TvUSec, Length (��. �������� ���������)
#define SGN_ADD_DATA_FLAG_REQUEST_USER_INFO 0x00000002		 // deprecated: ��� �������������

#define SWINE_PI_FLAG_SGN_REQUEST_USER_LOCATION 0x00000004 // ������� ������� �������� �������������� ��������
                                                           // ��������������, ��� ������� ����� �������� ������ ����������� ������� ��������� ����-���� #8 (���� UNI),
                                                           // �� ����������� ����� �����: UNI-C,TvSec, TvUSec, Length (��. �������� ���������)
#define SGN_ADD_DATA_FLAG_REQUEST_USER_LOCATION 0x00000004 // deprecated: ��� �������������

/* �����������
 * ���������� ��� �������� ���������� ������� ������
 * ���������:
 *   ����� �� ���������� �������� ��������� ���������� ������ (������������ � ���� SWINEStuff.plug_inst)
 */
typedef gpointer (MSCU_CALL_PREFIX * Tplug_create)(PPluginProtoStuff stuff);
/* �����������
 * ���������� ��� �������� ���������� ������� ������
 * user_data - ��������, ���������� � ������� proto_register_protocol_wud
 * ���������:
 *   ����� �� ���������� �������� ��������� ���������� ������ (������������ � ���� SWINEStuff.plug_inst)
 */
typedef gpointer (MSCU_CALL_PREFIX * Tplug_create_wud)(PPluginProtoStuff stuff, gpointer user_data);
/* ����������
 *   ������ ���������� ���������� �������� ��������� ���������� ������ (����� ��������� � ���� SWINEStuff.plug_inst)
 */
typedef void (MSCU_CALL_PREFIX * Tplug_destroy)(PPluginProtoStuff stuff);
/* ���������� ������� (������� �� command)
 * PERFORM_COMMAND_BUILD
 *   ������������ ��� ����������� ������������ � ������ (plug_proto_register_dissector,
 *   plug_proto_register_dissector_table, plug_proto_register_heur_dissector_list)
 * PERFORM_COMMAND_BIND
 *   ������ ������������
 *   ������������ ��� ������ ������������ � ���������� ������������ � ������� (plug_proto_find_dissector,
 *   plug_proto_dissector_add, plug_proto_heur_dissector_add)
 * PERFORM_COMMAND_START
 *   ������ �����������
 *   ���������� � ������ �������� ���������
 * PERFORM_COMMAND_STOP
 *   ������� �����������
 *   ���������� � ����� �������� ���������
 * PERFORM_COMMAND_START_TEST
 *   ������ ����������� � �������� ������ (������ ��� ���������)
 *   ���������� � ������ �������� �������
 * PERFORM_COMMAND_STOP_TEST
 *   ������� ����������� � �������� ������ (������ ��� ���������)
 *   ���������� � ����� �������� �������
 * PERFORM_COMMAND_IDLE
 *   �������, ���������� �������� �� ��������
 * 	 ���������� � ��������, ������ 1 ��� ��� 100 ����
 * PERFORM_COMMAND_FLUSH
 *   ������� ���������� ������� �������� ����������� ����� ����������� ������ ���������
 * PERFORM_COMMAND_SUSPEND
 *   ������������ ���������, �������������� ��������� �����
 * PERFORM_COMMAND_RESUME
 *   ������������� ���������, ������������� ��������� �����, ����������������� ��� ��������� PERFORM_COMMAND_SUSPEND
 *
 * ���������:
 *   ���� 0, �������� ����������� � ��������
 *   ���� �� 0, �������� ������ �������
 */
typedef gboolean (MSCU_CALL_PREFIX * Tplug_perform)(PPluginProtoStuff stuff, gint command);
/* ��������� ��������� ������
 * ���������:
 *   tvb - ����� � ���������� ������
 *   pi - ���������� � ������; �������� ��� ���������� ��������� ����������, ��� � �������������
 *        ��� ���������� ������ ����������
 *   tree - �������������� ������ ������; ���� nil, �� ����� ���������� ��������� ������;
 *          ���� �� nil, �� ����� ��������� ������������ � � tree ����� �������� ���������� � ������ ���
 *          ����������� �����������
 */
typedef void (MSCU_CALL_PREFIX * Tplug_crop)(PPluginProtoStuff stuff, tvbuff_t* tvb, PPacketInfo pi, PkrTreeNode tree);
/* ������������� ����������� ������������ "������" ������
 * ���������:
 *   tvb - ����� � ���������� ������
 *   pi - ���������� � ������; �������� ��� ���������� ��������� ����������, ��� � �������������
 *        ��� ���������� ������ ����������
 * ���������:
 *   ���� �� 0, �� ���������� �������, ��� ��� ��� �����, ����� ���� ����, �� ���������� ���� �����
 *   � ����� plug_crop ������� ����������� (���������, ��� �� ��� ������ ������ plug_heur)
 *   ����������. ���� ����������� ���������� 0, ��� ���� ����������� pi (������� ����� ack-�������),
 *   �� ���������� �������������� ������������ pi ��� ������ packet_info_clone (� ����������� ��������� �� packet_info_free)
 *   � ������������ ���� � ����� �����, �������� ������������ pi ������������.
 */
typedef gboolean (MSCU_CALL_PREFIX * Tplug_heur)(PPluginProtoStuff stuff, tvbuff_t* tvb, PPacketInfo pi);
/* ��������� ��������� ������ �����������
 * ���������:
 *   tree - �������������� ������, � ������� ����� ������� ���������� � ���������
 */
typedef void (MSCU_CALL_PREFIX * Tplug_info)(PPluginProtoStuff stuff, PkrTreeNode tree);

/* ������� ������ "��������" */
STRUCT_PACKED_BEGIN
struct STRUCT_PACKED_ATTRIBUTE TPluginProtoClass {
  Tplug_create  plug_create; // ��� wud - Tplug_create_wud
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
/* ����������� ������� */

// ���������� ������, ��������������� ������ ��������
typedef gconstpchar (MSCU_CALL_PREFIX * Tplug_val_to_str)(gint32 value, const value_string* glossary, gconstpchar default_value);

// ����� �����������
//   ��� ������ ������� ����� ������ �����������, ������������������ � ������� plug_proto_register_dissector
typedef PPluginProtoStuff (MSCU_CALL_PREFIX * Tplug_proto_find_stuff_by_dissector)(gpointer dissector);

// ��������� ����� �������� ������ �����������
typedef void (MSCU_CALL_PREFIX * Tset_swine_current_module_name)(gconstpchar name);

/* �������-������������ (���������� �� DLL-������� plugin_init) */
// ����������� ������ ���������
//   name, short_name, filter_name - ������ (��� �����������), ������� (��� �����������) � ���������� ���
//   ���������� ��� ������ ���� ����������
//   description - �������� (��� �����������)
//   plug_class - ������ ������� ������ ����������� (����� ������ �������� ������ �������, ��������� plug_class ����� �������, �.�. ���������� ��������� ������������ � ���� ���������)
//   ���������� ����� ���������� ���������, ������� ����� ���� ����������� � ������ ��������
//   !��������! ���� ���������� � ������ ���������� ������ ��� ������, �������� �������������� � ������������ ����� ���������� ���������, ��������� �����
typedef PProtoReg (MSCU_CALL_PREFIX * Tplug_proto_register_protocol)(gconstpchar name, gconstpchar short_name, gconstpchar filter_name, gconstpchar description, PPluginProtoClass plug_class);
typedef PProtoReg (MSCU_CALL_PREFIX * Tplug_proto_register_protocol_always_enabled)(gconstpchar name, gconstpchar short_name, gconstpchar filter_name, gconstpchar description, PPluginProtoClass plug_class); // 2010-02-17

typedef PProtoReg (MSCU_CALL_PREFIX * Tplug_proto_register_protocol_wud)(gconstpchar name, gconstpchar short_name, gconstpchar filter_name, gconstpchar description, PPluginProtoClass plug_class, gpointer user_data);
typedef PProtoReg (MSCU_CALL_PREFIX * Tplug_proto_register_protocol_wud_always_enabled)(gconstpchar name, gconstpchar short_name, gconstpchar filter_name, gconstpchar description, PPluginProtoClass plug_class, gpointer user_data); // 2010-02-17
// ����������� ������ ���������� ���������
// ���������� ����� ���������� ���������, ������� ����� ���� ����������� ��� ����������� ����������
typedef preference_p (MSCU_CALL_PREFIX * Tplug_prefs_register_protocol)(PProtoReg proto);
typedef preference_p (MSCU_CALL_PREFIX * Tplug_prefs_register_protocol_always_enabled)(PProtoReg proto); // 2010-02-17

// ����������� ������ ��������
//   name, short_name, filter_name - ������ (��� �����������), ������� (��� �����������) � ���������� ���
//   ���������� ��� ������ ���� ����������
//   description - �������� (��� �����������)
//   plug_class - ������ ������� ������ ����������� (����� ������ �������� ������ �������, ��������� plug_class ����� �������, �.�. ���������� ��������� ������������ � ���� ���������)
//   ���������� ����� ���������� ���������, ������� ����� ���� ����������� � ������ ��������
//   !��������! ���� ���������� � ������ ���������� ������ ��� ������, �������� �������������� � ������������ ����� ���������� ���������, ��������� �����
typedef PProtoReg (MSCU_CALL_PREFIX * Tplug_deco_register_decoder)(gconstpchar name, gconstpchar short_name, gconstpchar filter_name, gconstpchar description, PPluginProtoClass plug_class);
// ����������� ������ ���������� ���������
// ���������� ����� ���������� ���������, ������� ����� ���� ����������� ��� ����������� ����������
typedef preference_p (MSCU_CALL_PREFIX * Tplug_prefs_register_decoder)(PProtoReg proto);

/* ������ �� ���������� TPacketInfo */
// ������������ �������� ������ ���������� � ������
typedef PPacketInfo (MSCU_CALL_PREFIX * Tpacket_info_malloc)();
// �������� ������
typedef void (MSCU_CALL_PREFIX * Tpacket_info_free)(PPacketInfo PacketInfo);
// �������� ����� ������
typedef void (MSCU_CALL_PREFIX * Tpacket_info_clear)(PPacketInfo PacketInfo);
// ������������ ������ (�������� ����� ������ � ���������� ������ ������)
typedef PPacketInfo (MSCU_CALL_PREFIX * Tpacket_info_clone)(PPacketInfo PacketInfo);
// ������������ ��������� ������
typedef void (MSCU_CALL_PREFIX * Tpacket_info_tokens_clone)(PPacketInfo src, PPacketInfo dst);
/* ������ �� ���������� TPacketInfoEx */
// ������������ �������� ������ ���������� � ������
typedef PPacketInfoEx (MSCU_CALL_PREFIX * Tpacket_info_ex_malloc)();
// �������� ������
typedef void (MSCU_CALL_PREFIX * Tpacket_info_ex_free)(PPacketInfoEx PacketInfoEx);
// �������� ����� ������
typedef void (MSCU_CALL_PREFIX * Tpacket_info_ex_clear)(PPacketInfoEx PacketInfoEx);
// ������������ ������ (�������� ����� ������ � ���������� ������ ������)
typedef PPacketInfoEx (MSCU_CALL_PREFIX * Tpacket_info_ex_clone)(PPacketInfoEx PacketInfoEx);
/* ��������� ��������
 * ���� buf == 0, �� ��� ���������
 */
typedef void (MSCU_CALL_PREFIX * Tpacket_info_ex_set_description)(PPacketInfoEx PacketInfoEx, gconstpchar buf);
/* ��������� ����� �����
 * ���� buf = nil, �� ��� ���������
 */
typedef void (MSCU_CALL_PREFIX * Tpacket_info_ex_set_generic_name)(PPacketInfoEx PacketInfoEx, gconstpchar buf);
/* ��������� content-type
 * ���� buf = nil, �� ��� ���������
 */
typedef void (MSCU_CALL_PREFIX * Tpacket_info_ex_set_content_type)(PPacketInfoEx PacketInfoEx, gconstpchar buf);
/* ��������� auth_info
 * ���� (buf == 0), �� ��� ���������
 */
typedef void (MSCU_CALL_PREFIX * Tpacket_info_ex_set_auth_info)(PPacketInfoEx PacketInfoEx, gconstpchar buf);
/* ��������� ����������������� ���������� ident_info
 *
 * buf - �������� ������ � ��������� ���� (������ � ����������� �����), ����� ���� 0
 *       �������� � ����: <�������_1>;<�������_2>;...;<�������_N>
 *       �������� \c <�������>, ���������� ������� "����� � �������", "������� �������", ����������� �������� ���������: \code "<�������>" \endcode.
 *       ��� ����, ������� �������, ������������ � �������� \c <�������>, �����������: \code "I:MAIL_SUBJECT=subject;""mail delivery""" \endcode
 *       ��������� ��������� ���� ���������:
 *       - �������� ����� (��������������) - IDENTIFIER:
 *           I:<���>[/<�����������>][/<��������>]=<��������>
 *
 *           <���> - �������� ��������� (��������� �������): IP, PORT
 *           <�����������> - CALL ��� ANSW (�������������� ��������� � ������� ��� ��������� �����������)
 *           <��������> - �������������� ��������� � ������������� ���������
 *           <��������> - �������� ��������� (���� �������� ���������� � �������� 0xEF,0xBB,0xBF - ���������, ��� ��������� - UTF-8, ����� - WIN1251)
 *
 *           ������: "I:IP/CALL=195.200.200.1"
 *
 * ���� (buf == 0), �� ����������������� ���������� ���������
 */
typedef void (MSCU_CALL_PREFIX * Tpacket_info_ex_set_ident_info)(PPacketInfoEx PacketInfoEx, gconstpchar buf);
/* ��������� header
 * ���� buf = nil, �� ��� ���������
 */
typedef void (MSCU_CALL_PREFIX * Tpacket_info_set_header)(PPacketInfo PacketInfo, gpchar buf, guint32 len);

typedef void (MSCU_CALL_PREFIX * Tpacket_info_set_token_path)(PPacketInfo PacketInfo, gpchar buf);
typedef void (MSCU_CALL_PREFIX * Tpacket_info_set_token_entry)(PPacketInfo PacketInfo, gint idx, gpchar buf, guint32 len);

// added 2016-05-11
typedef void (MSCU_CALL_PREFIX * Tpacket_info_set_id_token_path)(PPacketInfo PacketInfo, guint32 id, gpchar buf);
typedef void (MSCU_CALL_PREFIX * Tpacket_info_set_id_token_entry)(PPacketInfo PacketInfo, guint32 id, gint idx, gpchar buf, guint32 len);

// ���������� ������ � ������ �������� ������
//   AParent - ����-��������
//   ���������� ����� ��������� ����, ������� ����� ����� ���� ���������� ���
//     ����� ��������� �����
typedef PkrTreeNode (MSCU_CALL_PREFIX * Tplug_tree_add)(PkrTreeNode AParent, gconstpchar AText);

// ����� ��������������� ���������
/// !������ ������� �������� ����������, ����������� msculib::klogf(MT_XXX, "[<��������_������>] <���������>" <���������>) ������ ���!
/// \param message_type - ���� �� �������� MT_XXX	(���������� � mscu_types.h)
typedef void (MSCU_CALL_PREFIX * Tplug_proto_add_log)(PPluginProtoStuff stuff, gconstpchar message, gint message_type);

// �������� ������ �� ����� (��������� ���������)
//   ����� ���������� �� ����� � ��������� �������:
//     - ����� �������� (������ CRC, ����� � �.�.) � �� ������
//     - ����������� ������������� ��������� ���������� ������ ��������� (����� ����������)
//     - ����� ������� � ������������ (��������� ��� ����� ���������)
/// \param tvb.buf - ��������� �� ����� ������/��� �����/���������� ����� (������������ ��������� � ������� SWINE_DATA_BUFFER_XXX)
/// \param tvb.len - ���������� ���� � ������ ������/��� ������ (������������ �������� ������ SWINE_DATA_BUFFER_XXX)
typedef void (MSCU_CALL_PREFIX * Tplug_proto_ack)(PPluginProtoStuff stuff, tvbuff_t* tvb, PPacketInfo pi);

// �������� ������ �� ����� (��������� ���������)
//   ����� ���������� �� ����� � ��������� �������:
//     - ����� �������� (������ CRC, ����� � �.�.) � �� ������
//     - ����������� ������������� ��������� ���������� ������ ��������� (����� ����������)
//     - ����� ������� � ������������ (��������� ��� ����� ���������)
/// \param tvb.buf - ��������� �� ����� ������/��� �����/���������� ����� (������������ ��������� � ������� SWINE_DATA_BUFFER_XXX)
/// \param tvb.len - ���������� ���� � ������ ������/��� ������ (������������ �������� ������ SWINE_DATA_BUFFER_XXX)
// pi_ex - �������������� ���������� � ������ (����� ���� 0)
//   ������ ���� ������� ���������� � ������� packet_info_ex_malloc
//   ����� ������ ������ ������� �������� pi_ex ���������� ����������������
typedef void (MSCU_CALL_PREFIX * Tplug_proto_ack_ex)(PPluginProtoStuff stuff, tvbuff_t* tvb, PPacketInfo pi, PPacketInfoEx pi_ex);

/// �������� ������ �� ����� (��������� ���������)
///
/// ���������� ������� Tplug_proto_ack_ex (��. ����), �� ����������� ��������������� ���������
///
/// \param tvb_svc.buf - ��������� �� ����� ������ ���������� ��������� (����������)
/// \param tvb_svc.len - ���������� ���� � ������ tvb_svc.buf
///
typedef void (MSCU_CALL_PREFIX * Tplug_proto_ack_ex_svc)(PPluginProtoStuff stuff, tvbuff_t* tvb, PPacketInfo pi, PPacketInfoEx pi_ex, tvbuff_t* tvb_svc);

/// �������� ����� ������� �� ����� (��������� ���������)
///
/// ���������� ������� Tplug_proto_ack_ex (��. ����), �� �����������
///
/// \param tvb - ������� ����� (������� �������� ������������ ������������ ����� ���������� ������ crop/heur)
/// \param pi - ������������ ���� tv � ������, ���� �������� tv ����� 0
///							(�.�. pi ����� ���� ����� 0 � ������, ���� tv �� ����� 0)
/// \param in uins - ������ �������� UIN, �� ������� ������������ �����
/// \param in uins_ext - ������ �������� UIN_EXT, �� ������� ������������ �����
/// \param in uins_count - ���������� ��������� � ��������
/// \param in tv - ��������� ����� ��� �������� �������, ���� ����� 0, �� ������������ ��������� ����� �� pi
/// \param flags - ����� ������, ����� �������� SWINE_ACK_RAW_XXX (��.����)
///
/// ����� ����� ������������ ������ ��� ���������� � uins_ext ������:
///   TERI_ID_EXT_RF_RAW_MAC - �������� �� ��������� - � ���������� ���������� ������
///   TERI_ID_EXT_RF_RAW_IP  - �������� IP-������ ��� ��������� ���������� ������ (������������ ���� offset � tvb)
///
typedef void (MSCU_CALL_PREFIX * Tplug_proto_ack_raw)(PPluginProtoStuff stuff, tvbuff_t* tvb, PPacketInfo pi, guint32 * uins, guint32 * uins_ext, guint32 uins_count, Ttimeval * tv, guint32 flags);

// �������� ������ �� ��������� ���������� ��������� (�� �������)
// stuff ����� ���� ����� 0
//   ��������, �������� Van Jacobson ����� ��������� ������ (�������������� TCP/IP) ���������
//   �������� ����� ��������� PPP ��� ���������� ���������
typedef gboolean (MSCU_CALL_PREFIX * Tplug_proto_forward_packet)(PPluginProtoStuff stuff, gpointer proto, tvbuff_t* tvb, PPacketInfo pi);
// ����� � ������� ����������� �� ����� � �������� ��� ������ ��� ���������
//   ��������, �������� TCP ��������� ������� ������ � plug_create ��� ������ ������� plug_proto_register_dissector_table,
//   � � �������� ��������� �������� ������ ������� ��� ������ �����������, "��������" �� ������������ ����� (HTTP, SMTP � �.�.),
//   � �������� ������ ���������� �����������
typedef gboolean (MSCU_CALL_PREFIX * Tplug_proto_dissector_try_port)(PPluginProtoStuff stuff, gpointer sub_dissectors, guint32 port, tvbuff_t* tvb, PPacketInfo pi);
// ����� � ������������� ������� ����������� �� ����� � �������� ��� ������ ��� ���������
//   ��������, �������� TCP ��������� ������� ������������� ������ � plug_create ��� ������ ������� plug_proto_register_heur_dissector_list,
//   � � �������� ��������� �������� ������ ������� ��� ������ �����������;
//   ������� ���������� �������� ��� ������������������ ������������� ����������� (plug_try_heuristic)
//   � � ������ �������������� ������� ������ �� ��� ���������� �����
typedef gboolean (MSCU_CALL_PREFIX * Tplug_proto_dissector_try_heuristic)(PPluginProtoStuff stuff, gpointer sub_dissectors, tvbuff_t* tvb, PPacketInfo pi);
// �������� ������ �� ��������� ���������� ��������� (�� �������) - ����������� ��� ���������
//   ��������, �������� Van Jacobson ����� ��������� ������ (�������������� TCP/IP) ���������
//   �������� ����� ��������� PPP ��� ���������� ���������
/// \param tvb.buf - ��������� �� ����� ������/��� �����/���������� ����� (������������ ��������� � ������� SWINE_DATA_BUFFER_XXX)
/// \param tvb.len - ���������� ���� � ������ ������/��� ������ (������������ �������� ������ SWINE_DATA_BUFFER_XXX)
typedef gboolean (MSCU_CALL_PREFIX * Tplug_proto_forward_packet_and_ack)(PPluginProtoStuff stuff, gpointer proto, tvbuff_t* tvb, PPacketInfo pi);
// ����� � ������� ����������� �� ����� � �������� ��� ������ ��� ��������� - ����������� ��� ���������
//   ��������, �������� TCP ��������� ������� ������ � plug_create ��� ������ ������� plug_proto_register_dissector_table,
//   � � �������� ��������� �������� ������ ������� ��� ������ �����������, "��������" �� ������������ ����� (HTTP, SMTP � �.�.),
//   � �������� ������ ���������� �����������
/// \param tvb.buf - ��������� �� ����� ������/��� �����/���������� ����� (������������ ��������� � ������� SWINE_DATA_BUFFER_XXX)
/// \param tvb.len - ���������� ���� � ������ ������/��� ������ (������������ �������� ������ SWINE_DATA_BUFFER_XXX)
typedef gboolean (MSCU_CALL_PREFIX * Tplug_proto_dissector_try_port_and_ack)(PPluginProtoStuff stuff, gpointer sub_dissectors, guint32 port, tvbuff_t* tvb, PPacketInfo pi);
// ����� � ������������� ������� ����������� �� ����� � �������� ��� ������ ��� ��������� - ����������� ��� ���������
//   ��������, �������� TCP ��������� ������� ������������� ������ � plug_create ��� ������ ������� plug_proto_register_heur_dissector_list,
//   � � �������� ��������� �������� ������ ������� ��� ������ �����������;
//   ������� ���������� �������� ��� ������������������ ������������� ����������� (plug_try_heuristic)
//   � � ������ �������������� ������� ������ �� ��� ���������� �����
/// \param tvb.buf - ��������� �� ����� ������/��� �����/���������� ����� (������������ ��������� � ������� SWINE_DATA_BUFFER_XXX)
/// \param tvb.len - ���������� ���� � ������ ������/��� ������ (������������ �������� ������ SWINE_DATA_BUFFER_XXX)
typedef gboolean (MSCU_CALL_PREFIX * Tplug_proto_dissector_try_heuristic_and_ack)(PPluginProtoStuff stuff, gpointer sub_dissectors, tvbuff_t* tvb, PPacketInfo pi);

// �������� ������ �� ��������� ���������� ��������� (�� �������) - ����������� ��� ���������
//   ��������, �������� Van Jacobson ����� ��������� ������ (�������������� TCP/IP) ���������
//   �������� ����� ��������� PPP ��� ���������� ���������
/// \param tvb.buf - ��������� �� ����� ������/��� �����/���������� ����� (������������ ��������� � ������� SWINE_DATA_BUFFER_XXX)
/// \param tvb.len - ���������� ���� � ������ ������/��� ������ (������������ �������� ������ SWINE_DATA_BUFFER_XXX)
// pi_ex - �������������� ���������� � ������ (����� ���� 0)
//   ������ ���� ������� ���������� � ������� packet_info_ex_malloc
//   ����� ������ ������ ������� �������� pi_ex ���������� ����������������
typedef gboolean (MSCU_CALL_PREFIX * Tplug_proto_forward_packet_and_ack_ex)(PPluginProtoStuff stuff, gpointer proto, tvbuff_t* tvb, PPacketInfo pi, PPacketInfoEx pi_ex);

/// �������� ������ �� ��������� ���������� ��������� (�� �������) - ����������� ��� ���������
///
/// ���������� ������� Tplug_proto_forward_packet_and_ack_ex (��. ����), �� ����������� ��������������� ���������
///
/// \param tvb_svc.buf - ��������� �� ����� ������ ���������� ��������� (����������)
/// \param tvb_svc.len - ���������� ���� � ������ tvb_svc.buf
///
typedef gboolean (MSCU_CALL_PREFIX * Tplug_proto_forward_packet_and_ack_ex_svc)(PPluginProtoStuff stuff, gpointer proto, tvbuff_t* tvb, PPacketInfo pi, PPacketInfoEx pi_ex, tvbuff_t* tvb_svc);

// ����� � ������� ����������� �� ����� � �������� ��� ������ ��� ��������� - ����������� ��� ���������
//   ��������, �������� TCP ��������� ������� ������ � plug_create ��� ������ ������� plug_proto_register_dissector_table,
//   � � �������� ��������� �������� ������ ������� ��� ������ �����������, "��������" �� ������������ ����� (HTTP, SMTP � �.�.),
//   � �������� ������ ���������� �����������
/// \param tvb.buf - ��������� �� ����� ������/��� �����/���������� ����� (������������ ��������� � ������� SWINE_DATA_BUFFER_XXX)
/// \param tvb.len - ���������� ���� � ������ ������/��� ������ (������������ �������� ������ SWINE_DATA_BUFFER_XXX)
// pi_ex - �������������� ���������� � ������ (����� ���� 0)
//   ������ ���� ������� ���������� � ������� packet_info_ex_malloc
//   ����� ������ ������ ������� �������� pi_ex ���������� ����������������
typedef gboolean (MSCU_CALL_PREFIX * Tplug_proto_dissector_try_port_and_ack_ex)(PPluginProtoStuff stuff, gpointer sub_dissectors, guint32 port, tvbuff_t* tvb, PPacketInfo pi, PPacketInfoEx pi_ex);

/// ����� � ������� ����������� �� ����� � �������� ��� ������ ��� ��������� - ����������� ��� ���������
///
/// ���������� ������� Tplug_proto_dissector_try_port_and_ack_ex (��. ����), �� ����������� ��������������� ���������
///
/// \param tvb_svc.buf - ��������� �� ����� ������ ���������� ��������� (����������)
/// \param tvb_svc.len - ���������� ���� � ������ tvb_svc.buf
///
typedef gboolean (MSCU_CALL_PREFIX * Tplug_proto_dissector_try_port_and_ack_ex_svc)(PPluginProtoStuff stuff, gpointer sub_dissectors, guint32 port, tvbuff_t* tvb, PPacketInfo pi, PPacketInfoEx pi_ex, tvbuff_t* tvb_svc);

// ����� � ������������� ������� ����������� �� ����� � �������� ��� ������ ��� ��������� - ����������� ��� ���������
//   ��������, �������� TCP ��������� ������� ������������� ������ � plug_create ��� ������ ������� plug_proto_register_heur_dissector_list,
//   � � �������� ��������� �������� ������ ������� ��� ������ �����������;
//   ������� ���������� �������� ��� ������������������ ������������� ����������� (plug_try_heuristic)
//   � � ������ �������������� ������� ������ �� ��� ���������� �����
/// \param tvb.buf - ��������� �� ����� ������/��� �����/���������� ����� (������������ ��������� � ������� SWINE_DATA_BUFFER_XXX)
/// \param tvb.len - ���������� ���� � ������ ������/��� ������ (������������ �������� ������ SWINE_DATA_BUFFER_XXX)
// pi_ex - �������������� ���������� � ������ (����� ���� 0)
//   ������ ���� ������� ���������� � ������� packet_info_ex_malloc
//   ����� ������ ������ ������� �������� pi_ex ���������� ����������������
typedef gboolean (MSCU_CALL_PREFIX * Tplug_proto_dissector_try_heuristic_and_ack_ex)(PPluginProtoStuff stuff, gpointer sub_dissectors, tvbuff_t* tvb, PPacketInfo pi, PPacketInfoEx pi_ex);

/// ����� � ������������� ������� ����������� �� ����� � �������� ��� ������ ��� ��������� - ����������� ��� ���������
///
/// ���������� ������� Tplug_proto_dissector_try_heuristic_and_ack_ex (��. ����), �� ����������� ��������������� ���������
///
/// \param tvb_svc.buf - ��������� �� ����� ������ ���������� ��������� (����������)
/// \param tvb_svc.len - ���������� ���� � ������ tvb_svc.buf
///
typedef gboolean (MSCU_CALL_PREFIX * Tplug_proto_dissector_try_heuristic_and_ack_ex_svc)(PPluginProtoStuff stuff, gpointer sub_dissectors, tvbuff_t* tvb, PPacketInfo pi, PPacketInfoEx pi_ex, tvbuff_t* tvb_svc);

//////////////////////////////////////////////////////////////////////////

/// ����� ��������� ��������� ������ � �������� ������ spots ������� bufs (� ������� lens).
/// ���� ������� ������, ���������� ������� ��������� ������ cb (��� ������� ���������� ��������) - � ���� ������ token->id �������� UIN
/// � ������ ���� ������ � ������ ������ �������� �� ����� �� ��������� ���������.
/// ���� ����� ���� ��������, ������� �������� � ������ ����������� ������, ����� ������ � ������ ������ �� ����� �� ��������� ��������� �� ��������.
/// � ������ ����������� ������ ������ ������ �������������� ������ ������, ���������� ������ �������� (������������� ������������ ��������).
///
/// \param in stuff - ��������, ������������ ��� ������ ������� \ref Tplug_create, � ������������ ��������� �����������
/// \param in pi		- �������������� ��������� ���������
/// \param in count - ���������� ������� ������
/// \param in bufs - ������ ������� ������
/// \param in lens - ������ ���� ������� ������
/// \param in spots - ������ �������� ������ \ref teri_bis.h
/// \param in cb - ����� ������� ��������� ������ (\ref teri_bis.h)
/// \param in ud - ������ �������� ������� ��������� ������
///
/// !��������! � ������ ���� ������ ������� ����� ������������ ������ ������ ������ plug_session_begin.
///
/// !��������! � ������ ����������� ������ ������� ��������� ������ ����� ���� �� ���� �� ������� ��� ������������� ������������ ��������.
///
/// \return � ������ ������ ������������ ���������� ��������� ���������
/// \return � ������ ������� ������������ ������������� �������� (��� ������)
///
typedef gint (MSCU_CALL_PREFIX * Tplug_proto_srm_teri_match)(PPluginProtoStuff stuff, PPacketInfo pi, gint count, gconstpointer* bufs, guint* lens, guint* spots, Tteri_bis_match_callback cb, void *ud);

//////////////////////////////////////////////////////////////////////////
// ����������, ��� ���������� ������ ������ �������� �������������� ������ ����� ������
// ������������� ������� ��������� ��������� �������� ���������, �.�. � ����� ������ ���������� � �������� ��������� �� ���������
// � �������������� ��������� ��������� ������
#define COMPLEX_TERI_MATCH_RF_RAW_ONLY 1

/// ������� �����
/// ����� ��������� ��������� ������ � �������� ������ spots ������� bufs (� ������� lens).
/// ���� ������� ������, ���������� ������� ��������� ������ cb (��� ������� ���������� ��������) - � ���� ������ token->id �������� UIN, token->id_ext �������� UIN_EXT
/// ���� ������� �������� � ������� TERI_ID_EXT_RF_RAW_MAC/TERI_ID_EXT_RF_RAW_IP, �� � ������ ��������� TCP-������, ������ ������������� �������� �� ����� �� ��������� ���������.
/// ���� ������� �������� � ������� TERI_ID_EXT_RF_RAW_MAC/TERI_ID_EXT_RF_RAW_IP, �� ������ ������ ���������� �������� ������ � ������� ������� plug_proto_ack_raw.
/// ���� ������� �������� � ������� TERI_ID_EXT_RF_DECODED, ���������� ������ ������ ������������ � ���������������� ������.
/// � ��������� ������ ������ ������ ���������� �� ����������� ������.
///
/// \param in stuff - ��������, ������������ ��� ������ ������� \ref Tplug_create, � ������������ ��������� �����������
/// \param in flags - ����� ������ ������, ��������� COMPLEX_TERI_MATCH_XXX
/// \param in pi		- �������������� ��������� ���������
/// \param in count - ���������� ������� ������
/// \param in bufs - ������ ������� ������
/// \param in lens - ������ ���� ������� ������
/// \param in spots - ������ �������� ������ \ref teri_bis.h
/// \param in cb - ����� ������� ��������� ������ (\ref teri_bis.h)
/// \param in ud - ������ �������� ������� ��������� ������
/// \param out has_rf_decoded - ��������� �� ���� ����, ��� ���� ������� DECODED-�������� (����� ����� ���� ����� 0)
/// \param out has_rf_raw - ��������� �� ���� ����, ��� ���� ������� RAW-�������� (����� ����� ���� ����� 0)
/// \param out out_uins	- ��������� �� ������ �������� UNI ��������� ��������� (����� ����� ���� ����� 0) - �������� ��������� ������ �� ���������� ������ ������ �������
/// \param out out_uins_ext - ��������� �� ������ �������� UNI_EXT ��������� ��������� (����� ����� ���� ����� 0) - �������� ��������� ������ �� ���������� ������ ������ �������
/// \param out out_uins_count - ��������� �� �������� ���������� ��������� ��������� - ������ �������� out_uins/out_uins_ext (����� ����� ���� ����� 0) - �������� ��������� ������ �� ���������� ������ ������ �������
///
/// !��������! ������ ������� ����� ������������ ������ ������ ������ ������� ���������.
///
/// \return � ������ ������ ������������ ���������� ��������� ���������
/// \return � ������ ������� ������������ ������������� �������� (��� ������)
///
typedef gint (MSCU_CALL_PREFIX * Tplug_proto_complex_teri_match)(PPluginProtoStuff stuff, guint32 flags, PPacketInfo pi, gint count, gconstpchar* bufs, gint32* lens, guint32* spots, Tteri_bis_match_callback cb, void *ud, gboolean * has_rf_decoded, gboolean * has_rf_raw, guint32 ** out_uins, guint32 ** out_uins_ext, guint32 * out_uins_count);

/// ������� �� ���������� �������
/// \param in bufs - ������ ������� ������
/// \param in lens - ������ ���� ������� ������
/// \param in spots - ������ �������� ������ \ref teri_bis.h
typedef gint (MSCU_CALL_PREFIX * Tplug_proto_complex_teri_match_retro)(PPluginProtoStuff stuff, guint32 flags, PPacketInfo pi, gint count, gconstpointer* bufs, guint* lens, guint* spots, Tteri_bis_match_callback cb, void *ud, gboolean * has_rf_decoded, gboolean * has_rf_raw, guint32 ** out_uins, guint32 ** out_uins_ext, guint32 * out_uins_count);
//////////////////////////////////////////////////////////////////////////

/* �������, ������������ � Create */
// ����������� �����������
//   ���������� ��� ����, ����� ��������� ��������� ����������� ���������
//   (dissector - � ���������������� TPluginProtoStuff.swine_inst) ���� ����� ������ ������������
//   ��� ������ ������� plug_proto_find_dissector ��� ������� name
typedef void (MSCU_CALL_PREFIX * Tplug_proto_register_dissector)(PPluginProtoStuff stuff, gconstpchar name);
// ����������� ������� ������������
//   ����� �������� � ��� ����� ��������� ����������� ��� ������ ������� plug_proto_dissector_add,
//   � ����� ������������ � ������� ������� plug_proto_dissector_try_port
typedef gpointer (MSCU_CALL_PREFIX * Tplug_proto_register_dissector_table)(PPluginProtoStuff stuff, gconstpchar name, gint key_type);
// ����������� ������� ���������
//   ����� �������� � ��� ����� ��������� ����������� ��� ������ ������� plug_proto_heur_dissector_add,
//   � ����� ������������ � ������� ������� plug_proto_dissector_try_heuristic
typedef gpointer (MSCU_CALL_PREFIX * Tplug_proto_register_heur_dissector_list)(PPluginProtoStuff stuff, gconstpchar name);
// ����������� ����
//   ����� �������� ����� ������������ ��� �������������� ����� �������������:
//   ���� ���������� � ������� ������ ������� ������������ ����� �� ���� ������
//   ������ � ������� ������� plug_proto_find_field_info �������� ���� ����� ��� �������������
typedef void (MSCU_CALL_PREFIX * Tplug_proto_register_field_info)(PPluginProtoStuff stuff, gconstpchar name, gpointer value);

/* �������, ������������ � Bind */

// ����� �����������
//   ��� ������ ������� ����� ������ �����������, ������������������ � ������� plug_proto_register_dissector
typedef gpointer (MSCU_CALL_PREFIX * Tplug_proto_find_dissector)(PPluginProtoStuff stuff, gconstpchar name);
//   ��� ������ ������� ����� ������ �����������, ������������������ � ������� plug_proto_register_dissector_table
typedef gpointer (MSCU_CALL_PREFIX * Tplug_proto_find_dissector_table)(PPluginProtoStuff stuff, gconstpchar name);
//   ��� ������ ������� ����� ������ �����������, ������������������ � ������� plug_proto_register_heur_dissector_list
typedef gpointer (MSCU_CALL_PREFIX * Tplug_proto_find_heur_dissector_list)(PPluginProtoStuff stuff, gconstpchar name);
// ����� ������������������� ����
typedef gpointer (MSCU_CALL_PREFIX * Tplug_proto_find_field_info)(PPluginProtoStuff stuff, gconstpchar name);
// ���������� ����������� � �������
//   ������ ������� ������������ ���� pattern ����������� proto � ������� � ������ name ��� ����������� ������������� �������� plug_proto_dissector_try_port
typedef void (MSCU_CALL_PREFIX * Tplug_proto_dissector_add)(PPluginProtoStuff stuff, gconstpchar name, guint32 pattern);
// ���������� ����������� � ������� ���������
//   ������ ������� ���������� proto � ������� � ������ name ��� ����������� ������������� �������� plug_proto_dissector_try_heuristic
typedef void (MSCU_CALL_PREFIX * Tplug_proto_heur_dissector_add)(PPluginProtoStuff stuff, gconstpchar name);

/// �������� �����.
///
/// � ������ �������� ���������� ���������� � fhandle ��������� ���������� �����.
///
/// ��� ������ � ���� ������������ \ref Tplug_file_write.
///
/// ��� ������ �� ����� ������������ \ref Tplug_file_read.
///
/// ��� �������� � �������� ����� ������������ \ref Tplug_file_close.
///
/// ��� ����������� ����� ������������ \ref Tplug_XXX_ack.
///
/// \param in stuff - ��������, ������������ ��� ������ ������� \ref Tplug_register, � ������������ ������� �������� ������
/// \param in flags - ����� ������ - �� ������������ (���������������)
/// \param[out] fhandle - ���������� ���������� ����� (������������ ���������: \ref Tplug_XXX_ack,
///   \ref Tplug_file_write, \ref Tplug_file_read, \ref Tplug_file_close).
///
/// \return � ������ ������ ���������� 0, � fhandle ������������ ���������� ���������� �����
/// \return � ������ ������� ���������� ������������� ��������
///
typedef gint (MSCU_CALL_PREFIX * Tplug_file_create)(PPluginProtoStuff stuff, gint flags, void ** fhandle);

/// ������ ������ � ����
/// ���������� ������ ������ � ���� �� ������������ �������
///
/// \param in stuff - ��������, ������������ ��� ������ ������� \ref Tplug_register, � ������������ ������� �������� ������
/// \param in fhandle - ���������� ���������� ����� (��������� � ������� \ref Tplug_callback_file_create)
/// \param in buf - ����� ��� ������
/// \param in len - ����� ������ ��� ������ � ������
/// \param in offset - ��������� ������� ������, �������� � ������ �� ������ ����� (�������� -1 ���������� ������� �������)
///
/// \return � ������ ������ ���������� 0
/// \return � ������ ������� ���������� ������������� ��������
///
typedef gint (MSCU_CALL_PREFIX * Tplug_file_write)(PPluginProtoStuff stuff, void * fhandle, void * buf, gsize_t len, gint64 offset);

/// ������ ������ �� �����
/// ���������� ������ ������ �� ����� �� ������������ �������
///
/// \param in stuff - ��������, ������������ ��� ������ ������� \ref Tplug_register, � ������������ ������� �������� ������
/// \param in fhandle - ���������� ���������� ����� (��������� � ������� \ref Tplug_callback_file_create)
/// \param in buf - ����� ��� ������
/// \param in len - ����� ������ ��� ������ � ������
/// \param in offset - ��������� ������� ������, �������� � ������ �� ������ ����� (�������� -1 ���������� ������� �������)
///
/// \return � ������ ������ ���������� 0
/// \return � ������ ������� ���������� ������������� ��������
///
typedef gint (MSCU_CALL_PREFIX * Tplug_file_read)(PPluginProtoStuff stuff, void * fhandle, void * buf, gsize_t len, gint64 offset);

/// �������� �����
/// ����������� ���������� � ������� ����
///
/// \param in stuff - ��������, ������������ ��� ������ ������� \ref Tplug_register, � ������������ ������� �������� ������
/// \param in fhandle - ���������� ���������� ����� (��������� � ������� \ref Tplug_callback_file_create)
///
/// \return � ������ ������ ���������� 0
/// \return � ������ ������� ���������� ������������� ��������
///
typedef gint (MSCU_CALL_PREFIX * Tplug_file_close)(PPluginProtoStuff stuff, void * fhandle);

/// \name ������� ������
///@{

/// ����� ��������� ��������� ������ � ������� ������ (area) ������ buf (������ len).
/// ���� ��������� ������, ������������ ��������� ��
/// ����������� ������ � ������ ���������� (������ � ������), � found_pos ��������� ������� ����������.
/// � ������ ������� ���������� nil.
///
/// \param buf - �����, � ������� ������������ �����
/// \param len - ������ ������ � ������
/// \param area - ������� ������ � ������
/// \param[out] found_pos - ������� ������ ����������
///
/// \return � ������ ������ ���������� ���������� (������ � ������), � found_pos ��������� ������� ���������� (������� � 0)
/// \return � ������ ������� ���������� 0 (nil/NULL)
///
typedef gconstpchar (MSCU_CALL_PREFIX * Tenum_file_find)(gconstpchar buf, guint len, guint area, guint * found_pos);

/// ���������� ����� ������������� �������� �� ������ TCP-�����
///
/// \param port - ����� �����
///
/// \return ���� port ������, ������������ ��������� �� ����������� ������ � ���������
/// \return � ������ ������� ���������� nil
///
typedef gconstpchar (MSCU_CALL_PREFIX * Tenum_service_tcp_find)(guint32 port);

/// ���������� ����� ������������� �������� �� ������ UDP-�����
///
/// \param port - ����� �����
///
/// \return ���� port ������, ������������ ��������� �� ����������� ������ � ���������
/// \return � ������ ������� ���������� nil
///
typedef gconstpchar (MSCU_CALL_PREFIX * Tenum_service_udp_find)(guint32 port);

/// ����� ���� ����� �� mime-���� (�������� content-type)
///
/// \param mime_type - �������� content-type � ��������� ���� � ����������� �����
///
/// \return � ������ ������ ���������� ���������� (������ � ������)
/// \return � ������ ������� ���������� 0 (nil/NULL)
///
typedef gconstpchar (MSCU_CALL_PREFIX * Tenum_mime_find)(gconstpchar mime_type);

/// ���������� ����� ���������� �������� �� IP-������
///
/// \param ip - IP-����� � �������� �������
///
/// \return ���� IP ������, ������������ ��������� �� ����������� ������ � ���������
/// \return � ������ ������� ���������� nil
///
typedef gconstpchar (MSCU_CALL_PREFIX * Tenum_ip_find)(guint32 ip);

/// ���������� ����� ���������� �������� ����������� �� OUI
///
/// \param oui - ��������� �� 3 �����, ������������ OUI
///
/// \return ���� OUI ������, ������������ ��������� �� ����������� ������ � ������ �����������
/// \return � ������ ������� ���������� nil
///
typedef gconstpchar (MSCU_CALL_PREFIX * Tenum_oui_find)(gconstpointer oui);

/// ���������� ����� ���������� �������� �� PID
///
/// \param pid - ����� PID
///
/// \return ���� PID ������, ������������ ��������� �� ����������� ������ � ���������
/// \return � ������ ������� ���������� nil
///
typedef gconstpchar (MSCU_CALL_PREFIX * Tenum_pid_find)(guint32 pid);

/// @}

// ��������� value_string-������� "wtap_encap" (��� ���������)
typedef value_string* (MSCU_CALL_PREFIX* Twtap_encap_get_vals)();

typedef guint (MSCU_CALL_PREFIX* Twtap_encap_register)(gconstpchar name, gconstpchar filter_name);

// ��������� ���� (��� ���������)
// ���������� ������� �������� � ������������ ������������
// ������� ������ ������������ ��� network WTAP_ENCAP_XXX-��������, ������������ � ����� "wtap_encap.h"
// ����������� ���������� ������ ���� ��������������� � ������� "wtap_encap" � ��������������� ��������� (network)
typedef void (MSCU_CALL_PREFIX * Tplug_proto_set_network)(PPluginProtoStuff stuff, gint32 network);

// ����������� ����������� ����� (��� ���������)
// ������� � ������� ������� crop �������� ����� ����, �������� ����� (������) � ������������ �� � ������� ������ �������
typedef void (MSCU_CALL_PREFIX * Tplug_proto_ack_frame)(PPluginProtoStuff stuff, tvbuff_t* tvb, PPacketInfo pi);

/// ���������� ���������� ������ �������
/// ������ ������� �������� ����������. ����������� Tplug_proto_add_filter_2 ������ ���.
///
/// \param in stuff - ��������, ������������ ��� ������ ������� \ref Tplug_register, � ������������ ������� �������� ������
/// \param in filter - ���������, ���������� ����� ������� (��. ��������������� �������� � ffsrm.h)
///
typedef void (MSCU_CALL_PREFIX * Tplug_proto_add_filter)(PPluginProtoStuff stuff, S10G_FILTER_ITEM_STRUCT* filter_item);

/// ���������� �������� ����� ������������ �������
/// ������ ������� �������� ����������. ����������� Tplug_proto_sub_filter_2 ������ ���.
///
/// \param in stuff - ��������, ������������ ��� ������ ������� \ref Tplug_register, � ������������ ������� �������� ������
/// \param in filter - ���������, ���������� ����� ������� (��. ��������������� �������� � ffsrm.h)
///
typedef void (MSCU_CALL_PREFIX * Tplug_proto_sub_filter)(PPluginProtoStuff stuff, S10G_FILTER_ITEM_STRUCT* filter_item);

/// ���������� ���������� ������ �������
///
/// \param in stuff - ��������, ������������ ��� ������ ������� \ref Tplug_register, � ������������ ������� �������� ������
/// \param in filter - ���������, ���������� ����� ������� (��. ��������������� �������� � ffsrm.h)
///
typedef void (MSCU_CALL_PREFIX * Tplug_proto_add_filter_2)(PPluginProtoStuff stuff, S10G_FILTER_ITEM_STRUCT_2 * filter_item);

/// ���������� �������� ����� ������������ �������
///
/// \param in stuff - ��������, ������������ ��� ������ ������� \ref Tplug_register, � ������������ ������� �������� ������
/// \param in filter - ���������, ���������� ����� ������� (��. ��������������� �������� � ffsrm.h)
///
typedef void (MSCU_CALL_PREFIX * Tplug_proto_sub_filter_2)(PPluginProtoStuff stuff, S10G_FILTER_ITEM_STRUCT_2 * filter_item);

/// 2016-11-24
/// ���������� ���������� �������� � ���������� ������.
/// ���������� ���� token_is_indirect ������������ ��� ���������� �������� ��������������� (����� ������������ ������� ���������� ���������� ���������� ����� ����������).
/// ����������� ���� token_is_indirect ������������ ��� ���������� �������� �������� (����� ������������ ������� ������ ���� �������� � �������� ��������� ����������).
///
/// \param in stuff - ��������, ������������ ��� ������ ������� \ref Tplug_register, � ������������ ������� �������� ������
/// \param in token_buf - ����� � ������� ��������
/// \param in token_len - ����� ������ � ������� ��������
/// \param in token_spot - �������� ������ \ref teri_bis.h
/// \param in token_is_indirect - ��� ��������: 0 - �� ��������� (��������� token->prio ���������� �������� ������� ���� �� ����� 2), !0 - ��������� (��������� token->prio ���������� �������� ������� ���� ����� 2, ����� ������� �� ����� � ���������� ��������� ����������� ������)
/// \param in uins - ������ �������� UIN, � ������� ��������� ����������� �������
/// \param in uins_count - ���������� ��������� � ������� uins
///
typedef void (MSCU_CALL_PREFIX * Tplug_proto_srm_set_secondary_token)(PPluginProtoStuff stuff, gconstpointer token_buf, guint token_len, guint token_spot, gboolean token_is_indirect, guint32 * uins, guint32 uins_count);

/// 2016-11-24
/// ���������� ���������� �������� � ���������� ������.
///
/// \param in stuff - ��������, ������������ ��� ������ ������� \ref Tplug_register, � ������������ ������� �������� ������
/// \param in filter_item - ���������, ���������� ip-������ (1 ��� 2)
/// \param in tv - TimeStamp
/// \param in unis - ������ �������� UNI, � ������� ��������� ����������� �������
/// \param in unis_count - ���������� ��������� � ������� uins
///
typedef void (MSCU_CALL_PREFIX * Tplug_proto_srm_set_secondary_token2)(PPluginProtoStuff stuff, S10G_FILTER_ITEM_STRUCT_2 * filter_item, Ttimeval* tv, guint32* unis, gsize_t unis_count);

/* ���������, ���������� ������ ����������� ������� */
STRUCT_PACKED_BEGIN // ������������� ������������ �������� � 1 ����
struct STRUCT_PACKED_ATTRIBUTE TSWINEStandartFunctions {
  // ������ ���������.
  // ������ �������� ����������� � ��������, ���� ������ ��������� � ��� �� ������, ��� � ����������.
  // �������� ������ �������������� ������� ������� swine_plugin_init ������ ����� ���:
  //   assert(sizeof(TSWINEStandartFunctions) <= SWINEStuff->cbSize);
  guint32 cbSize;

  // ����� �����������
  Tplug_proto_find_stuff_by_dissector plug_proto_find_stuff_by_dissector;
  // ��������� ����� �������� ������ �����������
  Tset_swine_current_module_name set_swine_current_module_name;
  /* ������������ ���������� */
  Tplug_proto_register_protocol                 plug_proto_register_protocol;
  Tplug_proto_register_protocol_always_enabled  plug_proto_register_protocol_always_enabled; // 2010-02-17

  Tplug_proto_register_protocol_wud                 plug_proto_register_protocol_wud; // 2010-02-17
  Tplug_proto_register_protocol_wud_always_enabled  plug_proto_register_protocol_wud_always_enabled; // 2010-02-17

  Tplug_prefs_register_protocol                 plug_prefs_register_protocol;
  Tplug_prefs_register_protocol_always_enabled  plug_prefs_register_protocol_always_enabled; // 2010-02-17
  /* ������ � ������� ���������� � ������ */
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
  /* ������ � ������� ������� */
  Tplug_tree_add plug_tree_add;
  /* ������ � value_string */
  Tplug_val_to_str plug_val_to_str; // !!����� ������ (���� � swine_utils.h/cpp)
  /* ����� ������� ��������� */
  Tplug_proto_add_log                 plug_proto_add_log;
  /* ������� ��������� */
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
  /* �������, ������������ � Create */
  Tplug_proto_register_dissector            plug_proto_register_dissector;
  Tplug_proto_register_dissector_table      plug_proto_register_dissector_table;
  Tplug_proto_register_heur_dissector_list  plug_proto_register_heur_dissector_list;
  Tplug_proto_register_field_info           plug_proto_register_field_info;
  /* �������, ������������ � Bind */
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

  // ���������: 2009-07-31
  // ������ ��� ���������
  /* ������������ ��������� */
  Tplug_deco_register_decoder plug_deco_register_decoder;
  Tplug_prefs_register_decoder plug_prefs_register_decoder;

  Twtap_encap_get_vals wtap_encap_get_vals;
  Twtap_encap_register wtap_encap_register;

  // ��������� ����
  Tplug_proto_set_network plug_proto_set_network;
  // ����������� ����������� �����
  Tplug_proto_ack_frame plug_proto_ack_frame;

  // ���������� ������� - ��������� 2011-05-11
  Tplug_proto_add_filter plug_proto_add_filter; /// ������ ������� �������� ����������. ����������� Tplug_proto_add_filter_2 ������ ���.
  // �������� ������� - ��������� 2011-05-11
  Tplug_proto_sub_filter plug_proto_sub_filter; /// ������ ������� �������� ����������. ����������� Tplug_proto_sub_filter_2 ������ ���.

  // ������ ����� - ��������� 2012-05-02
  Tplug_file_read                       plug_file_read;

  // ��������� 2014-06-27
  Tplug_proto_ack_ex_svc                              plug_proto_ack_ex_svc;
  Tplug_proto_forward_packet_and_ack_ex_svc           plug_proto_forward_packet_and_ack_ex_svc;
  Tplug_proto_dissector_try_port_and_ack_ex_svc       plug_proto_dissector_try_port_and_ack_ex_svc;
  Tplug_proto_dissector_try_heuristic_and_ack_ex_svc  plug_proto_dissector_try_heuristic_and_ack_ex_svc;

	// ��������� 2016-04-10
	Tplug_proto_srm_teri_match plug_proto_srm_teri_match;

	// ��������� 2016-05-11
  Tpacket_info_set_id_token_path      packet_info_set_id_token_path;
  Tpacket_info_set_id_token_entry     packet_info_set_id_token_entry;

  // ���������� ������� - ��������� 2016-10-23
  Tplug_proto_add_filter_2 plug_proto_add_filter_2;
  // �������� ������� - ��������� 2016-10-23
  Tplug_proto_sub_filter_2 plug_proto_sub_filter_2;

	// 2016-11-13
	// ������������ ��������� ������
  Tpacket_info_tokens_clone               packet_info_tokens_clone;

	/// 2016-11-24
  Tplug_proto_srm_set_secondary_token		plug_proto_srm_set_secondary_token;
  Tplug_proto_srm_set_secondary_token2	plug_proto_srm_set_secondary_token2;

	// ��������� 2017-06-02
	Tplug_proto_complex_teri_match plug_proto_complex_teri_match;
	Tplug_proto_ack_raw						 plug_proto_ack_raw;
	// ��������� 2017-06-13
	Tplug_proto_complex_teri_match_retro plug_proto_complex_teri_match_retro;
};
STRUCT_PACKED_END // ��������������� ������������ �������� �� ���������
typedef TSWINEStandartFunctions * PSWINEStandartFunctions;

/* ��� �������������� ������� �������
 * �������� ������� � ������� �������� DLL - swine_plugin_init (naked - ��� ���������)
 * ������� ���������� �������, ��� �������� ����������
 * ���������:
 *   SWINEStuff: ����� �� ���������, ���������� ������ ����������� ������� SWINE
 *   adescription: �������� �������, ������ - SWINE_STR_SIZE, ����������� ��������
 *   aversion: ������ ������� � ������� "n.n.n" ��� "n.n", ������ - SWINE_STR_SIZE, ����������� ��������
 * ������ �������:
 *   - ��������� adescription � aversion ���������������� ����������
 *   - ��������� �� ���������� ���������� ����� ��������� ����������� ������� (���� ��������� �������������
 *     ������ ���� � �������� ��� ����� ����� SWINE)
 *   - ���������������� ������ ��������� � ����������, ������������� � �������, � ����� ��������� � ���
 *     (�������: plug_proto_register_protocol, plug_prefs_register_protocol,
 *      plug_prefs_register_uint_preference, plug_prefs_register_uint_hidden_preference
 *      plug_prefs_register_bool_preference, plug_prefs_register_bool_hidden_preference)
 */
typedef void (MSCU_CALL_PREFIX * TPluginInit)(PSWINEStandartFunctions SWINEStuff, gpchar adescription, gpchar aversion);

#endif