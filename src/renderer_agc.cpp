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
	void createIndexBuffer(IndexBufferHandle _handle, const Memory* _mem, uint16_t _flags) override;
	void destroyIndexBuffer(IndexBufferHandle _handle) override;
	void createVertexLayout(VertexLayoutHandle _handle, const VertexLayout& _layout) override;
	void destroyVertexLayout(VertexLayoutHandle _handle) override;
	void createVertexBuffer(VertexBufferHandle _handle, const Memory* _mem, VertexLayoutHandle _layoutHandle, uint16_t _flags) override;
	void destroyVertexBuffer(VertexBufferHandle _handle) override;
	void createDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _size, uint16_t _flags) override;
	void updateDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _offset, uint32_t _size, const Memory* _mem) override;
	void destroyDynamicIndexBuffer(IndexBufferHandle _handle) override;
	void createDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _size, uint16_t _flags) override;
	void updateDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _offset, uint32_t _size, const Memory* _mem) override;
	void destroyDynamicVertexBuffer(VertexBufferHandle _handle) override;
	void createShader(ShaderHandle _handle, const Memory* _mem) override;
	void destroyShader(ShaderHandle _handle) override;
	void createProgram(ProgramHandle _handle, ShaderHandle _vsh, ShaderHandle _fsh) override;
	void destroyProgram(ProgramHandle _handle) override;
	void* createTexture(TextureHandle _handle, const Memory* _mem, uint64_t _flags, uint8_t _skip) override;
	void updateTextureBegin(TextureHandle _handle, uint8_t _side, uint8_t _mip) override;
	void updateTexture(TextureHandle _handle, uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem) override;
	void updateTextureEnd() override;
	void readTexture(TextureHandle _handle, void* _data, uint8_t _mip) override;
	void resizeTexture(TextureHandle _handle, uint16_t _width, uint16_t _height, uint8_t _numMips, uint16_t _numLayers) override;
	void overrideInternal(TextureHandle _handle, uintptr_t _ptr) override;
	uintptr_t getInternal(TextureHandle _handle) override;
	void destroyTexture(TextureHandle _handle) override;
	void createFrameBuffer(FrameBufferHandle _handle, uint8_t _num, const Attachment* _attachment) override;
	void createFrameBuffer(FrameBufferHandle _handle, void* _nwh, uint32_t _width, uint32_t _height, TextureFormat::Enum _format, TextureFormat::Enum _depthFormat) override;
	void destroyFrameBuffer(FrameBufferHandle _handle) override;
	void createUniform(UniformHandle _handle, UniformType::Enum _type, uint16_t _num, const char* _name) override;
	void destroyUniform(UniformHandle _handle) override;
	void requestScreenShot(FrameBufferHandle _handle, const char* _filePath) override;
	void updateViewName(ViewId _id, const char* _name) override;
	void updateUniform(uint16_t _loc, const void* _data, uint32_t _size) override;
	void invalidateOcclusionQuery(OcclusionQueryHandle _handle) override;
	void setMarker(const char* _marker, uint16_t _len) override;
	void setName(Handle _handle, const char* _name, uint16_t _len) override;
	void submit(Frame* _render, ClearQuad& _clearQuad, TextVideoMemBlitter& _textVideoMemBlitter) override;
	void blitSetup(TextVideoMemBlitter& _blitter) override;
	void blitRender(TextVideoMemBlitter& _blitter, uint32_t _numIndices) override;

	bool init(const Init& _init);

private:

	bool createDisplayBuffers(const Init& _init);
	bool createScanoutBuffers();
	bool createContext();

	sce::Agc::CxRenderTarget mRts[NumDisplayBuffers]{};
	sce::Agc::CxDepthRenderTarget mDtr;
	sce::Agc::Core::BasicContext mCtxs[NumDisplayBuffers]{};
	int mVideoHandle{};
	sce::Agc::Label* mFrameLabels{};
};

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

