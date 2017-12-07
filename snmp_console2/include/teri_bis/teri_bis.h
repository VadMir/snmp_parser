/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/*
 * ВНИМАНИЕ! Данный файл распространяется под авторским правом РАЗРАБОТЧИКА данного файла.
 * Любые изменения в данном файле СТОРОННИМИ разработчиками НЕДОПУСТИМЫ.
 * Для использования данного файла просто включите его в проект с помощью директивы uses.
 */
/* teri_bis.h
 * интерфейс библиотеки teri_bis.dll
 */
/* teri_bis - Data Retrieval Engine, bis
 * Copyright (C) 2002-2017 MSC, ORG
 */
// изменения
// ---------
// [+] 2017-07-28 - Добавлено: режимы TERI_MODE_WARN_NO_PRIO, TERI_MODE_WARN_NO_PATH (см. документацию);
// [+] 2017-06-14 - Добавлено: функция teri_bis_wrapper_tls_engine (см. документацию);
// [+] 2017-05-23 - Добавлено: режим TERI_MODE_NO_VERIFICATION (см. документацию);
// [+] 2017-05-21 - Добавлено: режим TERI_MODE_IGNORE_NO_ID (см. документацию);
// [+] 2017-05-11 - Добавлено: флаги TERI_UNI_EXT_XXX (см. документацию);
// [+] 2017-05-03 - Добавлено: режим TERI_MODE_NO_SHIFT (см. документацию);
// [*] 2017-02-25 - Изменено: политика использования функций блокировки (теперь только при многопоточном поиске) (см. документацию на функции teri_bis_wrapper_engine, teri_bis_wrapper_engine_enter, teri_bis_wrapper_engine_leave);
// [+] 2016-03-29 - Добавлено: области поиска - TERI_BIS_SPOT_NASp, TERI_BIS_SPOT_BSid;
// [+] 2016-03-14 - Добавлено: поле entry_spot в структуру Tteri_bis_match_token;
// [+] 2016-03-02 - Добавлено: области поиска - TERI_BIS_SPOT_URLad, TERI_BIS_SPOT_DNad, TERI_BIS_SPOT_ORIG, TERI_BIS_SPOT_REF, TERI_BIS_SPOT_fGET, TERI_BIS_SPOT_fPOST
// [+] 2014-04-14 Добавлена область поиска - TERI_BIS_SPOT_DNad
// [+] 2014-04-14 Добавлена область поиска - TERI_BIS_SPOT_URLad
// [+] 2015-07-22 - Добавлено: функция teri_bis_wrapper_reload_if_modified_raw (см. документацию);
// [+] 2014-12-30 - Добавлено: функция teri_bis_generate_wts (см. документацию);
// [+] 2014-12-30 - Добавлено: функция teri_bis_wrapper_set_transparent_spots (см. документацию);
// [+] 2014-04-14 Добавлена область поиска - TERI_BIS_SPOT_DN
// [+] 2013-12-15 Добавлено: функция teri_bis_match_medium_atomic_first_only
// [+] 2013-11-01 Добавлено: функция teri_bis_match_medium_atomic_all_bufs
// [+] 2013-10-21 Добавлена область поиска - TERI_BIS_SPOT_PhB
// [+] 2012-11-28 - обновлено: описание функции teri_bis_check_syntax;
// [+] 2012-11-08 - Добавлено: область поиска - TERI_BIS_SPOT_ISN (см. документацию);
// [+] 2011-11-18 - Добавлено: коды ошибок TERI_BIS_ERROR_BAD_TOKEN1_SPOT, TERI_BIS_ERROR_BAD_TOKEN2_SPOT  (см. документацию);
// [+] 2011-10-30 - Добавлено: режим TERI_MODE_IGNORE_ID_DUPLICATION (см. документацию);
// [+] 2011-10-12 - Добавлено: режим TERI_MODE_IGNORE_BAD_TOKENS (см. документацию)
// [+] 2011-03-09 Добавлено: квантификаторы
// [+] 2011-02-22 Добавлена область поиска - TERI_BIS_SPOT_bMPLS
// [+] 2011-02-22 Добавлены поля id_ext – расширение идентификатора призака (см. Документацию) – !несовместимость DTF-формата! !несовместимость по функциям поиска - изменение Tteri_bis_match_token!
// [+] 2011-02-20 Добавлено: функция teri_bis_wrapper_set_log_parameters
// [+] 2010-08-25 Добавлены поля sub_token_mask - маска подпризнаков (см. Документацию) – !несовместимость DTF-формата!
// [+] 2010-08-25 Добавлено: подпризнак с отрицанием (см. документацию)
// [+] 2010-08-24 Изменено: функция teri_bis_match_medium_atomic_all - добавлена работа с подпризнаками
// [+] 2010-06-04 Добавлен метасимвол – \[^...] — диапазон с отрицанием (см. документацию)
// [+] 2010-06-04 Добавлен метасимвол – \D (см. документацию)
// [+] 2010-06-04 Добавлен метасимвол – \S (см. документацию)
// [+] 2010-06-04 Добавлен метасимвол – \W (см. документацию)
// [+] 2009-09-10 Добавлена область поиска - TERI_BIS_SPOT_bVLAN
// [+] 2009-09-10 Добавлена область поиска - TERI_BIS_SPOT_bDPid
// [+] 2009-05-14 Добавлена область поиска - TERI_BIS_SPOT_mA
// [+] 2009-04-27 Добавлено: функция teri_bis_match_medium_atomic_all
// [+] 2009-03-26 Добавлено: режим TERI_MODE_SCRAMBLED (см. документацию)
// [+] 2009-02-03 Добавлена область поиска - TERI_BIS_SPOT_MED
// [+] 2009-01-19 Удалена область поиска - TERI_BIS_SPOT_mT
// [+] 2009-01-19 Удалена область поиска - TERI_BIS_SPOT_mF
// [+] 2009-01-14 Добавлена область поиска - TERI_BIS_SPOT_URL
// [+] 2009-01-14 Добавлена область поиска - TERI_BIS_SPOT_ICQ
// [+] 2009-01-14 Добавлена область поиска - TERI_BIS_SPOT_LGN
// [+] 2009-01-14 Добавлена область поиска - TERI_BIS_SPOT_bI6D
// [+] 2009-01-14 Добавлена область поиска - TERI_BIS_SPOT_bI6S
// [+] 2009-01-14 Добавлена область поиска - TERI_BIS_SPOT_bMa
// [+] 2009-01-14 Добавлена область поиска - TERI_BIS_SPOT_PhE
// [+] 2008-12-21 Добавлена область поиска - TERI_BIS_SPOT_PhI
// [+] 2008-12-21 Добавлена область поиска - TERI_BIS_SPOT_PhN
// [+] 2008-12-21 Добавлена область поиска - TERI_BIS_SPOT_Pr
// [*] 2008-12-18 - изменен DTF-формат (см. dtf_bis.pdf)
//

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#if !defined(TERI_BIS)
#define TERI_BIS

#include <mscu_types.h>

// Now we use the generic helper definitions above to define XXX_API and XXX_LOCAL.
// XXX_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
// XXX_LOCAL is used for non-api symbols.
#ifdef TERI_BIS_EXPORTS // defined if we are building the XXX DLL (instead of using it)
  /// \cond
  #define TERI_BIS_API MSCU_HELPER_DLL_EXPORT
  /// \endcond
#else
  /// \cond
  #define TERI_BIS_API MSCU_HELPER_DLL_IMPORT
  #pragma comment( lib, "teri_bis" )
  /// \endcond
#endif // TERI_BIS_EXPORTS
#define TERI_BIS_LOCAL MSCU_HELPER_DLL_LOCAL

