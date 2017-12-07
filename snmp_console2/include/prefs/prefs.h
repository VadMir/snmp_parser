/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/// \file prefs.h
/// \mainpage
/// @{
/// \section attention Предупреждение
/// \b ВНИМАНИЕ! Файл <b>"prefs.h"</b> распространяется под авторским правом РАЗРАБОТЧИКА данного файла.
/// Любые изменения в данном файле СТОРОННИМИ разработчиками НЕДОПУСТИМЫ.
/// Для использования данного файла просто включите его в проект с помощью директивы #include.
///
/// \section updated Последнее обновление
/// <b>2016-08-14</b>
///
/// \section changelog Изменения
/// - [+] 2016-08-14 - Добавлена функция prefs_params_terminal_dlg;
/// - [+] 2015-04-13 - Добавлена функция prefs_find_preference;
/// - [+] 2014-03-14 - Добавлено: тип-категория и соответствующие функции: prefs_register_category;
/// - [+] 2012-04-09 - добавлены функции prefs_unregister_XXX
/// - [*] 2012-04-09 - обновлена документация на функции prefs_register_XXX
/// - [+] 2011-07-20 - добавлена функция prefs_set_tags
/// - [+] 2010-07-26 - добавлены функции prefs_set_min/max_XXX
/// - [+] 2010-04-17 - добавлена функция prefs_set_xml_mode
/// - [+] 2009-09-21 - добавлена функция prefs_set_expert
/// - [*] 2009-09-19 - удалены все prefs_get_tmp_val_XXX-функции
/// - [*] 2009-09-18 - фиксированная версия для обратной совместимости
/// - [-] 2009-09-18 - исправлены ошибки в поведении свойства "файл" (PREF_FILE)
/// - [+] 2009-08-03 - добавлен msecs-тип и соответствующие функции: prefs_register_XXX, prefs_get_XXX
/// - [+] 2009-05-18 - добавлен int64-тип и соответствующие функции: prefs_register_XXX, prefs_get_XXX
/// - [*] 2009-04-17 - разработка
///
/// \section description Описание
/// Данный документ содержит API модуля обработки настроек.
///
/// \section copyright Авторские права
/// Copyright (C) MSC, ORG 2002-2015
///
/// @}

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#ifndef __PREFS_H
/// \cond
#define __PREFS_H
/// \endcond

// Now we use the generic helper definitions above to define XXX_API and XXX_LOCAL.
// XXX_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
// XXX_LOCAL is used for non-api symbols.
#ifdef PREFS_EXPORTS // defined if we are building the XXX DLL (instead of using it)
  /// \cond
  #define PREFS_API MSCU_HELPER_DLL_EXPORT
  /// \endcond
#else
  /// \cond
  #define PREFS_API MSCU_HELPER_DLL_IMPORT
  #pragma comment( lib, "prefs" )
  /// \endcond
#endif // PREFS_EXPORTS
#define PREFS_LOCAL MSCU_HELPER_DLL_LOCAL

#include <mscu_types.h>

/// \defgroup prefs_interface Интерфейс модуля обработки настроек
/// \{

/// Размер строкового буфера, предназначенного для хранения имен файлов и т.д. Задается в байтах
#define PREFS_MAX_PATH 4096

/// Указатель на внутренний объект-параметр
typedef gpointer preference_p;

/// \name Валидаторы
/// \{

/// режим вызова валидатора параметра (action)
#define vaCorrect 0  ///< проверка и коррекция, применение
#define vaVerify  1  ///< проверка на правильность (временные значения)
#define vaApply   2  ///< применение (без вывода ошибки)

/// валидатор параметра (простой)
///
/// \return 0 при удачном завершении
/// \return может вернуть описание ошибки (для vaCorrect, vaVerify)
///
typedef gconstpchar (MSCU_CALL_PREFIX * TPref_validator)(preference_p preference, gint action);

/// валидатор параметра (для элементов массива)
///
/// \return 0 при удачном завершении
/// \return может вернуть описание ошибки (для vaCorrect, vaVerify)
///
typedef gconstpchar (MSCU_CALL_PREFIX * TPref_validator_arr)(preference_p preference, gint action, guint index);

/// \}

/// вызов внешнего диалога
typedef gboolean (MSCU_CALL_PREFIX * Talien_dialog_executor)(gpointer user_data);

/// вызов функции обновления индекса
typedef void (MSCU_CALL_PREFIX * Tindex_executor)(gpointer user_data);

//////////////////////////////////////////////////////////////////////////
/// Адаптер для массива строк с завершающим нулем
struct Tprefs_string_array_adapter {
public:
  Tprefs_string_array_adapter(guint elements, guint chars): elements_(elements), chars_(chars), count(0), data(0)
  {
    data = new gpchar[elements_];
    for (guint i = 0; i < elements_; ++i) {
      data[i] = new gchar[chars_];
      *data[i] = 0;
    }
  }
  ~Tprefs_string_array_adapter()
  {
    for (guint i = 0; i < elements_; ++i) {
      delete[] (data[i]);
    }
    delete[] data;
  }
public:
  gchar** data;
  guint count;
  guint elements_;
  guint chars_;
private:
  Tprefs_string_array_adapter() {};
};

//////////////////////////////////////////////////////////////////////////
/// регистрация диалога
///
/// \param name         внутреннее имя диалога
/// \param title        заголовок в GUI
/// \param description  описание диалога
/// \param readonly     триггер возможности изменения
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_dialog(gconstpchar name, gconstpchar title, gconstpchar description, gboolean_p readonly);

/// зафиксировать определенный диалог как не входящий в общую группу загрузки/сохранения
/// установить/снять флаг "эксклюзивный диалог"
///
/// \param[in] dialog_p диалог
/// \param[in] value    устанавливаемое значение (true - установить, false - снять)
///
/// \return адрес на экземпляр параметра
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_set_exclusive_dialog(preference_p dialog_p, gboolean value);

/// регистрация модуля
///
/// \param owner    модуль-родитель (NULL - если нужно разместить в корне)
/// \param name     внутреннее имя модуля
/// \param title    заголовок в GUI
/// \param description  описание (для отображения), не должно быть 0
/// \param index    позиция внутри родителя
/// \param readonly триггер возможности изменения
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_module(preference_p owner, gconstpchar name, gconstpchar title, gconstpchar description, gint index, gboolean_p readonly);

