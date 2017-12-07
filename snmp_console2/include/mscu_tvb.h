/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/// \file mscu_tvb.h
/// \mainpage
/// @{
/// \section attention Предупреждение
/// \b ВНИМАНИЕ! Файл <b>"mscu_tvb.h"</b> распространяется под авторским правом РАЗРАБОТЧИКА данного файла.
/// Любые изменения в данном файле СТОРОННИМИ разработчиками НЕДОПУСТИМЫ.
/// Для использования данного файла просто включите его в проект с помощью директивы #include.
///
/// \section updated Последнее обновление
/// <b>2014-05-23</b>
///
/// \section changelog Изменения
/// - [*] 2014-05-23 - добавлены g_XtoXX-функции с offset-параметром
///
/// \section description Описание
/// trully virtual buffer and auxiliary retrieval functions.
///
/// \section copyright Авторские права
/// Copyright (C) MSC, ORG 2002-2014
///
/// @}

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#ifndef MSCU_TVB_H
#define MSCU_TVB_H

#include "mscu_types.h"

//////////////////////////////////////////////////////////////////////////
/* Pointer versions of g_ntohs and g_ntohl.  Given a pointer to a member of a
 * byte array, returns the value of the two or four bytes at the pointer.
 * The pletohXX versions return the little-endian representation.
 */

#define pntoh16(p)  ((guint16)                       \
                     ((guint16)*((const guint8 *)(p)+0)<<8|  \
                      (guint16)*((const guint8 *)(p)+1)<<0))

#define pntoh24(p)  ((guint32)*((const guint8 *)(p)+0)<<16|  \
                     (guint32)*((const guint8 *)(p)+1)<<8|   \
                     (guint32)*((const guint8 *)(p)+2)<<0)

#define pntoh32(p)  ((guint32)*((const guint8 *)(p)+0)<<24|  \
                     (guint32)*((const guint8 *)(p)+1)<<16|  \
                     (guint32)*((const guint8 *)(p)+2)<<8|   \
                     (guint32)*((const guint8 *)(p)+3)<<0)

#define pntoh40(p)  ((guint64)*((const guint8 *)(p)+0)<<32|  \
                     (guint64)*((const guint8 *)(p)+1)<<24|  \
                     (guint64)*((const guint8 *)(p)+2)<<16|  \
                     (guint64)*((const guint8 *)(p)+3)<<8|   \
                     (guint64)*((const guint8 *)(p)+4)<<0)

#define pntoh48(p)  ((guint64)*((const guint8 *)(p)+0)<<40|  \
                     (guint64)*((const guint8 *)(p)+1)<<32|  \
                     (guint64)*((const guint8 *)(p)+2)<<24|  \
                     (guint64)*((const guint8 *)(p)+3)<<16|  \
                     (guint64)*((const guint8 *)(p)+4)<<8|   \
                     (guint64)*((const guint8 *)(p)+5)<<0)

#define pntoh56(p)  ((guint64)*((const guint8 *)(p)+0)<<48|  \
                     (guint64)*((const guint8 *)(p)+1)<<40|  \
                     (guint64)*((const guint8 *)(p)+2)<<32|  \
                     (guint64)*((const guint8 *)(p)+3)<<24|  \
                     (guint64)*((const guint8 *)(p)+4)<<16|  \
                     (guint64)*((const guint8 *)(p)+5)<<8|   \
                     (guint64)*((const guint8 *)(p)+6)<<0)

#define pntoh64(p)  ((guint64)*((const guint8 *)(p)+0)<<56|  \
                     (guint64)*((const guint8 *)(p)+1)<<48|  \
                     (guint64)*((const guint8 *)(p)+2)<<40|  \
                     (guint64)*((const guint8 *)(p)+3)<<32|  \
                     (guint64)*((const guint8 *)(p)+4)<<24|  \
                     (guint64)*((const guint8 *)(p)+5)<<16|  \
                     (guint64)*((const guint8 *)(p)+6)<<8|   \
                     (guint64)*((const guint8 *)(p)+7)<<0)


