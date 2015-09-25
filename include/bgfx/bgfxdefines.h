/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef BGFX_DEFINES_H_HEADER_GUARD
#define BGFX_DEFINES_H_HEADER_GUARD

///
#define BGFX_STATE_RGB_WRITE             UINT64_C(0x0000000000000001) //!< Enable RGB write.
#define BGFX_STATE_ALPHA_WRITE           UINT64_C(0x0000000000000002) //!< Enable alpha write.
#define BGFX_STATE_DEPTH_WRITE           UINT64_C(0x0000000000000004) //!< Enable depth write.

#define BGFX_STATE_DEPTH_TEST_LESS       UINT64_C(0x0000000000000010) //!< Enable depth test, less.
#define BGFX_STATE_DEPTH_TEST_LEQUAL     UINT64_C(0x0000000000000020) //!< Enable depth test, less equal.
#define BGFX_STATE_DEPTH_TEST_EQUAL      UINT64_C(0x0000000000000030) //!< Enable depth test, equal.
#define BGFX_STATE_DEPTH_TEST_GEQUAL     UINT64_C(0x0000000000000040) //!< Enable depth test, greater equal.
#define BGFX_STATE_DEPTH_TEST_GREATER    UINT64_C(0x0000000000000050) //!< Enable depth test, greater.
#define BGFX_STATE_DEPTH_TEST_NOTEQUAL   UINT64_C(0x0000000000000060) //!< Enable depth test, not equal.
#define BGFX_STATE_DEPTH_TEST_NEVER      UINT64_C(0x0000000000000070) //!< Enable depth test, never.
#define BGFX_STATE_DEPTH_TEST_ALWAYS     UINT64_C(0x0000000000000080) //!< Enable depth test, always.
#define BGFX_STATE_DEPTH_TEST_SHIFT      4
#define BGFX_STATE_DEPTH_TEST_MASK       UINT64_C(0x00000000000000f0) //!< Depth test state bit mask.

#define BGFX_STATE_BLEND_ZERO            UINT64_C(0x0000000000001000) //!<
#define BGFX_STATE_BLEND_ONE             UINT64_C(0x0000000000002000) //!<
#define BGFX_STATE_BLEND_SRC_COLOR       UINT64_C(0x0000000000003000) //!<
#define BGFX_STATE_BLEND_INV_SRC_COLOR   UINT64_C(0x0000000000004000) //!<
#define BGFX_STATE_BLEND_SRC_ALPHA       UINT64_C(0x0000000000005000) //!<
#define BGFX_STATE_BLEND_INV_SRC_ALPHA   UINT64_C(0x0000000000006000) //!<
#define BGFX_STATE_BLEND_DST_ALPHA       UINT64_C(0x0000000000007000) //!<
#define BGFX_STATE_BLEND_INV_DST_ALPHA   UINT64_C(0x0000000000008000) //!<
#define BGFX_STATE_BLEND_DST_COLOR       UINT64_C(0x0000000000009000) //!<
#define BGFX_STATE_BLEND_INV_DST_COLOR   UINT64_C(0x000000000000a000) //!<
#define BGFX_STATE_BLEND_SRC_ALPHA_SAT   UINT64_C(0x000000000000b000) //!<
#define BGFX_STATE_BLEND_FACTOR          UINT64_C(0x000000000000c000) //!<
#define BGFX_STATE_BLEND_INV_FACTOR      UINT64_C(0x000000000000d000) //!<
#define BGFX_STATE_BLEND_SHIFT           12                           //!< Blend state bit shift.
#define BGFX_STATE_BLEND_MASK            UINT64_C(0x000000000ffff000) //!< Blend state bit mask.

#define BGFX_STATE_BLEND_EQUATION_ADD    UINT64_C(0x0000000000000000) //!<
#define BGFX_STATE_BLEND_EQUATION_SUB    UINT64_C(0x0000000010000000) //!<
#define BGFX_STATE_BLEND_EQUATION_REVSUB UINT64_C(0x0000000020000000) //!<
#define BGFX_STATE_BLEND_EQUATION_MIN    UINT64_C(0x0000000030000000) //!<
#define BGFX_STATE_BLEND_EQUATION_MAX    UINT64_C(0x0000000040000000) //!<
#define BGFX_STATE_BLEND_EQUATION_SHIFT  28                           //!< Blend equation bit shift.
#define BGFX_STATE_BLEND_EQUATION_MASK   UINT64_C(0x00000003f0000000) //!< Blend equation bit mask.

#define BGFX_STATE_BLEND_INDEPENDENT     UINT64_C(0x0000000400000000) //!< Enable blend independent.

