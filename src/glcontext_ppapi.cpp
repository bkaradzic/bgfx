/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "bgfx_p.h"

#if BX_PLATFORM_NACL && (BGFX_CONFIG_RENDERER_OPENGLES || BGFX_CONFIG_RENDERER_OPENGL)
#	include <bgfx/bgfxplatform.h>
#	include "renderer_gl.h"

namespace bgfx { namespace gl
{
#	define GL_IMPORT(_optional, _proto, _func, _import) _proto _func
#	include "glimports.h"

	void naclSwapCompleteCb(void* /*_data*/, int32_t /*_result*/);

	PP_CompletionCallback naclSwapComplete =
	{
		naclSwapCompleteCb,
		NULL,
		PP_COMPLETIONCALLBACK_FLAG_NONE
	};

	struct Ppapi
	{
		Ppapi()
			: m_context(0)
			, m_instance(0)
			, m_instInterface(NULL)
			, m_graphicsInterface(NULL)
			, m_instancedArrays(NULL)
			, m_postSwapBuffers(NULL)
			, m_forceSwap(true)
		{
		}

		bool setInterfaces(PP_Instance _instance, const PPB_Instance* _instInterface, const PPB_Graphics3D* _graphicsInterface, PostSwapBuffersFn _postSwapBuffers);

		void resize(uint32_t _width, uint32_t _height, uint32_t /*_flags*/)
		{
			m_graphicsInterface->ResizeBuffers(m_context, _width, _height);
		}

		void swap()
		{
			glSetCurrentContextPPAPI(m_context);
			m_graphicsInterface->SwapBuffers(m_context, naclSwapComplete);
		}

		bool isValid() const
		{
			return 0 != m_context;
		}

		PP_Resource m_context;
		PP_Instance m_instance;
		const PPB_Instance* m_instInterface;
		const PPB_Graphics3D* m_graphicsInterface;
		const PPB_OpenGLES2InstancedArrays* m_instancedArrays;
		PostSwapBuffersFn m_postSwapBuffers;
		bool m_forceSwap;
	};

	static Ppapi s_ppapi;

	void naclSwapCompleteCb(void* /*_data*/, int32_t /*_result*/)
	{
		// For NaCl bgfx doesn't create render thread, but rendering is always
		// multithreaded. Frame rendering is done on main thread, and context
		// is initialized when PPAPI interfaces are set. Force swap is there to
		// keep calling swap complete callback, so that initialization doesn't
		// deadlock on semaphores.
		if (s_ppapi.m_forceSwap)
		{
			s_ppapi.swap();
		}

		renderFrame();
	}

	static void GL_APIENTRY naclVertexAttribDivisor(GLuint _index, GLuint _divisor)
	{
		s_ppapi.m_instancedArrays->VertexAttribDivisorANGLE(s_ppapi.m_context, _index, _divisor);
	}

	static void GL_APIENTRY naclDrawArraysInstanced(GLenum _mode, GLint _first, GLsizei _count, GLsizei _primcount)
	{
		s_ppapi.m_instancedArrays->DrawArraysInstancedANGLE(s_ppapi.m_context, _mode, _first, _count, _primcount);
	}

	static void GL_APIENTRY naclDrawElementsInstanced(GLenum _mode, GLsizei _count, GLenum _type, const GLvoid* _indices, GLsizei _primcount)
	{
		s_ppapi.m_instancedArrays->DrawElementsInstancedANGLE(s_ppapi.m_context, _mode, _count, _type, _indices, _primcount);
	}

	bool Ppapi::setInterfaces(PP_Instance _instance, const PPB_Instance* _instInterface, const PPB_Graphics3D* _graphicsInterface, PostSwapBuffersFn _postSwapBuffers)
	{
		BX_TRACE("PPAPI Interfaces");

		m_instance = _instance;
		m_instInterface = _instInterface;
		m_graphicsInterface = _graphicsInterface;
		m_instancedArrays = glGetInstancedArraysInterfacePPAPI();
		m_postSwapBuffers = _postSwapBuffers;

		int32_t attribs[] =
		{
			PP_GRAPHICS3DATTRIB_ALPHA_SIZE, 8,
			PP_GRAPHICS3DATTRIB_DEPTH_SIZE, 24,
			PP_GRAPHICS3DATTRIB_STENCIL_SIZE, 8,
			PP_GRAPHICS3DATTRIB_SAMPLES, 0,
			PP_GRAPHICS3DATTRIB_SAMPLE_BUFFERS, 0,
			PP_GRAPHICS3DATTRIB_WIDTH, BGFX_DEFAULT_WIDTH,
			PP_GRAPHICS3DATTRIB_HEIGHT, BGFX_DEFAULT_HEIGHT,
			PP_GRAPHICS3DATTRIB_NONE
		};

		m_context = m_graphicsInterface->Create(m_instance, 0, attribs);
		if (0 == m_context)
		{
			BX_TRACE("Failed to create context!");
			return false;
		}

		m_instInterface->BindGraphics(m_instance, m_context);
		glSetCurrentContextPPAPI(m_context);
		m_graphicsInterface->SwapBuffers(m_context, naclSwapComplete);

		glVertexAttribDivisor   = naclVertexAttribDivisor;
		glDrawArraysInstanced   = naclDrawArraysInstanced;
		glDrawElementsInstanced = naclDrawElementsInstanced;

		// Prevent render thread creation.
		RenderFrame::Enum result = renderFrame();
		return RenderFrame::NoContext == result;
	}

	void GlContext::create(uint32_t _width, uint32_t _height)
	{
		BX_UNUSED(_width, _height);
		BX_TRACE("GlContext::create");
	}

	void GlContext::destroy()
	{
	}

	void GlContext::resize(uint32_t _width, uint32_t _height, uint32_t _flags)
	{
		s_ppapi.m_forceSwap = false;
		s_ppapi.resize(_width, _height, _flags);
	}

	uint64_t GlContext::getCaps() const
	{
		return 0;
	}

	SwapChainGL* GlContext::createSwapChain(void* /*_nwh*/)
	{
		BX_CHECK(false, "Shouldn't be called!");
		return NULL;
	}

	void GlContext::destroySwapChain(SwapChainGL*  /*_swapChain*/)
	{
		BX_CHECK(false, "Shouldn't be called!");
	}

	void GlContext::swap(SwapChainGL* /*_swapChain*/)
	{
		s_ppapi.swap();
	}

	void GlContext::makeCurrent(SwapChainGL* /*_swapChain*/)
	{
	}

	void GlContext::import()
	{
	}

	bool GlContext::isValid() const
	{
		return s_ppapi.isValid();
	}

} /* namespace gl */ } // namespace bgfx

namespace bgfx
{
	bool naclSetInterfaces(PP_Instance _instance, const PPB_Instance* _instInterface, const PPB_Graphics3D* _graphicsInterface, PostSwapBuffersFn _postSwapBuffers)
	{
		return gl::s_ppapi.setInterfaces( _instance, _instInterface, _graphicsInterface, _postSwapBuffers);
	}
} // namespace bgfx

#endif // BX_PLATFORM_NACL && (BGFX_CONFIG_RENDERER_OPENGLES || BGFX_CONFIG_RENDERER_OPENGL)
