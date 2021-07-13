//=============================================================================================
// Copyright 2011-2021 Branimir Karadzic. All rights reserved.
// License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
//=============================================================================================

#include "bgfx_p.h"

//=============================================================================================

#if BGFX_CONFIG_RENDERER_AGC

//=============================================================================================

#include <kernel.h>
#include <agc.h>
#include <video_out.h>
#include <math.h>
#include <shader/shader_reflection.h>
#include "renderer.h"
#include <functional>
#include <array>

//=============================================================================================

namespace bgfx { namespace agc {

//=============================================================================================

struct RendererContextAGC final : public RendererContextI
{
public:

	enum : size_t
	{
		NumDisplayBuffers = 2,
		DisplayCommandBufferSize = 1024 * 1024,
	};

	RendererContextAGC();
	~RendererContextAGC();
	RendererType::Enum getRendererType() const override;
	const char* getRendererName() const override;
	bool isDeviceRemoved() override;
	void flip() override;
	void createIndexBuffer(IndexBufferHandle handle, const Memory* mem, uint16_t flags) override;
	void destroyIndexBuffer(IndexBufferHandle handle) override;
	void createVertexLayout(VertexLayoutHandle handle, const VertexLayout& layout) override;
	void destroyVertexLayout(VertexLayoutHandle handle) override;
	void createVertexBuffer(VertexBufferHandle handle, const Memory* mem, VertexLayoutHandle layoutHandle, uint16_t flags) override;
	void destroyVertexBuffer(VertexBufferHandle handle) override;
	void createDynamicIndexBuffer(IndexBufferHandle handle, uint32_t size, uint16_t flags) override;
	void updateDynamicIndexBuffer(IndexBufferHandle handle, uint32_t offset, uint32_t size, const Memory* mem) override;
	void destroyDynamicIndexBuffer(IndexBufferHandle handle) override;
	void createDynamicVertexBuffer(VertexBufferHandle handle, uint32_t size, uint16_t flags) override;
	void updateDynamicVertexBuffer(VertexBufferHandle handle, uint32_t offset, uint32_t size, const Memory* mem) override;
	void destroyDynamicVertexBuffer(VertexBufferHandle handle) override;
	void createShader(ShaderHandle handle, const Memory* mem) override;
	void destroyShader(ShaderHandle handle) override;
	void createProgram(ProgramHandle handle, ShaderHandle vsh, ShaderHandle fsh) override;
	void destroyProgram(ProgramHandle handle) override;
	void* createTexture(TextureHandle handle, const Memory* mem, uint64_t flags, uint8_t skip) override;
	void updateTextureBegin(TextureHandle handle, uint8_t side, uint8_t mip) override;
	void updateTexture(TextureHandle handle, uint8_t side, uint8_t mip, const Rect& rect, uint16_t z, uint16_t depth, uint16_t pitch, const Memory* mem) override;
	void updateTextureEnd() override;
	void readTexture(TextureHandle handle, void* data, uint8_t mip) override;
	void resizeTexture(TextureHandle handle, uint16_t width, uint16_t height, uint8_t numMips, uint16_t numLayers) override;
	void overrideInternal(TextureHandle handle, uintptr_t ptr) override;
	uintptr_t getInternal(TextureHandle handle) override;
	void destroyTexture(TextureHandle handle) override;
	void createFrameBuffer(FrameBufferHandle handle, uint8_t num, const Attachment* attachment) override;
	void createFrameBuffer(FrameBufferHandle handle, void* nwh, uint32_t width, uint32_t height, TextureFormat::Enum format, TextureFormat::Enum depthFormat) override;
	void destroyFrameBuffer(FrameBufferHandle handle) override;
	void createUniform(UniformHandle handle, UniformType::Enum type, uint16_t num, const char* name) override;
	void destroyUniform(UniformHandle handle) override;
	void requestScreenShot(FrameBufferHandle handle, const char* filePath) override;
	void updateViewName(ViewId id, const char* name) override;
	void updateUniform(uint16_t loc, const void* data, uint32_t size) override;
	void invalidateOcclusionQuery(OcclusionQueryHandle handle) override;
	void setMarker(const char* marker, uint16_t len) override;
	void setName(Handle handle, const char* name, uint16_t len) override;
	void submit(Frame* render, ClearQuad& clearQuad, TextVideoMemBlitter& textVideoMemBlitter) override;
	void blitSetup(TextVideoMemBlitter& blitter) override;
	void blitRender(TextVideoMemBlitter& blitter, uint32_t numIndices) override;

