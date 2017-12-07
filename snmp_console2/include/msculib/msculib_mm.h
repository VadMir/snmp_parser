/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/*
 * last update: 2009-05-21
 *
 * mscu_mm.h : Memory Manager
 *
 * Copyright (C) MSC, ORG 2009
 */

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#ifndef MSCULIB_MM_H
#define MSCULIB_MM_H

//////////////////////////////////////////////////////////////////////////
extern "C" MSCULIB_API void MSCU_CALL_PREFIX memory_managers_cancel_greedy_mode();

//////////////////////////////////////////////////////////////////////////
extern "C" MSCULIB_API gpointer MSCU_CALL_PREFIX memory_manager_create(guint32 size);
extern "C" MSCULIB_API void MSCU_CALL_PREFIX memory_manager_destroy(gpointer memory_manager);
extern "C" MSCULIB_API gpointer MSCU_CALL_PREFIX memory_manager_alloc(gpointer memory_manager);
extern "C" MSCULIB_API void MSCU_CALL_PREFIX memory_manager_free(gpointer memory_manager, gpointer mem);
extern "C" MSCULIB_API void MSCU_CALL_PREFIX memory_manager_memory_status(gpointer memory_manager, gint64* busy, gint64* netto, gint64* brutto, gboolean increment);
extern "C" MSCULIB_API void MSCU_CALL_PREFIX memory_manager_status_blocks(gpointer memory_manager, guint32* quanta, guint32* pool_size, guint32* pool_count, guint32* blocks_busy, guint32* blocks_all, gdouble* blocks_busy_percent);
// 2017-01-18
// set up name for the memory manager messages
extern "C" MSCULIB_API gpointer MSCU_CALL_PREFIX memory_manager_set_name(gpointer memory_manager, gconstpchar name);

// 2017-07-26
// returns name for the memory manager messages
extern "C" MSCULIB_API gconstpchar MSCU_CALL_PREFIX memory_manager_get_name(gpointer memory_manager);

// 2017-07-26
// callback function for enumeration procedures
//
// user_data - second parameter for memory_managers_enum function
// memory_manager - memory_manager to work with, actual within given function call only
typedef void (MSCU_CALL_PREFIX *Tmemory_manager_enum_callback_t)(gpointer user_data, gpointer memory_manager);

// 2017-07-26
// enumerates actual memory managers, created with memory_manager_create function
// user_data - is passed as first parameter to the memory_manager_enum_callback function
// all memory_manager pointers passed memory_manager_enum_callback are actual within given function call only
extern "C" MSCULIB_API void MSCU_CALL_PREFIX memory_managers_enum(Tmemory_manager_enum_callback_t memory_manager_enum_callback, gpointer user_data);

namespace mscu {
  namespace mm {

    class LOCAL_API  TMemoryManagerWrapper {
    private:
      TMemoryManagerWrapper& operator=(const TMemoryManagerWrapper& /*rhs*/) {};
    public:
      TMemoryManagerWrapper(): instance_(0) {};
      TMemoryManagerWrapper(gpointer instance): instance_(instance) {};
      virtual ~TMemoryManagerWrapper()
      {
        reset();
      };

      gpointer instance()
      {
        return instance_;
      }

      void reset()
      {
        if (instance_)
          memory_manager_destroy(instance_);
      }
    private:
      gpointer instance_;
    };

  }
}

//////////////////////////////////////////////////////////////////////////
extern "C" MSCULIB_API gpointer MSCU_CALL_PREFIX range_memory_manager_create(guint32 size_min, guint32 size_max);
extern "C" MSCULIB_API void MSCU_CALL_PREFIX range_memory_manager_destroy(gpointer memory_manager);
extern "C" MSCULIB_API guint32 MSCU_CALL_PREFIX range_memory_manager_adjust_len(gpointer memory_manager, guint32 size);
extern "C" MSCULIB_API gpointer MSCU_CALL_PREFIX range_memory_manager_alloc(gpointer memory_manager, guint32 size);
extern "C" MSCULIB_API gpointer MSCU_CALL_PREFIX range_memory_manager_realloc(gpointer memory_manager, gpointer mem, guint32 new_size);
extern "C" MSCULIB_API void MSCU_CALL_PREFIX range_memory_manager_free(gpointer memory_manager, gpointer mem);
extern "C" MSCULIB_API guint32 MSCU_CALL_PREFIX range_memory_manager_pool_set_count(gpointer memory_manager);
extern "C" MSCULIB_API void MSCU_CALL_PREFIX range_memory_manager_memory_status(gpointer memory_manager, gint64* busy, gint64* netto, gint64* brutto, gboolean increment);
extern "C" MSCULIB_API void MSCU_CALL_PREFIX range_memory_manager_status_blocks(gpointer memory_manager, guint32* quanta, guint32* pool_size, guint32* pool_count, guint32* blocks_busy, guint32* blocks_all, gdouble* blocks_busy_percent);
// 2017-07-27
// set up name for the memory manager messages
extern "C" MSCULIB_API gpointer MSCU_CALL_PREFIX range_memory_manager_set_name(gpointer memory_manager, gconstpchar name);
// returns name for the memory manager messages
extern "C" MSCULIB_API gconstpchar MSCU_CALL_PREFIX range_memory_manager_get_name(gpointer memory_manager);
// enumerates actual memory managers, created with range_memory_manager_create function
// user_data - is passed as first parameter to the memory_manager_enum_callback function
// all memory_manager pointers passed memory_manager_enum_callback are actual within given function call only
extern "C" MSCULIB_API void MSCU_CALL_PREFIX range_memory_managers_enum(Tmemory_manager_enum_callback_t memory_manager_enum_callback, gpointer user_data);