//////////////////////////////////////////////////////////////////////////
/// регистрация параметров
///
/// тип: категория
///
/// \param owner        модуль-родитель
/// \param bool_owner   параметр-владелец
/// \param bool_index   разрешение/запрещения параметра в зависимости от состояния и типа владельца:
///  - enum: битовая карта элементов из списка - если в enum выбран элемент с единичным битов в маске, параметр разрешен
///  - bool: если 0, то параметр разрешен, когда разрешен bool-владелец; если 1, то наоборот
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param title        заголовок в GUI, не должно быть 0
/// \param description  описание (для отображения), не должно быть 0
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_category_preference(preference_p owner, preference_p bool_owner, gint bool_index, gconstpchar name, gconstpchar title, gconstpchar description);
/// регистрация параметров
///
/// тип: категория
///
/// \param owner        модуль-родитель
/// \param bool_owner   параметр-владелец
/// \param bool_index   разрешение/запрещения параметра в зависимости от состояния и типа владельца:
///  - enum: битовая карта элементов из списка - если в enum выбран элемент с единичным битов в маске, параметр разрешен
///  - bool: если 0, то параметр разрешен, когда разрешен bool-владелец; если 1, то наоборот
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param title        заголовок в GUI, не должно быть 0
/// \param description  описание (для отображения), не должно быть 0
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_category_preference_arr(preference_p owner, preference_p bool_owner, gint bool_index, gconstpchar name, gconstpchar title, gconstpchar description);

//////////////////////////////////////////////////////////////////////////
/// регистрация параметров
///
/// тип: целое без знака
///
/// Возможные модификаторы – K/M/G/T (1K = 1024, 1M = 1024K = 1048576, 1G = 1024M = 1048576K = 1073741824, 1T = 1024G = 1048576M = 1073741824K = 1099511627776), 0x — шестнадцатиричные значения (0xff = 255).
///
/// \param owner        модуль-родитель
/// \param bool_owner   параметр-владелец
/// \param bool_index   разрешение/запрещения параметра в зависимости от состояния и типа владельца:
///  - enum: битовая карта элементов из списка - если в enum выбран элемент с единичным битов в маске, параметр разрешен
///  - bool: если 0, то параметр разрешен, когда разрешен bool-владелец; если 1, то наоборот
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param title        заголовок в GUI, не должно быть 0
/// \param description  описание (для отображения), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_uint_preference(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, guint_p variable);
/// регистрация скрытых параметров
///
/// тип: целое без знака
///
/// Возможные модификаторы – K/M/G/T (1K = 1024, 1M = 1024K = 1048576, 1G = 1024M = 1048576K = 1073741824, 1T = 1024G = 1048576M = 1073741824K = 1099511627776), 0x — шестнадцатиричные значения (0xff = 255).
///
/// скрытые параметры, в отличие от обычных не будут видны в диалоге настройки параметров, но будут храниться в ini-файле
///
/// \param owner        модуль-родитель
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_uint_hidden_preference(preference_p owner, TPref_validator validator, gconstpchar name, guint_p variable);
/// регистрация параметров
///
/// тип: целое без знака (массив)
///
/// Возможные модификаторы – K/M/G/T (1K = 1024, 1M = 1024K = 1048576, 1G = 1024M = 1048576K = 1073741824, 1T = 1024G = 1048576M = 1073741824K = 1099511627776), 0x — шестнадцатиричные значения (0xff = 255).
///
/// \param owner        модуль-родитель
/// \param bool_owner   параметр-владелец
/// \param bool_index   разрешение/запрещения параметра в зависимости от состояния и типа владельца:
///  - enum: битовая карта элементов из списка - если в enum выбран элемент с единичным битов в маске, параметр разрешен
///  - bool: если 0, то параметр разрешен, когда разрешен bool-владелец; если 1, то наоборот
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param title        заголовок в GUI, не должно быть 0
/// \param description  описание (для отображения), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
/// \param array_size   общий размер массива (максимальное количество элементов)
/// \param array_count  текущее количество заполненных элементов в массиве
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_uint_preference_arr(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description,
                                                                   guint_p variable, guint array_size, guint_p array_count);
/// регистрация скрытых параметров
///
/// тип: целое без знака (массив)
///
/// Возможные модификаторы – K/M/G/T (1K = 1024, 1M = 1024K = 1048576, 1G = 1024M = 1048576K = 1073741824, 1T = 1024G = 1048576M = 1073741824K = 1099511627776), 0x — шестнадцатиричные значения (0xff = 255).
///
/// скрытые параметры, в отличие от обычных не будут видны в диалоге настройки параметров, но будут храниться в ini-файле
///
/// \param owner        модуль-родитель
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
/// \param array_size   общий размер массива (максимальное количество элементов)
/// \param array_count  текущее количество заполненных элементов в массиве
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_uint_hidden_preference_arr(preference_p owner, TPref_validator_arr validator, gconstpchar name,
                                                                          guint_p variable, guint array_size, guint_p array_count);

//////////////////////////////////////////////////////////////////////////
/// регистрация параметров
///
/// тип: временной интервал в миллисекундах
///
/// Возможные модификаторы – s/m/h/d (1s = 1000 мс = 1 секунда, 1m = 60000 мс = 1 минута, 1h = 3600000 мс = 1 час, 1d = 86400000 мс = 1 день), 0x — шестнадцатиричные значения (0xff = 255).
///
/// \param owner        модуль-родитель
/// \param bool_owner   параметр-владелец
/// \param bool_index   разрешение/запрещения параметра в зависимости от состояния и типа владельца:
///  - enum: битовая карта элементов из списка - если в enum выбран элемент с единичным битов в маске, параметр разрешен
///  - bool: если 0, то параметр разрешен, когда разрешен bool-владелец; если 1, то наоборот
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param title        заголовок в GUI, не должно быть 0
/// \param description  описание (для отображения), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_msec_preference(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, guint_p variable);
/// регистрация скрытых параметров
///
/// тип: временной интервал в миллисекундах
///
/// Возможные модификаторы – s/m/h/d (1s = 1000 мс = 1 секунда, 1m = 60000 мс = 1 минута, 1h = 3600000 мс = 1 час, 1d = 86400000 мс = 1 день), 0x — шестнадцатиричные значения (0xff = 255).
///
/// скрытые параметры, в отличие от обычных не будут видны в диалоге настройки параметров, но будут храниться в ini-файле
///
/// \param owner        модуль-родитель
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_msec_hidden_preference(preference_p owner, TPref_validator validator, gconstpchar name, guint_p variable);
/// регистрация параметров
///
/// тип: временной интервал в миллисекундах (массив)
///
/// Возможные модификаторы – s/m/h/d (1s = 1000 мс = 1 секунда, 1m = 60000 мс = 1 минута, 1h = 3600000 мс = 1 час, 1d = 86400000 мс = 1 день), 0x — шестнадцатиричные значения (0xff = 255).
///
/// \param owner        модуль-родитель
/// \param bool_owner   параметр-владелец
/// \param bool_index   разрешение/запрещения параметра в зависимости от состояния и типа владельца:
///  - enum: битовая карта элементов из списка - если в enum выбран элемент с единичным битов в маске, параметр разрешен
///  - bool: если 0, то параметр разрешен, когда разрешен bool-владелец; если 1, то наоборот
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param title        заголовок в GUI, не должно быть 0
/// \param description  описание (для отображения), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
/// \param array_size   общий размер массива (максимальное количество элементов)
/// \param array_count  текущее количество заполненных элементов в массиве
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_msec_preference_arr(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description,
                                                                   guint_p variable, guint array_size, guint_p array_count);
