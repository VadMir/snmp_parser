/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/// \file prefs.h
/// \mainpage
/// @{
/// \section attention ��������������
/// \b ��������! ���� <b>"prefs.h"</b> ���������������� ��� ��������� ������ ������������ ������� �����.
/// ����� ��������� � ������ ����� ���������� �������������� �����������.
/// ��� ������������� ������� ����� ������ �������� ��� � ������ � ������� ��������� #include.
///
/// \section updated ��������� ����������
/// <b>2016-08-14</b>
///
/// \section changelog ���������
/// - [+] 2016-08-14 - ��������� ������� prefs_params_terminal_dlg;
/// - [+] 2015-04-13 - ��������� ������� prefs_find_preference;
/// - [+] 2014-03-14 - ���������: ���-��������� � ��������������� �������: prefs_register_category;
/// - [+] 2012-04-09 - ��������� ������� prefs_unregister_XXX
/// - [*] 2012-04-09 - ��������� ������������ �� ������� prefs_register_XXX
/// - [+] 2011-07-20 - ��������� ������� prefs_set_tags
/// - [+] 2010-07-26 - ��������� ������� prefs_set_min/max_XXX
/// - [+] 2010-04-17 - ��������� ������� prefs_set_xml_mode
/// - [+] 2009-09-21 - ��������� ������� prefs_set_expert
/// - [*] 2009-09-19 - ������� ��� prefs_get_tmp_val_XXX-�������
/// - [*] 2009-09-18 - ������������� ������ ��� �������� �������������
/// - [-] 2009-09-18 - ���������� ������ � ��������� �������� "����" (PREF_FILE)
/// - [+] 2009-08-03 - �������� msecs-��� � ��������������� �������: prefs_register_XXX, prefs_get_XXX
/// - [+] 2009-05-18 - �������� int64-��� � ��������������� �������: prefs_register_XXX, prefs_get_XXX
/// - [*] 2009-04-17 - ����������
///
/// \section description ��������
/// ������ �������� �������� API ������ ��������� ��������.
///
/// \section copyright ��������� �����
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

/// \defgroup prefs_interface ��������� ������ ��������� ��������
/// \{

/// ������ ���������� ������, ���������������� ��� �������� ���� ������ � �.�. �������� � ������
#define PREFS_MAX_PATH 4096

/// ��������� �� ���������� ������-��������
typedef gpointer preference_p;

/// \name ����������
/// \{

/// ����� ������ ���������� ��������� (action)
#define vaCorrect 0  ///< �������� � ���������, ����������
#define vaVerify  1  ///< �������� �� ������������ (��������� ��������)
#define vaApply   2  ///< ���������� (��� ������ ������)

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

/// ����� �������� �������
typedef gboolean (MSCU_CALL_PREFIX * Talien_dialog_executor)(gpointer user_data);

/// ����� ������� ���������� �������
typedef void (MSCU_CALL_PREFIX * Tindex_executor)(gpointer user_data);

//////////////////////////////////////////////////////////////////////////
/// ������� ��� ������� ����� � ����������� �����
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
/// ����������� �������
///
/// \param name         ���������� ��� �������
/// \param title        ��������� � GUI
/// \param description  �������� �������
/// \param readonly     ������� ����������� ���������
///
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_dialog(gconstpchar name, gconstpchar title, gconstpchar description, gboolean_p readonly);

/// ������������� ������������ ������ ��� �� �������� � ����� ������ ��������/����������
/// ����������/����� ���� "������������ ������"
///
/// \param[in] dialog_p ������
/// \param[in] value    ��������������� �������� (true - ����������, false - �����)
///
/// \return ����� �� ��������� ���������
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_set_exclusive_dialog(preference_p dialog_p, gboolean value);

/// ����������� ������
///
/// \param owner    ������-�������� (NULL - ���� ����� ���������� � �����)
/// \param name     ���������� ��� ������
/// \param title    ��������� � GUI
/// \param description  �������� (��� �����������), �� ������ ���� 0
/// \param index    ������� ������ ��������
/// \param readonly ������� ����������� ���������
///
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_module(preference_p owner, gconstpchar name, gconstpchar title, gconstpchar description, gint index, gboolean_p readonly);

