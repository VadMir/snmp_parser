/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/*
 * last update: 2007-06-05
 *
 * mscu_time.h : time.
 *
 * Copyright (C) MSC, ORG 2007
 */

#pragma once

#ifndef MSCULIB_TIME_H
#define MSCULIB_TIME_H

extern "C" MSCULIB_API guint32 MSCU_CALL_PREFIX mscu_global_msecs();

// this function is deprecated, use _utc instead
extern "C" MSCULIB_API guint64 MSCU_CALL_PREFIX mscu_global_msecs_abs_0(); // now _0-function are equal to _utc
// this function is deprecated, use _utc instead
extern "C" MSCULIB_API guint64 MSCU_CALL_PREFIX mscu_global_usecs_abs_0(); // now _0-function are equal to _utc

// Get local time as milliseconds since 00:00:00, Jan 1st 1970
extern "C" MSCULIB_API guint64 MSCU_CALL_PREFIX mscu_global_msecs_abs_utc();
// Get local time as microseconds since 00:00:00, Jan 1st 1970
extern "C" MSCULIB_API guint64 MSCU_CALL_PREFIX mscu_global_usecs_abs_utc();

// this functions does not work already
extern "C" MSCULIB_API void MSCU_CALL_PREFIX one_second_flag_register(gint32* flag);
extern "C" MSCULIB_API void MSCU_CALL_PREFIX one_second_flag_unregister(gint32* flag);

// milliseconds
extern "C" MSCULIB_API void MSCU_CALL_PREFIX mscu_sleep(guint msecs);

///

extern "C" MSCULIB_API void MSCU_CALL_PREFIX mscu_timeval_get(Ttimeval * tv);
extern "C" MSCULIB_API void MSCU_CALL_PREFIX mscu_get_local_time(tm * now);
extern "C" MSCULIB_API void MSCU_CALL_PREFIX mscu_get_local_time_with_msec(tm * now, int * msec);

// utility c++ classes

#ifdef __cplusplus

#include <math.h>

// this class should be deprecated, use TIdleAutoresetEvent instead
class LOCAL_API TOneSecondEvent {
public:
	TOneSecondEvent()
	{
    last_msecs_ = mscu_global_msecs_abs_utc();
	}

  bool get_autoreset()
  {
    guint64 now_msecs = mscu_global_msecs_abs_utc();
    if ((now_msecs - last_msecs_) >= 1000) {
			last_msecs_ = now_msecs;
			return true;
    }
    return false;
  }

private:
  guint64 last_msecs_;
};

// just like class before, but 100 ms against 1 sesond
class LOCAL_API TIdleAutoresetEvent {
public:
	TIdleAutoresetEvent(size_t interval_msecs = 100): interval_msecs_(interval_msecs)
	{
    last_msecs_ = mscu_global_msecs_abs_utc();
	}

  bool get_autoreset()
  {
    guint64 now_msecs = mscu_global_msecs_abs_utc();
    if ((now_msecs - last_msecs_) >= interval_msecs_) {
			last_msecs_ = now_msecs;
			return true;
    }
    return false;
  }

private:
	size_t interval_msecs_;
  guint64 last_msecs_;
};

///

class LOCAL_API TSpeedRestrictor {
public:
	TSpeedRestrictor(): rt_(rtNone) {}

	void set(guint32 packets, guint32 msecs)
	{
		rt_ = rtPackets;

		restriction_packets_ = packets;
		restriction_msecs_ = msecs;

		restrict_delay_counter = 0;
	}

  // speed as bytes per second
	void set(guint32 speed)
	{
		rt_ = rtSpeed;

		restriction_speed_ = speed;

		restrict_bytes = 0;
		restrict_packets = 0;
		restrict_ticks = mscu_global_msecs();
		restrict_addon = 1;
		restrict_addon_accum = 0;
		restrict_multiply = 1;
		restrict_multiply_ticks = 0;
	}

	void set()
	{
		rt_ = rtLibpcap;

		first_microsecs_file = 0;
		first_microsecs_real = 0;
	}

