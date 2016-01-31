#ifndef __TABLES_HPP__
#define __TABLES_HPP__

#include "Types.hpp"
#ifdef __SSE4_1__
#include <smmintrin.h>
#endif

extern const int32 g_table[8][4];
extern const int64 g_table256[8][4];

extern const uint32 g_id[4][16];

extern const uint32 g_avg2[16];

extern const uint32 g_flags[64];

#ifdef __SSE4_1__
extern const uint8 g_flags_AVX2[64];
extern const __m128i g_table_SIMD[2];
extern const __m128i g_table128_SIMD[2];
extern const __m128i g_table256_SIMD[4];
#endif

#endif