//////////////////////////////////////////////////////////////////////////
/// ����������� ����������
///
/// ���: ���������
///
/// \param owner        ������-��������
/// \param bool_owner   ��������-��������
/// \param bool_index   ����������/���������� ��������� � ����������� �� ��������� � ���� ���������:
///  - enum: ������� ����� ��������� �� ������ - ���� � enum ������ ������� � ��������� ����� � �����, �������� ��������
///  - bool: ���� 0, �� �������� ��������, ����� �������� bool-��������; ���� 1, �� ��������
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param title        ��������� � GUI, �� ������ ���� 0
/// \param description  �������� (��� �����������), �� ������ ���� 0
///
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_category_preference(preference_p owner, preference_p bool_owner, gint bool_index, gconstpchar name, gconstpchar title, gconstpchar description);
/// ����������� ����������
///
/// ���: ���������
///
/// \param owner        ������-��������
/// \param bool_owner   ��������-��������
/// \param bool_index   ����������/���������� ��������� � ����������� �� ��������� � ���� ���������:
///  - enum: ������� ����� ��������� �� ������ - ���� � enum ������ ������� � ��������� ����� � �����, �������� ��������
///  - bool: ���� 0, �� �������� ��������, ����� �������� bool-��������; ���� 1, �� ��������
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param title        ��������� � GUI, �� ������ ���� 0
/// \param description  �������� (��� �����������), �� ������ ���� 0
///
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_category_preference_arr(preference_p owner, preference_p bool_owner, gint bool_index, gconstpchar name, gconstpchar title, gconstpchar description);

//////////////////////////////////////////////////////////////////////////
/// ����������� ����������
///
/// ���: ����� ��� �����
///
/// ��������� ������������ � K/M/G/T (1K = 1024, 1M = 1024K = 1048576, 1G = 1024M = 1048576K = 1073741824, 1T = 1024G = 1048576M = 1073741824K = 1099511627776), 0x � ����������������� �������� (0xff = 255).
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_uint_preference(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, guint_p variable);
/// ����������� ������� ����������
///
/// ���: ����� ��� �����
///
/// ��������� ������������ � K/M/G/T (1K = 1024, 1M = 1024K = 1048576, 1G = 1024M = 1048576K = 1073741824, 1T = 1024G = 1048576M = 1073741824K = 1099511627776), 0x � ����������������� �������� (0xff = 255).
///
/// ������� ���������, � ������� �� ������� �� ����� ����� � ������� ��������� ����������, �� ����� ��������� � ini-�����
///
/// \param owner        ������-��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
///
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_uint_hidden_preference(preference_p owner, TPref_validator validator, gconstpchar name, guint_p variable);
/// ����������� ����������
///
/// ���: ����� ��� ����� (������)
///
/// ��������� ������������ � K/M/G/T (1K = 1024, 1M = 1024K = 1048576, 1G = 1024M = 1048576K = 1073741824, 1T = 1024G = 1048576M = 1073741824K = 1099511627776), 0x � ����������������� �������� (0xff = 255).
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_uint_preference_arr(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description,
                                                                   guint_p variable, guint array_size, guint_p array_count);
/// ����������� ������� ����������
///
/// ���: ����� ��� ����� (������)
///
/// ��������� ������������ � K/M/G/T (1K = 1024, 1M = 1024K = 1048576, 1G = 1024M = 1048576K = 1073741824, 1T = 1024G = 1048576M = 1073741824K = 1099511627776), 0x � ����������������� �������� (0xff = 255).
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_uint_hidden_preference_arr(preference_p owner, TPref_validator_arr validator, gconstpchar name,
                                                                          guint_p variable, guint array_size, guint_p array_count);

