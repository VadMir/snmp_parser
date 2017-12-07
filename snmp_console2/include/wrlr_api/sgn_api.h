///
/// sgn_api.h : SGN interface API.
///
/// Changelog:
/// [+] 2017-08-30 - Добавлено: функция	sgn_callback_data_ready_istat_ex в структуру TSGNStandartFunctions (см.описание);
/// [+] 2017-02-13 - Добавлено: константы SGN_ADD_DATA_FLAG_REQUEST_USER_INFO, SGN_ADD_DATA_FLAG_REQUEST_USER_LOCATION (см.описание);
/// [+] 2017-01-24 - Добавлено: возможность экспорта функции wrlr_swine_plugin_init;
/// [+] 2016-10-22 - Добавлено: новые функции для поддержки IPv6 и возможности добавления признаков вторичного отбора (см. функции Tsgn_init_2, Tsgn_set_secondary_token, Tsgn_accept_new_uni_2)
/// [*] 2015-03-03 - Изменено: добавлено поле flags в функции типа TSGNDataReadyTV, SGN_AddData_p
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

/// название библиотеки
#if MSCU_OS_WINDOWS
#define SGN_LIB_NAME "sgn.dll"
#else
#define SGN_LIB_NAME "libsgn.so"
#endif

/// константы для использования внутри TSGNDataReadyTV::flags
#define SGN_DATA_READY_FLAG_DO_MULTICAST_COPY   0x00000001 // предписывает WRLR, помимо отправки пакета на выход, также передать его на вход остальным SGN-обработчикам
                                                           // в других функционирующих WRLR с флагом SGN_ADD_DATA_FLAG_DO_NOT_MULTICAST_COPY

/// константы для использования внутри SGN_AddData_p::flags
#define SGN_ADD_DATA_FLAG_DO_NOT_MULTICAST_COPY 0x00000001 // запрещает SGN-обработчику посылать данный пакет на выход с флагом SGN_DATA_READY_FLAG_DO_MULTICAST_COPY
                                                           // используется, если пакет уже был передан другим SGN-обработчиком с флагом SGN_DATA_READY_FLAG_DO_MULTICAST_COPY
                                                           // данный флаг необходим для предотвращения зацикливания между WRLR
/// константы для использования внутри SGN_AddData_p::flags
#define SGN_ADD_DATA_FLAG_REQUEST_USER_INFO 0x00000002		 // команда запроса информации по абоненту
                                                           // предполагается, что входной буфер содержит данные одноименной команды протокола СОРМ-САЛО #7 (поля UNI, Ext, Data),
                                                           // за исключением общих полей: UNI-C,TvSec, TvUSec, Length (см. описание протокола)
/// константы для использования внутри SGN_AddData_p::flags
#define SGN_ADD_DATA_FLAG_REQUEST_USER_LOCATION 0x00000004 // команда запроса текущего местоположения абонента
                                                           // предполагается, что входной буфер содержит данные одноименной команды протокола СОРМ-САЛО #8 (поле UNI),
                                                           // за исключением общих полей: UNI-C,TvSec, TvUSec, Length (см. описание протокола)

//////////////////////////////////////////////////////////////////////////
// При вызове данной функции из контекста AddData: async==false (!async или async == 0).
// Во всех остальных случаях: async==true (async или async != 0).
typedef int (MSCU_CALL_PREFIX *Tteri_bis_match_data_sgn)(gint count, gconstpointer* bufs, guint* lens, guint* spots, Tteri_bis_match_callback cb, void *ud, gboolean async);
/// Функция отправки очередного пакета
///
/// data - буфер с данными пакета
///        если data = 0, то текущий глобально обрабатываемый пакет доотбирается по ui/ui_ext и уже только после этого отправляется на выход
/// offset - offset to the "left" - size of data link bytes
/// flags - флаги пакета, набор констант SGN_DATA_READY_FLAG_XXX
///
/// возвращает 0 - в случае успеха, иначе - код ошибки
typedef void (MSCU_CALL_PREFIX *TSGNDataReadyTV)(unsigned char *Data, int LengthOfDataInByte, unsigned int offset, unsigned int uni, unsigned int uni_ext, Ttimeval * tv, guint32 flags);

