// Copyright 2011-2022 Branimir Karadzic. All rights reserved.
// License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE


//
// AUTO GENERATED! DO NOT EDIT!
//


const std = @import("std");

pub const ViewId = u16;

pub const StateFlags = u64;
/// Enable R write.
pub const StateFlags_WriteR: StateFlags                 = 0x0000000000000001;

/// Enable G write.
pub const StateFlags_WriteG: StateFlags                 = 0x0000000000000002;

/// Enable B write.
pub const StateFlags_WriteB: StateFlags                 = 0x0000000000000004;

/// Enable alpha write.
pub const StateFlags_WriteA: StateFlags                 = 0x0000000000000008;

/// Enable depth write.
pub const StateFlags_WriteZ: StateFlags                 = 0x0000004000000000;

/// Enable RGB write.
pub const StateFlags_WriteRgb: StateFlags               = 0x0000000000000007;

/// Write all channels mask.
pub const StateFlags_WriteMask: StateFlags              = 0x000000400000000f;

/// Enable depth test, less.
pub const StateFlags_DepthTestLess: StateFlags          = 0x0000000000000010;

/// Enable depth test, less or equal.
pub const StateFlags_DepthTestLequal: StateFlags        = 0x0000000000000020;

/// Enable depth test, equal.
pub const StateFlags_DepthTestEqual: StateFlags         = 0x0000000000000030;

/// Enable depth test, greater or equal.
pub const StateFlags_DepthTestGequal: StateFlags        = 0x0000000000000040;

/// Enable depth test, greater.
pub const StateFlags_DepthTestGreater: StateFlags       = 0x0000000000000050;

/// Enable depth test, not equal.
pub const StateFlags_DepthTestNotequal: StateFlags      = 0x0000000000000060;

/// Enable depth test, never.
pub const StateFlags_DepthTestNever: StateFlags         = 0x0000000000000070;

/// Enable depth test, always.
pub const StateFlags_DepthTestAlways: StateFlags        = 0x0000000000000080;
pub const StateFlags_DepthTestShift: StateFlags         = 4;
pub const StateFlags_DepthTestMask: StateFlags          = 0x00000000000000f0;

/// 0, 0, 0, 0
pub const StateFlags_BlendZero: StateFlags              = 0x0000000000001000;

/// 1, 1, 1, 1
pub const StateFlags_BlendOne: StateFlags               = 0x0000000000002000;

/// Rs, Gs, Bs, As
pub const StateFlags_BlendSrcColor: StateFlags          = 0x0000000000003000;

/// 1-Rs, 1-Gs, 1-Bs, 1-As
pub const StateFlags_BlendInvSrcColor: StateFlags       = 0x0000000000004000;

/// As, As, As, As
pub const StateFlags_BlendSrcAlpha: StateFlags          = 0x0000000000005000;

/// 1-As, 1-As, 1-As, 1-As
pub const StateFlags_BlendInvSrcAlpha: StateFlags       = 0x0000000000006000;

/// Ad, Ad, Ad, Ad
pub const StateFlags_BlendDstAlpha: StateFlags          = 0x0000000000007000;

/// 1-Ad, 1-Ad, 1-Ad ,1-Ad
pub const StateFlags_BlendInvDstAlpha: StateFlags       = 0x0000000000008000;

/// Rd, Gd, Bd, Ad
pub const StateFlags_BlendDstColor: StateFlags          = 0x0000000000009000;

/// 1-Rd, 1-Gd, 1-Bd, 1-Ad
pub const StateFlags_BlendInvDstColor: StateFlags       = 0x000000000000a000;

/// f, f, f, 1; f = min(As, 1-Ad)
pub const StateFlags_BlendSrcAlphaSat: StateFlags       = 0x000000000000b000;

/// Blend factor
pub const StateFlags_BlendFactor: StateFlags            = 0x000000000000c000;

/// 1-Blend factor
pub const StateFlags_BlendInvFactor: StateFlags         = 0x000000000000d000;
pub const StateFlags_BlendShift: StateFlags             = 12;
pub const StateFlags_BlendMask: StateFlags              = 0x000000000ffff000;

/// Blend add: src + dst.
pub const StateFlags_BlendEquationAdd: StateFlags       = 0x0000000000000000;

/// Blend subtract: src - dst.
pub const StateFlags_BlendEquationSub: StateFlags       = 0x0000000010000000;

/// Blend reverse subtract: dst - src.
pub const StateFlags_BlendEquationRevsub: StateFlags    = 0x0000000020000000;

/// Blend min: min(src, dst).
pub const StateFlags_BlendEquationMin: StateFlags       = 0x0000000030000000;

/// Blend max: max(src, dst).
pub const StateFlags_BlendEquationMax: StateFlags       = 0x0000000040000000;
pub const StateFlags_BlendEquationShift: StateFlags     = 28;
pub const StateFlags_BlendEquationMask: StateFlags      = 0x00000003f0000000;

/// Cull clockwise triangles.
pub const StateFlags_CullCw: StateFlags                 = 0x0000001000000000;

/// Cull counter-clockwise triangles.
pub const StateFlags_CullCcw: StateFlags                = 0x0000002000000000;
pub const StateFlags_CullShift: StateFlags              = 36;
pub const StateFlags_CullMask: StateFlags               = 0x0000003000000000;
pub const StateFlags_AlphaRefShift: StateFlags          = 40;
pub const StateFlags_AlphaRefMask: StateFlags           = 0x0000ff0000000000;

/// Tristrip.
pub const StateFlags_PtTristrip: StateFlags             = 0x0001000000000000;

/// Lines.
pub const StateFlags_PtLines: StateFlags                = 0x0002000000000000;

/// Line strip.
pub const StateFlags_PtLinestrip: StateFlags            = 0x0003000000000000;

/// Points.
pub const StateFlags_PtPoints: StateFlags               = 0x0004000000000000;
pub const StateFlags_PtShift: StateFlags                = 48;
pub const StateFlags_PtMask: StateFlags                 = 0x0007000000000000;
pub const StateFlags_PointSizeShift: StateFlags         = 52;
pub const StateFlags_PointSizeMask: StateFlags          = 0x00f0000000000000;

/// Enable MSAA rasterization.
pub const StateFlags_Msaa: StateFlags                   = 0x0100000000000000;

/// Enable line AA rasterization.
pub const StateFlags_Lineaa: StateFlags                 = 0x0200000000000000;

/// Enable conservative rasterization.
pub const StateFlags_ConservativeRaster: StateFlags     = 0x0400000000000000;

/// No state.
pub const StateFlags_None: StateFlags                   = 0x0000000000000000;

/// Front counter-clockwise (default is clockwise).
pub const StateFlags_FrontCcw: StateFlags               = 0x0000008000000000;

/// Enable blend independent.
pub const StateFlags_BlendIndependent: StateFlags       = 0x0000000400000000;

/// Enable alpha to coverage.
pub const StateFlags_BlendAlphaToCoverage: StateFlags   = 0x0000000800000000;

/// Default state is write to RGB, alpha, and depth with depth test less enabled, with clockwise
/// culling and MSAA (when writing into MSAA frame buffer, otherwise this flag is ignored).
pub const StateFlags_Default: StateFlags                = 0x010000500000001f;
pub const StateFlags_Mask: StateFlags                   = 0xffffffffffffffff;
pub const StateFlags_ReservedShift: StateFlags          = 61;
pub const StateFlags_ReservedMask: StateFlags           = 0xe000000000000000;

pub const StencilFlags = u32;
pub const StencilFlags_FuncRefShift: StencilFlags           = 0;
pub const StencilFlags_FuncRefMask: StencilFlags            = 0x000000ff;
pub const StencilFlags_FuncRmaskShift: StencilFlags         = 8;
pub const StencilFlags_FuncRmaskMask: StencilFlags          = 0x0000ff00;
pub const StencilFlags_None: StencilFlags                   = 0x00000000;
pub const StencilFlags_Mask: StencilFlags                   = 0xffffffff;
pub const StencilFlags_Default: StencilFlags                = 0x00000000;

/// Enable stencil test, less.
pub const StencilFlags_TestLess: StencilFlags               = 0x00010000;

/// Enable stencil test, less or equal.
pub const StencilFlags_TestLequal: StencilFlags             = 0x00020000;

/// Enable stencil test, equal.
pub const StencilFlags_TestEqual: StencilFlags              = 0x00030000;

/// Enable stencil test, greater or equal.
pub const StencilFlags_TestGequal: StencilFlags             = 0x00040000;

/// Enable stencil test, greater.
pub const StencilFlags_TestGreater: StencilFlags            = 0x00050000;

/// Enable stencil test, not equal.
pub const StencilFlags_TestNotequal: StencilFlags           = 0x00060000;

/// Enable stencil test, never.
pub const StencilFlags_TestNever: StencilFlags              = 0x00070000;

/// Enable stencil test, always.
pub const StencilFlags_TestAlways: StencilFlags             = 0x00080000;
pub const StencilFlags_TestShift: StencilFlags              = 16;
pub const StencilFlags_TestMask: StencilFlags               = 0x000f0000;

/// Zero.
pub const StencilFlags_OpFailSZero: StencilFlags            = 0x00000000;

/// Keep.
pub const StencilFlags_OpFailSKeep: StencilFlags            = 0x00100000;

/// Replace.
pub const StencilFlags_OpFailSReplace: StencilFlags         = 0x00200000;

/// Increment and wrap.
pub const StencilFlags_OpFailSIncr: StencilFlags            = 0x00300000;

/// Increment and clamp.
pub const StencilFlags_OpFailSIncrsat: StencilFlags         = 0x00400000;

/// Decrement and wrap.
pub const StencilFlags_OpFailSDecr: StencilFlags            = 0x00500000;

/// Decrement and clamp.
pub const StencilFlags_OpFailSDecrsat: StencilFlags         = 0x00600000;

/// Invert.
pub const StencilFlags_OpFailSInvert: StencilFlags          = 0x00700000;
pub const StencilFlags_OpFailSShift: StencilFlags           = 20;
pub const StencilFlags_OpFailSMask: StencilFlags            = 0x00f00000;

/// Zero.
pub const StencilFlags_OpFailZZero: StencilFlags            = 0x00000000;

/// Keep.
pub const StencilFlags_OpFailZKeep: StencilFlags            = 0x01000000;

/// Replace.
pub const StencilFlags_OpFailZReplace: StencilFlags         = 0x02000000;

/// Increment and wrap.
pub const StencilFlags_OpFailZIncr: StencilFlags            = 0x03000000;

/// Increment and clamp.
pub const StencilFlags_OpFailZIncrsat: StencilFlags         = 0x04000000;

/// Decrement and wrap.
pub const StencilFlags_OpFailZDecr: StencilFlags            = 0x05000000;

/// Decrement and clamp.
pub const StencilFlags_OpFailZDecrsat: StencilFlags         = 0x06000000;

/// Invert.
pub const StencilFlags_OpFailZInvert: StencilFlags          = 0x07000000;
pub const StencilFlags_OpFailZShift: StencilFlags           = 24;
pub const StencilFlags_OpFailZMask: StencilFlags            = 0x0f000000;

/// Zero.
pub const StencilFlags_OpPassZZero: StencilFlags            = 0x00000000;

/// Keep.
pub const StencilFlags_OpPassZKeep: StencilFlags            = 0x10000000;

/// Replace.
pub const StencilFlags_OpPassZReplace: StencilFlags         = 0x20000000;

/// Increment and wrap.
pub const StencilFlags_OpPassZIncr: StencilFlags            = 0x30000000;

/// Increment and clamp.
pub const StencilFlags_OpPassZIncrsat: StencilFlags         = 0x40000000;

/// Decrement and wrap.
pub const StencilFlags_OpPassZDecr: StencilFlags            = 0x50000000;

/// Decrement and clamp.
pub const StencilFlags_OpPassZDecrsat: StencilFlags         = 0x60000000;

/// Invert.
pub const StencilFlags_OpPassZInvert: StencilFlags          = 0x70000000;
pub const StencilFlags_OpPassZShift: StencilFlags           = 28;
pub const StencilFlags_OpPassZMask: StencilFlags            = 0xf0000000;

pub const ClearFlags = u16;
/// No clear flags.
pub const ClearFlags_None: ClearFlags                   = 0x0000;

/// Clear color.
pub const ClearFlags_Color: ClearFlags                  = 0x0001;

/// Clear depth.
pub const ClearFlags_Depth: ClearFlags                  = 0x0002;

/// Clear stencil.
pub const ClearFlags_Stencil: ClearFlags                = 0x0004;

/// Discard frame buffer attachment 0.
pub const ClearFlags_DiscardColor0: ClearFlags          = 0x0008;

/// Discard frame buffer attachment 1.
pub const ClearFlags_DiscardColor1: ClearFlags          = 0x0010;

/// Discard frame buffer attachment 2.
pub const ClearFlags_DiscardColor2: ClearFlags          = 0x0020;

/// Discard frame buffer attachment 3.
pub const ClearFlags_DiscardColor3: ClearFlags          = 0x0040;

/// Discard frame buffer attachment 4.
pub const ClearFlags_DiscardColor4: ClearFlags          = 0x0080;

/// Discard frame buffer attachment 5.
pub const ClearFlags_DiscardColor5: ClearFlags          = 0x0100;

/// Discard frame buffer attachment 6.
pub const ClearFlags_DiscardColor6: ClearFlags          = 0x0200;

/// Discard frame buffer attachment 7.
pub const ClearFlags_DiscardColor7: ClearFlags          = 0x0400;

/// Discard frame buffer depth attachment.
pub const ClearFlags_DiscardDepth: ClearFlags           = 0x0800;

/// Discard frame buffer stencil attachment.
pub const ClearFlags_DiscardStencil: ClearFlags         = 0x1000;
pub const ClearFlags_DiscardColorMask: ClearFlags       = 0x07f8;
pub const ClearFlags_DiscardMask: ClearFlags            = 0x1ff8;

pub const DiscardFlags = u32;
/// Preserve everything.
pub const DiscardFlags_None: DiscardFlags                   = 0x00000000;

/// Discard texture sampler and buffer bindings.
pub const DiscardFlags_Bindings: DiscardFlags               = 0x00000001;

/// Discard index buffer.
pub const DiscardFlags_IndexBuffer: DiscardFlags            = 0x00000002;

/// Discard instance data.
pub const DiscardFlags_InstanceData: DiscardFlags           = 0x00000004;

/// Discard state and uniform bindings.
pub const DiscardFlags_State: DiscardFlags                  = 0x00000008;

/// Discard transform.
pub const DiscardFlags_Transform: DiscardFlags              = 0x00000010;

/// Discard vertex streams.
pub const DiscardFlags_VertexStreams: DiscardFlags          = 0x00000020;

/// Discard all states.
pub const DiscardFlags_All: DiscardFlags                    = 0x000000ff;

pub const DebugFlags = u32;
/// No debug.
pub const DebugFlags_None: DebugFlags                   = 0x00000000;

/// Enable wireframe for all primitives.
pub const DebugFlags_Wireframe: DebugFlags              = 0x00000001;

/// Enable infinitely fast hardware test. No draw calls will be submitted to driver.
/// It's useful when profiling to quickly assess bottleneck between CPU and GPU.
pub const DebugFlags_Ifh: DebugFlags                    = 0x00000002;

/// Enable statistics display.
pub const DebugFlags_Stats: DebugFlags                  = 0x00000004;

/// Enable debug text display.
pub const DebugFlags_Text: DebugFlags                   = 0x00000008;

/// Enable profiler. This causes per-view statistics to be collected, available through `bgfx::Stats::ViewStats`. This is unrelated to the profiler functions in `bgfx::CallbackI`.
pub const DebugFlags_Profiler: DebugFlags               = 0x00000010;

pub const BufferFlags = u16;
/// 1 8-bit value
pub const BufferFlags_ComputeFormat8x1: BufferFlags       = 0x0001;

/// 2 8-bit values
pub const BufferFlags_ComputeFormat8x2: BufferFlags       = 0x0002;

