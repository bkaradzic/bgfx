/*
 * Copyright 2011-2016 Attila Kocsis. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
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

#define UNIFORM_BUFFER_SIZE (8*1024*1024)

/*
 // known metal shader generation issues:
   03-raymarch: OSX10.11.3 nothing is visible ( depth/color swap in fragment output struct fixed this )
   14-shadowvolumes: in texture as stencil mode - columns/bunny are dark. in fs_shadowvolume_color_lighting SAMPLER2D(s_texStencil, 1) is
		converted to "texture2d<float> s_texStencil [[texture(0)]], sampler _mtlsmp_s_texStencil [[sampler(0)]]". Slot is 1 -> 0.
   15-shadowmaps-simple: shader compilation error
   16-shadowmaps:  //problem with essl -> metal: SAMPLER2D(u_shadowMap0, 4);  sampler index is lost. Shadowmap is set to slot 4, but
      metal shader uses sampler/texture slot 0. this could require changes outside of renderer_mtl?
	  packFloatToRGBA needs highp. currently it uses half.
   24-nbody: no generated compute shaders for metal
   27-terrain: shaderc generates invalid metal shader for vs_terrain_height_texture. vertex output: half4 gl_Position [[position]], should be float4
   31-rsm:
      <program source>:6:23: error: type 'half4' (aka 'vector_half4') is not valid for attribute 'position'
      half4 gl_Position [[position]];


Known issues(driver problems??):
  OSX mac mini(late 2014), OSX10.11.3 : nanovg-rendering: color writemask off causes problem...
		03-raymarch: OSX nothing is visible  ( depth/color order should be swapped in fragment output struct)
					works fine with newer OSX
  iPad mini 2,  iOS 8.1.1:  21-deferred: scissor not working properly
							26-occlusion: query doesn't work with two rendercommandencoders
			Only on this device ( no problem on iPad Air 2 with iOS9.3.1)

  TODOs:
 - framebufferMtl and TextureMtl resolve

 - FrameBufferMtl::postReset recreate framebuffer???

	renderpass load/resolve
 - capture with msaa: 07-callback
 - implement fb discard. problematic with multiple views that has same fb...
 - msaa color/depth/stencil is not saved. could have problem when we switch back to msaa framebuffer
 - refactor store/load actions to support msaa/discard/capture/readback etc...

 - finish savescreenshot with screenshotbegin/end

 - support multiple windows: 22-windows
 - multithreading with multiple commandbuffer

 - compute and drawindirect: 24-nbody (needs compute shaders)

 INFO:
  - 15-shadowmaps-simple (example needs modification mtxCrop znew = z * 0.5 + 0.5 is not needed ) could be hacked in shader too

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
		//Note: unnormalized is handled as normalized now
		{
			{ MTLVertexFormatUInt1010102Normalized, MTLVertexFormatUInt1010102Normalized },
			{ MTLVertexFormatUInt1010102Normalized, MTLVertexFormatUInt1010102Normalized },
			{ MTLVertexFormatUInt1010102Normalized, MTLVertexFormatUInt1010102Normalized },
			{ MTLVertexFormatUInt1010102Normalized, MTLVertexFormatUInt1010102Normalized }
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
			{ MTLVertexFormatHalf3, MTLVertexFormatHalf3 },
			{ MTLVertexFormatHalf4, MTLVertexFormatHalf4 }
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
		MTLCompareFunctionAlways,
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
		MTLSamplerAddressModeClampToZero,
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

	static TextureFormatInfo s_textureFormat[] =
	{
		{ MTLPixelFormat(130) /*BC1_RGBA*/,				MTLPixelFormat(131) /*BC1_RGBA_sRGB*/        }, // BC1
		{ MTLPixelFormat(132) /*BC2_RGBA*/,				MTLPixelFormat(133) /*BC2_RGBA_sRGB*/        }, // BC2
		{ MTLPixelFormat(134) /*BC3_RGBA*/,				MTLPixelFormat(135) /*BC3_RGBA_sRGB*/        }, // BC3
		{ MTLPixelFormat(140) /*BC4_RUnorm*/,			MTLPixelFormatInvalid                        }, // BC4
		{ MTLPixelFormat(142) /*BC5_RGUnorm*/,			MTLPixelFormatInvalid                        }, // BC5
		{ MTLPixelFormat(150) /*BC6H_RGBFloat*/,		MTLPixelFormatInvalid                        }, // BC6H
		{ MTLPixelFormat(152) /*BC7_RGBAUnorm*/,		MTLPixelFormat(153) /*BC7_RGBAUnorm_sRGB*/   }, // BC7
		{ MTLPixelFormatInvalid,						MTLPixelFormatInvalid                        }, // ETC1
		{ MTLPixelFormat(180) /*ETC2_RGB8*/,			MTLPixelFormat(181) /*ETC2_RGB8_sRGB*/       }, // ETC2
		{ MTLPixelFormat(178) /*EAC_RGBA8*/,			MTLPixelFormat(179) /*EAC_RGBA8_sRGB*/       }, // ETC2A
		{ MTLPixelFormat(182) /*ETC2_RGB8A1*/,			MTLPixelFormat(183) /*ETC2_RGB8A1_sRGB*/     }, // ETC2A1
		{ MTLPixelFormat(160) /*PVRTC_RGB_2BPP*/,		MTLPixelFormat(161) /*PVRTC_RGB_2BPP_sRGB*/  }, // PTC12
		{ MTLPixelFormat(162) /*PVRTC_RGB_4BPP*/,		MTLPixelFormat(163) /*PVRTC_RGB_4BPP_sRGB*/  }, // PTC14
		{ MTLPixelFormat(164) /*PVRTC_RGBA_2BPP*/,		MTLPixelFormat(165) /*PVRTC_RGBA_2BPP_sRGB*/ }, // PTC12A
		{ MTLPixelFormat(166) /*PVRTC_RGBA_4BPP*/,		MTLPixelFormat(167) /*PVRTC_RGBA_4BPP_sRGB*/ }, // PTC14A
		{ MTLPixelFormatInvalid,						MTLPixelFormatInvalid                        }, // PTC22
		{ MTLPixelFormatInvalid,						MTLPixelFormatInvalid                        }, // PTC24
		{ MTLPixelFormatInvalid,						MTLPixelFormatInvalid                        }, // Unknown
		{ MTLPixelFormatInvalid,						MTLPixelFormatInvalid                        }, // R1
		{ MTLPixelFormatA8Unorm,						MTLPixelFormatInvalid                        }, // A8
		{ MTLPixelFormatR8Unorm,						MTLPixelFormat(11) /*R8Unorm_sRGB*/          }, // R8
		{ MTLPixelFormatR8Sint,							MTLPixelFormatInvalid                        }, // R8I
		{ MTLPixelFormatR8Uint,							MTLPixelFormatInvalid                        }, // R8U
		{ MTLPixelFormatR8Snorm,						MTLPixelFormatInvalid                        }, // R8S
		{ MTLPixelFormatR16Unorm,						MTLPixelFormatInvalid                        }, // R16
		{ MTLPixelFormatR16Sint,						MTLPixelFormatInvalid                        }, // R16I
		{ MTLPixelFormatR16Uint,						MTLPixelFormatInvalid                        }, // R16U
		{ MTLPixelFormatR16Float,						MTLPixelFormatInvalid                        }, // R16F
		{ MTLPixelFormatR16Snorm,						MTLPixelFormatInvalid                        }, // R16S
		{ MTLPixelFormatR32Sint,						MTLPixelFormatInvalid                        }, // R32I
		{ MTLPixelFormatR32Uint,						MTLPixelFormatInvalid                        }, // R32U
		{ MTLPixelFormatR32Float,						MTLPixelFormatInvalid                        }, // R32F
		{ MTLPixelFormatRG8Unorm,						MTLPixelFormat(31) /*RG8Unorm_sRGB*/         }, // RG8
		{ MTLPixelFormatRG8Sint,						MTLPixelFormatInvalid                        }, // RG8I
		{ MTLPixelFormatRG8Uint,						MTLPixelFormatInvalid                        }, // RG8U
		{ MTLPixelFormatRG8Snorm,						MTLPixelFormatInvalid                        }, // RG8S
		{ MTLPixelFormatRG16Unorm,						MTLPixelFormatInvalid                        }, // RG16
		{ MTLPixelFormatRG16Sint,						MTLPixelFormatInvalid                        }, // RG16I
		{ MTLPixelFormatRG16Uint,						MTLPixelFormatInvalid                        }, // RG16U
		{ MTLPixelFormatRG16Float,						MTLPixelFormatInvalid                        }, // RG16F
		{ MTLPixelFormatRG16Snorm,						MTLPixelFormatInvalid                        }, // RG16S
		{ MTLPixelFormatRG32Sint,						MTLPixelFormatInvalid                        }, // RG32I
		{ MTLPixelFormatRG32Uint,						MTLPixelFormatInvalid                        }, // RG32U
		{ MTLPixelFormatRG32Float,						MTLPixelFormatInvalid                        }, // RG32F
		{ MTLPixelFormatInvalid,						MTLPixelFormatInvalid                        }, // RGB8
		{ MTLPixelFormatInvalid,						MTLPixelFormatInvalid                        }, // RGB8I
		{ MTLPixelFormatInvalid,						MTLPixelFormatInvalid                        }, // RGB8U
		{ MTLPixelFormatInvalid,						MTLPixelFormatInvalid                        }, // RGB8S
		{ MTLPixelFormatRGB9E5Float,					MTLPixelFormatInvalid                        }, // RGB9E5F
		{ MTLPixelFormatBGRA8Unorm,						MTLPixelFormatBGRA8Unorm_sRGB                }, // BGRA8
		{ MTLPixelFormatRGBA8Unorm,						MTLPixelFormatRGBA8Unorm_sRGB                }, // RGBA8
		{ MTLPixelFormatRGBA8Sint,						MTLPixelFormatInvalid                        }, // RGBA8I
		{ MTLPixelFormatRGBA8Uint,						MTLPixelFormatInvalid                        }, // RGBA8U
		{ MTLPixelFormatRGBA8Snorm,						MTLPixelFormatInvalid                        }, // RGBA8S
		{ MTLPixelFormatRGBA16Unorm,					MTLPixelFormatInvalid                        }, // RGBA16
		{ MTLPixelFormatRGBA16Sint,						MTLPixelFormatInvalid                        }, // RGBA16I
		{ MTLPixelFormatRGBA16Uint,						MTLPixelFormatInvalid                        }, // RGBA16U
		{ MTLPixelFormatRGBA16Float,					MTLPixelFormatInvalid                        }, // RGBA16F
		{ MTLPixelFormatRGBA16Snorm,					MTLPixelFormatInvalid                        }, // RGBA16S
		{ MTLPixelFormatRGBA32Sint,						MTLPixelFormatInvalid                        }, // RGBA32I
		{ MTLPixelFormatRGBA32Uint,						MTLPixelFormatInvalid                        }, // RGBA32U
		{ MTLPixelFormatRGBA32Float,					MTLPixelFormatInvalid                        }, // RGBA32F
		{ MTLPixelFormat(40) /*B5G6R5Unorm*/,			MTLPixelFormatInvalid                        }, // R5G6B5
		{ MTLPixelFormat(42) /*ABGR4Unorm*/,			MTLPixelFormatInvalid                        }, // RGBA4
		{ MTLPixelFormat(41) /*A1BGR5Unorm*/,			MTLPixelFormatInvalid                        }, // RGB5A1
		{ MTLPixelFormatRGB10A2Unorm,					MTLPixelFormatInvalid                        }, // RGB10A2
		{ MTLPixelFormatRG11B10Float,					MTLPixelFormatInvalid                        }, // R11G11B10F
		{ MTLPixelFormatInvalid,						MTLPixelFormatInvalid                        }, // UnknownDepth
		{ MTLPixelFormatDepth32Float,					MTLPixelFormatInvalid                        }, // D16
		{ MTLPixelFormatDepth32Float,					MTLPixelFormatInvalid                        }, // D24
		{ MTLPixelFormat(255) /*Depth24Unorm_Stencil8*/,MTLPixelFormatInvalid						 }, // D24S8
		{ MTLPixelFormatDepth32Float,					MTLPixelFormatInvalid                        }, // D32
		{ MTLPixelFormatDepth32Float,					MTLPixelFormatInvalid                        }, // D16F
		{ MTLPixelFormatDepth32Float,					MTLPixelFormatInvalid                        }, // D24F
		{ MTLPixelFormatDepth32Float,					MTLPixelFormatInvalid                        }, // D32F
		{ MTLPixelFormatStencil8,						MTLPixelFormatInvalid                        }, // D0S8
	};
	BX_STATIC_ASSERT(TextureFormat::Count == BX_COUNTOF(s_textureFormat) );

	int s_msaa[5] = { 1,2,4,8,16 };

	#define SHADER_FUNCTION_NAME ("xlatMtlMain")
	#define SHADER_UNIFORM_NAME ("_mtl_u")

	struct RendererContextMtl : public RendererContextI
	{
		RendererContextMtl()
			: m_metalLayer(NULL)
			, m_backBufferPixelFormatHash(0)
			, m_maxAnisotropy(1)
			, m_bufferIndex(0)
			, m_numWindows(1)
			, m_rtMsaa(false)
			, m_capture(NULL)
			, m_captureSize(0)
			, m_drawable(NULL)
			, m_saveScreenshot(false)
		{
		}

		~RendererContextMtl()
		{
		}

		bool init()
		{
			BX_TRACE("Init.");

			m_fbh.idx = invalidHandle;
			memset(m_uniforms, 0, sizeof(m_uniforms) );
			memset(&m_resolution, 0, sizeof(m_resolution) );

			if (NULL != NSClassFromString(@"MTKView") )
			{
				MTKView *view = (MTKView *)g_platformData.nwh;
				if (NULL != view && [view isKindOfClass:NSClassFromString(@"MTKView")])
				{
					m_metalLayer = (CAMetalLayer *)view.layer;
				}
			}

			if (NULL != NSClassFromString(@"CAMetalLayer") )
			{
                if (NULL == m_metalLayer)
#if BX_PLATFORM_IOS
				{
					CAMetalLayer* metalLayer = (CAMetalLayer*)g_platformData.nwh;
					if (NULL == metalLayer
					|| ![metalLayer isKindOfClass:NSClassFromString(@"CAMetalLayer")])
					{
						BX_WARN(NULL != m_device, "Unable to create Metal device. Please set platform data window to a CAMetalLayer");
						return false;
					}

					m_metalLayer = metalLayer;
				}
#elif BX_PLATFORM_OSX
				{
					NSWindow* nsWindow = (NSWindow*)g_platformData.nwh;
					[nsWindow.contentView setWantsLayer:YES];
					m_metalLayer = [CAMetalLayer layer];
					[nsWindow.contentView setLayer:m_metalLayer];
				}
#endif // BX_PLATFORM_*

				m_device = (id<MTLDevice>)g_platformData.context;

				if (NULL == m_device)
				{
					m_device = MTLCreateSystemDefaultDevice();
				}
			}

			if (NULL == m_device
			||  NULL == m_metalLayer)
			{
				BX_WARN(NULL != m_device, "Unable to create Metal device.");
				return false;
			}

			m_metalLayer.device      = m_device;
			m_metalLayer.pixelFormat = MTLPixelFormatBGRA8Unorm;

			m_cmd.init(m_device);
			BGFX_FATAL(NULL != m_cmd.m_commandQueue, Fatal::UnableToInitialize, "Unable to create Metal device.");

			m_renderPipelineDescriptor   = newRenderPipelineDescriptor();
			m_depthStencilDescriptor     = newDepthStencilDescriptor();
			m_frontFaceStencilDescriptor = newStencilDescriptor();
			m_backFaceStencilDescriptor  = newStencilDescriptor();
			m_vertexDescriptor  = newVertexDescriptor();
			m_textureDescriptor = newTextureDescriptor();
			m_samplerDescriptor = newSamplerDescriptor();

			for (uint8_t i=0; i < MTL_MAX_FRAMES_IN_FLIGHT; ++i)
			{
				m_uniformBuffers[i] = m_device.newBufferWithLength(UNIFORM_BUFFER_SIZE, 0);
			}
			m_uniformBufferVertexOffset = 0;
			m_uniformBufferFragmentOffset = 0;

			const char* vshSource =
				"using namespace metal;\n"
				"struct xlatMtlShaderOutput { float4 gl_Position [[position]]; float2 v_texcoord0; }; \n"
				"vertex xlatMtlShaderOutput xlatMtlMain (uint v_id [[ vertex_id ]]) \n"
				"{\n"
				"	xlatMtlShaderOutput _mtl_o;\n"
				"   if (v_id==0) { _mtl_o.gl_Position = float4(-1.0,-1.0,0.0,1.0); _mtl_o.v_texcoord0 = float2(0.0,1.0); } \n"
				"   else if (v_id==1) { _mtl_o.gl_Position = float4(3.0,-1.0,0.0,1.0); _mtl_o.v_texcoord0 = float2(2.0,1.0); } \n"
				"   else { _mtl_o.gl_Position = float4(-1.0,3.0,0.0,1.0); _mtl_o.v_texcoord0 = float2(0.0,-1.0); }\n"
				"   return _mtl_o;\n"
				"}\n";

			 const char* fshSource = "using namespace metal; \n"
				" struct xlatMtlShaderInput { float2 v_texcoord0; }; \n"
				" fragment half4 xlatMtlMain (xlatMtlShaderInput _mtl_i[[stage_in]], texture2d<float> s_texColor [[texture(0)]], sampler _mtlsmp_s_texColor [[sampler(0)]] ) \n"
				" {	 return half4(s_texColor.sample(_mtlsmp_s_texColor, _mtl_i.v_texcoord0)); } \n";

			Library lib = m_device.newLibraryWithSource(vshSource);
			if (NULL != lib)
			{
				m_screenshotBlitProgramVsh.m_function = lib.newFunctionWithName(SHADER_FUNCTION_NAME);
			}
			lib = m_device.newLibraryWithSource(fshSource);
			if (NULL != lib)
			{
				m_screenshotBlitProgramFsh.m_function = lib.newFunctionWithName(SHADER_FUNCTION_NAME);
			}
			m_screenshotBlitProgram.create(&m_screenshotBlitProgramVsh, &m_screenshotBlitProgramFsh);

			reset(m_renderPipelineDescriptor);
			m_renderPipelineDescriptor.colorAttachments[0].pixelFormat = m_metalLayer.pixelFormat;
			m_renderPipelineDescriptor.vertexFunction = m_screenshotBlitProgram.m_vsh->m_function;
			m_renderPipelineDescriptor.fragmentFunction = m_screenshotBlitProgram.m_fsh->m_function;
			m_screenshotBlitRenderPipelineState = m_device.newRenderPipelineStateWithDescriptor(m_renderPipelineDescriptor);

			g_caps.supported |= (0
				| BGFX_CAPS_TEXTURE_COMPARE_LEQUAL	//NOTE: on IOS Gpu Family 1/2 have to set compare in shader
				| BGFX_CAPS_TEXTURE_COMPARE_ALL
				| BGFX_CAPS_TEXTURE_3D
				| BGFX_CAPS_VERTEX_ATTRIB_HALF
				| BGFX_CAPS_VERTEX_ATTRIB_UINT10
				| BGFX_CAPS_INSTANCING
				| BGFX_CAPS_FRAGMENT_DEPTH
				| BGFX_CAPS_BLEND_INDEPENDENT
//				| BGFX_CAPS_COMPUTE // TODO: api/hw supports it but metal compute shaders are not yet supported
				| BGFX_CAPS_INDEX32
//				| BGFX_CAPS_DRAW_INDIRECT // TODO: support on iOS9+gpu family3+ and on macOS
				| BGFX_CAPS_TEXTURE_BLIT
				| BGFX_CAPS_TEXTURE_READ_BACK
				| BGFX_CAPS_OCCLUSION_QUERY
				| BGFX_CAPS_ALPHA_TO_COVERAGE
				| BGFX_CAPS_TEXTURE_2D_ARRAY // supported on all platforms
				);

			if (BX_ENABLED(BX_PLATFORM_IOS) )
			{
				if (iOSVersionEqualOrGreater("9.0.0") )
				{
					g_caps.limits.maxTextureSize = m_device.supportsFeatureSet((MTLFeatureSet)4 /* iOS_GPUFamily3_v1 */) ? 16384 : 8192;
				}
				else
				{
					g_caps.limits.maxTextureSize = 4096;
				}

				g_caps.limits.maxFBAttachments = uint8_t(bx::uint32_min(m_device.supportsFeatureSet((MTLFeatureSet)1 /* MTLFeatureSet_iOS_GPUFamily2_v1 */) ? 8 : 4, BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS));
			}
			else if (BX_ENABLED(BX_PLATFORM_OSX) )
			{
				g_caps.limits.maxTextureSize   = 16384;
				g_caps.limits.maxFBAttachments = 8;
				g_caps.supported |= BGFX_CAPS_TEXTURE_CUBE_ARRAY;
			}

			//todo: vendor id, device id, gpu enum

			m_hasPixelFormatDepth32Float_Stencil8 =	false
				||  BX_ENABLED(BX_PLATFORM_OSX)
				|| (BX_ENABLED(BX_PLATFORM_IOS) && iOSVersionEqualOrGreater("9.0.0") )
				;
			m_macOS11Runtime = true
				&& BX_ENABLED(BX_PLATFORM_OSX)
				&& macOSVersionEqualOrGreater(10,11,0)
				;
			m_iOS9Runtime = true
				&& BX_ENABLED(BX_PLATFORM_IOS)
				&& iOSVersionEqualOrGreater("9.0.0")
				;

			if (BX_ENABLED(BX_PLATFORM_OSX) )
			{
				s_textureFormat[TextureFormat::R8].m_fmtSrgb = MTLPixelFormatInvalid;
				s_textureFormat[TextureFormat::RG8].m_fmtSrgb = MTLPixelFormatInvalid;
			}

			for (uint32_t ii = 0; ii < TextureFormat::Count; ++ii)
			{
				uint16_t support = 0;

				support |= MTLPixelFormatInvalid != s_textureFormat[ii].m_fmt
					? BGFX_CAPS_FORMAT_TEXTURE_2D
					| BGFX_CAPS_FORMAT_TEXTURE_3D
					| BGFX_CAPS_FORMAT_TEXTURE_CUBE
					| BGFX_CAPS_FORMAT_TEXTURE_VERTEX
					: BGFX_CAPS_FORMAT_TEXTURE_NONE
					;

				support |= MTLPixelFormatInvalid != s_textureFormat[ii].m_fmtSrgb
					? BGFX_CAPS_FORMAT_TEXTURE_2D_SRGB
					| BGFX_CAPS_FORMAT_TEXTURE_3D_SRGB
					| BGFX_CAPS_FORMAT_TEXTURE_CUBE_SRGB
					| BGFX_CAPS_FORMAT_TEXTURE_VERTEX
					: BGFX_CAPS_FORMAT_TEXTURE_NONE
					;

				if (!isCompressed((TextureFormat::Enum)(ii)))
				{
					support |= BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER
						| BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA;
				}

					//TODO: additional caps flags
//				support |= BGFX_CAPS_FORMAT_TEXTURE_IMAGE : BGFX_CAPS_FORMAT_TEXTURE_NONE;

				g_caps.formats[ii] = support;
			}

			g_caps.formats[TextureFormat::A8] &= ~(BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER | BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA);
			g_caps.formats[TextureFormat::RG32I] &= ~(BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA);
			g_caps.formats[TextureFormat::RG32U] &= ~(BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA);
			g_caps.formats[TextureFormat::RGBA32I] &= ~(BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA);
			g_caps.formats[TextureFormat::RGBA32U] &= ~(BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA);


			if (BX_ENABLED(BX_PLATFORM_IOS) )
			{
				s_textureFormat[TextureFormat::D24S8].m_fmt = MTLPixelFormatDepth32Float;

				g_caps.formats[TextureFormat::BC1] =
				g_caps.formats[TextureFormat::BC2] =
				g_caps.formats[TextureFormat::BC3] =
				g_caps.formats[TextureFormat::BC4] =
				g_caps.formats[TextureFormat::BC5] =
				g_caps.formats[TextureFormat::BC6H] =
				g_caps.formats[TextureFormat::BC7] = BGFX_CAPS_FORMAT_TEXTURE_NONE;

				g_caps.formats[TextureFormat::RG32F] &= ~(BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA);
				g_caps.formats[TextureFormat::RGBA32F] &= ~(BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA);
			}

			if (BX_ENABLED(BX_PLATFORM_OSX) )
			{
				s_textureFormat[TextureFormat::D24S8].m_fmt = (MTLPixelFormat)(m_device.depth24Stencil8PixelFormatSupported() ?
									255 /* Depth24Unorm_Stencil8 */ :
									MTLPixelFormatDepth32Float_Stencil8);

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
			}

			for (uint32_t ii = 0; ii < TextureFormat::Count; ++ii)
			{
				if (BGFX_CAPS_FORMAT_TEXTURE_NONE == g_caps.formats[ii])
				{
					s_textureFormat[ii].m_fmt     = MTLPixelFormatInvalid;
					s_textureFormat[ii].m_fmtSrgb = MTLPixelFormatInvalid;
				}
			}

			for(uint32_t ii=1; ii<5; ++ii)
			{
				if (!m_device.supportsTextureSampleCount(s_msaa[ii]))
				{
					s_msaa[ii] = s_msaa[ii-1];
				}
			}


			// Init reserved part of view name.
			for (uint32_t ii = 0; ii < BGFX_CONFIG_MAX_VIEWS; ++ii)
			{
				bx::snprintf(s_viewName[ii], BGFX_CONFIG_MAX_VIEW_NAME_RESERVED+1, "%3d   ", ii);
			}

			m_occlusionQuery.preReset();
			m_gpuTimer.init();

			g_internalData.context = m_device;
			return true;
		}

		void shutdown()
		{
			m_occlusionQuery.postReset();
			m_gpuTimer.shutdown();

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_shaders); ++ii)
			{
				m_shaders[ii].destroy();
			}

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_textures); ++ii)
			{
				m_textures[ii].destroy();
			}

			captureFinish();

			MTL_RELEASE(m_depthStencilDescriptor);
			MTL_RELEASE(m_frontFaceStencilDescriptor);
			MTL_RELEASE(m_backFaceStencilDescriptor);
			MTL_RELEASE(m_renderPipelineDescriptor);
			MTL_RELEASE(m_vertexDescriptor);
			MTL_RELEASE(m_textureDescriptor);
			MTL_RELEASE(m_samplerDescriptor);

			MTL_RELEASE(m_backBufferDepth);
			if (BX_ENABLED(BX_PLATFORM_IOS) )
			{
				MTL_RELEASE(m_backBufferStencil);
			}

			for (uint8_t i=0; i < MTL_MAX_FRAMES_IN_FLIGHT; ++i)
			{
				MTL_RELEASE(m_uniformBuffers[i]);
			}
			m_cmd.shutdown();
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

		void readTexture(TextureHandle _handle, void* _data, uint8_t _mip) BX_OVERRIDE
		{
			m_cmd.kick(false, true);
			m_commandBuffer = m_cmd.alloc();

			const TextureMtl& texture = m_textures[_handle.idx];

			BX_CHECK(_mip<texture.m_numMips,"Invalid mip: %d num mips:",_mip,texture.m_numMips);

			uint32_t srcWidth  = bx::uint32_max(1, texture.m_ptr.width()  >> _mip);
			uint32_t srcHeight = bx::uint32_max(1, texture.m_ptr.height() >> _mip);
			const uint8_t bpp = getBitsPerPixel(TextureFormat::Enum(texture.m_textureFormat) );

			MTLRegion region = { { 0, 0, 0 }, { srcWidth, srcHeight, 1 } };

			texture.m_ptr.getBytes(_data, srcWidth*bpp/8, 0, region, _mip, 0);

		}

		void resizeTexture(TextureHandle _handle, uint16_t _width, uint16_t _height, uint8_t _numMips) BX_OVERRIDE
		{
			TextureMtl& texture = m_textures[_handle.idx];

			uint32_t size = sizeof(uint32_t) + sizeof(TextureCreate);
			const Memory* mem = alloc(size);

			bx::StaticMemoryBlockWriter writer(mem->data, mem->size);
			uint32_t magic = BGFX_CHUNK_MAGIC_TEX;
			bx::write(&writer, magic);

			TextureCreate tc;
			tc.m_width     = _width;
			tc.m_height    = _height;
			tc.m_depth     = 0;
			tc.m_numLayers = 1;
			tc.m_numMips   = _numMips;
			tc.m_format    = TextureFormat::Enum(texture.m_requestedFormat);
			tc.m_cubeMap   = false;
			tc.m_mem       = NULL;
			bx::write(&writer, tc);

			texture.destroy();
			texture.create(mem, texture.m_flags, 0);

			release(mem);
		}

		void overrideInternal(TextureHandle _handle, uintptr_t _ptr) BX_OVERRIDE
		{
			BX_UNUSED(_handle, _ptr);
		}

		uintptr_t getInternal(TextureHandle _handle) BX_OVERRIDE
		{
			BX_UNUSED(_handle);
			return 0;
		}

		void destroyTexture(TextureHandle _handle) BX_OVERRIDE
		{
			m_textures[_handle.idx].destroy();
		}

		void createFrameBuffer(FrameBufferHandle _handle, uint8_t _num, const Attachment* _attachment) BX_OVERRIDE
		{
			m_frameBuffers[_handle.idx].create(_num, _attachment);
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
			m_uniformReg.remove(_handle);
		}

		//cmdPre
		void saveScreenShotPre(const char* _filePath) BX_OVERRIDE
		{
			BX_UNUSED(_filePath);
			m_saveScreenshot = true;
		}

		//cmdPost
		void saveScreenShot(const char* _filePath) BX_OVERRIDE
		{
			if (NULL == m_screenshotTarget)
				return;

			m_cmd.kick(false, true);
			m_commandBuffer = 0;

			uint32_t width  = m_screenshotTarget.width();
			uint32_t height = m_screenshotTarget.height();
			uint32_t length = width*height*4;
			uint8_t* data = (uint8_t*)BX_ALLOC(g_allocator, length);

			MTLRegion region = { { 0, 0, 0 }, { width, height, 1 } };

			m_screenshotTarget.getBytes(data, 4*width, 0, region, 0, 0);

			g_callback->screenShot(_filePath
					, m_screenshotTarget.width()
					, m_screenshotTarget.height()
					, width*4
					, data
					, length
					, false
					);

			BX_FREE(g_allocator, data);

			m_commandBuffer = m_cmd.alloc();
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

			uint32_t width  = m_resolution.m_width;
			uint32_t height  = m_resolution.m_height;

			//if (m_ovr.isEnabled() )
			//{
			//	m_ovr.getSize(width, height);
			//}

			FrameBufferHandle fbh = BGFX_INVALID_HANDLE;

			if ( NULL == rce || m_renderCommandEncoderFrameBufferHandle.idx != invalidHandle )
			{
				if ( m_renderCommandEncoder )
					m_renderCommandEncoder.endEncoding();

				RenderPassDescriptor renderPassDescriptor = newRenderPassDescriptor();

				setFrameBuffer(renderPassDescriptor, fbh);

				renderPassDescriptor.colorAttachments[0].loadAction = MTLLoadActionLoad;
				renderPassDescriptor.colorAttachments[0].storeAction = NULL != renderPassDescriptor.colorAttachments[0].resolveTexture ?
					MTLStoreActionMultisampleResolve : MTLStoreActionStore;

				rce = m_commandBuffer.renderCommandEncoderWithDescriptor(renderPassDescriptor);
				m_renderCommandEncoder = rce;
				m_renderCommandEncoderFrameBufferHandle = fbh;
				MTL_RELEASE(renderPassDescriptor);
			}

			MTLViewport viewport = { 0.0f, 0.0f, (float)width, (float)height, 0.0f, 1.0f};
			rce.setViewport(viewport);
			MTLScissorRect rc = { 0,0,width,height };
			rce.setScissorRect(rc);
			rce.setCullMode(MTLCullModeNone);

			uint64_t state = 0
				| BGFX_STATE_RGB_WRITE
				| BGFX_STATE_ALPHA_WRITE
				| BGFX_STATE_DEPTH_TEST_ALWAYS
				;

			setDepthStencilState(state);

			ProgramMtl& program = m_program[_blitter.m_program.idx];
			RenderPipelineState pipelineState = program.getRenderPipelineState(state, 0, fbh, _blitter.m_vb->decl, 0);
			rce.setRenderPipelineState(pipelineState);

			uint32_t vertexUniformBufferSize = program.m_vshConstantBufferSize;
			uint32_t fragmentUniformBufferSize = program.m_fshConstantBufferSize;

			if (vertexUniformBufferSize )
			{
				m_uniformBufferVertexOffset = BX_ALIGN_MASK(m_uniformBufferVertexOffset, program.m_vshConstantBufferAlignmentMask);
				rce.setVertexBuffer(m_uniformBuffer, m_uniformBufferVertexOffset, 0);
			}

			m_uniformBufferFragmentOffset = m_uniformBufferVertexOffset + vertexUniformBufferSize;
			if (fragmentUniformBufferSize )
			{
				m_uniformBufferFragmentOffset = BX_ALIGN_MASK(m_uniformBufferFragmentOffset, program.m_fshConstantBufferAlignmentMask);
				rce.setFragmentBuffer(m_uniformBuffer, m_uniformBufferFragmentOffset, 0);
			}

			float proj[16];
			bx::mtxOrtho(proj, 0.0f, (float)width, (float)height, 0.0f, 0.0f, 1000.0f);

			PredefinedUniform& predefined = program.m_predefined[0];
			uint8_t flags = predefined.m_type;
			setShaderUniform(flags, predefined.m_loc, proj, 4);

			m_textures[_blitter.m_texture.idx].commit(0, false, true);
		}

		void blitRender(TextVideoMemBlitter& _blitter, uint32_t _numIndices) BX_OVERRIDE
		{
			const uint32_t numVertices = _numIndices*4/6;
			if (0 < numVertices)
			{
				m_indexBuffers [_blitter.m_ib->handle.idx].update(0, _numIndices*2, _blitter.m_ib->data, true);
				m_vertexBuffers[_blitter.m_vb->handle.idx].update(0, numVertices*_blitter.m_decl.m_stride, _blitter.m_vb->data, true);

				VertexBufferMtl& vb = m_vertexBuffers[_blitter.m_vb->handle.idx];
				m_renderCommandEncoder.setVertexBuffer(vb.getBuffer(), 0, 1);

				m_renderCommandEncoder.drawIndexedPrimitives(MTLPrimitiveTypeTriangle, _numIndices, MTLIndexTypeUInt16, m_indexBuffers[_blitter.m_ib->handle.idx].getBuffer(), 0, 1);
			}
		}

		void flip(HMD& /*_hmd*/) BX_OVERRIDE
		{
			if (NULL == m_commandBuffer)
			{
				return;
			}

			// Present and commit the command buffer
			if ( NULL != m_drawable)
			{
				m_commandBuffer.presentDrawable(m_drawable);
				MTL_RELEASE(m_drawable);
			}

			m_cmd.kick(true);
			m_commandBuffer = 0;

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
			m_maxAnisotropy = !!(_resolution.m_flags & BGFX_RESET_MAXANISOTROPY)
				? 16
				: 1
				;

			//TODO: there should be a way to specify if backbuffer needs stencil/depth.
			const uint32_t maskFlags = ~(0
										 | BGFX_RESET_HMD_RECENTER
										 | BGFX_RESET_MAXANISOTROPY
										 | BGFX_RESET_DEPTH_CLAMP
										 | BGFX_RESET_SUSPEND
										 );

			if (m_resolution.m_width				!=  _resolution.m_width
				||  m_resolution.m_height           !=  _resolution.m_height
				|| (m_resolution.m_flags&maskFlags) != (_resolution.m_flags&maskFlags) )
			{
				int sampleCount = s_msaa[(_resolution.m_flags&BGFX_RESET_MSAA_MASK)>>BGFX_RESET_MSAA_SHIFT];

				MTLPixelFormat prevMetalLayerPixelFormat = m_metalLayer.pixelFormat;

				m_metalLayer.drawableSize = CGSizeMake(_resolution.m_width, _resolution.m_height);
				m_metalLayer.pixelFormat = (m_resolution.m_flags & BGFX_RESET_SRGB_BACKBUFFER)
								? MTLPixelFormatBGRA8Unorm_sRGB
								: MTLPixelFormatBGRA8Unorm
								;

				m_resolution = _resolution;
				m_resolution.m_flags &= ~BGFX_RESET_INTERNAL_FORCE;

				m_textureDescriptor.textureType = sampleCount > 1 ? MTLTextureType2DMultisample : MTLTextureType2D;

				if (m_hasPixelFormatDepth32Float_Stencil8)
					m_textureDescriptor.pixelFormat = MTLPixelFormatDepth32Float_Stencil8;
				else
					m_textureDescriptor.pixelFormat = MTLPixelFormatDepth32Float;

				m_textureDescriptor.width  = _resolution.m_width;
				m_textureDescriptor.height = _resolution.m_height;
				m_textureDescriptor.depth  = 1;
				m_textureDescriptor.mipmapLevelCount = 1;
				m_textureDescriptor.sampleCount = sampleCount;
				m_textureDescriptor.arrayLength = 1;
				if ( m_iOS9Runtime || m_macOS11Runtime )
				{
					m_textureDescriptor.cpuCacheMode = MTLCPUCacheModeDefaultCache;
					m_textureDescriptor.storageMode  = MTLStorageModePrivate;
					m_textureDescriptor.usage		 = MTLTextureUsageRenderTarget;
				}

				if (NULL != m_backBufferDepth)
				{
					release(m_backBufferDepth);
				}
				m_backBufferDepth   = m_device.newTextureWithDescriptor(m_textureDescriptor);


				if (m_hasPixelFormatDepth32Float_Stencil8)
					m_backBufferStencil = m_backBufferDepth;
				else
				{
					m_textureDescriptor.pixelFormat = MTLPixelFormatStencil8;
					m_backBufferStencil   = m_device.newTextureWithDescriptor(m_textureDescriptor);
				}

				if ( sampleCount > 1 )
				{
					if (NULL != m_backBufferColorMSAA)
					{
						release(m_backBufferColorMSAA);
					}
					m_textureDescriptor.pixelFormat = m_metalLayer.pixelFormat;
					m_backBufferColorMSAA   = m_device.newTextureWithDescriptor(m_textureDescriptor);
				}

				bx::HashMurmur2A murmur;
				murmur.begin();
				murmur.add(1);
				murmur.add((uint32_t)m_metalLayer.pixelFormat);
				murmur.add((uint32_t)m_backBufferDepth.pixelFormat());
				murmur.add((uint32_t)m_backBufferStencil.pixelFormat());
				murmur.add((uint32_t)sampleCount);
				m_backBufferPixelFormatHash = murmur.end();

				for (uint32_t ii = 0; ii < BX_COUNTOF(m_frameBuffers); ++ii)
				{
					m_frameBuffers[ii].postReset();
				}

				updateCapture();

				m_textVideoMem.resize(false, _resolution.m_width, _resolution.m_height);
				m_textVideoMem.clear();

				if ( prevMetalLayerPixelFormat != m_metalLayer.pixelFormat)
				{
					MTL_RELEASE(m_screenshotBlitRenderPipelineState)
					reset(m_renderPipelineDescriptor);
					m_renderPipelineDescriptor.colorAttachments[0].pixelFormat = m_metalLayer.pixelFormat;
					m_renderPipelineDescriptor.vertexFunction = m_screenshotBlitProgram.m_vsh->m_function;
					m_renderPipelineDescriptor.fragmentFunction = m_screenshotBlitProgram.m_fsh->m_function;
					m_screenshotBlitRenderPipelineState = m_device.newRenderPipelineStateWithDescriptor(m_renderPipelineDescriptor);
				}
			}
		}


		void updateCapture()
		{
			if (m_resolution.m_flags&BGFX_RESET_CAPTURE)
			{
				m_captureSize = m_resolution.m_width*m_resolution.m_height*4;
				m_capture = BX_REALLOC(g_allocator, m_capture, m_captureSize);
				g_callback->captureBegin(m_resolution.m_width, m_resolution.m_height, m_resolution.m_width*4, TextureFormat::BGRA8, false);
			}
			else
			{
				captureFinish();
			}
		}

		void capture()
		{
			if (NULL != m_capture)
			{
				if (NULL == m_screenshotTarget)
				{
					return;
				}

				m_renderCommandEncoder.endEncoding();

				m_cmd.kick(false, true);
				m_commandBuffer = 0;

				MTLRegion region = { { 0, 0, 0 }, { m_resolution.m_width, m_resolution.m_height, 1 } };

				//TODO: enable screenshot target when capturing
				m_screenshotTarget.getBytes(m_capture, 4*m_resolution.m_width, 0, region, 0, 0);

				m_commandBuffer = m_cmd.alloc();

				if (m_screenshotTarget.pixelFormat() == MTLPixelFormatRGBA8Uint)
				{
					imageSwizzleBgra8(
						  m_capture
						, m_resolution.m_width
						, m_resolution.m_height
						, m_resolution.m_width*4
						, m_capture
						);
				}

				g_callback->captureFrame(m_capture, m_captureSize);

				RenderPassDescriptor renderPassDescriptor = newRenderPassDescriptor();
				setFrameBuffer(renderPassDescriptor, m_renderCommandEncoderFrameBufferHandle);

				for (uint32_t ii = 0; ii < g_caps.limits.maxFBAttachments; ++ii)
				{
					MTLRenderPassColorAttachmentDescriptor* desc = renderPassDescriptor.colorAttachments[ii];
					if (NULL != desc.texture)
					{
						desc.loadAction = MTLLoadActionLoad;
					}
				}

				RenderPassDepthAttachmentDescriptor depthAttachment = renderPassDescriptor.depthAttachment;
				if (NULL != depthAttachment.texture)
				{
					depthAttachment.loadAction = MTLLoadActionLoad;
					depthAttachment.storeAction = MTLStoreActionStore;
				}

				RenderPassStencilAttachmentDescriptor stencilAttachment = renderPassDescriptor.stencilAttachment;
				if (NULL != stencilAttachment.texture)
				{
					stencilAttachment.loadAction   = MTLLoadActionLoad;
					stencilAttachment.storeAction  = MTLStoreActionStore;
				}

				m_renderCommandEncoder = m_commandBuffer.renderCommandEncoderWithDescriptor(renderPassDescriptor);
				MTL_RELEASE(renderPassDescriptor);
			}
		}

		void captureFinish()
		{
			if (NULL != m_capture)
			{
				g_callback->captureEnd();
				BX_FREE(g_allocator, m_capture);
				m_capture = NULL;
				m_captureSize = 0;
			}
		}


		void setShaderUniform(uint8_t _flags, uint32_t _loc, const void* _val, uint32_t _numRegs)
		{
			uint32_t offset = 0 != (_flags&BGFX_UNIFORM_FRAGMENTBIT)
				? m_uniformBufferFragmentOffset
				: m_uniformBufferVertexOffset
				;
			uint8_t* dst = (uint8_t*)m_uniformBuffer.contents();
			memcpy(&dst[offset + _loc], _val, _numRegs*16);
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
					memcpy(&handle, _uniformBuffer.read(sizeof(UniformHandle) ), sizeof(UniformHandle) );
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
				case UniformType::Mat3|BGFX_UNIFORM_FRAGMENTBIT:
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
					BX_TRACE("%4d: INVALID 0x%08x, t %d, l %d, n %d, c %d", _uniformBuffer.getPos(), opcode, type, loc, num, copy);
					break;
				}