/// регистрация скрытых параметров
///
/// тип: временной интервал в миллисекундах (массив)
///
/// Возможные модификаторы – s/m/h/d (1s = 1000 мс = 1 секунда, 1m = 60000 мс = 1 минута, 1h = 3600000 мс = 1 час, 1d = 86400000 мс = 1 день), 0x — шестнадцатиричные значения (0xff = 255).
///
/// скрытые параметры, в отличие от обычных не будут видны в диалоге настройки параметров, но будут храниться в ini-файле
///
/// \param owner        модуль-родитель
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
/// \param array_size   общий размер массива (максимальное количество элементов)
/// \param array_count  текущее количество заполненных элементов в массиве
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_msec_hidden_preference_arr(preference_p owner, TPref_validator_arr validator, gconstpchar name,
                                                                          guint_p variable, guint array_size, guint_p array_count);

//////////////////////////////////////////////////////////////////////////
/// регистрация параметров
///
/// тип: целое со знаком 64 бит
///
/// Возможные модификаторы – K/M/G/T (1K = 1024, 1M = 1024K = 1048576, 1G = 1024M = 1048576K = 1073741824, 1T = 1024G = 1048576M = 1073741824K = 1099511627776), 0x — шестнадцатиричные значения (0xff = 255).
///
/// \param owner        модуль-родитель
/// \param bool_owner   параметр-владелец
/// \param bool_index   разрешение/запрещения параметра в зависимости от состояния и типа владельца:
///  - enum: битовая карта элементов из списка - если в enum выбран элемент с единичным битов в маске, параметр разрешен
///  - bool: если 0, то параметр разрешен, когда разрешен bool-владелец; если 1, то наоборот
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param title        заголовок в GUI, не должно быть 0
/// \param description  описание (для отображения), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_int64_preference(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, gint64_p variable);
/// регистрация скрытых параметров
///
/// тип: целое со знаком 64 бит
///
/// Возможные модификаторы – K/M/G/T (1K = 1024, 1M = 1024K = 1048576, 1G = 1024M = 1048576K = 1073741824, 1T = 1024G = 1048576M = 1073741824K = 1099511627776), 0x — шестнадцатиричные значения (0xff = 255).
///
/// скрытые параметры, в отличие от обычных не будут видны в диалоге настройки параметров, но будут храниться в ini-файле
///
/// \param owner        модуль-родитель
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_int64_hidden_preference(preference_p owner, TPref_validator validator, gconstpchar name, gint64_p variable);
/// регистрация параметров
///
/// тип: целое со знаком 64 бит
///
/// Возможные модификаторы – K/M/G/T (1K = 1024, 1M = 1024K = 1048576, 1G = 1024M = 1048576K = 1073741824, 1T = 1024G = 1048576M = 1073741824K = 1099511627776), 0x — шестнадцатиричные значения (0xff = 255).
///
/// \param owner        модуль-родитель
/// \param bool_owner   параметр-владелец
/// \param bool_index   разрешение/запрещения параметра в зависимости от состояния и типа владельца:
///  - enum: битовая карта элементов из списка - если в enum выбран элемент с единичным битов в маске, параметр разрешен
///  - bool: если 0, то параметр разрешен, когда разрешен bool-владелец; если 1, то наоборот
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param title        заголовок в GUI, не должно быть 0
/// \param description  описание (для отображения), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
/// \param array_size   общий размер массива (максимальное количество элементов)
/// \param array_count  текущее количество заполненных элементов в массиве
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_int64_preference_arr(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description,
                                                                   gint64_p variable, guint array_size, guint_p array_count);
/// регистрация скрытых параметров
///
/// тип: целое со знаком 64 бит
///
/// Возможные модификаторы – K/M/G/T (1K = 1024, 1M = 1024K = 1048576, 1G = 1024M = 1048576K = 1073741824, 1T = 1024G = 1048576M = 1073741824K = 1099511627776), 0x — шестнадцатиричные значения (0xff = 255).
///
/// скрытые параметры, в отличие от обычных не будут видны в диалоге настройки параметров, но будут храниться в ini-файле
///
/// \param owner        модуль-родитель
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
/// \param array_size   общий размер массива (максимальное количество элементов)
/// \param array_count  текущее количество заполненных элементов в массиве
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_int64_hidden_preference_arr(preference_p owner, TPref_validator_arr validator, gconstpchar name,
                                                                          gint64_p variable, guint array_size, guint_p array_count);

//////////////////////////////////////////////////////////////////////////
/// регистрация параметров
///
/// тип: число с плавающей точкой двойной точности
///
/// \param owner        модуль-родитель
/// \param bool_owner   параметр-владелец
/// \param bool_index   разрешение/запрещения параметра в зависимости от состояния и типа владельца:
///  - enum: битовая карта элементов из списка - если в enum выбран элемент с единичным битов в маске, параметр разрешен
///  - bool: если 0, то параметр разрешен, когда разрешен bool-владелец; если 1, то наоборот
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param title        заголовок в GUI, не должно быть 0
/// \param description  описание (для отображения), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_double_preference(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, gdouble_p variable);
/// регистрация скрытых параметров
///
/// тип: число с плавающей точкой двойной точности
///
/// скрытые параметры, в отличие от обычных не будут видны в диалоге настройки параметров, но будут храниться в ini-файле
///
/// \param owner        модуль-родитель
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_double_hidden_preference(preference_p owner, TPref_validator validator, gconstpchar name, gdouble_p variable);
/// регистрация параметров
///
/// тип: число с плавающей точкой двойной точности (массив)
///
/// \param owner        модуль-родитель
/// \param bool_owner   параметр-владелец
/// \param bool_index   разрешение/запрещения параметра в зависимости от состояния и типа владельца:
///  - enum: битовая карта элементов из списка - если в enum выбран элемент с единичным битов в маске, параметр разрешен
///  - bool: если 0, то параметр разрешен, когда разрешен bool-владелец; если 1, то наоборот
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param title        заголовок в GUI, не должно быть 0
/// \param description  описание (для отображения), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
/// \param array_size   общий размер массива (максимальное количество элементов)
/// \param array_count  текущее количество заполненных элементов в массиве
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_double_preference_arr(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description,
                                                                     gdouble_p variable, guint array_size, guint_p array_count);
