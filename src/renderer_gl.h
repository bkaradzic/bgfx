/*
 * Copyright 2011-2020 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_RENDERER_GL_H_HEADER_GUARD
#define BGFX_RENDERER_GL_H_HEADER_GUARD

#define BGFX_USE_EGL (BGFX_CONFIG_RENDERER_OPENGLES && (0 \
			|| BX_PLATFORM_ANDROID                        \
			|| BX_PLATFORM_BSD                            \
			|| BX_PLATFORM_LINUX                          \
			|| BX_PLATFORM_NX                             \
			|| BX_PLATFORM_RPI                            \
			|| BX_PLATFORM_WINDOWS                        \
			) )

#define BGFX_USE_HTML5 (BGFX_CONFIG_RENDERER_OPENGLES && (0 \
			|| BX_PLATFORM_EMSCRIPTEN                     \
			) )

#define BGFX_USE_WGL (BGFX_CONFIG_RENDERER_OPENGL && BX_PLATFORM_WINDOWS)
#define BGFX_USE_GLX (BGFX_CONFIG_RENDERER_OPENGL && (0 \
			|| BX_PLATFORM_BSD                          \
			|| BX_PLATFORM_LINUX                        \
			) )

#define BGFX_USE_GL_DYNAMIC_LIB (0 \
			|| BX_PLATFORM_BSD     \
			|| BX_PLATFORM_LINUX   \
			|| BX_PLATFORM_OSX     \
			|| BX_PLATFORM_WINDOWS \
			)

// Keep a state cache of GL uniform values to avoid redundant uploads
// on the following platforms.
#define BGFX_GL_CONFIG_UNIFORM_CACHE BX_PLATFORM_EMSCRIPTEN

#define BGFX_GL_PROFILER_BEGIN(_view, _abgr)                                               \
	BX_MACRO_BLOCK_BEGIN                                                                   \
		GL_CHECK(glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 0, -1, s_viewName[view]) ); \
		BGFX_PROFILER_BEGIN(s_viewName[view], _abgr);                                      \
	BX_MACRO_BLOCK_END

#define BGFX_GL_PROFILER_BEGIN_LITERAL(_name, _abgr)                                       \
	BX_MACRO_BLOCK_BEGIN                                                                   \
		GL_CHECK(glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 0, -1, "" _name) );         \
		BGFX_PROFILER_BEGIN_LITERAL("" _name, _abgr);                                      \
	BX_MACRO_BLOCK_END

#define BGFX_GL_PROFILER_END()        \
	BX_MACRO_BLOCK_BEGIN              \
		BGFX_PROFILER_END();          \
		GL_CHECK(glPopDebugGroup() ); \
	BX_MACRO_BLOCK_END

#if BGFX_CONFIG_RENDERER_OPENGL
#	if BGFX_CONFIG_RENDERER_OPENGL >= 31
#		include <gl/glcorearb.h>
#		if BX_PLATFORM_OSX
#			define GL_ARB_shader_objects // OSX collsion with GLhandleARB in gltypes.h
#		endif // BX_PLATFORM_OSX
#	else
#		if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
#			define GL_PROTOTYPES
#			define GL_GLEXT_LEGACY
#			include <GL/gl.h>
#			undef GL_PROTOTYPES
#		elif BX_PLATFORM_OSX
#			define GL_GLEXT_LEGACY
#			define long ptrdiff_t
#			include <OpenGL/gl.h>
#			undef long
#			undef GL_VERSION_1_2
#			undef GL_VERSION_1_3
#			undef GL_VERSION_1_4
#			undef GL_VERSION_1_5
#			undef GL_VERSION_2_0
#		else
#			include <GL/gl.h>
#		endif // BX_PLATFORM_

#		include <gl/glext.h>
#	endif // BGFX_CONFIG_RENDERER_OPENGL >= 31

#elif BGFX_CONFIG_RENDERER_OPENGLES
typedef double GLdouble;
#	if BGFX_CONFIG_RENDERER_OPENGLES < 30
#		if BX_PLATFORM_IOS
#			include <OpenGLES/ES2/gl.h>
#			include <OpenGLES/ES2/glext.h>
//#define GL_UNSIGNED_INT_10_10_10_2_OES                          0x8DF6
#define GL_UNSIGNED_INT_2_10_10_10_REV_EXT                      0x8368
#define GL_TEXTURE_3D_OES                                       0x806F
#define GL_SAMPLER_3D_OES                                       0x8B5F
#define GL_TEXTURE_WRAP_R_OES                                   0x8072
#define GL_PROGRAM_BINARY_LENGTH_OES                            0x8741
#		else
#			include <GLES2/gl2platform.h>
#			include <GLES2/gl2.h>
#			include <GLES2/gl2ext.h>
#		endif // BX_PLATFORM_
typedef int64_t  GLint64;
typedef uint64_t GLuint64;
#		define GL_PROGRAM_BINARY_LENGTH GL_PROGRAM_BINARY_LENGTH_OES
#		define GL_HALF_FLOAT GL_HALF_FLOAT_OES
#		define GL_RGBA8 GL_RGBA8_OES
#		define GL_UNSIGNED_INT_2_10_10_10_REV GL_UNSIGNED_INT_2_10_10_10_REV_EXT
#		ifndef GL_TEXTURE_3D
#			define GL_TEXTURE_3D GL_TEXTURE_3D_OES
#		endif // GL_TEXTURE_3D
#		define GL_SAMPLER_3D GL_SAMPLER_3D_OES
#		define GL_TEXTURE_WRAP_R GL_TEXTURE_WRAP_R_OES
#		ifndef GL_MIN
#			define GL_MIN GL_MIN_EXT
#		endif // GL_MIN
#		ifndef GL_MAX
#			define GL_MAX GL_MAX_EXT
#		endif // GL_MAX
#		define GL_DEPTH_COMPONENT24 GL_DEPTH_COMPONENT24_OES
#		define GL_DEPTH24_STENCIL8 GL_DEPTH24_STENCIL8_OES
#		define GL_DEPTH_COMPONENT32 GL_DEPTH_COMPONENT32_OES
#		define GL_UNSIGNED_INT_24_8 GL_UNSIGNED_INT_24_8_OES
#	elif BGFX_CONFIG_RENDERER_OPENGLES >= 30
#		include <GLES3/gl3platform.h>
#		include <GLES3/gl3.h>
#		include <GLES3/gl3ext.h>
#	endif // BGFX_CONFIG_RENDERER_

#	if BGFX_USE_EGL
#		include "glcontext_egl.h"
#	endif // BGFX_USE_EGL

#	if BGFX_USE_HTML5
#		include "glcontext_html5.h"
#	endif // BGFX_USE_EGL

#	if BX_PLATFORM_EMSCRIPTEN
#		include <emscripten/emscripten.h>
#	endif // BX_PLATFORM_EMSCRIPTEN
#endif // BGFX_CONFIG_RENDERER_OPENGL

#include "renderer.h"
#include "debug_renderdoc.h"

#ifndef GL_LUMINANCE
#	define GL_LUMINANCE 0x1909
#endif // GL_LUMINANCE

#ifndef GL_BGRA
#	define GL_BGRA 0x80E1
#endif // GL_BGRA

#ifndef GL_R8
#	define GL_R8 0x8229
#endif // GL_R8

#ifndef GL_R8I
#	define GL_R8I 0x8231
#endif // GL_R8I

#ifndef GL_R8UI
#	define GL_R8UI 0x8232
#endif // GL_R8UI

#ifndef GL_R8_SNORM
#	define GL_R8_SNORM 0x8F94
#endif // GL_R8_SNORM

#ifndef GL_R16
#	define GL_R16 0x822A
#endif // GL_R16

#ifndef GL_R16I
#	define GL_R16I 0x8233
#endif // GL_R16I

#ifndef GL_R16UI
#	define GL_R16UI 0x8234
#endif // GL_R16UI

#ifndef GL_R16F
#	define GL_R16F 0x822D
#endif // GL_R16F

#ifndef GL_R16_SNORM
#	define GL_R16_SNORM 0x8F98
#endif // GL_R16_SNORM

#ifndef GL_R32UI
#	define GL_R32UI 0x8236
#endif // GL_R32UI

#ifndef GL_R32F
#	define GL_R32F 0x822E
#endif // GL_R32F

#ifndef GL_RG8
#	define GL_RG8 0x822B
#endif // GL_RG8

#ifndef GL_RG8I
#	define GL_RG8I 0x8237
#endif // GL_RG8I

#ifndef GL_RG8UI
#	define GL_RG8UI 0x8238
#endif // GL_RG8UI

#ifndef GL_RG8_SNORM
#	define GL_RG8_SNORM 0x8F95
#endif // GL_RG8_SNORM

#ifndef GL_RG16
#	define GL_RG16 0x822C
#endif // GL_RG16

#ifndef GL_RG16UI
#	define GL_RG16UI 0x823A
#endif // GL_RG16UI

#ifndef GL_RG16F
#	define GL_RG16F 0x822F
#endif // GL_RG16F

#ifndef GL_RG16I
#	define GL_RG16I 0x8239
#endif // GL_RG16I

#ifndef GL_RG16UI
#	define GL_RG16UI 0x823A
#endif // GL_RG16UI

#ifndef GL_RG16_SNORM
#	define GL_RG16_SNORM 0x8F99
#endif // GL_RG16_SNORM

#ifndef GL_R32I
#	define GL_R32I 0x8235
#endif // GL_R32I

#ifndef GL_R32UI
#	define GL_R32UI 0x8236
#endif // GL_R32UI

#ifndef GL_RG32I
#	define GL_RG32I 0x823B
#endif // GL_RG32I

#ifndef GL_RG32UI
#	define GL_RG32UI 0x823C
#endif // GL_RG32UI

#ifndef GL_RG32F
#	define GL_RG32F 0x8230
#endif // GL_RG32F

#ifndef GL_RGB8
#	define GL_RGB8 0x8051
#endif // GL_RGB8

#ifndef GL_SRGB
#	define GL_SRGB 0x8C40
#endif // GL_SRGB

#ifndef GL_SRGB8
#	define GL_SRGB8 0x8C41
#endif // GL_SRGB8

#ifndef GL_RGB8I
#	define GL_RGB8I 0x8D8F
#endif // GL_RGB8I

#ifndef GL_RGB8UI
#	define GL_RGB8UI 0x8D7D
#endif // GL_RGB8UI

#ifndef GL_RGB8_SNORM
#	define GL_RGB8_SNORM 0x8F96
#endif // GL_RGB8_SNORM

#ifndef GL_RGBA8I
#	define GL_RGBA8I 0x8D8E
#endif // GL_RGBA8I

#ifndef GL_RGBA8UI
#	define GL_RGBA8UI 0x8D7C
#endif // GL_RGBA8UI

#ifndef GL_RGBA8_SNORM
#	define GL_RGBA8_SNORM 0x8F97
#endif // GL_RGBA8_SNORM

#ifndef GL_RGBA16I
#	define GL_RGBA16I 0x8D88
#endif // GL_RGBA16I

#ifndef GL_RGBA16UI
#	define GL_RGBA16UI 0x8D76
#endif // GL_RGBA16UI

#ifndef GL_RGBA16_SNORM
#	define GL_RGBA16_SNORM 0x8F9B
#endif // GL_RGBA16_SNORM

#ifndef GL_RGBA32UI
#	define GL_RGBA32UI 0x8D70
#endif // GL_RGBA32UI

#ifndef GL_RGBA32F
#	define GL_RGBA32F 0x8814
#endif // GL_RGBA32F

#ifndef GL_RGBA32I
#	define GL_RGBA32I 0x8D82
#endif // GL_RGBA32I

#ifndef GL_STENCIL_INDEX
#	define GL_STENCIL_INDEX 0x1901
#endif // GL_STENCIL_INDEX

#ifndef GL_RED
#	define GL_RED 0x1903
#endif // GL_RED

#ifndef GL_RED_INTEGER
#	define GL_RED_INTEGER 0x8D94
#endif // GL_RED_INTEGER

#ifndef GL_RG
#	define GL_RG 0x8227
#endif // GL_RG

#ifndef GL_RG_INTEGER
#	define GL_RG_INTEGER 0x8228
#endif // GL_RG_INTEGER

#ifndef GL_GREEN
#	define GL_GREEN 0x1904
#endif // GL_GREEN

#ifndef GL_BLUE
#	define GL_BLUE 0x1905
#endif // GL_BLUE

#ifndef GL_RGB_INTEGER
#	define GL_RGB_INTEGER 0x8D98
#endif // GL_RGB_INTEGER

#ifndef GL_RGBA_INTEGER
#	define GL_RGBA_INTEGER 0x8D99
#endif // GL_RGBA_INTEGER

#ifndef GL_RGB10_A2
#	define GL_RGB10_A2 0x8059
#endif // GL_RGB10_A2

#ifndef GL_RGBA16
#	define GL_RGBA16 0x805B
#endif // GL_RGBA16

#ifndef GL_RGBA16F
#	define GL_RGBA16F 0x881A
#endif // GL_RGBA16F

#ifndef GL_R16UI
#	define GL_R16UI 0x8234
#endif // GL_R16UI

#ifndef GL_RGBA16UI
#	define GL_RGBA16UI 0x8D76
#endif // GL_RGBA16UI

#ifndef GL_RGB9_E5
#	define GL_RGB9_E5 0x8C3D
#endif // GL_RGB9_E5

#ifndef GL_UNSIGNED_INT_5_9_9_9_REV
#	define GL_UNSIGNED_INT_5_9_9_9_REV 0x8C3E
#endif // GL_UNSIGNED_INT_5_9_9_9_REV

#ifndef GL_R11F_G11F_B10F
#	define GL_R11F_G11F_B10F 0x8C3A
#endif // GL_R11F_G11F_B10F

#ifndef GL_UNSIGNED_SHORT_5_6_5_REV
#	define GL_UNSIGNED_SHORT_5_6_5_REV 0x8364
#endif // GL_UNSIGNED_SHORT_5_6_5_REV

#ifndef GL_UNSIGNED_SHORT_1_5_5_5_REV
#	define GL_UNSIGNED_SHORT_1_5_5_5_REV 0x8366
#endif // GL_UNSIGNED_SHORT_1_5_5_5_REV

#ifndef GL_UNSIGNED_SHORT_4_4_4_4_REV
#	define GL_UNSIGNED_SHORT_4_4_4_4_REV 0x8365
#endif // GL_UNSIGNED_SHORT_4_4_4_4_REV

#ifndef GL_UNSIGNED_INT_10F_11F_11F_REV
#	define GL_UNSIGNED_INT_10F_11F_11F_REV 0x8C3B
#endif // GL_UNSIGNED_INT_10F_11F_11F_REV

#ifndef GL_COMPRESSED_RGB_S3TC_DXT1_EXT
#	define GL_COMPRESSED_RGB_S3TC_DXT1_EXT 0x83F0
#endif // GL_COMPRESSED_RGB_S3TC_DXT1_EXT

#ifndef GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
#	define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT 0x83F1
#endif // GL_COMPRESSED_RGBA_S3TC_DXT1_EXT

#ifndef GL_COMPRESSED_RGBA_S3TC_DXT3_EXT
#	define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT 0x83F2
#endif // GL_COMPRESSED_RGBA_S3TC_DXT3_EXT

#ifndef GL_COMPRESSED_RGBA_S3TC_DXT5_EXT
#	define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT 0x83F3
#endif // GL_COMPRESSED_RGBA_S3TC_DXT5_EXT

#ifndef GL_COMPRESSED_LUMINANCE_LATC1_EXT
#	define GL_COMPRESSED_LUMINANCE_LATC1_EXT 0x8C70
#endif // GL_COMPRESSED_LUMINANCE_LATC1_EXT

#ifndef GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT
#	define GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT 0x8C72
#endif // GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT

#ifndef GL_COMPRESSED_RED_RGTC1
#	define GL_COMPRESSED_RED_RGTC1 0x8DBB
#endif // GL_COMPRESSED_RED_RGTC1

#ifndef GL_COMPRESSED_RG_RGTC2
#	define GL_COMPRESSED_RG_RGTC2 0x8DBD
#endif // GL_COMPRESSED_RG_RGTC2

#ifndef GL_ETC1_RGB8_OES
#	define GL_ETC1_RGB8_OES 0x8D64
#endif // GL_ETC1_RGB8_OES

#ifndef GL_COMPRESSED_RGB8_ETC2
#	define GL_COMPRESSED_RGB8_ETC2 0x9274
#endif // GL_COMPRESSED_RGB8_ETC2

#ifndef GL_COMPRESSED_RGBA8_ETC2_EAC
#	define GL_COMPRESSED_RGBA8_ETC2_EAC 0x9278
#endif // GL_COMPRESSED_RGBA8_ETC2_EAC

#ifndef GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2
#	define GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9276
#endif // GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2

#ifndef GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG
#	define GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG 0x8C01
#endif // GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG

#ifndef GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG
#	define GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG 0x8C03
#endif // GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG

#ifndef GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG
#	define GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG 0x8C00
#endif // GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG

#ifndef GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG
#	define GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG 0x8C02
#endif // GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG

#ifndef GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG
#	define GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG 0x9137
#endif // GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG

#ifndef GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG
#	define GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG 0x9138
#endif // GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG

#ifndef GL_COMPRESSED_SRGB_PVRTC_2BPPV1_EXT
#	define GL_COMPRESSED_SRGB_PVRTC_2BPPV1_EXT 0x8A54
#endif // GL_COMPRESSED_SRGB_PVRTC_2BPPV1_EXT

#ifndef GL_COMPRESSED_SRGB_PVRTC_4BPPV1_EXT
#	define GL_COMPRESSED_SRGB_PVRTC_4BPPV1_EXT 0x8A55
#endif // GL_COMPRESSED_SRGB_PVRTC_4BPPV1_EXT

#ifndef GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV1_EXT
#	define GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV1_EXT 0x8A56
#endif // GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV1_EXT

#ifndef GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV1_EXT
#	define GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV1_EXT 0x8A57
#endif // GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV1_EXT

#ifndef ATC_RGB_AMD
	#define GL_ATC_RGB_AMD 0x8C92
#endif

#ifndef GL_ATC_RGBA_EXPLICIT_ALPHA_AMD
#   define GL_ATC_RGBA_EXPLICIT_ALPHA_AMD 0x8C93
#endif

#ifndef ATC_RGBA_INTERPOLATED_ALPHA_AMD
#   define GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD 0x87EE
#endif

#ifndef GL_COMPRESSED_RGBA_ASTC_4x4_KHR
#   define GL_COMPRESSED_RGBA_ASTC_4x4_KHR 0x93B0
#endif

#ifndef GL_COMPRESSED_RGBA_ASTC_5x5_KHR
#   define GL_COMPRESSED_RGBA_ASTC_5x5_KHR 0x93B2
#endif

#ifndef GL_COMPRESSED_RGBA_ASTC_6x6_KHR
#   define GL_COMPRESSED_RGBA_ASTC_6x6_KHR 0x93B4
#endif

#ifndef GL_COMPRESSED_RGBA_ASTC_8x5_KHR
#   define GL_COMPRESSED_RGBA_ASTC_8x5_KHR 0x93B5
#endif

#ifndef GL_COMPRESSED_RGBA_ASTC_8x6_KHR
#   define GL_COMPRESSED_RGBA_ASTC_8x6_KHR 0x93B6
#endif

#ifndef GL_COMPRESSED_RGBA_ASTC_10x5_KHR
#   define GL_COMPRESSED_RGBA_ASTC_10x5_KHR 0x93B8
#endif

#ifndef GL_COMPRESSED_SRGB8_ASTC_4x4_KHR
#   define GL_COMPRESSED_SRGB8_ASTC_4x4_KHR 0x93D0
#endif

#ifndef GL_COMPRESSED_SRGB8_ASTC_5x5_KHR
#   define GL_COMPRESSED_SRGB8_ASTC_5x5_KHR 0x93D2
#endif

#ifndef GL_COMPRESSED_SRGB8_ASTC_6x6_KHR
#   define GL_COMPRESSED_SRGB8_ASTC_6x6_KHR 0x93D4
#endif

#ifndef GL_COMPRESSED_SRGB8_ASTC_8x5_KHR
#   define GL_COMPRESSED_SRGB8_ASTC_8x5_KHR 0x93D5
#endif

#ifndef GL_COMPRESSED_SRGB8_ASTC_8x6_KHR
#   define GL_COMPRESSED_SRGB8_ASTC_8x6_KHR 0x93D6
#endif

#ifndef GL_COMPRESSED_SRGB8_ASTC_10x5_KHR
#   define GL_COMPRESSED_SRGB8_ASTC_10x5_KHR 0x93D8
#endif

#ifndef GL_COMPRESSED_RGBA_BPTC_UNORM_ARB
#	define GL_COMPRESSED_RGBA_BPTC_UNORM_ARB 0x8E8C
#endif // GL_COMPRESSED_RGBA_BPTC_UNORM_ARB

#ifndef GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_ARB
#	define GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_ARB 0x8E8D
#endif // GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_ARB

#ifndef GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB
#	define GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB 0x8E8E
#endif // GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB

#ifndef GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB
#	define GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB 0x8E8F
#endif // GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB

#ifndef GL_SRGB_EXT
#	define GL_SRGB_EXT 0x8C40
#endif // GL_SRGB_EXT

#ifndef GL_SRGB_ALPHA_EXT
#	define GL_SRGB_ALPHA_EXT 0x8C42
#endif // GL_SRGB_ALPHA_EXT

#ifndef GL_SRGB8_ALPHA8
#	define GL_SRGB8_ALPHA8 0x8C43
#endif // GL_SRGB8_ALPHA8

#ifndef GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT
#	define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT 0x8C4D
#endif // GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT

#ifndef GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT
#	define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT 0x8C4E
#endif // GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT

#ifndef GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT
#	define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT 0x8C4F
#endif // GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT

#ifndef GL_COMPRESSED_SRGB8_ETC2
#	define GL_COMPRESSED_SRGB8_ETC2 0x9275
#endif // GL_COMPRESSED_SRGB8_ETC2

#ifndef GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2
#	define GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9277
#endif // GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2

#ifndef GL_TRANSLATED_SHADER_SOURCE_LENGTH_ANGLE
#	define GL_TRANSLATED_SHADER_SOURCE_LENGTH_ANGLE 0x93A0
#endif // GL_TRANSLATED_SHADER_SOURCE_LENGTH_ANGLE

#ifndef GL_TEXTURE_MAX_ANISOTROPY_EXT
#	define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE
#endif // GL_TEXTURE_MAX_ANISOTROPY_EXT

#ifndef GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT
#	define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#endif // GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT

#ifndef GL_TEXTURE_SWIZZLE_RGBA
#	define GL_TEXTURE_SWIZZLE_RGBA 0x8E46
#endif // GL_TEXTURE_SWIZZLE_RGBA

#ifndef GL_MAX_SAMPLES
#	define GL_MAX_SAMPLES 0x8D57
#endif // GL_MAX_SAMPLES

#ifndef GL_MAX_COLOR_ATTACHMENTS
#	define GL_MAX_COLOR_ATTACHMENTS 0x8CDF
#endif // GL_MAX_COLOR_ATTACHMENTS

#ifndef GL_MAX_DRAW_BUFFERS
#	define GL_MAX_DRAW_BUFFERS 0x8824
#endif // GL_MAX_DRAW_BUFFERS

#ifndef GL_MAX_ARRAY_TEXTURE_LAYERS
#	define GL_MAX_ARRAY_TEXTURE_LAYERS 0x88FF
#endif // GL_MAX_ARRAY_TEXTURE_LAYERS

#ifndef GL_MAX_LABEL_LENGTH
#	define GL_MAX_LABEL_LENGTH 0x82E8
#endif // GL_MAX_LABEL_LENGTH

#ifndef GL_QUERY_RESULT
#	define GL_QUERY_RESULT 0x8866
#endif // GL_QUERY_RESULT

#ifndef GL_QUERY_RESULT_AVAILABLE
#	define GL_QUERY_RESULT_AVAILABLE 0x8867
#endif // GL_QUERY_RESULT_AVAILABLE

#ifndef GL_SAMPLES_PASSED
#	define GL_SAMPLES_PASSED 0x8914
#endif // GL_SAMPLES_PASSED

#ifndef GL_ANY_SAMPLES_PASSED
#	define GL_ANY_SAMPLES_PASSED 0x8C2F
#endif // GL_ANY_SAMPLES_PASSED

#ifndef GL_READ_FRAMEBUFFER
#	define GL_READ_FRAMEBUFFER 0x8CA8
#endif /// GL_READ_FRAMEBUFFER

#ifndef GL_DRAW_FRAMEBUFFER
#	define GL_DRAW_FRAMEBUFFER 0x8CA9
#endif // GL_DRAW_FRAMEBUFFER

#ifndef GL_TIME_ELAPSED
#	define GL_TIME_ELAPSED 0x88BF
#endif // GL_TIME_ELAPSED

#ifndef GL_TIMESTAMP
#	define GL_TIMESTAMP 0x8E28
#endif // GL_TIMESTAMP

#ifndef GL_VBO_FREE_MEMORY_ATI
#	define GL_VBO_FREE_MEMORY_ATI 0x87FB
#endif // GL_VBO_FREE_MEMORY_ATI

#ifndef GL_TEXTURE_FREE_MEMORY_ATI
#	define GL_TEXTURE_FREE_MEMORY_ATI 0x87FC
#endif // GL_TEXTURE_FREE_MEMORY_ATI

#ifndef GL_RENDERBUFFER_FREE_MEMORY_ATI
#	define GL_RENDERBUFFER_FREE_MEMORY_ATI 0x87FD
#endif // GL_RENDERBUFFER_FREE_MEMORY_ATI

// https://web.archive.org/web/20190207230448/http://developer.download.nvidia.com/opengl/specs/GL_NVX_gpu_memory_info.txt
#ifndef GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX
#	define GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX 0x9047
#endif // GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX

#ifndef GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX
#	define GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX 0x9048
#endif // GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX

#ifndef GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX
#	define GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX 0x9049
#endif // GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX

#ifndef GL_GPU_MEMORY_INFO_EVICTION_COUNT_NVX
#	define GL_GPU_MEMORY_INFO_EVICTION_COUNT_NVX 0x904A
#endif // GL_GPU_MEMORY_INFO_EVICTION_COUNT_NVX

#ifndef GL_GPU_MEMORY_INFO_EVICTED_MEMORY_NVX
#	define GL_GPU_MEMORY_INFO_EVICTED_MEMORY_NVX 0x904B
#endif // GL_GPU_MEMORY_INFO_EVICTED_MEMORY_NVX

#ifndef GL_UNPACK_ROW_LENGTH
#	define GL_UNPACK_ROW_LENGTH 0x0CF2
#endif // GL_UNPACK_ROW_LENGTH

#ifndef GL_DEPTH_STENCIL
#	define GL_DEPTH_STENCIL 0x84F9
#endif // GL_DEPTH_STENCIL

#ifndef GL_DEPTH_COMPONENT32
#	define GL_DEPTH_COMPONENT32 0x81A7
#endif // GL_DEPTH_COMPONENT32

#ifndef GL_DEPTH_COMPONENT32F
#	define GL_DEPTH_COMPONENT32F 0x8CAC
#endif // GL_DEPTH_COMPONENT32F

#ifndef GL_DEPTH_STENCIL_ATTACHMENT
#	define GL_DEPTH_STENCIL_ATTACHMENT 0x821A
#endif // GL_DEPTH_STENCIL_ATTACHMENT

#ifndef GL_TEXTURE_COMPARE_MODE
#	define GL_TEXTURE_COMPARE_MODE 0x884C
#endif // GL_TEXTURE_COMPARE_MODE

#ifndef GL_TEXTURE_COMPARE_FUNC
#	define GL_TEXTURE_COMPARE_FUNC 0x884D
#endif // GL_TEXTURE_COMPARE_FUNC

#ifndef GL_COMPARE_REF_TO_TEXTURE
#	define GL_COMPARE_REF_TO_TEXTURE 0x884E
#endif // GL_COMPARE_REF_TO_TEXTURE

#ifndef GL_SAMPLER_1D
#    define GL_SAMPLER_1D 0x8B5D
#endif // GL_SAMPLER_1D

#ifndef GL_INT_SAMPLER_1D
#    define GL_INT_SAMPLER_1D 0x8DC9
#endif // GL_INT_SAMPLER_1D

#ifndef GL_UNSIGNED_INT_SAMPLER_1D
#    define GL_UNSIGNED_INT_SAMPLER_1D 0x8DD1
#endif // GL_UNSIGNED_INT_SAMPLER_1D

#ifndef GL_SAMPLER_1D_SHADOW
#    define GL_SAMPLER_1D_SHADOW 0x8B61
#endif // GL_SAMPLER_1D_SHADOW

#ifndef GL_TEXTURE_1D
#    define GL_TEXTURE_1D 0x0DE0
#endif // GL_TEXTURE_1D

#ifndef GL_SAMPLER_1D_ARRAY
#    define GL_SAMPLER_1D_ARRAY 0x8DC0
#endif // GL_SAMPLER_1D_ARRAY

#ifndef GL_INT_SAMPLER_1D_ARRAY
#    define GL_INT_SAMPLER_1D_ARRAY 0x8DCE
#endif // GL_INT_SAMPLER_1D_ARRAY

#ifndef GL_UNSIGNED_INT_SAMPLER_1D_ARRAY
#    define GL_UNSIGNED_INT_SAMPLER_1D_ARRAY 0x8DD6
#endif // GL_UNSIGNED_INT_SAMPLER_1D_ARRAY

#ifndef GL_SAMPLER_1D_ARRAY_SHADOW
#    define GL_SAMPLER_1D_ARRAY_SHADOW 0x8DC3
#endif // GL_SAMPLER_1D_ARRAY_SHADOW

#ifndef GL_TEXTURE_1D_ARRAY
#    define GL_TEXTURE_1D_ARRAY 0x8C18
#endif // GL_TEXTURE_1D_ARRAY

#ifndef GL_SAMPLER_2D_MULTISAMPLE_ARRAY
#    define GL_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910B
#endif // GL_SAMPLER_2D_MULTISAMPLE_ARRAY

#ifndef GL_SAMPLER_CUBE_MAP_ARRAY
#    define GL_SAMPLER_CUBE_MAP_ARRAY 0x900C
#endif // GL_SAMPLER_CUBE_MAP_ARRAY

#ifndef GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW
#    define GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW 0x900D
#endif // GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW

#ifndef GL_INT_SAMPLER_CUBE_MAP_ARRAY
#    define GL_INT_SAMPLER_CUBE_MAP_ARRAY 0x900E
#endif // GL_INT_SAMPLER_CUBE_MAP_ARRAY

#ifndef GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY
#    define GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY 0x900F
#endif // GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY

#ifndef GL_SAMPLER_2D_RECT
#    define GL_SAMPLER_2D_RECT 0x8B63
#endif // GL_SAMPLER_2D_RECT

#ifndef GL_INT_SAMPLER_2D_RECT
#    define GL_INT_SAMPLER_2D_RECT 0x8DCD
#endif // GL_INT_SAMPLER_2D_RECT

#ifndef GL_UNSIGNED_INT_SAMPLER_2D_RECT
#    define GL_UNSIGNED_INT_SAMPLER_2D_RECT 0x8DD5
#endif // GL_UNSIGNED_INT_SAMPLER_2D_RECT

#ifndef GL_SAMPLER_2D_RECT_SHADOW
#    define GL_SAMPLER_2D_RECT_SHADOW 0x8B64
#endif // GL_SAMPLER_2D_RECT_SHADOW

#ifndef GL_TEXTURE_RECTANGLE
#    define GL_TEXTURE_RECTANGLE 0x84F5
#endif // GL_TEXTURE_RECTANGLE

#ifndef GL_SAMPLER_CUBE_SHADOW
#    define GL_SAMPLER_CUBE_SHADOW 0x8DC5
#endif // GL_SAMPLER_CUBE_SHADOW

#ifndef GL_INT_SAMPLER_2D
#	define GL_INT_SAMPLER_2D 0x8DCA
#endif // GL_INT_SAMPLER_2D

#ifndef GL_UNSIGNED_INT_SAMPLER_2D
#	define GL_UNSIGNED_INT_SAMPLER_2D 0x8DD2
#endif // GL_UNSIGNED_INT_SAMPLER_2D

#ifndef GL_INT_SAMPLER_2D_ARRAY
#	define GL_INT_SAMPLER_2D_ARRAY 0x8DCF
#endif // GL_INT_SAMPLER_2D_ARRAY

#ifndef GL_UNSIGNED_INT_SAMPLER_2D_ARRAY
#	define GL_UNSIGNED_INT_SAMPLER_2D_ARRAY 0x8DD7
#endif // GL_UNSIGNED_INT_SAMPLER_2D_ARRAY

#ifndef GL_INT_SAMPLER_3D
#	define GL_INT_SAMPLER_3D 0x8DCB
#endif // GL_INT_SAMPLER_3D

#ifndef GL_UNSIGNED_INT_SAMPLER_3D
#	define GL_UNSIGNED_INT_SAMPLER_3D 0x8DD3
#endif // GL_UNSIGNED_INT_SAMPLER_3D

#ifndef GL_INT_SAMPLER_CUBE
#	define GL_INT_SAMPLER_CUBE 0x8DCC
#endif // GL_INT_SAMPLER_CUBE

#ifndef GL_UNSIGNED_INT_SAMPLER_CUBE
#	define GL_UNSIGNED_INT_SAMPLER_CUBE 0x8DD4
#endif // GL_UNSIGNED_INT_SAMPLER_CUBE

#ifndef GL_SAMPLER_2D_MULTISAMPLE
#	define GL_SAMPLER_2D_MULTISAMPLE 0x9108
#endif // GL_SAMPLER_2D_MULTISAMPLE

#ifndef GL_INT_SAMPLER_2D_MULTISAMPLE
#	define GL_INT_SAMPLER_2D_MULTISAMPLE 0x9109
#endif // GL_INT_SAMPLER_2D_MULTISAMPLE

#ifndef GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE
#	define GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE 0x910A
#endif // GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE

#ifndef GL_SAMPLER_2D_SHADOW
#	define GL_SAMPLER_2D_SHADOW 0x8B62
#endif // GL_SAMPLER_2D_SHADOW

#ifndef GL_SAMPLER_2D_ARRAY
#	define GL_SAMPLER_2D_ARRAY 0x8DC1
#endif // GL_SAMPLER_2D_ARRAY

#ifndef GL_SAMPLER_2D_ARRAY_SHADOW
#	define GL_SAMPLER_2D_ARRAY_SHADOW 0x8DC4
#endif // GL_SAMPLER_2D_ARRAY_SHADOW

#ifndef GL_SAMPLER_EXTERNAL_OES
#    define GL_SAMPLER_EXTERNAL_OES 0x8D66
#endif // GL_SAMPLER_EXTERNAL_OES

#ifndef GL_TEXTURE_EXTERNAL_OES
#    define GL_TEXTURE_EXTERNAL_OES 0x8D65
#endif // GL_TEXTURE_EXTERNAL_OES

#ifndef GL_TEXTURE_BINDING_EXTERNAL_OES
#    define GL_TEXTURE_BINDING_EXTERNAL_OES 0x8D67
#endif // GL_TEXTURE_BINDING_EXTERNAL_OES

#ifndef GL_TEXTURE_MAX_LEVEL
#	define GL_TEXTURE_MAX_LEVEL 0x813D
#endif // GL_TEXTURE_MAX_LEVEL

#ifndef GL_COMPUTE_SHADER
#	define GL_COMPUTE_SHADER 0x91B9
#endif // GL_COMPUTE_SHADER

#ifndef GL_READ_ONLY
#	define GL_READ_ONLY 0x88B8
#endif // GL_READ_ONLY

#ifndef GL_WRITE_ONLY
#	define GL_WRITE_ONLY 0x88B9
#endif // GL_WRITE_ONLY

#ifndef GL_READ_WRITE
#	define GL_READ_WRITE 0x88BA
#endif // GL_READ_WRITE

#ifndef GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT
#	define GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT 0x00000001
#endif // GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT

#ifndef GL_ELEMENT_ARRAY_BARRIER_BIT
#	define GL_ELEMENT_ARRAY_BARRIER_BIT 0x00000002
#endif // GL_ELEMENT_ARRAY_BARRIER_BIT

#ifndef GL_SHADER_IMAGE_ACCESS_BARRIER_BIT
#	define GL_SHADER_IMAGE_ACCESS_BARRIER_BIT 0x00000020
#endif // GL_SHADER_IMAGE_ACCESS_BARRIER_BIT

#ifndef GL_SHADER_STORAGE_BARRIER_BIT
#	define GL_SHADER_STORAGE_BARRIER_BIT 0x00002000
#endif // GL_SHADER_STORAGE_BARRIER_BIT

#ifndef GL_SHADER_STORAGE_BUFFER
#	define GL_SHADER_STORAGE_BUFFER 0x90D2
#endif // GL_SHADER_STORAGE_BUFFER

#ifndef GL_IMAGE_1D
#	define GL_IMAGE_1D 0x904C
#endif // GL_IMAGE_1D

#ifndef GL_IMAGE_2D
#	define GL_IMAGE_2D 0x904D
#endif // GL_IMAGE_2D

#ifndef GL_IMAGE_2D_ARRAY
#	define GL_IMAGE_2D_ARRAY 0x9053
#endif // GL_IMAGE_2D_ARRAY

#ifndef GL_IMAGE_3D
#	define GL_IMAGE_3D 0x904E
#endif // GL_IMAGE_3D

#ifndef GL_IMAGE_CUBE
#	define GL_IMAGE_CUBE 0x9050
#endif // GL_IMAGE_CUBE

#ifndef GL_INT_IMAGE_1D
#	define GL_INT_IMAGE_1D 0x9057
#endif // GL_INT_IMAGE_1D

#ifndef GL_INT_IMAGE_2D
#	define GL_INT_IMAGE_2D 0x9058
#endif // GL_INT_IMAGE_2D

#ifndef GL_INT_IMAGE_3D
#	define GL_INT_IMAGE_3D 0x9059
#endif // GL_INT_IMAGE_3D

#ifndef GL_INT_IMAGE_CUBE
#	define GL_INT_IMAGE_CUBE 0x905B
#endif // GL_INT_IMAGE_CUBE

#ifndef GL_UNSIGNED_INT_IMAGE_1D
#	define GL_UNSIGNED_INT_IMAGE_1D 0x9062
#endif // GL_UNSIGNED_INT_IMAGE_1D

#ifndef GL_UNSIGNED_INT_IMAGE_2D
#	define GL_UNSIGNED_INT_IMAGE_2D 0x9063
#endif // GL_UNSIGNED_INT_IMAGE_2D

#ifndef GL_UNSIGNED_INT_IMAGE_3D
#	define GL_UNSIGNED_INT_IMAGE_3D 0x9064
#endif // GL_UNSIGNED_INT_IMAGE_3D

#ifndef GL_UNSIGNED_INT_IMAGE_CUBE
#	define GL_UNSIGNED_INT_IMAGE_CUBE 0x9066
#endif // GL_UNSIGNED_INT_IMAGE_CUBE

#ifndef GL_PROGRAM_INPUT
#	define GL_PROGRAM_INPUT 0x92E3
#endif // GL_PROGRAM_INPUT

#ifndef GL_ACTIVE_RESOURCES
#	define GL_ACTIVE_RESOURCES 0x92F5
#endif // GL_ACTIVE_RESOURCES

#ifndef GL_UNIFORM
#	define GL_UNIFORM 0x92E1
#endif // GL_UNIFORM

#ifndef GL_BUFFER_VARIABLE
#	define GL_BUFFER_VARIABLE 0x92E5
#endif // GL_BUFFER_VARIABLE

#ifndef GL_UNSIGNED_INT_VEC2
#	define GL_UNSIGNED_INT_VEC2 0x8DC6
#endif // GL_UNSIGNED_INT_VEC2

#ifndef GL_UNSIGNED_INT_VEC3
#	define GL_UNSIGNED_INT_VEC3 0x8DC7
#endif // GL_UNSIGNED_INT_VEC3

#ifndef GL_UNSIGNED_INT_VEC4
#	define GL_UNSIGNED_INT_VEC4 0x8DC8
#endif // GL_UNSIGNED_INT_VEC4

#ifndef GL_TYPE
#	define GL_TYPE 0x92FA
#endif // GL_TYPE

#ifndef GL_ARRAY_SIZE
#	define GL_ARRAY_SIZE 0x92FB
#endif // GL_ARRAY_SIZE

#ifndef GL_LOCATION
#	define GL_LOCATION 0x930E
#endif // GL_LOCATION

#ifndef GL_UNSIGNED_INT_10_10_10_2
#	define GL_UNSIGNED_INT_10_10_10_2 0x8DF6
#endif // GL_UNSIGNED_INT_10_10_10_2

#ifndef GL_FRAMEBUFFER_SRGB
#	define GL_FRAMEBUFFER_SRGB 0x8DB9
#endif // GL_FRAMEBUFFER_SRGB

#ifndef GL_NUM_EXTENSIONS
#	define GL_NUM_EXTENSIONS 0x821D
#endif // GL_NUM_EXTENSIONS

#ifndef GL_SAMPLE_ALPHA_TO_COVERAGE
#	define GL_SAMPLE_ALPHA_TO_COVERAGE 0x809E
#endif // GL_SAMPLE_ALPHA_TO_COVERAGE

#ifndef GL_CONSERVATIVE_RASTERIZATION_NV
#	define GL_CONSERVATIVE_RASTERIZATION_NV 0x9346
#endif // GL_CONSERVATIVE_RASTERIZATION_NV

#ifndef GL_NEGATIVE_ONE_TO_ONE
#	define GL_NEGATIVE_ONE_TO_ONE 0x935E
#endif // GL_NEGATIVE_ONE_TO_ONE

#ifndef GL_ZERO_TO_ONE
#	define GL_ZERO_TO_ONE 0x935F
#endif // GL_ZERO_TO_ONE

#ifndef GL_LOWER_LEFT
#	define GL_LOWER_LEFT 0x8CA1
#endif // GL_LOWER_LEFT

#ifndef GL_UPPER_LEFT
#	define GL_UPPER_LEFT 0x8CA2
#endif // GL_UPPER_LEFT

#ifndef GL_SHADER
#	define GL_SHADER 0x82E1
#endif // GL_SHADER

#ifndef GL_TEXTURE
#	define GL_TEXTURE 0x1702
#endif // GL_TEXTURE

#ifndef GL_BUFFER
#	define GL_BUFFER 0x82E0
#endif // GL_BUFFER

#ifndef GL_COMMAND_BARRIER_BIT
#	define GL_COMMAND_BARRIER_BIT 0x00000040
#endif // GL_COMMAND_BARRIER_BIT

// _KHR or _ARB...
#define GL_DEBUG_OUTPUT_SYNCHRONOUS         0x8242
#define GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH 0x8243
#define GL_DEBUG_CALLBACK_FUNCTION          0x8244
#define GL_DEBUG_CALLBACK_USER_PARAM        0x8245
#define GL_DEBUG_SOURCE_API                 0x8246
#define GL_DEBUG_SOURCE_WINDOW_SYSTEM       0x8247
#define GL_DEBUG_SOURCE_SHADER_COMPILER     0x8248
#define GL_DEBUG_SOURCE_THIRD_PARTY         0x8249
#define GL_DEBUG_SOURCE_APPLICATION         0x824A
#define GL_DEBUG_SOURCE_OTHER               0x824B
#define GL_DEBUG_TYPE_ERROR                 0x824C
#define GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR   0x824D
#define GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR    0x824E
#define GL_DEBUG_TYPE_PORTABILITY           0x824F
#define GL_DEBUG_TYPE_PERFORMANCE           0x8250
#define GL_DEBUG_TYPE_OTHER                 0x8251
#define GL_DEBUG_TYPE_MARKER                0x8268
#define GL_DEBUG_TYPE_PUSH_GROUP            0x8269
#define GL_DEBUG_TYPE_POP_GROUP             0x826A
#define GL_DEBUG_SEVERITY_NOTIFICATION      0x826B
#define GL_MAX_DEBUG_GROUP_STACK_DEPTH      0x826C
#define GL_DEBUG_GROUP_STACK_DEPTH          0x826D
#define GL_MAX_LABEL_LENGTH                 0x82E8
#define GL_MAX_DEBUG_MESSAGE_LENGTH         0x9143
#define GL_MAX_DEBUG_LOGGED_MESSAGES        0x9144
#define GL_DEBUG_LOGGED_MESSAGES            0x9145
#define GL_DEBUG_SEVERITY_HIGH              0x9146
#define GL_DEBUG_SEVERITY_MEDIUM            0x9147
#define GL_DEBUG_SEVERITY_LOW               0x9148

#ifndef GL_DEPTH_CLAMP
#	define GL_DEPTH_CLAMP 0x864F
#endif // GL_DEPTH_CLAMP

#ifndef GL_TEXTURE_BORDER_COLOR
#	define GL_TEXTURE_BORDER_COLOR 0x1004
#endif // GL_TEXTURE_BORDER_COLOR

#ifndef GL_CLAMP_TO_BORDER
#	define GL_CLAMP_TO_BORDER 0x812D
#endif // GL_CLAMP_TO_BORDER

#ifndef GL_TEXTURE_2D_ARRAY
#	define GL_TEXTURE_2D_ARRAY 0x8C1A
#endif // GL_TEXTURE_2D_ARRAY

#ifndef GL_TEXTURE_2D_MULTISAMPLE_ARRAY
#	define GL_TEXTURE_2D_MULTISAMPLE_ARRAY 0x9102
#endif // GL_TEXTURE_2D_MULTISAMPLE_ARRAY

#ifndef GL_TEXTURE_CUBE_MAP_ARRAY
#	define GL_TEXTURE_CUBE_MAP_ARRAY 0x9009
#endif // GL_TEXTURE_CUBE_MAP_ARRAY

#ifndef GL_TEXTURE_CUBE_MAP_SEAMLESS
#	define GL_TEXTURE_CUBE_MAP_SEAMLESS 0x884F
#endif // GL_TEXTURE_CUBE_MAP_SEAMLESS

#ifndef GL_TEXTURE_2D_MULTISAMPLE
#	define GL_TEXTURE_2D_MULTISAMPLE 0x9100
#endif // GL_TEXTURE_2D_MULTISAMPLE

#ifndef GL_DRAW_INDIRECT_BUFFER
#	define GL_DRAW_INDIRECT_BUFFER 0x8F3F
#endif // GL_DRAW_INDIRECT_BUFFER

#ifndef GL_DISPATCH_INDIRECT_BUFFER
#	define GL_DISPATCH_INDIRECT_BUFFER 0x90EE
#endif // GL_DISPATCH_INDIRECT_BUFFER

#ifndef GL_MAX_NAME_LENGTH
#	define GL_MAX_NAME_LENGTH 0x92F6
#endif // GL_MAX_NAME_LENGTH

#ifndef GL_DEBUG_SEVERITY_NOTIFICATION
#	define GL_DEBUG_SEVERITY_NOTIFICATION 0x826b
#endif // GL_DEBUG_SEVERITY_NOTIFICATION

#ifndef GL_LINE
#	define GL_LINE 0x1B01
#endif // GL_LINE

#ifndef GL_FILL
#	define GL_FILL 0x1B02
#endif // GL_FILL

#ifndef GL_MULTISAMPLE
#	define GL_MULTISAMPLE 0x809D
#endif // GL_MULTISAMPLE

#ifndef GL_LINE_SMOOTH
#	define GL_LINE_SMOOTH 0x0B20
#endif // GL_LINE_SMOOTH

#ifndef GL_TEXTURE_LOD_BIAS
#	define GL_TEXTURE_LOD_BIAS 0x8501
#endif // GL_TEXTURE_LOD_BIAS

#if BX_PLATFORM_WINDOWS
#	include <windows.h>
#elif BX_PLATFORM_LINUX || BX_PLATFORM_BSD
#	include "glcontext_glx.h"
#elif BX_PLATFORM_OSX
#	include "glcontext_nsgl.h"
#elif BX_PLATFORM_IOS
#	include "glcontext_eagl.h"
#endif // BX_PLATFORM_

#if BGFX_USE_WGL
#	include "glcontext_wgl.h"
#endif // BGFX_USE_WGL

#ifndef GL_APIENTRY
#	define GL_APIENTRY APIENTRY
#endif // GL_APIENTRY

#ifndef GL_APIENTRYP
#	define GL_APIENTRYP GL_APIENTRY*
#endif // GL_APIENTRYP

#if !BGFX_CONFIG_RENDERER_OPENGL
#	define glClearDepth glClearDepthf
#endif // !BGFX_CONFIG_RENDERER_OPENGL

namespace bgfx
{
	class UniformBuffer;
} // namespace bgfx

namespace bgfx { namespace gl
{
	void dumpExtensions(const char* _extensions);

	void lazyEnableVertexAttribArray(GLuint index);
	void lazyDisableVertexAttribArray(GLuint index);

	const char* glEnumName(GLenum _enum);

#define _GL_CHECK(_check, _call) \
				BX_MACRO_BLOCK_BEGIN \
					/*BX_TRACE(#_call);*/ \
					_call; \
					GLenum gl_err = glGetError(); \
					_check(0 == gl_err, #_call "; GL error 0x%x: %s", gl_err, glEnumName(gl_err) ); \
					BX_UNUSED(gl_err); \
				BX_MACRO_BLOCK_END

#define IGNORE_GL_ERROR_CHECK(...) BX_NOOP()

#if BGFX_CONFIG_DEBUG
#	define GL_CHECK(_call)   _GL_CHECK(BX_CHECK, _call)
#	define GL_CHECK_I(_call) _GL_CHECK(IGNORE_GL_ERROR_CHECK, _call)
#else
#	define GL_CHECK(_call)   _call
#	define GL_CHECK_I(_call) _call
#endif // BGFX_CONFIG_DEBUG

#define GL_IMPORT_TYPEDEFS 1
#define GL_IMPORT(_optional, _proto, _func, _import) extern _proto _func
#include "glimports.h"

	class UniformStateCache
	{
	public:
		struct f4   { float val[ 4]; bool operator ==(const f4   &rhs) { const uint64_t *a = (const uint64_t *)this; const uint64_t *b = (const uint64_t *)&rhs; return a[0] == b[0] && a[1] == b[1]; }};
		struct f3x3 { float val[ 9]; bool operator ==(const f3x3 &rhs) { const uint64_t *a = (const uint64_t *)this; const uint64_t *b = (const uint64_t *)&rhs; return a[0] == b[0] && a[1] == b[1] && a[2] == b[2] && a[3] == b[3] && ((const uint32_t*)a)[8] == ((const uint32_t*)b)[8]; }};
		struct f4x4 { float val[16]; bool operator ==(const f4x4 &rhs) { const uint64_t *a = (const uint64_t *)this; const uint64_t *b = (const uint64_t *)&rhs; return a[0] == b[0] && a[1] == b[1] && a[2] == b[2] && a[3] == b[3] && a[4] == b[4] && a[5] == b[5] && a[6] == b[6] && a[7] == b[7]; }};

		typedef stl::unordered_map<uint64_t, int>  IMap;
		typedef stl::unordered_map<uint64_t, f4>   F4Map;
		typedef stl::unordered_map<uint64_t, f3x3> F3x3Map;
		typedef stl::unordered_map<uint64_t, f4x4> F4x4Map;

		UniformStateCache()
			: m_currentProgram(0)
		{
		}

		// Inserts the new value into the uniform cache, and returns true
		// if the old value was different than the new one.
		template<typename T>
		bool updateUniformCache(uint32_t loc, const T &value)
		{
			if (BX_ENABLED(BGFX_GL_CONFIG_UNIFORM_CACHE) )
			{
				// Uniform state cache for various types.
				stl::unordered_map<uint64_t, T>& uniformCacheMap = getUniformCache<T>();

				uint64_t key = (uint64_t(m_currentProgram) << 32) | loc;

				auto iter = uniformCacheMap.find(key);

				// Not found in the cache? Add it.
				if (iter == uniformCacheMap.end())
				{
					uniformCacheMap[key] = value;
					return true;
				}

				// Value in the cache was the same as new state? Skip reuploading this state.
				if (iter->second == value)
				{
					return false;
				}

				iter->second = value;
			}

			return true;
		}

		void saveCurrentProgram(GLuint program)
		{
			if (BX_ENABLED(BGFX_GL_CONFIG_UNIFORM_CACHE) )
			{
				m_currentProgram = program;
			}
		}

	private:
		GLuint m_currentProgram;

		IMap    m_uniformiCacheMap;
		F4Map   m_uniformf4CacheMap;
		F3x3Map m_uniformf3x3CacheMap;
		F4x4Map m_uniformf4x4CacheMap;

		template<typename T>
		stl::unordered_map<uint64_t, T>& getUniformCache();
	};

	template<>
	inline UniformStateCache::IMap& UniformStateCache::getUniformCache() { return m_uniformiCacheMap; }

	template<>
	inline UniformStateCache::F4Map& UniformStateCache::getUniformCache() { return m_uniformf4CacheMap; }

	template<>
	inline UniformStateCache::F3x3Map& UniformStateCache::getUniformCache() { return m_uniformf3x3CacheMap; }

	template<>
	inline UniformStateCache::F4x4Map& UniformStateCache::getUniformCache() { return m_uniformf4x4CacheMap; }

	class SamplerStateCache
	{
	public:
		GLuint add(uint32_t _hash)
		{
			invalidate(_hash);

			GLuint samplerId;
			GL_CHECK(glGenSamplers(1, &samplerId) );

			m_hashMap.insert(stl::make_pair(_hash, samplerId) );

			return samplerId;
		}

		GLuint find(uint32_t _hash)
		{
			HashMap::iterator it = m_hashMap.find(_hash);
			if (it != m_hashMap.end() )
			{
				return it->second;
			}

			return UINT32_MAX;
		}

		void invalidate(uint32_t _hash)
		{
			HashMap::iterator it = m_hashMap.find(_hash);
			if (it != m_hashMap.end() )
			{
				GL_CHECK(glDeleteSamplers(1, &it->second) );
				m_hashMap.erase(it);
			}
		}

		void invalidate()
		{
			for (HashMap::iterator it = m_hashMap.begin(), itEnd = m_hashMap.end(); it != itEnd; ++it)
			{
				GL_CHECK(glDeleteSamplers(1, &it->second) );
			}
			m_hashMap.clear();
		}

		uint32_t getCount() const
		{
			return uint32_t(m_hashMap.size() );
		}

	private:
		typedef stl::unordered_map<uint32_t, GLuint> HashMap;
		HashMap m_hashMap;
	};

	struct IndexBufferGL
	{
		void create(uint32_t _size, void* _data, uint16_t _flags)
		{
			m_size  = _size;
			m_flags = _flags;

			GL_CHECK(glGenBuffers(1, &m_id) );
			BX_CHECK(0 != m_id, "Failed to generate buffer id.");
			GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id) );
			GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER
				, _size
				, _data
				, (NULL==_data) ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW
				) );
			GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) );
		}

		void update(uint32_t _offset, uint32_t _size, void* _data, bool _discard = false)
		{
			BX_CHECK(0 != m_id, "Updating invalid index buffer.");

			if (_discard)
			{
				// orphan buffer...
				destroy();
				create(m_size, NULL, m_flags);
			}

			GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id) );
			GL_CHECK(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER
				, _offset
				, _size
				, _data
				) );
			GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) );
		}

		void destroy();

		GLuint m_id;
		uint32_t m_size;
		uint16_t m_flags;
	};

	struct VertexBufferGL
	{
		void create(uint32_t _size, void* _data, VertexLayoutHandle _layoutHandle, uint16_t _flags)
		{
			m_size = _size;
			m_layoutHandle = _layoutHandle;
			const bool drawIndirect = 0 != (_flags & BGFX_BUFFER_DRAW_INDIRECT);

			m_target = drawIndirect ? GL_DRAW_INDIRECT_BUFFER : GL_ARRAY_BUFFER;

			GL_CHECK(glGenBuffers(1, &m_id) );
			BX_CHECK(0 != m_id, "Failed to generate buffer id.");
			GL_CHECK(glBindBuffer(m_target, m_id) );
			GL_CHECK(glBufferData(m_target
				, _size
				, _data
				, (NULL==_data) ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW
				) );
			GL_CHECK(glBindBuffer(m_target, 0) );
		}

		void update(uint32_t _offset, uint32_t _size, void* _data, bool _discard = false)
		{
			BX_CHECK(0 != m_id, "Updating invalid vertex buffer.");

			if (_discard)
			{
				// orphan buffer...
				destroy();
				create(m_size, NULL, m_layoutHandle, 0);
			}

			GL_CHECK(glBindBuffer(m_target, m_id) );
			GL_CHECK(glBufferSubData(m_target
				, _offset
				, _size
				, _data
				) );
			GL_CHECK(glBindBuffer(m_target, 0) );
		}

		void destroy();

		GLuint m_id;
		GLenum m_target;
		uint32_t m_size;
		VertexLayoutHandle m_layoutHandle;
	};

	struct TextureGL
	{
		TextureGL()
			: m_id(0)
			, m_rbo(0)
			, m_target(GL_TEXTURE_2D)
			, m_fmt(GL_ZERO)
			, m_type(GL_ZERO)
			, m_flags(0)
			, m_currentSamplerHash(UINT32_MAX)
			, m_numMips(0)
		{
		}

		bool init(GLenum _target, uint32_t _width, uint32_t _height, uint32_t _depth, uint8_t _numMips, uint64_t _flags);
		void create(const Memory* _mem, uint64_t _flags, uint8_t _skip);
		void destroy();
		void overrideInternal(uintptr_t _ptr);
		void update(uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem);
		void setSamplerState(uint32_t _flags, const float _rgba[4]);
		void commit(uint32_t _stage, uint32_t _flags, const float _palette[][4], GLenum _target);
		void resolve(uint8_t _resolve) const;

		bool isCubeMap() const
		{
			return 0
				|| GL_TEXTURE_CUBE_MAP       == m_target
				|| GL_TEXTURE_CUBE_MAP_ARRAY == m_target
				;
		}

		GLuint m_id;
		GLuint m_rbo;
		GLenum m_target;
		GLenum m_fmt;
		GLenum m_type;
		uint64_t m_flags;
		uint32_t m_currentSamplerHash;
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_depth;
		uint32_t m_numLayers;
		uint8_t m_numMips;
		uint8_t m_requestedFormat;
		uint8_t m_textureFormat;
	};

	struct ShaderGL
	{
		ShaderGL()
			: m_id(0)
			, m_type(0)
			, m_hash(0)
		{
		}

		void create(const Memory* _mem);
		void destroy();

		GLuint m_id;
		GLenum m_type;
		uint32_t m_hash;
	};

	struct FrameBufferGL
	{
		FrameBufferGL()
			: m_swapChain(NULL)
			, m_denseIdx(UINT16_MAX)
			, m_num(0)
			, m_needPresent(false)
		{
			bx::memSet(m_fbo, 0, sizeof(m_fbo) );
		}

		void create(uint8_t _num, const Attachment* _attachment);
		void create(uint16_t _denseIdx, void* _nwh, uint32_t _width, uint32_t _height, TextureFormat::Enum _format, TextureFormat::Enum _depthFormat);
		void postReset();
		uint16_t destroy();
		void resolve();
		void discard(uint16_t _flags);
		void set();

		SwapChainGL* m_swapChain;
		GLuint m_fbo[2];
		uint32_t m_width;
		uint32_t m_height;
		uint16_t m_denseIdx;
		uint8_t  m_num;
		uint8_t  m_numTh;
		bool     m_needPresent;
		Attachment m_attachment[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
	};

	struct SamplerGL {
		GLint loc;
		GLenum target;
	};

	struct ProgramGL
	{
		ProgramGL()
			: m_id(0)
			, m_constantBuffer(NULL)
			, m_numPredefined(0)
		{
		}

		void create(const ShaderGL& _vsh, const ShaderGL& _fsh);
		void destroy();
		void init();
		void bindInstanceData(uint32_t _stride, uint32_t _baseVertex = 0) const;
		void unbindInstanceData() const;

		void bindAttributesBegin()
		{
			bx::memCopy(m_unboundUsedAttrib, m_used, sizeof(m_unboundUsedAttrib) );
		}

		void bindAttributes(const VertexLayout& _layout, uint32_t _baseVertex = 0);

		void bindAttributesEnd()
		{
			for (uint32_t ii = 0, iiEnd = m_usedCount; ii < iiEnd; ++ii)
			{
				if (Attrib::Count != m_unboundUsedAttrib[ii])
				{
					Attrib::Enum attr = Attrib::Enum(m_unboundUsedAttrib[ii]);
					GLint loc = m_attributes[attr];
					GL_CHECK(lazyDisableVertexAttribArray(loc) );
				}
			}
		}

		void unbindAttributes();

		GLuint m_id;

		uint8_t m_unboundUsedAttrib[Attrib::Count]; // For tracking unbound used attributes between begin()/end().
		uint8_t m_usedCount;
		uint8_t m_used[Attrib::Count]; // Dense.
		GLint m_attributes[Attrib::Count]; // Sparse.
		GLint m_instanceData[BGFX_CONFIG_MAX_INSTANCE_DATA_COUNT+1];

		SamplerGL m_sampler[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
		uint8_t m_numSamplers;

		UniformBuffer* m_constantBuffer;
		PredefinedUniform m_predefined[PredefinedUniform::Count];
		uint8_t m_numPredefined;
	};

	struct TimerQueryGL
	{
		TimerQueryGL()
			: m_control(BX_COUNTOF(m_query) )
		{
		}

		void create()
		{
			for (uint32_t ii = 0; ii < BX_COUNTOF(m_query); ++ii)
			{
				Query& query = m_query[ii];
				query.m_ready = false;
				GL_CHECK(glGenQueries(1, &query.m_begin) );
				GL_CHECK(glGenQueries(1, &query.m_end) );
			}

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_result); ++ii)
			{
				Result& result = m_result[ii];
				result.reset();
			}
		}

		void destroy()
		{
			for (uint32_t ii = 0; ii < BX_COUNTOF(m_query); ++ii)
			{
				Query& query = m_query[ii];
				GL_CHECK(glDeleteQueries(1, &query.m_begin) );
				GL_CHECK(glDeleteQueries(1, &query.m_end) );
			}
		}

		uint32_t begin(uint32_t _resultIdx)
		{
			while (0 == m_control.reserve(1) )
			{
				update();
			}

			Result& result = m_result[_resultIdx];
			++result.m_pending;

			const uint32_t idx = m_control.m_current;
			Query& query = m_query[idx];
			query.m_resultIdx = _resultIdx;
			query.m_ready     = false;

			GL_CHECK(glQueryCounter(query.m_begin
				, GL_TIMESTAMP
				) );

			m_control.commit(1);

			return idx;
		}

		void end(uint32_t _idx)
		{
			Query& query = m_query[_idx];
			query.m_ready = true;

			GL_CHECK(glQueryCounter(query.m_end
				, GL_TIMESTAMP
				) );

			while (update() )
			{
			}
		}

		bool update()
		{
			if (0 != m_control.available() )
			{
				Query& query = m_query[m_control.m_read];

				if (!query.m_ready)
				{
					return false;
				}

				GLint available;
				GL_CHECK(glGetQueryObjectiv(query.m_end
					, GL_QUERY_RESULT_AVAILABLE
					, &available
					) );

				if (available)
				{
					m_control.consume(1);

					Result& result = m_result[query.m_resultIdx];
					--result.m_pending;

					GL_CHECK(glGetQueryObjectui64v(query.m_begin
						, GL_QUERY_RESULT
						, &result.m_begin
						) );

					GL_CHECK(glGetQueryObjectui64v(query.m_end
						, GL_QUERY_RESULT
						, &result.m_end
						) );

					return true;
				}
			}

			return false;
		}

		struct Result
		{
			void reset()
			{
				m_begin   = 0;
				m_end     = 0;
				m_pending = 0;
			}

			uint64_t m_begin;
			uint64_t m_end;
			uint32_t m_pending;
		};

		struct Query
		{
			GLuint   m_begin;
			GLuint   m_end;
			uint32_t m_resultIdx;
			bool     m_ready;
		};

		Result m_result[BGFX_CONFIG_MAX_VIEWS+1];

		Query m_query[BGFX_CONFIG_MAX_VIEWS*4];
		bx::RingBufferControl m_control;
	};

	struct OcclusionQueryGL
	{
		OcclusionQueryGL()
			: m_control(BX_COUNTOF(m_query) )
		{
		}

		void create();
		void destroy();
		void begin(Frame* _render, OcclusionQueryHandle _handle);
		void end();
		void resolve(Frame* _render, bool _wait = false);
		void invalidate(OcclusionQueryHandle _handle);

		struct Query
		{
			GLuint m_id;
			OcclusionQueryHandle m_handle;
		};

		Query m_query[BGFX_CONFIG_MAX_OCCLUSION_QUERIES];
		bx::RingBufferControl m_control;
	};

	class LineReader : public bx::ReaderI
	{
	public:
		LineReader(const void* _str)
			: m_str( (const char*)_str)
			, m_pos(0)
			, m_size(bx::strLen( (const char*)_str) )
		{
		}

		LineReader(const bx::StringView& _str)
			: m_str(_str.getPtr() )
			, m_pos(0)
			, m_size(_str.getLength() )
		{
		}

		virtual int32_t read(void* _data, int32_t _size, bx::Error* _err) override
		{
			if (m_str[m_pos] == '\0'
			||  m_pos == m_size)
			{
				BX_ERROR_SET(_err, BX_ERROR_READERWRITER_EOF, "LineReader: EOF.");
				return 0;
			}

			uint32_t pos = m_pos;
			const char* str = &m_str[pos];
			const char* nl = bx::strFindNl(str).getPtr();
			pos += (uint32_t)(nl - str);

			const char* eol = &m_str[pos];

			uint32_t size = bx::uint32_min(uint32_t(eol - str), _size);

			bx::memCopy(_data, str, size);
			m_pos += size;

			return size;
		}

		const char* m_str;
		uint32_t m_pos;
		uint32_t m_size;
	};

} /* namespace gl */ } // namespace bgfx

#endif // BGFX_RENDERER_GL_H_HEADER_GUARD