namespace mscu {
  namespace mm {

    class LOCAL_API  TRangeMemoryManagerWrapper {
    private:
      TRangeMemoryManagerWrapper& operator=(const TRangeMemoryManagerWrapper& /*rhs*/) {};
    public:
      TRangeMemoryManagerWrapper(): instance_(0) {};
      TRangeMemoryManagerWrapper(gpointer instance): instance_(instance) {};
      virtual ~TRangeMemoryManagerWrapper()
      {
        reset();
      };

      gpointer instance()
      {
        return instance_;
      }

      void reset()
      {
        if (instance_)
          range_memory_manager_destroy(instance_);
      }
    private:
      gpointer instance_;
    };

  }
}

//////////////////////////////////////////////////////////////////////////
extern "C" MSCULIB_API gpointer MSCU_CALL_PREFIX aligned_memory_manager_create(guint32 size);
extern "C" MSCULIB_API void MSCU_CALL_PREFIX aligned_memory_manager_destroy(gpointer memory_manager);
extern "C" MSCULIB_API gpointer MSCU_CALL_PREFIX aligned_memory_manager_alloc(gpointer memory_manager, gpointer* descriptor);
extern "C" MSCULIB_API void MSCU_CALL_PREFIX aligned_memory_manager_free(gpointer memory_manager, gpointer mem, gpointer* descriptor);
extern "C" MSCULIB_API void MSCU_CALL_PREFIX aligned_memory_manager_memory_status(gpointer memory_manager, gint64* busy, gint64* netto, gint64* brutto, gboolean increment);
extern "C" MSCULIB_API void MSCU_CALL_PREFIX aligned_memory_manager_status_blocks(gpointer memory_manager, guint32* quanta, guint32* pool_size, guint32* pool_count, guint32* blocks_busy, guint32* blocks_all, gdouble* blocks_busy_percent);
// 2017-07-27
// set up name for the memory manager messages
extern "C" MSCULIB_API gpointer MSCU_CALL_PREFIX aligned_memory_manager_set_name(gpointer memory_manager, gconstpchar name);
// returns name for the memory manager messages
extern "C" MSCULIB_API gconstpchar MSCU_CALL_PREFIX aligned_memory_manager_get_name(gpointer memory_manager);
// enumerates actual memory managers, created with aligned_memory_manager_create function
// user_data - is passed as first parameter to the memory_manager_enum_callback function
// all memory_manager pointers passed memory_manager_enum_callback are actual within given function call only
extern "C" MSCULIB_API void MSCU_CALL_PREFIX aligned_memory_managers_enum(Tmemory_manager_enum_callback_t memory_manager_enum_callback, gpointer user_data);

namespace mscu {
  namespace mm {

    class LOCAL_API  TAlignedMemoryManagerWrapper {
    private:
      TAlignedMemoryManagerWrapper& operator=(const TAlignedMemoryManagerWrapper& /*rhs*/) {};
    public:
      TAlignedMemoryManagerWrapper(): instance_(0) {};
      TAlignedMemoryManagerWrapper(gpointer instance): instance_(instance) {};
      virtual ~TAlignedMemoryManagerWrapper()
      {
        reset();
      };

      gpointer instance()
      {
        return instance_;
      }

      void reset()
      {
        if (instance_)
          aligned_memory_manager_destroy(instance_);
      }
    private:
      gpointer instance_;
    };

  }
}