/* границы задания кодов */
#define TERI_START_BASE_ERROR       0 /* начальная нумерация для ошибки */
#define TERI_STOP_BASE_ERROR      -63 /* конечная нумерация для ошибки */
#define TERI_START_BASE_WARNING   -64 /* начальная нумерация для предупреждений */
#define TERI_STOP_BASE_WARNING   -127 /* конечная нумерация для предупреждений */

/* коды ошибок (коды возврата функций)
 * частные для teri
 * 0..-31     - ERROR
 * -64..-95   - WARNING
 */
#define  TERI_ERROR_SUCCESS                       0 /* удачное выполнение операции
                                                * (параметры не определены)
                                                */
#define  TERI_ERROR_UNKNOWN                      -1 /* неизвестная ошибка
                                                * (параметры не определены)
                                                */
#define  TERI_ERROR_ABORT                        -2 /* операция прервана (через Callback-функцию)
                                                * (параметры не определены)
                                                */
#define  TERI_ERROR_BAD_ARG                      -3 /* неверный аргумент функции
                                                * (параметры не определены)
                                                */
#define  TERI_ERROR_BAD_OP                       -4 /* неверная операция
                                                * (параметры не определены)
                                                */
#define  TERI_ERROR_TOKEN_CLASH                  -5 /* конфликт между признаками
                                                * wParam - номер первого признака
                                                * lParam - номер второго признака
                                                */

/* предупреждения */
#define  TERI_WARNING_TOKEN_CLASH               -64 /* конфликт между признаками
                                                * wParam - номер первого признака
                                                * lParam - номер второго признака
                                                */

/* коды ошибок (коды возврата функций)
 * частные для teri_bis
 * -32..-63   - ERROR
 * -96..-127  - WARNING
 */

/* неверная строка */

#define  TERI_BIS_ERROR_BAD_LINE                           -32 /* неверная строка во входном буфере
                                                           * wParam - номер строки (начиная с 1)
                                                           */

/* неверный синтаксис */

#define  TERI_BIS_ERROR_BAD_CONTAINER_SYNTAX               -33 /* неверный синтаксис имени контейнера
                                                           * wParam - номер контейнера
                                                           */
#define  TERI_BIS_ERROR_BAD_CONTAINER_ITEM_SYNTAX          -34 /* неверный синтаксис элемента контейнера
                                                           * wParam - номер элемента контейнера
                                                           * lParam - позиция ошибочного символа (начиная с 0)
                                                           */
#define  TERI_BIS_ERROR_BAD_TOKEN1_SYNTAX                  -35 /* неверный синтаксис признака уровня 1
                                                           * wParam - номер признака уровня 1
                                                           * lParam - номер подпризнака внутри признака (начиная с 0)
                                                           */
#define  TERI_BIS_ERROR_BAD_TOKEN2_SYNTAX                  -36 /* неверный синтаксис признака уровня 2
                                                           * wParam - номер признака уровня 2
                                                           * lParam - номер подпризнака внутри признака (начиная с 0)
                                                           */
#define  TERI_BIS_ERROR_BAD_TOKEN1_SYNTAX_CONTAINER_MISS   -37 /* неверный синтаксис признака уровня 1 - не найден контенер с данным именем
                                                           * wParam - номер признака уровня 1
                                                           */
#define  TERI_BIS_ERROR_BAD_TOKEN2_SYNTAX_CONTAINER_MISS   -38 /* неверный синтаксис признака уровня 2 - не найден контенер с данным именем
                                                           * wParam - номер признака уровня 2
                                                           */

/* пустая группа */

#define  TERI_BIS_ERROR_EMPTY_CONTAINER                    -39 /* пустой контейнер;
                                                           * wParam - номер контейнера
                                                           */
#define  TERI_BIS_ERROR_EMPTY_GROUP1                       -40 /* пустая группа уровня 1
                                                           * wParam - номер группы уровня 1
                                                           */
#define  TERI_BIS_ERROR_EMPTY_GROUP2                       -41 /* пустая группа уровня 2
                                                           * wParam - номер группы уровня 2
                                                           */

/* повторение индексов */

#define  TERI_BIS_ERROR_CONTAINER_INDEX_REPEAT             -42 /* повторение индекса - контейнер
                                                           * wParam - номер контейнера
                                                           */
#define  TERI_BIS_ERROR_CONTAINER_ITEM_INDEX_REPEAT        -43 /* повторение индекса - элемент контейнера
                                                           * wParam - номер элемента контейнера
                                                           */
#define  TERI_BIS_ERROR_GROUP1_INDEX_REPEAT                -44 /* повторение индекса - группа уровня 1
                                                           * wParam - номер группы уровня 1
                                                           */
#define  TERI_BIS_ERROR_GROUP2_INDEX_REPEAT                -45 /* повторение индекса - группа уровня 2
                                                           * wParam - номер группы уровня 2
                                                           */
#define  TERI_BIS_ERROR_TOKEN1_INDEX_REPEAT                -46 /* повторение индекса - признак уровня 1
                                                           * wParam - номер признака уровня 1
                                                           */
#define  TERI_BIS_ERROR_TOKEN2_INDEX_REPEAT                -47 /* повторение индекса - признак уровня 2
                                                           * wParam - номер признака уровня 2
                                                           */

/* неверное значение приоритета */

#define  TERI_BIS_ERROR_BAD_GROUP1_PRIORITY                -48 /* неверное значение приоритета - группа уровня 1
                                                           * wParam - номер группы уровня 1
                                                           */
#define  TERI_BIS_ERROR_BAD_GROUP2_PRIORITY                -49 /* неверное значение приоритета - группа уровня 2
                                                           * wParam - номер группы уровня 2
                                                           */
#define  TERI_BIS_ERROR_BAD_TOKEN1_PRIORITY                -50 /* неверное значение приоритета - признак уровня 1
                                                           * wParam - номер признака уровня 1
                                                           */
#define  TERI_BIS_ERROR_BAD_TOKEN2_PRIORITY                -51 /* неверное значение приоритета - признак уровня 2
                                                           * wParam - номер признака уровня 2
                                                           */

/* неверное количество подпризнаков */

#define  TERI_BIS_ERROR_BAD_TOKEN1_SUBTOKEN_COUNT          -52 /* неверное количество подпризнаков - признак уровня 1
                                                           * wParam - номер признака уровня 1
                                                           */
#define  TERI_BIS_ERROR_BAD_TOKEN2_SUBTOKEN_COUNT          -53 /* неверное количество подпризнаков - признак уровня 2
                                                           * wParam - номер признака уровня 2
                                                           */

/* совпадение */

#define  TERI_BIS_ERROR_CONTAINER_CLASH                    -54 /* совпадение имен контейнеров;
                                                           * wParam - номер контейнера
                                                           */
#define  TERI_BIS_ERROR_CONTAINER_ITEM_CLASH               -55 /* совпадение элементов контейнера;
                                                           * wParam - номер первого элемента контейнера
                                                           * lParam - номер второго элемента контейнера
                                                           */
#define  TERI_BIS_ERROR_TOKEN1_INTERNAL_CLASH              -56 /* конфликт между подпризнаками признака уровня 1
                                                           * wParam - номер признака уровня 1
                                                           * lParam - номер подозрительного подпризнака внутри признака (начиная с 0)
                                                           */
#define  TERI_BIS_ERROR_TOKEN2_INTERNAL_CLASH              -57 /* конфликт между подпризнаками признака уровня 2
                                                           * wParam - номер признака уровня 2
                                                           * lParam - номер подозрительного подпризнака внутри признака (начиная с 0)
                                                           */

#define  TERI_BIS_ERROR_TOKEN1_CLASH                       -58 /* конфликт между признаками признака уровня 1
                                                           * wParam - номер превого признака уровня 1
                                                           * lParam - номер второго признака уровня 1
                                                           */
