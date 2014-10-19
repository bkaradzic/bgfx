/*
 * Copyright 2011-2014 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "bgfx_p.h"

#if BGFX_CONFIG_RENDERER_DIRECT3D11
#	include "renderer_d3d11.h"

#	if BGFX_CONFIG_DEBUG_PIX
#		include <psapi.h>
#		include <renderdoc/renderdoc_app.h>
#	endif // BGFX_CONFIG_DEBUG_PIX

namespace bgfx
{
	static wchar_t s_viewNameW[BGFX_CONFIG_MAX_VIEWS][256];

	struct PrimInfo
	{
		D3D11_PRIMITIVE_TOPOLOGY m_type;
		uint32_t m_min;
		uint32_t m_div;
		uint32_t m_sub;
	};

	static const PrimInfo s_primInfo[] =
	{
		{ D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,  3, 3, 0 },
		{ D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP, 3, 1, 2 },
		{ D3D11_PRIMITIVE_TOPOLOGY_LINELIST,      2, 2, 0 },
		{ D3D11_PRIMITIVE_TOPOLOGY_POINTLIST,     1, 1, 0 },
		{ D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED,     0, 0, 0 },
	};

	static const char* s_primName[] =
	{
		"TriList",
		"TriStrip",
		"Line",
		"Point",
	};
	BX_STATIC_ASSERT(BX_COUNTOF(s_primInfo) == BX_COUNTOF(s_primName)+1);

	static const uint32_t s_checkMsaa[] =
	{
		0,
		2,
		4,
		8,
		16,
	};

	static DXGI_SAMPLE_DESC s_msaa[] =
	{
		{  1, 0 },
		{  2, 0 },
		{  4, 0 },
		{  8, 0 },
		{ 16, 0 },
	};

	static const D3D11_BLEND s_blendFactor[][2] =
	{
		{ (D3D11_BLEND)0,               (D3D11_BLEND)0               }, // ignored
		{ D3D11_BLEND_ZERO,             D3D11_BLEND_ZERO             }, // ZERO
		{ D3D11_BLEND_ONE,              D3D11_BLEND_ONE              },	// ONE
		{ D3D11_BLEND_SRC_COLOR,        D3D11_BLEND_SRC_ALPHA        },	// SRC_COLOR
		{ D3D11_BLEND_INV_SRC_COLOR,    D3D11_BLEND_INV_SRC_ALPHA    },	// INV_SRC_COLOR
		{ D3D11_BLEND_SRC_ALPHA,        D3D11_BLEND_SRC_ALPHA        },	// SRC_ALPHA
		{ D3D11_BLEND_INV_SRC_ALPHA,    D3D11_BLEND_INV_SRC_ALPHA    },	// INV_SRC_ALPHA
		{ D3D11_BLEND_DEST_ALPHA,       D3D11_BLEND_DEST_ALPHA       },	// DST_ALPHA
		{ D3D11_BLEND_INV_DEST_ALPHA,   D3D11_BLEND_INV_DEST_ALPHA   },	// INV_DST_ALPHA
		{ D3D11_BLEND_DEST_COLOR,       D3D11_BLEND_DEST_ALPHA       },	// DST_COLOR
		{ D3D11_BLEND_INV_DEST_COLOR,   D3D11_BLEND_INV_DEST_ALPHA   },	// INV_DST_COLOR
		{ D3D11_BLEND_SRC_ALPHA_SAT,    D3D11_BLEND_ONE              },	// SRC_ALPHA_SAT
		{ D3D11_BLEND_BLEND_FACTOR,     D3D11_BLEND_BLEND_FACTOR     },	// FACTOR
		{ D3D11_BLEND_INV_BLEND_FACTOR, D3D11_BLEND_INV_BLEND_FACTOR },	// INV_FACTOR
	};

	static const D3D11_BLEND_OP s_blendEquation[] =
	{
		D3D11_BLEND_OP_ADD,
		D3D11_BLEND_OP_SUBTRACT,
		D3D11_BLEND_OP_REV_SUBTRACT,
		D3D11_BLEND_OP_MIN,
		D3D11_BLEND_OP_MAX,
	};

	static const D3D11_COMPARISON_FUNC s_cmpFunc[] =
	{
		D3D11_COMPARISON_FUNC(0), // ignored
		D3D11_COMPARISON_LESS,
		D3D11_COMPARISON_LESS_EQUAL,
		D3D11_COMPARISON_EQUAL,
		D3D11_COMPARISON_GREATER_EQUAL,
		D3D11_COMPARISON_GREATER,
		D3D11_COMPARISON_NOT_EQUAL,
		D3D11_COMPARISON_NEVER,
		D3D11_COMPARISON_ALWAYS,
	};

	static const D3D11_STENCIL_OP s_stencilOp[] =
	{
		D3D11_STENCIL_OP_ZERO,
		D3D11_STENCIL_OP_KEEP,
		D3D11_STENCIL_OP_REPLACE,
		D3D11_STENCIL_OP_INCR,
		D3D11_STENCIL_OP_INCR_SAT,
		D3D11_STENCIL_OP_DECR,
		D3D11_STENCIL_OP_DECR_SAT,
		D3D11_STENCIL_OP_INVERT,
	};

	static const D3D11_CULL_MODE s_cullMode[] =
	{
		D3D11_CULL_NONE,
		D3D11_CULL_FRONT,
		D3D11_CULL_BACK,
	};

	static const D3D11_TEXTURE_ADDRESS_MODE s_textureAddress[] =
	{
		D3D11_TEXTURE_ADDRESS_WRAP,
		D3D11_TEXTURE_ADDRESS_MIRROR,
		D3D11_TEXTURE_ADDRESS_CLAMP,
	};

	/*
	 * D3D11_FILTER_MIN_MAG_MIP_POINT               = 0x00,
	 * D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR        = 0x01,
	 * D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT  = 0x04,
	 * D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR        = 0x05,
	 * D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT        = 0x10,
	 * D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR = 0x11,
	 * D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT        = 0x14,
	 * D3D11_FILTER_MIN_MAG_MIP_LINEAR              = 0x15,
	 * D3D11_FILTER_ANISOTROPIC                     = 0x55,
	 *
	 * D3D11_COMPARISON_FILTERING_BIT               = 0x80,
	 * D3D11_ANISOTROPIC_FILTERING_BIT              = 0x40,
	 *
	 * According to D3D11_FILTER enum bits for mip, mag and mip are:
	 * 0x10 // MIN_LINEAR
	 * 0x04 // MAG_LINEAR
	 * 0x01 // MIP_LINEAR
	 */

	static const uint32_t s_textureFilter[3][3] =
	{
		{
			0x10, // min linear
			0x00, // min point
			0x55, // anisotopic
		},
		{
			0x04, // mag linear
			0x00, // mag point
			0x55, // anisotopic
		},
		{
			0x01, // mip linear
			0x00, // mip point
			0x55, // anisotopic
		},
	};

	struct TextureFormatInfo
	{
		DXGI_FORMAT m_fmt;
		DXGI_FORMAT m_fmtSrv;
		DXGI_FORMAT m_fmtDsv;
	};

