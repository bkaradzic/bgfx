/*
 * Copyright 2011-2022 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

/*
 *
 * AUTO GENERATED! DO NOT EDIT!
 *
 */

using System;

namespace Bgfx
{
public static class bgfx
{
	public typealias ViewId = uint16;

	[AllowDuplicates]
	public enum StateFlags : uint64
	{
		/// <summary>
		/// Enable R write.
		/// </summary>
		WriteR                 = 0x0000000000000001,
	
		/// <summary>
		/// Enable G write.
		/// </summary>
		WriteG                 = 0x0000000000000002,
	
		/// <summary>
		/// Enable B write.
		/// </summary>
		WriteB                 = 0x0000000000000004,
	
		/// <summary>
		/// Enable alpha write.
		/// </summary>
		WriteA                 = 0x0000000000000008,
	
		/// <summary>
		/// Enable depth write.
		/// </summary>
		WriteZ                 = 0x0000004000000000,
	
		/// <summary>
		/// Enable RGB write.
		/// </summary>
		WriteRgb               = 0x0000000000000007,
	
		/// <summary>
		/// Write all channels mask.
		/// </summary>
		WriteMask              = 0x000000400000000f,
	
		/// <summary>
		/// Enable depth test, less.
		/// </summary>
		DepthTestLess          = 0x0000000000000010,
	
		/// <summary>
		/// Enable depth test, less or equal.
		/// </summary>
		DepthTestLequal        = 0x0000000000000020,
	
		/// <summary>
		/// Enable depth test, equal.
		/// </summary>
		DepthTestEqual         = 0x0000000000000030,
	
		/// <summary>
		/// Enable depth test, greater or equal.
		/// </summary>
		DepthTestGequal        = 0x0000000000000040,
	
		/// <summary>
		/// Enable depth test, greater.
		/// </summary>
		DepthTestGreater       = 0x0000000000000050,
	
		/// <summary>
		/// Enable depth test, not equal.
		/// </summary>
		DepthTestNotequal      = 0x0000000000000060,
	
		/// <summary>
		/// Enable depth test, never.
		/// </summary>
		DepthTestNever         = 0x0000000000000070,
	
		/// <summary>
		/// Enable depth test, always.
		/// </summary>
		DepthTestAlways        = 0x0000000000000080,
		DepthTestShift         = 4,
		DepthTestMask          = 0x00000000000000f0,
	
		/// <summary>
		/// 0, 0, 0, 0
		/// </summary>
		BlendZero              = 0x0000000000001000,
	
		/// <summary>
		/// 1, 1, 1, 1
		/// </summary>
		BlendOne               = 0x0000000000002000,
	
		/// <summary>
		/// Rs, Gs, Bs, As
		/// </summary>
		BlendSrcColor          = 0x0000000000003000,
	
		/// <summary>
		/// 1-Rs, 1-Gs, 1-Bs, 1-As
		/// </summary>
		BlendInvSrcColor       = 0x0000000000004000,
	
		/// <summary>
		/// As, As, As, As
		/// </summary>
		BlendSrcAlpha          = 0x0000000000005000,
	
		/// <summary>
		/// 1-As, 1-As, 1-As, 1-As
		/// </summary>
		BlendInvSrcAlpha       = 0x0000000000006000,
	
		/// <summary>
		/// Ad, Ad, Ad, Ad
		/// </summary>
		BlendDstAlpha          = 0x0000000000007000,
	
		/// <summary>
		/// 1-Ad, 1-Ad, 1-Ad ,1-Ad
		/// </summary>
		BlendInvDstAlpha       = 0x0000000000008000,
	
		/// <summary>
		/// Rd, Gd, Bd, Ad
		/// </summary>
		BlendDstColor          = 0x0000000000009000,
	
		/// <summary>
		/// 1-Rd, 1-Gd, 1-Bd, 1-Ad
		/// </summary>
		BlendInvDstColor       = 0x000000000000a000,
	
		/// <summary>
		/// f, f, f, 1; f = min(As, 1-Ad)
		/// </summary>
		BlendSrcAlphaSat       = 0x000000000000b000,
	
		/// <summary>
		/// Blend factor
		/// </summary>
		BlendFactor            = 0x000000000000c000,
	
		/// <summary>
		/// 1-Blend factor
		/// </summary>
		BlendInvFactor         = 0x000000000000d000,
		BlendShift             = 12,
		BlendMask              = 0x000000000ffff000,
	
		/// <summary>
		/// Blend add: src + dst.
		/// </summary>
		BlendEquationAdd       = 0x0000000000000000,
	
		/// <summary>
		/// Blend subtract: src - dst.
		/// </summary>
		BlendEquationSub       = 0x0000000010000000,
	
		/// <summary>
		/// Blend reverse subtract: dst - src.
		/// </summary>
		BlendEquationRevsub    = 0x0000000020000000,
	
		/// <summary>
		/// Blend min: min(src, dst).
		/// </summary>
		BlendEquationMin       = 0x0000000030000000,
	
		/// <summary>
		/// Blend max: max(src, dst).
		/// </summary>
		BlendEquationMax       = 0x0000000040000000,
		BlendEquationShift     = 28,
		BlendEquationMask      = 0x00000003f0000000,
	
		/// <summary>
		/// Cull clockwise triangles.
		/// </summary>
		CullCw                 = 0x0000001000000000,
	
		/// <summary>
		/// Cull counter-clockwise triangles.
		/// </summary>
		CullCcw                = 0x0000002000000000,
		CullShift              = 36,
		CullMask               = 0x0000003000000000,
		AlphaRefShift          = 40,
		AlphaRefMask           = 0x0000ff0000000000,
	
		/// <summary>
		/// Tristrip.
		/// </summary>
		PtTristrip             = 0x0001000000000000,
	
		/// <summary>
		/// Lines.
		/// </summary>
		PtLines                = 0x0002000000000000,
	
		/// <summary>
		/// Line strip.
		/// </summary>
		PtLinestrip            = 0x0003000000000000,
	
		/// <summary>
		/// Points.
		/// </summary>
		PtPoints               = 0x0004000000000000,
		PtShift                = 48,
		PtMask                 = 0x0007000000000000,
		PointSizeShift         = 52,
		PointSizeMask          = 0x00f0000000000000,
	
		/// <summary>
		/// Enable MSAA rasterization.
		/// </summary>
		Msaa                   = 0x0100000000000000,
	
		/// <summary>
		/// Enable line AA rasterization.
		/// </summary>
		Lineaa                 = 0x0200000000000000,
	
		/// <summary>
		/// Enable conservative rasterization.
		/// </summary>
		ConservativeRaster     = 0x0400000000000000,
	
		/// <summary>
		/// No state.
		/// </summary>
		None                   = 0x0000000000000000,
	
		/// <summary>
		/// Front counter-clockwise (default is clockwise).
		/// </summary>
		FrontCcw               = 0x0000008000000000,
	
		/// <summary>
		/// Enable blend independent.
		/// </summary>
		BlendIndependent       = 0x0000000400000000,
	
		/// <summary>
		/// Enable alpha to coverage.
		/// </summary>
		BlendAlphaToCoverage   = 0x0000000800000000,
	
		/// <summary>
		/// Default state is write to RGB, alpha, and depth with depth test less enabled, with clockwise
		/// culling and MSAA (when writing into MSAA frame buffer, otherwise this flag is ignored).
		/// </summary>
		Default                = 0x010000500000001f,
		Mask                   = 0xffffffffffffffff,
		ReservedShift          = 61,
		ReservedMask           = 0xe000000000000000,
	}
	
	[AllowDuplicates]
	public enum StencilFlags : uint32
	{
		FuncRefShift           = 0,
		FuncRefMask            = 0x000000ff,
		FuncRmaskShift         = 8,
		FuncRmaskMask          = 0x0000ff00,
		None                   = 0x00000000,
		Mask                   = 0xffffffff,
		Default                = 0x00000000,
	
		/// <summary>
		/// Enable stencil test, less.
		/// </summary>
		TestLess               = 0x00010000,
	
		/// <summary>
		/// Enable stencil test, less or equal.
		/// </summary>
		TestLequal             = 0x00020000,
	
		/// <summary>
		/// Enable stencil test, equal.
		/// </summary>
		TestEqual              = 0x00030000,
	
		/// <summary>
		/// Enable stencil test, greater or equal.
		/// </summary>
		TestGequal             = 0x00040000,
	
		/// <summary>
		/// Enable stencil test, greater.
		/// </summary>
		TestGreater            = 0x00050000,
	
		/// <summary>
		/// Enable stencil test, not equal.
		/// </summary>
		TestNotequal           = 0x00060000,
	
		/// <summary>
		/// Enable stencil test, never.
		/// </summary>
		TestNever              = 0x00070000,
	
		/// <summary>
		/// Enable stencil test, always.
		/// </summary>
		TestAlways             = 0x00080000,
		TestShift              = 16,
		TestMask               = 0x000f0000,
	
		/// <summary>
		/// Zero.
		/// </summary>
		OpFailSZero            = 0x00000000,
	
		/// <summary>
		/// Keep.
		/// </summary>
		OpFailSKeep            = 0x00100000,
	
		/// <summary>
		/// Replace.
		/// </summary>
		OpFailSReplace         = 0x00200000,
	
		/// <summary>
		/// Increment and wrap.
		/// </summary>
		OpFailSIncr            = 0x00300000,
	
		/// <summary>
		/// Increment and clamp.
		/// </summary>
		OpFailSIncrsat         = 0x00400000,
	
		/// <summary>
		/// Decrement and wrap.
		/// </summary>
		OpFailSDecr            = 0x00500000,
	
		/// <summary>
		/// Decrement and clamp.
		/// </summary>
		OpFailSDecrsat         = 0x00600000,
	
		/// <summary>
		/// Invert.
		/// </summary>
		OpFailSInvert          = 0x00700000,
		OpFailSShift           = 20,
		OpFailSMask            = 0x00f00000,
	
		/// <summary>
		/// Zero.
		/// </summary>
		OpFailZZero            = 0x00000000,
	
		/// <summary>
		/// Keep.
		/// </summary>
		OpFailZKeep            = 0x01000000,
	
		/// <summary>
		/// Replace.
		/// </summary>
		OpFailZReplace         = 0x02000000,
	
		/// <summary>
		/// Increment and wrap.
		/// </summary>
		OpFailZIncr            = 0x03000000,
	
		/// <summary>
		/// Increment and clamp.
		/// </summary>
		OpFailZIncrsat         = 0x04000000,
	
		/// <summary>
		/// Decrement and wrap.
		/// </summary>
		OpFailZDecr            = 0x05000000,
	
		/// <summary>
		/// Decrement and clamp.
		/// </summary>
		OpFailZDecrsat         = 0x06000000,
	
		/// <summary>
		/// Invert.
		/// </summary>
		OpFailZInvert          = 0x07000000,
		OpFailZShift           = 24,
		OpFailZMask            = 0x0f000000,
	
		/// <summary>
		/// Zero.
		/// </summary>
		OpPassZZero            = 0x00000000,
	
		/// <summary>
		/// Keep.
		/// </summary>
		OpPassZKeep            = 0x10000000,
	
		/// <summary>
		/// Replace.
		/// </summary>
		OpPassZReplace         = 0x20000000,
	
		/// <summary>
		/// Increment and wrap.
		/// </summary>
		OpPassZIncr            = 0x30000000,
	
		/// <summary>
		/// Increment and clamp.
		/// </summary>
		OpPassZIncrsat         = 0x40000000,
	
		/// <summary>
		/// Decrement and wrap.
		/// </summary>
		OpPassZDecr            = 0x50000000,
	
		/// <summary>
		/// Decrement and clamp.
		/// </summary>
		OpPassZDecrsat         = 0x60000000,
	
		/// <summary>
		/// Invert.
		/// </summary>
		OpPassZInvert          = 0x70000000,
		OpPassZShift           = 28,
		OpPassZMask            = 0xf0000000,
	}
	
	[AllowDuplicates]
	public enum ClearFlags : uint16
	{
		/// <summary>
		/// No clear flags.
		/// </summary>
		None                   = 0x0000,
	
		/// <summary>
		/// Clear color.
		/// </summary>
		Color                  = 0x0001,
	
		/// <summary>
		/// Clear depth.
		/// </summary>
		Depth                  = 0x0002,
	
		/// <summary>
		/// Clear stencil.
		/// </summary>
		Stencil                = 0x0004,
	
		/// <summary>
		/// Discard frame buffer attachment 0.
		/// </summary>
		DiscardColor0          = 0x0008,
	
		/// <summary>
		/// Discard frame buffer attachment 1.
		/// </summary>
		DiscardColor1          = 0x0010,
	
		/// <summary>
		/// Discard frame buffer attachment 2.
		/// </summary>
		DiscardColor2          = 0x0020,
	
		/// <summary>
		/// Discard frame buffer attachment 3.
		/// </summary>
		DiscardColor3          = 0x0040,
	
		/// <summary>
		/// Discard frame buffer attachment 4.
		/// </summary>
		DiscardColor4          = 0x0080,
	
		/// <summary>
		/// Discard frame buffer attachment 5.
		/// </summary>
		DiscardColor5          = 0x0100,
	
		/// <summary>
		/// Discard frame buffer attachment 6.
		/// </summary>
		DiscardColor6          = 0x0200,
	
		/// <summary>
		/// Discard frame buffer attachment 7.
		/// </summary>
		DiscardColor7          = 0x0400,
	
		/// <summary>
		/// Discard frame buffer depth attachment.
		/// </summary>
		DiscardDepth           = 0x0800,
	
		/// <summary>
		/// Discard frame buffer stencil attachment.
		/// </summary>
		DiscardStencil         = 0x1000,
		DiscardColorMask       = 0x07f8,
		DiscardMask            = 0x1ff8,
	}
	
	[AllowDuplicates]
	public enum DiscardFlags : uint32
	{
		/// <summary>
		/// Preserve everything.
		/// </summary>
		None                   = 0x00000000,
	
		/// <summary>
		/// Discard texture sampler and buffer bindings.
		/// </summary>
		Bindings               = 0x00000001,
	
		/// <summary>
		/// Discard index buffer.
		/// </summary>
		IndexBuffer            = 0x00000002,
	
		/// <summary>
		/// Discard instance data.
		/// </summary>
		InstanceData           = 0x00000004,
	
		/// <summary>
		/// Discard state and uniform bindings.
		/// </summary>
		State                  = 0x00000008,
	
		/// <summary>
		/// Discard transform.
		/// </summary>
		Transform              = 0x00000010,
	
		/// <summary>
		/// Discard vertex streams.
		/// </summary>
		VertexStreams          = 0x00000020,
	
		/// <summary>
		/// Discard all states.
		/// </summary>
		All                    = 0x000000ff,
	}
	
	[AllowDuplicates]
	public enum DebugFlags : uint32
	{
		/// <summary>
		/// No debug.
		/// </summary>
		None                   = 0x00000000,
	
		/// <summary>
		/// Enable wireframe for all primitives.
		/// </summary>
		Wireframe              = 0x00000001,
	
		/// <summary>
		/// Enable infinitely fast hardware test. No draw calls will be submitted to driver.
		/// It's useful when profiling to quickly assess bottleneck between CPU and GPU.
		/// </summary>
		Ifh                    = 0x00000002,
	
		/// <summary>
		/// Enable statistics display.
		/// </summary>
		Stats                  = 0x00000004,
	
		/// <summary>
		/// Enable debug text display.
		/// </summary>
		Text                   = 0x00000008,
	
		/// <summary>
		/// Enable profiler. This causes per-view statistics to be collected, available through `bgfx::Stats::ViewStats`. This is unrelated to the profiler functions in `bgfx::CallbackI`.
		/// </summary>
		Profiler               = 0x00000010,
	}
	
	[AllowDuplicates]
	public enum BufferFlags : uint16
	{
		/// <summary>
		/// 1 8-bit value
		/// </summary>
		ComputeFormat8x1       = 0x0001,
	
		/// <summary>
		/// 2 8-bit values
		/// </summary>
		ComputeFormat8x2       = 0x0002,
	
		/// <summary>
		/// 4 8-bit values
		/// </summary>
		ComputeFormat8x4       = 0x0003,
	
		/// <summary>
		/// 1 16-bit value
		/// </summary>
		ComputeFormat16x1      = 0x0004,
	
		/// <summary>
		/// 2 16-bit values
		/// </summary>
		ComputeFormat16x2      = 0x0005,
	
		/// <summary>
		/// 4 16-bit values
		/// </summary>
		ComputeFormat16x4      = 0x0006,
	
		/// <summary>
		/// 1 32-bit value
		/// </summary>
		ComputeFormat32x1      = 0x0007,
	
		/// <summary>
		/// 2 32-bit values
		/// </summary>
		ComputeFormat32x2      = 0x0008,
	
