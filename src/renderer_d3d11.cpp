/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "bgfx_p.h"

#if BGFX_CONFIG_RENDERER_DIRECT3D11
#	include "renderer_d3d11.h"

namespace bgfx
{
	static wchar_t s_viewNameW[BGFX_CONFIG_MAX_VIEWS][256];

	static const D3D11_PRIMITIVE_TOPOLOGY s_primType[] =
	{
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		D3D11_PRIMITIVE_TOPOLOGY_LINELIST,
		D3D11_PRIMITIVE_TOPOLOGY_POINTLIST,
	};

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
		{ D3D11_BLEND_ZERO,             D3D11_BLEND_ZERO             },
		{ D3D11_BLEND_ONE,              D3D11_BLEND_ONE              },
		{ D3D11_BLEND_SRC_COLOR,        D3D11_BLEND_SRC_ALPHA        },
		{ D3D11_BLEND_INV_SRC_COLOR,    D3D11_BLEND_INV_SRC_ALPHA    },
		{ D3D11_BLEND_SRC_ALPHA,        D3D11_BLEND_SRC_ALPHA        },
		{ D3D11_BLEND_INV_SRC_ALPHA,    D3D11_BLEND_INV_SRC_ALPHA    },
		{ D3D11_BLEND_DEST_ALPHA,       D3D11_BLEND_DEST_ALPHA       },
		{ D3D11_BLEND_INV_DEST_ALPHA,   D3D11_BLEND_INV_DEST_ALPHA   },
		{ D3D11_BLEND_DEST_COLOR,       D3D11_BLEND_DEST_ALPHA       },
		{ D3D11_BLEND_INV_DEST_COLOR,   D3D11_BLEND_INV_DEST_ALPHA   },
		{ D3D11_BLEND_SRC_ALPHA_SAT,    D3D11_BLEND_ONE              },
		{ D3D11_BLEND_BLEND_FACTOR,     D3D11_BLEND_BLEND_FACTOR     },
		{ D3D11_BLEND_INV_BLEND_FACTOR, D3D11_BLEND_INV_BLEND_FACTOR },
	};

	static const D3D11_BLEND_OP s_blendEquation[] =
	{
		D3D11_BLEND_OP_ADD,
		D3D11_BLEND_OP_SUBTRACT,
		D3D11_BLEND_OP_REV_SUBTRACT,
		D3D11_BLEND_OP_MIN,
		D3D11_BLEND_OP_MAX,
	};

	static const D3D11_COMPARISON_FUNC s_depthFunc[] =
	{
		D3D11_COMPARISON_LESS, // ignored
		D3D11_COMPARISON_LESS,
		D3D11_COMPARISON_LESS_EQUAL,
		D3D11_COMPARISON_EQUAL,
		D3D11_COMPARISON_GREATER_EQUAL,
		D3D11_COMPARISON_GREATER,
		D3D11_COMPARISON_NOT_EQUAL,
		D3D11_COMPARISON_NEVER,
		D3D11_COMPARISON_ALWAYS,
	};

	static const D3D11_COMPARISON_FUNC s_stencilFunc[] =
	{
		D3D11_COMPARISON_LESS, // ignored
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

	static DXGI_FORMAT s_colorFormat[] =
	{
		DXGI_FORMAT_UNKNOWN, // ignored
		DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_FORMAT_R10G10B10A2_UNORM,
		DXGI_FORMAT_R16G16B16A16_UNORM,
		DXGI_FORMAT_R16G16B16A16_FLOAT,
		DXGI_FORMAT_R16_FLOAT,
		DXGI_FORMAT_R32_FLOAT,
	};

	static const DXGI_FORMAT s_depthFormat[] =
	{
		DXGI_FORMAT_UNKNOWN, // ignored
		DXGI_FORMAT_D24_UNORM_S8_UINT,
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
		uint8_t m_bpp;
	};

#ifndef DXGI_FORMAT_B4G4R4A4_UNORM
// Win8 only BS
// https://blogs.msdn.com/b/chuckw/archive/2012/11/14/directx-11-1-and-windows-7.aspx?Redirected=true
// http://msdn.microsoft.com/en-us/library/windows/desktop/bb173059%28v=vs.85%29.aspx
#	define DXGI_FORMAT_B4G4R4A4_UNORM DXGI_FORMAT(115)
#endif // DXGI_FORMAT_B4G4R4A4_UNORM

	static const TextureFormatInfo s_textureFormat[TextureFormat::Count] =
	{
		{ DXGI_FORMAT_BC1_UNORM,          4  },
		{ DXGI_FORMAT_BC2_UNORM,          8  },
		{ DXGI_FORMAT_BC3_UNORM,          8  },
		{ DXGI_FORMAT_BC4_UNORM,          4  },
		{ DXGI_FORMAT_BC5_UNORM,          8  },
		{ DXGI_FORMAT_UNKNOWN,            0  },
		{ DXGI_FORMAT_R8_UNORM,           8  },
		{ DXGI_FORMAT_B8G8R8A8_UNORM,     32 },
		{ DXGI_FORMAT_B8G8R8A8_UNORM,     32 },
		{ DXGI_FORMAT_R16G16B16A16_UNORM, 64 },
		{ DXGI_FORMAT_R16G16B16A16_FLOAT, 64 },
		{ DXGI_FORMAT_B5G6R5_UNORM,       16 },
		{ DXGI_FORMAT_B4G4R4A4_UNORM,     16 },
		{ DXGI_FORMAT_B5G5R5A1_UNORM,     16 },
		{ DXGI_FORMAT_R10G10B10A2_UNORM,  32 },
	};

	static const D3D11_INPUT_ELEMENT_DESC s_attrib[Attrib::Count] =
	{
		{ "POSITION",     0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",       0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TANGENT",      0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
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

	static const DXGI_FORMAT s_attribType[AttribType::Count][4][2] =
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

		ID3D11ShaderResourceView* m_srv[BGFX_STATE_TEX_COUNT];
		ID3D11SamplerState* m_sampler[BGFX_STATE_TEX_COUNT];
	};

	static const GUID WKPDID_D3DDebugObjectName = { 0x429b8c22, 0x9188, 0x4b0c, { 0x87, 0x42, 0xac, 0xb0, 0xbf, 0x85, 0xc2, 0x00 } };

	template <typename Ty>
	static BX_NO_INLINE void setDebugObjectName(Ty* _interface, const char* _format, ...)
	{
#if BGFX_CONFIG_DEBUG_OBJECT_NAME
		char temp[2048];
		va_list argList;
		va_start(argList, _format);
		int size = uint32_min(sizeof(temp)-1, vsnprintf(temp, sizeof(temp), _format, argList) );
		va_end(argList);
		temp[size] = '\0';

		_interface->SetPrivateData(WKPDID_D3DDebugObjectName, size, temp);
#endif // BGFX_CONFIG_DEBUG_OBJECT_NAME
	}

	struct RendererContext
	{
		RendererContext()
			: m_captureTexture(NULL)
			, m_captureResolve(NULL)
			, m_wireframe(false)
			, m_vsChanges(0)
			, m_fsChanges(0)
		{
		}

		void init()
		{
			m_d3d11dll = bx::dlopen("d3d11.dll");
			BGFX_FATAL(NULL != m_d3d11dll, Fatal::UnableToInitialize, "Failed to load d3d11.dll.");

#if BGFX_CONFIG_DEBUG_PIX
			// D3D11_1.h has ID3DUserDefinedAnnotation
			// http://msdn.microsoft.com/en-us/library/windows/desktop/hh446881%28v=vs.85%29.aspx
			m_d3d9dll = bx::dlopen("d3d9.dll");
			BGFX_FATAL(NULL != m_d3d9dll, Fatal::UnableToInitialize, "Failed to load d3d9.dll.");

			m_D3DPERF_SetMarker = (D3DPERF_SetMarkerFunc)bx::dlsym(m_d3d9dll, "D3DPERF_SetMarker");
			m_D3DPERF_BeginEvent = (D3DPERF_BeginEventFunc)bx::dlsym(m_d3d9dll, "D3DPERF_BeginEvent");
			m_D3DPERF_EndEvent = (D3DPERF_EndEventFunc)bx::dlsym(m_d3d9dll, "D3DPERF_EndEvent");
			BX_CHECK(NULL != m_D3DPERF_SetMarker
				  && NULL != m_D3DPERF_BeginEvent
				  && NULL != m_D3DPERF_EndEvent
				  , "Failed to initialize PIX events."
				  );
#endif // BGFX_CONFIG_DEBUG_PIX

			PFN_D3D11_CREATE_DEVICE d3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE)bx::dlsym(m_d3d11dll, "D3D11CreateDevice");
			BGFX_FATAL(NULL != d3D11CreateDevice, Fatal::UnableToInitialize, "Function D3D11CreateDevice not found.");

			m_dxgidll = bx::dlopen("dxgi.dll");
			BGFX_FATAL(NULL != m_dxgidll, Fatal::UnableToInitialize, "Failed to load dxgi.dll.");

			PFN_CREATEDXGIFACTORY dxgiCreateDXGIFactory = (PFN_CREATEDXGIFACTORY)bx::dlsym(m_dxgidll, "CreateDXGIFactory");
			BGFX_FATAL(NULL != dxgiCreateDXGIFactory, Fatal::UnableToInitialize, "Function CreateDXGIFactory not found.");

			HRESULT hr;

			IDXGIFactory* factory;
			hr = dxgiCreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
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

#if BGFX_CONFIG_DEBUG_PERFHUD
					if (0 != strstr(description, "PerfHUD") )
					{
						m_adapter = adapter;
						m_driverType = D3D_DRIVER_TYPE_REFERENCE;
					}
#endif // BGFX_CONFIG_DEBUG_PERFHUD
				}

				DX_RELEASE(adapter, adapter == m_adapter ? 1 : 0);
			}
			DX_RELEASE(factory, NULL != m_adapter ? 1 : 0);

			D3D_FEATURE_LEVEL features[] =
			{
				D3D_FEATURE_LEVEL_11_0,
			};

			memset(&m_scd, 0, sizeof(m_scd) );
			m_scd.BufferDesc.Width = BGFX_DEFAULT_WIDTH;
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

			uint32_t flags = D3D11_CREATE_DEVICE_SINGLETHREADED
#if BGFX_CONFIG_DEBUG
				| D3D11_CREATE_DEVICE_DEBUG
#endif // BGFX_CONFIG_DEBUG
				;

			D3D_FEATURE_LEVEL featureLevel;

			hr = d3D11CreateDevice(m_adapter
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
			DX_RELEASE(device, 2);

			hr = adapter->GetDesc(&m_adapterDesc);
			BGFX_FATAL(SUCCEEDED(hr), Fatal::UnableToInitialize, "Unable to create Direct3D11 device.");

			hr = adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_factory);
			BGFX_FATAL(SUCCEEDED(hr), Fatal::UnableToInitialize, "Unable to create Direct3D11 device.");
			DX_RELEASE(adapter, 2);

			hr = m_factory->CreateSwapChain(m_device
										, &m_scd
										, &m_swapChain
										);
			BGFX_FATAL(SUCCEEDED(hr), Fatal::UnableToInitialize, "Failed to create swap chain.");

			for (uint32_t ii = 0; ii < PredefinedUniform::Count; ++ii)
			{
				m_predefinedUniforms[ii].create(UniformType::Uniform4x4fv, 1, false);
				m_uniformReg.add(getPredefinedUniformName(PredefinedUniform::Enum(ii) ), &m_predefinedUniforms[ii]);
			}

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

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_vertexShaders); ++ii)
			{
				m_vertexShaders[ii].destroy();
			}

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_fragmentShaders); ++ii)
			{
				m_fragmentShaders[ii].destroy();
			}

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_textures); ++ii)
			{
				m_textures[ii].destroy();
			}

 			for (uint32_t ii = 0; ii < BX_COUNTOF(m_renderTargets); ++ii)
 			{
 				m_renderTargets[ii].destroy();
 			}

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_uniforms); ++ii)
			{
				m_uniforms[ii].destroy();
			}

			for (uint32_t ii = 0; ii < PredefinedUniform::Count; ++ii)
			{
				m_predefinedUniforms[ii].destroy();
			}

			DX_RELEASE(m_swapChain, 0);
			DX_RELEASE(m_deviceCtx, 0);
			DX_RELEASE(m_device, 0);
			DX_RELEASE(m_factory, 0);

			bx::dlclose(m_dxgidll);
			bx::dlclose(m_d3d11dll);
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

		void flip()
		{
			if (NULL != m_swapChain)
			{
				uint32_t syncInterval = !!(m_flags & BGFX_RESET_VSYNC);
				DX_CHECK(m_swapChain->Present(syncInterval, 0) );
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

		void setRenderTarget(RenderTargetHandle _rt, bool _msaa = true)
		{
			BX_UNUSED(_msaa);
			if (_rt.idx == invalidHandle)
			{
				m_deviceCtx->OMSetRenderTargets(1, &m_backBufferColor, m_backBufferDepthStencil);
				
				m_currentColor = m_backBufferColor;
				m_currentDepthStencil = m_backBufferDepthStencil;
			}
			else
			{
				invalidateTextureStage();

				RenderTarget& renderTarget = m_renderTargets[_rt.idx];
				m_deviceCtx->OMSetRenderTargets(1, &renderTarget.m_rtv, renderTarget.m_dsv);

				m_currentColor = renderTarget.m_rtv;
				m_currentDepthStencil = renderTarget.m_dsv;
			}
		}

		void clear(const Clear& _clear)
		{
			if (NULL != m_currentColor
			&&  BGFX_CLEAR_COLOR_BIT & _clear.m_flags)
			{
				uint32_t rgba = _clear.m_rgba;
				float frgba[4] = { (rgba>>24)/255.0f, ( (rgba>>16)&0xff)/255.0f, ( (rgba>>8)&0xff)/255.0f, (rgba&0xff)/255.0f };
				m_deviceCtx->ClearRenderTargetView(m_currentColor, frgba);
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

		void setInputLayout(const VertexDecl& _vertexDecl, const Program& _program, uint8_t _numInstanceData)
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

		void setBlendState(uint64_t _state, uint32_t _rgba = UINT32_MAX)
		{
			_state &= BGFX_STATE_BLEND_MASK|BGFX_STATE_BLEND_EQUATION_MASK|BGFX_STATE_ALPHA_WRITE|BGFX_STATE_RGB_WRITE;

			ID3D11BlendState* bs = m_blendStateCache.find(_state);
			if (NULL == bs)
			{
				D3D11_BLEND_DESC desc;
				memset(&desc, 0, sizeof(desc) );
				D3D11_RENDER_TARGET_BLEND_DESC& drt = desc.RenderTarget[0];
				drt.BlendEnable = !!(BGFX_STATE_BLEND_MASK & _state);

				uint32_t blend = (_state&BGFX_STATE_BLEND_MASK)>>BGFX_STATE_BLEND_SHIFT;
				uint32_t equation = (_state&BGFX_STATE_BLEND_EQUATION_MASK)>>BGFX_STATE_BLEND_EQUATION_SHIFT;
				uint32_t src = blend&0xf;
				uint32_t dst = (blend>>4)&0xf;
				uint32_t writeMask = (_state&BGFX_STATE_ALPHA_WRITE) ? D3D11_COLOR_WRITE_ENABLE_ALPHA : 0;
				writeMask |= (_state&BGFX_STATE_RGB_WRITE) ? D3D11_COLOR_WRITE_ENABLE_RED|D3D11_COLOR_WRITE_ENABLE_GREEN|D3D11_COLOR_WRITE_ENABLE_BLUE : 0;

				drt.SrcBlend = s_blendFactor[src][0];
				drt.DestBlend = s_blendFactor[dst][0];
				drt.BlendOp = s_blendEquation[equation];

				drt.SrcBlendAlpha = s_blendFactor[src][1];
				drt.DestBlendAlpha = s_blendFactor[dst][1];
				drt.BlendOpAlpha = s_blendEquation[equation];

				drt.RenderTargetWriteMask = writeMask;

				DX_CHECK(m_device->CreateBlendState(&desc, &bs) );

				m_blendStateCache.add(_state, bs);
			}

			float blendFactor[4];
			blendFactor[0] = (_rgba>>24)/255.0f;
			blendFactor[1] = ( (_rgba>>16)&0xff)/255.0f;
			blendFactor[2] = ( (_rgba>>8)&0xff)/255.0f;
			blendFactor[3] = (_rgba&0xff)/255.0f;

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
				desc.DepthFunc = s_depthFunc[func];

				uint32_t bstencil = unpackStencil(1, _stencil);
				uint32_t frontAndBack = bstencil != BGFX_STENCIL_NONE && bstencil != fstencil;
				bstencil = frontAndBack ? bstencil : fstencil;

				desc.StencilEnable = 0 != _stencil;
				desc.StencilReadMask = (fstencil&BGFX_STENCIL_FUNC_RMASK_MASK)>>BGFX_STENCIL_FUNC_RMASK_SHIFT;
				desc.StencilWriteMask = 0xff;
				desc.FrontFace.StencilFailOp      = s_stencilOp[(fstencil&BGFX_STENCIL_OP_FAIL_S_MASK)>>BGFX_STENCIL_OP_FAIL_S_SHIFT];
				desc.FrontFace.StencilDepthFailOp = s_stencilOp[(fstencil&BGFX_STENCIL_OP_FAIL_Z_MASK)>>BGFX_STENCIL_OP_FAIL_Z_SHIFT];
				desc.FrontFace.StencilPassOp      = s_stencilOp[(fstencil&BGFX_STENCIL_OP_PASS_Z_MASK)>>BGFX_STENCIL_OP_PASS_Z_SHIFT];
				desc.FrontFace.StencilFunc        = s_stencilFunc[(fstencil&BGFX_STENCIL_TEST_MASK)>>BGFX_STENCIL_TEST_SHIFT];
				desc.BackFace.StencilFailOp       = s_stencilOp[(bstencil&BGFX_STENCIL_OP_FAIL_Z_MASK)>>BGFX_STENCIL_OP_FAIL_Z_SHIFT];
				desc.BackFace.StencilDepthFailOp  = s_stencilOp[(bstencil&BGFX_STENCIL_OP_FAIL_S_MASK)>>BGFX_STENCIL_OP_FAIL_S_SHIFT];
				desc.BackFace.StencilPassOp       = s_stencilOp[(bstencil&BGFX_STENCIL_OP_PASS_Z_MASK)>>BGFX_STENCIL_OP_PASS_Z_SHIFT];
				desc.BackFace.StencilFunc         = s_stencilFunc[(bstencil&BGFX_STENCIL_TEST_MASK)>>BGFX_STENCIL_TEST_SHIFT];

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
			_flags &= BGFX_TEXTURE_MIN_MASK|BGFX_TEXTURE_MAG_MASK|BGFX_TEXTURE_MIP_MASK
					| BGFX_TEXTURE_U_MASK|BGFX_TEXTURE_V_MASK|BGFX_TEXTURE_W_MASK
					;

			ID3D11SamplerState* sampler = m_samplerStateCache.find(_flags);
			if (NULL == sampler)
			{
				uint8_t minFilter = s_textureFilter[0][(_flags&BGFX_TEXTURE_MIN_MASK)>>BGFX_TEXTURE_MIN_SHIFT];
				uint8_t magFilter = s_textureFilter[1][(_flags&BGFX_TEXTURE_MAG_MASK)>>BGFX_TEXTURE_MAG_SHIFT];
				uint8_t mipFilter = s_textureFilter[2][(_flags&BGFX_TEXTURE_MIP_MASK)>>BGFX_TEXTURE_MIP_SHIFT];

				D3D11_SAMPLER_DESC sd;
				sd.Filter = (D3D11_FILTER)(minFilter|magFilter|mipFilter);
				sd.AddressU = s_textureAddress[(_flags&BGFX_TEXTURE_U_MASK)>>BGFX_TEXTURE_U_SHIFT];
				sd.AddressV = s_textureAddress[(_flags&BGFX_TEXTURE_V_MASK)>>BGFX_TEXTURE_V_SHIFT];
				sd.AddressW = s_textureAddress[(_flags&BGFX_TEXTURE_W_MASK)>>BGFX_TEXTURE_W_SHIFT];
				sd.MipLODBias = 0.0f;
				sd.MaxAnisotropy = 1;
				sd.ComparisonFunc = D3D11_COMPARISON_NEVER;
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
			m_deviceCtx->PSSetShaderResources(0, BGFX_STATE_TEX_COUNT, m_textureStage.m_srv);
			m_deviceCtx->PSSetSamplers(0, BGFX_STATE_TEX_COUNT, m_textureStage.m_sampler);
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

		void saveScreenShot(const char* _filePath)
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

#if BGFX_CONFIG_DEBUG_PIX
		void* m_d3d9dll;
		D3DPERF_SetMarkerFunc m_D3DPERF_SetMarker;
		D3DPERF_BeginEventFunc m_D3DPERF_BeginEvent;
		D3DPERF_EndEventFunc m_D3DPERF_EndEvent;
#endif // BGFX_CONFIG_DEBUG_PIX

		void* m_d3d11dll;
		void* m_dxgidll;
		D3D_DRIVER_TYPE m_driverType;
		IDXGIAdapter* m_adapter;
		DXGI_ADAPTER_DESC m_adapterDesc;
		IDXGIFactory* m_factory;
		IDXGISwapChain* m_swapChain;
		ID3D11Device* m_device;
		ID3D11DeviceContext* m_deviceCtx;
		ID3D11RenderTargetView* m_backBufferColor;
		ID3D11DepthStencilView* m_backBufferDepthStencil;
		ID3D11RenderTargetView* m_currentColor;
		ID3D11DepthStencilView* m_currentDepthStencil;

		ID3D11Texture2D* m_captureTexture;
		ID3D11Texture2D* m_captureResolve;

		bool m_wireframe;

		DXGI_SWAP_CHAIN_DESC m_scd;
		uint32_t m_flags;

		IndexBuffer m_indexBuffers[BGFX_CONFIG_MAX_INDEX_BUFFERS];
		VertexBuffer m_vertexBuffers[BGFX_CONFIG_MAX_VERTEX_BUFFERS];
		Shader m_vertexShaders[BGFX_CONFIG_MAX_VERTEX_SHADERS];
		Shader m_fragmentShaders[BGFX_CONFIG_MAX_FRAGMENT_SHADERS];
		Program m_program[BGFX_CONFIG_MAX_PROGRAMS];
		Texture m_textures[BGFX_CONFIG_MAX_TEXTURES];
		VertexDecl m_vertexDecls[BGFX_CONFIG_MAX_VERTEX_DECLS];
		RenderTarget m_renderTargets[BGFX_CONFIG_MAX_RENDER_TARGETS];
		UniformBuffer m_uniforms[BGFX_CONFIG_MAX_UNIFORMS];
		UniformBuffer m_predefinedUniforms[PredefinedUniform::Count];
		UniformRegistry m_uniformReg;
		
		StateCacheT<ID3D11BlendState> m_blendStateCache;
		StateCacheT<ID3D11DepthStencilState> m_depthStencilStateCache;
		StateCacheT<ID3D11InputLayout> m_inputLayoutCache;
		StateCacheT<ID3D11RasterizerState> m_rasterizerStateCache;
		StateCacheT<ID3D11SamplerState> m_samplerStateCache;

		TextVideoMem m_textVideoMem;
		RenderTargetHandle m_rt;

		TextureStage m_textureStage;

		Program* m_currentProgram;

		uint8_t m_vsScratch[64<<10];
		uint8_t m_fsScratch[64<<10];

		uint32_t m_vsChanges;
		uint32_t m_fsChanges;
	};

	static RendererContext s_renderCtx;

	void IndexBuffer::create(uint32_t _size, void* _data)
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

			DX_CHECK(s_renderCtx.m_device->CreateBuffer(&desc
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

			DX_CHECK(s_renderCtx.m_device->CreateBuffer(&desc
				, &srd
				, &m_ptr
				) );
		}
	}

	void IndexBuffer::update(uint32_t _offset, uint32_t _size, void* _data)
	{
		ID3D11DeviceContext* deviceCtx = s_renderCtx.m_deviceCtx;
		BX_CHECK(m_dynamic, "Must be dynamic!");

		D3D11_MAPPED_SUBRESOURCE mapped;
		D3D11_MAP type = m_dynamic && 0 == _offset && m_size == _size ? D3D11_MAP_WRITE_DISCARD : D3D11_MAP_WRITE_NO_OVERWRITE;
		DX_CHECK(deviceCtx->Map(m_ptr, 0, type, 0, &mapped) );
		memcpy( (uint8_t*)mapped.pData + _offset, _data, _size);
		deviceCtx->Unmap(m_ptr, 0);
	}

	void VertexBuffer::create(uint32_t _size, void* _data, VertexDeclHandle _declHandle)
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

			DX_CHECK(s_renderCtx.m_device->CreateBuffer(&desc
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

			DX_CHECK(s_renderCtx.m_device->CreateBuffer(&desc
				, &srd
				, &m_ptr
				) );
		}
	}

	void VertexBuffer::update(uint32_t _offset, uint32_t _size, void* _data)
	{
		ID3D11DeviceContext* deviceCtx = s_renderCtx.m_deviceCtx;
		BX_CHECK(m_dynamic, "Must be dynamic!");

		D3D11_MAPPED_SUBRESOURCE mapped;
		D3D11_MAP type = m_dynamic && 0 == _offset && m_size == _size ? D3D11_MAP_WRITE_DISCARD : D3D11_MAP_WRITE_NO_OVERWRITE;
		DX_CHECK(deviceCtx->Map(m_ptr, 0, type, 0, &mapped) );
		memcpy( (uint8_t*)mapped.pData + _offset, _data, _size);
		deviceCtx->Unmap(m_ptr, 0);
	}

	void ConstantBuffer::commit()
	{
		reset();

		do
		{
			uint32_t opcode = read();

			if (UniformType::End == opcode)
			{
				break;
			}

			UniformType::Enum type;
			uint16_t loc;
			uint16_t num;
			uint16_t copy;
			decodeOpcode(opcode, type, loc, num, copy);

			const char* data;
			if (copy)
			{
				data = read(g_uniformTypeSize[type]*num);
			}
			else
			{
				memcpy(&data, read(sizeof(void*) ), sizeof(void*) );
			}

#define CASE_IMPLEMENT_UNIFORM(_uniform, _glsuffix, _dxsuffix, _type) \
		case UniformType::_uniform: \
		case UniformType::_uniform|BGFX_UNIFORM_FRAGMENTBIT: \
			{ \
				s_renderCtx.setShaderConstant(type, loc, data, num); \
			} \
			break;

			switch ((int32_t)type)
			{
				CASE_IMPLEMENT_UNIFORM(Uniform1i, 1iv, I, int);
				CASE_IMPLEMENT_UNIFORM(Uniform1f, 1fv, F, float);
				CASE_IMPLEMENT_UNIFORM(Uniform1iv, 1iv, I, int);
				CASE_IMPLEMENT_UNIFORM(Uniform1fv, 1fv, F, float);
				CASE_IMPLEMENT_UNIFORM(Uniform2fv, 2fv, F, float);
				CASE_IMPLEMENT_UNIFORM(Uniform3fv, 3fv, F, float);
				CASE_IMPLEMENT_UNIFORM(Uniform4fv, 4fv, F, float);
				CASE_IMPLEMENT_UNIFORM(Uniform3x3fv, Matrix3fv, F, float);
				CASE_IMPLEMENT_UNIFORM(Uniform4x4fv, Matrix4fv, F, float);

			case UniformType::End:
				break;

			default:
				BX_TRACE("%4d: INVALID 0x%08x, t %d, l %d, n %d, c %d", m_pos, opcode, type, loc, num, copy);
				break;
			}

#undef CASE_IMPLEMENT_UNIFORM

		} while (true);
	}

	void TextVideoMemBlitter::setup()
	{
		ID3D11DeviceContext* deviceCtx = s_renderCtx.m_deviceCtx;

		uint32_t width = s_renderCtx.m_scd.BufferDesc.Width;
		uint32_t height = s_renderCtx.m_scd.BufferDesc.Height;

		RenderTargetHandle rt = BGFX_INVALID_HANDLE;
		s_renderCtx.setRenderTarget(rt, false);

		D3D11_VIEWPORT vp;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		vp.Width = (float)width;
		vp.Height = (float)height;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		deviceCtx->RSSetViewports(1, &vp);

		uint64_t state = BGFX_STATE_RGB_WRITE
			| BGFX_STATE_ALPHA_WRITE
			| BGFX_STATE_DEPTH_TEST_ALWAYS
			;
			
 		s_renderCtx.setBlendState(state);
 		s_renderCtx.setDepthStencilState(state);
 		s_renderCtx.setRasterizerState(state);

		Program& program = s_renderCtx.m_program[m_program.idx];
		s_renderCtx.m_currentProgram = &program;
		deviceCtx->VSSetShader( (ID3D11VertexShader*)program.m_vsh->m_ptr, NULL, 0);
		deviceCtx->VSSetConstantBuffers(0, 1, &program.m_vsh->m_buffer);
		deviceCtx->PSSetShader( (ID3D11PixelShader*)program.m_fsh->m_ptr, NULL, 0);
		deviceCtx->PSSetConstantBuffers(0, 1, &program.m_fsh->m_buffer);

		VertexBuffer& vb = s_renderCtx.m_vertexBuffers[m_vb->handle.idx];
		VertexDecl& vertexDecl = s_renderCtx.m_vertexDecls[m_vb->decl.idx];
		uint32_t stride = vertexDecl.m_stride;
		uint32_t offset = 0;
		deviceCtx->IASetVertexBuffers(0, 1, &vb.m_ptr, &stride, &offset);
		s_renderCtx.setInputLayout(vertexDecl, program, 0);

		IndexBuffer& ib = s_renderCtx.m_indexBuffers[m_ib->handle.idx];
		deviceCtx->IASetIndexBuffer(ib.m_ptr, DXGI_FORMAT_R16_UINT, 0);

		float proj[16];
		mtxOrtho(proj, 0.0f, (float)width, (float)height, 0.0f, 0.0f, 1000.0f);

		PredefinedUniform& predefined = program.m_predefined[0];
		uint8_t flags = predefined.m_type;
		s_renderCtx.setShaderConstant(flags, predefined.m_loc, proj, 4);

		s_renderCtx.commitShaderConstants();
		s_renderCtx.m_textures[m_texture.idx].commit(0);
		s_renderCtx.commitTextureStage();
	}

	void TextVideoMemBlitter::render(uint32_t _numIndices)
	{
		ID3D11DeviceContext* deviceCtx = s_renderCtx.m_deviceCtx;

		IndexBuffer& ib = s_renderCtx.m_indexBuffers[m_ib->handle.idx];
 		ib.update(0, _numIndices*2, m_ib->data);

		uint32_t numVertices = _numIndices*4/6;
		s_renderCtx.m_vertexBuffers[m_vb->handle.idx].update(0, numVertices*m_decl.m_stride, m_vb->data);

		deviceCtx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		deviceCtx->DrawIndexed(_numIndices, 0, 0);
	}

	void ClearQuad::clear(const Rect& _rect, const Clear& _clear, uint32_t _height)
	{
		BX_UNUSED(_height);
		uint32_t width = s_renderCtx.m_scd.BufferDesc.Width;
		uint32_t height = s_renderCtx.m_scd.BufferDesc.Height;

		if (0 == _rect.m_x
		&&  0 == _rect.m_y
		&&  width == _rect.m_width
		&&  height == _rect.m_height)
		{
			s_renderCtx.clear(_clear);
		}
		else
		{
			ID3D11DeviceContext* deviceCtx = s_renderCtx.m_deviceCtx;

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

			s_renderCtx.setBlendState(state);
			s_renderCtx.setDepthStencilState(state, stencil);
			s_renderCtx.setRasterizerState(state);

			Program& program = s_renderCtx.m_program[m_program.idx];
			s_renderCtx.m_currentProgram = &program;
			deviceCtx->VSSetShader( (ID3D11VertexShader*)program.m_vsh->m_ptr, NULL, 0);
			deviceCtx->VSSetConstantBuffers(0, 0, NULL);
			deviceCtx->PSSetShader( (ID3D11PixelShader*)program.m_fsh->m_ptr, NULL, 0);
			deviceCtx->PSSetConstantBuffers(0, 0, NULL);

			VertexBuffer& vb = s_renderCtx.m_vertexBuffers[m_vb->handle.idx];
			VertexDecl& vertexDecl = s_renderCtx.m_vertexDecls[m_vb->decl.idx];
			uint32_t stride = vertexDecl.m_stride;
			uint32_t offset = 0;

			{
				struct Vertex
				{
					float m_x;
					float m_y;
					float m_z;
					uint32_t m_abgr;
				} * vertex = (Vertex*)m_vb->data;
				BX_CHECK(stride == sizeof(Vertex), "Stride/Vertex mismatch (stride %d, sizeof(Vertex) %d)", stride, sizeof(Vertex) );

				const uint32_t abgr = bx::endianSwap(_clear.m_rgba);
				const float depth = _clear.m_depth;

				vertex->m_x = -1.0f;
				vertex->m_y = -1.0f;
				vertex->m_z = depth;
				vertex->m_abgr = abgr;
				vertex++;
				vertex->m_x =  1.0f;
				vertex->m_y = -1.0f;
				vertex->m_z = depth;
				vertex->m_abgr = abgr;
				vertex++;
				vertex->m_x =  1.0f;
				vertex->m_y =  1.0f;
				vertex->m_z = depth;
				vertex->m_abgr = abgr;
				vertex++;
				vertex->m_x = -1.0f;
				vertex->m_y =  1.0f;
				vertex->m_z = depth;
				vertex->m_abgr = abgr;
			}

			s_renderCtx.m_vertexBuffers[m_vb->handle.idx].update(0, 4*m_decl.m_stride, m_vb->data);
			deviceCtx->IASetVertexBuffers(0, 1, &vb.m_ptr, &stride, &offset);
			s_renderCtx.setInputLayout(vertexDecl, program, 0);

			IndexBuffer& ib = s_renderCtx.m_indexBuffers[m_ib.idx];
			deviceCtx->IASetIndexBuffer(ib.m_ptr, DXGI_FORMAT_R16_UINT, 0);

			deviceCtx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			deviceCtx->DrawIndexed(6, 0, 0);
		}
	}

	void Shader::create(bool _fragment, const Memory* _mem)
	{
		bx::MemoryReader reader(_mem->data, _mem->size);

		uint32_t magic;
		bx::read(&reader, magic);

		uint32_t iohash;
		bx::read(&reader, iohash);

		bx::read(&reader, m_attrMask, sizeof(m_attrMask) );

		uint16_t count;
		bx::read(&reader, count);

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
			DX_CHECK(s_renderCtx.m_device->CreateBuffer(&desc, NULL, &m_buffer) );
		}

		m_numPredefined = 0;
		m_numUniforms = count;

		BX_TRACE("Shader consts %d", count);

		uint8_t fragmentBit = _fragment ? BGFX_UNIFORM_FRAGMENTBIT : 0;

		if (0 < count)
		{
			m_constantBuffer = ConstantBuffer::create(1024);

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

				const void* data = NULL;
				PredefinedUniform::Enum predefined = nameToPredefinedUniformEnum(name);
				if (PredefinedUniform::Count != predefined)
				{
					kind = "predefined";
					m_predefined[m_numPredefined].m_loc = regIndex;
					m_predefined[m_numPredefined].m_count = regCount;
					m_predefined[m_numPredefined].m_type = predefined|fragmentBit;
					m_numPredefined++;
				}
				else
				{
					const UniformInfo* info = s_renderCtx.m_uniformReg.find(name);
					UniformBuffer* uniform = info != NULL ? (UniformBuffer*)info->m_data : NULL;

					if (NULL != uniform)
					{
						kind = "user";
						data = uniform->m_data;
						m_constantBuffer->writeUniformRef( (UniformType::Enum)(type|fragmentBit), regIndex, data, regCount);
					}
				}

				BX_TRACE("\t%s: %s, type %2d, num %2d, r.index %3d, r.count %2d"
					, kind
					, name
					, type
					, num
					, regIndex
					, regCount
					);
			}

			m_constantBuffer->finish();
		}

		uint16_t shaderSize;
		bx::read(&reader, shaderSize);

		const DWORD* code = (const DWORD*)reader.getDataPtr();
		bx::skip(&reader, shaderSize);

		if (_fragment)
		{
			DX_CHECK(s_renderCtx.m_device->CreatePixelShader(code, shaderSize, NULL, (ID3D11PixelShader**)&m_ptr) );
			BGFX_FATAL(NULL != m_ptr, bgfx::Fatal::InvalidShader, "Failed to create fragment shader.");
		}
		else
		{
			m_hash = bx::hashMurmur2A(code, shaderSize);
			m_code = alloc(shaderSize);
			memcpy(m_code->data, code, shaderSize);

			DX_CHECK(s_renderCtx.m_device->CreateVertexShader(code, shaderSize, NULL, (ID3D11VertexShader**)&m_ptr) );
			BGFX_FATAL(NULL != m_ptr, bgfx::Fatal::InvalidShader, "Failed to create vertex shader.");
		}
	}

	void Texture::create(const Memory* _mem, uint32_t _flags)
	{
		m_sampler = s_renderCtx.getSamplerState(_flags);

		Dds dds;

		if (parseDds(dds, _mem) )
		{
			bool decompress = false;

			if (dds.m_cubeMap)
			{
				m_type = TextureCube;
			}
			else if (dds.m_depth > 1)
			{
				m_type = Texture3D;
			}
			else
			{
				m_type = Texture2D;
			}

			uint32_t numSrd = dds.m_numMips*(dds.m_cubeMap ? 6 : 1);
			D3D11_SUBRESOURCE_DATA* srd = (D3D11_SUBRESOURCE_DATA*)alloca(numSrd*sizeof(D3D11_SUBRESOURCE_DATA) );

			uint32_t kk = 0;
			bool convert = false;

			m_numMips = dds.m_numMips;

			if (decompress
			||  TextureFormat::Unknown < dds.m_type)
			{
				uint32_t bpp = s_textureFormat[dds.m_type].m_bpp;
				convert = TextureFormat::BGRX8 == dds.m_type;

				for (uint8_t side = 0, numSides = dds.m_cubeMap ? 6 : 1; side < numSides; ++side)
				{
					uint32_t width  = dds.m_width;
					uint32_t height = dds.m_height;
					uint32_t depth  = dds.m_depth;

					for (uint32_t lod = 0, num = m_numMips; lod < num; ++lod)
					{
						width  = bx::uint32_max(1, width);
						height = bx::uint32_max(1, height);
						depth  = bx::uint32_max(1, depth);

						Mip mip;
						if (getRawImageData(dds, side, lod, _mem, mip) )
						{
							if (convert)
							{
								uint8_t* temp = (uint8_t*)g_realloc(NULL, mip.m_width*mip.m_height*bpp/8);
								mip.decode(temp);

								srd[kk].pSysMem = temp;
								srd[kk].SysMemPitch = mip.m_width*bpp/8;
							}
							else
							{
								srd[kk].pSysMem = mip.m_data;
								srd[kk].SysMemPitch = mip.m_width*mip.m_bpp/8;
							}

							srd[kk].SysMemSlicePitch = mip.m_height*srd[kk].SysMemPitch;
							++kk;
						}

						width  >>= 1;
						height >>= 1;
						depth  >>= 1;
					}
				}
			}
			else
			{
				for (uint8_t side = 0, numSides = dds.m_cubeMap ? 6 : 1; side < numSides; ++side)
				{
					for (uint32_t lod = 0, num = m_numMips; lod < num; ++lod)
					{
						Mip mip;
						if (getRawImageData(dds, side, lod, _mem, mip) )
						{
							srd[kk].pSysMem = mip.m_data;
							if (TextureFormat::Unknown > dds.m_type)
							{
								srd[kk].SysMemPitch = (mip.m_width/4)*mip.m_blockSize;
								srd[kk].SysMemSlicePitch = (mip.m_height/4)*srd[kk].SysMemPitch;
							}
							else
							{
								srd[kk].SysMemPitch = mip.m_width*mip.m_bpp/8;
								srd[kk].SysMemSlicePitch = mip.m_height*srd[kk].SysMemPitch;
							}

							++kk;
						}
					}
				}
			}

			D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
			memset(&srvd, 0, sizeof(srvd) );
			srvd.Format = s_textureFormat[dds.m_type].m_fmt;

			switch (m_type)
			{
			case Texture2D:
			case TextureCube:
				{
					D3D11_TEXTURE2D_DESC desc;
					desc.Width = dds.m_width;
					desc.Height = dds.m_height;
					desc.MipLevels = dds.m_numMips;
					desc.Format = s_textureFormat[dds.m_type].m_fmt;
					desc.SampleDesc.Count = 1;
					desc.SampleDesc.Quality = 0;
					desc.Usage = D3D11_USAGE_IMMUTABLE;
					desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
					desc.CPUAccessFlags = 0;

					if (dds.m_cubeMap)
					{
						desc.ArraySize = 6;
						desc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
						srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
						srvd.TextureCube.MipLevels = dds.m_numMips;
					}
					else
					{
						desc.ArraySize = 1;
						desc.MiscFlags = 0;
						srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
						srvd.Texture2D.MipLevels = dds.m_numMips;
					}

					DX_CHECK(s_renderCtx.m_device->CreateTexture2D(&desc, srd, &m_texture2d) );
				}
				break;

			case Texture3D:
				{
					D3D11_TEXTURE3D_DESC desc;
					desc.Width = dds.m_width;
					desc.Height = dds.m_height;
					desc.Depth = dds.m_depth;
					desc.MipLevels = dds.m_numMips;
					desc.Format = s_textureFormat[dds.m_type].m_fmt;
					desc.Usage = D3D11_USAGE_IMMUTABLE;
					desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
					desc.CPUAccessFlags = 0;
					desc.MiscFlags = 0;

					srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE3D;
					srvd.Texture3D.MipLevels = dds.m_numMips;

					DX_CHECK(s_renderCtx.m_device->CreateTexture3D(&desc, srd, &m_texture3d) );
				}
				break;
			}

			DX_CHECK(s_renderCtx.m_device->CreateShaderResourceView(m_ptr, &srvd, &m_srv) );

			if (convert)
			{
				kk = 0;
				for (uint8_t side = 0, numSides = dds.m_cubeMap ? 6 : 1; side < numSides; ++side)
				{
					for (uint32_t lod = 0, num = dds.m_numMips; lod < num; ++lod)
					{
						g_free(const_cast<void*>(srd[kk].pSysMem) );
						++kk;
					}
				}
			}
		}
		else
		{
			bx::MemoryReader reader(_mem->data, _mem->size);

			uint32_t magic;
			bx::read(&reader, magic);

			if (BGFX_CHUNK_MAGIC_TEX == magic)
			{
				TextureCreate tc;
				bx::read(&reader, tc);

				if (tc.m_cubeMap)
				{
					m_type = TextureCube;
				}
				else if (tc.m_depth > 1)
				{
					m_type = Texture3D;
				}
				else
				{
					m_type = Texture2D;
				}

				m_numMips = tc.m_numMips;

				D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
				memset(&srvd, 0, sizeof(srvd) );
				srvd.Format = s_textureFormat[tc.m_format].m_fmt;

				if (NULL != tc.m_mem)
				{
					D3D11_TEXTURE2D_DESC desc;
					desc.Width = tc.m_width;
					desc.Height = tc.m_height;
					desc.MipLevels = tc.m_numMips;
					desc.ArraySize = 1;
					desc.Format = srvd.Format;
					desc.SampleDesc.Count = 1;
					desc.SampleDesc.Quality = 0;
					desc.Usage = D3D11_USAGE_IMMUTABLE;
					desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
					desc.CPUAccessFlags = 0;
					desc.MiscFlags = 0;

					srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
					srvd.Texture2D.MipLevels = tc.m_numMips;

					D3D11_SUBRESOURCE_DATA* srd = (D3D11_SUBRESOURCE_DATA*)alloca(tc.m_numMips*sizeof(D3D11_SUBRESOURCE_DATA) );
					uint32_t bpp = s_textureFormat[tc.m_format].m_bpp;
					uint8_t* data = tc.m_mem->data;

					for (uint8_t side = 0, numSides = tc.m_cubeMap ? 6 : 1; side < numSides; ++side)
					{
						uint32_t width  = tc.m_width;
						uint32_t height = tc.m_height;
						uint32_t depth  = tc.m_depth;

						for (uint32_t lod = 0, num = tc.m_numMips; lod < num; ++lod)
						{
							width  = bx::uint32_max(1, width);
							height = bx::uint32_max(1, height);
							depth  = bx::uint32_max(1, depth);

							srd[lod].pSysMem = data;
							srd[lod].SysMemPitch = width*bpp/8;
							srd[lod].SysMemSlicePitch = 0;

							data += width*height*bpp/8;

							width  >>= 1;
							height >>= 1;
							depth  >>= 1;
						}
					}

					DX_CHECK(s_renderCtx.m_device->CreateTexture2D(&desc, srd, &m_texture2d) );

					release(tc.m_mem);
				}
				else
				{
					switch (m_type)
					{
					case Texture2D:
					case TextureCube:
						{
							D3D11_TEXTURE2D_DESC desc;
							desc.Width = tc.m_width;
							desc.Height = tc.m_height;
							desc.MipLevels = tc.m_numMips;
							desc.Format = srvd.Format;
							desc.SampleDesc.Count = 1;
							desc.SampleDesc.Quality = 0;
							desc.Usage = D3D11_USAGE_DEFAULT;
							desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
							desc.CPUAccessFlags = 0;

							if (TextureCube == m_type)
							{
								desc.ArraySize = 6;
								desc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
								srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
								srvd.TextureCube.MipLevels = m_numMips;
							}
							else
							{
								desc.ArraySize = 1;
								desc.MiscFlags = 0;
								srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
								srvd.Texture2D.MipLevels = m_numMips;
							}

							DX_CHECK(s_renderCtx.m_device->CreateTexture2D(&desc, NULL, &m_texture2d) );
						}
						break;

					case Texture3D:
						{
							D3D11_TEXTURE3D_DESC desc;
							desc.Width = tc.m_width;
							desc.Height = tc.m_height;
							desc.Depth = tc.m_depth;
							desc.MipLevels = tc.m_numMips;
							desc.Format = srvd.Format;
							desc.Usage = D3D11_USAGE_DEFAULT;
							desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
							desc.CPUAccessFlags = 0;
							desc.MiscFlags = 0;

							srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE3D;
							srvd.Texture3D.MipLevels = m_numMips;

							DX_CHECK(s_renderCtx.m_device->CreateTexture3D(&desc, NULL, &m_texture3d) );
						}
						break;
					}
				}

				DX_CHECK(s_renderCtx.m_device->CreateShaderResourceView(m_ptr, &srvd, &m_srv) );
			}
			else
			{
				//
			}
		}
	}

	void Texture::destroy()
	{
		DX_RELEASE(m_srv, 0);
		DX_RELEASE(m_ptr, 0);
	}

	void Texture::commit(uint8_t _stage, uint32_t _flags)
	{
		TextureStage& ts = s_renderCtx.m_textureStage;
		ts.m_srv[_stage] = m_srv;
		ts.m_sampler[_stage] = 0 == (BGFX_SAMPLER_DEFAULT_FLAGS & _flags) 
							 ? s_renderCtx.getSamplerState(_flags)
							 : m_sampler
							 ;
	}

	void Texture::update(uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, const Memory* _mem)
	{
		ID3D11DeviceContext* deviceCtx = s_renderCtx.m_deviceCtx;

		D3D11_BOX box;
		box.left = _rect.m_x;
		box.top = _rect.m_y;
		box.right = box.left + _rect.m_width;
		box.bottom = box.top + _rect.m_height;
		box.front = _z;
		box.back = box.front + _depth;

		uint32_t subres = _mip + (_side * m_numMips);
#if 0
		D3D11_MAPPED_SUBRESOURCE mapped;
		DX_CHECK(deviceCtx->Map(m_ptr, 0, D3D11_MAP_WRITE, D3D11_MAP_FLAG_DO_NOT_WAIT, &mapped) );
		memcpy( (uint8_t*)mapped.pData + subres*mapped.DepthPitch, _mem->data, _mem->size);
		deviceCtx->Unmap(m_ptr, 0);

		deviceCtx->CopySubresourceRegion(m_ptr
			, subres
			, _rect.m_x
			, _rect.m_y
			, _rect.m_z
			, staging // D3D11_USAGE_STAGING
			, ...
			);
#else
		deviceCtx->UpdateSubresource(m_ptr, subres, &box, _mem->data, _rect.m_width*4, 0);
#endif // 0
	}

	void RenderTarget::create(uint16_t _width, uint16_t _height, uint32_t _flags, uint32_t _textureFlags)
	{
		m_width = _width;
		m_height = _height;
		m_flags = _flags;

		uint32_t colorFormat = (m_flags&BGFX_RENDER_TARGET_COLOR_MASK)>>BGFX_RENDER_TARGET_COLOR_SHIFT;
		uint32_t depthFormat = (m_flags&BGFX_RENDER_TARGET_DEPTH_MASK)>>BGFX_RENDER_TARGET_DEPTH_SHIFT;

		D3D11_TEXTURE2D_DESC desc;
		desc.Width = _width;
		desc.Height = _height;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = s_colorFormat[colorFormat];
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE|D3D11_BIND_RENDER_TARGET;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;

		DX_CHECK(s_renderCtx.m_device->CreateTexture2D(&desc, NULL, &m_colorTexture) );
		DX_CHECK(s_renderCtx.m_device->CreateRenderTargetView(m_colorTexture, NULL, &m_rtv) );
		DX_CHECK(s_renderCtx.m_device->CreateShaderResourceView(m_colorTexture, NULL, &m_srv) );

		if (0 < depthFormat)
		{
			D3D11_TEXTURE2D_DESC desc;
			desc.Width = _width;
			desc.Height = _height;
			desc.MipLevels = 1;
			desc.ArraySize = 1;
			desc.Format = s_depthFormat[depthFormat];
			desc.SampleDesc.Count = 1;
			desc.SampleDesc.Quality = 0;
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			desc.CPUAccessFlags = 0;
			desc.MiscFlags = 0;
			
			DX_CHECK(s_renderCtx.m_device->CreateTexture2D(&desc, NULL, &m_depthTexture) );
			DX_CHECK(s_renderCtx.m_device->CreateDepthStencilView(m_depthTexture, NULL, &m_dsv) );
//			DX_CHECK(s_renderCtx.m_device->CreateShaderResourceView(m_depthTexture, NULL, &m_srv) );
		}

		m_sampler = s_renderCtx.getSamplerState(_textureFlags);
	}

	void RenderTarget::destroy()
	{
		DX_RELEASE(m_srv, 0);
		DX_RELEASE(m_rtv, 0);
		DX_RELEASE(m_colorTexture, 0);
		DX_RELEASE(m_dsv, 0);
		DX_RELEASE(m_depthTexture, 0);

		m_flags = 0;
	}

	void RenderTarget::commit(uint8_t _stage, uint32_t _flags)
	{
		TextureStage& ts = s_renderCtx.m_textureStage;
		ts.m_srv[_stage] = m_srv;
		ts.m_sampler[_stage] = 0 == (BGFX_SAMPLER_DEFAULT_FLAGS & _flags) 
							 ? s_renderCtx.getSamplerState(_flags)
							 : m_sampler
							 ;
	}

	void UniformBuffer::create(UniformType::Enum _type, uint16_t _num, bool _alloc)
	{
		uint32_t size = BX_ALIGN_16(g_uniformTypeSize[_type]*_num);
		if (_alloc)
		{
			m_data = g_realloc(NULL, size);
			memset(m_data, 0, size);
		}

		D3D11_BUFFER_DESC desc;
		desc.ByteWidth = size;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;
		DX_CHECK(s_renderCtx.m_device->CreateBuffer(&desc, NULL, &m_ptr) );
	}

	void UniformBuffer::destroy()
	{
		if (NULL != m_data)
		{
			g_free(m_data);
			m_data = NULL;
		}

		DX_RELEASE(m_ptr, 0);
	}

	void Context::flip()
	{
		s_renderCtx.flip();
	}

	void Context::rendererInit()
	{
		s_renderCtx.init();
	}

	void Context::rendererShutdown()
	{
		s_renderCtx.shutdown();
	}

	void Context::rendererCreateIndexBuffer(IndexBufferHandle _handle, Memory* _mem)
	{
		s_renderCtx.m_indexBuffers[_handle.idx].create(_mem->size, _mem->data);
	}

	void Context::rendererDestroyIndexBuffer(IndexBufferHandle _handle)
	{
		s_renderCtx.m_indexBuffers[_handle.idx].destroy();
	}

	void Context::rendererCreateVertexDecl(VertexDeclHandle _handle, const VertexDecl& _decl)
	{
		VertexDecl& decl = s_renderCtx.m_vertexDecls[_handle.idx];
		memcpy(&decl, &_decl, sizeof(VertexDecl) );
		dump(decl);
	}

	void Context::rendererDestroyVertexDecl(VertexDeclHandle /*_handle*/)
	{
	}

	void Context::rendererCreateVertexBuffer(VertexBufferHandle _handle, Memory* _mem, VertexDeclHandle _declHandle)
	{
		s_renderCtx.m_vertexBuffers[_handle.idx].create(_mem->size, _mem->data, _declHandle);
	}

	void Context::rendererDestroyVertexBuffer(VertexBufferHandle _handle)
	{
		s_renderCtx.m_vertexBuffers[_handle.idx].destroy();
	}

	void Context::rendererCreateDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _size)
	{
		s_renderCtx.m_indexBuffers[_handle.idx].create(_size, NULL);
	}

	void Context::rendererUpdateDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _offset, uint32_t _size, Memory* _mem)
	{
		s_renderCtx.m_indexBuffers[_handle.idx].update(_offset, bx::uint32_min(_size, _mem->size), _mem->data);
	}

	void Context::rendererDestroyDynamicIndexBuffer(IndexBufferHandle _handle)
	{
		s_renderCtx.m_indexBuffers[_handle.idx].destroy();
	}

	void Context::rendererCreateDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _size)
	{
		VertexDeclHandle decl = BGFX_INVALID_HANDLE;
		s_renderCtx.m_vertexBuffers[_handle.idx].create(_size, NULL, decl);
	}

	void Context::rendererUpdateDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _offset, uint32_t _size, Memory* _mem)
	{
		s_renderCtx.m_vertexBuffers[_handle.idx].update(_offset, bx::uint32_min(_size, _mem->size), _mem->data);
	}

	void Context::rendererDestroyDynamicVertexBuffer(VertexBufferHandle _handle)
	{
		s_renderCtx.m_vertexBuffers[_handle.idx].destroy();
	}

	void Context::rendererCreateVertexShader(VertexShaderHandle _handle, Memory* _mem)
	{
		s_renderCtx.m_vertexShaders[_handle.idx].create(false, _mem);
	}

	void Context::rendererDestroyVertexShader(VertexShaderHandle _handle)
	{
		s_renderCtx.m_vertexShaders[_handle.idx].destroy();
	}

	void Context::rendererCreateFragmentShader(FragmentShaderHandle _handle, Memory* _mem)
	{
		s_renderCtx.m_fragmentShaders[_handle.idx].create(true, _mem);
	}

	void Context::rendererDestroyFragmentShader(FragmentShaderHandle _handle)
	{
		s_renderCtx.m_fragmentShaders[_handle.idx].destroy();
	}

	void Context::rendererCreateProgram(ProgramHandle _handle, VertexShaderHandle _vsh, FragmentShaderHandle _fsh)
	{
		s_renderCtx.m_program[_handle.idx].create(s_renderCtx.m_vertexShaders[_vsh.idx], s_renderCtx.m_fragmentShaders[_fsh.idx]);
	}

	void Context::rendererDestroyProgram(FragmentShaderHandle _handle)
	{
		s_renderCtx.m_program[_handle.idx].destroy();
	}

	void Context::rendererCreateTexture(TextureHandle _handle, Memory* _mem, uint32_t _flags)
	{
		s_renderCtx.m_textures[_handle.idx].create(_mem, _flags);
	}

	void Context::rendererUpdateTextureBegin(TextureHandle /*_handle*/, uint8_t /*_side*/, uint8_t /*_mip*/)
	{
	}

	void Context::rendererUpdateTexture(TextureHandle _handle, uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, const Memory* _mem)
	{
		s_renderCtx.m_textures[_handle.idx].update(_side, _mip, _rect, _z, _depth, _mem);
	}

	void Context::rendererUpdateTextureEnd()
	{
	}

	void Context::rendererDestroyTexture(TextureHandle _handle)
	{
		s_renderCtx.m_textures[_handle.idx].destroy();
	}

	void Context::rendererCreateRenderTarget(RenderTargetHandle _handle, uint16_t _width, uint16_t _height, uint32_t _flags, uint32_t _textureFlags)
	{
		s_renderCtx.m_renderTargets[_handle.idx].create(_width, _height, _flags, _textureFlags);
	}

	void Context::rendererDestroyRenderTarget(RenderTargetHandle _handle)
	{
		s_renderCtx.m_renderTargets[_handle.idx].destroy();
	}

	void Context::rendererCreateUniform(UniformHandle _handle, UniformType::Enum _type, uint16_t _num, const char* _name)
	{
		s_renderCtx.m_uniforms[_handle.idx].create(_type, _num);
		s_renderCtx.m_uniformReg.add(_name, &s_renderCtx.m_uniforms[_handle.idx]);
	}

	void Context::rendererDestroyUniform(UniformHandle _handle)
	{
		s_renderCtx.m_uniforms[_handle.idx].destroy();
	}

	void Context::rendererSaveScreenShot(const char* _filePath)
	{
		s_renderCtx.saveScreenShot(_filePath);
	}

	void Context::rendererUpdateViewName(uint8_t _id, const char* _name)
	{
		mbstowcs(&s_viewNameW[_id][0], _name, BX_COUNTOF(s_viewNameW[0]) );
	}

	void Context::rendererUpdateUniform(uint16_t _loc, const void* _data, uint32_t _size)
	{
		memcpy(s_renderCtx.m_uniforms[_loc].m_data, _data, _size);
	}

	void Context::rendererSetMarker(const char* _marker, uint32_t _size)
	{
#if BGFX_CONFIG_DEBUG_PIX
		uint32_t size = _size*sizeof(wchar_t);
		wchar_t* name = (wchar_t*)alloca(size);
		mbstowcs(name, _marker, size-2);
		PIX_SETMARKER(D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xff), name);
