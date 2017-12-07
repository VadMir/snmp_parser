/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/*
 * last update: 2015-03-20
 *
 * msculib_log.h : File logger functions
 *
 * Copyright (C) MSC, ORG 2007-2015
 */

#pragma once

#ifndef MSCULIB_LOG_H
#define MSCULIB_LOG_H

//////////////////////////////////////////////////////////////////////////
/// установка альтернативного базового пути
/// функци€ должна быть вызвана перед первым вызовом функции log_file_add(log_file_add_utf8)
///
/// \param in path - строковое значение альтернативного базового пути
///
/// базовый путь по-умолчанию: <путь_к_исполн€емому_файлу>\<им€_исполн€емого_файла>.logs
///
extern "C" MSCULIB_API void MSCU_CALL_PREFIX log_file_set_path(gconstpchar path);

/// запись сообщени€ в log-файл
/// при первом вызове данной функции:
///   создаетс€ базовый путь (если не существует)
///   внутри базового пути удал€ютс€ все файлы старше 1 мес€ца
///   внутри базового пути создаетс€ папка с текущей датой
///   внутри созданной папки создаетс€ log-файл с именем <им€_исполн€емого_файла>.<дата>.<сетевое_им€_компьютера>.log.txt
///     если данное им€ уже зан€то - выбираетс€ следующее доступное им€ с инкрементом счетчика
///
/// при записи строки перед сообщением (msg) вставл€етс€:
///   текуща€ дата
///   текущее врем€
///   символ, определ€ющий тип сообщени€ (MT_INFORMATION: "~", MT_ERROR: "!", MT_WARNING: "?", MT_PROCESS: "<", MT_RESULT: ">", MT_DEBUG: "@")
///
/// \param in msg - строка с сообщением
/// \param in msg_type - тип сообщени€ (константы MT_XXX, кроме MT_PROGRESS_BEGIN, MT_PROGRESS, MT_PROGRESS_END, описаны в mscu_types.h)
///
/// возможное/рекомендуемое использование - через msculib_set_klog_std_event/klogf/klog (см. msculib.h)
extern "C" MSCULIB_API void MSCU_CALL_PREFIX log_file_add(gconstpchar msg, gint msg_type);
// this is UTF-8 version of the above function
// msg should have UTF-8 encoding
extern "C" MSCULIB_API void MSCU_CALL_PREFIX log_file_add_utf8(gconstpchar msg, gint msg_type);

//////////////////////////////////////////////////////////////////////////

#endif