		/// <summary>
		/// 4 32-bit values
		/// </summary>
		ComputeFormat32x4      = 0x0009,
		ComputeFormatShift     = 0,
		ComputeFormatMask      = 0x000f,
	
		/// <summary>
		/// Type `int`.
		/// </summary>
		ComputeTypeInt         = 0x0010,
	
		/// <summary>
		/// Type `uint`.
		/// </summary>
		ComputeTypeUint        = 0x0020,
	
		/// <summary>
		/// Type `float`.
		/// </summary>
		ComputeTypeFloat       = 0x0030,
		ComputeTypeShift       = 4,
		ComputeTypeMask        = 0x0030,
		None                   = 0x0000,
	
		/// <summary>
		/// Buffer will be read by shader.
		/// </summary>
		ComputeRead            = 0x0100,
	
		/// <summary>
		/// Buffer will be used for writing.
		/// </summary>
		ComputeWrite           = 0x0200,
	
		/// <summary>
		/// Buffer will be used for storing draw indirect commands.
		/// </summary>
		DrawIndirect           = 0x0400,
	
		/// <summary>
		/// Allow dynamic index/vertex buffer resize during update.
		/// </summary>
		AllowResize            = 0x0800,
	
		/// <summary>
		/// Index buffer contains 32-bit indices.
		/// </summary>
		Index32                = 0x1000,
		ComputeReadWrite       = 0x0300,
	}
	
	[AllowDuplicates]
	public enum TextureFlags : uint64
	{
		None                   = 0x0000000000000000,
	
		/// <summary>
		/// Texture will be used for MSAA sampling.
		/// </summary>
		MsaaSample             = 0x0000000800000000,
	
		/// <summary>
		/// Render target no MSAA.
		/// </summary>
		Rt                     = 0x0000001000000000,
	
		/// <summary>
		/// Texture will be used for compute write.
		/// </summary>
		ComputeWrite           = 0x0000100000000000,
	
		/// <summary>
		/// Sample texture as sRGB.
		/// </summary>
		Srgb                   = 0x0000200000000000,
	
		/// <summary>
		/// Texture will be used as blit destination.
		/// </summary>
		BlitDst                = 0x0000400000000000,
	
		/// <summary>
		/// Texture will be used for read back from GPU.
		/// </summary>
		ReadBack               = 0x0000800000000000,
	
		/// <summary>
		/// Render target MSAAx2 mode.
		/// </summary>
		RtMsaaX2               = 0x0000002000000000,
	
		/// <summary>
		/// Render target MSAAx4 mode.
		/// </summary>
		RtMsaaX4               = 0x0000003000000000,
	
		/// <summary>
		/// Render target MSAAx8 mode.
		/// </summary>
		RtMsaaX8               = 0x0000004000000000,
	
		/// <summary>
		/// Render target MSAAx16 mode.
		/// </summary>
		RtMsaaX16              = 0x0000005000000000,
		RtMsaaShift            = 36,
		RtMsaaMask             = 0x0000007000000000,
	
		/// <summary>
		/// Render target will be used for writing
		/// </summary>
		RtWriteOnly            = 0x0000008000000000,
		RtShift                = 36,
		RtMask                 = 0x000000f000000000,
	}
	
	[AllowDuplicates]
	public enum SamplerFlags : uint32
	{
		/// <summary>
		/// Wrap U mode: Mirror
		/// </summary>
		UMirror                = 0x00000001,
	
		/// <summary>
		/// Wrap U mode: Clamp
		/// </summary>
		UClamp                 = 0x00000002,
	
		/// <summary>
		/// Wrap U mode: Border
		/// </summary>
		UBorder                = 0x00000003,
		UShift                 = 0,
		UMask                  = 0x00000003,
	
		/// <summary>
		/// Wrap V mode: Mirror
		/// </summary>
		VMirror                = 0x00000004,
	
		/// <summary>
		/// Wrap V mode: Clamp
		/// </summary>
		VClamp                 = 0x00000008,
	
		/// <summary>
		/// Wrap V mode: Border
		/// </summary>
		VBorder                = 0x0000000c,
		VShift                 = 2,
		VMask                  = 0x0000000c,
	
		/// <summary>
		/// Wrap W mode: Mirror
		/// </summary>
		WMirror                = 0x00000010,
	
		/// <summary>
		/// Wrap W mode: Clamp
		/// </summary>
		WClamp                 = 0x00000020,
	
		/// <summary>
		/// Wrap W mode: Border
		/// </summary>
		WBorder                = 0x00000030,
		WShift                 = 4,
		WMask                  = 0x00000030,
	
		/// <summary>
		/// Min sampling mode: Point
		/// </summary>
		MinPoint               = 0x00000040,
	
		/// <summary>
		/// Min sampling mode: Anisotropic
		/// </summary>
		MinAnisotropic         = 0x00000080,
		MinShift               = 6,
		MinMask                = 0x000000c0,
	
		/// <summary>
		/// Mag sampling mode: Point
		/// </summary>
		MagPoint               = 0x00000100,
	
		/// <summary>
		/// Mag sampling mode: Anisotropic
		/// </summary>
		MagAnisotropic         = 0x00000200,
		MagShift               = 8,
		MagMask                = 0x00000300,
	
		/// <summary>
		/// Mip sampling mode: Point
		/// </summary>
		MipPoint               = 0x00000400,
		MipShift               = 10,
		MipMask                = 0x00000400,
	
		/// <summary>
		/// Compare when sampling depth texture: less.
		/// </summary>
		CompareLess            = 0x00010000,
	
		/// <summary>
		/// Compare when sampling depth texture: less or equal.
		/// </summary>
		CompareLequal          = 0x00020000,
	
		/// <summary>
		/// Compare when sampling depth texture: equal.
		/// </summary>
		CompareEqual           = 0x00030000,
	
		/// <summary>
		/// Compare when sampling depth texture: greater or equal.
		/// </summary>
		CompareGequal          = 0x00040000,
	
		/// <summary>
		/// Compare when sampling depth texture: greater.
		/// </summary>
		CompareGreater         = 0x00050000,
	
		/// <summary>
		/// Compare when sampling depth texture: not equal.
		/// </summary>
		CompareNotequal        = 0x00060000,
	
		/// <summary>
		/// Compare when sampling depth texture: never.
		/// </summary>
		CompareNever           = 0x00070000,
	
		/// <summary>
		/// Compare when sampling depth texture: always.
		/// </summary>
		CompareAlways          = 0x00080000,
		CompareShift           = 16,
		CompareMask            = 0x000f0000,
		BorderColorShift       = 24,
		BorderColorMask        = 0x0f000000,
		ReservedShift          = 28,
		ReservedMask           = 0xf0000000,
		None                   = 0x00000000,
	
		/// <summary>
		/// Sample stencil instead of depth.
		/// </summary>
		SampleStencil          = 0x00100000,
		Point                  = 0x00000540,
		UvwMirror              = 0x00000015,
		UvwClamp               = 0x0000002a,
		UvwBorder              = 0x0000003f,
		BitsMask               = 0x000f07ff,
	}
	
	[AllowDuplicates]
	public enum ResetFlags : uint32
	{
		/// <summary>
		/// Enable 2x MSAA.
		/// </summary>
		MsaaX2                 = 0x00000010,
	
		/// <summary>
		/// Enable 4x MSAA.
		/// </summary>
		MsaaX4                 = 0x00000020,
	
		/// <summary>
		/// Enable 8x MSAA.
		/// </summary>
		MsaaX8                 = 0x00000030,
	
		/// <summary>
		/// Enable 16x MSAA.
		/// </summary>
		MsaaX16                = 0x00000040,
		MsaaShift              = 4,
		MsaaMask               = 0x00000070,
	
		/// <summary>
		/// No reset flags.
		/// </summary>
		None                   = 0x00000000,
	
		/// <summary>
		/// Not supported yet.
		/// </summary>
		Fullscreen             = 0x00000001,
	
		/// <summary>
		/// Enable V-Sync.
		/// </summary>
		Vsync                  = 0x00000080,
	
		/// <summary>
		/// Turn on/off max anisotropy.
		/// </summary>
		Maxanisotropy          = 0x00000100,
	
		/// <summary>
		/// Begin screen capture.
		/// </summary>
		Capture                = 0x00000200,
	
		/// <summary>
		/// Flush rendering after submitting to GPU.
		/// </summary>
		FlushAfterRender       = 0x00002000,
	
		/// <summary>
		/// This flag specifies where flip occurs. Default behaviour is that flip occurs
		/// before rendering new frame. This flag only has effect when `BGFX_CONFIG_MULTITHREADED=0`.
		/// </summary>
		FlipAfterRender        = 0x00004000,
	
		/// <summary>
		/// Enable sRGB backbuffer.
		/// </summary>
		SrgbBackbuffer         = 0x00008000,
	
		/// <summary>
		/// Enable HDR10 rendering.
		/// </summary>
		Hdr10                  = 0x00010000,
	
		/// <summary>
		/// Enable HiDPI rendering.
		/// </summary>
		Hidpi                  = 0x00020000,
	
		/// <summary>
		/// Enable depth clamp.
		/// </summary>
		DepthClamp             = 0x00040000,
	
		/// <summary>
		/// Suspend rendering.
		/// </summary>
		Suspend                = 0x00080000,
		FullscreenShift        = 0,
		FullscreenMask         = 0x00000001,
		ReservedShift          = 31,
		ReservedMask           = 0x80000000,
	}
	
	[AllowDuplicates]
	public enum CapsFlags : uint64
	{
		/// <summary>
		/// Alpha to coverage is supported.
		/// </summary>
		AlphaToCoverage        = 0x0000000000000001,
	
		/// <summary>
		/// Blend independent is supported.
		/// </summary>
		BlendIndependent       = 0x0000000000000002,
	
		/// <summary>
		/// Compute shaders are supported.
		/// </summary>
		Compute                = 0x0000000000000004,
	
		/// <summary>
		/// Conservative rasterization is supported.
		/// </summary>
		ConservativeRaster     = 0x0000000000000008,
	
		/// <summary>
		/// Draw indirect is supported.
		/// </summary>
		DrawIndirect           = 0x0000000000000010,
	
		/// <summary>
		/// Fragment depth is available in fragment shader.
		/// </summary>
		FragmentDepth          = 0x0000000000000020,
	
		/// <summary>
		/// Fragment ordering is available in fragment shader.
		/// </summary>
		FragmentOrdering       = 0x0000000000000040,
	
		/// <summary>
		/// Graphics debugger is present.
		/// </summary>
		GraphicsDebugger       = 0x0000000000000080,
	
		/// <summary>
		/// HDR10 rendering is supported.
		/// </summary>
		Hdr10                  = 0x0000000000000100,
	
		/// <summary>
		/// HiDPI rendering is supported.
		/// </summary>
		Hidpi                  = 0x0000000000000200,
	
		/// <summary>
		/// Image Read/Write is supported.
		/// </summary>
		ImageRw                = 0x0000000000000400,
	
		/// <summary>
		/// 32-bit indices are supported.
		/// </summary>
		Index32                = 0x0000000000000800,
	
		/// <summary>
		/// Instancing is supported.
		/// </summary>
		Instancing             = 0x0000000000001000,
	
		/// <summary>
		/// Occlusion query is supported.
		/// </summary>
		OcclusionQuery         = 0x0000000000002000,
	
		/// <summary>
		/// Renderer is on separate thread.
		/// </summary>
		RendererMultithreaded  = 0x0000000000004000,
	
		/// <summary>
		/// Multiple windows are supported.
		/// </summary>
		SwapChain              = 0x0000000000008000,
	
		/// <summary>
		/// 2D texture array is supported.
		/// </summary>
		Texture2dArray         = 0x0000000000010000,
	
		/// <summary>
		/// 3D textures are supported.
		/// </summary>
		Texture3d              = 0x0000000000020000,
	
		/// <summary>
		/// Texture blit is supported.
		/// </summary>
		TextureBlit            = 0x0000000000040000,
		TextureCompareReserved = 0x0000000000080000,
	
		/// <summary>
		/// Texture compare less equal mode is supported.
		/// </summary>
		TextureCompareLequal   = 0x0000000000100000,
	
		/// <summary>
		/// Cubemap texture array is supported.
		/// </summary>
		TextureCubeArray       = 0x0000000000200000,
	
		/// <summary>
		/// CPU direct access to GPU texture memory.
		/// </summary>
		TextureDirectAccess    = 0x0000000000400000,
	
		/// <summary>
		/// Read-back texture is supported.
		/// </summary>
		TextureReadBack        = 0x0000000000800000,
	
		/// <summary>
		/// Vertex attribute half-float is supported.
		/// </summary>
		VertexAttribHalf       = 0x0000000001000000,
	
		/// <summary>
		/// Vertex attribute 10_10_10_2 is supported.
		/// </summary>
		VertexAttribUint10     = 0x0000000002000000,
	
		/// <summary>
		/// Rendering with VertexID only is supported.
		/// </summary>
		VertexId               = 0x0000000004000000,
	
		/// <summary>
		/// Viewport layer is available in vertex shader.
		/// </summary>
		ViewportLayerArray     = 0x0000000008000000,
	
		/// <summary>
		/// All texture compare modes are supported.
		/// </summary>
		TextureCompareAll      = 0x0000000000180000,
	}
	
	[AllowDuplicates]
	public enum CapsFormatFlags : uint32
	{
		/// <summary>
		/// Texture format is not supported.
		/// </summary>
		TextureNone            = 0x00000000,
	
		/// <summary>
		/// Texture format is supported.
		/// </summary>
		Texture2d              = 0x00000001,
	
		/// <summary>
		/// Texture as sRGB format is supported.
		/// </summary>
		Texture2dSrgb          = 0x00000002,
	
		/// <summary>
		/// Texture format is emulated.
		/// </summary>
		Texture2dEmulated      = 0x00000004,
	
		/// <summary>
		/// Texture format is supported.
		/// </summary>
		Texture3d              = 0x00000008,
	
		/// <summary>
		/// Texture as sRGB format is supported.
		/// </summary>
		Texture3dSrgb          = 0x00000010,
	
		/// <summary>
		/// Texture format is emulated.
		/// </summary>
		Texture3dEmulated      = 0x00000020,
	
		/// <summary>
		/// Texture format is supported.
		/// </summary>
		TextureCube            = 0x00000040,
	
		/// <summary>
		/// Texture as sRGB format is supported.
		/// </summary>
		TextureCubeSrgb        = 0x00000080,
	
		/// <summary>
		/// Texture format is emulated.
		/// </summary>
		TextureCubeEmulated    = 0x00000100,
	
		/// <summary>
		/// Texture format can be used from vertex shader.
		/// </summary>
		TextureVertex          = 0x00000200,
	
		/// <summary>
		/// Texture format can be used as image and read from.
		/// </summary>
		TextureImageRead       = 0x00000400,
	
		/// <summary>
		/// Texture format can be used as image and written to.
		/// </summary>
		TextureImageWrite      = 0x00000800,
	
		/// <summary>
		/// Texture format can be used as frame buffer.
		/// </summary>
		TextureFramebuffer     = 0x00001000,
	
		/// <summary>
		/// Texture format can be used as MSAA frame buffer.
		/// </summary>
		TextureFramebufferMsaa = 0x00002000,
	
		/// <summary>
		/// Texture can be sampled as MSAA.
		/// </summary>
		TextureMsaa            = 0x00004000,
	
		/// <summary>
		/// Texture format supports auto-generated mips.
		/// </summary>
		TextureMipAutogen      = 0x00008000,
	}
	
	[AllowDuplicates]
	public enum ResolveFlags : uint32
	{
		/// <summary>
		/// No resolve flags.
		/// </summary>
		None                   = 0x00000000,
	
		/// <summary>
		/// Auto-generate mip maps on resolve.
		/// </summary>
		AutoGenMips            = 0x00000001,
	}
	
	[AllowDuplicates]
	public enum PciIdFlags : uint16
	{
		/// <summary>
		/// Autoselect adapter.
		/// </summary>
		None                   = 0x0000,
	
		/// <summary>
		/// Software rasterizer.
		/// </summary>
		SoftwareRasterizer     = 0x0001,
	
		/// <summary>
		/// AMD adapter.
		/// </summary>
		Amd                    = 0x1002,
	
		/// <summary>
		/// Apple adapter.
		/// </summary>
		Apple                  = 0x106b,
	
		/// <summary>
		/// Intel adapter.
		/// </summary>
		Intel                  = 0x8086,
	
		/// <summary>
		/// nVidia adapter.
		/// </summary>
		Nvidia                 = 0x10de,
	
		/// <summary>
		/// Microsoft adapter.
		/// </summary>
		Microsoft              = 0x1414,
	}
	
	[AllowDuplicates]
	public enum CubeMapFlags : uint32
	{
		/// <summary>
		/// Cubemap +x.
		/// </summary>
		PositiveX              = 0x00000000,
	
