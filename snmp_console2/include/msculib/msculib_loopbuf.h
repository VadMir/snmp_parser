/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/*
 * last update: 2016-07-08
 *
 * loopbuf.h : Ring Buffer
 *
 * Copyright (C) MSC, ORG 2007-2009
 */
/// Changelog:
/// [*] 2016-07-08 - Modified: documentation was updated;
/// [+] 2016-01-22 - Added: multibuffer write functions;
///

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#ifndef MSCULIB_LOOPBUF_H
#define MSCULIB_LOOPBUF_H

//////////////////////////////////////////////////////////////////////////
// creation the new instance of loop buffer
// one (if simple=true) or many (if simple=false) threads can write to buffer, but only ONE thread can read from buffer (but this one not necessary the same thread that is used to write data)
// parameters:
//   bufferSize - new created buffer size, in bytes (minimal size - 0x100000=1MB, if parameter value less than 1MB - it will be corrected)
//   simple - if true - only ONE thread should write to buffer (undefined behavior will occur if many threads will write in simple mode)
//            if false - more than one thread can write to buffer
// result:
//   returns the descriptor of newly created buffer (will be the first parameter for all functions below)
extern "C" MSCULIB_API gpointer MSCU_CALL_PREFIX loop_buf_create(gsize_t bufferSize, gboolean simple);

// destroys the instance of previously created buffer
// parameters:
//   loopbuf - descriptor of the buffer, created by loop_buf_create
extern "C" MSCULIB_API void MSCU_CALL_PREFIX loop_buf_destroy(gpointer loopbuf);

// returns busy percentage of buffer
// parameters:
//   loopbuf - descriptor of the buffer, created by loop_buf_create
// result:
//	 the per cent value of buffer occupation (0% means buffer is empty, 99% means buffer is full)
extern "C" MSCULIB_API gint MSCU_CALL_PREFIX loop_buf_commit_percent(gpointer loopbuf);

// returns the size of buffer
// parameters:
//   loopbuf - descriptor of the buffer, created by loop_buf_create
// result:
//	 the size of buffer in megabytes
extern "C" MSCULIB_API gsize_t MSCU_CALL_PREFIX loop_buf_megabytes(gpointer loopbuf);

// writes packet to the buffer (generic mode)
// this write-function stores and "locks" packet inside buffer, preventing memory occupied inside buffer to be written over
//   to "unlock" and delete this packet from buffer the one should call corresponding peek-function, followed by pop-function
// total packet bytes consist of hdata and data bytes "glued" together, i.e. hdata[hdatasize]+data[datasize]
// attention - simple and indexed versions of write/peek/pop functions cannot be mixed, i.e.:
//   if loop_buf_write/loop_buf_write_n is called, then only loop_buf_read_peek_n/loop_buf_read_pop_n versions should be used to retrieve data
//   if loop_buf_write_index/loop_buf_write_n_index is called, then only loop_buf_read_peek_n_index/loop_buf_read_pop_n_index versions should be used to retrieve data
// parameters:
//   loopbuf - descriptor of the buffer, created by loop_buf_create
//   hdata - pointer to the header packet data
//   hdatasize - size (in bytes) of data, pointed by hdata
//   data - pointer to the main packet data
//   datasize - size (in bytes) of data, pointed by datasize
// result:
//   false (0) - if there is not enough space to write data to buffer
//   true (not 0) - otherwise
extern "C" MSCULIB_API gboolean MSCU_CALL_PREFIX loop_buf_write(gpointer loopbuf, const char* hdata, guint16 hdatasize, const char* data, guint16 datasize);

// writes packet to the buffer (indexed mode)
// this write-function stores and "locks" packet inside buffer, preventing memory occupied inside buffer to be written over
//   to "unlock" and delete this packet from buffer the one should call corresponding peek-function, followed by pop-function
// total packet bytes consist of hdata and data bytes "glued" together, i.e. hdata[hdatasize]+data[datasize]
// attention - simple and indexed versions of write/peek/pop functions cannot be mixed, i.e.:
//   if loop_buf_write/loop_buf_write_n is called, then only loop_buf_read_peek_n/loop_buf_read_pop_n versions should be used to retrieve data
//   if loop_buf_write_index/loop_buf_write_n_index is called, then only loop_buf_read_peek_n_index/loop_buf_read_pop_n_index versions should be used to retrieve data
// parameters:
//   loopbuf - descriptor of the buffer, created by loop_buf_create
//   hdata - pointer to the header packet data
//   hdatasize - size (in bytes) of data, pointed by hdata
//   data - pointer to the main packet data
//   datasize - size (in bytes) of data, pointed by datasize
// result:
//   false (0) - if there is not enough space to write data to buffer
//   true (not 0) - otherwise
extern "C" MSCULIB_API gboolean MSCU_CALL_PREFIX loop_buf_write_indexed(gpointer loopbuf, const char * hdata, guint16 hdatasize, const char * data, guint16 datasize);

