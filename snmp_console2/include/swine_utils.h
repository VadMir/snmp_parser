/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/*
 * ВНИМАНИЕ! Данный файл распространяется под авторским правом РАЗРАБОТЧИКА данного файла.
 * Любые изменения в данном файле СТОРОННИМИ разработчиками НЕДОПУСТИМЫ.
 * Для использования данного файла просто включите его в проект с помощью директивы #include.
 */
/* swine_utils.h
 */
// changelog/изменения
// -------------------
// [+] 2017-06-13 - Добавлено - функция TIProto::has_complex_teri_match_retro
// [+] 2017-06-13 - Добавлено - функция TIProto::complex_teri_match_retro
// [+] 2017-06-05 - Добавлено - функция TIProto::has_complex_teri_match
// [+] 2017-06-05 - Добавлено - функция TIProto::complex_teri_match
// [+] 2017-06-05 - Добавлено - функция TIProto::has_ack_raw
// [+] 2017-06-05 - Добавлено - функция TIProto::ack_raw
// [+] 2016-12-27 - Добавлено - типы функций Tproto_aaa_link_by_ip, Tproto_aaa_link_by_pid_lid_ip (изменение параметров), Tproto_aaa_link_by_pid_lid_ipv6 (изменение параметров), Tproto_aaa_set_secondary_token
// [+] 2016-11-24 - Добавлено - функция TIProto::srm_set_secondary_token;
// [+] 2016-11-24 - Добавлено - функция TIProto::srm_set_secondary_token2;
// [+] 2016-11-13 - Добавлено - функция TIProto::packet_info_tolens_clone
// [+] 2016-10-23 - Добавлено - функция TIProto::add_filter_2
// [+] 2016-10-23 - Добавлено - функция TIProto::sub_filter_2
// [+] 2016-04-26 - Добавлено - функция TIProto::add_filter
// [+] 2016-04-26 - Добавлено - функция TIProto::sub_filter
// [+] 2016-04-26 - Добавлено - функция TIProto::srm_teri_match;
// 2014-06-27 - TIProto - добавлены функции ack_ex_svc, forward_packet_and_ack_ex_svc, has_ack_ex_svc, has_forward_packet_and_ack_ex_svc
// 2012-04-04 - TIProto - добавлены функции file_create, file_write, file_close
// 2010-12-27 - TIProto - добавлена packet_info_ex_set_ident_info
// 2008-11-21 - TIProto - добавлена heur_dissector_add
// 2008-11-21 - TIProto - добавлена get_swine
//
/*
 * Plugin API for War Pig 0.9 (Swine 0.8) - UTILS
 *
 * War Pig (wrpg) - Network Protocol Dissector
 * Copyright (C) 2002-2010 MSC, ORG
 */
#pragma once

#if !defined(SWINE_UTILS_H)
#define SWINE_UTILS_H

#include <swine_api.h>
#include <mscu_tvb.h>
#include <msculib/msculib.h>
#include <stdio.h>
#include <stddef.h>

#if !MSCU_COMP_MSVC
#define _snprintf snprintf
#define sprintf_s snprintf
#endif

// глобальный указатель на стандартные функции
// !данная переменная должна быть определена в одном из CPP-модулей проекта!
extern PSWINEStandartFunctions swine;

//////////////////////////////////////////////////////////////////////////////
// функции для работы с буфером tvbuff_t
//////////////////////////////////////////////////////////////////////////////
inline guint8 tvb_get_guint8(tvbuff_t *tvb, gint offset)
{
  return tvb->buf[offset];
}

inline guint16 tvb_get_ntohs(tvbuff_t* tvb, gint offset)
{
  return pntoh16(&tvb->buf[offset]);
}

inline guint32 tvb_get_ntoh24(tvbuff_t* tvb, gint offset)
{
  return pntoh24(&tvb->buf[offset]);
}

inline guint32 tvb_get_ntohl(tvbuff_t* tvb, gint offset)
{
  return pntoh32(&tvb->buf[offset]);
}

inline guint64 tvb_get_ntoh64(tvbuff_t* tvb, gint offset)
{
  return pntoh64(&tvb->buf[offset]);
}