		/// <summary>
		/// Cubemap -x.
		/// </summary>
		NegativeX              = 0x00000001,
	
		/// <summary>
		/// Cubemap +y.
		/// </summary>
		PositiveY              = 0x00000002,
	
		/// <summary>
		/// Cubemap -y.
		/// </summary>
		NegativeY              = 0x00000003,
	
		/// <summary>
		/// Cubemap +z.
		/// </summary>
		PositiveZ              = 0x00000004,
	
		/// <summary>
		/// Cubemap -z.
		/// </summary>
		NegativeZ              = 0x00000005,
	}
	
	[AllowDuplicates]
	public enum Fatal : uint32
	{
		DebugCheck,
		InvalidShader,
		UnableToInitialize,
		UnableToCreateTexture,
		DeviceLost,
	
		Count
	}
	
	[AllowDuplicates]
	public enum RendererType : uint32
	{
		/// <summary>
		/// No rendering.
		/// </summary>
		Noop,
	
		/// <summary>
		/// AGC
		/// </summary>
		Agc,
	
		/// <summary>
		/// Direct3D 9.0
		/// </summary>
		Direct3D9,
	
		/// <summary>
		/// Direct3D 11.0
		/// </summary>
		Direct3D11,
	
		/// <summary>
		/// Direct3D 12.0
		/// </summary>
		Direct3D12,
	
		/// <summary>
		/// GNM
		/// </summary>
		Gnm,
	
		/// <summary>
		/// Metal
		/// </summary>
		Metal,
	
		/// <summary>
		/// NVN
		/// </summary>
		Nvn,
	
		/// <summary>
		/// OpenGL ES 2.0+
		/// </summary>
		OpenGLES,
	
		/// <summary>
		/// OpenGL 2.1+
		/// </summary>
		OpenGL,
	
		/// <summary>
		/// Vulkan
		/// </summary>
		Vulkan,
	
		/// <summary>
		/// WebGPU
		/// </summary>
		WebGPU,
	
		Count
	}
	
	[AllowDuplicates]
	public enum Access : uint32
	{
		/// <summary>
		/// Read.
		/// </summary>
		Read,
	
		/// <summary>
		/// Write.
		/// </summary>
		Write,
	
		/// <summary>
		/// Read and write.
		/// </summary>
		ReadWrite,
	
		Count
	}
	
	[AllowDuplicates]
	public enum Attrib : uint32
	{
		/// <summary>
		/// a_position
		/// </summary>
		Position,
	
		/// <summary>
		/// a_normal
		/// </summary>
		Normal,
	
		/// <summary>
		/// a_tangent
		/// </summary>
		Tangent,
	
		/// <summary>
		/// a_bitangent
		/// </summary>
		Bitangent,
	
		/// <summary>
		/// a_color0
		/// </summary>
		Color0,
	
		/// <summary>
		/// a_color1
		/// </summary>
		Color1,
	
		/// <summary>
		/// a_color2
		/// </summary>
		Color2,
	
		/// <summary>
		/// a_color3
		/// </summary>
		Color3,
	
		/// <summary>
		/// a_indices
		/// </summary>
		Indices,
	
		/// <summary>
		/// a_weight
		/// </summary>
		Weight,
	
		/// <summary>
		/// a_texcoord0
		/// </summary>
		TexCoord0,
	
		/// <summary>
		/// a_texcoord1
		/// </summary>
		TexCoord1,
	
		/// <summary>
		/// a_texcoord2
		/// </summary>
		TexCoord2,
	
		/// <summary>
		/// a_texcoord3
		/// </summary>
		TexCoord3,
	
		/// <summary>
		/// a_texcoord4
		/// </summary>
		TexCoord4,
	
		/// <summary>
		/// a_texcoord5
		/// </summary>
		TexCoord5,
	
		/// <summary>
		/// a_texcoord6
		/// </summary>
		TexCoord6,
	
		/// <summary>
		/// a_texcoord7
		/// </summary>
		TexCoord7,
	
		Count
	}
	
	[AllowDuplicates]
	public enum AttribType : uint32
	{
		/// <summary>
		/// Uint8
		/// </summary>
		Uint8,
	
		/// <summary>
		/// Uint10, availability depends on: `BGFX_CAPS_VERTEX_ATTRIB_UINT10`.
		/// </summary>
		Uint10,
	
		/// <summary>
		/// Int16
		/// </summary>
		Int16,
	
		/// <summary>
		/// Half, availability depends on: `BGFX_CAPS_VERTEX_ATTRIB_HALF`.
		/// </summary>
		Half,
	
		/// <summary>
		/// Float
		/// </summary>
		Float,
	
		Count
	}
	
	[AllowDuplicates]
	public enum TextureFormat : uint32
	{
		/// <summary>
		/// DXT1 R5G6B5A1
		/// </summary>
		BC1,
	
		/// <summary>
		/// DXT3 R5G6B5A4
		/// </summary>
		BC2,
	
		/// <summary>
		/// DXT5 R5G6B5A8
		/// </summary>
		BC3,
	
		/// <summary>
		/// LATC1/ATI1 R8
		/// </summary>
		BC4,
	
		/// <summary>
		/// LATC2/ATI2 RG8
		/// </summary>
		BC5,
	
		/// <summary>
		/// BC6H RGB16F
		/// </summary>
		BC6H,
	
		/// <summary>
		/// BC7 RGB 4-7 bits per color channel, 0-8 bits alpha
		/// </summary>
		BC7,
	
		/// <summary>
		/// ETC1 RGB8
		/// </summary>
		ETC1,
	
		/// <summary>
		/// ETC2 RGB8
		/// </summary>
		ETC2,
	
		/// <summary>
		/// ETC2 RGBA8
		/// </summary>
		ETC2A,
	
		/// <summary>
		/// ETC2 RGB8A1
		/// </summary>
		ETC2A1,
	
		/// <summary>
		/// PVRTC1 RGB 2BPP
		/// </summary>
		PTC12,
	
		/// <summary>
		/// PVRTC1 RGB 4BPP
		/// </summary>
		PTC14,
	
		/// <summary>
		/// PVRTC1 RGBA 2BPP
		/// </summary>
		PTC12A,
	
		/// <summary>
		/// PVRTC1 RGBA 4BPP
		/// </summary>
		PTC14A,
	
		/// <summary>
		/// PVRTC2 RGBA 2BPP
		/// </summary>
		PTC22,
	
		/// <summary>
		/// PVRTC2 RGBA 4BPP
		/// </summary>
		PTC24,
	
		/// <summary>
		/// ATC RGB 4BPP
		/// </summary>
		ATC,
	
		/// <summary>
		/// ATCE RGBA 8 BPP explicit alpha
		/// </summary>
		ATCE,
	
		/// <summary>
		/// ATCI RGBA 8 BPP interpolated alpha
		/// </summary>
		ATCI,
	
		/// <summary>
		/// ASTC 4x4 8.0 BPP
		/// </summary>
		ASTC4x4,
	
		/// <summary>
		/// ASTC 5x5 5.12 BPP
		/// </summary>
		ASTC5x5,
	
		/// <summary>
		/// ASTC 6x6 3.56 BPP
		/// </summary>
		ASTC6x6,
	
		/// <summary>
		/// ASTC 8x5 3.20 BPP
		/// </summary>
		ASTC8x5,
	
		/// <summary>
		/// ASTC 8x6 2.67 BPP
		/// </summary>
		ASTC8x6,
	
		/// <summary>
		/// ASTC 10x5 2.56 BPP
		/// </summary>
		ASTC10x5,
	
		/// <summary>
		/// Compressed formats above.
		/// </summary>
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
	
		/// <summary>
		/// Depth formats below.
		/// </summary>
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
	
	[AllowDuplicates]
	public enum UniformType : uint32
	{
		/// <summary>
		/// Sampler.
		/// </summary>
		Sampler,
	
		/// <summary>
		/// Reserved, do not use.
		/// </summary>
		End,
	
		/// <summary>
		/// 4 floats vector.
		/// </summary>
		Vec4,
	
		/// <summary>
		/// 3x3 matrix.
		/// </summary>
		Mat3,
	
		/// <summary>
		/// 4x4 matrix.
		/// </summary>
		Mat4,
	
		Count
	}
	
	[AllowDuplicates]
	public enum BackbufferRatio : uint32
	{
		/// <summary>
		/// Equal to backbuffer.
		/// </summary>
		Equal,
	
		/// <summary>
		/// One half size of backbuffer.
		/// </summary>
		Half,
	
		/// <summary>
		/// One quarter size of backbuffer.
		/// </summary>
		Quarter,
	
		/// <summary>
		/// One eighth size of backbuffer.
		/// </summary>
		Eighth,
	
		/// <summary>
		/// One sixteenth size of backbuffer.
		/// </summary>
		Sixteenth,
	
		/// <summary>
		/// Double size of backbuffer.
		/// </summary>
		Double,
	
		Count
	}
	
	[AllowDuplicates]
	public enum OcclusionQueryResult : uint32
	{
		/// <summary>
		/// Query failed test.
		/// </summary>
		Invisible,
	
		/// <summary>
		/// Query passed test.
		/// </summary>
		Visible,
	
		/// <summary>
		/// Query result is not available yet.
		/// </summary>
		NoResult,
	
		Count
	}
	
	[AllowDuplicates]
	public enum Topology : uint32
	{
		/// <summary>
		/// Triangle list.
		/// </summary>
		TriList,
	
		/// <summary>
		/// Triangle strip.
		/// </summary>
		TriStrip,
	
		/// <summary>
		/// Line list.
		/// </summary>
		LineList,
	
		/// <summary>
		/// Line strip.
		/// </summary>
		LineStrip,
	
		/// <summary>
		/// Point list.
		/// </summary>
		PointList,
	
		Count
	}
	
	[AllowDuplicates]
	public enum TopologyConvert : uint32
	{
		/// <summary>
		/// Flip winding order of triangle list.
		/// </summary>
		TriListFlipWinding,
	
		/// <summary>
		/// Flip winding order of triangle strip.
		/// </summary>
		TriStripFlipWinding,
	
		/// <summary>
		/// Convert triangle list to line list.
		/// </summary>
		TriListToLineList,
	
		/// <summary>
		/// Convert triangle strip to triangle list.
		/// </summary>
		TriStripToTriList,
	
		/// <summary>
		/// Convert line strip to line list.
		/// </summary>
		LineStripToLineList,
	
		Count
	}
	
	[AllowDuplicates]
	public enum TopologySort : uint32
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
	
	[AllowDuplicates]
	public enum ViewMode : uint32
	{
		/// <summary>
		/// Default sort order.
		/// </summary>
		Default,
	
		/// <summary>
		/// Sort in the same order in which submit calls were called.
		/// </summary>
		Sequential,
	
		/// <summary>
		/// Sort draw call depth in ascending order.
		/// </summary>
		DepthAscending,
	
		/// <summary>
		/// Sort draw call depth in descending order.
		/// </summary>
		DepthDescending,
	
		Count
	}
	
	[AllowDuplicates]
	public enum RenderFrame : uint32
	{
		/// <summary>
		/// Renderer context is not created yet.
		/// </summary>
		NoContext,
	
		/// <summary>
		/// Renderer context is created and rendering.
		/// </summary>
		Render,
	
		/// <summary>
		/// Renderer context wait for main thread signal timed out without rendering.
		/// </summary>
		Timeout,
	
		/// <summary>
		/// Renderer context is getting destroyed.
		/// </summary>
		Exiting,
	
		Count
	}
	
	[CRepr]
	public struct Caps
	{
		[CRepr]
		public struct GPU
		{
			public uint16 vendorId;
			public uint16 deviceId;
		}
	
		[CRepr]
		public struct Limits
		{
			public uint32 maxDrawCalls;
			public uint32 maxBlits;
			public uint32 maxTextureSize;
			public uint32 maxTextureLayers;
			public uint32 maxViews;
			public uint32 maxFrameBuffers;
			public uint32 maxFBAttachments;
			public uint32 maxPrograms;
			public uint32 maxShaders;
			public uint32 maxTextures;
			public uint32 maxTextureSamplers;
			public uint32 maxComputeBindings;
			public uint32 maxVertexLayouts;
			public uint32 maxVertexStreams;
			public uint32 maxIndexBuffers;
			public uint32 maxVertexBuffers;
			public uint32 maxDynamicIndexBuffers;
			public uint32 maxDynamicVertexBuffers;
			public uint32 maxUniforms;
			public uint32 maxOcclusionQueries;
			public uint32 maxEncoders;
			public uint32 minResourceCbSize;
			public uint32 transientVbSize;
			public uint32 transientIbSize;
		}
	
		public RendererType rendererType;
		public uint64 supported;
		public uint16 vendorId;
		public uint16 deviceId;
		public uint8 homogeneousDepth;
		public uint8 originBottomLeft;
		public uint8 numGPUs;
		public GPU[4] gpu;
		public Limits limits;
		public uint16[85] formats;
	}
	
	[CRepr]
	public struct InternalData
	{
		public Caps* caps;
		public void* context;
	}
	
	[CRepr]
	public struct PlatformData
	{
		public void* ndt;
		public void* nwh;
		public void* context;
		public void* backBuffer;
		public void* backBufferDS;
	}
	
	[CRepr]
	public struct Resolution
	{
		public TextureFormat format;
		public uint32 width;
		public uint32 height;
		public uint32 reset;
		public uint8 numBackBuffers;
		public uint8 maxFrameLatency;
	}
	
	[CRepr]
	public struct Init
	{
		[CRepr]
		public struct Limits
		{
			public uint16 maxEncoders;
			public uint32 minResourceCbSize;
			public uint32 transientVbSize;
			public uint32 transientIbSize;
		}
	
		public RendererType type;
		public uint16 vendorId;
		public uint16 deviceId;
		public uint64 capabilities;
		public uint8 debug;
		public uint8 profile;
		public PlatformData platformData;
		public Resolution resolution;
		public Limits limits;
		public void* callback;
		public void* allocator;
	}
	
	[CRepr]
	public struct Memory
	{
		public uint8* data;
		public uint32 size;
	}
	
	[CRepr]
	public struct TransientIndexBuffer
	{
		public uint8* data;
		public uint32 size;
		public uint32 startIndex;
		public IndexBufferHandle handle;
		public uint8 isIndex16;
	}
	
	[CRepr]
	public struct TransientVertexBuffer
	{
		public uint8* data;
		public uint32 size;
		public uint32 startVertex;
		public uint16 stride;
		public VertexBufferHandle handle;
		public VertexLayoutHandle layoutHandle;
	}
	
	[CRepr]
	public struct InstanceDataBuffer
	{
		public uint8* data;
		public uint32 size;
		public uint32 offset;
		public uint32 num;
		public uint16 stride;
		public VertexBufferHandle handle;
	}
	
	[CRepr]
	public struct TextureInfo
	{
		public TextureFormat format;
		public uint32 storageSize;
		public uint16 width;
		public uint16 height;
		public uint16 depth;
		public uint16 numLayers;
		public uint8 numMips;
		public uint8 bitsPerPixel;
		public uint8 cubeMap;
	}
	
	[CRepr]
	public struct UniformInfo
	{
		public char8[256] name;
		public UniformType type;
		public uint16 num;
	}
	
	[CRepr]
	public struct Attachment
	{
		public Access access;
		public TextureHandle handle;
		public uint16 mip;
		public uint16 layer;
		public uint16 numLayers;
		public uint8 resolve;
	}
	
	[CRepr]
	public struct Transform
	{
		public float* data;
		public uint16 num;
	}
	
	[CRepr]
	public struct ViewStats
	{
		public char8[256] name;
		public ViewId view;
		public int64 cpuTimeBegin;
		public int64 cpuTimeEnd;
		public int64 gpuTimeBegin;
		public int64 gpuTimeEnd;
	}
	
	[CRepr]
	public struct EncoderStats
	{
		public int64 cpuTimeBegin;
		public int64 cpuTimeEnd;
	}
	
	[CRepr]
	public struct Stats
	{
		public int64 cpuTimeFrame;
		public int64 cpuTimeBegin;
		public int64 cpuTimeEnd;
		public int64 cpuTimerFreq;
		public int64 gpuTimeBegin;
		public int64 gpuTimeEnd;
		public int64 gpuTimerFreq;
		public int64 waitRender;
		public int64 waitSubmit;
		public uint32 numDraw;
		public uint32 numCompute;
		public uint32 numBlit;
		public uint32 maxGpuLatency;
		public uint16 numDynamicIndexBuffers;
		public uint16 numDynamicVertexBuffers;
		public uint16 numFrameBuffers;
		public uint16 numIndexBuffers;
		public uint16 numOcclusionQueries;
		public uint16 numPrograms;
		public uint16 numShaders;
		public uint16 numTextures;
		public uint16 numUniforms;
		public uint16 numVertexBuffers;
		public uint16 numVertexLayouts;
		public int64 textureMemoryUsed;
		public int64 rtMemoryUsed;
		public int transientVbUsed;
		public int transientIbUsed;
		public uint32[5] numPrims;
		public int64 gpuMemoryMax;
		public int64 gpuMemoryUsed;
		public uint16 width;
		public uint16 height;
		public uint16 textWidth;
		public uint16 textHeight;
		public uint16 numViews;
		public ViewStats* viewStats;
		public uint8 numEncoders;
		public EncoderStats* encoderStats;
	}
	
