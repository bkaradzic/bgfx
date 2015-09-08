/*
 * Copyright 2011-2015 Attila Kocsis. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "bgfx_p.h"

#if BGFX_CONFIG_RENDERER_METAL

#include "renderer_mtl.h"
#include "renderer.h"
#include "bx/bx.h"

#if BX_PLATFORM_OSX
#	include <Cocoa/Cocoa.h>
#endif

#import <Foundation/Foundation.h>

#define UNIFORM_BUFFER_SIZE (1024*1024)

/*
Known issues / TODOs:
- 15-shadowmaps-simple (modified shaderc and example needs modification too, mtxCrop znew = z * 0.5 + 0.5 is not needed ) could be hacked in shader too
- 19-oit ( hacked shaderc to support MRT output)
- 21-deferred ( hacked shaderc to support MRT output and fs_deferred_light needed modification for metal (similar to BGFX_SHADER_LANGUAGE_HLSL )

07-callback, saveScreenshot should be implemented with one frame latency (using saveScreenshotBegin and End)

16-shadowmaps,  //problem with essl -> metal: SAMPLER2D(u_shadowMap0, 4);  sampler index is lost. Shadowmap is set to slot 4, but
 metal shader uses sampler/texture slot 0. this could require changes outside of renderer_mtl?
  Otherwise it works with hacking the slot.

24-nbody - cannot generate compute shaders for metal

20-nanonvg - TODO: remove sampler/texture hack

- caps

- optimization...

create binary shader representation

 13-stencil and 16-shadowmaps are very inefficient. every view stores/loads backbuffer data

 BGFX_RESET_FLIP_AFTER_RENDER on low level renderers should be true? (crashes even with BGFX_RESET_FLIP_AFTER_RENDER because there is
 one rendering frame before reset). Do I have absolutely need to send result to View at flip or can I do it in submit?

 */

namespace bgfx { namespace mtl
{
	static char s_viewName[BGFX_CONFIG_MAX_VIEWS][BGFX_CONFIG_MAX_VIEW_NAME];

	struct PrimInfo
	{
		MTLPrimitiveType m_type;
		uint32_t m_min;
		uint32_t m_div;
		uint32_t m_sub;
	};

	static const PrimInfo s_primInfo[] =
	{
		{ MTLPrimitiveTypeTriangle,      3, 3, 0 },
		{ MTLPrimitiveTypeTriangleStrip, 3, 1, 2 },
		{ MTLPrimitiveTypeLine,          2, 2, 0 },
		{ MTLPrimitiveTypeLineStrip,     2, 1, 1 },
		{ MTLPrimitiveTypePoint,         1, 1, 0 },
	};

	static const char* s_primName[] =
	{
		"TriList",
		"TriStrip",
		"Line",
		"LineStrip",
		"Point",
	};
	BX_STATIC_ASSERT(BX_COUNTOF(s_primInfo) == BX_COUNTOF(s_primName));

	static const char* s_attribName[] =
	{
		"a_position",
		"a_normal",
		"a_tangent",
		"a_bitangent",
		"a_color0",
		"a_color1",
		"a_indices",
		"a_weight",
		"a_texcoord0",
		"a_texcoord1",
		"a_texcoord2",
		"a_texcoord3",
		"a_texcoord4",
		"a_texcoord5",
		"a_texcoord6",
		"a_texcoord7",
	};
	BX_STATIC_ASSERT(Attrib::Count == BX_COUNTOF(s_attribName) );

	static const char* s_instanceDataName[] =
	{
		"i_data0",
		"i_data1",
		"i_data2",
		"i_data3",
		"i_data4",
	};
	BX_STATIC_ASSERT(BGFX_CONFIG_MAX_INSTANCE_DATA_COUNT == BX_COUNTOF(s_instanceDataName) );

	static const MTLVertexFormat s_attribType[][4][2] = //type, count, normalized
	{
		// Uint8
		{
			{ MTLVertexFormatUChar2, MTLVertexFormatUChar2Normalized },
			{ MTLVertexFormatUChar2, MTLVertexFormatUChar2Normalized },
			{ MTLVertexFormatUChar3, MTLVertexFormatUChar3Normalized },
			{ MTLVertexFormatUChar4, MTLVertexFormatUChar4Normalized }
		},

		//Uint10
		//TODO: normalized only
		{
			{ MTLVertexFormatInvalid, MTLVertexFormatUInt1010102Normalized },
			{ MTLVertexFormatInvalid, MTLVertexFormatUInt1010102Normalized },
			{ MTLVertexFormatInvalid, MTLVertexFormatUInt1010102Normalized },
			{ MTLVertexFormatInvalid, MTLVertexFormatUInt1010102Normalized }
		},

		//Int16
		{
			{ MTLVertexFormatShort2, MTLVertexFormatShort2Normalized },
			{ MTLVertexFormatShort2, MTLVertexFormatShort2Normalized },
			{ MTLVertexFormatShort3, MTLVertexFormatShort3Normalized },
			{ MTLVertexFormatShort4, MTLVertexFormatShort4Normalized }
		},

		//Half
		{
			{ MTLVertexFormatHalf2, MTLVertexFormatHalf2 },
			{ MTLVertexFormatHalf2, MTLVertexFormatHalf2 },
			{ MTLVertexFormatHalf3, MTLVertexFormatHalf2 },
			{ MTLVertexFormatHalf4, MTLVertexFormatHalf2 }
		},

		//Float
		{
			{ MTLVertexFormatFloat,  MTLVertexFormatFloat  },
			{ MTLVertexFormatFloat2, MTLVertexFormatFloat2 },
			{ MTLVertexFormatFloat3, MTLVertexFormatFloat3 },
			{ MTLVertexFormatFloat4, MTLVertexFormatFloat4 }
		},
	};
	BX_STATIC_ASSERT(AttribType::Count == BX_COUNTOF(s_attribType) );

	static const MTLCullMode s_cullMode[] =
	{
		MTLCullModeNone,
		MTLCullModeFront,
		MTLCullModeBack,
		MTLCullModeNone
	};

	static const MTLBlendFactor s_blendFactor[][2] =
	{
		{ (MTLBlendFactor)0,                      (MTLBlendFactor)0                      }, // ignored
		{ MTLBlendFactorZero,                     MTLBlendFactorZero                     }, // ZERO
		{ MTLBlendFactorOne,                      MTLBlendFactorOne                      }, // ONE
		{ MTLBlendFactorSourceColor,              MTLBlendFactorSourceAlpha              }, // SRC_COLOR
		{ MTLBlendFactorOneMinusSourceColor,      MTLBlendFactorOneMinusSourceAlpha      }, // INV_SRC_COLOR
		{ MTLBlendFactorSourceAlpha,              MTLBlendFactorSourceAlpha              }, // SRC_ALPHA
		{ MTLBlendFactorOneMinusSourceAlpha,      MTLBlendFactorOneMinusSourceAlpha      }, // INV_SRC_ALPHA
		{ MTLBlendFactorDestinationAlpha,         MTLBlendFactorDestinationAlpha         }, // DST_ALPHA
		{ MTLBlendFactorOneMinusDestinationAlpha, MTLBlendFactorOneMinusDestinationAlpha }, // INV_DST_ALPHA
		{ MTLBlendFactorDestinationColor,         MTLBlendFactorDestinationAlpha         }, // DST_COLOR
		{ MTLBlendFactorOneMinusDestinationColor, MTLBlendFactorOneMinusDestinationAlpha }, // INV_DST_COLOR
		{ MTLBlendFactorSourceAlphaSaturated,     MTLBlendFactorOne                      }, // SRC_ALPHA_SAT
		{ MTLBlendFactorBlendColor,               MTLBlendFactorBlendColor               }, // FACTOR
		{ MTLBlendFactorOneMinusBlendColor,       MTLBlendFactorOneMinusBlendColor       }, // INV_FACTOR
	};

	static const MTLBlendOperation s_blendEquation[] =
	{
		MTLBlendOperationAdd,
		MTLBlendOperationSubtract,
		MTLBlendOperationReverseSubtract,
		MTLBlendOperationMin,
		MTLBlendOperationMax,
	};

	static const MTLCompareFunction s_cmpFunc[] =
	{
		MTLCompareFunctionAlways, //TODO: depth disable?
		MTLCompareFunctionLess,
		MTLCompareFunctionLessEqual,
		MTLCompareFunctionEqual,
		MTLCompareFunctionGreaterEqual,
		MTLCompareFunctionGreater,
		MTLCompareFunctionNotEqual,
		MTLCompareFunctionNever,
		MTLCompareFunctionAlways
	};

	static const MTLStencilOperation s_stencilOp[] =
	{
		MTLStencilOperationZero,
		MTLStencilOperationKeep,
		MTLStencilOperationReplace,
		MTLStencilOperationIncrementWrap,
		MTLStencilOperationIncrementClamp,
		MTLStencilOperationDecrementWrap,
		MTLStencilOperationDecrementClamp,
		MTLStencilOperationInvert
	};

	static const MTLSamplerAddressMode s_textureAddress[] =
	{
		MTLSamplerAddressModeRepeat,
		MTLSamplerAddressModeMirrorRepeat,
		MTLSamplerAddressModeClampToEdge,
	};

	static const MTLSamplerMinMagFilter s_textureFilterMinMag[] =
	{
		MTLSamplerMinMagFilterLinear,
		MTLSamplerMinMagFilterNearest,
		MTLSamplerMinMagFilterLinear,
	};

	static const MTLSamplerMipFilter s_textureFilterMip[] =
	{
		MTLSamplerMipFilterLinear,
		MTLSamplerMipFilterNearest,
	};

	struct TextureFormatInfo
	{
		MTLPixelFormat m_fmt;
		MTLPixelFormat m_fmtSrgb;
	};