bool RendererContextAGC::createDisplayBuffers(const Init& _init)
{
	// Set up the RenderTarget spec.
	// TODO: (manderson) As I understand it using k8_8_8_8Srgb will cause GPU to do implicit linear to sRGB conversion and
	// I think that Bgfx expects output buffer to have no implicit gamma conversion.
	sce::Agc::Core::RenderTargetSpec rtSpec;
	rtSpec.init();
	rtSpec.m_width = _init.resolution.width;
	rtSpec.m_height = _init.resolution.height;
	rtSpec.m_format = { sce::Agc::Core::TypedFormat::k8_8_8_8UNorm, sce::Agc::Core::Swizzle::kRGBA_R4S4 };
	rtSpec.m_tileMode = sce::Agc::CxRenderTarget::TileMode::kRenderTarget;

	// First, retrieve the size of the render target. We can of course do this before we have any pointers.
	sce::Agc::SizeAlign const rtSize = sce::Agc::Core::getSize(&rtSpec);
	// Then we can allocate the required memory backing and assign it to the spec.
	rtSpec.m_dataAddress = allocDmem(rtSize);
	memset((void*)rtSpec.m_dataAddress, 0x80, rtSize.m_size);

	// We can now initialize the render target. This will check that the dataAddress is properly aligned.
	SceError error = sce::Agc::Core::initialize(&mRts[0], &rtSpec);
	SCE_AGC_ASSERT_MSG(error == SCE_OK, "Failed to initialize RenderTarget.");
	if (error != SCE_OK) return false;

	// Now that we have the first RT set up, we can create the others. They are identical to the first material, except for the RT memory.
	for (size_t i = 1; i < NumDisplayBuffers; ++i)
	{
		// You can just memcpy the CxRenderTarget, but doing so of course sidesteps the alignment checks in initialize().
		memcpy(&mRts[i], &mRts[0], sizeof(mRts[0]));
		mRts[i].setDataAddress(allocDmem(rtSize));
		memset(mRts[i].getDataAddress(), 0x80, rtSize.m_size);
	}

	// Create and set up one depth target
	sce::Agc::Core::DepthRenderTargetSpec drtSpec;
	drtSpec.init();
	drtSpec.m_width = rtSpec.m_width;
	drtSpec.m_height = rtSpec.m_height;
	drtSpec.m_depthFormat = sce::Agc::CxDepthRenderTarget::DepthFormat::k32Float;
	drtSpec.m_stencilFormat = sce::Agc::CxDepthRenderTarget::StencilFormat::k8UInt;
	const sce::Agc::SizeAlign depthBufferSize = sce::Agc::Core::getSize(&drtSpec);
	void* const depthMem = allocDmem(sce::Agc::SizeAlign(depthBufferSize.m_size, depthBufferSize.m_align));
	drtSpec.m_depthReadAddress = depthMem;
	drtSpec.m_depthWriteAddress = depthMem;
	error = sce::Agc::Core::initialize(&mDtr, &drtSpec);
	SCE_AGC_ASSERT(error == SCE_OK);
	if (error != SCE_OK) return false;
	mDtr.setDepthClearValue(1.0f);

	return false;
}

//=============================================================================================