//////////////////////////////////////////////////////////////////////////
/// ����������� ����������
///
/// ���: ��������� �������� � �������������
///
/// ��������� ������������ � s/m/h/d (1s = 1000 �� = 1 �������, 1m = 60000 �� = 1 ������, 1h = 3600000 �� = 1 ���, 1d = 86400000 �� = 1 ����), 0x � ����������������� �������� (0xff = 255).
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_msec_preference(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, guint_p variable);
/// ����������� ������� ����������
///
/// ���: ��������� �������� � �������������
///
/// ��������� ������������ � s/m/h/d (1s = 1000 �� = 1 �������, 1m = 60000 �� = 1 ������, 1h = 3600000 �� = 1 ���, 1d = 86400000 �� = 1 ����), 0x � ����������������� �������� (0xff = 255).
///
/// ������� ���������, � ������� �� ������� �� ����� ����� � ������� ��������� ����������, �� ����� ��������� � ini-�����
///
/// \param owner        ������-��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
///
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_msec_hidden_preference(preference_p owner, TPref_validator validator, gconstpchar name, guint_p variable);
/// ����������� ����������
///
/// ���: ��������� �������� � ������������� (������)
///
/// ��������� ������������ � s/m/h/d (1s = 1000 �� = 1 �������, 1m = 60000 �� = 1 ������, 1h = 3600000 �� = 1 ���, 1d = 86400000 �� = 1 ����), 0x � ����������������� �������� (0xff = 255).
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_msec_preference_arr(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description,
                                                                   guint_p variable, guint array_size, guint_p array_count);
/// ����������� ������� ����������
///
/// ���: ��������� �������� � ������������� (������)
///
/// ��������� ������������ � s/m/h/d (1s = 1000 �� = 1 �������, 1m = 60000 �� = 1 ������, 1h = 3600000 �� = 1 ���, 1d = 86400000 �� = 1 ����), 0x � ����������������� �������� (0xff = 255).
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_msec_hidden_preference_arr(preference_p owner, TPref_validator_arr validator, gconstpchar name,
                                                                          guint_p variable, guint array_size, guint_p array_count);

//////////////////////////////////////////////////////////////////////////
/// ����������� ����������
///
/// ���: ����� �� ������ 64 ���
///
/// ��������� ������������ � K/M/G/T (1K = 1024, 1M = 1024K = 1048576, 1G = 1024M = 1048576K = 1073741824, 1T = 1024G = 1048576M = 1073741824K = 1099511627776), 0x � ����������������� �������� (0xff = 255).
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_int64_preference(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, gint64_p variable);
/// ����������� ������� ����������
///
/// ���: ����� �� ������ 64 ���
///
/// ��������� ������������ � K/M/G/T (1K = 1024, 1M = 1024K = 1048576, 1G = 1024M = 1048576K = 1073741824, 1T = 1024G = 1048576M = 1073741824K = 1099511627776), 0x � ����������������� �������� (0xff = 255).
///
/// ������� ���������, � ������� �� ������� �� ����� ����� � ������� ��������� ����������, �� ����� ��������� � ini-�����
///
/// \param owner        ������-��������
/// \param validator    �������, ���������� ��� ��������/����������/������������� �������� ���������. ����� ���� ����� 0.
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
/// \param variable     ����� �� ���������� �� ��������� ���������������� ����, �� ������ ���� 0
///
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_int64_hidden_preference(preference_p owner, TPref_validator validator, gconstpchar name, gint64_p variable);
/// ����������� ����������
///
/// ���: ����� �� ������ 64 ���
///
/// ��������� ������������ � K/M/G/T (1K = 1024, 1M = 1024K = 1048576, 1G = 1024M = 1048576K = 1073741824, 1T = 1024G = 1048576M = 1073741824K = 1099511627776), 0x � ����������������� �������� (0xff = 255).
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_int64_preference_arr(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description,
                                                                   gint64_p variable, guint array_size, guint_p array_count);
/// ����������� ������� ����������
///
/// ���: ����� �� ������ 64 ���
///
/// ��������� ������������ � K/M/G/T (1K = 1024, 1M = 1024K = 1048576, 1G = 1024M = 1048576K = 1073741824, 1T = 1024G = 1048576M = 1073741824K = 1099511627776), 0x � ����������������� �������� (0xff = 255).
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_int64_hidden_preference_arr(preference_p owner, TPref_validator_arr validator, gconstpchar name,
                                                                          gint64_p variable, guint array_size, guint_p array_count);