inline guint16 tvb_get_letohs(tvbuff_t* tvb, gint offset)
{
  return pletoh16(&tvb->buf[offset]);
}

inline guint32 tvb_get_letoh24(tvbuff_t* tvb, gint offset)
{
  return pletoh24(&tvb->buf[offset]);
}

inline guint8 * tvb_get_ptr(tvbuff_t* tvb, gint offset, gint/* len*/)
{
//???   len;
  return ( guint8 * )&tvb->buf[offset];
}

inline tvbuff_t tvb_new_subset(tvbuff_t* tvb, gint offset, gint backing_offset)
{
  tvbuff_t new_tvb = { tvb->len, tvb->buf, tvb->offset };
  if (offset != -1) {
          new_tvb.len -= offset;
          new_tvb.buf += offset;
          new_tvb.offset += offset;
  }
  if (backing_offset != -1) {
          new_tvb.len -= backing_offset;
  }
  return new_tvb;
}

inline tvbuff_t* tvb_set_buf(tvbuff_t* tvb, const guint8* abuf, gsize_t alen, gsize_t aoffset = 0)
{
  assert(tvb != 0);
  tvb->buf = (guint8*)abuf;
  tvb->len = alen;
  tvb->offset = aoffset;
  return tvb;
}

inline void tvb_forward(tvbuff_t* tvb, gsize_t bytes)
{
  assert(tvb != 0);
  assert(bytes <= tvb->len);
  tvb->buf += bytes;
  tvb->len -= bytes;
  tvb->offset += bytes;
}

inline void tvb_reward(tvbuff_t* tvb, gsize_t bytes)
{
  assert(tvb != 0);
  tvb->buf -= bytes;
  tvb->len += bytes;
  if (tvb->offset < bytes)
		tvb->offset = 0;
	else
		tvb->offset -= bytes;
}

inline void tvb_truncate(tvbuff_t* tvb, gsize_t bytes)
{
  assert(tvb != 0);
  assert(bytes <= tvb->len);
  tvb->len -= bytes;
}

inline gboolean tvb_bytes_exist(tvbuff_t* tvb, gint offset, gsize_t len)
{
  assert(tvb != 0);
  return tvb->len >= (len + offset);
}

//////////////////////////////////////////////////////////////////////////////
// базовый класс-обертка для создания обработчиков
//////////////////////////////////////////////////////////////////////////////
class LOCAL_API  TIProto {
public:
  TIProto(PPluginProtoStuff stuff): stuff_(stuff) {}
  virtual ~TIProto() {}

  PPluginProtoStuff get_stuff()
  {
    return stuff_;
  }

  /* wrappers */
  void add_log(gconstpchar message, gint message_type)
  {
    (*swine->plug_proto_add_log)(stuff_, message, message_type);
  }
  void ack(tvbuff_t* tvb, PPacketInfo pi)
  {
    (*swine->plug_proto_ack)(stuff_, tvb, pi);
  }

  void ack_ex(tvbuff_t* tvb, PPacketInfo pi, PPacketInfoEx pi_ex)
  {
    (*swine->plug_proto_ack_ex)(stuff_, tvb, pi, pi_ex);
  }

	// return true if given function is supported by API
  bool has_ack_ex_svc()
  {
    return swine->cbSize > offsetof(TSWINEStandartFunctions, plug_proto_ack_ex_svc);
  }

  void ack_ex_svc(tvbuff_t* tvb, PPacketInfo pi, PPacketInfoEx pi_ex, tvbuff_t* tvb_svc)
  {
    (*swine->plug_proto_ack_ex_svc)(stuff_, tvb, pi, pi_ex, tvb_svc);
  }

	// return true if given function is supported by API
  bool has_ack_raw()
  {
    return swine->cbSize > offsetof(TSWINEStandartFunctions, plug_proto_ack_raw);
  }

	// read description for: swine_api.h::Tplug_proto_ack_raw
	void ack_raw(tvbuff_t* tvb, PPacketInfo pi, guint32 * uins, guint32 * uins_ext, guint32 uins_count, Ttimeval * tv, guint32 flags)
	{
		(*swine->plug_proto_ack_raw)(stuff_, tvb, pi, uins, uins_ext, uins_count, tv, flags);
	}