	bool init(const Init& init);

private:

	struct FrameResources
	{
		sce::Agc::CxRenderTarget mRenderTarget{};
		sce::Agc::Core::BasicContext mContext{};
		sce::Agc::Label* mLabel{};
	};

	struct Shader
	{
		bool create(const Memory& mem);
		void destroy();

		UniformBuffer* mUniforms{};
		std::array<PredefinedUniform, PredefinedUniform::Count> mPredefinedUniforms{};
		std::array<int8_t, Attrib::Count> mAttributeSlots{};
		void* mBuf{};
		sce::Agc::Shader* mShader{};
		uint16_t mNumUniforms{};
		uint8_t mNumAttributes{};
		uint8_t mNumPredefinedUniforms{};
	};

	struct Program
	{
		bool create(Shader* const vsShader, Shader* const psShader);
		void destroy();

		Shader* mVsShader{};
		Shader* mPsShader{};
	};

	struct Buffer
	{
	protected:
		Buffer() = default;
	
	public:
		virtual ~Buffer() = default;
		bool update(uint32_t const offset, uint32_t const size, const uint8_t* const data);
		virtual void destroy();

		uint8_t* mBuffer{};
		uint32_t mSize{};
	};

	struct IndexBuffer final : public Buffer
	{
		bool create(uint16_t const flags, uint32_t const size, const uint8_t* const data);
		void destroy() override;

		uint16_t mFlags{};
	};

	struct VertexBuffer final : public Buffer
	{
		bool create(VertexLayoutHandle const layoutHandle, uint16_t const flags, uint32_t const size, const uint8_t* const data);
		void destroy() override;

		VertexLayoutHandle mLayoutHandle{kInvalidHandle};
	};
	
	bool verifyInit(const Init& init);
	bool createDisplayBuffers(const Init& init);
	bool createScanoutBuffers();
	bool createContext();
	void tickDestroyList(bool const force = false);
	void clearRect(ClearQuad& clearQuad, const Rect& rect, const Clear& clear, const float palette[][4]);

	IndexBuffer mIndexBuffers[BGFX_CONFIG_MAX_INDEX_BUFFERS]{};
	VertexBuffer mVertexBuffers[BGFX_CONFIG_MAX_VERTEX_BUFFERS]{};
	Shader mShaders[BGFX_CONFIG_MAX_SHADERS]{};
	Program mPrograms[BGFX_CONFIG_MAX_PROGRAMS]{};
	VertexLayout mVertexLayouts[BGFX_CONFIG_MAX_VERTEX_LAYOUTS]{};
	stl::vector<std::function<bool()>> mDestroyList;

	void* mUniforms[BGFX_CONFIG_MAX_UNIFORMS]{};
	UniformRegistry mUniformReg{};

	FrameResources mFrameResources[NumDisplayBuffers]{};
	sce::Agc::CxDepthRenderTarget mDepthRenderTarget{};
	int mVideoHandle{};
	uint8_t mPhase{};
	Program mClearProgram{};
};

//=============================================================================================

} } // namespace agc bgfx

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

static RendererContextAGC* sRendererAGC;

//=============================================================================================

