/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
///
///
/// ffsrm.h : Fielgat's headers.
///
/// Changelog:
/// [+] 2017-01-12 - ���������: S10G_FILTER_ITEM_STRUCT_2_PACKED, S10G_ADD_FILTER_2_PACKED;
/// [+] 2016-10-22 - ���������: S10G_ADD_FILTER_2, S10G_UPDATE_FILTERS_2, S10G_FILTER_ITEM_STRUCT_2 (� ���������� IPv6);
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

//��������� ���� ������� (��� ����, � �������� ����� ���� �� ���):
// enum
// {
//      TRAIN_ENCAP_SRM_UNI     = 0x9a, //SRM UNI packet - ��� ������ � ����� ���������� LID, ��� ������ �� ��������� IP �������, MAC ������, ������ VLAN.
//              //IP ����� ����� ���� ��� � "��������" IP ������, ��� � ���������������� �� VLAN, Q-in-Q, MPLS, VLAN-MPLS, Q-in-Q - VLAN - MPLS
//      TRAIN_ENCAP_SRM_MAIL    = 0x9b, //����� TCP ���� 25/110/119/143 (E-Mail)
//      TRAIN_ENCAP_SRM_FTP     = 0x9c, //����� TCP ���� 20/21 (FTP)
//      TRAIN_ENCAP_SRM_TCPVOIP = 0x9d, //����� TCP ���� 1720 (VoIP)
//      TRAIN_ENCAP_SRM_UDPVOIP = 0x9e, //����� UDP ���� 5060 (VoIP)
//      TRAIN_ENCAP_SRM_ICQ     = 0x9f, //����� TCP ���� 5190 (ICQ)
//      TRAIN_ENCAP_SRM_WMSG    = 0xa0, //����� TCP ���� 3235/1863 (W-MSG)
//      TRAIN_ENCAP_SRM_MRAGENT = 0xa1, //����� TCP ���� 2041/2042 (MailruAgent)
//      TRAIN_ENCAP_SRM_GGLTALK = 0xa2, //����� TCP ���� 443 (GoogleTalk)
//      TRAIN_ENCAP_SRM_RADIUS  = 0xa3, //����� UDP ���� 1812/1813/1645/1646 (RADIUS)
//      TRAIN_ENCAP_SRM_TACACS  = 0xa4, //����� TCP ���� 49 / ����� UDP ���� 49 (TACACS)
//      TRAIN_ENCAP_SRM_DIAMETR = 0xa5, //����� TCP ���� 3868 (DIAMETR)
//      TRAIN_ENCAP_SRM_UDP     = 0xa6, //����� UDP
// //   TRAIN_ENCAP_SRM_UNI_    = 0xa7, //����� ������� �������� ��� ����, ����� ���������� LID - ������ ���� ������ 0x9a
//      TRAIN_ENCAP_SRM_RESERV  = 0xa8, //������
//      TRAIN_ENCAP_SRM_NOIP    = 0xa9, //PPPoE (0x8863, 0x8864) & broadcasts (MAC2 = ff:ff:ff:ff:ff:ff)
//      TRAIN_ENCAP_SRM_UNKNOWN = 0xaa, //����� ������������� ����
// }

//��������������� ��������� ��� ����� �� ���� �� ���������:
//��������� �������
enum {
        S10G_ADD_FILTER				= 0x09081818,   //�������� ������ (S10G_FILTER_ITEM_STRUCT)
        S10G_UPDATE_FILTERS		= 0x09081819,   //�������� ������ �������� ��������
                                      // ������ ����� � ������ ���������� �������� ��������� S10G_UPDATE_FILTERS_HEADER_STRUCT
                                      // � ������������ ���������� ������� ���� S10G_FILTER_ITEM_STRUCT
                                      // �������� ��������:
                                      //  ������ ������ �������� �� ����� ���������� � ����� ������ � ���������� S10G_UPDATE_FILTERS (��� UDP-�������)
                                      //  ������� ������ ������ ����������� �� ����� � ���������� ������� �������
                                      //  � ������ �������: �������� ���� sequence ������� ������ ����� 0
                                      //  � ������ �������: �������� ���� count ���������� ������ ����� 0
                                      //  � ������ �������: �������� ���� sequence ���������� ������ ����� �������� (count+sequence) ����������� ������
        S10G_RES_FILTER				= 0x0908181a,   //������������ �� �������� ����� �� ��������� �������

        S10G_GET_PARAMS				= 0x0908181b,   //�������� ��������� �� �������� - ������� ���������� �� �������
        S10G_REQ_PARAMS				= 0x0908181c,   //�������� ��������� �� �������� - ������������ ������ �� ��������
        S10G_SET_FILTER_PARAM = 0x10051418,	// �������� ��������� ��������� ���������� �� �������
        S10G_ADD_FILTER_2     = 0x0908181d,	//�������� ������ (S10G_FILTER_ITEM_STRUCT_2)
        S10G_UPDATE_FILTERS_2 = 0x0908181e, // �������� ������ �������� ��������
																						// ������ ����� � ������ ���������� �������� ��������� S10G_UPDATE_FILTERS_HEADER_STRUCT
																						// � ������������ ���������� ������� ���� S10G_FILTER_ITEM_STRUCT_2_PACKED
																						// �������� ��������:	��. S10G_UPDATE_FILTERS
																						// ������ ��������� ����������� � ���, ��� ���������� ����������
																						// ������ �� ����, ������� ����� ��������. ��� ���� ������������ ������������ �� 4 ����.
																						// ���� proto � flags ���������� ������. ��������� ���� ���������� � ����������� �� �������� ���� proto:
																						//	 �������� proto										|	  ������������ ����
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
        S10G_ADD_FILTER_2_PACKED = 0x0908181f,	//�������� ������ - ����������� ������� (S10G_FILTER_ITEM_STRUCT_2_PACKED)
};

//�������� �������
// ���� ������������ ���� ����� 0, ������ ���� �� ��������� � ���������� (����� ��������)
// �������� ����� ��������, � ����� ����������� ������� �����, ��������:
//  - ip1,port1,ip2,port2
//  - ip1,port1,ip2 (� ���� ������ port2 ���������� ��� �������)
//  - ip1,ip2 (� ���� ������ port1, port2 ���������� ��� �������)
//  - ip1,port1 (� ���� ������ ip2, port2 ���������� ��� �������)
//  - ip1 (� ���� ������ port1, ip2, port2 ���������� ��� �������)
// ������� ������ ������������ ��� ����������� ��������, ��������:
//   ip1,ip2 - �������� ������ ip_src==ip1,ip_dst==ip2 � ip_src==ip2,ip_dst==ip1
STRUCT_PACKED_BEGIN // ������������� ������������ �������� � 1 ����
typedef struct STRUCT_PACKED_ATTRIBUTE {
#define S10G_FILTER_PROTO_AAA 0x00
#define S10G_FILTER_PROTO_TCP 0x01
#define S10G_FILTER_PROTO_UDP 0x02
#define S10G_FILTER_PROTO_TCP_IGNORE_SESSION 0x03 // 2013-07-04 HTTP-request functionality
#define S10G_FILTER_PROTO_UDP_IGNORE_SESSION 0x04 // 2014-03-11 HTTP-request functionality

  guint32 proto; //�������� (��� ������������ ������)

  guint32 ip1;   //IP-����� � ������� �������
  guint32 ip2;   //IP-����� � ������� �������
  guint16 port1; //TCP/UDP-���� � ������� �������
  guint16 port2; //TCP/UDP-���� � ������� �������
} S10G_FILTER_ITEM_STRUCT; //�������� �������
STRUCT_PACKED_END // ��������������� ������������ �������� �� ���������

// added 2016-10-22

STRUCT_PACKED_BEGIN // ������������� ������������ �������� � 1 ����
typedef struct STRUCT_PACKED_ATTRIBUTE {
	union {
		guint8    bytes[4];
		guint16   words[2];
		guint32   qword;
	}; // IP-����� � ������� �������
} S10G_IPv4;
STRUCT_PACKED_END // ��������������� ������������ �������� �� ���������

