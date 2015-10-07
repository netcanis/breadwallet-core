//
//  BRTypes.h
//
//  Created by Aaron Voisine on 8/16/15.
//  Copyright (c) 2015 breadwallet LLC.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.

#ifndef BRTypes_h
#define BRTypes_h

#include <stdint.h>
#include <stdlib.h>

// large integers

typedef union {
    uint8_t u8[128/8];
    uint16_t u16[128/16];
    uint32_t u32[128/32];
    uint64_t u64[128/64];
} UInt128;

typedef union {
    uint8_t u8[160/8];
    uint16_t u16[160/16];
    uint32_t u32[160/32];
} UInt160;

typedef union {
    uint8_t u8[256/8];
    uint16_t u16[256/16];
    uint32_t u32[256/32];
    uint64_t u64[256/64];
} UInt256;

typedef union {
    uint8_t u8[512/8];
    uint16_t u16[512/16];
    uint32_t u32[512/32];
    uint64_t u64[512/64];
} UInt512;

inline static int UInt128Eq(UInt128 a, UInt128 b)
{
    return (a.u64[0] == b.u64[0] && a.u64[1] == b.u64[1]);
}

inline static int UInt160Eq(UInt160 a, UInt160 b)
{
    return (a.u32[0] == b.u32[0] && a.u32[1] == b.u32[1] && a.u32[2] == b.u32[2] && a.u32[3] == b.u32[3] &&
            a.u32[4] == b.u32[4]);
}

inline static int UInt256Eq(UInt256 a, UInt256 b)
{
    return (a.u64[0] == b.u64[0] && a.u64[1] == b.u64[1] && a.u64[2] == b.u64[2] && a.u64[3] == b.u64[3]);
}

inline static int UInt512Eq(UInt512 a, UInt512 b)
{
    return (a.u64[0] == b.u64[0] && a.u64[1] == b.u64[1] && a.u64[2] == b.u64[2] && a.u64[3] == b.u64[3] &&
            a.u64[4] == b.u64[4] && a.u64[5] == b.u64[5] && a.u64[6] == b.u64[6] && a.u64[7] == b.u64[7]);
}

inline static int UInt128IsZero(UInt128 u)
{
    return ((u.u64[0] | u.u64[1]) == 0);
}

inline static int UInt160IsZero(UInt160 u)
{
    return ((u.u32[0] | u.u32[1] | u.u32[2] | u.u32[3] | u.u32[4]) == 0);
}

inline static int UInt256IsZero(UInt256 u)
{
    return ((u.u64[0] | u.u64[1] | u.u64[2] | u.u64[3]) == 0);
}

inline static int UInt512IsZero(UInt512 u)
{
    return ((u.u64[0] | u.u64[1] | u.u64[2] | u.u64[3] | u.u64[4] | u.u64[5] | u.u64[6] | u.u64[7]) == 0);
}

inline static UInt256 UInt256Reverse(UInt256 u)
{
    return ((UInt256) { .u8 = { u.u8[31], u.u8[30], u.u8[29], u.u8[28], u.u8[27], u.u8[26], u.u8[25], u.u8[24],
                                u.u8[23], u.u8[22], u.u8[21], u.u8[20], u.u8[19], u.u8[18], u.u8[17], u.u8[16],
                                u.u8[15], u.u8[14], u.u8[13], u.u8[12], u.u8[11], u.u8[10], u.u8[9],  u.u8[8],
                                u.u8[7],  u.u8[6],  u.u8[5],  u.u8[4],  u.u8[3],  u.u8[2],  u.u8[1],  u.u8[0] } });
}

#define UINT128_ZERO ((UInt128) { .u64 = { 0, 0 } })
#define UINT160_ZERO ((UInt160) { .u32 = { 0, 0, 0, 0, 0 } })
#define UINT256_ZERO ((UInt256) { .u64 = { 0, 0, 0, 0 } })
#define UINT512_ZERO ((UInt512) { .u64 = { 0, 0, 0, 0, 0, 0, 0, 0 } })

// integer endian swapping

#if __BIG_ENDIAN__

