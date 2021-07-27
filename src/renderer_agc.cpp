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
	ATTRIB_FORMAT(1, Float, false, k32Float, kX, k1, k1, k1),
	ATTRIB_FORMAT(2, Float, false, k32_32Float, kX, kY, k1, k1),
	ATTRIB_FORMAT(3, Float, false, k32_32_32Float, kX, kY, kZ, k1),
	ATTRIB_FORMAT(4, Float, false, k32_32_32_32Float, kX, kY, kZ, kW),

	ATTRIB_FORMAT(1, Half, false, k16Float, kX, k1, k1, k1),
	ATTRIB_FORMAT(2, Half, false, k16_16Float, kX, kY, k1, k1),
	ATTRIB_FORMAT(3, Half, false, k16_16_16_16Float, kX, kY, kZ, k1),
	ATTRIB_FORMAT(4, Half, false, k16_16_16_16Float, kX, kY, kZ, kW),

	ATTRIB_FORMAT(1, Uint8, true, k8UNorm, kX, k1, k1, k1),
	ATTRIB_FORMAT(2, Uint8, true, k8_8UNorm, kX, kY, k1, k1),
	ATTRIB_FORMAT(3, Uint8, true, k8_8_8_8UNorm, kX, kY, kZ, k1),
	ATTRIB_FORMAT(4, Uint8, true, k8_8_8_8UNorm, kX, kY, kZ, kW),

	ATTRIB_FORMAT(1, Uint8, false, k8UInt, kX, k1, k1, k1),
	ATTRIB_FORMAT(2, Uint8, false, k8_8UInt, kX, kY, k1, k1),
	ATTRIB_FORMAT(3, Uint8, false, k8_8_8_8UInt, kX, kY, kZ, k1),
	ATTRIB_FORMAT(4, Uint8, false, k8_8_8_8UInt, kX, kY, kZ, kW),

	ATTRIB_FORMAT(1, Int16, true, k16UNorm, kX, k1, k1, k1),
	ATTRIB_FORMAT(2, Int16, true, k16_16UNorm, kX, kY, k1, k1),
	ATTRIB_FORMAT(3, Int16, true, k16_16_16_16UNorm, kX, kY, kZ, k1),
	ATTRIB_FORMAT(4, Int16, true, k16_16_16_16UNorm, kX, kY, kZ, kW),

	ATTRIB_FORMAT(1, Int16, false, k16UInt, kX, k1, k1, k1),
	ATTRIB_FORMAT(2, Int16, false, k16_16UInt, kX, kY, k1, k1),
	ATTRIB_FORMAT(3, Int16, false, k16_16_16_16UInt, kX, kY, kZ, k1),
	ATTRIB_FORMAT(4, Int16, false, k16_16_16_16UInt, kX, kY, kZ, kW),

	ATTRIB_FORMAT(1, Uint10, false, k10_10_10_2UInt, kX, k1, k1, k1),
	ATTRIB_FORMAT(2, Uint10, false, k10_10_10_2UInt, kX, kY, k1, k1),
	ATTRIB_FORMAT(3, Uint10, false, k10_10_10_2UInt, kX, kY, kZ, k1),
	ATTRIB_FORMAT(4, Uint10, false, k10_10_10_2UInt, kX, kY, kZ, kW),

	ATTRIB_FORMAT(1, Uint10, true, k10_10_10_2UNorm, kX, k1, k1, k1),
	ATTRIB_FORMAT(2, Uint10, true, k10_10_10_2UNorm, kX, kY, k1, k1),
	ATTRIB_FORMAT(3, Uint10, true, k10_10_10_2UNorm, kX, kY, kZ, k1),
	ATTRIB_FORMAT(4, Uint10, true, k10_10_10_2UNorm, kX, kY, kZ, kW),
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

static const PrimTypeInfo sPrimTypeInfo[Topology::Count] =
{
	PRIM_TYPE( kTriList, 3, 3, 0 ),
	PRIM_TYPE( kTriStrip, 3, 1, 2 ),
	PRIM_TYPE( kLineList, 2, 2, 0 ),
	PRIM_TYPE( kLineStrip, 2, 1, 1 ),
	PRIM_TYPE( kPointList, 1, 1, 0 ),
};

#undef PRIM_TYPE

//=============================================================================================

#define CULL_MODE( mode ) \
		sce::Agc::CxPrimitiveSetup::CullFace::mode \

