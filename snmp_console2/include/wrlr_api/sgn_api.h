///
/// sgn_api.h : SGN interface API.
///
/// Changelog:
/// [+] 2017-08-30 - ���������: �������	sgn_callback_data_ready_istat_ex � ��������� TSGNStandartFunctions (��.��������);
/// [+] 2017-02-13 - ���������: ��������� SGN_ADD_DATA_FLAG_REQUEST_USER_INFO, SGN_ADD_DATA_FLAG_REQUEST_USER_LOCATION (��.��������);
/// [+] 2017-01-24 - ���������: ����������� �������� ������� wrlr_swine_plugin_init;
/// [+] 2016-10-22 - ���������: ����� ������� ��� ��������� IPv6 � ����������� ���������� ��������� ���������� ������ (��. ������� Tsgn_init_2, Tsgn_set_secondary_token, Tsgn_accept_new_uni_2)
/// [*] 2015-03-03 - ��������: ��������� ���� flags � ������� ���� TSGNDataReadyTV, SGN_AddData_p
///
/// Copyright (C) MSC, ORG 2016-2017
///

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#ifndef SGN_API_H
#define SGN_API_H

// YOU MUST UNCOMMENT THE LINE BELOW IN CASE OF TYPE MISMATCH
#include <mscu_types.h>
#include <ffsrm.h>
#include <prefs/prefs.h>
#include <swine_api.h>

/// �������� ����������
#if MSCU_OS_WINDOWS
#define SGN_LIB_NAME "sgn.dll"
#else
#define SGN_LIB_NAME "libsgn.so"
#endif

/// ��������� ��� ������������� ������ TSGNDataReadyTV::flags
#define SGN_DATA_READY_FLAG_DO_MULTICAST_COPY   0x00000001 // ������������ WRLR, ������ �������� ������ �� �����, ����� �������� ��� �� ���� ��������� SGN-������������
                                                           // � ������ ��������������� WRLR � ������ SGN_ADD_DATA_FLAG_DO_NOT_MULTICAST_COPY

/// ��������� ��� ������������� ������ SGN_AddData_p::flags
#define SGN_ADD_DATA_FLAG_DO_NOT_MULTICAST_COPY 0x00000001 // ��������� SGN-����������� �������� ������ ����� �� ����� � ������ SGN_DATA_READY_FLAG_DO_MULTICAST_COPY
                                                           // ������������, ���� ����� ��� ��� ������� ������ SGN-������������ � ������ SGN_DATA_READY_FLAG_DO_MULTICAST_COPY
                                                           // ������ ���� ��������� ��� �������������� ������������ ����� WRLR
/// ��������� ��� ������������� ������ SGN_AddData_p::flags
#define SGN_ADD_DATA_FLAG_REQUEST_USER_INFO 0x00000002		 // ������� ������� ���������� �� ��������
                                                           // ��������������, ��� ������� ����� �������� ������ ����������� ������� ��������� ����-���� #7 (���� UNI, Ext, Data),
                                                           // �� ����������� ����� �����: UNI-C,TvSec, TvUSec, Length (��. �������� ���������)
/// ��������� ��� ������������� ������ SGN_AddData_p::flags
#define SGN_ADD_DATA_FLAG_REQUEST_USER_LOCATION 0x00000004 // ������� ������� �������� �������������� ��������
                                                           // ��������������, ��� ������� ����� �������� ������ ����������� ������� ��������� ����-���� #8 (���� UNI),
                                                           // �� ����������� ����� �����: UNI-C,TvSec, TvUSec, Length (��. �������� ���������)

//////////////////////////////////////////////////////////////////////////
// ��� ������ ������ ������� �� ��������� AddData: async==false (!async ��� async == 0).
// �� ���� ��������� �������: async==true (async ��� async != 0).
typedef int (MSCU_CALL_PREFIX *Tteri_bis_match_data_sgn)(gint count, gconstpointer* bufs, guint* lens, guint* spots, Tteri_bis_match_callback cb, void *ud, gboolean async);
/// ������� �������� ���������� ������
///
/// data - ����� � ������� ������
///        ���� data = 0, �� ������� ��������� �������������� ����� ������������ �� ui/ui_ext � ��� ������ ����� ����� ������������ �� �����
/// offset - offset to the "left" - size of data link bytes
/// flags - ����� ������, ����� �������� SGN_DATA_READY_FLAG_XXX
///
/// ���������� 0 - � ������ ������, ����� - ��� ������
typedef void (MSCU_CALL_PREFIX *TSGNDataReadyTV)(unsigned char *Data, int LengthOfDataInByte, unsigned int offset, unsigned int uni, unsigned int uni_ext, Ttimeval * tv, guint32 flags);

