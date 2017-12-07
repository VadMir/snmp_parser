/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
///!!! ��������! ������ ���� ��������� ����������. ����������� prefs.h ������ ����. !!!
/// \file prefs_api.h
/// \mainpage
/// @{
/// \section attention ��������������
/// \b ��������! ���� <b>"prefs_api.h"</b> ���������������� ��� ��������� ������ ������������ ������� �����.
/// ����� ��������� � ������ ����� ���������� �������������� �����������.
/// ��� ������������� ������� ����� ������ �������� ��� � ������ � ������� ��������� #include.
/// 
/// \section updated ��������� ����������
/// <b>2009-04-17</b>
/// 
/// \section changelog ���������
/// - 2009-04-17 - ����������
/// 
/// \section description ��������
/// ������ �������� �������� API ������ ��������� ��������.
/// 
/// \section copyright ��������� �����
/// Copyright (C) MSC, ORG 2002-2009
/// 
/// @}

#pragma once

#ifndef PREFS_API_H
/// \cond
#define PREFS_API_H
/// \endcond

/* �������������� ��������� ���������:
 *
 *   PREFS_NO_GUI - �� ������������ GUI-�������
 *
 */

#ifndef PREFS_NO_GUI
/// \cond
#define PREFS_GUI
/// \endcond
#endif

#include <mscu_types.h>

/// ������ ���������� ������, ���������������� ��� �������� ���� ������ � �.�. �������� � ������
#define PREFS_MAX_PATH 4096

typedef gpointer preference_p;

/// ����� ������ ���������� ��������� (action)
#define vaCorrect 0  ///< �������� � ���������, ����������
#define vaVerify  1  ///< �������� �� ������������ (��������� ��������)
#define vaApply   2  ///< ���������� (��� ������ ������)

/// \name ����������
/// \{

/// ��������� ��������� (�������)
/// 
/// \return 0 ��� ������� ����������
/// \return ����� ������� �������� ������ (��� vaCorrect, vaVerify)
/// 
typedef gconstpchar (MSCU_CALL_PREFIX * TPref_validator)(preference_p preference, gint action);

/// ��������� ��������� (��� ��������� �������)
/// 
/// \return 0 ��� ������� ����������
/// \return ����� ������� �������� ������ (��� vaCorrect, vaVerify)
/// 
typedef gconstpchar (MSCU_CALL_PREFIX * TPref_validator_arr)(preference_p preference, gint action, guint index);

/// \}

#ifdef PREFS_GUI
/// ����� �������� ������� 
typedef gboolean (MSCU_CALL_PREFIX * Talien_dialog_executor)(gpointer user_data);
#endif

/// ����� ������� ���������� �������
typedef void (MSCU_CALL_PREFIX * Tindex_executor)(gpointer user_data);

/// ����������� �������
///
/// \param name         ���������� ��� �������
/// \param title        ��������� � GUI
/// \param description  �������� �������
/// \param readonly     ������� ����������� ���������
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_dialog)(gconstpchar name, gconstpchar title, gconstpchar description, gboolean_p readonly);

/// ����������� ������
///
/// \param owner    ������-�������� (NULL - ���� ����� ���������� � �����)
/// \param name     ���������� ��� ������
/// \param title    ��������� � GUI
/// \param index    ������� ������ ��������
/// \param readonly ������� ����������� ���������
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_module)(preference_p owner, gconstpchar name, gconstpchar title, gconstpchar description, gint index, gboolean_p readonly);