/// 4 8-bit values
pub const BufferFlags_ComputeFormat8x4: BufferFlags       = 0x0003;

/// 1 16-bit value
pub const BufferFlags_ComputeFormat16x1: BufferFlags      = 0x0004;

/// 2 16-bit values
pub const BufferFlags_ComputeFormat16x2: BufferFlags      = 0x0005;

/// 4 16-bit values
pub const BufferFlags_ComputeFormat16x4: BufferFlags      = 0x0006;

/// 1 32-bit value
pub const BufferFlags_ComputeFormat32x1: BufferFlags      = 0x0007;

/// 2 32-bit values
pub const BufferFlags_ComputeFormat32x2: BufferFlags      = 0x0008;

/// 4 32-bit values
pub const BufferFlags_ComputeFormat32x4: BufferFlags      = 0x0009;
pub const BufferFlags_ComputeFormatShift: BufferFlags     = 0;
pub const BufferFlags_ComputeFormatMask: BufferFlags      = 0x000f;

/// Type `int`.
pub const BufferFlags_ComputeTypeInt: BufferFlags         = 0x0010;

/// Type `uint`.
pub const BufferFlags_ComputeTypeUint: BufferFlags        = 0x0020;

/// Type `float`.
pub const BufferFlags_ComputeTypeFloat: BufferFlags       = 0x0030;
pub const BufferFlags_ComputeTypeShift: BufferFlags       = 4;
pub const BufferFlags_ComputeTypeMask: BufferFlags        = 0x0030;
pub const BufferFlags_None: BufferFlags                   = 0x0000;

/// Buffer will be read by shader.
pub const BufferFlags_ComputeRead: BufferFlags            = 0x0100;

/// Buffer will be used for writing.
pub const BufferFlags_ComputeWrite: BufferFlags           = 0x0200;

/// Buffer will be used for storing draw indirect commands.
pub const BufferFlags_DrawIndirect: BufferFlags           = 0x0400;

/// Allow dynamic index/vertex buffer resize during update.
pub const BufferFlags_AllowResize: BufferFlags            = 0x0800;

/// Index buffer contains 32-bit indices.
pub const BufferFlags_Index32: BufferFlags                = 0x1000;
pub const BufferFlags_ComputeReadWrite: BufferFlags       = 0x0300;

pub const TextureFlags = u64;
pub const TextureFlags_None: TextureFlags                   = 0x0000000000000000;

/// Texture will be used for MSAA sampling.
pub const TextureFlags_MsaaSample: TextureFlags             = 0x0000000800000000;

/// Render target no MSAA.
pub const TextureFlags_Rt: TextureFlags                     = 0x0000001000000000;

/// Texture will be used for compute write.
pub const TextureFlags_ComputeWrite: TextureFlags           = 0x0000100000000000;

/// Sample texture as sRGB.
pub const TextureFlags_Srgb: TextureFlags                   = 0x0000200000000000;

/// Texture will be used as blit destination.
pub const TextureFlags_BlitDst: TextureFlags                = 0x0000400000000000;

/// Texture will be used for read back from GPU.
pub const TextureFlags_ReadBack: TextureFlags               = 0x0000800000000000;

/// Render target MSAAx2 mode.
pub const TextureFlags_RtMsaaX2: TextureFlags               = 0x0000002000000000;

/// Render target MSAAx4 mode.
pub const TextureFlags_RtMsaaX4: TextureFlags               = 0x0000003000000000;

/// Render target MSAAx8 mode.
pub const TextureFlags_RtMsaaX8: TextureFlags               = 0x0000004000000000;

/// Render target MSAAx16 mode.
pub const TextureFlags_RtMsaaX16: TextureFlags              = 0x0000005000000000;
pub const TextureFlags_RtMsaaShift: TextureFlags            = 36;
pub const TextureFlags_RtMsaaMask: TextureFlags             = 0x0000007000000000;

/// Render target will be used for writing
pub const TextureFlags_RtWriteOnly: TextureFlags            = 0x0000008000000000;
pub const TextureFlags_RtShift: TextureFlags                = 36;
pub const TextureFlags_RtMask: TextureFlags                 = 0x000000f000000000;

pub const SamplerFlags = u32;
/// Wrap U mode: Mirror
pub const SamplerFlags_UMirror: SamplerFlags                = 0x00000001;

/// Wrap U mode: Clamp
pub const SamplerFlags_UClamp: SamplerFlags                 = 0x00000002;

/// Wrap U mode: Border
pub const SamplerFlags_UBorder: SamplerFlags                = 0x00000003;
pub const SamplerFlags_UShift: SamplerFlags                 = 0;
pub const SamplerFlags_UMask: SamplerFlags                  = 0x00000003;

/// Wrap V mode: Mirror
pub const SamplerFlags_VMirror: SamplerFlags                = 0x00000004;

/// Wrap V mode: Clamp
pub const SamplerFlags_VClamp: SamplerFlags                 = 0x00000008;

/// Wrap V mode: Border
pub const SamplerFlags_VBorder: SamplerFlags                = 0x0000000c;
pub const SamplerFlags_VShift: SamplerFlags                 = 2;
pub const SamplerFlags_VMask: SamplerFlags                  = 0x0000000c;

/// Wrap W mode: Mirror
pub const SamplerFlags_WMirror: SamplerFlags                = 0x00000010;

/// Wrap W mode: Clamp
pub const SamplerFlags_WClamp: SamplerFlags                 = 0x00000020;

/// Wrap W mode: Border
pub const SamplerFlags_WBorder: SamplerFlags                = 0x00000030;
pub const SamplerFlags_WShift: SamplerFlags                 = 4;
pub const SamplerFlags_WMask: SamplerFlags                  = 0x00000030;

/// Min sampling mode: Point
pub const SamplerFlags_MinPoint: SamplerFlags               = 0x00000040;

/// Min sampling mode: Anisotropic
pub const SamplerFlags_MinAnisotropic: SamplerFlags         = 0x00000080;
pub const SamplerFlags_MinShift: SamplerFlags               = 6;
pub const SamplerFlags_MinMask: SamplerFlags                = 0x000000c0;

/// Mag sampling mode: Point
pub const SamplerFlags_MagPoint: SamplerFlags               = 0x00000100;

/// Mag sampling mode: Anisotropic
pub const SamplerFlags_MagAnisotropic: SamplerFlags         = 0x00000200;
pub const SamplerFlags_MagShift: SamplerFlags               = 8;
pub const SamplerFlags_MagMask: SamplerFlags                = 0x00000300;

/// Mip sampling mode: Point
pub const SamplerFlags_MipPoint: SamplerFlags               = 0x00000400;
pub const SamplerFlags_MipShift: SamplerFlags               = 10;
pub const SamplerFlags_MipMask: SamplerFlags                = 0x00000400;

/// Compare when sampling depth texture: less.
pub const SamplerFlags_CompareLess: SamplerFlags            = 0x00010000;

/// Compare when sampling depth texture: less or equal.
pub const SamplerFlags_CompareLequal: SamplerFlags          = 0x00020000;

/// Compare when sampling depth texture: equal.
pub const SamplerFlags_CompareEqual: SamplerFlags           = 0x00030000;

/// Compare when sampling depth texture: greater or equal.
pub const SamplerFlags_CompareGequal: SamplerFlags          = 0x00040000;

/// Compare when sampling depth texture: greater.
pub const SamplerFlags_CompareGreater: SamplerFlags         = 0x00050000;

/// Compare when sampling depth texture: not equal.
pub const SamplerFlags_CompareNotequal: SamplerFlags        = 0x00060000;

/// Compare when sampling depth texture: never.
pub const SamplerFlags_CompareNever: SamplerFlags           = 0x00070000;

/// Compare when sampling depth texture: always.
pub const SamplerFlags_CompareAlways: SamplerFlags          = 0x00080000;
pub const SamplerFlags_CompareShift: SamplerFlags           = 16;
pub const SamplerFlags_CompareMask: SamplerFlags            = 0x000f0000;
pub const SamplerFlags_BorderColorShift: SamplerFlags       = 24;
pub const SamplerFlags_BorderColorMask: SamplerFlags        = 0x0f000000;
pub const SamplerFlags_ReservedShift: SamplerFlags          = 28;
pub const SamplerFlags_ReservedMask: SamplerFlags           = 0xf0000000;
pub const SamplerFlags_None: SamplerFlags                   = 0x00000000;

/// Sample stencil instead of depth.
pub const SamplerFlags_SampleStencil: SamplerFlags          = 0x00100000;
pub const SamplerFlags_Point: SamplerFlags                  = 0x00000540;
pub const SamplerFlags_UvwMirror: SamplerFlags              = 0x00000015;
pub const SamplerFlags_UvwClamp: SamplerFlags               = 0x0000002a;
pub const SamplerFlags_UvwBorder: SamplerFlags              = 0x0000003f;
pub const SamplerFlags_BitsMask: SamplerFlags               = 0x000f07ff;

pub const ResetFlags = u32;
/// Enable 2x MSAA.
pub const ResetFlags_MsaaX2: ResetFlags                 = 0x00000010;

/// Enable 4x MSAA.
pub const ResetFlags_MsaaX4: ResetFlags                 = 0x00000020;

/// Enable 8x MSAA.
pub const ResetFlags_MsaaX8: ResetFlags                 = 0x00000030;

/// Enable 16x MSAA.
pub const ResetFlags_MsaaX16: ResetFlags                = 0x00000040;
pub const ResetFlags_MsaaShift: ResetFlags              = 4;
pub const ResetFlags_MsaaMask: ResetFlags               = 0x00000070;

/// No reset flags.
pub const ResetFlags_None: ResetFlags                   = 0x00000000;

/// Not supported yet.
pub const ResetFlags_Fullscreen: ResetFlags             = 0x00000001;

/// Enable V-Sync.
pub const ResetFlags_Vsync: ResetFlags                  = 0x00000080;

/// Turn on/off max anisotropy.
pub const ResetFlags_Maxanisotropy: ResetFlags          = 0x00000100;

/// Begin screen capture.
pub const ResetFlags_Capture: ResetFlags                = 0x00000200;

/// Flush rendering after submitting to GPU.
pub const ResetFlags_FlushAfterRender: ResetFlags       = 0x00002000;

/// This flag specifies where flip occurs. Default behaviour is that flip occurs
/// before rendering new frame. This flag only has effect when `BGFX_CONFIG_MULTITHREADED=0`.
pub const ResetFlags_FlipAfterRender: ResetFlags        = 0x00004000;

/// Enable sRGB backbuffer.
pub const ResetFlags_SrgbBackbuffer: ResetFlags         = 0x00008000;

/// Enable HDR10 rendering.
pub const ResetFlags_Hdr10: ResetFlags                  = 0x00010000;

/// Enable HiDPI rendering.
pub const ResetFlags_Hidpi: ResetFlags                  = 0x00020000;

/// Enable depth clamp.
pub const ResetFlags_DepthClamp: ResetFlags             = 0x00040000;

/// Suspend rendering.
pub const ResetFlags_Suspend: ResetFlags                = 0x00080000;
pub const ResetFlags_FullscreenShift: ResetFlags        = 0;
pub const ResetFlags_FullscreenMask: ResetFlags         = 0x00000001;
pub const ResetFlags_ReservedShift: ResetFlags          = 31;
pub const ResetFlags_ReservedMask: ResetFlags           = 0x80000000;

pub const CapsFlags = u64;
/// Alpha to coverage is supported.
pub const CapsFlags_AlphaToCoverage: CapsFlags        = 0x0000000000000001;

/// Blend independent is supported.
pub const CapsFlags_BlendIndependent: CapsFlags       = 0x0000000000000002;

/// Compute shaders are supported.
pub const CapsFlags_Compute: CapsFlags                = 0x0000000000000004;

/// Conservative rasterization is supported.
pub const CapsFlags_ConservativeRaster: CapsFlags     = 0x0000000000000008;

/// Draw indirect is supported.
pub const CapsFlags_DrawIndirect: CapsFlags           = 0x0000000000000010;

/// Fragment depth is available in fragment shader.
pub const CapsFlags_FragmentDepth: CapsFlags          = 0x0000000000000020;

/// Fragment ordering is available in fragment shader.
pub const CapsFlags_FragmentOrdering: CapsFlags       = 0x0000000000000040;

/// Graphics debugger is present.
pub const CapsFlags_GraphicsDebugger: CapsFlags       = 0x0000000000000080;

/// HDR10 rendering is supported.
pub const CapsFlags_Hdr10: CapsFlags                  = 0x0000000000000100;

/// HiDPI rendering is supported.
pub const CapsFlags_Hidpi: CapsFlags                  = 0x0000000000000200;

/// Image Read/Write is supported.
pub const CapsFlags_ImageRw: CapsFlags                = 0x0000000000000400;

/// 32-bit indices are supported.
pub const CapsFlags_Index32: CapsFlags                = 0x0000000000000800;

/// Instancing is supported.
pub const CapsFlags_Instancing: CapsFlags             = 0x0000000000001000;

/// Occlusion query is supported.
pub const CapsFlags_OcclusionQuery: CapsFlags         = 0x0000000000002000;

/// Renderer is on separate thread.
pub const CapsFlags_RendererMultithreaded: CapsFlags  = 0x0000000000004000;

/// Multiple windows are supported.
pub const CapsFlags_SwapChain: CapsFlags              = 0x0000000000008000;

/// 2D texture array is supported.
pub const CapsFlags_Texture2dArray: CapsFlags         = 0x0000000000010000;

/// 3D textures are supported.
pub const CapsFlags_Texture3d: CapsFlags              = 0x0000000000020000;

/// Texture blit is supported.
pub const CapsFlags_TextureBlit: CapsFlags            = 0x0000000000040000;
pub const CapsFlags_TextureCompareReserved: CapsFlags = 0x0000000000080000;

/// Texture compare less equal mode is supported.
pub const CapsFlags_TextureCompareLequal: CapsFlags   = 0x0000000000100000;

/// Cubemap texture array is supported.
pub const CapsFlags_TextureCubeArray: CapsFlags       = 0x0000000000200000;

/// CPU direct access to GPU texture memory.
pub const CapsFlags_TextureDirectAccess: CapsFlags    = 0x0000000000400000;

/// Read-back texture is supported.
pub const CapsFlags_TextureReadBack: CapsFlags        = 0x0000000000800000;

/// Vertex attribute half-float is supported.
pub const CapsFlags_VertexAttribHalf: CapsFlags       = 0x0000000001000000;

/// Vertex attribute 10_10_10_2 is supported.
pub const CapsFlags_VertexAttribUint10: CapsFlags     = 0x0000000002000000;

/// Rendering with VertexID only is supported.
pub const CapsFlags_VertexId: CapsFlags               = 0x0000000004000000;

/// Viewport layer is available in vertex shader.
pub const CapsFlags_ViewportLayerArray: CapsFlags     = 0x0000000008000000;

/// All texture compare modes are supported.
pub const CapsFlags_TextureCompareAll: CapsFlags      = 0x0000000000180000;

pub const CapsFormatFlags = u32;
/// Texture format is not supported.
pub const CapsFormatFlags_TextureNone: CapsFormatFlags            = 0x00000000;

/// Texture format is supported.
pub const CapsFormatFlags_Texture2d: CapsFormatFlags              = 0x00000001;

/// Texture as sRGB format is supported.
pub const CapsFormatFlags_Texture2dSrgb: CapsFormatFlags          = 0x00000002;

/// Texture format is emulated.
pub const CapsFormatFlags_Texture2dEmulated: CapsFormatFlags      = 0x00000004;

/// Texture format is supported.
pub const CapsFormatFlags_Texture3d: CapsFormatFlags              = 0x00000008;

/// Texture as sRGB format is supported.
pub const CapsFormatFlags_Texture3dSrgb: CapsFormatFlags          = 0x00000010;

/// Texture format is emulated.
pub const CapsFormatFlags_Texture3dEmulated: CapsFormatFlags      = 0x00000020;

