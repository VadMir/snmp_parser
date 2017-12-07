/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/// \libswine_api.h
/// \mainpage
/// @{
/// \section attention Предупреждение
/// \b ВНИМАНИЕ! Файл <b>"libswine_api.h"</b> распространяется под авторским правом РАЗРАБОТЧИКА данного файла.
/// Любые изменения в данном файле СТОРОННИМИ разработчиками НЕДОПУСТИМЫ.
/// Для использования данного файла просто включите его в проект с помощью директивы #include.
///
/// \section changelog Изменения
/// - [*] 2016-11-10 - Добавлено: функция swine_chopper_process_sorm_command (см.документацию);
/// - [*] 2016-12-28 - Изменено: параметры вызова функций swine_chopper_aaa_link_by_pid_lid_ipv6, swine_chopper_aaa_link_by_pid_lid_ip (!несовместимо с предыдущими версиями!)
/// - [*] 2016-11-10 - Добавлено: функция swine_chopper_aaa_link_by_pid_lid_ipv6
/// - [*] 2014-12-23 - Добавлено: функция swine_chopper_aaa_link_by_pid_lid_ip
/// - [*] 2014-12-23 - Удалено: функция swine_chopper_aaa_link_by_ip
/// - [*] 2014-06-27 - добавлено: функция swine_chopper_set_on_ack
/// - [*] 2012-12-26 - добавлено: функция swine_chopper_aaa_link_by_ip
///
/// \section description Описание
/// Данный документ содержит API
///
/// \section copyright Авторские права
/// Copyright (C) MSC, ORG 2002-2010
///
/// @}

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#ifndef __LIBSWINE_API_H
/// \cond
#define __LIBSWINE_API_H
/// \endcond

// Now we use the generic helper definitions above to define XXX_API and XXX_LOCAL.
// XXX_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
// XXX_LOCAL is used for non-api symbols.
#ifdef LIBSWINE_EXPORTS // defined if we are building the XXX DLL (instead of using it)
  /// \cond
  #define LIBSWINE_API extern "C" MSCU_HELPER_DLL_EXPORT
  /// \endcond
#else
  /// \cond
  #define LIBSWINE_API extern "C" MSCU_HELPER_DLL_IMPORT
  #pragma comment( lib, "libswine" )
  /// \endcond
#endif // LIBSWINE_API_EXPORTS
#define LIBSWINE_LOCAL MSCU_HELPER_DLL_LOCAL

#include <mscu_types.h>

//////////////////////////////////////////////////////////////////////////
// !PORT from swine_ts.h
//////////////////////////////////////////////////////////////////////////

#include <mscu_types.h>
#include <swinertm/swinertm.h>
#include <swine_api.h>
#include <ffsrm.h>
#include <lardsorm/lardsorm.h>

#define TS_READER_SOURCE_FILE 0 //* !!!комментарий *)
#define TS_READER_SOURCE_NET  1 //* !!!комментарий *)

#define TS_READER_TYPE_RAW           0 //* обычный поток, 1 направление *)
#define TS_READER_TYPE_FRAME         1 //* обычный поток, 1 направление *)
#define TS_READER_TYPE_LIBPCAP       2 //* LibPCap *)
#define TS_READER_TYPE_NETMON        3 //* Network Monitor *)
#define TS_READER_TYPE_WRPGPCAP      4 //* WarPig Capture *)
#define TS_READER_TYPE_IPSTREAM      5 //* IP_STREAM *)
#define TS_READER_TYPE_FRAMETIME64   6 //* FRAME-TIME 64 bit, 1 или 2 направления *)
#define TS_READER_TYPE_FRAMETIME32   7 //* FRAME-TIME 32bit, 1 или 2 направления *)
#define TS_READER_TYPE_TRAIN3        8 //* TRAIN 3 *)
#define TS_READER_TYPE_TRAIN         9 //* TRAIN *)
#define TS_READER_TYPE_TRAINTM      10 //* TRAIN *)

#define TS_READER_FLAG_ONLINE     0x00000001 //* ONLINE-режим, иначе - OFFLINE(файл) *)
#define TS_READER_FLAG_PACKETIZED 0x00000002 //* пакетный режим, иначе - потоковый *)

#define TS_SENT 0
#define TS_RECV 1

//////////////////////////////////////////////////////////////////////////
//* направления передачи *)
#define TS_P2P_DIR_UNKNOWN  0
#define TS_P2P_DIR_SENT     1
#define TS_P2P_DIR_RECV     2

//////////////////////////////////////////////////////////////////////////
// * изменения: увеличена разрядность - с 32 до 64
STRUCT_PACKED_BEGIN // устанавливаем выравнивание структур в 1 байт
struct STRUCT_PACKED_ATTRIBUTE Tfrms32_rec_hdr {
  gint32  tv_usec;
  guint32 len;
};
STRUCT_PACKED_END // восстанавливаем выравнивание структур по умолчанию

STRUCT_PACKED_BEGIN // устанавливаем выравнивание структур в 1 байт
struct STRUCT_PACKED_ATTRIBUTE Tfrms64_rec_hdr {
  gint64  tv_usec;
  guint32 len;
};
STRUCT_PACKED_END // восстанавливаем выравнивание структур по умолчанию

struct ts_reader_data_t {
  guint     count;
  guint8*   buffer;
  gint      direction;
  gint64    usec;
  Ttimeval  tv;
  guint32   pid;
  guint32   lid;
  guint     dl_offset;
  union {
	  guint16 ext; // LE format
#pragma warning(disable : 4201)
	  struct { guint8 ext_encap; 	guint8 ext_offset; };
  };
};

STRUCT_PACKED_BEGIN // устанавливаем выравнивание структур в 1 байт
struct STRUCT_PACKED_ATTRIBUTE Text_pid_lid_rec {
  guint16 len;      // Amount of data currently in buffer
  guint16 ext;      // write count - this increments but is never reset
  guint32 pid;      // read point - this is only changed by sysman
  guint32 lid;      // how many entries?
  guint8 buffer[4]; // Our actual entries, put 4 bytes for the bytes alignment.
};
STRUCT_PACKED_END // восстанавливаем выравнивание структур по умолчанию

//* объект читателя из файлов *)
typedef /*gpointer*/class TkrTSReader;

