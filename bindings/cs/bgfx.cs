using System;
using System.Runtime.InteropServices;
using System.Security;

internal struct bgfx
{
	[Flags]
	public enum StateFlags : ulong
	{
		WriteR                 = 0x0000000000000001,
		WriteG                 = 0x0000000000000002,
		WriteB                 = 0x0000000000000004,
		WriteA                 = 0x0000000000000008,
		WriteZ                 = 0x0000004000000000,
		WriteRgb               = 0x0000000000000007,
		WriteMask              = 0x000000400000000f,
		DepthTestLess          = 0x0000000000000010,
		DepthTestLequal        = 0x0000000000000020,
		DepthTestEqual         = 0x0000000000000030,
		DepthTestGequal        = 0x0000000000000040,
		DepthTestGreater       = 0x0000000000000050,
		DepthTestNotequal      = 0x0000000000000060,
		DepthTestNever         = 0x0000000000000070,
		DepthTestAlways        = 0x0000000000000080,
		DepthTestShift         = 4,
		DepthTestMask          = 0x00000000000000f0,
		BlendZero              = 0x0000000000001000,
		BlendOne               = 0x0000000000002000,
		BlendSrcColor          = 0x0000000000003000,
		BlendInvSrcColor       = 0x0000000000004000,
		BlendSrcAlpha          = 0x0000000000005000,
		BlendInvSrcAlpha       = 0x0000000000006000,
		BlendDstAlpha          = 0x0000000000007000,
		BlendInvDstAlpha       = 0x0000000000008000,
		BlendDstColor          = 0x0000000000009000,
		BlendInvDstColor       = 0x000000000000a000,
		BlendSrcAlphaSat       = 0x000000000000b000,
		BlendFactor            = 0x000000000000c000,
		BlendInvFactor         = 0x000000000000d000,
		BlendShift             = 12,
		BlendMask              = 0x000000000ffff000,
		BlendEquationAdd       = 0x0000000000000000,
		BlendEquationSub       = 0x0000000010000000,
		BlendEquationRevsub    = 0x0000000020000000,
		BlendEquationMin       = 0x0000000030000000,
		BlendEquationMax       = 0x0000000040000000,
		BlendEquationShift     = 28,
		BlendEquationMask      = 0x00000003f0000000,
		CullCw                 = 0x0000001000000000,
		CullCcw                = 0x0000002000000000,
		CullShift              = 36,
		CullMask               = 0x0000003000000000,
		AlphaRefShift          = 40,
		AlphaRefMask           = 0x0000ff0000000000,
		PtTristrip             = 0x0001000000000000,
		PtLines                = 0x0002000000000000,
		PtLinestrip            = 0x0003000000000000,
		PtPoints               = 0x0004000000000000,
		PtShift                = 48,
		PtMask                 = 0x0007000000000000,
		PointSizeShift         = 52,
		PointSizeMask          = 0x00f0000000000000,
		Msaa                   = 0x0100000000000000,
		Lineaa                 = 0x0200000000000000,
		ConservativeRaster     = 0x0400000000000000,
		None                   = 0x0000000000000000,
		BlendIndependent       = 0x0000000400000000,
		BlendAlphaToCoverage   = 0x0000000800000000,
		Default                = 0x010000500000001f,
		Mask                   = 0xffffffffffffffff,
		ReservedShift          = 61,
		ReservedMask           = 0xe000000000000000,
	}
	
	[Flags]
	public enum StencilFlags : uint
	{
		FuncRefShift           = 0,
		FuncRefMask            = 0x000000ff,
		FuncRmaskShift         = 8,
		FuncRmaskMask          = 0x0000ff00,
		None                   = 0x00000000,
		Mask                   = 0xffffffff,
		Default                = 0x00000000,
		TestLess               = 0x00010000,
		TestLequal             = 0x00020000,
		TestEqual              = 0x00030000,
		TestGequal             = 0x00040000,
		TestGreater            = 0x00050000,
		TestNotequal           = 0x00060000,
		TestNever              = 0x00070000,
		TestAlways             = 0x00080000,
		TestShift              = 16,
		TestMask               = 0x000f0000,
		OpFailSZero            = 0x00000000,
		OpFailSKeep            = 0x00100000,
		OpFailSReplace         = 0x00200000,
		OpFailSIncr            = 0x00300000,
		OpFailSIncrsat         = 0x00400000,
		OpFailSDecr            = 0x00500000,
		OpFailSDecrsat         = 0x00600000,
		OpFailSInvert          = 0x00700000,
		OpFailSShift           = 20,
		OpFailSMask            = 0x00f00000,
		OpFailZZero            = 0x00000000,
		OpFailZKeep            = 0x01000000,
		OpFailZReplace         = 0x02000000,
		OpFailZIncr            = 0x03000000,
		OpFailZIncrsat         = 0x04000000,
		OpFailZDecr            = 0x05000000,
		OpFailZDecrsat         = 0x06000000,
		OpFailZInvert          = 0x07000000,
		OpFailZShift           = 24,
		OpFailZMask            = 0x0f000000,
		OpPassZZero            = 0x00000000,
		OpPassZKeep            = 0x10000000,
		OpPassZReplace         = 0x20000000,
		OpPassZIncr            = 0x30000000,
		OpPassZIncrsat         = 0x40000000,
		OpPassZDecr            = 0x50000000,
		OpPassZDecrsat         = 0x60000000,
		OpPassZInvert          = 0x70000000,
		OpPassZShift           = 28,
		OpPassZMask            = 0xf0000000,
	}
	[Flags]
	public enum ClearFlags : ushort
	{
		None                   = 0x0000,
		Color                  = 0x0001,
		Depth                  = 0x0002,
		Stencil                = 0x0004,
		DiscardColor0          = 0x0008,
		DiscardColor1          = 0x0010,
		DiscardColor2          = 0x0020,
		DiscardColor3          = 0x0040,
		DiscardColor4          = 0x0080,
		DiscardColor5          = 0x0100,
		DiscardColor6          = 0x0200,
		DiscardColor7          = 0x0400,
		DiscardDepth           = 0x0800,
		DiscardStencil         = 0x1000,
		DiscardColorMask       = 0x07f8,
		DiscardMask            = 0x1ff8,
	}
	
	[Flags]
	public enum DebugFlags : uint
	{
		None                   = 0x00000000,
		Wireframe              = 0x00000001,
		Ifh                    = 0x00000002,
		Stats                  = 0x00000004,
		Text                   = 0x00000008,
		Profiler               = 0x00000010,
	}
	
	[Flags]
	public enum BufferFlags : ushort
	{
		ComputeFormat8x1       = 0x0001,
		ComputeFormat8x2       = 0x0002,
		ComputeFormat8x4       = 0x0003,
		ComputeFormat16x1      = 0x0004,
		ComputeFormat16x2      = 0x0005,
		ComputeFormat16x4      = 0x0006,
		ComputeFormat32x1      = 0x0007,
		ComputeFormat32x2      = 0x0008,
		ComputeFormat32x4      = 0x0009,
		ComputeFormatShift     = 0,
		ComputeFormatMask      = 0x000f,
		ComputeTypeInt         = 0x0010,
		ComputeTypeUint        = 0x0020,
		ComputeTypeFloat       = 0x0030,
		ComputeTypeShift       = 4,
		ComputeTypeMask        = 0x0030,
		None                   = 0x0000,
		ComputeRead            = 0x0100,
		ComputeWrite           = 0x0200,
		DrawIndirect           = 0x0400,
		AllowResize            = 0x0800,
		Index32                = 0x1000,
		ComputeReadWrite       = 0x0300,
	}
	
