/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef __GLCONTEXT_NSGL_H__
#define __GLCONTEXT_NSGL_H__

#if BX_PLATFORM_OSX

namespace bgfx
{
	struct GlContext
	{
		GlContext()
        : m_context(0)
		{
		}
        
		void create(uint32_t _width, uint32_t _height);
		void destroy();
		void resize(uint32_t _width, uint32_t _height);
		void swap();
		void import();
        
		bool isValid() const
		{
			return 0 != m_context;
		}
        
		void* m_view;
		void* m_context;
	};
} // namespace bgfx

#endif // BX_PLATFORM_OSX

#endif // __GLCONTEXT_NSGL_H__
