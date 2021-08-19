//=============================================================================================
// Copyright 2011-2021 Branimir Karadzic. All rights reserved.
// License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
//=============================================================================================

#include "renderer_agc.h"

//=============================================================================================

#if BGFX_CONFIG_RENDERER_AGC

//=============================================================================================

namespace {

//=============================================================================================

// This is a temporary utility function to allocate direct memory. It's not important to understand how this works.
uint8_t* allocDmem(sce::Agc::SizeAlign sizeAlign)
{
	if (!sizeAlign.m_size)
	{
		return nullptr;
	}

	static uint32_t allocCount = 0;
	off_t offsetOut;

	// TODO: (manderson) Min alignment and size 64k???
	const size_t alignment = (sizeAlign.m_align + 0xffffu) & ~0xffffu;
	const uint64_t size = (sizeAlign.m_size + 0xffffu) & ~0xffffu;

	int32_t ret = sceKernelAllocateMainDirectMemory(size, alignment, SCE_KERNEL_MTYPE_C_SHARED, &offsetOut);
	if (ret) {
		printf("sceKernelAllocateMainDirectMemory error:0x%x size:0x%zx\n", ret, size);
		return nullptr;
	}

	void* ptr = NULL;
	char namedStr[32];
	snprintf_s(namedStr, sizeof(namedStr), "bgfx %d_%zuKB", allocCount++, size >> 10);
	ret = sceKernelMapNamedDirectMemory(&ptr, size, SCE_KERNEL_PROT_GPU_RW | SCE_KERNEL_PROT_CPU_RW, 0, offsetOut, alignment, namedStr);
	SCE_AGC_ASSERT_MSG(ret == SCE_OK, "Unable to map memory");
	return (uint8_t*)ptr;
}

//=============================================================================================

void freeDmem(void* memVA)
{
	SceKernelVirtualQueryInfo info;
	if (sceKernelVirtualQuery(memVA, 0, &info, sizeof(info)) < 0)
	{
		printf("virtual query failed for mem 0x%p", memVA);
		return;
	}
	if (sceKernelReleaseDirectMemory(info.offset, (uintptr_t)info.end - (uintptr_t)info.start) < 0)
	{
		printf("error freeing direct memory\n");
		return;
	}
}

//=============================================================================================

} // namespace 

//=============================================================================================

