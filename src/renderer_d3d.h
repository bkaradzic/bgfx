/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_RENDERER_D3D_H_HEADER_GUARD
#define BGFX_RENDERER_D3D_H_HEADER_GUARD

#if 0 // BGFX_CONFIG_DEBUG && BGFX_CONFIG_RENDERER_DIRECT3D9 && !(BX_COMPILER_GCC || BX_COMPILER_CLANG)
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

#ifndef D3DCOLOR_ARGB
#	define D3DCOLOR_ARGB(_a, _r, _g, _b) ( (DWORD)( ( ( (_a)&0xff)<<24)|( ( (_r)&0xff)<<16)|( ( (_g)&0xff)<<8)|( (_b)&0xff) ) )
#endif // D3DCOLOR_ARGB

#ifndef D3DCOLOR_RGBA
#	define D3DCOLOR_RGBA(_r, _g, _b, _a) D3DCOLOR_ARGB(_a, _r, _g, _b)
#endif // D3DCOLOR_RGBA

namespace bgfx
{
#if BX_PLATFORM_XBOXONE
	typedef ::IGraphicsUnknown IUnknown;
#else
	typedef ::IUnknown IUnknown;
#endif // BX_PLATFORM_XBOXONE

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
				if (NULL != (_ptr) ) \
				{ \
					ULONG count = (_ptr)->Release(); \
					_check(isGraphicsDebuggerPresent() || _expected == count, "%p RefCount is %d (expected %d).", _ptr, count, _expected); BX_UNUSED(count); \
					_ptr = NULL; \
				} \
			BX_MACRO_BLOCK_END

#define _DX_CHECK_REFCOUNT(_ptr, _expected) \
			BX_MACRO_BLOCK_BEGIN \
				ULONG count = getRefCount(_ptr); \
				BX_CHECK(isGraphicsDebuggerPresent() || _expected == count, "%p RefCount is %d (expected %d).", _ptr, count, _expected); \
			BX_MACRO_BLOCK_END

#define _DX_NAME(_ptr, _format, ...) setDebugObjectName(_ptr, _format, ##__VA_ARGS__)

#if BGFX_CONFIG_DEBUG
#	define DX_CHECK(_call) _DX_CHECK(_call)
#	define DX_CHECK_REFCOUNT(_ptr, _expected) _DX_CHECK_REFCOUNT(_ptr, _expected)
#else
#	define DX_CHECK(_call) _call
#	define DX_CHECK_REFCOUNT(_ptr, _expected)
#endif // BGFX_CONFIG_DEBUG

#if BGFX_CONFIG_DEBUG_OBJECT_NAME
#	define DX_NAME(_ptr, _format, ...) _DX_NAME(_ptr, _format, ##__VA_ARGS__)
#else
#	define DX_NAME(_ptr, _format, ...)
#endif // BGFX_CONFIG_DEBUG_OBJECT_NAME

#define DX_RELEASE(_ptr, _expected) _DX_RELEASE(_ptr, _expected, BX_CHECK)
#define DX_RELEASE_WARNONLY(_ptr, _expected) _DX_RELEASE(_ptr, _expected, BX_WARN)