static const sce::Agc::CxPrimitiveSetup::CullFace sCullMode[] =
{
	CULL_MODE( kNone ),
	CULL_MODE( kFront ),
	CULL_MODE( kBack ),
};

#undef CULL_MODE

//=============================================================================================

#define DEPTH_FUNC( func ) \
		sce::Agc::CxDepthStencilControl::DepthFunction::func \

static const sce::Agc::CxDepthStencilControl::DepthFunction sDepthFunc[] =
{
	DEPTH_FUNC( kAlways ),
	DEPTH_FUNC( kLess ),
	DEPTH_FUNC( kLessEqual ),
	DEPTH_FUNC( kEqual ),
	DEPTH_FUNC( kGreaterEqual ),
	DEPTH_FUNC( kGreater ),
	DEPTH_FUNC( kNotEqual ),
	DEPTH_FUNC( kNever ),
	DEPTH_FUNC( kAlways ),
};

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

static const StencilFunc sStencilFunc[] =
{
	STENCIL_FUNC( kAlways ),
	STENCIL_FUNC( kLess ),
	STENCIL_FUNC( kLessEqual ),
	STENCIL_FUNC( kEqual ),
	STENCIL_FUNC( kGreaterEqual ),
	STENCIL_FUNC( kGreater ),
	STENCIL_FUNC( kNotEqual ),
	STENCIL_FUNC( kNever ),
	STENCIL_FUNC( kAlways ),
};

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

static const StencilOp sStencilOp[] =
{
	STENCIL_OP( kZero ),
	STENCIL_OP( kKeep ),
	STENCIL_OP( kReplaceTest ),
	STENCIL_OP( kAddWrap ),
	STENCIL_OP( kAddClamp ),
	STENCIL_OP( kSubWrap ),
	STENCIL_OP( kSubClamp ),
	STENCIL_OP( kInvert ),
};

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

static const BlendFunc sBlendFunc[] =
{
	BLEND_FUNC( kAdd ),
	BLEND_FUNC( kSubtract ),
	BLEND_FUNC( kReverseSubtract ),
	BLEND_FUNC( kMin ),
	BLEND_FUNC( kMax ),
};

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

static const BlendFactor sBlendFactor[] =
{
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
};

#undef BLEND_FACTOR

//=============================================================================================

static RendererContextAGC* sRendererAGC;

//=============================================================================================

bool RendererContextAGC::Shader::create(const Memory& mem)
{
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
}

//=============================================================================================

bool RendererContextAGC::Program::create(ShaderHandle const vertexShaderHandle, ShaderHandle const fragmentShaderHandle)
{
	mVertexShaderHandle = vertexShaderHandle;
	mFragmentShaderHandle = fragmentShaderHandle;
	return true;
}

//=============================================================================================

void RendererContextAGC::Program::destroy()
{
	// TODO: (manderson) destroy program.
}

//=============================================================================================

bool RendererContextAGC::Buffer::update(uint32_t const offset, uint32_t const size, const uint8_t* const data)
{
	// TODO: (manderson) Once things are up and running consider N buffering to avoid malloc and memcpy, or possibly
	// staging buffer with GPU copy?
	uint32_t const requestSize = offset + size;
	uint32_t const newSize = mSize > requestSize ? mSize : requestSize;
	uint8_t* const newBuffer = allocDmem({newSize, 16});
	if (newBuffer == nullptr)
	{
		return false;
	}
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
		sRendererAGC->mDestroyList.push_back([count=(int32_t)NumDisplayBuffers,buffer=mBuffer]() mutable {
			count--;
			if (count <= 0)
			{
				freeDmem(buffer);
				return true;
			}
			return false;
		});
	}
	mBuffer = newBuffer;
	mSize = newSize;
	memcpy(mBuffer + offset, data, size);

	return true;
}

//=============================================================================================

