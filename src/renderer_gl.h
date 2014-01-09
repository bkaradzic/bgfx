/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef BGFX_RENDERER_GL_H_HEADER_GUARD
#define BGFX_RENDERER_GL_H_HEADER_GUARD

#define BGFX_USE_EGL 0
#define BGFX_USE_WGL 0
#define BGFX_USE_NSGL 0

#if BGFX_CONFIG_RENDERER_OPENGL
#	if BGFX_CONFIG_RENDERER_OPENGL >= 31
#		define GLCOREARB_PROTOTYPES
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

#	if BX_PLATFORM_WINDOWS
#		undef BGFX_USE_WGL
#		define BGFX_USE_WGL 1
#	endif // BX_PLATFORM_

#elif BGFX_CONFIG_RENDERER_OPENGLES2 || BGFX_CONFIG_RENDERER_OPENGLES3
#	if BGFX_CONFIG_RENDERER_OPENGLES2
#		if BX_PLATFORM_IOS
#			include <OpenGLES/ES2/gl.h>
#			include <OpenGLES/ES2/glext.h>

typedef void (GL_APIENTRYP PFNGLBINDVERTEXARRAYOESPROC) (GLuint array);
typedef void (GL_APIENTRYP PFNGLDELETEVERTEXARRAYSOESPROC) (GLsizei n, const GLuint *arrays);
typedef void (GL_APIENTRYP PFNGLGENVERTEXARRAYSOESPROC) (GLsizei n, GLuint *arrays);
typedef GLboolean (GL_APIENTRYP PFNGLISVERTEXARRAYOESPROC) (GLuint array);
typedef void (GL_APIENTRYP PFNGLGETPROGRAMBINARYOESPROC) (GLuint program, GLsizei bufSize, GLsizei *length, GLenum *binaryFormat, GLvoid *binary);
typedef void (GL_APIENTRYP PFNGLPROGRAMBINARYOESPROC) (GLuint program, GLenum binaryFormat, const GLvoid *binary, GLint length);
typedef void (GL_APIENTRYP PFNGLTEXIMAGE3DOESPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid* pixels);
typedef void (GL_APIENTRYP PFNGLTEXSUBIMAGE3DOESPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid* pixels);
typedef void (GL_APIENTRYP PFNGLCOMPRESSEDTEXIMAGE3DOESPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid* data);
typedef void (GL_APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE3DOESPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid* data);
typedef void (GL_APIENTRYP PFLGLDRAWARRAYSINSTANCEDANGLEPROC) (GLenum mode, GLint first, GLsizei count, GLsizei primcount);
typedef void (GL_APIENTRYP PFLGLDRAWELEMENTSINSTANCEDANGLEPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei primcount);
typedef void (GL_APIENTRYP PFLGLVERTEXATTRIBDIVISORANGLEPROC) (GLuint index, GLuint divisor);
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
#		define glProgramBinary glProgramBinaryOES
#		define glGetProgramBinary glGetProgramBinaryOES
#		define glTexImage3D glTexImage3DOES
#		define glTexSubImage3D glTexSubImage3DOES
#		define glCompressedTexImage3D glCompressedTexImage3DOES
#		define glCompressedTexSubImage3D glCompressedTexSubImage3DOES
#		define glBindVertexArray glBindVertexArrayOES
#		define glDeleteVertexArrays glDeleteVertexArraysOES
#		define glGenVertexArrays glGenVertexArraysOES
#		define GL_PROGRAM_BINARY_LENGTH GL_PROGRAM_BINARY_LENGTH_OES
#		define GL_HALF_FLOAT GL_HALF_FLOAT_OES
#		define GL_RGBA8 GL_RGBA //GL_RGBA8_OES
#		define GL_RGB10_A2 GL_RGB10_A2_EXT
#		define GL_R16F GL_R16F_EXT
#		define GL_R32F GL_R32F_EXT
#		define GL_UNSIGNED_INT_2_10_10_10_REV GL_UNSIGNED_INT_2_10_10_10_REV_EXT
#		define GL_TEXTURE_3D GL_TEXTURE_3D_OES
#		define GL_SAMPLER_3D GL_SAMPLER_3D_OES
#		define GL_TEXTURE_WRAP_R GL_TEXTURE_WRAP_R_OES
#		define GL_MIN GL_MIN_EXT
#		define GL_MAX GL_MAX_EXT
#	elif BGFX_CONFIG_RENDERER_OPENGLES3
#		include <GLES3/gl3platform.h>
#		include <GLES3/gl3.h>
#		include <GLES3/gl3ext.h>
#	endif // BGFX_CONFIG_RENDERER_

