/*
 * Copyright 2011-2014 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef BGFX_RENDERER_D3D_H_HEADER_GUARD
#define BGFX_RENDERER_D3D_H_HEADER_GUARD

#if BGFX_CONFIG_DEBUG && BGFX_CONFIG_RENDERER_DIRECT3D9 && !(BX_COMPILER_GCC || BX_COMPILER_CLANG)
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
			BX_MACRO_BLOCK_BEGIN \
				HRESULT __hr__ = _call; \
				BX_CHECK(SUCCEEDED(__hr__), #_call " FAILED 0x%08x" DX_CHECK_EXTRA_F "\n" \
					, (uint32_t)__hr__ \
					DX_CHECK_EXTRA_ARGS \
					); \
			BX_MACRO_BLOCK_END

#define _DX_RELEASE(_ptr, _expected, _check) \
			BX_MACRO_BLOCK_BEGIN \
				if (NULL != _ptr) \
				{ \
					ULONG count = _ptr->Release(); \
					_check(isGraphicsDebuggerPresent() || _expected == count, "%p RefCount is %d (expected %d).", _ptr, count, _expected); BX_UNUSED(count); \
					_ptr = NULL; \
				} \
			BX_MACRO_BLOCK_END

#	define _DX_CHECK_REFCOUNT(_ptr, _expected) \
			BX_MACRO_BLOCK_BEGIN \
				ULONG count = getRefCount(_ptr); \
				BX_CHECK(isGraphicsDebuggerPresent() || _expected == count, "%p RefCount is %d (expected %d).", _ptr, count, _expected); \
			BX_MACRO_BLOCK_END

#if BGFX_CONFIG_DEBUG
#	define DX_CHECK(_call) _DX_CHECK(_call)
#	define DX_CHECK_REFCOUNT(_ptr, _expected) _DX_CHECK_REFCOUNT(_ptr, _expected)
#else
#	define DX_CHECK(_call) _call
#	define DX_CHECK_REFCOUNT(_ptr, _expected)
#endif // BGFX_CONFIG_DEBUG

#define DX_RELEASE(_ptr, _expected) _DX_RELEASE(_ptr, _expected, BX_CHECK)
#define DX_RELEASE_WARNONLY(_ptr, _expected) _DX_RELEASE(_ptr, _expected, BX_WARN)

	typedef int (WINAPI *D3DPERF_BeginEventFunc)(DWORD _color, LPCWSTR _wszName);
	typedef int (WINAPI *D3DPERF_EndEventFunc)();
	typedef void (WINAPI *D3DPERF_SetMarkerFunc)(DWORD _color, LPCWSTR _wszName);
	typedef void (WINAPI *D3DPERF_SetRegionFunc)(DWORD _color, LPCWSTR _wszName);
	typedef BOOL (WINAPI *D3DPERF_QueryRepeatFrameFunc)();
	typedef void (WINAPI *D3DPERF_SetOptionsFunc)(DWORD _options);
	typedef DWORD (WINAPI *D3DPERF_GetStatusFunc)();

#define _PIX_SETMARKER(_col, _name) m_D3DPERF_SetMarker(_col, _name)
#define _PIX_BEGINEVENT(_col, _name) m_D3DPERF_BeginEvent(_col, _name)
#define _PIX_ENDEVENT() m_D3DPERF_EndEvent()

#if BGFX_CONFIG_DEBUG_PIX
#	define PIX_SETMARKER(_color, _name) _PIX_SETMARKER(_color, _name)
#	define PIX_BEGINEVENT(_color, _name) _PIX_BEGINEVENT(_color, _name)
#	define PIX_ENDEVENT() _PIX_ENDEVENT()
#else
#	define PIX_SETMARKER(_color, _name)
#	define PIX_BEGINEVENT(_color, _name)
#	define PIX_ENDEVENT()
#endif // BGFX_CONFIG_DEBUG_PIX

	inline int getRefCount(IUnknown* _interface)
	{
		_interface->AddRef();
		return _interface->Release();
	}

} // namespace bgfx

#endif // BGFX_RENDERER_D3D_H_HEADER_GUARD