/// ����������� ����������
///
/// ���: ����� ��� �����
///
/// \param owner        ������-��������
/// \param bool_owner   ��������-��������
/// \param bool_index   ����������/���������� ��������� � ����������� �� ��������� � ���� ���������:
///  - enum: ������� ����� ��������� �� ������ - ���� � enum ������ ������� � ��������� ����� � �����, �������� ��������
///  - bool: ���� 0, �� �������� ��������, ����� �������� bool-��������; ���� 1, �� ��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param title        ��������� � GUI, �� ������ ���� 0
/// \param description  �������� (��� �����������), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_uint_preference)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, guint_p variable);
/// ����������� ������� ����������
///
/// ���: ����� ��� �����
///
/// ������� ���������, � ������� �� ������� �� ����� ����� � ������� ��������� ����������, �� ����� ��������� � ini-�����
///
/// \param owner        ������-��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_uint_hidden_preference)(preference_p owner, TPref_validator validator, gconstpchar name, guint_p variable);
/// ����������� ����������
///
/// ���: ����� ��� ����� (������)
///
/// \param owner        ������-��������
/// \param bool_owner   ��������-��������
/// \param bool_index   ����������/���������� ��������� � ����������� �� ��������� � ���� ���������:
///  - enum: ������� ����� ��������� �� ������ - ���� � enum ������ ������� � ��������� ����� � �����, �������� ��������
///  - bool: ���� 0, �� �������� ��������, ����� �������� bool-��������; ���� 1, �� ��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param title        ��������� � GUI, �� ������ ���� 0
/// \param description  �������� (��� �����������), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
/// \param array_size   ����� ������ ������� (������������ ���������� ���������)
/// \param array_count  ������� ���������� ����������� ��������� � �������
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_uint_preference_arr)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description, guint_p variable, guint array_size, guint_p array_count);
/// ����������� ������� ����������
///
/// ���: ����� ��� ����� (������)
///
/// ������� ���������, � ������� �� ������� �� ����� ����� � ������� ��������� ����������, �� ����� ��������� � ini-�����
///
/// \param owner        ������-��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
/// \param array_size   ����� ������ ������� (������������ ���������� ���������)
/// \param array_count  ������� ���������� ����������� ��������� � �������
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_uint_hidden_preference_arr)(preference_p owner, TPref_validator_arr validator, gconstpchar name, guint_p variable, guint array_size, guint_p array_count);

/// ����������� ����������
///
/// ���: ����� � ��������� ������ ������� ��������
///
/// \param owner        ������-��������
/// \param bool_owner   ��������-��������
/// \param bool_index   ����������/���������� ��������� � ����������� �� ��������� � ���� ���������:
///  - enum: ������� ����� ��������� �� ������ - ���� � enum ������ ������� � ��������� ����� � �����, �������� ��������
///  - bool: ���� 0, �� �������� ��������, ����� �������� bool-��������; ���� 1, �� ��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param title        ��������� � GUI, �� ������ ���� 0
/// \param description  �������� (��� �����������), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_double_preference)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, gdouble_p variable);
/// ����������� ������� ����������
///
/// ���: ����� � ��������� ������ ������� ��������
///
/// ������� ���������, � ������� �� ������� �� ����� ����� � ������� ��������� ����������, �� ����� ��������� � ini-�����
///
/// \param owner        ������-��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_double_hidden_preference)(preference_p owner, TPref_validator validator, gconstpchar name, gdouble_p variable);
/// ����������� ����������
///
/// ���: ����� � ��������� ������ ������� �������� (������)
///
/// \param owner        ������-��������
/// \param bool_owner   ��������-��������
/// \param bool_index   ����������/���������� ��������� � ����������� �� ��������� � ���� ���������:
///  - enum: ������� ����� ��������� �� ������ - ���� � enum ������ ������� � ��������� ����� � �����, �������� ��������
///  - bool: ���� 0, �� �������� ��������, ����� �������� bool-��������; ���� 1, �� ��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param title        ��������� � GUI, �� ������ ���� 0
/// \param description  �������� (��� �����������), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
/// \param array_size   ����� ������ ������� (������������ ���������� ���������)
/// \param array_count  ������� ���������� ����������� ��������� � �������
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_double_preference_arr)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description, gdouble_p variable, guint array_size, guint_p array_count);
/// ����������� ������� ����������
///
/// ���: ����� � ��������� ������ ������� �������� (������)
///
/// ������� ���������, � ������� �� ������� �� ����� ����� � ������� ��������� ����������, �� ����� ��������� � ini-�����
///
/// \param owner        ������-��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
/// \param array_size   ����� ������ ������� (������������ ���������� ���������)
/// \param array_count  ������� ���������� ����������� ��������� � �������
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_double_hidden_preference_arr)(preference_p owner, TPref_validator_arr validator, gconstpchar name, gdouble_p variable, guint array_size, guint_p array_count);

