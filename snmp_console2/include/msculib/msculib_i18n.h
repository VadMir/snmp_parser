/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/*
 * last update: 2012-01-06
 *
 * mscu_i18n.h : Internationalization
 *
 * Copyright (C) MSC, ORG 2012
 */

#pragma once

#ifndef MSCULIB_I18N_H
#define MSCULIB_I18N_H

//////////////////////////////////////////////////////////////////////////
extern "C" MSCULIB_API gboolean MSCU_CALL_PREFIX mscu_i18n_en();

#define _ENRU(a, b) (mscu_i18n_en() ? (a) : (b))

#define _EN mscu_i18n_en()

extern "C" MSCULIB_API void MSCU_CALL_PREFIX mscu_i18n_parse_cmd_line(int argc, char* argv[]);

//////////////////////////////////////////////////////////////////////////

#endif

