/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/*
 * ��������! ������ ���� ���������������� ��� ��������� ������ ������������ ������� �����.
 * ����� ��������� � ������ ����� ���������� �������������� �����������.
 * ��� ������������� ������� ����� ������ �������� ��� � ������ � ������� ��������� uses.
 */
/* teri_bis.h
 * ��������� ���������� teri_bis.dll
 */
/* teri_bis - Data Retrieval Engine, bis
 * Copyright (C) 2002-2017 MSC, ORG
 */
// ���������
// ---------
// [+] 2017-07-28 - ���������: ������ TERI_MODE_WARN_NO_PRIO, TERI_MODE_WARN_NO_PATH (��. ������������);
// [+] 2017-06-14 - ���������: ������� teri_bis_wrapper_tls_engine (��. ������������);
// [+] 2017-05-23 - ���������: ����� TERI_MODE_NO_VERIFICATION (��. ������������);
// [+] 2017-05-21 - ���������: ����� TERI_MODE_IGNORE_NO_ID (��. ������������);
// [+] 2017-05-11 - ���������: ����� TERI_UNI_EXT_XXX (��. ������������);
// [+] 2017-05-03 - ���������: ����� TERI_MODE_NO_SHIFT (��. ������������);
// [*] 2017-02-25 - ��������: �������� ������������� ������� ���������� (������ ������ ��� ������������� ������) (��. ������������ �� ������� teri_bis_wrapper_engine, teri_bis_wrapper_engine_enter, teri_bis_wrapper_engine_leave);
// [+] 2016-03-29 - ���������: ������� ������ - TERI_BIS_SPOT_NASp, TERI_BIS_SPOT_BSid;
// [+] 2016-03-14 - ���������: ���� entry_spot � ��������� Tteri_bis_match_token;
// [+] 2016-03-02 - ���������: ������� ������ - TERI_BIS_SPOT_URLad, TERI_BIS_SPOT_DNad, TERI_BIS_SPOT_ORIG, TERI_BIS_SPOT_REF, TERI_BIS_SPOT_fGET, TERI_BIS_SPOT_fPOST
// [+] 2014-04-14 ��������� ������� ������ - TERI_BIS_SPOT_DNad
// [+] 2014-04-14 ��������� ������� ������ - TERI_BIS_SPOT_URLad
// [+] 2015-07-22 - ���������: ������� teri_bis_wrapper_reload_if_modified_raw (��. ������������);
// [+] 2014-12-30 - ���������: ������� teri_bis_generate_wts (��. ������������);
// [+] 2014-12-30 - ���������: ������� teri_bis_wrapper_set_transparent_spots (��. ������������);
// [+] 2014-04-14 ��������� ������� ������ - TERI_BIS_SPOT_DN
// [+] 2013-12-15 ���������: ������� teri_bis_match_medium_atomic_first_only
// [+] 2013-11-01 ���������: ������� teri_bis_match_medium_atomic_all_bufs
// [+] 2013-10-21 ��������� ������� ������ - TERI_BIS_SPOT_PhB
// [+] 2012-11-28 - ���������: �������� ������� teri_bis_check_syntax;
// [+] 2012-11-08 - ���������: ������� ������ - TERI_BIS_SPOT_ISN (��. ������������);
// [+] 2011-11-18 - ���������: ���� ������ TERI_BIS_ERROR_BAD_TOKEN1_SPOT, TERI_BIS_ERROR_BAD_TOKEN2_SPOT  (��. ������������);
// [+] 2011-10-30 - ���������: ����� TERI_MODE_IGNORE_ID_DUPLICATION (��. ������������);
// [+] 2011-10-12 - ���������: ����� TERI_MODE_IGNORE_BAD_TOKENS (��. ������������)
// [+] 2011-03-09 ���������: ��������������
// [+] 2011-02-22 ��������� ������� ������ - TERI_BIS_SPOT_bMPLS
// [+] 2011-02-22 ��������� ���� id_ext � ���������� �������������� ������� (��. ������������) � !��������������� DTF-�������! !��������������� �� �������� ������ - ��������� Tteri_bis_match_token!
// [+] 2011-02-20 ���������: ������� teri_bis_wrapper_set_log_parameters
// [+] 2010-08-25 ��������� ���� sub_token_mask - ����� ������������ (��. ������������) � !��������������� DTF-�������!
// [+] 2010-08-25 ���������: ���������� � ���������� (��. ������������)
// [+] 2010-08-24 ��������: ������� teri_bis_match_medium_atomic_all - ��������� ������ � �������������
// [+] 2010-06-04 �������� ���������� � \[^...] � �������� � ���������� (��. ������������)
// [+] 2010-06-04 �������� ���������� � \D (��. ������������)
// [+] 2010-06-04 �������� ���������� � \S (��. ������������)
// [+] 2010-06-04 �������� ���������� � \W (��. ������������)
// [+] 2009-09-10 ��������� ������� ������ - TERI_BIS_SPOT_bVLAN
// [+] 2009-09-10 ��������� ������� ������ - TERI_BIS_SPOT_bDPid
// [+] 2009-05-14 ��������� ������� ������ - TERI_BIS_SPOT_mA
// [+] 2009-04-27 ���������: ������� teri_bis_match_medium_atomic_all
// [+] 2009-03-26 ���������: ����� TERI_MODE_SCRAMBLED (��. ������������)
// [+] 2009-02-03 ��������� ������� ������ - TERI_BIS_SPOT_MED
// [+] 2009-01-19 ������� ������� ������ - TERI_BIS_SPOT_mT
// [+] 2009-01-19 ������� ������� ������ - TERI_BIS_SPOT_mF
// [+] 2009-01-14 ��������� ������� ������ - TERI_BIS_SPOT_URL
// [+] 2009-01-14 ��������� ������� ������ - TERI_BIS_SPOT_ICQ
// [+] 2009-01-14 ��������� ������� ������ - TERI_BIS_SPOT_LGN
// [+] 2009-01-14 ��������� ������� ������ - TERI_BIS_SPOT_bI6D
// [+] 2009-01-14 ��������� ������� ������ - TERI_BIS_SPOT_bI6S
// [+] 2009-01-14 ��������� ������� ������ - TERI_BIS_SPOT_bMa
// [+] 2009-01-14 ��������� ������� ������ - TERI_BIS_SPOT_PhE
// [+] 2008-12-21 ��������� ������� ������ - TERI_BIS_SPOT_PhI
// [+] 2008-12-21 ��������� ������� ������ - TERI_BIS_SPOT_PhN
// [+] 2008-12-21 ��������� ������� ������ - TERI_BIS_SPOT_Pr
// [*] 2008-12-18 - ������� DTF-������ (��. dtf_bis.pdf)
//

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#if !defined(TERI_BIS)
#define TERI_BIS

#include <mscu_types.h>

// Now we use the generic helper definitions above to define XXX_API and XXX_LOCAL.
// XXX_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
// XXX_LOCAL is used for non-api symbols.
#ifdef TERI_BIS_EXPORTS // defined if we are building the XXX DLL (instead of using it)
  /// \cond
  #define TERI_BIS_API MSCU_HELPER_DLL_EXPORT
  /// \endcond
#else
  /// \cond
  #define TERI_BIS_API MSCU_HELPER_DLL_IMPORT
  #pragma comment( lib, "teri_bis" )
  /// \endcond
#endif // TERI_BIS_EXPORTS
#define TERI_BIS_LOCAL MSCU_HELPER_DLL_LOCAL

/* ������� ������� ����� */
#define TERI_START_BASE_ERROR       0 /* ��������� ��������� ��� ������ */
#define TERI_STOP_BASE_ERROR      -63 /* �������� ��������� ��� ������ */
#define TERI_START_BASE_WARNING   -64 /* ��������� ��������� ��� �������������� */
#define TERI_STOP_BASE_WARNING   -127 /* �������� ��������� ��� �������������� */

