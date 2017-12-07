/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/// \file tcpcat_http_api.h
/// \mainpage
/// @{
/// \section attention ��������������
/// \b ��������! ���� <b>"tcpcat_http_api.h"</b> ���������������� ��� ��������� ������ ������������ ������� �����.
/// ����� ��������� � ������ ����� ���������� �������������� �����������.
/// ��� ������������� ������� ����� ������ �������� ��� � ������ � ������� ��������� #include.
///
/// \section common ����� ���������� � ��������
///   - ������� ������ ���� ��������� � ���� ����������� ����������� ��������� (DLL)
///   - DLL-������ ����� ����� ����� ��� � ���������� ".dll"
///   - DLL-������ ������ ���� ����������� � �������� "<������� EXE-������>\plugins" ���
///       � ��� ������������ ������ ������ ��������
///   - �������, �������������� �����������, ������ ����� �������������� (naked) �����
///   - �������, �������������� �����������, ������ ������������ MSCU_CALL_PREFIX - stdcall (__stdcall) ���������� � ������
///
/// \section changelog ���������
/// - [+] 2016-05-13 - ���������: ��������� raw_buf, raw_len � ������� plug_http_session_data - !������������ � ����������� ��������!
/// - [+] 2016-02-02 - ���������: ������������ �������� TCPCAT_RESULT_ESCAPE_REST (��. ��������)
/// - [*] 2015-07-30 - ��������� Ttcpcat_http_header: ��������� ���� <tv_start>, <tv_stop> - !������������� ������ �� �����������!
/// - [+] 2015-02-17 - ���������: ���� PERFORM_COMMAND_BIND ��� ������� Ttcpcat_plug_http_perform (��. ������������)
/// - [+] 2015-02-17 - ���������: ���� PERFORM_COMMAND_BUILD ��� ������� Ttcpcat_plug_http_perform (��. ������������)
/// - [*] 2014-07-01 - ��������� Ttcpcat_http_header: ��������� ���� <header_index>, <stub_0>, <raw_header_bytes>, <raw_header_size> - !������������� ������ �� �����������!
/// - [*] 2014-02-21 - ��������� Ttcpcat_http_header: ��������� ���� <version>, �������� ����������� ����� <method>, <status_code> - !������������ � ����������� ��������!
/// - [*] 2014-02-04 - ��������: ������ ������ ������� Tplug_callback_is_native_url - �������� ����� �������� proto;
/// - [*] 2014-02-04 - ��������: ������ ��������� natve_urls ������� Tplug_http_register;
/// - [+] 2012-06-15 - ��������� - ������������ �� ������������� �������� PROTOCOL ��������� data_attrs ������� plug_callback_register_data (�������� ������, ����� 5)
/// - [+] 2012-04-02 - ��������� Ttcpcat_http_header: ��������� ���� <referer>
/// - [*] 2012-02-20 - ��������� ��������� TTCPCATHttpStandardFunctions (�������� ��� ������� tcpcat_plug_http_register)
/// - [*] 2012-02-17 - ���������� ����������
/// - [*] 2012-02-16 - ���������� �������������
/// - [*] 2012-02-13 - alpha-������
///
/// \section copyright ��������� �����
/// Copyright (C) MSC, ORG 2006-2016
///
/// @}
#ifndef TCPCAT_PLUG_HTTP_IF_INC
/// \cond
#define TCPCAT_PLUG_HTTP_IF_INC
/// \endcond

#include "mscu_types.h"
#include <limits.h>
#include <prefs/prefs.h>
#include <teri_bis/teri_bis.h>
#include "swine_api.h"
#include "tcpcat_api.h"

