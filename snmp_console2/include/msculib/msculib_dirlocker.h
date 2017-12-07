/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/*
* last update: 2008-10-05
*
* mscu_dirlocker.h : Directory Locker
*
* Copyright (C) MSC, ORG 2007-2008
*/

#pragma once

#ifndef MSCULIB_DIRLOCKER_H
#define MSCULIB_DIRLOCKER_H

//////////////////////////////////////////////////////////////////////////
// TDirectoryLockerFlag
const guint DL_CLEAR_BEFORE = 0x01; // очистсить перед использованием
const guint DL_CLEAR_AFTER  = 0x02; // очистить после использования
const guint DL_DELETE_AFTER = 0x04; // удалить после использования

//////////////////////////////////////////////////////////////////////////
//!!!сделать Wrapper и использовать
extern "C" MSCULIB_API gpointer MSCU_CALL_PREFIX directory_locker_create(const char* initial_name, guint Flags);
extern "C" MSCULIB_API void     MSCU_CALL_PREFIX directory_locker_destroy(gpointer dirlocker);
extern "C" MSCULIB_API void     MSCU_CALL_PREFIX directory_locker_set_parameters(gpointer dirlocker, guint32 Agranularity, guint32 Agranularity_ring, gboolean Adatetime_in_filename, const char* Asubdivision_prefix, const char* Asubdivision_index, const char* Aunique_ident);
extern "C" MSCULIB_API gboolean MSCU_CALL_PREFIX directory_locker_acquire_filename(gpointer dirlocker, const char* subdirectory, gboolean with_granularity, char* filename);
extern "C" MSCULIB_API gboolean MSCU_CALL_PREFIX directory_locker_acquire_filename_with_addon(gpointer dirlocker, const char* subdirectory, gboolean with_granularity, char* filename, const char* addon);
extern "C" MSCULIB_API gboolean MSCU_CALL_PREFIX directory_locker_has_error(gpointer dirlocker);
extern "C" MSCULIB_API const    char* MSCU_CALL_PREFIX directory_locker_error_message(gpointer dirlocker);
extern "C" MSCULIB_API const    char* MSCU_CALL_PREFIX directory_locker_base_name(gpointer dirlocker);
//////////////////////////////////////////////////////////////////////////

#endif