/* ���� ������ (���� �������� �������)
 * ������� ��� teri
 * 0..-31     - ERROR
 * -64..-95   - WARNING
 */
#define  TERI_ERROR_SUCCESS                       0 /* ������� ���������� ��������
                                                * (��������� �� ����������)
                                                */
#define  TERI_ERROR_UNKNOWN                      -1 /* ����������� ������
                                                * (��������� �� ����������)
                                                */
#define  TERI_ERROR_ABORT                        -2 /* �������� �������� (����� Callback-�������)
                                                * (��������� �� ����������)
                                                */
#define  TERI_ERROR_BAD_ARG                      -3 /* �������� �������� �������
                                                * (��������� �� ����������)
                                                */
#define  TERI_ERROR_BAD_OP                       -4 /* �������� ��������
                                                * (��������� �� ����������)
                                                */
#define  TERI_ERROR_TOKEN_CLASH                  -5 /* �������� ����� ����������
                                                * wParam - ����� ������� ��������
                                                * lParam - ����� ������� ��������
                                                */

/* �������������� */
#define  TERI_WARNING_TOKEN_CLASH               -64 /* �������� ����� ����������
                                                * wParam - ����� ������� ��������
                                                * lParam - ����� ������� ��������
                                                */

/* ���� ������ (���� �������� �������)
 * ������� ��� teri_bis
 * -32..-63   - ERROR
 * -96..-127  - WARNING
 */

/* �������� ������ */

#define  TERI_BIS_ERROR_BAD_LINE                           -32 /* �������� ������ �� ������� ������
                                                           * wParam - ����� ������ (������� � 1)
                                                           */

/* �������� ��������� */

#define  TERI_BIS_ERROR_BAD_CONTAINER_SYNTAX               -33 /* �������� ��������� ����� ����������
                                                           * wParam - ����� ����������
                                                           */
#define  TERI_BIS_ERROR_BAD_CONTAINER_ITEM_SYNTAX          -34 /* �������� ��������� �������� ����������
                                                           * wParam - ����� �������� ����������
                                                           * lParam - ������� ���������� ������� (������� � 0)
                                                           */
#define  TERI_BIS_ERROR_BAD_TOKEN1_SYNTAX                  -35 /* �������� ��������� �������� ������ 1
                                                           * wParam - ����� �������� ������ 1
                                                           * lParam - ����� ����������� ������ �������� (������� � 0)
                                                           */
#define  TERI_BIS_ERROR_BAD_TOKEN2_SYNTAX                  -36 /* �������� ��������� �������� ������ 2
                                                           * wParam - ����� �������� ������ 2
                                                           * lParam - ����� ����������� ������ �������� (������� � 0)
                                                           */
#define  TERI_BIS_ERROR_BAD_TOKEN1_SYNTAX_CONTAINER_MISS   -37 /* �������� ��������� �������� ������ 1 - �� ������ �������� � ������ ������
                                                           * wParam - ����� �������� ������ 1
                                                           */
#define  TERI_BIS_ERROR_BAD_TOKEN2_SYNTAX_CONTAINER_MISS   -38 /* �������� ��������� �������� ������ 2 - �� ������ �������� � ������ ������
                                                           * wParam - ����� �������� ������ 2
                                                           */

/* ������ ������ */

#define  TERI_BIS_ERROR_EMPTY_CONTAINER                    -39 /* ������ ���������;
                                                           * wParam - ����� ����������
                                                           */
#define  TERI_BIS_ERROR_EMPTY_GROUP1                       -40 /* ������ ������ ������ 1
                                                           * wParam - ����� ������ ������ 1
                                                           */
#define  TERI_BIS_ERROR_EMPTY_GROUP2                       -41 /* ������ ������ ������ 2
                                                           * wParam - ����� ������ ������ 2
                                                           */

/* ���������� �������� */

#define  TERI_BIS_ERROR_CONTAINER_INDEX_REPEAT             -42 /* ���������� ������� - ���������
                                                           * wParam - ����� ����������
                                                           */
#define  TERI_BIS_ERROR_CONTAINER_ITEM_INDEX_REPEAT        -43 /* ���������� ������� - ������� ����������
                                                           * wParam - ����� �������� ����������
                                                           */
#define  TERI_BIS_ERROR_GROUP1_INDEX_REPEAT                -44 /* ���������� ������� - ������ ������ 1
                                                           * wParam - ����� ������ ������ 1
                                                           */
#define  TERI_BIS_ERROR_GROUP2_INDEX_REPEAT                -45 /* ���������� ������� - ������ ������ 2
                                                           * wParam - ����� ������ ������ 2
                                                           */
#define  TERI_BIS_ERROR_TOKEN1_INDEX_REPEAT                -46 /* ���������� ������� - ������� ������ 1
                                                           * wParam - ����� �������� ������ 1
                                                           */
#define  TERI_BIS_ERROR_TOKEN2_INDEX_REPEAT                -47 /* ���������� ������� - ������� ������ 2
                                                           * wParam - ����� �������� ������ 2
                                                           */

/* �������� �������� ���������� */

#define  TERI_BIS_ERROR_BAD_GROUP1_PRIORITY                -48 /* �������� �������� ���������� - ������ ������ 1
                                                           * wParam - ����� ������ ������ 1
                                                           */
#define  TERI_BIS_ERROR_BAD_GROUP2_PRIORITY                -49 /* �������� �������� ���������� - ������ ������ 2
                                                           * wParam - ����� ������ ������ 2
                                                           */
#define  TERI_BIS_ERROR_BAD_TOKEN1_PRIORITY                -50 /* �������� �������� ���������� - ������� ������ 1
                                                           * wParam - ����� �������� ������ 1
                                                           */
#define  TERI_BIS_ERROR_BAD_TOKEN2_PRIORITY                -51 /* �������� �������� ���������� - ������� ������ 2
                                                           * wParam - ����� �������� ������ 2
                                                           */

/* �������� ���������� ������������ */

#define  TERI_BIS_ERROR_BAD_TOKEN1_SUBTOKEN_COUNT          -52 /* �������� ���������� ������������ - ������� ������ 1
                                                           * wParam - ����� �������� ������ 1
                                                           */
#define  TERI_BIS_ERROR_BAD_TOKEN2_SUBTOKEN_COUNT          -53 /* �������� ���������� ������������ - ������� ������ 2
                                                           * wParam - ����� �������� ������ 2
                                                           */

/* ���������� */

#define  TERI_BIS_ERROR_CONTAINER_CLASH                    -54 /* ���������� ���� �����������;
                                                           * wParam - ����� ����������
                                                           */
#define  TERI_BIS_ERROR_CONTAINER_ITEM_CLASH               -55 /* ���������� ��������� ����������;
                                                           * wParam - ����� ������� �������� ����������
                                                           * lParam - ����� ������� �������� ����������
                                                           */
#define  TERI_BIS_ERROR_TOKEN1_INTERNAL_CLASH              -56 /* �������� ����� ������������� �������� ������ 1
                                                           * wParam - ����� �������� ������ 1
                                                           * lParam - ����� ��������������� ����������� ������ �������� (������� � 0)
                                                           */
#define  TERI_BIS_ERROR_TOKEN2_INTERNAL_CLASH              -57 /* �������� ����� ������������� �������� ������ 2
                                                           * wParam - ����� �������� ������ 2
                                                           * lParam - ����� ��������������� ����������� ������ �������� (������� � 0)
                                                           */

#define  TERI_BIS_ERROR_TOKEN1_CLASH                       -58 /* �������� ����� ���������� �������� ������ 1
                                                           * wParam - ����� ������� �������� ������ 1
                                                           * lParam - ����� ������� �������� ������ 1
                                                           */
#define  TERI_BIS_ERROR_TOKEN2_CLASH                       -59 /* �������� ����� ���������� �������� ������ 2
                                                           * wParam - ����� ������� �������� ������ 2
                                                           * lParam - ����� ������� �������� ������ 2
                                                           */

/* �������� ������ */