#define BGFX_STATE_CULL_CW               UINT64_C(0x0000001000000000) //!< Cull clockwise triangles.
#define BGFX_STATE_CULL_CCW              UINT64_C(0x0000002000000000) //!< Cull counter-clockwise triangles.
#define BGFX_STATE_CULL_SHIFT            36                           //!< Culling mode bit shift.
#define BGFX_STATE_CULL_MASK             UINT64_C(0x0000003000000000) //!< Culling mode bit mask.

/// See BGFX_STATE_ALPHA_REF(_ref) helper macro.
#define BGFX_STATE_ALPHA_REF_SHIFT       40                           //!< Alpha reference bit shift.
#define BGFX_STATE_ALPHA_REF_MASK        UINT64_C(0x0000ff0000000000) //!< Alpha reference bit mask.

#define BGFX_STATE_PT_TRISTRIP           UINT64_C(0x0001000000000000) //!< Tristrip.
#define BGFX_STATE_PT_LINES              UINT64_C(0x0002000000000000) //!< Lines.
#define BGFX_STATE_PT_LINESTRIP          UINT64_C(0x0003000000000000) //!< Line strip.
#define BGFX_STATE_PT_POINTS             UINT64_C(0x0004000000000000) //!< Points.
#define BGFX_STATE_PT_SHIFT              48                           //!< Primitive type bit shift.
#define BGFX_STATE_PT_MASK               UINT64_C(0x0007000000000000) //!< Primitive type bit mask.

#define BGFX_STATE_POINT_SIZE_SHIFT      52                           //!< Point size bit shift.
#define BGFX_STATE_POINT_SIZE_MASK       UINT64_C(0x0ff0000000000000) //!< Point size bit mask.

/// Enable MSAA write when writing into MSAA frame buffer. This flag is ignored when not writing into
/// MSAA frame buffer.
#define BGFX_STATE_MSAA                  UINT64_C(0x1000000000000000) //!< Enable MSAA rasterization.

#define BGFX_STATE_RESERVED_MASK         UINT64_C(0xe000000000000000) //!< Internal bits, do not use!

/// See BGFX_STATE_POINT_SIZE(_size) helper macro.
#define BGFX_STATE_NONE                  UINT64_C(0x0000000000000000) //!< No state.
#define BGFX_STATE_MASK                  UINT64_C(0xffffffffffffffff) //!< State mask.

/// Default state is write to RGB, alpha, and depth with depth test less enabled, with clockwise
/// culling and MSAA (when writing into MSAA frame buffer, otherwise this flag is ignored).
#define BGFX_STATE_DEFAULT (0 \
					| BGFX_STATE_RGB_WRITE \
					| BGFX_STATE_ALPHA_WRITE \
					| BGFX_STATE_DEPTH_TEST_LESS \
					| BGFX_STATE_DEPTH_WRITE \
					| BGFX_STATE_CULL_CW \
					| BGFX_STATE_MSAA \
					)

#define BGFX_STATE_ALPHA_REF(_ref)   ( ( (uint64_t)(_ref )<<BGFX_STATE_ALPHA_REF_SHIFT )&BGFX_STATE_ALPHA_REF_MASK)
#define BGFX_STATE_POINT_SIZE(_size) ( ( (uint64_t)(_size)<<BGFX_STATE_POINT_SIZE_SHIFT)&BGFX_STATE_POINT_SIZE_MASK)

///
#define BGFX_STATE_BLEND_FUNC_SEPARATE(_srcRGB, _dstRGB, _srcA, _dstA) (UINT64_C(0) \
					| ( ( (uint64_t)(_srcRGB)|( (uint64_t)(_dstRGB)<<4) )   ) \
					| ( ( (uint64_t)(_srcA  )|( (uint64_t)(_dstA  )<<4) )<<8) \
					)

#define BGFX_STATE_BLEND_EQUATION_SEPARATE(_rgb, _a) ( (uint64_t)(_rgb)|( (uint64_t)(_a)<<3) )

///
#define BGFX_STATE_BLEND_FUNC(_src, _dst)    BGFX_STATE_BLEND_FUNC_SEPARATE(_src, _dst, _src, _dst)
#define BGFX_STATE_BLEND_EQUATION(_equation) BGFX_STATE_BLEND_EQUATION_SEPARATE(_equation, _equation)

