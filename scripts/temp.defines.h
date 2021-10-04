/*
 * Copyright 2011-2020 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

/*
 *
 * AUTO GENERATED FROM IDL! DO NOT EDIT! (source : $source)
 *
 * More info about IDL:
 * https://gist.github.com/bkaradzic/05a1c86a6dd57bf86e2d828878e88dc2#bgfx-is-switching-to-idl-to-generate-api
 *
 */

#ifndef BGFX_DEFINES_H_HEADER_GUARD
#define BGFX_DEFINES_H_HEADER_GUARD

$version

$cflags

/// Blend function separate.
#define BGFX_STATE_BLEND_FUNC_SEPARATE(_srcRGB, _dstRGB, _srcA, _dstA) (UINT64_C(0) \
	| ( ( (uint64_t)(_srcRGB)|( (uint64_t)(_dstRGB)<<4) )   )                       \
	| ( ( (uint64_t)(_srcA  )|( (uint64_t)(_dstA  )<<4) )<<8)                       \
	)

/// Blend equation separate.
#define BGFX_STATE_BLEND_EQUATION_SEPARATE(_equationRGB, _equationA) ( (uint64_t)(_equationRGB)|( (uint64_t)(_equationA)<<3) )

/// Blend function.
#define BGFX_STATE_BLEND_FUNC(_src, _dst)    BGFX_STATE_BLEND_FUNC_SEPARATE(_src, _dst, _src, _dst)

/// Blend equation.
#define BGFX_STATE_BLEND_EQUATION(_equation) BGFX_STATE_BLEND_EQUATION_SEPARATE(_equation, _equation)

/// Utility predefined blend modes.

/// Additive blending.
#define BGFX_STATE_BLEND_ADD (0                                         \
	| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ONE, BGFX_STATE_BLEND_ONE) \
	)

/// Alpha blend.
#define BGFX_STATE_BLEND_ALPHA (0                                                       \
	| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA) \
	)

/// Selects darker color of blend.
#define BGFX_STATE_BLEND_DARKEN (0                                      \
	| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ONE, BGFX_STATE_BLEND_ONE) \
	| BGFX_STATE_BLEND_EQUATION(BGFX_STATE_BLEND_EQUATION_MIN)          \
	)

/// Selects lighter color of blend.
#define BGFX_STATE_BLEND_LIGHTEN (0                                     \
	| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ONE, BGFX_STATE_BLEND_ONE) \
	| BGFX_STATE_BLEND_EQUATION(BGFX_STATE_BLEND_EQUATION_MAX)          \
	)

/// Multiplies colors.
#define BGFX_STATE_BLEND_MULTIPLY (0                                           \
	| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_DST_COLOR, BGFX_STATE_BLEND_ZERO) \
	)

/// Opaque pixels will cover the pixels directly below them without any math or algorithm applied to them.
#define BGFX_STATE_BLEND_NORMAL (0                                                \
	| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ONE, BGFX_STATE_BLEND_INV_SRC_ALPHA) \
	)

/// Multiplies the inverse of the blend and base colors.
#define BGFX_STATE_BLEND_SCREEN (0                                                \
	| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ONE, BGFX_STATE_BLEND_INV_SRC_COLOR) \
	)

/// Decreases the brightness of the base color based on the value of the blend color.
#define BGFX_STATE_BLEND_LINEAR_BURN (0                                                 \
	| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_DST_COLOR, BGFX_STATE_BLEND_INV_DST_COLOR) \
	| BGFX_STATE_BLEND_EQUATION(BGFX_STATE_BLEND_EQUATION_SUB)                          \
	)

///
#define BGFX_STATE_BLEND_FUNC_RT_x(_src, _dst) (0         \
	| ( (uint32_t)( (_src)>>BGFX_STATE_BLEND_SHIFT)       \
	| ( (uint32_t)( (_dst)>>BGFX_STATE_BLEND_SHIFT)<<4) ) \
	)

///
#define BGFX_STATE_BLEND_FUNC_RT_xE(_src, _dst, _equation) (0         \
	| BGFX_STATE_BLEND_FUNC_RT_x(_src, _dst)                          \
	| ( (uint32_t)( (_equation)>>BGFX_STATE_BLEND_EQUATION_SHIFT)<<8) \
	)

#define BGFX_STATE_BLEND_FUNC_RT_1(_src, _dst)  (BGFX_STATE_BLEND_FUNC_RT_x(_src, _dst)<< 0)
#define BGFX_STATE_BLEND_FUNC_RT_2(_src, _dst)  (BGFX_STATE_BLEND_FUNC_RT_x(_src, _dst)<<11)
#define BGFX_STATE_BLEND_FUNC_RT_3(_src, _dst)  (BGFX_STATE_BLEND_FUNC_RT_x(_src, _dst)<<22)

#define BGFX_STATE_BLEND_FUNC_RT_1E(_src, _dst, _equation) (BGFX_STATE_BLEND_FUNC_RT_xE(_src, _dst, _equation)<< 0)
#define BGFX_STATE_BLEND_FUNC_RT_2E(_src, _dst, _equation) (BGFX_STATE_BLEND_FUNC_RT_xE(_src, _dst, _equation)<<11)
#define BGFX_STATE_BLEND_FUNC_RT_3E(_src, _dst, _equation) (BGFX_STATE_BLEND_FUNC_RT_xE(_src, _dst, _equation)<<22)


#endif // BGFX_DEFINES_H_HEADER_GUARD