#define  TERI_BIS_ERROR_BAD_GROUP1_REF                     -60 /* �������� ������ � ������ ������ 1 �� ������ ������ 2
                                                           * wParam - ����� ������ ������ 1
                                                           * lParam - �������� ����� ������ ������ 2, �� ������� ��������� wParam
                                                           */

/* �������� ������������ */

#define  TERI_BIS_ERROR_BAD_TOKEN1_SPOT                    -61 /* �������� ������������ �������� ������ 1
                                                           * wParam - ����� �������� ������ 1
                                                           * lParam - ����� ����������� ������ �������� (������� � 0)
                                                           */
#define  TERI_BIS_ERROR_BAD_TOKEN2_SPOT                    -62 /* �������� ������������ �������� ������ 2
                                                           * wParam - ����� �������� ������ 2
                                                           * lParam - ����� ����������� ������ �������� (������� � 0)
                                                           */

/* �������� ����� */

#define  TERI_BIS_ERROR_BAD_TOKEN1_LENGTH                  -63 /* �������� ����� �������� ������ 1
                                                           * wParam - ����� �������� ������ 1
                                                           * lParam - ����� ����������� ������ �������� (������� � 0)
                                                           */
#define  TERI_BIS_ERROR_BAD_TOKEN2_LENGTH                  -64 /* �������� ����� �������� ������ 2
                                                           * wParam - ����� �������� ������ 2
                                                           * lParam - ����� ����������� ������ �������� (������� � 0)
                                                           */

/* �������������� */

/* ��� ������� */

#define  TERI_BIS_WARNING_CONTAINER_INDEX_MISS             -96 /* ���������� ������� - ���������
                                                           * wParam - ����� ������
                                                           */
#define  TERI_BIS_WARNING_CONTAINER_ITEM_INDEX_MISS        -97 /* ���������� ������� - ������� ����������
                                                           * wParam - ����� ������
                                                           */
#define  TERI_BIS_WARNING_GROUP1_INDEX_MISS                -98 /* ���������� ������� - ������ ������ 1
                                                           * wParam - ����� ������
                                                           */
#define  TERI_BIS_WARNING_GROUP2_INDEX_MISS                -99 /* ���������� ������� - ������ ������ 2
                                                           * wParam - ����� ������
                                                           */
#define  TERI_BIS_WARNING_TOKEN1_INDEX_MISS               -100 /* ���������� ������� - ������� ������ 1
                                                           * wParam - ����� ������
                                                           */
#define  TERI_BIS_WARNING_TOKEN2_INDEX_MISS               -101 /* ���������� ������� - ������� ������ 2
                                                           * wParam - ����� ������
                                                           */

/* ��� ���������� */

#define  TERI_BIS_WARNING_GROUP1_PRIO_MISS                -102 /* ���������� ���������� - ������ ������ 1
                                                           * wParam - ����� ������
                                                           */
#define  TERI_BIS_WARNING_GROUP2_PRIO_MISS                -103 /* ���������� ���������� - ������ ������ 2
                                                           * wParam - ����� ������
                                                           */
#define  TERI_BIS_WARNING_TOKEN1_PRIO_MISS                -104 /* ���������� ���������� - ������� ������ 1
                                                           * wParam - ����� ������
                                                           */
#define  TERI_BIS_WARNING_TOKEN2_PRIO_MISS                -105 /* ���������� ���������� - ������� ������ 2
                                                           * wParam - ����� ������
                                                           */

/* ��� ���� */

#define  TERI_BIS_WARNING_GROUP1_PATH_MISS                -106 /* ���������� ���� - ������ ������ 1
                                                           * wParam - ����� ������
                                                           */
#define  TERI_BIS_WARNING_GROUP2_PATH_MISS                -107 /* ���������� ���� - ������ ������ 2
                                                           * wParam - ����� ������
                                                           */
#define  TERI_BIS_WARNING_TOKEN1_PATH_MISS                -108 /* ���������� ���� - ������� ������ 1
                                                           * wParam - ����� ������
                                                           */
#define  TERI_BIS_WARNING_TOKEN2_PATH_MISS                -109 /* ���������� ���� - ������� ������ 2
                                                           * wParam - ����� ������
                                                           */

/* ���������� */

#define  TERI_BIS_WARNING_TOKEN1_CLASH                    -110 /* �������� ����� ���������� �������� ������ 1
                                                           * wParam - ����� ������� �������� ������ 1
                                                           * lParam - ����� ������� �������� ������ 1
                                                           */
#define  TERI_BIS_WARNING_TOKEN2_CLASH                    -111 /* �������� ����� ���������� �������� ������ 2
                                                           * wParam - ����� ������� �������� ������ 2
                                                           * lParam - ����� ������� �������� ������ 2
                                                           */

/* ������ ������ */

#define  TERI_BIS_WARNING_EMPTY_CONTAINER                    -112 /* ������ ���������;
                                                           * wParam - ����� ����������
                                                           */
#define  TERI_BIS_WARNING_EMPTY_GROUP1                       -113 /* ������ ������ ������ 1
                                                           * wParam - ����� ������ ������ 1
                                                           */
#define  TERI_BIS_WARNING_EMPTY_GROUP2                       -114 /* ������ ������ ������ 2
                                                           * wParam - ����� ������ ������ 2
                                                           */

/* ���� �������
 *
 * Progress (CP_) - ���������� � ���� ���������� ��������
 */

/* ����� �������� ��������� */
#define  CP_bis_generate_lod_begin        32 /* lParam - <�����_�����_������> << 8 + <�������_����> */
#define  CP_bis_generate_lod_progress     33 /* wParam - ������� ����������, lParam - <�����_�����_������> << 8 + <�������_����> */
#define  CP_bis_generate_lod_end          34 /* lParam - <�����_�����_������> << 8 + <�������_����> */
/* �������� - ������� */
/* �������� ��������� */
#define  CP_generate_ver_begin        1  /* lParam - <�����_�����_������> << 8 + <�������_����> */
#define  CP_generate_ver_progress     2  /* wParam - ������� ����������, lParam - <�����_�����_������> << 8 + <�������_����> */
#define  CP_generate_ver_end          3  /* lParam - <�����_�����_������> << 8 + <�������_����> */
/* ��������� �������� */
#define  CP_generate_gen_begin        4  /* lParam - <�����_�����_������> << 8 + <�������_����> */
#define  CP_generate_gen_progress     5  /* wParam - ������� ����������, lParam - <�����_�����_������> << 8 + <�������_����> */
#define  CP_generate_gen_end          6  /* lParam - <�����_�����_������> << 8 + <�������_����> */
/* ������ �������� */
#define  CP_generate_cmp_begin        7  /* lParam - <�����_�����_������> << 8 + <�������_����> */
#define  CP_generate_cmp_progress     8  /* wParam - ������� ����������, lParam - <�����_�����_������> << 8 + <�������_����> */
#define  CP_generate_cmp_end          9  /* lParam - <�����_�����_������> << 8 + <�������_����> */

/* ��� Callback-�������, ���������� ��� ��������� �������� � ���������� ���������
*
* ud - �������� user_data, ������������ ��� ������ ������� teri_bis_generate (����� ����� ����� ��������)
* Msg - ��� �������
* wParam - �������� �������
* lParam - �������� �������
* MsgStr - ������������� ������� � ��������� ����
*
* ������������ ��������:
*   true  - �������� ����� ���� ����������
*   false - �������� ���������� ��������
*/
typedef gboolean (MSCU_CALL_PREFIX * Tteri_generate_callback)(gpointer user_data, gint32 Msg, guint32 wParam, guint32 lParam, gpchar MsgStr);

/* ����� */

