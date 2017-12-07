/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/*
 * last update: 2010-04-17
 *
 * prefs_sample.cpp : example of prefs.h usage
 *
 * !ВНИМАНИЕ! Данный файл является только примером использования prefs.h и библиотеки prefs.ddl.
 * Запрещается компилировать данный файл с исходным именем.
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
guint cfg_snapshot_period = 600; // задается в секундах

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
gpchar cfg_pins_filename_any_filter = "Все файлы (*.*)|*.*";
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

  {in_src_type::in_src_file_train,      "файл - TRAIN"},
  {in_src_type::in_src_file_trainc,     "файл - TRAINC"},
  {in_src_type::in_src_file_libpcap,    "файл - LIBPCAP"},
  {in_src_type::in_src_file_train32,    "файл - TRAIN32"},
  {in_src_type::in_src_file_trainips32, "файл - TRAINIPS32"},
  {in_src_type::in_src_file_traintm,    "файл - TRAINTM"},
  {in_src_type::in_src_file_pkc,        "файл - PKC"},
  {in_src_type::in_src_file_raw,        "файл - RAW"},
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
  {SPEED_RESTRICTION_NONE,    "Нет" },
  {SPEED_RESTRICTION_SPEED,   "По скорости" },
  {SPEED_RESTRICTION_PACKETS, "Попакетно" },
  {SPEED_RESTRICTION_LIBPCAP, "Метки LIBPCAP" },
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

gpchar cfg_in_pins_filter_file_filter = _EN ? "Deflated teri (*.dtf)|*.dtf|Inflated teri (*.itf)|*.itf|All files (*.*)|*.*" : "Откомпилированный маршрут (*.dtf)|*.dtf|Неоткомпилированный маршрут (*.itf)|*.itf|Все файлы (*.*)|*.*";

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

  {out_dst_type::out_dst_file_train,      "файл - TRAIN"},
  {out_dst_type::out_dst_file_raw,        "файл - RAW"},
  {out_dst_type::out_dst_file_pkc,        "файл - PKC"},
  {out_dst_type::out_dst_file_ipsv2,      "файл - IP_STREAM v2"},
  {out_dst_type::out_dst_file_libpcap,    "файл - LIBPCAP"},

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
  {0xFFFF                 , "Перенаправление"},
  {0xFFFF                 , "Другое"},
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
      error = str(boost::format("Неверное значение параметра pid_lid_count: %d. Установлено значение по-умолчанию.") % *value);
      *value = 32;
      break;
    case vaVerify:
      error = str(boost::format("Неверное значение параметра pid_lid_count: %d.") % *value);
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
      error = str(boost::format("Неверное значение параметра container_size: %d. Установлено значение по-умолчанию.") % *value);
      *value = 1472;
      break;
    case vaVerify:
      error = str(boost::format("Неверное значение параметра container_size: %d.") % *value);
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
      error = str(boost::format("Неверное значение параметра out_pin_buffer_size: %d. Установлено значение по-умолчанию.") % *value);
      *value = 16*1024*1024;
      break;
    case vaVerify:
      error = str(boost::format("Неверное значение параметра out_pin_buffer_size: %d.") % *value);
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
      error = str(boost::format("Неверное значение параметра pid_lid_buffer_size: %d. Установлено значение по-умолчанию.") % *value);
      *value = 32*1024*1024;
      break;
    case vaVerify:
      error = str(boost::format("Неверное значение параметра pid_lid_buffer_size: %d.") % *value);
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
      error = str(boost::format("Неверное значение параметра ip_frag_time: %d. Установлено значение по-умолчанию.") % *value);
      *value = 1000;
      break;
    case vaVerify:
      error = str(boost::format("Неверное значение параметра ip_frag_time: %d.") % *value);
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
      error = str(boost::format("Неверное значение параметра ip_frag_count: %d. Установлено значение по-умолчанию.") % *value);
      *value = 8192;
      break;
    case vaVerify:
      error = str(boost::format("Неверное значение параметра ip_frag_count: %d.") % *value);
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
        error = _EN ? "Empty value unacceptable." : "Пустое значение недопустимо.";
        break;
      }
    }
    boost::smatch match; // Do regex match and convert the interesting part to int.
    if (regex_match(*sit, match, r_number)) {
      gint port = mscu_strtoint(match[0]);
      if ((port < 0) || (port > 0xffff)) {
        ++errors;
        if (action == vaVerify) {
          error = str(boost::format(_EN ? "Value is out of range: %d." : "Значение выходит за границы допустимого диапазона: %d.") % port);
          break;
        }
      }
      independent_tcp_ports[port >> 5] |= (guint32)1 << (port & 0x1f);
    } else {
      ++errors;
      if (action == vaVerify) {
        error = str(boost::format(_EN ? "Value is not a number: %s." : "Значение не является числом: %s.") % *sit);
        break;
      }
    }
  }

  if (errors > 0) {
    switch (action) {
    case vaCorrect:
    case vaApply:
      error = "В некоторых значениях обнаружены ошибки. Вызовите диалог изменения параметров для устранения ошибок.";
      break;
    case vaVerify:
      error = str(boost::format("Неверное значение параметра independent_tcp_ports: %s.") % (string(value)));
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
        error = _EN ? "Empty value unacceptable." : "Пустое значение недопустимо.";
        break;
      }
    }
    boost::smatch match; // Do regex match and convert the interesting part to int.
    if (regex_match(*sit, match, r_number)) {
      gint port = mscu_strtoint(match[0]);
      if ((port < 0) || (port > 0xffff)) {
        ++errors;
        if (action == vaVerify) {
          error = str(boost::format(_EN ? "Value is out of range: %d." : "Значение выходит за границы допустимого диапазона: %d.") % port);
          break;
        }
      }
      independent_udp_ports[port >> 5] |= (guint32)1 << (port & 0x1f);
    } else {
      ++errors;
      if (action == vaVerify) {
        error = str(boost::format(_EN ? "Value is not a number: %s." : "Значение не является числом: %s.") % *sit);
        break;
      }
    }
  }

  if (errors > 0) {
    switch (action) {
    case vaCorrect:
    case vaApply:
      error = "В некоторых значениях обнаружены ошибки. Вызовите диалог изменения параметров для устранения ошибок.";
      break;
    case vaVerify:
      error = str(boost::format("Неверное значение параметра independent_udp_ports: %s.") % (string(value)));
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
        error = _EN ? "Empty value unacceptable." : "Пустое значение недопустимо.";
        break;
      }
    }
    boost::smatch match; // Do regex match and convert the interesting part to int.
    if (regex_match(*sit, match, r_number)) {
      gint response = mscu_strtoint(match[0]);
      if ((response < 0) || (response > 999)) {
        ++errors;
        if (action == vaVerify) {
          error = str(boost::format(_EN ? "Value is out of range: %d." : "Значение выходит за границы допустимого диапазона: %d.") % response);
          break;
        }
      }
      tcpcat_http_responses[response] = true;
    } else {
      ++errors;
      if (action == vaVerify) {
        error = str(boost::format(_EN ? "Value is not a number: %s." : "Значение не является числом: %s.") % *sit);
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
      error = "В некоторых значениях обнаружены ошибки. Вызовите диалог изменения параметров для устранения ошибок.";
      break;
    case vaVerify:
      error = str(boost::format("Неверное значение параметра tcpcat_http_responses: %s.") % error.c_str());
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
        error = _EN ? "Empty value unacceptable." : "Пустое значение недопустимо.";
        break;
      }
    }
    boost::smatch match; // Do regex match and convert the interesting part to int.
    if (regex_match(*sit, match, r_number)) {
      gint port = mscu_strtoint(match[0]);
      if ((port < 0) || (port > 0xffff)) {
        ++errors;
        if (action == vaVerify) {
          error = str(boost::format(_EN ? "Value is out of range: %d." : "Значение выходит за границы допустимого диапазона: %d.") % port);
          break;
        }
      }
      in_pins_filter_tcp_ports[index][port >> 5] |= (guint32)1 << (port & 0x1f);
    } else {
      ++errors;
      if (action == vaVerify) {
        error = str(boost::format(_EN ? "Value is not a number: %s." : "Значение не является числом: %s.") % *sit);
        break;
      }
    }
  }

  if (errors > 0) {
    switch (action) {
    case vaCorrect:
    case vaApply:
      error = "В некоторых значениях обнаружены ошибки. Вызовите диалог изменения параметров для устранения ошибок.";
      break;
    case vaVerify:
      error = str(boost::format("Неверное значение параметра independent_tcp_ports: %s.") % (string(value)));
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
        error = _EN ? "Empty value unacceptable." : "Пустое значение недопустимо.";
        break;
      }
    }
    boost::smatch match; // Do regex match and convert the interesting part to int.
    if (regex_match(*sit, match, r_number)) {
      gint port = mscu_strtoint(match[0]);
      if ((port < 0) || (port > 0xffff)) {
        ++errors;
        if (action == vaVerify) {
          error = str(boost::format(_EN ? "Value is out of range: %d." : "Значение выходит за границы допустимого диапазона: %d.") % port);
          break;
        }
      }
      in_pins_filter_tcp_rem_ports[index][port >> 5] |= (guint32)1 << (port & 0x1f);
    } else {
      ++errors;
      if (action == vaVerify) {
        error = str(boost::format(_EN ? "Value is not a number: %s." : "Значение не является числом: %s.") % *sit);
        break;
      }
    }
  }

  if (errors > 0) {
    switch (action) {
    case vaCorrect:
    case vaApply:
      error = "В некоторых значениях обнаружены ошибки. Вызовите диалог изменения параметров для устранения ошибок.";
      break;
    case vaVerify:
      error = str(boost::format("Неверное значение параметра independent_tcp_ports: %s.") % (string(value)));
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
        error = _EN ? "Empty value unacceptable." : "Пустое значение недопустимо.";
        break;
      }
    }
    boost::smatch match; // Do regex match and convert the interesting part to int.
    if (regex_match(*sit, match, r_number)) {
      gint port = mscu_strtoint(match[0]);
      if ((port < 0) || (port > 0xffff)) {
        ++errors;
        if (action == vaVerify) {
          error = str(boost::format(_EN ? "Value is out of range: %d." : "Значение выходит за границы допустимого диапазона: %d.") % port);
          break;
        }
      }
      mux_pins_filter_tcp_ports[index][port >> 5] |= (guint32)1 << (port & 0x1f);
    } else {
      ++errors;
      if (action == vaVerify) {
        error = str(boost::format(_EN ? "Value is not a number: %s." : "Значение не является числом: %s.") % *sit);
        break;
      }
    }
  }

  if (errors > 0) {
    switch (action) {
    case vaCorrect:
    case vaApply:
      error = "В некоторых значениях обнаружены ошибки. Вызовите диалог изменения параметров для устранения ошибок.";
      break;
    case vaVerify:
      error = str(boost::format("Неверное значение параметра independent_tcp_ports: %s.") % (string(value)));
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
        error = _EN ? "Empty value unacceptable." : "Пустое значение недопустимо.";
        break;
      }
    }
    boost::smatch match; // Do regex match and convert the interesting part to int.
    if (regex_match(*sit, match, r_number)) {
      gint port = mscu_strtoint(match[0]);
      if ((port < 0) || (port > 0xffff)) {
        ++errors;
        if (action == vaVerify) {
          error = str(boost::format(_EN ? "Value is out of range: %d." : "Значение выходит за границы допустимого диапазона: %d.") % port);
          break;
        }
      }
      mux_pins_filter_tcp_rem_ports[index][port >> 5] |= (guint32)1 << (port & 0x1f);
    } else {
      ++errors;
      if (action == vaVerify) {
        error = str(boost::format(_EN ? "Value is not a number: %s." : "Значение не является числом: %s.") % *sit);
        break;
      }
    }
  }

  if (errors > 0) {
    switch (action) {
    case vaCorrect:
    case vaApply:
      error = "В некоторых значениях обнаружены ошибки. Вызовите диалог изменения параметров для устранения ошибок.";
      break;
    case vaVerify:
      error = str(boost::format("Неверное значение параметра independent_tcp_ports: %s.") % (string(value)));
      break;
    }
    Result = error.c_str();
  }

  return Result;
}

void register_prefs()
{
  preference_p pref_ide = prefs_register_module(0, "ide", "Вид",
    "Данная страница позволяет настроить общие параметры поведения приложения."
    , 0, 0);

  prefs_register_msec_preference(pref_ide, 0, 0, 0, "screensaver_ticks",
    _EN ? "Screensaver, ms" : "Заставка, мс",
    _EN ?
    "Given option defines the time, when elapsed, without any keyboard input, program goes to the screensaver mode. \n"
    "Press any key to return to the common mode. \n"
    "Given in milliseconds. \n"
    "Zero value turns off this function."
    :
    "Данный параметр определяет время, по прошествии которого, в случает отсутствия ввода с клавиатуры, приложение переходит в режим заставки. \n"
    "Вернуться в обычный режим можно путем нажатия любой клавиши. \n"
    "Задается в миллисекундах. \n"
    "Нулевое значение параметра отключает данную функцию."
    ,&cfg_screensaver_ticks);

  prefs_register_bool_preference(pref_ide, 0, 0, 0, "autohide_to_tray",
    _EN ? "Hide to tray at start" : "Скрывать при запуске",
    _EN ?
    "Automatically hide to system tray at program start."
    :
    "Автоматически скрывать приложение в системный трей при запуске."
    ,&cfg_autohide_to_tray);

  prefs_register_uint_preference(pref_ide, 0, 0, 0, "snapshot_period",
    "Период записи снимка состояния, с",
    "Период записи снимка состояния, задается в секундах. "
    "Если задано нулевое значение, запись снимка состояния не производится. "
    "Если задано ненулевое значение, то в файл сообщений с данным периодом будет записываться "
    "состояние процесса опработки (информационное содержимое всех консолей)."
    ,&cfg_snapshot_period);

  preference_p pref_common = prefs_register_module(0, "common", "Общие",
    "Данная страница позволяет настроить общие параметры работы приложения."
    , 1, 0);

  prefs_register_uint_preference(pref_common, 0, 0, 0, "virtual_avail_percent",
    "Порог свободной виртуальной памяти, %",
    "Минимально допустимый процент свободной виртуальной памяти процесса.\n"
    "Если процент свободной виртуальной памяти процесса становится меньше данного значения, приложение завершается.\n"
    "Нулевое значение отключает действие данного параметра.\n"
    ,&cfg_virtual_avail_percent);

  prefs_register_uint_preference(pref_common, 0, 0, 0, "socket_buffer_size",
    "Буфер сокета, б",
    "Размер буфера приемных/отправляющих сокетов. "
    "Задается в байтах. "
    "Данный параметр позволяет настроить операционную систему на более оптимальный "
    "прием данных по сети. "
    ,&cfg_socket_buffer_size);

  prefs_register_uint_preference(pref_common, 0, 0, 0, "wpcap_buffer_size",
    "WinPCap. Буфер адаптера, б",
    "Размер буфера драйвера для адаптера сетевого интерфейса. "
    "Задается в байтах. "
    "Данное значение следует увеличить в случае потерь при приеме пакетов.  "
    "Нулевое значение данного параметра не производит замену системного значения по умолчанию, которое равно 1 МБ. "
    ,&cfg_wpcap_buffer_size);

  prefs_register_uint_preference(pref_common, 0, 0, 0, "wpcap_mintocopy_size",
    "WinPCap. Гранулярность чтения, б",
    "Минимальный размер данных в приемном буфере, при котором драйвер отдает пакеты приложению. "
    "Задается в байтах. "
    "Данное значение следует увеличить в случае большой интенсивности поступления данных.  "
    "Этим можно добиться уменьшения числа системных вызовов и, следовательно, уменьшения нагрузки на процессор. "
    "Нулевое значение данного параметра не производит замену системного значения по умолчанию. "
    ,&cfg_wpcap_mintocopy_size);

  prefs_register_uint_preference(pref_common, 0, 0, container_size_validator, "container_size",
    "Контейнер, б",
    "Размер отправляемого контейнера. "
    "Задается в байтах. "
    "Данный параметр позволяет определить размер данных UDP/IP-пакетов (а также TRAIN-"
    "контейнеров внутри TCP/IP), передаваемых по сети. В случае высокоскоростной передачи "
    "(например, 1Gbit Ethernet) рекомендуется задавать большие значения (например, 16384). "
    "Значение параметра должно быть в пределах 8..65535, кратно 4. "
    "Фиксированные значения: 8192. "
    ,&cfg_container_size);

  prefs_register_bool_preference(pref_common, 0, 0, 0, "container_full_flush",
    "Контейнер - полный размер",
    "Отправлять только полноразмерные UDP-пакеты (только контейнеры с размером, заданным в параметре \"Контейнер\"). "
    "Возможные значения: \n"
    " - 0 - допустима отправка контейнеров с размером меньше заданного \n"
    " - 1 - отправлять только полноразмерные контейнеры \n"
    "Данный параметр позволяет определить поведение выходных потоков при отправке пакетов в формате \"Паровоз\" по UDP-сокету. \n"
    "Если параметр отключен, возможна отправка \"укороченных\" контейнеров. \n"
    "Если параметр включен, возможна отправка только полноразмерных контейнеров. В этом случае, если контейнер заполнен не полностью, оставшиеся байты контейнера заполняются нулями. \n"
    ,&cfg_container_full_flush);

  prefs_register_bool_preference(pref_common, 0, 0, 0, "pid_lid_ignore_pid",
    "Игнорировать PID-значение PID/LID-обработчика",
    "Игнорировать или нет PID-значение PID/LID-обработчика. "
    "Возможные значения: \n"
    " - 0 - не игнорировать \n"
    " - 1 - игнорировать \n"
    "Если данный флаг включен, PID/LID-обработчики создаются только по значению LID. "
    "Если данный флаг выключен, PID/LID-обработчики создаются по значению PID/LID. "
    "!Внимание! Если включены оба параметра \"Игнорировать PID-значение PID/LID-обработчика\" и \"Игнорировать LID-значение PID/LID-обработчика\", используется один общий PID/LID-обработчик и мультиплексоры игнорируются. "
    ,&cfg_pid_lid_ignore_pid);

  prefs_register_bool_preference(pref_common, 0, 0, 0, "pid_lid_ignore_lid",
    "Игнорировать LID-значение PID/LID-обработчика",
    "Игнорировать или нет LID-значение PID/LID-обработчика. "
    "Возможные значения: \n"
    " - 0 - не игнорировать \n"
    " - 1 - игнорировать \n"
    "Если данный флаг включен, PID/LID-обработчики создаются только по значению PID. "
    "Если данный флаг выключен, PID/LID-обработчики создаются по значению PID/LID. "
    "!Внимание! Если включены оба параметра \"Игнорировать PID-значение PID/LID-обработчика\" и \"Игнорировать LID-значение PID/LID-обработчика\", используется один общий PID/LID-обработчик и мультиплексоры игнорируются. "
    ,&cfg_pid_lid_ignore_lid);

  prefs_register_uint_preference(pref_common, 0, 0, pid_lid_buffer_size_validator, "pid_lid_buffer_size",
    "Буфер PID/LID обработчика, б",
    "Размер буфера PID/LID - обработчика. "
    "Задается в байтах. "
    "Данный параметр позволяет настроить протокольные обработчики на соответствующую "
    "скорость входных данных (размер буфера должен быть по крайней мере не меньше объема "
    "данных по любой PID/LID-паре, обрабатываемых за 1 секунду).Значение параметра должно быть в пределах от 16K. "
    ,&cfg_pid_lid_buffer_size);

  prefs_register_uint_preference(pref_common, 0, 0, pid_lid_count_validator, "pid_lid_count",
    "Количество PID/LID обработчиков, шт",
    "Максимальное количество PID/LID-обработчиков. "
    "Задается в шт. "
    "Данный параметр позволяет настроить максимальное количество создаваемых обработчик. "
    "Каждый обработчик обрабатывает уникальную пару PID/LID (все пакеты с данными "
    "значениями PID/LID). Каждый обработчик создает буфер в памяти, размером "
    "pid_lid_buffer_size. Соответственно, при большом количестве пар PID/LID, "
    "оперативной памяти может не хватить. Следовательно, необходимо задать количество "
    "PID/LID-обработчиков с учетом, что общая занимаемая оперативная память будет равна "
    "pid_lid_count * pid_lid_buffer_size байт. "
    "Значение параметра не должно быть равно 0. "
    ,&cfg_pid_lid_count);

  prefs_register_msec_preference(pref_common, 0, 0, 0, "pid_lid_msecs",
    "Время жизни PID/LID обработчиков, мс",
    "Время жизни PID/LID-обработчиков. "
    "Задается в миллисекундах. "
    "Данный параметр позволяет настроить удаление неактивных PID/LID-обработчиков, "
    "если за заданное время не приходило пакетов с соответствующим PID/LID. "
    "Рекомендуется задавать значения, значительно превышающие другие таймауты, используемые в протокольной обработке. "
    "Нулевой значение параметра отменяет данную функциональность. "
    ,&cfg_pid_lid_msecs);

  prefs_register_uint_preference(pref_common, 0, 0, out_pin_buffer_size_validator, "out_pin_buffer_size",
    "Буфер выходного потока, б",
    "Размер буфера выходного потока. "
    "Задается в байтах. "
    "Данный параметр позволяет настроить обработчики выходных потоков на соответствующую "
    "скорость обрабатываемых данных (размер буфера должен быть по крайней мере не "
    "меньше объема данных, обрабатываемых за 1 секунду). "
    "Значение параметра должно быть в пределах от 16K. "
    ,&cfg_out_pin_buffer_size);

  prefs_register_msec_preference(pref_common, 0, 0, 0, "activity_timeout",
    "Тайм-аут сборки, мс",
    "Тайм-аут буфера сборки выходного потока. "
    "Задается в миллисекундах. "
    "Если выходной поток неактивен в течении данного периода времени, контейнер с неполной "
    "длиной (container_size), но содержащий пакеты, принудительно отправляется. "
    "Если задано нулевое значение, принудительная отправка буфера не производится. "
    ,&cfg_activity_timeout);

  preference_p pref_control = prefs_register_module(0, "control", "Управление",
    "Данная страница позволяет настроить параметры управления."
    , 2, 0);

  prefs_register_bool_preference(pref_control, 0, 0, 0, "use_cps",
    "Система конвейерной обработки",
    "Использовать или нет взаимодействие с системой конвейерной обработки. \n"
    "Возможные значения: \n"
    "  - 0 - не использовать (по-умолчанию) \n"
    "  - 1 - использовать \n"
    "Если данный параметр включен: \n"
    "  - приложение загружает динамическую библиотеку \"CPSData_1.dll\" (Windows) \n"
    "  - периодически вызывается функция SendKeepAliveCPS \n"
    ,&cfg_use_cps);

  preference_p pref_statistics = prefs_register_module(0, "statistics", "Статистика",
    "Данная страница позволяет настроить параметры сбора статистики."
    , 3, 0);

  /*preference_p pref_teri = */prefs_register_module(0, "teri", "Отбор",
    "Данная страница позволяет настроить параметры отбора."
    , 4, 0);

  preference_p pref_dissect = prefs_register_module(0, "dissect", "Обработка",
    "Данная страница позволяет настроить параметры протокольной обработки."
    , 5, 0);

    prefs_register_bool_preference(pref_dissect, 0, 0, 0, "log_train_errors",
      "Выводить ошибки (\"Паровоз\")",
      "Выводить в журнал сообщений подробное описание ошибок, возникающих при чтении "
      "входных данных в формате <Паровоз> или нет. "
      "Возможные значения: \n"
      "  - 0 - не выводить \n"
      "  - 1 - выводить \n"
      "При  включенном значении  и  большом количестве  ошибок на  входе  происходит  резкое "
      "повышение использования процессора приложением. "
      ,&cfg_log_train_errors);

    prefs_register_bool_preference(pref_dissect, 0, 0, 0, "log_trainc_errors",
      "Выводить ошибки (\"Паровоз со счетчиком\")",
      "Выводить в журнал сообщений подробное описание ошибок, возникающих при чтении "
      "входных данных в формате <Паровоз со счетчиком> или нет. "
      "Возможные значения: \n"
      "  - 0 - не выводить \n"
      "  - 1 - выводить \n"
      "При  включенном значении  и  большом количестве  ошибок на  входе  происходит  резкое "
      "повышение использования процессора приложением. "
      ,&cfg_log_trainc_errors);

    prefs_register_uint_preference(pref_dissect, 0, 0, 0, "trainc_window_size",
      "Окно приема (\"Паровоз со счетчиком\"), шт",
      "Задается в шт. Данный параметр определяет количество входящих пакетов, которые накапливаются в окне "
      "приема. Это необходимо для сортировки поступления пакетов от разных источников с "
      "асинхронным значением счетчика. "
      ,&cfg_trainc_window_size);

    prefs_register_bool_preference(pref_dissect, 0, 0, 0, "trainc_crc_control",
      "Контроль CRC (\"Паровоз со счетчиком\")",
      "Если опция включена, то считается, что перед каждым пакетом (после PID и LID) находится 32-битное значение, определяющее качество CRC. "
      "Ненулевое значение определяет хорошее качество CRC, иначе - плохое. "
      "В таком случае пакеты с плохим CRC отбрасываются. "
      "Возможные значения: \n"
      "  - 0 - не контролировать \n"
      "  - 1 - контролировать \n"
      ,&cfg_trainc_crc_control);

    prefs_register_uint_preference(pref_dissect, 0, 0, 0, "proto_auto_packet_range",
      "Количество пакетов для автоопределения, шт",
      "Количество пакетов для автоопределения. "
      "Задается в шт. "
      "Данный параметр определяет количество входящих пакетов, на основании которых функция "
      "автоматического определения канального уровня пытается определить канальный уровень "
      "входного потока данных. "
      ,&cfg_proto_auto_packet_range);

    prefs_register_bool_preference(pref_dissect, 0, 0, 0, "ip_skip_checksum",
      "Не проверять контрольную сумму IP-пакета",
      "Проверять/не проверять контрольную сумму заголовка IP-пакета. "
      "Возможные значения: \n"
      "  - 0 - проверять \n"
      "  - 1 - не проверять (пропускать) \n"
      "При выключенном значении данного параметра производится проверка контрольной суммы "
      "заголовка IP-пакета. Если контрольная сумма очередного пакета оказывается неверной, "
      "пакет отбрасывается (при \"ip_ignore_bad_checksum=0\"). Если в данном случае все же "
      "необходима дальнейшая обработка таких пакетов, необходимо установить значение "
      "параметра ip_skip_checksum в \"1\". "
      ,&cfg_ip_skip_checksum);

    prefs_register_bool_preference(pref_dissect, 0, 0, 0, "ip_ignore_bad_checksum",
      "Игнорировать контрольную сумму IP-пакета",
      "Игнорировать/не игнорировать плохую контрольную сумму заголовка IP-пакета. "
      "Возможные значения: \n"
      "  - 0 - не игнорировать \n"
      "  - 1 - игнорировать \n"
      "При выключенном значении данного параметра (значение \"0\") IP-пакеты с плохой "
      "контрольной суммой отбрасываются. Если параметр включен (значение \"1\") , IP-пакеты с "
      "плохой контрольной суммой не отбрасываются и передаются на дальнейшую обработку. "
      ,&cfg_ip_ignore_bad_checksum);

    prefs_register_msec_preference(pref_dissect, 0, 0, ip_frag_time_validator, "ip_frag_time",
      "Таймаут сборки фрагментированных IP-пакетов, мс",
      "Таймаут буфера сборки фрагментированных IP-пакетов. "
      "Задается в миллисекундах. "
      "Если в течении данного периода времени для отдельного собираемого IP-пакета не "
      "поступает новый фрагмент, буфер сборки считается устаревшим и сборка данного IP-пакета "
      "прекращается (пакет теряется). "
      ,&cfg_ip_frag_time);

    prefs_register_uint_preference(pref_dissect, 0, 0, ip_frag_count_validator, "ip_frag_count",
      "Количество дефрагментируемых IP-пакетов",
      "Количество одновременно дефрагментируемых IP-пакетов. "
      "Максимальное количество собираемых IP-пакетов для одного обработчика. "
      "Обработчик определяется парой значений PID:LID. "
      "Если в определенный момент времени заняты все ip_frag_count буферов сборки и поступает "
      "начальный фрагмент нового IP-пакета, такой фрагмент отбрасывается. "
      ,&cfg_ip_frag_count);

    prefs_register_bool_preference(pref_dissect, 0, 0, 0, "ip_skip_checksum_recalc",
      "Не пересчитывать контрольную сумму IP-пакета",
      "Пропустить пересчитывание контрольной суммы заголовка дефрагментированного IP-пакета. "
      "Возможные значения: \n"
      "  - 0 - не игнорировать \n"
      "  - 1 - игнорировать \n"
      "Если параметр имеет ненулевое значение, то, при дефрагментации IP-пакетов, контрольная "
      "сумма после сборки  не пересчитывается и заполняется нулевым значением (0). Данная "
      "особенность предназначена для уменьшения времени обработки. При нулевом (0) значении "
      "параметра контрольная сумма пересчитывается для каждого собранного IP-пакета. "
      ,&cfg_ip_skip_checksum_recalc);

    prefs_register_bool_preference(pref_dissect, 0, 0, 0, "tcp_skip_checksum",
      "Не проверять контрольную сумму TCP-пакета",
      "Проверять/не проверять контрольную сумму TCP-пакета. "
      "Возможные значения: \n"
      "  - 0 - проверять \n"
      "  - 1 - не проверять (пропускать) \n"
      "При выключенном значении данного параметра производится проверка контрольной суммы "
      "TCP-пакета. Если контрольная сумма очередного пакета оказывается неверной, пакет "
      "отбрасывается  (при \"tcp_ignore_bad_checksum=0\"). Если в данном случае все же "
      "необходима дальнейшая обработка таких пакетов, необходимо установить значение "
      "параметра tcp_skip_checksum в \"1\". "
      ,&cfg_tcp_skip_checksum);

    prefs_register_bool_preference(pref_dissect, 0, 0, 0, "tcp_ignore_bad_checksum",
      "Игнорировать контрольную сумму TCP-пакета",
      "Игнорировать/не игнорировать плохую контрольную сумму TCP-пакета. "
      "Возможные значения: \n"
      "  - 0 - не игнорировать \n"
      "  - 1 - игнорировать \n"
      "При выключенном значении данного параметра (значение \"0\") TCP-пакеты с плохой "
      "контрольной суммой отбрасываются. Если параметр включен (значение \"1\") , TCP-пакеты с "
      "плохой контрольной суммой не отбрасываются и передаются на дальнейшую обработку. "
      ,&cfg_tcp_ignore_bad_checksum);

    prefs_register_bool_preference(pref_dissect, 0, 0, 0, "udp_skip_checksum",
      "Не проверять контрольную сумму UDP-пакета",
      "Проверять/не проверять контрольную сумму UDP-пакета. "
      "Возможные значения: \n"
      "  - 0 - проверять \n"
      "  - 1 - не проверять (пропускать) \n"
      "При выключенном значении данного параметра производится проверка контрольной суммы "
      "UDP-пакета. Если контрольная сумма очередного пакета оказывается неверной, пакет "
      "отбрасывается  (при \"udp_ignore_bad_checksum=0\"). Если в данном случае все же "
      "необходима дальнейшая обработка таких пакетов, необходимо установить значение "
      "параметра udp_skip_checksum в \"1\". "
      ,&cfg_udp_skip_checksum);

    prefs_register_bool_preference(pref_dissect, 0, 0, 0, "udp_ignore_bad_checksum",
      "Игнорировать контрольную сумму UDP-пакета",
      "Игнорировать/не игнорировать плохую контрольную сумму UDP-пакета. "
      "Возможные значения: \n"
      "  - 0 - не игнорировать \n"
      "  - 1 - игнорировать \n"
      "При выключенном значении данного параметра (значение \"0\") UDP-пакеты с плохой "
      "контрольной суммой отбрасываются. Если параметр включен (значение \"1\") , UDP-пакеты с "
      "плохой контрольной суммой не отбрасываются и передаются на дальнейшую обработку. "
      ,&cfg_udp_ignore_bad_checksum);

    prefs_register_bool_preference(pref_dissect, 0, 0, 0, "mpls_fix_lid",
      "Обновлять LID по MPLS-меткам",
      "Обновлять/не обновлять LID по MPLS-меткам. "
      "Возможные значения: \n"
      "  - 0 - не игнорировать \n"
      "  - 1 - игнорировать \n"
      "При включенном значении данного параметра (1) для каждого обрабатываемого MPLS-"
      "пакета производится подсчет совокупного значения стека MPLS-меток по определенному "
      "алгоритму (сложение по модулю 2). Вычисленное значение виртуального MPLS-канала "
      "заносится в поле LID пакета. "
      ,&cfg_mpls_fix_lid);

    preference_p pref_dissect_gre = prefs_register_bool_preference(pref_dissect, 0, 0, 0, "dissect_gre",
      "Обрабатывать GRE",
      "Призводить или нет обработку пакетов протокола GRE. "
      "Возможные значения: \n"
      "  - 0 - не производить \n"
      "  - 1 - производить \n"
      "При включенном значении данного параметра (1) производится обработка пакетов протокола GRE "
      "и выделение из них пакетов протоколов следующего уровня. "
      "В этом случае пакеты с вложенностью IP/GRE/IP будут дублировать друг друга для некоторых типо выходной нагрузки: "
      "выход типа ALLIP будет содержать пакет IP/GRE/IP, а также пакет IP, выделенный из вышеописанного пакета IP/GRE/IP."
      ,&cfg_dissect_gre);

    prefs_register_bool_preference(pref_dissect, pref_dissect_gre, 0, 0, "dissect_gre_alternative",
      "Избирательная обработка GRE",
      "Призводить или нет избирательную обработку пакетов протокола GRE. "
      "Возможные значения: \n"
      "  - 0 - не производить \n"
      "  - 1 - производить \n"
      "При включенном значении данного параметра (1) производится обработка пакетов протокола GRE "
      "и выделение из них пакетов протоколов следующего уровня только в случае, если внешний IP-пакет должен быть удален по признакам отбора/неотбора. "
      ,&cfg_dissect_gre_alternative);

    /*preference_p pref_dissect_gtp = */prefs_register_bool_preference(pref_dissect, 0, 0, 0, "dissect_gtp",
      "Обрабатывать GTP",
      "Призводить или нет обработку пакетов протокола GTP. "
      "Возможные значения: \n"
      "  - 0 - не производить \n"
      "  - 1 - производить \n"
      "При включенном значении данного параметра (1) производится обработка пакетов протокола GTP "
      "и выделение из них пакетов протоколов следующего уровня. "
      "В этом случае пакеты с вложенностью IP/GTP/IP будут дублировать друг друга для некоторых типо выходной нагрузки: "
      "выход типа ALLIP будет содержать пакет IP/GTP/IP, а также пакет IP, выделенный из вышеописанного пакета IP/GTP/IP."
      ,&cfg_dissect_gtp);

    prefs_register_csv_preference(pref_dissect, 0, 0, independent_tcp_ports_validator, "independent_tcp_ports",
      "Независимые TCP-порты",
      "Независимые TCP-порты. "
      "Возможные значения: список действительных значений TCP-портов. "
      "Данный параметр определяет список TCP-портов, на которые не влияет "
      "демультиплексирование цифровых потоков. Все пакеты с данными TCP-портами будут "
      "отправляться по всем выходным потокам, входящим в группы демультиплексирования. "
      ,cfg_independent_tcp_ports, sizeof(cfg_independent_tcp_ports));

    prefs_register_csv_preference(pref_dissect, 0, 0, independent_udp_ports_validator, "independent_udp_ports",
      "Независимые UDP-порты",
      "Независимые UDP-порты. "
      "Возможные значения: список действительных значений UDP-портов. "
      "Данный параметр определяет список UDP-портов, на которые не влияет "
      "демультиплексирование цифровых потоков. Все пакеты с данными UDP-портами будут "
      "отправляться по всем выходным потокам, входящим в группы демультиплексирования. "
      ,cfg_independent_udp_ports, sizeof(cfg_independent_udp_ports));

    preference_p pref_dissect_tcpcat = prefs_register_module(pref_dissect, "dissect_tcpcat", "TCP-сессии",
      "Данная страница позволяет настроить параметры контроля TCP-сессий."
      , 0, 0);

      preference_p pref_dissect_tcpcat_use = prefs_register_bool_preference(pref_dissect_tcpcat, 0, 0, 0, "tcpcat_use_iterator",
        "Контроль TCP-сессий",
        "Включить/выключить контроль TCP-сессий. "
        ,&cfg_tcpcat_use_iterator);

      prefs_register_bool_preference(pref_dissect_tcpcat, pref_dissect_tcpcat_use, 0, 0, "tcpcat_zap_wo_syn",
        "Удалять сессии без SYN (SYN/ACK)",
        "Удалять сессии без заголовка или нет. "
        "Заголовком считаются служебные пакеты с флагами SYN (SYN/ACK), определяющие открытие новой TCP-сессии. "
        "Если опция отключена (не рекомендуется), некоторые сессии будут сформированы не полностью (данные не сначала передачи). "
        ,&cfg_tcpcat_zap_wo_syn);

      prefs_register_msec_preference(pref_dissect_tcpcat, pref_dissect_tcpcat_use, 0, 0, "tcpcat_activity_time",
        "Время отсутствия активности сессии, мс",
        "Время, по истечении которого незакрытые сессии завершаются принудительно. "
        "Значение задается в миллисекундах. "
        "!Нулевое значение недопустимо! "
        ,&cfg_tcpcat_activity_time);

      prefs_register_msec_preference(pref_dissect_tcpcat, pref_dissect_tcpcat_use, 0, 0, "tcpcat_idle_granularity",
        "Период обновления состояний сеансов, мс",
        "Период обновления состояний сеансов. "
        "Значение задается в миллисекундах. "
        "Определяет периодичность пересчета временных значений таймаутов сеансов и обновления состояний. "
        "!Не может быть равно 0! "
        ,&cfg_tcpcat_idle_granularity);

      prefs_register_csv_preference(pref_dissect_tcpcat, pref_dissect_tcpcat_use, 0, tcpcat_http_responses_validator, "tcpcat_http_responses",
        "Фильтрация по кодам HTTP-отклика",
        "Фильтрация по кодам HTTP-отклика. "
        "Возможные значения: список разрешенных значений кодов HTTP-отклика. "
        "Данный параметр определяет список разрешенных кодов HTTP-отклика. Коды представляют собой трехзначные десятичные значения 1XX, 2XX, 3XX, 4XX, 5XX. Если фильтрация включена и внутри HTTP-сессии обнаружен завершающий отклик (с тегом \"Connection: close\"), значение которого не входит в список разрешенных значенний, то данная сессия становится заблокированной (все пакеты данной TCP-сессии отбрасываются). "
        "Пустое значение определяет, что фильтрация производиться не будет. "
        "Рекомендуемое значение - \"200;206;302\". "
        ,cfg_tcpcat_http_responses, sizeof(cfg_tcpcat_http_responses));

