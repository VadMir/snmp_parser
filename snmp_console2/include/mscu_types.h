/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/// \file mscu_types.h
/// \page mscu_types Стандартные типы
/// @{
/// \section attention Предупреждение
/// \b ВНИМАНИЕ! Файл <b>"mscu_types.h"</b> распространяется под авторским правом РАЗРАБОТЧИКА данного файла.
/// Любые изменения в данном файле СТОРОННИМИ разработчиками НЕДОПУСТИМЫ.
/// Для использования данного файла просто включите его в проект с помощью директивы #include.
///
/// \section changelog Изменения
/// [+] 2016-06-09 - Добавлено: STRUCT_PACKED_ATTRIBUTE, STRUCT_PACKED_BEGIN, STRUCT_PACKED_END
/// [+] 2015-11-15 - Добавлено: тип сообщения - MT_DEBUG
/// [*] 2015-01-13 - добавлен тим - Ttimespec
/// [*] 2011-05-19 - обновление документации
/// [*] 2009-04-17 - разработка
///
/// \section description Описание
/// Данный документ содержит описание базовых типов, используемых в различных программных интерфейсах.
///
/// \section copyright Авторские права
/// Copyright (C) MSC, ORG 2007-2011
///
/// @}

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#ifndef MSCU_TYPES_H
/// \cond
#define MSCU_TYPES_H
/// \endcond

#include <stdint.h>

#define NOMINMAX // this is for windows users to avoid widows.h min/max definition

#if defined(_MSC_VER)
#if !defined(_SECURE_SCL)
	#define _SECURE_SCL 0
#endif
#if !defined(_CRT_SECURE_NO_WARNINGS)
	#define _CRT_SECURE_NO_WARNINGS
#endif
#if !defined(_CRT_NONSTDC_NO_WARNINGS)
	#define _CRT_NONSTDC_NO_WARNINGS
#endif
#endif

#define MSCU_OS_WINDOWS 0

#if ( \
    defined(_WIN32) || defined(_WIN64) || \
    defined(__WIN32__) || defined(__TOS_WIN__) || \
    defined(__WINDOWS__) \
    )
#   undef MSCU_OS_WINDOWS
#   define MSCU_OS_WINDOWS 1

    /* MSVC predefines _WIN64 for 64 bit builds, for gcc we use generic
       architecture definitions. */
#   if defined(_WIN64) || defined(__x86_64__)
#       ifndef __WIN64__
#           define __WIN64__
#       endif /* !__WIN64__ */
#   endif /* _WIN64 */

#endif

#define MSCU_OS_LINUX 0

#if ( \
    defined(linux) || defined(__linux) || defined(__linux__) \
    )
#   undef MSCU_OS_LINUX
#   define MSCU_OS_LINUX 1
#endif

#define MSCU_COMP_GNUC 0

#if defined(__GNUC__)
#   undef MSCU_COMP_GNUC
#   define MSCU_COMP_GNUC 1
#endif

#define MSCU_COMP_MSVC 0

#if defined(_MSC_VER)
#   undef MSCU_COMP_MSVC
#   define MSCU_COMP_MSVC 1
#endif

/// \cond
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/timeb.h>
#ifdef __cplusplus
#include <string>
#endif
/// \endcond

#if MSCU_OS_LINUX
/// \cond
#define MSCU_CALL_PREFIX
/// \endcond
#else
/// \cond
#define MSCU_CALL_PREFIX __stdcall
/// \endcond
#endif

#ifdef __cplusplus
#define EXTERNC         extern "C"
#else
#define EXTERNC
#endif

// Generic helper definitions for shared library support
#if defined _WIN32 || defined __CYGWIN__
  #define MSCU_HELPER_DLL_IMPORT __declspec(dllimport)
  #define MSCU_HELPER_DLL_EXPORT __declspec(dllexport)
  #define MSCU_HELPER_DLL_LOCAL
#else
  #if __GNUC__ >= 4
    #define MSCU_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
    #define MSCU_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
    #define MSCU_HELPER_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define MSCU_HELPER_DLL_IMPORT
    #define MSCU_HELPER_DLL_EXPORT
    #define MSCU_HELPER_DLL_LOCAL
  #endif
#endif

#define LOCAL_API MSCU_HELPER_DLL_LOCAL // shorter name for this function

#if MSCU_COMP_GNUC
#define STRUCT_PACKED_ATTRIBUTE __attribute__((packed))
#define STRUCT_PACKED_BEGIN
#define STRUCT_PACKED_END
#elif MSCU_COMP_MSVC
#define STRUCT_PACKED_ATTRIBUTE
#define STRUCT_PACKED_BEGIN __pragma(pack(push,1))
#define STRUCT_PACKED_END __pragma(pack(pop))
#else
#define STRUCT_PACKED_ATTRIBUTE
#define STRUCT_PACKED_BEGIN
#define STRUCT_PACKED_END
#endif

/// \defgroup mscu_types Стандартные типы и константы
/// @{
///

/// \defgroup mscu_base_types Базовые типы
/// @{
///

/// \name Целые числа
/// @{