namespace bgfx { namespace agc {

//=============================================================================================

struct AttribFormat
{
	sce::Agc::Core::TypedFormat mTypedFormat;
	sce::Agc::Core::VertexAttribute::Format mAttribFormat;
	sce::Agc::Core::Swizzle mSwizzle;
};

#define ATTRIB_FORMAT(num, type, norm, format, x, y, z, w ) \
	{ \
		VertexLayout::encode(num, AttribType::type, norm, false), \
		{ \
			sce::Agc::Core::TypedFormat::format, \
			sce::Agc::Core::VertexAttribute::Format::format, \
			sce::Agc::Core::createSwizzle(sce::Agc::Core::ChannelSelect::x, sce::Agc::Core::ChannelSelect::y, sce::Agc::Core::ChannelSelect::z, sce::Agc::Core::ChannelSelect::w) \
		} \
	}

static std::unordered_map<uint16_t, AttribFormat> sAttribFormatIndex{
	ATTRIB_FORMAT(1, Float, false, k32Float, kX, k0, k0, k1),
	ATTRIB_FORMAT(2, Float, false, k32_32Float, kX, kY, k0, k1),
	ATTRIB_FORMAT(3, Float, false, k32_32_32Float, kX, kY, kZ, k1),
	ATTRIB_FORMAT(4, Float, false, k32_32_32_32Float, kX, kY, kZ, kW),

	ATTRIB_FORMAT(1, Half, false, k16Float, kX, k0, k0, k1),
	ATTRIB_FORMAT(2, Half, false, k16_16Float, kX, kY, k0, k1),
	ATTRIB_FORMAT(3, Half, false, k16_16_16_16Float, kX, kY, kZ, k1),
	ATTRIB_FORMAT(4, Half, false, k16_16_16_16Float, kX, kY, kZ, kW),

	ATTRIB_FORMAT(1, Uint8, true, k8UNorm, kX, k0, k0, k1),
	ATTRIB_FORMAT(2, Uint8, true, k8_8UNorm, kX, kY, k0, k1),
	ATTRIB_FORMAT(3, Uint8, true, k8_8_8_8UNorm, kX, kY, kZ, k1),
	ATTRIB_FORMAT(4, Uint8, true, k8_8_8_8UNorm, kX, kY, kZ, kW),

	ATTRIB_FORMAT(1, Uint8, false, k8UInt, kX, k0, k0, k1),
	ATTRIB_FORMAT(2, Uint8, false, k8_8UInt, kX, kY, k0, k1),
	ATTRIB_FORMAT(3, Uint8, false, k8_8_8_8UInt, kX, kY, kZ, k1),
	ATTRIB_FORMAT(4, Uint8, false, k8_8_8_8UInt, kX, kY, kZ, kW),

	ATTRIB_FORMAT(1, Int16, true, k16SNorm, kX, k0, k0, k1),
	ATTRIB_FORMAT(2, Int16, true, k16_16SNorm, kX, kY, k0, k1),
	ATTRIB_FORMAT(3, Int16, true, k16_16_16_16SNorm, kX, kY, kZ, k1),
	ATTRIB_FORMAT(4, Int16, true, k16_16_16_16SNorm, kX, kY, kZ, kW),

	ATTRIB_FORMAT(1, Int16, false, k16SInt, kX, k0, k0, k1),
	ATTRIB_FORMAT(2, Int16, false, k16_16SInt, kX, kY, k0, k1),
	ATTRIB_FORMAT(3, Int16, false, k16_16_16_16SInt, kX, kY, kZ, k1),
	ATTRIB_FORMAT(4, Int16, false, k16_16_16_16SInt, kX, kY, kZ, kW),

	ATTRIB_FORMAT(1, Uint10, false, k10_10_10_2UInt, kX, k0, k0, k1),
	ATTRIB_FORMAT(2, Uint10, false, k10_10_10_2UInt, kX, kY, k0, k1),
	ATTRIB_FORMAT(3, Uint10, false, k10_10_10_2UInt, kX, kY, kZ, k1),

	ATTRIB_FORMAT(1, Uint10, true, k10_10_10_2UNorm, kX, k0, k0, k1),
	ATTRIB_FORMAT(2, Uint10, true, k10_10_10_2UNorm, kX, kY, k0, k1),
	ATTRIB_FORMAT(3, Uint10, true, k10_10_10_2UNorm, kX, kY, kZ, k1),
};

#undef ATTRIB_FORMAT

//=============================================================================================

struct PrimTypeInfo
{
	sce::Agc::UcPrimitiveType::Type m_type;
	uint32_t m_min;
	uint32_t m_div;
	uint32_t m_sub;
};

#define PRIM_TYPE( type, min, div, sub ) \
	{ \
		sce::Agc::UcPrimitiveType::Type::type, \
		min, \
		div, \
		sub \
	}

static const std::array<PrimTypeInfo, Topology::Enum::Count> sPrimTypeInfo{{
	PRIM_TYPE(kTriList, 3, 3, 0),
	PRIM_TYPE(kTriStrip, 3, 1, 2),
	PRIM_TYPE(kLineList, 2, 2, 0),
	PRIM_TYPE(kLineStrip, 2, 1, 1),
	PRIM_TYPE(kPointList, 1, 1, 0),
}};

#undef PRIM_TYPE

//=============================================================================================

#define CULL_MODE( mode ) \
		sce::Agc::CxPrimitiveSetup::CullFace::mode

static const std::array<sce::Agc::CxPrimitiveSetup::CullFace, 3> sCullMode{{
	CULL_MODE( kNone ),
	CULL_MODE( kFront ),
	CULL_MODE( kBack ),
}};

#undef CULL_MODE

//=============================================================================================

#define DEPTH_FUNC( func ) \
		sce::Agc::CxDepthStencilControl::DepthFunction::func

static const std::array<sce::Agc::CxDepthStencilControl::DepthFunction, 9> sDepthFunc{{
	DEPTH_FUNC( kAlways ),
	DEPTH_FUNC( kLess ),
	DEPTH_FUNC( kLessEqual ),
	DEPTH_FUNC( kEqual ),
	DEPTH_FUNC( kGreaterEqual ),
	DEPTH_FUNC( kGreater ),
	DEPTH_FUNC( kNotEqual ),
	DEPTH_FUNC( kNever ),
	DEPTH_FUNC( kAlways ),
}};

#undef DEPTH_FUNC

//=============================================================================================

struct StencilFunc
{
	sce::Agc::CxDepthStencilControl::StencilFunction m_front;
	sce::Agc::CxDepthStencilControl::StencilFunctionBack m_back;
};

#define STENCIL_FUNC( func ) \
	{ \
		sce::Agc::CxDepthStencilControl::StencilFunction::func, \
		sce::Agc::CxDepthStencilControl::StencilFunctionBack::func \
	}

static const std::array<StencilFunc, 9> sStencilFunc{{
	STENCIL_FUNC( kAlways ),
	STENCIL_FUNC( kLess ),
	STENCIL_FUNC( kLessEqual ),
	STENCIL_FUNC( kEqual ),
	STENCIL_FUNC( kGreaterEqual ),
	STENCIL_FUNC( kGreater ),
	STENCIL_FUNC( kNotEqual ),
	STENCIL_FUNC( kNever ),
	STENCIL_FUNC( kAlways ),
}};

#undef STENCIL_FUNC

//=============================================================================================

struct StencilOp
{
	sce::Agc::CxStencilOpControl::StencilFailOp m_failFront;
	sce::Agc::CxStencilOpControl::StencilFailBackOp m_failBack;
	sce::Agc::CxStencilOpControl::StencilZPassOp m_zPassFront;
	sce::Agc::CxStencilOpControl::StencilZPassBackOp m_zPassBack;
	sce::Agc::CxStencilOpControl::StencilZFailOp m_zFailFront;
	sce::Agc::CxStencilOpControl::StencilZFailBackOp m_zFailBack;
};

#define STENCIL_OP( op ) \
	{ \
		sce::Agc::CxStencilOpControl::StencilFailOp::op, \
		sce::Agc::CxStencilOpControl::StencilFailBackOp::op, \
		sce::Agc::CxStencilOpControl::StencilZPassOp::op, \
		sce::Agc::CxStencilOpControl::StencilZPassBackOp::op, \
		sce::Agc::CxStencilOpControl::StencilZFailOp::op, \
		sce::Agc::CxStencilOpControl::StencilZFailBackOp::op \
	}

static const std::array<StencilOp, 8> sStencilOp{{
	STENCIL_OP( kZero ),
	STENCIL_OP( kKeep ),
	STENCIL_OP( kReplaceTest ),
	STENCIL_OP( kAddWrap ),
	STENCIL_OP( kAddClamp ),
	STENCIL_OP( kSubWrap ),
	STENCIL_OP( kSubClamp ),
	STENCIL_OP( kInvert ),
}};

#undef STENCIL_OP

//=============================================================================================

struct BlendFunc
{
	sce::Agc::CxBlendControl::ColorBlendFunc m_rgbFunc;
	sce::Agc::CxBlendControl::AlphaBlendFunc m_aFunc;
};

#define BLEND_FUNC( func ) \
	{ \
		sce::Agc::CxBlendControl::ColorBlendFunc::func, \
		sce::Agc::CxBlendControl::AlphaBlendFunc::func \
	}

static const std::array<BlendFunc, 5> sBlendFunc{{
	BLEND_FUNC( kAdd ),
	BLEND_FUNC( kSubtract ),
	BLEND_FUNC( kReverseSubtract ),
	BLEND_FUNC( kMin ),
	BLEND_FUNC( kMax ),
}};

#undef BLEND_FUNC

//=============================================================================================

struct BlendFactor
{
	sce::Agc::CxBlendControl::ColorSourceMultiplier m_rgbSrc;
	sce::Agc::CxBlendControl::AlphaSourceMultiplier m_aSrc;
	sce::Agc::CxBlendControl::ColorDestMultiplier m_rgbDst;
	sce::Agc::CxBlendControl::AlphaDestMultiplier m_aDst;
	bool m_usesConst;
};

#define BLEND_FACTOR( rgbFactor, aFactor, usesConst ) \
	{ \
		sce::Agc::CxBlendControl::ColorSourceMultiplier::rgbFactor, \
		sce::Agc::CxBlendControl::AlphaSourceMultiplier::aFactor, \
		sce::Agc::CxBlendControl::ColorDestMultiplier::rgbFactor, \
		sce::Agc::CxBlendControl::AlphaDestMultiplier::aFactor, usesConst \
	}

static const std::array<BlendFactor, 14> sBlendFactor{{
	BLEND_FACTOR( kZero, kZero, false ),
	BLEND_FACTOR( kZero, kZero, false ),
	BLEND_FACTOR( kOne, kOne, false ),
	BLEND_FACTOR( kSrcColor, kSrcColor, false ),
	BLEND_FACTOR( kOneMinusSrcColor, kOneMinusSrcColor, false ),
	BLEND_FACTOR( kSrcAlpha, kSrcAlpha, false ),
	BLEND_FACTOR( kOneMinusSrcAlpha, kOneMinusSrcAlpha, false ),
	BLEND_FACTOR( kDestAlpha, kDestAlpha, false ),
	BLEND_FACTOR( kOneMinusDestAlpha, kOneMinusDestAlpha, false ),
	BLEND_FACTOR( kDestColor, kDestColor, false ),
	BLEND_FACTOR( kOneMinusDestColor, kOneMinusDestColor, false ),
	BLEND_FACTOR( kSrcAlphaSaturate, kOne, false ),
	BLEND_FACTOR( kConstantColor, kConstantColor, true ),
	BLEND_FACTOR( kOneMinusConstantColor, kOneMinusConstantColor, true ),
}};

#undef BLEND_FACTOR

//=============================================================================================

// TODO: (manderson) MSAA?
#define TEXTURE_CAPS_FLAGS \
	(BGFX_CAPS_FORMAT_TEXTURE_2D | BGFX_CAPS_FORMAT_TEXTURE_3D | BGFX_CAPS_FORMAT_TEXTURE_CUBE | BGFX_CAPS_FORMAT_TEXTURE_VERTEX)

#define TEXTURE_CAPS_FLAGS_SRGB \
	(BGFX_CAPS_FORMAT_TEXTURE_2D_SRGB | BGFX_CAPS_FORMAT_TEXTURE_3D_SRGB | BGFX_CAPS_FORMAT_TEXTURE_CUBE_SRGB)

#define TEXTURE_CAPS_FLAGS_FRAMEBUFFER \
	(BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER)

struct TextureFormatInfo
{
	sce::Agc::Core::TypedFormat m_fmt{};
	sce::Agc::Core::TypedFormat m_fmtSrgb{};
	sce::Agc::Core::Swizzle m_swzl{};
	uint32_t m_flags{};
	bool m_convert{};
};

#define TEXTURE_FORMAT(fmt, fmtSrbg, swzl, flags) \
{ \
	sce::Agc::Core::TypedFormat::fmt, \
	sce::Agc::Core::TypedFormat::fmtSrbg, \
	sce::Agc::Core::Swizzle::swzl, \
	flags, \
	false \
}

#define TEXTURE_FORMAT_CONVERT() \
{ \
	sce::Agc::Core::TypedFormat::k8_8_8_8UNorm, \
	sce::Agc::Core::TypedFormat::k8_8_8_8Srgb, \
	sce::Agc::Core::Swizzle::kBGRA_R4S4, \
	TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_SRGB | TEXTURE_CAPS_FLAGS_FRAMEBUFFER, \
	true \
}

#define TEXTURE_FORMAT_CONVERT_FMT(fmt) \
{ \
	sce::Agc::Core::TypedFormat::fmt, \
	sce::Agc::Core::TypedFormat::kLast, \
	sce::Agc::Core::Swizzle::kBGRA_R4S4, \
	TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER, \
	true \
}

#define TEXTURE_FORMAT_UNSUPPORTED() \
{ \
	sce::Agc::Core::TypedFormat::kLast, \
	sce::Agc::Core::TypedFormat::kLast, \
	sce::Agc::Core::Swizzle::kLast, \
	BGFX_CAPS_FORMAT_TEXTURE_NONE, \
	false \
}

static const std::array<TextureFormatInfo, TextureFormat::Enum::Count> sTextureFormat{{
	TEXTURE_FORMAT( kBc1UNorm, kBc1Srgb, kRGB1_R3S34, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_SRGB ),											// BC1
	TEXTURE_FORMAT( kBc2UNorm, kBc2Srgb, kRGBA_R4S4, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_SRGB ),											// BC2
	TEXTURE_FORMAT( kBc3UNorm, kBc3Srgb, kRGBA_R4S4, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_SRGB ),											// BC3
	TEXTURE_FORMAT( kBc4UNorm, kLast, kR001_R1S1, TEXTURE_CAPS_FLAGS ),																			// BC4
	TEXTURE_FORMAT( kBc5UNorm, kLast, kRG01_R2S24, TEXTURE_CAPS_FLAGS ),																		// BC5
	TEXTURE_FORMAT( kBc6SFloat, kLast, kRGB1_R3S34, TEXTURE_CAPS_FLAGS ),																		// BC6H
	TEXTURE_FORMAT( kBc7UNorm, kBc7Srgb, kRGBA_R4S4, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_SRGB ),											// BC7
	TEXTURE_FORMAT_CONVERT(),																													// ETC1
	TEXTURE_FORMAT_CONVERT(),																													// ETC2
	TEXTURE_FORMAT_CONVERT(),																													// ETC2A
	TEXTURE_FORMAT_CONVERT(),																													// ETC2A1
	TEXTURE_FORMAT_CONVERT(),																													// PTC12
	TEXTURE_FORMAT_CONVERT(),																													// PTC14
	TEXTURE_FORMAT_CONVERT(),																													// PTC12A
	TEXTURE_FORMAT_CONVERT(),																													// PTC14A
	TEXTURE_FORMAT_CONVERT(),																													// PTC22
	TEXTURE_FORMAT_CONVERT(),																													// PTC24
	TEXTURE_FORMAT_CONVERT(),																													// ATC
	TEXTURE_FORMAT_CONVERT(),																													// ATCE
	TEXTURE_FORMAT_CONVERT(),																													// ATCI
	TEXTURE_FORMAT_CONVERT(),																													// ASTC4x4
	TEXTURE_FORMAT_CONVERT(),																													// ASTC5x5
	TEXTURE_FORMAT_CONVERT(),																													// ASTC6x6
	TEXTURE_FORMAT_CONVERT(),																													// ASTC8x5
	TEXTURE_FORMAT_CONVERT(),																													// ASTC8x6
	TEXTURE_FORMAT_CONVERT(),																													// ASTC10x5
	TEXTURE_FORMAT_UNSUPPORTED(),																												// Unknown
	TEXTURE_FORMAT_UNSUPPORTED(),																												// R1
	TEXTURE_FORMAT( k8UNorm, k8Srgb, k000R_R1S14, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_SRGB | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),				// A8
	TEXTURE_FORMAT( k8UNorm, k8Srgb, kR001_R1S1, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_SRGB | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),				// R8
	TEXTURE_FORMAT( k8SInt, kLast, kR001_R1S1, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),											// R8I
	TEXTURE_FORMAT( k8UInt, kLast, kR001_R1S1, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),											// R8U
	TEXTURE_FORMAT( k8SNorm, kLast, kR001_R1S1, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),											// R8S
	TEXTURE_FORMAT( k16UNorm, kLast, kR001_R1S1, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),											// R16
	TEXTURE_FORMAT( k16SInt, kLast, kR001_R1S1, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),											// R16I
	TEXTURE_FORMAT( k16UInt, kLast, kR001_R1S1, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),											// R16U
	TEXTURE_FORMAT( k16Float, kLast, kR001_R1S1, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),											// R16F
	TEXTURE_FORMAT( k16SNorm, kLast, kR001_R1S1, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),											// R16S
	TEXTURE_FORMAT( k32SInt, kLast, kR001_R1S1, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),											// R321
	TEXTURE_FORMAT( k32UInt, kLast, kR001_R1S1, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),											// R32U
	TEXTURE_FORMAT( k32Float, kLast, kR001_R1S1, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),											// R32F
	TEXTURE_FORMAT( k8_8UNorm, k8_8Srgb, kRG01_R2S24, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_SRGB | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),			// RG8
	TEXTURE_FORMAT( k8_8SInt, kLast, kRG01_R2S24, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),										// RG8I
	TEXTURE_FORMAT( k8_8UInt, kLast, kRG01_R2S24, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),										// RG8U
	TEXTURE_FORMAT( k8_8SNorm, kLast, kRG01_R2S24, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),										// RG8S
	TEXTURE_FORMAT( k16_16UNorm, kLast, kRG01_R2S24, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),										// RG16
	TEXTURE_FORMAT( k16_16SInt, kLast, kRG01_R2S24, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),										// RG16I
	TEXTURE_FORMAT( k16_16UInt, kLast, kRG01_R2S24, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),										// RG16U
	TEXTURE_FORMAT( k16_16Float, kLast, kRG01_R2S24, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),										// RG16F
	TEXTURE_FORMAT( k16_16SNorm, kLast, kRG01_R2S24, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),										// RG16S
	TEXTURE_FORMAT( k32_32SInt, kLast, kRG01_R2S24, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),										// RG321
	TEXTURE_FORMAT( k32_32UInt, kLast, kRG01_R2S24, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),										// RG32U
	TEXTURE_FORMAT( k32_32Float, kLast, kRG01_R2S24, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),										// RG32F
	TEXTURE_FORMAT_CONVERT(),																													// RGB8
	TEXTURE_FORMAT_CONVERT_FMT( k8_8_8_8SInt ),																									// RGB8I
	TEXTURE_FORMAT_CONVERT_FMT( k8_8_8_8UInt ),																									// RGB8U
	TEXTURE_FORMAT_CONVERT_FMT( k8_8_8_8SNorm ),																								// RGB8S
	TEXTURE_FORMAT( k9_9_9_5Float, kLast, kRGBA_R4S4, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),									// RGB9E5F
	TEXTURE_FORMAT( k8_8_8_8UNorm, k8_8_8_8Srgb, kBGRA_R4S4, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_SRGB | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),	// BGRA8
	TEXTURE_FORMAT( k8_8_8_8UNorm, k8_8_8_8Srgb, kRGBA_R4S4, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_SRGB | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),	// RGBA8
	TEXTURE_FORMAT( k8_8_8_8SInt, kLast, kRGBA_R4S4, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),										// RGBA8I
	TEXTURE_FORMAT( k8_8_8_8UInt, kLast, kRGBA_R4S4, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),										// RGBA8U
	TEXTURE_FORMAT( k8_8_8_8SNorm, kLast, kRGBA_R4S4, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),									// RGBA8S
	TEXTURE_FORMAT( k16_16_16_16UNorm, kLast, kRGBA_R4S4, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),								// RGBA16
	TEXTURE_FORMAT( k16_16_16_16SInt, kLast, kRGBA_R4S4, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),									// RGBA16I
	TEXTURE_FORMAT( k16_16_16_16UInt, kLast, kRGBA_R4S4, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),									// RGBA16U
	TEXTURE_FORMAT( k16_16_16_16Float, kLast, kRGBA_R4S4, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),								// RGBA16F
	TEXTURE_FORMAT( k16_16_16_16SNorm, kLast, kRGBA_R4S4, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),								// RGBA16S
	TEXTURE_FORMAT( k32_32_32_32SInt, kLast, kRGBA_R4S4, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),									// RGBA32I
	TEXTURE_FORMAT( k32_32_32_32UInt, kLast, kRGBA_R4S4, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),									// RGBA32U
	TEXTURE_FORMAT( k32_32_32_32Float, kLast, kRGBA_R4S4, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),								// RGBA32F
	TEXTURE_FORMAT( k5_6_5UNorm, kLast, kRGB1_R3S34, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),										// R5G6B5
	TEXTURE_FORMAT( k4_4_4_4UNorm, kLast, kRGBA_R4S4, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),									// RGBA4
	TEXTURE_FORMAT( k5_5_5_1UNorm, kLast, kRGBA_R4S4, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),									// RGB5A1
	TEXTURE_FORMAT( k10_10_10_2UNorm, kLast, kRGBA_R4S4, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),									// RGB10A2
	TEXTURE_FORMAT( k11_11_10Float, kLast, kRGB1_R3S34, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),									// RG11B10F

	// TODO: (manderson) Depth formats.
	TEXTURE_FORMAT_UNSUPPORTED(),																												// UnknownDepth
	TEXTURE_FORMAT( k32Float, kLast, kR001_R1S1, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),											// D16
	TEXTURE_FORMAT( k32Float, kLast, kR001_R1S1, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),											// D24
	TEXTURE_FORMAT( k32Float, kLast, kR001_R1S1, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),											// D24S8
	TEXTURE_FORMAT( k32Float, kLast, kR001_R1S1, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),											// D32
	TEXTURE_FORMAT( k32Float, kLast, kR001_R1S1, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),											// D16F
	TEXTURE_FORMAT( k32Float, kLast, kR001_R1S1, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),											// D24F
	TEXTURE_FORMAT( k32Float, kLast, kR001_R1S1, TEXTURE_CAPS_FLAGS | TEXTURE_CAPS_FLAGS_FRAMEBUFFER ),											// D32F
	TEXTURE_FORMAT_UNSUPPORTED(),																												// D0S8
}};

#undef TEXTURE_FORMAT
#undef TEXTURE_FORMAT_CONVERT
#undef TEXTURE_FORMAT_CONVERT_FMT
#undef TEXTURE_FORMAT_UNSUPPORTED

//=============================================================================================

#define TEXTURE_WRAP_MODE( mode ) \
		sce::Agc::Core::Sampler::WrapMode::mode

static const std::array<sce::Agc::Core::Sampler::WrapMode, 4> sWrapMode{{
	TEXTURE_WRAP_MODE( kWrap ),
	TEXTURE_WRAP_MODE( kMirror ),
	TEXTURE_WRAP_MODE( kClampLastTexel ),
	TEXTURE_WRAP_MODE( kClampBorder ),
}};

#undef TEXTURE_WRAP_MODE

//=============================================================================================

#define TEXTURE_FILTER_MODE( mode ) \
		sce::Agc::Core::Sampler::FilterMode::mode

static const std::array<sce::Agc::Core::Sampler::FilterMode, 3> sFilterMode{{
	TEXTURE_FILTER_MODE( kBilinear ),
	TEXTURE_FILTER_MODE( kPoint ),
	TEXTURE_FILTER_MODE( kAnisoBilinear ),
}};

#undef TEXTURE_FILTER_MODE

//=============================================================================================

#define TEXTURE_MIP_FILTER_MODE( mode ) \
		sce::Agc::Core::Sampler::MipFilterMode::mode

static const std::array<sce::Agc::Core::Sampler::MipFilterMode, 2> sMipFilterMode{{
	TEXTURE_MIP_FILTER_MODE( kLinear ),
	TEXTURE_MIP_FILTER_MODE( kPoint ),
}};

#undef TEXTURE_MIP_FILTER_MODE

//=============================================================================================

#define TEXTURE_DEPTH_COMPARE_MODE( mode ) \
		sce::Agc::Core::Sampler::DepthCompare::mode

static const std::array<sce::Agc::Core::Sampler::DepthCompare, 9> sDepthCompareMode{{
	TEXTURE_DEPTH_COMPARE_MODE( kNever ), // not used
	TEXTURE_DEPTH_COMPARE_MODE( kLess ),
	TEXTURE_DEPTH_COMPARE_MODE( kLessEqual ),
	TEXTURE_DEPTH_COMPARE_MODE( kEqual ),
	TEXTURE_DEPTH_COMPARE_MODE( kGreaterEqual ),
	TEXTURE_DEPTH_COMPARE_MODE( kGreater ),
	TEXTURE_DEPTH_COMPARE_MODE( kNotEqual ),
	TEXTURE_DEPTH_COMPARE_MODE( kNever ),
	TEXTURE_DEPTH_COMPARE_MODE( kAlways ),
}};

#undef TEXTURE_DEPTH_COMPARE_MODE

//=============================================================================================

static RendererContextAGC* sRendererAGC;

//=============================================================================================

RendererContextAGC::Resource::Resource()
{
	mInflightCounter = std::make_shared<InflightCounter>();
}

//=============================================================================================

void RendererContextAGC::Resource::setInflight()
{
	if (mInflightCounter->mFrameClock != sRendererAGC->mFrameClock)
	{
		mInflightCounter->mCount++;
		mInflightCounter->mFrameClock = sRendererAGC->mFrameClock;

		DisplayResources& displayRes = *(sRendererAGC->mFrameState.mDisplayRes);
		displayRes.mInflightCounters.push_back(mInflightCounter);
	}
}

//=============================================================================================

bool RendererContextAGC::Shader::create(const Memory& mem)
{
	// Run constructor to reset object.
	new (this) Shader{};

	bx::MemoryReader reader{mem.data, mem.size};

	uint32_t magic{};
	bx::read(&reader, magic);

	uint8_t fragmentBit{};
	if (isShaderType(magic, 'F'))
	{
		fragmentBit = kUniformFragmentBit;
	}
	else if (!isShaderType(magic, 'V') &&
			 !isShaderType(magic, 'V'))
	{
		BGFX_FATAL(false, Fatal::InvalidShader, "Unknown shader format %x.", magic);
		return false;
	}


	uint32_t hashIn{};
	bx::read(&reader, hashIn);

	uint32_t hashOut{};
	if (isShaderVerLess(magic, 6) )
	{
		hashOut = hashIn;
	}
	else
	{
		bx::read(&reader, hashOut);
	}

	uint16_t count{};
	bx::read(&reader, count);

	BX_TRACE("%s Shader consts %d"
		, getShaderTypeName(magic)
		, count
		);

	m_numPredefined = 0;

	mNumSamplers = 0;
	if (count > 0)
	{
		for (uint32_t ii = 0; ii < count; ++ii)
		{
			uint8_t nameSize{};
			bx::read(&reader, nameSize);

			char* name = (char*)alloca(nameSize+1);
			bx::read(&reader, name, nameSize);
			name[nameSize] = '\0';

			uint8_t type{};
			bx::read(&reader, type);

			uint8_t num{};
			bx::read(&reader, num);

			uint16_t regIndex{};
			bx::read(&reader, regIndex);

			uint16_t regCount{};
			bx::read(&reader, regCount);

			uint8_t texComponent{};
			uint8_t texDimension{};
			if (!isShaderVerLess(magic, 8))
			{
				bx::read(&reader, texComponent);
				bx::read(&reader, texDimension);
			}

			uint16_t texFormat{};
			if (!isShaderVerLess(magic, 10) )
			{
				bx::read(&reader, texFormat);
			}

			const char* kind{"invalid"};

			PredefinedUniform::Enum const predefined{nameToPredefinedUniformEnum(name)};
			if (predefined != PredefinedUniform::Count)
			{
				kind = "predefined";
				m_predefined[m_numPredefined].m_loc = regIndex;
				m_predefined[m_numPredefined].m_count = regCount;
				m_predefined[m_numPredefined].m_type = uint8_t(predefined | fragmentBit);
				m_numPredefined++;
			}
			else if ((kUniformSamplerBit & type) == 0)
			{
				const UniformRegInfo* info = sRendererAGC->mUniformReg.find(name);
				BX_WARN(info != nullptr, "User defined uniform '%s' is not found, it won't be set.", name);

				if (info != nullptr)
				{
					if (mUniforms == nullptr)
					{
						mUniforms = UniformBuffer::create(4<<10);
					}

					kind = "user";
					mUniforms->writeUniformHandle((UniformType::Enum)(type | fragmentBit), regIndex, info->m_handle, regCount);
				}
			}
			else
			{
				kind = "sampler";
				mNumSamplers++;
				// TODO: (manderson) Capture samplers?
			}

			BX_TRACE("\t%s: %s (%s), num %2d, r.index %3d, r.count %2d"
				, kind
				, name
				, getUniformTypeName(UniformType::Enum(type&~kUniformMask))
				, num
				, regIndex
				, regCount
			);
			BX_UNUSED(kind);
		}

		if (mUniforms != nullptr)
		{
			mUniforms = UniformBuffer::finishAndTrim(mUniforms);
		}
	}

	uint32_t shaderSize{};
	bx::read(&reader, shaderSize);

	const uint32_t* source = reinterpret_cast<const uint32_t*>(reader.getDataPtr());
	bx::skip(&reader, shaderSize + 1);

	mCompiledCode = allocDmem(sce::Agc::SizeAlign(shaderSize, sce::Agc::Alignment::kShaderCode));
	bx::memCopy(mCompiledCode, source, shaderSize);
	SceShaderBinaryHandle const binaryHandle = sceShaderGetBinaryHandle(mCompiledCode);
	void* const header = (void*)sceShaderGetProgramHeader(binaryHandle);
	const void* const program = sceShaderGetProgram(binaryHandle);
	SceError const error = sce::Agc::createShader(&mShader, header, program);
	if (error != SCE_OK)
	{
		freeDmem(mCompiledCode);
		return false;
	}

	uint8_t numAttrs{};
	bx::read(&reader, numAttrs);

	//bool isInstanced[numAttrs];
	//bool atLeastOneInstanced = false;

	std::fill(mAttributes.begin(), mAttributes.end(), Attrib::Count);

	for (uint32_t ii = 0; ii < numAttrs; ++ii)
	{
		/*uint8_t slotPlusInstanceFlag;
		bx::read(&reader, slotPlusInstanceFlag);

		constexpr uint8_t IS_INSTANCE_FLAG = 128;
		if (slotPlusInstanceFlag & IS_INSTANCE_FLAG) {
			isInstanced[ii] = true;
			atLeastOneInstanced = true;
		}
		uint8_t const slot = slotPlusInstanceFlag & ~IS_INSTANCE_FLAG;*/

		uint16_t id;
		bx::read(&reader, id);

		Attrib::Enum attr = idToAttrib(id);

		if (Attrib::Count != attr)
		{
			mAttributes[mNumAttributes] = attr;
			mNumAttributes++;
		}
	}

	bx::read(&reader, mUniformBufferSize);
	if (mUniformBufferSize > 0)
	{
		mUniformBuffer = (uint8_t*)BX_ALLOC(g_allocator, mUniformBufferSize);
	}

	return true;
}

//=============================================================================================

void RendererContextAGC::Shader::destroy()
{
	// TODO: (manderson) destroy shader.
	
	// Run destructor.
	this->~Shader();
}

//=============================================================================================

bool RendererContextAGC::Program::create(ShaderHandle const vertexShaderHandle, ShaderHandle const fragmentShaderHandle)
{
	// Run constructor to reset object.
	new (this) Program{};

	mVertexShaderHandle = vertexShaderHandle;
	mFragmentShaderHandle = fragmentShaderHandle;
	return true;
}

//=============================================================================================

void RendererContextAGC::Program::destroy()
{
	// TODO: (manderson) destroy program.

	// Run destructor.
	this->~Program();
}

//=============================================================================================

bool RendererContextAGC::Buffer::update(uint32_t const offset, uint32_t const size, const uint8_t* const data)
{
	// If the buffer is not inflight and it's size hasn't changed we can update it's contents directly,
	// otherwise we need to modify a copy of the current buffer and discard the current buffer when it's
	// not inflight.
	uint32_t const requestSize = offset + size;
	uint32_t const newSize = mSize > requestSize ? mSize : requestSize;
	uint8_t* newBuffer = mBuffer;
	if (mInflightCounter->mCount > 0 || newSize > mSize)
	{		
		// Allocate new buffer.
		newBuffer = allocDmem({newSize, 16});
		if (newBuffer == nullptr)
		{
			return false;
		}

		// Copy previous contents, don't bother with portion we are going to update.
		if (mBuffer != nullptr)
		{
			uint32_t const beforeSize = mSize < offset ? mSize : offset;
			if (beforeSize > 0)
			{
				memcpy(newBuffer, mBuffer, beforeSize);
			}
			uint32_t const afterSize = mSize > requestSize ? (mSize - requestSize) : 0;
			if (afterSize > 0)
			{
				memcpy(newBuffer + requestSize, mBuffer + requestSize, afterSize);
			}
		}	
	}

	// Update buffer.
	memcpy(newBuffer + offset, data, size);

	// If we allocated a new buffer queue to old one for delete once it's not inflight.
	if (newBuffer != mBuffer)
	{
		if (mBuffer != nullptr)
		{
			sRendererAGC->mDestroyList.push_back([inflightCounter=mInflightCounter,buffer=mBuffer]() mutable {
				if (inflightCounter->mCount == 0)
				{
					freeDmem(buffer);
					return true;
				}
				return false;
			});
		}
		mInflightCounter = std::make_shared<InflightCounter>();
		mBuffer = newBuffer;
	}

	// Update size.
	mSize = newSize;

	return true;
}

//=============================================================================================

void RendererContextAGC::Buffer::destroy()
{
	if (mBuffer != nullptr)
	{
		sRendererAGC->mDestroyList.push_back([inflightCounter=mInflightCounter,buffer=mBuffer]() mutable {
			if (inflightCounter->mCount == 0)
			{
				freeDmem(buffer);
				return true;
			}
			return false;
		});
	}
	mBuffer = nullptr;
	mSize = 0;
}

//=============================================================================================

bool RendererContextAGC::IndexBuffer::create(uint16_t const flags, uint32_t const size, const uint8_t* const data)
{
	// Run constructor to reset object.
	new (this) IndexBuffer{};

	mFlags = flags;
	mSize = 0;
	if (data != nullptr)
	{
		return update(0, size, data);
	}
	return true;
}

//=============================================================================================

void RendererContextAGC::IndexBuffer::destroy()
{
	Buffer::destroy();
	mFlags = 0;

	// Run destructor.
	this->~IndexBuffer();
}

//=============================================================================================

bool RendererContextAGC::VertexBuffer::create(VertexLayoutHandle const layoutHandle, uint16_t const flags, uint32_t const size, const uint8_t* const data)
{
	// Run constructor to reset object.
	new (this) VertexBuffer{};

	mLayoutHandle = layoutHandle;
	mSize = 0;
	if (data != nullptr)
	{
		return update(0, size, data);
	}
	return true;
}

//=============================================================================================

void RendererContextAGC::VertexBuffer::destroy()
{
	Buffer::destroy();
	mLayoutHandle = {kInvalidHandle};

	// Run destructor.
	this->~VertexBuffer();
}

//=============================================================================================

bool RendererContextAGC::Texture::tileSurface(void* const tiledSurface, const sce::Agc::Core::TextureSpec& tiledSpec, uint32_t const arraySlice, uint32_t const mipLevel, const void* const untiledSurface, uint32_t const untiledSize, bimg::TextureFormat::Enum const untiledFormat, uint32_t untiledBlockPitch, const sce::AgcGpuAddress::SurfaceRegion& region)
{
	SceError ret;

	sce::AgcGpuAddress::SurfaceDescription desc{};
	ret = sce::Agc::Core::translate(&desc, &tiledSpec);
	if (ret != SCE_OK) {
		return false;
	}

	// Verify region.
	if ((region.m_left % desc.m_texelsPerElementWide) != 0 ||
		(region.m_top % desc.m_texelsPerElementTall) != 0 ||
		(region.m_right % desc.m_texelsPerElementWide) != 0 ||
		(region.m_bottom % desc.m_texelsPerElementTall) != 0)
	{
		return false;
	}

	sce::AgcGpuAddress::SurfaceSummary summary{};
	ret = sce::AgcGpuAddress::computeSurfaceSummary(&summary, &desc);
	if (ret != SCE_OK) {
		return false;
	}

	// NOTE: (manderson) I am assuming that if pitch is specified it is block pitch for compressed
	// textures.
	uint32_t const width = region.m_right - region.m_left;
	uint32_t const height = region.m_bottom - region.m_top;
	uint32_t const depth = region.m_back - region.m_front;

	// Convert texture format if required.
	const bimg::ImageBlockInfo& bgraBlockInfo = bimg::getBlockInfo(bimg::TextureFormat::BGRA8);
	const bimg::ImageBlockInfo& blockInfo = bimg::getBlockInfo(untiledFormat);
	const TextureFormatInfo& tf = sTextureFormat[untiledFormat];
	uint32_t pitch = untiledBlockPitch == UINT16_MAX ? (width / blockInfo.blockWidth * blockInfo.blockSize) : untiledBlockPitch;
	uint32_t size = bx::uint32_min(height / blockInfo.blockHeight * pitch * depth, untiledSize);
	uint8_t* ptr = (uint8_t*)untiledSurface;
	sce::AgcGpuAddress::SurfaceRegion adjustedRegion{region};
	if (tf.m_convert)
	{
		// NOTE: (manderson) Conversion routine doesn't support 3d textures.
		// NOTE: (manderson) Conversion doesn't support variable source pitch...
		if (depth > 1 || untiledBlockPitch != UINT16_MAX)
		{
			return false;
		}

		// NOTE: (manderson) For some texture formats that we convert (Compressed formats) the slice width, height, and depth cannot
		// be below 4, after we convert tileSurface will fail if the mip size isn't orig >> mipLevel, so pass the expected width and height to tileSurface.
		sce::AgcGpuAddress::SurfaceRegion const maxRegion{
			0,
			0,
			0, 
			bx::max<uint32_t>(tiledSpec.m_width >> mipLevel, 1),
			bx::max<uint32_t>(tiledSpec.m_height >> mipLevel, 1),
			bx::max<uint32_t>(tiledSpec.m_depth >> mipLevel, 1)
		};
		adjustedRegion = {
			bx::min<uint32_t>(region.m_left, maxRegion.m_right),
			bx::min<uint32_t>(region.m_top, maxRegion.m_bottom),
			bx::min<uint32_t>(region.m_front, maxRegion.m_back),
			bx::min<uint32_t>(region.m_right, maxRegion.m_right),
			bx::min<uint32_t>(region.m_bottom, maxRegion.m_bottom),
			bx::min<uint32_t>(region.m_back, maxRegion.m_back)
		};
		if ((adjustedRegion.m_right - adjustedRegion.m_left) == 0 ||
			(adjustedRegion.m_bottom - adjustedRegion.m_top) == 0 ||
			(adjustedRegion.m_back - adjustedRegion.m_front) == 0)
		{
			BX_FREE(g_allocator, ptr);
			return false;
		}

		pitch = width / bgraBlockInfo.blockWidth * bgraBlockInfo.blockSize;
		size = height / bgraBlockInfo.blockHeight * pitch * depth;
		ptr = (uint8_t*)BX_ALLOC(g_allocator, size);
		bimg::imageDecodeToBgra8(g_allocator,
			ptr,
			untiledSurface,
			width,
			height,
			pitch,
			untiledFormat);
	}

	// Calc element region (an element is the sce equivelant for block).
	sce::AgcGpuAddress::SurfaceRegion elementRegion{
		adjustedRegion.m_left / desc.m_texelsPerElementWide,
		adjustedRegion.m_top / desc.m_texelsPerElementTall,
		adjustedRegion.m_front,
		adjustedRegion.m_right / desc.m_texelsPerElementWide,
		adjustedRegion.m_bottom / desc.m_texelsPerElementTall,
		adjustedRegion.m_back
	};

	// Calc element row & slice pitch, this assumes the pitch is for a row of elements
	// (texels for uncompressed images, blocks for compressed).
	uint32_t const elementRowPitch = pitch >> desc.m_bytesPerElementLog2;
	uint32_t const elementSlicePitch = (elementRegion.m_bottom - elementRegion.m_top) * elementRowPitch;

	// Do it!
	sce::Agc::SizeAlign sizeAlign = sce::Agc::Core::getSize(&tiledSpec);
	ret = sce::AgcGpuAddress::tileSurfaceRegionFromPaddedBuffer(
		tiledSurface,
		sizeAlign.m_size,
		ptr,
		size,
		&summary,
		&elementRegion,
		mipLevel,
		arraySlice,
		elementRowPitch,
		elementSlicePitch);
	if (ptr != untiledSurface)
	{
		BX_FREE(g_allocator, ptr);
	}
	if (ret != SCE_OK) {
		return false;
	}

	return true;
}

//=============================================================================================

void RendererContextAGC::Texture::setSampler(sce::Agc::Core::Sampler& sampler, uint64_t const flags)
{
	auto const u = sWrapMode[(flags & BGFX_SAMPLER_U_MASK) >> BGFX_SAMPLER_U_SHIFT];
	auto const v = sWrapMode[(flags & BGFX_SAMPLER_V_MASK) >> BGFX_SAMPLER_V_SHIFT];
	auto const w = sWrapMode[(flags & BGFX_SAMPLER_W_MASK) >> BGFX_SAMPLER_W_SHIFT];
	auto const mag = sFilterMode[(flags & BGFX_SAMPLER_MAG_MASK) >> BGFX_SAMPLER_MAG_SHIFT];
	auto const min = sFilterMode[(flags & BGFX_SAMPLER_MIN_MASK) >> BGFX_SAMPLER_MIN_SHIFT];
	auto const mip = sMipFilterMode[(flags & BGFX_SAMPLER_MIP_MASK) >> BGFX_SAMPLER_MIP_SHIFT];
	auto const compare = sDepthCompareMode[(flags & BGFX_SAMPLER_COMPARE_MASK) >> BGFX_SAMPLER_COMPARE_SHIFT];

	auto border = sce::Agc::Core::Sampler::BorderColor::kOpaqueBlack;
	uint32_t borderIndex = 0;
	if ((flags & BGFX_SAMPLER_U_BORDER) == BGFX_SAMPLER_U_BORDER ||
		(flags & BGFX_SAMPLER_V_BORDER) == BGFX_SAMPLER_V_BORDER ||
		(flags & BGFX_SAMPLER_W_BORDER) == BGFX_SAMPLER_W_BORDER)
	{
		border = sce::Agc::Core::Sampler::BorderColor::kFromTable;
		borderIndex = (flags & BGFX_SAMPLER_BORDER_COLOR_MASK) >> BGFX_SAMPLER_BORDER_COLOR_SHIFT;
	}

	sampler.init()
		.setWrapMode(u, v, w)
		.setXyFilterMode(mag, min)
		.setMipFilterMode(mip)
		.setDepthCompareFunction(compare)
		.setBorderColor(border)
		.setBorderColorTableIndex(borderIndex)
		.setZFilterMode(sce::Agc::Core::Sampler::ZFilterMode::kLinear)
		.setAnisotropyRatio(sce::Agc::Core::Sampler::AnisotropyRatio::k16);
}

//=============================================================================================

bool RendererContextAGC::Texture::create(uint64_t const flags, uint32_t const size, const uint8_t* const data, uint8_t const mipSkip)
{
	// Run constructor to reset object.
	new (this) Texture{};

	// NOTE: (manderson) Texture is valid if mBuffer != nullptr.

	bimg::ImageContainer imageContainer;
	if (bimg::imageParse(imageContainer, data, size))
	{
		uint8_t const startLod = bx::min<uint8_t>(mipSkip, imageContainer.m_numMips-1);

		bimg::TextureInfo ti;
		bimg::imageGetSize( &ti
			, uint16_t(imageContainer.m_width>>startLod)
			, uint16_t(imageContainer.m_height>>startLod)
			, uint16_t(imageContainer.m_depth>>startLod)
			, imageContainer.m_cubeMap
			, 1 < imageContainer.m_numMips
			, imageContainer.m_numLayers
			, imageContainer.m_format );
		ti.numMips = bx::min<uint8_t>(imageContainer.m_numMips-startLod, ti.numMips);

		bool const srgb = (flags & BGFX_TEXTURE_SRGB) != 0;
		bool const rt = (flags & BGFX_TEXTURE_RT) != 0;
		bool const depth = bimg::isDepth(ti.format);

		const TextureFormatInfo& tf = sTextureFormat[ti.format];
		sce::Agc::Core::TypedFormat const typedFormat = srgb ? tf.m_fmtSrgb : tf.m_fmt;
		if (typedFormat == sce::Agc::Core::TypedFormat::kLast)
		{
			mTexture.init(); // blank texture.
			return false;
		}

		mSpec.init();
		mSpec.m_format = sce::Agc::Core::DataFormat( { typedFormat, tf.m_swzl } );
		if (ti.cubeMap)
		{
			mSpec.m_type = sce::Agc::Core::Texture::Type::kCubemap;
			mSpec.m_numSlices = 6 * ti.numLayers;
			mSpec.m_depth = 1;
		}
		else if (imageContainer.m_depth > 1)
		{
			mSpec.m_type = sce::Agc::Core::Texture::Type::k3d;
			mSpec.m_numSlices = 1;
			mSpec.m_depth = ti.depth;
		}
		else
		{
			mSpec.m_type = ti.numLayers > 1 ? sce::Agc::Core::Texture::Type::k2dArray : sce::Agc::Core::Texture::Type::k2d;
			mSpec.m_numSlices = ti.numLayers;
			mSpec.m_depth = 1;
		}
		mSpec.m_width = ti.width;
		mSpec.m_height = ti.height;
		mSpec.m_tileMode = depth ? sce::Agc::Core::Texture::TileMode::kDepth : (rt ? sce::Agc::Core::Texture::TileMode::kRenderTarget : sce::Agc::Core::Texture::TileMode::kLinear); // TODO: (manderson) Use block tile mode
		mSpec.m_numMips = ti.numMips;

		sce::Agc::SizeAlign const alignedSize = sce::Agc::Core::getSize(&mSpec);
		mBuffer = allocDmem(alignedSize);
		if (mBuffer == nullptr)
		{
			mTexture.init(); // blank texture.
			return false;
		}

		mSpec.m_dataAddress = mBuffer;
		SceError error = sce::Agc::Core::initialize(&mTexture, &mSpec);
		if (error != SCE_OK)
		{
			mTexture.init(); // blank texture.
			freeDmem(mBuffer);
			mBuffer = nullptr;
			return false;
		}

		for (uint32_t slice = 0; slice < mSpec.m_numSlices; slice++)
		{
			for (uint32_t mip = 0; mip < mSpec.m_numMips; mip++)
			{
				bimg::ImageMip imgMip;
				if (bimg::imageGetRawData(imageContainer, slice, mip+startLod, data, size, imgMip))
				{
					// Verify format.
					if (imgMip.m_format != ti.format)
					{
						mTexture.init();
						return false;
					}

					// Tile surface to buffer.
					sce::AgcGpuAddress::SurfaceRegion const region{
						0,
						0,
						0,
						imgMip.m_width,
						imgMip.m_height,
						imgMip.m_depth
					};
					if (!tileSurface(mBuffer, mSpec, slice, mip, imgMip.m_data, imgMip.m_size, imgMip.m_format, UINT16_MAX, region))
					{
						mTexture.init(); // blank texture.
						freeDmem(mBuffer);
						mBuffer = nullptr;
						return false;
					}
				}
			}
		}

		// Set default sampler.
		setSampler(mSampler, flags);

		// Create stencil buffer if format requires one.
		if (ti.format == bimg::TextureFormat::D24S8)
		{
			sce::Agc::Core::DepthRenderTargetSpec drtSpec{};
			drtSpec.init();
			drtSpec.m_width = ti.width;
			drtSpec.m_height = ti.height;
			drtSpec.m_stencilFormat = sce::Agc::CxDepthRenderTarget::StencilFormat::k8UInt;
			sce::Agc::SizeAlign const stencilSize = sce::Agc::Core::getSize(&drtSpec, sce::Agc::Core::DepthRenderTargetComponent::kStencil);
			mStencilBuffer = allocDmem(sce::Agc::SizeAlign(stencilSize.m_size, stencilSize.m_align));
			if (mStencilBuffer == nullptr)
			{
				mTexture.init(); // blank texture.
				freeDmem(mBuffer);
				mBuffer = nullptr;
				return false;
			}
		}

		mFlags = flags;
		mFormat = ti.format;

		return true;
	}
	return false;
}

//=============================================================================================
bool RendererContextAGC::Texture::update(uint8_t const slice, uint8_t const mip, const Rect& rect, uint16_t const z, uint16_t const depth, uint16_t const pitch, uint32_t const size, const uint8_t* const data)
{
	// Was texture initialized successfully?
	if (mBuffer == nullptr)
	{
		return false;
	}

	// If the texture is not inflight we can update it's contents directly, otherwise we need to
	// modify a copy of the current texture and discard the current buffer when it's not inflight.
	uint8_t* newBuffer = mBuffer;
	if (mInflightCounter->mCount != 0)
	{
		sce::Agc::SizeAlign const alignedSize = sce::Agc::Core::getSize(&mSpec);
		newBuffer = allocDmem(alignedSize);
		if (newBuffer == nullptr)
		{
			return false;
		}
		mTexture.setDataAddress(newBuffer);

		// Copy existing contents, if we are updating the whole texture we don't need to do this.
		// TODO: (manderson) investigate copying only region that isn't updated, this is made difficult
		// by the fact that the existing buffer is tiled.
		bool isFullMip = rect.m_x == 0 && rect.m_width == bx::max<uint32_t>(mSpec.m_width >> mip, 1) &&
						 rect.m_y == 0 && rect.m_height == bx::max<uint32_t>(mSpec.m_height >> mip, 1) &&
						 z == 0 && depth == bx::max<uint32_t>(mSpec.m_depth >> mip, 1);
		if (!isFullMip)
		{
			memcpy(newBuffer, mBuffer, alignedSize.m_size);
		}
	}

	// Tile update rect into buffer.
	sce::AgcGpuAddress::SurfaceRegion const region{
		(uint32_t)rect.m_x,
		(uint32_t)rect.m_y,
		(uint32_t)z,
		(uint32_t)rect.m_x + (uint32_t)rect.m_width,
		(uint32_t)rect.m_y + (uint32_t)rect.m_height,
		(uint32_t)z + depth
	};
	if (!tileSurface(newBuffer, mSpec, slice, mip, data, size, mFormat, pitch, region))
	{
		if (newBuffer != mBuffer)
		{
			freeDmem(newBuffer);
		}
		return false;
	}

	// Discard old buffer if we needed to allocated a new one (old buffer is inflight)
	if (newBuffer != mBuffer)
	{
		sRendererAGC->mDestroyList.push_back([inflightCounter=mInflightCounter,buffer=mBuffer]() mutable {
			if (inflightCounter->mCount == 0)
			{
				freeDmem(buffer);
				return true;
			}
			return false;
		});
		mInflightCounter = std::make_shared<InflightCounter>();
		mBuffer = newBuffer;
	}

	return true;
}

//=============================================================================================

void RendererContextAGC::Texture::destroy()
{
	if (mBuffer != nullptr || mStencilBuffer != nullptr)
	{
		sRendererAGC->mDestroyList.push_back([inflightCounter=mInflightCounter,textureBuffer=mBuffer,stencilBuffer=mStencilBuffer]() mutable {
			if (inflightCounter->mCount == 0)
			{
				if (textureBuffer != nullptr)
				{
					freeDmem(textureBuffer);
				}
				if (stencilBuffer != nullptr)
				{
					freeDmem(stencilBuffer);
				}
				return true;
			}
			return false;
		});
	}
	mBuffer = nullptr;
	mStencilBuffer = nullptr;

	// Run destructor.
	this->~Texture();
}

//=============================================================================================

RendererContextAGC::FrameBuffer::FrameBuffer()
{
	mColorHandles.fill({ kInvalidHandle });
}

//=============================================================================================

bool RendererContextAGC::FrameBuffer::create(uint8_t const num, const Attachment* const attachments)
{
	// Run constructor to reset object.
	new (this) FrameBuffer{};

	mWidth = 0;
	mHeight = 0;
	mNumAttachments = 0;
	mDepthTarget.init(); // blank depth target.
	for (uint32_t i = 0; i < num; i++)
	{
		const Attachment& attachment = attachments[i];
		if (isValid(attachment.handle))
		{
			Texture& texture = sRendererAGC->mTextures[attachment.handle.idx];

			uint32_t const width  = bx::uint32_max(texture.mSpec.m_width  >> attachment.mip, 1);
			uint32_t const height = bx::uint32_max(texture.mSpec.m_height >> attachment.mip, 1);
			if (mWidth != 0)
			{
				if (width != mWidth || height != mHeight)
				{
					// ERROR: dimensions don't match.
					return false;
				}
			}
			else
			{
				mWidth = width;
				mHeight = height;
			}

			if (!bimg::isDepth(texture.mFormat))
			{
				if (texture.mSpec.m_tileMode != sce::Agc::Core::Texture::TileMode::kRenderTarget)
				{
					// ERROR: Not a render target.
					return false;
				}

				sce::Agc::Core::RenderTargetSpec spec;
				spec.init();
				spec.m_format = texture.mSpec.m_format;
				spec.m_numSlices = texture.mSpec.m_numSlices;
				spec.m_depth = texture.mSpec.m_depth;
				spec.m_width = texture.mSpec.m_width;
				spec.m_height = texture.mSpec.m_height;
				spec.m_numMips = texture.mSpec.m_numMips;
				spec.m_tileMode = sce::Agc::CxRenderTarget::TileMode::kRenderTarget;
				spec.m_dataAddress = texture.mSpec.m_dataAddress;
				SceError error = sce::Agc::Core::initialize(&mColorTargets[mNumAttachments], &spec);
				if (error != SCE_OK)
				{
					// ERROR!
					return false;
				}
				mColorTargets[mNumAttachments].setSlot(mNumAttachments)
					.setCurrentMipLevel(attachment.mip)
					.setBaseArraySliceIndex(attachment.layer);
				mColorHandles[mNumAttachments] = attachment.handle;
				mNumAttachments++;
			}
			else
			{
				if (texture.mSpec.m_tileMode != sce::Agc::Core::Texture::TileMode::kDepth ||texture.mSpec.m_numMips > 1 || texture.mSpec.m_numSlices > 1)
				{
					// ERROR: Don't support depth texture arrays or mipmaps... yet?
					return false;
				}

				sce::Agc::Core::DepthRenderTargetSpec spec;
				spec.init();
				spec.m_depthFormat = sce::Agc::CxDepthRenderTarget::DepthFormat::k32Float;
				spec.m_stencilFormat = texture.mStencilBuffer != nullptr ? sce::Agc::CxDepthRenderTarget::StencilFormat::k8UInt : spec.m_stencilFormat;
				spec.m_width = texture.mSpec.m_width;
				spec.m_height = texture.mSpec.m_height;
				spec.m_depthReadAddress = texture.mBuffer;
				spec.m_depthWriteAddress = texture.mBuffer;
				spec.m_stencilReadAddress = texture.mStencilBuffer;
				spec.m_stencilWriteAddress = texture.mStencilBuffer;
				SceError error = sce::Agc::Core::initialize(&mDepthTarget, &spec);
				if (error != SCE_OK)
				{
					// ERROR!
					return false;
				}
				mDepthHandle = attachment.handle;
			}
		}
	}

	// Clear remaining color targets.
	for (uint32_t i = mNumAttachments; i < BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS; i++)
	{
		mColorTargets[i].init()
			.setSlot(i);
	}

	return false;
}

//=============================================================================================

void RendererContextAGC::FrameBuffer::destroy()
{
	// Run destructor.
	this->~FrameBuffer();
}

//=============================================================================================

RendererContextAGC::RendererContextAGC()
{
	g_caps.supported = 0
		//| BGFX_CAPS_ALPHA_TO_COVERAGE
		| BGFX_CAPS_BLEND_INDEPENDENT
		//| BGFX_CAPS_COMPUTE
		//| BGFX_CAPS_CONSERVATIVE_RASTER
		//| BGFX_CAPS_DRAW_INDIRECT
		| BGFX_CAPS_FRAGMENT_DEPTH
		| BGFX_CAPS_FRAGMENT_ORDERING
		//| BGFX_CAPS_GRAPHICS_DEBUGGER
		//| BGFX_CAPS_HIDPI
		| BGFX_CAPS_INDEX32
		//| BGFX_CAPS_INSTANCING
		//| BGFX_CAPS_OCCLUSION_QUERY
		| BGFX_CAPS_RENDERER_MULTITHREADED
		//| BGFX_CAPS_SWAP_CHAIN
		| BGFX_CAPS_TEXTURE_2D_ARRAY
		| BGFX_CAPS_TEXTURE_3D
		//| BGFX_CAPS_TEXTURE_BLIT
		| BGFX_CAPS_TEXTURE_COMPARE_ALL
		| BGFX_CAPS_TEXTURE_COMPARE_LEQUAL
		| BGFX_CAPS_TEXTURE_CUBE_ARRAY
		//| BGFX_CAPS_TEXTURE_READ_BACK
		| BGFX_CAPS_VERTEX_ATTRIB_HALF
		| BGFX_CAPS_VERTEX_ATTRIB_UINT10
		;

	// Pretend all features are available for all texture formats.
	for (uint32_t formatIdx = 0; formatIdx < TextureFormat::Count; ++formatIdx)
	{
		g_caps.formats[formatIdx] = sTextureFormat[formatIdx].m_flags;
	}

	// Pretend we have no limits
	g_caps.limits.maxTextureSize     = 16384;
	g_caps.limits.maxTextureLayers   = 2048;
	g_caps.limits.maxComputeBindings = g_caps.limits.maxTextureSamplers;
	g_caps.limits.maxFBAttachments   = BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS;
	g_caps.limits.maxVertexStreams   = BGFX_CONFIG_MAX_VERTEX_STREAMS;
}

//=============================================================================================

RendererContextAGC::~RendererContextAGC()
{
	// TODO: cleanup?
}

//=============================================================================================

bool RendererContextAGC::verifyInit(const Init& init)
{
	// TODO: (manderson) We may want to be more clever here and choose an appropriate mode and 
	// leterbox or scale into it, not sure yet how Bgfx handles this.
	// As I understand it VideoOut will scale from one of these modes to the actual display mode.
	return (init.resolution.width == 3840 && init.resolution.height == 2160) ||
		   (init.resolution.width == 3680 && init.resolution.height == 2070) ||
		   (init.resolution.width == 3520 && init.resolution.height == 1980) ||
		   (init.resolution.width == 3360 && init.resolution.height == 1890) ||
		   (init.resolution.width == 3200 && init.resolution.height == 1800) ||
		   (init.resolution.width == 2880 && init.resolution.height == 1620) ||
		   (init.resolution.width == 2560 && init.resolution.height == 1440) ||
		   (init.resolution.width == 2240 && init.resolution.height == 1260) ||
		   (init.resolution.width == 1920 && init.resolution.height == 1080);
}

//=============================================================================================

bool RendererContextAGC::createDisplayBuffers(const Init& init)
{
	// Set up the RenderTarget spec.
	// TODO: (manderson) As I understand it using k8_8_8_8Srgb will cause GPU to do implicit linear to sRGB conversion and
	// I think that Bgfx expects output buffer to have no implicit gamma conversion.
	sce::Agc::Core::RenderTargetSpec rtSpec{};
	rtSpec.init();
	rtSpec.m_width = init.resolution.width;
	rtSpec.m_height = init.resolution.height;
	rtSpec.m_format = { sce::Agc::Core::TypedFormat::k8_8_8_8UNorm, sce::Agc::Core::Swizzle::kRGBA_R4S4 };
	rtSpec.m_tileMode = sce::Agc::CxRenderTarget::TileMode::kRenderTarget;

	// First, retrieve the size of the render target. We can of course do this before we have any pointers.
	sce::Agc::SizeAlign const rtSize = sce::Agc::Core::getSize(&rtSpec);
	// Then we can allocate the required memory backing and assign it to the spec.
	rtSpec.m_dataAddress = allocDmem(rtSize);
	memset((void*)rtSpec.m_dataAddress, 0x80, rtSize.m_size);

	// We can now initialize the render target. This will check that the dataAddress is properly aligned.
	SceError error = sce::Agc::Core::initialize(&mDisplayResources[0].mRenderTarget, &rtSpec);
	SCE_AGC_ASSERT(error == SCE_OK);
	if (error != SCE_OK)
		return false;

	// Now that we have the first RT set up, we can create the others. They are identical to the first material, except for the RT memory.
	sce::Agc::CxRenderTarget& baseRt = mDisplayResources[0].mRenderTarget;
	for (size_t i = 1; i < NumDisplayBuffers; ++i)
	{
		// You can just memcpy the CxRenderTarget, but doing so of course sidesteps the alignment checks in initialize().
		sce::Agc::CxRenderTarget& rt = mDisplayResources[i].mRenderTarget;
		memcpy(&rt, &baseRt, sizeof(baseRt));
		rt.setDataAddress(allocDmem(rtSize));
		memset(rt.getDataAddress(), 0x80, rtSize.m_size);
	}

	// Create and set up one depth target
	sce::Agc::Core::DepthRenderTargetSpec drtSpec{};
	drtSpec.init();
	drtSpec.m_width = rtSpec.m_width;
	drtSpec.m_height = rtSpec.m_height;
	drtSpec.m_depthFormat = sce::Agc::CxDepthRenderTarget::DepthFormat::k32Float;
	drtSpec.m_stencilFormat = sce::Agc::CxDepthRenderTarget::StencilFormat::k8UInt;
	sce::Agc::SizeAlign const depthSize = sce::Agc::Core::getSize(&drtSpec, sce::Agc::Core::DepthRenderTargetComponent::kDepth);
	sce::Agc::SizeAlign const stencilSize = sce::Agc::Core::getSize(&drtSpec, sce::Agc::Core::DepthRenderTargetComponent::kStencil);
	void* const depthMem = allocDmem(sce::Agc::SizeAlign(depthSize.m_size, depthSize.m_align));
	void* const stencilMem = allocDmem(sce::Agc::SizeAlign(stencilSize.m_size, stencilSize.m_align));
	drtSpec.m_depthReadAddress = depthMem;
	drtSpec.m_depthWriteAddress = depthMem;
	drtSpec.m_stencilReadAddress = stencilMem;
	drtSpec.m_stencilWriteAddress = stencilMem;
	error = sce::Agc::Core::initialize(&mDepthRenderTarget, &drtSpec);
	SCE_AGC_ASSERT(error == SCE_OK);
	if (error != SCE_OK)
		return false;

	error = sce::Agc::Toolkit::init();
	SCE_AGC_ASSERT(error == SCE_OK);
	if (error != SCE_OK)
		return false;

	mWidth = init.resolution.width;
	mHeight = init.resolution.height;

	return true;
}

//=============================================================================================

bool RendererContextAGC::createScanoutBuffers()
{
	// First we need to select what we want to display on, which in this case is the TV, also known as SCE_VIDEO_OUT_BUS_TYPE_MAIN.
	mVideoHandle = sceVideoOutOpen(SCE_USER_SERVICE_USER_ID_SYSTEM, SCE_VIDEO_OUT_BUS_TYPE_MAIN, 0, NULL);
	SCE_AGC_ASSERT(mVideoHandle >= 0);
	if (mVideoHandle < 0)
		return false;

	// Next we need to inform scan-out about the format of our buffers. This can be done by directly talking to VideoOut or
	// by letting Agc::Core do the translation. To do so, we first need to get a RenderTargetSpec, which we can extract from
	// the list of CxRenderTargets passed into the function.
	sce::Agc::Core::RenderTargetSpec spec{};
	SceError error = sce::Agc::Core::translate(&spec, &mDisplayResources[0].mRenderTarget);
	SCE_AGC_ASSERT(error == SCE_OK);
	if (error != SCE_OK)
		return false;

	// Next, we use this RenderTargetSpec to create a SceVideoOutBufferAttribute2 which tells VideoOut how it should interpret
	// our buffers. VideoOut needs to know how the color data in the target should be interpreted, and since our pixel shader has
	// been writing linear values into an sRGB RenderTarget, the data VideoOut will find in memory are sRGB encoded.
	// TODO: (manderson) As I understand it Bgfx expects output buffer to not be sRGB (no implicit gamma conversion), but a render
	// should at some point do a gamma conversion (either implicit using an sRGB render target or explicit in shader code) so the
	// output buffer *should* contain sRGB data, so leave this set to kSrgb, not sure what kBt709 is for, I can't find a translate
	// prototype in the docs that takes a second Colorimetry value...?
	SceVideoOutBufferAttribute2 attribute{};
	error = sce::Agc::Core::translate(&attribute, &spec, sce::Agc::Core::Colorimetry::kSrgb, sce::Agc::Core::Colorimetry::kBt709);
	SCE_AGC_ASSERT(error == SCE_OK);
	if (error != SCE_OK)
		return false;

	// Ideally, all buffers should be registered with VideoOut in a single call to sceVideoOutRegisterBuffers2.
	// The reason for this is that the buffers provided in each call get associated with one attribute slot in the API.
	// Even if consecutive calls pass the same SceVideoOutBufferAttribute2 into the function, they still get assigned
	// new attribute slots. When processing a flip, there is significant extra cost associated with switching attribute
	// slots, which should be avoided.
	SceVideoOutBuffers* addresses = (SceVideoOutBuffers*)calloc(NumDisplayBuffers, sizeof(SceVideoOutBuffers));
	for (uint32_t i = 0; i < NumDisplayBuffers; ++i)
	{
		// We could manually call into VideoOut to set up the scan-out buffers, but Agc::Core provides a helper for this.
		addresses[i].data = mDisplayResources[i].mRenderTarget.getDataAddress();
	}

	// VideoOut internally groups scan-out buffers in sets. Every buffer in a set has the same attributes and switching (flipping) between
	// buffers of the same set is a light-weight operation. Switching to a buffer from a different set is significantly more expensive
	// and should be avoided. If an application wants to change the attributes of a scan-out buffer or wants to unregister buffers,
	// these operations are done on whole sets and affect every buffer in the set. This sample only registers one set of buffers and never
	// modifies the set.
	const int32_t setIndex = 0; // Call sceVideoOutUnregisterBuffers with this.
	error = sceVideoOutRegisterBuffers2(mVideoHandle, setIndex, 0, addresses, NumDisplayBuffers, &attribute, SCE_VIDEO_OUT_BUFFER_ATTRIBUTE_CATEGORY_UNCOMPRESSED, nullptr);
	SCE_AGC_ASSERT(error == SCE_OK);
	if (error != SCE_OK)
		return false;
	free(addresses);

	return true;
}

//=============================================================================================

bool RendererContextAGC::createContext()
{
	// Create a context for each buffered frame
	for (uint32_t i = 0; i < NumDisplayBuffers; ++i)
	{
		DisplayResources& displayRes = mDisplayResources[i];
		sce::Agc::Core::BasicContext& ctx = displayRes.mContext;
		ctx.m_dcb.init(
			allocDmem({ DisplayCommandBufferSize, 4 }),
			DisplayCommandBufferSize,
			nullptr,
			nullptr);
		ctx.m_bdr.init(
			&ctx.m_dcb,
			&ctx.m_dcb);
		ctx.m_sb.init(
			256, // This is the size of a chunk in the StateBuffer, defining the largest size of a load packet's payload
			&ctx.m_dcb,
			&ctx.m_dcb);
		displayRes.mLabel = (sce::Agc::Label*)allocDmem({ sizeof(sce::Agc::Label), sce::Agc::Alignment::kLabel });
		displayRes.mLabel->m_value = 1; // 1 means "not used by GPU"
		displayRes.mBorderColorBuffer = (float*)allocDmem({BGFX_CONFIG_MAX_COLOR_PALETTE * sizeof(float) * 4, 256});
	}

	return true;
}

//=============================================================================================

bool RendererContextAGC::init(const Init& initParams)
{
	// TODO: (manderson) cleanup?

	// Validate initialization settings.
	if (!verifyInit(initParams))
		return false;

	SceError error = sce::Agc::init();
	SCE_AGC_ASSERT(error == SCE_OK);
	if (error != SCE_OK)
		return false;

	if (!createDisplayBuffers(initParams) ||
		!createScanoutBuffers() ||
		!createContext())
		return false;

	mBlitDraw.clear();
	mBlitBind.clear();
	mBlitDraw.m_stateFlags = BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_WRITE_Z;
	mBlitDraw.m_scissor = UINT16_MAX;
	mBlitBind.m_bind[0].m_type = (uint8_t)Binding::Texture;
	mBlitBind.m_bind[0].m_samplerFlags = BGFX_SAMPLER_UVW_CLAMP;

	mClearDraw.clear();
	mClearBind.clear();
	mClearDraw.m_stateFlags = BGFX_STATE_PT_TRISTRIP;
	mBlitDraw.m_scissor = UINT16_MAX;

	mVsync = initParams.resolution.reset == BGFX_RESET_VSYNC;

	return true;
}

//=============================================================================================

RendererType::Enum RendererContextAGC::getRendererType() const
{
	return RendererType::Agc;
}

//=============================================================================================

const char* RendererContextAGC::getRendererName() const
{
	return BGFX_RENDERER_AGC_NAME;
}

//=============================================================================================

bool RendererContextAGC::isDeviceRemoved()
{
	return false;
}

//=============================================================================================

void RendererContextAGC::flip()
{
}

//=============================================================================================

void RendererContextAGC::createIndexBuffer(IndexBufferHandle handle, const Memory* mem, uint16_t flags)
{
	mIndexBuffers[handle.idx].create(flags, mem->size, mem->data);
}

//=============================================================================================

void RendererContextAGC::destroyIndexBuffer(IndexBufferHandle handle)
{
	mIndexBuffers[handle.idx].destroy();
}

//=============================================================================================

void RendererContextAGC::createVertexLayout(VertexLayoutHandle handle, const VertexLayout& layout)
{
	VertexLayout& ourLayout = mVertexLayouts[handle.idx];
	memcpy(&ourLayout, &layout, sizeof(VertexLayout) );
	dump(ourLayout);
}

//=============================================================================================

void RendererContextAGC::destroyVertexLayout(VertexLayoutHandle handle)
{
}

//=============================================================================================

void RendererContextAGC::createVertexBuffer(VertexBufferHandle handle, const Memory* mem, VertexLayoutHandle layoutHandle, uint16_t flags)
{
	mVertexBuffers[handle.idx].create(layoutHandle, flags, mem->size, mem->data);
}

//=============================================================================================

void RendererContextAGC::destroyVertexBuffer(VertexBufferHandle handle)
{
	mVertexBuffers[handle.idx].destroy();
}

//=============================================================================================

void RendererContextAGC::createDynamicIndexBuffer(IndexBufferHandle handle, uint32_t size, uint16_t flags)
{
	mIndexBuffers[handle.idx].create(flags, size, nullptr);
}

//=============================================================================================

void RendererContextAGC::updateDynamicIndexBuffer(IndexBufferHandle handle, uint32_t offset, uint32_t size, const Memory* mem)
{
	mIndexBuffers[handle.idx].update(offset, bx::uint32_min(size, mem->size), mem->data);
}

//=============================================================================================

void RendererContextAGC::destroyDynamicIndexBuffer(IndexBufferHandle handle)
{
	mIndexBuffers[handle.idx].destroy();
}

//=============================================================================================

void RendererContextAGC::createDynamicVertexBuffer(VertexBufferHandle handle, uint32_t size, uint16_t flags)
{
	mVertexBuffers[handle.idx].create({kInvalidHandle}, flags, size, nullptr);
}

//=============================================================================================

void RendererContextAGC::updateDynamicVertexBuffer(VertexBufferHandle handle, uint32_t offset, uint32_t size, const Memory* mem)
{
	mVertexBuffers[handle.idx].update(offset, bx::uint32_min(size, mem->size), mem->data);
}

//=============================================================================================

void RendererContextAGC::destroyDynamicVertexBuffer(VertexBufferHandle handle)
{
	mVertexBuffers[handle.idx].destroy();
}

//=============================================================================================

void RendererContextAGC::createShader(ShaderHandle handle, const Memory* mem)
{
	mShaders[handle.idx].create(*mem);
}

//=============================================================================================

void RendererContextAGC::destroyShader(ShaderHandle handle)
{
	mShaders[handle.idx].destroy();
}

//=============================================================================================

void RendererContextAGC::createProgram(ProgramHandle handle, ShaderHandle vsh, ShaderHandle fsh)
{
	mPrograms[handle.idx].create(vsh, fsh);
}

//=============================================================================================

void RendererContextAGC::destroyProgram(ProgramHandle handle)
{
	mPrograms[handle.idx].destroy();
}

//=============================================================================================

void* RendererContextAGC::createTexture(TextureHandle handle, const Memory* mem, uint64_t flags, uint8_t skip)
{
	mTextures[handle.idx].create(flags, mem->size, mem->data, skip);
	return nullptr;
}

//=============================================================================================

void RendererContextAGC::updateTextureBegin(TextureHandle handle, uint8_t side, uint8_t mip)
{
}

//=============================================================================================

void RendererContextAGC::updateTexture(TextureHandle handle, uint8_t side, uint8_t mip, const Rect& rect, uint16_t z, uint16_t depth, uint16_t pitch, const Memory* mem)
{
	mTextures[handle.idx].update(side, mip, rect, z, depth, pitch, mem->size, mem->data);
}

//=============================================================================================

void RendererContextAGC::updateTextureEnd()
{
}

//=============================================================================================

void RendererContextAGC::readTexture(TextureHandle handle, void* data, uint8_t mip)
{
}

//=============================================================================================

void RendererContextAGC::resizeTexture(TextureHandle handle, uint16_t width, uint16_t height, uint8_t numMips, uint16_t numLayers)
{
}

//=============================================================================================

void RendererContextAGC::overrideInternal(TextureHandle handle, uintptr_t ptr)
{
}

//=============================================================================================

uintptr_t RendererContextAGC::getInternal(TextureHandle handle)
{
	return 0;
}

//=============================================================================================

void RendererContextAGC::destroyTexture(TextureHandle handle)
{
	mTextures[handle.idx].destroy();
}

//=============================================================================================

void RendererContextAGC::createFrameBuffer(FrameBufferHandle handle, uint8_t num, const Attachment* attachment)
{
	mFrameBuffers[handle.idx].create(num, attachment);
}

//=============================================================================================

void RendererContextAGC::createFrameBuffer(FrameBufferHandle handle, void* nwh, uint32_t width, uint32_t height, TextureFormat::Enum format, TextureFormat::Enum depthFormat)
{
	// Error?
}

//=============================================================================================

void RendererContextAGC::destroyFrameBuffer(FrameBufferHandle handle)
{
	mFrameBuffers[handle.idx].destroy();
}

//=============================================================================================

void RendererContextAGC::createUniform(UniformHandle handle, UniformType::Enum type, uint16_t num, const char* name)
{
	if (NULL != mUniforms[handle.idx])
	{
		BX_FREE(g_allocator, mUniforms[handle.idx]);
	}

	uint32_t const size = bx::alignUp(g_uniformTypeSize[type]*num, 16);
	void* data = BX_ALLOC(g_allocator, size);
	bx::memSet(data, 0, size);
	mUniforms[handle.idx] = data;
	mUniformReg.add(handle, name);
}

//=============================================================================================

void RendererContextAGC::destroyUniform(UniformHandle handle)
{
	BX_FREE(g_allocator, mUniforms[handle.idx]);
	mUniforms[handle.idx] = NULL;
	mUniformReg.remove(handle);
}

//=============================================================================================

void RendererContextAGC::requestScreenShot(FrameBufferHandle handle, const char* filePath)
{
}

//=============================================================================================

void RendererContextAGC::updateViewName(ViewId id, const char* name)
{
}

//=============================================================================================

void RendererContextAGC::updateUniform(uint16_t loc, const void* data, uint32_t size)
{
	bx::memCopy(mUniforms[loc], data, size);
	mUniformClock++;
}

//=============================================================================================

void RendererContextAGC::invalidateOcclusionQuery(OcclusionQueryHandle handle)
{
}

//=============================================================================================

void RendererContextAGC::setMarker(const char* marker, uint16_t len)
{
}

//=============================================================================================

void RendererContextAGC::setName(Handle handle, const char* name, uint16_t len)
{
}

//=============================================================================================

bool RendererContextAGC::getVertexBindInfo(VertexBindInfo& bindInfo, ProgramHandle const programHandle, const RenderDraw& draw)
{
	// Iterate through attributes required by the vertex shader and find a vertex stream that
	// provides the attribute in the draw streams.
	const Program& program{ mPrograms[programHandle.idx] };
	const Shader& vertexShader{ mShaders[program.mVertexShaderHandle.idx] };
	const Stream* const streams{ draw.m_stream };
	uint8_t const streamMask{ draw.m_streamMask };
	bindInfo.mCount = vertexShader.mNumAttributes;
	for (uint32_t i = 0; i < bindInfo.mCount; i++)
	{
		// Use the last stream that has the attribute required by the vertex shader.
		Attrib::Enum const attrib = vertexShader.mAttributes[i];
		bool found{};
		for (uint32_t idx = 0, mask = streamMask;
			 0 != mask;
			 mask >>= 1, idx += 1)
		{
			// This bit of code just skips over streams that aren't set, so the next stream
			// the loop visits is the next one that is actually set.
			uint32_t const ntz = bx::uint32_cnttz(mask);
			mask >>= ntz;
			idx += ntz;

			const Stream& stream = streams[idx];
			const VertexBuffer& buffer = mVertexBuffers[stream.m_handle.idx];
			VertexLayoutHandle const layoutHandle = isValid(stream.m_layoutHandle) ? stream.m_layoutHandle : buffer.mLayoutHandle;
			const VertexLayout& layout = mVertexLayouts[layoutHandle.idx];
			if (layout.has(attrib))
			{
				bindInfo.mAttribs[i] = { attrib, stream.m_handle, layoutHandle, stream.m_startVertex };
				found = true;
			}
		}

		// If we didn't find any streams that have the attribute we can't draw!
		if (!found)
		{
			// ERROR: Missing vertex attribute stream.
			return false;
		}
	}
	
	// Calc hash for dirty state check.
	bindInfo.mHash = bx::hash<bx::HashMurmur2A>(&bindInfo.mAttribs[0], bindInfo.mCount * sizeof(VertexAttribBindInfo));

	return true;
}

//=============================================================================================

bool RendererContextAGC::getVertexBinding(VertexBinding& binding, const VertexBindInfo& bindInfo)
{
	// Build vertex binding from bind info.
	sce::Agc::Core::BufferSpec spec{};
	SceError error{};
	binding.mNumBufferVertices = UINT32_MAX;
	for (uint32_t i = 0; i < bindInfo.mCount; i++)
	{
		// Get buffer and layout.
		const VertexAttribBindInfo& attribBindInfo = bindInfo.mAttribs[i];
		Attrib::Enum const attrib = attribBindInfo.mAttrib;
		const VertexBuffer& buffer = mVertexBuffers[attribBindInfo.mBufferHandle.idx];
		const VertexLayout& layout = mVertexLayouts[attribBindInfo.mLayoutHandle.idx];

		// Clean up attribute flags (some examples have invalid attibute flags).
		// Flags for reference:
		//		uint16_t VertexLayout::encode(uint8_t _num, AttribType::Enum _type, bool _normalized, bool _asInt)
		//		{
		//			const uint16_t encodedNorm = (_normalized&1)<<7;
		//			const uint16_t encodedType = (_type&7)<<3;
		//			const uint16_t encodedNum  = (_num-1)&3;
		//			const uint16_t encodeAsInt = (_asInt&(!!"\x1\x1\x1\x0\x0"[_type]) )<<8;
		//			return encodedNorm|encodedType|encodedNum|encodeAsInt;
		//		}
		// Ignore AsInt, all of the other render contexts ignore this, not sure what it's for.
		constexpr uint16_t normalizedMask = (1 << 7);
		constexpr uint16_t asIntMask = (1 << 8);
		uint16_t cleanupMask = asIntMask;
		uint16_t encodedAttrib = layout.m_attributes[attrib];
		uint16_t const attribType = (encodedAttrib >> 3) & 0x7;
		if ((attribType == AttribType::Float || attribType == AttribType::Half) &&
			(encodedAttrib & normalizedMask) != 0)
		{
			cleanupMask |= normalizedMask;
		}
		encodedAttrib &= ~cleanupMask;
		
		// Lookup attribute format.
		auto it = sAttribFormatIndex.find(encodedAttrib);
		if (it == sAttribFormatIndex.end())
		{
			// ERROR: Invalid vertex atrribute format.
			return false;
		}
		const AttribFormat& format = it->second;
		
		// Initialize buffer struct.
		uint32_t const offs = attribBindInfo.mBaseVertex * layout.m_stride;
		uint32_t const count = (buffer.mSize - offs) / layout.m_stride;
		binding.mNumBufferVertices = bx::uint32_min(binding.mNumBufferVertices, count);
		spec.initAsVertexBuffer(buffer.mBuffer + offs, { format.mTypedFormat, format.mSwizzle }, layout.m_stride, count);
		error = sce::Agc::Core::initialize(&binding.mBuffers[i], &spec);
		if (error != SCE_OK)
		{
			// ERROR: Failed to create agc vertex buffer.
			return false;
		}

		// Set vertex attribute struct.
		binding.mAttribs[i] = { i, format.mAttribFormat, layout.m_offset[attrib], sce::Agc::Core::VertexAttribute::Index::kVertexId };
	}
	binding.mCount = bindInfo.mCount;
	return true;
}

//=============================================================================================

bool RendererContextAGC::bindVertexAttributes(const RenderDraw& draw)
{
	// Get bind info from the draw's vertex streams, if this fails we can't draw.
	VertexBindInfo bindInfo{};
	if (!getVertexBindInfo(bindInfo, mFrameState.mProgramHandle, draw))
	{
		return false;
	}

	// If the bind info hasn't changed we are good, do nothing.
	if (mFrameState.mVertexAttribHash == bindInfo.mHash)
	{
		return true;
	}
	
	// Get actual agc binding, if this fails we can't draw.
	VertexBinding binding{};
	if (!getVertexBinding(binding, bindInfo))
	{
		return false;
	}

	// Bind vertex streams.
	DisplayResources& displayRes = *(mFrameState.mDisplayRes);
	sce::Agc::Core::BasicContext& ctx = displayRes.mContext;
	ctx.m_bdr.getStage(sce::Agc::ShaderType::kGs)
		.setVertexAttributes(0, binding.mCount, &binding.mAttribs[0])
		.setVertexBuffers(0, binding.mCount, &binding.mBuffers[0]);
	mFrameState.mNumBufferVertices = binding.mNumBufferVertices;
	mFrameState.mVertexAttribHash = bindInfo.mHash;

	// Flag buffers as inflight.
	for (uint32_t i = 0; i < bindInfo.mCount; i++)
	{
		VertexBuffer& buffer = mVertexBuffers[bindInfo.mAttribs[i].mBufferHandle.idx];
		buffer.setInflight();
	}

	return true;
}

//=============================================================================================

void RendererContextAGC::setShaderUniform(uint8_t const flags, uint32_t const regIndex, const void* const val, uint32_t const numRegs)
{
	size_t const len = numRegs*16;
	if ((regIndex + len) <= mFrameState.mUniformBufferSize)
	{
		mFrameState.mUniformBufferDirty = mFrameState.mUniformBufferDirty || memcmp(&mFrameState.mUniformBuffer[regIndex], val, len) != 0;
		memcpy(&mFrameState.mUniformBuffer[regIndex], val, len);
	}
	else
	{
		// ERROR: constant buffer size mismatch!
	}
}

//=============================================================================================

void RendererContextAGC::setShaderUniform4f(uint8_t const flags, uint32_t const regIndex, const void* const val, uint32_t const numRegs)
{
	setShaderUniform(flags, regIndex, val, numRegs);
}

//=============================================================================================

void RendererContextAGC::setShaderUniform4x4f(uint8_t const flags, uint32_t const regIndex, const void* const val, uint32_t const numRegs)
{
	setShaderUniform(flags, regIndex, val, numRegs);
}

//=============================================================================================

void RendererContextAGC::bindFrameBuffer(FrameBufferHandle const frameBufferHandle)
{
	DisplayResources& displayRes = *(mFrameState.mDisplayRes);
	sce::Agc::Core::BasicContext& ctx = displayRes.mContext;
	if (mFrameState.mFrameBufferHandle.idx != frameBufferHandle.idx)
	{
		// If the current render targets are not the scanout buffers (default render targets)
		// make sure the textures are flushed in case we sample them in subsequent views. This is
		// the equivalent of an image memory barrier in Vulkan.
		if (mFrameState.mNumFrameBufferDraws > 0 &&
			(mFrameState.mFlushFrameBufferColor || mFrameState.mFlushFrameBufferDepth))
		{
			sce::Agc::Core::SyncCacheOp const mask = (mFrameState.mFlushFrameBufferColor ? sce::Agc::Core::SyncCacheOp::kFlushUncompressedColorBufferForTexture : sce::Agc::Core::SyncCacheOp::kNone) |
													 (mFrameState.mFlushFrameBufferDepth ? sce::Agc::Core::SyncCacheOp::kFlushUncompressedDepthBufferForTexture : sce::Agc::Core::SyncCacheOp::kNone);
			sce::Agc::Core::gpuSyncEvent(&ctx.m_dcb, sce::Agc::Core::SyncWaitMode::kDrainGraphics, mask);
		}
		if (isValid(frameBufferHandle))
		{
			FrameBuffer& fb = mFrameBuffers[frameBufferHandle.idx];
			fb.setInflight();
			uint32_t const c = bx::uint32_max(mFrameState.mNumFrameBufferAttachments, fb.mNumAttachments);
			for (uint32_t i = 0; i < c; i++)
			{
				ctx.m_sb.setState(fb.mColorTargets[i]);
				mFrameState.mFlushFrameBufferColor = mFrameState.mFlushFrameBufferColor || isValid(fb.mColorHandles[i]);
			}
			ctx.m_sb.setState(fb.mDepthTarget);
			mFrameState.mFlushFrameBufferDepth = isValid(fb.mDepthHandle);
			mFrameState.mNumFrameBufferAttachments = fb.mNumAttachments;
		}
		else
		{
			ctx.m_sb.setState(displayRes.mRenderTarget)
				.setState(mDepthRenderTarget);
			uint32_t const c = bx::uint32_max(mFrameState.mNumFrameBufferAttachments, 1);
			if (c > 1)
			{
				sce::Agc::CxRenderTarget blankRenderTarget;
				blankRenderTarget.init();
				for (uint32_t i = 1; i < c; i++)
				{
					ctx.m_sb.setState(blankRenderTarget.setSlot(i));
				}
			}
			mFrameState.mNumFrameBufferAttachments = 1;

			// Shouldn't read the scanout render targets so don't bother flushing.
			mFrameState.mFlushFrameBufferColor = false;
			mFrameState.mFlushFrameBufferDepth = false;
		}
		mFrameState.mFrameBufferHandle = frameBufferHandle;
		mFrameState.mNumFrameBufferDraws = 0;
	}
}

//=============================================================================================

bool RendererContextAGC::bindUniformBuffer(bool const isFragment)
{
	if (mFrameState.mUniformBufferSize > 0 && (mFrameState.mProgramChanged || mFrameState.mUniformBufferDirty))
	{
		DisplayResources& displayRes = *(mFrameState.mDisplayRes);
		sce::Agc::Core::BasicContext& ctx = displayRes.mContext;
		uint8_t* const uniformBuffer = (uint8_t*)ctx.m_dcb.allocateTopDown(mFrameState.mUniformBufferSize, 16);
		if (uniformBuffer == nullptr)
		{
			// ERROR!
			return false;
		}
		memcpy(uniformBuffer, mFrameState.mUniformBuffer, mFrameState.mUniformBufferSize);

		sce::Agc::Core::Buffer buffer;
		sce::Agc::Core::BufferSpec spec;
		spec.initAsConstantBuffer(uniformBuffer, mFrameState.mUniformBufferSize);
		SceError error = sce::Agc::Core::initialize(&buffer, &spec);
		if (error != SCE_OK)
		{
			// ERROR!
			return false;
		}

		// Bind the uniform buffer.
		ctx.m_bdr.getStage(isFragment ? sce::Agc::ShaderType::kPs : sce::Agc::ShaderType::kGs)
			.setConstantBuffers(0, 1, &buffer);
	}
	return true;
}

//=============================================================================================

void RendererContextAGC::overridePredefined(ShaderHandle const shaderHandle)
{
	Shader& shader = mShaders[shaderHandle.idx];
	for (uint32_t i = 0; i < shader.m_numPredefined; i++)
	{
		const PredefinedUniform& predefined = shader.m_predefined[i];
		uint8_t const flags = predefined.m_type&kUniformFragmentBit;
		switch (predefined.m_type&(~kUniformFragmentBit))
		{
			case PredefinedUniform::ModelViewProj:
			{
				setShaderUniform4x4f(flags
					, predefined.m_loc
					, mFrameState.mOverrideMVP
					, bx::uint32_min(4, predefined.m_count)
					);
			}
			break;
		}
	}
}

//=============================================================================================

bool RendererContextAGC::bindShaderUniforms(ShaderHandle const shaderHandle, const RenderDraw& draw, bool const isFragment, bool const _overridePredefined)
{
	Shader& shader = mShaders[shaderHandle.idx];
	if (shader.mUniformBufferSize > 0)
	{
		mFrameState.mUniformBuffer = shader.mUniformBuffer;
		mFrameState.mUniformBufferSize = shader.mUniformBufferSize;
		mFrameState.mUniformBufferDirty = false;

		#define CLEAR_UNIFORM_BUFFER()				\
			mFrameState.mUniformBuffer = nullptr; 	\
			mFrameState.mUniformBufferSize = 0; 	\
			mFrameState.mUniformBufferDirty = false;

		if (shader.mUniformClock != mUniformClock && shader.mUniforms != nullptr)
		{		
			// Iterate through uniforms.
			shader.mUniforms->reset();
			for (;;)
			{
				uint32_t opcode = shader.mUniforms->read();

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
					data = shader.mUniforms->read(g_uniformTypeSize[type]*num);
				}
				else
				{
					UniformHandle handle;
					bx::memCopy(&handle, shader.mUniforms->read(sizeof(UniformHandle) ), sizeof(UniformHandle) );
					data = (const char*)mUniforms[handle.idx];
				}

				#define CASE_IMPLEMENT_UNIFORM(_uniform, _dxsuffix, _type) \
					case UniformType::_uniform:                            \
					case UniformType::_uniform|kUniformFragmentBit:        \
					{                                                      \
						setShaderUniform(uint8_t(type), loc, data, num);   \
					}                                                      \
					break;

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

					CASE_IMPLEMENT_UNIFORM(Sampler, I, int);
					CASE_IMPLEMENT_UNIFORM(Vec4,    F, float);
					CASE_IMPLEMENT_UNIFORM(Mat4,    F, float);

					case UniformType::End:
					break;

					default:
					{
						BX_TRACE("%4d: INVALID 0x%08x, t %d, l %d, n %d, c %d", shader.mUniforms->getPos(), opcode, type, loc, num, copy);
						CLEAR_UNIFORM_BUFFER();
						return false;
					}
					break;
				}

				#undef CASE_IMPLEMENT_UNIFORM

			}

			shader.mUniformClock = mUniformClock;
		}

