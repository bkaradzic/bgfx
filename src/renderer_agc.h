//=============================================================================================
// Copyright 2011-2021 Branimir Karadzic. All rights reserved.
// License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
//=============================================================================================

#ifndef RENDERER_AGC_H_HEADER_GUARD
#define RENDERER_AGC_H_HEADER_GUARD

//=============================================================================================

#include "bgfx_p.h"

//=============================================================================================

#if BGFX_CONFIG_RENDERER_AGC

//=============================================================================================

#include "renderer.h"
#include <shader/shader_reflection.h>
#include <agc.h>
#include <video_out.h>
#include <kernel.h>
#include <math.h>
#include <functional>
#include <array>
#include <unordered_map>
#include <vector>
#include <memory>

//=============================================================================================

namespace bgfx { namespace agc {

//=============================================================================================

struct RendererContextAGC final : public RendererContextI
{
public:

	enum : uint32_t
	{
		NumDisplayBuffers = 2,
	
		// TODO: (manderson) make this grow as needed...
		DisplayCommandBufferSize = 16 * 1024 * 1024,

		VertexStage = 1 << 0,
		FragmentStage = 1 << 1,
		ComputeStage = 1 << 2,

		Graphics = 1 << 0,
		Compute = 1 << 1,
	};

	static void initEmbeddedShaders();

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
	void createShaderBuffer(ShaderBufferHandle handle, uint32_t size, uint32_t stride) override;
	void updateShaderBuffer(ShaderBufferHandle handle, const Memory* mem) override;
	void destroyShaderBuffer(ShaderBufferHandle handle) override;
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
	void setShaderUniform(uint8_t const flags, uint32_t const regIndex, const void* const val, uint32_t const numRegs);
	void setShaderUniform4f(uint8_t const flags, uint32_t const regIndex, const void* const val, uint32_t const numRegs);
	void setShaderUniform4x4f(uint8_t const flags, uint32_t const regIndex, const void* const val, uint32_t const numRegs);

	void init(const Init& init);

private:

	// We use a shared pointer to track inflight resources so that if a resource update occurs while a
	// resource is inflight we can queue the resource to be discarded once it's not inflight and
	// create a clone with the requested update. The queue used to delete the resource uses the old
	// inflight counter to determine when it is safe to delete the resource and the updated clone uses
	// a new counter. Using this method we can simply write updates to an existing resource without discarding
	// when the resource is not inflight. No double/triple buffering or staging buffers are required as all 
	// resource memory is either directly updated or cloned and updated by the CPU.
	// (Inflight = queued for GPU use).

	struct InflightCounter
	{
		uint64_t mFrameClock{};
		uint32_t mCount{};
	};

	struct Resource
	{
		Resource();
		virtual ~Resource() = default;

		std::shared_ptr<InflightCounter> mInflightCounter;
	};

	struct Shader final : public Resource
	{
		// renderer.h has a template function to push predefined uniforms
		// so these need to be named to match the code in renderer.h
		std::array<PredefinedUniform, PredefinedUniform::Count> m_predefined{};
		uint8_t m_numPredefined{};

		std::array<Attrib::Enum, Attrib::Count> mAttributes{};
		sce::Agc::Core::Buffer mBuffer{};
		UniformBuffer* mUniforms{};
		uint8_t* mCompiledCode{};
		sce::Agc::Shader* mShader{};
		uint8_t* mUniformBuffer{};
		uint8_t* mCommandBuffer{};
		uint64_t mUniformClock{};
		uint64_t mUniformBufferClock{};
		uint16_t mUniformBufferSize{};
		uint8_t mNumTextures{};
		uint8_t mStage{};
		uint8_t mNumAttributes{};
		uint8_t mNumInstanceAttributes{};
		bool mUniformBufferDirty{};
	};

	struct Program final : public Resource
	{
		ShaderHandle mVertexShaderHandle{kInvalidHandle};
		ShaderHandle mFragmentShaderHandle{kInvalidHandle};
	};