  void register_dissector(gconstpchar name)
  {
    (*swine->plug_proto_register_dissector)(stuff_, name);
  }
  gpointer find_dissector(gconstpchar name) {
    return (*swine->plug_proto_find_dissector)(stuff_, name);
  }
  gpointer find_dissector_table(gconstpchar name)
  {
    return (*swine->plug_proto_find_dissector_table)(stuff_, name);
  }
  gpointer find_heur_dissector_list(gconstpchar name)
  {
    return (*swine->plug_proto_find_heur_dissector_list)(stuff_, name);
  }
  void dissector_add(gconstpchar name, guint32 pattern)
  {
          (*swine->plug_proto_dissector_add)(stuff_, name, pattern);
  }
  void heur_dissector_add(gconstpchar name)
  {
          (*swine->plug_proto_heur_dissector_add)(stuff_, name);
  }
  gpointer register_dissector_table(gconstpchar name, gint key_type) {
    return (*swine->plug_proto_register_dissector_table)(stuff_, name, key_type);
  }
  gpointer register_heur_dissector_list(gconstpchar name)
  {
    return (*swine->plug_proto_register_heur_dissector_list)(stuff_, name);
  }
  void register_field_info(gconstpchar name, gpointer value) {
    (*swine->plug_proto_register_field_info)(stuff_, name, value);
  }
  gpointer find_field_info(gconstpchar name)
  {
    return (gbyte_p)(*swine->plug_proto_find_field_info)(stuff_, name);
  }
  gboolean dissector_try_port(gpointer sub_dissectors, guint32 port, tvbuff_t* tvb, PPacketInfo pi) {
    return (*swine->plug_proto_dissector_try_port)(stuff_, sub_dissectors, port, tvb, pi);
  }
  gboolean dissector_try_heuristic(gpointer sub_dissectors, tvbuff_t* tvb, PPacketInfo pi)
  {
    return (*swine->plug_proto_dissector_try_heuristic)(stuff_, sub_dissectors, tvb, pi);
  }
  gboolean forward_packet(gpointer proto, tvbuff_t* tvb, PPacketInfo pi) {
    return (*swine->plug_proto_forward_packet)(stuff_, proto, tvb, pi);
  }
  gboolean forward_packet_and_ack(gpointer proto, tvbuff_t* tvb, PPacketInfo pi) {
    return (*swine->plug_proto_forward_packet_and_ack)(stuff_, proto, tvb, pi);
  }

  gboolean forward_packet_and_ack_ex(gpointer proto, tvbuff_t* tvb, PPacketInfo pi, PPacketInfoEx pi_ex)
  {
    return (*swine->plug_proto_forward_packet_and_ack_ex)(stuff_, proto, tvb, pi, pi_ex);
  }

	// return true if given function is supported by API
  bool has_forward_packet_and_ack_ex_svc()
  {
    return swine->cbSize > offsetof(TSWINEStandartFunctions, plug_proto_forward_packet_and_ack_ex_svc);
  }

  gboolean forward_packet_and_ack_ex_svc(gpointer proto, tvbuff_t* tvb, PPacketInfo pi, PPacketInfoEx pi_ex, tvbuff_t* tvb_svc)
  {
    return (*swine->plug_proto_forward_packet_and_ack_ex_svc)(stuff_, proto, tvb, pi, pi_ex, tvb_svc);
  }

  gconstpchar val_to_str(gint32 value, const TValueString* glossary,  gconstpchar default_value = 0) {
//    return (*swine->plug_val_to_str)(value, glossary, default_value);
    assert(glossary != 0);
   const value_string* p = glossary;
    if (p) {
      while ((value_string*)p->s) {
        if (p->v == value)
          return p->s;
        ++p;
      }
    }
    return default_value;
  }
  PkrTreeNode proto_tree_add(PkrTreeNode AParent, gconstpchar AText) {
    return (*swine->plug_tree_add)(AParent, AText);
  }
  PkrTreeNode proto_tree_add_bool(PkrTreeNode AParent, gconstpchar AText, const true_false_string* tfv, gboolean value)
  {
    gchar sbuf[1024];

    sprintf_s(sbuf, sizeof(sbuf), "%s: %s", AText, (value ? tfv->true_string : tfv->false_string));
    return proto_tree_add(AParent, sbuf);
  }

