/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/// \file mscu_types.h
/// \page mscu_types ����������� ����
/// @{
/// \section attention ��������������
/// \b ��������! ���� <b>"mscu_types.h"</b> ���������������� ��� ��������� ������ ������������ ������� �����.
/// ����� ��������� � ������ ����� ���������� �������������� �����������.
/// ��� ������������� ������� ����� ������ �������� ��� � ������ � ������� ��������� #include.
///
/// \section changelog ���������
/// [+] 2016-06-09 - ���������: STRUCT_PACKED_ATTRIBUTE, STRUCT_PACKED_BEGIN, STRUCT_PACKED_END
/// [+] 2015-11-15 - ���������: ��� ��������� - MT_DEBUG
/// [*] 2015-01-13 - �������� ��� - Ttimespec
/// [*] 2011-05-19 - ���������� ������������
/// [*] 2009-04-17 - ����������
///
/// \section description ��������
/// ������ �������� �������� �������� ������� �����, ������������ � ��������� ����������� �����������.
///
/// \section copyright ��������� �����
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

/// \defgroup mscu_types ����������� ���� � ���������
/// @{
///

/// \defgroup mscu_base_types ������� ����
/// @{
///

/// \name ����� �����
/// @{

typedef signed char     gint8;      ///< 8-������� �����, �� ������
typedef gint8 *         gint8_p;    ///< ��������� �� \ref gint8

typedef unsigned char   guint8;     ///< 8-������� �����, ��� �����
typedef guint8 *        guint8_p;   ///< ��������� �� \ref guint8

typedef signed short    gint16;     ///< 16-������� �����, �� ������
typedef gint16 *        gint16_p;   ///< ��������� �� \ref gint16

typedef unsigned short  guint16;    ///< 16-������� �����, ��� �����
typedef guint16 *       guint16_p;  ///< ��������� �� \ref guint16

#if defined(_MSC_VER)

typedef signed long     gint32;     ///< 32-������� �����, �� ������
typedef unsigned long   guint32;    ///< 32-������� �����, ��� �����
typedef signed __int64    gint64;   ///< 64-������� �����, �� ������
typedef unsigned __int64  guint64;  ///< 64-������� �����, ��� �����

#else

#ifndef G_MAXINT32
typedef int32_t   gint32;     ///< 32-������� �����, �� ������
#endif

#ifndef G_MAXUINT32
typedef uint32_t  guint32;    ///< 32-������� �����, ��� �����
#endif

#ifndef G_MAXINT64
typedef int64_t		gint64;
#endif

#ifndef G_MAXUINT64
typedef uint64_t 	guint64;
#endif

#endif /* _MSC_VER */

typedef gint32 *        gint32_p;   ///< ��������� �� \ref gint32
typedef guint32 *       guint32_p;  ///< ��������� �� \ref guint32
typedef gint64 *          gint64_p; ///< ��������� �� \ref gint64
typedef guint64 *         guint64_p;///< ��������� �� \ref guint64

typedef char            gchar;    ///< ������, ���� �� ���������
typedef unsigned char   guchar;   ///< ������, ��� �����

typedef unsigned char   gbyte;    ///< 8-������� ����� (����), ��� �����
typedef unsigned char * gbyte_p;  ///< ��������� �� \ref gbyte

typedef short           gshort;   ///< �������� �����, �� ������

typedef unsigned short  gword;    ///< �������� ����� (�����), ��� �����
typedef unsigned short  gushort;  ///< �������� �����, ��� �����

typedef long            glong;    ///< ������� �����, �� ������
typedef unsigned long   gulong;   ///< ������� �����, ��� �����

typedef int             gint;     ///< �����, �� ������
typedef gint *          gint_p;   ///< ��������� �� \ref gint

typedef size_t          gsize_t;  ///< ������

typedef unsigned int    guint;    ///< �����, ��� �����
typedef unsigned int *  guint_p;  ///< ��������� �� \ref guint

/// @}

/// \name ������� ��������
/// \{

typedef gint            gboolean;   ///< ������� ��������
typedef gboolean *      gboolean_p; ///< ��������� �� \ref gboolean

/// \}

/// \name ��������� � ������
/// @{

typedef void *        gpointer;       ///< ���������
typedef const void *  gconstpointer;  ///< ����������� ���������

typedef void * *       gpointer_p;       ///< ��������� �� ���������
typedef const void * * gconstpointer_p;  ///< ����������� ��������� �� ���������

typedef gchar *       gpchar;       ///< ��������� �� ������ (��������� ���������)
typedef const gchar * gconstpchar;  ///< ��������� �� ����������� ������ (��������� ���������)
typedef gchar * *     gpchar_p;     ///< ��������� �� ��������� �� ������ (��������� �� ������ �����)

/// @}

/// \name ����� � ��������� ������
/// \{

typedef float   gfloat;     ///< ����� � ��������� ������, ��������� ��������
typedef double  gdouble;    ///< ����� � ��������� ������, ������� ��������
typedef double * gdouble_p; ///< ��������� �� \ref gdouble

/// \}

/// \name �����
/// \{

/// \struct Ttimeval
/// ����� � Unix-�������: ���������� ������ � ����������� � 00:00:00, Jan 1 1970 (UTC)
STRUCT_PACKED_BEGIN
struct STRUCT_PACKED_ATTRIBUTE Ttimeval_ {
  guint32 tv_sec;   ///< ���������� ������
  guint32 tv_usec;  ///< ���������� �����������
};
STRUCT_PACKED_END
typedef struct Ttimeval_ Ttimeval;
/// ��������� �� ��������� Ttimeval
typedef Ttimeval* Ptimeval;