#define be16(x) (x)
#define le16(x) ((((x) & 0xff00) << 8) | (((x) & 0xff0000) >> 8))
#define be32(x) (x)
#define le32(x) ((((x) & 0xff) << 24) | (((x) & 0xff00) << 8) | (((x) & 0xff0000) >> 8) | (((x) & 0xff000000) >> 24))
#define be64(x) (x)
#define le64(x) ((((x) & 0x00000000000000ffULL) << 56) | (((x) & 0xff00000000000000ULL) >> 56) |\
                 (((x) & 0x000000000000ff00ULL) << 40) | (((x) & 0x00ff000000000000ULL) >> 40) |\
                 (((x) & 0x0000000000ff0000ULL) << 24) | (((x) & 0x0000ff0000000000ULL) >> 24) |\
                 (((x) & 0x00000000ff000000ULL) << 8)  | (((x) & 0x000000ff00000000ULL) >> 8))

#elif __LITTLE_ENDIAN__

#define be16(x) ((((x) & 0xff00) << 8) | (((x) & 0xff0000) >> 8))
#define le16(x) (x)
#define be32(x) ((((x) & 0xff) << 24) | (((x) & 0xff00) << 8) | (((x) & 0xff0000) >> 8) | (((x) & 0xff000000) >> 24))
#define le32(x) (x)
#define be64(x) ((((x) & 0x00000000000000ffULL) << 56) | (((x) & 0xff00000000000000ULL) >> 56) |\
                 (((x) & 0x000000000000ff00ULL) << 40) | (((x) & 0x00ff000000000000ULL) >> 40) |\
                 (((x) & 0x0000000000ff0000ULL) << 24) | (((x) & 0x0000ff0000000000ULL) >> 24) |\
                 (((x) & 0x00000000ff000000ULL) << 8)  | (((x) & 0x000000ff00000000ULL) >> 8))
#define le64(x) (x)

#else

#error host endianess is unkown

#endif

// growable arrays with type checking

#define array_new(array, capacity) do {\
    (array) = (void *)((size_t *)malloc((capacity)*sizeof(*(array)) + sizeof(size_t)*2) + 2);\
    array_capacity(array) = (capacity);\
    array_count(array) = 0;\
} while (0)

#define array_capacity(array) (((size_t *)(array))[-2])

#define array_set_capacity(array, capacity) do {\
    (array) = (void *)((size_t *)realloc((size_t *)(array) - 2, (capacity)*sizeof(*(array)) + sizeof(size_t)*2) + 2);\
    array_capacity(array) = (capacity);\
} while (0)

#define array_count(array) (((size_t *)(array))[-1])

#define array_set_count(array, count) do {\
    if ((count) > array_capacity(array))\
        array_set_capacity(array, count);\
    if ((count) > array_count(array))\
        memset((array) + array_count(array), 0, ((count) - array_count(array))*sizeof(*(array)));\
    array_count(array) = (count);\
} while (0)

#define array_first(array) ((array_count(array) > 0) ? (array)[0] : NULL)

#define array_last(array) ((array_count(array) > 0) ? (array)[array_count(array) - 1] : NULL)

#define array_idx(array, item) (&(item) - (array))

#define array_add(array, item) do {\
    if (array_count(array) + 1 > array_capacity(array))\
        array_set_capacity(array, (array_capacity(array) + 1)*3/2);\
    (array)[array_count(array)++] = (item);\
} while (0)

#define array_add_array(array, other_array, count) do {\
    if (array_count(array) + (count) > array_capacity(array))\
        array_set_capacity(array, (array_count(array) + (count))*3/2);\
    memcpy((array) + array_count(array), (other_array), sizeof(*(other_array))*(count));\
    array_count(array) += (count);\
} while (0)

#define array_insert(array, idx, item) do {\
    if (array_count(array) + 1 > array_capacity(array))\
        array_set_capacity(array, (array_capacity(array) + 1)*3/2);\
    memmove((array) + (idx) + 1, (array) + (idx), (array_count(array)++ - (idx))*sizeof(*(array)));\
    (array)[(idx)] = (item);\
} while (0)

#define array_rm(array, idx) do {\
    memmove((array) + (idx), (array) + (idx) + 1, (--array_count(array) - (idx))*sizeof(*(array)));\
} while (0)

#define array_clear(array) do {\
    array_count(array) = 0;\
} while (0)

#define array_free(array) free((size_t *)(array) - 2)

#endif // BRTypes_h