#define  TERI_BIS_ERROR_TOKEN2_CLASH                       -59 /* конфликт между признаками признака уровня 2
                                                           * wParam - номер превого признака уровня 2
                                                           * lParam - номер второго признака уровня 2
                                                           */

/* неверная ссылка */

#define  TERI_BIS_ERROR_BAD_GROUP1_REF                     -60 /* неверные ссылки в группе уровня 1 на группу уровня 2
                                                           * wParam - номер группы уровня 1
                                                           * lParam - неверный номер группы уровня 2, на который ссылается wParam
                                                           */

/* неверное расположение */

#define  TERI_BIS_ERROR_BAD_TOKEN1_SPOT                    -61 /* неверный расположение признака уровня 1
                                                           * wParam - номер признака уровня 1
                                                           * lParam - номер подпризнака внутри признака (начиная с 0)
                                                           */
#define  TERI_BIS_ERROR_BAD_TOKEN2_SPOT                    -62 /* неверный расположение признака уровня 2
                                                           * wParam - номер признака уровня 2
                                                           * lParam - номер подпризнака внутри признака (начиная с 0)
                                                           */

/* неверная длина */

#define  TERI_BIS_ERROR_BAD_TOKEN1_LENGTH                  -63 /* неверная длина признака уровня 1
                                                           * wParam - номер признака уровня 1
                                                           * lParam - номер подпризнака внутри признака (начиная с 0)
                                                           */
#define  TERI_BIS_ERROR_BAD_TOKEN2_LENGTH                  -64 /* неверная длина признака уровня 2
                                                           * wParam - номер признака уровня 2
                                                           * lParam - номер подпризнака внутри признака (начиная с 0)
                                                           */

/* предупреждения */

/* нет индекса */

#define  TERI_BIS_WARNING_CONTAINER_INDEX_MISS             -96 /* отсутствие индекса - контейнер
                                                           * wParam - номер строки
                                                           */
#define  TERI_BIS_WARNING_CONTAINER_ITEM_INDEX_MISS        -97 /* отсутствие индекса - элемент контейнера
                                                           * wParam - номер строки
                                                           */
#define  TERI_BIS_WARNING_GROUP1_INDEX_MISS                -98 /* отсутствие индекса - группа уровня 1
                                                           * wParam - номер строки
                                                           */
#define  TERI_BIS_WARNING_GROUP2_INDEX_MISS                -99 /* отсутствие индекса - группа уровня 2
                                                           * wParam - номер строки
                                                           */
#define  TERI_BIS_WARNING_TOKEN1_INDEX_MISS               -100 /* отсутствие индекса - признак уровня 1
                                                           * wParam - номер строки
                                                           */
#define  TERI_BIS_WARNING_TOKEN2_INDEX_MISS               -101 /* отсутствие индекса - признак уровня 2
                                                           * wParam - номер строки
                                                           */

/* нет приоритета */

#define  TERI_BIS_WARNING_GROUP1_PRIO_MISS                -102 /* отсутствие приоритета - группа уровня 1
                                                           * wParam - номер строки
                                                           */
#define  TERI_BIS_WARNING_GROUP2_PRIO_MISS                -103 /* отсутствие приоритета - группа уровня 2
                                                           * wParam - номер строки
                                                           */
#define  TERI_BIS_WARNING_TOKEN1_PRIO_MISS                -104 /* отсутствие приоритета - признак уровня 1
                                                           * wParam - номер строки
                                                           */
#define  TERI_BIS_WARNING_TOKEN2_PRIO_MISS                -105 /* отсутствие приоритета - признак уровня 2
                                                           * wParam - номер строки
                                                           */

/* нет пути */

#define  TERI_BIS_WARNING_GROUP1_PATH_MISS                -106 /* отсутствие пути - группа уровня 1
                                                           * wParam - номер строки
                                                           */
#define  TERI_BIS_WARNING_GROUP2_PATH_MISS                -107 /* отсутствие пути - группа уровня 2
                                                           * wParam - номер строки
                                                           */
#define  TERI_BIS_WARNING_TOKEN1_PATH_MISS                -108 /* отсутствие пути - признак уровня 1
                                                           * wParam - номер строки
                                                           */
#define  TERI_BIS_WARNING_TOKEN2_PATH_MISS                -109 /* отсутствие пути - признак уровня 2
                                                           * wParam - номер строки
                                                           */

/* совпадение */

#define  TERI_BIS_WARNING_TOKEN1_CLASH                    -110 /* конфликт между признаками признака уровня 1
                                                           * wParam - номер превого признака уровня 1
                                                           * lParam - номер второго признака уровня 1
                                                           */
#define  TERI_BIS_WARNING_TOKEN2_CLASH                    -111 /* конфликт между признаками признака уровня 2
                                                           * wParam - номер превого признака уровня 2
                                                           * lParam - номер второго признака уровня 2
                                                           */

/* пустая группа */

#define  TERI_BIS_WARNING_EMPTY_CONTAINER                    -112 /* пустой контейнер;
                                                           * wParam - номер контейнера
                                                           */
#define  TERI_BIS_WARNING_EMPTY_GROUP1                       -113 /* пустая группа уровня 1
                                                           * wParam - номер группы уровня 1
                                                           */
#define  TERI_BIS_WARNING_EMPTY_GROUP2                       -114 /* пустая группа уровня 2
                                                           * wParam - номер группы уровня 2
                                                           */

/* типы событий
 *
 * Progress (CP_) - информация о ходе выполнения операции
 */

/* общая загрузка признаков */
#define  CP_bis_generate_lod_begin        32 /* lParam - <общее_число_этапов> << 8 + <текущий_этап> */
#define  CP_bis_generate_lod_progress     33 /* wParam - процент выполнения, lParam - <общее_число_этапов> << 8 + <текущий_этап> */
#define  CP_bis_generate_lod_end          34 /* lParam - <общее_число_этапов> << 8 + <текущий_этап> */
/* Прогресс - частные */
/* проверка признаков */
#define  CP_generate_ver_begin        1  /* lParam - <общее_число_этапов> << 8 + <текущий_этап> */
#define  CP_generate_ver_progress     2  /* wParam - процент выполнения, lParam - <общее_число_этапов> << 8 + <текущий_этап> */
#define  CP_generate_ver_end          3  /* lParam - <общее_число_этапов> << 8 + <текущий_этап> */
/* генерация маршрута */
#define  CP_generate_gen_begin        4  /* lParam - <общее_число_этапов> << 8 + <текущий_этап> */
#define  CP_generate_gen_progress     5  /* wParam - процент выполнения, lParam - <общее_число_этапов> << 8 + <текущий_этап> */
#define  CP_generate_gen_end          6  /* lParam - <общее_число_этапов> << 8 + <текущий_этап> */
/* сжатие маршрута */
#define  CP_generate_cmp_begin        7  /* lParam - <общее_число_этапов> << 8 + <текущий_этап> */
#define  CP_generate_cmp_progress     8  /* wParam - процент выполнения, lParam - <общее_число_этапов> << 8 + <текущий_этап> */
#define  CP_generate_cmp_end          9  /* lParam - <общее_число_этапов> << 8 + <текущий_этап> */

/* тип Callback-функции, вызываемой при различных событиях и длительных операциях
*
* ud - параметр user_data, передаваемый при вызове функции teri_bis_generate (может иметь любое значение)
* Msg - тип события
* wParam - параметр события
* lParam - параметр события
* MsgStr - интерпретация события в строковом виде
*
* возвращаемое значение:
*   true  - операция может быть продолжена
*   false - операцию необходимо прервать
*/
typedef gboolean (MSCU_CALL_PREFIX * Tteri_generate_callback)(gpointer user_data, gint32 Msg, guint32 wParam, guint32 lParam, gpchar MsgStr);

/* опции */

