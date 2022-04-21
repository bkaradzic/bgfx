/*
 * Copyright 2011-2019 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "bgfx_p.h"

//#define DAWN_ENABLE_BACKEND_D3D12
#define DAWN_ENABLE_BACKEND_VULKAN

#if BGFX_CONFIG_RENDERER_WEBGPU
#	include "renderer_webgpu.h"
#	include "renderer.h"
#	include "debug_renderdoc.h"
#	include "emscripten.h"
#	include "shader_spirv.h"

#	if BX_PLATFORM_ANDROID
#		define VK_USE_PLATFORM_ANDROID_KHR
#	elif BX_PLATFORM_LINUX
#		define VK_USE_PLATFORM_XLIB_KHR
#		define VK_USE_PLATFORM_XCB_KHR
#	elif BX_PLATFORM_WINDOWS
#		define VK_USE_PLATFORM_WIN32_KHR
#	elif BX_PLATFORM_OSX
#		define VK_USE_PLATFORM_MACOS_MVK
#	endif // BX_PLATFORM_*

#	define VK_NO_STDINT_H
#	define VK_NO_PROTOTYPES
#	include <vulkan-local/vulkan.h>

#	if BX_PLATFORM_EMSCRIPTEN
#		include "emscripten.h"
#		include "emscripten/html5_webgpu.h"
#	else
#		ifdef DAWN_ENABLE_BACKEND_D3D12
#			include <dawn_native/D3D12Backend.h>
#		endif // !BX_PLATFORM_EMSCRIPTEN

#		ifdef DAWN_ENABLE_BACKEND_VULKAN
#			include <dawn_native/VulkanBackend.h>
#		endif // DAWN_ENABLE_BACKEND_VULKAN

#		include <dawn_native/DawnNative.h>
#		include <dawn/dawn_wsi.h>
#		include <dawn/dawn_proc.h>
#	endif // !BX_PLATFORM_EMSCRIPTEN

namespace bgfx { namespace webgpu
{
	// TODO (hugoam) cleanup
	template <class T>
	T defaultDescriptor() { return T(); }

	template <> wgpu::BlendComponent			   defaultDescriptor() { return { wgpu::BlendOperation::Add, wgpu::BlendFactor::One, wgpu::BlendFactor::Zero }; }
	template <> wgpu::ColorTargetState             defaultDescriptor() { return { NULL, wgpu::TextureFormat::RGBA8Unorm, NULL, wgpu::ColorWriteMask::All }; }
	template <> wgpu::StencilFaceState			   defaultDescriptor() { return { wgpu::CompareFunction::Always, wgpu::StencilOperation::Keep, wgpu::StencilOperation::Keep, wgpu::StencilOperation::Keep }; }
	template <> wgpu::VertexState				   defaultDescriptor() { return { NULL, {}, "main", 0, NULL }; }
	template <> wgpu::FragmentState				   defaultDescriptor() { return { NULL, {}, "main", 0, NULL }; }
	template <> wgpu::VertexBufferLayout		   defaultDescriptor() { return { 0, wgpu::InputStepMode::Vertex, 0, NULL }; }
	template <> wgpu::VertexAttribute			   defaultDescriptor() { return { wgpu::VertexFormat::Float, 0, 0 }; }
	template <> wgpu::PrimitiveState			   defaultDescriptor() { return { NULL, wgpu::PrimitiveTopology::TriangleList, wgpu::IndexFormat::Undefined, wgpu::FrontFace::CCW, wgpu::CullMode::None }; }
	template <> wgpu::DepthStencilState			   defaultDescriptor() { return { NULL, wgpu::TextureFormat::Depth24PlusStencil8, false, wgpu::CompareFunction::Always, defaultDescriptor<wgpu::StencilFaceState>(), defaultDescriptor<wgpu::StencilFaceState>(), 0xff, 0xff }; }
	template <> wgpu::PipelineLayoutDescriptor     defaultDescriptor() { return { NULL, "", 0, NULL }; }
	template <> wgpu::TextureViewDescriptor        defaultDescriptor() { return {}; }

	template <> wgpu::RenderPassColorAttachment defaultDescriptor() { return { {}, {}, wgpu::LoadOp::Clear, wgpu::StoreOp::Store, { 0.0f, 0.0f, 0.0f, 0.0f } }; }
	template <> wgpu::RenderPassDepthStencilAttachment defaultDescriptor() { return { {}, wgpu::LoadOp::Clear, wgpu::StoreOp::Store, 1.0f, false, wgpu::LoadOp::Clear, wgpu::StoreOp::Store, 0, false }; }

	RenderPassDescriptor::RenderPassDescriptor()
	{
		depthStencilAttachment = defaultDescriptor<wgpu::RenderPassDepthStencilAttachment>();

		for(uint32_t i = 0; i < kMaxColorAttachments; ++i)
		{
			colorAttachments[i] = defaultDescriptor<wgpu::RenderPassColorAttachment>();
		}

		desc = defaultDescriptor<wgpu::RenderPassDescriptor>();
		//desc.colorAttachmentCount = colorAttachmentCount;
		desc.colorAttachments = colorAttachments;
		desc.colorAttachmentCount = 1; // TODO (hugoam) set it properly everywhere
	}

	VertexStateDescriptor::VertexStateDescriptor()
	{
		for(uint32_t i = 0; i < kMaxVertexInputs; ++i)
		{
			buffers[i] = defaultDescriptor<wgpu::VertexBufferLayout>();
		}

		for (uint32_t i = 0; i < kMaxVertexAttributes; ++i)
		{
			attributes[i] = defaultDescriptor<wgpu::VertexAttribute>();
		}

		buffers[0].attributes = &attributes[0];
		//buffers[0].attributeCount = numAttributes;

		desc = defaultDescriptor<wgpu::VertexState>();

		desc.buffers = buffers;
		//desc.vertexBufferCount = numVertexBuffers;
	}

	RenderPipelineDescriptor::RenderPipelineDescriptor()
	{
		//vertex = defaultDescriptor<wgpu::VertexState>();
		fragment = defaultDescriptor<wgpu::FragmentState>();
		depthStencil = defaultDescriptor<wgpu::DepthStencilState>();

		for(uint32_t i = 0; i < kMaxColorAttachments; ++i)
		{
			targets[i] = defaultDescriptor<wgpu::ColorTargetState>();
		}

		desc = defaultDescriptor<wgpu::RenderPipelineDescriptor2>();

		desc.primitive.topology = wgpu::PrimitiveTopology::TriangleList;
		desc.multisample.count = 1;

		fragment.targetCount = 1;
		fragment.targets = targets;

		//wgpu::VertexStateDescriptor inputState = inputState.descriptor();

		desc.vertex = defaultDescriptor<wgpu::VertexState>();
		desc.fragment = NULL;
		//desc.vertexState = &inputState;
		desc.primitive = defaultDescriptor<wgpu::PrimitiveState>();
		desc.depthStencil = NULL;
	}
	// TODO (hugoam) cleanup (end)

	static char s_viewName[BGFX_CONFIG_MAX_VIEWS][BGFX_CONFIG_MAX_VIEW_NAME];

	inline void setViewType(ViewId _view, const bx::StringView _str)
	{
		if (BX_ENABLED(BGFX_CONFIG_DEBUG_ANNOTATION || BGFX_CONFIG_PROFILER) )
		{
			bx::memCopy(&s_viewName[_view][3], _str.getPtr(), _str.getLength() );
		}
	}

	struct PrimInfo
	{
		wgpu::PrimitiveTopology m_type;
		uint32_t m_min;
		uint32_t m_div;
		uint32_t m_sub;
	};

	static const PrimInfo s_primInfo[] =
	{
		{ wgpu::PrimitiveTopology::TriangleList,  3, 3, 0 },
		{ wgpu::PrimitiveTopology::TriangleStrip, 3, 1, 2 },
		{ wgpu::PrimitiveTopology::LineList,      2, 2, 0 },
		{ wgpu::PrimitiveTopology::LineStrip,     2, 1, 1 },
		{ wgpu::PrimitiveTopology::PointList,     1, 1, 0 },
	};
	BX_STATIC_ASSERT(Topology::Count == BX_COUNTOF(s_primInfo) );

	static const wgpu::VertexFormat s_attribType[][4][2] =
	{
		{ // Uint8
			{ wgpu::VertexFormat::Uint8x2, wgpu::VertexFormat::Unorm8x2 },
			{ wgpu::VertexFormat::Uint8x2, wgpu::VertexFormat::Unorm8x2 },
			{ wgpu::VertexFormat::Uint8x4, wgpu::VertexFormat::Unorm8x4 },
			{ wgpu::VertexFormat::Uint8x4, wgpu::VertexFormat::Unorm8x4 },
		},
		{ // Uint10
			{ wgpu::VertexFormat::Uint16x2, wgpu::VertexFormat::Unorm16x2 },
			{ wgpu::VertexFormat::Uint16x2, wgpu::VertexFormat::Unorm16x2 },
			{ wgpu::VertexFormat::Uint16x4, wgpu::VertexFormat::Unorm16x4 },
			{ wgpu::VertexFormat::Uint16x4, wgpu::VertexFormat::Unorm16x4 },
		},
		{ // Int16
			{ wgpu::VertexFormat::Sint16x2, wgpu::VertexFormat::Snorm16x2 },
			{ wgpu::VertexFormat::Sint16x2, wgpu::VertexFormat::Snorm16x2 },
			{ wgpu::VertexFormat::Sint16x4, wgpu::VertexFormat::Snorm16x4 },
			{ wgpu::VertexFormat::Sint16x4, wgpu::VertexFormat::Snorm16x4 },
		},
		{ // Half
			{ wgpu::VertexFormat::Float16x2, wgpu::VertexFormat::Float16x2 },
			{ wgpu::VertexFormat::Float16x2, wgpu::VertexFormat::Float16x2 },
			{ wgpu::VertexFormat::Float16x4, wgpu::VertexFormat::Float16x4 },
			{ wgpu::VertexFormat::Float16x4, wgpu::VertexFormat::Float16x4 },
		},
		{ // Float
			{ wgpu::VertexFormat::Float32,   wgpu::VertexFormat::Float32  },
			{ wgpu::VertexFormat::Float32x2, wgpu::VertexFormat::Float32x2 },
			{ wgpu::VertexFormat::Float32x3, wgpu::VertexFormat::Float32x3 },
			{ wgpu::VertexFormat::Float32x4, wgpu::VertexFormat::Float32x4 },
		},
	};
	BX_STATIC_ASSERT(AttribType::Count == BX_COUNTOF(s_attribType) );

	static const wgpu::CullMode s_cullMode[] =
	{
		wgpu::CullMode::None,
		wgpu::CullMode::Front,
		wgpu::CullMode::Back,
		wgpu::CullMode::None,
	};

	static const wgpu::BlendFactor s_blendFactor[][2] =
	{
		{ wgpu::BlendFactor(0),                  wgpu::BlendFactor(0)                  }, // ignored
		{ wgpu::BlendFactor::Zero,               wgpu::BlendFactor::Zero               }, // ZERO
		{ wgpu::BlendFactor::One,                wgpu::BlendFactor::One                }, // ONE
		{ wgpu::BlendFactor::SrcColor,           wgpu::BlendFactor::SrcAlpha           }, // SRC_COLOR
		{ wgpu::BlendFactor::OneMinusSrcColor,   wgpu::BlendFactor::OneMinusSrcAlpha   }, // INV_SRC_COLOR
		{ wgpu::BlendFactor::SrcAlpha,           wgpu::BlendFactor::SrcAlpha           }, // SRC_ALPHA
		{ wgpu::BlendFactor::OneMinusSrcAlpha,   wgpu::BlendFactor::OneMinusSrcAlpha   }, // INV_SRC_ALPHA
		{ wgpu::BlendFactor::DstAlpha,           wgpu::BlendFactor::DstAlpha           }, // DST_ALPHA
		{ wgpu::BlendFactor::OneMinusDstAlpha,   wgpu::BlendFactor::OneMinusDstAlpha   }, // INV_DST_ALPHA
		{ wgpu::BlendFactor::DstColor,           wgpu::BlendFactor::DstAlpha           }, // DST_COLOR
		{ wgpu::BlendFactor::OneMinusDstColor,   wgpu::BlendFactor::OneMinusDstAlpha   }, // INV_DST_COLOR
		{ wgpu::BlendFactor::SrcAlphaSaturated,  wgpu::BlendFactor::One                }, // SRC_ALPHA_SAT
		{ wgpu::BlendFactor::BlendColor,         wgpu::BlendFactor::BlendColor         }, // FACTOR
		{ wgpu::BlendFactor::OneMinusBlendColor, wgpu::BlendFactor::OneMinusBlendColor }, // INV_FACTOR
	};

	static const wgpu::BlendOperation s_blendEquation[] =
	{
		wgpu::BlendOperation::Add,
		wgpu::BlendOperation::Subtract,
		wgpu::BlendOperation::ReverseSubtract,
		wgpu::BlendOperation::Min,
		wgpu::BlendOperation::Max,
	};

	static const wgpu::CompareFunction s_cmpFunc[] =
	{
		wgpu::CompareFunction::Always, // ignored
		wgpu::CompareFunction::Less,
		wgpu::CompareFunction::LessEqual,
		wgpu::CompareFunction::Equal,
		wgpu::CompareFunction::GreaterEqual,
		wgpu::CompareFunction::Greater,
		wgpu::CompareFunction::NotEqual,
		wgpu::CompareFunction::Never,
		wgpu::CompareFunction::Always,
	};

	static const wgpu::StencilOperation s_stencilOp[] =
	{
		wgpu::StencilOperation::Zero,
		wgpu::StencilOperation::Keep,
		wgpu::StencilOperation::Replace,
		wgpu::StencilOperation::IncrementWrap,
		wgpu::StencilOperation::IncrementClamp,
		wgpu::StencilOperation::DecrementWrap,
		wgpu::StencilOperation::DecrementClamp,
		wgpu::StencilOperation::Invert,
	};

	static const wgpu::AddressMode s_textureAddress[] =
	{
		wgpu::AddressMode::Repeat,
		wgpu::AddressMode::MirrorRepeat,
		wgpu::AddressMode::ClampToEdge,
		wgpu::AddressMode(0), // Border ? ClampToZero ?
	};

	static const wgpu::FilterMode s_textureFilterMinMag[] =
	{
		wgpu::FilterMode::Linear,
		wgpu::FilterMode::Nearest,
		wgpu::FilterMode::Linear,
	};

	static const wgpu::FilterMode s_textureFilterMip[] =
	{
		wgpu::FilterMode::Linear,
		wgpu::FilterMode::Nearest,
	};

	struct TextureFormatInfo
	{
		wgpu::TextureFormat m_fmt;
		wgpu::TextureFormat m_fmtSrgb;
	};

	static TextureFormatInfo s_textureFormat[] =
	{
		{ wgpu::TextureFormat::BC1RGBAUnorm,        wgpu::TextureFormat::BC1RGBAUnormSrgb },  // BC1
		{ wgpu::TextureFormat::BC2RGBAUnorm,        wgpu::TextureFormat::BC2RGBAUnormSrgb },  // BC2
		{ wgpu::TextureFormat::BC3RGBAUnorm,        wgpu::TextureFormat::BC3RGBAUnormSrgb },  // BC3
		{ wgpu::TextureFormat::BC4RUnorm,           wgpu::TextureFormat::Undefined        },  // BC4  //  BC4RSnorm ??
		{ wgpu::TextureFormat::BC5RGUnorm,          wgpu::TextureFormat::Undefined        },  // BC5  //  BC5RGSnorm ??
		{ wgpu::TextureFormat::BC6HRGBUfloat,       wgpu::TextureFormat::Undefined        },  // BC6H //  BC6HRGBSfloat ??
		{ wgpu::TextureFormat::BC7RGBAUnorm,        wgpu::TextureFormat::BC7RGBAUnormSrgb },  // BC7
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // ETC1
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // ETC2
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // ETC2A
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // ETC2A1
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // PTC12
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // PTC14
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // PTC12A
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // PTC14A
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // PTC22
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // PTC24
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // ATC
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // ATCE
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // ATCI
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // ASTC4x4
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // ASTC5x5
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // ASTC6x6
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // ASTC8x5
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // ASTC8x6
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // ASTC10x5
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // Unknown
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // R1
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // A8
		{ wgpu::TextureFormat::R8Unorm,             wgpu::TextureFormat::Undefined        },  // R8
		{ wgpu::TextureFormat::R8Sint,              wgpu::TextureFormat::Undefined        },  // R8I
		{ wgpu::TextureFormat::R8Uint,              wgpu::TextureFormat::Undefined        },  // R8U
		{ wgpu::TextureFormat::R8Snorm,             wgpu::TextureFormat::Undefined        },  // R8S
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // R16
		{ wgpu::TextureFormat::R16Sint,             wgpu::TextureFormat::Undefined        },  // R16I
		{ wgpu::TextureFormat::R16Uint,             wgpu::TextureFormat::Undefined        },  // R16U
		{ wgpu::TextureFormat::R16Float,            wgpu::TextureFormat::Undefined        },  // R16F
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // R16S
		{ wgpu::TextureFormat::R32Sint,             wgpu::TextureFormat::Undefined        },  // R32I
		{ wgpu::TextureFormat::R32Uint,             wgpu::TextureFormat::Undefined        },  // R32U
		{ wgpu::TextureFormat::R32Float,            wgpu::TextureFormat::Undefined        },  // R32F
		{ wgpu::TextureFormat::RG8Unorm,            wgpu::TextureFormat::Undefined        },  // RG8
		{ wgpu::TextureFormat::RG8Sint,             wgpu::TextureFormat::Undefined        },  // RG8I
		{ wgpu::TextureFormat::RG8Uint,             wgpu::TextureFormat::Undefined        },  // RG8U
		{ wgpu::TextureFormat::RG8Snorm,            wgpu::TextureFormat::Undefined        },  // RG8S
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // RG16
		{ wgpu::TextureFormat::RG16Sint,            wgpu::TextureFormat::Undefined        },  // RG16I
		{ wgpu::TextureFormat::RG16Uint,            wgpu::TextureFormat::Undefined        },  // RG16U
		{ wgpu::TextureFormat::RG16Float,           wgpu::TextureFormat::Undefined        },  // RG16F
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // RG16S
		{ wgpu::TextureFormat::RG32Sint,            wgpu::TextureFormat::Undefined        },  // RG32I
		{ wgpu::TextureFormat::RG32Uint,            wgpu::TextureFormat::Undefined        },  // RG32U
		{ wgpu::TextureFormat::RG32Float,           wgpu::TextureFormat::Undefined        },  // RG32F
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // RGB8
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // RGB8I
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // RGB8U
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // RGB8S
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // RGB9E5F
		{ wgpu::TextureFormat::BGRA8Unorm,          wgpu::TextureFormat::BGRA8UnormSrgb   },  // BGRA8
		{ wgpu::TextureFormat::RGBA8Unorm,          wgpu::TextureFormat::RGBA8UnormSrgb   },  // RGBA8
		{ wgpu::TextureFormat::RGBA8Sint,           wgpu::TextureFormat::Undefined        },  // RGBA8I
		{ wgpu::TextureFormat::RGBA8Uint,           wgpu::TextureFormat::Undefined        },  // RGBA8U
		{ wgpu::TextureFormat::RGBA8Snorm,          wgpu::TextureFormat::Undefined        },  // RGBA8S
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // RGBA16
		{ wgpu::TextureFormat::RGBA16Sint,          wgpu::TextureFormat::Undefined        },  // RGBA16I
		{ wgpu::TextureFormat::RGBA16Uint,          wgpu::TextureFormat::Undefined        },  // RGBA16U
		{ wgpu::TextureFormat::RGBA16Float,         wgpu::TextureFormat::Undefined        },  // RGBA16F
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // RGBA16S
		{ wgpu::TextureFormat::RGBA32Sint,          wgpu::TextureFormat::Undefined        },  // RGBA32I
		{ wgpu::TextureFormat::RGBA32Uint,          wgpu::TextureFormat::Undefined        },  // RGBA32U
		{ wgpu::TextureFormat::RGBA32Float,         wgpu::TextureFormat::Undefined        },  // RGBA32F
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // R5G6B5
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // RGBA4
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // RGB5A1
		{ wgpu::TextureFormat::RGB10A2Unorm,        wgpu::TextureFormat::Undefined        },  // RGB10A2
		{ wgpu::TextureFormat::RG11B10Ufloat,       wgpu::TextureFormat::Undefined        },  // RG11B10F
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // UnknownDepth
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // D16
		{ wgpu::TextureFormat::Depth24Plus,         wgpu::TextureFormat::Undefined        },  // D24
		{ wgpu::TextureFormat::Depth24PlusStencil8, wgpu::TextureFormat::Undefined        },  // D24S8
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // D32
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // D16F
		{ wgpu::TextureFormat::Undefined,           wgpu::TextureFormat::Undefined        },  // D24F
		{ wgpu::TextureFormat::Depth32Float,        wgpu::TextureFormat::Undefined        },  // D32F
		{ wgpu::TextureFormat::Stencil8,            wgpu::TextureFormat::Undefined        },  // D0S8
	};
	BX_STATIC_ASSERT(TextureFormat::Count == BX_COUNTOF(s_textureFormat));

	int32_t s_msaa[] =
	{
		 1,
		 2,
		 4,
		 8,
		16,
	};

	struct RendererContextWgpu;
	static RendererContextWgpu* s_renderWgpu;

	static bool s_ignoreError = false;

#if !BX_PLATFORM_EMSCRIPTEN
	DawnSwapChainImplementation(*createSwapChain)(wgpu::Device device, void* nwh);

#	if defined(DAWN_ENABLE_BACKEND_D3D12)
	DawnSwapChainImplementation CreateSwapChainD3D12(wgpu::Device device, void* nwh)
	{
		HWND win32Window = (HWND)nwh;
		return dawn_native::d3d12::CreateNativeSwapChainImpl(device.Get(), win32Window);
	}
#	endif // defined(DAWN_ENABLE_BACKEND_D3D12)

#	if defined(DAWN_ENABLE_BACKEND_VULKAN)
	DawnSwapChainImplementation CreateSwapChainVulkan(wgpu::Device device, void* nwh)
	{
		VkInstance instance = dawn_native::vulkan::GetInstance(device.Get());

		PFN_vkCreateWin32SurfaceKHR vkCreateWin32SurfaceKHR = (PFN_vkCreateWin32SurfaceKHR)dawn_native::vulkan::GetInstanceProcAddr(device.Get(), "vkCreateWin32SurfaceKHR");

		VkSurfaceKHR surface;
#		if BX_PLATFORM_WINDOWS
		// Copied from renderer_vk.cpp -> needs refactor
		{
			VkWin32SurfaceCreateInfoKHR sci;
			sci.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
			sci.pNext = NULL;
			sci.flags = 0;
			sci.hinstance = (HINSTANCE)GetModuleHandle(NULL);
			sci.hwnd = (HWND)nwh;
			VkResult result = vkCreateWin32SurfaceKHR(instance, &sci, NULL, &surface);
		}
#		endif // BX_PLATFORM_WINDOWS
		return dawn_native::vulkan::CreateNativeSwapChainImpl(device.Get(), surface);
	}
#	endif // defined(DAWN_ENABLE_BACKEND_VULKAN)

#endif // !BX_PLATFORM_EMSCRIPTEN

	struct RendererContextWgpu : public RendererContextI
	{
		RendererContextWgpu()
			: m_frameIndex(0)
			, m_numWindows(0)
			, m_rtMsaa(false)
			, m_capture(NULL)
			, m_captureSize(0)
		{
			bx::memSet(&m_windows, 0xff, sizeof(m_windows) );
		}

		~RendererContextWgpu()
		{
		}

		bool init(const Init& _init)
		{
			BX_UNUSED(_init);
			BX_TRACE("Init.");

			if (_init.debug
			||  _init.profile)
			{
				m_renderDocDll = loadRenderDoc();
			}

			setGraphicsDebuggerPresent(NULL != m_renderDocDll);

			m_fbh.idx = kInvalidHandle;
			bx::memSet(m_uniforms, 0, sizeof(m_uniforms) );
			bx::memSet(&m_resolution, 0, sizeof(m_resolution) );

#if !BX_PLATFORM_EMSCRIPTEN
			// Default to D3D12, Metal, Vulkan, OpenGL in that order as D3D12 and Metal are the preferred on
			// their respective platforms, and Vulkan is preferred to OpenGL
#	if defined(DAWN_ENABLE_BACKEND_D3D12)
			static wgpu::BackendType backendType = wgpu::BackendType::D3D12;
#	elif defined(DAWN_ENABLE_BACKEND_METAL)
			static wgpu::BackendType backendType = wgpu::BackendType::Metal;
#	elif defined(DAWN_ENABLE_BACKEND_OPENGL)
			static wgpu::BackendType backendType = wgpu::BackendType::OpenGL;
#	elif defined(DAWN_ENABLE_BACKEND_VULKAN)
			static wgpu::BackendType backendType = wgpu::BackendType::Vulkan;
#	else
#		error "Unknown platform."
#	endif // defined(DAWN_ENABLE_BACKEND_*)

			if (BX_ENABLED(BGFX_CONFIG_DEBUG))
			{
				m_instance.EnableBackendValidation(true);
			}

			m_instance.DiscoverDefaultAdapters();

			dawn_native::Adapter backendAdapter;
			std::vector<dawn_native::Adapter> adapters = m_instance.GetAdapters();
			for (dawn_native::Adapter& adapter : adapters)
			{
				wgpu::AdapterProperties properties;
				adapter.GetProperties(&properties);
				if (properties.backendType == backendType)
				{
					backendAdapter = adapter;
					break;
				}
			}

			//BX_ASSERT(adapterIt != adapters.end());

			dawn_native::DeviceDescriptor desc;
#	if defined(DAWN_ENABLE_BACKEND_D3D12)
			desc.forceEnabledToggles.push_back("use_dxc");
#	endif

			desc.forceDisabledToggles.push_back("disallow_unsafe_apis");

			WGPUDevice backendDevice = backendAdapter.CreateDevice(&desc);
			DawnProcTable backendProcs = dawn_native::GetProcs();

			using CreateSwapChain = DawnSwapChainImplementation (*)(wgpu::Device device, void* nwh);

#	if defined(DAWN_ENABLE_BACKEND_D3D12)
			createSwapChain = CreateSwapChainD3D12;
#	elif defined(DAWN_ENABLE_BACKEND_METAL)
			createSwapChain = CreateSwapChainMetal;
#	elif defined(DAWN_ENABLE_BACKEND_NULL)
			createSwapChain = CreateSwapChainNull;
#	elif defined(DAWN_ENABLE_BACKEND_OPENGL)
			createSwapChain = CreateSwapChainOpenGL;
#	elif defined(DAWN_ENABLE_BACKEND_VULKAN)
			createSwapChain = CreateSwapChainVulkan;
#	endif // defined(DAWN_ENABLE_BACKEND_*)

			// Choose whether to use the backend procs and devices directly, or set up the wire.
			WGPUDevice cDevice = backendDevice;
			DawnProcTable procs = backendProcs;
			dawnProcSetProcs(&procs);

			m_device = wgpu::Device::Acquire(cDevice);
#else
			m_device = wgpu::Device(emscripten_webgpu_get_device());
#endif // !BX_PLATFORM_EMSCRIPTEN

			auto PrintDeviceError = [](WGPUErrorType errorType, const char* message, void*) {
				BX_UNUSED(errorType);

				if (s_ignoreError)
				{
					BX_TRACE("Device error: %s", message);
				}
				else
				{
					BX_ASSERT(false, "Device error: %s", message);
				}

				s_ignoreError = false;
			};

			if (!m_device)
			{
				BX_WARN(!m_device, "Unable to create WebGPU device.");
				return false;
			}

			m_device.SetUncapturedErrorCallback(PrintDeviceError, NULL);

			bool success = m_mainFrameBuffer.create(
				  0
				, g_platformData.nwh
				, _init.resolution.width
				, _init.resolution.height
				, TextureFormat::Unknown
				, TextureFormat::UnknownDepth
				);
			m_numWindows = 1;

			if (!success)
			{
				return false;
			}

			m_queue = m_device.GetQueue();

			m_cmd.init(m_queue);
			//BGFX_FATAL(NULL != m_cmd.m_commandQueue, Fatal::UnableToInitialize, "Unable to create Metal device.");

			for (uint8_t ii = 0; ii < BGFX_CONFIG_MAX_FRAME_LATENCY; ++ii)
			{
				BX_TRACE("Create scratch buffer %d", ii);
				m_scratchBuffers[ii].create(BGFX_CONFIG_MAX_DRAW_CALLS * 128);
				m_bindStateCache[ii].create(); // (1024);
			}

			for (uint8_t ii = 0; ii < WEBGPU_NUM_UNIFORM_BUFFERS; ++ii)
			{
				bool mapped = true; // ii == WEBGPU_NUM_UNIFORM_BUFFERS - 1;
				m_uniformBuffers[ii].create(BGFX_CONFIG_MAX_DRAW_CALLS * 128, mapped);
			}

			g_caps.supported |= (0
				| BGFX_CAPS_ALPHA_TO_COVERAGE
				| BGFX_CAPS_BLEND_INDEPENDENT
				| BGFX_CAPS_FRAGMENT_DEPTH
				| BGFX_CAPS_INDEX32
				| BGFX_CAPS_INSTANCING
			//	| BGFX_CAPS_OCCLUSION_QUERY
				| BGFX_CAPS_SWAP_CHAIN
				| BGFX_CAPS_TEXTURE_2D_ARRAY
				| BGFX_CAPS_TEXTURE_3D
				| BGFX_CAPS_TEXTURE_BLIT
				| BGFX_CAPS_TEXTURE_COMPARE_ALL
				| BGFX_CAPS_TEXTURE_COMPARE_LEQUAL
				| BGFX_CAPS_TEXTURE_READ_BACK
				| BGFX_CAPS_VERTEX_ATTRIB_HALF
				| BGFX_CAPS_VERTEX_ATTRIB_UINT10
				| BGFX_CAPS_COMPUTE
				);

			g_caps.limits.maxTextureSize   = 8192;
			g_caps.limits.maxFBAttachments = 4;
			g_caps.supported |= BGFX_CAPS_TEXTURE_CUBE_ARRAY;
			g_caps.supported |= BGFX_CAPS_DRAW_INDIRECT;

			g_caps.limits.maxTextureLayers = 2048;
			g_caps.limits.maxVertexStreams = BGFX_CONFIG_MAX_VERTEX_STREAMS;
			// Maximum number of entries in the buffer argument table, per graphics or compute function are 31.
			// It is decremented by 1 because 1 entry is used for uniforms.
			g_caps.limits.maxComputeBindings = bx::uint32_min(30, BGFX_MAX_COMPUTE_BINDINGS);

			for (uint32_t ii = 0; ii < TextureFormat::Count; ++ii)
			{
				uint16_t support = 0;

				support |= wgpu::TextureFormat::Undefined != s_textureFormat[ii].m_fmt
					? BGFX_CAPS_FORMAT_TEXTURE_2D
					| BGFX_CAPS_FORMAT_TEXTURE_3D
					| BGFX_CAPS_FORMAT_TEXTURE_CUBE
					| BGFX_CAPS_FORMAT_TEXTURE_VERTEX
					: BGFX_CAPS_FORMAT_TEXTURE_NONE
					;

				support |= wgpu::TextureFormat::Undefined != s_textureFormat[ii].m_fmtSrgb
					? BGFX_CAPS_FORMAT_TEXTURE_2D_SRGB
					| BGFX_CAPS_FORMAT_TEXTURE_3D_SRGB
					| BGFX_CAPS_FORMAT_TEXTURE_CUBE_SRGB
					| BGFX_CAPS_FORMAT_TEXTURE_VERTEX
					: BGFX_CAPS_FORMAT_TEXTURE_NONE
					;

				if (!bimg::isCompressed(bimg::TextureFormat::Enum(ii) ) )
				{
					support |= 0
						| BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER
					//	| BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA
						;
				}

				g_caps.formats[ii] = support;
			}

			g_caps.formats[TextureFormat::A8     ] &= ~(BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER | BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA);
			g_caps.formats[TextureFormat::RG32I  ] &= ~(BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA);
			g_caps.formats[TextureFormat::RG32U  ] &= ~(BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA);
			g_caps.formats[TextureFormat::RGBA32I] &= ~(BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA);
			g_caps.formats[TextureFormat::RGBA32U] &= ~(BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA);

			g_caps.formats[TextureFormat::ETC2  ] =
			g_caps.formats[TextureFormat::ETC2A ] =
			g_caps.formats[TextureFormat::ETC2A1] =
			g_caps.formats[TextureFormat::PTC12 ] =
			g_caps.formats[TextureFormat::PTC14 ] =
			g_caps.formats[TextureFormat::PTC12A] =
			g_caps.formats[TextureFormat::PTC14A] =
			g_caps.formats[TextureFormat::R5G6B5] =
			g_caps.formats[TextureFormat::RGBA4 ] =
			g_caps.formats[TextureFormat::RGB5A1] = BGFX_CAPS_FORMAT_TEXTURE_NONE;

			g_caps.formats[TextureFormat::RGB9E5F] &= ~(BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER | BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA);
			g_caps.formats[TextureFormat::RG11B10F] &= ~(BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER | BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA);

			// disable compressed formats
			for (uint32_t ii = 0; ii < TextureFormat::Unknown; ++ii)
			{
				s_textureFormat[ii].m_fmt = wgpu::TextureFormat::Undefined;
			}

			for (uint32_t ii = 0; ii < TextureFormat::Count; ++ii)
			{
				if (BGFX_CAPS_FORMAT_TEXTURE_NONE == g_caps.formats[ii])
				{
					s_textureFormat[ii].m_fmt = wgpu::TextureFormat::Undefined;
					s_textureFormat[ii].m_fmtSrgb = wgpu::TextureFormat::Undefined;
				}
			}

			for (uint32_t ii = 1, last = 0; ii < BX_COUNTOF(s_msaa); ++ii)
			{
				// TODO (hugoam)
				//const int32_t sampleCount = 1; //1<<ii;
				//if (m_device.supportsTextureSampleCount(sampleCount) )
				//{
				//	s_msaa[ii] = sampleCount;
				//	last = ii;
				//}
				//else
				{
					s_msaa[ii] = s_msaa[last];
				}
			}

			// Init reserved part of view name.
			for (uint32_t ii = 0; ii < BGFX_CONFIG_MAX_VIEWS; ++ii)
			{
				bx::snprintf(s_viewName[ii], BGFX_CONFIG_MAX_VIEW_NAME_RESERVED+1, "%3d   ", ii);
			}

			m_gpuTimer.init();

			g_internalData.context = &m_device;

			return true;
		}

		void shutdown()
		{
			m_gpuTimer.shutdown();

			m_pipelineStateCache.invalidate();

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_shaders); ++ii)
			{
				m_shaders[ii].destroy();
			}

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_textures); ++ii)
			{
				m_textures[ii].destroy();
			}

			captureFinish();

			m_mainFrameBuffer.destroy();

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_scratchBuffers); ++ii)
			{
				m_scratchBuffers[ii].destroy();
			}

			m_cmd.shutdown();
		}

		RendererType::Enum getRendererType() const override
		{
			return RendererType::WebGPU;
		}

		const char* getRendererName() const override
		{
			return BGFX_RENDERER_WEBGPU_NAME;
		}

		void createIndexBuffer(IndexBufferHandle _handle, const Memory* _mem, uint16_t _flags) override
		{
			m_indexBuffers[_handle.idx].create(_mem->size, _mem->data, _flags);
		}

		void destroyIndexBuffer(IndexBufferHandle _handle) override
		{
			m_indexBuffers[_handle.idx].destroy();
		}

		void createVertexLayout(VertexLayoutHandle _handle, const VertexLayout& _decl) override
		{
			VertexLayout& decl = m_vertexDecls[_handle.idx];
			bx::memCopy(&decl, &_decl, sizeof(VertexLayout) );
			dump(decl);
		}

		void destroyVertexLayout(VertexLayoutHandle /*_handle*/) override
		{
		}

		void createVertexBuffer(VertexBufferHandle _handle, const Memory* _mem, VertexLayoutHandle _declHandle, uint16_t _flags) override
		{
			m_vertexBuffers[_handle.idx].create(_mem->size, _mem->data, _declHandle, _flags);
		}

		void destroyVertexBuffer(VertexBufferHandle _handle) override
		{
			m_vertexBuffers[_handle.idx].destroy();
		}

		void createDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _size, uint16_t _flags) override
		{
			m_indexBuffers[_handle.idx].create(_size, NULL, _flags);
		}

		void updateDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _offset, uint32_t _size, const Memory* _mem) override
		{
			m_indexBuffers[_handle.idx].update(_offset, bx::uint32_min(_size, _mem->size), _mem->data);
		}

		void destroyDynamicIndexBuffer(IndexBufferHandle _handle) override
		{
			m_indexBuffers[_handle.idx].destroy();
		}

		void createDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _size, uint16_t _flags) override
		{
			VertexLayoutHandle decl = BGFX_INVALID_HANDLE;
			m_vertexBuffers[_handle.idx].create(_size, NULL, decl, _flags);
		}

		void updateDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _offset, uint32_t _size, const Memory* _mem) override
		{
			m_vertexBuffers[_handle.idx].update(_offset, bx::uint32_min(_size, _mem->size), _mem->data);
		}

		void destroyDynamicVertexBuffer(VertexBufferHandle _handle) override
		{
			m_vertexBuffers[_handle.idx].destroy();
		}

		void createShader(ShaderHandle _handle, const Memory* _mem) override
		{
			m_shaders[_handle.idx].create(_handle, _mem);
		}

		void destroyShader(ShaderHandle _handle) override
		{
			m_shaders[_handle.idx].destroy();
		}

		void createProgram(ProgramHandle _handle, ShaderHandle _vsh, ShaderHandle _fsh) override
		{
			m_program[_handle.idx].create(&m_shaders[_vsh.idx], isValid(_fsh) ? &m_shaders[_fsh.idx] : NULL);
		}

		void destroyProgram(ProgramHandle _handle) override
		{
			m_program[_handle.idx].destroy();
		}

		void* createTexture(TextureHandle _handle, const Memory* _mem, uint64_t _flags, uint8_t _skip) override
		{
			m_textures[_handle.idx].create(_handle, _mem, _flags, _skip);
			return NULL;
		}

		void updateTextureBegin(TextureHandle /*_handle*/, uint8_t /*_side*/, uint8_t /*_mip*/) override
		{
		}

		void updateTexture(TextureHandle _handle, uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem) override
		{
			m_textures[_handle.idx].update(_side, _mip, _rect, _z, _depth, _pitch, _mem);
		}

		void updateTextureEnd() override
		{
		}

		void readback(ReadbackWgpu& readback,  const TextureWgpu& texture, void* _data)
		{
			m_cmd.kick(false, true);
			m_cmd.beginRender();

			if (readback.m_mapped)
				return;

			BX_ASSERT(readback.m_mip<texture.m_numMips,"Invalid mip: %d num mips:", readback.m_mip,texture.m_numMips);

			uint32_t srcWidth  = bx::uint32_max(1, texture.m_width  >> readback.m_mip);
			uint32_t srcHeight = bx::uint32_max(1, texture.m_height >> readback.m_mip);

			const uint32_t bpp = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(texture.m_textureFormat));
			const uint32_t pitch = srcWidth * bpp / 8;

			const uint32_t dstpitch = bx::strideAlign(pitch, kMinBufferOffsetAlignment);
			const uint32_t size = dstpitch * srcHeight;

			// TODO move inside ReadbackWgpu::create
			if (!readback.m_buffer)
			{
				wgpu::BufferDescriptor desc;
				desc.size = size;
				desc.usage = wgpu::BufferUsage::CopyDst | wgpu::BufferUsage::MapRead;

				readback.m_buffer = m_device.CreateBuffer(&desc);
			}

			wgpu::ImageCopyTexture imageCopyTexture;
			imageCopyTexture.texture = texture.m_ptr;
			imageCopyTexture.origin = { 0, 0, 0 };

			wgpu::ImageCopyBuffer imageCopyBuffer;
			imageCopyBuffer.buffer = readback.m_buffer;
			imageCopyBuffer.layout.bytesPerRow = dstpitch;
			imageCopyBuffer.layout.rowsPerImage = srcHeight;

			wgpu::Extent3D extent3D = { srcWidth, srcHeight, 1 };
			getBlitCommandEncoder().CopyTextureToBuffer(&imageCopyTexture, &imageCopyBuffer, &extent3D);

			auto finish = [](WGPUBufferMapAsyncStatus status, void* userdata)
			{
				ReadbackWgpu* readback = static_cast<ReadbackWgpu*>(userdata);
				void const* data = readback->m_buffer.GetConstMappedRange();
				if(status == WGPUBufferMapAsyncStatus_Success)
					readback->readback(data);
			};

			m_cmd.finish();

			m_cmd.kick(true);

			readback.m_mapped = true;
			readback.m_data = _data;
			readback.m_size = pitch * srcHeight;

			readback.m_buffer.MapAsync(wgpu::MapMode::Read, 0, size, finish, &readback);
		}

		void readTexture(TextureHandle _handle, void* _data, uint8_t _mip) override
		{
			TextureWgpu& texture = m_textures[_handle.idx];

			readback(texture.m_readback, texture, _data);
		}

		void resizeTexture(TextureHandle _handle, uint16_t _width, uint16_t _height, uint8_t _numMips, uint16_t _numLayers) override
		{
			TextureWgpu& texture = m_textures[_handle.idx];

			uint32_t size = sizeof(uint32_t) + sizeof(TextureCreate);
			const Memory* mem = alloc(size);

			bx::StaticMemoryBlockWriter writer(mem->data, mem->size);
			uint32_t magic = BGFX_CHUNK_MAGIC_TEX;
			bx::write(&writer, magic);

			TextureCreate tc;
			tc.m_width     = _width;
			tc.m_height    = _height;
			tc.m_depth     = 0;
			tc.m_numLayers = _numLayers;
			tc.m_numMips   = _numMips;
			tc.m_format    = TextureFormat::Enum(texture.m_requestedFormat);
			tc.m_cubeMap   = false;
			tc.m_mem       = NULL;
			bx::write(&writer, tc);

			texture.destroy();
			texture.create(_handle, mem, texture.m_flags, 0);

			release(mem);
		}

		void overrideInternal(TextureHandle _handle, uintptr_t _ptr) override
		{
			BX_UNUSED(_handle, _ptr);
		}

		uintptr_t getInternal(TextureHandle _handle) override
		{
			BX_UNUSED(_handle);
			return 0;
		}

		void destroyTexture(TextureHandle _handle) override
		{
			m_textures[_handle.idx].destroy();
		}

		void createFrameBuffer(FrameBufferHandle _handle, uint8_t _num, const Attachment* _attachment) override
		{
			m_frameBuffers[_handle.idx].create(_num, _attachment);
		}

		void createFrameBuffer(FrameBufferHandle _handle, void* _nwh, uint32_t _width, uint32_t _height, TextureFormat::Enum _format, TextureFormat::Enum _depthFormat) override
		{
			for (uint32_t ii = 0, num = m_numWindows; ii < num; ++ii)
			{
				FrameBufferHandle handle = m_windows[ii];
				if (isValid(handle)
				&&  m_frameBuffers[handle.idx].m_nwh == _nwh)
				{
					destroyFrameBuffer(handle);
				}
			}

			uint16_t denseIdx   = m_numWindows++;
			m_windows[denseIdx] = _handle;

			FrameBufferWgpu& fb = m_frameBuffers[_handle.idx];
			fb.create(denseIdx, _nwh, _width, _height, _format, _depthFormat);
			fb.m_swapChain->resize(m_frameBuffers[_handle.idx], _width, _height, 0);
		}

		void destroyFrameBuffer(FrameBufferHandle _handle) override
		{
			uint16_t denseIdx = m_frameBuffers[_handle.idx].destroy();

			if (UINT16_MAX != denseIdx)
			{
				--m_numWindows;

				if (m_numWindows > 1)
				{
					FrameBufferHandle handle = m_windows[m_numWindows];
					m_windows[m_numWindows]  = {kInvalidHandle};

					if (m_numWindows != denseIdx)
					{
						m_windows[denseIdx] = handle;
						m_frameBuffers[handle.idx].m_denseIdx = denseIdx;
					}
				}
			}
		}

		void createUniform(UniformHandle _handle, UniformType::Enum _type, uint16_t _num, const char* _name) override
		{
			if (NULL != m_uniforms[_handle.idx])
			{
				BX_FREE(g_allocator, m_uniforms[_handle.idx]);
			}

			uint32_t size = bx::alignUp(g_uniformTypeSize[_type]*_num, 16);
			void* data = BX_ALLOC(g_allocator, size);
			bx::memSet(data, 0, size);
			m_uniforms[_handle.idx] = data;
			m_uniformReg.add(_handle, _name);
		}

		void destroyUniform(UniformHandle _handle) override
		{
			BX_FREE(g_allocator, m_uniforms[_handle.idx]);
			m_uniforms[_handle.idx] = NULL;
			m_uniformReg.remove(_handle);
		}

		void requestScreenShot(FrameBufferHandle _handle, const char* _filePath) override
		{
			BX_UNUSED(_handle); BX_UNUSED(_filePath);
		}

		void updateViewName(ViewId _id, const char* _name) override
		{
			bx::strCopy(
				  &s_viewName[_id][BGFX_CONFIG_MAX_VIEW_NAME_RESERVED]
				, BX_COUNTOF(s_viewName[0])-BGFX_CONFIG_MAX_VIEW_NAME_RESERVED
				, _name
				);
		}

		void updateUniform(uint16_t _loc, const void* _data, uint32_t _size) override
		{
			bx::memCopy(m_uniforms[_loc], _data, _size);
		}

		void invalidateOcclusionQuery(OcclusionQueryHandle _handle) override
		{
			BX_UNUSED(_handle);
		}

		void setMarker(const char* _marker, uint16_t _len) override
		{
			BX_UNUSED(_len);

			if (BX_ENABLED(BGFX_CONFIG_DEBUG_ANNOTATION) )
			{
				m_renderEncoder.InsertDebugMarker(_marker);
			}
		}

		virtual void setName(Handle _handle, const char* _name, uint16_t _len) override
		{
			BX_UNUSED(_handle); BX_UNUSED(_name); BX_UNUSED(_len);
			BX_UNUSED(_len);

			switch (_handle.type)
			{
			case Handle::IndexBuffer:
				m_indexBuffers[_handle.idx].m_label.clear();
				m_indexBuffers[_handle.idx].m_label.append(_name);
				break;

			case Handle::Shader:
				m_shaders[_handle.idx].m_label.clear();
				m_shaders[_handle.idx].m_label.append(_name);
				break;

			case Handle::Texture:
				m_textures[_handle.idx].m_label.clear();
				m_textures[_handle.idx].m_label.append(_name);
				break;

			case Handle::VertexBuffer:
				m_vertexBuffers[_handle.idx].m_label.clear();
				m_vertexBuffers[_handle.idx].m_label.append(_name);
				break;

			default:
				BX_ASSERT(false, "Invalid handle type?! %d", _handle.type);
				break;
			}
		}

		void submitBlit(BlitState& _bs, uint16_t _view);

		void submit(Frame* _render, ClearQuad& _clearQuad, TextVideoMemBlitter& _textVideoMemBlitter) override;

		void blitSetup(TextVideoMemBlitter& _blitter) override
		{
			BX_UNUSED(_blitter);
		}

		void blitRender(TextVideoMemBlitter& _blitter, uint32_t _numIndices) override
		{
			const uint32_t numVertices = _numIndices*4/6;
			if (0 < numVertices)
			{
				m_indexBuffers [_blitter.m_ib->handle.idx].update(
					  0
					, bx::strideAlign(_numIndices*2, 4)
					, _blitter.m_ib->data
					, true
					);
				m_vertexBuffers[_blitter.m_vb->handle.idx].update(
					  0
					, numVertices*_blitter.m_layout.m_stride
					, _blitter.m_vb->data
					, true
					);

				endEncoding();

				uint32_t width  = m_resolution.width;
				uint32_t height = m_resolution.height;

				FrameBufferHandle fbh = BGFX_INVALID_HANDLE;

				uint64_t state = 0
				| BGFX_STATE_WRITE_RGB
				| BGFX_STATE_WRITE_A
				| BGFX_STATE_DEPTH_TEST_ALWAYS
				;

				PipelineStateWgpu* pso = getPipelineState(
														 state
														 , 0
														 , 0
														 , fbh
														 , _blitter.m_vb->layoutHandle
														 , false
														 , _blitter.m_program
														 , 0
														 );

				RenderPassDescriptor renderPassDescriptor;
				wgpu::RenderPassColorAttachment& color = renderPassDescriptor.colorAttachments[0];

				setFrameBuffer(renderPassDescriptor, fbh);

				color.loadOp = wgpu::LoadOp::Load;
				color.storeOp = wgpu::StoreOp::Store;
				//	NULL != renderPassDescriptor.colorAttachments[0].resolveTexture
				//	? wgpu::StoreOp::MultisampleResolve
				//	: wgpu::StoreOp::Store
				//;

				wgpu::RenderPassEncoder rce = m_cmd.m_renderEncoder.BeginRenderPass(&renderPassDescriptor.desc);
				m_renderEncoder = rce;

				rce.SetViewport(0.0f, 0.0f, (float)width, (float)height, 0.0f, 1.0f);
				rce.SetScissorRect(0.0f, 0.0f, (float)width, (float)height);

				rce.SetPipeline(pso->m_rps);

				ProgramWgpu& program = m_program[_blitter.m_program.idx];

				ScratchBufferWgpu& scratchBuffer = m_scratchBuffers[0];
				BindStateCacheWgpu& bindStates = m_bindStateCache[0];

				float proj[16];
				bx::mtxOrtho(proj, 0.0f, (float)width, (float)height, 0.0f, 0.0f, 1000.0f, 0.0f, false);

				PredefinedUniform& predefined = program.m_predefined[0];
				uint8_t flags = predefined.m_type;
				setShaderUniform(flags, predefined.m_loc, proj, 4);

				BX_ASSERT(program.m_vsh->m_size > 0, "Not supposed to happen");
				const uint32_t voffset = scratchBuffer.write(m_vsScratch, program.m_vsh->m_gpuSize);

				const uint32_t fsize = (NULL != program.m_fsh ? program.m_fsh->m_gpuSize : 0);
				BX_ASSERT(fsize == 0, "Not supposed to happen");

				TextureWgpu& texture = m_textures[_blitter.m_texture.idx];

				BindingsWgpu b;

				BindStateWgpu& bindState = allocBindState(program, bindStates, b, scratchBuffer);

				wgpu::BindGroupEntry& textureEntry = b.m_entries[b.numEntries++];
				textureEntry.binding = program.m_textures[0].binding;
				textureEntry.textureView = texture.m_ptr.CreateView();

				wgpu::BindGroupEntry& samplerEntry = b.m_entries[b.numEntries++];
				samplerEntry.binding = program.m_samplers[0].binding;
				samplerEntry.sampler = 0 == (BGFX_SAMPLER_INTERNAL_DEFAULT & state)
					? getSamplerState(state)
					: texture.m_sampler;

				bindGroups(program, bindState, b);

				uint32_t numOffset = 1;
				uint32_t offsets[1] = { voffset };

				bindProgram(rce, program, bindState, numOffset, offsets);

				VertexBufferWgpu& vb = m_vertexBuffers[_blitter.m_vb->handle.idx];
				rce.SetVertexBuffer(0, vb.m_ptr);

				IndexBufferWgpu& ib = m_indexBuffers[_blitter.m_ib->handle.idx];
				rce.SetIndexBuffer(ib.m_ptr, ib.m_format);
				rce.DrawIndexed(_numIndices, 1, 0, 0, 0);
			}
		}

		bool isDeviceRemoved() override
		{
			return false;
		}

		void flip() override
		{
			for (uint32_t ii = 0, num = m_numWindows; ii < num; ++ii)
			{
				FrameBufferWgpu& frameBuffer = ii == 0 ? m_mainFrameBuffer : m_frameBuffers[m_windows[ii].idx];
				if (NULL != frameBuffer.m_swapChain)
				//&& frameBuffer.m_swapChain->m_drawable)
				{
					SwapChainWgpu& swapChain = *frameBuffer.m_swapChain;
					swapChain.flip();
				}
			}

			m_cmd.m_stagingEncoder = NULL;
			m_cmd.m_renderEncoder = NULL;
		}

		void updateResolution(const Resolution& _resolution)
		{
			m_resolution = _resolution;
			return; // TODO (hugoam)

			m_mainFrameBuffer.m_swapChain->m_maxAnisotropy = !!(_resolution.reset & BGFX_RESET_MAXANISOTROPY)
				? 16
				: 1
				;

			const uint32_t maskFlags = ~(0
				| BGFX_RESET_MAXANISOTROPY
				| BGFX_RESET_DEPTH_CLAMP
				| BGFX_RESET_SUSPEND
				);

			if (m_resolution.width            !=  _resolution.width
			||  m_resolution.height           !=  _resolution.height
			|| (m_resolution.reset&maskFlags) != (_resolution.reset&maskFlags) )
			{
				wgpu::TextureFormat prevMetalLayerPixelFormat; // = m_mainFrameBuffer.m_swapChain->m_metalLayer.pixelFormat;
				BX_UNUSED(prevMetalLayerPixelFormat);

				m_resolution = _resolution;
				m_resolution.reset &= ~BGFX_RESET_INTERNAL_FORCE;

				m_mainFrameBuffer.m_swapChain->resize(m_mainFrameBuffer, _resolution.width, _resolution.height, _resolution.reset);

				for (uint32_t ii = 0; ii < BX_COUNTOF(m_frameBuffers); ++ii)
				{
					m_frameBuffers[ii].postReset();
				}

				updateCapture();

				m_textVideoMem.resize(false, _resolution.width, _resolution.height);
				m_textVideoMem.clear();

				//if (prevMetalLayerPixelFormat != m_mainFrameBuffer.m_swapChain->m_metalLayer.pixelFormat)
				{
					//MTL_RELEASE(m_screenshotBlitRenderPipelineState)
					//reset(m_renderPipelineDescriptor);

					//m_renderPipelineDescriptor.colorAttachments[0].pixelFormat = m_mainFrameBuffer.m_swapChain->m_metalLayer.pixelFormat;
					//m_renderPipelineDescriptor.vertexFunction   = m_screenshotBlitProgram.m_vsh->m_function;
					//m_renderPipelineDescriptor.fragmentFunction = m_screenshotBlitProgram.m_fsh->m_function;
					//m_screenshotBlitRenderPipelineState = m_device.newRenderPipelineStateWithDescriptor(m_renderPipelineDescriptor);
				}
			}
		}

		void invalidateCompute()
		{
			if (m_computeEncoder)
			{
				m_computeEncoder.EndPass();
				m_computeEncoder = NULL;
			}
		}

		void updateCapture()
		{
		}

		void capture()
		{
		}

		void captureFinish()
		{
		}

		BindStateWgpu& allocBindState(const ProgramWgpu& program, BindStateCacheWgpu& bindStates, BindingsWgpu& bindings, ScratchBufferWgpu& scratchBuffer)
		{
			BindStateWgpu& bindState = bindStates.m_bindStates[bindStates.m_currentBindState];
			bindStates.m_currentBindState++;

			bindState.numOffset = program.m_numUniforms;

			// first two bindings are always uniform buffer (vertex/fragment)
			if (0 < program.m_vsh->m_gpuSize)
			{
				bindings.m_entries[0].binding = kSpirvVertexBinding;
				bindings.m_entries[0].offset = 0;
				bindings.m_entries[0].size = program.m_vsh->m_gpuSize;
				bindings.m_entries[0].buffer = scratchBuffer.m_buffer;
				bindings.numEntries++;
			}

			if (NULL != program.m_fsh
			&& 0 < program.m_fsh->m_gpuSize)
			{
				bindings.m_entries[1].binding = kSpirvFragmentBinding;
				bindings.m_entries[1].offset = 0;
				bindings.m_entries[1].size = program.m_fsh->m_gpuSize;
				bindings.m_entries[1].buffer = scratchBuffer.m_buffer;
				bindings.numEntries++;
			}

			return bindState;
		}

		void bindGroups(const ProgramWgpu& program, BindStateWgpu& bindState, BindingsWgpu& bindings)
		{
			wgpu::BindGroupDescriptor bindGroupDesc;
			bindGroupDesc.layout = program.m_bindGroupLayout;
			bindGroupDesc.entryCount = bindings.numEntries;
			bindGroupDesc.entries = bindings.m_entries;

			bindState.m_bindGroup = m_device.CreateBindGroup(&bindGroupDesc);
		}

		template <class Encoder>
		void bindProgram(Encoder& encoder, const ProgramWgpu& program, BindStateWgpu& bindState, uint32_t numOffset, uint32_t* offsets)
		{
			BX_ASSERT(bindState.numOffset == numOffset, "We're obviously doing something wrong");
			encoder.SetBindGroup(0, bindState.m_bindGroup, numOffset, offsets);
		}

		BindStateWgpu& allocAndFillBindState(const ProgramWgpu& program, BindStateCacheWgpu& bindStates, ScratchBufferWgpu& scratchBuffer, const RenderBind& renderBind)
		{
			BindingsWgpu b;

			BindStateWgpu& bindState = allocBindState(program, bindStates, b, scratchBuffer);

			for (uint8_t stage = 0; stage < BGFX_CONFIG_MAX_TEXTURE_SAMPLERS; ++stage)
			{
				const Binding& bind = renderBind.m_bind[stage];
				const BindInfo& bindInfo = program.m_bindInfo[stage];

				bool isUsed = isValid(program.m_bindInfo[stage].m_uniform);

				BX_ASSERT(!isUsed || kInvalidHandle != bind.m_idx, "All expected bindings must be bound with WebGPU");

				if (kInvalidHandle != bind.m_idx)
				{
					switch (bind.m_type)
					{
					case Binding::Image:
					{
						TextureWgpu& texture = m_textures[bind.m_idx];
						wgpu::BindGroupEntry& entry = b.m_entries[b.numEntries++];
						entry.binding = bindInfo.m_binding;
						entry.textureView = texture.getTextureMipLevel(bind.m_mip);

						if (Access::Read == bind.m_access)
						{
							wgpu::BindGroupEntry& samplerEntry = b.m_entries[b.numEntries++];
							samplerEntry.binding = bindInfo.m_binding + 16;
							samplerEntry.sampler = texture.m_sampler;
						}
					}
					break;

					case Binding::Texture:
					{
						// apparently bgfx allows to set a texture to a stage that a program does not even use
						if (isUsed)
						{
							TextureWgpu& texture = m_textures[bind.m_idx];
							uint32_t flags = bind.m_samplerFlags;

							wgpu::TextureViewDescriptor viewDesc = defaultDescriptor<wgpu::TextureViewDescriptor>();
							viewDesc.dimension = program.m_textures[bindInfo.m_index].texture.viewDimension;

							wgpu::BindGroupEntry& textureEntry = b.m_entries[b.numEntries++];
							textureEntry.binding = bindInfo.m_binding;
							//textureEntry.textureView = texture.m_ptr.CreateView();
							textureEntry.textureView = texture.m_ptr.CreateView(&viewDesc);

							wgpu::BindGroupEntry& samplerEntry = b.m_entries[b.numEntries++];
							samplerEntry.binding = bindInfo.m_binding + kSpirvSamplerShift;
							samplerEntry.sampler = 0 == (BGFX_SAMPLER_INTERNAL_DEFAULT & flags)
								? getSamplerState(flags)
								: texture.m_sampler;
						}
					}
					break;

					case Binding::IndexBuffer:
					case Binding::VertexBuffer:
					{
						const BufferWgpu& buffer = Binding::IndexBuffer == bind.m_type
							? (const BufferWgpu&) m_indexBuffers[bind.m_idx]
							: (const BufferWgpu&) m_vertexBuffers[bind.m_idx]
							;

						wgpu::BindGroupEntry& entry = b.m_entries[b.numEntries++];
						entry.binding = bindInfo.m_binding;
						entry.offset = 0;
						entry.size = buffer.m_size;
						entry.buffer = buffer.m_ptr;
					}
					break;
					}
				}
			}

			bindGroups(program, bindState, b);

			return bindState;
		};

		void setShaderUniform(uint8_t _flags, uint32_t _regIndex, const void* _val, uint32_t _numRegs)
		{
			if(_flags&kUniformFragmentBit)
			{
				bx::memCopy(&m_fsScratch[_regIndex], _val, _numRegs * 16);
			}
			else
			{
				bx::memCopy(&m_vsScratch[_regIndex], _val, _numRegs * 16);
			}
		}

		void setShaderUniform4f(uint8_t _flags, uint32_t _loc, const void* _val, uint32_t _numRegs)
		{
			setShaderUniform(_flags, _loc, _val, _numRegs);
		}

		void setShaderUniform4x4f(uint8_t _flags, uint32_t _loc, const void* _val, uint32_t _numRegs)
		{
			setShaderUniform(_flags, _loc, _val, _numRegs);
		}

		void commit(UniformBuffer& _uniformBuffer)
		{
			_uniformBuffer.reset();

			for (;;)
			{
				uint32_t opcode = _uniformBuffer.read();

				if (UniformType::End == opcode)
				{
					break;
				}

				UniformType::Enum type;
				uint16_t loc;
				uint16_t num;
				uint16_t copy;
				UniformBuffer::decodeOpcode(opcode, type, loc, num, copy);

				const char* data;
				if (copy)
				{
					data = _uniformBuffer.read(g_uniformTypeSize[type]*num);
				}
				else
				{
					UniformHandle handle;
					bx::memCopy(&handle, _uniformBuffer.read(sizeof(UniformHandle) ), sizeof(UniformHandle) );
					data = (const char*)m_uniforms[handle.idx];
				}

				switch ( (uint32_t)type)
				{
				case UniformType::Mat3:
				case UniformType::Mat3|kUniformFragmentBit:
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
							setShaderUniform(uint8_t(type), loc, &mtx.un.val[0], 3);
						}
					}
					break;

				case UniformType::Sampler:
				case UniformType::Sampler | kUniformFragmentBit:
				case UniformType::Vec4:
				case UniformType::Vec4 | kUniformFragmentBit:
				case UniformType::Mat4:
				case UniformType::Mat4 | kUniformFragmentBit:
					{
						setShaderUniform(uint8_t(type), loc, data, num);
					}
					break;
				case UniformType::End:
					break;

				default:
					BX_TRACE("%4d: INVALID 0x%08x, t %d, l %d, n %d, c %d", _uniformBuffer.getPos(), opcode, type, loc, num, copy);
					break;
				}
			}
		}

		void clearQuad(ClearQuad& _clearQuad, const Rect& _rect, const Clear& _clear, const float _palette[][4])
		{
			uint32_t width;
			uint32_t height;

			if (isValid(m_fbh) )
			{
				const FrameBufferWgpu& fb = m_frameBuffers[m_fbh.idx];
				width  = fb.m_width;
				height = fb.m_height;
			}
			else
			{
				width  = m_resolution.width;
				height = m_resolution.height;
			}

			uint64_t state = 0;
			state |= _clear.m_flags & BGFX_CLEAR_COLOR ? BGFX_STATE_WRITE_RGB|BGFX_STATE_WRITE_A         : 0;
			state |= _clear.m_flags & BGFX_CLEAR_DEPTH ? BGFX_STATE_DEPTH_TEST_ALWAYS|BGFX_STATE_WRITE_Z : 0;
			state |= BGFX_STATE_PT_TRISTRIP;

			uint64_t stencil = 0;
			stencil |= _clear.m_flags & BGFX_CLEAR_STENCIL ? 0
				| BGFX_STENCIL_TEST_ALWAYS
				| BGFX_STENCIL_FUNC_REF(_clear.m_stencil)
				| BGFX_STENCIL_FUNC_RMASK(0xff)
				| BGFX_STENCIL_OP_FAIL_S_REPLACE
				| BGFX_STENCIL_OP_FAIL_Z_REPLACE
				| BGFX_STENCIL_OP_PASS_Z_REPLACE
				: 0
				;

			uint32_t numMrt = 1;
			FrameBufferHandle fbh = m_fbh;
			if (isValid(fbh) && m_frameBuffers[fbh.idx].m_swapChain == NULL)
			{
				const FrameBufferWgpu& fb = m_frameBuffers[fbh.idx];
				numMrt = bx::uint32_max(1, fb.m_num);
			}

			wgpu::RenderPassEncoder rce = m_renderEncoder;
			ProgramHandle programHandle = _clearQuad.m_program[numMrt-1];

			const VertexLayout* decl = &_clearQuad.m_layout;
			const PipelineStateWgpu* pso = getPipelineState(
				  state
				, stencil
				, 0
				, fbh
				, 1
				, &decl
				, false
				, programHandle
				, 0
				);
			rce.SetPipeline(pso->m_rps);

			float mrtClearColor[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS][4];
			float mrtClearDepth[4] = { _clear.m_depth };

			if (BGFX_CLEAR_COLOR_USE_PALETTE & _clear.m_flags)
			{
				for (uint32_t ii = 0; ii < numMrt; ++ii)
				{
					uint8_t index = (uint8_t)bx::uint32_min(BGFX_CONFIG_MAX_COLOR_PALETTE-1, _clear.m_index[ii]);
					bx::memCopy(mrtClearColor[ii], _palette[index], 16);
				}
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

				for (uint32_t ii = 0; ii < numMrt; ++ii)
				{
					bx::memCopy( mrtClearColor[ii]
								, rgba
								, 16
								);
				}
			}

			ProgramWgpu& program = m_program[programHandle.idx];

			ScratchBufferWgpu& scratchBuffer = m_scratchBuffers[0];
			BindStateCacheWgpu& bindStates = m_bindStateCache[0];

			BindingsWgpu b;
			BindStateWgpu& bindState = allocBindState(program, bindStates, b, scratchBuffer);

			const uint32_t voffset = scratchBuffer.write(mrtClearDepth, sizeof(mrtClearDepth), program.m_vsh->m_gpuSize);
			const uint32_t foffset = scratchBuffer.write(mrtClearColor, sizeof(mrtClearColor), program.m_fsh->m_gpuSize);

			uint32_t numOffset = 2;
			uint32_t offsets[2] = { voffset, foffset };

			bindGroups(program, bindState, b);

			const VertexBufferWgpu& vb = m_vertexBuffers[_clearQuad.m_vb.idx];

			bindProgram(rce, program, bindState, numOffset, offsets);

			rce.SetViewport(_rect.m_x, _rect.m_y, _rect.m_width, _rect.m_height, 0.0f, 1.0f);
			rce.SetScissorRect(_rect.m_x, _rect.m_y, _rect.m_width, _rect.m_height);

			rce.SetVertexBuffer(0, vb.m_ptr);
			rce.Draw(4, 1, 0, 0);
		}

		wgpu::TextureViewDescriptor attachmentView(const Attachment& _at, const TextureWgpu& _texture)
		{
			bool _resolve = bool(_texture.m_ptrMsaa);
			BX_UNUSED(_resolve);

			wgpu::TextureViewDescriptor desc;
			if (1 < _texture.m_numSides)
			{
				desc.baseArrayLayer = _at.layer;
			}
			desc.baseMipLevel = _at.mip;
			desc.arrayLayerCount = 1;
			desc.mipLevelCount = 1;

			if (_texture.m_type == TextureWgpu::Texture3D)
			{
				desc.dimension = wgpu::TextureViewDimension::e3D;
			}

			return desc;
		}

		void setFrameBuffer(RenderPassDescriptor& _renderPassDescriptor, FrameBufferHandle _fbh, bool _msaa = true)
		{
			if (!isValid(_fbh)
			||  m_frameBuffers[_fbh.idx].m_swapChain)
			{
				SwapChainWgpu* swapChain = !isValid(_fbh)
					? m_mainFrameBuffer.m_swapChain
					: m_frameBuffers[_fbh.idx].m_swapChain
					;

				_renderPassDescriptor.colorAttachments[0] = defaultDescriptor<wgpu::RenderPassColorAttachment>();
				_renderPassDescriptor.desc.colorAttachmentCount = 1;

				// Force 1 array layers for attachments
				wgpu::TextureViewDescriptor desc;
				desc.arrayLayerCount = 1;

				if (swapChain->m_backBufferColorMsaa)
				{
					_renderPassDescriptor.colorAttachments[0].view    = swapChain->m_backBufferColorMsaa.CreateView(&desc);
					_renderPassDescriptor.colorAttachments[0].resolveTarget = swapChain->current();
				}
				else
				{
					_renderPassDescriptor.colorAttachments[0].view = swapChain->current();
				}

				_renderPassDescriptor.depthStencilAttachment = defaultDescriptor<wgpu::RenderPassDepthStencilAttachment>();
				_renderPassDescriptor.depthStencilAttachment.view = swapChain->m_backBufferDepth.CreateView();
				_renderPassDescriptor.desc.depthStencilAttachment = &_renderPassDescriptor.depthStencilAttachment;
			}
			else
			{
				FrameBufferWgpu& frameBuffer = m_frameBuffers[_fbh.idx];

				_renderPassDescriptor.desc.colorAttachmentCount = frameBuffer.m_num;

				for (uint32_t ii = 0; ii < frameBuffer.m_num; ++ii)
				{
					const TextureWgpu& texture = m_textures[frameBuffer.m_colorHandle[ii].idx];

					const wgpu::TextureViewDescriptor desc = attachmentView(frameBuffer.m_colorAttachment[ii], texture);

					_renderPassDescriptor.colorAttachments[ii] = defaultDescriptor<wgpu::RenderPassColorAttachment>();
					_renderPassDescriptor.colorAttachments[ii].view = texture.m_ptrMsaa
						? texture.m_ptrMsaa.CreateView(&desc)
						: texture.m_ptr.CreateView(&desc)
						;
					_renderPassDescriptor.colorAttachments[ii].resolveTarget = texture.m_ptrMsaa
						? texture.m_ptr.CreateView(&desc)
						: wgpu::TextureView()
						;
				}

				if (isValid(frameBuffer.m_depthHandle) )
				{
					const TextureWgpu& texture = m_textures[frameBuffer.m_depthHandle.idx];
					const wgpu::TextureViewDescriptor desc = attachmentView(frameBuffer.m_depthAttachment, texture);

					_renderPassDescriptor.depthStencilAttachment = defaultDescriptor<wgpu::RenderPassDepthStencilAttachment>();
					_renderPassDescriptor.depthStencilAttachment.view = texture.m_ptrMsaa
						? texture.m_ptrMsaa.CreateView(&desc)
						: texture.m_ptr.CreateView(&desc)
						;

					_renderPassDescriptor.desc.depthStencilAttachment = &_renderPassDescriptor.depthStencilAttachment;
				}
			}

			m_fbh    = _fbh;
			m_rtMsaa = _msaa;
		}

		void setDepthStencilState(wgpu::DepthStencilState& desc, uint64_t _state, uint64_t _stencil = 0)
		{
			const uint32_t fstencil = unpackStencil(0, _stencil);
			const uint32_t func = (_state&BGFX_STATE_DEPTH_TEST_MASK) >> BGFX_STATE_DEPTH_TEST_SHIFT;

			desc.depthWriteEnabled = !!(BGFX_STATE_WRITE_Z & _state);
			desc.depthCompare = s_cmpFunc[func];

			uint32_t bstencil = unpackStencil(1, _stencil);
			const uint32_t frontAndBack = bstencil != BGFX_STENCIL_NONE && bstencil != fstencil;
			bstencil = frontAndBack ? bstencil : fstencil;

			desc.stencilFront = defaultDescriptor<wgpu::StencilFaceState>();
			desc.stencilBack = defaultDescriptor<wgpu::StencilFaceState>();

			if (0 != _stencil)
			{
				// TODO (hugoam)
				const uint32_t readMask  = (fstencil&BGFX_STENCIL_FUNC_RMASK_MASK)>>BGFX_STENCIL_FUNC_RMASK_SHIFT;
				const uint32_t writeMask = 0xff;

				desc.stencilReadMask  = readMask;
				desc.stencilWriteMask = writeMask;

				desc.stencilFront.failOp      = s_stencilOp[(fstencil&BGFX_STENCIL_OP_FAIL_S_MASK)>>BGFX_STENCIL_OP_FAIL_S_SHIFT];
				desc.stencilFront.depthFailOp = s_stencilOp[(fstencil&BGFX_STENCIL_OP_FAIL_Z_MASK)>>BGFX_STENCIL_OP_FAIL_Z_SHIFT];
				desc.stencilFront.passOp      = s_stencilOp[(fstencil&BGFX_STENCIL_OP_PASS_Z_MASK)>>BGFX_STENCIL_OP_PASS_Z_SHIFT];
				desc.stencilFront.compare     = s_cmpFunc[(fstencil&BGFX_STENCIL_TEST_MASK)>>BGFX_STENCIL_TEST_SHIFT];

				desc.stencilBack.failOp      = s_stencilOp[(bstencil&BGFX_STENCIL_OP_FAIL_S_MASK)>>BGFX_STENCIL_OP_FAIL_S_SHIFT];
				desc.stencilBack.depthFailOp = s_stencilOp[(bstencil&BGFX_STENCIL_OP_FAIL_Z_MASK)>>BGFX_STENCIL_OP_FAIL_Z_SHIFT];
				desc.stencilBack.passOp      = s_stencilOp[(bstencil&BGFX_STENCIL_OP_PASS_Z_MASK)>>BGFX_STENCIL_OP_PASS_Z_SHIFT];
				desc.stencilBack.compare     = s_cmpFunc[(bstencil&BGFX_STENCIL_TEST_MASK)>>BGFX_STENCIL_TEST_SHIFT];
			}
		}

		RenderPassStateWgpu* getRenderPassState(bgfx::FrameBufferHandle fbh, bool clear, Clear clr)
		{
			bx::HashMurmur2A murmur;
			murmur.begin();
			murmur.add(fbh.idx);
			murmur.add(clear);
			murmur.add(&clr, sizeof(clr));
			uint32_t hash = murmur.end();

			RenderPassStateWgpu* rps = m_renderPassStateCache.find(hash);

			if (NULL == rps)
			{
				rps = BX_NEW(g_allocator, RenderPassStateWgpu);
				m_renderPassStateCache.add(hash, rps);
			}

			return rps;
		}

		PipelineStateWgpu* getPipelineState(
			  uint64_t _state
			, uint64_t _stencil
			, uint32_t _rgba
			, FrameBufferHandle _fbh
			, uint8_t _numStreams
			, const VertexLayout** _vertexDecls
			, bool _isIndex16
			, ProgramHandle _program
			, uint8_t _numInstanceData
			)
		{
			_state &= 0
				| BGFX_STATE_WRITE_RGB
				| BGFX_STATE_WRITE_A
				| BGFX_STATE_WRITE_Z
				| BGFX_STATE_DEPTH_TEST_MASK
				| BGFX_STATE_BLEND_MASK
				| BGFX_STATE_BLEND_EQUATION_MASK
				| BGFX_STATE_BLEND_INDEPENDENT
				| BGFX_STATE_BLEND_ALPHA_TO_COVERAGE
				| BGFX_STATE_CULL_MASK
				| BGFX_STATE_MSAA
				| BGFX_STATE_LINEAA
				| BGFX_STATE_CONSERVATIVE_RASTER
				| BGFX_STATE_PT_MASK
				;

			const bool independentBlendEnable = !!(BGFX_STATE_BLEND_INDEPENDENT & _state);
			const ProgramWgpu& program = m_program[_program.idx];

			bx::HashMurmur2A murmur;
			murmur.begin();
			murmur.add(_state);
			murmur.add(_stencil);
			murmur.add(independentBlendEnable ? _rgba : 0);
			murmur.add(_numInstanceData);

			FrameBufferWgpu& frameBuffer = !isValid(_fbh) ? m_mainFrameBuffer : m_frameBuffers[_fbh.idx];
			murmur.add(frameBuffer.m_pixelFormatHash);

			murmur.add(program.m_vsh->m_hash);
			if (NULL != program.m_fsh)
			{
				murmur.add(program.m_fsh->m_hash);
			}

			for (uint8_t ii = 0; ii < _numStreams; ++ii)
			{
				murmur.add(_vertexDecls[ii]->m_hash);
			}

			uint32_t hash = murmur.end();

			PipelineStateWgpu* pso = m_pipelineStateCache.find(hash);

			if (NULL == pso)
			{
				pso = BX_NEW(g_allocator, PipelineStateWgpu);

				//pd.alphaToCoverageEnabled = !!(BGFX_STATE_BLEND_ALPHA_TO_COVERAGE & _state);

				RenderPipelineDescriptor& pd = pso->m_rpd;

				uint32_t frameBufferAttachment = 1;
				uint32_t sampleCount = 1;

				if (!isValid(_fbh)
				||  s_renderWgpu->m_frameBuffers[_fbh.idx].m_swapChain)
				{
					SwapChainWgpu& swapChain = !isValid(_fbh)
						? *s_renderWgpu->m_mainFrameBuffer.m_swapChain
						: *s_renderWgpu->m_frameBuffers[_fbh.idx].m_swapChain
						;
					sampleCount = swapChain.m_backBufferColorMsaa
						? swapChain.m_sampleCount
						: 1
						;
					pd.targets[0].format = swapChain.m_colorFormat;
					pd.depthStencil.format = swapChain.m_depthFormat;
					pd.desc.depthStencil = &pd.depthStencil;
				}
				else
				{
					frameBufferAttachment = frameBuffer.m_num;

					for (uint32_t ii = 0; ii < frameBuffer.m_num; ++ii)
					{
						const TextureWgpu& texture = m_textures[frameBuffer.m_colorHandle[ii].idx];
						sampleCount = texture.m_ptrMsaa
							? texture.m_sampleCount
							: 1
							;
						pd.targets[ii].format = s_textureFormat[texture.m_textureFormat].m_fmt;
					}

					pd.fragment.targetCount = frameBuffer.m_num;

					if (isValid(frameBuffer.m_depthHandle) )
					{
						const TextureWgpu& texture = m_textures[frameBuffer.m_depthHandle.idx];
						pd.depthStencil.format = s_textureFormat[texture.m_textureFormat].m_fmt;
						pd.desc.depthStencil = &pd.depthStencil;
					}
				}

				const uint32_t blend    = uint32_t( (_state&BGFX_STATE_BLEND_MASK         )>>BGFX_STATE_BLEND_SHIFT);
				const uint32_t equation = uint32_t( (_state&BGFX_STATE_BLEND_EQUATION_MASK)>>BGFX_STATE_BLEND_EQUATION_SHIFT);

				const uint32_t srcRGB = (blend    )&0xf;
				const uint32_t dstRGB = (blend>> 4)&0xf;
				const uint32_t srcA   = (blend>> 8)&0xf;
				const uint32_t dstA   = (blend>>12)&0xf;

				const uint32_t equRGB = (equation   )&0x7;
				const uint32_t equA   = (equation>>3)&0x7;

				wgpu::ColorWriteMask writeMask = wgpu::ColorWriteMask::None;
				writeMask |= (_state&BGFX_STATE_WRITE_R) ? wgpu::ColorWriteMask::Red   : wgpu::ColorWriteMask::None;
				writeMask |= (_state&BGFX_STATE_WRITE_G) ? wgpu::ColorWriteMask::Green : wgpu::ColorWriteMask::None;
				writeMask |= (_state&BGFX_STATE_WRITE_B) ? wgpu::ColorWriteMask::Blue  : wgpu::ColorWriteMask::None;
				writeMask |= (_state&BGFX_STATE_WRITE_A) ? wgpu::ColorWriteMask::Alpha : wgpu::ColorWriteMask::None;

				for (uint32_t ii = 0; ii < (independentBlendEnable ? 1 : frameBufferAttachment); ++ii)
				{
					wgpu::ColorTargetState& drt = pd.targets[ii];
					wgpu::BlendState& blend = pd.blends[ii];

					if(!(BGFX_STATE_BLEND_MASK & _state))
					{
						// useless
						blend.color = defaultDescriptor<wgpu::BlendComponent>();
						blend.alpha = defaultDescriptor<wgpu::BlendComponent>();

						drt.blend = NULL;
					}
					else
					{
						blend.color.srcFactor = s_blendFactor[srcRGB][0];
						blend.color.dstFactor = s_blendFactor[dstRGB][0];
						blend.color.operation = s_blendEquation[equRGB];

						blend.alpha.srcFactor = s_blendFactor[srcA][1];
						blend.alpha.dstFactor = s_blendFactor[dstA][1];
						blend.alpha.operation = s_blendEquation[equA];

						drt.blend = &blend;
					}

					drt.writeMask = writeMask;
				}

				if (independentBlendEnable)
				{
					for (uint32_t ii = 1, rgba = _rgba; ii < frameBufferAttachment; ++ii, rgba >>= 11)
					{
						wgpu::ColorTargetState& drt = pd.targets[ii];
						wgpu::BlendState& blend = pd.blends[ii];

						//drt.blendingEnabled = 0 != (rgba&0x7ff);

						const uint32_t src           = (rgba   )&0xf;
						const uint32_t dst           = (rgba>>4)&0xf;
						const uint32_t equationIndex = (rgba>>8)&0x7;

						blend.color.srcFactor  = s_blendFactor[src][0];
						blend.color.dstFactor  = s_blendFactor[dst][0];
						blend.color.operation  = s_blendEquation[equationIndex];

						blend.alpha.srcFactor  = s_blendFactor[src][1];
						blend.alpha.dstFactor  = s_blendFactor[dst][1];
						blend.alpha.operation  = s_blendEquation[equationIndex];

						drt.writeMask = writeMask;
					}
				}

				pd.desc.vertex.module = program.m_vsh->m_module;

				if (NULL != program.m_fsh)
				{
					pd.fragment.module = program.m_fsh->m_module;
					pd.desc.fragment = &pd.fragment;
				}

				setDepthStencilState(pd.depthStencil, _state, _stencil);

				const uint64_t cull = _state & BGFX_STATE_CULL_MASK;
				const uint8_t cullIndex = uint8_t(cull >> BGFX_STATE_CULL_SHIFT);
				pd.desc.primitive.cullMode = s_cullMode[cullIndex];

				pd.desc.primitive.frontFace = (_state & BGFX_STATE_FRONT_CCW) ? wgpu::FrontFace::CCW : wgpu::FrontFace::CW;

				// pd.desc = m_renderPipelineDescriptor;
				pd.desc.multisample.count = sampleCount;

				wgpu::PipelineLayoutDescriptor layout = defaultDescriptor<wgpu::PipelineLayoutDescriptor>();
				layout.bindGroupLayouts = &program.m_bindGroupLayout;
				layout.bindGroupLayoutCount = 1;

				BX_TRACE("Creating WebGPU render pipeline layout for program %s", program.m_vsh->name());
				pd.desc.layout = m_device.CreatePipelineLayout(&layout);
				// TODO (hugoam) this should be cached too ?

				//uint32_t ref = (_state&BGFX_STATE_ALPHA_REF_MASK) >> BGFX_STATE_ALPHA_REF_SHIFT;
				//viewState.m_alphaRef = ref / 255.0f;

				const uint64_t primType = _state & BGFX_STATE_PT_MASK;
				uint8_t primIndex = uint8_t(primType >> BGFX_STATE_PT_SHIFT);

				PrimInfo prim = s_primInfo[primIndex];
				pd.desc.primitive.topology = prim.m_type;

				VertexStateDescriptor vertex;
				vertex.desc.module = program.m_vsh->m_module;
				vertex.desc.bufferCount = 0;

				wgpu::VertexBufferLayout* inputBinding = vertex.buffers;
				wgpu::VertexAttribute* inputAttrib = vertex.attributes;

				auto fillVertexDecl = [&](const ShaderWgpu* _vsh, const VertexLayout& _decl)
				{
					vertex.desc.bufferCount += 1;

					inputBinding->arrayStride = _decl.m_stride;
					inputBinding->stepMode = wgpu::InputStepMode::Vertex;
					inputBinding->attributes = inputAttrib;

					uint32_t numAttribs = 0;

					for(uint32_t attr = 0; attr < Attrib::Count; ++attr)
					{
						if(UINT16_MAX != _decl.m_attributes[attr])
						{
							if(UINT8_MAX == _vsh->m_attrRemap[attr])
								continue;

							inputAttrib->shaderLocation = _vsh->m_attrRemap[attr];

							if(0 == _decl.m_attributes[attr])
							{
								inputAttrib->format = wgpu::VertexFormat::Float3;
								inputAttrib->offset = 0;
							}
							else
							{
								uint8_t num;
								AttribType::Enum type;
								bool normalized;
								bool asInt;
								_decl.decode(Attrib::Enum(attr), num, type, normalized, asInt);
								inputAttrib->format = s_attribType[type][num-1][normalized];
								inputAttrib->offset = _decl.m_offset[attr];
							}

							++inputAttrib;
							++numAttribs;
						}
					}

					inputBinding->attributeCount = numAttribs;
					inputBinding++;

					return numAttribs;
				};

				//bool attrSet[Attrib::Count] = {};

				uint16_t unsettedAttr[Attrib::Count];
				bx::memCopy(unsettedAttr, program.m_vsh->m_attrMask, sizeof(uint16_t) * Attrib::Count);

				uint8_t stream = 0;
				for (; stream < _numStreams; ++stream)
				{
					VertexLayout layout;
					bx::memCopy(&layout, _vertexDecls[stream], sizeof(VertexLayout));
					const uint16_t* attrMask = program.m_vsh->m_attrMask;

					for (uint32_t ii = 0; ii < Attrib::Count; ++ii)
					{
						Attrib::Enum iiattr = Attrib::Enum(ii);
						uint16_t mask = attrMask[ii];
						uint16_t attr = (layout.m_attributes[ii] & mask);
						if (attr == 0)
						{
							layout.m_attributes[ii] = UINT16_MAX;
						}
						if (unsettedAttr[ii] && attr != UINT16_MAX)
						{
							unsettedAttr[ii] = 0;
						}
					}

					fillVertexDecl(program.m_vsh, layout);
				}

				for (uint32_t ii = 0; ii < Attrib::Count; ++ii)
				{
					Attrib::Enum iiattr = Attrib::Enum(ii);
					if (0 < unsettedAttr[ii])
					{
					  //uint32_t numAttribs = vertexs.buffers[stream].attributeCount;
					  //uint32_t numAttribs = inputBinding->attributeCount;
					  //wgpu::VertexBufferLayout* inputAttrib = const_cast<VkVertexInputAttributeDescription*>(_vertexInputState.pVertexAttributeDescriptions + numAttribs);
						inputAttrib->shaderLocation = program.m_vsh->m_attrRemap[ii];
					  //inputAttrib->binding = 0;
						inputAttrib->format = wgpu::VertexFormat::Float3; // VK_FORMAT_R32G32B32_SFLOAT;
						inputAttrib->offset = 0;
						vertex.buffers[stream-1].attributeCount++;
						++inputAttrib;
					}
				}

				// TODO (hugoam) WebGPU will crash whenever we are not supplying the correct number of attributes (which depends on the stride passed to bgfx::allocInstanceDataBuffer)
				// so we need to know the number of live instance attributes in the shader and if they aren't all supplied:
				//   - fail the pipeline state creation
				//   - bind dummy attributes
				if (0 < _numInstanceData)
				{
					uint32_t numBindings = vertex.desc.bufferCount; // == stream+1 // .vertexBindingDescriptionCount;
					uint32_t firstAttrib = vertex.buffers[stream-1].attributeCount;
					uint32_t numAttribs = firstAttrib;

					inputBinding->arrayStride = _numInstanceData * 16;
					inputBinding->stepMode = wgpu::InputStepMode::Instance;

					for (uint32_t inst = 0; inst < _numInstanceData; ++inst)
					{
						inputAttrib->shaderLocation = numAttribs;
						inputAttrib->format = wgpu::VertexFormat::Float32x4;
						inputAttrib->offset = inst * 16;

						++numAttribs;
						++inputAttrib;
					}

					vertex.desc.bufferCount = numBindings + 1;
					vertex.buffers[stream].attributeCount = numAttribs - firstAttrib;
					vertex.buffers[stream].attributes = &vertex.attributes[firstAttrib];
				}

				bool isStrip = prim.m_type == wgpu::PrimitiveTopology::LineStrip
				 			|| prim.m_type == wgpu::PrimitiveTopology::TriangleStrip;
				if (isStrip)
					pd.desc.primitive.stripIndexFormat = _isIndex16 ? wgpu::IndexFormat::Uint16 : wgpu::IndexFormat::Uint32;
				else
					pd.desc.primitive.stripIndexFormat = wgpu::IndexFormat::Undefined;

				pd.desc.vertex = vertex.desc;

				BX_TRACE("Creating WebGPU render pipeline state for program %s", program.m_vsh->name());
				pso->m_rps = m_device.CreateRenderPipeline2(&pd.desc);

				m_pipelineStateCache.add(hash, pso);
			}

			return pso;
		}

		PipelineStateWgpu* getPipelineState(
			  uint64_t _state
			, uint64_t _stencil
			, uint32_t _rgba
			, FrameBufferHandle _fbh
			, VertexLayoutHandle _declHandle
			, bool _isIndex16
			, ProgramHandle _program
			, uint8_t _numInstanceData
			)
		{
			const VertexLayout* decl = &m_vertexDecls[_declHandle.idx];
			return getPipelineState(
				  _state
				, _stencil
				, _rgba
				, _fbh
				, 1
				, &decl
				, _isIndex16
				, _program
				, _numInstanceData
				);
		}

		PipelineStateWgpu* getComputePipelineState(ProgramHandle _program)
		{
			ProgramWgpu& program = m_program[_program.idx];

			if (NULL == program.m_computePS)
			{
				PipelineStateWgpu* pso = BX_NEW(g_allocator, PipelineStateWgpu);
				program.m_computePS = pso;

				wgpu::PipelineLayoutDescriptor layout = defaultDescriptor<wgpu::PipelineLayoutDescriptor>();
				layout.bindGroupLayouts = &program.m_bindGroupLayout;
				layout.bindGroupLayoutCount = 1;

				BX_TRACE("Creating WebGPU render pipeline layout for program %s", program.m_vsh->name());
				pso->m_layout = m_device.CreatePipelineLayout(&layout);

				wgpu::ComputePipelineDescriptor desc;
				desc.layout = pso->m_layout;
				desc.computeStage = { NULL, program.m_vsh->m_module, "main" };

				BX_TRACE("Creating WebGPU render pipeline state for program %s", program.m_vsh->name());
				pso->m_cps = m_device.CreateComputePipeline(&desc);
			}

			return program.m_computePS;
		}


		wgpu::Sampler getSamplerState(uint32_t _flags)
		{
			_flags &= BGFX_SAMPLER_BITS_MASK;
			SamplerStateWgpu* sampler = m_samplerStateCache.find(_flags);

			if (NULL == sampler)
			{
				sampler = BX_NEW(g_allocator, SamplerStateWgpu);

				wgpu::SamplerDescriptor desc;
				desc.addressModeU = s_textureAddress[(_flags&BGFX_SAMPLER_U_MASK)>>BGFX_SAMPLER_U_SHIFT];
				desc.addressModeV = s_textureAddress[(_flags&BGFX_SAMPLER_V_MASK)>>BGFX_SAMPLER_V_SHIFT];
				desc.addressModeW = s_textureAddress[(_flags&BGFX_SAMPLER_W_MASK)>>BGFX_SAMPLER_W_SHIFT];
				desc.minFilter    = s_textureFilterMinMag[(_flags&BGFX_SAMPLER_MIN_MASK)>>BGFX_SAMPLER_MIN_SHIFT];
				desc.magFilter    = s_textureFilterMinMag[(_flags&BGFX_SAMPLER_MAG_MASK)>>BGFX_SAMPLER_MAG_SHIFT];
				desc.mipmapFilter = s_textureFilterMip[(_flags&BGFX_SAMPLER_MIP_MASK)>>BGFX_SAMPLER_MIP_SHIFT];
				desc.lodMinClamp  = 0;
				desc.lodMaxClamp  = bx::kFloatMax;

				const uint32_t cmpFunc = (_flags&BGFX_SAMPLER_COMPARE_MASK)>>BGFX_SAMPLER_COMPARE_SHIFT;
				desc.compare = 0 == cmpFunc
					? wgpu::CompareFunction::Undefined
					: s_cmpFunc[cmpFunc]
					;

				sampler->m_sampler = s_renderWgpu->m_device.CreateSampler(&desc);
				m_samplerStateCache.add(_flags, sampler);
			}

			return sampler->m_sampler;
		}

		wgpu::CommandEncoder& getRenderEncoder()
		{
			if (!m_cmd.m_renderEncoder)
				m_cmd.beginRender();

			return m_cmd.m_renderEncoder;
		}

		wgpu::CommandEncoder& getStagingEncoder()
		{
			if (!m_cmd.m_stagingEncoder)
				m_cmd.beginStaging();

			return m_cmd.m_stagingEncoder;
		}

		wgpu::CommandEncoder& getBlitCommandEncoder()
		{
			if (m_renderEncoder || m_computeEncoder)
				endEncoding();

			return getRenderEncoder();
		}

		wgpu::RenderPassEncoder renderPass(bgfx::Frame* _render, bgfx::FrameBufferHandle fbh, bool clear, Clear clr, const char* name = NULL)
		{
			RenderPassStateWgpu* rps = s_renderWgpu->getRenderPassState(fbh, clear, clr);

			RenderPassDescriptor& renderPassDescriptor = rps->m_rpd;
			renderPassDescriptor.desc.label = name;

			setFrameBuffer(renderPassDescriptor, fbh);

			if(clear)
			{
				for(uint32_t ii = 0; ii < g_caps.limits.maxFBAttachments; ++ii)
				{
					wgpu::RenderPassColorAttachment& color = renderPassDescriptor.colorAttachments[ii];

					if(0 != (BGFX_CLEAR_COLOR & clr.m_flags))
					{
						if(0 != (BGFX_CLEAR_COLOR_USE_PALETTE & clr.m_flags))
						{
							uint8_t index = (uint8_t)bx::uint32_min(BGFX_CONFIG_MAX_COLOR_PALETTE - 1, clr.m_index[ii]);
							const float* rgba = _render->m_colorPalette[index];
							const float rr = rgba[0];
							const float gg = rgba[1];
							const float bb = rgba[2];
							const float aa = rgba[3];
							color.clearColor = { rr, gg, bb, aa };
						}
						else
						{
							float rr = clr.m_index[0] * 1.0f / 255.0f;
							float gg = clr.m_index[1] * 1.0f / 255.0f;
							float bb = clr.m_index[2] * 1.0f / 255.0f;
							float aa = clr.m_index[3] * 1.0f / 255.0f;
							color.clearColor = { rr, gg, bb, aa };
						}

						color.loadOp = wgpu::LoadOp::Clear;
					}
					else
					{
						color.loadOp = wgpu::LoadOp::Load;
					}

					//desc.storeOp = desc.view.sampleCount > 1 ? wgpu::StoreOp::MultisampleResolve : wgpu::StoreOp::Store;
					color.storeOp = wgpu::StoreOp::Store;
				}

				wgpu::RenderPassDepthStencilAttachment& depthStencil = renderPassDescriptor.depthStencilAttachment;

				if(depthStencil.view)
				{
					depthStencil.clearDepth = clr.m_depth;
					depthStencil.depthLoadOp = 0 != (BGFX_CLEAR_DEPTH & clr.m_flags)
						? wgpu::LoadOp::Clear
						: wgpu::LoadOp::Load
						;
					depthStencil.depthStoreOp = m_mainFrameBuffer.m_swapChain->m_backBufferColorMsaa
						? wgpu::StoreOp(0) //wgpu::StoreOp::DontCare
						: wgpu::StoreOp::Store
						;

					depthStencil.clearStencil = clr.m_stencil;
					depthStencil.stencilLoadOp = 0 != (BGFX_CLEAR_STENCIL & clr.m_flags)
						? wgpu::LoadOp::Clear
						: wgpu::LoadOp::Load
						;
					depthStencil.stencilStoreOp = m_mainFrameBuffer.m_swapChain->m_backBufferColorMsaa
						? wgpu::StoreOp(0) //wgpu::StoreOp::DontCare
						: wgpu::StoreOp::Store
						;
				}
			}
			else
			{
				for(uint32_t ii = 0; ii < g_caps.limits.maxFBAttachments; ++ii)
				{
					wgpu::RenderPassColorAttachment& color = renderPassDescriptor.colorAttachments[ii];
					if(color.view)
					{
						color.loadOp = wgpu::LoadOp::Load;
					}
				}

				wgpu::RenderPassDepthStencilAttachment& depthStencil = renderPassDescriptor.depthStencilAttachment;

				if(depthStencil.view)
				{
					depthStencil.depthLoadOp = wgpu::LoadOp::Load;
					depthStencil.depthStoreOp = wgpu::StoreOp::Store;

					depthStencil.stencilLoadOp = wgpu::LoadOp::Load;
					depthStencil.stencilStoreOp = wgpu::StoreOp::Store;
				}
			}

			wgpu::RenderPassEncoder rce = m_cmd.m_renderEncoder.BeginRenderPass(&renderPassDescriptor.desc);
			m_renderEncoder = rce;
			return rce;
		}

		void endEncoding()
		{
			if (m_renderEncoder)
			{
				m_renderEncoder.EndPass();
				m_renderEncoder = NULL;
			}

			if (m_computeEncoder)
			{
				m_computeEncoder.EndPass();
				m_computeEncoder = NULL;
			}
		}

		void* m_renderDocDll;

