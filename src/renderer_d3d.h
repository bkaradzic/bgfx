/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef __RENDERER_D3D_H__
#define __RENDERER_D3D_H__

#if BGFX_CONFIG_DEBUG && BGFX_CONFIG_RENDERER_DIRECT3D9
#	include <sal.h>
#	include <dxerr.h>
#	if BX_COMPILER_MSVC
#		pragma comment(lib, "dxerr.lib")
#	endif // BX_COMPILER_MSVC
#	define DX_CHECK_EXTRA_F " (%s): %s"
#	define DX_CHECK_EXTRA_ARGS , DXGetErrorString(__hr__), DXGetErrorDescription(__hr__)
#else
#	define DX_CHECK_EXTRA_F ""
#	define DX_CHECK_EXTRA_ARGS
#endif // BGFX_CONFIG_DEBUG && BGFX_CONFIG_RENDERER_DIRECT3D9

namespace bgfx
{
#define _DX_CHECK(_call) \
			do { \
				HRESULT __hr__ = _call; \
				BX_CHECK(SUCCEEDED(__hr__), #_call " FAILED 0x%08x" DX_CHECK_EXTRA_F "\n" \
					, (uint32_t)__hr__ \
					DX_CHECK_EXTRA_ARGS \
					); \
			} while (0)

#if BGFX_CONFIG_DEBUG
#	define DX_CHECK(_call) _DX_CHECK(_call)
#else
#	define DX_CHECK(_call) _call
#endif // BGFX_CONFIG_DEBUG

#if BGFX_CONFIG_DEBUG
#	define DX_CHECK_REFCOUNT(_ptr, _expected) \
			do { \
				ULONG count = getRefCount(_ptr); \
				BX_CHECK(_expected == count, "RefCount is %d (expected %d).", count, _expected); \
			} while (0)

#	define DX_RELEASE(_ptr, _expected) \
			do { \
				if (NULL != _ptr) \
				{ \
					ULONG count = _ptr->Release(); \
					BX_CHECK(_expected == count, "RefCount is %d (expected %d).", count, _expected); \
					_ptr = NULL; \
				} \
			} while (0)
#else
#	define DX_CHECK_REFCOUNT(_ptr, _expected)
#	define DX_RELEASE(_ptr, _expected) \
			do { \
				if (NULL != _ptr) \
				{ \
					_ptr->Release(); \
					_ptr = NULL; \
				} \
			} while (0)
#endif // BGFX_CONFIG_DEBUG

	inline int getRefCount(IUnknown* _interface)
	{
		_interface->AddRef();
		return _interface->Release();
	}

} // namespace bgfx

#endif // __RENDERER_D3D_H__