//////////////////////////////////////////////////////////////////////////
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_double_preference(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, gdouble_p variable);
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_double_hidden_preference(preference_p owner, TPref_validator validator, gconstpchar name, gdouble_p variable);
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_double_preference_arr(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description,
                                                                     gdouble_p variable, guint array_size, guint_p array_count);
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_double_hidden_preference_arr(preference_p owner, TPref_validator_arr validator, gconstpchar name,
                                                                            gdouble_p variable, guint array_size, guint_p array_count);

//////////////////////////////////////////////////////////////////////////
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_bool_preference(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, gboolean_p variable);
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_bool_hidden_preference(preference_p owner, TPref_validator validator, gconstpchar name, gboolean_p variable);
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_bool_preference_arr(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description,
                                                                   gboolean_p variable, guint array_size, guint_p array_count);
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_bool_hidden_preference_arr(preference_p owner, TPref_validator_arr validator, gconstpchar name,
                                                                          gboolean_p variable, guint array_size, guint_p array_count);
//////////////////////////////////////////////////////////////////////////
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
/// \param enumvals     ������ ��������� ��������
///
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_enum_preference(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, gint_p variable, const value_string * enumvals);
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
/// \param enumvals     ������ ��������� ��������
///
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_enum_hidden_preference(preference_p owner, TPref_validator validator, gconstpchar name, gint_p variable, const value_string * enumvals);
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
/// \param enumvals     ������ ��������� ��������
/// \param array_size   ����� ������ ������� (������������ ���������� ���������)
/// \param array_count  ������� ���������� ����������� ��������� � �������
///
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_enum_preference_arr(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description,
                                                                   gint_p variable, const value_string * enumvals, guint array_size, guint_p array_count);
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
/// \param enumvals     ������ ��������� ��������
/// \param array_size   ����� ������ ������� (������������ ���������� ���������)
/// \param array_count  ������� ���������� ����������� ��������� � �������
///
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_enum_hidden_preference_arr(preference_p owner, TPref_validator_arr validator, gconstpchar name,
                                                                          gint_p variable, const value_string * enumvals, guint array_size, guint_p array_count);

//////////////////////////////////////////////////////////////////////////
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_string_preference(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, char * variable, guint variable_size);
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_string_hidden_preference(preference_p owner, TPref_validator validator, gconstpchar name, char * variable, guint variable_size);
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_string_preference_arr(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description,
                                                                     char ** variable, guint variable_size, guint array_size, guint_p array_count);
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_string_hidden_preference_arr(preference_p owner, TPref_validator_arr validator, gconstpchar name,
                                                                            char ** variable, guint variable_size, guint array_size, guint_p array_count);

//////////////////////////////////////////////////////////////////////////
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_dir_preference(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, char * variable, guint variable_size);
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_dir_hidden_preference(preference_p owner, TPref_validator validator, gconstpchar name, char * variable, guint variable_size);
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_dir_preference_arr(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description,
                                                                  char ** variable, guint variable_size, guint array_size, guint_p array_count);
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_dir_hidden_preference_arr(preference_p owner, TPref_validator_arr validator, gconstpchar name,
                                                                         char ** variable, guint variable_size, guint array_size, guint_p array_count);

//////////////////////////////////////////////////////////////////////////
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_file_preference(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, char * variable, guint variable_size, gconstpchar afilter);
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_file_hidden_preference(preference_p owner, TPref_validator validator, gconstpchar name, char * variable, guint variable_size, gconstpchar afilter);
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_file_preference_arr(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description,
                                                                   char ** variable, guint variable_size, gconstpchar afilter, guint array_size, guint_p array_count);
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_file_hidden_preference_arr(preference_p owner, TPref_validator_arr validator, gconstpchar name,
                                                                          char ** variable, guint variable_size, gconstpchar afilter, guint array_size, guint_p array_count);