#define BGFX_STATE_BLEND_ADD         (BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ONE,       BGFX_STATE_BLEND_ONE          ) )
#define BGFX_STATE_BLEND_ALPHA       (BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA) )
#define BGFX_STATE_BLEND_DARKEN      (BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ONE,       BGFX_STATE_BLEND_ONE          ) | BGFX_STATE_BLEND_EQUATION(BGFX_STATE_BLEND_EQUATION_MIN) )
#define BGFX_STATE_BLEND_LIGHTEN     (BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ONE,       BGFX_STATE_BLEND_ONE          ) | BGFX_STATE_BLEND_EQUATION(BGFX_STATE_BLEND_EQUATION_MAX) )
#define BGFX_STATE_BLEND_MULTIPLY    (BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_DST_COLOR, BGFX_STATE_BLEND_ZERO         ) )
#define BGFX_STATE_BLEND_NORMAL      (BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ONE,       BGFX_STATE_BLEND_INV_SRC_ALPHA) )
#define BGFX_STATE_BLEND_SCREEN      (BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ONE,       BGFX_STATE_BLEND_INV_SRC_COLOR) )
#define BGFX_STATE_BLEND_LINEAR_BURN (BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_DST_COLOR, BGFX_STATE_BLEND_INV_DST_COLOR) | BGFX_STATE_BLEND_EQUATION(BGFX_STATE_BLEND_EQUATION_SUB) )

///
#define BGFX_STATE_BLEND_FUNC_RT_x(_src, _dst) (0 \
					| ( uint32_t( (_src)>>BGFX_STATE_BLEND_SHIFT) \
					| ( uint32_t( (_dst)>>BGFX_STATE_BLEND_SHIFT)<<4) ) \
					)

#define BGFX_STATE_BLEND_FUNC_RT_xE(_src, _dst, _equation) (0 \
					| BGFX_STATE_BLEND_FUNC_RT_x(_src, _dst) \
					| ( uint32_t( (_equation)>>BGFX_STATE_BLEND_EQUATION_SHIFT)<<8) \
					)

#define BGFX_STATE_BLEND_FUNC_RT_1(_src, _dst)  (BGFX_STATE_BLEND_FUNC_RT_x(_src, _dst)<< 0)
#define BGFX_STATE_BLEND_FUNC_RT_2(_src, _dst)  (BGFX_STATE_BLEND_FUNC_RT_x(_src, _dst)<<11)
#define BGFX_STATE_BLEND_FUNC_RT_3(_src, _dst)  (BGFX_STATE_BLEND_FUNC_RT_x(_src, _dst)<<22)

#define BGFX_STATE_BLEND_FUNC_RT_1E(_src, _dst, _equation) (BGFX_STATE_BLEND_FUNC_RT_xE(_src, _dst, _equation)<< 0)
#define BGFX_STATE_BLEND_FUNC_RT_2E(_src, _dst, _equation) (BGFX_STATE_BLEND_FUNC_RT_xE(_src, _dst, _equation)<<11)
#define BGFX_STATE_BLEND_FUNC_RT_3E(_src, _dst, _equation) (BGFX_STATE_BLEND_FUNC_RT_xE(_src, _dst, _equation)<<22)

///
#define BGFX_STENCIL_FUNC_REF_SHIFT      0                    //!<
#define BGFX_STENCIL_FUNC_REF_MASK       UINT32_C(0x000000ff) //!<
#define BGFX_STENCIL_FUNC_RMASK_SHIFT    8                    //!<
#define BGFX_STENCIL_FUNC_RMASK_MASK     UINT32_C(0x0000ff00) //!<

#define BGFX_STENCIL_TEST_LESS           UINT32_C(0x00010000) //!< Enable stencil test, less.
#define BGFX_STENCIL_TEST_LEQUAL         UINT32_C(0x00020000) //!<
#define BGFX_STENCIL_TEST_EQUAL          UINT32_C(0x00030000) //!<
#define BGFX_STENCIL_TEST_GEQUAL         UINT32_C(0x00040000) //!<
#define BGFX_STENCIL_TEST_GREATER        UINT32_C(0x00050000) //!<
#define BGFX_STENCIL_TEST_NOTEQUAL       UINT32_C(0x00060000) //!<
#define BGFX_STENCIL_TEST_NEVER          UINT32_C(0x00070000) //!<
#define BGFX_STENCIL_TEST_ALWAYS         UINT32_C(0x00080000) //!<
#define BGFX_STENCIL_TEST_SHIFT          16                   //!<
#define BGFX_STENCIL_TEST_MASK           UINT32_C(0x000f0000) //!<