STRUCT_PACKED_BEGIN // ������������� ������������ �������� � 1 ����
typedef struct STRUCT_PACKED_ATTRIBUTE {
	union {
		guint8    bytes[16];
		guint16   words[8];
		guint32  qwords[4];
	}; // IP-����� � ������� �������
} S10G_IPv6;
STRUCT_PACKED_END // ��������������� ������������ �������� �� ���������

// �������� �������
// �� ����� ��������� ���� �� ��������� 0, ��� ����� ������������ ���������� ��������	���� proto
// �������� ����� ��������, � ����� ����������� ������� �����, ��������:
//  - ip1,port1,ip2,port2
//  - ip1,port1,ip2 (� ���� ������ port2 ���������� ��� �������)
//  - ip1,ip2 (� ���� ������ port1, port2 ���������� ��� �������)
//  - ip1,port1 (� ���� ������ ip2, port2 ���������� ��� �������)
//  - ip1 (� ���� ������ port1, ip2, port2 ���������� ��� �������)
// ������� ������ ������������ ��� ����������� ��������, ��������:
//   ip1,ip2 - �������� ������ ip_src==ip1,ip_dst==ip2 � ip_src==ip2,ip_dst==ip1
STRUCT_PACKED_BEGIN // ������������� ������������ �������� � 1 ����
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
	guint16 proto; // ���������� - S10G_FILTER_PROTO_XXX (������� ������� ����)
#define S10G_FILTER_FLAG_IGNORE 0x0001
	guint16 flags; // ����� - ���������� S10G_FILTER_FLAG_XXX (������� ������� ����)
	union	{
		struct STRUCT_PACKED_ATTRIBUTE {
			S10G_IPv4 ip1; // IP-����� � ������� �������
			S10G_IPv4 ip2; // IP-����� � ������� �������
		} ip4;
		struct STRUCT_PACKED_ATTRIBUTE {
			S10G_IPv6 ip1; // IP-����� � ������� �������
			S10G_IPv6 ip2; // IP-����� � ������� �������
		} ip6;
	};
	guint16 port1; // TCP/UDP-���� � ������� �������
	guint16 port2; // TCP/UDP-���� � ������� �������
} S10G_FILTER_ITEM_STRUCT_2; //�������� �������
STRUCT_PACKED_END // ��������������� ������������ �������� �� ���������

// added 2017-01-12