typedef signed char     gint8;      ///< 8-битовое целое, со знаком
typedef gint8 *         gint8_p;    ///< указатель на \ref gint8

typedef unsigned char   guint8;     ///< 8-битовое целое, без знака
typedef guint8 *        guint8_p;   ///< указатель на \ref guint8

typedef signed short    gint16;     ///< 16-битовое целое, со знаком
typedef gint16 *        gint16_p;   ///< указатель на \ref gint16

typedef unsigned short  guint16;    ///< 16-битовое целое, без знака
typedef guint16 *       guint16_p;  ///< указатель на \ref guint16

#if defined(_MSC_VER)

typedef signed long     gint32;     ///< 32-битовое целое, со знаком
typedef unsigned long   guint32;    ///< 32-битовое целое, без знака
typedef signed __int64    gint64;   ///< 64-битовое целое, со знаком
typedef unsigned __int64  guint64;  ///< 64-битовое целое, без знака

#else

#ifndef G_MAXINT32
typedef int32_t   gint32;     ///< 32-битовое целое, со знаком
#endif

#ifndef G_MAXUINT32
typedef uint32_t  guint32;    ///< 32-битовое целое, без знака
#endif

#ifndef G_MAXINT64
typedef int64_t		gint64;
#endif

#ifndef G_MAXUINT64
typedef uint64_t 	guint64;
#endif

#endif /* _MSC_VER */

typedef gint32 *        gint32_p;   ///< указатель на \ref gint32
typedef guint32 *       guint32_p;  ///< указатель на \ref guint32
typedef gint64 *          gint64_p; ///< указатель на \ref gint64
typedef guint64 *         guint64_p;///< указатель на \ref guint64

typedef char            gchar;    ///< символ, знак не определен
typedef unsigned char   guchar;   ///< символ, без знака

typedef unsigned char   gbyte;    ///< 8-битовое целое (байт), без знака
typedef unsigned char * gbyte_p;  ///< указатель на \ref gbyte

typedef short           gshort;   ///< короткое целое, со знаком

typedef unsigned short  gword;    ///< короткое целое (слово), без знака
typedef unsigned short  gushort;  ///< короткое целое, без знака

typedef long            glong;    ///< длинное целое, со знаком
typedef unsigned long   gulong;   ///< длинное целое, без знака

typedef int             gint;     ///< целое, со знаком
typedef gint *          gint_p;   ///< указатель на \ref gint

typedef size_t          gsize_t;  ///< размер

typedef unsigned int    guint;    ///< целое, без знака
typedef unsigned int *  guint_p;  ///< указатель на \ref guint

/// @}

/// \name Булевые значения
/// \{

typedef gint            gboolean;   ///< булевое значение
typedef gboolean *      gboolean_p; ///< указатель на \ref gboolean

/// \}

/// \name Указатели и строки
/// @{

typedef void *        gpointer;       ///< указатель
typedef const void *  gconstpointer;  ///< константный указатель

typedef void * *       gpointer_p;       ///< указатель на указатель
typedef const void * * gconstpointer_p;  ///< константный указатель на указатель

typedef gchar *       gpchar;       ///< указатель на символ (строковый указатель)
typedef const gchar * gconstpchar;  ///< указатель на константный символ (строковый указатель)
typedef gchar * *     gpchar_p;     ///< указатель на указатель на символ (указатель на массив строк)

/// @}

/// \name Числа с плавающей точкой
/// \{

typedef float   gfloat;     ///< число с плавающей точкой, одинарная точность
typedef double  gdouble;    ///< число с плавающей точкой, двойная точность
typedef double * gdouble_p; ///< указатель на \ref gdouble

/// \}

/// \name Время
/// \{

/// \struct Ttimeval
/// время в Unix-формате: количество секунд и микросекунд с 00:00:00, Jan 1 1970 (UTC)
STRUCT_PACKED_BEGIN
struct STRUCT_PACKED_ATTRIBUTE Ttimeval_ {
  guint32 tv_sec;   ///< количество секунд
  guint32 tv_usec;  ///< количество микросекунд
};
STRUCT_PACKED_END
typedef struct Ttimeval_ Ttimeval;
/// указатель на структуру Ttimeval
typedef Ttimeval* Ptimeval;

/// \struct Ttimespec
/// время в Unix-формате: количество секунд и наносекунд с 00:00:00, Jan 1 1970 (UTC)
STRUCT_PACKED_BEGIN
struct STRUCT_PACKED_ATTRIBUTE Ttimespec_ {
  guint32 tv_sec;   ///< количество секунд
  guint32 tv_nsec;  ///< количество наносекунд
};
STRUCT_PACKED_END
typedef struct Ttimespec_ Ttimespec;
/// указатель на структуру Ttimeval
typedef Ttimespec* Ptimespec;

/// \}

/// \name Дополнительные типы
/// @{

/// \struct value_string
/// Пара значение-описание
/// Используется в создании списков выбора и т.д.
STRUCT_PACKED_BEGIN
struct STRUCT_PACKED_ATTRIBUTE value_string_ {
  gint   v; ///< значение
  gconstpchar s; ///< описание значения (строка с завершающим нулем), для массива: нулевое значение определяет конец массива
};
STRUCT_PACKED_END
/// структура value_string
typedef struct value_string_ value_string;
typedef struct value_string_ TValueString;
/// указатель на структуру value_string
typedef TValueString* PValueString;