#define BGFX_STENCIL_OP_FAIL_S_ZERO      UINT32_C(0x00000000) //!<
#define BGFX_STENCIL_OP_FAIL_S_KEEP      UINT32_C(0x00100000) //!<
#define BGFX_STENCIL_OP_FAIL_S_REPLACE   UINT32_C(0x00200000) //!<
#define BGFX_STENCIL_OP_FAIL_S_INCR      UINT32_C(0x00300000) //!<
#define BGFX_STENCIL_OP_FAIL_S_INCRSAT   UINT32_C(0x00400000) //!<
#define BGFX_STENCIL_OP_FAIL_S_DECR      UINT32_C(0x00500000) //!<
#define BGFX_STENCIL_OP_FAIL_S_DECRSAT   UINT32_C(0x00600000) //!<
#define BGFX_STENCIL_OP_FAIL_S_INVERT    UINT32_C(0x00700000) //!<
#define BGFX_STENCIL_OP_FAIL_S_SHIFT     20                   //!<
#define BGFX_STENCIL_OP_FAIL_S_MASK      UINT32_C(0x00f00000) //!<

#define BGFX_STENCIL_OP_FAIL_Z_ZERO      UINT32_C(0x00000000) //!<
#define BGFX_STENCIL_OP_FAIL_Z_KEEP      UINT32_C(0x01000000) //!<
#define BGFX_STENCIL_OP_FAIL_Z_REPLACE   UINT32_C(0x02000000) //!<
#define BGFX_STENCIL_OP_FAIL_Z_INCR      UINT32_C(0x03000000) //!<
#define BGFX_STENCIL_OP_FAIL_Z_INCRSAT   UINT32_C(0x04000000) //!<
#define BGFX_STENCIL_OP_FAIL_Z_DECR      UINT32_C(0x05000000) //!<
#define BGFX_STENCIL_OP_FAIL_Z_DECRSAT   UINT32_C(0x06000000) //!<
#define BGFX_STENCIL_OP_FAIL_Z_INVERT    UINT32_C(0x07000000) //!<
#define BGFX_STENCIL_OP_FAIL_Z_SHIFT     24                   //!<
#define BGFX_STENCIL_OP_FAIL_Z_MASK      UINT32_C(0x0f000000) //!<

#define BGFX_STENCIL_OP_PASS_Z_ZERO      UINT32_C(0x00000000) //!<
#define BGFX_STENCIL_OP_PASS_Z_KEEP      UINT32_C(0x10000000) //!<
#define BGFX_STENCIL_OP_PASS_Z_REPLACE   UINT32_C(0x20000000) //!<
#define BGFX_STENCIL_OP_PASS_Z_INCR      UINT32_C(0x30000000) //!<
#define BGFX_STENCIL_OP_PASS_Z_INCRSAT   UINT32_C(0x40000000) //!<
#define BGFX_STENCIL_OP_PASS_Z_DECR      UINT32_C(0x50000000) //!<
#define BGFX_STENCIL_OP_PASS_Z_DECRSAT   UINT32_C(0x60000000) //!<
#define BGFX_STENCIL_OP_PASS_Z_INVERT    UINT32_C(0x70000000) //!<
#define BGFX_STENCIL_OP_PASS_Z_SHIFT     28                   //!<
#define BGFX_STENCIL_OP_PASS_Z_MASK      UINT32_C(0xf0000000) //!<

#define BGFX_STENCIL_NONE                UINT32_C(0x00000000) //!<
#define BGFX_STENCIL_MASK                UINT32_C(0xffffffff) //!<
#define BGFX_STENCIL_DEFAULT             UINT32_C(0x00000000) //!<

/// Set stencil ref value.
#define BGFX_STENCIL_FUNC_REF(_ref) ( (uint32_t(_ref)<<BGFX_STENCIL_FUNC_REF_SHIFT)&BGFX_STENCIL_FUNC_REF_MASK)

/// Set stencil rmask value.
#define BGFX_STENCIL_FUNC_RMASK(_mask) ( (uint32_t(_mask)<<BGFX_STENCIL_FUNC_RMASK_SHIFT)&BGFX_STENCIL_FUNC_RMASK_MASK)