// ������������������ � ��������
//
#define TERI_MODE_CASE_INSENSITIVE			0x00000001
// "������" ���������
//  ��� ���������:
//  ��������� ��������� ��������� ���� � �����
//
#define TERI_MODE_SOFT_SYNTAX						0x00000002
// ��� ���������:
//  �� ��������� "������", �.�. �������� ������
//  ������� "��������" � �������
//
#define TERI_MODE_NO_TAILS							0x00000004
// ��� ���������� � ������� �����:
//  ���������� ���������� ��������� ��������������� ������
//
#define TERI_MODE_SCRAMBLED							0x00000008
// ������������ �������� ��������
//  ��� ���������:
//  ������������ ������ � ��������� � ���������� ��������� �������� ��� ��������� ��������� (��������� �� ������� ����� ��������� � ����� ������)
//
#define TERI_MODE_IGNORE_BAD_TOKENS			0x00000010
// ������������ ������������ ���������������
//  ��� ���������:
//  ������������ ������������ �������� �������� ��������������� �����, ���������, �����������, ��������� ����������� � ���������� ��������� �������� ��� ������ ������
//
#define TERI_MODE_IGNORE_ID_DUPLICATION	0x00000020
// ��� ��������� (��������� ����������):
//  �� "��������" ���� ��� ����������
//  ��� ���������� ����� ����������� ����� ����������, �� ������������� ������ ��������
//
#define TERI_MODE_NO_SHIFT							0x00000040
// ������������ ���������� ���������������
//  ��� ���������:
//  ������������ ���������� �������� �������� ��������������� �����, ���������, �����������, ��������� ����������� � ����������� �������� �� ���������
//
#define TERI_MODE_IGNORE_NO_ID					0x00000080

// �� ��������� �������� ���������
//  ��� ���������:
//  �� ��������� ���� �������� ���������, ��� �������� ������� �������� ��������
//	��������� ���������� ��� ����� ������� ������� ��������� (������� �������� ����)
//  ������ ����� �������� ������ ��� ���������� ������������� ������������� � �������� TERI_MODE_SOFT_SYNTAX � TERI_MODE_NO_TAILS
//
#define TERI_MODE_NO_VERIFICATION				0x00000100

// �������� ������������� �� ���������� �������� ����
//  ��� ���������:
//  �������� ��������������� ��������� �� ���������� ���������� �������� ���� �����, ���������, �����������, ��������� ����������� � ����������� �������� �� ���������
//
#define TERI_MODE_WARN_NO_PATH					0x00000200

// �������� ������������� �� ���������� �������� ����������
//  ��� ���������:
//  �������� ��������������� ��������� �� ���������� ��������� �������� ���������� �����, ���������, �����������, ��������� ����������� � ����������� �������� �� ���������
//
#define TERI_MODE_WARN_NO_PRIO					0x00000400

/* ������������ � ����������� �������� ���������� (�������/������ �������) */
#define MIN_PRIORITY_VALUE  0
#define MAX_PRIORITY_VALUE  255

/* ������������ �������� ����������� ���������� */
#define MAX_ABSOLUTE_PRIORITY_VALUE   0xffff

/* ������������ ���������� ������������ � �������� */
#define MAX_SUBTOKEN_COUNT  8

//----------------------------------------------------------------------------------------------------------------------
/* ������ ������ (spot) */
#define  TERI_BIS_SPOT_NONE   0x00 // �� ����������
#define  TERI_BIS_SPOT_bIS    0x01 // IP-source
#define  TERI_BIS_SPOT_bID    0x02 // IP-destination
#define  TERI_BIS_SPOT_bPS    0x03 // TCP/UDP port-source
#define  TERI_BIS_SPOT_bPD    0x04 // TCP/UDP port-destination
#define  TERI_BIS_SPOT_bPI    0x05 // Protocol idendifier
#define  TERI_BIS_SPOT_T      0x06 // Text
#define  TERI_BIS_SPOT_H      0x07 // Header
#define  TERI_BIS_SPOT_S      0x08 // Service
#define  TERI_BIS_SPOT_C      0x09 // CALL
#define  TERI_BIS_SPOT_A      0x0a // ANSW
#define  TERI_BIS_SPOT_mS     0x0b // Mail Subject
#define  TERI_BIS_SPOT_F      0x0c // File Name
#define  TERI_BIS_SPOT_bT     0x0d // binary Text
#define  TERI_BIS_SPOT_bSTS   0x0e // Socket: TCP/IP source
#define  TERI_BIS_SPOT_bSTD   0x0f // Socket: TCP/IP dest
#define  TERI_BIS_SPOT_bSUS   0x10 // Socket: UDP/IP source
#define  TERI_BIS_SPOT_bSUD   0x11 // Socket: UDP/IP dest
#define  TERI_BIS_SPOT_bMD    0x12 // DVB MAC-address
#define  TERI_BIS_SPOT_Pr     0x13 // Protocol Name
#define  TERI_BIS_SPOT_PhN    0x14 // Phone Number
#define  TERI_BIS_SPOT_PhI    0x15 // Phone IMSI
#define  TERI_BIS_SPOT_PhE    0x16 // Phone IMEI
#define  TERI_BIS_SPOT_bMa    0x17 // MAC-address
#define  TERI_BIS_SPOT_bI6S   0x18 // IPv6-source
#define  TERI_BIS_SPOT_bI6D   0x19 // IPv6-destination
#define  TERI_BIS_SPOT_LGN    0x1a // LOGIN
#define  TERI_BIS_SPOT_ICQ    0x1b // ICQ-number
#define  TERI_BIS_SPOT_URL    0x1c // URL
#define  TERI_BIS_SPOT_MED    0x1d // Media-��� (content-type)
#define  TERI_BIS_SPOT_mA     0x1e // E-Mail address
#define  TERI_BIS_SPOT_bDPid  0x1f // DVB PID
#define  TERI_BIS_SPOT_bVLAN  0x20 // Virtual LAN
#define  TERI_BIS_SPOT_bMPLS  0x21 // MPLS label
#define  TERI_BIS_SPOT_ISN    0x22 // Social Networks Identifier
#define  TERI_BIS_SPOT_PhB    0x23 // Phone BlackBerry PIN
#define  TERI_BIS_SPOT_DN     0x24 // DN - Domain Name
#define  TERI_BIS_SPOT_URLad  0x25 // URL - Ads
#define  TERI_BIS_SPOT_DNad   0x26 // DN - Domain Name - Ads
#define  TERI_BIS_SPOT_ORIG   0x27 // HTTP Origin
#define  TERI_BIS_SPOT_REF    0x28 // HTTP Referer
#define  TERI_BIS_SPOT_fGET   0x29 // HTTP GET flag
#define  TERI_BIS_SPOT_fPOST  0x2a // HTTP POST flag
#define  TERI_BIS_SPOT_NASp   0x2b // HTTP GET flag
#define  TERI_BIS_SPOT_BSid   0x2c // HTTP POST flag

#define  TERI_BIS_SPOT_MAX    0x2c // ������������ SPOT
#define  TERI_BIS_SPOT_COUNT  0x2d // ���������� SPOT

/* �������� ������ ����������
 * version_str - ������ ������������ ������ ����
 * version_major - ������� �������� �������� ������
 * version_minor - ������� �������� �������� ������
 */
extern "C" TERI_BIS_API void MSCU_CALL_PREFIX teri_bis_get_version(gpchar_p version_str, gint_p version_major, gint_p version_minor);

/* ������� ��������� ������� � ���������� ��������� �� ����
 *
 * ������� ���������� 0 - ���� ��������� ������ �������� ����������
 *   � ������ ������ ������������ ��������� �� ��������� ���������
 */
extern "C" TERI_BIS_API gpointer MSCU_CALL_PREFIX teri_bis_create();

/* �������� ��������� �������, �� ������� ��������� AInstance
 *
 * AInstance - ��������� �������
 *
 * � ������ ������ ���������� TERI_ERROR_SUCCESS
 */
extern "C" TERI_BIS_API gint MSCU_CALL_PREFIX teri_bis_destroy(gpointer instance);

/* �������� ���������� � ��������� ������
 *
 * ��� ������ ���������� ��� ������ ����� ������� � �����������
 */
