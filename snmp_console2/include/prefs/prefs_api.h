/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
///!!! Внимание! Данный файл считается устаревшим. Используйте prefs.h вместо него. !!!
/// \file prefs_api.h
/// \mainpage
/// @{
/// \section attention Предупреждение
/// \b ВНИМАНИЕ! Файл <b>"prefs_api.h"</b> распространяется под авторским правом РАЗРАБОТЧИКА данного файла.
/// Любые изменения в данном файле СТОРОННИМИ разработчиками НЕДОПУСТИМЫ.
/// Для использования данного файла просто включите его в проект с помощью директивы #include.
/// 
/// \section updated Последнее обновление
/// <b>2009-04-17</b>
/// 
/// \section changelog Изменения
/// - 2009-04-17 - разработка
/// 
/// \section description Описание
/// Данный документ содержит API модуля обработки настроек.
/// 
/// \section copyright Авторские права
/// Copyright (C) MSC, ORG 2002-2009
/// 
/// @}

#pragma once

#ifndef PREFS_API_H
/// \cond
#define PREFS_API_H
/// \endcond

/* дополнительные директивы копиляции:
 *
 *   PREFS_NO_GUI - не использовать GUI-диалоги
 *
 */

#ifndef PREFS_NO_GUI
/// \cond
#define PREFS_GUI
/// \endcond
#endif

#include <mscu_types.h>

/// Размер строкового буфера, предназначенного для хранения имен файлов и т.д. Задается в байтах
#define PREFS_MAX_PATH 4096

typedef gpointer preference_p;

/// режим вызова валидатора параметра (action)
#define vaCorrect 0  ///< проверка и коррекция, применение
#define vaVerify  1  ///< проверка на правильность (временные значения)
#define vaApply   2  ///< применение (без вывода ошибки)

/// \name Валидаторы
/// \{

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

#ifdef PREFS_GUI
/// вызов внешнего диалога 
typedef gboolean (MSCU_CALL_PREFIX * Talien_dialog_executor)(gpointer user_data);
#endif

/// вызов функции обновления индекса
typedef void (MSCU_CALL_PREFIX * Tindex_executor)(gpointer user_data);

/// регистрация диалога
///
/// \param name         внутреннее имя диалога
/// \param title        заголовок в GUI
/// \param description  описание диалога
/// \param readonly     триггер возможности изменения
///
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_dialog)(gconstpchar name, gconstpchar title, gconstpchar description, gboolean_p readonly);

/// регистрация модуля
///
/// \param owner    модуль-родитель (NULL - если нужно разместить в корне)
/// \param name     внутреннее имя модуля
/// \param title    заголовок в GUI
/// \param index    позиция внутри родителя
/// \param readonly триггер возможности изменения
///
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_module)(preference_p owner, gconstpchar name, gconstpchar title, gconstpchar description, gint index, gboolean_p readonly);

