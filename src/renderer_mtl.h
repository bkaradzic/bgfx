/*
 * Copyright 2011-2025 Attila Kocsis. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef BGFX_RENDERER_METAL_H_HEADER_GUARD
#define BGFX_RENDERER_METAL_H_HEADER_GUARD

#include "bgfx_p.h"

#if BGFX_CONFIG_RENDERER_METAL

#import <MetalKit/MetalKit.h>

#if BX_PLATFORM_IOS || BX_PLATFORM_VISIONOS
#	import <UIKit/UIKit.h>
#endif // BX_PLATFORM_*

#define BGFX_MTL_PROFILER_BEGIN(_view, _abgr)         \
	BX_MACRO_BLOCK_BEGIN                              \
		BGFX_PROFILER_BEGIN(s_viewName[view], _abgr); \
	BX_MACRO_BLOCK_END

#define BGFX_MTL_PROFILER_BEGIN_LITERAL(_name, _abgr) \
	BX_MACRO_BLOCK_BEGIN                              \
		BGFX_PROFILER_BEGIN_LITERAL("" _name, _abgr); \
	BX_MACRO_BLOCK_END

#define BGFX_MTL_PROFILER_END() \
	BX_MACRO_BLOCK_BEGIN        \
		BGFX_PROFILER_END();    \
	BX_MACRO_BLOCK_END

#define _MTL_RELEASE(_obj, _expected, _check)                                     \
	BX_MACRO_BLOCK_BEGIN                                                          \
		if (NULL != _obj)                                                         \
		{                                                                         \
			id _bridgedObj = (__bridge id)(const void*)_obj;                      \
			const NSUInteger count = [_bridgedObj retainCount] - 1;               \
			_check(isGraphicsDebuggerPresent()                                    \
				|| _expected == count                                             \
				, "%p RefCount is %d (expected %d). Label: \"%s\"."               \
				, _obj                                                            \
				, count                                                           \
				, _expected                                                       \
				, [_bridgedObj respondsToSelector:@selector(label)]               \
					? [[_bridgedObj performSelector:@selector(label)] UTF8String] \
					: "?!"                                                        \
				);                                                                \
			BX_UNUSED(count);                                                     \
			[_bridgedObj release];                                                \
			_obj = NULL;                                                          \
		}                                                                         \
	BX_MACRO_BLOCK_END

#define _MTL_CHECK_REFCOUNT(_obj, _expected)                                  \
	BX_MACRO_BLOCK_BEGIN                                                      \
		id _bridgedObj = (__bridge id)(const void*)_obj;                      \
		const NSUInteger count = [_bridgedObj retainCount];                   \
		BX_ASSERT(isGraphicsDebuggerPresent()                                 \
			|| _expected == count                                             \
			, "%p RefCount is %d (expected %d). Label: \"%s\"."               \
			, _obj                                                            \
			, count                                                           \
			, _expected                                                       \
			, [_bridgedObj respondsToSelector:@selector(label)]               \
				? [[_bridgedObj performSelector:@selector(label)] UTF8String] \
				: "?!"                                                        \
			);                                                                \
	BX_MACRO_BLOCK_END

#if BGFX_CONFIG_DEBUG
#	define MTL_CHECK_REFCOUNT(_ptr, _expected) _MTL_CHECK_REFCOUNT(_ptr, _expected)
#else
#	define MTL_CHECK_REFCOUNT(_ptr, _expected)
#endif // BGFX_CONFIG_DEBUG

#define MTL_RELEASE(_obj, _expected)   _MTL_RELEASE(_obj, _expected, BX_WARN)
#define MTL_RELEASE_W(_obj, _expected) _MTL_RELEASE(_obj, _expected, BX_WARN)
#define MTL_RELEASE_I(_obj)            _MTL_RELEASE(_obj, 0, BX_NOOP)

namespace bgfx { namespace mtl
{
	// Metal API has obnoxious "availability" annotations on enums causing build errors when
	// referencing format, and requiring use of ifdefery to reference format. To reduce ifdefery
	// bgfx uses redefined formats, and on initialization it sets up format caps and provides
	// availability.
	constexpr MTL::PixelFormat kMtlPixelFormatInvalid               = MTL::PixelFormat(0);
	constexpr MTL::PixelFormat kMtlPixelFormatA8Unorm               = MTL::PixelFormat(1);
	constexpr MTL::PixelFormat kMtlPixelFormatR8Unorm               = MTL::PixelFormat(10);
	constexpr MTL::PixelFormat kMtlPixelFormatR8Unorm_sRGB          = MTL::PixelFormat(11);
	constexpr MTL::PixelFormat kMtlPixelFormatR8Snorm               = MTL::PixelFormat(12);
	constexpr MTL::PixelFormat kMtlPixelFormatR8Uint                = MTL::PixelFormat(13);
	constexpr MTL::PixelFormat kMtlPixelFormatR8Sint                = MTL::PixelFormat(14);
	constexpr MTL::PixelFormat kMtlPixelFormatR16Unorm              = MTL::PixelFormat(20);
	constexpr MTL::PixelFormat kMtlPixelFormatR16Snorm              = MTL::PixelFormat(22);
	constexpr MTL::PixelFormat kMtlPixelFormatR16Uint               = MTL::PixelFormat(23);
	constexpr MTL::PixelFormat kMtlPixelFormatR16Sint               = MTL::PixelFormat(24);
	constexpr MTL::PixelFormat kMtlPixelFormatR16Float              = MTL::PixelFormat(25);
	constexpr MTL::PixelFormat kMtlPixelFormatRG8Unorm              = MTL::PixelFormat(30);
	constexpr MTL::PixelFormat kMtlPixelFormatRG8Unorm_sRGB         = MTL::PixelFormat(31);
	constexpr MTL::PixelFormat kMtlPixelFormatRG8Snorm              = MTL::PixelFormat(32);
	constexpr MTL::PixelFormat kMtlPixelFormatRG8Uint               = MTL::PixelFormat(33);
	constexpr MTL::PixelFormat kMtlPixelFormatRG8Sint               = MTL::PixelFormat(34);
	constexpr MTL::PixelFormat kMtlPixelFormatB5G6R5Unorm           = MTL::PixelFormat(40);
	constexpr MTL::PixelFormat kMtlPixelFormatA1BGR5Unorm           = MTL::PixelFormat(41);
	constexpr MTL::PixelFormat kMtlPixelFormatABGR4Unorm            = MTL::PixelFormat(42);
	constexpr MTL::PixelFormat kMtlPixelFormatBGR5A1Unorm           = MTL::PixelFormat(43);
	constexpr MTL::PixelFormat kMtlPixelFormatR32Uint               = MTL::PixelFormat(53);
	constexpr MTL::PixelFormat kMtlPixelFormatR32Sint               = MTL::PixelFormat(54);
	constexpr MTL::PixelFormat kMtlPixelFormatR32Float              = MTL::PixelFormat(55);
	constexpr MTL::PixelFormat kMtlPixelFormatRG16Unorm             = MTL::PixelFormat(60);
	constexpr MTL::PixelFormat kMtlPixelFormatRG16Snorm             = MTL::PixelFormat(62);
	constexpr MTL::PixelFormat kMtlPixelFormatRG16Uint              = MTL::PixelFormat(63);
	constexpr MTL::PixelFormat kMtlPixelFormatRG16Sint              = MTL::PixelFormat(64);
	constexpr MTL::PixelFormat kMtlPixelFormatRG16Float             = MTL::PixelFormat(65);
	constexpr MTL::PixelFormat kMtlPixelFormatRGBA8Unorm            = MTL::PixelFormat(70);
	constexpr MTL::PixelFormat kMtlPixelFormatRGBA8Unorm_sRGB       = MTL::PixelFormat(71);
	constexpr MTL::PixelFormat kMtlPixelFormatRGBA8Snorm            = MTL::PixelFormat(72);
	constexpr MTL::PixelFormat kMtlPixelFormatRGBA8Uint             = MTL::PixelFormat(73);
	constexpr MTL::PixelFormat kMtlPixelFormatRGBA8Sint             = MTL::PixelFormat(74);
	constexpr MTL::PixelFormat kMtlPixelFormatBGRA8Unorm            = MTL::PixelFormat(80);
	constexpr MTL::PixelFormat kMtlPixelFormatBGRA8Unorm_sRGB       = MTL::PixelFormat(81);
	constexpr MTL::PixelFormat kMtlPixelFormatRGB10A2Unorm          = MTL::PixelFormat(90);
	constexpr MTL::PixelFormat kMtlPixelFormatRGB10A2Uint           = MTL::PixelFormat(91);
	constexpr MTL::PixelFormat kMtlPixelFormatRG11B10Float          = MTL::PixelFormat(92);
	constexpr MTL::PixelFormat kMtlPixelFormatRGB9E5Float           = MTL::PixelFormat(93);
	constexpr MTL::PixelFormat kMtlPixelFormatBGR10A2Unorm          = MTL::PixelFormat(94);
	constexpr MTL::PixelFormat kMtlPixelFormatBGR10_XR              = MTL::PixelFormat(554);
	constexpr MTL::PixelFormat kMtlPixelFormatBGR10_XR_sRGB         = MTL::PixelFormat(555);
	constexpr MTL::PixelFormat kMtlPixelFormatRG32Uint              = MTL::PixelFormat(103);
	constexpr MTL::PixelFormat kMtlPixelFormatRG32Sint              = MTL::PixelFormat(104);
	constexpr MTL::PixelFormat kMtlPixelFormatRG32Float             = MTL::PixelFormat(105);
	constexpr MTL::PixelFormat kMtlPixelFormatRGBA16Unorm           = MTL::PixelFormat(110);
	constexpr MTL::PixelFormat kMtlPixelFormatRGBA16Snorm           = MTL::PixelFormat(112);
	constexpr MTL::PixelFormat kMtlPixelFormatRGBA16Uint            = MTL::PixelFormat(113);
	constexpr MTL::PixelFormat kMtlPixelFormatRGBA16Sint            = MTL::PixelFormat(114);
	constexpr MTL::PixelFormat kMtlPixelFormatRGBA16Float           = MTL::PixelFormat(115);
	constexpr MTL::PixelFormat kMtlPixelFormatBGRA10_XR             = MTL::PixelFormat(552);
	constexpr MTL::PixelFormat kMtlPixelFormatBGRA10_XR_sRGB        = MTL::PixelFormat(553);
	constexpr MTL::PixelFormat kMtlPixelFormatRGBA32Uint            = MTL::PixelFormat(123);
	constexpr MTL::PixelFormat kMtlPixelFormatRGBA32Sint            = MTL::PixelFormat(124);
	constexpr MTL::PixelFormat kMtlPixelFormatRGBA32Float           = MTL::PixelFormat(125);
	constexpr MTL::PixelFormat kMtlPixelFormatBC1_RGBA              = MTL::PixelFormat(130);
	constexpr MTL::PixelFormat kMtlPixelFormatBC1_RGBA_sRGB         = MTL::PixelFormat(131);
	constexpr MTL::PixelFormat kMtlPixelFormatBC2_RGBA              = MTL::PixelFormat(132);
	constexpr MTL::PixelFormat kMtlPixelFormatBC2_RGBA_sRGB         = MTL::PixelFormat(133);
	constexpr MTL::PixelFormat kMtlPixelFormatBC3_RGBA              = MTL::PixelFormat(134);
	constexpr MTL::PixelFormat kMtlPixelFormatBC3_RGBA_sRGB         = MTL::PixelFormat(135);
	constexpr MTL::PixelFormat kMtlPixelFormatBC4_RUnorm            = MTL::PixelFormat(140);
	constexpr MTL::PixelFormat kMtlPixelFormatBC4_RSnorm            = MTL::PixelFormat(141);
	constexpr MTL::PixelFormat kMtlPixelFormatBC5_RGUnorm           = MTL::PixelFormat(142);
	constexpr MTL::PixelFormat kMtlPixelFormatBC5_RGSnorm           = MTL::PixelFormat(143);
	constexpr MTL::PixelFormat kMtlPixelFormatBC6H_RGBFloat         = MTL::PixelFormat(150);
	constexpr MTL::PixelFormat kMtlPixelFormatBC6H_RGBUfloat        = MTL::PixelFormat(151);
	constexpr MTL::PixelFormat kMtlPixelFormatBC7_RGBAUnorm         = MTL::PixelFormat(152);
	constexpr MTL::PixelFormat kMtlPixelFormatBC7_RGBAUnorm_sRGB    = MTL::PixelFormat(153);
	constexpr MTL::PixelFormat kMtlPixelFormatPVRTC_RGB_2BPP        = MTL::PixelFormat(160);
	constexpr MTL::PixelFormat kMtlPixelFormatPVRTC_RGB_2BPP_sRGB   = MTL::PixelFormat(161);
	constexpr MTL::PixelFormat kMtlPixelFormatPVRTC_RGB_4BPP        = MTL::PixelFormat(162);
	constexpr MTL::PixelFormat kMtlPixelFormatPVRTC_RGB_4BPP_sRGB   = MTL::PixelFormat(163);
	constexpr MTL::PixelFormat kMtlPixelFormatPVRTC_RGBA_2BPP       = MTL::PixelFormat(164);
	constexpr MTL::PixelFormat kMtlPixelFormatPVRTC_RGBA_2BPP_sRGB  = MTL::PixelFormat(165);
	constexpr MTL::PixelFormat kMtlPixelFormatPVRTC_RGBA_4BPP       = MTL::PixelFormat(166);
	constexpr MTL::PixelFormat kMtlPixelFormatPVRTC_RGBA_4BPP_sRGB  = MTL::PixelFormat(167);
	constexpr MTL::PixelFormat kMtlPixelFormatEAC_R11Unorm          = MTL::PixelFormat(170);
	constexpr MTL::PixelFormat kMtlPixelFormatEAC_R11Snorm          = MTL::PixelFormat(172);
	constexpr MTL::PixelFormat kMtlPixelFormatEAC_RG11Unorm         = MTL::PixelFormat(174);
	constexpr MTL::PixelFormat kMtlPixelFormatEAC_RG11Snorm         = MTL::PixelFormat(176);
	constexpr MTL::PixelFormat kMtlPixelFormatEAC_RGBA8             = MTL::PixelFormat(178);
	constexpr MTL::PixelFormat kMtlPixelFormatEAC_RGBA8_sRGB        = MTL::PixelFormat(179);
	constexpr MTL::PixelFormat kMtlPixelFormatETC2_RGB8             = MTL::PixelFormat(180);
	constexpr MTL::PixelFormat kMtlPixelFormatETC2_RGB8_sRGB        = MTL::PixelFormat(181);
	constexpr MTL::PixelFormat kMtlPixelFormatETC2_RGB8A1           = MTL::PixelFormat(182);
	constexpr MTL::PixelFormat kMtlPixelFormatETC2_RGB8A1_sRGB      = MTL::PixelFormat(183);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_4x4_sRGB         = MTL::PixelFormat(186);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_5x4_sRGB         = MTL::PixelFormat(187);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_5x5_sRGB         = MTL::PixelFormat(188);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_6x5_sRGB         = MTL::PixelFormat(189);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_6x6_sRGB         = MTL::PixelFormat(190);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_8x5_sRGB         = MTL::PixelFormat(192);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_8x6_sRGB         = MTL::PixelFormat(193);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_8x8_sRGB         = MTL::PixelFormat(194);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_10x5_sRGB        = MTL::PixelFormat(195);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_10x6_sRGB        = MTL::PixelFormat(196);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_10x8_sRGB        = MTL::PixelFormat(197);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_10x10_sRGB       = MTL::PixelFormat(198);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_12x10_sRGB       = MTL::PixelFormat(199);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_12x12_sRGB       = MTL::PixelFormat(200);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_4x4_LDR          = MTL::PixelFormat(204);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_5x4_LDR          = MTL::PixelFormat(205);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_5x5_LDR          = MTL::PixelFormat(206);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_6x5_LDR          = MTL::PixelFormat(207);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_6x6_LDR          = MTL::PixelFormat(208);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_8x5_LDR          = MTL::PixelFormat(210);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_8x6_LDR          = MTL::PixelFormat(211);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_8x8_LDR          = MTL::PixelFormat(212);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_10x5_LDR         = MTL::PixelFormat(213);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_10x6_LDR         = MTL::PixelFormat(214);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_10x8_LDR         = MTL::PixelFormat(215);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_10x10_LDR        = MTL::PixelFormat(216);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_12x10_LDR        = MTL::PixelFormat(217);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_12x12_LDR        = MTL::PixelFormat(218);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_4x4_HDR          = MTL::PixelFormat(222);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_5x4_HDR          = MTL::PixelFormat(223);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_5x5_HDR          = MTL::PixelFormat(224);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_6x5_HDR          = MTL::PixelFormat(225);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_6x6_HDR          = MTL::PixelFormat(226);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_8x5_HDR          = MTL::PixelFormat(228);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_8x6_HDR          = MTL::PixelFormat(229);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_8x8_HDR          = MTL::PixelFormat(230);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_10x5_HDR         = MTL::PixelFormat(231);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_10x6_HDR         = MTL::PixelFormat(232);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_10x8_HDR         = MTL::PixelFormat(233);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_10x10_HDR        = MTL::PixelFormat(234);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_12x10_HDR        = MTL::PixelFormat(235);
	constexpr MTL::PixelFormat kMtlPixelFormatASTC_12x12_HDR        = MTL::PixelFormat(236);
	constexpr MTL::PixelFormat kMtlPixelFormatGBGR422               = MTL::PixelFormat(240);
	constexpr MTL::PixelFormat kMtlPixelFormatBGRG422               = MTL::PixelFormat(241);
	constexpr MTL::PixelFormat kMtlPixelFormatDepth16Unorm          = MTL::PixelFormat(250);
	constexpr MTL::PixelFormat kMtlPixelFormatDepth32Float          = MTL::PixelFormat(252);
	constexpr MTL::PixelFormat kMtlPixelFormatStencil8              = MTL::PixelFormat(253);
	constexpr MTL::PixelFormat kMtlPixelFormatDepth24Unorm_Stencil8 = MTL::PixelFormat(255);
	constexpr MTL::PixelFormat kMtlPixelFormatDepth32Float_Stencil8 = MTL::PixelFormat(260);
	constexpr MTL::PixelFormat kMtlPixelFormatX32_Stencil8          = MTL::PixelFormat(261);
	constexpr MTL::PixelFormat kMtlPixelFormatX24_Stencil8          = MTL::PixelFormat(262);

	constexpr MTL::GPUFamily kMtlGPUFamilyApple1  = MTL::GPUFamily(1001);
	constexpr MTL::GPUFamily kMtlGPUFamilyApple2  = MTL::GPUFamily(1002);
	constexpr MTL::GPUFamily kMtlGPUFamilyApple3  = MTL::GPUFamily(1003);
	constexpr MTL::GPUFamily kMtlGPUFamilyApple4  = MTL::GPUFamily(1004);
	constexpr MTL::GPUFamily kMtlGPUFamilyApple5  = MTL::GPUFamily(1005);
	constexpr MTL::GPUFamily kMtlGPUFamilyApple6  = MTL::GPUFamily(1006);
	constexpr MTL::GPUFamily kMtlGPUFamilyApple7  = MTL::GPUFamily(1007);
	constexpr MTL::GPUFamily kMtlGPUFamilyApple8  = MTL::GPUFamily(1008);
	constexpr MTL::GPUFamily kMtlGPUFamilyApple9  = MTL::GPUFamily(1009);
	constexpr MTL::GPUFamily kMtlGPUFamilyApple10 = MTL::GPUFamily(1010);

	typedef MTL::BlitCommandEncoder*    BlitCommandEncoder;
	typedef MTL::Buffer*                Buffer;
	typedef MTL::CommandBuffer*         CommandBuffer;
	typedef MTL::CommandQueue*          CommandQueue;
	typedef MTL::ComputeCommandEncoder* ComputeCommandEncoder;
	typedef MTL::Device*                Device;
	typedef MTL::Function*              Function;
	typedef MTL::Library*               Library;
	typedef MTL::RenderCommandEncoder*  RenderCommandEncoder;
	typedef MTL::Texture*               Texture;
	typedef MTL::ComputePipelineState*  ComputePipelineState;
	typedef MTL::DepthStencilState*     DepthStencilState;
	typedef MTL::RenderPipelineState*   RenderPipelineState;
	typedef MTL::SamplerState*          SamplerState;

	// String conversion helper for metal-cpp API calls that take NS::String*
	inline NS::String* nsstr(const char* _str)
	{
		return NS::String::string(_str, NS::UTF8StringEncoding);
	}

	inline Library newLibraryWithSource(Device _device, const char* _source)
	{
		NS::Error* error = NULL;
		NS::String* source = NS::String::string(_source, NS::ASCIIStringEncoding);
		Library lib = _device->newLibrary(source, (MTL::CompileOptions*)NULL, &error);
		BX_WARN(NULL == error
			, "Shader compilation failed: %s"
			, error->localizedDescription()->utf8String()
			);
		return lib;
	}

	typedef MTL::RenderPipelineDescriptor*                    RenderPipelineDescriptor;
	typedef MTL::RenderPipelineColorAttachmentDescriptor*     RenderPipelineColorAttachmentDescriptor;
	typedef MTL::RenderPipelineColorAttachmentDescriptorArray* RenderPipelineColorAttachmentDescriptorArray;
	typedef MTL::ComputePipelineReflection*                   ComputePipelineReflection;
	typedef MTL::DepthStencilDescriptor*                      DepthStencilDescriptor;
	typedef MTL::StencilDescriptor*                           StencilDescriptor;
	typedef MTL::RenderPassColorAttachmentDescriptor*         RenderPassColorAttachmentDescriptor;
	typedef MTL::RenderPassDepthAttachmentDescriptor*         RenderPassDepthAttachmentDescriptor;
	typedef MTL::RenderPassStencilAttachmentDescriptor*       RenderPassStencilAttachmentDescriptor;
	typedef MTL::RenderPassDescriptor*                        RenderPassDescriptor;
	typedef MTL::VertexDescriptor*                            VertexDescriptor;
	typedef MTL::SamplerDescriptor*                           SamplerDescriptor;
	typedef MTL::TextureDescriptor*                           TextureDescriptor;
	typedef MTL::RenderPipelineReflection*                    RenderPipelineReflection;
	typedef MTL::CaptureManager*                              CaptureManager;
	typedef MTL::CaptureDescriptor*                           CaptureDescriptor;
	typedef MTL::RasterizationRateMapDescriptor*              RasterizationRateMapDescriptor;
	typedef MTL::RasterizationRateLayerDescriptor*            RasterizationRateLayerDescriptor;

	inline RenderPipelineState newRenderPipelineStateWithDescriptor(Device _device, RenderPipelineDescriptor _descriptor)
	{
		NS::Error* error = NULL;
		RenderPipelineState state = _device->newRenderPipelineState(_descriptor, &error);
		BX_WARN(NULL == error
			, "newRenderPipelineStateWithDescriptor failed: %s"
			, error->localizedDescription()->utf8String()
			);
		return state;
	}

	inline RenderPipelineState newRenderPipelineStateWithDescriptor(
		  Device _device
		, RenderPipelineDescriptor _descriptor
		, MTL::PipelineOption _options
		, RenderPipelineReflection* _reflection
		)
	{
		NS::Error* error = NULL;
		RenderPipelineState state = _device->newRenderPipelineState(_descriptor, _options, _reflection, &error);
		BX_WARN(NULL == error
			, "newRenderPipelineStateWithDescriptor failed: %s"
			, error->localizedDescription()->utf8String()
			);
		return state;
	}

	inline ComputePipelineState newComputePipelineStateWithFunction(
		  Device _device
		, Function _function
		, MTL::PipelineOption _options
		, ComputePipelineReflection* _reflection
		)
	{
		NS::Error* error = NULL;
		ComputePipelineState state = _device->newComputePipelineState(_function, _options, _reflection, &error);
		BX_WARN(NULL == error
			, "newComputePipelineStateWithFunction failed: %s"
			, error->localizedDescription()->utf8String()
			);
		return state;
	}

	inline RenderPipelineDescriptor newRenderPipelineDescriptor()
	{
		return MTL::RenderPipelineDescriptor::alloc()->init();
	}

	inline void reset(RenderPipelineDescriptor _desc)
	{
		_desc->reset();
	}

	inline DepthStencilDescriptor newDepthStencilDescriptor()
	{
		return MTL::DepthStencilDescriptor::alloc()->init();
	}

	inline StencilDescriptor newStencilDescriptor()
	{
		return MTL::StencilDescriptor::alloc()->init();
	}

	inline RenderPassDescriptor newRenderPassDescriptor()
	{
		return MTL::RenderPassDescriptor::alloc()->init();
	}

	inline VertexDescriptor newVertexDescriptor()
	{
		return MTL::VertexDescriptor::alloc()->init();
	}

	inline void reset(VertexDescriptor _desc)
	{
		_desc->reset();
	}

	inline SamplerDescriptor newSamplerDescriptor()
	{
		return MTL::SamplerDescriptor::alloc()->init();
	}

	inline TextureDescriptor newTextureDescriptor()
	{
		return MTL::TextureDescriptor::alloc()->init();
	}

	inline CaptureManager getSharedCaptureManager()
	{
		return MTL::CaptureManager::sharedCaptureManager();
	}

	inline CaptureDescriptor newCaptureDescriptor()
	{
		return MTL::CaptureDescriptor::alloc()->init();
	}

	inline RasterizationRateLayerDescriptor newRasterizationRateLayerDescriptor(float _rate)
	{
		const float rate[1] = { _rate };
		return MTL::RasterizationRateLayerDescriptor::alloc()->init(MTL::Size::Make(1, 1, 0), rate, rate);
	}

	inline RasterizationRateMapDescriptor newRasterizationRateMapDescriptor()
	{
		return MTL::RasterizationRateMapDescriptor::alloc()->init();
	}

	//helper functions
	inline void release(NSObject* _obj)
	{
		[_obj release];
	}

	template<typename T>
	inline void release(T* _obj)
	{
		[(id)(void*)_obj release];
	}

	inline void retain(NSObject* _obj)
	{
		[_obj retain];
	}

	template<typename T>
	inline void retain(T* _obj)
	{
		[(id)(void*)_obj retain];
	}

	inline const char* utf8String(NSString* _str)
	{
		return [_str UTF8String];
	}

	// end of c++ wrapper

	template <typename Ty>
	class StateCacheT
	{
	public:
		void add(uint64_t _id, Ty _item)
		{
			invalidate(_id);
			m_hashMap.insert(stl::make_pair(_id, _item) );
		}

		Ty find(uint64_t _id)
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
				release(it->second);
				m_hashMap.erase(it);
			}
		}

		void invalidate()
		{
			for (typename HashMap::iterator it = m_hashMap.begin(), itEnd = m_hashMap.end(); it != itEnd; ++it)
			{
				release(it->second);
			}

			m_hashMap.clear();
		}

		uint32_t getCount() const
		{
			return uint32_t(m_hashMap.size() );
		}

	private:
		typedef stl::unordered_map<uint64_t, Ty> HashMap;
		HashMap m_hashMap;
	};

	struct BufferMtl
	{
		BufferMtl()
			: m_flags(BGFX_BUFFER_NONE)
			, m_ptr(NULL)
			, m_dynamic(NULL)
		{
		}

		void create(uint32_t _size, void* _data, uint16_t _flags, uint16_t _stride = 0, bool _vertex = false);
		void update(uint32_t _offset, uint32_t _size, void* _data, bool _discard = false);

		void destroy()
		{
			MTL_RELEASE_W(m_ptr, 0);

			if (NULL != m_dynamic)
			{
				bx::deleteObject(g_allocator, m_dynamic);
				m_dynamic = NULL;
			}
		}

		uint32_t m_size;
		uint16_t m_flags;
		bool     m_vertex;

		Buffer   m_ptr;
		uint8_t* m_dynamic;
	};

	typedef BufferMtl IndexBufferMtl;

	struct VertexBufferMtl : public BufferMtl
	{
		VertexBufferMtl()
			: BufferMtl()
		{
		}

		void create(uint32_t _size, void* _data, VertexLayoutHandle _layoutHandle, uint16_t _flags);

		VertexLayoutHandle m_layoutHandle;
	};

	struct ShaderMtl
	{
		ShaderMtl()
			: m_function(NULL)
		{
		}

		void create(const Memory* _mem);

		void destroy()
		{
			MTL_RELEASE_W(m_function, 0);
		}

		Function m_function;
		uint32_t m_hash;
		uint16_t m_numThreads[3];
	};

	struct PipelineStateMtl;

	struct ProgramMtl
	{
		ProgramMtl()
			: m_vsh(NULL)
			, m_fsh(NULL)
			, m_computePS(NULL)
		{
		}

		void create(const ShaderMtl* _vsh, const ShaderMtl* _fsh);
		void destroy();

		uint8_t  m_used[Attrib::Count+1]; // dense
		uint32_t m_attributes[Attrib::Count]; // sparse
		uint32_t m_instanceData[BGFX_CONFIG_MAX_INSTANCE_DATA_COUNT+1];

		const ShaderMtl* m_vsh;
		const ShaderMtl* m_fsh;

		PipelineStateMtl* m_computePS;
	};

	struct PipelineStateMtl
	{
		PipelineStateMtl()
			: m_vshConstantBuffer(NULL)
			, m_fshConstantBuffer(NULL)
			, m_vshConstantBufferSize(0)
			, m_vshConstantBufferAlignment(0)
			, m_fshConstantBufferSize(0)
			, m_fshConstantBufferAlignment(0)
			, m_numPredefined(0)
			, m_rps(NULL)
			, m_cps(NULL)
		{
			m_numThreads[0] = 1;
			m_numThreads[1] = 1;
			m_numThreads[2] = 1;

			for (uint32_t ii = 0; ii < BGFX_CONFIG_MAX_TEXTURE_SAMPLERS; ++ii)
			{
				m_bindingTypes[ii] = 0;
			}
		}

		~PipelineStateMtl()
		{
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

			MTL_RELEASE_W(m_rps, 0);
			MTL_RELEASE_W(m_cps, 0);
		}

		UniformBuffer* m_vshConstantBuffer;
		UniformBuffer* m_fshConstantBuffer;

		uint32_t m_vshConstantBufferSize;
		uint32_t m_vshConstantBufferAlignment;
		uint32_t m_fshConstantBufferSize;
		uint32_t m_fshConstantBufferAlignment;

		enum
		{
			BindToVertexShader   = 1 << 0,
			BindToFragmentShader = 1 << 1,
		};
		uint8_t m_bindingTypes[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];

		uint16_t m_numThreads[3];

		PredefinedUniform m_predefined[PredefinedUniform::Count*2];
		uint8_t m_numPredefined;

		RenderPipelineState  m_rps;
		ComputePipelineState m_cps;
	};

	void release(PipelineStateMtl* _ptr)
	{
		bx::deleteObject(g_allocator, _ptr);
	}

	struct TextureMtl
	{
		enum Enum
		{
			Texture2D,
			Texture3D,
			TextureCube,
		};

		TextureMtl()
			: m_ptr(NULL)
			, m_ptrMsaa(NULL)
			, m_ptrStencil(NULL)
			, m_sampler(NULL)
			, m_flags(0)
			, m_width(0)
			, m_height(0)
			, m_depth(0)
			, m_numMips(0)
		{
			for (uint32_t ii = 0; ii < BX_COUNTOF(m_ptrMips); ++ii)
			{
				m_ptrMips[ii] = NULL;
			}
		}

		void create(const Memory* _mem, uint64_t _flags, uint8_t _skip, uint64_t _external);
		void destroy();
		void overrideInternal(uintptr_t _ptr);

		void update(
			  uint8_t _side
			, uint8_t _mip
			, const Rect& _rect
			, uint16_t _z
			, uint16_t _depth
			, uint16_t _pitch
			, const Memory* _mem
			);

		void commit(
			  uint8_t _stage
			, bool _vertex
			, bool _fragment
			, uint32_t _flags = BGFX_SAMPLER_INTERNAL_DEFAULT
			, uint8_t _mip = UINT8_MAX
			);

		Texture getTextureMipLevel(uint8_t _mip);

		Texture m_ptr;
		Texture m_ptrMsaa;
		Texture m_ptrStencil; // for emulating packed depth/stencil formats - only for iOS8...
		Texture m_ptrMips[14];
		SamplerState m_sampler;
		uint64_t m_flags;
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_depth;
		uint8_t m_type;
		uint8_t m_requestedFormat;
		uint8_t m_textureFormat;
		uint8_t m_numMips;
	};

	struct FrameBufferMtl;

	struct SwapChainMtl
	{
		SwapChainMtl()
			: m_metalLayer(NULL)
			, m_drawable(NULL)
			, m_drawableTexture(NULL)
			, m_backBufferColorMsaa()
			, m_backBufferDepth()
			, m_backBufferStencil()
			, m_maxAnisotropy(0)
		{
		}

		~SwapChainMtl();

		void init(void* _nwh);

		void releaseBackBuffer();

		uint32_t resize(uint32_t _width, uint32_t _height, TextureFormat::Enum _format, TextureFormat::Enum _depthFormat);

		Texture currentDrawableTexture();

		CAMetalLayer* m_metalLayer;
		id<CAMetalDrawable> m_drawable;

		Texture m_drawableTexture;

		Texture m_backBufferColorMsaa;
		Texture m_backBufferDepth;
		Texture m_backBufferStencil;

		uint32_t m_maxAnisotropy;
		void* m_nwh;
	};

	struct FrameBufferMtl
	{
		FrameBufferMtl()
			: m_swapChain(NULL)
			, m_nwh(NULL)
			, m_pixelFormatHash(0)
			, m_denseIdx(UINT16_MAX)
			, m_num(0)
		{
			m_depthHandle = BGFX_INVALID_HANDLE;
		}

		void create(uint8_t _num, const Attachment* _attachment);
		void create(
			  uint16_t _denseIdx
			, void* _nwh
			, uint32_t _width
			, uint32_t _height
			, TextureFormat::Enum _format
			, TextureFormat::Enum _depthFormat
			);
		void postReset();
		uint16_t destroy();

		void resolve();
		void resizeSwapChain(
			  uint32_t _width
			, uint32_t _height
			, TextureFormat::Enum _format = TextureFormat::Count
			, TextureFormat::Enum _depthFormat = TextureFormat::Count
			);

		SwapChainMtl* m_swapChain;
		void* m_nwh;
		uint32_t m_pixelFormatHash;
		uint32_t m_width;
		uint32_t m_height;
		uint16_t m_denseIdx;

		TextureHandle m_colorHandle[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS-1];
		TextureHandle m_depthHandle;
		Attachment m_colorAttachment[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS-1];
		Attachment m_depthAttachment;
		uint8_t m_num; // number of color handles
	};

	struct CommandQueueMtl
	{
		CommandQueueMtl()
			: m_commandQueue(NULL)
			, m_activeCommandBuffer(NULL)
			, m_releaseWriteIndex(0)
			, m_releaseReadIndex(0)
		{
		}

		void init(Device _device);
		void shutdown();
		CommandBuffer alloc();
		void kick(bool _endFrame, bool _waitForFinish);
		void finish(bool _finishAll);
		void release(NSObject* _ptr);

		template<typename T>
		void release(T* _ptr) { release( (__bridge NSObject*)(const void*)_ptr ); }

		void consume();

		bx::Semaphore m_framesSemaphore;

		CommandQueue  m_commandQueue;
		CommandBuffer m_activeCommandBuffer;

		int m_releaseWriteIndex;
		int m_releaseReadIndex;
		typedef stl::vector<NSObject*> ResourceArray;
		ResourceArray m_release[BGFX_CONFIG_MAX_FRAME_LATENCY];
	};

	struct TimerQueryMtl
	{
		TimerQueryMtl()
			: m_control(4)
		{
		}

		void init();
		void shutdown();
		uint32_t begin(uint32_t _resultIdx, uint32_t _frameNum);
		void end(uint32_t _idx);
		void addHandlers(CommandBuffer& _commandBuffer);
		bool get();

		struct Result
		{
			void reset()
			{
				m_begin    = 0;
				m_end      = 0;
				m_pending  = 0;
				m_frameNum = 0;
			}

			uint64_t m_begin;
			uint64_t m_end;
			uint32_t m_pending;
			uint32_t m_frameNum; // TODO: implement (currently stays 0)
		};

		uint64_t m_begin;
		uint64_t m_end;
		uint64_t m_elapsed;
		uint64_t m_frequency;

		Result m_result[BGFX_CONFIG_MAX_VIEWS+1];
		bx::RingBufferControl m_control;
	};

	struct OcclusionQueryMTL
	{
		OcclusionQueryMTL()
			: m_buffer(NULL)
			, m_control(BX_COUNTOF(m_query) )
		{
		}

		void postReset();
		void preReset();
		void begin(RenderCommandEncoder& _rce, Frame* _render, OcclusionQueryHandle _handle);
		void end(RenderCommandEncoder& _rce);
		void resolve(Frame* _render, bool _wait = false);
		void invalidate(OcclusionQueryHandle _handle);

		struct Query
		{
			OcclusionQueryHandle m_handle;
		};

		Buffer m_buffer;
		Query m_query[BGFX_CONFIG_MAX_OCCLUSION_QUERIES];
		bx::RingBufferControl m_control;
	};

} /* namespace metal */ } // namespace bgfx

#endif // BGFX_CONFIG_RENDERER_METAL

#endif // BGFX_RENDERER_METAL_H_HEADER_GUARD