bool RendererContextAGC::createScanoutBuffers()
{
	// First we need to select what we want to display on, which in this case is the TV, also known as SCE_VIDEO_OUT_BUS_TYPE_MAIN.
	mVideoHandle = sceVideoOutOpen(SCE_USER_SERVICE_USER_ID_SYSTEM, SCE_VIDEO_OUT_BUS_TYPE_MAIN, 0, NULL);
	SCE_AGC_ASSERT_MSG(mVideoHandle >= 0, "sceVideoOutOpen() returns handle=%d\n", mVideoHandle);
	if (mVideoHandle < 0) return false;

	// Next we need to inform scan-out about the format of our buffers. This can be done by directly talking to VideoOut or
	// by letting Agc::Core do the translation. To do so, we first need to get a RenderTargetSpec, which we can extract from
	// the list of CxRenderTargets passed into the function.
	sce::Agc::Core::RenderTargetSpec spec;
	SceError error = sce::Agc::Core::translate(&spec, &mRts[0]);
	SCE_AGC_ASSERT(error == SCE_OK);
	if (error != SCE_OK) return false;

	// Next, we use this RenderTargetSpec to create a SceVideoOutBufferAttribute2 which tells VideoOut how it should interpret
	// our buffers. VideoOut needs to know how the color data in the target should be interpreted, and since our pixel shader has
	// been writing linear values into an sRGB RenderTarget, the data VideoOut will find in memory are sRGB encoded.
	// TODO: (manderson) As I understand it Bgfx expects output buffer to not be sRGB (no implicit gamma conversion), but a render
	// should at some point do a gamma conversion (either implicit using an sRGB render target or explicit in shader code) so the
	// output buffer *should* contain sRGB data, so leave this set to kSrgb, not sure what kBt709 is for, I can't find a translate
	// prototype in the docs that takes a second Colorimetry value...?
	SceVideoOutBufferAttribute2 attribute;
	error = sce::Agc::Core::translate(&attribute, &spec, sce::Agc::Core::Colorimetry::kSrgb, sce::Agc::Core::Colorimetry::kBt709);
	SCE_AGC_ASSERT(error == SCE_OK);
	if (error != SCE_OK) return false;

	// Ideally, all buffers should be registered with VideoOut in a single call to sceVideoOutRegisterBuffers2.
	// The reason for this is that the buffers provided in each call get associated with one attribute slot in the API.
	// Even if consecutive calls pass the same SceVideoOutBufferAttribute2 into the function, they still get assigned
	// new attribute slots. When processing a flip, there is significant extra cost associated with switching attribute
	// slots, which should be avoided.
	SceVideoOutBuffers* addresses = (SceVideoOutBuffers*)calloc(NumDisplayBuffers, sizeof(SceVideoOutBuffers));
	for (uint32_t i = 0; i < NumDisplayBuffers; ++i)
	{
		// We could manually call into VideoOut to set up the scan-out buffers, but Agc::Core provides a helper for this.
		addresses[i].data = mRts[i].getDataAddress();
	}

	// VideoOut internally groups scan-out buffers in sets. Every buffer in a set has the same attributes and switching (flipping) between
	// buffers of the same set is a light-weight operation. Switching to a buffer from a different set is significantly more expensive
	// and should be avoided. If an application wants to change the attributes of a scan-out buffer or wants to unregister buffers,
	// these operations are done on whole sets and affect every buffer in the set. This sample only registers one set of buffers and never
	// modifies the set.
	const int32_t setIndex = 0; // Call sceVideoOutUnregisterBuffers with this.
	error = sceVideoOutRegisterBuffers2(mVideoHandle, setIndex, 0, addresses, NumDisplayBuffers, &attribute, SCE_VIDEO_OUT_BUFFER_ATTRIBUTE_CATEGORY_UNCOMPRESSED, nullptr);
	SCE_AGC_ASSERT(error == SCE_OK);
	if (error != SCE_OK) return false;
	free(addresses);

	return true;
}

//=============================================================================================

bool RendererContextAGC::createContext()
{
	// These labels are currently unused, but the intent is to use them for flip tracking.
	mFrameLabels = (sce::Agc::Label*)allocDmem({ sizeof(sce::Agc::Label) * NumDisplayBuffers, sce::Agc::Alignment::kLabel });
	
	// Create a context for each buffered frame
	for (uint32_t i = 0; i < NumDisplayBuffers; ++i)
	{
		mCtxs[i].m_dcb.init(
			allocDmem({ DisplayCommandBufferSize, 4 }),
			DisplayCommandBufferSize,
			nullptr,
			nullptr);
		mCtxs[i].m_bdr.init(
			&mCtxs[i].m_dcb,
			&mCtxs[i].m_dcb);
		mCtxs[i].m_sb.init(
			256, // This is the size of a chunk in the StateBuffer, defining the largest size of a load packet's payload
			&mCtxs[i].m_dcb,
			&mCtxs[i].m_dcb);
		mFrameLabels[i].m_value = 1; // 1 means "not used by GPU"
	}

	return true;
}

