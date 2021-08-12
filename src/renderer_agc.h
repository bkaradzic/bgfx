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

	struct Shader
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

	struct Program
	{
		bool create(ShaderHandle const vertexShaderHandle, ShaderHandle const fragmentShaderHandle);
		void destroy();

		ShaderHandle mVertexShaderHandle{ kInvalidHandle };
		ShaderHandle mFragmentShaderHandle{ kInvalidHandle };
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

	struct Texture
	{
		static void setSampler(sce::Agc::Core::Sampler& sampler, uint64_t const flags);
		bool create(uint64_t const flags, uint32_t const size, const uint8_t* const data, uint8_t const mipSkip);
		void destroy();

		uint8_t* mBuffer{};
		uint8_t* mStencilBuffer{};
		sce::Agc::Core::TextureSpec mSpec{};
		sce::Agc::Core::Texture mTexture{};
		sce::Agc::Core::Sampler mSampler{};
		uint64_t mFlags;
		bimg::TextureFormat::Enum mFormat;
	};
	
	struct FrameBuffer
	{
		bool create(uint8_t const num, const Attachment* const attachment);
		void destroy();

		TextureHandle mColorHandles[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS]{};
		sce::Agc::CxRenderTarget mColorTargets[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS]{};
		TextureHandle mDepthHandle{ kInvalidHandle };
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
		uint32_t mBaseVertex;
	};

	struct VertexBindInfo
	{
		VertexBindInfo( ProgramHandle const programHandle, VertexBufferHandle const bufferHandle, VertexLayoutHandle layoutHandle = { kInvalidHandle }, uint32_t const baseVertex = 0 );
		VertexBindInfo( ProgramHandle const programHandle, const RenderDraw& draw);

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
	};

	bool verifyInit(const Init& init);
	bool createDisplayBuffers(const Init& init);
	bool createScanoutBuffers();
	bool createContext();
	void beginFrame(Frame* const frame);
	void waitForGPU();
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
	void tickDestroyList(bool const force = false);

 	// NOTE: (manderson) We add + 1 to each resource type limit to have
	// an explicit unused handle we can use if needed.
	IndexBuffer mIndexBuffers[BGFX_CONFIG_MAX_INDEX_BUFFERS + 1]{};
	VertexBuffer mVertexBuffers[BGFX_CONFIG_MAX_VERTEX_BUFFERS + 1]{};
	Shader mShaders[BGFX_CONFIG_MAX_SHADERS + 1]{};
	Program mPrograms[BGFX_CONFIG_MAX_PROGRAMS + 1]{};
	VertexLayout mVertexLayouts[BGFX_CONFIG_MAX_VERTEX_LAYOUTS + 1]{};
	Texture mTextures[BGFX_CONFIG_MAX_TEXTURES + 1]{};
	FrameBuffer mFrameBuffers[BGFX_CONFIG_MAX_FRAME_BUFFERS + 1]{};
	std::vector<std::function<bool()>> mDestroyList;

	void* mUniforms[BGFX_CONFIG_MAX_UNIFORMS]{};
	UniformRegistry mUniformReg{};

	DisplayResources mDisplayResources[NumDisplayBuffers]{};
	FrameState mFrameState{};
	sce::Agc::CxDepthRenderTarget mDepthRenderTarget{};
	RenderDraw mBlitDraw{};
	RenderBind mBlitBind{};
	RenderDraw mClearDraw{};
	RenderBind mClearBind{};
	UniformHandle mClearQuadColor{kInvalidHandle};
	UniformHandle mClearQuadDepth{kInvalidHandle};
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