		// Commit predefined uniforms.
		// NOTE: (manderson) This will always write any predifined uniforms used by the shader
		// to the uniform buffer, this could be optimized with some dirty state checking. When
		// we bind the uniform buffer it will do nothing if the buffer contents haven't changed, but
		// we could avoid the additional memcpy for the actual uniforms.
		if (!_overridePredefined)
		{
			mFrameState.mViewState.setPredefined<4>(this, mFrameState.mView, shader, mFrameState.mFrame, draw);
		}
		else
		{
			overridePredefined(shaderHandle);
		}

		// Bind the uniform buffer.
		if (!bindUniformBuffer(isFragment))
		{
			CLEAR_UNIFORM_BUFFER();
			return false;
		}
	}

	CLEAR_UNIFORM_BUFFER();

	#undef CLEAR_UNIFORM_BUFFER

	return true;
}

//=============================================================================================

void RendererContextAGC::bindSamplers(const RenderBind& bindings, bool const vertexStage, bool const fragmentStage, bool const computeStage)
{
	sce::Agc::Core::Texture blankTexture{};
	sce::Agc::Core::Sampler blankSampler{};
	blankTexture.init();
	blankSampler.init();
	DisplayResources& displayRes = *(mFrameState.mDisplayRes);
	sce::Agc::Core::BasicContext& ctx = displayRes.mContext;
	for (uint32_t stage = 0; stage < BGFX_CONFIG_MAX_TEXTURE_SAMPLERS; stage++)
	{
		const Binding& bind = bindings.m_bind[stage];
		Binding& curBind = mFrameState.mBindState.m_bind[stage];
		bool const force = bind.m_type != curBind.m_type || mFrameState.mProgramChanged;
		switch (bind.m_type)
		{
			case Binding::Image:
			{
			}
			break;

			case Binding::Texture:
			{
				if (force || bind.m_idx != curBind.m_idx)
				{
					if (bind.m_idx != kInvalidHandle)
					{
						Texture& texture = mTextures[bind.m_idx];
						texture.setInflight();
						if (vertexStage)
						{
							ctx.m_bdr.getStage(sce::Agc::ShaderType::kGs)
								.setTextures(stage, 1, &texture.mTexture);
						}
						if (fragmentStage)
						{
							ctx.m_bdr.getStage(sce::Agc::ShaderType::kPs)
								.setTextures(stage, 1, &texture.mTexture);
						}
						if (computeStage)
						{
							ctx.m_bdr.getStage(sce::Agc::ShaderType::kCs)
								.setTextures(stage, 1, &texture.mTexture);
						}
					}
					else
					{
						if (vertexStage)
						{
							ctx.m_bdr.getStage(sce::Agc::ShaderType::kGs)
								.setTextures(stage, 1, &blankTexture);
						}
						if (fragmentStage)
						{
							ctx.m_bdr.getStage(sce::Agc::ShaderType::kPs)
								.setTextures(stage, 1, &blankTexture);
						}
						if (computeStage)
						{
							ctx.m_bdr.getStage(sce::Agc::ShaderType::kCs)
								.setTextures(stage, 1, &blankTexture);
						}
					}
					curBind.m_idx = bind.m_idx;
				}				
				
				if (bind.m_idx != kInvalidHandle)
				{
					Texture& texture = mTextures[bind.m_idx];
					uint32_t const textureSamplerFlags = (uint32_t)(texture.mFlags & BGFX_SAMPLER_BITS_MASK);
					uint32_t const flags = (bind.m_samplerFlags & BGFX_SAMPLER_INTERNAL_DEFAULT) != 0 ? textureSamplerFlags : bind.m_samplerFlags;
					if (force || curBind.m_samplerFlags != flags)
					{
						sce::Agc::Core::Sampler sampler{};
						sce::Agc::Core::Sampler* samplerPtr{ &texture.mSampler };
						if (flags != textureSamplerFlags)
						{
							Texture::setSampler(sampler, flags);
							samplerPtr = &sampler;
						}

						if (vertexStage)
						{
							ctx.m_bdr.getStage(sce::Agc::ShaderType::kGs)
								.setSamplers(stage, 1, samplerPtr);
						}
						if (fragmentStage)
						{
							ctx.m_bdr.getStage(sce::Agc::ShaderType::kPs)
								.setSamplers(stage, 1, samplerPtr);
						}
						if (computeStage)
						{
							ctx.m_bdr.getStage(sce::Agc::ShaderType::kCs)
								.setSamplers(stage, 1, samplerPtr);
						}

						curBind.m_samplerFlags = flags;
					}
				}
				else
				{
					if (force || curBind.m_samplerFlags != UINT32_MAX)
					{
						if (vertexStage)
						{
							ctx.m_bdr.getStage(sce::Agc::ShaderType::kGs)
								.setSamplers(stage, 1, &blankSampler);
						}
						if (fragmentStage)
						{
							ctx.m_bdr.getStage(sce::Agc::ShaderType::kPs)
								.setSamplers(stage, 1, &blankSampler);
						}
						if (computeStage)
						{
							ctx.m_bdr.getStage(sce::Agc::ShaderType::kCs)
								.setSamplers(stage, 1, &blankSampler);
						}
						curBind.m_samplerFlags = UINT32_MAX;
					}
				}
			}
			break;

			case Binding::IndexBuffer:
			{
			}
			break;

			case Binding::VertexBuffer:
			{
			}
			break;
		}
	}
}

