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

//=============================================================================================

// TODO: (manderson) Replace with proper embedded shaders
#include "vs_clear.pssl2.h"
#include "fs_clear0.pssl2.h"

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
		bool create(const Memory& mem, bool const embedded = false);
		void destroy();

		void* mBuf{};
		sce::Agc::Shader* mShader{};
	};

	struct Program
	{
		bool create(Shader* const vsShader, Shader* const psShader);
		void destroy();

		Shader* mVsShader{};
		Shader* mPsShader{};
	};

	struct IndexBuffer
	{
		bool create(const Memory& mem, uint16_t const flags) { return true; };
		void destroy() {};
	};

	struct VertexBuffer
	{
		bool create(const Memory& mem, VertexLayoutHandle const layoutHandle, uint16_t const flags) { return true; };
		void destroy() {};
	};
	
	bool verifyInit(const Init& init);
	bool createDisplayBuffers(const Init& init);
	bool createScanoutBuffers();
	bool createContext();
	bool createEmbeddedProgram(Program& program, const uint8_t* const vsData, size_t const vsSize, const uint8_t* const psData, size_t psSize);
	bool createEmbeddedPrograms();

	IndexBuffer mIndexBuffers[BGFX_CONFIG_MAX_INDEX_BUFFERS]{};
	VertexBuffer mVertexBuffers[BGFX_CONFIG_MAX_VERTEX_BUFFERS]{};
	Shader mShaders[BGFX_CONFIG_MAX_SHADERS]{};
	Program mPrograms[BGFX_CONFIG_MAX_PROGRAMS]{};
	VertexLayout mVertexLayouts[BGFX_CONFIG_MAX_VERTEX_LAYOUTS]{};

	void* m_uniforms[BGFX_CONFIG_MAX_UNIFORMS]{};
	UniformRegistry m_uniformReg{};

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

bool RendererContextAGC::Shader::create(const Memory& mem, bool const embedded)
{
	if (embedded)
	{
		mBuf = allocDmem(sce::Agc::SizeAlign(mem.size, sce::Agc::Alignment::kShaderCode));
		memcpy(mBuf, mem.data, mem.size);
		SceShaderBinaryHandle const binaryHandle = sceShaderGetBinaryHandle(mBuf);
		void* const header = (void*)sceShaderGetProgramHeader(binaryHandle);
		const void* const program = sceShaderGetProgram(binaryHandle);
		SceError error = sce::Agc::createShader(&mShader, header, program);
		if (error != SCE_OK)
		{
			freeDmem(mBuf);
			return false;
		}
		return true;
	}
	// TODO: (manderson) parse shader file.
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

bool RendererContextAGC::createEmbeddedProgram(Program& program, const uint8_t* const vsData, size_t const vsSize, const uint8_t* const psData, size_t psSize)
{
	program.mVsShader = new Shader();
	program.mPsShader = new Shader();
	if (!program.mVsShader->create(Memory{(uint8_t*)vsData, (uint32_t)vsSize}, true) ||
		!program.mPsShader->create(Memory{(uint8_t*)psData, (uint32_t)psSize}, true))
	{
		delete program.mVsShader;
		delete program.mPsShader;
		program.mVsShader = nullptr;
		program.mPsShader = nullptr;
		return false;
	}
	return true;
}

//=============================================================================================

bool RendererContextAGC::createEmbeddedPrograms()
{
	return createEmbeddedProgram(mClearProgram, vs_clear_data, vs_clear_size, fs_clear0_data, fs_clear0_size);
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
		!createContext() ||
		!createEmbeddedPrograms())
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
	mIndexBuffers[handle.idx].create(*mem, flags);
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
	bx::memCopy(&ourLayout, &layout, sizeof(VertexLayout) );
	dump(ourLayout);
}

//=============================================================================================

void RendererContextAGC::destroyVertexLayout(VertexLayoutHandle handle)
{
}

//=============================================================================================

void RendererContextAGC::createVertexBuffer(VertexBufferHandle handle, const Memory* mem, VertexLayoutHandle layoutHandle, uint16_t flags)
{
	mVertexBuffers[handle.idx].create(*mem, layoutHandle, flags);
}

//=============================================================================================

void RendererContextAGC::destroyVertexBuffer(VertexBufferHandle handle)
{
	mVertexBuffers[handle.idx].destroy();
}

//=============================================================================================

void RendererContextAGC::createDynamicIndexBuffer(IndexBufferHandle handle, uint32_t size, uint16_t flags)
{
}

//=============================================================================================

void RendererContextAGC::updateDynamicIndexBuffer(IndexBufferHandle handle, uint32_t offset, uint32_t size, const Memory* mem)
{
}

//=============================================================================================

void RendererContextAGC::destroyDynamicIndexBuffer(IndexBufferHandle handle)
{
}

//=============================================================================================

void RendererContextAGC::createDynamicVertexBuffer(VertexBufferHandle handle, uint32_t size, uint16_t flags)
{
}

//=============================================================================================

void RendererContextAGC::updateDynamicVertexBuffer(VertexBufferHandle handle, uint32_t offset, uint32_t size, const Memory* mem)
{
}

//=============================================================================================

void RendererContextAGC::destroyDynamicVertexBuffer(VertexBufferHandle handle)
{
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
	if (NULL != m_uniforms[handle.idx])
	{
		BX_FREE(g_allocator, m_uniforms[handle.idx]);
	}

	const uint32_t size = bx::alignUp(g_uniformTypeSize[type]*num, 16);
	void* data = BX_ALLOC(g_allocator, size);
	bx::memSet(data, 0, size);
	m_uniforms[handle.idx] = data;
	m_uniformReg.add(handle, name);
}

//=============================================================================================

void RendererContextAGC::destroyUniform(UniformHandle handle)
{
	BX_FREE(g_allocator, m_uniforms[handle.idx]);
	m_uniforms[handle.idx] = NULL;
	m_uniformReg.remove(handle);
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
	bx::memCopy(m_uniforms[loc], data, size);
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









	static ViewState viewState{};
	viewState.reset(render);
	SortKey key{};
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

			//const bool viewChanged = key.m_view != view || item == numItems;

			const uint32_t itemIdx  = render->m_sortValues[item];
			const RenderItem& renderItem = render->m_renderItem[itemIdx];
			//const RenderBind& renderBind = render->m_renderItemBind[itemIdx];
			item++;

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

static RendererContextAGC* s_renderAGC;

//=============================================================================================

RendererContextI* rendererCreate(const Init& init)
{
	BX_UNUSED(init);
	s_renderAGC = BX_NEW(g_allocator, RendererContextAGC);
	if (!s_renderAGC->init(init) )
	{
		BX_DELETE(g_allocator, s_renderAGC);
		s_renderAGC = NULL;
	}
	return s_renderAGC;
}

//=============================================================================================

void rendererDestroy()
{
	BX_DELETE(g_allocator, s_renderAGC);
	s_renderAGC = NULL;
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