//////////////////////////////////////////////////////////////////////////
extern "C" LIBSWINE_API gconstpchar MSCU_CALL_PREFIX swine_ts_reader_get_last_error();

extern "C" LIBSWINE_API preference_p MSCU_CALL_PREFIX pref_swine_get_ts_dialog();
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_ts_reader_set_source(gint source);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_ts_reader_set_file_as_list(gboolean value);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_ts_reader_set_filetype_auto(gboolean value);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_ts_reader_set_filetype(gint filetype);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_ts_reader_set_filename(gconstpchar filename);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_ts_reader_set_filename2(gconstpchar filename);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_ts_reader_set_url(gconstpchar url);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_ts_reader_set_url2(gconstpchar url);

//////////////////////////////////////////////////////////////////////////

extern "C" LIBSWINE_API gpointer MSCU_CALL_PREFIX swine_ts_reader_create();
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_ts_reader_destroy(gpointer ts_reader);
extern "C" LIBSWINE_API gint64 MSCU_CALL_PREFIX swine_ts_reader_size(gpointer ts_reader);
extern "C" LIBSWINE_API gint64 MSCU_CALL_PREFIX swine_ts_reader_position(gpointer ts_reader);
extern "C" LIBSWINE_API gint MSCU_CALL_PREFIX swine_ts_reader_network(gpointer ts_reader);
extern "C" LIBSWINE_API gboolean MSCU_CALL_PREFIX swine_ts_reader_decoderable(gpointer ts_reader);
// в случае неудачи возвращает false, swine_ts_reader_get_last_error содержит описание ошибки
extern "C" LIBSWINE_API gboolean MSCU_CALL_PREFIX swine_ts_reader_open(gpointer ts_reader);
extern "C" LIBSWINE_API gboolean MSCU_CALL_PREFIX swine_ts_reader_open_next(gpointer ts_reader, gboolean* has_next);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_ts_reader_reset(gpointer ts_reader);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_ts_reader_freeze(gpointer ts_reader);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_ts_reader_close(gpointer ts_reader);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_ts_reader_read_lock(gpointer ts_reader, ts_reader_data_t* di);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_ts_reader_read_unlock(gpointer ts_reader);

extern "C" LIBSWINE_API gconstpchar MSCU_CALL_PREFIX swine_ts_reader_get_source_name(gpointer ts_reader);
extern "C" LIBSWINE_API gconstpchar MSCU_CALL_PREFIX swine_ts_reader_get_short_source_name(gpointer ts_reader);
extern "C" LIBSWINE_API gconstpchar MSCU_CALL_PREFIX swine_ts_reader_get_single_file_name(gpointer ts_reader);
extern "C" LIBSWINE_API gconstpchar MSCU_CALL_PREFIX swine_ts_reader_get_source_type_name(gpointer ts_reader);

extern "C" LIBSWINE_API gconstpchar MSCU_CALL_PREFIX swine_ts_reader_get_filename();
extern "C" LIBSWINE_API gconstpchar MSCU_CALL_PREFIX swine_ts_reader_get_filename2();

extern "C" LIBSWINE_API gint MSCU_CALL_PREFIX swine_ts_reader_get_source(gpointer ts_reader);

extern "C" LIBSWINE_API gdouble MSCU_CALL_PREFIX swine_ts_reader_get_ticks(gpointer ts_reader);

extern "C" LIBSWINE_API gint64 MSCU_CALL_PREFIX swine_ts_reader_get_in_bytes(gpointer ts_reader);
extern "C" LIBSWINE_API gchar MSCU_CALL_PREFIX swine_ts_reader_get_in_bytes_modificator(gpointer ts_reader);
extern "C" LIBSWINE_API gdouble MSCU_CALL_PREFIX swine_ts_reader_get_in_bytes_speed(gpointer ts_reader);

extern "C" LIBSWINE_API gint64 MSCU_CALL_PREFIX swine_ts_reader_get_in_packets(gpointer ts_reader);
extern "C" LIBSWINE_API gchar MSCU_CALL_PREFIX swine_ts_reader_get_in_packets_modificator(gpointer ts_reader);
extern "C" LIBSWINE_API gdouble MSCU_CALL_PREFIX swine_ts_reader_get_in_packets_speed(gpointer ts_reader);

extern "C" LIBSWINE_API gint64 MSCU_CALL_PREFIX swine_ts_reader_get_udpcapt_errors(gpointer ts_reader);
extern "C" LIBSWINE_API gchar MSCU_CALL_PREFIX swine_ts_reader_get_udpcapt_errors_modificator(gpointer ts_reader);

extern "C" LIBSWINE_API gint64 MSCU_CALL_PREFIX swine_ts_reader_get_udpcapt_errors2(gpointer ts_reader);
extern "C" LIBSWINE_API gchar MSCU_CALL_PREFIX swine_ts_reader_get_udpcapt_errors2_modificator(gpointer ts_reader);

extern "C" LIBSWINE_API gint64 MSCU_CALL_PREFIX swine_ts_reader_get_udpcapt_errors3(gpointer ts_reader);
extern "C" LIBSWINE_API gchar MSCU_CALL_PREFIX swine_ts_reader_get_udpcapt_errors3_modificator(gpointer ts_reader);

extern "C" LIBSWINE_API gint MSCU_CALL_PREFIX swine_ts_reader_get_udpcapt_queue_commit_percent(gpointer ts_reader);
extern "C" LIBSWINE_API gsize_t MSCU_CALL_PREFIX swine_ts_reader_get_udpcapt_queue_megabytes(gpointer ts_reader);

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// !PORT from swine_impl.h
//////////////////////////////////////////////////////////////////////////
#define SWINE_ENCODER_TYPE_RAW       0 // !!!комментарий
#define SWINE_ENCODER_TYPE_TRAIN     1 // !!!комментарий
#define SWINE_ENCODER_TYPE_LIBPCAP   2 // !!!комментарий
#define SWINE_ENCODER_TYPE_WRPGCAP   3 // !!!комментарий
#define SWINE_ENCODER_TYPE_TRAIN3    4 // !!!комментарий
#define SWINE_ENCODER_TYPE_IPSTREAM  5 // !!!комментарий

