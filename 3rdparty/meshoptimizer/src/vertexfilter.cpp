// This file is part of meshoptimizer library; see meshoptimizer.h for version/license details
#include "meshoptimizer.h"

#include <math.h>

#if defined(__wasm_simd128__)
#define SIMD_WASM
#endif

#ifdef SIMD_WASM
#include <wasm_simd128.h>
#endif

#ifdef SIMD_WASM
#define wasmx_unpacklo_v16x8(a, b) wasm_v16x8_shuffle(a, b, 0, 8, 1, 9, 2, 10, 3, 11)
#define wasmx_unpackhi_v16x8(a, b) wasm_v16x8_shuffle(a, b, 4, 12, 5, 13, 6, 14, 7, 15)
#define wasmx_unziplo_v32x4(a, b) wasm_v32x4_shuffle(a, b, 0, 2, 4, 6)
#define wasmx_unziphi_v32x4(a, b) wasm_v32x4_shuffle(a, b, 1, 3, 5, 7)
#endif

namespace meshopt
{

#if !defined(SIMD_WASM)
template <typename T>
static void decodeFilterOct(T* data, size_t count)
{
	const float max = float((1 << (sizeof(T) * 8 - 1)) - 1);

	for (size_t i = 0; i < count; ++i)
	{
		// convert x and y to floats and reconstruct z; this assumes zf encodes 1.f at the same bit count
		float x = float(data[i * 4 + 0]);
		float y = float(data[i * 4 + 1]);
		float z = float(data[i * 4 + 2]) - fabsf(x) - fabsf(y);

		// fixup octahedral coordinates for z<0
		float t = (z >= 0.f) ? 0.f : z;

		x += (x >= 0.f) ? t : -t;
		y += (y >= 0.f) ? t : -t;

		// compute normal length & scale
		float l = sqrtf(x * x + y * y + z * z);
		float s = max / l;

		// rounded signed float->int
		int xf = int(x * s + (x >= 0.f ? 0.5f : -0.5f));
		int yf = int(y * s + (y >= 0.f ? 0.5f : -0.5f));
		int zf = int(z * s + (z >= 0.f ? 0.5f : -0.5f));

		data[i * 4 + 0] = T(xf);
		data[i * 4 + 1] = T(yf);
		data[i * 4 + 2] = T(zf);
	}
}

static void decodeFilterQuat(short* data, size_t count)
{
	const float scale = 1.f / sqrtf(2.f);

	static const int order[4][4] = {
	    {1, 2, 3, 0},
	    {2, 3, 0, 1},
	    {3, 0, 1, 2},
	    {0, 1, 2, 3},
	};

	for (size_t i = 0; i < count; ++i)
	{
		// recover scale from the high byte of the component
		int sf = data[i * 4 + 3] | 3;
		float ss = scale / float(sf);

		// convert x/y/z to [-1..1] (scaled...)
		float x = float(data[i * 4 + 0]) * ss;
		float y = float(data[i * 4 + 1]) * ss;
		float z = float(data[i * 4 + 2]) * ss;

		// reconstruct w as a square root; we clamp to 0.f to avoid NaN due to precision errors
		float ww = 1.f - x * x - y * y - z * z;
		float w = sqrtf(ww >= 0.f ? ww : 0.f);

		// rounded signed float->int
		int xf = int(x * 32767.f + (x >= 0.f ? 0.5f : -0.5f));
		int yf = int(y * 32767.f + (y >= 0.f ? 0.5f : -0.5f));
		int zf = int(z * 32767.f + (z >= 0.f ? 0.5f : -0.5f));
		int wf = int(w * 32767.f + 0.5f);

		int qc = data[i * 4 + 3] & 3;

		// output order is dictated by input index
		data[i * 4 + order[qc][0]] = short(xf);
		data[i * 4 + order[qc][1]] = short(yf);
		data[i * 4 + order[qc][2]] = short(zf);
		data[i * 4 + order[qc][3]] = short(wf);
	}
}

static void decodeFilterExp(unsigned int* data, size_t count)
{
	for (size_t i = 0; i < count; ++i)
	{
		unsigned int v = data[i];

		// decode mantissa and exponent
		int m = int(v << 8) >> 8;
		int e = int(v) >> 24;

		union {
			float f;
			unsigned int ui;
		} u;

		// optimized version of ldexp(float(m), e)
		u.ui = unsigned(e + 127) << 23;
		u.f = u.f * float(m);

		data[i] = u.ui;
	}
}
#endif

#ifdef SIMD_WASM
static void decodeFilterOctSimd(signed char* data, size_t count)
{
	const v128_t sign = wasm_f32x4_splat(-0.f);

	for (size_t i = 0; i < count; i += 4)
	{
		v128_t n4 = wasm_v128_load(&data[i * 4]);

		// sign-extends each of x,y in [x y ? ?] with arithmetic shifts
		v128_t xf = wasm_i32x4_shr(wasm_i32x4_shl(n4, 24), 24);
		v128_t yf = wasm_i32x4_shr(wasm_i32x4_shl(n4, 16), 24);

		// unpack z; note that z is unsigned so we technically don't need to sign extend it
		v128_t zf = wasm_i32x4_shr(wasm_i32x4_shl(n4, 8), 24);

		// convert x and y to floats and reconstruct z; this assumes zf encodes 1.f at the same bit count
		v128_t x = wasm_f32x4_convert_i32x4(xf);
		v128_t y = wasm_f32x4_convert_i32x4(yf);
		// TODO: when i32x4_abs is available it might be faster, f32x4_abs is 3 instructions in v8
		v128_t z = wasm_f32x4_sub(wasm_f32x4_convert_i32x4(zf), wasm_f32x4_add(wasm_f32x4_abs(x), wasm_f32x4_abs(y)));

		// fixup octahedral coordinates for z<0
		// note: i32x4_min_s with 0 is equvalent to f32x4_min
		v128_t t = wasm_i32x4_min(z, wasm_i32x4_splat(0));

		x = wasm_f32x4_add(x, wasm_v128_xor(t, wasm_v128_and(x, sign)));
		y = wasm_f32x4_add(y, wasm_v128_xor(t, wasm_v128_and(y, sign)));

		// compute normal length & scale
		v128_t l = wasm_f32x4_sqrt(wasm_f32x4_add(wasm_f32x4_mul(x, x), wasm_f32x4_add(wasm_f32x4_mul(y, y), wasm_f32x4_mul(z, z))));
		v128_t s = wasm_f32x4_div(wasm_f32x4_splat(127.f), l);

		// fast rounded signed float->int: addition triggers renormalization after which mantissa stores the integer value
		// note: the result is offset by 0x4B40_0000, but we only need the low 8 bits so we can omit the subtraction
		const v128_t fsnap = wasm_f32x4_splat(3 << 22);

		v128_t xr = wasm_f32x4_add(wasm_f32x4_mul(x, s), fsnap);
		v128_t yr = wasm_f32x4_add(wasm_f32x4_mul(y, s), fsnap);
		v128_t zr = wasm_f32x4_add(wasm_f32x4_mul(z, s), fsnap);

		// combine xr/yr/zr into final value
		v128_t res = wasm_v128_and(n4, wasm_i32x4_splat(0xff000000));
		res = wasm_v128_or(res, wasm_v128_and(xr, wasm_i32x4_splat(0xff)));
		res = wasm_v128_or(res, wasm_i32x4_shl(wasm_v128_and(yr, wasm_i32x4_splat(0xff)), 8));
		res = wasm_v128_or(res, wasm_i32x4_shl(wasm_v128_and(zr, wasm_i32x4_splat(0xff)), 16));

		wasm_v128_store(&data[i * 4], res);
	}
}

static void decodeFilterOctSimd(short* data, size_t count)
{
	const v128_t sign = wasm_f32x4_splat(-0.f);
	volatile v128_t zmask = wasm_i32x4_splat(0x7fff); // TODO: volatile works around LLVM shuffle "optimizations"

	for (size_t i = 0; i < count; i += 4)
	{
		v128_t n4_0 = wasm_v128_load(&data[(i + 0) * 4]);
		v128_t n4_1 = wasm_v128_load(&data[(i + 2) * 4]);

		// gather both x/y 16-bit pairs in each 32-bit lane
		v128_t n4 = wasmx_unziplo_v32x4(n4_0, n4_1);

		// sign-extends each of x,y in [x y] with arithmetic shifts
		v128_t xf = wasm_i32x4_shr(wasm_i32x4_shl(n4, 16), 16);
		v128_t yf = wasm_i32x4_shr(n4, 16);

		// unpack z; note that z is unsigned so we don't need to sign extend it
		v128_t z4 = wasmx_unziphi_v32x4(n4_0, n4_1);
		v128_t zf = wasm_v128_and(z4, zmask);

		// convert x and y to floats and reconstruct z; this assumes zf encodes 1.f at the same bit count
		v128_t x = wasm_f32x4_convert_i32x4(xf);
		v128_t y = wasm_f32x4_convert_i32x4(yf);
		// TODO: when i32x4_abs is available it might be faster, f32x4_abs is 3 instructions in v8
		v128_t z = wasm_f32x4_sub(wasm_f32x4_convert_i32x4(zf), wasm_f32x4_add(wasm_f32x4_abs(x), wasm_f32x4_abs(y)));

		// fixup octahedral coordinates for z<0
		// note: i32x4_min_s with 0 is equvalent to f32x4_min
		v128_t t = wasm_i32x4_min(z, wasm_i32x4_splat(0));

		x = wasm_f32x4_add(x, wasm_v128_xor(t, wasm_v128_and(x, sign)));
		y = wasm_f32x4_add(y, wasm_v128_xor(t, wasm_v128_and(y, sign)));

		// compute normal length & scale
		v128_t l = wasm_f32x4_sqrt(wasm_f32x4_add(wasm_f32x4_mul(x, x), wasm_f32x4_add(wasm_f32x4_mul(y, y), wasm_f32x4_mul(z, z))));
		v128_t s = wasm_f32x4_div(wasm_f32x4_splat(32767.f), l);

		// fast rounded signed float->int: addition triggers renormalization after which mantissa stores the integer value
		// note: the result is offset by 0x4B40_0000, but we only need the low 16 bits so we can omit the subtraction
		const v128_t fsnap = wasm_f32x4_splat(3 << 22);

		v128_t xr = wasm_f32x4_add(wasm_f32x4_mul(x, s), fsnap);
		v128_t yr = wasm_f32x4_add(wasm_f32x4_mul(y, s), fsnap);
		v128_t zr = wasm_f32x4_add(wasm_f32x4_mul(z, s), fsnap);

		// mix x/z and y/0 to make 16-bit unpack easier
		v128_t xzr = wasm_v128_or(wasm_v128_and(xr, wasm_i32x4_splat(0xffff)), wasm_i32x4_shl(zr, 16));
		v128_t y0r = wasm_v128_and(yr, wasm_i32x4_splat(0xffff));

		// pack x/y/z using 16-bit unpacks; note that this has 0 where we should have .w
		v128_t res_0 = wasmx_unpacklo_v16x8(xzr, y0r);
		v128_t res_1 = wasmx_unpackhi_v16x8(xzr, y0r);

		// patch in .w
		// TODO: this can use pblendw-like shuffles and we can remove y0r - once LLVM fixes shuffle merging
		res_0 = wasm_v128_or(res_0, wasm_v128_and(n4_0, wasm_i64x2_splat(0xffff000000000000)));
		res_1 = wasm_v128_or(res_1, wasm_v128_and(n4_1, wasm_i64x2_splat(0xffff000000000000)));

		wasm_v128_store(&data[(i + 0) * 4], res_0);
		wasm_v128_store(&data[(i + 2) * 4], res_1);
	}
}

static void decodeFilterQuatSimd(short* data, size_t count)
{
	const float scale = 1.f / sqrtf(2.f);

	for (size_t i = 0; i < count; i += 4)
	{
		v128_t q4_0 = wasm_v128_load(&data[(i + 0) * 4]);
		v128_t q4_1 = wasm_v128_load(&data[(i + 2) * 4]);

		// gather both x/y 16-bit pairs in each 32-bit lane
		v128_t q4_xy = wasmx_unziplo_v32x4(q4_0, q4_1);
		v128_t q4_zc = wasmx_unziphi_v32x4(q4_0, q4_1);

		// sign-extends each of x,y in [x y] with arithmetic shifts
		v128_t xf = wasm_i32x4_shr(wasm_i32x4_shl(q4_xy, 16), 16);
		v128_t yf = wasm_i32x4_shr(q4_xy, 16);
		v128_t zf = wasm_i32x4_shr(wasm_i32x4_shl(q4_zc, 16), 16);
		v128_t cf = wasm_i32x4_shr(q4_zc, 16);

		// get a floating-point scaler using zc with bottom 2 bits set to 1 (which represents 1.f)
		v128_t sf = wasm_v128_or(cf, wasm_i32x4_splat(3));
		v128_t ss = wasm_f32x4_div(wasm_f32x4_splat(scale), wasm_f32x4_convert_i32x4(sf));

		// convert x/y/z to [-1..1] (scaled...)
		v128_t x = wasm_f32x4_mul(wasm_f32x4_convert_i32x4(xf), ss);
		v128_t y = wasm_f32x4_mul(wasm_f32x4_convert_i32x4(yf), ss);
		v128_t z = wasm_f32x4_mul(wasm_f32x4_convert_i32x4(zf), ss);

		// reconstruct w as a square root; we clamp to 0.f to avoid NaN due to precision errors
		// note: i32x4_max_s with 0 is equivalent to f32x4_max
		v128_t ww = wasm_f32x4_sub(wasm_f32x4_splat(1.f), wasm_f32x4_add(wasm_f32x4_mul(x, x), wasm_f32x4_add(wasm_f32x4_mul(y, y), wasm_f32x4_mul(z, z))));
		v128_t w = wasm_f32x4_sqrt(wasm_i32x4_max(ww, wasm_i32x4_splat(0)));

		v128_t s = wasm_f32x4_splat(32767.f);

		// fast rounded signed float->int: addition triggers renormalization after which mantissa stores the integer value
		// note: the result is offset by 0x4B40_0000, but we only need the low 16 bits so we can omit the subtraction
		const v128_t fsnap = wasm_f32x4_splat(3 << 22);

		v128_t xr = wasm_f32x4_add(wasm_f32x4_mul(x, s), fsnap);
		v128_t yr = wasm_f32x4_add(wasm_f32x4_mul(y, s), fsnap);
		v128_t zr = wasm_f32x4_add(wasm_f32x4_mul(z, s), fsnap);
		v128_t wr = wasm_f32x4_add(wasm_f32x4_mul(w, s), fsnap);

		// mix x/z and w/y to make 16-bit unpack easier
		v128_t xzr = wasm_v128_or(wasm_v128_and(xr, wasm_i32x4_splat(0xffff)), wasm_i32x4_shl(zr, 16));
		v128_t wyr = wasm_v128_or(wasm_v128_and(wr, wasm_i32x4_splat(0xffff)), wasm_i32x4_shl(yr, 16));

		// pack x/y/z/w using 16-bit unpacks; we pack wxyz by default (for qc=0)
		v128_t res_0 = wasmx_unpacklo_v16x8(wyr, xzr);
		v128_t res_1 = wasmx_unpackhi_v16x8(wyr, xzr);

		// compute component index shifted left by 4 (and moved into i32x4 slot)
		v128_t cm = wasm_i32x4_shl(cf, 4);

		// rotate and store
		uint64_t* out = (uint64_t*)&data[i * 4];

		out[0] = __builtin_rotateleft64(wasm_i64x2_extract_lane(res_0, 0), wasm_i32x4_extract_lane(cm, 0));
		out[1] = __builtin_rotateleft64(wasm_i64x2_extract_lane(res_0, 1), wasm_i32x4_extract_lane(cm, 1));
		out[2] = __builtin_rotateleft64(wasm_i64x2_extract_lane(res_1, 0), wasm_i32x4_extract_lane(cm, 2));
		out[3] = __builtin_rotateleft64(wasm_i64x2_extract_lane(res_1, 1), wasm_i32x4_extract_lane(cm, 3));
	}
}

static void decodeFilterExpSimd(unsigned int* data, size_t count)
{
	for (size_t i = 0; i < count; i += 4)
	{
		v128_t v = wasm_v128_load(&data[i]);

		// decode exponent into 2^x directly
		v128_t ef = wasm_i32x4_shr(v, 24);
		v128_t es = wasm_i32x4_shl(wasm_i32x4_add(ef, wasm_i32x4_splat(127)), 23);

		// decode 24-bit mantissa into floating-point value
		v128_t mf = wasm_i32x4_shr(wasm_i32x4_shl(v, 8), 8);
		v128_t m = wasm_f32x4_convert_i32x4(mf);

		v128_t r = wasm_f32x4_mul(es, m);

		wasm_v128_store(&data[i], r);
	}
}
#endif

} // namespace meshopt

