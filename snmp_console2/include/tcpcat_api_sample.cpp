/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/*
 * last update: 2010-05-12
 * 
 * tcpcat_api_sample.cpp : example of tcpcat_api.h usage
 *
 * !��������! ������ ���� �������� ������ �������� ������������� tcpcat_api.h.
 * ����������� ������������� ������ ���� � �������� ������.
 * 
 * Copyright (C) MSC, ORG 2006-2009
 */

#include <tcpcat_api.h>

// Now we use the generic helper definitions above to define XXX_API and XXX_LOCAL.
// XXX_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
// XXX_LOCAL is used for non-api symbols.
#ifdef TCPCAT_API_SAMPLE_EXPORTS // defined if we are building the XXX DLL (instead of using it)
  /// \cond
  #define TCPCAT_API_SAMPLE_API extern "C" MSCU_HELPER_DLL_EXPORT
  /// \endcond
#else
  /// \cond
  #define TCPCAT_API_SAMPLE_API extern "C" MSCU_HELPER_DLL_IMPORT
  /// \endcond
#endif // TCPCAT_API_SAMPLE_EXPORTS
#define TCPCAT_API_SAMPLE_LOCAL MSCU_HELPER_DLL_LOCAL

//////////////////////////////////////////////////////////////////////////
LOCAL_API PTCPCATStandartFunctions _tcpcat = 0; // ���������� ��������� �� ����������� �������
LOCAL_API void* _stuff = 0; // ���������� ��������� �� ������ �������� ����������� �������

//////////////////////////////////////////////////////////////////////////
LOCAL_API gconstpchar MY_NAME = "Dump";
LOCAL_API gconstpchar MY_SHORT_NAME = "DUMP";
LOCAL_API gconstpchar MY_FILTER_NAME = "dump";
LOCAL_API gconstpchar MY_DESCRIPTION =
                  "������, �������������� TCP-������ ��� ��������� ������. "
                  "������������� ������� ��� ��������� � ������, ����� �� �� \"����������\" ������ ������ �������."
                  ;
LOCAL_API gconstpchar MY_VERSION = "0.6";

//////////////////////////////////////////////////////////////////////////
LOCAL_API guint dump_zap_min_len                      = 0; // ����������� �����
LOCAL_API guint dump_zap_max_len                      = 0; // ������������ �����
LOCAL_API gboolean dump_ext_search                    = true; // ����������� ���������
LOCAL_API guint dump_search_hdr_area                  = 2048; // ����������� ������ ������
LOCAL_API gboolean dump_cut_service_header            = true; // ����������� �����

enum {
  FILTER_NONE     = 0, // �� �����������
  FILTER_INCLUDE  = 1, // ��������
  FILTER_EXCLUDE  = 2, // ���������
};

static value_string filter_encap_vals[]  = {
  { FILTER_NONE     , "�����������" },
  { FILTER_INCLUDE  , "�������� � ���������" },
  { FILTER_EXCLUDE  , "��������� �� ���������" },
  { 0               , 0 }
};

gint cfg_filter = FILTER_NONE; // ��� ����������
char cfg_filter_vals[PREFS_MAX_PATH] = "";   // ������ ������

const gint PORTS_SIZE = 0x10000;
const gint PORTS_ARRAY_SIZE = PORTS_SIZE >> 5;
guint32 filter_ports[PORTS_ARRAY_SIZE];

//////////////////////////////////////////////////////////////////////////
class LOCAL_API  TDump {
public:
  TCatSID sid;
};

/* ���������� ����� ������������������� �����
 * port - ����� �����
 * ���� port ������, ������������ true
 */
gboolean dump_tcp_port_find(guint32 port)
{
  port = port & 0xffff;
  return ((filter_ports[port >> 5] >> (port & 0x1f)) & 0x01) != 0;
}