  PkrTreeNode proto_tree_add_uint(PkrTreeNode AParent, gconstpchar AText, value_string* vs, gboolean value)
  {
    gchar sbuf[1024];
    if (vs) {
      sprintf_s(sbuf, sizeof(sbuf), "%s: %s (0x%.2x)", AText, val_to_str(value, vs, _EN ? "Unknown" : "Неизвестен"), value);
      return proto_tree_add(AParent, sbuf);
    } else {
      sprintf_s(sbuf, sizeof(sbuf), "%s: 0x%.2x", AText, (value));
      return proto_tree_add(AParent, sbuf);
    }
  }

  void set_network(gint network)
  {
    (*swine->plug_proto_set_network)(stuff_, network);
  }
  void ack_frame(tvbuff_t* tvb, PPacketInfo pi) {
    (*swine->plug_proto_ack_frame)(stuff_, tvb, pi);
  }

  void packet_info_clear(PPacketInfo PacketInfo)
  {
    (*swine->packet_info_clear)(PacketInfo);
  }

  void packet_info_free(PPacketInfo PacketInfo)
  {
    (*swine->packet_info_free)(PacketInfo);
  }

  PPacketInfo packet_info_clone(PPacketInfo pi)
  {
    return (*swine->packet_info_clone)(pi);
  }

  void packet_info_tokens_clone(PPacketInfo src, PPacketInfo dst)
  {
    (*swine->packet_info_tokens_clone)(src, dst);
  }

  TPacketInfoEx* packet_info_ex_malloc()
  {
    return (*swine->packet_info_ex_malloc)();
  }

  void packet_info_ex_set_description(TPacketInfoEx* pi_ex, gconstpchar buf)
  {
    (*swine->packet_info_ex_set_description)(pi_ex, buf);
  }

  void packet_info_ex_set_generic_name(TPacketInfoEx* pi_ex, gconstpchar buf)
  {
    (*swine->packet_info_ex_set_generic_name)(pi_ex, buf);
  }

  void packet_info_ex_set_ident_info(TPacketInfoEx* pi_ex, gconstpchar buf)
  {
    (*swine->packet_info_ex_set_ident_info)(pi_ex, buf);
  }

  value_string* wtap_encap_get_vals()
  {
    return (*swine->wtap_encap_get_vals)();
  }
  guint wtap_encap_register(gconstpchar name, gconstpchar filter_name)
  {
    return (*swine->wtap_encap_register)(name, filter_name);
  }

  gint file_create(gint flags, void ** fhandle)
  {
    return (*swine->plug_file_create)(stuff_, flags, fhandle);
  }
  gint file_write(void * fhandle, const void * buf, gsize_t len, gint64 offset)
  {
    return (*swine->plug_file_write)(stuff_, fhandle, (void *)buf, len, offset);
  }
  gint file_read(void * fhandle, void * buf, gsize_t len, gint64 offset)
  {
    return (*swine->plug_file_read)(stuff_, fhandle, buf, len, offset);
  }
  gint file_close(void * fhandle)
  {
    return (*swine->plug_file_close)(stuff_, fhandle);
  }

  gint srm_teri_match(PPacketInfo pi, gint count, gconstpointer* bufs, guint* lens, guint* spots, Tteri_bis_match_callback cb, void *ud)
  {
    return (*swine->plug_proto_srm_teri_match)(stuff_, pi, count, bufs, lens, spots, cb, ud);
  }

  void add_filter(S10G_FILTER_ITEM_STRUCT* filter_item)
  {
    (*swine->plug_proto_add_filter)(stuff_, filter_item);
  }

  void sub_filter(S10G_FILTER_ITEM_STRUCT* filter_item)
  {
    (*swine->plug_proto_sub_filter)(stuff_, filter_item);
  }

  void add_filter_2(S10G_FILTER_ITEM_STRUCT_2 * filter_item)
  {
    (*swine->plug_proto_add_filter_2)(stuff_, filter_item);
  }

  void sub_filter_2(S10G_FILTER_ITEM_STRUCT_2 * filter_item)
  {
    (*swine->plug_proto_sub_filter_2)(stuff_, filter_item);
  }