/// регистрация параметров
///
/// тип: целое без знака
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
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_uint_preference)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, guint_p variable);
/// регистрация скрытых параметров
///
/// тип: целое без знака
///
/// скрытые параметры, в отличие от обычных не будут видны в диалоге настройки параметров, но будут храниться в ini-файле
///
/// \param owner        модуль-родитель
/// \param validator    функция, вызываемая для проверки/применения/корректировки значения параметра. Может быть равна 0.
/// \param name         внутреннее имя (для ini-файла), не должно быть 0
/// \param variable     адрес на переменную со значением соответствующего типа, не должно быть 0
///
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_uint_hidden_preference)(preference_p owner, TPref_validator validator, gconstpchar name, guint_p variable);
/// регистрация параметров
///
/// тип: целое без знака (массив)
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
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_uint_preference_arr)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description, guint_p variable, guint array_size, guint_p array_count);
/// регистрация скрытых параметров
///
/// тип: целое без знака (массив)
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
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_uint_hidden_preference_arr)(preference_p owner, TPref_validator_arr validator, gconstpchar name, guint_p variable, guint array_size, guint_p array_count);

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
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_double_preference)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, gdouble_p variable);
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
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_double_hidden_preference)(preference_p owner, TPref_validator validator, gconstpchar name, gdouble_p variable);
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
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_double_preference_arr)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description, gdouble_p variable, guint array_size, guint_p array_count);
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
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_double_hidden_preference_arr)(preference_p owner, TPref_validator_arr validator, gconstpchar name, gdouble_p variable, guint array_size, guint_p array_count);

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
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_bool_preference)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, gboolean_p variable);
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
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_bool_hidden_preference)(preference_p owner, TPref_validator validator, gconstpchar name, gboolean_p variable);
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
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_bool_preference_arr)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description, gboolean_p variable, guint array_size, guint_p array_count);
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
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_bool_hidden_preference_arr)(preference_p owner, TPref_validator_arr validator, gconstpchar name, gboolean_p variable, guint array_size, guint_p array_count);

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
///
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_enum_preference)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, gint_p variable, const value_string * enumvals);
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
///
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_enum_hidden_preference)(preference_p owner, TPref_validator validator, gconstpchar name, gint_p variable, const value_string * enumvals);
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
/// \param array_size   общий размер массива (максимальное количество элементов)
/// \param array_count  текущее количество заполненных элементов в массиве
///
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_enum_preference_arr)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description, gint_p variable, const value_string * enumvals, guint array_size, guint_p array_count);
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
/// \param array_size   общий размер массива (максимальное количество элементов)
/// \param array_count  текущее количество заполненных элементов в массиве
///
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_enum_hidden_preference_arr)(preference_p owner, TPref_validator_arr validator, gconstpchar name, gint_p variable, const value_string * enumvals, guint array_size, guint_p array_count);

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
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_string_preference)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, char * variable, guint variable_size);
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
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_string_hidden_preference)(preference_p owner, TPref_validator validator, gconstpchar name, char * variable, guint variable_size);
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
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_string_preference_arr)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description, char ** variable, guint variable_size, guint array_size, guint_p array_count);
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
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_string_hidden_preference_arr)(preference_p owner, TPref_validator_arr validator, gconstpchar name, char ** variable, guint variable_size, guint array_size, guint_p array_count);

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
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_dir_preference)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, char * variable, guint variable_size);
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
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_dir_hidden_preference)(preference_p owner, TPref_validator validator, gconstpchar name, char * variable, guint variable_size);
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
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_dir_preference_arr)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description, char ** variable, guint variable_size, guint array_size, guint_p array_count);
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
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_dir_hidden_preference_arr)(preference_p owner, TPref_validator_arr validator, gconstpchar name, char ** variable, guint variable_size, guint array_size, guint_p array_count);

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
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_file_preference)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, char * variable, guint variable_size, gconstpchar afilter);
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
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_file_hidden_preference)(preference_p owner, TPref_validator validator, gconstpchar name, char * variable, guint variable_size, gconstpchar afilter);
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
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_file_preference_arr)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description, char ** variable, guint variable_size, gconstpchar afilter, guint array_size, guint_p array_count);
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
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_file_hidden_preference_arr)(preference_p owner, TPref_validator_arr validator, gconstpchar name, char ** variable, guint variable_size, gconstpchar afilter, guint array_size, guint_p array_count);

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
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_csv_preference)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, char * variable, guint variable_size);
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
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_csv_hidden_preference)(preference_p owner, TPref_validator validator, gconstpchar name, char * variable, guint variable_size);
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
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_csv_preference_arr)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description, char ** variable, guint variable_size, guint array_size, guint_p array_count);
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
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_csv_hidden_preference_arr)(preference_p owner, TPref_validator_arr validator, gconstpchar name, char ** variable, guint variable_size, guint array_size, guint_p array_count);

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
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_text_preference)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, char * variable, guint variable_size, gconstpchar afile_name);
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
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_text_hidden_preference)(preference_p owner, TPref_validator validator, gconstpchar name, char * variable, guint variable_size, gconstpchar afile_name);
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
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_text_preference_arr)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description, char ** variable, guint variable_size, gconstpchar afile_name, guint array_size, guint_p array_count);
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
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_text_hidden_preference_arr)(preference_p owner, TPref_validator_arr validator, gconstpchar name, char ** variable, guint variable_size, gconstpchar afile_name, guint array_size, guint_p array_count);

#ifdef PREFS_GUI
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
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_dialog_preference)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, preference_p variable, gboolean_p readonly);
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
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_alien_dialog_preference)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, Talien_dialog_executor variable, gpointer user_data, gboolean_p readonly);

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
/// \return адрес на экземпляр созданного параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_plug_preference)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, gboolean_p variable, Talien_dialog_executor dialog, gpointer user_data);
#endif

/// загрузка параметров из файла
/// эксклюзивные диалоги исключаются из обработки
/// file_name не может быть равен 0 или ""
///
/// \param file_name имя файла
///
typedef gboolean (MSCU_CALL_PREFIX * Tprefs_load_from_file)(gconstpchar file_name);

