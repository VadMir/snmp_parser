/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/*
 * last update: 2010-04-17
 *
 * prefs_sample.cpp : example of prefs.h usage
 *
 * !��������! ������ ���� �������� ������ �������� ������������� prefs.h � ���������� prefs.ddl.
 * ����������� ������������� ������ ���� � �������� ������.
 *
 * Copyright (C) MSC, ORG 2006-2010
 */

#include <prefs/prefs.h>

guint cfg_virtual_avail_percent = 0;
guint current_virtual_avail_percent = 100;

guint cfg_socket_buffer_size = 256*1024*1024;

guint cfg_wpcap_buffer_size = 0;
guint cfg_wpcap_mintocopy_size = 0;

gboolean cfg_use_cps = 0;

guint cfg_trainc_window_size = 16384;
gboolean cfg_trainc_crc_control = false;
gboolean cfg_log_trainc_errors = true;

guint cfg_proto_auto_packet_range = 128;

gboolean cfg_ip_skip_checksum         = false;
gboolean cfg_ip_ignore_bad_checksum   = false;
gboolean cfg_ip_skip_checksum_recalc  = false;
gboolean cfg_tcp_skip_checksum        = false;
gboolean cfg_tcp_ignore_bad_checksum  = false;
gboolean cfg_udp_skip_checksum        = false;
gboolean cfg_udp_ignore_bad_checksum  = false;
guint cfg_ip_frag_time = 1000;  /* fragment lifetime - 1 second */
guint cfg_ip_frag_count = 8192;  /* fragmenters count */

guint cfg_activity_timeout = 1000;
guint cfg_snapshot_period = 600; // �������� � ��������

gboolean cfg_autohide_to_tray = false;

gboolean cfg_log_train_errors = true;

guint cfg_out_pin_buffer_size = 16*1024*1024;

gboolean cfg_mpls_fix_lid = false;
gboolean cfg_dissect_gre = true;
gboolean cfg_dissect_gre_alternative = true;

gboolean cfg_dissect_gtp = true;

gboolean cfg_pid_lid_ignore_pid = false;
gboolean cfg_pid_lid_ignore_lid = false;
guint cfg_pid_lid_buffer_size = 32*1024*1024;
guint cfg_pid_lid_count = 32;
guint cfg_pid_lid_msecs = 0;

gchar cfg_independent_tcp_ports[PREFS_MAX_PATH] = "";
gchar cfg_independent_udp_ports[PREFS_MAX_PATH] = "";
guint32 independent_tcp_ports[PORTS_ARRAY_SIZE];
guint32 independent_udp_ports[PORTS_ARRAY_SIZE];

guint cfg_screensaver_ticks = 300000;

// pins configuration
gpchar cfg_pins_filename_any_filter = "��� ����� (*.*)|*.*";
//////////////////////////////////////////////////////////////////////////
guint cfg_in_pins_count = 0;
gboolean cfg_in_pins_check[PINS_ARRAY_SIZE];

Tprefs_string_array_adapter cfg_in_pins_name(PINS_ARRAY_SIZE, PREFS_MAX_PATH);

value_string cfg_in_pins_src_enum[] = {
  {in_src_type::in_src_net_udp_train,   "UDP - TRAIN"},
  {in_src_type::in_src_net_udp_trainc,  "UDP - TRAINC"},
  {in_src_type::in_src_net_udp_trainm2, "UDP - TRAINM2"},
  {in_src_type::in_src_net_udp_raw,     "UDP - RAW"},

  {in_src_type::in_src_net_tcps_train,  "TCPS - TRAIN"},
  {in_src_type::in_src_net_tcps_trains, "TCPS - TRAINS"},
  {in_src_type::in_src_net_tcps_trainm, "TCPS - TRAINM"},
  {in_src_type::in_src_net_tcps_srm   , "TCPS - SRM"},

  {in_src_type::in_src_net_raws_raw,    "RAW SOCKET - RAW"},
  {in_src_type::in_src_pcap,            "WinPCap/libpcap"},

  {in_src_type::in_src_file_train,      "���� - TRAIN"},
  {in_src_type::in_src_file_trainc,     "���� - TRAINC"},
  {in_src_type::in_src_file_libpcap,    "���� - LIBPCAP"},
  {in_src_type::in_src_file_train32,    "���� - TRAIN32"},
  {in_src_type::in_src_file_trainips32, "���� - TRAINIPS32"},
  {in_src_type::in_src_file_traintm,    "���� - TRAINTM"},
  {in_src_type::in_src_file_pkc,        "���� - PKC"},
  {in_src_type::in_src_file_raw,        "���� - RAW"},
  {0, 0}
};

gint cfg_in_pins_src[PINS_ARRAY_SIZE];

Tprefs_string_array_adapter cfg_in_pins_src_address(PINS_ARRAY_SIZE, PREFS_MAX_PATH);
Tprefs_string_array_adapter cfg_in_pins_src_filename(PINS_ARRAY_SIZE, PREFS_MAX_PATH);
gint cfg_in_pins_src_interface[PINS_ARRAY_SIZE];
guint cfg_in_pins_src_pid[PINS_ARRAY_SIZE];
guint cfg_in_pins_src_lid[PINS_ARRAY_SIZE];
guint cfg_in_pins_src_snap[PINS_ARRAY_SIZE];

value_string cfg_in_pins_set_delay_enum[] = {
  {SPEED_RESTRICTION_NONE,    "���" },
  {SPEED_RESTRICTION_SPEED,   "�� ��������" },
  {SPEED_RESTRICTION_PACKETS, "���������" },
  {SPEED_RESTRICTION_LIBPCAP, "����� LIBPCAP" },
  {0, 0}
};

gint cfg_in_pins_has_set_delay[PINS_ARRAY_SIZE];
guint cfg_in_pins_set_delay_speed[PINS_ARRAY_SIZE];
guint cfg_in_pins_set_delay_packets[PINS_ARRAY_SIZE];
guint cfg_in_pins_set_delay_msecs[PINS_ARRAY_SIZE];

gboolean cfg_in_pins_has_cyclic[PINS_ARRAY_SIZE];

gboolean cfg_in_pins_has_unlink[PINS_ARRAY_SIZE];

value_string cfg_in_pins_payload_enum[] = {
  {CZ_IN_AUTO           , "AUTO"},
  {CZ_IN_DUMMY          , "DUMMY"},
  {CZ_IN_NULL           , "NULL"},
  {CZ_IN_RAW_IP         , "RAWIP"},
  {CZ_IN_ETH            , "ETH"},
  {CZ_IN_CHDLC          , "CHDLC"},
  {CZ_IN_PPP            , "PPP"},
  {CZ_IN_DVB            , "DVB"},
  {CZ_IN_FR             , "FR"},
  {CZ_IN_WLAN           , "WLAN"},
  {CZ_IN_ATM            , "ATM"},
  {CZ_IN_ATM_MSB        , "ATM MSB"},
  {CZ_IN_SATM           , "SATM"},
  {CZ_IN_SATM_MSB       , "SATM MSB"},
  {CZ_IN_SHDLC          , "SHDLC"},
  {CZ_IN_SHDLC_MSB      , "SHDLC MSB"},
  {CZ_IN_SHDLC_OCTET    , "SHDLC OCTET"},
  {CZ_IN_SHDLCM         , "SHDLCM"},
  {CZ_IN_SHDLCM_MSB     , "SHDLCM MSB"},
  {CZ_IN_SPPP_HDLC      , "SPPP HDLC"},
  {CZ_IN_SPPP_HDLC_MSB  , "SPPP HDLC MSB"},
  {CZ_IN_SPPP_HDLC_OCTET, "SPPP HDLC OCTET"},
  {CZ_IN_ATM_AAL5       , "ATM AAL5"},
  {CZ_IN_SRAW_IP        , "SRAWIP"},
  {0, 0}
};

gint cfg_in_pins_payload[PINS_ARRAY_SIZE];
guint cfg_in_pins_payload_wparam[PINS_ARRAY_SIZE];
guint cfg_in_pins_payload_lparam[PINS_ARRAY_SIZE];

gboolean cfg_in_pins_pid_lid_setter_check[PINS_ARRAY_SIZE];

gboolean cfg_in_pins_has_set_pid[PINS_ARRAY_SIZE];
gboolean cfg_in_pins_has_set_lid[PINS_ARRAY_SIZE];
gboolean cfg_in_pins_has_set_pid_mask[PINS_ARRAY_SIZE];
gboolean cfg_in_pins_has_set_lid_mask[PINS_ARRAY_SIZE];
guint cfg_in_pins_set_pid[PINS_ARRAY_SIZE];
guint cfg_in_pins_set_lid[PINS_ARRAY_SIZE];
guint cfg_in_pins_set_pid_mask[PINS_ARRAY_SIZE];
guint cfg_in_pins_set_lid_mask[PINS_ARRAY_SIZE];

gboolean cfg_in_pins_suppress_pid_lid_counting[PINS_ARRAY_SIZE];

gboolean cfg_in_pins_filter_check[PINS_ARRAY_SIZE];

gpchar cfg_in_pins_filter_file_filter = _EN ? "Deflated teri (*.dtf)|*.dtf|Inflated teri (*.itf)|*.itf|All files (*.*)|*.*" : "����������������� ������� (*.dtf)|*.dtf|������������������� ������� (*.itf)|*.itf|��� ����� (*.*)|*.*";

Tprefs_string_array_adapter cfg_in_pins_filter_dvb_mac(PINS_ARRAY_SIZE, PREFS_MAX_PATH);
Tprefs_string_array_adapter cfg_in_pins_filter_dvb_mac_rem(PINS_ARRAY_SIZE, PREFS_MAX_PATH);
Tprefs_string_array_adapter cfg_in_pins_filter_ip(PINS_ARRAY_SIZE, PREFS_MAX_PATH);
Tprefs_string_array_adapter cfg_in_pins_filter_ip_rem(PINS_ARRAY_SIZE, PREFS_MAX_PATH);
Tprefs_string_array_adapter cfg_in_pins_filter_tcp(PINS_ARRAY_SIZE, PREFS_MAX_PATH);
Tprefs_string_array_adapter cfg_in_pins_filter_tcp_rem(PINS_ARRAY_SIZE, PREFS_MAX_PATH);
Tprefs_string_array_adapter cfg_in_pins_filter_ip_tcp(PINS_ARRAY_SIZE, PREFS_MAX_PATH);
Tprefs_string_array_adapter cfg_in_pins_filter_ip_tcp_rem(PINS_ARRAY_SIZE, PREFS_MAX_PATH);
Tprefs_string_array_adapter cfg_in_pins_filter_ip_udp(PINS_ARRAY_SIZE, PREFS_MAX_PATH);
Tprefs_string_array_adapter cfg_in_pins_filter_ip_udp_rem(PINS_ARRAY_SIZE, PREFS_MAX_PATH);
Tprefs_string_array_adapter cfg_in_pins_filter_url_rem(PINS_ARRAY_SIZE, PREFS_MAX_PATH);
Tprefs_string_array_adapter cfg_in_pins_filter_med_rem(PINS_ARRAY_SIZE, PREFS_MAX_PATH);
Tprefs_string_array_adapter cfg_in_pins_filter_session_header_rem(PINS_ARRAY_SIZE, PREFS_MAX_PATH);

guint32 in_pins_filter_tcp_ports[PINS_ARRAY_SIZE][PORTS_ARRAY_SIZE];
guint32 in_pins_filter_tcp_rem_ports[PINS_ARRAY_SIZE][PORTS_ARRAY_SIZE];

//////////////////////////////////////////////////////////////////////////
guint cfg_mux_pins_count = 0;
gboolean cfg_mux_pins_check[PINS_ARRAY_SIZE];

Tprefs_string_array_adapter cfg_mux_pins_name(PINS_ARRAY_SIZE, PREFS_MAX_PATH);

guint cfg_mux_pins_pid[PINS_ARRAY_SIZE];
guint cfg_mux_pins_lid[PINS_ARRAY_SIZE];

gint cfg_mux_pins_payload[PINS_ARRAY_SIZE];
guint cfg_mux_pins_payload_wparam[PINS_ARRAY_SIZE];
guint cfg_mux_pins_payload_lparam[PINS_ARRAY_SIZE];

gboolean cfg_mux_pins_pid_lid_setter_check[PINS_ARRAY_SIZE];

gboolean cfg_mux_pins_has_set_pid[PINS_ARRAY_SIZE];
gboolean cfg_mux_pins_has_set_lid[PINS_ARRAY_SIZE];
gboolean cfg_mux_pins_has_set_pid_mask[PINS_ARRAY_SIZE];
gboolean cfg_mux_pins_has_set_lid_mask[PINS_ARRAY_SIZE];
guint cfg_mux_pins_set_pid[PINS_ARRAY_SIZE];
guint cfg_mux_pins_set_lid[PINS_ARRAY_SIZE];
guint cfg_mux_pins_set_pid_mask[PINS_ARRAY_SIZE];
guint cfg_mux_pins_set_lid_mask[PINS_ARRAY_SIZE];

gboolean cfg_mux_pins_filter_check[PINS_ARRAY_SIZE];

Tprefs_string_array_adapter cfg_mux_pins_filter_dvb_mac(PINS_ARRAY_SIZE, PREFS_MAX_PATH);
Tprefs_string_array_adapter cfg_mux_pins_filter_dvb_mac_rem(PINS_ARRAY_SIZE, PREFS_MAX_PATH);
Tprefs_string_array_adapter cfg_mux_pins_filter_ip(PINS_ARRAY_SIZE, PREFS_MAX_PATH);
Tprefs_string_array_adapter cfg_mux_pins_filter_ip_rem(PINS_ARRAY_SIZE, PREFS_MAX_PATH);
Tprefs_string_array_adapter cfg_mux_pins_filter_tcp(PINS_ARRAY_SIZE, PREFS_MAX_PATH);
Tprefs_string_array_adapter cfg_mux_pins_filter_tcp_rem(PINS_ARRAY_SIZE, PREFS_MAX_PATH);
Tprefs_string_array_adapter cfg_mux_pins_filter_ip_tcp(PINS_ARRAY_SIZE, PREFS_MAX_PATH);
Tprefs_string_array_adapter cfg_mux_pins_filter_ip_tcp_rem(PINS_ARRAY_SIZE, PREFS_MAX_PATH);
Tprefs_string_array_adapter cfg_mux_pins_filter_ip_udp(PINS_ARRAY_SIZE, PREFS_MAX_PATH);
Tprefs_string_array_adapter cfg_mux_pins_filter_ip_udp_rem(PINS_ARRAY_SIZE, PREFS_MAX_PATH);
Tprefs_string_array_adapter cfg_mux_pins_filter_url_rem(PINS_ARRAY_SIZE, PREFS_MAX_PATH);
Tprefs_string_array_adapter cfg_mux_pins_filter_med_rem(PINS_ARRAY_SIZE, PREFS_MAX_PATH);
Tprefs_string_array_adapter cfg_mux_pins_filter_session_header_rem(PINS_ARRAY_SIZE, PREFS_MAX_PATH);

guint32 mux_pins_filter_tcp_ports[PINS_ARRAY_SIZE][PORTS_ARRAY_SIZE];
guint32 mux_pins_filter_tcp_rem_ports[PINS_ARRAY_SIZE][PORTS_ARRAY_SIZE];

//////////////////////////////////////////////////////////////////////////
guint cfg_out_pins_count = 0;
gboolean cfg_out_pins_check[PINS_ARRAY_SIZE];

Tprefs_string_array_adapter cfg_out_pins_name(PINS_ARRAY_SIZE, PREFS_MAX_PATH);

value_string cfg_out_pins_dst_enum[] = {
  {out_dst_type::out_dst_net_udp_train,   "UDP - TRAIN"},
  {out_dst_type::out_dst_net_udp_raw,     "UDP - RAW"},

  {out_dst_type::out_dst_net_tcpc_train,  "TCPC - TRAIN"},
  {out_dst_type::out_dst_net_tcpc_trains, "TCPC - TRAINS"},
  {out_dst_type::out_dst_net_tcpc_trainm, "TCPC - TRAINM"},
  {out_dst_type::out_dst_net_tcpc_srm,    "TCPC - SRM"},
  {out_dst_type::out_dst_net_tcpc_raw,    "TCPC - RAW"},

  {out_dst_type::out_dst_file_train,      "���� - TRAIN"},
  {out_dst_type::out_dst_file_raw,        "���� - RAW"},
  {out_dst_type::out_dst_file_pkc,        "���� - PKC"},
  {out_dst_type::out_dst_file_ipsv2,      "���� - IP_STREAM v2"},
  {out_dst_type::out_dst_file_libpcap,    "���� - LIBPCAP"},

  {out_dst_type::out_dst_null,            "NULL"},
  {out_dst_type::out_dst_callback,        "CALLBACK"},
  {0, 0}
};

gint cfg_out_pins_dst[PINS_ARRAY_SIZE];

Tprefs_string_array_adapter cfg_out_pins_dst_address(PINS_ARRAY_SIZE, PREFS_MAX_PATH);
Tprefs_string_array_adapter cfg_out_pins_dst_filename(PINS_ARRAY_SIZE, PREFS_MAX_PATH);
Tprefs_string_array_adapter cfg_out_pins_dst_filename_addon(PINS_ARRAY_SIZE, PREFS_MAX_PATH);

gboolean cfg_out_pins_has_append[PINS_ARRAY_SIZE];

gint cfg_out_pins_libpcap_payload[PINS_ARRAY_SIZE];

