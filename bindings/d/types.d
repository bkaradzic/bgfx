/*
 *
 * AUTO GENERATED! DO NOT EDIT!
 *
 */

module bindbc.bgfx.types;

public import core.stdc.stdarg : va_list;

extern(C) @nogc nothrow:

enum uint BGFX_API_VERSION = 115;

alias bgfx_view_id_t = ushort;

/// Memory release callback.

/// Color RGB/alpha/depth write. When it's not specified write will be disabled.
enum ulong BGFX_STATE_WRITE_R = 0x0000000000000001; /// Enable R write.
enum ulong BGFX_STATE_WRITE_G = 0x0000000000000002; /// Enable G write.
enum ulong BGFX_STATE_WRITE_B = 0x0000000000000004; /// Enable B write.
enum ulong BGFX_STATE_WRITE_A = 0x0000000000000008; /// Enable alpha write.
enum ulong BGFX_STATE_WRITE_Z = 0x0000004000000000; /// Enable depth write.
enum ulong BGFX_STATE_WRITE_RGB = 0x0000000000000007; /// Enable RGB write.
enum ulong BGFX_STATE_WRITE_MASK = 0x000000400000000f; /// Write all channels mask.

/// Depth test state. When `BGFX_STATE_DEPTH_` is not specified depth test will be disabled.
enum ulong BGFX_STATE_DEPTH_TEST_LESS = 0x0000000000000010; /// Enable depth test, less.
enum ulong BGFX_STATE_DEPTH_TEST_LEQUAL = 0x0000000000000020; /// Enable depth test, less or equal.
enum ulong BGFX_STATE_DEPTH_TEST_EQUAL = 0x0000000000000030; /// Enable depth test, equal.
enum ulong BGFX_STATE_DEPTH_TEST_GEQUAL = 0x0000000000000040; /// Enable depth test, greater or equal.
enum ulong BGFX_STATE_DEPTH_TEST_GREATER = 0x0000000000000050; /// Enable depth test, greater.
enum ulong BGFX_STATE_DEPTH_TEST_NOTEQUAL = 0x0000000000000060; /// Enable depth test, not equal.
enum ulong BGFX_STATE_DEPTH_TEST_NEVER = 0x0000000000000070; /// Enable depth test, never.
enum ulong BGFX_STATE_DEPTH_TEST_ALWAYS = 0x0000000000000080; /// Enable depth test, always.
enum ulong BGFX_STATE_DEPTH_TEST_SHIFT = 4; /// Depth test state bit shift
enum ulong BGFX_STATE_DEPTH_TEST_MASK = 0x00000000000000f0; /// Depth test state bit mask

/**
 * Use BGFX_STATE_BLEND_FUNC(_src, _dst) or BGFX_STATE_BLEND_FUNC_SEPARATE(_srcRGB, _dstRGB, _srcA, _dstA)
 * helper macros.
 */
enum ulong BGFX_STATE_BLEND_ZERO = 0x0000000000001000; /// 0, 0, 0, 0
enum ulong BGFX_STATE_BLEND_ONE = 0x0000000000002000; /// 1, 1, 1, 1
enum ulong BGFX_STATE_BLEND_SRC_COLOR = 0x0000000000003000; /// Rs, Gs, Bs, As
enum ulong BGFX_STATE_BLEND_INV_SRC_COLOR = 0x0000000000004000; /// 1-Rs, 1-Gs, 1-Bs, 1-As
enum ulong BGFX_STATE_BLEND_SRC_ALPHA = 0x0000000000005000; /// As, As, As, As
enum ulong BGFX_STATE_BLEND_INV_SRC_ALPHA = 0x0000000000006000; /// 1-As, 1-As, 1-As, 1-As
enum ulong BGFX_STATE_BLEND_DST_ALPHA = 0x0000000000007000; /// Ad, Ad, Ad, Ad
enum ulong BGFX_STATE_BLEND_INV_DST_ALPHA = 0x0000000000008000; /// 1-Ad, 1-Ad, 1-Ad ,1-Ad
enum ulong BGFX_STATE_BLEND_DST_COLOR = 0x0000000000009000; /// Rd, Gd, Bd, Ad
enum ulong BGFX_STATE_BLEND_INV_DST_COLOR = 0x000000000000a000; /// 1-Rd, 1-Gd, 1-Bd, 1-Ad
enum ulong BGFX_STATE_BLEND_SRC_ALPHA_SAT = 0x000000000000b000; /// f, f, f, 1; f = min(As, 1-Ad)
enum ulong BGFX_STATE_BLEND_FACTOR = 0x000000000000c000; /// Blend factor
enum ulong BGFX_STATE_BLEND_INV_FACTOR = 0x000000000000d000; /// 1-Blend factor
enum ulong BGFX_STATE_BLEND_SHIFT = 12; /// Blend state bit shift
enum ulong BGFX_STATE_BLEND_MASK = 0x000000000ffff000; /// Blend state bit mask

/**
 * Use BGFX_STATE_BLEND_EQUATION(_equation) or BGFX_STATE_BLEND_EQUATION_SEPARATE(_equationRGB, _equationA)
 * helper macros.
 */
enum ulong BGFX_STATE_BLEND_EQUATION_ADD = 0x0000000000000000; /// Blend add: src + dst.
enum ulong BGFX_STATE_BLEND_EQUATION_SUB = 0x0000000010000000; /// Blend subtract: src - dst.
enum ulong BGFX_STATE_BLEND_EQUATION_REVSUB = 0x0000000020000000; /// Blend reverse subtract: dst - src.
enum ulong BGFX_STATE_BLEND_EQUATION_MIN = 0x0000000030000000; /// Blend min: min(src, dst).
enum ulong BGFX_STATE_BLEND_EQUATION_MAX = 0x0000000040000000; /// Blend max: max(src, dst).
enum ulong BGFX_STATE_BLEND_EQUATION_SHIFT = 28; /// Blend equation bit shift
enum ulong BGFX_STATE_BLEND_EQUATION_MASK = 0x00000003f0000000; /// Blend equation bit mask

/// Cull state. When `BGFX_STATE_CULL_*` is not specified culling will be disabled.
enum ulong BGFX_STATE_CULL_CW = 0x0000001000000000; /// Cull clockwise triangles.
enum ulong BGFX_STATE_CULL_CCW = 0x0000002000000000; /// Cull counter-clockwise triangles.
enum ulong BGFX_STATE_CULL_SHIFT = 36; /// Culling mode bit shift
enum ulong BGFX_STATE_CULL_MASK = 0x0000003000000000; /// Culling mode bit mask

/// Alpha reference value.
enum ulong BGFX_STATE_ALPHA_REF_SHIFT = 40; /// Alpha reference bit shift
enum ulong BGFX_STATE_ALPHA_REF_MASK = 0x0000ff0000000000; /// Alpha reference bit mask
ulong BGFX_STATE_ALPHA_REF (ulong v) { return (v << BGFX_STATE_ALPHA_REF_SHIFT) & BGFX_STATE_ALPHA_REF_MASK; }

enum ulong BGFX_STATE_PT_TRISTRIP = 0x0001000000000000; /// Tristrip.
enum ulong BGFX_STATE_PT_LINES = 0x0002000000000000; /// Lines.
enum ulong BGFX_STATE_PT_LINESTRIP = 0x0003000000000000; /// Line strip.
enum ulong BGFX_STATE_PT_POINTS = 0x0004000000000000; /// Points.
enum ulong BGFX_STATE_PT_SHIFT = 48; /// Primitive type bit shift
enum ulong BGFX_STATE_PT_MASK = 0x0007000000000000; /// Primitive type bit mask

/// Point size value.
enum ulong BGFX_STATE_POINT_SIZE_SHIFT = 52; /// Point size bit shift
enum ulong BGFX_STATE_POINT_SIZE_MASK = 0x00f0000000000000; /// Point size bit mask
ulong BGFX_STATE_POINT_SIZE (ulong v) { return (v << BGFX_STATE_POINT_SIZE_SHIFT) & BGFX_STATE_POINT_SIZE_MASK; }

/**
 * Enable MSAA write when writing into MSAA frame buffer.
 * This flag is ignored when not writing into MSAA frame buffer.
 */
enum ulong BGFX_STATE_MSAA = 0x0100000000000000; /// Enable MSAA rasterization.
enum ulong BGFX_STATE_LINEAA = 0x0200000000000000; /// Enable line AA rasterization.
enum ulong BGFX_STATE_CONSERVATIVE_RASTER = 0x0400000000000000; /// Enable conservative rasterization.
enum ulong BGFX_STATE_NONE = 0x0000000000000000; /// No state.
enum ulong BGFX_STATE_FRONT_CCW = 0x0000008000000000; /// Front counter-clockwise (default is clockwise).
enum ulong BGFX_STATE_BLEND_INDEPENDENT = 0x0000000400000000; /// Enable blend independent.
enum ulong BGFX_STATE_BLEND_ALPHA_TO_COVERAGE = 0x0000000800000000; /// Enable alpha to coverage.
/**
 * Default state is write to RGB, alpha, and depth with depth test less enabled, with clockwise
 * culling and MSAA (when writing into MSAA frame buffer, otherwise this flag is ignored).
 */