extern "C" LIBSWINE_API gpointer MSCU_CALL_PREFIX swine_encoder_create();
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_encoder_destroy(gpointer encoder);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_encoder_start(gpointer encoder);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_encoder_stop(gpointer encoder);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_encoder_crop(gpointer encoder, tvbuff_t* tvb, PPacketInfo pi);

extern "C" LIBSWINE_API gconstpchar MSCU_CALL_PREFIX swine_encoder_filename(/*gpointer encoder*/);

extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_encoder_update_type(gint a_type);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_encoder_update_filename(gconstpchar filename);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_encoder_update_filename_wo_ext(gconstpchar filename);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_encoder_update_dlt(gint dlt);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_encoder_update_ip_filter(gconstpchar a_filter_ip_proto, gconstpchar a_filter_ip_proto_rem, gconstpchar a_filter_tcp, gconstpchar a_filter_tcp_rem, gconstpchar a_filter_udp, gconstpchar a_filter_udp_rem, gconstpchar a_filter_sessions_file, gconstpchar a_filter_separator_file);

extern "C" LIBSWINE_API preference_p MSCU_CALL_PREFIX pref_swine_get_encoder_dialog();
extern "C" LIBSWINE_API preference_p MSCU_CALL_PREFIX pref_swine_get_encoder_module();

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// !PORT from swine_impl.h
//////////////////////////////////////////////////////////////////////////

/* работа со структурой TPacketInfo */
// динамическое создание записи информации о пакете
extern "C" LIBSWINE_API PPacketInfo MSCU_CALL_PREFIX base_packet_info_malloc();
// удаление записи
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX base_packet_info_free(PPacketInfo PacketInfo);
// очищение полей записи
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX base_packet_info_clear(PPacketInfo PacketInfo);
// клонирование записи (создание новой записи с содержимым старой записи)
extern "C" LIBSWINE_API PPacketInfo MSCU_CALL_PREFIX base_packet_info_clone(PPacketInfo PacketInfo);
// клонирование признаков записи
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX base_packet_info_tokens_clone(PPacketInfo src, PPacketInfo dst);

/* работа со структурой TPacketInfoEx */
// динамическое создание записи информации о пакете
extern "C" LIBSWINE_API PPacketInfoEx MSCU_CALL_PREFIX base_packet_info_ex_malloc();
// удаление записи
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX base_packet_info_ex_free(PPacketInfoEx PacketInfoEx);
// очищение полей записи
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX base_packet_info_ex_clear(PPacketInfoEx PacketInfoEx);
// клонирование записи (создание новой записи с содержимым старой записи)
extern "C" LIBSWINE_API PPacketInfoEx MSCU_CALL_PREFIX base_packet_info_ex_clone(PPacketInfoEx PacketInfoEx);

/* изменение описания
 * если buf == 0, то имя очищается
 */
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX base_packet_info_ex_set_description(PPacketInfoEx PacketInfoEx, gconstpchar buf);
/* изменение имени файла
 * если buf = nil, то имя очищается
 */
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX base_packet_info_ex_set_generic_name(PPacketInfoEx PacketInfoEx, gconstpchar buf);
/* изменение content-type
 * если buf = nil, то имя очищается
 */
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX base_packet_info_ex_set_content_type(PPacketInfoEx PacketInfoEx, gconstpchar buf);
/* изменение auth_info
 * если buf = nil, то имя очищается
 */
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX base_packet_info_ex_set_auth_info(PPacketInfoEx PacketInfoEx, gconstpchar buf);
/* изменение ident_info
 * если buf = nil, то имя очищается
 */
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX base_packet_info_ex_set_ident_info(PPacketInfoEx PacketInfoEx, gconstpchar buf);

/* изменение header
 * если buf = nil, то имя очищается
 */
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX base_packet_info_set_header(PPacketInfo PacketInfo, gpchar buf, guint32 len);

extern "C" LIBSWINE_API void MSCU_CALL_PREFIX base_packet_info_set_token_path(PPacketInfo PacketInfo, gpchar buf);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX base_packet_info_set_token_entry(PPacketInfo PacketInfo, gint idx, gpchar buf, guint32 len);

// added 2016-05-11
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX base_packet_info_set_id_token_path(PPacketInfo PacketInfo, guint32 id, gpchar buf);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX base_packet_info_set_id_token_entry(PPacketInfo PacketInfo, guint32 id, gint idx, gpchar buf, guint32 len);

//////////////////////////////////////////////////////////////////////////
// создание корневого узла дерева
extern "C" LIBSWINE_API PkrTreeNode MSCU_CALL_PREFIX base_proto_tree_root_create();

// разрушение корневого узла со всеми детьми и обнуление переменной
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX base_proto_tree_root_destroy(PkrTreeNode root);

// добавление узла, AParent - родитель, AText - текст
extern "C" LIBSWINE_API PkrTreeNode MSCU_CALL_PREFIX base_proto_tree_add(PkrTreeNode AParent, gconstpchar AText);

//////////////////////////////////////////////////////////////////////////
// элемент дерева
STRUCT_PACKED_BEGIN // устанавливаем выравнивание структур в 1 байт
struct STRUCT_PACKED_ATTRIBUTE TkrTreeNode {
public:
  gpchar text          ;  // текст
  TkrTreeNode* next         ;  // следующий на одном уровне
  TkrTreeNode* first_child  ;  // первый ребенок
  TkrTreeNode* last_child   ;  // последний ребенок
  TkrTreeNode* parent       ;  // родитель-владелец
};
STRUCT_PACKED_END // восстанавливаем выравнивание структур по умолчанию

//***************************************************************************************)
  // служебный статический (для всех обработчиков) набор служебных данных протокола
typedef /*void*/class TProtoReg;

////////////////////////////////////////////////////////////////////////////////////////////////
//* виды состояний, в которых может находиться прерыватель *)
enum TChopperState {
  CS_IDLE,      //* режим простой *)
  CS_TEST,      //* режим автоопределения *)
  CS_PROCESS,   //* режим обработки *)
  CS_CONVERT,   //* режим преобразования *)
  CS_CONVERT_IP //* режим преобразования (уровень IP) *)
};

typedef /*void*/class TkrProtocol;
typedef /*void*/class TkrChopper;

