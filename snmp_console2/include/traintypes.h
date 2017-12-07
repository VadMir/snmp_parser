/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/*
 * This header file is written UNDER "cenzor" project.
 * Inner changes're APPLIED under this project ONLY.
 * DON'T MAKE ANY CHANGES to this file.
 * Use this header via #include in your project.
 */
/*
 * last update: 2011-02-10
 *
 * traintypes.h : train encap type values.
 *
 * changelog
 * ---------
 * 2011-02-10 - added: TRAIN_ENCAP_OSI_T (see description below)
 * 2011-02-10 - added: TRAIN_ENCAP_CDP_T (see description below)
 * 2011-02-10 - added: TRAIN_ENCAP_IP_T (see description below)
 * 2010-06-09 - added: TRAIN_ENCAP_OSI (see description below)
 * 2009-03-25 - added: TRAIN_ENCAP_SRM_UNI (see description below)
 * 2009-03-25 - added: TRAIN_ENCAP_SRM_RAW (see description below)
 *
 * Copyright (C) MSC, ORG 2006-2009
 */

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#ifndef TRAINTYPES_H
#define TRAINTYPES_H

/* Train encapsulation types. This type value is located in the
 * lowest byte of Ext field, as shown in the type definition below:
 *
 *   union ext_type {
 *     guint16 ext; !it must be disabled due to LE/BE problems
 *     struct { guint8 encap; guint8 offset; };
 *   } ext_type;
 *
 * encap - encapsulation type value
 * offset - octet offset of the first IP-header octet within total packet buffer
 *
 * Due to the compatibility with external "Train-3" format, we place our "cenzor native"
 * type values in the upper half of 8-bit range, so, our values should never intersect
 * with "external native" band
 *
 * Note, that encap always stands for then whole packet buffer, even when packet contains IP (with legal offset value)
 *
 * For more information about Train format, see other documenation
 */

/* total amount of "cenzor-native" type values */
#define TRAIN_NUM_ENCAP_TYPES              51;

/* bounds of "cenzor-native" type values */
#define TRAIN_NUM_ENCAP_TYPES_BELOW        0x80;
#define TRAIN_NUM_ENCAP_TYPES_UPPER        0xb2;

/* here the are
 */

#define TRAIN_ENCAP_IP        0x45  /* Internet Protocol */

#define TRAIN_ENCAP_RAW       0x80  /* raw buffer (may contain IP-packet) with unknown data-link-type */

#define TRAIN_ENCAP_ETH       0x82  /* Ethernet */
#define TRAIN_ENCAP_PPP       0x83  /* Point-to-Point Protocol */
#define TRAIN_ENCAP_CHDLC     0x84  /* Cisco HDLC (Cisco SLE) */
#define TRAIN_ENCAP_DVB       0x85  /* DVB MPEG-TS 188 bytes packet */

#define TRAIN_ENCAP_CDP       0x86  /* Cisco Discovery Protocol */
#define TRAIN_ENCAP_ARP       0x87  /* ARP/SLARP/FRARP... */
#define TRAIN_ENCAP_OSI       0x88  /* OSI */

//!!! conflicted encaps
#define TRAIN_ENCAP_MPEG_PSI  0x89  /* DVB MPEG-PSI Program Specific Information */
#define TRAIN_ENCAP_TCP_SYN   0x89  /* TCP packets with SYN flags */

#define TRAIN_ENCAP_DVB_MPE    0x8a  /* DVB MPE Multi-Protocol Encapsulation */
#define TRAIN_ENCAP_IP_BIG_TTL 0x8a  /* IP packets with specific TTL and specific address color */

/* ^^^ really used encap vals  ^^^ */

#define TRAIN_ENCAP_TCP       0x8b  /* Transmition Control Protocol */
#define TRAIN_ENCAP_UDP       0x8c  /* User Data Packet */

#define TRAIN_ENCAP_ICMP      0x8d  /* Internet Control Messages Protocol */
#define TRAIN_ENCAP_ICMPv6    0x8e  /* Internet Control Messages Protocol v6 */
#define TRAIN_ENCAP_IGMP      0x8f  /* IGMP */
#define TRAIN_ENCAP_GGP       0x90  /* GGP */
#define TRAIN_ENCAP_EGP       0x91  /* EGP */
#define TRAIN_ENCAP_IGRP      0x92  /* IGRP */
#define TRAIN_ENCAP_EIGRP     0x93  /* EIGRP */
#define TRAIN_ENCAP_DGP       0x94  /* DGP */
#define TRAIN_ENCAP_OSPF      0x95  /* OSPF */
#define TRAIN_ENCAP_BGP       0x96  /* BGP */
#define TRAIN_ENCAP_RIP       0x97  /* RIP */