extern "C" TERI_BIS_API gint MSCU_CALL_PREFIX teri_bis_get_error(gpointer instance, gint_p wParam, gint_p lParam, gpchar_p MsgStr);

/* ��������� ������ ������� � �����
 *
 * instance - ��������� �������
 * buf - ��������� �� �����, � ������� ������������ �������
 * ����� ������ ����������� ���������� �������
 * len - ������ ������ � ������
 *
 * ��� ���� ����� ������ ������ ������, ������������ ��� ������ ��������,
 * ���������� ������� ������ ������� � ������� ���������� �� �����
 * ��� � ������� ������. � ���� ������ ������� � �������� ���������� ������
 * ����������� ������ � ������
 *
 * ���� ����� ������ ������� (������������), ������� ������ ������ TERI_ERROR_BAD_ARG
 *
 * � ������ �������� ���������� ������� ������ ���������� ����������� ����
 */
extern "C" TERI_BIS_API gint MSCU_CALL_PREFIX teri_bis_save(gpointer instance, gpchar buf, gint32 len);

/* ��������� ������ ������� �� ������
 *
 * instance - ��������� �������
 * buf - ��������� �� �����, � ������� ������������ �������
 * len - ������ ������ � ������
 *
 * ���� �������� ������ ������, ������� ������ ������ TERI_ERROR_BAD_DATA
 * ���� ����� ������ ������� (� ��������� �� �����), ������� ������ ������ TERI_ERROR_BAD_DATA
 *
 * � ������ ������� �������� ������� ������ ���������� ����������� ����
 */
extern "C" TERI_BIS_API gint MSCU_CALL_PREFIX teri_bis_load(gpointer instance, gpchar buf, gint32 len);

/* ���������� �������� � ���� ��������� ��������� � ITF-�������
 * ���������� ������� � ������� ���
 *
 * instance - ��������� �������
 * mode - ������� �����, ���������� ����� ��������� (TERI_MODE_XXX)
 * buf, len: ����� � ���������� � ITF-�������
 * check_only - ����������/��������
 * cb - ��������� �� ������� ��������� ������
 *   ������ ������ ���������� ��� ������������� ������ �������
 *   �� ����������� � ������ �������� �� ����������� ������
 * ud - ���������������� ������ - ������ ��������, ������������ ��� ������ ������� cb (����� ����� ����� ��������)
 *
 * ���������� TERI_ERROR_SUCCESS � ������ ������� ��������� ��������
 * ��������� ��������:
 *   TERI_ERROR_TOKEN_CLASH          - �������� ����� ����������
 *   TERI_ERROR_BAD_SYNTAX           - �������� ���������
 */
extern "C" TERI_BIS_API gint MSCU_CALL_PREFIX teri_bis_generate(gpointer instance, gint mode, gpchar buf, gint len, gboolean check_only, Tteri_generate_callback cb, gpointer ud);

/* ���������� �������� � ���� ��������� ��������� � ITF-�������
 * ���������� ������� � ������� ���
 * wts - "with transparent spots" - ��������� ������ ���������� �������� ������
 * ���������� ������� - �����, �������� ������� ������������� � "\." (����� ������), �.�. ����� ����� �� ������ ������� ���� ������������� ���������
 *
 * instance - ��������� �������
 * mode - ������� �����, ���������� ����� ��������� (TERI_MODE_XXX)
 * buf, len: ����� � ���������� � ITF-�������
 * check_only - ����������/��������
 * cb - ��������� �� ������� ��������� ������
 *   ������ ������ ���������� ��� ������������� ������ �������
 *   �� ����������� � ������ �������� �� ����������� ������
 * ud - ���������������� ������ - ������ ��������, ������������ ��� ������ ������� cb (����� ����� ����� ��������)
 * count - ���������� ��������� � ������� spots
 * spots - ������ �������� (����) ������ - ��������� TERI_BIS_SPOT_XXX
 *
 * ���������� TERI_ERROR_SUCCESS � ������ ������� ��������� ��������
 * ��������� ��������:
 *   TERI_ERROR_TOKEN_CLASH          - �������� ����� ����������
 *   TERI_ERROR_BAD_SYNTAX           - �������� ���������
 */
extern "C" TERI_BIS_API gint MSCU_CALL_PREFIX teri_bis_generate_wts(gpointer instance, gint mode, gpchar buf, gint len, gboolean check_only, Tteri_generate_callback cb, gpointer ud, gsize_t count, const guint32 * spots);

/* ������� �������� */
/* Tteri_bis_match_level */
#define tbmlLevel1  0
#define tbmlLevel2  1

#ifndef TTERI_BIS_MATCH_ENTRY_TYPE
#define TTERI_BIS_MATCH_ENTRY_TYPE
/* ��������� �������� (�����������) � ����� ������ */
STRUCT_PACKED_BEGIN // ������������� ������������ �������� � 1 ����
struct STRUCT_PACKED_ATTRIBUTE Tteri_bis_match_entry {
  gpchar buf; /* ��������� �� ������ ������ ��������� (�� ������ ������ ������!) */
  gint32 len; /* ���������� �������� �� ��������� */
};
STRUCT_PACKED_END // ��������������� ������������ �������� �� ���������
/// ��������� �� ��������� Tteri_bis_match_entry
typedef Tteri_bis_match_entry* Pteri_bis_match_entry;
#endif

#ifndef TTERI_BIS_MATCH_TOKEN_TYPE
#define TTERI_BIS_MATCH_TOKEN_TYPE
/* ���������� � ��������� �������� */
STRUCT_PACKED_BEGIN // ������������� ������������ �������� � 1 ����
struct STRUCT_PACKED_ATTRIBUTE Tteri_bis_match_token {
  gint level;
  guint32 absolute_prio; /* ���������� ��������� */
  guint32 up_id; /* ����� ������� */
  guint32 up_prio; /* ��������� ������� */
  guint32 id; /* ����� �������� */
  guint32 id_ext; /* ���������� ������ �������� */
  guint32 prio; /* ��������� */
  gint32  is_stat; /* ���� - stat (0 - �����������, �� 0 - ������������) */
  gint32  is_rem; /* ���� - rem (0 - �����������, �� 0 - ������������) */
  gpchar  path; /* ���� */
  guint32 entry_count; /* ���������� ��������� */
  Tteri_bis_match_entry entry[MAX_SUBTOKEN_COUNT]; /* ������ �������� */
  gpointer entry_bud[MAX_SUBTOKEN_COUNT]; /* ������ �������� */
  guint32 entry_spot[MAX_SUBTOKEN_COUNT]; /* ������ �������� ������ */
};
STRUCT_PACKED_END // ��������������� ������������ �������� �� ���������
/// ��������� �� ��������� Tteri_bis_match_token
typedef Tteri_bis_match_token* Pteri_bis_match_token;
#endif

/* ��� Callback-�������, ���������� ��� �������
*
* ud - �������� ud, ������������ ��� ������ ������� teri_bis_match_data (����� ����� ����� ��������)
* token - ���������� � ��������� ���������
*/
typedef void (MSCU_CALL_PREFIX * Tteri_bis_match_callback)(gpointer ud, Pteri_bis_match_token token);

/* ������ ������
 *
 * instance - ��������� �������
 *
 * ���������� TERI_ERROR_SUCCESS, ���� ��� � �������
 */
extern "C" TERI_BIS_API gint MSCU_CALL_PREFIX teri_bis_match_start(gpointer instance);

/* ���������, ������������ ����� � ��������� ������
 *
 * instance - ��������� �������
 * buf - ��������� �� �����, ������ �������� ������������ �����
 *       ���������� ������ ���������� ��� ������������� ����� � ���������� cp1251
 * len - ������ ������ � ������
 * spot - ������ (�����) ������ - ��������� TERI_BIS_SPOT_XXX
 * bud - �������� ud, ������������� � ������� ������� ������
 *
 * ���������� TERI_ERROR_SUCCESS � ������ ������
 */