#if !BX_PLATFORM_EMSCRIPTEN
		dawn_native::Instance m_instance;
#endif
		wgpu::Device       m_device;
		wgpu::Queue        m_queue;
		TimerQueryWgpu     m_gpuTimer;
		CommandQueueWgpu   m_cmd;

		StagingBufferWgpu	m_uniformBuffers[WEBGPU_NUM_UNIFORM_BUFFERS];
		ScratchBufferWgpu   m_scratchBuffers[BGFX_CONFIG_MAX_FRAME_LATENCY];

		BindStateCacheWgpu  m_bindStateCache[BGFX_CONFIG_MAX_FRAME_LATENCY];

		uint8_t m_frameIndex;

		uint16_t          m_numWindows;
		FrameBufferHandle m_windows[BGFX_CONFIG_MAX_FRAME_BUFFERS];

		IndexBufferWgpu  m_indexBuffers[BGFX_CONFIG_MAX_INDEX_BUFFERS];
		VertexBufferWgpu m_vertexBuffers[BGFX_CONFIG_MAX_VERTEX_BUFFERS];
		ShaderWgpu       m_shaders[BGFX_CONFIG_MAX_SHADERS];
		ProgramWgpu      m_program[BGFX_CONFIG_MAX_PROGRAMS];
		TextureWgpu      m_textures[BGFX_CONFIG_MAX_TEXTURES];
		ReadbackWgpu     m_readbacks[BGFX_CONFIG_MAX_TEXTURES];
		FrameBufferWgpu  m_mainFrameBuffer;
		FrameBufferWgpu  m_frameBuffers[BGFX_CONFIG_MAX_FRAME_BUFFERS];
		VertexLayout     m_vertexDecls[BGFX_CONFIG_MAX_VERTEX_LAYOUTS];
		UniformRegistry  m_uniformReg;
		void*            m_uniforms[BGFX_CONFIG_MAX_UNIFORMS];

		//StateCacheT<BindStateWgpu*>   m_bindStateCache;
		StateCacheT<RenderPassStateWgpu*> m_renderPassStateCache;
		StateCacheT<PipelineStateWgpu*> m_pipelineStateCache;
		StateCacheT<SamplerStateWgpu*>  m_samplerStateCache;

		TextVideoMem m_textVideoMem;

		uint8_t m_fsScratch[64 << 10];
		uint8_t m_vsScratch[64 << 10];

		FrameBufferHandle m_fbh;
		bool m_rtMsaa;

		Resolution m_resolution;
		void* m_capture;
		uint32_t m_captureSize;

		wgpu::RenderPassEncoder     m_renderEncoder;
		wgpu::ComputePassEncoder    m_computeEncoder;
	};

	RendererContextI* rendererCreate(const Init& _init)
	{
		s_renderWgpu = BX_NEW(g_allocator, RendererContextWgpu);
		if (!s_renderWgpu->init(_init) )
		{
			BX_DELETE(g_allocator, s_renderWgpu);
			s_renderWgpu = NULL;
		}
		return s_renderWgpu;
	}

	void rendererDestroy()
	{
		s_renderWgpu->shutdown();
		BX_DELETE(g_allocator, s_renderWgpu);
		s_renderWgpu = NULL;
	}

	void writeString(bx::WriterI* _writer, const char* _str)
	{
		bx::write(_writer, _str, (int32_t)bx::strLen(_str) );
	}

	void ShaderWgpu::create(ShaderHandle _handle, const Memory* _mem)
	{
		m_handle = _handle;

		BX_TRACE("Creating shader %s", getName(_handle));

		bx::MemoryReader reader(_mem->data, _mem->size);

		bx::ErrorAssert err;

		uint32_t magic;
		bx::read(&reader, magic, &err);

		wgpu::ShaderStage shaderStage;

		if (isShaderType(magic, 'C'))
		{
			shaderStage = wgpu::ShaderStage::Compute;
		}
		else if (isShaderType(magic, 'F'))
		{
			shaderStage = wgpu::ShaderStage::Fragment;
		}
		else if (isShaderType(magic, 'G'))
		{
			//shaderStage = wgpu::ShaderStage::Geometry;
		}
		else if (isShaderType(magic, 'V'))
		{
			shaderStage = wgpu::ShaderStage::Vertex;
		}

		m_stage = shaderStage;

		uint32_t hashIn;
		bx::read(&reader, hashIn, &err);

		uint32_t hashOut;

		if (isShaderVerLess(magic, 6) )
		{
			hashOut = hashIn;
		}
		else
		{
			bx::read(&reader, hashOut, &err);
		}

		uint16_t count;
		bx::read(&reader, count, &err);

		m_numPredefined = 0;
		m_numUniforms = count;

		BX_TRACE("%s Shader consts %d"
			, getShaderTypeName(magic)
			, count
			);

		const bool fragment = isShaderType(magic, 'F');
		uint8_t fragmentBit = fragment ? kUniformFragmentBit : 0;

		BX_ASSERT(!isShaderVerLess(magic, 11), "WebGPU backend supports only shader binary version >= 11");

		if (0 < count)
		{
			for (uint32_t ii = 0; ii < count; ++ii)
			{
				uint8_t nameSize = 0;
				bx::read(&reader, nameSize, &err);

				char name[256];
				bx::read(&reader, &name, nameSize, &err);
				name[nameSize] = '\0';

				uint8_t type = 0;
				bx::read(&reader, type, &err);

				uint8_t num;
				bx::read(&reader, num, &err);

				uint16_t regIndex;
				bx::read(&reader, regIndex, &err);

				uint16_t regCount;
				bx::read(&reader, regCount, &err);

				uint8_t texComponent;
				bx::read(&reader, texComponent, &err);

				uint8_t texDimension;
				bx::read(&reader, texDimension, &err);

				uint16_t texFormat = 0;
				bx::read(&reader, texFormat, &err);

				const char* kind = "invalid";

				PredefinedUniform::Enum predefined = nameToPredefinedUniformEnum(name);
				if (PredefinedUniform::Count != predefined)
				{
					kind = "predefined";
					m_predefined[m_numPredefined].m_loc   = regIndex;
					m_predefined[m_numPredefined].m_count = regCount;
					m_predefined[m_numPredefined].m_type  = uint8_t(predefined|fragmentBit);
					m_numPredefined++;
				}
				else if (UniformType::End == (~kUniformMask & type))
				{
					// regCount is used for descriptor type
					const bool buffer = idToDescriptorType(regCount) == DescriptorType::StorageBuffer;
					const bool readonly = (type & kUniformReadOnlyBit) != 0;

					const uint8_t reverseShift = kSpirvBindShift;
					const uint8_t stage = regIndex - reverseShift;

					m_bindInfo[stage].m_index = m_numBuffers;
					m_bindInfo[stage].m_binding = regIndex;
					m_bindInfo[stage].m_uniform = { 0 };

					m_buffers[m_numBuffers] = wgpu::BindGroupLayoutEntry();
					m_buffers[m_numBuffers].binding = regIndex;
					m_buffers[m_numBuffers].visibility = shaderStage;

					if (buffer)
					{
						m_buffers[m_numBuffers].buffer.type = readonly
							? wgpu::BufferBindingType::ReadOnlyStorage
							: wgpu::BufferBindingType::Storage;
					}
					else
					{
						m_buffers[m_numBuffers].storageTexture.access = readonly
							? wgpu::StorageTextureAccess::ReadOnly
							: wgpu::StorageTextureAccess::WriteOnly;

						m_buffers[m_numBuffers].storageTexture.format = s_textureFormat[texFormat].m_fmt;
					}

					m_numBuffers++;

					kind = "storage";
				}
				else if (UniformType::Sampler == (~kUniformMask & type))
				{
					const UniformRegInfo* info = s_renderWgpu->m_uniformReg.find(name);
					BX_ASSERT(NULL != info, "User defined uniform '%s' is not found, it won't be set.", name);

					const uint8_t reverseShift = kSpirvBindShift;
					const uint8_t stage = regIndex - reverseShift;

					m_bindInfo[stage].m_index = m_numSamplers;
					m_bindInfo[stage].m_binding = regIndex;
					m_bindInfo[stage].m_uniform = info->m_handle;

					auto textureDimensionToWgpu = [](TextureDimension::Enum dimension)
					{
						switch (dimension)
						{
						case TextureDimension::Dimension1D:        return wgpu::TextureViewDimension::e1D;
						case TextureDimension::Dimension2D:        return wgpu::TextureViewDimension::e2D;
						case TextureDimension::Dimension2DArray:   return wgpu::TextureViewDimension::e2DArray;
						case TextureDimension::DimensionCube:      return wgpu::TextureViewDimension::Cube;
						case TextureDimension::DimensionCubeArray: return wgpu::TextureViewDimension::CubeArray;
						case TextureDimension::Dimension3D:        return wgpu::TextureViewDimension::e3D;
						default:                                   return wgpu::TextureViewDimension::Undefined;
						}
					};

					auto textureComponentToWgpuSampleType = [](TextureComponentType::Enum componentType)
					{
						switch (componentType)
						{
						case TextureComponentType::Float: return wgpu::TextureSampleType::Float;
						case TextureComponentType::Int:   return wgpu::TextureSampleType::Sint;
						case TextureComponentType::Uint:  return wgpu::TextureSampleType::Uint;
						default:                          return wgpu::TextureSampleType::Float;
						}
					};

					m_textures[m_numSamplers] = wgpu::BindGroupLayoutEntry();
					m_textures[m_numSamplers].binding = regIndex;
					m_textures[m_numSamplers].visibility = shaderStage;
					m_textures[m_numSamplers].texture.viewDimension = textureDimensionToWgpu(idToTextureDimension(texDimension));
					m_textures[m_numSamplers].texture.sampleType = textureComponentToWgpuSampleType(idToTextureComponentType(texComponent));

					const bool comparisonSampler = (type & kUniformCompareBit) != 0;

					m_samplers[m_numSamplers] = wgpu::BindGroupLayoutEntry();
					m_samplers[m_numSamplers].binding = regIndex + kSpirvSamplerShift;
					m_samplers[m_numSamplers].visibility = shaderStage;
					m_samplers[m_numSamplers].sampler.type = comparisonSampler
						? wgpu::SamplerBindingType::Comparison
						: wgpu::SamplerBindingType::Filtering
						;

					m_numSamplers++;

					kind = "sampler";
				}
				else
				{
					const UniformRegInfo* info = s_renderWgpu->m_uniformReg.find(name);
					BX_ASSERT(NULL != info, "User defined uniform '%s' is not found, it won't be set.", name);

					if(NULL == m_constantBuffer)
					{
						m_constantBuffer = UniformBuffer::create(1024);
					}

					kind = "user";
					m_constantBuffer->writeUniformHandle((UniformType::Enum)(type | fragmentBit), regIndex, info->m_handle, regCount);
				}

				BX_TRACE("\t%s: %s (%s), r.index %3d, r.count %2d, r.texComponent %1d, r.texDimension %1d"
					, kind
					, name
					, getUniformTypeName(UniformType::Enum(type&~kUniformMask) )
					, regIndex
					, regCount
					, texComponent
					, texDimension
					);
				BX_UNUSED(kind);
			}

			if (NULL != m_constantBuffer)
			{
				m_constantBuffer->finish();
			}
		}

		uint32_t shaderSize;
		bx::read(&reader, shaderSize, &err);

		BX_TRACE("Shader body is at %lld size %u remaining %lld", reader.getPos(), shaderSize, reader.remaining());

		const uint32_t* code = (const uint32_t*)reader.getDataPtr();
		bx::skip(&reader, shaderSize+1);

		m_code = (uint32_t*)BX_ALLOC(g_allocator, shaderSize);
		m_codeSize = shaderSize;

		bx::memCopy(m_code, code, shaderSize);
		// TODO (hugoam) delete this

		BX_TRACE("First word %08" PRIx32, code[0]);

		uint8_t numAttrs = 0;
		bx::read(&reader, numAttrs, &err);

		m_numAttrs = numAttrs;

		bx::memSet(m_attrMask, 0, sizeof(m_attrMask));
		bx::memSet(m_attrRemap, UINT8_MAX, sizeof(m_attrRemap));

		for(uint8_t ii = 0; ii < numAttrs; ++ii)
		{
			uint16_t id;
			bx::read(&reader, id, &err);

			auto toString = [](Attrib::Enum attr)
			{
				if (attr == Attrib::Position) return "Position";
				else if (attr == Attrib::Normal) return "Normal";
				else if (attr == Attrib::Tangent) return "Tangent";
				else if (attr == Attrib::Bitangent) return "Bitangent";
				else if (attr == Attrib::Color0) return "Color0";
				else if (attr == Attrib::Color1) return "Color1";
				else if (attr == Attrib::Color2) return "Color2";
				else if (attr == Attrib::Color3) return "Color3";
				else if (attr == Attrib::Indices) return "Indices";
				else if (attr == Attrib::Weight) return "Weight";
				else if (attr == Attrib::TexCoord0) return "TexCoord0";
				else if (attr == Attrib::TexCoord1) return "TexCoord1";
				else if (attr == Attrib::TexCoord2) return "TexCoord2";
				else if (attr == Attrib::TexCoord3) return "TexCoord3";
				else if (attr == Attrib::TexCoord4) return "TexCoord4";
				else if (attr == Attrib::TexCoord5) return "TexCoord5";
				else if (attr == Attrib::TexCoord6) return "TexCoord6";
				else if (attr == Attrib::TexCoord7) return "TexCoord7";
				return "Invalid";
			};

			Attrib::Enum attr = idToAttrib(id);

			if(Attrib::Count != attr)
			{
				m_attrMask[attr] = UINT16_MAX;
				m_attrRemap[attr] = ii;
				BX_TRACE("\tattrib: %s (%i) at index %i", toString(attr), attr, ii);
			}
		}

		wgpu::ShaderModuleSPIRVDescriptor spirv;
		spirv.code = m_code;
		spirv.codeSize = shaderSize / 4;

		wgpu::ShaderModuleDescriptor desc;
		desc.label = getName(_handle);
		desc.nextInChain = &spirv;

		m_module = s_renderWgpu->m_device.CreateShaderModule(&desc);

		BGFX_FATAL(m_module
			, bgfx::Fatal::InvalidShader
			, "Failed to create %s shader."
			, getShaderTypeName(magic)
			);

		bx::HashMurmur2A murmur;
		murmur.begin();
		murmur.add(hashIn);
		murmur.add(hashOut);
		murmur.add(code, shaderSize);
		murmur.add(numAttrs);
		murmur.add(m_attrMask, numAttrs);
		m_hash = murmur.end();

		auto roundUp = [](auto value, auto multiple)
		{
			return ((value + multiple - 1) / multiple) * multiple;
		};

		bx::read(&reader, m_size, &err);

		const uint32_t align = kMinBufferOffsetAlignment;
		m_gpuSize = uint16_t(bx::strideAlign(m_size, align) );

		BX_TRACE("shader size %d (used=%d) (prev=%d)", (int)m_size, (int)m_gpuSize, (int)bx::strideAlign(roundUp(m_size, 4), align));
	}

	void ProgramWgpu::create(const ShaderWgpu* _vsh, const ShaderWgpu* _fsh)
	{
		BX_ASSERT(_vsh->m_module, "Vertex shader doesn't exist.");
		m_vsh = _vsh;
		m_fsh = _fsh;
		m_gpuSize = _vsh->m_gpuSize + (_fsh ? _fsh->m_gpuSize : 0);

		//BX_ASSERT(NULL != _vsh->m_code, "Vertex shader doesn't exist.");
		m_vsh = _vsh;
		bx::memCopy(&m_predefined[0], _vsh->m_predefined, _vsh->m_numPredefined * sizeof(PredefinedUniform));
		m_numPredefined = _vsh->m_numPredefined;

		if(NULL != _fsh)
		{
			//BX_ASSERT(NULL != _fsh->m_code, "Fragment shader doesn't exist.");
			m_fsh = _fsh;
			bx::memCopy(&m_predefined[m_numPredefined], _fsh->m_predefined, _fsh->m_numPredefined * sizeof(PredefinedUniform));
			m_numPredefined += _fsh->m_numPredefined;
		}

		wgpu::BindGroupLayoutEntry bindings[2 + BGFX_CONFIG_MAX_TEXTURE_SAMPLERS * 3];

		m_numUniforms = 0 + (_vsh->m_size > 0 ? 1 : 0) + (NULL != _fsh && _fsh->m_size > 0 ? 1 : 0);

		uint8_t numBindings = 0;

		if (_vsh->m_size > 0)
		{
			bindings[numBindings].binding = kSpirvVertexBinding;
			bindings[numBindings].visibility = _vsh->m_stage;
			bindings[numBindings].buffer.type = wgpu::BufferBindingType::Uniform;
			bindings[numBindings].buffer.hasDynamicOffset = true;
			numBindings++;
		}

		if (NULL != _fsh && _fsh->m_size > 0)
		{
			bindings[numBindings].binding = kSpirvFragmentBinding;
			bindings[numBindings].visibility = wgpu::ShaderStage::Fragment;
			bindings[numBindings].buffer.type = wgpu::BufferBindingType::Uniform;
			bindings[numBindings].buffer.hasDynamicOffset = true;
			numBindings++;
		}

		uint8_t numSamplers = 0;

		for (uint32_t ii = 0; ii < _vsh->m_numSamplers; ++ii)
		{
			m_textures[ii] = _vsh->m_textures[ii];
			m_samplers[ii] = _vsh->m_samplers[ii];
			bindings[numBindings++] = _vsh->m_textures[ii];
			bindings[numBindings++] = _vsh->m_samplers[ii];
		}

		numSamplers += _vsh->m_numSamplers;

		if (NULL != _fsh)
		{
			for (uint32_t ii = 0; ii < _fsh->m_numSamplers; ++ii)
			{
				m_textures[numSamplers + ii] = _fsh->m_textures[ii];
				m_samplers[numSamplers + ii] = _fsh->m_samplers[ii];
				bindings[numBindings++] = _fsh->m_textures[ii];
				bindings[numBindings++] = _fsh->m_samplers[ii];
			}

			numSamplers += _fsh->m_numSamplers;
		}

		for (uint8_t stage = 0; stage < BGFX_CONFIG_MAX_TEXTURE_SAMPLERS; ++stage)
		{
			if (isValid(m_vsh->m_bindInfo[stage].m_uniform))
			{
				m_bindInfo[stage] = m_vsh->m_bindInfo[stage];
			}
			else if (NULL != m_fsh && isValid(m_fsh->m_bindInfo[stage].m_uniform))
			{
				m_bindInfo[stage] = m_fsh->m_bindInfo[stage];
				m_bindInfo[stage].m_index += _vsh->m_numSamplers;
			}
		}

		m_numSamplers = numSamplers;

		uint8_t numBuffers = 0;

		for (uint32_t ii = 0; ii < _vsh->m_numBuffers; ++ii)
		{
			m_buffers[ii] = _vsh->m_buffers[ii];
			bindings[numBindings++] = _vsh->m_buffers[ii];
		}

		numBuffers += _vsh->m_numBuffers;

		if (NULL != _fsh)
		{
			for (uint32_t ii = 0; ii < _fsh->m_numBuffers; ++ii)
			{
				m_buffers[numBuffers + ii] = _fsh->m_buffers[ii];
				bindings[numBindings++] = _fsh->m_buffers[ii];
			}

			numBuffers += _fsh->m_numBuffers;
		}

		m_numBuffers = numBuffers;

		BX_ASSERT(m_numUniforms + m_numSamplers * 2 + m_numBuffers == numBindings, "");

		wgpu::BindGroupLayoutDescriptor bindGroupDesc;
		bindGroupDesc.entryCount = numBindings;
		bindGroupDesc.entries = bindings;
		m_bindGroupLayout = s_renderWgpu->m_device.CreateBindGroupLayout(&bindGroupDesc);

		bx::HashMurmur2A murmur;
		murmur.begin();
		murmur.add(m_numUniforms);
		murmur.add(m_textures, sizeof(wgpu::BindGroupLayoutEntry) * numSamplers);
		murmur.add(m_samplers, sizeof(wgpu::BindGroupLayoutEntry) * numSamplers);
		murmur.add(m_buffers,  sizeof(wgpu::BindGroupLayoutEntry) * m_numBuffers);
		m_bindGroupLayoutHash = murmur.end();
	}

	void ProgramWgpu::destroy()
	{
		m_vsh = NULL;
		m_fsh = NULL;
		if ( NULL != m_computePS )
		{
			BX_DELETE(g_allocator, m_computePS);
			m_computePS = NULL;
		}
	}

	void BufferWgpu::create(uint32_t _size, void* _data, uint16_t _flags, uint16_t _stride, bool _vertex)
	{
		BX_UNUSED(_stride);

		m_size = _size;
		m_flags = _flags;
		m_vertex = _vertex;

		const uint32_t paddedSize = bx::strideAlign(_size, 4);

		bool storage = m_flags & BGFX_BUFFER_COMPUTE_READ_WRITE;
		bool indirect = m_flags & BGFX_BUFFER_DRAW_INDIRECT;

		wgpu::BufferDescriptor desc;
		desc.size = paddedSize;
		desc.usage = _vertex ? wgpu::BufferUsage::Vertex : wgpu::BufferUsage::Index;
		desc.usage |= (storage || indirect) ? wgpu::BufferUsage::Storage : wgpu::BufferUsage::None;
		desc.usage |= indirect ? wgpu::BufferUsage::Indirect : wgpu::BufferUsage::None;
		desc.usage |= NULL == _data ? wgpu::BufferUsage::CopyDst : wgpu::BufferUsage::None;
		desc.mappedAtCreation = NULL != _data;

		m_ptr = s_renderWgpu->m_device.CreateBuffer(&desc);

		if(NULL != _data)
		{
			bx::memCopy(m_ptr.GetMappedRange(), _data, _size);
			m_ptr.Unmap();
		}
	}

	void BufferWgpu::update(uint32_t _offset, uint32_t _size, void* _data, bool _discard)
	{
		wgpu::CommandEncoder& bce = s_renderWgpu->getBlitCommandEncoder();

		if (!m_vertex && !_discard)
		{
			if ( m_dynamic == NULL )
			{
				m_dynamic = (uint8_t*)BX_ALLOC(g_allocator, m_size);
			}

			bx::memCopy(m_dynamic + _offset, _data, _size);
			uint32_t start = _offset & 4;
			uint32_t end = bx::strideAlign(_offset + _size, 4);

			wgpu::BufferDescriptor desc;
			desc.size = end - start;
			desc.usage = wgpu::BufferUsage::CopyDst | wgpu::BufferUsage::CopySrc;
			desc.mappedAtCreation = true;

			wgpu::Buffer staging = s_renderWgpu->m_device.CreateBuffer(&desc);
			bx::memCopy(staging.GetMappedRange(), m_dynamic, end - start);
			staging.Unmap();

			// TODO pad to 4 bytes
			bce.CopyBufferToBuffer(staging, 0, m_ptr, start, end - start);
			s_renderWgpu->m_cmd.release(staging);
		}
		else
		{
			wgpu::BufferDescriptor desc;
			desc.size = _size;
			desc.usage = wgpu::BufferUsage::CopyDst | wgpu::BufferUsage::CopySrc;
			desc.mappedAtCreation = true;

			wgpu::Buffer staging = s_renderWgpu->m_device.CreateBuffer(&desc);
			bx::memCopy(staging.GetMappedRange(), _data, _size);
			staging.Unmap();

			bce.CopyBufferToBuffer(staging, 0, m_ptr, _offset, _size);
			s_renderWgpu->m_cmd.release(staging);
		}
	}

	void IndexBufferWgpu::create(uint32_t _size, void* _data, uint16_t _flags)
	{
		m_format = (_flags & BGFX_BUFFER_INDEX32) != 0
			? wgpu::IndexFormat::Uint32
			: wgpu::IndexFormat::Uint16;

		BufferWgpu::create(_size, _data, _flags);
	}

	void VertexBufferWgpu::create(uint32_t _size, void* _data, VertexLayoutHandle _layoutHandle, uint16_t _flags)
	{
		m_layoutHandle = _layoutHandle;
		uint16_t stride = isValid(_layoutHandle)
			? s_renderWgpu->m_vertexDecls[_layoutHandle.idx].m_stride
			: 0
			;

		BufferWgpu::create(_size, _data, _flags, stride, true);
	}

	void TextureWgpu::create(TextureHandle _handle, const Memory* _mem, uint64_t _flags, uint8_t _skip)
	{
		m_handle = _handle;

		m_sampler = s_renderWgpu->getSamplerState(uint32_t(_flags) );

		bimg::ImageContainer imageContainer;

		if (bimg::imageParse(imageContainer, _mem->data, _mem->size) )
		{
			const bimg::ImageBlockInfo& blockInfo = getBlockInfo(bimg::TextureFormat::Enum(imageContainer.m_format) );
			const uint8_t startLod = bx::min<uint8_t>(_skip, imageContainer.m_numMips-1);

			bimg::TextureInfo ti;
			bimg::imageGetSize(
				  &ti
				, uint16_t(imageContainer.m_width >>startLod)
				, uint16_t(imageContainer.m_height>>startLod)
				, uint16_t(imageContainer.m_depth >>startLod)
				, imageContainer.m_cubeMap
				, 1 < imageContainer.m_numMips
				, imageContainer.m_numLayers
				, imageContainer.m_format
				);
			ti.numMips = bx::min<uint8_t>(imageContainer.m_numMips-startLod, ti.numMips);

			m_flags     = _flags;
			m_width     = ti.width;
			m_height    = ti.height;
			m_depth     = ti.depth;
			m_numLayers = ti.numLayers;
			m_numMips   = ti.numMips;
			m_numSides  = ti.numLayers * (imageContainer.m_cubeMap ? 6 : 1);
			m_requestedFormat  = TextureFormat::Enum(imageContainer.m_format);
			m_textureFormat    = getViableTextureFormat(imageContainer);

			if (m_requestedFormat == bgfx::TextureFormat::D16)
				m_textureFormat = bgfx::TextureFormat::D32F;

			const bool compressed = bimg::isCompressed(bimg::TextureFormat::Enum(imageContainer.m_format));

			if (compressed)
				m_textureFormat = bgfx::TextureFormat::BGRA8;

			const bool convert = m_textureFormat != m_requestedFormat;
			const uint8_t bpp  = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(m_textureFormat) );

			wgpu::TextureDescriptor desc = defaultDescriptor<wgpu::TextureDescriptor>();
			//desc.label = getName(_handle);

			if (1 < ti.numLayers)
			{
				if (imageContainer.m_cubeMap)
				{
					m_type = TextureCube;
					desc.dimension = wgpu::TextureDimension::e2D;
				}
				else
				{
					m_type = Texture2D;
					desc.dimension = wgpu::TextureDimension::e2D;
				}
			}
			else if (imageContainer.m_cubeMap)
			{
				m_type = TextureCube;
				desc.dimension = wgpu::TextureDimension::e2D;
			}
			else if (1 < imageContainer.m_depth)
			{
				m_type = Texture3D;
				desc.dimension = wgpu::TextureDimension::e3D;
			}
			else
			{
				m_type = Texture2D;
				desc.dimension = wgpu::TextureDimension::e2D;
			}

			const uint16_t numSides = ti.numLayers * (imageContainer.m_cubeMap ? 6 : 1);
			const uint32_t numSrd = numSides * ti.numMips;

			const bool writeOnly    = 0 != (_flags&BGFX_TEXTURE_RT_WRITE_ONLY);
			const bool computeWrite = 0 != (_flags&BGFX_TEXTURE_COMPUTE_WRITE);
			const bool renderTarget = 0 != (_flags&BGFX_TEXTURE_RT_MASK);
			const bool srgb         = 0 != (_flags&BGFX_TEXTURE_SRGB);

			BX_TRACE("Texture %3d: %s (requested: %s), layers %d, %dx%d%s RT[%c], WO[%c], CW[%c], sRGB[%c]"
				, this - s_renderWgpu->m_textures
				, getName( (TextureFormat::Enum)m_textureFormat)
				, getName( (TextureFormat::Enum)m_requestedFormat)
				, ti.numLayers
				, ti.width
				, ti.height
				, imageContainer.m_cubeMap ? "x6" : ""
				, renderTarget ? 'x' : ' '
				, writeOnly    ? 'x' : ' '
				, computeWrite ? 'x' : ' '
				, srgb         ? 'x' : ' '
				);

			const uint32_t msaaQuality = bx::uint32_satsub( (_flags&BGFX_TEXTURE_RT_MSAA_MASK)>>BGFX_TEXTURE_RT_MSAA_SHIFT, 1);
			const int32_t  sampleCount = s_msaa[msaaQuality];


			wgpu::TextureFormat format = wgpu::TextureFormat::Undefined;
			if (srgb)
			{
				format = s_textureFormat[m_textureFormat].m_fmtSrgb;
				BX_WARN(format != wgpu::TextureFormat::Undefined
					, "sRGB not supported for texture format %d"
					, m_textureFormat
					);
			}

			if (format == wgpu::TextureFormat::Undefined)
			{
				// not swizzled and not sRGB, or sRGB unsupported
				format = s_textureFormat[m_textureFormat].m_fmt;
			}

			desc.format = format;
			desc.size.width  = m_width;
			desc.size.height = m_height;
			desc.size.depthOrArrayLayers = m_numSides * bx::uint32_max(1,imageContainer.m_depth);
			desc.mipLevelCount    = m_numMips;
			desc.sampleCount      = 1;

			desc.usage = wgpu::TextureUsage::Sampled;
			desc.usage |= wgpu::TextureUsage::CopyDst;
			desc.usage |= wgpu::TextureUsage::CopySrc;

			if (computeWrite)
			{
				desc.usage |= wgpu::TextureUsage::Storage;
			}

			if (renderTarget)
			{
				desc.usage |= wgpu::TextureUsage::OutputAttachment;
			}

			m_ptr = s_renderWgpu->m_device.CreateTexture(&desc);

			if (sampleCount > 1)
			{
				desc.sampleCount = sampleCount;

				m_ptrMsaa = s_renderWgpu->m_device.CreateTexture(&desc);
			}

			// decode images
			struct ImageInfo
			{
				uint8_t* data;
				uint32_t width;
				uint32_t height;
				uint32_t depth;
				uint32_t pitch;
				uint32_t slice;
				uint32_t size;
				uint8_t mipLevel;
				uint8_t layer;
			};

			ImageInfo* imageInfos = (ImageInfo*)BX_ALLOC(g_allocator, sizeof(ImageInfo) * numSrd);
			bx::memSet(imageInfos, 0, sizeof(ImageInfo) * numSrd);
			uint32_t alignment = 1; // tightly aligned buffer

			uint32_t kk = 0;

			for (uint8_t side = 0; side < numSides; ++side)
			{
				for (uint8_t lod = 0; lod < ti.numMips; ++lod)
				{
					bimg::ImageMip mip;
					if (bimg::imageGetRawData(imageContainer, side, lod + startLod, _mem->data, _mem->size, mip))
					{
						if (convert)
						{
							const uint32_t pitch = bx::strideAlign(bx::max<uint32_t>(mip.m_width, 4) * bpp / 8, alignment);
							const uint32_t slice = bx::strideAlign(bx::max<uint32_t>(mip.m_height, 4) * pitch, alignment);
							const uint32_t size = slice * mip.m_depth;

							uint8_t* temp = (uint8_t*)BX_ALLOC(g_allocator, size);
							bimg::imageDecodeToBgra8(
								  g_allocator
								, temp
								, mip.m_data
								, mip.m_width
								, mip.m_height
								, pitch
								, mip.m_format
								);

							imageInfos[kk].data = temp;
							imageInfos[kk].width = mip.m_width;
							imageInfos[kk].height = mip.m_height;
							imageInfos[kk].depth = mip.m_depth;
							imageInfos[kk].pitch = pitch;
							imageInfos[kk].slice = slice;
							imageInfos[kk].size = size;
							imageInfos[kk].mipLevel = lod;
							imageInfos[kk].layer = side;
						}
						else if (compressed)
						{
							const uint32_t pitch = bx::strideAlign((mip.m_width / blockInfo.blockWidth) * mip.m_blockSize, alignment);
							const uint32_t slice = bx::strideAlign((mip.m_height / blockInfo.blockHeight) * pitch, alignment);
							const uint32_t size = slice * mip.m_depth;

							uint8_t* temp = (uint8_t*)BX_ALLOC(g_allocator, size);
							bimg::imageCopy(
								  temp
								, mip.m_height / blockInfo.blockHeight
								, (mip.m_width / blockInfo.blockWidth) * mip.m_blockSize
								, mip.m_depth
								, mip.m_data
								, pitch
								);

							imageInfos[kk].data = temp;
							imageInfos[kk].width = mip.m_width;
							imageInfos[kk].height = mip.m_height;
							imageInfos[kk].depth = mip.m_depth;
							imageInfos[kk].pitch = pitch;
							imageInfos[kk].slice = slice;
							imageInfos[kk].size = size;
							imageInfos[kk].mipLevel = lod;
							imageInfos[kk].layer = side;
						}
						else
						{
							const uint32_t pitch = bx::strideAlign(mip.m_width * mip.m_bpp / 8, alignment);
							const uint32_t slice = bx::strideAlign(mip.m_height * pitch, alignment);
							const uint32_t size = slice * mip.m_depth;

							uint8_t* temp = (uint8_t*)BX_ALLOC(g_allocator, size);
							bimg::imageCopy(temp
								, mip.m_height
								, mip.m_width * mip.m_bpp / 8
								, mip.m_depth
								, mip.m_data
								, pitch
							);

							imageInfos[kk].data = temp;
							imageInfos[kk].width = mip.m_width;
							imageInfos[kk].height = mip.m_height;
							imageInfos[kk].depth = mip.m_depth;
							imageInfos[kk].pitch = pitch;
							imageInfos[kk].slice = slice;
							imageInfos[kk].size = size;
							imageInfos[kk].mipLevel = lod;
							imageInfos[kk].layer = side;
						}
					}
					++kk;
				}
			}

			uint32_t totalMemSize = 0;
			for (uint32_t ii = 0; ii < numSrd; ++ii)
			{
				const uint32_t dstpitch = bx::strideAlign(imageInfos[ii].pitch, kMinBufferOffsetAlignment);
				totalMemSize += dstpitch * imageInfos[ii].height;
				//totalMemSize += imageInfos[ii].size;
			}

			wgpu::Buffer stagingBuffer;
			if (totalMemSize > 0)
			{
				wgpu::BufferDescriptor staginBufferDesc;
				staginBufferDesc.size = totalMemSize;
				staginBufferDesc.usage = wgpu::BufferUsage::CopyDst | wgpu::BufferUsage::CopySrc;
				staginBufferDesc.mappedAtCreation = true;

				stagingBuffer = s_renderWgpu->m_device.CreateBuffer(&staginBufferDesc);
				void* stagingData = stagingBuffer.GetMappedRange();

				uint64_t offset = 0;

				for (uint32_t ii = 0; ii < numSrd; ++ii)
				{
					const uint32_t dstpitch = bx::strideAlign(imageInfos[ii].pitch, kMinBufferOffsetAlignment);

					const uint8_t* src = (uint8_t*)imageInfos[ii].data;
					uint8_t* dst = (uint8_t*)stagingData;

					for (uint32_t yy = 0; yy < imageInfos[ii].height; ++yy, src += imageInfos[ii].pitch, offset += dstpitch)
					{
						bx::memCopy(dst + offset, src, imageInfos[ii].pitch);
					}

					//bx::memCopy(dst + offset, imageInfos[ii].data, imageInfos[ii].size);
					//offset += imageInfos[ii].size;
				}

				stagingBuffer.Unmap();
			}

			wgpu::ImageCopyBuffer* imageCopyBuffer = (wgpu::ImageCopyBuffer*)BX_ALLOC(g_allocator, sizeof(wgpu::ImageCopyBuffer) * numSrd);
			wgpu::ImageCopyTexture* imageCopyTexture = (wgpu::ImageCopyTexture*)BX_ALLOC(g_allocator, sizeof(wgpu::ImageCopyTexture) * numSrd);
			wgpu::Extent3D* textureCopySize = (wgpu::Extent3D*)BX_ALLOC(g_allocator, sizeof(wgpu::Extent3D) * numSrd);

			uint64_t offset = 0;

			for (uint32_t ii = 0; ii < numSrd; ++ii)
			{
				const uint32_t dstpitch = bx::strideAlign(imageInfos[ii].pitch, kMinBufferOffsetAlignment);

				uint32_t idealWidth  = bx::max<uint32_t>(1, m_width  >> imageInfos[ii].mipLevel);
				uint32_t idealHeight = bx::max<uint32_t>(1, m_height >> imageInfos[ii].mipLevel);
				BX_PLACEMENT_NEW(&imageCopyBuffer[ii], wgpu::ImageCopyBuffer)();
				BX_PLACEMENT_NEW(&imageCopyTexture[ii], wgpu::ImageCopyTexture)();
				BX_PLACEMENT_NEW(&textureCopySize[ii], wgpu::Extent3D)();
				imageCopyBuffer[ii].buffer              = stagingBuffer;
				imageCopyBuffer[ii].layout.offset       = offset;
				imageCopyBuffer[ii].layout.bytesPerRow  = dstpitch; // assume that image data are tightly aligned
				imageCopyBuffer[ii].layout.rowsPerImage = 0; // assume that image data are tightly aligned
				imageCopyTexture[ii].texture            = m_ptr;
				imageCopyTexture[ii].mipLevel       = imageInfos[ii].mipLevel;
				imageCopyTexture[ii].origin         = { 0, 0, imageInfos[ii].layer };
				textureCopySize[ii] = { idealWidth, idealHeight, imageInfos[ii].depth };

				offset += dstpitch * imageInfos[ii].height;
				//offset += imageInfos[ii].size;
			}


			if (stagingBuffer)
			{
				wgpu::CommandEncoder encoder = s_renderWgpu->getBlitCommandEncoder();
				//wgpu::CommandEncoder encoder = s_renderWgpu->m_cmd.m_encoder;
				for (uint32_t ii = 0; ii < numSrd; ++ii)
				{
					encoder.CopyBufferToTexture(&imageCopyBuffer[ii], &imageCopyTexture[ii], &textureCopySize[ii]);
				}
			}
			else
			{
				//VkCommandBuffer commandBuffer = s_renderVK->beginNewCommand();
				//setImageMemoryBarrier(
				//	commandBuffer
				//	, (m_flags & BGFX_TEXTURE_COMPUTE_WRITE
				//		? VK_IMAGE_LAYOUT_GENERAL
				//		: VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
				//		)
				//);
				//s_renderVK->submitCommandAndWait(commandBuffer);
			}

			//vkFreeMemory(device, stagingDeviceMem, allocatorCb);
			//vkDestroy(stagingBuffer);

			BX_FREE(g_allocator, imageCopyBuffer);
			BX_FREE(g_allocator, imageCopyTexture);
			BX_FREE(g_allocator, textureCopySize);
			for (uint32_t ii = 0; ii < numSrd; ++ii)
			{
				BX_FREE(g_allocator, imageInfos[ii].data);
			}
			BX_FREE(g_allocator, imageInfos);
		}
	}

	void TextureWgpu::update(uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem)
	{
		const uint32_t bpp       = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(m_textureFormat) );
		const uint32_t rectpitch = _rect.m_width*bpp/8;
		const uint32_t srcpitch  = UINT16_MAX == _pitch ? rectpitch : _pitch;
		const uint16_t zz        = (m_type == Texture3D) ? _z : _side;
		// TODO (hugoam) This won't work for 3D texture arrays, but do we even support that

		const bool convert = m_textureFormat != m_requestedFormat;

		uint8_t* data = _mem->data;
		uint8_t* temp = NULL;

		if (convert)
		{
			temp = (uint8_t*)BX_ALLOC(g_allocator, rectpitch*_rect.m_height);
			bimg::imageDecodeToBgra8(
				  g_allocator
				, temp
				, data
				, _rect.m_width
				, _rect.m_height
				, srcpitch
				, bimg::TextureFormat::Enum(m_requestedFormat)
				);
			data = temp;
		}

		const uint32_t dstpitch = bx::strideAlign(rectpitch, kMinBufferOffsetAlignment);

		wgpu::BufferDescriptor desc;
		desc.size = dstpitch * _rect.m_height;
		desc.usage = wgpu::BufferUsage::CopyDst | wgpu::BufferUsage::CopySrc;
		desc.mappedAtCreation = true;

		wgpu::Buffer staging = s_renderWgpu->m_device.CreateBuffer(&desc);

		const uint8_t* src = (uint8_t*)data;
		uint8_t* dst = (uint8_t*)staging.GetMappedRange();
		uint64_t offset = 0;

		for (uint32_t yy = 0; yy < _rect.m_height; ++yy, src += srcpitch, offset += dstpitch)
		{
			const uint32_t size = bx::strideAlign(rectpitch, 4);
			bx::memCopy(dst + offset, src, size);
		}

		staging.Unmap();

		wgpu::ImageCopyBuffer srcView;
		srcView.buffer = staging;
		srcView.layout.bytesPerRow = dstpitch;
		srcView.layout.rowsPerImage = 0;

		wgpu::ImageCopyTexture destView;
		destView.texture = m_ptr;
		destView.mipLevel = _mip;
		destView.origin = { _rect.m_x, _rect.m_y, zz };

		wgpu::Extent3D destExtent = { _rect.m_width, _rect.m_height, _depth };

		//region.imageSubresource.aspectMask = m_vkTextureAspect;

		wgpu::CommandEncoder encoder = s_renderWgpu->getBlitCommandEncoder();
		//wgpu::CommandEncoder encoder = s_renderWgpu->m_cmd.m_encoder;
		encoder.CopyBufferToTexture(&srcView, &destView, &destExtent);

		//wgpu::CommandBuffer copy = encoder.Finish();
		//wgpu::Queue queue = s_renderWgpu->m_queue;
		//queue.Submit(1, &copy);

		//staging.Destroy();

		if (NULL != temp)
		{
			BX_FREE(g_allocator, temp);
		}
	}

	void BindStateWgpu::clear()
	{
		m_bindGroup = NULL;
	}

	void StagingBufferWgpu::create(uint32_t _size, bool mapped)
	{
		m_size = _size;

		wgpu::BufferDescriptor desc;
		desc.size = _size;
		desc.usage = wgpu::BufferUsage::MapWrite | wgpu::BufferUsage::CopySrc;
		desc.mappedAtCreation = mapped;

		m_buffer = s_renderWgpu->m_device.CreateBuffer(&desc);

		if (mapped)
		{
			m_data = m_buffer.GetMappedRange();
		}
		else
		{
			map();
		}
	}

	void StagingBufferWgpu::map()
	{
		auto ready = [](WGPUBufferMapAsyncStatus status, void* userdata)
		{
			StagingBufferWgpu* staging = static_cast<StagingBufferWgpu*>(userdata);
			BX_WARN(status == WGPUBufferMapAsyncStatus_Success, "Failed mapping staging buffer (size %d) for writing with error %d", staging->m_size, status);
			if (status == WGPUBufferMapAsyncStatus_Success)
			{
				void* data = staging->m_buffer.GetMappedRange();
				staging->mapped(data);
			}
		};

		m_buffer.MapAsync(wgpu::MapMode::Write, 0, m_size, ready, this);
	}

	void StagingBufferWgpu::unmap()
	{
		m_data = NULL;
		m_buffer.Unmap();
	}

	void StagingBufferWgpu::destroy()
	{
		m_buffer = NULL;
	}

	void StagingBufferWgpu::mapped(void* _data)
	{
		m_data = _data;
	}

	void ScratchBufferWgpu::create(uint32_t _size)
	{
		m_offset = 0;
		m_size = _size;

		wgpu::BufferDescriptor desc;
		desc.size = BGFX_CONFIG_MAX_DRAW_CALLS * 128;
		desc.usage = wgpu::BufferUsage::CopyDst | wgpu::BufferUsage::Uniform;

		m_buffer = s_renderWgpu->m_device.CreateBuffer(&desc);
	}

	void ScratchBufferWgpu::destroy()
	{
	}

	void ScratchBufferWgpu::begin()
	{
		for (uint8_t ii = 0; ii < WEBGPU_NUM_UNIFORM_BUFFERS; ++ii)
		{
			if (NULL != s_renderWgpu->m_uniformBuffers[ii].m_data)
			{
				m_staging = &s_renderWgpu->m_uniformBuffers[ii];
				break;
			}
		}

		BX_ASSERT(NULL != m_staging, "No available mapped uniform buffer");
	}

	uint32_t ScratchBufferWgpu::write(void* data, uint64_t _size, uint64_t _offset)
	{
		BX_ASSERT(nullptr != m_staging, "Cannot write uniforms outside of begin()/submit() calls");
		BX_ASSERT(m_size > m_offset + _offset, "Out-of-bounds scratch buffer write");
		uint32_t offset = m_offset;
		bx::memCopy((void*)((uint8_t*)m_staging->m_data + offset), data, _size);
		m_offset += _offset;
		return offset;
	}

	uint32_t ScratchBufferWgpu::write(void* data, uint64_t _size)
	{
		BX_ASSERT(nullptr != m_staging, "Cannot write uniforms outside of begin()/submit() calls");
		BX_ASSERT(m_size > m_offset + _size, "Out-of-bounds scratch buffer write");
		uint32_t offset = m_offset;
		bx::memCopy((void*)((uint8_t*)m_staging->m_data + offset), data, _size);
		m_offset += _size;
		return offset;
	}

	void ScratchBufferWgpu::submit()
	{
		m_staging->unmap();

		if (m_offset != 0)
		{
			wgpu::CommandEncoder& bce = s_renderWgpu->getStagingEncoder();
			bce.CopyBufferToBuffer(m_staging->m_buffer, 0, m_buffer, 0, m_offset);
		}
	}

	void ScratchBufferWgpu::release()
	{
		m_staging->map();
		m_staging = NULL;
		m_offset = 0;
	}

	void BindStateCacheWgpu::create() //(uint32_t _maxBindGroups)
	{
		//m_maxBindStates = 1024; // _maxBindStates;
		m_currentBindState = 0;
	}

	void BindStateCacheWgpu::destroy()
	{
		reset();
	}

	void BindStateCacheWgpu::reset()
	{
		for (size_t i = 0; i < m_currentBindState; ++i)
		{
			m_bindStates[i] = {};
		}

		m_currentBindState = 0;
	}

	wgpu::TextureView TextureWgpu::getTextureMipLevel(int _mip)
	{
		if (_mip >= 0
		&&  _mip <  m_numMips
		&&  m_ptr)
		{
			if (!m_ptrMips[_mip])
			{
				wgpu::TextureViewDescriptor desc;
				desc.baseMipLevel = _mip;
				desc.mipLevelCount = 1;

				desc.format = s_textureFormat[m_textureFormat].m_fmt;

				if (TextureCube == m_type)
				{
					//desc.dimension = MTLTextureType2DArray;
					desc.baseArrayLayer = 0;
					desc.arrayLayerCount = m_numLayers * 6;
				}
				else
				{
					desc.baseArrayLayer = 0;
					desc.arrayLayerCount = m_numLayers;
				}

				m_ptrMips[_mip] = m_ptr.CreateView(&desc);
			}

			return m_ptrMips[_mip];
		}

		return wgpu::TextureView();
	}

	void SwapChainWgpu::init(wgpu::Device _device, void* _nwh, uint32_t _width, uint32_t _height)
	{
		BX_UNUSED(_nwh);

		wgpu::SwapChainDescriptor desc;
		desc.usage = wgpu::TextureUsage::OutputAttachment;
		desc.width = _width;
		desc.height = _height;

#if !BX_PLATFORM_EMSCRIPTEN
		m_impl = createSwapChain(_device, _nwh);

		desc.presentMode = wgpu::PresentMode::Immediate;
		desc.format = wgpu::TextureFormat::RGBA8Unorm;
		desc.implementation = reinterpret_cast<uint64_t>(&m_impl);
		m_swapChain = _device.CreateSwapChain(nullptr, &desc);
#else
		wgpu::SurfaceDescriptorFromCanvasHTMLSelector canvasDesc{};
		canvasDesc.selector = "#canvas";

		wgpu::SurfaceDescriptor surfDesc{};
		surfDesc.nextInChain = &canvasDesc;
		wgpu::Surface surface = wgpu::Instance().CreateSurface(&surfDesc);

		desc.presentMode = wgpu::PresentMode::Fifo;
		desc.format = wgpu::TextureFormat::BGRA8Unorm;
		m_swapChain = _device.CreateSwapChain(surface, &desc);
#endif

		m_colorFormat = desc.format;
		m_depthFormat = wgpu::TextureFormat::Depth24PlusStencil8;
	}

	void SwapChainWgpu::resize(FrameBufferWgpu& _frameBuffer, uint32_t _width, uint32_t _height, uint32_t _flags)
	{
		BX_TRACE("SwapChainWgpu::resize");

		const int32_t sampleCount = s_msaa[(_flags&BGFX_RESET_MSAA_MASK)>>BGFX_RESET_MSAA_SHIFT];

		wgpu::TextureFormat format = (_flags & BGFX_RESET_SRGB_BACKBUFFER)
#ifdef DAWN_ENABLE_BACKEND_VULKAN
			? wgpu::TextureFormat::BGRA8UnormSrgb
			: wgpu::TextureFormat::BGRA8Unorm
#else
			? wgpu::TextureFormat::RGBA8UnormSrgb
			: wgpu::TextureFormat::RGBA8Unorm
#endif
			;

#if !BX_PLATFORM_EMSCRIPTEN
		m_swapChain.Configure(format, wgpu::TextureUsage::OutputAttachment, _width, _height);
#endif

		m_colorFormat = format;
		m_depthFormat = wgpu::TextureFormat::Depth24PlusStencil8;

		bx::HashMurmur2A murmur;
		murmur.begin();
		murmur.add(1);
		murmur.add((uint32_t)m_colorFormat);
		murmur.add((uint32_t)m_depthFormat);
		murmur.add((uint32_t)sampleCount);
		_frameBuffer.m_pixelFormatHash = murmur.end();

		wgpu::TextureDescriptor desc;

		desc.dimension = wgpu::TextureDimension::e2D;

		desc.size.width  = _width;
		desc.size.height = _height;
		desc.size.depthOrArrayLayers = 1;
		desc.mipLevelCount = 1;
		desc.sampleCount = sampleCount;
		desc.usage = wgpu::TextureUsage::OutputAttachment;

		if (m_backBufferDepth)
		{
			m_backBufferDepth.Destroy();
		}

		desc.format = wgpu::TextureFormat::Depth24PlusStencil8;

		m_backBufferDepth = s_renderWgpu->m_device.CreateTexture(&desc);

		if (sampleCount > 1)
		{
			if (m_backBufferColorMsaa)
			{
				m_backBufferColorMsaa.Destroy();
			}

			desc.format = m_colorFormat;
			desc.sampleCount = sampleCount;

			m_backBufferColorMsaa = s_renderWgpu->m_device.CreateTexture(&desc);
		}
	}

	void SwapChainWgpu::flip()
	{
		m_drawable = m_swapChain.GetCurrentTextureView();
	}

	wgpu::TextureView SwapChainWgpu::current()
	{
		if (!m_drawable)
			m_drawable = m_swapChain.GetCurrentTextureView();
		return m_drawable;
	}

	void FrameBufferWgpu::create(uint8_t _num, const Attachment* _attachment)
	{
		m_swapChain = NULL;
		m_denseIdx  = UINT16_MAX;
		m_num       = 0;
		m_width     = 0;
		m_height    = 0;

		for (uint32_t ii = 0; ii < _num; ++ii)
		{
			const Attachment& at = _attachment[ii];
			TextureHandle handle = at.handle;

			if (isValid(handle) )
			{
				const TextureWgpu& texture = s_renderWgpu->m_textures[handle.idx];

				if (0 == m_width)
				{
					m_width = texture.m_width;
					m_height = texture.m_height;
				}

				if (bimg::isDepth(bimg::TextureFormat::Enum(texture.m_textureFormat) ) )
				{
					m_depthHandle = handle;
					m_depthAttachment = at;
				}
				else
				{
					m_colorHandle[m_num] = handle;
					m_colorAttachment[m_num] = at;
					m_num++;
				}
			}
		}

		bx::HashMurmur2A murmur;
		murmur.begin();
		murmur.add(m_num);

		for (uint32_t ii = 0; ii < m_num; ++ii)
		{
			const TextureWgpu& texture = s_renderWgpu->m_textures[m_colorHandle[ii].idx];
			murmur.add(uint32_t(s_textureFormat[texture.m_textureFormat].m_fmt) );
		}

		if (!isValid(m_depthHandle) )
		{
			murmur.add(uint32_t(wgpu::TextureFormat::Undefined) );
		}
		else
		{
			const TextureWgpu& depthTexture = s_renderWgpu->m_textures[m_depthHandle.idx];
			murmur.add(uint32_t(s_textureFormat[depthTexture.m_textureFormat].m_fmt) );
		}

		murmur.add(1); // SampleCount

		m_pixelFormatHash = murmur.end();
	}

	bool FrameBufferWgpu::create(uint16_t _denseIdx, void* _nwh, uint32_t _width, uint32_t _height, TextureFormat::Enum _format, TextureFormat::Enum _depthFormat)
	{
		BX_UNUSED(_format, _depthFormat);
		m_swapChain = BX_NEW(g_allocator, SwapChainWgpu);
		m_num       = 0;
		m_width     = _width;
		m_height    = _height;
		m_nwh       = _nwh;
		m_denseIdx  = _denseIdx;

		m_swapChain->init(s_renderWgpu->m_device, _nwh, _width, _height);
		m_swapChain->resize(*this, _width, _height, 0);

		return m_swapChain->m_swapChain != NULL;
	}

	void FrameBufferWgpu::postReset()
	{
	}

	uint16_t FrameBufferWgpu::destroy()
	{
		if (NULL != m_swapChain)
		{
			BX_DELETE(g_allocator, m_swapChain);
			m_swapChain = NULL;
		}

		m_num = 0;
		m_nwh = NULL;
		m_depthHandle.idx = kInvalidHandle;

		uint16_t denseIdx = m_denseIdx;
		m_denseIdx = UINT16_MAX;

		return denseIdx;
	}

	void CommandQueueWgpu::init(wgpu::Queue _queue)
	{
		m_queue = _queue;
#if BGFX_CONFIG_MULTITHREADED
		//m_framesSemaphore.post(BGFX_CONFIG_MAX_FRAME_LATENCY);
#endif
	}

	void CommandQueueWgpu::shutdown()
	{
		finish(true);
	}

	void CommandQueueWgpu::beginRender()
	{
		m_renderEncoder = s_renderWgpu->m_device.CreateCommandEncoder();
	}

	void CommandQueueWgpu::beginStaging()
	{
		m_stagingEncoder = s_renderWgpu->m_device.CreateCommandEncoder();
	}

	inline void commandBufferFinishedCallback(void* _data)
	{
#if BGFX_CONFIG_MULTITHREADED
		CommandQueueWgpu* queue = (CommandQueueWgpu*)_data;
		if (queue)
		{
			//queue->m_framesSemaphore.post();
		}
#else
		BX_UNUSED(_data);
#endif
	}

	void CommandQueueWgpu::kick(bool _endFrame, bool _waitForFinish)
	{
		if (m_renderEncoder)
		{
			if (_endFrame)
			{
				m_releaseWriteIndex = (m_releaseWriteIndex + 1) % BGFX_CONFIG_MAX_FRAME_LATENCY;
				//m_encoder.addCompletedHandler(commandBufferFinishedCallback, this);
			}

			if (m_stagingEncoder)
			{
				wgpu::CommandBuffer commands = m_stagingEncoder.Finish();
				m_queue.Submit(1, &commands);
			}

			wgpu::CommandBuffer commands = m_renderEncoder.Finish();
			m_queue.Submit(1, &commands);

			if (_waitForFinish)
			{
#if BGFX_CONFIG_MULTITHREADED
				//m_framesSemaphore.post();
#endif
			}

			m_stagingEncoder = NULL;
			m_renderEncoder = NULL;
		}
	}

	void CommandQueueWgpu::finish(bool _finishAll)
	{
		if (_finishAll)
		{
			uint32_t count = m_renderEncoder
				? 2
				: 3
				;

			for (uint32_t ii = 0; ii < count; ++ii)
			{
				consume();
			}

#if BGFX_CONFIG_MULTITHREADED
			//m_framesSemaphore.post(count);
#endif
		}
		else
		{
			consume();
		}
	}

	void CommandQueueWgpu::release(wgpu::Buffer _buffer)
	{
		m_release[m_releaseWriteIndex].push_back(_buffer);
	}

	void CommandQueueWgpu::consume()
	{
#if BGFX_CONFIG_MULTITHREADED
		//m_framesSemaphore.wait();
#endif

		m_releaseReadIndex = (m_releaseReadIndex + 1) % BGFX_CONFIG_MAX_FRAME_LATENCY;

		for (wgpu::Buffer& buffer : m_release[m_releaseReadIndex])
		{
			buffer.Destroy();
		}

		m_release[m_releaseReadIndex].clear();
	}

	void TimerQueryWgpu::init()
	{
		m_frequency = bx::getHPFrequency();
	}

	void TimerQueryWgpu::shutdown()
	{
	}

	uint32_t TimerQueryWgpu::begin(uint32_t _resultIdx)
	{
		BX_UNUSED(_resultIdx);
		return 0;
	}

	void TimerQueryWgpu::end(uint32_t _idx)
	{
		BX_UNUSED(_idx);
	}