//=============================================================================================

bool RendererContextAGC::init(const Init& _init)
{
	// TODO: (manderson) cleanup?

	// Validate display mode.
	// TODO: (manderson) We may want to be more clever here and choose an appropriate mode and 
	// leterbox or scale into it, not sure yet how Bgfx handles this.
	// As I understand it VideoOut will scale from one of these modes to the actual display mode.
	if (!((_init.resolution.width == 3840 && _init.resolution.height == 2160) ||
		  (_init.resolution.width == 3680 && _init.resolution.height == 2070) ||
		  (_init.resolution.width == 3520 && _init.resolution.height == 1980) ||
		  (_init.resolution.width == 3360 && _init.resolution.height == 1890) ||
		  (_init.resolution.width == 3200 && _init.resolution.height == 1800) ||
		  (_init.resolution.width == 2880 && _init.resolution.height == 1620) ||
		  (_init.resolution.width == 2560 && _init.resolution.height == 1440) ||
		  (_init.resolution.width == 2240 && _init.resolution.height == 1260) ||
		  (_init.resolution.width == 1920 && _init.resolution.height == 1080)))
	{
		return false;
	}

	SceError error = sce::Agc::init();
	SCE_AGC_ASSERT(error == SCE_OK);
	if (error != SCE_OK) return false;

	if (!createDisplayBuffers(_init) ||
		!createScanoutBuffers() ||
		!createContext())
	{
		return false;
	}

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

void RendererContextAGC::createIndexBuffer(IndexBufferHandle _handle, const Memory* _mem, uint16_t _flags)
{
}

//=============================================================================================

void RendererContextAGC::destroyIndexBuffer(IndexBufferHandle _handle)
{
}

//=============================================================================================

void RendererContextAGC::createVertexLayout(VertexLayoutHandle _handle, const VertexLayout& _layout)
{
}

//=============================================================================================

void RendererContextAGC::destroyVertexLayout(VertexLayoutHandle _handle)
{
}

//=============================================================================================

void RendererContextAGC::createVertexBuffer(VertexBufferHandle _handle, const Memory* _mem, VertexLayoutHandle _layoutHandle, uint16_t _flags)
{
}

//=============================================================================================

void RendererContextAGC::destroyVertexBuffer(VertexBufferHandle _handle)
{
}

//=============================================================================================

void RendererContextAGC::createDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _size, uint16_t _flags)
{
}

//=============================================================================================

void RendererContextAGC::updateDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _offset, uint32_t _size, const Memory* _mem)
{
}

//=============================================================================================

void RendererContextAGC::destroyDynamicIndexBuffer(IndexBufferHandle _handle)
{
}

//=============================================================================================

void RendererContextAGC::createDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _size, uint16_t _flags)
{
}

//=============================================================================================

void RendererContextAGC::updateDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _offset, uint32_t _size, const Memory* _mem)
{
}

//=============================================================================================

void RendererContextAGC::destroyDynamicVertexBuffer(VertexBufferHandle _handle)
{
}

//=============================================================================================

void RendererContextAGC::createShader(ShaderHandle _handle, const Memory* _mem)
{
}

//=============================================================================================

void RendererContextAGC::destroyShader(ShaderHandle _handle)
{
}

//=============================================================================================

void RendererContextAGC::createProgram(ProgramHandle _handle, ShaderHandle _vsh, ShaderHandle _fsh)
{
}