	[Flags]
	public enum TextureFlags : ulong
	{
		None                   = 0x0000000000000000,
		MsaaSample             = 0x0000000800000000,
		Rt                     = 0x0000001000000000,
		ComputeWrite           = 0x0000100000000000,
		Srgb                   = 0x0000200000000000,
		BlitDst                = 0x0000400000000000,
		ReadBack               = 0x0000800000000000,
		RtMsaaX2               = 0x0000002000000000,
		RtMsaaX4               = 0x0000003000000000,
		RtMsaaX8               = 0x0000004000000000,
		RtMsaaX16              = 0x0000005000000000,
		RtMsaaShift            = 36,
		RtMsaaMask             = 0x0000007000000000,
		RtWriteOnly            = 0x0000008000000000,
		RtShift                = 36,
		RtMask                 = 0x000000f000000000,
	}
	
	[Flags]
	public enum SamplerFlags : uint
	{
		UMirror                = 0x00000001,
		UClamp                 = 0x00000002,
		UBorder                = 0x00000003,
		UShift                 = 0,
		UMask                  = 0x00000003,
		VMirror                = 0x00000004,
		VClamp                 = 0x00000008,
		VBorder                = 0x0000000c,
		VShift                 = 2,
		VMask                  = 0x0000000c,
		WMirror                = 0x00000010,
		WClamp                 = 0x00000020,
		WBorder                = 0x00000030,
		WShift                 = 4,
		WMask                  = 0x00000030,
		MinPoint               = 0x00000040,
		MinAnisotropic         = 0x00000080,
		MinShift               = 6,
		MinMask                = 0x000000c0,
		MagPoint               = 0x00000100,
		MagAnisotropic         = 0x00000200,
		MagShift               = 8,
		MagMask                = 0x00000300,
		MipPoint               = 0x00000400,
		MipShift               = 10,
		MipMask                = 0x00000400,
		CompareLess            = 0x00010000,
		CompareLequal          = 0x00020000,
		CompareEqual           = 0x00030000,
		CompareGequal          = 0x00040000,
		CompareGreater         = 0x00050000,
		CompareNotequal        = 0x00060000,
		CompareNever           = 0x00070000,
		CompareAlways          = 0x00080000,
		CompareShift           = 16,
		CompareMask            = 0x000f0000,
		BorderColorShift       = 24,
		BorderColorMask        = 0x0f000000,
		ReservedShift          = 28,
		ReservedMask           = 0xf0000000,
		None                   = 0x00000000,
		SampleStencil          = 0x00100000,
		Point                  = 0x00000540,
		UvwMirror              = 0x00000015,
		UvwClamp               = 0x0000002a,
		UvwBorder              = 0x0000003f,
		BitsMask               = 0x000f07ff,
	}
	
	[Flags]
	public enum ResetFlags : uint
	{
		MsaaX2                 = 0x00000010,
		MsaaX4                 = 0x00000020,
		MsaaX8                 = 0x00000030,
		MsaaX16                = 0x00000040,
		MsaaShift              = 4,
		MsaaMask               = 0x00000070,
		None                   = 0x00000000,
		Fullscreen             = 0x00000001,
		Vsync                  = 0x00000080,
		Maxanisotropy          = 0x00000100,
		Capture                = 0x00000200,
		FlushAfterRender       = 0x00002000,
		FlipAfterRender        = 0x00004000,
		SrgbBackbuffer         = 0x00008000,
		Hdr10                  = 0x00010000,
		Hidpi                  = 0x00020000,
		DepthClamp             = 0x00040000,
		Suspend                = 0x00080000,
		FullscreenShift        = 0,
		FullscreenMask         = 0x00000001,
		ReservedShift          = 31,
		ReservedMask           = 0x80000000,
	}
	[Flags]
	public enum CapsFlags : ulong
	{
		AlphaToCoverage        = 0x0000000000000001,
		BlendIndependent       = 0x0000000000000002,
		Compute                = 0x0000000000000004,
		ConservativeRaster     = 0x0000000000000008,
		DrawIndirect           = 0x0000000000000010,
		FragmentDepth          = 0x0000000000000020,
		FragmentOrdering       = 0x0000000000000040,
		FramebufferRw          = 0x0000000000000080,
		GraphicsDebugger       = 0x0000000000000100,
		Reserved               = 0x0000000000000200,
		Hdr10                  = 0x0000000000000400,
		Hidpi                  = 0x0000000000000800,
		Index32                = 0x0000000000001000,
		Instancing             = 0x0000000000002000,
		OcclusionQuery         = 0x0000000000004000,
		RendererMultithreaded  = 0x0000000000008000,
		SwapChain              = 0x0000000000010000,
		Texture2dArray         = 0x0000000000020000,
		Texture3d              = 0x0000000000040000,
		TextureBlit            = 0x0000000000080000,
		TextureCompareReserved = 0x0000000000100000,
		TextureCompareLequal   = 0x0000000000200000,
		TextureCubeArray       = 0x0000000000400000,
		TextureDirectAccess    = 0x0000000000800000,
		TextureReadBack        = 0x0000000001000000,
		VertexAttribHalf       = 0x0000000002000000,
		VertexAttribUint10     = 0x0000000004000000,
		VertexId               = 0x0000000008000000,
		TextureCompareAll      = 0x0000000000300000,
	}
	
	[Flags]
	public enum CapsFormatFlags : ushort
	{
		TextureNone            = 0x0000,
		Texture2d              = 0x0001,
		Texture2dSrgb          = 0x0002,
		Texture2dEmulated      = 0x0004,
		Texture3d              = 0x0008,
		Texture3dSrgb          = 0x0010,
		Texture3dEmulated      = 0x0020,
		TextureCube            = 0x0040,
		TextureCubeSrgb        = 0x0080,
		TextureCubeEmulated    = 0x0100,
		TextureVertex          = 0x0200,
		TextureImage           = 0x0400,
		TextureFramebuffer     = 0x0800,
		TextureFramebufferMsaa = 0x1000,
		TextureMsaa            = 0x2000,
		TextureMipAutogen      = 0x4000,
	}
	
	[Flags]
	public enum ResolveFlags : uint
	{
		None                   = 0x00000000,
		AutoGenMips            = 0x00000001,
	}
	
	[Flags]
	public enum PciIdFlags : ushort
	{
		None                   = 0x0000,
		SoftwareRasterizer     = 0x0001,
		Amd                    = 0x1002,
		Intel                  = 0x8086,
		Nvidia                 = 0x10de,
	}
	
	[Flags]
	public enum CubeMapFlags : uint
	{
		PositiveX              = 0x00000000,
		NegativeX              = 0x00000001,
		PositiveY              = 0x00000002,
		NegativeY              = 0x00000003,
		PositiveZ              = 0x00000004,
		NegativeZ              = 0x00000005,
	}
	
	public enum Fatal
	{
		DebugCheck,
		InvalidShader,
		UnableToInitialize,
		UnableToCreateTexture,
		DeviceLost,
	}
	