enum ulong BGFX_STATE_DEFAULT = BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_WRITE_Z | BGFX_STATE_DEPTH_TEST_LESS | BGFX_STATE_CULL_CW | BGFX_STATE_MSAA;
enum ulong BGFX_STATE_MASK = 0xffffffffffffffff; /// State bit mask

/// Do not use!
enum ulong BGFX_STATE_RESERVED_SHIFT = 61;
enum ulong BGFX_STATE_RESERVED_MASK = 0xe000000000000000;

/// Set stencil ref value.
enum uint BGFX_STENCIL_FUNC_REF_SHIFT = 0;
enum uint BGFX_STENCIL_FUNC_REF_MASK = 0x000000ff;
uint BGFX_STENCIL_FUNC_REF (uint v) { return (v << BGFX_STENCIL_FUNC_REF_SHIFT) & BGFX_STENCIL_FUNC_REF_MASK; }

/// Set stencil rmask value.
enum uint BGFX_STENCIL_FUNC_RMASK_SHIFT = 8;
enum uint BGFX_STENCIL_FUNC_RMASK_MASK = 0x0000ff00;
uint BGFX_STENCIL_FUNC_RMASK (uint v) { return (v << BGFX_STENCIL_FUNC_RMASK_SHIFT) & BGFX_STENCIL_FUNC_RMASK_MASK; }

enum uint BGFX_STENCIL_NONE = 0x00000000;
enum uint BGFX_STENCIL_MASK = 0xffffffff;
enum uint BGFX_STENCIL_DEFAULT = 0x00000000;

enum uint BGFX_STENCIL_TEST_LESS = 0x00010000; /// Enable stencil test, less.
enum uint BGFX_STENCIL_TEST_LEQUAL = 0x00020000; /// Enable stencil test, less or equal.
enum uint BGFX_STENCIL_TEST_EQUAL = 0x00030000; /// Enable stencil test, equal.
enum uint BGFX_STENCIL_TEST_GEQUAL = 0x00040000; /// Enable stencil test, greater or equal.
enum uint BGFX_STENCIL_TEST_GREATER = 0x00050000; /// Enable stencil test, greater.
enum uint BGFX_STENCIL_TEST_NOTEQUAL = 0x00060000; /// Enable stencil test, not equal.
enum uint BGFX_STENCIL_TEST_NEVER = 0x00070000; /// Enable stencil test, never.
enum uint BGFX_STENCIL_TEST_ALWAYS = 0x00080000; /// Enable stencil test, always.
enum uint BGFX_STENCIL_TEST_SHIFT = 16; /// Stencil test bit shift
enum uint BGFX_STENCIL_TEST_MASK = 0x000f0000; /// Stencil test bit mask

enum uint BGFX_STENCIL_OP_FAIL_S_ZERO = 0x00000000; /// Zero.
enum uint BGFX_STENCIL_OP_FAIL_S_KEEP = 0x00100000; /// Keep.
enum uint BGFX_STENCIL_OP_FAIL_S_REPLACE = 0x00200000; /// Replace.
enum uint BGFX_STENCIL_OP_FAIL_S_INCR = 0x00300000; /// Increment and wrap.
enum uint BGFX_STENCIL_OP_FAIL_S_INCRSAT = 0x00400000; /// Increment and clamp.
enum uint BGFX_STENCIL_OP_FAIL_S_DECR = 0x00500000; /// Decrement and wrap.
enum uint BGFX_STENCIL_OP_FAIL_S_DECRSAT = 0x00600000; /// Decrement and clamp.
enum uint BGFX_STENCIL_OP_FAIL_S_INVERT = 0x00700000; /// Invert.
enum uint BGFX_STENCIL_OP_FAIL_S_SHIFT = 20; /// Stencil operation fail bit shift
enum uint BGFX_STENCIL_OP_FAIL_S_MASK = 0x00f00000; /// Stencil operation fail bit mask

enum uint BGFX_STENCIL_OP_FAIL_Z_ZERO = 0x00000000; /// Zero.
enum uint BGFX_STENCIL_OP_FAIL_Z_KEEP = 0x01000000; /// Keep.
enum uint BGFX_STENCIL_OP_FAIL_Z_REPLACE = 0x02000000; /// Replace.
enum uint BGFX_STENCIL_OP_FAIL_Z_INCR = 0x03000000; /// Increment and wrap.
enum uint BGFX_STENCIL_OP_FAIL_Z_INCRSAT = 0x04000000; /// Increment and clamp.
enum uint BGFX_STENCIL_OP_FAIL_Z_DECR = 0x05000000; /// Decrement and wrap.
enum uint BGFX_STENCIL_OP_FAIL_Z_DECRSAT = 0x06000000; /// Decrement and clamp.
enum uint BGFX_STENCIL_OP_FAIL_Z_INVERT = 0x07000000; /// Invert.
enum uint BGFX_STENCIL_OP_FAIL_Z_SHIFT = 24; /// Stencil operation depth fail bit shift
enum uint BGFX_STENCIL_OP_FAIL_Z_MASK = 0x0f000000; /// Stencil operation depth fail bit mask

enum uint BGFX_STENCIL_OP_PASS_Z_ZERO = 0x00000000; /// Zero.
enum uint BGFX_STENCIL_OP_PASS_Z_KEEP = 0x10000000; /// Keep.
enum uint BGFX_STENCIL_OP_PASS_Z_REPLACE = 0x20000000; /// Replace.
enum uint BGFX_STENCIL_OP_PASS_Z_INCR = 0x30000000; /// Increment and wrap.
enum uint BGFX_STENCIL_OP_PASS_Z_INCRSAT = 0x40000000; /// Increment and clamp.
enum uint BGFX_STENCIL_OP_PASS_Z_DECR = 0x50000000; /// Decrement and wrap.
enum uint BGFX_STENCIL_OP_PASS_Z_DECRSAT = 0x60000000; /// Decrement and clamp.
enum uint BGFX_STENCIL_OP_PASS_Z_INVERT = 0x70000000; /// Invert.
enum uint BGFX_STENCIL_OP_PASS_Z_SHIFT = 28; /// Stencil operation depth pass bit shift
enum uint BGFX_STENCIL_OP_PASS_Z_MASK = 0xf0000000; /// Stencil operation depth pass bit mask

enum ushort BGFX_CLEAR_NONE = 0x0000; /// No clear flags.
enum ushort BGFX_CLEAR_COLOR = 0x0001; /// Clear color.
enum ushort BGFX_CLEAR_DEPTH = 0x0002; /// Clear depth.
enum ushort BGFX_CLEAR_STENCIL = 0x0004; /// Clear stencil.
enum ushort BGFX_CLEAR_DISCARD_COLOR_0 = 0x0008; /// Discard frame buffer attachment 0.
enum ushort BGFX_CLEAR_DISCARD_COLOR_1 = 0x0010; /// Discard frame buffer attachment 1.
enum ushort BGFX_CLEAR_DISCARD_COLOR_2 = 0x0020; /// Discard frame buffer attachment 2.
enum ushort BGFX_CLEAR_DISCARD_COLOR_3 = 0x0040; /// Discard frame buffer attachment 3.
enum ushort BGFX_CLEAR_DISCARD_COLOR_4 = 0x0080; /// Discard frame buffer attachment 4.
enum ushort BGFX_CLEAR_DISCARD_COLOR_5 = 0x0100; /// Discard frame buffer attachment 5.
enum ushort BGFX_CLEAR_DISCARD_COLOR_6 = 0x0200; /// Discard frame buffer attachment 6.
enum ushort BGFX_CLEAR_DISCARD_COLOR_7 = 0x0400; /// Discard frame buffer attachment 7.
enum ushort BGFX_CLEAR_DISCARD_DEPTH = 0x0800; /// Discard frame buffer depth attachment.
enum ushort BGFX_CLEAR_DISCARD_STENCIL = 0x1000; /// Discard frame buffer stencil attachment.
enum ushort BGFX_CLEAR_DISCARD_COLOR_MASK = 0x07f8;
enum ushort BGFX_CLEAR_DISCARD_MASK = 0x1ff8;

/**
 * Rendering state discard. When state is preserved in submit, rendering states can be discarded
 * on a finer grain.
 */
