/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */
#include "mtlpp.hpp"

//////////////////////////////////////
// FILE: argument.mm
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #include "argument.hpp"
#include <Metal/MTLArgument.h>

namespace mtlpp
{
    StructMember::StructMember() :
        ns::Object(ns::Handle{ (__bridge void*)[[MTLStructMember alloc] init] })
    {
    }

    ns::String StructMember::GetName() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge MTLStructMember*)m_ptr name] };
    }

    uint32_t StructMember::GetOffset() const
    {
        Validate();
        return uint32_t([(__bridge MTLStructMember*)m_ptr offset]);
    }

    DataType StructMember::GetDataType() const
    {
        Validate();
        return DataType([(__bridge MTLStructMember*)m_ptr dataType]);
    }

    StructType StructMember::GetStructType() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge MTLStructMember*)m_ptr structType] };
    }

    ArrayType StructMember::GetArrayType() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge MTLStructMember*)m_ptr arrayType] };
    }

    StructType::StructType() :
        ns::Object(ns::Handle{ (__bridge void*)[[MTLStructType alloc] init] })
    {
    }

    const ns::Array<StructMember> StructType::GetMembers() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge MTLStructType*)m_ptr members] };
    }

    StructMember StructType::GetMember(const ns::String& name) const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge MTLStructType*)m_ptr memberByName:(__bridge NSString*)name.GetPtr()] };
    }

    ArrayType::ArrayType() :
        ns::Object(ns::Handle{ (__bridge void*)[[MTLArrayType alloc] init] })
    {
    }

    uint32_t ArrayType::GetArrayLength() const
    {
        Validate();
        return uint32_t([(__bridge MTLArrayType*)m_ptr arrayLength]);
    }

    DataType ArrayType::GetElementType() const
    {
        Validate();
        return DataType([(__bridge MTLArrayType*)m_ptr elementType]);
    }

    uint32_t ArrayType::GetStride() const
    {
        Validate();
        return uint32_t([(__bridge MTLArrayType*)m_ptr stride]);
    }

    StructType ArrayType::GetElementStructType() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge MTLArrayType*)m_ptr elementStructType] };
    }

    ArrayType ArrayType::GetElementArrayType() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge MTLArrayType*)m_ptr elementArrayType] };
    }

    Argument::Argument() :
        ns::Object(ns::Handle{ (__bridge void*)[[MTLArgument alloc] init] })
    {
    }

    ns::String Argument::GetName() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge MTLArgument*)m_ptr name] };
    }

    ArgumentType Argument::GetType() const
    {
        Validate();
        return ArgumentType([(__bridge MTLArgument*)m_ptr type]);
    }

    ArgumentAccess Argument::GetAccess() const
    {
        Validate();
        return ArgumentAccess([(__bridge MTLArgument*)m_ptr access]);
    }

    uint32_t Argument::GetIndex() const
    {
        Validate();
        return uint32_t([(__bridge MTLArgument*)m_ptr index]);
    }

    bool Argument::IsActive() const
    {
        Validate();
        return [(__bridge MTLArgument*)m_ptr isActive];
    }

    uint32_t Argument::GetBufferAlignment() const
    {
        Validate();
        return uint32_t([(__bridge MTLArgument*)m_ptr bufferAlignment]);
    }

    uint32_t Argument::GetBufferDataSize() const
    {
        Validate();
        return uint32_t([(__bridge MTLArgument*)m_ptr bufferDataSize]);
    }

    DataType Argument::GetBufferDataType() const
    {
        Validate();
        return DataType([(__bridge MTLArgument*)m_ptr bufferDataType]);
    }

    StructType Argument::GetBufferStructType() const
    {
        Validate();
        return StructType(ns::Handle { (__bridge void*)[(__bridge MTLArgument*)m_ptr bufferStructType] });
    }

    uint32_t Argument::GetThreadgroupMemoryAlignment() const
    {
        Validate();
        return uint32_t([(__bridge MTLArgument*)m_ptr threadgroupMemoryAlignment]);
    }

    uint32_t Argument::GetThreadgroupMemoryDataSize() const
    {
        Validate();
        return uint32_t([(__bridge MTLArgument*)m_ptr threadgroupMemoryDataSize]);
    }

    TextureType Argument::GetTextureType() const
    {
        Validate();
        return TextureType([(__bridge MTLArgument*)m_ptr textureType]);
    }

    DataType Argument::GetTextureDataType() const
    {
        Validate();
        return DataType([(__bridge MTLArgument*)m_ptr textureDataType]);
    }

    bool Argument::IsDepthTexture() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return [(__bridge MTLArgument*)m_ptr isDepthTexture];
#else
        return false;
#endif
    }
}

//////////////////////////////////////
// FILE: blit_command_encoder.mm
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #include "blit_command_encoder.hpp"
#include <Metal/MTLBlitCommandEncoder.h>

namespace mtlpp
{
    void BlitCommandEncoder::Synchronize(const Resource& resource)
    {
        Validate();
#if MTLPP_IS_AVAILABLE_MAC(10_11)
        [(__bridge id<MTLBlitCommandEncoder>)m_ptr
            synchronizeResource:(__bridge id<MTLResource>)resource.GetPtr()];
#endif
    }

    void BlitCommandEncoder::Synchronize(const Texture& texture, uint32_t slice, uint32_t level)
    {
        Validate();
#if MTLPP_IS_AVAILABLE_MAC(10_11)
        [(__bridge id<MTLBlitCommandEncoder>)m_ptr
            synchronizeTexture:(__bridge id<MTLTexture>)texture.GetPtr()
            slice:slice
            level:level];
#endif
    }

    void BlitCommandEncoder::Copy(const Texture& sourceTexture, uint32_t sourceSlice, uint32_t sourceLevel, const Origin& sourceOrigin, const Size& sourceSize, const Texture& destinationTexture, uint32_t destinationSlice, uint32_t destinationLevel, const Origin& destinationOrigin)
    {
        Validate();
        [(__bridge id<MTLBlitCommandEncoder>)m_ptr
            copyFromTexture:(__bridge id<MTLTexture>)sourceTexture.GetPtr()
            sourceSlice:sourceSlice
            sourceLevel:sourceLevel
            sourceOrigin:MTLOriginMake(sourceOrigin.X, sourceOrigin.Y, sourceOrigin.Z)
            sourceSize:MTLSizeMake(sourceSize.Width, sourceSize.Height, sourceSize.Depth)
            toTexture:(__bridge id<MTLTexture>)destinationTexture.GetPtr()
            destinationSlice:destinationSlice
            destinationLevel:destinationLevel
            destinationOrigin:MTLOriginMake(destinationOrigin.X, destinationOrigin.Y, destinationOrigin.Z)];
    }

    void BlitCommandEncoder::Copy(const Buffer& sourceBuffer, uint32_t sourceOffset, uint32_t sourceBytesPerRow, uint32_t sourceBytesPerImage, const Size& sourceSize, const Texture& destinationTexture, uint32_t destinationSlice, uint32_t destinationLevel, const Origin& destinationOrigin)
    {
        Validate();
        [(__bridge id<MTLBlitCommandEncoder>)m_ptr
            copyFromBuffer:(__bridge id<MTLBuffer>)sourceBuffer.GetPtr()
            sourceOffset:sourceOffset
            sourceBytesPerRow:sourceBytesPerRow
            sourceBytesPerImage:sourceBytesPerImage
            sourceSize:MTLSizeMake(sourceSize.Width, sourceSize.Height, sourceSize.Depth)
            toTexture:(__bridge id<MTLTexture>)destinationTexture.GetPtr()
            destinationSlice:destinationSlice
            destinationLevel:destinationLevel
            destinationOrigin:MTLOriginMake(destinationOrigin.X, destinationOrigin.Y, destinationOrigin.Z)];
    }

    void BlitCommandEncoder::Copy(const Buffer& sourceBuffer, uint32_t sourceOffset, uint32_t sourceBytesPerRow, uint32_t sourceBytesPerImage, const Size& sourceSize, const Texture& destinationTexture, uint32_t destinationSlice, uint32_t destinationLevel, const Origin& destinationOrigin, BlitOption options)
    {
        Validate();
        [(__bridge id<MTLBlitCommandEncoder>)m_ptr
            copyFromBuffer:(__bridge id<MTLBuffer>)sourceBuffer.GetPtr()
            sourceOffset:sourceOffset
            sourceBytesPerRow:sourceBytesPerRow
            sourceBytesPerImage:sourceBytesPerImage
            sourceSize:MTLSizeMake(sourceSize.Width, sourceSize.Height, sourceSize.Depth)
            toTexture:(__bridge id<MTLTexture>)destinationTexture.GetPtr()
            destinationSlice:destinationSlice
            destinationLevel:destinationLevel
            destinationOrigin:MTLOriginMake(destinationOrigin.X, destinationOrigin.Y, destinationOrigin.Z)
            options:MTLBlitOption(options)];
    }

    void BlitCommandEncoder::Copy(const Texture& sourceTexture, uint32_t sourceSlice, uint32_t sourceLevel, const Origin& sourceOrigin, const Size& sourceSize, const Buffer& destinationBuffer, uint32_t destinationOffset, uint32_t destinationBytesPerRow, uint32_t destinationBytesPerImage)
    {
        Validate();
        [(__bridge id<MTLBlitCommandEncoder>)m_ptr
            copyFromTexture:(__bridge id<MTLTexture>)sourceTexture.GetPtr()
            sourceSlice:sourceSlice
            sourceLevel:sourceLevel
            sourceOrigin:MTLOriginMake(sourceOrigin.X, sourceOrigin.Y, sourceOrigin.Z)
            sourceSize:MTLSizeMake(sourceSize.Width, sourceSize.Height, sourceSize.Depth)
            toBuffer:(__bridge id<MTLBuffer>)destinationBuffer.GetPtr()
            destinationOffset:destinationOffset
            destinationBytesPerRow:destinationBytesPerRow
            destinationBytesPerImage:destinationBytesPerImage];
    }

    void BlitCommandEncoder::Copy(const Texture& sourceTexture, uint32_t sourceSlice, uint32_t sourceLevel, const Origin& sourceOrigin, const Size& sourceSize, const Buffer& destinationBuffer, uint32_t destinationOffset, uint32_t destinationBytesPerRow, uint32_t destinationBytesPerImage, BlitOption options)
    {
        Validate();
        [(__bridge id<MTLBlitCommandEncoder>)m_ptr
            copyFromTexture:(__bridge id<MTLTexture>)sourceTexture.GetPtr()
            sourceSlice:sourceSlice
            sourceLevel:sourceLevel
            sourceOrigin:MTLOriginMake(sourceOrigin.X, sourceOrigin.Y, sourceOrigin.Z)
            sourceSize:MTLSizeMake(sourceSize.Width, sourceSize.Height, sourceSize.Depth)
            toBuffer:(__bridge id<MTLBuffer>)destinationBuffer.GetPtr()
            destinationOffset:destinationOffset
            destinationBytesPerRow:destinationBytesPerRow
            destinationBytesPerImage:destinationBytesPerImage
            options:MTLBlitOption(options)];
    }

    void BlitCommandEncoder::Copy(const Buffer& sourceBuffer, uint32_t sourceOffset, const Buffer& destinationBuffer, uint32_t destinationOffset, uint32_t size)
    {
        Validate();
        [(__bridge id<MTLBlitCommandEncoder>)m_ptr
            copyFromBuffer:(__bridge id<MTLBuffer>)sourceBuffer.GetPtr()
            sourceOffset:sourceOffset
            toBuffer:(__bridge id<MTLBuffer>)destinationBuffer.GetPtr()
            destinationOffset:destinationOffset
            size:size];
    }

    void BlitCommandEncoder::GenerateMipmaps(const Texture& texture)
    {
        Validate();
        [(__bridge id<MTLBlitCommandEncoder>)m_ptr
            generateMipmapsForTexture:(__bridge id<MTLTexture>)texture.GetPtr()];
    }

    void BlitCommandEncoder::Fill(const Buffer& buffer, const ns::Range& range, uint8_t value)
    {
        Validate();
        [(__bridge id<MTLBlitCommandEncoder>)m_ptr
            fillBuffer:(__bridge id<MTLBuffer>)buffer.GetPtr()
            range:NSMakeRange(range.Location, range.Length)
            value:value];
    }

    void BlitCommandEncoder::UpdateFence(const Fence& fence)
    {
        Validate();
#if MTLPP_IS_AVAILABLE_IOS(10_0)
        [(__bridge id<MTLBlitCommandEncoder>)m_ptr
            updateFence:(__bridge id<MTLFence>)fence.GetPtr()];
#endif
    }

    void BlitCommandEncoder::WaitForFence(const Fence& fence)
    {
#if MTLPP_IS_AVAILABLE_IOS(10_0)
        [(__bridge id<MTLBlitCommandEncoder>)m_ptr
            waitForFence:(__bridge id<MTLFence>)fence.GetPtr()];
#endif
    }
}

//////////////////////////////////////
// FILE: buffer.mm
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #include "buffer.hpp"
// #include "texture.hpp"
#include <Metal/MTLBuffer.h>

namespace mtlpp
{
    uint32_t Buffer::GetLength() const
    {
        Validate();
        return uint32_t([(__bridge id<MTLBuffer>)m_ptr length]);
    }

    void* Buffer::GetContents()
    {
        Validate();
        return [(__bridge id<MTLBuffer>)m_ptr contents];
    }

    void Buffer::DidModify(const ns::Range& range)
    {
        Validate();
#if MTLPP_IS_AVAILABLE_MAC(10_11)
        [(__bridge id<MTLBuffer>)m_ptr didModifyRange:NSMakeRange(range.Location, range.Length)];
#endif
    }

    Texture Buffer::NewTexture(const TextureDescriptor& descriptor, uint32_t offset, uint32_t bytesPerRow)
    {
        Validate();
#if MTLPP_IS_AVAILABLE_IOS(8_0)
        MTLTextureDescriptor* mtlTextureDescriptor = (__bridge MTLTextureDescriptor*)descriptor.GetPtr();
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLBuffer>)m_ptr newTextureWithDescriptor:mtlTextureDescriptor offset:offset bytesPerRow:bytesPerRow] };
#else
        return ns::Handle{ nullptr };
#endif
    }

    void Buffer::AddDebugMarker(const ns::String& marker, const ns::Range& range)
    {
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        [(__bridge id<MTLBuffer>)m_ptr addDebugMarker:(__bridge NSString*)marker.GetPtr() range:NSMakeRange(range.Location, range.Length)];
#endif
    }

    void Buffer::RemoveAllDebugMarkers()
    {
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        [(__bridge id<MTLBuffer>)m_ptr removeAllDebugMarkers];
#endif
    }
}

//////////////////////////////////////
// FILE: command_buffer.mm
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #include "command_buffer.hpp"
// #include "command_queue.hpp"
// #include "drawable.hpp"
// #include "blit_command_encoder.hpp"
// #include "render_command_encoder.hpp"
// #include "compute_command_encoder.hpp"
// #include "parallel_render_command_encoder.hpp"
// #include "render_pass.hpp"

#include <Metal/MTLCommandBuffer.h>

namespace mtlpp
{
    Device CommandBuffer::GetDevice() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLCommandBuffer>)m_ptr device] };
    }

    CommandQueue CommandBuffer::GetCommandQueue() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLCommandBuffer>)m_ptr commandQueue] };
    }

    bool CommandBuffer::GetRetainedReferences() const
    {
        Validate();
        return [(__bridge id<MTLCommandBuffer>)m_ptr retainedReferences];
    }

    ns::String CommandBuffer::GetLabel() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLCommandBuffer>)m_ptr label] };
    }

    CommandBufferStatus CommandBuffer::GetStatus() const
    {
        Validate();
        return CommandBufferStatus([(__bridge id<MTLCommandBuffer>)m_ptr status]);
    }

    ns::Error CommandBuffer::GetError() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLCommandBuffer>)m_ptr error] };
    }

    void CommandBuffer::SetLabel(const ns::String& label)
    {
        Validate();
        [(__bridge id<MTLCommandBuffer>)m_ptr setLabel:(__bridge NSString*)label.GetPtr()];
    }

    void CommandBuffer::Enqueue()
    {
        Validate();
        [(__bridge id<MTLCommandBuffer>)m_ptr enqueue];
    }

    void CommandBuffer::Commit()
    {
        Validate();
        [(__bridge id<MTLCommandBuffer>)m_ptr commit];
    }

    void CommandBuffer::AddScheduledHandler(std::function<void(const CommandBuffer&)> handler)
    {
        Validate();
        [(__bridge id<MTLCommandBuffer>)m_ptr addScheduledHandler:^(id <MTLCommandBuffer> mtlCommandBuffer){
            CommandBuffer commandBuffer(ns::Handle{ (__bridge void*)mtlCommandBuffer });
            handler(commandBuffer);
        }];
    }

    void CommandBuffer::AddCompletedHandler(std::function<void(const CommandBuffer&)> handler)
    {
        Validate();
        [(__bridge id<MTLCommandBuffer>)m_ptr addCompletedHandler:^(id <MTLCommandBuffer> mtlCommandBuffer){
            CommandBuffer commandBuffer(ns::Handle{ (__bridge void*)mtlCommandBuffer });
            handler(commandBuffer);
        }];
    }

    void CommandBuffer::Present(const Drawable& drawable)
    {
        Validate();
        [(__bridge id<MTLCommandBuffer>)m_ptr presentDrawable:(__bridge id<MTLDrawable>)drawable.GetPtr()];
    }

    void CommandBuffer::Present(const Drawable& drawable, double presentationTime)
    {
        Validate();
        [(__bridge id<MTLCommandBuffer>)m_ptr presentDrawable:(__bridge id<MTLDrawable>)drawable.GetPtr() atTime:presentationTime];
    }

    void CommandBuffer::WaitUntilScheduled()
    {
        Validate();
        [(__bridge id<MTLCommandBuffer>)m_ptr waitUntilScheduled];
    }

    void CommandBuffer::WaitUntilCompleted()
    {
        Validate();
        [(__bridge id<MTLCommandBuffer>)m_ptr waitUntilCompleted];
    }

    BlitCommandEncoder CommandBuffer::BlitCommandEncoder()
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLCommandBuffer>)m_ptr blitCommandEncoder] };
    }

    RenderCommandEncoder CommandBuffer::RenderCommandEncoder(const RenderPassDescriptor& renderPassDescriptor)
    {
        Validate();
        MTLRenderPassDescriptor* mtlRenderPassDescriptor = (__bridge MTLRenderPassDescriptor*)renderPassDescriptor.GetPtr();
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLCommandBuffer>)m_ptr renderCommandEncoderWithDescriptor:mtlRenderPassDescriptor] };
    }

    ComputeCommandEncoder CommandBuffer::ComputeCommandEncoder()
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLCommandBuffer>)m_ptr computeCommandEncoder] };
    }

    ParallelRenderCommandEncoder CommandBuffer::ParallelRenderCommandEncoder(const RenderPassDescriptor& renderPassDescriptor)
    {
        Validate();
        MTLRenderPassDescriptor* mtlRenderPassDescriptor = (__bridge MTLRenderPassDescriptor*)renderPassDescriptor.GetPtr();
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLCommandBuffer>)m_ptr parallelRenderCommandEncoderWithDescriptor:mtlRenderPassDescriptor] };
    }
}