///
#define BGFX_CLEAR_NONE                  UINT16_C(0x0000) //!< No clear flags.
#define BGFX_CLEAR_COLOR                 UINT16_C(0x0001) //!< Clear color.
#define BGFX_CLEAR_DEPTH                 UINT16_C(0x0002) //!< Clear depth.
#define BGFX_CLEAR_STENCIL               UINT16_C(0x0004) //!< Clear stencil.
#define BGFX_CLEAR_DISCARD_COLOR_0       UINT16_C(0x0008) //!< Discard frame buffer attachment 0.
#define BGFX_CLEAR_DISCARD_COLOR_1       UINT16_C(0x0010) //!< Discard frame buffer attachment 1.
#define BGFX_CLEAR_DISCARD_COLOR_2       UINT16_C(0x0020) //!< Discard frame buffer attachment 2.
#define BGFX_CLEAR_DISCARD_COLOR_3       UINT16_C(0x0040) //!< Discard frame buffer attachment 3.
#define BGFX_CLEAR_DISCARD_COLOR_4       UINT16_C(0x0080) //!< Discard frame buffer attachment 4.
#define BGFX_CLEAR_DISCARD_COLOR_5       UINT16_C(0x0100) //!< Discard frame buffer attachment 5.
#define BGFX_CLEAR_DISCARD_COLOR_6       UINT16_C(0x0200) //!< Discard frame buffer attachment 6.
#define BGFX_CLEAR_DISCARD_COLOR_7       UINT16_C(0x0400) //!< Discard frame buffer attachment 7.
#define BGFX_CLEAR_DISCARD_DEPTH         UINT16_C(0x0800) //!< Discard frame buffer depth attachment.
#define BGFX_CLEAR_DISCARD_STENCIL       UINT16_C(0x1000) //!< Discard frame buffer stencil attachment.

#define BGFX_CLEAR_DISCARD_COLOR_MASK (0 \
			| BGFX_CLEAR_DISCARD_COLOR_0 \
			| BGFX_CLEAR_DISCARD_COLOR_1 \
			| BGFX_CLEAR_DISCARD_COLOR_2 \
			| BGFX_CLEAR_DISCARD_COLOR_3 \
			| BGFX_CLEAR_DISCARD_COLOR_4 \
			| BGFX_CLEAR_DISCARD_COLOR_5 \
			| BGFX_CLEAR_DISCARD_COLOR_6 \
			| BGFX_CLEAR_DISCARD_COLOR_7 \
			)
#define BGFX_CLEAR_DISCARD_MASK (0 \
			| BGFX_CLEAR_DISCARD_COLOR_MASK \
			| BGFX_CLEAR_DISCARD_DEPTH \
			| BGFX_CLEAR_DISCARD_STENCIL \
			)

#define BGFX_DEBUG_NONE                  UINT32_C(0x00000000) //!< No debug.
#define BGFX_DEBUG_WIREFRAME             UINT32_C(0x00000001) //!< Enable wireframe for all primitives.
#define BGFX_DEBUG_IFH                   UINT32_C(0x00000002) //!< Enable infinitely fast hardware test. No draw calls will be submitted to driver. It’s useful when profiling to quickly assess bottleneck between CPU and GPU.
#define BGFX_DEBUG_STATS                 UINT32_C(0x00000004) //!< Enable statistics display.
#define BGFX_DEBUG_TEXT                  UINT32_C(0x00000008) //!< Enable debug text display.

///
#define BGFX_BUFFER_NONE                 UINT16_C(0x0000) //!<

#define BGFX_BUFFER_COMPUTE_FORMAT_8x1   UINT16_C(0x0001) //!<
#define BGFX_BUFFER_COMPUTE_FORMAT_8x2   UINT16_C(0x0002) //!<
#define BGFX_BUFFER_COMPUTE_FORMAT_8x4   UINT16_C(0x0003) //!<
#define BGFX_BUFFER_COMPUTE_FORMAT_16x1  UINT16_C(0x0004) //!<
#define BGFX_BUFFER_COMPUTE_FORMAT_16x2  UINT16_C(0x0005) //!<
#define BGFX_BUFFER_COMPUTE_FORMAT_16x4  UINT16_C(0x0006) //!<
#define BGFX_BUFFER_COMPUTE_FORMAT_32x1  UINT16_C(0x0007) //!<
#define BGFX_BUFFER_COMPUTE_FORMAT_32x2  UINT16_C(0x0008) //!<
#define BGFX_BUFFER_COMPUTE_FORMAT_32x4  UINT16_C(0x0009) //!<
#define BGFX_BUFFER_COMPUTE_FORMAT_SHIFT 0                //!<
#define BGFX_BUFFER_COMPUTE_FORMAT_MASK  UINT16_C(0x000f) //!<

#define BGFX_BUFFER_COMPUTE_TYPE_UINT    UINT16_C(0x0010) //!<
#define BGFX_BUFFER_COMPUTE_TYPE_INT     UINT16_C(0x0020) //!<
#define BGFX_BUFFER_COMPUTE_TYPE_FLOAT   UINT16_C(0x0030) //!<
#define BGFX_BUFFER_COMPUTE_TYPE_SHIFT   4                //!<
#define BGFX_BUFFER_COMPUTE_TYPE_MASK    UINT16_C(0x0030) //!<