//////////////////////////////////////////////////////////////////////////
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_csv_preference(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, char * variable, guint variable_size);
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_csv_hidden_preference(preference_p owner, TPref_validator validator, gconstpchar name, char * variable, guint variable_size);
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_csv_preference_arr(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description,
                                                                  char ** variable, guint variable_size, guint array_size, guint_p array_count);
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_csv_hidden_preference_arr(preference_p owner, TPref_validator_arr validator, gconstpchar name,
                                                                         char ** variable, guint variable_size, guint array_size, guint_p array_count);

//////////////////////////////////////////////////////////////////////////
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_text_preference(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, char * variable, guint variable_size, gconstpchar afile_name);
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_text_hidden_preference(preference_p owner, TPref_validator validator, gconstpchar name, char * variable, guint variable_size, gconstpchar afile_name);
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_text_preference_arr(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator_arr validator, gconstpchar name, gconstpchar title, gconstpchar description,
                                                                   char ** variable, guint variable_size, gconstpchar afile_name, guint array_size, guint_p array_count);
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_text_hidden_preference_arr(preference_p owner, TPref_validator_arr validator, gconstpchar name,
                                                                          char ** variable, guint variable_size, gconstpchar afile_name, guint array_size, guint_p array_count);

//////////////////////////////////////////////////////////////////////////
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_dialog_preference(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, preference_p variable, gboolean_p readonly);
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_alien_dialog_preference(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, Talien_dialog_executor variable, gpointer user_data, gboolean_p readonly);
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
/// \return ����� �� ��������� ���������� ��������� (��� �������, ���� �������� � ����� ������� ��� ����������)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_register_plug_preference(preference_p owner, preference_p bool_owner, gint bool_index, TPref_validator validator, gconstpchar name, gconstpchar title, gconstpchar description, gboolean_p variable, Talien_dialog_executor dialog, gpointer user_data);
//#endif

//////////////////////////////////////////////////////////////////////////
/// ������ ����������� �������
///
/// \param name         ���������� ��� �������
///
extern "C" PREFS_API void MSCU_CALL_PREFIX prefs_unregister_dialog(gconstpchar name);

/// ������ ����������� ������
///
/// \param owner    ������-�������� (NULL - ���� ����� ���������� � �����)
/// \param name     ���������� ��� ������
///
extern "C" PREFS_API void MSCU_CALL_PREFIX prefs_unregister_module(preference_p owner, gconstpchar name);

/// ������ ����������� ���������
///
/// \param owner        ������-��������
/// \param name         ���������� ��� (��� ini-�����), �� ������ ���� 0
///
extern "C" PREFS_API void MSCU_CALL_PREFIX prefs_unregister_preference(preference_p owner, gconstpchar name);

/// ��������� xml-������ ��������� �����/������
/// ���������� ����� ������ load/save-�������
/// ���� xml-����� �������, ������ ������ - XML
/// ���� xml-����� ��������, ������ ������ - INI
///
/// ��-��������� xml-����� ��������
///
/// \param xml_mode_active ���������� xml-������
///
extern "C" PREFS_API void MSCU_CALL_PREFIX prefs_set_xml_mode(gboolean xml_mode_active);

/// �������� ���������� �� �����
/// ������������ ������� ����������� �� ���������
/// file_name �� ����� ���� ����� 0 ��� ""
///
/// \param file_name ��� �����
///
extern "C" PREFS_API gboolean MSCU_CALL_PREFIX prefs_load_from_file(gconstpchar file_name);
/// �������� ���������� ������������� ������� �� �����
/// file_name �� ����� ���� ����� 0 ��� ""
///
/// \param file_name    ��� �����
/// \param[in] dialog_p ������
///
extern "C" PREFS_API gboolean MSCU_CALL_PREFIX prefs_load_from_file_dlg(gconstpchar file_name, preference_p dialog_p);
/// ���������� ���������� � ����
/// ������������ ������� ����������� �� ���������
/// file_name �� ����� ���� ����� 0 ��� ""
///
/// \param file_name ��� �����
///
extern "C" PREFS_API gboolean MSCU_CALL_PREFIX prefs_save_to_file(gconstpchar file_name);
/// ���������� ���������� ������������� ������� � ����
/// file_name �� ����� ���� ����� 0 ��� ""
///
/// \param file_name    ��� �����
/// \param[in] dialog_p ������
///
extern "C" PREFS_API gboolean MSCU_CALL_PREFIX prefs_save_to_file_dlg(gconstpchar file_name, preference_p dialog_p);