//* дерево протколов *)
struct TkrTraceNode {
  TkrProtocol*  proto       ;
  TkrTraceNode* first_child ;
  TkrTraceNode* next        ;
};

// событие по сохранению пакета.
// Sender - TkrProtocol
// pi_ex - необходимо обнулить, если "забирается"
typedef void (MSCU_CALL_PREFIX * TkrChopperAck)(gpointer user_data, tvbuff_t* tvb, PPacketInfo pi, PPacketInfoEx pi_ex);//of object;

typedef void (MSCU_CALL_PREFIX * TkrChopperAck_svc)(gpointer user_data, tvbuff_t* tvb, PPacketInfo pi, PPacketInfoEx pi_ex, tvbuff_t* tvb_svc);//of object;

// добавление фильтра
typedef void (*Tswine_add_filter_control_message)(S10G_FILTER_ITEM_STRUCT* filter_item);
// удаление фильтра
typedef void (*Tswine_sub_filter_control_message)(S10G_FILTER_ITEM_STRUCT* filter_item);
// добавление фильтра
typedef void (*Tswine_add_filter_2_control_message)(S10G_FILTER_ITEM_STRUCT_2 * filter_item);
// удаление фильтра
typedef void (*Tswine_sub_filter_2_control_message)(S10G_FILTER_ITEM_STRUCT_2 * filter_item);

typedef void (MSCU_CALL_PREFIX * TkrChopperOutSorm)(gpointer user_data, const guint8 * hdr_buf, gsize_t hdr_len, const guint8 * buf, gsize_t buf_len, guint offset, Ttimeval * tv);//of object;
typedef void (MSCU_CALL_PREFIX * TkrChopperOutTag) (gpointer user_data, const guint8 * buf, gsize_t buf_len);//of object;

///
STRUCT_PACKED_BEGIN // устанавливаем выравнивание структур в 1 байт
struct STRUCT_PACKED_ATTRIBUTE TkrStatist_PID_rec {
  guint32 tpid; // transport PID
  guint32 circuit_id;
};
typedef TkrStatist_PID_rec* PkrStatist_PID_rec;
STRUCT_PACKED_END // восстанавливаем выравнивание структур по умолчанию

STRUCT_PACKED_BEGIN // устанавливаем выравнивание структур в 1 байт
struct STRUCT_PACKED_ATTRIBUTE TkrStatist_PID {
public:
  TkrStatist_PID_rec key       ;
  gint64 packets   ;
  gint64 bytes     ;
  TkrStatist_PID(const TkrStatist_PID_rec& Akey, gint Apackets, gint Abytes);
};
STRUCT_PACKED_END // восстанавливаем выравнивание структур по умолчанию

STRUCT_PACKED_BEGIN // устанавливаем выравнивание структур в 1 байт
struct STRUCT_PACKED_ATTRIBUTE TkrStatist_IP_rec {
  guint32 tpid; // transport PID
  TAddress net_addr  ;
};
typedef TkrStatist_IP_rec* PkrStatist_IP_rec;
STRUCT_PACKED_END // восстанавливаем выравнивание структур по умолчанию

STRUCT_PACKED_BEGIN // устанавливаем выравнивание структур в 1 байт
struct STRUCT_PACKED_ATTRIBUTE TkrStatist_IP {
public:
  TkrStatist_IP_rec key       ;
  gint64 packets   ;
  gint64 bytes     ;
  TkrStatist_IP(const TkrStatist_IP_rec& Akey, gint Apackets, gint Abytes);
};
STRUCT_PACKED_END // восстанавливаем выравнивание структур по умолчанию

STRUCT_PACKED_BEGIN // устанавливаем выравнивание структур в 1 байт
struct STRUCT_PACKED_ATTRIBUTE TkrStatist_IP_TCPPORT_rec {
  guint32 tpid; // transport PID
  TAddress net_addr  ;
  guint32 tcpport   ;                   //* порт источника *)
};
typedef TkrStatist_IP_TCPPORT_rec* PkrStatist_IP_TCPPORT_rec;
STRUCT_PACKED_END // восстанавливаем выравнивание структур по умолчанию

STRUCT_PACKED_BEGIN // устанавливаем выравнивание структур в 1 байт
struct STRUCT_PACKED_ATTRIBUTE TkrStatist_IP_TCPPORT {
public:
  TkrStatist_IP_TCPPORT_rec key       ;
  gint64 packets   ;
  gint64 bytes     ;
  TkrStatist_IP_TCPPORT(const TkrStatist_IP_TCPPORT_rec& Akey, gint Apackets, gint Abytes);
};
STRUCT_PACKED_END // восстанавливаем выравнивание структур по умолчанию

STRUCT_PACKED_BEGIN // устанавливаем выравнивание структур в 1 байт
struct STRUCT_PACKED_ATTRIBUTE TkrStatist_IP_UDPPORT_rec {
  guint32 tpid; // transport PID
  TAddress net_addr  ;
  guint32 udpport   ;                   //* порт источника *)
};
typedef TkrStatist_IP_UDPPORT_rec* PkrStatist_IP_UDPPORT_rec;
STRUCT_PACKED_END // восстанавливаем выравнивание структур по умолчанию

STRUCT_PACKED_BEGIN // устанавливаем выравнивание структур в 1 байт
struct STRUCT_PACKED_ATTRIBUTE TkrStatist_IP_UDPPORT {
public:
  TkrStatist_IP_UDPPORT_rec key       ;
  gint64 packets   ;
  gint64 bytes     ;
  TkrStatist_IP_UDPPORT(const TkrStatist_IP_UDPPORT_rec& Akey, gint Apackets, gint Abytes);
};
STRUCT_PACKED_END // восстанавливаем выравнивание структур по умолчанию

STRUCT_PACKED_BEGIN // устанавливаем выравнивание структур в 1 байт
struct STRUCT_PACKED_ATTRIBUTE TkrStatist_IPSRC_IPDST_rec {
  guint32 tpid; // transport PID
  TAddress net_src     ;
  TAddress net_dst     ;
};
typedef TkrStatist_IPSRC_IPDST_rec* PkrStatist_IPSRC_IPDST_rec;
STRUCT_PACKED_END // восстанавливаем выравнивание структур по умолчанию