//////////////////////////////////////
// FILE: command_encoder.mm
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #include "command_encoder.hpp"
// #include "device.hpp"
#include <Metal/MTLCommandEncoder.h>

namespace mtlpp
{
    Device CommandEncoder::GetDevice() const
    {
        Validate();
        return ns::Handle { (__bridge void*)[(__bridge id<MTLCommandEncoder>)m_ptr device] };
    }

    ns::String CommandEncoder::GetLabel() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLCommandEncoder>)m_ptr label] };
    }

    void CommandEncoder::SetLabel(const ns::String& label)
    {
        Validate();
        [(__bridge id<MTLCommandEncoder>)m_ptr setLabel:(__bridge NSString*)label.GetPtr()];
    }

    void CommandEncoder::EndEncoding()
    {
        Validate();
        [(__bridge id<MTLCommandEncoder>)m_ptr endEncoding];
    }

    void CommandEncoder::InsertDebugSignpost(const ns::String& string)
    {
        Validate();
        [(__bridge id<MTLCommandEncoder>)m_ptr insertDebugSignpost:(__bridge NSString*)string.GetPtr()];
    }

    void CommandEncoder::PushDebugGroup(const ns::String& string)
    {
        Validate();
        [(__bridge id<MTLCommandEncoder>)m_ptr pushDebugGroup:(__bridge NSString*)string.GetPtr()];
    }

    void CommandEncoder::PopDebugGroup()
    {
        Validate();
        [(__bridge id<MTLCommandEncoder>)m_ptr popDebugGroup];
    }
}

//////////////////////////////////////
// FILE: command_queue.mm
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #include "command_queue.hpp"
// #include "command_buffer.hpp"
// #include "device.hpp"
#include <Metal/MTLCommandQueue.h>

namespace mtlpp
{
    ns::String CommandQueue::GetLabel() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLCommandQueue>)m_ptr label] };
    }

    Device CommandQueue::GetDevice() const
    {
        Validate();
        return ns::Handle { (__bridge void*)[(__bridge id<MTLCommandQueue>)m_ptr device] };
    }

    void CommandQueue::SetLabel(const ns::String& label)
    {
        Validate();
        [(__bridge id<MTLCommandQueue>)m_ptr setLabel:(__bridge NSString*)label.GetPtr()];
    }

    CommandBuffer CommandQueue::CommandBufferWithUnretainedReferences()
    {
        Validate();
        return ns::Handle { (__bridge void*)[(__bridge id<MTLCommandQueue>)m_ptr commandBufferWithUnretainedReferences] };
    }

    CommandBuffer CommandQueue::CommandBuffer()
    {
        Validate();
        return ns::Handle { (__bridge void*)[(__bridge id<MTLCommandQueue>)m_ptr commandBuffer] };
    }

    void CommandQueue::InsertDebugCaptureBoundary()
    {
        Validate();
        [(__bridge id<MTLCommandQueue>)m_ptr insertDebugCaptureBoundary];
    }
}

//////////////////////////////////////
// FILE: compute_command_encoder.mm
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #include "compute_command_encoder.hpp"
// #include "buffer.hpp"
// #include "compute_pipeline.hpp"
// #include "sampler.hpp"
#include <Metal/MTLComputeCommandEncoder.h>

namespace mtlpp
{
    void ComputeCommandEncoder::SetComputePipelineState(const ComputePipelineState& state)
    {
        Validate();
        [(__bridge id<MTLComputeCommandEncoder>)m_ptr setComputePipelineState:(__bridge id<MTLComputePipelineState>)state.GetPtr()];
    }

    void ComputeCommandEncoder::SetBytes(const void* data, uint32_t length, uint32_t index)
    {
        Validate();
        [(__bridge id<MTLComputeCommandEncoder>)m_ptr setBytes:data length:length atIndex:index];
    }

    void ComputeCommandEncoder::SetBuffer(const Buffer& buffer, uint32_t offset, uint32_t index)
    {
        Validate();
        [(__bridge id<MTLComputeCommandEncoder>)m_ptr setBuffer:(__bridge id<MTLBuffer>)buffer.GetPtr() offset:offset atIndex:index];
    }

    void ComputeCommandEncoder::SetBufferOffset(uint32_t offset, uint32_t index)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_11, 8_3)
        [(__bridge id<MTLComputeCommandEncoder>)m_ptr setBufferOffset:offset atIndex:index];
#endif
    }

    void ComputeCommandEncoder::SetBuffers(const Buffer* buffers, const uint32_t* offsets, const ns::Range& range)
    {
        Validate();

        const uint32_t maxBuffers = 32;
        assert(range.Length <= maxBuffers);

        id<MTLBuffer> mtlBuffers[maxBuffers];
        NSUInteger    nsOffsets[maxBuffers];
        for (uint32_t i=0; i<range.Length; i++)
        {
            mtlBuffers[i] = (__bridge id<MTLBuffer>)buffers[i].GetPtr();
            nsOffsets[i] = offsets[i];
        }

        [(__bridge id<MTLComputeCommandEncoder>)m_ptr setBuffers:mtlBuffers
                                                         offsets:nsOffsets
                                                       withRange:NSMakeRange(range.Location, range.Length)];
    }

    void ComputeCommandEncoder::SetTexture(const Texture& texture, uint32_t index)
    {
        Validate();
        [(__bridge id<MTLComputeCommandEncoder>)m_ptr setTexture:(__bridge id<MTLTexture>)texture.GetPtr() atIndex:index];
    }

    void ComputeCommandEncoder::SetTextures(const Texture* textures, const ns::Range& range)
    {
        Validate();

        const uint32_t maxTextures = 32;
        assert(range.Length <= maxTextures);

        id<MTLTexture> mtlTextures[maxTextures];
        for (uint32_t i=0; i<range.Length; i++)
            mtlTextures[i] = (__bridge id<MTLTexture>)textures[i].GetPtr();

        [(__bridge id<MTLComputeCommandEncoder>)m_ptr setTextures:mtlTextures
                                                        withRange:NSMakeRange(range.Location, range.Length)];
    }

    void ComputeCommandEncoder::SetSamplerState(const SamplerState& sampler, uint32_t index)
    {
        Validate();
        [(__bridge id<MTLComputeCommandEncoder>)m_ptr setSamplerState:(__bridge id<MTLSamplerState>)sampler.GetPtr() atIndex:index];
    }

    void ComputeCommandEncoder::SetSamplerStates(const SamplerState* samplers, const ns::Range& range)
    {
        Validate();

        const uint32_t maxStates = 32;
        assert(range.Length <= maxStates);

        id<MTLSamplerState> mtlStates[maxStates];
        for (uint32_t i=0; i<range.Length; i++)
            mtlStates[i] = (__bridge id<MTLSamplerState>)samplers[i].GetPtr();

        [(__bridge id<MTLComputeCommandEncoder>)m_ptr setSamplerStates:mtlStates
                                                             withRange:NSMakeRange(range.Location, range.Length)];
    }

    void ComputeCommandEncoder::SetSamplerState(const SamplerState& sampler, float lodMinClamp, float lodMaxClamp, uint32_t index)
    {
        Validate();
        [(__bridge id<MTLComputeCommandEncoder>)m_ptr setSamplerState:(__bridge id<MTLSamplerState>)sampler.GetPtr()
                                                          lodMinClamp:lodMinClamp
                                                          lodMaxClamp:lodMaxClamp
                                                              atIndex:index];
    }

    void ComputeCommandEncoder::SetSamplerStates(const SamplerState* samplers, const float* lodMinClamps, const float* lodMaxClamps, const ns::Range& range)
    {
        Validate();

        const uint32_t maxStates = 32;
        assert(range.Length <= maxStates);

        id<MTLSamplerState> mtlStates[maxStates];
        for (uint32_t i=0; i<range.Length; i++)
            mtlStates[i] = (__bridge id<MTLSamplerState>)samplers[i].GetPtr();

        [(__bridge id<MTLComputeCommandEncoder>)m_ptr setSamplerStates:mtlStates
                                                          lodMinClamps:lodMinClamps
                                                          lodMaxClamps:lodMaxClamps
                                                             withRange:NSMakeRange(range.Location, range.Length)];
    }

    void ComputeCommandEncoder::SetThreadgroupMemory(uint32_t length, uint32_t index)
    {
        Validate();
        [(__bridge id<MTLComputeCommandEncoder>)m_ptr setThreadgroupMemoryLength:length atIndex:index];
    }

    void ComputeCommandEncoder::SetStageInRegion(const Region& region)
    {
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        [(__bridge id<MTLComputeCommandEncoder>)m_ptr setStageInRegion:MTLRegionMake3D(region.Origin.X, region.Origin.Y, region.Origin.Z, region.Size.Width, region.Size.Height, region.Size.Depth)];
#endif
    }

    void ComputeCommandEncoder::DispatchThreadgroups(const Size& threadgroupsPerGrid, const Size& threadsPerThreadgroup)
    {
        Validate();
        MTLSize mtlThreadgroupsPerGrid = MTLSizeMake(threadgroupsPerGrid.Width, threadgroupsPerGrid.Height, threadgroupsPerGrid.Depth);
        MTLSize mtlThreadsPerThreadgroup = MTLSizeMake(threadsPerThreadgroup.Width, threadsPerThreadgroup.Height, threadsPerThreadgroup.Depth);
        [(__bridge id<MTLComputeCommandEncoder>)m_ptr dispatchThreadgroups:mtlThreadgroupsPerGrid threadsPerThreadgroup:mtlThreadsPerThreadgroup];
    }

    void ComputeCommandEncoder::DispatchThreadgroupsWithIndirectBuffer(const Buffer& indirectBuffer, uint32_t indirectBufferOffset, const Size& threadsPerThreadgroup)
    {
        Validate();
        MTLSize mtlThreadsPerThreadgroup = MTLSizeMake(threadsPerThreadgroup.Width, threadsPerThreadgroup.Height, threadsPerThreadgroup.Depth);
        [(__bridge id<MTLComputeCommandEncoder>)m_ptr dispatchThreadgroupsWithIndirectBuffer:(__bridge id<MTLBuffer>)indirectBuffer.GetPtr()
                                                                        indirectBufferOffset:indirectBufferOffset
                                                                       threadsPerThreadgroup:mtlThreadsPerThreadgroup];
    }

    void ComputeCommandEncoder::UpdateFence(const Fence& fence)
    {
        Validate();
#if MTLPP_IS_AVAILABLE_IOS(10_0)
        [(__bridge id<MTLComputeCommandEncoder>)m_ptr updateFence:(__bridge id<MTLFence>)fence.GetPtr()];
#endif
    }

    void ComputeCommandEncoder::WaitForFence(const Fence& fence)
    {
#if MTLPP_IS_AVAILABLE_IOS(10_0)
        [(__bridge id<MTLComputeCommandEncoder>)m_ptr waitForFence:(__bridge id<MTLFence>)fence.GetPtr()];
#endif
    }
}

//////////////////////////////////////
// FILE: compute_pipeline.mm
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #include "compute_pipeline.hpp"
#include <Metal/MTLComputePipeline.h>

namespace mtlpp
{
    ComputePipelineReflection::ComputePipelineReflection() :
        ns::Object(ns::Handle{ (__bridge void*)[[MTLComputePipelineReflection alloc] init] })
    {
    }

    ComputePipelineDescriptor::ComputePipelineDescriptor() :
        ns::Object(ns::Handle{ (__bridge void*)[[MTLComputePipelineDescriptor alloc] init] })
    {
    }

    ns::String ComputePipelineDescriptor::GetLabel() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge MTLComputePipelineDescriptor*)m_ptr label] };
    }

    Function ComputePipelineDescriptor::GetComputeFunction() const
    {
        Validate();
        return ns::Handle { (__bridge void*)[(__bridge MTLComputePipelineDescriptor*)m_ptr computeFunction] };
    }

    bool ComputePipelineDescriptor::GetThreadGroupSizeIsMultipleOfThreadExecutionWidth() const
    {
        Validate();
        return [(__bridge MTLComputePipelineDescriptor*)m_ptr threadGroupSizeIsMultipleOfThreadExecutionWidth];
    }

    StageInputOutputDescriptor ComputePipelineDescriptor::GetStageInputDescriptor() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return ns::Handle { (__bridge void*)[(__bridge MTLComputePipelineDescriptor*)m_ptr stageInputDescriptor] };
#else
        return ns::Handle { nullptr };
#endif
    }

    void ComputePipelineDescriptor::SetLabel(const ns::String& label)
    {
        Validate();
        [(__bridge MTLComputePipelineDescriptor*)m_ptr setLabel:(__bridge NSString*)label.GetPtr()];
    }

    void ComputePipelineDescriptor::SetComputeFunction(const Function& function)
    {
        Validate();
        [(__bridge MTLComputePipelineDescriptor*)m_ptr setComputeFunction:(__bridge id<MTLFunction>)function.GetPtr()];
    }

    void ComputePipelineDescriptor::SetThreadGroupSizeIsMultipleOfThreadExecutionWidth(bool value)
    {
        Validate();
        [(__bridge MTLComputePipelineDescriptor*)m_ptr setThreadGroupSizeIsMultipleOfThreadExecutionWidth:value];
    }

    void ComputePipelineDescriptor::SetStageInputDescriptor(const StageInputOutputDescriptor& stageInputDescriptor) const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        [(__bridge MTLComputePipelineDescriptor*)m_ptr setStageInputDescriptor:(__bridge MTLStageInputOutputDescriptor*)stageInputDescriptor.GetPtr()];
#endif
    }

    Device ComputePipelineState::GetDevice() const
    {
        Validate();
        return ns::Handle { (__bridge void*)[(__bridge id<MTLComputePipelineState>)m_ptr device] };
    }

    uint32_t ComputePipelineState::GetMaxTotalThreadsPerThreadgroup() const
    {
        Validate();
        return uint32_t([(__bridge id<MTLComputePipelineState>)m_ptr maxTotalThreadsPerThreadgroup]);
    }

    uint32_t ComputePipelineState::GetThreadExecutionWidth() const
    {
        Validate();
        return uint32_t([(__bridge id<MTLComputePipelineState>)m_ptr threadExecutionWidth]);
    }
}

//////////////////////////////////////
// FILE: depth_stencil.mm
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #include "depth_stencil.hpp"
#include <Metal/MTLDepthStencil.h>

namespace mtlpp
{
    StencilDescriptor::StencilDescriptor() :
        ns::Object(ns::Handle{ (__bridge void*)[[MTLStencilDescriptor alloc] init] })
    {
    }

    CompareFunction StencilDescriptor::GetStencilCompareFunction() const
    {
        Validate();
        return CompareFunction([(__bridge MTLStencilDescriptor*)m_ptr stencilCompareFunction]);
    }

    StencilOperation StencilDescriptor::GetStencilFailureOperation() const
    {
        Validate();
        return StencilOperation([(__bridge MTLStencilDescriptor*)m_ptr stencilFailureOperation]);
    }

    StencilOperation StencilDescriptor::GetDepthFailureOperation() const
    {
        Validate();
        return StencilOperation([(__bridge MTLStencilDescriptor*)m_ptr depthFailureOperation]);
    }

    StencilOperation StencilDescriptor::GetDepthStencilPassOperation() const
    {
        Validate();
        return StencilOperation([(__bridge MTLStencilDescriptor*)m_ptr depthStencilPassOperation]);
    }

    uint32_t StencilDescriptor::GetReadMask() const
    {
        Validate();
        return uint32_t([(__bridge MTLStencilDescriptor*)m_ptr readMask]);
    }

    uint32_t StencilDescriptor::GetWriteMask() const
    {
        Validate();
        return uint32_t([(__bridge MTLStencilDescriptor*)m_ptr writeMask]);
    }

    void StencilDescriptor::SetStencilCompareFunction(CompareFunction stencilCompareFunction)
    {
        Validate();
        [(__bridge MTLStencilDescriptor*)m_ptr setStencilCompareFunction:MTLCompareFunction(stencilCompareFunction)];
    }

    void StencilDescriptor::SetStencilFailureOperation(StencilOperation stencilFailureOperation)
    {
        Validate();
        [(__bridge MTLStencilDescriptor*)m_ptr setStencilFailureOperation:MTLStencilOperation(stencilFailureOperation)];
    }

    void StencilDescriptor::SetDepthFailureOperation(StencilOperation depthFailureOperation)
    {
        Validate();
        [(__bridge MTLStencilDescriptor*)m_ptr setDepthFailureOperation:MTLStencilOperation(depthFailureOperation)];
    }

    void StencilDescriptor::SetDepthStencilPassOperation(StencilOperation depthStencilPassOperation)
    {
        Validate();
        [(__bridge MTLStencilDescriptor*)m_ptr setDepthStencilPassOperation:MTLStencilOperation(depthStencilPassOperation)];
    }

    void StencilDescriptor::SetReadMask(uint32_t readMask)
    {
        Validate();
        [(__bridge MTLStencilDescriptor*)m_ptr setReadMask:readMask];
    }

    void StencilDescriptor::SetWriteMask(uint32_t writeMask)
    {
        Validate();
        [(__bridge MTLStencilDescriptor*)m_ptr setWriteMask:writeMask];
    }

    DepthStencilDescriptor::DepthStencilDescriptor() :
        ns::Object(ns::Handle{ (__bridge void*)[[MTLDepthStencilDescriptor alloc] init] })
    {
    }

    CompareFunction DepthStencilDescriptor::GetDepthCompareFunction() const
    {
        Validate();
        return CompareFunction([(__bridge MTLDepthStencilDescriptor*)m_ptr depthCompareFunction]);
    }

    bool DepthStencilDescriptor::IsDepthWriteEnabled() const
    {
        Validate();
        return [(__bridge MTLDepthStencilDescriptor*)m_ptr isDepthWriteEnabled];
    }

    StencilDescriptor DepthStencilDescriptor::GetFrontFaceStencil() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge MTLDepthStencilDescriptor*)m_ptr frontFaceStencil] };
    }

    StencilDescriptor DepthStencilDescriptor::GetBackFaceStencil() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge MTLDepthStencilDescriptor*)m_ptr backFaceStencil] };
    }

    ns::String DepthStencilDescriptor::GetLabel() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge MTLDepthStencilDescriptor*)m_ptr label] };
    }

    void DepthStencilDescriptor::SetDepthCompareFunction(CompareFunction depthCompareFunction) const
    {
        Validate();
        [(__bridge MTLDepthStencilDescriptor*)m_ptr setDepthCompareFunction:MTLCompareFunction(depthCompareFunction)];
    }

    void DepthStencilDescriptor::SetDepthWriteEnabled(bool depthWriteEnabled) const
    {
        Validate();
        [(__bridge MTLDepthStencilDescriptor*)m_ptr setDepthWriteEnabled:depthWriteEnabled];
    }

    void DepthStencilDescriptor::SetFrontFaceStencil(const StencilDescriptor& frontFaceStencil) const
    {
        Validate();
        [(__bridge MTLDepthStencilDescriptor*)m_ptr setFrontFaceStencil:(__bridge MTLStencilDescriptor*)frontFaceStencil.GetPtr()];
    }

    void DepthStencilDescriptor::SetBackFaceStencil(const StencilDescriptor& backFaceStencil) const
    {
        Validate();
        [(__bridge MTLDepthStencilDescriptor*)m_ptr setBackFaceStencil:(__bridge MTLStencilDescriptor*)backFaceStencil.GetPtr()];
    }

    void DepthStencilDescriptor::SetLabel(const ns::String& label) const
    {
        Validate();
        [(__bridge MTLDepthStencilDescriptor*)m_ptr setLabel:(__bridge NSString*)label.GetPtr()];
    }

    ns::String DepthStencilState::GetLabel() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLDepthStencilState>)m_ptr label] };
    }

    Device DepthStencilState::GetDevice() const
    {
        Validate();
        return ns::Handle { (__bridge void*)[(__bridge id<MTLDepthStencilState>)m_ptr device] };
    }
}