#define pletoh16(p) ((guint16)                       \
                     ((guint16)*((const guint8 *)(p)+1)<<8|  \
                      (guint16)*((const guint8 *)(p)+0)<<0))

#define pletoh24(p) ((guint32)*((const guint8 *)(p)+2)<<16|  \
                     (guint32)*((const guint8 *)(p)+1)<<8|   \
                     (guint32)*((const guint8 *)(p)+0)<<0)

#define pletoh32(p) ((guint32)*((const guint8 *)(p)+3)<<24|  \
                     (guint32)*((const guint8 *)(p)+2)<<16|  \
                     (guint32)*((const guint8 *)(p)+1)<<8|   \
                     (guint32)*((const guint8 *)(p)+0)<<0)

#define pletoh40(p) ((guint64)*((const guint8 *)(p)+4)<<32|  \
                     (guint64)*((const guint8 *)(p)+3)<<24|  \
                     (guint64)*((const guint8 *)(p)+2)<<16|  \
                     (guint64)*((const guint8 *)(p)+1)<<8|   \
                     (guint64)*((const guint8 *)(p)+0)<<0)

#define pletoh48(p) ((guint64)*((const guint8 *)(p)+5)<<40|  \
                     (guint64)*((const guint8 *)(p)+4)<<32|  \
                     (guint64)*((const guint8 *)(p)+3)<<24|  \
                     (guint64)*((const guint8 *)(p)+2)<<16|  \
                     (guint64)*((const guint8 *)(p)+1)<<8|   \
                     (guint64)*((const guint8 *)(p)+0)<<0)

#define pletoh56(p) ((guint64)*((const guint8 *)(p)+6)<<48|  \
                     (guint64)*((const guint8 *)(p)+5)<<40|  \
                     (guint64)*((const guint8 *)(p)+4)<<32|  \
                     (guint64)*((const guint8 *)(p)+3)<<24|  \
                     (guint64)*((const guint8 *)(p)+2)<<16|  \
                     (guint64)*((const guint8 *)(p)+1)<<8|   \
                     (guint64)*((const guint8 *)(p)+0)<<0)

#define pletoh64(p) ((guint64)*((const guint8 *)(p)+7)<<56|  \
                     (guint64)*((const guint8 *)(p)+6)<<48|  \
                     (guint64)*((const guint8 *)(p)+5)<<40|  \
                     (guint64)*((const guint8 *)(p)+4)<<32|  \
                     (guint64)*((const guint8 *)(p)+3)<<24|  \
                     (guint64)*((const guint8 *)(p)+2)<<16|  \
                     (guint64)*((const guint8 *)(p)+1)<<8|   \
                     (guint64)*((const guint8 *)(p)+0)<<0)

/* Pointer routines to put items out in a particular byte order.
 * These will work regardless of the byte alignment of the pointer.
 */

#define phton16(p, v) \
	{ 				\
	((guint8*)(p))[0] = (guint8)((v) >> 8);	\
	((guint8*)(p))[1] = (guint8)((v) >> 0);	\
	}

#define phton32(p, v) \
	{ 				\
	((guint8*)(p))[0] = (guint8)((v) >> 24);	\
	((guint8*)(p))[1] = (guint8)((v) >> 16);	\
	((guint8*)(p))[2] = (guint8)((v) >> 8);	\
	((guint8*)(p))[3] = (guint8)((v) >> 0);	\
	}

#define phtole16(p, v) \
	{ 				\
	((guint8*)(p))[1] = (guint8)((v) >> 8);	\
	((guint8*)(p))[0] = (guint8)((v) >> 0);	\
	}

#define phtole32(p, v) \
	{ 				\
	((guint8*)(p))[3] = (guint8)((v) >> 24);	\
	((guint8*)(p))[2] = (guint8)((v) >> 16);	\
	((guint8*)(p))[1] = (guint8)((v) >> 8);	\
	((guint8*)(p))[0] = (guint8)((v) >> 0);	\
	}


//////////////////////////////////////////////////////////////////////////
#pragma pack(push, 1)
struct TVBpacked { // packet in container header with dissector data
  const guint8 * buf;
  guint len;
};
#pragma pack(pop)