STRUCT_PACKED_BEGIN // устанавливаем выравнивание структур в 1 байт
struct STRUCT_PACKED_ATTRIBUTE TkrStatist_IPSRC_IPDST {
public:
  TkrStatist_IPSRC_IPDST_rec key       ;
  gint64 packets   ;
  gint64 bytes     ;
  TkrStatist_IPSRC_IPDST(const TkrStatist_IPSRC_IPDST_rec& Akey, gint Apackets, gint Abytes);
};
STRUCT_PACKED_END // восстанавливаем выравнивание структур по умолчанию

STRUCT_PACKED_BEGIN // устанавливаем выравнивание структур в 1 байт
struct STRUCT_PACKED_ATTRIBUTE TkrStatist_IPPROTO_rec {
  guint32 tpid; // transport PID
  guint8 ipproto  ;
};
typedef TkrStatist_IPPROTO_rec* PkrStatist_IPPROTO_rec;
STRUCT_PACKED_END // восстанавливаем выравнивание структур по умолчанию

STRUCT_PACKED_BEGIN // устанавливаем выравнивание структур в 1 байт
struct STRUCT_PACKED_ATTRIBUTE TkrStatist_IPPROTO {
public:
  TkrStatist_IPPROTO_rec key       ;
  gint64 packets   ;
  gint64 bytes     ;
  TkrStatist_IPPROTO(const TkrStatist_IPPROTO_rec& Akey, gint Apackets, gint Abytes);
};
STRUCT_PACKED_END // восстанавливаем выравнивание структур по умолчанию

STRUCT_PACKED_BEGIN // устанавливаем выравнивание структур в 1 байт
struct STRUCT_PACKED_ATTRIBUTE TkrStatist_MACDST_rec {
  guint32 tpid; // transport PID
  TAddress dl_dst      ;
};
typedef TkrStatist_MACDST_rec* PkrStatist_MACDST_rec;
STRUCT_PACKED_END // восстанавливаем выравнивание структур по умолчанию

STRUCT_PACKED_BEGIN // устанавливаем выравнивание структур в 1 байт
struct STRUCT_PACKED_ATTRIBUTE TkrStatist_MACDST {
public:
  TkrStatist_MACDST_rec key       ;
  gint64 packets   ;
  gint64 bytes     ;
  TkrStatist_MACDST(const TkrStatist_MACDST_rec& Akey, gint Apackets, gint Abytes);
};
STRUCT_PACKED_END // восстанавливаем выравнивание структур по умолчанию

STRUCT_PACKED_BEGIN // устанавливаем выравнивание структур в 1 байт
struct STRUCT_PACKED_ATTRIBUTE TkrStatist_PID_MACDST_IPSRC_IPDST_IPPROTO_PORTSRC_PORTDST_rec {
  guint32 tpid; // transport PID
  guint32 circuit_id  ;
  TAddress dl_dst      ;
  TAddress net_src     ;
  TAddress net_dst     ;
  guint8 ipproto     ;
  guint32 srcport     ;                   //* порт источника *)
  guint32 destport    ;                  //* порт приемника *)
};
typedef TkrStatist_PID_MACDST_IPSRC_IPDST_IPPROTO_PORTSRC_PORTDST_rec* PkrStatist_PID_MACDST_IPSRC_IPDST_IPPROTO_PORTSRC_PORTDST_rec;
STRUCT_PACKED_END // восстанавливаем выравнивание структур по умолчанию

STRUCT_PACKED_BEGIN // устанавливаем выравнивание структур в 1 байт
struct STRUCT_PACKED_ATTRIBUTE TkrStatist_PID_MACDST_IPSRC_IPDST_IPPROTO_PORTSRC_PORTDST {
public:
  TkrStatist_PID_MACDST_IPSRC_IPDST_IPPROTO_PORTSRC_PORTDST_rec key       ;
  gint64 packets   ;
  gint64 bytes     ;
  TkrStatist_PID_MACDST_IPSRC_IPDST_IPPROTO_PORTSRC_PORTDST(const TkrStatist_PID_MACDST_IPSRC_IPDST_IPPROTO_PORTSRC_PORTDST_rec& Akey, gint Apackets, gint Abytes);
};
STRUCT_PACKED_END // восстанавливаем выравнивание структур по умолчанию

typedef /*void*/class TkrStatist;
///

extern "C" LIBSWINE_API PkrTreeNode MSCU_CALL_PREFIX proto_tree_add_proto_info(PkrTreeNode tree, TkrProtocol* proto);
extern "C" LIBSWINE_API PkrTreeNode MSCU_CALL_PREFIX proto_tree_add_packet_info(PkrTreeNode tree, tvbuff_t* tvb, PPacketInfo pi, PPacketInfoEx pi_ex);

// возвращает количество зарегистрированных протоколов
extern "C" LIBSWINE_API gsize_t MSCU_CALL_PREFIX swine_proto_get_proto_count();

// возвращает протокол по индексу
extern "C" LIBSWINE_API TProtoReg* MSCU_CALL_PREFIX swine_proto_get_proto(gsize_t Index);

extern "C" LIBSWINE_API gsize_t MSCU_CALL_PREFIX swine_deco_get_deco_count();

extern "C" LIBSWINE_API TProtoReg* MSCU_CALL_PREFIX swine_deco_get_deco(gsize_t Index);

//////////////////////////////////////////////////////////////////////////
extern "C" LIBSWINE_API const gchar * MSCU_CALL_PREFIX enum_dns_find_url(const guint8 * ip_addr);
extern "C" LIBSWINE_API guint32 MSCU_CALL_PREFIX enum_dns_get_ip(gint index);
extern "C" LIBSWINE_API gconstpchar MSCU_CALL_PREFIX enum_dns_get_url(gint index);
extern "C" LIBSWINE_API gint MSCU_CALL_PREFIX enum_dns_get_count();

//////////////////////////////////////////////////////////////////////////
// диалог параметров ядра

extern "C" LIBSWINE_API preference_p MSCU_CALL_PREFIX swine_prefs_get_swine_dlg();
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_register_prefs(preference_p owner, gboolean_p readonly);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_unregister_prefs();

//////////////////////////////////////////////////////////////////////////
extern "C" LIBSWINE_API gboolean MSCU_CALL_PREFIX swine_get_cfg_trace_tree_enabled();
extern "C" LIBSWINE_API guint MSCU_CALL_PREFIX swine_get_cfg_auto_decoder_buffer_size();