#ifndef DXGI_FORMAT_B4G4R4A4_UNORM
// Win8 only BS
// https://blogs.msdn.com/b/chuckw/archive/2012/11/14/directx-11-1-and-windows-7.aspx?Redirected=true
// http://msdn.microsoft.com/en-us/library/windows/desktop/bb173059%28v=vs.85%29.aspx
#	define DXGI_FORMAT_B4G4R4A4_UNORM DXGI_FORMAT(115)
#endif // DXGI_FORMAT_B4G4R4A4_UNORM

	static const TextureFormatInfo s_textureFormat[] =
	{
		{ DXGI_FORMAT_BC1_UNORM,          DXGI_FORMAT_BC1_UNORM,             DXGI_FORMAT_UNKNOWN           }, // BC1 
		{ DXGI_FORMAT_BC2_UNORM,          DXGI_FORMAT_BC2_UNORM,             DXGI_FORMAT_UNKNOWN           }, // BC2
		{ DXGI_FORMAT_BC3_UNORM,          DXGI_FORMAT_BC3_UNORM,             DXGI_FORMAT_UNKNOWN           }, // BC3
		{ DXGI_FORMAT_BC4_UNORM,          DXGI_FORMAT_BC4_UNORM,             DXGI_FORMAT_UNKNOWN           }, // BC4
		{ DXGI_FORMAT_BC5_UNORM,          DXGI_FORMAT_BC5_UNORM,             DXGI_FORMAT_UNKNOWN           }, // BC5
		{ DXGI_FORMAT_BC6H_SF16,          DXGI_FORMAT_BC6H_SF16,             DXGI_FORMAT_UNKNOWN           }, // BC6H
		{ DXGI_FORMAT_BC7_UNORM,          DXGI_FORMAT_BC7_UNORM,             DXGI_FORMAT_UNKNOWN           }, // BC7
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN           }, // ETC1
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN           }, // ETC2
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN           }, // ETC2A
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN           }, // ETC2A1
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN           }, // PTC12
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN           }, // PTC14
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN           }, // PTC12A
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN           }, // PTC14A
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN           }, // PTC22
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN           }, // PTC24
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN           }, // Unknown
		{ DXGI_FORMAT_R1_UNORM,           DXGI_FORMAT_R1_UNORM,              DXGI_FORMAT_UNKNOWN           }, // R1
		{ DXGI_FORMAT_R8_UNORM,           DXGI_FORMAT_R8_UNORM,              DXGI_FORMAT_UNKNOWN           }, // R8
		{ DXGI_FORMAT_R16_UNORM,          DXGI_FORMAT_R16_UNORM,             DXGI_FORMAT_UNKNOWN           }, // R16
		{ DXGI_FORMAT_R16_FLOAT,          DXGI_FORMAT_R16_FLOAT,             DXGI_FORMAT_UNKNOWN           }, // R16F
		{ DXGI_FORMAT_R32_UINT,           DXGI_FORMAT_R32_UINT,              DXGI_FORMAT_UNKNOWN           }, // R32
		{ DXGI_FORMAT_R32_FLOAT,          DXGI_FORMAT_R32_FLOAT,             DXGI_FORMAT_UNKNOWN           }, // R32F
		{ DXGI_FORMAT_R8G8_UNORM,         DXGI_FORMAT_R8G8_UNORM,            DXGI_FORMAT_UNKNOWN           }, // RG8
		{ DXGI_FORMAT_R16G16_UNORM,       DXGI_FORMAT_R16G16_UNORM,          DXGI_FORMAT_UNKNOWN           }, // RG16
		{ DXGI_FORMAT_R16G16_FLOAT,       DXGI_FORMAT_R16G16_FLOAT,          DXGI_FORMAT_UNKNOWN           }, // RG16F
		{ DXGI_FORMAT_R32G32_UINT,        DXGI_FORMAT_R32G32_UINT,           DXGI_FORMAT_UNKNOWN           }, // RG32
		{ DXGI_FORMAT_R32G32_FLOAT,       DXGI_FORMAT_R32G32_FLOAT,          DXGI_FORMAT_UNKNOWN           }, // RG32F
		{ DXGI_FORMAT_B8G8R8A8_UNORM,     DXGI_FORMAT_B8G8R8A8_UNORM,        DXGI_FORMAT_UNKNOWN           }, // BGRA8
		{ DXGI_FORMAT_R16G16B16A16_UNORM, DXGI_FORMAT_R16G16B16A16_UNORM,    DXGI_FORMAT_UNKNOWN           }, // RGBA16
		{ DXGI_FORMAT_R16G16B16A16_FLOAT, DXGI_FORMAT_R16G16B16A16_FLOAT,    DXGI_FORMAT_UNKNOWN           }, // RGBA16F
		{ DXGI_FORMAT_R32G32B32A32_UINT,  DXGI_FORMAT_R32G32B32A32_UINT,     DXGI_FORMAT_UNKNOWN           }, // RGBA32
		{ DXGI_FORMAT_R32G32B32A32_FLOAT, DXGI_FORMAT_R32G32B32A32_FLOAT,    DXGI_FORMAT_UNKNOWN           }, // RGBA32F
		{ DXGI_FORMAT_B5G6R5_UNORM,       DXGI_FORMAT_B5G6R5_UNORM,          DXGI_FORMAT_UNKNOWN           }, // R5G6B5
		{ DXGI_FORMAT_B4G4R4A4_UNORM,     DXGI_FORMAT_B4G4R4A4_UNORM,        DXGI_FORMAT_UNKNOWN           }, // RGBA4
		{ DXGI_FORMAT_B5G5R5A1_UNORM,     DXGI_FORMAT_B5G5R5A1_UNORM,        DXGI_FORMAT_UNKNOWN           }, // RGB5A1
		{ DXGI_FORMAT_R10G10B10A2_UNORM,  DXGI_FORMAT_R10G10B10A2_UNORM,     DXGI_FORMAT_UNKNOWN           }, // RGB10A2
		{ DXGI_FORMAT_R11G11B10_FLOAT,    DXGI_FORMAT_R11G11B10_FLOAT,       DXGI_FORMAT_UNKNOWN           }, // R11G11B10F
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN           }, // UnknownDepth
		{ DXGI_FORMAT_R16_TYPELESS,       DXGI_FORMAT_R16_UNORM,             DXGI_FORMAT_D16_UNORM         }, // D16
		{ DXGI_FORMAT_R24G8_TYPELESS,     DXGI_FORMAT_R24_UNORM_X8_TYPELESS, DXGI_FORMAT_D24_UNORM_S8_UINT }, // D24
		{ DXGI_FORMAT_R24G8_TYPELESS,     DXGI_FORMAT_R24_UNORM_X8_TYPELESS, DXGI_FORMAT_D24_UNORM_S8_UINT }, // D24S8
		{ DXGI_FORMAT_R24G8_TYPELESS,     DXGI_FORMAT_R24_UNORM_X8_TYPELESS, DXGI_FORMAT_D24_UNORM_S8_UINT }, // D32
		{ DXGI_FORMAT_R32_TYPELESS,       DXGI_FORMAT_R32_FLOAT,             DXGI_FORMAT_D32_FLOAT         }, // D16F
		{ DXGI_FORMAT_R32_TYPELESS,       DXGI_FORMAT_R32_FLOAT,             DXGI_FORMAT_D32_FLOAT         }, // D24F
		{ DXGI_FORMAT_R32_TYPELESS,       DXGI_FORMAT_R32_FLOAT,             DXGI_FORMAT_D32_FLOAT         }, // D32F
		{ DXGI_FORMAT_R24G8_TYPELESS,     DXGI_FORMAT_R24_UNORM_X8_TYPELESS, DXGI_FORMAT_D24_UNORM_S8_UINT }, // D0S8
	};
	BX_STATIC_ASSERT(TextureFormat::Count == BX_COUNTOF(s_textureFormat) );

	static const D3D11_INPUT_ELEMENT_DESC s_attrib[] =
	{
		{ "POSITION",     0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",       0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TANGENT",      0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BITANGENT",    0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",        0, DXGI_FORMAT_R8G8B8A8_UINT,   0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",        1, DXGI_FORMAT_R8G8B8A8_UINT,   0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BLENDINDICES", 0, DXGI_FORMAT_R8G8B8A8_UINT,   0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BLENDWEIGHT",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",     0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",     1, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",     2, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",     3, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",     4, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",     5, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",     6, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",     7, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	BX_STATIC_ASSERT(Attrib::Count == BX_COUNTOF(s_attrib) );

	static const DXGI_FORMAT s_attribType[][4][2] =
	{
		{
			{ DXGI_FORMAT_R8_UINT,            DXGI_FORMAT_R8_UNORM           },
			{ DXGI_FORMAT_R8G8_UINT,          DXGI_FORMAT_R8G8_UNORM         },
			{ DXGI_FORMAT_R8G8B8A8_UINT,      DXGI_FORMAT_R8G8B8A8_UNORM     },
			{ DXGI_FORMAT_R8G8B8A8_UINT,      DXGI_FORMAT_R8G8B8A8_UNORM     },
		},
		{
			{ DXGI_FORMAT_R16_SINT,           DXGI_FORMAT_R16_SNORM          },
			{ DXGI_FORMAT_R16G16_SINT,        DXGI_FORMAT_R16G16_SNORM       },
			{ DXGI_FORMAT_R16G16B16A16_SINT,  DXGI_FORMAT_R16G16B16A16_SNORM },
			{ DXGI_FORMAT_R16G16B16A16_SINT,  DXGI_FORMAT_R16G16B16A16_SNORM },
		},
		{
			{ DXGI_FORMAT_R16_FLOAT,          DXGI_FORMAT_R16_FLOAT          },
			{ DXGI_FORMAT_R16G16_FLOAT,       DXGI_FORMAT_R16G16_FLOAT       },
			{ DXGI_FORMAT_R16G16B16A16_FLOAT, DXGI_FORMAT_R16G16B16A16_FLOAT },
			{ DXGI_FORMAT_R16G16B16A16_FLOAT, DXGI_FORMAT_R16G16B16A16_FLOAT },
		},
		{
			{ DXGI_FORMAT_R32_FLOAT,          DXGI_FORMAT_R32_FLOAT          },
			{ DXGI_FORMAT_R32G32_FLOAT,       DXGI_FORMAT_R32G32_FLOAT       },
			{ DXGI_FORMAT_R32G32B32_FLOAT,    DXGI_FORMAT_R32G32B32_FLOAT    },
			{ DXGI_FORMAT_R32G32B32A32_FLOAT, DXGI_FORMAT_R32G32B32A32_FLOAT },
		},
	};
	BX_STATIC_ASSERT(AttribType::Count == BX_COUNTOF(s_attribType) );

	static D3D11_INPUT_ELEMENT_DESC* fillVertexDecl(D3D11_INPUT_ELEMENT_DESC* _out, const VertexDecl& _decl)
	{
		D3D11_INPUT_ELEMENT_DESC* elem = _out;

		for (uint32_t attr = 0; attr < Attrib::Count; ++attr)
		{
			if (0xff != _decl.m_attributes[attr])
			{
				memcpy(elem, &s_attrib[attr], sizeof(D3D11_INPUT_ELEMENT_DESC) );

				if (0 == _decl.m_attributes[attr])
				{
					elem->AlignedByteOffset = 0;
				}
				else
				{
					uint8_t num;
					AttribType::Enum type;
					bool normalized;
					bool asInt;
					_decl.decode(Attrib::Enum(attr), num, type, normalized, asInt);
					elem->Format = s_attribType[type][num-1][normalized];
					elem->AlignedByteOffset = _decl.m_offset[attr];
				}

				++elem;
			}
		}

		return elem;
	}

	struct TextureStage
	{
		TextureStage()
		{
			clear();
		}

		void clear()
		{
			memset(m_srv, 0, sizeof(m_srv) );
			memset(m_sampler, 0, sizeof(m_sampler) );
		}

		ID3D11ShaderResourceView* m_srv[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
		ID3D11SamplerState* m_sampler[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
	};

	BX_PRAGMA_DIAGNOSTIC_PUSH();
	BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG("-Wunused-const-variable");
	BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG("-Wunneeded-internal-declaration");

	static const GUID WKPDID_D3DDebugObjectName = { 0x429b8c22, 0x9188, 0x4b0c, { 0x87, 0x42, 0xac, 0xb0, 0xbf, 0x85, 0xc2, 0x00 } };

	template <typename Ty>
	static BX_NO_INLINE void setDebugObjectName(Ty* _interface, const char* _format, ...)
	{
		if (BX_ENABLED(BGFX_CONFIG_DEBUG_OBJECT_NAME) )
		{
			char temp[2048];
			va_list argList;
			va_start(argList, _format);
			int size = bx::uint32_min(sizeof(temp)-1, vsnprintf(temp, sizeof(temp), _format, argList) );
			va_end(argList);
			temp[size] = '\0';

			_interface->SetPrivateData(WKPDID_D3DDebugObjectName, size, temp);
		}
	}

	BX_PRAGMA_DIAGNOSTIC_POP();

	static BX_NO_INLINE bool getIntelExtensions(ID3D11Device* _device)
	{
		uint8_t temp[28];

		D3D11_BUFFER_DESC desc;
		desc.ByteWidth = sizeof(temp);
		desc.Usage = D3D11_USAGE_STAGING;
		desc.BindFlags = 0;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = &temp;
		initData.SysMemPitch = sizeof(temp);
		initData.SysMemSlicePitch = 0;

		bx::StaticMemoryBlockWriter writer(&temp, sizeof(temp) );
		bx::write(&writer, "INTCEXTNCAPSFUNC", 16);
		bx::write(&writer, UINT32_C(0x00010000) );
		bx::write(&writer, UINT32_C(0) );
		bx::write(&writer, UINT32_C(0) );

		ID3D11Buffer* buffer;
		HRESULT hr = _device->CreateBuffer(&desc, &initData, &buffer);

		if (SUCCEEDED(hr) )
		{
			buffer->Release();

			bx::MemoryReader reader(&temp, sizeof(temp) );
			bx::skip(&reader, 16);

			uint32_t version;
			bx::read(&reader, version);

			uint32_t driverVersion;
			bx::read(&reader, driverVersion);

			return version <= driverVersion;
		}

		return false;
	};

#if BGFX_CONFIG_DEBUG_PIX && BX_PLATFORM_WINDOWS
	bool findModule(const char* _name)
	{
		HANDLE process = GetCurrentProcess();
		DWORD size;
		BOOL result = EnumProcessModules(process
						, NULL
						, 0
						, &size
						);
		if (0 != result)
		{
			HMODULE* modules = (HMODULE*)alloca(size);
			result = EnumProcessModules(process
				, modules
				, size
				, &size
				);

			if (0 != result)
			{
				char moduleName[MAX_PATH];
				for (uint32_t ii = 0, num = uint32_t(size/sizeof(HMODULE) ); ii < num; ++ii)
				{
					result = GetModuleBaseNameA(process
								, modules[ii]
								, moduleName
								, BX_COUNTOF(moduleName)
								);
					if (0 != result
					&&  0 == bx::stricmp(_name, moduleName) )
					{
						return true;
					}
				}
			}
		}

		return false;
	}

#define RENDERDOC_IMPORT \
			RENDERDOC_IMPORT_FUNC(RENDERDOC_SetLogFile); \
			RENDERDOC_IMPORT_FUNC(RENDERDOC_GetCapture); \
			RENDERDOC_IMPORT_FUNC(RENDERDOC_SetCaptureOptions); \
			RENDERDOC_IMPORT_FUNC(RENDERDOC_SetActiveWindow); \
			RENDERDOC_IMPORT_FUNC(RENDERDOC_TriggerCapture); \
			RENDERDOC_IMPORT_FUNC(RENDERDOC_StartFrameCapture); \
			RENDERDOC_IMPORT_FUNC(RENDERDOC_EndFrameCapture); \
			RENDERDOC_IMPORT_FUNC(RENDERDOC_GetOverlayBits); \
			RENDERDOC_IMPORT_FUNC(RENDERDOC_MaskOverlayBits); \
			RENDERDOC_IMPORT_FUNC(RENDERDOC_SetFocusToggleKeys); \
			RENDERDOC_IMPORT_FUNC(RENDERDOC_SetCaptureKeys); \
			RENDERDOC_IMPORT_FUNC(RENDERDOC_InitRemoteAccess);

#define RENDERDOC_IMPORT_FUNC(_func) p##_func _func
	RENDERDOC_IMPORT
#undef RENDERDOC_IMPORT_FUNC

	pRENDERDOC_GetAPIVersion RENDERDOC_GetAPIVersion;

	void* loadRenderDoc()
	{
		// Skip loading RenderDoc when IntelGPA is present to avoid RenderDoc crash.
		if (findModule(BX_ARCH_32BIT ? "shimloader32.dll" : "shimloader64.dll") )
		{
			return NULL;
		}

		void* renderdocdll = bx::dlopen("renderdoc.dll");

		if (NULL != renderdocdll)
		{
			RENDERDOC_GetAPIVersion = (pRENDERDOC_GetAPIVersion)bx::dlsym(renderdocdll, "RENDERDOC_GetAPIVersion");
			if (NULL != RENDERDOC_GetAPIVersion
			&&  RENDERDOC_API_VERSION == RENDERDOC_GetAPIVersion() )
			{
#define RENDERDOC_IMPORT_FUNC(_func) \
			_func = (p##_func)bx::dlsym(renderdocdll, #_func); \
			BX_TRACE("%p " #_func, _func);
RENDERDOC_IMPORT
#undef RENDERDOC_IMPORT_FUNC

				RENDERDOC_SetLogFile(L"temp/bgfx");

				RENDERDOC_SetFocusToggleKeys(NULL, 0);

				KeyButton captureKey = eKey_F11;
				RENDERDOC_SetCaptureKeys(&captureKey, 1);

				CaptureOptions opt;
				memset(&opt, 0, sizeof(opt) );
				opt.AllowVSync      = 1;
				opt.SaveAllInitials = 1;
				RENDERDOC_SetCaptureOptions(&opt);

				uint32_t ident = 0;
				RENDERDOC_InitRemoteAccess(&ident);

				RENDERDOC_MaskOverlayBits(eOverlay_None, eOverlay_None);
			}
			else
			{
				bx::dlclose(renderdocdll);
				renderdocdll = NULL;
			}
		}

		return renderdocdll;
	}

	void unloadRenderDoc(void* _renderdocdll)
	{
		if (NULL != _renderdocdll)
		{
			bx::dlclose(_renderdocdll);
		}
	}
#else
	void* loadRenderDoc()
	{
		return NULL;
	}

	void unloadRenderDoc(void*)
	{
	}
#endif // BGFX_CONFIG_DEBUG_PIX

#if USE_D3D11_DYNAMIC_LIB
	static PFN_D3D11_CREATE_DEVICE D3D11CreateDevice;
	static PFN_CREATE_DXGI_FACTORY CreateDXGIFactory;
	static PFN_D3DPERF_SET_MARKER  D3DPERF_SetMarker;
	static PFN_D3DPERF_BEGIN_EVENT D3DPERF_BeginEvent;
	static PFN_D3DPERF_END_EVENT   D3DPERF_EndEvent;
#endif // USE_D3D11_DYNAMIC_LIB

	struct RendererContextD3D11 : public RendererContextI
	{
		RendererContextD3D11()
			: m_lost(0)
			, m_captureTexture(NULL)
			, m_captureResolve(NULL)
			, m_wireframe(false)
			, m_flags(BGFX_RESET_NONE)
			, m_vsChanges(0)
			, m_fsChanges(0)
			, m_rtMsaa(false)
		{
		}

		~RendererContextD3D11()
		{
		}

		void init()
		{
			m_renderdocdll = loadRenderDoc();

			m_fbh.idx = invalidHandle;
			memset(m_uniforms, 0, sizeof(m_uniforms) );
			memset(&m_resolution, 0, sizeof(m_resolution) );

#if USE_D3D11_DYNAMIC_LIB
			m_d3d11dll = bx::dlopen("d3d11.dll");
			BGFX_FATAL(NULL != m_d3d11dll, Fatal::UnableToInitialize, "Failed to load d3d11.dll.");

			m_d3d9dll = NULL;

			if (BX_ENABLED(BGFX_CONFIG_DEBUG_PIX) )
			{
				// D3D11_1.h has ID3DUserDefinedAnnotation
				// http://msdn.microsoft.com/en-us/library/windows/desktop/hh446881%28v=vs.85%29.aspx
				m_d3d9dll = bx::dlopen("d3d9.dll");
				BGFX_FATAL(NULL != m_d3d9dll, Fatal::UnableToInitialize, "Failed to load d3d9.dll.");

				D3DPERF_SetMarker  = (PFN_D3DPERF_SET_MARKER )bx::dlsym(m_d3d9dll, "D3DPERF_SetMarker" );
				D3DPERF_BeginEvent = (PFN_D3DPERF_BEGIN_EVENT)bx::dlsym(m_d3d9dll, "D3DPERF_BeginEvent");
				D3DPERF_EndEvent   = (PFN_D3DPERF_END_EVENT  )bx::dlsym(m_d3d9dll, "D3DPERF_EndEvent"  );
				BX_CHECK(NULL != D3DPERF_SetMarker
					  && NULL != D3DPERF_BeginEvent
					  && NULL != D3DPERF_EndEvent
					  , "Failed to initialize PIX events."
					  );
			}

			D3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE)bx::dlsym(m_d3d11dll, "D3D11CreateDevice");
			BGFX_FATAL(NULL != D3D11CreateDevice, Fatal::UnableToInitialize, "Function D3D11CreateDevice not found.");

			m_dxgidll = bx::dlopen("dxgi.dll");
			BGFX_FATAL(NULL != m_dxgidll, Fatal::UnableToInitialize, "Failed to load dxgi.dll.");

			CreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY)bx::dlsym(m_dxgidll, "CreateDXGIFactory");
			BGFX_FATAL(NULL != CreateDXGIFactory, Fatal::UnableToInitialize, "Function CreateDXGIFactory not found.");
#endif // USE_D3D11_DYNAMIC_LIB

			HRESULT hr;

			IDXGIFactory* factory;
			hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
			BGFX_FATAL(SUCCEEDED(hr), Fatal::UnableToInitialize, "Unable to create DXGI factory.");

			m_adapter = NULL;
			m_driverType = D3D_DRIVER_TYPE_HARDWARE;

			IDXGIAdapter* adapter;
			for (uint32_t ii = 0; DXGI_ERROR_NOT_FOUND != factory->EnumAdapters(ii, &adapter); ++ii)
			{
				DXGI_ADAPTER_DESC desc;
				hr = adapter->GetDesc(&desc);
				if (SUCCEEDED(hr) )
				{
					BX_TRACE("Adapter #%d", ii);

					char description[BX_COUNTOF(desc.Description)];
					wcstombs(description, desc.Description, BX_COUNTOF(desc.Description) );
					BX_TRACE("\tDescription: %s", description);
					BX_TRACE("\tVendorId: 0x%08x, DeviceId: 0x%08x, SubSysId: 0x%08x, Revision: 0x%08x"
						, desc.VendorId
						, desc.DeviceId
						, desc.SubSysId
						, desc.Revision
						);
					BX_TRACE("\tMemory: %" PRIi64 " (video), %" PRIi64 " (system), %" PRIi64 " (shared)"
						, desc.DedicatedVideoMemory
						, desc.DedicatedSystemMemory
						, desc.SharedSystemMemory
						);

					if (BX_ENABLED(BGFX_CONFIG_DEBUG_PERFHUD)
					&&  0 != strstr(description, "PerfHUD") )
					{
						m_adapter = adapter;
						m_driverType = D3D_DRIVER_TYPE_REFERENCE;
					}
				}

				DX_RELEASE(adapter, adapter == m_adapter ? 1 : 0);
			}
			DX_RELEASE(factory, NULL != m_adapter ? 1 : 0);

			D3D_FEATURE_LEVEL features[] =
			{
				D3D_FEATURE_LEVEL_11_0,
				D3D_FEATURE_LEVEL_10_1,
				D3D_FEATURE_LEVEL_10_0,
			};

			uint32_t flags = D3D11_CREATE_DEVICE_SINGLETHREADED
				| BX_ENABLED(BGFX_CONFIG_DEBUG) ? D3D11_CREATE_DEVICE_DEBUG : 0
				;

			D3D_FEATURE_LEVEL featureLevel;

			hr = D3D11CreateDevice(m_adapter
				, m_driverType
				, NULL
				, flags
				, features
				, 1
				, D3D11_SDK_VERSION
				, &m_device
				, &featureLevel
				, &m_deviceCtx
				);
			BGFX_FATAL(SUCCEEDED(hr), Fatal::UnableToInitialize, "Unable to create Direct3D11 device.");

			IDXGIDevice* device;
			hr = m_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&device);
			BGFX_FATAL(SUCCEEDED(hr), Fatal::UnableToInitialize, "Unable to create Direct3D11 device.");

			hr = device->GetParent(__uuidof(IDXGIAdapter), (void**)&adapter);
			BGFX_FATAL(SUCCEEDED(hr), Fatal::UnableToInitialize, "Unable to create Direct3D11 device.");

			// GPA increases device ref count.
			// RenderDoc makes device ref count 0 here.
			//
			// This causes assert in debug. When debugger is present refcount
			// checks are off.
			setGraphicsDebuggerPresent(2 != getRefCount(device) );
			DX_RELEASE(device, 2);

			hr = adapter->GetDesc(&m_adapterDesc);
			BGFX_FATAL(SUCCEEDED(hr), Fatal::UnableToInitialize, "Unable to create Direct3D11 device.");

			hr = adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_factory);
			BGFX_FATAL(SUCCEEDED(hr), Fatal::UnableToInitialize, "Unable to create Direct3D11 device.");
			DX_RELEASE(adapter, 2);

			memset(&m_scd, 0, sizeof(m_scd) );
			m_scd.BufferDesc.Width  = BGFX_DEFAULT_WIDTH;
			m_scd.BufferDesc.Height = BGFX_DEFAULT_HEIGHT;
			m_scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			m_scd.BufferDesc.RefreshRate.Numerator = 60;
			m_scd.BufferDesc.RefreshRate.Denominator = 1;
			m_scd.SampleDesc.Count = 1;
			m_scd.SampleDesc.Quality = 0;
			m_scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			m_scd.BufferCount = 1;
			m_scd.OutputWindow = g_bgfxHwnd;
			m_scd.Windowed = true;

			hr = m_factory->CreateSwapChain(m_device
										, &m_scd
										, &m_swapChain
										);
			BGFX_FATAL(SUCCEEDED(hr), Fatal::UnableToInitialize, "Failed to create swap chain.");

			m_numWindows = 1;

			if (BX_ENABLED(BGFX_CONFIG_DEBUG) )
			{
				ID3D11InfoQueue* infoQueue;
				hr = m_device->QueryInterface(__uuidof(ID3D11InfoQueue), (void**)&infoQueue);

				if (SUCCEEDED(hr) )
				{
					infoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
					infoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR,      true);
					infoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_WARNING,    false);

					D3D11_INFO_QUEUE_FILTER filter;
					memset(&filter, 0, sizeof(filter) );

					D3D11_MESSAGE_CATEGORY categies[] =
					{
						D3D11_MESSAGE_CATEGORY_STATE_SETTING,
						D3D11_MESSAGE_CATEGORY_EXECUTION,
					};
					filter.DenyList.NumCategories = BX_COUNTOF(categies);
					filter.DenyList.pCategoryList = categies;
					infoQueue->PushStorageFilter(&filter);

					DX_RELEASE(infoQueue, 3);
				}
				else
				{
					// InfoQueue QueryInterface will fail when AMD GPU Perfstudio 2 is present.
					setGraphicsDebuggerPresent(true);
				}
			}

			UniformHandle handle = BGFX_INVALID_HANDLE;
			for (uint32_t ii = 0; ii < PredefinedUniform::Count; ++ii)
			{
				m_uniformReg.add(handle, getPredefinedUniformName(PredefinedUniform::Enum(ii) ), &m_predefinedUniforms[ii]);
			}

			g_caps.supported |= ( 0
								| BGFX_CAPS_TEXTURE_3D
								| BGFX_CAPS_TEXTURE_COMPARE_ALL
								| BGFX_CAPS_INSTANCING
								| BGFX_CAPS_VERTEX_ATTRIB_HALF
								| BGFX_CAPS_FRAGMENT_DEPTH
								| BGFX_CAPS_BLEND_INDEPENDENT
								| BGFX_CAPS_COMPUTE
								| (getIntelExtensions(m_device) ? BGFX_CAPS_FRAGMENT_ORDERING : 0)
								| BGFX_CAPS_SWAP_CHAIN
								);
			g_caps.maxTextureSize   = D3D11_REQ_TEXTURE2D_U_OR_V_DIMENSION;
			g_caps.maxFBAttachments = bx::uint32_min(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT, BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS);

			for (uint32_t ii = 0; ii < TextureFormat::Count; ++ii)
			{
				g_caps.formats[ii] = DXGI_FORMAT_UNKNOWN == s_textureFormat[ii].m_fmt ? 0 : 1;
			}

			updateMsaa();
			postReset();
		}

		void shutdown()
		{
			preReset();

			m_deviceCtx->ClearState();

			invalidateCache();

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_indexBuffers); ++ii)
			{
				m_indexBuffers[ii].destroy();
			}

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_vertexBuffers); ++ii)
			{
				m_vertexBuffers[ii].destroy();
			}

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_shaders); ++ii)
			{
				m_shaders[ii].destroy();
			}

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_textures); ++ii)
			{
				m_textures[ii].destroy();
			}

			DX_RELEASE(m_swapChain, 0);
			DX_RELEASE(m_deviceCtx, 0);
			DX_RELEASE(m_device, 0);
			DX_RELEASE(m_factory, 0);

			unloadRenderDoc(m_renderdocdll);