/// ����������� ����������
///
/// ���: ������� ��������
///
/// \param owner        ������-��������
/// \param bool_owner   ��������-��������
/// \param bool_index   ����������/���������� ��������� � ����������� �� ��������� � ���� ���������:
///  - enum: ������� ����� ��������� �� ������ - ���� � enum ������ ������� � ��������� ����� � �����, �������� ��������
///  - bool: ���� 0, �� �������� ��������, ����� �������� bool-��������; ���� 1, �� ��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param title        ��������� � GUI, �� ������ ���� 0
/// \param description  �������� (��� �����������), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_bool_preference)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, gboolean_p variable);
/// ����������� ������� ����������
///
/// ���: ������� ��������
///
/// ������� ���������, � ������� �� ������� �� ����� ����� � ������� ��������� ����������, �� ����� ��������� � ini-�����
///
/// \param owner        ������-��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_bool_hidden_preference)(preference_p owner, TPref_validator validator, gconstpchar name, gboolean_p variable);
/// ����������� ����������
///
/// ���: ������� �������� (������)
///
/// \param owner        ������-��������
/// \param bool_owner   ��������-��������
/// \param bool_index   ����������/���������� ��������� � ����������� �� ��������� � ���� ���������:
///  - enum: ������� ����� ��������� �� ������ - ���� � enum ������ ������� � ��������� ����� � �����, �������� ��������
///  - bool: ���� 0, �� �������� ��������, ����� �������� bool-��������; ���� 1, �� ��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param title        ��������� � GUI, �� ������ ���� 0
/// \param description  �������� (��� �����������), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
/// \param array_size   ����� ������ ������� (������������ ���������� ���������)
/// \param array_count  ������� ���������� ����������� ��������� � �������
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_bool_preference_arr)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description, gboolean_p variable, guint array_size, guint_p array_count);
/// ����������� ������� ����������
///
/// ���: ������� �������� (������)
///
/// ������� ���������, � ������� �� ������� �� ����� ����� � ������� ��������� ����������, �� ����� ��������� � ini-�����
///
/// \param owner        ������-��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
/// \param array_size   ����� ������ ������� (������������ ���������� ���������)
/// \param array_count  ������� ���������� ����������� ��������� � �������
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_bool_hidden_preference_arr)(preference_p owner, TPref_validator_arr validator, gconstpchar name, gboolean_p variable, guint array_size, guint_p array_count);

/// ����������� ����������
///
/// ���: ������ ������ �� ������/������������
///
/// \param owner        ������-��������
/// \param bool_owner   ��������-��������
/// \param bool_index   ����������/���������� ��������� � ����������� �� ��������� � ���� ���������:
///  - enum: ������� ����� ��������� �� ������ - ���� � enum ������ ������� � ��������� ����� � �����, �������� ��������
///  - bool: ���� 0, �� �������� ��������, ����� �������� bool-��������; ���� 1, �� ��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param title        ��������� � GUI, �� ������ ���� 0
/// \param description  �������� (��� �����������), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_enum_preference)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, gint_p variable, const value_string * enumvals);
/// ����������� ������� ����������
///
/// ���: ������ ������ �� ������/������������
///
/// ������� ���������, � ������� �� ������� �� ����� ����� � ������� ��������� ����������, �� ����� ��������� � ini-�����
///
/// \param owner        ������-��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_enum_hidden_preference)(preference_p owner, TPref_validator validator, gconstpchar name, gint_p variable, const value_string * enumvals);
/// ����������� ����������
///
/// ���: ������ ������ �� ������/������������ (������)
///
/// \param owner        ������-��������
/// \param bool_owner   ��������-��������
/// \param bool_index   ����������/���������� ��������� � ����������� �� ��������� � ���� ���������:
///  - enum: ������� ����� ��������� �� ������ - ���� � enum ������ ������� � ��������� ����� � �����, �������� ��������
///  - bool: ���� 0, �� �������� ��������, ����� �������� bool-��������; ���� 1, �� ��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param title        ��������� � GUI, �� ������ ���� 0
/// \param description  �������� (��� �����������), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
/// \param array_size   ����� ������ ������� (������������ ���������� ���������)
/// \param array_count  ������� ���������� ����������� ��������� � �������
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_enum_preference_arr)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description, gint_p variable, const value_string * enumvals, guint array_size, guint_p array_count);
/// ����������� ������� ����������
///
/// ���: ������ ������ �� ������/������������ (������)
///
/// ������� ���������, � ������� �� ������� �� ����� ����� � ������� ��������� ����������, �� ����� ��������� � ini-�����
///
/// \param owner        ������-��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
/// \param array_size   ����� ������ ������� (������������ ���������� ���������)
/// \param array_count  ������� ���������� ����������� ��������� � �������
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_enum_hidden_preference_arr)(preference_p owner, TPref_validator_arr validator, gconstpchar name, gint_p variable, const value_string * enumvals, guint array_size, guint_p array_count);