//////////////////////////////////////
// FILE: device.mm
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #include "device.hpp"
// #include "buffer.hpp"
// #include "command_queue.hpp"
// #include "compute_pipeline.hpp"
// #include "depth_stencil.hpp"
// #include "render_pipeline.hpp"
// #include "sampler.hpp"
// #include "texture.hpp"
// #include "heap.hpp"
#include <Metal/MTLDevice.h>

namespace mtlpp
{
    CompileOptions::CompileOptions() :
        ns::Object(ns::Handle{ (__bridge void*)[[MTLCompileOptions alloc] init] })
    {
    }

    Device Device::CreateSystemDefaultDevice()
    {
        return ns::Handle{ (__bridge void*)MTLCreateSystemDefaultDevice() };
    }

    ns::Array<Device> Device::CopyAllDevices()
    {
#if MTLPP_IS_AVAILABLE_MAC(10_11)
        return ns::Handle{ (__bridge void*)MTLCopyAllDevices() };
#else
        return ns::Handle{ nullptr };
#endif
    }

    ns::String Device::GetName() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLDevice>)m_ptr name] };
    }

    Size Device::GetMaxThreadsPerThreadgroup() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_11, 9_0)
        MTLSize mtlSize = [(__bridge id<MTLDevice>)m_ptr maxThreadsPerThreadgroup];
        return Size(uint32_t(mtlSize.width), uint32_t(mtlSize.height), uint32_t(mtlSize.depth));
#else
        return Size(0, 0, 0);
#endif
    }

    bool Device::IsLowPower() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE_MAC(10_11)
        return [(__bridge id<MTLDevice>)m_ptr isLowPower];
#else
        return false;
#endif
    }

    bool Device::IsHeadless() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE_MAC(10_11)
        return [(__bridge id<MTLDevice>)m_ptr isHeadless];
#else
        return false;
#endif
    }

    uint64_t Device::GetRecommendedMaxWorkingSetSize() const
    {
#if MTLPP_IS_AVAILABLE_MAC(10_12)
        return [(__bridge id<MTLDevice>)m_ptr recommendedMaxWorkingSetSize];
#else
        return 0;
#endif
    }

    bool Device::IsDepth24Stencil8PixelFormatSupported() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE_MAC(10_11)
        return [(__bridge id<MTLDevice>)m_ptr isDepth24Stencil8PixelFormatSupported];
#else
        return true;
#endif
    }

    CommandQueue Device::NewCommandQueue()
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLDevice>)m_ptr newCommandQueue] };
    }

    CommandQueue Device::NewCommandQueue(uint32_t maxCommandBufferCount)
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLDevice>)m_ptr newCommandQueueWithMaxCommandBufferCount:maxCommandBufferCount] };
    }

    SizeAndAlign Device::HeapTextureSizeAndAlign(const TextureDescriptor& desc)
    {
#if MTLPP_IS_AVAILABLE_IOS(10_0)
        MTLSizeAndAlign mtlSizeAndAlign = [(__bridge id<MTLDevice>)m_ptr heapTextureSizeAndAlignWithDescriptor:(__bridge MTLTextureDescriptor*)desc.GetPtr()];
        return SizeAndAlign{ uint32_t(mtlSizeAndAlign.size), uint32_t(mtlSizeAndAlign.align) };
#else
        return SizeAndAlign{0, 0};
#endif
    }

    SizeAndAlign Device::HeapBufferSizeAndAlign(uint32_t length, ResourceOptions options)
    {
#if MTLPP_IS_AVAILABLE_IOS(10_0)
        MTLSizeAndAlign mtlSizeAndAlign = [(__bridge id<MTLDevice>)m_ptr heapBufferSizeAndAlignWithLength:length options:MTLResourceOptions(options)];
        return SizeAndAlign{ uint32_t(mtlSizeAndAlign.size), uint32_t(mtlSizeAndAlign.align) };
#else
        return SizeAndAlign{0, 0};
#endif
    }

    Heap Device::NewHeap(const HeapDescriptor& descriptor)
    {
#if MTLPP_IS_AVAILABLE_IOS(10_0)
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLDevice>)m_ptr newHeapWithDescriptor:(__bridge MTLHeapDescriptor*)descriptor.GetPtr()] };
#else
        return ns::Handle{ nullptr };
#endif
    }

    Buffer Device::NewBuffer(uint32_t length, ResourceOptions options)
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLDevice>)m_ptr newBufferWithLength:length options:MTLResourceOptions(options)] };
    }

    Buffer Device::NewBuffer(const void* pointer, uint32_t length, ResourceOptions options)
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLDevice>)m_ptr newBufferWithBytes:pointer length:length options:MTLResourceOptions(options)] };
    }


    Buffer Device::NewBuffer(void* pointer, uint32_t length, ResourceOptions options, std::function<void (void* pointer, uint32_t length)> deallocator)
    {
        Validate();
        return ns::Handle{
            (__bridge void*)[(__bridge id<MTLDevice>)m_ptr newBufferWithBytesNoCopy:pointer
                                                                             length:length
                                                                            options:MTLResourceOptions(options)
                                                                        deallocator:^(void* pointer, NSUInteger length) { deallocator(pointer, uint32_t(length)); }]
        };
    }

    DepthStencilState Device::NewDepthStencilState(const DepthStencilDescriptor& descriptor)
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLDevice>)m_ptr newDepthStencilStateWithDescriptor:(__bridge MTLDepthStencilDescriptor*)descriptor.GetPtr()] };
    }

    Texture Device::NewTexture(const TextureDescriptor& descriptor)
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLDevice>)m_ptr newTextureWithDescriptor:(__bridge MTLTextureDescriptor*)descriptor.GetPtr()] };
    }

    //- (id <MTLTexture>)newTextureWithDescriptor:(MTLTextureDescriptor *)descriptor iosurface:(IOSurfaceRef)iosurface plane:(NSUInteger)plane NS_AVAILABLE_MAC(10_11);
    SamplerState Device::NewSamplerState(const SamplerDescriptor& descriptor)
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLDevice>)m_ptr newSamplerStateWithDescriptor:(__bridge MTLSamplerDescriptor*)descriptor.GetPtr()] };
    }

    Library Device::NewDefaultLibrary()
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLDevice>)m_ptr newDefaultLibrary] };
    }

    Library Device::NewLibrary(const ns::String& filepath, ns::Error* error)
    {
        Validate();
        NSError* nsError = error ? (__bridge NSError*)error->GetPtr() : nullptr;
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLDevice>)m_ptr newLibraryWithFile:(__bridge NSString*)filepath.GetPtr() error:&nsError] };
    }

    Library Device::NewLibrary(const char* source, const CompileOptions& options, ns::Error* error)
    {
        Validate();
        NSString* nsSource = [NSString stringWithUTF8String:source];
        NSError* nsError = error ? (__bridge NSError*)error->GetPtr() : nullptr;
        return ns::Handle{
            (__bridge void*)[(__bridge id<MTLDevice>)m_ptr newLibraryWithSource:nsSource
                                                                        options:(__bridge MTLCompileOptions*)options.GetPtr()
                                                                          error:&nsError]
        };
    }

    void Device::NewLibrary(const char* source, const CompileOptions& options, std::function<void(const Library&, const ns::Error&)> completionHandler)
    {
        Validate();
        NSString* nsSource = [NSString stringWithUTF8String:source];
        [(__bridge id<MTLDevice>)m_ptr newLibraryWithSource:nsSource
                                                    options:(__bridge MTLCompileOptions*)options.GetPtr()
                                          completionHandler:^(id <MTLLibrary> library, NSError * error) {
                                                completionHandler(
                                                    ns::Handle{ (__bridge void*)library },
                                                    ns::Handle{ (__bridge void*)error });
                                          }];
    }

    RenderPipelineState Device::NewRenderPipelineState(const RenderPipelineDescriptor& descriptor, ns::Error* error)
    {
        Validate();
        NSError* nsError = error ? (__bridge NSError*)error->GetPtr() : nullptr;
        return ns::Handle{
            (__bridge void*)[(__bridge id<MTLDevice>)m_ptr newRenderPipelineStateWithDescriptor:(__bridge MTLRenderPipelineDescriptor*)descriptor.GetPtr()
                                                                                          error:&nsError]
        };
    }

    RenderPipelineState Device::NewRenderPipelineState(const RenderPipelineDescriptor& descriptor, PipelineOption options, RenderPipelineReflection* outReflection, ns::Error* error)
    {
        Validate();
        NSError* nsError = error ? (__bridge NSError*)error->GetPtr() : nullptr;
        MTLRenderPipelineReflection* mtlReflection = outReflection ? (__bridge MTLRenderPipelineReflection*)outReflection->GetPtr() : nullptr;
        return ns::Handle{
            (__bridge void*)[(__bridge id<MTLDevice>)m_ptr newRenderPipelineStateWithDescriptor:(__bridge MTLRenderPipelineDescriptor*)descriptor.GetPtr()
                                                                                        options:MTLPipelineOption(options)
                                                                                     reflection:&mtlReflection
                                                                                          error:&nsError]
        };
    }

    void Device::NewRenderPipelineState(const RenderPipelineDescriptor& descriptor, std::function<void(const RenderPipelineState&, const ns::Error&)> completionHandler)
    {
        Validate();
        [(__bridge id<MTLDevice>)m_ptr newRenderPipelineStateWithDescriptor:(__bridge MTLRenderPipelineDescriptor*)descriptor.GetPtr()
                                                          completionHandler:^(id <MTLRenderPipelineState> renderPipelineState, NSError * error) {
                                                              completionHandler(
                                                                  ns::Handle{ (__bridge void*)renderPipelineState },
                                                                  ns::Handle{ (__bridge void*)error }
                                                              );
                                                          }];
    }

    void Device::NewRenderPipelineState(const RenderPipelineDescriptor& descriptor, PipelineOption options, std::function<void(const RenderPipelineState&, const RenderPipelineReflection&, const ns::Error&)> completionHandler)
    {
        Validate();
        [(__bridge id<MTLDevice>)m_ptr newRenderPipelineStateWithDescriptor:(__bridge MTLRenderPipelineDescriptor*)descriptor.GetPtr()
                                                                    options:MTLPipelineOption(options)
                                                          completionHandler:^(id <MTLRenderPipelineState> renderPipelineState, MTLRenderPipelineReflection * reflection, NSError * error) {
                                                              completionHandler(
                                                                  ns::Handle{ (__bridge void*)renderPipelineState },
                                                                  ns::Handle{ (__bridge void*)reflection },
                                                                  ns::Handle{ (__bridge void*)error }
                                                              );
                                                          }];
    }

    ComputePipelineState Device::NewComputePipelineState(const Function& computeFunction, ns::Error* error)
    {
        Validate();
        NSError* nsError = error ? (__bridge NSError*)error->GetPtr() : nullptr;
        return ns::Handle{
            (__bridge void*)[(__bridge id<MTLDevice>)m_ptr newComputePipelineStateWithFunction:(__bridge id<MTLFunction>)computeFunction.GetPtr()
                                                                                         error:&nsError]
        };
    }

    ComputePipelineState Device::NewComputePipelineState(const Function& computeFunction, PipelineOption options, ComputePipelineReflection& outReflection, ns::Error* error)
    {
        Validate();
        return ns::Handle{ nullptr };
    }

    void Device::NewComputePipelineState(const Function& computeFunction, std::function<void(const ComputePipelineState&, const ns::Error&)> completionHandler)
    {
        Validate();
        [(__bridge id<MTLDevice>)m_ptr newComputePipelineStateWithFunction:(__bridge id<MTLFunction>)computeFunction.GetPtr()
                                                         completionHandler:^(id <MTLComputePipelineState> computePipelineState, NSError * error) {
                                                             completionHandler(
                                                                 ns::Handle{ (__bridge void*)computePipelineState },
                                                                 ns::Handle{ (__bridge void*)error }
                                                             );
                                                         }];
    }

    void Device::NewComputePipelineState(const Function& computeFunction, PipelineOption options, std::function<void(const ComputePipelineState&, const ComputePipelineReflection&, const ns::Error&)> completionHandler)
    {
        Validate();
        [(__bridge id<MTLDevice>)m_ptr newComputePipelineStateWithFunction:(__bridge id<MTLFunction>)computeFunction.GetPtr()
                                                                   options:MTLPipelineOption(options)
                                                         completionHandler:^(id <MTLComputePipelineState> computePipelineState, MTLComputePipelineReflection * reflection, NSError * error) {
                                                             completionHandler(
                                                                 ns::Handle{ (__bridge void*)computePipelineState },
                                                                 ns::Handle{ (__bridge void*)reflection },
                                                                 ns::Handle{ (__bridge void*)error }
                                                             );
                                                         }];
    }

    ComputePipelineState Device::NewComputePipelineState(const ComputePipelineDescriptor& descriptor, PipelineOption options, ComputePipelineReflection* outReflection, ns::Error* error)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_11, 9_0)
        NSError* nsError = error ? (__bridge NSError*)error->GetPtr() : nullptr;
        MTLComputePipelineReflection* mtlReflection = outReflection ? (__bridge MTLComputePipelineReflection*)outReflection->GetPtr() : nullptr;
        return ns::Handle{
            (__bridge void*)[(__bridge id<MTLDevice>)m_ptr newComputePipelineStateWithDescriptor:(__bridge MTLComputePipelineDescriptor*)descriptor.GetPtr()
                                                                                         options:MTLPipelineOption(options)
                                                                                      reflection:&mtlReflection
                                                                                           error:&nsError] };
#else
        return ns::Handle{ nullptr };
#endif
    }

    void Device::NewComputePipelineState(const ComputePipelineDescriptor& descriptor, PipelineOption options, std::function<void(const ComputePipelineState&, const ComputePipelineReflection&, const ns::Error&)> completionHandler)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_11, 9_0)
        [(__bridge id<MTLDevice>)m_ptr newComputePipelineStateWithDescriptor:(__bridge MTLComputePipelineDescriptor*)descriptor.GetPtr()
                                                                     options:MTLPipelineOption(options)
                                                         completionHandler:^(id <MTLComputePipelineState> computePipelineState, MTLComputePipelineReflection * reflection, NSError * error)
                                                                    {
                                                                        completionHandler(
                                                                            ns::Handle{ (__bridge void*)computePipelineState },
                                                                            ns::Handle{ (__bridge void*)reflection },
                                                                            ns::Handle{ (__bridge void*)error });
                                                                    }];
#endif
    }

    Fence Device::NewFence()
    {
        Validate();
#if MTLPP_IS_AVAILABLE_IOS(10_0)
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLDevice>)m_ptr newFence] };
#else
        return ns::Handle{ nullptr };
#endif
    }

    bool Device::SupportsFeatureSet(FeatureSet featureSet) const
    {
        Validate();
        return [(__bridge id<MTLDevice>)m_ptr supportsFeatureSet:MTLFeatureSet(featureSet)];
    }

    bool Device::SupportsTextureSampleCount(uint32_t sampleCount) const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_11, 9_0)
        return [(__bridge id<MTLDevice>)m_ptr supportsTextureSampleCount:sampleCount];
#else
        return true;
#endif
    }
}

//////////////////////////////////////
// FILE: drawable.mm
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #include "drawable.hpp"
#include <Metal/MTLDrawable.h>

namespace mtlpp
{
    void Drawable::Present()
    {
        Validate();
        [(__bridge id<MTLDrawable>)m_ptr present];
    }

    void Drawable::Present(double presentationTime)
    {
        Validate();
        [(__bridge id<MTLDrawable>)m_ptr presentAtTime:presentationTime];
    }
}

//////////////////////////////////////
// FILE: fence.mm
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #include "fence.hpp"
#if MTLPP_IS_AVAILABLE_IOS(10_0)
#   include <Metal/MTLFence.h>
#endif

namespace mtlpp
{
    Texture Fence::GetDevice() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE_IOS(10_0)
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLFence>)m_ptr device] };
#else
        return ns::Handle{ nullptr };
#endif
    }

    ns::String Fence::GetLabel() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE_IOS(10_0)
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLFence>)m_ptr label] };
#else
        return ns::Handle{ nullptr };
#endif
    }

    void Fence::SetLabel(const ns::String& label)
    {
        Validate();
#if MTLPP_IS_AVAILABLE_IOS(10_0)
        [(__bridge id<MTLFence>)m_ptr setLabel:(__bridge NSString*)label.GetPtr()];
#endif
    }
}

//////////////////////////////////////
// FILE: function_constant_values.mm
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #include "function_constant_values.hpp"
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
#   include <Metal/MTLFunctionConstantValues.h>
#endif

namespace mtlpp
{
    FunctionConstantValues::FunctionConstantValues() :
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        ns::Object(ns::Handle{ (__bridge void*)[[MTLFunctionConstantValues alloc] init] })
#else
        ns::Object(ns::Handle{ nullptr })
#endif
    {
    }

    void FunctionConstantValues::SetConstantValue(const void* value, DataType type, uint32_t index)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        [(__bridge MTLFunctionConstantValues*)m_ptr setConstantValue:value type:MTLDataType(type) atIndex:index];
#endif
    }

    void FunctionConstantValues::SetConstantValue(const void* value, DataType type, const ns::String& name)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        [(__bridge MTLFunctionConstantValues*)m_ptr setConstantValue:value type:MTLDataType(type) withName:(__bridge NSString*)name.GetPtr()];
#endif
    }

    void FunctionConstantValues::SetConstantValues(const void* value, DataType type, const ns::Range& range)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        [(__bridge MTLFunctionConstantValues*)m_ptr setConstantValues:value type:MTLDataType(type) withRange:NSMakeRange(range.Location, range.Length)];
#endif
    }

    void FunctionConstantValues::Reset()
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return [(__bridge MTLFunctionConstantValues*)m_ptr reset];
#endif
    }
}

//////////////////////////////////////
// FILE: heap.mm
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #include "heap.hpp"
#if MTLPP_IS_AVAILABLE_IOS(10_0)
#   include <Metal/MTLHeap.h>
#endif