enum ubyte BGFX_DISCARD_NONE = 0x00; /// Preserve everything.
enum ubyte BGFX_DISCARD_BINDINGS = 0x01; /// Discard texture sampler and buffer bindings.
enum ubyte BGFX_DISCARD_INDEX_BUFFER = 0x02; /// Discard index buffer.
enum ubyte BGFX_DISCARD_INSTANCE_DATA = 0x04; /// Discard instance data.
enum ubyte BGFX_DISCARD_STATE = 0x08; /// Discard state and uniform bindings.
enum ubyte BGFX_DISCARD_TRANSFORM = 0x10; /// Discard transform.
enum ubyte BGFX_DISCARD_VERTEX_STREAMS = 0x20; /// Discard vertex streams.
enum ubyte BGFX_DISCARD_ALL = 0xff; /// Discard all states.

enum uint BGFX_DEBUG_NONE = 0x00000000; /// No debug.
enum uint BGFX_DEBUG_WIREFRAME = 0x00000001; /// Enable wireframe for all primitives.
/**
 * Enable infinitely fast hardware test. No draw calls will be submitted to driver.
 * It's useful when profiling to quickly assess bottleneck between CPU and GPU.
 */
enum uint BGFX_DEBUG_IFH = 0x00000002;
enum uint BGFX_DEBUG_STATS = 0x00000004; /// Enable statistics display.
enum uint BGFX_DEBUG_TEXT = 0x00000008; /// Enable debug text display.
enum uint BGFX_DEBUG_PROFILER = 0x00000010; /// Enable profiler.

enum ushort BGFX_BUFFER_COMPUTE_FORMAT_8X1 = 0x0001; /// 1 8-bit value
enum ushort BGFX_BUFFER_COMPUTE_FORMAT_8X2 = 0x0002; /// 2 8-bit values
enum ushort BGFX_BUFFER_COMPUTE_FORMAT_8X4 = 0x0003; /// 4 8-bit values
enum ushort BGFX_BUFFER_COMPUTE_FORMAT_16X1 = 0x0004; /// 1 16-bit value
enum ushort BGFX_BUFFER_COMPUTE_FORMAT_16X2 = 0x0005; /// 2 16-bit values
enum ushort BGFX_BUFFER_COMPUTE_FORMAT_16X4 = 0x0006; /// 4 16-bit values
enum ushort BGFX_BUFFER_COMPUTE_FORMAT_32X1 = 0x0007; /// 1 32-bit value
enum ushort BGFX_BUFFER_COMPUTE_FORMAT_32X2 = 0x0008; /// 2 32-bit values
enum ushort BGFX_BUFFER_COMPUTE_FORMAT_32X4 = 0x0009; /// 4 32-bit values
enum ushort BGFX_BUFFER_COMPUTE_FORMAT_SHIFT = 0;
enum ushort BGFX_BUFFER_COMPUTE_FORMAT_MASK = 0x000f;

enum ushort BGFX_BUFFER_COMPUTE_TYPE_INT = 0x0010; /// Type `int`.
enum ushort BGFX_BUFFER_COMPUTE_TYPE_UINT = 0x0020; /// Type `uint`.
enum ushort BGFX_BUFFER_COMPUTE_TYPE_FLOAT = 0x0030; /// Type `float`.
enum ushort BGFX_BUFFER_COMPUTE_TYPE_SHIFT = 4;
enum ushort BGFX_BUFFER_COMPUTE_TYPE_MASK = 0x0030;

enum ushort BGFX_BUFFER_NONE = 0x0000;
enum ushort BGFX_BUFFER_COMPUTE_READ = 0x0100; /// Buffer will be read by shader.
enum ushort BGFX_BUFFER_COMPUTE_WRITE = 0x0200; /// Buffer will be used for writing.
enum ushort BGFX_BUFFER_DRAW_INDIRECT = 0x0400; /// Buffer will be used for storing draw indirect commands.
enum ushort BGFX_BUFFER_ALLOW_RESIZE = 0x0800; /// Allow dynamic index/vertex buffer resize during update.
enum ushort BGFX_BUFFER_INDEX32 = 0x1000; /// Index buffer contains 32-bit indices.
enum ushort BGFX_BUFFER_COMPUTE_READ_WRITE = 0x0300;

enum ulong BGFX_TEXTURE_NONE = 0x0000000000000000;
enum ulong BGFX_TEXTURE_MSAA_SAMPLE = 0x0000000800000000; /// Texture will be used for MSAA sampling.
enum ulong BGFX_TEXTURE_RT = 0x0000001000000000; /// Render target no MSAA.
enum ulong BGFX_TEXTURE_COMPUTE_WRITE = 0x0000100000000000; /// Texture will be used for compute write.
enum ulong BGFX_TEXTURE_SRGB = 0x0000200000000000; /// Sample texture as sRGB.
enum ulong BGFX_TEXTURE_BLIT_DST = 0x0000400000000000; /// Texture will be used as blit destination.
enum ulong BGFX_TEXTURE_READ_BACK = 0x0000800000000000; /// Texture will be used for read back from GPU.

enum ulong BGFX_TEXTURE_RT_MSAA_X2 = 0x0000002000000000; /// Render target MSAAx2 mode.
enum ulong BGFX_TEXTURE_RT_MSAA_X4 = 0x0000003000000000; /// Render target MSAAx4 mode.
enum ulong BGFX_TEXTURE_RT_MSAA_X8 = 0x0000004000000000; /// Render target MSAAx8 mode.
enum ulong BGFX_TEXTURE_RT_MSAA_X16 = 0x0000005000000000; /// Render target MSAAx16 mode.
enum ulong BGFX_TEXTURE_RT_MSAA_SHIFT = 36;
enum ulong BGFX_TEXTURE_RT_MSAA_MASK = 0x0000007000000000;

enum ulong BGFX_TEXTURE_RT_WRITE_ONLY = 0x0000008000000000; /// Render target will be used for writing
enum ulong BGFX_TEXTURE_RT_SHIFT = 36;
enum ulong BGFX_TEXTURE_RT_MASK = 0x000000f000000000;

/// Sampler flags.
enum uint BGFX_SAMPLER_U_MIRROR = 0x00000001; /// Wrap U mode: Mirror
enum uint BGFX_SAMPLER_U_CLAMP = 0x00000002; /// Wrap U mode: Clamp
enum uint BGFX_SAMPLER_U_BORDER = 0x00000003; /// Wrap U mode: Border
enum uint BGFX_SAMPLER_U_SHIFT = 0;
enum uint BGFX_SAMPLER_U_MASK = 0x00000003;

enum uint BGFX_SAMPLER_V_MIRROR = 0x00000004; /// Wrap V mode: Mirror
enum uint BGFX_SAMPLER_V_CLAMP = 0x00000008; /// Wrap V mode: Clamp
enum uint BGFX_SAMPLER_V_BORDER = 0x0000000c; /// Wrap V mode: Border
enum uint BGFX_SAMPLER_V_SHIFT = 2;
enum uint BGFX_SAMPLER_V_MASK = 0x0000000c;

enum uint BGFX_SAMPLER_W_MIRROR = 0x00000010; /// Wrap W mode: Mirror
enum uint BGFX_SAMPLER_W_CLAMP = 0x00000020; /// Wrap W mode: Clamp
enum uint BGFX_SAMPLER_W_BORDER = 0x00000030; /// Wrap W mode: Border
enum uint BGFX_SAMPLER_W_SHIFT = 4;
enum uint BGFX_SAMPLER_W_MASK = 0x00000030;

enum uint BGFX_SAMPLER_MIN_POINT = 0x00000040; /// Min sampling mode: Point
enum uint BGFX_SAMPLER_MIN_ANISOTROPIC = 0x00000080; /// Min sampling mode: Anisotropic
enum uint BGFX_SAMPLER_MIN_SHIFT = 6;
enum uint BGFX_SAMPLER_MIN_MASK = 0x000000c0;

enum uint BGFX_SAMPLER_MAG_POINT = 0x00000100; /// Mag sampling mode: Point
enum uint BGFX_SAMPLER_MAG_ANISOTROPIC = 0x00000200; /// Mag sampling mode: Anisotropic
enum uint BGFX_SAMPLER_MAG_SHIFT = 8;
enum uint BGFX_SAMPLER_MAG_MASK = 0x00000300;

enum uint BGFX_SAMPLER_MIP_POINT = 0x00000400; /// Mip sampling mode: Point
enum uint BGFX_SAMPLER_MIP_SHIFT = 10;
enum uint BGFX_SAMPLER_MIP_MASK = 0x00000400;

enum uint BGFX_SAMPLER_COMPARE_LESS = 0x00010000; /// Compare when sampling depth texture: less.
enum uint BGFX_SAMPLER_COMPARE_LEQUAL = 0x00020000; /// Compare when sampling depth texture: less or equal.
enum uint BGFX_SAMPLER_COMPARE_EQUAL = 0x00030000; /// Compare when sampling depth texture: equal.
enum uint BGFX_SAMPLER_COMPARE_GEQUAL = 0x00040000; /// Compare when sampling depth texture: greater or equal.
enum uint BGFX_SAMPLER_COMPARE_GREATER = 0x00050000; /// Compare when sampling depth texture: greater.
enum uint BGFX_SAMPLER_COMPARE_NOTEQUAL = 0x00060000; /// Compare when sampling depth texture: not equal.
enum uint BGFX_SAMPLER_COMPARE_NEVER = 0x00070000; /// Compare when sampling depth texture: never.
enum uint BGFX_SAMPLER_COMPARE_ALWAYS = 0x00080000; /// Compare when sampling depth texture: always.
enum uint BGFX_SAMPLER_COMPARE_SHIFT = 16;
enum uint BGFX_SAMPLER_COMPARE_MASK = 0x000f0000;