/// \page Algorithm �������� ������ ������� ��������
/// @{
///
/// 1. ����� ������� ������ ��������� ���������� "plugins" ��������, ��� ���������� exe-���� (�������
///    �����������), �� ������� ������� dll-������ � ����������� ".dll". ��������� ��������� ����
///    ����������� � � ��� ����������� ������� ������������ �������������� �������
///      - tcpcat_plug_http_register        - ��� \ref Tplug_http_register
///      - tcpcat_plug_http_config_register - ��� \ref Tplug_http_config_register (�� �����������)
///      - tcpcat_plug_http_session_begin   - ��� \ref Tplug_http_session_begin
///      - tcpcat_plug_http_session_data    - ��� \ref Tplug_http_session_data
///      - tcpcat_plug_http_session_end     - ��� \ref Tplug_http_session_end
///      - tcpcat_plug_http_perform         - ��� \ref Ttcpcat_plug_http_perform
///      .
/// �����:
///      ���������� ������� \b tcpcat_plug_http_register. ���� ������� ���������� ������� �������� (�����),
///      ������ ��������� � ������ ��������-������������ �������. � ������ ������� ������ �����������.
///
/// 2. ����� �������� ���� �������� ��� ������� ���������� ������� \b tcpcat_plug_http_config_register, ��������� �������
///    ���������������� ���� ��������� ������ (��������, ����������� � �������� ���������� �������������� ���������� �����������).
///
/// 3. ��� ��������� ���������� ������ ������� (��������� ���������� ������ �������) ��� ������� �� ��������
///    ����� ���� �������� ���������, ������������������ �������� tcpcat_plug_http_config_register
///    ��� ������ ������� ��������� ����������. ������
///    ��������� ���������� ������ ��������� ���������������� (�����������, ���������) ����� ��������.
///    ������ �� ����������� ������� ����������� �� ���, �������� � ��������� ������� �������.
///
/// 4. ����� ������� �������� ���������:
///     - ��� ������� �������-����������� ���������� ������� \b tcpcat_plug_http_perform(PERFORM_COMMAND_START) (��� �������������
///       ���������� ��������).
///
/// 5. ������� ���������.
///     - � �������� ��������� ��� �������� ��������� ������ ���������� ��� ������� ������� ���������� �������
///       \b tcpcat_plug_http_session_begin, ��������� ������� ������� ������������ �������� ��������� ������.
///     - � �������� ���������, ��� ����������� ���������� ������� ��������� HTTP,
///       ���������� ������� \b tcpcat_plug_http_session_data ���� �������� ���������� �������� ������.
///       ������ ������, ��������� ��������, �������� �� TCPCAT_RESULT_ESCAPE, ��������� ������������ ��� �������� ��������� � ��� ������.
///       ���� ������ ���������� TCPCAT_RESULT_ESCAPE_REST, �� �� ������������ �� ��� �������� ��������� � �������, ��� �� ���� ���������
///       � �������� ������ TCP-������
///     - � �������� ���������, ��� ����������� ��������� ������ � ������ ������������� ��������� HTTP,
///       ���������� ������� \b tcpcat_plug_http_session_data ���������������� ������� � ��������������� ���������� ���������.
///       ��������, ������������ ��������, ������������.
///     - � �������� ���������, ��� ���������� ������������ ������, ���������� ������� \b tcpcat_plug_http_session_end
///       ���������������� ������� � ��������������� ���������� ��������� ��� ���������� �������������� ������
///       ��������� � �������� ��������, � ��� ����� � ������ ���������.
///     - � �������� ���������, ����� �������� ������� ������� �����, � ������������
///       �������������� (������� 1 �) ����� ���������� ������� \b tcpcat_plug_http_perform(PERFORM_COMMAND_IDLE), � ������� ������-���������� �����
///       ��������� ������� ��������.
///     - � �������� ��������� ����� ���������� ������� \b tcpcat_plug_http_perform, � ������� ������-���������� ������
///       ��������� ��������� ��������.
///     - � ������� klogf(msculib)  ��� Callback-������� \b plug_callback_add_message ������-���������� ����� ������� ��������� �������
///       ��� ������ ��� �� ����� ������������. ��������� ����� ���� ��������� �����: ���������� (MT_INFORMATION),
///       ������ (MT_ERROR) � �������������� (MT_WARNING).
///     - � ������� Callback-������� \b plug_callback_register_data ������-���������� ����� ���������������� ������������
///       ���� �������� ������. ������ ����� ���� ���������� ����.
///       \b ������������� ������������ ������� PROTOCOL ��������� data_attrs ������� plug_callback_register_data ��� ��������� ���� ���������
///       (������ ��������� �������� �������� short_name ������� plug_http_register + ��� �������������); ��������: "P:HTTP_WEBMAIL__"
///     - \b ��������! ������ �����������, ��� ����� ����� �� �������������� �������� ������� ��� ������� ������� ����� ����������� ���������, �.�.
///       � ���� � ��� �� ������ ������� ����� ����������� ������ ���� ������� (��� �������� ���������)
///
/// 6. ����� ���������� �������� ���������:
///     - ��� ������� �������-����������� ���������� ������� \b tcpcat_plug_http_perform(PERFORM_COMMAND_FLUSH) - ��� "�������" ���������� (� ������������ �������� ������).
///     - ��� ������� �������-����������� ���������� ������� \b tcpcat_plug_http_perform(PERFORM_COMMAND_STOP) - ��� "�������" ����������.
///
/// @}