// �������� ������� - ����������� ���
// ����������� ����� ��������� ������� �� �������� ���� proto (�.�. �� ��� �����, ������� ����� ��������).
// ��� ���� ������������ ������������ �� 4 ����.
// ���� proto � flags ���������� ������. ��������� ���� ���������� � ����������� �� �������� ���� proto:
//	 �������� proto										|		������������ ����							|	������ ��������� (����)
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
STRUCT_PACKED_BEGIN // ������������� ������������ �������� � 1 ����
typedef struct STRUCT_PACKED_ATTRIBUTE {
	guint16 proto; // ���������� - S10G_FILTER_PROTO_XXX (������� ������� ����)
	guint16 flags; // ����� - ���������� S10G_FILTER_FLAG_XXX (������� ������� ����)
	union {
// S10G_FILTER_PROTO_4_IP							| ip4.ip1													|				 8
		struct STRUCT_PACKED_ATTRIBUTE {
			S10G_IPv4 ip1; // IP-����� � ������� �������
		} ip4;
// S10G_FILTER_PROTO_4_IP_IP					| ip4.ip1 ip4.ip2									|				12
		struct STRUCT_PACKED_ATTRIBUTE {
			S10G_IPv4 ip1; // IP-����� � ������� �������
			S10G_IPv4 ip2; // IP-����� � ������� �������
		} ip4_ip4;
// S10G_FILTER_PROTO_4_IP_TCP					| ip4.ip1 port1 2_byte_alignment	|				12
// S10G_FILTER_PROTO_4_IP_UDP					| ip4.ip1 port1 2_byte_alignment	|				12
		struct STRUCT_PACKED_ATTRIBUTE {
			S10G_IPv4 ip1; // IP-����� � ������� �������
			guint16 port1; // TCP/UDP-���� � ������� �������
			guint16 stub; // reserved - fill to 4 byte boundary
		} ip4_port;
// S10G_FILTER_PROTO_4_IP_TCP_IP_TCP	| ip4.ip1 ip4.ip2 port1 port2			|				16
// S10G_FILTER_PROTO_4_IP_UDP_IP_UDP	| ip4.ip1 ip4.ip2	port1	port2			|				16
		struct STRUCT_PACKED_ATTRIBUTE {
			S10G_IPv4 ip1; // IP-����� � ������� �������
			S10G_IPv4 ip2; // IP-����� � ������� �������
			guint16 port1; // TCP/UDP-���� � ������� �������
			guint16 port2; // TCP/UDP-���� � ������� �������
		} ip4_ip4_port_port;
// S10G_FILTER_PROTO_6_IP							| ip6.ip1													|				20
		struct STRUCT_PACKED_ATTRIBUTE {
			S10G_IPv6 ip1; // IP-����� � ������� �������
		} ip6;
// S10G_FILTER_PROTO_6_IP_IP					| ip6.ip1 ip6.ip2									|				36
		struct STRUCT_PACKED_ATTRIBUTE {
			S10G_IPv6 ip1; // IP-����� � ������� �������
			S10G_IPv6 ip2; // IP-����� � ������� �������
		} ip6_ip6;
// S10G_FILTER_PROTO_6_IP_TCP					| ip6.ip1 port1 2_byte_alignment	|				24
// S10G_FILTER_PROTO_6_IP_UDP					| ip6.ip1 port2 2_byte_alignment	|				24
		struct STRUCT_PACKED_ATTRIBUTE {
			S10G_IPv6 ip1; // IP-����� � ������� �������
			guint16 port1; // TCP/UDP-���� � ������� �������
			guint16 stub; // reserved - fill to 4 byte boundary
		} ip6_port;
// S10G_FILTER_PROTO_6_IP_TCP_IP_TCP	| ip6.ip1 ip6.ip2 port1	port2			|				40
// S10G_FILTER_PROTO_6_IP_UDP_IP_UDP	| ip6.ip1 ip6.ip2 port1	port2			|				40
		struct STRUCT_PACKED_ATTRIBUTE {
			S10G_IPv6 ip1; // IP-����� � ������� �������
			S10G_IPv6 ip2; // IP-����� � ������� �������
			guint16 port1; // TCP/UDP-���� � ������� �������
			guint16 port2; // TCP/UDP-���� � ������� �������
		} ip6_ip6_port_port;
	};
} S10G_FILTER_ITEM_STRUCT_2_PACKED; //�������� ������� - ����������� ���������
STRUCT_PACKED_END // ��������������� ������������ �������� �� ���������

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

//��������� ������, ��������� �� ���������� S10G_UPDATE_FILTERS/S10G_UPDATE_FILTERS_2
STRUCT_PACKED_BEGIN // ������������� ������������ �������� � 1 ����
typedef struct STRUCT_PACKED_ATTRIBUTE {
  guint32 sequence; // 0 - ������ �������� ������ �������, ���������� ������ ������ ������; �����, ���������� count == 0, ������� ��������� � ������
  guint32 count; // ���������� ��������� (���������� ������) � �������, ��������� �� ������ ���������� � ����������� ������,
								 // ��� �������� - S10G_FILTER_ITEM_STRUCT (S10G_UPDATE_FILTERS),  S10G_FILTER_ITEM_STRUCT_2 (S10G_UPDATE_FILTERS_2)
}	S10G_UPDATE_FILTERS_HEADER_STRUCT; //�������� ������ �������� TCP/IP(UDP/IP)-������
STRUCT_PACKED_END // ��������������� ������������ �������� �� ���������

STRUCT_PACKED_BEGIN // ������������� ������������ �������� � 1 ����
typedef struct STRUCT_PACKED_ATTRIBUTE {
	guint32 data;  //data - ����� ���� ����� ��:
#define S10G_FILTER_SUB_OK 0x0908181f
#define S10G_FILTER_ADD_OK 0x09081820
#define S10G_FILTER_TOOMANYFILTERS 0x09081821   //������ - ������� ����� �������� �����������, ��������� �� ���������
#define S10G_NEED_PARAMS  0x09081822    //������� ������� ������
} S10G_RES_FILTER_STRUCT, S10G_GET_PARAMS_STRUCT; //����� �������� ��� �������� ������� �� �������
STRUCT_PACKED_END // ��������������� ������������ �������� �� ���������

STRUCT_PACKED_BEGIN // ������������� ������������ �������� � 1 ����
typedef struct STRUCT_PACKED_ATTRIBUTE {
	unsigned char t1;       //�����������_����������_1 ������
	unsigned char t2;       //�����������_����������_2 ������
	unsigned char tb;       //�����������_����������_����� ������
	unsigned char s1;       //��������_��������_�����������_1 ��/���
	unsigned char s2;       //��������_��������_�����������_2 ��/���
	unsigned char s3;       //��������_��������_�����������_3 ��/���
	unsigned char s4;       //��������_��������_�����������_4 ��/���
	unsigned char s5;       //��������_��������_�����������_5 ��/���
	unsigned char tx;       //�����������������_�������_����������� 1 ��� 0
	unsigned char rx;       //�����������������_�������_����������� 1 ��� 0
	unsigned char rx1;      //�����_����������_����������_�����_����������_�����_�_�������� ����/���
	unsigned char rx2;      //�����_����������_����������_��_��������������_���� ����/���
} S10G_REQ_PARAMS_STRUCT; //������������ ��������� ������ �� ��������
STRUCT_PACKED_END // ��������������� ������������ �������� �� ���������

STRUCT_PACKED_BEGIN // ������������� ������������ �������� � 1 ����
typedef struct STRUCT_PACKED_ATTRIBUTE {
  guint32 update_period; // ������ ������� ��������� ���� S10G_UPDATE_FILTERS (S10G_UPDATE_HASH)
                                  // �������� � �������������
}	S10G_SET_FILTER_PARAM_STRUCT; //��������� ������� �������� ����������
STRUCT_PACKED_END // ��������������� ������������ �������� �� ���������

STRUCT_PACKED_BEGIN // ������������� ������������ �������� � 1 ����
typedef struct STRUCT_PACKED_ATTRIBUTE {
	guint32 signature;
	union	{																						// ���������								| ���������
		S10G_FILTER_ITEM_STRUCT add;										// S10G_ADD_FILTER					| �������� ������
		S10G_FILTER_ITEM_STRUCT_2 add_2;								// S10G_ADD_FILTER_2				| �������� ������
		S10G_FILTER_ITEM_STRUCT_2_PACKED add_2_packed;	// S10G_ADD_FILTER_2_PACKED	| �������� ������ - ����������� �������
		S10G_UPDATE_FILTERS_HEADER_STRUCT upd;					// S10G_UPDATE_FILTERS			| �������� ������ �������� ��������
																										// S10G_UPDATE_FILTERS_2		| �������� ������ �������� ��������
		S10G_RES_FILTER_STRUCT res;											// S10G_RES_FILTER					| ������������ �� �������� ����� �� ��������� �������
		S10G_GET_PARAMS_STRUCT get;											// S10G_GET_PARAMS					| �������� ��������� �� �������� - ������� ���������� �� �������
		S10G_REQ_PARAMS_STRUCT req;											// S10G_REQ_PARAMS					| �������� ��������� �� �������� - ������������ ������ �� ��������
		S10G_SET_FILTER_PARAM_STRUCT set;								// S10G_SET_FILTER_PARAM		| �������� ��������� ���������� �� �������
	};
}	S10G_NETWORK_PROTOCOL;
STRUCT_PACKED_END // ��������������� ������������ �������� �� ���������

//������� ��������� UDP ������ � ����� ���������� � �������� �� �� ���-�� �����, ������ ������ �����
//���� ����� - ���� �������
//���� ������ ������ ������������ (������ ��� 16 ���� � 8 ����) ��� ���������-������� ��������������� - �� �� ������ ������
//��� ����� ����� ����

#endif