// writes packet to the buffer (generic mode)
// this write-function stores and "locks" packet inside buffer, preventing memory occupied inside buffer to be written over
//   to "unlock" and delete this packet from buffer the one should call corresponding peek-function, followed by pop-function
// total packet bytes consist of data_n[0]...data_n[count-1] bytes "glued" together, i.e. data_n[0][datasize_n[0]]+data_n[1][datasize_n[1]]+...+data_n[count-1][datasize_n[count-1]]
// attention - simple and indexed versions of write/peek/pop functions cannot be mixed, i.e.:
//   if loop_buf_write/loop_buf_write_n is called, then only loop_buf_read_peek_n/loop_buf_read_pop_n versions should be used to retrieve data
//   if loop_buf_write_index/loop_buf_write_n_index is called, then only loop_buf_read_peek_n_index/loop_buf_read_pop_n_index versions should be used to retrieve data
// parameters:
//   loopbuf - descriptor of the buffer, created by loop_buf_create
//   data_n - array of elements, containing pointers to the part of packet data
//   datasize_n - array of elements, containing sizes (in bytes) of data, pointed by corresponding data_n element
//   count - data_n and datasize_n size (elements count)
// result:
//   false (0) - if there is not enough space to write data to buffer
//   true (not 0) - otherwise
extern "C" MSCULIB_API gboolean MSCU_CALL_PREFIX loop_buf_write_n(gpointer loopbuf, const char** data_n, guint32 * datasize_n, gsize_t count);

// writes packet to the buffer (indexed mode)
// this write-function stores and "locks" packet inside buffer, preventing memory occupied inside buffer to be written over
//   to "unlock" and delete this packet from buffer the one should call corresponding peek-function, followed by pop-function
// total packet bytes consist of data_n[0]...data_n[count-1] bytes "glued" together, i.e. data_n[0][datasize_n[0]]+data_n[1][datasize_n[1]]+...+data_n[count-1][datasize_n[count-1]]
// attention - simple and indexed versions of write/peek/pop functions cannot be mixed, i.e.:
//   if loop_buf_write/loop_buf_write_n is called, then only loop_buf_read_peek_n/loop_buf_read_pop_n versions should be used to retrieve data
//   if loop_buf_write_index/loop_buf_write_n_index is called, then only loop_buf_read_peek_n_index/loop_buf_read_pop_n_index versions should be used to retrieve data
// parameters:
//   loopbuf - descriptor of the buffer, created by loop_buf_create
//   data_n - array of elements, containing pointers to the part of packet data
//   datasize_n - array of elements, containing sizes (in bytes) of data, pointed by corresponding data_n element
//   count - data_n and datasize_n size (elements count)
// result:
//   false (0) - if there is not enough space to write data to buffer
//   true (not 0) - otherwise
extern "C" MSCULIB_API gboolean MSCU_CALL_PREFIX loop_buf_write_n_indexed(gpointer loopbuf, const char * data_n, guint32 * datasize_n, gsize_t count);

// reads packets from the buffer - dispatch (generic mode)
// this peek-function returns some packets, "locked" by write-function, preventing memory occupied inside buffer to be written over (count parameter means how much packets are returned to work with),
//   the one can work with these packets until corresponding pop-function will be called
// "generic" mode means that peek (loop_buf_read_peek_n) and pop (loop_buf_read_pop_n) functions, opposite to the "simple" mode,
//   can be called strictly one after another, i.e. if loop_buf_read_peek_n first time is called, than before calling it second time you must call loop_buf_read_pop_n to free all peeked packets
// attention - simple and indexed versions of write/peek/pop functions cannot be mixed, i.e.:
//   if loop_buf_write/loop_buf_write_n is called, then only loop_buf_read_peek_n/loop_buf_read_pop_n versions should be used to retrieve data
//   if loop_buf_write_index/loop_buf_write_n_index is called, then only loop_buf_read_peek_n_index/loop_buf_read_pop_n_index versions should be used to retrieve data
// parameters:
//   loopbuf - descriptor of the buffer, created by loop_buf_create
//   buffer - [OUT] array of pointers to the packets data
//   size - [OUT] array of packets data sizes
//   count - [IN] size (count of elements) of buffer and size arrays - i.e. how much elements can be written
//           [OUT] count of elements actually written into buffer and size arrays by this function
// result:
//   false (0) - if there is no data ready inside buffer
//   true (not 0) - otherwise
extern "C" MSCULIB_API gboolean MSCU_CALL_PREFIX loop_buf_read_peek_n(gpointer loopbuf, gpchar * buffer, guint32 * size, guint32 &count);