#if USE_D3D11_DYNAMIC_LIB
			bx::dlclose(m_dxgidll);
			bx::dlclose(m_d3d9dll);
			bx::dlclose(m_d3d11dll);
#endif // USE_D3D11_DYNAMIC_LIB
		}

		RendererType::Enum getRendererType() const BX_OVERRIDE
		{
			return RendererType::Direct3D11;
		}

		const char* getRendererName() const BX_OVERRIDE
		{
			return BGFX_RENDERER_DIRECT3D11_NAME;
		}

		void createIndexBuffer(IndexBufferHandle _handle, Memory* _mem) BX_OVERRIDE
		{
			m_indexBuffers[_handle.idx].create(_mem->size, _mem->data);
		}

		void destroyIndexBuffer(IndexBufferHandle _handle) BX_OVERRIDE
		{
			m_indexBuffers[_handle.idx].destroy();
		}

		void createVertexDecl(VertexDeclHandle _handle, const VertexDecl& _decl) BX_OVERRIDE
		{
			VertexDecl& decl = m_vertexDecls[_handle.idx];
			memcpy(&decl, &_decl, sizeof(VertexDecl) );
			dump(decl);
		}

		void destroyVertexDecl(VertexDeclHandle /*_handle*/) BX_OVERRIDE
		{
		}

		void createVertexBuffer(VertexBufferHandle _handle, Memory* _mem, VertexDeclHandle _declHandle) BX_OVERRIDE
		{
			m_vertexBuffers[_handle.idx].create(_mem->size, _mem->data, _declHandle);
		}

		void destroyVertexBuffer(VertexBufferHandle _handle) BX_OVERRIDE
		{
			m_vertexBuffers[_handle.idx].destroy();
		}

		void createDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _size) BX_OVERRIDE
		{
			m_indexBuffers[_handle.idx].create(_size, NULL);
		}

		void updateDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _offset, uint32_t _size, Memory* _mem) BX_OVERRIDE
		{
			m_indexBuffers[_handle.idx].update(_offset, bx::uint32_min(_size, _mem->size), _mem->data);
		}

		void destroyDynamicIndexBuffer(IndexBufferHandle _handle) BX_OVERRIDE
		{
			m_indexBuffers[_handle.idx].destroy();
		}

		void createDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _size) BX_OVERRIDE
		{
			VertexDeclHandle decl = BGFX_INVALID_HANDLE;
			m_vertexBuffers[_handle.idx].create(_size, NULL, decl);
		}

		void updateDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _offset, uint32_t _size, Memory* _mem) BX_OVERRIDE
		{
			m_vertexBuffers[_handle.idx].update(_offset, bx::uint32_min(_size, _mem->size), _mem->data);
		}

		void destroyDynamicVertexBuffer(VertexBufferHandle _handle) BX_OVERRIDE
		{
			m_vertexBuffers[_handle.idx].destroy();
		}

		void createShader(ShaderHandle _handle, Memory* _mem) BX_OVERRIDE
		{
			m_shaders[_handle.idx].create(_mem);
		}

		void destroyShader(ShaderHandle _handle) BX_OVERRIDE
		{
			m_shaders[_handle.idx].destroy();
		}

		void createProgram(ProgramHandle _handle, ShaderHandle _vsh, ShaderHandle _fsh) BX_OVERRIDE
		{
			m_program[_handle.idx].create(&m_shaders[_vsh.idx], isValid(_fsh) ? &m_shaders[_fsh.idx] : NULL);
		}

		void destroyProgram(ProgramHandle _handle) BX_OVERRIDE
		{
			m_program[_handle.idx].destroy();
		}

		void createTexture(TextureHandle _handle, Memory* _mem, uint32_t _flags, uint8_t _skip) BX_OVERRIDE
		{
			m_textures[_handle.idx].create(_mem, _flags, _skip);
		}

		void updateTextureBegin(TextureHandle /*_handle*/, uint8_t /*_side*/, uint8_t /*_mip*/) BX_OVERRIDE
		{
		}

		void updateTexture(TextureHandle _handle, uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem) BX_OVERRIDE
		{
			m_textures[_handle.idx].update(_side, _mip, _rect, _z, _depth, _pitch, _mem);
		}

		void updateTextureEnd() BX_OVERRIDE
		{
		}

		void destroyTexture(TextureHandle _handle) BX_OVERRIDE
		{
			m_textures[_handle.idx].destroy();
		}

		void createFrameBuffer(FrameBufferHandle _handle, uint8_t _num, const TextureHandle* _textureHandles) BX_OVERRIDE
		{
			m_frameBuffers[_handle.idx].create(_num, _textureHandles);
		}

		void createFrameBuffer(FrameBufferHandle _handle, void* _nwh, uint32_t _width, uint32_t _height, TextureFormat::Enum _depthFormat) BX_OVERRIDE
		{
			uint16_t denseIdx = m_numWindows++;
			m_windows[denseIdx] = _handle;
			m_frameBuffers[_handle.idx].create(denseIdx, _nwh, _width, _height, _depthFormat);
		}

		void destroyFrameBuffer(FrameBufferHandle _handle) BX_OVERRIDE
		{
			uint16_t denseIdx = m_frameBuffers[_handle.idx].destroy();
			if (UINT16_MAX != denseIdx)
			{
				--m_numWindows;
				if (m_numWindows > 1)
				{
					FrameBufferHandle handle = m_windows[m_numWindows];
					m_windows[denseIdx] = handle;
					m_frameBuffers[handle.idx].m_denseIdx = denseIdx;
				}
			}
		}

		void createUniform(UniformHandle _handle, UniformType::Enum _type, uint16_t _num, const char* _name) BX_OVERRIDE
		{
			if (NULL != m_uniforms[_handle.idx])
			{
				BX_FREE(g_allocator, m_uniforms[_handle.idx]);
			}

			uint32_t size = BX_ALIGN_16(g_uniformTypeSize[_type]*_num);
			void* data = BX_ALLOC(g_allocator, size);
			memset(data, 0, size);
			m_uniforms[_handle.idx] = data;
			m_uniformReg.add(_handle, _name, data);
		}

		void destroyUniform(UniformHandle _handle) BX_OVERRIDE
		{
			BX_FREE(g_allocator, m_uniforms[_handle.idx]);
			m_uniforms[_handle.idx] = NULL;
		}

		void saveScreenShot(const char* _filePath) BX_OVERRIDE
		{
			ID3D11Texture2D* backBuffer;
			DX_CHECK(m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer) );

			D3D11_TEXTURE2D_DESC backBufferDesc;
			backBuffer->GetDesc(&backBufferDesc);

			D3D11_TEXTURE2D_DESC desc;
			memcpy(&desc, &backBufferDesc, sizeof(desc) );
			desc.SampleDesc.Count = 1;
			desc.SampleDesc.Quality = 0;
			desc.Usage = D3D11_USAGE_STAGING;
			desc.BindFlags = 0;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

			ID3D11Texture2D* texture;
			HRESULT hr = m_device->CreateTexture2D(&desc, NULL, &texture);
			if (SUCCEEDED(hr) )
			{
				if (backBufferDesc.SampleDesc.Count == 1)
				{
					m_deviceCtx->CopyResource(texture, backBuffer);
				}
				else
				{
					desc.Usage = D3D11_USAGE_DEFAULT;
					desc.CPUAccessFlags = 0;
					ID3D11Texture2D* resolve;
					HRESULT hr = m_device->CreateTexture2D(&desc, NULL, &resolve);
					if (SUCCEEDED(hr) )
					{
						m_deviceCtx->ResolveSubresource(resolve, 0, backBuffer, 0, desc.Format);
						m_deviceCtx->CopyResource(texture, resolve);
						DX_RELEASE(resolve, 0);
					}
				}

				D3D11_MAPPED_SUBRESOURCE mapped;
				DX_CHECK(m_deviceCtx->Map(texture, 0, D3D11_MAP_READ, 0, &mapped) );
				g_callback->screenShot(_filePath
					, backBufferDesc.Width
					, backBufferDesc.Height
					, mapped.RowPitch
					, mapped.pData
					, backBufferDesc.Height*mapped.RowPitch
					, false
					);
				m_deviceCtx->Unmap(texture, 0);

				DX_RELEASE(texture, 0);
			}

			DX_RELEASE(backBuffer, 0);
		}

		void updateViewName(uint8_t _id, const char* _name) BX_OVERRIDE
		{
			mbstowcs(&s_viewNameW[_id][0], _name, BX_COUNTOF(s_viewNameW[0]) );
		}

		void updateUniform(uint16_t _loc, const void* _data, uint32_t _size) BX_OVERRIDE
		{
			memcpy(m_uniforms[_loc], _data, _size);
		}

		void setMarker(const char* _marker, uint32_t _size) BX_OVERRIDE
		{
			if (BX_ENABLED(BGFX_CONFIG_DEBUG_PIX) )
			{
				uint32_t size = _size*sizeof(wchar_t);
				wchar_t* name = (wchar_t*)alloca(size);
				mbstowcs(name, _marker, size-2);
				PIX_SETMARKER(D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xff), name);
			}
		}

		void submit(Frame* _render, ClearQuad& _clearQuad, TextVideoMemBlitter& _textVideoMemBlitter) BX_OVERRIDE;

		void blitSetup(TextVideoMemBlitter& _blitter) BX_OVERRIDE
		{
			ID3D11DeviceContext* deviceCtx = m_deviceCtx;

			uint32_t width  = m_scd.BufferDesc.Width;
			uint32_t height = m_scd.BufferDesc.Height;

			FrameBufferHandle fbh = BGFX_INVALID_HANDLE;
			setFrameBuffer(fbh, false);

			D3D11_VIEWPORT vp;
			vp.TopLeftX = 0;
			vp.TopLeftY = 0;
			vp.Width    = (float)width;
			vp.Height   = (float)height;
			vp.MinDepth = 0.0f;
			vp.MaxDepth = 1.0f;
			deviceCtx->RSSetViewports(1, &vp);

			uint64_t state = BGFX_STATE_RGB_WRITE
				| BGFX_STATE_ALPHA_WRITE
				| BGFX_STATE_DEPTH_TEST_ALWAYS
				;

			setBlendState(state);
			setDepthStencilState(state);
			setRasterizerState(state);

			ProgramD3D11& program = m_program[_blitter.m_program.idx];
			m_currentProgram = &program;
			deviceCtx->VSSetShader(program.m_vsh->m_vertexShader, NULL, 0);
			deviceCtx->VSSetConstantBuffers(0, 1, &program.m_vsh->m_buffer);
			deviceCtx->PSSetShader(program.m_fsh->m_pixelShader, NULL, 0);
			deviceCtx->PSSetConstantBuffers(0, 1, &program.m_fsh->m_buffer);

			VertexBufferD3D11& vb = m_vertexBuffers[_blitter.m_vb->handle.idx];
			VertexDecl& vertexDecl = m_vertexDecls[_blitter.m_vb->decl.idx];
			uint32_t stride = vertexDecl.m_stride;
			uint32_t offset = 0;
			deviceCtx->IASetVertexBuffers(0, 1, &vb.m_ptr, &stride, &offset);
			setInputLayout(vertexDecl, program, 0);

			IndexBufferD3D11& ib = m_indexBuffers[_blitter.m_ib->handle.idx];
			deviceCtx->IASetIndexBuffer(ib.m_ptr, DXGI_FORMAT_R16_UINT, 0);

			float proj[16];
			mtxOrtho(proj, 0.0f, (float)width, (float)height, 0.0f, 0.0f, 1000.0f);

			PredefinedUniform& predefined = program.m_predefined[0];
			uint8_t flags = predefined.m_type;
			setShaderConstant(flags, predefined.m_loc, proj, 4);

			commitShaderConstants();
			m_textures[_blitter.m_texture.idx].commit(0);
			commitTextureStage();
		}

		void blitRender(TextVideoMemBlitter& _blitter, uint32_t _numIndices) BX_OVERRIDE
		{
			ID3D11DeviceContext* deviceCtx = m_deviceCtx;

			uint32_t numVertices = _numIndices*4/6;
			m_indexBuffers [_blitter.m_ib->handle.idx].update(0, _numIndices*2, _blitter.m_ib->data);
			m_vertexBuffers[_blitter.m_vb->handle.idx].update(0, numVertices*_blitter.m_decl.m_stride, _blitter.m_vb->data, true);

			deviceCtx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			deviceCtx->DrawIndexed(_numIndices, 0, 0);
		}

		void preReset()
		{
			DX_RELEASE(m_backBufferDepthStencil, 0);
			DX_RELEASE(m_backBufferColor, 0);

//			invalidateCache();

			capturePreReset();
		}

		void postReset()
		{
			ID3D11Texture2D* color;
			DX_CHECK(m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&color) );

			DX_CHECK(m_device->CreateRenderTargetView(color, NULL, &m_backBufferColor) );
			DX_RELEASE(color, 0);

			D3D11_TEXTURE2D_DESC dsd;
			dsd.Width = m_scd.BufferDesc.Width;
			dsd.Height = m_scd.BufferDesc.Height;
			dsd.MipLevels = 1;
			dsd.ArraySize = 1;
			dsd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			dsd.SampleDesc = m_scd.SampleDesc;
			dsd.Usage = D3D11_USAGE_DEFAULT;
			dsd.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			dsd.CPUAccessFlags = 0;
			dsd.MiscFlags = 0;

			ID3D11Texture2D* depthStencil;
			DX_CHECK(m_device->CreateTexture2D(&dsd, NULL, &depthStencil) );
			DX_CHECK(m_device->CreateDepthStencilView(depthStencil, NULL, &m_backBufferDepthStencil) );
			DX_RELEASE(depthStencil, 0);

			m_deviceCtx->OMSetRenderTargets(1, &m_backBufferColor, m_backBufferDepthStencil);

			m_currentColor = m_backBufferColor;
			m_currentDepthStencil = m_backBufferDepthStencil;

			capturePostReset();
		}

		static bool isLost(HRESULT _hr)
		{
			return DXGI_ERROR_DEVICE_REMOVED == _hr
				|| DXGI_ERROR_DEVICE_HUNG == _hr
				|| DXGI_ERROR_DEVICE_RESET == _hr
				|| DXGI_ERROR_DRIVER_INTERNAL_ERROR == _hr
				|| DXGI_ERROR_NOT_CURRENTLY_AVAILABLE == _hr
				;
		}

		void flip() BX_OVERRIDE
		{
			if (NULL != m_swapChain)
			{
				HRESULT hr = 0;
				uint32_t syncInterval = !!(m_flags & BGFX_RESET_VSYNC);
				for (uint32_t ii = 1, num = m_numWindows; ii < num && SUCCEEDED(hr); ++ii)
				{
					hr = m_frameBuffers[m_windows[ii].idx].m_swapChain->Present(syncInterval, 0);
				}

				if (SUCCEEDED(hr) )
				{
					hr = m_swapChain->Present(syncInterval, 0);
				}

				if (FAILED(hr)
				&&  isLost(hr) )
				{
					++m_lost;
					BGFX_FATAL(10 > m_lost, bgfx::Fatal::DeviceLost, "Device is lost. FAILED 0x%08x", hr);
				}
				else
				{
					m_lost = 0;
				}
			}
		}

		void invalidateCache()
		{
			m_inputLayoutCache.invalidate();
			m_blendStateCache.invalidate();
			m_depthStencilStateCache.invalidate();
			m_rasterizerStateCache.invalidate();
			m_samplerStateCache.invalidate();
		}

		void updateMsaa()
		{
			for (uint32_t ii = 1, last = 0; ii < BX_COUNTOF(s_msaa); ++ii)
			{
				uint32_t msaa = s_checkMsaa[ii];
				uint32_t quality = 0;
				HRESULT hr = m_device->CheckMultisampleQualityLevels(m_scd.BufferDesc.Format, msaa, &quality);

				if (SUCCEEDED(hr)
				&&  0 < quality)
				{
					s_msaa[ii].Count = msaa;
					s_msaa[ii].Quality = quality - 1;
					last = ii;
				}
				else
				{
					s_msaa[ii] = s_msaa[last];
				}
			}
		}

		void updateResolution(const Resolution& _resolution)
		{
			if ( (uint32_t)m_scd.BufferDesc.Width != _resolution.m_width
			||   (uint32_t)m_scd.BufferDesc.Height != _resolution.m_height
			||   m_flags != _resolution.m_flags)
			{
				bool resize = (m_flags&BGFX_RESET_MSAA_MASK) == (_resolution.m_flags&BGFX_RESET_MSAA_MASK);
				m_flags = _resolution.m_flags;

				m_textVideoMem.resize(false, _resolution.m_width, _resolution.m_height);
				m_textVideoMem.clear();

				m_resolution = _resolution;

				m_scd.BufferDesc.Width = _resolution.m_width;
				m_scd.BufferDesc.Height = _resolution.m_height;

				preReset();

				if (resize)
				{
					DX_CHECK(m_swapChain->ResizeBuffers(2
						, m_scd.BufferDesc.Width
						, m_scd.BufferDesc.Height
						, m_scd.BufferDesc.Format
						, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH
						) );
				}
				else
				{
					updateMsaa();
					m_scd.SampleDesc = s_msaa[(m_flags&BGFX_RESET_MSAA_MASK)>>BGFX_RESET_MSAA_SHIFT];

					DX_RELEASE(m_swapChain, 0);

					HRESULT hr;
					hr = m_factory->CreateSwapChain(m_device
						, &m_scd
						, &m_swapChain
						);
					BGFX_FATAL(SUCCEEDED(hr), bgfx::Fatal::UnableToInitialize, "Failed to create swap chain.");
				}

				postReset();
			}
		}

		void setShaderConstant(uint8_t _flags, uint16_t _regIndex, const void* _val, uint16_t _numRegs)
		{
			if (_flags&BGFX_UNIFORM_FRAGMENTBIT)
			{
				memcpy(&m_fsScratch[_regIndex], _val, _numRegs*16);
				m_fsChanges += _numRegs;
			}
			else
			{
				memcpy(&m_vsScratch[_regIndex], _val, _numRegs*16);
				m_vsChanges += _numRegs;
			}
		}

		void commitShaderConstants()
		{
			if (0 < m_vsChanges)
			{
				if (NULL != m_currentProgram->m_vsh->m_buffer)
				{
					m_deviceCtx->UpdateSubresource(m_currentProgram->m_vsh->m_buffer, 0, 0, m_vsScratch, 0, 0);
				}

				m_vsChanges = 0;
			}

			if (0 < m_fsChanges)
			{
				if (NULL != m_currentProgram->m_fsh->m_buffer)
				{
					m_deviceCtx->UpdateSubresource(m_currentProgram->m_fsh->m_buffer, 0, 0, m_fsScratch, 0, 0);
				}

				m_fsChanges = 0;
			}
		}

		void setFrameBuffer(FrameBufferHandle _fbh, bool _msaa = true)
		{
			BX_UNUSED(_msaa);
			if (!isValid(_fbh) )
			{
				m_deviceCtx->OMSetRenderTargets(1, &m_backBufferColor, m_backBufferDepthStencil);

				m_currentColor = m_backBufferColor;
				m_currentDepthStencil = m_backBufferDepthStencil;
			}
			else
			{
				invalidateTextureStage();

				FrameBufferD3D11& frameBuffer = m_frameBuffers[_fbh.idx];
				m_deviceCtx->OMSetRenderTargets(frameBuffer.m_num, frameBuffer.m_rtv, frameBuffer.m_dsv);

				m_currentColor = frameBuffer.m_rtv[0];
				m_currentDepthStencil = frameBuffer.m_dsv;
			}

			if (isValid(m_fbh)
			&&  m_fbh.idx != _fbh.idx
			&&  m_rtMsaa)
			{
				FrameBufferD3D11& frameBuffer = m_frameBuffers[m_fbh.idx];
				frameBuffer.resolve();
			}

			m_fbh = _fbh;
			m_rtMsaa = _msaa;
		}

		void clear(const Clear& _clear, const float _palette[][4])
		{
			if (isValid(m_fbh) )
			{
				FrameBufferD3D11& frameBuffer = m_frameBuffers[m_fbh.idx];
				frameBuffer.clear(_clear, _palette);
			}
			else
			{
				if (NULL != m_currentColor
				&&  BGFX_CLEAR_COLOR_BIT & _clear.m_flags)
				{
					if (BGFX_CLEAR_COLOR_USE_PALETTE_BIT & _clear.m_flags)
					{
						uint8_t index = _clear.m_index[0];
						if (UINT8_MAX != index)
						{
							m_deviceCtx->ClearRenderTargetView(m_currentColor, _palette[index]);
						}
					}
					else
					{
						float frgba[4] =
						{ 
							_clear.m_index[0]*1.0f/255.0f,
							_clear.m_index[1]*1.0f/255.0f,
							_clear.m_index[2]*1.0f/255.0f,
							_clear.m_index[3]*1.0f/255.0f,
						};
						m_deviceCtx->ClearRenderTargetView(m_currentColor, frgba);
					}
				}

				if (NULL != m_currentDepthStencil
				&& (BGFX_CLEAR_DEPTH_BIT|BGFX_CLEAR_STENCIL_BIT) & _clear.m_flags)
				{
					DWORD flags = 0;
					flags |= (_clear.m_flags & BGFX_CLEAR_DEPTH_BIT) ? D3D11_CLEAR_DEPTH : 0;
					flags |= (_clear.m_flags & BGFX_CLEAR_STENCIL_BIT) ? D3D11_CLEAR_STENCIL : 0;
					m_deviceCtx->ClearDepthStencilView(m_currentDepthStencil, flags, _clear.m_depth, _clear.m_stencil);
				}
			}
		}

		void setInputLayout(const VertexDecl& _vertexDecl, const ProgramD3D11& _program, uint8_t _numInstanceData)
		{
			uint64_t layoutHash = (uint64_t(_vertexDecl.m_hash)<<32) | _program.m_vsh->m_hash;
			layoutHash ^= _numInstanceData;
			ID3D11InputLayout* layout = m_inputLayoutCache.find(layoutHash);
			if (NULL == layout)
			{
				D3D11_INPUT_ELEMENT_DESC vertexElements[Attrib::Count+1+BGFX_CONFIG_MAX_INSTANCE_DATA_COUNT];

				VertexDecl decl;
				memcpy(&decl, &_vertexDecl, sizeof(VertexDecl) );
				const uint8_t* attrMask = _program.m_vsh->m_attrMask;

				for (uint32_t ii = 0; ii < Attrib::Count; ++ii)
				{
					uint8_t mask = attrMask[ii];
					uint8_t attr = (decl.m_attributes[ii] & mask);
					decl.m_attributes[ii] = attr == 0 ? 0xff : attr == 0xff ? 0 : attr;
				}

				D3D11_INPUT_ELEMENT_DESC* elem = fillVertexDecl(vertexElements, decl);
				uint32_t num = uint32_t(elem-vertexElements);

				const D3D11_INPUT_ELEMENT_DESC inst = { "TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 };

				for (uint32_t ii = 0; ii < _numInstanceData; ++ii)
				{
					uint32_t index = 8-_numInstanceData+ii;

					uint32_t jj;
					D3D11_INPUT_ELEMENT_DESC* curr = vertexElements;
					for (jj = 0; jj < num; ++jj)
					{
						curr = &vertexElements[jj];
						if (0 == strcmp(curr->SemanticName, "TEXCOORD")
						&&  curr->SemanticIndex == index)
						{
							break;
						}
					}

					if (jj == num)
					{
						curr = elem;
						++elem;
					}

					memcpy(curr, &inst, sizeof(D3D11_INPUT_ELEMENT_DESC) );
					curr->InputSlot = 1;
					curr->SemanticIndex = index;
					curr->AlignedByteOffset = ii*16;
				}

				num = uint32_t(elem-vertexElements);
				DX_CHECK(m_device->CreateInputLayout(vertexElements
					, num
					, _program.m_vsh->m_code->data
					, _program.m_vsh->m_code->size
					, &layout
					) );
				m_inputLayoutCache.add(layoutHash, layout);
			}

			m_deviceCtx->IASetInputLayout(layout);
		}

		void setBlendState(uint64_t _state, uint32_t _rgba = 0)
		{
			_state &= 0
				| BGFX_STATE_BLEND_MASK
				| BGFX_STATE_BLEND_EQUATION_MASK
				| BGFX_STATE_BLEND_INDEPENDENT
				| BGFX_STATE_ALPHA_WRITE
				| BGFX_STATE_RGB_WRITE
				;

			bx::HashMurmur2A murmur;
			murmur.begin();
			murmur.add(_state);

			const uint64_t f0 = BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_FACTOR, BGFX_STATE_BLEND_FACTOR);
			const uint64_t f1 = BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_INV_FACTOR, BGFX_STATE_BLEND_INV_FACTOR);
			bool hasFactor = f0 == (_state & f0) 
				|| f1 == (_state & f1)
				;

			float blendFactor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
			if (hasFactor)
			{
				blendFactor[0] = ( (_rgba>>24)     )/255.0f;
				blendFactor[1] = ( (_rgba>>16)&0xff)/255.0f;
				blendFactor[2] = ( (_rgba>> 8)&0xff)/255.0f;
				blendFactor[3] = ( (_rgba    )&0xff)/255.0f;
			}
			else
			{
				murmur.add(_rgba);
			}

			uint32_t hash = murmur.end();

			ID3D11BlendState* bs = m_blendStateCache.find(hash);
			if (NULL == bs)
			{
				D3D11_BLEND_DESC desc;
				memset(&desc, 0, sizeof(desc) );
				desc.IndependentBlendEnable = !!(BGFX_STATE_BLEND_INDEPENDENT & _state);

				D3D11_RENDER_TARGET_BLEND_DESC* drt = &desc.RenderTarget[0];
				drt->BlendEnable = !!(BGFX_STATE_BLEND_MASK & _state);

				const uint32_t blend    = uint32_t( (_state&BGFX_STATE_BLEND_MASK)>>BGFX_STATE_BLEND_SHIFT);
				const uint32_t equation = uint32_t( (_state&BGFX_STATE_BLEND_EQUATION_MASK)>>BGFX_STATE_BLEND_EQUATION_SHIFT);

				const uint32_t srcRGB = (blend    )&0xf;
				const uint32_t dstRGB = (blend>> 4)&0xf;
				const uint32_t srcA   = (blend>> 8)&0xf;
				const uint32_t dstA   = (blend>>12)&0xf;

				const uint32_t equRGB = (equation   )&0x7;
				const uint32_t equA   = (equation>>3)&0x7;

				drt->SrcBlend       = s_blendFactor[srcRGB][0];
				drt->DestBlend      = s_blendFactor[dstRGB][0];
				drt->BlendOp        = s_blendEquation[equRGB];

				drt->SrcBlendAlpha  = s_blendFactor[srcA][1];
				drt->DestBlendAlpha = s_blendFactor[dstA][1];
				drt->BlendOpAlpha   = s_blendEquation[equA];

				uint32_t writeMask = (_state&BGFX_STATE_ALPHA_WRITE) ? D3D11_COLOR_WRITE_ENABLE_ALPHA : 0;
				writeMask |= (_state&BGFX_STATE_RGB_WRITE) ? D3D11_COLOR_WRITE_ENABLE_RED|D3D11_COLOR_WRITE_ENABLE_GREEN|D3D11_COLOR_WRITE_ENABLE_BLUE : 0;

				drt->RenderTargetWriteMask = writeMask;

				if (desc.IndependentBlendEnable)
				{
					for (uint32_t ii = 1, rgba = _rgba; ii < BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS; ++ii, rgba >>= 11)
					{
						drt = &desc.RenderTarget[ii];
						drt->BlendEnable = 0 != (rgba&0x7ff);

						const uint32_t src      = (rgba   )&0xf;
						const uint32_t dst      = (rgba>>4)&0xf;
						const uint32_t equation = (rgba>>8)&0x7;

						drt->SrcBlend       = s_blendFactor[src][0];
						drt->DestBlend      = s_blendFactor[dst][0];
						drt->BlendOp        = s_blendEquation[equation];

						drt->SrcBlendAlpha  = s_blendFactor[src][1];
						drt->DestBlendAlpha = s_blendFactor[dst][1];
						drt->BlendOpAlpha   = s_blendEquation[equation];

						drt->RenderTargetWriteMask = writeMask;
					}
				}
				else
				{
					for (uint32_t ii = 1; ii < BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS; ++ii)
					{
						memcpy(&desc.RenderTarget[ii], drt, sizeof(D3D11_RENDER_TARGET_BLEND_DESC) );
					}
				}

				DX_CHECK(m_device->CreateBlendState(&desc, &bs) );

				m_blendStateCache.add(hash, bs);
			}

			m_deviceCtx->OMSetBlendState(bs, blendFactor, 0xffffffff);
		}

		void setDepthStencilState(uint64_t _state, uint64_t _stencil = 0)
		{
			_state &= BGFX_STATE_DEPTH_WRITE|BGFX_STATE_DEPTH_TEST_MASK;

			uint32_t fstencil = unpackStencil(0, _stencil);
			uint32_t ref = (fstencil&BGFX_STENCIL_FUNC_REF_MASK)>>BGFX_STENCIL_FUNC_REF_SHIFT;
			_stencil &= packStencil(~BGFX_STENCIL_FUNC_REF_MASK, BGFX_STENCIL_MASK);

			bx::HashMurmur2A murmur;
			murmur.begin();
			murmur.add(_state);
			murmur.add(_stencil);
			uint32_t hash = murmur.end();

			ID3D11DepthStencilState* dss = m_depthStencilStateCache.find(hash);
			if (NULL == dss)
			{
				D3D11_DEPTH_STENCIL_DESC desc;
				memset(&desc, 0, sizeof(desc) );
				uint32_t func = (_state&BGFX_STATE_DEPTH_TEST_MASK)>>BGFX_STATE_DEPTH_TEST_SHIFT;
				desc.DepthEnable = 0 != func;
				desc.DepthWriteMask = !!(BGFX_STATE_DEPTH_WRITE & _state) ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
				desc.DepthFunc = s_cmpFunc[func];

				uint32_t bstencil = unpackStencil(1, _stencil);
				uint32_t frontAndBack = bstencil != BGFX_STENCIL_NONE && bstencil != fstencil;
				bstencil = frontAndBack ? bstencil : fstencil;

				desc.StencilEnable = 0 != _stencil;
				desc.StencilReadMask = (fstencil&BGFX_STENCIL_FUNC_RMASK_MASK)>>BGFX_STENCIL_FUNC_RMASK_SHIFT;
				desc.StencilWriteMask = 0xff;
				desc.FrontFace.StencilFailOp      = s_stencilOp[(fstencil&BGFX_STENCIL_OP_FAIL_S_MASK)>>BGFX_STENCIL_OP_FAIL_S_SHIFT];
				desc.FrontFace.StencilDepthFailOp = s_stencilOp[(fstencil&BGFX_STENCIL_OP_FAIL_Z_MASK)>>BGFX_STENCIL_OP_FAIL_Z_SHIFT];
				desc.FrontFace.StencilPassOp      = s_stencilOp[(fstencil&BGFX_STENCIL_OP_PASS_Z_MASK)>>BGFX_STENCIL_OP_PASS_Z_SHIFT];
				desc.FrontFace.StencilFunc        = s_cmpFunc[(fstencil&BGFX_STENCIL_TEST_MASK)>>BGFX_STENCIL_TEST_SHIFT];
				desc.BackFace.StencilFailOp       = s_stencilOp[(bstencil&BGFX_STENCIL_OP_FAIL_S_MASK)>>BGFX_STENCIL_OP_FAIL_S_SHIFT];
				desc.BackFace.StencilDepthFailOp  = s_stencilOp[(bstencil&BGFX_STENCIL_OP_FAIL_Z_MASK)>>BGFX_STENCIL_OP_FAIL_Z_SHIFT];
				desc.BackFace.StencilPassOp       = s_stencilOp[(bstencil&BGFX_STENCIL_OP_PASS_Z_MASK)>>BGFX_STENCIL_OP_PASS_Z_SHIFT];
				desc.BackFace.StencilFunc         = s_cmpFunc[(bstencil&BGFX_STENCIL_TEST_MASK)>>BGFX_STENCIL_TEST_SHIFT];

				DX_CHECK(m_device->CreateDepthStencilState(&desc, &dss) );

				m_depthStencilStateCache.add(hash, dss);
			}

			m_deviceCtx->OMSetDepthStencilState(dss, ref);
		}

		void setDebugWireframe(bool _wireframe)
		{
			if (m_wireframe != _wireframe)
			{
				m_wireframe = _wireframe;
				m_rasterizerStateCache.invalidate();
			}
		}

		void setRasterizerState(uint64_t _state, bool _wireframe = false, bool _scissor = false)
		{
			_state &= BGFX_STATE_CULL_MASK|BGFX_STATE_MSAA;
			_state |= _wireframe ? BGFX_STATE_PT_LINES : BGFX_STATE_NONE;
			_state |= _scissor ? BGFX_STATE_RESERVED_MASK : 0;

			ID3D11RasterizerState* rs = m_rasterizerStateCache.find(_state);
			if (NULL == rs)
			{
				uint32_t cull = (_state&BGFX_STATE_CULL_MASK)>>BGFX_STATE_CULL_SHIFT;

				D3D11_RASTERIZER_DESC desc;
				desc.FillMode = _wireframe ? D3D11_FILL_WIREFRAME : D3D11_FILL_SOLID;
				desc.CullMode = s_cullMode[cull];
				desc.FrontCounterClockwise = false;
				desc.DepthBias = 0;
				desc.DepthBiasClamp = 0.0f;
				desc.SlopeScaledDepthBias = 0.0f;
				desc.DepthClipEnable = false;
				desc.ScissorEnable = _scissor;
				desc.MultisampleEnable = !!(_state&BGFX_STATE_MSAA);
				desc.AntialiasedLineEnable = false;

				DX_CHECK(m_device->CreateRasterizerState(&desc, &rs) );

				m_rasterizerStateCache.add(_state, rs);
			}

			m_deviceCtx->RSSetState(rs);
		}

		ID3D11SamplerState* getSamplerState(uint32_t _flags)
		{
			_flags &= BGFX_TEXTURE_SAMPLER_BITS_MASK;
			ID3D11SamplerState* sampler = m_samplerStateCache.find(_flags);
			if (NULL == sampler)
			{
				const uint32_t cmpFunc = (_flags&BGFX_TEXTURE_COMPARE_MASK)>>BGFX_TEXTURE_COMPARE_SHIFT;
				const uint8_t minFilter = s_textureFilter[0][(_flags&BGFX_TEXTURE_MIN_MASK)>>BGFX_TEXTURE_MIN_SHIFT];
				const uint8_t magFilter = s_textureFilter[1][(_flags&BGFX_TEXTURE_MAG_MASK)>>BGFX_TEXTURE_MAG_SHIFT];
				const uint8_t mipFilter = s_textureFilter[2][(_flags&BGFX_TEXTURE_MIP_MASK)>>BGFX_TEXTURE_MIP_SHIFT];
				const uint8_t filter = 0 == cmpFunc ? 0 : D3D11_COMPARISON_FILTERING_BIT;

				D3D11_SAMPLER_DESC sd;
				sd.Filter = (D3D11_FILTER)(filter|minFilter|magFilter|mipFilter);
				sd.AddressU = s_textureAddress[(_flags&BGFX_TEXTURE_U_MASK)>>BGFX_TEXTURE_U_SHIFT];
				sd.AddressV = s_textureAddress[(_flags&BGFX_TEXTURE_V_MASK)>>BGFX_TEXTURE_V_SHIFT];
				sd.AddressW = s_textureAddress[(_flags&BGFX_TEXTURE_W_MASK)>>BGFX_TEXTURE_W_SHIFT];
				sd.MipLODBias = 0.0f;
				sd.MaxAnisotropy = 1;
				sd.ComparisonFunc = 0 == cmpFunc ? D3D11_COMPARISON_NEVER : s_cmpFunc[cmpFunc];
				sd.BorderColor[0] = 0.0f;
				sd.BorderColor[1] = 0.0f;
				sd.BorderColor[2] = 0.0f;
				sd.BorderColor[3] = 0.0f;
				sd.MinLOD = 0;
				sd.MaxLOD = D3D11_FLOAT32_MAX;

				m_device->CreateSamplerState(&sd, &sampler);
				DX_CHECK_REFCOUNT(sampler, 1);

				m_samplerStateCache.add(_flags, sampler);
			}

			return sampler;
		}

		void commitTextureStage()
		{
			m_deviceCtx->PSSetShaderResources(0, BGFX_CONFIG_MAX_TEXTURE_SAMPLERS, m_textureStage.m_srv);
			m_deviceCtx->PSSetSamplers(0, BGFX_CONFIG_MAX_TEXTURE_SAMPLERS, m_textureStage.m_sampler);
		}

		void invalidateTextureStage()
		{
			m_textureStage.clear();
			commitTextureStage();
		}

		void capturePostReset()
		{
			if (m_flags&BGFX_RESET_CAPTURE)
			{
				ID3D11Texture2D* backBuffer;
				DX_CHECK(m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer) );

				D3D11_TEXTURE2D_DESC backBufferDesc;
				backBuffer->GetDesc(&backBufferDesc);

				D3D11_TEXTURE2D_DESC desc;
				memcpy(&desc, &backBufferDesc, sizeof(desc) );
				desc.SampleDesc.Count = 1;
				desc.SampleDesc.Quality = 0;
				desc.Usage = D3D11_USAGE_STAGING;
				desc.BindFlags = 0;
				desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

				HRESULT hr = m_device->CreateTexture2D(&desc, NULL, &m_captureTexture);
				if (SUCCEEDED(hr) )
				{
					if (backBufferDesc.SampleDesc.Count != 1)
					{
						desc.Usage = D3D11_USAGE_DEFAULT;
						desc.CPUAccessFlags = 0;
						m_device->CreateTexture2D(&desc, NULL, &m_captureResolve);
					}

					g_callback->captureBegin(backBufferDesc.Width, backBufferDesc.Height, backBufferDesc.Width*4, TextureFormat::BGRA8, false);
				}

				DX_RELEASE(backBuffer, 0);
			}
		}

		void capturePreReset()
		{
			if (NULL != m_captureTexture)
			{
				g_callback->captureEnd();
			}

			DX_RELEASE(m_captureResolve, 0);
			DX_RELEASE(m_captureTexture, 0);
		}

		void capture()
		{
			if (NULL != m_captureTexture)
			{
				ID3D11Texture2D* backBuffer;
				DX_CHECK(m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer) );

				DXGI_MODE_DESC& desc = m_scd.BufferDesc;

				if (NULL == m_captureResolve)
				{
					m_deviceCtx->CopyResource(m_captureTexture, backBuffer);
				}
				else
				{
					m_deviceCtx->ResolveSubresource(m_captureResolve, 0, backBuffer, 0, desc.Format);
					m_deviceCtx->CopyResource(m_captureTexture, m_captureResolve);
				}

				D3D11_MAPPED_SUBRESOURCE mapped;
				DX_CHECK(m_deviceCtx->Map(m_captureTexture, 0, D3D11_MAP_READ, 0, &mapped) );

				g_callback->captureFrame(mapped.pData, desc.Height*mapped.RowPitch);

				m_deviceCtx->Unmap(m_captureTexture, 0);

				DX_RELEASE(backBuffer, 0);
			}
		}

		void commit(ConstantBuffer& _constantBuffer)
		{
			_constantBuffer.reset();

			for (;;)
			{
				uint32_t opcode = _constantBuffer.read();

				if (UniformType::End == opcode)
				{
					break;
				}

				UniformType::Enum type;
				uint16_t loc;
				uint16_t num;
				uint16_t copy;
				ConstantBuffer::decodeOpcode(opcode, type, loc, num, copy);

				const char* data;
				if (copy)
				{
					data = _constantBuffer.read(g_uniformTypeSize[type]*num);
				}
				else
				{
					UniformHandle handle;
					memcpy(&handle, _constantBuffer.read(sizeof(UniformHandle) ), sizeof(UniformHandle) );
					data = (const char*)m_uniforms[handle.idx];
				}

#define CASE_IMPLEMENT_UNIFORM(_uniform, _dxsuffix, _type) \
		case UniformType::_uniform: \
		case UniformType::_uniform|BGFX_UNIFORM_FRAGMENTBIT: \
				{ \
					setShaderConstant(type, loc, data, num); \
				} \
				break;

				switch ( (int32_t)type)
				{
				case UniformType::Uniform3x3fv:
				case UniformType::Uniform3x3fv|BGFX_UNIFORM_FRAGMENTBIT: \
					 {
						 float* value = (float*)data;
						 for (uint32_t ii = 0, count = num/3; ii < count; ++ii,  loc += 3*16, value += 9)
						 {
							 Matrix4 mtx;
							 mtx.un.val[ 0] = value[0];
							 mtx.un.val[ 1] = value[1];
							 mtx.un.val[ 2] = value[2];
							 mtx.un.val[ 3] = 0.0f;
							 mtx.un.val[ 4] = value[3];
							 mtx.un.val[ 5] = value[4];
							 mtx.un.val[ 6] = value[5];
							 mtx.un.val[ 7] = 0.0f;
							 mtx.un.val[ 8] = value[6];
							 mtx.un.val[ 9] = value[7];
							 mtx.un.val[10] = value[8];
							 mtx.un.val[11] = 0.0f;
							 setShaderConstant(type, loc, &mtx.un.val[0], 3);
						 }
					}
					break;

				CASE_IMPLEMENT_UNIFORM(Uniform1i,    I, int);
				CASE_IMPLEMENT_UNIFORM(Uniform1f,    F, float);
				CASE_IMPLEMENT_UNIFORM(Uniform1iv,   I, int);
				CASE_IMPLEMENT_UNIFORM(Uniform1fv,   F, float);
				CASE_IMPLEMENT_UNIFORM(Uniform2fv,   F, float);
				CASE_IMPLEMENT_UNIFORM(Uniform3fv,   F, float);
				CASE_IMPLEMENT_UNIFORM(Uniform4fv,   F, float);
				CASE_IMPLEMENT_UNIFORM(Uniform4x4fv, F, float);

				case UniformType::End:
					break;

				default:
					BX_TRACE("%4d: INVALID 0x%08x, t %d, l %d, n %d, c %d", _constantBuffer.getPos(), opcode, type, loc, num, copy);
					break;
				}

#undef CASE_IMPLEMENT_UNIFORM

			}
		}

		void clearQuad(ClearQuad& _clearQuad, const Rect& _rect, const Clear& _clear, const float _palette[][4])
		{
			uint32_t width  = m_scd.BufferDesc.Width;
			uint32_t height = m_scd.BufferDesc.Height;

			if (0      == _rect.m_x
			&&  0      == _rect.m_y
			&&  width  == _rect.m_width
			&&  height == _rect.m_height)
			{
				clear(_clear, _palette);
			}
			else
			{
				ID3D11DeviceContext* deviceCtx = m_deviceCtx;

				uint64_t state = 0;
				state |= _clear.m_flags & BGFX_CLEAR_COLOR_BIT ? BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE : 0;
				state |= _clear.m_flags & BGFX_CLEAR_DEPTH_BIT ? BGFX_STATE_DEPTH_TEST_ALWAYS|BGFX_STATE_DEPTH_WRITE : 0;

				uint64_t stencil = 0;
				stencil |= _clear.m_flags & BGFX_CLEAR_STENCIL_BIT ? 0
					| BGFX_STENCIL_TEST_ALWAYS
					| BGFX_STENCIL_FUNC_REF(_clear.m_stencil)
					| BGFX_STENCIL_FUNC_RMASK(0xff)
					| BGFX_STENCIL_OP_FAIL_S_REPLACE
					| BGFX_STENCIL_OP_FAIL_Z_REPLACE
					| BGFX_STENCIL_OP_PASS_Z_REPLACE
					: 0
					;

				setBlendState(state);
				setDepthStencilState(state, stencil);
				setRasterizerState(state);

				uint32_t numMrt = 1;
				FrameBufferHandle fbh = m_fbh;
				if (isValid(fbh) )
				{
					const FrameBufferD3D11& fb = m_frameBuffers[fbh.idx];
					numMrt = bx::uint32_max(1, fb.m_num);
				}

				ProgramD3D11& program = m_program[_clearQuad.m_program[numMrt-1].idx];
				m_currentProgram = &program;
				deviceCtx->VSSetShader(program.m_vsh->m_vertexShader, NULL, 0);
				deviceCtx->VSSetConstantBuffers(0, 0, NULL);
				if (NULL != m_currentColor)
				{
					const ShaderD3D11* fsh = program.m_fsh;
					deviceCtx->PSSetShader(fsh->m_pixelShader, NULL, 0);
					deviceCtx->PSSetConstantBuffers(0, 1, &fsh->m_buffer);

					if (BGFX_CLEAR_COLOR_USE_PALETTE_BIT & _clear.m_flags)
					{
						float mrtClear[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS][4];
						for (uint32_t ii = 0; ii < numMrt; ++ii)
						{
							uint8_t index = (uint8_t)bx::uint32_min(BGFX_CONFIG_MAX_CLEAR_COLOR_PALETTE-1, _clear.m_index[ii]);
							memcpy(mrtClear[ii], _palette[index], 16);
						}

						deviceCtx->UpdateSubresource(fsh->m_buffer, 0, 0, mrtClear, 0, 0);
					}
					else
					{
						float rgba[4] =
						{
							_clear.m_index[0]*1.0f/255.0f,
							_clear.m_index[1]*1.0f/255.0f,
							_clear.m_index[2]*1.0f/255.0f,
							_clear.m_index[3]*1.0f/255.0f,
						};
						deviceCtx->UpdateSubresource(fsh->m_buffer, 0, 0, rgba, 0, 0);
					}
				}
				else
				{
					deviceCtx->PSSetShader(NULL, NULL, 0);
				}

				VertexBufferD3D11& vb = m_vertexBuffers[_clearQuad.m_vb->handle.idx];
				const VertexDecl& vertexDecl = m_vertexDecls[_clearQuad.m_vb->decl.idx];
				const uint32_t stride = vertexDecl.m_stride;
				const uint32_t offset = 0;

				{
					struct Vertex
					{
						float m_x;
						float m_y;
						float m_z;
					};
					
					Vertex* vertex = (Vertex*)_clearQuad.m_vb->data;
					BX_CHECK(stride == sizeof(Vertex), "Stride/Vertex mismatch (stride %d, sizeof(Vertex) %d)", stride, sizeof(Vertex) );

					const float depth = _clear.m_depth;

					vertex->m_x = -1.0f;
					vertex->m_y = -1.0f;
					vertex->m_z = depth;
					vertex++;
					vertex->m_x =  1.0f;
					vertex->m_y = -1.0f;
					vertex->m_z = depth;
					vertex++;
					vertex->m_x = -1.0f;
					vertex->m_y =  1.0f;
					vertex->m_z = depth;
					vertex++;
					vertex->m_x =  1.0f;
					vertex->m_y =  1.0f;
					vertex->m_z = depth;
				}

				m_vertexBuffers[_clearQuad.m_vb->handle.idx].update(0, 4*_clearQuad.m_decl.m_stride, _clearQuad.m_vb->data);
				deviceCtx->IASetVertexBuffers(0, 1, &vb.m_ptr, &stride, &offset);
				setInputLayout(vertexDecl, program, 0);

				deviceCtx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
				deviceCtx->Draw(4, 0);
			}
		}