namespace mtlpp
{
    uint32_t HeapDescriptor::GetSize() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE_IOS(10_0)
        return uint32_t([(__bridge MTLHeapDescriptor*)m_ptr size]);
#else
        return 0;
#endif

    }

    StorageMode HeapDescriptor::GetStorageMode() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE_IOS(10_0)
        return StorageMode([(__bridge MTLHeapDescriptor*)m_ptr storageMode]);
#else
        return StorageMode(0);
#endif

    }

    CpuCacheMode HeapDescriptor::GetCpuCacheMode() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE_IOS(10_0)
        return CpuCacheMode([(__bridge MTLHeapDescriptor*)m_ptr cpuCacheMode]);
#else
        return CpuCacheMode(0);
#endif

    }

    void HeapDescriptor::SetSize(uint32_t size) const
    {
        Validate();
#if MTLPP_IS_AVAILABLE_IOS(10_0)
        [(__bridge MTLHeapDescriptor*)m_ptr setSize:size];
#endif

    }

    void HeapDescriptor::SetStorageMode(StorageMode storageMode) const
    {
        Validate();
#if MTLPP_IS_AVAILABLE_IOS(10_0)
        [(__bridge MTLHeapDescriptor*)m_ptr setStorageMode:MTLStorageMode(storageMode)];
#endif

    }

    void HeapDescriptor::SetCpuCacheMode(CpuCacheMode cpuCacheMode) const
    {
        Validate();
#if MTLPP_IS_AVAILABLE_IOS(10_0)
        [(__bridge MTLHeapDescriptor*)m_ptr setCpuCacheMode:MTLCPUCacheMode(cpuCacheMode)];
#endif

    }

    ns::String Heap::GetLabel() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE_IOS(10_0)
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLHeap>)m_ptr label] };
#else
        return ns::Handle{ nullptr };
#endif

    }

    Device Heap::GetDevice() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE_IOS(10_0)
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLHeap>)m_ptr device] };
#else
        return ns::Handle{ nullptr };
#endif

    }

    StorageMode Heap::GetStorageMode() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE_IOS(10_0)
        return StorageMode([(__bridge id<MTLHeap>)m_ptr storageMode]);
#else
        return StorageMode(0);
#endif

    }

    CpuCacheMode Heap::GetCpuCacheMode() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE_IOS(10_0)
        return CpuCacheMode([(__bridge id<MTLHeap>)m_ptr cpuCacheMode]);
#else
        return CpuCacheMode(0);
#endif

    }

    uint32_t Heap::GetSize() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE_IOS(10_0)
        return uint32_t([(__bridge id<MTLHeap>)m_ptr size]);
#else
        return 0;
#endif

    }

    uint32_t Heap::GetUsedSize() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE_IOS(10_0)
        return uint32_t([(__bridge id<MTLHeap>)m_ptr usedSize]);
#else
        return 0;
#endif

    }

    void Heap::SetLabel(const ns::String& label)
    {
        Validate();
#if MTLPP_IS_AVAILABLE_IOS(10_0)
        [(__bridge id<MTLHeap>)m_ptr setLabel:(__bridge NSString*)label.GetPtr()];
#endif

    }

    uint32_t Heap::MaxAvailableSizeWithAlignment(uint32_t alignment)
    {
        Validate();
#if MTLPP_IS_AVAILABLE_IOS(10_0)
        return uint32_t([(__bridge id<MTLHeap>)m_ptr maxAvailableSizeWithAlignment:alignment]);
#else
        return 0;
#endif

    }

    Buffer Heap::NewBuffer(uint32_t length, ResourceOptions options)
    {
        Validate();
#if MTLPP_IS_AVAILABLE_IOS(10_0)
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLHeap>)m_ptr newBufferWithLength:length options:MTLResourceOptions(options)] };
#else
        return ns::Handle{ nullptr };
#endif

    }

    Texture Heap::NewTexture(const TextureDescriptor& desc)
    {
        Validate();
#if MTLPP_IS_AVAILABLE_IOS(10_0)
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLHeap>)m_ptr newTextureWithDescriptor:(__bridge MTLTextureDescriptor*)desc.GetPtr()] };
#else
        return ns::Handle{ nullptr };
#endif

    }

    PurgeableState Heap::SetPurgeableState(PurgeableState state)
    {
        Validate();
#if MTLPP_IS_AVAILABLE_IOS(10_0)
        return PurgeableState([(__bridge id<MTLHeap>)m_ptr setPurgeableState:MTLPurgeableState(state)]);
#else
        return PurgeableState(0);
#endif

    }
}

//////////////////////////////////////
// FILE: library.mm
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #include "library.hpp"
// #include "device.hpp"
// #include "function_constant_values.hpp"
#include <Metal/MTLLibrary.h>

namespace mtlpp
{
    VertexAttribute::VertexAttribute() :
        ns::Object(ns::Handle{ (__bridge void*)[[MTLVertexAttribute alloc] init] })
    {
    }

    ns::String VertexAttribute::GetName() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge MTLVertexAttribute*)m_ptr name] };
    }

    uint32_t VertexAttribute::GetAttributeIndex() const
    {
        Validate();
        return uint32_t([(__bridge MTLVertexAttribute*)m_ptr attributeIndex]);
    }

    DataType VertexAttribute::GetAttributeType() const
    {
        Validate();
        return DataType([(__bridge MTLVertexAttribute*)m_ptr attributeType]);
    }

    bool VertexAttribute::IsActive() const
    {
        Validate();
        return [(__bridge MTLVertexAttribute*)m_ptr isActive];
    }

    bool VertexAttribute::IsPatchData() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return [(__bridge MTLVertexAttribute*)m_ptr isActive];
#else
        return false;
#endif
    }

    bool VertexAttribute::IsPatchControlPointData() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return [(__bridge MTLVertexAttribute*)m_ptr isActive];
#else
        return false;
#endif
    }

    Attribute::Attribute() :
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        ns::Object(ns::Handle{ (__bridge void*)[[MTLAttribute alloc] init] })
#else
        ns::Object(ns::Handle{ nullptr })
#endif
    {
    }

    ns::String Attribute::GetName() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return ns::Handle{ (__bridge void*)[(__bridge MTLAttribute*)m_ptr name] };
#else
        return ns::Handle{ nullptr };
#endif
    }

    uint32_t Attribute::GetAttributeIndex() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return uint32_t([(__bridge MTLAttribute*)m_ptr attributeIndex]);
#else
        return 0;
#endif
    }

    DataType Attribute::GetAttributeType() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return DataType([(__bridge MTLAttribute*)m_ptr attributeType]);
#else
        return DataType(0);
#endif
    }

    bool Attribute::IsActive() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return [(__bridge MTLAttribute*)m_ptr isActive];
#else
        return false;
#endif
    }

    bool Attribute::IsPatchData() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return [(__bridge MTLAttribute*)m_ptr isActive];
#else
        return false;
#endif
    }

    bool Attribute::IsPatchControlPointData() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return [(__bridge MTLAttribute*)m_ptr isActive];
#else
        return false;
#endif
    }

    FunctionConstant::FunctionConstant() :
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        ns::Object(ns::Handle{ (__bridge void*)[[MTLFunctionConstant alloc] init] })
#else
        ns::Object(ns::Handle{ nullptr })
#endif
    {
    }

    ns::String FunctionConstant::GetName() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return ns::Handle{ (__bridge void*)[(__bridge MTLFunctionConstant*)m_ptr name] };
#else
        return ns::Handle{ nullptr };
#endif
    }

    DataType FunctionConstant::GetType() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return DataType([(__bridge MTLFunctionConstant*)m_ptr type]);
#else
        return DataType(0);
#endif
    }

    uint32_t FunctionConstant::GetIndex() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return uint32_t([(__bridge MTLFunctionConstant*)m_ptr index]);
#else
        return 0;
#endif
    }

    bool FunctionConstant::IsRequired() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return [(__bridge MTLFunctionConstant*)m_ptr required];
#else
        return false;
#endif
    }

    ns::String Function::GetLabel() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLFunction>)m_ptr label] };
#else
        return ns::Handle{ nullptr };
#endif
    }

    Device Function::GetDevice() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLFunction>)m_ptr device] };
    }

    FunctionType Function::GetFunctionType() const
    {
        Validate();
        return FunctionType([(__bridge id<MTLFunction>)m_ptr functionType]);
    }

    PatchType Function::GetPatchType() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return PatchType([(__bridge id<MTLFunction>)m_ptr patchType]);
#else
        return PatchType(0);
#endif
    }

    int32_t Function::GetPatchControlPointCount() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return int32_t([(__bridge id<MTLFunction>)m_ptr patchControlPointCount]);
#else
        return 0;
#endif
    }

    const ns::Array<VertexAttribute> Function::GetVertexAttributes() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLFunction>)m_ptr vertexAttributes] };
    }

    const ns::Array<Attribute> Function::GetStageInputAttributes() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLFunction>)m_ptr stageInputAttributes] };
#else
        return ns::Handle{ nullptr };
#endif
    }

    ns::String Function::GetName() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLFunction>)m_ptr name] };
    }

    ns::Dictionary<ns::String, FunctionConstant> Function::GetFunctionConstants() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLFunction>)m_ptr functionConstantsDictionary] };
#else
        return ns::Handle{ nullptr };
#endif
    }

    void Function::SetLabel(const ns::String& label)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        [(__bridge id<MTLFunction>)m_ptr setLabel:(__bridge NSString*)label.GetPtr()];
#endif
    }

    ns::Dictionary<ns::String, ns::String> CompileOptions::GetPreprocessorMacros() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge MTLCompileOptions*)m_ptr preprocessorMacros] };
    }

    bool CompileOptions::IsFastMathEnabled() const
    {
        Validate();
        return [(__bridge MTLCompileOptions*)m_ptr fastMathEnabled];
    }

    LanguageVersion CompileOptions::GetLanguageVersion() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_11, 9_0)
        return LanguageVersion([(__bridge MTLCompileOptions*)m_ptr languageVersion]);
#else
        return LanguageVersion::Version1_0;
#endif
    }

    void CompileOptions::SetFastMathEnabled(bool fastMathEnabled)
    {
        Validate();
        [(__bridge MTLCompileOptions*)m_ptr setFastMathEnabled:fastMathEnabled];
    }

    void CompileOptions::SetFastMathEnabled(LanguageVersion languageVersion)
    {
        Validate();
        [(__bridge MTLCompileOptions*)m_ptr setFastMathEnabled:MTLLanguageVersion(languageVersion)];
    }

    ns::String Library::GetLabel() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLLibrary>)m_ptr label] };
    }

    void Library::SetLabel(const ns::String& label)
    {
        Validate();
        [(__bridge id<MTLLibrary>)m_ptr setLabel:(__bridge NSString*)label.GetPtr()];
    }

    ns::Array<ns::String> Library::GetFunctionNames() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLLibrary>)m_ptr functionNames] };
    }

    Function Library::NewFunction(const ns::String& functionName)
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLLibrary>)m_ptr newFunctionWithName:(__bridge NSString*)functionName.GetPtr()] };
    }

    Function Library::NewFunction(const ns::String& functionName, const FunctionConstantValues& constantValues, ns::Error* error)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        NSError* nsError = error ? (__bridge NSError*)error->GetPtr() : nullptr;
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLLibrary>)m_ptr
                                            newFunctionWithName:(__bridge NSString*)functionName.GetPtr()
                                            constantValues:(__bridge MTLFunctionConstantValues*)constantValues.GetPtr()
                                            error:&nsError] };
#else
        return ns::Handle{ nullptr };
#endif
    }

    void Library::NewFunction(const ns::String& functionName, const FunctionConstantValues& constantValues, std::function<void(const Function&, const ns::Error&)> completionHandler)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        [(__bridge id<MTLLibrary>)m_ptr
             newFunctionWithName:(__bridge NSString*)functionName.GetPtr()
             constantValues:(__bridge MTLFunctionConstantValues*)constantValues.GetPtr()
             completionHandler:^(id <MTLFunction> mtlFunction, NSError* error){
                 completionHandler(ns::Handle{ (__bridge void*)mtlFunction }, ns::Handle{ (__bridge void*)error });
             }];
#endif
    }

}

//////////////////////////////////////
// FILE: ns.mm
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #include "ns.hpp"
#include <CoreFoundation/CFBase.h>
#include <Foundation/NSString.h>
#include <Foundation/NSError.h>
#include <Foundation/NSArray.h>
#include <cstring>

namespace ns
{
    Object::Object() :
        m_ptr(nullptr)
    {
    }

    Object::Object(const Handle& handle) :
        m_ptr(handle.ptr)
    {
        if (m_ptr)
            CFRetain(m_ptr);
    }

    Object::Object(const Object& rhs) :
        m_ptr(rhs.m_ptr)
    {
        if (m_ptr)
            CFRetain(m_ptr);
    }

#if MTLPP_CONFIG_RVALUE_REFERENCES
    Object::Object(Object&& rhs) :
        m_ptr(rhs.m_ptr)
    {
        rhs.m_ptr = nullptr;
    }
#endif

    Object::~Object()
    {
        if (m_ptr)
            CFRelease(m_ptr);
    }

    Object& Object::operator=(const Object& rhs)
    {
        if (rhs.m_ptr == m_ptr)
            return *this;
        if (rhs.m_ptr)
            CFRetain(rhs.m_ptr);
        if (m_ptr)
            CFRelease(m_ptr);
        m_ptr = rhs.m_ptr;
        return *this;
    }

#if MTLPP_CONFIG_RVALUE_REFERENCES
    Object& Object::operator=(Object&& rhs)
    {
        if (rhs.m_ptr == m_ptr)
            return *this;
        if (m_ptr)
            CFRelease(m_ptr);
        m_ptr = rhs.m_ptr;
        rhs.m_ptr = nullptr;
        return *this;
    }
#endif

    const uint32_t ArrayBase::GetSize() const
    {
        Validate();
        return uint32_t([(__bridge NSArray*)m_ptr count]);
    }

    void* ArrayBase::GetItem(uint32_t index) const
    {
        Validate();
        return (__bridge void*)[(__bridge NSArray*)m_ptr objectAtIndexedSubscript:index];
    }

    String::String(const char* cstr) :
        Object(Handle{ (__bridge void*)[NSString stringWithUTF8String:cstr] })
    {
    }

    const char* String::GetCStr() const
    {
        Validate();
        return [(__bridge NSString*)m_ptr cStringUsingEncoding:NSUTF8StringEncoding];
    }

    uint32_t String::GetLength() const
    {
        Validate();
        return uint32_t([(__bridge NSString*)m_ptr length]);
    }

    Error::Error() :
        Object(Handle{ (__bridge void*)[[NSError alloc] init] })
    {

    }

    String Error::GetDomain() const
    {
        Validate();
        return Handle{ (__bridge void*)[(__bridge NSError*)m_ptr domain] };
    }

    uint32_t Error::GetCode() const
    {
        Validate();
        return uint32_t([(__bridge NSError*)m_ptr code]);
    }

    //@property (readonly, copy) NSDictionary *userInfo;

    String Error::GetLocalizedDescription() const
    {
        Validate();
        return Handle{ (__bridge void*)[(__bridge NSError*)m_ptr localizedDescription] };
    }

    String Error::GetLocalizedFailureReason() const
    {
        Validate();
        return Handle{ (__bridge void*)[(__bridge NSError*)m_ptr localizedFailureReason] };
    }

    String Error::GetLocalizedRecoverySuggestion() const
    {
        Validate();
        return Handle{ (__bridge void*)[(__bridge NSError*)m_ptr localizedRecoverySuggestion] };
    }

    String Error::GetLocalizedRecoveryOptions() const
    {
        Validate();
        return Handle{ (__bridge void*)[(__bridge NSError*)m_ptr localizedRecoveryOptions] };
    }

    //@property (nullable, readonly, strong) id recoveryAttempter;

    String Error::GetHelpAnchor() const
    {
        Validate();
        return Handle{ (__bridge void*)[(__bridge NSError*)m_ptr helpAnchor] };
    }
}

//////////////////////////////////////
// FILE: parallel_render_command_encoder.mm
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #include "parallel_render_command_encoder.hpp"
// #include "render_command_encoder.hpp"
#include <Metal/MTLParallelRenderCommandEncoder.h>

namespace mtlpp
{
    RenderCommandEncoder ParallelRenderCommandEncoder::GetRenderCommandEncoder()
    {
        Validate();
        return ns::Handle { (__bridge void*)[(__bridge id<MTLParallelRenderCommandEncoder>)m_ptr renderCommandEncoder] };
    }

    void ParallelRenderCommandEncoder::SetColorStoreAction(StoreAction storeAction, uint32_t colorAttachmentIndex)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        [(__bridge id<MTLParallelRenderCommandEncoder>)m_ptr setColorStoreAction:MTLStoreAction(storeAction) atIndex:colorAttachmentIndex];
#endif
    }

    void ParallelRenderCommandEncoder::SetDepthStoreAction(StoreAction storeAction)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        [(__bridge id<MTLParallelRenderCommandEncoder>)m_ptr setDepthStoreAction:MTLStoreAction(storeAction)];
#endif
    }

    void ParallelRenderCommandEncoder::SetStencilStoreAction(StoreAction storeAction)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        [(__bridge id<MTLParallelRenderCommandEncoder>)m_ptr setStencilStoreAction:MTLStoreAction(storeAction)];
#endif
    }
}

//////////////////////////////////////
// FILE: render_command_encoder.mm
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #include "render_command_encoder.hpp"
// #include "buffer.hpp"
// #include "depth_stencil.hpp"
// #include "render_pipeline.hpp"
// #include "sampler.hpp"
// #include "texture.hpp"
#include <Metal/MTLRenderCommandEncoder.h>
#include <Metal/MTLBuffer.h>