// нечувствительность к регистру
//
#define TERI_MODE_CASE_INSENSITIVE			0x00000001
// "мягкий" синтаксис
//  при генерации:
//  разрешать вхождение признаков друг в друга
//
#define TERI_MODE_SOFT_SYNTAX						0x00000002
// при генерации:
//  не создавать "хвосты", т.е. признаки должны
//  целиком "ложиться" в маршрут
//
#define TERI_MODE_NO_TAILS							0x00000004
// при сохранении в внешний буфер:
//  необходимо произвести процедуру скремблирования данных
//
#define TERI_MODE_SCRAMBLED							0x00000008
// игнорировать неверные признаки
//  при генерации:
//  игнорировать ошибки в признаках и продолжать генерацию маршрута без ошибочных признаков (сообщения об ошибках будут выводится в любом случае)
//
#define TERI_MODE_IGNORE_BAD_TOKENS			0x00000010
// игнорировать дублирование идентификаторов
//  при генерации:
//  игнорировать дублирование числовых значений идентификаторов групп, признаков, контейнеров, элементов контейнеров и продолжать генерацию маршрута без вывода ошибок
//
#define TERI_MODE_IGNORE_ID_DUPLICATION	0x00000020
// при генерации (процедура уплотнения):
//  не "сдвигать" узлы при совмещении
//  при включенном флаге уменьшается время уплотнения, но увеличивается размер маршрута
//
#define TERI_MODE_NO_SHIFT							0x00000040
// игнорировать отсутствие идентификаторов
//  при генерации:
//  игнорировать отсутствие числовых значений идентификаторов групп, признаков, контейнеров, элементов контейнеров и подставлять значения по умолчанию
//
#define TERI_MODE_IGNORE_NO_ID					0x00000080

// не проводить проверку признаков
//  при генерации:
//  не проводить этап проверки признаков, что ускоряет процесс создания маршрута
//	допустимо применение при очень больших объемах признаков (порядка миллиона штук)
//  данный режим применим только при совместном одновременном использовании с режимами TERI_MODE_SOFT_SYNTAX и TERI_MODE_NO_TAILS
//
#define TERI_MODE_NO_VERIFICATION				0x00000100

// выводить предупрежение об отсутствии значения пути
//  при генерации:
//  выводить предупреждающее сообщение об отсутствии строкового значения пути групп, признаков, контейнеров, элементов контейнеров и подстановки значения по умолчанию
//
#define TERI_MODE_WARN_NO_PATH					0x00000200

// выводить предупрежение об отсутствии значения приоритета
//  при генерации:
//  выводить предупреждающее сообщение об отсутствии числового значения приоритета групп, признаков, контейнеров, элементов контейнеров и подстановки значения по умолчанию
//
#define TERI_MODE_WARN_NO_PRIO					0x00000400

/* максимальное и минимальное значение приоритета (раздела/внутри раздела) */
#define MIN_PRIORITY_VALUE  0
#define MAX_PRIORITY_VALUE  255

/* максимальное значение абсолютного приоритета */
#define MAX_ABSOLUTE_PRIORITY_VALUE   0xffff

/* максимальное количество подпризнаков в признаке */
#define MAX_SUBTOKEN_COUNT  8

//----------------------------------------------------------------------------------------------------------------------
/* объект поиска (spot) */
#define  TERI_BIS_SPOT_NONE   0x00 // не определено
#define  TERI_BIS_SPOT_bIS    0x01 // IP-source
#define  TERI_BIS_SPOT_bID    0x02 // IP-destination
#define  TERI_BIS_SPOT_bPS    0x03 // TCP/UDP port-source
#define  TERI_BIS_SPOT_bPD    0x04 // TCP/UDP port-destination
#define  TERI_BIS_SPOT_bPI    0x05 // Protocol idendifier
#define  TERI_BIS_SPOT_T      0x06 // Text
#define  TERI_BIS_SPOT_H      0x07 // Header
#define  TERI_BIS_SPOT_S      0x08 // Service
#define  TERI_BIS_SPOT_C      0x09 // CALL
#define  TERI_BIS_SPOT_A      0x0a // ANSW
#define  TERI_BIS_SPOT_mS     0x0b // Mail Subject
#define  TERI_BIS_SPOT_F      0x0c // File Name
#define  TERI_BIS_SPOT_bT     0x0d // binary Text
#define  TERI_BIS_SPOT_bSTS   0x0e // Socket: TCP/IP source
#define  TERI_BIS_SPOT_bSTD   0x0f // Socket: TCP/IP dest
#define  TERI_BIS_SPOT_bSUS   0x10 // Socket: UDP/IP source
#define  TERI_BIS_SPOT_bSUD   0x11 // Socket: UDP/IP dest
#define  TERI_BIS_SPOT_bMD    0x12 // DVB MAC-address
#define  TERI_BIS_SPOT_Pr     0x13 // Protocol Name
#define  TERI_BIS_SPOT_PhN    0x14 // Phone Number
#define  TERI_BIS_SPOT_PhI    0x15 // Phone IMSI
#define  TERI_BIS_SPOT_PhE    0x16 // Phone IMEI
#define  TERI_BIS_SPOT_bMa    0x17 // MAC-address
#define  TERI_BIS_SPOT_bI6S   0x18 // IPv6-source
#define  TERI_BIS_SPOT_bI6D   0x19 // IPv6-destination
#define  TERI_BIS_SPOT_LGN    0x1a // LOGIN
#define  TERI_BIS_SPOT_ICQ    0x1b // ICQ-number
#define  TERI_BIS_SPOT_URL    0x1c // URL
#define  TERI_BIS_SPOT_MED    0x1d // Media-тип (content-type)
#define  TERI_BIS_SPOT_mA     0x1e // E-Mail address
#define  TERI_BIS_SPOT_bDPid  0x1f // DVB PID
#define  TERI_BIS_SPOT_bVLAN  0x20 // Virtual LAN
#define  TERI_BIS_SPOT_bMPLS  0x21 // MPLS label
#define  TERI_BIS_SPOT_ISN    0x22 // Social Networks Identifier
#define  TERI_BIS_SPOT_PhB    0x23 // Phone BlackBerry PIN
#define  TERI_BIS_SPOT_DN     0x24 // DN - Domain Name
#define  TERI_BIS_SPOT_URLad  0x25 // URL - Ads
#define  TERI_BIS_SPOT_DNad   0x26 // DN - Domain Name - Ads
#define  TERI_BIS_SPOT_ORIG   0x27 // HTTP Origin
#define  TERI_BIS_SPOT_REF    0x28 // HTTP Referer
#define  TERI_BIS_SPOT_fGET   0x29 // HTTP GET flag
#define  TERI_BIS_SPOT_fPOST  0x2a // HTTP POST flag
#define  TERI_BIS_SPOT_NASp   0x2b // HTTP GET flag
#define  TERI_BIS_SPOT_BSid   0x2c // HTTP POST flag

#define  TERI_BIS_SPOT_MAX    0x2c // максимальный SPOT
#define  TERI_BIS_SPOT_COUNT  0x2d // количество SPOT

/* получить версию библиотеки
 * version_str - полное наименование версии ядра
 * version_major - старшее числовое значение версии
 * version_minor - младшее числовое значение версии
 */
extern "C" TERI_BIS_API void MSCU_CALL_PREFIX teri_bis_get_version(gpchar_p version_str, gint_p version_major, gint_p version_minor);

/* создает экземпляр объекта и возвращает указатель на него
 *
 * функция возвращает 0 - если произошла ошибка создания экземпляра
 *   в случае успеха возвращается указатель на созданный экземпляр
 */
extern "C" TERI_BIS_API gpointer MSCU_CALL_PREFIX teri_bis_create();

/* разрушет экземпляр объекта, на который указываеи AInstance
 *
 * AInstance - экземпляр объекта
 *
 * в случае успеха возвращает TERI_ERROR_SUCCESS
 */