extern "C" TERI_BIS_API gint MSCU_CALL_PREFIX teri_bis_match_data(gpointer instance, gconstpchar buf, gint32 len, guint32 spot, gpointer bud);

/* ���������, ����������� ����� � ������������ ��������� ������
 *
 * instance - ��������� �������
 * cb - ��������� �� ������� ��������� ������
 *   ������ ������ ���������� ��� ����������� ��������� (����� ���� ������� �� 0 �� ���������� ���)
 *   ������ ������ ���������� ��� ������� ���������� stat-��������
 *   ����� �� ���� ������� ��������� ��������� ���������� ���� � �������� �����������, ��� �������� � ���������� �������
 *     �.�. ���� ����� ������� ��������� �� �������������� ��������� (���� � ���������� �����������), ������� ��������� ������ ���� ��� ��� ������ �� ���
 * ud - ���������������� ������ - ������ ��������, ������������ ��� ������ ������� cb (����� ����� ����� ��������)
 *
 * ���������� ����� ���������� ��������� ���������
 */
extern "C" TERI_BIS_API gint MSCU_CALL_PREFIX teri_bis_match_stop(gpointer instance, Tteri_bis_match_callback cb, gpointer ud);

// ���������, ������������ ����� � ������� ��������
// ����� �� ������ ������ �� ������������
// �� �������������� ��������� ��������
// �� �������������� ���� ��������� (rem/stat)
//
// instance - ��������� �������
// buf - ��������� �� �����, ������ �������� ������������ �����
//       ���������� ������ ���������� ��� ������������� ����� � ���������� cp1251
// len - ������ ������ � ������
// buf2 - ��������� �� �������������� �����, ������ �������� ������������ �����
//       ���������� ������ ���������� ��� ������������� ����� � ���������� cp1251
// len2 - ������ �������������� ������ � ������
// spot - ������ (�����) ������ - ��������� TERI_BIS_SPOT_XXX
// bud - �������� ud, ������������� � ������� ������� ������
// cb - ��������� �� ������� ��������� ������
//   ������ ������ ���������� ��� ����������� ��������� (����� ���� ������� �� 0 �� 1 ����)
//   �� ���� ������� ��������� ��������� ���������� ���� � �������� �����������, ��� �������� � ���������� �������
//     �.�. ���� ����� ������� ��������� ��������� (���� � ���������� �����������), ������� ��������� ������ ���� ��� ��� ������ �� ���
// ud - ���������������� ������ - ������ ��������, ������������ ��� ������ ������� cb (����� ����� ����� ��������)
//
// ���������� ���-�� ��������� � ������ ������
extern "C" TERI_BIS_API gint MSCU_CALL_PREFIX teri_bis_match_medium_atomic(gpointer instance, gconstpchar buf, gint32 len, gconstpchar buf2, gint32 len2, guint32 spot, gpointer bud, Tteri_bis_match_callback cb, gpointer ud);

// ���������, ������������ ����� � ������� ��������
// ������������ ����� �� ������ �� ������� ��������� ������ ��������
// ����� �� ������ ������ �� ������������
// �� �������������� ��������� ��������
// �� �������������� ���� ��������� (rem/stat)
//
// instance - ��������� �������
// buf - ��������� �� �����, ������ �������� ������������ �����
//       ���������� ������ ���������� ��� ������������� ����� � ���������� cp1251
// len - ������ ������ � ������
// buf2 - ��������� �� �������������� �����, ������ �������� ������������ �����
//       ���������� ������ ���������� ��� ������������� ����� � ���������� cp1251
// len2 - ������ �������������� ������ � ������
// spot - ������ (�����) ������ - ��������� TERI_BIS_SPOT_XXX
// bud - �������� ud, ������������� � ������� ������� ������
// cb - ��������� �� ������� ��������� ������
//   ������ ������ ���������� ��� ����������� ��������� (����� ���� ������� �� 0 �� 1 ����)
// ud - ���������������� ������ - ������ ��������, ������������ ��� ������ ������� cb (����� ����� ����� ��������)
//
// ���������� ���-�� ��������� � ������ ������
extern "C" TERI_BIS_API gint MSCU_CALL_PREFIX teri_bis_match_medium_atomic_first_only(gpointer instance, gconstpchar buf, gint32 len, gconstpchar buf2, gint32 len2, guint32 spot, gpointer bud, Tteri_bis_match_callback cb, gpointer ud);

// ���������, ������������ ����� � ������� ��������
// ����� �� ������ ������ �� ������������
// �������������� ��������� ��������
// �� �������������� ���� ��������� (rem/stat)
// �� �������������� ���������� - �������� ��� ��������� ��������
//
// instance - ��������� �������
// buf - ��������� �� �����, ������ �������� ������������ �����
//       ���������� ������ ���������� ��� ������������� ����� � ���������� cp1251
// len - ������ ������ � ������
// buf2 - ��������� �� �������������� �����, ������ �������� ������������ �����
//       ���������� ������ ���������� ��� ������������� ����� � ���������� cp1251
// len2 - ������ �������������� ������ � ������
// spot - ������ (�����) ������ - ��������� TERI_BIS_SPOT_XXX
// bud - �������� ud, ������������� � ������� ������� ������
// cb - ��������� �� ������� ��������� ������
//   ������ ������ ���������� ��� ����������� ��������� (����� ���� ������� �� 0 �� ���������� ���)
// ud - ���������������� ������ - ������ ��������, ������������ ��� ������ ������� cb (����� ����� ����� ��������)
//
// ���������� ���-�� ��������� � ������ ������
extern "C" TERI_BIS_API gint MSCU_CALL_PREFIX teri_bis_match_medium_atomic_all(gpointer instance, gconstpchar buf, gint32 len, gconstpchar buf2, gint32 len2, guint32 spot, gpointer bud, Tteri_bis_match_callback cb, gpointer ud);

// ���������, ������������ ����� � ������� ��������
// ����� �� ������ ������ �� ������������
// �������������� ��������� ��������
// �� �������������� ���� ��������� (rem/stat)
// �� �������������� ���������� - �������� ��� ��������� ��������
//
// instance - ��������� �������
// count - ���������� � ��������� �������� bufs, lens, spots, buds
// bufs - ������ ���������� �� �����, ������ �������� ������������ �����
//       ���������� ������ ���������� ��� ������������� ����� � ���������� cp1251
// lens - ������ �������� ������� ������ � ������
// spots - ������ �������� (����) ������ - ��������� TERI_BIS_SPOT_XXX
// buds - ������ ���������� ud, ������������� � ������� ������� ������, ����� ���� ����� 0
// cb - ��������� �� ������� ��������� ������
//   ������ ������ ���������� ��� ����������� ��������� (����� ���� ������� �� 0 �� ���������� ���)
// ud - ���������������� ������ - ������ ��������, ������������ ��� ������ ������� cb (����� ����� ����� ��������)
//
// ���������� ���-�� ��������� � ������ ������
extern "C" TERI_BIS_API gint MSCU_CALL_PREFIX teri_bis_match_medium_atomic_all_bufs(gpointer instance, gint count, gconstpchar* bufs, gint32* lens, guint32* spots, gpointer* buds, Tteri_bis_match_callback cb, gpointer ud);

/* ���������, ������������ ����� � ��������� ������
 *
 * instance - ��������� �������
 * buf - ��������� �� �����, ������ �������� ������������ �����
 *       ���������� ������ ���������� ��� ������������� ����� � ���������� cp1251
 * len - ������ ������ � ������
 * spot - ������ (�����) ������ - ��������� TERI_BIS_SPOT_XXX
 *
 * ���������� ����� ��������� ��������� � ������ ������
 */
extern "C" TERI_BIS_API gint MSCU_CALL_PREFIX teri_bis_match_simple(gpointer instance, gpchar buf, gint32 len, guint32 spot);