	[CRepr]
	public struct VertexLayout
	{
		public uint32 hash;
		public uint16 stride;
		public uint16[18] offset;
		public uint16[18] attributes;
	}
	
	[CRepr]
	public struct Encoder
	{
	}
	
	[CRepr]
	public struct DynamicIndexBufferHandle {
	    public uint16 idx;
	    public bool Valid => idx != uint16.MaxValue;
	}
	
	[CRepr]
	public struct DynamicVertexBufferHandle {
	    public uint16 idx;
	    public bool Valid => idx != uint16.MaxValue;
	}
	
	[CRepr]
	public struct FrameBufferHandle {
	    public uint16 idx;
	    public bool Valid => idx != uint16.MaxValue;
	}
	
	[CRepr]
	public struct IndexBufferHandle {
	    public uint16 idx;
	    public bool Valid => idx != uint16.MaxValue;
	}
	
	[CRepr]
	public struct IndirectBufferHandle {
	    public uint16 idx;
	    public bool Valid => idx != uint16.MaxValue;
	}
	
	[CRepr]
	public struct OcclusionQueryHandle {
	    public uint16 idx;
	    public bool Valid => idx != uint16.MaxValue;
	}
	
	[CRepr]
	public struct ProgramHandle {
	    public uint16 idx;
	    public bool Valid => idx != uint16.MaxValue;
	}
	
	[CRepr]
	public struct ShaderHandle {
	    public uint16 idx;
	    public bool Valid => idx != uint16.MaxValue;
	}
	
	[CRepr]
	public struct TextureHandle {
	    public uint16 idx;
	    public bool Valid => idx != uint16.MaxValue;
	}
	
	[CRepr]
	public struct UniformHandle {
	    public uint16 idx;
	    public bool Valid => idx != uint16.MaxValue;
	}
	
	[CRepr]
	public struct VertexBufferHandle {
	    public uint16 idx;
	    public bool Valid => idx != uint16.MaxValue;
	}
	
	[CRepr]
	public struct VertexLayoutHandle {
	    public uint16 idx;
	    public bool Valid => idx != uint16.MaxValue;
	}
	

	/// <summary>
	/// Init attachment.
	/// </summary>
	///
	/// <param name="_handle">Render target texture handle.</param>
	/// <param name="_access">Access. See `Access::Enum`.</param>
	/// <param name="_layer">Cubemap side or depth layer/slice to use.</param>
	/// <param name="_numLayers">Number of texture layer/slice(s) in array to use.</param>
	/// <param name="_mip">Mip level.</param>
	/// <param name="_resolve">Resolve flags. See: `BGFX_RESOLVE_*`</param>
	///
	[LinkName("bgfx_attachment_init")]
	public static extern void attachment_init(Attachment* _this, TextureHandle _handle, Access _access, uint16 _layer, uint16 _numLayers, uint16 _mip, uint8 _resolve);
	
	/// <summary>
	/// Start VertexLayout.
	/// </summary>
	///
	/// <param name="_rendererType">Renderer backend type. See: `bgfx::RendererType`</param>
	///
	[LinkName("bgfx_vertex_layout_begin")]
	public static extern VertexLayout* vertex_layout_begin(VertexLayout* _this, RendererType _rendererType);
	
	/// <summary>
	/// Add attribute to VertexLayout.
	/// @remarks Must be called between begin/end.
	/// </summary>
	///
	/// <param name="_attrib">Attribute semantics. See: `bgfx::Attrib`</param>
	/// <param name="_num">Number of elements 1, 2, 3 or 4.</param>
	/// <param name="_type">Element type.</param>
	/// <param name="_normalized">When using fixed point AttribType (f.e. Uint8) value will be normalized for vertex shader usage. When normalized is set to true, AttribType::Uint8 value in range 0-255 will be in range 0.0-1.0 in vertex shader.</param>
	/// <param name="_asInt">Packaging rule for vertexPack, vertexUnpack, and vertexConvert for AttribType::Uint8 and AttribType::Int16. Unpacking code must be implemented inside vertex shader.</param>
	///
	[LinkName("bgfx_vertex_layout_add")]
	public static extern VertexLayout* vertex_layout_add(VertexLayout* _this, Attrib _attrib, uint8 _num, AttribType _type, bool _normalized, bool _asInt);
	
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
	[LinkName("bgfx_vertex_layout_decode")]
	public static extern void vertex_layout_decode(VertexLayout* _this, Attrib _attrib, uint8 * _num, AttribType* _type, bool* _normalized, bool* _asInt);
	
	/// <summary>
	/// Returns `true` if VertexLayout contains attribute.
	/// </summary>
	///
	/// <param name="_attrib">Attribute semantics. See: `bgfx::Attrib`</param>
	///
	[LinkName("bgfx_vertex_layout_has")]
	public static extern bool vertex_layout_has(VertexLayout* _this, Attrib _attrib);
	
	/// <summary>
	/// Skip `_num` bytes in vertex stream.
	/// </summary>
	///
	/// <param name="_num">Number of bytes to skip.</param>
	///
	[LinkName("bgfx_vertex_layout_skip")]
	public static extern VertexLayout* vertex_layout_skip(VertexLayout* _this, uint8 _num);
	
	/// <summary>
	/// End VertexLayout.
	/// </summary>
	///
	[LinkName("bgfx_vertex_layout_end")]
	public static extern void vertex_layout_end(VertexLayout* _this);
	
	/// <summary>
	/// Pack vertex attribute into vertex stream format.
	/// </summary>
	///
	/// <param name="_input">Value to be packed into vertex stream.</param>
	/// <param name="_inputNormalized">`true` if input value is already normalized.</param>
	/// <param name="_attr">Attribute to pack.</param>
	/// <param name="_layout">Vertex stream layout.</param>
	/// <param name="_data">Destination vertex stream where data will be packed.</param>
	/// <param name="_index">Vertex index that will be modified.</param>
	///
	[LinkName("bgfx_vertex_pack")]
	public static extern void vertex_pack(float _input, bool _inputNormalized, Attrib _attr, VertexLayout* _layout, void* _data, uint32 _index);
	
	/// <summary>
	/// Unpack vertex attribute from vertex stream format.
	/// </summary>
	///
	/// <param name="_output">Result of unpacking.</param>
	/// <param name="_attr">Attribute to unpack.</param>
	/// <param name="_layout">Vertex stream layout.</param>
	/// <param name="_data">Source vertex stream from where data will be unpacked.</param>
	/// <param name="_index">Vertex index that will be unpacked.</param>
	///
	[LinkName("bgfx_vertex_unpack")]
	public static extern void vertex_unpack(float _output, Attrib _attr, VertexLayout* _layout, void* _data, uint32 _index);
	
	/// <summary>
	/// Converts vertex stream data from one vertex stream format to another.
	/// </summary>
	///
	/// <param name="_dstLayout">Destination vertex stream layout.</param>
	/// <param name="_dstData">Destination vertex stream.</param>
	/// <param name="_srcLayout">Source vertex stream layout.</param>
	/// <param name="_srcData">Source vertex stream data.</param>
	/// <param name="_num">Number of vertices to convert from source to destination.</param>
	///
	[LinkName("bgfx_vertex_convert")]
	public static extern void vertex_convert(VertexLayout* _dstLayout, void* _dstData, VertexLayout* _srcLayout, void* _srcData, uint32 _num);
	
	/// <summary>
	/// Weld vertices.
	/// </summary>
	///
	/// <param name="_output">Welded vertices remapping table. The size of buffer must be the same as number of vertices.</param>
	/// <param name="_layout">Vertex stream layout.</param>
	/// <param name="_data">Vertex stream.</param>
	/// <param name="_num">Number of vertices in vertex stream.</param>
	/// <param name="_index32">Set to `true` if input indices are 32-bit.</param>
	/// <param name="_epsilon">Error tolerance for vertex position comparison.</param>
	///
	[LinkName("bgfx_weld_vertices")]
	public static extern uint32 weld_vertices(void* _output, VertexLayout* _layout, void* _data, uint32 _num, bool _index32, float _epsilon);
	
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
	[LinkName("bgfx_topology_convert")]
	public static extern uint32 topology_convert(TopologyConvert _conversion, void* _dst, uint32 _dstSize, void* _indices, uint32 _numIndices, bool _index32);
	
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
	[LinkName("bgfx_topology_sort_tri_list")]
	public static extern void topology_sort_tri_list(TopologySort _sort, void* _dst, uint32 _dstSize, float _dir, float _pos, void* _vertices, uint32 _stride, void* _indices, uint32 _numIndices, bool _index32);
	
	/// <summary>
	/// Returns supported backend API renderers.
	/// </summary>
	///
	/// <param name="_max">Maximum number of elements in _enum array.</param>
	/// <param name="_enum">Array where supported renderers will be written.</param>
	///
	[LinkName("bgfx_get_supported_renderers")]
	public static extern uint8 get_supported_renderers(uint8 _max, RendererType* _enum);
	
	/// <summary>
	/// Returns name of renderer.
	/// </summary>
	///
	/// <param name="_type">Renderer backend type. See: `bgfx::RendererType`</param>
	///
	[LinkName("bgfx_get_renderer_name")]
	public static extern char8* get_renderer_name(RendererType _type);
	
	[LinkName("bgfx_init_ctor")]
	public static extern void init_ctor(Init* _init);
	
	/// <summary>
	/// Initialize the bgfx library.
	/// </summary>
	///
	/// <param name="_init">Initialization parameters. See: `bgfx::Init` for more info.</param>
	///
	[LinkName("bgfx_init")]
	public static extern bool init(Init* _init);
	
	/// <summary>
	/// Shutdown bgfx library.
	/// </summary>
	///
	[LinkName("bgfx_shutdown")]
	public static extern void shutdown();
	
	/// <summary>
	/// Reset graphic settings and back-buffer size.
	/// @attention This call doesn’t change the window size, it just resizes
	///   the back-buffer. Your windowing code controls the window size.
	/// </summary>
	///
	/// <param name="_width">Back-buffer width.</param>
	/// <param name="_height">Back-buffer height.</param>
	/// <param name="_flags">See: `BGFX_RESET_*` for more info.   - `BGFX_RESET_NONE` - No reset flags.   - `BGFX_RESET_FULLSCREEN` - Not supported yet.   - `BGFX_RESET_MSAA_X[2/4/8/16]` - Enable 2, 4, 8 or 16 x MSAA.   - `BGFX_RESET_VSYNC` - Enable V-Sync.   - `BGFX_RESET_MAXANISOTROPY` - Turn on/off max anisotropy.   - `BGFX_RESET_CAPTURE` - Begin screen capture.   - `BGFX_RESET_FLUSH_AFTER_RENDER` - Flush rendering after submitting to GPU.   - `BGFX_RESET_FLIP_AFTER_RENDER` - This flag  specifies where flip     occurs. Default behaviour is that flip occurs before rendering new     frame. This flag only has effect when `BGFX_CONFIG_MULTITHREADED=0`.   - `BGFX_RESET_SRGB_BACKBUFFER` - Enable sRGB back-buffer.</param>
	/// <param name="_format">Texture format. See: `TextureFormat::Enum`.</param>
	///
	[LinkName("bgfx_reset")]
	public static extern void reset(uint32 _width, uint32 _height, uint32 _flags, TextureFormat _format);
	
	/// <summary>
	/// Advance to next frame. When using multithreaded renderer, this call
	/// just swaps internal buffers, kicks render thread, and returns. In
	/// singlethreaded renderer this call does frame rendering.
	/// </summary>
	///
	/// <param name="_capture">Capture frame with graphics debugger.</param>
	///
	[LinkName("bgfx_frame")]
	public static extern uint32 frame(bool _capture);
	
	/// <summary>
	/// Returns current renderer backend API type.
	/// @remarks
	///   Library must be initialized.
	/// </summary>
	///
	[LinkName("bgfx_get_renderer_type")]
	public static extern RendererType get_renderer_type();
	
	/// <summary>
	/// Returns renderer capabilities.
	/// @remarks
	///   Library must be initialized.
	/// </summary>
	///
	[LinkName("bgfx_get_caps")]
	public static extern Caps* get_caps();
	
	/// <summary>
	/// Returns performance counters.
	/// @attention Pointer returned is valid until `bgfx::frame` is called.
	/// </summary>
	///
	[LinkName("bgfx_get_stats")]
	public static extern Stats* get_stats();
	
	/// <summary>
	/// Allocate buffer to pass to bgfx calls. Data will be freed inside bgfx.
	/// </summary>
	///
	/// <param name="_size">Size to allocate.</param>
	///
	[LinkName("bgfx_alloc")]
	public static extern Memory* alloc(uint32 _size);
	
	/// <summary>
	/// Allocate buffer and copy data into it. Data will be freed inside bgfx.
	/// </summary>
	///
	/// <param name="_data">Pointer to data to be copied.</param>
	/// <param name="_size">Size of data to be copied.</param>
	///
	[LinkName("bgfx_copy")]
	public static extern Memory* copy(void* _data, uint32 _size);
	
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
	[LinkName("bgfx_make_ref")]
	public static extern Memory* make_ref(void* _data, uint32 _size);
	
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
	[LinkName("bgfx_make_ref_release")]
	public static extern Memory* make_ref_release(void* _data, uint32 _size, void* _releaseFn, void* _userData);
	
	/// <summary>
	/// Set debug flags.
	/// </summary>
	///
	/// <param name="_debug">Available flags:   - `BGFX_DEBUG_IFH` - Infinitely fast hardware. When this flag is set     all rendering calls will be skipped. This is useful when profiling     to quickly assess potential bottlenecks between CPU and GPU.   - `BGFX_DEBUG_PROFILER` - Enable profiler.   - `BGFX_DEBUG_STATS` - Display internal statistics.   - `BGFX_DEBUG_TEXT` - Display debug text.   - `BGFX_DEBUG_WIREFRAME` - Wireframe rendering. All rendering     primitives will be rendered as lines.</param>
	///
	[LinkName("bgfx_set_debug")]
	public static extern void set_debug(uint32 _debug);
	
	/// <summary>
	/// Clear internal debug text buffer.
	/// </summary>
	///
	/// <param name="_attr">Background color.</param>
	/// <param name="_small">Default 8x16 or 8x8 font.</param>
	///
	[LinkName("bgfx_dbg_text_clear")]
	public static extern void dbg_text_clear(uint8 _attr, bool _small);
	
	/// <summary>
	/// Print formatted data to internal debug text character-buffer (VGA-compatible text mode).
	/// </summary>
	///
	/// <param name="_x">Position x from the left corner of the window.</param>
	/// <param name="_y">Position y from the top corner of the window.</param>
	/// <param name="_attr">Color palette. Where top 4-bits represent index of background, and bottom 4-bits represent foreground color from standard VGA text palette (ANSI escape codes).</param>
	/// <param name="_format">`printf` style format.</param>
	///
	[LinkName("bgfx_dbg_text_printf")]
	public static extern void dbg_text_printf(uint16 _x, uint16 _y, uint8 _attr, char8* _format, ... );
	
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
	[LinkName("bgfx_dbg_text_vprintf")]
	public static extern void dbg_text_vprintf(uint16 _x, uint16 _y, uint8 _attr, char8* _format, void* _argList);
	
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
	[LinkName("bgfx_dbg_text_image")]
	public static extern void dbg_text_image(uint16 _x, uint16 _y, uint16 _width, uint16 _height, void* _data, uint16 _pitch);
	
	/// <summary>
	/// Create static index buffer.
	/// </summary>
	///
	/// <param name="_mem">Index buffer data.</param>
	/// <param name="_flags">Buffer creation flags.   - `BGFX_BUFFER_NONE` - No flags.   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of       data is passed. If this flag is not specified, and more data is passed on update, the buffer       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic       buffers.   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on       index buffers.</param>
	///
	[LinkName("bgfx_create_index_buffer")]
	public static extern IndexBufferHandle create_index_buffer(Memory* _mem, uint16 _flags);
	
	/// <summary>
	/// Set static index buffer debug name.
	/// </summary>
	///
	/// <param name="_handle">Static index buffer handle.</param>
	/// <param name="_name">Static index buffer name.</param>
	/// <param name="_len">Static index buffer name length (if length is INT32_MAX, it's expected that _name is zero terminated string.</param>
	///
	[LinkName("bgfx_set_index_buffer_name")]
	public static extern void set_index_buffer_name(IndexBufferHandle _handle, char8* _name, int _len);
	
