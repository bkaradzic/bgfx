/*
 * Copyright 2011-2020 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef BGFX_EMBEDDED_SHADER_H_HEADER_GUARD
#define BGFX_EMBEDDED_SHADER_H_HEADER_GUARD

#include <bx/bx.h>
#include "bgfx.h"

#define BGFX_EMBEDDED_SHADER_DXBC(...)
#define BGFX_EMBEDDED_SHADER_DX9BC(...)
#define BGFX_EMBEDDED_SHADER_PSSL(...)
#define BGFX_EMBEDDED_SHADER_ESSL(...)
#define BGFX_EMBEDDED_SHADER_GLSL(...)
#define BGFX_EMBEDDED_SHADER_METAL(...)
#define BGFX_EMBEDDED_SHADER_NVN(...)
#define BGFX_EMBEDDED_SHADER_SPIRV(...)

#define BGFX_PLATFORM_SUPPORTS_DX9BC (0 \
		|| BX_PLATFORM_WINDOWS          \
		)
#define BGFX_PLATFORM_SUPPORTS_DXBC (0  \
		|| BX_PLATFORM_WINDOWS          \
		|| BX_PLATFORM_WINRT            \
		|| BX_PLATFORM_XBOXONE          \
		)
#define BGFX_PLATFORM_SUPPORTS_PSSL (0  \
		|| BX_PLATFORM_PS4              \
		)
#define BGFX_PLATFORM_SUPPORTS_ESSL (0  \
		|| BX_PLATFORM_ANDROID          \
		|| BX_PLATFORM_EMSCRIPTEN       \
		|| BX_PLATFORM_IOS              \
		|| BX_PLATFORM_LINUX            \
		|| BX_PLATFORM_OSX              \
		|| BX_PLATFORM_RPI              \
		|| BX_PLATFORM_WINDOWS          \
		)
#define BGFX_PLATFORM_SUPPORTS_GLSL (0  \
		|| BX_PLATFORM_BSD              \
		|| BX_PLATFORM_LINUX            \
		|| BX_PLATFORM_OSX              \
		|| BX_PLATFORM_WINDOWS          \
		)
#define BGFX_PLATFORM_SUPPORTS_METAL (0 \
		|| BX_PLATFORM_IOS              \
		|| BX_PLATFORM_OSX              \
		)
#define BGFX_PLATFORM_SUPPORTS_NVN (0   \
		|| BX_PLATFORM_NX               \
		)
#define BGFX_PLATFORM_SUPPORTS_SPIRV (0 \
		|| BX_PLATFORM_ANDROID          \
		|| BX_PLATFORM_EMSCRIPTEN       \
		|| BX_PLATFORM_LINUX            \
		|| BX_PLATFORM_WINDOWS          \
		|| BX_PLATFORM_OSX              \
		)

#if BGFX_PLATFORM_SUPPORTS_DX9BC
#	undef  BGFX_EMBEDDED_SHADER_DX9BC
#	define BGFX_EMBEDDED_SHADER_DX9BC(_renderer, _name) \
		{ _renderer, BX_CONCATENATE(_name, _dx9 ), BX_COUNTOF(BX_CONCATENATE(_name, _dx9 ) ) },
#endif // BGFX_PLATFORM_SUPPORTS_DX9BC

#if BGFX_PLATFORM_SUPPORTS_DXBC
#	undef  BGFX_EMBEDDED_SHADER_DXBC
#	define BGFX_EMBEDDED_SHADER_DXBC(_renderer, _name) \
		{ _renderer, BX_CONCATENATE(_name, _dx11), BX_COUNTOF(BX_CONCATENATE(_name, _dx11) ) },
#endif // BGFX_PLATFORM_SUPPORTS_DXBC

#if BGFX_PLATFORM_SUPPORTS_PSSL
#	undef  BGFX_EMBEDDED_SHADER_PSSL
#	define BGFX_EMBEDDED_SHADER_PSSL(_renderer, _name) \
		{ _renderer, BX_CONCATENATE(_name, _pssl), BX_CONCATENATE(_name, _pssl_size) },
#endif // BGFX_PLATFORM_SUPPORTS_PSSL

#if BGFX_PLATFORM_SUPPORTS_ESSL
#	undef  BGFX_EMBEDDED_SHADER_ESSL
#	define BGFX_EMBEDDED_SHADER_ESSL(_renderer, _name) \
		{ _renderer, BX_CONCATENATE(_name, _glsl), BX_COUNTOF(BX_CONCATENATE(_name, _glsl) ) },
#endif // BGFX_PLATFORM_SUPPORTS_ESSL

#if BGFX_PLATFORM_SUPPORTS_GLSL
#	undef  BGFX_EMBEDDED_SHADER_GLSL
#	define BGFX_EMBEDDED_SHADER_GLSL(_renderer, _name) \
		{ _renderer, BX_CONCATENATE(_name, _glsl), BX_COUNTOF(BX_CONCATENATE(_name, _glsl) ) },
#endif // BGFX_PLATFORM_SUPPORTS_GLSL

#if BGFX_PLATFORM_SUPPORTS_SPIRV
#	undef  BGFX_EMBEDDED_SHADER_SPIRV
#	define BGFX_EMBEDDED_SHADER_SPIRV(_renderer, _name) \
		{ _renderer, BX_CONCATENATE(_name, _spv), BX_COUNTOF(BX_CONCATENATE(_name, _spv) ) },
#endif // BGFX_PLATFORM_SUPPORTS_SPIRV

#if BGFX_PLATFORM_SUPPORTS_METAL
#	undef  BGFX_EMBEDDED_SHADER_METAL
#	define BGFX_EMBEDDED_SHADER_METAL(_renderer, _name) \
		{ _renderer, BX_CONCATENATE(_name, _mtl), BX_COUNTOF(BX_CONCATENATE(_name, _mtl) ) },
#endif // BGFX_PLATFORM_SUPPORTS_METAL

#define BGFX_EMBEDDED_SHADER(_name)                                                                \
			{                                                                                      \
				#_name,                                                                            \
				{                                                                                  \
					BGFX_EMBEDDED_SHADER_DX9BC(bgfx::RendererType::Direct3D9,  _name)              \
					BGFX_EMBEDDED_SHADER_DXBC (bgfx::RendererType::Direct3D11, _name)              \
					BGFX_EMBEDDED_SHADER_DXBC (bgfx::RendererType::Direct3D12, _name)              \
					BGFX_EMBEDDED_SHADER_PSSL (bgfx::RendererType::Gnm,        _name)              \
					BGFX_EMBEDDED_SHADER_METAL(bgfx::RendererType::Metal,      _name)              \
					BGFX_EMBEDDED_SHADER_NVN  (bgfx::RendererType::Nvn,        _name)              \
					BGFX_EMBEDDED_SHADER_ESSL (bgfx::RendererType::OpenGLES,   _name)              \
					BGFX_EMBEDDED_SHADER_GLSL (bgfx::RendererType::OpenGL,     _name)              \
					BGFX_EMBEDDED_SHADER_SPIRV(bgfx::RendererType::Vulkan,     _name)              \
					BGFX_EMBEDDED_SHADER_SPIRV(bgfx::RendererType::WebGPU,     _name)              \
					{ bgfx::RendererType::Noop,  (const uint8_t*)"VSH\x5\x0\x0\x0\x0\x0\x0", 10 }, \
					{ bgfx::RendererType::Count, NULL, 0 }                                         \
				}                                                                                  \
			}

#define BGFX_EMBEDDED_SHADER_END()                         \
			{                                              \
				NULL,                                      \
				{                                          \
					{ bgfx::RendererType::Count, NULL, 0 } \
				}                                          \
			}

namespace bgfx
{
	struct EmbeddedShader
	{
		struct Data
		{
			RendererType::Enum type;
			const uint8_t* data;
			uint32_t size;
		};

		const char* name;
		Data data[RendererType::Count];
	};

	ShaderHandle createEmbeddedShader(const bgfx::EmbeddedShader* _es, RendererType::Enum _type, const char* _name);

} // namespace bgfx

#endif // BGFX_EMBEDDED_SHADER_H_HEADER_GUARD