/// регистрация скрытых параметров
///
/// тип: число с плавающей точкой двойной точности (массив)
///
/// скрытые параметры, в отличие от обычных не будут видны в диалоге настройки параметров, но будут храниться в ini-файле
///
/// \param owner        модуль-родитель
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
/// \param array_size   общий размер массива (максимальное количество элементов)
/// \param array_count  текущее количество заполненных элементов в массиве
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_double_hidden_preference_arr(preference_p owner, TPref_validator_arr validator, gconstpchar name,
                                                                            gdouble_p variable, guint array_size, guint_p array_count);

//////////////////////////////////////////////////////////////////////////
/// регистрация параметров
///
/// тип: булевое значение
///
/// \param owner        модуль-родитель
/// \param bool_owner   параметр-владелец
/// \param bool_index   разрешение/запрещения параметра в зависимости от состояния и типа владельца:
///  - enum: битовая карта элементов из списка - если в enum выбран элемент с единичным битов в маске, параметр разрешен
///  - bool: если 0, то параметр разрешен, когда разрешен bool-владелец; если 1, то наоборот
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param title        заголовок в GUI, не должно быть 0
/// \param description  описание (для отображения), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_bool_preference(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, gboolean_p variable);
/// регистрация скрытых параметров
///
/// тип: булевое значение
///
/// скрытые параметры, в отличие от обычных не будут видны в диалоге настройки параметров, но будут храниться в ini-файле
///
/// \param owner        модуль-родитель
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_bool_hidden_preference(preference_p owner, TPref_validator validator, gconstpchar name, gboolean_p variable);
/// регистрация параметров
///
/// тип: булевое значение (массив)
///
/// \param owner        модуль-родитель
/// \param bool_owner   параметр-владелец
/// \param bool_index   разрешение/запрещения параметра в зависимости от состояния и типа владельца:
///  - enum: битовая карта элементов из списка - если в enum выбран элемент с единичным битов в маске, параметр разрешен
///  - bool: если 0, то параметр разрешен, когда разрешен bool-владелец; если 1, то наоборот
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param title        заголовок в GUI, не должно быть 0
/// \param description  описание (для отображения), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
/// \param array_size   общий размер массива (максимальное количество элементов)
/// \param array_count  текущее количество заполненных элементов в массиве
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_bool_preference_arr(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description,
                                                                   gboolean_p variable, guint array_size, guint_p array_count);
/// регистрация скрытых параметров
///
/// тип: булевое значение (массив)
///
/// скрытые параметры, в отличие от обычных не будут видны в диалоге настройки параметров, но будут храниться в ini-файле
///
/// \param owner        модуль-родитель
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
/// \param array_size   общий размер массива (максимальное количество элементов)
/// \param array_count  текущее количество заполненных элементов в массиве
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_bool_hidden_preference_arr(preference_p owner, TPref_validator_arr validator, gconstpchar name,
                                                                          gboolean_p variable, guint array_size, guint_p array_count);
//////////////////////////////////////////////////////////////////////////
/// регистрация параметров
///
/// тип: индекс выбора из списка/перечисления
///
/// \param owner        модуль-родитель
/// \param bool_owner   параметр-владелец
/// \param bool_index   разрешение/запрещения параметра в зависимости от состояния и типа владельца:
///  - enum: битовая карта элементов из списка - если в enum выбран элемент с единичным битов в маске, параметр разрешен
///  - bool: если 0, то параметр разрешен, когда разрешен bool-владелец; если 1, то наоборот
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param title        заголовок в GUI, не должно быть 0
/// \param description  описание (для отображения), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
/// \param enumvals     список возможных значений
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_enum_preference(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, gint_p variable, const value_string * enumvals);
/// регистрация скрытых параметров
///
/// тип: индекс выбора из списка/перечисления
///
/// скрытые параметры, в отличие от обычных не будут видны в диалоге настройки параметров, но будут храниться в ini-файле
///
/// \param owner        модуль-родитель
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
/// \param enumvals     список возможных значений
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_enum_hidden_preference(preference_p owner, TPref_validator validator, gconstpchar name, gint_p variable, const value_string * enumvals);
/// регистрация параметров
///
/// тип: индекс выбора из списка/перечисления (массив)
///
/// \param owner        модуль-родитель
/// \param bool_owner   параметр-владелец
/// \param bool_index   разрешение/запрещения параметра в зависимости от состояния и типа владельца:
///  - enum: битовая карта элементов из списка - если в enum выбран элемент с единичным битов в маске, параметр разрешен
///  - bool: если 0, то параметр разрешен, когда разрешен bool-владелец; если 1, то наоборот
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param title        заголовок в GUI, не должно быть 0
/// \param description  описание (для отображения), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
/// \param enumvals     список возможных значений
/// \param array_size   общий размер массива (максимальное количество элементов)
/// \param array_count  текущее количество заполненных элементов в массиве
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_enum_preference_arr(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description,
                                                                   gint_p variable, const value_string * enumvals, guint array_size, guint_p array_count);
/// регистрация скрытых параметров
///
/// тип: индекс выбора из списка/перечисления (массив)
///
/// скрытые параметры, в отличие от обычных не будут видны в диалоге настройки параметров, но будут храниться в ini-файле
///
/// \param owner        модуль-родитель
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
/// \param enumvals     список возможных значений
/// \param array_size   общий размер массива (максимальное количество элементов)
/// \param array_count  текущее количество заполненных элементов в массиве
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_enum_hidden_preference_arr(preference_p owner, TPref_validator_arr validator, gconstpchar name,
                                                                          gint_p variable, const value_string * enumvals, guint array_size, guint_p array_count);