	struct Buffer : public Resource
	{
		sce::Agc::Core::Buffer mComputeBuffer{};
		uint8_t* mBuffer{};
		uint32_t mSize{};
		uint16_t mFlags{};
		uint16_t mStride{};

	};

	struct IndexBuffer final : public Buffer
	{
	};

	struct VertexBuffer final : public Buffer
	{
		VertexLayoutHandle mLayoutHandle{kInvalidHandle};
	};

	struct Texture final : public Resource
	{
		uint8_t* mBuffer{};
		uint8_t* mStencilBuffer{};
		sce::Agc::Core::TextureSpec mSpec{};
		sce::Agc::Core::Texture mTexture{};
		sce::Agc::Core::Sampler mSampler{};
		uint64_t mFlags{};
		bimg::TextureFormat::Enum mFormat{bimg::TextureFormat::Count};
	};
	
	struct FrameBuffer final : public Resource
	{
		FrameBuffer();

		std::array<TextureHandle, BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS> mColorHandles;
		std::array<sce::Agc::CxRenderTarget, BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS> mColorTargets{};
		TextureHandle mDepthHandle{kInvalidHandle};
		sce::Agc::CxDepthRenderTarget mDepthTarget{};
		uint32_t mWidth{};
		uint32_t mHeight{};
		uint32_t mNumAttachments{};
	};

	// We hash this, so keep it small.
	struct VertexAttribBindInfo
	{
		uint16_t mBufferIndex;
		uint16_t mAttribParams;			// DWORD 1
		uint32_t mBufferOffset;			// DWORD 2
		uint16_t mAttribOffset;
		uint16_t mStride:15;
		uint16_t mIsInstanceAttrib:1;	// DWORD 3
	};

	struct VertexBindInfo
	{
		std::array<VertexAttribBindInfo, Attrib::Count> mAttribs{};
		uint32_t mCount{};
		uint32_t mHash{};
	};

	struct VertexBinding
	{
		std::array<sce::Agc::Core::Buffer, Attrib::Count> mBuffers{};
		std::array<sce::Agc::Core::VertexAttribute, Attrib::Count> mAttribs{};
		uint32_t mNumVertices{};
		uint32_t mNumInstances{};
		uint32_t mCount{};
	};

	struct ViewPerfCounter
	{
		volatile uint64_t* mGPUTimeStamps[2]{};
		int64_t mCPUTimeStamps[2]{};
		uint16_t mViewId{};
	};

	struct DisplayResources
	{
		sce::Agc::CxRenderTarget mRenderTarget{};
		sce::Agc::Core::BasicContext mContext{};
		sce::Agc::Label* mLabel{};
		float* mBorderColorBuffer{};
		std::array<ViewPerfCounter, BGFX_CONFIG_MAX_VIEWS + 1> mViewPerfCounters{};
		std::vector<std::shared_ptr<InflightCounter>> mInflightCounters{};
		uint32_t mNumViews{};
	};

	struct FrameState
	{
		DisplayResources* mDisplayRes{};
		Frame* mFrame{};
		const RenderItem* mRenderItem{};
		const RenderBind* mRenderBind{};
		ViewPerfCounter* mViewPerfCounter{};
		SortKey mKey{};
		RenderDraw mDrawState{};
		RenderBind mBindState{};
		ViewState mViewState{};
		Rect mViewportState{};
		Rect mScissorState{};
		BlitState mBlitState{};
		Rect mViewScissor{};
		ProgramHandle mProgramHandle{};
		ShaderHandle mShaderHandle{};
		FrameBufferHandle mFrameBufferHandle{};
		float mOverrideMVP[16];
		uint32_t mNumItems{};
		uint32_t mItem{};
		uint32_t mNumVertices{};
		uint32_t mVertexAttribHash{};
		uint16_t mView{};
		uint16_t mFixedStateView{};
		uint8_t mNumFrameBufferAttachments{};
		bool mIsCompute{};
		bool mViewChanged{};
		bool mProgramChanged{};
		bool mWireframeFill{};
		bool mBlitting{};
		bool mHaveColorBuffer{};
		bool mHaveDepthBuffer{};
		bool mShouldFlushGraphics{};
		bool mShouldFlushCompute{};
	};