	/// <summary>
	/// Destroy static index buffer.
	/// </summary>
	///
	/// <param name="_handle">Static index buffer handle.</param>
	///
	[LinkName("bgfx_destroy_index_buffer")]
	public static extern void destroy_index_buffer(IndexBufferHandle _handle);
	
	/// <summary>
	/// Create vertex layout.
	/// </summary>
	///
	/// <param name="_layout">Vertex layout.</param>
	///
	[LinkName("bgfx_create_vertex_layout")]
	public static extern VertexLayoutHandle create_vertex_layout(VertexLayout* _layout);
	
	/// <summary>
	/// Destroy vertex layout.
	/// </summary>
	///
	/// <param name="_layoutHandle">Vertex layout handle.</param>
	///
	[LinkName("bgfx_destroy_vertex_layout")]
	public static extern void destroy_vertex_layout(VertexLayoutHandle _layoutHandle);
	
	/// <summary>
	/// Create static vertex buffer.
	/// </summary>
	///
	/// <param name="_mem">Vertex buffer data.</param>
	/// <param name="_layout">Vertex layout.</param>
	/// <param name="_flags">Buffer creation flags.  - `BGFX_BUFFER_NONE` - No flags.  - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.  - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer      is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.  - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.  - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of      data is passed. If this flag is not specified, and more data is passed on update, the buffer      will be trimmed to fit the existing buffer size. This flag has effect only on dynamic buffers.  - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on index buffers.</param>
	///
	[LinkName("bgfx_create_vertex_buffer")]
	public static extern VertexBufferHandle create_vertex_buffer(Memory* _mem, VertexLayout* _layout, uint16 _flags);
	
	/// <summary>
	/// Set static vertex buffer debug name.
	/// </summary>
	///
	/// <param name="_handle">Static vertex buffer handle.</param>
	/// <param name="_name">Static vertex buffer name.</param>
	/// <param name="_len">Static vertex buffer name length (if length is INT32_MAX, it's expected that _name is zero terminated string.</param>
	///
	[LinkName("bgfx_set_vertex_buffer_name")]
	public static extern void set_vertex_buffer_name(VertexBufferHandle _handle, char8* _name, int _len);
	
	/// <summary>
	/// Destroy static vertex buffer.
	/// </summary>
	///
	/// <param name="_handle">Static vertex buffer handle.</param>
	///
	[LinkName("bgfx_destroy_vertex_buffer")]
	public static extern void destroy_vertex_buffer(VertexBufferHandle _handle);
	
	/// <summary>
	/// Create empty dynamic index buffer.
	/// </summary>
	///
	/// <param name="_num">Number of indices.</param>
	/// <param name="_flags">Buffer creation flags.   - `BGFX_BUFFER_NONE` - No flags.   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of       data is passed. If this flag is not specified, and more data is passed on update, the buffer       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic       buffers.   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on       index buffers.</param>
	///
	[LinkName("bgfx_create_dynamic_index_buffer")]
	public static extern DynamicIndexBufferHandle create_dynamic_index_buffer(uint32 _num, uint16 _flags);
	
	/// <summary>
	/// Create a dynamic index buffer and initialize it.
	/// </summary>
	///
	/// <param name="_mem">Index buffer data.</param>
	/// <param name="_flags">Buffer creation flags.   - `BGFX_BUFFER_NONE` - No flags.   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of       data is passed. If this flag is not specified, and more data is passed on update, the buffer       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic       buffers.   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on       index buffers.</param>
	///
	[LinkName("bgfx_create_dynamic_index_buffer_mem")]
	public static extern DynamicIndexBufferHandle create_dynamic_index_buffer_mem(Memory* _mem, uint16 _flags);
	
	/// <summary>
	/// Update dynamic index buffer.
	/// </summary>
	///
	/// <param name="_handle">Dynamic index buffer handle.</param>
	/// <param name="_startIndex">Start index.</param>
	/// <param name="_mem">Index buffer data.</param>
	///
	[LinkName("bgfx_update_dynamic_index_buffer")]
	public static extern void update_dynamic_index_buffer(DynamicIndexBufferHandle _handle, uint32 _startIndex, Memory* _mem);
	
	/// <summary>
	/// Destroy dynamic index buffer.
	/// </summary>
	///
	/// <param name="_handle">Dynamic index buffer handle.</param>
	///
	[LinkName("bgfx_destroy_dynamic_index_buffer")]
	public static extern void destroy_dynamic_index_buffer(DynamicIndexBufferHandle _handle);
	
	/// <summary>
	/// Create empty dynamic vertex buffer.
	/// </summary>
	///
	/// <param name="_num">Number of vertices.</param>
	/// <param name="_layout">Vertex layout.</param>
	/// <param name="_flags">Buffer creation flags.   - `BGFX_BUFFER_NONE` - No flags.   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of       data is passed. If this flag is not specified, and more data is passed on update, the buffer       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic       buffers.   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on       index buffers.</param>
	///
	[LinkName("bgfx_create_dynamic_vertex_buffer")]
	public static extern DynamicVertexBufferHandle create_dynamic_vertex_buffer(uint32 _num, VertexLayout* _layout, uint16 _flags);
	
	/// <summary>
	/// Create dynamic vertex buffer and initialize it.
	/// </summary>
	///
	/// <param name="_mem">Vertex buffer data.</param>
	/// <param name="_layout">Vertex layout.</param>
	/// <param name="_flags">Buffer creation flags.   - `BGFX_BUFFER_NONE` - No flags.   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of       data is passed. If this flag is not specified, and more data is passed on update, the buffer       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic       buffers.   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on       index buffers.</param>
	///
	[LinkName("bgfx_create_dynamic_vertex_buffer_mem")]
	public static extern DynamicVertexBufferHandle create_dynamic_vertex_buffer_mem(Memory* _mem, VertexLayout* _layout, uint16 _flags);
	
	/// <summary>
	/// Update dynamic vertex buffer.
	/// </summary>
	///
	/// <param name="_handle">Dynamic vertex buffer handle.</param>
	/// <param name="_startVertex">Start vertex.</param>
	/// <param name="_mem">Vertex buffer data.</param>
	///
	[LinkName("bgfx_update_dynamic_vertex_buffer")]
	public static extern void update_dynamic_vertex_buffer(DynamicVertexBufferHandle _handle, uint32 _startVertex, Memory* _mem);
	
	/// <summary>
	/// Destroy dynamic vertex buffer.
	/// </summary>
	///
	/// <param name="_handle">Dynamic vertex buffer handle.</param>
	///
	[LinkName("bgfx_destroy_dynamic_vertex_buffer")]
	public static extern void destroy_dynamic_vertex_buffer(DynamicVertexBufferHandle _handle);
	
	/// <summary>
	/// Returns number of requested or maximum available indices.
	/// </summary>
	///
	/// <param name="_num">Number of required indices.</param>
	/// <param name="_index32">Set to `true` if input indices will be 32-bit.</param>
	///
	[LinkName("bgfx_get_avail_transient_index_buffer")]
	public static extern uint32 get_avail_transient_index_buffer(uint32 _num, bool _index32);
	
	/// <summary>
	/// Returns number of requested or maximum available vertices.
	/// </summary>
	///
	/// <param name="_num">Number of required vertices.</param>
	/// <param name="_layout">Vertex layout.</param>
	///
	[LinkName("bgfx_get_avail_transient_vertex_buffer")]
	public static extern uint32 get_avail_transient_vertex_buffer(uint32 _num, VertexLayout* _layout);
	
	/// <summary>
	/// Returns number of requested or maximum available instance buffer slots.
	/// </summary>
	///
	/// <param name="_num">Number of required instances.</param>
	/// <param name="_stride">Stride per instance.</param>
	///
	[LinkName("bgfx_get_avail_instance_data_buffer")]
	public static extern uint32 get_avail_instance_data_buffer(uint32 _num, uint16 _stride);
	
	/// <summary>
	/// Allocate transient index buffer.
	/// </summary>
	///
	/// <param name="_tib">TransientIndexBuffer structure is filled and is valid for the duration of frame, and it can be reused for multiple draw calls.</param>
	/// <param name="_num">Number of indices to allocate.</param>
	/// <param name="_index32">Set to `true` if input indices will be 32-bit.</param>
	///
	[LinkName("bgfx_alloc_transient_index_buffer")]
	public static extern void alloc_transient_index_buffer(TransientIndexBuffer* _tib, uint32 _num, bool _index32);
	
	/// <summary>
	/// Allocate transient vertex buffer.
	/// </summary>
	///
	/// <param name="_tvb">TransientVertexBuffer structure is filled and is valid for the duration of frame, and it can be reused for multiple draw calls.</param>
	/// <param name="_num">Number of vertices to allocate.</param>
	/// <param name="_layout">Vertex layout.</param>
	///
	[LinkName("bgfx_alloc_transient_vertex_buffer")]
	public static extern void alloc_transient_vertex_buffer(TransientVertexBuffer* _tvb, uint32 _num, VertexLayout* _layout);
	
	/// <summary>
	/// Check for required space and allocate transient vertex and index
	/// buffers. If both space requirements are satisfied function returns
	/// true.
	/// </summary>
	///
	/// <param name="_tvb">TransientVertexBuffer structure is filled and is valid for the duration of frame, and it can be reused for multiple draw calls.</param>
	/// <param name="_layout">Vertex layout.</param>
	/// <param name="_numVertices">Number of vertices to allocate.</param>
	/// <param name="_tib">TransientIndexBuffer structure is filled and is valid for the duration of frame, and it can be reused for multiple draw calls.</param>
	/// <param name="_numIndices">Number of indices to allocate.</param>
	/// <param name="_index32">Set to `true` if input indices will be 32-bit.</param>
	///
	[LinkName("bgfx_alloc_transient_buffers")]
	public static extern bool alloc_transient_buffers(TransientVertexBuffer* _tvb, VertexLayout* _layout, uint32 _numVertices, TransientIndexBuffer* _tib, uint32 _numIndices, bool _index32);
	
	/// <summary>
	/// Allocate instance data buffer.
	/// </summary>
	///
	/// <param name="_idb">InstanceDataBuffer structure is filled and is valid for duration of frame, and it can be reused for multiple draw calls.</param>
	/// <param name="_num">Number of instances.</param>
	/// <param name="_stride">Instance stride. Must be multiple of 16.</param>
	///
	[LinkName("bgfx_alloc_instance_data_buffer")]
	public static extern void alloc_instance_data_buffer(InstanceDataBuffer* _idb, uint32 _num, uint16 _stride);
	
	/// <summary>
	/// Create draw indirect buffer.
	/// </summary>
	///
	/// <param name="_num">Number of indirect calls.</param>
	///
	[LinkName("bgfx_create_indirect_buffer")]
	public static extern IndirectBufferHandle create_indirect_buffer(uint32 _num);
	
	/// <summary>
	/// Destroy draw indirect buffer.
	/// </summary>
	///
	/// <param name="_handle">Indirect buffer handle.</param>
	///
	[LinkName("bgfx_destroy_indirect_buffer")]
	public static extern void destroy_indirect_buffer(IndirectBufferHandle _handle);
	
	/// <summary>
	/// Create shader from memory buffer.
	/// </summary>
	///
	/// <param name="_mem">Shader binary.</param>
	///
	[LinkName("bgfx_create_shader")]
	public static extern ShaderHandle create_shader(Memory* _mem);
	
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
	[LinkName("bgfx_get_shader_uniforms")]
	public static extern uint16 get_shader_uniforms(ShaderHandle _handle, UniformHandle* _uniforms, uint16 _max);
	
	/// <summary>
	/// Set shader debug name.
	/// </summary>
	///
	/// <param name="_handle">Shader handle.</param>
	/// <param name="_name">Shader name.</param>
	/// <param name="_len">Shader name length (if length is INT32_MAX, it's expected that _name is zero terminated string).</param>
	///
	[LinkName("bgfx_set_shader_name")]
	public static extern void set_shader_name(ShaderHandle _handle, char8* _name, int _len);
	
	/// <summary>
	/// Destroy shader.
	/// @remark Once a shader program is created with _handle,
	///   it is safe to destroy that shader.
	/// </summary>
	///
	/// <param name="_handle">Shader handle.</param>
	///
	[LinkName("bgfx_destroy_shader")]
	public static extern void destroy_shader(ShaderHandle _handle);
	
	/// <summary>
	/// Create program with vertex and fragment shaders.
	/// </summary>
	///
	/// <param name="_vsh">Vertex shader.</param>
	/// <param name="_fsh">Fragment shader.</param>
	/// <param name="_destroyShaders">If true, shaders will be destroyed when program is destroyed.</param>
	///
	[LinkName("bgfx_create_program")]
	public static extern ProgramHandle create_program(ShaderHandle _vsh, ShaderHandle _fsh, bool _destroyShaders);
	
	/// <summary>
	/// Create program with compute shader.
	/// </summary>
	///
	/// <param name="_csh">Compute shader.</param>
	/// <param name="_destroyShaders">If true, shaders will be destroyed when program is destroyed.</param>
	///
	[LinkName("bgfx_create_compute_program")]
	public static extern ProgramHandle create_compute_program(ShaderHandle _csh, bool _destroyShaders);
	
	/// <summary>
	/// Destroy program.
	/// </summary>
	///
	/// <param name="_handle">Program handle.</param>
	///
	[LinkName("bgfx_destroy_program")]
	public static extern void destroy_program(ProgramHandle _handle);
	
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
	[LinkName("bgfx_is_texture_valid")]
	public static extern bool is_texture_valid(uint16 _depth, bool _cubeMap, uint16 _numLayers, TextureFormat _format, uint64 _flags);
	
	/// <summary>
	/// Validate frame buffer parameters.
	/// </summary>
	///
	/// <param name="_num">Number of attachments.</param>
	/// <param name="_attachment">Attachment texture info. See: `bgfx::Attachment`.</param>
	///
	[LinkName("bgfx_is_frame_buffer_valid")]
	public static extern bool is_frame_buffer_valid(uint8 _num, Attachment* _attachment);
	
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
	[LinkName("bgfx_calc_texture_size")]
	public static extern void calc_texture_size(TextureInfo* _info, uint16 _width, uint16 _height, uint16 _depth, bool _cubeMap, bool _hasMips, uint16 _numLayers, TextureFormat _format);
	
	/// <summary>
	/// Create texture from memory buffer.
	/// </summary>
	///
	/// <param name="_mem">DDS, KTX or PVR texture binary data.</param>
	/// <param name="_flags">Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`) flags. Default texture sampling mode is linear, and wrap mode is repeat. - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap   mode. - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic   sampling.</param>
	/// <param name="_skip">Skip top level mips when parsing texture.</param>
	/// <param name="_info">When non-`NULL` is specified it returns parsed texture information.</param>
	///
	[LinkName("bgfx_create_texture")]
	public static extern TextureHandle create_texture(Memory* _mem, uint64 _flags, uint8 _skip, TextureInfo* _info);
	
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
	[LinkName("bgfx_create_texture_2d")]
	public static extern TextureHandle create_texture_2d(uint16 _width, uint16 _height, bool _hasMips, uint16 _numLayers, TextureFormat _format, uint64 _flags, Memory* _mem);
	
	/// <summary>
	/// Create texture with size based on back-buffer ratio. Texture will maintain ratio
	/// if back buffer resolution changes.
	/// </summary>
	///
	/// <param name="_ratio">Texture size in respect to back-buffer size. See: `BackbufferRatio::Enum`.</param>
	/// <param name="_hasMips">Indicates that texture contains full mip-map chain.</param>
	/// <param name="_numLayers">Number of layers in texture array. Must be 1 if caps `BGFX_CAPS_TEXTURE_2D_ARRAY` flag is not set.</param>
	/// <param name="_format">Texture format. See: `TextureFormat::Enum`.</param>
	/// <param name="_flags">Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`) flags. Default texture sampling mode is linear, and wrap mode is repeat. - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap   mode. - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic   sampling.</param>
	///
	[LinkName("bgfx_create_texture_2d_scaled")]
	public static extern TextureHandle create_texture_2d_scaled(BackbufferRatio _ratio, bool _hasMips, uint16 _numLayers, TextureFormat _format, uint64 _flags);
	
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
	[LinkName("bgfx_create_texture_3d")]
	public static extern TextureHandle create_texture_3d(uint16 _width, uint16 _height, uint16 _depth, bool _hasMips, TextureFormat _format, uint64 _flags, Memory* _mem);
	
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
	[LinkName("bgfx_create_texture_cube")]
	public static extern TextureHandle create_texture_cube(uint16 _size, bool _hasMips, uint16 _numLayers, TextureFormat _format, uint64 _flags, Memory* _mem);
	
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
	[LinkName("bgfx_update_texture_2d")]
	public static extern void update_texture_2d(TextureHandle _handle, uint16 _layer, uint8 _mip, uint16 _x, uint16 _y, uint16 _width, uint16 _height, Memory* _mem, uint16 _pitch);
	
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
	[LinkName("bgfx_update_texture_3d")]
	public static extern void update_texture_3d(TextureHandle _handle, uint8 _mip, uint16 _x, uint16 _y, uint16 _z, uint16 _width, uint16 _height, uint16 _depth, Memory* _mem);
	
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
	[LinkName("bgfx_update_texture_cube")]
	public static extern void update_texture_cube(TextureHandle _handle, uint16 _layer, uint8 _side, uint8 _mip, uint16 _x, uint16 _y, uint16 _width, uint16 _height, Memory* _mem, uint16 _pitch);
	
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
	[LinkName("bgfx_read_texture")]
	public static extern uint32 read_texture(TextureHandle _handle, void* _data, uint8 _mip);
	