	public enum RendererType
	{
		Noop,
		Direct3D9,
		Direct3D11,
		Direct3D12,
		Gnm,
		Metal,
		Nvn,
		OpenGLES,
		OpenGL,
		Vulkan,
	}
	
	public enum Access
	{
		Read,
		Write,
		ReadWrite,
	}
	
	public enum Attrib
	{
		Position,
		Normal,
		Tangent,
		Bitangent,
		Color0,
		Color1,
		Color2,
		Color3,
		Indices,
		Weight,
		TexCoord0,
		TexCoord1,
		TexCoord2,
		TexCoord3,
		TexCoord4,
		TexCoord5,
		TexCoord6,
		TexCoord7,
	}
	
	public enum AttribType
	{
		Uint8,
		Uint10,
		Int16,
		Half,
		Float,
	}
	
	public enum TextureFormat
	{
		BC1,
		BC2,
		BC3,
		BC4,
		BC5,
		BC6H,
		BC7,
		ETC1,
		ETC2,
		ETC2A,
		ETC2A1,
		PTC12,
		PTC14,
		PTC12A,
		PTC14A,
		PTC22,
		PTC24,
		ATC,
		ATCE,
		ATCI,
		ASTC4x4,
		ASTC5x5,
		ASTC6x6,
		ASTC8x5,
		ASTC8x6,
		ASTC10x5,
		Unknown,
		R1,
		A8,
		R8,
		R8I,
		R8U,
		R8S,
		R16,
		R16I,
		R16U,
		R16F,
		R16S,
		R32I,
		R32U,
		R32F,
		RG8,
		RG8I,
		RG8U,
		RG8S,
		RG16,
		RG16I,
		RG16U,
		RG16F,
		RG16S,
		RG32I,
		RG32U,
		RG32F,
		RGB8,
		RGB8I,
		RGB8U,
		RGB8S,
		RGB9E5F,
		BGRA8,
		RGBA8,
		RGBA8I,
		RGBA8U,
		RGBA8S,
		RGBA16,
		RGBA16I,
		RGBA16U,
		RGBA16F,
		RGBA16S,
		RGBA32I,
		RGBA32U,
		RGBA32F,
		R5G6B5,
		RGBA4,
		RGB5A1,
		RGB10A2,
		RG11B10F,
		UnknownDepth,
		D16,
		D24,
		D24S8,
		D32,
		D16F,
		D24F,
		D32F,
		D0S8,
	}
	
	public enum UniformType
	{
		Sampler,
		End,
		Vec4,
		Mat3,
		Mat4,
	}
	
	public enum BackbufferRatio
	{
		Equal,
		Half,
		Quarter,
		Eighth,
		Sixteenth,
		Double,
	}
	
	public enum OcclusionQueryResult
	{
		Invisible,
		Visible,
		NoResult,
	}
	
	public enum Topology
	{
		TriList,
		TriStrip,
		LineList,
		LineStrip,
		PointList,
	}
	
	public enum TopologyConvert
	{
		TriListFlipWinding,
		TriStripFlipWinding,
		TriListToLineList,
		TriStripToTriList,
		LineStripToLineList,
	}
	
	public enum TopologySort
	{
		DirectionFrontToBackMin,
		DirectionFrontToBackAvg,
		DirectionFrontToBackMax,
		DirectionBackToFrontMin,
		DirectionBackToFrontAvg,
		DirectionBackToFrontMax,
		DistanceFrontToBackMin,
		DistanceFrontToBackAvg,
		DistanceFrontToBackMax,
		DistanceBackToFrontMin,
		DistanceBackToFrontAvg,
		DistanceBackToFrontMax,
	}
	
	public enum ViewMode
	{
		Default,
		Sequential,
		DepthAscending,
		DepthDescending,
	}
	
	public enum RenderFrame
	{
		NoContext,
		Render,
		Timeout,
		Exiting,
	}
	
	public unsafe struct CapsGPU
	{
		public ushort vendorId;
		public ushort deviceId;
	}
	
	public unsafe struct CapsLimits
	{
		public uint maxDrawCalls;
		public uint maxBlits;
		public uint maxTextureSize;
		public uint maxTextureLayers;
		public uint maxViews;
		public uint maxFrameBuffers;
		public uint maxFBAttachments;
		public uint maxPrograms;
		public uint maxShaders;
		public uint maxTextures;
		public uint maxTextureSamplers;
		public uint maxComputeBindings;
		public uint maxVertexDecls;
		public uint maxVertexStreams;
		public uint maxIndexBuffers;
		public uint maxVertexBuffers;
		public uint maxDynamicIndexBuffers;
		public uint maxDynamicVertexBuffers;
		public uint maxUniforms;
		public uint maxOcclusionQueries;
		public uint maxEncoders;
		public uint transientVbSize;
		public uint transientIbSize;
	}
	
	public unsafe struct Caps
	{
		public RendererType rendererType;
		public ulong supported;
		public ushort vendorId;
		public ushort deviceId;
		public bool homogeneousDepth;
		public bool originBottomLeft;
		public byte numGPUs;
		public GPU gpu;
		public Limits limits;
		public ushort formats;
	}
	
	public unsafe struct InternalData
	{
		public Caps* caps;
		public void* context;
	}
	
	public unsafe struct PlatformData
	{
		public void* ndt;
		public void* nwh;
		public void* context;
		public void* backBuffer;
		public void* backBufferDS;
	}
	
	public unsafe struct Resolution
	{
		public TextureFormat format;
		public uint width;
		public uint height;
		public uint reset;
		public byte numBackBuffers;
		public byte maxFrameLatency;
	}
	
	public unsafe struct InitLimits
	{
		public ushort maxEncoders;
		public uint transientVbSize;
		public uint transientIbSize;
	}
	
	public unsafe struct Init
	{
		public RendererType type;
		public ushort vendorId;
		public ushort deviceId;
		public bool debug;
		public bool profile;
		public PlatformData platformData;
		public Resolution resolution;
		public Limits limits;
		public IntPtr callback;
		public IntPtr allocator;
	}
	
	public unsafe struct Memory
	{
		public byte* data;
		public uint size;
	}
	
	public unsafe struct TransientIndexBuffer
	{
		public byte* data;
		public uint size;
		public uint startIndex;
		public IndexBufferHandle handle;
	}
	
	public unsafe struct TransientVertexBuffer
	{
		public byte* data;
		public uint size;
		public uint startVertex;
		public ushort stride;
		public VertexBufferHandle handle;
		public VertexDeclHandle decl;
	}
	
	public unsafe struct InstanceDataBuffer
	{
		public byte* data;
		public uint size;
		public uint offset;
		public uint num;
		public ushort stride;
		public VertexBufferHandle handle;
	}
	
	public unsafe struct TextureInfo
	{
		public TextureFormat format;
		public uint storageSize;
		public ushort width;
		public ushort height;
		public ushort depth;
		public ushort numLayers;
		public byte numMips;
		public byte bitsPerPixel;
		public bool cubeMap;
	}
	
	public unsafe struct UniformInfo
	{
		public char name;
		public UniformType type;
		public ushort num;
	}
	
	public unsafe struct Attachment
	{
		public Access access;
		public TextureHandle handle;
		public ushort mip;
		public ushort layer;
		public byte resolve;
	}
	
	public unsafe struct Transform
	{
		public float* data;
		public ushort num;
	}
	