enum uint BGFX_SAMPLER_BORDER_COLOR_SHIFT = 24;
enum uint BGFX_SAMPLER_BORDER_COLOR_MASK = 0x0f000000;
uint BGFX_SAMPLER_BORDER_COLOR (uint v) { return (v << BGFX_SAMPLER_BORDER_COLOR_SHIFT) & BGFX_SAMPLER_BORDER_COLOR_MASK; }

enum uint BGFX_SAMPLER_RESERVED_SHIFT = 28;
enum uint BGFX_SAMPLER_RESERVED_MASK = 0xf0000000;

enum uint BGFX_SAMPLER_NONE = 0x00000000;
enum uint BGFX_SAMPLER_SAMPLE_STENCIL = 0x00100000; /// Sample stencil instead of depth.
enum uint BGFX_SAMPLER_POINT = BGFX_SAMPLER_MIN_POINT | BGFX_SAMPLER_MAG_POINT | BGFX_SAMPLER_MIP_POINT;
enum uint BGFX_SAMPLER_UVW_MIRROR = BGFX_SAMPLER_U_MIRROR | BGFX_SAMPLER_V_MIRROR | BGFX_SAMPLER_W_MIRROR;
enum uint BGFX_SAMPLER_UVW_CLAMP = BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP | BGFX_SAMPLER_W_CLAMP;
enum uint BGFX_SAMPLER_UVW_BORDER = BGFX_SAMPLER_U_BORDER | BGFX_SAMPLER_V_BORDER | BGFX_SAMPLER_W_BORDER;
enum uint BGFX_SAMPLER_BITS_MASK = BGFX_SAMPLER_U_MASK | BGFX_SAMPLER_V_MASK | BGFX_SAMPLER_W_MASK | BGFX_SAMPLER_MIN_MASK | BGFX_SAMPLER_MAG_MASK | BGFX_SAMPLER_MIP_MASK | BGFX_SAMPLER_COMPARE_MASK;

enum uint BGFX_RESET_MSAA_X2 = 0x00000010; /// Enable 2x MSAA.
enum uint BGFX_RESET_MSAA_X4 = 0x00000020; /// Enable 4x MSAA.
enum uint BGFX_RESET_MSAA_X8 = 0x00000030; /// Enable 8x MSAA.
enum uint BGFX_RESET_MSAA_X16 = 0x00000040; /// Enable 16x MSAA.
enum uint BGFX_RESET_MSAA_SHIFT = 4;
enum uint BGFX_RESET_MSAA_MASK = 0x00000070;

enum uint BGFX_RESET_NONE = 0x00000000; /// No reset flags.
enum uint BGFX_RESET_FULLSCREEN = 0x00000001; /// Not supported yet.
enum uint BGFX_RESET_VSYNC = 0x00000080; /// Enable V-Sync.
enum uint BGFX_RESET_MAXANISOTROPY = 0x00000100; /// Turn on/off max anisotropy.
enum uint BGFX_RESET_CAPTURE = 0x00000200; /// Begin screen capture.
enum uint BGFX_RESET_FLUSH_AFTER_RENDER = 0x00002000; /// Flush rendering after submitting to GPU.
/**
 * This flag specifies where flip occurs. Default behaviour is that flip occurs
 * before rendering new frame. This flag only has effect when `BGFX_CONFIG_MULTITHREADED=0`.
 */
enum uint BGFX_RESET_FLIP_AFTER_RENDER = 0x00004000;
enum uint BGFX_RESET_SRGB_BACKBUFFER = 0x00008000; /// Enable sRGB backbuffer.
enum uint BGFX_RESET_HDR10 = 0x00010000; /// Enable HDR10 rendering.
enum uint BGFX_RESET_HIDPI = 0x00020000; /// Enable HiDPI rendering.
enum uint BGFX_RESET_DEPTH_CLAMP = 0x00040000; /// Enable depth clamp.
enum uint BGFX_RESET_SUSPEND = 0x00080000; /// Suspend rendering.

enum uint BGFX_RESET_FULLSCREEN_SHIFT = 0;
enum uint BGFX_RESET_FULLSCREEN_MASK = 0x00000001;

enum uint BGFX_RESET_RESERVED_SHIFT = 31; /// Internal bit shift
enum uint BGFX_RESET_RESERVED_MASK = 0x80000000; /// Internal bit mask

enum ulong BGFX_CAPS_ALPHA_TO_COVERAGE = 0x0000000000000001; /// Alpha to coverage is supported.
enum ulong BGFX_CAPS_BLEND_INDEPENDENT = 0x0000000000000002; /// Blend independent is supported.
enum ulong BGFX_CAPS_COMPUTE = 0x0000000000000004; /// Compute shaders are supported.
enum ulong BGFX_CAPS_CONSERVATIVE_RASTER = 0x0000000000000008; /// Conservative rasterization is supported.
enum ulong BGFX_CAPS_DRAW_INDIRECT = 0x0000000000000010; /// Draw indirect is supported.
enum ulong BGFX_CAPS_FRAGMENT_DEPTH = 0x0000000000000020; /// Fragment depth is available in fragment shader.
enum ulong BGFX_CAPS_FRAGMENT_ORDERING = 0x0000000000000040; /// Fragment ordering is available in fragment shader.
enum ulong BGFX_CAPS_GRAPHICS_DEBUGGER = 0x0000000000000080; /// Graphics debugger is present.
enum ulong BGFX_CAPS_HDR10 = 0x0000000000000100; /// HDR10 rendering is supported.
enum ulong BGFX_CAPS_HIDPI = 0x0000000000000200; /// HiDPI rendering is supported.
enum ulong BGFX_CAPS_IMAGE_RW = 0x0000000000000400; /// Image Read/Write is supported.
enum ulong BGFX_CAPS_INDEX32 = 0x0000000000000800; /// 32-bit indices are supported.
enum ulong BGFX_CAPS_INSTANCING = 0x0000000000001000; /// Instancing is supported.
enum ulong BGFX_CAPS_OCCLUSION_QUERY = 0x0000000000002000; /// Occlusion query is supported.
enum ulong BGFX_CAPS_RENDERER_MULTITHREADED = 0x0000000000004000; /// Renderer is on separate thread.
enum ulong BGFX_CAPS_SWAP_CHAIN = 0x0000000000008000; /// Multiple windows are supported.
enum ulong BGFX_CAPS_TEXTURE_2D_ARRAY = 0x0000000000010000; /// 2D texture array is supported.
enum ulong BGFX_CAPS_TEXTURE_3D = 0x0000000000020000; /// 3D textures are supported.
enum ulong BGFX_CAPS_TEXTURE_BLIT = 0x0000000000040000; /// Texture blit is supported.
enum ulong BGFX_CAPS_TEXTURE_COMPARE_RESERVED = 0x0000000000080000;
enum ulong BGFX_CAPS_TEXTURE_COMPARE_LEQUAL = 0x0000000000100000; /// Texture compare less equal mode is supported.
enum ulong BGFX_CAPS_TEXTURE_CUBE_ARRAY = 0x0000000000200000; /// Cubemap texture array is supported.
enum ulong BGFX_CAPS_TEXTURE_DIRECT_ACCESS = 0x0000000000400000; /// CPU direct access to GPU texture memory.
enum ulong BGFX_CAPS_TEXTURE_READ_BACK = 0x0000000000800000; /// Read-back texture is supported.
enum ulong BGFX_CAPS_VERTEX_ATTRIB_HALF = 0x0000000001000000; /// Vertex attribute half-float is supported.
enum ulong BGFX_CAPS_VERTEX_ATTRIB_UINT10 = 0x0000000002000000; /// Vertex attribute 10_10_10_2 is supported.
enum ulong BGFX_CAPS_VERTEX_ID = 0x0000000004000000; /// Rendering with VertexID only is supported.
enum ulong BGFX_CAPS_VIEWPORT_LAYER_ARRAY = 0x0000000008000000; /// Viewport layer is available in vertex shader.
enum ulong BGFX_CAPS_TEXTURE_COMPARE_ALL = 0x0000000000180000; /// All texture compare modes are supported.