//////////////////////////////////////////////////////////////////////////
/// регистрация параметров
///
/// тип: строковое значение
///
/// \param owner        модуль-родитель
/// \param bool_owner   параметр-владелец
/// \param bool_index   разрешение/запрещения параметра в зависимости от состояния и типа владельца:
///  - enum: битовая карта элементов из списка - если в enum выбран элемент с единичным битов в маске, параметр разрешен
///  - bool: если 0, то параметр разрешен, когда разрешен bool-владелец; если 1, то наоборот
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param title        заголовок в GUI, не должно быть 0
/// \param description  описание (для отображения), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
/// \param variable_size  размер переменной (строкового буфера), в байтах
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_string_preference(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, char * variable, guint variable_size);
/// регистрация скрытых параметров
///
/// тип: строковое значение
///
/// скрытые параметры, в отличие от обычных не будут видны в диалоге настройки параметров, но будут храниться в ini-файле
///
/// \param owner        модуль-родитель
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
/// \param variable_size  размер переменной (строкового буфера), в байтах
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_string_hidden_preference(preference_p owner, TPref_validator validator, gconstpchar name, char * variable, guint variable_size);
/// регистрация параметров
///
/// тип: строковое значение (массив)
///
/// \param owner        модуль-родитель
/// \param bool_owner   параметр-владелец
/// \param bool_index   разрешение/запрещения параметра в зависимости от состояния и типа владельца:
///  - enum: битовая карта элементов из списка - если в enum выбран элемент с единичным битов в маске, параметр разрешен
///  - bool: если 0, то параметр разрешен, когда разрешен bool-владелец; если 1, то наоборот
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param title        заголовок в GUI, не должно быть 0
/// \param description  описание (для отображения), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
/// \param variable_size  размер переменной (строкового буфера), в байтах
/// \param array_size   общий размер массива (максимальное количество элементов)
/// \param array_count  текущее количество заполненных элементов в массиве
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_string_preference_arr(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description,
                                                                     char ** variable, guint variable_size, guint array_size, guint_p array_count);
/// регистрация скрытых параметров
///
/// тип: строковое значение (массив)
///
/// скрытые параметры, в отличие от обычных не будут видны в диалоге настройки параметров, но будут храниться в ini-файле
///
/// \param owner        модуль-родитель
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
/// \param variable_size  размер переменной (строкового буфера), в байтах
/// \param array_size   общий размер массива (максимальное количество элементов)
/// \param array_count  текущее количество заполненных элементов в массиве
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_string_hidden_preference_arr(preference_p owner, TPref_validator_arr validator, gconstpchar name,
                                                                            char ** variable, guint variable_size, guint array_size, guint_p array_count);

//////////////////////////////////////////////////////////////////////////
/// регистрация параметров
///
/// тип: путь/каталог/директория
///
/// \param owner        модуль-родитель
/// \param bool_owner   параметр-владелец
/// \param bool_index   разрешение/запрещения параметра в зависимости от состояния и типа владельца:
///  - enum: битовая карта элементов из списка - если в enum выбран элемент с единичным битов в маске, параметр разрешен
///  - bool: если 0, то параметр разрешен, когда разрешен bool-владелец; если 1, то наоборот
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param title        заголовок в GUI, не должно быть 0
/// \param description  описание (для отображения), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
/// \param variable_size  размер переменной (строкового буфера), в байтах
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_dir_preference(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, char * variable, guint variable_size);
/// регистрация скрытых параметров
///
/// тип: путь/каталог/директория
///
/// скрытые параметры, в отличие от обычных не будут видны в диалоге настройки параметров, но будут храниться в ini-файле
///
/// \param owner        модуль-родитель
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
/// \param variable_size  размер переменной (строкового буфера), в байтах
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_dir_hidden_preference(preference_p owner, TPref_validator validator, gconstpchar name, char * variable, guint variable_size);
/// регистрация параметров
///
/// тип: путь/каталог/директория (массив)
///
/// \param owner        модуль-родитель
/// \param bool_owner   параметр-владелец
/// \param bool_index   разрешение/запрещения параметра в зависимости от состояния и типа владельца:
///  - enum: битовая карта элементов из списка - если в enum выбран элемент с единичным битов в маске, параметр разрешен
///  - bool: если 0, то параметр разрешен, когда разрешен bool-владелец; если 1, то наоборот
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param title        заголовок в GUI, не должно быть 0
/// \param description  описание (для отображения), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
/// \param variable_size  размер переменной (строкового буфера), в байтах
/// \param array_size   общий размер массива (максимальное количество элементов)
/// \param array_count  текущее количество заполненных элементов в массиве
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_dir_preference_arr(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description,
                                                                  char ** variable, guint variable_size, guint array_size, guint_p array_count);
/// регистрация скрытых параметров
///
/// тип: путь/каталог/директория (массив)
///
/// скрытые параметры, в отличие от обычных не будут видны в диалоге настройки параметров, но будут храниться в ini-файле
///
/// \param owner        модуль-родитель
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
/// \param variable_size  размер переменной (строкового буфера), в байтах
/// \param array_size   общий размер массива (максимальное количество элементов)
/// \param array_count  текущее количество заполненных элементов в массиве
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_dir_hidden_preference_arr(preference_p owner, TPref_validator_arr validator, gconstpchar name,
                                                                         char ** variable, guint variable_size, guint array_size, guint_p array_count);

//////////////////////////////////////////////////////////////////////////
/// регистрация параметров
///
/// тип: путь к файлу
///
/// \param owner        модуль-родитель
/// \param bool_owner   параметр-владелец
/// \param bool_index   разрешение/запрещения параметра в зависимости от состояния и типа владельца:
///  - enum: битовая карта элементов из списка - если в enum выбран элемент с единичным битов в маске, параметр разрешен
///  - bool: если 0, то параметр разрешен, когда разрешен bool-владелец; если 1, то наоборот
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param title        заголовок в GUI, не должно быть 0
/// \param description  описание (для отображения), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
/// \param variable_size  размер переменной (строкового буфера), в байтах
/// \param afilter      строковое определение фильтра (типы файлов)
///                     формат: \code <описание|фильтр|описание|фильтр...> \endcode
///                     пример: \code 'Все файлы ( *.* )|*.*...' \endcode
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_file_preference(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, char * variable, guint variable_size, gconstpchar afilter);
/// регистрация скрытых параметров
///
/// тип: путь к файлу
///
/// скрытые параметры, в отличие от обычных не будут видны в диалоге настройки параметров, но будут храниться в ini-файле
///
/// \param owner        модуль-родитель
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
/// \param variable_size  размер переменной (строкового буфера), в байтах
/// \param afilter      строковое определение фильтра (типы файлов)
///                     формат: \code <описание|фильтр|описание|фильтр...> \endcode
///                     пример: \code 'Все файлы ( *.* )|*.*...' \endcode
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_file_hidden_preference(preference_p owner, TPref_validator validator, gconstpchar name, char * variable, guint variable_size, gconstpchar afilter);
/// регистрация параметров
///
/// тип: путь к файлу (массив)
///
/// \param owner        модуль-родитель
/// \param bool_owner   параметр-владелец
/// \param bool_index   разрешение/запрещения параметра в зависимости от состояния и типа владельца:
///  - enum: битовая карта элементов из списка - если в enum выбран элемент с единичным битов в маске, параметр разрешен
///  - bool: если 0, то параметр разрешен, когда разрешен bool-владелец; если 1, то наоборот
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param title        заголовок в GUI, не должно быть 0
/// \param description  описание (для отображения), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
/// \param variable_size  размер переменной (строкового буфера), в байтах
/// \param afilter      строковое определение фильтра (типы файлов)
///                     формат: \code <описание|фильтр|описание|фильтр...> \endcode
///                     пример: \code 'Все файлы ( *.* )|*.*...' \endcode
/// \param array_size   общий размер массива (максимальное количество элементов)
/// \param array_count  текущее количество заполненных элементов в массиве
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_file_preference_arr(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description,
                                                                   char ** variable, guint variable_size, gconstpchar afilter, guint array_size, guint_p array_count);