class LOCAL_API  TVB {
public:
  TVB(): buf(0), len(0), offset_(0) {};
  TVB(const guint8 * a_buf, guint a_len, guint a_offset = 0): buf(a_buf), len(a_len), offset_(a_offset) {};
  TVB(const TVB& source) {
    buf			= source.buf;
    len			= source.len;
    offset_ = source.offset_;
  };
  TVB& operator =(const TVB& source) {
    buf			= source.buf;
    len			= source.len;
    offset_ = source.offset_;
    return *this;
  };

  inline guint8 get_guint8(guint offset)
  {
#ifdef _CENZOR_HAVE_TVB_CHECK
    if ((offset + 1) > len) {
      gchar sbuf[512];
      sprintf_s(sbuf, sizeof(sbuf), "TVB::get_guint8: buffer is too short - %d (%d required)", len, (offset + 1));
      mscu_throw_exception(sbuf);
    }
#endif

    return buf[offset];
  }

  inline guint16 get_ntohs(guint offset)
  {
#ifdef _CENZOR_HAVE_TVB_CHECK
    if ((offset + 2) > len) {
      gchar sbuf[512];
      sprintf_s(sbuf, sizeof(sbuf), "TVB::get_ntohs: buffer is too short - %d (%d required)", len, (offset + 2));
      mscu_throw_exception(sbuf);
    }
#endif

    return pntoh16(&buf[offset]);
  }

  inline guint16 get_letohs(guint offset)
  {
#ifdef _CENZOR_HAVE_TVB_CHECK
    if ((offset + 2) > len) {
      gchar sbuf[512];
      sprintf_s(sbuf, sizeof(sbuf), "TVB::get_letohs: buffer is too short - %d (%d required)", len, (offset + 2));
      mscu_throw_exception(sbuf);
    }
#endif

    return pletoh16(&buf[offset]);
  }

  inline guint32 get_ntohl(guint offset)
  {
#ifdef _CENZOR_HAVE_TVB_CHECK
    if ((offset + 4) > len) {
      gchar sbuf[512];
      sprintf_s(sbuf, sizeof(sbuf), "TVB::get_ntohl: buffer is too short - %d (%d required)", len, (offset + 4));
      mscu_throw_exception(sbuf);
    }
#endif

    return pntoh32(&buf[offset]);
  }

  inline guint32 get_ntoh24(guint offset)
  {
#ifdef _CENZOR_HAVE_TVB_CHECK
    if ((offset + 3) > len) {
      gchar sbuf[512];
      sprintf_s(sbuf, sizeof(sbuf), "TVB::get_ntoh24: buffer is too short - %d (%d required)", len, (offset + 3));
      mscu_throw_exception(sbuf);
    }
#endif

    return pntoh24(&buf[offset]);
  }

  inline guint32 get_letoh24(guint offset)
  {
#ifdef _CENZOR_HAVE_TVB_CHECK
    if ((offset + 3) > len) {
      gchar sbuf[512];
      sprintf_s(sbuf, sizeof(sbuf), "TVB::get_ntoh24: buffer is too short - %d (%d required)", len, (offset + 3));
      mscu_throw_exception(sbuf);
    }
#endif

    return pletoh24(&buf[offset]);
  }

  inline gboolean GetBitMSBb(gint nBit)
  {
    return ((buf[nBit >> 3] << (nBit & 0x07)) & 0x80) != 0;
  }

  inline gint GetBitMSB(gint nBit)
  {
    gint nXbit, nOffset;
    nXbit = nBit >> 3;
    nOffset = nBit - nXbit * 8;
    if (((buf[nXbit] << nOffset) & 0x80) != 0)
      return 1;
    else
      return 0;
  }

  inline guint8 GetByteValueMSB(gint nBit, gint nCount)
  {
    guint8 Result;
    if (GetBitMSBb(nBit))
      Result = 1;
    else
      Result = 0;
    for (gint k = 1; k < nCount; ++k) {
      Result <<= 1;
      if (GetBitMSBb(nBit + k))
        Result |= 1;
    }
    return Result;
  }