typedef void (MSCU_CALL_PREFIX *Tdata_ready_istat)(unsigned char *Data, int LengthOfDataInByte);
// istat_type - формат статистических данных (константы из swine_api.h):
//   PDT_ISTAT1 - <2И>					
//   PDT_ISTAT2 - <Приказ 83>	  
//   PDT_ISTAT3 - <НТ>					
typedef void (MSCU_CALL_PREFIX *Tdata_ready_istat_ex)(unsigned char *Data, int LengthOfDataInByte, int istat_type);

typedef void (MSCU_CALL_PREFIX *TAddFilterControlMessage)(S10G_FILTER_ITEM_STRUCT* filter_item);
typedef void (MSCU_CALL_PREFIX *TSubFilterControlMessage)(S10G_FILTER_ITEM_STRUCT* filter_item);

/// Данная функция является устаревшей. Используйте "wrlr_init_2" вместо нее.
///
/// экспортируемое имя: "wrlr_Init"
typedef int (MSCU_CALL_PREFIX *SGN_Init_p)(TSGNDataReadyTV DataReadyTV, Tdata_ready_istat data_ready_istat, Tteri_bis_match_data_sgn teri_bis_match_data_sgn, TAddFilterControlMessage wrapper_add_filter_control_message, TSubFilterControlMessage wrapper_sub_filter_control_message);

/// экспортируемое имя: "wrlr_Free"
typedef int (MSCU_CALL_PREFIX *SGN_Free_p)(void);

/// Функция обработки очередного пакета
///
/// экспортируемое имя: "wrlr_AddData"
///
/// offset - offset to the "left" - size of data link bytes
/// flags - флаги пакета, набор констант SGN_ADD_DATA_FLAG_XXX
///
/// if IPPacket==0 && Length==0, idle is invoked (вызывается с периодом, равным 1 сек или 100 мсек)
///
/// возвращает 0 - в случае успеха, иначе - код ошибки
typedef int (MSCU_CALL_PREFIX *SGN_AddData_p)(unsigned char *IPPacket, int Length, unsigned int offset, Ttimeval * tv, guint32 flags);

/// экспортируемое имя: "wrlr_PrintState"
typedef int (MSCU_CALL_PREFIX *SGN_PrintState_p)(Tsnapshot_std_function r);

/// find aaa packet by ip - найти AAA-сессию, соответствующую заданным в filter_item ip-адресам и отправить
/// управляющие AAA-пакеты по заданным unis uni-значениям
///
/// Данная функция является устаревшей. Используйте "wrlr_init_2" вместо нее.
///
/// экспортируемое имя: "wrlr_accept_new_uni"
///
/// filter_item - структура, содержащая ip-адреса (необходимо проверить как ip1, так и ip2)
/// \param in unis - массив значений UNI, к которым относится добавляемый признак
/// \param in unis_count - количество элементов в массиве unis
///
typedef int (MSCU_CALL_PREFIX *SGN_accept_new_uni_p)(S10G_FILTER_ITEM_STRUCT* filter_item, guint32* unis, gsize_t unis_count, Ttimeval* tv);

/// экспортируемое имя: "wrlr_RegisterPrefs"
typedef int (MSCU_CALL_PREFIX *TRegisterPrefs_p)(preference_p owner);

//////////////////////////////////////////////////////////////////////////
// 2016-10-22 new API addons

/// !!!this is modified copy of the type Tplug_callback_srm_set_secondary_token form tcpcat_api.h!!!
/// Добавление вторичного признака в подсистему отбора.
///
/// \param in token_buf - буфер с данными признака
/// \param in token_len - длина буфера с данными признака
/// \param in token_spot - областей поиска \ref teri_bis.h
/// \param in unis - массив значений UNI, к которым относится добавляемый признак
/// \param in unis_count - количество элементов в массиве unis
///
/// !Внимание! Данную функцию можно использовать только внутри вызова plug_session_data.
///
typedef void (MSCU_CALL_PREFIX * Tsgn_callback_srm_set_secondary_token)(gconstpointer token_buf, guint token_len, guint token_spot, guint32 * unis, gsize_t unis_count);