/// регистрация скрытых параметров
///
/// тип: путь к файлу (массив)
///
/// скрытые параметры, в отличие от обычных не будут видны в диалоге настройки параметров, но будут храниться в ini-файле
///
/// \param owner        модуль-родитель
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
/// \param variable_size  размер переменной (строкового буфера), в байтах
/// \param afilter      строковое определение фильтра (типы файлов)
///                     формат: \code <описание|фильтр|описание|фильтр...> \endcode
///                     пример: \code 'Все файлы ( *.* )|*.*...' \endcode
/// \param array_size   общий размер массива (максимальное количество элементов)
/// \param array_count  текущее количество заполненных элементов в массиве
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_file_hidden_preference_arr(preference_p owner, TPref_validator_arr validator, gconstpchar name,
                                                                          char ** variable, guint variable_size, gconstpchar afilter, guint array_size, guint_p array_count);

//////////////////////////////////////////////////////////////////////////
/// регистрация параметров
///
/// тип: набор строковых значений, разделенных точкой с запятой
///
/// \param owner        модуль-родитель
/// \param bool_owner   параметр-владелец
/// \param bool_index   разрешение/запрещения параметра в зависимости от состояния и типа владельца:
///  - enum: битовая карта элементов из списка - если в enum выбран элемент с единичным битов в маске, параметр разрешен
///  - bool: если 0, то параметр разрешен, когда разрешен bool-владелец; если 1, то наоборот
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param title        заголовок в GUI, не должно быть 0
/// \param description  описание (для отображения), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
/// \param variable_size  размер переменной (строкового буфера), в байтах
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_csv_preference(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, char * variable, guint variable_size);
/// регистрация скрытых параметров
///
/// тип: набор строковых значений, разделенных точкой с запятой
///
/// скрытые параметры, в отличие от обычных не будут видны в диалоге настройки параметров, но будут храниться в ini-файле
///
/// \param owner        модуль-родитель
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
/// \param variable_size  размер переменной (строкового буфера), в байтах
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_csv_hidden_preference(preference_p owner, TPref_validator validator, gconstpchar name, char * variable, guint variable_size);
/// регистрация параметров
///
/// тип: набор строковых значений, разделенных точкой с запятой (массив)
///
/// \param owner        модуль-родитель
/// \param bool_owner   параметр-владелец
/// \param bool_index   разрешение/запрещения параметра в зависимости от состояния и типа владельца:
///  - enum: битовая карта элементов из списка - если в enum выбран элемент с единичным битов в маске, параметр разрешен
///  - bool: если 0, то параметр разрешен, когда разрешен bool-владелец; если 1, то наоборот
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param title        заголовок в GUI, не должно быть 0
/// \param description  описание (для отображения), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
/// \param variable_size  размер переменной (строкового буфера), в байтах
/// \param array_size   общий размер массива (максимальное количество элементов)
/// \param array_count  текущее количество заполненных элементов в массиве
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_csv_preference_arr(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description,
                                                                  char ** variable, guint variable_size, guint array_size, guint_p array_count);
/// регистрация скрытых параметров
///
/// тип: набор строковых значений, разделенных точкой с запятой (массив)
///
/// скрытые параметры, в отличие от обычных не будут видны в диалоге настройки параметров, но будут храниться в ini-файле
///
/// \param owner        модуль-родитель
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
/// \param variable_size  размер переменной (строкового буфера), в байтах
/// \param array_size   общий размер массива (максимальное количество элементов)
/// \param array_count  текущее количество заполненных элементов в массиве
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_csv_hidden_preference_arr(preference_p owner, TPref_validator_arr validator, gconstpchar name,
                                                                         char ** variable, guint variable_size, guint array_size, guint_p array_count);

//////////////////////////////////////////////////////////////////////////
/// регистрация параметров
///
/// тип: многостраничный текст, хранящийся во внешнем файле
///
/// \param owner        модуль-родитель
/// \param bool_owner   параметр-владелец
/// \param bool_index   разрешение/запрещения параметра в зависимости от состояния и типа владельца:
///  - enum: битовая карта элементов из списка - если в enum выбран элемент с единичным битов в маске, параметр разрешен
///  - bool: если 0, то параметр разрешен, когда разрешен bool-владелец; если 1, то наоборот
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param title        заголовок в GUI, не должно быть 0
/// \param description  описание (для отображения), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
/// \param variable_size  размер переменной (строкового буфера), в байтах
/// \param afile_name   имя внешнего файла, используемого для хранения значения параметра. Не должен содержать уточнения пути.
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_text_preference(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, char * variable, guint variable_size, gconstpchar afile_name);
/// регистрация скрытых параметров
///
/// тип: многостраничный текст, хранящийся во внешнем файле
///
/// скрытые параметры, в отличие от обычных не будут видны в диалоге настройки параметров, но будут храниться в ini-файле
///
/// \param owner        модуль-родитель
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
/// \param variable_size  размер переменной (строкового буфера), в байтах
/// \param afile_name   имя внешнего файла, используемого для хранения значения параметра. Не должен содержать уточнения пути.
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_text_hidden_preference(preference_p owner, TPref_validator validator, gconstpchar name, char * variable, guint variable_size, gconstpchar afile_name);
/// регистрация параметров
///
/// тип: многостраничный текст, хранящийся во внешнем файле (массив)
///
/// \param owner        модуль-родитель
/// \param bool_owner   параметр-владелец
/// \param bool_index   разрешение/запрещения параметра в зависимости от состояния и типа владельца:
///  - enum: битовая карта элементов из списка - если в enum выбран элемент с единичным битов в маске, параметр разрешен
///  - bool: если 0, то параметр разрешен, когда разрешен bool-владелец; если 1, то наоборот
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param title        заголовок в GUI, не должно быть 0
/// \param description  описание (для отображения), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
/// \param variable_size  размер переменной (строкового буфера), в байтах
/// \param afile_name   имя внешнего файла, используемого для хранения значения параметра. Не должен содержать уточнения пути.
/// \param array_size   общий размер массива (максимальное количество элементов)
/// \param array_count  текущее количество заполненных элементов в массиве
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_text_preference_arr(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description,
                                                                   char ** variable, guint variable_size, gconstpchar afile_name, guint array_size, guint_p array_count);