void RendererContextAGC::Buffer::destroy()
{
	if (mBuffer != nullptr)
	{
		sRendererAGC->mDestroyList.push_back([count=(int32_t)NumDisplayBuffers,buffer=mBuffer]() mutable {
			count--;
			if (count <= 0)
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
}

//=============================================================================================

bool RendererContextAGC::VertexBuffer::create(VertexLayoutHandle const layoutHandle, uint16_t const flags, uint32_t const size, const uint8_t* const data)
{
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
}

//=============================================================================================

RendererContextAGC::RendererContextAGC()
{
	// Pretend all features are available.
	g_caps.supported = 0
		| BGFX_CAPS_ALPHA_TO_COVERAGE
		| BGFX_CAPS_BLEND_INDEPENDENT
		| BGFX_CAPS_COMPUTE
		| BGFX_CAPS_CONSERVATIVE_RASTER
		| BGFX_CAPS_DRAW_INDIRECT
		| BGFX_CAPS_FRAGMENT_DEPTH
		| BGFX_CAPS_FRAGMENT_ORDERING
		| BGFX_CAPS_GRAPHICS_DEBUGGER
		| BGFX_CAPS_HIDPI
		| BGFX_CAPS_INDEX32
		| BGFX_CAPS_INSTANCING
		| BGFX_CAPS_OCCLUSION_QUERY
		| BGFX_CAPS_RENDERER_MULTITHREADED
		| BGFX_CAPS_SWAP_CHAIN
		| BGFX_CAPS_TEXTURE_2D_ARRAY
		| BGFX_CAPS_TEXTURE_3D
		| BGFX_CAPS_TEXTURE_BLIT
		| BGFX_CAPS_TEXTURE_COMPARE_ALL
		| BGFX_CAPS_TEXTURE_COMPARE_LEQUAL
		| BGFX_CAPS_TEXTURE_CUBE_ARRAY
		| BGFX_CAPS_TEXTURE_READ_BACK
		| BGFX_CAPS_VERTEX_ATTRIB_HALF
		| BGFX_CAPS_VERTEX_ATTRIB_UINT10
		;

	// Pretend all features are available for all texture formats.
	for (uint32_t formatIdx = 0; formatIdx < TextureFormat::Count; ++formatIdx)
	{
		g_caps.formats[formatIdx] = 0
			| BGFX_CAPS_FORMAT_TEXTURE_NONE
			| BGFX_CAPS_FORMAT_TEXTURE_2D
			| BGFX_CAPS_FORMAT_TEXTURE_2D_SRGB
			| BGFX_CAPS_FORMAT_TEXTURE_2D_EMULATED
			| BGFX_CAPS_FORMAT_TEXTURE_3D
			| BGFX_CAPS_FORMAT_TEXTURE_3D_SRGB
			| BGFX_CAPS_FORMAT_TEXTURE_3D_EMULATED
			| BGFX_CAPS_FORMAT_TEXTURE_CUBE
			| BGFX_CAPS_FORMAT_TEXTURE_CUBE_SRGB
			| BGFX_CAPS_FORMAT_TEXTURE_CUBE_EMULATED
			| BGFX_CAPS_FORMAT_TEXTURE_VERTEX
			| BGFX_CAPS_FORMAT_TEXTURE_IMAGE_READ
			| BGFX_CAPS_FORMAT_TEXTURE_IMAGE_WRITE
			| BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER
			| BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA
			| BGFX_CAPS_FORMAT_TEXTURE_MSAA
			| BGFX_CAPS_FORMAT_TEXTURE_MIP_AUTOGEN
			;
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
	return NULL;
}

//=============================================================================================

void RendererContextAGC::updateTextureBegin(TextureHandle handle, uint8_t side, uint8_t mip)
{
}

//=============================================================================================

void RendererContextAGC::updateTexture(TextureHandle handle, uint8_t side, uint8_t mip, const Rect& rect, uint16_t z, uint16_t depth, uint16_t pitch, const Memory* mem)
{
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
}

//=============================================================================================

void RendererContextAGC::createFrameBuffer(FrameBufferHandle handle, uint8_t num, const Attachment* attachment)
{
}

//=============================================================================================

void RendererContextAGC::createFrameBuffer(FrameBufferHandle handle, void* nwh, uint32_t width, uint32_t height, TextureFormat::Enum format, TextureFormat::Enum depthFormat)
{
}

//=============================================================================================

void RendererContextAGC::destroyFrameBuffer(FrameBufferHandle handle)
{
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

RendererContextAGC::VertexBindInfo::VertexBindInfo( ProgramHandle const programHandle, VertexBufferHandle const bufferHandle, VertexLayoutHandle layoutHandle, uint32_t const baseVertex )
{
	const Program& program{ sRendererAGC->mPrograms[programHandle.idx] };
	const Shader& vertexShader{ sRendererAGC->mShaders[program.mVertexShaderHandle.idx] };
	mCount = vertexShader.mNumAttributes;
	for (uint32_t i = 0; i < mCount; i++)
	{
		mAttribs[i] = { vertexShader.mAttributes[i], bufferHandle, layoutHandle, baseVertex };
	}
	mHash = bx::hash<bx::HashMurmur2A>(&mAttribs[0], mCount * sizeof(VertexBindInfo));
}

//=============================================================================================

RendererContextAGC::VertexBindInfo::VertexBindInfo( ProgramHandle const programHandle, const RenderDraw& draw )
{
	const Program& program{ sRendererAGC->mPrograms[programHandle.idx] };
	const Shader& vertexShader{ sRendererAGC->mShaders[program.mVertexShaderHandle.idx] };
	const Stream* const streams{ draw.m_stream };
	uint8_t const streamMask{ draw.m_streamMask };
	mCount = vertexShader.mNumAttributes;
	for (uint32_t i = 0; i < mCount; i++)
	{
		Attrib::Enum const attrib = vertexShader.mAttributes[i];
		for (uint32_t idx = 0, mask = streamMask;
			 0 != mask;
			 mask >>= 1, idx += 1)
		{
			uint32_t const ntz = bx::uint32_cnttz(mask);
			mask >>= ntz;
			idx += ntz;

			const Stream& stream = streams[idx];
			mAttribs[i] = { attrib, stream.m_handle, stream.m_layoutHandle, stream.m_startVertex };
		}
	}
	mHash = bx::hash<bx::HashMurmur2A>(&mAttribs[0], mCount * sizeof(VertexBindInfo));
}

//=============================================================================================

bool RendererContextAGC::getVertexBinding(VertexBinding& binding, const VertexBindInfo& bindInfo)
{
	// NOTE: (manderson) Ignore asInt bit in encoded attribute.
	constexpr uint16_t asIntMask = (1 << 8);
	sce::Agc::Core::BufferSpec spec{};
	SceError error{};
	binding.mNumBufferVertices = UINT32_MAX;
	for (uint32_t i = 0; i < bindInfo.mCount; i++)
	{
		// Get buffer and layout.
		const VertexAttribBindInfo& attribBindInfo = bindInfo.mAttribs[i];
		Attrib::Enum const attrib = attribBindInfo.mAttrib;
		const VertexBuffer& buffer = mVertexBuffers[attribBindInfo.mBufferHandle.idx];
		const VertexLayout& layout = mVertexLayouts[isValid(attribBindInfo.mLayoutHandle) ? attribBindInfo.mLayoutHandle.idx : buffer.mLayoutHandle.idx];
		
		// Lookup attribute format.
		auto it = sAttribFormatIndex.find(layout.m_attributes[attrib] & ~asIntMask);
		if (it == sAttribFormatIndex.end())
		{
			// ERROR!
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
			// ERROR!
			return false;
		}

		// Set vertex attribute struct.
		binding.mAttribs[i] = { i, format.mAttribFormat, layout.m_offset[attrib], sce::Agc::Core::VertexAttribute::Index::kVertexId };
	}
	binding.mCount = bindInfo.mCount;
	return true;
}

//=============================================================================================

bool RendererContextAGC::bindVertexAttributes(const VertexBindInfo& bindInfo)
{
	if (mFrameState.mVertexAttribHash != bindInfo.mHash)
	{
		VertexBinding binding;
		if (getVertexBinding(binding, bindInfo))
		{
			DisplayResources& displayRes = *(mFrameState.mDisplayRes);
			sce::Agc::Core::BasicContext& ctx = displayRes.mContext;
			ctx.m_bdr.getStage(sce::Agc::ShaderType::kGs)
				.setVertexAttributes(0, binding.mCount, &binding.mAttribs[0])
				.setVertexBuffers(0, binding.mCount, &binding.mBuffers[0]);
			mFrameState.mNumBufferVertices = binding.mNumBufferVertices;
			mFrameState.mVertexAttribHash = bindInfo.mHash;
			return true;
		}
		return false;
	}
	return true;
}

//=============================================================================================

bool RendererContextAGC::bindVertexAttributes(const ProgramHandle& programHandle, VertexBufferHandle const bufferHandle, VertexLayoutHandle const layoutHandle, uint32_t const baseVertex )
{
	VertexBindInfo const bindInfo{ programHandle, bufferHandle, layoutHandle, baseVertex };
	return bindVertexAttributes(bindInfo);
}

//=============================================================================================

bool RendererContextAGC::bindVertexAttributes()
{
	VertexBindInfo const bindInfo{ mFrameState.mKey.m_program, mFrameState.mRenderItem->draw };
	return bindVertexAttributes(bindInfo);
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
		// ERROR constant buffer size mismatch!
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

bool RendererContextAGC::bindShaderUniforms(ShaderHandle const shaderHandle, const RenderDraw& draw, bool const isFragment)
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
		mFrameState.mViewState.setPredefined<4>(this, mFrameState.mView, shader, mFrameState.mFrame, draw);

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

bool RendererContextAGC::bindProgram(const ProgramHandle& programHandle, const RenderDraw& draw)
{
	Program& program = mPrograms[programHandle.idx];
	Shader* const vtxShader = &mShaders[program.mVertexShaderHandle.idx];
	Shader* const frgShader = isValid(program.mFragmentShaderHandle) ? &mShaders[program.mFragmentShaderHandle.idx] : nullptr;

	// Bind shaders.
	mFrameState.mProgramChanged = programHandle.idx != mFrameState.mProgramHandle.idx;
	if (mFrameState.mProgramChanged)
	{
		DisplayResources& displayRes = *(mFrameState.mDisplayRes);
		sce::Agc::Core::BasicContext& ctx = displayRes.mContext;
		uint64_t const primType = (draw.m_stateFlags & BGFX_STATE_PT_MASK) >> BGFX_STATE_PT_SHIFT;
		ctx.setShaders(nullptr, vtxShader->mShader, frgShader != nullptr ? frgShader->mShader : nullptr, sPrimTypeInfo[primType].m_type);
		mFrameState.mProgramHandle = programHandle;
	}

	// Commit vertex shader uniforms.
	if (!bindShaderUniforms(program.mVertexShaderHandle, draw, false))
	{
		return false;
	}

	// Bind fragment shader uniforms.
	if (frgShader != nullptr)
	{
		if (!bindShaderUniforms(program.mFragmentShaderHandle, draw, true))
		{
			return false;
		}
	}

	// HACK: (manderson) Ignore draw with samplers until we hook them up, need to flush the
	// uniforms though so do all of the binding.
	if (vtxShader->mNumSamplers > 0 || frgShader->mNumSamplers > 0)
		return false;

	return true;
}

//=============================================================================================

bool RendererContextAGC::bindProgram()
{
	return bindProgram(mFrameState.mKey.m_program, mFrameState.mRenderItem->draw);
}

//=============================================================================================

void RendererContextAGC::bindFixedState(const RenderDraw& draw)
{
	RenderDraw& currentState = mFrameState.mDrawState;

	// Firgure out what needs updating. If the view changed or the last render item
	// was compute flush everything.
	uint64_t changedFlags{};
	uint64_t changedStencil{};
	uint32_t changedBlendColor{};
	if (mFrameState.mViewChanged || mFrameState.mWasCompute)
	{
		currentState.clear();
		currentState.m_scissor = !draw.m_scissor;

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

	// Push scissor.
	uint16_t const scissor = draw.m_scissor;
	if (currentState.m_scissor != scissor)
	{
		currentState.m_scissor = scissor;

		Rect scissorRect;
		if (scissor == UINT16_MAX)
		{
			scissorRect = mFrameState.mScissorRect;
		}
		else
		{
			scissorRect.setIntersect(mFrameState.mScissorRect, mFrameState.mFrame->m_frameCache.m_rectCache.m_cache[scissor]);
		}

		sce::Agc::CxScreenScissor cxScissor;
		cxScissor.init()
			.setLeft( scissorRect.m_x )
			.setTop( scissorRect.m_y )
			.setRight( scissorRect.m_x + scissorRect.m_width )
			.setBottom( scissorRect.m_y + scissorRect.m_height );
		ctx.m_sb.setState(cxScissor);
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
	if ((changedFlags & stateBits) != 0 || changedStencil != 0 || changedBlendColor != 0)
	{
		uint32_t const numRt = 1; //getNumRt();

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
				.setDepthWrite(depthWrite ? sce::Agc::CxDepthStencilControl::DepthWrite::kDisable : sce::Agc::CxDepthStencilControl::DepthWrite::kEnable)
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
		if ((changedFlags & blendingBits) != 0 || changedBlendColor)
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
		if ((changedFlags & bufferMaskBits) != 0)
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

void RendererContextAGC::bindFixedState()
{
	bindFixedState(mFrameState.mRenderItem->draw);
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
	mFrameState.mViewState.m_rect = mFrameState.mFrame->m_view[0].m_rect;
	//displayRes.mBlitState = { displayRes.mFrame };
	mFrameState.mScissorRect.clear();
	mFrameState.mProgramHandle = { kInvalidHandle };
	mFrameState.mFrameBufferHandle = { BGFX_CONFIG_MAX_FRAME_BUFFERS };
	mFrameState.mNumItems = mFrameState.mFrame->m_numRenderItems;
	mFrameState.mVertexAttribHash = 0;
	mFrameState.mItem = 0;
	mFrameState.mView = UINT16_MAX;
	mFrameState.mIsCompute = false;
	mFrameState.mWasCompute = false;
	mFrameState.mWireframeFill = !!(mFrameState.mFrame->m_debug&BGFX_DEBUG_WIREFRAME);

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
		mFrameState.mItem++;
		return true;
	}
	return false;
}

//=============================================================================================

void RendererContextAGC::clearRect(const ClearQuad& clearQuad)
{
	// TODO: (manderson) support only clearing viewport and MRT (I think the toolkit clear methods automatically clear MRTs).
	// NOTE: (manderson) Doesn't look like the toolkit clear methods support different clear colors for each MRT.
	DisplayResources& displayRes = *(mFrameState.mDisplayRes);
	sce::Agc::Core::BasicContext& ctx = displayRes.mContext;
	const Clear& clear = mFrameState.mFrame->m_view[mFrameState.mView].m_clear;
	sce::Agc::Toolkit::Result tk0{}, tk1{};
	bool haveWork = false;
	if ((clear.m_flags & BGFX_CLEAR_COLOR) != 0)
	{
		if ((clear.m_flags & BGFX_CLEAR_COLOR_USE_PALETTE) != 0)
		{
			uint8_t const index = (uint8_t)bx::uint32_min(BGFX_CONFIG_MAX_COLOR_PALETTE-1, clear.m_index[0]);
			const float* const rgba = mFrameState.mFrame->m_colorPalette[index];
			float const rr = rgba[0];
			float const gg = rgba[1];
			float const bb = rgba[2];
			float const aa = rgba[3];
			tk0 = sce::Agc::Toolkit::clearRenderTargetCs(&ctx.m_dcb, &displayRes.mRenderTarget, sce::Agc::Core::Encoder::encode({ rr, gg , bb, aa }));
			haveWork = true;
		}
		else
		{
			float const rr = clear.m_index[0]*1.0f/255.0f;
			float const gg = clear.m_index[1]*1.0f/255.0f;
			float const bb = clear.m_index[2]*1.0f/255.0f;
			float const aa = clear.m_index[3]*1.0f/255.0f;
			tk0 = sce::Agc::Toolkit::clearRenderTargetCs(&ctx.m_dcb, &displayRes.mRenderTarget, sce::Agc::Core::Encoder::encode({ rr, gg , bb, aa }));
			haveWork = true;
		}
	}

	if ((clear.m_flags & BGFX_CLEAR_DEPTH) != 0)
	{
		mDepthRenderTarget.setDepthClearValue(clear.m_depth);
		tk1 = sce::Agc::Toolkit::clearDepthRenderTargetCs(&ctx.m_dcb, &mDepthRenderTarget);
		haveWork = true;
	}

	if (haveWork)
	{
		ctx.resetToolkitChangesAndSyncToGl2(tk0 | tk1);
	}
}

//=============================================================================================

void RendererContextAGC::viewChanged(const ClearQuad& clearQuad)
{
	mFrameState.mView = mFrameState.mKey.m_view;

	mFrameState.mProgramHandle = { kInvalidHandle };

	// Handle framebuffer change.
	/*if (render->m_view[view].m_fbh.idx != fbh.idx)
	{
		fbh = _render->m_view[view].m_fbh;
		resolutionHeight = _render->m_resolution.height;
		resolutionHeight = setFrameBuffer(fbh, resolutionHeight, discardFlags);
	}*/

	clearRect(clearQuad);

	mFrameState.mViewState.m_rect = mFrameState.mFrame->m_view[mFrameState.mView].m_rect;
	const Rect& scissorRect = mFrameState.mFrame->m_view[mFrameState.mView].m_scissor;
	bool const viewHasScissor = !scissorRect.isZero();
	mFrameState.mScissorRect = viewHasScissor ? scissorRect : mFrameState.mViewState.m_rect;

	// Viewport.
	const Rect& viewport = mFrameState.mViewState.m_rect;
	sce::Agc::CxViewport cxViewport;
	sce::Agc::Core::setViewport(&cxViewport, viewport.m_width, viewport.m_height, viewport.m_x, viewport.m_y, -1.0f, 1.0f);

	DisplayResources& displayRes = *(mFrameState.mDisplayRes);
	sce::Agc::Core::BasicContext& ctx = displayRes.mContext;
	sce::Agc::CxRenderTargetMask const rtMask = sce::Agc::CxRenderTargetMask().init().setMask(0, 0xf);
	ctx.m_sb.setState(rtMask)
		.setState(displayRes.mRenderTarget)
		.setState(mDepthRenderTarget)
		.setState(cxViewport);

	//submitBlit(bs, view);
}

//=============================================================================================

bool RendererContextAGC::submitCompute()
{
	const RenderCompute& compute = mFrameState.mRenderItem->compute;
	if (compute.m_uniformBegin < compute.m_uniformEnd)
	{
		rendererUpdateUniforms(this, mFrameState.mFrame->m_uniformBuffer[compute.m_uniformIdx], compute.m_uniformBegin, compute.m_uniformEnd);
		mUniformClock++;
	}

	// ... do stuff ...

	return true;
}

//=============================================================================================

bool RendererContextAGC::submitDrawCall()
{
	// TODO: (manderson) cache index buffer state.
	const RenderDraw& draw = mFrameState.mRenderItem->draw;
	uint64_t const primType = (draw.m_stateFlags & BGFX_STATE_PT_MASK) >> BGFX_STATE_PT_SHIFT;
	DisplayResources& displayRes = *(mFrameState.mDisplayRes);
	sce::Agc::Core::BasicContext& ctx = displayRes.mContext;
	if (isValid(draw.m_indexBuffer))
	{
		const IndexBuffer& indexBuffer = mIndexBuffers[draw.m_indexBuffer.idx];
		uint32_t const indexSize = draw.isIndex16() ? 2 : 4;
		uint32_t const numIndices = indexBuffer.mSize / indexSize;
		if (draw.m_indexBuffer.idx != mFrameState.mDrawState.m_indexBuffer.idx)
		{
			ctx.m_dcb.setIndexSize(indexSize == 2 ? sce::Agc::IndexSize::k16 : sce::Agc::IndexSize::k32);
			ctx.m_dcb.setIndexBuffer(indexBuffer.mBuffer);
			ctx.m_dcb.setIndexCount(numIndices);
			mFrameState.mDrawState.m_indexBuffer = draw.m_indexBuffer;
		}
		
		if (draw.m_numIndices == UINT32_MAX)
		{
			ctx.drawIndexOffset(0, numIndices);
		}
		else if (draw.m_numIndices >= sPrimTypeInfo[primType].m_min)
		{
			ctx.drawIndexOffset(draw.m_startIndex, draw.m_numIndices);
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
		}
		else if (draw.m_numVertices > sPrimTypeInfo[primType].m_min)
		{
			ctx.drawIndexAuto(draw.m_numVertices);
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

	const RenderDraw& draw = mFrameState.mRenderItem->draw;
	if (draw.m_uniformBegin < draw.m_uniformEnd)
	{
		rendererUpdateUniforms(this, mFrameState.mFrame->m_uniformBuffer[draw.m_uniformIdx], draw.m_uniformBegin, draw.m_uniformEnd);
		mUniformClock++;
	}

	if (isValid(mFrameState.mKey.m_program) && draw.m_streamMask != UINT8_MAX)
	{
		if (!bindProgram())
			return false;
		
		if (!bindVertexAttributes())
			return false;

		bindFixedState();

		submitDrawCall();

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
	ctx.m_dcb.setFlip(mVideoHandle, mPhase, SCE_VIDEO_OUT_FLIP_MODE_VSYNC, 0);
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

		endFrame();
	}

	// Process destroy list.
	tickDestroyList();
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
		if (removed)
		{
			// TODO: (manderson) swap with end - 1 instead of erase, tinystl doesn't have iter_swap...
			it = mDestroyList.erase(it);
		}
	}
}

//=============================================================================================

void RendererContextAGC::blitSetup(TextVideoMemBlitter& blitter)
{
}

//=============================================================================================

void RendererContextAGC::blitRender(TextVideoMemBlitter& blitter, uint32_t numIndices)
{
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