/// \defgroup Interface ��������� �������-�����������
/// @{

/// \name ���� ����� HTTP-����������
/// \{

#define HTTP_METHOD_HTTP               0
#define HTTP_METHOD_GET                1
#define HTTP_METHOD_POST               2
#define HTTP_METHOD_CONNECT            3
#define HTTP_METHOD_HEAD               4
#define HTTP_METHOD_DELETE             5
#define HTTP_METHOD_PUT                6
#define HTTP_METHOD_TRACE              7
#define HTTP_METHOD_OPTION             8
#define HTTP_METHOD_PATCH              9
#define HTTP_METHOD_LINK              10
#define HTTP_METHOD_PROPFIND          11
#define HTTP_METHOD_PROPPATCH         12
#define HTTP_METHOD_MKCOL             13
#define HTTP_METHOD_COPY              14
#define HTTP_METHOD_MOVE              15
#define HTTP_METHOD_LOCK              16
#define HTTP_METHOD_UNLOCK            17
#define HTTP_METHOD_VERSION_CONTROL   18
#define HTTP_METHOD_CHECKOUT          19
#define HTTP_METHOD_UNCHECKOUT        20
#define HTTP_METHOD_CHECKIN           21
#define HTTP_METHOD_UPDATE            22
#define HTTP_METHOD_LABEL             23
#define HTTP_METHOD_REPORT            24
#define HTTP_METHOD_MKWORKSPACE       25
#define HTTP_METHOD_MKACTIVITY        26
#define HTTP_METHOD_BASELINE_CONTROL  27
#define HTTP_METHOD_MERGE             28

/// \}

/// \name ���� ������ HTTP-�������
/// \{

#define HTTP_VERSION_1_0               0
#define HTTP_VERSION_1_1               1
#define HTTP_VERSION_OTHER             2

/// \}

/// \name HTTP-���������
/// \{

STRUCT_PACKED_BEGIN
struct STRUCT_PACKED_ATTRIBUTE Ttcpcat_http_header {
public:
  guint8 method;        // available values - HTTP_METHOD_XXX constants
  guint8 version;       // HTTP request/response version - HTTP_VERSION_XXX constants
  guint16 status_code;  // status code for the response - 1xx, 2xx, 3xx, 4xx, 5xx
  gpchar status_label;  // for the response - symbol definition right after status code
  gpchar uri;           // ������ ������ �������; ���������� ����������� �� �����
  gpchar url;           // �������� ��� �� ������� /; ���������� ����������� �����
  gpchar urn;           // ��������� ��� + ���������� ����� �� ����� ?; ���������� ����������� �����
  gpchar urn_params;    // ������ ������� ����� ����� ?; ���������� ����������� �����
  gpchar content_type;
  gpchar content_type_raw;
  gpchar set_cookie_raw;
  gpchar cookie_raw;
  gpchar referer;
  gchar ext[PI_CONTENT_SIZE];
  gint64 data_size; // -1 - �� ����������
  gboolean connection_close;
  gboolean content_encoding_gzip;
  gboolean transfer_encoding_chunked;
  gboolean has_content_range;
  gint64 content_range_min;
  gint64 content_range_max;   // -1 means undefined/default value
	gint64 content_range_total;	// -1 means undefined/default value
  // ��������� ��������� ��������� �� ���������:
  //   accept, accept-charset, accept-encoding, accept-language, cache-control, date, expires, if-modified-since, keep-alive, last-modified, pragma, server, user-agent, via
  gsize_t headers_names_count;
  gpchar * headers_names;
  gsize_t headers_values_count;
  gpchar * headers_values;
  guint16 header_index; // absolute index (starting from 0) of the given header within whole transport (TCP) session
  guint16 stub_0;       // stub for byte alignment - for future use
  gpchar raw_header_bytes; // buffer, containing raw HTTP-header
  gsize_t raw_header_size; // size of bytes in buffer
	Ttimeval tv_start; // starting timestamp for corresponding data block
	Ttimeval tv_stop;	 // stopping timestamp for corresponding data block
};
STRUCT_PACKED_END

/// \}

/// \name ��������, ������������ \ref Ttcpcat_http_session_data
/// \{