	void srm_set_secondary_token(gconstpointer token_buf, guint token_len, guint token_spot, gboolean token_is_indirect, guint32 * uins, guint32 uins_count)
  {
    (*swine->plug_proto_srm_set_secondary_token)(stuff_, token_buf, token_len, token_spot, token_is_indirect, uins, uins_count);
  }

	void srm_set_secondary_token2(S10G_FILTER_ITEM_STRUCT_2 * filter_item, Ttimeval* tv, guint32* unis, gsize_t unis_count)
  {
    (*swine->plug_proto_srm_set_secondary_token2)(stuff_, filter_item, tv, unis, unis_count);
  }

	// return true if given function is supported by API
  bool has_complex_teri_match()
  {
    return swine->cbSize > offsetof(TSWINEStandartFunctions, plug_proto_complex_teri_match);
  }

	// read description for: swine_api.h::Tplug_proto_complex_teri_match
	gint complex_teri_match(guint32 flags, PPacketInfo pi, gint count, gconstpchar* bufs, gint32* lens, guint32* spots, Tteri_bis_match_callback cb, void *ud, gboolean * has_rf_decoded, gboolean * has_rf_raw, guint32 ** out_uins, guint32 ** out_uins_ext, guint32 * out_uins_count)
	{
		return (*swine->plug_proto_complex_teri_match)(stuff_, flags, pi, count, bufs, lens, spots, cb, ud, has_rf_decoded, has_rf_raw, out_uins, out_uins_ext, out_uins_count);
	}

	// return true if given function is supported by API
  bool has_complex_teri_match_retro()
  {
    return swine->cbSize > offsetof(TSWINEStandartFunctions, plug_proto_complex_teri_match_retro);
  }

	// read description for: swine_api.h::Tplug_proto_complex_teri_match
	gint complex_teri_match_retro(guint32 flags, PPacketInfo pi, gint count, gconstpointer* bufs, guint* lens, guint* spots, Tteri_bis_match_callback cb, void *ud, gboolean * has_rf_decoded, gboolean * has_rf_raw, guint32 ** out_uins, guint32 ** out_uins_ext, guint32 * out_uins_count)
	{
		return (*swine->plug_proto_complex_teri_match_retro)(stuff_, flags, pi, count, bufs, lens, spots, cb, ud, has_rf_decoded, has_rf_raw, out_uins, out_uins_ext, out_uins_count);
	}

private:
  TIProto() {}; // hide default constructor
  TIProto(TIProto&) {}; // hide default constructor
  PPluginProtoStuff stuff_;
};

//////////////////////////////////////////////////////////////////////////////
// функции-шаблоны для регистрации обработчиков, созданных на базе TIProto
//////////////////////////////////////////////////////////////////////////////
template<class Tproto>
static gpointer MSCU_CALL_PREFIX tmpl_proto_create(PPluginProtoStuff stuff)
{
  return new Tproto(stuff);
}

template<class Tproto>
static gpointer MSCU_CALL_PREFIX tmpl_proto_create_wud(PPluginProtoStuff stuff, gpointer user_data)
{
  return new Tproto(stuff, user_data);
}

template<class Tproto>
static void MSCU_CALL_PREFIX tmpl_proto_destroy(PPluginProtoStuff stuff)
{
  delete (Tproto*)stuff->plug_inst;
}

template<class Tproto>
static gboolean MSCU_CALL_PREFIX tmpl_proto_perform(PPluginProtoStuff stuff, gint command)
{
  Tproto& me = *((Tproto*)stuff->plug_inst);
  return me.perform(command);
}

template<class Tproto>
static void MSCU_CALL_PREFIX tmpl_proto_crop(PPluginProtoStuff stuff, tvbuff_t* pvb, PPacketInfo pi, PkrTreeNode tree)
{
  Tproto& me = *((Tproto*)stuff->plug_inst);
  me.crop(pvb, pi, tree);
}

template<class Tproto>
static gboolean MSCU_CALL_PREFIX tmpl_proto_heur(PPluginProtoStuff stuff, tvbuff_t* pvb, PPacketInfo pi)
{
  Tproto& me = *((Tproto*)stuff->plug_inst);
  return me.heur(pvb, pi);
}