value_string cfg_out_pins_payload_enum[] = {
  {0xFFFF                 , "���������������"},
  {0xFFFF                 , "������"},
  {CZ_OUT_FWD             , "FWD"},
  {CZ_OUT_BLCK            , "BLCK"},
  {CZ_OUT_ALL_IP          , "ALLIP"},
  {CZ_OUT_VPN             , "VPN"},
  {CZ_OUT_VOIP            , "VOIP"},
  {CZ_OUT_SVC             , "SVC"},
  {CZ_OUT_HTTP            , "HTTP"},
  {CZ_OUT_ALL_IP_BUT_HTTP , "NOTHTTP"},
  {CZ_OUT_MAIL            , "MAIL"},
  {CZ_OUT_FTP             , "FTP"},
  {CZ_OUT_OTH_TCP         , "OTHTCP"},
  {CZ_OUT_OTH_UDP         , "OTHUDP"},
  {CZ_OUT_OTH_IP          , "OTHIP"},
  {CZ_OUT_THIN_TCP        , "THINTCP"},
  {CZ_OUT_IPV6            , "IPV6"},
  {CZ_OUT_GRE             , "GRE"},
  {CZ_OUT_IPIP            , "IPIP"},
  {CZ_OUT_UNK             , "UNK"},
  {0, 0}
};

gint cfg_out_pins_payload[PINS_ARRAY_SIZE];
Tprefs_string_array_adapter cfg_out_pins_payload_param(PINS_ARRAY_SIZE, PREFS_MAX_PATH);

gboolean cfg_out_pins_pid_lid_setter_check[PINS_ARRAY_SIZE];

gboolean cfg_out_pins_has_set_pid[PINS_ARRAY_SIZE];
gboolean cfg_out_pins_has_set_lid[PINS_ARRAY_SIZE];
gboolean cfg_out_pins_has_set_pid_mask[PINS_ARRAY_SIZE];
gboolean cfg_out_pins_has_set_lid_mask[PINS_ARRAY_SIZE];
guint cfg_out_pins_set_pid[PINS_ARRAY_SIZE];
guint cfg_out_pins_set_lid[PINS_ARRAY_SIZE];
guint cfg_out_pins_set_pid_mask[PINS_ARRAY_SIZE];
guint cfg_out_pins_set_lid_mask[PINS_ARRAY_SIZE];

gboolean cfg_out_pins_suppress_pid_lid_counting[PINS_ARRAY_SIZE];

gboolean cfg_out_pins_has_buffer_size[PINS_ARRAY_SIZE];
guint cfg_out_pins_buffer_size[PINS_ARRAY_SIZE];

//////////////////////////////////////////////////////////////////////////////
gconstpchar MSCU_CALL_PREFIX pid_lid_count_validator(preference_p preference, gint action)
{
  static string error = "";
  gconstpchar Result = 0;
  guint_p value;
  value = prefs_get_var_uint(preference);

  if (*value < 1) {
    switch (action) {
    case vaCorrect:
    case vaApply:
      error = str(boost::format("�������� �������� ��������� pid_lid_count: %d. ����������� �������� ��-���������.") % *value);
      *value = 32;
      break;
    case vaVerify:
      error = str(boost::format("�������� �������� ��������� pid_lid_count: %d.") % *value);
      break;
    }
    Result = error.c_str();
  }

  return Result;
}

gconstpchar MSCU_CALL_PREFIX container_size_validator(preference_p preference, gint action)
{
  static string error = "";
  gconstpchar Result = 0;
  guint_p value;
  value = prefs_get_var_uint(preference);

  if ((*value < 8) | (*value > 65535) | (*value & 0x3)) {
    switch (action) {
    case vaCorrect:
    case vaApply:
      error = str(boost::format("�������� �������� ��������� container_size: %d. ����������� �������� ��-���������.") % *value);
      *value = 1472;
      break;
    case vaVerify:
      error = str(boost::format("�������� �������� ��������� container_size: %d.") % *value);
      break;
    }
    Result = error.c_str();
  }

  return Result;
}

gconstpchar MSCU_CALL_PREFIX out_pin_buffer_size_validator(preference_p preference, gint action)
{
  static string error = "";
  gconstpchar Result = 0;
  guint_p value;
  value = prefs_get_var_uint(preference);

  if (*value <= 16384) {
    switch (action) {
    case vaCorrect:
    case vaApply:
      error = str(boost::format("�������� �������� ��������� out_pin_buffer_size: %d. ����������� �������� ��-���������.") % *value);
      *value = 16*1024*1024;
      break;
    case vaVerify:
      error = str(boost::format("�������� �������� ��������� out_pin_buffer_size: %d.") % *value);
      break;
    }
    Result = error.c_str();
  }

  return Result;
}

gconstpchar MSCU_CALL_PREFIX pid_lid_buffer_size_validator(preference_p preference, gint action)
{
  static string error = "";
  gconstpchar Result = 0;
  guint_p value;
  value = prefs_get_var_uint(preference);

  if (*value <= 16384) {
    switch (action) {
    case vaCorrect:
    case vaApply:
      error = str(boost::format("�������� �������� ��������� pid_lid_buffer_size: %d. ����������� �������� ��-���������.") % *value);
      *value = 32*1024*1024;
      break;
    case vaVerify:
      error = str(boost::format("�������� �������� ��������� pid_lid_buffer_size: %d.") % *value);
      break;
    }
    Result = error.c_str();
  }

  return Result;
}

gconstpchar MSCU_CALL_PREFIX ip_frag_time_validator(preference_p preference, gint action)
{
  static string error = "";
  gconstpchar Result = 0;
  guint_p value;
  value = prefs_get_var_uint(preference);

  if (*value <= 0) {
    switch (action) {
    case vaCorrect:
    case vaApply:
      error = str(boost::format("�������� �������� ��������� ip_frag_time: %d. ����������� �������� ��-���������.") % *value);
      *value = 1000;
      break;
    case vaVerify:
      error = str(boost::format("�������� �������� ��������� ip_frag_time: %d.") % *value);
      break;
    }
    Result = error.c_str();
  }

  return Result;
}

gconstpchar MSCU_CALL_PREFIX ip_frag_count_validator(preference_p preference, gint action)
{
  static string error = "";
  gconstpchar Result = 0;
  guint_p value;
  value = prefs_get_var_uint(preference);

  if (*value <= 0) {
    switch (action) {
    case vaCorrect:
    case vaApply:
      error = str(boost::format("�������� �������� ��������� ip_frag_count: %d. ����������� �������� ��-���������.") % *value);
      *value = 8192;
      break;
    case vaVerify:
      error = str(boost::format("�������� �������� ��������� ip_frag_count: %d.") % *value);
      break;
    }
    Result = error.c_str();
  }

  return Result;
}

gconstpchar MSCU_CALL_PREFIX independent_tcp_ports_validator(preference_p preference, gint action)
{
  static boost::regex r_number        ("^\\d+$");
  static string error = "";
  gconstpchar Result = 0;
  gpchar value;

  if (action != vaVerify)
    fill_n(independent_tcp_ports, PORTS_ARRAY_SIZE, 0);

  value = prefs_get_var_string(preference);

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
    boost::smatch match; // Do regex match and convert the interesting part to int.
    if (regex_match(*sit, match, r_number)) {
      gint port = mscu_strtoint(match[0]);
      if ((port < 0) || (port > 0xffff)) {
        ++errors;
        if (action == vaVerify) {
          error = str(boost::format(_EN ? "Value is out of range: %d." : "�������� ������� �� ������� ����������� ���������: %d.") % port);
          break;
        }
      }
      independent_tcp_ports[port >> 5] |= (guint32)1 << (port & 0x1f);
    } else {
      ++errors;
      if (action == vaVerify) {
        error = str(boost::format(_EN ? "Value is not a number: %s." : "�������� �� �������� ������: %s.") % *sit);
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
      error = str(boost::format("�������� �������� ��������� independent_tcp_ports: %s.") % (string(value)));
      break;
    }
    Result = error.c_str();
  }

  return Result;
}

gconstpchar MSCU_CALL_PREFIX independent_udp_ports_validator(preference_p preference, gint action)
{
  static boost::regex r_number        ("^\\d+$");
  static string error = "";
  gconstpchar Result = 0;
  gpchar value;

  if (action != vaVerify)
    fill_n(independent_udp_ports, PORTS_ARRAY_SIZE, 0);

  value = prefs_get_var_string(preference);

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
    boost::smatch match; // Do regex match and convert the interesting part to int.
    if (regex_match(*sit, match, r_number)) {
      gint port = mscu_strtoint(match[0]);
      if ((port < 0) || (port > 0xffff)) {
        ++errors;
        if (action == vaVerify) {
          error = str(boost::format(_EN ? "Value is out of range: %d." : "�������� ������� �� ������� ����������� ���������: %d.") % port);
          break;
        }
      }
      independent_udp_ports[port >> 5] |= (guint32)1 << (port & 0x1f);
    } else {
      ++errors;
      if (action == vaVerify) {
        error = str(boost::format(_EN ? "Value is not a number: %s." : "�������� �� �������� ������: %s.") % *sit);
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
      error = str(boost::format("�������� �������� ��������� independent_udp_ports: %s.") % (string(value)));
      break;
    }
    Result = error.c_str();
  }

  return Result;
}

gconstpchar MSCU_CALL_PREFIX tcpcat_http_responses_validator(preference_p preference, gint action)
{
  static boost::regex r_number        ("^\\d+$");
  static string error = "";
  gconstpchar Result = 0;
  gpchar value;

  if (action != vaVerify)
    fill_n(tcpcat_http_responses, tcpcat_http_responses_size, false);

  value = prefs_get_var_string(preference);
  tcpcat_http_responses_enabled = false;

  vector<string> responses;
  mscu_delimited_to_list(string(value), ';', responses);

  gint errors = 0;
  for (vector<string>::iterator sit = responses.begin(); sit != responses.end(); ++sit) {
    if (sit->empty()) {
      ++errors;
      if (action == vaVerify) {
        error = _EN ? "Empty value unacceptable." : "������ �������� �����������.";
        break;
      }
    }
    boost::smatch match; // Do regex match and convert the interesting part to int.
    if (regex_match(*sit, match, r_number)) {
      gint response = mscu_strtoint(match[0]);
      if ((response < 0) || (response > 999)) {
        ++errors;
        if (action == vaVerify) {
          error = str(boost::format(_EN ? "Value is out of range: %d." : "�������� ������� �� ������� ����������� ���������: %d.") % response);
          break;
        }
      }
      tcpcat_http_responses[response] = true;
    } else {
      ++errors;
      if (action == vaVerify) {
        error = str(boost::format(_EN ? "Value is not a number: %s." : "�������� �� �������� ������: %s.") % *sit);
        break;
      }
    }
  }

  if ((action != vaVerify) && responses.size())
    tcpcat_http_responses_enabled = true;

  if (errors > 0) {
    switch (action) {
    case vaCorrect:
    case vaApply:
      error = "� ��������� ��������� ���������� ������. �������� ������ ��������� ���������� ��� ���������� ������.";
      break;
    case vaVerify:
      error = str(boost::format("�������� �������� ��������� tcpcat_http_responses: %s.") % error.c_str());
      break;
    }
    Result = error.c_str();
  }

  return Result;
}

gconstpchar MSCU_CALL_PREFIX in_pins_filter_tcp_ports_validator(preference_p preference, gint action, guint index)
{
  static boost::regex r_number        ("^\\d+$");
  static string error = "";
  gconstpchar Result = 0;
  gpchar value;

  if (action != vaVerify)
    fill_n(in_pins_filter_tcp_ports[index], PORTS_ARRAY_SIZE, 0);

  value = prefs_get_var_string_arr(preference, index);

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
    boost::smatch match; // Do regex match and convert the interesting part to int.
    if (regex_match(*sit, match, r_number)) {
      gint port = mscu_strtoint(match[0]);
      if ((port < 0) || (port > 0xffff)) {
        ++errors;
        if (action == vaVerify) {
          error = str(boost::format(_EN ? "Value is out of range: %d." : "�������� ������� �� ������� ����������� ���������: %d.") % port);
          break;
        }
      }
      in_pins_filter_tcp_ports[index][port >> 5] |= (guint32)1 << (port & 0x1f);
    } else {
      ++errors;
      if (action == vaVerify) {
        error = str(boost::format(_EN ? "Value is not a number: %s." : "�������� �� �������� ������: %s.") % *sit);
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
      error = str(boost::format("�������� �������� ��������� independent_tcp_ports: %s.") % (string(value)));
      break;
    }
    Result = error.c_str();
  }

  return Result;
}

gconstpchar MSCU_CALL_PREFIX in_pins_filter_tcp_rem_ports_validator(preference_p preference, gint action, guint index)
{
  static boost::regex r_number        ("^\\d+$");
  static string error = "";
  gconstpchar Result = 0;
  gpchar value;

  if (action != vaVerify)
    fill_n(in_pins_filter_tcp_rem_ports[index], PORTS_ARRAY_SIZE, false);

  value = prefs_get_var_string_arr(preference, index);

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
    boost::smatch match; // Do regex match and convert the interesting part to int.
    if (regex_match(*sit, match, r_number)) {
      gint port = mscu_strtoint(match[0]);
      if ((port < 0) || (port > 0xffff)) {
        ++errors;
        if (action == vaVerify) {
          error = str(boost::format(_EN ? "Value is out of range: %d." : "�������� ������� �� ������� ����������� ���������: %d.") % port);
          break;
        }
      }
      in_pins_filter_tcp_rem_ports[index][port >> 5] |= (guint32)1 << (port & 0x1f);
    } else {
      ++errors;
      if (action == vaVerify) {
        error = str(boost::format(_EN ? "Value is not a number: %s." : "�������� �� �������� ������: %s.") % *sit);
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
      error = str(boost::format("�������� �������� ��������� independent_tcp_ports: %s.") % (string(value)));
      break;
    }
    Result = error.c_str();
  }

  return Result;
}

gconstpchar MSCU_CALL_PREFIX mux_pins_filter_tcp_ports_validator(preference_p preference, gint action, guint index)
{
  static boost::regex r_number        ("^\\d+$");
  static string error = "";
  gconstpchar Result = 0;
  gpchar value;

  if (action != vaVerify)
    fill_n(mux_pins_filter_tcp_ports[index], PORTS_ARRAY_SIZE, false);

  value = prefs_get_var_string_arr(preference, index);

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
    boost::smatch match; // Do regex match and convert the interesting part to int.
    if (regex_match(*sit, match, r_number)) {
      gint port = mscu_strtoint(match[0]);
      if ((port < 0) || (port > 0xffff)) {
        ++errors;
        if (action == vaVerify) {
          error = str(boost::format(_EN ? "Value is out of range: %d." : "�������� ������� �� ������� ����������� ���������: %d.") % port);
          break;
        }
      }
      mux_pins_filter_tcp_ports[index][port >> 5] |= (guint32)1 << (port & 0x1f);
    } else {
      ++errors;
      if (action == vaVerify) {
        error = str(boost::format(_EN ? "Value is not a number: %s." : "�������� �� �������� ������: %s.") % *sit);
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
      error = str(boost::format("�������� �������� ��������� independent_tcp_ports: %s.") % (string(value)));
      break;
    }
    Result = error.c_str();
  }

  return Result;
}

gconstpchar MSCU_CALL_PREFIX mux_pins_filter_tcp_rem_ports_validator(preference_p preference, gint action, guint index)
{
  static boost::regex r_number        ("^\\d+$");
  static string error = "";
  gconstpchar Result = 0;
  gpchar value;

  if (action != vaVerify)
    fill_n(mux_pins_filter_tcp_rem_ports[index], PORTS_ARRAY_SIZE, false);

  value = prefs_get_var_string_arr(preference, index);

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
    boost::smatch match; // Do regex match and convert the interesting part to int.
    if (regex_match(*sit, match, r_number)) {
      gint port = mscu_strtoint(match[0]);
      if ((port < 0) || (port > 0xffff)) {
        ++errors;
        if (action == vaVerify) {
          error = str(boost::format(_EN ? "Value is out of range: %d." : "�������� ������� �� ������� ����������� ���������: %d.") % port);
          break;
        }
      }
      mux_pins_filter_tcp_rem_ports[index][port >> 5] |= (guint32)1 << (port & 0x1f);
    } else {
      ++errors;
      if (action == vaVerify) {
        error = str(boost::format(_EN ? "Value is not a number: %s." : "�������� �� �������� ������: %s.") % *sit);
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
      error = str(boost::format("�������� �������� ��������� independent_tcp_ports: %s.") % (string(value)));
      break;
    }
    Result = error.c_str();
  }

  return Result;
}

