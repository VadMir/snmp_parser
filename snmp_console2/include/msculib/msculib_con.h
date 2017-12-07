/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/*
 * mscu_dirlocker.h : Directory Locker
 *
 * Copyright (C) MSC, ORG 2007-2017
 */

#pragma once

#ifndef MSCULIB_CON_H
#define MSCULIB_CON_H

//////////////////////////////////////////////////////////////////////////
// флаг, запрещающий вызов функции log_file_add(log_file_add_utf8) из функций log_add_std(log_add_std_utf8)/log_add_generic(log_add_generic_utf8)
// значение по-умолчанию - false
extern "C" MSCULIB_API gboolean log_supress_write_to_file;
// установка значени€ флага log_supress_write_to_file
extern "C" MSCULIB_API void MSCU_CALL_PREFIX set_log_supress_write_to_file(gboolean value);

//////////////////////////////////////////////////////////////////////////
// calls log_file_add (if flag log_supress_write_to_file is enabled) and writes message to the standard output invoking printf
// рекомендуемое использование - через msculib_set_klog_std_event/klogf/klog (см. msculib.h)
extern "C" MSCULIB_API void MSCU_CALL_PREFIX log_add_generic(const char* msg, gint msg_type = MT_INFORMATION);

// calls log_file_add_utf8 (if flag log_supress_write_to_file is enabled) and writes message to the standard output invoking printf
//
// msg should be in UTF-8 encoding
//
// рекомендуемое использование - через msculib_set_klog_std_event_utf8/klogf_utf8/klog_utf8 (см. msculib.h)
extern "C" MSCULIB_API void MSCU_CALL_PREFIX log_add_generic_utf8(const char* msg, gint msg_type = MT_INFORMATION);

// вывод сообщени€ на экран и в лог-файл (в зависимости от флага log_supress_write_to_file)
// рекомендуемое использование - через msculib_set_klog_std_event/klogf/klog (см. msculib.h)
//
// if message msg is repeated, then message like <Last message repeated N times!> is printed when
// new distinct message comes or when 10 seconds elapsed
extern "C" MSCULIB_API void MSCU_CALL_PREFIX log_add_std(const char* msg, gint msg_type = MT_INFORMATION);

// вывод сообщени€ на экран и в лог-файл (в зависимости от флага log_supress_write_to_file)
// рекомендуемое использование - через msculib_set_klog_std_event_utf8/klogf_utf8/klog_utf8 (см. msculib.h)
//
// msg should be in UTF-8 encoding
//
// if message msg is repeated, then message like <Last message repeated N times!> is printed when
// new distinct message comes or when 10 seconds elapsed
extern "C" MSCULIB_API void MSCU_CALL_PREFIX log_add_std_utf8(const char* msg, gint msg_type = MT_INFORMATION);

//////////////////////////////////////////////////////////////////////////
// инициализаци€ консоли
// необходимо вызвать данную функцию до вызова любой функции, объ€вленной ниже
// given function calls msculib_set_klog_std_event(log_add_std)
//
// Signal/CtrlHandler setup:
//   for linux: <signal> function with SIGINT, SIGTERM is invoked (standard routine is replaced)
//   for windows: SetConsoleCtrlHandler function is invoked (standard routine is not replaced)
//   user defined routine simply calls kterminate() to set the termination flag
//	 if one needs to change/redefine signal handler, new function should call kterminate() function for proper auxilliary work
extern "C" MSCULIB_API void MSCU_CALL_PREFIX msculib_start_console();

// returns console width in chars
extern "C" MSCULIB_API gint MSCU_CALL_PREFIX con_width();
// returns console height in chars
extern "C" MSCULIB_API gint MSCU_CALL_PREFIX con_height();

// returns true if ch contains pressed char code
// returns false if no char was pressed
extern "C" MSCULIB_API gboolean MSCU_CALL_PREFIX con_hit_char(gint * ch);

// set standard	log console as visible om the top
extern "C" MSCULIB_API void MSCU_CALL_PREFIX con_set_active_std();
// set alternative console as visible om the top
extern "C" MSCULIB_API void MSCU_CALL_PREFIX con_set_active_alt_std();

//////////////////////////////////////////////////////////////////////////
// functions to work with standard screen

// clears standard console screen
extern "C" MSCULIB_API void MSCU_CALL_PREFIX con_cls();

// prints message to the standard console and to the log file, invoking log_file_add(log_file_add_utf8)
// coloring rules (by msg_type):
//   MT_INFORMATION: grey
//   MT_ERROR: light red
//   MT_WARNING: red
//   MT_PROCESS: light blue
//   MT_RESULT: yellow
//   MT_PROGRESS_BEGIN, MT_PROGRESS, MT_PROGRESS_END: light green
//   MT_DEBUG: magenta
//   otherwise - grey
extern "C" MSCULIB_API void MSCU_CALL_PREFIX con_out(gconstpchar msg, gint msg_type = MT_INFORMATION);
// this is UTF-8 version of the above function
// msg should have UTF-8 encoding
extern "C" MSCULIB_API void MSCU_CALL_PREFIX con_out_utf8(gconstpchar msg, gint msg_type = MT_INFORMATION);

//////////////////////////////////////////////////////////////////////////
// functions to work with alternative screen

// starts writing lines to the alternative console: clears screen and move cursor to the top
// the next step is invoking of con_out_alt_ln per every line
// the last step is invoking the con_alt_stop to flush the output
extern "C" MSCULIB_API void MSCU_CALL_PREFIX con_alt_start();

// prints message to the alternative console
// coloring rules:
//   line started with | - yellow
//   text surrounded with  [..] - green
//   text surrounded with *[..] - light green
//   text surrounded with  {..} - red
//   text surrounded with *{..} - light red
//   otherwise - grey
extern "C" MSCULIB_API void MSCU_CALL_PREFIX con_out_alt_ln(gconstpchar msg);
// this is UTF-8 version of the above function
// msg should have UTF-8 encoding
extern "C" MSCULIB_API void MSCU_CALL_PREFIX con_out_alt_ln_utf8(gconstpchar msg);

// finishes writing to the alternative consiole procedure
// should be called after con_alt_start+con_out_alt_ln
// fills the rest of screen with empty chars and redraw screen if possible
extern "C" MSCULIB_API void MSCU_CALL_PREFIX con_alt_stop();

//////////////////////////////////////////////////////////////////////////
// miscellaneous functions

//////////////////////////////////////////////////////////////////////////
// sets up console title (windows)
extern "C" MSCULIB_API void MSCU_CALL_PREFIX my_set_console_title(gconstpchar title);

//////////////////////////////////////////////////////////////////////////
/* updated frequency (in milliseconds) */
extern "C" MSCULIB_API guint con_progress_granularity;
extern "C" MSCULIB_API guint con_title_granularity;
extern "C" MSCULIB_API void MSCU_CALL_PREFIX set_con_progress_granularity(guint value);
extern "C" MSCULIB_API void MSCU_CALL_PREFIX set_con_title_granularity(guint value);

// prints multiline text to the console
extern "C" MSCULIB_API void MSCU_CALL_PREFIX con_usage(gconstpchar msg);
// this is UTF-8 version of the above function
// msg should have UTF-8 encoding
extern "C" MSCULIB_API void MSCU_CALL_PREFIX con_usage_utf8(gconstpchar msg);

#endif