namespace mtlpp
{
    void RenderCommandEncoder::SetRenderPipelineState(const RenderPipelineState& pipelineState)
    {
        Validate();
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setRenderPipelineState:(__bridge id<MTLRenderPipelineState>)pipelineState.GetPtr()];
    }

    void RenderCommandEncoder::SetVertexData(const void* bytes, uint32_t length, uint32_t index)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_11, 8_3)
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setVertexBytes:bytes length:length atIndex:index];
#endif
    }

    void RenderCommandEncoder::SetVertexBuffer(const Buffer& buffer, uint32_t offset, uint32_t index)
    {
        Validate();
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setVertexBuffer:(__bridge id<MTLBuffer>)buffer.GetPtr()
                                                              offset:offset
                                                             atIndex:index];
    }
    void RenderCommandEncoder::SetVertexBufferOffset(uint32_t offset, uint32_t index)
    {
#if MTLPP_IS_AVAILABLE(10_11, 8_3)
        Validate();
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setVertexBufferOffset:offset atIndex:index];
#endif
    }

    void RenderCommandEncoder::SetVertexBuffers(const Buffer* buffers, const uint32_t* offsets, const ns::Range& range)
    {
        Validate();

        const uint32_t maxBuffers = 32;
        assert(range.Length <= maxBuffers);

        id<MTLBuffer> mtlBuffers[maxBuffers];
        NSUInteger    nsOffsets[maxBuffers];
        for (uint32_t i=0; i<range.Length; i++)
        {
            mtlBuffers[i] = (__bridge id<MTLBuffer>)buffers[i].GetPtr();
            nsOffsets[i] = offsets[i];
        }

        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setVertexBuffers:mtlBuffers offsets:nsOffsets withRange:NSMakeRange(range.Location, range.Length)];
    }

    void RenderCommandEncoder::SetVertexTexture(const Texture& texture, uint32_t index)
    {
        Validate();
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setVertexTexture:(__bridge id<MTLTexture>)texture.GetPtr()
                                                              atIndex:index];
    }


    void RenderCommandEncoder::SetVertexTextures(const Texture* textures, const ns::Range& range)
    {
        Validate();

        const uint32_t maxTextures = 32;
        assert(range.Length <= maxTextures);

        id<MTLTexture> mtlTextures[maxTextures];
        for (uint32_t i=0; i<range.Length; i++)
            mtlTextures[i] = (__bridge id<MTLTexture>)textures[i].GetPtr();

        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setVertexTextures:mtlTextures withRange:NSMakeRange(range.Location, range.Length)];
    }

    void RenderCommandEncoder::SetVertexSamplerState(const SamplerState& sampler, uint32_t index)
    {
        Validate();
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setVertexSamplerState:(__bridge id<MTLSamplerState>)sampler.GetPtr()
                                                                   atIndex:index];

    }

    void RenderCommandEncoder::SetVertexSamplerStates(const SamplerState* samplers, const ns::Range& range)
    {
        Validate();

        const uint32_t maxStates = 32;
        assert(range.Length <= maxStates);

        id<MTLSamplerState> mtlStates[maxStates];
        for (uint32_t i=0; i<range.Length; i++)
            mtlStates[i] = (__bridge id<MTLSamplerState>)samplers[i].GetPtr();

        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setVertexSamplerStates:mtlStates withRange:NSMakeRange(range.Location, range.Length)];
    }

    void RenderCommandEncoder::SetVertexSamplerState(const SamplerState& sampler, float lodMinClamp, float lodMaxClamp, uint32_t index)
    {
        Validate();
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setVertexSamplerState:(__bridge id<MTLSamplerState>)sampler.GetPtr()
                                                               lodMinClamp:lodMinClamp
                                                               lodMaxClamp:lodMaxClamp
                                                                   atIndex:index];
    }

    void RenderCommandEncoder::SetVertexSamplerStates(const SamplerState* samplers, const float* lodMinClamps, const float* lodMaxClamps, const ns::Range& range)
    {
        Validate();

        const uint32_t maxStates = 32;
        assert(range.Length <= maxStates);

        id<MTLSamplerState> mtlStates[maxStates];
        for (uint32_t i=0; i<range.Length; i++)
            mtlStates[i] = (__bridge id<MTLSamplerState>)samplers[i].GetPtr();

        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setVertexSamplerStates:mtlStates
                                                               lodMinClamps:lodMinClamps
                                                               lodMaxClamps:lodMaxClamps
                                                                  withRange:NSMakeRange(range.Location, range.Length)];
    }

    void RenderCommandEncoder::SetViewport(const Viewport& viewport)
    {
        Validate();
        MTLViewport mtlViewport = { viewport.OriginX, viewport.OriginY, viewport.Width, viewport.Height, viewport.ZNear, viewport.ZFar };
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setViewport:mtlViewport];
    }

    void RenderCommandEncoder::SetFrontFacingWinding(Winding frontFacingWinding)
    {
        Validate();
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setFrontFacingWinding:MTLWinding(frontFacingWinding)];
    }

    void RenderCommandEncoder::SetCullMode(CullMode cullMode)
    {
        Validate();
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setCullMode:MTLCullMode(cullMode)];
    }

    void RenderCommandEncoder::SetDepthClipMode(DepthClipMode depthClipMode)
    {
        Validate();
#if MTLPP_IS_AVAILABLE_MAC(10_11)
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setDepthClipMode:MTLDepthClipMode(depthClipMode)];
#endif
    }

    void RenderCommandEncoder::SetDepthBias(float depthBias, float slopeScale, float clamp)
    {
        Validate();
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setDepthBias:depthBias slopeScale:slopeScale clamp:clamp];
    }

    void RenderCommandEncoder::SetScissorRect(const ScissorRect& rect)
    {
        Validate();
        MTLScissorRect mtlRect { rect.X, rect.Y, rect.Width, rect.Height };
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setScissorRect:mtlRect];
    }

    void RenderCommandEncoder::SetTriangleFillMode(TriangleFillMode fillMode)
    {
        Validate();
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setTriangleFillMode:MTLTriangleFillMode(fillMode)];
    }

    void RenderCommandEncoder::SetFragmentData(const void* bytes, uint32_t length, uint32_t index)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_11, 8_3)
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setFragmentBytes:bytes
                                                               length:length
                                                              atIndex:index];
#endif
    }

    void RenderCommandEncoder::SetFragmentBuffer(const Buffer& buffer, uint32_t offset, uint32_t index)
    {
        Validate();
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setFragmentBuffer:(__bridge id<MTLBuffer>)buffer.GetPtr()
                                                                offset:offset
                                                               atIndex:index];
    }

    void RenderCommandEncoder::SetFragmentBufferOffset(uint32_t offset, uint32_t index)
    {
#if MTLPP_IS_AVAILABLE(10_11, 8_3)
        Validate();
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setFragmentBufferOffset:offset atIndex:index];
#endif
    }

    void RenderCommandEncoder::SetFragmentBuffers(const Buffer* buffers, const uint32_t* offsets, const ns::Range& range)
    {
        Validate();

        const uint32_t maxBuffers = 32;
        assert(range.Length <= maxBuffers);

        id<MTLBuffer> mtlBuffers[maxBuffers];
        NSUInteger    nsOffsets[maxBuffers];
        for (uint32_t i=0; i<range.Length; i++)
        {
            mtlBuffers[i] = (__bridge id<MTLBuffer>)buffers[i].GetPtr();
            nsOffsets[i] = offsets[i];
        }

        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setFragmentBuffers:mtlBuffers offsets:nsOffsets withRange:NSMakeRange(range.Location, range.Length)];
    }

    void RenderCommandEncoder::SetFragmentTexture(const Texture& texture, uint32_t index)
    {
        Validate();
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setFragmentTexture:(__bridge id<MTLTexture>)texture.GetPtr()
                                                                atIndex:index];
    }

    void RenderCommandEncoder::SetFragmentTextures(const Texture* textures, const ns::Range& range)
    {
        Validate();

        const uint32_t maxTextures = 32;
        assert(range.Length <= maxTextures);

        id<MTLTexture> mtlTextures[maxTextures];
        for (uint32_t i=0; i<range.Length; i++)
            mtlTextures[i] = (__bridge id<MTLTexture>)textures[i].GetPtr();

        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setFragmentTextures:mtlTextures withRange:NSMakeRange(range.Location, range.Length)];
    }

    void RenderCommandEncoder::SetFragmentSamplerState(const SamplerState& sampler, uint32_t index)
    {
        Validate();
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setFragmentSamplerState:(__bridge id<MTLSamplerState>)sampler.GetPtr()
                                                                     atIndex:index];
    }

    void RenderCommandEncoder::SetFragmentSamplerStates(const SamplerState* samplers, const ns::Range& range)
    {
        Validate();

        const uint32_t maxStates = 32;
        assert(range.Length <= maxStates);

        id<MTLSamplerState> mtlStates[maxStates];
        for (uint32_t i=0; i<range.Length; i++)
            mtlStates[i] = (__bridge id<MTLSamplerState>)samplers[i].GetPtr();

        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setFragmentSamplerStates:mtlStates withRange:NSMakeRange(range.Location, range.Length)];
    }

    void RenderCommandEncoder::SetFragmentSamplerState(const SamplerState& sampler, float lodMinClamp, float lodMaxClamp, uint32_t index)
    {
        Validate();
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setFragmentSamplerState:(__bridge id<MTLSamplerState>)sampler.GetPtr()
                                                                 lodMinClamp:lodMinClamp
                                                                 lodMaxClamp:lodMaxClamp
                                                                     atIndex:index];
    }

    void RenderCommandEncoder::SetFragmentSamplerStates(const SamplerState* samplers, const float* lodMinClamps, const float* lodMaxClamps, const ns::Range& range)
    {
        Validate();

        const uint32_t maxStates = 32;
        assert(range.Length <= maxStates);

        id<MTLSamplerState> mtlStates[maxStates];
        for (uint32_t i=0; i<range.Length; i++)
            mtlStates[i] = (__bridge id<MTLSamplerState>)samplers[i].GetPtr();

        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setFragmentSamplerStates:mtlStates
                                                                 lodMinClamps:lodMinClamps
                                                                 lodMaxClamps:lodMaxClamps
                                                                    withRange:NSMakeRange(range.Location, range.Length)];
    }

    void RenderCommandEncoder::SetBlendColor(float red, float green, float blue, float alpha)
    {
        Validate();
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setBlendColorRed:red green:green blue:blue alpha:alpha];
    }

    void RenderCommandEncoder::SetDepthStencilState(const DepthStencilState& depthStencilState)
    {
        Validate();
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setDepthStencilState:(__bridge id<MTLDepthStencilState>)depthStencilState.GetPtr()];
    }

    void RenderCommandEncoder::SetStencilReferenceValue(uint32_t referenceValue)
    {
        Validate();
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setStencilReferenceValue:referenceValue];
    }

    void RenderCommandEncoder::SetStencilReferenceValue(uint32_t frontReferenceValue, uint32_t backReferenceValue)
    {
        Validate();
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setStencilFrontReferenceValue:frontReferenceValue backReferenceValue:backReferenceValue];
    }

    void RenderCommandEncoder::SetVisibilityResultMode(VisibilityResultMode mode, uint32_t offset)
    {
        Validate();
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setVisibilityResultMode:MTLVisibilityResultMode(mode) offset:offset];
    }

    void RenderCommandEncoder::SetColorStoreAction(StoreAction storeAction, uint32_t colorAttachmentIndex)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setColorStoreAction:MTLStoreAction(storeAction) atIndex:colorAttachmentIndex];
#endif
    }

    void RenderCommandEncoder::SetDepthStoreAction(StoreAction storeAction)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setDepthStoreAction:MTLStoreAction(storeAction)];
#endif
    }

    void RenderCommandEncoder::SetStencilStoreAction(StoreAction storeAction)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setStencilStoreAction:MTLStoreAction(storeAction)];
#endif
    }

    void RenderCommandEncoder::Draw(PrimitiveType primitiveType, uint32_t vertexStart, uint32_t vertexCount)
    {
        Validate();
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr drawPrimitives:MTLPrimitiveType(primitiveType)
                                                        vertexStart:vertexStart
                                                        vertexCount:vertexCount];
    }

    void RenderCommandEncoder::Draw(PrimitiveType primitiveType, uint32_t vertexStart, uint32_t vertexCount, uint32_t instanceCount)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_11, 9_0)
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr drawPrimitives:MTLPrimitiveType(primitiveType)
                                                        vertexStart:vertexStart
                                                        vertexCount:vertexCount
                                                      instanceCount:instanceCount];
#endif
    }

    void RenderCommandEncoder::Draw(PrimitiveType primitiveType, uint32_t vertexStart, uint32_t vertexCount, uint32_t instanceCount, uint32_t baseInstance)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_11, 9_0)
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr drawPrimitives:MTLPrimitiveType(primitiveType)
                                                        vertexStart:vertexStart
                                                        vertexCount:vertexCount
                                                      instanceCount:instanceCount
                                                       baseInstance:baseInstance];
#endif
    }

    void RenderCommandEncoder::Draw(PrimitiveType primitiveType, Buffer indirectBuffer, uint32_t indirectBufferOffset)
    {
        Validate();
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr drawPrimitives:MTLPrimitiveType(primitiveType)
                                                     indirectBuffer:(__bridge id<MTLBuffer>)indirectBuffer.GetPtr()
                                               indirectBufferOffset:indirectBufferOffset];
    }

    void RenderCommandEncoder::DrawIndexed(PrimitiveType primitiveType, uint32_t indexCount, IndexType indexType, const Buffer& indexBuffer, uint32_t indexBufferOffset)
    {
        Validate();
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr drawIndexedPrimitives:MTLPrimitiveType(primitiveType)
                                                                indexCount:indexCount
                                                                 indexType:MTLIndexType(indexType)
                                                               indexBuffer:(__bridge id<MTLBuffer>)indexBuffer.GetPtr()
                                                         indexBufferOffset:indexBufferOffset];
    }

    void RenderCommandEncoder::DrawIndexed(PrimitiveType primitiveType, uint32_t indexCount, IndexType indexType, const Buffer& indexBuffer, uint32_t indexBufferOffset, uint32_t instanceCount)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_11, 9_0)
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr drawIndexedPrimitives:MTLPrimitiveType(primitiveType)
                                                                indexCount:indexCount indexType:MTLIndexType(indexType)
                                                               indexBuffer:(__bridge id<MTLBuffer>)indexBuffer.GetPtr()
                                                         indexBufferOffset:indexBufferOffset instanceCount:instanceCount];
#endif
    }

    void RenderCommandEncoder::DrawIndexed(PrimitiveType primitiveType, uint32_t indexCount, IndexType indexType, const Buffer& indexBuffer, uint32_t indexBufferOffset, uint32_t instanceCount, uint32_t baseVertex, uint32_t baseInstance)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_11, 9_0)
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr drawIndexedPrimitives:MTLPrimitiveType(primitiveType)
                                                                indexCount:indexCount
                                                                 indexType:MTLIndexType(indexType)
                                                               indexBuffer:(__bridge id<MTLBuffer>)indexBuffer.GetPtr()
                                                         indexBufferOffset:indexBufferOffset
                                                             instanceCount:instanceCount
                                                                baseVertex:baseVertex
                                                              baseInstance:baseInstance];
#endif
    }

    void RenderCommandEncoder::DrawIndexed(PrimitiveType primitiveType, IndexType indexType, const Buffer& indexBuffer, uint32_t indexBufferOffset, const Buffer& indirectBuffer, uint32_t indirectBufferOffset)
    {
        Validate();
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr drawIndexedPrimitives:MTLPrimitiveType(primitiveType)
                                                                 indexType:MTLIndexType(indexType)
                                                               indexBuffer:(__bridge id<MTLBuffer>)indexBuffer.GetPtr()
                                                         indexBufferOffset:indexBufferOffset
                                                            indirectBuffer:(__bridge id<MTLBuffer>)indirectBuffer.GetPtr()
                                                      indirectBufferOffset:indirectBufferOffset];
    }

    void RenderCommandEncoder::TextureBarrier()
    {
        Validate();
#if MTLPP_IS_AVAILABLE_MAC(10_11)
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr textureBarrier];
#endif
    }

    void RenderCommandEncoder::UpdateFence(const Fence& fence, RenderStages afterStages)
    {
        Validate();
#if MTLPP_IS_AVAILABLE_IOS(10_0)
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr updateFence:(__bridge id<MTLFence>)fence.GetPtr() afterStages:MTLRenderStages(afterStages)];
#endif
    }

    void RenderCommandEncoder::WaitForFence(const Fence& fence, RenderStages beforeStages)
    {
        Validate();
#if MTLPP_IS_AVAILABLE_IOS(10_0)
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr waitForFence:(__bridge id<MTLFence>)fence.GetPtr() beforeStages:MTLRenderStages(beforeStages)];
#endif
    }

    void RenderCommandEncoder::SetTessellationFactorBuffer(const Buffer& buffer, uint32_t offset, uint32_t instanceStride)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setTessellationFactorBuffer:(__bridge id<MTLBuffer>)buffer.GetPtr() offset:offset instanceStride:instanceStride];
#endif
    }

    void RenderCommandEncoder::SetTessellationFactorScale(float scale)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr setTessellationFactorScale:scale];
#endif
    }

    void RenderCommandEncoder::DrawPatches(uint32_t numberOfPatchControlPoints, uint32_t patchStart, uint32_t patchCount, const Buffer& patchIndexBuffer, uint32_t patchIndexBufferOffset, uint32_t instanceCount, uint32_t baseInstance)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr drawPatches:numberOfPatchControlPoints
                                                      patchStart:patchStart
                                                      patchCount:patchCount
                                                patchIndexBuffer:(__bridge id<MTLBuffer>)patchIndexBuffer.GetPtr()
                                          patchIndexBufferOffset:patchIndexBufferOffset
                                                   instanceCount:instanceCount
                                                    baseInstance:baseInstance];
#endif
    }

    void RenderCommandEncoder::DrawPatches(uint32_t numberOfPatchControlPoints, const Buffer& patchIndexBuffer, uint32_t patchIndexBufferOffset, const Buffer& indirectBuffer, uint32_t indirectBufferOffset)
    {
        Validate();
#if MTLPP_IS_AVAILABLE_MAC(10_12)
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr drawPatches:numberOfPatchControlPoints
                                                patchIndexBuffer:(__bridge id<MTLBuffer>)patchIndexBuffer.GetPtr()
                                          patchIndexBufferOffset:patchIndexBufferOffset
                                                  indirectBuffer:(__bridge id<MTLBuffer>)indirectBuffer.GetPtr()
                                            indirectBufferOffset:indirectBufferOffset];
#endif
    }

    void RenderCommandEncoder::DrawIndexedPatches(uint32_t numberOfPatchControlPoints, uint32_t patchStart, uint32_t patchCount, const Buffer& patchIndexBuffer, uint32_t patchIndexBufferOffset, const Buffer& controlPointIndexBuffer, uint32_t controlPointIndexBufferOffset, uint32_t instanceCount, uint32_t baseInstance)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr drawIndexedPatches:numberOfPatchControlPoints
                                                             patchStart:patchStart
                                                             patchCount:patchCount
                                                       patchIndexBuffer:(__bridge id<MTLBuffer>)patchIndexBuffer.GetPtr()
                                                 patchIndexBufferOffset:patchIndexBufferOffset
                                                controlPointIndexBuffer:(__bridge id<MTLBuffer>)controlPointIndexBuffer.GetPtr()
                                          controlPointIndexBufferOffset:controlPointIndexBufferOffset
                                                          instanceCount:instanceCount
                                                           baseInstance:baseInstance];
#endif
    }

    void RenderCommandEncoder::DrawIndexedPatches(uint32_t numberOfPatchControlPoints, const Buffer& patchIndexBuffer, uint32_t patchIndexBufferOffset, const Buffer& controlPointIndexBuffer, uint32_t controlPointIndexBufferOffset, const Buffer& indirectBuffer, uint32_t indirectBufferOffset)
    {
        Validate();
#if MTLPP_IS_AVAILABLE_MAC(10_12)
        [(__bridge id<MTLRenderCommandEncoder>)m_ptr drawIndexedPatches:numberOfPatchControlPoints
                                                       patchIndexBuffer:(__bridge id<MTLBuffer>)patchIndexBuffer.GetPtr()
                                                 patchIndexBufferOffset:patchIndexBufferOffset
                                                controlPointIndexBuffer:(__bridge id<MTLBuffer>)controlPointIndexBuffer.GetPtr()
                                          controlPointIndexBufferOffset:controlPointIndexBufferOffset
                                                         indirectBuffer:(__bridge id<MTLBuffer>)indirectBuffer.GetPtr()
                                                   indirectBufferOffset:indirectBufferOffset];
#endif
    }
}