/// \struct true_false_string
/// Описание значений истина/ложь
/// Используется в визуализации.
STRUCT_PACKED_BEGIN
struct STRUCT_PACKED_ATTRIBUTE true_false_string_ {
  gconstpchar true_string;   ///< строка, описывающая истинное состояние
  gconstpchar false_string;  ///< строка, описывающая ложное состояние
};
STRUCT_PACKED_END
/// структура true_false_string
typedef struct true_false_string_ true_false_string;
typedef struct true_false_string_ TTrueFalseString;
/// указатель на структуру true_false_string
typedef TTrueFalseString* PTrueFalseString;

/// @}

/// @}

#ifndef _WIN32
typedef gpointer HANDLE;
typedef gpointer HMODULE;
#endif

/// \defgroup mscu_messaging Сообщения
/// @{

/// \name Типы сообщений

/// \ingroup mscu_message_types
#define MT_INFORMATION    0 ///< информация (цвет текста - серый)
/// \ingroup mscu_message_types
#define MT_ERROR          1 ///< ошибка (цвет текста - светло-красный)
/// \ingroup mscu_message_types
#define MT_WARNING        2 ///< предупреждение (цвет текста - темно-красный)
/// \ingroup mscu_message_types
#define MT_PROCESS        3 ///< запущен определенный процесс обработки (цвет текста - синий)
/// \ingroup mscu_message_types
#define MT_RESULT         4 ///< завершен определенный процесс обработки (цвет текста - желтый)
/// \ingroup mscu_message_types
#define MT_PROGRESS_BEGIN 5 ///< старт индикатора прогресса (цвет текста - зеленый)
/// \ingroup mscu_message_types
#define MT_PROGRESS       6 ///< обновление индикатора прогресса (цвет текста - зеленый)
/// \ingroup mscu_message_types
#define MT_PROGRESS_END   7 ///< завершение индикатора прогресса (цвет текста - зеленый)
/// \ingroup mscu_message_types
#define MT_DEBUG					8 ///< отладка (цвет текста - серый)

/// \name Типы функций
/// @{

/// Функция регистрации сообщения
/// \param Message Сообщение в строковом виде (строка с завершающим нулем)
/// \param MessageType Тип сообщения, см. выше
typedef void (MSCU_CALL_PREFIX *Tklog_std_event)(const char* Message, gint MessageType);

///< тип функции, вызываемой в начале прогресса
typedef void (MSCU_CALL_PREFIX *Tprogress_begin_event)(gpointer user_data, gconstpchar Target, gint64 TargetSize);
///< тип функции, вызываемой в процессе прогресса
typedef void (MSCU_CALL_PREFIX *Tprogress_update_event)(gpointer user_data, gint64 TargetPosition);
///< тип функции, вызываемой в конце прогресса
typedef void (MSCU_CALL_PREFIX *Tprogress_end_event)(gpointer user_data);
///< тип функции, вызываемой в процессе прогресса чтобы определить, не нужно ли его прервать
typedef gboolean (MSCU_CALL_PREFIX *Tprogress_cancelled_event)(gpointer user_data);

/// \struct TProgressEventClass
/// Структура, содержащая функции класса "progress"
STRUCT_PACKED_BEGIN
struct STRUCT_PACKED_ATTRIBUTE TProgressEventClass_ {
  gpointer  user_data; ///< указатель на пользовательские данные - первый параметр для нижеописанных функций
  Tprogress_begin_event     progress_begin_event;     ///< функция вызываемая в начале прогресса
  Tprogress_update_event    progress_update_event;    ///< функция вызываемая в процессе прогресса
  Tprogress_end_event       progress_end_event;       ///< функция вызываемая в конце прогресса
  Tprogress_cancelled_event progress_cancelled_event; ///< функция вызываемая в процессе прогресса чтобы определить, не нужно ли его прервать
};
STRUCT_PACKED_END
typedef struct TProgressEventClass_ TProgressEventClass;
/// указатель на структуру TProgressEventClass
typedef TProgressEventClass* PProgressEventClass;

/// Функция регистрации сообщения (нетипизированная) - C
/// \param msg Сообщение в строковом виде (строка с завершающим нулем)
typedef void (MSCU_CALL_PREFIX *Tsnapshot_std_function)(gconstpchar msg);

/// Функция регистрации сообщения (нетипизированная) - C
/// \param msg Сообщение в строковом виде (строка с завершающим нулем)
typedef void (MSCU_CALL_PREFIX *Tsnapshot_std_function_variadic)(gconstpchar msg, ...);

/// @}

/// @}

/// \cond
#ifdef __cplusplus
/// \endcond

// this macro is used to get string (c_str) from exception, like: ... catch (std::exception& e) ...
#define MSCU_GET_E_WHAT	(e.what() && strlen(e.what()) ? e.what() : "<empty>")

/// \cond
#endif // __cplusplus
/// \endcond

/// @}

#endif