#define BGFX_BUFFER_COMPUTE_READ         UINT16_C(0x0100) //!< Buffer will be read by shader.
#define BGFX_BUFFER_COMPUTE_WRITE        UINT16_C(0x0200) //!< Buffer will be used for writing.
#define BGFX_BUFFER_DRAW_INDIRECT        UINT16_C(0x0400) //!< Buffer will be used for storing draw indirect commands.
#define BGFX_BUFFER_ALLOW_RESIZE         UINT16_C(0x0800) //!<
#define BGFX_BUFFER_INDEX32              UINT16_C(0x1000) //!<

#define BGFX_BUFFER_COMPUTE_READ_WRITE (0 \
			| BGFX_BUFFER_COMPUTE_READ \
			| BGFX_BUFFER_COMPUTE_WRITE \
			)

///
#define BGFX_TEXTURE_NONE                UINT32_C(0x00000000) //!<
#define BGFX_TEXTURE_U_MIRROR            UINT32_C(0x00000001) //!<
#define BGFX_TEXTURE_U_CLAMP             UINT32_C(0x00000002) //!<
#define BGFX_TEXTURE_U_BORDER            UINT32_C(0x00000003) //!<
#define BGFX_TEXTURE_U_SHIFT             0                    //!<
#define BGFX_TEXTURE_U_MASK              UINT32_C(0x00000003) //!<
#define BGFX_TEXTURE_V_MIRROR            UINT32_C(0x00000004) //!<
#define BGFX_TEXTURE_V_CLAMP             UINT32_C(0x00000008) //!<
#define BGFX_TEXTURE_V_BORDER            UINT32_C(0x0000000c) //!<
#define BGFX_TEXTURE_V_SHIFT             2                    //!<
#define BGFX_TEXTURE_V_MASK              UINT32_C(0x0000000c) //!<
#define BGFX_TEXTURE_W_MIRROR            UINT32_C(0x00000010) //!<
#define BGFX_TEXTURE_W_CLAMP             UINT32_C(0x00000020) //!<
#define BGFX_TEXTURE_W_BORDER            UINT32_C(0x00000030) //!<
#define BGFX_TEXTURE_W_SHIFT             4                    //!<
#define BGFX_TEXTURE_W_MASK              UINT32_C(0x00000030) //!<
#define BGFX_TEXTURE_MIN_POINT           UINT32_C(0x00000040) //!<
#define BGFX_TEXTURE_MIN_ANISOTROPIC     UINT32_C(0x00000080) //!<
#define BGFX_TEXTURE_MIN_SHIFT           6                    //!<
#define BGFX_TEXTURE_MIN_MASK            UINT32_C(0x000000c0) //!<
#define BGFX_TEXTURE_MAG_POINT           UINT32_C(0x00000100) //!<
#define BGFX_TEXTURE_MAG_ANISOTROPIC     UINT32_C(0x00000200) //!<
#define BGFX_TEXTURE_MAG_SHIFT           8                    //!<
#define BGFX_TEXTURE_MAG_MASK            UINT32_C(0x00000300) //!<
#define BGFX_TEXTURE_MIP_POINT           UINT32_C(0x00000400) //!<
#define BGFX_TEXTURE_MIP_SHIFT           10                   //!<
#define BGFX_TEXTURE_MIP_MASK            UINT32_C(0x00000400) //!<
#define BGFX_TEXTURE_RT                  UINT32_C(0x00001000) //!<
#define BGFX_TEXTURE_RT_MSAA_X2          UINT32_C(0x00002000) //!<
#define BGFX_TEXTURE_RT_MSAA_X4          UINT32_C(0x00003000) //!<
#define BGFX_TEXTURE_RT_MSAA_X8          UINT32_C(0x00004000) //!<
#define BGFX_TEXTURE_RT_MSAA_X16         UINT32_C(0x00005000) //!<
#define BGFX_TEXTURE_RT_MSAA_SHIFT       12                   //!<
#define BGFX_TEXTURE_RT_MSAA_MASK        UINT32_C(0x00007000) //!<
#define BGFX_TEXTURE_RT_BUFFER_ONLY      UINT32_C(0x00008000) //!<
#define BGFX_TEXTURE_RT_MASK             UINT32_C(0x0000f000) //!<
#define BGFX_TEXTURE_COMPARE_LESS        UINT32_C(0x00010000) //!<
#define BGFX_TEXTURE_COMPARE_LEQUAL      UINT32_C(0x00020000) //!<
#define BGFX_TEXTURE_COMPARE_EQUAL       UINT32_C(0x00030000) //!<
#define BGFX_TEXTURE_COMPARE_GEQUAL      UINT32_C(0x00040000) //!<
#define BGFX_TEXTURE_COMPARE_GREATER     UINT32_C(0x00050000) //!<
#define BGFX_TEXTURE_COMPARE_NOTEQUAL    UINT32_C(0x00060000) //!<
#define BGFX_TEXTURE_COMPARE_NEVER       UINT32_C(0x00070000) //!<
#define BGFX_TEXTURE_COMPARE_ALWAYS      UINT32_C(0x00080000) //!<
#define BGFX_TEXTURE_COMPARE_SHIFT       16                   //!<
#define BGFX_TEXTURE_COMPARE_MASK        UINT32_C(0x000f0000) //!<
#define BGFX_TEXTURE_COMPUTE_WRITE       UINT32_C(0x00100000) //!<
#define BGFX_TEXTURE_SRGB                UINT32_C(0x00200000) //!<
#define BGFX_TEXTURE_BORDER_COLOR_SHIFT  24                   //!<
#define BGFX_TEXTURE_BORDER_COLOR_MASK   UINT32_C(0x0f000000) //!<
#define BGFX_TEXTURE_RESERVED_SHIFT      28                   //!<
#define BGFX_TEXTURE_RESERVED_MASK       UINT32_C(0xf0000000) //!<

