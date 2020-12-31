
#ifndef WEBGPU_CPP_H_
#define WEBGPU_CPP_H_

#include "webgpu/webgpu.h"
#include "webgpu/EnumClassBitmasks.h"

namespace wgpu {

    static constexpr uint64_t kWholeSize = WGPU_WHOLE_SIZE;

    enum class AdapterType : uint32_t {
        DiscreteGPU = 0x00000000,
        IntegratedGPU = 0x00000001,
        CPU = 0x00000002,
        Unknown = 0x00000003,
    };

    enum class AddressMode : uint32_t {
        Repeat = 0x00000000,
        MirrorRepeat = 0x00000001,
        ClampToEdge = 0x00000002,
    };

    enum class BackendType : uint32_t {
        Null = 0x00000000,
        D3D11 = 0x00000001,
        D3D12 = 0x00000002,
        Metal = 0x00000003,
        Vulkan = 0x00000004,
        OpenGL = 0x00000005,
        OpenGLES = 0x00000006,
    };

    enum class BindingType : uint32_t {
        UniformBuffer = 0x00000000,
        StorageBuffer = 0x00000001,
        ReadonlyStorageBuffer = 0x00000002,
        Sampler = 0x00000003,
        ComparisonSampler = 0x00000004,
        SampledTexture = 0x00000005,
        StorageTexture = 0x00000006,
        ReadonlyStorageTexture = 0x00000007,
        WriteonlyStorageTexture = 0x00000008,
    };

    enum class BlendFactor : uint32_t {
        Zero = 0x00000000,
        One = 0x00000001,
        SrcColor = 0x00000002,
        OneMinusSrcColor = 0x00000003,
        SrcAlpha = 0x00000004,
        OneMinusSrcAlpha = 0x00000005,
        DstColor = 0x00000006,
        OneMinusDstColor = 0x00000007,
        DstAlpha = 0x00000008,
        OneMinusDstAlpha = 0x00000009,
        SrcAlphaSaturated = 0x0000000A,
        BlendColor = 0x0000000B,
        OneMinusBlendColor = 0x0000000C,
    };

    enum class BlendOperation : uint32_t {
        Add = 0x00000000,
        Subtract = 0x00000001,
        ReverseSubtract = 0x00000002,
        Min = 0x00000003,
        Max = 0x00000004,
    };

    enum class BufferMapAsyncStatus : uint32_t {
        Success = 0x00000000,
        Error = 0x00000001,
        Unknown = 0x00000002,
        DeviceLost = 0x00000003,
    };

    enum class CompareFunction : uint32_t {
        Undefined = 0x00000000,
        Never = 0x00000001,
        Less = 0x00000002,
        LessEqual = 0x00000003,
        Greater = 0x00000004,
        GreaterEqual = 0x00000005,
        Equal = 0x00000006,
        NotEqual = 0x00000007,
        Always = 0x00000008,
    };

    enum class CullMode : uint32_t {
        None = 0x00000000,
        Front = 0x00000001,
        Back = 0x00000002,
    };

    enum class ErrorFilter : uint32_t {
        None = 0x00000000,
        Validation = 0x00000001,
        OutOfMemory = 0x00000002,
    };

    enum class ErrorType : uint32_t {
        NoError = 0x00000000,
        Validation = 0x00000001,
        OutOfMemory = 0x00000002,
        Unknown = 0x00000003,
        DeviceLost = 0x00000004,
    };

    enum class FenceCompletionStatus : uint32_t {
        Success = 0x00000000,
        Error = 0x00000001,
        Unknown = 0x00000002,
        DeviceLost = 0x00000003,
    };

    enum class FilterMode : uint32_t {
        Nearest = 0x00000000,
        Linear = 0x00000001,
    };

    enum class FrontFace : uint32_t {
        CCW = 0x00000000,
        CW = 0x00000001,
    };

    enum class IndexFormat : uint32_t {
        Uint16 = 0x00000000,
        Uint32 = 0x00000001,
    };

    enum class InputStepMode : uint32_t {
        Vertex = 0x00000000,
        Instance = 0x00000001,
    };

    enum class LoadOp : uint32_t {
        Clear = 0x00000000,
        Load = 0x00000001,
    };

    enum class PresentMode : uint32_t {
        Immediate = 0x00000000,
        Mailbox = 0x00000001,
        Fifo = 0x00000002,
    };

    enum class PrimitiveTopology : uint32_t {
        PointList = 0x00000000,
        LineList = 0x00000001,
        LineStrip = 0x00000002,
        TriangleList = 0x00000003,
        TriangleStrip = 0x00000004,
    };

    enum class SType : uint32_t {
        Invalid = 0x00000000,
        SurfaceDescriptorFromMetalLayer = 0x00000001,
        SurfaceDescriptorFromWindowsHWND = 0x00000002,
        SurfaceDescriptorFromXlib = 0x00000003,
        SurfaceDescriptorFromHTMLCanvasId = 0x00000004,
        ShaderModuleSPIRVDescriptor = 0x00000005,
        ShaderModuleWGSLDescriptor = 0x00000006,
        SamplerDescriptorDummyAnisotropicFiltering = 0x00000007,
        RenderPipelineDescriptorDummyExtension = 0x00000008,
    };

