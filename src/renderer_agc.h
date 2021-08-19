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

	enum : size_t
	{
		NumDisplayBuffers = 2,
	
		// TODO: (manderson) make this grow as needed...
		DisplayCommandBufferSize = 4 * 1024 * 1024,
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
	void setShaderUniform(uint8_t const flags, uint32_t const regIndex, const void* const val, uint32_t const numRegs);
	void setShaderUniform4f(uint8_t const flags, uint32_t const regIndex, const void* const val, uint32_t const numRegs);
	void setShaderUniform4x4f(uint8_t const flags, uint32_t const regIndex, const void* const val, uint32_t const numRegs);

	bool init(const Init& init);

private:

	struct InflightCounter
	{
		uint64_t mFrameClock{};
		uint32_t mCount{};
	};

	// We use a shared pointer to track inflight resources so that if a resource update occurs while a
	// resource is inflight we can queue the resource to be discarded once it's not inflight and
	// create a clone with the requested update. The queue used to delete the resource uses the old
	// inflight counter to determine when it is safe to delete the resource and the updated clone uses
	// a new counter. Using this method we can simply write updates to an existing resource without discarding
	// when the resource is not inflight. No double/triple buffering or staging buffers are required as all 
	// resource memory is either directly updated or cloned and updated by the CPU.
	struct Resource
	{
		Resource();
		virtual ~Resource() = default;
		void setInflight();

		std::shared_ptr<InflightCounter> mInflightCounter{};
	};

	struct Shader final : public Resource
	{
		bool create(const Memory& mem);
		void destroy();

		// renderer.h has a template function to push predefined uniforms
		// so these need to be named to match the code in renderer.h
		std::array<PredefinedUniform, PredefinedUniform::Count> m_predefined{};
		uint8_t m_numPredefined{};

		std::array<Attrib::Enum, Attrib::Count> mAttributes{};
		UniformBuffer* mUniforms{};
		uint8_t* mCompiledCode{};
		sce::Agc::Shader* mShader{};
		uint8_t* mUniformBuffer{};
		uint64_t mUniformClock{};
		uint32_t mNumSamplers{};
		uint16_t mUniformBufferSize{};
		uint8_t mNumAttributes{};
	};

	struct Program final : public Resource
	{
		bool create(ShaderHandle const vertexShaderHandle, ShaderHandle const fragmentShaderHandle);
		void destroy();

		ShaderHandle mVertexShaderHandle{kInvalidHandle};
		ShaderHandle mFragmentShaderHandle{kInvalidHandle};
	};

	struct Buffer : public Resource
	{
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

	struct Texture final : public Resource
	{
		static bool tileSurface(void* const tiledSurface, const sce::Agc::Core::TextureSpec& tiledSpec, uint32_t const arraySlice, uint32_t const mipLevel, const void* const untiledSurface, uint32_t const untiledSize, bimg::TextureFormat::Enum const untiledFormat, uint32_t untiledBlockPitch, const sce::AgcGpuAddress::SurfaceRegion& region);
		static void setSampler(sce::Agc::Core::Sampler& sampler, uint64_t const flags);
		bool create(uint64_t const flags, uint32_t const size, const uint8_t* const data, uint8_t const mipSkip);
		bool update(uint8_t const side, uint8_t const mip, const Rect& rect, uint16_t const z, uint16_t const depth, uint16_t const pitch, uint32_t const size, const uint8_t* const data);
		void destroy();

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
		bool create(uint8_t const num, const Attachment* const attachment);
		void destroy();

		std::array<TextureHandle, BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS> mColorHandles{};
		std::array<sce::Agc::CxRenderTarget, BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS> mColorTargets{};
		TextureHandle mDepthHandle{kInvalidHandle};
		sce::Agc::CxDepthRenderTarget mDepthTarget{};
		uint32_t mWidth{};
		uint32_t mHeight{};
		uint32_t mNumAttachments{};
	};

	struct VertexAttribBindInfo
	{
		Attrib::Enum mAttrib{};
		VertexBufferHandle mBufferHandle{};
		VertexLayoutHandle mLayoutHandle{};
		uint32_t mBaseVertex{};
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
		uint32_t mCount{};
		uint32_t mNumBufferVertices{};
	};

	struct DisplayResources
	{
		sce::Agc::CxRenderTarget mRenderTarget{};
		sce::Agc::Core::BasicContext mContext{};
		sce::Agc::Label* mLabel{};
		float* mBorderColorBuffer{};
		std::vector<std::shared_ptr<InflightCounter>> mInflightCounters;
	};

	struct FrameState
	{
		DisplayResources* mDisplayRes{};
		Frame* mFrame{};
		const RenderItem* mRenderItem{};
		const RenderBind* mRenderBind{};
		uint8_t* mUniformBuffer{};
		SortKey mKey{};
		RenderDraw mDrawState{};
		RenderBind mBindState{};
		ViewState mViewState{};
		Rect mViewportState{};
		Rect mScissorState{};
		//BlitState mBlitState{};
		Rect mViewScissor{};
		ProgramHandle mProgramHandle{};
		FrameBufferHandle mFrameBufferHandle{};
		uint64_t mEncodedKey{};
		float mOverrideMVP[16];
		uint32_t mNumItems{};
		uint32_t mItem{};
		uint32_t mItemIdx{};
		uint32_t mUniformBufferSize{};
		uint32_t mNumBufferVertices{};
		uint32_t mVertexAttribHash{};
		uint32_t mNumFrameBufferDraws{};
		uint16_t mView{};
		uint16_t mFixedStateView{};
		uint8_t mNumFrameBufferAttachments{};
		bool mIsCompute{};
		bool mWasCompute{};
		bool mViewChanged{};
		bool mProgramChanged{};
		bool mUniformBufferDirty{};
		bool mWireframeFill{};
		bool mBlitting{};
		bool mFlushFrameBufferColor{};
		bool mFlushFrameBufferDepth{};
	};

	bool verifyInit(const Init& init);
	bool createDisplayBuffers(const Init& init);
	bool createScanoutBuffers();
	bool createContext();
	void beginFrame(Frame* const frame);
	void waitForGPU();
	bool getVertexBindInfo(VertexBindInfo& bindInfo, ProgramHandle const programHandle, const RenderDraw& draw);
	bool getVertexBinding(VertexBinding& binding, const VertexBindInfo& bindInfo);
	void bindFrameBuffer(FrameBufferHandle const frameBufferHandle);
	bool bindUniformBuffer(bool const isFragment);
	void overridePredefined(ShaderHandle const shaderHandle);
	bool bindShaderUniforms(ShaderHandle const shaderHandle, const RenderDraw& draw, bool const isFragment, bool overridePredefined);
	void bindSamplers(const RenderBind& bind, bool const vertexStage, bool const fragmentStage, bool const computeStage);
	bool bindProgram(ProgramHandle const programHandle, const RenderDraw& draw, const RenderBind& bind, bool const overridePredefined);
	bool bindVertexAttributes(const RenderDraw& draw);
	void bindFixedState(const RenderDraw& draw);
	bool submitDrawCall(const RenderDraw& draw);
	bool nextItem();
	void clearRect(const ClearQuad& clearQuad);
	void viewChanged(const ClearQuad& clearQuad);
	bool submitCompute();
	bool submitDraw();
	void endFrame();
	void landResources();
	void tickDestroyList(bool const force = false);

 	// NOTE: (manderson) We add + 1 to each resource type limit to have
	// an explicit unused handle we can use if needed.
	std::array<IndexBuffer, BGFX_CONFIG_MAX_INDEX_BUFFERS + 1> mIndexBuffers{};
	std::array<VertexBuffer,BGFX_CONFIG_MAX_VERTEX_BUFFERS + 1> mVertexBuffers{};
	std::array<Shader, BGFX_CONFIG_MAX_VERTEX_BUFFERS + 1> mShaders{};
	std::array<Program, BGFX_CONFIG_MAX_PROGRAMS + 1> mPrograms{};
	std::array<VertexLayout, BGFX_CONFIG_MAX_VERTEX_LAYOUTS + 1> mVertexLayouts{};
	std::array<Texture, BGFX_CONFIG_MAX_TEXTURES + 1> mTextures{};
	std::array<FrameBuffer, BGFX_CONFIG_MAX_FRAME_BUFFERS + 1> mFrameBuffers{};
	std::vector<std::function<bool()>> mDestroyList;

	std::array<void*, BGFX_CONFIG_MAX_UNIFORMS> mUniforms{};
	UniformRegistry mUniformReg{};

	std::array<DisplayResources, NumDisplayBuffers> mDisplayResources{};
	FrameState mFrameState{};
	sce::Agc::CxDepthRenderTarget mDepthRenderTarget{};
	RenderDraw mBlitDraw{};
	RenderBind mBlitBind{};
	RenderDraw mClearDraw{};
	RenderBind mClearBind{};
	UniformHandle mClearQuadColor{kInvalidHandle};
	UniformHandle mClearQuadDepth{kInvalidHandle};
	uint64_t mFrameClock{};
	uint64_t mUniformClock{};
	int mVideoHandle{};
	uint32_t mWidth{};
	uint32_t mHeight{};
	uint8_t mPhase{};
	bool mVsync{};
};

//=============================================================================================

} } // namespace agc bgfx

//=============================================================================================

#endif // BGFX_CONFIG_RENDERER_AGC

//=============================================================================================

#endif // RENDERER_AGC_H_HEADER_GUARD

//=============================================================================================