	public unsafe struct ViewStats
	{
		public char name;
		public ushort view;
		public long cpuTimeElapsed;
		public long gpuTimeElapsed;
	}
	
	public unsafe struct EncoderStats
	{
		public long cpuTimeBegin;
		public long cpuTimeEnd;
	}
	
	public unsafe struct Stats
	{
		public long cpuTimeFrame;
		public long cpuTimeBegin;
		public long cpuTimeEnd;
		public long cpuTimerFreq;
		public long gpuTimeBegin;
		public long gpuTimeEnd;
		public long gpuTimerFreq;
		public long waitRender;
		public long waitSubmit;
		public uint numDraw;
		public uint numCompute;
		public uint numBlit;
		public uint maxGpuLatency;
		public ushort numDynamicIndexBuffers;
		public ushort numDynamicVertexBuffers;
		public ushort numFrameBuffers;
		public ushort numIndexBuffers;
		public ushort numOcclusionQueries;
		public ushort numPrograms;
		public ushort numShaders;
		public ushort numTextures;
		public ushort numUniforms;
		public ushort numVertexBuffers;
		public ushort numVertexDecls;
		public long textureMemoryUsed;
		public long rtMemoryUsed;
		public int transientVbUsed;
		public int transientIbUsed;
		public uint numPrims;
		public long gpuMemoryMax;
		public long gpuMemoryUsed;
		public ushort width;
		public ushort height;
		public ushort textWidth;
		public ushort textHeight;
		public ushort numViews;
		public ViewStats* viewStats;
		public byte numEncoders;
		public EncoderStats* encoderStats;
	}
	
	public unsafe struct VertexDecl
	{
		public uint hash;
		public ushort stride;
		public ushort offset;
		public ushort attributes;
	}
	
	public unsafe struct Encoder
	{
	}
	
	public struct DynamicIndexBufferHandle{ public ushort idx; }
	
	public struct DynamicVertexBufferHandle{ public ushort idx; }
	
	public struct FrameBufferHandle{ public ushort idx; }
	
	public struct IndexBufferHandle{ public ushort idx; }
	
	public struct IndirectBufferHandle{ public ushort idx; }
	
	public struct OcclusionQueryHandle{ public ushort idx; }
	
	public struct ProgramHandle{ public ushort idx; }
	
	public struct ShaderHandle{ public ushort idx; }
	
	public struct TextureHandle{ public ushort idx; }
	
	public struct UniformHandle{ public ushort idx; }
	
	public struct VertexBufferHandle{ public ushort idx; }
	
	public struct VertexDeclHandle{ public ushort idx; }
	

