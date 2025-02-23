/*
 *  Copyright (C) 2004 Steve Harris
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  as published by the Free Software Foundation; either version 2.1
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  $Id$
 */

#ifndef LOP_ENDIAN_H
#define LOP_ENDIAN_H

// #include <endian.h>
#include <sys/types.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// #define htons(x) x
#define htnol(x) __builtin_bswap16(x)

#define lop_swap16(x) htons(x)

#define lop_swap32(x) htonl(x)

/* These macros come from the Linux kernel */

#ifndef lop_swap16
#define lop_swap16(x) \
({ \
    uint16_t __x = (x); \
    ((uint16_t)( \
	(((uint16_t)(__x) & (uint16_t)0x00ffU) << 8) | \
	(((uint16_t)(__x) & (uint16_t)0xff00U) >> 8) )); \
})
#warning USING UNOPTIMISED ENDIAN STUFF
#endif

#ifndef lop_swap32
#define lop_swap32(x) \
({ \
    uint32_t __x = (x); \
    ((uint32_t)( \
	(((uint32_t)(__x) & (uint32_t)0x000000ffUL) << 24) | \
	(((uint32_t)(__x) & (uint32_t)0x0000ff00UL) <<  8) | \
	(((uint32_t)(__x) & (uint32_t)0x00ff0000UL) >>  8) | \
	(((uint32_t)(__x) & (uint32_t)0xff000000UL) >> 24) )); \
})
#endif

#if 0
#ifndef lop_swap64
#define lop_swap64(x) \
({ \
    uint64_t __x = (x); \
    ((uint64_t)( \
	(uint64_t)(((uint64_t)(__x) & (uint64_t)0x00000000000000ffULL) << 56) | \
	(uint64_t)(((uint64_t)(__x) & (uint64_t)0x000000000000ff00ULL) << 40) | \
	(uint64_t)(((uint64_t)(__x) & (uint64_t)0x0000000000ff0000ULL) << 24) | \
	(uint64_t)(((uint64_t)(__x) & (uint64_t)0x00000000ff000000ULL) <<  8) | \
	(uint64_t)(((uint64_t)(__x) & (uint64_t)0x000000ff00000000ULL) >>  8) | \
	(uint64_t)(((uint64_t)(__x) & (uint64_t)0x0000ff0000000000ULL) >> 24) | \
	(uint64_t)(((uint64_t)(__x) & (uint64_t)0x00ff000000000000ULL) >> 40) | \
	(uint64_t)(((uint64_t)(__x) & (uint64_t)0xff00000000000000ULL) >> 56) )); \
})
#endif
#else

typedef union {
    uint64_t all;
    struct {
	uint32_t a;
	uint32_t b;
    } part;
} lop_split64;

static inline uint64_t lop_swap64(uint64_t x)
{
    lop_split64 in, out;

    in.all = x;
    out.part.a = lop_swap32(in.part.b);
    out.part.b = lop_swap32(in.part.a);

    return out.all;
}
#endif

/* Host to OSC and OSC to Host conversion macros */

#if 1
#define lop_htoo16(x) (x)
#define lop_htoo32(x) (x)
#define lop_htoo64(x) (x)
#define lop_otoh16(x) (x)
#define lop_otoh32(x) (x)
#define lop_otoh64(x) (x)
#else
#define lop_htoo16 lop_swap16
#define lop_htoo32 lop_swap32
#define lop_htoo64 lop_swap64
#define lop_otoh16 lop_swap16
#define lop_otoh32 lop_swap32
#define lop_otoh64 lop_swap64
#endif

#ifdef __cplusplus
}
#endif

#endif

/* vi:set ts=8 sts=4 sw=4: */
