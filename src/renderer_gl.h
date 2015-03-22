/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef BGFX_RENDERER_GL_H_HEADER_GUARD
#define BGFX_RENDERER_GL_H_HEADER_GUARD

#define BGFX_USE_EGL (BGFX_CONFIG_RENDERER_OPENGLES && (0 \
			|| BX_PLATFORM_ANDROID \
			|| BX_PLATFORM_EMSCRIPTEN \
			|| BX_PLATFORM_LINUX \
			|| BX_PLATFORM_QNX \
			|| BX_PLATFORM_RPI \
			|| BX_PLATFORM_WINDOWS \
			) )

#define BGFX_USE_WGL (BGFX_CONFIG_RENDERER_OPENGL && BX_PLATFORM_WINDOWS)
#define BGFX_USE_GLX (BGFX_CONFIG_RENDERER_OPENGL && (0 \
			|| BX_PLATFORM_LINUX \
			|| BX_PLATFORM_FREEBSD \
			) )

#define BGFX_USE_GL_DYNAMIC_LIB (0 \
			|| BX_PLATFORM_LINUX \
			|| BX_PLATFORM_OSX \
			|| BX_PLATFORM_WINDOWS \
			)

#if BGFX_CONFIG_RENDERER_OPENGL
#	if BGFX_CONFIG_RENDERER_OPENGL >= 31
#		include <gl/glcorearb.h>
#		if BX_PLATFORM_OSX
#			define GL_ARB_shader_objects // OSX collsion with GLhandleARB in gltypes.h
#		endif // BX_PLATFORM_OSX
#	else
#		if BX_PLATFORM_LINUX
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
#		define GL_TEXTURE_3D GL_TEXTURE_3D_OES
#		define GL_SAMPLER_3D GL_SAMPLER_3D_OES
#		define GL_TEXTURE_WRAP_R GL_TEXTURE_WRAP_R_OES
#		define GL_MIN GL_MIN_EXT
#		define GL_MAX GL_MAX_EXT
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

#	if BX_PLATFORM_EMSCRIPTEN
#		include <emscripten/emscripten.h>
#	endif // BX_PLATFORM_EMSCRIPTEN
#endif // BGFX_CONFIG_RENDERER_OPENGL

#include "renderer.h"
#include "ovr.h"
#include "renderdoc.h"

#ifndef GL_LUMINANCE
#	define GL_LUMINANCE 0x1909
#endif // GL_LUMINANCE

#ifndef GL_BGRA
#	define GL_BGRA 0x80E1
#endif // GL_BGRA

#ifndef GL_R8
#	define GL_R8 0x8229
#endif // GL_R8

#ifndef GL_R16
#	define GL_R16 0x822A
#endif // GL_R16

#ifndef GL_R16F
#	define GL_R16F 0x822D
#endif // GL_R16F

#ifndef GL_R32UI
#	define GL_R32UI 0x8236
#endif // GL_R32UI

#ifndef GL_R32F
#	define GL_R32F 0x822E
#endif // GL_R32F

#ifndef GL_RG8
#	define GL_RG8 0x822B
#endif // GL_RG8

#ifndef GL_RG16
#	define GL_RG16 0x822C
#endif // GL_RG16

#ifndef GL_RG16UI
#	define GL_RG16UI 0x823A
#endif // GL_RG16UI

#ifndef GL_RG16F
#	define GL_RG16F 0x822F
#endif // GL_RG16F

#ifndef GL_R32UI
#	define GL_R32UI 0x8236
#endif // GL_R32UI

#ifndef GL_RG32UI
#	define GL_RG32UI 0x823C
#endif // GL_RG32UI

#ifndef GL_RG32F
#	define GL_RG32F 0x8230
#endif // GL_RG32F

#ifndef GL_RGBA32UI
#	define GL_RGBA32UI 0x8D70
#endif // GL_RGBA32UI

#ifndef GL_RGBA32F
#	define GL_RGBA32F 0x8814
#endif // GL_RGBA32F

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

#ifndef GL_R11F_G11F_B10F
#	define GL_R11F_G11F_B10F 0x8C3A
#endif // GL_R11F_G11F_B10F

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

#ifndef GL_QUERY_RESULT
#	define GL_QUERY_RESULT 0x8866
#endif // GL_QUERY_RESULT

#ifndef GL_READ_FRAMEBUFFER
#	define GL_READ_FRAMEBUFFER 0x8CA8
#endif /// GL_READ_FRAMEBUFFER

#ifndef GL_DRAW_FRAMEBUFFER
#	define GL_DRAW_FRAMEBUFFER 0x8CA9
#endif // GL_DRAW_FRAMEBUFFER

