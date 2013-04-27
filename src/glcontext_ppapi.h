/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef __GLCONTEXT_PPAPI_H__
#define __GLCONTEXT_PPAPI_H__

#if BX_PLATFORM_NACL

#	include <ppapi/gles2/gl2ext_ppapi.h>
#	include <ppapi/c/pp_completion_callback.h>
#	include <ppapi/c/ppb_instance.h>
#	include <ppapi/c/ppb_graphics_3d.h>

namespace bgfx
{
	struct GlContext
	{
		GlContext()
			: m_context(0)
			, m_instance(0)
			, m_instInterface(NULL)
			, m_graphicsInterface(NULL)
			, m_instancedArrays(NULL)
		{
		}

		void create(uint32_t _width, uint32_t _height);
		void destroy();
		void resize(uint32_t _width, uint32_t _height, bool _vsync);
		void swap();
		void import();

		bool isValid() const
		{
			return 0 != m_context;
		}

		PP_Resource m_context;
		PP_Instance m_instance;
		const PPB_Instance* m_instInterface;
		const PPB_Graphics3D* m_graphicsInterface;
		const PPB_OpenGLES2InstancedArrays* m_instancedArrays;
	};
} // namespace bgfx

#endif // BX_PLATFORM_NACL

#endif // __GLCONTEXT_PPAPI_H__