/// ������ ����������� ���� ��������� ����������
/// ���������� true, ���� ���� �� ���� �������� ���� ��������
///
/// \param dialog_p ������
///
extern "C" PREFS_API gboolean MSCU_CALL_PREFIX prefs_params_dlg(preference_p dialog_p);

/// ����� ����������� ����������� ���� ��������� ����������
#define PREFS_TERMINAL_MODE_DEFAULT		0  ///< ��-���������
#define PREFS_TERMINAL_MODE_DIALOG		1  ///< dialog (dialog.exe)
#define PREFS_TERMINAL_MODE_WHIPTAIL	2  ///< newt whiptail

/// ������ ����������� ����������� ���� ��������� ����������
/// ���������� true, ���� ���� �� ���� �������� ���� ��������
///
/// \param mode ����� ������ (��������� PREFS_TERMINAL_MODE_XXX)
/// \param dialog_p ������
extern "C" PREFS_API gboolean MSCU_CALL_PREFIX prefs_params_terminal_dlg(gint mode, preference_p dialog_p);
///

/// �������������
/// ������ ������� � ����������
extern "C" PREFS_API void MSCU_CALL_PREFIX prefs_lock();
/// �������������
/// ������������ ������� � ����������
extern "C" PREFS_API void MSCU_CALL_PREFIX prefs_unlock();

/// ��������� ������������ � ����
/// file_name �� ����� ���� ����� 0 ��� ""
///
/// \param file_name ��� ����� ��� ���������
///
extern "C" PREFS_API gboolean MSCU_CALL_PREFIX prefs_generate_documentation(gconstpchar file_name);

/// \name ������� ����������
/// \{

///
/// \return ����� �� ��������� ���������
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_set_sorted_prefs(preference_p preference, gboolean value);
///
/// \return ����� �� ��������� ���������
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_set_pref_index(preference_p preference, preference_p value);
///
/// \return ����� �� ��������� ���������
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_set_update_index(preference_p preference, Tindex_executor value);
///
/// \return ����� �� ��������� ���������
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_set_update_index_user_data(preference_p preference, gpointer value);

/// \}

/// \name ������ �������
/// \{

/// ��������� �������������� ��������� � ���������� ����������
///
/// \param[in] value �������� ����� ��������������: 0 - �� ���������� ���������, �� 0 - ���������� ���������
///
/// \return ����� �� ��������� ���������
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_set_expert(preference_p preference, gboolean value);

/// ��������� ����� ������� ���������
///
/// \param[in] tags ������ ����� �������� ���������, � ������� ����������� �������� (���� ����������� ����� ����� ������ "����� � �������")
///
/// \return ����� �� ��������� ���������
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_set_tags(preference_p preference, gconstpchar tags);

/// \}

/// \name ��������� �������� ��������
/// \{

/// ��������� ������������ �������� ������������ (>= value)
///
/// \return ����� �� ��������� ��������� (preference)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_set_min_uint(preference_p preference, guint value);

/// ��������� ������������� �������� ������������ (<= value)
///
/// \return ����� �� ��������� ��������� (preference)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_set_max_uint(preference_p preference, guint value);

/// ��������� ������������ �������� ������������ (>= value)
///
/// \return ����� �� ��������� ��������� (preference)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_set_min_int64(preference_p preference, gint64 value);

/// ��������� ������������� �������� ������������ (<= value)
///
/// \return ����� �� ��������� ��������� (preference)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_set_max_int64(preference_p preference, gint64 value);

/// ��������� ������������ �������� ������������ (>= value)
///
/// \return ����� �� ��������� ��������� (preference)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_set_min_double(preference_p preference, gdouble value);

/// ��������� ������������� �������� ������������ (<= value)
///
/// \return ����� �� ��������� ��������� (preference)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_set_max_double(preference_p preference, gdouble value);