#	if BX_PLATFORM_ANDROID || BX_PLATFORM_EMSCRIPTEN || BX_PLATFORM_WINDOWS || BX_PLATFORM_QNX
#		undef BGFX_USE_EGL
#		define BGFX_USE_EGL 1
#		include "glcontext_egl.h"
#	endif // BX_PLATFORM_

#	if BX_PLATFORM_EMSCRIPTEN
#		include <emscripten/emscripten.h>
#	endif // BX_PLATFORM_EMSCRIPTEN

typedef void (*PFNGLGETTRANSLATEDSHADERSOURCEANGLEPROC)(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source);

#endif // BGFX_CONFIG_RENDERER_OPENGL

#ifndef GL_LUMINANCE
#	define GL_LUMINANCE 0x1909
#endif // GL_LUMINANCE

#ifndef GL_BGRA_EXT
#	define GL_BGRA_EXT 0x80E1
#endif // GL_BGRA_EXT

#ifndef GL_R16F_EXT
#	define GL_R16F_EXT 0x822D
#endif // GL_R16F_EXT

#ifndef GL_R32F_EXT
#	define GL_R32F_EXT 0x822E
#endif // GL_R32F_EXT

#ifndef GL_RGB10_A2_EXT
#	define GL_RGB10_A2_EXT 0x8059
#endif // GL_RGB10_A2_EXT

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

#ifndef GL_COMPRESSED_RED_RGTC1_EXT
#	define GL_COMPRESSED_RED_RGTC1_EXT 0x8DBB
#endif // GL_COMPRESSED_RED_RGTC1_EXT

#ifndef GL_COMPRESSED_RED_GREEN_RGTC2_EXT
#	define GL_COMPRESSED_RED_GREEN_RGTC2_EXT 0x8DBD
#endif // GL_COMPRESSED_RED_GREEN_RGTC2_EXT

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

#ifndef GL_TRANSLATED_SHADER_SOURCE_LENGTH_ANGLE
#	define GL_TRANSLATED_SHADER_SOURCE_LENGTH_ANGLE 0x93A0
#endif // GL_TRANSLATED_SHADER_SOURCE_LENGTH_ANGLE

#ifndef GL_TEXTURE_MAX_ANISOTROPY_EXT
#	define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE
#endif // GL_TEXTURE_MAX_ANISOTROPY_EXT

#ifndef GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT
#	define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#endif // GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT

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

#ifndef GL_RGBA16
#	define GL_RGBA16 0x805B
#endif // GL_RGBA16

#ifndef GL_RGBA16F
#	define GL_RGBA16F 0x881A
#endif // GL_RGBA16F

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

#if BGFX_CONFIG_DEBUG_GREMEDY && (BX_PLATFORM_WINDOWS || BX_PLATFORM_LINUX)
#	include <gl/GRemedyGLExtensions.h>
#endif // BGFX_CONFIG_DEBUG_GREMEDY && (BX_PLATFORM_WINDOWS || BX_PLATFORM_LINUX)

#if BGFX_USE_WGL
#	include "glcontext_wgl.h"
#endif // BGFX_USE_WGL

#ifndef GL_APIENTRY
#   define GL_APIENTRY APIENTRY
#endif // GL_APIENTRY

#ifndef GL_APIENTRYP
#   define GL_APIENTRYP GL_APIENTRY*
#endif // GL_APIENTRYP

#if !BGFX_CONFIG_RENDERER_OPENGL
#	define glClearDepth glClearDepthf
#endif // !BGFX_CONFIG_RENDERER_OPENGL