/// ����������� ����������
///
/// ���: ��������� ��������
///
/// \param owner        ������-��������
/// \param bool_owner   ��������-��������
/// \param bool_index   ����������/���������� ��������� � ����������� �� ��������� � ���� ���������:
///  - enum: ������� ����� ��������� �� ������ - ���� � enum ������ ������� � ��������� ����� � �����, �������� ��������
///  - bool: ���� 0, �� �������� ��������, ����� �������� bool-��������; ���� 1, �� ��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param title        ��������� � GUI, �� ������ ���� 0
/// \param description  �������� (��� �����������), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
/// \param variable_size  ������ ���������� (���������� ������), � ������
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_string_preference)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, char * variable, guint variable_size);
/// ����������� ������� ����������
///
/// ���: ��������� ��������
///
/// ������� ���������, � ������� �� ������� �� ����� ����� � ������� ��������� ����������, �� ����� ��������� � ini-�����
///
/// \param owner        ������-��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
/// \param variable_size  ������ ���������� (���������� ������), � ������
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_string_hidden_preference)(preference_p owner, TPref_validator validator, gconstpchar name, char * variable, guint variable_size);
/// ����������� ����������
///
/// ���: ��������� �������� (������)
///
/// \param owner        ������-��������
/// \param bool_owner   ��������-��������
/// \param bool_index   ����������/���������� ��������� � ����������� �� ��������� � ���� ���������:
///  - enum: ������� ����� ��������� �� ������ - ���� � enum ������ ������� � ��������� ����� � �����, �������� ��������
///  - bool: ���� 0, �� �������� ��������, ����� �������� bool-��������; ���� 1, �� ��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param title        ��������� � GUI, �� ������ ���� 0
/// \param description  �������� (��� �����������), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
/// \param variable_size  ������ ���������� (���������� ������), � ������
/// \param array_size   ����� ������ ������� (������������ ���������� ���������)
/// \param array_count  ������� ���������� ����������� ��������� � �������
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_string_preference_arr)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description, char ** variable, guint variable_size, guint array_size, guint_p array_count);
/// ����������� ������� ����������
///
/// ���: ��������� �������� (������)
///
/// ������� ���������, � ������� �� ������� �� ����� ����� � ������� ��������� ����������, �� ����� ��������� � ini-�����
///
/// \param owner        ������-��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
/// \param variable_size  ������ ���������� (���������� ������), � ������
/// \param array_size   ����� ������ ������� (������������ ���������� ���������)
/// \param array_count  ������� ���������� ����������� ��������� � �������
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_string_hidden_preference_arr)(preference_p owner, TPref_validator_arr validator, gconstpchar name, char ** variable, guint variable_size, guint array_size, guint_p array_count);

/// ����������� ����������
///
/// ���: ����/�������/����������
///
/// \param owner        ������-��������
/// \param bool_owner   ��������-��������
/// \param bool_index   ����������/���������� ��������� � ����������� �� ��������� � ���� ���������:
///  - enum: ������� ����� ��������� �� ������ - ���� � enum ������ ������� � ��������� ����� � �����, �������� ��������
///  - bool: ���� 0, �� �������� ��������, ����� �������� bool-��������; ���� 1, �� ��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param title        ��������� � GUI, �� ������ ���� 0
/// \param description  �������� (��� �����������), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
/// \param variable_size  ������ ���������� (���������� ������), � ������
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_dir_preference)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, char * variable, guint variable_size);
/// ����������� ������� ����������
///
/// ���: ����/�������/����������
///
/// ������� ���������, � ������� �� ������� �� ����� ����� � ������� ��������� ����������, �� ����� ��������� � ini-�����
///
/// \param owner        ������-��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
/// \param variable_size  ������ ���������� (���������� ������), � ������
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_dir_hidden_preference)(preference_p owner, TPref_validator validator, gconstpchar name, char * variable, guint variable_size);
/// ����������� ����������
///
/// ���: ����/�������/���������� (������)
///
/// \param owner        ������-��������
/// \param bool_owner   ��������-��������
/// \param bool_index   ����������/���������� ��������� � ����������� �� ��������� � ���� ���������:
///  - enum: ������� ����� ��������� �� ������ - ���� � enum ������ ������� � ��������� ����� � �����, �������� ��������
///  - bool: ���� 0, �� �������� ��������, ����� �������� bool-��������; ���� 1, �� ��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param title        ��������� � GUI, �� ������ ���� 0
/// \param description  �������� (��� �����������), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
/// \param variable_size  ������ ���������� (���������� ������), � ������
/// \param array_size   ����� ������ ������� (������������ ���������� ���������)
/// \param array_count  ������� ���������� ����������� ��������� � �������
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_dir_preference_arr)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description, char ** variable, guint variable_size, guint array_size, guint_p array_count);
/// ����������� ������� ����������
///
/// ���: ����/�������/���������� (������)
///
/// ������� ���������, � ������� �� ������� �� ����� ����� � ������� ��������� ����������, �� ����� ��������� � ini-�����
///
/// \param owner        ������-��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
/// \param variable_size  ������ ���������� (���������� ������), � ������
/// \param array_size   ����� ������ ������� (������������ ���������� ���������)
/// \param array_count  ������� ���������� ����������� ��������� � �������
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_dir_hidden_preference_arr)(preference_p owner, TPref_validator_arr validator, gconstpchar name, char ** variable, guint variable_size, guint array_size, guint_p array_count);