// ������� �������� ��������� ������������� �������� - ������ ������
gconstpchar MSCU_CALL_PREFIX port_validator(preference_p preference, gint action)
{
  static RE2 r_number        ("^\\s*(\\d+)\\s*$", RE2::Latin1);
  static string error = "";
  gconstpchar Result = 0;
  gpchar value = (*_tcpcat->prefs_get_var_string)(preference);

  if (action != vaVerify) 
    fill_n(filter_ports, PORTS_ARRAY_SIZE, 0);

  vector<string> ports;
  mscu_delimited_to_list(string(value), ';', ports);

  gint errors = 0;
  for (vector<string>::iterator sit = ports.begin(); sit != ports.end(); ++sit) {
    if (sit->empty()) {
      ++errors;
      if (action == vaVerify) {
        error = _EN ? "Empty value unacceptable." : "������ �������� �����������.";
        break;
      }
    }
    gint port;
    if (RE2::FullMatch(*sit, r_number, &port)) {
      if ((port < 0) || (port > 0xffff)) {
        ++errors;
        if (action == vaVerify) {
          error = str_format(_EN ? "Value is out of range: %d." : "�������� ������� �� ������� ����������� ���������: %d.", port);
          break;
        }
      }
      filter_ports[port >> 5] |= (guint32)1 << (port & 0x1f);
    } else {
      ++errors;
      if (action == vaVerify) {
        error = str_format(_EN ? "Value is not a number: %s." : "�������� �� �������� ������: %s.", *sit.c_str());
        break;
      }
    }
  }

  if (errors > 0) {
    switch (action) {
    case vaCorrect:
    case vaApply:
      error = "� ��������� ��������� ���������� ������. �������� ������ ��������� ���������� ��� ���������� ������.";
      break;
    case vaVerify: 
      error = str_format("�������� �������� ��������� cfg_filter_vals: %s.", string(value).c_str());
      break;
    }
    Result = error.c_str();
  }

  return Result;
}

//////////////////////////////////////////////////////////////////////////
// �������������� �������
TCPCAT_API_SAMPLE_API gint MSCU_CALL_PREFIX tcpcat_plug_register(PTCPCATStandartFunctions TCPCATStandartFunctions, void * TCPCATStuff, 
                   char * version, char * name, char * short_name, char * filter_name, char * description,
                   char * alt_ports, char * alt_tokens)
{
  gint Result = 0;

  // ���������� ��������� ������
//   assert(sizeof(TTCPCATStandartFunctions) <= TCPCATStandartFunctions->cbSize);
  _tcpcat = TCPCATStandartFunctions;
  _stuff = TCPCATStuff;

  // ������� ���� ����������������� ����������
  strncpy(name       , MY_NAME			, TCPCAT_STR_SIZE);
  strncpy(short_name , MY_SHORT_NAME	, TCPCAT_STR_SIZE);
  strncpy(filter_name, MY_FILTER_NAME	, TCPCAT_STR_SIZE);
  strncpy(description, MY_DESCRIPTION	, TCPCAT_STR_SIZE);
  strncpy(version    , MY_VERSION		, TCPCAT_STR_SIZE);

  return Result;
}

//////////////////////////////////////////////////////////////////////////
// �������������� �������
TCPCAT_API_SAMPLE_API void MSCU_CALL_PREFIX tcpcat_plug_unregister()
{
  //...
}

//////////////////////////////////////////////////////////////////////////
// �������������� �������
TCPCAT_API_SAMPLE_API void MSCU_CALL_PREFIX tcpcat_plug_config_register(preference_p owner)
{
  // ������������ ���������
  prefs_register_uint_preference(owner, 0, 0, 0, "dump_zap_min_len",
    "����������� ������ ������",
    "����������� ������ ������, ����. ���� ������ ����� ��������� ���������� ����, ��� �� ��������������. ������� �� ���������, ���� ������� ������� ��������.",
    &dump_zap_min_len);
  prefs_register_uint_preference(owner, 0, 0, 0, "dump_zap_max_len",
    "������������ ������ ������",
    "������������ ������ ������, ����. ���� ������ ����� ��������� ���������� ����, ��� �� ��������������. ������� �� ���������, ���� ������� ������� ��������.",
    &dump_zap_max_len);

  preference_p pref_filter = prefs_register_enum_preference(owner, 0, 0, 0, "cfg_filter",
    "���������� (TCP-�����)",
    "������ ���������� ������ �� ������� TCP-������. ����� �������� ��� ������� ������� � ������ ���������� ���� �� ������ �������� �� ���� ������� TCP-������. \n"
    "\"�����������\" - �������������� ��� ������. \n"
    "\"�������� � ���������\" - �������������� ������ ������, ������������ �� ������������� ������� ������. \n"
    "\"��������� �� ���������\" - �������������� ��� ������, ����� ������������ �� ������������� ������� ������. \n"
    ,&cfg_filter, (PValueString)filter_encap_vals);
  prefs_register_csv_preference(owner, pref_filter, 0x2 | 0x4, port_validator, "cfg_filter_vals",
    "�����",
    "������ ������, ������������ ��� ����������. �������� � ��������� ����: \"<����1>;<����2>;<����3>...\".\n"
    ,cfg_filter_vals, sizeof(cfg_filter_vals));

  preference_p pref_ext = prefs_register_bool_preference(owner, 0, 0, 0, "dump_ext_search",
    "����������� ���������",
    "����������� ���������.",
    &dump_ext_search);
  prefs_register_uint_preference(owner, pref_ext, 0, 0, "dump_search_hdr_area",
    "������� ������, ����",
    "������ ��������� ������� ������, � ������� ������������ ������������� ����� ��������� ��� ����������� ���� ������.",
    &dump_search_hdr_area);
  prefs_register_bool_preference(owner, pref_ext, 0, 0, "dump_cut_service_header",
    "�������� ��������� ���������",
    "�������� ��������� ���������.",
    &dump_cut_service_header);
}