#define BGFX_TEXTURE_BORDER_COLOR(_index) ( (_index << BGFX_TEXTURE_BORDER_COLOR_SHIFT) & BGFX_TEXTURE_BORDER_COLOR_MASK)

#define BGFX_TEXTURE_SAMPLER_BITS_MASK (0 \
			| BGFX_TEXTURE_U_MASK \
			| BGFX_TEXTURE_V_MASK \
			| BGFX_TEXTURE_W_MASK \
			| BGFX_TEXTURE_MIN_MASK \
			| BGFX_TEXTURE_MAG_MASK \
			| BGFX_TEXTURE_MIP_MASK \
			| BGFX_TEXTURE_COMPARE_MASK \
			)

///
#define BGFX_RESET_NONE                  UINT32_C(0x00000000) //!< No reset flags.
#define BGFX_RESET_FULLSCREEN            UINT32_C(0x00000001) //!< Not supported yet.
#define BGFX_RESET_FULLSCREEN_SHIFT      0                    //!< Fullscreen bit shift.
#define BGFX_RESET_FULLSCREEN_MASK       UINT32_C(0x00000001) //!< Fullscreen bit mask.
#define BGFX_RESET_MSAA_X2               UINT32_C(0x00000010) //!< Enable 2x MSAA.
#define BGFX_RESET_MSAA_X4               UINT32_C(0x00000020) //!< Enable 4x MSAA.
#define BGFX_RESET_MSAA_X8               UINT32_C(0x00000030) //!< Enable 8x MSAA.
#define BGFX_RESET_MSAA_X16              UINT32_C(0x00000040) //!< Enable 16x MSAA.
#define BGFX_RESET_MSAA_SHIFT            4                    //!< MSAA mode bit shift.
#define BGFX_RESET_MSAA_MASK             UINT32_C(0x00000070) //!< MSAA mode bit mask.
#define BGFX_RESET_VSYNC                 UINT32_C(0x00000080) //!< Enable V-Sync.
#define BGFX_RESET_MAXANISOTROPY         UINT32_C(0x00000100) //!< Turn on/off max anisotropy.
#define BGFX_RESET_CAPTURE               UINT32_C(0x00000200) //!< Begin screen capture.
#define BGFX_RESET_HMD                   UINT32_C(0x00000400) //!< HMD stereo rendering.
#define BGFX_RESET_HMD_DEBUG             UINT32_C(0x00000800) //!< HMD stereo rendering debug mode.
#define BGFX_RESET_HMD_RECENTER          UINT32_C(0x00001000) //!< HMD calibration.
#define BGFX_RESET_FLUSH_AFTER_RENDER    UINT32_C(0x00002000) //!< Flush rendering after submitting to GPU.
#define BGFX_RESET_FLIP_AFTER_RENDER     UINT32_C(0x00004000) //!< This flag  specifies where flip occurs. Default behavior is that flip occurs before rendering new frame. This flag only has effect when `BGFX_CONFIG_MULTITHREADED=0`.
#define BGFX_RESET_SRGB_BACKBUFFER       UINT32_C(0x00008000) //!< Enable sRGB backbuffer.
#define BGFX_RESET_HIDPI                 UINT32_C(0x00010000) //!< Enable HiDPI rendering.