/// ����������� ����������
///
/// ���: ���� � �����
///
/// \param owner        ������-��������
/// \param bool_owner   ��������-��������
/// \param bool_index   ����������/���������� ��������� � ����������� �� ��������� � ���� ���������:
///  - enum: ������� ����� ��������� �� ������ - ���� � enum ������ ������� � ��������� ����� � �����, �������� ��������
///  - bool: ���� 0, �� �������� ��������, ����� �������� bool-��������; ���� 1, �� ��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param title        ��������� � GUI, �� ������ ���� 0
/// \param description  �������� (��� �����������), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
/// \param variable_size  ������ ���������� (���������� ������), � ������
/// \param afilter      ��������� ����������� ������� (���� ������)
///                     ������: \code <��������|������|��������|������...> \endcode
///                     ������: \code '��� ����� ( *.* )|*.*...' \endcode
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_file_preference)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, char * variable, guint variable_size, gconstpchar afilter);
/// ����������� ������� ����������
///
/// ���: ���� � �����
///
/// ������� ���������, � ������� �� ������� �� ����� ����� � ������� ��������� ����������, �� ����� ��������� � ini-�����
///
/// \param owner        ������-��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
/// \param variable_size  ������ ���������� (���������� ������), � ������
/// \param afilter      ��������� ����������� ������� (���� ������)
///                     ������: \code <��������|������|��������|������...> \endcode
///                     ������: \code '��� ����� ( *.* )|*.*...' \endcode
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_file_hidden_preference)(preference_p owner, TPref_validator validator, gconstpchar name, char * variable, guint variable_size, gconstpchar afilter);
/// ����������� ����������
///
/// ���: ���� � ����� (������)
///
/// \param owner        ������-��������
/// \param bool_owner   ��������-��������
/// \param bool_index   ����������/���������� ��������� � ����������� �� ��������� � ���� ���������:
///  - enum: ������� ����� ��������� �� ������ - ���� � enum ������ ������� � ��������� ����� � �����, �������� ��������
///  - bool: ���� 0, �� �������� ��������, ����� �������� bool-��������; ���� 1, �� ��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param title        ��������� � GUI, �� ������ ���� 0
/// \param description  �������� (��� �����������), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
/// \param variable_size  ������ ���������� (���������� ������), � ������
/// \param afilter      ��������� ����������� ������� (���� ������)
///                     ������: \code <��������|������|��������|������...> \endcode
///                     ������: \code '��� ����� ( *.* )|*.*...' \endcode
/// \param array_size   ����� ������ ������� (������������ ���������� ���������)
/// \param array_count  ������� ���������� ����������� ��������� � �������
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_file_preference_arr)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description, char ** variable, guint variable_size, gconstpchar afilter, guint array_size, guint_p array_count);
/// ����������� ������� ����������
///
/// ���: ���� � ����� (������)
///
/// ������� ���������, � ������� �� ������� �� ����� ����� � ������� ��������� ����������, �� ����� ��������� � ini-�����
///
/// \param owner        ������-��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
/// \param variable_size  ������ ���������� (���������� ������), � ������
/// \param afilter      ��������� ����������� ������� (���� ������)
///                     ������: \code <��������|������|��������|������...> \endcode
///                     ������: \code '��� ����� ( *.* )|*.*...' \endcode
/// \param array_size   ����� ������ ������� (������������ ���������� ���������)
/// \param array_count  ������� ���������� ����������� ��������� � �������
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_file_hidden_preference_arr)(preference_p owner, TPref_validator_arr validator, gconstpchar name, char ** variable, guint variable_size, gconstpchar afilter, guint array_size, guint_p array_count);

