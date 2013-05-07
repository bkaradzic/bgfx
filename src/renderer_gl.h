/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef __RENDERER_GL_H__
#define __RENDERER_GL_H__

#define BGFX_USE_EGL 0
#define BGFX_USE_WGL 0
#define BGFX_USE_NSGL 0

#if BGFX_CONFIG_RENDERER_OPENGL
#	if BGFX_CONFIG_RENDERER_OPENGL >= 31
#		include <gl/glcorearb.h>
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

// remove deprecated from glext.h
#		define GL_VERSION_1_2_DEPRECATED
#		define GL_ARB_imaging_DEPRECATED
#		define GL_VERSION_1_3_DEPRECATED
#		define GL_VERSION_1_4_DEPRECATED
#		define GL_VERSION_1_5_DEPRECATED
#		define GL_VERSION_2_0_DEPRECATED
#		define GL_VERSION_2_1_DEPRECATED
// ignore everything above 2.1
#		define GL_VERSION_3_0
#		define GL_VERSION_3_0_DEPRECATED
#		define GL_VERSION_3_1
#		define GL_VERSION_3_2
#		define GL_VERSION_3_3
#		define GL_VERSION_4_0
#		define GL_VERSION_4_1
#		define GL_VERSION_4_2
#		include <gl/glext.h>
#	endif // BGFX_CONFIG_RENDERER_OPENGL >= 31

#	define glVertexAttribDivisor glVertexAttribDivisorARB
#	define glDrawArraysInstanced glDrawArraysInstancedARB
#	define glDrawElementsInstanced glDrawElementsInstancedARB

#	if BX_PLATFORM_WINDOWS
#		undef BGFX_USE_WGL
#		define BGFX_USE_WGL 1
#	endif // BX_PLATFORM_

#elif BGFX_CONFIG_RENDERER_OPENGLES2 || BGFX_CONFIG_RENDERER_OPENGLES3
#	if BGFX_CONFIG_RENDERER_OPENGLES2
#		include <GLES2/gl2platform.h>
#		include <GLES2/gl2.h>
#		include <GLES2/gl2ext.h>
#		define glProgramBinary glProgramBinaryOES
#		define glGetProgramBinary glGetProgramBinaryOES
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
#		define GL_SAMPLER_3D GL_SAMPLER_3D_OES
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

#	ifndef GL_LUMINANCE
#		define GL_LUMINANCE 0x1909
#	endif // GL_LUMINANCE

#	ifndef GL_BGRA_EXT
#		define GL_BGRA_EXT 0x80E1
#	endif // GL_BGRA_EXT

#	ifndef GL_R16F_EXT
#		define GL_R16F_EXT 0x822D
#	endif // GL_R16F_EXT

#	ifndef GL_R32F_EXT
#		define GL_R32F_EXT 0x822E
#	endif // GL_R32F_EXT

#	ifndef GL_RGB10_A2_EXT
#		define GL_RGB10_A2_EXT 0x8059
#	endif // GL_RGB10_A2_EXT

#	ifndef GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
#		define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT 0x83F1
#	endif // GL_COMPRESSED_RGBA_S3TC_DXT1_EXT

#	ifndef GL_COMPRESSED_RGBA_S3TC_DXT3_EXT
#		define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT 0x83F2
#	endif // GL_COMPRESSED_RGBA_S3TC_DXT3_EXT

#	ifndef GL_COMPRESSED_RGBA_S3TC_DXT5_EXT
#		define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT 0x83F3
#	endif // GL_COMPRESSED_RGBA_S3TC_DXT5_EXT

#	ifndef GL_COMPRESSED_LUMINANCE_LATC1_EXT
#		define GL_COMPRESSED_LUMINANCE_LATC1_EXT 0x8C70
#	endif // GL_COMPRESSED_LUMINANCE_LATC1_EXT

#	ifndef GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT
#		define GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT 0x8C72
#	endif // GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT

#	ifndef GL_COMPRESSED_RED_RGTC1_EXT
#		define GL_COMPRESSED_RED_RGTC1_EXT 0x8DBB
#	endif // GL_COMPRESSED_RED_RGTC1_EXT

#	ifndef GL_COMPRESSED_RED_GREEN_RGTC2_EXT
#		define GL_COMPRESSED_RED_GREEN_RGTC2_EXT 0x8DBD
#	endif // GL_COMPRESSED_RED_GREEN_RGTC2_EXT

#	ifndef GL_TRANSLATED_SHADER_SOURCE_LENGTH_ANGLE
#		define GL_TRANSLATED_SHADER_SOURCE_LENGTH_ANGLE 0x93A0
#	endif // GL_TRANSLATED_SHADER_SOURCE_LENGTH_ANGLE

#	ifndef GL_TEXTURE_MAX_ANISOTROPY_EXT
#		define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE
#	endif // GL_TEXTURE_MAX_ANISOTROPY_EXT

#	ifndef GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT
#		define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#	endif // GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT

#	ifndef GL_VBO_FREE_MEMORY_ATI
#		define GL_VBO_FREE_MEMORY_ATI 0x87FB
#	endif // GL_VBO_FREE_MEMORY_ATI

#	ifndef GL_TEXTURE_FREE_MEMORY_ATI
#		define GL_TEXTURE_FREE_MEMORY_ATI 0x87FC
#	endif // GL_TEXTURE_FREE_MEMORY_ATI

#	ifndef GL_RENDERBUFFER_FREE_MEMORY_ATI
#		define GL_RENDERBUFFER_FREE_MEMORY_ATI 0x87FD
#	endif // GL_RENDERBUFFER_FREE_MEMORY_ATI

// http://developer.download.nvidia.com/opengl/specs/GL_NVX_gpu_memory_info.txt
#	ifndef GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX
#		define GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX 0x9047
#	endif // GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX

#	ifndef GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX
#		define GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX 0x9048
#	endif // GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX

#	ifndef GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX
#		define GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX 0x9049
#	endif // GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX

#	ifndef GL_GPU_MEMORY_INFO_EVICTION_COUNT_NVX
#		define GL_GPU_MEMORY_INFO_EVICTION_COUNT_NVX 0x904A
#	endif // GL_GPU_MEMORY_INFO_EVICTION_COUNT_NVX

#	ifndef GL_GPU_MEMORY_INFO_EVICTED_MEMORY_NVX
#		define GL_GPU_MEMORY_INFO_EVICTED_MEMORY_NVX 0x904B
#	endif // GL_GPU_MEMORY_INFO_EVICTED_MEMORY_NVX

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
#	define _GREMEDY_SETMARKER(_string) \
					do \
					{ \
						if (NULL != glStringMarkerGREMEDY) \
						{ \
							glStringMarkerGREMEDY( (GLsizei)strlen(_string), _string); \
						} \
					} while(0)
#	define _GREMEDY_FRAMETERMINATOR() \
					do \
					{ \
						if (NULL != glStringMarkerGREMEDY) \
						{ \
							glFrameTerminatorGREMEDY(); \
						} \
					} while(0)
#else
#	define _GREMEDY_SETMARKER(_string) do {} while(0)
#	define _GREMEDY_FRAMETERMINATOR() do {} while(0)
#endif // BGFX_CONFIG_DEBUG_GREMEDY

#define GREMEDY_SETMARKER(_string) _GREMEDY_SETMARKER(_string)
#define GREMEDY_FRAMETERMINATOR() _GREMEDY_FRAMETERMINATOR()

#define GL_IMPORT(_optional, _proto, _func) extern _proto _func
#include "glimports.h"
#undef GL_IMPORT

	void dumpExtensions(const char* _extensions);

	class ConstantBuffer;
	
	class VaoCache
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

		void invalidate(VaoCache& _vaoCache)
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
			, m_compressed(false)
		{
		}

		void init(GLenum _target, uint8_t _numMips, uint32_t _flags);
		void create(const Memory* _mem, uint32_t _flags);
		void createColor(uint32_t _colorFormat, uint32_t _width, uint32_t _height, GLenum _min, GLenum _mag);
		void createDepth(uint32_t _width, uint32_t _height);
		void destroy();
		void update(uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, const Memory* _mem);

		GLuint m_id;
		GLenum m_target;
		GLenum m_fmt;
		GLenum m_type;
		bool m_compressed;
	};

	struct Shader
	{
		void create(GLenum _type, Memory* _mem)
		{
			m_id = glCreateShader(_type);
			m_type = _type;

			bx::MemoryReader reader(_mem->data, _mem->size);
			m_hash = hashMurmur2A(_mem->data, _mem->size);

			uint32_t magic;
			bx::read(&reader, magic);

			uint32_t iohash;
			bx::read(&reader, iohash);

			const uint8_t* code = reader.getDataPtr();

			if (0 != m_id)
			{
				GL_CHECK(glShaderSource(m_id, 1, (const GLchar**)&code, NULL) );
				GL_CHECK(glCompileShader(m_id) );

				GLint compiled = 0;
				GL_CHECK(glGetShaderiv(m_id, GL_COMPILE_STATUS, &compiled) );

				if (0 == compiled)
				{
					char log[1024];
					GL_CHECK(glGetShaderInfoLog(m_id, sizeof(log), NULL, log) );
					BX_TRACE("Failed to compile shader. %d: %s", compiled, log);
					BX_TRACE("\n####\n%s\n####", code);

					GL_CHECK(glDeleteShader(m_id) );
					BGFX_FATAL(false, bgfx::Fatal::InvalidShader, "Failed to compile shader.");
				}
			}
		}

		void destroy()
		{
			GL_CHECK(glDeleteShader(m_id) );
		}

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
			glGenQueries(countof(m_queries), m_queries);
		}

		void destroy()
		{
			glDeleteQueries(countof(m_queries), m_queries);
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

#endif // __RENDERER_GL_H__