#if 0
	static void setTimestamp(void* _data)
	{
		*( (int64_t*)_data) = bx::getHPCounter();
	}
#endif

	void TimerQueryWgpu::addHandlers(wgpu::CommandBuffer& _commandBuffer)
	{
		BX_UNUSED(_commandBuffer);

		while (0 == m_control.reserve(1) )
		{
			m_control.consume(1);
		}

		//uint32_t offset = m_control.m_current;
		//_commandBuffer.addScheduledHandler(setTimestamp, &m_result[offset].m_begin);
		//_commandBuffer.addCompletedHandler(setTimestamp, &m_result[offset].m_end);
		m_control.commit(1);
	}

	bool TimerQueryWgpu::get()
	{
		if (0 != m_control.available() )
		{
			uint32_t offset = m_control.m_read;
			m_begin = m_result[offset].m_begin;
			m_end   = m_result[offset].m_end;
			m_elapsed = m_end - m_begin;

			m_control.consume(1);

			return true;
		}

		return false;
	}

	void RendererContextWgpu::submitBlit(BlitState& _bs, uint16_t _view)
	{
		if (!_bs.hasItem(_view) )
		{
			return;
		}

		endEncoding();

		wgpu::CommandEncoder& bce = getBlitCommandEncoder();

		while (_bs.hasItem(_view) )
		{
			const BlitItem& blit = _bs.advance();

			const TextureWgpu& src = m_textures[blit.m_src.idx];
			const TextureWgpu& dst = m_textures[blit.m_dst.idx];

			bool readBack = !!(dst.m_flags & BGFX_TEXTURE_READ_BACK);

			wgpu::ImageCopyTexture srcView;
			srcView.texture = src.m_ptr;
			srcView.origin = { blit.m_srcX, blit.m_srcY, blit.m_srcZ };
			srcView.mipLevel = blit.m_srcMip;

			wgpu::ImageCopyTexture dstView;
			dstView.texture = dst.m_ptr;
			dstView.origin = { blit.m_dstX, blit.m_dstY, blit.m_dstZ };
			dstView.mipLevel = blit.m_dstMip;

			if (blit.m_depth == 0)
			{
				wgpu::Extent3D copyExtent = { blit.m_width, blit.m_height, 1 };
				bce.CopyTextureToTexture(&srcView, &dstView, &copyExtent);
			}
			else
			{
				wgpu::Extent3D copyExtent = { blit.m_width, blit.m_height, blit.m_depth };
				bce.CopyTextureToTexture(&srcView, &dstView, &copyExtent);
			}

			if (readBack)
			{
				//bce..synchronizeTexture(dst.m_ptr, 0, blit.m_dstMip);
			}
		}

		//if (bce)
		//{
		//	bce.endEncoding();
		//	bce = 0;
		//}
	}

	void RendererContextWgpu::submit(Frame* _render, ClearQuad& _clearQuad, TextVideoMemBlitter& _textVideoMemBlitter)
	{
		if(_render->m_capture)
		{
			renderDocTriggerCapture();
		}

		m_cmd.finish(false);

		if (!m_cmd.m_renderEncoder)
		{
			m_cmd.beginRender();
		}

		BGFX_WEBGPU_PROFILER_BEGIN_LITERAL("rendererSubmit", kColorFrame);

		int64_t timeBegin = bx::getHPCounter();
		int64_t captureElapsed = 0;

		//m_gpuTimer.addHandlers(m_encoder);

		updateResolution(_render->m_resolution);

		m_frameIndex = 0; // (m_frameIndex + 1) % BGFX_CONFIG_MAX_FRAME_LATENCY;

		ScratchBufferWgpu& scratchBuffer = m_scratchBuffers[m_frameIndex];
		scratchBuffer.begin();

		BindStateCacheWgpu& bindStates = m_bindStateCache[m_frameIndex];
		bindStates.reset();

		if (0 < _render->m_iboffset)
		{
			BGFX_PROFILER_SCOPE("bgfx/Update transient index buffer", kColorResource);
			TransientIndexBuffer* ib = _render->m_transientIb;
			m_indexBuffers[ib->handle.idx].update(0, bx::strideAlign(_render->m_iboffset,4), ib->data, true);
		}

		if (0 < _render->m_vboffset)
		{
			BGFX_PROFILER_SCOPE("bgfx/Update transient vertex buffer", kColorResource);
			TransientVertexBuffer* vb = _render->m_transientVb;
			m_vertexBuffers[vb->handle.idx].update(0, bx::strideAlign(_render->m_vboffset,4), vb->data, true);
		}

		_render->sort();

		RenderDraw currentState;
		currentState.clear();
		currentState.m_stateFlags = BGFX_STATE_NONE;
		currentState.m_stencil    = packStencil(BGFX_STENCIL_NONE, BGFX_STENCIL_NONE);

		RenderBind currentBind;
		currentBind.clear();

		static ViewState viewState;
		viewState.reset(_render);
		uint32_t blendFactor = 0;

		//bool wireframe = !!(_render->m_debug&BGFX_DEBUG_WIREFRAME);

		ProgramHandle currentProgram = BGFX_INVALID_HANDLE;
		uint32_t currentBindHash = 0;
		uint32_t currentBindLayoutHash = 0;
		BindStateWgpu* previousBindState = NULL;
		SortKey key;
		uint16_t view = UINT16_MAX;
		FrameBufferHandle fbh = { BGFX_CONFIG_MAX_FRAME_BUFFERS };

		BlitState bs(_render);

		const uint64_t primType = 0;
		uint8_t primIndex = uint8_t(primType >> BGFX_STATE_PT_SHIFT);
		PrimInfo prim = s_primInfo[primIndex];
		const uint32_t maxComputeBindings = g_caps.limits.maxComputeBindings;

		// TODO store this
		static wgpu::RenderPassEncoder rce;

		PipelineStateWgpu* currentPso = NULL;

		bool wasCompute     = false;
		bool viewHasScissor = false;
		Rect viewScissorRect;
		viewScissorRect.clear();

		uint32_t statsNumPrimsSubmitted[BX_COUNTOF(s_primInfo)] = {};
		uint32_t statsNumPrimsRendered[BX_COUNTOF(s_primInfo)]  = {};
		uint32_t statsNumInstances[BX_COUNTOF(s_primInfo)]      = {};
		uint32_t statsNumDrawIndirect[BX_COUNTOF(s_primInfo)]   = {};
		uint32_t statsNumIndices = 0;
		uint32_t statsKeyType[2] = {};

		Profiler<TimerQueryWgpu> profiler(
			  _render
			, m_gpuTimer
			, s_viewName
			);

		if (0 == (_render->m_debug & BGFX_DEBUG_IFH))
		{
			viewState.m_rect = _render->m_view[0].m_rect;
			int32_t numItems = _render->m_numRenderItems;

			for (int32_t item = 0; item < numItems;)
			{
				const uint64_t encodedKey = _render->m_sortKeys[item];
				const bool isCompute = key.decode(encodedKey, _render->m_viewRemap);
				statsKeyType[isCompute]++;

				const bool viewChanged = 0
					|| key.m_view != view
					|| item == numItems
					;

				const uint32_t itemIdx = _render->m_sortValues[item];
				const RenderItem& renderItem = _render->m_renderItem[itemIdx];
				const RenderBind& renderBind = _render->m_renderItemBind[itemIdx];
				++item;

				if (viewChanged
					|| (!isCompute && wasCompute))
				{
					view = key.m_view;
					currentProgram = BGFX_INVALID_HANDLE;

					if (item > 1)
					{
						profiler.end();
					}

					BGFX_WEBGPU_PROFILER_END();
					setViewType(view, "  ");
					BGFX_WEBGPU_PROFILER_BEGIN(view, kColorView);

					profiler.begin(view);

					viewState.m_rect = _render->m_view[view].m_rect;

					submitBlit(bs, view);

					if (!isCompute)
					{
						const Rect& scissorRect = _render->m_view[view].m_scissor;
						viewHasScissor = !scissorRect.isZero();
						viewScissorRect = viewHasScissor ? scissorRect : viewState.m_rect;
						Clear& clr = _render->m_view[view].m_clear;

						Rect viewRect = viewState.m_rect;
						bool clearWithRenderPass = false;

						if (!m_renderEncoder
							|| fbh.idx != _render->m_view[view].m_fbh.idx)
						{
							endEncoding();

							fbh = _render->m_view[view].m_fbh;

							uint32_t width = m_resolution.width;
							uint32_t height = m_resolution.height;

							if (isValid(fbh))
							{
								FrameBufferWgpu& frameBuffer = m_frameBuffers[fbh.idx];
								width = frameBuffer.m_width;
								height = frameBuffer.m_height;
							}

							clearWithRenderPass = true
								&& 0 == viewRect.m_x
								&& 0 == viewRect.m_y
								&& width == viewRect.m_width
								&& height == viewRect.m_height
								;

							rce = renderPass(_render, fbh, clearWithRenderPass, clr, s_viewName[view]);
						}
						else if (BX_ENABLED(BGFX_CONFIG_DEBUG_ANNOTATION))
						{
							rce.PopDebugGroup();
						}

						if (BX_ENABLED(BGFX_CONFIG_DEBUG_ANNOTATION))
						{
							rce.PushDebugGroup(s_viewName[view]);
						}

						//rce.setTriangleFillMode(wireframe ? MTLTriangleFillModeLines : MTLTriangleFillModeFill);

						const Rect& rect = viewState.m_rect;
						rce.SetViewport(rect.m_x, rect.m_y, rect.m_width, rect.m_height, 0.0f, 1.0f);
						rce.SetScissorRect(rect.m_x, rect.m_y, rect.m_width, rect.m_height);


						if (BGFX_CLEAR_NONE != (clr.m_flags & BGFX_CLEAR_MASK)
						&&  !clearWithRenderPass)
						{
							clearQuad(_clearQuad, viewState.m_rect, clr, _render->m_colorPalette);
						}
					}
				}

				if (isCompute)
				{
					if (!wasCompute)
					{
						wasCompute = true;

						endEncoding();
						rce = NULL;

						setViewType(view, "C");
						BGFX_WEBGPU_PROFILER_END();
						BGFX_WEBGPU_PROFILER_BEGIN(view, kColorCompute);

						m_computeEncoder = m_cmd.m_renderEncoder.BeginComputePass();
					}
					else if (viewChanged)
					{
						if (BX_ENABLED(BGFX_CONFIG_DEBUG_ANNOTATION))
						{
							m_computeEncoder.PopDebugGroup();
						}

						endEncoding();
						m_computeEncoder = m_cmd.m_renderEncoder.BeginComputePass();
					}

					if (viewChanged)
					{
						if (BX_ENABLED(BGFX_CONFIG_DEBUG_ANNOTATION))
						{
							s_viewName[view][3] = L'C';
							m_computeEncoder.PushDebugGroup(s_viewName[view]);
							s_viewName[view][3] = L' ';
						}
					}

					const RenderCompute& compute = renderItem.compute;

					bool programChanged = false;
					bool constantsChanged = compute.m_uniformBegin < compute.m_uniformEnd;
					rendererUpdateUniforms(this, _render->m_uniformBuffer[compute.m_uniformIdx], compute.m_uniformBegin, compute.m_uniformEnd);

					if (key.m_program.idx != currentProgram.idx)
					{
						currentProgram = key.m_program;

						currentPso = getComputePipelineState(currentProgram);

						if (NULL == currentPso)
						{
							currentProgram = BGFX_INVALID_HANDLE;
							continue;
						}

						m_computeEncoder.SetPipeline(currentPso->m_cps);
						programChanged =
							constantsChanged = true;
					}

					if (!isValid(currentProgram)
					  || NULL == currentPso)
						BX_WARN(false, "Invalid program / No PSO");

					const ProgramWgpu& program = m_program[currentProgram.idx];

					if (constantsChanged)
					{
						UniformBuffer* vcb = program.m_vsh->m_constantBuffer;
						if (NULL != vcb)
						{
							commit(*vcb);
						}
					}

					viewState.setPredefined<4>(this, view, program, _render, compute);

					uint32_t numOffset = 0;
					uint32_t offsets[2] = { 0, 0 };
					if (program.m_vsh->m_size > 0)
					{
						offsets[numOffset++] = scratchBuffer.write(m_vsScratch, program.m_vsh->m_gpuSize);
					}

					BindStateWgpu& bindState = allocAndFillBindState(program, bindStates, scratchBuffer, renderBind);

					bindProgram(m_computeEncoder, program, bindState, numOffset, offsets);

					if (isValid(compute.m_indirectBuffer))
					{
						const VertexBufferWgpu& vb = m_vertexBuffers[compute.m_indirectBuffer.idx];

						uint32_t numDrawIndirect = UINT16_MAX == compute.m_numIndirect
						? vb.m_size/BGFX_CONFIG_DRAW_INDIRECT_STRIDE
						: compute.m_numIndirect
						;

						uint32_t args = compute.m_startIndirect * BGFX_CONFIG_DRAW_INDIRECT_STRIDE;
						for (uint32_t ii = 0; ii < numDrawIndirect; ++ii)
						{
							m_computeEncoder.DispatchIndirect(
								  vb.m_ptr
								, args
								);
							args += BGFX_CONFIG_DRAW_INDIRECT_STRIDE;
						}
					}
					else
					{
						m_computeEncoder.Dispatch(compute.m_numX, compute.m_numY, compute.m_numZ);
					}

					continue;
				}


				bool resetState = viewChanged || wasCompute;

				if (wasCompute)
				{
					wasCompute = false;
					currentProgram = BGFX_INVALID_HANDLE;

					setViewType(view, " ");
					BGFX_WEBGPU_PROFILER_END();
					BGFX_WEBGPU_PROFILER_BEGIN(view, kColorDraw);
				}

				const RenderDraw& draw = renderItem.draw;

				// TODO (hugoam)
				//const bool depthWrite = !!(BGFX_STATE_WRITE_Z & draw.m_stateFlags);
				const uint64_t newFlags = draw.m_stateFlags;
				uint64_t changedFlags = currentState.m_stateFlags ^ draw.m_stateFlags;
				currentState.m_stateFlags = newFlags;

				const uint64_t newStencil = draw.m_stencil;
				uint64_t changedStencil = (currentState.m_stencil ^ draw.m_stencil) & BGFX_STENCIL_FUNC_REF_MASK;
				currentState.m_stencil = newStencil;

				if (resetState)
				{
					wasCompute = false;

					currentState.clear();
					currentState.m_scissor = !draw.m_scissor;
					changedFlags = BGFX_STATE_MASK;
					changedStencil = packStencil(BGFX_STENCIL_MASK, BGFX_STENCIL_MASK);
					currentState.m_stateFlags = newFlags;
					currentState.m_stencil = newStencil;

					currentBind.clear();

					currentProgram = BGFX_INVALID_HANDLE;
					const uint64_t pt = newFlags & BGFX_STATE_PT_MASK;
					primIndex = uint8_t(pt >> BGFX_STATE_PT_SHIFT);
				}

				if (prim.m_type != s_primInfo[primIndex].m_type)
				{
					prim = s_primInfo[primIndex];
				}

				uint16_t scissor = draw.m_scissor;
				if (currentState.m_scissor != scissor)
				{
					currentState.m_scissor = scissor;

					if (UINT16_MAX == scissor)
					{
						if (viewHasScissor)
						{
							const auto& r = viewScissorRect;
							rce.SetScissorRect(r.m_x, r.m_y, r.m_width, r.m_height);
						}
						else
						{   // can't disable: set to view rect
							const auto& r = viewState.m_rect;
							rce.SetScissorRect(r.m_x, r.m_y, r.m_width, r.m_height);
						}
					}
					else
					{
						Rect scissorRect;
						scissorRect.setIntersect(viewScissorRect, _render->m_frameCache.m_rectCache.m_cache[scissor]);

						const auto& r = scissorRect;
						if (r.m_width == 0 || r.m_height == 0)
						{
							continue;
						}
						rce.SetScissorRect(r.m_x, r.m_y, r.m_width, r.m_height);
					}

				}

				if (0 != changedStencil)
				{
					const uint32_t fstencil = unpackStencil(0, draw.m_stencil);
					const uint32_t ref = (fstencil & BGFX_STENCIL_FUNC_REF_MASK) >> BGFX_STENCIL_FUNC_REF_SHIFT;
					rce.SetStencilReference(ref);
				}

				if ((0 | BGFX_STATE_PT_MASK) & changedFlags)
				{
					const uint64_t pt = newFlags & BGFX_STATE_PT_MASK;
					primIndex = uint8_t(pt >> BGFX_STATE_PT_SHIFT);
					if (prim.m_type != s_primInfo[primIndex].m_type)
					{
						prim = s_primInfo[primIndex];
					}
				}

				if (blendFactor != draw.m_rgba
					&& !(newFlags & BGFX_STATE_BLEND_INDEPENDENT))
				{
					const uint32_t rgba = draw.m_rgba;
					float rr = ((rgba >> 24)) / 255.0f;
					float gg = ((rgba >> 16) & 0xff) / 255.0f;
					float bb = ((rgba >> 8) & 0xff) / 255.0f;
					float aa = ((rgba) & 0xff) / 255.0f;
					wgpu::Color color = { rr, gg, bb, aa };
					rce.SetBlendColor(&color);

					blendFactor = draw.m_rgba;
				}

				bool programChanged = false;
				bool constantsChanged = draw.m_uniformBegin < draw.m_uniformEnd;
				rendererUpdateUniforms(this, _render->m_uniformBuffer[draw.m_uniformIdx], draw.m_uniformBegin, draw.m_uniformEnd);

				bool vertexStreamChanged = hasVertexStreamChanged(currentState, draw);

				if (key.m_program.idx != currentProgram.idx
					|| vertexStreamChanged
					|| (0
						| BGFX_STATE_BLEND_MASK
						| BGFX_STATE_BLEND_EQUATION_MASK
						| BGFX_STATE_WRITE_RGB
						| BGFX_STATE_WRITE_A
						| BGFX_STATE_BLEND_INDEPENDENT
						| BGFX_STATE_MSAA
						| BGFX_STATE_BLEND_ALPHA_TO_COVERAGE
						) & changedFlags
					|| ((blendFactor != draw.m_rgba) && !!(newFlags & BGFX_STATE_BLEND_INDEPENDENT)))
				{
					currentProgram = key.m_program;

					currentState.m_streamMask = draw.m_streamMask;
					currentState.m_instanceDataBuffer.idx = draw.m_instanceDataBuffer.idx;
					currentState.m_instanceDataOffset = draw.m_instanceDataOffset;
					currentState.m_instanceDataStride = draw.m_instanceDataStride;

					const VertexLayout* decls[BGFX_CONFIG_MAX_VERTEX_STREAMS];

					uint32_t numVertices = draw.m_numVertices;
					uint8_t  numStreams = 0;
					for (uint32_t idx = 0, streamMask = draw.m_streamMask
						; 0 != streamMask
						; streamMask >>= 1, idx += 1, ++numStreams
						)
					{
						const uint32_t ntz = bx::uint32_cnttz(streamMask);
						streamMask >>= ntz;
						idx += ntz;

						currentState.m_stream[idx].m_layoutHandle = draw.m_stream[idx].m_layoutHandle;
						currentState.m_stream[idx].m_handle = draw.m_stream[idx].m_handle;
						currentState.m_stream[idx].m_startVertex = draw.m_stream[idx].m_startVertex;

						const uint16_t handle = draw.m_stream[idx].m_handle.idx;
						const VertexBufferWgpu& vb = m_vertexBuffers[handle];
						const uint16_t decl = isValid(draw.m_stream[idx].m_layoutHandle)
							? draw.m_stream[idx].m_layoutHandle.idx
							: vb.m_layoutHandle.idx;
						const VertexLayout& vertexDecl = m_vertexDecls[decl];
						const uint32_t stride = vertexDecl.m_stride;

						decls[numStreams] = &vertexDecl;

						numVertices = bx::uint32_min(UINT32_MAX == draw.m_numVertices
							? vb.m_size / stride
							: draw.m_numVertices
							, numVertices
						);
						const uint32_t offset = draw.m_stream[idx].m_startVertex * stride;

						rce.SetVertexBuffer(idx, vb.m_ptr, offset);
					}

					if (!isValid(currentProgram))
					{
						continue;
					}
					else
					{
						currentPso = NULL;

						if (0 < numStreams)
						{
							currentPso = getPipelineState(
								newFlags
								, newStencil
								, draw.m_rgba
								, fbh
								, numStreams
								, decls
								, draw.isIndex16()
								, currentProgram
								, uint8_t(draw.m_instanceDataStride / 16)
							);
						}

						if (NULL == currentPso)
						{
							currentProgram = BGFX_INVALID_HANDLE;
							continue;
						}

						rce.SetPipeline(currentPso->m_rps);
					}

					if (isValid(draw.m_instanceDataBuffer))
					{
						const VertexBufferWgpu& inst = m_vertexBuffers[draw.m_instanceDataBuffer.idx];
						rce.SetVertexBuffer(numStreams/*+1*/, inst.m_ptr, draw.m_instanceDataOffset);
					}

					programChanged =
						constantsChanged = true;
				}

				if (isValid(currentProgram))
				{
					const ProgramWgpu& program = m_program[currentProgram.idx];

					if (constantsChanged)
					{
						UniformBuffer* vcb = program.m_vsh->m_constantBuffer;
						if (NULL != vcb)
						{
							commit(*vcb);
						}
					}

					if (constantsChanged)
					{
						UniformBuffer* fcb = program.m_fsh->m_constantBuffer;
						if (NULL != fcb)
						{
							commit(*fcb);
						}
					}

					viewState.setPredefined<4>(this, view, program, _render, draw);

					bool hasPredefined = 0 < program.m_numPredefined;

					uint32_t numOffset = 0;
					uint32_t offsets[2] = { 0, 0 };
					if (constantsChanged
					||  hasPredefined)
					{
						//viewState.setPredefined<4>(this, view, program, _render, draw, programChanged || viewChanged);

						const uint32_t vsize = program.m_vsh->m_gpuSize;
						const uint32_t fsize = (NULL != program.m_fsh ? program.m_fsh->m_gpuSize : 0);

						if (program.m_vsh->m_size > 0)
						{
							offsets[numOffset++] = scratchBuffer.write(m_vsScratch, vsize);
						}
						if (fsize > 0)
						{
							offsets[numOffset++] = scratchBuffer.write(m_fsScratch, fsize);
						}
					}

					uint32_t bindHash = bx::hash<bx::HashMurmur2A>(renderBind.m_bind, sizeof(renderBind.m_bind));
					if (currentBindHash != bindHash
					||  currentBindLayoutHash != program.m_bindGroupLayoutHash)
					{
						currentBindHash = bindHash;
						currentBindLayoutHash = program.m_bindGroupLayoutHash;
						previousBindState = &bindStates.m_bindStates[bindStates.m_currentBindState];

						allocAndFillBindState(program, bindStates, scratchBuffer, renderBind);
					}

					BindStateWgpu& bindState = bindStates.m_bindStates[bindStates.m_currentBindState-1];

					bindProgram(rce, program, bindState, numOffset, offsets);
				}

				if (0 != currentState.m_streamMask)
				{
					uint32_t numVertices = draw.m_numVertices;
					if (UINT32_MAX == numVertices)
					{
						const VertexBufferWgpu& vb = m_vertexBuffers[currentState.m_stream[0].m_handle.idx];
						uint16_t decl = !isValid(vb.m_layoutHandle) ? draw.m_stream[0].m_layoutHandle.idx : vb.m_layoutHandle.idx;
						const VertexLayout& vertexDecl = m_vertexDecls[decl];
						numVertices = vb.m_size/vertexDecl.m_stride;
					}

					uint32_t numIndices        = 0;
					uint32_t numPrimsSubmitted = 0;
					uint32_t numInstances      = 0;
					uint32_t numPrimsRendered  = 0;
					uint32_t numDrawIndirect   = 0;

					if (isValid(draw.m_indirectBuffer) )
					{
						const VertexBufferWgpu& vb = m_vertexBuffers[draw.m_indirectBuffer.idx];

						if (isValid(draw.m_indexBuffer) )
						{
							const IndexBufferWgpu& ib = m_indexBuffers[draw.m_indexBuffer.idx];

							numDrawIndirect = UINT16_MAX == draw.m_numIndirect
							? vb.m_size/BGFX_CONFIG_DRAW_INDIRECT_STRIDE
							: draw.m_numIndirect
							;

							for (uint32_t ii = 0; ii < numDrawIndirect; ++ii)
							{
								rce.SetIndexBuffer(ib.m_ptr, ib.m_format, 0);
								rce.DrawIndexedIndirect(vb.m_ptr, (draw.m_startIndirect + ii)* BGFX_CONFIG_DRAW_INDIRECT_STRIDE);
							}
						}
						else
						{
							numDrawIndirect = UINT16_MAX == draw.m_numIndirect
							? vb.m_size/BGFX_CONFIG_DRAW_INDIRECT_STRIDE
							: draw.m_numIndirect
							;
							for (uint32_t ii = 0; ii < numDrawIndirect; ++ii)
							{
								rce.DrawIndirect(vb.m_ptr, (draw.m_startIndirect + ii)* BGFX_CONFIG_DRAW_INDIRECT_STRIDE);
							}
						}
					}
					else
					{
						if (isValid(draw.m_indexBuffer) )
						{
							const IndexBufferWgpu& ib = m_indexBuffers[draw.m_indexBuffer.idx];
							const uint32_t indexSize  = draw.isIndex16() ? 2 : 4;

							if (UINT32_MAX == draw.m_numIndices)
							{
								numIndices        = ib.m_size/indexSize;
								numPrimsSubmitted = numIndices/prim.m_div - prim.m_sub;
								numInstances      = draw.m_numInstances;
								numPrimsRendered  = numPrimsSubmitted*draw.m_numInstances;

								rce.SetIndexBuffer(ib.m_ptr, ib.m_format, 0);
								rce.DrawIndexed(numIndices, draw.m_numInstances, 0, 0, 0);
							}
							else if (prim.m_min <= draw.m_numIndices)
							{
								numIndices        = draw.m_numIndices;
								numPrimsSubmitted = numIndices/prim.m_div - prim.m_sub;
								numInstances      = draw.m_numInstances;
								numPrimsRendered  = numPrimsSubmitted*draw.m_numInstances;

								rce.SetIndexBuffer(ib.m_ptr, ib.m_format, 0);
								rce.DrawIndexed(numIndices, numInstances, draw.m_startIndex, 0, 0);
							}
						}
						else
						{
							numPrimsSubmitted = numVertices/prim.m_div - prim.m_sub;
							numInstances      = draw.m_numInstances;
							numPrimsRendered  = numPrimsSubmitted*draw.m_numInstances;

							rce.Draw(numVertices, draw.m_numInstances, 0, 0);
						}
					}

					statsNumPrimsSubmitted[primIndex] += numPrimsSubmitted;
					statsNumPrimsRendered[primIndex]  += numPrimsRendered;
					statsNumInstances[primIndex]      += numInstances;
					statsNumDrawIndirect[primIndex]   += numDrawIndirect;
					statsNumIndices                   += numIndices;
				}
			}

			if (wasCompute)
			{
				invalidateCompute();

				setViewType(view, "C");
				BGFX_WEBGPU_PROFILER_END();
				BGFX_WEBGPU_PROFILER_BEGIN(view, kColorCompute);
			}

			submitBlit(bs, BGFX_CONFIG_MAX_VIEWS);

			if (0 < _render->m_numRenderItems)
			{
				captureElapsed = -bx::getHPCounter();
				capture();
				rce = m_renderEncoder;
				captureElapsed += bx::getHPCounter();

				profiler.end();
			}
		}

		if (BX_ENABLED(BGFX_CONFIG_DEBUG_ANNOTATION) )
		{
			if (0 < _render->m_numRenderItems)
			{
				rce.PopDebugGroup();
			}
		}

		BGFX_WEBGPU_PROFILER_END();

		int64_t timeEnd = bx::getHPCounter();
		int64_t frameTime = timeEnd - timeBegin;

		static int64_t min = frameTime;
		static int64_t max = frameTime;
		min = bx::min<int64_t>(min, frameTime);
		max = bx::max<int64_t>(max, frameTime);

		static uint32_t maxGpuLatency = 0;
		static double   maxGpuElapsed = 0.0f;
		double elapsedGpuMs = 0.0;

		do
		{
			double toGpuMs = 1000.0 / double(m_gpuTimer.m_frequency);
			elapsedGpuMs   = m_gpuTimer.m_elapsed * toGpuMs;
			maxGpuElapsed  = elapsedGpuMs > maxGpuElapsed ? elapsedGpuMs : maxGpuElapsed;
		}
		while (m_gpuTimer.get() );

		maxGpuLatency = bx::uint32_imax(maxGpuLatency, m_gpuTimer.m_control.available()-1);

		const int64_t timerFreq = bx::getHPFrequency();

		Stats& perfStats = _render->m_perfStats;
		perfStats.cpuTimeBegin  = timeBegin;
		perfStats.cpuTimeEnd    = timeEnd;
		perfStats.cpuTimerFreq  = timerFreq;
		perfStats.gpuTimeBegin  = m_gpuTimer.m_begin;
		perfStats.gpuTimeEnd    = m_gpuTimer.m_end;
		perfStats.gpuTimerFreq  = m_gpuTimer.m_frequency;
		perfStats.numDraw       = statsKeyType[0];
		perfStats.numCompute    = statsKeyType[1];
		perfStats.numBlit       = _render->m_numBlitItems;
		perfStats.maxGpuLatency = maxGpuLatency;
		bx::memCopy(perfStats.numPrims, statsNumPrimsRendered, sizeof(perfStats.numPrims) );
		perfStats.gpuMemoryMax  = -INT64_MAX;
		perfStats.gpuMemoryUsed = -INT64_MAX;

		//rce.setTriangleFillMode(MTLTriangleFillModeFill);
		if (_render->m_debug & (BGFX_DEBUG_IFH|BGFX_DEBUG_STATS) )
		{
			rce = renderPass(_render, BGFX_INVALID_HANDLE, false, Clear());

			if (BX_ENABLED(BGFX_CONFIG_DEBUG_ANNOTATION))
			{
				rce.PushDebugGroup("debugstats");
			}

			TextVideoMem& tvm = m_textVideoMem;

			static int64_t next = timeEnd;

			if (timeEnd >= next)
			{
				next = timeEnd + timerFreq;

				double freq = double(timerFreq);
				double toMs = 1000.0/freq;

				tvm.clear();
				uint16_t pos = 0;
				tvm.printf(0, pos++, BGFX_CONFIG_DEBUG ? 0x8c : 0x8f
					, " %s / " BX_COMPILER_NAME
					  " / " BX_CPU_NAME
					  " / " BX_ARCH_NAME
					  " / " BX_PLATFORM_NAME
					  " / Version 1.%d.%d (commit: " BGFX_REV_SHA1 ")"
					, getRendererName()
					, BGFX_API_VERSION
					, BGFX_REV_NUMBER
					);

				pos = 10;
				tvm.printf(10, pos++, 0x8b, "        Frame: %7.3f, % 7.3f \x1f, % 7.3f \x1e [ms] / % 6.2f FPS "
					, double(frameTime)*toMs
					, double(min)*toMs
					, double(max)*toMs
					, freq/frameTime
					);

				const uint32_t msaa = (m_resolution.reset&BGFX_RESET_MSAA_MASK)>>BGFX_RESET_MSAA_SHIFT;
				tvm.printf(10, pos++, 0x8b, "  Reset flags: [%c] vsync, [%c] MSAAx%d, [%c] MaxAnisotropy "
					, !!(m_resolution.reset&BGFX_RESET_VSYNC) ? '\xfe' : ' '
					, 0 != msaa ? '\xfe' : ' '
					, 1<<msaa
					, !!(m_resolution.reset&BGFX_RESET_MAXANISOTROPY) ? '\xfe' : ' '
					);

				double elapsedCpuMs = double(frameTime)*toMs;
				tvm.printf(10, pos++, 0x8b, "    Submitted: %4d (draw %4d, compute %4d) / CPU %3.4f [ms] %c GPU %3.4f [ms] (latency %d)"
					, _render->m_numRenderItems
					, statsKeyType[0]
					, statsKeyType[1]
					, elapsedCpuMs
					, elapsedCpuMs > maxGpuElapsed ? '>' : '<'
					, maxGpuElapsed
					, maxGpuLatency
					);
				maxGpuLatency = 0;
				maxGpuElapsed = 0.0;

				for (uint32_t ii = 0; ii < Topology::Count; ++ii)
				{
					tvm.printf(10, pos++, 0x8b, "   %10s: %7d (#inst: %5d), submitted: %7d"
						, getName(Topology::Enum(ii) )
						, statsNumPrimsRendered[ii]
						, statsNumInstances[ii]
						, statsNumPrimsSubmitted[ii]
						);
				}

				tvm.printf(10, pos++, 0x8b, "      Indices: %7d ", statsNumIndices);
//				tvm.printf(10, pos++, 0x8b, " Uniform size: %7d, Max: %7d ", _render->m_uniformEnd, _render->m_uniformMax);
				tvm.printf(10, pos++, 0x8b, "     DVB size: %7d ", _render->m_vboffset);
				tvm.printf(10, pos++, 0x8b, "     DIB size: %7d ", _render->m_iboffset);

				pos++;
				double captureMs = double(captureElapsed)*toMs;
				tvm.printf(10, pos++, 0x8b, "     Capture: %3.4f [ms]", captureMs);

				uint8_t attr[2] = { 0x8c, 0x8a };
				uint8_t attrIndex = _render->m_waitSubmit < _render->m_waitRender;

				tvm.printf(10, pos++, attr[attrIndex    &1], " Submit wait: %3.4f [ms]", _render->m_waitSubmit*toMs);
				tvm.printf(10, pos++, attr[(attrIndex+1)&1], " Render wait: %3.4f [ms]", _render->m_waitRender*toMs);

				min = frameTime;
				max = frameTime;
			}

			blit(this, _textVideoMemBlitter, tvm);
			rce = m_renderEncoder;

			if (BX_ENABLED(BGFX_CONFIG_DEBUG_ANNOTATION))
			{
				rce.PopDebugGroup();
			}
		}
		else if (_render->m_debug & BGFX_DEBUG_TEXT)
		{
			if (BX_ENABLED(BGFX_CONFIG_DEBUG_ANNOTATION))
			{
				rce.PushDebugGroup("debugtext");
			}

			blit(this, _textVideoMemBlitter, _render->m_textVideoMem);
			rce = m_renderEncoder;

			if (BX_ENABLED(BGFX_CONFIG_DEBUG_ANNOTATION))
			{
				rce.PopDebugGroup();
			}
		}

		endEncoding();

		scratchBuffer.submit();

		m_cmd.kick(true);

		scratchBuffer.release();

#if !BX_PLATFORM_EMSCRIPTEN
		for (uint32_t ii = 0, num = m_numWindows; ii < num; ++ii)
		{
			FrameBufferWgpu& frameBuffer = ii == 0 ? m_mainFrameBuffer : m_frameBuffers[m_windows[ii].idx];
			if (NULL != frameBuffer.m_swapChain
			&& frameBuffer.m_swapChain->m_drawable)
			{
				SwapChainWgpu& swapChain = *frameBuffer.m_swapChain;
				swapChain.m_swapChain.Present();
			}
		}
#endif
	}

} /* namespace webgpu */ } // namespace bgfx

#else

namespace bgfx { namespace webgpu
	{
		RendererContextI* rendererCreate(const Init& _init)
		{
			BX_UNUSED(_init);
			return NULL;
		}

		void rendererDestroy()
		{
		}
	} /* namespace webgpu */ } // namespace bgfx

#endif // BGFX_CONFIG_RENDERER_WEBGPU