  // one packet follow
	void tick(guint32 packet_size, Ttimeval& tv)
	{
		guint32 t;

		switch (rt_) {
		case rtSpeed:
			if (!restriction_speed_)
				return;

			// do the waiting
			if (restrict_addon > 0) {
				++restrict_multiply_ticks;
				if (restrict_multiply_ticks >= restrict_multiply) {
					restrict_multiply_ticks = 0;
					mscu_sleep(restrict_addon);
					restrict_addon_accum += restrict_addon;
				}
			}

			// update counters
			++restrict_packets;
			restrict_bytes += packet_size;

			// do the correction
			t = mscu_global_msecs();
			if (t >= restrict_ticks) {
				guint32 delta = t - restrict_ticks;
				if (delta > 1000) { // 1000 milliseconds elapsed
					gint64 spd = restrict_bytes * 1000 / delta;
					guint32 awaited_delta = guint32(1000 * restrict_bytes / restriction_speed_);

					guint32 total_sleep_msecs;
					gdouble divider;
					if (spd > restriction_speed_) { // speed overflow - do the correction
						guint32 addon_delta = awaited_delta - delta;
						total_sleep_msecs = restrict_addon_accum + addon_delta;

						divider = (total_sleep_msecs + (delta - restrict_addon_accum)) / 1000.0;// number of seconds
						if (divider > 0.1) {
							restrict_addon = (guint32)floor(total_sleep_msecs / divider);
							restrict_multiply = (guint32)floor(restrict_packets / divider);
						}
					} else if ((restrict_addon > 0) && (spd < restriction_speed_)) { // may be too large fading?
						guint32 subtract_delta = delta - awaited_delta;

						if (subtract_delta < restrict_addon_accum)
							total_sleep_msecs = restrict_addon_accum - subtract_delta;
						else// no need to sleep
							total_sleep_msecs = 0;

						if (total_sleep_msecs == 0) { // no need to sleep
							restrict_addon = 0;
							restrict_multiply = 1;
						} else {
							divider = (total_sleep_msecs + (delta - restrict_addon_accum)) / 1000.0; // number of seconds
							if (divider > 0.1) {
								restrict_addon = (guint32)floor(total_sleep_msecs / divider);
								restrict_multiply = (guint32)floor(restrict_packets / divider);
							}
						}
					}

					if ((restrict_addon > 5) && (restrict_multiply > 5)) { // gain the time precision
						restrict_addon = restrict_addon / 5;
						restrict_multiply = restrict_multiply / 5;
					} else if ((restrict_addon > 4) && (restrict_multiply > 4)) { // gain the time precision
						restrict_addon = restrict_addon / 4;
						restrict_multiply = restrict_multiply / 4;
					} else if ((restrict_addon > 3) && (restrict_multiply > 3)) { // gain the time precision
						restrict_addon = restrict_addon / 3;
						restrict_multiply = restrict_multiply / 3;
					} else if ((restrict_addon > 2) && (restrict_multiply > 2)) { // gain the time precision
						restrict_addon = restrict_addon / 2;
						restrict_multiply = restrict_multiply / 2;
					}

					// reset the counters
					restrict_packets = 0;
					restrict_bytes = 0;
					restrict_ticks = t;
					restrict_addon_accum = 0;
				}
			} else // overflow - correct timings
				restrict_ticks = t;

			break;
		case rtPackets:
			if ((restrict_delay_counter = (restrict_delay_counter + 1) % restriction_packets_) == 0)
				mscu_sleep(restriction_msecs_);
			break;
		case rtLibpcap: {
			guint64 tv_microsecs = guint64(tv.tv_sec) * 1000000 + guint64(tv.tv_usec);

			if (first_microsecs_file == 0) {
				first_microsecs_file = tv_microsecs;
				first_microsecs_real = mscu_global_usecs_abs_utc();
			} else {
				if (tv_microsecs > first_microsecs_file) {
					guint64 microsecs_real = mscu_global_usecs_abs_utc();
					guint64 microsecs_real_for_packet = first_microsecs_real + (tv_microsecs - first_microsecs_file);
					if (microsecs_real_for_packet > microsecs_real) { // we must wait
						guint64 millisecs_to_wait = (microsecs_real_for_packet - microsecs_real) / 1000;
						if (millisecs_to_wait > 0)
							mscu_sleep(guint(millisecs_to_wait < 60000 ? millisecs_to_wait : 60000));
					}
				}
			}

		} break;
		default: // rtNone
			break;
		}
	}

private:
  enum TRestrictionType {
    rtNone,
    rtSpeed,
    rtPackets,
    rtLibpcap
  };

  TRestrictionType rt_;
  guint32 restriction_packets_;
  guint32 restriction_msecs_;
  guint32 restriction_speed_;

  guint64 first_microsecs_file;
  guint64 first_microsecs_real;

  // speed restrictor
  gint64 restrict_bytes;
  gint64 restrict_packets;
  guint32 restrict_ticks;
  guint32 restrict_addon; // millisec for waiting
  guint32 restrict_addon_accum; // millisec for waiting
  guint32 restrict_multiply; // count after waiting
  guint32 restrict_multiply_ticks; // current value of count after waiting
  // packets restrictor
  gint64 restrict_delay_counter; // packets/msecs mode
};

#endif

#endif