//////////////////////////////////////////////////////////////////////////
#define FILTER_DESCRIPTION \
      "Параметры определяют алгоритм фильтрации обрабатываемых пакетов: отбор (DVB MAC-адрес), неотбор (DVB MAC-адрес), отбор (IP-адрес), неотбор (IP-адрес), отбор (IP-адрес/TCP-порт), неотбор (IP-адрес/TCP-порт), отбор (IP-адрес/UDP-порт), неотбор (IP-адрес/UDP-порт), отбор (URL), неотбор (URL), отбор (Content-тип), неотбор (Content-тип), неотбор (текстовые признаки в начале сессии) соответственно. \n" \
        "Именование файлов: \n" \
        " - *.itf - Inflated Teri Format - признаки в нескомпилированном формате \n" \
        " - *.dtf - Deflated Teri Format - признаки в откомпилированном формате \n" \
        "В данном файле должны содержаться признаки в соответствующем виде: \n" \
        " - DVB MAC-адрес источника/приемника (область поиска - bMD) \n" \
        " - IP-адрес источника (область поиска - bIS) \n" \
        " - IP-адрес приемника (область поиска - bID) \n" \
        " - IP-адрес/TCP-порт источника (область поиска - bSTS) \n" \
        " - IP-адрес/TCP-порт приемника (область поиска - bSTD) \n" \
        " - IP-адрес/UDP-порт источника (область поиска - bSUS) \n" \
        " - IP-адрес/UDP-порт приемника (область поиска - bSUD) \n" \
        " - URL (область поиска - URL) \n" \
        " - MED (область поиска - MED - media-тип/content-type) \n" \
        " - SESSION HEADER - текстовые признаки, содержащиеся в первых пакетах сессии - по одному пакету в каждом направлении передачи данных (область поиска - T - текст) \n"

  preference_p pref_in_pins = prefs_register_module(0, "in_pins", "Входы",
    "Данная страница позволяет настроить параметры входов."
    , 6, 0);

    preference_p pref_in_pins_check = prefs_register_bool_preference_arr(pref_in_pins, 0, 0, 0, "in_pins_check",
      "Вход",
      "Использовать данный входной поток или нет. "
      "Возможные значения: \n"
      "  - 0 - не использовать \n"
      "  - 1 - использовать \n"
      ,cfg_in_pins_check, PINS_ARRAY_SIZE, &cfg_in_pins_count);

      prefs_register_string_preference_arr(pref_in_pins, pref_in_pins_check, 0, 0, "in_pins_name",
        "Имя",
        "Имя входного потока. "
        "Значение параметра задается в виде набора алфавитно-цифровых символов и служит для идентификации элемента (например, при связывании элементов между собой). "
        ,cfg_in_pins_name.data, PREFS_MAX_PATH, PINS_ARRAY_SIZE, &cfg_in_pins_count);

      preference_p pref_in_pins_src = prefs_register_enum_preference_arr(pref_in_pins, pref_in_pins_check, 0, 0, "in_pins_src",
        "Источник",
        "Источник. "
        "Параметр может иметь следующие значения: \n"
        "\n"
        "UDP/TCPS:<ip_address>:<port> TRAIN - тип входных данных - сетевое подключение, принимающее данные в формате \"Паровоз\". \n"
        "\n"
        "TCPS:<ip_address>:<port> TRAINS - тип входных данных - сетевое подключение, принимающее данные в модифицированном формате \"Паровоз\". Отличие - заголовок контейнера не используется. Длина пакетов выравнивается до 4 байт. Данный тип недоступен для UDP-соединений. \n"
        "\n"
        "UDP:<ip_address>:<port> TRAINC <PID> <LID> - тип входных данных - сетевое подключение, принимающее данные в модифицированном формате \"Паровоз\" - \"Паровоз со счетчиком\". Отличие - внутри поля LID содержится 16-битный счетчик пакета, сквозной для нескольких сетевых входов с оригинальным значением PID/LID (учитываются старшие 16 бит поля LID), определяющий порядок обработки пакетов. Все принимаемые пакеты должны иметь только данные значения PID <PID> и LID <LID>. В случае, если принимаемый пакет имеет другие значения, он отбрасывается и выдается соответствующее сообщение об ошибке.  \n"
        "\n"
        "TCPS:<ip_address>:<port> TRAINM - тип входных данных - сетевое подключение, принимающее данные в модифицированном формате \"Паровоз\". Отличие - заголовок контейнера не используется. Длина пакетов выравнивается до 4 байт. Поля PID/LID не учитываются в значении поля длины. Данный тип недоступен для UDP-соединений. \n"
        "\n"
        "UDP:<ip_address>:<port> TRAINM2 - тип входных данных - сетевое подключение, принимающее данные в модифицированном формате \"Паровоз\". Отличие - между полями PID и LID расположено служебное 32-битное поле (игнорируется). Данный тип недоступен для TCP-соединений. \n"
        "\n"
        "\"src=TCPS:<ip_address>:<port> SRM <PID>\" - тип входных данных - сетевое подключение, принимающее данные в следующем формате: \n"
        "  UNI(4) \n"
        "  Length(4) \n"
        "  TvSec(4) \n"
        "  TvUSec(4) \n"
        "  Length2(4) \n"
        "  Data(Length2) \n"
        " UNI - идентификатор признака отбора, которому принадлежит пакет с данными; \n"
        " Length - длина данных в байтах, передаваемых непосредственно за данным полем; \n"
        " TvSec - время приема пакета, задается в секундах; \n"
        " TvUSec - уточнение времени приема пакета, задается в микросекундах; \n"
        " Length2 - длина данных в байтах, передаваемых непосредственно за данным полем; \n"
        " Data - данные. \n"
        " Длина пакетов НЕ выравнивается до 4 байт. Все числовые поля имеют Intel-порядок байт (младший байт - первый), размер полей - 32 бита. Данный тип недоступен для UDP-соединений. \n"
        "\n"
        "UDP:<ip_address>:<port> RAW <размер_данных> <PID> <LID> - тип входных данных - сетевое подключение, принимающее данные в \"сыром\" формате. Данные каждого принятого пакета \"нарезаются\" на пакеты данных размером <размер_данных> (задается в байтах, не может быть больше 65536). Если значение <размер_данных> равен нулю, пакеты принимаются \"как есть\". Каждому пакету присваивается PID <PID> и LID <LID>. \n"
        "\n"
        "RAWS:<ip_address> RAW <PID> <LID>  - тип входных данных - сетевое подключение, принимающее данные в \"сыром\" формате через \"сырой\" сокет. Данное подключение функционирует как \"снифер\", принимая все IP-пакеты, передаваемые по сетевому интерфейсу, с заданным IP-адресом. Недопустимые значения для IP-адреса - 127.0.0.1 и 0.0.0.0. Каждому пакету присваивается PID <PID> и LID <LID>. \n"
        "\n"
        "Виды сетевых подключений: \n"
        " - UDP:<ip_address>:<port> - тип входных данных - сетевое подключение по локальному IP-адресу <ip_address> и UDP-порту <port> (UDP-сервер получатель) \n"
        " - TCPS:<ip_address>:<port> - тип входных данных - сетевое подключение по локальному IP-адресу <ip_address> и TCP-порту <port> (TCP-сервер получатель) \n"
        " - RAWS:<ip_address> - тип входных данных - \"сырое\" сетевое подключение по локальному IP-адресу <ip_address> (RAW-сокет) \n"
        "\n"
        "<имя_файла> TRAIN - тип входных данных - файл с именем <имя_файла>, содержащий пакеты в формате \"Паровоз\" (данные пакета не выровнены до 4 байт). Параметр \"<имя_файла>\" может содержать символы маски \"*\" и \"?\" для задания не одного, а группы файлов для чтения (например: \"c:\\in\\*\" - все файлы в каталоге \"c:\\in\\*\"). \n"
        "\n"
        "<имя_файла> TRAINC <PID> <LID> - тип входных данных - файл с именем <имя_файла>, содержащий пакеты в модифицированном формате \"Паровоз\" (данные пакета не выровнены до 4 байт). Отличие - внутри поля LID содержится 16-битный счетчик пакета, сквозной для нескольких сетевых входов с оригинальным значением PID/LID (учитываются старшие 16 бит поля LID), определяющий порядок обработки пакетов. Все принимаемые пакеты должны иметь только данные значения PID <PID> и LID <LID>. В случае, если принимаемый пакет имеет другие значения, он отбрасывается и выдается соответствующее сообщение об ошибке. Параметр \"<имя_файла>\" может содержать символы маски \"*\" и \"?\" для задания не одного, а группы файлов для чтения (например: \"c:\\in\\*\" - все файлы в каталоге \"c:\\in\\*\"). \n"
        "\n"
        "<имя_файла> TRAIN32 <PID> <LID> - тип входных данных - файл с именем <имя_файла>, содержащий пакеты в формате: <длина_пакета_32бита><данные>..<длина_пакета_32бита><данные>. Каждому пакету присваивается PID <PID> и LID <LID>. Параметр \"<имя_файла>\" может содержать символы маски \"*\" и \"?\" для задания не одного, а группы файлов для чтения (например: \"c:\\in\\*\" - все файлы в каталоге \"c:\\in\\*\"). \n"
        "\n"
        "<имя_файла> TRAINIPS32 <PID> <LID> - тип входных данных - файл с именем <имя_файла>, содержащий пакеты в формате: <длина_пакета_32бита><данные>..<длина_пакета_32бита><данные>. Первые 9 байт файла должны содержать \"магический\" набор байт - \"IP_STREAM\". Каждому пакету присваивается PID <PID> и LID <LID>. Параметр \"<имя_файла>\" может содержать символы маски \"*\" и \"?\" для задания не одного, а группы файлов для чтения (например: \"c:\\in\\*\" - все файлы в каталоге \"c:\\in\\*\"). \n"
        "\n"
        "<имя_файла> LIBPCAP <PID> <LID> - тип входных данных - файл с именем <имя_файла>, содержащий пакеты в формате: LibPCap/TCPDump/Wireshark. Каждому пакету присваивается PID <PID> и LID <LID>. Тип нагрузки, указанный в заголовке файла, не используется. Параметр \"<имя_файла>\" может содержать символы маски \"*\" и \"?\" для задания не одного, а группы файлов для чтения (например: \"c:\\in\\*\" - все файлы в каталоге \"c:\\in\\*\"). \n"
        "\n"
        "<имя_файла> TRAINTM <PID> <LID> - тип входных данных - файл с именем <имя_файла>, содержащий пакеты в формате: <временная_метка_32бита><IP-пакет>..<временная_метка_32бита><IP-пакет>. Каждому пакету присваивается PID <PID> и LID <LID>. Параметр \"<имя_файла>\" может содержать символы маски \"*\" и \"?\" для задания не одного, а группы файлов для чтения (например: \"c:\\in\\*\" - все файлы в каталоге \"c:\\in\\*\"). \n"
        "\n"
        "<имя_файла> RAW <размер_данных> <PID> <LID>  - тип входных данных - файл с именем <имя_файла>, содержащий пакеты в \"сыром\" формате. Данные файла \"нарезаются\" на пакеты данных размером <размер_данных> (задается в байтах).  Значение <размер_данных> не может быть равно нулю, не может быть больше 65536. Каждому пакету присваивается PID <PID> и LID <LID>. Параметр \"<имя_файла>\" может содержать символы маски \"*\" и \"?\" для задания не одного, а группы файлов для чтения (например: \"c:\\in\\*\" - все файлы в каталоге \"c:\\in\\*\"). \n"
        "\n"
        "<имя_файла> PKC <PID> <LID> - тип входных данных - файл с именем <имя_файла>, содержащий пакеты в формате: \"PKC\". Каждому пакету присваивается PID <PID> и LID <LID>. Параметр \"<имя_файла>\" может содержать символы маски \"*\" и \"?\" для задания не одного, а группы файлов для чтения (например: \"c:\\in\\*\" - все файлы в каталоге \"c:\\in\\*\"). \n"
        "  Формат пакета: \n"
        "    5B 5D XX XX 0D 0A пакет \n"
        "    где XX XX количество байт следующих за этим (длина пакета + 2 байта). \n"
        "\n"
        "PCAP<iface> RAW <PID> <LID>  - тип входных данных - захват пакетов сетевого интерфейса посредством WinPCap (должен быть установлен в системе). Данное подключение функционирует как \"снифер\", принимая все пакеты, передаваемые по сетевому интерфейсу (выбирается в дополнительном поле). Каждому пакету присваивается PID <PID> и LID <LID>. \n"
        "\n"
        ,cfg_in_pins_src, cfg_in_pins_src_enum, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_string_preference_arr(pref_in_pins, pref_in_pins_src,
          1 << in_src_type::in_src_net_udp_train | 1 << in_src_type::in_src_net_udp_trainc | 1 << in_src_type::in_src_net_udp_trainm2 | 1 << in_src_type::in_src_net_udp_raw |
          1 << in_src_type::in_src_net_tcps_train | 1 << in_src_type::in_src_net_tcps_trains | 1 << in_src_type::in_src_net_tcps_trainm |
          1 << in_src_type::in_src_net_tcps_srm | 1 << in_src_type::in_src_net_raws_raw,
          0, "in_pins_src_address",
          "Адрес",
          "Адрес. "
          "Значение данного параметра используется для уточнения некоторых типов источников (<ip_address>:<port>)."
          ,cfg_in_pins_src_address.data, PREFS_MAX_PATH, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_enum_preference_arr(pref_in_pins, pref_in_pins_src,
          1 << in_src_type::in_src_pcap,
          0, "in_pins_src_interface",
          "Интерфейс",
          "Интерфейс. "
          "Значение данного параметра используется для уточнения некоторых типов источников."
          ,cfg_in_pins_src_interface, wpcap_wrapper.interfaces_enum, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_file_preference_arr(pref_in_pins, pref_in_pins_src,
          1 << in_src_type::in_src_file_train | 1 << in_src_type::in_src_file_trainc | 1 << in_src_type::in_src_file_libpcap |
          1 << in_src_type::in_src_file_train32 | 1 << in_src_type::in_src_file_trainips32 | 1 << in_src_type::in_src_file_traintm |
          1 << in_src_type::in_src_file_raw | 1 << in_src_type::in_src_file_pkc,
          0, "in_pins_src_filename",
          "Файл",
          "Имя файла. "
          "Значение данного параметра используется для уточнения некоторых типов источников (<имя_файла>)."
          ,cfg_in_pins_src_filename.data, PREFS_MAX_PATH, cfg_pins_filename_any_filter, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_uint_preference_arr(pref_in_pins, pref_in_pins_src,
          1 << in_src_type::in_src_net_udp_trainc | 1 << in_src_type::in_src_net_udp_raw | 1 << in_src_type::in_src_net_raws_raw |
          1 << in_src_type::in_src_file_trainc | 1 << in_src_type::in_src_file_libpcap | 1 << in_src_type::in_src_file_train32 |
          1 << in_src_type::in_src_file_trainips32 | 1 << in_src_type::in_src_file_traintm | 1 << in_src_type::in_src_file_raw |
          1 << in_src_type::in_src_net_tcps_srm | 1 << in_src_type::in_src_pcap | 1 << in_src_type::in_src_file_pkc,
          0, "in_pins_src_pid",
          "PID",
          "PID. "
          "Значение данного параметра используется для уточнения некоторых типов источников (<PID>)."
          ,cfg_in_pins_src_pid, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_uint_preference_arr(pref_in_pins, pref_in_pins_src,
          1 << in_src_type::in_src_net_udp_trainc | 1 << in_src_type::in_src_net_udp_raw | 1 << in_src_type::in_src_net_raws_raw |
          1 << in_src_type::in_src_file_trainc | 1 << in_src_type::in_src_file_libpcap | 1 << in_src_type::in_src_file_train32 |
          1 << in_src_type::in_src_file_trainips32 | 1 << in_src_type::in_src_file_traintm | 1 << in_src_type::in_src_file_raw |
          /*1 << in_src_type::in_src_net_tcps_srm | */1 << in_src_type::in_src_pcap | 1 << in_src_type::in_src_file_pkc,
          0, "in_pins_src_lid",
          "LID",
          "LID. "
          "Значение данного параметра используется для уточнения некоторых типов источников (<LID>)."
          ,cfg_in_pins_src_lid, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_uint_preference_arr(pref_in_pins, pref_in_pins_src,
          1 << in_src_type::in_src_net_udp_raw | 1 << in_src_type::in_src_file_raw,
          0, "in_pins_src_snap",
          "Длина кадра",
          "Длина кадра. "
          "Значение данного параметра используется для уточнения некоторых типов источников (<размер_данных>)."
          ,cfg_in_pins_src_snap, PINS_ARRAY_SIZE, &cfg_in_pins_count);

      preference_p pref_in_pins_payload = prefs_register_enum_preference_arr(pref_in_pins, pref_in_pins_check, 0, 0, "in_pins_payload",
        "Тип нагрузки",
        "Тип нагрузки. "
        "Параметр определяет тип канального уровня принимаемых данных. \n"
        "Варианты типа потока: \n"
        " - AUTO - автоматическое определение вида нагрузки (канального уровня);\n"
        " - DUMMY - обработка потока не производится (прямое перенаправление на выходы);\n"
        " - NULL - обработка пакетов не производится, все пакеты трактуются как \"UNK - неизвестные данные\";\n"
        " - RAWIP <байты заголовка> <байты концевика> - неизвестный \"канальный\" уровень. Производится отсекание начала и конца пакета (количество отсекаемых байт задается через дополнительные числовые параметры <байты заголовка> <байты концевика>), оставшаяся часть считается IP-пакетом и производится его обработка. Если значение <байты заголовка> отрицательное, производится поиск начала заголовка IP-пакета в диапазоне с нулевого (0) байта по абсолютное положительное значение параметра <байты заголовка>;\n"
        " - ETH - прием и обработка Ethernet-кадров (без контрольной суммы);\n"
        " - CHDLC - прием и обработка пакетов Cisco HDLC с заголовком и контрольной суммой;\n"
        " - PPP - прием и обработка PPP-пакетов с заголовком и контрольной суммой;\n"
        " - DVB - прием и обработка DVB MPEG-TS кадров;\n"
        " - FR - прием и обработка FR-кадров с заголовком и контрольной суммой;\n"
        " - WLAN - прием и обработка IEEE 802.11-кадров (без контрольной суммы);\n"
        " - ATM [MSB] - прием и обработка ячеек ATM, сборка пакетов AAL 5, обработка нагрузки. Если задан дополнительный параметр MSB, производится разворот бит в байтах входного потока;\n"
        " - SATM [MSB] - прием и обработка ячеек ATM в потоке, сборка пакетов AAL 5, обработка нагрузки. Если задан дополнительный параметр MSB, производится разворот бит в байтах входного потока. Отличие от ATM заключается в том, что производится автоматическая синхронизация по правильности заголовка и HEC;\n"
        " - SHDLC [MSB|OCTET] <байты заголовка> <байты концевика> - снятие битовой процедуры HDLC, выделение IP-пакетов так же, как и в типе RAWIP (см. выше). ВНИМАНИЕ! Скорость снятия битовой процедуры HDLC составляет примерно 6 Мбайт/с на процессорах класса Intel(TM) Core(TM)2, 2 ГГц. Необходимо учитывать данный факт при обработке потоков большей скорости; \n"
        " - SHDLCM [MSB|OCTET] <байты заголовка> <байты концевика> - снятие битовой процедуры HDLC-M, выделение IP-пакетов так же, как и в типе RAWIP (см. выше). ВНИМАНИЕ! Скорость снятия битовой процедуры HDLC составляет примерно 6 Мбайт/с на процессорах класса Intel(TM) Core(TM)2, 2 ГГц. Необходимо учитывать данный факт при обработке потоков большей скорости; \n"
        " - SPPPHDLC [MSB|OCTET] - снятие битовой процедуры HDLC, выделение PPP-пакетов. ВНИМАНИЕ! Скорость снятия битовой процедуры HDLC составляет примерно 6 Мбайт/с на процессорах класса Intel(TM) Core(TM)2, 2 ГГц. Необходимо учитывать данный факт при обработке потоков большей скорости; \n"
        " - ATM AAL5 - обработка пакетов ATM уровня адаптации AAL 5, определение нагрузки; \n"
        " - SRAWIP. Производится поиск IP-пакетов по сигнатурным признакам и его обработка. Признаки: версия IP - 4, длина IP-заголовка - от 20 до 40 байт, длина IP-пакета - не более 16384, контрольная сумма IP-пакета - правильная;\n"
        ,cfg_in_pins_payload, cfg_in_pins_payload_enum, PINS_ARRAY_SIZE, &cfg_in_pins_count);

      prefs_register_uint_preference_arr(pref_in_pins, pref_in_pins_payload, (1 << 3) | (1 << 14) | (1 << 15) | (1 << 16) | (1 << 17) | (1 << 18), 0, "in_pins_payload_wparam",
        "Заголовок, б",
        "Заголовок, б. "
        "Значение данного параметра используется для уточнения некоторых типов нагрузки (<байты заголовка>)."
        ,cfg_in_pins_payload_wparam, PINS_ARRAY_SIZE, &cfg_in_pins_count);

      prefs_register_uint_preference_arr(pref_in_pins, pref_in_pins_payload, (1 << 3) | (1 << 14) | (1 << 15) | (1 << 16) | (1 << 17) | (1 << 18), 0, "in_pins_payload_lparam",
        "Концевик, б",
        "Концевик, б. "
        "Значение данного параметра используется для уточнения некоторых типов нагрузки (<байты концевика>)."
        ,cfg_in_pins_payload_lparam, PINS_ARRAY_SIZE, &cfg_in_pins_count);

      preference_p pref_in_pins_pid_lid_setter_check = prefs_register_bool_preference_arr(pref_in_pins, pref_in_pins_check, 0, 0, "in_pins_pid_lid_setter_check",
        "Модификация PID/LID",
        "Модифицировать значения PID/LID или нет. "
        "Возможные значения: \n"
        "  - 0 - не использовать \n"
        "  - 1 - использовать \n"
        ,cfg_in_pins_pid_lid_setter_check, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        preference_p pref_in_pins_has_set_pid = prefs_register_bool_preference_arr(pref_in_pins, pref_in_pins_pid_lid_setter_check, 0, 0, "in_pins_has_set_pid",
          "Установка PID",
          "Установка PID."
          ,cfg_in_pins_has_set_pid, PINS_ARRAY_SIZE, &cfg_in_pins_count);

          prefs_register_uint_preference_arr(pref_in_pins, pref_in_pins_has_set_pid, 0, 0, "in_pins_set_pid",
            "Значение PID",
            "Значение PID."
            "Параметры \"set_pid\" и \"set_lid\" определяют альтернативные значения PID и LID для каждого входящего пакета, "
            "то есть, при поступлении очередного пакета, его оригинальные значения PID/LID заменяются на заданные. "
            "Значения \"set_pid\" и \"set_lid\" задаются независимо. Например, если задан PID, но не задан LID, "
            "тогда подмена PID производиться будет, а подмена LID - нет. "
            ,cfg_in_pins_set_pid, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        preference_p pref_in_pins_has_set_lid = prefs_register_bool_preference_arr(pref_in_pins, pref_in_pins_pid_lid_setter_check, 0, 0, "in_pins_has_set_lid",
          "Установка LID",
          "Установка LID."
          ,cfg_in_pins_has_set_lid, PINS_ARRAY_SIZE, &cfg_in_pins_count);

          prefs_register_uint_preference_arr(pref_in_pins, pref_in_pins_has_set_lid, 0, 0, "in_pins_set_lid",
            "Значение LID",
            "Значение LID."
            "Параметры \"set_pid\" и \"set_lid\" определяют альтернативные значения PID и LID для каждого входящего пакета, "
            "то есть, при поступлении очередного пакета, его оригинальные значения PID/LID заменяются на заданные. "
            "Значения \"set_pid\" и \"set_lid\" задаются независимо. Например, если задан PID, но не задан LID, "
            "тогда подмена PID производиться будет, а подмена LID - нет. "
            ,cfg_in_pins_set_lid, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        preference_p pref_in_pins_has_set_pid_mask = prefs_register_bool_preference_arr(pref_in_pins, pref_in_pins_pid_lid_setter_check, 0, 0, "in_pins_has_set_pid_mask",
          "Установка PID-маски",
          "Установка PID-маски."
          ,cfg_in_pins_has_set_pid_mask, PINS_ARRAY_SIZE, &cfg_in_pins_count);

          prefs_register_uint_preference_arr(pref_in_pins, pref_in_pins_has_set_pid_mask, 0, 0, "in_pins_set_pid_mask",
            "Значение PID-маски",
            "Значение PID-маски."
            "Параметры \"set_pid_mask\" и \"set_lid_mask\" определяют маскирование значений PID и LID для каждого входящего пакета, "
            "то есть, при поступлении очередного пакета, его оригинальные значения PID/LID маскируются логическим <И> с заданным значением. "
            "Значения \"set_pid_mask\" и \"set_lid_mask\" задаются независимо. Например, если задан PID_MASK, но не задан LID_MASK, "
            "тогда подмена PID_MASK производиться будет, а подмена LID_MASK - нет. "
            "Применение \"set_pid_mask\" и \"set_lid_mask\" следует за применением \"set_pid\" и \"set_lid\". "
            ,cfg_in_pins_set_pid_mask, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        preference_p pref_in_pins_has_set_lid_mask = prefs_register_bool_preference_arr(pref_in_pins, pref_in_pins_pid_lid_setter_check, 0, 0, "in_pins_has_set_lid_mask",
          "Установка LID-маски",
          "Установка LID-маски."
          ,cfg_in_pins_has_set_lid_mask, PINS_ARRAY_SIZE, &cfg_in_pins_count);

          prefs_register_uint_preference_arr(pref_in_pins, pref_in_pins_has_set_lid_mask, 0, 0, "in_pins_set_lid_mask",
            "Значение LID-маски",
            "Значение LID-маски."
            "Параметры \"set_pid_mask\" и \"set_lid_mask\" определяют маскирование значений PID и LID для каждого входящего пакета, "
            "то есть, при поступлении очередного пакета, его оригинальные значения PID/LID маскируются логическим <И> с заданным значением. "
            "Значения \"set_pid_mask\" и \"set_lid_mask\" задаются независимо. Например, если задан PID_MASK, но не задан LID_MASK, "
            "тогда подмена PID_MASK производиться будет, а подмена LID_MASK - нет. "
            "Применение \"set_pid_mask\" и \"set_lid_mask\" следует за применением \"set_pid\" и \"set_lid\". "
            ,cfg_in_pins_set_lid_mask, PINS_ARRAY_SIZE, &cfg_in_pins_count);

      prefs_register_bool_preference_arr(pref_in_pins, pref_in_pins_check, 0, 0, "in_pins_suppress_pid_lid_counting",
        "Запретить контроль PID/LID-активности",
        "Производить или нет подсчет количества PID/LID-пар, поступаующих на данный вход. "
        "Возможные значения: \n"
        "  - 0 - производить контроль \n"
        "  - 1 - не производить контроль \n"
        ,cfg_in_pins_suppress_pid_lid_counting, PINS_ARRAY_SIZE, &cfg_in_pins_count);

      preference_p pref_in_pins_filter_check = prefs_register_bool_preference_arr(pref_in_pins, pref_in_pins_check, 0, 0, "in_pins_filter_check",
        "Фильтрация",
        "Использовать фильтрацию или нет. "
        "Возможные значения: \n"
        "  - 0 - не использовать \n"
        "  - 1 - использовать \n"
        ,cfg_in_pins_filter_check, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_file_preference_arr(pref_in_pins, pref_in_pins_filter_check, 0, 0, "in_pins_filter_dvb_mac",
          "Фильтр DVB MAC - отбор",
          "Фильтр DVB MAC - отбор."
          FILTER_DESCRIPTION
          ,cfg_in_pins_filter_dvb_mac.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_file_preference_arr(pref_in_pins, pref_in_pins_filter_check, 0, 0, "in_pins_filter_dvb_mac_rem",
          "Фильтр DVB MAC - неотбор",
          "Фильтр DVB MAC - неотбор."
          FILTER_DESCRIPTION
          ,cfg_in_pins_filter_dvb_mac_rem.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_file_preference_arr(pref_in_pins, pref_in_pins_filter_check, 0, 0, "in_pins_filter_ip",
          "Фильтр IP - отбор",
          "Фильтр IP - отбор."
          FILTER_DESCRIPTION
          ,cfg_in_pins_filter_ip.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_file_preference_arr(pref_in_pins, pref_in_pins_filter_check, 0, 0, "in_pins_filter_ip_rem",
          "Фильтр IP - неотбор",
          "Фильтр IP - неотбор."
          FILTER_DESCRIPTION
          ,cfg_in_pins_filter_ip_rem.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_csv_preference_arr(pref_in_pins, pref_in_pins_filter_check, 0, in_pins_filter_tcp_ports_validator, "in_pins_filter_tcp",
          "Фильтр TCP - отбор",
          "Фильтр TCP - отбор. "
          "Возможные значения: список действительных значений TCP-портов. "
          "Данный параметр определяет список действительных TCP-портов - пакеты с данными значениями портов будут "
          "отправляться на обработку, остальные - нет."
          "Пустое значение данного параметра определяет, что фильтрация по данному критерию производиться не будет. "
          ,cfg_in_pins_filter_tcp.data, PREFS_MAX_PATH, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_csv_preference_arr(pref_in_pins, pref_in_pins_filter_check, 0, in_pins_filter_tcp_rem_ports_validator, "in_pins_filter_tcp_rem",
          "Фильтр TCP - неотбор",
          "Фильтр TCP - неотбор. "
          "Возможные значения: список действительных значений TCP-портов. "
          "Данный параметр определяет список действительных TCP-портов - пакеты с данными значениями портов не будут "
          "отправляться на обработку, остальные - будут."
          "Пустое значение данного параметра определяет, что фильтрация по данному критерию производиться не будет. "
          ,cfg_in_pins_filter_tcp_rem.data, PREFS_MAX_PATH, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_file_preference_arr(pref_in_pins, pref_in_pins_filter_check, 0, 0, "in_pins_filter_ip_tcp",
          "Фильтр IP/TCP - отбор",
          "Фильтр IP/TCP - отбор."
          FILTER_DESCRIPTION
          ,cfg_in_pins_filter_ip_tcp.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_file_preference_arr(pref_in_pins, pref_in_pins_filter_check, 0, 0, "in_pins_filter_ip_tcp_rem",
          "Фильтр IP/TCP - неотбор",
          "Фильтр IP/TCP - неотбор."
          FILTER_DESCRIPTION
          ,cfg_in_pins_filter_ip_tcp_rem.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_file_preference_arr(pref_in_pins, pref_in_pins_filter_check, 0, 0, "in_pins_filter_ip_udp",
          "Фильтр IP/UDP - отбор",
          "Фильтр IP/UDP - отбор."
          FILTER_DESCRIPTION
          ,cfg_in_pins_filter_ip_udp.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_file_preference_arr(pref_in_pins, pref_in_pins_filter_check, 0, 0, "in_pins_filter_ip_udp_rem",
          "Фильтр IP/UDP - неотбор",
          "Фильтр IP/UDP - неотбор."
          FILTER_DESCRIPTION
          ,cfg_in_pins_filter_ip_udp_rem.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_file_preference_arr(pref_in_pins, pref_in_pins_filter_check, 0, 0, "in_pins_filter_url_rem",
          "Фильтр URL - неотбор",
          "Фильтр URL - неотбор."
          FILTER_DESCRIPTION
          ,cfg_in_pins_filter_url_rem.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_file_preference_arr(pref_in_pins, pref_in_pins_filter_check, 0, 0, "in_pins_filter_med_rem",
          "Фильтр MED - неотбор",
          "Фильтр MED - неотбор."
          FILTER_DESCRIPTION
          ,cfg_in_pins_filter_med_rem.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_file_preference_arr(pref_in_pins, pref_in_pins_filter_check, 0, 0, "in_pins_filter_session_header_rem",
          "Фильтр SESSION HEADER - неотбор",
          "Фильтр SESSION HEADER - неотбор."
          FILTER_DESCRIPTION
          ,cfg_in_pins_filter_session_header_rem.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_in_pins_count);

      preference_p pref_in_pins_has_set_delay = prefs_register_enum_preference_arr(pref_in_pins, pref_in_pins_src,
        1 << in_src_type::in_src_file_train | 1 << in_src_type::in_src_file_trainc | 1 << in_src_type::in_src_file_libpcap |
        1 << in_src_type::in_src_file_train32 | 1 << in_src_type::in_src_file_trainips32 | 1 << in_src_type::in_src_file_traintm |
        1 << in_src_type::in_src_file_raw | 1 << in_src_type::in_src_file_pkc,
        0, "in_pins_has_set_delay",
        "Ограничение скорости чтения",
        "Ограничение скорости чтения файлов."
        "По скорости: \n"
        "Параметр \"<Максимальная скорость чтения>\" используется только в случае чтения данных из файла и определяет искусственную задержку "
        "при чтении данных. \n"
        "Попакетно: \n"
        "Параметры \"<Количество пакетов>,<Время задержки>\" используется только в случае чтения данных из файла и определяет искусственную задержку "
        "при чтении данных: после чтения очередных <Количество пакетов> пакетов происходит \"засыпание\" читающего потока на <миллисекунды> миллисекунд. "
        "Поля <Количество пакетов> и <Время задержки> - числовые значения. Значение поля <Количество пакетов> не может быть равно 0!. Данная функциональность может "
        "использоваться для искусственного замедления потока чтения данных из файла. \n"
        "Метки LIBPCAP: \n"
        "Имитация реального времени с помощью установки задержек по меткам времени для каждого пакета, содержащихся в файлах формата LIBPCAP."
        ,cfg_in_pins_has_set_delay, cfg_in_pins_set_delay_enum, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_uint_preference_arr(pref_in_pins, pref_in_pins_has_set_delay, 1 << SPEED_RESTRICTION_SPEED, 0, "in_pins_set_delay_speed",
          "Максимальная скорость чтения, байт/с",
          "Максимальная скорость чтения данных из файла. \n"
          "Ввиду асинхронного характера процесса обработки, обработчики не имеют обратной связи с потоком чтения. \n"
          "Поэтому, \"медленные\" обработчики не имеют возможности \"притормозить\" поток чтения данных. \n"
          "Ограничение скорости гарантирует, что скорость не будет превышать заданного значения, если время обработки превышает 1 с. \n"
          "Задается в байтах в секунду. \n"
          "!Не может быть равно 0! \n"
          ,cfg_in_pins_set_delay_speed, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_uint_preference_arr(pref_in_pins, pref_in_pins_has_set_delay, 1 << SPEED_RESTRICTION_PACKETS, 0, "in_pins_set_delay_packets",
          "Количество пакетов, шт",
          "Количество пакетов, шт. \n"
          "!Не может быть равно 0! \n"
          ,cfg_in_pins_set_delay_packets, PINS_ARRAY_SIZE, &cfg_in_pins_count);

        prefs_register_msec_preference_arr(pref_in_pins, pref_in_pins_has_set_delay, 1 << SPEED_RESTRICTION_PACKETS, 0, "in_pins_set_delay_msecs",
          "Время задержки, мс",
          "Время задержки, мс. \n"
          "!Не может быть равно 0! \n"
          ,cfg_in_pins_set_delay_msecs, PINS_ARRAY_SIZE, &cfg_in_pins_count);

      prefs_register_bool_preference_arr(pref_in_pins, pref_in_pins_src,
        1 << in_src_type::in_src_file_train | 1 << in_src_type::in_src_file_trainc | 1 << in_src_type::in_src_file_libpcap |
        1 << in_src_type::in_src_file_train32 | 1 << in_src_type::in_src_file_trainips32 | 1 << in_src_type::in_src_file_traintm |
        1 << in_src_type::in_src_file_raw | 1 << in_src_type::in_src_file_pkc,
        0, "in_pins_has_cyclic",
        "Повторное сканирование",
        "Повторять опрос входного каталога после завершения обработки или нет."
        "Параметр используется только в случае чтения данных из файла и определяет циклический алгоритм чтения данных из файла: "
        "при достижении конца файла указатель чтения перемещается в начальную позицию. Таким образом достигается бесконечное чтение данных из файла. "
        ,cfg_in_pins_has_cyclic, PINS_ARRAY_SIZE, &cfg_in_pins_count);

      prefs_register_bool_preference_arr(pref_in_pins, pref_in_pins_src,
        1 << in_src_type::in_src_file_train | 1 << in_src_type::in_src_file_trainc | 1 << in_src_type::in_src_file_libpcap |
        1 << in_src_type::in_src_file_train32 | 1 << in_src_type::in_src_file_trainips32 | 1 << in_src_type::in_src_file_traintm |
        1 << in_src_type::in_src_file_raw | 1 << in_src_type::in_src_file_pkc,
        0, "in_pins_has_unlink",
        "Удалять файлы",
        "Удалять файлы после обработки или нет."
        "Параметр используется только в случае чтения данных из файла и предписывает удалять входные файлы после их обработки. "
        ,cfg_in_pins_has_unlink, PINS_ARRAY_SIZE, &cfg_in_pins_count);

//////////////////////////////////////////////////////////////////////////
  preference_p pref_mux_pins = prefs_register_module(0, "mux_pins", "Мультиплексоры",
    "Данная страница позволяет настроить параметры мультиплексоров. "
    "!Внимание! Если включены оба параметра \"Общие\\Игнорировать PID-значение PID/LID-обработчика\" и \"Общие\\Игнорировать LID-значение PID/LID-обработчика\", используется один общий PID/LID-обработчик и мультиплексоры игнорируются. "
    , 7, 0);

    preference_p pref_mux_pins_check = prefs_register_bool_preference_arr(pref_mux_pins, 0, 0, 0, "mux_pins_check",
      "Мультиплексор",
      "Использовать данный мультиплексор или нет. "
      "Возможные значения: \n"
      "  - 0 - не использовать \n"
      "  - 1 - использовать \n"
      ,cfg_mux_pins_check, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

      prefs_register_string_preference_arr(pref_mux_pins, pref_mux_pins_check, 0, 0, "mux_pins_name",
        "Имя",
        "Имя мультиплексора. "
        "Значение параметра задается в виде набора алфавитно-цифровых символов и служит для идентификации элемента (например, при связывании элементов между собой). "
        ,cfg_mux_pins_name.data, PREFS_MAX_PATH, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

      prefs_register_uint_preference_arr(pref_mux_pins, pref_mux_pins_check, 0, 0, "mux_pins_pid",
        "PID",
        "PID. "
        "Значение параметра определяет значение PID пары PID/LID, тип которой уточняется. "
        ,cfg_mux_pins_pid, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

      prefs_register_uint_preference_arr(pref_mux_pins, pref_mux_pins_check, 0, 0, "mux_pins_lid",
        "LID",
        "LID. "
        "Значение параметра определяет значение LID пары PID/LID, тип которой уточняется. "
        ,cfg_mux_pins_lid, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

      preference_p pref_mux_pins_payload = prefs_register_enum_preference_arr(pref_mux_pins, pref_mux_pins_check, 0, 0, "mux_pins_payload",
        "Тип нагрузки",
        "Тип нагрузки. "
        "Параметр определяет тип канального уровня принимаемых данных. \n"
        "Варианты типа потока: \n"
        " - AUTO - автоматическое определение вида нагрузки (канального уровня);\n"
        " - DUMMY - обработка потока не производится (прямое перенаправление на выходы);\n"
        " - NULL - обработка пакетов не производится, все пакеты трактуются как \"UNK - неизвестные данные\";\n"
        " - RAWIP <байты заголовка> <байты концевика> - неизвестный \"канальный\" уровень. Производится отсекание начала и конца пакета (количество отсекаемых байт задается через дополнительные числовые параметры <байты заголовка> <байты концевика>), оставшаяся часть считается IP-пакетом и производится его обработка. Если значение <байты заголовка> отрицательное, производится поиск начала заголовка IP-пакета в диапазоне с нулевого (0) байта по абсолютное положительное значение параметра <байты заголовка>;\n"
        " - ETH - прием и обработка Ethernet-кадров (без контрольной суммы);\n"
        " - CHDLC - прием и обработка пакетов Cisco HDLC с заголовком и контрольной суммой;\n"
        " - PPP - прием и обработка PPP-пакетов с заголовком и контрольной суммой;\n"
        " - DVB - прием и обработка DVB MPEG-TS кадров;\n"
        " - FR - прием и обработка FR-кадров с заголовком и контрольной суммой;\n"
        " - WLAN - прием и обработка IEEE 802.11-кадров (без контрольной суммы);\n"
        " - ATM [MSB] - прием и обработка ячеек ATM, сборка пакетов AAL 5, обработка нагрузки. Если задан дополнительный параметр MSB, производится разворот бит в байтах входного потока;\n"
        " - SATM [MSB] - прием и обработка ячеек ATM в потоке, сборка пакетов AAL 5, обработка нагрузки. Если задан дополнительный параметр MSB, производится разворот бит в байтах входного потока. Отличие от ATM заключается в том, что производится автоматическая синхронизация по правильности заголовка и HEC;\n"
        " - SHDLC [MSB|OCTET] <байты заголовка> <байты концевика> - снятие битовой процедуры HDLC, выделение IP-пакетов так же, как и в типе RAWIP (см. выше). ВНИМАНИЕ! Скорость снятия битовой процедуры HDLC составляет примерно 6 Мбайт/с на процессорах класса Intel(TM) Core(TM)2, 2 ГГц. Необходимо учитывать данный факт при обработке потоков большей скорости; \n"
        " - SHDLCM [MSB|OCTET] <байты заголовка> <байты концевика> - снятие битовой процедуры HDLC-M, выделение IP-пакетов так же, как и в типе RAWIP (см. выше). ВНИМАНИЕ! Скорость снятия битовой процедуры HDLC составляет примерно 6 Мбайт/с на процессорах класса Intel(TM) Core(TM)2, 2 ГГц. Необходимо учитывать данный факт при обработке потоков большей скорости; \n"
        " - SPPPHDLC [MSB|OCTET] - снятие битовой процедуры HDLC, выделение PPP-пакетов. ВНИМАНИЕ! Скорость снятия битовой процедуры HDLC составляет примерно 6 Мбайт/с на процессорах класса Intel(TM) Core(TM)2, 2 ГГц. Необходимо учитывать данный факт при обработке потоков большей скорости; \n"
        " - ATM AAL5 - обработка пакетов ATM уровня адаптации AAL 5, определение нагрузки; \n"
        ,cfg_mux_pins_payload, cfg_in_pins_payload_enum, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        prefs_register_uint_preference_arr(pref_mux_pins, pref_mux_pins_payload, (1 << 3) | (1 << 14) | (1 << 15) | (1 << 16) | (1 << 17) | (1 << 18), 0, "mux_pins_payload_wparam",
          "Заголовок, б",
          "Заголовок, б. "
          "Значение данного параметра используется для уточнения некоторых типов нагрузки (<байты заголовка>)."
          ,cfg_mux_pins_payload_wparam, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        prefs_register_uint_preference_arr(pref_mux_pins, pref_mux_pins_payload, (1 << 3) | (1 << 14) | (1 << 15) | (1 << 16) | (1 << 17) | (1 << 18), 0, "mux_pins_payload_lparam",
          "Концевик, б",
          "Концевик, б. "
          "Значение данного параметра используется для уточнения некоторых типов нагрузки (<байты концевика>)."
          ,cfg_mux_pins_payload_lparam, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

      preference_p pref_mux_pins_pid_lid_setter_check = prefs_register_bool_preference_arr(pref_mux_pins, pref_mux_pins_check, 0, 0, "mux_pins_pid_lid_setter_check",
        "Модификация PID/LID",
        "Модифицировать значения PID/LID или нет. "
        "Возможные значения: \n"
        "  - 0 - не использовать \n"
        "  - 1 - использовать \n"
        ,cfg_mux_pins_pid_lid_setter_check, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        preference_p pref_mux_pins_has_set_pid = prefs_register_bool_preference_arr(pref_mux_pins, pref_mux_pins_pid_lid_setter_check, 0, 0, "mux_pins_has_set_pid",
          "Установка PID",
          "Установка PID."
          ,cfg_mux_pins_has_set_pid, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

          prefs_register_uint_preference_arr(pref_mux_pins, pref_mux_pins_has_set_pid, 0, 0, "mux_pins_set_pid",
            "Значение PID",
            "Значение PID."
            "Параметры \"set_pid\" и \"set_lid\" определяют альтернативные значения PID и LID для каждого входящего пакета, "
            "то есть, при поступлении очередного пакета, его оригинальные значения PID/LID заменяются на заданные. "
            "Значения \"set_pid\" и \"set_lid\" задаются независимо. Например, если задан PID, но не задан LID, "
            "тогда подмена PID производиться будет, а подмена LID - нет. "
            ,cfg_mux_pins_set_pid, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        preference_p pref_mux_pins_has_set_lid = prefs_register_bool_preference_arr(pref_mux_pins, pref_mux_pins_pid_lid_setter_check, 0, 0, "mux_pins_has_set_lid",
          "Установка LID",
          "Установка LID."
          ,cfg_mux_pins_has_set_lid, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

          prefs_register_uint_preference_arr(pref_mux_pins, pref_mux_pins_has_set_lid, 0, 0, "mux_pins_set_lid",
            "Значение LID",
            "Значение LID."
            "Параметры \"set_pid\" и \"set_lid\" определяют альтернативные значения PID и LID для каждого входящего пакета, "
            "то есть, при поступлении очередного пакета, его оригинальные значения PID/LID заменяются на заданные. "
            "Значения \"set_pid\" и \"set_lid\" задаются независимо. Например, если задан PID, но не задан LID, "
            "тогда подмена PID производиться будет, а подмена LID - нет. "
            ,cfg_mux_pins_set_lid, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        preference_p pref_mux_pins_has_set_pid_mask = prefs_register_bool_preference_arr(pref_mux_pins, pref_mux_pins_pid_lid_setter_check, 0, 0, "mux_pins_has_set_pid_mask",
          "Установка PID-маски",
          "Установка PID-маски."
          ,cfg_mux_pins_has_set_pid_mask, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

          prefs_register_uint_preference_arr(pref_mux_pins, pref_mux_pins_has_set_pid_mask, 0, 0, "mux_pins_set_pid_mask",
            "Значение PID-маски",
            "Значение PID-маски."
            "Параметры \"set_pid_mask\" и \"set_lid_mask\" определяют маскирование значений PID и LID для каждого входящего пакета, "
            "то есть, при поступлении очередного пакета, его оригинальные значения PID/LID маскируются логическим <И> с заданным значением. "
            "Значения \"set_pid_mask\" и \"set_lid_mask\" задаются независимо. Например, если задан PID_MASK, но не задан LID_MASK, "
            "тогда подмена PID_MASK производиться будет, а подмена LID_MASK - нет. "
            "Применение \"set_pid_mask\" и \"set_lid_mask\" следует за применением \"set_pid\" и \"set_lid\". "
            ,cfg_mux_pins_set_pid_mask, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        preference_p pref_mux_pins_has_set_lid_mask = prefs_register_bool_preference_arr(pref_mux_pins, pref_mux_pins_pid_lid_setter_check, 0, 0, "mux_pins_has_set_lid_mask",
          "Установка LID-маски",
          "Установка LID-маски."
          ,cfg_mux_pins_has_set_lid_mask, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

          prefs_register_uint_preference_arr(pref_mux_pins, pref_mux_pins_has_set_lid_mask, 0, 0, "mux_pins_set_lid_mask",
            "Значение LID-маски",
            "Значение LID-маски."
            "Параметры \"set_pid_mask\" и \"set_lid_mask\" определяют маскирование значений PID и LID для каждого входящего пакета, "
            "то есть, при поступлении очередного пакета, его оригинальные значения PID/LID маскируются логическим <И> с заданным значением. "
            "Значения \"set_pid_mask\" и \"set_lid_mask\" задаются независимо. Например, если задан PID_MASK, но не задан LID_MASK, "
            "тогда подмена PID_MASK производиться будет, а подмена LID_MASK - нет. "
            "Применение \"set_pid_mask\" и \"set_lid_mask\" следует за применением \"set_pid\" и \"set_lid\". "
            ,cfg_mux_pins_set_lid_mask, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

      preference_p pref_mux_pins_filter_check = prefs_register_bool_preference_arr(pref_mux_pins, pref_mux_pins_check, 0, 0, "mux_pins_filter_check",
        "Фильтрация",
        "Использовать фильтрацию или нет. "
        "Возможные значения: \n"
        "  - 0 - не использовать \n"
        "  - 1 - использовать \n"
        ,cfg_mux_pins_filter_check, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        prefs_register_file_preference_arr(pref_mux_pins, pref_mux_pins_filter_check, 0, 0, "mux_pins_filter_dvb_mac",
          "Фильтр DVB MAC - отбор",
          "Фильтр DVB MAC - отбор."
          FILTER_DESCRIPTION
          ,cfg_mux_pins_filter_dvb_mac.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        prefs_register_file_preference_arr(pref_mux_pins, pref_mux_pins_filter_check, 0, 0, "mux_pins_filter_dvb_mac_rem",
          "Фильтр DVB MAC - неотбор",
          "Фильтр DVB MAC - неотбор."
          FILTER_DESCRIPTION
          ,cfg_mux_pins_filter_dvb_mac_rem.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        prefs_register_file_preference_arr(pref_mux_pins, pref_mux_pins_filter_check, 0, 0, "mux_pins_filter_ip",
          "Фильтр IP - отбор",
          "Фильтр IP - отбор."
          FILTER_DESCRIPTION
          ,cfg_mux_pins_filter_ip.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        prefs_register_file_preference_arr(pref_mux_pins, pref_mux_pins_filter_check, 0, 0, "mux_pins_filter_ip_rem",
          "Фильтр IP - неотбор",
          "Фильтр IP - неотбор."
          FILTER_DESCRIPTION
          ,cfg_mux_pins_filter_ip_rem.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        prefs_register_csv_preference_arr(pref_mux_pins, pref_mux_pins_filter_check, 0, mux_pins_filter_tcp_ports_validator, "mux_pins_filter_tcp",
          "Фильтр TCP - отбор",
          "Фильтр TCP - отбор. "
          "Возможные значения: список действительных значений TCP-портов. "
          "Данный параметр определяет список действительных TCP-портов - пакеты с данными значениями портов будут "
          "отправляться на обработку, остальные - нет."
          "Пустое значение данного параметра определяет, что фильтрация по данному критерию производиться не будет. "
          ,cfg_mux_pins_filter_tcp.data, PREFS_MAX_PATH, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        prefs_register_csv_preference_arr(pref_mux_pins, pref_mux_pins_filter_check, 0, mux_pins_filter_tcp_rem_ports_validator, "mux_pins_filter_tcp_rem",
          "Фильтр TCP - неотбор",
          "Фильтр TCP - неотбор. "
          "Возможные значения: список действительных значений TCP-портов. "
          "Данный параметр определяет список действительных TCP-портов - пакеты с данными значениями портов не будут "
          "отправляться на обработку, остальные - будут."
          "Пустое значение данного параметра определяет, что фильтрация по данному критерию производиться не будет. "
          ,cfg_mux_pins_filter_tcp_rem.data, PREFS_MAX_PATH, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        prefs_register_file_preference_arr(pref_mux_pins, pref_mux_pins_filter_check, 0, 0, "mux_pins_filter_ip_tcp",
          "Фильтр IP/TCP - отбор",
          "Фильтр IP/TCP - отбор."
          FILTER_DESCRIPTION
          ,cfg_mux_pins_filter_ip_tcp.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        prefs_register_file_preference_arr(pref_mux_pins, pref_mux_pins_filter_check, 0, 0, "mux_pins_filter_ip_tcp_rem",
          "Фильтр IP/TCP - неотбор",
          "Фильтр IP/TCP - неотбор."
          FILTER_DESCRIPTION
          ,cfg_mux_pins_filter_ip_tcp_rem.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        prefs_register_file_preference_arr(pref_mux_pins, pref_mux_pins_filter_check, 0, 0, "mux_pins_filter_ip_udp",
          "Фильтр IP/UDP - отбор",
          "Фильтр IP/UDP - отбор."
          FILTER_DESCRIPTION
          ,cfg_mux_pins_filter_ip_udp.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        prefs_register_file_preference_arr(pref_mux_pins, pref_mux_pins_filter_check, 0, 0, "mux_pins_filter_ip_udp_rem",
          "Фильтр IP/UDP - неотбор",
          "Фильтр IP/UDP - неотбор."
          FILTER_DESCRIPTION
          ,cfg_mux_pins_filter_ip_udp_rem.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        prefs_register_file_preference_arr(pref_mux_pins, pref_mux_pins_filter_check, 0, 0, "mux_pins_filter_url_rem",
          "Фильтр URL - неотбор",
          "Фильтр URL - неотбор."
          FILTER_DESCRIPTION
          ,cfg_mux_pins_filter_url_rem.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        prefs_register_file_preference_arr(pref_mux_pins, pref_mux_pins_filter_check, 0, 0, "mux_pins_filter_med_rem",
          "Фильтр MED - неотбор",
          "Фильтр MED - неотбор."
          FILTER_DESCRIPTION
          ,cfg_mux_pins_filter_med_rem.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

        prefs_register_file_preference_arr(pref_mux_pins, pref_mux_pins_filter_check, 0, 0, "mux_pins_filter_session_header_rem",
          "Фильтр SESSION HEADER - неотбор",
          "Фильтр SESSION HEADER - неотбор."
          FILTER_DESCRIPTION
          ,cfg_mux_pins_filter_session_header_rem.data, PREFS_MAX_PATH, cfg_in_pins_filter_file_filter, PINS_ARRAY_SIZE, &cfg_mux_pins_count);

//////////////////////////////////////////////////////////////////////////
  preference_p pref_out_pins = prefs_register_module(0, "out_pins", "Выходы",
    "Данная страница позволяет настроить параметры выходов."
    , 8, 0);

    preference_p pref_out_pins_check = prefs_register_bool_preference_arr(pref_out_pins, 0, 0, 0, "out_pins_check",
      "Выход",
      "Использовать данный выходной поток или нет. "
      "Возможные значения: \n"
      "  - 0 - не использовать \n"
      "  - 1 - использовать \n"
      ,cfg_out_pins_check, PINS_ARRAY_SIZE, &cfg_out_pins_count);

      prefs_register_string_preference_arr(pref_out_pins, pref_out_pins_check, 0, 0, "out_pins_name",
        "Имя",
        "Имя выходного потока. "
        "Значение параметра задается в виде набора алфавитно-цифровых символов и служит для идентификации элемента (например, при связывании элементов между собой). "
        ,cfg_out_pins_name.data, PREFS_MAX_PATH, PINS_ARRAY_SIZE, &cfg_out_pins_count);

      preference_p pref_out_pins_dst = prefs_register_enum_preference_arr(pref_out_pins, pref_out_pins_check, 0, 0, "out_pins_dst",
        "Назначение",
        "Назначение. "
        "Параметр может иметь следующие значения: \n"
        "\n"
        "NULL - данные никуда не попадают, просто удаляются (используются для контроля поступления данных определенного типа). \n"
        "\n"
        "CALLBACK - данные передаются зарегистрированной функции обратного вызова. Внимание! Данный тип используется только для библиотечного варианта приложения - libcenzor.dll. \n"
        "\n"
        "UDP/TCPC:<ip_address>:<port> TRAIN  - пакеты данных отправляются по сетевому подключению, в формате \"Паровоз\". \n"
        "\n"
        "TCPC:<ip_address>:<port> TRAINS  - пакеты данных отправляются по сетевому подключению, в модифицированном формате \"Паровоз\". Отличие - заголовок контейнера не используется. Длина пакетов выравнивается до 4 байт. Данный тип недоступен для UDP-соединений. \n"
        "\n"
        "TCPC:<ip_address>:<port> TRAINM  - пакеты данных отправляются по сетевому подключению, в модифицированном формате \"Паровоз\". Отличие - заголовок контейнера не используется. Длина пакетов выравнивается до 4 байт. Поля PID/LID не учитываются в значении поля длины. Данный тип недоступен для UDP-соединений. \n"
        "\n"
        "dst=TCPC:<ip_address>:<port> SRM  - пакеты данных отправляются по сетевому подключению, в следующем формате: \n"
        "  UNI(4)|Length(4)|TvSec(4)|TvUSec(4)|Length2(4)|Data(Length2) \n"
        "    UNI - идентификатор признака отбора, которому принадлежит пакет с данными;\n"
        "    Length - длина данных в байтах, передаваемых непосредственно за данным полем;\n"
        "    TvSec - время приема пакета, задается в секундах;\n"
        "    TvUSec - уточнение времени приема пакета, задается в микросекундах;\n"
        "    Length2 - длина данных в байтах, передаваемых непосредственно за данным полем;\n"
        "    Data - данные.\n"
        "    Длина пакетов НЕ выравнивается до 4 байт. Все числовые поля имеют сетвой порядок байт, размер полей - 32 бита. Данный тип недоступен для UDP-соединений. \n"
        "\n"
        "UDP/TCPC:<ip_address>:<port> RAW  - пакеты данных отправляются по сетевому подключению, в \"сыром\" формате (пакеты данных ничем не обрамляются). \n"
        "\n"
        "Виды сетевых подключений: \n"
        " - UDP:<ip_address>:<port> - тип входных данных - сетевое подключение по удаленному IP-адресу <ip_address> и UDP-порту <port> (UDP-клиент отправитель) \n"
        " - TCPC:<ip_address>:<port> - тип входных данных - сетевое подключение по удаленному IP-адресу <ip_address> и TCP-порту <port> (TCP-клиент отправитель) \n"
        "\n"
        "<имя_файла> TRAIN  - пакеты данных записываются в файл <имя_файла>, в формате \"Паровоз\" (данные пакета не выровнены до 4 байт). \n"
        "\n"
        "<имя_файла> RAW  - пакеты данных записываются в файл <имя_файла>, в \"сыром\" формате (пакеты данных ничем не обрамляются). \n"
        "\n"
        "<имя_файла> PKC  - пакеты данных записываются в файл <имя_файла>, в формате \"PKC\":  \n"
        "  Формат пакета: \n"
        "    5B 5D XX XX 0D 0A пакет \n"
        "    где XX XX количество байт следующих за этим (длина пакета + 2 байта). \n"
        "\n"
        "<имя_файла> IPSv2 [APPEND] - пакеты данных записываются в файл <имя_файла>, в формате IP_STREAM v2 (является модифицированным IP_STREAM и описывается в соответствующем документе). \n"
        "\n"
        "<имя_файла> LIBPCAP [APPEND] - пакеты данных записываются в файл <имя_файла>, в формате LIBPCAP. \n"
        "\n"
        ,cfg_out_pins_dst, cfg_out_pins_dst_enum, PINS_ARRAY_SIZE, &cfg_out_pins_count);

        prefs_register_string_preference_arr(pref_out_pins, pref_out_pins_dst,
          1 << out_dst_type::out_dst_net_udp_train | 1 << out_dst_type::out_dst_net_udp_raw | 1 << out_dst_type::out_dst_net_tcpc_train |
          1 << out_dst_type::out_dst_net_tcpc_trains | 1 << out_dst_type::out_dst_net_tcpc_trainm | 1 << out_dst_type::out_dst_net_tcpc_srm | 1 << out_dst_type::out_dst_net_tcpc_raw,
          0, "out_pins_dst_address",
          "Адрес",
          "Адрес. "
          "Значение данного параметра используется для уточнения некоторых типов источников (<ip_address>:<port>)."
          ,cfg_out_pins_dst_address.data, PREFS_MAX_PATH, PINS_ARRAY_SIZE, &cfg_out_pins_count);

        prefs_register_file_preference_arr(pref_out_pins, pref_out_pins_dst,
          1 << out_dst_type::out_dst_file_train | 1 << out_dst_type::out_dst_file_raw | 1 << out_dst_type::out_dst_file_pkc | 1 << out_dst_type::out_dst_file_ipsv2 | 1 << out_dst_type::out_dst_file_libpcap,
          0, "out_pins_dst_filename",
          "Файл",
          "Имя файла. "
          "Значение данного параметра используется для уточнения некоторых типов назначения (<имя_файла>)."
          "Параметр <имя_файла> может включать в себя следующие подстановочные переменные: \n"
          "\n"
          " - $(DATE) - текущая дата в формате ГГГГ-ММ-ДД. Например, \"all_$(DATE).dat\" преобразуется в следующее имя файла: \"all_2007-12-03.dat\"; \n"
          "\n"
          " - $(TIME) - текущее время в формате ЧЧ-ММ-СС. Например, \"all_$(TIME).dat\" преобразуется в следующее имя файла: \"all_14-21-58.dat\"; \n"
          "\n"
          " - $(PID) - шестнадцатиричное представление значения PID в формате XXXXXXXX. Например, \"all_$(PID).dat\" преобразуется в следующее имя файла: \"all_00000001.dat\". Если поток содержит пакеты с разными значениями PID, производится демультиплексирование потока, то есть будет создано столько файлов, сколько разных значений было встречено в потоке. Тогда в каждом файле будут находиться пакеты только с соответствующим PID. Данную переменную можно можно комбинировать с переменной $(LID) (одновременное демультиплексирование по PID и LID); \n"
          "\n"
          " - $(LID) - шестнадцатиричное представление значения LID в формате XXXXXXXX. Например, \"all_$(LID).dat\" преобразуется в следующее имя файла: \"all_00000001.dat\". Если поток содержит пакеты с разными значениями LID, производится демультиплексирование потока, то есть будет создано столько файлов, сколько разных значений было встречено в потоке. Тогда в каждом файле будут находиться пакеты только с соответствующим LID. Данную переменную можно можно комбинировать с переменной $(PID) (одновременное демультиплексирование по PID и LID); \n"
          "\n"
          " - $(<размер>) - нарезка регистрируемого на части по размеру, задаваемому значением <размер> (задается в байтах). Возможные модификаторы значения <размер> - K/M/G/T (1K = 1024, 1M = 1024K = 1048576, 1G = 1024M = 1048576K = 1073741824, 1T = 1024G = 1048576M = 1073741824K = 1099511627776). К имени файла добавляется шестнадцатиричное представление значения счетчика (порядкового номера) нарезаемого фрагмента, начиная со значения 0, в формате XXXXXXXX. Например, \"all_$(32M).dat\" преобразуется в следующие имена файлов (каждый файл будет иметь рамер, близкий к 32 Мегабайтам): \"all_0000.dat\", \"all_0001.dat\", \"all_0002.dat\" и так далее. \n"
          "\n"
          " - $(<время>s) - нарезка регистрируемого на части по времени, задаваемому значением <время> (задается в секундах). Возможные модификаторы значения <размер> - K/M/G/T (1K = 1024, 1M = 1024K = 1048576, 1G = 1024M = 1048576K = 1073741824, 1T = 1024G = 1048576M = 1073741824K = 1099511627776). К имени файла добавляется шестнадцатиричное представление значения счетчика (порядкового номера) нарезаемого фрагмента, начиная со значения 0, в формате XXXXXXXX. Например, \"all_$(60s).dat\" преобразуется в следующие имена файлов (каждый файл будет иметь время записи в 60 секунд): \"all_0000.dat\", \"all_0001.dat\", \"all_0002.dat\" и так далее. \n"
          "\n"
          ,cfg_out_pins_dst_filename.data, PREFS_MAX_PATH, cfg_pins_filename_any_filter, PINS_ARRAY_SIZE, &cfg_out_pins_count);

        prefs_register_enum_preference_arr(pref_out_pins, pref_out_pins_dst,
          1 << out_dst_type::out_dst_file_libpcap, 0, "out_pins_libpcap_payload",
          "Тип нагрузки - LIBPCAP",
          "Тип нагрузки, записываемый в заголовок LIBPCAP-файла. "
          "\n"
          ,cfg_out_pins_libpcap_payload, pcap_enum, PINS_ARRAY_SIZE, &cfg_out_pins_count);

        prefs_register_string_preference_arr(pref_out_pins, pref_out_pins_dst,
          1 << out_dst_type::out_dst_file_train | 1 << out_dst_type::out_dst_file_raw | 1 << out_dst_type::out_dst_file_pkc | 1 << out_dst_type::out_dst_file_ipsv2 | 1 << out_dst_type::out_dst_file_libpcap,
          0, "out_pins_dst_filename_addon",
          "Окончание",
          "Окончание имени файла. "
          "Пустое значение данного параметра отключает его действие. "
          "Значение данного параметра добавляется к имени выходного файла при его закрытии. \n"
          "Окончательное имя выходного файла будет иметь вид: \"<имя_файла><окончание>\" \n"
          ,cfg_out_pins_dst_filename_addon.data, PREFS_MAX_PATH, PINS_ARRAY_SIZE, &cfg_out_pins_count);

        prefs_register_bool_preference_arr(pref_out_pins, pref_out_pins_dst,
          1 << out_dst_type::out_dst_file_train | 1 << out_dst_type::out_dst_file_raw | 1 << out_dst_type::out_dst_file_pkc | 1 << out_dst_type::out_dst_file_ipsv2 | 1 << out_dst_type::out_dst_file_libpcap,
          0, "out_pins_has_append",
          "Режим добавления",
          "Режим добавления/замещения. "
          "Если параметр задан, пакеты данных записываются в конец файла (режим добавления). "
          "Если параметр не задан, файл очищается перед началом записи в него пакетов данных (режим замещения). "
          ,cfg_out_pins_has_append, PINS_ARRAY_SIZE, &cfg_out_pins_count);

      preference_p pref_out_pins_payload = prefs_register_enum_preference_arr(pref_out_pins, pref_out_pins_check, 0, 0, "out_pins_payload",
        "Тип нагрузки",
        "Тип нагрузки. "
        "Параметр определяет тип данных, передаваемой по данному выходу. \n"
        "Типы передаваемой информации: \n"
        "\n"
        " - FWD - поток, передающий данные, отобранные по признакам переадресации \n"
        "\n"
        " - BLCK[:<index>] - поток, передающий TCP/IP-пакеты, искуственно генерируемые для управления дальнейшими обработчиками (<команда> снятия TCP-сессии с обработки) \n"
        "\n"
        " - ALLIP[:<index>] - весь IP-поток \n"
        "\n"
        " - VPN - ESP, AH, KERBEROS, PPTP, L2TP... (для TCP-пакетов, TCP-порты: 500 - ISAKMP, 88 - KERBEROS, 49 - TACACS, 1723 - PPTP, 135 - BNE, 45 - CHECKPOINT; для UDP-пакетов, UDP-порты: 500 - ISAKMP, 88 - KERBEROS, 750 - KRB4, 1502 - SHIVA, 1549 - SHIVA, 1651 - SHIVA, 2233 - SHIVA, 1701 - L2TP, 1645 - RADIUS, 1812 - RADIUS, 1646 - RADACCT, 1813 - RADACCT, 49 - TACACS, 1111 - BNE) \n"
        "\n"
        " - VOIP - H.323, SIP, IAX, MGCP, TDMOIP, RTP, RTCP... (для TCP-пакетов, TCP-порты: 1720 - H.323  CS, 1721 - H.323 CS2, 5060 - SIP; для UDP-пакетов, UDP-порты: 1718 - H.323 RAS1, 1719 - H.323 RAS2, 5060 - SIP, 2427 - MGCP, TDMOIP - 2142, IAX - 4569) \n"
        "\n"
        " - SVC - ICMP, DNS... (для TCP-пакетов, TCP-порты: 53 - DNS, 5353 - DNS, 179 - BNE; для UDP-пакетов, UDP-порты: 53 - DNS, 5353 - DNS, 520 - RIP) \n"
        "\n"
        " - HTTP[:<index>] - HTTP-трафик (для TCP-пакетов, TCP-порты: 80 - HTTP, 3128 - PROXY HTTP, 3132 - ADMIN HTTP, 8080 - ALT HTTP, 8088 - RADAN HTTP, 3124 - ALT HTTP, 3127 - ALT HTTP, 3689 - DAAP, 11371 - HKP) \n"
        "\n"
        " - NOTHTTP[:<index>] - весь IP-поток, кроме HTTP (ALLIP = HTTP + NOTHTTP) \n"
        "\n"
        " - MAIL[:<index>] - E-MAIL-трафик (для TCP-пакетов, TCP-порты: 25 - SMTP, 110 - POP3, 143 - IMAP) \n"
        "\n"
        " - FTP[:<index>] - FTP-трафик (для TCP-пакетов, TCP-порты: 20 - FTPDATA, 21 - FTP) \n"
        "\n"
        " - OTHTCP[:<index>] - остальной TCP-трафик \n"
        "\n"
        " - OTHUDP[:<index>] - остальной UDP-трафик \n"
        "\n"
        " - OTHIP[:<index>] - остальной IP-трафик (кроме TCP и UDP) \n"
        "\n"
        " - THINTCP[:<index>] - поток, передающий только определенные TCP/IP-пакеты: содержащие SYN (начало), содержащие FIN|RST (конец) и первые пакеты с данными (по одному с каждого направления)  \n"
        "\n"
        " - IPV6 - IP-протокол версии 6 \n"
        "\n"
        " - GRE - протокол GRE \n"
        "\n"
        " - IPIP - протоколы IP-IP (RFC 2003), IP-in-IP \n"
        "\n"
        " - UNK - неизвестные данные \n"
        "\n"
        ,cfg_out_pins_payload, cfg_out_pins_payload_enum, PINS_ARRAY_SIZE, &cfg_out_pins_count);

        prefs_register_csv_preference_arr(pref_out_pins, pref_out_pins_payload,
          (1 << 0) | (1 << 1),
          0, "out_pins_payload_wparam",
          "Нагрузка",
          "Нагрузка. "
          "Уточнение типа нагрузки. "
          "Для типа нагрузки \"Перенаправление\": \n"
          "  Определяет имена всех входов и демультиплексоров (должны быть DUMMY), пакеты от которых поступают напрямую на данный выход, минуя обработку. \n"
          "Для типа нагрузки \"Другое\": \n"
          "  Позволяет скомбинировать несколько типов нагрузки в один выходной поток. \n"
          "  Позволяет задавать типы нагрузки с индексом демультиплексирования. \n"
          "    <index> - если существует, то все выходные потоки одного типа с одинаковым индексом \n"
          "    объединяются в группу демультиплексирования (ограничение: значение индекса должно быть равным 0 или 1). \n"
          "    Если заданы независимые TCP/UDP-порты, то содержащие их TCP/UDP-пакеты не будут демультиплексированы, \n"
          "    то есть будут отправлены по всем выходным потокам, входящим в группу демультиплексирования. \n"
          ,cfg_out_pins_payload_param.data, PREFS_MAX_PATH, PINS_ARRAY_SIZE, &cfg_out_pins_count);

      preference_p pref_out_pins_pid_lid_setter_check = prefs_register_bool_preference_arr(pref_out_pins, pref_out_pins_check, 0, 0, "out_pins_pid_lid_setter_check",
        "Модификация PID/LID",
        "Модифицировать значения PID/LID или нет. "
        "Возможные значения: \n"
        "  - 0 - не использовать \n"
        "  - 1 - использовать \n"
        ,cfg_out_pins_pid_lid_setter_check, PINS_ARRAY_SIZE, &cfg_out_pins_count);

        preference_p pref_out_pins_has_set_pid = prefs_register_bool_preference_arr(pref_out_pins, pref_out_pins_pid_lid_setter_check, 0, 0, "out_pins_has_set_pid",
          "Установка PID",
          "Установка PID."
          ,cfg_out_pins_has_set_pid, PINS_ARRAY_SIZE, &cfg_out_pins_count);

          prefs_register_uint_preference_arr(pref_out_pins, pref_out_pins_has_set_pid, 0, 0, "out_pins_set_pid",
            "Значение PID",
            "Значение PID."
            "Параметры \"set_pid\" и \"set_lid\" определяют альтернативные значения PID и LID для каждого исходящего пакета, "
            "то есть, при поступлении очередного пакета, его оригинальные значения PID/LID заменяются на заданные. "
            "Значения \"set_pid\" и \"set_lid\" задаются независимо. Например, если задан PID, но не задан LID, "
            "тогда подмена PID производиться будет, а подмена LID - нет. "
            ,cfg_out_pins_set_pid, PINS_ARRAY_SIZE, &cfg_out_pins_count);

        preference_p pref_out_pins_has_set_lid = prefs_register_bool_preference_arr(pref_out_pins, pref_out_pins_pid_lid_setter_check, 0, 0, "out_pins_has_set_lid",
          "Установка LID",
          "Установка LID."
          ,cfg_out_pins_has_set_lid, PINS_ARRAY_SIZE, &cfg_out_pins_count);

          prefs_register_uint_preference_arr(pref_out_pins, pref_out_pins_has_set_lid, 0, 0, "out_pins_set_lid",
            "Значение LID",
            "Значение LID."
            "Параметры \"set_pid\" и \"set_lid\" определяют альтернативные значения PID и LID для каждого исходящего пакета, "
            "то есть, при поступлении очередного пакета, его оригинальные значения PID/LID заменяются на заданные. "
            "Значения \"set_pid\" и \"set_lid\" задаются независимо. Например, если задан PID, но не задан LID, "
            "тогда подмена PID производиться будет, а подмена LID - нет. "
            ,cfg_out_pins_set_lid, PINS_ARRAY_SIZE, &cfg_out_pins_count);

        preference_p pref_out_pins_has_set_pid_mask = prefs_register_bool_preference_arr(pref_out_pins, pref_out_pins_pid_lid_setter_check, 0, 0, "out_pins_has_set_pid_mask",
          "Установка PID-маски",
          "Установка PID-маски."
          ,cfg_out_pins_has_set_pid_mask, PINS_ARRAY_SIZE, &cfg_out_pins_count);

          prefs_register_uint_preference_arr(pref_out_pins, pref_out_pins_has_set_pid_mask, 0, 0, "out_pins_set_pid_mask",
            "Значение PID-маски",
            "Значение PID-маски."
            "Параметры \"set_pid_mask\" и \"set_lid_mask\" определяют маскирование значений PID и LID для каждого исходящего пакета, "
            "то есть, при поступлении очередного пакета, его оригинальные значения PID/LID маскируются логическим <И> с заданным значением. "
            "Значения \"set_pid_mask\" и \"set_lid_mask\" задаются независимо. Например, если задан PID_MASK, но не задан LID_MASK, "
            "тогда подмена PID_MASK производиться будет, а подмена LID_MASK - нет. "
            "Применение \"set_pid_mask\" и \"set_lid_mask\" следует за применением \"set_pid\" и \"set_lid\". "
            ,cfg_out_pins_set_pid_mask, PINS_ARRAY_SIZE, &cfg_out_pins_count);

        preference_p pref_out_pins_has_set_lid_mask = prefs_register_bool_preference_arr(pref_out_pins, pref_out_pins_pid_lid_setter_check, 0, 0, "out_pins_has_set_lid_mask",
          "Установка LID-маски",
          "Установка LID-маски."
          ,cfg_out_pins_has_set_lid_mask, PINS_ARRAY_SIZE, &cfg_out_pins_count);

          prefs_register_uint_preference_arr(pref_out_pins, pref_out_pins_has_set_lid_mask, 0, 0, "out_pins_set_lid_mask",
            "Значение LID-маски",
            "Значение LID-маски."
            "Параметры \"set_pid_mask\" и \"set_lid_mask\" определяют маскирование значений PID и LID для каждого исходящего пакета, "
            "то есть, при поступлении очередного пакета, его оригинальные значения PID/LID маскируются логическим <И> с заданным значением. "
            "Значения \"set_pid_mask\" и \"set_lid_mask\" задаются независимо. Например, если задан PID_MASK, но не задан LID_MASK, "
            "тогда подмена PID_MASK производиться будет, а подмена LID_MASK - нет. "
            "Применение \"set_pid_mask\" и \"set_lid_mask\" следует за применением \"set_pid\" и \"set_lid\". "
            ,cfg_out_pins_set_lid_mask, PINS_ARRAY_SIZE, &cfg_out_pins_count);

      prefs_register_bool_preference_arr(pref_out_pins, pref_out_pins_check, 0, 0, "out_pins_suppress_pid_lid_counting",
        "Запретить контроль PID/LID-активности",
        "Производить или нет подсчет количества PID/LID-пар, поступаующих на данный выход. "
        "Возможные значения: \n"
        "  - 0 - производить контроль \n"
        "  - 1 - не производить контроль \n"
        ,cfg_out_pins_suppress_pid_lid_counting, PINS_ARRAY_SIZE, &cfg_out_pins_count);

      preference_p pref_out_pins_has_buffer_size = prefs_register_bool_preference_arr(pref_out_pins, pref_out_pins_check, 0, 0, "out_pins_has_buffer_size",
        "Альтернативный буфер",
        "Использовать или нет альтернативный буфер."
        ,cfg_out_pins_has_buffer_size, PINS_ARRAY_SIZE, &cfg_out_pins_count);

        prefs_register_uint_preference_arr(pref_out_pins, pref_out_pins_has_buffer_size, 0, 0, "out_pins_buffer_size",
          "Размер альтернативного буфера, б",
          "Размер альтернативного буфера, б. "
          "Параметр \"out_pin_buffer_size\" аналогичен одноименному глобальному параметру (описан выше). "
          "Значение локального параметра будет использоваться для данного описываемого параметра. "
          "Значение глобального параметра используется по-умолчанию. "
          ,cfg_out_pins_buffer_size, PINS_ARRAY_SIZE, &cfg_out_pins_count);

}