extern "C" TERI_BIS_API gint MSCU_CALL_PREFIX teri_bis_destroy(gpointer instance);

/* получить информацию о последней ошибке
 *
 * код ошибки изменяется при вызове любой функции в последующем
 */
extern "C" TERI_BIS_API gint MSCU_CALL_PREFIX teri_bis_get_error(gpointer instance, gint_p wParam, gint_p lParam, gpchar_p MsgStr);

/* сохраняет сжатый маршрут в буфер
 *
 * instance - экземпляр объекта
 * buf - указатель на буфер, в который записывается маршрут
 * буфер должен создаваться вызывающим модулем
 * len - размер буфера в байтах
 *
 * для того чтобы узнать размер буфера, необходимого для записи маршрута,
 * необходимо вызвать данную функцию с нулевым указателем на буфер
 * или с нулевой длиной. в этом случае функция в качестве результата вернет
 * необходимый размер в байтах
 *
 * если длина буфера неверна (недостаточна), функция вернет ошибку TERI_ERROR_BAD_ARG
 *
 * в случае удачного сохранения функция вернет количество сохраненных байт
 */
extern "C" TERI_BIS_API gint MSCU_CALL_PREFIX teri_bis_save(gpointer instance, gpchar buf, gint32 len);

/* загружает сжатый маршрут из буфера
 *
 * instance - экземпляр объекта
 * buf - указатель на буфер, в который записывается маршрут
 * len - размер буфера в байтах
 *
 * если неверная версия данных, функция вернет ошибку TERI_ERROR_BAD_DATA
 * если длина буфера неверна (с точностью до байта), функция вернет ошибку TERI_ERROR_BAD_DATA
 *
 * в случае удачной загрузки функция вернет количество прочитанных байт
 */
extern "C" TERI_BIS_API gint MSCU_CALL_PREFIX teri_bis_load(gpointer instance, gpchar buf, gint32 len);

/* производит загрузку в ядро словарных признаков в ITF-формате
 * генерирует маршрут и сжимает его
 *
 * instance - экземпляр объекта
 * mode - битовая карта, содержащая опции настройки (TERI_MODE_XXX)
 * buf, len: буфер с признаками в ITF-формате
 * check_only - компиляция/проверка
 * cb - указатель на функцию обратного вызова
 *   данная функия вызывается при возникновении любого события
 *   от уведомления о начале операции до критической ошибки
 * ud - пользовательские данные - первый параметр, передаваемый при вызове функции cb (может иметь любое значение)
 *
 * возвращает TERI_ERROR_SUCCESS в случае удачной генерации маршрута
 * ошибочные ситуации:
 *   TERI_ERROR_TOKEN_CLASH          - конфликт между признаками
 *   TERI_ERROR_BAD_SYNTAX           - неверный синтаксис
 */
extern "C" TERI_BIS_API gint MSCU_CALL_PREFIX teri_bis_generate(gpointer instance, gint mode, gpchar buf, gint len, gboolean check_only, Tteri_generate_callback cb, gpointer ud);

/* производит загрузку в ядро словарных признаков в ITF-формате
 * генерирует маршрут и сжимает его
 * wts - "with transparent spots" - установка списка прозрачных областей поиска
 * прозрачная область - такая, признаки которой преобразуются в "\." (любой символ), т.е. любой поиск по данной области даст положительный результат
 *
 * instance - экземпляр объекта
 * mode - битовая карта, содержащая опции настройки (TERI_MODE_XXX)
 * buf, len: буфер с признаками в ITF-формате
 * check_only - компиляция/проверка
 * cb - указатель на функцию обратного вызова
 *   данная функия вызывается при возникновении любого события
 *   от уведомления о начале операции до критической ошибки
 * ud - пользовательские данные - первый параметр, передаваемый при вызове функции cb (может иметь любое значение)
 * count - количество элементов в массиве spots
 * spots - массив объектов (мест) поиска - константы TERI_BIS_SPOT_XXX
 *
 * возвращает TERI_ERROR_SUCCESS в случае удачной генерации маршрута
 * ошибочные ситуации:
 *   TERI_ERROR_TOKEN_CLASH          - конфликт между признаками
 *   TERI_ERROR_BAD_SYNTAX           - неверный синтаксис
 */
extern "C" TERI_BIS_API gint MSCU_CALL_PREFIX teri_bis_generate_wts(gpointer instance, gint mode, gpchar buf, gint len, gboolean check_only, Tteri_generate_callback cb, gpointer ud, gsize_t count, const guint32 * spots);

/* уровень признака */
/* Tteri_bis_match_level */
#define tbmlLevel1  0
#define tbmlLevel2  1

#ifndef TTERI_BIS_MATCH_ENTRY_TYPE
#define TTERI_BIS_MATCH_ENTRY_TYPE
/* вхождение признака (подпризнака) в буфер поиска */
STRUCT_PACKED_BEGIN // устанавливаем выравнивание структур в 1 байт
struct STRUCT_PACKED_ATTRIBUTE Tteri_bis_match_entry {
  gpchar buf; /* указатель на первый символ вхождения (не внутри буфера поиска!) */
  gint32 len; /* количество символов во вхождении */
};
STRUCT_PACKED_END // восстанавливаем выравнивание структур по умолчанию
/// указатель на структуру Tteri_bis_match_entry
typedef Tteri_bis_match_entry* Pteri_bis_match_entry;
#endif

#ifndef TTERI_BIS_MATCH_TOKEN_TYPE
#define TTERI_BIS_MATCH_TOKEN_TYPE
/* информация о найденном признаке */
STRUCT_PACKED_BEGIN // устанавливаем выравнивание структур в 1 байт
struct STRUCT_PACKED_ATTRIBUTE Tteri_bis_match_token {
  gint level;
  guint32 absolute_prio; /* абсолютный приоритет */
  guint32 up_id; /* номер раздела */
  guint32 up_prio; /* приоритет раздела */
  guint32 id; /* номер признака */
  guint32 id_ext; /* расширение номера признака */
  guint32 prio; /* приоритет */
  gint32  is_stat; /* флаг - stat (0 - отсутствует, на 0 - присутствует) */
  gint32  is_rem; /* флаг - rem (0 - отсутствует, на 0 - присутствует) */
  gpchar  path; /* путь */
  guint32 entry_count; /* количество вхождений */
  Tteri_bis_match_entry entry[MAX_SUBTOKEN_COUNT]; /* массив вхожений */
  gpointer entry_bud[MAX_SUBTOKEN_COUNT]; /* массив вхожений */
  guint32 entry_spot[MAX_SUBTOKEN_COUNT]; /* массив областей поиска */
};
STRUCT_PACKED_END // восстанавливаем выравнивание структур по умолчанию
/// указатель на структуру Tteri_bis_match_token
typedef Tteri_bis_match_token* Pteri_bis_match_token;
#endif

/* тип Callback-функции, вызываемой при поисках
*
* ud - параметр ud, передаваемый при вызове функции teri_bis_match_data (может иметь любое значение)
* token - информация о найденном вхождении
*/
typedef void (MSCU_CALL_PREFIX * Tteri_bis_match_callback)(gpointer ud, Pteri_bis_match_token token);

/* начало поиска
 *
 * instance - экземпляр объекта
 *
 * возвращает TERI_ERROR_SUCCESS, если все в порядке
 */
extern "C" TERI_BIS_API gint MSCU_CALL_PREFIX teri_bis_match_start(gpointer instance);

/* процедура, производящая поиск в очередном буфере
 *
 * instance - экземпляр объекта
 * buf - указатель на буфер, внутри которого производится поиск
 *       содержимое буфера трактуется как многострочный текст с кодировкой cp1251
 * len - размер буфера в байтах
 * spot - объект (место) поиска - константы TERI_BIS_SPOT_XXX
 * bud - параметр ud, ассоциируемый с текущим буфером поиска
 *
 * возвращает TERI_ERROR_SUCCESS в случае успеха
 */