//////////////////////////////////////////////////////////////////////////
extern "C" MSCULIB_API gpointer MSCU_CALL_PREFIX aligned_range_memory_manager_create(guint32 size_min, guint32 size_max);
extern "C" MSCULIB_API void     MSCU_CALL_PREFIX aligned_range_memory_manager_destroy(gpointer memory_manager);
extern "C" MSCULIB_API guint32  MSCU_CALL_PREFIX aligned_range_memory_manager_adjust_len(gpointer memory_manager, guint32 size);
extern "C" MSCULIB_API gpointer MSCU_CALL_PREFIX aligned_range_memory_manager_alloc(gpointer memory_manager, guint32 size, gpointer* descriptor);
extern "C" MSCULIB_API gpointer MSCU_CALL_PREFIX aligned_range_memory_manager_realloc(gpointer memory_manager, gpointer mem, gpointer* descriptor, guint32 new_size, gpointer* new_descriptor);
extern "C" MSCULIB_API void     MSCU_CALL_PREFIX aligned_range_memory_manager_free(gpointer memory_manager, gpointer mem, gpointer* descriptor);
extern "C" MSCULIB_API guint32  MSCU_CALL_PREFIX aligned_range_memory_manager_pool_set_count(gpointer memory_manager);
extern "C" MSCULIB_API void     MSCU_CALL_PREFIX aligned_range_memory_manager_memory_status(gpointer memory_manager, gint64* busy, gint64* netto, gint64* brutto, gboolean increment);
extern "C" MSCULIB_API void     MSCU_CALL_PREFIX aligned_range_memory_manager_status_blocks(gpointer memory_manager, guint32* quanta, guint32* pool_size, guint32* pool_count, guint32* blocks_busy, guint32* blocks_all, gdouble* blocks_busy_percent);
// 2017-07-27
// set up name for the memory manager messages
extern "C" MSCULIB_API gpointer MSCU_CALL_PREFIX aligned_range_memory_manager_set_name(gpointer memory_manager, gconstpchar name);
// returns name for the memory manager messages
extern "C" MSCULIB_API gconstpchar MSCU_CALL_PREFIX aligned_range_memory_manager_get_name(gpointer memory_manager);
// enumerates actual memory managers, created with aligned_range_memory_manager_create function
// user_data - is passed as first parameter to the memory_manager_enum_callback function
// all memory_manager pointers passed memory_manager_enum_callback are actual within given function call only
extern "C" MSCULIB_API void MSCU_CALL_PREFIX aligned_range_memory_managers_enum(Tmemory_manager_enum_callback_t memory_manager_enum_callback, gpointer user_data);

namespace mscu {
  namespace mm {

    class LOCAL_API  TAlignedRangeMemoryManagerWrapper {
    private:
      TAlignedRangeMemoryManagerWrapper& operator=(const TAlignedRangeMemoryManagerWrapper& /*rhs*/) {};
    public:
      TAlignedRangeMemoryManagerWrapper(): instance_(0) {};
      TAlignedRangeMemoryManagerWrapper(gpointer instance): instance_(instance) {};
      virtual ~TAlignedRangeMemoryManagerWrapper()
      {
        reset();
      };

      gpointer instance()
      {
        return instance_;
      }

      void reset()
      {
        if (instance_)
          aligned_range_memory_manager_destroy(instance_);
      }
    private:
      gpointer instance_;
    };

  }
}