#undef CASE_IMPLEMENT_UNIFORM

			}
		}

		void clearQuad(ClearQuad& _clearQuad, const Rect& /*_rect*/, const Clear& _clear, const float _palette[][4])
		{
			uint32_t width;
			uint32_t height;

			if (isValid(m_fbh) )
			{
				const FrameBufferMtl& fb = m_frameBuffers[m_fbh.idx];
				width  = fb.m_width;
				height = fb.m_height;
			}
			else
			{
				width  = m_resolution.m_width;
				height = m_resolution.m_height;
			}


			uint64_t state = 0;
			state |= _clear.m_flags & BGFX_CLEAR_COLOR ? BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE : 0;
			state |= _clear.m_flags & BGFX_CLEAR_DEPTH ? BGFX_STATE_DEPTH_TEST_ALWAYS|BGFX_STATE_DEPTH_WRITE : 0;

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

			setDepthStencilState(state, stencil);

			uint32_t numMrt = 1;
			FrameBufferHandle fbh = m_fbh;
			if (isValid(fbh) )
			{
				const FrameBufferMtl& fb = m_frameBuffers[fbh.idx];
				numMrt = bx::uint32_max(1, fb.m_num);
			}

			ProgramMtl& program = m_program[_clearQuad.m_program[numMrt-1].idx];
			m_renderCommandEncoder.setRenderPipelineState(program.getRenderPipelineState(state, 0, fbh, _clearQuad.m_vb->decl, 0));

			uint32_t fragmentUniformBufferSize = program.m_fshConstantBufferSize;

			m_uniformBufferFragmentOffset = m_uniformBufferVertexOffset;
			if (fragmentUniformBufferSize)
			{
				m_uniformBufferFragmentOffset = BX_ALIGN_MASK(m_uniformBufferFragmentOffset, program.m_fshConstantBufferAlignmentMask);
				m_renderCommandEncoder.setFragmentBuffer(m_uniformBuffer, m_uniformBufferFragmentOffset, 0);
			}

			if (BGFX_CLEAR_COLOR_USE_PALETTE & _clear.m_flags)
			{
				float mrtClear[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS][4];
				for (uint32_t ii = 0; ii < numMrt; ++ii)
				{
					uint8_t index = (uint8_t)bx::uint32_min(BGFX_CONFIG_MAX_COLOR_PALETTE-1, _clear.m_index[ii]);
					memcpy(mrtClear[ii], _palette[index], 16);
				}

				memcpy((uint8_t*)m_uniformBuffer.contents() + m_uniformBufferFragmentOffset,
					   mrtClear,
					   bx::uint32_min(fragmentUniformBufferSize, sizeof(mrtClear)));
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

				memcpy((uint8_t*)m_uniformBuffer.contents() + m_uniformBufferFragmentOffset,
					   rgba,
					   bx::uint32_min(fragmentUniformBufferSize, sizeof(rgba)));
			}

			m_uniformBufferFragmentOffset += fragmentUniformBufferSize;
			m_uniformBufferVertexOffset = m_uniformBufferFragmentOffset;

			const VertexBufferMtl& vb = m_vertexBuffers[_clearQuad.m_vb->handle.idx];
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
				BX_CHECK(stride == sizeof(Vertex)
					, "Stride/Vertex mismatch (stride %d, sizeof(Vertex) %d)"
					, stride
					, sizeof(Vertex)
					);
				BX_UNUSED(stride);

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
			m_renderCommandEncoder.setCullMode(MTLCullModeNone);
			m_renderCommandEncoder.setVertexBuffer(vb.getBuffer(), offset, 1);
			m_renderCommandEncoder.drawPrimitives(MTLPrimitiveTypeTriangleStrip, 0, 4, 1);
		}

		void setFrameBuffer(RenderPassDescriptor renderPassDescriptor, FrameBufferHandle _fbh, bool _msaa = true)
		{
			if (!isValid(_fbh) )
			{
				if ( NULL != m_backBufferColorMSAA )
				{
					renderPassDescriptor.colorAttachments[0].texture = m_backBufferColorMSAA;
					renderPassDescriptor.colorAttachments[0].resolveTexture = ((NULL != m_screenshotTarget) ?
																			   m_screenshotTarget.m_obj :
																			   currentDrawable().texture);
				}
				else
				{
					renderPassDescriptor.colorAttachments[0].texture = ((NULL != m_screenshotTarget) ?
																		m_screenshotTarget.m_obj :
																		currentDrawable().texture);
				}
				renderPassDescriptor.depthAttachment.texture = m_backBufferDepth;
				renderPassDescriptor.stencilAttachment.texture = m_backBufferStencil;
			}
			else
			{
				FrameBufferMtl& frameBuffer = m_frameBuffers[_fbh.idx];

				for (uint32_t ii = 0; ii < frameBuffer.m_num; ++ii)
				{
					const TextureMtl& texture = m_textures[frameBuffer.m_colorHandle[ii].idx];
					renderPassDescriptor.colorAttachments[ii].texture = texture.m_ptrMSAA ? texture.m_ptrMSAA : texture.m_ptr;
					renderPassDescriptor.colorAttachments[ii].resolveTexture = texture.m_ptrMSAA ? texture.m_ptr.m_obj : NULL;
				}

				if (isValid(frameBuffer.m_depthHandle) )
				{
					const TextureMtl& texture = m_textures[frameBuffer.m_depthHandle.idx];
					renderPassDescriptor.depthAttachment.texture = texture.m_ptrMSAA ? texture.m_ptrMSAA : texture.m_ptr;
					renderPassDescriptor.stencilAttachment.texture = texture.m_ptrStencil;

					if ( texture.m_textureFormat == TextureFormat::D24S8)//TODO: msaa and stencil iOS8 hack
					{
						if ( texture.m_ptr.pixelFormat() == 255 /* Depth24Unorm_Stencil8 */||
							 texture.m_ptr.pixelFormat() == 260 /* Depth32Float_Stencil8 */ )
						{
							renderPassDescriptor.stencilAttachment.texture = renderPassDescriptor.depthAttachment.texture;
						}
						else
							renderPassDescriptor.stencilAttachment.texture = texture.m_ptrMSAA ? texture.m_ptrMSAA : texture.m_ptrStencil;
					}
				}
			}

			m_fbh    = _fbh;
			m_rtMsaa = _msaa;
		}

		void setDepthStencilState(uint64_t _state, uint64_t _stencil = 0)
		{
			_state &= BGFX_STATE_DEPTH_WRITE|BGFX_STATE_DEPTH_TEST_MASK;

			uint32_t fstencil = unpackStencil(0, _stencil);
			uint32_t ref      = (fstencil&BGFX_STENCIL_FUNC_REF_MASK)>>BGFX_STENCIL_FUNC_REF_SHIFT;

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

				if (0 != _stencil)
				{
					StencilDescriptor frontFaceDesc = m_frontFaceStencilDescriptor;
					StencilDescriptor backfaceDesc = m_backFaceStencilDescriptor;

					uint32_t readMask  = (fstencil&BGFX_STENCIL_FUNC_RMASK_MASK)>>BGFX_STENCIL_FUNC_RMASK_SHIFT;
					uint32_t writeMask = 0xff;

					frontFaceDesc.stencilFailureOperation   = s_stencilOp[(fstencil&BGFX_STENCIL_OP_FAIL_S_MASK)>>BGFX_STENCIL_OP_FAIL_S_SHIFT];
					frontFaceDesc.depthFailureOperation     = s_stencilOp[(fstencil&BGFX_STENCIL_OP_FAIL_Z_MASK)>>BGFX_STENCIL_OP_FAIL_Z_SHIFT];
					frontFaceDesc.depthStencilPassOperation = s_stencilOp[(fstencil&BGFX_STENCIL_OP_PASS_Z_MASK)>>BGFX_STENCIL_OP_PASS_Z_SHIFT];
					frontFaceDesc.stencilCompareFunction    = s_cmpFunc[(fstencil&BGFX_STENCIL_TEST_MASK)>>BGFX_STENCIL_TEST_SHIFT];
					frontFaceDesc.readMask  = readMask;
					frontFaceDesc.writeMask = writeMask;

					backfaceDesc.stencilFailureOperation   = s_stencilOp[(bstencil&BGFX_STENCIL_OP_FAIL_S_MASK)>>BGFX_STENCIL_OP_FAIL_S_SHIFT];
					backfaceDesc.depthFailureOperation     = s_stencilOp[(bstencil&BGFX_STENCIL_OP_FAIL_Z_MASK)>>BGFX_STENCIL_OP_FAIL_Z_SHIFT];
					backfaceDesc.depthStencilPassOperation = s_stencilOp[(bstencil&BGFX_STENCIL_OP_PASS_Z_MASK)>>BGFX_STENCIL_OP_PASS_Z_SHIFT];
					backfaceDesc.stencilCompareFunction    = s_cmpFunc[(bstencil&BGFX_STENCIL_TEST_MASK)>>BGFX_STENCIL_TEST_SHIFT];
					backfaceDesc.readMask  = readMask;
					backfaceDesc.writeMask = writeMask;

					desc.frontFaceStencil = frontFaceDesc;
					desc.backFaceStencil = backfaceDesc;
				}
				else
				{
					desc.backFaceStencil  = NULL;
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
				m_samplerDescriptor.maxAnisotropy =  (0 != (_flags & (BGFX_TEXTURE_MIN_ANISOTROPIC|BGFX_TEXTURE_MAG_ANISOTROPIC) ) ) ? m_maxAnisotropy : 1;

				//NOTE: Comparison function can be specified in shader on all metal hw.
				if ( m_macOS11Runtime || [m_device supportsFeatureSet:(MTLFeatureSet)4/*MTLFeatureSet_iOS_GPUFamily3_v1*/])
				{
					const uint32_t cmpFunc = (_flags&BGFX_TEXTURE_COMPARE_MASK)>>BGFX_TEXTURE_COMPARE_SHIFT;
					m_samplerDescriptor.compareFunction = 0 == cmpFunc ? MTLCompareFunctionNever : s_cmpFunc[cmpFunc];
				}

				sampler = m_device.newSamplerStateWithDescriptor(m_samplerDescriptor);
				m_samplerStateCache.add(_flags, sampler);
			}

			return sampler;
		}

		bool isVisible(Frame* _render, OcclusionQueryHandle _handle, bool _visible)
		{
			m_occlusionQuery.resolve(_render);
			return _visible == (0 != _render->m_occlusion[_handle.idx]);
		}


		BlitCommandEncoder getBlitCommandEncoder()
		{
			if ( m_blitCommandEncoder == NULL)
			{
				if ( m_commandBuffer == NULL )
				{
					m_commandBuffer = m_cmd.alloc();
				}

				m_blitCommandEncoder = m_commandBuffer.blitCommandEncoder();
			}

			return m_blitCommandEncoder;
		}

		id<CAMetalDrawable> currentDrawable()
		{
			if (m_drawable == nil)
			{
				m_drawable = m_metalLayer.nextDrawable;
				retain(m_drawable); // keep alive to be useable at 'flip'
			}

			return m_drawable;
		}


		Device				m_device;
		OcclusionQueryMTL	m_occlusionQuery;
		TimerQueryMtl		m_gpuTimer;
		CommandQueueMtl		m_cmd;

		CAMetalLayer* m_metalLayer;
		Texture       m_backBufferColorMSAA;
		Texture       m_backBufferDepth;
		Texture       m_backBufferStencil;
		uint32_t      m_backBufferPixelFormatHash;
		uint32_t      m_maxAnisotropy;

		bool m_iOS9Runtime;
		bool m_macOS11Runtime;
		bool m_hasPixelFormatDepth32Float_Stencil8;

		Buffer   m_uniformBuffer;
		Buffer   m_uniformBuffers[MTL_MAX_FRAMES_IN_FLIGHT];
		uint32_t m_uniformBufferVertexOffset;
		uint32_t m_uniformBufferFragmentOffset;

		uint8_t  m_bufferIndex;

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

		Resolution m_resolution;
		void* m_capture;
		uint32_t m_captureSize;

		// descriptors
		RenderPipelineDescriptor m_renderPipelineDescriptor;
		DepthStencilDescriptor   m_depthStencilDescriptor;
		StencilDescriptor        m_frontFaceStencilDescriptor;
		StencilDescriptor        m_backFaceStencilDescriptor;
		VertexDescriptor         m_vertexDescriptor;
		TextureDescriptor        m_textureDescriptor;
		SamplerDescriptor        m_samplerDescriptor;

		// currently active objects data
		id <CAMetalDrawable>	m_drawable;
		bool					m_saveScreenshot;
		Texture					m_screenshotTarget;
		ShaderMtl				m_screenshotBlitProgramVsh;
		ShaderMtl				m_screenshotBlitProgramFsh;
		ProgramMtl				m_screenshotBlitProgram;
		RenderPipelineState		m_screenshotBlitRenderPipelineState;

		CommandBuffer			m_commandBuffer;
		CommandBuffer			m_prevCommandBuffer;
		BlitCommandEncoder		m_blitCommandEncoder;
		RenderCommandEncoder	m_renderCommandEncoder;
		FrameBufferHandle		m_renderCommandEncoderFrameBufferHandle;
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
		bx::write(_writer, _str, (int32_t)bx::strnlen(_str) );
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

		Library lib = s_renderMtl->m_device.newLibraryWithSource(code);

		if (NULL != lib)
		{
			m_function = lib.newFunctionWithName(SHADER_FUNCTION_NAME);
		}

		BGFX_FATAL(NULL != m_function
			, bgfx::Fatal::InvalidShader
			, "Failed to create %s shader."
			, BGFX_CHUNK_MAGIC_FSH == magic ? "Fragment" : BGFX_CHUNK_MAGIC_VSH == magic ? "Vertex" : "Compute"
			);
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
		if (NULL != _vsh->m_function.m_obj )
		{
			for (MTLVertexAttribute* attrib in _vsh->m_function.m_obj.vertexAttributes)
			{
				if (attrib.active )
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
		m_instanceData[instUsed] = UINT16_MAX;
	}

	void ProgramMtl::destroy()
	{
		m_vsh = NULL;
		m_fsh = NULL;

		if (NULL != m_vshConstantBuffer)
		{
			UniformBuffer::destroy(m_vshConstantBuffer);
			m_vshConstantBuffer = NULL;
		}

		if (NULL != m_fshConstantBuffer)
		{
			UniformBuffer::destroy(m_fshConstantBuffer);
			m_fshConstantBuffer = NULL;
		}

		m_vshConstantBufferSize = 0;
		m_vshConstantBufferAlignmentMask = 0;
		m_fshConstantBufferSize = 0;
		m_fshConstantBufferAlignmentMask = 0;

		m_processedUniforms = false;
		m_numPredefined = 0;

		m_renderPipelineStateCache.invalidate();
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

			default:
				break;
		};

		BX_CHECK(false, "Unrecognized Mtl Data type 0x%04x.", _type);
		return UniformType::End;
	}

	RenderPipelineState ProgramMtl::getRenderPipelineState(uint64_t _state, uint32_t _rgba, FrameBufferHandle _fbHandle, VertexDeclHandle _declHandle,  uint16_t _numInstanceData)
	{
		_state &= (BGFX_STATE_BLEND_MASK|BGFX_STATE_BLEND_EQUATION_MASK|BGFX_STATE_ALPHA_WRITE|BGFX_STATE_RGB_WRITE|BGFX_STATE_BLEND_INDEPENDENT|BGFX_STATE_MSAA|BGFX_STATE_BLEND_ALPHA_TO_COVERAGE);

		bool independentBlendEnable = !!(BGFX_STATE_BLEND_INDEPENDENT & _state);

		bx::HashMurmur2A murmur;
		murmur.begin();
		murmur.add(_state);
		murmur.add(independentBlendEnable ? _rgba : 0);
		if (!isValid(_fbHandle) )
		{
			murmur.add(s_renderMtl->m_backBufferPixelFormatHash);
		}
		else
		{
			FrameBufferMtl& frameBuffer = s_renderMtl->m_frameBuffers[_fbHandle.idx];
			murmur.add(frameBuffer.m_pixelFormatHash);
		}
		murmur.add(_declHandle.idx);
		murmur.add(_numInstanceData);
		uint32_t hash = murmur.end();

		RenderPipelineState rps = m_renderPipelineStateCache.find(hash);
		if (NULL == rps)
		{
			RenderPipelineDescriptor& pd = s_renderMtl->m_renderPipelineDescriptor;
			reset(pd);

			pd.alphaToCoverageEnabled  = !!(BGFX_STATE_BLEND_ALPHA_TO_COVERAGE & _state);

			uint32_t frameBufferAttachment = 1;

			if (!isValid(_fbHandle) )
			{
				pd.sampleCount = NULL != s_renderMtl->m_backBufferColorMSAA ? s_renderMtl->m_backBufferColorMSAA.sampleCount() : 1;
				pd.colorAttachments[0].pixelFormat = s_renderMtl->currentDrawable().texture.pixelFormat;
				pd.depthAttachmentPixelFormat      = s_renderMtl->m_backBufferDepth.m_obj.pixelFormat;
				pd.stencilAttachmentPixelFormat    = s_renderMtl->m_backBufferStencil.m_obj.pixelFormat;
			}
			else
			{
				FrameBufferMtl& frameBuffer = s_renderMtl->m_frameBuffers[_fbHandle.idx];
				frameBufferAttachment = frameBuffer.m_num;

				for (uint32_t ii = 0; ii < frameBuffer.m_num; ++ii)
				{
					const TextureMtl& texture = s_renderMtl->m_textures[frameBuffer.m_colorHandle[ii].idx];
					pd.sampleCount = NULL != texture.m_ptrMSAA ? texture.m_ptrMSAA.sampleCount() : 1;
					pd.colorAttachments[ii].pixelFormat = texture.m_ptr.m_obj.pixelFormat;
				}

				if (isValid(frameBuffer.m_depthHandle))
				{
					const TextureMtl& texture = s_renderMtl->m_textures[frameBuffer.m_depthHandle.idx];
					pd.depthAttachmentPixelFormat = texture.m_ptr.m_obj.pixelFormat;
					if (NULL != texture.m_ptrStencil)
					{
						pd.stencilAttachmentPixelFormat = texture.m_ptrStencil.m_obj.pixelFormat;
					}
					else
					{
						if ( texture.m_textureFormat == TextureFormat::D24S8)
							pd.stencilAttachmentPixelFormat = texture.m_ptr.m_obj.pixelFormat;
					}
				}
			}

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
				RenderPipelineColorAttachmentDescriptor drt = pd.colorAttachments[ii];

				drt.blendingEnabled = !!(BGFX_STATE_BLEND_MASK & _state);

				drt.sourceRGBBlendFactor        = s_blendFactor[srcRGB][0];
				drt.destinationRGBBlendFactor   = s_blendFactor[dstRGB][0];
				drt.rgbBlendOperation           = s_blendEquation[equRGB];

				drt.sourceAlphaBlendFactor      = s_blendFactor[srcA][1];
				drt.destinationAlphaBlendFactor = s_blendFactor[dstA][1];
				drt.alphaBlendOperation         = s_blendEquation[equA];

				drt.writeMask = writeMask;
			}

			if (independentBlendEnable)
			{
				for (uint32_t ii = 1, rgba = _rgba; ii < frameBufferAttachment; ++ii, rgba >>= 11)
				{
					RenderPipelineColorAttachmentDescriptor drt = pd.colorAttachments[ii];

					drt.blendingEnabled = 0 != (rgba&0x7ff);

					const uint32_t src           = (rgba   )&0xf;
					const uint32_t dst           = (rgba>>4)&0xf;
					const uint32_t equationIndex = (rgba>>8)&0x7;

					drt.sourceRGBBlendFactor      = s_blendFactor[src][0];
					drt.destinationRGBBlendFactor = s_blendFactor[dst][0];
					drt.rgbBlendOperation         = s_blendEquation[equationIndex];

					drt.sourceAlphaBlendFactor      = s_blendFactor[src][1];
					drt.destinationAlphaBlendFactor = s_blendFactor[dst][1];
					drt.alphaBlendOperation         = s_blendEquation[equationIndex];

					drt.writeMask = writeMask;
				}
			}

			pd.vertexFunction = m_vsh->m_function;
			pd.fragmentFunction = m_fsh->m_function;

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
					BX_CHECK(num <= 4, "num must be <=4");

					if (UINT16_MAX != vertexDecl.m_attributes[attr])
					{
						vertexDesc.attributes[loc].format = s_attribType[type][num-1][normalized?1:0];
						vertexDesc.attributes[loc].bufferIndex = 1;
						vertexDesc.attributes[loc].offset = vertexDecl.m_offset[attr];

						BX_TRACE("attrib:%s format: %d offset:%d", s_attribName[attr], (int)vertexDesc.attributes[loc].format, (int)vertexDesc.attributes[loc].offset);
					}
					else
					{	// NOTE: missing attribute: using dummy attribute with smallest possible size
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
					for (uint32_t ii = 0; UINT16_MAX != m_instanceData[ii]; ++ii)
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

				pd.vertexDescriptor = vertexDesc;
			}

			if (m_processedUniforms)
			{
				rps = s_renderMtl->m_device.newRenderPipelineStateWithDescriptor(pd);
			}
			else
			{
				m_numPredefined = 0;
				RenderPipelineReflection reflection = NULL;
				rps = s_renderMtl->m_device.newRenderPipelineStateWithDescriptor(pd, MTLPipelineOptionBufferTypeInfo, &reflection);

				if (NULL != reflection)
				{
					for (uint32_t shaderType = 0; shaderType < 2; ++shaderType)
					{
						UniformBuffer*& constantBuffer = (shaderType == 0 ? m_vshConstantBuffer : m_fshConstantBuffer);
						uint8_t fragmentBit = (1 == shaderType ? BGFX_UNIFORM_FRAGMENTBIT : 0);

						for (MTLArgument* arg in (shaderType == 0 ? reflection.vertexArguments : reflection.fragmentArguments))
						{
							BX_TRACE("arg: %s type:%d", utf8String(arg.name), arg.type);
							if (arg.active)
							{
								if (arg.type == MTLArgumentTypeBuffer
								&& 0 == strcmp(utf8String(arg.name), SHADER_UNIFORM_NAME) )
								{
									BX_CHECK( arg.index == 0, "Uniform buffer must be in the buffer slot 0.");
									BX_CHECK( MTLDataTypeStruct == arg.bufferDataType, "%s's type must be a struct",SHADER_UNIFORM_NAME );

									if (MTLDataTypeStruct == arg.bufferDataType)
									{
										if (shaderType == 0)
										{
											m_vshConstantBufferSize = (uint32_t)arg.bufferDataSize;
											m_vshConstantBufferAlignmentMask = (uint32_t)arg.bufferAlignment - 1;
										}
										else
										{
											m_fshConstantBufferSize = (uint32_t)arg.bufferDataSize;
											m_fshConstantBufferAlignmentMask = (uint32_t)arg.bufferAlignment - 1;
										}

										for (MTLStructMember* uniform in arg.bufferStructType.members )
										{
											const char* name = utf8String(uniform.name);
											BX_TRACE("uniform: %s type:%d", name, uniform.dataType);

											MTLDataType dataType = uniform.dataType;
											uint32_t num = 1;

											if (dataType == MTLDataTypeArray)
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
												const UniformRegInfo* info = s_renderMtl->m_uniformReg.find(name);
												BX_WARN(NULL != info, "User defined uniform '%s' is not found, it won't be set.", name);

												if (NULL != info)
												{
													if (NULL == constantBuffer)
													{
														constantBuffer = UniformBuffer::create(1024);
													}

													UniformType::Enum type = convertMtlType(dataType);
													constantBuffer->writeUniformHandle((UniformType::Enum)(type|fragmentBit), uint32_t(uniform.offset), info->m_handle, uint16_t(num) );
													BX_TRACE("store %s %d offset:%d", name, info->m_handle, uint32_t(uniform.offset));
												}
											}

										}
									}
								}
								else if (arg.type == MTLArgumentTypeTexture)
								{
									if ( shaderType == 0 ) m_usedVertexSamplerStages |= 1<<arg.index;
									else m_usedFragmentSamplerStages |= 1<<arg.index;

									BX_TRACE("texture: %s index:%d", utf8String(arg.name), arg.index);
								}
								else if (arg.type == MTLArgumentTypeSampler)
								{
									BX_TRACE("sampler: %s index:%d", utf8String(arg.name), arg.index);
								}
							}
						}

						if (NULL != constantBuffer)
						{
							constantBuffer->finish();
						}
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
		BX_UNUSED(_stride, _vertex);

		m_size = _size;
		m_flags = _flags;
		m_dynamic = (NULL == _data);

		if (NULL == _data)
		{
			for (uint32_t ii = 0; ii < MTL_MAX_FRAMES_IN_FLIGHT; ++ii)
				m_buffers[ii] = s_renderMtl->m_device.newBufferWithLength(_size, 0);
		}
		else
		{
			m_buffers[0] = s_renderMtl->m_device.newBufferWithBytes(_data, _size, 0);
		}
	}

	void BufferMtl::update(uint32_t _offset, uint32_t _size, void* _data, bool _discard)
	{
		BX_UNUSED(_discard);

			//TODO: cannot call this more than once per frame
		if ( m_dynamic && _discard )
		{
			m_bufferIndex = (m_bufferIndex + 1) % MTL_MAX_FRAMES_IN_FLIGHT;
			memcpy( (uint8_t*)getBuffer().contents() + _offset, _data, _size);
		}
		else if ( NULL != s_renderMtl->m_renderCommandEncoder )
		{
			s_renderMtl->m_cmd.release(m_buffers[m_bufferIndex]);

			if (_offset == 0 && _size == m_size)
				m_buffers[m_bufferIndex] = s_renderMtl->m_device.newBufferWithBytes(_data, _size, 0);
			else
			{
				const void* oldContent = m_buffers[m_bufferIndex].contents();
				m_buffers[m_bufferIndex] = s_renderMtl->m_device.newBufferWithBytes(oldContent, m_size, 0);
				memcpy( (uint8_t*)m_buffers[m_bufferIndex].contents() + _offset, _data, _size);
			}
		}
		else
		{
			BlitCommandEncoder bce = s_renderMtl->getBlitCommandEncoder();

			Buffer temp = s_renderMtl->m_device.newBufferWithBytes(_data, _size, 0);
			bce.copyFromBuffer(temp, 0, getBuffer(), _offset, _size);
			release(temp);
		}
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
			const uint16_t numLayers     = imageContainer.m_numLayers;

			m_flags   = _flags;
			m_width   = textureWidth;
			m_height  = textureHeight;
			m_depth   = imageContainer.m_depth;
			m_requestedFormat  = uint8_t(imageContainer.m_format);
			m_textureFormat    = uint8_t(getViableTextureFormat(imageContainer) );
			const bool convert = m_textureFormat != m_requestedFormat;
			const uint8_t bpp = getBitsPerPixel(TextureFormat::Enum(m_textureFormat) );

			TextureDescriptor desc = s_renderMtl->m_textureDescriptor;

			if (1 < numLayers)
			{
				if (imageContainer.m_cubeMap)
				{
					desc.textureType = MTLTextureType(6); // MTLTextureTypeCubeArray
					m_type = TextureCube;
				}
				else
				{
					desc.textureType = MTLTextureType2DArray;
					m_type = Texture2D;
				}

				desc.arrayLength = numLayers;
			}
			else if (imageContainer.m_cubeMap)
			{
				desc.textureType = MTLTextureTypeCube;
				m_type = TextureCube;
			}
			else if (imageContainer.m_depth > 1)
			{
				desc.textureType = MTLTextureType3D;
				m_type = Texture3D;
			}
			else
			{
				desc.textureType = MTLTextureType2D;
				m_type = Texture2D;
			}

			m_numMips = numMips;
			const uint16_t numSides = numLayers * (imageContainer.m_cubeMap ? 6 : 1);

			const bool compressed   = isCompressed(TextureFormat::Enum(m_textureFormat) );
			const bool writeOnly    = 0 != (_flags&BGFX_TEXTURE_RT_WRITE_ONLY);
			const bool computeWrite = 0 != (_flags&BGFX_TEXTURE_COMPUTE_WRITE);
			const bool renderTarget = 0 != (_flags&BGFX_TEXTURE_RT_MASK);
			const bool srgb			= 0 != (_flags&BGFX_TEXTURE_SRGB) || imageContainer.m_srgb;

			BX_TRACE("Texture %3d: %s (requested: %s), layers %d, %dx%d%s RT[%c], WO[%c], CW[%c], sRGB[%c]"
					 , this - s_renderMtl->m_textures
					 , getName( (TextureFormat::Enum)m_textureFormat)
					 , getName( (TextureFormat::Enum)m_requestedFormat)
					 , numLayers
					 , textureWidth
					 , textureHeight
					 , imageContainer.m_cubeMap ? "x6" : ""
					 , renderTarget ? 'x' : '.'
					 , writeOnly ? 'x' : '.'
					 , computeWrite ? 'x' : '.'
					 , srgb ? 'x' : '.'
					 );

			const uint32_t msaaQuality = bx::uint32_satsub( (_flags&BGFX_TEXTURE_RT_MSAA_MASK)>>BGFX_TEXTURE_RT_MSAA_SHIFT, 1);
			int sampleCount = s_msaa[msaaQuality];

			MTLPixelFormat format = MTLPixelFormatInvalid;
			if (srgb)
			{
				format = s_textureFormat[m_textureFormat].m_fmtSrgb;
				BX_WARN(format != MTLPixelFormatInvalid
					, "sRGB not supported for texture format %d"
					, m_textureFormat
					);
			}

			if (format == MTLPixelFormatInvalid)
			{
				// not swizzled and not sRGB, or sRGB unsupported
				format = s_textureFormat[m_textureFormat].m_fmt;
			}

			desc.pixelFormat = format;
			desc.width  = textureWidth;
			desc.height = textureHeight;
			desc.depth  = bx::uint32_max(1,imageContainer.m_depth);
			desc.mipmapLevelCount = imageContainer.m_numMips;
			desc.sampleCount      = 1;

			if (s_renderMtl->m_iOS9Runtime || s_renderMtl->m_macOS11Runtime)
			{
				desc.cpuCacheMode = MTLCPUCacheModeDefaultCache;

				desc.storageMode = (MTLStorageMode)(writeOnly||isDepth(TextureFormat::Enum(m_textureFormat))
													? 2 /*MTLStorageModePrivate*/
													: ((BX_ENABLED(BX_PLATFORM_IOS)) ? 0 /* MTLStorageModeShared */ :  1 /*MTLStorageModeManaged*/)
													);

				desc.usage = MTLTextureUsageShaderRead;
				if (computeWrite)
					desc.usage |= MTLTextureUsageShaderWrite;
				if (renderTarget)
					desc.usage |= MTLTextureUsageRenderTarget;
			}

			m_ptr = s_renderMtl->m_device.newTextureWithDescriptor(desc);

			if ( sampleCount > 1)
			{
				desc.textureType = MTLTextureType2DMultisample;
				desc.sampleCount = sampleCount;
				if (s_renderMtl->m_iOS9Runtime || s_renderMtl->m_macOS11Runtime)
					desc.storageMode = (MTLStorageMode)( 2 /*MTLStorageModePrivate*/);
				m_ptrMSAA = s_renderMtl->m_device.newTextureWithDescriptor(desc);
			}

			if (m_requestedFormat == TextureFormat::D24S8
			&&  desc.pixelFormat  == MTLPixelFormatDepth32Float)
			{
				desc.pixelFormat = MTLPixelFormatStencil8;
				m_ptrStencil = s_renderMtl->m_device.newTextureWithDescriptor(desc);
			}

			uint8_t* temp = NULL;
			if (convert)
			{
				temp = (uint8_t*)BX_ALLOC(g_allocator, textureWidth*textureHeight*4);
			}

			for (uint8_t side = 0; side < numSides; ++side)
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
							imageDecodeToBgra8(temp
								, mip.m_data
								, mip.m_width
								, mip.m_height
								, mip.m_width*4
								, mip.m_format
								);
							data = temp;
						}

						MTLRegion region = { { 0, 0, 0 }, { width, height, depth } };

						uint32_t bytesPerRow   = 0;
						uint32_t bytesPerImage = 0;

						if (compressed && !convert)
						{
							if (format >= 160 /*PVRTC_RGB_2BPP*/
							&&  format <= 167 /*PVRTC_RGBA_4BPP_sRGB*/)
							{
								bytesPerRow   = 0;
								bytesPerImage = 0;
							}
							else
							{
								bytesPerRow   = (mip.m_width / blockInfo.blockWidth)*mip.m_blockSize;
								bytesPerImage = desc.textureType == MTLTextureType3D
									? (mip.m_height/blockInfo.blockHeight)*bytesPerRow
									: 0
									;
							}
						}
						else
						{
							bytesPerRow   = width * bpp / 8;
							bytesPerImage = desc.textureType == MTLTextureType3D
								? bytesPerRow * height
								: 0
								;
						}

						m_ptr.replaceRegion(region, lod, side, data, bytesPerRow, bytesPerImage);
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
		const uint32_t bpp       = getBitsPerPixel(TextureFormat::Enum(m_textureFormat) );
		const uint32_t rectpitch = _rect.m_width*bpp/8;
		const uint32_t srcpitch  = UINT16_MAX == _pitch ? rectpitch : _pitch;
		const uint32_t slice = ((m_type == Texture3D) ? 0 : _side + _z * (m_type == TextureCube ? 6 : 1));
		const uint16_t z = (m_type == Texture3D) ? _z : 0 ;

		const bool convert = m_textureFormat != m_requestedFormat;

		uint8_t* data = _mem->data;
		uint8_t* temp = NULL;

		if (convert)
		{
			temp = (uint8_t*)BX_ALLOC(g_allocator, rectpitch*_rect.m_height);
			imageDecodeToBgra8(temp
				, data
				, _rect.m_width
				, _rect.m_height
				, srcpitch
				, TextureFormat::Enum(m_requestedFormat)
				);
			data = temp;
		}

		if ( NULL != s_renderMtl->m_renderCommandEncoder )
		{
			s_renderMtl->m_cmd.finish(true);

			MTLRegion region =
			{
				{ _rect.m_x,     _rect.m_y,      z     },
				{ _rect.m_width, _rect.m_height, _depth },
			};

			m_ptr.replaceRegion(region, _mip, slice, data, srcpitch, srcpitch * _rect.m_height);
		}
		else
		{
			BlitCommandEncoder bce = s_renderMtl->getBlitCommandEncoder();

			const uint32_t dstpitch = bx::strideAlign(rectpitch, 64);

			Buffer tempBuffer = s_renderMtl->m_device.newBufferWithLength(dstpitch*_rect.m_height, 0);

			const uint8_t* src = (uint8_t*)data;
			uint8_t* dst = (uint8_t*)tempBuffer.contents();

			for (uint32_t yy = 0; yy < _rect.m_height; ++yy, src += srcpitch, dst += dstpitch)
			{
				memcpy(dst, src, rectpitch);
			}

			bce.copyFromBuffer(
				  tempBuffer
				, 0
				, dstpitch
				, dstpitch * _rect.m_height
				, MTLSizeMake(_rect.m_width, _rect.m_height, _depth)
				, m_ptr
				, slice
				, _mip
				, MTLOriginMake(_rect.m_x, _rect.m_y, z)
				);
			release(tempBuffer);
		}

		if (NULL != temp)
		{
			BX_FREE(g_allocator, temp);
		}
	}

	void TextureMtl::commit(uint8_t _stage, bool _vertex, bool _fragment, uint32_t _flags)
	{
		if (_vertex)
		{
			s_renderMtl->m_renderCommandEncoder.setVertexTexture(m_ptr, _stage);
			s_renderMtl->m_renderCommandEncoder.setVertexSamplerState(
					  0 == (BGFX_TEXTURE_INTERNAL_DEFAULT_SAMPLER & _flags)
					? s_renderMtl->getSamplerState(_flags)
					: m_sampler, _stage);
		}

		if (_fragment)
		{
			s_renderMtl->m_renderCommandEncoder.setFragmentTexture(m_ptr, _stage);
			s_renderMtl->m_renderCommandEncoder.setFragmentSamplerState(
					  0 == (BGFX_TEXTURE_INTERNAL_DEFAULT_SAMPLER & _flags)
					? s_renderMtl->getSamplerState(_flags)
					: m_sampler, _stage);
		}
	}

	void FrameBufferMtl::create(uint8_t _num, const Attachment* _attachment)
	{
		m_denseIdx = UINT16_MAX;
		m_num = 0;
		m_width = 0;
		m_height = 0;
		for (uint32_t ii = 0; ii < _num; ++ii)
		{
			TextureHandle handle = _attachment[ii].handle;
			if (isValid(handle) )
			{
				const TextureMtl& texture = s_renderMtl->m_textures[handle.idx];

				if ( 0 == m_width )
				{
					m_width = texture.m_width;
					m_height = texture.m_height;
				}

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
		if (!isValid(m_depthHandle))
		{
			murmur.add((uint32_t)MTLPixelFormatInvalid);
			murmur.add((uint32_t)MTLPixelFormatInvalid);
		}
		else
		{
			const TextureMtl& depthTexture = s_renderMtl->m_textures[m_depthHandle.idx];
			murmur.add((uint32_t)depthTexture.m_ptr.pixelFormat());
			murmur.add((uint32_t)(NULL != depthTexture.m_ptrStencil ? depthTexture.m_ptrStencil.pixelFormat() : MTLPixelFormatInvalid));
		}
		murmur.add(1); //SampleCount

		m_pixelFormatHash = murmur.end();
	}

	void FrameBufferMtl::create(uint16_t _denseIdx, void* _nwh, uint32_t _width, uint32_t _height, TextureFormat::Enum _depthFormat)
	{
		BX_UNUSED(_denseIdx, _nwh, _width, _height, _depthFormat);

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

	void CommandQueueMtl::init(Device _device)
	{
		m_commandQueue = _device.newCommandQueue();
		m_framesSemaphore.post(MTL_MAX_FRAMES_IN_FLIGHT);
	}

	void CommandQueueMtl::shutdown()
	{
		MTL_RELEASE(m_commandQueue);
	}

	CommandBuffer CommandQueueMtl::alloc()
	{
		m_activeCommandBuffer = m_commandQueue.commandBuffer();
		retain(m_activeCommandBuffer);
		return m_activeCommandBuffer;
	}

	static void commandBufferFinishedCallback(void* _data)
	{
		CommandQueueMtl* queue = (CommandQueueMtl*)_data;
		if ( queue )
			queue->m_framesSemaphore.post();
	}

	void CommandQueueMtl::kick(bool _endFrame, bool _waitForFinish)
	{
		if ( m_activeCommandBuffer )
		{
			if ( _endFrame )
			{
				m_releaseWriteIndex = (m_releaseWriteIndex + 1) % MTL_MAX_FRAMES_IN_FLIGHT;
				m_activeCommandBuffer.addCompletedHandler(commandBufferFinishedCallback, this);
			}

			m_activeCommandBuffer.commit();
			if ( _waitForFinish )
				m_activeCommandBuffer.waitUntilCompleted();
			MTL_RELEASE(m_activeCommandBuffer);
		}
	}

	void CommandQueueMtl::finish(bool _finishAll)
	{
		if ( _finishAll)
		{
			int count = m_activeCommandBuffer != NULL ? 2 : 3;

			for( int i=0; i< count; ++i)
			{
				consume();
			}

			m_framesSemaphore.post(count);
		}
		else
		{
			consume();
		}
	}

	void CommandQueueMtl::release(NSObject* _ptr)
	{
		m_release[m_releaseWriteIndex].push_back(_ptr);
	}

	void CommandQueueMtl::consume()
	{
		m_framesSemaphore.wait();
		m_releaseReadIndex = (m_releaseReadIndex + 1) % MTL_MAX_FRAMES_IN_FLIGHT;

		ResourceArray& ra = m_release[m_releaseReadIndex];
		for (ResourceArray::iterator it = ra.begin(), itEnd = ra.end(); it != itEnd; ++it)
		{
			bgfx::mtl::release(*it);
		}
		ra.clear();
	}

	void TimerQueryMtl::init()
	{
		m_frequency = bx::getHPFrequency();
	}

	void TimerQueryMtl::shutdown()
	{
	}

    static void setTimestamp(void* _data)
	{
		*((int64_t*)_data) = bx::getHPCounter();
	}

	void TimerQueryMtl::addHandlers(CommandBuffer& _commandBuffer)
	{
		while (0 == m_control.reserve(1) )
		{
			m_control.consume(1);
		}

		uint32_t offset = m_control.m_current * 2 + 0;

		_commandBuffer.addScheduledHandler(setTimestamp, &m_result[offset]);
		_commandBuffer.addCompletedHandler(setTimestamp, &m_result[offset+1]);
		m_control.commit(1);
	}

	bool TimerQueryMtl::get()
	{
		if (0 != m_control.available() )
		{
			uint32_t offset = m_control.m_read * 2;
			m_begin = m_result[offset+0];
			m_end   = m_result[offset+1];
			m_elapsed = m_end - m_begin;

			m_control.consume(1);

			return true;
		}

		return false;
	}

	void OcclusionQueryMTL::postReset()
	{
		MTL_RELEASE(m_buffer);
	}

	void OcclusionQueryMTL::preReset()
	{
		m_buffer = s_renderMtl->m_device.newBufferWithLength(BX_COUNTOF(m_query) * 8, 0);
	}

	void OcclusionQueryMTL::begin(RenderCommandEncoder& _rce, Frame* _render, OcclusionQueryHandle _handle)
	{
		while (0 == m_control.reserve(1) )
		{
			resolve(_render, true);
		}

		Query& query = m_query[m_control.m_current];
		query.m_handle = _handle;
		uint32_t offset = _handle.idx * 8;
		_rce.setVisibilityResultMode(MTLVisibilityResultModeBoolean, offset);
	}

	void OcclusionQueryMTL::end(RenderCommandEncoder& _rce)
	{
		Query& query = m_query[m_control.m_current];
		uint32_t offset = query.m_handle.idx * 8;
		_rce.setVisibilityResultMode(MTLVisibilityResultModeDisabled, offset);
		m_control.commit(1);
	}

	void OcclusionQueryMTL::resolve(Frame* _render, bool _wait)
	{
		BX_UNUSED(_wait);
		while (0 != m_control.available() )
		{
			Query& query = m_query[m_control.m_read];

			uint64_t result = ( (uint64_t*)m_buffer.contents() )[query.m_handle.idx];
			_render->m_occlusion[query.m_handle.idx] = 0 < result;
			m_control.consume(1);
		}
	}

	void RendererContextMtl::submit(Frame* _render, ClearQuad& _clearQuad, TextVideoMemBlitter& _textVideoMemBlitter) BX_OVERRIDE
	{
		m_cmd.finish(false);


		if ( m_commandBuffer == NULL )
		{
			m_commandBuffer = m_cmd.alloc();
		}

		int64_t elapsed = -bx::getHPCounter();
		int64_t captureElapsed = 0;

		m_gpuTimer.addHandlers(m_commandBuffer);

		if ( m_blitCommandEncoder )
		{
			m_blitCommandEncoder.endEncoding();
			m_blitCommandEncoder = 0;
		}

		updateResolution(_render->m_resolution);

		if ( m_saveScreenshot || NULL != m_capture )
		{
			if ( m_screenshotTarget )
			{
				if ( m_screenshotTarget.width() != m_resolution.m_width ||
					m_screenshotTarget.height() != m_resolution.m_height )
				{
					MTL_RELEASE(m_screenshotTarget);
				}
			}

			if ( NULL == m_screenshotTarget)
			{
				m_textureDescriptor.textureType = MTLTextureType2D;
				m_textureDescriptor.pixelFormat = m_metalLayer.pixelFormat;
				m_textureDescriptor.width  = m_resolution.m_width;
				m_textureDescriptor.height = m_resolution.m_height;
				m_textureDescriptor.depth  = 1;
				m_textureDescriptor.mipmapLevelCount = 1;
				m_textureDescriptor.sampleCount = 1;
				m_textureDescriptor.arrayLength = 1;
				if ( m_iOS9Runtime || m_macOS11Runtime )
				{
					m_textureDescriptor.cpuCacheMode = MTLCPUCacheModeDefaultCache;
					m_textureDescriptor.storageMode = (MTLStorageMode)(((BX_ENABLED(BX_PLATFORM_IOS)) ? 0 /* MTLStorageModeShared */ :  1 /*MTLStorageModeManaged*/)
														);
					m_textureDescriptor.usage		 = MTLTextureUsageRenderTarget | MTLTextureUsageShaderRead;
				}

				m_screenshotTarget   = m_device.newTextureWithDescriptor(m_textureDescriptor);
			}
			m_saveScreenshot = false;
		}
		else
		{
			MTL_RELEASE(m_screenshotTarget);
		}

		m_uniformBuffer = m_uniformBuffers[m_bufferIndex];
		m_bufferIndex = (m_bufferIndex + 1) % MTL_MAX_FRAMES_IN_FLIGHT;
		m_uniformBufferVertexOffset = 0;
		m_uniformBufferFragmentOffset = 0;

		if (0 < _render->m_iboffset)
		{
			TransientIndexBuffer* ib = _render->m_transientIb;
			m_indexBuffers[ib->handle.idx].update(0, _render->m_iboffset, ib->data, true);
		}

		if (0 < _render->m_vboffset)
		{
			TransientVertexBuffer* vb = _render->m_transientVb;
			m_vertexBuffers[vb->handle.idx].update(0, _render->m_vboffset, vb->data, true);
		}

		_render->sort();

		RenderDraw currentState;
		currentState.clear();
		currentState.m_stateFlags = BGFX_STATE_NONE;
		currentState.m_stencil    = packStencil(BGFX_STENCIL_NONE, BGFX_STENCIL_NONE);

		_render->m_hmdInitialized = false;

		const bool hmdEnabled = false;
		static ViewState viewState;
		viewState.reset(_render, hmdEnabled);
		uint32_t blendFactor = 0;

		bool wireframe = !!(_render->m_debug&BGFX_DEBUG_WIREFRAME);

		uint16_t programIdx = invalidHandle;
		SortKey key;
		uint16_t view = UINT16_MAX;
		FrameBufferHandle fbh = { BGFX_CONFIG_MAX_FRAME_BUFFERS };

		BlitKey blitKey;
		blitKey.decode(_render->m_blitKeys[0]);
		uint16_t numBlitItems = _render->m_numBlitItems;
		uint16_t blitItem = 0;

		const uint64_t primType = 0;
		uint8_t primIndex = uint8_t(primType>>BGFX_STATE_PT_SHIFT);
		PrimInfo prim = s_primInfo[primIndex];

		ProgramMtl* currentProgram = NULL;
		RenderCommandEncoder rce;

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

		m_occlusionQuery.resolve(_render);

		if (0 == (_render->m_debug&BGFX_DEBUG_IFH) )
		{
			bool viewRestart = false;
			uint8_t eye = 0;
			uint8_t restartState = 0;
			viewState.m_rect = _render->m_rect[0];

			int32_t numItems = _render->m_num;
			for (int32_t item = 0, restartItem = numItems; item < numItems || restartItem < numItems;)
			{
				const uint64_t encodedKey = _render->m_sortKeys[item];
				const bool isCompute = key.decode(encodedKey, _render->m_viewRemap);
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

					const uint8_t blitView = SortKey::decodeView(encodedKey);
					for (; blitItem < numBlitItems && blitKey.m_view <= blitView; blitItem++)
					{
						if (0 != m_renderCommandEncoder)
						{
							m_renderCommandEncoder.endEncoding();
							m_renderCommandEncoder = 0;
						}
						m_blitCommandEncoder = getBlitCommandEncoder();

						const BlitItem& blit = _render->m_blitItem[blitItem];
						blitKey.decode(_render->m_blitKeys[blitItem+1]);

						const TextureMtl& src = m_textures[blit.m_src.idx];
						const TextureMtl& dst = m_textures[blit.m_dst.idx];

						uint32_t srcWidth  = bx::uint32_min(src.m_width,  blit.m_srcX + blit.m_width)  - blit.m_srcX;
						uint32_t srcHeight = bx::uint32_min(src.m_height, blit.m_srcY + blit.m_height) - blit.m_srcY;
						uint32_t srcDepth  = bx::uint32_min(src.m_depth,  blit.m_srcZ + blit.m_depth)  - blit.m_srcZ;
						uint32_t dstWidth  = bx::uint32_min(dst.m_width,  blit.m_dstX + blit.m_width)  - blit.m_dstX;
						uint32_t dstHeight = bx::uint32_min(dst.m_height, blit.m_dstY + blit.m_height) - blit.m_dstY;
						uint32_t dstDepth  = bx::uint32_min(dst.m_depth,  blit.m_dstZ + blit.m_depth)  - blit.m_dstZ;
						uint32_t width     = bx::uint32_min(srcWidth,  dstWidth);
						uint32_t height    = bx::uint32_min(srcHeight, dstHeight);
						uint32_t depth     = bx::uint32_min(srcDepth,  dstDepth);
#if BX_PLATFORM_OSX
						bool     readBack  = !!(dst.m_flags & BGFX_TEXTURE_READ_BACK);
#endif  // BX_PLATFORM_OSX

						if ( MTLTextureType3D == src.m_ptr.textureType())
						{
							m_blitCommandEncoder.copyFromTexture(src.m_ptr, 0, 0, MTLOriginMake(blit.m_srcX, blit.m_srcY, blit.m_srcZ), MTLSizeMake(width, height, bx::uint32_imax(depth, 1)),
																 dst.m_ptr, 0, 0, MTLOriginMake(blit.m_dstX, blit.m_dstY, blit.m_dstZ));
#if BX_PLATFORM_OSX
							if (m_macOS11Runtime &&readBack) {
								m_blitCommandEncoder.synchronizeResource(dst.m_ptr);
							}
#endif  // BX_PLATFORM_OSX
						}
						else
						{
							m_blitCommandEncoder.copyFromTexture(src.m_ptr, blit.m_srcZ, blit.m_srcMip, MTLOriginMake(blit.m_srcX, blit.m_srcY, 0), MTLSizeMake(width, height, 1),
																 dst.m_ptr, blit.m_dstZ, blit.m_dstMip, MTLOriginMake(blit.m_dstX, blit.m_dstY, 0));
#if BX_PLATFORM_OSX
							if (m_macOS11Runtime && readBack) {
								m_blitCommandEncoder.synchronizeTexture(dst.m_ptr, 0, blit.m_dstMip);
							}
#endif  // BX_PLATFORM_OSX
						}
					}

					if (0 != m_blitCommandEncoder)
					{
						m_blitCommandEncoder.endEncoding();
						m_blitCommandEncoder = 0;
					}

					const Rect& scissorRect = _render->m_scissor[view];
					viewHasScissor = !scissorRect.isZero();
					viewScissorRect = viewHasScissor ? scissorRect : viewState.m_rect;
					Clear& clr = _render->m_clear[view];

					Rect viewRect = viewState.m_rect;
					bool clearWithRenderPass = false;

					if ( NULL == m_renderCommandEncoder || fbh.idx != _render->m_fb[view].idx )
					{
						if (0 != m_renderCommandEncoder)
						{
							m_renderCommandEncoder.endEncoding();
						}

						RenderPassDescriptor renderPassDescriptor = newRenderPassDescriptor();
						renderPassDescriptor.visibilityResultBuffer = m_occlusionQuery.m_buffer;

						fbh = _render->m_fb[view];

						uint32_t width  = m_resolution.m_width;
						uint32_t height = m_resolution.m_height;

						if ( isValid(fbh) )
						{
							FrameBufferMtl& frameBuffer = m_frameBuffers[fbh.idx];
							width = frameBuffer.m_width;
							height = frameBuffer.m_height;
						}

						clearWithRenderPass = true
						&& 0 == viewRect.m_x
						&& 0      == viewRect.m_y
						&& width  == viewRect.m_width
						&& height == viewRect.m_height;

						setFrameBuffer(renderPassDescriptor, fbh);

						if ( clearWithRenderPass )
						{

							for(uint32_t ii = 0; ii < g_caps.limits.maxFBAttachments; ++ii)
							{
								MTLRenderPassColorAttachmentDescriptor* desc = renderPassDescriptor.colorAttachments[ii];

								if ( desc.texture != NULL)
								{
									if (0 != (BGFX_CLEAR_COLOR & clr.m_flags) )
									{
										if (0 != (BGFX_CLEAR_COLOR_USE_PALETTE & clr.m_flags) )
										{
											uint8_t index = (uint8_t)bx::uint32_min(BGFX_CONFIG_MAX_COLOR_PALETTE-1, clr.m_index[ii]);
											const float* rgba = _render->m_colorPalette[index];
											const float rr = rgba[0];
											const float gg = rgba[1];
											const float bb = rgba[2];
											const float aa = rgba[3];
											desc.clearColor = MTLClearColorMake(rr, gg, bb, aa);
										}
										else
										{
											float rr = clr.m_index[0]*1.0f/255.0f;
											float gg = clr.m_index[1]*1.0f/255.0f;
											float bb = clr.m_index[2]*1.0f/255.0f;
											float aa = clr.m_index[3]*1.0f/255.0f;
											desc.clearColor = MTLClearColorMake(rr, gg, bb, aa);
										}

										desc.loadAction = MTLLoadActionClear;
									}
									else
									{
										desc.loadAction = MTLLoadActionLoad;
									}
									desc.storeAction = desc.texture.sampleCount > 1 ? MTLStoreActionMultisampleResolve : MTLStoreActionStore;
								}
							}

							//TODO: optimize store actions use discard flag
							RenderPassDepthAttachmentDescriptor depthAttachment = renderPassDescriptor.depthAttachment;
							if (NULL != depthAttachment.texture)
							{
								depthAttachment.clearDepth = clr.m_depth;
								depthAttachment.loadAction = 0 != (BGFX_CLEAR_DEPTH & clr.m_flags)
								? MTLLoadActionClear
								: MTLLoadActionLoad
								;
								depthAttachment.storeAction = NULL != m_backBufferColorMSAA ? MTLStoreActionDontCare : MTLStoreActionStore;
							}

							RenderPassStencilAttachmentDescriptor stencilAttachment = renderPassDescriptor.stencilAttachment;
							if (NULL != stencilAttachment.texture)
							{
								stencilAttachment.clearStencil = clr.m_stencil;
								stencilAttachment.loadAction   = 0 != (BGFX_CLEAR_STENCIL & clr.m_flags)
								? MTLLoadActionClear
								: MTLLoadActionLoad
								;
								stencilAttachment.storeAction = NULL != m_backBufferColorMSAA ? MTLStoreActionDontCare : MTLStoreActionStore;
							}
						}
						else
						{
							for(uint32_t ii = 0; ii < g_caps.limits.maxFBAttachments; ++ii)
							{
								MTLRenderPassColorAttachmentDescriptor* desc = renderPassDescriptor.colorAttachments[ii];
								if ( desc.texture != NULL)
									desc.loadAction = MTLLoadActionLoad;
							}

							//TODO: optimize store actions use discard flag
							RenderPassDepthAttachmentDescriptor depthAttachment = renderPassDescriptor.depthAttachment;
							if (NULL != depthAttachment.texture)
							{
								depthAttachment.loadAction = MTLLoadActionLoad;
								depthAttachment.storeAction = MTLStoreActionStore;
							}

							RenderPassStencilAttachmentDescriptor stencilAttachment = renderPassDescriptor.stencilAttachment;
							if (NULL != stencilAttachment.texture)
							{
								stencilAttachment.loadAction   = MTLLoadActionLoad;
								stencilAttachment.storeAction  = MTLStoreActionStore;
							}
						}

						rce = m_commandBuffer.renderCommandEncoderWithDescriptor(renderPassDescriptor);
						m_renderCommandEncoder = rce;
						m_renderCommandEncoderFrameBufferHandle = fbh;
						MTL_RELEASE(renderPassDescriptor);
					}

					rce.setTriangleFillMode(wireframe? MTLTriangleFillModeLines : MTLTriangleFillModeFill);

					if (BX_ENABLED(BGFX_CONFIG_DEBUG_MTL) )
					{
						if (item != 1)
						{
							rce.popDebugGroup();
						}

						rce.pushDebugGroup(s_viewName[view]);
					}

					MTLViewport vp;
					vp.originX = viewState.m_rect.m_x;
					vp.originY = viewState.m_rect.m_y;
					vp.width   = viewState.m_rect.m_width;
					vp.height  = viewState.m_rect.m_height;
					vp.znear   = 0.0f;
					vp.zfar    = 1.0f;
					rce.setViewport(vp);

					if (BGFX_CLEAR_NONE != (clr.m_flags & BGFX_CLEAR_MASK)
					&& !clearWithRenderPass)
					{
						clearQuad(_clearQuad, viewState.m_rect, clr, _render->m_colorPalette);
					}
				}

				bool resetState = viewChanged || wasCompute;

				if (wasCompute)
				{
					wasCompute = false;

					programIdx = invalidHandle;
					currentProgram = NULL;

					//invalidateCompute();
				}

				const RenderDraw& draw = renderItem.draw;

				const bool hasOcclusionQuery = 0 != (draw.m_stateFlags & BGFX_STATE_INTERNAL_OCCLUSION_QUERY);
				if (isValid(draw.m_occlusionQuery)
				&&  !hasOcclusionQuery
				&&  !isVisible(_render, draw.m_occlusionQuery, 0 != (draw.m_submitFlags&BGFX_SUBMIT_INTERNAL_OCCLUSION_VISIBLE) ) )
				{
					continue;
				}

				const uint64_t newFlags = draw.m_stateFlags;
				uint64_t changedFlags = currentState.m_stateFlags ^ draw.m_stateFlags;
				currentState.m_stateFlags = newFlags;

				const uint64_t newStencil = draw.m_stencil;
				uint64_t changedStencil = currentState.m_stencil ^ draw.m_stencil;
				currentState.m_stencil = newStencil;

				if (resetState)
				{
					currentState.clear();
					currentState.m_scissor = !draw.m_scissor;
					changedFlags = BGFX_STATE_MASK;
					changedStencil = packStencil(BGFX_STENCIL_MASK, BGFX_STENCIL_MASK);
					currentState.m_stateFlags = newFlags;
					currentState.m_stencil    = newStencil;

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
						if (scissorRect.isZeroArea() )
						{
							continue;
						}

						rc.x      = scissorRect.m_x;
						rc.y      = scissorRect.m_y;
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

				if (blendFactor != draw.m_rgba
				&& !(newFlags & BGFX_STATE_BLEND_INDEPENDENT) )
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
				rendererUpdateUniforms(this, _render->m_uniformBuffer, draw.m_constBegin, draw.m_constEnd);

				if (key.m_program != programIdx
				|| (BGFX_STATE_BLEND_MASK|BGFX_STATE_BLEND_EQUATION_MASK|BGFX_STATE_ALPHA_WRITE|BGFX_STATE_RGB_WRITE|BGFX_STATE_BLEND_INDEPENDENT|BGFX_STATE_MSAA|BGFX_STATE_BLEND_ALPHA_TO_COVERAGE) & changedFlags
				||  currentState.m_streamMask             != draw.m_streamMask
				||  currentState.m_stream[0].m_handle.idx != draw.m_stream[0].m_handle.idx
				||  currentState.m_stream[0].m_decl.idx   != draw.m_stream[0].m_decl.idx
				||  currentState.m_instanceDataStride     != draw.m_instanceDataStride
				|| ( (blendFactor != draw.m_rgba) && !!(newFlags & BGFX_STATE_BLEND_INDEPENDENT) ) )
				{
					programIdx = key.m_program;
					currentState.m_streamMask         = draw.m_streamMask;
					currentState.m_stream[0].m_decl   = draw.m_stream[0].m_decl;
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

						RenderPipelineState pipelineState = NULL;

						if (isValid(draw.m_stream[0].m_handle) )
						{
							uint16_t handle = draw.m_stream[0].m_handle.idx;
							const VertexBufferMtl& vb = m_vertexBuffers[handle];
							VertexDeclHandle decl;
							decl.idx = !isValid(vb.m_decl) ? draw.m_stream[0].m_decl.idx : vb.m_decl.idx;

							pipelineState = program.getRenderPipelineState(newFlags, draw.m_rgba, fbh, decl, draw.m_instanceDataStride/16);
						}

						if (NULL == pipelineState)
						{
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

					uint32_t vertexUniformBufferSize   = program.m_vshConstantBufferSize;
					uint32_t fragmentUniformBufferSize = program.m_fshConstantBufferSize;

					if (vertexUniformBufferSize)
					{
						m_uniformBufferVertexOffset = BX_ALIGN_MASK(m_uniformBufferVertexOffset, program.m_vshConstantBufferAlignmentMask);
						rce.setVertexBuffer(m_uniformBuffer, m_uniformBufferVertexOffset, 0);
					}

					m_uniformBufferFragmentOffset = m_uniformBufferVertexOffset + vertexUniformBufferSize;
					if (fragmentUniformBufferSize)
					{
						m_uniformBufferFragmentOffset = BX_ALIGN_MASK(m_uniformBufferFragmentOffset, program.m_fshConstantBufferAlignmentMask);
						rce.setFragmentBuffer(m_uniformBuffer, m_uniformBufferFragmentOffset, 0);
					}

					if (constantsChanged)
					{
						UniformBuffer* vcb = program.m_vshConstantBuffer;
						if (NULL != vcb)
						{
							commit(*vcb);
						}

						UniformBuffer* fcb = program.m_fshConstantBuffer;
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
					uint32_t usedVertexSamplerStages = 0;
					uint32_t usedFragmentSamplerStages = 0;

					if (invalidHandle != programIdx)
					{
						ProgramMtl& program = m_program[programIdx];
						usedVertexSamplerStages = program.m_usedVertexSamplerStages;
						usedFragmentSamplerStages = program.m_usedFragmentSamplerStages;
					}

					for (uint8_t stage = 0; stage < BGFX_CONFIG_MAX_TEXTURE_SAMPLERS; ++stage)
					{
						const Binding& sampler = draw.m_bind[stage];
						Binding& current = currentState.m_bind[stage];
						if (current.m_idx != sampler.m_idx
						||  current.m_un.m_draw.m_textureFlags != sampler.m_un.m_draw.m_textureFlags
						||  programChanged)
						{
							if (invalidHandle != sampler.m_idx)
							{
								TextureMtl& texture = m_textures[sampler.m_idx];
								texture.commit(stage, (usedVertexSamplerStages&(1<<stage))!=0,
											   (usedFragmentSamplerStages&(1<<stage))!=0,
												sampler.m_un.m_draw.m_textureFlags);
							}
						}

						current = sampler;
					}
				}

				if (currentState.m_streamMask              != draw.m_streamMask
				||  currentState.m_stream[0].m_handle.idx  != draw.m_stream[0].m_handle.idx
				||  currentState.m_stream[0].m_startVertex != draw.m_stream[0].m_startVertex
				||  currentState.m_instanceDataBuffer.idx  != draw.m_instanceDataBuffer.idx
				||  currentState.m_instanceDataOffset      != draw.m_instanceDataOffset)
				{
					currentState.m_streamMask               = draw.m_streamMask;
					currentState.m_stream[0].m_handle       = draw.m_stream[0].m_handle;
					currentState.m_stream[0].m_startVertex  = draw.m_stream[0].m_startVertex;
					currentState.m_instanceDataBuffer.idx   = draw.m_instanceDataBuffer.idx;
					currentState.m_instanceDataOffset       = draw.m_instanceDataOffset;

					uint16_t handle = draw.m_stream[0].m_handle.idx;
					if (invalidHandle != handle)
					{
						const VertexBufferMtl& vb = m_vertexBuffers[handle];

						uint16_t decl = !isValid(vb.m_decl) ? draw.m_stream[0].m_decl.idx : vb.m_decl.idx;
						const VertexDecl& vertexDecl = m_vertexDecls[decl];
						uint32_t offset = draw.m_stream[0].m_startVertex  * vertexDecl.getStride();

						rce.setVertexBuffer(vb.getBuffer(), offset, 1);

						if (isValid(draw.m_instanceDataBuffer) )
						{
							const VertexBufferMtl& inst = m_vertexBuffers[draw.m_instanceDataBuffer.idx];
							rce.setVertexBuffer(inst.getBuffer(), draw.m_instanceDataOffset, 2);
						}
					}
				}

				if (0 != currentState.m_streamMask)
				{
					uint32_t numVertices = draw.m_numVertices;
					if (UINT32_MAX == numVertices)
					{
						const VertexBufferMtl& vb = m_vertexBuffers[currentState.m_stream[0].m_handle.idx];
						uint16_t decl = !isValid(vb.m_decl) ? draw.m_stream[0].m_decl.idx : vb.m_decl.idx;
						const VertexDecl& vertexDecl = m_vertexDecls[decl];
						numVertices = vb.m_size/vertexDecl.m_stride;
					}

					uint32_t numIndices        = 0;
					uint32_t numPrimsSubmitted = 0;
					uint32_t numInstances      = 0;
					uint32_t numPrimsRendered  = 0;
					uint32_t numDrawIndirect   = 0;

					if (hasOcclusionQuery)
					{
						m_occlusionQuery.begin(rce, _render, draw.m_occlusionQuery);
					}

					if (isValid(draw.m_indirectBuffer) )
					{
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

								rce.drawIndexedPrimitives(prim.m_type, numIndices, indexType, ib.getBuffer(), 0, draw.m_numInstances);
							}
							else if (prim.m_min <= draw.m_numIndices)
							{
								const uint32_t indexSize = 0 == (ib.m_flags & BGFX_BUFFER_INDEX32) ? 2 : 4;
								numIndices        = draw.m_numIndices;
								numPrimsSubmitted = numIndices/prim.m_div - prim.m_sub;
								numInstances      = draw.m_numInstances;
								numPrimsRendered  = numPrimsSubmitted*draw.m_numInstances;

								rce.drawIndexedPrimitives(prim.m_type, numIndices, indexType, ib.getBuffer(), draw.m_startIndex * indexSize,numInstances);
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

					if (hasOcclusionQuery)
					{
						m_occlusionQuery.end(rce);
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
				//invalidateCompute();
			}

			if (0 < _render->m_num)
			{
				captureElapsed = -bx::getHPCounter();
				capture();
				rce = m_renderCommandEncoder; //TODO: ugly, can create new encoder
				captureElapsed += bx::getHPCounter();
			}
		}

		if (BX_ENABLED(BGFX_CONFIG_DEBUG_MTL) )
		{
			if (0 < _render->m_num)
			{
				rce.popDebugGroup();
			}
		}

		int64_t now = bx::getHPCounter();
		elapsed += now;

		static int64_t last = now;

		Stats& perfStats = _render->m_perfStats;
		perfStats.cpuTimeBegin = last;

		int64_t frameTime = now - last;
		last = now;

		static int64_t min = frameTime;
		static int64_t max = frameTime;
		min = bx::int64_min(min, frameTime);
		max = bx::int64_max(max, frameTime);

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

		perfStats.cpuTimeEnd    = now;
		perfStats.cpuTimerFreq  = timerFreq;
		perfStats.gpuTimeBegin  = m_gpuTimer.m_begin;
		perfStats.gpuTimeEnd    = m_gpuTimer.m_end;
		perfStats.gpuTimerFreq  = m_gpuTimer.m_frequency;
		perfStats.numDraw       = statsKeyType[0];
		perfStats.numCompute    = statsKeyType[1];
		perfStats.maxGpuLatency = maxGpuLatency;

		rce.setTriangleFillMode(MTLTriangleFillModeFill);
		if (_render->m_debug & (BGFX_DEBUG_IFH|BGFX_DEBUG_STATS) )
		{
			rce.pushDebugGroup("debugstats");

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

				pos = 10;
				tvm.printf(10, pos++, 0x8e, "        Frame: %7.3f, % 7.3f \x1f, % 7.3f \x1e [ms] / % 6.2f FPS "
						, double(frameTime)*toMs
						, double(min)*toMs
						, double(max)*toMs
						, freq/frameTime
						);

				const uint32_t msaa = (m_resolution.m_flags&BGFX_RESET_MSAA_MASK)>>BGFX_RESET_MSAA_SHIFT;
				tvm.printf(10, pos++, 0x8e, "  Reset flags: [%c] vsync, [%c] MSAAx%d, [%c] MaxAnisotropy "
						, !!(m_resolution.m_flags&BGFX_RESET_VSYNC) ? '\xfe' : ' '
						, 0 != msaa ? '\xfe' : ' '
						, 1<<msaa
						, !!(m_resolution.m_flags&BGFX_RESET_MAXANISOTROPY) ? '\xfe' : ' '
						);

				double elapsedCpuMs = double(elapsed)*toMs;
				tvm.printf(10, pos++, 0x8e, "    Submitted: %4d (draw %4d, compute %4d) / CPU %3.4f [ms] %c GPU %3.4f [ms] (latency %d)"
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
					tvm.printf(10, pos++, 0x8e, "   %10s: %7d (#inst: %5d), submitted: %7d"
							, s_primName[ii]
							, statsNumPrimsRendered[ii]
							, statsNumInstances[ii]
							, statsNumPrimsSubmitted[ii]
							);
				}

				tvm.printf(10, pos++, 0x8e, "      Indices: %7d ", statsNumIndices);
				tvm.printf(10, pos++, 0x8e, " Uniform size: %7d, Max: %7d ", _render->m_uniformEnd, _render->m_uniformMax);
				tvm.printf(10, pos++, 0x8e, "     DVB size: %7d ", _render->m_vboffset);
				tvm.printf(10, pos++, 0x8e, "     DIB size: %7d ", _render->m_iboffset);

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
			rce = m_renderCommandEncoder; //TODO: ugly, blit can create encoder

			rce.popDebugGroup();
		}
		else if (_render->m_debug & BGFX_DEBUG_TEXT)
		{
			rce.pushDebugGroup("debugtext");

			blit(this, _textVideoMemBlitter, _render->m_textVideoMem);
			rce = m_renderCommandEncoder; //TODO: ugly, blit can create encoder

			rce.popDebugGroup();
		}

		rce.endEncoding();
		m_renderCommandEncoder = 0;
		m_renderCommandEncoderFrameBufferHandle.idx = invalidHandle;


		if ( m_screenshotTarget )
		{
			RenderPassDescriptor renderPassDescriptor = newRenderPassDescriptor();
			renderPassDescriptor.colorAttachments[0].texture = currentDrawable().texture;
			renderPassDescriptor.colorAttachments[0].storeAction = MTLStoreActionStore;

			rce =  m_commandBuffer.renderCommandEncoderWithDescriptor(renderPassDescriptor);

			rce.setCullMode(MTLCullModeNone);

			rce.setRenderPipelineState(m_screenshotBlitRenderPipelineState);

			rce.setFragmentSamplerState(getSamplerState(BGFX_TEXTURE_U_CLAMP|BGFX_TEXTURE_V_CLAMP|BGFX_TEXTURE_MIN_POINT|BGFX_TEXTURE_MAG_POINT|BGFX_TEXTURE_MIP_POINT), 0);
			rce.setFragmentTexture(m_screenshotTarget, 0);

			rce.drawPrimitives(MTLPrimitiveTypeTriangle, 0, 3, 1);

			rce.endEncoding();
		 }
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