/// Texture format is supported.
pub const CapsFormatFlags_TextureCube: CapsFormatFlags            = 0x00000040;

/// Texture as sRGB format is supported.
pub const CapsFormatFlags_TextureCubeSrgb: CapsFormatFlags        = 0x00000080;

/// Texture format is emulated.
pub const CapsFormatFlags_TextureCubeEmulated: CapsFormatFlags    = 0x00000100;

/// Texture format can be used from vertex shader.
pub const CapsFormatFlags_TextureVertex: CapsFormatFlags          = 0x00000200;

/// Texture format can be used as image and read from.
pub const CapsFormatFlags_TextureImageRead: CapsFormatFlags       = 0x00000400;

/// Texture format can be used as image and written to.
pub const CapsFormatFlags_TextureImageWrite: CapsFormatFlags      = 0x00000800;

/// Texture format can be used as frame buffer.
pub const CapsFormatFlags_TextureFramebuffer: CapsFormatFlags     = 0x00001000;

/// Texture format can be used as MSAA frame buffer.
pub const CapsFormatFlags_TextureFramebufferMsaa: CapsFormatFlags = 0x00002000;

/// Texture can be sampled as MSAA.
pub const CapsFormatFlags_TextureMsaa: CapsFormatFlags            = 0x00004000;

/// Texture format supports auto-generated mips.
pub const CapsFormatFlags_TextureMipAutogen: CapsFormatFlags      = 0x00008000;

pub const ResolveFlags = u32;
/// No resolve flags.
pub const ResolveFlags_None: ResolveFlags                   = 0x00000000;

/// Auto-generate mip maps on resolve.
pub const ResolveFlags_AutoGenMips: ResolveFlags            = 0x00000001;

pub const PciIdFlags = u16;
/// Autoselect adapter.
pub const PciIdFlags_None: PciIdFlags                   = 0x0000;

/// Software rasterizer.
pub const PciIdFlags_SoftwareRasterizer: PciIdFlags     = 0x0001;

/// AMD adapter.
pub const PciIdFlags_Amd: PciIdFlags                    = 0x1002;

/// Apple adapter.
pub const PciIdFlags_Apple: PciIdFlags                  = 0x106b;

/// Intel adapter.
pub const PciIdFlags_Intel: PciIdFlags                  = 0x8086;

/// nVidia adapter.
pub const PciIdFlags_Nvidia: PciIdFlags                 = 0x10de;

/// Microsoft adapter.
pub const PciIdFlags_Microsoft: PciIdFlags              = 0x1414;

pub const CubeMapFlags = u32;
/// Cubemap +x.
pub const CubeMapFlags_PositiveX: CubeMapFlags              = 0x00000000;

/// Cubemap -x.
pub const CubeMapFlags_NegativeX: CubeMapFlags              = 0x00000001;

/// Cubemap +y.
pub const CubeMapFlags_PositiveY: CubeMapFlags              = 0x00000002;

/// Cubemap -y.
pub const CubeMapFlags_NegativeY: CubeMapFlags              = 0x00000003;

/// Cubemap +z.
pub const CubeMapFlags_PositiveZ: CubeMapFlags              = 0x00000004;

/// Cubemap -z.
pub const CubeMapFlags_NegativeZ: CubeMapFlags              = 0x00000005;

pub const Fatal = enum(c_int) {
    DebugCheck,
    InvalidShader,
    UnableToInitialize,
    UnableToCreateTexture,
    DeviceLost,

    Count
};

pub const RendererType = enum(c_int) {
    /// No rendering.
    Noop,

    /// AGC
    Agc,

    /// Direct3D 9.0
    Direct3D9,

    /// Direct3D 11.0
    Direct3D11,

    /// Direct3D 12.0
    Direct3D12,

    /// GNM
    Gnm,

    /// Metal
    Metal,

    /// NVN
    Nvn,

    /// OpenGL ES 2.0+
    OpenGLES,

    /// OpenGL 2.1+
    OpenGL,

    /// Vulkan
    Vulkan,

    /// WebGPU
    WebGPU,

    Count
};

pub const Access = enum(c_int) {
    /// Read.
    Read,

    /// Write.
    Write,

    /// Read and write.
    ReadWrite,

    Count
};

pub const Attrib = enum(c_int) {
    /// a_position
    Position,

    /// a_normal
    Normal,

    /// a_tangent
    Tangent,

    /// a_bitangent
    Bitangent,

    /// a_color0
    Color0,

    /// a_color1
    Color1,

    /// a_color2
    Color2,

    /// a_color3
    Color3,

    /// a_indices
    Indices,

    /// a_weight
    Weight,

    /// a_texcoord0
    TexCoord0,

    /// a_texcoord1
    TexCoord1,

    /// a_texcoord2
    TexCoord2,

    /// a_texcoord3
    TexCoord3,

    /// a_texcoord4
    TexCoord4,

    /// a_texcoord5
    TexCoord5,

    /// a_texcoord6
    TexCoord6,

    /// a_texcoord7
    TexCoord7,

    Count
};

pub const AttribType = enum(c_int) {
    /// Uint8
    Uint8,

    /// Uint10, availability depends on: `BGFX_CAPS_VERTEX_ATTRIB_UINT10`.
    Uint10,

    /// Int16
    Int16,

    /// Half, availability depends on: `BGFX_CAPS_VERTEX_ATTRIB_HALF`.
    Half,

    /// Float
    Float,

    Count
};

pub const TextureFormat = enum(c_int) {
    /// DXT1 R5G6B5A1
    BC1,

    /// DXT3 R5G6B5A4
    BC2,

    /// DXT5 R5G6B5A8
    BC3,

    /// LATC1/ATI1 R8
    BC4,

    /// LATC2/ATI2 RG8
    BC5,

    /// BC6H RGB16F
    BC6H,

    /// BC7 RGB 4-7 bits per color channel, 0-8 bits alpha
    BC7,

    /// ETC1 RGB8
    ETC1,

    /// ETC2 RGB8
    ETC2,

    /// ETC2 RGBA8
    ETC2A,

    /// ETC2 RGB8A1
    ETC2A1,

    /// PVRTC1 RGB 2BPP
    PTC12,

    /// PVRTC1 RGB 4BPP
    PTC14,

    /// PVRTC1 RGBA 2BPP
    PTC12A,

    /// PVRTC1 RGBA 4BPP
    PTC14A,

    /// PVRTC2 RGBA 2BPP
    PTC22,

    /// PVRTC2 RGBA 4BPP
    PTC24,

    /// ATC RGB 4BPP
    ATC,

    /// ATCE RGBA 8 BPP explicit alpha
    ATCE,

    /// ATCI RGBA 8 BPP interpolated alpha
    ATCI,

    /// ASTC 4x4 8.0 BPP
    ASTC4x4,

    /// ASTC 5x5 5.12 BPP
    ASTC5x5,

    /// ASTC 6x6 3.56 BPP
    ASTC6x6,

    /// ASTC 8x5 3.20 BPP
    ASTC8x5,

    /// ASTC 8x6 2.67 BPP
    ASTC8x6,

    /// ASTC 10x5 2.56 BPP
    ASTC10x5,

    /// Compressed formats above.
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

    /// Depth formats below.
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
};

pub const UniformType = enum(c_int) {
    /// Sampler.
    Sampler,

    /// Reserved, do not use.
    End,

    /// 4 floats vector.
    Vec4,

    /// 3x3 matrix.
    Mat3,

    /// 4x4 matrix.
    Mat4,

    Count
};

pub const BackbufferRatio = enum(c_int) {
    /// Equal to backbuffer.
    Equal,

    /// One half size of backbuffer.
    Half,

    /// One quarter size of backbuffer.
    Quarter,

    /// One eighth size of backbuffer.
    Eighth,

    /// One sixteenth size of backbuffer.
    Sixteenth,

    /// Double size of backbuffer.
    Double,

    Count
};

pub const OcclusionQueryResult = enum(c_int) {
    /// Query failed test.
    Invisible,

    /// Query passed test.
    Visible,

    /// Query result is not available yet.
    NoResult,

    Count
};

pub const Topology = enum(c_int) {
    /// Triangle list.
    TriList,

    /// Triangle strip.
    TriStrip,

    /// Line list.
    LineList,

    /// Line strip.
    LineStrip,

    /// Point list.
    PointList,

    Count
};

pub const TopologyConvert = enum(c_int) {
    /// Flip winding order of triangle list.
    TriListFlipWinding,

    /// Flip winding order of triangle strip.
    TriStripFlipWinding,

    /// Convert triangle list to line list.
    TriListToLineList,

    /// Convert triangle strip to triangle list.
    TriStripToTriList,

    /// Convert line strip to line list.
    LineStripToLineList,

    Count
};

pub const TopologySort = enum(c_int) {
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
};

pub const ViewMode = enum(c_int) {
    /// Default sort order.
    Default,

    /// Sort in the same order in which submit calls were called.
    Sequential,

    /// Sort draw call depth in ascending order.
    DepthAscending,

    /// Sort draw call depth in descending order.
    DepthDescending,

    Count
};

pub const RenderFrame = enum(c_int) {
    /// Renderer context is not created yet.
    NoContext,

    /// Renderer context is created and rendering.
    Render,

    /// Renderer context wait for main thread signal timed out without rendering.
    Timeout,

    /// Renderer context is getting destroyed.
    Exiting,

    Count
};

pub const Caps = extern struct {
    pub const GPU = extern struct {
        vendorId: u16,
        deviceId: u16,
    };

    pub const Limits = extern struct {
        maxDrawCalls: u32,
        maxBlits: u32,
        maxTextureSize: u32,
        maxTextureLayers: u32,
        maxViews: u32,
        maxFrameBuffers: u32,
        maxFBAttachments: u32,
        maxPrograms: u32,
        maxShaders: u32,
        maxTextures: u32,
        maxTextureSamplers: u32,
        maxComputeBindings: u32,
        maxVertexLayouts: u32,
        maxVertexStreams: u32,
        maxIndexBuffers: u32,
        maxVertexBuffers: u32,
        maxDynamicIndexBuffers: u32,
        maxDynamicVertexBuffers: u32,
        maxUniforms: u32,
        maxOcclusionQueries: u32,
        maxEncoders: u32,
        minResourceCbSize: u32,
        transientVbSize: u32,
        transientIbSize: u32,
    };

        rendererType: RendererType,
        supported: u64,
        vendorId: u16,
        deviceId: u16,
        homogeneousDepth: bool,
        originBottomLeft: bool,
        numGPUs: u8,
        gpu: [4]GPU,
        limits: Limits,
        formats: [85]u16,
    };

    pub const InternalData = extern struct {
        caps: [*c]const Caps,
        context: ?*anyopaque,
    };

    pub const PlatformData = extern struct {
        ndt: ?*anyopaque,
        nwh: ?*anyopaque,
        context: ?*anyopaque,
        backBuffer: ?*anyopaque,
        backBufferDS: ?*anyopaque,
    };

    pub const Resolution = extern struct {
        format: TextureFormat,
        width: u32,
        height: u32,
        reset: u32,
        numBackBuffers: u8,
        maxFrameLatency: u8,
    };

pub const Init = extern struct {
    pub const Limits = extern struct {
        maxEncoders: u16,
        minResourceCbSize: u32,
        transientVbSize: u32,
        transientIbSize: u32,
    };

        type: RendererType,
        vendorId: u16,
        deviceId: u16,
        capabilities: u64,
        debug: bool,
        profile: bool,
        platformData: PlatformData,
        resolution: Resolution,
        limits: Limits,
        callback: ?*anyopaque,
        allocator: ?*anyopaque,
    };

    pub const Memory = extern struct {
        data: [*c]u8,
        size: u32,
    };

    pub const TransientIndexBuffer = extern struct {
        data: [*c]u8,
        size: u32,
        startIndex: u32,
        handle: IndexBufferHandle,
        isIndex16: bool,
    };

    pub const TransientVertexBuffer = extern struct {
        data: [*c]u8,
        size: u32,
        startVertex: u32,
        stride: u16,
        handle: VertexBufferHandle,
        layoutHandle: VertexLayoutHandle,
    };

    pub const InstanceDataBuffer = extern struct {
        data: [*c]u8,
        size: u32,
        offset: u32,
        num: u32,
        stride: u16,
        handle: VertexBufferHandle,
    };

    pub const TextureInfo = extern struct {
        format: TextureFormat,
        storageSize: u32,
        width: u16,
        height: u16,
        depth: u16,
        numLayers: u16,
        numMips: u8,
        bitsPerPixel: u8,
        cubeMap: bool,
    };

    pub const UniformInfo = extern struct {
        name: [256]u8,
        type: UniformType,
        num: u16,
    };

    pub const Attachment = extern struct {
        access: Access,
        handle: TextureHandle,
        mip: u16,
        layer: u16,
        numLayers: u16,
        resolve: u8,
    };

    pub const Transform = extern struct {
        data: [*c]f32,
        num: u16,
    };

    pub const ViewStats = extern struct {
        name: [256]u8,
        view: ViewId,
        cpuTimeBegin: i64,
        cpuTimeEnd: i64,
        gpuTimeBegin: i64,
        gpuTimeEnd: i64,
    };

    pub const EncoderStats = extern struct {
        cpuTimeBegin: i64,
        cpuTimeEnd: i64,
    };

    pub const Stats = extern struct {
        cpuTimeFrame: i64,
        cpuTimeBegin: i64,
        cpuTimeEnd: i64,
        cpuTimerFreq: i64,
        gpuTimeBegin: i64,
        gpuTimeEnd: i64,
        gpuTimerFreq: i64,
        waitRender: i64,
        waitSubmit: i64,
        numDraw: u32,
        numCompute: u32,
        numBlit: u32,
        maxGpuLatency: u32,
        numDynamicIndexBuffers: u16,
        numDynamicVertexBuffers: u16,
        numFrameBuffers: u16,
        numIndexBuffers: u16,
        numOcclusionQueries: u16,
        numPrograms: u16,
        numShaders: u16,
        numTextures: u16,
        numUniforms: u16,
        numVertexBuffers: u16,
        numVertexLayouts: u16,
        textureMemoryUsed: i64,
        rtMemoryUsed: i64,
        transientVbUsed: i32,
        transientIbUsed: i32,
        numPrims: [5]u32,
        gpuMemoryMax: i64,
        gpuMemoryUsed: i64,
        width: u16,
        height: u16,
        textWidth: u16,
        textHeight: u16,
        numViews: u16,
        viewStats: [*c]ViewStats,
        numEncoders: u8,
        encoderStats: [*c]EncoderStats,
    };

    pub const VertexLayout = extern struct {
        hash: u32,
        stride: u16,
        offset: [18]u16,
        attributes: [18]u16,
    };

    pub const Encoder = opaque {
    };

pub const DynamicIndexBufferHandle = extern struct {
    idx: c_ushort,
};

pub const DynamicVertexBufferHandle = extern struct {
    idx: c_ushort,
};

pub const FrameBufferHandle = extern struct {
    idx: c_ushort,
};

pub const IndexBufferHandle = extern struct {
    idx: c_ushort,
};

pub const IndirectBufferHandle = extern struct {
    idx: c_ushort,
};

pub const OcclusionQueryHandle = extern struct {
    idx: c_ushort,
};

pub const ProgramHandle = extern struct {
    idx: c_ushort,
};

pub const ShaderHandle = extern struct {
    idx: c_ushort,
};

pub const TextureHandle = extern struct {
    idx: c_ushort,
};

pub const UniformHandle = extern struct {
    idx: c_ushort,
};

pub const VertexBufferHandle = extern struct {
    idx: c_ushort,
};

pub const VertexLayoutHandle = extern struct {
    idx: c_ushort,
};