//////////////////////////////////////////////////////////////////////////
extern "C" MSCULIB_API gpointer MSCU_CALL_PREFIX swap_aligned_range_memory_manager_create(guint Asize_min, guint Asize_max, gint64 commit, gconstpchar swap_dir, gconstpchar prio_swap_dir, gint64 prio_swap_dir_size);
extern "C" MSCULIB_API void     MSCU_CALL_PREFIX swap_aligned_range_memory_manager_destroy(gpointer memory_manager);
extern "C" MSCULIB_API guint32  MSCU_CALL_PREFIX swap_aligned_range_memory_manager_adjust_len(gpointer memory_manager, guint32 size);
extern "C" MSCULIB_API gpointer MSCU_CALL_PREFIX swap_aligned_range_memory_manager_alloc(gpointer memory_manager, guint32 size, gpointer* descriptor);
extern "C" MSCULIB_API gpointer MSCU_CALL_PREFIX swap_aligned_range_memory_manager_realloc(gpointer memory_manager, gpointer mem, gpointer* descriptor, guint32 new_size, gpointer* new_descriptor);
extern "C" MSCULIB_API void     MSCU_CALL_PREFIX swap_aligned_range_memory_manager_free(gpointer memory_manager, gpointer mem, gpointer* descriptor);
extern "C" MSCULIB_API void     MSCU_CALL_PREFIX swap_aligned_range_memory_manager_suspend(gpointer memory_manager, gpointer* mem, gpointer* descriptor);
extern "C" MSCULIB_API void     MSCU_CALL_PREFIX swap_aligned_range_memory_manager_resume(gpointer memory_manager, gpointer* mem, gpointer* descriptor);
extern "C" MSCULIB_API void     MSCU_CALL_PREFIX swap_aligned_range_memory_manager_status_blocks_color(gpointer memory_manager, guint32* blocks_memory, guint32* blocks_fly, guint32* blocks_disk, gint64* blocks_memory_bytes, gint64* blocks_fly_bytes, gint64* blocks_disk_bytes);
extern "C" MSCULIB_API void     MSCU_CALL_PREFIX swap_aligned_range_memory_manager_io_status(gpointer memory_manager, guint32* io_read_ops, guint32* io_write_ops, guint32* io_errors);
extern "C" MSCULIB_API guint32  MSCU_CALL_PREFIX swap_aligned_range_memory_manager_pool_set_count(gpointer memory_manager);
extern "C" MSCULIB_API void     MSCU_CALL_PREFIX swap_aligned_range_memory_manager_memory_status(gpointer memory_manager, gint64* busy, gint64* netto, gint64* brutto, gboolean increment);
extern "C" MSCULIB_API void     MSCU_CALL_PREFIX swap_aligned_range_memory_manager_status_blocks(gpointer memory_manager, guint32* quanta, guint32* pool_size, guint32* pool_count, guint32* blocks_busy, guint32* blocks_all, gdouble* blocks_busy_percent);
extern "C" MSCULIB_API guint32  MSCU_CALL_PREFIX swap_aligned_range_memory_manager_swap_pool_set_count(gpointer memory_manager);
extern "C" MSCULIB_API void     MSCU_CALL_PREFIX swap_aligned_range_memory_manager_swap_status(gpointer memory_manager, gint64* busy, gint64* netto, gint64* brutto, gboolean increment);
extern "C" MSCULIB_API void     MSCU_CALL_PREFIX swap_aligned_range_memory_manager_swap_status_blocks(gpointer memory_manager, guint32* quanta, guint32* pool_size, guint32* pool_count, guint32* blocks_busy, guint32* blocks_all, gdouble* blocks_busy_percent);
extern "C" MSCULIB_API guint32  MSCU_CALL_PREFIX swap_aligned_range_memory_manager_swap_prio_pool_set_count(gpointer memory_manager);
extern "C" MSCULIB_API void     MSCU_CALL_PREFIX swap_aligned_range_memory_manager_swap_prio_status(gpointer memory_manager, gint64* busy, gint64* netto, gint64* brutto, gboolean increment);
extern "C" MSCULIB_API void     MSCU_CALL_PREFIX swap_aligned_range_memory_manager_swap_prio_status_blocks(gpointer memory_manager, guint32* quanta, guint32* pool_size, guint32* pool_count, guint32* blocks_busy, guint32* blocks_all, gdouble* blocks_busy_percent);
// 2017-07-27
// set up name for the memory manager messages
extern "C" MSCULIB_API gpointer MSCU_CALL_PREFIX swap_aligned_range_memory_manager_set_name(gpointer memory_manager, gconstpchar name);
// returns name for the memory manager messages
extern "C" MSCULIB_API gconstpchar MSCU_CALL_PREFIX swap_aligned_range_memory_manager_get_name(gpointer memory_manager);
// enumerates actual memory managers, created with swap_aligned_range_memory_manager_create function
// user_data - is passed as first parameter to the memory_manager_enum_callback function
// all memory_manager pointers passed memory_manager_enum_callback are actual within given function call only
extern "C" MSCULIB_API void MSCU_CALL_PREFIX swap_aligned_range_memory_managers_enum(Tmemory_manager_enum_callback_t memory_manager_enum_callback, gpointer user_data);

namespace mscu {
  namespace mm {

    class LOCAL_API  TSwapAlignedRangeMemoryManagerWrapper {
    private:
      TSwapAlignedRangeMemoryManagerWrapper& operator=(const TSwapAlignedRangeMemoryManagerWrapper& /*rhs*/) {};
    public:
      TSwapAlignedRangeMemoryManagerWrapper(): instance_(0) {};
      TSwapAlignedRangeMemoryManagerWrapper(gpointer instance): instance_(instance) {};
      virtual ~TSwapAlignedRangeMemoryManagerWrapper()
      {
        reset();
      };

      gpointer instance()
      {
        return instance_;
      }

      void reset()
      {
        if (instance_)
          swap_aligned_range_memory_manager_destroy(instance_);
      }
    private:
      gpointer instance_;
    };

  }
}

#endif