template<class Tproto>
static void MSCU_CALL_PREFIX tmpl_proto_info(PPluginProtoStuff stuff, PkrTreeNode tree)
{
  Tproto& me = *((Tproto*)stuff->plug_inst);
  me.info(tree);
}

//////////////////////////////////////////////////////////////////////////
// functions and symbols exported from AAA plugin/protocol
//////////////////////////////////////////////////////////////////////////

//--- AAA AddOn
// !deprecated!
// function name (to locate with find_field_info): "aaa.link_by_ip_ptr"
typedef void (MSCU_CALL_PREFIX * Tproto_aaa_link_by_ip)(guint32 ip, const char *** names, const char *** values);

//--- AAA AddOn - 2014-12-23, updated 2016-12-27
// function name (to locate with find_field_info): "aaa.link_by_pid_lid_ip_ptr"
//
// pid - channel PID value
// lid - channel LID value
// ip - IPv4-address value
// names - pointer to the array of identifier names (can be 0)
//   is used in FSI
//   last element value must be (const char *)0 to denote end of array
// values - pointer to the array of identifier values (can be 0)
//   is used in FSI and teri engine
//   last element value must be (const char *)0 to denote end of array
// value_lens - pointer to the array of value lengths (can be 0)
// spots - pointer to the array of spot values (constant TERI_BIS_SPOT_XXX - from teri_bis.h) (can be 0)
//   in case that corresponding item from <values> array is not intended to be in use with teri engine, its spot value must be set to <TERI_BIS_SPOT_NONE>
//
// arrays <names>, <values>, <value_lens>, <spots> are maintained by callee and are actual at least till the next function invocation
typedef void (MSCU_CALL_PREFIX * Tproto_aaa_link_by_pid_lid_ip)(guint32 pid, guint32 lid, guint32 ip, const char *** names, const char *** values, gint32 ** value_lens, guint32 ** spots);

//--- AAA AddOn - 2016-11-10, updated 2016-12-27
// function name (to locate with find_field_info): "aaa.link_by_pid_lid_ipv6_ptr"
//
// pid - channel PID value
// lid - channel LID value
// ipv6 - pointer to the IPv6-address value (can not be 0)
// names - pointer to the array of identifier names (can be 0)
//   is used in FSI
//   last element value must be (const char *)0 to denote end of array
// values - pointer to the array of identifier values (can be 0)
//   is used in FSI and teri engine
//   last element value must be (const char *)0 to denote end of array
// value_lens - pointer to the array of value lengths (can be 0)
// spots - pointer to the array of spot values (constant TERI_BIS_SPOT_XXX - from teri_bis.h) (can be 0)
//   in case that corresponding item from <values> array is not intended to be in use with teri engine, its spot value must be set to <TERI_BIS_SPOT_NONE>
//
// arrays <names>, <values>, <value_lens>, <spots> are maintained by callee and are actual at least till the next function invocation
typedef void (MSCU_CALL_PREFIX * Tproto_aaa_link_by_pid_lid_ipv6)(guint32 pid, guint32 lid, const guint8 * ipv6, const char ***names, const char ***values, gint32 ** value_lens, guint32 ** spots);

//--- AAA AddOn
/// Функция добавления вторичных признаков в подсистему отбора
/// вызвать функцию sgn_callback_srm_set_secondary_token с AAA-атрибутами для заданных uni-значений по критерию filter_item/tv
///
/// экспортируемое имя: "wrlr_set_secondary_token"
///
/// \param in filter_item - структура, содержащая ip-адреса (1 или 2)
/// \param in tv - TimeStamp
/// \param in unis - массив значений UNI, к которым относится добавляемый признак
/// \param in unis_count - количество элементов в массиве unis
///
// function name (to locate with find_field_info): "aaa.set_secondary_token_ptr"
typedef int (MSCU_CALL_PREFIX * Tproto_aaa_set_secondary_token)(S10G_FILTER_ITEM_STRUCT_2 * filter_item, Ttimeval* tv, guint32* unis, gsize_t unis_count);

#endif /* SWINE_UTILS_H */