/// Init attachment.
/// <param name="_handle">Render target texture handle.</param>
/// <param name="_access">Access. See `Access::Enum`.</param>
/// <param name="_layer">Cubemap side or depth layer/slice to use.</param>
/// <param name="_numLayers">Number of texture layer/slice(s) in array to use.</param>
/// <param name="_mip">Mip level.</param>
/// <param name="_resolve">Resolve flags. See: `BGFX_RESOLVE_*`</param>
pub extern fn bgfx_attachment_init(self: [*c]Attachment, handle: TextureHandle, access: Access, layer: u16, numLayers: u16, mip: u16, resolve: u8) void;

/// Start VertexLayout.
/// <param name="_rendererType">Renderer backend type. See: `bgfx::RendererType`</param>
pub extern fn bgfx_vertex_layout_begin(self: [*c]VertexLayout, rendererType: RendererType) [*c]VertexLayout;

/// Add attribute to VertexLayout.
/// @remarks Must be called between begin/end.
/// <param name="_attrib">Attribute semantics. See: `bgfx::Attrib`</param>
/// <param name="_num">Number of elements 1, 2, 3 or 4.</param>
/// <param name="_type">Element type.</param>
/// <param name="_normalized">When using fixed point AttribType (f.e. Uint8) value will be normalized for vertex shader usage. When normalized is set to true, AttribType::Uint8 value in range 0-255 will be in range 0.0-1.0 in vertex shader.</param>
/// <param name="_asInt">Packaging rule for vertexPack, vertexUnpack, and vertexConvert for AttribType::Uint8 and AttribType::Int16. Unpacking code must be implemented inside vertex shader.</param>
pub extern fn bgfx_vertex_layout_add(self: [*c]VertexLayout, attrib: Attrib, num: u8, type: AttribType, normalized: bool, asInt: bool) [*c]VertexLayout;

/// Decode attribute.
/// <param name="_attrib">Attribute semantics. See: `bgfx::Attrib`</param>
/// <param name="_num">Number of elements.</param>
/// <param name="_type">Element type.</param>
/// <param name="_normalized">Attribute is normalized.</param>
/// <param name="_asInt">Attribute is packed as int.</param>
pub extern fn bgfx_vertex_layout_decode(self: [*c]const VertexLayout, attrib: Attrib, num: [*c]u8 , type: [*c]AttribType, normalized: [*c]bool, asInt: [*c]bool) void;

/// Returns `true` if VertexLayout contains attribute.
/// <param name="_attrib">Attribute semantics. See: `bgfx::Attrib`</param>
pub extern fn bgfx_vertex_layout_has(self: [*c]const VertexLayout, attrib: Attrib) bool;

/// Skip `_num` bytes in vertex stream.
/// <param name="_num">Number of bytes to skip.</param>
pub extern fn bgfx_vertex_layout_skip(self: [*c]VertexLayout, num: u8) [*c]VertexLayout;

/// End VertexLayout.
pub extern fn bgfx_vertex_layout_end(self: [*c]VertexLayout) void;

/// Pack vertex attribute into vertex stream format.
/// <param name="_input">Value to be packed into vertex stream.</param>
/// <param name="_inputNormalized">`true` if input value is already normalized.</param>
/// <param name="_attr">Attribute to pack.</param>
/// <param name="_layout">Vertex stream layout.</param>
/// <param name="_data">Destination vertex stream where data will be packed.</param>
/// <param name="_index">Vertex index that will be modified.</param>
pub extern fn bgfx_vertex_pack(input: [4]f32, inputNormalized: bool, attr: Attrib, layout: [*c]const VertexLayout, data: ?*anyopaque, index: u32) void;

/// Unpack vertex attribute from vertex stream format.
/// <param name="_output">Result of unpacking.</param>
/// <param name="_attr">Attribute to unpack.</param>
/// <param name="_layout">Vertex stream layout.</param>
/// <param name="_data">Source vertex stream from where data will be unpacked.</param>
/// <param name="_index">Vertex index that will be unpacked.</param>
pub extern fn bgfx_vertex_unpack(output: [4]f32, attr: Attrib, layout: [*c]const VertexLayout, data: ?*const anyopaque, index: u32) void;

/// Converts vertex stream data from one vertex stream format to another.
/// <param name="_dstLayout">Destination vertex stream layout.</param>
/// <param name="_dstData">Destination vertex stream.</param>
/// <param name="_srcLayout">Source vertex stream layout.</param>
/// <param name="_srcData">Source vertex stream data.</param>
/// <param name="_num">Number of vertices to convert from source to destination.</param>
pub extern fn bgfx_vertex_convert(dstLayout: [*c]const VertexLayout, dstData: ?*anyopaque, srcLayout: [*c]const VertexLayout, srcData: ?*const anyopaque, num: u32) void;

/// Weld vertices.
/// <param name="_output">Welded vertices remapping table. The size of buffer must be the same as number of vertices.</param>
/// <param name="_layout">Vertex stream layout.</param>
/// <param name="_data">Vertex stream.</param>
/// <param name="_num">Number of vertices in vertex stream.</param>
/// <param name="_index32">Set to `true` if input indices are 32-bit.</param>
/// <param name="_epsilon">Error tolerance for vertex position comparison.</param>
pub extern fn bgfx_weld_vertices(output: ?*anyopaque, layout: [*c]const VertexLayout, data: ?*const anyopaque, num: u32, index32: bool, epsilon: f32) u32;

/// Convert index buffer for use with different primitive topologies.
/// <param name="_conversion">Conversion type, see `TopologyConvert::Enum`.</param>
/// <param name="_dst">Destination index buffer. If this argument is NULL function will return number of indices after conversion.</param>
/// <param name="_dstSize">Destination index buffer in bytes. It must be large enough to contain output indices. If destination size is insufficient index buffer will be truncated.</param>
/// <param name="_indices">Source indices.</param>
/// <param name="_numIndices">Number of input indices.</param>
/// <param name="_index32">Set to `true` if input indices are 32-bit.</param>
pub extern fn bgfx_topology_convert(conversion: TopologyConvert, dst: ?*anyopaque, dstSize: u32, indices: ?*const anyopaque, numIndices: u32, index32: bool) u32;

/// Sort indices.
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
pub extern fn bgfx_topology_sort_tri_list(sort: TopologySort, dst: ?*anyopaque, dstSize: u32, dir: [3]f32, pos: [3]f32, vertices: ?*const anyopaque, stride: u32, indices: ?*const anyopaque, numIndices: u32, index32: bool) void;

/// Returns supported backend API renderers.
/// <param name="_max">Maximum number of elements in _enum array.</param>
/// <param name="_enum">Array where supported renderers will be written.</param>
pub extern fn bgfx_get_supported_renderers(max: u8, enumeration: [*c]RendererType) u8;

/// Returns name of renderer.
/// <param name="_type">Renderer backend type. See: `bgfx::RendererType`</param>
pub extern fn bgfx_get_renderer_name(type: RendererType) [*c]const u8;

pub extern fn bgfx_init_ctor(init: [*c]Init) void;

/// Initialize the bgfx library.
/// <param name="_init">Initialization parameters. See: `bgfx::Init` for more info.</param>
pub extern fn bgfx_init(init: [*c]const Init) bool;

/// Shutdown bgfx library.
pub extern fn bgfx_shutdown() void;

/// Reset graphic settings and back-buffer size.
/// @attention This call doesn’t change the window size, it just resizes
///   the back-buffer. Your windowing code controls the window size.
/// <param name="_width">Back-buffer width.</param>
/// <param name="_height">Back-buffer height.</param>
/// <param name="_flags">See: `BGFX_RESET_*` for more info.   - `BGFX_RESET_NONE` - No reset flags.   - `BGFX_RESET_FULLSCREEN` - Not supported yet.   - `BGFX_RESET_MSAA_X[2/4/8/16]` - Enable 2, 4, 8 or 16 x MSAA.   - `BGFX_RESET_VSYNC` - Enable V-Sync.   - `BGFX_RESET_MAXANISOTROPY` - Turn on/off max anisotropy.   - `BGFX_RESET_CAPTURE` - Begin screen capture.   - `BGFX_RESET_FLUSH_AFTER_RENDER` - Flush rendering after submitting to GPU.   - `BGFX_RESET_FLIP_AFTER_RENDER` - This flag  specifies where flip     occurs. Default behaviour is that flip occurs before rendering new     frame. This flag only has effect when `BGFX_CONFIG_MULTITHREADED=0`.   - `BGFX_RESET_SRGB_BACKBUFFER` - Enable sRGB back-buffer.</param>
/// <param name="_format">Texture format. See: `TextureFormat::Enum`.</param>
pub extern fn bgfx_reset(width: u32, height: u32, flags: u32, format: TextureFormat) void;

/// Advance to next frame. When using multithreaded renderer, this call
/// just swaps internal buffers, kicks render thread, and returns. In
/// singlethreaded renderer this call does frame rendering.
/// <param name="_capture">Capture frame with graphics debugger.</param>
pub extern fn bgfx_frame(capture: bool) u32;

/// Returns current renderer backend API type.
/// @remarks
///   Library must be initialized.
pub extern fn bgfx_get_renderer_type() RendererType;

/// Returns renderer capabilities.
/// @remarks
///   Library must be initialized.
pub extern fn bgfx_get_caps() [*c]const Caps;

/// Returns performance counters.
/// @attention Pointer returned is valid until `bgfx::frame` is called.
pub extern fn bgfx_get_stats() [*c]const Stats;

/// Allocate buffer to pass to bgfx calls. Data will be freed inside bgfx.
/// <param name="_size">Size to allocate.</param>
pub extern fn bgfx_alloc(size: u32) [*c]const Memory;

/// Allocate buffer and copy data into it. Data will be freed inside bgfx.
/// <param name="_data">Pointer to data to be copied.</param>
/// <param name="_size">Size of data to be copied.</param>
pub extern fn bgfx_copy(data: ?*const anyopaque, size: u32) [*c]const Memory;

/// Make reference to data to pass to bgfx. Unlike `bgfx::alloc`, this call
/// doesn't allocate memory for data. It just copies the _data pointer. You
/// can pass `ReleaseFn` function pointer to release this memory after it's
/// consumed, otherwise you must make sure _data is available for at least 2
/// `bgfx::frame` calls. `ReleaseFn` function must be able to be called
/// from any thread.
/// @attention Data passed must be available for at least 2 `bgfx::frame` calls.
/// <param name="_data">Pointer to data.</param>
/// <param name="_size">Size of data.</param>
pub extern fn bgfx_make_ref(data: ?*const anyopaque, size: u32) [*c]const Memory;

/// Make reference to data to pass to bgfx. Unlike `bgfx::alloc`, this call
/// doesn't allocate memory for data. It just copies the _data pointer. You
/// can pass `ReleaseFn` function pointer to release this memory after it's
/// consumed, otherwise you must make sure _data is available for at least 2
/// `bgfx::frame` calls. `ReleaseFn` function must be able to be called
/// from any thread.
/// @attention Data passed must be available for at least 2 `bgfx::frame` calls.
/// <param name="_data">Pointer to data.</param>
/// <param name="_size">Size of data.</param>
/// <param name="_releaseFn">Callback function to release memory after use.</param>
/// <param name="_userData">User data to be passed to callback function.</param>
pub extern fn bgfx_make_ref_release(data: ?*const anyopaque, size: u32, releaseFn: ?*anyopaque, userData: ?*anyopaque) [*c]const Memory;

/// Set debug flags.
/// <param name="_debug">Available flags:   - `BGFX_DEBUG_IFH` - Infinitely fast hardware. When this flag is set     all rendering calls will be skipped. This is useful when profiling     to quickly assess potential bottlenecks between CPU and GPU.   - `BGFX_DEBUG_PROFILER` - Enable profiler.   - `BGFX_DEBUG_STATS` - Display internal statistics.   - `BGFX_DEBUG_TEXT` - Display debug text.   - `BGFX_DEBUG_WIREFRAME` - Wireframe rendering. All rendering     primitives will be rendered as lines.</param>
pub extern fn bgfx_set_debug(debug: u32) void;

/// Clear internal debug text buffer.
/// <param name="_attr">Background color.</param>
/// <param name="_small">Default 8x16 or 8x8 font.</param>
pub extern fn bgfx_dbg_text_clear(attr: u8, small: bool) void;

/// Print formatted data to internal debug text character-buffer (VGA-compatible text mode).
/// <param name="_x">Position x from the left corner of the window.</param>
/// <param name="_y">Position y from the top corner of the window.</param>
/// <param name="_attr">Color palette. Where top 4-bits represent index of background, and bottom 4-bits represent foreground color from standard VGA text palette (ANSI escape codes).</param>
/// <param name="_format">`printf` style format.</param>
pub extern fn bgfx_dbg_text_printf(x: u16, y: u16, attr: u8, format: [*c]const u8, ...) void;

/// Print formatted data from variable argument list to internal debug text character-buffer (VGA-compatible text mode).
/// <param name="_x">Position x from the left corner of the window.</param>
/// <param name="_y">Position y from the top corner of the window.</param>
/// <param name="_attr">Color palette. Where top 4-bits represent index of background, and bottom 4-bits represent foreground color from standard VGA text palette (ANSI escape codes).</param>
/// <param name="_format">`printf` style format.</param>
/// <param name="_argList">Variable arguments list for format string.</param>
pub extern fn bgfx_dbg_text_vprintf(x: u16, y: u16, attr: u8, format: [*c]const u8, argList: ?*anyopaque) void;

/// Draw image into internal debug text buffer.
/// <param name="_x">Position x from the left corner of the window.</param>
/// <param name="_y">Position y from the top corner of the window.</param>
/// <param name="_width">Image width.</param>
/// <param name="_height">Image height.</param>
/// <param name="_data">Raw image data (character/attribute raw encoding).</param>
/// <param name="_pitch">Image pitch in bytes.</param>
pub extern fn bgfx_dbg_text_image(x: u16, y: u16, width: u16, height: u16, data: ?*const anyopaque, pitch: u16) void;

/// Create static index buffer.
/// <param name="_mem">Index buffer data.</param>
/// <param name="_flags">Buffer creation flags.   - `BGFX_BUFFER_NONE` - No flags.   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of       data is passed. If this flag is not specified, and more data is passed on update, the buffer       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic       buffers.   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on       index buffers.</param>
pub extern fn bgfx_create_index_buffer(mem: [*c]const Memory, flags: u16) IndexBufferHandle;

/// Set static index buffer debug name.
/// <param name="_handle">Static index buffer handle.</param>
/// <param name="_name">Static index buffer name.</param>
/// <param name="_len">Static index buffer name length (if length is INT32_MAX, it's expected that _name is zero terminated string.</param>
pub extern fn bgfx_set_index_buffer_name(handle: IndexBufferHandle, name: [*c]const u8, len: i32) void;

/// Destroy static index buffer.
/// <param name="_handle">Static index buffer handle.</param>
pub extern fn bgfx_destroy_index_buffer(handle: IndexBufferHandle) void;

/// Create vertex layout.
/// <param name="_layout">Vertex layout.</param>
pub extern fn bgfx_create_vertex_layout(layout: [*c]const VertexLayout) VertexLayoutHandle;

/// Destroy vertex layout.
/// <param name="_layoutHandle">Vertex layout handle.</param>
pub extern fn bgfx_destroy_vertex_layout(layoutHandle: VertexLayoutHandle) void;

/// Create static vertex buffer.
/// <param name="_mem">Vertex buffer data.</param>
/// <param name="_layout">Vertex layout.</param>
/// <param name="_flags">Buffer creation flags.  - `BGFX_BUFFER_NONE` - No flags.  - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.  - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer      is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.  - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.  - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of      data is passed. If this flag is not specified, and more data is passed on update, the buffer      will be trimmed to fit the existing buffer size. This flag has effect only on dynamic buffers.  - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on index buffers.</param>
pub extern fn bgfx_create_vertex_buffer(mem: [*c]const Memory, layout: [*c]const VertexLayout, flags: u16) VertexBufferHandle;

/// Set static vertex buffer debug name.
/// <param name="_handle">Static vertex buffer handle.</param>
/// <param name="_name">Static vertex buffer name.</param>
/// <param name="_len">Static vertex buffer name length (if length is INT32_MAX, it's expected that _name is zero terminated string.</param>
pub extern fn bgfx_set_vertex_buffer_name(handle: VertexBufferHandle, name: [*c]const u8, len: i32) void;