/// ����������� ����������
///
/// ���: ����� ��������� ��������, ����������� ������ � �������
///
/// \param owner        ������-��������
/// \param bool_owner   ��������-��������
/// \param bool_index   ����������/���������� ��������� � ����������� �� ��������� � ���� ���������:
///  - enum: ������� ����� ��������� �� ������ - ���� � enum ������ ������� � ��������� ����� � �����, �������� ��������
///  - bool: ���� 0, �� �������� ��������, ����� �������� bool-��������; ���� 1, �� ��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param title        ��������� � GUI, �� ������ ���� 0
/// \param description  �������� (��� �����������), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
/// \param variable_size  ������ ���������� (���������� ������), � ������
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_csv_preference)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, char * variable, guint variable_size);
/// ����������� ������� ����������
///
/// ���: ����� ��������� ��������, ����������� ������ � �������
///
/// ������� ���������, � ������� �� ������� �� ����� ����� � ������� ��������� ����������, �� ����� ��������� � ini-�����
///
/// \param owner        ������-��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
/// \param variable_size  ������ ���������� (���������� ������), � ������
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_csv_hidden_preference)(preference_p owner, TPref_validator validator, gconstpchar name, char * variable, guint variable_size);
/// ����������� ����������
///
/// ���: ����� ��������� ��������, ����������� ������ � ������� (������)
///
/// \param owner        ������-��������
/// \param bool_owner   ��������-��������
/// \param bool_index   ����������/���������� ��������� � ����������� �� ��������� � ���� ���������:
///  - enum: ������� ����� ��������� �� ������ - ���� � enum ������ ������� � ��������� ����� � �����, �������� ��������
///  - bool: ���� 0, �� �������� ��������, ����� �������� bool-��������; ���� 1, �� ��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param title        ��������� � GUI, �� ������ ���� 0
/// \param description  �������� (��� �����������), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
/// \param variable_size  ������ ���������� (���������� ������), � ������
/// \param array_size   ����� ������ ������� (������������ ���������� ���������)
/// \param array_count  ������� ���������� ����������� ��������� � �������
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_csv_preference_arr)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description, char ** variable, guint variable_size, guint array_size, guint_p array_count);
/// ����������� ������� ����������
///
/// ���: ����� ��������� ��������, ����������� ������ � ������� (������)
///
/// ������� ���������, � ������� �� ������� �� ����� ����� � ������� ��������� ����������, �� ����� ��������� � ini-�����
///
/// \param owner        ������-��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
/// \param variable_size  ������ ���������� (���������� ������), � ������
/// \param array_size   ����� ������ ������� (������������ ���������� ���������)
/// \param array_count  ������� ���������� ����������� ��������� � �������
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_csv_hidden_preference_arr)(preference_p owner, TPref_validator_arr validator, gconstpchar name, char ** variable, guint variable_size, guint array_size, guint_p array_count);

/// ����������� ����������
///
/// ���: ��������������� �����, ���������� �� ������� �����
///
/// \param owner        ������-��������
/// \param bool_owner   ��������-��������
/// \param bool_index   ����������/���������� ��������� � ����������� �� ��������� � ���� ���������:
///  - enum: ������� ����� ��������� �� ������ - ���� � enum ������ ������� � ��������� ����� � �����, �������� ��������
///  - bool: ���� 0, �� �������� ��������, ����� �������� bool-��������; ���� 1, �� ��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param title        ��������� � GUI, �� ������ ���� 0
/// \param description  �������� (��� �����������), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
/// \param variable_size  ������ ���������� (���������� ������), � ������
/// \param afile_name   ��� �������� �����, ������������� ��� �������� �������� ���������. �� ������ ��������� ��������� ����.
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_text_preference)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, char * variable, guint variable_size, gconstpchar afile_name);
/// ����������� ������� ����������
///
/// ���: ��������������� �����, ���������� �� ������� �����
///
/// ������� ���������, � ������� �� ������� �� ����� ����� � ������� ��������� ����������, �� ����� ��������� � ini-�����
///
/// \param owner        ������-��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
/// \param variable_size  ������ ���������� (���������� ������), � ������
/// \param afile_name   ��� �������� �����, ������������� ��� �������� �������� ���������. �� ������ ��������� ��������� ����.
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_text_hidden_preference)(preference_p owner, TPref_validator validator, gconstpchar name, char * variable, guint variable_size, gconstpchar afile_name);
/// ����������� ����������
///
/// ���: ��������������� �����, ���������� �� ������� ����� (������)
///
/// \param owner        ������-��������
/// \param bool_owner   ��������-��������
/// \param bool_index   ����������/���������� ��������� � ����������� �� ��������� � ���� ���������:
///  - enum: ������� ����� ��������� �� ������ - ���� � enum ������ ������� � ��������� ����� � �����, �������� ��������
///  - bool: ���� 0, �� �������� ��������, ����� �������� bool-��������; ���� 1, �� ��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param title        ��������� � GUI, �� ������ ���� 0
/// \param description  �������� (��� �����������), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
/// \param variable_size  ������ ���������� (���������� ������), � ������
/// \param afile_name   ��� �������� �����, ������������� ��� �������� �������� ���������. �� ������ ��������� ��������� ����.
/// \param array_size   ����� ������ ������� (������������ ���������� ���������)
/// \param array_count  ������� ���������� ����������� ��������� � �������
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_text_preference_arr)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description, char ** variable, guint variable_size, gconstpchar afile_name, guint array_size, guint_p array_count);
/// ����������� ������� ����������
///
/// ���: ��������������� �����, ���������� �� ������� ����� (������)
///
/// ������� ���������, � ������� �� ������� �� ����� ����� � ������� ��������� ����������, �� ����� ��������� � ini-�����
///
/// \param owner        ������-��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
/// \param variable_size  ������ ���������� (���������� ������), � ������
/// \param afile_name   ��� �������� �����, ������������� ��� �������� �������� ���������. �� ������ ��������� ��������� ����.
/// \param array_size   ����� ������ ������� (������������ ���������� ���������)
/// \param array_count  ������� ���������� ����������� ��������� � �������
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_text_hidden_preference_arr)(preference_p owner, TPref_validator_arr validator, gconstpchar name, char ** variable, guint variable_size, gconstpchar afile_name, guint array_size, guint_p array_count);

