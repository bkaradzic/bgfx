/*
 * Copyright 2011-2021 Branimir Karadzic. All rights reserved.
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

#define DXGI_FORMAT_ASTC_4X4_TYPELESS     DXGI_FORMAT(133)
#define DXGI_FORMAT_ASTC_4X4_UNORM        DXGI_FORMAT(134)
#define DXGI_FORMAT_ASTC_4X4_UNORM_SRGB   DXGI_FORMAT(135)
#define DXGI_FORMAT_ASTC_5X4_TYPELESS     DXGI_FORMAT(137)
#define DXGI_FORMAT_ASTC_5X4_UNORM        DXGI_FORMAT(138)
#define DXGI_FORMAT_ASTC_5X4_UNORM_SRGB   DXGI_FORMAT(139)
#define DXGI_FORMAT_ASTC_5X5_TYPELESS     DXGI_FORMAT(141)
#define DXGI_FORMAT_ASTC_5X5_UNORM        DXGI_FORMAT(142)
#define DXGI_FORMAT_ASTC_5X5_UNORM_SRGB   DXGI_FORMAT(143)
#define DXGI_FORMAT_ASTC_6X5_TYPELESS     DXGI_FORMAT(145)
#define DXGI_FORMAT_ASTC_6X5_UNORM        DXGI_FORMAT(146)
#define DXGI_FORMAT_ASTC_6X5_UNORM_SRGB   DXGI_FORMAT(147)
#define DXGI_FORMAT_ASTC_6X6_TYPELESS     DXGI_FORMAT(149)
#define DXGI_FORMAT_ASTC_6X6_UNORM        DXGI_FORMAT(150)
#define DXGI_FORMAT_ASTC_6X6_UNORM_SRGB   DXGI_FORMAT(151)
#define DXGI_FORMAT_ASTC_8X5_TYPELESS     DXGI_FORMAT(153)
#define DXGI_FORMAT_ASTC_8X5_UNORM        DXGI_FORMAT(154)
#define DXGI_FORMAT_ASTC_8X5_UNORM_SRGB   DXGI_FORMAT(155)
#define DXGI_FORMAT_ASTC_8X6_TYPELESS     DXGI_FORMAT(157)
#define DXGI_FORMAT_ASTC_8X6_UNORM        DXGI_FORMAT(158)
#define DXGI_FORMAT_ASTC_8X6_UNORM_SRGB   DXGI_FORMAT(159)
#define DXGI_FORMAT_ASTC_8X8_TYPELESS     DXGI_FORMAT(161)
#define DXGI_FORMAT_ASTC_8X8_UNORM        DXGI_FORMAT(162)
#define DXGI_FORMAT_ASTC_8X8_UNORM_SRGB   DXGI_FORMAT(163)
#define DXGI_FORMAT_ASTC_10X5_TYPELESS    DXGI_FORMAT(165)
#define DXGI_FORMAT_ASTC_10X5_UNORM       DXGI_FORMAT(166)
#define DXGI_FORMAT_ASTC_10X5_UNORM_SRGB  DXGI_FORMAT(167)
#define DXGI_FORMAT_ASTC_10X6_TYPELESS    DXGI_FORMAT(169)
#define DXGI_FORMAT_ASTC_10X6_UNORM       DXGI_FORMAT(170)
#define DXGI_FORMAT_ASTC_10X6_UNORM_SRGB  DXGI_FORMAT(171)
#define DXGI_FORMAT_ASTC_10X8_TYPELESS    DXGI_FORMAT(173)
#define DXGI_FORMAT_ASTC_10X8_UNORM       DXGI_FORMAT(174)
#define DXGI_FORMAT_ASTC_10X8_UNORM_SRGB  DXGI_FORMAT(175)
#define DXGI_FORMAT_ASTC_10X10_TYPELESS   DXGI_FORMAT(177)
#define DXGI_FORMAT_ASTC_10X10_UNORM      DXGI_FORMAT(178)
#define DXGI_FORMAT_ASTC_10X10_UNORM_SRGB DXGI_FORMAT(179)
#define DXGI_FORMAT_ASTC_12X10_TYPELESS   DXGI_FORMAT(181)
#define DXGI_FORMAT_ASTC_12X10_UNORM      DXGI_FORMAT(182)
#define DXGI_FORMAT_ASTC_12X10_UNORM_SRGB DXGI_FORMAT(183)
#define DXGI_FORMAT_ASTC_12X12_TYPELESS   DXGI_FORMAT(185)
#define DXGI_FORMAT_ASTC_12X12_UNORM      DXGI_FORMAT(186)
#define DXGI_FORMAT_ASTC_12X12_UNORM_SRGB DXGI_FORMAT(187)

namespace bgfx
{
#if BX_PLATFORM_LINUX || BX_PLATFORM_WINDOWS || BX_PLATFORM_WINRT
	typedef ::IUnknown IUnknown;
#else
	typedef ::IGraphicsUnknown IUnknown;
#endif // BX_PLATFORM_WINDOWS || BX_PLATFORM_WINRT

#define _DX_CHECK(_call)                                                                   \
			BX_MACRO_BLOCK_BEGIN                                                           \
				HRESULT __hr__ = _call;                                                    \
				BX_ASSERT(SUCCEEDED(__hr__), #_call " FAILED 0x%08x" DX_CHECK_EXTRA_F "\n" \
					, (uint32_t)__hr__                                                     \
					DX_CHECK_EXTRA_ARGS                                                    \
					);                                                                     \
			BX_MACRO_BLOCK_END

#define _DX_RELEASE(_ptr, _expected, _check)                                                                                                                 \
			BX_MACRO_BLOCK_BEGIN                                                                                                                             \
				if (NULL != (_ptr) )                                                                                                                         \
				{                                                                                                                                            \
					ULONG count = (_ptr)->Release();                                                                                                         \
					_check(isGraphicsDebuggerPresent() || _expected == count, "%p RefCount is %d (expected %d).", _ptr, count, _expected); BX_UNUSED(count); \
					_ptr = NULL;                                                                                                                             \
				}                                                                                                                                            \
			BX_MACRO_BLOCK_END

#define _DX_CHECK_REFCOUNT(_ptr, _expected)                                                                                               \
			BX_MACRO_BLOCK_BEGIN                                                                                                          \
				ULONG count = getRefCount(_ptr);                                                                                          \
				BX_ASSERT(isGraphicsDebuggerPresent() || _expected == count, "%p RefCount is %d (expected %d).", _ptr, count, _expected); \
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

#define DX_RELEASE(_ptr, _expected) _DX_RELEASE(_ptr, _expected, BX_ASSERT)
#define DX_RELEASE_W(_ptr, _expected) _DX_RELEASE(_ptr, _expected, BX_WARN)
#define DX_RELEASE_I(_ptr) _DX_RELEASE(_ptr, 0, BX_NOOP)

	typedef int     (WINAPI* PFN_D3DPERF_BEGIN_EVENT)(DWORD _color, LPCWSTR _name);
	typedef int     (WINAPI* PFN_D3DPERF_END_EVENT)();
	typedef void    (WINAPI* PFN_D3DPERF_SET_MARKER)(DWORD _color, LPCWSTR _name);
	typedef void    (WINAPI* PFN_D3DPERF_SET_REGION)(DWORD _color, LPCWSTR _name);
	typedef BOOL    (WINAPI* PFN_D3DPERF_QUERY_REPEAT_FRAME)();
	typedef void    (WINAPI* PFN_D3DPERF_SET_OPTIONS)(DWORD _options);
	typedef DWORD   (WINAPI* PFN_D3DPERF_GET_STATUS)();

#define _PIX_SETMARKER(_color, _name)    D3DPERF_SetMarker(_color, _name)
#define _PIX_BEGINEVENT(_color, _name)   D3DPERF_BeginEvent(_color, _name)
#define _PIX_ENDEVENT()                  D3DPERF_EndEvent()

#if BGFX_CONFIG_DEBUG_ANNOTATION
#	define PIX_SETMARKER(_color, _name)  _PIX_SETMARKER(_color, _name)
#	define PIX_BEGINEVENT(_color, _name) _PIX_BEGINEVENT(_color, _name)
#	define PIX_ENDEVENT()                _PIX_ENDEVENT()
#else
#	define PIX_SETMARKER(_color, _name)  BX_UNUSED(_name)
#	define PIX_BEGINEVENT(_color, _name) BX_UNUSED(_name)
#	define PIX_ENDEVENT()
#endif // BGFX_CONFIG_DEBUG_ANNOTATION

	inline bool isType(IUnknown* _interface, const GUID& _id)
	{
		IUnknown* out;
		HRESULT hr = _interface->QueryInterface(_id, (void**)&out);
		if (FAILED(hr) )
		{
			return false;
		}

		out->Release();
		return true;
	}

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
			BX_ASSERT(isGraphicsDebuggerPresent()
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
				DX_RELEASE_W(it->second, 0);
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