	struct PerfCounters
	{
		std::array<ViewStats, BGFX_CONFIG_MAX_VIEWS> mViewStats;
		std::array<uint32_t, Topology::Count> mNumInstances{};
		std::array<uint32_t, Topology::Count> mNumPrimsRendered{};
		int64_t mFrameTimeStamp{};
		int64_t mResetTimeStamp{};
		int64_t mDrawTimeStamp{};
		int64_t mCPUFrameTime{};
		int64_t mCPUMinFrameTime{};
		int64_t mCPUMaxFrameTime{};
		int64_t mCPUSubmitTime{};
		int64_t mCPUMinSubmitTime{};
		int64_t mCPUMaxSubmitTime{};
		int64_t mGPUFrameTime{};
		int64_t mGPUMinFrameTime{};
		int64_t mGPUMaxFrameTime{};
		uint32_t mNumViews{};
	};

	void verifyInit(const Init& init);
	void createDisplayBuffers(const Init& init);
	void createScanoutBuffers();
	void createContext();
	void setResourceInflight(Resource& resource);
	void landResources();
	void updateBuffer(Buffer& buffer, uint32_t const offset, uint32_t const size, const uint8_t* const data);
	void destroyBuffer(Buffer& buffer);
	void createVertexBuffer(VertexBuffer& vertexBuffer, VertexLayoutHandle const layoutHandle, uint16_t const flags, uint32_t const size, const uint8_t* const data);
	void destroyVertexBuffer(VertexBuffer& vertexBuffer);
	void createIndexBuffer(IndexBuffer& indexBuffer, uint16_t const flags, uint32_t const size, const uint8_t* const data);
	void destroyIndexBuffer(IndexBuffer& indexBuffer);
	void createShader(Shader& shader, const Memory& mem);
	void destroyShader(Shader& shader);
	void createProgram(Program& program, ShaderHandle const vertexShaderHandle, ShaderHandle const fragmentShaderHandle);
	void destroyProgram(Program& program);
	bool tileSurface(void* const tiledSurface, const sce::Agc::Core::TextureSpec& tiledSpec, uint32_t const arraySlice, uint32_t const mipLevel, const void* const untiledSurface, uint32_t const untiledSize, bimg::TextureFormat::Enum const untiledFormat, uint32_t untiledBlockPitch, const sce::AgcGpuAddress::SurfaceRegion& region);
	void setSampler(sce::Agc::Core::Sampler& sampler, uint64_t const flags);
	void createTexture(Texture& texture, uint64_t const flags, uint32_t const size, const uint8_t* const data, uint8_t const mipSkip);
	void updateTexture(Texture& texture, uint8_t const side, uint8_t const mip, const Rect& rect, uint16_t const z, uint16_t const depth, uint16_t const pitch, uint32_t const size, const uint8_t* const data);
	void destroyTexture(Texture& texture);
	void createFrameBuffer(FrameBuffer& frameBuffer, uint8_t const num, const Attachment* const attachment);
	void destroyFrameBuffer(FrameBuffer& frameBuffer);
	void beginFrame(Frame* const frame);
	void waitForGPU();
	void flushGPU(uint32_t const parts);
	bool nextItem();
	void viewChanged(const ClearQuad& clearQuad);
	void submitViewBlits(uint16_t const view);
	void submitCompute();
	void submitDraw();
	void submitDebugText(TextVideoMemBlitter& textVideoMemBlitter);
	void endFrame();
	void tickDestroyList(bool const force = false);
	void bindFrameBuffer(FrameBufferHandle const frameBufferHandle);
	bool bindVertexAttributes(const RenderDraw& draw);
	bool getVertexBindInfo(VertexBindInfo& bindInfo, ProgramHandle const programHandle, const RenderDraw& draw);
	uint16_t cleanupEncodedAttrib(uint16_t const encodedAttrib);
	bool getVertexBinding(VertexBinding& binding, const VertexBindInfo& bindInfo);
	bool bindProgram(ProgramHandle const programHandle, const RenderItem& item, const RenderBind& bind, bool const isCompute, bool const overridePredefined);
	void bindShaderUniforms(ShaderHandle const shaderHandle, const RenderItem& item, bool const isCompute, bool const overridePredefined);
	void bindUniformBuffer(ShaderHandle const shaderHandle);
	void overridePredefined(ShaderHandle const shaderHandle);
	void bindSamplers(const RenderBind& bind, uint32_t const stages);
	void bindFixedState(const RenderDraw& draw);
	void submitDrawCall(const RenderDraw& draw);
	void submitDispatch(const RenderCompute& compute);
	void clearRect(const ClearQuad& clearQuad);
	void startViewPerfCounter();
	void stopViewPerfCounter();
	void pushMarker(const char* const str);
	void popMarker();