//=============================================================================================

bool RendererContextAGC::bindProgram(ProgramHandle const programHandle, const RenderDraw& draw, const RenderBind& bind, bool const overridePredefined)
{
	Program& program = mPrograms[programHandle.idx];
	Shader& vtxShader = mShaders[program.mVertexShaderHandle.idx];
	Shader* const frgShader = isValid(program.mFragmentShaderHandle) ? &mShaders[program.mFragmentShaderHandle.idx] : nullptr;

	// Bind shaders.
	mFrameState.mProgramChanged = programHandle.idx != mFrameState.mProgramHandle.idx;
	if (mFrameState.mProgramChanged)
	{
		DisplayResources& displayRes = *(mFrameState.mDisplayRes);
		sce::Agc::Core::BasicContext& ctx = displayRes.mContext;
		uint64_t const primType = (draw.m_stateFlags & BGFX_STATE_PT_MASK) >> BGFX_STATE_PT_SHIFT;
		ctx.setShaders(nullptr, vtxShader.mShader, frgShader != nullptr ? frgShader->mShader : nullptr, sPrimTypeInfo[primType].m_type);
		mFrameState.mProgramHandle = programHandle;
		program.setInflight();
		vtxShader.setInflight();
		if (frgShader != nullptr)
		{
			frgShader->setInflight();
		}
	}

	// Commit vertex shader uniforms.
	bool const vtxSamplers = vtxShader.mNumSamplers > 0;
	if (!bindShaderUniforms(program.mVertexShaderHandle, draw, false, overridePredefined))
	{
		return false;
	}

	// Bind fragment shader uniforms.
	bool frgSamplers{};
	if (frgShader != nullptr)
	{
		frgSamplers = frgShader->mNumSamplers > 0;
		if (!bindShaderUniforms(program.mFragmentShaderHandle, draw, true, overridePredefined))
		{
			return false;
		}
	}

	// Bind samplers.
	if (vtxSamplers || frgSamplers)
	{
		bindSamplers(bind, vtxSamplers, frgSamplers, false);
	}

	return true;
}

