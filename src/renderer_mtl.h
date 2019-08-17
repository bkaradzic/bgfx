/*
 * Copyright 2011-2015 Attila Kocsis, Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_RENDERER_METAL_H_HEADER_GUARD
#define BGFX_RENDERER_METAL_H_HEADER_GUARD

#include "bgfx_p.h"

#if BGFX_CONFIG_RENDERER_METAL

#import <QuartzCore/CAMetalLayer.h>
#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>

#if BX_PLATFORM_IOS
#	import <UIKit/UIKit.h>
#endif // BX_PLATFORM_*

#define BGFX_MTL_PROFILER_BEGIN(_view, _abgr)         \
	BX_MACRO_BLOCK_BEGIN                              \
		BGFX_PROFILER_BEGIN(s_viewName[view], _abgr); \
	BX_MACRO_BLOCK_END

#define BGFX_MTL_PROFILER_BEGIN_LITERAL(_name, _abgr)   \
	BX_MACRO_BLOCK_BEGIN                                \
		BGFX_PROFILER_BEGIN_LITERAL("" # _name, _abgr); \
	BX_MACRO_BLOCK_END

#define BGFX_MTL_PROFILER_END() \
	BX_MACRO_BLOCK_BEGIN        \
		BGFX_PROFILER_END();    \
	BX_MACRO_BLOCK_END

namespace bgfx { namespace mtl
{
	//runtime os check
	inline bool iOSVersionEqualOrGreater(const char* _version)
	{
#if BX_PLATFORM_IOS
		return ([[[UIDevice currentDevice] systemVersion] compare:@(_version) options:NSNumericSearch] != NSOrderedAscending);
#else
		BX_UNUSED(_version);
		return false;
#endif
	}

	inline bool macOSVersionEqualOrGreater(
		  NSInteger _majorVersion
		, NSInteger _minorVersion
		, NSInteger _patchVersion
		)
	{
#if BX_PLATFORM_OSX
		NSOperatingSystemVersion v = [[NSProcessInfo processInfo] operatingSystemVersion];
		return (v.majorVersion<<16) + (v.minorVersion<<8) + v.patchVersion >=
		(_majorVersion<<16) + (_minorVersion<<8) + _patchVersion;
#else
		BX_UNUSED(_majorVersion, _minorVersion, _patchVersion);
		return false;
#endif
	}


	// c++ wrapper
	// objects with creation functions starting with 'new' has a refcount 1 after creation, object must be destroyed with release.
	// commandBuffer, commandEncoders are autoreleased objects. Needs AutoreleasePool!

#define MTL_MAX_FRAMES_IN_FLIGHT (3)

#define MTL_CLASS(name)                                   \
	class name                                            \
	{                                                     \
	public:                                               \
		name(id <MTL##name> _obj = nil) : m_obj(_obj) {}  \
		operator id <MTL##name>() const { return m_obj; } \
		id <MTL##name> m_obj;

#define MTL_CLASS_END };

	typedef void (*mtlCallback)(void* userData);

	MTL_CLASS(BlitCommandEncoder)
		void copyFromTexture(
			  id<MTLTexture> _sourceTexture
			, NSUInteger _sourceSlice
			, NSUInteger _sourceLevel
			, MTLOrigin _sourceOrigin
			, MTLSize _sourceSize
			, id<MTLTexture> _destinationTexture
			, NSUInteger _destinationSlice
			, NSUInteger _destinationLevel
			, MTLOrigin _destinationOrigin
			)
		{
			[m_obj copyFromTexture:_sourceTexture sourceSlice:_sourceSlice sourceLevel:_sourceLevel sourceOrigin:_sourceOrigin sourceSize:_sourceSize
						 toTexture:_destinationTexture destinationSlice:_destinationSlice destinationLevel:_destinationLevel destinationOrigin:_destinationOrigin];
		}

		void copyFromBuffer(
			  id<MTLBuffer> _sourceBuffer
			, NSUInteger _sourceOffset
			, id<MTLBuffer> _destinationBuffer
			, NSUInteger _destinationOffset
			, NSUInteger _size
			)
		{
			[m_obj copyFromBuffer:_sourceBuffer	sourceOffset:_sourceOffset toBuffer:_destinationBuffer
				destinationOffset:_destinationOffset size:_size];
		}

		void copyFromBuffer(
			  id<MTLBuffer> _sourceBuffer
			, NSUInteger _sourceOffset
			, NSUInteger _sourceBytesPerRow
			, NSUInteger _sourceBytesPerImage
			, MTLSize _sourceSize
			, id<MTLTexture> _destinationTexture
			, NSUInteger _destinationSlice
			, NSUInteger _destinationLevel
			, MTLOrigin _destinationOrigin
			)
		{
			[m_obj copyFromBuffer:_sourceBuffer sourceOffset:_sourceOffset sourceBytesPerRow:_sourceBytesPerRow
			  sourceBytesPerImage:_sourceBytesPerImage sourceSize:_sourceSize toTexture:_destinationTexture
				 destinationSlice:_destinationSlice destinationLevel:_destinationLevel destinationOrigin:_destinationOrigin];
		}

#if BX_PLATFORM_OSX
		void synchronizeTexture(id<MTLTexture> _texture, NSUInteger _slice, NSUInteger _level)
		{
			[m_obj synchronizeTexture:_texture slice:_slice level:_level];
		}

		void synchronizeResource(id<MTLResource> _resource)
		{
			[m_obj synchronizeResource:_resource];
		}
#endif  // BX_PLATFORM_OSX

		void endEncoding()
		{
			[m_obj endEncoding];
		}
	MTL_CLASS_END

	MTL_CLASS(Buffer)
		void* contents()
		{
			return m_obj.contents;
		}

		uint32_t length()
		{
			return (uint32_t)m_obj.length;
		}

		void setLabel(const char* _label)
		{
			[m_obj setLabel:@(_label)];
		}
	MTL_CLASS_END

	MTL_CLASS(CommandBuffer)
		// Creating Command Encoders
		id<MTLRenderCommandEncoder> renderCommandEncoderWithDescriptor(MTLRenderPassDescriptor* _renderPassDescriptor){
			return [m_obj renderCommandEncoderWithDescriptor:_renderPassDescriptor];
		}

		id<MTLComputeCommandEncoder> computeCommandEncoder()
		{
			return [m_obj computeCommandEncoder];
		}

		id<MTLBlitCommandEncoder> blitCommandEncoder()
		{
			return [m_obj blitCommandEncoder];
		}

		// Scheduling and Executing Commands
		void enqueue()
		{
			[m_obj enqueue];
		}

		void commit()
		{
			[m_obj commit];
		}

		void addScheduledHandler(mtlCallback _cb, void* _data)
		{
			[m_obj addScheduledHandler:^(id <MTLCommandBuffer>){ _cb(_data); }];
		}

		void addCompletedHandler(mtlCallback _cb, void* _data)
		{
			[m_obj addCompletedHandler:^(id <MTLCommandBuffer>){ _cb(_data); }];
		}

		void presentDrawable(id<MTLDrawable> _drawable)
		{
			[m_obj presentDrawable:_drawable];
		}

		void waitUntilCompleted()
		{
			[m_obj waitUntilCompleted];
		}
	MTL_CLASS_END

	MTL_CLASS(CommandQueue)
		id<MTLCommandBuffer> commandBuffer()
		{
			return [m_obj commandBuffer];
		}

		id<MTLCommandBuffer> commandBufferWithUnretainedReferences()
		{
			return [m_obj commandBufferWithUnretainedReferences];
		}
	MTL_CLASS_END

	MTL_CLASS(ComputeCommandEncoder)
		void setComputePipelineState(id<MTLComputePipelineState> _state)
		{
			[m_obj setComputePipelineState:_state];
		}

		void setBuffer(id<MTLBuffer> _buffer, NSUInteger _offset, NSUInteger _index)
		{
			[m_obj setBuffer:_buffer offset:_offset atIndex:_index];
		}

		void setTexture(id<MTLTexture> _texture, NSUInteger _index)
		{
			[m_obj setTexture:_texture atIndex:_index];
		}

		void setSamplerState(id<MTLSamplerState> _sampler, NSUInteger _index)
		{
			[m_obj setSamplerState:_sampler atIndex:_index];
		}

		void dispatchThreadgroups(MTLSize _threadgroupsPerGrid, MTLSize _threadsPerThreadgroup)
		{
			[m_obj dispatchThreadgroups:_threadgroupsPerGrid threadsPerThreadgroup:_threadsPerThreadgroup];
		}

		void dispatchThreadgroupsWithIndirectBuffer(id <MTLBuffer> _indirectBuffer,
												NSUInteger _indirectBufferOffset, MTLSize _threadsPerThreadgroup)
		{
			[m_obj dispatchThreadgroupsWithIndirectBuffer:_indirectBuffer indirectBufferOffset:_indirectBufferOffset threadsPerThreadgroup:_threadsPerThreadgroup];
		}

		void endEncoding()
		{
			[m_obj endEncoding];
		}

		void pushDebugGroup(const char* _string)
		{
			[m_obj pushDebugGroup:@(_string)];
		}

		void popDebugGroup()
		{
			[m_obj popDebugGroup];
		}
	MTL_CLASS_END

	MTL_CLASS(Device)
		bool supportsFeatureSet(MTLFeatureSet _featureSet)
		{
			return [m_obj supportsFeatureSet:_featureSet];
		}

		id<MTLLibrary> newLibraryWithData(const void* _data)
		{
			NSError* error;
			id<MTLLibrary> lib =  [m_obj newLibraryWithData:(dispatch_data_t)_data error:&error];
			BX_WARN(NULL == error
				, "newLibraryWithData failed: %s"
				, [error.localizedDescription cStringUsingEncoding:NSASCIIStringEncoding]
				);
			return lib;
		}

		id<MTLLibrary> newLibraryWithSource(const char* _source)
		{
			NSError* error;
			id<MTLLibrary> lib = [m_obj newLibraryWithSource:@(_source) options:nil error:&error];
			BX_WARN(NULL == error
				, "Shader compilation failed: %s"
				, [error.localizedDescription cStringUsingEncoding:NSASCIIStringEncoding]
				);
			return lib;
		}

		id<MTLCommandQueue> newCommandQueue()
		{
			return [m_obj newCommandQueue];
		}

		id<MTLCommandQueue> newCommandQueueWithMaxCommandBufferCount(NSUInteger _maxCommandBufferCount)
		{
			return [m_obj newCommandQueueWithMaxCommandBufferCount:_maxCommandBufferCount];
		}

		// Creating Resources
		id<MTLBuffer> newBufferWithLength(unsigned int _length, MTLResourceOptions _options)
		{
			return [m_obj newBufferWithLength:_length options:_options ];
		}

		id<MTLBuffer> newBufferWithBytes(const void* _pointer, NSUInteger _length, MTLResourceOptions _options)
		{
			return [m_obj newBufferWithBytes:_pointer length:_length options:_options];
		}

		id<MTLTexture> newTextureWithDescriptor(MTLTextureDescriptor* _descriptor)
		{
			return [m_obj newTextureWithDescriptor:_descriptor];
		}

		id<MTLSamplerState> newSamplerStateWithDescriptor(MTLSamplerDescriptor* _descriptor)
		{
			return [m_obj newSamplerStateWithDescriptor:_descriptor];
		}

		// Creating Command Objects Needed to Render Graphics
		id<MTLDepthStencilState> newDepthStencilStateWithDescriptor(MTLDepthStencilDescriptor* _descriptor)
		{
			return [m_obj newDepthStencilStateWithDescriptor:_descriptor];
		}

		id <MTLRenderPipelineState> newRenderPipelineStateWithDescriptor(MTLRenderPipelineDescriptor* _descriptor)
		{
			NSError* error;
			id <MTLRenderPipelineState> state = [m_obj newRenderPipelineStateWithDescriptor:_descriptor error:&error];
			BX_WARN(NULL == error
				, "newRenderPipelineStateWithDescriptor failed: %s"
				, [error.localizedDescription cStringUsingEncoding:NSASCIIStringEncoding]
				);
			return state;
		}

		id <MTLRenderPipelineState> newRenderPipelineStateWithDescriptor(
			  MTLRenderPipelineDescriptor* _descriptor
			, MTLPipelineOption _options
			, MTLRenderPipelineReflection** _reflection
			)
		{
			NSError* error;
			id <MTLRenderPipelineState> state = [m_obj newRenderPipelineStateWithDescriptor:_descriptor options:_options reflection:_reflection error:&error];

			BX_WARN(NULL == error
				, "newRenderPipelineStateWithDescriptor failed: %s"
				, [error.localizedDescription cStringUsingEncoding:NSASCIIStringEncoding]
				);
			return state;
		}

		// Creating Command Objects Needed to Perform Computational Tasks
		id <MTLComputePipelineState> newComputePipelineStateWithFunction(
			  id <MTLFunction> _computeFunction
			, MTLPipelineOption _options
			, MTLComputePipelineReflection** _reflection
			)
		{
			NSError* error;
			id <MTLComputePipelineState> state = [m_obj newComputePipelineStateWithFunction:_computeFunction options:_options reflection:_reflection error:&error];

			BX_WARN(NULL == error
				, "newComputePipelineStateWithFunction failed: %s"
				, [error.localizedDescription cStringUsingEncoding:NSASCIIStringEncoding]
				);
			return state;
		}

		bool supportsTextureSampleCount(int sampleCount)
		{
			if (BX_ENABLED(BX_PLATFORM_IOS) && !iOSVersionEqualOrGreater("9.0.0") )
				return sampleCount == 1 || sampleCount == 2 ||  sampleCount == 4;
			else
				return [m_obj supportsTextureSampleCount:sampleCount];
		}

		bool depth24Stencil8PixelFormatSupported()
		{
#if BX_PLATFORM_IOS
			return false;
#else
			return m_obj.depth24Stencil8PixelFormatSupported;
#endif // BX_PLATFORM_IOS
		}
	MTL_CLASS_END

	MTL_CLASS(Function)
		NSArray* vertexAttributes()
		{
			return m_obj.vertexAttributes;
		}

		void setLabel(const char* _label)
		{
			if ([m_obj respondsToSelector:@selector(setLabel:)])
			{
				[m_obj setLabel:@(_label)];
			}
		}
	MTL_CLASS_END

	MTL_CLASS(Library)
		id <MTLFunction> newFunctionWithName(const char* _functionName)
		{
			return [m_obj newFunctionWithName:@(_functionName)];
		}
	MTL_CLASS_END

	MTL_CLASS(RenderCommandEncoder)
		// Setting Graphics Rendering State
		void setBlendColor(float _red, float _green, float _blue, float _alpha)
		{
			[m_obj setBlendColorRed:_red green:_green blue:_blue alpha:_alpha];
		}

		void setCullMode(MTLCullMode _cullMode)
		{
			[m_obj setCullMode:_cullMode];
		}

		void setDepthBias(float _depthBias, float _slopeScale, float _clamp)
		{
			[m_obj setDepthBias:_depthBias slopeScale:_slopeScale clamp:_clamp];
		}

		void setDepthStencilState(id<MTLDepthStencilState> _depthStencilState)
		{
			[m_obj setDepthStencilState:_depthStencilState];
		}

		void setFrontFacingWinding(MTLWinding _frontFacingWinding)
		{
			[m_obj setFrontFacingWinding:_frontFacingWinding];
		}

		void setRenderPipelineState(id<MTLRenderPipelineState> _pipelineState)
		{
			[m_obj setRenderPipelineState:_pipelineState];
		}

		void setScissorRect(MTLScissorRect _rect)
		{
			[m_obj setScissorRect:_rect];
		}

		void setStencilReferenceValue(uint32_t _ref)
		{
			[m_obj setStencilReferenceValue:_ref];
		}

		void setTriangleFillMode(MTLTriangleFillMode _fillMode)
		{
			[m_obj setTriangleFillMode:_fillMode];
		}

		void setViewport(MTLViewport _viewport)
		{
			[m_obj setViewport:_viewport];
		}

		void setVisibilityResultMode(MTLVisibilityResultMode _mode, NSUInteger _offset)
		{
			[m_obj setVisibilityResultMode:_mode offset:_offset];
		}

		// Specifying Resources for a Vertex Function
		void setVertexBuffer(id<MTLBuffer> _buffer, NSUInteger _offset, NSUInteger _index)
		{
			[m_obj setVertexBuffer:_buffer offset:_offset atIndex:_index];
		}

		void setVertexSamplerState(id<MTLSamplerState> _sampler, NSUInteger _index)
		{
			[m_obj setVertexSamplerState:_sampler atIndex:_index];
		}

		void setVertexTexture(id<MTLTexture> _texture, NSUInteger _index)
		{
			[m_obj setVertexTexture:_texture atIndex:_index];
		}

		// Specifying Resources for a Fragment Function
		void setFragmentBuffer(id<MTLBuffer> _buffer, NSUInteger _offset, NSUInteger _index)
		{
			[m_obj setFragmentBuffer:_buffer offset:_offset atIndex:_index];
		}

		void setFragmentSamplerState(id<MTLSamplerState> _sampler, NSUInteger _index)
		{
			[m_obj setFragmentSamplerState:_sampler atIndex:_index];
		}

		void setFragmentTexture(id<MTLTexture> _texture, NSUInteger _index)
		{
			[m_obj setFragmentTexture:_texture atIndex:_index];
		}

		//Drawing Geometric Primitives
		//NOTE: not exposing functions without instanceCount, it seems they are just wrappers
		void drawIndexedPrimitives(
			  MTLPrimitiveType _primitiveType
			, NSUInteger _indexCount
			, MTLIndexType _indexType
			, id<MTLBuffer> _indexBuffer
			, NSUInteger _indexBufferOffset
			, NSUInteger _instanceCount
			)
		{
			[m_obj drawIndexedPrimitives:_primitiveType indexCount:_indexCount indexType:_indexType indexBuffer:_indexBuffer indexBufferOffset:_indexBufferOffset instanceCount:_instanceCount];
		}

		void drawPrimitives(
			  MTLPrimitiveType _primitiveType
			, NSUInteger _vertexStart
			, NSUInteger _vertexCount
			, NSUInteger _instanceCount
			)
		{
			[m_obj drawPrimitives:_primitiveType vertexStart:_vertexStart vertexCount:_vertexCount instanceCount:_instanceCount];
		}

		void drawPrimitives(
			  MTLPrimitiveType _primitiveType
			, id <MTLBuffer> _indirectBuffer
			, NSUInteger _indirectBufferOffset)
		{
			[m_obj drawPrimitives:_primitiveType indirectBuffer:_indirectBuffer indirectBufferOffset:_indirectBufferOffset];
		}

		void drawIndexedPrimitives(
			  MTLPrimitiveType _primitiveType
			, MTLIndexType _indexType
			, id <MTLBuffer> _indexBuffer
			, NSUInteger _indexBufferOffset
			, id <MTLBuffer> _indirectBuffer
			, NSUInteger _indirectBufferOffset)
		{
			[m_obj drawIndexedPrimitives:_primitiveType indexType:_indexType indexBuffer:_indexBuffer indexBufferOffset:_indexBufferOffset indirectBuffer:_indirectBuffer indirectBufferOffset:_indirectBufferOffset];
		}

		void insertDebugSignpost(const char* _string)
		{
			[m_obj insertDebugSignpost:@(_string)];
		}

		void pushDebugGroup(const char* _string)
		{
			[m_obj pushDebugGroup:@(_string)];
		}

		void popDebugGroup()
		{
			[m_obj popDebugGroup];
		}

		void endEncoding()
		{
			[m_obj endEncoding];
		}
	MTL_CLASS_END

	MTL_CLASS(Texture)
		// Copying Data into a Texture Image
		void replaceRegion(MTLRegion _region, NSUInteger _level, NSUInteger _slice, const void* _pixelBytes, NSUInteger _bytesPerRow, NSUInteger _bytesPerImage)
		{
			[m_obj replaceRegion:_region mipmapLevel:_level slice:_slice withBytes:_pixelBytes bytesPerRow:_bytesPerRow bytesPerImage:_bytesPerImage];
		}

		// Copying Data from a Texture Image
		void getBytes(void* _pixelBytes, NSUInteger _bytesPerRow, NSUInteger _bytesPerImage, MTLRegion _region, NSUInteger _mipmapLevel, NSUInteger _slice) const
		{
			[m_obj getBytes:_pixelBytes bytesPerRow:_bytesPerRow bytesPerImage:_bytesPerImage fromRegion:_region mipmapLevel:_mipmapLevel slice:_slice];
		}

		// Creating Textures by Reusing Image Data
		id<MTLTexture> newTextureViewWithPixelFormat(MTLPixelFormat _pixelFormat)
		{
			return [m_obj newTextureViewWithPixelFormat:_pixelFormat];
		}

		id<MTLTexture> newTextureViewWithPixelFormat(MTLPixelFormat _pixelFormat, MTLTextureType _textureType, NSRange _levelRange, NSRange _sliceRange)
		{
			return [m_obj newTextureViewWithPixelFormat:_pixelFormat textureType:_textureType levels:_levelRange slices:_sliceRange];
		}

		//properties
		uint32_t width() const
		{
			return (uint32_t)m_obj.width;
		}

		uint32_t height() const
		{
			return (uint32_t)m_obj.height;
		}

		uint32_t arrayLength() const
		{
			return (uint32_t)m_obj.arrayLength;
		}

		MTLPixelFormat pixelFormat() const
		{
			return m_obj.pixelFormat;
		}

		uint32_t sampleCount() const
		{
			return (uint32_t)m_obj.sampleCount;
		}

		MTLTextureType textureType() const
		{
			return m_obj.textureType;
		}

		void setLabel(const char* _label)
		{
			[m_obj setLabel:@(_label)];
		}
	MTL_CLASS_END

	typedef id<MTLComputePipelineState> ComputePipelineState;
	typedef id<MTLDepthStencilState> DepthStencilState;
	typedef id<MTLRenderPipelineState> RenderPipelineState;
	typedef id<MTLSamplerState> SamplerState;

	//descriptors
	//NOTE: [class new] is same as [[class alloc] init]
	typedef MTLRenderPipelineDescriptor* RenderPipelineDescriptor;
	typedef MTLComputePipelineReflection* ComputePipelineReflection;

	inline RenderPipelineDescriptor newRenderPipelineDescriptor()
	{
		return [MTLRenderPipelineDescriptor new];
	}

	inline void reset(RenderPipelineDescriptor _desc)
	{
		[_desc reset];
	}

	typedef MTLRenderPipelineColorAttachmentDescriptor* RenderPipelineColorAttachmentDescriptor;

	typedef MTLDepthStencilDescriptor* DepthStencilDescriptor;

	inline MTLDepthStencilDescriptor* newDepthStencilDescriptor()
	{
		return [MTLDepthStencilDescriptor new];
	}

	typedef MTLStencilDescriptor* StencilDescriptor;

	inline MTLStencilDescriptor* newStencilDescriptor()
	{
		return [MTLStencilDescriptor new];
	}

	typedef MTLRenderPassColorAttachmentDescriptor* RenderPassColorAttachmentDescriptor;
	typedef MTLRenderPassDepthAttachmentDescriptor* RenderPassDepthAttachmentDescriptor;
	typedef MTLRenderPassStencilAttachmentDescriptor* RenderPassStencilAttachmentDescriptor;

	typedef MTLRenderPassDescriptor* RenderPassDescriptor;

	inline MTLRenderPassDescriptor* newRenderPassDescriptor()
	{
		return [MTLRenderPassDescriptor new];
	}

	typedef MTLVertexDescriptor* VertexDescriptor;

	inline MTLVertexDescriptor* newVertexDescriptor()
	{
		return [MTLVertexDescriptor new];
	}

	inline void reset(VertexDescriptor _desc)
	{
		[_desc reset];
	}

	typedef MTLSamplerDescriptor* SamplerDescriptor;

	inline MTLSamplerDescriptor* newSamplerDescriptor()
	{
		return [MTLSamplerDescriptor new];
	}

	typedef MTLTextureDescriptor* TextureDescriptor;

	inline MTLTextureDescriptor* newTextureDescriptor()
	{
		return [MTLTextureDescriptor new];
	}

	typedef MTLRenderPipelineReflection* RenderPipelineReflection;

	//helper functions
	inline void release(NSObject* _obj)
	{
		[_obj release];
	}

	inline void retain(NSObject* _obj)
	{
		[_obj retain];
	}

	inline const char* utf8String(NSString* _str)
	{
		return [_str UTF8String];
	}

#define MTL_RELEASE(_obj)        \
			BX_MACRO_BLOCK_BEGIN \
				[_obj release];  \
				_obj = nil;      \
			BX_MACRO_BLOCK_END

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
			, m_dynamic(NULL)
		{
		}

		void create(uint32_t _size, void* _data, uint16_t _flags, uint16_t _stride = 0, bool _vertex = false);
		void update(uint32_t _offset, uint32_t _size, void* _data, bool _discard = false);

		void destroy()
		{
			MTL_RELEASE(m_ptr);

			if (NULL != m_dynamic)
			{
				BX_DELETE(g_allocator, m_dynamic);
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
			MTL_RELEASE(m_function);

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
			, m_vshConstantBufferAlignmentMask(0)
			, m_fshConstantBufferSize(0)
			, m_fshConstantBufferAlignmentMask(0)
			, m_numPredefined(0)
			, m_rps(NULL)
			, m_cps(NULL)
			{
				m_numThreads[0] = 1;
				m_numThreads[1] = 1;
				m_numThreads[2] = 1;
				for(uint32_t i=0; i<BGFX_CONFIG_MAX_TEXTURE_SAMPLERS; ++i)
					m_bindingTypes[i] = 0;
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

			release(m_rps);
			release(m_cps);
		}

		UniformBuffer* m_vshConstantBuffer;
		UniformBuffer* m_fshConstantBuffer;

		uint32_t m_vshConstantBufferSize;
		uint32_t m_vshConstantBufferAlignmentMask;
		uint32_t m_fshConstantBufferSize;
		uint32_t m_fshConstantBufferAlignmentMask;

		enum
		{
			BindToVertexShader   = 1 << 0,
			BindToFragmentShader = 1 << 1,
		};
		uint8_t m_bindingTypes[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];

		uint16_t 	m_numThreads[3];

		PredefinedUniform m_predefined[PredefinedUniform::Count*2];
		uint8_t m_numPredefined;

		RenderPipelineState m_rps;
		ComputePipelineState m_cps;
	};

	void release(PipelineStateMtl* _ptr)
	{
		BX_DELETE(g_allocator, _ptr);
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
			for(uint32_t ii = 0; ii < BX_COUNTOF(m_ptrMips); ++ii)
			{
				m_ptrMips[ii] = NULL;
			}
		}

		void create(const Memory* _mem, uint64_t _flags, uint8_t _skip);

		void destroy()
		{
			MTL_RELEASE(m_ptr);
			MTL_RELEASE(m_ptrStencil);
			for (uint32_t ii = 0; ii < m_numMips; ++ii)
			{
				MTL_RELEASE(m_ptrMips[ii]);
			}
		}

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
			);

		Texture getTextureMipLevel(int _mip);

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
			: m_metalLayer(nil)
			, m_drawable(nil)
			, m_drawableTexture(nil)
			, m_backBufferColorMsaa()
			, m_backBufferDepth()
			, m_backBufferStencil()
			, m_maxAnisotropy(0)
		{
		}

		~SwapChainMtl();

		void init(void* _nwh);
		void resize(FrameBufferMtl &_frameBuffer, uint32_t _width, uint32_t _height, uint32_t _flags);

		id <MTLTexture> 	currentDrawableTexture();

		CAMetalLayer* m_metalLayer;
		id <CAMetalDrawable> m_drawable;
		id <MTLTexture> 	 m_drawableTexture;
		Texture m_backBufferColorMsaa;
		Texture m_backBufferDepth;
		Texture m_backBufferStencil;
		uint32_t m_maxAnisotropy;
	};

	struct FrameBufferMtl
	{
		FrameBufferMtl()
			: m_swapChain(NULL)
			, m_nwh(NULL)
			, m_denseIdx(UINT16_MAX)
			, m_pixelFormatHash(0)
			, m_num(0)
		{
			m_depthHandle.idx = kInvalidHandle;
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

		SwapChainMtl* m_swapChain;
		void* m_nwh;
		uint32_t m_width;
		uint32_t m_height;
		uint16_t m_denseIdx;

		uint32_t m_pixelFormatHash;

		TextureHandle m_colorHandle[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS-1];
		TextureHandle m_depthHandle;
		Attachment m_colorAttachment[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS-1];
		Attachment m_depthAttachment;
		uint8_t m_num; // number of color handles
	};

	struct CommandQueueMtl
	{
		CommandQueueMtl()
			: m_releaseWriteIndex(0)
			, m_releaseReadIndex(0)
		{
		}

		void init(Device _device);
		void shutdown();
		CommandBuffer alloc();
		void kick(bool _endFrame, bool _waitForFinish = false);
		void finish(bool _finishAll = false);
		void release(NSObject* _ptr);
		void consume();

		bx::Semaphore m_framesSemaphore;

		CommandQueue  m_commandQueue;
		CommandBuffer m_activeCommandBuffer;

		int m_releaseWriteIndex;
		int m_releaseReadIndex;
		typedef stl::vector<NSObject*> ResourceArray;
		ResourceArray m_release[MTL_MAX_FRAMES_IN_FLIGHT];
	};

	struct TimerQueryMtl
	{
		TimerQueryMtl()
			: m_control(4)
		{
		}

		void init();
		void shutdown();
		uint32_t begin(uint32_t _resultIdx);
		void end(uint32_t _idx);
		void addHandlers(CommandBuffer& _commandBuffer);
		bool get();

		struct Result
		{
			void reset()
			{
				m_begin     = 0;
				m_end       = 0;
				m_pending   = 0;
			}

			uint64_t m_begin;
			uint64_t m_end;
			uint32_t m_pending;
		};

		uint64_t m_begin;
		uint64_t m_end;
		uint64_t m_elapsed;
		uint64_t m_frequency;

		Result m_result[4*2];
		bx::RingBufferControl m_control;
	};

	struct OcclusionQueryMTL
	{
		OcclusionQueryMTL()
			: m_control(BX_COUNTOF(m_query) )
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