extern "C" TERI_BIS_API gint MSCU_CALL_PREFIX teri_bis_match_data(gpointer instance, gconstpchar buf, gint32 len, guint32 spot, gpointer bud);

/* процедура, завершающая поиск и возвращающая результат поиска
 *
 * instance - экземпляр объекта
 * cb - указатель на функцию обратного вызова
 *   данная функия вызывается при обнаружении вхождения (может быть вызвана от 0 до нескольких раз)
 *   данная функия вызывается для каждого найденного stat-признака
 *   далее из всех обычных найденных признаков выбирается один с навысшим приоритетом, для которого и вызывается функция
 *     т.е. если будут найдены несколько не статистических признаков (даже с одинаковым приоритетом), функция вызовется только один раз для одного из них
 * ud - пользовательские данные - первый параметр, передаваемый при вызове функции cb (может иметь любое значение)
 *
 * возвращает общее количество найденных признаков
 */
extern "C" TERI_BIS_API gint MSCU_CALL_PREFIX teri_bis_match_stop(gpointer instance, Tteri_bis_match_callback cb, gpointer ud);

// процедура, производящая поиск в буферах атомарно
// поиск во втором уровне не производится
// не поддерживаются составные признаки
// не поддерживаются типы признаков (rem/stat)
//
// instance - экземпляр объекта
// buf - указатель на буфер, внутри которого производится поиск
//       содержимое буфера трактуется как многострочный текст с кодировкой cp1251
// len - размер буфера в байтах
// buf2 - указатель на дополнительный буфер, внутри которого производится поиск
//       содержимое буфера трактуется как многострочный текст с кодировкой cp1251
// len2 - размер дополнительный буфера в байтах
// spot - объект (место) поиска - константы TERI_BIS_SPOT_XXX
// bud - параметр ud, ассоциируемый с текущим буфером поиска
// cb - указатель на функцию обратного вызова
//   данная функия вызывается при обнаружении вхождения (может быть вызвана от 0 до 1 раза)
//   из всех обычных найденных признаков выбирается один с навысшим приоритетом, для которого и вызывается функция
//     т.е. если будут найдены несколько признаков (даже с одинаковым приоритетом), функция вызовется только один раз для одного из них
// ud - пользовательские данные - первый параметр, передаваемый при вызове функции cb (может иметь любое значение)
//
// возвращает кол-во вхождений в случае успеха
extern "C" TERI_BIS_API gint MSCU_CALL_PREFIX teri_bis_match_medium_atomic(gpointer instance, gconstpchar buf, gint32 len, gconstpchar buf2, gint32 len2, guint32 spot, gpointer bud, Tteri_bis_match_callback cb, gpointer ud);

// процедура, производящая поиск в буферах атомарно
// производится поиск по буферц до первого вхождения любого признака
// поиск во втором уровне не производится
// не поддерживаются составные признаки
// не поддерживаются типы признаков (rem/stat)
//
// instance - экземпляр объекта
// buf - указатель на буфер, внутри которого производится поиск
//       содержимое буфера трактуется как многострочный текст с кодировкой cp1251
// len - размер буфера в байтах
// buf2 - указатель на дополнительный буфер, внутри которого производится поиск
//       содержимое буфера трактуется как многострочный текст с кодировкой cp1251
// len2 - размер дополнительный буфера в байтах
// spot - объект (место) поиска - константы TERI_BIS_SPOT_XXX
// bud - параметр ud, ассоциируемый с текущим буфером поиска
// cb - указатель на функцию обратного вызова
//   данная функия вызывается при обнаружении вхождения (может быть вызвана от 0 до 1 раза)
// ud - пользовательские данные - первый параметр, передаваемый при вызове функции cb (может иметь любое значение)
//
// возвращает кол-во вхождений в случае успеха
extern "C" TERI_BIS_API gint MSCU_CALL_PREFIX teri_bis_match_medium_atomic_first_only(gpointer instance, gconstpchar buf, gint32 len, gconstpchar buf2, gint32 len2, guint32 spot, gpointer bud, Tteri_bis_match_callback cb, gpointer ud);

// процедура, производящая поиск в буферах атомарно
// поиск во втором уровне не производится
// поддерживаются составные признаки
// не поддерживаются типы признаков (rem/stat)
// не поддерживаются приоритеты - выдаются все найденные признаки
//
// instance - экземпляр объекта
// buf - указатель на буфер, внутри которого производится поиск
//       содержимое буфера трактуется как многострочный текст с кодировкой cp1251
// len - размер буфера в байтах
// buf2 - указатель на дополнительный буфер, внутри которого производится поиск
//       содержимое буфера трактуется как многострочный текст с кодировкой cp1251
// len2 - размер дополнительный буфера в байтах
// spot - объект (место) поиска - константы TERI_BIS_SPOT_XXX
// bud - параметр ud, ассоциируемый с текущим буфером поиска
// cb - указатель на функцию обратного вызова
//   данная функия вызывается при обнаружении вхождения (может быть вызвана от 0 до нескольких раз)
// ud - пользовательские данные - первый параметр, передаваемый при вызове функции cb (может иметь любое значение)
//
// возвращает кол-во вхождений в случае успеха
extern "C" TERI_BIS_API gint MSCU_CALL_PREFIX teri_bis_match_medium_atomic_all(gpointer instance, gconstpchar buf, gint32 len, gconstpchar buf2, gint32 len2, guint32 spot, gpointer bud, Tteri_bis_match_callback cb, gpointer ud);

// процедура, производящая поиск в буферах атомарно
// поиск во втором уровне не производится
// поддерживаются составные признаки
// не поддерживаются типы признаков (rem/stat)
// не поддерживаются приоритеты - выдаются все найденные признаки
//
// instance - экземпляр объекта
// count - количество в элементах массивов bufs, lens, spots, buds
// bufs - массив указателей на буфер, внутри которого производится поиск
//       содержимое буфера трактуется как многострочный текст с кодировкой cp1251
// lens - массив размеров буферов поиска в байтах
// spots - массив объектов (мест) поиска - константы TERI_BIS_SPOT_XXX
// buds - массив параметров ud, ассоциируемых с текущим буфером поиска, может быть равен 0
// cb - указатель на функцию обратного вызова
//   данная функия вызывается при обнаружении вхождения (может быть вызвана от 0 до нескольких раз)
// ud - пользовательские данные - первый параметр, передаваемый при вызове функции cb (может иметь любое значение)
//
// возвращает кол-во вхождений в случае успеха
extern "C" TERI_BIS_API gint MSCU_CALL_PREFIX teri_bis_match_medium_atomic_all_bufs(gpointer instance, gint count, gconstpchar* bufs, gint32* lens, guint32* spots, gpointer* buds, Tteri_bis_match_callback cb, gpointer ud);

/* процедура, производящая поиск в очередном буфере
 *
 * instance - экземпляр объекта
 * buf - указатель на буфер, внутри которого производится поиск
 *       содержимое буфера трактуется как многострочный текст с кодировкой cp1251
 * len - размер буфера в байтах
 * spot - объект (место) поиска - константы TERI_BIS_SPOT_XXX
 *
 * возвращает число найденных вхождений в случае успеха
 */
extern "C" TERI_BIS_API gint MSCU_CALL_PREFIX teri_bis_match_simple(gpointer instance, gpchar buf, gint32 len, guint32 spot);

