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
/// ��������� ��������������� �������� ����
/// ������� ������ ���� ������� ����� ������ ������� ������� log_file_add(log_file_add_utf8)
///
/// \param in path - ��������� �������� ��������������� �������� ����
///
/// ������� ���� ��-���������: <����_�_������������_�����>\<���_������������_�����>.logs
///
extern "C" MSCULIB_API void MSCU_CALL_PREFIX log_file_set_path(gconstpchar path);

/// ������ ��������� � log-����
/// ��� ������ ������ ������ �������:
///   ��������� ������� ���� (���� �� ����������)
///   ������ �������� ���� ��������� ��� ����� ������ 1 ������
///   ������ �������� ���� ��������� ����� � ������� �����
///   ������ ��������� ����� ��������� log-���� � ������ <���_������������_�����>.<����>.<�������_���_����������>.log.txt
///     ���� ������ ��� ��� ������ - ���������� ��������� ��������� ��� � ����������� ��������
///
/// ��� ������ ������ ����� ���������� (msg) �����������:
///   ������� ����
///   ������� �����
///   ������, ������������ ��� ��������� (MT_INFORMATION: "~", MT_ERROR: "!", MT_WARNING: "?", MT_PROCESS: "<", MT_RESULT: ">", MT_DEBUG: "@")
///
/// \param in msg - ������ � ����������
/// \param in msg_type - ��� ��������� (��������� MT_XXX, ����� MT_PROGRESS_BEGIN, MT_PROGRESS, MT_PROGRESS_END, ������� � mscu_types.h)
///
/// ���������/������������� ������������� - ����� msculib_set_klog_std_event/klogf/klog (��. msculib.h)
extern "C" MSCULIB_API void MSCU_CALL_PREFIX log_file_add(gconstpchar msg, gint msg_type);
// this is UTF-8 version of the above function
// msg should have UTF-8 encoding
extern "C" MSCULIB_API void MSCU_CALL_PREFIX log_file_add_utf8(gconstpchar msg, gint msg_type);

//////////////////////////////////////////////////////////////////////////

#endif