	/// <summary>
	/// Set texture debug name.
	/// </summary>
	///
	/// <param name="_handle">Texture handle.</param>
	/// <param name="_name">Texture name.</param>
	/// <param name="_len">Texture name length (if length is INT32_MAX, it's expected that _name is zero terminated string.</param>
	///
	[LinkName("bgfx_set_texture_name")]
	public static extern void set_texture_name(TextureHandle _handle, char8* _name, int _len);
	
	/// <summary>
	/// Returns texture direct access pointer.
	/// @attention Availability depends on: `BGFX_CAPS_TEXTURE_DIRECT_ACCESS`. This feature
	///   is available on GPUs that have unified memory architecture (UMA) support.
	/// </summary>
	///
	/// <param name="_handle">Texture handle.</param>
	///
	[LinkName("bgfx_get_direct_access_ptr")]
	public static extern void* get_direct_access_ptr(TextureHandle _handle);
	
	/// <summary>
	/// Destroy texture.
	/// </summary>
	///
	/// <param name="_handle">Texture handle.</param>
	///
	[LinkName("bgfx_destroy_texture")]
	public static extern void destroy_texture(TextureHandle _handle);
	
	/// <summary>
	/// Create frame buffer (simple).
	/// </summary>
	///
	/// <param name="_width">Texture width.</param>
	/// <param name="_height">Texture height.</param>
	/// <param name="_format">Texture format. See: `TextureFormat::Enum`.</param>
	/// <param name="_textureFlags">Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`) flags. Default texture sampling mode is linear, and wrap mode is repeat. - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap   mode. - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic   sampling.</param>
	///
	[LinkName("bgfx_create_frame_buffer")]
	public static extern FrameBufferHandle create_frame_buffer(uint16 _width, uint16 _height, TextureFormat _format, uint64 _textureFlags);
	
	/// <summary>
	/// Create frame buffer with size based on back-buffer ratio. Frame buffer will maintain ratio
	/// if back buffer resolution changes.
	/// </summary>
	///
	/// <param name="_ratio">Frame buffer size in respect to back-buffer size. See: `BackbufferRatio::Enum`.</param>
	/// <param name="_format">Texture format. See: `TextureFormat::Enum`.</param>
	/// <param name="_textureFlags">Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`) flags. Default texture sampling mode is linear, and wrap mode is repeat. - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap   mode. - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic   sampling.</param>
	///
	[LinkName("bgfx_create_frame_buffer_scaled")]
	public static extern FrameBufferHandle create_frame_buffer_scaled(BackbufferRatio _ratio, TextureFormat _format, uint64 _textureFlags);
	
	/// <summary>
	/// Create MRT frame buffer from texture handles (simple).
	/// </summary>
	///
	/// <param name="_num">Number of texture handles.</param>
	/// <param name="_handles">Texture attachments.</param>
	/// <param name="_destroyTexture">If true, textures will be destroyed when frame buffer is destroyed.</param>
	///
	[LinkName("bgfx_create_frame_buffer_from_handles")]
	public static extern FrameBufferHandle create_frame_buffer_from_handles(uint8 _num, TextureHandle* _handles, bool _destroyTexture);
	
	/// <summary>
	/// Create MRT frame buffer from texture handles with specific layer and
	/// mip level.
	/// </summary>
	///
	/// <param name="_num">Number of attachments.</param>
	/// <param name="_attachment">Attachment texture info. See: `bgfx::Attachment`.</param>
	/// <param name="_destroyTexture">If true, textures will be destroyed when frame buffer is destroyed.</param>
	///
	[LinkName("bgfx_create_frame_buffer_from_attachment")]
	public static extern FrameBufferHandle create_frame_buffer_from_attachment(uint8 _num, Attachment* _attachment, bool _destroyTexture);
	
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
	[LinkName("bgfx_create_frame_buffer_from_nwh")]
	public static extern FrameBufferHandle create_frame_buffer_from_nwh(void* _nwh, uint16 _width, uint16 _height, TextureFormat _format, TextureFormat _depthFormat);
	
	/// <summary>
	/// Set frame buffer debug name.
	/// </summary>
	///
	/// <param name="_handle">Frame buffer handle.</param>
	/// <param name="_name">Frame buffer name.</param>
	/// <param name="_len">Frame buffer name length (if length is INT32_MAX, it's expected that _name is zero terminated string.</param>
	///
	[LinkName("bgfx_set_frame_buffer_name")]
	public static extern void set_frame_buffer_name(FrameBufferHandle _handle, char8* _name, int _len);
	
	/// <summary>
	/// Obtain texture handle of frame buffer attachment.
	/// </summary>
	///
	/// <param name="_handle">Frame buffer handle.</param>
	///
	[LinkName("bgfx_get_texture")]
	public static extern TextureHandle get_texture(FrameBufferHandle _handle, uint8 _attachment);
	
	/// <summary>
	/// Destroy frame buffer.
	/// </summary>
	///
	/// <param name="_handle">Frame buffer handle.</param>
	///
	[LinkName("bgfx_destroy_frame_buffer")]
	public static extern void destroy_frame_buffer(FrameBufferHandle _handle);
	
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
	[LinkName("bgfx_create_uniform")]
	public static extern UniformHandle create_uniform(char8* _name, UniformType _type, uint16 _num);
	
	/// <summary>
	/// Retrieve uniform info.
	/// </summary>
	///
	/// <param name="_handle">Handle to uniform object.</param>
	/// <param name="_info">Uniform info.</param>
	///
	[LinkName("bgfx_get_uniform_info")]
	public static extern void get_uniform_info(UniformHandle _handle, UniformInfo* _info);
	
	/// <summary>
	/// Destroy shader uniform parameter.
	/// </summary>
	///
	/// <param name="_handle">Handle to uniform object.</param>
	///
	[LinkName("bgfx_destroy_uniform")]
	public static extern void destroy_uniform(UniformHandle _handle);
	
	/// <summary>
	/// Create occlusion query.
	/// </summary>
	///
	[LinkName("bgfx_create_occlusion_query")]
	public static extern OcclusionQueryHandle create_occlusion_query();
	
	/// <summary>
	/// Retrieve occlusion query result from previous frame.
	/// </summary>
	///
	/// <param name="_handle">Handle to occlusion query object.</param>
	/// <param name="_result">Number of pixels that passed test. This argument can be `NULL` if result of occlusion query is not needed.</param>
	///
	[LinkName("bgfx_get_result")]
	public static extern OcclusionQueryResult get_result(OcclusionQueryHandle _handle, int* _result);
	
	/// <summary>
	/// Destroy occlusion query.
	/// </summary>
	///
	/// <param name="_handle">Handle to occlusion query object.</param>
	///
	[LinkName("bgfx_destroy_occlusion_query")]
	public static extern void destroy_occlusion_query(OcclusionQueryHandle _handle);
	
	/// <summary>
	/// Set palette color value.
	/// </summary>
	///
	/// <param name="_index">Index into palette.</param>
	/// <param name="_rgba">RGBA floating point values.</param>
	///
	[LinkName("bgfx_set_palette_color")]
	public static extern void set_palette_color(uint8 _index, float _rgba);
	
	/// <summary>
	/// Set palette color value.
	/// </summary>
	///
	/// <param name="_index">Index into palette.</param>
	/// <param name="_rgba">Packed 32-bit RGBA value.</param>
	///
	[LinkName("bgfx_set_palette_color_rgba8")]
	public static extern void set_palette_color_rgba8(uint8 _index, uint32 _rgba);
	
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
	[LinkName("bgfx_set_view_name")]
	public static extern void set_view_name(ViewId _id, char8* _name);
	
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
	[LinkName("bgfx_set_view_rect")]
	public static extern void set_view_rect(ViewId _id, uint16 _x, uint16 _y, uint16 _width, uint16 _height);
	
	/// <summary>
	/// Set view rectangle. Draw primitive outside view will be clipped.
	/// </summary>
	///
	/// <param name="_id">View id.</param>
	/// <param name="_x">Position x from the left corner of the window.</param>
	/// <param name="_y">Position y from the top corner of the window.</param>
	/// <param name="_ratio">Width and height will be set in respect to back-buffer size. See: `BackbufferRatio::Enum`.</param>
	///
	[LinkName("bgfx_set_view_rect_ratio")]
	public static extern void set_view_rect_ratio(ViewId _id, uint16 _x, uint16 _y, BackbufferRatio _ratio);
	
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
	[LinkName("bgfx_set_view_scissor")]
	public static extern void set_view_scissor(ViewId _id, uint16 _x, uint16 _y, uint16 _width, uint16 _height);
	
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
	[LinkName("bgfx_set_view_clear")]
	public static extern void set_view_clear(ViewId _id, uint16 _flags, uint32 _rgba, float _depth, uint8 _stencil);
	
	/// <summary>
	/// Set view clear flags with different clear color for each
	/// frame buffer texture. `bgfx::setPaletteColor` must be used to set up a
	/// clear color palette.
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
	[LinkName("bgfx_set_view_clear_mrt")]
	public static extern void set_view_clear_mrt(ViewId _id, uint16 _flags, float _depth, uint8 _stencil, uint8 _c0, uint8 _c1, uint8 _c2, uint8 _c3, uint8 _c4, uint8 _c5, uint8 _c6, uint8 _c7);
	
	/// <summary>
	/// Set view sorting mode.
	/// @remarks
	///   View mode must be set prior calling `bgfx::submit` for the view.
	/// </summary>
	///
	/// <param name="_id">View id.</param>
	/// <param name="_mode">View sort mode. See `ViewMode::Enum`.</param>
	///
	[LinkName("bgfx_set_view_mode")]
	public static extern void set_view_mode(ViewId _id, ViewMode _mode);
	
	/// <summary>
	/// Set view frame buffer.
	/// @remarks
	///   Not persistent after `bgfx::reset` call.
	/// </summary>
	///
	/// <param name="_id">View id.</param>
	/// <param name="_handle">Frame buffer handle. Passing `BGFX_INVALID_HANDLE` as frame buffer handle will draw primitives from this view into default back buffer.</param>
	///
	[LinkName("bgfx_set_view_frame_buffer")]
	public static extern void set_view_frame_buffer(ViewId _id, FrameBufferHandle _handle);
	
	/// <summary>
	/// Set view's view matrix and projection matrix,
	/// all draw primitives in this view will use these two matrices.
	/// </summary>
	///
	/// <param name="_id">View id.</param>
	/// <param name="_view">View matrix.</param>
	/// <param name="_proj">Projection matrix.</param>
	///
	[LinkName("bgfx_set_view_transform")]
	public static extern void set_view_transform(ViewId _id, void* _view, void* _proj);
	
	/// <summary>
	/// Post submit view reordering.
	/// </summary>
	///
	/// <param name="_id">First view id.</param>
	/// <param name="_num">Number of views to remap.</param>
	/// <param name="_order">View remap id table. Passing `NULL` will reset view ids to default state.</param>
	///
	[LinkName("bgfx_set_view_order")]
	public static extern void set_view_order(ViewId _id, uint16 _num, ViewId* _order);
	
	/// <summary>
	/// Reset all view settings to default.
	/// </summary>
	///
	[LinkName("bgfx_reset_view")]
	public static extern void reset_view(ViewId _id);
	
	/// <summary>
	/// Begin submitting draw calls from thread.
	/// </summary>
	///
	/// <param name="_forThread">Explicitly request an encoder for a worker thread.</param>
	///
	[LinkName("bgfx_encoder_begin")]
	public static extern Encoder* encoder_begin(bool _forThread);
	
	/// <summary>
	/// End submitting draw calls from thread.
	/// </summary>
	///
	/// <param name="_encoder">Encoder.</param>
	///
	[LinkName("bgfx_encoder_end")]
	public static extern void encoder_end(Encoder* _encoder);
	
	/// <summary>
	/// Sets a debug marker. This allows you to group graphics calls together for easy browsing in
	/// graphics debugging tools.
	/// </summary>
	///
	/// <param name="_marker">Marker string.</param>
	///
	[LinkName("bgfx_encoder_set_marker")]
	public static extern void encoder_set_marker(Encoder* _this, char8* _marker);
	
	/// <summary>
	/// Set render states for draw primitive.
	/// @remarks
	///   1. To set up more complex states use:
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
	[LinkName("bgfx_encoder_set_state")]
	public static extern void encoder_set_state(Encoder* _this, uint64 _state, uint32 _rgba);
	
	/// <summary>
	/// Set condition for rendering.
	/// </summary>
	///
	/// <param name="_handle">Occlusion query handle.</param>
	/// <param name="_visible">Render if occlusion query is visible.</param>
	///
	[LinkName("bgfx_encoder_set_condition")]
	public static extern void encoder_set_condition(Encoder* _this, OcclusionQueryHandle _handle, bool _visible);
	
	/// <summary>
	/// Set stencil test state.
	/// </summary>
	///
	/// <param name="_fstencil">Front stencil state.</param>
	/// <param name="_bstencil">Back stencil state. If back is set to `BGFX_STENCIL_NONE` _fstencil is applied to both front and back facing primitives.</param>
	///
	[LinkName("bgfx_encoder_set_stencil")]
	public static extern void encoder_set_stencil(Encoder* _this, uint32 _fstencil, uint32 _bstencil);
	
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
	[LinkName("bgfx_encoder_set_scissor")]
	public static extern uint16 encoder_set_scissor(Encoder* _this, uint16 _x, uint16 _y, uint16 _width, uint16 _height);
	
	/// <summary>
	/// Set scissor from cache for draw primitive.
	/// @remark
	///   To scissor for all primitives in view see `bgfx::setViewScissor`.
	/// </summary>
	///
	/// <param name="_cache">Index in scissor cache.</param>
	///
	[LinkName("bgfx_encoder_set_scissor_cached")]
	public static extern void encoder_set_scissor_cached(Encoder* _this, uint16 _cache);
	
	/// <summary>
	/// Set model matrix for draw primitive. If it is not called,
	/// the model will be rendered with an identity model matrix.
	/// </summary>
	///
	/// <param name="_mtx">Pointer to first matrix in array.</param>
	/// <param name="_num">Number of matrices in array.</param>
	///
	[LinkName("bgfx_encoder_set_transform")]
	public static extern uint32 encoder_set_transform(Encoder* _this, void* _mtx, uint16 _num);
	
	/// <summary>
	///  Set model matrix from matrix cache for draw primitive.
	/// </summary>
	///
	/// <param name="_cache">Index in matrix cache.</param>
	/// <param name="_num">Number of matrices from cache.</param>
	///
	[LinkName("bgfx_encoder_set_transform_cached")]
	public static extern void encoder_set_transform_cached(Encoder* _this, uint32 _cache, uint16 _num);
	
	/// <summary>
	/// Reserve matrices in internal matrix cache.
	/// @attention Pointer returned can be modified until `bgfx::frame` is called.
	/// </summary>
	///
	/// <param name="_transform">Pointer to `Transform` structure.</param>
	/// <param name="_num">Number of matrices.</param>
	///
	[LinkName("bgfx_encoder_alloc_transform")]
	public static extern uint32 encoder_alloc_transform(Encoder* _this, Transform* _transform, uint16 _num);
	
	/// <summary>
	/// Set shader uniform parameter for draw primitive.
	/// </summary>
	///
	/// <param name="_handle">Uniform.</param>
	/// <param name="_value">Pointer to uniform data.</param>
	/// <param name="_num">Number of elements. Passing `UINT16_MAX` will use the _num passed on uniform creation.</param>
	///
	[LinkName("bgfx_encoder_set_uniform")]
	public static extern void encoder_set_uniform(Encoder* _this, UniformHandle _handle, void* _value, uint16 _num);
	
	/// <summary>
	/// Set index buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_handle">Index buffer.</param>
	/// <param name="_firstIndex">First index to render.</param>
	/// <param name="_numIndices">Number of indices to render.</param>
	///
	[LinkName("bgfx_encoder_set_index_buffer")]
	public static extern void encoder_set_index_buffer(Encoder* _this, IndexBufferHandle _handle, uint32 _firstIndex, uint32 _numIndices);
	