// reads packets from the buffer - free (generic mode)
// this pop-function "unlocks" packets, previously "locked" by calling peek-function
// "generic" mode means that peek (loop_buf_read_peek_n) and pop (loop_buf_read_pop_n) functions, opposite to the "simple" mode,
//   can be called strictly one after another, i.e. if loop_buf_read_peek_n first time is called, than before calling it second time you must call loop_buf_read_pop_n to free all peeked packets
// attention - simple and indexed versions of write/peek/pop functions cannot be mixed, i.e.:
//   if loop_buf_write/loop_buf_write_n is called, then only loop_buf_read_peek_n/loop_buf_read_pop_n versions should be used to retrieve data
//   if loop_buf_write_index/loop_buf_write_n_index is called, then only loop_buf_read_peek_n_index/loop_buf_read_pop_n_index versions should be used to retrieve data
// parameters:
//   loopbuf - descriptor of the buffer, created by loop_buf_create
// result:
//   false (0) - if error occurred
//   true (not 0) - otherwise
extern "C" MSCULIB_API gboolean MSCU_CALL_PREFIX loop_buf_read_pop_n(gpointer loopbuf);

// reads packets from the buffer - dispatch (indexed mode)
// this peek-function returns some packets, "locked" by write-function, preventing memory occupied inside buffer to be written over (count parameter means how much packets are returned to work with),
//   the one can work with these packets until corresponding pop-function will be called
// "indexed" mode means that packets can be popped (freed) from buffer in random (not sequential) order, opposite to the "generic" mode
// attention - simple and indexed versions of write/peek/pop functions cannot be mixed, i.e.:
//   if loop_buf_write/loop_buf_write_n is called, then only loop_buf_read_peek_n/loop_buf_read_pop_n versions should be used to retrieve data
//   if loop_buf_write_index/loop_buf_write_n_index is called, then only loop_buf_read_peek_n_index/loop_buf_read_pop_n_index versions should be used to retrieve data
// parameters:
//   loopbuf - descriptor of the buffer, created by loop_buf_create
//   buffer - [OUT] array of pointers to the packets data
//   size - [OUT] array of packets data sizes
//   index - [OUT] array of packets indexes (index is needed to free packet from buffer by loop_buf_read_pop_index invocation)
//   count - [IN] size (count of elements) of buffer and size arrays - i.e. how much elements can be written
//           [OUT] count of elements actually written into buffer and size arrays by this function
// result:
//   false (0) - if there is no data ready inside buffer
//   true (not 0) - otherwise
extern "C" MSCULIB_API gboolean MSCU_CALL_PREFIX loop_buf_read_peek_index_n(gpointer loopbuf, gpchar * buffer, guint32 * size, gsize_t * index, guint32 &count);

// reads packets from the buffer - free (indexed mode)
// this pop-function "unlocks" and delete packet (only one packet with specific index), previously "locked" by calling peek-function
// "indexed" mode means that packets can be popped (freed) from buffer in random (not sequential) order, opposite to the "generic" mode
// attention - simple and indexed versions of write/peek/pop functions cannot be mixed, i.e.:
//   if loop_buf_write/loop_buf_write_n is called, then only loop_buf_read_peek_n/loop_buf_read_pop_n versions should be used to retrieve data
//   if loop_buf_write_index/loop_buf_write_n_index is called, then only loop_buf_read_peek_n_index/loop_buf_read_pop_n_index versions should be used to retrieve data
// parameters:
//   loopbuf - descriptor of the buffer, created by loop_buf_create
//   index - index of packet to free from buffer (index is obtained by loop_buf_read_peek_index invocation)
// result:
//   false (0) - if error occurred
//   true (not 0) - otherwise
extern "C" MSCULIB_API gboolean MSCU_CALL_PREFIX loop_buf_read_pop_index(gpointer loopbuf, gsize_t index);

#endif