    enum class StencilOperation : uint32_t {
        Keep = 0x00000000,
        Zero = 0x00000001,
        Replace = 0x00000002,
        Invert = 0x00000003,
        IncrementClamp = 0x00000004,
        DecrementClamp = 0x00000005,
        IncrementWrap = 0x00000006,
        DecrementWrap = 0x00000007,
    };

    enum class StoreOp : uint32_t {
        Store = 0x00000000,
        Clear = 0x00000001,
    };

    enum class TextureAspect : uint32_t {
        All = 0x00000000,
        StencilOnly = 0x00000001,
        DepthOnly = 0x00000002,
    };

    enum class TextureComponentType : uint32_t {
        Float = 0x00000000,
        Sint = 0x00000001,
        Uint = 0x00000002,
    };

    enum class TextureDimension : uint32_t {
        e1D = 0x00000000,
        e2D = 0x00000001,
        e3D = 0x00000002,
    };

    enum class TextureFormat : uint32_t {
        Undefined = 0x00000000,
        R8Unorm = 0x00000001,
        R8Snorm = 0x00000002,
        R8Uint = 0x00000003,
        R8Sint = 0x00000004,
        R16Uint = 0x00000005,
        R16Sint = 0x00000006,
        R16Float = 0x00000007,
        RG8Unorm = 0x00000008,
        RG8Snorm = 0x00000009,
        RG8Uint = 0x0000000A,
        RG8Sint = 0x0000000B,
        R32Float = 0x0000000C,
        R32Uint = 0x0000000D,
        R32Sint = 0x0000000E,
        RG16Uint = 0x0000000F,
        RG16Sint = 0x00000010,
        RG16Float = 0x00000011,
        RGBA8Unorm = 0x00000012,
        RGBA8UnormSrgb = 0x00000013,
        RGBA8Snorm = 0x00000014,
        RGBA8Uint = 0x00000015,
        RGBA8Sint = 0x00000016,
        BGRA8Unorm = 0x00000017,
        BGRA8UnormSrgb = 0x00000018,
        RGB10A2Unorm = 0x00000019,
        RG11B10Float = 0x0000001A,
        RG32Float = 0x0000001B,
        RG32Uint = 0x0000001C,
        RG32Sint = 0x0000001D,
        RGBA16Uint = 0x0000001E,
        RGBA16Sint = 0x0000001F,
        RGBA16Float = 0x00000020,
        RGBA32Float = 0x00000021,
        RGBA32Uint = 0x00000022,
        RGBA32Sint = 0x00000023,
        Depth32Float = 0x00000024,
        Depth24Plus = 0x00000025,
        Depth24PlusStencil8 = 0x00000026,
        BC1RGBAUnorm = 0x00000027,
        BC1RGBAUnormSrgb = 0x00000028,
        BC2RGBAUnorm = 0x00000029,
        BC2RGBAUnormSrgb = 0x0000002A,
        BC3RGBAUnorm = 0x0000002B,
        BC3RGBAUnormSrgb = 0x0000002C,
        BC4RUnorm = 0x0000002D,
        BC4RSnorm = 0x0000002E,
        BC5RGUnorm = 0x0000002F,
        BC5RGSnorm = 0x00000030,
        BC6HRGBUfloat = 0x00000031,
        BC6HRGBSfloat = 0x00000032,
        BC7RGBAUnorm = 0x00000033,
        BC7RGBAUnormSrgb = 0x00000034,
    };

    enum class TextureViewDimension : uint32_t {
        Undefined = 0x00000000,
        e1D = 0x00000001,
        e2D = 0x00000002,
        e2DArray = 0x00000003,
        Cube = 0x00000004,
        CubeArray = 0x00000005,
        e3D = 0x00000006,
    };

    enum class VertexFormat : uint32_t {
        UChar2 = 0x00000000,
        UChar4 = 0x00000001,
        Char2 = 0x00000002,
        Char4 = 0x00000003,
        UChar2Norm = 0x00000004,
        UChar4Norm = 0x00000005,
        Char2Norm = 0x00000006,
        Char4Norm = 0x00000007,
        UShort2 = 0x00000008,
        UShort4 = 0x00000009,
        Short2 = 0x0000000A,
        Short4 = 0x0000000B,
        UShort2Norm = 0x0000000C,
        UShort4Norm = 0x0000000D,
        Short2Norm = 0x0000000E,
        Short4Norm = 0x0000000F,
        Half2 = 0x00000010,
        Half4 = 0x00000011,
        Float = 0x00000012,
        Float2 = 0x00000013,
        Float3 = 0x00000014,
        Float4 = 0x00000015,
        UInt = 0x00000016,
        UInt2 = 0x00000017,
        UInt3 = 0x00000018,
        UInt4 = 0x00000019,
        Int = 0x0000001A,
        Int2 = 0x0000001B,
        Int3 = 0x0000001C,
        Int4 = 0x0000001D,
    };


    enum class BufferUsage : uint32_t {
        None = 0x00000000,
        MapRead = 0x00000001,
        MapWrite = 0x00000002,
        CopySrc = 0x00000004,
        CopyDst = 0x00000008,
        Index = 0x00000010,
        Vertex = 0x00000020,
        Uniform = 0x00000040,
        Storage = 0x00000080,
        Indirect = 0x00000100,
    };