//////////////////////////////////////
// FILE: render_pass.mm
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #include "render_pass.hpp"
// #include "texture.hpp"
#include <Metal/MTLRenderPass.h>

namespace mtlpp
{
    RenderPassAttachmentDescriptor::RenderPassAttachmentDescriptor() :
        ns::Object(ns::Handle{ (__bridge void*)[[MTLRenderPassAttachmentDescriptor alloc] init] })
    {
    }

    Texture RenderPassAttachmentDescriptor::GetTexture() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge MTLRenderPassAttachmentDescriptor*)m_ptr texture] };
    }

    uint32_t RenderPassAttachmentDescriptor::GetLevel() const
    {
        Validate();
        return uint32_t([(__bridge MTLRenderPassAttachmentDescriptor*)m_ptr level]);
    }

    uint32_t RenderPassAttachmentDescriptor::GetSlice() const
    {
        Validate();
        return uint32_t([(__bridge MTLRenderPassAttachmentDescriptor*)m_ptr slice]);
    }

    uint32_t RenderPassAttachmentDescriptor::GetDepthPlane() const
    {
        Validate();
        return uint32_t([(__bridge MTLRenderPassAttachmentDescriptor*)m_ptr depthPlane]);
    }

    Texture RenderPassAttachmentDescriptor::GetResolveTexture() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge MTLRenderPassAttachmentDescriptor*)m_ptr resolveTexture] };
    }

    uint32_t RenderPassAttachmentDescriptor::GetResolveLevel() const
    {
        Validate();
        return uint32_t([(__bridge MTLRenderPassAttachmentDescriptor*)m_ptr resolveLevel]);
    }

    uint32_t RenderPassAttachmentDescriptor::GetResolveSlice() const
    {
        Validate();
        return uint32_t([(__bridge MTLRenderPassAttachmentDescriptor*)m_ptr resolveSlice]);
    }

    uint32_t RenderPassAttachmentDescriptor::GetResolveDepthPlane() const
    {
        Validate();
        return uint32_t([(__bridge MTLRenderPassAttachmentDescriptor*)m_ptr resolveDepthPlane]);
    }

    LoadAction RenderPassAttachmentDescriptor::GetLoadAction() const
    {
        Validate();
        return LoadAction([(__bridge MTLRenderPassAttachmentDescriptor*)m_ptr loadAction]);
    }

    StoreAction RenderPassAttachmentDescriptor::GetStoreAction() const
    {
        Validate();
        return StoreAction([(__bridge MTLRenderPassAttachmentDescriptor*)m_ptr storeAction]);
    }

    void RenderPassAttachmentDescriptor::SetTexture(const Texture& texture)
    {
        Validate();
        [(__bridge MTLRenderPassAttachmentDescriptor*)m_ptr setTexture:(__bridge id<MTLTexture>)texture.GetPtr()];
    }

    void RenderPassAttachmentDescriptor::SetLevel(uint32_t level)
    {
        Validate();
        [(__bridge MTLRenderPassAttachmentDescriptor*)m_ptr setLevel:level];
    }

    void RenderPassAttachmentDescriptor::SetSlice(uint32_t slice)
    {
        Validate();
        [(__bridge MTLRenderPassAttachmentDescriptor*)m_ptr setSlice:slice];
    }

    void RenderPassAttachmentDescriptor::SetDepthPlane(uint32_t depthPlane)
    {
        Validate();
        [(__bridge MTLRenderPassAttachmentDescriptor*)m_ptr setDepthPlane:depthPlane];
    }

    void RenderPassAttachmentDescriptor::SetResolveTexture(const Texture& texture)
    {
        Validate();
        [(__bridge MTLRenderPassAttachmentDescriptor*)m_ptr setResolveTexture:(__bridge id<MTLTexture>)texture.GetPtr()];
    }

    void RenderPassAttachmentDescriptor::SetResolveLevel(uint32_t resolveLevel)
    {
        Validate();
        [(__bridge MTLRenderPassAttachmentDescriptor*)m_ptr setResolveLevel:resolveLevel];
    }

    void RenderPassAttachmentDescriptor::SetResolveSlice(uint32_t resolveSlice)
    {
        Validate();
        [(__bridge MTLRenderPassAttachmentDescriptor*)m_ptr setResolveSlice:resolveSlice];
    }

    void RenderPassAttachmentDescriptor::SetResolveDepthPlane(uint32_t resolveDepthPlane)
    {
        Validate();
        [(__bridge MTLRenderPassAttachmentDescriptor*)m_ptr setResolveDepthPlane:resolveDepthPlane];
    }

    void RenderPassAttachmentDescriptor::SetLoadAction(LoadAction loadAction)
    {
        Validate();
        [(__bridge MTLRenderPassAttachmentDescriptor*)m_ptr setLoadAction:MTLLoadAction(loadAction)];
    }

    void RenderPassAttachmentDescriptor::SetStoreAction(StoreAction storeAction)
    {
        Validate();
        [(__bridge MTLRenderPassAttachmentDescriptor*)m_ptr setStoreAction:MTLStoreAction(storeAction)];
    }

    RenderPassColorAttachmentDescriptor::RenderPassColorAttachmentDescriptor() :
        RenderPassAttachmentDescriptor(ns::Handle{ (__bridge void*)[[MTLRenderPassColorAttachmentDescriptor alloc] init] })
    {
    }

    ClearColor RenderPassColorAttachmentDescriptor::GetClearColor() const
    {
        Validate();
        MTLClearColor mtlClearColor = [(__bridge MTLRenderPassColorAttachmentDescriptor*)m_ptr clearColor];
        return ClearColor(mtlClearColor.red, mtlClearColor.green, mtlClearColor.blue, mtlClearColor.alpha);
    }

    void RenderPassColorAttachmentDescriptor::SetClearColor(const ClearColor& clearColor)
    {
        Validate();
        MTLClearColor mtlClearColor = { clearColor.Red, clearColor.Green, clearColor.Blue, clearColor.Alpha };
        [(__bridge MTLRenderPassColorAttachmentDescriptor*)m_ptr setClearColor:mtlClearColor];
    }

    RenderPassDepthAttachmentDescriptor::RenderPassDepthAttachmentDescriptor() :
        RenderPassAttachmentDescriptor(ns::Handle{ (__bridge void*)[[MTLRenderPassDepthAttachmentDescriptor alloc] init] })
    {
    }

    double RenderPassDepthAttachmentDescriptor::GetClearDepth() const
    {
        Validate();
        return [(__bridge MTLRenderPassDepthAttachmentDescriptor*)m_ptr clearDepth];
    }

    MultisampleDepthResolveFilter RenderPassDepthAttachmentDescriptor::GetDepthResolveFilter() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE_IOS(9_0)
        return MultisampleDepthResolveFilter([(__bridge MTLRenderPassDepthAttachmentDescriptor*)m_ptr depthResolveFilter]);
#else
        return MultisampleDepthResolveFilter(0);
#endif
    }

    void RenderPassDepthAttachmentDescriptor::SetClearDepth(double clearDepth)
    {
        Validate();
        [(__bridge MTLRenderPassDepthAttachmentDescriptor*)m_ptr setClearDepth:clearDepth];
    }

    void RenderPassDepthAttachmentDescriptor::SetDepthResolveFilter(MultisampleDepthResolveFilter depthResolveFilter)
    {
        Validate();
#if MTLPP_IS_AVAILABLE_IOS(9_0)
        [(__bridge MTLRenderPassDepthAttachmentDescriptor*)m_ptr setDepthResolveFilter:MTLMultisampleDepthResolveFilter(depthResolveFilter)];
#endif
    }

    RenderPassStencilAttachmentDescriptor::RenderPassStencilAttachmentDescriptor() :
        RenderPassAttachmentDescriptor(ns::Handle{ (__bridge void*)[[MTLRenderPassStencilAttachmentDescriptor alloc] init] })
    {
    }

    uint32_t RenderPassStencilAttachmentDescriptor::GetClearStencil() const
    {
        Validate();
        return uint32_t([(__bridge MTLRenderPassStencilAttachmentDescriptor*)m_ptr clearStencil]);
    }

    void RenderPassStencilAttachmentDescriptor::SetClearStencil(uint32_t clearStencil)
    {
        Validate();
        [(__bridge MTLRenderPassStencilAttachmentDescriptor*)m_ptr setClearStencil:clearStencil];
    }

    RenderPassDescriptor::RenderPassDescriptor() :
        ns::Object(ns::Handle{ (__bridge void*)[[MTLRenderPassDescriptor alloc] init] })
    {
    }

    ns::Array<RenderPassColorAttachmentDescriptor> RenderPassDescriptor::GetColorAttachments() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge MTLRenderPassDescriptor*)m_ptr colorAttachments] };
    }

    RenderPassDepthAttachmentDescriptor RenderPassDescriptor::GetDepthAttachment() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge MTLRenderPassDescriptor*)m_ptr depthAttachment] };
    }

    RenderPassStencilAttachmentDescriptor RenderPassDescriptor::GetStencilAttachment() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge MTLRenderPassDescriptor*)m_ptr stencilAttachment] };
    }

    Buffer RenderPassDescriptor::GetVisibilityResultBuffer() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge MTLRenderPassDescriptor*)m_ptr visibilityResultBuffer] };
    }

    uint32_t RenderPassDescriptor::GetRenderTargetArrayLength() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE_MAC(10_11)
        return uint32_t([(__bridge MTLRenderPassDescriptor*)m_ptr renderTargetArrayLength]);
#else
        return 0;
#endif
    }

    void RenderPassDescriptor::SetDepthAttachment(const RenderPassDepthAttachmentDescriptor& depthAttachment)
    {
        Validate();
        [(__bridge MTLRenderPassDescriptor*)m_ptr setDepthAttachment:(__bridge MTLRenderPassDepthAttachmentDescriptor*)depthAttachment.GetPtr()];
    }

    void RenderPassDescriptor::SetStencilAttachment(const RenderPassStencilAttachmentDescriptor& stencilAttachment)
    {
        Validate();
        [(__bridge MTLRenderPassDescriptor*)m_ptr setStencilAttachment:(__bridge MTLRenderPassStencilAttachmentDescriptor*)stencilAttachment.GetPtr()];
    }

    void RenderPassDescriptor::SetVisibilityResultBuffer(const Buffer& visibilityResultBuffer)
    {
        Validate();
        [(__bridge MTLRenderPassDescriptor*)m_ptr setVisibilityResultBuffer:(__bridge id<MTLBuffer>)visibilityResultBuffer.GetPtr()];
    }

    void RenderPassDescriptor::SetRenderTargetArrayLength(uint32_t renderTargetArrayLength)
    {
        Validate();
#if MTLPP_IS_AVAILABLE_MAC(10_11)
        [(__bridge MTLRenderPassDescriptor*)m_ptr setRenderTargetArrayLength:renderTargetArrayLength];
#endif
    }
}

//////////////////////////////////////
// FILE: render_pipeline.mm
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #include "render_pipeline.hpp"
// #include "vertex_descriptor.hpp"
#include <Metal/MTLRenderPipeline.h>

namespace mtlpp
{
    RenderPipelineColorAttachmentDescriptor::RenderPipelineColorAttachmentDescriptor() :
        ns::Object(ns::Handle{ (__bridge void*)[[MTLRenderPipelineColorAttachmentDescriptor alloc] init] })
    {
    }

    PixelFormat RenderPipelineColorAttachmentDescriptor::GetPixelFormat() const
    {
        Validate();
        return PixelFormat([(__bridge MTLRenderPipelineColorAttachmentDescriptor*)m_ptr pixelFormat]);
    }

    bool RenderPipelineColorAttachmentDescriptor::IsBlendingEnabled() const
    {
        Validate();
        return [(__bridge MTLRenderPipelineColorAttachmentDescriptor*)m_ptr isBlendingEnabled];
    }

    BlendFactor RenderPipelineColorAttachmentDescriptor::GetSourceRgbBlendFactor() const
    {
        Validate();
        return BlendFactor([(__bridge MTLRenderPipelineColorAttachmentDescriptor*)m_ptr sourceRGBBlendFactor]);
    }

    BlendFactor RenderPipelineColorAttachmentDescriptor::GetDestinationRgbBlendFactor() const
    {
        Validate();
        return BlendFactor([(__bridge MTLRenderPipelineColorAttachmentDescriptor*)m_ptr destinationRGBBlendFactor]);
    }

    BlendOperation RenderPipelineColorAttachmentDescriptor::GetRgbBlendOperation() const
    {
        Validate();
        return BlendOperation([(__bridge MTLRenderPipelineColorAttachmentDescriptor*)m_ptr rgbBlendOperation]);
    }

    BlendFactor RenderPipelineColorAttachmentDescriptor::GetSourceAlphaBlendFactor() const
    {
        Validate();
        return BlendFactor([(__bridge MTLRenderPipelineColorAttachmentDescriptor*)m_ptr sourceAlphaBlendFactor]);
    }

    BlendFactor RenderPipelineColorAttachmentDescriptor::GetDestinationAlphaBlendFactor() const
    {
        Validate();
        return BlendFactor([(__bridge MTLRenderPipelineColorAttachmentDescriptor*)m_ptr destinationAlphaBlendFactor]);
    }

    BlendOperation RenderPipelineColorAttachmentDescriptor::GetAlphaBlendOperation() const
    {
        Validate();
        return BlendOperation([(__bridge MTLRenderPipelineColorAttachmentDescriptor*)m_ptr alphaBlendOperation]);
    }

    ColorWriteMask RenderPipelineColorAttachmentDescriptor::GetWriteMask() const
    {
        Validate();
        return ColorWriteMask([(__bridge MTLRenderPipelineColorAttachmentDescriptor*)m_ptr writeMask]);
    }

    void RenderPipelineColorAttachmentDescriptor::SetPixelFormat(PixelFormat pixelFormat)
    {
        Validate();
        [(__bridge MTLRenderPipelineColorAttachmentDescriptor*)m_ptr setPixelFormat:MTLPixelFormat(pixelFormat)];
    }

    void RenderPipelineColorAttachmentDescriptor::SetBlendingEnabled(bool blendingEnabled)
    {
        Validate();
        [(__bridge MTLRenderPipelineColorAttachmentDescriptor*)m_ptr setBlendingEnabled:blendingEnabled];
    }

    void RenderPipelineColorAttachmentDescriptor::SetSourceRgbBlendFactor(BlendFactor sourceRgbBlendFactor)
    {
        Validate();
        [(__bridge MTLRenderPipelineColorAttachmentDescriptor*)m_ptr setSourceRGBBlendFactor:MTLBlendFactor(sourceRgbBlendFactor)];
    }

    void RenderPipelineColorAttachmentDescriptor::SetDestinationRgbBlendFactor(BlendFactor destinationRgbBlendFactor)
    {
        Validate();
        [(__bridge MTLRenderPipelineColorAttachmentDescriptor*)m_ptr setDestinationRGBBlendFactor:MTLBlendFactor(destinationRgbBlendFactor)];
    }

    void RenderPipelineColorAttachmentDescriptor::SetRgbBlendOperation(BlendOperation rgbBlendOperation)
    {
        Validate();
        [(__bridge MTLRenderPipelineColorAttachmentDescriptor*)m_ptr setRgbBlendOperation:MTLBlendOperation(rgbBlendOperation)];
    }

    void RenderPipelineColorAttachmentDescriptor::SetSourceAlphaBlendFactor(BlendFactor sourceAlphaBlendFactor)
    {
        Validate();
        [(__bridge MTLRenderPipelineColorAttachmentDescriptor*)m_ptr setSourceAlphaBlendFactor:MTLBlendFactor(sourceAlphaBlendFactor)];
    }

    void RenderPipelineColorAttachmentDescriptor::SetDestinationAlphaBlendFactor(BlendFactor destinationAlphaBlendFactor)
    {
        Validate();
        [(__bridge MTLRenderPipelineColorAttachmentDescriptor*)m_ptr setDestinationAlphaBlendFactor:MTLBlendFactor(destinationAlphaBlendFactor)];
    }

    void RenderPipelineColorAttachmentDescriptor::SetAlphaBlendOperation(BlendOperation alphaBlendOperation)
    {
        Validate();
        [(__bridge MTLRenderPipelineColorAttachmentDescriptor*)m_ptr setAlphaBlendOperation:MTLBlendOperation(alphaBlendOperation)];
    }

    void RenderPipelineColorAttachmentDescriptor::SetWriteMask(ColorWriteMask writeMask)
    {
        Validate();
        [(__bridge MTLRenderPipelineColorAttachmentDescriptor*)m_ptr setWriteMask:MTLColorWriteMask(writeMask)];
    }

    RenderPipelineReflection::RenderPipelineReflection() :
        ns::Object(ns::Handle{ (__bridge void*)[[MTLRenderPipelineReflection alloc] init] })
    {
    }

    const ns::Array<Argument> RenderPipelineReflection::GetVertexArguments() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge MTLRenderPipelineReflection*)m_ptr vertexArguments] };
    }

    const ns::Array<Argument> RenderPipelineReflection::GetFragmentArguments() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge MTLRenderPipelineReflection*)m_ptr fragmentArguments] };
    }

    RenderPipelineDescriptor::RenderPipelineDescriptor() :
        ns::Object(ns::Handle{ (__bridge void*)[[MTLRenderPipelineDescriptor alloc] init] })
    {
    }

    ns::String RenderPipelineDescriptor::GetLabel() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge MTLRenderPipelineDescriptor*)m_ptr label] };
    }

    Function RenderPipelineDescriptor::GetVertexFunction() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge MTLRenderPipelineDescriptor*)m_ptr vertexFunction] };
    }

    Function RenderPipelineDescriptor::GetFragmentFunction() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge MTLRenderPipelineDescriptor*)m_ptr fragmentFunction] };
    }

    VertexDescriptor RenderPipelineDescriptor::GetVertexDescriptor() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge MTLRenderPipelineDescriptor*)m_ptr vertexDescriptor] };
    }

    uint32_t RenderPipelineDescriptor::GetSampleCount() const
    {
        Validate();
        return uint32_t([(__bridge MTLRenderPipelineDescriptor*)m_ptr sampleCount]);
    }

    bool RenderPipelineDescriptor::IsAlphaToCoverageEnabled() const
    {
        Validate();
        return [(__bridge MTLRenderPipelineDescriptor*)m_ptr isAlphaToCoverageEnabled];
    }

    bool RenderPipelineDescriptor::IsAlphaToOneEnabled() const
    {
        Validate();
        return [(__bridge MTLRenderPipelineDescriptor*)m_ptr isAlphaToOneEnabled];
    }

    bool RenderPipelineDescriptor::IsRasterizationEnabled() const
    {
        Validate();
        return [(__bridge MTLRenderPipelineDescriptor*)m_ptr isRasterizationEnabled];
    }

    ns::Array<RenderPipelineColorAttachmentDescriptor> RenderPipelineDescriptor::GetColorAttachments() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge MTLRenderPipelineDescriptor*)m_ptr colorAttachments] };
    }

    PixelFormat RenderPipelineDescriptor::GetDepthAttachmentPixelFormat() const
    {
        Validate();
        return PixelFormat([(__bridge MTLRenderPipelineDescriptor*)m_ptr depthAttachmentPixelFormat]);
    }

    PixelFormat RenderPipelineDescriptor::GetStencilAttachmentPixelFormat() const
    {
        Validate();
        return PixelFormat([(__bridge MTLRenderPipelineDescriptor*)m_ptr stencilAttachmentPixelFormat]);
    }

    PrimitiveTopologyClass RenderPipelineDescriptor::GetInputPrimitiveTopology() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE_MAC(10_11)
        return PrimitiveTopologyClass([(__bridge MTLRenderPipelineDescriptor*)m_ptr inputPrimitiveTopology]);