enum uint BGFX_CAPS_FORMAT_TEXTURE_NONE = 0x00000000; /// Texture format is not supported.
enum uint BGFX_CAPS_FORMAT_TEXTURE_2D = 0x00000001; /// Texture format is supported.
enum uint BGFX_CAPS_FORMAT_TEXTURE_2D_SRGB = 0x00000002; /// Texture as sRGB format is supported.
enum uint BGFX_CAPS_FORMAT_TEXTURE_2D_EMULATED = 0x00000004; /// Texture format is emulated.
enum uint BGFX_CAPS_FORMAT_TEXTURE_3D = 0x00000008; /// Texture format is supported.
enum uint BGFX_CAPS_FORMAT_TEXTURE_3D_SRGB = 0x00000010; /// Texture as sRGB format is supported.
enum uint BGFX_CAPS_FORMAT_TEXTURE_3D_EMULATED = 0x00000020; /// Texture format is emulated.
enum uint BGFX_CAPS_FORMAT_TEXTURE_CUBE = 0x00000040; /// Texture format is supported.
enum uint BGFX_CAPS_FORMAT_TEXTURE_CUBE_SRGB = 0x00000080; /// Texture as sRGB format is supported.
enum uint BGFX_CAPS_FORMAT_TEXTURE_CUBE_EMULATED = 0x00000100; /// Texture format is emulated.
enum uint BGFX_CAPS_FORMAT_TEXTURE_VERTEX = 0x00000200; /// Texture format can be used from vertex shader.
enum uint BGFX_CAPS_FORMAT_TEXTURE_IMAGE_READ = 0x00000400; /// Texture format can be used as image and read from.
enum uint BGFX_CAPS_FORMAT_TEXTURE_IMAGE_WRITE = 0x00000800; /// Texture format can be used as image and written to.
enum uint BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER = 0x00001000; /// Texture format can be used as frame buffer.
enum uint BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA = 0x00002000; /// Texture format can be used as MSAA frame buffer.
enum uint BGFX_CAPS_FORMAT_TEXTURE_MSAA = 0x00004000; /// Texture can be sampled as MSAA.
enum uint BGFX_CAPS_FORMAT_TEXTURE_MIP_AUTOGEN = 0x00008000; /// Texture format supports auto-generated mips.

enum ubyte BGFX_RESOLVE_NONE = 0x00; /// No resolve flags.
enum ubyte BGFX_RESOLVE_AUTO_GEN_MIPS = 0x01; /// Auto-generate mip maps on resolve.

enum ushort BGFX_PCI_ID_NONE = 0x0000; /// Autoselect adapter.
enum ushort BGFX_PCI_ID_SOFTWARE_RASTERIZER = 0x0001; /// Software rasterizer.
enum ushort BGFX_PCI_ID_AMD = 0x1002; /// AMD adapter.
enum ushort BGFX_PCI_ID_INTEL = 0x8086; /// Intel adapter.
enum ushort BGFX_PCI_ID_NVIDIA = 0x10de; /// nVidia adapter.

enum ubyte BGFX_CUBE_MAP_POSITIVE_X = 0x00; /// Cubemap +x.
enum ubyte BGFX_CUBE_MAP_NEGATIVE_X = 0x01; /// Cubemap -x.
enum ubyte BGFX_CUBE_MAP_POSITIVE_Y = 0x02; /// Cubemap +y.
enum ubyte BGFX_CUBE_MAP_NEGATIVE_Y = 0x03; /// Cubemap -y.
enum ubyte BGFX_CUBE_MAP_POSITIVE_Z = 0x04; /// Cubemap +z.
enum ubyte BGFX_CUBE_MAP_NEGATIVE_Z = 0x05; /// Cubemap -z.

/// Fatal error enum.
enum bgfx_fatal_t
{
	BGFX_FATAL_DEBUGCHECK,
	BGFX_FATAL_INVALIDSHADER,
	BGFX_FATAL_UNABLETOINITIALIZE,
	BGFX_FATAL_UNABLETOCREATETEXTURE,
	BGFX_FATAL_DEVICELOST,

	BGFX_FATAL_COUNT
}

/// Renderer backend type enum.
enum bgfx_renderer_type_t
{
	BGFX_RENDERER_TYPE_NOOP, /// No rendering.
	BGFX_RENDERER_TYPE_DIRECT3D9, /// Direct3D 9.0
	BGFX_RENDERER_TYPE_DIRECT3D11, /// Direct3D 11.0
	BGFX_RENDERER_TYPE_DIRECT3D12, /// Direct3D 12.0
	BGFX_RENDERER_TYPE_GNM, /// GNM
	BGFX_RENDERER_TYPE_METAL, /// Metal
	BGFX_RENDERER_TYPE_NVN, /// NVN
	BGFX_RENDERER_TYPE_OPENGLES, /// OpenGL ES 2.0+
	BGFX_RENDERER_TYPE_OPENGL, /// OpenGL 2.1+
	BGFX_RENDERER_TYPE_VULKAN, /// Vulkan
	BGFX_RENDERER_TYPE_WEBGPU, /// WebGPU

	BGFX_RENDERER_TYPE_COUNT
}

/// Access mode enum.
enum bgfx_access_t
{
	BGFX_ACCESS_READ, /// Read.
	BGFX_ACCESS_WRITE, /// Write.
	BGFX_ACCESS_READWRITE, /// Read and write.

	BGFX_ACCESS_COUNT
}

/// Vertex attribute enum.
enum bgfx_attrib_t
{
	BGFX_ATTRIB_POSITION, /// a_position
	BGFX_ATTRIB_NORMAL, /// a_normal
	BGFX_ATTRIB_TANGENT, /// a_tangent
	BGFX_ATTRIB_BITANGENT, /// a_bitangent
	BGFX_ATTRIB_COLOR0, /// a_color0
	BGFX_ATTRIB_COLOR1, /// a_color1
	BGFX_ATTRIB_COLOR2, /// a_color2
	BGFX_ATTRIB_COLOR3, /// a_color3
	BGFX_ATTRIB_INDICES, /// a_indices
	BGFX_ATTRIB_WEIGHT, /// a_weight
	BGFX_ATTRIB_TEXCOORD0, /// a_texcoord0
	BGFX_ATTRIB_TEXCOORD1, /// a_texcoord1
	BGFX_ATTRIB_TEXCOORD2, /// a_texcoord2
	BGFX_ATTRIB_TEXCOORD3, /// a_texcoord3
	BGFX_ATTRIB_TEXCOORD4, /// a_texcoord4
	BGFX_ATTRIB_TEXCOORD5, /// a_texcoord5
	BGFX_ATTRIB_TEXCOORD6, /// a_texcoord6
	BGFX_ATTRIB_TEXCOORD7, /// a_texcoord7

	BGFX_ATTRIB_COUNT
}

/// Vertex attribute type enum.
enum bgfx_attrib_type_t
{
	BGFX_ATTRIB_TYPE_UINT8, /// Uint8
	BGFX_ATTRIB_TYPE_UINT10, /// Uint10, availability depends on: `BGFX_CAPS_VERTEX_ATTRIB_UINT10`.
	BGFX_ATTRIB_TYPE_INT16, /// Int16
	BGFX_ATTRIB_TYPE_HALF, /// Half, availability depends on: `BGFX_CAPS_VERTEX_ATTRIB_HALF`.
	BGFX_ATTRIB_TYPE_FLOAT, /// Float

	BGFX_ATTRIB_TYPE_COUNT
}

/**
 * Texture format enum.
 * Notation:
 *       RGBA16S
 *       ^   ^ ^
 *       |   | +-- [ ]Unorm
 *       |   |     [F]loat
 *       |   |     [S]norm
 *       |   |     [I]nt
 *       |   |     [U]int
 *       |   +---- Number of bits per component
 *       +-------- Components
 * @attention Availability depends on Caps (see: formats).
 */