/// Destroy static vertex buffer.
/// <param name="_handle">Static vertex buffer handle.</param>
pub extern fn bgfx_destroy_vertex_buffer(handle: VertexBufferHandle) void;

/// Create empty dynamic index buffer.
/// <param name="_num">Number of indices.</param>
/// <param name="_flags">Buffer creation flags.   - `BGFX_BUFFER_NONE` - No flags.   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of       data is passed. If this flag is not specified, and more data is passed on update, the buffer       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic       buffers.   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on       index buffers.</param>
pub extern fn bgfx_create_dynamic_index_buffer(num: u32, flags: u16) DynamicIndexBufferHandle;

/// Create a dynamic index buffer and initialize it.
/// <param name="_mem">Index buffer data.</param>
/// <param name="_flags">Buffer creation flags.   - `BGFX_BUFFER_NONE` - No flags.   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of       data is passed. If this flag is not specified, and more data is passed on update, the buffer       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic       buffers.   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on       index buffers.</param>
pub extern fn bgfx_create_dynamic_index_buffer_mem(mem: [*c]const Memory, flags: u16) DynamicIndexBufferHandle;

/// Update dynamic index buffer.
/// <param name="_handle">Dynamic index buffer handle.</param>
/// <param name="_startIndex">Start index.</param>
/// <param name="_mem">Index buffer data.</param>
pub extern fn bgfx_update_dynamic_index_buffer(handle: DynamicIndexBufferHandle, startIndex: u32, mem: [*c]const Memory) void;

/// Destroy dynamic index buffer.
/// <param name="_handle">Dynamic index buffer handle.</param>
pub extern fn bgfx_destroy_dynamic_index_buffer(handle: DynamicIndexBufferHandle) void;

/// Create empty dynamic vertex buffer.
/// <param name="_num">Number of vertices.</param>
/// <param name="_layout">Vertex layout.</param>
/// <param name="_flags">Buffer creation flags.   - `BGFX_BUFFER_NONE` - No flags.   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of       data is passed. If this flag is not specified, and more data is passed on update, the buffer       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic       buffers.   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on       index buffers.</param>
pub extern fn bgfx_create_dynamic_vertex_buffer(num: u32, layout: [*c]const VertexLayout, flags: u16) DynamicVertexBufferHandle;

/// Create dynamic vertex buffer and initialize it.
/// <param name="_mem">Vertex buffer data.</param>
/// <param name="_layout">Vertex layout.</param>
/// <param name="_flags">Buffer creation flags.   - `BGFX_BUFFER_NONE` - No flags.   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of       data is passed. If this flag is not specified, and more data is passed on update, the buffer       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic       buffers.   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on       index buffers.</param>
pub extern fn bgfx_create_dynamic_vertex_buffer_mem(mem: [*c]const Memory, layout: [*c]const VertexLayout, flags: u16) DynamicVertexBufferHandle;

/// Update dynamic vertex buffer.
/// <param name="_handle">Dynamic vertex buffer handle.</param>
/// <param name="_startVertex">Start vertex.</param>
/// <param name="_mem">Vertex buffer data.</param>
pub extern fn bgfx_update_dynamic_vertex_buffer(handle: DynamicVertexBufferHandle, startVertex: u32, mem: [*c]const Memory) void;

/// Destroy dynamic vertex buffer.
/// <param name="_handle">Dynamic vertex buffer handle.</param>
pub extern fn bgfx_destroy_dynamic_vertex_buffer(handle: DynamicVertexBufferHandle) void;

/// Returns number of requested or maximum available indices.
/// <param name="_num">Number of required indices.</param>
/// <param name="_index32">Set to `true` if input indices will be 32-bit.</param>
pub extern fn bgfx_get_avail_transient_index_buffer(num: u32, index32: bool) u32;

/// Returns number of requested or maximum available vertices.
/// <param name="_num">Number of required vertices.</param>
/// <param name="_layout">Vertex layout.</param>
pub extern fn bgfx_get_avail_transient_vertex_buffer(num: u32, layout: [*c]const VertexLayout) u32;

/// Returns number of requested or maximum available instance buffer slots.
/// <param name="_num">Number of required instances.</param>
/// <param name="_stride">Stride per instance.</param>
pub extern fn bgfx_get_avail_instance_data_buffer(num: u32, stride: u16) u32;

/// Allocate transient index buffer.
/// <param name="_tib">TransientIndexBuffer structure is filled and is valid for the duration of frame, and it can be reused for multiple draw calls.</param>
/// <param name="_num">Number of indices to allocate.</param>
/// <param name="_index32">Set to `true` if input indices will be 32-bit.</param>
pub extern fn bgfx_alloc_transient_index_buffer(tib: [*c]TransientIndexBuffer, num: u32, index32: bool) void;

/// Allocate transient vertex buffer.
/// <param name="_tvb">TransientVertexBuffer structure is filled and is valid for the duration of frame, and it can be reused for multiple draw calls.</param>
/// <param name="_num">Number of vertices to allocate.</param>
/// <param name="_layout">Vertex layout.</param>
pub extern fn bgfx_alloc_transient_vertex_buffer(tvb: [*c]TransientVertexBuffer, num: u32, layout: [*c]const VertexLayout) void;

/// Check for required space and allocate transient vertex and index
/// buffers. If both space requirements are satisfied function returns
/// true.
/// <param name="_tvb">TransientVertexBuffer structure is filled and is valid for the duration of frame, and it can be reused for multiple draw calls.</param>
/// <param name="_layout">Vertex layout.</param>
/// <param name="_numVertices">Number of vertices to allocate.</param>
/// <param name="_tib">TransientIndexBuffer structure is filled and is valid for the duration of frame, and it can be reused for multiple draw calls.</param>
/// <param name="_numIndices">Number of indices to allocate.</param>
/// <param name="_index32">Set to `true` if input indices will be 32-bit.</param>
pub extern fn bgfx_alloc_transient_buffers(tvb: [*c]TransientVertexBuffer, layout: [*c]const VertexLayout, numVertices: u32, tib: [*c]TransientIndexBuffer, numIndices: u32, index32: bool) bool;

/// Allocate instance data buffer.
/// <param name="_idb">InstanceDataBuffer structure is filled and is valid for duration of frame, and it can be reused for multiple draw calls.</param>
/// <param name="_num">Number of instances.</param>
/// <param name="_stride">Instance stride. Must be multiple of 16.</param>
pub extern fn bgfx_alloc_instance_data_buffer(idb: [*c]InstanceDataBuffer, num: u32, stride: u16) void;

/// Create draw indirect buffer.
/// <param name="_num">Number of indirect calls.</param>
pub extern fn bgfx_create_indirect_buffer(num: u32) IndirectBufferHandle;

/// Destroy draw indirect buffer.
/// <param name="_handle">Indirect buffer handle.</param>
pub extern fn bgfx_destroy_indirect_buffer(handle: IndirectBufferHandle) void;

/// Create shader from memory buffer.
/// <param name="_mem">Shader binary.</param>
pub extern fn bgfx_create_shader(mem: [*c]const Memory) ShaderHandle;

/// Returns the number of uniforms and uniform handles used inside a shader.
/// @remarks
///   Only non-predefined uniforms are returned.
/// <param name="_handle">Shader handle.</param>
/// <param name="_uniforms">UniformHandle array where data will be stored.</param>
/// <param name="_max">Maximum capacity of array.</param>
pub extern fn bgfx_get_shader_uniforms(handle: ShaderHandle, uniforms: [*c]UniformHandle, max: u16) u16;

/// Set shader debug name.
/// <param name="_handle">Shader handle.</param>
/// <param name="_name">Shader name.</param>
/// <param name="_len">Shader name length (if length is INT32_MAX, it's expected that _name is zero terminated string).</param>
pub extern fn bgfx_set_shader_name(handle: ShaderHandle, name: [*c]const u8, len: i32) void;

/// Destroy shader.
/// @remark Once a shader program is created with _handle,
///   it is safe to destroy that shader.
/// <param name="_handle">Shader handle.</param>
pub extern fn bgfx_destroy_shader(handle: ShaderHandle) void;

/// Create program with vertex and fragment shaders.
/// <param name="_vsh">Vertex shader.</param>
/// <param name="_fsh">Fragment shader.</param>
/// <param name="_destroyShaders">If true, shaders will be destroyed when program is destroyed.</param>
pub extern fn bgfx_create_program(vsh: ShaderHandle, fsh: ShaderHandle, destroyShaders: bool) ProgramHandle;

/// Create program with compute shader.
/// <param name="_csh">Compute shader.</param>
/// <param name="_destroyShaders">If true, shaders will be destroyed when program is destroyed.</param>
pub extern fn bgfx_create_compute_program(csh: ShaderHandle, destroyShaders: bool) ProgramHandle;

/// Destroy program.
/// <param name="_handle">Program handle.</param>
pub extern fn bgfx_destroy_program(handle: ProgramHandle) void;

/// Validate texture parameters.
/// <param name="_depth">Depth dimension of volume texture.</param>
/// <param name="_cubeMap">Indicates that texture contains cubemap.</param>
/// <param name="_numLayers">Number of layers in texture array.</param>
/// <param name="_format">Texture format. See: `TextureFormat::Enum`.</param>
/// <param name="_flags">Texture flags. See `BGFX_TEXTURE_*`.</param>
pub extern fn bgfx_is_texture_valid(depth: u16, cubeMap: bool, numLayers: u16, format: TextureFormat, flags: u64) bool;

/// Validate frame buffer parameters.
/// <param name="_num">Number of attachments.</param>
/// <param name="_attachment">Attachment texture info. See: `bgfx::Attachment`.</param>
pub extern fn bgfx_is_frame_buffer_valid(num: u8, attachment: [*c]const Attachment) bool;

/// Calculate amount of memory required for texture.
/// <param name="_info">Resulting texture info structure. See: `TextureInfo`.</param>
/// <param name="_width">Width.</param>
/// <param name="_height">Height.</param>
/// <param name="_depth">Depth dimension of volume texture.</param>
/// <param name="_cubeMap">Indicates that texture contains cubemap.</param>
/// <param name="_hasMips">Indicates that texture contains full mip-map chain.</param>
/// <param name="_numLayers">Number of layers in texture array.</param>
/// <param name="_format">Texture format. See: `TextureFormat::Enum`.</param>
pub extern fn bgfx_calc_texture_size(info: [*c]TextureInfo, width: u16, height: u16, depth: u16, cubeMap: bool, hasMips: bool, numLayers: u16, format: TextureFormat) void;

/// Create texture from memory buffer.
/// <param name="_mem">DDS, KTX or PVR texture binary data.</param>
/// <param name="_flags">Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`) flags. Default texture sampling mode is linear, and wrap mode is repeat. - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap   mode. - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic   sampling.</param>
/// <param name="_skip">Skip top level mips when parsing texture.</param>
/// <param name="_info">When non-`NULL` is specified it returns parsed texture information.</param>
pub extern fn bgfx_create_texture(mem: [*c]const Memory, flags: u64, skip: u8, info: [*c]TextureInfo) TextureHandle;

/// Create 2D texture.
/// <param name="_width">Width.</param>
/// <param name="_height">Height.</param>
/// <param name="_hasMips">Indicates that texture contains full mip-map chain.</param>
/// <param name="_numLayers">Number of layers in texture array. Must be 1 if caps `BGFX_CAPS_TEXTURE_2D_ARRAY` flag is not set.</param>
/// <param name="_format">Texture format. See: `TextureFormat::Enum`.</param>
/// <param name="_flags">Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`) flags. Default texture sampling mode is linear, and wrap mode is repeat. - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap   mode. - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic   sampling.</param>
/// <param name="_mem">Texture data. If `_mem` is non-NULL, created texture will be immutable. If `_mem` is NULL content of the texture is uninitialized. When `_numLayers` is more than 1, expected memory layout is texture and all mips together for each array element.</param>
pub extern fn bgfx_create_texture_2d(width: u16, height: u16, hasMips: bool, numLayers: u16, format: TextureFormat, flags: u64, mem: [*c]const Memory) TextureHandle;

/// Create texture with size based on back-buffer ratio. Texture will maintain ratio
/// if back buffer resolution changes.
/// <param name="_ratio">Texture size in respect to back-buffer size. See: `BackbufferRatio::Enum`.</param>
/// <param name="_hasMips">Indicates that texture contains full mip-map chain.</param>
/// <param name="_numLayers">Number of layers in texture array. Must be 1 if caps `BGFX_CAPS_TEXTURE_2D_ARRAY` flag is not set.</param>
/// <param name="_format">Texture format. See: `TextureFormat::Enum`.</param>
/// <param name="_flags">Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`) flags. Default texture sampling mode is linear, and wrap mode is repeat. - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap   mode. - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic   sampling.</param>
pub extern fn bgfx_create_texture_2d_scaled(ratio: BackbufferRatio, hasMips: bool, numLayers: u16, format: TextureFormat, flags: u64) TextureHandle;

/// Create 3D texture.
/// <param name="_width">Width.</param>
/// <param name="_height">Height.</param>
/// <param name="_depth">Depth.</param>
/// <param name="_hasMips">Indicates that texture contains full mip-map chain.</param>
/// <param name="_format">Texture format. See: `TextureFormat::Enum`.</param>
/// <param name="_flags">Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`) flags. Default texture sampling mode is linear, and wrap mode is repeat. - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap   mode. - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic   sampling.</param>
/// <param name="_mem">Texture data. If `_mem` is non-NULL, created texture will be immutable. If `_mem` is NULL content of the texture is uninitialized. When `_numLayers` is more than 1, expected memory layout is texture and all mips together for each array element.</param>
pub extern fn bgfx_create_texture_3d(width: u16, height: u16, depth: u16, hasMips: bool, format: TextureFormat, flags: u64, mem: [*c]const Memory) TextureHandle;

/// Create Cube texture.
/// <param name="_size">Cube side size.</param>
/// <param name="_hasMips">Indicates that texture contains full mip-map chain.</param>
/// <param name="_numLayers">Number of layers in texture array. Must be 1 if caps `BGFX_CAPS_TEXTURE_2D_ARRAY` flag is not set.</param>
/// <param name="_format">Texture format. See: `TextureFormat::Enum`.</param>
/// <param name="_flags">Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`) flags. Default texture sampling mode is linear, and wrap mode is repeat. - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap   mode. - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic   sampling.</param>
/// <param name="_mem">Texture data. If `_mem` is non-NULL, created texture will be immutable. If `_mem` is NULL content of the texture is uninitialized. When `_numLayers` is more than 1, expected memory layout is texture and all mips together for each array element.</param>
pub extern fn bgfx_create_texture_cube(size: u16, hasMips: bool, numLayers: u16, format: TextureFormat, flags: u64, mem: [*c]const Memory) TextureHandle;

/// Update 2D texture.
/// @attention It's valid to update only mutable texture. See `bgfx::createTexture2D` for more info.
/// <param name="_handle">Texture handle.</param>
/// <param name="_layer">Layer in texture array.</param>
/// <param name="_mip">Mip level.</param>
/// <param name="_x">X offset in texture.</param>
/// <param name="_y">Y offset in texture.</param>
/// <param name="_width">Width of texture block.</param>
/// <param name="_height">Height of texture block.</param>
/// <param name="_mem">Texture update data.</param>
/// <param name="_pitch">Pitch of input image (bytes). When _pitch is set to UINT16_MAX, it will be calculated internally based on _width.</param>
pub extern fn bgfx_update_texture_2d(handle: TextureHandle, layer: u16, mip: u8, x: u16, y: u16, width: u16, height: u16, mem: [*c]const Memory, pitch: u16) void;