#define TCPCAT_RESULT_SKIP_NEXT     -2147483646 ///< 0x80000002 - ���������� �� ����� �������� �����
#define TCPCAT_RESULT_FINISH_NEXT   -2147483645 ///< 0x80000003 - ������� �� ����� �������� �����
#define TCPCAT_RESULT_ESCAPE_REST   -2147483644 ///< 0x80000004 - ���������� �� �������� ����� � �� ���� ���������

/// \}

/// \defgroup tcpcat_http_callback ������� ��������� ������
/// \{

/// �������� ���� URL
/// \param stuff - ��������, ������������ ��� ������ ������� \ref Tplug_http_register, � ������������ ������� �������� ������
/// \param url - ��������� ��������� (������ � ����������� �����)
/// \param proto - ���� �������� �� ����� 0, �� �� ����������� � ���� ������������ ����� �� ������ � ����������� �����, ���������� �������� ��������� (���� �������� ���, �� ��������� ������������� ������� �����)
///
/// \return 0, ���� URL �� �������� \"������\" ��� ������ �� ������������������ ��������
/// \return ��������� ��������, ���� URL �������� \"������\" ��� ������ �� ������������������ ��������
///
typedef gboolean (MSCU_CALL_PREFIX * Tplug_callback_is_native_url)(void * stuff, gconstpchar url, gconstpchar * proto);

/// @}

/// \struct TTCPCATHttpStandardFunctions
/// ����� ����������� ������� ��������� ������
STRUCT_PACKED_BEGIN
struct STRUCT_PACKED_ATTRIBUTE TTCPCATHttpStandardFunctions {
  // ������ ���������.
  // ������ �������� ����������� � ��������, ���� ������ ��������� � ��� �� ������, ��� � ����������.
  // �������� ������ �������������� ������� ������� plug_http_register ������ ����� ���:
  //   assert(sizeof(TTCPCATHttpStandardFunctions) <= TCPCATHttpStandardFunctions->cbSize);
  unsigned int cbSize; ///< ������ ������ ���������

  /// \name ������� ������ ����������
  ///@{
  Tplug_callback_is_native_url           plug_callback_is_native_url;
  ///@}
};
/// ��������� �� ��������� TTCPCATHttpStandardunctions
typedef TTCPCATHttpStandardFunctions* PTCPCATHttpStandardFunctions;
STRUCT_PACKED_END

/// \}

/// \defgroup tcpcat_exports �������������� �������
/// \{
/// ������ ������� ��������� ���� �������������� ������� ��� ���������� ������ �������

/// ����������� ������ �����������: ���������� ��� - \b "tcpcat_plug_register". <br>
/// ������� ������ ��������� ��������� ��������� ������ (������ �������� TCPCAT_STR_SIZE)
/// ������������� ���������� (�������� � ����������� �����, ��������, � ������� ������� strncpy):
///   \c version, \c name, \c short_name. \c filter_name, \c description, \c native_urls
/// \param version - ������ ������� (��������, "0.4.1")
/// \param name -        "�������" ��� ���������, ������ �������� ��������
///               ������������ ������ ������, ��������: "HyperText Transfer Protocol"
///               ��������� - �� ���������, ���� ������, ����������, ������ �� 40-60 ��������
/// \param short_name -  "��������" ��� ���������, ������ �������� ��������
///               ������������ ������ ������, ��������: "HTTP"
///               ��������� - �� ���������, ��������� �����, ���������� �����-����� ��������� �������
/// \param filter_name - "����������" ��� ���������, ������ �������� ��������
///               ������������ ������ ������, ��������: "http"
///               ��������� - ������ �������� ����� � ������� �������������, ���������� ����� �������� ������
/// \param description - �������� ������� (��������, "���������� HTTP + WebMail. �������������� ������ HTTP: 1.0, 1.1. ��������� WebMail - mail.ru � ��.")
///               ��������� - �� ���������, �������� ������� �������� ������� � �������� ������ (������������� ��������)
/// \param native_urls - ������ "������" �������� URL, ��������������� ������� ���������
///               ������: <��������>=<��������>;<��������>=<��������>;...<��������>=<��������>, ��������: "id.rambler.ru=wmail_rambler;mail.rambler.ru=wmail_rambler;newmail.rambler.ru=wmail_rambler;vk.com=vk"
///               ���������: ����� � ������� ITF (��. itf_bis.pdf)
///
/// \param TCPCATStandartFunctions - ����� �� ���������, ���������� ������ ����������� ������� ��������� ������ TCPCAT (TTCPCATStandartFunctions).
///   ���������� ��������� �� ���������� ���������� ����� ��������� ����������� ������� (���� ��������� �������������
///     ������ ���� � �������� ��� ����� ����� ��������
///
/// \param TCPCATHttpStandardFunctions - ����� �� ���������, ���������� ������ ����������� ������� ��������� ������ TCPCATHttp (TTCPCATHttpStandardFunctions).
///   ���������� ��������� �� ���������� ���������� ����� ��������� ����������� ������� (���� ��������� �������������
///     ������ ���� � �������� ��� ����� ����� ��������
///
/// \param TCPCATStuff - ������ �������� ��� ����������� ������� ��������� ������ TCPCAT, TCPCATHttp (TTCPCATStandartFunctions, TTCPCATHttpStandardFunctions).
///   ���������� ��������� �� ���������� ���������� � ������������ ��� ������ ����������� ������� ��������� ������
///
/// \return ���������� 0 � ������ ������
/// \return ���� ���������� �� ������ ��������� �����������, ������ ��������� ��������� ��������, ����� ������ �������� ����������
typedef int (MSCU_CALL_PREFIX * Tplug_http_register)(PTCPCATStandartFunctions TCPCATStandartFunctions, PTCPCATHttpStandardFunctions TCPCATHttpStandardFunctions, void * TCPCATStuff,
                                        char * version, char * name, char * short_name, char * filter_name, char * description, char * native_urls);