    enum class ColorWriteMask : uint32_t {
        None = 0x00000000,
        Red = 0x00000001,
        Green = 0x00000002,
        Blue = 0x00000004,
        Alpha = 0x00000008,
        All = 0x0000000F,
    };

    enum class ShaderStage : uint32_t {
        None = 0x00000000,
        Vertex = 0x00000001,
        Fragment = 0x00000002,
        Compute = 0x00000004,
    };

    enum class TextureUsage : uint32_t {
        None = 0x00000000,
        CopySrc = 0x00000001,
        CopyDst = 0x00000002,
        Sampled = 0x00000004,
        Storage = 0x00000008,
        OutputAttachment = 0x00000010,
        Present = 0x00000020,
    };


    template<>
    struct IsDawnBitmask<BufferUsage> {
        static constexpr bool enable = true;
    };

    template<>
    struct IsDawnBitmask<ColorWriteMask> {
        static constexpr bool enable = true;
    };

    template<>
    struct IsDawnBitmask<ShaderStage> {
        static constexpr bool enable = true;
    };

    template<>
    struct IsDawnBitmask<TextureUsage> {
        static constexpr bool enable = true;
    };


    using Proc = WGPUProc;
    using BufferMapReadCallback = WGPUBufferMapReadCallback;
    using BufferMapWriteCallback = WGPUBufferMapWriteCallback;
    using DeviceLostCallback = WGPUDeviceLostCallback;
    using ErrorCallback = WGPUErrorCallback;
    using FenceOnCompletionCallback = WGPUFenceOnCompletionCallback;

    class BindGroup;
    class BindGroupLayout;
    class Buffer;
    class CommandBuffer;
    class CommandEncoder;
    class ComputePassEncoder;
    class ComputePipeline;
    class Device;
    class Fence;
    class Instance;
    class PipelineLayout;
    class Queue;
    class RenderBundle;
    class RenderBundleEncoder;
    class RenderPassEncoder;
    class RenderPipeline;
    class Sampler;
    class ShaderModule;
    class Surface;
    class SwapChain;
    class Texture;
    class TextureView;

    struct AdapterProperties;
    struct BindGroupEntry;
    struct BindGroupLayoutEntry;
    struct BlendDescriptor;
    struct BufferCopyView;
    struct BufferDescriptor;
    struct Color;
    struct CommandBufferDescriptor;
    struct CommandEncoderDescriptor;
    struct ComputePassDescriptor;
    struct CreateBufferMappedResult;
    struct DeviceProperties;
    struct Extent3D;
    struct FenceDescriptor;
    struct InstanceDescriptor;
    struct Origin3D;
    struct PipelineLayoutDescriptor;
    struct ProgrammableStageDescriptor;
    struct RasterizationStateDescriptor;
    struct RenderBundleDescriptor;
    struct RenderBundleEncoderDescriptor;
    struct RenderPassDepthStencilAttachmentDescriptor;
    struct SamplerDescriptor;
    struct SamplerDescriptorDummyAnisotropicFiltering;
    struct ShaderModuleDescriptor;
    struct ShaderModuleSPIRVDescriptor;
    struct ShaderModuleWGSLDescriptor;
    struct StencilStateFaceDescriptor;
    struct SurfaceDescriptor;
    struct SurfaceDescriptorFromHTMLCanvasId;
    struct SurfaceDescriptorFromMetalLayer;
    struct SurfaceDescriptorFromWindowsHWND;
    struct SurfaceDescriptorFromXlib;
    struct SwapChainDescriptor;
    struct TextureViewDescriptor;
    struct VertexAttributeDescriptor;
    struct BindGroupDescriptor;
    struct BindGroupLayoutDescriptor;
    struct ColorStateDescriptor;
    struct ComputePipelineDescriptor;
    struct DepthStencilStateDescriptor;
    struct RenderPassColorAttachmentDescriptor;
    struct RenderPipelineDescriptorDummyExtension;
    struct TextureCopyView;
    struct TextureDescriptor;
    struct VertexBufferLayoutDescriptor;
    struct RenderPassDescriptor;
    struct VertexStateDescriptor;
    struct RenderPipelineDescriptor;

    template<typename Derived, typename CType>
    class ObjectBase {
      public:
        ObjectBase() = default;
        ObjectBase(CType handle): mHandle(handle) {
            if (mHandle) Derived::WGPUReference(mHandle);
        }
        ~ObjectBase() {
            if (mHandle) Derived::WGPURelease(mHandle);
        }

        ObjectBase(ObjectBase const& other)
            : ObjectBase(other.Get()) {
        }
        Derived& operator=(ObjectBase const& other) {
            if (&other != this) {
                if (mHandle) Derived::WGPURelease(mHandle);
                mHandle = other.mHandle;
                if (mHandle) Derived::WGPUReference(mHandle);
            }

            return static_cast<Derived&>(*this);
        }

        ObjectBase(ObjectBase&& other) {
            mHandle = other.mHandle;
            other.mHandle = 0;
        }
        Derived& operator=(ObjectBase&& other) {
            if (&other != this) {
                if (mHandle) Derived::WGPURelease(mHandle);
                mHandle = other.mHandle;
                other.mHandle = 0;
            }

            return static_cast<Derived&>(*this);
        }