#ifndef TTERI_BIS_SYNTAX_ENTRY_TYPE
#define TTERI_BIS_SYNTAX_ENTRY_TYPE
/* ��������� ���������� ������� � ����� ������ */
STRUCT_PACKED_BEGIN // ������������� ������������ �������� � 1 ����
struct STRUCT_PACKED_ATTRIBUTE Tteri_bis_syntax_entry {
  gint32 pos; /* ������ ������� ������� ��������� (������� � 0) */
  gint32 len; /* ���������� �������� �� ��������� */
};
STRUCT_PACKED_END // ��������������� ������������ �������� �� ���������
/// ��������� �� ��������� Tteri_bis_syntax_entry
typedef Tteri_bis_syntax_entry* Pteri_bis_syntax_entry;
#endif

/*
 * ������� �������� ������ �� ���������� ��������� �� ������������� �� ���������� ������ (htf->ttf)
 * ���������� -1, ���� ��� ������ ��������� ��� ������� ������� ���� ��������� ������ ��������
 *
 * ���������:
 *   accept_container - ���������� ����������� ��������� � ������ "\(?P<���_����������>)", "\b", "\^", "\$"
 *   buf[len] - ������ � htf-�������
 *   entry[entry_len] - ������, ����������� ������� ��������� ��������� ��������
 *   IN:entry_len - ������ ������� (���������� ���������)
 *   OUT:entry_len - ���������� ���������� ���������� ���������
 */
extern "C" TERI_BIS_API gint MSCU_CALL_PREFIX teri_bis_check_syntax(gboolean accept_containers, gpchar buf, gint len, Pteri_bis_syntax_entry entry, gint_p entry_len);

//////////////////////////////////////////////////////////////////////////
extern "C" TERI_BIS_API void MSCU_CALL_PREFIX teri_bis_wrapper_set_klog_std_event(Tklog_std_event Aklog_std_event); //!!!deprecated
extern "C" TERI_BIS_API void MSCU_CALL_PREFIX teri_bis_wrapper_set_terminated_flag(gboolean_p Aterminated_flag); //!!!deprecated

extern "C" TERI_BIS_API gboolean MSCU_CALL_PREFIX teri_bis_wrapper_std_generate_callback(gpointer user_data, gint32 Msg, guint32 wParam, guint32 lParam, gpchar MsgStr);

extern "C" TERI_BIS_API gpointer MSCU_CALL_PREFIX teri_bis_wrapper_create();
extern "C" TERI_BIS_API void MSCU_CALL_PREFIX teri_bis_wrapper_destroy(gpointer instance);

extern "C" TERI_BIS_API gboolean MSCU_CALL_PREFIX teri_bis_wrapper_set_parameters(gpointer instance, guint32 stat_period, gconstpchar stat_dir_name, guint32 file_update_period);
extern "C" TERI_BIS_API gconstpchar MSCU_CALL_PREFIX teri_bis_wrapper_stat_dir_name(gpointer instance);

extern "C" TERI_BIS_API gboolean MSCU_CALL_PREFIX teri_bis_wrapper_set_log_parameters(gpointer instance, gconstpchar name, gboolean log_progress, gboolean log_margins);

// ���������, ��������������� ������ ���������� �������� ������
// ���������� ������� - �����, �������� ������� ������������� � "\." (����� ������), �.�. ����� ����� �� ������ ������� ���� ������������� ���������
//
// instance - ��������� �������, ������������ �������� teri_bis_wrapper_create
// count - ���������� ��������� � ������� spots
// spots - ������ �������� (����) ������ - ��������� TERI_BIS_SPOT_XXX
//
// ���������� true � ������ ������
extern "C" TERI_BIS_API gboolean MSCU_CALL_PREFIX teri_bis_wrapper_set_transparent_spots(gpointer instance, gsize_t count, const guint32 * spots);

extern "C" TERI_BIS_API gconstpchar MSCU_CALL_PREFIX teri_bis_wrapper_error_message(gpointer instance);

// Attention! This function updates teri_bis engine, if there is newly reloaded one, so do not call this function
// more than one time per atomic search stage (teri_bis_match_start..teri_bis_match_stop)
extern "C" TERI_BIS_API gpointer MSCU_CALL_PREFIX teri_bis_wrapper_engine(gpointer instance);
// enter/leave procedure to use in multi-threaded search
extern "C" TERI_BIS_API void MSCU_CALL_PREFIX teri_bis_wrapper_engine_enter(gpointer instance);
extern "C" TERI_BIS_API void MSCU_CALL_PREFIX teri_bis_wrapper_engine_leave(gpointer instance);
// returns engine pointer that is stable within active thread until next teri_bis_wrapper_tls_engine function call
// function compares values of main engine and thread local storage engine pointers
// then if differs, new tls engine is created as copy of changed main tls engine
extern "C" TERI_BIS_API gpointer MSCU_CALL_PREFIX teri_bis_wrapper_tls_engine(gpointer instance);

// class LOCAL_API Tteri_bis_wrapper_holder {
// public:
//   Tteri_bis_wrapper_holder(gpointer teri_bis_wrapper_instance): instance_(teri_bis_wrapper_instance)
//   {
//   };
//   ~Tteri_bis_wrapper_holder()
//   {
//     if (instance_)
//       teri_bis_wrapper_destroy(instance_);
//   };
//   gpointer instance_;
// private:
//   Tteri_bis_wrapper_holder() {}
//   Tteri_bis_wrapper_holder(const Tteri_bis_wrapper_holder &) {}
// };

// this is suitable class to replace teri_bis_wrapper_engine_enter/teri_bis_wrapper_engine_leave usage
class LOCAL_API Tteri_bis_wrapper_engine_locker {
public:
  Tteri_bis_wrapper_engine_locker(gpointer teri_bis_wrapper_instance): instance_(teri_bis_wrapper_instance)
  {
    if (instance_)
      teri_bis_wrapper_engine_enter(instance_);
  };
  ~Tteri_bis_wrapper_engine_locker()
  {
    if (instance_)
      teri_bis_wrapper_engine_leave(instance_);
  };
private:
  Tteri_bis_wrapper_engine_locker() {}
  Tteri_bis_wrapper_engine_locker(const Tteri_bis_wrapper_engine_locker &) {}
  gpointer instance_;
};

extern "C" TERI_BIS_API gboolean MSCU_CALL_PREFIX teri_bis_wrapper_compile(gpointer instance, gconstpchar file_name, gconstpchar file_name_to_save, gboolean do_save, gboolean check_only);
extern "C" TERI_BIS_API gboolean MSCU_CALL_PREFIX teri_bis_wrapper_load(gpointer instance, gconstpchar file_name);
extern "C" TERI_BIS_API gboolean MSCU_CALL_PREFIX teri_bis_wrapper_generate(gpointer instance, gconstpchar buf, guint len);
extern "C" TERI_BIS_API void MSCU_CALL_PREFIX teri_bis_wrapper_reload(gpointer instance);
// make reloading if file is modified with period <file_update_period> from <teri_bis_wrapper_set_parameters function>
// if reloading thread is active, returns false
extern "C" TERI_BIS_API gboolean MSCU_CALL_PREFIX teri_bis_wrapper_reload_if_modified(gpointer instance);
// make reloading if file is modified without any period
// if reloading thread is active, returns false
extern "C" TERI_BIS_API gboolean MSCU_CALL_PREFIX teri_bis_wrapper_reload_if_modified_raw(gpointer instance);

extern "C" TERI_BIS_API gboolean MSCU_CALL_PREFIX teri_bis_wrapper_engine_reloading_active(gpointer instance);

extern "C" TERI_BIS_API void MSCU_CALL_PREFIX teri_bis_wrapper_stat_update(gpointer instance, gint level, guint32 id);
extern "C" TERI_BIS_API void MSCU_CALL_PREFIX teri_bis_wrapper_save_stat_sync(gpointer instance);
extern "C" TERI_BIS_API void MSCU_CALL_PREFIX teri_bis_wrapper_save_stat_async(gpointer instance);
extern "C" TERI_BIS_API gboolean MSCU_CALL_PREFIX teri_bis_wrapper_save_stat_if_needed(gpointer instance);
extern "C" TERI_BIS_API gboolean MSCU_CALL_PREFIX teri_bis_wrapper_stat_saving_active(gpointer instance);

