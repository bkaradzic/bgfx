/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
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

	typedef int     (WINAPI* PFN_D3DPERF_BEGIN_EVENT)(DWORD _color, LPCWSTR _wszName);
	typedef int     (WINAPI* PFN_D3DPERF_END_EVENT)();
	typedef void    (WINAPI* PFN_D3DPERF_SET_MARKER)(DWORD _color, LPCWSTR _wszName);
	typedef void    (WINAPI* PFN_D3DPERF_SET_REGION)(DWORD _color, LPCWSTR _wszName);
	typedef BOOL    (WINAPI* PFN_D3DPERF_QUERY_REPEAT_FRAME)();
	typedef void    (WINAPI* PFN_D3DPERF_SET_OPTIONS)(DWORD _options);
	typedef DWORD   (WINAPI* PFN_D3DPERF_GET_STATUS)();
	typedef HRESULT (WINAPI* PFN_CREATE_DXGI_FACTORY)(REFIID _riid, void** _factory);

#define _PIX_SETMARKER(_col, _name) D3DPERF_SetMarker(_col, _name)
#define _PIX_BEGINEVENT(_col, _name) D3DPERF_BeginEvent(_col, _name)
#define _PIX_ENDEVENT() D3DPERF_EndEvent()

#if BGFX_CONFIG_DEBUG_PIX
#	define PIX_SETMARKER(_color, _name)  _PIX_SETMARKER(_color, _name)
#	define PIX_BEGINEVENT(_color, _name) _PIX_BEGINEVENT(_color, _name)
#	define PIX_ENDEVENT() _PIX_ENDEVENT()
#else
#	define PIX_SETMARKER(_color, _name)  BX_UNUSED(_name)
#	define PIX_BEGINEVENT(_color, _name) BX_UNUSED(_name)
#	define PIX_ENDEVENT()
#endif // BGFX_CONFIG_DEBUG_PIX

	inline int getRefCount(IUnknown* _interface)
	{
		_interface->AddRef();
		return _interface->Release();
	}

	template <typename Ty>
	class StateCacheT
	{
	public:
		void add(uint64_t _id, Ty* _item)
		{
			invalidate(_id);
			m_hashMap.insert(stl::make_pair(_id, _item) );
		}

		Ty* find(uint64_t _id)
		{
			typename HashMap::iterator it = m_hashMap.find(_id);
			if (it != m_hashMap.end() )
			{
				return it->second;
			}

			return NULL;
		}

		void invalidate(uint64_t _id)
		{
			typename HashMap::iterator it = m_hashMap.find(_id);
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

	class StateCache
	{
	public:
		void add(uint64_t _id, uint16_t _item)
		{
			invalidate(_id);
			m_hashMap.insert(stl::make_pair(_id, _item));
		}

		uint16_t find(uint64_t _id)
		{
			HashMap::iterator it = m_hashMap.find(_id);
			if (it != m_hashMap.end())
			{
				return it->second;
			}

			return UINT16_MAX;
		}

		void invalidate(uint64_t _id)
		{
			HashMap::iterator it = m_hashMap.find(_id);
			if (it != m_hashMap.end())
			{
				m_hashMap.erase(it);
			}
		}

		void invalidate()
		{
			m_hashMap.clear();
		}

		uint32_t getCount() const
		{
			return uint32_t(m_hashMap.size());
		}

	private:
		typedef stl::unordered_map<uint64_t, uint16_t> HashMap;
		HashMap m_hashMap;
	};

} // namespace bgfx

#endif // BGFX_RENDERER_D3D_H_HEADER_GUARD
