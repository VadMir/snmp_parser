/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/*
* last update: 2008-11-26
*
* mscu_filereader.h : TFileReader.
*
* Copyright (C) MSC, ORG 2007-2008
*/

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#ifndef MSCULIB_FILEREADER_H
#define MSCULIB_FILEREADER_H

//////////////////////////////////////////////////////////////////////////
//!!!сделать Wrapper и использовать
extern "C" MSCULIB_API gpointer     MSCU_CALL_PREFIX file_reader_create();
extern "C" MSCULIB_API void         MSCU_CALL_PREFIX file_reader_destroy(gpointer filereader);
extern "C" MSCULIB_API void         MSCU_CALL_PREFIX file_reader_open(gpointer filereader, gconstpchar url);
extern "C" MSCULIB_API void         MSCU_CALL_PREFIX file_reader_reset(gpointer filereader);
extern "C" MSCULIB_API void         MSCU_CALL_PREFIX file_reader_close(gpointer filereader);
extern "C" MSCULIB_API void         MSCU_CALL_PREFIX file_reader_read_buffer(gpointer filereader, gpointer buffer, guint len);
extern "C" MSCULIB_API void         MSCU_CALL_PREFIX file_reader_skip_buffer(gpointer filereader, guint len);
extern "C" MSCULIB_API void         MSCU_CALL_PREFIX file_reader_read_buffer_lazy(gpointer filereader, gpointer buffer, guint* len);
extern "C" MSCULIB_API void         MSCU_CALL_PREFIX file_reader_skip_buffer_lazy(gpointer filereader, guint* len);
extern "C" MSCULIB_API void         MSCU_CALL_PREFIX file_reader_read_buffer_lock(gpointer filereader, gpointer* buffer, guint* len);
extern "C" MSCULIB_API void         MSCU_CALL_PREFIX file_reader_read_buffer_unlock(gpointer filereader);
extern "C" MSCULIB_API gboolean     MSCU_CALL_PREFIX file_reader_empty(gpointer filereader);
extern "C" MSCULIB_API gconstpchar  MSCU_CALL_PREFIX file_reader_url(gpointer filereader);
extern "C" MSCULIB_API gint64       MSCU_CALL_PREFIX file_reader_size(gpointer filereader);
extern "C" MSCULIB_API gint64       MSCU_CALL_PREFIX file_reader_position(gpointer filereader);
extern "C" MSCULIB_API gint64       MSCU_CALL_PREFIX file_reader_rest(gpointer filereader);

#endif