#ifndef GL_TIME_ELAPSED
#	define GL_TIME_ELAPSED 0x88BF
#endif // GL_TIME_ELAPSED

#ifndef GL_VBO_FREE_MEMORY_ATI
#	define GL_VBO_FREE_MEMORY_ATI 0x87FB
#endif // GL_VBO_FREE_MEMORY_ATI

#ifndef GL_TEXTURE_FREE_MEMORY_ATI
#	define GL_TEXTURE_FREE_MEMORY_ATI 0x87FC
#endif // GL_TEXTURE_FREE_MEMORY_ATI

#ifndef GL_RENDERBUFFER_FREE_MEMORY_ATI
#	define GL_RENDERBUFFER_FREE_MEMORY_ATI 0x87FD
#endif // GL_RENDERBUFFER_FREE_MEMORY_ATI

// http://developer.download.nvidia.com/opengl/specs/GL_NVX_gpu_memory_info.txt
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

#ifndef GL_INT_SAMPLER_2D
#	define GL_INT_SAMPLER_2D 0x8DCA
#endif // GL_INT_SAMPLER_2D

#ifndef GL_UNSIGNED_INT_SAMPLER_2D
#	define GL_UNSIGNED_INT_SAMPLER_2D 0x8DD2
#endif // GL_UNSIGNED_INT_SAMPLER_2D

#ifndef GL_INT_SAMPLER_3D
#	define GL_INT_SAMPLER_3D 0x8DCB
#endif // GL_INT_SAMPLER_3D

#ifndef GL_UNSIGNED_INT_SAMPLER_3D
#	define GL_UNSIGNED_INT_SAMPLER_3D 0x8DD3
#endif // GL_UNSIGNED_INT_SAMPLER_3D

#ifndef GL_INT_SAMPLER_CUBE
#	define GL_INT_SAMPLER_CUBE 0x8DCC
#endif // GL_INT_SAMPLER_CUBEER_3D

#ifndef GL_UNSIGNED_INT_SAMPLER_CUBE
#	define GL_UNSIGNED_INT_SAMPLER_CUBE 0x8DD4
#endif // GL_UNSIGNED_INT_SAMPLER_CUBE

#ifndef GL_SAMPLER_2D_SHADOW
#	define GL_SAMPLER_2D_SHADOW 0x8B62
#endif // GL_SAMPLER_2D_SHADOW

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

#if BX_PLATFORM_NACL
#	include "glcontext_ppapi.h"
#elif BX_PLATFORM_WINDOWS
#	include <windows.h>
#elif BX_PLATFORM_LINUX
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
	class ConstantBuffer;
} // namespace bgfx

namespace bgfx { namespace gl
{
	void dumpExtensions(const char* _extensions);