/// \struct Ttimespec
/// ����� � Unix-�������: ���������� ������ � ���������� � 00:00:00, Jan 1 1970 (UTC)
STRUCT_PACKED_BEGIN
struct STRUCT_PACKED_ATTRIBUTE Ttimespec_ {
  guint32 tv_sec;   ///< ���������� ������
  guint32 tv_nsec;  ///< ���������� ����������
};
STRUCT_PACKED_END
typedef struct Ttimespec_ Ttimespec;
/// ��������� �� ��������� Ttimeval
typedef Ttimespec* Ptimespec;

/// \}

/// \name �������������� ����
/// @{

/// \struct value_string
/// ���� ��������-��������
/// ������������ � �������� ������� ������ � �.�.
STRUCT_PACKED_BEGIN
struct STRUCT_PACKED_ATTRIBUTE value_string_ {
  gint   v; ///< ��������
  gconstpchar s; ///< �������� �������� (������ � ����������� �����), ��� �������: ������� �������� ���������� ����� �������
};
STRUCT_PACKED_END
/// ��������� value_string
typedef struct value_string_ value_string;
typedef struct value_string_ TValueString;
/// ��������� �� ��������� value_string
typedef TValueString* PValueString;

/// \struct true_false_string
/// �������� �������� ������/����
/// ������������ � ������������.
STRUCT_PACKED_BEGIN
struct STRUCT_PACKED_ATTRIBUTE true_false_string_ {
  gconstpchar true_string;   ///< ������, ����������� �������� ���������
  gconstpchar false_string;  ///< ������, ����������� ������ ���������
};
STRUCT_PACKED_END
/// ��������� true_false_string
typedef struct true_false_string_ true_false_string;
typedef struct true_false_string_ TTrueFalseString;
/// ��������� �� ��������� true_false_string
typedef TTrueFalseString* PTrueFalseString;

/// @}

/// @}

#ifndef _WIN32
typedef gpointer HANDLE;
typedef gpointer HMODULE;
#endif

/// \defgroup mscu_messaging ���������
/// @{

/// \name ���� ���������

/// \ingroup mscu_message_types
#define MT_INFORMATION    0 ///< ���������� (���� ������ - �����)
/// \ingroup mscu_message_types
#define MT_ERROR          1 ///< ������ (���� ������ - ������-�������)
/// \ingroup mscu_message_types
#define MT_WARNING        2 ///< �������������� (���� ������ - �����-�������)
/// \ingroup mscu_message_types
#define MT_PROCESS        3 ///< ������� ������������ ������� ��������� (���� ������ - �����)
/// \ingroup mscu_message_types
#define MT_RESULT         4 ///< �������� ������������ ������� ��������� (���� ������ - ������)
/// \ingroup mscu_message_types
#define MT_PROGRESS_BEGIN 5 ///< ����� ���������� ��������� (���� ������ - �������)
/// \ingroup mscu_message_types
#define MT_PROGRESS       6 ///< ���������� ���������� ��������� (���� ������ - �������)
/// \ingroup mscu_message_types
#define MT_PROGRESS_END   7 ///< ���������� ���������� ��������� (���� ������ - �������)
/// \ingroup mscu_message_types
#define MT_DEBUG					8 ///< ������� (���� ������ - �����)

/// \name ���� �������
/// @{

/// ������� ����������� ���������
/// \param Message ��������� � ��������� ���� (������ � ����������� �����)
/// \param MessageType ��� ���������, ��. ����
typedef void (MSCU_CALL_PREFIX *Tklog_std_event)(const char* Message, gint MessageType);

///< ��� �������, ���������� � ������ ���������
typedef void (MSCU_CALL_PREFIX *Tprogress_begin_event)(gpointer user_data, gconstpchar Target, gint64 TargetSize);
///< ��� �������, ���������� � �������� ���������
typedef void (MSCU_CALL_PREFIX *Tprogress_update_event)(gpointer user_data, gint64 TargetPosition);
///< ��� �������, ���������� � ����� ���������
typedef void (MSCU_CALL_PREFIX *Tprogress_end_event)(gpointer user_data);
///< ��� �������, ���������� � �������� ��������� ����� ����������, �� ����� �� ��� ��������
typedef gboolean (MSCU_CALL_PREFIX *Tprogress_cancelled_event)(gpointer user_data);

/// \struct TProgressEventClass
/// ���������, ���������� ������� ������ "progress"
STRUCT_PACKED_BEGIN
struct STRUCT_PACKED_ATTRIBUTE TProgressEventClass_ {
  gpointer  user_data; ///< ��������� �� ���������������� ������ - ������ �������� ��� ������������� �������
  Tprogress_begin_event     progress_begin_event;     ///< ������� ���������� � ������ ���������
  Tprogress_update_event    progress_update_event;    ///< ������� ���������� � �������� ���������
  Tprogress_end_event       progress_end_event;       ///< ������� ���������� � ����� ���������
  Tprogress_cancelled_event progress_cancelled_event; ///< ������� ���������� � �������� ��������� ����� ����������, �� ����� �� ��� ��������
};
STRUCT_PACKED_END
typedef struct TProgressEventClass_ TProgressEventClass;
/// ��������� �� ��������� TProgressEventClass
typedef TProgressEventClass* PProgressEventClass;

/// ������� ����������� ��������� (����������������) - C
/// \param msg ��������� � ��������� ���� (������ � ����������� �����)
typedef void (MSCU_CALL_PREFIX *Tsnapshot_std_function)(gconstpchar msg);

/// ������� ����������� ��������� (����������������) - C
/// \param msg ��������� � ��������� ���� (������ � ����������� �����)
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

