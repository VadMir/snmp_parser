// AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! //
// AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! //
// AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! //
// AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! //
/// \file msculib.h
/// \mainpage
/// @{
/// \section attention Предупреждение
/// \b ВНИМАНИЕ! Файл <b>"msculib.h"</b> распространяется под авторским правом РАЗРАБОТЧИКА данного файла.
/// Любые изменения в данном файле СТОРОННИМИ разработчиками НЕДОПУСТИМЫ.
/// Для использования данного файла просто включите его в проект с помощью директивы #include.
///
/// \section changelog Изменения
/// - [+] 2017-07-27 - Добавлено: функции msculib_set_klog_std_event_utf8, klog_utf8, klogf_utf8, log_file_add_utf8, con_out_alt_ln_utf8, con_usage_utf8, con_out_utf8, log_add_std_utf8, log_add_generic_utf8, удалена функция msculib_set_utf8;
/// - [+] 2017-07-27 - Добавлено: функции XXX_memory_managers_enum/XXX_memory_manager_set_name/XXX_memory_manager_set_name для все типов (см. msculib_mm.h);
/// - [+] 2017-07-26 - Добавлено: функция memory_managers_enum (см. msculib_mm.h);
/// - [+] 2017-01-18 - Добавлено: функция memory_manager_set_name (см. msculib_mm.h);
/// - [*] 2012-01-06 - интернационализация
/// - [*] 2010-07-19 - версия 0.9.10.2000
/// - [*] 2010-07-19 - добавлены ber-функции (msculib_ber.h)
/// - [*] 2010-04-21 - глобальная модификация
///
/// \section description Описание
/// Данный документ содержит API функций общего назначения.
///
/// \section copyright Авторские права
/// Copyright (C) MSC, ORG 2002-2009
///
/// @}

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#ifndef __MSCULIB_H
/// \cond
#define __MSCULIB_H
/// \endcond

// #define _SECURE_SCL 0
// #define _CRT_SECURE_NO_WARNINGS
// #define _CRT_NONSTDC_NO_WARNINGS

#include <mscu_types.h>

// Now we use the generic helper definitions above to define XXX_API and XXX_LOCAL.
// XXX_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
// XXX_LOCAL is used for non-api symbols.
#ifdef MSCULIB_EXPORTS // defined if we are building the XXX DLL (instead of using it)
  /// \cond
  #define MSCULIB_API MSCU_HELPER_DLL_EXPORT
  /// \endcond
#else
  /// \cond
  #define MSCULIB_API MSCU_HELPER_DLL_IMPORT
  #pragma comment( lib, "msculib" )
  /// \endcond
#endif // MSCULIB_EXPORTS
#define MSCULIB_LOCAL MSCU_HELPER_DLL_LOCAL

//////////////////////////////////////////////////////////////////////////
// main function used to log message to the console/file (with formatting)
// by default all MT_DEBUG-messages are ignored unless msculib_set_debug is called
// it is strongly recommended to use klogf for MT_DEBUG messages, because message formating is done only if
// MT_DEBUG-messages are enabled by msculib_set_debug
//
// MessageType - on of the MT_XXX constant from mscu_types.h
// MessageFmt - null-terminated printf-like string with format specifiers
//              %s - this format specifier accept (char *) only, not (std::string)!
// ... - parameters for the MessageFmt
extern "C" MSCULIB_API void klogf(gint MessageType, gconstpchar MessageFmt, ...);
// this is UTF-8 version of the above function
// MessageFmt should be UTF-8 encoded
extern "C" MSCULIB_API void klogf_utf8(gint MessageType, gconstpchar MessageFmt, ...);

// main function used to log message to the console/file
// by default all MT_DEBUG-messages are ignored unless msculib_set_debug is called
// MT_DEBUG-messages are enabled by msculib_set_debug
//
// Message - null-terminated string
// MessageType - on of the MT_XXX constant from mscu_types.h
extern "C" MSCULIB_API void MSCU_CALL_PREFIX klog(gconstpchar Message, gint MessageType);
// this is UTF-8 version of the above function
// MessageFmt should be UTF-8 encoded
extern "C" MSCULIB_API void MSCU_CALL_PREFIX klog_utf8(gconstpchar Message, gint MessageType);

//////////////////////////////////////////////////////////////////////////
// set up global log-function to use by klogf/klog
// variants:
// 	 log_add_generic (see msculib_log.h) - output to the standard output and to the log-file only
//	 log_add_std (see msculib_con.h) - output both to the console and file (one must invoke msculib_start_console)
// 	 log_file_add (see msculib_log.h) - output to the log-file only
// by default global log-function is log_add_generic
extern "C" MSCULIB_API void MSCU_CALL_PREFIX msculib_set_klog_std_event(Tklog_std_event Aklog_std_event);
// set up global log-function to use by klogf_utf8/klog_utf8
// variants:
// 	 log_add_generic_utf8 (see msculib_log.h) - output to the standard output and to the log-file only
//	 log_add_std_utf8 (see msculib_con.h) - output both to the console and file (one must invoke msculib_start_console)
// 	 log_file_add_utf8 (see msculib_log.h) - output to the log-file only
// by default global log-function is log_add_generic_utf8
extern "C" MSCULIB_API void MSCU_CALL_PREFIX msculib_set_klog_std_event_utf8(Tklog_std_event Aklog_std_event);
// set up pointer to the gboolean variable use to signal about termination
// use kterminate() to set up this variable to true
// use kterm() to retrieve given variable state (true or false)
// by default address to the _con_terminated is with kterm()/kterminate()
extern "C" MSCULIB_API void MSCU_CALL_PREFIX msculib_set_terminated_flag(gboolean_p Aterminated_flag);

//////////////////////////////////////////////////////////////////////////

// enable output for MT_DEBUG-messages
// by default all MT_DEBUG-messages passed through klog/klogf-functions are ignored
extern "C" MSCULIB_API void MSCU_CALL_PREFIX msculib_set_debug();

// retrieve termination flag (variable set up by msculib_set_terminated_flag) state (true or false)
extern "C" gboolean MSCULIB_API MSCU_CALL_PREFIX kterm();
// writes true to the termination flag (variable set up by msculib_set_terminated_flag)
extern "C" void MSCULIB_API MSCU_CALL_PREFIX kterminate();
// variable used by default with kterm()/kterminate()
// deprecated - do not use it directly
// invoke kterm()/kterminate() instead
extern "C" MSCULIB_API gboolean _con_terminated; //!!!deprecated

// sets launched application instance name value
extern "C" MSCULIB_API void MSCU_CALL_PREFIX msculib_set_process_name(const char * name);
// returns launched application instance name value that was set by msculib_set_process_name
extern "C" MSCULIB_API const char * MSCU_CALL_PREFIX msculib_get_process_name();

//////////////////////////////////////////////////////////////////////////

#include <msculib/msculib_ber.h>
#include <msculib/msculib_time.h>
#include <msculib/msculib_dirlocker.h>
#include <msculib/msculib_mm.h>
#include <msculib/msculib_queue.h>
#include <msculib/msculib_hash.h>
#include <msculib/msculib_loopbuf.h>
#include <msculib/msculib_filereader.h>
#include <msculib/msculib_log.h>
#include <msculib/msculib_tray.h>
#include <msculib/msculib_con.h>
#include <msculib/msculib_i18n.h>

#endif