#ifndef TTERI_BIS_SYNTAX_ENTRY_TYPE
#define TTERI_BIS_SYNTAX_ENTRY_TYPE
/* вхождение служебного символа в буфер поиска */
STRUCT_PACKED_BEGIN // устанавливаем выравнивание структур в 1 байт
struct STRUCT_PACKED_ATTRIBUTE Tteri_bis_syntax_entry {
  gint32 pos; /* индекс первого символа вхождения (начиная с 0) */
  gint32 len; /* количество символов во вхождении */
};
STRUCT_PACKED_END // восстанавливаем выравнивание структур по умолчанию
/// указатель на структуру Tteri_bis_syntax_entry
typedef Tteri_bis_syntax_entry* Pteri_bis_syntax_entry;
#endif

/*
 * функция парсинга строки со служебными символами из человеческого во внутренний формат (htf->ttf)
 * возвращает -1, если все прошло нормально или позицию символа если произошла ошибка парсинга
 *
 * параметры:
 *   accept_container - определяет возможность появления в строке "\(?P<имя_контейнера>)", "\b", "\^", "\$"
 *   buf[len] - строка в htf-формате
 *   entry[entry_len] - массив, принимающий позиции вхождений служебных символов
 *   IN:entry_len - размер массива (количество элементов)
 *   OUT:entry_len - количество фактически записанных элементов
 */
extern "C" TERI_BIS_API gint MSCU_CALL_PREFIX teri_bis_check_syntax(gboolean accept_containers, gpchar buf, gint len, Pteri_bis_syntax_entry entry, gint_p entry_len);

//////////////////////////////////////////////////////////////////////////
extern "C" TERI_BIS_API void MSCU_CALL_PREFIX teri_bis_wrapper_set_klog_std_event(Tklog_std_event Aklog_std_event); //!!!deprecated
extern "C" TERI_BIS_API void MSCU_CALL_PREFIX teri_bis_wrapper_set_terminated_flag(gboolean_p Aterminated_flag); //!!!deprecated

extern "C" TERI_BIS_API gboolean MSCU_CALL_PREFIX teri_bis_wrapper_std_generate_callback(gpointer user_data, gint32 Msg, guint32 wParam, guint32 lParam, gpchar MsgStr);

extern "C" TERI_BIS_API gpointer MSCU_CALL_PREFIX teri_bis_wrapper_create();
extern "C" TERI_BIS_API void MSCU_CALL_PREFIX teri_bis_wrapper_destroy(gpointer instance);

extern "C" TERI_BIS_API gboolean MSCU_CALL_PREFIX teri_bis_wrapper_set_parameters(gpointer instance, guint32 stat_period, gconstpchar stat_dir_name, guint32 file_update_period);
extern "C" TERI_BIS_API gconstpchar MSCU_CALL_PREFIX teri_bis_wrapper_stat_dir_name(gpointer instance);

extern "C" TERI_BIS_API gboolean MSCU_CALL_PREFIX teri_bis_wrapper_set_log_parameters(gpointer instance, gconstpchar name, gboolean log_progress, gboolean log_margins);

// процедура, устанавливающая список прозрачных областей поиска
// прозрачная область - такая, признаки которой преобразуются в "\." (любой символ), т.е. любой поиск по данной области даст положительный результат
//
// instance - экземпляр объекта, возвращаемый функцией teri_bis_wrapper_create
// count - количество элементов в массиве spots
// spots - массив объектов (мест) поиска - константы TERI_BIS_SPOT_XXX
//
// возвращает true в случае успеха
extern "C" TERI_BIS_API gboolean MSCU_CALL_PREFIX teri_bis_wrapper_set_transparent_spots(gpointer instance, gsize_t count, const guint32 * spots);

extern "C" TERI_BIS_API gconstpchar MSCU_CALL_PREFIX teri_bis_wrapper_error_message(gpointer instance);

// Attention! This function updates teri_bis engine, if there is newly reloaded one, so do not call this function
// more than one time per atomic search stage (teri_bis_match_start..teri_bis_match_stop)
extern "C" TERI_BIS_API gpointer MSCU_CALL_PREFIX teri_bis_wrapper_engine(gpointer instance);
// enter/leave procedure to use in multi-threaded search
extern "C" TERI_BIS_API void MSCU_CALL_PREFIX teri_bis_wrapper_engine_enter(gpointer instance);
extern "C" TERI_BIS_API void MSCU_CALL_PREFIX teri_bis_wrapper_engine_leave(gpointer instance);
// returns engine pointer that is stable within active thread until next teri_bis_wrapper_tls_engine function call
// function compares values of main engine and thread local storage engine pointers
// then if differs, new tls engine is created as copy of changed main tls engine
extern "C" TERI_BIS_API gpointer MSCU_CALL_PREFIX teri_bis_wrapper_tls_engine(gpointer instance);

// class LOCAL_API Tteri_bis_wrapper_holder {
// public:
//   Tteri_bis_wrapper_holder(gpointer teri_bis_wrapper_instance): instance_(teri_bis_wrapper_instance)
//   {
//   };
//   ~Tteri_bis_wrapper_holder()
//   {
//     if (instance_)
//       teri_bis_wrapper_destroy(instance_);
//   };
//   gpointer instance_;
// private:
//   Tteri_bis_wrapper_holder() {}
//   Tteri_bis_wrapper_holder(const Tteri_bis_wrapper_holder &) {}
// };

// this is suitable class to replace teri_bis_wrapper_engine_enter/teri_bis_wrapper_engine_leave usage
class LOCAL_API Tteri_bis_wrapper_engine_locker {
public:
  Tteri_bis_wrapper_engine_locker(gpointer teri_bis_wrapper_instance): instance_(teri_bis_wrapper_instance)
  {
    if (instance_)
      teri_bis_wrapper_engine_enter(instance_);
  };
  ~Tteri_bis_wrapper_engine_locker()
  {
    if (instance_)
      teri_bis_wrapper_engine_leave(instance_);
  };
private:
  Tteri_bis_wrapper_engine_locker() {}
  Tteri_bis_wrapper_engine_locker(const Tteri_bis_wrapper_engine_locker &) {}
  gpointer instance_;
};

extern "C" TERI_BIS_API gboolean MSCU_CALL_PREFIX teri_bis_wrapper_compile(gpointer instance, gconstpchar file_name, gconstpchar file_name_to_save, gboolean do_save, gboolean check_only);
extern "C" TERI_BIS_API gboolean MSCU_CALL_PREFIX teri_bis_wrapper_load(gpointer instance, gconstpchar file_name);
extern "C" TERI_BIS_API gboolean MSCU_CALL_PREFIX teri_bis_wrapper_generate(gpointer instance, gconstpchar buf, guint len);
extern "C" TERI_BIS_API void MSCU_CALL_PREFIX teri_bis_wrapper_reload(gpointer instance);
// make reloading if file is modified with period <file_update_period> from <teri_bis_wrapper_set_parameters function>
// if reloading thread is active, returns false
extern "C" TERI_BIS_API gboolean MSCU_CALL_PREFIX teri_bis_wrapper_reload_if_modified(gpointer instance);
// make reloading if file is modified without any period
// if reloading thread is active, returns false
extern "C" TERI_BIS_API gboolean MSCU_CALL_PREFIX teri_bis_wrapper_reload_if_modified_raw(gpointer instance);

extern "C" TERI_BIS_API gboolean MSCU_CALL_PREFIX teri_bis_wrapper_engine_reloading_active(gpointer instance);

extern "C" TERI_BIS_API void MSCU_CALL_PREFIX teri_bis_wrapper_stat_update(gpointer instance, gint level, guint32 id);
extern "C" TERI_BIS_API void MSCU_CALL_PREFIX teri_bis_wrapper_save_stat_sync(gpointer instance);
extern "C" TERI_BIS_API void MSCU_CALL_PREFIX teri_bis_wrapper_save_stat_async(gpointer instance);
extern "C" TERI_BIS_API gboolean MSCU_CALL_PREFIX teri_bis_wrapper_save_stat_if_needed(gpointer instance);
extern "C" TERI_BIS_API gboolean MSCU_CALL_PREFIX teri_bis_wrapper_stat_saving_active(gpointer instance);