enum bgfx_texture_format_t
{
	BGFX_TEXTURE_FORMAT_BC1, /// DXT1 R5G6B5A1
	BGFX_TEXTURE_FORMAT_BC2, /// DXT3 R5G6B5A4
	BGFX_TEXTURE_FORMAT_BC3, /// DXT5 R5G6B5A8
	BGFX_TEXTURE_FORMAT_BC4, /// LATC1/ATI1 R8
	BGFX_TEXTURE_FORMAT_BC5, /// LATC2/ATI2 RG8
	BGFX_TEXTURE_FORMAT_BC6H, /// BC6H RGB16F
	BGFX_TEXTURE_FORMAT_BC7, /// BC7 RGB 4-7 bits per color channel, 0-8 bits alpha
	BGFX_TEXTURE_FORMAT_ETC1, /// ETC1 RGB8
	BGFX_TEXTURE_FORMAT_ETC2, /// ETC2 RGB8
	BGFX_TEXTURE_FORMAT_ETC2A, /// ETC2 RGBA8
	BGFX_TEXTURE_FORMAT_ETC2A1, /// ETC2 RGB8A1
	BGFX_TEXTURE_FORMAT_PTC12, /// PVRTC1 RGB 2BPP
	BGFX_TEXTURE_FORMAT_PTC14, /// PVRTC1 RGB 4BPP
	BGFX_TEXTURE_FORMAT_PTC12A, /// PVRTC1 RGBA 2BPP
	BGFX_TEXTURE_FORMAT_PTC14A, /// PVRTC1 RGBA 4BPP
	BGFX_TEXTURE_FORMAT_PTC22, /// PVRTC2 RGBA 2BPP
	BGFX_TEXTURE_FORMAT_PTC24, /// PVRTC2 RGBA 4BPP
	BGFX_TEXTURE_FORMAT_ATC, /// ATC RGB 4BPP
	BGFX_TEXTURE_FORMAT_ATCE, /// ATCE RGBA 8 BPP explicit alpha
	BGFX_TEXTURE_FORMAT_ATCI, /// ATCI RGBA 8 BPP interpolated alpha
	BGFX_TEXTURE_FORMAT_ASTC4X4, /// ASTC 4x4 8.0 BPP
	BGFX_TEXTURE_FORMAT_ASTC5X5, /// ASTC 5x5 5.12 BPP
	BGFX_TEXTURE_FORMAT_ASTC6X6, /// ASTC 6x6 3.56 BPP
	BGFX_TEXTURE_FORMAT_ASTC8X5, /// ASTC 8x5 3.20 BPP
	BGFX_TEXTURE_FORMAT_ASTC8X6, /// ASTC 8x6 2.67 BPP
	BGFX_TEXTURE_FORMAT_ASTC10X5, /// ASTC 10x5 2.56 BPP
	BGFX_TEXTURE_FORMAT_UNKNOWN, /// Compressed formats above.
	BGFX_TEXTURE_FORMAT_R1,
	BGFX_TEXTURE_FORMAT_A8,
	BGFX_TEXTURE_FORMAT_R8,
	BGFX_TEXTURE_FORMAT_R8I,
	BGFX_TEXTURE_FORMAT_R8U,
	BGFX_TEXTURE_FORMAT_R8S,
	BGFX_TEXTURE_FORMAT_R16,
	BGFX_TEXTURE_FORMAT_R16I,
	BGFX_TEXTURE_FORMAT_R16U,
	BGFX_TEXTURE_FORMAT_R16F,
	BGFX_TEXTURE_FORMAT_R16S,
	BGFX_TEXTURE_FORMAT_R32I,
	BGFX_TEXTURE_FORMAT_R32U,
	BGFX_TEXTURE_FORMAT_R32F,
	BGFX_TEXTURE_FORMAT_RG8,
	BGFX_TEXTURE_FORMAT_RG8I,
	BGFX_TEXTURE_FORMAT_RG8U,
	BGFX_TEXTURE_FORMAT_RG8S,
	BGFX_TEXTURE_FORMAT_RG16,
	BGFX_TEXTURE_FORMAT_RG16I,
	BGFX_TEXTURE_FORMAT_RG16U,
	BGFX_TEXTURE_FORMAT_RG16F,
	BGFX_TEXTURE_FORMAT_RG16S,
	BGFX_TEXTURE_FORMAT_RG32I,
	BGFX_TEXTURE_FORMAT_RG32U,
	BGFX_TEXTURE_FORMAT_RG32F,
	BGFX_TEXTURE_FORMAT_RGB8,
	BGFX_TEXTURE_FORMAT_RGB8I,
	BGFX_TEXTURE_FORMAT_RGB8U,
	BGFX_TEXTURE_FORMAT_RGB8S,
	BGFX_TEXTURE_FORMAT_RGB9E5F,
	BGFX_TEXTURE_FORMAT_BGRA8,
	BGFX_TEXTURE_FORMAT_RGBA8,
	BGFX_TEXTURE_FORMAT_RGBA8I,
	BGFX_TEXTURE_FORMAT_RGBA8U,
	BGFX_TEXTURE_FORMAT_RGBA8S,
	BGFX_TEXTURE_FORMAT_RGBA16,
	BGFX_TEXTURE_FORMAT_RGBA16I,
	BGFX_TEXTURE_FORMAT_RGBA16U,
	BGFX_TEXTURE_FORMAT_RGBA16F,
	BGFX_TEXTURE_FORMAT_RGBA16S,
	BGFX_TEXTURE_FORMAT_RGBA32I,
	BGFX_TEXTURE_FORMAT_RGBA32U,
	BGFX_TEXTURE_FORMAT_RGBA32F,
	BGFX_TEXTURE_FORMAT_R5G6B5,
	BGFX_TEXTURE_FORMAT_RGBA4,
	BGFX_TEXTURE_FORMAT_RGB5A1,
	BGFX_TEXTURE_FORMAT_RGB10A2,
	BGFX_TEXTURE_FORMAT_RG11B10F,
	BGFX_TEXTURE_FORMAT_UNKNOWNDEPTH, /// Depth formats below.
	BGFX_TEXTURE_FORMAT_D16,
	BGFX_TEXTURE_FORMAT_D24,
	BGFX_TEXTURE_FORMAT_D24S8,
	BGFX_TEXTURE_FORMAT_D32,
	BGFX_TEXTURE_FORMAT_D16F,
	BGFX_TEXTURE_FORMAT_D24F,
	BGFX_TEXTURE_FORMAT_D32F,
	BGFX_TEXTURE_FORMAT_D0S8,

	BGFX_TEXTURE_FORMAT_COUNT
}

/// Uniform type enum.
enum bgfx_uniform_type_t
{
	BGFX_UNIFORM_TYPE_SAMPLER, /// Sampler.
	BGFX_UNIFORM_TYPE_END, /// Reserved, do not use.
	BGFX_UNIFORM_TYPE_VEC4, /// 4 floats vector.
	BGFX_UNIFORM_TYPE_MAT3, /// 3x3 matrix.
	BGFX_UNIFORM_TYPE_MAT4, /// 4x4 matrix.

	BGFX_UNIFORM_TYPE_COUNT
}

/// Backbuffer ratio enum.
enum bgfx_backbuffer_ratio_t
{
	BGFX_BACKBUFFER_RATIO_EQUAL, /// Equal to backbuffer.
	BGFX_BACKBUFFER_RATIO_HALF, /// One half size of backbuffer.
	BGFX_BACKBUFFER_RATIO_QUARTER, /// One quarter size of backbuffer.
	BGFX_BACKBUFFER_RATIO_EIGHTH, /// One eighth size of backbuffer.
	BGFX_BACKBUFFER_RATIO_SIXTEENTH, /// One sixteenth size of backbuffer.
	BGFX_BACKBUFFER_RATIO_DOUBLE, /// Double size of backbuffer.

	BGFX_BACKBUFFER_RATIO_COUNT
}

/// Occlusion query result.
enum bgfx_occlusion_query_result_t
{
	BGFX_OCCLUSION_QUERY_RESULT_INVISIBLE, /// Query failed test.
	BGFX_OCCLUSION_QUERY_RESULT_VISIBLE, /// Query passed test.
	BGFX_OCCLUSION_QUERY_RESULT_NORESULT, /// Query result is not available yet.

	BGFX_OCCLUSION_QUERY_RESULT_COUNT
}

/// Primitive topology.
enum bgfx_topology_t
{
	BGFX_TOPOLOGY_TRILIST, /// Triangle list.
	BGFX_TOPOLOGY_TRISTRIP, /// Triangle strip.
	BGFX_TOPOLOGY_LINELIST, /// Line list.
	BGFX_TOPOLOGY_LINESTRIP, /// Line strip.
	BGFX_TOPOLOGY_POINTLIST, /// Point list.

	BGFX_TOPOLOGY_COUNT
}

/// Topology conversion function.
enum bgfx_topology_convert_t
{
	BGFX_TOPOLOGY_CONVERT_TRILISTFLIPWINDING, /// Flip winding order of triangle list.
	BGFX_TOPOLOGY_CONVERT_TRISTRIPFLIPWINDING, /// Flip winding order of triangle strip.
	BGFX_TOPOLOGY_CONVERT_TRILISTTOLINELIST, /// Convert triangle list to line list.
	BGFX_TOPOLOGY_CONVERT_TRISTRIPTOTRILIST, /// Convert triangle strip to triangle list.
	BGFX_TOPOLOGY_CONVERT_LINESTRIPTOLINELIST, /// Convert line strip to line list.

	BGFX_TOPOLOGY_CONVERT_COUNT
}

