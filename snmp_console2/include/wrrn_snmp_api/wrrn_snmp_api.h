///
/// wrrn_snmp_api.h : SNMP plugin interface API.
///
/// Changelog:
/// [+] 2017-10-12 - ���������: ��������� ������;
///
/// Copyright (C) MSC, ORG 2017
///

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#ifndef WRRN_SNMP_API_H
#define WRRN_SNMP_API_H

// YOU MUST UNCOMMENT THE LINE BELOW IN CASE OF TYPE MISMATCH
#include <mscu_types.h>
#include <ffsrm.h>
#include <prefs/prefs.h>
#include <swine_api.h>
#include <tcpcat_api.h>

/// �������� ����������
#if MSCU_OS_WINDOWS
#define WRRN_SNMP_LIB_NAME "wrrn_snmp.dll"
#else
#define WRRN_SNMP_LIB_NAME "libwrrn_snmp.so"
#endif

/// \struct TTCPCATStandartFunctions
/// ����� ����������� ������� ��������� ������
/*STRUCT_PACKED_BEGIN*/
struct /*STRUCT_PACKED_ATTRIBUTE */TWRRNSNMPStandartFunctions {
  unsigned int cbSize; ///< ������ ������ ���������
											 /// ��� ������������� ����� ��������� ���������� ��������� ������ ���� �� ��, ��� ������ ������������� ���� ������ ��� �����
											 /// �������� ������� ����, ���� ��������� ������ ������������ ���� �� ������� ���������� ������ ������, ��������
											 /// ��������� ���� cbSize

};
/*STRUCT_PACKED_END*/
/// ��������� �� ��������� TTCPCATStandartFunctions
typedef TWRRNSNMPStandartFunctions* PWRRNSNMPStandartFunctions;

/// \}

/// \defgroup tcpcat_exports �������������� �������
/// \{
/// ������ ������ ��������� ���� �������������� ������� ��� ���������� ������ �������

/// ������� ������������� ������ � ����������� WRRN_SNMP.
///
/// �������������� ���: "wrrn_snmp_init"
///
/// \param WRRNSNMPStandartFunctions - ����� �� ���������, ���������� ������ ����������� ������� ��������� ������.
///   ���������� ��������� �� ���������� ���������� ����� ��������� ����������� ������� (���� ��������� �������������
///     ������ ���� � �������� ��� ����� ����� ��������)
///
/// \param pref_owner - �������� ���� �������� ��� ������� ������
///		������ ������ ���������� ����������� ���������� ���������
///		��� ����������� ���������� ���������� ������������ ������� prefs_XXX (��. prefs.h)
///
/// \return ���������� 0 � ������ ������
/// \return ���� ���������� �� ������ ��������� �����������, ������ ��������� ��������� �������� (��� ������), ����� ������ �������� ����������
///         � ����� ������ ������������� � ������� msculib::klogf ������� ��������� �������� ������
typedef int (MSCU_CALL_PREFIX * Twrrn_snmp_init)(PWRRNSNMPStandartFunctions WRRNSNMPStandartFunctions, preference_p pref_owner, preference_p pref_bool_owner);

/// ���������� �������: ���������� ��� - "wrrn_snmp_perform"
///
/// \param command - ��������
///
/// ���������� ������� (������� �� command)
///  - PERFORM_COMMAND_START - ���������� ��� ������� ������ ������ ���������
///  - PERFORM_COMMAND_STOP - ���������� ��� ���������� ���������� ������ ���������
///  - PERFORM_COMMAND_IDLE - ���� ����������� ������ ����������� ������� ��������� (���������� � ��������, ������ 1 ��� ��� 100 ����)
///  - PERFORM_COMMAND_CLEAN - �������, �������������� ����������� �������� ����������
///
/// \return ���������� 0 � ������ ������
/// \return ����� - ��� ������ (������������� � ������� msculib::klogf ������� ��������� �������� ������)
///
typedef gint (MSCU_CALL_PREFIX * Twrrn_snmp_perform)(gint command);

// ��������, ������������ �������� wrrn_snmp_session_data (��. ��������)
#define SNMP_SESSION_DATA_RESULT_FORWARD 0
#define SNMP_SESSION_DATA_RESULT_DELETE  1
#define SNMP_SESSION_DATA_RESULT_MODIFY  2

/// ��������� ������ ������: ���������� ��� - \b "wrrn_snmp_session_data". <br>
///
/// \param[in] sid - ������������� ������ (������ � �����).
/// \param[in] direction - ����������� �������� ������ (!0 - �� ������� � �������, 0 - �� ������� � �������)
/// \param[in] in_buf, in_len - ������� ����� � �������	(�� ������ ������ ������ ������ �� ����������������� �� ��������� SNMP)
/// \param[out] out_buf, out_len - �������� ����� � �������
///   � ������, ����� �������� ����� �������� ������, ����������, ����� ����� out_buf ��� �������� �� ������� ����
///   �� ���������� ������ wrrn_snmp_session_data � ��������� �������� ������ ����������
///
/// \return ������������ �������� (SNMP_SESSION_DATA_RESULT_XXX)
///   SNMP_SESSION_DATA_RESULT_FORWARD - ������ ��������������� �������� ������
///   SNMP_SESSION_DATA_RESULT_DELETE  - ������ �������� �������� ������
///   SNMP_SESSION_DATA_RESULT_MODIFY  - �������� ������ �� �������� ������ ������� �� ��������� ������
///
typedef int (MSCU_CALL_PREFIX * Twrrn_snmp_session_data)(TCatSID * sid, gboolean direction, const guint8* in_buf, size_t in_len, guint8** out_buf, size_t * out_len);

/// \}

/// @}

// ��� ������������� �������������� ����������������� ��������� ����������� ������ ������ ���������� �������������� ������ � ������ get_version
// � ����� ������ �������� ������ � ���� ������� ��� ������ ������
// ������:
// extern "C" MSCU_HELPER_DLL_EXPORT char * MSCU_CALL_PREFIX get_version()
// {
// #define MSCU_MY_VERSION "2.14.21.2017-09-24"
// 	return MSCU_MY_VERSION;
// }

#endif