#ifndef TTERI_BIS_WRAPPER_STATISTICS_TYPE
#define TTERI_BIS_WRAPPER_STATISTICS_TYPE
STRUCT_PACKED_BEGIN // устанавливаем выравнивание структур в 1 байт
struct STRUCT_PACKED_ATTRIBUTE Tteri_bis_wrapper_statistics {
  // перегрузка файла признаков
  gint64 reload_ok         ;
  gint64 mod_reload_ok     ; // для определения изменения

  gint64 reload_bad        ;
  gint64 mod_reload_bad    ; // для определения изменения

  // сохранение статистики
  gint64 stat_ok           ;
  gint64 mod_stat_ok       ; // для определения изменения

  gint64 stat_bad          ;
  gint64 mod_stat_bad      ; // для определения изменения

  // срабатывание признаков
  gint64 tokens_stat       ;
  gint64 mod_tokens_stat   ; // для определения изменения

  gint64 tokens_rdy        ;
  gint64 mod_tokens_rdy    ; // для определения изменения

  gint64 tokens_zap        ;
  gint64 mod_tokens_zap    ; // для определения изменения

  gint64 tokens_unk        ;
  gint64 mod_tokens_unk    ; // для определения изменения
};
STRUCT_PACKED_END // восстанавливаем выравнивание структур по умолчанию
/// указатель на структуру Tteri_bis_wrapper_statistics
typedef Tteri_bis_wrapper_statistics* Pteri_bis_wrapper_statistics;
#endif

extern "C" TERI_BIS_API volatile Tteri_bis_wrapper_statistics * MSCU_CALL_PREFIX teri_bis_wrapper_statistics(gpointer instance);
extern "C" TERI_BIS_API void MSCU_CALL_PREFIX teri_bis_wrapper_statistics_clear(gpointer instance);
//----------------------------------------------------------------------------

// ID EXT field description
//   3                   2                   1                   0
// 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//|CTL| OR_NMBR   |!| RF  |AND_NMB|AND_SIZ|TT_RSRV|      TT       |
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/* флаги поля ID_EXT */
// флаги Traffic_Type – битовая маска, отображающая разрешенные к отбору типы данных
#define TERI_ID_EXT_TT_HTTP											0x00000001
#define TERI_ID_EXT_TT_FTP											0x00000002
#define TERI_ID_EXT_TT_MAIL											0x00000004
#define TERI_ID_EXT_TT_IM												0x00000008 // instant messaging
#define TERI_ID_EXT_TT_VOIP											0x00000010
#define TERI_ID_EXT_TT_OTH											0x00000020
#define TERI_ID_EXT_TT_AAA											0x00000040
#define TERI_ID_EXT_TT_SOCIAL										0x00000080 // social networks
#define TERI_ID_EXT_TT_RESERVED1								0x00000100 // reserved for future use
#define TERI_ID_EXT_TT_RESERVED2								0x00000200 // reserved for future use
#define TERI_ID_EXT_TT_RESERVED3								0x00000400 // reserved for future use
#define TERI_ID_EXT_TT_RESERVED4								0x00000800 // reserved for future use
// объединение признаков по AND
#define TERI_ID_EXT_SUBSELECT_AND_SIZE_MASK			0x0000f000 // определяет количество элементарных неотрицательных подпризнаков в конъюнкте составного признака, приведенного к ДНФ (отрицательные подпризнаки в подсчете не учитываются, для отрицательных подпризнаков значение данного поля должно быть нулевым)
#define TERI_ID_EXT_SUBSELECT_AND_SIZE_SHIFT						12
#define TERI_ID_EXT_SUBSELECT_AND_NUMBER_MASK		0x000f0000 // порядковый номер элементарного неотрицательного подпризнака (поля типа Subselect_AND, для отрицательных подпризнаков значение данного поля должно быть нулевым)
#define TERI_ID_EXT_SUBSELECT_AND_NUMBER_SHIFT					16
// флаги Register Flags - регистрации данных по признаку
#define TERI_ID_EXT_RF_DECODED									0x00100000 /* флаг регистрации данных по признаку (Register Flag) – если бит включен - регистрировать декодированные данные */
#define TERI_ID_EXT_RF_RAW_MAC									0x00200000 /* флаг регистрации данных по признаку (Register Flag) – если бит включен - регистрировать сырые пакеты с MAC-уровнем */
#define TERI_ID_EXT_RF_RAW_IP										0x00400000 /* флаг регистрации данных по признаку (Register Flag) – если бит включен - регистрировать сырые IP-пакеты */
// флаг отрицания
#define TERI_ID_EXT_NOT_FLAG										0x00800000 /* признак наличия логического отрицания у элементарного подпризнака (поля типа Subselect_AND) */
// объединение признаков по AND
#define TERI_ID_EXT_SUBSELECT_OR_NUMBER_MASK		0x3f000000 // порядковый номер комбинации подпризнаков (полей типа Subselect_OR), являющихся конъюнктами составного признака, приведенного к дизъюнктивной нормальной форме (ДНФ)
#define TERI_ID_EXT_SUBSELECT_OR_NUMBER_SHIFT						24
// Control – флаги режима контроля
#define TERI_ID_EXT_CONTROL_MASK								0xc0000000
#define TERI_ID_EXT_CONTROL_SHIFT												30
// Control values, shifted: (v & TERI_ID_EXT_CONTROL_MASK) >> TERI_ID_EXT_CONTROL_SHIFT
#define TERI_ID_EXT_CONTROL_NA												0x00 // не определен (устанавливается для обычных признаков)
#define TERI_ID_EXT_CONTROL_FULL_SPARE								0x01 // Полный контроль (режим совмещенного контроля)
#define TERI_ID_EXT_CONTROL_STAT											0x02 // Статистический контроль
#define TERI_ID_EXT_CONTROL_FULL_SINGLE								0x03 // Полный контроль (режим раздельного контроля)

// define functions
#define TERI_ID_EXT_EXTRACT_CONTROL(id_ext) ((id_ext >> 30) & 0x03)
#define TERI_ID_EXT_EXTRACT_SUBSELECT_OR_NUMBER(id_ext) ((id_ext >> 24) & 0x3f)
#define TERI_ID_EXT_EXTRACT_NOT_FLAG(id_ext) ((id_ext >> 23) & 0x01)
#define TERI_ID_EXT_EXTRACT_SUBSELECT_AND_NUMBER(id_ext) ((id_ext >> 16) & 0xf)
#define TERI_ID_EXT_EXTRACT_SUBSELECT_AND_SIZE(id_ext) ((id_ext >> 12) & 0xf)
#define TERI_ID_EXT_EXTRACT_TRAFFIC_TYPE(id_ext) (id_ext & 0xfff)

#define TERI_ID_EXT_IS_NEGATIVE(id_ext) (((id_ext >> 23) & 0x01) != 0)

#define TERI_ID_EXT_HAS_RF_DECODED(id_ext) (((id_ext) & TERI_ID_EXT_RF_DECODED) != 0)
#define TERI_ID_EXT_HAS_RF_RAW_MAC(id_ext) (((id_ext) & TERI_ID_EXT_RF_RAW_MAC) != 0)
#define TERI_ID_EXT_HAS_RF_RAW_IP(id_ext) (((id_ext) & TERI_ID_EXT_RF_RAW_IP) != 0)
// either raw_ip or raw_mac
#define TERI_ID_EXT_HAS_RF_RAW(id_ext) (TERI_ID_EXT_HAS_RF_RAW_MAC(id_ext) || TERI_ID_EXT_HAS_RF_RAW_IP(id_ext))

#endif
