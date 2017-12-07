/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/*
 * last update: 2010-07-19
 *
 * mscu_mm.h : Memory Manager
 *
 * Copyright (C) MSC, ORG 2009-2010
 */

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#ifndef MSCULIB_BER_H
#define MSCULIB_BER_H

//////////////////////////////////////////////////////////////////////////
// in_number - число, которое необходимо закодировать
// out_buffer - буфер-приемник
// возвращает количество байт, задействованных для хранения числа
extern "C" MSCULIB_API gboolean mscu_ber_decode(unsigned char * buf, size_t len, size_t * offset, guint64 * number);

extern "C" MSCULIB_API size_t mscu_ber_encode_needs(guint64 number);

extern "C" MSCULIB_API gboolean mscu_ber_encode(guint64 number, unsigned char * buf, size_t len, size_t * offset);

#endif