void register_prefs()
{
  preference_p pref_ide = prefs_register_module(0, "ide", "���",
    "������ �������� ��������� ��������� ����� ��������� ��������� ����������."
    , 0, 0);

  prefs_register_msec_preference(pref_ide, 0, 0, 0, "screensaver_ticks",
    _EN ? "Screensaver, ms" : "��������, ��",
    _EN ?
    "Given option defines the time, when elapsed, without any keyboard input, program goes to the screensaver mode. \n"
    "Press any key to return to the common mode. \n"
    "Given in milliseconds. \n"
    "Zero value turns off this function."
    :
    "������ �������� ���������� �����, �� ���������� ��������, � ������� ���������� ����� � ����������, ���������� ��������� � ����� ��������. \n"
    "��������� � ������� ����� ����� ����� ������� ����� �������. \n"
    "�������� � �������������. \n"
    "������� �������� ��������� ��������� ������ �������."
    ,&cfg_screensaver_ticks);

  prefs_register_bool_preference(pref_ide, 0, 0, 0, "autohide_to_tray",
    _EN ? "Hide to tray at start" : "�������� ��� �������",
    _EN ?
    "Automatically hide to system tray at program start."
    :
    "������������� �������� ���������� � ��������� ���� ��� �������."
    ,&cfg_autohide_to_tray);

  prefs_register_uint_preference(pref_ide, 0, 0, 0, "snapshot_period",
    "������ ������ ������ ���������, �",
    "������ ������ ������ ���������, �������� � ��������. "
    "���� ������ ������� ��������, ������ ������ ��������� �� ������������. "
    "���� ������ ��������� ��������, �� � ���� ��������� � ������ �������� ����� ������������ "
    "��������� �������� ��������� (�������������� ���������� ���� ��������)."
    ,&cfg_snapshot_period);

  preference_p pref_common = prefs_register_module(0, "common", "�����",
    "������ �������� ��������� ��������� ����� ��������� ������ ����������."
    , 1, 0);

  prefs_register_uint_preference(pref_common, 0, 0, 0, "virtual_avail_percent",
    "����� ��������� ����������� ������, %",
    "���������� ���������� ������� ��������� ����������� ������ ��������.\n"
    "���� ������� ��������� ����������� ������ �������� ���������� ������ ������� ��������, ���������� �����������.\n"
    "������� �������� ��������� �������� ������� ���������.\n"
    ,&cfg_virtual_avail_percent);

  prefs_register_uint_preference(pref_common, 0, 0, 0, "socket_buffer_size",
    "����� ������, �",
    "������ ������ ��������/������������ �������. "
    "�������� � ������. "
    "������ �������� ��������� ��������� ������������ ������� �� ����� ����������� "
    "����� ������ �� ����. "
    ,&cfg_socket_buffer_size);

  prefs_register_uint_preference(pref_common, 0, 0, 0, "wpcap_buffer_size",
    "WinPCap. ����� ��������, �",
    "������ ������ �������� ��� �������� �������� ����������. "
    "�������� � ������. "
    "������ �������� ������� ��������� � ������ ������ ��� ������ �������.  "
    "������� �������� ������� ��������� �� ���������� ������ ���������� �������� �� ���������, ������� ����� 1 ��. "
    ,&cfg_wpcap_buffer_size);

  prefs_register_uint_preference(pref_common, 0, 0, 0, "wpcap_mintocopy_size",
    "WinPCap. ������������� ������, �",
    "����������� ������ ������ � �������� ������, ��� ������� ������� ������ ������ ����������. "
    "�������� � ������. "
    "������ �������� ������� ��������� � ������ ������� ������������� ����������� ������.  "
    "���� ����� �������� ���������� ����� ��������� ������� �, �������������, ���������� �������� �� ���������. "
    "������� �������� ������� ��������� �� ���������� ������ ���������� �������� �� ���������. "
    ,&cfg_wpcap_mintocopy_size);

  prefs_register_uint_preference(pref_common, 0, 0, container_size_validator, "container_size",
    "���������, �",
    "������ ������������� ����������. "
    "�������� � ������. "
    "������ �������� ��������� ���������� ������ ������ UDP/IP-������� (� ����� TRAIN-"
    "����������� ������ TCP/IP), ������������ �� ����. � ������ ���������������� �������� "
    "(��������, 1Gbit Ethernet) ������������� �������� ������� �������� (��������, 16384). "
    "�������� ��������� ������ ���� � �������� 8..65535, ������ 4. "
    "������������� ��������: 8192. "
    ,&cfg_container_size);

  prefs_register_bool_preference(pref_common, 0, 0, 0, "container_full_flush",
    "��������� - ������ ������",
    "���������� ������ �������������� UDP-������ (������ ���������� � ��������, �������� � ��������� \"���������\"). "
    "��������� ��������: \n"
    " - 0 - ��������� �������� ����������� � �������� ������ ��������� \n"
    " - 1 - ���������� ������ �������������� ���������� \n"
    "������ �������� ��������� ���������� ��������� �������� ������� ��� �������� ������� � ������� \"�������\" �� UDP-������. \n"
    "���� �������� ��������, �������� �������� \"�����������\" �����������. \n"
    "���� �������� �������, �������� �������� ������ �������������� �����������. � ���� ������, ���� ��������� �������� �� ���������, ���������� ����� ���������� ����������� ������. \n"
    ,&cfg_container_full_flush);

  prefs_register_bool_preference(pref_common, 0, 0, 0, "pid_lid_ignore_pid",
    "������������ PID-�������� PID/LID-�����������",
    "������������ ��� ��� PID-�������� PID/LID-�����������. "
    "��������� ��������: \n"
    " - 0 - �� ������������ \n"
    " - 1 - ������������ \n"
    "���� ������ ���� �������, PID/LID-����������� ��������� ������ �� �������� LID. "
    "���� ������ ���� ��������, PID/LID-����������� ��������� �� �������� PID/LID. "
    "!��������! ���� �������� ��� ��������� \"������������ PID-�������� PID/LID-�����������\" � \"������������ LID-�������� PID/LID-�����������\", ������������ ���� ����� PID/LID-���������� � �������������� ������������. "
    ,&cfg_pid_lid_ignore_pid);

  prefs_register_bool_preference(pref_common, 0, 0, 0, "pid_lid_ignore_lid",
    "������������ LID-�������� PID/LID-�����������",
    "������������ ��� ��� LID-�������� PID/LID-�����������. "
    "��������� ��������: \n"
    " - 0 - �� ������������ \n"
    " - 1 - ������������ \n"
    "���� ������ ���� �������, PID/LID-����������� ��������� ������ �� �������� PID. "
    "���� ������ ���� ��������, PID/LID-����������� ��������� �� �������� PID/LID. "
    "!��������! ���� �������� ��� ��������� \"������������ PID-�������� PID/LID-�����������\" � \"������������ LID-�������� PID/LID-�����������\", ������������ ���� ����� PID/LID-���������� � �������������� ������������. "
    ,&cfg_pid_lid_ignore_lid);

  prefs_register_uint_preference(pref_common, 0, 0, pid_lid_buffer_size_validator, "pid_lid_buffer_size",
    "����� PID/LID �����������, �",
    "������ ������ PID/LID - �����������. "
    "�������� � ������. "
    "������ �������� ��������� ��������� ������������ ����������� �� ��������������� "
    "�������� ������� ������ (������ ������ ������ ���� �� ������� ���� �� ������ ������ "
    "������ �� ����� PID/LID-����, �������������� �� 1 �������).�������� ��������� ������ ���� � �������� �� 16K. "
    ,&cfg_pid_lid_buffer_size);

  prefs_register_uint_preference(pref_common, 0, 0, pid_lid_count_validator, "pid_lid_count",
    "���������� PID/LID ������������, ��",
    "������������ ���������� PID/LID-������������. "
    "�������� � ��. "
    "������ �������� ��������� ��������� ������������ ���������� ����������� ����������. "
    "������ ���������� ������������ ���������� ���� PID/LID (��� ������ � ������� "
    "���������� PID/LID). ������ ���������� ������� ����� � ������, �������� "
    "pid_lid_buffer_size. ��������������, ��� ������� ���������� ��� PID/LID, "
    "����������� ������ ����� �� �������. �������������, ���������� ������ ���������� "
    "PID/LID-������������ � ������, ��� ����� ���������� ����������� ������ ����� ����� "
    "pid_lid_count * pid_lid_buffer_size ����. "
    "�������� ��������� �� ������ ���� ����� 0. "
    ,&cfg_pid_lid_count);

  prefs_register_msec_preference(pref_common, 0, 0, 0, "pid_lid_msecs",
    "����� ����� PID/LID ������������, ��",
    "����� ����� PID/LID-������������. "
    "�������� � �������������. "
    "������ �������� ��������� ��������� �������� ���������� PID/LID-������������, "
    "���� �� �������� ����� �� ��������� ������� � ��������������� PID/LID. "
    "������������� �������� ��������, ����������� ����������� ������ ��������, ������������ � ������������ ���������. "
    "������� �������� ��������� �������� ������ ����������������. "
    ,&cfg_pid_lid_msecs);

  prefs_register_uint_preference(pref_common, 0, 0, out_pin_buffer_size_validator, "out_pin_buffer_size",
    "����� ��������� ������, �",
    "������ ������ ��������� ������. "
    "�������� � ������. "
    "������ �������� ��������� ��������� ����������� �������� ������� �� ��������������� "
    "�������� �������������� ������ (������ ������ ������ ���� �� ������� ���� �� "
    "������ ������ ������, �������������� �� 1 �������). "
    "�������� ��������� ������ ���� � �������� �� 16K. "
    ,&cfg_out_pin_buffer_size);

  prefs_register_msec_preference(pref_common, 0, 0, 0, "activity_timeout",
    "����-��� ������, ��",
    "����-��� ������ ������ ��������� ������. "
    "�������� � �������������. "
    "���� �������� ����� ��������� � ������� ������� ������� �������, ��������� � �������� "
    "������ (container_size), �� ���������� ������, ������������� ������������. "
    "���� ������ ������� ��������, �������������� �������� ������ �� ������������. "
    ,&cfg_activity_timeout);

  preference_p pref_control = prefs_register_module(0, "control", "����������",
    "������ �������� ��������� ��������� ��������� ����������."
    , 2, 0);

  prefs_register_bool_preference(pref_control, 0, 0, 0, "use_cps",
    "������� ����������� ���������",
    "������������ ��� ��� �������������� � �������� ����������� ���������. \n"
    "��������� ��������: \n"
    "  - 0 - �� ������������ (��-���������) \n"
    "  - 1 - ������������ \n"
    "���� ������ �������� �������: \n"
    "  - ���������� ��������� ������������ ���������� \"CPSData_1.dll\" (Windows) \n"
    "  - ������������ ���������� ������� SendKeepAliveCPS \n"
    ,&cfg_use_cps);

  preference_p pref_statistics = prefs_register_module(0, "statistics", "����������",
    "������ �������� ��������� ��������� ��������� ����� ����������."
    , 3, 0);

  /*preference_p pref_teri = */prefs_register_module(0, "teri", "�����",
    "������ �������� ��������� ��������� ��������� ������."
    , 4, 0);

  preference_p pref_dissect = prefs_register_module(0, "dissect", "���������",
    "������ �������� ��������� ��������� ��������� ������������ ���������."
    , 5, 0);

    prefs_register_bool_preference(pref_dissect, 0, 0, 0, "log_train_errors",
      "�������� ������ (\"�������\")",
      "�������� � ������ ��������� ��������� �������� ������, ����������� ��� ������ "
      "������� ������ � ������� <�������> ��� ���. "
      "��������� ��������: \n"
      "  - 0 - �� �������� \n"
      "  - 1 - �������� \n"
      "���  ���������� ��������  �  ������� ����������  ������ ��  �����  ����������  ������ "
      "��������� ������������� ���������� �����������. "
      ,&cfg_log_train_errors);

    prefs_register_bool_preference(pref_dissect, 0, 0, 0, "log_trainc_errors",
      "�������� ������ (\"������� �� ���������\")",
      "�������� � ������ ��������� ��������� �������� ������, ����������� ��� ������ "
      "������� ������ � ������� <������� �� ���������> ��� ���. "
      "��������� ��������: \n"
      "  - 0 - �� �������� \n"
      "  - 1 - �������� \n"
      "���  ���������� ��������  �  ������� ����������  ������ ��  �����  ����������  ������ "
      "��������� ������������� ���������� �����������. "
      ,&cfg_log_trainc_errors);

    prefs_register_uint_preference(pref_dissect, 0, 0, 0, "trainc_window_size",
      "���� ������ (\"������� �� ���������\"), ��",
      "�������� � ��. ������ �������� ���������� ���������� �������� �������, ������� ������������� � ���� "
      "������. ��� ���������� ��� ���������� ����������� ������� �� ������ ���������� � "
      "����������� ��������� ��������. "
      ,&cfg_trainc_window_size);

    prefs_register_bool_preference(pref_dissect, 0, 0, 0, "trainc_crc_control",
      "�������� CRC (\"������� �� ���������\")",
      "���� ����� ��������, �� ���������, ��� ����� ������ ������� (����� PID � LID) ��������� 32-������ ��������, ������������ �������� CRC. "
      "��������� �������� ���������� ������� �������� CRC, ����� - ������. "
      "� ����� ������ ������ � ������ CRC �������������. "
      "��������� ��������: \n"
      "  - 0 - �� �������������� \n"
      "  - 1 - �������������� \n"
      ,&cfg_trainc_crc_control);

    prefs_register_uint_preference(pref_dissect, 0, 0, 0, "proto_auto_packet_range",
      "���������� ������� ��� ���������������, ��",
      "���������� ������� ��� ���������������. "
      "�������� � ��. "
      "������ �������� ���������� ���������� �������� �������, �� ��������� ������� ������� "
      "��������������� ����������� ���������� ������ �������� ���������� ��������� ������� "
      "�������� ������ ������. "
      ,&cfg_proto_auto_packet_range);

    prefs_register_bool_preference(pref_dissect, 0, 0, 0, "ip_skip_checksum",
      "�� ��������� ����������� ����� IP-������",
      "���������/�� ��������� ����������� ����� ��������� IP-������. "
      "��������� ��������: \n"
      "  - 0 - ��������� \n"
      "  - 1 - �� ��������� (����������) \n"
      "��� ����������� �������� ������� ��������� ������������ �������� ����������� ����� "
      "��������� IP-������. ���� ����������� ����� ���������� ������ ����������� ��������, "
      "����� ������������� (��� \"ip_ignore_bad_checksum=0\"). ���� � ������ ������ ��� �� "
      "���������� ���������� ��������� ����� �������, ���������� ���������� �������� "
      "��������� ip_skip_checksum � \"1\". "
      ,&cfg_ip_skip_checksum);

    prefs_register_bool_preference(pref_dissect, 0, 0, 0, "ip_ignore_bad_checksum",
      "������������ ����������� ����� IP-������",
      "������������/�� ������������ ������ ����������� ����� ��������� IP-������. "
      "��������� ��������: \n"
      "  - 0 - �� ������������ \n"
      "  - 1 - ������������ \n"
      "��� ����������� �������� ������� ��������� (�������� \"0\") IP-������ � ������ "
      "����������� ������ �������������. ���� �������� ������� (�������� \"1\") , IP-������ � "
      "������ ����������� ������ �� ������������� � ���������� �� ���������� ���������. "
      ,&cfg_ip_ignore_bad_checksum);

    prefs_register_msec_preference(pref_dissect, 0, 0, ip_frag_time_validator, "ip_frag_time",
      "������� ������ ����������������� IP-�������, ��",
      "������� ������ ������ ����������������� IP-�������. "
      "�������� � �������������. "
      "���� � ������� ������� ������� ������� ��� ���������� ����������� IP-������ �� "
      "��������� ����� ��������, ����� ������ ��������� ���������� � ������ ������� IP-������ "
      "������������ (����� ��������). "
      ,&cfg_ip_frag_time);

    prefs_register_uint_preference(pref_dissect, 0, 0, ip_frag_count_validator, "ip_frag_count",
      "���������� ����������������� IP-�������",
      "���������� ������������ ����������������� IP-�������. "
      "������������ ���������� ���������� IP-������� ��� ������ �����������. "
      "���������� ������������ ����� �������� PID:LID. "
      "���� � ������������ ������ ������� ������ ��� ip_frag_count ������� ������ � ��������� "
      "��������� �������� ������ IP-������, ����� �������� �������������. "
      ,&cfg_ip_frag_count);

    prefs_register_bool_preference(pref_dissect, 0, 0, 0, "ip_skip_checksum_recalc",
      "�� ������������� ����������� ����� IP-������",
      "���������� �������������� ����������� ����� ��������� �������������������� IP-������. "
      "��������� ��������: \n"
      "  - 0 - �� ������������ \n"
      "  - 1 - ������������ \n"
      "���� �������� ����� ��������� ��������, ��, ��� �������������� IP-�������, ����������� "
      "����� ����� ������  �� ��������������� � ����������� ������� ��������� (0). ������ "
      "����������� ������������� ��� ���������� ������� ���������. ��� ������� (0) �������� "
      "��������� ����������� ����� ��������������� ��� ������� ���������� IP-������. "
      ,&cfg_ip_skip_checksum_recalc);

    prefs_register_bool_preference(pref_dissect, 0, 0, 0, "tcp_skip_checksum",
      "�� ��������� ����������� ����� TCP-������",
      "���������/�� ��������� ����������� ����� TCP-������. "
      "��������� ��������: \n"
      "  - 0 - ��������� \n"
      "  - 1 - �� ��������� (����������) \n"
      "��� ����������� �������� ������� ��������� ������������ �������� ����������� ����� "
      "TCP-������. ���� ����������� ����� ���������� ������ ����������� ��������, ����� "
      "�������������  (��� \"tcp_ignore_bad_checksum=0\"). ���� � ������ ������ ��� �� "
      "���������� ���������� ��������� ����� �������, ���������� ���������� �������� "
      "��������� tcp_skip_checksum � \"1\". "
      ,&cfg_tcp_skip_checksum);

    prefs_register_bool_preference(pref_dissect, 0, 0, 0, "tcp_ignore_bad_checksum",
      "������������ ����������� ����� TCP-������",
      "������������/�� ������������ ������ ����������� ����� TCP-������. "
      "��������� ��������: \n"
      "  - 0 - �� ������������ \n"
      "  - 1 - ������������ \n"
      "��� ����������� �������� ������� ��������� (�������� \"0\") TCP-������ � ������ "
      "����������� ������ �������������. ���� �������� ������� (�������� \"1\") , TCP-������ � "
      "������ ����������� ������ �� ������������� � ���������� �� ���������� ���������. "
      ,&cfg_tcp_ignore_bad_checksum);

    prefs_register_bool_preference(pref_dissect, 0, 0, 0, "udp_skip_checksum",
      "�� ��������� ����������� ����� UDP-������",
      "���������/�� ��������� ����������� ����� UDP-������. "
      "��������� ��������: \n"
      "  - 0 - ��������� \n"
      "  - 1 - �� ��������� (����������) \n"
      "��� ����������� �������� ������� ��������� ������������ �������� ����������� ����� "
      "UDP-������. ���� ����������� ����� ���������� ������ ����������� ��������, ����� "
      "�������������  (��� \"udp_ignore_bad_checksum=0\"). ���� � ������ ������ ��� �� "
      "���������� ���������� ��������� ����� �������, ���������� ���������� �������� "
      "��������� udp_skip_checksum � \"1\". "
      ,&cfg_udp_skip_checksum);

    prefs_register_bool_preference(pref_dissect, 0, 0, 0, "udp_ignore_bad_checksum",
      "������������ ����������� ����� UDP-������",
      "������������/�� ������������ ������ ����������� ����� UDP-������. "
      "��������� ��������: \n"
      "  - 0 - �� ������������ \n"
      "  - 1 - ������������ \n"
      "��� ����������� �������� ������� ��������� (�������� \"0\") UDP-������ � ������ "
      "����������� ������ �������������. ���� �������� ������� (�������� \"1\") , UDP-������ � "
      "������ ����������� ������ �� ������������� � ���������� �� ���������� ���������. "
      ,&cfg_udp_ignore_bad_checksum);

    prefs_register_bool_preference(pref_dissect, 0, 0, 0, "mpls_fix_lid",
      "��������� LID �� MPLS-������",
      "���������/�� ��������� LID �� MPLS-������. "
      "��������� ��������: \n"
      "  - 0 - �� ������������ \n"
      "  - 1 - ������������ \n"
      "��� ���������� �������� ������� ��������� (1) ��� ������� ��������������� MPLS-"
      "������ ������������ ������� ����������� �������� ����� MPLS-����� �� ������������� "
      "��������� (�������� �� ������ 2). ����������� �������� ������������ MPLS-������ "
      "��������� � ���� LID ������. "
      ,&cfg_mpls_fix_lid);

    preference_p pref_dissect_gre = prefs_register_bool_preference(pref_dissect, 0, 0, 0, "dissect_gre",
      "������������ GRE",
      "���������� ��� ��� ��������� ������� ��������� GRE. "
      "��������� ��������: \n"
      "  - 0 - �� ����������� \n"
      "  - 1 - ����������� \n"
      "��� ���������� �������� ������� ��������� (1) ������������ ��������� ������� ��������� GRE "
      "� ��������� �� ��� ������� ���������� ���������� ������. "
      "� ���� ������ ������ � ������������ IP/GRE/IP ����� ����������� ���� ����� ��� ��������� ���� �������� ��������: "
      "����� ���� ALLIP ����� ��������� ����� IP/GRE/IP, � ����� ����� IP, ���������� �� �������������� ������ IP/GRE/IP."
      ,&cfg_dissect_gre);

    prefs_register_bool_preference(pref_dissect, pref_dissect_gre, 0, 0, "dissect_gre_alternative",
      "������������� ��������� GRE",
      "���������� ��� ��� ������������� ��������� ������� ��������� GRE. "
      "��������� ��������: \n"
      "  - 0 - �� ����������� \n"
      "  - 1 - ����������� \n"
      "��� ���������� �������� ������� ��������� (1) ������������ ��������� ������� ��������� GRE "
      "� ��������� �� ��� ������� ���������� ���������� ������ ������ � ������, ���� ������� IP-����� ������ ���� ������ �� ��������� ������/��������. "
      ,&cfg_dissect_gre_alternative);

    /*preference_p pref_dissect_gtp = */prefs_register_bool_preference(pref_dissect, 0, 0, 0, "dissect_gtp",
      "������������ GTP",
      "���������� ��� ��� ��������� ������� ��������� GTP. "
      "��������� ��������: \n"
      "  - 0 - �� ����������� \n"
      "  - 1 - ����������� \n"
      "��� ���������� �������� ������� ��������� (1) ������������ ��������� ������� ��������� GTP "
      "� ��������� �� ��� ������� ���������� ���������� ������. "
      "� ���� ������ ������ � ������������ IP/GTP/IP ����� ����������� ���� ����� ��� ��������� ���� �������� ��������: "
      "����� ���� ALLIP ����� ��������� ����� IP/GTP/IP, � ����� ����� IP, ���������� �� �������������� ������ IP/GTP/IP."
      ,&cfg_dissect_gtp);

    prefs_register_csv_preference(pref_dissect, 0, 0, independent_tcp_ports_validator, "independent_tcp_ports",
      "����������� TCP-�����",
      "����������� TCP-�����. "
      "��������� ��������: ������ �������������� �������� TCP-������. "
      "������ �������� ���������� ������ TCP-������, �� ������� �� ������ "
      "��������������������� �������� �������. ��� ������ � ������� TCP-������� ����� "
      "������������ �� ���� �������� �������, �������� � ������ ���������������������. "
      ,cfg_independent_tcp_ports, sizeof(cfg_independent_tcp_ports));

    prefs_register_csv_preference(pref_dissect, 0, 0, independent_udp_ports_validator, "independent_udp_ports",
      "����������� UDP-�����",
      "����������� UDP-�����. "
      "��������� ��������: ������ �������������� �������� UDP-������. "
      "������ �������� ���������� ������ UDP-������, �� ������� �� ������ "
      "��������������������� �������� �������. ��� ������ � ������� UDP-������� ����� "
      "������������ �� ���� �������� �������, �������� � ������ ���������������������. "
      ,cfg_independent_udp_ports, sizeof(cfg_independent_udp_ports));

    preference_p pref_dissect_tcpcat = prefs_register_module(pref_dissect, "dissect_tcpcat", "TCP-������",
      "������ �������� ��������� ��������� ��������� �������� TCP-������."
      , 0, 0);

      preference_p pref_dissect_tcpcat_use = prefs_register_bool_preference(pref_dissect_tcpcat, 0, 0, 0, "tcpcat_use_iterator",
        "�������� TCP-������",
        "��������/��������� �������� TCP-������. "
        ,&cfg_tcpcat_use_iterator);

      prefs_register_bool_preference(pref_dissect_tcpcat, pref_dissect_tcpcat_use, 0, 0, "tcpcat_zap_wo_syn",
        "������� ������ ��� SYN (SYN/ACK)",
        "������� ������ ��� ��������� ��� ���. "
        "���������� ��������� ��������� ������ � ������� SYN (SYN/ACK), ������������ �������� ����� TCP-������. "
        "���� ����� ��������� (�� �������������), ��������� ������ ����� ������������ �� ��������� (������ �� ������� ��������). "
        ,&cfg_tcpcat_zap_wo_syn);

      prefs_register_msec_preference(pref_dissect_tcpcat, pref_dissect_tcpcat_use, 0, 0, "tcpcat_activity_time",
        "����� ���������� ���������� ������, ��",
        "�����, �� ��������� �������� ���������� ������ ����������� �������������. "
        "�������� �������� � �������������. "
        "!������� �������� �����������! "
        ,&cfg_tcpcat_activity_time);

      prefs_register_msec_preference(pref_dissect_tcpcat, pref_dissect_tcpcat_use, 0, 0, "tcpcat_idle_granularity",
        "������ ���������� ��������� �������, ��",
        "������ ���������� ��������� �������. "
        "�������� �������� � �������������. "
        "���������� ������������� ��������� ��������� �������� ��������� ������� � ���������� ���������. "
        "!�� ����� ���� ����� 0! "
        ,&cfg_tcpcat_idle_granularity);

      prefs_register_csv_preference(pref_dissect_tcpcat, pref_dissect_tcpcat_use, 0, tcpcat_http_responses_validator, "tcpcat_http_responses",
        "���������� �� ����� HTTP-�������",
        "���������� �� ����� HTTP-�������. "
        "��������� ��������: ������ ����������� �������� ����� HTTP-�������. "
        "������ �������� ���������� ������ ����������� ����� HTTP-�������. ���� ������������ ����� ����������� ���������� �������� 1XX, 2XX, 3XX, 4XX, 5XX. ���� ���������� �������� � ������ HTTP-������ ��������� ����������� ������ (� ����� \"Connection: close\"), �������� �������� �� ������ � ������ ����������� ���������, �� ������ ������ ���������� ��������������� (��� ������ ������ TCP-������ �������������). "
        "������ �������� ����������, ��� ���������� ������������� �� �����. "
        "������������� �������� - \"200;206;302\". "
        ,cfg_tcpcat_http_responses, sizeof(cfg_tcpcat_http_responses));

//////////////////////////////////////////////////////////////////////////
#define FILTER_DESCRIPTION \
      "��������� ���������� �������� ���������� �������������� �������: ����� (DVB MAC-�����), ������� (DVB MAC-�����), ����� (IP-�����), ������� (IP-�����), ����� (IP-�����/TCP-����), ������� (IP-�����/TCP-����), ����� (IP-�����/UDP-����), ������� (IP-�����/UDP-����), ����� (URL), ������� (URL), ����� (Content-���), ������� (Content-���), ������� (��������� �������� � ������ ������) ��������������. \n" \
        "���������� ������: \n" \
        " - *.itf - Inflated Teri Format - �������� � ������������������ ������� \n" \
        " - *.dtf - Deflated Teri Format - �������� � ����������������� ������� \n" \
        "� ������ ����� ������ ����������� �������� � ��������������� ����: \n" \
        " - DVB MAC-����� ���������/��������� (������� ������ - bMD) \n" \
        " - IP-����� ��������� (������� ������ - bIS) \n" \
        " - IP-����� ��������� (������� ������ - bID) \n" \
        " - IP-�����/TCP-���� ��������� (������� ������ - bSTS) \n" \
        " - IP-�����/TCP-���� ��������� (������� ������ - bSTD) \n" \
        " - IP-�����/UDP-���� ��������� (������� ������ - bSUS) \n" \
        " - IP-�����/UDP-���� ��������� (������� ������ - bSUD) \n" \
        " - URL (������� ������ - URL) \n" \
        " - MED (������� ������ - MED - media-���/content-type) \n" \
        " - SESSION HEADER - ��������� ��������, ������������ � ������ ������� ������ - �� ������ ������ � ������ ����������� �������� ������ (������� ������ - T - �����) \n"

  preference_p pref_in_pins = prefs_register_module(0, "in_pins", "�����",
    "������ �������� ��������� ��������� ��������� ������."
    , 6, 0);

    preference_p pref_in_pins_check = prefs_register_bool_preference_arr(pref_in_pins, 0, 0, 0, "in_pins_check",
      "����",
      "������������ ������ ������� ����� ��� ���. "
      "��������� ��������: \n"
      "  - 0 - �� ������������ \n"
      "  - 1 - ������������ \n"
      ,cfg_in_pins_check, PINS_ARRAY_SIZE, &cfg_in_pins_count);

      prefs_register_string_preference_arr(pref_in_pins, pref_in_pins_check, 0, 0, "in_pins_name",
        "���",
        "��� �������� ������. "
        "�������� ��������� �������� � ���� ������ ���������-�������� �������� � ������ ��� ������������� �������� (��������, ��� ���������� ��������� ����� �����). "
        ,cfg_in_pins_name.data, PREFS_MAX_PATH, PINS_ARRAY_SIZE, &cfg_in_pins_count);

      preference_p pref_in_pins_src = prefs_register_enum_preference_arr(pref_in_pins, pref_in_pins_check, 0, 0, "in_pins_src",
        "��������",
        "��������. "
        "�������� ����� ����� ��������� ��������: \n"
        "\n"
        "UDP/TCPS:<ip_address>:<port> TRAIN - ��� ������� ������ - ������� �����������, ����������� ������ � ������� \"�������\". \n"
        "\n"
        "TCPS:<ip_address>:<port> TRAINS - ��� ������� ������ - ������� �����������, ����������� ������ � ���������������� ������� \"�������\". ������� - ��������� ���������� �� ������������. ����� ������� ������������� �� 4 ����. ������ ��� ���������� ��� UDP-����������. \n"
        "\n"
        "UDP:<ip_address>:<port> TRAINC <PID> <LID> - ��� ������� ������ - ������� �����������, ����������� ������ � ���������������� ������� \"�������\" - \"������� �� ���������\". ������� - ������ ���� LID ���������� 16-������ ������� ������, �������� ��� ���������� ������� ������ � ������������ ��������� PID/LID (����������� ������� 16 ��� ���� LID), ������������ ������� ��������� �������. ��� ����������� ������ ������ ����� ������ ������ �������� PID <PID> � LID <LID>. � ������, ���� ����������� ����� ����� ������ ��������, �� ������������� � �������� ��������������� ��������� �� ������.  \n"
        "\n"
        "TCPS:<ip_address>:<port> TRAINM - ��� ������� ������ - ������� �����������, ����������� ������ � ���������������� ������� \"�������\". ������� - ��������� ���������� �� ������������. ����� ������� ������������� �� 4 ����. ���� PID/LID �� ����������� � �������� ���� �����. ������ ��� ���������� ��� UDP-����������. \n"
        "\n"
        "UDP:<ip_address>:<port> TRAINM2 - ��� ������� ������ - ������� �����������, ����������� ������ � ���������������� ������� \"�������\". ������� - ����� ������ PID � LID ����������� ��������� 32-������ ���� (������������). ������ ��� ���������� ��� TCP-����������. \n"
        "\n"
        "\"src=TCPS:<ip_address>:<port> SRM <PID>\" - ��� ������� ������ - ������� �����������, ����������� ������ � ��������� �������: \n"
        "  UNI(4) \n"
        "  Length(4) \n"
        "  TvSec(4) \n"
        "  TvUSec(4) \n"
        "  Length2(4) \n"
        "  Data(Length2) \n"
        " UNI - ������������� �������� ������, �������� ����������� ����� � �������; \n"
        " Length - ����� ������ � ������, ������������ ��������������� �� ������ �����; \n"
        " TvSec - ����� ������ ������, �������� � ��������; \n"
        " TvUSec - ��������� ������� ������ ������, �������� � �������������; \n"
        " Length2 - ����� ������ � ������, ������������ ��������������� �� ������ �����; \n"
        " Data - ������. \n"
        " ����� ������� �� ������������� �� 4 ����. ��� �������� ���� ����� Intel-������� ���� (������� ���� - ������), ������ ����� - 32 ����. ������ ��� ���������� ��� UDP-����������. \n"
        "\n"
        "UDP:<ip_address>:<port> RAW <������_������> <PID> <LID> - ��� ������� ������ - ������� �����������, ����������� ������ � \"�����\" �������. ������ ������� ��������� ������ \"����������\" �� ������ ������ �������� <������_������> (�������� � ������, �� ����� ���� ������ 65536). ���� �������� <������_������> ����� ����, ������ ����������� \"��� ����\". ������� ������ ������������� PID <PID> � LID <LID>. \n"
        "\n"
        "RAWS:<ip_address> RAW <PID> <LID>  - ��� ������� ������ - ������� �����������, ����������� ������ � \"�����\" ������� ����� \"�����\" �����. ������ ����������� ������������� ��� \"������\", �������� ��� IP-������, ������������ �� �������� ����������, � �������� IP-�������. ������������ �������� ��� IP-������ - 127.0.0.1 � 0.0.0.0. ������� ������ ������������� PID <PID> � LID <LID>. \n"
        "\n"
        "���� ������� �����������: \n"
        " - UDP:<ip_address>:<port> - ��� ������� ������ - ������� ����������� �� ���������� IP-������ <ip_address> � UDP-����� <port> (UDP-������ ����������) \n"
        " - TCPS:<ip_address>:<port> - ��� ������� ������ - ������� ����������� �� ���������� IP-������ <ip_address> � TCP-����� <port> (TCP-������ ����������) \n"
        " - RAWS:<ip_address> - ��� ������� ������ - \"�����\" ������� ����������� �� ���������� IP-������ <ip_address> (RAW-�����) \n"
        "\n"
        "<���_�����> TRAIN - ��� ������� ������ - ���� � ������ <���_�����>, ���������� ������ � ������� \"�������\" (������ ������ �� ��������� �� 4 ����). �������� \"<���_�����>\" ����� ��������� ������� ����� \"*\" � \"?\" ��� ������� �� ������, � ������ ������ ��� ������ (��������: \"c:\\in\\*\" - ��� ����� � �������� \"c:\\in\\*\"). \n"
        "\n"
        "<���_�����> TRAINC <PID> <LID> - ��� ������� ������ - ���� � ������ <���_�����>, ���������� ������ � ���������������� ������� \"�������\" (������ ������ �� ��������� �� 4 ����). ������� - ������ ���� LID ���������� 16-������ ������� ������, �������� ��� ���������� ������� ������ � ������������ ��������� PID/LID (����������� ������� 16 ��� ���� LID), ������������ ������� ��������� �������. ��� ����������� ������ ������ ����� ������ ������ �������� PID <PID> � LID <LID>. � ������, ���� ����������� ����� ����� ������ ��������, �� ������������� � �������� ��������������� ��������� �� ������. �������� \"<���_�����>\" ����� ��������� ������� ����� \"*\" � \"?\" ��� ������� �� ������, � ������ ������ ��� ������ (��������: \"c:\\in\\*\" - ��� ����� � �������� \"c:\\in\\*\"). \n"
        "\n"
        "<���_�����> TRAIN32 <PID> <LID> - ��� ������� ������ - ���� � ������ <���_�����>, ���������� ������ � �������: <�����_������_32����><������>..<�����_������_32����><������>. ������� ������ ������������� PID <PID> � LID <LID>. �������� \"<���_�����>\" ����� ��������� ������� ����� \"*\" � \"?\" ��� ������� �� ������, � ������ ������ ��� ������ (��������: \"c:\\in\\*\" - ��� ����� � �������� \"c:\\in\\*\"). \n"
        "\n"
        "<���_�����> TRAINIPS32 <PID> <LID> - ��� ������� ������ - ���� � ������ <���_�����>, ���������� ������ � �������: <�����_������_32����><������>..<�����_������_32����><������>. ������ 9 ���� ����� ������ ��������� \"����������\" ����� ���� - \"IP_STREAM\". ������� ������ ������������� PID <PID> � LID <LID>. �������� \"<���_�����>\" ����� ��������� ������� ����� \"*\" � \"?\" ��� ������� �� ������, � ������ ������ ��� ������ (��������: \"c:\\in\\*\" - ��� ����� � �������� \"c:\\in\\*\"). \n"
        "\n"
        "<���_�����> LIBPCAP <PID> <LID> - ��� ������� ������ - ���� � ������ <���_�����>, ���������� ������ � �������: LibPCap/TCPDump/Wireshark. ������� ������ ������������� PID <PID> � LID <LID>. ��� ��������, ��������� � ��������� �����, �� ������������. �������� \"<���_�����>\" ����� ��������� ������� ����� \"*\" � \"?\" ��� ������� �� ������, � ������ ������ ��� ������ (��������: \"c:\\in\\*\" - ��� ����� � �������� \"c:\\in\\*\"). \n"
        "\n"
        "<���_�����> TRAINTM <PID> <LID> - ��� ������� ������ - ���� � ������ <���_�����>, ���������� ������ � �������: <���������_�����_32����><IP-�����>..<���������_�����_32����><IP-�����>. ������� ������ ������������� PID <PID> � LID <LID>. �������� \"<���_�����>\" ����� ��������� ������� ����� \"*\" � \"?\" ��� ������� �� ������, � ������ ������ ��� ������ (��������: \"c:\\in\\*\" - ��� ����� � �������� \"c:\\in\\*\"). \n"
        "\n"
        "<���_�����> RAW <������_������> <PID> <LID>  - ��� ������� ������ - ���� � ������ <���_�����>, ���������� ������ � \"�����\" �������. ������ ����� \"����������\" �� ������ ������ �������� <������_������> (�������� � ������).  �������� <������_������> �� ����� ���� ����� ����, �� ����� ���� ������ 65536. ������� ������ ������������� PID <PID> � LID <LID>. �������� \"<���_�����>\" ����� ��������� ������� ����� \"*\" � \"?\" ��� ������� �� ������, � ������ ������ ��� ������ (��������: \"c:\\in\\*\" - ��� ����� � �������� \"c:\\in\\*\"). \n"
        "\n"
        "<���_�����> PKC <PID> <LID> - ��� ������� ������ - ���� � ������ <���_�����>, ���������� ������ � �������: \"PKC\". ������� ������ ������������� PID <PID> � LID <LID>. �������� \"<���_�����>\" ����� ��������� ������� ����� \"*\" � \"?\" ��� ������� �� ������, � ������ ������ ��� ������ (��������: \"c:\\in\\*\" - ��� ����� � �������� \"c:\\in\\*\"). \n"
        "  ������ ������: \n"
        "    5B 5D XX XX 0D 0A ����� \n"
        "    ��� XX XX ���������� ���� ��������� �� ���� (����� ������ + 2 �����). \n"
        "\n"
        "PCAP<iface> RAW <PID> <LID>  - ��� ������� ������ - ������ ������� �������� ���������� ����������� WinPCap (������ ���� ���������� � �������). ������ ����������� ������������� ��� \"������\", �������� ��� ������, ������������ �� �������� ���������� (���������� � �������������� ����). ������� ������ ������������� PID <PID> � LID <LID>. \n"
        "\n"
        ,cfg_in_pins_src, cfg_in_pins_src_enum, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_string_preference_arr(pref_in_pins, pref_in_pins_src,
          1 << in_src_type::in_src_net_udp_train | 1 << in_src_type::in_src_net_udp_trainc | 1 << in_src_type::in_src_net_udp_trainm2 | 1 << in_src_type::in_src_net_udp_raw |
          1 << in_src_type::in_src_net_tcps_train | 1 << in_src_type::in_src_net_tcps_trains | 1 << in_src_type::in_src_net_tcps_trainm |
          1 << in_src_type::in_src_net_tcps_srm | 1 << in_src_type::in_src_net_raws_raw,
          0, "in_pins_src_address",
          "�����",
          "�����. "
          "�������� ������� ��������� ������������ ��� ��������� ��������� ����� ���������� (<ip_address>:<port>)."
          ,cfg_in_pins_src_address.data, PREFS_MAX_PATH, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_enum_preference_arr(pref_in_pins, pref_in_pins_src,
          1 << in_src_type::in_src_pcap,
          0, "in_pins_src_interface",
          "���������",
          "���������. "
          "�������� ������� ��������� ������������ ��� ��������� ��������� ����� ����������."
          ,cfg_in_pins_src_interface, wpcap_wrapper.interfaces_enum, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_file_preference_arr(pref_in_pins, pref_in_pins_src,
          1 << in_src_type::in_src_file_train | 1 << in_src_type::in_src_file_trainc | 1 << in_src_type::in_src_file_libpcap |
          1 << in_src_type::in_src_file_train32 | 1 << in_src_type::in_src_file_trainips32 | 1 << in_src_type::in_src_file_traintm |
          1 << in_src_type::in_src_file_raw | 1 << in_src_type::in_src_file_pkc,
          0, "in_pins_src_filename",
          "����",
          "��� �����. "
          "�������� ������� ��������� ������������ ��� ��������� ��������� ����� ���������� (<���_�����>)."
          ,cfg_in_pins_src_filename.data, PREFS_MAX_PATH, cfg_pins_filename_any_filter, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_uint_preference_arr(pref_in_pins, pref_in_pins_src,
          1 << in_src_type::in_src_net_udp_trainc | 1 << in_src_type::in_src_net_udp_raw | 1 << in_src_type::in_src_net_raws_raw |
          1 << in_src_type::in_src_file_trainc | 1 << in_src_type::in_src_file_libpcap | 1 << in_src_type::in_src_file_train32 |
          1 << in_src_type::in_src_file_trainips32 | 1 << in_src_type::in_src_file_traintm | 1 << in_src_type::in_src_file_raw |
          1 << in_src_type::in_src_net_tcps_srm | 1 << in_src_type::in_src_pcap | 1 << in_src_type::in_src_file_pkc,
          0, "in_pins_src_pid",
          "PID",
          "PID. "
          "�������� ������� ��������� ������������ ��� ��������� ��������� ����� ���������� (<PID>)."
          ,cfg_in_pins_src_pid, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_uint_preference_arr(pref_in_pins, pref_in_pins_src,
          1 << in_src_type::in_src_net_udp_trainc | 1 << in_src_type::in_src_net_udp_raw | 1 << in_src_type::in_src_net_raws_raw |
          1 << in_src_type::in_src_file_trainc | 1 << in_src_type::in_src_file_libpcap | 1 << in_src_type::in_src_file_train32 |
          1 << in_src_type::in_src_file_trainips32 | 1 << in_src_type::in_src_file_traintm | 1 << in_src_type::in_src_file_raw |
          /*1 << in_src_type::in_src_net_tcps_srm | */1 << in_src_type::in_src_pcap | 1 << in_src_type::in_src_file_pkc,
          0, "in_pins_src_lid",
          "LID",
          "LID. "
          "�������� ������� ��������� ������������ ��� ��������� ��������� ����� ���������� (<LID>)."
          ,cfg_in_pins_src_lid, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_uint_preference_arr(pref_in_pins, pref_in_pins_src,
          1 << in_src_type::in_src_net_udp_raw | 1 << in_src_type::in_src_file_raw,
          0, "in_pins_src_snap",
          "����� �����",
          "����� �����. "
          "�������� ������� ��������� ������������ ��� ��������� ��������� ����� ���������� (<������_������>)."
          ,cfg_in_pins_src_snap, PINS_ARRAY_SIZE, &cfg_in_pins_count);

      preference_p pref_in_pins_payload = prefs_register_enum_preference_arr(pref_in_pins, pref_in_pins_check, 0, 0, "in_pins_payload",
        "��� ��������",
        "��� ��������. "
        "�������� ���������� ��� ���������� ������ ����������� ������. \n"
        "�������� ���� ������: \n"
        " - AUTO - �������������� ����������� ���� �������� (���������� ������);\n"
        " - DUMMY - ��������� ������ �� ������������ (������ ��������������� �� ������);\n"
        " - NULL - ��������� ������� �� ������������, ��� ������ ���������� ��� \"UNK - ����������� ������\";\n"
        " - RAWIP <����� ���������> <����� ���������> - ����������� \"���������\" �������. ������������ ��������� ������ � ����� ������ (���������� ���������� ���� �������� ����� �������������� �������� ��������� <����� ���������> <����� ���������>), ���������� ����� ��������� IP-������� � ������������ ��� ���������. ���� �������� <����� ���������> �������������, ������������ ����� ������ ��������� IP-������ � ��������� � �������� (0) ����� �� ���������� ������������� �������� ��������� <����� ���������>;\n"
        " - ETH - ����� � ��������� Ethernet-������ (��� ����������� �����);\n"
        " - CHDLC - ����� � ��������� ������� Cisco HDLC � ���������� � ����������� ������;\n"
        " - PPP - ����� � ��������� PPP-������� � ���������� � ����������� ������;\n"
        " - DVB - ����� � ��������� DVB MPEG-TS ������;\n"
        " - FR - ����� � ��������� FR-������ � ���������� � ����������� ������;\n"
        " - WLAN - ����� � ��������� IEEE 802.11-������ (��� ����������� �����);\n"
        " - ATM [MSB] - ����� � ��������� ����� ATM, ������ ������� AAL 5, ��������� ��������. ���� ����� �������������� �������� MSB, ������������ �������� ��� � ������ �������� ������;\n"
        " - SATM [MSB] - ����� � ��������� ����� ATM � ������, ������ ������� AAL 5, ��������� ��������. ���� ����� �������������� �������� MSB, ������������ �������� ��� � ������ �������� ������. ������� �� ATM ����������� � ���, ��� ������������ �������������� ������������� �� ������������ ��������� � HEC;\n"
        " - SHDLC [MSB|OCTET] <����� ���������> <����� ���������> - ������ ������� ��������� HDLC, ��������� IP-������� ��� ��, ��� � � ���� RAWIP (��. ����). ��������! �������� ������ ������� ��������� HDLC ���������� �������� 6 �����/� �� ����������� ������ Intel(TM) Core(TM)2, 2 ���. ���������� ��������� ������ ���� ��� ��������� ������� ������� ��������; \n"
        " - SHDLCM [MSB|OCTET] <����� ���������> <����� ���������> - ������ ������� ��������� HDLC-M, ��������� IP-������� ��� ��, ��� � � ���� RAWIP (��. ����). ��������! �������� ������ ������� ��������� HDLC ���������� �������� 6 �����/� �� ����������� ������ Intel(TM) Core(TM)2, 2 ���. ���������� ��������� ������ ���� ��� ��������� ������� ������� ��������; \n"
        " - SPPPHDLC [MSB|OCTET] - ������ ������� ��������� HDLC, ��������� PPP-�������. ��������! �������� ������ ������� ��������� HDLC ���������� �������� 6 �����/� �� ����������� ������ Intel(TM) Core(TM)2, 2 ���. ���������� ��������� ������ ���� ��� ��������� ������� ������� ��������; \n"
        " - ATM AAL5 - ��������� ������� ATM ������ ��������� AAL 5, ����������� ��������; \n"
        " - SRAWIP. ������������ ����� IP-������� �� ����������� ��������� � ��� ���������. ��������: ������ IP - 4, ����� IP-��������� - �� 20 �� 40 ����, ����� IP-������ - �� ����� 16384, ����������� ����� IP-������ - ����������;\n"
        ,cfg_in_pins_payload, cfg_in_pins_payload_enum, PINS_ARRAY_SIZE, &cfg_in_pins_count);

      prefs_register_uint_preference_arr(pref_in_pins, pref_in_pins_payload, (1 << 3) | (1 << 14) | (1 << 15) | (1 << 16) | (1 << 17) | (1 << 18), 0, "in_pins_payload_wparam",
        "���������, �",
        "���������, �. "
        "�������� ������� ��������� ������������ ��� ��������� ��������� ����� �������� (<����� ���������>)."
        ,cfg_in_pins_payload_wparam, PINS_ARRAY_SIZE, &cfg_in_pins_count);

      prefs_register_uint_preference_arr(pref_in_pins, pref_in_pins_payload, (1 << 3) | (1 << 14) | (1 << 15) | (1 << 16) | (1 << 17) | (1 << 18), 0, "in_pins_payload_lparam",
        "��������, �",
        "��������, �. "
        "�������� ������� ��������� ������������ ��� ��������� ��������� ����� �������� (<����� ���������>)."
        ,cfg_in_pins_payload_lparam, PINS_ARRAY_SIZE, &cfg_in_pins_count);

      preference_p pref_in_pins_pid_lid_setter_check = prefs_register_bool_preference_arr(pref_in_pins, pref_in_pins_check, 0, 0, "in_pins_pid_lid_setter_check",
        "����������� PID/LID",
        "�������������� �������� PID/LID ��� ���. "
        "��������� ��������: \n"
        "  - 0 - �� ������������ \n"
        "  - 1 - ������������ \n"
        ,cfg_in_pins_pid_lid_setter_check, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        preference_p pref_in_pins_has_set_pid = prefs_register_bool_preference_arr(pref_in_pins, pref_in_pins_pid_lid_setter_check, 0, 0, "in_pins_has_set_pid",
          "��������� PID",
          "��������� PID."
          ,cfg_in_pins_has_set_pid, PINS_ARRAY_SIZE, &cfg_in_pins_count);

          prefs_register_uint_preference_arr(pref_in_pins, pref_in_pins_has_set_pid, 0, 0, "in_pins_set_pid",
            "�������� PID",
            "�������� PID."
            "��������� \"set_pid\" � \"set_lid\" ���������� �������������� �������� PID � LID ��� ������� ��������� ������, "
            "�� ����, ��� ����������� ���������� ������, ��� ������������ �������� PID/LID ���������� �� ��������. "
            "�������� \"set_pid\" � \"set_lid\" �������� ����������. ��������, ���� ����� PID, �� �� ����� LID, "
            "����� ������� PID ������������� �����, � ������� LID - ���. "
            ,cfg_in_pins_set_pid, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        preference_p pref_in_pins_has_set_lid = prefs_register_bool_preference_arr(pref_in_pins, pref_in_pins_pid_lid_setter_check, 0, 0, "in_pins_has_set_lid",
          "��������� LID",
          "��������� LID."
          ,cfg_in_pins_has_set_lid, PINS_ARRAY_SIZE, &cfg_in_pins_count);

          prefs_register_uint_preference_arr(pref_in_pins, pref_in_pins_has_set_lid, 0, 0, "in_pins_set_lid",
            "�������� LID",
            "�������� LID."
            "��������� \"set_pid\" � \"set_lid\" ���������� �������������� �������� PID � LID ��� ������� ��������� ������, "
            "�� ����, ��� ����������� ���������� ������, ��� ������������ �������� PID/LID ���������� �� ��������. "
            "�������� \"set_pid\" � \"set_lid\" �������� ����������. ��������, ���� ����� PID, �� �� ����� LID, "
            "����� ������� PID ������������� �����, � ������� LID - ���. "
            ,cfg_in_pins_set_lid, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        preference_p pref_in_pins_has_set_pid_mask = prefs_register_bool_preference_arr(pref_in_pins, pref_in_pins_pid_lid_setter_check, 0, 0, "in_pins_has_set_pid_mask",
          "��������� PID-�����",
          "��������� PID-�����."
          ,cfg_in_pins_has_set_pid_mask, PINS_ARRAY_SIZE, &cfg_in_pins_count);

          prefs_register_uint_preference_arr(pref_in_pins, pref_in_pins_has_set_pid_mask, 0, 0, "in_pins_set_pid_mask",
            "�������� PID-�����",
            "�������� PID-�����."
            "��������� \"set_pid_mask\" � \"set_lid_mask\" ���������� ������������ �������� PID � LID ��� ������� ��������� ������, "
            "�� ����, ��� ����������� ���������� ������, ��� ������������ �������� PID/LID ����������� ���������� <�> � �������� ���������. "
            "�������� \"set_pid_mask\" � \"set_lid_mask\" �������� ����������. ��������, ���� ����� PID_MASK, �� �� ����� LID_MASK, "
            "����� ������� PID_MASK ������������� �����, � ������� LID_MASK - ���. "
            "���������� \"set_pid_mask\" � \"set_lid_mask\" ������� �� ����������� \"set_pid\" � \"set_lid\". "
            ,cfg_in_pins_set_pid_mask, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        preference_p pref_in_pins_has_set_lid_mask = prefs_register_bool_preference_arr(pref_in_pins, pref_in_pins_pid_lid_setter_check, 0, 0, "in_pins_has_set_lid_mask",
          "��������� LID-�����",
          "��������� LID-�����."
          ,cfg_in_pins_has_set_lid_mask, PINS_ARRAY_SIZE, &cfg_in_pins_count);

          prefs_register_uint_preference_arr(pref_in_pins, pref_in_pins_has_set_lid_mask, 0, 0, "in_pins_set_lid_mask",
            "�������� LID-�����",
            "�������� LID-�����."
            "��������� \"set_pid_mask\" � \"set_lid_mask\" ���������� ������������ �������� PID � LID ��� ������� ��������� ������, "
            "�� ����, ��� ����������� ���������� ������, ��� ������������ �������� PID/LID ����������� ���������� <�> � �������� ���������. "
            "�������� \"set_pid_mask\" � \"set_lid_mask\" �������� ����������. ��������, ���� ����� PID_MASK, �� �� ����� LID_MASK, "
            "����� ������� PID_MASK ������������� �����, � ������� LID_MASK - ���. "
            "���������� \"set_pid_mask\" � \"set_lid_mask\" ������� �� ����������� \"set_pid\" � \"set_lid\". "
            ,cfg_in_pins_set_lid_mask, PINS_ARRAY_SIZE, &cfg_in_pins_count);

      prefs_register_bool_preference_arr(pref_in_pins, pref_in_pins_check, 0, 0, "in_pins_suppress_pid_lid_counting",
        "��������� �������� PID/LID-����������",
        "����������� ��� ��� ������� ���������� PID/LID-���, ������������ �� ������ ����. "
        "��������� ��������: \n"
        "  - 0 - ����������� �������� \n"
        "  - 1 - �� ����������� �������� \n"
        ,cfg_in_pins_suppress_pid_lid_counting, PINS_ARRAY_SIZE, &cfg_in_pins_count);

      preference_p pref_in_pins_filter_check = prefs_register_bool_preference_arr(pref_in_pins, pref_in_pins_check, 0, 0, "in_pins_filter_check",
        "����������",
        "������������ ���������� ��� ���. "
        "��������� ��������: \n"
        "  - 0 - �� ������������ \n"
        "  - 1 - ������������ \n"
        ,cfg_in_pins_filter_check, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_file_preference_arr(pref_in_pins, pref_in_pins_filter_check, 0, 0, "in_pins_filter_dvb_mac",
          "������ DVB MAC - �����",
          "������ DVB MAC - �����."
          FILTER_DESCRIPTION
          ,cfg_in_pins_filter_dvb_mac.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_file_preference_arr(pref_in_pins, pref_in_pins_filter_check, 0, 0, "in_pins_filter_dvb_mac_rem",
          "������ DVB MAC - �������",
          "������ DVB MAC - �������."
          FILTER_DESCRIPTION
          ,cfg_in_pins_filter_dvb_mac_rem.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_file_preference_arr(pref_in_pins, pref_in_pins_filter_check, 0, 0, "in_pins_filter_ip",
          "������ IP - �����",
          "������ IP - �����."
          FILTER_DESCRIPTION
          ,cfg_in_pins_filter_ip.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_file_preference_arr(pref_in_pins, pref_in_pins_filter_check, 0, 0, "in_pins_filter_ip_rem",
          "������ IP - �������",
          "������ IP - �������."
          FILTER_DESCRIPTION
          ,cfg_in_pins_filter_ip_rem.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_csv_preference_arr(pref_in_pins, pref_in_pins_filter_check, 0, in_pins_filter_tcp_ports_validator, "in_pins_filter_tcp",
          "������ TCP - �����",
          "������ TCP - �����. "
          "��������� ��������: ������ �������������� �������� TCP-������. "
          "������ �������� ���������� ������ �������������� TCP-������ - ������ � ������� ���������� ������ ����� "
          "������������ �� ���������, ��������� - ���."
          "������ �������� ������� ��������� ����������, ��� ���������� �� ������� �������� ������������� �� �����. "
          ,cfg_in_pins_filter_tcp.data, PREFS_MAX_PATH, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_csv_preference_arr(pref_in_pins, pref_in_pins_filter_check, 0, in_pins_filter_tcp_rem_ports_validator, "in_pins_filter_tcp_rem",
          "������ TCP - �������",
          "������ TCP - �������. "
          "��������� ��������: ������ �������������� �������� TCP-������. "
          "������ �������� ���������� ������ �������������� TCP-������ - ������ � ������� ���������� ������ �� ����� "
          "������������ �� ���������, ��������� - �����."
          "������ �������� ������� ��������� ����������, ��� ���������� �� ������� �������� ������������� �� �����. "
          ,cfg_in_pins_filter_tcp_rem.data, PREFS_MAX_PATH, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_file_preference_arr(pref_in_pins, pref_in_pins_filter_check, 0, 0, "in_pins_filter_ip_tcp",
          "������ IP/TCP - �����",
          "������ IP/TCP - �����."
          FILTER_DESCRIPTION
          ,cfg_in_pins_filter_ip_tcp.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_file_preference_arr(pref_in_pins, pref_in_pins_filter_check, 0, 0, "in_pins_filter_ip_tcp_rem",
          "������ IP/TCP - �������",
          "������ IP/TCP - �������."
          FILTER_DESCRIPTION
          ,cfg_in_pins_filter_ip_tcp_rem.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_file_preference_arr(pref_in_pins, pref_in_pins_filter_check, 0, 0, "in_pins_filter_ip_udp",
          "������ IP/UDP - �����",
          "������ IP/UDP - �����."
          FILTER_DESCRIPTION
          ,cfg_in_pins_filter_ip_udp.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_file_preference_arr(pref_in_pins, pref_in_pins_filter_check, 0, 0, "in_pins_filter_ip_udp_rem",
          "������ IP/UDP - �������",
          "������ IP/UDP - �������."
          FILTER_DESCRIPTION
          ,cfg_in_pins_filter_ip_udp_rem.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_file_preference_arr(pref_in_pins, pref_in_pins_filter_check, 0, 0, "in_pins_filter_url_rem",
          "������ URL - �������",
          "������ URL - �������."
          FILTER_DESCRIPTION
          ,cfg_in_pins_filter_url_rem.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_file_preference_arr(pref_in_pins, pref_in_pins_filter_check, 0, 0, "in_pins_filter_med_rem",
          "������ MED - �������",
          "������ MED - �������."
          FILTER_DESCRIPTION
          ,cfg_in_pins_filter_med_rem.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_file_preference_arr(pref_in_pins, pref_in_pins_filter_check, 0, 0, "in_pins_filter_session_header_rem",
          "������ SESSION HEADER - �������",
          "������ SESSION HEADER - �������."
          FILTER_DESCRIPTION
          ,cfg_in_pins_filter_session_header_rem.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_in_pins_count);

      preference_p pref_in_pins_has_set_delay = prefs_register_enum_preference_arr(pref_in_pins, pref_in_pins_src,
        1 << in_src_type::in_src_file_train | 1 << in_src_type::in_src_file_trainc | 1 << in_src_type::in_src_file_libpcap |
        1 << in_src_type::in_src_file_train32 | 1 << in_src_type::in_src_file_trainips32 | 1 << in_src_type::in_src_file_traintm |
        1 << in_src_type::in_src_file_raw | 1 << in_src_type::in_src_file_pkc,
        0, "in_pins_has_set_delay",
        "����������� �������� ������",
        "����������� �������� ������ ������."
        "�� ��������: \n"
        "�������� \"<������������ �������� ������>\" ������������ ������ � ������ ������ ������ �� ����� � ���������� ������������� �������� "
        "��� ������ ������. \n"
        "���������: \n"
        "��������� \"<���������� �������>,<����� ��������>\" ������������ ������ � ������ ������ ������ �� ����� � ���������� ������������� �������� "
        "��� ������ ������: ����� ������ ��������� <���������� �������> ������� ���������� \"���������\" ��������� ������ �� <������������> �����������. "
        "���� <���������� �������> � <����� ��������> - �������� ��������. �������� ���� <���������� �������> �� ����� ���� ����� 0!. ������ ���������������� ����� "
        "�������������� ��� �������������� ���������� ������ ������ ������ �� �����. \n"
        "����� LIBPCAP: \n"
        "�������� ��������� ������� � ������� ��������� �������� �� ������ ������� ��� ������� ������, ������������ � ������ ������� LIBPCAP."
        ,cfg_in_pins_has_set_delay, cfg_in_pins_set_delay_enum, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_uint_preference_arr(pref_in_pins, pref_in_pins_has_set_delay, 1 << SPEED_RESTRICTION_SPEED, 0, "in_pins_set_delay_speed",
          "������������ �������� ������, ����/�",
          "������������ �������� ������ ������ �� �����. \n"
          "����� ������������ ��������� �������� ���������, ����������� �� ����� �������� ����� � ������� ������. \n"
          "�������, \"���������\" ����������� �� ����� ����������� \"������������\" ����� ������ ������. \n"
          "����������� �������� �����������, ��� �������� �� ����� ��������� ��������� ��������, ���� ����� ��������� ��������� 1 �. \n"
          "�������� � ������ � �������. \n"
          "!�� ����� ���� ����� 0! \n"
          ,cfg_in_pins_set_delay_speed, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_uint_preference_arr(pref_in_pins, pref_in_pins_has_set_delay, 1 << SPEED_RESTRICTION_PACKETS, 0, "in_pins_set_delay_packets",
          "���������� �������, ��",
          "���������� �������, ��. \n"
          "!�� ����� ���� ����� 0! \n"
          ,cfg_in_pins_set_delay_packets, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_msec_preference_arr(pref_in_pins, pref_in_pins_has_set_delay, 1 << SPEED_RESTRICTION_PACKETS, 0, "in_pins_set_delay_msecs",
          "����� ��������, ��",
          "����� ��������, ��. \n"
          "!�� ����� ���� ����� 0! \n"
          ,cfg_in_pins_set_delay_msecs, PINS_ARRAY_SIZE, &cfg_in_pins_count);

      prefs_register_bool_preference_arr(pref_in_pins, pref_in_pins_src,
        1 << in_src_type::in_src_file_train | 1 << in_src_type::in_src_file_trainc | 1 << in_src_type::in_src_file_libpcap |
        1 << in_src_type::in_src_file_train32 | 1 << in_src_type::in_src_file_trainips32 | 1 << in_src_type::in_src_file_traintm |
        1 << in_src_type::in_src_file_raw | 1 << in_src_type::in_src_file_pkc,
        0, "in_pins_has_cyclic",
        "��������� ������������",
        "��������� ����� �������� �������� ����� ���������� ��������� ��� ���."
        "�������� ������������ ������ � ������ ������ ������ �� ����� � ���������� ����������� �������� ������ ������ �� �����: "
        "��� ���������� ����� ����� ��������� ������ ������������ � ��������� �������. ����� ������� ����������� ����������� ������ ������ �� �����. "
        ,cfg_in_pins_has_cyclic, PINS_ARRAY_SIZE, &cfg_in_pins_count);

      prefs_register_bool_preference_arr(pref_in_pins, pref_in_pins_src,
        1 << in_src_type::in_src_file_train | 1 << in_src_type::in_src_file_trainc | 1 << in_src_type::in_src_file_libpcap |
        1 << in_src_type::in_src_file_train32 | 1 << in_src_type::in_src_file_trainips32 | 1 << in_src_type::in_src_file_traintm |
        1 << in_src_type::in_src_file_raw | 1 << in_src_type::in_src_file_pkc,
        0, "in_pins_has_unlink",
        "������� �����",
        "������� ����� ����� ��������� ��� ���."
        "�������� ������������ ������ � ������ ������ ������ �� ����� � ������������ ������� ������� ����� ����� �� ���������. "
        ,cfg_in_pins_has_unlink, PINS_ARRAY_SIZE, &cfg_in_pins_count);

//////////////////////////////////////////////////////////////////////////
  preference_p pref_mux_pins = prefs_register_module(0, "mux_pins", "��������������",
    "������ �������� ��������� ��������� ��������� ���������������. "
    "!��������! ���� �������� ��� ��������� \"�����\\������������ PID-�������� PID/LID-�����������\" � \"�����\\������������ LID-�������� PID/LID-�����������\", ������������ ���� ����� PID/LID-���������� � �������������� ������������. "
    , 7, 0);

    preference_p pref_mux_pins_check = prefs_register_bool_preference_arr(pref_mux_pins, 0, 0, 0, "mux_pins_check",
      "�������������",
      "������������ ������ ������������� ��� ���. "
      "��������� ��������: \n"
      "  - 0 - �� ������������ \n"
      "  - 1 - ������������ \n"
      ,cfg_mux_pins_check, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

      prefs_register_string_preference_arr(pref_mux_pins, pref_mux_pins_check, 0, 0, "mux_pins_name",
        "���",
        "��� ��������������. "
        "�������� ��������� �������� � ���� ������ ���������-�������� �������� � ������ ��� ������������� �������� (��������, ��� ���������� ��������� ����� �����). "
        ,cfg_mux_pins_name.data, PREFS_MAX_PATH, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

      prefs_register_uint_preference_arr(pref_mux_pins, pref_mux_pins_check, 0, 0, "mux_pins_pid",
        "PID",
        "PID. "
        "�������� ��������� ���������� �������� PID ���� PID/LID, ��� ������� ����������. "
        ,cfg_mux_pins_pid, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

      prefs_register_uint_preference_arr(pref_mux_pins, pref_mux_pins_check, 0, 0, "mux_pins_lid",
        "LID",
        "LID. "
        "�������� ��������� ���������� �������� LID ���� PID/LID, ��� ������� ����������. "
        ,cfg_mux_pins_lid, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

      preference_p pref_mux_pins_payload = prefs_register_enum_preference_arr(pref_mux_pins, pref_mux_pins_check, 0, 0, "mux_pins_payload",
        "��� ��������",
        "��� ��������. "
        "�������� ���������� ��� ���������� ������ ����������� ������. \n"
        "�������� ���� ������: \n"
        " - AUTO - �������������� ����������� ���� �������� (���������� ������);\n"
        " - DUMMY - ��������� ������ �� ������������ (������ ��������������� �� ������);\n"
        " - NULL - ��������� ������� �� ������������, ��� ������ ���������� ��� \"UNK - ����������� ������\";\n"
        " - RAWIP <����� ���������> <����� ���������> - ����������� \"���������\" �������. ������������ ��������� ������ � ����� ������ (���������� ���������� ���� �������� ����� �������������� �������� ��������� <����� ���������> <����� ���������>), ���������� ����� ��������� IP-������� � ������������ ��� ���������. ���� �������� <����� ���������> �������������, ������������ ����� ������ ��������� IP-������ � ��������� � �������� (0) ����� �� ���������� ������������� �������� ��������� <����� ���������>;\n"
        " - ETH - ����� � ��������� Ethernet-������ (��� ����������� �����);\n"
        " - CHDLC - ����� � ��������� ������� Cisco HDLC � ���������� � ����������� ������;\n"
        " - PPP - ����� � ��������� PPP-������� � ���������� � ����������� ������;\n"
        " - DVB - ����� � ��������� DVB MPEG-TS ������;\n"
        " - FR - ����� � ��������� FR-������ � ���������� � ����������� ������;\n"
        " - WLAN - ����� � ��������� IEEE 802.11-������ (��� ����������� �����);\n"
        " - ATM [MSB] - ����� � ��������� ����� ATM, ������ ������� AAL 5, ��������� ��������. ���� ����� �������������� �������� MSB, ������������ �������� ��� � ������ �������� ������;\n"
        " - SATM [MSB] - ����� � ��������� ����� ATM � ������, ������ ������� AAL 5, ��������� ��������. ���� ����� �������������� �������� MSB, ������������ �������� ��� � ������ �������� ������. ������� �� ATM ����������� � ���, ��� ������������ �������������� ������������� �� ������������ ��������� � HEC;\n"
        " - SHDLC [MSB|OCTET] <����� ���������> <����� ���������> - ������ ������� ��������� HDLC, ��������� IP-������� ��� ��, ��� � � ���� RAWIP (��. ����). ��������! �������� ������ ������� ��������� HDLC ���������� �������� 6 �����/� �� ����������� ������ Intel(TM) Core(TM)2, 2 ���. ���������� ��������� ������ ���� ��� ��������� ������� ������� ��������; \n"
        " - SHDLCM [MSB|OCTET] <����� ���������> <����� ���������> - ������ ������� ��������� HDLC-M, ��������� IP-������� ��� ��, ��� � � ���� RAWIP (��. ����). ��������! �������� ������ ������� ��������� HDLC ���������� �������� 6 �����/� �� ����������� ������ Intel(TM) Core(TM)2, 2 ���. ���������� ��������� ������ ���� ��� ��������� ������� ������� ��������; \n"
        " - SPPPHDLC [MSB|OCTET] - ������ ������� ��������� HDLC, ��������� PPP-�������. ��������! �������� ������ ������� ��������� HDLC ���������� �������� 6 �����/� �� ����������� ������ Intel(TM) Core(TM)2, 2 ���. ���������� ��������� ������ ���� ��� ��������� ������� ������� ��������; \n"
        " - ATM AAL5 - ��������� ������� ATM ������ ��������� AAL 5, ����������� ��������; \n"
        ,cfg_mux_pins_payload, cfg_in_pins_payload_enum, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        prefs_register_uint_preference_arr(pref_mux_pins, pref_mux_pins_payload, (1 << 3) | (1 << 14) | (1 << 15) | (1 << 16) | (1 << 17) | (1 << 18), 0, "mux_pins_payload_wparam",
          "���������, �",
          "���������, �. "
          "�������� ������� ��������� ������������ ��� ��������� ��������� ����� �������� (<����� ���������>)."
          ,cfg_mux_pins_payload_wparam, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        prefs_register_uint_preference_arr(pref_mux_pins, pref_mux_pins_payload, (1 << 3) | (1 << 14) | (1 << 15) | (1 << 16) | (1 << 17) | (1 << 18), 0, "mux_pins_payload_lparam",
          "��������, �",
          "��������, �. "
          "�������� ������� ��������� ������������ ��� ��������� ��������� ����� �������� (<����� ���������>)."
          ,cfg_mux_pins_payload_lparam, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

      preference_p pref_mux_pins_pid_lid_setter_check = prefs_register_bool_preference_arr(pref_mux_pins, pref_mux_pins_check, 0, 0, "mux_pins_pid_lid_setter_check",
        "����������� PID/LID",
        "�������������� �������� PID/LID ��� ���. "
        "��������� ��������: \n"
        "  - 0 - �� ������������ \n"
        "  - 1 - ������������ \n"
        ,cfg_mux_pins_pid_lid_setter_check, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        preference_p pref_mux_pins_has_set_pid = prefs_register_bool_preference_arr(pref_mux_pins, pref_mux_pins_pid_lid_setter_check, 0, 0, "mux_pins_has_set_pid",
          "��������� PID",
          "��������� PID."
          ,cfg_mux_pins_has_set_pid, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

          prefs_register_uint_preference_arr(pref_mux_pins, pref_mux_pins_has_set_pid, 0, 0, "mux_pins_set_pid",
            "�������� PID",
            "�������� PID."
            "��������� \"set_pid\" � \"set_lid\" ���������� �������������� �������� PID � LID ��� ������� ��������� ������, "
            "�� ����, ��� ����������� ���������� ������, ��� ������������ �������� PID/LID ���������� �� ��������. "
            "�������� \"set_pid\" � \"set_lid\" �������� ����������. ��������, ���� ����� PID, �� �� ����� LID, "
            "����� ������� PID ������������� �����, � ������� LID - ���. "
            ,cfg_mux_pins_set_pid, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        preference_p pref_mux_pins_has_set_lid = prefs_register_bool_preference_arr(pref_mux_pins, pref_mux_pins_pid_lid_setter_check, 0, 0, "mux_pins_has_set_lid",
          "��������� LID",
          "��������� LID."
          ,cfg_mux_pins_has_set_lid, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

          prefs_register_uint_preference_arr(pref_mux_pins, pref_mux_pins_has_set_lid, 0, 0, "mux_pins_set_lid",
            "�������� LID",
            "�������� LID."
            "��������� \"set_pid\" � \"set_lid\" ���������� �������������� �������� PID � LID ��� ������� ��������� ������, "
            "�� ����, ��� ����������� ���������� ������, ��� ������������ �������� PID/LID ���������� �� ��������. "
            "�������� \"set_pid\" � \"set_lid\" �������� ����������. ��������, ���� ����� PID, �� �� ����� LID, "
            "����� ������� PID ������������� �����, � ������� LID - ���. "
            ,cfg_mux_pins_set_lid, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        preference_p pref_mux_pins_has_set_pid_mask = prefs_register_bool_preference_arr(pref_mux_pins, pref_mux_pins_pid_lid_setter_check, 0, 0, "mux_pins_has_set_pid_mask",
          "��������� PID-�����",
          "��������� PID-�����."
          ,cfg_mux_pins_has_set_pid_mask, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

          prefs_register_uint_preference_arr(pref_mux_pins, pref_mux_pins_has_set_pid_mask, 0, 0, "mux_pins_set_pid_mask",
            "�������� PID-�����",
            "�������� PID-�����."
            "��������� \"set_pid_mask\" � \"set_lid_mask\" ���������� ������������ �������� PID � LID ��� ������� ��������� ������, "
            "�� ����, ��� ����������� ���������� ������, ��� ������������ �������� PID/LID ����������� ���������� <�> � �������� ���������. "
            "�������� \"set_pid_mask\" � \"set_lid_mask\" �������� ����������. ��������, ���� ����� PID_MASK, �� �� ����� LID_MASK, "
            "����� ������� PID_MASK ������������� �����, � ������� LID_MASK - ���. "
            "���������� \"set_pid_mask\" � \"set_lid_mask\" ������� �� ����������� \"set_pid\" � \"set_lid\". "
            ,cfg_mux_pins_set_pid_mask, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        preference_p pref_mux_pins_has_set_lid_mask = prefs_register_bool_preference_arr(pref_mux_pins, pref_mux_pins_pid_lid_setter_check, 0, 0, "mux_pins_has_set_lid_mask",
          "��������� LID-�����",
          "��������� LID-�����."
          ,cfg_mux_pins_has_set_lid_mask, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

          prefs_register_uint_preference_arr(pref_mux_pins, pref_mux_pins_has_set_lid_mask, 0, 0, "mux_pins_set_lid_mask",
            "�������� LID-�����",
            "�������� LID-�����."
            "��������� \"set_pid_mask\" � \"set_lid_mask\" ���������� ������������ �������� PID � LID ��� ������� ��������� ������, "
            "�� ����, ��� ����������� ���������� ������, ��� ������������ �������� PID/LID ����������� ���������� <�> � �������� ���������. "
            "�������� \"set_pid_mask\" � \"set_lid_mask\" �������� ����������. ��������, ���� ����� PID_MASK, �� �� ����� LID_MASK, "
            "����� ������� PID_MASK ������������� �����, � ������� LID_MASK - ���. "
            "���������� \"set_pid_mask\" � \"set_lid_mask\" ������� �� ����������� \"set_pid\" � \"set_lid\". "
            ,cfg_mux_pins_set_lid_mask, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

      preference_p pref_mux_pins_filter_check = prefs_register_bool_preference_arr(pref_mux_pins, pref_mux_pins_check, 0, 0, "mux_pins_filter_check",
        "����������",
        "������������ ���������� ��� ���. "
        "��������� ��������: \n"
        "  - 0 - �� ������������ \n"
        "  - 1 - ������������ \n"
        ,cfg_mux_pins_filter_check, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        prefs_register_file_preference_arr(pref_mux_pins, pref_mux_pins_filter_check, 0, 0, "mux_pins_filter_dvb_mac",
          "������ DVB MAC - �����",
          "������ DVB MAC - �����."
          FILTER_DESCRIPTION
          ,cfg_mux_pins_filter_dvb_mac.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        prefs_register_file_preference_arr(pref_mux_pins, pref_mux_pins_filter_check, 0, 0, "mux_pins_filter_dvb_mac_rem",
          "������ DVB MAC - �������",
          "������ DVB MAC - �������."
          FILTER_DESCRIPTION
          ,cfg_mux_pins_filter_dvb_mac_rem.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        prefs_register_file_preference_arr(pref_mux_pins, pref_mux_pins_filter_check, 0, 0, "mux_pins_filter_ip",
          "������ IP - �����",
          "������ IP - �����."
          FILTER_DESCRIPTION
          ,cfg_mux_pins_filter_ip.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        prefs_register_file_preference_arr(pref_mux_pins, pref_mux_pins_filter_check, 0, 0, "mux_pins_filter_ip_rem",
          "������ IP - �������",
          "������ IP - �������."
          FILTER_DESCRIPTION
          ,cfg_mux_pins_filter_ip_rem.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        prefs_register_csv_preference_arr(pref_mux_pins, pref_mux_pins_filter_check, 0, mux_pins_filter_tcp_ports_validator, "mux_pins_filter_tcp",
          "������ TCP - �����",
          "������ TCP - �����. "
          "��������� ��������: ������ �������������� �������� TCP-������. "
          "������ �������� ���������� ������ �������������� TCP-������ - ������ � ������� ���������� ������ ����� "
          "������������ �� ���������, ��������� - ���."
          "������ �������� ������� ��������� ����������, ��� ���������� �� ������� �������� ������������� �� �����. "
          ,cfg_mux_pins_filter_tcp.data, PREFS_MAX_PATH, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        prefs_register_csv_preference_arr(pref_mux_pins, pref_mux_pins_filter_check, 0, mux_pins_filter_tcp_rem_ports_validator, "mux_pins_filter_tcp_rem",
          "������ TCP - �������",
          "������ TCP - �������. "
          "��������� ��������: ������ �������������� �������� TCP-������. "
          "������ �������� ���������� ������ �������������� TCP-������ - ������ � ������� ���������� ������ �� ����� "
          "������������ �� ���������, ��������� - �����."
          "������ �������� ������� ��������� ����������, ��� ���������� �� ������� �������� ������������� �� �����. "
          ,cfg_mux_pins_filter_tcp_rem.data, PREFS_MAX_PATH, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        prefs_register_file_preference_arr(pref_mux_pins, pref_mux_pins_filter_check, 0, 0, "mux_pins_filter_ip_tcp",
          "������ IP/TCP - �����",
          "������ IP/TCP - �����."
          FILTER_DESCRIPTION
          ,cfg_mux_pins_filter_ip_tcp.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        prefs_register_file_preference_arr(pref_mux_pins, pref_mux_pins_filter_check, 0, 0, "mux_pins_filter_ip_tcp_rem",
          "������ IP/TCP - �������",
          "������ IP/TCP - �������."
          FILTER_DESCRIPTION
          ,cfg_mux_pins_filter_ip_tcp_rem.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        prefs_register_file_preference_arr(pref_mux_pins, pref_mux_pins_filter_check, 0, 0, "mux_pins_filter_ip_udp",
          "������ IP/UDP - �����",
          "������ IP/UDP - �����."
          FILTER_DESCRIPTION
          ,cfg_mux_pins_filter_ip_udp.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        prefs_register_file_preference_arr(pref_mux_pins, pref_mux_pins_filter_check, 0, 0, "mux_pins_filter_ip_udp_rem",
          "������ IP/UDP - �������",
          "������ IP/UDP - �������."
          FILTER_DESCRIPTION
          ,cfg_mux_pins_filter_ip_udp_rem.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        prefs_register_file_preference_arr(pref_mux_pins, pref_mux_pins_filter_check, 0, 0, "mux_pins_filter_url_rem",
          "������ URL - �������",
          "������ URL - �������."
          FILTER_DESCRIPTION
          ,cfg_mux_pins_filter_url_rem.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        prefs_register_file_preference_arr(pref_mux_pins, pref_mux_pins_filter_check, 0, 0, "mux_pins_filter_med_rem",
          "������ MED - �������",
          "������ MED - �������."
          FILTER_DESCRIPTION
          ,cfg_mux_pins_filter_med_rem.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        prefs_register_file_preference_arr(pref_mux_pins, pref_mux_pins_filter_check, 0, 0, "mux_pins_filter_session_header_rem",
          "������ SESSION HEADER - �������",
          "������ SESSION HEADER - �������."
          FILTER_DESCRIPTION
          ,cfg_mux_pins_filter_session_header_rem.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

//////////////////////////////////////////////////////////////////////////
  preference_p pref_out_pins = prefs_register_module(0, "out_pins", "������",
    "������ �������� ��������� ��������� ��������� �������."
    , 8, 0);

    preference_p pref_out_pins_check = prefs_register_bool_preference_arr(pref_out_pins, 0, 0, 0, "out_pins_check",
      "�����",
      "������������ ������ �������� ����� ��� ���. "
      "��������� ��������: \n"
      "  - 0 - �� ������������ \n"
      "  - 1 - ������������ \n"
      ,cfg_out_pins_check, PINS_ARRAY_SIZE, &cfg_out_pins_count);

      prefs_register_string_preference_arr(pref_out_pins, pref_out_pins_check, 0, 0, "out_pins_name",
        "���",
        "��� ��������� ������. "
        "�������� ��������� �������� � ���� ������ ���������-�������� �������� � ������ ��� ������������� �������� (��������, ��� ���������� ��������� ����� �����). "
        ,cfg_out_pins_name.data, PREFS_MAX_PATH, PINS_ARRAY_SIZE, &cfg_out_pins_count);

      preference_p pref_out_pins_dst = prefs_register_enum_preference_arr(pref_out_pins, pref_out_pins_check, 0, 0, "out_pins_dst",
        "����������",
        "����������. "
        "�������� ����� ����� ��������� ��������: \n"
        "\n"
        "NULL - ������ ������ �� ��������, ������ ��������� (������������ ��� �������� ����������� ������ ������������� ����). \n"
        "\n"
        "CALLBACK - ������ ���������� ������������������ ������� ��������� ������. ��������! ������ ��� ������������ ������ ��� ������������� �������� ���������� - libcenzor.dll. \n"
        "\n"
        "UDP/TCPC:<ip_address>:<port> TRAIN  - ������ ������ ������������ �� �������� �����������, � ������� \"�������\". \n"
        "\n"
        "TCPC:<ip_address>:<port> TRAINS  - ������ ������ ������������ �� �������� �����������, � ���������������� ������� \"�������\". ������� - ��������� ���������� �� ������������. ����� ������� ������������� �� 4 ����. ������ ��� ���������� ��� UDP-����������. \n"
        "\n"
        "TCPC:<ip_address>:<port> TRAINM  - ������ ������ ������������ �� �������� �����������, � ���������������� ������� \"�������\". ������� - ��������� ���������� �� ������������. ����� ������� ������������� �� 4 ����. ���� PID/LID �� ����������� � �������� ���� �����. ������ ��� ���������� ��� UDP-����������. \n"
        "\n"
        "dst=TCPC:<ip_address>:<port> SRM  - ������ ������ ������������ �� �������� �����������, � ��������� �������: \n"
        "  UNI(4)|Length(4)|TvSec(4)|TvUSec(4)|Length2(4)|Data(Length2) \n"
        "    UNI - ������������� �������� ������, �������� ����������� ����� � �������;\n"
        "    Length - ����� ������ � ������, ������������ ��������������� �� ������ �����;\n"
        "    TvSec - ����� ������ ������, �������� � ��������;\n"
        "    TvUSec - ��������� ������� ������ ������, �������� � �������������;\n"
        "    Length2 - ����� ������ � ������, ������������ ��������������� �� ������ �����;\n"
        "    Data - ������.\n"
        "    ����� ������� �� ������������� �� 4 ����. ��� �������� ���� ����� ������ ������� ����, ������ ����� - 32 ����. ������ ��� ���������� ��� UDP-����������. \n"
        "\n"
        "UDP/TCPC:<ip_address>:<port> RAW  - ������ ������ ������������ �� �������� �����������, � \"�����\" ������� (������ ������ ����� �� �����������). \n"
        "\n"
        "���� ������� �����������: \n"
        " - UDP:<ip_address>:<port> - ��� ������� ������ - ������� ����������� �� ���������� IP-������ <ip_address> � UDP-����� <port> (UDP-������ �����������) \n"
        " - TCPC:<ip_address>:<port> - ��� ������� ������ - ������� ����������� �� ���������� IP-������ <ip_address> � TCP-����� <port> (TCP-������ �����������) \n"
        "\n"
        "<���_�����> TRAIN  - ������ ������ ������������ � ���� <���_�����>, � ������� \"�������\" (������ ������ �� ��������� �� 4 ����). \n"
        "\n"
        "<���_�����> RAW  - ������ ������ ������������ � ���� <���_�����>, � \"�����\" ������� (������ ������ ����� �� �����������). \n"
        "\n"
        "<���_�����> PKC  - ������ ������ ������������ � ���� <���_�����>, � ������� \"PKC\":  \n"
        "  ������ ������: \n"
        "    5B 5D XX XX 0D 0A ����� \n"
        "    ��� XX XX ���������� ���� ��������� �� ���� (����� ������ + 2 �����). \n"
        "\n"
        "<���_�����> IPSv2 [APPEND] - ������ ������ ������������ � ���� <���_�����>, � ������� IP_STREAM v2 (�������� ���������������� IP_STREAM � ����������� � ��������������� ���������). \n"
        "\n"
        "<���_�����> LIBPCAP [APPEND] - ������ ������ ������������ � ���� <���_�����>, � ������� LIBPCAP. \n"
        "\n"
        ,cfg_out_pins_dst, cfg_out_pins_dst_enum, PINS_ARRAY_SIZE, &cfg_out_pins_count);

        prefs_register_string_preference_arr(pref_out_pins, pref_out_pins_dst,
          1 << out_dst_type::out_dst_net_udp_train | 1 << out_dst_type::out_dst_net_udp_raw | 1 << out_dst_type::out_dst_net_tcpc_train |
          1 << out_dst_type::out_dst_net_tcpc_trains | 1 << out_dst_type::out_dst_net_tcpc_trainm | 1 << out_dst_type::out_dst_net_tcpc_srm | 1 << out_dst_type::out_dst_net_tcpc_raw,
          0, "out_pins_dst_address",
          "�����",
          "�����. "
          "�������� ������� ��������� ������������ ��� ��������� ��������� ����� ���������� (<ip_address>:<port>)."
          ,cfg_out_pins_dst_address.data, PREFS_MAX_PATH, PINS_ARRAY_SIZE, &cfg_out_pins_count);

        prefs_register_file_preference_arr(pref_out_pins, pref_out_pins_dst,
          1 << out_dst_type::out_dst_file_train | 1 << out_dst_type::out_dst_file_raw | 1 << out_dst_type::out_dst_file_pkc | 1 << out_dst_type::out_dst_file_ipsv2 | 1 << out_dst_type::out_dst_file_libpcap,
          0, "out_pins_dst_filename",
          "����",
          "��� �����. "
          "�������� ������� ��������� ������������ ��� ��������� ��������� ����� ���������� (<���_�����>)."
          "�������� <���_�����> ����� �������� � ���� ��������� �������������� ����������: \n"
          "\n"
          " - $(DATE) - ������� ���� � ������� ����-��-��. ��������, \"all_$(DATE).dat\" ������������� � ��������� ��� �����: \"all_2007-12-03.dat\"; \n"
          "\n"
          " - $(TIME) - ������� ����� � ������� ��-��-��. ��������, \"all_$(TIME).dat\" ������������� � ��������� ��� �����: \"all_14-21-58.dat\"; \n"
          "\n"
          " - $(PID) - ����������������� ������������� �������� PID � ������� XXXXXXXX. ��������, \"all_$(PID).dat\" ������������� � ��������� ��� �����: \"all_00000001.dat\". ���� ����� �������� ������ � ������� ���������� PID, ������������ ��������������������� ������, �� ���� ����� ������� ������� ������, ������� ������ �������� ���� ��������� � ������. ����� � ������ ����� ����� ���������� ������ ������ � ��������������� PID. ������ ���������� ����� ����� ������������� � ���������� $(LID) (������������� ��������������������� �� PID � LID); \n"
          "\n"
          " - $(LID) - ����������������� ������������� �������� LID � ������� XXXXXXXX. ��������, \"all_$(LID).dat\" ������������� � ��������� ��� �����: \"all_00000001.dat\". ���� ����� �������� ������ � ������� ���������� LID, ������������ ��������������������� ������, �� ���� ����� ������� ������� ������, ������� ������ �������� ���� ��������� � ������. ����� � ������ ����� ����� ���������� ������ ������ � ��������������� LID. ������ ���������� ����� ����� ������������� � ���������� $(PID) (������������� ��������������������� �� PID � LID); \n"
          "\n"
          " - $(<������>) - ������� ��������������� �� ����� �� �������, ����������� ��������� <������> (�������� � ������). ��������� ������������ �������� <������> - K/M/G/T (1K = 1024, 1M = 1024K = 1048576, 1G = 1024M = 1048576K = 1073741824, 1T = 1024G = 1048576M = 1073741824K = 1099511627776). � ����� ����� ����������� ����������������� ������������� �������� �������� (����������� ������) ����������� ���������, ������� �� �������� 0, � ������� XXXXXXXX. ��������, \"all_$(32M).dat\" ������������� � ��������� ����� ������ (������ ���� ����� ����� �����, ������� � 32 ����������): \"all_0000.dat\", \"all_0001.dat\", \"all_0002.dat\" � ��� �����. \n"
          "\n"
          " - $(<�����>s) - ������� ��������������� �� ����� �� �������, ����������� ��������� <�����> (�������� � ��������). ��������� ������������ �������� <������> - K/M/G/T (1K = 1024, 1M = 1024K = 1048576, 1G = 1024M = 1048576K = 1073741824, 1T = 1024G = 1048576M = 1073741824K = 1099511627776). � ����� ����� ����������� ����������������� ������������� �������� �������� (����������� ������) ����������� ���������, ������� �� �������� 0, � ������� XXXXXXXX. ��������, \"all_$(60s).dat\" ������������� � ��������� ����� ������ (������ ���� ����� ����� ����� ������ � 60 ������): \"all_0000.dat\", \"all_0001.dat\", \"all_0002.dat\" � ��� �����. \n"
          "\n"
          ,cfg_out_pins_dst_filename.data, PREFS_MAX_PATH, cfg_pins_filename_any_filter, PINS_ARRAY_SIZE, &cfg_out_pins_count);

        prefs_register_enum_preference_arr(pref_out_pins, pref_out_pins_dst,
          1 << out_dst_type::out_dst_file_libpcap, 0, "out_pins_libpcap_payload",
          "��� �������� - LIBPCAP",
          "��� ��������, ������������ � ��������� LIBPCAP-�����. "
          "\n"
          ,cfg_out_pins_libpcap_payload, pcap_enum, PINS_ARRAY_SIZE, &cfg_out_pins_count);

        prefs_register_string_preference_arr(pref_out_pins, pref_out_pins_dst,
          1 << out_dst_type::out_dst_file_train | 1 << out_dst_type::out_dst_file_raw | 1 << out_dst_type::out_dst_file_pkc | 1 << out_dst_type::out_dst_file_ipsv2 | 1 << out_dst_type::out_dst_file_libpcap,
          0, "out_pins_dst_filename_addon",
          "���������",
          "��������� ����� �����. "
          "������ �������� ������� ��������� ��������� ��� ��������. "
          "�������� ������� ��������� ����������� � ����� ��������� ����� ��� ��� ��������. \n"
          "������������� ��� ��������� ����� ����� ����� ���: \"<���_�����><���������>\" \n"
          ,cfg_out_pins_dst_filename_addon.data, PREFS_MAX_PATH, PINS_ARRAY_SIZE, &cfg_out_pins_count);

        prefs_register_bool_preference_arr(pref_out_pins, pref_out_pins_dst,
          1 << out_dst_type::out_dst_file_train | 1 << out_dst_type::out_dst_file_raw | 1 << out_dst_type::out_dst_file_pkc | 1 << out_dst_type::out_dst_file_ipsv2 | 1 << out_dst_type::out_dst_file_libpcap,
          0, "out_pins_has_append",
          "����� ����������",
          "����� ����������/���������. "
          "���� �������� �����, ������ ������ ������������ � ����� ����� (����� ����������). "
          "���� �������� �� �����, ���� ��������� ����� ������� ������ � ���� ������� ������ (����� ���������). "
          ,cfg_out_pins_has_append, PINS_ARRAY_SIZE, &cfg_out_pins_count);

      preference_p pref_out_pins_payload = prefs_register_enum_preference_arr(pref_out_pins, pref_out_pins_check, 0, 0, "out_pins_payload",
        "��� ��������",
        "��� ��������. "
        "�������� ���������� ��� ������, ������������ �� ������� ������. \n"
        "���� ������������ ����������: \n"
        "\n"
        " - FWD - �����, ���������� ������, ���������� �� ��������� ������������� \n"
        "\n"
        " - BLCK[:<index>] - �����, ���������� TCP/IP-������, ����������� ������������ ��� ���������� ����������� ������������� (<�������> ������ TCP-������ � ���������) \n"
        "\n"
        " - ALLIP[:<index>] - ���� IP-����� \n"
        "\n"
        " - VPN - ESP, AH, KERBEROS, PPTP, L2TP... (��� TCP-�������, TCP-�����: 500 - ISAKMP, 88 - KERBEROS, 49 - TACACS, 1723 - PPTP, 135 - BNE, 45 - CHECKPOINT; ��� UDP-�������, UDP-�����: 500 - ISAKMP, 88 - KERBEROS, 750 - KRB4, 1502 - SHIVA, 1549 - SHIVA, 1651 - SHIVA, 2233 - SHIVA, 1701 - L2TP, 1645 - RADIUS, 1812 - RADIUS, 1646 - RADACCT, 1813 - RADACCT, 49 - TACACS, 1111 - BNE) \n"
        "\n"
        " - VOIP - H.323, SIP, IAX, MGCP, TDMOIP, RTP, RTCP... (��� TCP-�������, TCP-�����: 1720 - H.323  CS, 1721 - H.323 CS2, 5060 - SIP; ��� UDP-�������, UDP-�����: 1718 - H.323 RAS1, 1719 - H.323 RAS2, 5060 - SIP, 2427 - MGCP, TDMOIP - 2142, IAX - 4569) \n"
        "\n"
        " - SVC - ICMP, DNS... (��� TCP-�������, TCP-�����: 53 - DNS, 5353 - DNS, 179 - BNE; ��� UDP-�������, UDP-�����: 53 - DNS, 5353 - DNS, 520 - RIP) \n"
        "\n"
        " - HTTP[:<index>] - HTTP-������ (��� TCP-�������, TCP-�����: 80 - HTTP, 3128 - PROXY HTTP, 3132 - ADMIN HTTP, 8080 - ALT HTTP, 8088 - RADAN HTTP, 3124 - ALT HTTP, 3127 - ALT HTTP, 3689 - DAAP, 11371 - HKP) \n"
        "\n"
        " - NOTHTTP[:<index>] - ���� IP-�����, ����� HTTP (ALLIP = HTTP + NOTHTTP) \n"
        "\n"
        " - MAIL[:<index>] - E-MAIL-������ (��� TCP-�������, TCP-�����: 25 - SMTP, 110 - POP3, 143 - IMAP) \n"
        "\n"
        " - FTP[:<index>] - FTP-������ (��� TCP-�������, TCP-�����: 20 - FTPDATA, 21 - FTP) \n"
        "\n"
        " - OTHTCP[:<index>] - ��������� TCP-������ \n"
        "\n"
        " - OTHUDP[:<index>] - ��������� UDP-������ \n"
        "\n"
        " - OTHIP[:<index>] - ��������� IP-������ (����� TCP � UDP) \n"
        "\n"
        " - THINTCP[:<index>] - �����, ���������� ������ ������������ TCP/IP-������: ���������� SYN (������), ���������� FIN|RST (�����) � ������ ������ � ������� (�� ������ � ������� �����������)  \n"
        "\n"
        " - IPV6 - IP-�������� ������ 6 \n"
        "\n"
        " - GRE - �������� GRE \n"
        "\n"
        " - IPIP - ��������� IP-IP (RFC 2003), IP-in-IP \n"
        "\n"
        " - UNK - ����������� ������ \n"
        "\n"
        ,cfg_out_pins_payload, cfg_out_pins_payload_enum, PINS_ARRAY_SIZE, &cfg_out_pins_count);

        prefs_register_csv_preference_arr(pref_out_pins, pref_out_pins_payload,
          (1 << 0) | (1 << 1),
          0, "out_pins_payload_wparam",
          "��������",
          "��������. "
          "��������� ���� ��������. "
          "��� ���� �������� \"���������������\": \n"
          "  ���������� ����� ���� ������ � ����������������� (������ ���� DUMMY), ������ �� ������� ��������� �������� �� ������ �����, ����� ���������. \n"
          "��� ���� �������� \"������\": \n"
          "  ��������� �������������� ��������� ����� �������� � ���� �������� �����. \n"
          "  ��������� �������� ���� �������� � �������� ���������������������. \n"
          "    <index> - ���� ����������, �� ��� �������� ������ ������ ���� � ���������� �������� \n"
          "    ������������ � ������ ��������������������� (�����������: �������� ������� ������ ���� ������ 0 ��� 1). \n"
          "    ���� ������ ����������� TCP/UDP-�����, �� ���������� �� TCP/UDP-������ �� ����� ��������������������, \n"
          "    �� ���� ����� ���������� �� ���� �������� �������, �������� � ������ ���������������������. \n"
          ,cfg_out_pins_payload_param.data, PREFS_MAX_PATH, PINS_ARRAY_SIZE, &cfg_out_pins_count);

      preference_p pref_out_pins_pid_lid_setter_check = prefs_register_bool_preference_arr(pref_out_pins, pref_out_pins_check, 0, 0, "out_pins_pid_lid_setter_check",
        "����������� PID/LID",
        "�������������� �������� PID/LID ��� ���. "
        "��������� ��������: \n"
        "  - 0 - �� ������������ \n"
        "  - 1 - ������������ \n"
        ,cfg_out_pins_pid_lid_setter_check, PINS_ARRAY_SIZE, &cfg_out_pins_count);

        preference_p pref_out_pins_has_set_pid = prefs_register_bool_preference_arr(pref_out_pins, pref_out_pins_pid_lid_setter_check, 0, 0, "out_pins_has_set_pid",
          "��������� PID",
          "��������� PID."
          ,cfg_out_pins_has_set_pid, PINS_ARRAY_SIZE, &cfg_out_pins_count);

          prefs_register_uint_preference_arr(pref_out_pins, pref_out_pins_has_set_pid, 0, 0, "out_pins_set_pid",
            "�������� PID",
            "�������� PID."
            "��������� \"set_pid\" � \"set_lid\" ���������� �������������� �������� PID � LID ��� ������� ���������� ������, "
            "�� ����, ��� ����������� ���������� ������, ��� ������������ �������� PID/LID ���������� �� ��������. "
            "�������� \"set_pid\" � \"set_lid\" �������� ����������. ��������, ���� ����� PID, �� �� ����� LID, "
            "����� ������� PID ������������� �����, � ������� LID - ���. "
            ,cfg_out_pins_set_pid, PINS_ARRAY_SIZE, &cfg_out_pins_count);

        preference_p pref_out_pins_has_set_lid = prefs_register_bool_preference_arr(pref_out_pins, pref_out_pins_pid_lid_setter_check, 0, 0, "out_pins_has_set_lid",
          "��������� LID",
          "��������� LID."
          ,cfg_out_pins_has_set_lid, PINS_ARRAY_SIZE, &cfg_out_pins_count);

          prefs_register_uint_preference_arr(pref_out_pins, pref_out_pins_has_set_lid, 0, 0, "out_pins_set_lid",
            "�������� LID",
            "�������� LID."
            "��������� \"set_pid\" � \"set_lid\" ���������� �������������� �������� PID � LID ��� ������� ���������� ������, "
            "�� ����, ��� ����������� ���������� ������, ��� ������������ �������� PID/LID ���������� �� ��������. "
            "�������� \"set_pid\" � \"set_lid\" �������� ����������. ��������, ���� ����� PID, �� �� ����� LID, "
            "����� ������� PID ������������� �����, � ������� LID - ���. "
            ,cfg_out_pins_set_lid, PINS_ARRAY_SIZE, &cfg_out_pins_count);

        preference_p pref_out_pins_has_set_pid_mask = prefs_register_bool_preference_arr(pref_out_pins, pref_out_pins_pid_lid_setter_check, 0, 0, "out_pins_has_set_pid_mask",
          "��������� PID-�����",
          "��������� PID-�����."
          ,cfg_out_pins_has_set_pid_mask, PINS_ARRAY_SIZE, &cfg_out_pins_count);

          prefs_register_uint_preference_arr(pref_out_pins, pref_out_pins_has_set_pid_mask, 0, 0, "out_pins_set_pid_mask",
            "�������� PID-�����",
            "�������� PID-�����."
            "��������� \"set_pid_mask\" � \"set_lid_mask\" ���������� ������������ �������� PID � LID ��� ������� ���������� ������, "
            "�� ����, ��� ����������� ���������� ������, ��� ������������ �������� PID/LID ����������� ���������� <�> � �������� ���������. "
            "�������� \"set_pid_mask\" � \"set_lid_mask\" �������� ����������. ��������, ���� ����� PID_MASK, �� �� ����� LID_MASK, "
            "����� ������� PID_MASK ������������� �����, � ������� LID_MASK - ���. "
            "���������� \"set_pid_mask\" � \"set_lid_mask\" ������� �� ����������� \"set_pid\" � \"set_lid\". "
            ,cfg_out_pins_set_pid_mask, PINS_ARRAY_SIZE, &cfg_out_pins_count);

        preference_p pref_out_pins_has_set_lid_mask = prefs_register_bool_preference_arr(pref_out_pins, pref_out_pins_pid_lid_setter_check, 0, 0, "out_pins_has_set_lid_mask",
          "��������� LID-�����",
          "��������� LID-�����."
          ,cfg_out_pins_has_set_lid_mask, PINS_ARRAY_SIZE, &cfg_out_pins_count);

          prefs_register_uint_preference_arr(pref_out_pins, pref_out_pins_has_set_lid_mask, 0, 0, "out_pins_set_lid_mask",
            "�������� LID-�����",
            "�������� LID-�����."
            "��������� \"set_pid_mask\" � \"set_lid_mask\" ���������� ������������ �������� PID � LID ��� ������� ���������� ������, "
            "�� ����, ��� ����������� ���������� ������, ��� ������������ �������� PID/LID ����������� ���������� <�> � �������� ���������. "
            "�������� \"set_pid_mask\" � \"set_lid_mask\" �������� ����������. ��������, ���� ����� PID_MASK, �� �� ����� LID_MASK, "
            "����� ������� PID_MASK ������������� �����, � ������� LID_MASK - ���. "
            "���������� \"set_pid_mask\" � \"set_lid_mask\" ������� �� ����������� \"set_pid\" � \"set_lid\". "
            ,cfg_out_pins_set_lid_mask, PINS_ARRAY_SIZE, &cfg_out_pins_count);

      prefs_register_bool_preference_arr(pref_out_pins, pref_out_pins_check, 0, 0, "out_pins_suppress_pid_lid_counting",
        "��������� �������� PID/LID-����������",
        "����������� ��� ��� ������� ���������� PID/LID-���, ������������ �� ������ �����. "
        "��������� ��������: \n"
        "  - 0 - ����������� �������� \n"
        "  - 1 - �� ����������� �������� \n"
        ,cfg_out_pins_suppress_pid_lid_counting, PINS_ARRAY_SIZE, &cfg_out_pins_count);

      preference_p pref_out_pins_has_buffer_size = prefs_register_bool_preference_arr(pref_out_pins, pref_out_pins_check, 0, 0, "out_pins_has_buffer_size",
        "�������������� �����",
        "������������ ��� ��� �������������� �����."
        ,cfg_out_pins_has_buffer_size, PINS_ARRAY_SIZE, &cfg_out_pins_count);

        prefs_register_uint_preference_arr(pref_out_pins, pref_out_pins_has_buffer_size, 0, 0, "out_pins_buffer_size",
          "������ ��������������� ������, �",
          "������ ��������������� ������, �. "
          "�������� \"out_pin_buffer_size\" ���������� ������������ ����������� ��������� (������ ����). "
          "�������� ���������� ��������� ����� �������������� ��� ������� ������������ ���������. "
          "�������� ����������� ��������� ������������ ��-���������. "
          ,cfg_out_pins_buffer_size, PINS_ARRAY_SIZE, &cfg_out_pins_count);

}