//////////////////////////////////////////////////////////////////////////
// �������������� �������
TCPCAT_API_SAMPLE_API gpointer MSCU_CALL_PREFIX tcpcat_plug_session_begin(PCatSID sid, gconstpchar buf, int len, gconstpchar buf2, int len2, int * flags)
{
  // ���������� �� ������
  switch (cfg_filter) {
  case FILTER_NONE:
    break; // ���������� ������
  case FILTER_INCLUDE: 
    if (!(dump_tcp_port_find(sid->sport) || dump_tcp_port_find(sid->dport))) 
      return 0;
    break;
  case FILTER_EXCLUDE: 
    if (dump_tcp_port_find(sid->sport) || dump_tcp_port_find(sid->dport))
      return 0;
    break;
  default:
    assert(false);
  }

  // ������� ��� ������
  TDump* Result = new TDump();
  Result->sid = *sid;

  return Result;
}

//////////////////////////////////////////////////////////////////////////
// �������������� �������
TCPCAT_API_SAMPLE_API gint MSCU_CALL_PREFIX tcpcat_plug_session_data(void ** shandle, PCatSessionInfo si, int * flags, gconstpchar buf, int len)
{
  gint Result;

  TDump** dmp = (TDump**)shandle;
  if (*dmp == 0) { // no context
    // ���������� ������� ��� ������
    *dmp = new TDump();
    (*dmp)->sid = si->sid;
  }

  if (len <= 0) { 
    (*_tcpcat->plug_callback_add_message)(_stuff, "������� ����� ����� ������", MT_ERROR);
    return 0;
  } else {
    // ����������� �� �����
    if (((dump_zap_min_len != 0) && (len < gint(dump_zap_min_len))) ||
        ((dump_zap_max_len != 0) && (len > gint(dump_zap_max_len)))) {
       // ������� ��� ������
       delete (*dmp);
       *dmp = 0;
       return TCPCAT_RESULT_DISCARD; // ������� ������ �� ���������
    } else {
      /* !!!���������� ����������!!!
        if (dump_use_match) {
        if ((*_tcpcat->plug_callback_teri_match)(_stuff, &(*dmp)->sid, buf, len) <= 0) {
          // ������� ��� ������
          delete (*dmp);
          *dmp = 0;
          return TCPCAT_RESULT_DISCARD; // ������� ������ �� ���������
        }
      }*/

      gpchar data_type = 0;
      gconstpchar t_buf = buf;
      gint t_len = len;
      gint head_area;
      guint found_pos;

      if (dump_ext_search) {
        if (dump_search_hdr_area == 0) 
          head_area = len;
        else
          head_area = dump_search_hdr_area;
        data_type = (*_tcpcat->enum_file_find)(buf, len, head_area, &found_pos);
        if (data_type != 0) {
          if (*data_type == '.') 
            ++data_type;
          if (dump_cut_service_header) {
            t_buf += found_pos;
            t_len -= found_pos;
          }
        }
      }

      // ������������ ������
      (*_tcpcat->plug_callback_register_data)(_stuff, &(*dmp)->sid,
        *flags, t_buf, t_len,
        data_type,
        0,
        0,
        0  
        );

      // ������� ��� ������
      delete (*dmp);
      *dmp = 0;
      return len; // ���������� ������������ ������
    }
  }
}

//////////////////////////////////////////////////////////////////////////
// �������������� �������
TCPCAT_API_SAMPLE_API void MSCU_CALL_PREFIX tcpcat_plug_session_end(gpointer shandle)
{
  // ������� ��� ������
  TDump* dmp = (TDump*)shandle;
  delete dmp;
}

//////////////////////////////////////////////////////////////////////////
// �������������� �������
TCPCAT_API_SAMPLE_API gboolean MSCU_CALL_PREFIX tcpcat_plug_perform(gint command)
{
  //...
}
