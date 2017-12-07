// AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
// AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
// AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
// AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
//
// last update: 2010-10-12
//
// msculib_queue.h : Queue Manager
//
// Copyright (C) MSC, ORG 2009-2010
//

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#ifndef MSCULIB_QUEUE_H
#define MSCULIB_QUEUE_H

#if MSCU_OS_WINDOWS
//!!!сделать Wrapper и использовать
extern "C" MSCULIB_API gpointer  MSCU_CALL_PREFIX lfqueue_create(guint32 size);
extern "C" MSCULIB_API void      MSCU_CALL_PREFIX lfqueue_destroy(gpointer lfqueue);
extern "C" MSCULIB_API void      MSCU_CALL_PREFIX lfqueue_push(gpointer lfqueue, gpointer data, guint32 cmd);
extern "C" MSCULIB_API gpointer  MSCU_CALL_PREFIX lfqueue_pop(gpointer lfqueue, guint32* cmd, guint32 timeout);
extern "C" MSCULIB_API void      MSCU_CALL_PREFIX lfqueue_utilize(gpointer lfqueue);
extern "C" MSCULIB_API void      MSCU_CALL_PREFIX lfqueue_suspend(gpointer lfqueue, guint number_of_threads_to_wait);
extern "C" MSCULIB_API void      MSCU_CALL_PREFIX lfqueue_resume(gpointer lfqueue);
extern "C" MSCULIB_API void      MSCU_CALL_PREFIX lfqueue_pulse(gpointer lfqueue, guint number_of_threads_to_wait);
extern "C" MSCULIB_API guint32   MSCU_CALL_PREFIX lfqueue_size(gpointer lfqueue);
extern "C" MSCULIB_API guint32   MSCU_CALL_PREFIX lfqueue_locked(gpointer lfqueue);
#endif

#endif