#ifndef TTERI_BIS_WRAPPER_STATISTICS_TYPE
#define TTERI_BIS_WRAPPER_STATISTICS_TYPE
STRUCT_PACKED_BEGIN // ������������� ������������ �������� � 1 ����
struct STRUCT_PACKED_ATTRIBUTE Tteri_bis_wrapper_statistics {
  // ���������� ����� ���������
  gint64 reload_ok         ;
  gint64 mod_reload_ok     ; // ��� ����������� ���������

  gint64 reload_bad        ;
  gint64 mod_reload_bad    ; // ��� ����������� ���������

  // ���������� ����������
  gint64 stat_ok           ;
  gint64 mod_stat_ok       ; // ��� ����������� ���������

  gint64 stat_bad          ;
  gint64 mod_stat_bad      ; // ��� ����������� ���������

  // ������������ ���������
  gint64 tokens_stat       ;
  gint64 mod_tokens_stat   ; // ��� ����������� ���������

  gint64 tokens_rdy        ;
  gint64 mod_tokens_rdy    ; // ��� ����������� ���������

  gint64 tokens_zap        ;
  gint64 mod_tokens_zap    ; // ��� ����������� ���������

  gint64 tokens_unk        ;
  gint64 mod_tokens_unk    ; // ��� ����������� ���������
};
STRUCT_PACKED_END // ��������������� ������������ �������� �� ���������
/// ��������� �� ��������� Tteri_bis_wrapper_statistics
typedef Tteri_bis_wrapper_statistics* Pteri_bis_wrapper_statistics;
#endif

extern "C" TERI_BIS_API volatile Tteri_bis_wrapper_statistics * MSCU_CALL_PREFIX teri_bis_wrapper_statistics(gpointer instance);
extern "C" TERI_BIS_API void MSCU_CALL_PREFIX teri_bis_wrapper_statistics_clear(gpointer instance);
//----------------------------------------------------------------------------

// ID EXT field description
//   3                   2                   1                   0
// 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//|CTL| OR_NMBR   |!| RF  |AND_NMB|AND_SIZ|TT_RSRV|      TT       |
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/* ����� ���� ID_EXT */
// ����� Traffic_Type � ������� �����, ������������ ����������� � ������ ���� ������
#define TERI_ID_EXT_TT_HTTP											0x00000001
#define TERI_ID_EXT_TT_FTP											0x00000002
#define TERI_ID_EXT_TT_MAIL											0x00000004
#define TERI_ID_EXT_TT_IM												0x00000008 // instant messaging
#define TERI_ID_EXT_TT_VOIP											0x00000010
#define TERI_ID_EXT_TT_OTH											0x00000020
#define TERI_ID_EXT_TT_AAA											0x00000040
#define TERI_ID_EXT_TT_SOCIAL										0x00000080 // social networks
#define TERI_ID_EXT_TT_RESERVED1								0x00000100 // reserved for future use
#define TERI_ID_EXT_TT_RESERVED2								0x00000200 // reserved for future use
#define TERI_ID_EXT_TT_RESERVED3								0x00000400 // reserved for future use
#define TERI_ID_EXT_TT_RESERVED4								0x00000800 // reserved for future use
// ����������� ��������� �� AND
#define TERI_ID_EXT_SUBSELECT_AND_SIZE_MASK			0x0000f000 // ���������� ���������� ������������ ��������������� ������������ � ��������� ���������� ��������, ������������ � ��� (������������� ����������� � �������� �� �����������, ��� ������������� ������������ �������� ������� ���� ������ ���� �������)
#define TERI_ID_EXT_SUBSELECT_AND_SIZE_SHIFT						12
#define TERI_ID_EXT_SUBSELECT_AND_NUMBER_MASK		0x000f0000 // ���������� ����� ������������� ���������������� ����������� (���� ���� Subselect_AND, ��� ������������� ������������ �������� ������� ���� ������ ���� �������)
#define TERI_ID_EXT_SUBSELECT_AND_NUMBER_SHIFT					16
// ����� Register Flags - ����������� ������ �� ��������
#define TERI_ID_EXT_RF_DECODED									0x00100000 /* ���� ����������� ������ �� �������� (Register Flag) � ���� ��� ������� - �������������� �������������� ������ */
#define TERI_ID_EXT_RF_RAW_MAC									0x00200000 /* ���� ����������� ������ �� �������� (Register Flag) � ���� ��� ������� - �������������� ����� ������ � MAC-������� */
#define TERI_ID_EXT_RF_RAW_IP										0x00400000 /* ���� ����������� ������ �� �������� (Register Flag) � ���� ��� ������� - �������������� ����� IP-������ */
// ���� ���������
#define TERI_ID_EXT_NOT_FLAG										0x00800000 /* ������� ������� ����������� ��������� � ������������� ����������� (���� ���� Subselect_AND) */
// ����������� ��������� �� AND
#define TERI_ID_EXT_SUBSELECT_OR_NUMBER_MASK		0x3f000000 // ���������� ����� ���������� ������������ (����� ���� Subselect_OR), ���������� ����������� ���������� ��������, ������������ � ������������� ���������� ����� (���)
#define TERI_ID_EXT_SUBSELECT_OR_NUMBER_SHIFT						24
// Control � ����� ������ ��������
#define TERI_ID_EXT_CONTROL_MASK								0xc0000000
#define TERI_ID_EXT_CONTROL_SHIFT												30
// Control values, shifted: (v & TERI_ID_EXT_CONTROL_MASK) >> TERI_ID_EXT_CONTROL_SHIFT
#define TERI_ID_EXT_CONTROL_NA												0x00 // �� ��������� (��������������� ��� ������� ���������)
#define TERI_ID_EXT_CONTROL_FULL_SPARE								0x01 // ������ �������� (����� ������������ ��������)
#define TERI_ID_EXT_CONTROL_STAT											0x02 // �������������� ��������
#define TERI_ID_EXT_CONTROL_FULL_SINGLE								0x03 // ������ �������� (����� ����������� ��������)

// define functions
#define TERI_ID_EXT_EXTRACT_CONTROL(id_ext) ((id_ext >> 30) & 0x03)
#define TERI_ID_EXT_EXTRACT_SUBSELECT_OR_NUMBER(id_ext) ((id_ext >> 24) & 0x3f)
#define TERI_ID_EXT_EXTRACT_NOT_FLAG(id_ext) ((id_ext >> 23) & 0x01)
#define TERI_ID_EXT_EXTRACT_SUBSELECT_AND_NUMBER(id_ext) ((id_ext >> 16) & 0xf)
#define TERI_ID_EXT_EXTRACT_SUBSELECT_AND_SIZE(id_ext) ((id_ext >> 12) & 0xf)
#define TERI_ID_EXT_EXTRACT_TRAFFIC_TYPE(id_ext) (id_ext & 0xfff)

#define TERI_ID_EXT_IS_NEGATIVE(id_ext) (((id_ext >> 23) & 0x01) != 0)

#define TERI_ID_EXT_HAS_RF_DECODED(id_ext) (((id_ext) & TERI_ID_EXT_RF_DECODED) != 0)
#define TERI_ID_EXT_HAS_RF_RAW_MAC(id_ext) (((id_ext) & TERI_ID_EXT_RF_RAW_MAC) != 0)
#define TERI_ID_EXT_HAS_RF_RAW_IP(id_ext) (((id_ext) & TERI_ID_EXT_RF_RAW_IP) != 0)
// either raw_ip or raw_mac
#define TERI_ID_EXT_HAS_RF_RAW(id_ext) (TERI_ID_EXT_HAS_RF_RAW_MAC(id_ext) || TERI_ID_EXT_HAS_RF_RAW_IP(id_ext))

#endif