	typedef int     (WINAPI* PFN_D3DPERF_BEGIN_EVENT)(DWORD _color, LPCWSTR _name);
	typedef int     (WINAPI* PFN_D3DPERF_END_EVENT)();
	typedef void    (WINAPI* PFN_D3DPERF_SET_MARKER)(DWORD _color, LPCWSTR _name);
	typedef void    (WINAPI* PFN_D3DPERF_SET_REGION)(DWORD _color, LPCWSTR _name);
	typedef BOOL    (WINAPI* PFN_D3DPERF_QUERY_REPEAT_FRAME)();
	typedef void    (WINAPI* PFN_D3DPERF_SET_OPTIONS)(DWORD _options);
	typedef DWORD   (WINAPI* PFN_D3DPERF_GET_STATUS)();
	typedef HRESULT (WINAPI* PFN_CREATE_DXGI_FACTORY)(REFIID _riid, void** _factory);
	typedef HRESULT (WINAPI* PFN_GET_DEBUG_INTERFACE)(REFIID _riid, void** _debug);
	typedef HRESULT (WINAPI* PFN_GET_DEBUG_INTERFACE1)(UINT _flags, REFIID _riid, void** _debug);

#define _PIX_SETMARKER(_col, _name)  D3DPERF_SetMarker(_col, _name)
#define _PIX_BEGINEVENT(_col, _name) D3DPERF_BeginEvent(_col, _name)
#define _PIX_ENDEVENT()              D3DPERF_EndEvent()

#if BGFX_CONFIG_DEBUG_PIX
#	define PIX_SETMARKER(_color, _name)  _PIX_SETMARKER(_color, _name)
#	define PIX_BEGINEVENT(_color, _name) _PIX_BEGINEVENT(_color, _name)
#	define PIX_ENDEVENT()                _PIX_ENDEVENT()
#else
#	define PIX_SETMARKER(_color, _name)  BX_UNUSED(_name)
#	define PIX_BEGINEVENT(_color, _name) BX_UNUSED(_name)
#	define PIX_ENDEVENT()
#endif // BGFX_CONFIG_DEBUG_PIX

#define D3DCOLOR_FRAME   D3DCOLOR_RGBA(0xff, 0xd7, 0xc9, 0xff)
#define D3DCOLOR_VIEW    D3DCOLOR_RGBA(0xe4, 0xb4, 0x8e, 0xff)
#define D3DCOLOR_VIEW_L  D3DCOLOR_RGBA(0xf9, 0xee, 0xe5, 0xff)
#define D3DCOLOR_VIEW_R  D3DCOLOR_RGBA(0xe8, 0xd3, 0xc0, 0xff)
#define D3DCOLOR_DRAW    D3DCOLOR_RGBA(0xc6, 0xe5, 0xb9, 0xff)
#define D3DCOLOR_COMPUTE D3DCOLOR_RGBA(0xa7, 0xdb, 0xd8, 0xff)
#define D3DCOLOR_MARKER  D3DCOLOR_RGBA(0xff, 0x00, 0x00, 0xff)

	inline int getRefCount(IUnknown* _interface)
	{
		_interface->AddRef();
		return _interface->Release();
	}

	template<typename Ty>
	class StateCacheT
	{
	public:
		void add(uint64_t _key, Ty* _value)
		{
			invalidate(_key);
			m_hashMap.insert(stl::make_pair(_key, _value) );
			BX_CHECK(isGraphicsDebuggerPresent()
				|| 1 == getRefCount(_value), "Interface ref count %d, hash %" PRIx64 "."
				, getRefCount(_value)
				, _key
				);
		}

		Ty* find(uint64_t _key)
		{
			typename HashMap::iterator it = m_hashMap.find(_key);
			if (it != m_hashMap.end() )
			{
				return it->second;
			}

			return NULL;
		}

		void invalidate(uint64_t _key)
		{
			typename HashMap::iterator it = m_hashMap.find(_key);
			if (it != m_hashMap.end() )
			{
				DX_RELEASE_WARNONLY(it->second, 0);
				m_hashMap.erase(it);
			}
		}

		void invalidate()
		{
			for (typename HashMap::iterator it = m_hashMap.begin(), itEnd = m_hashMap.end(); it != itEnd; ++it)
			{
				DX_CHECK_REFCOUNT(it->second, 1);
				it->second->Release();
			}

			m_hashMap.clear();
		}

		uint32_t getCount() const
		{
			return uint32_t(m_hashMap.size() );
		}

	private:
		typedef stl::unordered_map<uint64_t, Ty*> HashMap;
		HashMap m_hashMap;
	};

	template<>
	inline void release<IUnknown*>(IUnknown* _ptr)
	{
		DX_RELEASE(_ptr, 0);
	}

} // namespace bgfx

#endif // BGFX_RENDERER_D3D_H_HEADER_GUARD