//=============================================================================================

void RendererContextAGC::bindFixedState(const RenderDraw& draw)
{
	RenderDraw& currentState = mFrameState.mDrawState;

	bool const changedView = mFrameState.mFixedStateView != mFrameState.mView;
	mFrameState.mFixedStateView = mFrameState.mView;

	// Firgure out what needs updating.
	uint64_t changedFlags{};
	uint64_t changedStencil{};
	uint32_t changedBlendColor{};
	if (0)//mFrameState.mWasCompute)
	{
		currentState.clear();
		changedFlags = BGFX_STATE_MASK;
		changedStencil = packStencil(BGFX_STENCIL_MASK, BGFX_STENCIL_MASK);
		changedBlendColor = ~0u;
	}
	else
	{
		changedFlags = currentState.m_stateFlags ^ draw.m_stateFlags;
		changedStencil = currentState.m_stencil ^ draw.m_stencil;
		changedBlendColor = currentState.m_rgba ^ draw.m_rgba;

	}
	currentState.m_stateFlags = draw.m_stateFlags;
	currentState.m_stencil = draw.m_stencil;
	currentState.m_rgba = draw.m_rgba;

	DisplayResources& displayRes = *(mFrameState.mDisplayRes);
	sce::Agc::Core::BasicContext& ctx = displayRes.mContext;

	// Push viewport.
	const Rect& viewportRect = mFrameState.mViewState.m_rect;
	if (viewportRect.m_x != mFrameState.mViewportState.m_x ||
		viewportRect.m_y != mFrameState.mViewportState.m_y ||
		viewportRect.m_width != mFrameState.mViewportState.m_width ||
		viewportRect.m_height != mFrameState.mViewportState.m_height)
	{
		sce::Agc::CxViewport cxViewport;
		sce::Agc::Core::setViewport(&cxViewport, viewportRect.m_width, viewportRect.m_height, viewportRect.m_x, viewportRect.m_y, -1.0f, 1.0f);
		ctx.m_sb.setState(cxViewport);
		mFrameState.mViewportState = viewportRect;
	}

	// Push scissor.
	Rect scissorRect{};
	if (draw.m_scissor == UINT16_MAX)
	{
		scissorRect = mFrameState.mViewScissor;
	}
	else
	{
		scissorRect.setIntersect(mFrameState.mViewScissor, mFrameState.mFrame->m_frameCache.m_rectCache.m_cache[draw.m_scissor]);
	}
	if (scissorRect.m_x != mFrameState.mScissorState.m_x ||
		scissorRect.m_y != mFrameState.mScissorState.m_y ||
		scissorRect.m_width != mFrameState.mScissorState.m_width ||
		scissorRect.m_height != mFrameState.mScissorState.m_height)
	{
		sce::Agc::CxScreenScissor cxScissor;
		cxScissor.init()
			.setLeft( scissorRect.m_x )
			.setTop( scissorRect.m_y )
			.setRight( scissorRect.m_x + scissorRect.m_width )
			.setBottom( scissorRect.m_y + scissorRect.m_height );
		ctx.m_sb.setState(cxScissor);
		mFrameState.mScissorState = scissorRect;
	}

	// Push changed state.
	uint64_t const stateBits = 0 
		| BGFX_STATE_ALPHA_REF_MASK					// *
		| BGFX_STATE_BLEND_ALPHA_TO_COVERAGE
		| BGFX_STATE_BLEND_EQUATION_MASK			// *
		| BGFX_STATE_BLEND_INDEPENDENT				// *
		| BGFX_STATE_BLEND_MASK						// *
		| BGFX_STATE_CONSERVATIVE_RASTER
		| BGFX_STATE_CULL_MASK						// *
		| BGFX_STATE_DEPTH_TEST_MASK				// *
		| BGFX_STATE_FRONT_CCW						// *
		| BGFX_STATE_LINEAA
		| BGFX_STATE_MSAA
		| BGFX_STATE_POINT_SIZE_MASK
		| BGFX_STATE_PT_MASK						// *
		| BGFX_STATE_WRITE_A						// *
		| BGFX_STATE_WRITE_RGB						// *
		| BGFX_STATE_WRITE_Z;						// *
	if ((changedFlags & stateBits) != 0 || changedStencil != 0 || changedBlendColor != 0 || changedView)
	{
		uint32_t const numRt = mFrameState.mNumFrameBufferAttachments;

		// Primitive mode.
		uint64_t const primModeBits = 0
			| BGFX_STATE_FRONT_CCW
			| BGFX_STATE_CULL_MASK;
		if ((changedFlags & primModeBits) != 0)
		{
			sce::Agc::CxPrimitiveSetup cxPrimitiveSetup;
			sce::Agc::CxPrimitiveSetup::FrontPolygonMode const frontFillMode = mFrameState.mWireframeFill ? sce::Agc::CxPrimitiveSetup::FrontPolygonMode::kLine : sce::Agc::CxPrimitiveSetup::FrontPolygonMode::kFill;
			sce::Agc::CxPrimitiveSetup::BackPolygonMode const backFillMode = mFrameState.mWireframeFill ? sce::Agc::CxPrimitiveSetup::BackPolygonMode::kLine : sce::Agc::CxPrimitiveSetup::BackPolygonMode::kFill;
			sce::Agc::CxPrimitiveSetup::CullFace const cullMode = sCullMode[(draw.m_stateFlags & BGFX_STATE_CULL_MASK) >> BGFX_STATE_CULL_SHIFT];
			sce::Agc::CxPrimitiveSetup::FrontFace const frontFace = (draw.m_stateFlags & BGFX_STATE_FRONT_CCW) ? sce::Agc::CxPrimitiveSetup::FrontFace::kCcw : sce::Agc::CxPrimitiveSetup::FrontFace::kCw;
			cxPrimitiveSetup.init()
				.setFrontPolygonMode(frontFillMode)
				.setBackPolygonMode(backFillMode)
				.setPolygonMode(sce::Agc::CxPrimitiveSetup::PolygonMode::kEnable)
				.setCullFace(cullMode)
				.setFrontFace(frontFace);
			ctx.m_sb.setState(cxPrimitiveSetup);
		}

		// Primitive type.
		uint64_t const primTypeBits = 0
			| BGFX_STATE_PT_MASK;
		if ((changedFlags & primTypeBits) != 0)
		{
			uint64_t const primType = (draw.m_stateFlags & BGFX_STATE_PT_MASK) >> BGFX_STATE_PT_SHIFT;
			sce::Agc::UcPrimitiveType ucPrimType;
			ucPrimType.init()
				.setType(sPrimTypeInfo[primType].m_type);
			ctx.m_sb.setState(ucPrimType);
		}

		// Depthtest & Stencil.
		uint64_t const depthBits = 0
			| BGFX_STATE_DEPTH_TEST_MASK
			| BGFX_STATE_WRITE_Z;
		if ((changedFlags & depthBits) != 0 || changedStencil != 0)
		{
			sce::Agc::CxDepthStencilControl cxDepthStencil;
			bool const depthWrite = (BGFX_STATE_WRITE_Z & draw.m_stateFlags) != 0;
			uint64_t const depthFunc = (draw.m_stateFlags & BGFX_STATE_DEPTH_TEST_MASK) >> BGFX_STATE_DEPTH_TEST_SHIFT;
			cxDepthStencil.init()
				.setDepthWrite(depthWrite ? sce::Agc::CxDepthStencilControl::DepthWrite::kEnable : sce::Agc::CxDepthStencilControl::DepthWrite::kDisable)
				.setDepth(depthFunc == 0 ? sce::Agc::CxDepthStencilControl::Depth::kDisable : sce::Agc::CxDepthStencilControl::Depth::kEnable)
				.setDepthFunction(sDepthFunc[depthFunc]);
			
			// Sooo much code to setup stencil.
			if (draw.m_stencil != 0)
			{
				sce::Agc::CxStencilOpControl cxStencilOp;
				uint32_t const frontStencil = unpackStencil(0, draw.m_stencil);
				uint32_t const frontFunc = (frontStencil & BGFX_STENCIL_TEST_MASK) >> BGFX_STENCIL_TEST_SHIFT;
				uint32_t const frontFail = (frontStencil & BGFX_STENCIL_OP_FAIL_S_MASK) >> BGFX_STENCIL_OP_FAIL_S_SHIFT;
				uint32_t const frontZPass = (frontStencil & BGFX_STENCIL_OP_PASS_Z_MASK) >> BGFX_STENCIL_OP_PASS_Z_SHIFT;
				uint32_t const frontZFail = (frontStencil & BGFX_STENCIL_OP_FAIL_Z_MASK) >> BGFX_STENCIL_OP_FAIL_Z_SHIFT;
				uint32_t const frontRef = (frontStencil & BGFX_STENCIL_FUNC_REF_MASK) >> BGFX_STENCIL_FUNC_REF_SHIFT;
				uint32_t const frontMask = (frontStencil & BGFX_STENCIL_FUNC_RMASK_MASK) >> BGFX_STENCIL_FUNC_RMASK_SHIFT;
				uint32_t const backStencil = unpackStencil(1, draw.m_stencil);
				bool const separateStencil = backStencil != BGFX_STENCIL_NONE && backStencil != frontStencil;
				if (separateStencil)
				{
					uint32_t const backFunc = (backStencil & BGFX_STENCIL_TEST_MASK) >> BGFX_STENCIL_TEST_SHIFT;
					uint32_t const backFail = (backStencil & BGFX_STENCIL_OP_FAIL_S_MASK) >> BGFX_STENCIL_OP_FAIL_S_SHIFT;
					uint32_t const backZPass = (backStencil & BGFX_STENCIL_OP_PASS_Z_MASK) >> BGFX_STENCIL_OP_PASS_Z_SHIFT;
					uint32_t const backZFail = (backStencil & BGFX_STENCIL_OP_FAIL_Z_MASK) >> BGFX_STENCIL_OP_FAIL_Z_SHIFT;
					uint32_t const backRef = (backStencil & BGFX_STENCIL_FUNC_REF_MASK) >> BGFX_STENCIL_FUNC_REF_SHIFT;
					uint32_t const backMask = (backStencil & BGFX_STENCIL_FUNC_RMASK_MASK) >> BGFX_STENCIL_FUNC_RMASK_SHIFT;

					cxDepthStencil.setStencil(sce::Agc::CxDepthStencilControl::Stencil::kEnable)
						.setSeparateStencil(sce::Agc::CxDepthStencilControl::SeparateStencil::kEnable)
						.setStencilFunction(sStencilFunc[frontFunc].m_front)
						.setStencilFunctionBack(sStencilFunc[backFunc].m_back);
					cxStencilOp.init()
						.setStencilFailOp(sStencilOp[frontFail].m_failFront)
						.setStencilZPassOp(sStencilOp[frontZPass].m_zPassFront)
						.setStencilZFailOp(sStencilOp[frontZFail].m_zFailFront)
						.setStencilFailBackOp(sStencilOp[backFail].m_failBack)
						.setStencilZPassBackOp(sStencilOp[backZPass].m_zPassBack)
						.setStencilZFailBackOp(sStencilOp[backZFail].m_zFailBack);

					sce::Agc::CxStencilControl cxStencilCtrl;
					cxStencilCtrl.init()
						.setTestValue(frontRef)
						.setMask(frontMask)
						.setOpValue(1)
						.setWriteMask(~0);
					ctx.m_sb.setState(cxStencilCtrl);

					sce::Agc::CxStencilControlBackFace cxStencilCtrlBack;
					cxStencilCtrlBack.init()
						.setTestValue(backRef)
						.setMask(backMask)
						.setOpValue(1)
						.setWriteMask(~0);
					ctx.m_sb.setState(cxStencilCtrlBack);
				}
				else
				{
					cxDepthStencil.setStencil(sce::Agc::CxDepthStencilControl::Stencil::kEnable)
						.setSeparateStencil(sce::Agc::CxDepthStencilControl::SeparateStencil::kDisable)
						.setStencilFunction(sStencilFunc[frontFunc].m_front);
					cxStencilOp.init()
						.setStencilFailOp(sStencilOp[frontFail].m_failFront)
						.setStencilZPassOp(sStencilOp[frontZPass].m_zPassFront)
						.setStencilZFailOp(sStencilOp[frontZFail].m_zFailFront);

					sce::Agc::CxStencilControl cxStencilCtrl;
					cxStencilCtrl.init()
						.setTestValue(frontRef)
						.setMask(frontMask)
						.setOpValue(1)
						.setWriteMask(~0);
					ctx.m_sb.setState(cxStencilCtrl);
				}
				ctx.m_sb.setState(cxStencilOp);
			}
			else
			{
				cxDepthStencil.setStencil(sce::Agc::CxDepthStencilControl::Stencil::kDisable);
			}
			ctx.m_sb.setState(cxDepthStencil);
		}

		// Blending.
		uint64_t const blendingBits = 0
			| BGFX_STATE_BLEND_EQUATION_MASK
			| BGFX_STATE_BLEND_INDEPENDENT
			| BGFX_STATE_BLEND_MASK;
		if ((changedFlags & blendingBits) != 0 || changedBlendColor != 0 || changedView)
		{
			// TODO: (manderson) hook this up once MRT works.
			bool const independent = (draw.m_stateFlags & BGFX_STATE_BLEND_INDEPENDENT) != 0;
			bool const enabled = (draw.m_stateFlags & BGFX_STATE_BLEND_MASK) != 0;
			if (enabled)
			{
				uint32_t const equ = (uint32_t)((draw.m_stateFlags & BGFX_STATE_BLEND_EQUATION_MASK) >> BGFX_STATE_BLEND_EQUATION_SHIFT);
				uint32_t const equRGB = equ & 0x7;
				uint32_t const equA = (equ >> 3) & 0x7;
				uint32_t const blend = (uint32_t)((draw.m_stateFlags & BGFX_STATE_BLEND_MASK) >> BGFX_STATE_BLEND_SHIFT);
				uint32_t const srcRGB = blend & 0xf;
				uint32_t const dstRGB = (blend >> 4) & 0xf;
				uint32_t const srcA = (blend >> 8) & 0xf;
				uint32_t const dstA = (blend >> 12) & 0xf;

				// If we are not doing independant render target blending set all of the
				// render target blend modes the same, otherwise set only the first the
				// remaining will be taken care of below.
				for (uint32_t i = 0, c = independent ? 1 : numRt; i < c; i++)
				{
					sce::Agc::CxBlendControl cxBlending;
					cxBlending.init()
						.setSlot(i)
						.setBlend(sce::Agc::CxBlendControl::Blend::kEnable)
						.setColorBlendFunc(sBlendFunc[equRGB].m_rgbFunc)
						.setColorSourceMultiplier(sBlendFactor[srcRGB].m_rgbSrc)
						.setColorDestMultiplier(sBlendFactor[dstRGB].m_rgbDst)
						.setAlphaBlendFunc(sBlendFunc[equA].m_aFunc)
						.setAlphaSourceMultiplier(sBlendFactor[srcA].m_aSrc)
						.setAlphaDestMultiplier(sBlendFactor[dstA].m_aDst);
					ctx.m_sb.setState(cxBlending);
				}

				// If independent blending modes are used for each MRT the modes are
				// encoded in the constant blend color so don't push it.
				if (changedBlendColor &&
					!independent &&
					(sBlendFactor[srcRGB].m_usesConst || sBlendFactor[dstRGB].m_usesConst))
				{
					uint32_t const rgba = draw.m_rgba;
					float const r = (rgba >> 24) / 255.0f;
					float const g = ((rgba >> 16) & 0xff) / 255.0f;
					float const b = ((rgba >> 8) & 0xff) / 255.0f;
					float const a = (rgba & 0xff) / 255.0f;
					sce::Agc::CxBlendColor cxBlendColor;
					cxBlendColor.init()
						.setRed(r)
						.setGreen(g)
						.setBlue(b)
						.setAlpha(a);
					ctx.m_sb.setState(cxBlendColor);
				}
			}
			else
			{
				for (uint32_t i = 0, c = independent ? 1 : numRt; i < c; i++)
				{
					sce::Agc::CxBlendControl cxBlending;
					cxBlending.init()
						.setSlot(i)
						.setBlend(sce::Agc::CxBlendControl::Blend::kDisable);
					ctx.m_sb.setState(cxBlending);
				}
			}
			if (independent)
			{
				// Independant blend modes are encoded in blending constant color.
				for (uint32_t i = 1; i < numRt; i++)
				{
					sce::Agc::CxBlendControl cxBlending;
					if ((draw.m_rgba & 0x7ff) != 0)
					{
						uint32_t const rgba = draw.m_rgba;
						uint32_t const equRGBA = (rgba >> 8) & 0x7;
						uint32_t const srcRGBA = rgba & 0xf;
						uint32_t const dstRGBA = (rgba >> 4) & 0xf;

						cxBlending.init()
							.setSlot(i)
							.setBlend(sce::Agc::CxBlendControl::Blend::kEnable)
							.setColorBlendFunc(sBlendFunc[equRGBA].m_rgbFunc)
							.setColorSourceMultiplier(sBlendFactor[srcRGBA].m_rgbSrc)
							.setColorDestMultiplier(sBlendFactor[dstRGBA].m_rgbDst)
							.setAlphaBlendFunc(sBlendFunc[equRGBA].m_aFunc)
							.setAlphaSourceMultiplier(sBlendFactor[srcRGBA].m_aSrc)
							.setAlphaDestMultiplier(sBlendFactor[dstRGBA].m_aDst);
						ctx.m_sb.setState(cxBlending);
					}
					else
					{
						sce::Agc::CxBlendControl cxBlending;
						cxBlending.init()
							.setSlot(i)
							.setBlend(sce::Agc::CxBlendControl::Blend::kDisable);
						ctx.m_sb.setState(cxBlending);
					}
				}
			}
		}

		// Color buffer writes.
		uint64_t const bufferMaskBits = 0
			| BGFX_STATE_WRITE_RGB
			| BGFX_STATE_WRITE_A;
		if ((changedFlags & bufferMaskBits) != 0 || changedView)
		{
			uint32_t const mask = 0
				| ((draw.m_stateFlags & BGFX_STATE_WRITE_R) != 0 ? (1 << 0) : 0)
				| ((draw.m_stateFlags & BGFX_STATE_WRITE_G) != 0 ? (1 << 1) : 0)
				| ((draw.m_stateFlags & BGFX_STATE_WRITE_B) != 0 ? (1 << 2) : 0)
				| ((draw.m_stateFlags & BGFX_STATE_WRITE_A) != 0 ? (1 << 3) : 0);

			// NOTE: I guess Bgfx doesn't have separate masks for each MRT.
			sce::Agc::CxRenderTargetMask cxRenderTargetMask;
			cxRenderTargetMask.init();
			for (uint32_t i = 0; i < numRt; i++)
			{
				cxRenderTargetMask.setMask(i, mask);
			}
			ctx.m_sb.setState(cxRenderTargetMask);
		}
	}
}