/// Update 3D texture.
/// @attention It's valid to update only mutable texture. See `bgfx::createTexture3D` for more info.
/// <param name="_handle">Texture handle.</param>
/// <param name="_mip">Mip level.</param>
/// <param name="_x">X offset in texture.</param>
/// <param name="_y">Y offset in texture.</param>
/// <param name="_z">Z offset in texture.</param>
/// <param name="_width">Width of texture block.</param>
/// <param name="_height">Height of texture block.</param>
/// <param name="_depth">Depth of texture block.</param>
/// <param name="_mem">Texture update data.</param>
pub extern fn bgfx_update_texture_3d(handle: TextureHandle, mip: u8, x: u16, y: u16, z: u16, width: u16, height: u16, depth: u16, mem: [*c]const Memory) void;

/// Update Cube texture.
/// @attention It's valid to update only mutable texture. See `bgfx::createTextureCube` for more info.
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
pub extern fn bgfx_update_texture_cube(handle: TextureHandle, layer: u16, side: u8, mip: u8, x: u16, y: u16, width: u16, height: u16, mem: [*c]const Memory, pitch: u16) void;

/// Read back texture content.
/// @attention Texture must be created with `BGFX_TEXTURE_READ_BACK` flag.
/// @attention Availability depends on: `BGFX_CAPS_TEXTURE_READ_BACK`.
/// <param name="_handle">Texture handle.</param>
/// <param name="_data">Destination buffer.</param>
/// <param name="_mip">Mip level.</param>
pub extern fn bgfx_read_texture(handle: TextureHandle, data: ?*anyopaque, mip: u8) u32;

/// Set texture debug name.
/// <param name="_handle">Texture handle.</param>
/// <param name="_name">Texture name.</param>
/// <param name="_len">Texture name length (if length is INT32_MAX, it's expected that _name is zero terminated string.</param>
pub extern fn bgfx_set_texture_name(handle: TextureHandle, name: [*c]const u8, len: i32) void;

/// Returns texture direct access pointer.
/// @attention Availability depends on: `BGFX_CAPS_TEXTURE_DIRECT_ACCESS`. This feature
///   is available on GPUs that have unified memory architecture (UMA) support.
/// <param name="_handle">Texture handle.</param>
pub extern fn bgfx_get_direct_access_ptr(handle: TextureHandle) ?*anyopaque;

/// Destroy texture.
/// <param name="_handle">Texture handle.</param>
pub extern fn bgfx_destroy_texture(handle: TextureHandle) void;

/// Create frame buffer (simple).
/// <param name="_width">Texture width.</param>
/// <param name="_height">Texture height.</param>
/// <param name="_format">Texture format. See: `TextureFormat::Enum`.</param>
/// <param name="_textureFlags">Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`) flags. Default texture sampling mode is linear, and wrap mode is repeat. - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap   mode. - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic   sampling.</param>
pub extern fn bgfx_create_frame_buffer(width: u16, height: u16, format: TextureFormat, textureFlags: u64) FrameBufferHandle;

/// Create frame buffer with size based on back-buffer ratio. Frame buffer will maintain ratio
/// if back buffer resolution changes.
/// <param name="_ratio">Frame buffer size in respect to back-buffer size. See: `BackbufferRatio::Enum`.</param>
/// <param name="_format">Texture format. See: `TextureFormat::Enum`.</param>
/// <param name="_textureFlags">Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`) flags. Default texture sampling mode is linear, and wrap mode is repeat. - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap   mode. - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic   sampling.</param>
pub extern fn bgfx_create_frame_buffer_scaled(ratio: BackbufferRatio, format: TextureFormat, textureFlags: u64) FrameBufferHandle;

/// Create MRT frame buffer from texture handles (simple).
/// <param name="_num">Number of texture handles.</param>
/// <param name="_handles">Texture attachments.</param>
/// <param name="_destroyTexture">If true, textures will be destroyed when frame buffer is destroyed.</param>
pub extern fn bgfx_create_frame_buffer_from_handles(num: u8, handles: [*c]const TextureHandle, destroyTexture: bool) FrameBufferHandle;

/// Create MRT frame buffer from texture handles with specific layer and
/// mip level.
/// <param name="_num">Number of attachments.</param>
/// <param name="_attachment">Attachment texture info. See: `bgfx::Attachment`.</param>
/// <param name="_destroyTexture">If true, textures will be destroyed when frame buffer is destroyed.</param>
pub extern fn bgfx_create_frame_buffer_from_attachment(num: u8, attachment: [*c]const Attachment, destroyTexture: bool) FrameBufferHandle;

/// Create frame buffer for multiple window rendering.
/// @remarks
///   Frame buffer cannot be used for sampling.
/// @attention Availability depends on: `BGFX_CAPS_SWAP_CHAIN`.
/// <param name="_nwh">OS' target native window handle.</param>
/// <param name="_width">Window back buffer width.</param>
/// <param name="_height">Window back buffer height.</param>
/// <param name="_format">Window back buffer color format.</param>
/// <param name="_depthFormat">Window back buffer depth format.</param>
pub extern fn bgfx_create_frame_buffer_from_nwh(nwh: ?*anyopaque, width: u16, height: u16, format: TextureFormat, depthFormat: TextureFormat) FrameBufferHandle;

/// Set frame buffer debug name.
/// <param name="_handle">Frame buffer handle.</param>
/// <param name="_name">Frame buffer name.</param>
/// <param name="_len">Frame buffer name length (if length is INT32_MAX, it's expected that _name is zero terminated string.</param>
pub extern fn bgfx_set_frame_buffer_name(handle: FrameBufferHandle, name: [*c]const u8, len: i32) void;

/// Obtain texture handle of frame buffer attachment.
/// <param name="_handle">Frame buffer handle.</param>
pub extern fn bgfx_get_texture(handle: FrameBufferHandle, attachment: u8) TextureHandle;

/// Destroy frame buffer.
/// <param name="_handle">Frame buffer handle.</param>
pub extern fn bgfx_destroy_frame_buffer(handle: FrameBufferHandle) void;

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
/// <param name="_name">Uniform name in shader.</param>
/// <param name="_type">Type of uniform (See: `bgfx::UniformType`).</param>
/// <param name="_num">Number of elements in array.</param>
pub extern fn bgfx_create_uniform(name: [*c]const u8, type: UniformType, num: u16) UniformHandle;

/// Retrieve uniform info.
/// <param name="_handle">Handle to uniform object.</param>
/// <param name="_info">Uniform info.</param>
pub extern fn bgfx_get_uniform_info(handle: UniformHandle, info: [*c]UniformInfo) void;

/// Destroy shader uniform parameter.
/// <param name="_handle">Handle to uniform object.</param>
pub extern fn bgfx_destroy_uniform(handle: UniformHandle) void;

/// Create occlusion query.
pub extern fn bgfx_create_occlusion_query() OcclusionQueryHandle;

/// Retrieve occlusion query result from previous frame.
/// <param name="_handle">Handle to occlusion query object.</param>
/// <param name="_result">Number of pixels that passed test. This argument can be `NULL` if result of occlusion query is not needed.</param>
pub extern fn bgfx_get_result(handle: OcclusionQueryHandle, result: [*c]i32) OcclusionQueryResult;

/// Destroy occlusion query.
/// <param name="_handle">Handle to occlusion query object.</param>
pub extern fn bgfx_destroy_occlusion_query(handle: OcclusionQueryHandle) void;

/// Set palette color value.
/// <param name="_index">Index into palette.</param>
/// <param name="_rgba">RGBA floating point values.</param>
pub extern fn bgfx_set_palette_color(index: u8, rgba: [4]f32) void;

/// Set palette color value.
/// <param name="_index">Index into palette.</param>
/// <param name="_rgba">Packed 32-bit RGBA value.</param>
pub extern fn bgfx_set_palette_color_rgba8(index: u8, rgba: u32) void;

/// Set view name.
/// @remarks
///   This is debug only feature.
///   In graphics debugger view name will appear as:
///       "nnnc <view name>"
///        ^  ^ ^
///        |  +--- compute (C)
///        +------ view id
/// <param name="_id">View id.</param>
/// <param name="_name">View name.</param>
pub extern fn bgfx_set_view_name(id: ViewId, name: [*c]const u8) void;

/// Set view rectangle. Draw primitive outside view will be clipped.
/// <param name="_id">View id.</param>
/// <param name="_x">Position x from the left corner of the window.</param>
/// <param name="_y">Position y from the top corner of the window.</param>
/// <param name="_width">Width of view port region.</param>
/// <param name="_height">Height of view port region.</param>
pub extern fn bgfx_set_view_rect(id: ViewId, x: u16, y: u16, width: u16, height: u16) void;

/// Set view rectangle. Draw primitive outside view will be clipped.
/// <param name="_id">View id.</param>
/// <param name="_x">Position x from the left corner of the window.</param>
/// <param name="_y">Position y from the top corner of the window.</param>
/// <param name="_ratio">Width and height will be set in respect to back-buffer size. See: `BackbufferRatio::Enum`.</param>
pub extern fn bgfx_set_view_rect_ratio(id: ViewId, x: u16, y: u16, ratio: BackbufferRatio) void;

/// Set view scissor. Draw primitive outside view will be clipped. When
/// _x, _y, _width and _height are set to 0, scissor will be disabled.
/// <param name="_id">View id.</param>
/// <param name="_x">Position x from the left corner of the window.</param>
/// <param name="_y">Position y from the top corner of the window.</param>
/// <param name="_width">Width of view scissor region.</param>
/// <param name="_height">Height of view scissor region.</param>
pub extern fn bgfx_set_view_scissor(id: ViewId, x: u16, y: u16, width: u16, height: u16) void;

/// Set view clear flags.
/// <param name="_id">View id.</param>
/// <param name="_flags">Clear flags. Use `BGFX_CLEAR_NONE` to remove any clear operation. See: `BGFX_CLEAR_*`.</param>
/// <param name="_rgba">Color clear value.</param>
/// <param name="_depth">Depth clear value.</param>
/// <param name="_stencil">Stencil clear value.</param>
pub extern fn bgfx_set_view_clear(id: ViewId, flags: u16, rgba: u32, depth: f32, stencil: u8) void;

/// Set view clear flags with different clear color for each
/// frame buffer texture. `bgfx::setPaletteColor` must be used to set up a
/// clear color palette.
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
pub extern fn bgfx_set_view_clear_mrt(id: ViewId, flags: u16, depth: f32, stencil: u8, c0: u8, c1: u8, c2: u8, c3: u8, c4: u8, c5: u8, c6: u8, c7: u8) void;

/// Set view sorting mode.
/// @remarks
///   View mode must be set prior calling `bgfx::submit` for the view.
/// <param name="_id">View id.</param>
/// <param name="_mode">View sort mode. See `ViewMode::Enum`.</param>
pub extern fn bgfx_set_view_mode(id: ViewId, mode: ViewMode) void;

/// Set view frame buffer.
/// @remarks
///   Not persistent after `bgfx::reset` call.
/// <param name="_id">View id.</param>
/// <param name="_handle">Frame buffer handle. Passing `BGFX_INVALID_HANDLE` as frame buffer handle will draw primitives from this view into default back buffer.</param>
pub extern fn bgfx_set_view_frame_buffer(id: ViewId, handle: FrameBufferHandle) void;

/// Set view's view matrix and projection matrix,
/// all draw primitives in this view will use these two matrices.
/// <param name="_id">View id.</param>
/// <param name="_view">View matrix.</param>
/// <param name="_proj">Projection matrix.</param>
pub extern fn bgfx_set_view_transform(id: ViewId, view: ?*const anyopaque, proj: ?*const anyopaque) void;

/// Post submit view reordering.
/// <param name="_id">First view id.</param>
/// <param name="_num">Number of views to remap.</param>
/// <param name="_order">View remap id table. Passing `NULL` will reset view ids to default state.</param>
pub extern fn bgfx_set_view_order(id: ViewId, num: u16, order: [*c]const ViewId) void;

/// Reset all view settings to default.
pub extern fn bgfx_reset_view(id: ViewId) void;

/// Begin submitting draw calls from thread.
/// <param name="_forThread">Explicitly request an encoder for a worker thread.</param>
pub extern fn bgfx_encoder_begin(forThread: bool) ?*Encoder;

/// End submitting draw calls from thread.
/// <param name="_encoder">Encoder.</param>
pub extern fn bgfx_encoder_end(encoder: ?*Encoder) void;

/// Sets a debug marker. This allows you to group graphics calls together for easy browsing in
/// graphics debugging tools.
/// <param name="_marker">Marker string.</param>
pub extern fn bgfx_encoder_set_marker(self: ?*Encoder, marker: [*c]const u8) void;

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
/// <param name="_state">State flags. Default state for primitive type is   triangles. See: `BGFX_STATE_DEFAULT`.   - `BGFX_STATE_DEPTH_TEST_*` - Depth test function.   - `BGFX_STATE_BLEND_*` - See remark 1 about BGFX_STATE_BLEND_FUNC.   - `BGFX_STATE_BLEND_EQUATION_*` - See remark 2.   - `BGFX_STATE_CULL_*` - Backface culling mode.   - `BGFX_STATE_WRITE_*` - Enable R, G, B, A or Z write.   - `BGFX_STATE_MSAA` - Enable hardware multisample antialiasing.   - `BGFX_STATE_PT_[TRISTRIP/LINES/POINTS]` - Primitive type.</param>
/// <param name="_rgba">Sets blend factor used by `BGFX_STATE_BLEND_FACTOR` and   `BGFX_STATE_BLEND_INV_FACTOR` blend modes.</param>
pub extern fn bgfx_encoder_set_state(self: ?*Encoder, state: u64, rgba: u32) void;

/// Set condition for rendering.
/// <param name="_handle">Occlusion query handle.</param>
/// <param name="_visible">Render if occlusion query is visible.</param>
pub extern fn bgfx_encoder_set_condition(self: ?*Encoder, handle: OcclusionQueryHandle, visible: bool) void;

/// Set stencil test state.
/// <param name="_fstencil">Front stencil state.</param>
/// <param name="_bstencil">Back stencil state. If back is set to `BGFX_STENCIL_NONE` _fstencil is applied to both front and back facing primitives.</param>
pub extern fn bgfx_encoder_set_stencil(self: ?*Encoder, fstencil: u32, bstencil: u32) void;

/// Set scissor for draw primitive.
/// @remark
///   To scissor for all primitives in view see `bgfx::setViewScissor`.
/// <param name="_x">Position x from the left corner of the window.</param>
/// <param name="_y">Position y from the top corner of the window.</param>
/// <param name="_width">Width of view scissor region.</param>
/// <param name="_height">Height of view scissor region.</param>
pub extern fn bgfx_encoder_set_scissor(self: ?*Encoder, x: u16, y: u16, width: u16, height: u16) u16;

/// Set scissor from cache for draw primitive.
/// @remark
///   To scissor for all primitives in view see `bgfx::setViewScissor`.
/// <param name="_cache">Index in scissor cache.</param>
pub extern fn bgfx_encoder_set_scissor_cached(self: ?*Encoder, cache: u16) void;

/// Set model matrix for draw primitive. If it is not called,
/// the model will be rendered with an identity model matrix.
/// <param name="_mtx">Pointer to first matrix in array.</param>
/// <param name="_num">Number of matrices in array.</param>
pub extern fn bgfx_encoder_set_transform(self: ?*Encoder, mtx: ?*const anyopaque, num: u16) u32;

///  Set model matrix from matrix cache for draw primitive.
/// <param name="_cache">Index in matrix cache.</param>
/// <param name="_num">Number of matrices from cache.</param>
pub extern fn bgfx_encoder_set_transform_cached(self: ?*Encoder, cache: u32, num: u16) void;

/// Reserve matrices in internal matrix cache.
/// @attention Pointer returned can be modified until `bgfx::frame` is called.
/// <param name="_transform">Pointer to `Transform` structure.</param>
/// <param name="_num">Number of matrices.</param>
pub extern fn bgfx_encoder_alloc_transform(self: ?*Encoder, transform: [*c]Transform, num: u16) u32;

