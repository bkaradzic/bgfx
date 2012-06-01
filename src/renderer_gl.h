/*
 * Copyright 2011-2012 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef __RENDERER_GL_H__
#define __RENDERER_GL_H__

#if BGFX_CONFIG_RENDERER_OPENGL
#	include <GL/gl.h>
#	include <gl/glext.h>
#elif BGFX_CONFIG_RENDERER_OPENGLES
#	include <GLES2/gl2.h>

#	ifndef GL_BGRA_EXT
#		define GL_BGRA_EXT 0x80E1
#	endif // GL_BGRA_EXT

#	ifndef GL_COMPRESSED_RGB_S3TC_DXT1_EXT
#		define GL_COMPRESSED_RGB_S3TC_DXT1_EXT 0x83F0
#	endif // GL_COMPRESSED_RGB_S3TC_DXT1_EXT

#	ifndef GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
#		define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT 0x83F1
#	endif // GL_COMPRESSED_RGBA_S3TC_DXT1_EXT

#	ifndef GL_COMPRESSED_RGBA_S3TC_DXT3_EXT
#		define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT 0x83F2
#	endif // GL_COMPRESSED_RGBA_S3TC_DXT3_EXT

#	ifndef GL_COMPRESSED_RGBA_S3TC_DXT5_EXT
#		define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT 0x83F3
#	endif // GL_COMPRESSED_RGBA_S3TC_DXT5_EXT

#	ifndef GL_FRAGMENT_SHADER_DERIVATIVE_HINT_OES
#		define GL_FRAGMENT_SHADER_DERIVATIVE_HINT_OES 0x8B8B
#	endif // GL_FRAGMENT_SHADER_DERIVATIVE_HINT_OES
#endif // BGFX_CONFIG_RENDERER_OPENGL

#if BX_PLATFORM_NACL
#	include <ppapi/gles2/gl2ext_ppapi.h>
#	include <ppapi/c/pp_completion_callback.h>
#	include <ppapi/c/ppb_instance.h>
#	include <ppapi/c/ppb_graphics_3d.h>
#elif BX_PLATFORM_WINDOWS
#	include <windows.h>
#elif BX_PLATFORM_LINUX
#	include <GL/glx.h>
#	include <X11/Xlib.h>
#endif // BX_PLATFORM_

#if BGFX_CONFIG_DEBUG_GREMEDY && (BX_PLATFORM_WINDOWS || BX_PLATFORM_LINUX)
#	include <gl/GRemedyGLExtensions.h>
#endif // BGFX_CONFIG_DEBUG_GREMEDY && (BX_PLATFORM_WINDOWS || BX_PLATFORM_LINUX)

namespace bgfx
{
#	define _GL_CHECK(_call) \
				do { \
					/*BX_TRACE(#_call);*/ \
					_call; \
					GLenum err = glGetError(); \
					BX_CHECK(0 == err, #_call "; glError 0x%x %d", err, err); \
				} while (0)

#if BGFX_CONFIG_DEBUG
#	define GL_CHECK(_call) _call // _GL_CHECK(_call)
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

#if BGFX_CONFIG_RENDERER_OPENGL
#	define GL_IMPORT(_optional, _proto, _func) extern _proto _func
#	include "glimports.h"
#	undef GL_IMPORT
#endif // BGFX_CONFIG_RENDERER_OPENGL
	
	class ConstantBuffer;
	
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

		void update(uint32_t _size, void* _data)
		{
			GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id) );
			GL_CHECK(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER
				, 0
				, _size
				, _data
				) );
			GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) );
		}

		void destroy()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glDeleteBuffers(1, &m_id);
		}

		GLuint m_id;
		uint32_t m_size;
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

		void update(uint32_t _size, void* _data)
		{
			GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_id) );
			GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER
				, 0
				, _size
				, _data
				) );
			GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0) );
		}

		void destroy()
		{
			GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0) );
			GL_CHECK(glDeleteBuffers(1, &m_id) );
		}

		GLuint m_id;
		uint32_t m_size;
		VertexDeclHandle m_decl;
	};

	struct Texture
	{
		Texture()
			: m_id(0)
			, m_target(GL_TEXTURE_2D)
		{
		}

		void create(const Memory* _mem, uint32_t _flags);
		void createColor(uint32_t _width, uint32_t _height);
		void createDepth(uint32_t _width, uint32_t _height);
		void destroy();

		GLuint m_id;
		GLenum m_target;
	};

	struct Shader
	{
		void create(GLenum _type, const uint8_t* _code)
		{
			m_id = glCreateShader(_type);
			m_type = _type;

			if (0 != m_id)
			{
				m_hash = hash(_code, (uint32_t)strlen( (const char*)_code) );
				GL_CHECK(glShaderSource(m_id, 1, (const GLchar**)&_code, NULL) );
				GL_CHECK(glCompileShader(m_id) );

				GLint compiled = 0;
				GL_CHECK(glGetShaderiv(m_id, GL_COMPILE_STATUS, &compiled) );

				if (0 == compiled)
				{
					char log[1024];
					GL_CHECK(glGetShaderInfoLog(m_id, sizeof(log), NULL, log) );
					BX_TRACE("Failed to compile shader. %d: %s", compiled, log);
					BX_TRACE("\n####\n%s\n####", _code);

					GL_CHECK(glDeleteShader(m_id) );
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
		void create(uint16_t _width, uint16_t _height, uint32_t _flags);
		void destroy();

		GLsizei m_width;
		GLsizei m_height;
		Texture m_color;
		Texture m_depth;
		GLuint m_fbo;
		GLuint m_rbo;
	};

	struct Material
	{
		void create(const Shader& _vsh, const Shader& _fsh);
		void destroy();
 		void init();
 		void bindAttributes(const VertexDecl& _vertexDecl, uint32_t _baseVertex = 0);
 
		GLuint m_id;

		uint8_t m_used[Attrib::Count+1]; // dense
		uint16_t m_attributes[Attrib::Count]; // sparse
		uint32_t m_enabled;

 		GLuint m_sampler[BGFX_CONFIG_MAX_TEXTURES];
 		uint8_t m_numSamplers;

		ConstantBuffer* m_constantBuffer;
		PredefinedUniform m_predefined[PredefinedUniform::Count];
		uint8_t m_numPredefined;
	};

} // namespace bgfx

#endif // __RENDERER_GL_H__