void meshopt_decodeFilterOct(void* buffer, size_t vertex_count, size_t vertex_size)
{
	using namespace meshopt;

	assert(vertex_count % 4 == 0);
	assert(vertex_size == 4 || vertex_size == 8);

#if defined(SIMD_WASM)
	if (vertex_size == 4)
		decodeFilterOctSimd(static_cast<signed char*>(buffer), vertex_count);
	else
		decodeFilterOctSimd(static_cast<short*>(buffer), vertex_count);
#else
	if (vertex_size == 4)
		decodeFilterOct(static_cast<signed char*>(buffer), vertex_count);
	else
		decodeFilterOct(static_cast<short*>(buffer), vertex_count);
#endif
}

void meshopt_decodeFilterQuat(void* buffer, size_t vertex_count, size_t vertex_size)
{
	using namespace meshopt;

	assert(vertex_count % 4 == 0);
	assert(vertex_size == 8);
	(void)vertex_size;

#if defined(SIMD_WASM)
	decodeFilterQuatSimd(static_cast<short*>(buffer), vertex_count);
#else
	decodeFilterQuat(static_cast<short*>(buffer), vertex_count);
#endif
}

void meshopt_decodeFilterExp(void* buffer, size_t vertex_count, size_t vertex_size)
{
	using namespace meshopt;

	assert(vertex_count % 4 == 0);
	assert(vertex_size % 4 == 0);

#if defined(SIMD_WASM)
	decodeFilterExpSimd(static_cast<unsigned int*>(buffer), vertex_count * (vertex_size / 4));
#else
	decodeFilterExp(static_cast<unsigned int*>(buffer), vertex_count * (vertex_size / 4));
#endif
}

#undef SIMD_WASM
