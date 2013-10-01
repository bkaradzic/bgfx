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
		{
		}

		void create(uint32_t _width, uint32_t _height);
		void destroy();
		void resize(uint32_t _width, uint32_t _height, bool _vsync);
		void swap();
		void import();
		bool isValid() const;
	};
} // namespace bgfx

#endif // BX_PLATFORM_NACL

#endif // __GLCONTEXT_PPAPI_H__