	const char* glEnumName(GLenum _enum);

#define _GL_CHECK(_check, _call) \
				BX_MACRO_BLOCK_BEGIN \
					/*BX_TRACE(#_call);*/ \
					_call; \
					GLenum err = glGetError(); \
					_check(0 == err, #_call "; GL error 0x%x: %s", err, glEnumName(err) ); \
					BX_UNUSED(err); \
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

	class VaoStateCache
	{
	public:
		GLuint add(uint32_t _hash)
		{
			invalidate(_hash);

			GLuint arrayId;
			GL_CHECK(glGenVertexArrays(1, &arrayId) );

			m_hashMap.insert(stl::make_pair(_hash, arrayId) );

			return arrayId;
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
			GL_CHECK(glBindVertexArray(0) );

			HashMap::iterator it = m_hashMap.find(_hash);
			if (it != m_hashMap.end() )
			{
				GL_CHECK(glDeleteVertexArrays(1, &it->second) );
				m_hashMap.erase(it);
			}
		}

		void invalidate()
		{
			GL_CHECK(glBindVertexArray(0) );

			for (HashMap::iterator it = m_hashMap.begin(), itEnd = m_hashMap.end(); it != itEnd; ++it)
			{
				GL_CHECK(glDeleteVertexArrays(1, &it->second) );
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

	class VaoCacheRef
	{
	public:
		void add(uint32_t _hash)
		{
			m_vaoSet.insert(_hash);
		}

		void invalidate(VaoStateCache& _vaoCache)
		{
			for (VaoSet::iterator it = m_vaoSet.begin(), itEnd = m_vaoSet.end(); it != itEnd; ++it)
			{
				_vaoCache.invalidate(*it);
			}

			m_vaoSet.clear();
		}

		typedef stl::unordered_set<uint32_t> VaoSet;
		VaoSet m_vaoSet;
	};

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
		void create(uint32_t _size, void* _data)
		{
			m_size = _size;

			GL_CHECK(glGenBuffers(1, &m_id) );
			BX_CHECK(0 != m_id, "Failed to generate buffer id.");
			GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id) );
			GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER
				, _size
				, _data
				, (NULL==_data)?GL_DYNAMIC_DRAW:GL_STATIC_DRAW
				) );
			GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) );
		}

		void update(uint32_t _offset, uint32_t _size, void* _data)
		{
			BX_CHECK(0 != m_id, "Updating invalid index buffer.");
			GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id) );
			GL_CHECK(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER
				, _offset
				, _size
				, _data
				) );
			GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) );
		}

		void destroy();

		void add(uint32_t _hash)
		{
			m_vcref.add(_hash);
		}

		GLuint m_id;
		uint32_t m_size;
		VaoCacheRef m_vcref;
	};

	struct VertexBufferGL
	{
		void create(uint32_t _size, void* _data, VertexDeclHandle _declHandle)
		{
			m_size = _size;
			m_decl = _declHandle;

			GL_CHECK(glGenBuffers(1, &m_id) );
			BX_CHECK(0 != m_id, "Failed to generate buffer id.");
			GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_id) );
			GL_CHECK(glBufferData(GL_ARRAY_BUFFER
				, _size
				, _data
				, (NULL==_data)?GL_DYNAMIC_DRAW:GL_STATIC_DRAW
				) );
			GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0) );
		}

		void update(uint32_t _offset, uint32_t _size, void* _data)
		{
			BX_CHECK(0 != m_id, "Updating invalid vertex buffer.");
			GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_id) );
			GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER
				, _offset
				, _size
				, _data
				) );
			GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0) );
		}

		void destroy();

		void add(uint32_t _hash)
		{
			m_vcref.add(_hash);
		}

		GLuint m_id;
		uint32_t m_size;
		VertexDeclHandle m_decl;
		VaoCacheRef m_vcref;
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
			, m_currentFlags(UINT32_MAX)
			, m_numMips(0)
		{
		}

		bool init(GLenum _target, uint32_t _width, uint32_t _height, uint8_t _format, uint8_t _numMips, uint32_t _flags);
		void create(const Memory* _mem, uint32_t _flags, uint8_t _skip);
		void destroy();
		void update(uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem);
		void setSamplerState(uint32_t _flags);
		void commit(uint32_t _stage, uint32_t _flags);

		GLuint m_id;
		GLuint m_rbo;
		GLenum m_target;
		GLenum m_fmt;
		GLenum m_type;
		uint32_t m_flags;
		uint32_t m_currentFlags;
		uint32_t m_width;
		uint32_t m_height;
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

		void create(Memory* _mem);
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
		{
			memset(m_fbo, 0, sizeof(m_fbo) );
		}

		void create(uint8_t _num, const TextureHandle* _handles);
		void create(uint16_t _denseIdx, void* _nwh, uint32_t _width, uint32_t _height, TextureFormat::Enum _depthFormat);
		uint16_t destroy();
		void resolve();
		void discard(uint8_t _flags);

		SwapChainGL* m_swapChain;
		GLuint m_fbo[2];
		uint32_t m_width;
		uint32_t m_height;
		uint16_t m_denseIdx;
		uint8_t m_num;
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
 		void bindAttributes(const VertexDecl& _vertexDecl, uint32_t _baseVertex = 0) const;
		void bindInstanceData(uint32_t _stride, uint32_t _baseVertex = 0) const;

		void add(uint32_t _hash)
		{
			m_vcref.add(_hash);
		}

		GLuint m_id;

		uint8_t m_used[Attrib::Count+1]; // dense
		GLint m_attributes[Attrib::Count]; // sparse
		GLint m_instanceData[BGFX_CONFIG_MAX_INSTANCE_DATA_COUNT];

 		GLint m_sampler[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
 		uint8_t m_numSamplers;

		ConstantBuffer* m_constantBuffer;
		PredefinedUniform m_predefined[PredefinedUniform::Count];
		uint8_t m_numPredefined;
		VaoCacheRef m_vcref;
	};

	struct QueriesGL
	{
		void create()
		{
			glGenQueries(BX_COUNTOF(m_queries), m_queries);
		}

		void destroy()
		{
			glDeleteQueries(BX_COUNTOF(m_queries), m_queries);
		}

		void begin(uint16_t _id, GLenum _target) const
		{
			glBeginQuery(_target, m_queries[_id]);
		}

		void end(GLenum _target) const
		{
			glEndQuery(_target);
		}

		uint64_t getResult(uint16_t _id) const
		{
			uint64_t result;
			glGetQueryObjectui64v(m_queries[_id], GL_QUERY_RESULT, &result);
			return result;
		}

		GLuint m_queries[64];
	};

} /* namespace gl */ } // namespace bgfx

#endif // BGFX_RENDERER_GL_H_HEADER_GUARD