 	// NOTE: (manderson) We add + 1 to the vertex layouts as we use the extra slot
	// for non tracked veretx layouts (clear and blit draws).
	std::array<IndexBuffer, BGFX_CONFIG_MAX_INDEX_BUFFERS> mIndexBuffers{};
	std::array<VertexBuffer,BGFX_CONFIG_MAX_VERTEX_BUFFERS> mVertexBuffers{};
	std::array<Shader, BGFX_CONFIG_MAX_SHADERS> mShaders{};
	std::array<Program, BGFX_CONFIG_MAX_PROGRAMS> mPrograms{};
	std::array<VertexLayout, BGFX_CONFIG_MAX_VERTEX_LAYOUTS + 1> mVertexLayouts{};
	std::array<Texture, BGFX_CONFIG_MAX_TEXTURES> mTextures{};
	std::array<FrameBuffer, BGFX_CONFIG_MAX_FRAME_BUFFERS> mFrameBuffers{};
	std::vector<std::function<bool()>> mDestroyList;
	std::array<void*, BGFX_CONFIG_MAX_UNIFORMS> mUniforms{};
	UniformRegistry mUniformReg{};
	char mViewNames[BGFX_CONFIG_MAX_VIEWS][BGFX_CONFIG_MAX_VIEW_NAME]{};
	std::array<DisplayResources, NumDisplayBuffers> mDisplayResources{};
	FrameState mFrameState{};
	PerfCounters mPerfCounters{};
	sce::Agc::CxDepthRenderTarget mDepthRenderTarget{};
	RenderItem mTextItem{};
	RenderBind mTextBind{};
	RenderItem mClearItem{};
	RenderBind mClearBind{};
	RenderItem mBlitItem{};
	RenderBind mBlitBind{};
	UniformHandle mClearQuadColor{kInvalidHandle};
	UniformHandle mClearQuadDepth{kInvalidHandle};
	UniformHandle mBlitSrcOffset{kInvalidHandle};
	UniformHandle mBlitDstOffset{kInvalidHandle};
	TextVideoMem mTextVideoMem;
	uint64_t mFrameClock{};
	uint64_t mUniformClock{};
	int mVideoHandle{};
	uint32_t mWidth{};
	uint32_t mHeight{};
	uint8_t mPhase{};
	bool mVsync{};
};

//=============================================================================================

void initEmbeddedShaders();

//=============================================================================================

} } // namespace agc bgfx

//=============================================================================================

#endif // BGFX_CONFIG_RENDERER_AGC

//=============================================================================================

#endif // RENDERER_AGC_H_HEADER_GUARD

//=============================================================================================