//=============================================================================================

void RendererContextAGC::beginFrame(Frame* const frame)
{
	// Grab the right context for this frame
	mPhase = (mPhase + 1) % NumDisplayBuffers;
	mFrameState.mDisplayRes = &mDisplayResources[mPhase];

	mFrameState.mFrame = frame;

	// Flush transient buffers.
	if (0 < mFrameState.mFrame->m_iboffset)
	{
		//BGFX_PROFILER_SCOPE("bgfx/Update transient index buffer", kColorResource);
		TransientIndexBuffer* const ib = mFrameState.mFrame->m_transientIb;
		mIndexBuffers[ib->handle.idx].update(0, mFrameState.mFrame->m_iboffset, ib->data);
	}
	if (0 < mFrameState.mFrame->m_vboffset)
	{
		//BGFX_PROFILER_SCOPE("bgfx/Update transient vertex buffer", kColorResource);
		TransientVertexBuffer* const vb = mFrameState.mFrame->m_transientVb;
		mVertexBuffers[vb->handle.idx].update(0, mFrameState.mFrame->m_vboffset, vb->data);
	}

	// Sort frame items.
	mFrameState.mFrame->sort();

	// Init state bits.
	mFrameState.mDrawState.clear();
	mFrameState.mDrawState.m_stateFlags = BGFX_STATE_NONE;
	mFrameState.mDrawState.m_stencil = packStencil(BGFX_STENCIL_NONE, BGFX_STENCIL_NONE);
	mFrameState.mBindState.clear();
	mFrameState.mViewState.reset( mFrameState.mFrame );
	mFrameState.mViewportState.clear();
	mFrameState.mScissorState.clear();
	//displayRes.mBlitState = { displayRes.mFrame };
	mFrameState.mViewScissor.clear();
	mFrameState.mProgramHandle = { kInvalidHandle };
	mFrameState.mFrameBufferHandle = { BGFX_CONFIG_MAX_FRAME_BUFFERS };
	mFrameState.mNumItems = mFrameState.mFrame->m_numRenderItems;
	mFrameState.mVertexAttribHash = 0;
	mFrameState.mItem = 0;
	mFrameState.mView = UINT16_MAX;
	mFrameState.mFixedStateView = UINT16_MAX;
	mFrameState.mIsCompute = false;
	mFrameState.mWasCompute = false;
	mFrameState.mWireframeFill = (mFrameState.mFrame->m_debug & BGFX_DEBUG_WIREFRAME) != 0;
	mFrameState.mBlitting = false;
	mFrameState.mNumFrameBufferAttachments = 0;
	mFrameState.mNumFrameBufferDraws = 0;
	mFrameState.mFlushFrameBufferColor = false;
	mFrameState.mFlushFrameBufferDepth = false;

	// Init perf stats.
	// TODO: (manderson) hooks these up...
	const int64_t timerFreq = bx::getHPFrequency();
	const int64_t timeBegin = bx::getHPCounter();

	Stats& perfStats = frame->m_perfStats;
	perfStats.cpuTimeBegin  = timeBegin;
	perfStats.cpuTimeEnd    = timeBegin;
	perfStats.cpuTimerFreq  = timerFreq;

	perfStats.gpuTimeBegin  = 0;
	perfStats.gpuTimeEnd    = 0;
	perfStats.gpuTimerFreq  = 1000000000;

	bx::memSet(perfStats.numPrims, 0, sizeof(perfStats.numPrims) );

	perfStats.gpuMemoryMax  = -INT64_MAX;
	perfStats.gpuMemoryUsed = -INT64_MAX;
}