	/// <summary>
	/// Set index buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_handle">Dynamic index buffer.</param>
	/// <param name="_firstIndex">First index to render.</param>
	/// <param name="_numIndices">Number of indices to render.</param>
	///
	[LinkName("bgfx_encoder_set_dynamic_index_buffer")]
	public static extern void encoder_set_dynamic_index_buffer(Encoder* _this, DynamicIndexBufferHandle _handle, uint32 _firstIndex, uint32 _numIndices);
	
	/// <summary>
	/// Set index buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_tib">Transient index buffer.</param>
	/// <param name="_firstIndex">First index to render.</param>
	/// <param name="_numIndices">Number of indices to render.</param>
	///
	[LinkName("bgfx_encoder_set_transient_index_buffer")]
	public static extern void encoder_set_transient_index_buffer(Encoder* _this, TransientIndexBuffer* _tib, uint32 _firstIndex, uint32 _numIndices);
	
	/// <summary>
	/// Set vertex buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_stream">Vertex stream.</param>
	/// <param name="_handle">Vertex buffer.</param>
	/// <param name="_startVertex">First vertex to render.</param>
	/// <param name="_numVertices">Number of vertices to render.</param>
	///
	[LinkName("bgfx_encoder_set_vertex_buffer")]
	public static extern void encoder_set_vertex_buffer(Encoder* _this, uint8 _stream, VertexBufferHandle _handle, uint32 _startVertex, uint32 _numVertices);
	
	/// <summary>
	/// Set vertex buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_stream">Vertex stream.</param>
	/// <param name="_handle">Vertex buffer.</param>
	/// <param name="_startVertex">First vertex to render.</param>
	/// <param name="_numVertices">Number of vertices to render.</param>
	/// <param name="_layoutHandle">Vertex layout for aliasing vertex buffer. If invalid handle is used, vertex layout used for creation of vertex buffer will be used.</param>
	///
	[LinkName("bgfx_encoder_set_vertex_buffer_with_layout")]
	public static extern void encoder_set_vertex_buffer_with_layout(Encoder* _this, uint8 _stream, VertexBufferHandle _handle, uint32 _startVertex, uint32 _numVertices, VertexLayoutHandle _layoutHandle);
	
	/// <summary>
	/// Set vertex buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_stream">Vertex stream.</param>
	/// <param name="_handle">Dynamic vertex buffer.</param>
	/// <param name="_startVertex">First vertex to render.</param>
	/// <param name="_numVertices">Number of vertices to render.</param>
	///
	[LinkName("bgfx_encoder_set_dynamic_vertex_buffer")]
	public static extern void encoder_set_dynamic_vertex_buffer(Encoder* _this, uint8 _stream, DynamicVertexBufferHandle _handle, uint32 _startVertex, uint32 _numVertices);
	
	[LinkName("bgfx_encoder_set_dynamic_vertex_buffer_with_layout")]
	public static extern void encoder_set_dynamic_vertex_buffer_with_layout(Encoder* _this, uint8 _stream, DynamicVertexBufferHandle _handle, uint32 _startVertex, uint32 _numVertices, VertexLayoutHandle _layoutHandle);
	
	/// <summary>
	/// Set vertex buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_stream">Vertex stream.</param>
	/// <param name="_tvb">Transient vertex buffer.</param>
	/// <param name="_startVertex">First vertex to render.</param>
	/// <param name="_numVertices">Number of vertices to render.</param>
	///
	[LinkName("bgfx_encoder_set_transient_vertex_buffer")]
	public static extern void encoder_set_transient_vertex_buffer(Encoder* _this, uint8 _stream, TransientVertexBuffer* _tvb, uint32 _startVertex, uint32 _numVertices);
	
	/// <summary>
	/// Set vertex buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_stream">Vertex stream.</param>
	/// <param name="_tvb">Transient vertex buffer.</param>
	/// <param name="_startVertex">First vertex to render.</param>
	/// <param name="_numVertices">Number of vertices to render.</param>
	/// <param name="_layoutHandle">Vertex layout for aliasing vertex buffer. If invalid handle is used, vertex layout used for creation of vertex buffer will be used.</param>
	///
	[LinkName("bgfx_encoder_set_transient_vertex_buffer_with_layout")]
	public static extern void encoder_set_transient_vertex_buffer_with_layout(Encoder* _this, uint8 _stream, TransientVertexBuffer* _tvb, uint32 _startVertex, uint32 _numVertices, VertexLayoutHandle _layoutHandle);
	
	/// <summary>
	/// Set number of vertices for auto generated vertices use in conjunction
	/// with gl_VertexID.
	/// @attention Availability depends on: `BGFX_CAPS_VERTEX_ID`.
	/// </summary>
	///
	/// <param name="_numVertices">Number of vertices.</param>
	///
	[LinkName("bgfx_encoder_set_vertex_count")]
	public static extern void encoder_set_vertex_count(Encoder* _this, uint32 _numVertices);
	
	/// <summary>
	/// Set instance data buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_idb">Transient instance data buffer.</param>
	/// <param name="_start">First instance data.</param>
	/// <param name="_num">Number of data instances.</param>
	///
	[LinkName("bgfx_encoder_set_instance_data_buffer")]
	public static extern void encoder_set_instance_data_buffer(Encoder* _this, InstanceDataBuffer* _idb, uint32 _start, uint32 _num);
	
	/// <summary>
	/// Set instance data buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_handle">Vertex buffer.</param>
	/// <param name="_startVertex">First instance data.</param>
	/// <param name="_num">Number of data instances. Set instance data buffer for draw primitive.</param>
	///
	[LinkName("bgfx_encoder_set_instance_data_from_vertex_buffer")]
	public static extern void encoder_set_instance_data_from_vertex_buffer(Encoder* _this, VertexBufferHandle _handle, uint32 _startVertex, uint32 _num);
	
	/// <summary>
	/// Set instance data buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_handle">Dynamic vertex buffer.</param>
	/// <param name="_startVertex">First instance data.</param>
	/// <param name="_num">Number of data instances.</param>
	///
	[LinkName("bgfx_encoder_set_instance_data_from_dynamic_vertex_buffer")]
	public static extern void encoder_set_instance_data_from_dynamic_vertex_buffer(Encoder* _this, DynamicVertexBufferHandle _handle, uint32 _startVertex, uint32 _num);
	
	/// <summary>
	/// Set number of instances for auto generated instances use in conjunction
	/// with gl_InstanceID.
	/// @attention Availability depends on: `BGFX_CAPS_VERTEX_ID`.
	/// </summary>
	///
	[LinkName("bgfx_encoder_set_instance_count")]
	public static extern void encoder_set_instance_count(Encoder* _this, uint32 _numInstances);
	
	/// <summary>
	/// Set texture stage for draw primitive.
	/// </summary>
	///
	/// <param name="_stage">Texture unit.</param>
	/// <param name="_sampler">Program sampler.</param>
	/// <param name="_handle">Texture handle.</param>
	/// <param name="_flags">Texture sampling mode. Default value UINT32_MAX uses   texture sampling settings from the texture.   - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap     mode.   - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic     sampling.</param>
	///
	[LinkName("bgfx_encoder_set_texture")]
	public static extern void encoder_set_texture(Encoder* _this, uint8 _stage, UniformHandle _sampler, TextureHandle _handle, uint32 _flags);
	
	/// <summary>
	/// Submit an empty primitive for rendering. Uniforms and draw state
	/// will be applied but no geometry will be submitted. Useful in cases
	/// when no other draw/compute primitive is submitted to view, but it's
	/// desired to execute clear view.
	/// @remark
	///   These empty draw calls will sort before ordinary draw calls.
	/// </summary>
	///
	/// <param name="_id">View id.</param>
	///
	[LinkName("bgfx_encoder_touch")]
	public static extern void encoder_touch(Encoder* _this, ViewId _id);
	
	/// <summary>
	/// Submit primitive for rendering.
	/// </summary>
	///
	/// <param name="_id">View id.</param>
	/// <param name="_program">Program.</param>
	/// <param name="_depth">Depth for sorting.</param>
	/// <param name="_flags">Discard or preserve states. See `BGFX_DISCARD_*`.</param>
	///
	[LinkName("bgfx_encoder_submit")]
	public static extern void encoder_submit(Encoder* _this, ViewId _id, ProgramHandle _program, uint32 _depth, uint8 _flags);
	
	/// <summary>
	/// Submit primitive with occlusion query for rendering.
	/// </summary>
	///
	/// <param name="_id">View id.</param>
	/// <param name="_program">Program.</param>
	/// <param name="_occlusionQuery">Occlusion query.</param>
	/// <param name="_depth">Depth for sorting.</param>
	/// <param name="_flags">Discard or preserve states. See `BGFX_DISCARD_*`.</param>
	///
	[LinkName("bgfx_encoder_submit_occlusion_query")]
	public static extern void encoder_submit_occlusion_query(Encoder* _this, ViewId _id, ProgramHandle _program, OcclusionQueryHandle _occlusionQuery, uint32 _depth, uint8 _flags);
	
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
	/// <param name="_flags">Discard or preserve states. See `BGFX_DISCARD_*`.</param>
	///
	[LinkName("bgfx_encoder_submit_indirect")]
	public static extern void encoder_submit_indirect(Encoder* _this, ViewId _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, uint16 _start, uint16 _num, uint32 _depth, uint8 _flags);
	
	/// <summary>
	/// Set compute index buffer.
	/// </summary>
	///
	/// <param name="_stage">Compute stage.</param>
	/// <param name="_handle">Index buffer handle.</param>
	/// <param name="_access">Buffer access. See `Access::Enum`.</param>
	///
	[LinkName("bgfx_encoder_set_compute_index_buffer")]
	public static extern void encoder_set_compute_index_buffer(Encoder* _this, uint8 _stage, IndexBufferHandle _handle, Access _access);
	
	/// <summary>
	/// Set compute vertex buffer.
	/// </summary>
	///
	/// <param name="_stage">Compute stage.</param>
	/// <param name="_handle">Vertex buffer handle.</param>
	/// <param name="_access">Buffer access. See `Access::Enum`.</param>
	///
	[LinkName("bgfx_encoder_set_compute_vertex_buffer")]
	public static extern void encoder_set_compute_vertex_buffer(Encoder* _this, uint8 _stage, VertexBufferHandle _handle, Access _access);
	
	/// <summary>
	/// Set compute dynamic index buffer.
	/// </summary>
	///
	/// <param name="_stage">Compute stage.</param>
	/// <param name="_handle">Dynamic index buffer handle.</param>
	/// <param name="_access">Buffer access. See `Access::Enum`.</param>
	///
	[LinkName("bgfx_encoder_set_compute_dynamic_index_buffer")]
	public static extern void encoder_set_compute_dynamic_index_buffer(Encoder* _this, uint8 _stage, DynamicIndexBufferHandle _handle, Access _access);
	
	/// <summary>
	/// Set compute dynamic vertex buffer.
	/// </summary>
	///
	/// <param name="_stage">Compute stage.</param>
	/// <param name="_handle">Dynamic vertex buffer handle.</param>
	/// <param name="_access">Buffer access. See `Access::Enum`.</param>
	///
	[LinkName("bgfx_encoder_set_compute_dynamic_vertex_buffer")]
	public static extern void encoder_set_compute_dynamic_vertex_buffer(Encoder* _this, uint8 _stage, DynamicVertexBufferHandle _handle, Access _access);
	
	/// <summary>
	/// Set compute indirect buffer.
	/// </summary>
	///
	/// <param name="_stage">Compute stage.</param>
	/// <param name="_handle">Indirect buffer handle.</param>
	/// <param name="_access">Buffer access. See `Access::Enum`.</param>
	///
	[LinkName("bgfx_encoder_set_compute_indirect_buffer")]
	public static extern void encoder_set_compute_indirect_buffer(Encoder* _this, uint8 _stage, IndirectBufferHandle _handle, Access _access);
	
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
	[LinkName("bgfx_encoder_set_image")]
	public static extern void encoder_set_image(Encoder* _this, uint8 _stage, TextureHandle _handle, uint8 _mip, Access _access, TextureFormat _format);
	
	/// <summary>
	/// Dispatch compute.
	/// </summary>
	///
	/// <param name="_id">View id.</param>
	/// <param name="_program">Compute program.</param>
	/// <param name="_numX">Number of groups X.</param>
	/// <param name="_numY">Number of groups Y.</param>
	/// <param name="_numZ">Number of groups Z.</param>
	/// <param name="_flags">Discard or preserve states. See `BGFX_DISCARD_*`.</param>
	///
	[LinkName("bgfx_encoder_dispatch")]
	public static extern void encoder_dispatch(Encoder* _this, ViewId _id, ProgramHandle _program, uint32 _numX, uint32 _numY, uint32 _numZ, uint8 _flags);
	
	/// <summary>
	/// Dispatch compute indirect.
	/// </summary>
	///
	/// <param name="_id">View id.</param>
	/// <param name="_program">Compute program.</param>
	/// <param name="_indirectHandle">Indirect buffer.</param>
	/// <param name="_start">First element in indirect buffer.</param>
	/// <param name="_num">Number of dispatches.</param>
	/// <param name="_flags">Discard or preserve states. See `BGFX_DISCARD_*`.</param>
	///
	[LinkName("bgfx_encoder_dispatch_indirect")]
	public static extern void encoder_dispatch_indirect(Encoder* _this, ViewId _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, uint16 _start, uint16 _num, uint8 _flags);
	
	/// <summary>
	/// Discard previously set state for draw or compute call.
	/// </summary>
	///
	/// <param name="_flags">Discard or preserve states. See `BGFX_DISCARD_*`.</param>
	///
	[LinkName("bgfx_encoder_discard")]
	public static extern void encoder_discard(Encoder* _this, uint8 _flags);
	
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
	[LinkName("bgfx_encoder_blit")]
	public static extern void encoder_blit(Encoder* _this, ViewId _id, TextureHandle _dst, uint8 _dstMip, uint16 _dstX, uint16 _dstY, uint16 _dstZ, TextureHandle _src, uint8 _srcMip, uint16 _srcX, uint16 _srcY, uint16 _srcZ, uint16 _width, uint16 _height, uint16 _depth);
	
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
	[LinkName("bgfx_request_screen_shot")]
	public static extern void request_screen_shot(FrameBufferHandle _handle, char8* _filePath);
	
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
	[LinkName("bgfx_render_frame")]
	public static extern RenderFrame render_frame(int _msecs);
	
	/// <summary>
	/// Set platform data.
	/// @warning Must be called before `bgfx::init`.
	/// </summary>
	///
	/// <param name="_data">Platform data.</param>
	///
	[LinkName("bgfx_set_platform_data")]
	public static extern void set_platform_data(PlatformData* _data);
	
	/// <summary>
	/// Get internal data for interop.
	/// @attention It's expected you understand some bgfx internals before you
	///   use this call.
	/// @warning Must be called only on render thread.
	/// </summary>
	///
	[LinkName("bgfx_get_internal_data")]
	public static extern InternalData* get_internal_data();
	
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
	[LinkName("bgfx_override_internal_texture_ptr")]
	public static extern void* override_internal_texture_ptr(TextureHandle _handle, void* _ptr);
	
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
	[LinkName("bgfx_override_internal_texture")]
	public static extern void* override_internal_texture(TextureHandle _handle, uint16 _width, uint16 _height, uint8 _numMips, TextureFormat _format, uint64 _flags);
	
	/// <summary>
	/// Sets a debug marker. This allows you to group graphics calls together for easy browsing in
	/// graphics debugging tools.
	/// </summary>
	///
	/// <param name="_marker">Marker string.</param>
	///
	[LinkName("bgfx_set_marker")]
	public static extern void set_marker(char8* _marker);
	
	/// <summary>
	/// Set render states for draw primitive.
	/// @remarks
	///   1. To set up more complex states use:
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
	[LinkName("bgfx_set_state")]
	public static extern void set_state(uint64 _state, uint32 _rgba);
	
	/// <summary>
	/// Set condition for rendering.
	/// </summary>
	///
	/// <param name="_handle">Occlusion query handle.</param>
	/// <param name="_visible">Render if occlusion query is visible.</param>
	///
	[LinkName("bgfx_set_condition")]
	public static extern void set_condition(OcclusionQueryHandle _handle, bool _visible);
	
	/// <summary>
	/// Set stencil test state.
	/// </summary>
	///
	/// <param name="_fstencil">Front stencil state.</param>
	/// <param name="_bstencil">Back stencil state. If back is set to `BGFX_STENCIL_NONE` _fstencil is applied to both front and back facing primitives.</param>
	///
	[LinkName("bgfx_set_stencil")]
	public static extern void set_stencil(uint32 _fstencil, uint32 _bstencil);
	
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
	[LinkName("bgfx_set_scissor")]
	public static extern uint16 set_scissor(uint16 _x, uint16 _y, uint16 _width, uint16 _height);
	