typedef void (MSCU_CALL_PREFIX *Tdata_ready_istat)(unsigned char *Data, int LengthOfDataInByte);
// istat_type - ������ �������������� ������ (��������� �� swine_api.h):
//   PDT_ISTAT1 - <2�>					
//   PDT_ISTAT2 - <������ 83>	  
//   PDT_ISTAT3 - <��>					
typedef void (MSCU_CALL_PREFIX *Tdata_ready_istat_ex)(unsigned char *Data, int LengthOfDataInByte, int istat_type);

typedef void (MSCU_CALL_PREFIX *TAddFilterControlMessage)(S10G_FILTER_ITEM_STRUCT* filter_item);
typedef void (MSCU_CALL_PREFIX *TSubFilterControlMessage)(S10G_FILTER_ITEM_STRUCT* filter_item);

/// ������ ������� �������� ����������. ����������� "wrlr_init_2" ������ ���.
///
/// �������������� ���: "wrlr_Init"
typedef int (MSCU_CALL_PREFIX *SGN_Init_p)(TSGNDataReadyTV DataReadyTV, Tdata_ready_istat data_ready_istat, Tteri_bis_match_data_sgn teri_bis_match_data_sgn, TAddFilterControlMessage wrapper_add_filter_control_message, TSubFilterControlMessage wrapper_sub_filter_control_message);

/// �������������� ���: "wrlr_Free"
typedef int (MSCU_CALL_PREFIX *SGN_Free_p)(void);

/// ������� ��������� ���������� ������
///
/// �������������� ���: "wrlr_AddData"
///
/// offset - offset to the "left" - size of data link bytes
/// flags - ����� ������, ����� �������� SGN_ADD_DATA_FLAG_XXX
///
/// if IPPacket==0 && Length==0, idle is invoked (���������� � ��������, ������ 1 ��� ��� 100 ����)
///
/// ���������� 0 - � ������ ������, ����� - ��� ������
typedef int (MSCU_CALL_PREFIX *SGN_AddData_p)(unsigned char *IPPacket, int Length, unsigned int offset, Ttimeval * tv, guint32 flags);

/// �������������� ���: "wrlr_PrintState"
typedef int (MSCU_CALL_PREFIX *SGN_PrintState_p)(Tsnapshot_std_function r);

/// find aaa packet by ip - ����� AAA-������, ��������������� �������� � filter_item ip-������� � ���������
/// ����������� AAA-������ �� �������� unis uni-���������
///
/// ������ ������� �������� ����������. ����������� "wrlr_init_2" ������ ���.
///
/// �������������� ���: "wrlr_accept_new_uni"
///
/// filter_item - ���������, ���������� ip-������ (���������� ��������� ��� ip1, ��� � ip2)
/// \param in unis - ������ �������� UNI, � ������� ��������� ����������� �������
/// \param in unis_count - ���������� ��������� � ������� unis
///
typedef int (MSCU_CALL_PREFIX *SGN_accept_new_uni_p)(S10G_FILTER_ITEM_STRUCT* filter_item, guint32* unis, gsize_t unis_count, Ttimeval* tv);

/// �������������� ���: "wrlr_RegisterPrefs"
typedef int (MSCU_CALL_PREFIX *TRegisterPrefs_p)(preference_p owner);

//////////////////////////////////////////////////////////////////////////
// 2016-10-22 new API addons

/// !!!this is modified copy of the type Tplug_callback_srm_set_secondary_token form tcpcat_api.h!!!
/// ���������� ���������� �������� � ���������� ������.
///
/// \param in token_buf - ����� � ������� ��������
/// \param in token_len - ����� ������ � ������� ��������
/// \param in token_spot - �������� ������ \ref teri_bis.h
/// \param in unis - ������ �������� UNI, � ������� ��������� ����������� �������
/// \param in unis_count - ���������� ��������� � ������� unis
///
/// !��������! ������ ������� ����� ������������ ������ ������ ������ plug_session_data.
///
typedef void (MSCU_CALL_PREFIX * Tsgn_callback_srm_set_secondary_token)(gconstpointer token_buf, guint token_len, guint token_spot, guint32 * unis, gsize_t unis_count);

typedef void (MSCU_CALL_PREFIX * Tsgn_callback_add_filter_control_message)(S10G_FILTER_ITEM_STRUCT_2 * filter_item);
typedef void (MSCU_CALL_PREFIX * Tsgn_callback_sub_filter_control_message)(S10G_FILTER_ITEM_STRUCT_2 * filter_item);

