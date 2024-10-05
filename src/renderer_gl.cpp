/*
 * Copyright 2011-2024 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "bgfx_p.h"

#if (BGFX_CONFIG_RENDERER_OPENGLES || BGFX_CONFIG_RENDERER_OPENGL)
#	include "renderer_gl.h"
#	include <bx/timer.h>
#	include <bx/uint32_t.h>
#	include "emscripten.h"

namespace bgfx { namespace gl
{
	static char s_viewName[BGFX_CONFIG_MAX_VIEWS][BGFX_CONFIG_MAX_VIEW_NAME];

	inline void setViewType(ViewId _view, const bx::StringView _str)
	{
		if (BX_ENABLED(BGFX_CONFIG_DEBUG_ANNOTATION || BGFX_CONFIG_PROFILER) )
		{
			bx::memCopy(&s_viewName[_view][3], _str.getPtr(), _str.getLength() );
		}
	}

	struct PrimInfo
	{
		GLenum m_type;
		uint32_t m_min;
		uint32_t m_div;
		uint32_t m_sub;
	};

	static const PrimInfo s_primInfo[] =
	{
		{ GL_TRIANGLES,      3, 3, 0 },
		{ GL_TRIANGLE_STRIP, 3, 1, 2 },
		{ GL_LINES,          2, 2, 0 },
		{ GL_LINE_STRIP,     2, 1, 1 },
		{ GL_POINTS,         1, 1, 0 },
		{ GL_ZERO,           0, 0, 0 },
	};
	BX_STATIC_ASSERT(Topology::Count == BX_COUNTOF(s_primInfo)-1);

	static const char* s_attribName[] =
	{
		"a_position",
		"a_normal",
		"a_tangent",
		"a_bitangent",
		"a_color0",
		"a_color1",
		"a_color2",
		"a_color3",
		"a_indices",
		"a_weight",
		"a_texcoord0",
		"a_texcoord1",
		"a_texcoord2",
		"a_texcoord3",
		"a_texcoord4",
		"a_texcoord5",
		"a_texcoord6",
		"a_texcoord7",
	};
	BX_STATIC_ASSERT(Attrib::Count == BX_COUNTOF(s_attribName) );

	static const char* s_instanceDataName[] =
	{
		"i_data0",
		"i_data1",
		"i_data2",
		"i_data3",
		"i_data4",
	};
	BX_STATIC_ASSERT(BGFX_CONFIG_MAX_INSTANCE_DATA_COUNT == BX_COUNTOF(s_instanceDataName) );

	static const GLenum s_access[] =
	{
		GL_READ_ONLY,
		GL_WRITE_ONLY,
		GL_READ_WRITE,
	};
	BX_STATIC_ASSERT(Access::Count == BX_COUNTOF(s_access) );

	static const GLenum s_attribType[] =
	{
		GL_UNSIGNED_BYTE,            // Uint8
		GL_UNSIGNED_INT_10_10_10_2,  // Uint10
		GL_SHORT,                    // Int16
		GL_HALF_FLOAT,               // Half
		GL_FLOAT,                    // Float
	};
	BX_STATIC_ASSERT(AttribType::Count == BX_COUNTOF(s_attribType) );

	struct Blend
	{
		GLenum m_src;
		GLenum m_dst;
		bool m_factor;
	};

	static const Blend s_blendFactor[] =
	{
		{ 0,                           0,                           false }, // ignored
		{ GL_ZERO,                     GL_ZERO,                     false }, // ZERO
		{ GL_ONE,                      GL_ONE,                      false }, // ONE
		{ GL_SRC_COLOR,                GL_SRC_COLOR,                false }, // SRC_COLOR
		{ GL_ONE_MINUS_SRC_COLOR,      GL_ONE_MINUS_SRC_COLOR,      false }, // INV_SRC_COLOR
		{ GL_SRC_ALPHA,                GL_SRC_ALPHA,                false }, // SRC_ALPHA
		{ GL_ONE_MINUS_SRC_ALPHA,      GL_ONE_MINUS_SRC_ALPHA,      false }, // INV_SRC_ALPHA
		{ GL_DST_ALPHA,                GL_DST_ALPHA,                false }, // DST_ALPHA
		{ GL_ONE_MINUS_DST_ALPHA,      GL_ONE_MINUS_DST_ALPHA,      false }, // INV_DST_ALPHA
		{ GL_DST_COLOR,                GL_DST_COLOR,                false }, // DST_COLOR
		{ GL_ONE_MINUS_DST_COLOR,      GL_ONE_MINUS_DST_COLOR,      false }, // INV_DST_COLOR
		{ GL_SRC_ALPHA_SATURATE,       GL_ONE,                      false }, // SRC_ALPHA_SAT
		{ GL_CONSTANT_COLOR,           GL_CONSTANT_COLOR,           true  }, // FACTOR
		{ GL_ONE_MINUS_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_COLOR, true  }, // INV_FACTOR
	};

	static const GLenum s_blendEquation[] =
	{
		GL_FUNC_ADD,
		GL_FUNC_SUBTRACT,
		GL_FUNC_REVERSE_SUBTRACT,
		GL_MIN,
		GL_MAX,
	};

	static const GLenum s_cmpFunc[] =
	{
		0, // ignored
		GL_LESS,
		GL_LEQUAL,
		GL_EQUAL,
		GL_GEQUAL,
		GL_GREATER,
		GL_NOTEQUAL,
		GL_NEVER,
		GL_ALWAYS,
	};

	static const GLenum s_stencilOp[] =
	{
		GL_ZERO,
		GL_KEEP,
		GL_REPLACE,
		GL_INCR_WRAP,
		GL_INCR,
		GL_DECR_WRAP,
		GL_DECR,
		GL_INVERT,
	};

	static const GLenum s_stencilFace[] =
	{
		GL_FRONT_AND_BACK,
		GL_FRONT,
		GL_BACK,
	};

	static GLenum s_textureAddress[] =
	{
		GL_REPEAT,
		GL_MIRRORED_REPEAT,
		GL_CLAMP_TO_EDGE,
		GL_CLAMP_TO_BORDER,
	};

	static const GLenum s_textureFilterMag[] =
	{
		GL_LINEAR,
		GL_NEAREST,
		GL_LINEAR,
	};

	static const GLenum s_textureFilterMin[][3] =
	{
		{ GL_LINEAR,  GL_LINEAR_MIPMAP_LINEAR,  GL_LINEAR_MIPMAP_NEAREST  },
		{ GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST_MIPMAP_NEAREST },
		{ GL_LINEAR,  GL_LINEAR_MIPMAP_LINEAR,  GL_LINEAR_MIPMAP_NEAREST  },
	};

	struct TextureFormatInfo
	{
		GLenum m_internalFmt;
		GLenum m_internalFmtSrgb;
		GLenum m_fmt;
		GLenum m_fmtSrgb;
		GLenum m_type;
		bool   m_supported;
		GLint  m_mapping[4];
	};

// In desktop OpenGL 4+ and OpenGL ES 3.0+, specific GL formats GL_x_INTEGER are used for integer textures.
// For older desktop OpenGL contexts, GL names without _INTEGER suffix were used.
// See http://docs.gl/gl4/glTexImage2D, http://docs.gl/gl3/glTexImage2D, http://docs.gl/es3/glTexImage2D
#if BGFX_CONFIG_RENDERER_OPENGL >= 40 || BGFX_CONFIG_RENDERER_OPENGLES
#	define RED_INTEGER  GL_RED_INTEGER
#	define RG_INTEGER   GL_RG_INTEGER
#	define RGB_INTEGER  GL_RGB_INTEGER
#	define RGBA_INTEGER GL_RGBA_INTEGER
#else
#	define RED_INTEGER  GL_RED
#	define RG_INTEGER   GL_RG
#	define RGB_INTEGER  GL_RGB
#	define RGBA_INTEGER GL_RGBA
#endif

	static TextureFormatInfo s_textureFormat[] =
	{
#define $_ -1
#define $0 GL_ZERO
#define $1 GL_ONE
#define $R GL_RED
#define $G GL_GREEN
#define $B GL_BLUE
#define $A GL_ALPHA
		{ GL_COMPRESSED_RGBA_S3TC_DXT1_EXT,            GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT,       GL_COMPRESSED_RGBA_S3TC_DXT1_EXT,            GL_COMPRESSED_RGBA_S3TC_DXT1_EXT,            GL_ZERO,                         false, { $_, $_, $_, $_ } }, // BC1
		{ GL_COMPRESSED_RGBA_S3TC_DXT3_EXT,            GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT,       GL_COMPRESSED_RGBA_S3TC_DXT3_EXT,            GL_COMPRESSED_RGBA_S3TC_DXT3_EXT,            GL_ZERO,                         false, { $_, $_, $_, $_ } }, // BC2
		{ GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,            GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT,       GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,            GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,            GL_ZERO,                         false, { $_, $_, $_, $_ } }, // BC3
		{ GL_COMPRESSED_LUMINANCE_LATC1_EXT,           GL_ZERO,                                      GL_COMPRESSED_LUMINANCE_LATC1_EXT,           GL_COMPRESSED_LUMINANCE_LATC1_EXT,           GL_ZERO,                         false, { $_, $_, $_, $_ } }, // BC4
		{ GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT,     GL_ZERO,                                      GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT,     GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT,     GL_ZERO,                         false, { $_, $_, $_, $_ } }, // BC5
		{ GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB,     GL_ZERO,                                      GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB,     GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB,     GL_ZERO,                         false, { $_, $_, $_, $_ } }, // BC6H
		{ GL_COMPRESSED_RGBA_BPTC_UNORM_ARB,           GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_ARB,      GL_COMPRESSED_RGBA_BPTC_UNORM_ARB,           GL_COMPRESSED_RGBA_BPTC_UNORM_ARB,           GL_ZERO,                         false, { $_, $_, $_, $_ } }, // BC7
		{ GL_ETC1_RGB8_OES,                            GL_ZERO,                                      GL_ETC1_RGB8_OES,                            GL_ETC1_RGB8_OES,                            GL_ZERO,                         false, { $_, $_, $_, $_ } }, // ETC1
		{ GL_COMPRESSED_RGB8_ETC2,                     GL_ZERO,                                      GL_COMPRESSED_RGB8_ETC2,                     GL_COMPRESSED_RGB8_ETC2,                     GL_ZERO,                         false, { $_, $_, $_, $_ } }, // ETC2
		{ GL_COMPRESSED_RGBA8_ETC2_EAC,                GL_COMPRESSED_SRGB8_ETC2,                     GL_COMPRESSED_RGBA8_ETC2_EAC,                GL_COMPRESSED_RGBA8_ETC2_EAC,                GL_ZERO,                         false, { $_, $_, $_, $_ } }, // ETC2A
		{ GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2, GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2, GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2, GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2, GL_ZERO,                         false, { $_, $_, $_, $_ } }, // ETC2A1
		{ GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG,          GL_COMPRESSED_SRGB_PVRTC_2BPPV1_EXT,          GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG,          GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG,          GL_ZERO,                         false, { $_, $_, $_, $_ } }, // PTC12
		{ GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG,          GL_COMPRESSED_SRGB_PVRTC_4BPPV1_EXT,          GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG,          GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG,          GL_ZERO,                         false, { $_, $_, $_, $_ } }, // PTC14
		{ GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG,         GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV1_EXT,    GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG,         GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG,         GL_ZERO,                         false, { $_, $_, $_, $_ } }, // PTC12A
		{ GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG,         GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV1_EXT,    GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG,         GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG,         GL_ZERO,                         false, { $_, $_, $_, $_ } }, // PTC14A
		{ GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG,         GL_ZERO,                                      GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG,         GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG,         GL_ZERO,                         false, { $_, $_, $_, $_ } }, // PTC22
		{ GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG,         GL_ZERO,                                      GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG,         GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG,         GL_ZERO,                         false, { $_, $_, $_, $_ } }, // PTC24
		{ GL_ATC_RGB_AMD,                              GL_ZERO,                                      GL_ATC_RGB_AMD,                              GL_ATC_RGB_AMD,                              GL_ZERO,                         false, { $_, $_, $_, $_ } }, // ATC
		{ GL_ATC_RGBA_EXPLICIT_ALPHA_AMD,              GL_ZERO,                                      GL_ATC_RGBA_EXPLICIT_ALPHA_AMD,              GL_ATC_RGBA_EXPLICIT_ALPHA_AMD,              GL_ZERO,                         false, { $_, $_, $_, $_ } }, // ATCE
		{ GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD,          GL_ZERO,                                      GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD,          GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD,          GL_ZERO,                         false, { $_, $_, $_, $_ } }, // ATCI
		{ GL_COMPRESSED_RGBA_ASTC_4x4_KHR,             GL_COMPRESSED_SRGB8_ASTC_4x4_KHR,             GL_COMPRESSED_RGBA_ASTC_4x4_KHR,             GL_COMPRESSED_RGBA_ASTC_4x4_KHR,             GL_ZERO,                         false, { $_, $_, $_, $_ } }, // ASTC4x4
		{ GL_COMPRESSED_RGBA_ASTC_5x4_KHR,             GL_COMPRESSED_SRGB8_ASTC_5x4_KHR,             GL_COMPRESSED_RGBA_ASTC_5x4_KHR,             GL_COMPRESSED_RGBA_ASTC_5x4_KHR,             GL_ZERO,                         false, { $_, $_, $_, $_ } }, // ASTC5x4
		{ GL_COMPRESSED_RGBA_ASTC_5x5_KHR,             GL_COMPRESSED_SRGB8_ASTC_5x5_KHR,             GL_COMPRESSED_RGBA_ASTC_5x5_KHR,             GL_COMPRESSED_RGBA_ASTC_5x5_KHR,             GL_ZERO,                         false, { $_, $_, $_, $_ } }, // ASTC5x5
		{ GL_COMPRESSED_RGBA_ASTC_6x5_KHR,             GL_COMPRESSED_SRGB8_ASTC_6x5_KHR,             GL_COMPRESSED_RGBA_ASTC_6x5_KHR,             GL_COMPRESSED_RGBA_ASTC_6x5_KHR,             GL_ZERO,                         false, { $_, $_, $_, $_ } }, // ASTC6x5
		{ GL_COMPRESSED_RGBA_ASTC_6x6_KHR,             GL_COMPRESSED_SRGB8_ASTC_6x6_KHR,             GL_COMPRESSED_RGBA_ASTC_6x6_KHR,             GL_COMPRESSED_RGBA_ASTC_6x6_KHR,             GL_ZERO,                         false, { $_, $_, $_, $_ } }, // ASTC6x6
		{ GL_COMPRESSED_RGBA_ASTC_8x5_KHR,             GL_COMPRESSED_SRGB8_ASTC_8x5_KHR,             GL_COMPRESSED_RGBA_ASTC_8x5_KHR,             GL_COMPRESSED_RGBA_ASTC_8x5_KHR,             GL_ZERO,                         false, { $_, $_, $_, $_ } }, // ASTC8x5
		{ GL_COMPRESSED_RGBA_ASTC_8x6_KHR,             GL_COMPRESSED_SRGB8_ASTC_8x6_KHR,             GL_COMPRESSED_RGBA_ASTC_8x6_KHR,             GL_COMPRESSED_RGBA_ASTC_8x6_KHR,             GL_ZERO,                         false, { $_, $_, $_, $_ } }, // ASTC8x6
		{ GL_COMPRESSED_RGBA_ASTC_8x8_KHR,             GL_COMPRESSED_SRGB8_ASTC_8x8_KHR,             GL_COMPRESSED_RGBA_ASTC_8x8_KHR,             GL_COMPRESSED_RGBA_ASTC_8x8_KHR,             GL_ZERO,                         false, { $_, $_, $_, $_ } }, // ASTC8x8
		{ GL_COMPRESSED_RGBA_ASTC_10x5_KHR,            GL_COMPRESSED_SRGB8_ASTC_10x5_KHR,            GL_COMPRESSED_RGBA_ASTC_10x5_KHR,            GL_COMPRESSED_RGBA_ASTC_10x5_KHR,            GL_ZERO,                         false, { $_, $_, $_, $_ } }, // ASTC10x5
		{ GL_COMPRESSED_RGBA_ASTC_10x6_KHR,            GL_COMPRESSED_SRGB8_ASTC_10x6_KHR,            GL_COMPRESSED_RGBA_ASTC_10x6_KHR,            GL_COMPRESSED_RGBA_ASTC_10x6_KHR,            GL_ZERO,                         false, { $_, $_, $_, $_ } }, // ASTC10x6
		{ GL_COMPRESSED_RGBA_ASTC_10x8_KHR,            GL_COMPRESSED_SRGB8_ASTC_10x8_KHR,            GL_COMPRESSED_RGBA_ASTC_10x8_KHR,            GL_COMPRESSED_RGBA_ASTC_10x8_KHR,            GL_ZERO,                         false, { $_, $_, $_, $_ } }, // ASTC10x8
		{ GL_COMPRESSED_RGBA_ASTC_10x10_KHR,           GL_COMPRESSED_SRGB8_ASTC_10x10_KHR,           GL_COMPRESSED_RGBA_ASTC_10x10_KHR,           GL_COMPRESSED_RGBA_ASTC_10x10_KHR,           GL_ZERO,                         false, { $_, $_, $_, $_ } }, // ASTC10x10
		{ GL_COMPRESSED_RGBA_ASTC_12x10_KHR,           GL_COMPRESSED_SRGB8_ASTC_12x10_KHR,           GL_COMPRESSED_RGBA_ASTC_12x10_KHR,           GL_COMPRESSED_RGBA_ASTC_12x10_KHR,           GL_ZERO,                         false, { $_, $_, $_, $_ } }, // ASTC12x10
		{ GL_COMPRESSED_RGBA_ASTC_12x12_KHR,           GL_COMPRESSED_SRGB8_ASTC_12x12_KHR,           GL_COMPRESSED_RGBA_ASTC_12x12_KHR,           GL_COMPRESSED_RGBA_ASTC_12x12_KHR,           GL_ZERO,                         false, { $_, $_, $_, $_ } }, // ASTC12x12
		{ GL_ZERO,                                     GL_ZERO,                                      GL_ZERO,                                     GL_ZERO,                                     GL_ZERO,                         false, { $_, $_, $_, $_ } }, // Unknown
		{ GL_ZERO,                                     GL_ZERO,                                      GL_ZERO,                                     GL_ZERO,                                     GL_ZERO,                         false, { $_, $_, $_, $_ } }, // R1
		{ GL_ALPHA,                                    GL_ZERO,                                      GL_ALPHA,                                    GL_ALPHA,                                    GL_UNSIGNED_BYTE,                false, { $_, $_, $_, $_ } }, // A8
		{ GL_R8,                                       GL_ZERO,                                      GL_RED,                                      GL_RED,                                      GL_UNSIGNED_BYTE,                false, { $_, $_, $_, $_ } }, // R8
		{ GL_R8I,                                      GL_ZERO,                                      RED_INTEGER,                                 GL_RED_INTEGER,                              GL_BYTE,                         false, { $_, $_, $_, $_ } }, // R8I
		{ GL_R8UI,                                     GL_ZERO,                                      RED_INTEGER,                                 GL_RED_INTEGER,                              GL_UNSIGNED_BYTE,                false, { $_, $_, $_, $_ } }, // R8U
		{ GL_R8_SNORM,                                 GL_ZERO,                                      GL_RED,                                      GL_RED,                                      GL_BYTE,                         false, { $_, $_, $_, $_ } }, // R8S
		{ GL_R16,                                      GL_ZERO,                                      GL_RED,                                      GL_RED,                                      GL_UNSIGNED_SHORT,               false, { $_, $_, $_, $_ } }, // R16
		{ GL_R16I,                                     GL_ZERO,                                      RED_INTEGER,                                 GL_RED_INTEGER,                              GL_SHORT,                        false, { $_, $_, $_, $_ } }, // R16I
		{ GL_R16UI,                                    GL_ZERO,                                      RED_INTEGER,                                 GL_RED_INTEGER,                              GL_UNSIGNED_SHORT,               false, { $_, $_, $_, $_ } }, // R16U
		{ GL_R16F,                                     GL_ZERO,                                      GL_RED,                                      GL_RED,                                      GL_HALF_FLOAT,                   false, { $_, $_, $_, $_ } }, // R16F
		{ GL_R16_SNORM,                                GL_ZERO,                                      GL_RED,                                      GL_RED,                                      GL_SHORT,                        false, { $_, $_, $_, $_ } }, // R16S
		{ GL_R32I,                                     GL_ZERO,                                      RED_INTEGER,                                 GL_RED_INTEGER,                              GL_INT,                          false, { $_, $_, $_, $_ } }, // R32I
		{ GL_R32UI,                                    GL_ZERO,                                      RED_INTEGER,                                 GL_RED_INTEGER,                              GL_UNSIGNED_INT,                 false, { $_, $_, $_, $_ } }, // R32U
		{ GL_R32F,                                     GL_ZERO,                                      GL_RED,                                      GL_RED,                                      GL_FLOAT,                        false, { $_, $_, $_, $_ } }, // R32F
		{ GL_RG8,                                      GL_ZERO,                                      GL_RG,                                       GL_RG,                                       GL_UNSIGNED_BYTE,                false, { $_, $_, $_, $_ } }, // RG8
		{ GL_RG8I,                                     GL_ZERO,                                      RG_INTEGER,                                  GL_RG_INTEGER,                               GL_BYTE,                         false, { $_, $_, $_, $_ } }, // RG8I
		{ GL_RG8UI,                                    GL_ZERO,                                      RG_INTEGER,                                  GL_RG_INTEGER,                               GL_UNSIGNED_BYTE,                false, { $_, $_, $_, $_ } }, // RG8U
		{ GL_RG8_SNORM,                                GL_ZERO,                                      GL_RG,                                       GL_RG,                                       GL_BYTE,                         false, { $_, $_, $_, $_ } }, // RG8S
		{ GL_RG16,                                     GL_ZERO,                                      GL_RG,                                       GL_RG,                                       GL_UNSIGNED_SHORT,               false, { $_, $_, $_, $_ } }, // RG16
		{ GL_RG16I,                                    GL_ZERO,                                      RG_INTEGER,                                  GL_RG_INTEGER,                               GL_SHORT,                        false, { $_, $_, $_, $_ } }, // RG16I
		{ GL_RG16UI,                                   GL_ZERO,                                      RG_INTEGER,                                  GL_RG_INTEGER,                               GL_UNSIGNED_SHORT,               false, { $_, $_, $_, $_ } }, // RG16U
		{ GL_RG16F,                                    GL_ZERO,                                      GL_RG,                                       GL_RG,                                       GL_HALF_FLOAT,                   false, { $_, $_, $_, $_ } }, // RG16F
		{ GL_RG16_SNORM,                               GL_ZERO,                                      GL_RG,                                       GL_RG,                                       GL_SHORT,                        false, { $_, $_, $_, $_ } }, // RG16S
		{ GL_RG32I,                                    GL_ZERO,                                      RG_INTEGER,                                  GL_RG_INTEGER,                               GL_INT,                          false, { $_, $_, $_, $_ } }, // RG32I
		{ GL_RG32UI,                                   GL_ZERO,                                      RG_INTEGER,                                  GL_RG_INTEGER,                               GL_UNSIGNED_INT,                 false, { $_, $_, $_, $_ } }, // RG32U
		{ GL_RG32F,                                    GL_ZERO,                                      GL_RG,                                       GL_RG,                                       GL_FLOAT,                        false, { $_, $_, $_, $_ } }, // RG32F
		{ GL_RGB8,                                     GL_SRGB8,                                     GL_RGB,                                      GL_RGB,                                      GL_UNSIGNED_BYTE,                false, { $_, $_, $_, $_ } }, // RGB8
		{ GL_RGB8I,                                    GL_ZERO,                                      RGB_INTEGER,                                 GL_RGB_INTEGER,                              GL_BYTE,                         false, { $_, $_, $_, $_ } }, // RGB8I
		{ GL_RGB8UI,                                   GL_ZERO,                                      RGB_INTEGER,                                 GL_RGB_INTEGER,                              GL_UNSIGNED_BYTE,                false, { $_, $_, $_, $_ } }, // RGB8U
		{ GL_RGB8_SNORM,                               GL_ZERO,                                      GL_RGB,                                      GL_RGB,                                      GL_BYTE,                         false, { $_, $_, $_, $_ } }, // RGB8S
		{ GL_RGB9_E5,                                  GL_ZERO,                                      GL_RGB,                                      GL_RGB,                                      GL_UNSIGNED_INT_5_9_9_9_REV,     false, { $_, $_, $_, $_ } }, // RGB9E5F
		{ GL_RGBA8,                                    GL_SRGB8_ALPHA8,                              GL_BGRA,                                     GL_BGRA,                                     GL_UNSIGNED_BYTE,                false, { $_, $_, $_, $_ } }, // BGRA8
		{ GL_RGBA8,                                    GL_SRGB8_ALPHA8,                              GL_RGBA,                                     GL_RGBA,                                     GL_UNSIGNED_BYTE,                false, { $_, $_, $_, $_ } }, // RGBA8
		{ GL_RGBA8I,                                   GL_ZERO,                                      RGBA_INTEGER,                                GL_RGBA_INTEGER,                             GL_BYTE,                         false, { $_, $_, $_, $_ } }, // RGBA8I
		{ GL_RGBA8UI,                                  GL_ZERO,                                      RGBA_INTEGER,                                GL_RGBA_INTEGER,                             GL_UNSIGNED_BYTE,                false, { $_, $_, $_, $_ } }, // RGBA8U
		{ GL_RGBA8_SNORM,                              GL_ZERO,                                      GL_RGBA,                                     GL_RGBA,                                     GL_BYTE,                         false, { $_, $_, $_, $_ } }, // RGBA8S
		{ GL_RGBA16,                                   GL_ZERO,                                      GL_RGBA,                                     GL_RGBA,                                     GL_UNSIGNED_SHORT,               false, { $_, $_, $_, $_ } }, // RGBA16
		{ GL_RGBA16I,                                  GL_ZERO,                                      RGBA_INTEGER,                                GL_RGBA_INTEGER,                             GL_SHORT,                        false, { $_, $_, $_, $_ } }, // RGBA16I
		{ GL_RGBA16UI,                                 GL_ZERO,                                      RGBA_INTEGER,                                GL_RGBA_INTEGER,                             GL_UNSIGNED_SHORT,               false, { $_, $_, $_, $_ } }, // RGBA16U
		{ GL_RGBA16F,                                  GL_ZERO,                                      GL_RGBA,                                     GL_RGBA,                                     GL_HALF_FLOAT,                   false, { $_, $_, $_, $_ } }, // RGBA16F
		{ GL_RGBA16_SNORM,                             GL_ZERO,                                      GL_RGBA,                                     GL_RGBA,                                     GL_SHORT,                        false, { $_, $_, $_, $_ } }, // RGBA16S
		{ GL_RGBA32I,                                  GL_ZERO,                                      RGBA_INTEGER,                                GL_RGBA_INTEGER,                             GL_INT,                          false, { $_, $_, $_, $_ } }, // RGBA32I
		{ GL_RGBA32UI,                                 GL_ZERO,                                      RGBA_INTEGER,                                GL_RGBA_INTEGER,                             GL_UNSIGNED_INT,                 false, { $_, $_, $_, $_ } }, // RGBA32U
		{ GL_RGBA32F,                                  GL_ZERO,                                      GL_RGBA,                                     GL_RGBA,                                     GL_FLOAT,                        false, { $_, $_, $_, $_ } }, // RGBA32F
		{ GL_RGB565,                                   GL_ZERO,                                      GL_RGB,                                      GL_RGB,                                      GL_UNSIGNED_SHORT_5_6_5,         false, { $_, $_, $_, $_ } }, // B5G6R5
		{ GL_RGB565,                                   GL_ZERO,                                      GL_RGB,                                      GL_RGB,                                      GL_UNSIGNED_SHORT_5_6_5,         false, { $_, $_, $_, $_ } }, // R5G6B5
		{ GL_RGBA4,                                    GL_ZERO,                                      GL_BGRA,                                     GL_BGRA,                                     GL_UNSIGNED_SHORT_4_4_4_4_REV,   false, { $_, $_, $_, $_ } }, // BGRA4
		{ GL_RGBA4,                                    GL_ZERO,                                      GL_RGBA,                                     GL_RGBA,                                     GL_UNSIGNED_SHORT_4_4_4_4_REV,   false, { $_, $_, $_, $_ } }, // RGBA4
		{ GL_RGB5_A1,                                  GL_ZERO,                                      GL_BGRA,                                     GL_BGRA,                                     GL_UNSIGNED_SHORT_1_5_5_5_REV,   false, { $_, $_, $_, $_ } }, // BGR5A1
		{ GL_RGB5_A1,                                  GL_ZERO,                                      GL_RGBA,                                     GL_RGBA,                                     GL_UNSIGNED_SHORT_1_5_5_5_REV,   false, { $_, $_, $_, $_ } }, // RGB5A1
		{ GL_RGB10_A2,                                 GL_ZERO,                                      GL_RGBA,                                     GL_RGBA,                                     GL_UNSIGNED_INT_2_10_10_10_REV,  false, { $_, $_, $_, $_ } }, // RGB10A2
		{ GL_R11F_G11F_B10F,                           GL_ZERO,                                      GL_RGB,                                      GL_RGB,                                      GL_UNSIGNED_INT_10F_11F_11F_REV, false, { $_, $_, $_, $_ } }, // RG11B10F
		{ GL_ZERO,                                     GL_ZERO,                                      GL_ZERO,                                     GL_ZERO,                                     GL_ZERO,                         false, { $_, $_, $_, $_ } }, // UnknownDepth
		{ GL_DEPTH_COMPONENT16,                        GL_ZERO,                                      GL_DEPTH_COMPONENT,                          GL_DEPTH_COMPONENT,                          GL_UNSIGNED_SHORT,               false, { $_, $_, $_, $_ } }, // D16
		{ GL_DEPTH_COMPONENT24,                        GL_ZERO,                                      GL_DEPTH_COMPONENT,                          GL_DEPTH_COMPONENT,                          GL_UNSIGNED_INT,                 false, { $_, $_, $_, $_ } }, // D24
		{ GL_DEPTH24_STENCIL8,                         GL_ZERO,                                      GL_DEPTH_STENCIL,                            GL_DEPTH_STENCIL,                            GL_UNSIGNED_INT_24_8,            false, { $_, $_, $_, $_ } }, // D24S8
		{ GL_DEPTH_COMPONENT32,                        GL_ZERO,                                      GL_DEPTH_COMPONENT,                          GL_DEPTH_COMPONENT,                          GL_UNSIGNED_INT,                 false, { $_, $_, $_, $_ } }, // D32
		{ GL_DEPTH_COMPONENT32F,                       GL_ZERO,                                      GL_DEPTH_COMPONENT,                          GL_DEPTH_COMPONENT,                          GL_FLOAT,                        false, { $_, $_, $_, $_ } }, // D16F
		{ GL_DEPTH_COMPONENT32F,                       GL_ZERO,                                      GL_DEPTH_COMPONENT,                          GL_DEPTH_COMPONENT,                          GL_FLOAT,                        false, { $_, $_, $_, $_ } }, // D24F
		{ GL_DEPTH_COMPONENT32F,                       GL_ZERO,                                      GL_DEPTH_COMPONENT,                          GL_DEPTH_COMPONENT,                          GL_FLOAT,                        false, { $_, $_, $_, $_ } }, // D32F
		{ GL_STENCIL_INDEX8,                           GL_ZERO,                                      GL_STENCIL_INDEX,                            GL_STENCIL_INDEX,                            GL_UNSIGNED_BYTE,                false, { $_, $_, $_, $_ } }, // D0S8
#undef $_
#undef $0
#undef $1
#undef $R
#undef $G
#undef $B
#undef $A
	};
	BX_STATIC_ASSERT(TextureFormat::Count == BX_COUNTOF(s_textureFormat) );

	static bool s_textureFilter[TextureFormat::Count+1];

	static GLenum s_rboFormat[] =
	{
		GL_ZERO,               // BC1
		GL_ZERO,               // BC2
		GL_ZERO,               // BC3
		GL_ZERO,               // BC4
		GL_ZERO,               // BC5
		GL_ZERO,               // BC6H
		GL_ZERO,               // BC7
		GL_ZERO,               // ETC1
		GL_ZERO,               // ETC2
		GL_ZERO,               // ETC2A
		GL_ZERO,               // ETC2A1
		GL_ZERO,               // PTC12
		GL_ZERO,               // PTC14
		GL_ZERO,               // PTC12A
		GL_ZERO,               // PTC14A
		GL_ZERO,               // PTC22
		GL_ZERO,               // PTC24
		GL_ZERO,               // ATC
		GL_ZERO,               // ATCE
		GL_ZERO,               // ATCI
		GL_ZERO,               // ASTC4x4
		GL_ZERO,               // ASTC5x4
		GL_ZERO,               // ASTC5x5
		GL_ZERO,               // ASTC6x5
		GL_ZERO,               // ASTC6x6
		GL_ZERO,               // ASTC8x5
		GL_ZERO,               // ASTC8x6
		GL_ZERO,               // ASTC8x8
		GL_ZERO,               // ASTC10x5
		GL_ZERO,               // ASTC10x6
		GL_ZERO,               // ASTC10x8
		GL_ZERO,               // ASTC10x10
		GL_ZERO,               // ASTC12x10
		GL_ZERO,               // ASTC12x12
		GL_ZERO,               // Unknown
		GL_ZERO,               // R1
		GL_ALPHA,              // A8
		GL_R8,                 // R8
		GL_R8I,                // R8I
		GL_R8UI,               // R8U
		GL_R8_SNORM,           // R8S
		GL_R16,                // R16
		GL_R16I,               // R16I
		GL_R16UI,              // R16U
		GL_R16F,               // R16F
		GL_R16_SNORM,          // R16S
		GL_R32I,               // R32I
		GL_R32UI,              // R32U
		GL_R32F,               // R32F
		GL_RG8,                // RG8
		GL_RG8I,               // RG8I
		GL_RG8UI,              // RG8U
		GL_RG8_SNORM,          // RG8S
		GL_RG16,               // RG16
		GL_RG16I,              // RG16I
		GL_RG16UI,             // RG16U
		GL_RG16F,              // RG16F
		GL_RG16_SNORM,         // RG16S
		GL_RG32I,              // RG32I
		GL_RG32UI,             // RG32U
		GL_RG32F,              // RG32F
		GL_RGB8,               // RGB8
		GL_RGB8I,              // RGB8I
		GL_RGB8UI,             // RGB8UI
		GL_RGB8_SNORM,         // RGB8S
		GL_RGB9_E5,            // RGB9E5F
		GL_RGBA8,              // BGRA8
		GL_RGBA8,              // RGBA8
		GL_RGBA8I,             // RGBA8I
		GL_RGBA8UI,            // RGBA8UI
		GL_RGBA8_SNORM,        // RGBA8S
		GL_RGBA16,             // RGBA16
		GL_RGBA16I,            // RGBA16I
		GL_RGBA16UI,           // RGBA16U
		GL_RGBA16F,            // RGBA16F
		GL_RGBA16_SNORM,       // RGBA16S
		GL_RGBA32I,            // RGBA32I
		GL_RGBA32UI,           // RGBA32U
		GL_RGBA32F,            // RGBA32F
		GL_RGB565,             // B5G6R5
		GL_RGB565,             // R5G6B5
		GL_RGBA4,              // BGRA4
		GL_RGBA4,              // RGBA4
		GL_RGB5_A1,            // BGR5A1
		GL_RGB5_A1,            // RGB5A1
		GL_RGB10_A2,           // RGB10A2
		GL_R11F_G11F_B10F,     // RG11B10F
		GL_ZERO,               // UnknownDepth
		GL_DEPTH_COMPONENT16,  // D16
		GL_DEPTH_COMPONENT24,  // D24
		GL_DEPTH24_STENCIL8,   // D24S8
		GL_DEPTH_COMPONENT32,  // D32
		GL_DEPTH_COMPONENT32F, // D16F
		GL_DEPTH_COMPONENT32F, // D24F
		GL_DEPTH_COMPONENT32F, // D32F
		GL_STENCIL_INDEX8,     // D0S8
	};
	BX_STATIC_ASSERT(TextureFormat::Count == BX_COUNTOF(s_rboFormat) );

	static GLenum s_imageFormat[] =
	{
		GL_ZERO,           // BC1
		GL_ZERO,           // BC2
		GL_ZERO,           // BC3
		GL_ZERO,           // BC4
		GL_ZERO,           // BC5
		GL_ZERO,           // BC6H
		GL_ZERO,           // BC7
		GL_ZERO,           // ETC1
		GL_ZERO,           // ETC2
		GL_ZERO,           // ETC2A
		GL_ZERO,           // ETC2A1
		GL_ZERO,           // PTC12
		GL_ZERO,           // PTC14
		GL_ZERO,           // PTC12A
		GL_ZERO,           // PTC14A
		GL_ZERO,           // PTC22
		GL_ZERO,           // PTC24
		GL_ZERO,           // ATC
		GL_ZERO,           // ATCE
		GL_ZERO,           // ATCI
		GL_ZERO,           // ASTC4x4
		GL_ZERO,           // ASTC5x4
		GL_ZERO,           // ASTC5x5
		GL_ZERO,           // ASTC6x5
		GL_ZERO,           // ASTC6x6
		GL_ZERO,           // ASTC8x5
		GL_ZERO,           // ASTC8x6
		GL_ZERO,           // ASTC8x8
		GL_ZERO,           // ASTC10x5
		GL_ZERO,           // ASTC10x6
		GL_ZERO,           // ASTC10x8
		GL_ZERO,           // ASTC10x10
		GL_ZERO,           // ASTC12x10
		GL_ZERO,           // ASTC12x12
		GL_ZERO,           // Unknown
		GL_ZERO,           // R1
		GL_ALPHA,          // A8
		GL_R8,             // R8
		GL_R8I,            // R8I
		GL_R8UI,           // R8UI
		GL_R8_SNORM,       // R8S
		GL_R16,            // R16
		GL_R16I,           // R16I
		GL_R16UI,          // R16U
		GL_R16F,           // R16F
		GL_R16_SNORM,      // R16S
		GL_R32I,           // R32I
		GL_R32UI,          // R32U
		GL_R32F,           // R32F
		GL_RG8,            // RG8
		GL_RG8I,           // RG8I
		GL_RG8UI,          // RG8U
		GL_RG8_SNORM,      // RG8S
		GL_RG16,           // RG16
		GL_RG16I,          // RG16I
		GL_RG16UI,         // RG16U
		GL_RG16F,          // RG16F
		GL_RG16_SNORM,     // RG16S
		GL_RG32I,          // RG32I
		GL_RG32UI,         // RG32U
		GL_RG32F,          // RG32F
		GL_RGB8,           // RGB8
		GL_RGB8I,          // RGB8I
		GL_RGB8UI,         // RGB8UI
		GL_RGB8_SNORM,     // RGB8S
		GL_RGB9_E5,        // RGB9E5F
		GL_RGBA8,          // BGRA8
		GL_RGBA8,          // RGBA8
		GL_RGBA8I,         // RGBA8I
		GL_RGBA8UI,        // RGBA8UI
		GL_RGBA8_SNORM,    // RGBA8S
		GL_RGBA16,         // RGBA16
		GL_RGBA16I,        // RGBA16I
		GL_RGBA16UI,       // RGBA16U
		GL_RGBA16F,        // RGBA16F
		GL_RGBA16_SNORM,   // RGBA16S
		GL_RGBA32I,        // RGBA32I
		GL_RGBA32UI,       // RGBA32U
		GL_RGBA32F,        // RGBA32F
		GL_RGB565,         // B5G6R5
		GL_RGB565,         // R5G6B5
		GL_RGBA4,          // BGRA4
		GL_RGBA4,          // RGBA4
		GL_RGB5_A1,        // BGR5A1
		GL_RGB5_A1,        // RGB5A1
		GL_RGB10_A2,       // RGB10A2
		GL_R11F_G11F_B10F, // RG11B10F
		GL_ZERO,           // UnknownDepth
		GL_ZERO,           // D16
		GL_ZERO,           // D24
		GL_ZERO,           // D24S8
		GL_ZERO,           // D32
		GL_ZERO,           // D16F
		GL_ZERO,           // D24F
		GL_ZERO,           // D32F
		GL_ZERO,           // D0S8
	};
	BX_STATIC_ASSERT(TextureFormat::Count == BX_COUNTOF(s_imageFormat) );

	struct Extension
	{
		enum Enum
		{
			AMD_conservative_depth,
			AMD_multi_draw_indirect,

			ANGLE_depth_texture,
			ANGLE_framebuffer_blit,
			ANGLE_framebuffer_multisample,
			ANGLE_instanced_arrays,
			ANGLE_texture_compression_dxt1,
			ANGLE_texture_compression_dxt3,
			ANGLE_texture_compression_dxt5,
			ANGLE_timer_query,
			ANGLE_translated_shader_source,

			APPLE_texture_format_BGRA8888,
			APPLE_texture_max_level,

			ARB_clip_control,
			ARB_compute_shader,
			ARB_conservative_depth,
			ARB_copy_image,
			ARB_debug_label,
			ARB_debug_output,
			ARB_depth_buffer_float,
			ARB_depth_clamp,
			ARB_draw_buffers_blend,
			ARB_draw_indirect,
			ARB_draw_instanced,
			ARB_ES3_compatibility,
			ARB_framebuffer_object,
			ARB_framebuffer_sRGB,
			ARB_get_program_binary,
			ARB_half_float_pixel,
			ARB_half_float_vertex,
			ARB_indirect_parameters,
			ARB_instanced_arrays,
			ARB_internalformat_query,
			ARB_internalformat_query2,
			ARB_invalidate_subdata,
			ARB_map_buffer_range,
			ARB_multi_draw_indirect,
			ARB_multisample,
			ARB_occlusion_query,
			ARB_occlusion_query2,
			ARB_program_interface_query,
			ARB_provoking_vertex,
			ARB_sampler_objects,
			ARB_seamless_cube_map,
			ARB_shader_bit_encoding,
			ARB_shader_image_load_store,
			ARB_shader_storage_buffer_object,
			ARB_shader_texture_lod,
			ARB_shader_viewport_layer_array,
			ARB_texture_compression_bptc,
			ARB_texture_compression_rgtc,
			ARB_texture_cube_map_array,
			ARB_texture_float,
			ARB_texture_multisample,
			ARB_texture_rg,
			ARB_texture_rgb10_a2ui,
			ARB_texture_stencil8,
			ARB_texture_storage,
			ARB_texture_swizzle,
			ARB_timer_query,
			ARB_uniform_buffer_object,
			ARB_vertex_array_object,
			ARB_vertex_type_2_10_10_10_rev,

			ATI_meminfo,

			CHROMIUM_color_buffer_float_rgb,
			CHROMIUM_color_buffer_float_rgba,
			CHROMIUM_depth_texture,
			CHROMIUM_framebuffer_multisample,
			CHROMIUM_texture_compression_dxt3,
			CHROMIUM_texture_compression_dxt5,

			EXT_bgra,
			EXT_blend_color,
			EXT_blend_minmax,
			EXT_blend_subtract,
			EXT_color_buffer_half_float,
			EXT_color_buffer_float,
			EXT_copy_image,
			EXT_compressed_ETC1_RGB8_sub_texture,
			EXT_debug_label,
			EXT_debug_marker,
			EXT_debug_tool,
			EXT_discard_framebuffer,
			EXT_disjoint_timer_query,
			EXT_draw_buffers,
			EXT_draw_instanced,
			EXT_instanced_arrays,
			EXT_frag_depth,
			EXT_framebuffer_blit,
			EXT_framebuffer_object,
			EXT_framebuffer_sRGB,
			EXT_gpu_shader4,
			EXT_multi_draw_indirect,
			EXT_occlusion_query_boolean,
			EXT_packed_float,
			EXT_read_format_bgra,
			EXT_shader_image_load_store,
			EXT_shader_texture_lod,
			EXT_shadow_samplers,
			EXT_sRGB_write_control,
			EXT_texture_array,
			EXT_texture_compression_dxt1,
			EXT_texture_compression_latc,
			EXT_texture_compression_rgtc,
			EXT_texture_compression_s3tc,
			EXT_texture_cube_map_array,
			EXT_texture_filter_anisotropic,
			EXT_texture_format_BGRA8888,
			EXT_texture_rg,
			EXT_texture_shared_exponent,
			EXT_texture_snorm,
			EXT_texture_sRGB,
			EXT_texture_storage,
			EXT_texture_swizzle,
			EXT_texture_type_2_10_10_10_REV,
			EXT_timer_query,
			EXT_unpack_subimage,
			EXT_sRGB,
			EXT_multisampled_render_to_texture,

			GOOGLE_depth_texture,

			IMG_multisampled_render_to_texture,
			IMG_read_format,
			IMG_shader_binary,
			IMG_texture_compression_pvrtc,
			IMG_texture_compression_pvrtc2,
			IMG_texture_format_BGRA8888,

			INTEL_fragment_shader_ordering,

			KHR_debug,
			KHR_no_error,

			MOZ_WEBGL_compressed_texture_s3tc,
			MOZ_WEBGL_depth_texture,

			NV_conservative_raster,
			NV_copy_image,
			NV_draw_buffers,
			NV_draw_instanced,
			NV_instanced_arrays,
			NV_occlusion_query,
			NV_texture_border_clamp,
			NVX_gpu_memory_info,

			OES_copy_image,
			OES_compressed_ETC1_RGB8_texture,
			OES_depth24,
			OES_depth32,
			OES_depth_texture,
			OES_element_index_uint,
			OES_fragment_precision_high,
			OES_fbo_render_mipmap,
			OES_get_program_binary,
			OES_required_internalformat,
			OES_packed_depth_stencil,
			OES_read_format,
			OES_rgb8_rgba8,
			OES_standard_derivatives,
			OES_texture_3D,
			OES_texture_float,
			OES_texture_float_linear,
			OES_texture_npot,
			OES_texture_half_float,
			OES_texture_half_float_linear,
			OES_texture_stencil8,
			OES_texture_storage_multisample_2d_array,
			OES_vertex_array_object,
			OES_vertex_half_float,
			OES_vertex_type_10_10_10_2,

			WEBGL_color_buffer_float,
			WEBGL_compressed_texture_etc1,
			WEBGL_compressed_texture_s3tc,
			WEBGL_compressed_texture_pvrtc,
			WEBGL_depth_texture,
			WEBGL_draw_buffers,

			WEBKIT_EXT_texture_filter_anisotropic,
			WEBKIT_WEBGL_compressed_texture_s3tc,
			WEBKIT_WEBGL_depth_texture,

			Count
		};

		const char* m_name;
		bool m_supported;
		bool m_initialize;
	};

	// Extension registry
	//
	// ANGLE:
	// https://github.com/google/angle/tree/master/extensions
	//
	// CHROMIUM:
	// https://chromium.googlesource.com/chromium/src.git/+/refs/heads/git-svn/gpu/GLES2/extensions/CHROMIUM
	//
	// EGL:
	// https://www.khronos.org/registry/egl/extensions/
	//
	// GL:
	// https://www.opengl.org/registry/
	//
	// GLES:
	// https://www.khronos.org/registry/gles/extensions/
	//
	// WEBGL:
	// https://www.khronos.org/registry/webgl/extensions/
	//
	static Extension s_extension[] =
	{
		{ "AMD_conservative_depth",                   false,                             true  },
		{ "AMD_multi_draw_indirect",                  false,                             true  },

		{ "ANGLE_depth_texture",                      false,                             true  },
		{ "ANGLE_framebuffer_blit",                   false,                             true  },
		{ "ANGLE_framebuffer_multisample",            false,                             false },
		{ "ANGLE_instanced_arrays",                   false,                             true  },
		{ "ANGLE_texture_compression_dxt1",           false,                             true  },
		{ "ANGLE_texture_compression_dxt3",           false,                             true  },
		{ "ANGLE_texture_compression_dxt5",           false,                             true  },
		{ "ANGLE_timer_query",                        false,                             true  },
		{ "ANGLE_translated_shader_source",           false,                             true  },

		{ "APPLE_texture_format_BGRA8888",            false,                             true  },
		{ "APPLE_texture_max_level",                  false,                             true  },

		{ "ARB_clip_control",                         BGFX_CONFIG_RENDERER_OPENGL >= 43, true  },
		{ "ARB_compute_shader",                       BGFX_CONFIG_RENDERER_OPENGL >= 43, true  },
		{ "ARB_conservative_depth",                   BGFX_CONFIG_RENDERER_OPENGL >= 42, true  },
		{ "ARB_copy_image",                           BGFX_CONFIG_RENDERER_OPENGL >= 42, true  },
		{ "ARB_debug_label",                          false,                             true  },
		{ "ARB_debug_output",                         BGFX_CONFIG_RENDERER_OPENGL >= 43, true  },
		{ "ARB_depth_buffer_float",                   BGFX_CONFIG_RENDERER_OPENGL >= 33, true  },
		{ "ARB_depth_clamp",                          BGFX_CONFIG_RENDERER_OPENGL >= 32, true  },
		{ "ARB_draw_buffers_blend",                   BGFX_CONFIG_RENDERER_OPENGL >= 40, true  },
		{ "ARB_draw_indirect",                        BGFX_CONFIG_RENDERER_OPENGL >= 40, true  },
		{ "ARB_draw_instanced",                       BGFX_CONFIG_RENDERER_OPENGL >= 33, true  },
		{ "ARB_ES3_compatibility",                    BGFX_CONFIG_RENDERER_OPENGL >= 43, true  },
		{ "ARB_framebuffer_object",                   BGFX_CONFIG_RENDERER_OPENGL >= 30, true  },
		{ "ARB_framebuffer_sRGB",                     BGFX_CONFIG_RENDERER_OPENGL >= 30, true  },
		{ "ARB_get_program_binary",                   BGFX_CONFIG_RENDERER_OPENGL >= 41, true  },
		{ "ARB_half_float_pixel",                     BGFX_CONFIG_RENDERER_OPENGL >= 30, true  },
		{ "ARB_half_float_vertex",                    BGFX_CONFIG_RENDERER_OPENGL >= 30, true  },
		{ "ARB_indirect_parameters",                  BGFX_CONFIG_RENDERER_OPENGL >= 46, true  },
		{ "ARB_instanced_arrays",                     BGFX_CONFIG_RENDERER_OPENGL >= 33, true  },
		{ "ARB_internalformat_query",                 BGFX_CONFIG_RENDERER_OPENGL >= 42, true  },
		{ "ARB_internalformat_query2",                BGFX_CONFIG_RENDERER_OPENGL >= 43, true  },
		{ "ARB_invalidate_subdata",                   BGFX_CONFIG_RENDERER_OPENGL >= 43, true  },
		{ "ARB_map_buffer_range",                     BGFX_CONFIG_RENDERER_OPENGL >= 30, true  },
		{ "ARB_multi_draw_indirect",                  BGFX_CONFIG_RENDERER_OPENGL >= 43, true  },
		{ "ARB_multisample",                          false,                             true  },
		{ "ARB_occlusion_query",                      BGFX_CONFIG_RENDERER_OPENGL >= 33, true  },
		{ "ARB_occlusion_query2",                     BGFX_CONFIG_RENDERER_OPENGL >= 33, true  },
		{ "ARB_program_interface_query",              BGFX_CONFIG_RENDERER_OPENGL >= 43, true  },
		{ "ARB_provoking_vertex",                     BGFX_CONFIG_RENDERER_OPENGL >= 32, true  },
		{ "ARB_sampler_objects",                      BGFX_CONFIG_RENDERER_OPENGL >= 33, true  },
		{ "ARB_seamless_cube_map",                    BGFX_CONFIG_RENDERER_OPENGL >= 32, true  },
		{ "ARB_shader_bit_encoding",                  BGFX_CONFIG_RENDERER_OPENGL >= 33, true  },
		{ "ARB_shader_image_load_store",              BGFX_CONFIG_RENDERER_OPENGL >= 42, true  },
		{ "ARB_shader_storage_buffer_object",         BGFX_CONFIG_RENDERER_OPENGL >= 43, true  },
		{ "ARB_shader_texture_lod",                   BGFX_CONFIG_RENDERER_OPENGL >= 30, true  },
		{ "ARB_shader_viewport_layer_array",          false,                             true  },
		{ "ARB_texture_compression_bptc",             BGFX_CONFIG_RENDERER_OPENGL >= 44, true  },
		{ "ARB_texture_compression_rgtc",             BGFX_CONFIG_RENDERER_OPENGL >= 30, true  },
		{ "ARB_texture_cube_map_array",               BGFX_CONFIG_RENDERER_OPENGL >= 40, true  },
		{ "ARB_texture_float",                        BGFX_CONFIG_RENDERER_OPENGL >= 30, true  },
		{ "ARB_texture_multisample",                  BGFX_CONFIG_RENDERER_OPENGL >= 32, true  },
		{ "ARB_texture_rg",                           BGFX_CONFIG_RENDERER_OPENGL >= 30, true  },
		{ "ARB_texture_rgb10_a2ui",                   BGFX_CONFIG_RENDERER_OPENGL >= 33, true  },
		{ "ARB_texture_stencil8",                     false,                             true  },
		{ "ARB_texture_storage",                      BGFX_CONFIG_RENDERER_OPENGL >= 42, true  },
		{ "ARB_texture_swizzle",                      BGFX_CONFIG_RENDERER_OPENGL >= 33, true  },
		{ "ARB_timer_query",                          BGFX_CONFIG_RENDERER_OPENGL >= 33, true  },
		{ "ARB_uniform_buffer_object",                BGFX_CONFIG_RENDERER_OPENGL >= 31, true  },
		{ "ARB_vertex_array_object",                  BGFX_CONFIG_RENDERER_OPENGL >= 30, true  },
		{ "ARB_vertex_type_2_10_10_10_rev",           false,                             true  },

		{ "ATI_meminfo",                              false,                             true  },

		{ "CHROMIUM_color_buffer_float_rgb",          false,                             true  },
		{ "CHROMIUM_color_buffer_float_rgba",         false,                             true  },
		{ "CHROMIUM_depth_texture",                   false,                             true  },
		{ "CHROMIUM_framebuffer_multisample",         false,                             true  },
		{ "CHROMIUM_texture_compression_dxt3",        false,                             true  },
		{ "CHROMIUM_texture_compression_dxt5",        false,                             true  },

		{ "EXT_bgra",                                 false,                             true  },
		{ "EXT_blend_color",                          BGFX_CONFIG_RENDERER_OPENGL >= 31, true  },
		{ "EXT_blend_minmax",                         BGFX_CONFIG_RENDERER_OPENGL >= 14, true  },
		{ "EXT_blend_subtract",                       BGFX_CONFIG_RENDERER_OPENGL >= 14, true  },
		{ "EXT_color_buffer_half_float",              false,                             true  }, // GLES2 extension.
		{ "EXT_color_buffer_float",                   false,                             true  }, // GLES2 extension.
		{ "EXT_copy_image",                           false,                             true  }, // GLES2 extension.
		{ "EXT_compressed_ETC1_RGB8_sub_texture",     false,                             true  }, // GLES2 extension.
		{ "EXT_debug_label",                          false,                             true  },
		{ "EXT_debug_marker",                         false,                             true  },
		{ "EXT_debug_tool",                           false,                             true  }, // RenderDoc extension.
		{ "EXT_discard_framebuffer",                  false,                             true  }, // GLES2 extension.
		{ "EXT_disjoint_timer_query",                 false,                             true  }, // GLES2 extension.
		{ "EXT_draw_buffers",                         false,                             true  }, // GLES2 extension.
		{ "EXT_draw_instanced",                       false,                             true  }, // GLES2 extension.
		{ "EXT_instanced_arrays",                     false,                             true  }, // GLES2 extension.
		{ "EXT_frag_depth",                           false,                             true  }, // GLES2 extension.
		{ "EXT_framebuffer_blit",                     BGFX_CONFIG_RENDERER_OPENGL >= 30, true  },
		{ "EXT_framebuffer_object",                   BGFX_CONFIG_RENDERER_OPENGL >= 30, true  },
		{ "EXT_framebuffer_sRGB",                     BGFX_CONFIG_RENDERER_OPENGL >= 30, true  },
		{ "EXT_gpu_shader4",                          BGFX_CONFIG_RENDERER_OPENGL >= 31, true  },
		{ "EXT_multi_draw_indirect",                  false,                             true  }, // GLES3.1 extension.
		{ "EXT_occlusion_query_boolean",              false,                             true  }, // GLES2 extension.
		{ "EXT_packed_float",                         BGFX_CONFIG_RENDERER_OPENGL >= 33, true  },
		{ "EXT_read_format_bgra",                     false,                             true  },
		{ "EXT_shader_image_load_store",              false,                             true  },
		{ "EXT_shader_texture_lod",                   false,                             true  }, // GLES2 extension.
		{ "EXT_shadow_samplers",                      false,                             true  },
		{ "EXT_sRGB_write_control",                   false,                             true  }, // GLES2 extension.
		{ "EXT_texture_array",                        BGFX_CONFIG_RENDERER_OPENGL >= 30, true  },
		{ "EXT_texture_compression_dxt1",             false,                             true  },
		{ "EXT_texture_compression_latc",             false,                             true  },
		{ "EXT_texture_compression_rgtc",             BGFX_CONFIG_RENDERER_OPENGL >= 30, true  },
		{ "EXT_texture_compression_s3tc",             false,                             true  },
		{ "EXT_texture_cube_map_array",               false,                             true  }, // GLES3.1 extension.
		{ "EXT_texture_filter_anisotropic",           false,                             true  },
		{ "EXT_texture_format_BGRA8888",              false,                             true  },
		{ "EXT_texture_rg",                           false,                             true  }, // GLES2 extension.
		{ "EXT_texture_shared_exponent",              false,                             true  },
		{ "EXT_texture_snorm",                        BGFX_CONFIG_RENDERER_OPENGL >= 30, true  },
		{ "EXT_texture_sRGB",                         false,                             true  },
		{ "EXT_texture_storage",                      false,                             true  },
		{ "EXT_texture_swizzle",                      false,                             true  },
		{ "EXT_texture_type_2_10_10_10_REV",          false,                             true  },
		{ "EXT_timer_query",                          BGFX_CONFIG_RENDERER_OPENGL >= 33, true  },
		{ "EXT_unpack_subimage",                      false,                             true  },
		{ "EXT_sRGB",                                 false,                             true  }, // GLES2 extension.
		{ "EXT_multisampled_render_to_texture",       false,                             true  }, // GLES2 extension.

		{ "GOOGLE_depth_texture",                     false,                             true  },

		{ "IMG_multisampled_render_to_texture",       false,                             true  },
		{ "IMG_read_format",                          false,                             true  },
		{ "IMG_shader_binary",                        false,                             true  },
		{ "IMG_texture_compression_pvrtc",            false,                             true  },
		{ "IMG_texture_compression_pvrtc2",           false,                             true  },
		{ "IMG_texture_format_BGRA8888",              false,                             true  },

		{ "INTEL_fragment_shader_ordering",           false,                             true  },

		{ "KHR_debug",                                BGFX_CONFIG_RENDERER_OPENGL >= 43, true  },
		{ "KHR_no_error",                             false,                             true  },

		{ "MOZ_WEBGL_compressed_texture_s3tc",        false,                             true  },
		{ "MOZ_WEBGL_depth_texture",                  false,                             true  },

		{ "NV_conservative_raster",                   false,                             true  },
		{ "NV_copy_image",                            false,                             true  },
		{ "NV_draw_buffers",                          false,                             true  }, // GLES2 extension.
		{ "NV_draw_instanced",                        false,                             true  }, // GLES2 extension.
		{ "NV_instanced_arrays",                      false,                             true  }, // GLES2 extension.
		{ "NV_occlusion_query",                       false,                             true  },
		{ "NV_texture_border_clamp",                  false,                             true  }, // GLES2 extension.
		{ "NVX_gpu_memory_info",                      false,                             true  },

		{ "OES_copy_image",                           false,                             true  },
		{ "OES_compressed_ETC1_RGB8_texture",         false,                             true  },
		{ "OES_depth24",                              false,                             true  },
		{ "OES_depth32",                              false,                             true  },
		{ "OES_depth_texture",                        false,                             true  },
		{ "OES_element_index_uint",                   false,                             true  },
		{ "OES_fragment_precision_high",              false,                             true  },
		{ "OES_fbo_render_mipmap",                    false,                             true  },
		{ "OES_get_program_binary",                   false,                             true  },
		{ "OES_required_internalformat",              false,                             true  },
		{ "OES_packed_depth_stencil",                 false,                             true  },
		{ "OES_read_format",                          false,                             true  },
		{ "OES_rgb8_rgba8",                           false,                             true  },
		{ "OES_standard_derivatives",                 false,                             true  },
		{ "OES_texture_3D",                           false,                             true  },
		{ "OES_texture_float",                        false,                             true  },
		{ "OES_texture_float_linear",                 false,                             true  },
		{ "OES_texture_npot",                         false,                             true  },
		{ "OES_texture_half_float",                   false,                             true  },
		{ "OES_texture_half_float_linear",            false,                             true  },
		{ "OES_texture_stencil8",                     false,                             true  },
		{ "OES_texture_storage_multisample_2d_array", false,                             true  },
		{ "OES_vertex_array_object",                  false,                             true  },
		{ "OES_vertex_half_float",                    false,                             true  },
		{ "OES_vertex_type_10_10_10_2",               false,                             true  },

		{ "WEBGL_color_buffer_float",                 false,                             true  },
		{ "WEBGL_compressed_texture_etc1",            false,                             true  },
		{ "WEBGL_compressed_texture_s3tc",            false,                             true  },
		{ "WEBGL_compressed_texture_pvrtc",           false,                             true  },
		{ "WEBGL_depth_texture",                      false,                             true  },
		{ "WEBGL_draw_buffers",                       false,                             true  },

		{ "WEBKIT_EXT_texture_filter_anisotropic",    false,                             true  },
		{ "WEBKIT_WEBGL_compressed_texture_s3tc",     false,                             true  },
		{ "WEBKIT_WEBGL_depth_texture",               false,                             true  },
	};
	BX_STATIC_ASSERT(Extension::Count == BX_COUNTOF(s_extension) );

	static const char* s_ARB_shader_texture_lod[] =
	{
		"texture2DLod",
		"texture2DArrayLod", // BK - interacts with ARB_texture_array.
		"texture2DProjLod",
		"texture2DGrad",
		"texture2DProjGrad",
		"texture3DLod",
		"texture3DProjLod",
		"texture3DGrad",
		"texture3DProjGrad",
		"textureCubeLod",
		"textureCubeGrad",
		"shadow2DLod",
		"shadow2DProjLod",
		NULL
		// "texture1DLod",
		// "texture1DProjLod",
		// "shadow1DLod",
		// "shadow1DProjLod",
	};

	static const char* s_EXT_shader_texture_lod[] =
	{
		"texture2DLod",
		"texture2DProjLod",
		"textureCubeLod",
		"texture2DGrad",
		"texture2DProjGrad",
		"textureCubeGrad",
		NULL
	};

	static const char* s_ARB_shader_viewport_layer_array[] =
	{
		"gl_ViewportIndex",
		"gl_Layer",
		NULL
	};

	static const char* s_EXT_shadow_samplers[] =
	{
		"shadow2D",
		"shadow2DProj",
		NULL
	};

	static const char* s_OES_standard_derivatives[] =
	{
		"dFdx",
		"dFdy",
		"fwidth",
		NULL
	};

	static const char* s_uisamplers[] =
	{
		"isampler2D",
		"usampler2D",
		"isampler3D",
		"usampler3D",
		"isamplerCube",
		"usamplerCube",
		NULL
	};

	static const char* s_uint[] =
	{
		"uint",
		"uvec2",
		"uvec3",
		"uvec4",
		NULL
	};

	static const char* s_texelFetch[] =
	{
		"texture",
		"textureLod",
		"textureGrad",
		"textureProj",
		"textureProjLod",
		"texelFetch",
		"texelFetchOffset",
		NULL
	};

	static const char* s_texture3D[] =
	{
		"sampler3D",
		"sampler3DArray",
		NULL
	};

	static const char* s_textureArray[] =
	{
		"sampler2DArray",
		"sampler2DMSArray",
		"samplerCubeArray",
		"sampler2DArrayShadow",
		NULL
	};

	static const char* s_ARB_texture_multisample[] =
	{
		"sampler2DMS",
		"isampler2DMS",
		"usampler2DMS",
		NULL
	};

	static const char* s_EXT_gpu_shader4[] =
	{
		"gl_VertexID",
		"gl_InstanceID",
		"uint",
		NULL
	};

	static const char* s_ARB_gpu_shader5[] =
	{
		"bitfieldReverse",
		"floatBitsToInt",
		"floatBitsToUint",
		"intBitsToFloat",
		"uintBitsToFloat",
		NULL
	};

	static const char* s_ARB_shading_language_packing[] =
	{
		"packHalf2x16",
		"unpackHalf2x16",
		NULL
	};

	static const char* s_intepolationQualifier[] =
	{
		"flat",
		"smooth",
		"noperspective",
		"centroid",
		NULL
	};

	static void GL_APIENTRY stubVertexAttribDivisor(GLuint /*_index*/, GLuint /*_divisor*/)
	{
	}

	static void GL_APIENTRY stubDrawArraysInstanced(GLenum _mode, GLint _first, GLsizei _count, GLsizei /*_primcount*/)
	{
		GL_CHECK(glDrawArrays(_mode, _first, _count) );
	}

	static void GL_APIENTRY stubDrawElementsInstanced(GLenum _mode, GLsizei _count, GLenum _type, const GLvoid* _indices, GLsizei /*_primcount*/)
	{
		GL_CHECK(glDrawElements(_mode, _count, _type, _indices) );
	}

	static void GL_APIENTRY stubInsertEventMarker(GLsizei /*_length*/, const char* /*_marker*/)
	{
	}

	static void GL_APIENTRY stubPushDebugGroup(GLenum /*_source*/, GLuint /*_id*/, GLsizei /*_length*/, const char* /*_message*/)
	{
	}

	static void GL_APIENTRY stubPopDebugGroup()
	{
	}

	static void GL_APIENTRY stubObjectLabel(GLenum /*_identifier*/, GLuint /*_name*/, GLsizei /*_length*/, const char* /*_label*/)
	{
	}

	static void GL_APIENTRY stubInvalidateFramebuffer(GLenum /*_target*/, GLsizei /*_numAttachments*/, const GLenum* /*_attachments*/)
	{
	}

	static void GL_APIENTRY stubFramebufferTexture(GLenum _target, GLenum _attachment, GLuint _texture, GLint _level)
	{
		GL_CHECK(glFramebufferTextureLayer(_target
			, _attachment
			, _texture
			, _level
			, 0
			) );
	}

	static void GL_APIENTRY stubMultiDrawArraysIndirect(GLenum _mode, const void* _indirect, GLsizei _drawCount, GLsizei _stride)
	{
		const uint8_t* args = (const uint8_t*)_indirect;
		for (GLsizei ii = 0; ii < _drawCount; ++ii)
		{
			GL_CHECK(glDrawArraysIndirect(_mode, (void*)args) );
			args += _stride;
		}
	}

	static void GL_APIENTRY stubMultiDrawElementsIndirect(GLenum _mode, GLenum _type, const void* _indirect, GLsizei _drawCount, GLsizei _stride)
	{
		const uint8_t* args = (const uint8_t*)_indirect;
		for (GLsizei ii = 0; ii < _drawCount; ++ii)
		{
			GL_CHECK(glDrawElementsIndirect(_mode, _type, (void*)args) );
			args += _stride;
		}
	}

	static void GL_APIENTRY stubPolygonMode(GLenum /*_face*/, GLenum /*_mode*/)
	{
	}

	typedef void (*PostSwapBuffersFn)(uint32_t _width, uint32_t _height);

	void flushGlError()
	{
		for (GLenum err = glGetError(); err != 0; err = glGetError() );
	}

	GLenum getGlError()
	{
		GLenum err = glGetError();
		flushGlError();
		return err;
	}

	static const char* getGLString(GLenum _name)
	{
		const char* str = (const char*)glGetString(_name);
		getGlError(); // ignore error if glGetString returns NULL.
		if (NULL != str)
		{
			return str;
		}

		return "<unknown>";
	}

	static uint32_t getGLStringHash(GLenum _name)
	{
		const char* str = (const char*)glGetString(_name);
		getGlError(); // ignore error if glGetString returns NULL.
		if (NULL != str)
		{
			return bx::hash<bx::HashMurmur2A>(str, (uint32_t)bx::strLen(str) );
		}

		return 0;
	}

	void dumpExtensions(const char* _extensions)
	{
		if (NULL != _extensions)
		{
			char name[1024];
			const char* pos = _extensions;
			const char* end = _extensions + bx::strLen(_extensions);
			while (pos < end)
			{
				uint32_t len;
				bx::StringView space = bx::strFind(pos, ' ');
				if (!space.isEmpty() )
				{
					len = bx::uint32_min(sizeof(name), (uint32_t)(space.getPtr() - pos) );
				}
				else
				{
					len = bx::uint32_min(sizeof(name), (uint32_t)bx::strLen(pos) );
				}

				bx::strCopy(name, BX_COUNTOF(name), pos, len);
				name[len] = '\0';

				BX_TRACE("\t%s", name);

				pos += len+1;
			}
		}
	}

	const char* toString(GLenum _enum)
	{
		switch (_enum)
		{
		case GL_DEBUG_SOURCE_API:               return "API";
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:     return "WinSys";
		case GL_DEBUG_SOURCE_SHADER_COMPILER:   return "Shader";
		case GL_DEBUG_SOURCE_THIRD_PARTY:       return "3rdparty";
		case GL_DEBUG_SOURCE_APPLICATION:       return "Application";
		case GL_DEBUG_SOURCE_OTHER:             return "Other";
		case GL_DEBUG_TYPE_ERROR:               return "Error";
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "Deprecated behavior";
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  return "Undefined behavior";
		case GL_DEBUG_TYPE_PORTABILITY:         return "Portability";
		case GL_DEBUG_TYPE_PERFORMANCE:         return "Performance";
		case GL_DEBUG_TYPE_OTHER:               return "Other";
		case GL_DEBUG_SEVERITY_HIGH:            return "High";
		case GL_DEBUG_SEVERITY_MEDIUM:          return "Medium";
		case GL_DEBUG_SEVERITY_LOW:             return "Low";
		case GL_DEBUG_SEVERITY_NOTIFICATION:    return "SPAM";
		default:
			break;
		}

		return "<unknown>";
	}

	void GL_APIENTRY debugProcCb(GLenum _source, GLenum _type, GLuint _id, GLenum _severity, GLsizei /*_length*/, const GLchar* _message, const void* /*_userParam*/)
	{
		if (GL_DEBUG_SEVERITY_NOTIFICATION != _severity)
		{
			BX_TRACE("src %s, type %s, id %d, severity %s, '%s'"
					, toString(_source)
					, toString(_type)
					, _id
					, toString(_severity)
					, _message
					);
			BX_UNUSED(_source, _type, _id, _severity, _message);
		}
	}

	GLint glGet(GLenum _pname)
	{
		GLint result = 0;
		glGetIntegerv(_pname, &result);
		GLenum err = getGlError();
		BX_WARN(0 == err, "glGetIntegerv(0x%04x, ...) failed with GL error: 0x%04x.", _pname, err);
		return 0 == err ? result : 0;
	}

	static uint64_t s_currentlyEnabledVertexAttribArrays = 0;
	static uint64_t s_vertexAttribArraysPendingDisable   = 0;
	static uint64_t s_vertexAttribArraysPendingEnable    = 0;

	void initLazyEnabledVertexAttributes()
	{
		s_currentlyEnabledVertexAttribArrays = 0;
		s_vertexAttribArraysPendingDisable   = 0;
		s_vertexAttribArraysPendingEnable    = 0;
	}

	void lazyEnableVertexAttribArray(GLuint index)
	{
		if (BX_ENABLED(BX_PLATFORM_EMSCRIPTEN) )
		{
			if (index >= 64)
			{
				// On WebGL platform calling out to WebGL API is detrimental to performance, so optimize
				// out redundant API calls to glEnable/DisableVertexAttribArray.
				GL_CHECK(glEnableVertexAttribArray(index) );
				return;
			}

			const uint64_t mask = UINT64_C(1) << index;
			s_vertexAttribArraysPendingEnable  |=  mask & (~s_currentlyEnabledVertexAttribArrays);
			s_vertexAttribArraysPendingDisable &= ~mask;
		}
		else
		{
			GL_CHECK(glEnableVertexAttribArray(index) );
		}
	}

	void lazyDisableVertexAttribArray(GLuint index)
	{
		if (BX_ENABLED(BX_PLATFORM_EMSCRIPTEN) )
		{
			if (index >= 64)
			{
				// On WebGL platform calling out to WebGL API is detrimental to performance, so optimize
				// out redundant API calls to glEnable/DisableVertexAttribArray.
				GL_CHECK(glDisableVertexAttribArray(index) );
				return;
			}

			const uint64_t mask = UINT64_C(1) << index;
			s_vertexAttribArraysPendingDisable |=  mask & s_currentlyEnabledVertexAttribArrays;
			s_vertexAttribArraysPendingEnable  &= ~mask;
		}
		else
		{
			GL_CHECK(glDisableVertexAttribArray(index) );
		}
	}

	void applyLazyEnabledVertexAttributes()
	{
		if (BX_ENABLED(BX_PLATFORM_EMSCRIPTEN) )
		{
			while (s_vertexAttribArraysPendingDisable)
			{
				uint32_t index = bx::countTrailingZeros(s_vertexAttribArraysPendingDisable);
				uint64_t mask  = ~(UINT64_C(1) << index);
				s_vertexAttribArraysPendingDisable   &= mask;
				s_currentlyEnabledVertexAttribArrays &= mask;
				GL_CHECK(glDisableVertexAttribArray(index) );
			}

			while (s_vertexAttribArraysPendingEnable)
			{
				uint32_t index = bx::countTrailingZeros(s_vertexAttribArraysPendingEnable);
				uint64_t mask  = UINT64_C(1) << index;
				s_vertexAttribArraysPendingEnable    &= ~mask;
				s_currentlyEnabledVertexAttribArrays |= mask;
				GL_CHECK(glEnableVertexAttribArray(index) );
			}
		}
	}

	void setTextureFormat(TextureFormat::Enum _format, GLenum _internalFmt, GLenum _fmt, GLenum _type = GL_ZERO)
	{
		TextureFormatInfo& tfi = s_textureFormat[_format];
		tfi.m_internalFmt = _internalFmt;
		tfi.m_fmt         = _fmt;
		tfi.m_fmtSrgb     = _fmt;
		tfi.m_type        = _type;
	}

	void setTextureFormatSrgb(TextureFormat::Enum _format, GLenum _internalFmtSrgb, GLenum _fmtSrgb)
	{
		TextureFormatInfo& tfi = s_textureFormat[_format];
		tfi.m_internalFmtSrgb = _internalFmtSrgb;
		tfi.m_fmtSrgb = _fmtSrgb;
	}

	static void texSubImage(
		  GLenum _target
		, GLint _level
		, GLint _xoffset
		, GLint _yoffset
		, GLint _zoffset
		, GLsizei _width
		, GLsizei _height
		, GLsizei _depth
		, GLenum _format
		, GLenum _type
		, const GLvoid* _data
	)
	{
		if (NULL == _data)
		{
			return;
		}

		if (_target == GL_TEXTURE_3D
		||  _target == GL_TEXTURE_2D_ARRAY
		||  _target == GL_TEXTURE_CUBE_MAP_ARRAY)
		{
			glTexSubImage3D(
				  _target
				, _level
				, _xoffset
				, _yoffset
				, _zoffset
				, _width
				, _height
				, _depth
				, _format
				, _type
				, _data
				);
		}
		else if (_target == GL_TEXTURE_2D_MULTISAMPLE_ARRAY)
		{
		}
		else
		{
			BX_UNUSED(_zoffset, _depth);
			glTexSubImage2D(
				  _target
				, _level
				, _xoffset
				, _yoffset
				, _width
				, _height
				, _format
				, _type
				, _data
				);
		}
	}

	static void texImage(
		  GLenum _target
		, uint32_t _msaaQuality
		, GLint _level
		, GLint _internalFormat
		, GLsizei _width
		, GLsizei _height
		, GLsizei _depth
		, GLint _border
		, GLenum _format
		, GLenum _type
		, const GLvoid* _data
	)
	{
		if (_target == GL_TEXTURE_3D)
		{
			glTexImage3D(
				  _target
				, _level
				, _internalFormat
				, _width
				, _height
				, _depth
				, _border
				, _format
				, _type
				, _data
				);
		}
		else if (_target == GL_TEXTURE_2D_ARRAY
			 ||  _target == GL_TEXTURE_CUBE_MAP_ARRAY)
		{
			texSubImage(
				  _target
				, _level
				, 0
				, 0
				, _depth
				, _width
				, _height
				, 1
				, _format
				, _type
				, _data
				);
		}
		else if (_target == GL_TEXTURE_2D_MULTISAMPLE_ARRAY)
		{
		}
		else if (_target == GL_TEXTURE_2D_MULTISAMPLE)
		{
			glTexImage2DMultisample(
				  _target
				, _msaaQuality
				, _internalFormat
				, _width
				, _height
				, false
				);
		}
		else
		{
			glTexImage2D(
				  _target
				, _level
				, _internalFormat
				, _width
				, _height
				, _border
				, _format
				, _type
				, _data
				);
		}

		BX_UNUSED(_msaaQuality, _depth, _border, _data);
	}

	static void compressedTexSubImage(
		  GLenum _target
		, GLint _level
		, GLint _xoffset
		, GLint _yoffset
		, GLint _zoffset
		, GLsizei _width
		, GLsizei _height
		, GLsizei _depth
		, GLenum _format
		, GLsizei _imageSize
		, const GLvoid* _data
	)
	{
		if (_target == GL_TEXTURE_3D
		||  _target == GL_TEXTURE_2D_ARRAY)
		{
			glCompressedTexSubImage3D(
				  _target
				, _level
				, _xoffset
				, _yoffset
				, _zoffset
				, _width
				, _height
				, _depth
				, _format
				, _imageSize
				, _data
				);
		}
		else
		{
			BX_UNUSED(_zoffset, _depth);
			glCompressedTexSubImage2D(
				  _target
				, _level
				, _xoffset
				, _yoffset
				, _width
				, _height
				, _format
				, _imageSize
				, _data
				);
		}
	}

	static void compressedTexImage(
		  GLenum _target
		, GLint _level
		, GLenum _internalformat
		, GLsizei _width
		, GLsizei _height
		, GLsizei _depth
		, GLint _border
		, GLsizei _imageSize
		, const GLvoid* _data
	)
	{
		if (_target == GL_TEXTURE_3D)
		{
			glCompressedTexImage3D(
				  _target
				, _level
				, _internalformat
				, _width
				, _height
				, _depth
				, _border
				, _imageSize
				, _data
				);
		}
		else if (_target == GL_TEXTURE_2D_ARRAY
			 ||  _target == GL_TEXTURE_CUBE_MAP_ARRAY)
		{
			compressedTexSubImage(
				  _target
				, _level
				, 0
				, 0
				, _depth
				, _width
				, _height
				, 1
				, _internalformat
				, _imageSize
				, _data
				);
		}
		else if (_target == GL_TEXTURE_2D_MULTISAMPLE_ARRAY)
		{
		}
		else
		{
			BX_UNUSED(_depth);
			glCompressedTexImage2D(
				  _target
				, _level
				, _internalformat
				, _width
				, _height
				, _border
				, _imageSize
				, _data
				);
		}
	}

	GLenum initTestTexture(TextureFormat::Enum _format, bool _srgb, bool _mipmaps, bool _array, GLsizei _dim)
	{
		const TextureFormatInfo& tfi = s_textureFormat[_format];
		GLenum internalFmt = _srgb
			? tfi.m_internalFmtSrgb
			: tfi.m_internalFmt
			;
		GLenum fmt = _srgb
			? tfi.m_fmtSrgb
			: tfi.m_fmt
			;

		GLsizei bpp  = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(_format) );
		GLsizei size = (_dim*_dim*bpp)/8;
		void* data = NULL;

		if (bimg::isDepth(bimg::TextureFormat::Enum(_format) ) )
		{
			_srgb    = false;
			_mipmaps = false;
			_array   = false;
		}
		else
		{
			data = bx::alignPtr(alloca(size+16), 0, 16);
		}

		flushGlError();
		GLenum err = 0;

		const GLenum target = _array
			? GL_TEXTURE_2D_ARRAY
			: GL_TEXTURE_2D
			;

		if (bimg::isCompressed(bimg::TextureFormat::Enum(_format) ) )
		{
			for (uint32_t ii = 0, dim = _dim; ii < (_mipmaps ? 5u : 1u) && 0 == err; ++ii, dim >>= 1)
			{
				dim = bx::uint32_max(1, dim);
				uint32_t block = bx::uint32_max(4, dim);
				size = (block*block*bpp)/8;
				compressedTexImage(target, ii, internalFmt, dim, dim, 0, 0, size, data);
				err |= getGlError();
			}
		}
		else
		{
			for (uint32_t ii = 0, dim = _dim; ii < (_mipmaps ? 5u : 1u) && 0 == err; ++ii, dim >>= 1)
			{
				dim = bx::uint32_max(1, dim);
				size = (dim*dim*bpp)/8;
				texImage(target, 0, ii, internalFmt, dim, dim, 0, 0, fmt, tfi.m_type, data);
				err |= getGlError();
			}
		}

		return err;
	}

#if BX_PLATFORM_EMSCRIPTEN
	static bool isTextureFormatValidPerSpec(
		  TextureFormat::Enum _format
		, bool _srgb
		, bool _mipAutogen
		)
	{
		// Avoid creating test textures for WebGL, that causes error noise in the browser
		// console; instead examine the supported texture formats from the spec.
		EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx = emscripten_webgl_get_current_context();

		EmscriptenWebGLContextAttributes attrs;
		EMSCRIPTEN_CHECK(emscripten_webgl_get_context_attributes(ctx, &attrs) );

		const int glesVersion = attrs.majorVersion + 1;

		switch(_format)
		{
			case TextureFormat::A8:
			case TextureFormat::R8: // Luminance
			case TextureFormat::B5G6R5:
			case TextureFormat::R5G6B5:
			case TextureFormat::BGRA4:
			case TextureFormat::RGBA4:
			case TextureFormat::BGR5A1:
			case TextureFormat::RGB5A1:
				// GLES2 formats without sRGB.
				return !_srgb;

			case TextureFormat::D16:
				// GLES2 formats without sRGB, depth textures do not support mipmaps.
				return !_srgb
					&& !_mipAutogen
					;

			case TextureFormat::R16F:
			case TextureFormat::R32F:
			case TextureFormat::RG8:
			case TextureFormat::RG16F:
			case TextureFormat::RG32F:
			case TextureFormat::RGB10A2:
			case TextureFormat::RG11B10F:
				// GLES3 formats without sRGB
				return !_srgb
					&& glesVersion >= 3
					;

			case TextureFormat::R8I:
			case TextureFormat::R8U:
			case TextureFormat::R16I:
			case TextureFormat::R16U:
			case TextureFormat::R32I:
			case TextureFormat::R32U:
			case TextureFormat::RG8I:
			case TextureFormat::RG8U:
			case TextureFormat::RG16I:
			case TextureFormat::RG16U:
			case TextureFormat::RG32I:
			case TextureFormat::RG32U:
			case TextureFormat::RGB8I:
			case TextureFormat::RGB8U:
			case TextureFormat::RGBA8I:
			case TextureFormat::RGBA8U:
			case TextureFormat::RGBA16I:
			case TextureFormat::RGBA16U:
			case TextureFormat::RGBA32I:
			case TextureFormat::RGBA32U:
			case TextureFormat::D32F:
			case TextureFormat::R8S:
			case TextureFormat::RG8S:
			case TextureFormat::RGB8S:
			case TextureFormat::RGBA8S:
			case TextureFormat::RGB9E5F:
				// GLES3 formats without sRGB that are not texture filterable or color renderable.
				return !_srgb && glesVersion >= 3
					&& !_mipAutogen
					;

			case TextureFormat::D24:
			case TextureFormat::D24S8:
			case TextureFormat::D32:
				// GLES3 formats without sRGB, depth textures do not support mipmaps.
				return !_srgb && !_mipAutogen
					&& (glesVersion >= 3 || emscripten_webgl_enable_extension(ctx, "WEBGL_depth_texture") )
					;

			case TextureFormat::D16F:
			case TextureFormat::D24F:
				// GLES3 depth formats without sRGB, depth textures do not support mipmaps.
				return !_srgb
					&& !_mipAutogen
					&& glesVersion >= 3
					;

			case TextureFormat::RGBA16F:
			case TextureFormat::RGBA32F:
				// GLES3 formats without sRGB
				return !_srgb
					&& (glesVersion >= 3 || emscripten_webgl_enable_extension(ctx, "OES_texture_half_float") )
					;

			case TextureFormat::RGB8:
			case TextureFormat::RGBA8:
				// sRGB formats
				return !_srgb
					|| glesVersion >= 3
					|| emscripten_webgl_enable_extension(ctx, "EXT_sRGB")
					;

			case TextureFormat::BC1:
			case TextureFormat::BC2:
			case TextureFormat::BC3:
				return            emscripten_webgl_enable_extension(ctx, "WEBGL_compressed_texture_s3tc")
					&& (!_srgb || emscripten_webgl_enable_extension(ctx, "WEBGL_compressed_texture_s3tc_srgb") )
					;

			case TextureFormat::PTC12:
			case TextureFormat::PTC14:
			case TextureFormat::PTC12A:
			case TextureFormat::PTC14A:
				return !_srgb
					&& emscripten_webgl_enable_extension(ctx, "WEBGL_compressed_texture_pvrtc")
					;

			case TextureFormat::ETC1:
				return !_srgb
					&& emscripten_webgl_enable_extension(ctx, "WEBGL_compressed_texture_etc1")
					;

			case TextureFormat::ETC2:
			case TextureFormat::ETC2A:
			case TextureFormat::ETC2A1:
				return emscripten_webgl_enable_extension(ctx, "WEBGL_compressed_texture_etc");

			case TextureFormat::ASTC4x4:
			case TextureFormat::ASTC5x5:
			case TextureFormat::ASTC6x6:
			case TextureFormat::ASTC8x5:
			case TextureFormat::ASTC8x6:
			case TextureFormat::ASTC10x5:
				return emscripten_webgl_enable_extension(ctx, "WEBGL_compressed_texture_astc");

			default:
				break;
		}

		return false;
	}
#endif // BX_PLATFORM_EMSCRIPTEN

	static bool isTextureFormatValid(
		  TextureFormat::Enum _format
		, bool _srgb = false
		, bool _mipAutogen = false
		, bool _array = false
		, GLsizei _dim = 16
		)
	{
#if BX_PLATFORM_EMSCRIPTEN
		// On web platform read the validity of textures based on the available GL context and extensions
		// to avoid developer unfriendly console error noise that would come from probing.
		BX_UNUSED(_array, _dim);
		return isTextureFormatValidPerSpec(_format, _srgb, _mipAutogen);
#else
		// On other platforms probe the supported textures.
		const TextureFormatInfo& tfi = s_textureFormat[_format];
		GLenum internalFmt = _srgb
			? tfi.m_internalFmtSrgb
			: tfi.m_internalFmt
			;
		if (GL_ZERO == internalFmt)
		{
			return false;
		}

		const GLenum target = _array
			? GL_TEXTURE_2D_ARRAY
			: GL_TEXTURE_2D
			;

		GLuint id;
		GL_CHECK(glGenTextures(1, &id) );
		GL_CHECK(glBindTexture(target, id) );

		GLenum err = 0;
		if (_array)
		{
			glTexStorage3D(target
				, 1 + GLsizei(bx::ceilLog2( (int32_t)_dim) )
				, internalFmt
				, _dim
				, _dim
				, _dim
				);
			err = getGlError();
		}

		if (0 == err)
		{
			err = initTestTexture(_format, _srgb, _mipAutogen, _array, _dim);
			BX_WARN(0 == err, "TextureFormat::%s %s%s%sis not supported (%x: %s)."
				, getName(_format)
				, _srgb       ? "+sRGB "       : ""
				, _mipAutogen ? "+mipAutoGen " : ""
				, _array      ? "+array "      : ""
				, err
				, glEnumName(err)
				);

			if (0 == err
			&&  _mipAutogen)
			{
				glGenerateMipmap(target);
				err = getGlError();
			}
		}

		GL_CHECK(glDeleteTextures(1, &id) );

		return 0 == err;
#endif
	}

	static bool isImageFormatValid(TextureFormat::Enum _format, GLsizei _dim = 16)
	{
		if (GL_ZERO == s_imageFormat[_format])
		{
			return false;
		}

		GLuint id;
		GL_CHECK(glGenTextures(1, &id) );
		GL_CHECK(glBindTexture(GL_TEXTURE_2D, id) );

		flushGlError();
		GLenum err = 0;

		glTexStorage2D(GL_TEXTURE_2D, 1, s_imageFormat[_format], _dim, _dim);
		err |= getGlError();
		if (0 == err)
		{
			glBindImageTexture(0
				, id
				, 0
				, GL_FALSE
				, 0
				, GL_READ_WRITE
				, s_imageFormat[_format]
				);
			err |= getGlError();
		}

		GL_CHECK(glDeleteTextures(1, &id) );

		return 0 == err;
	}

#if BX_PLATFORM_EMSCRIPTEN
	static bool isFramebufferFormatValidPerSpec(
		  TextureFormat::Enum _format
		, bool _srgb
		, bool _writeOnly
		)
	{
		// Avoid creating test textures for WebGL, that causes error noise in the browser console; instead examine the supported texture formats from the spec.
		EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx = emscripten_webgl_get_current_context();

		EmscriptenWebGLContextAttributes attrs;
		EMSCRIPTEN_CHECK(emscripten_webgl_get_context_attributes(ctx, &attrs) );

		const int glesVersion = attrs.majorVersion + 1;

		switch(_format)
		{
			// GLES2 textures
			case TextureFormat::B5G6R5:
			case TextureFormat::R5G6B5:
			case TextureFormat::BGRA4:
			case TextureFormat::RGBA4:
			case TextureFormat::BGR5A1:
			case TextureFormat::RGB5A1:
			case TextureFormat::D16:
				return !_srgb;

			// GLES2 renderbuffers not a texture in GLES3
			case TextureFormat::D0S8:
				return !_srgb
					&& _writeOnly
					;

			// GLES2 textures that are not renderbuffers
			case TextureFormat::RGB8:
			case TextureFormat::RGBA8:
				return !_srgb
					&& (!_writeOnly || glesVersion >= 3)
					;

			// GLES3 EXT_color_buffer_float renderbuffer formats
			case TextureFormat::R16F:
			case TextureFormat::RG16F:
			case TextureFormat::R32F:
			case TextureFormat::RG32F:
			case TextureFormat::RG11B10F:
				if (_writeOnly)
				{
					return emscripten_webgl_enable_extension(ctx, "EXT_color_buffer_float");
				}

				return !_srgb && glesVersion >= 3;

			// GLES2 float extension:
			case TextureFormat::RGBA16F:
				if (_writeOnly && emscripten_webgl_enable_extension(ctx, "EXT_color_buffer_half_float") )
				{
					return true;
				}
				[[fallthrough]];

			case TextureFormat::RGBA32F:
				if (_writeOnly)
				{
					return emscripten_webgl_enable_extension(ctx, "EXT_color_buffer_float") || emscripten_webgl_enable_extension(ctx, "WEBGL_color_buffer_float");
				}

				// GLES3 formats without sRGB
				return !_srgb
					&& (glesVersion >= 3 || emscripten_webgl_enable_extension(ctx, "OES_texture_half_float") )
					;

			case TextureFormat::D24:
			case TextureFormat::D24S8:
				// GLES3 formats without sRGB, depth textures do not support mipmaps.
				return !_srgb
					&& (glesVersion >= 3 || (!_writeOnly && emscripten_webgl_enable_extension(ctx, "WEBGL_depth_texture") ) )
					;

			case TextureFormat::D32:
				// GLES3 formats without sRGB, depth textures do not support mipmaps.
				return !_srgb
					&& !_writeOnly
					&& (glesVersion >= 3 || emscripten_webgl_enable_extension(ctx, "WEBGL_depth_texture") )
					;

			// GLES3 textures
			case TextureFormat::R8:
			case TextureFormat::RG8:
			case TextureFormat::R8I:
			case TextureFormat::R8U:
			case TextureFormat::R16I:
			case TextureFormat::R16U:
			case TextureFormat::R32I:
			case TextureFormat::R32U:
			case TextureFormat::RG8I:
			case TextureFormat::RG8U:
			case TextureFormat::RGBA8I:
			case TextureFormat::RGBA8U:
			case TextureFormat::RG16I:
			case TextureFormat::RG16U:
			case TextureFormat::RG32I:
			case TextureFormat::RG32U:
			case TextureFormat::RGBA16I:
			case TextureFormat::RGBA16U:
			case TextureFormat::RGBA32I:
			case TextureFormat::RGBA32U:
			case TextureFormat::RGB10A2:
			case TextureFormat::D16F:
			case TextureFormat::D24F:
			case TextureFormat::D32F:
				return !_srgb
					&& glesVersion >= 3
					;

			case TextureFormat::BGRA8:
				return !_srgb
					&& _writeOnly
					&& glesVersion >= 3
					;

			default:
				break;
		}

		return false;
	}
#endif

	static bool isFramebufferFormatValid(
		  TextureFormat::Enum _format
		, bool _srgb = false
		, bool _writeOnly = false
		, GLsizei _dim = 16
		)
	{
#if BX_PLATFORM_EMSCRIPTEN
		// On web platform read the validity of framebuffers based on the available GL context and extensions
		// to avoid developer unfriendly console error noise that would come from probing.
		BX_UNUSED(_dim);
		return isFramebufferFormatValidPerSpec(_format, _srgb, _writeOnly);
#else
		// On other platforms probe the supported textures.
		const TextureFormatInfo& tfi = s_textureFormat[_format];
		GLenum internalFmt = _srgb
			? tfi.m_internalFmtSrgb
			: tfi.m_internalFmt
			;
		if (GL_ZERO == internalFmt)
		{
			return false;
		}

		if (_writeOnly)
		{
			GLuint rbo;
			glGenRenderbuffers(1, &rbo);
			glBindRenderbuffer(GL_RENDERBUFFER, rbo);

			glRenderbufferStorage(GL_RENDERBUFFER
				, s_rboFormat[_format]
				, _dim
				, _dim
				);
			glBindRenderbuffer(GL_RENDERBUFFER, 0);
			glDeleteRenderbuffers(1, &rbo);

			GLenum err = getGlError();
			return 0 == err;
		}

		GLuint fbo;
		GL_CHECK(glGenFramebuffers(1, &fbo) );
		GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, fbo) );

		GLuint id;
		GL_CHECK(glGenTextures(1, &id) );
		GL_CHECK(glBindTexture(GL_TEXTURE_2D, id) );

		GLenum err = initTestTexture(_format, _srgb, false, false, _dim);

		GLenum attachment;
		if (bimg::isDepth(bimg::TextureFormat::Enum(_format) ) )
		{
			const bimg::ImageBlockInfo& info = bimg::getBlockInfo(bimg::TextureFormat::Enum(_format) );
			if (0 == info.depthBits)
			{
				attachment = GL_STENCIL_ATTACHMENT;
			}
			else if (0 == info.stencilBits)
			{
				attachment = GL_DEPTH_ATTACHMENT;
			}
			else
			{
				attachment = GL_DEPTH_STENCIL_ATTACHMENT;
			}
		}
		else
		{
			attachment = GL_COLOR_ATTACHMENT0;
		}

		glFramebufferTexture2D(GL_FRAMEBUFFER
				, attachment
				, GL_TEXTURE_2D
				, id
				, 0
				);
		err = getGlError();

		if (0 == err)
		{
			err = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		}

		GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0) );
		GL_CHECK(glDeleteFramebuffers(1, &fbo) );

		GL_CHECK(glDeleteTextures(1, &id) );

		return GL_FRAMEBUFFER_COMPLETE == err;
#endif
	}

	static void getFilters(uint32_t _flags, bool _hasMips, GLenum& _magFilter, GLenum& _minFilter)
	{
		const uint32_t mag = (_flags&BGFX_SAMPLER_MAG_MASK)>>BGFX_SAMPLER_MAG_SHIFT;
		const uint32_t min = (_flags&BGFX_SAMPLER_MIN_MASK)>>BGFX_SAMPLER_MIN_SHIFT;
		const uint32_t mip = (_flags&BGFX_SAMPLER_MIP_MASK)>>BGFX_SAMPLER_MIP_SHIFT;
		_magFilter = s_textureFilterMag[mag];
		_minFilter = s_textureFilterMin[min][_hasMips ? mip+1 : 0];
	}

	void updateExtension(const bx::StringView& _name)
	{
		bx::StringView ext(_name);
		if (0 == bx::strCmp(ext, "GL_", 3) ) // skip GL_
		{
			ext.set(ext.getPtr()+3, ext.getTerm() );
		}

		bool supported = false;
		for (uint32_t ii = 0; ii < Extension::Count; ++ii)
		{
			Extension& extension = s_extension[ii];
			if (!extension.m_supported
			&&  extension.m_initialize)
			{
				if (0 == bx::strCmp(ext, extension.m_name) )
				{
#if BX_PLATFORM_EMSCRIPTEN
					EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx = emscripten_webgl_get_current_context();
					supported = emscripten_webgl_enable_extension(ctx, extension.m_name);
#else
					supported = true;
#endif
					extension.m_supported = supported;
					break;
				}
			}
		}

		BX_TRACE("GL_EXTENSION %s: %.*s", supported ? " (supported)" : "", _name.getLength(), _name.getPtr() );
		BX_UNUSED(supported);
	}

	struct VendorId
	{
		const char* name;
		uint16_t id;
	};

	static const VendorId s_vendorIds[] =
	{
		{ "NVIDIA Corporation",           BGFX_PCI_ID_NVIDIA },
		{ "Advanced Micro Devices, Inc.", BGFX_PCI_ID_AMD    },
		{ "Intel",                        BGFX_PCI_ID_INTEL  },
		{ "ATI Technologies Inc.",        BGFX_PCI_ID_AMD    },
		{ "ARM",                          BGFX_PCI_ID_ARM    },
	};

	struct Workaround
	{
		void reset()
		{
			m_detachShader = true;
		}

		bool m_detachShader;
	};

	struct RendererContextGL : public RendererContextI
	{
		RendererContextGL()
			: m_numWindows(1)
			, m_rtMsaa(false)
			, m_fbDiscard(BGFX_CLEAR_NONE)
			, m_capture(NULL)
			, m_captureSize(0)
			, m_maxAnisotropy(0.0f)
			, m_maxAnisotropyDefault(0.0f)
			, m_maxMsaa(0)
			, m_vao(0)
			, m_blitSupported(false)
			, m_readBackSupported(BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGL) )
			, m_vaoSupport(false)
			, m_samplerObjectSupport(false)
			, m_shadowSamplersSupport(false)
			, m_srgbWriteControlSupport(BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGL) )
			, m_borderColorSupport(BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGL) )
			, m_programBinarySupport(false)
			, m_textureSwizzleSupport(false)
			, m_depthTextureSupport(false)
			, m_timerQuerySupport(false)
			, m_occlusionQuerySupport(false)
			, m_atocSupport(false)
			, m_conservativeRasterSupport(false)
			, m_flip(false)
			, m_hash( (BX_PLATFORM_WINDOWS<<1) | BX_ARCH_64BIT)
			, m_backBufferFbo(0)
			, m_msaaBackBufferFbo(0)
			, m_msaaBlitProgram(0)
			, m_clearQuadColor(BGFX_INVALID_HANDLE)
			, m_clearQuadDepth(BGFX_INVALID_HANDLE)
		{
			bx::memSet(m_msaaBackBufferRbos, 0, sizeof(m_msaaBackBufferRbos) );
		}

		~RendererContextGL()
		{
		}

		bool init(const Init& _init)
		{
			struct ErrorState
			{
				enum Enum
				{
					Default,
				};
			};

			ErrorState::Enum errorState = ErrorState::Default;

			initLazyEnabledVertexAttributes();

			if (_init.debug
			||  _init.profile)
			{
				m_renderdocdll = loadRenderDoc();
			}

			m_fbh.idx = kInvalidHandle;
			bx::memSet(m_uniforms, 0, sizeof(m_uniforms) );
			bx::memSet(&m_resolution, 0, sizeof(m_resolution) );

			setRenderContextSize(_init.resolution.width, _init.resolution.height, _init.resolution.reset);

			m_vendor      = getGLString(GL_VENDOR);
			m_renderer    = getGLString(GL_RENDERER);
			m_version     = getGLString(GL_VERSION);
			m_glslVersion = getGLString(GL_SHADING_LANGUAGE_VERSION);

			{
				if (BX_ENABLED(BX_PLATFORM_EMSCRIPTEN) )
				{
					int32_t majorGlVersion = 0;
					int32_t minorGlVersion = 0;
					const char* version = m_version;

					while (*version && !bx::isNumeric(*version) )
					{
						++version;
					}

					bx::fromString(&majorGlVersion, version);
					bx::fromString(&minorGlVersion, version + 2);
					int32_t glVersion = majorGlVersion*10 + minorGlVersion;

					BX_TRACE("WebGL context version %d (%d.%d).", glVersion, majorGlVersion, minorGlVersion);

					m_gles3 = glVersion >= 30;
				}
				else
				{
					m_gles3 = BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGLES >= 30);
				}
			}

			for (uint32_t ii = 0; ii < BX_COUNTOF(s_vendorIds); ++ii)
			{
				const VendorId& vendorId = s_vendorIds[ii];
				if (0 == bx::strCmp(vendorId.name, m_vendor, bx::strLen(vendorId.name) ) )
				{
					g_caps.vendorId = vendorId.id;
					break;
				}
			}

			m_workaround.reset();

			GLint numCmpFormats = 0;
			GL_CHECK(glGetIntegerv(GL_NUM_COMPRESSED_TEXTURE_FORMATS, &numCmpFormats) );
			BX_TRACE("GL_NUM_COMPRESSED_TEXTURE_FORMATS %d", numCmpFormats);

			GLint* cmpFormat = NULL;

			if (0 < numCmpFormats)
			{
				numCmpFormats = numCmpFormats > 256 ? 256 : numCmpFormats;
				cmpFormat = (GLint*)alloca(sizeof(GLint)*numCmpFormats);
				GL_CHECK(glGetIntegerv(GL_COMPRESSED_TEXTURE_FORMATS, cmpFormat) );

				for (GLint ii = 0; ii < numCmpFormats; ++ii)
				{
					GLint internalFmt = cmpFormat[ii];
					uint32_t fmt = uint32_t(TextureFormat::Unknown);
					for (uint32_t jj = 0; jj < fmt; ++jj)
					{
						if (s_textureFormat[jj].m_internalFmt == (GLenum)internalFmt)
						{
							s_textureFormat[jj].m_supported = true;
							fmt = jj;
						}
					}

					BX_TRACE("  %3d: %8x %s", ii, internalFmt, getName( (TextureFormat::Enum)fmt) );
				}
			}

			if (BX_ENABLED(BGFX_CONFIG_DEBUG) )
			{
#define GL_GET(_pname, _min) BX_TRACE("  " #_pname " %d (min: %d)", glGet(_pname), _min)
				BX_TRACE("Defaults:");
#if BGFX_CONFIG_RENDERER_OPENGL >= 41 || BGFX_CONFIG_RENDERER_OPENGLES
				GL_GET(GL_MAX_FRAGMENT_UNIFORM_VECTORS, 16);
				GL_GET(GL_MAX_VERTEX_UNIFORM_VECTORS, 128);
				GL_GET(GL_MAX_VARYING_VECTORS, 8);
#else
				GL_GET(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, 16 * 4);
				GL_GET(GL_MAX_VERTEX_UNIFORM_COMPONENTS, 128 * 4);
				GL_GET(GL_MAX_VARYING_FLOATS, 8 * 4);
#endif // BGFX_CONFIG_RENDERER_OPENGL >= 41 || BGFX_CONFIG_RENDERER_OPENGLES
				GL_GET(GL_MAX_VERTEX_ATTRIBS, 8);
				GL_GET(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, 8);
				GL_GET(GL_MAX_CUBE_MAP_TEXTURE_SIZE, 16);
				GL_GET(GL_MAX_TEXTURE_IMAGE_UNITS, 8);
				GL_GET(GL_MAX_TEXTURE_SIZE, 64);
				GL_GET(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, 0);
				GL_GET(GL_MAX_RENDERBUFFER_SIZE, 1);
				GL_GET(GL_MAX_COLOR_ATTACHMENTS, 1);
				GL_GET(GL_MAX_DRAW_BUFFERS, 1);

#undef GL_GET

				BX_TRACE("      Vendor: %s", m_vendor);
				BX_TRACE("    Renderer: %s", m_renderer);
				BX_TRACE("     Version: %s", m_version);
				BX_TRACE("GLSL version: %s", m_glslVersion);
			}

			// Initial binary shader hash depends on driver version.
			m_hash = ( (BX_PLATFORM_WINDOWS<<1) | BX_ARCH_64BIT)
				^ (uint64_t(getGLStringHash(GL_VENDOR  ) )<<32)
				^ (uint64_t(getGLStringHash(GL_RENDERER) )<<0 )
				^ (uint64_t(getGLStringHash(GL_VERSION ) )<<16)
				;

			if (BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGLES >= 31)
			&&  0 == bx::strCmp(m_vendor, "Imagination Technologies")
			&&  !bx::strFind(m_version, "(SDK 3.5@3510720)").isEmpty() )
			{
				// Skip initializing extensions that are broken in emulator.
				s_extension[Extension::ARB_program_interface_query     ].m_initialize =
				s_extension[Extension::ARB_shader_storage_buffer_object].m_initialize = false;
			}

			if (BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGLES)
			&&  0 == bx::strCmp(m_vendor, "Imagination Technologies")
			&&  !bx::strFind(m_version, "1.8@905891").isEmpty() )
			{
				m_workaround.m_detachShader = false;
			}

			if (BX_ENABLED(BGFX_CONFIG_RENDERER_USE_EXTENSIONS) )
			{
				const char* extensions = (const char*)glGetString(GL_EXTENSIONS);
				getGlError(); // ignore error if glGetString returns NULL.
				if (NULL != extensions)
				{
					bx::StringView ext(extensions);

					while (!ext.isEmpty() )
					{
						const bx::StringView space = bx::strFind(ext, ' ');
						const bx::StringView token = bx::StringView(ext.getPtr(), space.getPtr() );
						updateExtension(token);

						ext.set(space.getPtr() + (space.isEmpty() ? 0 : 1), ext.getTerm() );
					}
				}
				else if (NULL != glGetStringi)
				{
					GLint numExtensions = 0;
					glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);
					getGlError(); // ignore error if glGetIntegerv returns NULL.

					for (GLint index = 0; index < numExtensions; ++index)
					{
						const char* name = (const char*)glGetStringi(GL_EXTENSIONS, index);
						updateExtension(name);
					}
				}

				BX_TRACE("Supported extensions:");
				for (uint32_t ii = 0; ii < Extension::Count; ++ii)
				{
					if (s_extension[ii].m_supported)
					{
						BX_TRACE("\t%2d: %s", ii, s_extension[ii].m_name);
					}
				}
			}

			if (BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGL)
			&&  !s_extension[Extension::ARB_framebuffer_object].m_supported)
			{
				BX_TRACE("Init error: ARB_framebuffer_object not supported.");
				goto error;
			}

			{
				// Allow all texture filters.
				bx::memSet(s_textureFilter, true, BX_COUNTOF(s_textureFilter) );

				bool bc123Supported = 0
					|| s_extension[Extension::EXT_texture_compression_s3tc        ].m_supported
					|| s_extension[Extension::MOZ_WEBGL_compressed_texture_s3tc   ].m_supported
					|| s_extension[Extension::WEBGL_compressed_texture_s3tc       ].m_supported
					|| s_extension[Extension::WEBKIT_WEBGL_compressed_texture_s3tc].m_supported
					;
				s_textureFormat[TextureFormat::BC1].m_supported |= bc123Supported
					|| s_extension[Extension::ANGLE_texture_compression_dxt1].m_supported
					|| s_extension[Extension::EXT_texture_compression_dxt1  ].m_supported
					;

				if (!s_textureFormat[TextureFormat::BC1].m_supported
				&& ( s_textureFormat[TextureFormat::BC2].m_supported || s_textureFormat[TextureFormat::BC3].m_supported) )
				{
					// If RGBA_S3TC_DXT1 is not supported, maybe RGB_S3TC_DXT1 is?
					for (GLint ii = 0; ii < numCmpFormats; ++ii)
					{
						if (GL_COMPRESSED_RGB_S3TC_DXT1_EXT == cmpFormat[ii])
						{
							setTextureFormat(TextureFormat::BC1, GL_COMPRESSED_RGB_S3TC_DXT1_EXT, GL_COMPRESSED_RGB_S3TC_DXT1_EXT);
							s_textureFormat[TextureFormat::BC1].m_supported   = true;
							break;
						}
					}
				}

				s_textureFormat[TextureFormat::BC2].m_supported |= bc123Supported
					|| s_extension[Extension::ANGLE_texture_compression_dxt3   ].m_supported
					|| s_extension[Extension::CHROMIUM_texture_compression_dxt3].m_supported
					;

				s_textureFormat[TextureFormat::BC3].m_supported |= bc123Supported
					|| s_extension[Extension::ANGLE_texture_compression_dxt5   ].m_supported
					|| s_extension[Extension::CHROMIUM_texture_compression_dxt5].m_supported
					;

				if (s_extension[Extension::EXT_texture_compression_latc].m_supported)
				{
					setTextureFormat(TextureFormat::BC4, GL_COMPRESSED_LUMINANCE_LATC1_EXT,       GL_COMPRESSED_LUMINANCE_LATC1_EXT);
					setTextureFormat(TextureFormat::BC5, GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT, GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT);
				}

				if (s_extension[Extension::ARB_texture_compression_rgtc].m_supported
				||  s_extension[Extension::EXT_texture_compression_rgtc].m_supported)
				{
					setTextureFormat(TextureFormat::BC4, GL_COMPRESSED_RED_RGTC1, GL_COMPRESSED_RED_RGTC1);
					setTextureFormat(TextureFormat::BC5, GL_COMPRESSED_RG_RGTC2,  GL_COMPRESSED_RG_RGTC2);
				}

				bool etc1Supported = 0
					|| s_extension[Extension::OES_compressed_ETC1_RGB8_texture].m_supported
					|| s_extension[Extension::WEBGL_compressed_texture_etc1   ].m_supported
					;
				s_textureFormat[TextureFormat::ETC1].m_supported |= etc1Supported;

				bool etc2Supported = !!(BGFX_CONFIG_RENDERER_OPENGLES >= 30)
					|| s_extension[Extension::ARB_ES3_compatibility].m_supported
					;
				s_textureFormat[TextureFormat::ETC2  ].m_supported |= etc2Supported;
				s_textureFormat[TextureFormat::ETC2A ].m_supported |= etc2Supported;
				s_textureFormat[TextureFormat::ETC2A1].m_supported |= etc2Supported;

				if (!s_textureFormat[TextureFormat::ETC1].m_supported
				&&   s_textureFormat[TextureFormat::ETC2].m_supported)
				{
					// When ETC2 is supported override ETC1 texture format settings.
					s_textureFormat[TextureFormat::ETC1].m_internalFmt = GL_COMPRESSED_RGB8_ETC2;
					s_textureFormat[TextureFormat::ETC1].m_fmt         = GL_COMPRESSED_RGB8_ETC2;
					s_textureFormat[TextureFormat::ETC1].m_supported   = true;
				}

				bool ptc1Supported = 0
					|| s_extension[Extension::IMG_texture_compression_pvrtc ].m_supported
					|| s_extension[Extension::WEBGL_compressed_texture_pvrtc].m_supported
					;
				s_textureFormat[TextureFormat::PTC12 ].m_supported |= ptc1Supported;
				s_textureFormat[TextureFormat::PTC14 ].m_supported |= ptc1Supported;
				s_textureFormat[TextureFormat::PTC12A].m_supported |= ptc1Supported;
				s_textureFormat[TextureFormat::PTC14A].m_supported |= ptc1Supported;

				bool ptc2Supported = s_extension[Extension::IMG_texture_compression_pvrtc2].m_supported;
				s_textureFormat[TextureFormat::PTC22].m_supported |= ptc2Supported;
				s_textureFormat[TextureFormat::PTC24].m_supported |= ptc2Supported;

				if (BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGLES) )
				{
					if (m_gles3)
					{
						setTextureFormat(TextureFormat::R16F,    GL_R16F,    GL_RED,  0x140B /* == GL_HALF_FLOAT, but bgfx overwrites it globally with GL_HALF_FLOAT_OES */);
						setTextureFormat(TextureFormat::RG16F,   GL_RG16F,   GL_RG,   0x140B /* == GL_HALF_FLOAT, but bgfx overwrites it globally with GL_HALF_FLOAT_OES */);
						setTextureFormat(TextureFormat::RGBA16F, GL_RGBA16F, GL_RGBA, 0x140B /* == GL_HALF_FLOAT, but bgfx overwrites it globally with GL_HALF_FLOAT_OES */);
					}
					else
					{
						setTextureFormat(TextureFormat::RGBA16F, GL_RGBA, GL_RGBA, GL_HALF_FLOAT); // Note: this is actually GL_HALF_FLOAT_OES and not GL_HALF_FLOAT if compiling for GLES target.
						setTextureFormat(TextureFormat::RGBA32F, GL_RGBA, GL_RGBA, GL_FLOAT);
						// internalFormat and format must match:
						// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexImage2D.xml
						setTextureFormat(TextureFormat::RGBA8,  GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
						setTextureFormat(TextureFormat::B5G6R5, GL_RGB,  GL_RGB,  GL_UNSIGNED_SHORT_5_6_5_REV);
						setTextureFormat(TextureFormat::R5G6B5, GL_RGB,  GL_RGB,  GL_UNSIGNED_SHORT_5_6_5_REV);
						setTextureFormat(TextureFormat::BGRA4,  GL_BGRA, GL_BGRA, GL_UNSIGNED_SHORT_4_4_4_4_REV);
						setTextureFormat(TextureFormat::RGBA4,  GL_RGBA, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4_REV);
						setTextureFormat(TextureFormat::BGR5A1, GL_BGRA, GL_BGRA, GL_UNSIGNED_SHORT_1_5_5_5_REV);
						setTextureFormat(TextureFormat::RGB5A1, GL_RGBA, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV);

						if (s_extension[Extension::EXT_sRGB].m_supported)
						{
							setTextureFormatSrgb(TextureFormat::RGBA8, GL_SRGB_ALPHA_EXT, GL_SRGB_ALPHA_EXT);
							setTextureFormatSrgb(TextureFormat::RGB8, GL_SRGB_EXT, GL_SRGB_EXT);
						}

						if (s_extension[Extension::EXT_texture_swizzle].m_supported)
						{
							s_textureFormat[TextureFormat::R5G6B5].m_mapping[0] = GL_BLUE;
							s_textureFormat[TextureFormat::R5G6B5].m_mapping[2] = GL_RED;
						}

						if (s_extension[Extension::OES_texture_half_float].m_supported
						||  s_extension[Extension::OES_texture_float     ].m_supported)
						{
							// https://www.khronos.org/registry/gles/extensions/OES/OES_texture_float.txt
							// When half/float is available via extensions texture will be marked as
							// incomplete if it uses anything other than nearest filter.
							const bool linear16F = s_extension[Extension::OES_texture_half_float_linear].m_supported;
							const bool linear32F = s_extension[Extension::OES_texture_float_linear     ].m_supported;

							s_textureFilter[TextureFormat::R16F]    = linear16F;
							s_textureFilter[TextureFormat::RG16F]   = linear16F;
							s_textureFilter[TextureFormat::RGBA16F] = linear16F;
							s_textureFilter[TextureFormat::R32F]    = linear32F;
							s_textureFilter[TextureFormat::RG32F]   = linear32F;
							s_textureFilter[TextureFormat::RGBA32F] = linear32F;
						}
					}

					if (BX_ENABLED(BX_PLATFORM_EMSCRIPTEN)
						&& (s_extension[Extension::WEBGL_depth_texture].m_supported
						|| s_extension[Extension::MOZ_WEBGL_depth_texture].m_supported
						|| s_extension[Extension::WEBKIT_WEBGL_depth_texture].m_supported) )
					{
						setTextureFormat(TextureFormat::D16,   GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT);
						setTextureFormat(TextureFormat::D24,   GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT); // N.b. OpenGL ES does not guarantee that there are 24 bits available here, could be 16. See https://www.khronos.org/registry/webgl/extensions/WEBGL_depth_texture/
						setTextureFormat(TextureFormat::D32,   GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT); // N.b. same as above.
						setTextureFormat(TextureFormat::D24S8, GL_DEPTH_STENCIL,   GL_DEPTH_STENCIL,   GL_UNSIGNED_INT_24_8);
					}

					// OpenGL ES 3.0 depth formats.
					if (m_gles3)
					{
						setTextureFormat(TextureFormat::D16,   GL_DEPTH_COMPONENT16,  GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT);
						setTextureFormat(TextureFormat::D24,   GL_DEPTH_COMPONENT24,  GL_DEPTH_COMPONENT, GL_UNSIGNED_INT);
						setTextureFormat(TextureFormat::D32,   GL_DEPTH_COMPONENT24,  GL_DEPTH_COMPONENT, GL_UNSIGNED_INT);
						setTextureFormat(TextureFormat::D24S8, GL_DEPTH24_STENCIL8,   GL_DEPTH_STENCIL,   GL_UNSIGNED_INT_24_8);
						setTextureFormat(TextureFormat::D16F,  GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT, GL_FLOAT); // GLES 3.0 does not have D16F, overshoot to D32F
						setTextureFormat(TextureFormat::D24F,  GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT, GL_FLOAT); // GLES 3.0 does not have D24F, overshoot to D32F
						setTextureFormat(TextureFormat::D32F,  GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT, GL_FLOAT);
						setTextureFormat(TextureFormat::D0S8,  GL_STENCIL_INDEX8, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE); // Only works as renderbuffer, not as texture
					}
				}
				else
				{
					setTextureFormat(TextureFormat::R5G6B5, GL_BGR,  GL_BGR,  GL_UNSIGNED_SHORT_5_6_5);
					setTextureFormatSrgb(TextureFormat::R5G6B5, GL_ZERO,  GL_BGR);
				}

				if (BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGL)
				||  m_gles3)
				{
					setTextureFormat(TextureFormat::R8I,     GL_R8I,      GL_RED_INTEGER,  GL_BYTE);
					setTextureFormat(TextureFormat::R8U,     GL_R8UI,     GL_RED_INTEGER,  GL_UNSIGNED_BYTE);
					setTextureFormat(TextureFormat::R16I,    GL_R16I,     GL_RED_INTEGER,  GL_SHORT);
					setTextureFormat(TextureFormat::R16U,    GL_R16UI,    GL_RED_INTEGER,  GL_UNSIGNED_SHORT);
	//				setTextureFormat(TextureFormat::RG16,    GL_RG16UI,   GL_RG_INTEGER,   GL_UNSIGNED_SHORT);
	//				setTextureFormat(TextureFormat::RGBA16,  GL_RGBA16UI, GL_RGBA_INTEGER, GL_UNSIGNED_SHORT);
					setTextureFormat(TextureFormat::R32U,    GL_R32UI,    GL_RED_INTEGER,  GL_UNSIGNED_INT);
					setTextureFormat(TextureFormat::RG32U,   GL_RG32UI,   GL_RG_INTEGER,   GL_UNSIGNED_INT);
					setTextureFormat(TextureFormat::RGBA32U, GL_RGBA32UI, GL_RGBA_INTEGER, GL_UNSIGNED_INT);
				}

				if (s_extension[Extension::EXT_texture_format_BGRA8888  ].m_supported
				||  s_extension[Extension::EXT_bgra                     ].m_supported
				||  s_extension[Extension::IMG_texture_format_BGRA8888  ].m_supported
				||  s_extension[Extension::APPLE_texture_format_BGRA8888].m_supported)
				{
					if (BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGL) )
					{
						m_readPixelsFmt = GL_BGRA;
					}

					// Mixing GLES and GL extensions here. OpenGL EXT_bgra and
					// APPLE_texture_format_BGRA8888 wants
					// format to be BGRA but internal format to stay RGBA, but
					// EXT_texture_format_BGRA8888 wants both format and internal
					// format to be BGRA.
					//
					// Reference(s):
					// - https://web.archive.org/web/20181126035829/https://www.khronos.org/registry/OpenGL/extensions/EXT/EXT_texture_format_BGRA8888.txt
					// - https://web.archive.org/web/20181126035841/https://www.khronos.org/registry/OpenGL/extensions/EXT/EXT_bgra.txt
					// - https://web.archive.org/web/20181126035851/https://www.khronos.org/registry/OpenGL/extensions/APPLE/APPLE_texture_format_BGRA8888.txt
					//
					if (!s_extension[Extension::EXT_bgra                     ].m_supported
					&&  !s_extension[Extension::APPLE_texture_format_BGRA8888].m_supported)
					{
						s_textureFormat[TextureFormat::BGRA8].m_internalFmt = GL_BGRA;
					}

					if (!isTextureFormatValid(TextureFormat::BGRA8) )
					{
						// Revert back to RGBA if texture can't be created.
						setTextureFormat(TextureFormat::BGRA8, GL_RGBA, GL_BGRA, GL_UNSIGNED_BYTE);
					}
				}

				if (BX_ENABLED(BX_PLATFORM_EMSCRIPTEN) )
				{
					// OpenGL ES does not have reversed BGRA4 and BGR5A1 support.
					setTextureFormat(TextureFormat::BGRA4,  GL_RGBA, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4);
					setTextureFormat(TextureFormat::RGBA4,  GL_RGBA, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4);
					setTextureFormat(TextureFormat::BGR5A1, GL_RGBA, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1);
					setTextureFormat(TextureFormat::RGB5A1, GL_RGBA, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1);
					setTextureFormat(TextureFormat::B5G6R5, GL_RGB,  GL_RGB,  GL_UNSIGNED_SHORT_5_6_5);
					setTextureFormat(TextureFormat::R5G6B5, GL_RGB,  GL_RGB,  GL_UNSIGNED_SHORT_5_6_5);

					if (!m_gles3)
					{
						// OpenGL ES 2.0 uses unsized internal formats.
						s_textureFormat[TextureFormat::RGB8].m_internalFmt = GL_RGB;

						// OpenGL ES 2.0 does not have R8 texture format, only L8. Open GL ES 2.0 extension https://www.khronos.org/registry/OpenGL/extensions/EXT/EXT_texture_rg.txt
						// adds support for R8 to GLES 2.0 core contexts. For those use L8 instead.
						if (!s_extension[Extension::EXT_texture_rg].m_supported)
						{
							s_textureFormat[TextureFormat::R8].m_internalFmt = GL_LUMINANCE;
							s_textureFormat[TextureFormat::R8].m_fmt         = GL_LUMINANCE;
						}
					}
				}

				for (uint32_t ii = 0; ii < TextureFormat::Count; ++ii)
				{
					if (TextureFormat::Unknown != ii
					&&  TextureFormat::UnknownDepth != ii)
					{
						s_textureFormat[ii].m_supported = isTextureFormatValid(TextureFormat::Enum(ii) );
					}
				}

				if (BX_ENABLED(0) )
				{
					// Disable all compressed texture formats. For testing only.
					for (uint32_t ii = 0; ii < TextureFormat::Unknown; ++ii)
					{
						s_textureFormat[ii].m_supported = false;
					}
				}

				const bool computeSupport = false
					|| !!(BGFX_CONFIG_RENDERER_OPENGLES >= 31)
					|| s_extension[Extension::ARB_compute_shader].m_supported
					;

				for (uint32_t ii = 0; ii < TextureFormat::Count; ++ii)
				{
					const TextureFormat::Enum fmt = TextureFormat::Enum(ii);

					uint16_t supported = BGFX_CAPS_FORMAT_TEXTURE_NONE;
					supported |= s_textureFormat[ii].m_supported
						? BGFX_CAPS_FORMAT_TEXTURE_2D
						| BGFX_CAPS_FORMAT_TEXTURE_3D
						| BGFX_CAPS_FORMAT_TEXTURE_CUBE
						: BGFX_CAPS_FORMAT_TEXTURE_NONE
						;

					supported |= isTextureFormatValid(fmt, true)
						? BGFX_CAPS_FORMAT_TEXTURE_2D_SRGB
						| BGFX_CAPS_FORMAT_TEXTURE_3D_SRGB
						| BGFX_CAPS_FORMAT_TEXTURE_CUBE_SRGB
						: BGFX_CAPS_FORMAT_TEXTURE_NONE
						;

					if (!bimg::isCompressed(bimg::TextureFormat::Enum(fmt) ) )
					{
						supported |= isTextureFormatValid(fmt, false, true)
							? BGFX_CAPS_FORMAT_TEXTURE_MIP_AUTOGEN
							: BGFX_CAPS_FORMAT_TEXTURE_NONE
							;
					}

					supported |= computeSupport
						&& isImageFormatValid(fmt)
						? (BGFX_CAPS_FORMAT_TEXTURE_IMAGE_READ | BGFX_CAPS_FORMAT_TEXTURE_IMAGE_WRITE)
						: BGFX_CAPS_FORMAT_TEXTURE_NONE
						;

					supported |= isFramebufferFormatValid(fmt)
						? BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER
						: BGFX_CAPS_FORMAT_TEXTURE_NONE
						;

					supported |= isFramebufferFormatValid(fmt, false, true)
						? BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER
						: BGFX_CAPS_FORMAT_TEXTURE_NONE
						;

					if (NULL != glGetInternalformativ)
					{
						GLint maxSamples;
						glGetInternalformativ(GL_RENDERBUFFER
							, s_textureFormat[ii].m_internalFmt
							, GL_SAMPLES
							, 1
							, &maxSamples
							);
						GLenum err = getGlError();
						supported |= 0 == err && maxSamples > 0
							? BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA
							: BGFX_CAPS_FORMAT_TEXTURE_NONE
							;

						glGetInternalformativ(GL_TEXTURE_2D_MULTISAMPLE
							, s_textureFormat[ii].m_internalFmt
							, GL_SAMPLES
							, 1
							, &maxSamples
							);
						err = getGlError();
						supported |= 0 == err && maxSamples > 0
							? BGFX_CAPS_FORMAT_TEXTURE_MSAA
							: BGFX_CAPS_FORMAT_TEXTURE_NONE
							;
					}

					g_caps.formats[ii] = supported;
				}

				g_caps.supported |= !!(BGFX_CONFIG_RENDERER_OPENGL || m_gles3)
					|| s_extension[Extension::OES_texture_3D].m_supported
					? BGFX_CAPS_TEXTURE_3D
					: 0
					;
				g_caps.supported |= !!(BGFX_CONFIG_RENDERER_OPENGL || m_gles3)
					|| s_extension[Extension::EXT_shadow_samplers].m_supported
					? BGFX_CAPS_TEXTURE_COMPARE_ALL
					: 0
					;
				g_caps.supported |= !!(BGFX_CONFIG_RENDERER_OPENGL || m_gles3)
					|| s_extension[Extension::OES_vertex_half_float].m_supported
					? BGFX_CAPS_VERTEX_ATTRIB_HALF
					: 0
					;
				g_caps.supported |= false
					|| s_extension[Extension::ARB_vertex_type_2_10_10_10_rev].m_supported
					|| s_extension[Extension::OES_vertex_type_10_10_10_2].m_supported
					? BGFX_CAPS_VERTEX_ATTRIB_UINT10
					: 0
					;
				g_caps.supported |= !!(BGFX_CONFIG_RENDERER_OPENGL || m_gles3)
					|| s_extension[Extension::EXT_frag_depth].m_supported
					? BGFX_CAPS_FRAGMENT_DEPTH
					: 0
					;
				g_caps.supported |= s_extension[Extension::ARB_draw_buffers_blend].m_supported
					? BGFX_CAPS_BLEND_INDEPENDENT
					: 0
					;
				g_caps.supported |= s_extension[Extension::INTEL_fragment_shader_ordering].m_supported
					? BGFX_CAPS_FRAGMENT_ORDERING
					: 0
					;
				g_caps.supported |= !!(BGFX_CONFIG_RENDERER_OPENGL || m_gles3)
					|| s_extension[Extension::OES_element_index_uint].m_supported
					? BGFX_CAPS_INDEX32
					: 0
					;

				const bool drawIndirectSupported = false
					|| s_extension[Extension::AMD_multi_draw_indirect].m_supported
					|| s_extension[Extension::ARB_draw_indirect      ].m_supported
					|| s_extension[Extension::ARB_multi_draw_indirect].m_supported
					|| s_extension[Extension::EXT_multi_draw_indirect].m_supported
					;

				if (drawIndirectSupported)
				{
					if (NULL == glMultiDrawArraysIndirect
					||  NULL == glMultiDrawElementsIndirect)
					{
						glMultiDrawArraysIndirect   = stubMultiDrawArraysIndirect;
						glMultiDrawElementsIndirect = stubMultiDrawElementsIndirect;
					}
				}

				g_caps.supported |= drawIndirectSupported
					? BGFX_CAPS_DRAW_INDIRECT
					: 0
					;

				g_caps.supported |= s_extension[Extension::ARB_indirect_parameters].m_supported
					? BGFX_CAPS_DRAW_INDIRECT_COUNT
					: 0
					;

				if (BX_ENABLED(BX_PLATFORM_EMSCRIPTEN)
				||  NULL == glPolygonMode)
				{
					glPolygonMode = stubPolygonMode;
				}

				if (s_extension[Extension::ARB_copy_image].m_supported
				||  s_extension[Extension::EXT_copy_image].m_supported
				||  s_extension[Extension:: NV_copy_image].m_supported
				||  s_extension[Extension::OES_copy_image].m_supported)
				{
					m_blitSupported = NULL != glCopyImageSubData;
				}

				g_caps.supported |= m_blitSupported || BX_ENABLED(BGFX_GL_CONFIG_BLIT_EMULATION)
					? BGFX_CAPS_TEXTURE_BLIT
					: 0
					;

				g_caps.supported |= (m_readBackSupported || BX_ENABLED(BGFX_GL_CONFIG_TEXTURE_READ_BACK_EMULATION) )
					? BGFX_CAPS_TEXTURE_READ_BACK
					: 0
					;

				g_caps.supported |= false
					|| s_extension[Extension::EXT_texture_array].m_supported
					|| s_extension[Extension::EXT_gpu_shader4].m_supported
					|| (m_gles3 && !BX_ENABLED(BX_PLATFORM_EMSCRIPTEN) )
					? BGFX_CAPS_TEXTURE_2D_ARRAY
					: 0
					;

				g_caps.supported |= false
					|| s_extension[Extension::EXT_gpu_shader4].m_supported
					|| (m_gles3 && !BX_ENABLED(BX_PLATFORM_EMSCRIPTEN) )
					? BGFX_CAPS_VERTEX_ID
					: 0
					;

				g_caps.supported |= false
					|| BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGL >= 32)
					|| (m_gles3 && !BX_ENABLED(BX_PLATFORM_EMSCRIPTEN) && BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGLES >= 32) )
					? BGFX_CAPS_PRIMITIVE_ID
					: 0
					;

				g_caps.supported |= false
					|| s_extension[Extension::ARB_texture_cube_map_array].m_supported
					|| s_extension[Extension::EXT_texture_cube_map_array].m_supported
					? BGFX_CAPS_TEXTURE_CUBE_ARRAY
					: 0
					;

				g_caps.limits.maxTextureSize     = uint32_t(glGet(GL_MAX_TEXTURE_SIZE) );
				g_caps.limits.maxTextureLayers   = BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGL >= 30) || BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGLES >= 30) || s_extension[Extension::EXT_texture_array].m_supported ? uint16_t(bx::max(glGet(GL_MAX_ARRAY_TEXTURE_LAYERS), 1) ) : 1;
				g_caps.limits.maxComputeBindings = computeSupport ? BGFX_MAX_COMPUTE_BINDINGS : 0;
				g_caps.limits.maxVertexStreams   = BGFX_CONFIG_MAX_VERTEX_STREAMS;

				if (BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGL)
				||  m_gles3
				||  s_extension[Extension::EXT_draw_buffers  ].m_supported
				||  s_extension[Extension::WEBGL_draw_buffers].m_supported)
				{
					g_caps.limits.maxFBAttachments = uint8_t(bx::uint32_clamp(
						  glGet(GL_MAX_DRAW_BUFFERS)
						, 1
						, BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS)
						);
				}

//				if (s_extension[Extension::ARB_clip_control].m_supported)
//				{
//					GL_CHECK(glClipControl(GL_LOWER_LEFT, GL_ZERO_TO_ONE) );
//					g_caps.originBottomLeft = true;
//				}
//				else
				{
					g_caps.homogeneousDepth = true;
					g_caps.originBottomLeft = true;
				}

				m_vaoSupport = !BX_ENABLED(BX_PLATFORM_EMSCRIPTEN)
					&& (m_gles3
						|| s_extension[Extension::ARB_vertex_array_object].m_supported
						|| s_extension[Extension::OES_vertex_array_object].m_supported
						);

				if (m_vaoSupport)
				{
					GL_CHECK(glGenVertexArrays(1, &m_vao) );
					GL_CHECK(glBindVertexArray(m_vao) );
				}

				m_samplerObjectSupport = false
					|| m_gles3
					|| s_extension[Extension::ARB_sampler_objects].m_supported
					;

				m_shadowSamplersSupport = !!(BGFX_CONFIG_RENDERER_OPENGL || m_gles3)
					|| s_extension[Extension::EXT_shadow_samplers].m_supported
					;

				m_programBinarySupport = !BX_ENABLED(BX_PLATFORM_EMSCRIPTEN)
					&& (m_gles3
						|| s_extension[Extension::ARB_get_program_binary].m_supported
						|| s_extension[Extension::OES_get_program_binary].m_supported
						|| s_extension[Extension::IMG_shader_binary     ].m_supported
						);

				m_textureSwizzleSupport = false
					|| s_extension[Extension::ARB_texture_swizzle].m_supported
					|| s_extension[Extension::EXT_texture_swizzle].m_supported
					;

				m_depthTextureSupport = !!(BGFX_CONFIG_RENDERER_OPENGL || m_gles3)
					|| s_extension[Extension::ANGLE_depth_texture       ].m_supported
					|| s_extension[Extension::CHROMIUM_depth_texture    ].m_supported
					|| s_extension[Extension::GOOGLE_depth_texture      ].m_supported
					|| s_extension[Extension::OES_depth_texture         ].m_supported
					|| s_extension[Extension::MOZ_WEBGL_depth_texture   ].m_supported
					|| s_extension[Extension::WEBGL_depth_texture       ].m_supported
					|| s_extension[Extension::WEBKIT_WEBGL_depth_texture].m_supported
					;

				m_timerQuerySupport = false
					|| s_extension[Extension::ANGLE_timer_query       ].m_supported
					|| s_extension[Extension::ARB_timer_query         ].m_supported
					|| s_extension[Extension::EXT_disjoint_timer_query].m_supported
					|| s_extension[Extension::EXT_timer_query         ].m_supported
					;

				m_timerQuerySupport &= true
					&& NULL != glQueryCounter
					&& NULL != glGetQueryObjectiv
					&& NULL != glGetQueryObjectui64v
					;

				m_occlusionQuerySupport = false
					|| s_extension[Extension::ARB_occlusion_query        ].m_supported
					|| s_extension[Extension::ARB_occlusion_query2       ].m_supported
					|| s_extension[Extension::EXT_occlusion_query_boolean].m_supported
					|| s_extension[Extension::NV_occlusion_query         ].m_supported
					;

				m_occlusionQuerySupport &= true
					&& NULL != glGenQueries
					&& NULL != glDeleteQueries
					&& NULL != glBeginQuery
					&& NULL != glEndQuery
					;

				m_atocSupport = s_extension[Extension::ARB_multisample].m_supported;
				m_conservativeRasterSupport = s_extension[Extension::NV_conservative_raster].m_supported;

				m_imageLoadStoreSupport = false
					|| s_extension[Extension::ARB_shader_image_load_store].m_supported
					|| s_extension[Extension::EXT_shader_image_load_store].m_supported
					;

				g_caps.supported |= 0
					| (m_atocSupport               ? BGFX_CAPS_ALPHA_TO_COVERAGE      : 0)
					| (m_conservativeRasterSupport ? BGFX_CAPS_CONSERVATIVE_RASTER    : 0)
					| (m_occlusionQuerySupport     ? BGFX_CAPS_OCCLUSION_QUERY        : 0)
					| (m_depthTextureSupport       ? BGFX_CAPS_TEXTURE_COMPARE_LEQUAL : 0)
					| (computeSupport              ? BGFX_CAPS_COMPUTE                : 0)
					| (m_imageLoadStoreSupport     ? BGFX_CAPS_IMAGE_RW               : 0)
					;

				g_caps.supported |= m_glctx.getCaps();

				if (BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGLES) )
				{
					m_srgbWriteControlSupport = s_extension[Extension::EXT_sRGB_write_control].m_supported;

					m_borderColorSupport = s_extension[Extension::NV_texture_border_clamp].m_supported;
					s_textureAddress[BGFX_SAMPLER_U_BORDER>>BGFX_SAMPLER_U_SHIFT] = s_extension[Extension::NV_texture_border_clamp].m_supported
						? GL_CLAMP_TO_BORDER
						: GL_CLAMP_TO_EDGE
						;
				}

				if (s_extension[Extension::EXT_texture_filter_anisotropic].m_supported)
				{
					GL_CHECK(glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &m_maxAnisotropyDefault) );
				}

				if (s_extension[Extension::ARB_texture_multisample].m_supported
				||  s_extension[Extension::ANGLE_framebuffer_multisample].m_supported
				||  s_extension[Extension::EXT_multisampled_render_to_texture].m_supported)
				{
					GL_CHECK(glGetIntegerv(GL_MAX_SAMPLES, &m_maxMsaa) );
				}

#if BGFX_CONFIG_RENDERER_OPENGLES && (BGFX_CONFIG_RENDERER_OPENGLES < 30)
				if (!m_maxMsaa  && s_extension[Extension::IMG_multisampled_render_to_texture].m_supported)
				{
					GL_CHECK(glGetIntegerv(GL_MAX_SAMPLES_IMG, &m_maxMsaa) );
				}
#endif // BGFX_CONFIG_RENDERER_OPENGLES < 30

				if (s_extension[Extension::OES_read_format].m_supported
				&& (s_extension[Extension::IMG_read_format].m_supported	|| s_extension[Extension::EXT_read_format_bgra].m_supported) )
				{
					m_readPixelsFmt = GL_BGRA;
				}
				else
				{
					m_readPixelsFmt = GL_RGBA;
				}

				if (m_gles3)
				{
					g_caps.supported |= BGFX_CAPS_INSTANCING;
				}
				else
				{
					if (s_extension[Extension::ANGLE_instanced_arrays].m_supported
					||  s_extension[Extension::  ARB_instanced_arrays].m_supported
					||  s_extension[Extension::  EXT_instanced_arrays].m_supported
					|| (s_extension[Extension::   NV_instanced_arrays].m_supported && s_extension[Extension::NV_draw_instanced].m_supported)
					   )
					{
						if (NULL != glVertexAttribDivisor
						&&  NULL != glDrawArraysInstanced
						&&  NULL != glDrawElementsInstanced)
						{
							g_caps.supported |= BGFX_CAPS_INSTANCING;
						}
						else if (NULL != glVertexAttribDivisorNV
							 &&  NULL != glDrawArraysInstancedNV
							 &&  NULL != glDrawElementsInstancedNV)
						{
							glVertexAttribDivisor   = glVertexAttribDivisorNV;
							glDrawArraysInstanced   = glDrawArraysInstancedNV;
							glDrawElementsInstanced = glDrawElementsInstancedNV;

							g_caps.supported |= BGFX_CAPS_INSTANCING;
						}
					}

					if (0 == (g_caps.supported & BGFX_CAPS_INSTANCING) )
					{
						glVertexAttribDivisor   = stubVertexAttribDivisor;
						glDrawArraysInstanced   = stubDrawArraysInstanced;
						glDrawElementsInstanced = stubDrawElementsInstanced;
					}
				}

				g_caps.supported |= s_extension[Extension::ARB_shader_viewport_layer_array].m_supported
					? BGFX_CAPS_VIEWPORT_LAYER_ARRAY
					: 0
					;

				g_caps.supported |= BX_ENABLED(BX_PLATFORM_WINRT) ? BGFX_CAPS_TRANSPARENT_BACKBUFFER : 0;

				if (s_extension[Extension::ARB_debug_output].m_supported
				||  s_extension[Extension::KHR_debug].m_supported)
				{
					if (NULL != glDebugMessageControl
					&&  NULL != glDebugMessageInsert
					&&  NULL != glDebugMessageCallback
					&&  NULL != glGetDebugMessageLog)
					{
						GL_CHECK(glDebugMessageCallback(debugProcCb, NULL) );
						GL_CHECK(glDebugMessageControl(GL_DONT_CARE
							, GL_DONT_CARE
							, GL_DEBUG_SEVERITY_MEDIUM
							, 0
							, NULL
							, GL_TRUE
							) );
					}
				}

				if (NULL == glPushDebugGroup
				||  NULL == glPopDebugGroup)
				{
					glPushDebugGroup = stubPushDebugGroup;
					glPopDebugGroup  = stubPopDebugGroup;
				}

				if (s_extension[Extension::ARB_seamless_cube_map].m_supported)
				{
					GL_CHECK(glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS) );
				}

				if (NULL != glProvokingVertex
				&&  s_extension[Extension::ARB_provoking_vertex].m_supported)
				{
					GL_CHECK(glProvokingVertex(GL_FIRST_VERTEX_CONVENTION) );
				}

				if (NULL == glInsertEventMarker
				||  !s_extension[Extension::EXT_debug_marker].m_supported)
				{
					glInsertEventMarker = stubInsertEventMarker;
				}

				m_maxLabelLen = BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGLES >= 32) || BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGL >= 43) || s_extension[Extension::KHR_debug].m_supported ? uint16_t(glGet(GL_MAX_LABEL_LENGTH) ) : 0;

				setGraphicsDebuggerPresent(s_extension[Extension::EXT_debug_tool].m_supported);

				if (NULL == glObjectLabel)
				{
					glObjectLabel = stubObjectLabel;
				}

				if (NULL == glInvalidateFramebuffer)
				{
					glInvalidateFramebuffer = stubInvalidateFramebuffer;
				}

				if (NULL == glFramebufferTexture)
				{
					glFramebufferTexture = stubFramebufferTexture;
				}

				if (m_timerQuerySupport)
				{
					m_gpuTimer.create();
				}

				if (m_occlusionQuerySupport)
				{
					m_occlusionQuery.create();
				}

				// Init reserved part of view name.
				for (uint32_t ii = 0; ii < BGFX_CONFIG_MAX_VIEWS; ++ii)
				{
					bx::snprintf(s_viewName[ii], BGFX_CONFIG_MAX_VIEW_NAME_RESERVED+1, "%3d   ", ii);
				}

				m_needPresent = false;
			}

			return true;

		error:
			switch (errorState)
			{
			case ErrorState::Default:
				break;
			}

			m_glctx.destroy();

			unloadRenderDoc(m_renderdocdll);
			return false;
		}

		void shutdown()
		{
			if (m_vaoSupport)
			{
				GL_CHECK(glBindVertexArray(0) );
				GL_CHECK(glDeleteVertexArrays(1, &m_vao) );
				m_vao = 0;
			}

			captureFinish();

			invalidateCache();

			if (m_timerQuerySupport)
			{
				m_gpuTimer.destroy();
			}

			if (m_occlusionQuerySupport)
			{
				m_occlusionQuery.destroy();
			}

			destroyMsaaFbo();
			m_glctx.destroy();

			m_flip = false;

			unloadRenderDoc(m_renderdocdll);
		}

		RendererType::Enum getRendererType() const override
		{
			if (BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGL) )
			{
				return RendererType::OpenGL;
			}

			return RendererType::OpenGLES;
		}

		const char* getRendererName() const override
		{
			return BGFX_RENDERER_OPENGL_NAME;
		}

		bool isDeviceRemoved() override
		{
			return false;
		}

		void flip() override
		{
			if (m_flip)
			{
				for (uint32_t ii = 1, num = m_numWindows; ii < num; ++ii)
				{
					FrameBufferGL& frameBuffer = m_frameBuffers[m_windows[ii].idx];
					if (frameBuffer.m_needPresent)
					{
						m_glctx.swap(frameBuffer.m_swapChain);
						frameBuffer.m_needPresent = false;
					}
				}

				if (m_needPresent)
				{
					// Ensure the back buffer is bound as the source of the flip
					GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_backBufferFbo) );

					m_glctx.swap();
					m_needPresent = false;
				}
			}
		}

		void createIndexBuffer(IndexBufferHandle _handle, const Memory* _mem, uint16_t _flags) override
		{
			m_indexBuffers[_handle.idx].create(_mem->size, _mem->data, _flags);
		}

		void destroyIndexBuffer(IndexBufferHandle _handle) override
		{
			m_indexBuffers[_handle.idx].destroy();
		}

		void createVertexLayout(VertexLayoutHandle _handle, const VertexLayout& _layout) override
		{
			VertexLayout& layout = m_vertexLayouts[_handle.idx];
			bx::memCopy(&layout, &_layout, sizeof(VertexLayout) );
			dump(layout);
		}

		void destroyVertexLayout(VertexLayoutHandle /*_handle*/) override
		{
		}

		void createVertexBuffer(VertexBufferHandle _handle, const Memory* _mem, VertexLayoutHandle _layoutHandle, uint16_t _flags) override
		{
			m_vertexBuffers[_handle.idx].create(_mem->size, _mem->data, _layoutHandle, _flags);
		}

		void destroyVertexBuffer(VertexBufferHandle _handle) override
		{
			m_vertexBuffers[_handle.idx].destroy();
		}

		void createDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _size, uint16_t _flags) override
		{
			m_indexBuffers[_handle.idx].create(_size, NULL, _flags);
		}

		void updateDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _offset, uint32_t _size, const Memory* _mem) override
		{
			m_indexBuffers[_handle.idx].update(_offset, bx::uint32_min(_size, _mem->size), _mem->data);
		}

		void destroyDynamicIndexBuffer(IndexBufferHandle _handle) override
		{
			m_indexBuffers[_handle.idx].destroy();
		}

		void createDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _size, uint16_t _flags) override
		{
			VertexLayoutHandle layoutHandle = BGFX_INVALID_HANDLE;
			m_vertexBuffers[_handle.idx].create(_size, NULL, layoutHandle, _flags);
		}

		void updateDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _offset, uint32_t _size, const Memory* _mem) override
		{
			m_vertexBuffers[_handle.idx].update(_offset, bx::uint32_min(_size, _mem->size), _mem->data);
		}

		void destroyDynamicVertexBuffer(VertexBufferHandle _handle) override
		{
			m_vertexBuffers[_handle.idx].destroy();
		}

		void createShader(ShaderHandle _handle, const Memory* _mem) override
		{
			m_shaders[_handle.idx].create(_mem);
		}

		void destroyShader(ShaderHandle _handle) override
		{
			m_shaders[_handle.idx].destroy();
		}

		void createProgram(ProgramHandle _handle, ShaderHandle _vsh, ShaderHandle _fsh) override
		{
			ShaderGL dummyFragmentShader;
			m_program[_handle.idx].create(m_shaders[_vsh.idx], isValid(_fsh) ? m_shaders[_fsh.idx] : dummyFragmentShader);
		}

		void destroyProgram(ProgramHandle _handle) override
		{
			m_program[_handle.idx].destroy();
		}

		void* createTexture(TextureHandle _handle, const Memory* _mem, uint64_t _flags, uint8_t _skip) override
		{
			m_textures[_handle.idx].create(_mem, _flags, _skip);
			return NULL;
		}

		void updateTextureBegin(TextureHandle /*_handle*/, uint8_t /*_side*/, uint8_t /*_mip*/) override
		{
		}

		void updateTexture(TextureHandle _handle, uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem) override
		{
			m_textures[_handle.idx].update(_side, _mip, _rect, _z, _depth, _pitch, _mem);
		}

		void updateTextureEnd() override
		{
		}

		void readTexture(TextureHandle _handle, void* _data, uint8_t _mip) override
		{
			if (m_readBackSupported)
			{
				const TextureGL& texture = m_textures[_handle.idx];
				const bool compressed    = bimg::isCompressed(bimg::TextureFormat::Enum(texture.m_textureFormat) );

				GL_CHECK(glBindTexture(texture.m_target, texture.m_id) );

				if (compressed)
				{
					GL_CHECK(glGetCompressedTexImage(texture.m_target
						, _mip
						, _data
						) );
				}
				else
				{
					GL_CHECK(glGetTexImage(texture.m_target
						, _mip
						, texture.m_fmt
						, texture.m_type
						, _data
						) );
				}

				GL_CHECK(glBindTexture(texture.m_target, 0) );
			}
			else if (BX_ENABLED(BGFX_GL_CONFIG_TEXTURE_READ_BACK_EMULATION) )
			{
				const TextureGL& texture = m_textures[_handle.idx];
				const bool compressed    = bimg::isCompressed(bimg::TextureFormat::Enum(texture.m_textureFormat) );

				if (!compressed)
				{
					Attachment at[1];
					at[0].init(_handle);

					FrameBufferGL frameBuffer;
					frameBuffer.create(BX_COUNTOF(at), at);
					GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer.m_fbo[0]) );
					GL_CHECK(glFramebufferTexture2D(
						  GL_FRAMEBUFFER
						, GL_COLOR_ATTACHMENT0
						, GL_TEXTURE_2D
						, texture.m_id
						, at[0].mip
						) );

					if (BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGL) || m_gles3)
					{
						GL_CHECK(glReadBuffer(GL_COLOR_ATTACHMENT0) );
					}

					if (GL_FRAMEBUFFER_COMPLETE == glCheckFramebufferStatus(GL_FRAMEBUFFER) )
					{
						GL_CHECK(glReadPixels(
							  0
							, 0
							, texture.m_width
							, texture.m_height
							, m_readPixelsFmt
							, GL_UNSIGNED_BYTE
							, _data
							) );
					}

					frameBuffer.destroy();
				}
			}
		}

		void resizeTexture(TextureHandle _handle, uint16_t _width, uint16_t _height, uint8_t _numMips, uint16_t _numLayers) override
		{
			TextureGL& texture = m_textures[_handle.idx];

			uint32_t size = sizeof(uint32_t) + sizeof(TextureCreate);
			const Memory* mem = alloc(size);

			bx::StaticMemoryBlockWriter writer(mem->data, mem->size);
			uint32_t magic = BGFX_CHUNK_MAGIC_TEX;
			bx::write(&writer, magic, bx::ErrorAssert{});

			TextureCreate tc;
			tc.m_width     = _width;
			tc.m_height    = _height;
			tc.m_depth     = 0;
			tc.m_numLayers = _numLayers;
			tc.m_numMips   = _numMips;
			tc.m_format    = TextureFormat::Enum(texture.m_requestedFormat);
			tc.m_cubeMap   = false;
			tc.m_mem       = NULL;
			bx::write(&writer, tc, bx::ErrorAssert{});

			texture.destroy();
			texture.create(mem, texture.m_flags, 0);

			release(mem);
		}

		void overrideInternal(TextureHandle _handle, uintptr_t _ptr) override
		{
			m_textures[_handle.idx].overrideInternal(_ptr);
		}

		uintptr_t getInternal(TextureHandle _handle) override
		{
			return uintptr_t(m_textures[_handle.idx].m_id);
		}

		void destroyTexture(TextureHandle _handle) override
		{
			m_textures[_handle.idx].destroy();
		}

		void createFrameBuffer(FrameBufferHandle _handle, uint8_t _num, const Attachment* _attachment) override
		{
			m_frameBuffers[_handle.idx].create(_num, _attachment);
		}

		void createFrameBuffer(FrameBufferHandle _handle, void* _nwh, uint32_t _width, uint32_t _height, TextureFormat::Enum _format, TextureFormat::Enum _depthFormat) override
		{
			uint16_t denseIdx = m_numWindows++;
			m_windows[denseIdx] = _handle;
			m_frameBuffers[_handle.idx].create(denseIdx, _nwh, _width, _height, _format, _depthFormat);
		}

		void destroyFrameBuffer(FrameBufferHandle _handle) override
		{
			uint16_t denseIdx = m_frameBuffers[_handle.idx].destroy();
			if (UINT16_MAX != denseIdx)
			{
				--m_numWindows;
				if (m_numWindows > 1)
				{
					FrameBufferHandle handle = m_windows[m_numWindows];
					m_windows[m_numWindows]  = {kInvalidHandle};
					if (m_numWindows != denseIdx)
					{
						m_windows[denseIdx] = handle;
						m_frameBuffers[handle.idx].m_denseIdx = denseIdx;
					}
				}
			}
		}

		void createUniform(UniformHandle _handle, UniformType::Enum _type, uint16_t _num, const char* _name) override
		{
			if (NULL != m_uniforms[_handle.idx])
			{
				bx::free(g_allocator, m_uniforms[_handle.idx]);
			}

			uint32_t size = g_uniformTypeSize[_type]*_num;
			void* data = bx::alloc(g_allocator, size);
			bx::memSet(data, 0, size);
			m_uniforms[_handle.idx] = data;
			m_uniformReg.add(_handle, _name);
		}

		void destroyUniform(UniformHandle _handle) override
		{
			bx::free(g_allocator, m_uniforms[_handle.idx]);
			m_uniforms[_handle.idx] = NULL;
			m_uniformReg.remove(_handle);
		}

		void requestScreenShot(FrameBufferHandle _handle, const char* _filePath) override
		{
			SwapChainGL* swapChain = NULL;
			uint32_t width  = m_resolution.width;
			uint32_t height = m_resolution.height;

			if (isValid(_handle) )
			{
				const FrameBufferGL& frameBuffer = m_frameBuffers[_handle.idx];
				swapChain = frameBuffer.m_swapChain;
				width  = frameBuffer.m_width;
				height = frameBuffer.m_height;
			}

			m_glctx.makeCurrent(swapChain);

			uint32_t length = width*height*4;
			uint8_t* data = (uint8_t*)bx::alloc(g_allocator, length);

			GL_CHECK(glReadPixels(0
				, 0
				, width
				, height
				, m_readPixelsFmt
				, GL_UNSIGNED_BYTE
				, data
				) );

			if (GL_RGBA == m_readPixelsFmt)
			{
				bimg::imageSwizzleBgra8(data, width*4, width, height, data, width*4);
			}

			g_callback->screenShot(_filePath
				, width
				, height
				, width*4
				, data
				, length
				, true
				);
			bx::free(g_allocator, data);
		}

		void updateViewName(ViewId _id, const char* _name) override
		{
			bx::strCopy(&s_viewName[_id][BGFX_CONFIG_MAX_VIEW_NAME_RESERVED]
				, BX_COUNTOF(s_viewName[0])-BGFX_CONFIG_MAX_VIEW_NAME_RESERVED
				, _name
				);
		}

		void updateUniform(uint16_t _loc, const void* _data, uint32_t _size) override
		{
			bx::memCopy(m_uniforms[_loc], _data, _size);
		}

		void invalidateOcclusionQuery(OcclusionQueryHandle _handle) override
		{
			m_occlusionQuery.invalidate(_handle);
		}

		void setMarker(const char* _marker, uint16_t _len) override
		{
			GL_CHECK(glInsertEventMarker(_len, _marker) );
		}

		virtual void setName(Handle _handle, const char* _name, uint16_t _len) override
		{
			uint16_t len = bx::min(_len, m_maxLabelLen);

			switch (_handle.type)
			{
			case Handle::IndexBuffer:
				GL_CHECK(glObjectLabel(GL_BUFFER, m_indexBuffers[_handle.idx].m_id, len, _name) );
				break;

			case Handle::Shader:
				GL_CHECK(glObjectLabel(GL_SHADER, m_shaders[_handle.idx].m_id, len, _name) );
				break;

			case Handle::Texture:
				{
					GLint id = m_textures[_handle.idx].m_id;
					if (0 != id)
					{
						GL_CHECK(glObjectLabel(GL_TEXTURE, id, len, _name) );
					}
					else
					{
						GL_CHECK(glObjectLabel(GL_RENDERBUFFER, m_textures[_handle.idx].m_rbo, len, _name) );
					}
				}
				break;

			case Handle::VertexBuffer:
				GL_CHECK(glObjectLabel(GL_BUFFER, m_vertexBuffers[_handle.idx].m_id, len, _name) );
				break;

			default:
				BX_ASSERT(false, "Invalid handle type?! %d", _handle.type);
				break;
			}
		}

		void submitBlit(BlitState& _bs, uint16_t _view);

		void submit(Frame* _render, ClearQuad& _clearQuad, TextVideoMemBlitter& _textVideoMemBlitter) override;

		void blitSetup(TextVideoMemBlitter& _blitter) override
		{
			uint32_t width  = m_resolution.width;
			uint32_t height = m_resolution.height;

			GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_backBufferFbo) );
			GL_CHECK(glViewport(0, 0, width, height) );

			GL_CHECK(glDisable(GL_SCISSOR_TEST) );
			GL_CHECK(glDisable(GL_STENCIL_TEST) );
			GL_CHECK(glDisable(GL_DEPTH_TEST) );
			GL_CHECK(glDepthFunc(GL_ALWAYS) );
			GL_CHECK(glDisable(GL_CULL_FACE) );
			GL_CHECK(glDisable(GL_BLEND) );
			GL_CHECK(glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE) );

			ProgramGL& program = m_program[_blitter.m_program.idx];
			setProgram(program.m_id);
			setUniform1i(program.m_sampler[0], 0);

			float proj[16];
			bx::mtxOrtho(proj, 0.0f, (float)width, (float)height, 0.0f, 0.0f, 1000.0f, 0.0f, g_caps.homogeneousDepth);

			setUniformMatrix4fv(program.m_predefined[0].m_loc
				, 1
				, GL_FALSE
				, proj
				);

			GL_CHECK(glActiveTexture(GL_TEXTURE0) );
			GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_textures[_blitter.m_texture.idx].m_id) );

			if (m_samplerObjectSupport)
			{
				GL_CHECK(glBindSampler(0, 0) );
			}
		}

		void blitRender(TextVideoMemBlitter& _blitter, uint32_t _numIndices) override
		{
			const uint32_t numVertices = _numIndices*4/6;
			if (0 < numVertices)
			{
				m_indexBuffers[_blitter.m_ib->handle.idx].update(0, _numIndices*2, _blitter.m_ib->data);
				m_vertexBuffers[_blitter.m_vb->handle.idx].update(0, numVertices*_blitter.m_layout.m_stride, _blitter.m_vb->data);

				VertexBufferGL& vb = m_vertexBuffers[_blitter.m_vb->handle.idx];
				GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vb.m_id) );

				IndexBufferGL& ib = m_indexBuffers[_blitter.m_ib->handle.idx];
				GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib.m_id) );

				ProgramGL& program = m_program[_blitter.m_program.idx];
				program.bindAttributesBegin();
				program.bindAttributes(_blitter.m_layout, 0);
				program.bindAttributesEnd();

				GL_CHECK(glDrawElements(GL_TRIANGLES
					, _numIndices
					, GL_UNSIGNED_SHORT
					, (void*)0
					) );
			}
		}

		void updateResolution(const Resolution& _resolution)
		{
			m_maxAnisotropy = !!(_resolution.reset & BGFX_RESET_MAXANISOTROPY)
				? m_maxAnisotropyDefault
				: 0.0f
				;

			if (s_extension[Extension::ARB_depth_clamp].m_supported)
			{
				if (!!(_resolution.reset & BGFX_RESET_DEPTH_CLAMP) )
				{
					GL_CHECK(glEnable(GL_DEPTH_CLAMP) );
				}
				else
				{
					GL_CHECK(glDisable(GL_DEPTH_CLAMP) );
				}
			}

			const uint32_t maskFlags = ~(0
				| BGFX_RESET_MAXANISOTROPY
				| BGFX_RESET_DEPTH_CLAMP
				| BGFX_RESET_SUSPEND
				);

			if (m_resolution.width            !=  _resolution.width
			||  m_resolution.height           !=  _resolution.height
			|| (m_resolution.reset&maskFlags) != (_resolution.reset&maskFlags) )
			{
				uint32_t flags = _resolution.reset & (~BGFX_RESET_INTERNAL_FORCE);

				m_resolution = _resolution;
				m_resolution.reset = flags;

				m_textVideoMem.resize(false, _resolution.width, _resolution.height);
				m_textVideoMem.clear();

				setRenderContextSize(m_resolution.width
						, m_resolution.height
						, flags
						);
				updateCapture();

				for (uint32_t ii = 0; ii < BX_COUNTOF(m_frameBuffers); ++ii)
				{
					m_frameBuffers[ii].postReset();
				}

				m_currentFbo = 0;

				GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_currentFbo) );
			}
		}

		void setShaderUniform4f(uint8_t /*_flags*/, uint32_t _regIndex, const void* _val, uint32_t _numRegs)
		{
			setUniform4fv(_regIndex
				, _numRegs
				, (const GLfloat*)_val
				);
		}

		void setShaderUniform4x4f(uint8_t /*_flags*/, uint32_t _regIndex, const void* _val, uint32_t _numRegs)
		{
			setUniformMatrix4fv(_regIndex
				, _numRegs
				, GL_FALSE
				, (const GLfloat*)_val
				);
		}

		uint32_t setFrameBuffer(FrameBufferHandle _fbh, uint32_t _height, uint16_t _discard = BGFX_CLEAR_NONE, bool _msaa = true)
		{
			if (isValid(m_fbh)
			&&  m_fbh.idx != _fbh.idx)
			{
				FrameBufferGL& frameBuffer = m_frameBuffers[m_fbh.idx];
				frameBuffer.resolve();

				if (BGFX_CLEAR_NONE != m_fbDiscard)
				{
					frameBuffer.discard(m_fbDiscard);
					m_fbDiscard = BGFX_CLEAR_NONE;
				}
			}

			m_glctx.makeCurrent(NULL);

			if (!isValid(_fbh) )
			{
				m_needPresent |= true;

				m_currentFbo = m_msaaBackBufferFbo;
			}
			else
			{
				FrameBufferGL& frameBuffer = m_frameBuffers[_fbh.idx];
				_height = frameBuffer.m_height;
				if (UINT16_MAX != frameBuffer.m_denseIdx)
				{
					m_glctx.makeCurrent(frameBuffer.m_swapChain);
					GL_CHECK(glFrontFace(GL_CW) );

					frameBuffer.m_needPresent = true;
					m_currentFbo = 0;
				}
				else
				{
					m_glctx.makeCurrent(NULL);
					m_currentFbo = frameBuffer.m_fbo[0];
				}
			}

			if (0 != m_vao)
			{
				GL_CHECK(glDeleteVertexArrays(1, &m_vao) );
				GL_CHECK(glGenVertexArrays(1, &m_vao) );
				GL_CHECK(glBindVertexArray(m_vao) );
			}

			if (m_srgbWriteControlSupport)
			{
				if (0 == m_currentFbo)
				{
					if (0 != (m_resolution.reset & BGFX_RESET_SRGB_BACKBUFFER) )
					{
						GL_CHECK(glEnable(GL_FRAMEBUFFER_SRGB) );
					}
					else
					{
						GL_CHECK(glDisable(GL_FRAMEBUFFER_SRGB) );
					}
				}
				else
				{
					// actual sRGB write/blending determined by FBO's color attachments format
					GL_CHECK(glEnable(GL_FRAMEBUFFER_SRGB) );
				}
			}

			GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_currentFbo) );

			m_fbh       = _fbh;
			m_fbDiscard = _discard;
			m_rtMsaa    = _msaa;

			return _height;
		}

		uint32_t getNumRt() const
		{
			if (isValid(m_fbh) )
			{
				const FrameBufferGL& frameBuffer = m_frameBuffers[m_fbh.idx];
				return frameBuffer.m_num;
			}

			return 1;
		}

		void createMsaaFbo(uint32_t _width, uint32_t _height, uint32_t _msaa)
		{
			if (0 == m_msaaBackBufferFbo // iOS
			&&  1 < _msaa
			&& !m_glctx.m_msaaContext)
			{
				GLenum storageFormat = m_resolution.reset & BGFX_RESET_SRGB_BACKBUFFER
					? GL_SRGB8_ALPHA8
					: GL_RGBA8
					;

				GLenum attachment = BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGL) || m_gles3
					? GL_DEPTH_STENCIL_ATTACHMENT
					: GL_DEPTH_ATTACHMENT
					;

				GL_CHECK(glGenFramebuffers(1, &m_msaaBackBufferFbo) );
				GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_msaaBackBufferFbo) );

				if (m_gles3)
				{
					GL_CHECK(glGenTextures(BX_COUNTOF(m_msaaBackBufferTextures), m_msaaBackBufferTextures) );
					GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_msaaBackBufferTextures[0]) );
					GL_CHECK(glTexStorage2D(GL_TEXTURE_2D, 1, storageFormat, _width, _height) );
					GL_CHECK(glFramebufferTexture2DMultisampleEXT(
						  GL_FRAMEBUFFER
						, GL_COLOR_ATTACHMENT0
						, GL_TEXTURE_2D
						, m_msaaBackBufferTextures[0]
						, 0
						, _msaa
						) );
					GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_msaaBackBufferFbo) );

					GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_msaaBackBufferTextures[1]) );
					GL_CHECK(glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, _width, _height) );
					GL_CHECK(glFramebufferTexture2DMultisampleEXT(
						  GL_FRAMEBUFFER
						, attachment
						, GL_TEXTURE_2D
						, m_msaaBackBufferTextures[1]
						, 0
						, _msaa
						) );
					GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0) );

					BX_ASSERT(GL_FRAMEBUFFER_COMPLETE == glCheckFramebufferStatus(GL_FRAMEBUFFER)
						, "glCheckFramebufferStatus failed 0x%08x"
						, glCheckFramebufferStatus(GL_FRAMEBUFFER)
						);

					if (0 == m_msaaBlitProgram)
					{
						static const char* msaa_blit_vs =
							R"(#version 300 es
							precision highp float;
							out vec2 UV;
							void main()
							{
								float x = -1.0 + float( (gl_VertexID & 1) << 2);
								float y = -1.0 + float( (gl_VertexID & 2) << 1);
								gl_Position = vec4(x, y, 0, 1);
								UV = vec2(gl_Position.x + 1.0, gl_Position.y + 1.0) * 0.5;
							}
						)";

						static const char* msaa_blit_fs =
							R"(#version 300 es
							precision mediump float;
							in vec2 UV;
							uniform sampler2D msaaTexture;
							out vec4 oFragColor;
							void main()
							{
								oFragColor = texture(msaaTexture, UV);
							}
						)";

						const GLchar *const vs = msaa_blit_vs;
						const GLchar *const fs = msaa_blit_fs;

						GLuint shader_vs = glCreateShader(GL_VERTEX_SHADER);
						{
							BX_WARN(0 != shader_vs, "Failed to create msaa Blit Vertex shader.");
							GL_CHECK(glShaderSource(shader_vs, 1, &vs, NULL) );
							GL_CHECK(glCompileShader(shader_vs) );

							GLint compiled = 0;
							GL_CHECK(glGetShaderiv(shader_vs, GL_COMPILE_STATUS, &compiled) );
							BX_WARN(0 == shader_vs, "Unable to compile msaa Blit Vertex shader.");
						}

						GLuint shader_fs = glCreateShader(GL_FRAGMENT_SHADER);
						{
							BX_WARN(0 != shader_fs, "Failed to create msaa Blit Fragment shader.");
							GL_CHECK(glShaderSource(shader_fs, 1, &fs, NULL) );
							GL_CHECK(glCompileShader(shader_fs) );

							GLint compiled = 0;
							GL_CHECK(glGetShaderiv(shader_fs, GL_COMPILE_STATUS, &compiled) );
							BX_WARN(0 == shader_vs, "Unable to compile msaa Blit Fragment shader.");
						}

						m_msaaBlitProgram = glCreateProgram();

						if (m_msaaBlitProgram)
						{
							GL_CHECK(glAttachShader(m_msaaBlitProgram, shader_vs) );
							GL_CHECK(glAttachShader(m_msaaBlitProgram, shader_fs) );
							GL_CHECK(glLinkProgram(m_msaaBlitProgram) );

							GLint linked = 0;
							GL_CHECK(glGetProgramiv(m_msaaBlitProgram, GL_LINK_STATUS, &linked) );

							if (0 == linked)
							{
								char log[1024];
								GL_CHECK(glGetProgramInfoLog(
									  m_msaaBlitProgram
									, sizeof(log)
									, NULL
									, log
									) );
								BX_TRACE("%d: %s", linked, log);
							}

							GL_CHECK(glDetachShader(m_msaaBlitProgram, shader_vs) );
							GL_CHECK(glDeleteShader(shader_vs) );

							GL_CHECK(glDetachShader(m_msaaBlitProgram, shader_fs) );
							GL_CHECK(glDeleteShader(shader_fs) );
						}
					}
				}
				else
				{
					GL_CHECK(glGenRenderbuffers(BX_COUNTOF(m_msaaBackBufferRbos), m_msaaBackBufferRbos) );

					GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, m_msaaBackBufferRbos[0]) );
					GL_CHECK(glRenderbufferStorageMultisample(
						  GL_RENDERBUFFER
						, _msaa
						, storageFormat
						, _width
						, _height
						) );

					GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, m_msaaBackBufferRbos[1]) );
					GL_CHECK(glRenderbufferStorageMultisample(
						  GL_RENDERBUFFER
						, _msaa
						, GL_DEPTH24_STENCIL8
						, _width
						, _height
						) );

					GL_CHECK(glFramebufferRenderbuffer(
						  GL_FRAMEBUFFER
						, GL_COLOR_ATTACHMENT0
						, GL_RENDERBUFFER
						, m_msaaBackBufferRbos[0]
						) );
					GL_CHECK(glFramebufferRenderbuffer(
						  GL_FRAMEBUFFER
						, attachment
						, GL_RENDERBUFFER
						, m_msaaBackBufferRbos[1]
						) );

					BX_ASSERT(GL_FRAMEBUFFER_COMPLETE ==  glCheckFramebufferStatus(GL_FRAMEBUFFER)
						, "glCheckFramebufferStatus failed 0x%08x"
						, glCheckFramebufferStatus(GL_FRAMEBUFFER)
						);
				}
			}
		}

		void destroyMsaaFbo()
		{
			if (m_backBufferFbo != m_msaaBackBufferFbo // iOS
			&&  0 != m_msaaBackBufferFbo)
			{
				GL_CHECK(glDeleteFramebuffers(1, &m_msaaBackBufferFbo) );
				m_msaaBackBufferFbo = 0;

				if (m_gles3)
				{
					if (0 != m_msaaBackBufferTextures[0])
					{
						GL_CHECK(glDeleteTextures(BX_COUNTOF(m_msaaBackBufferTextures), m_msaaBackBufferTextures) );
						m_msaaBackBufferTextures[0] = 0;
						m_msaaBackBufferTextures[1] = 0;
					}
					if (0 != m_msaaBlitProgram)
					{
						GL_CHECK(glDeleteProgram(m_msaaBlitProgram) );
						m_msaaBlitProgram = 0;
					}
				}
				else
				{
					if (0 != m_msaaBackBufferRbos[0])
					{
						GL_CHECK(glDeleteRenderbuffers(BX_COUNTOF(m_msaaBackBufferRbos), m_msaaBackBufferRbos) );
						m_msaaBackBufferRbos[0] = 0;
						m_msaaBackBufferRbos[1] = 0;
					}
				}
			}
		}

		void blitMsaaFbo()
		{
			if (m_backBufferFbo != m_msaaBackBufferFbo // iOS
			&&  0 != m_msaaBackBufferFbo)
			{
				GL_CHECK(glDisable(GL_SCISSOR_TEST) );
				GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_backBufferFbo) );
				GL_CHECK(glBindFramebuffer(GL_READ_FRAMEBUFFER, m_msaaBackBufferFbo) );
				GL_CHECK(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0) );

				const uint32_t width  = m_resolution.width;
				const uint32_t height = m_resolution.height;
				const GLenum filter = BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGL) || !m_gles3
					? GL_NEAREST
					: GL_LINEAR
					;

				if (m_gles3)
				{
					GL_CHECK(glUseProgram(m_msaaBlitProgram) );
					GL_CHECK(glActiveTexture(GL_TEXTURE0) );
					GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_msaaBackBufferTextures[0]) );
					GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3) );
				}
				else
				{
					GL_CHECK(glBlitFramebuffer(
						  0
						, 0
						, width
						, height
						, 0
						, 0
						, width
						, height
						, GL_COLOR_BUFFER_BIT
						, filter
						) );
				}

				GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_backBufferFbo) );
			}
		}

		void setRenderContextSize(uint32_t _width, uint32_t _height, uint32_t _flags = 0)
		{
			if (!m_glctx.isValid() )
			{
				m_glctx.create(_width, _height, _flags);
			}
			else
			{
				destroyMsaaFbo();

				m_glctx.resize(_width, _height, _flags);

				uint32_t msaa = (_flags&BGFX_RESET_MSAA_MASK)>>BGFX_RESET_MSAA_SHIFT;
				msaa = bx::uint32_min(m_maxMsaa, msaa == 0 ? 0 : 1<<msaa);

				createMsaaFbo(_width, _height, msaa);
			}

			m_flip = true;
		}

		void invalidateCache()
		{
			if (m_samplerObjectSupport)
			{
				m_samplerStateCache.invalidate();
			}
		}

		void setSamplerState(uint32_t _stage, uint32_t _numMips, uint32_t _flags, const float _rgba[4])
		{
			BX_ASSERT(m_samplerObjectSupport, "Cannot use Sampler Objects");

			if (0 == (BGFX_SAMPLER_INTERNAL_DEFAULT & _flags) )
			{
				const uint32_t index = (_flags & BGFX_SAMPLER_BORDER_COLOR_MASK) >> BGFX_SAMPLER_BORDER_COLOR_SHIFT;

				_flags &= ~BGFX_SAMPLER_RESERVED_MASK;
				_flags &= BGFX_SAMPLER_BITS_MASK;
				_flags |= _numMips<<BGFX_SAMPLER_RESERVED_SHIFT;

				GLuint sampler;

				bool hasBorderColor = false;
				bx::HashMurmur2A murmur;
				uint32_t hash;

				murmur.begin();
				murmur.add(_flags);
				if (!needBorderColor(_flags) )
				{
					murmur.add(-1);
					hash = murmur.end();

					sampler = m_samplerStateCache.find(hash);
				}
				else
				{
					murmur.add(index);
					hash = murmur.end();

					if (NULL != _rgba)
					{
						hasBorderColor = true;
						sampler = UINT32_MAX;
					}
					else
					{
						sampler = m_samplerStateCache.find(hash);
					}
				}

				if (UINT32_MAX == sampler)
				{
					sampler = m_samplerStateCache.add(hash);

					GL_CHECK(glSamplerParameteri(sampler
						, GL_TEXTURE_WRAP_S
						, s_textureAddress[(_flags&BGFX_SAMPLER_U_MASK)>>BGFX_SAMPLER_U_SHIFT]
						) );
					GL_CHECK(glSamplerParameteri(sampler
						, GL_TEXTURE_WRAP_T
						, s_textureAddress[(_flags&BGFX_SAMPLER_V_MASK)>>BGFX_SAMPLER_V_SHIFT]
						) );
					GL_CHECK(glSamplerParameteri(sampler
						, GL_TEXTURE_WRAP_R
						, s_textureAddress[(_flags&BGFX_SAMPLER_W_MASK)>>BGFX_SAMPLER_W_SHIFT]
						) );

					GLenum minFilter;
					GLenum magFilter;
					getFilters(_flags, 1 < _numMips, magFilter, minFilter);
					GL_CHECK(glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, magFilter) );
					GL_CHECK(glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, minFilter) );

					if (BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGL) )
					{
						GL_CHECK(glSamplerParameterf(sampler, GL_TEXTURE_LOD_BIAS, float(BGFX_CONFIG_MIP_LOD_BIAS) ) );
					}

					if (m_borderColorSupport
					&&  hasBorderColor)
					{
						GL_CHECK(glSamplerParameterfv(sampler, GL_TEXTURE_BORDER_COLOR, _rgba) );
					}

					if (0 != (_flags & (BGFX_SAMPLER_MIN_ANISOTROPIC|BGFX_SAMPLER_MAG_ANISOTROPIC) )
					&&  0.0f < m_maxAnisotropy)
					{
						GL_CHECK(glSamplerParameterf(sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT, m_maxAnisotropy) );
					}

					if (m_gles3
					||  m_shadowSamplersSupport)
					{
						const uint32_t cmpFunc = (_flags&BGFX_SAMPLER_COMPARE_MASK)>>BGFX_SAMPLER_COMPARE_SHIFT;
						if (0 == cmpFunc)
						{
							GL_CHECK(glSamplerParameteri(sampler, GL_TEXTURE_COMPARE_MODE, GL_NONE) );
						}
						else
						{
							GL_CHECK(glSamplerParameteri(sampler, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE) );
							GL_CHECK(glSamplerParameteri(sampler, GL_TEXTURE_COMPARE_FUNC, s_cmpFunc[cmpFunc]) );
						}
					}
				}

				GL_CHECK(glBindSampler(_stage, sampler) );
			}
			else
			{
				GL_CHECK(glBindSampler(_stage, 0) );
			}
		}

		bool isVisible(Frame* _render, OcclusionQueryHandle _handle, bool _visible)
		{
			m_occlusionQuery.resolve(_render);
			return _visible == (0 != _render->m_occlusion[_handle.idx]);
		}

		void updateCapture()
		{
			if (m_resolution.reset&BGFX_RESET_CAPTURE)
			{
				m_captureSize = m_resolution.width*m_resolution.height*4;
				m_capture = bx::realloc(g_allocator, m_capture, m_captureSize);
				g_callback->captureBegin(m_resolution.width, m_resolution.height, m_resolution.width*4, TextureFormat::BGRA8, true);
			}
			else
			{
				captureFinish();
			}
		}

		void capture()
		{
			if (NULL != m_capture)
			{
				GL_CHECK(glReadPixels(0
					, 0
					, m_resolution.width
					, m_resolution.height
					, m_readPixelsFmt
					, GL_UNSIGNED_BYTE
					, m_capture
					) );

				if (GL_RGBA == m_readPixelsFmt)
				{
					bimg::imageSwizzleBgra8(
						  m_capture
						, m_resolution.width*4
						, m_resolution.width
						, m_resolution.height
						, m_capture
						, m_resolution.width*4
						);
				}

				g_callback->captureFrame(m_capture, m_captureSize);
			}
		}

		void captureFinish()
		{
			if (NULL != m_capture)
			{
				g_callback->captureEnd();
				bx::free(g_allocator, m_capture);
				m_capture = NULL;
				m_captureSize = 0;
			}
		}

		bool programFetchFromCache(GLuint programId, uint64_t _id)
		{
			_id ^= m_hash;

			bool cached = false;

			if (m_programBinarySupport)
			{
				uint32_t length = g_callback->cacheReadSize(_id);
				cached = length > 0;

				if (cached)
				{
					void* data = bx::alloc(g_allocator, length);
					if (g_callback->cacheRead(_id, data, length) )
					{
						bx::Error err;
						bx::MemoryReader reader(data, length);

						GLenum format;
						bx::read(&reader, format, &err);

						GL_CHECK(glProgramBinary(programId, format, reader.getDataPtr(), (GLsizei)reader.remaining() ) );
					}

					bx::free(g_allocator, data);
				}

#if BGFX_CONFIG_RENDERER_OPENGL
				GL_CHECK(glProgramParameteri(programId, GL_PROGRAM_BINARY_RETRIEVABLE_HINT, GL_TRUE) );
#endif // BGFX_CONFIG_RENDERER_OPENGL
			}

			return cached;
		}

		void programCache(GLuint programId, uint64_t _id)
		{
			_id ^= m_hash;

			if (m_programBinarySupport)
			{
				GLint programLength;
				GLenum format;
				GL_CHECK(glGetProgramiv(programId, GL_PROGRAM_BINARY_LENGTH, &programLength) );

				if (0 < programLength)
				{
					uint32_t length = programLength + 4;
					uint8_t* data = (uint8_t*)bx::alloc(g_allocator, length);
					GL_CHECK(glGetProgramBinary(programId, programLength, NULL, &format, &data[4]) );
					*(uint32_t*)data = format;

					g_callback->cacheWrite(_id, data, length);

					bx::free(g_allocator, data);
				}
			}
		}

		void commit(UniformBuffer& _uniformBuffer)
		{
			_uniformBuffer.reset();

			for (;;)
			{
				uint32_t opcode = _uniformBuffer.read();

				if (UniformType::End == opcode)
				{
					break;
				}

				UniformType::Enum type;
				uint16_t ignore;
				uint16_t num;
				uint16_t copy;
				UniformBuffer::decodeOpcode(opcode, type, ignore, num, copy);

				const char* data;
				if (copy)
				{
					data = _uniformBuffer.read(g_uniformTypeSize[type]*num);
				}
				else
				{
					UniformHandle handle;
					bx::memCopy(&handle, _uniformBuffer.read(sizeof(UniformHandle) ), sizeof(UniformHandle) );
					data = (const char*)m_uniforms[handle.idx];
				}

				uint32_t loc = _uniformBuffer.read();

				switch (type)
				{
#if BX_PLATFORM_EMSCRIPTEN
				// For WebAssembly the array forms glUniform1iv/glUniform4fv are much slower compared to glUniform1i/glUniform4f
				// since they need to marshal an array over from Wasm to JS, so optimize the case when there is exactly one
				// uniform to upload.
				case UniformType::Sampler:
					if (num > 1)
					{
						setUniform1iv(loc, num, (int32_t*)data);
					}
					else
					{
						setUniform1i(loc, *(int32_t*)data);
					}
					break;

				case UniformType::Vec4:
					if (num > 1)
					{
						setUniform4fv(loc, num, (float*)data);
					}
					else
					{
						float* vec4 = (float*)data;
						setUniform4f(loc, vec4[0], vec4[1], vec4[2], vec4[3]);
					}
					break;
#else
				case UniformType::Sampler:
					setUniform1iv(loc, num, (int32_t*)data);
					break;

				case UniformType::Vec4:
					setUniform4fv(loc, num, (float*)data);
					break;
#endif // BX_PLATFORM_EMSCRIPTEN

				case UniformType::Mat3:
					setUniformMatrix3fv(loc, num, GL_FALSE, (float*)data);
					break;

				case UniformType::Mat4:
					setUniformMatrix4fv(loc, num, GL_FALSE, (float*)data);
					break;

				case UniformType::End:
					break;

				default:
					BX_TRACE("%4d: INVALID 0x%08x, t %d, l %d, n %d, c %d", _uniformBuffer.getPos(), opcode, type, loc, num, copy);
					break;
				}
			}
		}

		void clearQuad(ClearQuad& _clearQuad, const Rect& _rect, const Clear& _clear, uint32_t _height, const float _palette[][4])
		{
			uint32_t numMrt = 1;
			FrameBufferHandle fbh = m_fbh;
			if (isValid(fbh) )
			{
				const FrameBufferGL& fb = m_frameBuffers[fbh.idx];
				numMrt = bx::uint32_max(1, fb.m_num);
			}

			if (1 == numMrt)
			{
				GLuint flags = 0;
				if (BGFX_CLEAR_COLOR & _clear.m_flags)
				{
					if (BGFX_CLEAR_COLOR_USE_PALETTE & _clear.m_flags)
					{
						uint8_t index = (uint8_t)bx::uint32_min(BGFX_CONFIG_MAX_COLOR_PALETTE-1, _clear.m_index[0]);
						const float* rgba = _palette[index];
						const float rr = rgba[0];
						const float gg = rgba[1];
						const float bb = rgba[2];
						const float aa = rgba[3];
						GL_CHECK(glClearColor(rr, gg, bb, aa) );
					}
					else
					{
						float rr = _clear.m_index[0]*1.0f/255.0f;
						float gg = _clear.m_index[1]*1.0f/255.0f;
						float bb = _clear.m_index[2]*1.0f/255.0f;
						float aa = _clear.m_index[3]*1.0f/255.0f;
						GL_CHECK(glClearColor(rr, gg, bb, aa) );
					}

					flags |= GL_COLOR_BUFFER_BIT;
					GL_CHECK(glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE) );
				}

				if (BGFX_CLEAR_DEPTH & _clear.m_flags)
				{
					flags |= GL_DEPTH_BUFFER_BIT;
					GL_CHECK(glClearDepth(_clear.m_depth) );
					GL_CHECK(glDepthMask(GL_TRUE) );
				}

				if (BGFX_CLEAR_STENCIL & _clear.m_flags)
				{
					flags |= GL_STENCIL_BUFFER_BIT;
					GL_CHECK(glClearStencil(_clear.m_stencil) );
				}

				if (0 != flags)
				{
					GL_CHECK(glEnable(GL_SCISSOR_TEST) );
					GL_CHECK(glScissor(_rect.m_x, _height-_rect.m_height-_rect.m_y, _rect.m_width, _rect.m_height) );
					GL_CHECK(glClear(flags) );
					GL_CHECK(glDisable(GL_SCISSOR_TEST) );
				}
			}
			else
			{
				if (0 != m_vao)
				{
					GL_CHECK(glBindVertexArray(m_vao) );
				}

				GL_CHECK(glDisable(GL_SCISSOR_TEST) );
				GL_CHECK(glDisable(GL_CULL_FACE) );
				GL_CHECK(glDisable(GL_BLEND) );

				GLboolean colorMask = !!(BGFX_CLEAR_COLOR & _clear.m_flags);
				GL_CHECK(glColorMask(colorMask, colorMask, colorMask, colorMask) );

				if (BGFX_CLEAR_DEPTH & _clear.m_flags)
				{
					GL_CHECK(glEnable(GL_DEPTH_TEST) );
					GL_CHECK(glDepthFunc(GL_ALWAYS) );
					GL_CHECK(glDepthMask(GL_TRUE) );
				}
				else
				{
					GL_CHECK(glDisable(GL_DEPTH_TEST) );
				}

				if (BGFX_CLEAR_STENCIL & _clear.m_flags)
				{
					GL_CHECK(glEnable(GL_STENCIL_TEST) );
					GL_CHECK(glStencilFuncSeparate(GL_FRONT_AND_BACK, GL_ALWAYS, _clear.m_stencil,  0xff) );
					GL_CHECK(glStencilOpSeparate(GL_FRONT_AND_BACK, GL_REPLACE, GL_REPLACE, GL_REPLACE) );
				}
				else
				{
					GL_CHECK(glDisable(GL_STENCIL_TEST) );
				}

				VertexBufferGL& vb = m_vertexBuffers[_clearQuad.m_vb.idx];
				VertexLayout& layout = _clearQuad.m_layout;

				GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vb.m_id) );

				ProgramGL& program = m_program[_clearQuad.m_program[numMrt-1].idx];
				setProgram(program.m_id);
				program.bindAttributesBegin();
				program.bindAttributes(layout, 0);
				program.bindAttributesEnd();

				if (m_clearQuadColor.idx == kInvalidHandle)
				{
					const UniformRegInfo* infoClearColor = m_uniformReg.find("bgfx_clear_color");
					if (NULL != infoClearColor)
					{
						m_clearQuadColor = infoClearColor->m_handle;
					}
				}

				if (m_clearQuadDepth.idx == kInvalidHandle)
				{
					const UniformRegInfo* infoClearDepth = m_uniformReg.find("bgfx_clear_depth");
					if (NULL != infoClearDepth)
					{
						m_clearQuadDepth = infoClearDepth->m_handle;
					}
				}

				float mrtClearDepth[4] = { g_caps.homogeneousDepth ? (_clear.m_depth * 2.0f - 1.0f) : _clear.m_depth };
				updateUniform(m_clearQuadDepth.idx, mrtClearDepth, sizeof(float)*4);

				float mrtClearColor[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS][4];

				if (BGFX_CLEAR_COLOR_USE_PALETTE & _clear.m_flags)
				{
					for (uint32_t ii = 0; ii < numMrt; ++ii)
					{
						uint8_t index = (uint8_t)bx::uint32_min(BGFX_CONFIG_MAX_COLOR_PALETTE-1, _clear.m_index[ii]);
						bx::memCopy(mrtClearColor[ii], _palette[index], 16);
					}
				}
				else
				{
					float rgba[4] =
					{
						_clear.m_index[0] * 1.0f / 255.0f,
						_clear.m_index[1] * 1.0f / 255.0f,
						_clear.m_index[2] * 1.0f / 255.0f,
						_clear.m_index[3] * 1.0f / 255.0f,
					};

					for (uint32_t ii = 0; ii < numMrt; ++ii)
					{
						bx::memCopy(mrtClearColor[ii], rgba, 16);
					}
				}

				updateUniform(m_clearQuadColor.idx, mrtClearColor[0], numMrt * sizeof(float) * 4);

				commit(*program.m_constantBuffer);

				GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP
					, 0
					, 4
					) );
			}
		}

		void setProgram(GLuint program)
		{
			m_uniformStateCache.saveCurrentProgram(program);
			GL_CHECK(glUseProgram(program) );
		}

		// Cache uniform uploads to avoid redundant uploading of state that is
		// already set to a shader program
		void setUniform1i(uint32_t loc, int value)
		{
			if (m_uniformStateCache.updateUniformCache(loc, value) )
			{
				GL_CHECK(glUniform1i(loc, value) );
			}
		}

		void setUniform1iv(uint32_t loc, int num, const int *data)
		{
			bool changed = false;
			for(int i = 0; i < num; ++i)
			{
				if (m_uniformStateCache.updateUniformCache(loc+i, data[i]) )
				{
					changed = true;
				}
			}
			if (changed)
			{
				GL_CHECK(glUniform1iv(loc, num, data) );
			}
		}

		void setUniform4f(uint32_t loc, float x, float y, float z, float w)
		{
			UniformStateCache::f4 f; f.val[0] = x; f.val[1] = y; f.val[2] = z; f.val[3] = w;
			if (m_uniformStateCache.updateUniformCache(loc, f) )
			{
				GL_CHECK(glUniform4f(loc, x, y, z, w) );
			}
		}

		void setUniform4fv(uint32_t loc, int num, const float *data)
		{
			bool changed = false;
			for(int i = 0; i < num; ++i)
			{
				if (m_uniformStateCache.updateUniformCache(loc+i, *(const UniformStateCache::f4*)&data[4*i]) )
				{
					changed = true;
				}
			}
			if (changed)
			{
				GL_CHECK(glUniform4fv(loc, num, data) );
			}
		}

		void setUniformMatrix3fv(uint32_t loc, int num, GLboolean transpose, const float *data)
		{
			bool changed = false;
			for(int i = 0; i < num; ++i)
			{
				if (m_uniformStateCache.updateUniformCache(loc+i, *(const UniformStateCache::f3x3*)&data[9*i]) )
				{
					changed = true;
				}
			}
			if (changed)
			{
				GL_CHECK(glUniformMatrix3fv(loc, num, transpose, data) );
			}
		}

		void setUniformMatrix4fv(uint32_t loc, int num, GLboolean transpose, const float *data)
		{
			bool changed = false;
			for(int i = 0; i < num; ++i)
			{
				if (m_uniformStateCache.updateUniformCache(loc+i, *(const UniformStateCache::f4x4*)&data[16*i]) )
				{
					changed = true;
				}
			}
			if (changed)
			{
				GL_CHECK(glUniformMatrix4fv(loc, num, transpose, data) );
			}
		}

		void* m_renderdocdll;

		uint16_t m_numWindows;
		FrameBufferHandle m_windows[BGFX_CONFIG_MAX_FRAME_BUFFERS];

		IndexBufferGL m_indexBuffers[BGFX_CONFIG_MAX_INDEX_BUFFERS];
		VertexBufferGL m_vertexBuffers[BGFX_CONFIG_MAX_VERTEX_BUFFERS];
		ShaderGL m_shaders[BGFX_CONFIG_MAX_SHADERS];
		ProgramGL m_program[BGFX_CONFIG_MAX_PROGRAMS];
		TextureGL m_textures[BGFX_CONFIG_MAX_TEXTURES];
		VertexLayout m_vertexLayouts[BGFX_CONFIG_MAX_VERTEX_LAYOUTS];
		FrameBufferGL m_frameBuffers[BGFX_CONFIG_MAX_FRAME_BUFFERS];
		UniformRegistry m_uniformReg;
		void* m_uniforms[BGFX_CONFIG_MAX_UNIFORMS];

		TimerQueryGL m_gpuTimer;
		OcclusionQueryGL m_occlusionQuery;

		SamplerStateCache m_samplerStateCache;
		UniformStateCache m_uniformStateCache;

		TextVideoMem m_textVideoMem;
		bool m_rtMsaa;

		FrameBufferHandle m_fbh;
		uint16_t m_fbDiscard;

		Resolution m_resolution;
		void* m_capture;
		uint32_t m_captureSize;
		float m_maxAnisotropy;
		float m_maxAnisotropyDefault;
		int32_t m_maxMsaa;
		GLuint m_vao;
		uint16_t m_maxLabelLen;
		bool m_blitSupported;
		bool m_readBackSupported;
		bool m_vaoSupport;
		bool m_samplerObjectSupport;
		bool m_shadowSamplersSupport;
		bool m_srgbWriteControlSupport;
		bool m_borderColorSupport;
		bool m_programBinarySupport;
		bool m_textureSwizzleSupport;
		bool m_depthTextureSupport;
		bool m_timerQuerySupport;
		bool m_occlusionQuerySupport;
		bool m_atocSupport;
		bool m_conservativeRasterSupport;
		bool m_imageLoadStoreSupport;
		bool m_flip;

		uint64_t m_hash;

		GLenum m_readPixelsFmt;
		GLuint m_backBufferFbo;
		GLuint m_msaaBackBufferFbo;
		union {
			GLuint m_msaaBackBufferRbos[2];
			GLuint m_msaaBackBufferTextures[2];
		};
		GLuint m_msaaBlitProgram;
		GlContext m_glctx;
		bool m_needPresent;

		UniformHandle m_clearQuadColor;
		UniformHandle m_clearQuadDepth;

		const char* m_vendor;
		const char* m_renderer;
		const char* m_version;
		const char* m_glslVersion;
		bool m_gles3;

		Workaround m_workaround;

		GLuint m_currentFbo;
	};

	RendererContextGL* s_renderGL;

	RendererContextI* rendererCreate(const Init& _init)
	{
		s_renderGL = BX_NEW(g_allocator, RendererContextGL);
		if (!s_renderGL->init(_init) )
		{
			bx::deleteObject(g_allocator, s_renderGL);
			s_renderGL = NULL;
		}
		return s_renderGL;
	}

	void rendererDestroy()
	{
		s_renderGL->shutdown();
		bx::deleteObject(g_allocator, s_renderGL);
		s_renderGL = NULL;
	}

	static void frameBufferValidate()
	{
		GLenum complete = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		BX_ASSERT(GL_FRAMEBUFFER_COMPLETE == complete
			, "glCheckFramebufferStatus failed 0x%08x: %s"
			, complete
			, glEnumName(complete)
		);
		BX_UNUSED(complete);
	}

	const char* glslTypeName(GLuint _type)
	{
#define GLSL_TYPE(_ty) case _ty: return #_ty

		switch (_type)
		{
			GLSL_TYPE(GL_BOOL);
			GLSL_TYPE(GL_INT);
			GLSL_TYPE(GL_INT_VEC2);
			GLSL_TYPE(GL_INT_VEC3);
			GLSL_TYPE(GL_INT_VEC4);
			GLSL_TYPE(GL_UNSIGNED_INT);
			GLSL_TYPE(GL_UNSIGNED_INT_VEC2);
			GLSL_TYPE(GL_UNSIGNED_INT_VEC3);
			GLSL_TYPE(GL_UNSIGNED_INT_VEC4);
			GLSL_TYPE(GL_FLOAT);
			GLSL_TYPE(GL_FLOAT_VEC2);
			GLSL_TYPE(GL_FLOAT_VEC3);
			GLSL_TYPE(GL_FLOAT_VEC4);
			GLSL_TYPE(GL_FLOAT_MAT2);
			GLSL_TYPE(GL_FLOAT_MAT3);
			GLSL_TYPE(GL_FLOAT_MAT4);

			GLSL_TYPE(GL_SAMPLER_2D);
			GLSL_TYPE(GL_SAMPLER_2D_ARRAY);
			GLSL_TYPE(GL_SAMPLER_2D_MULTISAMPLE);

			GLSL_TYPE(GL_INT_SAMPLER_2D);
			GLSL_TYPE(GL_INT_SAMPLER_2D_ARRAY);
			GLSL_TYPE(GL_INT_SAMPLER_2D_MULTISAMPLE);

			GLSL_TYPE(GL_UNSIGNED_INT_SAMPLER_2D);
			GLSL_TYPE(GL_UNSIGNED_INT_SAMPLER_2D_ARRAY);
			GLSL_TYPE(GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE);

			GLSL_TYPE(GL_SAMPLER_2D_SHADOW);
			GLSL_TYPE(GL_SAMPLER_2D_ARRAY_SHADOW);

			GLSL_TYPE(GL_SAMPLER_3D);
			GLSL_TYPE(GL_INT_SAMPLER_3D);
			GLSL_TYPE(GL_UNSIGNED_INT_SAMPLER_3D);

			GLSL_TYPE(GL_SAMPLER_CUBE);
			GLSL_TYPE(GL_INT_SAMPLER_CUBE);
			GLSL_TYPE(GL_UNSIGNED_INT_SAMPLER_CUBE);

			GLSL_TYPE(GL_IMAGE_1D);
			GLSL_TYPE(GL_INT_IMAGE_1D);
			GLSL_TYPE(GL_UNSIGNED_INT_IMAGE_1D);

			GLSL_TYPE(GL_IMAGE_2D);
			GLSL_TYPE(GL_IMAGE_2D_ARRAY);
			GLSL_TYPE(GL_INT_IMAGE_2D);
			GLSL_TYPE(GL_UNSIGNED_INT_IMAGE_2D);

			GLSL_TYPE(GL_IMAGE_3D);
			GLSL_TYPE(GL_INT_IMAGE_3D);
			GLSL_TYPE(GL_UNSIGNED_INT_IMAGE_3D);

			GLSL_TYPE(GL_IMAGE_CUBE);
			GLSL_TYPE(GL_INT_IMAGE_CUBE);
			GLSL_TYPE(GL_UNSIGNED_INT_IMAGE_CUBE);
		}

#undef GLSL_TYPE

		BX_ASSERT(false, "Unknown GLSL type? %x", _type);
		return "UNKNOWN GLSL TYPE!";
	}

	const char* glEnumName(GLenum _enum)
	{
#define GLENUM(_ty) case _ty: return #_ty

		switch (_enum)
		{
			GLENUM(GL_TEXTURE);
			GLENUM(GL_RENDERBUFFER);

			GLENUM(GL_INVALID_ENUM);
			GLENUM(GL_INVALID_FRAMEBUFFER_OPERATION);
			GLENUM(GL_INVALID_VALUE);
			GLENUM(GL_INVALID_OPERATION);
			GLENUM(GL_OUT_OF_MEMORY);

			GLENUM(GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT);
			GLENUM(GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT);
//			GLENUM(GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER);
//			GLENUM(GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER);
			GLENUM(GL_FRAMEBUFFER_UNSUPPORTED);
		}

#undef GLENUM

		BX_WARN(false, "Unknown enum? %x", _enum);
		return "<GLenum?>";
	}

	UniformType::Enum convertGlType(GLenum _type)
	{
		switch (_type)
		{
		case GL_INT:
		case GL_UNSIGNED_INT:
			return UniformType::Sampler;

		case GL_FLOAT:
		case GL_FLOAT_VEC2:
		case GL_FLOAT_VEC3:
		case GL_FLOAT_VEC4:
			return UniformType::Vec4;

		case GL_FLOAT_MAT2:
			break;

		case GL_FLOAT_MAT3:
			return UniformType::Mat3;

		case GL_FLOAT_MAT4:
			return UniformType::Mat4;

		case GL_SAMPLER_2D:
		case GL_SAMPLER_2D_ARRAY:
		case GL_SAMPLER_2D_MULTISAMPLE:

		case GL_INT_SAMPLER_2D:
		case GL_INT_SAMPLER_2D_ARRAY:
		case GL_INT_SAMPLER_2D_MULTISAMPLE:

		case GL_UNSIGNED_INT_SAMPLER_2D:
		case GL_UNSIGNED_INT_SAMPLER_2D_ARRAY:
		case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE:

		case GL_SAMPLER_2D_SHADOW:
		case GL_SAMPLER_2D_ARRAY_SHADOW:

		case GL_SAMPLER_3D:
		case GL_INT_SAMPLER_3D:
		case GL_UNSIGNED_INT_SAMPLER_3D:

		case GL_SAMPLER_CUBE:
		case GL_INT_SAMPLER_CUBE:
		case GL_UNSIGNED_INT_SAMPLER_CUBE:

		case GL_IMAGE_1D:
		case GL_INT_IMAGE_1D:
		case GL_UNSIGNED_INT_IMAGE_1D:

		case GL_IMAGE_2D:
		case GL_IMAGE_2D_ARRAY:
		case GL_INT_IMAGE_2D:
		case GL_UNSIGNED_INT_IMAGE_2D:

		case GL_IMAGE_3D:
		case GL_INT_IMAGE_3D:
		case GL_UNSIGNED_INT_IMAGE_3D:

		case GL_IMAGE_CUBE:
		case GL_INT_IMAGE_CUBE:
		case GL_UNSIGNED_INT_IMAGE_CUBE:
			return UniformType::Sampler;
		};

		BX_ASSERT(false, "Unrecognized GL type 0x%04x.", _type);
		return UniformType::End;
	}

	void ProgramGL::create(const ShaderGL& _vsh, const ShaderGL& _fsh)
	{
		m_id = glCreateProgram();
		BX_TRACE("Program create: GL%d: GL%d, GL%d", m_id, _vsh.m_id, _fsh.m_id);

		const uint64_t id = (uint64_t(_vsh.m_hash)<<32) | _fsh.m_hash;
		const bool cached = s_renderGL->programFetchFromCache(m_id, id);

		if (!cached)
		{
			GLint linked = 0;
			if (0 != _vsh.m_id)
			{
				GL_CHECK(glAttachShader(m_id, _vsh.m_id) );

				if (0 != _fsh.m_id)
				{
					GL_CHECK(glAttachShader(m_id, _fsh.m_id) );
				}

				GL_CHECK(glLinkProgram(m_id) );
				GL_CHECK(glGetProgramiv(m_id, GL_LINK_STATUS, &linked) );

				if (0 == linked)
				{
					char log[1024];
					GL_CHECK(glGetProgramInfoLog(m_id, sizeof(log), NULL, log) );
					BX_TRACE("%d: %s", linked, log);
				}
			}

			if (0 == linked)
			{
				BX_WARN(0 != _vsh.m_id, "Invalid vertex/compute shader.");
				GL_CHECK(glDeleteProgram(m_id) );
				m_usedCount = 0;
				m_id = 0;
				return;
			}

			s_renderGL->programCache(m_id, id);
		}

		init();

		if (!cached
		&&  s_renderGL->m_workaround.m_detachShader)
		{
			// Must be after init, otherwise init might fail to lookup shader
			// info (NVIDIA Tegra 3 OpenGL ES 2.0 14.01003).
			GL_CHECK(glDetachShader(m_id, _vsh.m_id) );

			if (0 != _fsh.m_id)
			{
				GL_CHECK(glDetachShader(m_id, _fsh.m_id) );
			}
		}
	}

	void ProgramGL::destroy()
	{
		if (NULL != m_constantBuffer)
		{
			UniformBuffer::destroy(m_constantBuffer);
			m_constantBuffer = NULL;
		}
		m_numPredefined = 0;

		if (0 != m_id)
		{
			s_renderGL->setProgram(0);
			GL_CHECK(glDeleteProgram(m_id) );
			m_id = 0;
		}
	}

	void ProgramGL::init()
	{
		GLint activeAttribs  = 0;
		GLint activeUniforms = 0;
		GLint activeBuffers  = 0;

#if BGFX_CONFIG_RENDERER_OPENGL >= 31
		GL_CHECK(glBindFragDataLocation(m_id, 0, "bgfx_FragColor") );
#endif // BGFX_CONFIG_RENDERER_OPENGL >= 31

		GLint max0, max1;

		bool piqSupported = true
			&& s_extension[Extension::ARB_program_interface_query     ].m_supported
			&& s_extension[Extension::ARB_shader_storage_buffer_object].m_supported
			;

		if (piqSupported)
		{
			GL_CHECK(glGetProgramInterfaceiv(m_id, GL_PROGRAM_INPUT,   GL_ACTIVE_RESOURCES, &activeAttribs ) );
			GL_CHECK(glGetProgramInterfaceiv(m_id, GL_UNIFORM,         GL_ACTIVE_RESOURCES, &activeUniforms) );
			GL_CHECK(glGetProgramInterfaceiv(m_id, GL_BUFFER_VARIABLE, GL_ACTIVE_RESOURCES, &activeBuffers ) );
			GL_CHECK(glGetProgramInterfaceiv(m_id, GL_PROGRAM_INPUT,   GL_MAX_NAME_LENGTH,  &max0          ) );
			GL_CHECK(glGetProgramInterfaceiv(m_id, GL_UNIFORM,         GL_MAX_NAME_LENGTH,  &max1          ) );
		}
		else
		{
			GL_CHECK(glGetProgramiv(m_id, GL_ACTIVE_ATTRIBUTES, &activeAttribs ) );
			GL_CHECK(glGetProgramiv(m_id, GL_ACTIVE_UNIFORMS,   &activeUniforms) );

			GL_CHECK(glGetProgramiv(m_id, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &max0) );
			GL_CHECK(glGetProgramiv(m_id, GL_ACTIVE_UNIFORM_MAX_LENGTH,   &max1) );
		}

		uint32_t maxLength = bx::uint32_max(max0, max1);
		char* name = (char*)alloca(maxLength + 1);

		BX_TRACE("Program %d", m_id);
		BX_TRACE("Attributes (%d):", activeAttribs);
		for (int32_t ii = 0; ii < activeAttribs; ++ii)
		{
			GLint size;
			GLenum type = 0;

			if (piqSupported)
			{
				GL_CHECK(glGetProgramResourceName(m_id, GL_PROGRAM_INPUT, ii, maxLength + 1, &size, name) );
				GLenum typeProp[] = { GL_TYPE };
				GL_CHECK(glGetProgramResourceiv(m_id
					, GL_PROGRAM_INPUT
					, ii
					, BX_COUNTOF(typeProp)
					, typeProp
					, 1
					, NULL
					, (GLint *)&type)
					);
			}
			else
			{
				GL_CHECK(glGetActiveAttrib(m_id, ii, maxLength + 1, NULL, &size, &type, name) );
			}

			BX_TRACE("\t%s %s is at location %d"
				, glslTypeName(type)
				, name
				, glGetAttribLocation(m_id, name)
				);
		}

		m_numPredefined = 0;
		m_numSamplers = 0;

		BX_TRACE("Uniforms (%d):", activeUniforms);
		for (int32_t ii = 0; ii < activeUniforms; ++ii)
		{
			struct VariableInfo
			{
				GLenum type;
				GLint  loc;
				GLint  num;
			};
			VariableInfo vi;
			GLenum props[] = { GL_TYPE, GL_LOCATION, GL_ARRAY_SIZE };

			GLenum gltype;
			GLint num;
			GLint loc;

			if (piqSupported)
			{
				GL_CHECK(glGetProgramResourceiv(m_id
					, GL_UNIFORM
					, ii
					, BX_COUNTOF(props)
					, props
					, BX_COUNTOF(props)
					, NULL
					, (GLint*)&vi
					) );

				GL_CHECK(glGetProgramResourceName(m_id
					, GL_UNIFORM
					, ii
					, maxLength + 1
					, NULL
					, name
					) );

				gltype = vi.type;
				loc    = vi.loc;
				num    = vi.num;
			}
			else
			{
				GL_CHECK(glGetActiveUniform(m_id, ii, maxLength + 1, NULL, &num, &gltype, name) );
				loc = glGetUniformLocation(m_id, name);
			}

			num = bx::uint32_max(num, 1);

			int32_t offset = 0;
			const bx::StringView array = bx::strFind(name, '[');
			if (!array.isEmpty() )
			{
				name[array.getPtr() - name] = '\0';
				BX_TRACE("--- %s", name);
				const bx::StringView end = bx::strFind(array.getPtr()+1, ']');
				bx::fromString(&offset, bx::StringView(array.getPtr()+1, end.getPtr() ) );
			}

			switch (gltype)
			{
			case GL_SAMPLER_2D:
			case GL_SAMPLER_2D_ARRAY:
			case GL_SAMPLER_2D_MULTISAMPLE:

			case GL_INT_SAMPLER_2D:
			case GL_INT_SAMPLER_2D_ARRAY:
			case GL_INT_SAMPLER_2D_MULTISAMPLE:

			case GL_UNSIGNED_INT_SAMPLER_2D:
			case GL_UNSIGNED_INT_SAMPLER_2D_ARRAY:
			case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE:

			case GL_SAMPLER_2D_SHADOW:
			case GL_SAMPLER_2D_ARRAY_SHADOW:

			case GL_SAMPLER_3D:
			case GL_INT_SAMPLER_3D:
			case GL_UNSIGNED_INT_SAMPLER_3D:

			case GL_SAMPLER_CUBE:
			case GL_INT_SAMPLER_CUBE:
			case GL_UNSIGNED_INT_SAMPLER_CUBE:

			case GL_IMAGE_1D:
			case GL_INT_IMAGE_1D:
			case GL_UNSIGNED_INT_IMAGE_1D:

			case GL_IMAGE_2D:
			case GL_INT_IMAGE_2D:
			case GL_UNSIGNED_INT_IMAGE_2D:

			case GL_IMAGE_3D:
			case GL_INT_IMAGE_3D:
			case GL_UNSIGNED_INT_IMAGE_3D:

			case GL_IMAGE_CUBE:
			case GL_INT_IMAGE_CUBE:
			case GL_UNSIGNED_INT_IMAGE_CUBE:
				if (m_numSamplers < BX_COUNTOF(m_sampler) )
				{
					BX_TRACE("Sampler #%d at location %d.", m_numSamplers, loc);
					m_sampler[m_numSamplers] = loc;
					m_numSamplers++;
				}
				else
				{
					BX_TRACE("Too many samplers (max: %d)! Sampler at location %d."
							, BX_COUNTOF(m_sampler)
							, loc
							);
				}
				break;

			default:
				break;
			}

			PredefinedUniform::Enum predefined = nameToPredefinedUniformEnum(name);
			if (PredefinedUniform::Count != predefined)
			{
				m_predefined[m_numPredefined].m_loc   = loc;
				m_predefined[m_numPredefined].m_count = uint16_t(num);
				m_predefined[m_numPredefined].m_type  = uint8_t(predefined);
				m_numPredefined++;
			}
			else
			{
				const UniformRegInfo* info = s_renderGL->m_uniformReg.find(name);
				BX_WARN(NULL != info, "User defined uniform '%s' is not found, it won't be set.", name);

				if (NULL != info)
				{
					if (NULL == m_constantBuffer)
					{
						m_constantBuffer = UniformBuffer::create(1024);
					}

					UniformType::Enum type = convertGlType(gltype);
					m_constantBuffer->writeUniformHandle(type, 0, info->m_handle, uint16_t(num) );
					m_constantBuffer->write(loc);
					BX_TRACE("store %s %d", name, info->m_handle);
				}
			}

			BX_TRACE("\tuniform %s %s%s is at location %d, size %d, offset %d"
				, glslTypeName(gltype)
				, name
				, PredefinedUniform::Count != predefined ? "*" : ""
				, loc
				, num
				, offset
				);
			BX_UNUSED(offset);
		}

		if (NULL != m_constantBuffer)
		{
			m_constantBuffer->finish();
		}

		if (piqSupported)
		{
			struct VariableInfo
			{
				GLenum type;
			};
			VariableInfo vi;
			GLenum props[] = { GL_TYPE };

			BX_TRACE("Buffers (%d):", activeBuffers);
			for (int32_t ii = 0; ii < activeBuffers; ++ii)
			{
				GL_CHECK(glGetProgramResourceiv(m_id
					, GL_BUFFER_VARIABLE
					, ii
					, BX_COUNTOF(props)
					, props
					, BX_COUNTOF(props)
					, NULL
					, (GLint*)&vi
					) );

				GL_CHECK(glGetProgramResourceName(m_id
					, GL_BUFFER_VARIABLE
					, ii
					, maxLength + 1
					, NULL
					, name
					) );

				BX_TRACE("\t%s %s at %d"
					, glslTypeName(vi.type)
					, name
					, 0 //vi.loc
					);
			}
		}

		bx::memSet(m_attributes, 0xff, sizeof(m_attributes) );
		uint32_t used = 0;
		for (uint8_t ii = 0; ii < Attrib::Count; ++ii)
		{
			GLint loc = glGetAttribLocation(m_id, s_attribName[ii]);
			if (-1 != loc)
			{
				BX_TRACE("attr %s: %d", s_attribName[ii], loc);
				m_attributes[ii] = loc;
				m_used[used++] = ii;
			}
		}
		BX_ASSERT(used < BX_COUNTOF(m_used), "Out of bounds %d > array size %d.", used, Attrib::Count);
		m_usedCount = (uint8_t)used;

		used = 0;
		for (uint32_t ii = 0, baseVertex = 0; ii < BX_COUNTOF(s_instanceDataName); ++ii, baseVertex += 16)
		{
			GLint loc = glGetAttribLocation(m_id, s_instanceDataName[ii]);
			if (-1 != loc)
			{
				BX_TRACE("instance data %s: %d", s_instanceDataName[ii], loc);
				m_instanceData[used]   = loc;
				m_instanceOffset[used] = uint16_t(baseVertex);

				used++;
			}
		}
		BX_ASSERT(used < BX_COUNTOF(m_instanceData)
			, "Out of bounds %d > array size %d."
			, used
			, BX_COUNTOF(m_instanceData)
			);
		m_instanceData[used] = -1;
	}

	void ProgramGL::bindAttributesBegin()
	{
		bx::memCopy(m_unboundUsedAttrib, m_used, sizeof(m_unboundUsedAttrib) );
	}

	void ProgramGL::bindAttributes(const VertexLayout& _layout, uint32_t _baseVertex)
	{
		for (uint32_t ii = 0, iiEnd = m_usedCount; ii < iiEnd; ++ii)
		{
			Attrib::Enum attr = Attrib::Enum(m_used[ii]);
			GLint loc = m_attributes[attr];

			uint8_t num;
			AttribType::Enum type;
			bool normalized;
			bool asInt;
			_layout.decode(attr, num, type, normalized, asInt);

			if (-1 != loc)
			{
				if (UINT16_MAX != _layout.m_attributes[attr])
				{
					lazyEnableVertexAttribArray(loc);
					GL_CHECK(glVertexAttribDivisor(loc, 0) );

					uint32_t baseVertex = _baseVertex*_layout.m_stride + _layout.m_offset[attr];
					if ( (BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGL >= 30) || s_renderGL->m_gles3)
					&&  !isFloat(type)
					&&  !normalized)
					{
						GL_CHECK(glVertexAttribIPointer(loc
							, num
							, s_attribType[type]
							, _layout.m_stride
							, (void*)(uintptr_t)baseVertex)
							);
					}
					else
					{
						GL_CHECK(glVertexAttribPointer(loc
							, num
							, s_attribType[type]
							, normalized
							, _layout.m_stride
							, (void*)(uintptr_t)baseVertex)
							);
					}

					m_unboundUsedAttrib[ii] = Attrib::Count;
				}
			}
		}
	}

	void ProgramGL::bindInstanceData(uint32_t _stride, uint32_t _baseVertex) const
	{
		for (uint32_t ii = 0; -1 != m_instanceData[ii]; ++ii)
		{
			GLint loc = m_instanceData[ii];
			lazyEnableVertexAttribArray(loc);

			const uint32_t baseVertex = _baseVertex + m_instanceOffset[ii];
			GL_CHECK(glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, _stride, (void*)(uintptr_t)baseVertex) );
			GL_CHECK(glVertexAttribDivisor(loc, 1) );
		}
	}

	void ProgramGL::bindAttributesEnd()
	{
		for (uint32_t ii = 0, iiEnd = m_usedCount; ii < iiEnd; ++ii)
		{
			if (Attrib::Count != m_unboundUsedAttrib[ii])
			{
				Attrib::Enum attr = Attrib::Enum(m_unboundUsedAttrib[ii]);
				GLint loc = m_attributes[attr];
				lazyDisableVertexAttribArray(loc);
			}
		}

		applyLazyEnabledVertexAttributes();
	}

	void ProgramGL::unbindAttributes()
	{
		for(uint32_t ii = 0, iiEnd = m_usedCount; ii < iiEnd; ++ii)
		{
			if (Attrib::Count == m_unboundUsedAttrib[ii])
			{
				Attrib::Enum attr = Attrib::Enum(m_used[ii]);
				GLint loc = m_attributes[attr];
				lazyDisableVertexAttribArray(loc);
			}
		}
	}

	void ProgramGL::unbindInstanceData() const
	{
		for(uint32_t ii = 0; -1 != m_instanceData[ii]; ++ii)
		{
			GLint loc = m_instanceData[ii];
			lazyDisableVertexAttribArray(loc);
		}
	}

	void IndexBufferGL::destroy()
	{
		GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) );
		GL_CHECK(glDeleteBuffers(1, &m_id) );
	}

	void VertexBufferGL::destroy()
	{
		GL_CHECK(glBindBuffer(m_target, 0) );
		GL_CHECK(glDeleteBuffers(1, &m_id) );
	}

	bool TextureGL::init(GLenum _target, uint32_t _width, uint32_t _height, uint32_t _depth, uint8_t _numMips, uint64_t _flags)
	{
		m_target  = _target;
		m_numMips = _numMips;
		m_flags   = _flags;
		m_width   = _width;
		m_height  = _height;
		m_depth   = _depth;
		m_currentSamplerHash = UINT32_MAX;

		const bool writeOnly    = 0 != (m_flags&BGFX_TEXTURE_RT_WRITE_ONLY);
		const bool computeWrite = 0 != (m_flags&BGFX_TEXTURE_COMPUTE_WRITE );
		const bool srgb         = 0 != (m_flags&BGFX_TEXTURE_SRGB);
		const bool renderTarget = 0 != (m_flags&BGFX_TEXTURE_RT_MASK);
		const bool textureArray = false
			|| _target == GL_TEXTURE_2D_ARRAY
			|| _target == GL_TEXTURE_CUBE_MAP_ARRAY
			;

		if (!writeOnly
		|| (renderTarget && textureArray) )
		{
			GL_CHECK(glGenTextures(1, &m_id) );
			BX_ASSERT(0 != m_id, "Failed to generate texture id.");
			GL_CHECK(glBindTexture(_target, m_id) );
			GL_CHECK(glPixelStorei(GL_UNPACK_ALIGNMENT, 1) );

			const TextureFormatInfo& tfi = s_textureFormat[m_textureFormat];

			const GLenum fmt = srgb
				? s_textureFormat[m_textureFormat].m_fmtSrgb
				: s_textureFormat[m_textureFormat].m_fmt
				;

			m_fmt  = fmt;
			m_type = tfi.m_type;

			const bool swizzle = true
				&& TextureFormat::BGRA8 == m_requestedFormat
				&& !s_textureFormat[m_requestedFormat].m_supported
				&& !s_renderGL->m_textureSwizzleSupport
				;
			const bool convert = false
				|| m_textureFormat != m_requestedFormat
				|| swizzle
				;

			if (convert)
			{
				m_textureFormat = (uint8_t)TextureFormat::RGBA8;
				const TextureFormatInfo& tfiRgba8 = s_textureFormat[TextureFormat::RGBA8];
				m_fmt  = tfiRgba8.m_fmt;
				m_type = tfiRgba8.m_type;
			}

			const GLenum internalFmt = srgb
				? s_textureFormat[m_textureFormat].m_internalFmtSrgb
				: s_textureFormat[m_textureFormat].m_internalFmt
				;

			if (textureArray)
			{
				GL_CHECK(glTexStorage3D(_target
					, _numMips
					, internalFmt
					, m_width
					, m_height
					, _depth
					) );
			}
			else if (computeWrite)
			{
				if (_target == GL_TEXTURE_3D)
				{
					GL_CHECK(glTexStorage3D(_target
						, _numMips
						, internalFmt
						, m_width
						, m_height
						, _depth
						) );
				}
				else
				{
					GL_CHECK(glTexStorage2D(_target
						, _numMips
						, internalFmt
						, m_width
						, m_height
						) );
				}
			}

			setSamplerState(uint32_t(_flags), NULL);

			if (BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGL)
			&&  TextureFormat::BGRA8 == m_requestedFormat
			&&  !s_textureFormat[m_requestedFormat].m_supported
			&&  s_renderGL->m_textureSwizzleSupport)
			{
				GLint swizzleMask[] = { GL_BLUE, GL_GREEN, GL_RED, GL_ALPHA };
				GL_CHECK(glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzleMask) );
			}
		}

		if (renderTarget)
		{
			uint32_t msaaQuality = ( (m_flags&BGFX_TEXTURE_RT_MSAA_MASK)>>BGFX_TEXTURE_RT_MSAA_SHIFT);
			msaaQuality = bx::uint32_satsub(msaaQuality, 1);
			msaaQuality = bx::uint32_min(s_renderGL->m_maxMsaa, msaaQuality == 0 ? 0 : 1<<msaaQuality);
			const bool msaaSample = 0 != (m_flags&BGFX_TEXTURE_MSAA_SAMPLE);

			if (!msaaSample
			&& (0 != msaaQuality || writeOnly)
			&&  !textureArray)
			{
				GL_CHECK(glGenRenderbuffers(1, &m_rbo) );
				BX_ASSERT(0 != m_rbo, "Failed to generate renderbuffer id.");
				GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, m_rbo) );

				if (0 == msaaQuality)
				{
					GL_CHECK(glRenderbufferStorage(GL_RENDERBUFFER
						, s_rboFormat[m_textureFormat]
						, _width
						, _height
						) );
				}
				else if (BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGL) || s_renderGL->m_gles3)
				{
					GL_CHECK(glRenderbufferStorageMultisample(GL_RENDERBUFFER
						, msaaQuality
						, s_rboFormat[m_textureFormat]
						, _width
						, _height
						) );
				}

				GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, 0) );

				if (writeOnly)
				{
					// This is render buffer, there is no sampling, no need
					// to create texture.
					return false;
				}
			}
		}

		return true;
	}

	void TextureGL::create(const Memory* _mem, uint64_t _flags, uint8_t _skip)
	{
		bimg::ImageContainer imageContainer;

		if (bimg::imageParse(imageContainer, _mem->data, _mem->size) )
		{
			const uint8_t startLod = bx::min<uint8_t>(_skip, imageContainer.m_numMips-1);

			bimg::TextureInfo ti;
			bimg::imageGetSize(
				  &ti
				, uint16_t(imageContainer.m_width >>startLod)
				, uint16_t(imageContainer.m_height>>startLod)
				, uint16_t(imageContainer.m_depth >>startLod)
				, imageContainer.m_cubeMap
				, 1 < imageContainer.m_numMips
				, imageContainer.m_numLayers
				, imageContainer.m_format
				);
			ti.numMips = bx::min<uint8_t>(imageContainer.m_numMips-startLod, ti.numMips);

			m_requestedFormat  = uint8_t(imageContainer.m_format);
			m_textureFormat    = uint8_t(getViableTextureFormat(imageContainer) );

			const bool computeWrite = 0 != (_flags&BGFX_TEXTURE_COMPUTE_WRITE);
			const bool srgb         = 0 != (_flags&BGFX_TEXTURE_SRGB);
			const bool msaaSample   = 0 != (_flags&BGFX_TEXTURE_MSAA_SAMPLE);
			uint32_t msaaQuality = ( (_flags&BGFX_TEXTURE_RT_MSAA_MASK)>>BGFX_TEXTURE_RT_MSAA_SHIFT);
			msaaQuality = bx::uint32_satsub(msaaQuality, 1);
			msaaQuality = bx::uint32_min(s_renderGL->m_maxMsaa, msaaQuality == 0 ? 0 : 1<<msaaQuality);

			GLenum target = msaaSample ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
			if (imageContainer.m_cubeMap)
			{
				target = GL_TEXTURE_CUBE_MAP;
			}
			else if (imageContainer.m_depth > 1)
			{
				target = GL_TEXTURE_3D;
			}

			const bool textureArray = 1 < ti.numLayers;
			if (textureArray)
			{
				switch (target)
				{
				case GL_TEXTURE_CUBE_MAP:       target = GL_TEXTURE_CUBE_MAP_ARRAY;       break;
				case GL_TEXTURE_2D_MULTISAMPLE: target = GL_TEXTURE_2D_MULTISAMPLE_ARRAY; break;
				default:                        target = GL_TEXTURE_2D_ARRAY;             break;
				}
			}

			if (!init(target
				, ti.width
				, ti.height
				, textureArray ? ti.numLayers : ti.depth
				, ti.numMips
				, _flags
				) )
			{
				return;
			}

			m_numLayers = ti.numLayers;

			target = isCubeMap()
				? GL_TEXTURE_CUBE_MAP_POSITIVE_X
				: m_target
				;

			const GLenum internalFmt = srgb
				? s_textureFormat[m_textureFormat].m_internalFmtSrgb
				: s_textureFormat[m_textureFormat].m_internalFmt
				;
			const GLenum fmt = srgb
				? s_textureFormat[m_textureFormat].m_fmtSrgb
				: s_textureFormat[m_textureFormat].m_fmt
				;

			const bool swizzle = true
				&& TextureFormat::BGRA8 == m_requestedFormat
				&& !s_textureFormat[m_requestedFormat].m_supported
				&& !s_renderGL->m_textureSwizzleSupport
				;
			const bool compressed = bimg::isCompressed(bimg::TextureFormat::Enum(m_requestedFormat) );
			const bool convert    = false
				|| m_textureFormat != m_requestedFormat
				|| swizzle
				;

			BX_TRACE("Texture%-4s %3d: %s %s(requested: %s), layers %d, %dx%dx%d%s."
				, imageContainer.m_cubeMap ? "Cube" : (1 < imageContainer.m_depth ? "3D" : "2D")
				, this - s_renderGL->m_textures
				, getName( (TextureFormat::Enum)m_textureFormat)
				, srgb ? "+sRGB " : ""
				, getName( (TextureFormat::Enum)m_requestedFormat)
				, ti.numLayers
				, ti.width
				, ti.height
				, imageContainer.m_cubeMap ? 6 : (1 < imageContainer.m_depth ? imageContainer.m_depth : 0)
				, 0 != (m_flags&BGFX_TEXTURE_RT_MASK) ? " (render target)" : ""
				);

			BX_WARN(!convert, "Texture %s%s%s from %s to %s."
				, swizzle ? "swizzle" : ""
				, swizzle&&convert ? " and " : ""
				, convert ? "convert" : ""
				, getName( (TextureFormat::Enum)m_requestedFormat)
				, getName( (TextureFormat::Enum)m_textureFormat)
				);

			uint8_t* temp = NULL;
			if (convert)
			{
				temp = (uint8_t*)bx::alloc(g_allocator, ti.width*ti.height*4);
			}

			const uint16_t numSides = ti.numLayers * (imageContainer.m_cubeMap ? 6 : 1);

			for (uint16_t side = 0; side < numSides; ++side)
			{
				uint32_t width  = ti.width;
				uint32_t height = ti.height;
				uint32_t depth  = ti.depth;
				GLenum imageTarget = imageContainer.m_cubeMap && !textureArray
					? target+side
					: target
					;

				for (uint8_t lod = 0, num = ti.numMips; lod < num; ++lod)
				{
					width  = bx::uint32_max(1, width);
					height = bx::uint32_max(1, height);
					depth  = 1 < imageContainer.m_depth
						? bx::uint32_max(1, depth)
						: side
						;

					bimg::ImageMip mip;
					if (bimg::imageGetRawData(imageContainer, side, lod+startLod, _mem->data, _mem->size, mip) )
					{
						if (compressed
						&& !convert)
						{
							GL_CHECK(compressedTexImage(imageTarget
								, lod
								, internalFmt
								, width
								, height
								, depth
								, 0
								, mip.m_size
								, mip.m_data
								) );
						}
						else
						{
							const uint8_t* data = mip.m_data;

							if (convert)
							{
								imageDecodeToRgba8(
									  g_allocator
									, temp
									, mip.m_data
									, mip.m_width
									, mip.m_height
									, mip.m_width*4
									, mip.m_format
									);
								data = temp;
							}

							GL_CHECK(texImage(imageTarget
								, msaaQuality
								, lod
								, internalFmt
								, width
								, height
								, depth
								, 0
								, fmt
								, m_type
								, data
								) );
						}
					}
					else if (!computeWrite)
					{
						if (compressed
						&& !convert)
						{
							uint32_t size = bx::max<uint32_t>(1, (width  + 3)>>2)
										  * bx::max<uint32_t>(1, (height + 3)>>2)
										  * 4*4* bimg::getBitsPerPixel(bimg::TextureFormat::Enum(m_textureFormat) )/8
										  ;

							GL_CHECK(compressedTexImage(imageTarget
								, lod
								, internalFmt
								, width
								, height
								, depth
								, 0
								, size
								, NULL
								) );
						}
						else
						{
							GL_CHECK(texImage(imageTarget
								, msaaQuality
								, lod
								, internalFmt
								, width
								, height
								, depth
								, 0
								, fmt
								, m_type
								, NULL
								) );
						}
					}

					width  >>= 1;
					height >>= 1;
					depth  >>= 1;
				}
			}

			GLint mapping[4] = {
				s_textureFormat[m_textureFormat].m_mapping[0],
				s_textureFormat[m_textureFormat].m_mapping[1],
				s_textureFormat[m_textureFormat].m_mapping[2],
				s_textureFormat[m_textureFormat].m_mapping[3],
			};
			if (s_renderGL->m_textureSwizzleSupport
			&& (-1 != mapping[0] || -1 != mapping[1] || -1 != mapping[2] || -1 != mapping[3]) )
			{
				mapping[0] = -1 == mapping[0] ? GL_RED   : mapping[0];
				mapping[1] = -1 == mapping[1] ? GL_GREEN : mapping[1];
				mapping[2] = -1 == mapping[2] ? GL_BLUE  : mapping[2];
				mapping[3] = -1 == mapping[3] ? GL_ALPHA : mapping[3];

				GL_CHECK(glTexParameteriv(m_target, GL_TEXTURE_SWIZZLE_RGBA, mapping));
			}

			if (NULL != temp)
			{
				bx::free(g_allocator, temp);
			}
		}

		GL_CHECK(glBindTexture(m_target, 0) );
	}

	void TextureGL::destroy()
	{
		if (0 == (m_flags & BGFX_SAMPLER_INTERNAL_SHARED)
		&&  0 != m_id)
		{
			GL_CHECK(glBindTexture(m_target, 0) );
			GL_CHECK(glDeleteTextures(1, &m_id) );
			m_id = 0;
		}

		if (0 != m_rbo)
		{
			GL_CHECK(glDeleteRenderbuffers(1, &m_rbo) );
			m_rbo = 0;
		}
	}

	void TextureGL::overrideInternal(uintptr_t _ptr)
	{
		destroy();
		m_flags |= BGFX_SAMPLER_INTERNAL_SHARED;
		m_id = (GLuint)_ptr;
	}

	void TextureGL::update(uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem)
	{
		const uint32_t bpp = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(m_textureFormat) );
		const uint32_t rectpitch = _rect.m_width*bpp/8;
		uint32_t srcpitch  = UINT16_MAX == _pitch ? rectpitch : _pitch;

		GL_CHECK(glBindTexture(m_target, m_id) );
		GL_CHECK(glPixelStorei(GL_UNPACK_ALIGNMENT, 1) );

		GLenum target = isCubeMap()
			? GL_TEXTURE_CUBE_MAP_POSITIVE_X
			: m_target
			;

		const bool swizzle = true
			&& TextureFormat::BGRA8 == m_requestedFormat
			&& !s_textureFormat[m_requestedFormat].m_supported
			&& !s_renderGL->m_textureSwizzleSupport
			;
		const bool unpackRowLength = !!BGFX_CONFIG_RENDERER_OPENGL || s_extension[Extension::EXT_unpack_subimage].m_supported;
		const bool compressed      = bimg::isCompressed(bimg::TextureFormat::Enum(m_requestedFormat) );
		const bool convert         = false
			|| (compressed && m_textureFormat != m_requestedFormat)
			|| swizzle
			;

		Rect rect;
		rect.setIntersect(_rect
			, {
				0, 0,
				uint16_t(bx::max(1u, m_width  >> _mip) ),
				uint16_t(bx::max(1u, m_height >> _mip) ),
			});

		uint32_t width  = rect.m_width;
		uint32_t height = rect.m_height;

		uint8_t* temp = NULL;
		if (convert
		||  !unpackRowLength)
		{
			temp = (uint8_t*)bx::alloc(g_allocator, rectpitch*height);
		}
		else if (unpackRowLength)
		{
			GL_CHECK(glPixelStorei(GL_UNPACK_ROW_LENGTH, srcpitch*8/bpp) );
		}

		if (compressed
		&& !convert)
		{
			const uint8_t* data = _mem->data;

			if (!unpackRowLength)
			{
				bimg::imageCopy(temp, width, height, 1, bpp, srcpitch, data);
				data = temp;
			}
			const GLenum internalFmt = (0 != (m_flags & BGFX_TEXTURE_SRGB) )
				? s_textureFormat[m_textureFormat].m_internalFmtSrgb
				: s_textureFormat[m_textureFormat].m_internalFmt
				;
			GL_CHECK(compressedTexSubImage(target+_side
				, _mip
				, rect.m_x
				, rect.m_y
				, _z
				, rect.m_width
				, rect.m_height
				, _depth
				, internalFmt
				, _mem->size
				, data
				) );
		}
		else
		{
			const uint8_t* data = _mem->data;

			if (convert)
			{
				bimg::imageDecodeToRgba8(g_allocator, temp, data, width, height, srcpitch, bimg::TextureFormat::Enum(m_requestedFormat) );
				data = temp;
				srcpitch = rectpitch;
			}

			if (BX_IGNORE_C4127(true
			&&  !unpackRowLength
			&&  !convert) )
			{
				bimg::imageCopy(temp, width, height, 1, bpp, srcpitch, data);
				data = temp;
			}

			GL_CHECK(texSubImage(target+_side
				, _mip
				, rect.m_x
				, rect.m_y
				, _z
				, rect.m_width
				, rect.m_height
				, _depth
				, m_fmt
				, m_type
				, data
				) );
		}

		if (!convert
		&&  unpackRowLength)
		{
			GL_CHECK(glPixelStorei(GL_UNPACK_ROW_LENGTH, 0) );
		}

		if (NULL != temp)
		{
			bx::free(g_allocator, temp);
		}
	}

	void TextureGL::setSamplerState(uint32_t _flags, const float _rgba[4])
	{
		if (!s_renderGL->m_gles3
		&&  !s_textureFilter[m_textureFormat])
		{
			// Force point sampling when texture format doesn't support linear sampling.
			_flags &= ~(0
				| BGFX_SAMPLER_MIN_MASK
				| BGFX_SAMPLER_MAG_MASK
				| BGFX_SAMPLER_MIP_MASK
				);
			_flags |= 0
				| BGFX_SAMPLER_MIN_POINT
				| BGFX_SAMPLER_MAG_POINT
				| BGFX_SAMPLER_MIP_POINT
				;
		}

		const uint32_t flags = (0 != (BGFX_SAMPLER_INTERNAL_DEFAULT & _flags) ? m_flags : _flags) & BGFX_SAMPLER_BITS_MASK;

		bool hasBorderColor = false;
		bx::HashMurmur2A murmur;
		murmur.begin();
		murmur.add(flags);
		if (NULL != _rgba)
		{
			if (BGFX_SAMPLER_U_BORDER == (flags & BGFX_SAMPLER_U_BORDER)
			||  BGFX_SAMPLER_V_BORDER == (flags & BGFX_SAMPLER_V_BORDER)
			||  BGFX_SAMPLER_W_BORDER == (flags & BGFX_SAMPLER_W_BORDER) )
			{
				murmur.add(_rgba, 16);
				hasBorderColor = true;
			}
		}
		uint32_t hash = murmur.end();

		if (hash != m_currentSamplerHash)
		{
			const GLenum  target     = m_target == GL_TEXTURE_2D_MULTISAMPLE ? GL_TEXTURE_2D : m_target;
			const GLenum  targetMsaa = m_target;
			const uint8_t numMips    = m_numMips;

			GL_CHECK(glTexParameteri(target, GL_TEXTURE_WRAP_S, s_textureAddress[(flags&BGFX_SAMPLER_U_MASK)>>BGFX_SAMPLER_U_SHIFT]) );
			GL_CHECK(glTexParameteri(target, GL_TEXTURE_WRAP_T, s_textureAddress[(flags&BGFX_SAMPLER_V_MASK)>>BGFX_SAMPLER_V_SHIFT]) );

			if (BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGL) || s_renderGL->m_gles3
			||  s_extension[Extension::APPLE_texture_max_level].m_supported)
			{
				GL_CHECK(glTexParameteri(targetMsaa, GL_TEXTURE_MAX_LEVEL, numMips-1) );
			}

			if (target == GL_TEXTURE_3D)
			{
				GL_CHECK(glTexParameteri(target, GL_TEXTURE_WRAP_R, s_textureAddress[(flags&BGFX_SAMPLER_W_MASK)>>BGFX_SAMPLER_W_SHIFT]) );
			}

			GLenum magFilter;
			GLenum minFilter;
			getFilters(flags, 1 < numMips, magFilter, minFilter);
			GL_CHECK(glTexParameteri(target, GL_TEXTURE_MAG_FILTER, magFilter) );
			GL_CHECK(glTexParameteri(target, GL_TEXTURE_MIN_FILTER, minFilter) );

			if (BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGL) )
			{
				GL_CHECK(glTexParameterf(target, GL_TEXTURE_LOD_BIAS, float(BGFX_CONFIG_MIP_LOD_BIAS) ) );
			}

			if (s_renderGL->m_borderColorSupport
			&&  hasBorderColor)
			{
				GL_CHECK(glTexParameterfv(target, GL_TEXTURE_BORDER_COLOR, _rgba) );
			}

			if (0 != (flags & (BGFX_SAMPLER_MIN_ANISOTROPIC|BGFX_SAMPLER_MAG_ANISOTROPIC) )
			&&  0.0f < s_renderGL->m_maxAnisotropy)
			{
				GL_CHECK(glTexParameterf(target, GL_TEXTURE_MAX_ANISOTROPY_EXT, s_renderGL->m_maxAnisotropy) );
			}

			if (s_renderGL->m_gles3
			||  s_renderGL->m_shadowSamplersSupport)
			{
				const uint32_t cmpFunc = (flags&BGFX_SAMPLER_COMPARE_MASK)>>BGFX_SAMPLER_COMPARE_SHIFT;
				if (0 == cmpFunc)
				{
					GL_CHECK(glTexParameteri(target, GL_TEXTURE_COMPARE_MODE, GL_NONE) );
				}
				else
				{
					GL_CHECK(glTexParameteri(target, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE) );
					GL_CHECK(glTexParameteri(target, GL_TEXTURE_COMPARE_FUNC, s_cmpFunc[cmpFunc]) );
				}
			}

			m_currentSamplerHash = hash;
		}
	}

	void TextureGL::commit(uint32_t _stage, uint32_t _flags, const float _palette[][4])
	{
		const uint32_t flags = 0 == (BGFX_SAMPLER_INTERNAL_DEFAULT & _flags)
			? _flags
			: uint32_t(m_flags)
			;
		const uint32_t index = (flags & BGFX_SAMPLER_BORDER_COLOR_MASK) >> BGFX_SAMPLER_BORDER_COLOR_SHIFT;

		GL_CHECK(glActiveTexture(GL_TEXTURE0+_stage) );
		GL_CHECK(glBindTexture(m_target, m_id) );

		if (s_renderGL->m_samplerObjectSupport)
		{
			s_renderGL->setSamplerState(_stage, m_numMips, flags, _palette[index]);
		}
		else
		{
			setSamplerState(flags, _palette[index]);
		}
	}

	void TextureGL::resolve(uint8_t _resolve) const
	{
		const bool renderTarget = 0 != (m_flags&BGFX_TEXTURE_RT_MASK);
		if (renderTarget
		&&  1 < m_numMips
		&&  0 != (_resolve & BGFX_RESOLVE_AUTO_GEN_MIPS) )
		{
			GL_CHECK(glBindTexture(m_target, m_id) );
			GL_CHECK(glGenerateMipmap(m_target) );
			GL_CHECK(glBindTexture(m_target, 0) );
		}
	}

	void strins(char* _str, const char* _insert)
	{
		size_t len = bx::strLen(_insert);
		bx::memMove(&_str[len], _str, bx::strLen(_str)+1);
		bx::memCopy(_str, _insert, len);
	}

	void ShaderGL::create(const Memory* _mem)
	{
		bx::MemoryReader reader(_mem->data, _mem->size);
		m_hash = bx::hash<bx::HashMurmur2A>(_mem->data, _mem->size);

		bx::ErrorAssert err;

		uint32_t magic;
		bx::read(&reader, magic, &err);

		if (isShaderType(magic, 'C') )
		{
			m_type = GL_COMPUTE_SHADER;
		}
		else if (isShaderType(magic, 'F') )
		{
			m_type = GL_FRAGMENT_SHADER;
		}
		else if (isShaderType(magic, 'V') )
		{
			m_type = GL_VERTEX_SHADER;
		}

		uint32_t hashIn;
		bx::read(&reader, hashIn, &err);

		uint32_t hashOut;

		if (isShaderVerLess(magic, 6) )
		{
			hashOut = hashIn;
		}
		else
		{
			bx::read(&reader, hashOut, &err);
		}

		uint16_t count;
		bx::read(&reader, count, &err);

		BX_TRACE("%s Shader consts %d"
			, getShaderTypeName(magic)
			, count
			);

		for (uint32_t ii = 0; ii < count; ++ii)
		{
			uint8_t nameSize = 0;
			bx::read(&reader, nameSize, &err);

			char name[256];
			bx::read(&reader, &name, nameSize, &err);
			name[nameSize] = '\0';

			uint8_t type;
			bx::read(&reader, type, &err);

			uint8_t num;
			bx::read(&reader, num, &err);

			uint16_t regIndex;
			bx::read(&reader, regIndex, &err);

			uint16_t regCount;
			bx::read(&reader, regCount, &err);

			if (!isShaderVerLess(magic, 8) )
			{
				uint16_t texInfo = 0;
				bx::read(&reader, texInfo, &err);
			}

			if (!isShaderVerLess(magic, 10) )
			{
				uint16_t texFormat = 0;
				bx::read(&reader, texFormat, &err);
			}
		}

		uint32_t shaderSize;
		bx::read(&reader, shaderSize, &err);

		m_id = glCreateShader(m_type);
		BX_WARN(0 != m_id, "Failed to create shader.");

		bx::StringView code( (const char*)reader.getDataPtr(), shaderSize);

		if (0 != m_id)
		{
			if (GL_COMPUTE_SHADER != m_type
			&&  0 != bx::strCmp(code, "#version", 8) ) // #2000
			{
				int32_t tempLen = code.getLength() + (4<<10);
				char* temp = (char*)alloca(tempLen);
				bx::StaticMemoryBlockWriter writer(temp, tempLen);

				if (BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGLES)
				&&  !s_renderGL->m_gles3)
				{
					bx::write(&writer
						, "#define centroid\n"
						  "#define flat\n"
						  "#define noperspective\n"
						  "#define smooth\n"
						, &err
						);

					bool usesDerivatives = s_extension[Extension::OES_standard_derivatives].m_supported
						&& !bx::findIdentifierMatch(code, s_OES_standard_derivatives).isEmpty()
						;

					const bool usesFragData         = !bx::findIdentifierMatch(code, "gl_FragData").isEmpty();
					const bool usesFragDepth        = !bx::findIdentifierMatch(code, "gl_FragDepth").isEmpty();
					const bool usesShadowSamplers   = !bx::findIdentifierMatch(code, s_EXT_shadow_samplers).isEmpty();
					const bool usesTextureLod       = !bx::findIdentifierMatch(code, s_EXT_shader_texture_lod).isEmpty();
					const bool usesFragmentOrdering = !bx::findIdentifierMatch(code, "beginFragmentShaderOrdering").isEmpty();

					const bool usesTexture3D = true
						&& s_extension[Extension::OES_texture_3D].m_supported
						&& !bx::findIdentifierMatch(code, s_texture3D).isEmpty()
						;

					if (usesDerivatives)
					{
						bx::write(&writer, "#extension GL_OES_standard_derivatives : enable\n", &err);
					}

					if (usesFragData)
					{
						BX_WARN(s_extension[Extension::EXT_draw_buffers  ].m_supported
							||  s_extension[Extension::WEBGL_draw_buffers].m_supported
							, "EXT_draw_buffers is used but not supported by GLES2 driver."
							);
						bx::write(&writer, "#extension GL_EXT_draw_buffers : enable\n", &err);
					}

					bool insertFragDepth = false;
					if (usesFragDepth)
					{
						BX_WARN(s_extension[Extension::EXT_frag_depth].m_supported, "EXT_frag_depth is used but not supported by GLES2 driver.");
						if (s_extension[Extension::EXT_frag_depth].m_supported)
						{
							bx::write(&writer
								, "#extension GL_EXT_frag_depth : enable\n"
								  "#define bgfx_FragDepth gl_FragDepthEXT\n"
								, &err
								);

							char str[128];
							bx::snprintf(str, BX_COUNTOF(str), "%s float gl_FragDepthEXT;\n"
								, s_extension[Extension::OES_fragment_precision_high].m_supported ? "highp" : "mediump"
								);
							bx::write(&writer, str, &err);
						}
						else
						{
							insertFragDepth = true;
						}
					}

					if (usesShadowSamplers)
					{
						if (s_renderGL->m_shadowSamplersSupport)
						{
							bx::write(&writer
								, "#extension GL_EXT_shadow_samplers : enable\n"
								  "#define shadow2D shadow2DEXT\n"
								  "#define shadow2DProj shadow2DProjEXT\n"
								, &err
								);
						}
						else
						{
							bx::write(&writer
								, "#define sampler2DShadow sampler2D\n"
								  "#define shadow2D(_sampler, _coord) step(_coord.z, texture2D(_sampler, _coord.xy).x)\n"
								  "#define shadow2DProj(_sampler, _coord) step(_coord.z/_coord.w, texture2DProj(_sampler, _coord).x)\n"
								, &err
								);
						}
					}

					if (usesTexture3D)
					{
						bx::write(&writer, "#extension GL_OES_texture_3D : enable\n", &err);
					}

					if (usesTextureLod)
					{
						BX_WARN(s_extension[Extension::ARB_shader_texture_lod].m_supported
							|| s_extension[Extension::EXT_shader_texture_lod].m_supported
							, "(ARB|EXT)_shader_texture_lod is used but not supported by GLES2 driver."
							);

						if (s_extension[Extension::ARB_shader_texture_lod].m_supported)
						{
							bx::write(&writer
								, "#extension GL_ARB_shader_texture_lod : enable\n"
								  "#define texture2DLod      texture2DLodARB\n"
								  "#define texture2DProjLod  texture2DProjLodARB\n"
								  "#define textureCubeLod    textureCubeLodARB\n"
								  "#define texture2DGrad     texture2DGradARB\n"
								  "#define texture2DProjGrad texture2DProjGradARB\n"
								  "#define textureCubeGrad   textureCubeGradARB\n"
								, &err
								);
						}
						else
						{
							if (s_extension[Extension::EXT_shader_texture_lod].m_supported)
							{
								bx::write(&writer
									, "#extension GL_EXT_shader_texture_lod : enable\n"
									  "#define texture2DLod     texture2DLodEXT\n"
									  "#define texture2DProjLod texture2DProjLodEXT\n"
									  "#define textureCubeLod   textureCubeLodEXT\n"
									, &err
									);
							}
							else
							{
								bx::write(&writer
									, "#define texture2DLod(_sampler, _coord, _level) texture2D(_sampler, _coord)\n"
									  "#define texture2DProjLod(_sampler, _coord, _level) texture2DProj(_sampler, _coord)\n"
									  "#define textureCubeLod(_sampler, _coord, _level) textureCube(_sampler, _coord)\n"
									, &err
									);
							}
						}
					}

					if (usesFragmentOrdering)
					{
						if (s_extension[Extension::INTEL_fragment_shader_ordering].m_supported)
						{
							bx::write(&writer, "#extension GL_INTEL_fragment_shader_ordering : enable\n", &err);
						}
						else
						{
							bx::write(&writer, "#define beginFragmentShaderOrdering()\n", &err);
						}
					}

					bx::write(&writer, &err, "precision %s float;\n"
						, m_type == GL_FRAGMENT_SHADER ? "mediump" : "highp"
						);

					bx::write(&writer, code, &err);
					bx::write(&writer, '\0', &err);

					if (insertFragDepth)
					{
						bx::StringView shader(temp);
						bx::StringView entry = bx::strFind(shader, "void main ()");
						if (!entry.isEmpty() )
						{
							entry.set(entry.getTerm(), shader.getTerm() );
							bx::StringView brace = bx::strFind(entry, "{");
							if (!brace.isEmpty() )
							{
								bx::StringView block = bx::strFindBlock(bx::StringView(brace.getPtr(), shader.getTerm() ), '{', '}');
								if (!block.isEmpty() )
								{
									strins(const_cast<char*>(brace.getPtr()+1), "\n  float bgfx_FragDepth = 0.0;\n");
								}
							}
						}
					}

					// Replace all instances of gl_FragDepth with bgfx_FragDepth.
					for (bx::StringView fragDepth = bx::findIdentifierMatch(temp, "gl_FragDepth")
						; !fragDepth.isEmpty()
						; fragDepth = bx::findIdentifierMatch(fragDepth.getPtr(), "gl_FragDepth")
						)
					{
						char* insert = const_cast<char*>(fragDepth.getPtr() );
						strins(insert, "bg");
						bx::memCopy(insert + 2, "fx", 2);
					}
				}
				else if (BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGL)
					 &&  BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGL <= 21) )
				{
					const bool usesTextureLod = true
						&& s_extension[Extension::ARB_shader_texture_lod].m_supported
						&& !bx::findIdentifierMatch(code, s_ARB_shader_texture_lod).isEmpty()
						;

					const bool usesVertexID = true
						&& !s_extension[Extension::EXT_gpu_shader4].m_supported
						&& !bx::findIdentifierMatch(code, "gl_VertexID").isEmpty()
						;

					const bool usesInstanceID = true
						&& !s_extension[Extension::EXT_gpu_shader4].m_supported
						&& !bx::findIdentifierMatch(code, "gl_InstanceID").isEmpty()
						;

					const bool usesGpuShader4 = true
						&& s_extension[Extension::EXT_gpu_shader4].m_supported
						&& !bx::findIdentifierMatch(code, s_EXT_gpu_shader4).isEmpty()
						;

					// GpuShader5 extension is not supported on the fragment shader!
					const bool usesGpuShader5 = true
						&& m_type != GL_FRAGMENT_SHADER
						&& !bx::findIdentifierMatch(code, s_ARB_gpu_shader5).isEmpty()
						;

					const bool usesViewportLayerArray = true
						&& s_extension[Extension::ARB_shader_viewport_layer_array].m_supported
						&& !bx::findIdentifierMatch(code, s_ARB_shader_viewport_layer_array).isEmpty()
						;

					const bool usesIUsamplers   = !bx::findIdentifierMatch(code, s_uisamplers).isEmpty();
					const bool usesUint         = !bx::findIdentifierMatch(code, s_uint).isEmpty();
					const bool usesTexelFetch   = !bx::findIdentifierMatch(code, s_texelFetch).isEmpty();
					const bool usesTextureArray = !bx::findIdentifierMatch(code, s_textureArray).isEmpty();
					const bool usesTexture3D    = !bx::findIdentifierMatch(code, s_texture3D).isEmpty();
					const bool usesTextureMS    = !bx::findIdentifierMatch(code, s_ARB_texture_multisample).isEmpty();
					const bool usesPacking      = !bx::findIdentifierMatch(code, s_ARB_shading_language_packing).isEmpty();
					const bool usesInterpQ      = !bx::findIdentifierMatch(code, s_intepolationQualifier).isEmpty();

					uint32_t version = false
						|| usesTextureArray
						|| usesTexture3D
						|| usesIUsamplers
						|| usesVertexID
						|| usesUint
						|| usesTexelFetch
					    || usesGpuShader4
						|| usesGpuShader5
						|| usesInterpQ
						? 130
						: 120
						;

					version = 0 == bx::strCmp(code, "#version 430", 12) ? 430 : version;

					bx::write(&writer, &err, "#version %d\n", version);

					if (430 > version && usesTextureLod)
					{
						if (m_type == GL_FRAGMENT_SHADER)
						{
							bx::write(&writer
								, "#extension GL_ARB_shader_texture_lod : enable\n"
								  "#define texture2DGrad     texture2DGradARB\n"
								  "#define texture2DProjGrad texture2DProjGradARB\n"
								  "#define textureCubeGrad   textureCubeGradARB\n"
								, &err
								);
						}
					}

					if (usesInstanceID)
					{
						bx::write(&writer, "#extension GL_ARB_draw_instanced : enable\n", &err);
					}

					if (usesGpuShader4)
					{
						bx::write(&writer, "#extension GL_EXT_gpu_shader4 : enable\n", &err);
					}

					if (usesGpuShader5)
					{
						bx::write(&writer, "#extension GL_ARB_gpu_shader5 : enable\n", &err);
					}

					if (usesViewportLayerArray)
					{
						bx::write(&writer, "#extension GL_ARB_shader_viewport_layer_array : enable\n", &err);
					}

					if (usesPacking)
					{
						bx::write(&writer, "#extension GL_ARB_shading_language_packing : enable\n", &err);
					}

					if (usesTextureMS)
					{
						bx::write(&writer, "#extension GL_ARB_texture_multisample : enable\n", &err);
					}

					if (usesTextureArray)
					{
						bx::write(&writer, "#extension GL_EXT_texture_array : enable\n", &err);
						bx::write(&writer, "#define texture2DArrayLodEXT texture2DArrayLod\n", &err);
						bx::write(&writer, "#define textureArray texture\n", &err);
					}

					if (usesTexture3D)
					{
						bx::write(&writer, "#define texture3DEXT texture3D\n", &err);
						bx::write(&writer, "#define texture3DLodEXT texture3DLod\n", &err);
					}

					if (130 <= version)
					{
						if (430 > version)
						{
							if (m_type == GL_FRAGMENT_SHADER)
							{
								bx::write(&writer, "#define varying in\n", &err);
							}
							else
							{
								bx::write(&writer, "#define attribute in\n", &err);
								bx::write(&writer, "#define varying out\n", &err);
							}
						}

						uint32_t fragData = 0;

						if (!bx::findIdentifierMatch(code, "gl_FragData").isEmpty() )
						{
							for (uint32_t ii = 0, num = g_caps.limits.maxFBAttachments; ii < num; ++ii)
							{
								char tmpFragData[16];
								bx::snprintf(tmpFragData, BX_COUNTOF(tmpFragData), "gl_FragData[%d]", ii);
								fragData = bx::uint32_max(fragData, bx::strFind(code, tmpFragData).isEmpty() ? 0 : ii+1);
							}

							BGFX_FATAL(0 != fragData, Fatal::InvalidShader, "Unable to find and patch gl_FragData!");
						}

						if (0 != fragData)
						{
							bx::write(&writer, &err, "out vec4 bgfx_FragData[%d];\n", fragData);
							bx::write(&writer, "#define gl_FragData bgfx_FragData\n", &err);
						}
						else if (!bx::findIdentifierMatch(code, "gl_FragColor").isEmpty() )
						{
							bx::write(&writer
								, "out vec4 bgfx_FragColor;\n"
								  "#define gl_FragColor bgfx_FragColor\n"
								, &err
								);
						}
					}
					else
					{
						if (m_type == GL_FRAGMENT_SHADER)
						{
							bx::write(&writer, "#define in varying\n", &err);
						}
						else
						{
							bx::write(&writer
								, "#define in attribute\n"
								  "#define out varying\n"
								, &err
								);
						}
					}

					bx::write(&writer
						, "#define lowp\n"
						  "#define mediump\n"
						  "#define highp\n"
						, &err
						);

					if (!usesInterpQ)
					{
						bx::write(&writer
							,
							  "#define centroid\n"
							  "#define flat\n"
							  "#define noperspective\n"
							  "#define smooth\n"
							, &err
							);
					}

					if (version == 430)
					{
						int32_t verLen = bx::strLen("#version 430\n");
						bx::write(&writer, code.getPtr()+verLen, code.getLength()-verLen, &err);
					}
					else
					{
						bx::write(&writer, code, &err);
					}

					bx::write(&writer, '\0', &err);
				}
				else if (BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGL   >= 31)
					 ||  s_renderGL->m_gles3)
				{
					if (s_renderGL->m_gles3)
					{
						bx::write(&writer, &err
							, "#version 300 es\n"
							  "precision %s float;\n"
							, m_type == GL_FRAGMENT_SHADER ? "mediump" : "highp"
							);
					}
					else
					{
						bx::write(&writer, "#version 140\n", &err);
					}

					bx::write(&writer
						, "#define texture2DLod    textureLod\n"
						  "#define texture3DLod    textureLod\n"
						  "#define textureCubeLod  textureLod\n"
						  "#define texture2DGrad   textureGrad\n"
						  "#define texture3DGrad   textureGrad\n"
						  "#define textureCubeGrad textureGrad\n"
						, &err
						);

					if (m_type == GL_FRAGMENT_SHADER)
					{
						bx::write(&writer
							, "#define varying        in\n"
							  "#define texture2D      texture\n"
							  "#define texture2DArray texture\n"
							  "#define texture2DProj  textureProj\n"
							, &err
							);

						if (BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGL) )
						{
							bx::write(&writer
								, "#define shadow2D(_sampler, _coord) vec2(textureProj(_sampler, vec4(_coord, 1.0) ) )\n"
								  "#define shadow2DProj(_sampler, _coord) vec2(textureProj(_sampler, _coord) )\n"
								, &err
								);
						}
						else
						{
							bx::write(&writer
								, "#define shadow2D(_sampler, _coord) (textureProj(_sampler, vec4(_coord, 1.0) ) )\n"
								  "#define shadow2DProj(_sampler, _coord) (textureProj(_sampler, _coord) )\n"
								, &err
								);
						}

						bx::write(&writer
							, "#define texture3D   texture\n"
							  "#define textureCube texture\n"
							, &err
							);

						uint32_t fragData = 0;

						bool patchedFragData = s_renderGL->m_gles3 && !bx::findIdentifierMatch(code, "bgfx_FragData").isEmpty();

						if (!patchedFragData && !bx::findIdentifierMatch(code, "gl_FragData").isEmpty() )
						{
							for (uint32_t ii = 0, num = g_caps.limits.maxFBAttachments; ii < num; ++ii)
							{
								char tmpFragData[16];
								bx::snprintf(tmpFragData, BX_COUNTOF(tmpFragData), "gl_FragData[%d]", ii);
								fragData = bx::max(fragData, bx::strFind(code, tmpFragData).isEmpty() ? 0 : ii+1);
							}

							BGFX_FATAL(0 != fragData, Fatal::InvalidShader, "Unable to find and patch gl_FragData!");
						}

						if (!bx::findIdentifierMatch(code, "beginFragmentShaderOrdering").isEmpty() )
						{
							if (s_extension[Extension::INTEL_fragment_shader_ordering].m_supported)
							{
								bx::write(&writer, "#extension GL_INTEL_fragment_shader_ordering : enable\n", &err);
							}
							else
							{
								bx::write(&writer, "#define beginFragmentShaderOrdering()\n", &err);
							}
						}

						if (!bx::findIdentifierMatch(code, s_ARB_texture_multisample).isEmpty() )
						{
							bx::write(&writer, "#extension GL_ARB_texture_multisample : enable\n", &err);
						}

						if (0 != fragData)
						{
							if (!patchedFragData)
							{
								bx::write(&writer, &err, "out vec4 bgfx_FragData[%d];\n", fragData);
								bx::write(&writer, "#define gl_FragData bgfx_FragData\n", &err);
							}
						}
						else if (!patchedFragData)
						{
							if (bx::findIdentifierMatch(code, "bgfx_FragColor").isEmpty() )
							{
								bx::write(&writer
									, "out vec4 bgfx_FragColor;\n"
									  "#define gl_FragColor bgfx_FragColor\n"
									, &err
									);
							}
						}
					}
					else
					{
						bx::write(&writer
							, "#define attribute in\n"
							  "#define varying   out\n"
							, &err
							);
					}

					if (!s_renderGL->m_gles3)
					{
						bx::write(&writer
							, "#define lowp\n"
							  "#define mediump\n"
							  "#define highp\n"
							, &err
							);
					}

					bx::write(&writer, code.getPtr(), code.getLength(), &err);
					bx::write(&writer, '\0', &err);
				}

				code.set(temp);
			}
			else if (GL_COMPUTE_SHADER == m_type)
			{
				int32_t codeLen = (int32_t)bx::strLen(code);
				int32_t tempLen = codeLen + (4<<10);
				char* temp = (char*)alloca(tempLen);
				bx::StaticMemoryBlockWriter writer(temp, tempLen);

				int32_t verLen = 0;
				if (s_renderGL->m_gles3)
				{
					const char* str = "#version 310 es\n";
					verLen = bx::strLen(str);
					bx::write(&writer, &err, str);
				}
				else
				{
					const char* str = "#version 430\n";
					verLen = bx::strLen(str);
					bx::write(&writer, &err, str);
				}

				bx::write(&writer
					, "#define texture2DLod             textureLod\n"
					  "#define texture2DLodOffset       textureLodOffset\n"
					  "#define texture2DArrayLod        textureLod\n"
					  "#define texture2DArrayLodOffset  textureLodOffset\n"
					  "#define texture3DLod             textureLod\n"
					  "#define textureCubeLod           textureLod\n"
					  "#define texture2DGrad            textureGrad\n"
					  "#define texture3DGrad            textureGrad\n"
					  "#define textureCubeGrad          textureGrad\n"
					, &err
					);

				bx::write(&writer, code.getPtr()+verLen, codeLen-verLen, &err);
				bx::write(&writer, '\0', &err);

				code = temp;
			}

			{
				const GLchar* str = (const GLchar*)code.getPtr();
				int32_t len = code.getLength();
				GL_CHECK(glShaderSource(m_id, 1, &str, &len) );
			}

			GL_CHECK(glCompileShader(m_id) );

			GLint compiled = 0;
			GL_CHECK(glGetShaderiv(m_id, GL_COMPILE_STATUS, &compiled) );

			if (0 == compiled)
			{
				bx::LineReader lineReader(code);
				for (int32_t line = 1; !lineReader.isDone(); ++line)
				{
					bx::StringView str = lineReader.next();
					BX_TRACE("%3d %.*s", line, str.getLength(), str.getPtr() );
					BX_UNUSED(str, line);
				}

				GLsizei len;
				char log[1024];
				GL_CHECK(glGetShaderInfoLog(m_id, sizeof(log), &len, log) );

				GL_CHECK(glDeleteShader(m_id) );
				m_id = 0;
				BGFX_FATAL(false, bgfx::Fatal::InvalidShader, "Failed to compile shader. %d: %s", compiled, log);
			}
			else if (BX_ENABLED(BGFX_CONFIG_DEBUG)
				 &&  s_extension[Extension::ANGLE_translated_shader_source].m_supported
				 &&  NULL != glGetTranslatedShaderSourceANGLE)
			{
				GLsizei len;
				GL_CHECK(glGetShaderiv(m_id, GL_TRANSLATED_SHADER_SOURCE_LENGTH_ANGLE, &len) );

				char* source = (char*)alloca(len);
				GL_CHECK(glGetTranslatedShaderSourceANGLE(m_id, len, &len, source) );

				BX_TRACE("ANGLE source (len: %d):\n%s\n####", len, source);
			}
		}
	}

	void ShaderGL::destroy()
	{
		if (0 != m_id)
		{
			GL_CHECK(glDeleteShader(m_id) );
			m_id = 0;
		}
	}

	void FrameBufferGL::create(uint8_t _num, const Attachment* _attachment)
	{
		GL_CHECK(glGenFramebuffers(1, &m_fbo[0]) );

		m_denseIdx = UINT16_MAX;
		m_numTh = _num;
		bx::memCopy(m_attachment, _attachment, _num*sizeof(Attachment) );

		m_needPresent = false;

		postReset();
	}

	void FrameBufferGL::postReset()
	{
		if (0 != m_fbo[0])
		{
			GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_fbo[0]) );

			bool needResolve = false;

			GLenum buffers[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];

			uint32_t colorIdx = 0;
			for (uint32_t ii = 0; ii < m_numTh; ++ii)
			{
				const Attachment& at = m_attachment[ii];

				if (isValid(at.handle) )
				{
					const TextureGL& texture = s_renderGL->m_textures[at.handle.idx];

					if (0 == colorIdx)
					{
						m_width  = bx::uint32_max(texture.m_width  >> at.mip, 1);
						m_height = bx::uint32_max(texture.m_height >> at.mip, 1);
					}

					GLenum attachment = GL_COLOR_ATTACHMENT0 + colorIdx;
					bimg::TextureFormat::Enum format = bimg::TextureFormat::Enum(texture.m_textureFormat);
					if (bimg::isDepth(format) )
					{
						const bimg::ImageBlockInfo& info = bimg::getBlockInfo(format);
						if (0 < info.stencilBits)
						{
							attachment = GL_DEPTH_STENCIL_ATTACHMENT;
						}
						else if (0 == info.depthBits)
						{
							attachment = GL_STENCIL_ATTACHMENT;
						}
						else
						{
							attachment = GL_DEPTH_ATTACHMENT;
						}
					}
					else if (Access::Write == at.access)
					{
						buffers[colorIdx] = attachment;
						++colorIdx;
					}

					if (0 != texture.m_rbo)
					{
						if (!(BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGL >= 30) || s_renderGL->m_gles3)
							&& GL_DEPTH_STENCIL_ATTACHMENT == attachment)
						{
							GL_CHECK(glFramebufferRenderbuffer(GL_FRAMEBUFFER
								, GL_DEPTH_ATTACHMENT
								, GL_RENDERBUFFER
								, texture.m_rbo
								) );
							GL_CHECK(glFramebufferRenderbuffer(GL_FRAMEBUFFER
								, GL_STENCIL_ATTACHMENT
								, GL_RENDERBUFFER
								, texture.m_rbo
								) );
						}
						else
						{
							GL_CHECK(glFramebufferRenderbuffer(GL_FRAMEBUFFER
								, attachment
								, GL_RENDERBUFFER
								, texture.m_rbo
								) );
						}
					}
					else
					{
						if (1 < texture.m_numLayers
						&&  !texture.isCubeMap() )
						{
							if (1 < at.numLayers)
							{
								BX_ASSERT(0 == at.layer, "Can't use start layer > 0 when binding multiple layers to a framebuffer.");

								GL_CHECK(glFramebufferTexture(GL_FRAMEBUFFER
									, attachment
									, texture.m_id
									, at.mip
									) );
							}
							else
							{
								GL_CHECK(glFramebufferTextureLayer(GL_FRAMEBUFFER
									, attachment
									, texture.m_id
									, at.mip
									, at.layer
									) );
							}
						}
						else
						{
							GLenum target = texture.isCubeMap()
								? GL_TEXTURE_CUBE_MAP_POSITIVE_X + at.layer
								: texture.m_target
								;

							GL_CHECK(glFramebufferTexture2D(GL_FRAMEBUFFER
								, attachment
								, target
								, texture.m_id
								, at.mip
								) );
						}
					}

					needResolve |= (0 != texture.m_rbo) && (0 != texture.m_id);
				}
			}

			m_num = uint8_t(colorIdx);

			if (0 == colorIdx && BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGL) )
			{
				// When only depth is attached disable draw buffer to avoid
				// GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER.
				GL_CHECK(glDrawBuffer(GL_NONE) );
			}
			else if (g_caps.limits.maxFBAttachments > 1)
			{
				GL_CHECK(glDrawBuffers(colorIdx, buffers) );
			}

			if (BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGL) || s_renderGL->m_gles3)
			{
				// Disable read buffer to avoid GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER.
				GL_CHECK(glReadBuffer(GL_NONE) );
			}

			frameBufferValidate();

			if (needResolve)
			{
				GL_CHECK(glGenFramebuffers(1, &m_fbo[1]) );
				GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_fbo[1]) );

				colorIdx = 0;
				for (uint32_t ii = 0; ii < m_numTh; ++ii)
				{
					const Attachment& at = m_attachment[ii];

					if (isValid(at.handle) )
					{
						const TextureGL& texture = s_renderGL->m_textures[at.handle.idx];

						if (0 != texture.m_id)
						{

							GLenum attachment = GL_INVALID_ENUM;
							bimg::TextureFormat::Enum format = bimg::TextureFormat::Enum(texture.m_textureFormat);
							if (bimg::isDepth(format) )
							{
								const bimg::ImageBlockInfo& info = bimg::getBlockInfo(format);
								if (0 < info.stencilBits)
								{
									attachment = GL_DEPTH_STENCIL_ATTACHMENT;
								}
								else if (0 == info.depthBits)
								{
									attachment = GL_STENCIL_ATTACHMENT;
								}
								else
								{
									attachment = GL_DEPTH_ATTACHMENT;
								}
							}
							else
							{
								attachment = GL_COLOR_ATTACHMENT0 + colorIdx;
								++colorIdx;
							}

							GLenum target = texture.isCubeMap()
								? GL_TEXTURE_CUBE_MAP_POSITIVE_X + at.layer
								: texture.m_target
								;

							GL_CHECK(glFramebufferTexture2D(GL_FRAMEBUFFER
								, attachment
								, target
								, texture.m_id
								, at.mip
								) );
						}
					}
				}

				frameBufferValidate();
			}

			GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, s_renderGL->m_msaaBackBufferFbo) );
		}
	}

	void FrameBufferGL::create(uint16_t _denseIdx, void* _nwh, uint32_t _width, uint32_t _height, TextureFormat::Enum _format, TextureFormat::Enum _depthFormat)
	{
		BX_UNUSED(_format, _depthFormat);
		m_swapChain = s_renderGL->m_glctx.createSwapChain(_nwh, _width, _height);
		m_width     = _width;
		m_height    = _height;
		m_numTh     = 0;
		m_denseIdx  = _denseIdx;
		m_needPresent = false;
	}

	uint16_t FrameBufferGL::destroy()
	{
		if (0 != m_fbo[0])
		{
			GL_CHECK(glDeleteFramebuffers(0 == m_fbo[1] ? 1 : 2, m_fbo) );
			m_num = 0;
		}

		if (NULL != m_swapChain)
		{
			s_renderGL->m_glctx.destroySwapChain(m_swapChain);
			m_swapChain = NULL;
		}

		bx::memSet(m_fbo, 0, sizeof(m_fbo) );
		uint16_t denseIdx = m_denseIdx;
		m_denseIdx = UINT16_MAX;
		m_needPresent = false;
		m_numTh = 0;

		return denseIdx;
	}

	void FrameBufferGL::resolve()
	{
		if (0 != m_fbo[1])
		{
			uint32_t colorIdx = 0;
			for (uint32_t ii = 0; ii < m_numTh; ++ii)
			{
				const Attachment& at = m_attachment[ii];

				if (isValid(at.handle) )
				{
					const TextureGL& texture = s_renderGL->m_textures[at.handle.idx];

					const bool writeOnly = 0 != (texture.m_flags&BGFX_TEXTURE_RT_WRITE_ONLY);
					bimg::TextureFormat::Enum format = bimg::TextureFormat::Enum(texture.m_textureFormat);

					if (!bimg::isDepth(format) )
					{
						GL_CHECK(glDisable(GL_SCISSOR_TEST) );

						GL_CHECK(glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo[0]) );
						GL_CHECK(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo[1]) );

						GL_CHECK(glReadBuffer(GL_COLOR_ATTACHMENT0 + colorIdx) );
						GL_CHECK(glDrawBuffer(GL_COLOR_ATTACHMENT0 + colorIdx) );

						colorIdx++;

						GL_CHECK(glBlitFramebuffer(0
							, 0
							, m_width
							, m_height
							, 0
							, 0
							, m_width
							, m_height
							, GL_COLOR_BUFFER_BIT
							, GL_LINEAR
							) );
					}
					else if (!writeOnly)
					{
						GL_CHECK(glDisable(GL_SCISSOR_TEST) );

						GL_CHECK(glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo[0]) );
						GL_CHECK(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo[1]) );

						GL_CHECK(glBlitFramebuffer(0
							, 0
							, m_width
							, m_height
							, 0
							, 0
							, m_width
							, m_height
							, GL_DEPTH_BUFFER_BIT
							, GL_NEAREST
							) );
					}
				}
			}

			GL_CHECK(glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo[0]) );

			if (BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGL) || s_renderGL->m_gles3)
			{
				GL_CHECK(glReadBuffer(GL_NONE) );
			}

			GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, s_renderGL->m_msaaBackBufferFbo) );
		}

		for (uint32_t ii = 0; ii < m_numTh; ++ii)
		{
			const Attachment& at = m_attachment[ii];

			if (isValid(at.handle) )
			{
				const TextureGL& texture = s_renderGL->m_textures[at.handle.idx];
				texture.resolve(at.resolve);
			}
		}
	}

	void FrameBufferGL::discard(uint16_t _flags)
	{
		GLenum buffers[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS+2];
		uint32_t idx = 0;

		if (BGFX_CLEAR_NONE != (_flags & BGFX_CLEAR_DISCARD_COLOR_MASK) )
		{
			for (uint32_t ii = 0, num = m_num; ii < num; ++ii)
			{
				if (BGFX_CLEAR_NONE != (_flags & (BGFX_CLEAR_DISCARD_COLOR_0<<ii) ) )
				{
					buffers[idx++] = GL_COLOR_ATTACHMENT0 + ii;
				}
			}
		}

		uint32_t dsFlags = _flags & (BGFX_CLEAR_DISCARD_DEPTH|BGFX_CLEAR_DISCARD_STENCIL);
		if (BGFX_CLEAR_NONE != dsFlags)
		{
			if (!BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGLES)
			&&  (BGFX_CLEAR_DISCARD_DEPTH|BGFX_CLEAR_DISCARD_STENCIL) == dsFlags)
			{
				buffers[idx++] = GL_DEPTH_STENCIL_ATTACHMENT;
			}
			else if (BGFX_CLEAR_DISCARD_DEPTH == dsFlags)
			{
				buffers[idx++] = GL_DEPTH_ATTACHMENT;
			}
			else if (BGFX_CLEAR_DISCARD_STENCIL == dsFlags)
			{
				buffers[idx++] = GL_STENCIL_ATTACHMENT;
			}
		}

		GL_CHECK(glInvalidateFramebuffer(GL_FRAMEBUFFER, idx, buffers) );
	}

	void OcclusionQueryGL::create()
	{
		for (uint32_t ii = 0; ii < BX_COUNTOF(m_query); ++ii)
		{
			Query& query = m_query[ii];
			GL_CHECK(glGenQueries(1, &query.m_id) );
		}
	}

	void OcclusionQueryGL::destroy()
	{
		for (uint32_t ii = 0; ii < BX_COUNTOF(m_query); ++ii)
		{
			Query& query = m_query[ii];
			GL_CHECK(glDeleteQueries(1, &query.m_id) );
		}
	}

	void OcclusionQueryGL::begin(Frame* _render, OcclusionQueryHandle _handle)
	{
		while (0 == m_control.reserve(1) )
		{
			resolve(_render, true);
		}

		Query& query = m_query[m_control.m_current];
		GL_CHECK(glBeginQuery(GL_SAMPLES_PASSED, query.m_id) );
		query.m_handle = _handle;
	}

	void OcclusionQueryGL::end()
	{
		GL_CHECK(glEndQuery(GL_SAMPLES_PASSED) );
		m_control.commit(1);
	}

	void OcclusionQueryGL::resolve(Frame* _render, bool _wait)
	{
		while (0 != m_control.available() )
		{
			Query& query = m_query[m_control.m_read];

			if (isValid(query.m_handle) )
			{
				int32_t result;

				if (!_wait)
				{
					GL_CHECK(glGetQueryObjectiv(query.m_id, GL_QUERY_RESULT_AVAILABLE, &result) );

					if (!result)
					{
						break;
					}
				}

				GL_CHECK(glGetQueryObjectiv(query.m_id, GL_QUERY_RESULT, &result) );
				_render->m_occlusion[query.m_handle.idx] = int32_t(result);
			}

			m_control.consume(1);
		}
	}

	void OcclusionQueryGL::invalidate(OcclusionQueryHandle _handle)
	{
		const uint32_t size = m_control.m_size;

		for (uint32_t ii = 0, num = m_control.available(); ii < num; ++ii)
		{
			Query& query = m_query[(m_control.m_read + ii) % size];
			if (query.m_handle.idx == _handle.idx)
			{
				query.m_handle.idx = bgfx::kInvalidHandle;
			}
		}
	}

	void RendererContextGL::submitBlit(BlitState& _bs, uint16_t _view)
	{
		if (m_blitSupported)
		{
			while (_bs.hasItem(_view) )
			{
				const BlitItem& bi = _bs.advance();

				const TextureGL& src = m_textures[bi.m_src.idx];
				const TextureGL& dst = m_textures[bi.m_dst.idx];

				GL_CHECK(glCopyImageSubData(src.m_id
					, src.m_target
					, bi.m_srcMip
					, bi.m_srcX
					, bi.m_srcY
					, bi.m_srcZ
					, dst.m_id
					, dst.m_target
					, bi.m_dstMip
					, bi.m_dstX
					, bi.m_dstY
					, bi.m_dstZ
					, bi.m_width
					, bi.m_height
					, bx::uint32_imax(bi.m_depth, 1)
					) );
				}
		}
		else if (BX_ENABLED(BGFX_GL_CONFIG_BLIT_EMULATION) )
		{
			while (_bs.hasItem(_view) )
			{
				const BlitItem& bi = _bs.advance();

				const TextureGL& src = m_textures[bi.m_src.idx];
				const TextureGL& dst = m_textures[bi.m_dst.idx];

				BX_ASSERT(0 == bi.m_srcZ && 0 == bi.m_dstZ && 1 >= bi.m_depth
					, "Blitting 3D regions is not supported"
					);

				GLuint fbo;
				GL_CHECK(glGenFramebuffers(1, &fbo) );

				GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, fbo) );

				GL_CHECK(glFramebufferTexture2D(GL_FRAMEBUFFER
					, GL_COLOR_ATTACHMENT0
					, GL_TEXTURE_2D
					, src.m_id
					, bi.m_srcMip
					) );

				GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
				BX_ASSERT(GL_FRAMEBUFFER_COMPLETE == status, "glCheckFramebufferStatus failed 0x%08x", status);
				BX_UNUSED(status);

				GL_CHECK(glActiveTexture(GL_TEXTURE0) );
				GL_CHECK(glBindTexture(GL_TEXTURE_2D, dst.m_id) );

				GL_CHECK(glCopyTexSubImage2D(GL_TEXTURE_2D
					, bi.m_dstMip
					, bi.m_dstX
					, bi.m_dstY
					, bi.m_srcX
					, bi.m_srcY
					, bi.m_width
					, bi.m_height
					) );

				GL_CHECK(glDeleteFramebuffers(1, &fbo) );
				GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_currentFbo) );
			}
		}
	}

	void RendererContextGL::submit(Frame* _render, ClearQuad& _clearQuad, TextVideoMemBlitter& _textVideoMemBlitter)
	{
		if (_render->m_capture)
		{
			renderDocTriggerCapture();
		}

		m_glctx.makeCurrent(NULL);

		BGFX_GL_PROFILER_BEGIN_LITERAL("rendererSubmit", kColorView);

		if (0 != m_vao)
		{
			GL_CHECK(glBindVertexArray(m_vao) );
		}

		GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_backBufferFbo) );
		GL_CHECK(glFrontFace(GL_CW) );

		updateResolution(_render->m_resolution);

		int64_t timeBegin = bx::getHPCounter();
		int64_t captureElapsed = 0;

		uint32_t frameQueryIdx = UINT32_MAX;

		if (m_timerQuerySupport)
		{
			frameQueryIdx = m_gpuTimer.begin(BGFX_CONFIG_MAX_VIEWS, _render->m_frameNum);
		}

		if (0 < _render->m_iboffset)
		{
			BGFX_PROFILER_SCOPE("bgfx/Update transient index buffer", kColorResource);
			TransientIndexBuffer* ib = _render->m_transientIb;
			m_indexBuffers[ib->handle.idx].update(0, _render->m_iboffset, ib->data, true);
		}

		if (0 < _render->m_vboffset)
		{
			BGFX_PROFILER_SCOPE("bgfx/Update transient vertex buffer", kColorResource);
			TransientVertexBuffer* vb = _render->m_transientVb;
			m_vertexBuffers[vb->handle.idx].update(0, _render->m_vboffset, vb->data, true);
		}

		_render->sort();

		RenderDraw currentState;
		currentState.clear();
		currentState.m_stateFlags = BGFX_STATE_NONE;
		currentState.m_stencil    = packStencil(BGFX_STENCIL_NONE, BGFX_STENCIL_NONE);

		RenderBind currentBind;
		currentBind.clear();

		static ViewState viewState;
		viewState.reset(_render);

		ProgramHandle currentProgram = BGFX_INVALID_HANDLE;
		ProgramHandle boundProgram   = BGFX_INVALID_HANDLE;
		SortKey key;
		uint16_t view = UINT16_MAX;
		FrameBufferHandle fbh = { BGFX_CONFIG_MAX_FRAME_BUFFERS };

		BlitState bs(_render);

		int32_t resolutionHeight = _render->m_resolution.height;
		uint32_t blendFactor = 0;

		uint8_t primIndex;
		{
			const uint64_t pt = 0;
			primIndex = uint8_t(pt>>BGFX_STATE_PT_SHIFT);
		}
		PrimInfo prim = s_primInfo[primIndex];

		GL_CHECK(glPolygonMode(GL_FRONT_AND_BACK
			, _render->m_debug&BGFX_DEBUG_WIREFRAME
			? GL_LINE
			: GL_FILL
			) );

		bool wasCompute = false;
		bool viewHasScissor = false;
		Rect viewScissorRect;
		viewScissorRect.clear();
		uint16_t discardFlags = BGFX_CLEAR_NONE;

		const bool blendIndependentSupported = s_extension[Extension::ARB_draw_buffers_blend].m_supported;
		const bool computeSupported = false
			|| (BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGL) && s_extension[Extension::ARB_compute_shader].m_supported)
			||  BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGLES >= 31)
			;
		const uint32_t maxComputeBindings = g_caps.limits.maxComputeBindings;

		uint32_t statsNumPrimsSubmitted[BX_COUNTOF(s_primInfo)] = {};
		uint32_t statsNumPrimsRendered[BX_COUNTOF(s_primInfo)] = {};
		uint32_t statsNumInstances[BX_COUNTOF(s_primInfo)] = {};
		uint32_t statsNumIndices = 0;
		uint32_t statsKeyType[2] = {};

		Profiler<TimerQueryGL> profiler(
			  _render
			, m_gpuTimer
			, s_viewName
			, m_timerQuerySupport
			);

		if (m_occlusionQuerySupport)
		{
			m_occlusionQuery.resolve(_render);
		}

		if (0 == (_render->m_debug&BGFX_DEBUG_IFH) )
		{
			GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_msaaBackBufferFbo) );

			viewState.m_rect = _render->m_view[0].m_rect;
			int32_t numItems = _render->m_numRenderItems;

			for (int32_t item = 0; item < numItems;)
			{
				const uint64_t encodedKey = _render->m_sortKeys[item];
				const bool isCompute = key.decode(encodedKey, _render->m_viewRemap);
				statsKeyType[isCompute]++;

				const bool viewChanged = 0
					|| key.m_view != view
					|| item == numItems
					;

				const uint32_t itemIdx       = _render->m_sortValues[item];
				const RenderItem& renderItem = _render->m_renderItem[itemIdx];
				const RenderBind& renderBind = _render->m_renderItemBind[itemIdx];
				++item;

				if (viewChanged)
				{
					view = key.m_view;
					currentProgram = BGFX_INVALID_HANDLE;

					if (item > 1)
					{
						profiler.end();
					}

					BGFX_GL_PROFILER_END();

					if (_render->m_view[view].m_fbh.idx != fbh.idx)
					{
						fbh = _render->m_view[view].m_fbh;
						resolutionHeight = _render->m_resolution.height;
						resolutionHeight = setFrameBuffer(fbh, resolutionHeight, discardFlags);
					}

					setViewType(view, "  ");
					BGFX_GL_PROFILER_BEGIN(view, kColorView);

					profiler.begin(view);

					viewState.m_rect = _render->m_view[view].m_rect;

					const Rect& scissorRect = _render->m_view[view].m_scissor;
					viewHasScissor  = !scissorRect.isZero();
					viewScissorRect = viewHasScissor ? scissorRect : viewState.m_rect;

					GL_CHECK(glViewport(viewState.m_rect.m_x
						, resolutionHeight-viewState.m_rect.m_height-viewState.m_rect.m_y
						, viewState.m_rect.m_width
						, viewState.m_rect.m_height
						) );

					Clear& clear = _render->m_view[view].m_clear;
					discardFlags = clear.m_flags & BGFX_CLEAR_DISCARD_MASK;

					if (BGFX_CLEAR_NONE != (clear.m_flags & BGFX_CLEAR_MASK) )
					{
						clearQuad(_clearQuad, viewState.m_rect, clear, resolutionHeight, _render->m_colorPalette);
					}

					GL_CHECK(glDisable(GL_STENCIL_TEST) );
					GL_CHECK(glEnable(GL_DEPTH_TEST) );
					GL_CHECK(glDepthFunc(GL_LESS) );
					GL_CHECK(glEnable(GL_CULL_FACE) );
					GL_CHECK(glDisable(GL_BLEND) );

					submitBlit(bs, view);
				}

				if (isCompute)
				{
					if (!wasCompute)
					{
						wasCompute = true;

						setViewType(view, "C");
						BGFX_GL_PROFILER_END();
						BGFX_GL_PROFILER_BEGIN(view, kColorCompute);
					}

					if (computeSupported)
					{
						const RenderCompute& compute = renderItem.compute;

						ProgramGL& program = m_program[key.m_program.idx];
						setProgram(program.m_id);

						GLbitfield barrier = 0;
						for (uint32_t ii = 0; ii < maxComputeBindings; ++ii)
						{
							const Binding& bind = renderBind.m_bind[ii];
							if (kInvalidHandle != bind.m_idx)
							{
								switch (bind.m_type)
								{
								case Binding::Texture:
									{
										TextureGL& texture = m_textures[bind.m_idx];
										texture.commit(ii, bind.m_samplerFlags, _render->m_colorPalette);
									}
									break;

								case Binding::Image:
									{
										const TextureGL& texture = m_textures[bind.m_idx];
										GL_CHECK(glBindImageTexture(ii
											, texture.m_id
											, bind.m_mip
											, texture.isCubeMap() || texture.m_target == GL_TEXTURE_2D_ARRAY ? GL_TRUE : GL_FALSE
											, 0
											, s_access[bind.m_access]
											, s_imageFormat[bind.m_format])
											);
										barrier |= GL_SHADER_IMAGE_ACCESS_BARRIER_BIT;
									}
									break;

								case Binding::IndexBuffer:
									{
										const IndexBufferGL& buffer = m_indexBuffers[bind.m_idx];
										GL_CHECK(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, ii, buffer.m_id) );
										barrier |= GL_SHADER_STORAGE_BARRIER_BIT;
									}
									break;

								case Binding::VertexBuffer:
									{
										const VertexBufferGL& buffer = m_vertexBuffers[bind.m_idx];
										GL_CHECK(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, ii, buffer.m_id) );
										barrier |= GL_SHADER_STORAGE_BARRIER_BIT;
									}
									break;
								}
							}
						}

						if (0 != barrier)
						{
							bool constantsChanged = compute.m_uniformBegin < compute.m_uniformEnd;
							rendererUpdateUniforms(this, _render->m_uniformBuffer[compute.m_uniformIdx], compute.m_uniformBegin, compute.m_uniformEnd);

							if (constantsChanged
							&&  NULL != program.m_constantBuffer)
							{
								commit(*program.m_constantBuffer);
							}

							viewState.setPredefined<1>(this, view, program, _render, compute);

							if (isValid(compute.m_indirectBuffer) )
							{
								barrier |= GL_COMMAND_BARRIER_BIT;
								const VertexBufferGL& vb = m_vertexBuffers[compute.m_indirectBuffer.idx];
								if (currentState.m_indirectBuffer.idx != compute.m_indirectBuffer.idx)
								{
									currentState.m_indirectBuffer = compute.m_indirectBuffer;
									GL_CHECK(glBindBuffer(GL_DISPATCH_INDIRECT_BUFFER, vb.m_id) );
								}

								uint32_t numDrawIndirect = UINT32_MAX == compute.m_numIndirect
									? vb.m_size/BGFX_CONFIG_DRAW_INDIRECT_STRIDE
									: compute.m_numIndirect
									;

								uintptr_t args = compute.m_startIndirect * BGFX_CONFIG_DRAW_INDIRECT_STRIDE;
								for (uint32_t ii = 0; ii < numDrawIndirect; ++ii)
								{
									GL_CHECK(glDispatchComputeIndirect( (GLintptr)args) );
									args += BGFX_CONFIG_DRAW_INDIRECT_STRIDE;
								}
							}
							else
							{
								if (isValid(currentState.m_indirectBuffer) )
								{
									currentState.m_indirectBuffer.idx = kInvalidHandle;
									GL_CHECK(glBindBuffer(GL_DISPATCH_INDIRECT_BUFFER, 0) );
								}

								GL_CHECK(glDispatchCompute(compute.m_numX, compute.m_numY, compute.m_numZ) );
							}

							GL_CHECK(glMemoryBarrier(barrier) );
						}
					}

					continue;
				}

				bool resetState = viewChanged || wasCompute;

				if (wasCompute)
				{
					wasCompute = false;

					setViewType(view, " ");
					BGFX_GL_PROFILER_END();
					BGFX_GL_PROFILER_BEGIN(view, kColorDraw);
				}

				const RenderDraw& draw = renderItem.draw;

				const bool hasOcclusionQuery = 0 != (draw.m_stateFlags & BGFX_STATE_INTERNAL_OCCLUSION_QUERY);
				{
					const bool occluded = true
						&& isValid(draw.m_occlusionQuery)
						&& !hasOcclusionQuery
						&& !isVisible(_render, draw.m_occlusionQuery, 0 != (draw.m_submitFlags&BGFX_SUBMIT_INTERNAL_OCCLUSION_VISIBLE) )
						;

					if (occluded
					||  _render->m_frameCache.isZeroArea(viewScissorRect, draw.m_scissor) )
					{
						if (resetState)
						{
							currentState.clear();
							currentState.m_scissor = !draw.m_scissor;
							currentBind.clear();
						}

						continue;
					}
				}

				const uint64_t newFlags = draw.m_stateFlags;
				uint64_t changedFlags = currentState.m_stateFlags ^ draw.m_stateFlags;
				currentState.m_stateFlags = newFlags;

				const uint64_t newStencil = draw.m_stencil;
				uint64_t changedStencil = currentState.m_stencil ^ draw.m_stencil;
				currentState.m_stencil = newStencil;

				if (resetState)
				{
					currentState.clear();
					currentState.m_scissor = !draw.m_scissor;
					changedFlags   = BGFX_STATE_MASK;
					changedStencil = packStencil(BGFX_STENCIL_MASK, BGFX_STENCIL_MASK);
					currentState.m_stateFlags = newFlags;
					currentState.m_stencil    = newStencil;

					currentBind.clear();
				}

				uint16_t scissor = draw.m_scissor;
				if (currentState.m_scissor != scissor)
				{
					currentState.m_scissor = scissor;

					if (UINT16_MAX == scissor)
					{
						if (viewHasScissor)
						{
							GL_CHECK(glEnable(GL_SCISSOR_TEST) );
							GL_CHECK(glScissor(viewScissorRect.m_x
								, resolutionHeight-viewScissorRect.m_height-viewScissorRect.m_y
								, viewScissorRect.m_width
								, viewScissorRect.m_height
								) );
						}
						else
						{
							GL_CHECK(glDisable(GL_SCISSOR_TEST) );
						}
					}
					else
					{
						Rect scissorRect;
						scissorRect.setIntersect(viewScissorRect, _render->m_frameCache.m_rectCache.m_cache[scissor]);

						GL_CHECK(glEnable(GL_SCISSOR_TEST) );
						GL_CHECK(glScissor(scissorRect.m_x
							, resolutionHeight-scissorRect.m_height-scissorRect.m_y
							, scissorRect.m_width
							, scissorRect.m_height
							) );
					}
				}

				if (0 != changedStencil)
				{
					if (0 != newStencil)
					{
						GL_CHECK(glEnable(GL_STENCIL_TEST) );

						uint32_t bstencil = unpackStencil(1, newStencil);
						uint8_t frontAndBack = bstencil != BGFX_STENCIL_NONE && bstencil != unpackStencil(0, newStencil);

// 						uint32_t bchanged = unpackStencil(1, changedStencil);
// 						if (BGFX_STENCIL_FUNC_RMASK_MASK & bchanged)
// 						{
// 							uint32_t wmask = (bstencil&BGFX_STENCIL_FUNC_RMASK_MASK)>>BGFX_STENCIL_FUNC_RMASK_SHIFT;
// 							GL_CHECK(glStencilMask(wmask) );
// 						}

						for (uint8_t ii = 0, num = frontAndBack+1; ii < num; ++ii)
						{
							uint32_t stencil = unpackStencil(ii, newStencil);
							uint32_t changed = unpackStencil(ii, changedStencil);
							GLenum face = s_stencilFace[frontAndBack+ii];

							if ( (BGFX_STENCIL_TEST_MASK|BGFX_STENCIL_FUNC_REF_MASK|BGFX_STENCIL_FUNC_RMASK_MASK) & changed)
							{
								GLint ref = (stencil&BGFX_STENCIL_FUNC_REF_MASK)>>BGFX_STENCIL_FUNC_REF_SHIFT;
								GLint mask = (stencil&BGFX_STENCIL_FUNC_RMASK_MASK)>>BGFX_STENCIL_FUNC_RMASK_SHIFT;
								uint32_t func = (stencil&BGFX_STENCIL_TEST_MASK)>>BGFX_STENCIL_TEST_SHIFT;
								GL_CHECK(glStencilFuncSeparate(face, s_cmpFunc[func], ref, mask) );
							}

							if ( (BGFX_STENCIL_OP_FAIL_S_MASK|BGFX_STENCIL_OP_FAIL_Z_MASK|BGFX_STENCIL_OP_PASS_Z_MASK) & changed)
							{
								uint32_t sfail = (stencil&BGFX_STENCIL_OP_FAIL_S_MASK)>>BGFX_STENCIL_OP_FAIL_S_SHIFT;
								uint32_t zfail = (stencil&BGFX_STENCIL_OP_FAIL_Z_MASK)>>BGFX_STENCIL_OP_FAIL_Z_SHIFT;
								uint32_t zpass = (stencil&BGFX_STENCIL_OP_PASS_Z_MASK)>>BGFX_STENCIL_OP_PASS_Z_SHIFT;
								GL_CHECK(glStencilOpSeparate(face, s_stencilOp[sfail], s_stencilOp[zfail], s_stencilOp[zpass]) );
							}
						}
					}
					else
					{
						GL_CHECK(glDisable(GL_STENCIL_TEST) );
					}
				}

				if ( ( (0
					 | BGFX_STATE_ALPHA_REF_MASK
					 | BGFX_STATE_BLEND_ALPHA_TO_COVERAGE
					 | BGFX_STATE_BLEND_EQUATION_MASK
					 | BGFX_STATE_BLEND_INDEPENDENT
					 | BGFX_STATE_BLEND_MASK
					 | BGFX_STATE_CONSERVATIVE_RASTER
					 | BGFX_STATE_CULL_MASK
					 | BGFX_STATE_FRONT_CCW
					 | BGFX_STATE_DEPTH_TEST_MASK
					 | BGFX_STATE_LINEAA
					 | BGFX_STATE_MSAA
					 | BGFX_STATE_POINT_SIZE_MASK
					 | BGFX_STATE_PT_MASK
					 | BGFX_STATE_WRITE_A
					 | BGFX_STATE_WRITE_RGB
					 | BGFX_STATE_WRITE_Z
					 ) & changedFlags)
				|| blendFactor != draw.m_rgba)
				{
					if (BGFX_STATE_FRONT_CCW & changedFlags)
					{
						GL_CHECK(glFrontFace( (BGFX_STATE_FRONT_CCW & newFlags) ? GL_CCW : GL_CW) );
					}

					if (BGFX_STATE_CULL_MASK & changedFlags)
					{
						if (BGFX_STATE_CULL_CCW & newFlags)
						{
							GL_CHECK(glEnable(GL_CULL_FACE) );
							GL_CHECK(glCullFace(GL_BACK) );
						}
						else if (BGFX_STATE_CULL_CW & newFlags)
						{
							GL_CHECK(glEnable(GL_CULL_FACE) );
							GL_CHECK(glCullFace(GL_FRONT) );
						}
						else
						{
							GL_CHECK(glDisable(GL_CULL_FACE) );
						}
					}

					if (BGFX_STATE_WRITE_Z & changedFlags)
					{
						GL_CHECK(glDepthMask(!!(BGFX_STATE_WRITE_Z & newFlags) ) );
					}

					if (BGFX_STATE_DEPTH_TEST_MASK & changedFlags)
					{
						uint32_t func = (newFlags&BGFX_STATE_DEPTH_TEST_MASK)>>BGFX_STATE_DEPTH_TEST_SHIFT;

						if (0 != func)
						{
							GL_CHECK(glEnable(GL_DEPTH_TEST) );
							GL_CHECK(glDepthFunc(s_cmpFunc[func]) );
						}
						else
						{
							if (BGFX_STATE_WRITE_Z & newFlags)
							{
								GL_CHECK(glEnable(GL_DEPTH_TEST) );
								GL_CHECK(glDepthFunc(GL_ALWAYS) );
							}
							else
							{
								GL_CHECK(glDisable(GL_DEPTH_TEST) );
							}
						}
					}

					if (BGFX_STATE_ALPHA_REF_MASK & changedFlags)
					{
						uint32_t ref = (newFlags&BGFX_STATE_ALPHA_REF_MASK)>>BGFX_STATE_ALPHA_REF_SHIFT;
						viewState.m_alphaRef = ref/255.0f;
					}

					if (BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGL) )
					{
						if ( (BGFX_STATE_PT_POINTS|BGFX_STATE_POINT_SIZE_MASK) & changedFlags)
						{
							float pointSize = (float)(bx::uint32_max(1, (newFlags&BGFX_STATE_POINT_SIZE_MASK)>>BGFX_STATE_POINT_SIZE_SHIFT) );
							GL_CHECK(glPointSize(pointSize) );
						}

						if (BGFX_STATE_MSAA & changedFlags)
						{
							GL_CHECK(BGFX_STATE_MSAA & newFlags
								? glEnable(GL_MULTISAMPLE)
								: glDisable(GL_MULTISAMPLE)
								);
						}

						if (BGFX_STATE_LINEAA & changedFlags)
						{
							GL_CHECK(BGFX_STATE_LINEAA & newFlags
								? glEnable(GL_LINE_SMOOTH)
								: glDisable(GL_LINE_SMOOTH)
								);
						}

						if (m_conservativeRasterSupport
						&&  BGFX_STATE_CONSERVATIVE_RASTER & changedFlags)
						{
							GL_CHECK(BGFX_STATE_CONSERVATIVE_RASTER & newFlags
								? glEnable(GL_CONSERVATIVE_RASTERIZATION_NV)
								: glDisable(GL_CONSERVATIVE_RASTERIZATION_NV)
								);
						}
					}

					if ( (BGFX_STATE_WRITE_A|BGFX_STATE_WRITE_RGB) & changedFlags)
					{
						const GLboolean rr = !!(newFlags&BGFX_STATE_WRITE_R);
						const GLboolean gg = !!(newFlags&BGFX_STATE_WRITE_G);
						const GLboolean bb = !!(newFlags&BGFX_STATE_WRITE_B);
						const GLboolean aa = !!(newFlags&BGFX_STATE_WRITE_A);
						GL_CHECK(glColorMask(rr, gg, bb, aa) );
					}

					if ( ( (0
						| BGFX_STATE_BLEND_ALPHA_TO_COVERAGE
						| BGFX_STATE_BLEND_EQUATION_MASK
						| BGFX_STATE_BLEND_INDEPENDENT
						| BGFX_STATE_BLEND_MASK
						) & changedFlags)
					||  blendFactor != draw.m_rgba)
					{
						if (m_atocSupport)
						{
							if (BGFX_STATE_BLEND_ALPHA_TO_COVERAGE & newFlags)
							{
								GL_CHECK(glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE) );
							}
							else
							{
								GL_CHECK(glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE) );
							}
						}

						if ( ( (0
							| BGFX_STATE_BLEND_EQUATION_MASK
							| BGFX_STATE_BLEND_INDEPENDENT
							| BGFX_STATE_BLEND_MASK
							) & newFlags)
						||  blendFactor != draw.m_rgba)
						{
							const bool enabled = !!(BGFX_STATE_BLEND_MASK & newFlags);
							const bool independent = !!(BGFX_STATE_BLEND_INDEPENDENT & newFlags)
								&& blendIndependentSupported
								;

							const uint32_t blend  = uint32_t( (newFlags&BGFX_STATE_BLEND_MASK)>>BGFX_STATE_BLEND_SHIFT);
							const uint32_t srcRGB = (blend    )&0xf;
							const uint32_t dstRGB = (blend>> 4)&0xf;
							const uint32_t srcA   = (blend>> 8)&0xf;
							const uint32_t dstA   = (blend>>12)&0xf;

							const uint32_t equ    = uint32_t( (newFlags&BGFX_STATE_BLEND_EQUATION_MASK)>>BGFX_STATE_BLEND_EQUATION_SHIFT);
							const uint32_t equRGB = (equ   )&0x7;
							const uint32_t equA   = (equ>>3)&0x7;

							const uint32_t numRt = getNumRt();

							if (!BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGL)
							||  1 >= numRt
							||  !independent)
							{
								if (enabled)
								{
									GL_CHECK(glEnable(GL_BLEND) );
									GL_CHECK(glBlendFuncSeparate(s_blendFactor[srcRGB].m_src
										, s_blendFactor[dstRGB].m_dst
										, s_blendFactor[srcA].m_src
										, s_blendFactor[dstA].m_dst
										) );
									GL_CHECK(glBlendEquationSeparate(s_blendEquation[equRGB], s_blendEquation[equA]) );

									if ( (s_blendFactor[srcRGB].m_factor || s_blendFactor[dstRGB].m_factor)
									&&  blendFactor != draw.m_rgba)
									{
										const uint32_t rgba = draw.m_rgba;
										GLclampf rr = ( (rgba>>24)     )/255.0f;
										GLclampf gg = ( (rgba>>16)&0xff)/255.0f;
										GLclampf bb = ( (rgba>> 8)&0xff)/255.0f;
										GLclampf aa = ( (rgba    )&0xff)/255.0f;

										GL_CHECK(glBlendColor(rr, gg, bb, aa) );
									}
								}
								else
								{
									GL_CHECK(glDisable(GL_BLEND) );
								}
							}
							else
							{
								if (enabled)
								{
									GL_CHECK(glEnablei(GL_BLEND, 0) );
									GL_CHECK(glBlendFuncSeparatei(0
										, s_blendFactor[srcRGB].m_src
										, s_blendFactor[dstRGB].m_dst
										, s_blendFactor[srcA].m_src
										, s_blendFactor[dstA].m_dst
										) );
									GL_CHECK(glBlendEquationSeparatei(0
										, s_blendEquation[equRGB]
										, s_blendEquation[equA]
										) );
								}
								else
								{
									GL_CHECK(glDisablei(GL_BLEND, 0) );
								}

								for (uint32_t ii = 1, rgba = draw.m_rgba; ii < numRt; ++ii, rgba >>= 11)
								{
									if (0 != (rgba&0x7ff) )
									{
										const uint32_t src      = (rgba   )&0xf;
										const uint32_t dst      = (rgba>>4)&0xf;
										const uint32_t equation = (rgba>>8)&0x7;
										GL_CHECK(glEnablei(GL_BLEND, ii) );
										GL_CHECK(glBlendFunci(ii, s_blendFactor[src].m_src, s_blendFactor[dst].m_dst) );
										GL_CHECK(glBlendEquationi(ii, s_blendEquation[equation]) );
									}
									else
									{
										GL_CHECK(glDisablei(GL_BLEND, ii) );
									}
								}
							}
						}
						else
						{
							GL_CHECK(glDisable(GL_BLEND) );
						}

						blendFactor = draw.m_rgba;
					}

					const uint64_t pt = newFlags&BGFX_STATE_PT_MASK;
					primIndex = uint8_t(pt>>BGFX_STATE_PT_SHIFT);
					prim = s_primInfo[primIndex];
				}

				bool programChanged = false;
				bool constantsChanged = draw.m_uniformBegin < draw.m_uniformEnd;
				bool bindAttribs = false;
				rendererUpdateUniforms(this, _render->m_uniformBuffer[draw.m_uniformIdx], draw.m_uniformBegin, draw.m_uniformEnd);

				if (key.m_program.idx != currentProgram.idx)
				{
					currentProgram = key.m_program;
					GLuint id = isValid(currentProgram) ? m_program[currentProgram.idx].m_id : 0;

					// Skip rendering if program index is valid, but program is invalid.
					currentProgram = 0 == id ? ProgramHandle{kInvalidHandle} : currentProgram;

					setProgram(id);
					programChanged =
						constantsChanged =
						bindAttribs = true;
				}

				if (isValid(currentProgram) )
				{
					ProgramGL& program = m_program[currentProgram.idx];

					if (constantsChanged
					&&  NULL != program.m_constantBuffer)
					{
						commit(*program.m_constantBuffer);
					}

					viewState.setPredefined<1>(this, view, program, _render, draw);

					{
						GLbitfield barrier = 0;
						for (uint32_t stage = 0; stage < BGFX_CONFIG_MAX_TEXTURE_SAMPLERS; ++stage)
						{
							const Binding& bind = renderBind.m_bind[stage];
							Binding& current = currentBind.m_bind[stage];
							if (current.m_idx          != bind.m_idx
							||  current.m_type         != bind.m_type
							||  current.m_samplerFlags != bind.m_samplerFlags
							||  programChanged)
							{
								if (kInvalidHandle != bind.m_idx)
								{
									switch (bind.m_type)
									{
									case Binding::Image:
										{
											const TextureGL& texture = m_textures[bind.m_idx];
											GL_CHECK(glBindImageTexture(stage
																		, texture.m_id
																		, bind.m_mip
																		, texture.isCubeMap() || texture.m_target == GL_TEXTURE_2D_ARRAY ? GL_TRUE : GL_FALSE
																		, 0
																		, s_access[bind.m_access]
																		, s_imageFormat[bind.m_format])
													);
											barrier |= GL_SHADER_IMAGE_ACCESS_BARRIER_BIT;
										}
										break;

									case Binding::Texture:
										{
											TextureGL& texture = m_textures[bind.m_idx];
											texture.commit(stage, bind.m_samplerFlags, _render->m_colorPalette);
										}
										break;

									case Binding::IndexBuffer:
										{
											const IndexBufferGL& buffer = m_indexBuffers[bind.m_idx];
											GL_CHECK(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, stage, buffer.m_id) );
										}
										break;

									case Binding::VertexBuffer:
										{
											const VertexBufferGL& buffer = m_vertexBuffers[bind.m_idx];
											GL_CHECK(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, stage, buffer.m_id) );
										}
										break;
									}
								}
							}

							current = bind;
						}

						if (0 != barrier)
						{
							GL_CHECK(glMemoryBarrier(barrier) );
						}
					}

					{
						for (uint32_t idx = 0, streamMask = draw.m_streamMask
							; 0 != streamMask
							; streamMask >>= 1, idx += 1
							)
						{
							const uint32_t ntz = bx::uint32_cnttz(streamMask);
							streamMask >>= ntz;
							idx         += ntz;

							if (currentState.m_stream[idx].m_handle.idx != draw.m_stream[idx].m_handle.idx)
							{
								currentState.m_stream[idx].m_handle = draw.m_stream[idx].m_handle;
								bindAttribs = true;
							}

							if (currentState.m_stream[idx].m_startVertex != draw.m_stream[idx].m_startVertex)
							{
								currentState.m_stream[idx].m_startVertex = draw.m_stream[idx].m_startVertex;
								bindAttribs = true;
							}
						}

						if (programChanged
						||  currentState.m_streamMask             != draw.m_streamMask
						||  currentState.m_instanceDataBuffer.idx != draw.m_instanceDataBuffer.idx
						||  currentState.m_instanceDataOffset     != draw.m_instanceDataOffset
						||  currentState.m_instanceDataStride     != draw.m_instanceDataStride)
						{
							currentState.m_streamMask         = draw.m_streamMask;
							currentState.m_instanceDataBuffer = draw.m_instanceDataBuffer;
							currentState.m_instanceDataOffset = draw.m_instanceDataOffset;
							currentState.m_instanceDataStride = draw.m_instanceDataStride;

							bindAttribs = true;
						}

						if (currentState.m_indexBuffer.idx != draw.m_indexBuffer.idx)
						{
							currentState.m_indexBuffer = draw.m_indexBuffer;

							if (isValid(draw.m_indexBuffer) )
							{
								IndexBufferGL& ib = m_indexBuffers[draw.m_indexBuffer.idx];
								GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib.m_id) );
							}
							else
							{
								GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) );
							}
						}

						if (currentState.m_startIndex != draw.m_startIndex)
						{
							currentState.m_startIndex = draw.m_startIndex;
						}

						if (0 != currentState.m_streamMask)
						{
							if (bindAttribs)
							{
								if (isValid(boundProgram) )
								{
									m_program[boundProgram.idx].unbindAttributes();
									m_program[boundProgram.idx].unbindInstanceData();
								}

								boundProgram = currentProgram;

								program.bindAttributesBegin();

								if (UINT8_MAX != draw.m_streamMask)
								{
									for (uint32_t idx = 0, streamMask = draw.m_streamMask
										; 0 != streamMask
										; streamMask >>= 1, idx += 1
										)
									{
										const uint32_t ntz = bx::uint32_cnttz(streamMask);
										streamMask >>= ntz;
										idx         += ntz;

										const VertexBufferGL& vb = m_vertexBuffers[draw.m_stream[idx].m_handle.idx];
										const uint16_t decl = isValid(draw.m_stream[idx].m_layoutHandle)
											? draw.m_stream[idx].m_layoutHandle.idx
											: vb.m_layoutHandle.idx;
										GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vb.m_id) );
										program.bindAttributes(m_vertexLayouts[decl], draw.m_stream[idx].m_startVertex);
									}
								}

								if (isValid(draw.m_instanceDataBuffer) )
								{
									GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffers[draw.m_instanceDataBuffer.idx].m_id) );
									program.bindInstanceData(draw.m_instanceDataStride, draw.m_instanceDataOffset);
								}

								program.bindAttributesEnd();
							}
						}
					}

					if (0 != currentState.m_streamMask)
					{
						uint32_t numVertices = draw.m_numVertices;
						if (UINT32_MAX == numVertices)
						{
							for (uint32_t idx = 0, streamMask = draw.m_streamMask
								; 0 != streamMask
								; streamMask >>= 1, idx += 1
								)
							{
								const uint32_t ntz = bx::uint32_cnttz(streamMask);
								streamMask >>= ntz;
								idx         += ntz;

								const VertexBufferGL& vb = m_vertexBuffers[draw.m_stream[idx].m_handle.idx];
								uint16_t decl = !isValid(vb.m_layoutHandle) ? draw.m_stream[idx].m_layoutHandle.idx : vb.m_layoutHandle.idx;
								const VertexLayout& layout = m_vertexLayouts[decl];

								numVertices = bx::uint32_min(numVertices, vb.m_size/layout.m_stride);
							}
						}

						uint32_t numIndices        = 0;
						uint32_t numPrimsSubmitted = 0;
						uint32_t numInstances      = 0;
						uint32_t numPrimsRendered  = 0;
						uint32_t numDrawIndirect   = 0;

						if (hasOcclusionQuery)
						{
							m_occlusionQuery.begin(_render, draw.m_occlusionQuery);
						}

						if (isValid(draw.m_indirectBuffer) )
						{
							const VertexBufferGL& vb = m_vertexBuffers[draw.m_indirectBuffer.idx];
							if (currentState.m_indirectBuffer.idx != draw.m_indirectBuffer.idx)
							{
								currentState.m_indirectBuffer = draw.m_indirectBuffer;
								GL_CHECK(glBindBuffer(GL_DRAW_INDIRECT_BUFFER, vb.m_id) );
							}

							uint32_t numOffsetIndirect = 0;
							if (isValid(draw.m_numIndirectBuffer) )
							{
								if (currentState.m_numIndirectBuffer.idx != draw.m_numIndirectBuffer.idx)
								{
									const IndexBufferGL& nb = m_indexBuffers[draw.m_numIndirectBuffer.idx];
									currentState.m_numIndirectBuffer = draw.m_numIndirectBuffer;
									GL_CHECK(glBindBuffer(GL_PARAMETER_BUFFER_ARB, nb.m_id) );
								}

								numOffsetIndirect = draw.m_numIndirectIndex * sizeof(uint32_t);
							}

							if (isValid(draw.m_indexBuffer) )
							{
								const IndexBufferGL& ib = m_indexBuffers[draw.m_indexBuffer.idx];
								const bool hasIndex16 = 0 == (ib.m_flags & BGFX_BUFFER_INDEX32);
								const GLenum indexFormat = hasIndex16
									? GL_UNSIGNED_SHORT
									: GL_UNSIGNED_INT
									;

								numDrawIndirect = UINT32_MAX == draw.m_numIndirect
									? vb.m_size/BGFX_CONFIG_DRAW_INDIRECT_STRIDE
									: draw.m_numIndirect
									;

								uintptr_t args = draw.m_startIndirect * BGFX_CONFIG_DRAW_INDIRECT_STRIDE;

								if (isValid(draw.m_numIndirectBuffer) )
								{
									GL_CHECK(glMultiDrawElementsIndirectCount(prim.m_type, indexFormat
										, (void*)args
										, numOffsetIndirect
										, numDrawIndirect
										, BGFX_CONFIG_DRAW_INDIRECT_STRIDE
										) );
								}
								else
								{
									GL_CHECK(glMultiDrawElementsIndirect(prim.m_type, indexFormat
										, (void*)args
										, numDrawIndirect
										, BGFX_CONFIG_DRAW_INDIRECT_STRIDE
										) );
								}
							}
							else
							{
								numDrawIndirect = UINT32_MAX == draw.m_numIndirect
									? vb.m_size/BGFX_CONFIG_DRAW_INDIRECT_STRIDE
									: draw.m_numIndirect
									;

								uintptr_t args = draw.m_startIndirect * BGFX_CONFIG_DRAW_INDIRECT_STRIDE;

								if (isValid(draw.m_numIndirectBuffer) )
								{
									GL_CHECK(glMultiDrawArraysIndirectCount(prim.m_type
										, (void*)args
										, numOffsetIndirect
										, numDrawIndirect
										, BGFX_CONFIG_DRAW_INDIRECT_STRIDE
										) );
								}
								else
								{
									GL_CHECK(glMultiDrawArraysIndirect(prim.m_type
										, (void*)args
										, numDrawIndirect
										, BGFX_CONFIG_DRAW_INDIRECT_STRIDE
										) );
								}
							}
						}
						else
						{
							if (isValid(currentState.m_indirectBuffer) )
							{
								currentState.m_indirectBuffer.idx = kInvalidHandle;
								GL_CHECK(glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0) );

								if (isValid(currentState.m_numIndirectBuffer) )
								{
									currentState.m_numIndirectBuffer.idx = kInvalidHandle;
									GL_CHECK(glBindBuffer(GL_PARAMETER_BUFFER_ARB, 0) );
								}
							}

							if (isValid(draw.m_indexBuffer) )
							{
								const IndexBufferGL& ib  = m_indexBuffers[draw.m_indexBuffer.idx];
								const bool isIndex16     = draw.isIndex16();
								const uint32_t indexSize = isIndex16 ? 2 : 4;
								const GLenum indexFormat = isIndex16
									? GL_UNSIGNED_SHORT
									: GL_UNSIGNED_INT
									;

								if (UINT32_MAX == draw.m_numIndices)
								{
									numIndices        = ib.m_size/indexSize;
									numPrimsSubmitted = numIndices/prim.m_div - prim.m_sub;
									numInstances      = draw.m_numInstances;
									numPrimsRendered  = numPrimsSubmitted*draw.m_numInstances;

									GL_CHECK(glDrawElementsInstanced(prim.m_type
										, numIndices
										, indexFormat
										, (void*)0
										, draw.m_numInstances
										) );
								}
								else if (prim.m_min <= draw.m_numIndices)
								{
									numIndices        = draw.m_numIndices;
									numPrimsSubmitted = numIndices/prim.m_div - prim.m_sub;
									numInstances      = draw.m_numInstances;
									numPrimsRendered  = numPrimsSubmitted*draw.m_numInstances;

									GL_CHECK(glDrawElementsInstanced(prim.m_type
										, numIndices
										, indexFormat
										, (void*)(uintptr_t)(draw.m_startIndex*indexSize)
										, draw.m_numInstances
										) );
								}
							}
							else
							{
								numPrimsSubmitted = numVertices/prim.m_div - prim.m_sub;
								numInstances      = draw.m_numInstances;
								numPrimsRendered  = numPrimsSubmitted*draw.m_numInstances;

								GL_CHECK(glDrawArraysInstanced(prim.m_type
									, 0
									, numVertices
									, draw.m_numInstances
									) );
							}
						}

						if (hasOcclusionQuery)
						{
							m_occlusionQuery.end();
						}

						statsNumPrimsSubmitted[primIndex] += numPrimsSubmitted;
						statsNumPrimsRendered[primIndex]  += numPrimsRendered;
						statsNumInstances[primIndex]      += numInstances;
						statsNumIndices += numIndices;
					}
				}
			}

			if (isValid(boundProgram) )
			{
				m_program[boundProgram.idx].unbindAttributes();
				boundProgram = BGFX_INVALID_HANDLE;
			}

			if (wasCompute)
			{
				setViewType(view, "C");
				BGFX_GL_PROFILER_END();
				BGFX_GL_PROFILER_BEGIN(view, kColorCompute);
			}

			submitBlit(bs, BGFX_CONFIG_MAX_VIEWS);

			blitMsaaFbo();

			if (0 < _render->m_numRenderItems)
			{
				if (0 != (m_resolution.reset & BGFX_RESET_FLUSH_AFTER_RENDER) )
				{
					GL_CHECK(glFlush() );
				}

				captureElapsed = -bx::getHPCounter();
				capture();
				captureElapsed += bx::getHPCounter();

				profiler.end();
			}

			if (m_srgbWriteControlSupport)
			{
				// switch state back to default for cases when the on-screen draw is done externally
				GL_CHECK(glDisable(GL_FRAMEBUFFER_SRGB) );
			}
		}

		BGFX_GL_PROFILER_END();

		m_glctx.makeCurrent(NULL);
		int64_t timeEnd = bx::getHPCounter();
		int64_t frameTime = timeEnd - timeBegin;

		static int64_t min = frameTime;
		static int64_t max = frameTime;
		min = min > frameTime ? frameTime : min;
		max = max < frameTime ? frameTime : max;

		static uint32_t maxGpuLatency = 0;
		static double   maxGpuElapsed = 0.0f;
		double elapsedGpuMs = 0.0;

		if (UINT32_MAX != frameQueryIdx)
		{
			m_gpuTimer.end(frameQueryIdx);

			const TimerQueryGL::Result& result = m_gpuTimer.m_result[BGFX_CONFIG_MAX_VIEWS];
			double toGpuMs = 1000.0 / 1e9;
			elapsedGpuMs   = (result.m_end - result.m_begin) * toGpuMs;
			maxGpuElapsed  = elapsedGpuMs > maxGpuElapsed ? elapsedGpuMs : maxGpuElapsed;

			maxGpuLatency = bx::uint32_imax(maxGpuLatency, result.m_pending-1);
		}

		const int64_t timerFreq = bx::getHPFrequency();

		Stats& perfStats = _render->m_perfStats;
		perfStats.cpuTimeBegin  = timeBegin;
		perfStats.cpuTimeEnd    = timeEnd;
		perfStats.cpuTimerFreq  = timerFreq;
		const TimerQueryGL::Result& result = m_gpuTimer.m_result[BGFX_CONFIG_MAX_VIEWS];
		perfStats.gpuTimeBegin  = result.m_begin;
		perfStats.gpuTimeEnd    = result.m_end;
		perfStats.gpuTimerFreq  = 1000000000;
		perfStats.numDraw       = statsKeyType[0];
		perfStats.numCompute    = statsKeyType[1];
		perfStats.numBlit       = _render->m_numBlitItems;
		perfStats.maxGpuLatency = maxGpuLatency;
		perfStats.gpuFrameNum   = result.m_frameNum;
		bx::memCopy(perfStats.numPrims, statsNumPrimsRendered, sizeof(perfStats.numPrims) );
		perfStats.gpuMemoryMax  = -INT64_MAX;
		perfStats.gpuMemoryUsed = -INT64_MAX;

		if (_render->m_debug & (BGFX_DEBUG_IFH|BGFX_DEBUG_STATS) )
		{
			BGFX_GL_PROFILER_BEGIN_LITERAL("debugstats", kColorFrame);

			m_needPresent = true;
			TextVideoMem& tvm = m_textVideoMem;

			static int64_t next = timeEnd;

			if (timeEnd >= next)
			{
				next = timeEnd + timerFreq;
				double freq = double(timerFreq);
				double toMs = 1000.0/freq;

				tvm.clear();
				uint16_t pos = 0;
				tvm.printf(0, pos++, BGFX_CONFIG_DEBUG ? 0x8c : 0x8f
					, " %s / " BX_COMPILER_NAME
					  " / " BX_CPU_NAME
					  " / " BX_ARCH_NAME
					  " / " BX_PLATFORM_NAME
					  " / Version 1.%d.%d (commit: " BGFX_REV_SHA1 ")"
					, getRendererName()
					, BGFX_API_VERSION
					, BGFX_REV_NUMBER
					);

				tvm.printf(0, pos++, 0x8f, "       Vendor: %s ", m_vendor);
				tvm.printf(0, pos++, 0x8f, "     Renderer: %s ", m_renderer);
				tvm.printf(0, pos++, 0x8f, "      Version: %s ", m_version);
				tvm.printf(0, pos++, 0x8f, " GLSL version: %s ", m_glslVersion);

				char processMemoryUsed[16];
				bx::prettify(processMemoryUsed, BX_COUNTOF(processMemoryUsed), bx::getProcessMemoryUsed() );
				tvm.printf(0, pos++, 0x8f, "       Memory: %s (process) ", processMemoryUsed);

				pos = 10;
				tvm.printf(10, pos++, 0x8b, "        Frame: %7.3f, % 7.3f \x1f, % 7.3f \x1e [ms] / % 6.2f FPS "
					, double(frameTime)*toMs
					, double(min)*toMs
					, double(max)*toMs
					, freq/frameTime
					);

				const uint32_t msaa = (m_resolution.reset&BGFX_RESET_MSAA_MASK)>>BGFX_RESET_MSAA_SHIFT;
				tvm.printf(10, pos++, 0x8b, "  Reset flags: [%c] vsync, [%c] MSAAx%d, [%c] MaxAnisotropy "
					, !!(m_resolution.reset&BGFX_RESET_VSYNC) ? '\xfe' : ' '
					, 0 != msaa ? '\xfe' : ' '
					, 1<<msaa
					, !!(m_resolution.reset&BGFX_RESET_MAXANISOTROPY) ? '\xfe' : ' '
					);

				double elapsedCpuMs = double(frameTime)*toMs;
				tvm.printf(10, pos++, 0x8b, "    Submitted: %5d (draw %5d, compute %4d) / CPU %7.4f [ms] %c GPU %7.4f [ms] (latency %d) "
					, _render->m_numRenderItems
					, statsKeyType[0]
					, statsKeyType[1]
					, elapsedCpuMs
					, elapsedCpuMs > elapsedGpuMs ? '>' : '<'
					, maxGpuElapsed
					, maxGpuLatency
					);
				maxGpuLatency = 0;
				maxGpuElapsed = 0.0;

				for (uint32_t ii = 0; ii < BX_COUNTOF(s_primInfo); ++ii)
				{
					tvm.printf(10, pos++, 0x8b, "   %10s: %7d (#inst: %5d), submitted: %7d "
						, getName(Topology::Enum(ii) )
						, statsNumPrimsRendered[ii]
						, statsNumInstances[ii]
						, statsNumPrimsSubmitted[ii]
						);
				}

				if (NULL != m_renderdocdll)
				{
					tvm.printf(tvm.m_width-27, 0, 0x4f, " [F11 - RenderDoc capture] ");
				}

				tvm.printf(10, pos++, 0x8b, "      Indices: %7d ", statsNumIndices);
//				tvm.printf(10, pos++, 0x8b, " Uniform size: %7d, Max: %7d ", _render->m_uniformEnd, _render->m_uniformMax);
				tvm.printf(10, pos++, 0x8b, "     DVB size: %7d ", _render->m_vboffset);
				tvm.printf(10, pos++, 0x8b, "     DIB size: %7d ", _render->m_iboffset);

				pos++;
				tvm.printf(10, pos++, 0x8b, " State cache:     ");
				tvm.printf(10, pos++, 0x8b, " Sampler ");
				tvm.printf(10, pos++, 0x8b, " %6d  "
					, m_samplerStateCache.getCount()
					);

#if BGFX_CONFIG_RENDERER_OPENGL
				if (s_extension[Extension::ATI_meminfo].m_supported)
				{
					GLint vboFree[4];
					GL_CHECK(glGetIntegerv(GL_VBO_FREE_MEMORY_ATI, vboFree) );

					GLint texFree[4];
					GL_CHECK(glGetIntegerv(GL_TEXTURE_FREE_MEMORY_ATI, texFree) );

					GLint rbfFree[4];
					GL_CHECK(glGetIntegerv(GL_RENDERBUFFER_FREE_MEMORY_ATI, rbfFree) );

					pos++;
					tvm.printf(10, pos++, 0x8c, " -------------|    free|  free b|     aux|  aux fb ");

					char tmp0[16];
					char tmp1[16];
					char tmp2[16];
					char tmp3[16];

					bx::prettify(tmp0, BX_COUNTOF(tmp0), vboFree[0]);
					bx::prettify(tmp1, BX_COUNTOF(tmp1), vboFree[1]);
					bx::prettify(tmp2, BX_COUNTOF(tmp2), vboFree[2]);
					bx::prettify(tmp3, BX_COUNTOF(tmp3), vboFree[3]);
					tvm.printf(10, pos++, 0x8b, "           VBO: %10s, %10s, %10s, %10s ", tmp0, tmp1, tmp2, tmp3);

					bx::prettify(tmp0, BX_COUNTOF(tmp0), texFree[0]);
					bx::prettify(tmp1, BX_COUNTOF(tmp1), texFree[1]);
					bx::prettify(tmp2, BX_COUNTOF(tmp2), texFree[2]);
					bx::prettify(tmp3, BX_COUNTOF(tmp3), texFree[3]);
					tvm.printf(10, pos++, 0x8b, "       Texture: %10s, %10s, %10s, %10s ", tmp0, tmp1, tmp2, tmp3);

					bx::prettify(tmp0, BX_COUNTOF(tmp0), rbfFree[0]);
					bx::prettify(tmp1, BX_COUNTOF(tmp1), rbfFree[1]);
					bx::prettify(tmp2, BX_COUNTOF(tmp2), rbfFree[2]);
					bx::prettify(tmp3, BX_COUNTOF(tmp3), rbfFree[3]);
					tvm.printf(10, pos++, 0x8b, " Render Buffer: %10s, %10s, %10s, %10s ", tmp0, tmp1, tmp2, tmp3);
				}
				else if (s_extension[Extension::NVX_gpu_memory_info].m_supported)
				{
					GLint dedicated;
					GL_CHECK(glGetIntegerv(GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX, &dedicated) );

					GLint totalAvail;
					GL_CHECK(glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &totalAvail) );
					GLint currAvail;
					GL_CHECK(glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &currAvail) );

					GLint evictedCount;
					GL_CHECK(glGetIntegerv(GL_GPU_MEMORY_INFO_EVICTION_COUNT_NVX, &evictedCount) );

					GLint evictedMemory;
					GL_CHECK(glGetIntegerv(GL_GPU_MEMORY_INFO_EVICTED_MEMORY_NVX, &evictedMemory) );

					pos++;

					char tmp0[16];
					char tmp1[16];

					bx::prettify(tmp0, BX_COUNTOF(tmp0), dedicated);
					tvm.printf(10, pos++, 0x8b, " Dedicated: %10s ", tmp0);

					bx::prettify(tmp0, BX_COUNTOF(tmp0), currAvail);
					bx::prettify(tmp1, BX_COUNTOF(tmp1), totalAvail);
					tvm.printf(10, pos++, 0x8b, " Available: %10s / %10s ", tmp0, tmp1);

					bx::prettify(tmp0, BX_COUNTOF(tmp0), evictedCount);
					bx::prettify(tmp1, BX_COUNTOF(tmp1), evictedMemory);
					tvm.printf(10, pos++, 0x8b, "  Eviction: %10s / %10s ", tmp0, tmp1);
				}
#endif // BGFX_CONFIG_RENDERER_OPENGL

				pos++;
				double captureMs = double(captureElapsed)*toMs;
				tvm.printf(10, pos++, 0x8b, "     Capture: %7.4f [ms] ", captureMs);

				uint8_t attr[2] = { 0x8c, 0x8a };
				uint8_t attrIndex = _render->m_waitSubmit < _render->m_waitRender;
				tvm.printf(10, pos++, attr[attrIndex&1], " Submit wait: %7.4f [ms] ", double(_render->m_waitSubmit)*toMs);
				tvm.printf(10, pos++, attr[(attrIndex+1)&1], " Render wait: %7.4f [ms] ", double(_render->m_waitRender)*toMs);

				min = frameTime;
				max = frameTime;
			}

			blit(this, _textVideoMemBlitter, tvm);

			BGFX_GL_PROFILER_END();
		}
		else if (_render->m_debug & BGFX_DEBUG_TEXT)
		{
			BGFX_GL_PROFILER_BEGIN_LITERAL("debugtext", kColorFrame);

			blit(this, _textVideoMemBlitter, _render->m_textVideoMem);

			BGFX_GL_PROFILER_END();
		}

		if (0 != m_vao)
		{
			GL_CHECK(glBindVertexArray(0) );
		}
	}
} } // namespace bgfx

#else

namespace bgfx { namespace gl
{
	RendererContextI* rendererCreate(const Init& _init)
	{
		BX_UNUSED(_init);
		return NULL;
	}

	void rendererDestroy()
	{
	}
} /* namespace gl */ } // namespace bgfx

#endif // (BGFX_CONFIG_RENDERER_OPENGLES || BGFX_CONFIG_RENDERER_OPENGL)