//////////////////////////////////////////////////////////////////////////
extern "C" LIBSWINE_API gconstpchar MSCU_CALL_PREFIX swine_get_last_error();

//////////////////////////////////////////////////////////////////////////
extern "C" LIBSWINE_API gconstpchar MSCU_CALL_PREFIX swine_protoreg_get_name(TProtoReg* protoreg);
extern "C" LIBSWINE_API gconstpchar MSCU_CALL_PREFIX swine_protoreg_get_short_name(TProtoReg* protoreg);
extern "C" LIBSWINE_API gconstpchar MSCU_CALL_PREFIX swine_protoreg_get_filter_name(TProtoReg* protoreg);
extern "C" LIBSWINE_API gconstpchar MSCU_CALL_PREFIX swine_protoreg_get_description(TProtoReg* protoreg);
extern "C" LIBSWINE_API gboolean MSCU_CALL_PREFIX swine_protoreg_get_is_enabled(TProtoReg* protoreg);

extern "C" LIBSWINE_API TProtoReg* MSCU_CALL_PREFIX swine_protocol_get_protoreg(TkrProtocol* protocol);

extern "C" LIBSWINE_API gint64 MSCU_CALL_PREFIX swine_protocol_get_PIn(TkrProtocol* protocol);
extern "C" LIBSWINE_API gint64 MSCU_CALL_PREFIX swine_protocol_get_PBad(TkrProtocol* protocol);
extern "C" LIBSWINE_API gint64 MSCU_CALL_PREFIX swine_protocol_get_PUnknown(TkrProtocol* protocol);
extern "C" LIBSWINE_API gint64 MSCU_CALL_PREFIX swine_protocol_get_PChain(TkrProtocol* protocol);
extern "C" LIBSWINE_API gint64 MSCU_CALL_PREFIX swine_protocol_get_POk(TkrProtocol* protocol);

extern "C" LIBSWINE_API gint64 MSCU_CALL_PREFIX swine_protocol_get_BIn(TkrProtocol* protocol);
extern "C" LIBSWINE_API gint64 MSCU_CALL_PREFIX swine_protocol_get_BBad(TkrProtocol* protocol);
extern "C" LIBSWINE_API gint64 MSCU_CALL_PREFIX swine_protocol_get_BUnknown(TkrProtocol* protocol);
extern "C" LIBSWINE_API gint64 MSCU_CALL_PREFIX swine_protocol_get_BChain(TkrProtocol* protocol);
extern "C" LIBSWINE_API gint64 MSCU_CALL_PREFIX swine_protocol_get_BOk(TkrProtocol* protocol);

extern "C" LIBSWINE_API gchar MSCU_CALL_PREFIX swine_protocol_get_PIn_modificator(TkrProtocol* protocol);
extern "C" LIBSWINE_API gchar MSCU_CALL_PREFIX swine_protocol_get_PBad_modificator(TkrProtocol* protocol);
extern "C" LIBSWINE_API gchar MSCU_CALL_PREFIX swine_protocol_get_PUnknown_modificator(TkrProtocol* protocol);
extern "C" LIBSWINE_API gchar MSCU_CALL_PREFIX swine_protocol_get_PChain_modificator(TkrProtocol* protocol);
extern "C" LIBSWINE_API gchar MSCU_CALL_PREFIX swine_protocol_get_POk_modificator(TkrProtocol* protocol);

extern "C" LIBSWINE_API gchar MSCU_CALL_PREFIX swine_protocol_get_BIn_modificator(TkrProtocol* protocol);
extern "C" LIBSWINE_API gchar MSCU_CALL_PREFIX swine_protocol_get_BBad_modificator(TkrProtocol* protocol);
extern "C" LIBSWINE_API gchar MSCU_CALL_PREFIX swine_protocol_get_BUnknown_modificator(TkrProtocol* protocol);
extern "C" LIBSWINE_API gchar MSCU_CALL_PREFIX swine_protocol_get_BChain_modificator(TkrProtocol* protocol);
extern "C" LIBSWINE_API gchar MSCU_CALL_PREFIX swine_protocol_get_BOk_modificator(TkrProtocol* protocol);

extern "C" LIBSWINE_API gint MSCU_CALL_PREFIX swine_protocol_get_network(TkrProtocol* protocol);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_protocol_set_network(TkrProtocol* protocol, gint network);
extern "C" LIBSWINE_API gint MSCU_CALL_PREFIX swine_protocol_get_frames(TkrProtocol* protocol);

extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_protocol_AcceptPacketTree(TkrProtocol* protocol, tvbuff_t* tvb, PPacketInfo pi, TkrTreeNode* tree);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_protocol_info(TkrProtocol* protocol, TkrTreeNode* tree);

///
extern "C" LIBSWINE_API TkrStatist_IP* MSCU_CALL_PREFIX swine_statist_get_IP(TkrStatist* statist, gint index);
extern "C" LIBSWINE_API TkrStatist_PID* MSCU_CALL_PREFIX swine_statist_get_PID(TkrStatist* statist, gint index);
extern "C" LIBSWINE_API TkrStatist_IP_TCPPORT* MSCU_CALL_PREFIX swine_statist_get_IP_TCPPORT(TkrStatist* statist, gint index);
extern "C" LIBSWINE_API TkrStatist_IP_UDPPORT* MSCU_CALL_PREFIX swine_statist_get_IP_UDPPORT(TkrStatist* statist, gint index);
extern "C" LIBSWINE_API TkrStatist_IPSRC_IPDST* MSCU_CALL_PREFIX swine_statist_get_IPSRC_IPDST(TkrStatist* statist, gint index);
extern "C" LIBSWINE_API TkrStatist_IPPROTO* MSCU_CALL_PREFIX swine_statist_get_IPPROTO(TkrStatist* statist, gint index);
extern "C" LIBSWINE_API TkrStatist_MACDST* MSCU_CALL_PREFIX swine_statist_get_MACDST(TkrStatist* statist, gint index);
extern "C" LIBSWINE_API TkrStatist_PID_MACDST_IPSRC_IPDST_IPPROTO_PORTSRC_PORTDST* MSCU_CALL_PREFIX swine_statist_get_PID_MACDST_IPSRC_IPDST_IPPROTO_PORTSRC_PORTDST(TkrStatist* statist, gint index);

