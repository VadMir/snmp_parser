///
/// wrrn_snmp_api.h : SNMP plugin interface API.
///
/// Changelog:
/// [+] 2017-10-12 - Добавлено: начальная версия;
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

/// название библиотеки
#if MSCU_OS_WINDOWS
#define WRRN_SNMP_LIB_NAME "wrrn_snmp.dll"
#else
#define WRRN_SNMP_LIB_NAME "libwrrn_snmp.so"
#endif

/// \struct TTCPCATStandartFunctions
/// набор стандартных функций обратного вызова
/*STRUCT_PACKED_BEGIN*/
struct /*STRUCT_PACKED_ATTRIBUTE */TWRRNSNMPStandartFunctions {
  unsigned int cbSize; ///< размер данной структуры
											 /// при использовании полей структуры необходимо проверять данное поле на то, что размер используемого типа меньше или равен
											 /// значению данного поля, либо проверять каждое используемое поле на предмет нахождения внутри границ, заданных
											 /// значением поля cbSize

};
/*STRUCT_PACKED_END*/
/// указатель на структуру TTCPCATStandartFunctions
typedef TWRRNSNMPStandartFunctions* PWRRNSNMPStandartFunctions;

/// \}

/// \defgroup tcpcat_exports Экспортируемые функции
/// \{
/// Данный раздел описывает типы экспортируемых функций для реализации внутри плагина

/// Функция инициализации работы с интерфейсом WRRN_SNMP.
///
/// экспортируемое имя: "wrrn_snmp_init"
///
/// \param WRRNSNMPStandartFunctions - адрес на структуру, содержащую адреса стандартных функций обратного вызова.
///   Необходимо запомнить во внутренней переменной адрес структуры стандартных функций (сама структура располагается
///     внутри ядра и хранится все время жизни процесса)
///
/// \param pref_owner - корневой узел настроек для данного модуля
///		модуль должен произвести регистрацию параметров настройки
///		при регистрации параметров необходимо использовать функции prefs_XXX (см. prefs.h)
///
/// \return возвращает 0 в случае успеха
/// \return если библиотека не смогла нормально загрузиться, должна возратить ненулевое значение (код ошибки), чтобы сервер выгрузил библиотеку
///         в таком случае рекомендуется с помощью msculib::klogf вывести подробное описание ошибки
typedef int (MSCU_CALL_PREFIX * Twrrn_snmp_init)(PWRRNSNMPStandartFunctions WRRNSNMPStandartFunctions, preference_p pref_owner, preference_p pref_bool_owner);

/// выполнение команды: экспортное имя - "wrrn_snmp_perform"
///
/// \param command - действие
///
/// Выполнение дествия (зависит от command)
///  - PERFORM_COMMAND_START - вызывается при запуске нового сеанса обработки
///  - PERFORM_COMMAND_STOP - вызывается при завершении очередного сеанса обработки
///  - PERFORM_COMMAND_IDLE - дает возможность модулю производить фоновую обработку (вызывается с периодом, равным 1 сек или 100 мсек)
///  - PERFORM_COMMAND_CLEAN - команда, предписывающая обработчику очистить статистику
///
/// \return возвращает 0 в случае успеха
/// \return иначе - код ошибки (рекомендуется с помощью msculib::klogf вывести подробное описание ошибки)
///
typedef gint (MSCU_CALL_PREFIX * Twrrn_snmp_perform)(gint command);

// значения, возвращаемые функцией wrrn_snmp_session_data (см. описание)
#define SNMP_SESSION_DATA_RESULT_FORWARD 0
#define SNMP_SESSION_DATA_RESULT_DELETE  1
#define SNMP_SESSION_DATA_RESULT_MODIFY  2

/// обработка данных сессии: экспортное имя - \b "wrrn_snmp_session_data". <br>
///
/// \param[in] sid - идентификатор сессии (адреса и порты).
/// \param[in] direction - направление передачи данных (!0 - от клиента к серверу, 0 - от сервера к клиенту)
/// \param[in] in_buf, in_len - входной буфер с данными	(на данный момент начало буфера не синхронизированно по заголовку SNMP)
/// \param[out] out_buf, out_len - выходной буфер с данными
///   в случае, когда выходной буфер содержит данные, необходимо, чтобы буфер out_buf был актуален по крайней мере
///   до следующего вызова wrrn_snmp_session_data в контексте текущеко потока выполнения
///
/// \return возвращаемые значения (SNMP_SESSION_DATA_RESULT_XXX)
///   SNMP_SESSION_DATA_RESULT_FORWARD - полное перенаправление входного буфера
///   SNMP_SESSION_DATA_RESULT_DELETE  - полное удаление входного буфера
///   SNMP_SESSION_DATA_RESULT_MODIFY  - заменить данные из входного буфера данными из выходного буфера
///
typedef int (MSCU_CALL_PREFIX * Twrrn_snmp_session_data)(TCatSID * sid, gboolean direction, const guint8* in_buf, size_t in_len, guint8** out_buf, size_t * out_len);

/// \}

/// @}

// для использования универсального межплатформенного механизма отображения версии модуля необходимо экспортировать фунцию с именем get_version
// а также менять значения версии и даты вручную при каждом релизе
// пример:
// extern "C" MSCU_HELPER_DLL_EXPORT char * MSCU_CALL_PREFIX get_version()
// {
// #define MSCU_MY_VERSION "2.14.21.2017-09-24"
// 	return MSCU_MY_VERSION;
// }

#endif