	//TODO: add new ios/osx formats
	//TODO: add caps for format support
	static TextureFormatInfo s_textureFormat[] =
	{
		{ MTLPixelFormatInvalid,          MTLPixelFormatInvalid              }, // BC1
		{ MTLPixelFormatInvalid,          MTLPixelFormatInvalid              }, // BC2
		{ MTLPixelFormatInvalid,          MTLPixelFormatInvalid              }, // BC3
		{ MTLPixelFormatInvalid,          MTLPixelFormatInvalid              }, // BC4
		{ MTLPixelFormatInvalid,          MTLPixelFormatInvalid              }, // BC5
		{ MTLPixelFormatInvalid,          MTLPixelFormatInvalid              }, // BC6H
		{ MTLPixelFormatInvalid,          MTLPixelFormatInvalid              }, // BC7
		{ MTLPixelFormatInvalid,          MTLPixelFormatInvalid              }, // ETC1
		{ MTLPixelFormatETC2_RGB8,        MTLPixelFormatETC2_RGB8_sRGB       }, // ETC2
		{ MTLPixelFormatEAC_RGBA8,        MTLPixelFormatEAC_RGBA8_sRGB       }, // ETC2A
		{ MTLPixelFormatETC2_RGB8A1,      MTLPixelFormatETC2_RGB8A1_sRGB     }, // ETC2A1
		{ MTLPixelFormatPVRTC_RGB_2BPP,   MTLPixelFormatPVRTC_RGB_2BPP_sRGB  }, // PTC12
		{ MTLPixelFormatPVRTC_RGB_4BPP,   MTLPixelFormatPVRTC_RGB_4BPP_sRGB  }, // PTC14
		{ MTLPixelFormatPVRTC_RGBA_2BPP,  MTLPixelFormatPVRTC_RGBA_2BPP_sRGB }, // PTC12A
		{ MTLPixelFormatPVRTC_RGBA_4BPP,  MTLPixelFormatPVRTC_RGBA_4BPP_sRGB }, // PTC14A
		{ MTLPixelFormatInvalid,          MTLPixelFormatInvalid              }, // PTC22
		{ MTLPixelFormatInvalid,          MTLPixelFormatInvalid              }, // PTC24
		{ MTLPixelFormatInvalid,          MTLPixelFormatInvalid              }, // Unknown
		{ MTLPixelFormatInvalid,          MTLPixelFormatInvalid              }, // R1
		{ MTLPixelFormatA8Unorm,          MTLPixelFormatInvalid              }, // A8
		{ MTLPixelFormatR8Unorm,          MTLPixelFormatR8Unorm_sRGB         }, // R8
		{ MTLPixelFormatR8Sint,           MTLPixelFormatInvalid              }, // R8I
		{ MTLPixelFormatR8Uint,           MTLPixelFormatInvalid              }, // R8U
		{ MTLPixelFormatR8Snorm,          MTLPixelFormatInvalid              }, // R8S
		{ MTLPixelFormatR16Unorm,         MTLPixelFormatInvalid              }, // R16
		{ MTLPixelFormatR16Sint,          MTLPixelFormatInvalid              }, // R16I
		{ MTLPixelFormatR16Uint,          MTLPixelFormatInvalid              }, // R16U
		{ MTLPixelFormatR16Float,         MTLPixelFormatInvalid              }, // R16F
		{ MTLPixelFormatR16Snorm,         MTLPixelFormatInvalid              }, // R16S
		{ MTLPixelFormatR32Sint,          MTLPixelFormatInvalid              }, // R32I
		{ MTLPixelFormatR32Uint,          MTLPixelFormatInvalid              }, // R32U
		{ MTLPixelFormatR32Float,         MTLPixelFormatInvalid              }, // R32F
		{ MTLPixelFormatRG8Unorm,         MTLPixelFormatRG8Unorm_sRGB        }, // RG8
		{ MTLPixelFormatRG8Sint,          MTLPixelFormatInvalid              }, // RG8I
		{ MTLPixelFormatRG8Uint,          MTLPixelFormatInvalid              }, // RG8U
		{ MTLPixelFormatRG8Snorm,         MTLPixelFormatInvalid              }, // RG8S
		{ MTLPixelFormatRG16Unorm,        MTLPixelFormatInvalid              }, // RG16
		{ MTLPixelFormatRG16Sint,         MTLPixelFormatInvalid              }, // RG16I
		{ MTLPixelFormatRG16Uint,         MTLPixelFormatInvalid              }, // RG16U
		{ MTLPixelFormatRG16Float,        MTLPixelFormatInvalid              }, // RG16F
		{ MTLPixelFormatRG16Snorm,        MTLPixelFormatInvalid              }, // RG16S
		{ MTLPixelFormatRG32Sint,         MTLPixelFormatInvalid              }, // RG32I
		{ MTLPixelFormatRG32Uint,         MTLPixelFormatInvalid              }, // RG32U
		{ MTLPixelFormatRG32Float,        MTLPixelFormatInvalid              }, // RG32F
		{ MTLPixelFormatBGRA8Unorm,       MTLPixelFormatBGRA8Unorm_sRGB      }, // BGRA8
		{ MTLPixelFormatRGBA8Unorm,       MTLPixelFormatRGBA8Unorm_sRGB      }, // RGBA8
		{ MTLPixelFormatRGBA8Sint,        MTLPixelFormatInvalid              }, // RGBA8I
		{ MTLPixelFormatRGBA8Uint,        MTLPixelFormatInvalid              }, // RGBA8U
		{ MTLPixelFormatRGBA8Snorm,       MTLPixelFormatInvalid              }, // RGBA8S
		{ MTLPixelFormatRGBA16Unorm,      MTLPixelFormatInvalid              }, // RGBA16
		{ MTLPixelFormatRGBA16Sint,       MTLPixelFormatInvalid              }, // RGBA16I
		{ MTLPixelFormatRGBA16Uint,       MTLPixelFormatInvalid              }, // RGBA16I
		{ MTLPixelFormatRGBA16Float,      MTLPixelFormatInvalid              }, // RGBA16F
		{ MTLPixelFormatRGBA16Snorm,      MTLPixelFormatInvalid              }, // RGBA16S
		{ MTLPixelFormatRGBA32Sint,       MTLPixelFormatInvalid              }, // RGBA32I
		{ MTLPixelFormatRGBA32Uint,       MTLPixelFormatInvalid              }, // RGBA32U
		{ MTLPixelFormatRGBA32Float,      MTLPixelFormatInvalid              }, // RGBA32F
		{ MTLPixelFormatB5G6R5Unorm,      MTLPixelFormatInvalid              }, // R5G6B5
		{ MTLPixelFormatABGR4Unorm,       MTLPixelFormatInvalid              }, // RGBA4
		{ MTLPixelFormatA1BGR5Unorm,      MTLPixelFormatInvalid              }, // RGB5A1
		{ MTLPixelFormatRGB10A2Unorm,     MTLPixelFormatInvalid              }, // RGB10A2
		{ MTLPixelFormatRG11B10Float,     MTLPixelFormatInvalid              }, // R11G11B10F
		{ MTLPixelFormatInvalid,          MTLPixelFormatInvalid              }, // UnknownDepth
		{ MTLPixelFormatDepth32Float,     MTLPixelFormatInvalid              }, // D16
		{ MTLPixelFormatDepth32Float,     MTLPixelFormatInvalid              }, // D24
		{ MTLPixelFormatInvalid,          MTLPixelFormatInvalid              }, // D24S8
		{ MTLPixelFormatDepth32Float,     MTLPixelFormatInvalid              }, // D32
		{ MTLPixelFormatDepth32Float,     MTLPixelFormatInvalid              }, // D16F
		{ MTLPixelFormatDepth32Float,     MTLPixelFormatInvalid              }, // D24F
		{ MTLPixelFormatDepth32Float,     MTLPixelFormatInvalid              }, // D32F
		{ MTLPixelFormatStencil8,         MTLPixelFormatInvalid              }, // D0S8
	};
	BX_STATIC_ASSERT(TextureFormat::Count == BX_COUNTOF(s_textureFormat) );

	#define SHADER_FUNCTION_NAME ("xlatMtlMain")
	#define SHADER_UNIFORM_NAME ("_mtl_u")

	struct RendererContextMtl : public RendererContextI
	{
		RendererContextMtl()
			  :	m_numWindows(1),
				m_metalLayer(NULL),
				m_drawable(NULL),
				m_maxAnisotropy(1),
				m_rtMsaa(false),
				m_backBufferPixelFormatHash(0)
		{
			m_fbh.idx = invalidHandle;
		}

		~RendererContextMtl()
		{
		}

		bool init()
		{
			if ( NSClassFromString(@"CAMetalLayer") != nil)
			{
				//on iOS we need the layer as CAmetalLayer
#if BX_PLATFORM_IOS
				CAMetalLayer* metalLayer = (CAMetalLayer*)g_platformData.nwh;
				if (metalLayer == nil || ![metalLayer isKindOfClass:NSClassFromString(@"CAMetalLayer")])
				{
					BX_WARN(NULL != m_device, "Unable to create Metal device. Please set platform data window to a CAMetalLayer");
					return false;
				}
				m_metalLayer = metalLayer;
#elif BX_PLATFORM_OSX
				// create and set metalLayer
				NSWindow* nsWindow = (NSWindow*)g_platformData.nwh;

				[nsWindow.contentView setWantsLayer:YES];
				m_metalLayer = [CAMetalLayer layer];
				[nsWindow.contentView setLayer:m_metalLayer];
#endif // BX_PLATFORM_*

				m_device = (id<MTLDevice>)g_platformData.context;

				if (NULL == m_device)
				{
					m_device = MTLCreateSystemDefaultDevice();
				}
			}

			if (m_device==NULL || m_metalLayer==nil)
			{
				BX_WARN(NULL != m_device, "Unable to create Metal device.");
				return false;
			}

			m_metalLayer.device = m_device;

			m_commandQueue = m_device.newCommandQueue();
			BGFX_FATAL(NULL != m_commandQueue, Fatal::UnableToInitialize, "Unable to create Metal device.");

			m_renderPipelineDescriptor = newRenderPipelineDescriptor();
			m_depthStencilDescriptor = newDepthStencilDescriptor();
			m_frontFaceStencilDescriptor = newStencilDescriptor();
			m_backFaceStencilDescriptor = newStencilDescriptor();
			m_vertexDescriptor = newVertexDescriptor();
			m_textureDescriptor = newTextureDescriptor();
			m_samplerDescriptor = newSamplerDescriptor();

			m_uniformBuffer = m_device.newBufferWithLength(UNIFORM_BUFFER_SIZE, 0);
			m_uniformBufferVertexOffset = 0;
			m_uniformBufferFragmentOffset = 0;

			memset(m_uniforms, 0, sizeof(m_uniforms) );

			g_caps.supported |= (0
								 | BGFX_CAPS_TEXTURE_COMPARE_LEQUAL
								 | BGFX_CAPS_TEXTURE_3D
								 | BGFX_CAPS_INSTANCING
								 | BGFX_CAPS_VERTEX_ATTRIB_HALF
//								 | BGFX_CAPS_FRAGMENT_DEPTH //TODO: is this supported?
								 | BGFX_CAPS_BLEND_INDEPENDENT
								 | BGFX_CAPS_COMPUTE
								 | BGFX_CAPS_INDEX32
								 | BGFX_CAPS_DRAW_INDIRECT
								 );

			g_caps.maxTextureSize = 2048; //ASK: real caps width/height: 4096, but max depth(3D) size is only: 2048
				//TODO: OSX
#if BX_PLATFORM_IOS
			g_caps.maxFBAttachments = uint8_t(bx::uint32_min(m_device.supportsFeatureSet(MTLFeatureSet_iOS_GPUFamily2_v1) ? 8 :4, BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS));
#endif // BX_PLATFORM_*

			//todo: vendor id, device id, gpu enum
			//todo: texture format caps

			//add texture formats/caps/etc that are available only on new sdk/devices
#if BX_PLATFORM_IOS
#	ifdef __IPHONE_8_0
			if (OsVersionEqualOrGreater("8.0.0"))
			{
				s_textureFormat[TextureFormat::D24S8].m_fmt = MTLPixelFormatDepth32Float;
			}
#	endif // __IPHONE_8_0
#endif // BX_PLATFORM_*

			for (uint32_t ii = 0; ii < TextureFormat::Count; ++ii)
			{
				uint8_t support = (s_textureFormat[ii].m_fmt != MTLPixelFormatInvalid) ? BGFX_CAPS_FORMAT_TEXTURE_COLOR : BGFX_CAPS_FORMAT_TEXTURE_NONE;

				support |= (s_textureFormat[ii].m_fmtSrgb != MTLPixelFormatInvalid) ? BGFX_CAPS_FORMAT_TEXTURE_COLOR_SRGB : BGFX_CAPS_FORMAT_TEXTURE_NONE;

					//TODO: additional caps flags
//				support |= BGFX_CAPS_FORMAT_TEXTURE_VERTEX : BGFX_CAPS_FORMAT_TEXTURE_NONE;
//				support |= BGFX_CAPS_FORMAT_TEXTURE_IMAGE : BGFX_CAPS_FORMAT_TEXTURE_NONE;
//				support |= BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER : BGFX_CAPS_FORMAT_TEXTURE_NONE;

				g_caps.formats[ii] = support;
			}

			// Init reserved part of view name.
			for (uint32_t ii = 0; ii < BGFX_CONFIG_MAX_VIEWS; ++ii)
			{
				bx::snprintf(s_viewName[ii], BGFX_CONFIG_MAX_VIEW_NAME_RESERVED+1, "%3d   ", ii);
			}

			return true;
		}

	void shutdown()
	{
		for (uint32_t ii = 0; ii < BX_COUNTOF(m_shaders); ++ii)
		{
			m_shaders[ii].destroy();
		}

		for (uint32_t ii = 0; ii < BX_COUNTOF(m_textures); ++ii)
		{
			m_textures[ii].destroy();
		}

		MTL_RELEASE(m_depthStencilDescriptor);
		MTL_RELEASE(m_frontFaceStencilDescriptor);
		MTL_RELEASE(m_backFaceStencilDescriptor);
		MTL_RELEASE(m_renderPipelineDescriptor);
		MTL_RELEASE(m_vertexDescriptor);
		MTL_RELEASE(m_textureDescriptor);
		MTL_RELEASE(m_samplerDescriptor);

		MTL_RELEASE(m_backBufferDepth);
#if BX_PLATFORM_IOS
		MTL_RELEASE(m_backBufferStencil);
#endif // BX_PLATFORM_*

		MTL_RELEASE(m_uniformBuffer);
		MTL_RELEASE(m_commandQueue);
		MTL_RELEASE(m_device);
	}

	RendererType::Enum getRendererType() const BX_OVERRIDE
	{
		return RendererType::Metal;
	}

	const char* getRendererName() const BX_OVERRIDE
	{
		return BGFX_RENDERER_METAL_NAME;
	}


	void createIndexBuffer(IndexBufferHandle _handle, Memory* _mem, uint16_t _flags) BX_OVERRIDE
	{
		m_indexBuffers[_handle.idx].create(_mem->size, _mem->data, _flags);
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

	void createVertexBuffer(VertexBufferHandle _handle, Memory* _mem, VertexDeclHandle _declHandle, uint16_t _flags) BX_OVERRIDE
	{
		m_vertexBuffers[_handle.idx].create(_mem->size, _mem->data, _declHandle, _flags);
	}

	void destroyVertexBuffer(VertexBufferHandle _handle) BX_OVERRIDE
	{
		m_vertexBuffers[_handle.idx].destroy();
	}

	void createDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _size, uint16_t _flags) BX_OVERRIDE
	{
		m_indexBuffers[_handle.idx].create(_size, NULL, _flags);
	}

	void updateDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _offset, uint32_t _size, Memory* _mem) BX_OVERRIDE
	{
		m_indexBuffers[_handle.idx].update(_offset, bx::uint32_min(_size, _mem->size), _mem->data);
	}

	void destroyDynamicIndexBuffer(IndexBufferHandle _handle) BX_OVERRIDE
	{
		m_indexBuffers[_handle.idx].destroy();
	}