/// ����������� ���������� ��������� ������: ���������� ��� - \b "tcpcat_plug_config_register". <br>
///
/// \param owner - �������� ���� �������� ��� ������� ������
///
/// \note ��� ����������� ���������� ���������� ������������ ������� prefs_XXX (�������� �����)
///
/// \return ������� �� ���������� ��������
///
typedef void (MSCU_CALL_PREFIX * Tplug_http_config_register)(preference_p owner);

/// �������� ����� ������: ���������� ��� - \b "tcpcat_plug_session_begin". <br>
/// � ������ ������� ������� ������������ ���������������� �������� ��������� ����� ������.
///
/// \param sid - ������������� ����� ������ (������ � �����).
///       ������������� ��������� ������ �������� ���� � ���������� �������������� ����� \ref Tplug_callback_register_data
///       ��������� ��������� TCatSID, �� ������� ��������� ������ ��������, ����������� � ������� ����� ����� ������.
///       ���� ����������� ������������� ������ ��������� �����, ���������� �������� �� ������������ � ������� �������������� �������.
///
/// \return ������������ �������� - �������� ��������� - �������� �������� � ������������ ��� ��� �������� �������� ������� \ref Tplug_http_session_data, \ref Tplug_http_session_end
/// \return ���� ���������� �� ���������� �������� � ������ �������, �� ������ ������� �������� nil (NULL)
///
typedef void * (MSCU_CALL_PREFIX * Tplug_http_session_begin)(TCatSID * sid);