#define TRAIN_ENCAP_WLAN      0x98  /* IEEE 802.11 */

#define TRAIN_ENCAP_SRM_RAW   0x99  /* SRM RAW packet (must be detected) */
#define TRAIN_ENCAP_SRM_UNI   0x9a  /* SRM UNI packet - it was selected by token - LID keep UNI-value - Token's UNique Identificator */

#define TRAIN_ENCAP_SRM_MAIL    0x9b //Пакет TCP порт 25/110/119/143 (E-Mail)
#define TRAIN_ENCAP_SRM_FTP     0x9c //Пакет TCP порт 20/21 (FTP)
#define TRAIN_ENCAP_SRM_TCPVOIP 0x9d //Пакет TCP порт 1720 (VoIP)
#define TRAIN_ENCAP_SRM_UDPVOIP 0x9e //Пакет UDP порт 5060 (VoIP)
#define TRAIN_ENCAP_SRM_ICQ     0x9f //Пакет TCP порт 5190 (ICQ)
#define TRAIN_ENCAP_SRM_WMSG    0xa0 //Пакет TCP порт 3235/1863 (W-MSG)
#define TRAIN_ENCAP_SRM_MRAGENT 0xa1 //Пакет TCP порт 2041/2042 (MailruAgent)
#define TRAIN_ENCAP_SRM_GGLTALK 0xa2 //Пакет TCP порт 443 (GoogleTalk)
#define TRAIN_ENCAP_SRM_RADIUS  0xa3 //Пакет UDP порт 1812/1813/1645/1646 (RADIUS)
#define TRAIN_ENCAP_SRM_TACACS  0xa4 //Пакет TCP порт 49 / Пакет UDP порт 49 (TACACS)
#define TRAIN_ENCAP_SRM_DIAMETR 0xa5 //Пакет TCP порт 3868 (DIAMETR)
#define TRAIN_ENCAP_SRM_UDP     0xa6 //Пакет UDP
//#define TRAIN_ENCAP_SRM_UNI_    0xa7 //Пакет отобран фильтром <по типу>, имеет правильный LID - вместо него сейчас 0x9a
//#define TRAIN_ENCAP_SRM_RESERV  0xa8 //резерв
#define TRAIN_ENCAP_SRM_NOIP    0xa9 //PPPoE (0x8863, 0x8864) & broadcasts (MAC2 = ff:ff:ff:ff:ff:ff)
#define TRAIN_ENCAP_SRM_UNKNOWN 0xaa //Пакет неопознанного типа
#define TRAIN_ENCAP_SRM_HTTP_REQUEST  0xab //HTTP request

#define TRAIN_ENCAP_IP_T        0xb0  /* Internet Protocol with timestamp*/
#define TRAIN_ENCAP_CDP_T       0xb1  /* Cisco Discovery Protocol with timestamp*/
#define TRAIN_ENCAP_OSI_T       0xb2  /* OSI stack with timestamp*/

/* ^^^ these encap vals're not still used ^^^ */

#define TRAIN_ENCAP_VPN         0xc0 /* according to algorithm - hdv mod */
#define TRAIN_ENCAP_GTPC        0xc1 /* according to algorithm - hdv mod */
#define TRAIN_ENCAP_GTPU        0xc2 /* according to algorithm - hdv mod */
#define TRAIN_ENCAP_IRC         0xc3 /* according to algorithm - hdv mod */
#define TRAIN_ENCAP_DNS         0xc4 /* according to algorithm - hdv mod */
#define TRAIN_ENCAP_TDMoIP      0xc5 /* according to algorithm - hdv mod */
#define TRAIN_ENCAP_SCTP        0xc6 /* according to algorithm - hdv mod */
#define TRAIN_ENCAP_ISIS        0xc7 /* according to algorithm - hdv mod */
#define TRAIN_ENCAP_TCP_FIN     0xc8 /* according to algorithm - hdv mod */
#define TRAIN_ENCAP_HTTP        0xc9 /* according to algorithm - hdv mod */
#define TRAIN_ENCAP_DCPP        0xca /* according to algorithm - hdv mod */
#define TRAIN_ENCAP_BITTORRENT  0xcb /* according to algorithm - hdv mod */

/* this is "bad" offset value
 * other values (within buffer bounds) should point to the real IP-header
 */

#define TRAIN_OFFSET_NA     0xff  /* Unknown offset for IP-header in packet buffer */

//////////////////////////////////////////////////////////////////////////
/* generic values */

//#define TRAIN_ENCAP_GENERIC_IP    0x45  /* Internet Protocol */

#endif
