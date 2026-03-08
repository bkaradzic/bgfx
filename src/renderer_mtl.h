/*
 * Copyright 2011-2025 Attila Kocsis. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef BGFX_RENDERER_METAL_H_HEADER_GUARD
#define BGFX_RENDERER_METAL_H_HEADER_GUARD

#include "bgfx_p.h"

#if BGFX_CONFIG_RENDERER_METAL

#include <metal-cpp/metal.hpp>
#include <CoreFoundation/CoreFoundation.h>

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

#define _MTL_RELEASE(_obj, _expected, _check)                                               \
	BX_MACRO_BLOCK_BEGIN                                                                    \
		if (NULL != _obj)                                                                   \
		{                                                                                   \
			const NS::UInteger count = ((NS::Object*)(const void*)_obj)->retainCount() - 1; \
			_check(isGraphicsDebuggerPresent()                                              \
				|| _expected == count                                                       \
				, "%p RefCount is %d (expected %d). Label: \"%s\"."                         \
				, _obj                                                                      \
				, count                                                                     \
				, _expected                                                                 \
				, bgfx::mtl::getObjectLabel((const void*)_obj)                              \
				);                                                                          \
			BX_UNUSED(count);                                                               \
			((NS::Object*)(const void*)_obj)->release();                                    \
			_obj = NULL;                                                                    \
		}                                                                                   \
	BX_MACRO_BLOCK_END

#define _MTL_CHECK_REFCOUNT(_obj, _expected)                                        \
	BX_MACRO_BLOCK_BEGIN                                                            \
		const NS::UInteger count = ((NS::Object*)(const void*)_obj)->retainCount(); \
		BX_ASSERT(isGraphicsDebuggerPresent()                                       \
			|| _expected == count                                                   \
			, "%p RefCount is %d (expected %d). Label: \"%s\"."                     \
			, _obj                                                                  \
			, count                                                                 \
			, _expected                                                             \
			, bgfx::mtl::getObjectLabel((const void*)_obj)                          \
			);                                                                      \
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
	// Helper to access NS::Object's protected sendMessage for label retrieval
	struct MtlObjAccess : public NS::Object
	{
		static bool hasLabel(const void* _obj)
		{
			return respondsToSelector(_obj, sel_registerName("label"));
		}

		static const char* label(const void* _obj)
		{
			NS::String* str = sendMessage<NS::String*>(_obj, sel_registerName("label"));
			return str ? str->utf8String() : "?!";
		}

		template<typename _Ret, typename... _Args>
		static _Ret send(const void* _obj, SEL _sel, _Args... _args)
		{
			return sendMessage<_Ret>(_obj, _sel, _args...);
		}
	};

	inline const char* getObjectLabel(const void* _obj)
	{
		return MtlObjAccess::hasLabel(_obj) ? MtlObjAccess::label(_obj) : "?!";
	}

	// String conversion helper for metal-cpp API calls that take NS::String*
	inline NS::String* nsstr(const char* _str)
	{
		return NS::String::string(_str, NS::UTF8StringEncoding);
	}

	inline MTL::Library* newLibraryWithSource(MTL::Device* _device, const char* _source)
	{
		NS::Error* error = NULL;
		NS::String* source = NS::String::string(_source, NS::ASCIIStringEncoding);
		MTL::Library* lib = _device->newLibrary(source, (MTL::CompileOptions*)NULL, &error);
		BX_WARN(NULL == error
			, "Shader compilation failed: %s"
			, error->localizedDescription()->utf8String()
			);
		return lib;
	}

	inline MTL::RenderPipelineState* newRenderPipelineStateWithDescriptor(MTL::Device* _device, MTL::RenderPipelineDescriptor* _descriptor)
	{
		NS::Error* error = NULL;
		MTL::RenderPipelineState* state = _device->newRenderPipelineState(_descriptor, &error);
		BX_WARN(NULL == error
			, "newRenderPipelineStateWithDescriptor failed: %s"
			, error->localizedDescription()->utf8String()
			);
		return state;
	}

	inline MTL::RenderPipelineState* newRenderPipelineStateWithDescriptor(
		  MTL::Device* _device
		, MTL::RenderPipelineDescriptor* _descriptor
		, MTL::PipelineOption _options
		, MTL::RenderPipelineReflection** _reflection
		)
	{
		NS::Error* error = NULL;
		MTL::RenderPipelineState* state = _device->newRenderPipelineState(_descriptor, _options, _reflection, &error);
		BX_WARN(NULL == error
			, "newRenderPipelineStateWithDescriptor failed: %s"
			, error->localizedDescription()->utf8String()
			);
		return state;
	}

	inline MTL::ComputePipelineState* newComputePipelineStateWithFunction(
		  MTL::Device* _device
		, MTL::Function* _function
		, MTL::PipelineOption _options
		, MTL::ComputePipelineReflection** _reflection
		)
	{
		NS::Error* error = NULL;
		MTL::ComputePipelineState* state = _device->newComputePipelineState(_function, _options, _reflection, &error);
		BX_WARN(NULL == error
			, "newComputePipelineStateWithFunction failed: %s"
			, error->localizedDescription()->utf8String()
			);
		return state;
	}

	inline MTL::RenderPipelineDescriptor* newRenderPipelineDescriptor()
	{
		return MTL::RenderPipelineDescriptor::alloc()->init();
	}

	inline void reset(MTL::RenderPipelineDescriptor* _desc)
	{
		_desc->reset();
	}

	inline MTL::DepthStencilDescriptor* newDepthStencilDescriptor()
	{
		return MTL::DepthStencilDescriptor::alloc()->init();
	}

	inline MTL::StencilDescriptor* newStencilDescriptor()
	{
		return MTL::StencilDescriptor::alloc()->init();
	}

	inline MTL::RenderPassDescriptor* newRenderPassDescriptor()
	{
		return MTL::RenderPassDescriptor::alloc()->init();
	}

	inline MTL::VertexDescriptor* newVertexDescriptor()
	{
		return MTL::VertexDescriptor::alloc()->init();
	}

	inline void reset(MTL::VertexDescriptor* _desc)
	{
		_desc->reset();
	}

	inline MTL::SamplerDescriptor* newSamplerDescriptor()
	{
		return MTL::SamplerDescriptor::alloc()->init();
	}

	inline MTL::TextureDescriptor* newTextureDescriptor()
	{
		return MTL::TextureDescriptor::alloc()->init();
	}

	inline MTL::CaptureManager* getSharedCaptureManager()
	{
		return MTL::CaptureManager::sharedCaptureManager();
	}

	inline MTL::CaptureDescriptor* newCaptureDescriptor()
	{
		return MTL::CaptureDescriptor::alloc()->init();
	}

	inline MTL::RasterizationRateLayerDescriptor* newRasterizationRateLayerDescriptor(float _rate)
	{
		const float rate[1] = { _rate };
		return MTL::RasterizationRateLayerDescriptor::alloc()->init(MTL::Size::Make(1, 1, 0), rate, rate);
	}

	inline MTL::RasterizationRateMapDescriptor* newRasterizationRateMapDescriptor()
	{
		return MTL::RasterizationRateMapDescriptor::alloc()->init();
	}

	//helper functions
	template<typename T>
	inline void release(T* _obj)
	{
		((NS::Object*)(void*)_obj)->release();
	}

	template<typename T>
	inline void retain(T* _obj)
	{
		((NS::Object*)(void*)_obj)->retain();
	}

	inline const char* utf8String(NS::String* _str)
	{
		return _str->utf8String();
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

		MTL::Buffer*   m_ptr;
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

		MTL::Function* m_function;
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

		MTL::RenderPipelineState*  m_rps;
		MTL::ComputePipelineState* m_cps;
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

		MTL::Texture* getTextureMipLevel(uint8_t _mip);

		MTL::Texture* m_ptr;
		MTL::Texture* m_ptrMsaa;
		MTL::Texture* m_ptrStencil; // for emulating packed depth/stencil formats - only for iOS8...
		MTL::Texture* m_ptrMips[14];
		MTL::SamplerState* m_sampler;
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

		MTL::Texture* currentDrawableTexture();

		CA::MetalLayer* m_metalLayer;
		CA::MetalDrawable* m_drawable;

		MTL::Texture* m_drawableTexture;

		MTL::Texture* m_backBufferColorMsaa;
		MTL::Texture* m_backBufferDepth;
		MTL::Texture* m_backBufferStencil;

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

		void init(MTL::Device* _device);
		void shutdown();
		MTL::CommandBuffer* alloc();
		void kick(bool _endFrame, bool _waitForFinish);
		void finish(bool _finishAll);
		void release(NS::Object* _ptr);

		template<typename T>
		void release(T* _ptr) { release( (NS::Object*)(const void*)_ptr ); }

		void consume();

		bx::Semaphore m_framesSemaphore;

		MTL::CommandQueue*  m_commandQueue;
		MTL::CommandBuffer* m_activeCommandBuffer;

		int m_releaseWriteIndex;
		int m_releaseReadIndex;
		typedef stl::vector<NS::Object*> ResourceArray;
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
		void addHandlers(MTL::CommandBuffer*& _commandBuffer);
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
		void begin(MTL::RenderCommandEncoder*& _rce, Frame* _render, OcclusionQueryHandle _handle);
		void end(MTL::RenderCommandEncoder*& _rce);
		void resolve(Frame* _render, bool _wait = false);
		void invalidate(OcclusionQueryHandle _handle);

		struct Query
		{
			OcclusionQueryHandle m_handle;
		};

		MTL::Buffer* m_buffer;
		Query m_query[BGFX_CONFIG_MAX_OCCLUSION_QUERIES];
		bx::RingBufferControl m_control;
	};

} /* namespace metal */ } // namespace bgfx

#endif // BGFX_CONFIG_RENDERER_METAL

#endif // BGFX_RENDERER_METAL_H_HEADER_GUARD