#else
        return PrimitiveTopologyClass(0);
#endif
    }

    TessellationPartitionMode RenderPipelineDescriptor::GetTessellationPartitionMode() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return TessellationPartitionMode([(__bridge MTLRenderPipelineDescriptor*)m_ptr tessellationPartitionMode]);
#else
        return TessellationPartitionMode(0);
#endif
    }

    uint32_t RenderPipelineDescriptor::GetMaxTessellationFactor() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return uint32_t([(__bridge MTLRenderPipelineDescriptor*)m_ptr maxTessellationFactor]);
#else
        return 0;
#endif
    }

    bool RenderPipelineDescriptor::IsTessellationFactorScaleEnabled() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return [(__bridge MTLRenderPipelineDescriptor*)m_ptr isTessellationFactorScaleEnabled];
#else
        return false;
#endif
    }

    TessellationFactorFormat RenderPipelineDescriptor::GetTessellationFactorFormat() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return TessellationFactorFormat([(__bridge MTLRenderPipelineDescriptor*)m_ptr tessellationFactorFormat]);
#else
        return TessellationFactorFormat(0);
#endif
    }

    TessellationControlPointIndexType RenderPipelineDescriptor::GetTessellationControlPointIndexType() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return TessellationControlPointIndexType([(__bridge MTLRenderPipelineDescriptor*)m_ptr tessellationControlPointIndexType]);
#else
        return TessellationControlPointIndexType(0);
#endif
    }

    TessellationFactorStepFunction RenderPipelineDescriptor::GetTessellationFactorStepFunction() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return TessellationFactorStepFunction([(__bridge MTLRenderPipelineDescriptor*)m_ptr tessellationFactorStepFunction]);
#else
        return TessellationFactorStepFunction(0);
#endif
    }

    Winding RenderPipelineDescriptor::GetTessellationOutputWindingOrder() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return Winding([(__bridge MTLRenderPipelineDescriptor*)m_ptr tessellationOutputWindingOrder]);
#else
        return Winding(0);
#endif
    }

    void RenderPipelineDescriptor::SetLabel(const ns::String& label)
    {
        Validate();
        [(__bridge MTLRenderPipelineDescriptor*)m_ptr setLabel:(__bridge NSString*)label.GetPtr()];
    }

    void RenderPipelineDescriptor::SetVertexFunction(const Function& vertexFunction)
    {
        Validate();
        [(__bridge MTLRenderPipelineDescriptor*)m_ptr setVertexFunction:(__bridge id<MTLFunction>)vertexFunction.GetPtr()];
    }

    void RenderPipelineDescriptor::SetFragmentFunction(const Function& fragmentFunction)
    {
        Validate();
        [(__bridge MTLRenderPipelineDescriptor*)m_ptr setFragmentFunction:(__bridge id<MTLFunction>)fragmentFunction.GetPtr()];
    }

    void RenderPipelineDescriptor::SetVertexDescriptor(const VertexDescriptor& vertexDescriptor)
    {
        Validate();
        [(__bridge MTLRenderPipelineDescriptor*)m_ptr setVertexDescriptor:(__bridge MTLVertexDescriptor*)vertexDescriptor.GetPtr()];
    }

    void RenderPipelineDescriptor::SetSampleCount(uint32_t sampleCount)
    {
        Validate();
        [(__bridge MTLRenderPipelineDescriptor*)m_ptr setSampleCount:sampleCount];
    }

    void RenderPipelineDescriptor::SetAlphaToCoverageEnabled(bool alphaToCoverageEnabled)
    {
        Validate();
        [(__bridge MTLRenderPipelineDescriptor*)m_ptr setAlphaToCoverageEnabled:alphaToCoverageEnabled];
    }

    void RenderPipelineDescriptor::SetAlphaToOneEnabled(bool alphaToOneEnabled)
    {
        Validate();
        [(__bridge MTLRenderPipelineDescriptor*)m_ptr setAlphaToOneEnabled:alphaToOneEnabled];
    }

    void RenderPipelineDescriptor::SetRasterizationEnabled(bool rasterizationEnabled)
    {
        Validate();
        [(__bridge MTLRenderPipelineDescriptor*)m_ptr setRasterizationEnabled:rasterizationEnabled];
    }

    void RenderPipelineDescriptor::SetDepthAttachmentPixelFormat(PixelFormat depthAttachmentPixelFormat)
    {
        Validate();
        [(__bridge MTLRenderPipelineDescriptor*)m_ptr setDepthAttachmentPixelFormat:MTLPixelFormat(depthAttachmentPixelFormat)];
    }

    void RenderPipelineDescriptor::SetStencilAttachmentPixelFormat(PixelFormat depthAttachmentPixelFormat)
    {
        Validate();
        [(__bridge MTLRenderPipelineDescriptor*)m_ptr setStencilAttachmentPixelFormat:MTLPixelFormat(depthAttachmentPixelFormat)];
    }

    void RenderPipelineDescriptor::SetInputPrimitiveTopology(PrimitiveTopologyClass inputPrimitiveTopology)
    {
        Validate();
#if MTLPP_IS_AVAILABLE_MAC(10_11)
        [(__bridge MTLRenderPipelineDescriptor*)m_ptr setInputPrimitiveTopology:MTLPrimitiveTopologyClass(inputPrimitiveTopology)];
#endif
    }

    void RenderPipelineDescriptor::SetTessellationPartitionMode(TessellationPartitionMode tessellationPartitionMode)
    {
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        [(__bridge MTLRenderPipelineDescriptor*)m_ptr setTessellationPartitionMode:MTLTessellationPartitionMode(tessellationPartitionMode)];
#endif
    }

    void RenderPipelineDescriptor::SetMaxTessellationFactor(uint32_t maxTessellationFactor)
    {
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        [(__bridge MTLRenderPipelineDescriptor*)m_ptr setMaxTessellationFactor:maxTessellationFactor];
#endif
    }

    void RenderPipelineDescriptor::SetTessellationFactorScaleEnabled(bool tessellationFactorScaleEnabled)
    {
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        [(__bridge MTLRenderPipelineDescriptor*)m_ptr setTessellationFactorScaleEnabled:tessellationFactorScaleEnabled];
#endif
    }

    void RenderPipelineDescriptor::SetTessellationFactorFormat(TessellationFactorFormat tessellationFactorFormat)
    {
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        [(__bridge MTLRenderPipelineDescriptor*)m_ptr setTessellationFactorFormat:MTLTessellationFactorFormat(tessellationFactorFormat)];
#endif
    }

    void RenderPipelineDescriptor::SetTessellationControlPointIndexType(TessellationControlPointIndexType tessellationControlPointIndexType)
    {
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        [(__bridge MTLRenderPipelineDescriptor*)m_ptr setTessellationControlPointIndexType:MTLTessellationControlPointIndexType(tessellationControlPointIndexType)];
#endif
    }

    void RenderPipelineDescriptor::SetTessellationFactorStepFunction(TessellationFactorStepFunction tessellationFactorStepFunction)
    {
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        [(__bridge MTLRenderPipelineDescriptor*)m_ptr setTessellationFactorStepFunction:MTLTessellationFactorStepFunction(tessellationFactorStepFunction)];
#endif
    }

    void RenderPipelineDescriptor::SetTessellationOutputWindingOrder(Winding tessellationOutputWindingOrder)
    {
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        [(__bridge MTLRenderPipelineDescriptor*)m_ptr setTessellationOutputWindingOrder:MTLWinding(tessellationOutputWindingOrder)];
#endif
    }

    void RenderPipelineDescriptor::Reset()
    {
        [(__bridge MTLRenderPipelineDescriptor*)m_ptr reset];
    }

    ns::String RenderPipelineState::GetLabel() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLRenderPipelineState>)m_ptr label] };
    }

    Device RenderPipelineState::GetDevice() const
    {
        Validate();
        return ns::Handle { (__bridge void*)[(__bridge id<MTLRenderPipelineState>)m_ptr device] };
    }
}

//////////////////////////////////////
// FILE: resource.mm
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #include "resource.hpp"
// #include "heap.hpp"
#include <Metal/MTLResource.h>

namespace mtlpp
{
    ns::String Resource::GetLabel() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLResource>)m_ptr label] };
    }

    CpuCacheMode Resource::GetCpuCacheMode() const
    {
        Validate();
        return CpuCacheMode([(__bridge id<MTLResource>)m_ptr cpuCacheMode]);
    }

    StorageMode Resource::GetStorageMode() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_11, 9_0)
        return StorageMode([(__bridge id<MTLResource>)m_ptr storageMode]);
#else
        return StorageMode(0);
#endif
    }

    Heap Resource::GetHeap() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE_IOS(10_0)
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLResource>)m_ptr heap] };
#else
        return ns::Handle{ nullptr };
#endif
    }

    bool Resource::IsAliasable() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE_IOS(10_0)
        return [(__bridge id<MTLResource>)m_ptr isAliasable];
#else
        return false;
#endif
    }

    void Resource::SetLabel(const ns::String& label)
    {
        Validate();
        [(__bridge id<MTLResource>)m_ptr setLabel:(__bridge NSString*)label.GetPtr()];
    }

    PurgeableState Resource::SetPurgeableState(PurgeableState state)
    {
        Validate();
        return PurgeableState([(__bridge id<MTLResource>)m_ptr setPurgeableState:MTLPurgeableState(state)]);
    }

    void Resource::MakeAliasable() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE_IOS(10_0)
        [(__bridge id<MTLResource>)m_ptr makeAliasable];
#endif
    }
}

//////////////////////////////////////
// FILE: sampler.mm
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #include "sampler.hpp"
#include <Metal/MTLSampler.h>

namespace mtlpp
{
    SamplerDescriptor::SamplerDescriptor() :
        ns::Object(ns::Handle{ (__bridge void*)[[MTLSamplerDescriptor alloc] init] })
    {
    }

    SamplerMinMagFilter SamplerDescriptor::GetMinFilter() const
    {
        Validate();
        return SamplerMinMagFilter([(__bridge MTLSamplerDescriptor*)m_ptr minFilter]);
    }

    SamplerMinMagFilter SamplerDescriptor::GetMagFilter() const
    {
        Validate();
        return SamplerMinMagFilter([(__bridge MTLSamplerDescriptor*)m_ptr magFilter]);
    }

    SamplerMipFilter SamplerDescriptor::GetMipFilter() const
    {
        Validate();
        return SamplerMipFilter([(__bridge MTLSamplerDescriptor*)m_ptr mipFilter]);
    }

    uint32_t SamplerDescriptor::GetMaxAnisotropy() const
    {
        Validate();
        return uint32_t([(__bridge MTLSamplerDescriptor*)m_ptr maxAnisotropy]);
    }

    SamplerAddressMode SamplerDescriptor::GetSAddressMode() const
    {
        Validate();
        return SamplerAddressMode([(__bridge MTLSamplerDescriptor*)m_ptr sAddressMode]);
    }

    SamplerAddressMode SamplerDescriptor::GetTAddressMode() const
    {
        Validate();
        return SamplerAddressMode([(__bridge MTLSamplerDescriptor*)m_ptr tAddressMode]);
    }

    SamplerAddressMode SamplerDescriptor::GetRAddressMode() const
    {
        Validate();
        return SamplerAddressMode([(__bridge MTLSamplerDescriptor*)m_ptr rAddressMode]);
    }

    SamplerBorderColor SamplerDescriptor::GetBorderColor() const
    {
#if MTLPP_IS_AVAILABLE_MAC(10_12)
        return SamplerBorderColor([(__bridge MTLSamplerDescriptor*)m_ptr borderColor]);
#else
        return SamplerBorderColor(0);
#endif
    }

    bool SamplerDescriptor::IsNormalizedCoordinates() const
    {
        Validate();
        return [(__bridge MTLSamplerDescriptor*)m_ptr normalizedCoordinates];
    }

    float SamplerDescriptor::GetLodMinClamp() const
    {
        Validate();
        return [(__bridge MTLSamplerDescriptor*)m_ptr lodMinClamp];
    }

    float SamplerDescriptor::GetLodMaxClamp() const
    {
        Validate();
        return [(__bridge MTLSamplerDescriptor*)m_ptr lodMaxClamp];
    }

    CompareFunction SamplerDescriptor::GetCompareFunction() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_11, 9_0)
        return CompareFunction([(__bridge MTLSamplerDescriptor*)m_ptr compareFunction]);
#else
        return CompareFunction(0);
#endif
    }

    ns::String SamplerDescriptor::GetLabel() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge MTLSamplerDescriptor*)m_ptr label] };
    }

    void SamplerDescriptor::SetMinFilter(SamplerMinMagFilter minFilter)
    {
        Validate();
        [(__bridge MTLSamplerDescriptor*)m_ptr setMinFilter:MTLSamplerMinMagFilter(minFilter)];
    }

    void SamplerDescriptor::SetMagFilter(SamplerMinMagFilter magFilter)
    {
        Validate();
        [(__bridge MTLSamplerDescriptor*)m_ptr setMagFilter:MTLSamplerMinMagFilter(magFilter)];
    }

    void SamplerDescriptor::SetMipFilter(SamplerMipFilter mipFilter)
    {
        Validate();
        [(__bridge MTLSamplerDescriptor*)m_ptr setMipFilter:MTLSamplerMipFilter(mipFilter)];
    }

    void SamplerDescriptor::SetMaxAnisotropy(uint32_t maxAnisotropy)
    {
        Validate();
        [(__bridge MTLSamplerDescriptor*)m_ptr setMaxAnisotropy:maxAnisotropy];
    }

    void SamplerDescriptor::SetSAddressMode(SamplerAddressMode sAddressMode)
    {
        Validate();
        [(__bridge MTLSamplerDescriptor*)m_ptr setSAddressMode:MTLSamplerAddressMode(sAddressMode)];
    }

    void SamplerDescriptor::SetTAddressMode(SamplerAddressMode tAddressMode)
    {
        Validate();
        [(__bridge MTLSamplerDescriptor*)m_ptr setTAddressMode:MTLSamplerAddressMode(tAddressMode)];
    }

    void SamplerDescriptor::SetRAddressMode(SamplerAddressMode rAddressMode)
    {
        Validate();
        [(__bridge MTLSamplerDescriptor*)m_ptr setRAddressMode:MTLSamplerAddressMode(rAddressMode)];
    }

    void SamplerDescriptor::SetBorderColor(SamplerBorderColor borderColor)
    {
#if MTLPP_IS_AVAILABLE_MAC(10_12)
        [(__bridge MTLSamplerDescriptor*)m_ptr setBorderColor:MTLSamplerBorderColor(borderColor)];
#endif
    }

    void SamplerDescriptor::SetNormalizedCoordinates(bool normalizedCoordinates)
    {
        Validate();
        [(__bridge MTLSamplerDescriptor*)m_ptr setNormalizedCoordinates:normalizedCoordinates];
    }

    void SamplerDescriptor::SetLodMinClamp(float lodMinClamp)
    {
        Validate();
        [(__bridge MTLSamplerDescriptor*)m_ptr setLodMinClamp:lodMinClamp];
    }

    void SamplerDescriptor::SetLodMaxClamp(float lodMaxClamp)
    {
        Validate();
        [(__bridge MTLSamplerDescriptor*)m_ptr setLodMaxClamp:lodMaxClamp];
    }

    void SamplerDescriptor::SetCompareFunction(CompareFunction compareFunction)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_11, 9_0)
        [(__bridge MTLSamplerDescriptor*)m_ptr setCompareFunction:MTLCompareFunction(compareFunction)];
#endif
    }

    void SamplerDescriptor::SetLabel(const ns::String& label)
    {
        Validate();
        [(__bridge MTLSamplerDescriptor*)m_ptr setLabel:(__bridge NSString*)label.GetPtr()];
    }

    ns::String SamplerState::GetLabel() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLSamplerState>)m_ptr label] };
    }

    Device SamplerState::GetDevice() const
    {
        Validate();
        return ns::Handle { (__bridge void*)[(__bridge id<MTLSamplerState>)m_ptr device] };
    }
}


//////////////////////////////////////
// FILE: stage_input_output_descriptor.mm
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #include "stage_input_output_descriptor.hpp"
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
#   include <Metal/MTLStageInputOutputDescriptor.h>
#endif

namespace mtlpp
{
    BufferLayoutDescriptor::BufferLayoutDescriptor() :
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        ns::Object(ns::Handle{ (__bridge void*)[[MTLBufferLayoutDescriptor alloc] init] })
#else
        ns::Object(ns::Handle{ nullptr })
#endif
    {
    }

    uint32_t BufferLayoutDescriptor::GetStride() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return uint32_t([(__bridge MTLBufferLayoutDescriptor*)m_ptr stride]);
#else
        return 0;
#endif
    }

    StepFunction BufferLayoutDescriptor::GetStepFunction() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return StepFunction([(__bridge MTLBufferLayoutDescriptor*)m_ptr stepFunction]);
#else
        return StepFunction(0);
#endif
    }

    uint32_t BufferLayoutDescriptor::GetStepRate() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return uint32_t([(__bridge MTLBufferLayoutDescriptor*)m_ptr stepRate]);
#else
        return 0;
#endif
    }

    void BufferLayoutDescriptor::SetStride(uint32_t stride)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        [(__bridge MTLBufferLayoutDescriptor*)m_ptr setStride:stride];
#endif
    }

    void BufferLayoutDescriptor::SetStepFunction(StepFunction stepFunction)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        [(__bridge MTLBufferLayoutDescriptor*)m_ptr setStepFunction:MTLStepFunction(stepFunction)];
#endif
    }

    void BufferLayoutDescriptor::SetStepRate(uint32_t stepRate)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        [(__bridge MTLBufferLayoutDescriptor*)m_ptr setStepRate:stepRate];
#endif
    }

    AttributeDescriptor::AttributeDescriptor() :
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        ns::Object(ns::Handle{ (__bridge void*)[[MTLAttributeDescriptor alloc] init] })
#else
        ns::Object(ns::Handle{ nullptr })
#endif
    {
    }

    AttributeFormat AttributeDescriptor::GetFormat() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return AttributeFormat([(__bridge MTLAttributeDescriptor*)m_ptr format]);
#else
        return AttributeFormat(0);
#endif
    }

    uint32_t AttributeDescriptor::GetOffset() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return uint32_t([(__bridge MTLAttributeDescriptor*)m_ptr offset]);
#else
        return 0;
#endif
    }

    uint32_t AttributeDescriptor::GetBufferIndex() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return uint32_t([(__bridge MTLAttributeDescriptor*)m_ptr bufferIndex]);