/// Topology sort order.
enum bgfx_topology_sort_t
{
	BGFX_TOPOLOGY_SORT_DIRECTIONFRONTTOBACKMIN,
	BGFX_TOPOLOGY_SORT_DIRECTIONFRONTTOBACKAVG,
	BGFX_TOPOLOGY_SORT_DIRECTIONFRONTTOBACKMAX,
	BGFX_TOPOLOGY_SORT_DIRECTIONBACKTOFRONTMIN,
	BGFX_TOPOLOGY_SORT_DIRECTIONBACKTOFRONTAVG,
	BGFX_TOPOLOGY_SORT_DIRECTIONBACKTOFRONTMAX,
	BGFX_TOPOLOGY_SORT_DISTANCEFRONTTOBACKMIN,
	BGFX_TOPOLOGY_SORT_DISTANCEFRONTTOBACKAVG,
	BGFX_TOPOLOGY_SORT_DISTANCEFRONTTOBACKMAX,
	BGFX_TOPOLOGY_SORT_DISTANCEBACKTOFRONTMIN,
	BGFX_TOPOLOGY_SORT_DISTANCEBACKTOFRONTAVG,
	BGFX_TOPOLOGY_SORT_DISTANCEBACKTOFRONTMAX,

	BGFX_TOPOLOGY_SORT_COUNT
}

/// View mode sets draw call sort order.
enum bgfx_view_mode_t
{
	BGFX_VIEW_MODE_DEFAULT, /// Default sort order.
	BGFX_VIEW_MODE_SEQUENTIAL, /// Sort in the same order in which submit calls were called.
	BGFX_VIEW_MODE_DEPTHASCENDING, /// Sort draw call depth in ascending order.
	BGFX_VIEW_MODE_DEPTHDESCENDING, /// Sort draw call depth in descending order.

	BGFX_VIEW_MODE_COUNT
}

/// Render frame enum.
enum bgfx_render_frame_t
{
	BGFX_RENDER_FRAME_NOCONTEXT, /// Renderer context is not created yet.
	BGFX_RENDER_FRAME_RENDER, /// Renderer context is created and rendering.
	BGFX_RENDER_FRAME_TIMEOUT, /// Renderer context wait for main thread signal timed out without rendering.
	BGFX_RENDER_FRAME_EXITING, /// Renderer context is getting destroyed.

	BGFX_RENDER_FRAME_COUNT
}

/// GPU info.
struct bgfx_caps_gpu_t
{
	ushort vendorId; /// Vendor PCI id. See `BGFX_PCI_ID_*`.
	ushort deviceId; /// Device id.
}

/// Renderer runtime limits.
struct bgfx_caps_limits_t
{
	uint maxDrawCalls; /// Maximum number of draw calls.
	uint maxBlits; /// Maximum number of blit calls.
	uint maxTextureSize; /// Maximum texture size.
	uint maxTextureLayers; /// Maximum texture layers.
	uint maxViews; /// Maximum number of views.
	uint maxFrameBuffers; /// Maximum number of frame buffer handles.
	uint maxFBAttachments; /// Maximum number of frame buffer attachments.
	uint maxPrograms; /// Maximum number of program handles.
	uint maxShaders; /// Maximum number of shader handles.
	uint maxTextures; /// Maximum number of texture handles.
	uint maxTextureSamplers; /// Maximum number of texture samplers.
	uint maxComputeBindings; /// Maximum number of compute bindings.
	uint maxVertexLayouts; /// Maximum number of vertex format layouts.
	uint maxVertexStreams; /// Maximum number of vertex streams.
	uint maxIndexBuffers; /// Maximum number of index buffer handles.
	uint maxVertexBuffers; /// Maximum number of vertex buffer handles.
	uint maxDynamicIndexBuffers; /// Maximum number of dynamic index buffer handles.
	uint maxDynamicVertexBuffers; /// Maximum number of dynamic vertex buffer handles.
	uint maxUniforms; /// Maximum number of uniform handles.
	uint maxOcclusionQueries; /// Maximum number of occlusion query handles.
	uint maxEncoders; /// Maximum number of encoder threads.
	uint minResourceCbSize; /// Minimum resource command buffer size.
	uint transientVbSize; /// Maximum transient vertex buffer size.
	uint transientIbSize; /// Maximum transient index buffer size.
}

/// Renderer capabilities.
struct bgfx_caps_t
{
	bgfx_renderer_type_t rendererType; /// Renderer backend type. See: `bgfx::RendererType`

	/**
	 * Supported functionality.
	 *   @attention See `BGFX_CAPS_*` flags at https://bkaradzic.github.io/bgfx/bgfx.html#available-caps
	 */
	ulong supported;
	ushort vendorId; /// Selected GPU vendor PCI id.
	ushort deviceId; /// Selected GPU device id.
	bool homogeneousDepth; /// True when NDC depth is in [-1, 1] range, otherwise its [0, 1].
	bool originBottomLeft; /// True when NDC origin is at bottom left.
	byte numGPUs; /// Number of enumerated GPUs.
	bgfx_caps_gpu_t[4] gpu; /// Enumerated GPUs.
	bgfx_caps_limits_t limits; /// Renderer runtime limits.

	/**
	 * Supported texture format capabilities flags:
	 *   - `BGFX_CAPS_FORMAT_TEXTURE_NONE` - Texture format is not supported.
	 *   - `BGFX_CAPS_FORMAT_TEXTURE_2D` - Texture format is supported.
	 *   - `BGFX_CAPS_FORMAT_TEXTURE_2D_SRGB` - Texture as sRGB format is supported.
	 *   - `BGFX_CAPS_FORMAT_TEXTURE_2D_EMULATED` - Texture format is emulated.
	 *   - `BGFX_CAPS_FORMAT_TEXTURE_3D` - Texture format is supported.
	 *   - `BGFX_CAPS_FORMAT_TEXTURE_3D_SRGB` - Texture as sRGB format is supported.
	 *   - `BGFX_CAPS_FORMAT_TEXTURE_3D_EMULATED` - Texture format is emulated.
	 *   - `BGFX_CAPS_FORMAT_TEXTURE_CUBE` - Texture format is supported.
	 *   - `BGFX_CAPS_FORMAT_TEXTURE_CUBE_SRGB` - Texture as sRGB format is supported.
	 *   - `BGFX_CAPS_FORMAT_TEXTURE_CUBE_EMULATED` - Texture format is emulated.
	 *   - `BGFX_CAPS_FORMAT_TEXTURE_VERTEX` - Texture format can be used from vertex shader.
	 *   - `BGFX_CAPS_FORMAT_TEXTURE_IMAGE_READ` - Texture format can be used as image
	 *     and read from.
	 *   - `BGFX_CAPS_FORMAT_TEXTURE_IMAGE_WRITE` - Texture format can be used as image
	 *     and written to.
	 *   - `BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER` - Texture format can be used as frame
	 *     buffer.
	 *   - `BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA` - Texture format can be used as MSAA
	 *     frame buffer.
	 *   - `BGFX_CAPS_FORMAT_TEXTURE_MSAA` - Texture can be sampled as MSAA.
	 *   - `BGFX_CAPS_FORMAT_TEXTURE_MIP_AUTOGEN` - Texture format supports auto-generated
	 *     mips.
	 */
	ushort[bgfx_texture_format_t.BGFX_TEXTURE_FORMAT_COUNT] formats;
}

/// Internal data.
struct bgfx_internal_data_t
{
	const(bgfx_caps_t)* caps; /// Renderer capabilities.
	void* context; /// GL context, or D3D device.
}

/// Platform data.
struct bgfx_platform_data_t
{
	void* ndt; /// Native display type (*nix specific).

	/**
	 * Native window handle. If `NULL` bgfx will create headless
	 * context/device if renderer API supports it.
	 */
	void* nwh;
	void* context; /// GL context, or D3D device. If `NULL`, bgfx will create context/device.

	/**
	 * GL back-buffer, or D3D render target view. If `NULL` bgfx will
	 * create back-buffer color surface.
	 */
	void* backBuffer;

	/**
	 * Backbuffer depth/stencil. If `NULL` bgfx will create back-buffer
	 * depth/stencil surface.
	 */
	void* backBufferDS;
}

/// Backbuffer resolution and reset parameters.
struct bgfx_resolution_t
{
	bgfx_texture_format_t format; /// Backbuffer format.
	uint width; /// Backbuffer width.
	uint height; /// Backbuffer height.
	uint reset; /// Reset parameters.
	byte numBackBuffers; /// Number of back buffers.
	byte maxFrameLatency; /// Maximum frame latency.
}

/// Configurable runtime limits parameters.
struct bgfx_init_limits_t
{
	ushort maxEncoders; /// Maximum number of encoder threads.
	uint minResourceCbSize; /// Minimum resource command buffer size.
	uint transientVbSize; /// Maximum transient vertex buffer size.
	uint transientIbSize; /// Maximum transient index buffer size.
}

/// Initialization parameters used by `bgfx::init`.
struct bgfx_init_t
{

	/**
	 * Select rendering backend. When set to RendererType::Count
	 * a default rendering backend will be selected appropriate to the platform.
	 * See: `bgfx::RendererType`
	 */
	bgfx_renderer_type_t type;