/// Set shader uniform parameter for draw primitive.
/// <param name="_handle">Uniform.</param>
/// <param name="_value">Pointer to uniform data.</param>
/// <param name="_num">Number of elements. Passing `UINT16_MAX` will use the _num passed on uniform creation.</param>
pub extern fn bgfx_encoder_set_uniform(self: ?*Encoder, handle: UniformHandle, value: ?*const anyopaque, num: u16) void;

/// Set index buffer for draw primitive.
/// <param name="_handle">Index buffer.</param>
/// <param name="_firstIndex">First index to render.</param>
/// <param name="_numIndices">Number of indices to render.</param>
pub extern fn bgfx_encoder_set_index_buffer(self: ?*Encoder, handle: IndexBufferHandle, firstIndex: u32, numIndices: u32) void;

/// Set index buffer for draw primitive.
/// <param name="_handle">Dynamic index buffer.</param>
/// <param name="_firstIndex">First index to render.</param>
/// <param name="_numIndices">Number of indices to render.</param>
pub extern fn bgfx_encoder_set_dynamic_index_buffer(self: ?*Encoder, handle: DynamicIndexBufferHandle, firstIndex: u32, numIndices: u32) void;

/// Set index buffer for draw primitive.
/// <param name="_tib">Transient index buffer.</param>
/// <param name="_firstIndex">First index to render.</param>
/// <param name="_numIndices">Number of indices to render.</param>
pub extern fn bgfx_encoder_set_transient_index_buffer(self: ?*Encoder, tib: [*c]const TransientIndexBuffer, firstIndex: u32, numIndices: u32) void;

/// Set vertex buffer for draw primitive.
/// <param name="_stream">Vertex stream.</param>
/// <param name="_handle">Vertex buffer.</param>
/// <param name="_startVertex">First vertex to render.</param>
/// <param name="_numVertices">Number of vertices to render.</param>
pub extern fn bgfx_encoder_set_vertex_buffer(self: ?*Encoder, stream: u8, handle: VertexBufferHandle, startVertex: u32, numVertices: u32) void;

/// Set vertex buffer for draw primitive.
/// <param name="_stream">Vertex stream.</param>
/// <param name="_handle">Vertex buffer.</param>
/// <param name="_startVertex">First vertex to render.</param>
/// <param name="_numVertices">Number of vertices to render.</param>
/// <param name="_layoutHandle">Vertex layout for aliasing vertex buffer. If invalid handle is used, vertex layout used for creation of vertex buffer will be used.</param>
pub extern fn bgfx_encoder_set_vertex_buffer_with_layout(self: ?*Encoder, stream: u8, handle: VertexBufferHandle, startVertex: u32, numVertices: u32, layoutHandle: VertexLayoutHandle) void;

/// Set vertex buffer for draw primitive.
/// <param name="_stream">Vertex stream.</param>
/// <param name="_handle">Dynamic vertex buffer.</param>
/// <param name="_startVertex">First vertex to render.</param>
/// <param name="_numVertices">Number of vertices to render.</param>
pub extern fn bgfx_encoder_set_dynamic_vertex_buffer(self: ?*Encoder, stream: u8, handle: DynamicVertexBufferHandle, startVertex: u32, numVertices: u32) void;

pub extern fn bgfx_encoder_set_dynamic_vertex_buffer_with_layout(self: ?*Encoder, stream: u8, handle: DynamicVertexBufferHandle, startVertex: u32, numVertices: u32, layoutHandle: VertexLayoutHandle) void;

/// Set vertex buffer for draw primitive.
/// <param name="_stream">Vertex stream.</param>
/// <param name="_tvb">Transient vertex buffer.</param>
/// <param name="_startVertex">First vertex to render.</param>
/// <param name="_numVertices">Number of vertices to render.</param>
pub extern fn bgfx_encoder_set_transient_vertex_buffer(self: ?*Encoder, stream: u8, tvb: [*c]const TransientVertexBuffer, startVertex: u32, numVertices: u32) void;

/// Set vertex buffer for draw primitive.
/// <param name="_stream">Vertex stream.</param>
/// <param name="_tvb">Transient vertex buffer.</param>
/// <param name="_startVertex">First vertex to render.</param>
/// <param name="_numVertices">Number of vertices to render.</param>
/// <param name="_layoutHandle">Vertex layout for aliasing vertex buffer. If invalid handle is used, vertex layout used for creation of vertex buffer will be used.</param>
pub extern fn bgfx_encoder_set_transient_vertex_buffer_with_layout(self: ?*Encoder, stream: u8, tvb: [*c]const TransientVertexBuffer, startVertex: u32, numVertices: u32, layoutHandle: VertexLayoutHandle) void;

/// Set number of vertices for auto generated vertices use in conjunction
/// with gl_VertexID.
/// @attention Availability depends on: `BGFX_CAPS_VERTEX_ID`.
/// <param name="_numVertices">Number of vertices.</param>
pub extern fn bgfx_encoder_set_vertex_count(self: ?*Encoder, numVertices: u32) void;

/// Set instance data buffer for draw primitive.
/// <param name="_idb">Transient instance data buffer.</param>
/// <param name="_start">First instance data.</param>
/// <param name="_num">Number of data instances.</param>
pub extern fn bgfx_encoder_set_instance_data_buffer(self: ?*Encoder, idb: [*c]const InstanceDataBuffer, start: u32, num: u32) void;

/// Set instance data buffer for draw primitive.
/// <param name="_handle">Vertex buffer.</param>
/// <param name="_startVertex">First instance data.</param>
/// <param name="_num">Number of data instances. Set instance data buffer for draw primitive.</param>
pub extern fn bgfx_encoder_set_instance_data_from_vertex_buffer(self: ?*Encoder, handle: VertexBufferHandle, startVertex: u32, num: u32) void;

/// Set instance data buffer for draw primitive.
/// <param name="_handle">Dynamic vertex buffer.</param>
/// <param name="_startVertex">First instance data.</param>
/// <param name="_num">Number of data instances.</param>
pub extern fn bgfx_encoder_set_instance_data_from_dynamic_vertex_buffer(self: ?*Encoder, handle: DynamicVertexBufferHandle, startVertex: u32, num: u32) void;

/// Set number of instances for auto generated instances use in conjunction
/// with gl_InstanceID.
/// @attention Availability depends on: `BGFX_CAPS_VERTEX_ID`.
pub extern fn bgfx_encoder_set_instance_count(self: ?*Encoder, numInstances: u32) void;

/// Set texture stage for draw primitive.
/// <param name="_stage">Texture unit.</param>
/// <param name="_sampler">Program sampler.</param>
/// <param name="_handle">Texture handle.</param>
/// <param name="_flags">Texture sampling mode. Default value UINT32_MAX uses   texture sampling settings from the texture.   - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap     mode.   - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic     sampling.</param>
pub extern fn bgfx_encoder_set_texture(self: ?*Encoder, stage: u8, sampler: UniformHandle, handle: TextureHandle, flags: u32) void;

/// Submit an empty primitive for rendering. Uniforms and draw state
/// will be applied but no geometry will be submitted. Useful in cases
/// when no other draw/compute primitive is submitted to view, but it's
/// desired to execute clear view.
/// @remark
///   These empty draw calls will sort before ordinary draw calls.
/// <param name="_id">View id.</param>
pub extern fn bgfx_encoder_touch(self: ?*Encoder, id: ViewId) void;

/// Submit primitive for rendering.
/// <param name="_id">View id.</param>
/// <param name="_program">Program.</param>
/// <param name="_depth">Depth for sorting.</param>
/// <param name="_flags">Discard or preserve states. See `BGFX_DISCARD_*`.</param>
pub extern fn bgfx_encoder_submit(self: ?*Encoder, id: ViewId, program: ProgramHandle, depth: u32, flags: u8) void;

/// Submit primitive with occlusion query for rendering.
/// <param name="_id">View id.</param>
/// <param name="_program">Program.</param>
/// <param name="_occlusionQuery">Occlusion query.</param>
/// <param name="_depth">Depth for sorting.</param>
/// <param name="_flags">Discard or preserve states. See `BGFX_DISCARD_*`.</param>
pub extern fn bgfx_encoder_submit_occlusion_query(self: ?*Encoder, id: ViewId, program: ProgramHandle, occlusionQuery: OcclusionQueryHandle, depth: u32, flags: u8) void;

/// Submit primitive for rendering with index and instance data info from
/// indirect buffer.
/// <param name="_id">View id.</param>
/// <param name="_program">Program.</param>
/// <param name="_indirectHandle">Indirect buffer.</param>
/// <param name="_start">First element in indirect buffer.</param>
/// <param name="_num">Number of dispatches.</param>
/// <param name="_depth">Depth for sorting.</param>
/// <param name="_flags">Discard or preserve states. See `BGFX_DISCARD_*`.</param>
pub extern fn bgfx_encoder_submit_indirect(self: ?*Encoder, id: ViewId, program: ProgramHandle, indirectHandle: IndirectBufferHandle, start: u16, num: u16, depth: u32, flags: u8) void;

/// Set compute index buffer.
/// <param name="_stage">Compute stage.</param>
/// <param name="_handle">Index buffer handle.</param>
/// <param name="_access">Buffer access. See `Access::Enum`.</param>
pub extern fn bgfx_encoder_set_compute_index_buffer(self: ?*Encoder, stage: u8, handle: IndexBufferHandle, access: Access) void;

/// Set compute vertex buffer.
/// <param name="_stage">Compute stage.</param>
/// <param name="_handle">Vertex buffer handle.</param>
/// <param name="_access">Buffer access. See `Access::Enum`.</param>
pub extern fn bgfx_encoder_set_compute_vertex_buffer(self: ?*Encoder, stage: u8, handle: VertexBufferHandle, access: Access) void;

/// Set compute dynamic index buffer.
/// <param name="_stage">Compute stage.</param>
/// <param name="_handle">Dynamic index buffer handle.</param>
/// <param name="_access">Buffer access. See `Access::Enum`.</param>
pub extern fn bgfx_encoder_set_compute_dynamic_index_buffer(self: ?*Encoder, stage: u8, handle: DynamicIndexBufferHandle, access: Access) void;

/// Set compute dynamic vertex buffer.
/// <param name="_stage">Compute stage.</param>
/// <param name="_handle">Dynamic vertex buffer handle.</param>
/// <param name="_access">Buffer access. See `Access::Enum`.</param>
pub extern fn bgfx_encoder_set_compute_dynamic_vertex_buffer(self: ?*Encoder, stage: u8, handle: DynamicVertexBufferHandle, access: Access) void;

/// Set compute indirect buffer.
/// <param name="_stage">Compute stage.</param>
/// <param name="_handle">Indirect buffer handle.</param>
/// <param name="_access">Buffer access. See `Access::Enum`.</param>
pub extern fn bgfx_encoder_set_compute_indirect_buffer(self: ?*Encoder, stage: u8, handle: IndirectBufferHandle, access: Access) void;

/// Set compute image from texture.
/// <param name="_stage">Compute stage.</param>
/// <param name="_handle">Texture handle.</param>
/// <param name="_mip">Mip level.</param>
/// <param name="_access">Image access. See `Access::Enum`.</param>
/// <param name="_format">Texture format. See: `TextureFormat::Enum`.</param>
pub extern fn bgfx_encoder_set_image(self: ?*Encoder, stage: u8, handle: TextureHandle, mip: u8, access: Access, format: TextureFormat) void;

/// Dispatch compute.
/// <param name="_id">View id.</param>
/// <param name="_program">Compute program.</param>
/// <param name="_numX">Number of groups X.</param>
/// <param name="_numY">Number of groups Y.</param>
/// <param name="_numZ">Number of groups Z.</param>
/// <param name="_flags">Discard or preserve states. See `BGFX_DISCARD_*`.</param>
pub extern fn bgfx_encoder_dispatch(self: ?*Encoder, id: ViewId, program: ProgramHandle, numX: u32, numY: u32, numZ: u32, flags: u8) void;

/// Dispatch compute indirect.
/// <param name="_id">View id.</param>
/// <param name="_program">Compute program.</param>
/// <param name="_indirectHandle">Indirect buffer.</param>
/// <param name="_start">First element in indirect buffer.</param>
/// <param name="_num">Number of dispatches.</param>
/// <param name="_flags">Discard or preserve states. See `BGFX_DISCARD_*`.</param>
pub extern fn bgfx_encoder_dispatch_indirect(self: ?*Encoder, id: ViewId, program: ProgramHandle, indirectHandle: IndirectBufferHandle, start: u16, num: u16, flags: u8) void;

/// Discard previously set state for draw or compute call.
/// <param name="_flags">Discard or preserve states. See `BGFX_DISCARD_*`.</param>
pub extern fn bgfx_encoder_discard(self: ?*Encoder, flags: u8) void;

/// Blit 2D texture region between two 2D textures.
/// @attention Destination texture must be created with `BGFX_TEXTURE_BLIT_DST` flag.
/// @attention Availability depends on: `BGFX_CAPS_TEXTURE_BLIT`.
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
pub extern fn bgfx_encoder_blit(self: ?*Encoder, id: ViewId, dst: TextureHandle, dstMip: u8, dstX: u16, dstY: u16, dstZ: u16, src: TextureHandle, srcMip: u8, srcX: u16, srcY: u16, srcZ: u16, width: u16, height: u16, depth: u16) void;

/// Request screen shot of window back buffer.
/// @remarks
///   `bgfx::CallbackI::screenShot` must be implemented.
/// @attention Frame buffer handle must be created with OS' target native window handle.
/// <param name="_handle">Frame buffer handle. If handle is `BGFX_INVALID_HANDLE` request will be made for main window back buffer.</param>
/// <param name="_filePath">Will be passed to `bgfx::CallbackI::screenShot` callback.</param>
pub extern fn bgfx_request_screen_shot(handle: FrameBufferHandle, filePath: [*c]const u8) void;

/// Render frame.
/// @attention `bgfx::renderFrame` is blocking call. It waits for
///   `bgfx::frame` to be called from API thread to process frame.
///   If timeout value is passed call will timeout and return even
///   if `bgfx::frame` is not called.
/// @warning This call should be only used on platforms that don't
///   allow creating separate rendering thread. If it is called before
///   to bgfx::init, render thread won't be created by bgfx::init call.
/// <param name="_msecs">Timeout in milliseconds.</param>
pub extern fn bgfx_render_frame(msecs: i32) RenderFrame;

/// Set platform data.
/// @warning Must be called before `bgfx::init`.
/// <param name="_data">Platform data.</param>
pub extern fn bgfx_set_platform_data(data: [*c]const PlatformData) void;

/// Get internal data for interop.
/// @attention It's expected you understand some bgfx internals before you
///   use this call.
/// @warning Must be called only on render thread.
pub extern fn bgfx_get_internal_data() [*c]const InternalData;

/// Override internal texture with externally created texture. Previously
/// created internal texture will released.
/// @attention It's expected you understand some bgfx internals before you
///   use this call.
/// @warning Must be called only on render thread.
/// <param name="_handle">Texture handle.</param>
/// <param name="_ptr">Native API pointer to texture.</param>
pub extern fn bgfx_override_internal_texture_ptr(handle: TextureHandle, ptr: usize) usize;

/// Override internal texture by creating new texture. Previously created
/// internal texture will released.
/// @attention It's expected you understand some bgfx internals before you
///   use this call.
/// @returns Native API pointer to texture. If result is 0, texture is not created yet from the
///   main thread.
/// @warning Must be called only on render thread.
/// <param name="_handle">Texture handle.</param>
/// <param name="_width">Width.</param>
/// <param name="_height">Height.</param>
/// <param name="_numMips">Number of mip-maps.</param>
/// <param name="_format">Texture format. See: `TextureFormat::Enum`.</param>
/// <param name="_flags">Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`) flags. Default texture sampling mode is linear, and wrap mode is repeat. - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap   mode. - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic   sampling.</param>
pub extern fn bgfx_override_internal_texture(handle: TextureHandle, width: u16, height: u16, numMips: u8, format: TextureFormat, flags: u64) usize;