extern "C" LIBSWINE_API gint MSCU_CALL_PREFIX swine_statist_get_IP_count(TkrStatist* statist);
extern "C" LIBSWINE_API gint MSCU_CALL_PREFIX swine_statist_get_PID_count(TkrStatist* statist);
extern "C" LIBSWINE_API gint MSCU_CALL_PREFIX swine_statist_get_IP_TCPPORT_count(TkrStatist* statist);
extern "C" LIBSWINE_API gint MSCU_CALL_PREFIX swine_statist_get_IP_UDPPORT_count(TkrStatist* statist);
extern "C" LIBSWINE_API gint MSCU_CALL_PREFIX swine_statist_get_IPSRC_IPDST_count(TkrStatist* statist);
extern "C" LIBSWINE_API gint MSCU_CALL_PREFIX swine_statist_get_IPPROTO_count(TkrStatist* statist);
extern "C" LIBSWINE_API gint MSCU_CALL_PREFIX swine_statist_get_MACDST_count(TkrStatist* statist);
extern "C" LIBSWINE_API gint MSCU_CALL_PREFIX swine_statist_get_PID_MACDST_IPSRC_IPDST_IPPROTO_PORTSRC_PORTDST_count(TkrStatist* statist);

extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_statist_SaveToFile(TkrStatist* statist, gconstpchar file_name);

///
// в случае неудачи возвращает 0, swine_get_last_error содержит описание ошибки
extern "C" LIBSWINE_API TkrChopper* MSCU_CALL_PREFIX swine_chopper_create(gpointer AOwner);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_chopper_destroy(TkrChopper* chopper);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_chopper_start(TkrChopper* chopper, TChopperState AState);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_chopper_stop(TkrChopper* chopper);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_chopper_suspend(TkrChopper* chopper);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_chopper_resume(TkrChopper* chopper);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_chopper_idle(TkrChopper* chopper);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_chopper_flush(TkrChopper* chopper);

extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_chopper_set_on_ack(TkrChopper* chopper, TkrChopperAck do_on_ack);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_chopper_set_on_ack_svc(TkrChopper* chopper, TkrChopperAck_svc do_on_ack_svc);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_chopper_set_on_add_filter(TkrChopper* chopper, Tswine_add_filter_control_message do_on_add_filter);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_chopper_set_on_sub_filter(TkrChopper* chopper, Tswine_sub_filter_control_message do_on_sub_filter);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_chopper_set_register_raw_ip(TkrChopper* chopper, gboolean action);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_chopper_set_on_add_filter_2(TkrChopper* chopper, Tswine_add_filter_2_control_message do_on_add_filter_2);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_chopper_set_on_sub_filter_2(TkrChopper* chopper, Tswine_sub_filter_2_control_message do_on_sub_filter_2);

extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_chopper_set_on_out_sorm(TkrChopper* chopper, TkrChopperOutSorm do_on_out_sorm);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_chopper_set_on_out_tag(TkrChopper* chopper, TkrChopperOutTag do_on_out_tag);

extern "C" LIBSWINE_API gboolean MSCU_CALL_PREFIX swine_chopper_perform_process(TkrChopper* chopper, gpointer ts, gint64 size_limit, gboolean suppress_flushing, PProgressEventClass progress_class);

extern "C" LIBSWINE_API TChopperState MSCU_CALL_PREFIX swine_chopper_get_state(TkrChopper* chopper);
extern "C" LIBSWINE_API TkrProtocol* MSCU_CALL_PREFIX swine_chopper_get_decoder(TkrChopper* chopper, gint index);
extern "C" LIBSWINE_API TkrProtocol* MSCU_CALL_PREFIX swine_chopper_FindDecoderByName(TkrChopper* chopper, gconstpchar filter_name);
extern "C" LIBSWINE_API gint MSCU_CALL_PREFIX swine_chopper_get_decoder_count(TkrChopper* chopper);
extern "C" LIBSWINE_API TkrProtocol* MSCU_CALL_PREFIX swine_chopper_get_protocol(TkrChopper* chopper, gint index);
extern "C" LIBSWINE_API TkrProtocol* MSCU_CALL_PREFIX swine_chopper_FindProtocolByName(TkrChopper* chopper, gconstpchar filter_name);
extern "C" LIBSWINE_API gint MSCU_CALL_PREFIX swine_chopper_get_protocol_count(TkrChopper* chopper);
extern "C" LIBSWINE_API TkrProtocol* MSCU_CALL_PREFIX swine_chopper_get_active_decoder(TkrChopper* chopper);
extern "C" LIBSWINE_API gboolean MSCU_CALL_PREFIX swine_chopper_get_ActiveDecoderIsUnique(TkrChopper* chopper, gdouble ratio);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_chopper_set_active_decoder(TkrChopper* chopper, TkrProtocol* decoder);
extern "C" LIBSWINE_API gpointer MSCU_CALL_PREFIX swine_chopper_get_active_encoder(TkrChopper* chopper);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_chopper_set_active_encoder(TkrChopper* chopper, gpointer encoder);
extern "C" LIBSWINE_API gint MSCU_CALL_PREFIX swine_chopper_get_active_network(TkrChopper* chopper);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_chopper_set_active_network(TkrChopper* chopper, gint network);
extern "C" LIBSWINE_API TkrTraceNode* MSCU_CALL_PREFIX swine_chopper_get_trace_root(TkrChopper* chopper);
extern "C" LIBSWINE_API TkrStatist* MSCU_CALL_PREFIX swine_chopper_get_statist(TkrChopper* chopper);
extern "C" LIBSWINE_API gpointer MSCU_CALL_PREFIX swine_chopper_get_prefs_work_dir(TkrChopper* chopper);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_chopper_get_tcpcat_oldest_session(TkrChopper* chopper, Ttimeval* time_value);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_chopper_get_tcpcat_active_sessions(TkrChopper* chopper, TCatSID** sidv, gsize_t* sidc);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_chopper_tcpcat_suppress_active_sessions(TkrChopper* chopper);
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_chopper_tcpcat_update_active_sessions_by_capture(TkrChopper* chopper);