/// \struct TSGNStandartFunctions
/// ����� ����������� ������� ��������� ������
struct TSGNStandartFunctions {
  unsigned int cbSize; ///< ������ ������ ���������
											 /// ��� ������������� ����� ��������� ���������� ��������� ������ ���� �� ��, ��� ������ ������������� ���� ������ ��� �����
											 /// �������� ������� ����, ���� ��������� ������ ������������ ���� �� ������� ���������� ������ ������, ��������
											 /// ��������� ���� cbSize

	Tteri_bis_match_data_sgn									sgn_callback_teri_bis_match_data_sgn;
	TSGNDataReadyTV														sgn_callback_data_ready_tv;
	Tdata_ready_istat													sgn_callback_data_ready_istat;
  Tsgn_callback_srm_set_secondary_token			sgn_callback_srm_set_secondary_token;
	Tsgn_callback_add_filter_control_message	sgn_callback_add_filter_control_message;
	Tsgn_callback_sub_filter_control_message	sgn_callback_sub_filter_control_message;
	Tdata_ready_istat_ex											sgn_callback_data_ready_istat_ex;
};
/// ��������� �� ��������� TTCPCATStandartFunctions
typedef TSGNStandartFunctions* PSGNStandartFunctions;

/// ������� ������������� ������ � ����������� SGN.
/// � ������, ���� ������ ������������ ��� ������� ������������� (wrlr_init � wrlr_init_2), �� ������������ ������ ����� ������
///
/// �������������� ���: "wrlr_init_2"
///
/// \param SGNStandartFunctions - ����� �� ���������, ���������� ������ ����������� ������� ��������� ������.
///   ���������� ��������� �� ���������� ���������� ����� ��������� ����������� ������� (���� ��������� �������������
///     ������ ���� � �������� ��� ����� ����� ��������)
///
/// ���������� 0 - � ������ ������, ����� - ��� ������
///
typedef int (MSCU_CALL_PREFIX * Tsgn_init_2)(PSGNStandartFunctions SGNStandartFunctions);

/// ������� ���������� ��������� ��������� � ���������� ������
/// ������� ������� sgn_callback_srm_set_secondary_token � AAA-���������� ��� �������� uni-�������� �� �������� filter_item/tv
///
/// �������������� ���: "wrlr_set_secondary_token"
///
/// \param in filter_item - ���������, ���������� ip-������ (1 ��� 2)
/// \param in tv - TimeStamp
/// \param in unis - ������ �������� UNI, � ������� ��������� ����������� �������
/// \param in unis_count - ���������� ��������� � ������� unis
///
typedef int (MSCU_CALL_PREFIX * Tsgn_set_secondary_token)(S10G_FILTER_ITEM_STRUCT_2 * filter_item, Ttimeval* tv, guint32* unis, gsize_t unis_count);

/// find aaa packet by ip - ����� AAA-������, ��������������� �������� � filter_item ip-������� � ���������
/// ����������� AAA-������ �� �������� unis uni-���������
/// � ������, ���� ������ ������������ ��� ������� (wrlr_accept_new_uni � wrlr_accept_new_uni_2), �� ������������ ������ ����� ������
///
/// �������������� ���: "wrlr_accept_new_uni_2"
///
/// \param in filter_item - ���������, ���������� ip-������
/// \param in tv - TimeStamp
/// \param in unis - ������ �������� UNI, � ������� ��������� ����������� �������
/// \param in unis_count - ���������� ��������� � ������� unis
///
typedef int (MSCU_CALL_PREFIX * Tsgn_accept_new_uni_2)(S10G_FILTER_ITEM_STRUCT_2 * filter_item, Ttimeval* tv, guint32* unis, gsize_t unis_count);

/// 2017-01-24
/// ������� ������������� ������ � ������ swine_api.
///
/// �������������� ���: "wrlr_swine_plugin_init"
/// �������� ������ - ��. swine_api.h
///
///	����������� �������������:
///   �� ������ ������ ����� ���� ������������ ������ �������:
///      plug_proto_register_field_info
///      plug_proto_find_field_info
///   ������������� �������� ������ - ������ ������� wrlr_swine_plugin_init
///   ������ �������� PPluginProtoStuff stuff ������������ (����� ���� ����� 0)
///
typedef void (MSCU_CALL_PREFIX * TPluginInit)(PSWINEStandartFunctions SWINEStuff, gpchar adescription, gpchar aversion);

#endif