  inline guint16 GetWordValueMSB(gint nBit, gint nCount)
  {
    guint16 Result;
    if (GetBitMSBb(nBit))
      Result = 1;
    else
      Result = 0;
    for (gint k = 1; k < nCount; ++k) {
      Result <<= 1;
      if (GetBitMSBb(nBit + k))
        Result |= 1;
    }
    return Result;
  }

  inline TVB& forward(guint offset)
  {
#ifdef _CENZOR_HAVE_TVB_CHECK
    if (offset > len) {
      gchar sbuf[512];
      sprintf_s(sbuf, sizeof(sbuf), "TVB::forward: buffer is too short - %d (%d required)", len, (offset));
      mscu_throw_exception(sbuf);
    }
#endif

    buf			+= offset;
    len			-= offset;
    offset_ += offset;
    return *this;
  }

  inline TVB& reward(guint offset)
  {
#ifdef _CENZOR_HAVE_TVB_CHECK
    if (offset > offset_)
      mscu_throw_exception(str_format("TVB::reward: buffer is too short - %d (%d required)", offset_, offset));
#endif

    buf			-= offset;
    len			+= offset;
    offset_ -= offset;
    return *this;
  }

  inline TVB& truncate(guint offset)
  {
#ifdef _CENZOR_HAVE_TVB_CHECK
    if (offset > len) {
      gchar sbuf[512];
      sprintf_s(sbuf, sizeof(sbuf), "TVB::truncate: buffer is too short - %d (%d required)", len, (offset));
      mscu_throw_exception(sbuf);
    }
#endif

    len -= offset;
    return *this;
  }

#if defined SWINERTM_API
  inline void reverse_bits()
  {
    for (guint i = 0; i < len; ++i) {
      ((guint8*)buf)[i] = swaptab[buf[i]];
    };
  }
#endif

  inline void set_len(guint new_len)
  {
    len = new_len; // check!!!
  }

  inline void set_buf(const guint8 * a_buf, guint a_len, guint a_offset = 0)
  {
    buf = a_buf;
    len = a_len;
		offset_ = a_offset;
  }

	inline void set_offset(guint offset)
	{
		offset_ = offset;
	};

  inline const guint8 * get_buf()
	{
		return buf;
	};

  inline const guint8 * get_ptr(guint offset, guint /*length*/)
	{
		return buf + offset;
	};

  inline guint get_len()
	{
		return len;
	};

  inline guint get_offset()
	{
		return offset_;
	};

  inline guint8& operator[](gint index)
	{
		return const_cast<guint8&>(buf[index]);
	};

private:
  const guint8 * buf;
  guint len;
	guint offset_;
};

#if defined SWINERTM_API
inline void reverse_bits(guint8 * buf, guint len)
{
  for (guint i = 0; i < len; ++i) {
    buf[i] = swaptab[buf[i]];
  };
}
#endif

//////////////////////////////////////////////////////////////////////////
inline guint16 g_ntohs(guint16 value)
{
	return pntoh16(&value);
}

inline guint32 g_ntohl(guint32 value)
{
	return pntoh32(&value);
}

inline guint16 g_htons(guint16 value)
{
	guint16 Result;
	phton16(&Result, value);
	return Result;
}

inline guint32 g_htonl(guint32 value)
{
	guint32 Result;
	phton32(&Result, value);
	return Result;
}

//////////////////////////////////////////////////////////////////////////
inline guint16 g_ntohs(gconstpointer buffer, gint offset)
{
	return pntoh16(&((guint8*)buffer)[offset]);
}

inline guint32 g_ntohl(gconstpointer buffer, gint offset)
{
	return pntoh32(&((guint8*)buffer)[offset]);
}

//////////////////////////////////////////////////////////////////////////
inline guint8 g_htoh8(gconstpointer buffer, gint offset)
{
  return ((const guint8 *)buffer)[offset];
}

inline guint16 g_htohs(gconstpointer buffer, gint offset)
{
  return *((const guint16*)(&((const guint8 *)buffer)[offset]));
}

inline guint32 g_htohl(gconstpointer buffer, gint offset)
{
  return *((const guint32*)(&((const guint8 *)buffer)[offset]));
}

#endif