/// ��������� ������������ �������� ������������ (>= value)
///
/// \return ����� �� ��������� ��������� (preference)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_set_min_enum(preference_p preference, gint value);

/// ��������� ������������� �������� ������������ (<= value)
///
/// \return ����� �� ��������� ��������� (preference)
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_set_max_enum(preference_p preference, gint value);

/// \}

/// \name ������� ��������� �������� �� ����������
/// \{

/// ��������� ��������
///
extern "C" PREFS_API char * MSCU_CALL_PREFIX prefs_get_var_string(preference_p preference);
/// ��������� ������� ���������� ������
///
extern "C" PREFS_API guint MSCU_CALL_PREFIX prefs_get_var_string_size(preference_p preference);

/// ��������� ��������
///
extern "C" PREFS_API guint_p MSCU_CALL_PREFIX prefs_get_var_uint(preference_p preference);

/// ��������� ��������
///
extern "C" PREFS_API guint_p MSCU_CALL_PREFIX prefs_get_var_msec(preference_p preference);

/// ��������� ��������
///
extern "C" PREFS_API gint64_p MSCU_CALL_PREFIX prefs_get_var_int64(preference_p preference);

/// ��������� ��������
///
extern "C" PREFS_API gdouble_p MSCU_CALL_PREFIX prefs_get_var_double(preference_p preference);

/// ��������� ��������
///
extern "C" PREFS_API gboolean_p MSCU_CALL_PREFIX prefs_get_var_bool(preference_p preference);

/// ��������� ��������
///
extern "C" PREFS_API gint_p MSCU_CALL_PREFIX prefs_get_var_enum(preference_p preference);

/// ��������� ������������� ���������� ��������� (������)
///
extern "C" PREFS_API guint MSCU_CALL_PREFIX prefs_get_var_size_arr(preference_p preference);

/// ��������� �������� ���������� ��������� (������)
///
extern "C" PREFS_API guint_p MSCU_CALL_PREFIX prefs_get_var_count_arr(preference_p preference);

/// ��������� �������� (������)
///
extern "C" PREFS_API char * MSCU_CALL_PREFIX prefs_get_var_string_arr(preference_p preference, guint index);

/// ��������� �������� (������)
///
extern "C" PREFS_API guint_p MSCU_CALL_PREFIX prefs_get_var_uint_arr(preference_p preference, guint index);

/// ��������� �������� (������)
///
extern "C" PREFS_API guint_p MSCU_CALL_PREFIX prefs_get_var_msec_arr(preference_p preference, guint index);

/// ��������� �������� (������)
///
extern "C" PREFS_API gint64_p MSCU_CALL_PREFIX prefs_get_var_int64_arr(preference_p preference, guint index);

/// ��������� �������� (������)
///
extern "C" PREFS_API gdouble_p MSCU_CALL_PREFIX prefs_get_var_double_arr(preference_p preference, guint index);

/// ��������� �������� (������)
///
extern "C" PREFS_API gboolean_p MSCU_CALL_PREFIX prefs_get_var_bool_arr(preference_p preference, guint index);

/// ��������� �������� (������)
///
extern "C" PREFS_API gint_p MSCU_CALL_PREFIX prefs_get_var_enum_arr(preference_p preference, guint index);

/// \}

/// \name �����
/// \{

/// ����� ��������� �� �����
/// ����� ������� ���������� �� ���� ��������� �����������, ������� � owner
///
/// \param owner      ������-�������� - ��������� ������� ������ (NULL - ���� ����� ������ � �����)
/// \param name       ���������� ��� ��������� (������� ��� ������)
/// \param full_name  0  - � name ���������� ������� ��� ������ ������-��������� (����� �������� ������� ����� ����� ��������� �����)
///                   !0 - � name ���������� ������ ��� (��� ������ � �������� � ������� ���� <���_ini_������>.<�������_���>)
///
/// \return ����� �� ��������� ���������� ��������� (preference) ��� 0 � ������ ���������� ������
///
extern "C" PREFS_API preference_p MSCU_CALL_PREFIX prefs_find_preference(preference_p owner, gconstpchar name, gboolean full_path);

///\}

///\}

#endif
