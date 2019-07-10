/*
 * Copyright 2011-2019 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

/*
 *
 * AUTO GENERATED! DO NOT EDIT!
 *
 */

using System;
using System.Runtime.InteropServices;
using System.Security;

namespace Bgfx
{
public static partial class bgfx
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
	
		Count
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
	
		Count
	}
	
	public enum Access
	{
		Read,
		Write,
		ReadWrite,
	
		Count
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
	
		Count
	}
	
	public enum AttribType
	{
		Uint8,
		Uint10,
		Int16,
		Half,
		Float,
	
		Count
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
	
		Count
	}
	
	public enum UniformType
	{
		Sampler,
		End,
		Vec4,
		Mat3,
		Mat4,
	
		Count
	}
	
	public enum BackbufferRatio
	{
		Equal,
		Half,
		Quarter,
		Eighth,
		Sixteenth,
		Double,
	
		Count
	}
	
	public enum OcclusionQueryResult
	{
		Invisible,
		Visible,
		NoResult,
	
		Count
	}
	
	public enum Topology
	{
		TriList,
		TriStrip,
		LineList,
		LineStrip,
		PointList,
	
		Count
	}
	
	public enum TopologyConvert
	{
		TriListFlipWinding,
		TriStripFlipWinding,
		TriListToLineList,
		TriStripToTriList,
		LineStripToLineList,
	
		Count
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
	
		Count
	}
	
	public enum ViewMode
	{
		Default,
		Sequential,
		DepthAscending,
		DepthDescending,
	
		Count
	}
	
	public enum RenderFrame
	{
		NoContext,
		Render,
		Timeout,
		Exiting,
	
		Count
	}
	
	public unsafe struct Caps
	{
		public unsafe struct GPU
		{
			public ushort vendorId;
			public ushort deviceId;
		}
	
		public unsafe struct Limits
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
	
		public RendererType rendererType;
		public ulong supported;
		public ushort vendorId;
		public ushort deviceId;
		public byte homogeneousDepth;
		public byte originBottomLeft;
		public byte numGPUs;
		public fixed uint gpu[4];
		public Limits limits;
		public fixed ushort formats[85];
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
	
	public unsafe struct Init
	{
		public unsafe struct Limits
		{
			public ushort maxEncoders;
			public uint transientVbSize;
			public uint transientIbSize;
		}
	
		public RendererType type;
		public ushort vendorId;
		public ushort deviceId;
		public byte debug;
		public byte profile;
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
		public byte cubeMap;
	}
	
	public unsafe struct UniformInfo
	{
		public fixed byte name[256];
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
		public fixed byte name[256];
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
		public fixed uint numPrims[5];
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
		public fixed ushort offset[18];
		public fixed ushort attributes[18];
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
	

	/// <summary>
	/// Init attachment.
	/// </summary>
	///
	/// <param name="_handle">Render target texture handle.</param>
	/// <param name="_access">Access. See `Access::Enum`.</param>
	/// <param name="_layer">Cubemap side or depth layer/slice.</param>
	/// <param name="_mip">Mip level.</param>
	/// <param name="_resolve">Resolve flags. See: `BGFX_RESOLVE_*`</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_attachment_init", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void attachment_init(Attachment* _this, TextureHandle _handle, Access _access, ushort _layer, ushort _mip, byte _resolve);
	
	/// <summary>
	/// Start VertexDecl.
	/// </summary>
	///
	[DllImport(DllName, EntryPoint="bgfx_vertex_decl_begin", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe VertexDecl* vertex_decl_begin(VertexDecl* _this, RendererType _rendererType);
	
	/// <summary>
	/// Add attribute to VertexDecl.
	/// @remarks Must be called between begin/end.
	/// </summary>
	///
	/// <param name="_attrib">Attribute semantics. See: `bgfx::Attrib`</param>
	/// <param name="_num">Number of elements 1, 2, 3 or 4.</param>
	/// <param name="_type">Element type.</param>
	/// <param name="_normalized">When using fixed point AttribType (f.e. Uint8) value will be normalized for vertex shader usage. When normalized is set to true, AttribType::Uint8 value in range 0-255 will be in range 0.0-1.0 in vertex shader.</param>
	/// <param name="_asInt">Packaging rule for vertexPack, vertexUnpack, and vertexConvert for AttribType::Uint8 and AttribType::Int16. Unpacking code must be implemented inside vertex shader.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_vertex_decl_add", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe VertexDecl* vertex_decl_add(VertexDecl* _this, Attrib _attrib, byte _num, AttribType _type, byte _normalized, byte _asInt);
	
	/// <summary>
	/// Decode attribute.
	/// </summary>
	///
	/// <param name="_attrib">Attribute semantics. See: `bgfx::Attrib`</param>
	/// <param name="_num">Number of elements.</param>
	/// <param name="_type">Element type.</param>
	/// <param name="_normalized">Attribute is normalized.</param>
	/// <param name="_asInt">Attribute is packed as int.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_vertex_decl_decode", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void vertex_decl_decode(VertexDecl* _this, Attrib _attrib, byte * _num, AttribType* _type, byte * _normalized, byte * _asInt);
	
	/// <summary>
	/// Returns true if VertexDecl contains attribute.
	/// </summary>
	///
	/// <param name="_attrib">Attribute semantics. See: `bgfx::Attrib`</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_vertex_decl_has", CallingConvention = CallingConvention.Cdecl)]
	[return: MarshalAs(UnmanagedType.I1)]
	public static extern unsafe byte vertex_decl_has(VertexDecl* _this, Attrib _attrib);
	
	/// <summary>
	/// Skip `_num` bytes in vertex stream.
	/// </summary>
	///
	[DllImport(DllName, EntryPoint="bgfx_vertex_decl_skip", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe VertexDecl* vertex_decl_skip(VertexDecl* _this, byte _num);
	
	/// <summary>
	/// End VertexDecl.
	/// </summary>
	///
	[DllImport(DllName, EntryPoint="bgfx_vertex_decl_end", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void vertex_decl_end(VertexDecl* _this);
	
	/// <summary>
	/// Pack vertex attribute into vertex stream format.
	/// </summary>
	///
	/// <param name="_input">Value to be packed into vertex stream.</param>
	/// <param name="_inputNormalized">`true` if input value is already normalized.</param>
	/// <param name="_attr">Attribute to pack.</param>
	/// <param name="_decl">Vertex stream declaration.</param>
	/// <param name="_data">Destination vertex stream where data will be packed.</param>
	/// <param name="_index">Vertex index that will be modified.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_vertex_pack", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void vertex_pack(float _input, byte _inputNormalized, Attrib _attr, VertexDecl* _decl, void* _data, uint _index);
	
	/// <summary>
	/// Unpack vertex attribute from vertex stream format.
	/// </summary>
	///
	/// <param name="_output">Result of unpacking.</param>
	/// <param name="_attr">Attribute to unpack.</param>
	/// <param name="_decl">Vertex stream declaration.</param>
	/// <param name="_data">Source vertex stream from where data will be unpacked.</param>
	/// <param name="_index">Vertex index that will be unpacked.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_vertex_unpack", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void vertex_unpack(float _output, Attrib _attr, VertexDecl* _decl, void* _data, uint _index);
	
	/// <summary>
	/// Converts vertex stream data from one vertex stream format to another.
	/// </summary>
	///
	/// <param name="_dstDecl">Destination vertex stream declaration.</param>
	/// <param name="_dstData">Destination vertex stream.</param>
	/// <param name="_srcDecl">Source vertex stream declaration.</param>
	/// <param name="_srcData">Source vertex stream data.</param>
	/// <param name="_num">Number of vertices to convert from source to destination.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_vertex_convert", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void vertex_convert(VertexDecl* _dstDecl, void* _dstData, VertexDecl* _srcDecl, void* _srcData, uint _num);
	
	/// <summary>
	/// Weld vertices.
	/// </summary>
	///
	/// <param name="_output">Welded vertices remapping table. The size of buffer must be the same as number of vertices.</param>
	/// <param name="_decl">Vertex stream declaration.</param>
	/// <param name="_data">Vertex stream.</param>
	/// <param name="_num">Number of vertices in vertex stream.</param>
	/// <param name="_epsilon">Error tolerance for vertex position comparison.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_weld_vertices", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe ushort weld_vertices(ushort* _output, VertexDecl* _decl, void* _data, ushort _num, float _epsilon);
	
	/// <summary>
	/// Convert index buffer for use with different primitive topologies.
	/// </summary>
	///
	/// <param name="_conversion">Conversion type, see `TopologyConvert::Enum`.</param>
	/// <param name="_dst">Destination index buffer. If this argument is NULL function will return number of indices after conversion.</param>
	/// <param name="_dstSize">Destination index buffer in bytes. It must be large enough to contain output indices. If destination size is insufficient index buffer will be truncated.</param>
	/// <param name="_indices">Source indices.</param>
	/// <param name="_numIndices">Number of input indices.</param>
	/// <param name="_index32">Set to `true` if input indices are 32-bit.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_topology_convert", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe uint topology_convert(TopologyConvert _conversion, void* _dst, uint _dstSize, void* _indices, uint _numIndices, byte _index32);
	
	/// <summary>
	/// Sort indices.
	/// </summary>
	///
	/// <param name="_sort">Sort order, see `TopologySort::Enum`.</param>
	/// <param name="_dst">Destination index buffer.</param>
	/// <param name="_dstSize">Destination index buffer in bytes. It must be large enough to contain output indices. If destination size is insufficient index buffer will be truncated.</param>
	/// <param name="_dir">Direction (vector must be normalized).</param>
	/// <param name="_pos">Position.</param>
	/// <param name="_vertices">Pointer to first vertex represented as float x, y, z. Must contain at least number of vertices referencende by index buffer.</param>
	/// <param name="_stride">Vertex stride.</param>
	/// <param name="_indices">Source indices.</param>
	/// <param name="_numIndices">Number of input indices.</param>
	/// <param name="_index32">Set to `true` if input indices are 32-bit.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_topology_sort_tri_list", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void topology_sort_tri_list(TopologySort _sort, void* _dst, uint _dstSize, float _dir, float _pos, void* _vertices, uint _stride, void* _indices, uint _numIndices, byte _index32);
	
	/// <summary>
	/// Returns supported backend API renderers.
	/// </summary>
	///
	/// <param name="_max">Maximum number of elements in _enum array.</param>
	/// <param name="_enum">Array where supported renderers will be written.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_get_supported_renderers", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe byte get_supported_renderers(byte _max, RendererType* _enum);
	
	/// <summary>
	/// Returns name of renderer.
	/// </summary>
	///
	/// <param name="_type">Renderer backend type. See: `bgfx::RendererType`</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_get_renderer_name", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe IntPtr get_renderer_name(RendererType _type);
	
	[DllImport(DllName, EntryPoint="bgfx_init_ctor", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void init_ctor(Init* _init);
	
	/// <summary>
	/// Initialize bgfx library.
	/// </summary>
	///
	/// <param name="_init">Initialization parameters. See: `bgfx::Init` for more info.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_init", CallingConvention = CallingConvention.Cdecl)]
	[return: MarshalAs(UnmanagedType.I1)]
	public static extern unsafe byte init(Init* _init);
	
	/// <summary>
	/// Shutdown bgfx library.
	/// </summary>
	///
	[DllImport(DllName, EntryPoint="bgfx_shutdown", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void shutdown();
	
	/// <summary>
	/// Reset graphic settings and back-buffer size.
	/// @attention This call doesn't actually change window size, it just
	///   resizes back-buffer. Windowing code has to change window size.
	/// </summary>
	///
	/// <param name="_width">Back-buffer width.</param>
	/// <param name="_height">Back-buffer height.</param>
	/// <param name="_flags">See: `BGFX_RESET_*` for more info.   - `BGFX_RESET_NONE` - No reset flags.   - `BGFX_RESET_FULLSCREEN` - Not supported yet.   - `BGFX_RESET_MSAA_X[2/4/8/16]` - Enable 2, 4, 8 or 16 x MSAA.   - `BGFX_RESET_VSYNC` - Enable V-Sync.   - `BGFX_RESET_MAXANISOTROPY` - Turn on/off max anisotropy.   - `BGFX_RESET_CAPTURE` - Begin screen capture.   - `BGFX_RESET_FLUSH_AFTER_RENDER` - Flush rendering after submitting to GPU.   - `BGFX_RESET_FLIP_AFTER_RENDER` - This flag  specifies where flip     occurs. Default behavior is that flip occurs before rendering new     frame. This flag only has effect when `BGFX_CONFIG_MULTITHREADED=0`.   - `BGFX_RESET_SRGB_BACKBUFFER` - Enable sRGB backbuffer.</param>
	/// <param name="_format">Texture format. See: `TextureFormat::Enum`.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_reset", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void reset(uint _width, uint _height, uint _flags, TextureFormat _format);
	
	/// <summary>
	/// Advance to next frame. When using multithreaded renderer, this call
	/// just swaps internal buffers, kicks render thread, and returns. In
	/// singlethreaded renderer this call does frame rendering.
	/// </summary>
	///
	/// <param name="_capture">Capture frame with graphics debugger.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_frame", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe uint frame(byte _capture);
	
	/// <summary>
	/// Returns current renderer backend API type.
	/// @remarks
	///   Library must be initialized.
	/// </summary>
	///
	[DllImport(DllName, EntryPoint="bgfx_get_renderer_type", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe RendererType get_renderer_type();
	
	/// <summary>
	/// Returns renderer capabilities.
	/// @remarks
	///   Library must be initialized.
	/// </summary>
	///
	[DllImport(DllName, EntryPoint="bgfx_get_caps", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe Caps* get_caps();
	
	/// <summary>
	/// Returns performance counters.
	/// @attention Pointer returned is valid until `bgfx::frame` is called.
	/// </summary>
	///
	[DllImport(DllName, EntryPoint="bgfx_get_stats", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe Stats* get_stats();
	
	/// <summary>
	/// Allocate buffer to pass to bgfx calls. Data will be freed inside bgfx.
	/// </summary>
	///
	/// <param name="_size">Size to allocate.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_alloc", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe Memory* alloc(uint _size);
	
	/// <summary>
	/// Allocate buffer and copy data into it. Data will be freed inside bgfx.
	/// </summary>
	///
	/// <param name="_data">Pointer to data to be copied.</param>
	/// <param name="_size">Size of data to be copied.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_copy", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe Memory* copy(void* _data, uint _size);
	
	/// <summary>
	/// Make reference to data to pass to bgfx. Unlike `bgfx::alloc`, this call
	/// doesn't allocate memory for data. It just copies the _data pointer. You
	/// can pass `ReleaseFn` function pointer to release this memory after it's
	/// consumed, otherwise you must make sure _data is available for at least 2
	/// `bgfx::frame` calls. `ReleaseFn` function must be able to be called
	/// from any thread.
	/// @attention Data passed must be available for at least 2 `bgfx::frame` calls.
	/// </summary>
	///
	/// <param name="_data">Pointer to data.</param>
	/// <param name="_size">Size of data.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_make_ref", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe Memory* make_ref(void* _data, uint _size);
	
	/// <summary>
	/// Make reference to data to pass to bgfx. Unlike `bgfx::alloc`, this call
	/// doesn't allocate memory for data. It just copies the _data pointer. You
	/// can pass `ReleaseFn` function pointer to release this memory after it's
	/// consumed, otherwise you must make sure _data is available for at least 2
	/// `bgfx::frame` calls. `ReleaseFn` function must be able to be called
	/// from any thread.
	/// @attention Data passed must be available for at least 2 `bgfx::frame` calls.
	/// </summary>
	///
	/// <param name="_data">Pointer to data.</param>
	/// <param name="_size">Size of data.</param>
	/// <param name="_releaseFn">Callback function to release memory after use.</param>
	/// <param name="_userData">User data to be passed to callback function.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_make_ref_release", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe Memory* make_ref_release(void* _data, uint _size, IntPtr _releaseFn, void* _userData);
	
	/// <summary>
	/// Set debug flags.
	/// </summary>
	///
	/// <param name="_debug">Available flags:   - `BGFX_DEBUG_IFH` - Infinitely fast hardware. When this flag is set     all rendering calls will be skipped. This is useful when profiling     to quickly assess potential bottlenecks between CPU and GPU.   - `BGFX_DEBUG_PROFILER` - Enable profiler.   - `BGFX_DEBUG_STATS` - Display internal statistics.   - `BGFX_DEBUG_TEXT` - Display debug text.   - `BGFX_DEBUG_WIREFRAME` - Wireframe rendering. All rendering     primitives will be rendered as lines.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_debug", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_debug(uint _debug);
	
	/// <summary>
	/// Clear internal debug text buffer.
	/// </summary>
	///
	/// <param name="_attr">Background color.</param>
	/// <param name="_small">Default 8x16 or 8x8 font.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_dbg_text_clear", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void dbg_text_clear(byte _attr, byte _small);
	
	/// <summary>
	/// Print formatted data to internal debug text character-buffer (VGA-compatible text mode).
	/// </summary>
	///
	/// <param name="_x">Position x from the left corner of the window.</param>
	/// <param name="_y">Position y from the top corner of the window.</param>
	/// <param name="_attr">Color palette. Where top 4-bits represent index of background, and bottom 4-bits represent foreground color from standard VGA text palette (ANSI escape codes).</param>
	/// <param name="_format">`printf` style format.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_dbg_text_printf", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void dbg_text_printf(ushort _x, ushort _y, byte _attr, [MarshalAs(UnmanagedType.LPStr)] string _format, [MarshalAs(UnmanagedType.LPStr)] string args );
	
	/// <summary>
	/// Print formatted data from variable argument list to internal debug text character-buffer (VGA-compatible text mode).
	/// </summary>
	///
	/// <param name="_x">Position x from the left corner of the window.</param>
	/// <param name="_y">Position y from the top corner of the window.</param>
	/// <param name="_attr">Color palette. Where top 4-bits represent index of background, and bottom 4-bits represent foreground color from standard VGA text palette (ANSI escape codes).</param>
	/// <param name="_format">`printf` style format.</param>
	/// <param name="_argList">Variable arguments list for format string.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_dbg_text_vprintf", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void dbg_text_vprintf(ushort _x, ushort _y, byte _attr, [MarshalAs(UnmanagedType.LPStr)] string _format, IntPtr _argList);
	
	/// <summary>
	/// Draw image into internal debug text buffer.
	/// </summary>
	///
	/// <param name="_x">Position x from the left corner of the window.</param>
	/// <param name="_y">Position y from the top corner of the window.</param>
	/// <param name="_width">Image width.</param>
	/// <param name="_height">Image height.</param>
	/// <param name="_data">Raw image data (character/attribute raw encoding).</param>
	/// <param name="_pitch">Image pitch in bytes.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_dbg_text_image", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void dbg_text_image(ushort _x, ushort _y, ushort _width, ushort _height, void* _data, ushort _pitch);
	
	/// <summary>
	/// Create static index buffer.
	/// </summary>
	///
	/// <param name="_mem">Index buffer data.</param>
	/// <param name="_flags">Buffer creation flags.   - `BGFX_BUFFER_NONE` - No flags.   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of       data is passed. If this flag is not specified, and more data is passed on update, the buffer       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic       buffers.   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on       index buffers.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_create_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe IndexBufferHandle create_index_buffer(Memory* _mem, ushort _flags);
	
	/// <summary>
	/// Set static index buffer debug name.
	/// </summary>
	///
	/// <param name="_handle">Static index buffer handle.</param>
	/// <param name="_name">Static index buffer name.</param>
	/// <param name="_len">Static index buffer name length (if length is INT32_MAX, it's expected that _name is zero terminated string.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_index_buffer_name", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_index_buffer_name(IndexBufferHandle _handle, [MarshalAs(UnmanagedType.LPStr)] string _name, int _len);
	
	/// <summary>
	/// Destroy static index buffer.
	/// </summary>
	///
	/// <param name="_handle">Static index buffer handle.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_destroy_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void destroy_index_buffer(IndexBufferHandle _handle);
	
	/// <summary>
	/// Create vertex declaration.
	/// </summary>
	///
	/// <param name="_decl">Vertex declaration.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_create_vertex_decl", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe VertexDeclHandle create_vertex_decl(VertexDecl* _decl);
	
	/// <summary>
	/// Destroy vertex declaration.
	/// </summary>
	///
	/// <param name="_handle">Vertex declaration handle.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_destroy_vertex_decl", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void destroy_vertex_decl(VertexDeclHandle _handle);
	
	/// <summary>
	/// Create static vertex buffer.
	/// </summary>
	///
	/// <param name="_mem">Vertex buffer data.</param>
	/// <param name="_decl">Vertex declaration.</param>
	/// <param name="_flags">Buffer creation flags.  - `BGFX_BUFFER_NONE` - No flags.  - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.  - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer      is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.  - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.  - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of      data is passed. If this flag is not specified, and more data is passed on update, the buffer      will be trimmed to fit the existing buffer size. This flag has effect only on dynamic buffers.  - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on index buffers.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_create_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe VertexBufferHandle create_vertex_buffer(Memory* _mem, VertexDecl* _decl, ushort _flags);
	
	/// <summary>
	/// Set static vertex buffer debug name.
	/// </summary>
	///
	/// <param name="_handle">Static vertex buffer handle.</param>
	/// <param name="_name">Static vertex buffer name.</param>
	/// <param name="_len">Static vertex buffer name length (if length is INT32_MAX, it's expected that _name is zero terminated string.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_vertex_buffer_name", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_vertex_buffer_name(VertexBufferHandle _handle, [MarshalAs(UnmanagedType.LPStr)] string _name, int _len);
	
	/// <summary>
	/// Destroy static vertex buffer.
	/// </summary>
	///
	/// <param name="_handle">Static vertex buffer handle.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_destroy_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void destroy_vertex_buffer(VertexBufferHandle _handle);
	
	/// <summary>
	/// Create empty dynamic index buffer.
	/// </summary>
	///
	/// <param name="_num">Number of indices.</param>
	/// <param name="_flags">Buffer creation flags.   - `BGFX_BUFFER_NONE` - No flags.   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of       data is passed. If this flag is not specified, and more data is passed on update, the buffer       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic       buffers.   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on       index buffers.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_create_dynamic_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe DynamicIndexBufferHandle create_dynamic_index_buffer(uint _num, ushort _flags);
	
	/// <summary>
	/// Create dynamic index buffer and initialized it.
	/// </summary>
	///
	/// <param name="_mem">Index buffer data.</param>
	/// <param name="_flags">Buffer creation flags.   - `BGFX_BUFFER_NONE` - No flags.   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of       data is passed. If this flag is not specified, and more data is passed on update, the buffer       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic       buffers.   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on       index buffers.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_create_dynamic_index_buffer_mem", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe DynamicIndexBufferHandle create_dynamic_index_buffer_mem(Memory* _mem, ushort _flags);
	
	/// <summary>
	/// Update dynamic index buffer.
	/// </summary>
	///
	/// <param name="_handle">Dynamic index buffer handle.</param>
	/// <param name="_startIndex">Start index.</param>
	/// <param name="_mem">Index buffer data.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_update_dynamic_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void update_dynamic_index_buffer(DynamicIndexBufferHandle _handle, uint _startIndex, Memory* _mem);
	
	/// <summary>
	/// Destroy dynamic index buffer.
	/// </summary>
	///
	/// <param name="_handle">Dynamic index buffer handle.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_destroy_dynamic_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void destroy_dynamic_index_buffer(DynamicIndexBufferHandle _handle);
	
	/// <summary>
	/// Create empty dynamic vertex buffer.
	/// </summary>
	///
	/// <param name="_num">Number of vertices.</param>
	/// <param name="_decl">Vertex declaration.</param>
	/// <param name="_flags">Buffer creation flags.   - `BGFX_BUFFER_NONE` - No flags.   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of       data is passed. If this flag is not specified, and more data is passed on update, the buffer       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic       buffers.   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on       index buffers.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_create_dynamic_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe DynamicVertexBufferHandle create_dynamic_vertex_buffer(uint _num, VertexDecl* _decl, ushort _flags);
	
	/// <summary>
	/// Create dynamic vertex buffer and initialize it.
	/// </summary>
	///
	/// <param name="_mem">Vertex buffer data.</param>
	/// <param name="_decl">Vertex declaration.</param>
	/// <param name="_flags">Buffer creation flags.   - `BGFX_BUFFER_NONE` - No flags.   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of       data is passed. If this flag is not specified, and more data is passed on update, the buffer       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic       buffers.   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on       index buffers.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_create_dynamic_vertex_buffer_mem", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe DynamicVertexBufferHandle create_dynamic_vertex_buffer_mem(Memory* _mem, VertexDecl* _decl, ushort _flags);
	
	/// <summary>
	/// Update dynamic vertex buffer.
	/// </summary>
	///
	/// <param name="_handle">Dynamic vertex buffer handle.</param>
	/// <param name="_startVertex">Start vertex.</param>
	/// <param name="_mem">Vertex buffer data.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_update_dynamic_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void update_dynamic_vertex_buffer(DynamicVertexBufferHandle _handle, uint _startVertex, Memory* _mem);
	
	/// <summary>
	/// Destroy dynamic vertex buffer.
	/// </summary>
	///
	/// <param name="_handle">Dynamic vertex buffer handle.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_destroy_dynamic_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void destroy_dynamic_vertex_buffer(DynamicVertexBufferHandle _handle);
	
	/// <summary>
	/// Returns number of requested or maximum available indices.
	/// </summary>
	///
	/// <param name="_num">Number of required indices.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_get_avail_transient_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe uint get_avail_transient_index_buffer(uint _num);
	
	/// <summary>
	/// Returns number of requested or maximum available vertices.
	/// </summary>
	///
	/// <param name="_num">Number of required vertices.</param>
	/// <param name="_decl">Vertex declaration.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_get_avail_transient_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe uint get_avail_transient_vertex_buffer(uint _num, VertexDecl* _decl);
	
	/// <summary>
	/// Returns number of requested or maximum available instance buffer slots.
	/// </summary>
	///
	/// <param name="_num">Number of required instances.</param>
	/// <param name="_stride">Stride per instance.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_get_avail_instance_data_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe uint get_avail_instance_data_buffer(uint _num, ushort _stride);
	
	/// <summary>
	/// Allocate transient index buffer.
	/// @remarks
	///   Only 16-bit index buffer is supported.
	/// </summary>
	///
	/// <param name="_tib">TransientIndexBuffer structure is filled and is valid for the duration of frame, and it can be reused for multiple draw calls.</param>
	/// <param name="_num">Number of indices to allocate.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_alloc_transient_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void alloc_transient_index_buffer(TransientIndexBuffer* _tib, uint _num);
	
	/// <summary>
	/// Allocate transient vertex buffer.
	/// </summary>
	///
	/// <param name="_tvb">TransientVertexBuffer structure is filled and is valid for the duration of frame, and it can be reused for multiple draw calls.</param>
	/// <param name="_num">Number of vertices to allocate.</param>
	/// <param name="_decl">Vertex declaration.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_alloc_transient_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void alloc_transient_vertex_buffer(TransientVertexBuffer* _tvb, uint _num, VertexDecl* _decl);
	
	/// <summary>
	/// Check for required space and allocate transient vertex and index
	/// buffers. If both space requirements are satisfied function returns
	/// true.
	/// @remarks
	///   Only 16-bit index buffer is supported.
	/// </summary>
	///
	/// <param name="_tvb">TransientVertexBuffer structure is filled and is valid for the duration of frame, and it can be reused for multiple draw calls.</param>
	/// <param name="_decl">Number of vertices to allocate.</param>
	/// <param name="_numVertices">Vertex declaration.</param>
	/// <param name="_tib">TransientIndexBuffer structure is filled and is valid for the duration of frame, and it can be reused for multiple draw calls.</param>
	/// <param name="_numIndices">Number of indices to allocate.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_alloc_transient_buffers", CallingConvention = CallingConvention.Cdecl)]
	[return: MarshalAs(UnmanagedType.I1)]
	public static extern unsafe byte alloc_transient_buffers(TransientVertexBuffer* _tvb, VertexDecl* _decl, uint _numVertices, TransientIndexBuffer* _tib, uint _numIndices);
	
	/// <summary>
	/// Allocate instance data buffer.
	/// </summary>
	///
	/// <param name="_idb">InstanceDataBuffer structure is filled and is valid for duration of frame, and it can be reused for multiple draw calls.</param>
	/// <param name="_num">Number of instances.</param>
	/// <param name="_stride">Instance stride. Must be multiple of 16.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_alloc_instance_data_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void alloc_instance_data_buffer(InstanceDataBuffer* _idb, uint _num, ushort _stride);
	
	/// <summary>
	/// Create draw indirect buffer.
	/// </summary>
	///
	/// <param name="_num">Number of indirect calls.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_create_indirect_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe IndirectBufferHandle create_indirect_buffer(uint _num);
	
	/// <summary>
	/// Destroy draw indirect buffer.
	/// </summary>
	///
	/// <param name="_handle">Indirect buffer handle.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_destroy_indirect_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void destroy_indirect_buffer(IndirectBufferHandle _handle);
	
	/// <summary>
	/// Create shader from memory buffer.
	/// </summary>
	///
	/// <param name="_mem">Shader binary.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_create_shader", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe ShaderHandle create_shader(Memory* _mem);
	
	/// <summary>
	/// Returns the number of uniforms and uniform handles used inside a shader.
	/// @remarks
	///   Only non-predefined uniforms are returned.
	/// </summary>
	///
	/// <param name="_handle">Shader handle.</param>
	/// <param name="_uniforms">UniformHandle array where data will be stored.</param>
	/// <param name="_max">Maximum capacity of array.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_get_shader_uniforms", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe ushort get_shader_uniforms(ShaderHandle _handle, UniformHandle* _uniforms, ushort _max);
	
	/// <summary>
	/// Set shader debug name.
	/// </summary>
	///
	/// <param name="_handle">Shader handle.</param>
	/// <param name="_name">Shader name.</param>
	/// <param name="_len">Shader name length (if length is INT32_MAX, it's expected that _name is zero terminated string).</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_shader_name", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_shader_name(ShaderHandle _handle, [MarshalAs(UnmanagedType.LPStr)] string _name, int _len);
	
	/// <summary>
	/// Destroy shader.
	/// @remark Once a shader program is created with _handle,
	///   it is safe to destroy that shader.
	/// </summary>
	///
	/// <param name="_handle">Shader handle.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_destroy_shader", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void destroy_shader(ShaderHandle _handle);
	
	/// <summary>
	/// Create program with vertex and fragment shaders.
	/// </summary>
	///
	/// <param name="_vsh">Vertex shader.</param>
	/// <param name="_fsh">Fragment shader.</param>
	/// <param name="_destroyShaders">If true, shaders will be destroyed when program is destroyed.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_create_program", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe ProgramHandle create_program(ShaderHandle _vsh, ShaderHandle _fsh, byte _destroyShaders);
	
	/// <summary>
	/// Create program with compute shader.
	/// </summary>
	///
	/// <param name="_csh">Compute shader.</param>
	/// <param name="_destroyShaders">If true, shaders will be destroyed when program is destroyed.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_create_compute_program", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe ProgramHandle create_compute_program(ShaderHandle _csh, byte _destroyShaders);
	
	/// <summary>
	/// Destroy program.
	/// </summary>
	///
	/// <param name="_handle">Program handle.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_destroy_program", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void destroy_program(ProgramHandle _handle);
	
	/// <summary>
	/// Validate texture parameters.
	/// </summary>
	///
	/// <param name="_depth">Depth dimension of volume texture.</param>
	/// <param name="_cubeMap">Indicates that texture contains cubemap.</param>
	/// <param name="_numLayers">Number of layers in texture array.</param>
	/// <param name="_format">Texture format. See: `TextureFormat::Enum`.</param>
	/// <param name="_flags">Texture flags. See `BGFX_TEXTURE_*`.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_is_texture_valid", CallingConvention = CallingConvention.Cdecl)]
	[return: MarshalAs(UnmanagedType.I1)]
	public static extern unsafe byte is_texture_valid(ushort _depth, byte _cubeMap, ushort _numLayers, TextureFormat _format, ulong _flags);
	
	/// <summary>
	/// Calculate amount of memory required for texture.
	/// </summary>
	///
	/// <param name="_info">Resulting texture info structure. See: `TextureInfo`.</param>
	/// <param name="_width">Width.</param>
	/// <param name="_height">Height.</param>
	/// <param name="_depth">Depth dimension of volume texture.</param>
	/// <param name="_cubeMap">Indicates that texture contains cubemap.</param>
	/// <param name="_hasMips">Indicates that texture contains full mip-map chain.</param>
	/// <param name="_numLayers">Number of layers in texture array.</param>
	/// <param name="_format">Texture format. See: `TextureFormat::Enum`.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_calc_texture_size", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void calc_texture_size(TextureInfo* _info, ushort _width, ushort _height, ushort _depth, byte _cubeMap, byte _hasMips, ushort _numLayers, TextureFormat _format);
	
	/// <summary>
	/// Create texture from memory buffer.
	/// </summary>
	///
	/// <param name="_mem">DDS, KTX or PVR texture binary data.</param>
	/// <param name="_flags">Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`) flags. Default texture sampling mode is linear, and wrap mode is repeat. - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap   mode. - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic   sampling.</param>
	/// <param name="_skip">Skip top level mips when parsing texture.</param>
	/// <param name="_info">When non-`NULL` is specified it returns parsed texture information.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_create_texture", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe TextureHandle create_texture(Memory* _mem, ulong _flags, byte _skip, TextureInfo* _info);
	
	/// <summary>
	/// Create 2D texture.
	/// </summary>
	///
	/// <param name="_width">Width.</param>
	/// <param name="_height">Height.</param>
	/// <param name="_hasMips">Indicates that texture contains full mip-map chain.</param>
	/// <param name="_numLayers">Number of layers in texture array. Must be 1 if caps `BGFX_CAPS_TEXTURE_2D_ARRAY` flag is not set.</param>
	/// <param name="_format">Texture format. See: `TextureFormat::Enum`.</param>
	/// <param name="_flags">Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`) flags. Default texture sampling mode is linear, and wrap mode is repeat. - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap   mode. - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic   sampling.</param>
	/// <param name="_mem">Texture data. If `_mem` is non-NULL, created texture will be immutable. If `_mem` is NULL content of the texture is uninitialized. When `_numLayers` is more than 1, expected memory layout is texture and all mips together for each array element.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_create_texture_2d", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe TextureHandle create_texture_2d(ushort _width, ushort _height, byte _hasMips, ushort _numLayers, TextureFormat _format, ulong _flags, Memory* _mem);
	
	/// <summary>
	/// Create texture with size based on backbuffer ratio. Texture will maintain ratio
	/// if back buffer resolution changes.
	/// </summary>
	///
	/// <param name="_ratio">Texture size in respect to back-buffer size. See: `BackbufferRatio::Enum`.</param>
	/// <param name="_hasMips">Indicates that texture contains full mip-map chain.</param>
	/// <param name="_numLayers">Number of layers in texture array. Must be 1 if caps `BGFX_CAPS_TEXTURE_2D_ARRAY` flag is not set.</param>
	/// <param name="_format">Texture format. See: `TextureFormat::Enum`.</param>
	/// <param name="_flags">Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`) flags. Default texture sampling mode is linear, and wrap mode is repeat. - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap   mode. - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic   sampling.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_create_texture_2d_scaled", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe TextureHandle create_texture_2d_scaled(BackbufferRatio _ratio, byte _hasMips, ushort _numLayers, TextureFormat _format, ulong _flags);
	
	/// <summary>
	/// Create 3D texture.
	/// </summary>
	///
	/// <param name="_width">Width.</param>
	/// <param name="_height">Height.</param>
	/// <param name="_depth">Depth.</param>
	/// <param name="_hasMips">Indicates that texture contains full mip-map chain.</param>
	/// <param name="_format">Texture format. See: `TextureFormat::Enum`.</param>
	/// <param name="_flags">Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`) flags. Default texture sampling mode is linear, and wrap mode is repeat. - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap   mode. - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic   sampling.</param>
	/// <param name="_mem">Texture data. If `_mem` is non-NULL, created texture will be immutable. If `_mem` is NULL content of the texture is uninitialized. When `_numLayers` is more than 1, expected memory layout is texture and all mips together for each array element.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_create_texture_3d", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe TextureHandle create_texture_3d(ushort _width, ushort _height, ushort _depth, byte _hasMips, TextureFormat _format, ulong _flags, Memory* _mem);
	
	/// <summary>
	/// Create Cube texture.
	/// </summary>
	///
	/// <param name="_size">Cube side size.</param>
	/// <param name="_hasMips">Indicates that texture contains full mip-map chain.</param>
	/// <param name="_numLayers">Number of layers in texture array. Must be 1 if caps `BGFX_CAPS_TEXTURE_2D_ARRAY` flag is not set.</param>
	/// <param name="_format">Texture format. See: `TextureFormat::Enum`.</param>
	/// <param name="_flags">Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`) flags. Default texture sampling mode is linear, and wrap mode is repeat. - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap   mode. - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic   sampling.</param>
	/// <param name="_mem">Texture data. If `_mem` is non-NULL, created texture will be immutable. If `_mem` is NULL content of the texture is uninitialized. When `_numLayers` is more than 1, expected memory layout is texture and all mips together for each array element.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_create_texture_cube", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe TextureHandle create_texture_cube(ushort _size, byte _hasMips, ushort _numLayers, TextureFormat _format, ulong _flags, Memory* _mem);
	
	/// <summary>
	/// Update 2D texture.
	/// @attention It's valid to update only mutable texture. See `bgfx::createTexture2D` for more info.
	/// </summary>
	///
	/// <param name="_handle">Texture handle.</param>
	/// <param name="_layer">Layer in texture array.</param>
	/// <param name="_mip">Mip level.</param>
	/// <param name="_x">X offset in texture.</param>
	/// <param name="_y">Y offset in texture.</param>
	/// <param name="_width">Width of texture block.</param>
	/// <param name="_height">Height of texture block.</param>
	/// <param name="_mem">Texture update data.</param>
	/// <param name="_pitch">Pitch of input image (bytes). When _pitch is set to UINT16_MAX, it will be calculated internally based on _width.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_update_texture_2d", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void update_texture_2d(TextureHandle _handle, ushort _layer, byte _mip, ushort _x, ushort _y, ushort _width, ushort _height, Memory* _mem, ushort _pitch);
	
	/// <summary>
	/// Update 3D texture.
	/// @attention It's valid to update only mutable texture. See `bgfx::createTexture3D` for more info.
	/// </summary>
	///
	/// <param name="_handle">Texture handle.</param>
	/// <param name="_mip">Mip level.</param>
	/// <param name="_x">X offset in texture.</param>
	/// <param name="_y">Y offset in texture.</param>
	/// <param name="_z">Z offset in texture.</param>
	/// <param name="_width">Width of texture block.</param>
	/// <param name="_height">Height of texture block.</param>
	/// <param name="_depth">Depth of texture block.</param>
	/// <param name="_mem">Texture update data.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_update_texture_3d", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void update_texture_3d(TextureHandle _handle, byte _mip, ushort _x, ushort _y, ushort _z, ushort _width, ushort _height, ushort _depth, Memory* _mem);
	
	/// <summary>
	/// Update Cube texture.
	/// @attention It's valid to update only mutable texture. See `bgfx::createTextureCube` for more info.
	/// </summary>
	///
	/// <param name="_handle">Texture handle.</param>
	/// <param name="_layer">Layer in texture array.</param>
	/// <param name="_side">Cubemap side `BGFX_CUBE_MAP_<POSITIVE or NEGATIVE>_<X, Y or Z>`,   where 0 is +X, 1 is -X, 2 is +Y, 3 is -Y, 4 is +Z, and 5 is -Z.                  +----------+                  |-z       2|                  | ^  +y    |                  | |        |    Unfolded cube:                  | +---->+x |       +----------+----------+----------+----------+       |+y       1|+y       4|+y       0|+y       5|       | ^  -x    | ^  +z    | ^  +x    | ^  -z    |       | |        | |        | |        | |        |       | +---->+z | +---->+x | +---->-z | +---->-x |       +----------+----------+----------+----------+                  |+z       3|                  | ^  -y    |                  | |        |                  | +---->+x |                  +----------+</param>
	/// <param name="_mip">Mip level.</param>
	/// <param name="_x">X offset in texture.</param>
	/// <param name="_y">Y offset in texture.</param>
	/// <param name="_width">Width of texture block.</param>
	/// <param name="_height">Height of texture block.</param>
	/// <param name="_mem">Texture update data.</param>
	/// <param name="_pitch">Pitch of input image (bytes). When _pitch is set to UINT16_MAX, it will be calculated internally based on _width.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_update_texture_cube", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void update_texture_cube(TextureHandle _handle, ushort _layer, byte _side, byte _mip, ushort _x, ushort _y, ushort _width, ushort _height, Memory* _mem, ushort _pitch);
	
	/// <summary>
	/// Read back texture content.
	/// @attention Texture must be created with `BGFX_TEXTURE_READ_BACK` flag.
	/// @attention Availability depends on: `BGFX_CAPS_TEXTURE_READ_BACK`.
	/// </summary>
	///
	/// <param name="_handle">Texture handle.</param>
	/// <param name="_data">Destination buffer.</param>
	/// <param name="_mip">Mip level.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_read_texture", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe uint read_texture(TextureHandle _handle, void* _data, byte _mip);
	
	/// <summary>
	/// Set texture debug name.
	/// </summary>
	///
	/// <param name="_handle">Texture handle.</param>
	/// <param name="_name">Texture name.</param>
	/// <param name="_len">Texture name length (if length is INT32_MAX, it's expected that _name is zero terminated string.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_texture_name", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_texture_name(TextureHandle _handle, [MarshalAs(UnmanagedType.LPStr)] string _name, int _len);
	
	/// <summary>
	/// Returns texture direct access pointer.
	/// @attention Availability depends on: `BGFX_CAPS_TEXTURE_DIRECT_ACCESS`. This feature
	///   is available on GPUs that have unified memory architecture (UMA) support.
	/// </summary>
	///
	/// <param name="_handle">Texture handle.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_get_direct_access_ptr", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void* get_direct_access_ptr(TextureHandle _handle);
	
	/// <summary>
	/// Destroy texture.
	/// </summary>
	///
	/// <param name="_handle">Texture handle.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_destroy_texture", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void destroy_texture(TextureHandle _handle);
	
	/// <summary>
	/// Create frame buffer (simple).
	/// </summary>
	///
	/// <param name="_width">Texture width.</param>
	/// <param name="_height">Texture height.</param>
	/// <param name="_format">Texture format. See: `TextureFormat::Enum`.</param>
	/// <param name="_textureFlags">Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`) flags. Default texture sampling mode is linear, and wrap mode is repeat. - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap   mode. - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic   sampling.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_create_frame_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe FrameBufferHandle create_frame_buffer(ushort _width, ushort _height, TextureFormat _format, ulong _textureFlags);
	
	/// <summary>
	/// Create frame buffer with size based on backbuffer ratio. Frame buffer will maintain ratio
	/// if back buffer resolution changes.
	/// </summary>
	///
	/// <param name="_ratio">Frame buffer size in respect to back-buffer size. See: `BackbufferRatio::Enum`.</param>
	/// <param name="_format">Texture format. See: `TextureFormat::Enum`.</param>
	/// <param name="_textureFlags">Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`) flags. Default texture sampling mode is linear, and wrap mode is repeat. - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap   mode. - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic   sampling.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_create_frame_buffer_scaled", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe FrameBufferHandle create_frame_buffer_scaled(BackbufferRatio _ratio, TextureFormat _format, ulong _textureFlags);
	
	/// <summary>
	/// Create MRT frame buffer from texture handles (simple).
	/// </summary>
	///
	/// <param name="_num">Number of texture handles.</param>
	/// <param name="_handles">Texture attachments.</param>
	/// <param name="_destroyTexture">If true, textures will be destroyed when frame buffer is destroyed.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_create_frame_buffer_from_handles", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe FrameBufferHandle create_frame_buffer_from_handles(byte _num, TextureHandle* _handles, byte _destroyTexture);
	
	/// <summary>
	/// Create MRT frame buffer from texture handles with specific layer and
	/// mip level.
	/// </summary>
	///
	/// <param name="_num">Number of attachements.</param>
	/// <param name="_attachment">Attachment texture info. See: `bgfx::Attachment`.</param>
	/// <param name="_destroyTexture">If true, textures will be destroyed when frame buffer is destroyed.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_create_frame_buffer_from_attachment", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe FrameBufferHandle create_frame_buffer_from_attachment(byte _num, Attachment* _attachment, byte _destroyTexture);
	
	/// <summary>
	/// Create frame buffer for multiple window rendering.
	/// @remarks
	///   Frame buffer cannot be used for sampling.
	/// @attention Availability depends on: `BGFX_CAPS_SWAP_CHAIN`.
	/// </summary>
	///
	/// <param name="_nwh">OS' target native window handle.</param>
	/// <param name="_width">Window back buffer width.</param>
	/// <param name="_height">Window back buffer height.</param>
	/// <param name="_format">Window back buffer color format.</param>
	/// <param name="_depthFormat">Window back buffer depth format.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_create_frame_buffer_from_nwh", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe FrameBufferHandle create_frame_buffer_from_nwh(void* _nwh, ushort _width, ushort _height, TextureFormat _format, TextureFormat _depthFormat);
	
	/// <summary>
	/// Set frame buffer debug name.
	/// </summary>
	///
	/// <param name="_handle">Frame buffer handle.</param>
	/// <param name="_name">Frame buffer name.</param>
	/// <param name="_len">Frame buffer name length (if length is INT32_MAX, it's expected that _name is zero terminated string.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_frame_buffer_name", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_frame_buffer_name(FrameBufferHandle _handle, [MarshalAs(UnmanagedType.LPStr)] string _name, int _len);
	
	/// <summary>
	/// Obtain texture handle of frame buffer attachment.
	/// </summary>
	///
	/// <param name="_handle">Frame buffer handle.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_get_texture", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe TextureHandle get_texture(FrameBufferHandle _handle, byte _attachment);
	
	/// <summary>
	/// Destroy frame buffer.
	/// </summary>
	///
	/// <param name="_handle">Frame buffer handle.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_destroy_frame_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void destroy_frame_buffer(FrameBufferHandle _handle);
	
	/// <summary>
	/// Create shader uniform parameter.
	/// @remarks
	///   1. Uniform names are unique. It's valid to call `bgfx::createUniform`
	///      multiple times with the same uniform name. The library will always
	///      return the same handle, but the handle reference count will be
	///      incremented. This means that the same number of `bgfx::destroyUniform`
	///      must be called to properly destroy the uniform.
	///   2. Predefined uniforms (declared in `bgfx_shader.sh`):
	///      - `u_viewRect vec4(x, y, width, height)` - view rectangle for current
	///        view, in pixels.
	///      - `u_viewTexel vec4(1.0/width, 1.0/height, undef, undef)` - inverse
	///        width and height
	///      - `u_view mat4` - view matrix
	///      - `u_invView mat4` - inverted view matrix
	///      - `u_proj mat4` - projection matrix
	///      - `u_invProj mat4` - inverted projection matrix
	///      - `u_viewProj mat4` - concatenated view projection matrix
	///      - `u_invViewProj mat4` - concatenated inverted view projection matrix
	///      - `u_model mat4[BGFX_CONFIG_MAX_BONES]` - array of model matrices.
	///      - `u_modelView mat4` - concatenated model view matrix, only first
	///        model matrix from array is used.
	///      - `u_modelViewProj mat4` - concatenated model view projection matrix.
	///      - `u_alphaRef float` - alpha reference value for alpha test.
	/// </summary>
	///
	/// <param name="_name">Uniform name in shader.</param>
	/// <param name="_type">Type of uniform (See: `bgfx::UniformType`).</param>
	/// <param name="_num">Number of elements in array.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_create_uniform", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe UniformHandle create_uniform([MarshalAs(UnmanagedType.LPStr)] string _name, UniformType _type, ushort _num);
	
	/// <summary>
	/// Retrieve uniform info.
	/// </summary>
	///
	/// <param name="_handle">Handle to uniform object.</param>
	/// <param name="_info">Uniform info.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_get_uniform_info", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void get_uniform_info(UniformHandle _handle, UniformInfo* _info);
	
	/// <summary>
	/// Destroy shader uniform parameter.
	/// </summary>
	///
	/// <param name="_handle">Handle to uniform object.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_destroy_uniform", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void destroy_uniform(UniformHandle _handle);
	
	/// <summary>
	/// Create occlusion query.
	/// </summary>
	///
	[DllImport(DllName, EntryPoint="bgfx_create_occlusion_query", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe OcclusionQueryHandle create_occlusion_query();
	
	/// <summary>
	/// Retrieve occlusion query result from previous frame.
	/// </summary>
	///
	/// <param name="_handle">Handle to occlusion query object.</param>
	/// <param name="_result">Number of pixels that passed test. This argument can be `NULL` if result of occlusion query is not needed.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_get_result", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe OcclusionQueryResult get_result(OcclusionQueryHandle _handle, int* _result);
	
	/// <summary>
	/// Destroy occlusion query.
	/// </summary>
	///
	/// <param name="_handle">Handle to occlusion query object.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_destroy_occlusion_query", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void destroy_occlusion_query(OcclusionQueryHandle _handle);
	
	/// <summary>
	/// Set palette color value.
	/// </summary>
	///
	/// <param name="_index">Index into palette.</param>
	/// <param name="_rgba">RGBA floating point values.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_palette_color", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_palette_color(byte _index, float _rgba);
	
	/// <summary>
	/// Set palette color value.
	/// </summary>
	///
	/// <param name="_index">Index into palette.</param>
	/// <param name="_rgba">Packed 32-bit RGBA value.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_palette_color_rgba8", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_palette_color_rgba8(byte _index, uint _rgba);
	
	/// <summary>
	/// Set view name.
	/// @remarks
	///   This is debug only feature.
	///   In graphics debugger view name will appear as:
	///       "nnnc <view name>"
	///        ^  ^ ^
	///        |  +--- compute (C)
	///        +------ view id
	/// </summary>
	///
	/// <param name="_id">View id.</param>
	/// <param name="_name">View name.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_view_name", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_view_name(ushort _id, [MarshalAs(UnmanagedType.LPStr)] string _name);
	
	/// <summary>
	/// Set view rectangle. Draw primitive outside view will be clipped.
	/// </summary>
	///
	/// <param name="_id">View id.</param>
	/// <param name="_x">Position x from the left corner of the window.</param>
	/// <param name="_y">Position y from the top corner of the window.</param>
	/// <param name="_width">Width of view port region.</param>
	/// <param name="_height">Height of view port region.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_view_rect", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_view_rect(ushort _id, ushort _x, ushort _y, ushort _width, ushort _height);
	
	/// <summary>
	/// Set view rectangle. Draw primitive outside view will be clipped.
	/// </summary>
	///
	/// <param name="_id">View id.</param>
	/// <param name="_x">Position x from the left corner of the window.</param>
	/// <param name="_y">Position y from the top corner of the window.</param>
	/// <param name="_ratio">Width and height will be set in respect to back-buffer size. See: `BackbufferRatio::Enum`.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_view_rect_ratio", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_view_rect_ratio(ushort _id, ushort _x, ushort _y, BackbufferRatio _ratio);
	
	/// <summary>
	/// Set view scissor. Draw primitive outside view will be clipped. When
	/// _x, _y, _width and _height are set to 0, scissor will be disabled.
	/// </summary>
	///
	/// <param name="_id">View id.</param>
	/// <param name="_x">Position x from the left corner of the window.</param>
	/// <param name="_y">Position y from the top corner of the window.</param>
	/// <param name="_width">Width of view scissor region.</param>
	/// <param name="_height">Height of view scissor region.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_view_scissor", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_view_scissor(ushort _id, ushort _x, ushort _y, ushort _width, ushort _height);
	
	/// <summary>
	/// Set view clear flags.
	/// </summary>
	///
	/// <param name="_id">View id.</param>
	/// <param name="_flags">Clear flags. Use `BGFX_CLEAR_NONE` to remove any clear operation. See: `BGFX_CLEAR_*`.</param>
	/// <param name="_rgba">Color clear value.</param>
	/// <param name="_depth">Depth clear value.</param>
	/// <param name="_stencil">Stencil clear value.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_view_clear", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_view_clear(ushort _id, ushort _flags, uint _rgba, float _depth, byte _stencil);
	
	/// <summary>
	/// Set view clear flags with different clear color for each
	/// frame buffer texture. Must use `bgfx::setPaletteColor` to setup clear color
	/// palette.
	/// </summary>
	///
	/// <param name="_id">View id.</param>
	/// <param name="_flags">Clear flags. Use `BGFX_CLEAR_NONE` to remove any clear operation. See: `BGFX_CLEAR_*`.</param>
	/// <param name="_depth">Depth clear value.</param>
	/// <param name="_stencil">Stencil clear value.</param>
	/// <param name="_c0">Palette index for frame buffer attachment 0.</param>
	/// <param name="_c1">Palette index for frame buffer attachment 1.</param>
	/// <param name="_c2">Palette index for frame buffer attachment 2.</param>
	/// <param name="_c3">Palette index for frame buffer attachment 3.</param>
	/// <param name="_c4">Palette index for frame buffer attachment 4.</param>
	/// <param name="_c5">Palette index for frame buffer attachment 5.</param>
	/// <param name="_c6">Palette index for frame buffer attachment 6.</param>
	/// <param name="_c7">Palette index for frame buffer attachment 7.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_view_clear_mrt", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_view_clear_mrt(ushort _id, ushort _flags, float _depth, byte _stencil, byte _c0, byte _c1, byte _c2, byte _c3, byte _c4, byte _c5, byte _c6, byte _c7);
	
	/// <summary>
	/// Set view sorting mode.
	/// @remarks
	///   View mode must be set prior calling `bgfx::submit` for the view.
	/// </summary>
	///
	/// <param name="_id">View id.</param>
	/// <param name="_mode">View sort mode. See `ViewMode::Enum`.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_view_mode", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_view_mode(ushort _id, ViewMode _mode);
	
	/// <summary>
	/// Set view frame buffer.
	/// @remarks
	///   Not persistent after `bgfx::reset` call.
	/// </summary>
	///
	/// <param name="_id">View id.</param>
	/// <param name="_handle">Frame buffer handle. Passing `BGFX_INVALID_HANDLE` as frame buffer handle will draw primitives from this view into default back buffer.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_view_frame_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_view_frame_buffer(ushort _id, FrameBufferHandle _handle);
	
	/// <summary>
	/// Set view view and projection matrices, all draw primitives in this
	/// view will use these matrices.
	/// </summary>
	///
	/// <param name="_id">View id.</param>
	/// <param name="_view">View matrix.</param>
	/// <param name="_proj">Projection matrix.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_view_transform", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_view_transform(ushort _id, void* _view, void* _proj);
	
	/// <summary>
	/// Post submit view reordering.
	/// </summary>
	///
	/// <param name="_id">First view id.</param>
	/// <param name="_num">Number of views to remap.</param>
	/// <param name="_order">View remap id table. Passing `NULL` will reset view ids to default state.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_view_order", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_view_order(ushort _id, ushort _num, ushort* _order);
	
	/// <summary>
	/// Begin submitting draw calls from thread.
	/// </summary>
	///
	/// <param name="_forThread">Explicitly request an encoder for a worker thread.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_begin", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe Encoder* encoder_begin(byte _forThread);
	
	/// <summary>
	/// End submitting draw calls from thread.
	/// </summary>
	///
	/// <param name="_encoder">Encoder.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_end", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void encoder_end(Encoder* _encoder);
	
	/// <summary>
	/// Sets a debug marker. This allows you to group graphics calls together for easy browsing in
	/// graphics debugging tools.
	/// </summary>
	///
	/// <param name="_marker">Marker string.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_marker", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void encoder_set_marker(Encoder* _this, [MarshalAs(UnmanagedType.LPStr)] string _marker);
	
	/// <summary>
	/// Set render states for draw primitive.
	/// @remarks
	///   1. To setup more complex states use:
	///      `BGFX_STATE_ALPHA_REF(_ref)`,
	///      `BGFX_STATE_POINT_SIZE(_size)`,
	///      `BGFX_STATE_BLEND_FUNC(_src, _dst)`,
	///      `BGFX_STATE_BLEND_FUNC_SEPARATE(_srcRGB, _dstRGB, _srcA, _dstA)`,
	///      `BGFX_STATE_BLEND_EQUATION(_equation)`,
	///      `BGFX_STATE_BLEND_EQUATION_SEPARATE(_equationRGB, _equationA)`
	///   2. `BGFX_STATE_BLEND_EQUATION_ADD` is set when no other blend
	///      equation is specified.
	/// </summary>
	///
	/// <param name="_state">State flags. Default state for primitive type is   triangles. See: `BGFX_STATE_DEFAULT`.   - `BGFX_STATE_DEPTH_TEST_*` - Depth test function.   - `BGFX_STATE_BLEND_*` - See remark 1 about BGFX_STATE_BLEND_FUNC.   - `BGFX_STATE_BLEND_EQUATION_*` - See remark 2.   - `BGFX_STATE_CULL_*` - Backface culling mode.   - `BGFX_STATE_WRITE_*` - Enable R, G, B, A or Z write.   - `BGFX_STATE_MSAA` - Enable hardware multisample antialiasing.   - `BGFX_STATE_PT_[TRISTRIP/LINES/POINTS]` - Primitive type.</param>
	/// <param name="_rgba">Sets blend factor used by `BGFX_STATE_BLEND_FACTOR` and   `BGFX_STATE_BLEND_INV_FACTOR` blend modes.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_state", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void encoder_set_state(Encoder* _this, ulong _state, uint _rgba);
	
	/// <summary>
	/// Set condition for rendering.
	/// </summary>
	///
	/// <param name="_handle">Occlusion query handle.</param>
	/// <param name="_visible">Render if occlusion query is visible.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_condition", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void encoder_set_condition(Encoder* _this, OcclusionQueryHandle _handle, byte _visible);
	
	/// <summary>
	/// Set stencil test state.
	/// </summary>
	///
	/// <param name="_fstencil">Front stencil state.</param>
	/// <param name="_bstencil">Back stencil state. If back is set to `BGFX_STENCIL_NONE` _fstencil is applied to both front and back facing primitives.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_stencil", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void encoder_set_stencil(Encoder* _this, uint _fstencil, uint _bstencil);
	
	/// <summary>
	/// Set scissor for draw primitive.
	/// @remark
	///   To scissor for all primitives in view see `bgfx::setViewScissor`.
	/// </summary>
	///
	/// <param name="_x">Position x from the left corner of the window.</param>
	/// <param name="_y">Position y from the top corner of the window.</param>
	/// <param name="_width">Width of view scissor region.</param>
	/// <param name="_height">Height of view scissor region.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_scissor", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe ushort encoder_set_scissor(Encoder* _this, ushort _x, ushort _y, ushort _width, ushort _height);
	
	/// <summary>
	/// Set scissor from cache for draw primitive.
	/// @remark
	///   To scissor for all primitives in view see `bgfx::setViewScissor`.
	/// </summary>
	///
	/// <param name="_cache">Index in scissor cache.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_scissor_cached", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void encoder_set_scissor_cached(Encoder* _this, ushort _cache);
	
	/// <summary>
	/// Set model matrix for draw primitive. If it is not called,
	/// the model will be rendered with an identity model matrix.
	/// </summary>
	///
	/// <param name="_mtx">Pointer to first matrix in array.</param>
	/// <param name="_num">Number of matrices in array.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_transform", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe uint encoder_set_transform(Encoder* _this, void* _mtx, ushort _num);
	
	/// <summary>
	///  Set model matrix from matrix cache for draw primitive.
	/// </summary>
	///
	/// <param name="_cache">Index in matrix cache.</param>
	/// <param name="_num">Number of matrices from cache.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_transform_cached", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void encoder_set_transform_cached(Encoder* _this, uint _cache, ushort _num);
	
	/// <summary>
	/// Reserve matrices in internal matrix cache.
	/// @attention Pointer returned can be modifed until `bgfx::frame` is called.
	/// </summary>
	///
	/// <param name="_transform">Pointer to `Transform` structure.</param>
	/// <param name="_num">Number of matrices.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_alloc_transform", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe uint encoder_alloc_transform(Encoder* _this, Transform* _transform, ushort _num);
	
	/// <summary>
	/// Set shader uniform parameter for draw primitive.
	/// </summary>
	///
	/// <param name="_handle">Uniform.</param>
	/// <param name="_value">Pointer to uniform data.</param>
	/// <param name="_num">Number of elements. Passing `UINT16_MAX` will use the _num passed on uniform creation.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_uniform", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void encoder_set_uniform(Encoder* _this, UniformHandle _handle, void* _value, ushort _num);
	
	/// <summary>
	/// Set index buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_handle">Index buffer.</param>
	/// <param name="_firstIndex">First index to render.</param>
	/// <param name="_numIndices">Number of indices to render.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void encoder_set_index_buffer(Encoder* _this, IndexBufferHandle _handle, uint _firstIndex, uint _numIndices);
	
	/// <summary>
	/// Set index buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_handle">Dynamic index buffer.</param>
	/// <param name="_firstIndex">First index to render.</param>
	/// <param name="_numIndices">Number of indices to render.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_dynamic_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void encoder_set_dynamic_index_buffer(Encoder* _this, DynamicIndexBufferHandle _handle, uint _firstIndex, uint _numIndices);
	
	/// <summary>
	/// Set index buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_tib">Transient index buffer.</param>
	/// <param name="_firstIndex">First index to render.</param>
	/// <param name="_numIndices">Number of indices to render.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_transient_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void encoder_set_transient_index_buffer(Encoder* _this, TransientIndexBuffer* _tib, uint _firstIndex, uint _numIndices);
	
	/// <summary>
	/// Set vertex buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_stream">Vertex stream.</param>
	/// <param name="_handle">Vertex buffer.</param>
	/// <param name="_startVertex">First vertex to render.</param>
	/// <param name="_numVertices">Number of vertices to render.</param>
	/// <param name="_declHandle">VertexDecl handle for aliasing vertex buffer.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void encoder_set_vertex_buffer(Encoder* _this, byte _stream, VertexBufferHandle _handle, uint _startVertex, uint _numVertices, VertexDeclHandle _declHandle);
	
	/// <summary>
	/// Set vertex buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_stream">Vertex stream.</param>
	/// <param name="_handle">Dynamic vertex buffer.</param>
	/// <param name="_startVertex">First vertex to render.</param>
	/// <param name="_numVertices">Number of vertices to render.</param>
	/// <param name="_declHandle">VertexDecl handle for aliasing vertex buffer.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_dynamic_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void encoder_set_dynamic_vertex_buffer(Encoder* _this, byte _stream, DynamicVertexBufferHandle _handle, uint _startVertex, uint _numVertices, VertexDeclHandle _declHandle);
	
	/// <summary>
	/// Set vertex buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_stream">Vertex stream.</param>
	/// <param name="_tvb">Transient vertex buffer.</param>
	/// <param name="_startVertex">First vertex to render.</param>
	/// <param name="_numVertices">Number of vertices to render.</param>
	/// <param name="_declHandle">VertexDecl handle for aliasing vertex buffer.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_transient_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void encoder_set_transient_vertex_buffer(Encoder* _this, byte _stream, TransientVertexBuffer* _tvb, uint _startVertex, uint _numVertices, VertexDeclHandle _declHandle);
	
	/// <summary>
	/// Set number of vertices for auto generated vertices use in conjuction
	/// with gl_VertexID.
	/// @attention Availability depends on: `BGFX_CAPS_VERTEX_ID`.
	/// </summary>
	///
	/// <param name="_numVertices">Number of vertices.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_vertex_count", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void encoder_set_vertex_count(Encoder* _this, uint _numVertices);
	
	/// <summary>
	/// Set instance data buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_idb">Transient instance data buffer.</param>
	/// <param name="_start">First instance data.</param>
	/// <param name="_num">Number of data instances.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_instance_data_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void encoder_set_instance_data_buffer(Encoder* _this, InstanceDataBuffer* _idb, uint _start, uint _num);
	
	/// <summary>
	/// Set instance data buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_handle">Vertex buffer.</param>
	/// <param name="_startVertex">First instance data.</param>
	/// <param name="_num">Number of data instances. Set instance data buffer for draw primitive.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_instance_data_from_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void encoder_set_instance_data_from_vertex_buffer(Encoder* _this, VertexBufferHandle _handle, uint _startVertex, uint _num);
	
	/// <summary>
	/// Set instance data buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_handle">Dynamic vertex buffer.</param>
	/// <param name="_startVertex">First instance data.</param>
	/// <param name="_num">Number of data instances.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_instance_data_from_dynamic_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void encoder_set_instance_data_from_dynamic_vertex_buffer(Encoder* _this, DynamicVertexBufferHandle _handle, uint _startVertex, uint _num);
	
	/// <summary>
	/// Set number of instances for auto generated instances use in conjuction
	/// with gl_InstanceID.
	/// @attention Availability depends on: `BGFX_CAPS_VERTEX_ID`.
	/// </summary>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_instance_count", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void encoder_set_instance_count(Encoder* _this, uint _numInstances);
	
	/// <summary>
	/// Set texture stage for draw primitive.
	/// </summary>
	///
	/// <param name="_stage">Texture unit.</param>
	/// <param name="_sampler">Program sampler.</param>
	/// <param name="_handle">Texture handle.</param>
	/// <param name="_flags">Texture sampling mode. Default value UINT32_MAX uses   texture sampling settings from the texture.   - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap     mode.   - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic     sampling.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_texture", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void encoder_set_texture(Encoder* _this, byte _stage, UniformHandle _sampler, TextureHandle _handle, uint _flags);
	
	/// <summary>
	/// Submit an empty primitive for rendering. Uniforms and draw state
	/// will be applied but no geometry will be submitted.
	/// @remark
	///   These empty draw calls will sort before ordinary draw calls.
	/// </summary>
	///
	/// <param name="_id">View id.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_touch", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void encoder_touch(Encoder* _this, ushort _id);
	
	/// <summary>
	/// Submit primitive for rendering.
	/// </summary>
	///
	/// <param name="_id">View id.</param>
	/// <param name="_program">Program.</param>
	/// <param name="_depth">Depth for sorting.</param>
	/// <param name="_preserveState">Preserve internal draw state for next draw call submit.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_submit", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void encoder_submit(Encoder* _this, ushort _id, ProgramHandle _program, uint _depth, byte _preserveState);
	
	/// <summary>
	/// Submit primitive with occlusion query for rendering.
	/// </summary>
	///
	/// <param name="_id">View id.</param>
	/// <param name="_program">Program.</param>
	/// <param name="_occlusionQuery">Occlusion query.</param>
	/// <param name="_depth">Depth for sorting.</param>
	/// <param name="_preserveState">Preserve internal draw state for next draw call submit.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_submit_occlusion_query", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void encoder_submit_occlusion_query(Encoder* _this, ushort _id, ProgramHandle _program, OcclusionQueryHandle _occlusionQuery, uint _depth, byte _preserveState);
	
	/// <summary>
	/// Submit primitive for rendering with index and instance data info from
	/// indirect buffer.
	/// </summary>
	///
	/// <param name="_id">View id.</param>
	/// <param name="_program">Program.</param>
	/// <param name="_indirectHandle">Indirect buffer.</param>
	/// <param name="_start">First element in indirect buffer.</param>
	/// <param name="_num">Number of dispatches.</param>
	/// <param name="_depth">Depth for sorting.</param>
	/// <param name="_preserveState">Preserve internal draw state for next draw call submit.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_submit_indirect", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void encoder_submit_indirect(Encoder* _this, ushort _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, ushort _start, ushort _num, uint _depth, byte _preserveState);
	
	/// <summary>
	/// Set compute index buffer.
	/// </summary>
	///
	/// <param name="_stage">Compute stage.</param>
	/// <param name="_handle">Index buffer handle.</param>
	/// <param name="_access">Buffer access. See `Access::Enum`.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_compute_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void encoder_set_compute_index_buffer(Encoder* _this, byte _stage, IndexBufferHandle _handle, Access _access);
	
	/// <summary>
	/// Set compute vertex buffer.
	/// </summary>
	///
	/// <param name="_stage">Compute stage.</param>
	/// <param name="_handle">Vertex buffer handle.</param>
	/// <param name="_access">Buffer access. See `Access::Enum`.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_compute_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void encoder_set_compute_vertex_buffer(Encoder* _this, byte _stage, VertexBufferHandle _handle, Access _access);
	
	/// <summary>
	/// Set compute dynamic index buffer.
	/// </summary>
	///
	/// <param name="_stage">Compute stage.</param>
	/// <param name="_handle">Dynamic index buffer handle.</param>
	/// <param name="_access">Buffer access. See `Access::Enum`.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_compute_dynamic_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void encoder_set_compute_dynamic_index_buffer(Encoder* _this, byte _stage, DynamicIndexBufferHandle _handle, Access _access);
	
	/// <summary>
	/// Set compute dynamic vertex buffer.
	/// </summary>
	///
	/// <param name="_stage">Compute stage.</param>
	/// <param name="_handle">Dynamic vertex buffer handle.</param>
	/// <param name="_access">Buffer access. See `Access::Enum`.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_compute_dynamic_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void encoder_set_compute_dynamic_vertex_buffer(Encoder* _this, byte _stage, DynamicVertexBufferHandle _handle, Access _access);
	
	/// <summary>
	/// Set compute indirect buffer.
	/// </summary>
	///
	/// <param name="_stage">Compute stage.</param>
	/// <param name="_handle">Indirect buffer handle.</param>
	/// <param name="_access">Buffer access. See `Access::Enum`.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_compute_indirect_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void encoder_set_compute_indirect_buffer(Encoder* _this, byte _stage, IndirectBufferHandle _handle, Access _access);
	
	/// <summary>
	/// Set compute image from texture.
	/// </summary>
	///
	/// <param name="_stage">Compute stage.</param>
	/// <param name="_handle">Texture handle.</param>
	/// <param name="_mip">Mip level.</param>
	/// <param name="_access">Image access. See `Access::Enum`.</param>
	/// <param name="_format">Texture format. See: `TextureFormat::Enum`.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_set_image", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void encoder_set_image(Encoder* _this, byte _stage, TextureHandle _handle, byte _mip, Access _access, TextureFormat _format);
	
	/// <summary>
	/// Dispatch compute.
	/// </summary>
	///
	/// <param name="_id">View id.</param>
	/// <param name="_program">Compute program.</param>
	/// <param name="_numX">Number of groups X.</param>
	/// <param name="_numY">Number of groups Y.</param>
	/// <param name="_numZ">Number of groups Z.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_dispatch", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void encoder_dispatch(Encoder* _this, ushort _id, ProgramHandle _program, uint _numX, uint _numY, uint _numZ);
	
	/// <summary>
	/// Dispatch compute indirect.
	/// </summary>
	///
	/// <param name="_id">View id.</param>
	/// <param name="_program">Compute program.</param>
	/// <param name="_indirectHandle">Indirect buffer.</param>
	/// <param name="_start">First element in indirect buffer.</param>
	/// <param name="_num">Number of dispatches.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_dispatch_indirect", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void encoder_dispatch_indirect(Encoder* _this, ushort _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, ushort _start, ushort _num);
	
	/// <summary>
	/// Discard all previously set state for draw or compute call.
	/// </summary>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_discard", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void encoder_discard(Encoder* _this);
	
	/// <summary>
	/// Blit 2D texture region between two 2D textures.
	/// @attention Destination texture must be created with `BGFX_TEXTURE_BLIT_DST` flag.
	/// @attention Availability depends on: `BGFX_CAPS_TEXTURE_BLIT`.
	/// </summary>
	///
	/// <param name="_id">View id.</param>
	/// <param name="_dst">Destination texture handle.</param>
	/// <param name="_dstMip">Destination texture mip level.</param>
	/// <param name="_dstX">Destination texture X position.</param>
	/// <param name="_dstY">Destination texture Y position.</param>
	/// <param name="_dstZ">If texture is 2D this argument should be 0. If destination texture is cube this argument represents destination texture cube face. For 3D texture this argument represents destination texture Z position.</param>
	/// <param name="_src">Source texture handle.</param>
	/// <param name="_srcMip">Source texture mip level.</param>
	/// <param name="_srcX">Source texture X position.</param>
	/// <param name="_srcY">Source texture Y position.</param>
	/// <param name="_srcZ">If texture is 2D this argument should be 0. If source texture is cube this argument represents source texture cube face. For 3D texture this argument represents source texture Z position.</param>
	/// <param name="_width">Width of region.</param>
	/// <param name="_height">Height of region.</param>
	/// <param name="_depth">If texture is 3D this argument represents depth of region, otherwise it's unused.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_encoder_blit", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void encoder_blit(Encoder* _this, ushort _id, TextureHandle _dst, byte _dstMip, ushort _dstX, ushort _dstY, ushort _dstZ, TextureHandle _src, byte _srcMip, ushort _srcX, ushort _srcY, ushort _srcZ, ushort _width, ushort _height, ushort _depth);
	
	/// <summary>
	/// Request screen shot of window back buffer.
	/// @remarks
	///   `bgfx::CallbackI::screenShot` must be implemented.
	/// @attention Frame buffer handle must be created with OS' target native window handle.
	/// </summary>
	///
	/// <param name="_handle">Frame buffer handle. If handle is `BGFX_INVALID_HANDLE` request will be made for main window back buffer.</param>
	/// <param name="_filePath">Will be passed to `bgfx::CallbackI::screenShot` callback.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_request_screen_shot", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void request_screen_shot(FrameBufferHandle _handle, [MarshalAs(UnmanagedType.LPStr)] string _filePath);
	
	/// <summary>
	/// Render frame.
	/// @attention `bgfx::renderFrame` is blocking call. It waits for
	///   `bgfx::frame` to be called from API thread to process frame.
	///   If timeout value is passed call will timeout and return even
	///   if `bgfx::frame` is not called.
	/// @warning This call should be only used on platforms that don't
	///   allow creating separate rendering thread. If it is called before
	///   to bgfx::init, render thread won't be created by bgfx::init call.
	/// </summary>
	///
	/// <param name="_msecs">Timeout in milliseconds.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_render_frame", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe RenderFrame render_frame(int _msecs);
	
	/// <summary>
	/// Set platform data.
	/// @warning Must be called before `bgfx::init`.
	/// </summary>
	///
	/// <param name="_data">Platform data.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_platform_data", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_platform_data(PlatformData* _data);
	
	/// <summary>
	/// Get internal data for interop.
	/// @attention It's expected you understand some bgfx internals before you
	///   use this call.
	/// @warning Must be called only on render thread.
	/// </summary>
	///
	[DllImport(DllName, EntryPoint="bgfx_get_internal_data", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe InternalData* get_internal_data();
	
	/// <summary>
	/// Override internal texture with externally created texture. Previously
	/// created internal texture will released.
	/// @attention It's expected you understand some bgfx internals before you
	///   use this call.
	/// @warning Must be called only on render thread.
	/// </summary>
	///
	/// <param name="_handle">Texture handle.</param>
	/// <param name="_ptr">Native API pointer to texture.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_override_internal_texture_ptr", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe UIntPtr override_internal_texture_ptr(TextureHandle _handle, UIntPtr _ptr);
	
	/// <summary>
	/// Override internal texture by creating new texture. Previously created
	/// internal texture will released.
	/// @attention It's expected you understand some bgfx internals before you
	///   use this call.
	/// @returns Native API pointer to texture. If result is 0, texture is not created yet from the
	///   main thread.
	/// @warning Must be called only on render thread.
	/// </summary>
	///
	/// <param name="_handle">Texture handle.</param>
	/// <param name="_width">Width.</param>
	/// <param name="_height">Height.</param>
	/// <param name="_numMips">Number of mip-maps.</param>
	/// <param name="_format">Texture format. See: `TextureFormat::Enum`.</param>
	/// <param name="_flags">Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`) flags. Default texture sampling mode is linear, and wrap mode is repeat. - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap   mode. - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic   sampling.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_override_internal_texture", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe UIntPtr override_internal_texture(TextureHandle _handle, ushort _width, ushort _height, byte _numMips, TextureFormat _format, ulong _flags);
	
	/// <summary>
	/// Sets a debug marker. This allows you to group graphics calls together for easy browsing in
	/// graphics debugging tools.
	/// </summary>
	///
	/// <param name="_marker">Marker string.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_marker", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_marker([MarshalAs(UnmanagedType.LPStr)] string _marker);
	
	/// <summary>
	/// Set render states for draw primitive.
	/// @remarks
	///   1. To setup more complex states use:
	///      `BGFX_STATE_ALPHA_REF(_ref)`,
	///      `BGFX_STATE_POINT_SIZE(_size)`,
	///      `BGFX_STATE_BLEND_FUNC(_src, _dst)`,
	///      `BGFX_STATE_BLEND_FUNC_SEPARATE(_srcRGB, _dstRGB, _srcA, _dstA)`,
	///      `BGFX_STATE_BLEND_EQUATION(_equation)`,
	///      `BGFX_STATE_BLEND_EQUATION_SEPARATE(_equationRGB, _equationA)`
	///   2. `BGFX_STATE_BLEND_EQUATION_ADD` is set when no other blend
	///      equation is specified.
	/// </summary>
	///
	/// <param name="_state">State flags. Default state for primitive type is   triangles. See: `BGFX_STATE_DEFAULT`.   - `BGFX_STATE_DEPTH_TEST_*` - Depth test function.   - `BGFX_STATE_BLEND_*` - See remark 1 about BGFX_STATE_BLEND_FUNC.   - `BGFX_STATE_BLEND_EQUATION_*` - See remark 2.   - `BGFX_STATE_CULL_*` - Backface culling mode.   - `BGFX_STATE_WRITE_*` - Enable R, G, B, A or Z write.   - `BGFX_STATE_MSAA` - Enable hardware multisample antialiasing.   - `BGFX_STATE_PT_[TRISTRIP/LINES/POINTS]` - Primitive type.</param>
	/// <param name="_rgba">Sets blend factor used by `BGFX_STATE_BLEND_FACTOR` and   `BGFX_STATE_BLEND_INV_FACTOR` blend modes.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_state", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_state(ulong _state, uint _rgba);
	
	/// <summary>
	/// Set condition for rendering.
	/// </summary>
	///
	/// <param name="_handle">Occlusion query handle.</param>
	/// <param name="_visible">Render if occlusion query is visible.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_condition", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_condition(OcclusionQueryHandle _handle, byte _visible);
	
	/// <summary>
	/// Set stencil test state.
	/// </summary>
	///
	/// <param name="_fstencil">Front stencil state.</param>
	/// <param name="_bstencil">Back stencil state. If back is set to `BGFX_STENCIL_NONE` _fstencil is applied to both front and back facing primitives.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_stencil", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_stencil(uint _fstencil, uint _bstencil);
	
	/// <summary>
	/// Set scissor for draw primitive.
	/// @remark
	///   To scissor for all primitives in view see `bgfx::setViewScissor`.
	/// </summary>
	///
	/// <param name="_x">Position x from the left corner of the window.</param>
	/// <param name="_y">Position y from the top corner of the window.</param>
	/// <param name="_width">Width of view scissor region.</param>
	/// <param name="_height">Height of view scissor region.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_scissor", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe ushort set_scissor(ushort _x, ushort _y, ushort _width, ushort _height);
	
	/// <summary>
	/// Set scissor from cache for draw primitive.
	/// @remark
	///   To scissor for all primitives in view see `bgfx::setViewScissor`.
	/// </summary>
	///
	/// <param name="_cache">Index in scissor cache.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_scissor_cached", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_scissor_cached(ushort _cache);
	
	/// <summary>
	/// Set model matrix for draw primitive. If it is not called,
	/// the model will be rendered with an identity model matrix.
	/// </summary>
	///
	/// <param name="_mtx">Pointer to first matrix in array.</param>
	/// <param name="_num">Number of matrices in array.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_transform", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe uint set_transform(void* _mtx, ushort _num);
	
	/// <summary>
	///  Set model matrix from matrix cache for draw primitive.
	/// </summary>
	///
	/// <param name="_cache">Index in matrix cache.</param>
	/// <param name="_num">Number of matrices from cache.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_transform_cached", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_transform_cached(uint _cache, ushort _num);
	
	/// <summary>
	/// Reserve matrices in internal matrix cache.
	/// @attention Pointer returned can be modifed until `bgfx::frame` is called.
	/// </summary>
	///
	/// <param name="_transform">Pointer to `Transform` structure.</param>
	/// <param name="_num">Number of matrices.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_alloc_transform", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe uint alloc_transform(Transform* _transform, ushort _num);
	
	/// <summary>
	/// Set shader uniform parameter for draw primitive.
	/// </summary>
	///
	/// <param name="_handle">Uniform.</param>
	/// <param name="_value">Pointer to uniform data.</param>
	/// <param name="_num">Number of elements. Passing `UINT16_MAX` will use the _num passed on uniform creation.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_uniform", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_uniform(UniformHandle _handle, void* _value, ushort _num);
	
	/// <summary>
	/// Set index buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_handle">Index buffer.</param>
	/// <param name="_firstIndex">First index to render.</param>
	/// <param name="_numIndices">Number of indices to render.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_index_buffer(IndexBufferHandle _handle, uint _firstIndex, uint _numIndices);
	
	/// <summary>
	/// Set index buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_handle">Dynamic index buffer.</param>
	/// <param name="_firstIndex">First index to render.</param>
	/// <param name="_numIndices">Number of indices to render.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_dynamic_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_dynamic_index_buffer(DynamicIndexBufferHandle _handle, uint _firstIndex, uint _numIndices);
	
	/// <summary>
	/// Set index buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_tib">Transient index buffer.</param>
	/// <param name="_firstIndex">First index to render.</param>
	/// <param name="_numIndices">Number of indices to render.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_transient_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_transient_index_buffer(TransientIndexBuffer* _tib, uint _firstIndex, uint _numIndices);
	
	/// <summary>
	/// Set vertex buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_stream">Vertex stream.</param>
	/// <param name="_handle">Vertex buffer.</param>
	/// <param name="_startVertex">First vertex to render.</param>
	/// <param name="_numVertices">Number of vertices to render.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_vertex_buffer(byte _stream, VertexBufferHandle _handle, uint _startVertex, uint _numVertices);
	
	/// <summary>
	/// Set vertex buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_stream">Vertex stream.</param>
	/// <param name="_handle">Dynamic vertex buffer.</param>
	/// <param name="_startVertex">First vertex to render.</param>
	/// <param name="_numVertices">Number of vertices to render.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_dynamic_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_dynamic_vertex_buffer(byte _stream, DynamicVertexBufferHandle _handle, uint _startVertex, uint _numVertices);
	
	/// <summary>
	/// Set vertex buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_stream">Vertex stream.</param>
	/// <param name="_tvb">Transient vertex buffer.</param>
	/// <param name="_startVertex">First vertex to render.</param>
	/// <param name="_numVertices">Number of vertices to render.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_transient_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_transient_vertex_buffer(byte _stream, TransientVertexBuffer* _tvb, uint _startVertex, uint _numVertices);
	
	/// <summary>
	/// Set number of vertices for auto generated vertices use in conjuction
	/// with gl_VertexID.
	/// @attention Availability depends on: `BGFX_CAPS_VERTEX_ID`.
	/// </summary>
	///
	/// <param name="_numVertices">Number of vertices.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_vertex_count", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_vertex_count(uint _numVertices);
	
	/// <summary>
	/// Set instance data buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_idb">Transient instance data buffer.</param>
	/// <param name="_start">First instance data.</param>
	/// <param name="_num">Number of data instances.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_instance_data_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_instance_data_buffer(InstanceDataBuffer* _idb, uint _start, uint _num);
	
	/// <summary>
	/// Set instance data buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_handle">Vertex buffer.</param>
	/// <param name="_startVertex">First instance data.</param>
	/// <param name="_num">Number of data instances. Set instance data buffer for draw primitive.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_instance_data_from_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_instance_data_from_vertex_buffer(VertexBufferHandle _handle, uint _startVertex, uint _num);
	
	/// <summary>
	/// Set instance data buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_handle">Dynamic vertex buffer.</param>
	/// <param name="_startVertex">First instance data.</param>
	/// <param name="_num">Number of data instances.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_instance_data_from_dynamic_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_instance_data_from_dynamic_vertex_buffer(DynamicVertexBufferHandle _handle, uint _startVertex, uint _num);
	
	/// <summary>
	/// Set number of instances for auto generated instances use in conjuction
	/// with gl_InstanceID.
	/// @attention Availability depends on: `BGFX_CAPS_VERTEX_ID`.
	/// </summary>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_instance_count", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_instance_count(uint _numInstances);
	
	/// <summary>
	/// Set texture stage for draw primitive.
	/// </summary>
	///
	/// <param name="_stage">Texture unit.</param>
	/// <param name="_sampler">Program sampler.</param>
	/// <param name="_handle">Texture handle.</param>
	/// <param name="_flags">Texture sampling mode. Default value UINT32_MAX uses   texture sampling settings from the texture.   - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap     mode.   - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic     sampling.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_texture", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_texture(byte _stage, UniformHandle _sampler, TextureHandle _handle, uint _flags);
	
	/// <summary>
	/// Submit an empty primitive for rendering. Uniforms and draw state
	/// will be applied but no geometry will be submitted.
	/// @remark
	///   These empty draw calls will sort before ordinary draw calls.
	/// </summary>
	///
	/// <param name="_id">View id.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_touch", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void touch(ushort _id);
	
	/// <summary>
	/// Submit primitive for rendering.
	/// </summary>
	///
	/// <param name="_id">View id.</param>
	/// <param name="_program">Program.</param>
	/// <param name="_depth">Depth for sorting.</param>
	/// <param name="_preserveState">Preserve internal draw state for next draw call submit.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_submit", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void submit(ushort _id, ProgramHandle _program, uint _depth, byte _preserveState);
	
	/// <summary>
	/// Submit primitive with occlusion query for rendering.
	/// </summary>
	///
	/// <param name="_id">View id.</param>
	/// <param name="_program">Program.</param>
	/// <param name="_occlusionQuery">Occlusion query.</param>
	/// <param name="_depth">Depth for sorting.</param>
	/// <param name="_preserveState">Preserve internal draw state for next draw call submit.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_submit_occlusion_query", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void submit_occlusion_query(ushort _id, ProgramHandle _program, OcclusionQueryHandle _occlusionQuery, uint _depth, byte _preserveState);
	
	/// <summary>
	/// Submit primitive for rendering with index and instance data info from
	/// indirect buffer.
	/// </summary>
	///
	/// <param name="_id">View id.</param>
	/// <param name="_program">Program.</param>
	/// <param name="_indirectHandle">Indirect buffer.</param>
	/// <param name="_start">First element in indirect buffer.</param>
	/// <param name="_num">Number of dispatches.</param>
	/// <param name="_depth">Depth for sorting.</param>
	/// <param name="_preserveState">Preserve internal draw state for next draw call submit.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_submit_indirect", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void submit_indirect(ushort _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, ushort _start, ushort _num, uint _depth, byte _preserveState);
	
	/// <summary>
	/// Set compute index buffer.
	/// </summary>
	///
	/// <param name="_stage">Compute stage.</param>
	/// <param name="_handle">Index buffer handle.</param>
	/// <param name="_access">Buffer access. See `Access::Enum`.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_compute_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_compute_index_buffer(byte _stage, IndexBufferHandle _handle, Access _access);
	
	/// <summary>
	/// Set compute vertex buffer.
	/// </summary>
	///
	/// <param name="_stage">Compute stage.</param>
	/// <param name="_handle">Vertex buffer handle.</param>
	/// <param name="_access">Buffer access. See `Access::Enum`.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_compute_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_compute_vertex_buffer(byte _stage, VertexBufferHandle _handle, Access _access);
	
	/// <summary>
	/// Set compute dynamic index buffer.
	/// </summary>
	///
	/// <param name="_stage">Compute stage.</param>
	/// <param name="_handle">Dynamic index buffer handle.</param>
	/// <param name="_access">Buffer access. See `Access::Enum`.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_compute_dynamic_index_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_compute_dynamic_index_buffer(byte _stage, DynamicIndexBufferHandle _handle, Access _access);
	
	/// <summary>
	/// Set compute dynamic vertex buffer.
	/// </summary>
	///
	/// <param name="_stage">Compute stage.</param>
	/// <param name="_handle">Dynamic vertex buffer handle.</param>
	/// <param name="_access">Buffer access. See `Access::Enum`.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_compute_dynamic_vertex_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_compute_dynamic_vertex_buffer(byte _stage, DynamicVertexBufferHandle _handle, Access _access);
	
	/// <summary>
	/// Set compute indirect buffer.
	/// </summary>
	///
	/// <param name="_stage">Compute stage.</param>
	/// <param name="_handle">Indirect buffer handle.</param>
	/// <param name="_access">Buffer access. See `Access::Enum`.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_compute_indirect_buffer", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_compute_indirect_buffer(byte _stage, IndirectBufferHandle _handle, Access _access);
	
	/// <summary>
	/// Set compute image from texture.
	/// </summary>
	///
	/// <param name="_stage">Compute stage.</param>
	/// <param name="_handle">Texture handle.</param>
	/// <param name="_mip">Mip level.</param>
	/// <param name="_access">Image access. See `Access::Enum`.</param>
	/// <param name="_format">Texture format. See: `TextureFormat::Enum`.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_set_image", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void set_image(byte _stage, TextureHandle _handle, byte _mip, Access _access, TextureFormat _format);
	
	/// <summary>
	/// Dispatch compute.
	/// </summary>
	///
	/// <param name="_id">View id.</param>
	/// <param name="_program">Compute program.</param>
	/// <param name="_numX">Number of groups X.</param>
	/// <param name="_numY">Number of groups Y.</param>
	/// <param name="_numZ">Number of groups Z.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_dispatch", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void dispatch(ushort _id, ProgramHandle _program, uint _numX, uint _numY, uint _numZ);
	
	/// <summary>
	/// Dispatch compute indirect.
	/// </summary>
	///
	/// <param name="_id">View id.</param>
	/// <param name="_program">Compute program.</param>
	/// <param name="_indirectHandle">Indirect buffer.</param>
	/// <param name="_start">First element in indirect buffer.</param>
	/// <param name="_num">Number of dispatches.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_dispatch_indirect", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void dispatch_indirect(ushort _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, ushort _start, ushort _num);
	
	/// <summary>
	/// Discard all previously set state for draw or compute call.
	/// </summary>
	///
	[DllImport(DllName, EntryPoint="bgfx_discard", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void discard();
	
	/// <summary>
	/// Blit 2D texture region between two 2D textures.
	/// @attention Destination texture must be created with `BGFX_TEXTURE_BLIT_DST` flag.
	/// @attention Availability depends on: `BGFX_CAPS_TEXTURE_BLIT`.
	/// </summary>
	///
	/// <param name="_id">View id.</param>
	/// <param name="_dst">Destination texture handle.</param>
	/// <param name="_dstMip">Destination texture mip level.</param>
	/// <param name="_dstX">Destination texture X position.</param>
	/// <param name="_dstY">Destination texture Y position.</param>
	/// <param name="_dstZ">If texture is 2D this argument should be 0. If destination texture is cube this argument represents destination texture cube face. For 3D texture this argument represents destination texture Z position.</param>
	/// <param name="_src">Source texture handle.</param>
	/// <param name="_srcMip">Source texture mip level.</param>
	/// <param name="_srcX">Source texture X position.</param>
	/// <param name="_srcY">Source texture Y position.</param>
	/// <param name="_srcZ">If texture is 2D this argument should be 0. If source texture is cube this argument represents source texture cube face. For 3D texture this argument represents source texture Z position.</param>
	/// <param name="_width">Width of region.</param>
	/// <param name="_height">Height of region.</param>
	/// <param name="_depth">If texture is 3D this argument represents depth of region, otherwise it's unused.</param>
	///
	[DllImport(DllName, EntryPoint="bgfx_blit", CallingConvention = CallingConvention.Cdecl)]
	public static extern unsafe void blit(ushort _id, TextureHandle _dst, byte _dstMip, ushort _dstX, ushort _dstY, ushort _dstZ, TextureHandle _src, byte _srcMip, ushort _srcX, ushort _srcY, ushort _srcZ, ushort _width, ushort _height, ushort _depth);
	

#if !BGFX_CSHARP_CUSTOM_DLLNAME
#if DEBUG
	const string DllName = "bgfx_debug.dll";
#else
	const string DllName = "bgfx.dll";
#endif
#endif
}
}