/// Sets a debug marker. This allows you to group graphics calls together for easy browsing in
/// graphics debugging tools.
/// <param name="_marker">Marker string.</param>
pub extern fn bgfx_set_marker(marker: [*c]const u8) void;

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
/// <param name="_state">State flags. Default state for primitive type is   triangles. See: `BGFX_STATE_DEFAULT`.   - `BGFX_STATE_DEPTH_TEST_*` - Depth test function.   - `BGFX_STATE_BLEND_*` - See remark 1 about BGFX_STATE_BLEND_FUNC.   - `BGFX_STATE_BLEND_EQUATION_*` - See remark 2.   - `BGFX_STATE_CULL_*` - Backface culling mode.   - `BGFX_STATE_WRITE_*` - Enable R, G, B, A or Z write.   - `BGFX_STATE_MSAA` - Enable hardware multisample antialiasing.   - `BGFX_STATE_PT_[TRISTRIP/LINES/POINTS]` - Primitive type.</param>
/// <param name="_rgba">Sets blend factor used by `BGFX_STATE_BLEND_FACTOR` and   `BGFX_STATE_BLEND_INV_FACTOR` blend modes.</param>
pub extern fn bgfx_set_state(state: u64, rgba: u32) void;

/// Set condition for rendering.
/// <param name="_handle">Occlusion query handle.</param>
/// <param name="_visible">Render if occlusion query is visible.</param>
pub extern fn bgfx_set_condition(handle: OcclusionQueryHandle, visible: bool) void;

/// Set stencil test state.
/// <param name="_fstencil">Front stencil state.</param>
/// <param name="_bstencil">Back stencil state. If back is set to `BGFX_STENCIL_NONE` _fstencil is applied to both front and back facing primitives.</param>
pub extern fn bgfx_set_stencil(fstencil: u32, bstencil: u32) void;

/// Set scissor for draw primitive.
/// @remark
///   To scissor for all primitives in view see `bgfx::setViewScissor`.
/// <param name="_x">Position x from the left corner of the window.</param>
/// <param name="_y">Position y from the top corner of the window.</param>
/// <param name="_width">Width of view scissor region.</param>
/// <param name="_height">Height of view scissor region.</param>
pub extern fn bgfx_set_scissor(x: u16, y: u16, width: u16, height: u16) u16;

/// Set scissor from cache for draw primitive.
/// @remark
///   To scissor for all primitives in view see `bgfx::setViewScissor`.
/// <param name="_cache">Index in scissor cache.</param>
pub extern fn bgfx_set_scissor_cached(cache: u16) void;

/// Set model matrix for draw primitive. If it is not called,
/// the model will be rendered with an identity model matrix.
/// <param name="_mtx">Pointer to first matrix in array.</param>
/// <param name="_num">Number of matrices in array.</param>
pub extern fn bgfx_set_transform(mtx: ?*const anyopaque, num: u16) u32;

///  Set model matrix from matrix cache for draw primitive.
/// <param name="_cache">Index in matrix cache.</param>
/// <param name="_num">Number of matrices from cache.</param>
pub extern fn bgfx_set_transform_cached(cache: u32, num: u16) void;

/// Reserve matrices in internal matrix cache.
/// @attention Pointer returned can be modified until `bgfx::frame` is called.
/// <param name="_transform">Pointer to `Transform` structure.</param>
/// <param name="_num">Number of matrices.</param>
pub extern fn bgfx_alloc_transform(transform: [*c]Transform, num: u16) u32;

/// Set shader uniform parameter for draw primitive.
/// <param name="_handle">Uniform.</param>
/// <param name="_value">Pointer to uniform data.</param>
/// <param name="_num">Number of elements. Passing `UINT16_MAX` will use the _num passed on uniform creation.</param>
pub extern fn bgfx_set_uniform(handle: UniformHandle, value: ?*const anyopaque, num: u16) void;

/// Set index buffer for draw primitive.
/// <param name="_handle">Index buffer.</param>
/// <param name="_firstIndex">First index to render.</param>
/// <param name="_numIndices">Number of indices to render.</param>
pub extern fn bgfx_set_index_buffer(handle: IndexBufferHandle, firstIndex: u32, numIndices: u32) void;

/// Set index buffer for draw primitive.
/// <param name="_handle">Dynamic index buffer.</param>
/// <param name="_firstIndex">First index to render.</param>
/// <param name="_numIndices">Number of indices to render.</param>
pub extern fn bgfx_set_dynamic_index_buffer(handle: DynamicIndexBufferHandle, firstIndex: u32, numIndices: u32) void;

/// Set index buffer for draw primitive.
/// <param name="_tib">Transient index buffer.</param>
/// <param name="_firstIndex">First index to render.</param>
/// <param name="_numIndices">Number of indices to render.</param>
pub extern fn bgfx_set_transient_index_buffer(tib: [*c]const TransientIndexBuffer, firstIndex: u32, numIndices: u32) void;

/// Set vertex buffer for draw primitive.
/// <param name="_stream">Vertex stream.</param>
/// <param name="_handle">Vertex buffer.</param>
/// <param name="_startVertex">First vertex to render.</param>
/// <param name="_numVertices">Number of vertices to render.</param>
pub extern fn bgfx_set_vertex_buffer(stream: u8, handle: VertexBufferHandle, startVertex: u32, numVertices: u32) void;

/// Set vertex buffer for draw primitive.
/// <param name="_stream">Vertex stream.</param>
/// <param name="_handle">Vertex buffer.</param>
/// <param name="_startVertex">First vertex to render.</param>
/// <param name="_numVertices">Number of vertices to render.</param>
/// <param name="_layoutHandle">Vertex layout for aliasing vertex buffer. If invalid handle is used, vertex layout used for creation of vertex buffer will be used.</param>
pub extern fn bgfx_set_vertex_buffer_with_layout(stream: u8, handle: VertexBufferHandle, startVertex: u32, numVertices: u32, layoutHandle: VertexLayoutHandle) void;

/// Set vertex buffer for draw primitive.
/// <param name="_stream">Vertex stream.</param>
/// <param name="_handle">Dynamic vertex buffer.</param>
/// <param name="_startVertex">First vertex to render.</param>
/// <param name="_numVertices">Number of vertices to render.</param>
pub extern fn bgfx_set_dynamic_vertex_buffer(stream: u8, handle: DynamicVertexBufferHandle, startVertex: u32, numVertices: u32) void;

/// Set vertex buffer for draw primitive.
/// <param name="_stream">Vertex stream.</param>
/// <param name="_handle">Dynamic vertex buffer.</param>
/// <param name="_startVertex">First vertex to render.</param>
/// <param name="_numVertices">Number of vertices to render.</param>
/// <param name="_layoutHandle">Vertex layout for aliasing vertex buffer. If invalid handle is used, vertex layout used for creation of vertex buffer will be used.</param>
pub extern fn bgfx_set_dynamic_vertex_buffer_with_layout(stream: u8, handle: DynamicVertexBufferHandle, startVertex: u32, numVertices: u32, layoutHandle: VertexLayoutHandle) void;

/// Set vertex buffer for draw primitive.
/// <param name="_stream">Vertex stream.</param>
/// <param name="_tvb">Transient vertex buffer.</param>
/// <param name="_startVertex">First vertex to render.</param>
/// <param name="_numVertices">Number of vertices to render.</param>
pub extern fn bgfx_set_transient_vertex_buffer(stream: u8, tvb: [*c]const TransientVertexBuffer, startVertex: u32, numVertices: u32) void;

/// Set vertex buffer for draw primitive.
/// <param name="_stream">Vertex stream.</param>
/// <param name="_tvb">Transient vertex buffer.</param>
/// <param name="_startVertex">First vertex to render.</param>
/// <param name="_numVertices">Number of vertices to render.</param>
/// <param name="_layoutHandle">Vertex layout for aliasing vertex buffer. If invalid handle is used, vertex layout used for creation of vertex buffer will be used.</param>
pub extern fn bgfx_set_transient_vertex_buffer_with_layout(stream: u8, tvb: [*c]const TransientVertexBuffer, startVertex: u32, numVertices: u32, layoutHandle: VertexLayoutHandle) void;

/// Set number of vertices for auto generated vertices use in conjunction
/// with gl_VertexID.
/// @attention Availability depends on: `BGFX_CAPS_VERTEX_ID`.
/// <param name="_numVertices">Number of vertices.</param>
pub extern fn bgfx_set_vertex_count(numVertices: u32) void;

/// Set instance data buffer for draw primitive.
/// <param name="_idb">Transient instance data buffer.</param>
/// <param name="_start">First instance data.</param>
/// <param name="_num">Number of data instances.</param>
pub extern fn bgfx_set_instance_data_buffer(idb: [*c]const InstanceDataBuffer, start: u32, num: u32) void;

/// Set instance data buffer for draw primitive.
/// <param name="_handle">Vertex buffer.</param>
/// <param name="_startVertex">First instance data.</param>
/// <param name="_num">Number of data instances. Set instance data buffer for draw primitive.</param>
pub extern fn bgfx_set_instance_data_from_vertex_buffer(handle: VertexBufferHandle, startVertex: u32, num: u32) void;

/// Set instance data buffer for draw primitive.
/// <param name="_handle">Dynamic vertex buffer.</param>
/// <param name="_startVertex">First instance data.</param>
/// <param name="_num">Number of data instances.</param>
pub extern fn bgfx_set_instance_data_from_dynamic_vertex_buffer(handle: DynamicVertexBufferHandle, startVertex: u32, num: u32) void;

/// Set number of instances for auto generated instances use in conjunction
/// with gl_InstanceID.
/// @attention Availability depends on: `BGFX_CAPS_VERTEX_ID`.
pub extern fn bgfx_set_instance_count(numInstances: u32) void;

/// Set texture stage for draw primitive.
/// <param name="_stage">Texture unit.</param>
/// <param name="_sampler">Program sampler.</param>
/// <param name="_handle">Texture handle.</param>
/// <param name="_flags">Texture sampling mode. Default value UINT32_MAX uses   texture sampling settings from the texture.   - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap     mode.   - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic     sampling.</param>
pub extern fn bgfx_set_texture(stage: u8, sampler: UniformHandle, handle: TextureHandle, flags: u32) void;

/// Submit an empty primitive for rendering. Uniforms and draw state
/// will be applied but no geometry will be submitted.
/// @remark
///   These empty draw calls will sort before ordinary draw calls.
/// <param name="_id">View id.</param>
pub extern fn bgfx_touch(id: ViewId) void;

/// Submit primitive for rendering.
/// <param name="_id">View id.</param>
/// <param name="_program">Program.</param>
/// <param name="_depth">Depth for sorting.</param>
/// <param name="_flags">Which states to discard for next draw. See `BGFX_DISCARD_*`.</param>
pub extern fn bgfx_submit(id: ViewId, program: ProgramHandle, depth: u32, flags: u8) void;

/// Submit primitive with occlusion query for rendering.
/// <param name="_id">View id.</param>
/// <param name="_program">Program.</param>
/// <param name="_occlusionQuery">Occlusion query.</param>
/// <param name="_depth">Depth for sorting.</param>
/// <param name="_flags">Which states to discard for next draw. See `BGFX_DISCARD_*`.</param>
pub extern fn bgfx_submit_occlusion_query(id: ViewId, program: ProgramHandle, occlusionQuery: OcclusionQueryHandle, depth: u32, flags: u8) void;

/// Submit primitive for rendering with index and instance data info from
/// indirect buffer.
/// <param name="_id">View id.</param>
/// <param name="_program">Program.</param>
/// <param name="_indirectHandle">Indirect buffer.</param>
/// <param name="_start">First element in indirect buffer.</param>
/// <param name="_num">Number of dispatches.</param>
/// <param name="_depth">Depth for sorting.</param>
/// <param name="_flags">Which states to discard for next draw. See `BGFX_DISCARD_*`.</param>
pub extern fn bgfx_submit_indirect(id: ViewId, program: ProgramHandle, indirectHandle: IndirectBufferHandle, start: u16, num: u16, depth: u32, flags: u8) void;

/// Set compute index buffer.
/// <param name="_stage">Compute stage.</param>
/// <param name="_handle">Index buffer handle.</param>
/// <param name="_access">Buffer access. See `Access::Enum`.</param>
pub extern fn bgfx_set_compute_index_buffer(stage: u8, handle: IndexBufferHandle, access: Access) void;

/// Set compute vertex buffer.
/// <param name="_stage">Compute stage.</param>
/// <param name="_handle">Vertex buffer handle.</param>
/// <param name="_access">Buffer access. See `Access::Enum`.</param>
pub extern fn bgfx_set_compute_vertex_buffer(stage: u8, handle: VertexBufferHandle, access: Access) void;

/// Set compute dynamic index buffer.
/// <param name="_stage">Compute stage.</param>
/// <param name="_handle">Dynamic index buffer handle.</param>
/// <param name="_access">Buffer access. See `Access::Enum`.</param>
pub extern fn bgfx_set_compute_dynamic_index_buffer(stage: u8, handle: DynamicIndexBufferHandle, access: Access) void;

/// Set compute dynamic vertex buffer.
/// <param name="_stage">Compute stage.</param>
/// <param name="_handle">Dynamic vertex buffer handle.</param>
/// <param name="_access">Buffer access. See `Access::Enum`.</param>
pub extern fn bgfx_set_compute_dynamic_vertex_buffer(stage: u8, handle: DynamicVertexBufferHandle, access: Access) void;

/// Set compute indirect buffer.
/// <param name="_stage">Compute stage.</param>
/// <param name="_handle">Indirect buffer handle.</param>
/// <param name="_access">Buffer access. See `Access::Enum`.</param>
pub extern fn bgfx_set_compute_indirect_buffer(stage: u8, handle: IndirectBufferHandle, access: Access) void;

/// Set compute image from texture.
/// <param name="_stage">Compute stage.</param>
/// <param name="_handle">Texture handle.</param>
/// <param name="_mip">Mip level.</param>
/// <param name="_access">Image access. See `Access::Enum`.</param>
/// <param name="_format">Texture format. See: `TextureFormat::Enum`.</param>
pub extern fn bgfx_set_image(stage: u8, handle: TextureHandle, mip: u8, access: Access, format: TextureFormat) void;

/// Dispatch compute.
/// <param name="_id">View id.</param>
/// <param name="_program">Compute program.</param>
/// <param name="_numX">Number of groups X.</param>
/// <param name="_numY">Number of groups Y.</param>
/// <param name="_numZ">Number of groups Z.</param>
/// <param name="_flags">Discard or preserve states. See `BGFX_DISCARD_*`.</param>
pub extern fn bgfx_dispatch(id: ViewId, program: ProgramHandle, numX: u32, numY: u32, numZ: u32, flags: u8) void;

/// Dispatch compute indirect.
/// <param name="_id">View id.</param>
/// <param name="_program">Compute program.</param>
/// <param name="_indirectHandle">Indirect buffer.</param>
/// <param name="_start">First element in indirect buffer.</param>
/// <param name="_num">Number of dispatches.</param>
/// <param name="_flags">Discard or preserve states. See `BGFX_DISCARD_*`.</param>
pub extern fn bgfx_dispatch_indirect(id: ViewId, program: ProgramHandle, indirectHandle: IndirectBufferHandle, start: u16, num: u16, flags: u8) void;

/// Discard previously set state for draw or compute call.
/// <param name="_flags">Draw/compute states to discard.</param>
pub extern fn bgfx_discard(flags: u8) void;

/// Blit 2D texture region between two 2D textures.
/// @attention Destination texture must be created with `BGFX_TEXTURE_BLIT_DST` flag.
/// @attention Availability depends on: `BGFX_CAPS_TEXTURE_BLIT`.
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
pub extern fn bgfx_blit(id: ViewId, dst: TextureHandle, dstMip: u8, dstX: u16, dstY: u16, dstZ: u16, src: TextureHandle, srcMip: u8, srcX: u16, srcY: u16, srcZ: u16, width: u16, height: u16, depth: u16) void;