	[DllImport(DllName, EntryPoint="bgfx_attachment_init", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void attachment_init(TextureHandle _handle, Access _access, ushort _layer, ushort _mip, byte _resolve);
	
	[DllImport(DllName, EntryPoint="bgfx_vertex_decl_begin", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe VertexDecl* vertex_decl_begin(RendererType _rendererType);
	
	[DllImport(DllName, EntryPoint="bgfx_vertex_decl_add", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe VertexDecl* vertex_decl_add(Attrib _attrib, byte _num, AttribType _type, bool _normalized, bool _asInt);
	
	[DllImport(DllName, EntryPoint="bgfx_vertex_decl_decode", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void vertex_decl_decode(Attrib _attrib, byte * _num, AttribType* _type, bool* _normalized, bool* _asInt);
	
	[DllImport(DllName, EntryPoint="bgfx_vertex_decl_has", CallingConvention = CallingConvention.Cdecl)]
	[return: MarshalAs(UnmanagedType.I1)]
	internal static extern unsafe bool vertex_decl_has(Attrib _attrib);
	
	[DllImport(DllName, EntryPoint="bgfx_vertex_decl_skip", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe VertexDecl* vertex_decl_skip(byte _num);
	
	[DllImport(DllName, EntryPoint="bgfx_vertex_decl_end", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void vertex_decl_end();
	
	[DllImport(DllName, EntryPoint="bgfx_vertex_decl_get_offset", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe ushort vertex_decl_get_offset(Attrib _attrib);
	
	[DllImport(DllName, EntryPoint="bgfx_vertex_decl_get_stride", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe ushort vertex_decl_get_stride();
	
	[DllImport(DllName, EntryPoint="bgfx_vertex_decl_get_size", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe uint vertex_decl_get_size(uint _num);
	
	[DllImport(DllName, EntryPoint="bgfx_vertex_pack", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void vertex_pack(float _input, bool _inputNormalized, Attrib _attr, VertexDecl* _decl, void* _data, uint _index);
	
	[DllImport(DllName, EntryPoint="bgfx_vertex_unpack", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void vertex_unpack(float _output, Attrib _attr, VertexDecl* _decl, void* _data, uint _index);
	
	[DllImport(DllName, EntryPoint="bgfx_vertex_convert", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void vertex_convert(VertexDecl* _dstDecl, void* _dstData, VertexDecl* _srcDecl, void* _srcData, uint _num);
	
	[DllImport(DllName, EntryPoint="bgfx_weld_vertices", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe ushort weld_vertices(ushort* _output, VertexDecl* _decl, void* _data, ushort _num, float _epsilon);
	
	[DllImport(DllName, EntryPoint="bgfx_topology_convert", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe uint topology_convert(TopologyConvert _conversion, void* _dst, uint _dstSize, void* _indices, uint _numIndices, bool _index32);
	
	[DllImport(DllName, EntryPoint="bgfx_topology_sort_tri_list", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void topology_sort_tri_list(TopologySort _sort, void* _dst, uint _dstSize, float _dir, float _pos, void* _vertices, uint _stride, void* _indices, uint _numIndices, bool _index32);
	
	[DllImport(DllName, EntryPoint="bgfx_get_supported_renderers", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe byte get_supported_renderers(byte _max, RendererType* _enum);
	
	[DllImport(DllName, EntryPoint="bgfx_get_renderer_name", CallingConvention = CallingConvention.Cdecl)]
	[return: MarshalAs(UnmanagedType.LPStr)]
	internal static extern unsafe string get_renderer_name(RendererType _type);
	
	[DllImport(DllName, EntryPoint="bgfx_init_ctor", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void init_ctor(Init* _init);
	
	[DllImport(DllName, EntryPoint="bgfx_init", CallingConvention = CallingConvention.Cdecl)]
	[return: MarshalAs(UnmanagedType.I1)]
	internal static extern unsafe bool init(Init* _init);
	
	[DllImport(DllName, EntryPoint="bgfx_shutdown", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void shutdown();
	
	[DllImport(DllName, EntryPoint="bgfx_reset", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void reset(uint _width, uint _height, uint _flags, TextureFormat _format);
	
	[DllImport(DllName, EntryPoint="bgfx_frame", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe uint frame(bool _capture);
	
	[DllImport(DllName, EntryPoint="bgfx_get_renderer_type", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe RendererType get_renderer_type();
	
	[DllImport(DllName, EntryPoint="bgfx_get_caps", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe Caps* get_caps();
	
	[DllImport(DllName, EntryPoint="bgfx_get_stats", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe Stats* get_stats();
	
	[DllImport(DllName, EntryPoint="bgfx_alloc", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe Memory* alloc(uint _size);
	
	[DllImport(DllName, EntryPoint="bgfx_copy", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe Memory* copy(void* _data, uint _size);
	
	[DllImport(DllName, EntryPoint="bgfx_make_ref", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe Memory* make_ref(void* _data, uint _size);
	
	[DllImport(DllName, EntryPoint="bgfx_make_ref_release", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe Memory* make_ref_release(void* _data, uint _size, IntPtr _releaseFn, void* _userData);
	
	[DllImport(DllName, EntryPoint="bgfx_set_debug", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_debug(uint _debug);
	
	[DllImport(DllName, EntryPoint="bgfx_dbg_text_clear", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void dbg_text_clear(byte _attr, bool _small);
	
	[DllImport(DllName, EntryPoint="bgfx_dbg_text_printf", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void dbg_text_printf(ushort _x, ushort _y, byte _attr, [MarshalAs(UnmanagedType.LPStr)] string _format, [MarshalAs(UnmanagedType.LPStr)] string args );
	
	[DllImport(DllName, EntryPoint="bgfx_dbg_text_vprintf", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void dbg_text_vprintf(ushort _x, ushort _y, byte _attr, [MarshalAs(UnmanagedType.LPStr)] string _format, IntPtr _argList);
	
	[DllImport(DllName, EntryPoint="bgfx_dbg_text_image", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void dbg_text_image(ushort _x, ushort _y, ushort _width, ushort _height, void* _data, ushort _pitch);
	
	[DllImport(DllName, EntryPoint="bgfx_create_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe IndexBufferHandle create_index_buffer(Memory* _mem, ushort _flags);
	
	[DllImport(DllName, EntryPoint="bgfx_set_index_buffer_name", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_index_buffer_name(IndexBufferHandle _handle, [MarshalAs(UnmanagedType.LPStr)] string _name, int _len);
	
	[DllImport(DllName, EntryPoint="bgfx_destroy_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void destroy_index_buffer(IndexBufferHandle _handle);
	
	[DllImport(DllName, EntryPoint="bgfx_create_vertex_decl", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe VertexDeclHandle create_vertex_decl(VertexDecl* _decl);
	
	[DllImport(DllName, EntryPoint="bgfx_destroy_vertex_decl", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void destroy_vertex_decl(VertexDeclHandle _handle);
	
	[DllImport(DllName, EntryPoint="bgfx_create_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe VertexBufferHandle create_vertex_buffer(Memory* _mem, VertexDecl* _decl, ushort _flags);
	
	[DllImport(DllName, EntryPoint="bgfx_set_vertex_buffer_name", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_vertex_buffer_name(VertexBufferHandle _handle, [MarshalAs(UnmanagedType.LPStr)] string _name, int _len);
	
	[DllImport(DllName, EntryPoint="bgfx_destroy_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void destroy_vertex_buffer(VertexBufferHandle _handle);
	
	[DllImport(DllName, EntryPoint="bgfx_create_dynamic_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe DynamicIndexBufferHandle create_dynamic_index_buffer(uint _num, ushort _flags);
	
	[DllImport(DllName, EntryPoint="bgfx_create_dynamic_index_buffer_mem", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe DynamicIndexBufferHandle create_dynamic_index_buffer_mem(Memory* _mem, ushort _flags);
	
	[DllImport(DllName, EntryPoint="bgfx_update_dynamic_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void update_dynamic_index_buffer(DynamicIndexBufferHandle _handle, uint _startIndex, Memory* _mem);
	
	[DllImport(DllName, EntryPoint="bgfx_destroy_dynamic_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void destroy_dynamic_index_buffer(DynamicIndexBufferHandle _handle);
	
	[DllImport(DllName, EntryPoint="bgfx_create_dynamic_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe DynamicVertexBufferHandle create_dynamic_vertex_buffer(uint _num, VertexDecl* _decl, ushort _flags);
	
	[DllImport(DllName, EntryPoint="bgfx_create_dynamic_vertex_buffer_mem", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe DynamicVertexBufferHandle create_dynamic_vertex_buffer_mem(Memory* _mem, VertexDecl* _decl, ushort _flags);
	
	[DllImport(DllName, EntryPoint="bgfx_update_dynamic_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void update_dynamic_vertex_buffer(DynamicVertexBufferHandle _handle, uint _startVertex, Memory* _mem);
	
	[DllImport(DllName, EntryPoint="bgfx_destroy_dynamic_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void destroy_dynamic_vertex_buffer(DynamicVertexBufferHandle _handle);
	
	[DllImport(DllName, EntryPoint="bgfx_get_avail_transient_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe uint get_avail_transient_index_buffer(uint _num);
	
	[DllImport(DllName, EntryPoint="bgfx_get_avail_transient_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe uint get_avail_transient_vertex_buffer(uint _num, VertexDecl* _decl);
	
	[DllImport(DllName, EntryPoint="bgfx_get_avail_instance_data_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe uint get_avail_instance_data_buffer(uint _num, ushort _stride);
	
	[DllImport(DllName, EntryPoint="bgfx_alloc_transient_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void alloc_transient_index_buffer(TransientIndexBuffer* _tib, uint _num);
	
	[DllImport(DllName, EntryPoint="bgfx_alloc_transient_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void alloc_transient_vertex_buffer(TransientVertexBuffer* _tvb, uint _num, VertexDecl* _decl);
	
	[DllImport(DllName, EntryPoint="bgfx_alloc_transient_buffers", CallingConvention = CallingConvention.Cdecl)]
	[return: MarshalAs(UnmanagedType.I1)]
	internal static extern unsafe bool alloc_transient_buffers(TransientVertexBuffer* _tvb, VertexDecl* _decl, uint _numVertices, TransientIndexBuffer* _tib, uint _numIndices);
	
	[DllImport(DllName, EntryPoint="bgfx_alloc_instance_data_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void alloc_instance_data_buffer(InstanceDataBuffer* _idb, uint _num, ushort _stride);
	
	[DllImport(DllName, EntryPoint="bgfx_create_indirect_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe IndirectBufferHandle create_indirect_buffer(uint _num);
	
	[DllImport(DllName, EntryPoint="bgfx_destroy_indirect_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void destroy_indirect_buffer(IndirectBufferHandle _handle);
	
	[DllImport(DllName, EntryPoint="bgfx_create_shader", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe ShaderHandle create_shader(Memory* _mem);
	
	[DllImport(DllName, EntryPoint="bgfx_get_shader_uniforms", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe ushort get_shader_uniforms(ShaderHandle _handle, UniformHandle* _uniforms, ushort _max);
	
	[DllImport(DllName, EntryPoint="bgfx_set_shader_name", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_shader_name(ShaderHandle _handle, [MarshalAs(UnmanagedType.LPStr)] string _name, int _len);
	
	[DllImport(DllName, EntryPoint="bgfx_destroy_shader", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void destroy_shader(ShaderHandle _handle);
	
	[DllImport(DllName, EntryPoint="bgfx_create_program", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe ProgramHandle create_program(ShaderHandle _vsh, ShaderHandle _fsh, bool _destroyShaders);
	
	[DllImport(DllName, EntryPoint="bgfx_create_compute_program", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe ProgramHandle create_compute_program(ShaderHandle _csh, bool _destroyShaders);
	
	[DllImport(DllName, EntryPoint="bgfx_destroy_program", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void destroy_program(ProgramHandle _handle);
	
	[DllImport(DllName, EntryPoint="bgfx_is_texture_valid", CallingConvention = CallingConvention.Cdecl)]
	[return: MarshalAs(UnmanagedType.I1)]
	internal static extern unsafe bool is_texture_valid(ushort _depth, bool _cubeMap, ushort _numLayers, TextureFormat _format, ulong _flags);
	
	[DllImport(DllName, EntryPoint="bgfx_calc_texture_size", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void calc_texture_size(TextureInfo* _info, ushort _width, ushort _height, ushort _depth, bool _cubeMap, bool _hasMips, ushort _numLayers, TextureFormat _format);
	
	[DllImport(DllName, EntryPoint="bgfx_create_texture", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe TextureHandle create_texture(Memory* _mem, ulong _flags, byte _skip, TextureInfo* _info);
	
	[DllImport(DllName, EntryPoint="bgfx_create_texture_2d", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe TextureHandle create_texture_2d(ushort _width, ushort _height, bool _hasMips, ushort _numLayers, TextureFormat _format, ulong _flags, Memory* _mem);
	
	[DllImport(DllName, EntryPoint="bgfx_create_texture_2d_scaled", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe TextureHandle create_texture_2d_scaled(BackbufferRatio _ratio, bool _hasMips, ushort _numLayers, TextureFormat _format, ulong _flags);
	
	[DllImport(DllName, EntryPoint="bgfx_create_texture_3d", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe TextureHandle create_texture_3d(ushort _width, ushort _height, ushort _depth, bool _hasMips, TextureFormat _format, ulong _flags, Memory* _mem);
	
	[DllImport(DllName, EntryPoint="bgfx_create_texture_cube", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe TextureHandle create_texture_cube(ushort _size, bool _hasMips, ushort _numLayers, TextureFormat _format, ulong _flags, Memory* _mem);
	
	[DllImport(DllName, EntryPoint="bgfx_update_texture_2d", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void update_texture_2d(TextureHandle _handle, ushort _layer, byte _mip, ushort _x, ushort _y, ushort _width, ushort _height, Memory* _mem, ushort _pitch);
	
	[DllImport(DllName, EntryPoint="bgfx_update_texture_3d", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void update_texture_3d(TextureHandle _handle, byte _mip, ushort _x, ushort _y, ushort _z, ushort _width, ushort _height, ushort _depth, Memory* _mem);
	
	[DllImport(DllName, EntryPoint="bgfx_update_texture_cube", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void update_texture_cube(TextureHandle _handle, ushort _layer, byte _side, byte _mip, ushort _x, ushort _y, ushort _width, ushort _height, Memory* _mem, ushort _pitch);
	
	[DllImport(DllName, EntryPoint="bgfx_read_texture", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe uint read_texture(TextureHandle _handle, void* _data, byte _mip);
	
	[DllImport(DllName, EntryPoint="bgfx_set_texture_name", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_texture_name(TextureHandle _handle, [MarshalAs(UnmanagedType.LPStr)] string _name, int _len);
	
	[DllImport(DllName, EntryPoint="bgfx_get_direct_access_ptr", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void* get_direct_access_ptr(TextureHandle _handle);
	
	[DllImport(DllName, EntryPoint="bgfx_destroy_texture", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void destroy_texture(TextureHandle _handle);
	
	[DllImport(DllName, EntryPoint="bgfx_create_frame_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe FrameBufferHandle create_frame_buffer(ushort _width, ushort _height, TextureFormat _format, ulong _textureFlags);
	
	[DllImport(DllName, EntryPoint="bgfx_create_frame_buffer_scaled", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe FrameBufferHandle create_frame_buffer_scaled(BackbufferRatio _ratio, TextureFormat _format, ulong _textureFlags);
	
	[DllImport(DllName, EntryPoint="bgfx_create_frame_buffer_from_handles", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe FrameBufferHandle create_frame_buffer_from_handles(byte _num, TextureHandle* _handles, bool _destroyTexture);
	
	[DllImport(DllName, EntryPoint="bgfx_create_frame_buffer_from_attachment", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe FrameBufferHandle create_frame_buffer_from_attachment(byte _num, Attachment* _attachment, bool _destroyTexture);
	
	[DllImport(DllName, EntryPoint="bgfx_create_frame_buffer_from_nwh", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe FrameBufferHandle create_frame_buffer_from_nwh(void* _nwh, ushort _width, ushort _height, TextureFormat _format, TextureFormat _depthFormat);
	
	[DllImport(DllName, EntryPoint="bgfx_set_frame_buffer_name", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_frame_buffer_name(FrameBufferHandle _handle, [MarshalAs(UnmanagedType.LPStr)] string _name, int _len);
	
	[DllImport(DllName, EntryPoint="bgfx_get_texture", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe TextureHandle get_texture(FrameBufferHandle _handle, byte _attachment);
	
	[DllImport(DllName, EntryPoint="bgfx_destroy_frame_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void destroy_frame_buffer(FrameBufferHandle _handle);
	
	[DllImport(DllName, EntryPoint="bgfx_create_uniform", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe UniformHandle create_uniform([MarshalAs(UnmanagedType.LPStr)] string _name, UniformType _type, ushort _num);
	
	[DllImport(DllName, EntryPoint="bgfx_get_uniform_info", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void get_uniform_info(UniformHandle _handle, UniformInfo* _info);
	
	[DllImport(DllName, EntryPoint="bgfx_destroy_uniform", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void destroy_uniform(UniformHandle _handle);
	
	[DllImport(DllName, EntryPoint="bgfx_create_occlusion_query", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe OcclusionQueryHandle create_occlusion_query();
	
	[DllImport(DllName, EntryPoint="bgfx_get_result", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe OcclusionQueryResult get_result(OcclusionQueryHandle _handle, int* _result);
	
	[DllImport(DllName, EntryPoint="bgfx_destroy_occlusion_query", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void destroy_occlusion_query(OcclusionQueryHandle _handle);
	
	[DllImport(DllName, EntryPoint="bgfx_set_palette_color", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_palette_color(byte _index, float _rgba);
	
	[DllImport(DllName, EntryPoint="bgfx_set_palette_color_rgba8", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_palette_color_rgba8(byte _index, uint _rgba);
	
	[DllImport(DllName, EntryPoint="bgfx_set_view_name", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_view_name(ushort _id, [MarshalAs(UnmanagedType.LPStr)] string _name);
	
	[DllImport(DllName, EntryPoint="bgfx_set_view_rect", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_view_rect(ushort _id, ushort _x, ushort _y, ushort _width, ushort _height);
	
	[DllImport(DllName, EntryPoint="bgfx_set_view_rect_ratio", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_view_rect_ratio(ushort _id, ushort _x, ushort _y, BackbufferRatio _ratio);
	
	[DllImport(DllName, EntryPoint="bgfx_set_view_scissor", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_view_scissor(ushort _id, ushort _x, ushort _y, ushort _width, ushort _height);
	
	[DllImport(DllName, EntryPoint="bgfx_set_view_clear", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_view_clear(ushort _id, ushort _flags, uint _rgba, float _depth, byte _stencil);
	
	[DllImport(DllName, EntryPoint="bgfx_set_view_clear_mrt", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_view_clear_mrt(ushort _id, ushort _flags, float _depth, byte _stencil, byte _c0, byte _c1, byte _c2, byte _c3, byte _c4, byte _c5, byte _c6, byte _c7);
	
	[DllImport(DllName, EntryPoint="bgfx_set_view_mode", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_view_mode(ushort _id, ViewMode _mode);
	
	[DllImport(DllName, EntryPoint="bgfx_set_view_frame_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_view_frame_buffer(ushort _id, FrameBufferHandle _handle);
	
	[DllImport(DllName, EntryPoint="bgfx_set_view_transform", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_view_transform(ushort _id, void* _view, void* _proj);
	
	[DllImport(DllName, EntryPoint="bgfx_set_view_order", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_view_order(ushort _id, ushort _num, ushort* _order);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_begin", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe Encoder* encoder_begin(bool _forThread);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_end", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_end(Encoder* _encoder);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_marker", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_set_marker([MarshalAs(UnmanagedType.LPStr)] string _marker);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_state", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_set_state(ulong _state, uint _rgba);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_condition", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_set_condition(OcclusionQueryHandle _handle, bool _visible);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_stencil", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_set_stencil(uint _fstencil, uint _bstencil);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_scissor", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe ushort encoder_set_scissor(ushort _x, ushort _y, ushort _width, ushort _height);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_scissor_cached", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_set_scissor_cached(ushort _cache);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_transform", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe uint encoder_set_transform(void* _mtx, ushort _num);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_transform_cached", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_set_transform_cached(uint _cache, ushort _num);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_alloc_transform", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe uint encoder_alloc_transform(Transform* _transform, ushort _num);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_uniform", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_set_uniform(UniformHandle _handle, void* _value, ushort _num);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_set_index_buffer(IndexBufferHandle _handle);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_set_index_buffer(IndexBufferHandle _handle, uint _firstIndex, uint _numIndices);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_set_index_buffer(DynamicIndexBufferHandle _handle);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_dynamic_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_set_dynamic_index_buffer(DynamicIndexBufferHandle _handle, uint _firstIndex, uint _numIndices);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_set_index_buffer(TransientIndexBuffer* _tib);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_transient_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_set_transient_index_buffer(TransientIndexBuffer* _tib, uint _firstIndex, uint _numIndices);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_set_vertex_buffer(byte _stream, VertexBufferHandle _handle);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_set_vertex_buffer(byte _stream, VertexBufferHandle _handle, uint _startVertex, uint _numVertices, VertexDeclHandle _declHandle);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_set_vertex_buffer(byte _stream, DynamicVertexBufferHandle _handle);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_dynamic_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_set_dynamic_vertex_buffer(byte _stream, DynamicVertexBufferHandle _handle, uint _startVertex, uint _numVertices, VertexDeclHandle _declHandle);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_set_vertex_buffer(byte _stream, TransientVertexBuffer* _tvb);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_transient_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_set_transient_vertex_buffer(byte _stream, TransientVertexBuffer* _tvb, uint _startVertex, uint _numVertices, VertexDeclHandle _declHandle);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_vertex_count", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_set_vertex_count(uint _numVertices);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_instance_data_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_set_instance_data_buffer(InstanceDataBuffer* _idb);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_instance_data_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_set_instance_data_buffer(InstanceDataBuffer* _idb, uint _start, uint _num);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_instance_data_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_set_instance_data_buffer(VertexBufferHandle _handle);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_instance_data_from_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_set_instance_data_from_vertex_buffer(VertexBufferHandle _handle, uint _startVertex, uint _num);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_instance_data_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_set_instance_data_buffer(DynamicVertexBufferHandle _handle);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_instance_data_from_dynamic_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_set_instance_data_from_dynamic_vertex_buffer(DynamicVertexBufferHandle _handle, uint _startVertex, uint _num);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_instance_count", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_set_instance_count(uint _numInstances);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_texture", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_set_texture(byte _stage, UniformHandle _sampler, TextureHandle _handle, uint _flags);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_touch", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_touch(ushort _id);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_submit", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_submit(ushort _id, ProgramHandle _program, uint _depth, bool _preserveState);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_submit_occlusion_query", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_submit_occlusion_query(ushort _id, ProgramHandle _program, OcclusionQueryHandle _occlusionQuery, uint _depth, bool _preserveState);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_submit_indirect", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_submit_indirect(ushort _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, ushort _start, ushort _num, uint _depth, bool _preserveState);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_compute_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_set_compute_index_buffer(byte _stage, IndexBufferHandle _handle, Access _access);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_compute_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_set_compute_vertex_buffer(byte _stage, VertexBufferHandle _handle, Access _access);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_compute_dynamic_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_set_compute_dynamic_index_buffer(byte _stage, DynamicIndexBufferHandle _handle, Access _access);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_compute_dynamic_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_set_compute_dynamic_vertex_buffer(byte _stage, DynamicVertexBufferHandle _handle, Access _access);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_compute_indirect_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_set_compute_indirect_buffer(byte _stage, IndirectBufferHandle _handle, Access _access);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_image", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_set_image(byte _stage, TextureHandle _handle, byte _mip, Access _access, TextureFormat _format);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_dispatch", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_dispatch(ushort _id, ProgramHandle _program, uint _numX, uint _numY, uint _numZ);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_dispatch_indirect", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_dispatch_indirect(ushort _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, ushort _start, ushort _num);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_discard", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_discard();
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_blit", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_blit(ushort _id, TextureHandle _dst, ushort _dstX, ushort _dstY, TextureHandle _src, ushort _srcX, ushort _srcY, ushort _width, ushort _height);
	
	[DllImport(DllName, EntryPoint="bgfx_encoder_blit", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void encoder_blit(ushort _id, TextureHandle _dst, byte _dstMip, ushort _dstX, ushort _dstY, ushort _dstZ, TextureHandle _src, byte _srcMip, ushort _srcX, ushort _srcY, ushort _srcZ, ushort _width, ushort _height, ushort _depth);
	
	[DllImport(DllName, EntryPoint="bgfx_request_screen_shot", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void request_screen_shot(FrameBufferHandle _handle, [MarshalAs(UnmanagedType.LPStr)] string _filePath);
	
	[DllImport(DllName, EntryPoint="bgfx_render_frame", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe RenderFrame render_frame(int _msecs);
	
	[DllImport(DllName, EntryPoint="bgfx_set_platform_data", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_platform_data(PlatformData* _data);
	
	[DllImport(DllName, EntryPoint="bgfx_get_internal_data", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe InternalData* get_internal_data();
	
	[DllImport(DllName, EntryPoint="bgfx_override_internal_texture_ptr", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe UIntPtr override_internal_texture_ptr(TextureHandle _handle, UIntPtr _ptr);
	
	[DllImport(DllName, EntryPoint="bgfx_override_internal_texture", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe UIntPtr override_internal_texture(TextureHandle _handle, ushort _width, ushort _height, byte _numMips, TextureFormat _format, ulong _flags);
	
	[DllImport(DllName, EntryPoint="bgfx_set_marker", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_marker([MarshalAs(UnmanagedType.LPStr)] string _marker);
	
	[DllImport(DllName, EntryPoint="bgfx_set_state", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_state(ulong _state, uint _rgba);
	
	[DllImport(DllName, EntryPoint="bgfx_set_condition", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_condition(OcclusionQueryHandle _handle, bool _visible);
	
	[DllImport(DllName, EntryPoint="bgfx_set_stencil", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_stencil(uint _fstencil, uint _bstencil);
	
	[DllImport(DllName, EntryPoint="bgfx_set_scissor", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe ushort set_scissor(ushort _x, ushort _y, ushort _width, ushort _height);
	
	[DllImport(DllName, EntryPoint="bgfx_set_scissor_cached", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_scissor_cached(ushort _cache);
	
	[DllImport(DllName, EntryPoint="bgfx_set_transform", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe uint set_transform(void* _mtx, ushort _num);
	
	[DllImport(DllName, EntryPoint="bgfx_set_transform_cached", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_transform_cached(uint _cache, ushort _num);
	
	[DllImport(DllName, EntryPoint="bgfx_alloc_transform", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe uint alloc_transform(Transform* _transform, ushort _num);
	
	[DllImport(DllName, EntryPoint="bgfx_set_uniform", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_uniform(UniformHandle _handle, void* _value, ushort _num);
	
	[DllImport(DllName, EntryPoint="bgfx_set_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_index_buffer(IndexBufferHandle _handle);
	
	[DllImport(DllName, EntryPoint="bgfx_set_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_index_buffer(IndexBufferHandle _handle, uint _firstIndex, uint _numIndices);
	
	[DllImport(DllName, EntryPoint="bgfx_set_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_index_buffer(DynamicIndexBufferHandle _handle);
	
	[DllImport(DllName, EntryPoint="bgfx_set_dynamic_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_dynamic_index_buffer(DynamicIndexBufferHandle _handle, uint _firstIndex, uint _numIndices);
	
	[DllImport(DllName, EntryPoint="bgfx_set_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_index_buffer(TransientIndexBuffer* _tib);
	
	[DllImport(DllName, EntryPoint="bgfx_set_transient_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_transient_index_buffer(TransientIndexBuffer* _tib, uint _firstIndex, uint _numIndices);
	
	[DllImport(DllName, EntryPoint="bgfx_set_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_vertex_buffer(byte _stream, VertexBufferHandle _handle);
	
	[DllImport(DllName, EntryPoint="bgfx_set_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_vertex_buffer(byte _stream, VertexBufferHandle _handle, uint _startVertex, uint _numVertices);
	
	[DllImport(DllName, EntryPoint="bgfx_set_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_vertex_buffer(byte _stream, DynamicVertexBufferHandle _handle);
	
	[DllImport(DllName, EntryPoint="bgfx_set_dynamic_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_dynamic_vertex_buffer(byte _stream, DynamicVertexBufferHandle _handle, uint _startVertex, uint _numVertices);
	
	[DllImport(DllName, EntryPoint="bgfx_set_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_vertex_buffer(byte _stream, TransientVertexBuffer* _tvb);
	
	[DllImport(DllName, EntryPoint="bgfx_set_transient_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_transient_vertex_buffer(byte _stream, TransientVertexBuffer* _tvb, uint _startVertex, uint _numVertices);
	
	[DllImport(DllName, EntryPoint="bgfx_set_vertex_count", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_vertex_count(uint _numVertices);
	
	[DllImport(DllName, EntryPoint="bgfx_set_instance_data_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_instance_data_buffer(InstanceDataBuffer* _idb);
	
	[DllImport(DllName, EntryPoint="bgfx_set_instance_data_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_instance_data_buffer(InstanceDataBuffer* _idb, uint _start, uint _num);
	
	[DllImport(DllName, EntryPoint="bgfx_set_instance_data_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_instance_data_buffer(VertexBufferHandle _handle);
	
	[DllImport(DllName, EntryPoint="bgfx_set_instance_data_from_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_instance_data_from_vertex_buffer(VertexBufferHandle _handle, uint _startVertex, uint _num);
	
	[DllImport(DllName, EntryPoint="bgfx_set_instance_data_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_instance_data_buffer(DynamicVertexBufferHandle _handle);
	
	[DllImport(DllName, EntryPoint="bgfx_set_instance_data_from_dynamic_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_instance_data_from_dynamic_vertex_buffer(DynamicVertexBufferHandle _handle, uint _startVertex, uint _num);
	
	[DllImport(DllName, EntryPoint="bgfx_set_instance_count", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_instance_count(uint _numInstances);
	
	[DllImport(DllName, EntryPoint="bgfx_set_texture", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_texture(byte _stage, UniformHandle _sampler, TextureHandle _handle, uint _flags);
	
	[DllImport(DllName, EntryPoint="bgfx_touch", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void touch(ushort _id);
	
	[DllImport(DllName, EntryPoint="bgfx_submit", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void submit(ushort _id, ProgramHandle _program, uint _depth, bool _preserveState);
	
	[DllImport(DllName, EntryPoint="bgfx_submit_occlusion_query", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void submit_occlusion_query(ushort _id, ProgramHandle _program, OcclusionQueryHandle _occlusionQuery, uint _depth, bool _preserveState);
	
	[DllImport(DllName, EntryPoint="bgfx_submit_indirect", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void submit_indirect(ushort _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, ushort _start, ushort _num, uint _depth, bool _preserveState);
	
	[DllImport(DllName, EntryPoint="bgfx_set_compute_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_compute_index_buffer(byte _stage, IndexBufferHandle _handle, Access _access);
	
	[DllImport(DllName, EntryPoint="bgfx_set_compute_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_compute_vertex_buffer(byte _stage, VertexBufferHandle _handle, Access _access);
	
	[DllImport(DllName, EntryPoint="bgfx_set_compute_dynamic_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_compute_dynamic_index_buffer(byte _stage, DynamicIndexBufferHandle _handle, Access _access);
	
	[DllImport(DllName, EntryPoint="bgfx_set_compute_dynamic_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_compute_dynamic_vertex_buffer(byte _stage, DynamicVertexBufferHandle _handle, Access _access);
	
	[DllImport(DllName, EntryPoint="bgfx_set_compute_indirect_buffer", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_compute_indirect_buffer(byte _stage, IndirectBufferHandle _handle, Access _access);
	
	[DllImport(DllName, EntryPoint="bgfx_set_image", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void set_image(byte _stage, TextureHandle _handle, byte _mip, Access _access, TextureFormat _format);
	
	[DllImport(DllName, EntryPoint="bgfx_dispatch", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void dispatch(ushort _id, ProgramHandle _program, uint _numX, uint _numY, uint _numZ);
	
	[DllImport(DllName, EntryPoint="bgfx_dispatch_indirect", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void dispatch_indirect(ushort _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, ushort _start, ushort _num);
	
	[DllImport(DllName, EntryPoint="bgfx_discard", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void discard();
	
	[DllImport(DllName, EntryPoint="bgfx_blit", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void blit(ushort _id, TextureHandle _dst, ushort _dstX, ushort _dstY, TextureHandle _src, ushort _srcX, ushort _srcY, ushort _width, ushort _height);
	
	[DllImport(DllName, EntryPoint="bgfx_blit", CallingConvention = CallingConvention.Cdecl)]
	internal static extern unsafe void blit(ushort _id, TextureHandle _dst, byte _dstMip, ushort _dstX, ushort _dstY, ushort _dstZ, TextureHandle _src, byte _srcMip, ushort _srcX, ushort _srcY, ushort _srcZ, ushort _width, ushort _height, ushort _depth);
	

#if DEBUG
	const string DllName = "bgfx_debug.dll";
#else
	const string DllName = "bgfx.dll";
#endif
}