#if USE_D3D11_DYNAMIC_LIB
		void* m_d3d9dll;
		void* m_d3d11dll;
		void* m_dxgidll;
#endif // USE_D3D11_DYNAMIC_LIB

		void* m_renderdocdll;

		D3D_DRIVER_TYPE m_driverType;
		IDXGIAdapter* m_adapter;
		DXGI_ADAPTER_DESC m_adapterDesc;
		IDXGIFactory* m_factory;

		IDXGISwapChain* m_swapChain;
		uint16_t m_lost;
		uint16_t m_numWindows;
		FrameBufferHandle m_windows[BGFX_CONFIG_MAX_FRAME_BUFFERS];

		ID3D11Device* m_device;
		ID3D11DeviceContext* m_deviceCtx;
		ID3D11RenderTargetView* m_backBufferColor;
		ID3D11DepthStencilView* m_backBufferDepthStencil;
		ID3D11RenderTargetView* m_currentColor;
		ID3D11DepthStencilView* m_currentDepthStencil;

		ID3D11Texture2D* m_captureTexture;
		ID3D11Texture2D* m_captureResolve;

		Resolution m_resolution;
		bool m_wireframe;

		DXGI_SWAP_CHAIN_DESC m_scd;
		uint32_t m_flags;

		IndexBufferD3D11 m_indexBuffers[BGFX_CONFIG_MAX_INDEX_BUFFERS];
		VertexBufferD3D11 m_vertexBuffers[BGFX_CONFIG_MAX_VERTEX_BUFFERS];
		ShaderD3D11 m_shaders[BGFX_CONFIG_MAX_SHADERS];
		ProgramD3D11 m_program[BGFX_CONFIG_MAX_PROGRAMS];
		TextureD3D11 m_textures[BGFX_CONFIG_MAX_TEXTURES];
		VertexDecl m_vertexDecls[BGFX_CONFIG_MAX_VERTEX_DECLS];
		FrameBufferD3D11 m_frameBuffers[BGFX_CONFIG_MAX_FRAME_BUFFERS];
		void* m_uniforms[BGFX_CONFIG_MAX_UNIFORMS];
		Matrix4 m_predefinedUniforms[PredefinedUniform::Count];
		UniformRegistry m_uniformReg;
		
		StateCacheT<ID3D11BlendState> m_blendStateCache;
		StateCacheT<ID3D11DepthStencilState> m_depthStencilStateCache;
		StateCacheT<ID3D11InputLayout> m_inputLayoutCache;
		StateCacheT<ID3D11RasterizerState> m_rasterizerStateCache;
		StateCacheT<ID3D11SamplerState> m_samplerStateCache;

		TextVideoMem m_textVideoMem;

		TextureStage m_textureStage;

		ProgramD3D11* m_currentProgram;

		uint8_t m_vsScratch[64<<10];
		uint8_t m_fsScratch[64<<10];

		uint32_t m_vsChanges;
		uint32_t m_fsChanges;

		FrameBufferHandle m_fbh;
		bool m_rtMsaa;
	};

	static RendererContextD3D11* s_renderD3D11;

	RendererContextI* rendererCreateD3D11()
	{
		s_renderD3D11 = BX_NEW(g_allocator, RendererContextD3D11);
		s_renderD3D11->init();
		return s_renderD3D11;
	}

	void rendererDestroyD3D11()
	{
		s_renderD3D11->shutdown();
		BX_DELETE(g_allocator, s_renderD3D11);
		s_renderD3D11 = NULL;
	}

	void IndexBufferD3D11::create(uint32_t _size, void* _data)
	{
		m_size = _size;
		m_dynamic = NULL == _data;

		D3D11_BUFFER_DESC desc;
		desc.ByteWidth = _size;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;

		if (m_dynamic)
		{
			desc.Usage = D3D11_USAGE_DYNAMIC;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

			DX_CHECK(s_renderD3D11->m_device->CreateBuffer(&desc
				, NULL
				, &m_ptr
				) );
		}
		else
		{
			desc.Usage = D3D11_USAGE_IMMUTABLE;
			desc.CPUAccessFlags = 0;

			D3D11_SUBRESOURCE_DATA srd;
			srd.pSysMem = _data;
			srd.SysMemPitch = 0;
			srd.SysMemSlicePitch = 0;

			DX_CHECK(s_renderD3D11->m_device->CreateBuffer(&desc
				, &srd
				, &m_ptr
				) );
		}
	}

	void IndexBufferD3D11::update(uint32_t _offset, uint32_t _size, void* _data)
	{
		ID3D11DeviceContext* deviceCtx = s_renderD3D11->m_deviceCtx;
		BX_CHECK(m_dynamic, "Must be dynamic!");

		D3D11_MAPPED_SUBRESOURCE mapped;
		D3D11_MAP type = m_dynamic && 0 == _offset && m_size == _size ? D3D11_MAP_WRITE_DISCARD : D3D11_MAP_WRITE_NO_OVERWRITE;
		DX_CHECK(deviceCtx->Map(m_ptr, 0, type, 0, &mapped) );
		memcpy( (uint8_t*)mapped.pData + _offset, _data, _size);
		deviceCtx->Unmap(m_ptr, 0);
	}

	void VertexBufferD3D11::create(uint32_t _size, void* _data, VertexDeclHandle _declHandle)
	{
		m_size = _size;
		m_decl = _declHandle;
		m_dynamic = NULL == _data;

		D3D11_BUFFER_DESC desc;
		desc.ByteWidth = _size;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.MiscFlags = 0;

		if (m_dynamic)
		{
			desc.Usage = D3D11_USAGE_DYNAMIC;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			desc.StructureByteStride = 0;

			DX_CHECK(s_renderD3D11->m_device->CreateBuffer(&desc
				, NULL
				, &m_ptr
				) );
		}
		else
		{
			desc.Usage = D3D11_USAGE_IMMUTABLE;
			desc.CPUAccessFlags = 0;
			desc.StructureByteStride = 0;

			D3D11_SUBRESOURCE_DATA srd;
			srd.pSysMem = _data;
			srd.SysMemPitch = 0;
			srd.SysMemSlicePitch = 0;

			DX_CHECK(s_renderD3D11->m_device->CreateBuffer(&desc
				, &srd
				, &m_ptr
				) );
		}
	}

	void VertexBufferD3D11::update(uint32_t _offset, uint32_t _size, void* _data, bool _discard)
	{
		ID3D11DeviceContext* deviceCtx = s_renderD3D11->m_deviceCtx;
		BX_CHECK(m_dynamic, "Must be dynamic!");

		D3D11_MAPPED_SUBRESOURCE mapped;
		D3D11_MAP type = m_dynamic && ( (0 == _offset && m_size == _size) || _discard) ? D3D11_MAP_WRITE_DISCARD : D3D11_MAP_WRITE_NO_OVERWRITE;
		DX_CHECK(deviceCtx->Map(m_ptr, 0, type, 0, &mapped) );
		memcpy( (uint8_t*)mapped.pData + _offset, _data, _size);
		deviceCtx->Unmap(m_ptr, 0);
	}

	void ShaderD3D11::create(const Memory* _mem)
	{
		bx::MemoryReader reader(_mem->data, _mem->size);

		uint32_t magic;
		bx::read(&reader, magic);

		switch (magic)
		{
		case BGFX_CHUNK_MAGIC_CSH:
		case BGFX_CHUNK_MAGIC_FSH:
		case BGFX_CHUNK_MAGIC_VSH:
			break;

		default:
			BGFX_FATAL(false, Fatal::InvalidShader, "Unknown shader format %x.", magic);
			break;
		}

		bool fragment = BGFX_CHUNK_MAGIC_FSH == magic;

		uint32_t iohash;
		bx::read(&reader, iohash);

		uint16_t count;
		bx::read(&reader, count);

		m_numPredefined = 0;
		m_numUniforms = count;

		BX_TRACE("%s Shader consts %d"
			, BGFX_CHUNK_MAGIC_FSH == magic ? "Fragment" : BGFX_CHUNK_MAGIC_VSH == magic ? "Vertex" : "Compute"
			, count
			);

		uint8_t fragmentBit = fragment ? BGFX_UNIFORM_FRAGMENTBIT : 0;

		if (0 < count)
		{
			for (uint32_t ii = 0; ii < count; ++ii)
			{
				uint8_t nameSize;
				bx::read(&reader, nameSize);

				char name[256];
				bx::read(&reader, &name, nameSize);
				name[nameSize] = '\0';

				uint8_t type;
				bx::read(&reader, type);

				uint8_t num;
				bx::read(&reader, num);

				uint16_t regIndex;
				bx::read(&reader, regIndex);

				uint16_t regCount;
				bx::read(&reader, regCount);

				const char* kind = "invalid";

				PredefinedUniform::Enum predefined = nameToPredefinedUniformEnum(name);
				if (PredefinedUniform::Count != predefined)
				{
					kind = "predefined";
					m_predefined[m_numPredefined].m_loc   = regIndex;
					m_predefined[m_numPredefined].m_count = regCount;
					m_predefined[m_numPredefined].m_type  = predefined|fragmentBit;
					m_numPredefined++;
				}
				else
				{
					const UniformInfo* info = s_renderD3D11->m_uniformReg.find(name);

					if (NULL != info)
					{
						if (NULL == m_constantBuffer)
						{
							m_constantBuffer = ConstantBuffer::create(1024);
						}

						kind = "user";
						m_constantBuffer->writeUniformHandle( (UniformType::Enum)(type|fragmentBit), regIndex, info->m_handle, regCount);
					}
				}

				BX_TRACE("\t%s: %s (%s), num %2d, r.index %3d, r.count %2d"
					, kind
					, name
					, getUniformTypeName(UniformType::Enum(type&~BGFX_UNIFORM_FRAGMENTBIT) )
					, num
					, regIndex
					, regCount
					);
				BX_UNUSED(kind);
			}

			if (NULL != m_constantBuffer)
			{
				m_constantBuffer->finish();
			}
		}

		uint16_t shaderSize;
		bx::read(&reader, shaderSize);

		const DWORD* code = (const DWORD*)reader.getDataPtr();
		bx::skip(&reader, shaderSize+1);

		if (BGFX_CHUNK_MAGIC_FSH == magic)
		{
			DX_CHECK(s_renderD3D11->m_device->CreatePixelShader(code, shaderSize, NULL, &m_pixelShader) );
			BGFX_FATAL(NULL != m_ptr, bgfx::Fatal::InvalidShader, "Failed to create fragment shader.");
		}
		else if (BGFX_CHUNK_MAGIC_VSH == magic)
		{
			m_hash = bx::hashMurmur2A(code, shaderSize);
			m_code = copy(code, shaderSize);

			DX_CHECK(s_renderD3D11->m_device->CreateVertexShader(code, shaderSize, NULL, &m_vertexShader) );
			BGFX_FATAL(NULL != m_ptr, bgfx::Fatal::InvalidShader, "Failed to create vertex shader.");
		}
		else
		{
			DX_CHECK(s_renderD3D11->m_device->CreateComputeShader(code, shaderSize, NULL, &m_computeShader) );
			BGFX_FATAL(NULL != m_ptr, bgfx::Fatal::InvalidShader, "Failed to create compute shader.");
		}

		uint8_t numAttrs;
		bx::read(&reader, numAttrs);

		memset(m_attrMask, 0, sizeof(m_attrMask));

		for (uint32_t ii = 0; ii < numAttrs; ++ii)
		{
			uint16_t id;
			bx::read(&reader, id);

			Attrib::Enum attr = idToAttrib(id);

			if (Attrib::Count != attr)
			{
				m_attrMask[attr] = 0xff;
			}
		}

		uint16_t size;
		bx::read(&reader, size);

		if (0 < size)
		{
			D3D11_BUFFER_DESC desc;
			desc.ByteWidth = size;
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			desc.CPUAccessFlags = 0;
			desc.MiscFlags = 0;
			desc.StructureByteStride = 0;
			DX_CHECK(s_renderD3D11->m_device->CreateBuffer(&desc, NULL, &m_buffer) );
		}
	}

	void TextureD3D11::create(const Memory* _mem, uint32_t _flags, uint8_t _skip)
	{
		m_sampler = s_renderD3D11->getSamplerState(_flags);

		ImageContainer imageContainer;

		if (imageParse(imageContainer, _mem->data, _mem->size) )
		{
			uint8_t numMips = imageContainer.m_numMips;
			const uint32_t startLod = bx::uint32_min(_skip, numMips-1);
			numMips -= startLod;
			const ImageBlockInfo& blockInfo = getBlockInfo(TextureFormat::Enum(imageContainer.m_format) );
			const uint32_t textureWidth  = bx::uint32_max(blockInfo.blockWidth,  imageContainer.m_width >>startLod);
			const uint32_t textureHeight = bx::uint32_max(blockInfo.blockHeight, imageContainer.m_height>>startLod);

			m_flags = _flags;
			m_requestedFormat = (uint8_t)imageContainer.m_format;
			m_textureFormat   = (uint8_t)imageContainer.m_format;

			const TextureFormatInfo& tfi = s_textureFormat[m_requestedFormat];
			const bool convert = DXGI_FORMAT_UNKNOWN == tfi.m_fmt;

			uint8_t bpp = getBitsPerPixel(TextureFormat::Enum(m_textureFormat) );
			if (convert)
			{
				m_textureFormat = (uint8_t)TextureFormat::BGRA8;
				bpp = 32;
			}

			if (imageContainer.m_cubeMap)
			{
				m_type = TextureCube;
			}
			else if (imageContainer.m_depth > 1)
			{
				m_type = Texture3D;
			}
			else
			{
				m_type = Texture2D;
			}

			m_numMips = numMips;

			uint32_t numSrd = numMips*(imageContainer.m_cubeMap ? 6 : 1);
			D3D11_SUBRESOURCE_DATA* srd = (D3D11_SUBRESOURCE_DATA*)alloca(numSrd*sizeof(D3D11_SUBRESOURCE_DATA) );

			uint32_t kk = 0;

			const bool compressed = isCompressed(TextureFormat::Enum(m_textureFormat) );
			const bool swizzle    = TextureFormat::BGRA8 == m_textureFormat && 0 != (m_flags&BGFX_TEXTURE_COMPUTE_WRITE);

			BX_TRACE("Texture %3d: %s (requested: %s), %dx%d%s%s%s."
				, this - s_renderD3D11->m_textures
				, getName( (TextureFormat::Enum)m_textureFormat)
				, getName( (TextureFormat::Enum)m_requestedFormat)
				, textureWidth
				, textureHeight
				, imageContainer.m_cubeMap ? "x6" : ""
				, 0 != (m_flags&BGFX_TEXTURE_RT_MASK) ? " (render target)" : ""
				, swizzle ? " (swizzle BGRA8 -> RGBA8)" : ""
				);

			for (uint8_t side = 0, numSides = imageContainer.m_cubeMap ? 6 : 1; side < numSides; ++side)
			{
				uint32_t width  = textureWidth;
				uint32_t height = textureHeight;
				uint32_t depth  = imageContainer.m_depth;

				for (uint32_t lod = 0, num = numMips; lod < num; ++lod)
				{
					width  = bx::uint32_max(1, width);
					height = bx::uint32_max(1, height);
					depth  = bx::uint32_max(1, depth);

					ImageMip mip;
					if (imageGetRawData(imageContainer, side, lod+startLod, _mem->data, _mem->size, mip) )
					{
						srd[kk].pSysMem = mip.m_data;

						if (convert)
						{
							uint32_t srcpitch = mip.m_width*bpp/8;
							uint8_t* temp = (uint8_t*)BX_ALLOC(g_allocator, mip.m_width*mip.m_height*bpp/8);
							imageDecodeToBgra8(temp, mip.m_data, mip.m_width, mip.m_height, srcpitch, mip.m_format);

							srd[kk].pSysMem = temp;
							srd[kk].SysMemPitch = srcpitch;
						}
						else if (compressed)
						{
							srd[kk].SysMemPitch      = (mip.m_width /blockInfo.blockWidth )*mip.m_blockSize;
							srd[kk].SysMemSlicePitch = (mip.m_height/blockInfo.blockHeight)*srd[kk].SysMemPitch;
						}
						else
						{
							srd[kk].SysMemPitch = mip.m_width*mip.m_bpp/8;
						}

 						if (swizzle)
 						{
// 							imageSwizzleBgra8(width, height, mip.m_width*4, data, temp);
 						}

						srd[kk].SysMemSlicePitch = mip.m_height*srd[kk].SysMemPitch;
						++kk;
					}

					width  >>= 1;
					height >>= 1;
					depth  >>= 1;
				}
			}

			const bool bufferOnly   = 0 != (m_flags&BGFX_TEXTURE_RT_BUFFER_ONLY);
			const bool computeWrite = 0 != (m_flags&BGFX_TEXTURE_COMPUTE_WRITE);
			const bool renderTarget = 0 != (m_flags&BGFX_TEXTURE_RT_MASK);
			const uint32_t msaaQuality = bx::uint32_satsub( (m_flags&BGFX_TEXTURE_RT_MSAA_MASK)>>BGFX_TEXTURE_RT_MSAA_SHIFT, 1);
			const DXGI_SAMPLE_DESC& msaa = s_msaa[msaaQuality];

			D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
			memset(&srvd, 0, sizeof(srvd) );
			srvd.Format = s_textureFormat[m_textureFormat].m_fmtSrv;
			DXGI_FORMAT format = s_textureFormat[m_textureFormat].m_fmt;

			if (swizzle)
			{
				format      = DXGI_FORMAT_R8G8B8A8_UNORM;
				srvd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			}

			switch (m_type)
			{
			case Texture2D:
			case TextureCube:
				{
					D3D11_TEXTURE2D_DESC desc;
					desc.Width = textureWidth;
					desc.Height = textureHeight;
					desc.MipLevels = numMips;
					desc.Format = format;
					desc.SampleDesc = msaa;
					desc.Usage = kk == 0 ? D3D11_USAGE_DEFAULT : D3D11_USAGE_IMMUTABLE;
					desc.BindFlags = bufferOnly ? 0 : D3D11_BIND_SHADER_RESOURCE;
					desc.CPUAccessFlags = 0;

					if (isDepth( (TextureFormat::Enum)m_textureFormat) )
					{
						desc.BindFlags |= D3D11_BIND_DEPTH_STENCIL;
						desc.Usage = D3D11_USAGE_DEFAULT;
					}
					else if (renderTarget)
					{
						desc.BindFlags |= D3D11_BIND_RENDER_TARGET;
						desc.Usage = D3D11_USAGE_DEFAULT;
					}

					if (computeWrite)
					{
						desc.BindFlags |= D3D11_BIND_UNORDERED_ACCESS;
						desc.Usage = D3D11_USAGE_DEFAULT;
					}

					if (imageContainer.m_cubeMap)
					{
						desc.ArraySize = 6;
						desc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
						srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
						srvd.TextureCube.MipLevels = numMips;
					}
					else
					{
						desc.ArraySize = 1;
						desc.MiscFlags = 0;
						srvd.ViewDimension = 1 < msaa.Count ? D3D11_SRV_DIMENSION_TEXTURE2DMS : D3D11_SRV_DIMENSION_TEXTURE2D;
						srvd.Texture2D.MipLevels = numMips;
					}

					DX_CHECK(s_renderD3D11->m_device->CreateTexture2D(&desc, kk == 0 ? NULL : srd, &m_texture2d) );
				}
				break;

			case Texture3D:
				{
					D3D11_TEXTURE3D_DESC desc;
					desc.Width = textureWidth;
					desc.Height = textureHeight;
					desc.Depth = imageContainer.m_depth;
					desc.MipLevels = imageContainer.m_numMips;
					desc.Format = format;
					desc.Usage = kk == 0 ? D3D11_USAGE_DEFAULT : D3D11_USAGE_IMMUTABLE;
					desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
					desc.CPUAccessFlags = 0;
					desc.MiscFlags = 0;

					if (computeWrite)
					{
						desc.BindFlags |= D3D11_BIND_UNORDERED_ACCESS;
						desc.Usage = D3D11_USAGE_DEFAULT;
					}

					srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE3D;
					srvd.Texture3D.MipLevels = numMips;

					DX_CHECK(s_renderD3D11->m_device->CreateTexture3D(&desc, kk == 0 ? NULL : srd, &m_texture3d) );
				}
				break;
			}

			if (!bufferOnly)
			{
				DX_CHECK(s_renderD3D11->m_device->CreateShaderResourceView(m_ptr, &srvd, &m_srv) );
			}

			if (computeWrite)
			{
				DX_CHECK(s_renderD3D11->m_device->CreateUnorderedAccessView(m_ptr, NULL, &m_uav) );
			}

			if (convert
			&&  0 != kk)
			{
				kk = 0;
				for (uint8_t side = 0, numSides = imageContainer.m_cubeMap ? 6 : 1; side < numSides; ++side)
				{
					for (uint32_t lod = 0, num = numMips; lod < num; ++lod)
					{
						BX_FREE(g_allocator, const_cast<void*>(srd[kk].pSysMem) );
						++kk;
					}
				}
			}
		}
	}

	void TextureD3D11::destroy()
	{
		DX_RELEASE(m_srv, 0);
		DX_RELEASE(m_uav, 0);
		DX_RELEASE(m_ptr, 0);
	}

	void TextureD3D11::update(uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem)
	{
		ID3D11DeviceContext* deviceCtx = s_renderD3D11->m_deviceCtx;

		D3D11_BOX box;
		box.left = _rect.m_x;
		box.top = _rect.m_y;
		box.right = box.left + _rect.m_width;
		box.bottom = box.top + _rect.m_height;
		box.front = _z;
		box.back = box.front + _depth;

		const uint32_t subres = _mip + (_side * m_numMips);
		const uint32_t bpp = getBitsPerPixel(TextureFormat::Enum(m_textureFormat) );
		const uint32_t rectpitch = _rect.m_width*bpp/8;
		const uint32_t srcpitch  = UINT16_MAX == _pitch ? rectpitch : _pitch;

		const bool convert = m_textureFormat != m_requestedFormat;

		uint8_t* data = _mem->data;
		uint8_t* temp = NULL;

		if (convert)
		{
			uint8_t* temp = (uint8_t*)BX_ALLOC(g_allocator, rectpitch*_rect.m_height);
			imageDecodeToBgra8(temp, data, _rect.m_width, _rect.m_height, srcpitch, m_requestedFormat);
			data = temp;
		}

		deviceCtx->UpdateSubresource(m_ptr, subres, &box, data, srcpitch, 0);

		if (NULL != temp)
		{
			BX_FREE(g_allocator, temp);
		}
	}

	void TextureD3D11::commit(uint8_t _stage, uint32_t _flags)
	{
		TextureStage& ts = s_renderD3D11->m_textureStage;
		ts.m_srv[_stage] = m_srv;
		ts.m_sampler[_stage] = 0 == (BGFX_SAMPLER_DEFAULT_FLAGS & _flags) 
			? s_renderD3D11->getSamplerState(_flags)
			: m_sampler
			;
	}

	void TextureD3D11::resolve()
	{
	}

	void FrameBufferD3D11::create(uint8_t _num, const TextureHandle* _handles)
	{
		for (uint32_t ii = 0; ii < BX_COUNTOF(m_rtv); ++ii)
		{
			m_rtv[ii] = NULL;
		}
		m_dsv       = NULL;
		m_swapChain = NULL;

		m_num = 0;
		for (uint32_t ii = 0; ii < _num; ++ii)
		{
			TextureHandle handle = _handles[ii];
			if (isValid(handle) )
			{
				const TextureD3D11& texture = s_renderD3D11->m_textures[handle.idx];
				if (isDepth( (TextureFormat::Enum)texture.m_textureFormat) )
				{
					BX_CHECK(NULL == m_dsv, "Frame buffer already has depth-stencil attached.");

					const uint32_t msaaQuality = bx::uint32_satsub( (texture.m_flags&BGFX_TEXTURE_RT_MSAA_MASK)>>BGFX_TEXTURE_RT_MSAA_SHIFT, 1);
					const DXGI_SAMPLE_DESC& msaa = s_msaa[msaaQuality];

					D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
					dsvDesc.Format = s_textureFormat[texture.m_textureFormat].m_fmtDsv;
					dsvDesc.ViewDimension = 1 < msaa.Count ? D3D11_DSV_DIMENSION_TEXTURE2DMS : D3D11_DSV_DIMENSION_TEXTURE2D;
					dsvDesc.Flags = 0;
					dsvDesc.Texture2D.MipSlice = 0;
					DX_CHECK(s_renderD3D11->m_device->CreateDepthStencilView(texture.m_ptr, &dsvDesc, &m_dsv) );
				}
				else
				{
					DX_CHECK(s_renderD3D11->m_device->CreateRenderTargetView(texture.m_ptr, NULL, &m_rtv[m_num]) );
					DX_CHECK(s_renderD3D11->m_device->CreateShaderResourceView(texture.m_ptr, NULL, &m_srv[m_num]) );
					m_num++;
				}
			}
		}
	}

	void FrameBufferD3D11::create(uint16_t _denseIdx, void* _nwh, uint32_t _width, uint32_t _height, TextureFormat::Enum _depthFormat)
	{
		BX_UNUSED(_depthFormat);

		DXGI_SWAP_CHAIN_DESC scd;
		memcpy(&scd, &s_renderD3D11->m_scd, sizeof(DXGI_SWAP_CHAIN_DESC) );
		scd.BufferDesc.Width  = _width;
		scd.BufferDesc.Height = _height;
		scd.OutputWindow = (HWND)_nwh;

		HRESULT hr;
		hr = s_renderD3D11->m_factory->CreateSwapChain(s_renderD3D11->m_device
			, &scd
			, &m_swapChain
			);
		BGFX_FATAL(SUCCEEDED(hr), Fatal::UnableToInitialize, "Failed to create swap chain.");

		ID3D11Resource* ptr;
		DX_CHECK(m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&ptr) );
		DX_CHECK(s_renderD3D11->m_device->CreateRenderTargetView(ptr, NULL, &m_rtv[0]) );
		DX_RELEASE(ptr, 0);
		m_srv[0]   = NULL;
		m_dsv      = NULL;
		m_denseIdx = _denseIdx;
		m_num      = 1;
	}

	uint16_t FrameBufferD3D11::destroy()
	{
		for (uint32_t ii = 0, num = m_num; ii < num; ++ii)
		{
			DX_RELEASE(m_srv[ii], 0);
			DX_RELEASE(m_rtv[ii], 0);
		}

		DX_RELEASE(m_dsv, 0);
		DX_RELEASE(m_swapChain, 0);

		m_num = 0;

		uint16_t denseIdx = m_denseIdx;
		m_denseIdx = UINT16_MAX;
		
		return denseIdx;
	}

	void FrameBufferD3D11::resolve()
	{
	}

	void FrameBufferD3D11::clear(const Clear& _clear, const float _palette[][4])
	{
		ID3D11DeviceContext* deviceCtx = s_renderD3D11->m_deviceCtx;

		if (BGFX_CLEAR_COLOR_BIT & _clear.m_flags)
		{
			if (BGFX_CLEAR_COLOR_USE_PALETTE_BIT & _clear.m_flags)
			{
				for (uint32_t ii = 0, num = m_num; ii < num; ++ii)
				{
					uint8_t index = _clear.m_index[ii];
					if (NULL != m_rtv[ii]
					&&  UINT8_MAX != index)
					{
						deviceCtx->ClearRenderTargetView(m_rtv[ii], _palette[index]);
					}
				}
			}
			else
			{
				float frgba[4] =
				{ 
					_clear.m_index[0]*1.0f/255.0f,
					_clear.m_index[1]*1.0f/255.0f,
					_clear.m_index[2]*1.0f/255.0f,
					_clear.m_index[3]*1.0f/255.0f,
				};
				for (uint32_t ii = 0, num = m_num; ii < num; ++ii)
				{
					if (NULL != m_rtv[ii])
					{
						deviceCtx->ClearRenderTargetView(m_rtv[ii], frgba);
					}
				}
			}
		}

		if (NULL != m_dsv
		&& (BGFX_CLEAR_DEPTH_BIT|BGFX_CLEAR_STENCIL_BIT) & _clear.m_flags)
		{
			DWORD flags = 0;
			flags |= (_clear.m_flags & BGFX_CLEAR_DEPTH_BIT) ? D3D11_CLEAR_DEPTH : 0;
			flags |= (_clear.m_flags & BGFX_CLEAR_STENCIL_BIT) ? D3D11_CLEAR_STENCIL : 0;
			deviceCtx->ClearDepthStencilView(m_dsv, flags, _clear.m_depth, _clear.m_stencil);
		}
	}

	void RendererContextD3D11::submit(Frame* _render, ClearQuad& _clearQuad, TextVideoMemBlitter& _textVideoMemBlitter)
	{
		PIX_BEGINEVENT(D3DCOLOR_RGBA(0xff, 0x00, 0x00, 0xff), L"rendererSubmit");

		ID3D11DeviceContext* deviceCtx = m_deviceCtx;

		updateResolution(_render->m_resolution);

		int64_t elapsed = -bx::getHPCounter();
		int64_t captureElapsed = 0;

		if (0 < _render->m_iboffset)
		{
			TransientIndexBuffer* ib = _render->m_transientIb;
			m_indexBuffers[ib->handle.idx].update(0, _render->m_iboffset, ib->data);
		}

		if (0 < _render->m_vboffset)
		{
			TransientVertexBuffer* vb = _render->m_transientVb;
			m_vertexBuffers[vb->handle.idx].update(0, _render->m_vboffset, vb->data);
		}

		_render->sort();

		RenderDraw currentState;
		currentState.clear();
		currentState.m_flags = BGFX_STATE_NONE;
		currentState.m_stencil = packStencil(BGFX_STENCIL_NONE, BGFX_STENCIL_NONE);

		Matrix4 viewProj[BGFX_CONFIG_MAX_VIEWS];
		for (uint32_t ii = 0; ii < BGFX_CONFIG_MAX_VIEWS; ++ii)
		{
			bx::float4x4_mul(&viewProj[ii].un.f4x4, &_render->m_view[ii].un.f4x4, &_render->m_proj[ii].un.f4x4);
		}

		Matrix4 invView;
		Matrix4 invProj;
		Matrix4 invViewProj;
		uint8_t invViewCached = 0xff;
		uint8_t invProjCached = 0xff;
		uint8_t invViewProjCached = 0xff;

		bool wireframe = !!(_render->m_debug&BGFX_DEBUG_WIREFRAME);
		bool scissorEnabled = false;
		setDebugWireframe(wireframe);

		uint16_t programIdx = invalidHandle;
		SortKey key;
		uint8_t view = 0xff;
		FrameBufferHandle fbh = BGFX_INVALID_HANDLE;
		float alphaRef = 0.0f;

		const uint64_t pt = _render->m_debug&BGFX_DEBUG_WIREFRAME ? BGFX_STATE_PT_LINES : 0;
		uint8_t primIndex = uint8_t(pt>>BGFX_STATE_PT_SHIFT);
		PrimInfo prim = s_primInfo[primIndex];
		deviceCtx->IASetPrimitiveTopology(prim.m_type);

		bool wasCompute = false;
		bool viewHasScissor = false;
		Rect viewScissorRect;
		viewScissorRect.clear();

		uint32_t statsNumPrimsSubmitted[BX_COUNTOF(s_primInfo)] = {};
		uint32_t statsNumPrimsRendered[BX_COUNTOF(s_primInfo)] = {};
		uint32_t statsNumInstances[BX_COUNTOF(s_primInfo)] = {};
		uint32_t statsNumIndices = 0;

		if (0 == (_render->m_debug&BGFX_DEBUG_IFH) )
		{
			for (uint32_t item = 0, numItems = _render->m_num; item < numItems; ++item)
			{
				const bool isCompute = key.decode(_render->m_sortKeys[item]);
				const bool viewChanged = key.m_view != view;

				const RenderItem& renderItem = _render->m_renderItem[_render->m_sortValues[item] ];

				if (viewChanged)
				{
					PIX_ENDEVENT();
					PIX_BEGINEVENT(D3DCOLOR_RGBA(0xff, 0x00, 0x00, 0xff), s_viewNameW[key.m_view]);

					view = key.m_view;
					programIdx = invalidHandle;

					if (_render->m_fb[view].idx != fbh.idx)
					{
						fbh = _render->m_fb[view];
						setFrameBuffer(fbh);
					}

					const Rect& rect = _render->m_rect[view];
					const Rect& scissorRect = _render->m_scissor[view];
					viewHasScissor = !scissorRect.isZero();
					viewScissorRect = viewHasScissor ? scissorRect : rect;

					D3D11_VIEWPORT vp;
					vp.TopLeftX = rect.m_x;
					vp.TopLeftY = rect.m_y;
					vp.Width    = rect.m_width;
					vp.Height   = rect.m_height;
					vp.MinDepth = 0.0f;
					vp.MaxDepth = 1.0f;
					deviceCtx->RSSetViewports(1, &vp);
					Clear& clear = _render->m_clear[view];

					if (BGFX_CLEAR_NONE != clear.m_flags)
					{
						clearQuad(_clearQuad, rect, clear, _render->m_clearColor);
						prim = s_primInfo[BX_COUNTOF(s_primName)]; // Force primitive type update after clear quad.
					}
				}

				if (isCompute)
				{
					if (!wasCompute)
					{
						wasCompute = true;

						ID3D11ShaderResourceView* srv[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS] = {};
						deviceCtx->VSSetShaderResources(0, BGFX_CONFIG_MAX_TEXTURE_SAMPLERS, srv);
						deviceCtx->PSSetShaderResources(0, BGFX_CONFIG_MAX_TEXTURE_SAMPLERS, srv);

						ID3D11SamplerState* sampler[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS] = {};
						deviceCtx->VSSetSamplers(0, BGFX_CONFIG_MAX_TEXTURE_SAMPLERS, sampler);
						deviceCtx->PSSetSamplers(0, BGFX_CONFIG_MAX_TEXTURE_SAMPLERS, sampler);
					}

					const RenderCompute& compute = renderItem.compute;

					bool programChanged = false;
					bool constantsChanged = compute.m_constBegin < compute.m_constEnd;
					rendererUpdateUniforms(this, _render->m_constantBuffer, compute.m_constBegin, compute.m_constEnd);

					if (key.m_program != programIdx)
					{
						programIdx = key.m_program;

						ProgramD3D11& program = m_program[key.m_program];
						m_currentProgram = &program;

						deviceCtx->CSSetShader(program.m_vsh->m_computeShader, NULL, 0);
						deviceCtx->CSSetConstantBuffers(0, 1, &program.m_vsh->m_buffer);

						programChanged = 
							constantsChanged = true;
					}

					if (invalidHandle != programIdx)
					{
						ProgramD3D11& program = m_program[programIdx];

						if (constantsChanged)
						{
							ConstantBuffer* vcb = program.m_vsh->m_constantBuffer;
							if (NULL != vcb)
							{
								commit(*vcb);
							}
						}

						if (constantsChanged
						||  program.m_numPredefined > 0)
						{
							commitShaderConstants();
						}
					}
					BX_UNUSED(programChanged);
					ID3D11UnorderedAccessView* uav[BGFX_MAX_COMPUTE_BINDINGS] = {};
					ID3D11ShaderResourceView*  srv[BGFX_MAX_COMPUTE_BINDINGS] = {};
					ID3D11SamplerState*    sampler[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS] = {};

					for (uint32_t ii = 0; ii < BGFX_MAX_COMPUTE_BINDINGS; ++ii)
					{
						const ComputeBinding& bind = compute.m_bind[ii];
						if (invalidHandle != bind.m_idx)
						{
							switch (bind.m_type)
							{
							case ComputeBinding::Image:
								{
									const TextureD3D11& texture = m_textures[bind.m_idx];
									if (Access::Read != bind.m_access)
									{
										uav[ii] = texture.m_uav;
									}
									else
									{
										srv[ii] = texture.m_srv;
										sampler[ii] = texture.m_sampler;
									}
								}
								break;

							case ComputeBinding::Buffer:
								{
									const VertexBufferD3D11& vertexBuffer = m_vertexBuffers[bind.m_idx];
									BX_UNUSED(vertexBuffer);
								}
								break;
							}
						}
					}

					deviceCtx->CSSetUnorderedAccessViews(0, BGFX_MAX_COMPUTE_BINDINGS, uav, NULL);
					deviceCtx->CSSetShaderResources(0, BGFX_MAX_COMPUTE_BINDINGS, srv);
					deviceCtx->CSSetSamplers(0, BGFX_MAX_COMPUTE_BINDINGS, sampler);

					deviceCtx->Dispatch(compute.m_numX, compute.m_numY, compute.m_numZ);

					continue;
				}

				if (wasCompute)
				{
					wasCompute = false;

					programIdx = invalidHandle;
					m_currentProgram = NULL;

					deviceCtx->CSSetShader(NULL, NULL, 0);

					ID3D11UnorderedAccessView* uav[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS] = {};
					deviceCtx->CSSetUnorderedAccessViews(0, BGFX_CONFIG_MAX_TEXTURE_SAMPLERS, uav, NULL);

					ID3D11ShaderResourceView* srv[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS] = {};
					deviceCtx->CSSetShaderResources(0, BGFX_CONFIG_MAX_TEXTURE_SAMPLERS, srv);

					ID3D11SamplerState* samplers[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS] = {};
					m_deviceCtx->CSSetSamplers(0, BGFX_CONFIG_MAX_TEXTURE_SAMPLERS, samplers);
				}

				const RenderDraw& draw = renderItem.draw;

				const uint64_t newFlags = draw.m_flags;
				uint64_t changedFlags = currentState.m_flags ^ draw.m_flags;
				currentState.m_flags = newFlags;

				const uint64_t newStencil = draw.m_stencil;
				uint64_t changedStencil = currentState.m_stencil ^ draw.m_stencil;
				currentState.m_stencil = newStencil;

				if (viewChanged)
				{
					currentState.clear();
					currentState.m_scissor = !draw.m_scissor;
					changedFlags = BGFX_STATE_MASK;
					changedStencil = packStencil(BGFX_STENCIL_MASK, BGFX_STENCIL_MASK);
					currentState.m_flags = newFlags;
					currentState.m_stencil = newStencil;

					uint64_t newFlags = renderItem.draw.m_flags;
					setBlendState(newFlags);
					setDepthStencilState(newFlags, packStencil(BGFX_STENCIL_DEFAULT, BGFX_STENCIL_DEFAULT) );

					const uint64_t pt = newFlags&BGFX_STATE_PT_MASK;
					primIndex = uint8_t(pt>>BGFX_STATE_PT_SHIFT);
					if (prim.m_type != s_primInfo[primIndex].m_type)
					{
						prim = s_primInfo[primIndex];
						deviceCtx->IASetPrimitiveTopology(prim.m_type);
					}
				}

				uint16_t scissor = draw.m_scissor;
				if (currentState.m_scissor != scissor)
				{
					currentState.m_scissor = scissor;

					if (UINT16_MAX == scissor)
					{
						scissorEnabled = viewHasScissor;
						if (viewHasScissor)
						{
							D3D11_RECT rc;
							rc.left   = viewScissorRect.m_x;
							rc.top    = viewScissorRect.m_y;
							rc.right  = viewScissorRect.m_x + viewScissorRect.m_width;
							rc.bottom = viewScissorRect.m_y + viewScissorRect.m_height;
							deviceCtx->RSSetScissorRects(1, &rc);
						}
					}
					else
					{
						Rect scissorRect;
						scissorRect.intersect(viewScissorRect, _render->m_rectCache.m_cache[scissor]);
						scissorEnabled = true;
						D3D11_RECT rc;
						rc.left   = scissorRect.m_x;
						rc.top    = scissorRect.m_y;
						rc.right  = scissorRect.m_x + scissorRect.m_width;
						rc.bottom = scissorRect.m_y + scissorRect.m_height;
						deviceCtx->RSSetScissorRects(1, &rc);
					}

					setRasterizerState(newFlags, wireframe, scissorEnabled);
				}

				if ( (BGFX_STATE_DEPTH_WRITE|BGFX_STATE_DEPTH_TEST_MASK) & changedFlags
				|| 0 != changedStencil)
				{
					setDepthStencilState(newFlags, newStencil);
				}

				if ( (0
					 | BGFX_STATE_CULL_MASK
					 | BGFX_STATE_RGB_WRITE
					 | BGFX_STATE_ALPHA_WRITE
					 | BGFX_STATE_BLEND_MASK
					 | BGFX_STATE_BLEND_EQUATION_MASK
					 | BGFX_STATE_ALPHA_REF_MASK
					 | BGFX_STATE_PT_MASK
					 | BGFX_STATE_POINT_SIZE_MASK
					 | BGFX_STATE_MSAA
					 ) & changedFlags)
				{
					if ( (BGFX_STATE_BLEND_MASK|BGFX_STATE_BLEND_EQUATION_MASK|BGFX_STATE_ALPHA_WRITE|BGFX_STATE_RGB_WRITE) & changedFlags)
					{
						setBlendState(newFlags, draw.m_rgba);
					}

					if ( (BGFX_STATE_CULL_MASK|BGFX_STATE_MSAA) & changedFlags)
					{
						setRasterizerState(newFlags, wireframe, scissorEnabled);
					}

					if (BGFX_STATE_ALPHA_REF_MASK & changedFlags)
					{
						uint32_t ref = (newFlags&BGFX_STATE_ALPHA_REF_MASK)>>BGFX_STATE_ALPHA_REF_SHIFT;
						alphaRef = ref/255.0f;
					}

					const uint64_t pt = newFlags&BGFX_STATE_PT_MASK;
					primIndex = uint8_t(pt>>BGFX_STATE_PT_SHIFT);
					if (prim.m_type != s_primInfo[primIndex].m_type)
					{
						prim = s_primInfo[primIndex];
						deviceCtx->IASetPrimitiveTopology(prim.m_type);
					}
				}

				bool programChanged = false;
				bool constantsChanged = draw.m_constBegin < draw.m_constEnd;
				rendererUpdateUniforms(this, _render->m_constantBuffer, draw.m_constBegin, draw.m_constEnd);

				if (key.m_program != programIdx)
				{
					programIdx = key.m_program;

					if (invalidHandle == programIdx)
					{
						m_currentProgram = NULL;

						deviceCtx->VSSetShader(NULL, NULL, 0);
						deviceCtx->PSSetShader(NULL, NULL, 0);
					}
					else
					{
						ProgramD3D11& program = m_program[programIdx];
						m_currentProgram = &program;

						const ShaderD3D11* vsh = program.m_vsh;
						deviceCtx->VSSetShader(vsh->m_vertexShader, NULL, 0);
						deviceCtx->VSSetConstantBuffers(0, 1, &vsh->m_buffer);

						if (NULL != m_currentColor)
						{
							const ShaderD3D11* fsh = program.m_fsh;
							deviceCtx->PSSetShader(fsh->m_pixelShader, NULL, 0);
							deviceCtx->PSSetConstantBuffers(0, 1, &fsh->m_buffer);
						}
						else
						{
							deviceCtx->PSSetShader(NULL, NULL, 0);
						}
					}

					programChanged = 
						constantsChanged = true;
				}

				if (invalidHandle != programIdx)
				{
					ProgramD3D11& program = m_program[programIdx];

					if (constantsChanged)
					{
						ConstantBuffer* vcb = program.m_vsh->m_constantBuffer;
						if (NULL != vcb)
						{
							commit(*vcb);
						}

						ConstantBuffer* fcb = program.m_fsh->m_constantBuffer;
						if (NULL != fcb)
						{
							commit(*fcb);
						}
					}

					for (uint32_t ii = 0, num = program.m_numPredefined; ii < num; ++ii)
					{
						PredefinedUniform& predefined = program.m_predefined[ii];
						uint8_t flags = predefined.m_type&BGFX_UNIFORM_FRAGMENTBIT;
						switch (predefined.m_type&(~BGFX_UNIFORM_FRAGMENTBIT) )
						{
						case PredefinedUniform::ViewRect:
							{
								float rect[4];
								rect[0] = _render->m_rect[view].m_x;
								rect[1] = _render->m_rect[view].m_y;
								rect[2] = _render->m_rect[view].m_width;
								rect[3] = _render->m_rect[view].m_height;

								setShaderConstant(flags, predefined.m_loc, &rect[0], 1);
							}
							break;

						case PredefinedUniform::ViewTexel:
							{
								float rect[4];
								rect[0] = 1.0f/float(_render->m_rect[view].m_width);
								rect[1] = 1.0f/float(_render->m_rect[view].m_height);

								setShaderConstant(flags, predefined.m_loc, &rect[0], 1);
							}
							break;

						case PredefinedUniform::View:
							{
								setShaderConstant(flags, predefined.m_loc, _render->m_view[view].un.val, bx::uint32_min(4, predefined.m_count) );
							}
							break;

						case PredefinedUniform::InvView:
							{
								if (view != invViewCached)
								{
									invViewCached = view;
									bx::float4x4_inverse(&invView.un.f4x4, &_render->m_view[view].un.f4x4);
								}

								setShaderConstant(flags, predefined.m_loc, invView.un.val, bx::uint32_min(4, predefined.m_count) );
							}
							break;

						case PredefinedUniform::Proj:
							{
								setShaderConstant(flags, predefined.m_loc, _render->m_proj[view].un.val, bx::uint32_min(4, predefined.m_count) );
							}
							break;

						case PredefinedUniform::InvProj:
							{
								if (view != invProjCached)
								{
									invProjCached = view;
									bx::float4x4_inverse(&invProj.un.f4x4, &_render->m_proj[view].un.f4x4);
								}

								setShaderConstant(flags, predefined.m_loc, invProj.un.val, bx::uint32_min(4, predefined.m_count) );
							}
							break;

						case PredefinedUniform::ViewProj:
							{
								setShaderConstant(flags, predefined.m_loc, viewProj[view].un.val, bx::uint32_min(4, predefined.m_count) );
							}
							break;

						case PredefinedUniform::InvViewProj:
							{
								if (view != invViewProjCached)
								{
									invViewProjCached = view;
									bx::float4x4_inverse(&invViewProj.un.f4x4, &viewProj[view].un.f4x4);
								}

								setShaderConstant(flags, predefined.m_loc, invViewProj.un.val, bx::uint32_min(4, predefined.m_count) );
							}
							break;

						case PredefinedUniform::Model:
							{
								const Matrix4& model = _render->m_matrixCache.m_cache[draw.m_matrix];
								setShaderConstant(flags, predefined.m_loc, model.un.val, bx::uint32_min(draw.m_num*4, predefined.m_count) );
							}
							break;

						case PredefinedUniform::ModelView:
							{
								Matrix4 modelView;
								const Matrix4& model = _render->m_matrixCache.m_cache[draw.m_matrix];
								bx::float4x4_mul(&modelView.un.f4x4, &model.un.f4x4, &_render->m_view[view].un.f4x4);
								setShaderConstant(flags, predefined.m_loc, modelView.un.val, bx::uint32_min(4, predefined.m_count) );
							}
							break;

						case PredefinedUniform::ModelViewProj:
							{
								Matrix4 modelViewProj;
								const Matrix4& model = _render->m_matrixCache.m_cache[draw.m_matrix];
								bx::float4x4_mul(&modelViewProj.un.f4x4, &model.un.f4x4, &viewProj[view].un.f4x4);
								setShaderConstant(flags, predefined.m_loc, modelViewProj.un.val, bx::uint32_min(4, predefined.m_count) );
							}
							break;

						case PredefinedUniform::AlphaRef:
							{
								setShaderConstant(flags, predefined.m_loc, &alphaRef, 1);
							}
							break;

						default:
							BX_CHECK(false, "predefined %d not handled", predefined.m_type);
							break;
						}
					}

					if (constantsChanged
					||  program.m_numPredefined > 0)
					{
						commitShaderConstants();
					}
				}

				{
					uint32_t changes = 0;
					for (uint32_t stage = 0; stage < BGFX_CONFIG_MAX_TEXTURE_SAMPLERS; ++stage)
					{
						const Sampler& sampler = draw.m_sampler[stage];
						Sampler& current = currentState.m_sampler[stage];
						if (current.m_idx != sampler.m_idx
						||  current.m_flags != sampler.m_flags
						||  programChanged)
						{
							if (invalidHandle != sampler.m_idx)
							{
								TextureD3D11& texture = m_textures[sampler.m_idx];
								texture.commit(stage, sampler.m_flags);
							}
							else
							{
								m_textureStage.m_srv[stage] = NULL;
								m_textureStage.m_sampler[stage] = NULL;
							}

							++changes;
						}

						current = sampler;
					}

					if (0 < changes)
					{
						commitTextureStage();
					}
				}

				if (programChanged
				||  currentState.m_vertexBuffer.idx != draw.m_vertexBuffer.idx
				||  currentState.m_instanceDataBuffer.idx != draw.m_instanceDataBuffer.idx
				||  currentState.m_instanceDataOffset != draw.m_instanceDataOffset
				||  currentState.m_instanceDataStride != draw.m_instanceDataStride)
				{
					currentState.m_vertexBuffer = draw.m_vertexBuffer;
					currentState.m_instanceDataBuffer.idx = draw.m_instanceDataBuffer.idx;
					currentState.m_instanceDataOffset = draw.m_instanceDataOffset;
					currentState.m_instanceDataStride = draw.m_instanceDataStride;

					uint16_t handle = draw.m_vertexBuffer.idx;
					if (invalidHandle != handle)
					{
						const VertexBufferD3D11& vb = m_vertexBuffers[handle];

						uint16_t decl = !isValid(vb.m_decl) ? draw.m_vertexDecl.idx : vb.m_decl.idx;
						const VertexDecl& vertexDecl = m_vertexDecls[decl];
						uint32_t stride = vertexDecl.m_stride;
						uint32_t offset = 0;
						deviceCtx->IASetVertexBuffers(0, 1, &vb.m_ptr, &stride, &offset);

						if (isValid(draw.m_instanceDataBuffer) )
						{
 							const VertexBufferD3D11& inst = m_vertexBuffers[draw.m_instanceDataBuffer.idx];
							uint32_t instStride = draw.m_instanceDataStride;
							deviceCtx->IASetVertexBuffers(1, 1, &inst.m_ptr, &instStride, &draw.m_instanceDataOffset);
							setInputLayout(vertexDecl, m_program[programIdx], draw.m_instanceDataStride/16);
						}
						else
						{
							deviceCtx->IASetVertexBuffers(1, 0, NULL, NULL, NULL);
							setInputLayout(vertexDecl, m_program[programIdx], 0);
						}
					}
					else
					{
						deviceCtx->IASetVertexBuffers(0, 0, NULL, NULL, NULL);
					}
				}

				if (currentState.m_indexBuffer.idx != draw.m_indexBuffer.idx)
				{
					currentState.m_indexBuffer = draw.m_indexBuffer;

					uint16_t handle = draw.m_indexBuffer.idx;
					if (invalidHandle != handle)
					{
						const IndexBufferD3D11& ib = m_indexBuffers[handle];
						deviceCtx->IASetIndexBuffer(ib.m_ptr, DXGI_FORMAT_R16_UINT, 0);
					}
					else
					{
						deviceCtx->IASetIndexBuffer(NULL, DXGI_FORMAT_R16_UINT, 0);
					}
				}

				if (isValid(currentState.m_vertexBuffer) )
				{
					uint32_t numVertices = draw.m_numVertices;
					if (UINT32_MAX == numVertices)
					{
						const VertexBufferD3D11& vb = m_vertexBuffers[currentState.m_vertexBuffer.idx];
						uint16_t decl = !isValid(vb.m_decl) ? draw.m_vertexDecl.idx : vb.m_decl.idx;
						const VertexDecl& vertexDecl = m_vertexDecls[decl];
						numVertices = vb.m_size/vertexDecl.m_stride;
					}

					uint32_t numIndices = 0;
					uint32_t numPrimsSubmitted = 0;
					uint32_t numInstances = 0;
					uint32_t numPrimsRendered = 0;

					if (isValid(draw.m_indexBuffer) )
					{
						if (UINT32_MAX == draw.m_numIndices)
						{
							numIndices = m_indexBuffers[draw.m_indexBuffer.idx].m_size/2;
							numPrimsSubmitted = numIndices/prim.m_div - prim.m_sub;
							numInstances = draw.m_numInstances;
							numPrimsRendered = numPrimsSubmitted*draw.m_numInstances;

							deviceCtx->DrawIndexedInstanced(numIndices
								, draw.m_numInstances
								, 0
								, draw.m_startVertex
								, 0
								);
						}
						else if (prim.m_min <= draw.m_numIndices)
						{
							numIndices = draw.m_numIndices;
							numPrimsSubmitted = numIndices/prim.m_div - prim.m_sub;
							numInstances = draw.m_numInstances;
							numPrimsRendered = numPrimsSubmitted*draw.m_numInstances;

							deviceCtx->DrawIndexedInstanced(numIndices
								, draw.m_numInstances
								, draw.m_startIndex
								, draw.m_startVertex
								, 0
								);
						}
					}
					else
					{
						numPrimsSubmitted = numVertices/prim.m_div - prim.m_sub;
						numInstances = draw.m_numInstances;
						numPrimsRendered = numPrimsSubmitted*draw.m_numInstances;

						deviceCtx->DrawInstanced(numVertices
							, draw.m_numInstances
							, draw.m_startVertex
							, 0
							);
					}

					statsNumPrimsSubmitted[primIndex] += numPrimsSubmitted;
					statsNumPrimsRendered[primIndex]  += numPrimsRendered;
					statsNumInstances[primIndex]      += numInstances;
					statsNumIndices += numIndices;
				}
			}

			if (0 < _render->m_num)
			{
				captureElapsed = -bx::getHPCounter();
				capture();
				captureElapsed += bx::getHPCounter();
			}
		}

		int64_t now = bx::getHPCounter();
		elapsed += now;

		static int64_t last = now;
		int64_t frameTime = now - last;
		last = now;

		static int64_t min = frameTime;
		static int64_t max = frameTime;
		min = min > frameTime ? frameTime : min;
		max = max < frameTime ? frameTime : max;

		if (_render->m_debug & (BGFX_DEBUG_IFH|BGFX_DEBUG_STATS) )
		{
			PIX_BEGINEVENT(D3DCOLOR_RGBA(0x40, 0x40, 0x40, 0xff), L"debugstats");

			TextVideoMem& tvm = m_textVideoMem;

			static int64_t next = now;

			if (now >= next)
			{
				next = now + bx::getHPFrequency();
				double freq = double(bx::getHPFrequency() );
				double toMs = 1000.0/freq;

				tvm.clear();
				uint16_t pos = 0;
				tvm.printf(0, pos++, BGFX_CONFIG_DEBUG ? 0x89 : 0x8f
					, " %s / " BX_COMPILER_NAME " / " BX_CPU_NAME " / " BX_ARCH_NAME " / " BX_PLATFORM_NAME " "
					, getRendererName()
					);

				const DXGI_ADAPTER_DESC& desc = m_adapterDesc;
				char description[BX_COUNTOF(desc.Description)];
				wcstombs(description, desc.Description, BX_COUNTOF(desc.Description) );
				tvm.printf(0, pos++, 0x0f, " Device: %s", description);

				char dedicatedVideo[16];
				bx::prettify(dedicatedVideo, BX_COUNTOF(dedicatedVideo), desc.DedicatedVideoMemory);

				char dedicatedSystem[16];
				bx::prettify(dedicatedSystem, BX_COUNTOF(dedicatedSystem), desc.DedicatedSystemMemory);

				char sharedSystem[16];
				bx::prettify(sharedSystem, BX_COUNTOF(sharedSystem), desc.SharedSystemMemory);
				
				tvm.printf(0, pos++, 0x0f, " Memory: %s (video), %s (system), %s (shared)"
					, dedicatedVideo
					, dedicatedSystem
					, sharedSystem
					);

				pos = 10;
				tvm.printf(10, pos++, 0x8e, "       Frame: %7.3f, % 7.3f \x1f, % 7.3f \x1e [ms] / % 6.2f FPS "
					, double(frameTime)*toMs
					, double(min)*toMs
					, double(max)*toMs
					, freq/frameTime
					);

				const uint32_t msaa = (m_resolution.m_flags&BGFX_RESET_MSAA_MASK)>>BGFX_RESET_MSAA_SHIFT;
				tvm.printf(10, pos++, 0x8e, " Reset flags: [%c] vsync, [%c] MSAAx%d "
					, !!(m_resolution.m_flags&BGFX_RESET_VSYNC) ? '\xfe' : ' '
					, 0 != msaa ? '\xfe' : ' '
					, 1<<msaa
					);

				double elapsedCpuMs = double(elapsed)*toMs;
				tvm.printf(10, pos++, 0x8e, "  Draw calls: %4d / CPU %3.4f [ms]"
					, _render->m_num
					, elapsedCpuMs
					);
				for (uint32_t ii = 0; ii < BX_COUNTOF(s_primName); ++ii)
				{
					tvm.printf(10, pos++, 0x8e, "    %8s: %7d (#inst: %5d), submitted: %7d"
						, s_primName[ii]
						, statsNumPrimsRendered[ii]
						, statsNumInstances[ii]
						, statsNumPrimsSubmitted[ii]
						);
				}

				if (NULL != m_renderdocdll)
				{
					tvm.printf(tvm.m_width-27, 0, 0x1f, " [F11 - RenderDoc capture] ");
				}

				tvm.printf(10, pos++, 0x8e, "     Indices: %7d", statsNumIndices);
				tvm.printf(10, pos++, 0x8e, "    DVB size: %7d", _render->m_vboffset);
				tvm.printf(10, pos++, 0x8e, "    DIB size: %7d", _render->m_iboffset);

				pos++;
				tvm.printf(10, pos++, 0x8e, " State cache:                                ");
				tvm.printf(10, pos++, 0x8e, " Blend  | DepthS | Input  | Raster | Sampler ");
				tvm.printf(10, pos++, 0x8e, " %6d | %6d | %6d | %6d | %6d  "
					, m_blendStateCache.getCount()
					, m_depthStencilStateCache.getCount()
					, m_inputLayoutCache.getCount()
					, m_rasterizerStateCache.getCount()
					, m_samplerStateCache.getCount()
					);
				pos++;

				double captureMs = double(captureElapsed)*toMs;
				tvm.printf(10, pos++, 0x8e, "     Capture: %3.4f [ms]", captureMs);

				uint8_t attr[2] = { 0x89, 0x8a };
				uint8_t attrIndex = _render->m_waitSubmit < _render->m_waitRender;

				tvm.printf(10, pos++, attr[attrIndex&1], " Submit wait: %3.4f [ms]", _render->m_waitSubmit*toMs);
				tvm.printf(10, pos++, attr[(attrIndex+1)&1], " Render wait: %3.4f [ms]", _render->m_waitRender*toMs);

				min = frameTime;
				max = frameTime;
			}

			blit(this, _textVideoMemBlitter, tvm);

			PIX_ENDEVENT();
		}
		else if (_render->m_debug & BGFX_DEBUG_TEXT)
		{
			PIX_BEGINEVENT(D3DCOLOR_RGBA(0x40, 0x40, 0x40, 0xff), L"debugtext");

			blit(this, _textVideoMemBlitter, _render->m_textVideoMem);

			PIX_ENDEVENT();
		}
	}
} // namespace bgfx

#else

namespace bgfx
{
	RendererContextI* rendererCreateD3D11()
	{
		return NULL;
	}

	void rendererDestroyD3D11()
	{
	}
} // namespace bgfx

#endif // BGFX_CONFIG_RENDERER_DIRECT3D11