bool RendererContextAGC::Shader::create(const Memory& mem)
{
	/*mBuf = allocDmem(sce::Agc::SizeAlign(mem.size, sce::Agc::Alignment::kShaderCode));
	bx::memCopy(mBuf, mem.data, mem.size);
	SceShaderBinaryHandle const binaryHandle = sceShaderGetBinaryHandle(mBuf);
	void* const header = (void*)sceShaderGetProgramHeader(binaryHandle);
	const void* const program = sceShaderGetProgram(binaryHandle);
	SceError const error = sce::Agc::createShader(&mShader, header, program);
	if (error != SCE_OK)
	{
		freeDmem(mBuf);
		return false;
	}
	return true;*/

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

	mNumPredefinedUniforms = 0;
	mNumUniforms = count;

	if (count > 0)
	{
		for (uint32_t ii = 0; ii < count; ++ii)
		{
			uint8_t nameSize{};
			bx::read(&reader, nameSize);

			char* name = (char*)alloca(nameSize+1);
			bx::read(&reader, &name, nameSize);
			name[nameSize] = '\0';

			uint8_t type{};
			bx::read(&reader, type);

			uint8_t num{};
			bx::read(&reader, num);

			uint16_t regIndex{};
			bx::read(&reader, regIndex);

			uint16_t regCount{};
			bx::read(&reader, regCount);

			// TODO: (manderson) Maybe this will be there?
			/*if (!isShaderVerLess(magic, 8) )
			{
				uint16_t texInfo = 0;
				bx::read(&reader, texInfo);
			}*/

			const char* kind{"invalid"};

			PredefinedUniform::Enum const predefined{nameToPredefinedUniformEnum(name)};
			if (predefined != PredefinedUniform::Count)
			{
				kind = "predefined";
				mPredefinedUniforms[mNumPredefinedUniforms].m_loc = regIndex;
				mPredefinedUniforms[mNumPredefinedUniforms].m_count = regCount;
				mPredefinedUniforms[mNumPredefinedUniforms].m_type = uint8_t(predefined | fragmentBit);
				mNumPredefinedUniforms++;
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
					mUniforms->writeUniformHandle((UniformType::Enum)(type | fragmentBit), regIndex, info->m_handle, regCount * num);
				}
			}
			else
			{
				kind = "sampler";
				// TODO: (manderson) Capture uniforms?
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

	uint8_t numAttrs{};
	bx::read(&reader, numAttrs);

	bool isInstanced[numAttrs];
	bool atLeastOneInstanced = false;

	std::fill(mAttributeSlots.begin(), mAttributeSlots.end(), -1);

	for (uint32_t ii = 0; ii < numAttrs; ++ii)
	{
		uint8_t slotPlusInstanceFlag;
		bx::read(&reader, slotPlusInstanceFlag);

		constexpr uint8_t IS_INSTANCE_FLAG = 128;
		if (slotPlusInstanceFlag & IS_INSTANCE_FLAG) {
			isInstanced[ii] = true;
			atLeastOneInstanced = true;
		}
		uint8_t const slot = slotPlusInstanceFlag & ~IS_INSTANCE_FLAG;

		uint16_t id;
		bx::read(&reader, id);

		Attrib::Enum attr = idToAttrib(id);

		if (Attrib::Count != attr)
		{
			mAttributeSlots[attr] = static_cast<int8_t>(slot);
			mNumAttributes++;
		}
	}

/*
	if (BGFX_CHUNK_MAGIC_FSH == magic)
	{
		BX_CHECK(m_pixelShader == nullptr,"No m_pixelShader set");
		m_pixelShader = BX_NEW(g_allocator, EmbeddedPixelShaderWithSource);
		m_pixelShader->m_source = source;
		m_pixelShader->initialize(s_renderGNM->m_garlicAllocator, s_renderGNM->m_onionAllocator, "ShaderGNM pixel");
	}
	else if (BGFX_CHUNK_MAGIC_VSH == magic)
	{
		BX_CHECK(m_vertexShader == nullptr,"No m_vertexShader set");
		m_vertexShader = BX_NEW(g_allocator, EmbeddedVertexShaderWithSource);
		m_vertexShader->m_source = source;
		m_vertexShader->initialize(s_renderGNM->m_garlicAllocator, s_renderGNM->m_onionAllocator, "ShaderGNM vertex");
		if (atLeastOneInstanced) {
			Gnm::FetchShaderInstancingMode instancingData[numAttrs];
			for (int i = 0; i < numAttrs; ++i) {
				instancingData[i] = isInstanced[i] ? Gnm::kFetchShaderUseInstanceId : Gnm::kFetchShaderUseVertexIndex;
			}

			m_vertexShader->initializeFetchShader(s_renderGNM->m_garlicAllocator,instancingData,numAttrs);
		}
		else {
			m_vertexShader->initializeFetchShader(s_renderGNM->m_garlicAllocator);
		}
	}
	else
	{
		BGFX_FATAL(BGFX_CHUNK_MAGIC_CSH == magic, bgfx::Fatal::InvalidShader, "Expected shader to be frag,vert, or compute.");
	}
*/

	uint16_t constantBufferSize = 0;
	bx::read(&reader, constantBufferSize);

	if (0 < constantBufferSize)
	{
		//m_constantBufferSize = constantBufferSize;
		//BX_TRACE("\tCB size: %d", m_constantBufferSize);
	}

	return true;
}

//=============================================================================================

void RendererContextAGC::Shader::destroy()
{
	// TODO: (manderson) destroy shader.
}

//=============================================================================================

bool RendererContextAGC::Program::create(Shader* const vsShader, Shader* const psShader)
{
	mVsShader = vsShader;
	mPsShader = psShader;
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
	uint8_t* const newBuffer = allocDmem({mSize, 16});
	if (newBuffer == nullptr)
	{
		return false;
	}
	if (mBuffer != nullptr)
	{
		uint32_t const beforeSize = offset;
		if (beforeSize > 0)
		{
			memcpy(newBuffer, mBuffer, beforeSize);
		}
		uint32_t const afterSize = mSize - (offset + size);
		if (afterSize > 0)
		{
			memcpy(newBuffer + offset + size, mBuffer + offset + size, afterSize);
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
	mSize = size;
	if (data != nullptr)
	{
		return update(0, mSize, data);
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
	mSize = size;
	if (data != nullptr)
	{
		return update(0, mSize, data);
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
	SceError error = sce::Agc::Core::initialize(&mFrameResources[0].mRenderTarget, &rtSpec);
	SCE_AGC_ASSERT(error == SCE_OK);
	if (error != SCE_OK)
		return false;

	// Now that we have the first RT set up, we can create the others. They are identical to the first material, except for the RT memory.
	sce::Agc::CxRenderTarget& baseRt = mFrameResources[0].mRenderTarget;
	for (size_t i = 1; i < NumDisplayBuffers; ++i)
	{
		// You can just memcpy the CxRenderTarget, but doing so of course sidesteps the alignment checks in initialize().
		sce::Agc::CxRenderTarget& rt = mFrameResources[i].mRenderTarget;
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
	mDepthRenderTarget.setDepthClearValue(1.0f);

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
	SceError error = sce::Agc::Core::translate(&spec, &mFrameResources[0].mRenderTarget);
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
		addresses[i].data = mFrameResources[i].mRenderTarget.getDataAddress();
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
		FrameResources& frameRes = mFrameResources[i];
		sce::Agc::Core::BasicContext& ctx = frameRes.mContext;
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
		frameRes.mLabel = (sce::Agc::Label*)allocDmem({ sizeof(sce::Agc::Label), sce::Agc::Alignment::kLabel });
		frameRes.mLabel->m_value = 1; // 1 means "not used by GPU"
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
	mPrograms[handle.idx].create(&mShaders[vsh.idx], isValid(fsh) ? &mShaders[fsh.idx] : nullptr);
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

	const uint32_t size = bx::alignUp(g_uniformTypeSize[type]*num, 16);
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

void RendererContextAGC::clearRect(ClearQuad& clearQuad, const Rect& rect, const Clear& clear, const float palette[][4])
{
#if 0
	// Create AGC Buffer and VertexAttrib table.
				const GLuint defaultVao = m_vao;
				if (0 != defaultVao)
				{
					GL_CHECK(glBindVertexArray(defaultVao) );
				}

				GL_CHECK(glDisable(GL_SCISSOR_TEST) );
				GL_CHECK(glDisable(GL_CULL_FACE) );
				GL_CHECK(glDisable(GL_BLEND) );

				GLboolean colorMask = !!(BGFX_CLEAR_COLOR & _clear.m_flags);
				GL_CHECK(glColorMask(colorMask, colorMask, colorMask, colorMask) );

				if (BGFX_CLEAR_DEPTH & _clear.m_flags)
				{
					GL_CHECK(glEnable(GL_DEPTH_TEST) );
					GL_CHECK(glDepthFunc(GL_ALWAYS) );
					GL_CHECK(glDepthMask(GL_TRUE) );
				}
				else
				{
					GL_CHECK(glDisable(GL_DEPTH_TEST) );
				}

				if (BGFX_CLEAR_STENCIL & _clear.m_flags)
				{
					GL_CHECK(glEnable(GL_STENCIL_TEST) );
					GL_CHECK(glStencilFuncSeparate(GL_FRONT_AND_BACK, GL_ALWAYS, _clear.m_stencil,  0xff) );
					GL_CHECK(glStencilOpSeparate(GL_FRONT_AND_BACK, GL_REPLACE, GL_REPLACE, GL_REPLACE) );
				}
				else
				{
					GL_CHECK(glDisable(GL_STENCIL_TEST) );
				}

				VertexBufferGL& vb = m_vertexBuffers[_clearQuad.m_vb.idx];
				VertexLayout& layout = _clearQuad.m_layout;

				GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vb.m_id) );

				ProgramGL& program = m_program[_clearQuad.m_program[numMrt-1].idx];
				setProgram(program.m_id);
				program.bindAttributesBegin();
				program.bindAttributes(layout, 0);
				program.bindAttributesEnd();

				if (m_clearQuadColor.idx == kInvalidHandle)
				{
					const UniformRegInfo* infoClearColor = mUniformReg.find("bgfx_clear_color");
					if (NULL != infoClearColor)
						m_clearQuadColor = infoClearColor->m_handle;
				}

				if (m_clearQuadDepth.idx == kInvalidHandle)
				{
					const UniformRegInfo* infoClearDepth = mUniformReg.find("bgfx_clear_depth");
					if (NULL != infoClearDepth)
						m_clearQuadDepth = infoClearDepth->m_handle;
				}

				float mrtClearDepth[4] = { g_caps.homogeneousDepth ? (_clear.m_depth * 2.0f - 1.0f) : _clear.m_depth };
				updateUniform(m_clearQuadDepth.idx, mrtClearDepth, sizeof(float)*4);

				float mrtClearColor[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS][4];

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
						_clear.m_index[0] * 1.0f / 255.0f,
						_clear.m_index[1] * 1.0f / 255.0f,
						_clear.m_index[2] * 1.0f / 255.0f,
						_clear.m_index[3] * 1.0f / 255.0f,
					};

					for (uint32_t ii = 0; ii < numMrt; ++ii)
					{
						bx::memCopy(mrtClearColor[ii], rgba, 16);
					}
				}

				updateUniform(m_clearQuadColor.idx, mrtClearColor[0], numMrt * sizeof(float) * 4);

				commit(*program.m_constantBuffer);

				GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP
					, 0
					, 4
					) );
			}
#endif
}

//=============================================================================================

void RendererContextAGC::submit(Frame* render, ClearQuad& clearQuad, TextVideoMemBlitter& textVideoMemBlitter)
{
	const int64_t timerFreq = bx::getHPFrequency();
	const int64_t timeBegin = bx::getHPCounter();

	Stats& perfStats = render->m_perfStats;
	perfStats.cpuTimeBegin  = timeBegin;
	perfStats.cpuTimeEnd    = timeBegin;
	perfStats.cpuTimerFreq  = timerFreq;

	perfStats.gpuTimeBegin  = 0;
	perfStats.gpuTimeEnd    = 0;
	perfStats.gpuTimerFreq  = 1000000000;

	bx::memSet(perfStats.numPrims, 0, sizeof(perfStats.numPrims) );

	perfStats.gpuMemoryMax  = -INT64_MAX;
	perfStats.gpuMemoryUsed = -INT64_MAX;





	ProgramHandle currentProgram{kInvalidHandle};
	ProgramHandle boundProgram{kInvalidHandle};
	SortKey key{};
	uint16_t view{UINT16_MAX};
	FrameBufferHandle fbh{BGFX_CONFIG_MAX_FRAME_BUFFERS};

	BlitState bs{render};

	bool viewHasScissor{false};
	Rect viewScissorRect{};
	viewScissorRect.clear();

	static ViewState viewState{};
	viewState.reset(render);
	//uint16_t view = UINT16_MAX;

	if (0 == (render->m_debug&BGFX_DEBUG_IFH) )
	{
		// Dispatch prologue---------------------------------------------------------------

		// Grab the right context for this frame
		//size_t const prevBuffer = mPhase;
		size_t const curBuffer = (mPhase + 1) % NumDisplayBuffers;
		mPhase = curBuffer;
		FrameResources& frameRes = mFrameResources[curBuffer];

		// Wait till GPU finishes.
		while (frameRes.mLabel->m_value != 1)
		{
			// TODO: (manderson) Non busy wait? Semaphore, Fence?
			sceKernelUsleep(1000);
		}
		frameRes.mLabel->m_value = 0;
		
		sce::Agc::Core::BasicContext& ctx = frameRes.mContext;
		ctx.reset();
		ctx.m_dcb.waitUntilSafeForRendering(mVideoHandle, curBuffer);

		viewState.m_rect = render->m_view[0].m_rect;

		// TODO: (manderson) Replace with clearQuad screen clear.
		static double clr = 0.0;
		clr += (0.0166667 / 2.5);
		clr = fmod(clr, 1.0);
		sce::Agc::Toolkit::Result tk0 = sce::Agc::Toolkit::clearRenderTargetCs(&ctx.m_dcb, &frameRes.mRenderTarget, sce::Agc::Core::Encoder::encode({ clr, clr , clr, 1.0 }));
		sce::Agc::Toolkit::Result tk1 = sce::Agc::Toolkit::clearDepthRenderTargetCs(&ctx.m_dcb, &mDepthRenderTarget);
		ctx.resetToolkitChangesAndSyncToGl2(tk0 | tk1);

		// Dispatch all render items ------------------------------------------------------

		int32_t numItems = render->m_numRenderItems;
		for (int32_t item = 0; item < numItems;)
		{
			const uint64_t encodedKey = render->m_sortKeys[item];
			const bool isCompute = key.decode(encodedKey, render->m_viewRemap);

			const bool viewChanged = key.m_view != view || item == numItems;

			const uint32_t itemIdx  = render->m_sortValues[item];
			const RenderItem& renderItem = render->m_renderItem[itemIdx];
			//const RenderBind& renderBind = render->m_renderItemBind[itemIdx];
			item++;

			// Update View-----------------------------------------------------------------

			if (viewChanged)
			{
				view = key.m_view;
				currentProgram = BGFX_INVALID_HANDLE;

				// Handle framebuffer change.
				/*if (render->m_view[view].m_fbh.idx != fbh.idx)
				{
					fbh = _render->m_view[view].m_fbh;
					resolutionHeight = _render->m_resolution.height;
					resolutionHeight = setFrameBuffer(fbh, resolutionHeight, discardFlags);
				}*/

				viewState.m_rect = render->m_view[view].m_rect;
				const Rect& scissorRect = render->m_view[view].m_scissor;
				viewHasScissor = !scissorRect.isZero();
				viewScissorRect = viewHasScissor ? scissorRect : viewState.m_rect;

				/*GL_CHECK(glViewport(viewState.m_rect.m_x
					, resolutionHeight-viewState.m_rect.m_height-viewState.m_rect.m_y
					, viewState.m_rect.m_width
					, viewState.m_rect.m_height
					) );*/

				Clear& clear = render->m_view[view].m_clear;
				//discardFlags = clear.m_flags & BGFX_CLEAR_DISCARD_MASK;

				if ((clear.m_flags & BGFX_CLEAR_MASK) != BGFX_CLEAR_NONE)
				{
					clearRect(clearQuad, viewState.m_rect, clear, render->m_colorPalette);
				}

				//submitBlit(bs, view);
			}
			
			// Compute dispatch -----------------------------------------------------------

			if (isCompute)
			{
				const RenderCompute& compute = renderItem.compute;
				//bool const constantsChanged = compute.m_uniformBegin < compute.m_uniformEnd;
				rendererUpdateUniforms(this, render->m_uniformBuffer[compute.m_uniformIdx], compute.m_uniformBegin, compute.m_uniformEnd);

				// ... do stuff ...

				continue;
			}
			/*if (wasCompute)
			{
				// ... do transition stuff ...
			}*/

			// Draw dispatch --------------------------------------------------------------

			const RenderDraw& draw = renderItem.draw;
			//bool constantsChanged = draw.m_uniformBegin < draw.m_uniformEnd;
			rendererUpdateUniforms(this, render->m_uniformBuffer[draw.m_uniformIdx], draw.m_uniformBegin, draw.m_uniformEnd);

			// ... do stuff ...
		}

		// Finally submit the workload to the GPU
		ctx.m_dcb.setFlip(mVideoHandle, curBuffer, SCE_VIDEO_OUT_FLIP_MODE_VSYNC, 0);
		sce::Agc::Core::gpuSyncEvent(
			&ctx.m_dcb,
			sce::Agc::Core::SyncWaitMode::kAsynchronous,
			sce::Agc::Core::SyncCacheOp::kClearAll,
			sce::Agc::Core::SyncLabelVisibility::kCpu,
			frameRes.mLabel,
			1);
		SceError error = sce::Agc::submitGraphics(
			sce::Agc::GraphicsQueue::kNormal,
			ctx.m_dcb.getSubmitPointer(),
			ctx.m_dcb.getSubmitSize());
		SCE_AGC_ASSERT(error == SCE_OK);
		error = sce::Agc::suspendPoint();
		SCE_AGC_ASSERT(error == SCE_OK);
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