#ifdef PREFS_GUI
/// ����������� ����������
///
/// ���: ������, ��� ������������������ � �������
///
/// \param owner        ������-��������
/// \param bool_owner   ��������-��������
/// \param bool_index   ����������/���������� ��������� � ����������� �� ��������� � ���� ���������:
///  - enum: ������� ����� ��������� �� ������ - ���� � enum ������ ������� � ��������� ����� � �����, �������� ��������
///  - bool: ���� 0, �� �������� ��������, ����� �������� bool-��������; ���� 1, �� ��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param title        ��������� � GUI, �� ������ ���� 0
/// \param description  �������� (��� �����������), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
/// \param readonly ������� ����������� ���������
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_dialog_preference)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, preference_p variable, gboolean_p readonly);
/// ����������� ����������
///
/// ���: ������� ������
///
/// \param owner        ������-��������
/// \param bool_owner   ��������-��������
/// \param bool_index   ����������/���������� ��������� � ����������� �� ��������� � ���� ���������:
///  - enum: ������� ����� ��������� �� ������ - ���� � enum ������ ������� � ��������� ����� � �����, �������� ��������
///  - bool: ���� 0, �� �������� ��������, ����� �������� bool-��������; ���� 1, �� ��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param title        ��������� � GUI, �� ������ ���� 0
/// \param description  �������� (��� �����������), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
/// \param user_data    ���������������� ������, ������������ � �������� ��������� ��� ������ variable
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_alien_dialog_preference)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, Talien_dialog_executor variable, gpointer user_data, gboolean_p readonly);

/// ����������� ����������
///
/// ���: ������
///
/// \param owner        ������-��������
/// \param bool_owner   ��������-��������
/// \param bool_index   ����������/���������� ��������� � ����������� �� ��������� � ���� ���������:
///  - enum: ������� ����� ��������� �� ������ - ���� � enum ������ ������� � ��������� ����� � �����, �������� ��������
///  - bool: ���� 0, �� �������� ��������, ����� �������� bool-��������; ���� 1, �� ��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param title        ��������� � GUI, �� ������ ���� 0
/// \param description  �������� (��� �����������), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
/// \param dialog       ������� ������, ��������� ��� ��������� ���������� �������
/// \param user_data    ���������������� ������, ������������ � �������� ��������� ��� ������ dialog
///
/// \return ����� �� ��������� ���������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_register_plug_preference)(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, gboolean_p variable, Talien_dialog_executor dialog, gpointer user_data);
#endif

/// �������� ���������� �� �����
/// ������������ ������� ����������� �� ���������
/// file_name �� ����� ���� ����� 0 ��� ""
///
/// \param file_name ��� �����
///
typedef gboolean (MSCU_CALL_PREFIX * Tprefs_load_from_file)(gconstpchar file_name);

/// �������� ���������� ������������� ������� �� �����
/// file_name �� ����� ���� ����� 0 ��� ""
///
/// \param file_name ��� �����
///
typedef gboolean (MSCU_CALL_PREFIX * Tprefs_load_from_file_dlg)(gconstpchar file_name, preference_p dialog_p);