	/**
	 * Vendor PCI id. If set to `BGFX_PCI_ID_NONE` it will select the first
	 * device.
	 *   - `BGFX_PCI_ID_NONE` - Autoselect adapter.
	 *   - `BGFX_PCI_ID_SOFTWARE_RASTERIZER` - Software rasterizer.
	 *   - `BGFX_PCI_ID_AMD` - AMD adapter.
	 *   - `BGFX_PCI_ID_INTEL` - Intel adapter.
	 *   - `BGFX_PCI_ID_NVIDIA` - nVidia adapter.
	 */
	ushort vendorId;

	/**
	 * Device id. If set to 0 it will select first device, or device with
	 * matching id.
	 */
	ushort deviceId;
	ulong capabilities; /// Capabilities initialization mask (default: UINT64_MAX).
	bool debug_; /// Enable device for debuging.
	bool profile; /// Enable device for profiling.
	bgfx_platform_data_t platformData; /// Platform data.
	bgfx_resolution_t resolution; /// Backbuffer resolution and reset parameters. See: `bgfx::Resolution`.
	bgfx_init_limits_t limits; /// Configurable runtime limits parameters.

	/**
	 * Provide application specific callback interface.
	 * See: `bgfx::CallbackI`
	 */
	void* callback;

	/**
	 * Custom allocator. When a custom allocator is not
	 * specified, bgfx uses the CRT allocator. Bgfx assumes
	 * custom allocator is thread safe.
	 */
	void* allocator;
}

/**
 * Memory must be obtained by calling `bgfx::alloc`, `bgfx::copy`, or `bgfx::makeRef`.
 * @attention It is illegal to create this structure on stack and pass it to any bgfx API.
 */
struct bgfx_memory_t
{
	byte* data; /// Pointer to data.
	uint size; /// Data size.
}

/// Transient index buffer.
struct bgfx_transient_index_buffer_t
{
	byte* data; /// Pointer to data.
	uint size; /// Data size.
	uint startIndex; /// First index.
	bgfx_index_buffer_handle_t handle; /// Index buffer handle.
	bool isIndex16; /// Index buffer format is 16-bits if true, otherwise it is 32-bit.
}

/// Transient vertex buffer.
struct bgfx_transient_vertex_buffer_t
{
	byte* data; /// Pointer to data.
	uint size; /// Data size.
	uint startVertex; /// First vertex.
	ushort stride; /// Vertex stride.
	bgfx_vertex_buffer_handle_t handle; /// Vertex buffer handle.
	bgfx_vertex_layout_handle_t layoutHandle; /// Vertex layout handle.
}

/// Instance data buffer info.
struct bgfx_instance_data_buffer_t
{
	byte* data; /// Pointer to data.
	uint size; /// Data size.
	uint offset; /// Offset in vertex buffer.
	uint num; /// Number of instances.
	ushort stride; /// Vertex buffer stride.
	bgfx_vertex_buffer_handle_t handle; /// Vertex buffer object handle.
}

/// Texture info.
struct bgfx_texture_info_t
{
	bgfx_texture_format_t format; /// Texture format.
	uint storageSize; /// Total amount of bytes required to store texture.
	ushort width; /// Texture width.
	ushort height; /// Texture height.
	ushort depth; /// Texture depth.
	ushort numLayers; /// Number of layers in texture array.
	byte numMips; /// Number of MIP maps.
	byte bitsPerPixel; /// Format bits per pixel.
	bool cubeMap; /// Texture is cubemap.
}

/// Uniform info.
struct bgfx_uniform_info_t
{
	char[256] name; /// Uniform name.
	bgfx_uniform_type_t type; /// Uniform type.
	ushort num; /// Number of elements in array.
}

/// Frame buffer texture attachment info.
struct bgfx_attachment_t
{
	bgfx_access_t access; /// Attachment access. See `Access::Enum`.
	bgfx_texture_handle_t handle; /// Render target texture handle.
	ushort mip; /// Mip level.
	ushort layer; /// Cubemap side or depth layer/slice to use.
	ushort numLayers; /// Number of texture layer/slice(s) in array to use.
	byte resolve; /// Resolve flags. See: `BGFX_RESOLVE_*`
}

/// Transform data.
struct bgfx_transform_t
{
	float* data; /// Pointer to first 4x4 matrix.
	ushort num; /// Number of matrices.
}

/// View stats.
struct bgfx_view_stats_t
{
	char[256] name; /// View name.
	bgfx_view_id_t view; /// View id.
	long cpuTimeBegin; /// CPU (submit) begin time.
	long cpuTimeEnd; /// CPU (submit) end time.
	long gpuTimeBegin; /// GPU begin time.
	long gpuTimeEnd; /// GPU end time.
}

/// Encoder stats.
struct bgfx_encoder_stats_t
{
	long cpuTimeBegin; /// Encoder thread CPU submit begin time.
	long cpuTimeEnd; /// Encoder thread CPU submit end time.
}

/**
 * Renderer statistics data.
 * @remarks All time values are high-resolution timestamps, while
 * time frequencies define timestamps-per-second for that hardware.
 */
struct bgfx_stats_t
{
	long cpuTimeFrame; /// CPU time between two `bgfx::frame` calls.
	long cpuTimeBegin; /// Render thread CPU submit begin time.
	long cpuTimeEnd; /// Render thread CPU submit end time.
	long cpuTimerFreq; /// CPU timer frequency. Timestamps-per-second
	long gpuTimeBegin; /// GPU frame begin time.
	long gpuTimeEnd; /// GPU frame end time.
	long gpuTimerFreq; /// GPU timer frequency.
	long waitRender; /// Time spent waiting for render backend thread to finish issuing draw commands to underlying graphics API.
	long waitSubmit; /// Time spent waiting for submit thread to advance to next frame.
	uint numDraw; /// Number of draw calls submitted.
	uint numCompute; /// Number of compute calls submitted.
	uint numBlit; /// Number of blit calls submitted.
	uint maxGpuLatency; /// GPU driver latency.
	ushort numDynamicIndexBuffers; /// Number of used dynamic index buffers.
	ushort numDynamicVertexBuffers; /// Number of used dynamic vertex buffers.
	ushort numFrameBuffers; /// Number of used frame buffers.
	ushort numIndexBuffers; /// Number of used index buffers.
	ushort numOcclusionQueries; /// Number of used occlusion queries.
	ushort numPrograms; /// Number of used programs.
	ushort numShaders; /// Number of used shaders.
	ushort numTextures; /// Number of used textures.
	ushort numUniforms; /// Number of used uniforms.
	ushort numVertexBuffers; /// Number of used vertex buffers.
	ushort numVertexLayouts; /// Number of used vertex layouts.
	long textureMemoryUsed; /// Estimate of texture memory used.
	long rtMemoryUsed; /// Estimate of render target memory used.
	int transientVbUsed; /// Amount of transient vertex buffer used.
	int transientIbUsed; /// Amount of transient index buffer used.
	uint[bgfx_topology_t.BGFX_TOPOLOGY_COUNT] numPrims; /// Number of primitives rendered.
	long gpuMemoryMax; /// Maximum available GPU memory for application.
	long gpuMemoryUsed; /// Amount of GPU memory used by the application.
	ushort width; /// Backbuffer width in pixels.
	ushort height; /// Backbuffer height in pixels.
	ushort textWidth; /// Debug text width in characters.
	ushort textHeight; /// Debug text height in characters.
	ushort numViews; /// Number of view stats.
	bgfx_view_stats_t* viewStats; /// Array of View stats.
	byte numEncoders; /// Number of encoders used during frame.
	bgfx_encoder_stats_t* encoderStats; /// Array of encoder stats.
}

/// Vertex layout.
struct bgfx_vertex_layout_t
{
	uint hash; /// Hash.
	ushort stride; /// Stride.
	ushort[bgfx_attrib_t.BGFX_ATTRIB_COUNT] offset; /// Attribute offsets.
	ushort[bgfx_attrib_t.BGFX_ATTRIB_COUNT] attributes; /// Used attributes.
}

/**
 * Encoders are used for submitting draw calls from multiple threads. Only one encoder
 * per thread should be used. Use `bgfx::begin()` to obtain an encoder for a thread.
 */
struct bgfx_encoder_t
{
}

struct bgfx_dynamic_index_buffer_handle_t { ushort idx; }

struct bgfx_dynamic_vertex_buffer_handle_t { ushort idx; }

struct bgfx_frame_buffer_handle_t { ushort idx; }

struct bgfx_index_buffer_handle_t { ushort idx; }

struct bgfx_indirect_buffer_handle_t { ushort idx; }

struct bgfx_occlusion_query_handle_t { ushort idx; }

struct bgfx_program_handle_t { ushort idx; }

struct bgfx_shader_handle_t { ushort idx; }

struct bgfx_texture_handle_t { ushort idx; }

struct bgfx_uniform_handle_t { ushort idx; }

struct bgfx_vertex_buffer_handle_t { ushort idx; }

struct bgfx_vertex_layout_handle_t { ushort idx; }