#endif // BGFX_CONFIG_DEBUG_PIX
		BX_UNUSED(_marker, _size);
	}

	void Context::rendererSubmit()
	{
		PIX_BEGINEVENT(D3DCOLOR_RGBA(0xff, 0x00, 0x00, 0xff), L"rendererSubmit");

		ID3D11DeviceContext* deviceCtx = s_renderCtx.m_deviceCtx;

		s_renderCtx.updateResolution(m_render->m_resolution);

		int64_t elapsed = -bx::getHPCounter();
		int64_t captureElapsed = 0;

		if (0 < m_render->m_iboffset)
		{
			TransientIndexBuffer* ib = m_render->m_transientIb;
			s_renderCtx.m_indexBuffers[ib->handle.idx].update(0, m_render->m_iboffset, ib->data);
		}

		if (0 < m_render->m_vboffset)
		{
			TransientVertexBuffer* vb = m_render->m_transientVb;
			s_renderCtx.m_vertexBuffers[vb->handle.idx].update(0, m_render->m_vboffset, vb->data);
		}

		m_render->sort();

		RenderState currentState;
		currentState.reset();
		currentState.m_flags = BGFX_STATE_NONE;
		currentState.m_stencil = packStencil(BGFX_STENCIL_NONE, BGFX_STENCIL_NONE);

		Matrix4 viewProj[BGFX_CONFIG_MAX_VIEWS];
		for (uint32_t ii = 0; ii < BGFX_CONFIG_MAX_VIEWS; ++ii)
		{
			mtxMul(viewProj[ii].val, m_render->m_view[ii].val, m_render->m_proj[ii].val);
		}

		bool wireframe = !!(m_render->m_debug&BGFX_DEBUG_WIREFRAME);
		bool scissorEnabled = false;
		s_renderCtx.setDebugWireframe(wireframe);

		uint16_t programIdx = invalidHandle;
		SortKey key;
		uint8_t view = 0xff;
		RenderTargetHandle rt = BGFX_INVALID_HANDLE;
		float alphaRef = 0.0f;
		D3D11_PRIMITIVE_TOPOLOGY primType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		deviceCtx->IASetPrimitiveTopology(primType);
		uint32_t primNumVerts = 3;
		bool viewHasScissor = false;
		Rect viewScissorRect;
		viewScissorRect.clear();

		uint32_t statsNumPrimsSubmitted = 0;
		uint32_t statsNumIndices = 0;
		uint32_t statsNumInstances = 0;
		uint32_t statsNumPrimsRendered = 0;

		if (0 == (m_render->m_debug&BGFX_DEBUG_IFH) )
		{
			for (uint32_t item = 0, numItems = m_render->m_num; item < numItems; ++item)
			{
				key.decode(m_render->m_sortKeys[item]);
				const RenderState& state = m_render->m_renderState[m_render->m_sortValues[item] ];

				const uint64_t newFlags = state.m_flags;
				uint64_t changedFlags = currentState.m_flags ^ state.m_flags;
				currentState.m_flags = newFlags;

				const uint64_t newStencil = state.m_stencil;
				uint64_t changedStencil = currentState.m_stencil ^ state.m_stencil;
				currentState.m_stencil = newStencil;

				if (key.m_view != view)
				{
					currentState.clear();
					currentState.m_scissor = !state.m_scissor;
					changedFlags = BGFX_STATE_MASK;
					changedStencil = packStencil(BGFX_STENCIL_MASK, BGFX_STENCIL_MASK);
					currentState.m_flags = newFlags;
					currentState.m_stencil = newStencil;

					PIX_ENDEVENT();
					PIX_BEGINEVENT(D3DCOLOR_RGBA(0xff, 0x00, 0x00, 0xff), s_viewNameW[key.m_view]);

					view = key.m_view;
					programIdx = invalidHandle;

					if (m_render->m_rt[view].idx != rt.idx)
					{
						rt = m_render->m_rt[view];
						s_renderCtx.setRenderTarget(rt);
					}

					const Rect& rect = m_render->m_rect[view];
					const Rect& scissorRect = m_render->m_scissor[view];
					viewHasScissor = !scissorRect.isZero();
					viewScissorRect = viewHasScissor ? scissorRect : rect;

					D3D11_VIEWPORT vp;
					vp.TopLeftX = rect.m_x;
					vp.TopLeftY = rect.m_y;
					vp.Width = rect.m_width;
					vp.Height = rect.m_height;
					vp.MinDepth = 0.0f;
					vp.MaxDepth = 1.0f;
					deviceCtx->RSSetViewports(1, &vp);
					Clear& clear = m_render->m_clear[view];

					if (BGFX_CLEAR_NONE != clear.m_flags)
					{
						m_clearQuad.clear(rect, clear);
					}

					s_renderCtx.setBlendState(newFlags);
					s_renderCtx.setDepthStencilState(newFlags, packStencil(BGFX_STENCIL_DEFAULT, BGFX_STENCIL_DEFAULT) );

					uint8_t primIndex = uint8_t( (newFlags&BGFX_STATE_PT_MASK)>>BGFX_STATE_PT_SHIFT);
					if (primType != s_primType[primIndex])
					{
						primType = s_primType[primIndex];
						primNumVerts = 3-primIndex;
						deviceCtx->IASetPrimitiveTopology(primType);
					}
				}

				uint16_t scissor = state.m_scissor;
				if (currentState.m_scissor != scissor)
				{
					currentState.m_scissor = scissor;

					if (UINT16_MAX == scissor)
					{
						scissorEnabled = viewHasScissor;
						if (viewHasScissor)
						{
							D3D11_RECT rc;
							rc.left = viewScissorRect.m_x;
							rc.top = viewScissorRect.m_y;
							rc.right = viewScissorRect.m_x + viewScissorRect.m_width;
							rc.bottom = viewScissorRect.m_y + viewScissorRect.m_height;
							deviceCtx->RSSetScissorRects(1, &rc);
						}
					}
					else
					{
						Rect scissorRect;
						scissorRect.intersect(viewScissorRect, m_render->m_rectCache.m_cache[scissor]);
						scissorEnabled = true;
						D3D11_RECT rc;
						rc.left = scissorRect.m_x;
						rc.top = scissorRect.m_y;
						rc.right = scissorRect.m_x + scissorRect.m_width;
						rc.bottom = scissorRect.m_y + scissorRect.m_height;
						deviceCtx->RSSetScissorRects(1, &rc);
					}

					s_renderCtx.setRasterizerState(newFlags, wireframe, scissorEnabled);
				}

				if ( (BGFX_STATE_DEPTH_WRITE|BGFX_STATE_DEPTH_TEST_MASK) & changedFlags
				|| 0 != changedStencil)
				{
					s_renderCtx.setDepthStencilState(newFlags, newStencil);
				}

				if ( (0
					 | BGFX_STATE_CULL_MASK
					 | BGFX_STATE_ALPHA_MASK
					 | BGFX_STATE_RGB_WRITE
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
						s_renderCtx.setBlendState(newFlags, state.m_rgba);
					}

					if ( (BGFX_STATE_CULL_MASK|BGFX_STATE_MSAA) & changedFlags)
					{
						s_renderCtx.setRasterizerState(newFlags, wireframe, scissorEnabled);
					}

					if (BGFX_STATE_ALPHA_REF_MASK & changedFlags)
					{
						uint32_t ref = (newFlags&BGFX_STATE_ALPHA_REF_MASK)>>BGFX_STATE_ALPHA_REF_SHIFT;
						alphaRef = ref/255.0f;
					}

					uint8_t primIndex = uint8_t( (newFlags&BGFX_STATE_PT_MASK)>>BGFX_STATE_PT_SHIFT);
					if (primType != s_primType[primIndex])
					{
						primType = s_primType[primIndex];
						primNumVerts = 3-primIndex;
						deviceCtx->IASetPrimitiveTopology(primType);
					}
				}

				bool programChanged = false;
				bool constantsChanged = state.m_constBegin < state.m_constEnd;
				rendererUpdateUniforms(m_render->m_constantBuffer, state.m_constBegin, state.m_constEnd);

				if (key.m_program != programIdx)
				{
					programIdx = key.m_program;

					if (invalidHandle == programIdx)
					{
						s_renderCtx.m_currentProgram = NULL;

						deviceCtx->VSSetShader(NULL, 0, 0);
						deviceCtx->PSSetShader(NULL, 0, 0);
					}
					else
					{
						Program& program = s_renderCtx.m_program[programIdx];
						s_renderCtx.m_currentProgram = &program;

						deviceCtx->VSSetShader( (ID3D11VertexShader*)program.m_vsh->m_ptr, NULL, 0);
						deviceCtx->VSSetConstantBuffers(0, 1, &program.m_vsh->m_buffer);

						deviceCtx->PSSetShader( (ID3D11PixelShader*)program.m_fsh->m_ptr, NULL, 0);
						deviceCtx->PSSetConstantBuffers(0, 1, &program.m_fsh->m_buffer);
					}

					programChanged = 
						constantsChanged = true;
				}

				if (invalidHandle != programIdx)
				{
					Program& program = s_renderCtx.m_program[programIdx];

					if (constantsChanged)
					{
						program.commit();
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
								rect[0] = m_render->m_rect[view].m_x;
								rect[1] = m_render->m_rect[view].m_y;
								rect[2] = m_render->m_rect[view].m_width;
								rect[3] = m_render->m_rect[view].m_height;

								s_renderCtx.setShaderConstant(flags, predefined.m_loc, &rect[0], 1);
							}
							break;

						case PredefinedUniform::ViewTexel:
							{
								float rect[4];
								rect[0] = 1.0f/float(m_render->m_rect[view].m_width);
								rect[1] = 1.0f/float(m_render->m_rect[view].m_height);

								s_renderCtx.setShaderConstant(flags, predefined.m_loc, &rect[0], 1);
							}
							break;

						case PredefinedUniform::View:
							{
								s_renderCtx.setShaderConstant(flags, predefined.m_loc, m_render->m_view[view].val, bx::uint32_min(4, predefined.m_count) );
							}
							break;

						case PredefinedUniform::ViewProj:
							{
								s_renderCtx.setShaderConstant(flags, predefined.m_loc, viewProj[view].val, bx::uint32_min(4, predefined.m_count) );
							}
							break;

						case PredefinedUniform::Model:
							{
								const Matrix4& model = m_render->m_matrixCache.m_cache[state.m_matrix];
								s_renderCtx.setShaderConstant(flags, predefined.m_loc, model.val, bx::uint32_min(state.m_num*4, predefined.m_count) );
							}
							break;

						case PredefinedUniform::ModelView:
							{
								Matrix4 modelView;
								const Matrix4& model = m_render->m_matrixCache.m_cache[state.m_matrix];
								mtxMul(modelView.val, model.val, m_render->m_view[view].val);
								s_renderCtx.setShaderConstant(flags, predefined.m_loc, modelView.val, bx::uint32_min(4, predefined.m_count) );
							}
							break;

						case PredefinedUniform::ModelViewProj:
							{
								Matrix4 modelViewProj;
								const Matrix4& model = m_render->m_matrixCache.m_cache[state.m_matrix];
								mtxMul(modelViewProj.val, model.val, viewProj[view].val);
								s_renderCtx.setShaderConstant(flags, predefined.m_loc, modelViewProj.val, bx::uint32_min(4, predefined.m_count) );
							}
							break;

						case PredefinedUniform::ModelViewProjX:
							{
								const Matrix4& model = m_render->m_matrixCache.m_cache[state.m_matrix];

								static const BX_ALIGN_STRUCT_16(float) s_bias[16] =
								{
									0.5f, 0.0f, 0.0f, 0.0f,
									0.0f, 0.5f, 0.0f, 0.0f,
									0.0f, 0.0f, 0.5f, 0.0f,
									0.5f, 0.5f, 0.5f, 1.0f,
								};

								uint8_t other = m_render->m_other[view];
								Matrix4 viewProjBias;
								mtxMul(viewProjBias.val, viewProj[other].val, s_bias);

								Matrix4 modelViewProj;
								mtxMul(modelViewProj.val, model.val, viewProjBias.val);

								s_renderCtx.setShaderConstant(flags, predefined.m_loc, modelViewProj.val, bx::uint32_min(4, predefined.m_count) );
							}
							break;

						case PredefinedUniform::ViewProjX:
							{
								static const BX_ALIGN_STRUCT_16(float) s_bias[16] =
								{
									0.5f, 0.0f, 0.0f, 0.0f,
									0.0f, 0.5f, 0.0f, 0.0f,
									0.0f, 0.0f, 0.5f, 0.0f,
									0.5f, 0.5f, 0.5f, 1.0f,
								};

								uint8_t other = m_render->m_other[view];
								Matrix4 viewProjBias;
								mtxMul(viewProjBias.val, viewProj[other].val, s_bias);

								s_renderCtx.setShaderConstant(flags, predefined.m_loc, viewProjBias.val, bx::uint32_min(4, predefined.m_count) );
							}
							break;

						case PredefinedUniform::AlphaRef:
							{
								s_renderCtx.setShaderConstant(flags, predefined.m_loc, &alphaRef, 1);
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
						s_renderCtx.commitShaderConstants();
					}
				}

//				if (BGFX_STATE_TEX_MASK & changedFlags)
				{
					uint32_t changes = 0;
					uint64_t flag = BGFX_STATE_TEX0;
					for (uint32_t stage = 0; stage < BGFX_STATE_TEX_COUNT; ++stage)
					{
						const Sampler& sampler = state.m_sampler[stage];
						Sampler& current = currentState.m_sampler[stage];
						if (current.m_idx != sampler.m_idx
						||  current.m_flags != sampler.m_flags
						||  programChanged)
						{
							if (invalidHandle != sampler.m_idx)
							{
								switch (sampler.m_flags&BGFX_SAMPLER_TYPE_MASK)
								{
								case BGFX_SAMPLER_TEXTURE:
									{
										Texture& texture = s_renderCtx.m_textures[sampler.m_idx];
										texture.commit(stage, sampler.m_flags);
									}
									break;

								case BGFX_SAMPLER_RENDERTARGET_COLOR:
									{
										RenderTarget& rt = s_renderCtx.m_renderTargets[sampler.m_idx];
										rt.commit(stage, sampler.m_flags);
									}
									break;

								case BGFX_SAMPLER_RENDERTARGET_DEPTH:
									{
//										id = s_renderCtx.m_renderTargets[sampler.m_idx].m_depth.m_id;
									}
									break;
								}
							}
							else
							{
								s_renderCtx.m_textureStage.m_srv[stage] = NULL;
								s_renderCtx.m_textureStage.m_sampler[stage] = NULL;
							}

							++changes;
						}

						current = sampler;
						flag <<= 1;
					}

					if (0 < changes)
					{
						s_renderCtx.commitTextureStage();
					}
				}

				if (programChanged
				||  currentState.m_vertexBuffer.idx != state.m_vertexBuffer.idx
				||  currentState.m_instanceDataBuffer.idx != state.m_instanceDataBuffer.idx
				||  currentState.m_instanceDataOffset != state.m_instanceDataOffset
				||  currentState.m_instanceDataStride != state.m_instanceDataStride)
				{
					currentState.m_vertexBuffer = state.m_vertexBuffer;
					currentState.m_instanceDataBuffer.idx = state.m_instanceDataBuffer.idx;
					currentState.m_instanceDataOffset = state.m_instanceDataOffset;
					currentState.m_instanceDataStride = state.m_instanceDataStride;

					uint16_t handle = state.m_vertexBuffer.idx;
					if (invalidHandle != handle)
					{
						const VertexBuffer& vb = s_renderCtx.m_vertexBuffers[handle];

						uint16_t decl = vb.m_decl.idx == invalidHandle ? state.m_vertexDecl.idx : vb.m_decl.idx;
						const VertexDecl& vertexDecl = s_renderCtx.m_vertexDecls[decl];
						uint32_t stride = vertexDecl.m_stride;
						uint32_t offset = 0;
						deviceCtx->IASetVertexBuffers(0, 1, &vb.m_ptr, &stride, &offset);

						if (invalidHandle != state.m_instanceDataBuffer.idx)
						{
 							const VertexBuffer& inst = s_renderCtx.m_vertexBuffers[state.m_instanceDataBuffer.idx];
							uint32_t instStride = state.m_instanceDataStride;
							deviceCtx->IASetVertexBuffers(1, 1, &inst.m_ptr, &instStride, &state.m_instanceDataOffset);
							s_renderCtx.setInputLayout(vertexDecl, s_renderCtx.m_program[programIdx], state.m_instanceDataStride/16);
						}
						else
						{
							deviceCtx->IASetVertexBuffers(1, 0, NULL, NULL, NULL);
							s_renderCtx.setInputLayout(vertexDecl, s_renderCtx.m_program[programIdx], 0);
						}
					}
					else
					{
						deviceCtx->IASetVertexBuffers(0, 0, NULL, NULL, NULL);
					}
				}

				if (currentState.m_indexBuffer.idx != state.m_indexBuffer.idx)
				{
					currentState.m_indexBuffer = state.m_indexBuffer;

					uint16_t handle = state.m_indexBuffer.idx;
					if (invalidHandle != handle)
					{
						const IndexBuffer& ib = s_renderCtx.m_indexBuffers[handle];
						deviceCtx->IASetIndexBuffer(ib.m_ptr, DXGI_FORMAT_R16_UINT, 0);
					}
					else
					{
						deviceCtx->IASetIndexBuffer(NULL, DXGI_FORMAT_R16_UINT, 0);
					}
				}

				if (invalidHandle != currentState.m_vertexBuffer.idx)
				{
					uint32_t numVertices = state.m_numVertices;
					if (UINT32_C(0xffffffff) == numVertices)
					{
						const VertexBuffer& vb = s_renderCtx.m_vertexBuffers[currentState.m_vertexBuffer.idx];
						uint16_t decl = vb.m_decl.idx == invalidHandle ? state.m_vertexDecl.idx : vb.m_decl.idx;
						const VertexDecl& vertexDecl = s_renderCtx.m_vertexDecls[decl];
						numVertices = vb.m_size/vertexDecl.m_stride;
					}

					uint32_t numIndices = 0;
					uint32_t numPrimsSubmitted = 0;
					uint32_t numInstances = 0;
					uint32_t numPrimsRendered = 0;

					if (invalidHandle != state.m_indexBuffer.idx)
					{
						if (UINT32_MAX == state.m_numIndices)
						{
							numIndices = s_renderCtx.m_indexBuffers[state.m_indexBuffer.idx].m_size/2;
							numPrimsSubmitted = numIndices/primNumVerts;
							numInstances = state.m_numInstances;
							numPrimsRendered = numPrimsSubmitted*state.m_numInstances;

							deviceCtx->DrawIndexedInstanced(numIndices
								, state.m_numInstances
								, 0
								, state.m_startVertex
								, 0
								);
						}
						else if (primNumVerts <= state.m_numIndices)
						{
							numIndices = state.m_numIndices;
							numPrimsSubmitted = numIndices/primNumVerts;
							numInstances = state.m_numInstances;
							numPrimsRendered = numPrimsSubmitted*state.m_numInstances;

							deviceCtx->DrawIndexedInstanced(numIndices
								, state.m_numInstances
								, state.m_startIndex
								, state.m_startVertex
								, 0
								);
						}
					}
					else
					{
						numPrimsSubmitted = numVertices/primNumVerts;
						numInstances = state.m_numInstances;
						numPrimsRendered = numPrimsSubmitted*state.m_numInstances;

						deviceCtx->DrawInstanced(numVertices
							, state.m_numInstances
							, state.m_startVertex
							, 0
							);
					}

					statsNumPrimsSubmitted += numPrimsSubmitted;
					statsNumIndices += numIndices;
					statsNumInstances += numInstances;
					statsNumPrimsRendered += numPrimsRendered;
				}
			}

			if (0 < m_render->m_num)
			{
				captureElapsed = -bx::getHPCounter();
				s_renderCtx.capture();
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

		if (m_render->m_debug & (BGFX_DEBUG_IFH|BGFX_DEBUG_STATS) )
		{
			PIX_BEGINEVENT(D3DCOLOR_RGBA(0x40, 0x40, 0x40, 0xff), L"debugstats");

			TextVideoMem& tvm = s_renderCtx.m_textVideoMem;

			static int64_t next = now;

			if (now >= next)
			{
				next = now + bx::getHPFrequency();
				double freq = double(bx::getHPFrequency() );
				double toMs = 1000.0/freq;

				tvm.clear();
				uint16_t pos = 0;
				tvm.printf(0, pos++, BGFX_CONFIG_DEBUG ? 0x89 : 0x8f, " " BGFX_RENDERER_NAME " ");

				const DXGI_ADAPTER_DESC& desc = s_renderCtx.m_adapterDesc;
				char description[BX_COUNTOF(desc.Description)];
				wcstombs(description, desc.Description, BX_COUNTOF(desc.Description) );
				tvm.printf(0, pos++, 0x0f, " Device: %s", description);
				tvm.printf(0, pos++, 0x0f, " Memory: %" PRIi64 " (video), %" PRIi64 " (system), %" PRIi64 " (shared)"
					, desc.DedicatedVideoMemory
					, desc.DedicatedSystemMemory
					, desc.SharedSystemMemory
					);

				pos = 10;
				tvm.printf(10, pos++, 0x8e, "      Frame: %7.3f, % 7.3f \x1f, % 7.3f \x1e [ms] / % 6.2f FPS%s"
					, double(frameTime)*toMs
					, double(min)*toMs
					, double(max)*toMs
					, freq/frameTime
					, !!(m_resolution.m_flags&BGFX_RESET_VSYNC) ? " (vsync)" : ""
					);

				double elapsedCpuMs = double(elapsed)*toMs;
				tvm.printf(10, pos++, 0x8e, " Draw calls: %4d / CPU %3.4f [ms]"
					, m_render->m_num
					, elapsedCpuMs
					);
				tvm.printf(10, pos++, 0x8e, "      Prims: %7d (#inst: %5d), submitted: %7d"
					, statsNumPrimsRendered
					, statsNumInstances
					, statsNumPrimsSubmitted
					);

				double captureMs = double(captureElapsed)*toMs;
				tvm.printf(10, pos++, 0x8e, "    Capture: %3.4f [ms]", captureMs);
				tvm.printf(10, pos++, 0x8e, "    Indices: %7d", statsNumIndices);
				tvm.printf(10, pos++, 0x8e, "   DVB size: %7d", m_render->m_vboffset);
				tvm.printf(10, pos++, 0x8e, "   DIB size: %7d", m_render->m_iboffset);

				uint8_t attr[2] = { 0x89, 0x8a };
				uint8_t attrIndex = m_render->m_waitSubmit < m_render->m_waitRender;

				tvm.printf(10, pos++, attr[attrIndex&1], "Submit wait: %3.4f [ms]", m_render->m_waitSubmit*toMs);
				tvm.printf(10, pos++, attr[(attrIndex+1)&1], "Render wait: %3.4f [ms]", m_render->m_waitRender*toMs);

				min = frameTime;
				max = frameTime;
			}

			m_textVideoMemBlitter.blit(tvm);

			PIX_ENDEVENT();
		}
		else if (m_render->m_debug & BGFX_DEBUG_TEXT)
		{
			PIX_BEGINEVENT(D3DCOLOR_RGBA(0x40, 0x40, 0x40, 0xff), L"debugtext");

			m_textVideoMemBlitter.blit(m_render->m_textVideoMem);

			PIX_ENDEVENT();
		}
	}
}

#endif // BGFX_CONFIG_RENDERER_DIRECT3D11