//=============================================================================================

void RendererContextAGC::waitForGPU()
{
	// Wait till GPU finishes.
	DisplayResources& displayRes = *(mFrameState.mDisplayRes);
	sce::Agc::Core::BasicContext& ctx = displayRes.mContext;
	while (displayRes.mLabel->m_value != 1)
	{
		// TODO: (manderson) Non busy wait? Semaphore, Fence?
		sceKernelUsleep(1000);
	}
	displayRes.mLabel->m_value = 0;
	ctx.reset();
	ctx.m_dcb.waitUntilSafeForRendering(mVideoHandle, mPhase);

	// Decrment the inflight count of all resources used by this command buffer for it's
	// previous frame.
	landResources();

	// Set border colors, this palette is shared with clear colors, but
	// just copy all of them incase they are used as uv border colors.
	memcpy(displayRes.mBorderColorBuffer, mFrameState.mFrame->m_colorPalette, BGFX_CONFIG_MAX_COLOR_PALETTE * sizeof(float) * 4);
	sce::Agc::CxBorderColorTableAddrGfx borderColorTableAddrGfx{};
	borderColorTableAddrGfx.init()
		.setBase(displayRes.mBorderColorBuffer);
	ctx.m_sb.setState(borderColorTableAddrGfx);
}

//=============================================================================================