typedef void (MSCU_CALL_PREFIX * Tsgn_callback_add_filter_control_message)(S10G_FILTER_ITEM_STRUCT_2 * filter_item);
typedef void (MSCU_CALL_PREFIX * Tsgn_callback_sub_filter_control_message)(S10G_FILTER_ITEM_STRUCT_2 * filter_item);

/// \struct TSGNStandartFunctions
/// набор стандартных функций обратного вызова
struct TSGNStandartFunctions {
  unsigned int cbSize; ///< размер данной структуры
											 /// при использовании полей структуры необходимо проверять данное поле на то, что размер используемого типа меньше или равен
											 /// значению данного поля, либо проверять каждое используемое поле на предмет нахождения внутри границ, заданных
											 /// значением поля cbSize

	Tteri_bis_match_data_sgn									sgn_callback_teri_bis_match_data_sgn;
	TSGNDataReadyTV														sgn_callback_data_ready_tv;
	Tdata_ready_istat													sgn_callback_data_ready_istat;
  Tsgn_callback_srm_set_secondary_token			sgn_callback_srm_set_secondary_token;
	Tsgn_callback_add_filter_control_message	sgn_callback_add_filter_control_message;
	Tsgn_callback_sub_filter_control_message	sgn_callback_sub_filter_control_message;
	Tdata_ready_istat_ex											sgn_callback_data_ready_istat_ex;
};
/// указатель на структуру TTCPCATStandartFunctions
typedef TSGNStandartFunctions* PSGNStandartFunctions;

/// Функция инициализации работы с интерфейсом SGN.
/// В случае, если модуль экспортирует обе функции инициализации (wrlr_init и wrlr_init_2), то используется только новая версия
///
/// экспортируемое имя: "wrlr_init_2"
///
/// \param SGNStandartFunctions - адрес на структуру, содержащую адреса стандартных функций обратного вызова.
///   Необходимо запомнить во внутренней переменной адрес структуры стандартных функций (сама структура располагается
///     внутри ядра и хранится все время жизни процесса)
///
/// возвращает 0 - в случае успеха, иначе - код ошибки
///
typedef int (MSCU_CALL_PREFIX * Tsgn_init_2)(PSGNStandartFunctions SGNStandartFunctions);

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
typedef int (MSCU_CALL_PREFIX * Tsgn_set_secondary_token)(S10G_FILTER_ITEM_STRUCT_2 * filter_item, Ttimeval* tv, guint32* unis, gsize_t unis_count);

/// find aaa packet by ip - найти AAA-сессию, соответствующую заданным в filter_item ip-адресам и отправить
/// управляющие AAA-пакеты по заданным unis uni-значениям
/// В случае, если модуль экспортирует обе функции (wrlr_accept_new_uni и wrlr_accept_new_uni_2), то используется только новая версия
///
/// экспортируемое имя: "wrlr_accept_new_uni_2"
///
/// \param in filter_item - структура, содержащая ip-адреса
/// \param in tv - TimeStamp
/// \param in unis - массив значений UNI, к которым относится добавляемый признак
/// \param in unis_count - количество элементов в массиве unis
///
typedef int (MSCU_CALL_PREFIX * Tsgn_accept_new_uni_2)(S10G_FILTER_ITEM_STRUCT_2 * filter_item, Ttimeval* tv, guint32* unis, gsize_t unis_count);

/// 2017-01-24
/// Функция инициализации работы в режиме swine_api.
///
/// экспортируемое имя: "wrlr_swine_plugin_init"
/// описание данной - см. swine_api.h
///
///	особенности использования:
///   на данный момент могут быть использованы только функции:
///      plug_proto_register_field_info
///      plug_proto_find_field_info
///   рекомендуемый контекст вызова - внутри функции wrlr_swine_plugin_init
///   первый параметр PPluginProtoStuff stuff игнорируется (может быть равен 0)
///
typedef void (MSCU_CALL_PREFIX * TPluginInit)(PSWINEStandartFunctions SWINEStuff, gpchar adescription, gpchar aversion);

#endif