/// регистрация скрытых параметров
///
/// тип: многостраничный текст, хранящийся во внешнем файле (массив)
///
/// скрытые параметры, в отличие от обычных не будут видны в диалоге настройки параметров, но будут храниться в ini-файле
///
/// \param owner        модуль-родитель
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
/// \param variable_size  размер переменной (строкового буфера), в байтах
/// \param afile_name   имя внешнего файла, используемого для хранения значения параметра. Не должен содержать уточнения пути.
/// \param array_size   общий размер массива (максимальное количество элементов)
/// \param array_count  текущее количество заполненных элементов в массиве
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_text_hidden_preference_arr(preference_p owner, TPref_validator_arr validator, gconstpchar name,
                                                                          char ** variable, guint variable_size, gconstpchar afile_name, guint array_size, guint_p array_count);

//////////////////////////////////////////////////////////////////////////
/// регистрация параметров
///
/// тип: диалог, уже зарегистрированный в системе
///
/// \param owner        модуль-родитель
/// \param bool_owner   параметр-владелец
/// \param bool_index   разрешение/запрещения параметра в зависимости от состояния и типа владельца:
///  - enum: битовая карта элементов из списка - если в enum выбран элемент с единичным битов в маске, параметр разрешен
///  - bool: если 0, то параметр разрешен, когда разрешен bool-владелец; если 1, то наоборот
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param title        заголовок в GUI, не должно быть 0
/// \param description  описание (для отображения), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
/// \param readonly триггер возможности изменения
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_dialog_preference(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, preference_p variable, gboolean_p readonly);
/// регистрация параметров
///
/// тип: внешний диалог
///
/// \param owner        модуль-родитель
/// \param bool_owner   параметр-владелец
/// \param bool_index   разрешение/запрещения параметра в зависимости от состояния и типа владельца:
///  - enum: битовая карта элементов из списка - если в enum выбран элемент с единичным битов в маске, параметр разрешен
///  - bool: если 0, то параметр разрешен, когда разрешен bool-владелец; если 1, то наоборот
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param title        заголовок в GUI, не должно быть 0
/// \param description  описание (для отображения), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
/// \param user_data    пользовательские данные, передаваемые в качестве параметра при вызове variable
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_alien_dialog_preference(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, Talien_dialog_executor variable, gpointer user_data, gboolean_p readonly);
/// регистрация параметров
///
/// тип: плагин
///
/// \param owner        модуль-родитель
/// \param bool_owner   параметр-владелец
/// \param bool_index   разрешение/запрещения параметра в зависимости от состояния и типа владельца:
///  - enum: битовая карта элементов из списка - если в enum выбран элемент с единичным битов в маске, параметр разрешен
///  - bool: если 0, то параметр разрешен, когда разрешен bool-владелец; если 1, то наоборот
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param title        заголовок в GUI, не должно быть 0
/// \param description  описание (для отображения), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
/// \param dialog       внешний диалог, вызываемй для настройки параметров плагина
/// \param user_data    пользовательские данные, передаваемые в качестве параметра при вызове dialog
///
/// \return адрес на экземпляр созданного параметра (или старого, если параметр с таким имененм уже существует)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_plug_preference(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, gboolean_p variable, Talien_dialog_executor dialog, gpointer user_data);
//#endif

//////////////////////////////////////////////////////////////////////////
/// отмена регистрации диалога
///
/// \param name         внутреннее имя диалога
///
extern "C" PREFS_API void MSCU_CALL_PREFIX prefs_unregister_dialog(gconstpchar name);

/// отмена регистрации модуля
///
/// \param owner    модуль-родитель (NULL - если нужно разместить в корне)
/// \param name     внутреннее имя модуля
///
extern "C" PREFS_API void MSCU_CALL_PREFIX prefs_unregister_module(preference_p owner, gconstpchar name);

/// отмена регистрации параметра
///
/// \param owner        модуль-родитель
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
///
extern "C" PREFS_API void MSCU_CALL_PREFIX prefs_unregister_preference(preference_p owner, gconstpchar name);

/// установка xml-режима файлового ввода/вывода
/// установить режим работы load/save-функций
/// если xml-режим включен, формат файлов - XML
/// если xml-режим выключен, формат файлов - INI
///
/// по-умолчанию xml-режим выключен
///
/// \param xml_mode_active активность xml-режима
///
extern "C" PREFS_API void MSCU_CALL_PREFIX prefs_set_xml_mode(gboolean xml_mode_active);

/// загрузка параметров из файла
/// эксклюзивные диалоги исключаются из обработки
/// file_name не может быть равен 0 или ""
///
/// \param file_name имя файла
///
extern "C" PREFS_API gboolean MSCU_CALL_PREFIX prefs_load_from_file(gconstpchar file_name);
/// загрузка параметров определенного диалога из файла
/// file_name не может быть равен 0 или ""
///
/// \param file_name    имя файла
/// \param[in] dialog_p диалог
///
extern "C" PREFS_API gboolean MSCU_CALL_PREFIX prefs_load_from_file_dlg(gconstpchar file_name, preference_p dialog_p);
/// сохранение параметров в файл
/// эксклюзивные диалоги исключаются из обработки
/// file_name не может быть равен 0 или ""
///
/// \param file_name имя файла
///
extern "C" PREFS_API gboolean MSCU_CALL_PREFIX prefs_save_to_file(gconstpchar file_name);
/// сохранение параметров определенного диалога в файл
/// file_name не может быть равен 0 или ""
///
/// \param file_name    имя файла
/// \param[in] dialog_p диалог
///
extern "C" PREFS_API gboolean MSCU_CALL_PREFIX prefs_save_to_file_dlg(gconstpchar file_name, preference_p dialog_p);

/// запуск диалогового окна изменения параметров
/// возвращает true, если хотя бы одно значение было изменено
///
/// \param dialog_p диалог
///
extern "C" PREFS_API gboolean MSCU_CALL_PREFIX prefs_params_dlg(preference_p dialog_p);

/// режим консольного диалогового окна изменения параметров
#define PREFS_TERMINAL_MODE_DEFAULT		0  ///< по-умолчанию
#define PREFS_TERMINAL_MODE_DIALOG		1  ///< dialog (dialog.exe)
#define PREFS_TERMINAL_MODE_WHIPTAIL	2  ///< newt whiptail