//=============================================================================================

void RendererContextAGC::destroyProgram(ProgramHandle _handle)
{
}

//=============================================================================================

void* RendererContextAGC::createTexture(TextureHandle _handle, const Memory* _mem, uint64_t _flags, uint8_t _skip)
{
	return NULL;
}

//=============================================================================================

void RendererContextAGC::updateTextureBegin(TextureHandle _handle, uint8_t _side, uint8_t _mip)
{
}

//=============================================================================================

void RendererContextAGC::updateTexture(TextureHandle _handle, uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem)
{
}

//=============================================================================================

void RendererContextAGC::updateTextureEnd()
{
}

//=============================================================================================

void RendererContextAGC::readTexture(TextureHandle _handle, void* _data, uint8_t _mip)
{
}

//=============================================================================================

void RendererContextAGC::resizeTexture(TextureHandle _handle, uint16_t _width, uint16_t _height, uint8_t _numMips, uint16_t _numLayers)
{
}

//=============================================================================================

void RendererContextAGC::overrideInternal(TextureHandle _handle, uintptr_t _ptr)
{
}

//=============================================================================================

uintptr_t RendererContextAGC::getInternal(TextureHandle _handle)
{
	return 0;
}

//=============================================================================================

void RendererContextAGC::destroyTexture(TextureHandle _handle)
{
}

//=============================================================================================

void RendererContextAGC::createFrameBuffer(FrameBufferHandle _handle, uint8_t _num, const Attachment* _attachment)
{
}

//=============================================================================================

void RendererContextAGC::createFrameBuffer(FrameBufferHandle _handle, void* _nwh, uint32_t _width, uint32_t _height, TextureFormat::Enum _format, TextureFormat::Enum _depthFormat)
{
}

//=============================================================================================

void RendererContextAGC::destroyFrameBuffer(FrameBufferHandle _handle)
{
}

//=============================================================================================

void RendererContextAGC::createUniform(UniformHandle _handle, UniformType::Enum _type, uint16_t _num, const char* _name)
{
}

//=============================================================================================

void RendererContextAGC::destroyUniform(UniformHandle _handle)
{
}

//=============================================================================================

void RendererContextAGC::requestScreenShot(FrameBufferHandle _handle, const char* _filePath)
{
}

//=============================================================================================

void RendererContextAGC::updateViewName(ViewId _id, const char* _name)
{
}

//=============================================================================================

void RendererContextAGC::updateUniform(uint16_t _loc, const void* _data, uint32_t _size)
{
}

//=============================================================================================

void RendererContextAGC::invalidateOcclusionQuery(OcclusionQueryHandle _handle)
{
}

//=============================================================================================

void RendererContextAGC::setMarker(const char* _marker, uint16_t _len)
{
}

//=============================================================================================

void RendererContextAGC::setName(Handle _handle, const char* _name, uint16_t _len)
{
}

//=============================================================================================

void RendererContextAGC::submit(Frame* _render, ClearQuad& _clearQuad, TextVideoMemBlitter& _textVideoMemBlitter)
{
	const int64_t timerFreq = bx::getHPFrequency();
	const int64_t timeBegin = bx::getHPCounter();

	Stats& perfStats = _render->m_perfStats;
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

void RendererContextAGC::blitSetup(TextVideoMemBlitter& _blitter)
{
}

//=============================================================================================

void RendererContextAGC::blitRender(TextVideoMemBlitter& _blitter, uint32_t _numIndices)
{
}

//=============================================================================================

static RendererContextAGC* s_renderAGC;

//=============================================================================================

RendererContextI* rendererCreate(const Init& _init)
{
	BX_UNUSED(_init);
	s_renderAGC = BX_NEW(g_allocator, RendererContextAGC);
	if (!s_renderAGC->init(_init) )
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

RendererContextI* rendererCreate(const Init& _init)
{
	BX_UNUSED(_init);
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