namespace bgfx
{
	// Both GL_ARB_instanced_arrays and GL_ANGLE_instanced_arrays use the same function signature.
	typedef void (GL_APIENTRYP PFNGLVERTEXATTRIBDIVISORBGFXPROC)(GLuint _index, GLuint _divisor);
	typedef void (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDBGFXPROC)(GLenum _mode, GLint _first, GLsizei _count, GLsizei _primcount);
	typedef void (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBGFXPROC)(GLenum _mode, GLsizei _count, GLenum _type, const GLvoid* _indices, GLsizei _primcount);

#	define _GL_CHECK(_call) \
				do { \
					/*BX_TRACE(#_call);*/ \
					_call; \
					GLenum err = glGetError(); \
					BX_CHECK(0 == err, #_call "; glError 0x%x %d", err, err); \
				} while (0)

#if BGFX_CONFIG_DEBUG
#	define GL_CHECK(_call) _GL_CHECK(_call)
#else
#	define GL_CHECK(_call) _call
#endif // BGFX_CONFIG_DEBUG

#if BGFX_CONFIG_DEBUG_GREMEDY
#	define _GREMEDY_SETMARKER(_string) glStringMarkerGREMEDY(0, _string)
#	define _GREMEDY_FRAMETERMINATOR() glFrameTerminatorGREMEDY()
#else
#	define _GREMEDY_SETMARKER(_string) do { BX_UNUSED(_string); } while(0)
#	define _GREMEDY_FRAMETERMINATOR() do {} while(0)
#endif // BGFX_CONFIG_DEBUG_GREMEDY

#define GREMEDY_SETMARKER(_string) _GREMEDY_SETMARKER(_string)
#define GREMEDY_FRAMETERMINATOR() _GREMEDY_FRAMETERMINATOR()

#define GL_IMPORT(_optional, _proto, _func, _import) extern _proto _func
#include "glimports.h"
#undef GL_IMPORT

	void dumpExtensions(const char* _extensions);

	class ConstantBuffer;

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

#if !BGFX_CONFIG_RENDERER_OPENGLES2
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

	private:
		typedef stl::unordered_map<uint32_t, GLuint> HashMap;
		HashMap m_hashMap;
	};
#endif // !BGFX_CONFIG_RENDERER_OPENGLES2

	struct IndexBuffer
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

	struct VertexBuffer
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

	struct Texture
	{
		Texture()
			: m_id(0)
			, m_target(GL_TEXTURE_2D)
			, m_fmt(GL_ZERO)
			, m_type(GL_ZERO)
			, m_flags(0)
			, m_currentFlags(UINT32_MAX)
			, m_numMips(0)
		{
		}

		void init(GLenum _target, uint8_t _format, uint8_t _numMips, uint32_t _flags);
		void create(const Memory* _mem, uint32_t _flags);
		void createColor(uint32_t _colorFormat, uint32_t _width, uint32_t _height, GLenum _min, GLenum _mag);
		void createDepth(uint32_t _width, uint32_t _height);
		void destroy();
		void update(uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem);
		void setSamplerState(uint32_t _flags);
		void commit(uint32_t _stage, uint32_t _flags);

		GLuint m_id;
		GLenum m_target;
		GLenum m_fmt;
		GLenum m_type;
		uint32_t m_flags;
		uint32_t m_currentFlags;
		uint8_t m_numMips;
		uint8_t m_requestedFormat;
		uint8_t m_textureFormat;
	};

	struct Shader
	{
		Shader()
			: m_id(0)
		{
		}

		void create(GLenum _type, Memory* _mem);
		void destroy();

		GLuint m_id;
		GLenum m_type;
		uint32_t m_hash;
	};

	struct RenderTarget
	{
		RenderTarget()
			: m_width(0)
			, m_height(0)
			, m_msaa(0)
		{
			memset(m_fbo, 0, sizeof(m_fbo) );
		}

		void create(uint16_t _width, uint16_t _height, uint32_t _flags, uint32_t _textureFlags);
		void destroy();
		void resolve();

		GLsizei m_width;
		GLsizei m_height;
		uint32_t m_msaa;
		Texture m_color;
		Texture m_depth;
		GLuint m_fbo[2];
		GLuint m_colorRbo;
		GLuint m_depthRbo;
	};

	struct Program
	{
		Program()
			: m_id(0)
			, m_constantBuffer(NULL)
			, m_numPredefined(0)
		{
		}

		void create(const Shader& _vsh, const Shader& _fsh);
		void destroy();
 		void init();
 		void bindAttributes(const VertexDecl& _vertexDecl, uint32_t _baseVertex = 0) const;
		void bindInstanceData(uint32_t _stride, uint32_t _baseVertex = 0) const;

		void commit()
		{
			m_constantBuffer->commit();
		}

		void add(uint32_t _hash)
		{
			m_vcref.add(_hash);
		}

		GLuint m_id;

		uint8_t m_used[Attrib::Count+1]; // dense
		GLint m_attributes[Attrib::Count]; // sparse
		GLint m_instanceData[BGFX_CONFIG_MAX_INSTANCE_DATA_COUNT];

 		GLint m_sampler[BGFX_CONFIG_MAX_TEXTURES];
 		uint8_t m_numSamplers;

		ConstantBuffer* m_constantBuffer;
		PredefinedUniform m_predefined[PredefinedUniform::Count];
		uint8_t m_numPredefined;
		VaoCacheRef m_vcref;
	};

#if BGFX_CONFIG_RENDERER_OPENGL
	struct Queries
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
#endif // BGFX_CONFIG_RENDERER_OPENGL

} // namespace bgfx

#endif // BGFX_RENDERER_GL_H_HEADER_GUARD