	void createDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _size, uint16_t _flags) BX_OVERRIDE
	{
		VertexDeclHandle decl = BGFX_INVALID_HANDLE;
		m_vertexBuffers[_handle.idx].create(_size, NULL, decl, _flags);
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
		m_program[_handle.idx].create(&m_shaders[_vsh.idx], &m_shaders[_fsh.idx]);
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

	void resizeTexture(TextureHandle _handle, uint16_t _width, uint16_t _height) BX_OVERRIDE
	{
		TextureMtl& texture = m_textures[_handle.idx];

		uint32_t size = sizeof(uint32_t) + sizeof(TextureCreate);
		const Memory* mem = alloc(size);

		bx::StaticMemoryBlockWriter writer(mem->data, mem->size);
		uint32_t magic = BGFX_CHUNK_MAGIC_TEX;
		bx::write(&writer, magic);

		TextureCreate tc;
		tc.m_flags   = texture.m_flags;
		tc.m_width   = _width;
		tc.m_height  = _height;
		tc.m_sides   = 0;
		tc.m_depth   = 0;
		tc.m_numMips = 1;
		tc.m_format  = texture.m_requestedFormat;
		tc.m_cubeMap = false;
		tc.m_mem     = NULL;
		bx::write(&writer, tc);

		texture.destroy();
		texture.create(mem, tc.m_flags, 0);

		release(mem);
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
		if ( NULL == m_drawable || NULL == m_drawable.texture)
			return;

		//TODO: we should wait for completion of pending commandBuffers
		//TODO: implement this with saveScreenshotBegin/End

		Texture backBuffer = m_drawable.texture;
		uint32_t width = backBuffer.width();
		uint32_t height = backBuffer.height();
		uint32_t length = width*height*4;
		uint8_t* data = (uint8_t*)BX_ALLOC(g_allocator, length);

        MTLRegion region = { 0, 0, 0, width, height, 1};

		backBuffer.getBytes(data, 4*width, 0, region, 0, 0);

		g_callback->screenShot(_filePath
					   , backBuffer.width()
					   , backBuffer.height()
					   , width*4
					   , data
					   , length
					   , false
					   );

		BX_FREE(g_allocator, data);
	}

	void updateViewName(uint8_t _id, const char* _name) BX_OVERRIDE
	{
		if (BX_ENABLED(BGFX_CONFIG_DEBUG_PIX) )
		{
			bx::strlcpy(&s_viewName[_id][BGFX_CONFIG_MAX_VIEW_NAME_RESERVED]
				, _name
				, BX_COUNTOF(s_viewName[0])-BGFX_CONFIG_MAX_VIEW_NAME_RESERVED
				);
		}
	}

	void updateUniform(uint16_t _loc, const void* _data, uint32_t _size) BX_OVERRIDE
	{
		memcpy(m_uniforms[_loc], _data, _size);
	}

	void setMarker(const char* _marker, uint32_t /*_size*/) BX_OVERRIDE
	{
		if (BX_ENABLED(BGFX_CONFIG_DEBUG_MTL) )
		{
			m_renderCommandEncoder.insertDebugSignpost(_marker);
		}
	}

	void submit(Frame* _render, ClearQuad& _clearQuad, TextVideoMemBlitter& _textVideoMemBlitter) BX_OVERRIDE;

	void blitSetup(TextVideoMemBlitter& _blitter) BX_OVERRIDE
	{
		RenderCommandEncoder rce = m_renderCommandEncoder;

		uint32_t width  = getBufferWidth();
		uint32_t height = getBufferHeight();

		//if (m_ovr.isEnabled() )
		//{
		//	m_ovr.getSize(width, height);
		//}

		FrameBufferHandle fbh = BGFX_INVALID_HANDLE;
		//TODO: change to default framebuffer - we need a new encoder for this!
		//setFrameBuffer(fbh, false);

		MTLViewport viewport = { 0.0f, 0.0f, (float)width, (float)height, 0.0f, 1.0f};
		rce.setViewport(viewport);
		MTLScissorRect rc = { 0,0,width,height };
		rce.setScissorRect(rc);
		rce.setCullMode(MTLCullModeNone);

		uint64_t state = BGFX_STATE_RGB_WRITE
						| BGFX_STATE_ALPHA_WRITE
						| BGFX_STATE_DEPTH_TEST_ALWAYS;

		setDepthStencilState(state);

		ProgramMtl& program = m_program[_blitter.m_program.idx];
		RenderPipelineState pipelineState = program.getRenderPipelineState(state, 0, fbh, _blitter.m_vb->decl, 0);
		rce.setRenderPipelineState(pipelineState);

		uint32_t vertexUniformBufferSize = program.m_vshConstantBufferSize;
		uint32_t fragmentUniformBufferSize = program.m_fshConstantBufferSize;

		if ( vertexUniformBufferSize )
		{
			m_uniformBufferVertexOffset = BX_ALIGN_MASK(m_uniformBufferVertexOffset, program.m_vshConstantBufferAlignmentMask);
			rce.setVertexBuffer(m_uniformBuffer, m_uniformBufferVertexOffset, 0);
		}

		m_uniformBufferFragmentOffset = m_uniformBufferVertexOffset + vertexUniformBufferSize;
		if ( fragmentUniformBufferSize )
		{
			m_uniformBufferFragmentOffset = BX_ALIGN_MASK(m_uniformBufferFragmentOffset, program.m_fshConstantBufferAlignmentMask);
			rce.setFragmentBuffer(m_uniformBuffer, m_uniformBufferFragmentOffset, 0);
		}

		VertexBufferMtl& vb = m_vertexBuffers[_blitter.m_vb->handle.idx];
		rce.setVertexBuffer(vb.m_buffer, 0, 1);

		float proj[16];
		bx::mtxOrtho(proj, 0.0f, (float)width, (float)height, 0.0f, 0.0f, 1000.0f);

		PredefinedUniform& predefined = program.m_predefined[0];
		uint8_t flags = predefined.m_type;
		setShaderUniform(flags, predefined.m_loc, proj, 4);

		m_textures[_blitter.m_texture.idx].commit(0);
	}

	void blitRender(TextVideoMemBlitter& _blitter, uint32_t _numIndices) BX_OVERRIDE
	{
		const uint32_t numVertices = _numIndices*4/6;
		if (0 < numVertices)
		{
			m_indexBuffers [_blitter.m_ib->handle.idx].update(0, _numIndices*2, _blitter.m_ib->data);
			m_vertexBuffers[_blitter.m_vb->handle.idx].update(0, numVertices*_blitter.m_decl.m_stride, _blitter.m_vb->data, true);

			m_renderCommandEncoder.drawIndexedPrimitives(MTLPrimitiveTypeTriangle, _numIndices, MTLIndexTypeUInt16, m_indexBuffers[_blitter.m_ib->handle.idx].m_buffer, 0, 1);
		}
	}

	void flip(HMD& /*_hmd*/) BX_OVERRIDE
	{
		if ( m_drawable == nil || m_commandBuffer == nil) //there was no draw call, cannot flip
			return;

		// Present and commit the command buffer
		m_commandBuffer.presentDrawable(m_drawable);
		MTL_RELEASE(m_drawable);

		m_commandBuffer.commit();

		//  using heavy syncing now
		//  TODO: refactor it with double/triple buffering frame data
		m_commandBuffer.waitUntilCompleted();

		MTL_RELEASE(m_commandBuffer);

		//TODO: support multiple windows on OSX
		/*
		 if (m_flip)
		 {
			for (uint32_t ii = 1, num = m_numWindows; ii < num; ++ii)
			{
				m_glctx.swap(m_frameBuffers[m_windows[ii].idx].m_swapChain);
			}

			if (!m_ovr.swap(_hmd) )
			{
				m_glctx.swap();
			}
		 }
		 */
	}

	void updateResolution(const Resolution& _resolution)
	{
		if (!!(_resolution.m_flags & BGFX_RESET_MAXANISOTROPY) )
		{
			m_maxAnisotropy = 16;
		}
		else
		{
			m_maxAnisotropy = 1;
		}

		//TODO: _resolution has wrong dimensions, using m_drawable.texture size now

		if ( NULL == m_drawable.texture )
			return;

		uint32_t width = (uint32_t)m_drawable.texture.width;
		uint32_t height = (uint32_t)m_drawable.texture.height;

		//TODO: there should be a way to specify if backbuffer needs stencil/depth.
		//TODO: support msaa
		if ( NULL == m_backBufferDepth || width!=m_backBufferDepth.width() || height!=m_backBufferDepth.height())
		{
			m_textureDescriptor.textureType = MTLTextureType2D;

#if BX_PLATFORM_IOS
			m_textureDescriptor.pixelFormat = MTLPixelFormatDepth32Float;
#else
			m_textureDescriptor.pixelFormat = MTLPixelFormatDepth32Float_Stencil8;
#endif // BX_PLATFORM_*

			m_textureDescriptor.width = width;
			m_textureDescriptor.height = height;
			m_textureDescriptor.depth = 1;
			m_textureDescriptor.mipmapLevelCount = 1;
			m_textureDescriptor.sampleCount = 1;
			m_textureDescriptor.arrayLength = 1;
			//m_textureDescriptor.resourceOptions = 0;

			if ( NULL != m_backBufferDepth )
			{
				release(m_backBufferDepth);
			}
			m_backBufferDepth = m_device.newTextureWithDescriptor(m_textureDescriptor);

#if BX_PLATFORM_IOS
			m_textureDescriptor.pixelFormat = MTLPixelFormatStencil8;
			m_textureDescriptor.width = width;
			m_textureDescriptor.height = height;

			if ( NULL != m_backBufferStencil )
			{
				release(m_backBufferStencil);
			}
			m_backBufferStencil = m_device.newTextureWithDescriptor(m_textureDescriptor);
#else
			m_backBufferStencil = m_backBufferDepth;
#endif // BX_PLATFORM_*

			bx::HashMurmur2A murmur;
			murmur.begin();
			murmur.add(1);
			murmur.add((uint32_t)m_drawable.texture.pixelFormat);
			murmur.add((uint32_t)m_backBufferDepth.pixelFormat());
			murmur.add((uint32_t)m_backBufferStencil.pixelFormat());
			m_backBufferPixelFormatHash = murmur.end();

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_frameBuffers); ++ii)
			{
				m_frameBuffers[ii].postReset();
			}

			m_textVideoMem.resize(false, width, height);
			m_textVideoMem.clear();
		}
	}

	void setShaderUniform(uint8_t _flags, uint32_t _loc, const void* _val, uint32_t _numRegs)
	{
		if (_flags&BGFX_UNIFORM_FRAGMENTBIT)
		{
			memcpy(&((char*)m_uniformBuffer.contents())[m_uniformBufferFragmentOffset + _loc], _val, _numRegs*16);
		}
		else
		{
			memcpy(&((char*)m_uniformBuffer.contents())[m_uniformBufferVertexOffset + _loc], _val, _numRegs*16);
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
				setShaderUniform(uint8_t(type), loc, data, num); \
				} \
				break;

			switch ( (uint32_t)type)
			{
				case UniformType::Mat3:
				case UniformType::Mat3|BGFX_UNIFORM_FRAGMENTBIT: \
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

					CASE_IMPLEMENT_UNIFORM(Int1,    I, int);
					CASE_IMPLEMENT_UNIFORM(Vec4,   F, float);
					CASE_IMPLEMENT_UNIFORM(Mat4, F, float);

				case UniformType::End:
					break;

				default:
					BX_TRACE("%4d: INVALID 0x%08x, t %d, l %d, n %d, c %d", _constantBuffer.getPos(), opcode, type, loc, num, copy);
					break;
			}

#undef CASE_IMPLEMENT_UNIFORM

		}
	}

	void setFrameBuffer(mtl::RenderPassDescriptor renderPassDescriptor, FrameBufferHandle _fbh, bool _msaa = true)
	{
		if (!isValid(_fbh) )
		{
			renderPassDescriptor.colorAttachments[0].texture = m_drawable.texture;
			renderPassDescriptor.depthAttachment.texture = m_backBufferDepth;
			renderPassDescriptor.stencilAttachment.texture = m_backBufferStencil;

			//todo: set resolve textures
		}
		else
		{
			FrameBufferMtl& frameBuffer = m_frameBuffers[_fbh.idx];

			for (uint32_t ii = 0; ii < frameBuffer.m_num; ++ii)
			{
				const TextureMtl& texture = m_textures[frameBuffer.m_colorHandle[ii].idx];
				renderPassDescriptor.colorAttachments[ii].texture = texture.m_ptr;
			}

			if (isValid(frameBuffer.m_depthHandle))
			{
				const TextureMtl& texture = m_textures[frameBuffer.m_depthHandle.idx];
				renderPassDescriptor.depthAttachment.texture = texture.m_ptr;
				renderPassDescriptor.stencilAttachment.texture = texture.m_ptrStencil;
				//TODO: stencilAttachment should be the same if packed/depth stencil format is used
			}

			//todo: set resolve textures
		}

		m_fbh = _fbh;
		m_rtMsaa = _msaa;
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

		DepthStencilState dss = m_depthStencilStateCache.find(hash);
		if (NULL == dss)
		{
			DepthStencilDescriptor desc = m_depthStencilDescriptor;
			uint32_t func = (_state&BGFX_STATE_DEPTH_TEST_MASK)>>BGFX_STATE_DEPTH_TEST_SHIFT;
			desc.depthWriteEnabled = !!(BGFX_STATE_DEPTH_WRITE & _state);
			desc.depthCompareFunction = s_cmpFunc[func];

			uint32_t bstencil = unpackStencil(1, _stencil);
			uint32_t frontAndBack = bstencil != BGFX_STENCIL_NONE && bstencil != fstencil;
			bstencil = frontAndBack ? bstencil : fstencil;

			if ( 0 != _stencil)
			{
				StencilDescriptor frontFaceDesc = m_frontFaceStencilDescriptor;
				StencilDescriptor backfaceDesc = m_backFaceStencilDescriptor;

				uint32_t readMask = (fstencil&BGFX_STENCIL_FUNC_RMASK_MASK)>>BGFX_STENCIL_FUNC_RMASK_SHIFT;
				uint32_t writeMask = 0xff;

				frontFaceDesc.stencilFailureOperation = s_stencilOp[(fstencil&BGFX_STENCIL_OP_FAIL_S_MASK)>>BGFX_STENCIL_OP_FAIL_S_SHIFT];
				frontFaceDesc.depthFailureOperation = s_stencilOp[(fstencil&BGFX_STENCIL_OP_FAIL_Z_MASK)>>BGFX_STENCIL_OP_FAIL_Z_SHIFT];
				frontFaceDesc.depthStencilPassOperation = s_stencilOp[(fstencil&BGFX_STENCIL_OP_PASS_Z_MASK)>>BGFX_STENCIL_OP_PASS_Z_SHIFT];
				frontFaceDesc.stencilCompareFunction  = s_cmpFunc[(fstencil&BGFX_STENCIL_TEST_MASK)>>BGFX_STENCIL_TEST_SHIFT];
				frontFaceDesc.readMask  = readMask;
				frontFaceDesc.writeMask = writeMask;

				backfaceDesc.stencilFailureOperation = s_stencilOp[(bstencil&BGFX_STENCIL_OP_FAIL_S_MASK)>>BGFX_STENCIL_OP_FAIL_S_SHIFT];
				backfaceDesc.depthFailureOperation = s_stencilOp[(bstencil&BGFX_STENCIL_OP_FAIL_Z_MASK)>>BGFX_STENCIL_OP_FAIL_Z_SHIFT];
				backfaceDesc.depthStencilPassOperation = s_stencilOp[(bstencil&BGFX_STENCIL_OP_PASS_Z_MASK)>>BGFX_STENCIL_OP_PASS_Z_SHIFT];
				backfaceDesc.stencilCompareFunction = s_cmpFunc[(bstencil&BGFX_STENCIL_TEST_MASK)>>BGFX_STENCIL_TEST_SHIFT];
				backfaceDesc.readMask  = readMask;
				backfaceDesc.writeMask = writeMask;

				desc.frontFaceStencil = frontFaceDesc;
				desc.backFaceStencil = backfaceDesc;
			}
			else
			{
				desc.backFaceStencil = NULL;
				desc.frontFaceStencil = NULL;
			}

			dss = m_device.newDepthStencilStateWithDescriptor(desc);

			m_depthStencilStateCache.add(hash, dss);
		}

		m_renderCommandEncoder.setDepthStencilState(dss);
		m_renderCommandEncoder.setStencilReferenceValue(ref);
	}

	SamplerState getSamplerState(uint32_t _flags)
	{
		_flags &= BGFX_TEXTURE_SAMPLER_BITS_MASK;
		SamplerState sampler = m_samplerStateCache.find(_flags);
		if (NULL == sampler)
		{

			m_samplerDescriptor.sAddressMode = s_textureAddress[(_flags&BGFX_TEXTURE_U_MASK)>>BGFX_TEXTURE_U_SHIFT];
			m_samplerDescriptor.tAddressMode = s_textureAddress[(_flags&BGFX_TEXTURE_V_MASK)>>BGFX_TEXTURE_V_SHIFT];
			m_samplerDescriptor.rAddressMode = s_textureAddress[(_flags&BGFX_TEXTURE_W_MASK)>>BGFX_TEXTURE_W_SHIFT];
			m_samplerDescriptor.minFilter = s_textureFilterMinMag[(_flags&BGFX_TEXTURE_MIN_MASK)>>BGFX_TEXTURE_MIN_SHIFT];
			m_samplerDescriptor.magFilter = s_textureFilterMinMag[(_flags&BGFX_TEXTURE_MAG_MASK)>>BGFX_TEXTURE_MAG_SHIFT];
			m_samplerDescriptor.mipFilter = s_textureFilterMip[(_flags&BGFX_TEXTURE_MIP_MASK)>>BGFX_TEXTURE_MIP_SHIFT];
			m_samplerDescriptor.lodMinClamp = 0;
			m_samplerDescriptor.lodMaxClamp = FLT_MAX;
			m_samplerDescriptor.normalizedCoordinates = TRUE;
			m_samplerDescriptor.maxAnisotropy =  m_maxAnisotropy;

				//TODO: I haven't found how to specify this. Comparison function can be specified in shader.
				//  On OSX this can be specified. There is no support for this on iOS right now.
			//const uint32_t cmpFunc = (_flags&BGFX_TEXTURE_COMPARE_MASK)>>BGFX_TEXTURE_COMPARE_SHIFT;
			//const uint8_t filter = 0 == cmpFunc ? 0 : D3D11_COMPARISON_FILTERING_BIT;
			//m_samplerDescriptor.comparisonFunc = 0 == cmpFunc ? D3D11_COMPARISON_NEVER : s_cmpFunc[cmpFunc];

			sampler = m_device.newSamplerStateWithDescriptor(m_samplerDescriptor);
			m_samplerStateCache.add(_flags, sampler);
		}

		return sampler;
	}

	uint32_t getBufferWidth()
	{
		return m_backBufferDepth.width();
	}

	uint32_t getBufferHeight()
	{
		return m_backBufferDepth.height();
	}



	Device        m_device;
	CommandQueue  m_commandQueue;
	CAMetalLayer* m_metalLayer;
	Texture       m_backBufferDepth;
	Texture       m_backBufferStencil;
	uint32_t      m_backBufferPixelFormatHash;
	uint32_t      m_maxAnisotropy;

	Buffer   m_uniformBuffer; //todo: use a pool of this
	uint32_t m_uniformBufferVertexOffset;
	uint32_t m_uniformBufferFragmentOffset;

	uint16_t          m_numWindows;
	FrameBufferHandle m_windows[BGFX_CONFIG_MAX_FRAME_BUFFERS];

	IndexBufferMtl  m_indexBuffers[BGFX_CONFIG_MAX_INDEX_BUFFERS];
	VertexBufferMtl m_vertexBuffers[BGFX_CONFIG_MAX_VERTEX_BUFFERS];
	ShaderMtl       m_shaders[BGFX_CONFIG_MAX_SHADERS];
	ProgramMtl      m_program[BGFX_CONFIG_MAX_PROGRAMS];
	TextureMtl      m_textures[BGFX_CONFIG_MAX_TEXTURES];
	FrameBufferMtl  m_frameBuffers[BGFX_CONFIG_MAX_FRAME_BUFFERS];
	VertexDecl      m_vertexDecls[BGFX_CONFIG_MAX_VERTEX_DECLS];
	UniformRegistry m_uniformReg;
	void*           m_uniforms[BGFX_CONFIG_MAX_UNIFORMS];

	StateCacheT<DepthStencilState> m_depthStencilStateCache;
	StateCacheT<SamplerState>      m_samplerStateCache;

	TextVideoMem m_textVideoMem;

	FrameBufferHandle m_fbh;
	bool m_rtMsaa;

	// descriptors
	RenderPipelineDescriptor m_renderPipelineDescriptor;
	DepthStencilDescriptor   m_depthStencilDescriptor;
	StencilDescriptor        m_frontFaceStencilDescriptor;
	StencilDescriptor        m_backFaceStencilDescriptor;
	VertexDescriptor         m_vertexDescriptor;
	TextureDescriptor        m_textureDescriptor;
	SamplerDescriptor        m_samplerDescriptor;

		// currently active objects data
	id <CAMetalDrawable> m_drawable;
	CommandBuffer m_commandBuffer;
	RenderCommandEncoder m_renderCommandEncoder;
};

	static RendererContextMtl* s_renderMtl;

	RendererContextI* rendererCreate()
	{
		s_renderMtl = BX_NEW(g_allocator, RendererContextMtl);
		if (!s_renderMtl->init())
		{
			BX_DELETE(g_allocator, s_renderMtl);
			s_renderMtl = NULL;
		}
		return s_renderMtl;
	}

	void rendererDestroy()
	{
		s_renderMtl->shutdown();
		BX_DELETE(g_allocator, s_renderMtl);
		s_renderMtl = NULL;
	}

	void writeString(bx::WriterI* _writer, const char* _str)
	{
		bx::write(_writer, _str, (int32_t)strlen(_str) );
	}

	void ShaderMtl::create(const Memory* _mem)
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

		//bool fragment = BGFX_CHUNK_MAGIC_FSH == magic;

		uint32_t iohash;
		bx::read(&reader, iohash);

		uint16_t count;
		bx::read(&reader, count);

		BX_TRACE("%s Shader consts %d"
				 , BGFX_CHUNK_MAGIC_FSH == magic ? "Fragment" : BGFX_CHUNK_MAGIC_VSH == magic ? "Vertex" : "Compute"
				 , count
				 );

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
		}

		uint32_t shaderSize;
		bx::read(&reader, shaderSize);

		const char* code = (const char*)reader.getDataPtr();
		bx::skip(&reader, shaderSize+1);

		int32_t codeLen = (int32_t)strlen(code);
		int32_t tempLen = codeLen + (4<<10);
		char* temp = (char*)alloca(tempLen);
		bx::StaticMemoryBlockWriter writer(temp, tempLen);

		//TODO: remove this hack. some shaders have problem with half<->float conversion
		writeString(&writer
					, "#define half float\n"
					 "#define half2 float2\n"
					 "#define half3 float3\n"
					 "#define half4 float4\n"
					);

		bx::write(&writer, code, codeLen);
		bx::write(&writer, '\0');
		code = temp;

			//TODO: use binary format
		Library lib = s_renderMtl->m_device.newLibraryWithSource(code);

		if (NULL != lib)
		{
			m_function = lib.newFunctionWithName(SHADER_FUNCTION_NAME);
		}

		BGFX_FATAL(NULL != m_function, bgfx::Fatal::InvalidShader, "Failed to create %s shader."
				   , BGFX_CHUNK_MAGIC_FSH == magic ? "Fragment" : BGFX_CHUNK_MAGIC_VSH == magic ? "Vertex" : "Compute");
	}

	void ProgramMtl::create(const ShaderMtl* _vsh, const ShaderMtl* _fsh)
	{
		BX_CHECK(NULL != _vsh->m_function.m_obj, "Vertex shader doesn't exist.");
		m_vsh = _vsh;

		if (NULL != _fsh)
		{
			BX_CHECK(NULL != _fsh->m_function.m_obj, "Fragment shader doesn't exist.");
			m_fsh = _fsh;
		}

		// get attributes
		memset(m_attributes, 0xff, sizeof(m_attributes) );
		uint32_t used = 0;
		uint32_t instUsed = 0;
		if ( NULL != _vsh->m_function.m_obj )
		{
			for (MTLVertexAttribute* attrib in _vsh->m_function.m_obj.vertexAttributes)
			{
				if ( attrib.active )
				{
					const char* name = utf8String(attrib.name);
					uint32_t loc = (uint32_t)attrib.attributeIndex;
					BX_TRACE("attr %s: %d", name, loc);

					for (uint8_t ii = 0; ii < Attrib::Count; ++ii)
					{
						if (!strcmp(s_attribName[ii],name))
						{
							m_attributes[ii] = loc;
							m_used[used++] = ii;
							break;
						}
					}

					for (uint32_t ii = 0; ii < BX_COUNTOF(s_instanceDataName); ++ii)
					{
						if (!strcmp(s_instanceDataName[ii],name))
						{
							m_instanceData[instUsed++] = loc;
						}
					}

				}
			}
		}
		m_used[used] = Attrib::Count;
		m_instanceData[instUsed] = 0xffff;
	}

	void ProgramMtl::destroy()
	{
		m_vsh = NULL;
		m_fsh = NULL;

		if (NULL != m_vshConstantBuffer)
		{
			ConstantBuffer::destroy(m_vshConstantBuffer);
			m_vshConstantBuffer = NULL;
		}

		if (NULL != m_fshConstantBuffer)
		{
			ConstantBuffer::destroy(m_fshConstantBuffer);
			m_fshConstantBuffer = NULL;
		}

		m_vshConstantBufferSize = 0;
		m_vshConstantBufferAlignmentMask = 0;
		m_fshConstantBufferSize = 0;
		m_fshConstantBufferAlignmentMask = 0;

		m_processedUniforms = false;
		m_numPredefined = 0;
	}

	UniformType::Enum convertMtlType(MTLDataType _type)
	{
		switch (_type)
		{
			case MTLDataTypeUInt:
			case MTLDataTypeInt:
				return UniformType::Int1;

			case MTLDataTypeFloat:
			case MTLDataTypeFloat2:
			case MTLDataTypeFloat3:
			case MTLDataTypeFloat4:
				return UniformType::Vec4;

			case MTLDataTypeFloat3x3:
				return UniformType::Mat3;

			case MTLDataTypeFloat4x4:
				return UniformType::Mat4;

		};

		BX_CHECK(false, "Unrecognized Mtl Data type 0x%04x.", _type);
		return UniformType::End;
	}

	RenderPipelineState ProgramMtl::getRenderPipelineState(uint64_t _state, uint32_t _rgba, FrameBufferHandle _fbHandle, VertexDeclHandle _declHandle,  uint16_t _numInstanceData)
	{
		_state &= (BGFX_STATE_BLEND_MASK|BGFX_STATE_BLEND_EQUATION_MASK|BGFX_STATE_ALPHA_WRITE|BGFX_STATE_RGB_WRITE|BGFX_STATE_BLEND_INDEPENDENT|BGFX_STATE_MSAA);

		bool independentBlendEnable = !!(BGFX_STATE_BLEND_INDEPENDENT & _state);

		bx::HashMurmur2A murmur;
		murmur.begin();
		murmur.add(_state);
		murmur.add(independentBlendEnable ? _rgba : 0);
		if (!isValid(_fbHandle) )
			murmur.add(s_renderMtl->m_backBufferPixelFormatHash);
		else
		{
			FrameBufferMtl& frameBuffer = s_renderMtl->m_frameBuffers[_fbHandle.idx];
			murmur.add(frameBuffer.m_pixelFormatHash);
		}
		murmur.add(_declHandle.idx);
		murmur.add(_numInstanceData);
		uint32_t hash = murmur.end();

		RenderPipelineState rps = m_renderPipelineStateCache.find(hash);
		if ( NULL == rps )
		{
			RenderPipelineDescriptor& 	pipelineDesc = s_renderMtl->m_renderPipelineDescriptor;
			reset(pipelineDesc);
			uint32_t frameBufferAttachment = 1;

			if (!isValid(_fbHandle) )
			{
				pipelineDesc.colorAttachments[0].pixelFormat = s_renderMtl->m_drawable.texture.pixelFormat;
				pipelineDesc.depthAttachmentPixelFormat = s_renderMtl->m_backBufferDepth.m_obj.pixelFormat;
				pipelineDesc.stencilAttachmentPixelFormat = s_renderMtl->m_backBufferStencil.m_obj.pixelFormat;
			}
			else
			{
				FrameBufferMtl& frameBuffer = s_renderMtl->m_frameBuffers[_fbHandle.idx];
				frameBufferAttachment = frameBuffer.m_num;

				for (uint32_t ii = 0; ii < frameBuffer.m_num; ++ii)
				{
					const TextureMtl& texture = s_renderMtl->m_textures[frameBuffer.m_colorHandle[ii].idx];
					pipelineDesc.colorAttachments[ii].pixelFormat = texture.m_ptr.m_obj.pixelFormat;
				}

				if (isValid(frameBuffer.m_depthHandle))
				{
					const TextureMtl& texture = s_renderMtl->m_textures[frameBuffer.m_depthHandle.idx];
					pipelineDesc.depthAttachmentPixelFormat = texture.m_ptr.m_obj.pixelFormat;
					if ( NULL != texture.m_ptrStencil)
						pipelineDesc.stencilAttachmentPixelFormat = texture.m_ptrStencil.m_obj.pixelFormat;
					//todo: stencil attachment should be the same as depth for packed depth/stencil
				}
			}

			// TODO: BGFX_STATE_MSAA using _fbHandle texture msaa values
			const uint32_t blend    = uint32_t( (_state&BGFX_STATE_BLEND_MASK)>>BGFX_STATE_BLEND_SHIFT);
			const uint32_t equation = uint32_t( (_state&BGFX_STATE_BLEND_EQUATION_MASK)>>BGFX_STATE_BLEND_EQUATION_SHIFT);

			const uint32_t srcRGB = (blend    )&0xf;
			const uint32_t dstRGB = (blend>> 4)&0xf;
			const uint32_t srcA   = (blend>> 8)&0xf;
			const uint32_t dstA   = (blend>>12)&0xf;

			const uint32_t equRGB = (equation   )&0x7;
			const uint32_t equA   = (equation>>3)&0x7;

			uint8_t writeMask = (_state&BGFX_STATE_ALPHA_WRITE) ? MTLColorWriteMaskAlpha : 0;
			writeMask |= (_state&BGFX_STATE_RGB_WRITE) ? MTLColorWriteMaskRed|MTLColorWriteMaskGreen|MTLColorWriteMaskBlue : 0;

			for (uint32_t ii = 0; ii < (independentBlendEnable ? 1 : frameBufferAttachment); ++ii)
			{
				RenderPipelineColorAttachmentDescriptor drt = pipelineDesc.colorAttachments[ii];

				drt.blendingEnabled = !!(BGFX_STATE_BLEND_MASK & _state);

				drt.sourceRGBBlendFactor      = s_blendFactor[srcRGB][0];
				drt.destinationRGBBlendFactor = s_blendFactor[dstRGB][0];
				drt.rgbBlendOperation        =	s_blendEquation[equRGB];

				drt.sourceAlphaBlendFactor		= s_blendFactor[srcA][1];
				drt.destinationAlphaBlendFactor = s_blendFactor[dstA][1];
				drt.alphaBlendOperation			= s_blendEquation[equA];

				drt.writeMask = writeMask;
			}

			if (independentBlendEnable)
			{
				for (uint32_t ii = 1, rgba = _rgba; ii < frameBufferAttachment; ++ii, rgba >>= 11)
				{
					RenderPipelineColorAttachmentDescriptor drt = pipelineDesc.colorAttachments[ii];

					drt.blendingEnabled = 0 != (rgba&0x7ff);

					const uint32_t src			 = (rgba   )&0xf;
					const uint32_t dst			 = (rgba>>4)&0xf;
					const uint32_t equationIndex = (rgba>>8)&0x7;

					drt.sourceRGBBlendFactor       = s_blendFactor[src][0];
					drt.destinationRGBBlendFactor  = s_blendFactor[dst][0];
					drt.rgbBlendOperation		   = s_blendEquation[equationIndex];

					drt.sourceAlphaBlendFactor		= s_blendFactor[src][1];
					drt.destinationAlphaBlendFactor = s_blendFactor[dst][1];
					drt.alphaBlendOperation			= s_blendEquation[equationIndex];

					drt.writeMask = writeMask;
				}
			}

			pipelineDesc.vertexFunction = m_vsh->m_function;
			pipelineDesc.fragmentFunction = m_fsh->m_function;

			if (isValid(_declHandle))
			{
				VertexDescriptor vertexDesc = s_renderMtl->m_vertexDescriptor;
				reset(vertexDesc);

				VertexDecl &vertexDecl = s_renderMtl->m_vertexDecls[_declHandle.idx];
				for (uint32_t ii = 0; Attrib::Count != m_used[ii]; ++ii)
				{
					Attrib::Enum attr = Attrib::Enum(m_used[ii]);
					uint32_t loc = m_attributes[attr];

					uint8_t num;
					AttribType::Enum type;
					bool normalized;
					bool asInt;
					vertexDecl.decode(attr, num, type, normalized, asInt);
					BX_CHECK(num<=4, "num must be <=4");

					if (0xff != vertexDecl.m_attributes[attr])
					{
						vertexDesc.attributes[loc].format = s_attribType[type][num-1][normalized?1:0];
						vertexDesc.attributes[loc].bufferIndex = 1;
						vertexDesc.attributes[loc].offset = vertexDecl.m_offset[attr];

						BX_TRACE("attrib:%s format: %d offset:%d", s_attribName[attr], (int)vertexDesc.attributes[loc].format, (int)vertexDesc.attributes[loc].offset);
					}
					else
					{	// missing attribute: using dummy attribute with smallest possible size
						vertexDesc.attributes[loc].format = MTLVertexFormatUChar2;
						vertexDesc.attributes[loc].bufferIndex = 1;
						vertexDesc.attributes[loc].offset = 0;
					}
				}

				vertexDesc.layouts[1].stride = vertexDecl.getStride();
				vertexDesc.layouts[1].stepFunction = MTLVertexStepFunctionPerVertex;

				BX_TRACE("stride: %d", (int)vertexDesc.layouts[1].stride);

				if (_numInstanceData > 0)
				{
					for (uint32_t ii = 0; 0xffff != m_instanceData[ii]; ++ii)
					{
						uint32_t loc = m_instanceData[ii];
						vertexDesc.attributes[loc].format = MTLVertexFormatFloat4;
						vertexDesc.attributes[loc].bufferIndex = 2;
						vertexDesc.attributes[loc].offset = ii*16;
					}

					vertexDesc.layouts[2].stride = _numInstanceData * 16;
					vertexDesc.layouts[2].stepFunction = MTLVertexStepFunctionPerInstance;
					vertexDesc.layouts[2].stepRate = 1;
				}

				pipelineDesc.vertexDescriptor = vertexDesc;
			}

			if (m_processedUniforms)
			{
				rps = s_renderMtl->m_device.newRenderPipelineStateWithDescriptor(pipelineDesc);
			}
			else
			{
				m_numPredefined = 0;
				RenderPipelineReflection reflection = NULL;
				rps = s_renderMtl->m_device.newRenderPipelineStateWithDescriptor(pipelineDesc, MTLPipelineOptionBufferTypeInfo, &reflection);

				if ( NULL != reflection )
				{
					for( int type =0; type<2; ++type)
					{
						ConstantBuffer*& constantBuffer = (type==0?m_vshConstantBuffer : m_fshConstantBuffer);
						uint8_t fragmentBit = (1 == type ? BGFX_UNIFORM_FRAGMENTBIT : 0);

						for( MTLArgument* arg in (type==0?reflection.vertexArguments:reflection.fragmentArguments))
						{
							BX_TRACE("arg: %s type:%d", utf8String(arg.name), arg.type);
							if (arg.active)
							{
								if (arg.type == MTLArgumentTypeBuffer && !strcmp(utf8String(arg.name),SHADER_UNIFORM_NAME) )
								{
									BX_CHECK( arg.index == 0, "Uniform buffer must be in the buffer slot 0.");
									BX_CHECK( MTLDataTypeStruct == arg.bufferDataType, "%s's type must be a struct",SHADER_UNIFORM_NAME );

									if ( MTLDataTypeStruct == arg.bufferDataType )
									{
										if ( type == 0)
										{
											m_vshConstantBufferSize = (uint32_t)arg.bufferDataSize;
											m_vshConstantBufferAlignmentMask = (uint32_t)arg.bufferAlignment - 1;
										}
										else
										{
											m_fshConstantBufferSize = (uint32_t)arg.bufferDataSize;
											m_fshConstantBufferAlignmentMask = (uint32_t)arg.bufferAlignment - 1;
										}

										for( MTLStructMember* uniform in arg.bufferStructType.members )
										{
											const char* name = utf8String(uniform.name);
											BX_TRACE("uniform: %s type:%d", name, uniform.dataType);

											MTLDataType dataType = uniform.dataType;
											uint32_t num = 1;

											if (dataType==MTLDataTypeArray)
											{
												dataType = uniform.arrayType.elementType;
												num = (uint32_t)uniform.arrayType.arrayLength;
											}

											switch (dataType) {
												case MTLDataTypeFloat4 :
													num *= 1;
													break;
												case MTLDataTypeFloat4x4:
													num *= 4;
													break;
												case MTLDataTypeFloat3x3:
													num *= 3;
													break;
												default:
													BX_WARN(0, "Unsupported uniform MTLDataType: %d", uniform.dataType);
													break;
											}

											PredefinedUniform::Enum predefined = nameToPredefinedUniformEnum(name);
											if (PredefinedUniform::Count != predefined)
											{
												m_predefined[m_numPredefined].m_loc   = uint32_t(uniform.offset);
												m_predefined[m_numPredefined].m_count = uint16_t(num);
												m_predefined[m_numPredefined].m_type  = uint8_t(predefined|fragmentBit);
												m_numPredefined++;
											}
											else
											{
												const UniformInfo* info = s_renderMtl->m_uniformReg.find(name);
												if (NULL != info)
												{
													if (NULL == constantBuffer)
													{
														constantBuffer = ConstantBuffer::create(1024);
													}

													UniformType::Enum type = convertMtlType(dataType);
													constantBuffer->writeUniformHandle((UniformType::Enum)(type|fragmentBit), uint32_t(uniform.offset), info->m_handle, uint16_t(num) );
													BX_TRACE("store %s %d offset:%d", name, info->m_handle, uint32_t(uniform.offset));
												}
											}

										}
									}
								} else if (arg.type == MTLArgumentTypeTexture)
								{
									const char* name = utf8String(arg.name);
									BX_TRACE("texture: %s index:%d", name, arg.index);
								} else if (arg.type == MTLArgumentTypeSampler)
								{
									const char* name = utf8String(arg.name);
									BX_TRACE("sampler: %s index:%d", name, arg.index);
								}
							}
						}
						if (NULL != constantBuffer)
							constantBuffer->finish();
					}
				}
				m_processedUniforms = true;
			}

			m_renderPipelineStateCache.add(hash, rps);
		}

		return rps;
	}

	void BufferMtl::create(uint32_t _size, void* _data, uint16_t _flags, uint16_t _stride, bool _vertex)
	{
		m_size = _size;
		if ( NULL == _data )
			m_buffer = s_renderMtl->m_device.newBufferWithLength(_size, 0);
		else
			m_buffer = s_renderMtl->m_device.newBufferWithBytes(_data, _size, 0);
	}

	void BufferMtl::update(uint32_t _offset, uint32_t _size, void* _data, bool _discard)
	{
		memcpy( (uint8_t*)m_buffer.contents() + _offset, _data, _size);
	}

	void VertexBufferMtl::create(uint32_t _size, void* _data, VertexDeclHandle _declHandle, uint16_t _flags)
	{
		m_decl = _declHandle;
		uint16_t stride = isValid(_declHandle)
		? s_renderMtl->m_vertexDecls[_declHandle.idx].m_stride
		: 0
		;

		BufferMtl::create(_size, _data, _flags, stride, true);
	}

	void TextureMtl::create(const Memory* _mem, uint32_t _flags, uint8_t _skip)
	{
		m_sampler = s_renderMtl->getSamplerState(_flags);

		ImageContainer imageContainer;

		if (imageParse(imageContainer, _mem->data, _mem->size) )
		{
			uint8_t numMips = imageContainer.m_numMips;
			const uint8_t startLod = uint8_t(bx::uint32_min(_skip, numMips-1) );
			numMips -= startLod;
			const ImageBlockInfo& blockInfo = getBlockInfo(TextureFormat::Enum(imageContainer.m_format) );
			const uint32_t textureWidth  = bx::uint32_max(blockInfo.blockWidth,  imageContainer.m_width >>startLod);
			const uint32_t textureHeight = bx::uint32_max(blockInfo.blockHeight, imageContainer.m_height>>startLod);

			m_flags = _flags;
			m_requestedFormat = (uint8_t)imageContainer.m_format;
			m_textureFormat   = (uint8_t)imageContainer.m_format;

			const TextureFormatInfo& tfi = s_textureFormat[m_requestedFormat];
			const bool convert = MTLPixelFormatInvalid == tfi.m_fmt;

			uint8_t bpp = getBitsPerPixel(TextureFormat::Enum(m_textureFormat) );
			if (convert)
			{
				m_textureFormat = (uint8_t)TextureFormat::RGBA8;
				bpp = 32;
			}

			TextureDescriptor desc = s_renderMtl->m_textureDescriptor;

			if (imageContainer.m_cubeMap)
			{
				desc.textureType = MTLTextureTypeCube;
			}
			else if (imageContainer.m_depth > 1)
			{
				desc.textureType = MTLTextureType3D;
			}
			else
			{
				desc.textureType = MTLTextureType2D;
			}

			m_numMips = numMips;

			const bool compressed = isCompressed(TextureFormat::Enum(m_textureFormat) );

			BX_TRACE("Texture %3d: %s (requested: %s), %dx%d%s%s."
					 , this - s_renderMtl->m_textures
					 , getName( (TextureFormat::Enum)m_textureFormat)
					 , getName( (TextureFormat::Enum)m_requestedFormat)
					 , textureWidth
					 , textureHeight
					 , imageContainer.m_cubeMap ? "x6" : ""
					 , 0 != (_flags&BGFX_TEXTURE_RT_MASK) ? " (render target)" : ""
					 );


			const bool bufferOnly   = 0 != (_flags&BGFX_TEXTURE_RT_BUFFER_ONLY);
			const bool computeWrite = 0 != (_flags&BGFX_TEXTURE_COMPUTE_WRITE);
			const bool renderTarget = 0 != (_flags&BGFX_TEXTURE_RT_MASK);
			const bool srgb			= 0 != (_flags&BGFX_TEXTURE_SRGB) || imageContainer.m_srgb;
			const uint32_t msaaQuality = bx::uint32_satsub( (_flags&BGFX_TEXTURE_RT_MSAA_MASK)>>BGFX_TEXTURE_RT_MSAA_SHIFT, 1);
//			const DXGI_SAMPLE_DESC& msaa = s_msaa[msaaQuality];

			MTLPixelFormat format = MTLPixelFormatInvalid;
			if (srgb)
			{
				format      = s_textureFormat[m_textureFormat].m_fmtSrgb;
				BX_WARN(format != MTLPixelFormatInvalid, "sRGB not supported for texture format %d", m_textureFormat);
			}

			if (format == MTLPixelFormatInvalid)
			{
				// not swizzled and not sRGB, or sRGB unsupported
				format		= s_textureFormat[m_textureFormat].m_fmt;
			}

			desc.pixelFormat = format;
			desc.width = textureWidth;
			desc.height = textureHeight;
			desc.depth = bx::uint32_max(1,imageContainer.m_depth);
			desc.mipmapLevelCount = imageContainer.m_numMips;
			desc.sampleCount = 1; //TODO: set samplecount -  If textureType is not MTLTextureType2DMultisample, the value must be 1.

			//TODO: set resource flags depending on usage(renderTarget/computeWrite/etc) on iOS9/OSX

			m_ptr = s_renderMtl->m_device.newTextureWithDescriptor(desc);
			if ( m_requestedFormat == TextureFormat::D24S8 && desc.pixelFormat == MTLPixelFormatDepth32Float )
			{
				desc.pixelFormat = MTLPixelFormatStencil8;
				m_ptrStencil = s_renderMtl->m_device.newTextureWithDescriptor(desc);
			}

			uint8_t* temp = NULL;
			if (convert)
			{
				temp = (uint8_t*)BX_ALLOC(g_allocator, textureWidth*textureHeight*4);
			}

			for (uint8_t side = 0, numSides = imageContainer.m_cubeMap ? 6 : 1; side < numSides; ++side)
			{
				uint32_t width  = textureWidth;
				uint32_t height = textureHeight;
				uint32_t depth  = imageContainer.m_depth;

				for (uint8_t lod = 0, num = numMips; lod < num; ++lod)
				{
					width  = bx::uint32_max(1, width);
					height = bx::uint32_max(1, height);
					depth  = bx::uint32_max(1, depth);

					ImageMip mip;
					if (imageGetRawData(imageContainer, side, lod+startLod, _mem->data, _mem->size, mip) )
					{
						const uint8_t* data = mip.m_data;

						if (convert)
						{
							imageDecodeToRgba8(temp
											   , mip.m_data
											   , mip.m_width
											   , mip.m_height
											   , mip.m_width*4
											   , mip.m_format
											   );
							data = temp;
						}

						MTLRegion region = { 0, 0, 0, width, height, depth};

						uint32_t bytesPerRow;
						uint32_t bytesPerImage;

						if ( compressed && !convert)
						{
							if ( format >= MTLPixelFormatPVRTC_RGB_2BPP && format <= MTLPixelFormatPVRTC_RGBA_4BPP_sRGB)
							{
								bytesPerRow = 0;
								bytesPerImage = 0;
							}
							else
							{
								bytesPerRow = (mip.m_width / blockInfo.blockWidth )*mip.m_blockSize;
								bytesPerImage = (desc.textureType == MTLTextureType3D) ? (mip.m_height/blockInfo.blockHeight)*bytesPerRow : 0;
							}
						}
						else
						{
							bytesPerRow = width * bpp / 8;
							bytesPerImage = (desc.textureType == MTLTextureType3D) ? width * height * bpp / 8 : 0;
						}

						m_ptr.replaceRegion(region, lod, side, data, bytesPerRow, bytesPerImage);
					}
					else if (!computeWrite)
					{
						//TODO: do we need to clear to zero??
					}

					width  >>= 1;
					height >>= 1;
					depth  >>= 1;
				}
			}

			if (NULL != temp)
			{
				BX_FREE(g_allocator, temp);
			}
		}
	}

	void TextureMtl::update(uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem)
	{
		MTLRegion region = { _rect.m_x, _rect.m_y, _z, _rect.m_width, _rect.m_height, _depth};

		const uint32_t bpp    = getBitsPerPixel(TextureFormat::Enum(m_textureFormat) );
		const uint32_t rectpitch = _rect.m_width*bpp/8;
		const uint32_t srcpitch  = UINT16_MAX == _pitch ? rectpitch : _pitch;

		const bool convert = m_textureFormat != m_requestedFormat;

		uint8_t* data = _mem->data;
		uint8_t* temp = NULL;

		if (convert)
		{
			temp = (uint8_t*)BX_ALLOC(g_allocator, rectpitch*_rect.m_height);
			imageDecodeToBgra8(temp, data, _rect.m_width, _rect.m_height, srcpitch, m_requestedFormat);
			data = temp;
		}

		m_ptr.replaceRegion(region, _mip, _side, data, srcpitch, srcpitch * _rect.m_height);

		if (NULL != temp)
		{
			BX_FREE(g_allocator, temp);
		}
	}

	void TextureMtl::commit(uint8_t _stage, uint32_t _flags)
	{
		//TODO: vertex or fragment stage?
		s_renderMtl->m_renderCommandEncoder.setFragmentTexture(m_ptr, _stage);
		s_renderMtl->m_renderCommandEncoder.setFragmentSamplerState(0 == (BGFX_SAMPLER_DEFAULT_FLAGS & _flags)
																	? s_renderMtl->getSamplerState(_flags)
																	: m_sampler, _stage);
	}

	void FrameBufferMtl::create(uint8_t _num, const TextureHandle* _handles)
	{
		m_num = 0;
		for (uint32_t ii = 0; ii < _num; ++ii)
		{
			TextureHandle handle = _handles[ii];
			if (isValid(handle) )
			{
				const TextureMtl& texture = s_renderMtl->m_textures[handle.idx];

				//TODO: separate stencil buffer? or just use packed depth/stencil (which is not available on iOS8)
				if (isDepth( (TextureFormat::Enum)texture.m_textureFormat) )
				{
					m_depthHandle = handle;
				}
				else
				{
					m_colorHandle[m_num] = handle;
					m_num++;
				}
			}
		}

		bx::HashMurmur2A murmur;
		murmur.begin();

		murmur.add(m_num);
		for (uint32_t ii = 0; ii < m_num; ++ii)
		{
			const TextureMtl& texture = s_renderMtl->m_textures[m_colorHandle[ii].idx];
			murmur.add((uint32_t)texture.m_ptr.pixelFormat());
		}
		const TextureMtl& depthTexture = s_renderMtl->m_textures[m_depthHandle.idx];
		murmur.add((uint32_t)depthTexture.m_ptr.pixelFormat());
		murmur.add((uint32_t)MTLPixelFormatInvalid); //stencil

		m_pixelFormatHash = murmur.end();
	}

	void FrameBufferMtl::create(uint16_t _denseIdx, void* _nwh, uint32_t _width, uint32_t _height, TextureFormat::Enum _depthFormat)
	{
		BX_WARN(false, "FrameBufferMtl::create not yet implemented");
	}

	void FrameBufferMtl::postReset()
	{
		BX_WARN(false, "FrameBufferMtl::postReset not yet implemented");
		//TODO: what should we do here?
	}

	uint16_t FrameBufferMtl::destroy()
	{
		m_num = 0;
		m_depthHandle.idx = invalidHandle;

		uint16_t denseIdx = m_denseIdx;
		m_denseIdx = UINT16_MAX;

		return denseIdx;
	}

	void RendererContextMtl::submit(Frame* _render, ClearQuad& _clearQuad, TextVideoMemBlitter& _textVideoMemBlitter) BX_OVERRIDE
	{
		m_commandBuffer = m_commandQueue.commandBuffer();
		retain(m_commandBuffer); // keep alive to be useable at 'flip'

		//TODO: multithreading with multiple commandbuffer
		// is there a FAST way to tell which view is active?

		//TODO: acquire CAMetalDrawable just before we really need it. When we are using an encoder with target metalLayer's texture
		m_drawable = m_metalLayer.nextDrawable;
		retain(m_drawable); // keep alive to be useable at 'flip'

		m_uniformBufferVertexOffset = 0;
		m_uniformBufferFragmentOffset = 0;

		updateResolution(_render->m_resolution);

		int64_t elapsed = -bx::getHPCounter();
		int64_t captureElapsed = 0;

		if (_render->m_debug & (BGFX_DEBUG_IFH|BGFX_DEBUG_STATS) )
		{
			//TODO
			//m_gpuTimer.begin();
		}

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

		_render->m_hmdInitialized = false;

		const bool hmdEnabled = false;
		ViewState viewState(_render, hmdEnabled);
		uint32_t blendFactor = 0;

		bool wireframe = !!(_render->m_debug&BGFX_DEBUG_WIREFRAME);

		//TODO: REMOVE THIS - TEMPORARY HACK
		m_textureDescriptor.textureType = MTLTextureType2D;
		m_textureDescriptor.pixelFormat = MTLPixelFormatRGBA8Unorm;
		m_textureDescriptor.width = 4;
		m_textureDescriptor.height = 4;
		m_textureDescriptor.depth = 1;
		m_textureDescriptor.mipmapLevelCount = 1;
		m_textureDescriptor.sampleCount = 1; //TODO: set samplecount -  If textureType is not MTLTextureType2DMultisample, the value must be 1.
		Texture zeroTexture = m_device.newTextureWithDescriptor(m_textureDescriptor);

		uint16_t programIdx = invalidHandle;
		SortKey key;
		uint16_t view = UINT16_MAX;
		FrameBufferHandle fbh = BGFX_INVALID_HANDLE;

		//ASK: why should we use this? It changes topology, so possible renders a big mess, doesn't it?
		//const uint64_t primType = _render->m_debug&BGFX_DEBUG_WIREFRAME ? BGFX_STATE_PT_LINES : 0;
		const uint64_t primType = 0;
		uint8_t primIndex = uint8_t(primType>>BGFX_STATE_PT_SHIFT);
		PrimInfo prim = s_primInfo[primIndex];

		ProgramMtl* currentProgram = NULL;
		mtl::RenderCommandEncoder  rce;

		bool wasCompute = false;
		bool viewHasScissor = false;
		Rect viewScissorRect;
		viewScissorRect.clear();

		uint32_t statsNumPrimsSubmitted[BX_COUNTOF(s_primInfo)] = {};
		uint32_t statsNumPrimsRendered[BX_COUNTOF(s_primInfo)] = {};
		uint32_t statsNumInstances[BX_COUNTOF(s_primInfo)] = {};
		uint32_t statsNumDrawIndirect[BX_COUNTOF(s_primInfo)] = {};
		uint32_t statsNumIndices = 0;
		uint32_t statsKeyType[2] = {};

		if (0 == (_render->m_debug&BGFX_DEBUG_IFH) )
		{
			bool viewRestart = false;
			uint8_t eye = 0;
			uint8_t restartState = 0;
			viewState.m_rect = _render->m_rect[0];

			int32_t numItems = _render->m_num;
			for (int32_t item = 0, restartItem = numItems; item < numItems || restartItem < numItems;)
			{
				const bool isCompute = key.decode(_render->m_sortKeys[item], _render->m_viewRemap);
				statsKeyType[isCompute]++;

				const bool viewChanged = 0
					|| key.m_view != view
					|| item == numItems
				;
				const RenderItem& renderItem = _render->m_renderItem[_render->m_sortValues[item] ];
				++item;

				if (viewChanged)
				{
					if (1 == restartState)
					{
						restartState = 2;
						item = restartItem;
						restartItem = numItems;
						view = UINT16_MAX;
						continue;
					}

					view = key.m_view;
					programIdx = invalidHandle;


					viewRestart = ( (BGFX_VIEW_STEREO == (_render->m_viewFlags[view] & BGFX_VIEW_STEREO) ) );
					viewRestart &= hmdEnabled;
					if (viewRestart)
					{
						if (0 == restartState)
						{
							restartState = 1;
							restartItem  = item - 1;
						}

						eye = (restartState - 1) & 1;
						restartState &= 1;
					}
					else
					{
						eye = 0;
					}

					viewState.m_rect = _render->m_rect[view];
					if (viewRestart)
					{
						viewState.m_rect.m_x = eye * (viewState.m_rect.m_width+1)/2;
						viewState.m_rect.m_width /= 2;
					}

					const Rect& scissorRect = _render->m_scissor[view];
					viewHasScissor = !scissorRect.isZero();
					viewScissorRect = viewHasScissor ? scissorRect : viewState.m_rect;
					Clear& clr = _render->m_clear[view];

					mtl::RenderPassDescriptor renderPassDescriptor = newRenderPassDescriptor();

					//todo: check FB size
					uint32_t width  = getBufferWidth();
					uint32_t height = getBufferHeight();
					Rect viewRect = viewState.m_rect;
					bool fullscreenRect = (0 == viewRect.m_x && 0 == viewRect.m_y	&&  width  == viewRect.m_width	&&  height == viewRect.m_height);

					//TODO/OPTIMIZATION: merge views with same target framebuffer into one renderPass

					fbh = _render->m_fb[view];
					setFrameBuffer(renderPassDescriptor, fbh);

					RenderPassColorAttachmentDescriptor colorAttachment0 = renderPassDescriptor.colorAttachments[0];
					if (BGFX_CLEAR_COLOR & clr.m_flags)
					{
						if (BGFX_CLEAR_COLOR_USE_PALETTE & clr.m_flags)
						{
							uint8_t index = (uint8_t)bx::uint32_min(BGFX_CONFIG_MAX_CLEAR_COLOR_PALETTE-1, clr.m_index[0]);
							const float* rgba = _render->m_clearColor[index];
							const float rr = rgba[0];
							const float gg = rgba[1];
							const float bb = rgba[2];
							const float aa = rgba[3];
							colorAttachment0.clearColor = MTLClearColorMake(rr,gg,bb,aa);
						}
						else
						{
							float rr = clr.m_index[0]*1.0f/255.0f;
							float gg = clr.m_index[1]*1.0f/255.0f;
							float bb = clr.m_index[2]*1.0f/255.0f;
							float aa = clr.m_index[3]*1.0f/255.0f;
							colorAttachment0.clearColor = MTLClearColorMake(rr,gg,bb,aa);
						}

						colorAttachment0.loadAction = MTLLoadActionClear;
					}
					else
						colorAttachment0.loadAction = MTLLoadActionLoad;

					//TODO: optimize store actions use discard flag
					RenderPassDepthAttachmentDescriptor depthAttachment = renderPassDescriptor.depthAttachment;
					if ( NULL != depthAttachment.texture)
					{
						depthAttachment.clearDepth = clr.m_depth;
						depthAttachment.loadAction = (BGFX_CLEAR_DEPTH & clr.m_flags) ? MTLLoadActionClear : MTLLoadActionLoad;
						depthAttachment.storeAction = MTLStoreActionStore;
					}

					RenderPassStencilAttachmentDescriptor stencilAttachment = renderPassDescriptor.stencilAttachment;
					if ( NULL != stencilAttachment.texture )
					{
						stencilAttachment.clearStencil = clr.m_stencil;
						stencilAttachment.loadAction = (BGFX_CLEAR_STENCIL & clr.m_flags) ? MTLLoadActionClear : MTLLoadActionLoad;
						stencilAttachment.storeAction = MTLStoreActionStore;
					}

					if ( 0 != m_renderCommandEncoder)
					{
						m_renderCommandEncoder.endEncoding();
					}
					rce = m_commandBuffer.renderCommandEncoderWithDescriptor(renderPassDescriptor);
					m_renderCommandEncoder = rce;
					MTL_RELEASE(renderPassDescriptor);

					//TODO: REMOVE THIS!!!!
					// TERRIBLE HACK TO SUPPRESS DEBUG LAYER WARNING ABOUT MISSING TEXTURE/SAMPLER AT 0 in 20-nanovg
					m_renderCommandEncoder.setFragmentTexture(zeroTexture, 0);
					m_renderCommandEncoder.setFragmentSamplerState(getSamplerState(0), 0);

					rce.setTriangleFillMode(wireframe? MTLTriangleFillModeLines : MTLTriangleFillModeFill);

					if (BX_ENABLED(BGFX_CONFIG_DEBUG_MTL) )
					{
						if ( item != 1) //ASK: better check ? I don't get the whole restart thing
							rce.popDebugGroup();

						rce.pushDebugGroup(s_viewName[view]);
					}

					MTLViewport vp;
					vp.originX = viewState.m_rect.m_x;
					vp.originY = viewState.m_rect.m_y;
					vp.width    = viewState.m_rect.m_width;
					vp.height   = viewState.m_rect.m_height;
					vp.znear = 0.0f;
					vp.zfar = 1.0f;
					rce.setViewport(vp);

					if (BGFX_CLEAR_NONE != (clr.m_flags & BGFX_CLEAR_MASK) && !fullscreenRect)
					{	//TODO: fallback to clear with quad
						//clearQuad(_clearQuad, viewState.m_rect, clr, _render->m_clearColor);
					}
				}

		//TODO: iscompute

				bool resetState = viewChanged || wasCompute;

				if (wasCompute)
				{
					wasCompute = false;

					programIdx = invalidHandle;
					currentProgram = NULL;

					//TODO
					//invalidateCompute();
				}

				const RenderDraw& draw = renderItem.draw;

				const uint64_t newFlags = draw.m_flags;
				uint64_t changedFlags = currentState.m_flags ^ draw.m_flags;
				currentState.m_flags = newFlags;

				const uint64_t newStencil = draw.m_stencil;
				uint64_t changedStencil = currentState.m_stencil ^ draw.m_stencil;
				currentState.m_stencil = newStencil;

				if (resetState)
				{
					currentState.clear();
					currentState.m_scissor = !draw.m_scissor;
					changedFlags = BGFX_STATE_MASK;
					changedStencil = packStencil(BGFX_STENCIL_MASK, BGFX_STENCIL_MASK);
					currentState.m_flags = newFlags;
					currentState.m_stencil = newStencil;

					programIdx = invalidHandle;
					setDepthStencilState(newFlags, packStencil(BGFX_STENCIL_DEFAULT, BGFX_STENCIL_DEFAULT));

					const uint64_t pt = newFlags&BGFX_STATE_PT_MASK;
					primIndex = uint8_t(pt>>BGFX_STATE_PT_SHIFT);
				}

				if (prim.m_type != s_primInfo[primIndex].m_type)
				{
					prim = s_primInfo[primIndex];
				}

				uint16_t scissor = draw.m_scissor;
				if (currentState.m_scissor != scissor)
				{
					currentState.m_scissor = scissor;

					MTLScissorRect rc;
					if (UINT16_MAX == scissor)
					{
						if (viewHasScissor)
						{
							rc.x   = viewScissorRect.m_x;
							rc.y    = viewScissorRect.m_y;
							rc.width  = viewScissorRect.m_width;
							rc.height = viewScissorRect.m_height;
						}
						else
						{   // can't disable: set to view rect
							rc.x   = viewState.m_rect.m_x;
							rc.y    = viewState.m_rect.m_y;
							rc.width  = viewState.m_rect.m_width;
							rc.height = viewState.m_rect.m_height;
						}
					}
					else
					{
						Rect scissorRect;
						scissorRect.intersect(viewScissorRect, _render->m_rectCache.m_cache[scissor]);
						rc.x   = scissorRect.m_x;
						rc.y    = scissorRect.m_y;
						rc.width  = scissorRect.m_width;
						rc.height = scissorRect.m_height;
					}
					rce.setScissorRect(rc);
				}

				if ( (BGFX_STATE_DEPTH_WRITE|BGFX_STATE_DEPTH_TEST_MASK) & changedFlags
					|| 0 != changedStencil)
				{
					setDepthStencilState(newFlags,newStencil);
				}

				if ( (0
					  | BGFX_STATE_CULL_MASK
					  | BGFX_STATE_ALPHA_REF_MASK
					  | BGFX_STATE_PT_MASK
					  //| BGFX_STATE_POINT_SIZE_MASK //TODO: not supported. could be supported with uniform
					  ) & changedFlags)
				{
					if (BGFX_STATE_CULL_MASK & changedFlags)
					{
						const uint64_t pt = newFlags&BGFX_STATE_CULL_MASK;
						uint8_t cullIndex = uint8_t(pt>>BGFX_STATE_CULL_SHIFT);
						rce.setCullMode(s_cullMode[cullIndex]);
					}

					if (BGFX_STATE_ALPHA_REF_MASK & changedFlags)
					{
						uint32_t ref = (newFlags&BGFX_STATE_ALPHA_REF_MASK)>>BGFX_STATE_ALPHA_REF_SHIFT;
						viewState.m_alphaRef = ref/255.0f;
					}

					const uint64_t pt = newFlags&BGFX_STATE_PT_MASK;
					primIndex = uint8_t(pt>>BGFX_STATE_PT_SHIFT);
					if (prim.m_type != s_primInfo[primIndex].m_type)
					{
						prim = s_primInfo[primIndex];
					}
				}

				if ( (blendFactor != draw.m_rgba) && !(newFlags & BGFX_STATE_BLEND_INDEPENDENT) )
				{
					const uint32_t rgba = draw.m_rgba;
					float rr = ( (rgba>>24)     )/255.0f;
					float gg = ( (rgba>>16)&0xff)/255.0f;
					float bb = ( (rgba>> 8)&0xff)/255.0f;
					float aa = ( (rgba    )&0xff)/255.0f;
					rce.setBlendColor(rr,gg,bb,aa);

					blendFactor = draw.m_rgba;
				}

				bool programChanged = false;
				bool constantsChanged = draw.m_constBegin < draw.m_constEnd;
				rendererUpdateUniforms(this, _render->m_constantBuffer, draw.m_constBegin, draw.m_constEnd);

				if (key.m_program != programIdx ||
					(BGFX_STATE_BLEND_MASK|BGFX_STATE_BLEND_EQUATION_MASK|BGFX_STATE_ALPHA_WRITE|BGFX_STATE_RGB_WRITE|BGFX_STATE_BLEND_INDEPENDENT|BGFX_STATE_MSAA) & changedFlags ||
					currentState.m_vertexBuffer.idx != draw.m_vertexBuffer.idx ||
					currentState.m_vertexDecl.idx != draw.m_vertexDecl.idx ||
					currentState.m_instanceDataStride != draw.m_instanceDataStride ||
					( (blendFactor != draw.m_rgba) && !!(newFlags & BGFX_STATE_BLEND_INDEPENDENT) ) )
				{
					programIdx = key.m_program;
					currentState.m_vertexDecl         = draw.m_vertexDecl;
					currentState.m_instanceDataStride = draw.m_instanceDataStride;

					if (invalidHandle == programIdx)
					{
						currentProgram = NULL;
						continue;
					}
					else
					{
						ProgramMtl& program = m_program[programIdx];
						currentProgram = &program;

						uint16_t handle = draw.m_vertexBuffer.idx;
						const VertexBufferMtl& vb = m_vertexBuffers[handle];
						VertexDeclHandle decl;
						decl.idx = !isValid(vb.m_decl) ? draw.m_vertexDecl.idx : vb.m_decl.idx;

						RenderPipelineState pipelineState = program.getRenderPipelineState(newFlags, draw.m_rgba, fbh, decl, draw.m_instanceDataStride/16);
						if ( NULL == pipelineState )
						{  //call with invalid program
							currentProgram = NULL;
							programIdx = invalidHandle;
							continue;
						}

						rce.setRenderPipelineState(pipelineState);
					}

					programChanged =
					constantsChanged = true;
				}

				if (invalidHandle != programIdx)
				{
					ProgramMtl& program = m_program[programIdx];

					uint32_t vertexUniformBufferSize = program.m_vshConstantBufferSize;
					uint32_t fragmentUniformBufferSize = program.m_fshConstantBufferSize;

					if ( vertexUniformBufferSize )
					{
						m_uniformBufferVertexOffset = BX_ALIGN_MASK(m_uniformBufferVertexOffset, program.m_vshConstantBufferAlignmentMask);
						rce.setVertexBuffer(m_uniformBuffer, m_uniformBufferVertexOffset, 0);
					}

					m_uniformBufferFragmentOffset = m_uniformBufferVertexOffset + vertexUniformBufferSize;
					if ( fragmentUniformBufferSize )
					{
						m_uniformBufferFragmentOffset = BX_ALIGN_MASK(m_uniformBufferFragmentOffset, program.m_fshConstantBufferAlignmentMask);
						rce.setFragmentBuffer(m_uniformBuffer, m_uniformBufferFragmentOffset, 0);
					}

					//TODO: create new UniformBuffer when not enough place for next buffer

					if (constantsChanged)
					{
						ConstantBuffer* vcb = program.m_vshConstantBuffer;
						if (NULL != vcb)
						{
							commit(*vcb);
						}

						ConstantBuffer* fcb = program.m_fshConstantBuffer;
						if (NULL != fcb)
						{
							commit(*fcb);
						}
					}

					viewState.setPredefined<4>(this, view, eye, program, _render, draw);

					m_uniformBufferFragmentOffset += fragmentUniformBufferSize;
					m_uniformBufferVertexOffset = m_uniformBufferFragmentOffset;
				}

				{
					for (uint8_t stage = 0; stage < BGFX_CONFIG_MAX_TEXTURE_SAMPLERS; ++stage)
					{
						const Binding& sampler = draw.m_bind[stage];
						Binding& current = currentState.m_bind[stage];
						if (current.m_idx != sampler.m_idx
							||  current.m_un.m_draw.m_flags != sampler.m_un.m_draw.m_flags
							||  programChanged)
						{
							if (invalidHandle != sampler.m_idx)
							{
								TextureMtl& texture = m_textures[sampler.m_idx];
								texture.commit(stage, sampler.m_un.m_draw.m_flags);
							}
						}

						current = sampler;
					}
				}

				if (currentState.m_vertexBuffer.idx       != draw.m_vertexBuffer.idx
					||  currentState.m_startVertex			  != draw.m_startVertex
					||  currentState.m_instanceDataBuffer.idx != draw.m_instanceDataBuffer.idx
					||  currentState.m_instanceDataOffset     != draw.m_instanceDataOffset
					)
				{
					currentState.m_vertexBuffer           = draw.m_vertexBuffer;
					currentState.m_startVertex           = draw.m_startVertex;
					currentState.m_instanceDataBuffer.idx = draw.m_instanceDataBuffer.idx;
					currentState.m_instanceDataOffset     = draw.m_instanceDataOffset;

					uint16_t handle = draw.m_vertexBuffer.idx;
					if (invalidHandle != handle)
					{
						const VertexBufferMtl& vb = m_vertexBuffers[handle];

						uint16_t decl = !isValid(vb.m_decl) ? draw.m_vertexDecl.idx : vb.m_decl.idx;
						const VertexDecl& vertexDecl = m_vertexDecls[decl];
						uint32_t offset = draw.m_startVertex  * vertexDecl.getStride();

						rce.setVertexBuffer(vb.m_buffer, offset, 1);

						if (isValid(draw.m_instanceDataBuffer) )
						{
							const VertexBufferMtl& inst = m_vertexBuffers[draw.m_instanceDataBuffer.idx];
							rce.setVertexBuffer(inst.m_buffer, draw.m_instanceDataOffset, 2);
						}
					}
				}

				if (isValid(currentState.m_vertexBuffer) )
				{
					uint32_t numVertices = draw.m_numVertices;
					if (UINT32_MAX == numVertices)
					{
						const VertexBufferMtl& vb = m_vertexBuffers[currentState.m_vertexBuffer.idx];
						uint16_t decl = !isValid(vb.m_decl) ? draw.m_vertexDecl.idx : vb.m_decl.idx;
						const VertexDecl& vertexDecl = m_vertexDecls[decl];
						numVertices = vb.m_size/vertexDecl.m_stride;
					}

					uint32_t numIndices        = 0;
					uint32_t numPrimsSubmitted = 0;
					uint32_t numInstances      = 0;
					uint32_t numPrimsRendered  = 0;
					uint32_t numDrawIndirect   = 0;

					if (isValid(draw.m_indirectBuffer) )
					{
						 // TODO: indirect draw
					}
					else
					{
						if (isValid(draw.m_indexBuffer) )
						{
							const IndexBufferMtl& ib = m_indexBuffers[draw.m_indexBuffer.idx];
							MTLIndexType indexType = 0 == (ib.m_flags & BGFX_BUFFER_INDEX32) ? MTLIndexTypeUInt16 : MTLIndexTypeUInt32;

							if (UINT32_MAX == draw.m_numIndices)
							{
								const uint32_t indexSize = 0 == (ib.m_flags & BGFX_BUFFER_INDEX32) ? 2 : 4;
								numIndices        = ib.m_size/indexSize;
								numPrimsSubmitted = numIndices/prim.m_div - prim.m_sub;
								numInstances      = draw.m_numInstances;
								numPrimsRendered  = numPrimsSubmitted*draw.m_numInstances;

								rce.drawIndexedPrimitives(prim.m_type, numIndices, indexType, ib.m_buffer, 0, draw.m_numInstances);
							}
							else if (prim.m_min <= draw.m_numIndices)
							{
								const uint32_t indexSize = 0 == (ib.m_flags & BGFX_BUFFER_INDEX32) ? 2 : 4;
								numIndices        = draw.m_numIndices;
								numPrimsSubmitted = numIndices/prim.m_div - prim.m_sub;
								numInstances      = draw.m_numInstances;
								numPrimsRendered  = numPrimsSubmitted*draw.m_numInstances;

								rce.drawIndexedPrimitives(prim.m_type, numIndices, indexType, ib.m_buffer, draw.m_startIndex * indexSize,numInstances);
							}
						}
						else
						{
							numPrimsSubmitted = numVertices/prim.m_div - prim.m_sub;
							numInstances      = draw.m_numInstances;
							numPrimsRendered  = numPrimsSubmitted*draw.m_numInstances;

							rce.drawPrimitives(prim.m_type, 0, draw.m_numVertices, draw.m_numInstances);
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
				//TODO
				//invalidateCompute();
			}

			if (0 < _render->m_num)
			{
				//ASK: we now using one commandBuffer that is commited in flush. Should we implement this?
				//if (0 != (m_resolution.m_flags & BGFX_RESET_FLUSH_AFTER_RENDER) )
				{
					// ????
					//deviceCtx->Flush();
				}

				captureElapsed = -bx::getHPCounter();
				//TODO
				//capture();
				captureElapsed += bx::getHPCounter();
			}
		}

		if (BX_ENABLED(BGFX_CONFIG_DEBUG_MTL) )
		{
			if ( 0 < _render->m_num)
				rce.popDebugGroup();
		}

		//TODO: debug stats
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
			rce.pushDebugGroup("debugstats");

			static uint32_t maxGpuLatency = 0;
			static double   maxGpuElapsed = 0.0f;
			double elapsedGpuMs = 0.0;

			//TODO: gputimer
			/*			m_gpuTimer.end();

			 while (m_gpuTimer.get() )
			 {
				double toGpuMs = 1000.0 / double(m_gpuTimer.m_frequency);
				elapsedGpuMs   = m_gpuTimer.m_elapsed * toGpuMs;
				maxGpuElapsed  = elapsedGpuMs > maxGpuElapsed ? elapsedGpuMs : maxGpuElapsed;
			 }
			 maxGpuLatency = bx::uint32_imax(maxGpuLatency, m_gpuTimer.m_control.available()-1);
			 */
			TextVideoMem& tvm = m_textVideoMem;

			static int64_t next = now;

			if (now >= next)
			{
				next = now + bx::getHPFrequency();

				double freq = double(bx::getHPFrequency() );
				double toMs = 1000.0/freq;

				tvm.clear();
				uint16_t pos = 0;
				tvm.printf(0, pos++, BGFX_CONFIG_DEBUG ? 0x89 : 0x8f, " %s / " BX_COMPILER_NAME " / " BX_CPU_NAME " / " BX_ARCH_NAME " / " BX_PLATFORM_NAME " "
				   , getRendererName()
				   );

				//const D3DADAPTER_IDENTIFIER9& identifier = m_identifier;
				//tvm.printf(0, pos++, 0x0f, " Device: %s (%s)", identifier.Description, identifier.Driver);

				pos = 10;
				tvm.printf(10, pos++, 0x8e, "       Frame: %7.3f, % 7.3f \x1f, % 7.3f \x1e [ms] / % 6.2f FPS "
						   , double(frameTime)*toMs
						   , double(min)*toMs
						   , double(max)*toMs
						   , freq/frameTime
						   );

				/*
				 const uint32_t msaa = (m_resolution.m_flags&BGFX_RESET_MSAA_MASK)>>BGFX_RESET_MSAA_SHIFT;
				 tvm.printf(10, pos++, 0x8e, " Reset flags: [%c] vsync, [%c] MSAAx%d, [%c] MaxAnisotropy "
				 , !!(m_resolution.m_flags&BGFX_RESET_VSYNC) ? '\xfe' : ' '
					, 0 != msaa ? '\xfe' : ' '
				 , 1<<msaa
				 , !!(m_resolution.m_flags&BGFX_RESET_MAXANISOTROPY) ? '\xfe' : ' '
				 );
		 */
				double elapsedCpuMs = double(elapsed)*toMs;
				tvm.printf(10, pos++, 0x8e, "   Submitted: %4d (draw %4d, compute %4d) / CPU %3.4f [ms] %c GPU %3.4f [ms] (latency %d)"
						   , _render->m_num
						   , statsKeyType[0]
						   , statsKeyType[1]
						   , elapsedCpuMs
						   , elapsedCpuMs > maxGpuElapsed ? '>' : '<'
						   , maxGpuElapsed
						   , maxGpuLatency
						   );
				maxGpuLatency = 0;
				maxGpuElapsed = 0.0;

				for (uint32_t ii = 0; ii < BX_COUNTOF(s_primName); ++ii)
				{
					tvm.printf(10, pos++, 0x8e, "   %9s: %7d (#inst: %5d), submitted: %7d"
					   , s_primName[ii]
					   , statsNumPrimsRendered[ii]
					   , statsNumInstances[ii]
					   , statsNumPrimsSubmitted[ii]
					   );
				}

				tvm.printf(10, pos++, 0x8e, "     Indices: %7d", statsNumIndices);
				tvm.printf(10, pos++, 0x8e, "    DVB size: %7d", _render->m_vboffset);
				tvm.printf(10, pos++, 0x8e, "    DIB size: %7d", _render->m_iboffset);

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

			rce.popDebugGroup();
		}
		else if (_render->m_debug & BGFX_DEBUG_TEXT)
		{
			rce.pushDebugGroup("debugtext");

			blit(this, _textVideoMemBlitter, _render->m_textVideoMem);

			rce.popDebugGroup();
		}

		//TODO: REMOVE THIS - TEMPORARY HACK
		release(zeroTexture);

		rce.endEncoding();
		m_renderCommandEncoder = 0;
	}

} /* namespace mtl */ } // namespace bgfx

#else

namespace bgfx { namespace mtl
	{
		RendererContextI* rendererCreate()
		{
			return NULL;
		}

		void rendererDestroy()
		{
		}
	} /* namespace mtl */ } // namespace bgfx

#endif // BGFX_CONFIG_RENDERER_METAL