/// запуск консольного диалогового окна изменения параметров
/// возвращает true, если хотя бы одно значение было изменено
///
/// \param mode режим работы (константа PREFS_TERMINAL_MODE_XXX)
/// \param dialog_p диалог
extern "C" PREFS_API gboolean MSCU_CALL_PREFIX prefs_params_terminal_dlg(gint mode, preference_p dialog_p);
///

/// синхронизация
/// захват доступа к параметрам
extern "C" PREFS_API void MSCU_CALL_PREFIX prefs_lock();
/// синхронизация
/// освобождение доступа к параметрам
extern "C" PREFS_API void MSCU_CALL_PREFIX prefs_unlock();

/// генерация документации в файл
/// file_name не может быть равен 0 или ""
///
/// \param file_name имя файла для генерации
///
extern "C" PREFS_API gboolean MSCU_CALL_PREFIX prefs_generate_documentation(gconstpchar file_name);

/// \name функции сортировки
/// \{

///
/// \return адрес на экземпляр параметра
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_set_sorted_prefs(preference_p preference, gboolean value);
///
/// \return адрес на экземпляр параметра
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_set_pref_index(preference_p preference, preference_p value);
///
/// \return адрес на экземпляр параметра
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_set_update_index(preference_p preference, Tindex_executor value);
///
/// \return адрес на экземпляр параметра
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_set_update_index_user_data(preference_p preference, gpointer value);

/// \}

/// \name другие функции
/// \{

/// установка принадлежности параметра к экспертным настройкам
///
/// \param[in] value значение флага принадлежности: 0 - не экспертная настройка, не 0 - экспертная настройка
///
/// \return адрес на экземпляр параметра
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_set_expert(preference_p preference, gboolean value);

/// установка тэгов области видимости
///
/// \param[in] tags список тэгов областей видимости, к которым принадлежит параметр (тэги разделяются между собой знаком "точка с запятой")
///
/// \return адрес на экземпляр параметра
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_set_tags(preference_p preference, gconstpchar tags);

/// \}

/// \name установка пределов значений
/// \{

/// установка минимального значения включительно (>= value)
///
/// \return адрес на экземпляр параметра (preference)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_set_min_uint(preference_p preference, guint value);

/// установка максимального значения включительно (<= value)
///
/// \return адрес на экземпляр параметра (preference)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_set_max_uint(preference_p preference, guint value);

/// установка минимального значения включительно (>= value)
///
/// \return адрес на экземпляр параметра (preference)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_set_min_int64(preference_p preference, gint64 value);

/// установка максимального значения включительно (<= value)
///
/// \return адрес на экземпляр параметра (preference)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_set_max_int64(preference_p preference, gint64 value);

/// установка минимального значения включительно (>= value)
///
/// \return адрес на экземпляр параметра (preference)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_set_min_double(preference_p preference, gdouble value);

/// установка максимального значения включительно (<= value)
///
/// \return адрес на экземпляр параметра (preference)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_set_max_double(preference_p preference, gdouble value);

/// установка минимального значения включительно (>= value)
///
/// \return адрес на экземпляр параметра (preference)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_set_min_enum(preference_p preference, gint value);

/// установка максимального значения включительно (<= value)
///
/// \return адрес на экземпляр параметра (preference)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_set_max_enum(preference_p preference, gint value);

/// \}

/// \name функции получения значений из валидатора
/// \{

/// получение значения
///
extern "C" PREFS_API char * MSCU_CALL_PREFIX prefs_get_var_string(preference_p preference);
/// получение размера строкового буфера
///
extern "C" PREFS_API guint MSCU_CALL_PREFIX prefs_get_var_string_size(preference_p preference);

/// получение значения
///
extern "C" PREFS_API guint_p MSCU_CALL_PREFIX prefs_get_var_uint(preference_p preference);

/// получение значения
///
extern "C" PREFS_API guint_p MSCU_CALL_PREFIX prefs_get_var_msec(preference_p preference);

/// получение значения
///
extern "C" PREFS_API gint64_p MSCU_CALL_PREFIX prefs_get_var_int64(preference_p preference);

/// получение значения
///
extern "C" PREFS_API gdouble_p MSCU_CALL_PREFIX prefs_get_var_double(preference_p preference);

/// получение значения
///
extern "C" PREFS_API gboolean_p MSCU_CALL_PREFIX prefs_get_var_bool(preference_p preference);

/// получение значения
///
extern "C" PREFS_API gint_p MSCU_CALL_PREFIX prefs_get_var_enum(preference_p preference);

/// получение максимального количества элементов (массив)
///
extern "C" PREFS_API guint MSCU_CALL_PREFIX prefs_get_var_size_arr(preference_p preference);

/// получение текущего количества элементов (массив)
///
extern "C" PREFS_API guint_p MSCU_CALL_PREFIX prefs_get_var_count_arr(preference_p preference);

/// получение значения (массив)
///
extern "C" PREFS_API char * MSCU_CALL_PREFIX prefs_get_var_string_arr(preference_p preference, guint index);

/// получение значения (массив)
///
extern "C" PREFS_API guint_p MSCU_CALL_PREFIX prefs_get_var_uint_arr(preference_p preference, guint index);

/// получение значения (массив)
///
extern "C" PREFS_API guint_p MSCU_CALL_PREFIX prefs_get_var_msec_arr(preference_p preference, guint index);

/// получение значения (массив)
///
extern "C" PREFS_API gint64_p MSCU_CALL_PREFIX prefs_get_var_int64_arr(preference_p preference, guint index);

/// получение значения (массив)
///
extern "C" PREFS_API gdouble_p MSCU_CALL_PREFIX prefs_get_var_double_arr(preference_p preference, guint index);

/// получение значения (массив)
///
extern "C" PREFS_API gboolean_p MSCU_CALL_PREFIX prefs_get_var_bool_arr(preference_p preference, guint index);

/// получение значения (массив)
///
extern "C" PREFS_API gint_p MSCU_CALL_PREFIX prefs_get_var_enum_arr(preference_p preference, guint index);

/// \}

/// \name поиск
/// \{

/// поиск параметра по имени
/// поиск ведется рекурсивно по всей структуре вложенности, начиная с owner
///
/// \param owner      модуль-родитель - стартовая позиция поиска (NULL - если нужно искать с корня)
/// \param name       внутреннее имя параметра (краткое или полное)
/// \param full_name  0  - в name содержится краткое имя внутри модуля-владельца (часть значения полного имени после последней точки)
///                   !0 - в name содержится полное имя (как задано в описании в диалоге либо <имя_ini_секции>.<краткое_имя>)
///
/// \return адрес на экземпляр найденного параметра (preference) или 0 в случае неудачного поиска
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_find_preference(preference_p owner, gconstpchar name, gboolean full_path);

///\}

///\}

#endif