bool RendererContextAGC::nextItem()
{
	if (mFrameState.mItem < mFrameState.mNumItems)
	{
		mFrameState.mEncodedKey = mFrameState.mFrame->m_sortKeys[mFrameState.mItem];
		mFrameState.mWasCompute = mFrameState.mIsCompute;
		mFrameState.mIsCompute = mFrameState.mKey.decode(mFrameState.mEncodedKey, mFrameState.mFrame->m_viewRemap);
		mFrameState.mViewChanged = mFrameState.mKey.m_view != mFrameState.mView;
		mFrameState.mItemIdx = mFrameState.mFrame->m_sortValues[mFrameState.mItem];
		mFrameState.mRenderItem = &(mFrameState.mFrame->m_renderItem[mFrameState.mItemIdx]);
		mFrameState.mRenderBind = &(mFrameState.mFrame->m_renderItemBind[mFrameState.mItemIdx]);
		mFrameState.mBlitting = false;
		mFrameState.mItem++;
		return true;
	}
	return false;
}

//=============================================================================================

void RendererContextAGC::clearRect(const ClearQuad& clearQuad)
{
	const Clear& clear = mFrameState.mFrame->m_view[mFrameState.mView].m_clear;
	if ((clear.m_flags & BGFX_CLEAR_MASK) != 0)
	{
		uint32_t const numRt = mFrameState.mNumFrameBufferAttachments;

		// Make sure scissor is full viewport.
		Rect prevViewScissor = mFrameState.mViewScissor;
		mFrameState.mViewScissor = mFrameState.mViewState.m_rect;

		// TODO: (manderson) Disable scissor and set stencil flags.
		mClearDraw.m_stateFlags &= ~(BGFX_STATE_WRITE_MASK | BGFX_STATE_DEPTH_TEST_MASK);
		mClearDraw.m_stateFlags |= (clear.m_flags & BGFX_CLEAR_COLOR) != 0 ? (BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A) : 0;
		mClearDraw.m_stateFlags |= (clear.m_flags & BGFX_CLEAR_DEPTH) != 0 ? (BGFX_STATE_DEPTH_TEST_ALWAYS | BGFX_STATE_WRITE_Z) : 0;
		mClearDraw.m_stencil = (clear.m_flags & BGFX_CLEAR_STENCIL) != 0 ? (BGFX_STENCIL_TEST_ALWAYS | BGFX_STENCIL_FUNC_REF(clear.m_stencil) | BGFX_STENCIL_FUNC_RMASK(0xff) | BGFX_STENCIL_OP_FAIL_S_REPLACE | BGFX_STENCIL_OP_FAIL_Z_REPLACE | BGFX_STENCIL_OP_PASS_Z_REPLACE) : 0;

		mVertexLayouts[BGFX_CONFIG_MAX_VERTEX_LAYOUTS] = clearQuad.m_layout;
		Stream& stream = mClearDraw.m_stream[0];
		stream.m_startVertex = 0;
		stream.m_handle = clearQuad.m_vb;
		stream.m_layoutHandle = { BGFX_CONFIG_MAX_VERTEX_LAYOUTS };
		mClearDraw.setStreamBit(0, clearQuad.m_vb);

		if (mClearQuadColor.idx == kInvalidHandle)
		{
			const UniformRegInfo* const infoClearColor = mUniformReg.find("bgfx_clear_color");
			if (infoClearColor != nullptr)
				mClearQuadColor = infoClearColor->m_handle;
		}

		if (mClearQuadDepth.idx == kInvalidHandle)
		{
			const UniformRegInfo* const infoClearDepth = mUniformReg.find("bgfx_clear_depth");
			if (infoClearDepth != nullptr)
				mClearQuadDepth = infoClearDepth->m_handle;
		}

		float mrtClearColor[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS][4];
		if ((clear.m_flags & BGFX_CLEAR_COLOR_USE_PALETTE) != 0)
		{
			for (uint32_t i = 0; i < numRt; ++i)
			{
				uint8_t const index = (uint8_t)bx::uint32_min(BGFX_CONFIG_MAX_COLOR_PALETTE-1, clear.m_index[i]);
				const float* const rgba = mFrameState.mFrame->m_colorPalette[index];
				bx::memCopy(mrtClearColor[i], rgba, 16);
			}
		}
		else
		{
			float const rgba[4]{
				(float)clear.m_index[0] * (1.0f / 255.0f),
				(float)clear.m_index[1] * (1.0f / 255.0f),
				(float)clear.m_index[2] * (1.0f / 255.0f),
				(float)clear.m_index[3] * (1.0f / 255.0f),
			};
			for (uint32_t i = 0; i < numRt; ++i)
			{
				bx::memCopy(mrtClearColor[i], rgba, 16);
			}
		}
		updateUniform(mClearQuadColor.idx, mrtClearColor[0], numRt * sizeof(float) * 4);

		float mrtClearDepth[4] = { g_caps.homogeneousDepth ? (clear.m_depth * 2.0f - 1.0f) : clear.m_depth };
		updateUniform(mClearQuadDepth.idx, mrtClearDepth, sizeof(float) * 4);

		if (bindProgram(clearQuad.m_program[numRt], mClearDraw, mClearBind, true) &&
			bindVertexAttributes(mClearDraw))
		{
			bindFixedState(mClearDraw);
			submitDrawCall(mClearDraw);
		}

		// Restore view scissor.
		mFrameState.mViewScissor = prevViewScissor;
	}
}

//=============================================================================================

void RendererContextAGC::viewChanged(const ClearQuad& clearQuad)
{
	mFrameState.mView = mFrameState.mKey.m_view;
	const View& view = mFrameState.mFrame->m_view[mFrameState.mView];

	mFrameState.mViewState.m_rect = view.m_rect;
	const Rect& scissorRect = view.m_scissor;
	bool const viewHasScissor = !scissorRect.isZero();
	mFrameState.mViewScissor = viewHasScissor ? scissorRect : mFrameState.mViewState.m_rect;

	bindFrameBuffer(view.m_fbh);

	clearRect(clearQuad);

	//submitBlit(bs, view);
}

//=============================================================================================

bool RendererContextAGC::submitCompute()
{
	const RenderCompute& compute = mFrameState.mRenderItem->compute;
	if (compute.m_uniformBegin < compute.m_uniformEnd)
	{
		rendererUpdateUniforms(this, mFrameState.mFrame->m_uniformBuffer[compute.m_uniformIdx], compute.m_uniformBegin, compute.m_uniformEnd);
	}

	// ... do stuff ...

	return true;
}

//=============================================================================================

bool RendererContextAGC::submitDrawCall(const RenderDraw& draw)
{
	uint64_t const primType = (draw.m_stateFlags & BGFX_STATE_PT_MASK) >> BGFX_STATE_PT_SHIFT;
	DisplayResources& displayRes = *(mFrameState.mDisplayRes);
	sce::Agc::Core::BasicContext& ctx = displayRes.mContext;
	if (isValid(draw.m_indexBuffer))
	{
		IndexBuffer& indexBuffer = mIndexBuffers[draw.m_indexBuffer.idx];
		uint32_t const indexSize = draw.isIndex16() ? 2 : 4;
		uint32_t const numIndices = indexBuffer.mSize / indexSize;
		if (draw.m_indexBuffer.idx != mFrameState.mDrawState.m_indexBuffer.idx)
		{
			indexBuffer.setInflight();
			ctx.m_dcb.setIndexSize(indexSize == 2 ? sce::Agc::IndexSize::k16 : sce::Agc::IndexSize::k32);
			ctx.m_dcb.setIndexBuffer(indexBuffer.mBuffer);
			ctx.m_dcb.setIndexCount(numIndices);
			mFrameState.mDrawState.m_indexBuffer = draw.m_indexBuffer;
		}
		
		if (draw.m_numIndices == UINT32_MAX)
		{
			ctx.drawIndexOffset(0, numIndices);
			mFrameState.mNumFrameBufferDraws++;
		}
		else if (draw.m_numIndices >= sPrimTypeInfo[primType].m_min)
		{
			ctx.drawIndexOffset(draw.m_startIndex, draw.m_numIndices);
			mFrameState.mNumFrameBufferDraws++;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (draw.m_numVertices == UINT32_MAX)
		{
			ctx.drawIndexAuto(mFrameState.mNumBufferVertices);
			mFrameState.mNumFrameBufferDraws++;
		}
		else if (draw.m_numVertices >= sPrimTypeInfo[primType].m_min)
		{
			ctx.drawIndexAuto(draw.m_numVertices);
			mFrameState.mNumFrameBufferDraws++;
		}
		else
		{
			return false;
		}
	}

	return true;
}

//=============================================================================================

bool RendererContextAGC::submitDraw()
{
	/*if (mFrameState.mWasCompute)
	{
		// ... do transition stuff ...
	}*/

	const ProgramHandle& programHandle = mFrameState.mKey.m_program;
	const RenderDraw& draw = mFrameState.mRenderItem->draw;
	const RenderBind& bind = *mFrameState.mRenderBind;

	if (draw.m_uniformBegin < draw.m_uniformEnd)
	{
		rendererUpdateUniforms(this, mFrameState.mFrame->m_uniformBuffer[draw.m_uniformIdx], draw.m_uniformBegin, draw.m_uniformEnd);
	}

	if (isValid(programHandle) &&
		draw.m_streamMask != UINT8_MAX && draw.m_streamMask != 0 &&
		bindProgram(programHandle, draw, bind, false) &&
		bindVertexAttributes(draw))
	{
		bindFixedState(draw);
		submitDrawCall(draw);
		return true;
	}

	return false;
}

//=============================================================================================

void RendererContextAGC::endFrame()
{
	// Finally submit the workload to the GPU
	DisplayResources& displayRes = *(mFrameState.mDisplayRes);
	sce::Agc::Core::BasicContext& ctx = displayRes.mContext;
	ctx.m_dcb.setFlip(mVideoHandle, mPhase, mVsync ? SCE_VIDEO_OUT_FLIP_MODE_VSYNC : SCE_VIDEO_OUT_FLIP_MODE_ASAP, 0);
	sce::Agc::Core::gpuSyncEvent(
		&ctx.m_dcb,
		sce::Agc::Core::SyncWaitMode::kAsynchronous,
		sce::Agc::Core::SyncCacheOp::kClearAll,
		sce::Agc::Core::SyncLabelVisibility::kCpu,
		displayRes.mLabel,
		1);
	SceError error = sce::Agc::submitGraphics(
		sce::Agc::GraphicsQueue::kNormal,
		ctx.m_dcb.getSubmitPointer(),
		ctx.m_dcb.getSubmitSize());
	SCE_AGC_ASSERT(error == SCE_OK);
	error = sce::Agc::suspendPoint();
	SCE_AGC_ASSERT(error == SCE_OK);
	mFrameClock++;
}

//=============================================================================================

void RendererContextAGC::submit(Frame* frame, ClearQuad& clearQuad, TextVideoMemBlitter& textVideoMemBlitter)
{
	beginFrame(frame);

	if (0 == (frame->m_debug&BGFX_DEBUG_IFH))
	{
		waitForGPU();

		while (nextItem())
		{
			if (mFrameState.mViewChanged)
			{
				viewChanged( clearQuad );
			}
			
			if (mFrameState.mIsCompute)
			{
				submitCompute();
				continue;
			}

			submitDraw();
		}

		if (frame->m_debug & BGFX_DEBUG_TEXT)
		{
			blit(this, textVideoMemBlitter, frame->m_textVideoMem);
		}

		endFrame();
	}

	// Process destroy list.
	tickDestroyList();
}

//=============================================================================================

void RendererContextAGC::landResources()
{
	DisplayResources& displayRes = *(mFrameState.mDisplayRes);
	for (auto& counter : displayRes.mInflightCounters)
	{
		if (counter->mCount > 0)
		{
			counter->mCount--;
		}
	}
	displayRes.mInflightCounters.clear();
}

//=============================================================================================

void RendererContextAGC::tickDestroyList(bool const force)
{
	for (auto it = mDestroyList.begin(); it != mDestroyList.end();)
	{
		const auto& callback = *it;
		bool removed = callback();
		if (force)
		{
			while (!removed)
			{
				removed = callback();
			}
		}
		it = removed ? mDestroyList.erase(it) : it + 1;
	}
}

//=============================================================================================

void RendererContextAGC::blitSetup(TextVideoMemBlitter& blitter)
{
	// Blit to back buffer.
	mFrameState.mView = UINT16_MAX;
	mFrameState.mViewState.m_rect = { 0, 0, (uint16_t)mWidth, (uint16_t)mHeight };
	mFrameState.mViewScissor = mFrameState.mViewState.m_rect;
	bindFrameBuffer({ kInvalidHandle });

	// Override model view projection.
	bx::mtxOrtho(mFrameState.mOverrideMVP, 0.0f, (float)mWidth, (float)mHeight, 0.0f, 0.0f, 1000.0f, 0.0f, g_caps.homogeneousDepth);

	// Set texture stage.
	mBlitBind.m_bind[0].m_idx = blitter.m_texture.idx;

	// Bind program and set fixed function state.
	if (bindProgram(blitter.m_program, mBlitDraw, mBlitBind, true))
	{
		bindFixedState(mBlitDraw);
		mFrameState.mBlitting = true;
	}
}

//=============================================================================================

void RendererContextAGC::blitRender(TextVideoMemBlitter& blitter, uint32_t numIndices)
{
	if (mFrameState.mBlitting)
	{
		uint32_t const numVertices = numIndices*4/6;
		if (numVertices > 0)
		{
			// Update buffers.
			mIndexBuffers[blitter.m_ib->handle.idx].update(0, numIndices * 2, blitter.m_ib->data);
			mVertexBuffers[blitter.m_vb->handle.idx].update(0, numVertices * blitter.m_layout.m_stride, blitter.m_vb->data);

			// Set draw streams (use temp vertex layout handle).
			mVertexLayouts[BGFX_CONFIG_MAX_VERTEX_LAYOUTS] = blitter.m_layout;
			Stream& stream = mBlitDraw.m_stream[0];
			stream.m_startVertex = 0;
			stream.m_handle = blitter.m_vb->handle;
			stream.m_layoutHandle = { BGFX_CONFIG_MAX_VERTEX_LAYOUTS };
			mBlitDraw.setStreamBit(0, blitter.m_vb->handle);
			mBlitDraw.m_indexBuffer = blitter.m_ib->handle;
			mBlitDraw.m_numIndices = numIndices;

			if (bindVertexAttributes(mBlitDraw))
			{
				submitDrawCall(mBlitDraw);
			}
		}
	}
}

//=============================================================================================

RendererContextI* rendererCreate(const Init& init)
{
	BX_UNUSED(init);
	sRendererAGC = BX_NEW(g_allocator, RendererContextAGC);
	if (!sRendererAGC->init(init) )
	{
		BX_DELETE(g_allocator, sRendererAGC);
		sRendererAGC = NULL;
	}
	return sRendererAGC;
}

//=============================================================================================

void rendererDestroy()
{
	BX_DELETE(g_allocator, sRendererAGC);
	sRendererAGC = NULL;
}

//=============================================================================================

} } // namespace agc bgfx

//=============================================================================================

#else

//=============================================================================================

namespace bgfx { namespace agc {

//=============================================================================================

RendererContextI* rendererCreate(const Init& init)
{
	BX_UNUSED(init);
	return NULL;
}

//=============================================================================================

void rendererDestroy()
{
}

//=============================================================================================

} } // namespace agc bgfx

//=============================================================================================

#endif // BGFX_CONFIG_RENDERER_AGC

//=============================================================================================