///
#define BGFX_CAPS_TEXTURE_COMPARE_LEQUAL UINT64_C(0x0000000000000001) //!< Texture compare less equal mode is supported.
#define BGFX_CAPS_TEXTURE_COMPARE_ALL    UINT64_C(0x0000000000000003) //!< All texture compare modes are supported.
#define BGFX_CAPS_TEXTURE_3D             UINT64_C(0x0000000000000004) //!< 3D textures are supported.
#define BGFX_CAPS_VERTEX_ATTRIB_HALF     UINT64_C(0x0000000000000008) //!< Vertex attribute half-float is supported.
#define BGFX_CAPS_VERTEX_ATTRIB_UINT10   UINT64_C(0x0000000000000010) //!< Vertex attribute 10_10_10_2 is supported.
#define BGFX_CAPS_INSTANCING             UINT64_C(0x0000000000000020) //!< Instancing is supported.
#define BGFX_CAPS_RENDERER_MULTITHREADED UINT64_C(0x0000000000000040) //!< Renderer is on separate thread.
#define BGFX_CAPS_FRAGMENT_DEPTH         UINT64_C(0x0000000000000080) //!< Fragment depth is accessible in fragment shader.
#define BGFX_CAPS_BLEND_INDEPENDENT      UINT64_C(0x0000000000000100) //!< Blend independent is supported.
#define BGFX_CAPS_COMPUTE                UINT64_C(0x0000000000000200) //!< Compute shaders are supported.
#define BGFX_CAPS_FRAGMENT_ORDERING      UINT64_C(0x0000000000000400) //!< Fragment ordering is available in fragment shader.
#define BGFX_CAPS_SWAP_CHAIN             UINT64_C(0x0000000000000800) //!< Multiple windows are supported.
#define BGFX_CAPS_HMD                    UINT64_C(0x0000000000001000) //!< Head Mounted Display is available.
#define BGFX_CAPS_INDEX32                UINT64_C(0x0000000000002000) //!< 32-bit indices are supported.
#define BGFX_CAPS_DRAW_INDIRECT          UINT64_C(0x0000000000004000) //!< Draw indirect is supported.
#define BGFX_CAPS_HIDPI                  UINT64_C(0x0000000000008000) //!< HiDPI rendering is supported.

///
#define BGFX_CAPS_FORMAT_TEXTURE_NONE             UINT8_C(0x00) //!< Texture format is not supported.
#define BGFX_CAPS_FORMAT_TEXTURE_COLOR            UINT8_C(0x01) //!< Texture format is supported.
#define BGFX_CAPS_FORMAT_TEXTURE_COLOR_SRGB       UINT8_C(0x02) //!< Texture as sRGB format is supported.
#define BGFX_CAPS_FORMAT_TEXTURE_EMULATED         UINT8_C(0x04) //!< Texture format is emulated.
#define BGFX_CAPS_FORMAT_TEXTURE_VERTEX           UINT8_C(0x08) //!< Texture format can be used from vertex shader.
#define BGFX_CAPS_FORMAT_TEXTURE_IMAGE            UINT8_C(0x10) //!< Texture format can be used as image from compute shader.
#define BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER      UINT8_C(0x20) //!< Texture format can be used as frame buffer.
#define BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA UINT8_C(0x40) //!< Texture format can be used as MSAA frame buffer.
#define BGFX_CAPS_FORMAT_TEXTURE_MSAA             UINT8_C(0x80) //!< Texture can be sampled as MSAA.

///
#define BGFX_VIEW_NONE   UINT8_C(0x00) //!<
#define BGFX_VIEW_STEREO UINT8_C(0x01) //!< View will be rendered in stereo mode.

///
#define BGFX_SUBMIT_EYE_LEFT  UINT8_C(0x01) //!< Submit to left eye.
#define BGFX_SUBMIT_EYE_RIGHT UINT8_C(0x02) //!< Submit to right eye.
#define BGFX_SUBMIT_EYE_MASK  UINT8_C(0x03) //!<
#define BGFX_SUBMIT_EYE_FIRST BGFX_SUBMIT_EYE_LEFT

///
#define BGFX_PCI_ID_NONE                UINT16_C(0x0000) //!< Autoselect adapter.
#define BGFX_PCI_ID_SOFTWARE_RASTERIZER UINT16_C(0x0001) //!< Software rasterizer.
#define BGFX_PCI_ID_AMD                 UINT16_C(0x1002) //!< AMD adapter.
#define BGFX_PCI_ID_INTEL               UINT16_C(0x8086) //!< Intel adapter.
#define BGFX_PCI_ID_NVIDIA              UINT16_C(0x10de) //!< nVidia adapter.

///
#define BGFX_HMD_NONE              UINT8_C(0x00) //!< None.
#define BGFX_HMD_DEVICE_RESOLUTION UINT8_C(0x01) //!< Has HMD native resolution.
#define BGFX_HMD_RENDERING         UINT8_C(0x02) //!< Rendering to HMD.

#endif // BGFX_DEFINES_H_HEADER_GUARD