	/// <summary>
	/// Set scissor from cache for draw primitive.
	/// @remark
	///   To scissor for all primitives in view see `bgfx::setViewScissor`.
	/// </summary>
	///
	/// <param name="_cache">Index in scissor cache.</param>
	///
	[LinkName("bgfx_set_scissor_cached")]
	public static extern void set_scissor_cached(uint16 _cache);
	
	/// <summary>
	/// Set model matrix for draw primitive. If it is not called,
	/// the model will be rendered with an identity model matrix.
	/// </summary>
	///
	/// <param name="_mtx">Pointer to first matrix in array.</param>
	/// <param name="_num">Number of matrices in array.</param>
	///
	[LinkName("bgfx_set_transform")]
	public static extern uint32 set_transform(void* _mtx, uint16 _num);
	
	/// <summary>
	///  Set model matrix from matrix cache for draw primitive.
	/// </summary>
	///
	/// <param name="_cache">Index in matrix cache.</param>
	/// <param name="_num">Number of matrices from cache.</param>
	///
	[LinkName("bgfx_set_transform_cached")]
	public static extern void set_transform_cached(uint32 _cache, uint16 _num);
	
	/// <summary>
	/// Reserve matrices in internal matrix cache.
	/// @attention Pointer returned can be modified until `bgfx::frame` is called.
	/// </summary>
	///
	/// <param name="_transform">Pointer to `Transform` structure.</param>
	/// <param name="_num">Number of matrices.</param>
	///
	[LinkName("bgfx_alloc_transform")]
	public static extern uint32 alloc_transform(Transform* _transform, uint16 _num);
	
	/// <summary>
	/// Set shader uniform parameter for draw primitive.
	/// </summary>
	///
	/// <param name="_handle">Uniform.</param>
	/// <param name="_value">Pointer to uniform data.</param>
	/// <param name="_num">Number of elements. Passing `UINT16_MAX` will use the _num passed on uniform creation.</param>
	///
	[LinkName("bgfx_set_uniform")]
	public static extern void set_uniform(UniformHandle _handle, void* _value, uint16 _num);
	
	/// <summary>
	/// Set index buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_handle">Index buffer.</param>
	/// <param name="_firstIndex">First index to render.</param>
	/// <param name="_numIndices">Number of indices to render.</param>
	///
	[LinkName("bgfx_set_index_buffer")]
	public static extern void set_index_buffer(IndexBufferHandle _handle, uint32 _firstIndex, uint32 _numIndices);
	
	/// <summary>
	/// Set index buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_handle">Dynamic index buffer.</param>
	/// <param name="_firstIndex">First index to render.</param>
	/// <param name="_numIndices">Number of indices to render.</param>
	///
	[LinkName("bgfx_set_dynamic_index_buffer")]
	public static extern void set_dynamic_index_buffer(DynamicIndexBufferHandle _handle, uint32 _firstIndex, uint32 _numIndices);
	
	/// <summary>
	/// Set index buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_tib">Transient index buffer.</param>
	/// <param name="_firstIndex">First index to render.</param>
	/// <param name="_numIndices">Number of indices to render.</param>
	///
	[LinkName("bgfx_set_transient_index_buffer")]
	public static extern void set_transient_index_buffer(TransientIndexBuffer* _tib, uint32 _firstIndex, uint32 _numIndices);
	
	/// <summary>
	/// Set vertex buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_stream">Vertex stream.</param>
	/// <param name="_handle">Vertex buffer.</param>
	/// <param name="_startVertex">First vertex to render.</param>
	/// <param name="_numVertices">Number of vertices to render.</param>
	///
	[LinkName("bgfx_set_vertex_buffer")]
	public static extern void set_vertex_buffer(uint8 _stream, VertexBufferHandle _handle, uint32 _startVertex, uint32 _numVertices);
	
	/// <summary>
	/// Set vertex buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_stream">Vertex stream.</param>
	/// <param name="_handle">Vertex buffer.</param>
	/// <param name="_startVertex">First vertex to render.</param>
	/// <param name="_numVertices">Number of vertices to render.</param>
	/// <param name="_layoutHandle">Vertex layout for aliasing vertex buffer. If invalid handle is used, vertex layout used for creation of vertex buffer will be used.</param>
	///
	[LinkName("bgfx_set_vertex_buffer_with_layout")]
	public static extern void set_vertex_buffer_with_layout(uint8 _stream, VertexBufferHandle _handle, uint32 _startVertex, uint32 _numVertices, VertexLayoutHandle _layoutHandle);
	
	/// <summary>
	/// Set vertex buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_stream">Vertex stream.</param>
	/// <param name="_handle">Dynamic vertex buffer.</param>
	/// <param name="_startVertex">First vertex to render.</param>
	/// <param name="_numVertices">Number of vertices to render.</param>
	///
	[LinkName("bgfx_set_dynamic_vertex_buffer")]
	public static extern void set_dynamic_vertex_buffer(uint8 _stream, DynamicVertexBufferHandle _handle, uint32 _startVertex, uint32 _numVertices);
	
	/// <summary>
	/// Set vertex buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_stream">Vertex stream.</param>
	/// <param name="_handle">Dynamic vertex buffer.</param>
	/// <param name="_startVertex">First vertex to render.</param>
	/// <param name="_numVertices">Number of vertices to render.</param>
	/// <param name="_layoutHandle">Vertex layout for aliasing vertex buffer. If invalid handle is used, vertex layout used for creation of vertex buffer will be used.</param>
	///
	[LinkName("bgfx_set_dynamic_vertex_buffer_with_layout")]
	public static extern void set_dynamic_vertex_buffer_with_layout(uint8 _stream, DynamicVertexBufferHandle _handle, uint32 _startVertex, uint32 _numVertices, VertexLayoutHandle _layoutHandle);
	
	/// <summary>
	/// Set vertex buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_stream">Vertex stream.</param>
	/// <param name="_tvb">Transient vertex buffer.</param>
	/// <param name="_startVertex">First vertex to render.</param>
	/// <param name="_numVertices">Number of vertices to render.</param>
	///
	[LinkName("bgfx_set_transient_vertex_buffer")]
	public static extern void set_transient_vertex_buffer(uint8 _stream, TransientVertexBuffer* _tvb, uint32 _startVertex, uint32 _numVertices);
	
	/// <summary>
	/// Set vertex buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_stream">Vertex stream.</param>
	/// <param name="_tvb">Transient vertex buffer.</param>
	/// <param name="_startVertex">First vertex to render.</param>
	/// <param name="_numVertices">Number of vertices to render.</param>
	/// <param name="_layoutHandle">Vertex layout for aliasing vertex buffer. If invalid handle is used, vertex layout used for creation of vertex buffer will be used.</param>
	///
	[LinkName("bgfx_set_transient_vertex_buffer_with_layout")]
	public static extern void set_transient_vertex_buffer_with_layout(uint8 _stream, TransientVertexBuffer* _tvb, uint32 _startVertex, uint32 _numVertices, VertexLayoutHandle _layoutHandle);
	
	/// <summary>
	/// Set number of vertices for auto generated vertices use in conjunction
	/// with gl_VertexID.
	/// @attention Availability depends on: `BGFX_CAPS_VERTEX_ID`.
	/// </summary>
	///
	/// <param name="_numVertices">Number of vertices.</param>
	///
	[LinkName("bgfx_set_vertex_count")]
	public static extern void set_vertex_count(uint32 _numVertices);
	
	/// <summary>
	/// Set instance data buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_idb">Transient instance data buffer.</param>
	/// <param name="_start">First instance data.</param>
	/// <param name="_num">Number of data instances.</param>
	///
	[LinkName("bgfx_set_instance_data_buffer")]
	public static extern void set_instance_data_buffer(InstanceDataBuffer* _idb, uint32 _start, uint32 _num);
	
	/// <summary>
	/// Set instance data buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_handle">Vertex buffer.</param>
	/// <param name="_startVertex">First instance data.</param>
	/// <param name="_num">Number of data instances. Set instance data buffer for draw primitive.</param>
	///
	[LinkName("bgfx_set_instance_data_from_vertex_buffer")]
	public static extern void set_instance_data_from_vertex_buffer(VertexBufferHandle _handle, uint32 _startVertex, uint32 _num);
	
	/// <summary>
	/// Set instance data buffer for draw primitive.
	/// </summary>
	///
	/// <param name="_handle">Dynamic vertex buffer.</param>
	/// <param name="_startVertex">First instance data.</param>
	/// <param name="_num">Number of data instances.</param>
	///
	[LinkName("bgfx_set_instance_data_from_dynamic_vertex_buffer")]
	public static extern void set_instance_data_from_dynamic_vertex_buffer(DynamicVertexBufferHandle _handle, uint32 _startVertex, uint32 _num);
	
	/// <summary>
	/// Set number of instances for auto generated instances use in conjunction
	/// with gl_InstanceID.
	/// @attention Availability depends on: `BGFX_CAPS_VERTEX_ID`.
	/// </summary>
	///
	[LinkName("bgfx_set_instance_count")]
	public static extern void set_instance_count(uint32 _numInstances);
	
	/// <summary>
	/// Set texture stage for draw primitive.
	/// </summary>
	///
	/// <param name="_stage">Texture unit.</param>
	/// <param name="_sampler">Program sampler.</param>
	/// <param name="_handle">Texture handle.</param>
	/// <param name="_flags">Texture sampling mode. Default value UINT32_MAX uses   texture sampling settings from the texture.   - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap     mode.   - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic     sampling.</param>
	///
	[LinkName("bgfx_set_texture")]
	public static extern void set_texture(uint8 _stage, UniformHandle _sampler, TextureHandle _handle, uint32 _flags);
	
	/// <summary>
	/// Submit an empty primitive for rendering. Uniforms and draw state
	/// will be applied but no geometry will be submitted.
	/// @remark
	///   These empty draw calls will sort before ordinary draw calls.
	/// </summary>
	///
	/// <param name="_id">View id.</param>
	///
	[LinkName("bgfx_touch")]
	public static extern void touch(ViewId _id);
	
	/// <summary>
	/// Submit primitive for rendering.
	/// </summary>
	///
	/// <param name="_id">View id.</param>
	/// <param name="_program">Program.</param>
	/// <param name="_depth">Depth for sorting.</param>
	/// <param name="_flags">Which states to discard for next draw. See `BGFX_DISCARD_*`.</param>
	///
	[LinkName("bgfx_submit")]
	public static extern void submit(ViewId _id, ProgramHandle _program, uint32 _depth, uint8 _flags);
	
	/// <summary>
	/// Submit primitive with occlusion query for rendering.
	/// </summary>
	///
	/// <param name="_id">View id.</param>
	/// <param name="_program">Program.</param>
	/// <param name="_occlusionQuery">Occlusion query.</param>
	/// <param name="_depth">Depth for sorting.</param>
	/// <param name="_flags">Which states to discard for next draw. See `BGFX_DISCARD_*`.</param>
	///
	[LinkName("bgfx_submit_occlusion_query")]
	public static extern void submit_occlusion_query(ViewId _id, ProgramHandle _program, OcclusionQueryHandle _occlusionQuery, uint32 _depth, uint8 _flags);
	
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
	/// <param name="_flags">Which states to discard for next draw. See `BGFX_DISCARD_*`.</param>
	///
	[LinkName("bgfx_submit_indirect")]
	public static extern void submit_indirect(ViewId _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, uint16 _start, uint16 _num, uint32 _depth, uint8 _flags);
	
	/// <summary>
	/// Set compute index buffer.
	/// </summary>
	///
	/// <param name="_stage">Compute stage.</param>
	/// <param name="_handle">Index buffer handle.</param>
	/// <param name="_access">Buffer access. See `Access::Enum`.</param>
	///
	[LinkName("bgfx_set_compute_index_buffer")]
	public static extern void set_compute_index_buffer(uint8 _stage, IndexBufferHandle _handle, Access _access);
	
	/// <summary>
	/// Set compute vertex buffer.
	/// </summary>
	///
	/// <param name="_stage">Compute stage.</param>
	/// <param name="_handle">Vertex buffer handle.</param>
	/// <param name="_access">Buffer access. See `Access::Enum`.</param>
	///
	[LinkName("bgfx_set_compute_vertex_buffer")]
	public static extern void set_compute_vertex_buffer(uint8 _stage, VertexBufferHandle _handle, Access _access);
	
	/// <summary>
	/// Set compute dynamic index buffer.
	/// </summary>
	///
	/// <param name="_stage">Compute stage.</param>
	/// <param name="_handle">Dynamic index buffer handle.</param>
	/// <param name="_access">Buffer access. See `Access::Enum`.</param>
	///
	[LinkName("bgfx_set_compute_dynamic_index_buffer")]
	public static extern void set_compute_dynamic_index_buffer(uint8 _stage, DynamicIndexBufferHandle _handle, Access _access);
	
	/// <summary>
	/// Set compute dynamic vertex buffer.
	/// </summary>
	///
	/// <param name="_stage">Compute stage.</param>
	/// <param name="_handle">Dynamic vertex buffer handle.</param>
	/// <param name="_access">Buffer access. See `Access::Enum`.</param>
	///
	[LinkName("bgfx_set_compute_dynamic_vertex_buffer")]
	public static extern void set_compute_dynamic_vertex_buffer(uint8 _stage, DynamicVertexBufferHandle _handle, Access _access);
	
	/// <summary>
	/// Set compute indirect buffer.
	/// </summary>
	///
	/// <param name="_stage">Compute stage.</param>
	/// <param name="_handle">Indirect buffer handle.</param>
	/// <param name="_access">Buffer access. See `Access::Enum`.</param>
	///
	[LinkName("bgfx_set_compute_indirect_buffer")]
	public static extern void set_compute_indirect_buffer(uint8 _stage, IndirectBufferHandle _handle, Access _access);
	
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
	[LinkName("bgfx_set_image")]
	public static extern void set_image(uint8 _stage, TextureHandle _handle, uint8 _mip, Access _access, TextureFormat _format);
	
	/// <summary>
	/// Dispatch compute.
	/// </summary>
	///
	/// <param name="_id">View id.</param>
	/// <param name="_program">Compute program.</param>
	/// <param name="_numX">Number of groups X.</param>
	/// <param name="_numY">Number of groups Y.</param>
	/// <param name="_numZ">Number of groups Z.</param>
	/// <param name="_flags">Discard or preserve states. See `BGFX_DISCARD_*`.</param>
	///
	[LinkName("bgfx_dispatch")]
	public static extern void dispatch(ViewId _id, ProgramHandle _program, uint32 _numX, uint32 _numY, uint32 _numZ, uint8 _flags);
	
	/// <summary>
	/// Dispatch compute indirect.
	/// </summary>
	///
	/// <param name="_id">View id.</param>
	/// <param name="_program">Compute program.</param>
	/// <param name="_indirectHandle">Indirect buffer.</param>
	/// <param name="_start">First element in indirect buffer.</param>
	/// <param name="_num">Number of dispatches.</param>
	/// <param name="_flags">Discard or preserve states. See `BGFX_DISCARD_*`.</param>
	///
	[LinkName("bgfx_dispatch_indirect")]
	public static extern void dispatch_indirect(ViewId _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, uint16 _start, uint16 _num, uint8 _flags);
	
	/// <summary>
	/// Discard previously set state for draw or compute call.
	/// </summary>
	///
	/// <param name="_flags">Draw/compute states to discard.</param>
	///
	[LinkName("bgfx_discard")]
	public static extern void discard(uint8 _flags);
	
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
	[LinkName("bgfx_blit")]
	public static extern void blit(ViewId _id, TextureHandle _dst, uint8 _dstMip, uint16 _dstX, uint16 _dstY, uint16 _dstZ, TextureHandle _src, uint8 _srcMip, uint16 _srcX, uint16 _srcY, uint16 _srcZ, uint16 _width, uint16 _height, uint16 _depth);
	

	public static bgfx.StateFlags blend_function_separate(bgfx.StateFlags _srcRGB, bgfx.StateFlags _dstRGB, bgfx.StateFlags _srcA, bgfx.StateFlags _dstA)
	{
		return (bgfx.StateFlags)(uint64(0) | (((uint64)(_srcRGB) | ((uint64)(_dstRGB) << 4))) | (((uint64)(_srcA) | ((uint64)(_dstA) << 4)) << 8));
	}

	public static bgfx.StateFlags blend_function(bgfx.StateFlags _srcRGB, bgfx.StateFlags _dstRGB)
	{
		return blend_function_separate(_srcRGB, _dstRGB, _srcRGB, _dstRGB);
	}
}
}