/// загрузка параметров определенного диалога из файла
/// file_name не может быть равен 0 или ""
///
/// \param file_name имя файла
///
typedef gboolean (MSCU_CALL_PREFIX * Tprefs_load_from_file_dlg)(gconstpchar file_name, preference_p dialog_p);

/// сохранение параметров в файл
/// эксклюзивные диалоги исключаются из обработки
/// file_name не может быть равен 0 или ""
///
/// \param file_name имя файла
///
typedef gboolean (MSCU_CALL_PREFIX * Tprefs_save_to_file)(gconstpchar file_name);
/// сохранение параметров определенного диалога в файл
/// file_name не может быть равен 0 или ""
///
/// \param file_name имя файла
///
typedef gboolean (MSCU_CALL_PREFIX * Tprefs_save_to_file_dlg)(gconstpchar file_name, preference_p dialog_p);

#ifdef PREFS_GUI
/// запуск диалогового окна изменения параметров
/// возвращает true, если хотя бы одно значение было изменено
///
/// \param dialog_p диалог
///
typedef gboolean (MSCU_CALL_PREFIX * Tprefs_params_dlg)(preference_p dialog_p);
#endif

/// синхронизация 
/// захват доступа к параметрам
typedef void (MSCU_CALL_PREFIX * Tprefs_lock)(); 

/// синхронизация
/// освобождение доступа к параметрам
typedef void (MSCU_CALL_PREFIX * Tprefs_unlock)(); 

/// генерация документации в файл
/// file_name не может быть равен 0 или ""
/// 
/// \param file_name имя файла для генерации
///
typedef gboolean (MSCU_CALL_PREFIX * Tprefs_generate_documentation)(gconstpchar file_name);

/// зафиксировать определенный диалог как не входящий в общую группу загрузки/сохранения
/// установить/снять флаг "эксклюзивный диалог"
///
/// \return адрес на экземпляр параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_set_exclusive_dialog)(preference_p dialog_p, gboolean value);

/// \name функции сортировки
/// \{

///
/// \return адрес на экземпляр параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_set_sorted_prefs)(preference_p preference, gboolean value);
///
/// \return адрес на экземпляр параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_set_pref_index)(preference_p preference, preference_p value);
///
/// \return адрес на экземпляр параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_set_update_index)(preference_p preference, Tindex_executor value);
///
/// \return адрес на экземпляр параметра
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_set_update_index_user_data)(preference_p preference, gpointer value);

/// \}

/// \name функции получения значений из валидатора
/// \{

/// получение значения
///
typedef char * (MSCU_CALL_PREFIX * Tprefs_get_var_string)(preference_p preference);
/// получение размера строкового буфера
///
typedef guint (MSCU_CALL_PREFIX * Tprefs_get_var_string_size)(preference_p preference);

/// получение значения
///
typedef guint_p (MSCU_CALL_PREFIX * Tprefs_get_var_uint)(preference_p preference);

/// получение значения
///
typedef gdouble_p (MSCU_CALL_PREFIX * Tprefs_get_var_double)(preference_p preference);

/// получение значения
///
typedef gboolean_p (MSCU_CALL_PREFIX * Tprefs_get_var_bool)(preference_p preference);

/// получение значения
///
typedef gint_p (MSCU_CALL_PREFIX * Tprefs_get_var_enum)(preference_p preference);

/// получение максимального количества элементов (массив)
///
typedef guint (MSCU_CALL_PREFIX * Tprefs_get_var_size_arr)(preference_p preference);

/// получение текущего количества элементов (массив)
///
typedef guint_p (MSCU_CALL_PREFIX * Tprefs_get_var_count_arr)(preference_p preference);

/// получение значения (массив)
///
typedef char * (MSCU_CALL_PREFIX * Tprefs_get_var_string_arr)(preference_p preference, guint index);

/// получение значения (массив)
///
typedef guint_p (MSCU_CALL_PREFIX * Tprefs_get_var_uint_arr)(preference_p preference, guint index);

/// получение значения (массив)
///
typedef gdouble_p (MSCU_CALL_PREFIX * Tprefs_get_var_double_arr)(preference_p preference, guint index);

/// получение значения (массив)
///
typedef gboolean_p (MSCU_CALL_PREFIX * Tprefs_get_var_bool_arr)(preference_p preference, guint index);

/// получение значения (массив)
///
typedef gint_p (MSCU_CALL_PREFIX * Tprefs_get_var_enum_arr)(preference_p preference, guint index);

/// \}
#endif