extern "C" LIBSWINE_API gboolean MSCU_CALL_PREFIX swine_chopper_SaveProtoTreeToFile(TkrChopper* chopper, gconstpchar file_name);

//extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_chopper_aaa_link_by_ip(TkrChopper* chopper, guint32 IP, char ***Names, char ***Values);
// if (pid == 0xffffffff) && (lid == 0xffffffff), they are ignored
// if Name=="TMP_UNI_LIST", Value contains UNI values, separated by comma
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_chopper_aaa_link_by_pid_lid_ip(TkrChopper* chopper, guint32 pid, guint32 lid, guint32 ip, const char *** names, const char *** values, gint32 ** value_lens, guint32 ** spots);
// if (PID == 0xffffffff) && (LID == 0xffffffff), they are ignored
// if Name=="TMP_UNI_LIST", Value contains UNI values, separated by comma
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_chopper_aaa_link_by_pid_lid_ipv6(TkrChopper* chopper, guint32 pid, guint32 lid, const guint8 * ipv6, const char ***names, const char ***values, gint32 ** value_lens, guint32 ** spots);

//extern "C" LIBSWINE_API TkrTreeNode* MSCU_CALL_PREFIX proto_tree_add_packet_info(TkrTreeNode* tree, tvbuff_t* tvb, PPacketInfo pi, PPacketInfoEx pi_ex);

// function to process commands received from sorm socket
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_chopper_process_sorm_command(TkrChopper* chopper, TSRMHdr * i_hdr, const guint8 * i_buf);

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// !PORT from tcpcatXXX.h
//////////////////////////////////////////////////////////////////////////

/* статистика плагина */
STRUCT_PACKED_BEGIN // устанавливаем выравнивание структур в 1 байт
struct STRUCT_PACKED_ATTRIBUTE TTCPCATPLUGinStatistics {
  // описание
  gconstpchar name          ;     // тип протокола *)
  gconstpchar short_name    ;     // тип протокола *)
  gconstpchar filter_name   ;     // тип протокола *)
  gconstpchar file_name_full;     // название библиотеки *)
  gconstpchar file_name     ;     // название библиотеки *)
  gconstpchar description   ;     // описание плагина *)
  gconstpchar version       ;     // версия *)
  gconstpchar ini_file      ;     // файл параметров *)

  // параметры *)
  gboolean is_enabled; // разрешен/запрещен
  gboolean is_disabled; // разрешен/запрещен
  gboolean is_discardent; // разрешен/запрещен
  gboolean is_transparent; // разрешен/запрещен

  guint32 whoami_cache_locked ; // ... - в обработке
  guint32 flush_cache_locked  ; // ... - в обработке
  guint32 close_cache_locked  ; // ... - в обработке
  guint32 idle_cache_locked   ; // ... - в обработке

//   guint UpdateTime;

  guint32 sessions_active     ; // количество активных сессий *)
  gint32 sessions_opened     ; // количество открытых сессий *)
  gint32 sessions_closed     ; // количество закрытых сессий *)
  gint64 sessions_bytes      ; // размер сессий в байтах *)

  guint32 sessions_escaped     ; // количество активных сессий *)

  gint64 data_registered           ; // зарегистрировано блоков данных *)
  gint64 old_data_registered       ; // для подсчета скорости *)
  guint old_data_registered_time  ;  // для подсчета скорости *)

  gint64 data_bytes          ; // зарегистрировано в байтах *)
  gint64 old_data_bytes      ; // для подсчета скорости *)
  guint old_data_bytes_time ;  // для подсчета скорости *)

  // кэш данных
  gint64 data_cache_count           ; // количество элементов в кэше данных *)

  gint64 data_cache_bytes           ; // размер элементов в кэше данных *)

  gint64 errors                     ; // количество ошибок *)

  // sid
  guint32 cloned_sids_count          ; // количество клонированных sid *)

  // fhandle
  guint32 fhandle_count          ; // количество клонированных sid *)

  guint32 us_idle_ave         ;
  guint32 us_idle_max         ;
  guint32 us_session_begin_ave;
  guint32 us_session_begin_max;
  guint32 us_session_data_ave ;
  guint32 us_session_data_max ;
  guint32 us_session_end_ave  ;
  guint32 us_session_end_max  ;
};
STRUCT_PACKED_END // восстанавливаем выравнивание структур по умолчанию

//////////////////////////////////////////////////////////////////////////
extern "C" LIBSWINE_API guint32 MSCU_CALL_PREFIX tcpcat_plug_exceptions();

extern "C" LIBSWINE_API void MSCU_CALL_PREFIX htcpcat_info(Tsnapshot_std_function r);

extern "C" LIBSWINE_API void MSCU_CALL_PREFIX htcpcat_session(TTCPCATPI* ca, const guint8* buf, guint len);

extern "C" LIBSWINE_API gpointer MSCU_CALL_PREFIX htcpcat_get();

extern "C" LIBSWINE_API void MSCU_CALL_PREFIX htcpcat_mutex_enter();
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX htcpcat_mutex_leave();

extern "C" LIBSWINE_API gsize_t MSCU_CALL_PREFIX tcpcat_plug_plug_count();
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX tcpcat_plug_plug_stat(gsize_t Index, TTCPCATPLUGinStatistics* stat);

// specialized teri
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX tcpcat_plug_set_specialized_teri(gconstpchar file_name);
extern "C" LIBSWINE_API gpointer MSCU_CALL_PREFIX teri_bis_wrapper_tcpcat_plug_specialized_teri_instance();
extern "C" LIBSWINE_API Tteri_bis_wrapper_statistics* MSCU_CALL_PREFIX teri_bis_wrapper_tcpcat_plug_specialized_teri_statistics();

// complex teri - added 2017-06-01
extern "C" LIBSWINE_API void MSCU_CALL_PREFIX swine_set_complex_teri(gconstpchar file_name);
extern "C" LIBSWINE_API gpointer MSCU_CALL_PREFIX swine_complex_teri_teri_bis_wrapper_instance();
extern "C" LIBSWINE_API Tteri_bis_wrapper_statistics* MSCU_CALL_PREFIX swine_complex_teri_teri_bis_wrapper_statistics();

//////////////////////////////////////////////////////////////////////////

#endif