/// ���������� ���������� � ����
/// ������������ ������� ����������� �� ���������
/// file_name �� ����� ���� ����� 0 ��� ""
///
/// \param file_name ��� �����
///
typedef gboolean (MSCU_CALL_PREFIX * Tprefs_save_to_file)(gconstpchar file_name);
/// ���������� ���������� ������������� ������� � ����
/// file_name �� ����� ���� ����� 0 ��� ""
///
/// \param file_name ��� �����
///
typedef gboolean (MSCU_CALL_PREFIX * Tprefs_save_to_file_dlg)(gconstpchar file_name, preference_p dialog_p);

#ifdef PREFS_GUI
/// ������ ����������� ���� ��������� ����������
/// ���������� true, ���� ���� �� ���� �������� ���� ��������
///
/// \param dialog_p ������
///
typedef gboolean (MSCU_CALL_PREFIX * Tprefs_params_dlg)(preference_p dialog_p);
#endif

/// ������������� 
/// ������ ������� � ����������
typedef void (MSCU_CALL_PREFIX * Tprefs_lock)(); 

/// �������������
/// ������������ ������� � ����������
typedef void (MSCU_CALL_PREFIX * Tprefs_unlock)(); 

/// ��������� ������������ � ����
/// file_name �� ����� ���� ����� 0 ��� ""
/// 
/// \param file_name ��� ����� ��� ���������
///
typedef gboolean (MSCU_CALL_PREFIX * Tprefs_generate_documentation)(gconstpchar file_name);

/// ������������� ������������ ������ ��� �� �������� � ����� ������ ��������/����������
/// ����������/����� ���� "������������ ������"
///
/// \return ����� �� ��������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_set_exclusive_dialog)(preference_p dialog_p, gboolean value);

/// \name ������� ����������
/// \{

///
/// \return ����� �� ��������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_set_sorted_prefs)(preference_p preference, gboolean value);
///
/// \return ����� �� ��������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_set_pref_index)(preference_p preference, preference_p value);
///
/// \return ����� �� ��������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_set_update_index)(preference_p preference, Tindex_executor value);
///
/// \return ����� �� ��������� ���������
///
typedef preference_p (MSCU_CALL_PREFIX * Tprefs_set_update_index_user_data)(preference_p preference, gpointer value);

/// \}

/// \name ������� ��������� �������� �� ����������
/// \{

/// ��������� ��������
///
typedef char * (MSCU_CALL_PREFIX * Tprefs_get_var_string)(preference_p preference);
/// ��������� ������� ���������� ������
///
typedef guint (MSCU_CALL_PREFIX * Tprefs_get_var_string_size)(preference_p preference);

/// ��������� ��������
///
typedef guint_p (MSCU_CALL_PREFIX * Tprefs_get_var_uint)(preference_p preference);

/// ��������� ��������
///
typedef gdouble_p (MSCU_CALL_PREFIX * Tprefs_get_var_double)(preference_p preference);

/// ��������� ��������
///
typedef gboolean_p (MSCU_CALL_PREFIX * Tprefs_get_var_bool)(preference_p preference);

/// ��������� ��������
///
typedef gint_p (MSCU_CALL_PREFIX * Tprefs_get_var_enum)(preference_p preference);

/// ��������� ������������� ���������� ��������� (������)
///
typedef guint (MSCU_CALL_PREFIX * Tprefs_get_var_size_arr)(preference_p preference);

/// ��������� �������� ���������� ��������� (������)
///
typedef guint_p (MSCU_CALL_PREFIX * Tprefs_get_var_count_arr)(preference_p preference);

/// ��������� �������� (������)
///
typedef char * (MSCU_CALL_PREFIX * Tprefs_get_var_string_arr)(preference_p preference, guint index);

/// ��������� �������� (������)
///
typedef guint_p (MSCU_CALL_PREFIX * Tprefs_get_var_uint_arr)(preference_p preference, guint index);

/// ��������� �������� (������)
///
typedef gdouble_p (MSCU_CALL_PREFIX * Tprefs_get_var_double_arr)(preference_p preference, guint index);

/// ��������� �������� (������)
///
typedef gboolean_p (MSCU_CALL_PREFIX * Tprefs_get_var_bool_arr)(preference_p preference, guint index);

/// ��������� �������� (������)
///
typedef gint_p (MSCU_CALL_PREFIX * Tprefs_get_var_enum_arr)(preference_p preference, guint index);

/// \}
#endif