/// ��������� ������ ������: ���������� ��� - \b "tcpcat_plug_session_data". <br>
///
/// \param[in] shandle - ������ �� �������� ��������� (������������ �������� \ref Tplug_session_begin)
/// \param[in] header - HTTP-���������
/// \param[in] prev_header - ���������� HTTP-���������
/// \param[in] buf - ����� � ������� - ���� ������ ������
/// \param[in] len - ����� ������ � �������
/// \param[in] offset - �������� ������ �� ������ buf ������������ HTTP-���������
/// \param[in] more_data - ���� ����, ��� ���� ������ ������ - �� ��������� (�������� ����������� ������ ������ ������� ��� ������� HTTP-���������)
/// \param[in] raw_buf - ����� � ������ ������� - ���� ������ ������ �� ������ ������/�����������
/// \param[in] raw_len - ����� ������ � ������ ������� (�� ������ ������/�����������)
///
/// ������ ������: ����� ������� ��� buf==0, len==0 ��� ���������� ����� more_data ��������, ��� ������ ����������� �� �����������
///   FIN/RST ��� ��������, � �� �� �������� ��������� ������.
/// ������ ������: ����� ������� ��� buf==0, len<0 ��� ������� ����� more_data ��������, ������� ���� ���� ������� ���������
///   � ������ ������ ����� �������� ������ ������ ������� � ������������ ���������, ������ TCPCAT_RESULT_SKIP_ALL ��� (len + TCPCAT_RESULT_SKIP_BASE).
///
/// ������ ������ (HTTP): ����� ������� ��� buf==0, len==0, more_data != 0 �������� ���������� HTTP-���������, �� �������, � ��������� ������, ��������� �������� ����� ������
///
/// \return ������������ �������� (����������� ������ ��� �������� ������ HTTP-��������� ��� ������)
///     - len (������ ���������� ��� ������)
///     - TCPCAT_RESULT_FINISH_NEXT	(-2147483645) (0x80000003 � ���������� ��������)
///					������ ������� �������� ������ �������� HTTP-��������� �� ����� (� ������ �����������???), ����� �������� �� ���������
///     - TCPCAT_RESULT_SKIP_NEXT		(-2147483646) (0x80000002 � ���������� ��������)
///					������ ������� ���������� ������ ��������� HTTP-��������� �� ����� (� ������ �����������???)
///               ������ ������� ����� ������� �� ����� ������ ���� �� ���������� ���������� buf==0, len<0 � ������� ����� more_data, ��� len � ���������� �������� ����� ���������� ���������� ������� ����������� ����
///     - TCPCAT_RESULT_SKIP_ALL		(-2147483647) (0x80000001 � ���������� ��������)
///					������ ������� ���������� ������ ������ �� ����� (� ������ �����������???)
///					������ ������� ����� ������� �� ����� ������ ���� �� ���������� ���������� buf==0, len<0 � ������� ����� more_data, ��� len � ���������� �������� ����� ���������� ���������� ������� ����������� ����
///     - TCPCAT_RESULT_DISCARD			(2147483647)  (0x7fffffff � ���������� ��������)
///					����� �� ���������� ��������� ������ ������
///     - TCPCAT_RESULT_ESCAPE			(2147483646)  (0x7ffffffe � ���������� ��������)
///					����� �� ���������� ��������� ������� HTTP-��������� � ������ ������� �����������
///			- TCPCAT_RESULT_ESCAPE_REST (-2147483644) (0x80000004 � ���������� ��������)
///					����� �� ���������� ��������� ��� �������� HTTP-���������, ��� � ���� ���������� � ��������
///					������ TCP-������ � ������ ������� �����������
///
typedef int (MSCU_CALL_PREFIX * Tplug_http_session_data)(gpointer * shandle, Ttcpcat_http_header * header, Ttcpcat_http_header * prev_header, gconstpchar buf, int len, int offset, gboolean more_data, gconstpchar raw_buf, int raw_len);

/// �������� ������: ���������� ��� - \b "tcpcat_plug_session_end". <br>
/// \param shandle - �������� ��������� (������������ �������� \ref Tplug_session_begin)
///
/// ����������, ����� ���������� ������� �������� ��������� ����������� ������.
/// � ������ ������� ������� ������������ �������������� ���������
/// ������, ���������� ���������� ������ � �.�.
///
typedef void (MSCU_CALL_PREFIX * Tplug_http_session_end)(void * shandle);

/// ������� ���������: ���������� ��� - \b "tcpcat_plug_perform". <br>
///
/// \param command - ��������
///
/// ���������� ������� (������� �� command)
///  - PERFORM_COMMAND_BUILD - ���������� ��� ���������� �������������� ��������� ������������ (����� ������� register_field_info)
///  - PERFORM_COMMAND_BIND - ���������� ��� ���������� ������������ (����� ������� find_field_info)
///  - PERFORM_COMMAND_START - ���������� ��� ������� ������ ������ ���������
///  - PERFORM_COMMAND_STOP - ���������� ��� ���������� ���������� ������ ���������
///  - PERFORM_COMMAND_IDLE - ���� ����������� ������ ����������� ������� ��������� (���������� � ��������, ������ 1 ��� ��� 100 ����)
///  - PERFORM_COMMAND_FLUSH - ���������� ��������� � ������������ �������� ������ ("������" ����������)
///  - PERFORM_COMMAND_SUSPEND - ������������ ���������, �������������� ��������� �����
///  - PERFORM_COMMAND_RESUME - ������������� ���������, ������������� ��������� �����, ����������������� ��� ��������� PERFORM_COMMAND_SUSPEND
///
/// \return ������� ���������� true � ������ �������� ����������, ����� - false (� ����� ������ ���������� � ������� plug_callback_add_message ������� ���������, ����������� ������)
///
typedef gboolean (MSCU_CALL_PREFIX * Ttcpcat_plug_http_perform)(gint command);

/// \}

/// @}

#endif