        ObjectBase(std::nullptr_t) {}
        Derived& operator=(std::nullptr_t) {
            if (mHandle != nullptr) {
                Derived::WGPURelease(mHandle);
                mHandle = nullptr;
            }
            return static_cast<Derived&>(*this);
        }

        bool operator==(std::nullptr_t) const {
            return mHandle == nullptr;
        }
        bool operator!=(std::nullptr_t) const {
            return mHandle != nullptr;
        }

        explicit operator bool() const {
            return mHandle != nullptr;
        }
        CType Get() const {
            return mHandle;
        }
        CType Release() {
            CType result = mHandle;
            mHandle = 0;
            return result;
        }
        static Derived Acquire(CType handle) {
            Derived result;
            result.mHandle = handle;
            return result;
        }

      protected:
        CType mHandle = nullptr;
    };



    class BindGroup : public ObjectBase<BindGroup, WGPUBindGroup> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;


      private:
        friend ObjectBase<BindGroup, WGPUBindGroup>;
        static void WGPUReference(WGPUBindGroup handle);
        static void WGPURelease(WGPUBindGroup handle);
    };

    class BindGroupLayout : public ObjectBase<BindGroupLayout, WGPUBindGroupLayout> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;


      private:
        friend ObjectBase<BindGroupLayout, WGPUBindGroupLayout>;
        static void WGPUReference(WGPUBindGroupLayout handle);
        static void WGPURelease(WGPUBindGroupLayout handle);
    };

    class Buffer : public ObjectBase<Buffer, WGPUBuffer> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        void Destroy() const;
        void MapReadAsync(BufferMapReadCallback callback, void * userdata) const;
        void MapWriteAsync(BufferMapWriteCallback callback, void * userdata) const;
        void SetSubData(uint64_t start, uint64_t count, void const * data) const;
        void Unmap() const;

      private:
        friend ObjectBase<Buffer, WGPUBuffer>;
        static void WGPUReference(WGPUBuffer handle);
        static void WGPURelease(WGPUBuffer handle);
    };

    class CommandBuffer : public ObjectBase<CommandBuffer, WGPUCommandBuffer> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;


      private:
        friend ObjectBase<CommandBuffer, WGPUCommandBuffer>;
        static void WGPUReference(WGPUCommandBuffer handle);
        static void WGPURelease(WGPUCommandBuffer handle);
    };

    class CommandEncoder : public ObjectBase<CommandEncoder, WGPUCommandEncoder> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        ComputePassEncoder BeginComputePass(ComputePassDescriptor const * descriptor = nullptr) const;
        RenderPassEncoder BeginRenderPass(RenderPassDescriptor const * descriptor) const;
        void CopyBufferToBuffer(Buffer const& source, uint64_t sourceOffset, Buffer const& destination, uint64_t destinationOffset, uint64_t size) const;
        void CopyBufferToTexture(BufferCopyView const * source, TextureCopyView const * destination, Extent3D const * copySize) const;
        void CopyTextureToBuffer(TextureCopyView const * source, BufferCopyView const * destination, Extent3D const * copySize) const;
        void CopyTextureToTexture(TextureCopyView const * source, TextureCopyView const * destination, Extent3D const * copySize) const;
        CommandBuffer Finish(CommandBufferDescriptor const * descriptor = nullptr) const;
        void InsertDebugMarker(char const * groupLabel) const;
        void PopDebugGroup() const;
        void PushDebugGroup(char const * groupLabel) const;

      private:
        friend ObjectBase<CommandEncoder, WGPUCommandEncoder>;
        static void WGPUReference(WGPUCommandEncoder handle);
        static void WGPURelease(WGPUCommandEncoder handle);
    };

    class ComputePassEncoder : public ObjectBase<ComputePassEncoder, WGPUComputePassEncoder> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        void Dispatch(uint32_t x, uint32_t y = 1, uint32_t z = 1) const;
        void DispatchIndirect(Buffer const& indirectBuffer, uint64_t indirectOffset) const;
        void EndPass() const;
        void InsertDebugMarker(char const * groupLabel) const;
        void PopDebugGroup() const;
        void PushDebugGroup(char const * groupLabel) const;
        void SetBindGroup(uint32_t groupIndex, BindGroup const& group, uint32_t dynamicOffsetCount = 0, uint32_t const * dynamicOffsets = nullptr) const;
        void SetPipeline(ComputePipeline const& pipeline) const;

      private:
        friend ObjectBase<ComputePassEncoder, WGPUComputePassEncoder>;
        static void WGPUReference(WGPUComputePassEncoder handle);
        static void WGPURelease(WGPUComputePassEncoder handle);
    };

    class ComputePipeline : public ObjectBase<ComputePipeline, WGPUComputePipeline> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        BindGroupLayout GetBindGroupLayout(uint32_t groupIndex) const;

      private:
        friend ObjectBase<ComputePipeline, WGPUComputePipeline>;
        static void WGPUReference(WGPUComputePipeline handle);
        static void WGPURelease(WGPUComputePipeline handle);
    };

    class Device : public ObjectBase<Device, WGPUDevice> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        BindGroup CreateBindGroup(BindGroupDescriptor const * descriptor) const;
        BindGroupLayout CreateBindGroupLayout(BindGroupLayoutDescriptor const * descriptor) const;
        Buffer CreateBuffer(BufferDescriptor const * descriptor) const;
        CreateBufferMappedResult CreateBufferMapped(BufferDescriptor const * descriptor) const;
        CommandEncoder CreateCommandEncoder(CommandEncoderDescriptor const * descriptor = nullptr) const;
        ComputePipeline CreateComputePipeline(ComputePipelineDescriptor const * descriptor) const;
        PipelineLayout CreatePipelineLayout(PipelineLayoutDescriptor const * descriptor) const;
        Queue CreateQueue() const;
        RenderBundleEncoder CreateRenderBundleEncoder(RenderBundleEncoderDescriptor const * descriptor) const;
        RenderPipeline CreateRenderPipeline(RenderPipelineDescriptor const * descriptor) const;
        Sampler CreateSampler(SamplerDescriptor const * descriptor) const;
        ShaderModule CreateShaderModule(ShaderModuleDescriptor const * descriptor) const;
        SwapChain CreateSwapChain(Surface const& surface, SwapChainDescriptor const * descriptor) const;
        Texture CreateTexture(TextureDescriptor const * descriptor) const;
        Queue GetDefaultQueue() const;
        void InjectError(ErrorType type, char const * message) const;
        void LoseForTesting() const;
        bool PopErrorScope(ErrorCallback callback, void * userdata) const;
        void PushErrorScope(ErrorFilter filter) const;
        void SetDeviceLostCallback(DeviceLostCallback callback, void * userdata) const;
        void SetUncapturedErrorCallback(ErrorCallback callback, void * userdata) const;
        void Tick() const;

      private:
        friend ObjectBase<Device, WGPUDevice>;
        static void WGPUReference(WGPUDevice handle);
        static void WGPURelease(WGPUDevice handle);
    };

    class Fence : public ObjectBase<Fence, WGPUFence> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        uint64_t GetCompletedValue() const;
        void OnCompletion(uint64_t value, FenceOnCompletionCallback callback, void * userdata) const;

      private:
        friend ObjectBase<Fence, WGPUFence>;
        static void WGPUReference(WGPUFence handle);
        static void WGPURelease(WGPUFence handle);
    };

    class Instance : public ObjectBase<Instance, WGPUInstance> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        Surface CreateSurface(SurfaceDescriptor const * descriptor) const;

      private:
        friend ObjectBase<Instance, WGPUInstance>;
        static void WGPUReference(WGPUInstance handle);
        static void WGPURelease(WGPUInstance handle);
    };

    class PipelineLayout : public ObjectBase<PipelineLayout, WGPUPipelineLayout> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;


      private:
        friend ObjectBase<PipelineLayout, WGPUPipelineLayout>;
        static void WGPUReference(WGPUPipelineLayout handle);
        static void WGPURelease(WGPUPipelineLayout handle);
    };

    class Queue : public ObjectBase<Queue, WGPUQueue> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        Fence CreateFence(FenceDescriptor const * descriptor) const;
        void Signal(Fence const& fence, uint64_t signalValue) const;
        void Submit(uint32_t commandCount, CommandBuffer const * commands) const;

      private:
        friend ObjectBase<Queue, WGPUQueue>;
        static void WGPUReference(WGPUQueue handle);
        static void WGPURelease(WGPUQueue handle);
    };

    class RenderBundle : public ObjectBase<RenderBundle, WGPURenderBundle> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;


      private:
        friend ObjectBase<RenderBundle, WGPURenderBundle>;
        static void WGPUReference(WGPURenderBundle handle);
        static void WGPURelease(WGPURenderBundle handle);
    };

    class RenderBundleEncoder : public ObjectBase<RenderBundleEncoder, WGPURenderBundleEncoder> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        void Draw(uint32_t vertexCount, uint32_t instanceCount = 1, uint32_t firstVertex = 0, uint32_t firstInstance = 0) const;
        void DrawIndexed(uint32_t indexCount, uint32_t instanceCount = 1, uint32_t firstIndex = 0, int32_t baseVertex = 0, uint32_t firstInstance = 0) const;
        void DrawIndexedIndirect(Buffer const& indirectBuffer, uint64_t indirectOffset) const;
        void DrawIndirect(Buffer const& indirectBuffer, uint64_t indirectOffset) const;
        RenderBundle Finish(RenderBundleDescriptor const * descriptor = nullptr) const;
        void InsertDebugMarker(char const * groupLabel) const;
        void PopDebugGroup() const;
        void PushDebugGroup(char const * groupLabel) const;
        void SetBindGroup(uint32_t groupIndex, BindGroup const& group, uint32_t dynamicOffsetCount = 0, uint32_t const * dynamicOffsets = nullptr) const;
        void SetIndexBuffer(Buffer const& buffer, uint64_t offset = 0, uint64_t size = 0) const;
        void SetPipeline(RenderPipeline const& pipeline) const;
        void SetVertexBuffer(uint32_t slot, Buffer const& buffer, uint64_t offset = 0, uint64_t size = 0) const;

      private:
        friend ObjectBase<RenderBundleEncoder, WGPURenderBundleEncoder>;
        static void WGPUReference(WGPURenderBundleEncoder handle);
        static void WGPURelease(WGPURenderBundleEncoder handle);
    };

    class RenderPassEncoder : public ObjectBase<RenderPassEncoder, WGPURenderPassEncoder> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        void Draw(uint32_t vertexCount, uint32_t instanceCount = 1, uint32_t firstVertex = 0, uint32_t firstInstance = 0) const;
        void DrawIndexed(uint32_t indexCount, uint32_t instanceCount = 1, uint32_t firstIndex = 0, int32_t baseVertex = 0, uint32_t firstInstance = 0) const;
        void DrawIndexedIndirect(Buffer const& indirectBuffer, uint64_t indirectOffset) const;
        void DrawIndirect(Buffer const& indirectBuffer, uint64_t indirectOffset) const;
        void EndPass() const;
        void ExecuteBundles(uint32_t bundlesCount, RenderBundle const * bundles) const;
        void InsertDebugMarker(char const * groupLabel) const;
        void PopDebugGroup() const;
        void PushDebugGroup(char const * groupLabel) const;
        void SetBindGroup(uint32_t groupIndex, BindGroup const& group, uint32_t dynamicOffsetCount = 0, uint32_t const * dynamicOffsets = nullptr) const;
        void SetBlendColor(Color const * color) const;
        void SetIndexBuffer(Buffer const& buffer, uint64_t offset = 0, uint64_t size = 0) const;
        void SetPipeline(RenderPipeline const& pipeline) const;
        void SetScissorRect(uint32_t x, uint32_t y, uint32_t width, uint32_t height) const;
        void SetStencilReference(uint32_t reference) const;
        void SetVertexBuffer(uint32_t slot, Buffer const& buffer, uint64_t offset = 0, uint64_t size = 0) const;
        void SetViewport(float x, float y, float width, float height, float minDepth, float maxDepth) const;

      private:
        friend ObjectBase<RenderPassEncoder, WGPURenderPassEncoder>;
        static void WGPUReference(WGPURenderPassEncoder handle);
        static void WGPURelease(WGPURenderPassEncoder handle);
    };

    class RenderPipeline : public ObjectBase<RenderPipeline, WGPURenderPipeline> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        BindGroupLayout GetBindGroupLayout(uint32_t groupIndex) const;

      private:
        friend ObjectBase<RenderPipeline, WGPURenderPipeline>;
        static void WGPUReference(WGPURenderPipeline handle);
        static void WGPURelease(WGPURenderPipeline handle);
    };

    class Sampler : public ObjectBase<Sampler, WGPUSampler> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;


      private:
        friend ObjectBase<Sampler, WGPUSampler>;
        static void WGPUReference(WGPUSampler handle);
        static void WGPURelease(WGPUSampler handle);
    };

    class ShaderModule : public ObjectBase<ShaderModule, WGPUShaderModule> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;


      private:
        friend ObjectBase<ShaderModule, WGPUShaderModule>;
        static void WGPUReference(WGPUShaderModule handle);
        static void WGPURelease(WGPUShaderModule handle);
    };

    class Surface : public ObjectBase<Surface, WGPUSurface> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;


      private:
        friend ObjectBase<Surface, WGPUSurface>;
        static void WGPUReference(WGPUSurface handle);
        static void WGPURelease(WGPUSurface handle);
    };

    class SwapChain : public ObjectBase<SwapChain, WGPUSwapChain> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        void Configure(TextureFormat format, TextureUsage allowedUsage, uint32_t width, uint32_t height) const;
        TextureView GetCurrentTextureView() const;
        void Present() const;

      private:
        friend ObjectBase<SwapChain, WGPUSwapChain>;
        static void WGPUReference(WGPUSwapChain handle);
        static void WGPURelease(WGPUSwapChain handle);
    };

    class Texture : public ObjectBase<Texture, WGPUTexture> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        TextureView CreateView(TextureViewDescriptor const * descriptor = nullptr) const;
        void Destroy() const;

      private:
        friend ObjectBase<Texture, WGPUTexture>;
        static void WGPUReference(WGPUTexture handle);
        static void WGPURelease(WGPUTexture handle);
    };

    class TextureView : public ObjectBase<TextureView, WGPUTextureView> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;


      private:
        friend ObjectBase<TextureView, WGPUTextureView>;
        static void WGPUReference(WGPUTextureView handle);
        static void WGPURelease(WGPUTextureView handle);
    };


    Instance CreateInstance(InstanceDescriptor const * descriptor = nullptr);
    Proc GetProcAddress(Device const& device, const char* procName);

    struct ChainedStruct {
        ChainedStruct const * nextInChain = nullptr;
        SType sType = SType::Invalid;
    };

    struct AdapterProperties {
        ChainedStruct const * nextInChain = nullptr;
        uint32_t deviceID;
        uint32_t vendorID;
        char const * name;
        AdapterType adapterType;
        BackendType backendType;
    };

    struct BindGroupEntry {
        uint32_t binding;
        Buffer buffer;
        uint64_t offset = 0;
        uint64_t size;
        Sampler sampler;
        TextureView textureView;
    };

    struct BindGroupLayoutEntry {
        uint32_t binding;
        ShaderStage visibility;
        BindingType type;
        bool hasDynamicOffset = false;
        bool multisampled = false;
        TextureViewDimension textureDimension = TextureViewDimension::Undefined;
        TextureViewDimension viewDimension = TextureViewDimension::Undefined;
        TextureComponentType textureComponentType = TextureComponentType::Float;
        TextureFormat storageTextureFormat = TextureFormat::Undefined;
    };

    struct BlendDescriptor {
        BlendOperation operation = BlendOperation::Add;
        BlendFactor srcFactor = BlendFactor::One;
        BlendFactor dstFactor = BlendFactor::Zero;
    };

    struct BufferCopyView {
        ChainedStruct const * nextInChain = nullptr;
        Buffer buffer;
        uint64_t offset = 0;
        uint32_t rowPitch = 0;
        uint32_t imageHeight = 0;
        uint32_t bytesPerRow = 0;
        uint32_t rowsPerImage = 0;
    };

    struct BufferDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        BufferUsage usage;
        uint64_t size;
    };

    struct Color {
        float r;
        float g;
        float b;
        float a;
    };

    struct CommandBufferDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
    };

    struct CommandEncoderDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
    };

    struct ComputePassDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
    };

    struct CreateBufferMappedResult {
        Buffer buffer;
        uint64_t dataLength;
        void * data;
    };

    struct DeviceProperties {
        bool textureCompressionBC = false;
    };

    struct Extent3D {
        uint32_t width;
        uint32_t height;
        uint32_t depth;
    };

    struct FenceDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        uint64_t initialValue = 0;
    };

    struct InstanceDescriptor {
        ChainedStruct const * nextInChain = nullptr;
    };

    struct Origin3D {
        uint32_t x = 0;
        uint32_t y = 0;
        uint32_t z = 0;
    };

    struct PipelineLayoutDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        uint32_t bindGroupLayoutCount;
        BindGroupLayout const * bindGroupLayouts;
    };

    struct ProgrammableStageDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        ShaderModule module;
        char const * entryPoint;
    };

    struct RasterizationStateDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        FrontFace frontFace = FrontFace::CCW;
        CullMode cullMode = CullMode::None;
        int32_t depthBias = 0;
        float depthBiasSlopeScale = 0.0f;
        float depthBiasClamp = 0.0f;
    };

    struct RenderBundleDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
    };

    struct RenderBundleEncoderDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        uint32_t colorFormatsCount;
        TextureFormat const * colorFormats;
        TextureFormat depthStencilFormat = TextureFormat::Undefined;
        uint32_t sampleCount = 1;
    };

    struct RenderPassDepthStencilAttachmentDescriptor {
        TextureView attachment;
        LoadOp depthLoadOp;
        StoreOp depthStoreOp;
        float clearDepth;
        LoadOp stencilLoadOp;
        StoreOp stencilStoreOp;
        uint32_t clearStencil = 0;
    };

    struct SamplerDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        AddressMode addressModeU = AddressMode::ClampToEdge;
        AddressMode addressModeV = AddressMode::ClampToEdge;
        AddressMode addressModeW = AddressMode::ClampToEdge;
        FilterMode magFilter = FilterMode::Nearest;
        FilterMode minFilter = FilterMode::Nearest;
        FilterMode mipmapFilter = FilterMode::Nearest;
        float lodMinClamp = 0.0f;
        float lodMaxClamp = 1000.0f;
        CompareFunction compare = CompareFunction::Undefined;
    };

    struct SamplerDescriptorDummyAnisotropicFiltering : ChainedStruct {
        SamplerDescriptorDummyAnisotropicFiltering() {
            sType = SType::SamplerDescriptorDummyAnisotropicFiltering;
        }
        alignas(ChainedStruct) float maxAnisotropy;
    };

    struct ShaderModuleDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        uint32_t codeSize = 0;
        uint32_t const * code = nullptr;
    };

    struct ShaderModuleSPIRVDescriptor : ChainedStruct {
        ShaderModuleSPIRVDescriptor() {
            sType = SType::ShaderModuleSPIRVDescriptor;
        }
        alignas(ChainedStruct) uint32_t codeSize;
        uint32_t const * code;
    };

    struct ShaderModuleWGSLDescriptor : ChainedStruct {
        ShaderModuleWGSLDescriptor() {
            sType = SType::ShaderModuleWGSLDescriptor;
        }
        alignas(ChainedStruct) char const * source;
    };

    struct StencilStateFaceDescriptor {
        CompareFunction compare = CompareFunction::Always;
        StencilOperation failOp = StencilOperation::Keep;
        StencilOperation depthFailOp = StencilOperation::Keep;
        StencilOperation passOp = StencilOperation::Keep;
    };

    struct SurfaceDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
    };

    struct SurfaceDescriptorFromHTMLCanvasId : ChainedStruct {
        SurfaceDescriptorFromHTMLCanvasId() {
            sType = SType::SurfaceDescriptorFromHTMLCanvasId;
        }
        alignas(ChainedStruct) char const * id;
    };

    struct SurfaceDescriptorFromMetalLayer : ChainedStruct {
        SurfaceDescriptorFromMetalLayer() {
            sType = SType::SurfaceDescriptorFromMetalLayer;
        }
        alignas(ChainedStruct) void * layer;
    };

    struct SurfaceDescriptorFromWindowsHWND : ChainedStruct {
        SurfaceDescriptorFromWindowsHWND() {
            sType = SType::SurfaceDescriptorFromWindowsHWND;
        }
        alignas(ChainedStruct) void * hinstance;
        void * hwnd;
    };

    struct SurfaceDescriptorFromXlib : ChainedStruct {
        SurfaceDescriptorFromXlib() {
            sType = SType::SurfaceDescriptorFromXlib;
        }
        alignas(ChainedStruct) void * display;
        uint32_t window;
    };

    struct SwapChainDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        TextureUsage usage;
        TextureFormat format;
        uint32_t width;
        uint32_t height;
        PresentMode presentMode;
        uint64_t implementation = 0;
    };

    struct TextureViewDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        TextureFormat format = TextureFormat::Undefined;
        TextureViewDimension dimension = TextureViewDimension::Undefined;
        uint32_t baseMipLevel = 0;
        uint32_t mipLevelCount = 0;
        uint32_t baseArrayLayer = 0;
        uint32_t arrayLayerCount = 0;
        TextureAspect aspect = TextureAspect::All;
    };

    struct VertexAttributeDescriptor {
        VertexFormat format;
        uint64_t offset;
        uint32_t shaderLocation;
    };

    struct BindGroupDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        BindGroupLayout layout;
        uint32_t bindingCount = 0;
        BindGroupEntry const * bindings;
        uint32_t entryCount = 0;
        BindGroupEntry const * entries;
    };

    struct BindGroupLayoutDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        uint32_t bindingCount = 0;
        BindGroupLayoutEntry const * bindings;
        uint32_t entryCount = 0;
        BindGroupLayoutEntry const * entries;
    };

    struct ColorStateDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        TextureFormat format;
        BlendDescriptor alphaBlend;
        BlendDescriptor colorBlend;
        ColorWriteMask writeMask = ColorWriteMask::All;
    };

    struct ComputePipelineDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        PipelineLayout layout;
        ProgrammableStageDescriptor computeStage;
    };

    struct DepthStencilStateDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        TextureFormat format;
        bool depthWriteEnabled = false;
        CompareFunction depthCompare = CompareFunction::Always;
        StencilStateFaceDescriptor stencilFront;
        StencilStateFaceDescriptor stencilBack;
        uint32_t stencilReadMask = 0xFFFFFFFF;
        uint32_t stencilWriteMask = 0xFFFFFFFF;
    };

    struct RenderPassColorAttachmentDescriptor {
        TextureView attachment;
        TextureView resolveTarget;
        LoadOp loadOp;
        StoreOp storeOp;
        Color clearColor;
    };

    struct RenderPipelineDescriptorDummyExtension : ChainedStruct {
        RenderPipelineDescriptorDummyExtension() {
            sType = SType::RenderPipelineDescriptorDummyExtension;
        }
        alignas(ChainedStruct) ProgrammableStageDescriptor dummyStage;
    };

    struct TextureCopyView {
        ChainedStruct const * nextInChain = nullptr;
        Texture texture;
        uint32_t mipLevel = 0;
        uint32_t arrayLayer = 0;
        Origin3D origin;
    };

    struct TextureDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        TextureUsage usage;
        TextureDimension dimension = TextureDimension::e2D;
        Extent3D size;
        uint32_t arrayLayerCount = 1;
        TextureFormat format;
        uint32_t mipLevelCount = 1;
        uint32_t sampleCount = 1;
    };

    struct VertexBufferLayoutDescriptor {
        uint64_t arrayStride;
        InputStepMode stepMode = InputStepMode::Vertex;
        uint32_t attributeCount;
        VertexAttributeDescriptor const * attributes;
    };

    struct RenderPassDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        uint32_t colorAttachmentCount;
        RenderPassColorAttachmentDescriptor const * colorAttachments;
        RenderPassDepthStencilAttachmentDescriptor const * depthStencilAttachment = nullptr;
    };

    struct VertexStateDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        IndexFormat indexFormat = IndexFormat::Uint32;
        uint32_t vertexBufferCount = 0;
        VertexBufferLayoutDescriptor const * vertexBuffers;
    };

    struct RenderPipelineDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        PipelineLayout layout;
        ProgrammableStageDescriptor vertexStage;
        ProgrammableStageDescriptor const * fragmentStage = nullptr;
        VertexStateDescriptor const * vertexState = nullptr;
        PrimitiveTopology primitiveTopology;
        RasterizationStateDescriptor const * rasterizationState = nullptr;
        uint32_t sampleCount = 1;
        DepthStencilStateDescriptor const * depthStencilState = nullptr;
        uint32_t colorStateCount;
        ColorStateDescriptor const * colorStates;
        uint32_t sampleMask = 0xFFFFFFFF;
        bool alphaToCoverageEnabled = false;
    };


    // TODO(dawn:22): Remove this once users use the "Entry" version.
    using BindGroupBinding = BindGroupEntry;
    using BindGroupLayoutBinding = BindGroupLayoutEntry;

}  // namespace wgpu

#endif // WEBGPU_CPP_H_