#else
        return 0;
#endif
    }

    void AttributeDescriptor::SetFormat(AttributeFormat format)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        [(__bridge MTLAttributeDescriptor*)m_ptr setFormat:MTLAttributeFormat(format)];
#endif
    }

    void AttributeDescriptor::SetOffset(uint32_t offset)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        [(__bridge MTLAttributeDescriptor*)m_ptr setOffset:offset];
#endif
    }

    void AttributeDescriptor::SetBufferIndex(uint32_t bufferIndex)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        [(__bridge MTLAttributeDescriptor*)m_ptr setBufferIndex:bufferIndex];
#endif
    }

    StageInputOutputDescriptor::StageInputOutputDescriptor() :
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        ns::Object(ns::Handle{ (__bridge void*)[[MTLStageInputOutputDescriptor alloc] init] })
#else
        ns::Object(ns::Handle{ nullptr })
#endif
    {
    }

    ns::Array<BufferLayoutDescriptor> StageInputOutputDescriptor::GetLayouts() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return ns::Handle{ (__bridge void*)[(__bridge MTLStageInputOutputDescriptor*)m_ptr layouts] };
#else
        return ns::Handle{ nullptr };
#endif
    }

    ns::Array<AttributeDescriptor> StageInputOutputDescriptor::GetAttributes() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return ns::Handle{ (__bridge void*)[(__bridge MTLStageInputOutputDescriptor*)m_ptr attributes] };
#else
        return ns::Handle{ nullptr };
#endif
    }

    IndexType StageInputOutputDescriptor::GetIndexType() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return IndexType([(__bridge MTLStageInputOutputDescriptor*)m_ptr indexType]);
#else
        return IndexType(0);
#endif
    }

    uint32_t StageInputOutputDescriptor::GetIndexBufferIndex() const
   {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return uint32_t([(__bridge MTLStageInputOutputDescriptor*)m_ptr indexBufferIndex]);
#else
        return 0;
#endif
    }

   void StageInputOutputDescriptor::SetIndexType(IndexType indexType)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        [(__bridge MTLStageInputOutputDescriptor*)m_ptr setIndexType:MTLIndexType(indexType)];
#endif
    }

    void StageInputOutputDescriptor::SetIndexBufferIndex(uint32_t indexBufferIndex)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        [(__bridge MTLStageInputOutputDescriptor*)m_ptr setIndexBufferIndex:indexBufferIndex];
#endif
    }

    void StageInputOutputDescriptor::Reset()
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 10_0)
        [(__bridge MTLStageInputOutputDescriptor*)m_ptr reset];
#endif
    }
}


//////////////////////////////////////
// FILE: texture.mm
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #include "texture.hpp"
#include <Metal/MTLTexture.h>

namespace mtlpp
{
    TextureDescriptor::TextureDescriptor() :
        ns::Object(ns::Handle{ (__bridge void*)[[MTLTextureDescriptor alloc] init] })
    {
    }

    TextureDescriptor TextureDescriptor::Texture2DDescriptor(PixelFormat pixelFormat, uint32_t width, uint32_t height, bool mipmapped)
    {
        return ns::Handle{ (__bridge void*)[MTLTextureDescriptor texture2DDescriptorWithPixelFormat:MTLPixelFormat(pixelFormat)
                                                                                              width:width
                                                                                             height:height
                                                                                          mipmapped:mipmapped] };
    }

    TextureDescriptor TextureDescriptor::TextureCubeDescriptor(PixelFormat pixelFormat, uint32_t size, bool mipmapped)
    {
        return ns::Handle{ (__bridge void*)[MTLTextureDescriptor textureCubeDescriptorWithPixelFormat:MTLPixelFormat(pixelFormat)
                                                                                                 size:size
                                                                                            mipmapped:mipmapped] };
    }

    TextureType TextureDescriptor::GetTextureType() const
    {
        Validate();
        return TextureType([(__bridge MTLTextureDescriptor*)m_ptr textureType]);
    }

    PixelFormat TextureDescriptor::GetPixelFormat() const
    {
        Validate();
        return PixelFormat([(__bridge MTLTextureDescriptor*)m_ptr pixelFormat]);
    }

    uint32_t TextureDescriptor::GetWidth() const
    {
        Validate();
        return uint32_t([(__bridge MTLTextureDescriptor*)m_ptr width]);
    }

    uint32_t TextureDescriptor::GetHeight() const
    {
        Validate();
        return uint32_t([(__bridge MTLTextureDescriptor*)m_ptr height]);
    }

    uint32_t TextureDescriptor::GetDepth() const
    {
        Validate();
        return uint32_t([(__bridge MTLTextureDescriptor*)m_ptr depth]);
    }

    uint32_t TextureDescriptor::GetMipmapLevelCount() const
    {
        Validate();
        return uint32_t([(__bridge MTLTextureDescriptor*)m_ptr mipmapLevelCount]);
    }

    uint32_t TextureDescriptor::GetSampleCount() const
    {
        Validate();
        return uint32_t([(__bridge MTLTextureDescriptor*)m_ptr sampleCount]);
    }

    uint32_t TextureDescriptor::GetArrayLength() const
    {
        Validate();
        return uint32_t([(__bridge MTLTextureDescriptor*)m_ptr arrayLength]);
    }

    ResourceOptions TextureDescriptor::GetResourceOptions() const
    {
        Validate();
        return ResourceOptions([(__bridge MTLTextureDescriptor*)m_ptr resourceOptions]);
    }

    CpuCacheMode TextureDescriptor::GetCpuCacheMode() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_11, 9_0)
        return CpuCacheMode([(__bridge MTLTextureDescriptor*)m_ptr cpuCacheMode]);
#else
        return CpuCacheMode(0);
#endif
    }

    StorageMode TextureDescriptor::GetStorageMode() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_11, 9_0)
        return StorageMode([(__bridge MTLTextureDescriptor*)m_ptr storageMode]);
#else
        return StorageMode(0);
#endif
    }

    TextureUsage TextureDescriptor::GetUsage() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_11, 9_0)
        return TextureUsage([(__bridge MTLTextureDescriptor*)m_ptr usage]);
#else
        return TextureUsage(0);
#endif
    }

    void TextureDescriptor::SetTextureType(TextureType textureType)
    {
        Validate();
        [(__bridge MTLTextureDescriptor*)m_ptr setTextureType:MTLTextureType(textureType)];
    }

    void TextureDescriptor::SetPixelFormat(PixelFormat pixelFormat)
    {
        Validate();
        [(__bridge MTLTextureDescriptor*)m_ptr setPixelFormat:MTLPixelFormat(pixelFormat)];
    }

    void TextureDescriptor::SetWidth(uint32_t width)
    {
        Validate();
        [(__bridge MTLTextureDescriptor*)m_ptr setWidth:width];
    }

    void TextureDescriptor::SetHeight(uint32_t height)
    {
        Validate();
        [(__bridge MTLTextureDescriptor*)m_ptr setHeight:height];
    }

    void TextureDescriptor::SetDepth(uint32_t depth)
    {
        Validate();
        [(__bridge MTLTextureDescriptor*)m_ptr setDepth:depth];
    }

    void TextureDescriptor::SetMipmapLevelCount(uint32_t mipmapLevelCount)
    {
        Validate();
        [(__bridge MTLTextureDescriptor*)m_ptr setMipmapLevelCount:mipmapLevelCount];
    }

    void TextureDescriptor::SetSampleCount(uint32_t sampleCount)
    {
        Validate();
        [(__bridge MTLTextureDescriptor*)m_ptr setSampleCount:sampleCount];
    }

    void TextureDescriptor::SetArrayLength(uint32_t arrayLength)
    {
        Validate();
        [(__bridge MTLTextureDescriptor*)m_ptr setArrayLength:arrayLength];
    }

    void TextureDescriptor::SetResourceOptions(ResourceOptions resourceOptions)
    {
        Validate();
        [(__bridge MTLTextureDescriptor*)m_ptr setResourceOptions:MTLResourceOptions(resourceOptions)];
    }

    void TextureDescriptor::SetCpuCacheMode(CpuCacheMode cpuCacheMode)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_11, 9_0)
        [(__bridge MTLTextureDescriptor*)m_ptr setCpuCacheMode:MTLCPUCacheMode(cpuCacheMode)];
#endif
    }

    void TextureDescriptor::SetStorageMode(StorageMode storageMode)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_11, 9_0)
        [(__bridge MTLTextureDescriptor*)m_ptr setStorageMode:MTLStorageMode(storageMode)];
#endif
    }

    void TextureDescriptor::SetUsage(TextureUsage usage)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_11, 9_0)
        [(__bridge MTLTextureDescriptor*)m_ptr setUsage:MTLTextureUsage(usage)];
#endif
    }

    Resource Texture::GetRootResource() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_11, 8_0)
#   if MTLPP_IS_AVAILABLE(10_12, 10_0)
        return ns::Handle{ nullptr };
#   else
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLTexture>)m_ptr rootResource] };
#   endif
#else
        return ns::Handle{ nullptr };
#endif
    }

    Texture Texture::GetParentTexture() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_11, 9_0)
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLTexture>)m_ptr parentTexture] };
#else
        return ns::Handle{ nullptr };
#endif
    }

    uint32_t Texture::GetParentRelativeLevel() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_11, 9_0)
        return uint32_t([(__bridge id<MTLTexture>)m_ptr parentRelativeLevel]);
#else
        return 0;
#endif

    }

    uint32_t Texture::GetParentRelativeSlice() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_11, 9_0)
        return uint32_t([(__bridge id<MTLTexture>)m_ptr parentRelativeSlice]);
#else
        return 0;
#endif

    }

    Buffer Texture::GetBuffer() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 9_0)
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLTexture>)m_ptr buffer] };
#else
        return ns::Handle{ nullptr };
#endif

    }

    uint32_t Texture::GetBufferOffset() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 9_0)
        return uint32_t([(__bridge id<MTLTexture>)m_ptr bufferOffset]);
#else
        return 0;
#endif

    }

    uint32_t Texture::GetBufferBytesPerRow() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_12, 9_0)
        return uint32_t([(__bridge id<MTLTexture>)m_ptr bufferBytesPerRow]);
#else
        return 0;
#endif

    }

    uint32_t Texture::GetIOSurfacePlane() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE_MAC(10_11)
        return uint32_t([(__bridge id<MTLTexture>)m_ptr iosurfacePlane]);
#else
        return 0;
#endif
    }

    TextureType Texture::GetTextureType() const
    {
        Validate();
        return TextureType([(__bridge id<MTLTexture>)m_ptr textureType]);
    }

    PixelFormat Texture::GetPixelFormat() const
    {
        Validate();
        return PixelFormat([(__bridge id<MTLTexture>)m_ptr pixelFormat]);
    }

    uint32_t Texture::GetWidth() const
    {
        Validate();
        return uint32_t([(__bridge id<MTLTexture>)m_ptr width]);
    }

    uint32_t Texture::GetHeight() const
    {
        Validate();
        return uint32_t([(__bridge id<MTLTexture>)m_ptr height]);
    }

    uint32_t Texture::GetDepth() const
    {
        Validate();
        return uint32_t([(__bridge id<MTLTexture>)m_ptr depth]);
    }

    uint32_t Texture::GetMipmapLevelCount() const
    {
        Validate();
        return uint32_t([(__bridge id<MTLTexture>)m_ptr mipmapLevelCount]);
    }

    uint32_t Texture::GetSampleCount() const
    {
        Validate();
        return uint32_t([(__bridge id<MTLTexture>)m_ptr sampleCount]);
    }

    uint32_t Texture::GetArrayLength() const
    {
        Validate();
        return uint32_t([(__bridge id<MTLTexture>)m_ptr arrayLength]);
    }

    TextureUsage Texture::GetUsage() const
    {
        Validate();
        return TextureUsage([(__bridge id<MTLTexture>)m_ptr usage]);
    }

    bool Texture::IsFrameBufferOnly() const
    {
        Validate();
        return [(__bridge id<MTLTexture>)m_ptr isFramebufferOnly];
    }

    void Texture::GetBytes(void* pixelBytes, uint32_t bytesPerRow, uint32_t bytesPerImage, const Region& fromRegion, uint32_t mipmapLevel, uint32_t slice)
    {
        Validate();
        [(__bridge id<MTLTexture>)m_ptr getBytes:pixelBytes
                                     bytesPerRow:bytesPerRow
                                   bytesPerImage:bytesPerImage
                                      fromRegion:MTLRegionMake3D(fromRegion.Origin.X, fromRegion.Origin.Y, fromRegion.Origin.Z, fromRegion.Size.Width, fromRegion.Size.Height, fromRegion.Size.Depth)
                                     mipmapLevel:mipmapLevel
                                           slice:slice];
    }

    void Texture::Replace(const Region& region, uint32_t mipmapLevel, uint32_t slice, void* pixelBytes, uint32_t bytesPerRow, uint32_t bytesPerImage)
    {
        Validate();
        [(__bridge id<MTLTexture>)m_ptr replaceRegion:MTLRegionMake3D(region.Origin.X, region.Origin.Y, region.Origin.Z, region.Size.Width, region.Size.Height, region.Size.Depth)
                                          mipmapLevel:mipmapLevel
                                                slice:slice
                                            withBytes:pixelBytes
                                          bytesPerRow:bytesPerRow
                                        bytesPerImage:bytesPerImage];
    }

    void Texture::GetBytes(void* pixelBytes, uint32_t bytesPerRow, const Region& fromRegion, uint32_t mipmapLevel)
    {
        Validate();
        [(__bridge id<MTLTexture>)m_ptr getBytes:pixelBytes
                                     bytesPerRow:bytesPerRow
                                      fromRegion:MTLRegionMake3D(fromRegion.Origin.X, fromRegion.Origin.Y, fromRegion.Origin.Z, fromRegion.Size.Width, fromRegion.Size.Height, fromRegion.Size.Depth)
                                     mipmapLevel:mipmapLevel];
    }

    void Texture::Replace(const Region& region, uint32_t mipmapLevel, void* pixelBytes, uint32_t bytesPerRow)
    {
        Validate();
        [(__bridge id<MTLTexture>)m_ptr replaceRegion:MTLRegionMake3D(region.Origin.X, region.Origin.Y, region.Origin.Z, region.Size.Width, region.Size.Height, region.Size.Depth)
                                          mipmapLevel:mipmapLevel
                                            withBytes:pixelBytes
                                          bytesPerRow:bytesPerRow];
    }

    Texture Texture::NewTextureView(PixelFormat pixelFormat)
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLTexture>)m_ptr newTextureViewWithPixelFormat:MTLPixelFormat(pixelFormat)] };
    }

    Texture Texture::NewTextureView(PixelFormat pixelFormat, TextureType textureType, const ns::Range& mipmapLevelRange, const ns::Range& sliceRange)
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge id<MTLTexture>)m_ptr newTextureViewWithPixelFormat:MTLPixelFormat(pixelFormat)
                                                                                             textureType:MTLTextureType(textureType)
                                                                                                  levels:NSMakeRange(mipmapLevelRange.Location, mipmapLevelRange.Length)
                                                                                                  slices:NSMakeRange(sliceRange.Location, sliceRange.Length)] };
    }
}

//////////////////////////////////////
// FILE: vertex_descriptor.mm
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #include "vertex_descriptor.hpp"
#include <Metal/MTLVertexDescriptor.h>

namespace mtlpp
{
    VertexBufferLayoutDescriptor::VertexBufferLayoutDescriptor() :
        ns::Object(ns::Handle{ (__bridge void*)[[MTLVertexBufferLayoutDescriptor alloc] init] })
    {
    }

    uint32_t VertexBufferLayoutDescriptor::GetStride() const
    {
        Validate();
        return uint32_t([(__bridge MTLVertexBufferLayoutDescriptor*)m_ptr stride]);
    }

    uint32_t VertexBufferLayoutDescriptor::GetStepRate() const
    {
        Validate();
        return uint32_t([(__bridge MTLVertexBufferLayoutDescriptor*)m_ptr stepRate]);
    }

    VertexStepFunction VertexBufferLayoutDescriptor::GetStepFunction() const
    {
        Validate();
        return VertexStepFunction([(__bridge MTLVertexBufferLayoutDescriptor*)m_ptr stepFunction]);
    }

    void VertexBufferLayoutDescriptor::SetStride(uint32_t stride)
    {
        Validate();
        [(__bridge MTLVertexBufferLayoutDescriptor*)m_ptr setStride:stride];
    }

    void VertexBufferLayoutDescriptor::SetStepRate(uint32_t stepRate)
    {
        Validate();
        [(__bridge MTLVertexBufferLayoutDescriptor*)m_ptr setStepRate:stepRate];
    }

    void VertexBufferLayoutDescriptor::SetStepFunction(VertexStepFunction stepFunction)
    {
        Validate();
        [(__bridge MTLVertexBufferLayoutDescriptor*)m_ptr setStepFunction:MTLVertexStepFunction(stepFunction)];
    }

    VertexAttributeDescriptor::VertexAttributeDescriptor() :
        ns::Object(ns::Handle{ (__bridge void*)[[MTLVertexAttributeDescriptor alloc] init] })
    {
    }

    VertexFormat VertexAttributeDescriptor::GetFormat() const
    {
        Validate();
        return VertexFormat([(__bridge MTLVertexAttributeDescriptor*)m_ptr format]);
    }

    uint32_t VertexAttributeDescriptor::GetOffset() const
    {
        Validate();
        return uint32_t([(__bridge MTLVertexAttributeDescriptor*)m_ptr offset]);
    }

    uint32_t VertexAttributeDescriptor::GetBufferIndex() const
    {
        Validate();
        return uint32_t([(__bridge MTLVertexAttributeDescriptor*)m_ptr bufferIndex]);
    }

    void VertexAttributeDescriptor::SetFormat(VertexFormat format)
    {
        Validate();
        [(__bridge MTLVertexAttributeDescriptor*)m_ptr setFormat:MTLVertexFormat(format)];
    }

    void VertexAttributeDescriptor::SetOffset(uint32_t offset)
    {
        Validate();
        [(__bridge MTLVertexAttributeDescriptor*)m_ptr setOffset:offset];
    }

    void VertexAttributeDescriptor::SetBufferIndex(uint32_t bufferIndex)
    {
        Validate();
        [(__bridge MTLVertexAttributeDescriptor*)m_ptr setBufferIndex:bufferIndex];
    }

    VertexDescriptor::VertexDescriptor() :
        ns::Object(ns::Handle{ (__bridge void*)[[MTLVertexDescriptor alloc] init] })
    {
    }

    ns::Array<VertexBufferLayoutDescriptor> VertexDescriptor::GetLayouts() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge MTLVertexDescriptor*)m_ptr layouts] };
    }

    ns::Array<VertexAttributeDescriptor> VertexDescriptor::GetAttributes() const
    {
        Validate();
        return ns::Handle{ (__bridge void*)[(__bridge MTLVertexDescriptor*)m_ptr attributes] };
    }

    void VertexDescriptor::Reset()
    {
        Validate();
        [(__bridge MTLVertexDescriptor*)m_ptr reset];
    }
}

