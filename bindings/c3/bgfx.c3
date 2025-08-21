/*
 * Copyright 2011-2025 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

/*
 *
 * AUTO GENERATED! DO NOT EDIT!
 *
 */
module bgfx;

enum StateFlags : const ulong
{
	// Enable R write.
	WRITER                 = 0x0000000000000001,

	// Enable G write.
	WRITEG                 = 0x0000000000000002,

	// Enable B write.
	WRITEB                 = 0x0000000000000004,

	// Enable alpha write.
	WRITEA                 = 0x0000000000000008,

	// Enable depth write.
	WRITEZ                 = 0x0000004000000000,

	// Enable RGB write.
	WRITERGB               = 0x0000000000000007,

	// Write all channels mask.
	WRITEMASK              = 0x000000400000000f,

	// Enable depth test, less.
	DEPTHTESTLESS          = 0x0000000000000010,

	// Enable depth test, less or equal.
	DEPTHTESTLEQUAL        = 0x0000000000000020,

	// Enable depth test, equal.
	DEPTHTESTEQUAL         = 0x0000000000000030,

	// Enable depth test, greater or equal.
	DEPTHTESTGEQUAL        = 0x0000000000000040,

	// Enable depth test, greater.
	DEPTHTESTGREATER       = 0x0000000000000050,

	// Enable depth test, not equal.
	DEPTHTESTNOTEQUAL      = 0x0000000000000060,

	// Enable depth test, never.
	DEPTHTESTNEVER         = 0x0000000000000070,

	// Enable depth test, always.
	DEPTHTESTALWAYS        = 0x0000000000000080,
	DEPTHTESTSHIFT         = 4,
	DEPTHTESTMASK          = 0x00000000000000f0,

	// 0, 0, 0, 0
	BLENDZERO              = 0x0000000000001000,

	// 1, 1, 1, 1
	BLENDONE               = 0x0000000000002000,

	// Rs, Gs, Bs, As
	BLENDSRCCOLOR          = 0x0000000000003000,

	// 1-Rs, 1-Gs, 1-Bs, 1-As
	BLENDINVSRCCOLOR       = 0x0000000000004000,

	// As, As, As, As
	BLENDSRCALPHA          = 0x0000000000005000,

	// 1-As, 1-As, 1-As, 1-As
	BLENDINVSRCALPHA       = 0x0000000000006000,

	// Ad, Ad, Ad, Ad
	BLENDDSTALPHA          = 0x0000000000007000,

	// 1-Ad, 1-Ad, 1-Ad ,1-Ad
	BLENDINVDSTALPHA       = 0x0000000000008000,

	// Rd, Gd, Bd, Ad
	BLENDDSTCOLOR          = 0x0000000000009000,

	// 1-Rd, 1-Gd, 1-Bd, 1-Ad
	BLENDINVDSTCOLOR       = 0x000000000000a000,

	// f, f, f, 1; f = min(As, 1-Ad)
	BLENDSRCALPHASAT       = 0x000000000000b000,

	// Blend factor
	BLENDFACTOR            = 0x000000000000c000,

	// 1-Blend factor
	BLENDINVFACTOR         = 0x000000000000d000,
	BLENDSHIFT             = 12,
	BLENDMASK              = 0x000000000ffff000,

	// Blend add: src + dst.
	BLENDEQUATIONADD       = 0x0000000000000000,

	// Blend subtract: src - dst.
	BLENDEQUATIONSUB       = 0x0000000010000000,

	// Blend reverse subtract: dst - src.
	BLENDEQUATIONREVSUB    = 0x0000000020000000,

	// Blend min: min(src, dst).
	BLENDEQUATIONMIN       = 0x0000000030000000,

	// Blend max: max(src, dst).
	BLENDEQUATIONMAX       = 0x0000000040000000,
	BLENDEQUATIONSHIFT     = 28,
	BLENDEQUATIONMASK      = 0x00000003f0000000,

	// Cull clockwise triangles.
	CULLCW                 = 0x0000001000000000,

	// Cull counter-clockwise triangles.
	CULLCCW                = 0x0000002000000000,
	CULLSHIFT              = 36,
	CULLMASK               = 0x0000003000000000,
	ALPHAREFSHIFT          = 40,
	ALPHAREFMASK           = 0x0000ff0000000000,

	// Tristrip.
	PTTRISTRIP             = 0x0001000000000000,

	// Lines.
	PTLINES                = 0x0002000000000000,

	// Line strip.
	PTLINESTRIP            = 0x0003000000000000,

	// Points.
	PTPOINTS               = 0x0004000000000000,
	PTSHIFT                = 48,
	PTMASK                 = 0x0007000000000000,
	POINTSIZESHIFT         = 52,
	POINTSIZEMASK          = 0x00f0000000000000,

	// Enable MSAA rasterization.
	MSAA                   = 0x0100000000000000,

	// Enable line AA rasterization.
	LINEAA                 = 0x0200000000000000,

	// Enable conservative rasterization.
	CONSERVATIVERASTER     = 0x0400000000000000,

	// No state.
	NONE                   = 0x0000000000000000,

	// Front counter-clockwise (default is clockwise).
	FRONTCCW               = 0x0000008000000000,

	// Enable blend independent.
	BLENDINDEPENDENT       = 0x0000000400000000,

	// Enable alpha to coverage.
	BLENDALPHATOCOVERAGE   = 0x0000000800000000,

	// Default state is write to RGB, alpha, and depth with depth test less enabled, with clockwise
	// culling and MSAA (when writing into MSAA frame buffer, otherwise this flag is ignored).
	DEFAULT                = 0x010000500000001f,
	MASK                   = 0xffffffffffffffff,
	RESERVEDSHIFT          = 61,
	RESERVEDMASK           = 0xe000000000000000,
}

enum StencilFlags : const uint
{
	FUNCREFSHIFT           = 0,
	FUNCREFMASK            = 0x000000ff,
	FUNCRMASKSHIFT         = 8,
	FUNCRMASKMASK          = 0x0000ff00,
	NONE                   = 0x00000000,
	MASK                   = 0xffffffff,
	DEFAULT                = 0x00000000,

	// Enable stencil test, less.
	TESTLESS               = 0x00010000,

	// Enable stencil test, less or equal.
	TESTLEQUAL             = 0x00020000,

	// Enable stencil test, equal.
	TESTEQUAL              = 0x00030000,

	// Enable stencil test, greater or equal.
	TESTGEQUAL             = 0x00040000,

	// Enable stencil test, greater.
	TESTGREATER            = 0x00050000,

	// Enable stencil test, not equal.
	TESTNOTEQUAL           = 0x00060000,

	// Enable stencil test, never.
	TESTNEVER              = 0x00070000,

	// Enable stencil test, always.
	TESTALWAYS             = 0x00080000,
	TESTSHIFT              = 16,
	TESTMASK               = 0x000f0000,

	// Zero.
	OPFAILSZERO            = 0x00000000,

	// Keep.
	OPFAILSKEEP            = 0x00100000,

	// Replace.
	OPFAILSREPLACE         = 0x00200000,

	// Increment and wrap.
	OPFAILSINCR            = 0x00300000,

	// Increment and clamp.
	OPFAILSINCRSAT         = 0x00400000,

	// Decrement and wrap.
	OPFAILSDECR            = 0x00500000,

	// Decrement and clamp.
	OPFAILSDECRSAT         = 0x00600000,

	// Invert.
	OPFAILSINVERT          = 0x00700000,
	OPFAILSSHIFT           = 20,
	OPFAILSMASK            = 0x00f00000,

	// Zero.
	OPFAILZZERO            = 0x00000000,

	// Keep.
	OPFAILZKEEP            = 0x01000000,

	// Replace.
	OPFAILZREPLACE         = 0x02000000,

	// Increment and wrap.
	OPFAILZINCR            = 0x03000000,

	// Increment and clamp.
	OPFAILZINCRSAT         = 0x04000000,

	// Decrement and wrap.
	OPFAILZDECR            = 0x05000000,

	// Decrement and clamp.
	OPFAILZDECRSAT         = 0x06000000,

	// Invert.
	OPFAILZINVERT          = 0x07000000,
	OPFAILZSHIFT           = 24,
	OPFAILZMASK            = 0x0f000000,

	// Zero.
	OPPASSZZERO            = 0x00000000,

	// Keep.
	OPPASSZKEEP            = 0x10000000,

	// Replace.
	OPPASSZREPLACE         = 0x20000000,

	// Increment and wrap.
	OPPASSZINCR            = 0x30000000,

	// Increment and clamp.
	OPPASSZINCRSAT         = 0x40000000,

	// Decrement and wrap.
	OPPASSZDECR            = 0x50000000,

	// Decrement and clamp.
	OPPASSZDECRSAT         = 0x60000000,

	// Invert.
	OPPASSZINVERT          = 0x70000000,
	OPPASSZSHIFT           = 28,
	OPPASSZMASK            = 0xf0000000,
}

enum ClearFlags : const ushort
{
	// No clear flags.
	NONE                   = 0x0000,

	// Clear color.
	COLOR                  = 0x0001,

	// Clear depth.
	DEPTH                  = 0x0002,

	// Clear stencil.
	STENCIL                = 0x0004,

	// Discard frame buffer attachment 0.
	DISCARDCOLOR_0         = 0x0008,

	// Discard frame buffer attachment 1.
	DISCARDCOLOR_1         = 0x0010,

	// Discard frame buffer attachment 2.
	DISCARDCOLOR_2         = 0x0020,

	// Discard frame buffer attachment 3.
	DISCARDCOLOR_3         = 0x0040,

	// Discard frame buffer attachment 4.
	DISCARDCOLOR_4         = 0x0080,

	// Discard frame buffer attachment 5.
	DISCARDCOLOR_5         = 0x0100,

	// Discard frame buffer attachment 6.
	DISCARDCOLOR_6         = 0x0200,

	// Discard frame buffer attachment 7.
	DISCARDCOLOR_7         = 0x0400,

	// Discard frame buffer depth attachment.
	DISCARDDEPTH           = 0x0800,

	// Discard frame buffer stencil attachment.
	DISCARDSTENCIL         = 0x1000,
	DISCARDCOLORMASK       = 0x07f8,
	DISCARDMASK            = 0x1ff8,
}

enum DiscardFlags : const uint
{
	// Preserve everything.
	NONE                   = 0x00000000,

	// Discard texture sampler and buffer bindings.
	BINDINGS               = 0x00000001,

	// Discard index buffer.
	INDEXBUFFER            = 0x00000002,

	// Discard instance data.
	INSTANCEDATA           = 0x00000004,

	// Discard state and uniform bindings.
	STATE                  = 0x00000008,

	// Discard transform.
	TRANSFORM              = 0x00000010,

	// Discard vertex streams.
	VERTEXSTREAMS          = 0x00000020,

	// Discard all states.
	ALL                    = 0x000000ff,
}

enum DebugFlags : const uint
{
	// No debug.
	NONE                   = 0x00000000,

	// Enable wireframe for all primitives.
	WIREFRAME              = 0x00000001,

	// Enable infinitely fast hardware test. No draw calls will be submitted to driver.
	// It's useful when profiling to quickly assess bottleneck between CPU and GPU.
	IFH                    = 0x00000002,

	// Enable statistics display.
	STATS                  = 0x00000004,

	// Enable debug text display.
	TEXT                   = 0x00000008,

	// Enable profiler. This causes per-view statistics to be collected, available through `bgfx::Stats::ViewStats`. This is unrelated to the profiler functions in `bgfx::CallbackI`.
	PROFILER               = 0x00000010,
}

enum BufferFlags : const ushort
{
	// 1 8-bit value
	COMPUTEFORMAT8X1       = 0x0001,

	// 2 8-bit values
	COMPUTEFORMAT8X2       = 0x0002,

	// 4 8-bit values
	COMPUTEFORMAT8X4       = 0x0003,

	// 1 16-bit value
	COMPUTEFORMAT16X1      = 0x0004,

	// 2 16-bit values
	COMPUTEFORMAT16X2      = 0x0005,

	// 4 16-bit values
	COMPUTEFORMAT16X4      = 0x0006,

	// 1 32-bit value
	COMPUTEFORMAT32X1      = 0x0007,

	// 2 32-bit values
	COMPUTEFORMAT32X2      = 0x0008,

	// 4 32-bit values
	COMPUTEFORMAT32X4      = 0x0009,
	COMPUTEFORMATSHIFT     = 0,
	COMPUTEFORMATMASK      = 0x000f,

	// Type `int`.
	COMPUTETYPEINT         = 0x0010,

	// Type `uint`.
	COMPUTETYPEUINT        = 0x0020,

	// Type `float`.
	COMPUTETYPEFLOAT       = 0x0030,
	COMPUTETYPESHIFT       = 4,
	COMPUTETYPEMASK        = 0x0030,
	NONE                   = 0x0000,

	// Buffer will be read by shader.
	COMPUTEREAD            = 0x0100,

	// Buffer will be used for writing.
	COMPUTEWRITE           = 0x0200,

	// Buffer will be used for storing draw indirect commands.
	DRAWINDIRECT           = 0x0400,

	// Allow dynamic index/vertex buffer resize during update.
	ALLOWRESIZE            = 0x0800,

	// Index buffer contains 32-bit indices.
	INDEX32                = 0x1000,
	COMPUTEREADWRITE       = 0x0300,
}

enum TextureFlags : const ulong
{
	NONE                   = 0x0000000000000000,

	// Texture will be used for MSAA sampling.
	MSAASAMPLE             = 0x0000000800000000,

	// Render target no MSAA.
	RT                     = 0x0000001000000000,

	// Texture will be used for compute write.
	COMPUTEWRITE           = 0x0000100000000000,

	// Sample texture as sRGB.
	SRGB                   = 0x0000200000000000,

	// Texture will be used as blit destination.
	BLITDST                = 0x0000400000000000,

	// Texture will be used for read back from GPU.
	READBACK               = 0x0000800000000000,

	// Render target MSAAx2 mode.
	RTMSAAX2               = 0x0000002000000000,

	// Render target MSAAx4 mode.
	RTMSAAX4               = 0x0000003000000000,

	// Render target MSAAx8 mode.
	RTMSAAX8               = 0x0000004000000000,

	// Render target MSAAx16 mode.
	RTMSAAX16              = 0x0000005000000000,
	RTMSAASHIFT            = 36,
	RTMSAAMASK             = 0x0000007000000000,

	// Render target will be used for writing
	RTWRITEONLY            = 0x0000008000000000,
	RTSHIFT                = 36,
	RTMASK                 = 0x000000f000000000,
}

enum SamplerFlags : const uint
{
	// Wrap U mode: Mirror
	UMIRROR                = 0x00000001,

	// Wrap U mode: Clamp
	UCLAMP                 = 0x00000002,

	// Wrap U mode: Border
	UBORDER                = 0x00000003,
	USHIFT                 = 0,
	UMASK                  = 0x00000003,

	// Wrap V mode: Mirror
	VMIRROR                = 0x00000004,

	// Wrap V mode: Clamp
	VCLAMP                 = 0x00000008,

	// Wrap V mode: Border
	VBORDER                = 0x0000000c,
	VSHIFT                 = 2,
	VMASK                  = 0x0000000c,

	// Wrap W mode: Mirror
	WMIRROR                = 0x00000010,

	// Wrap W mode: Clamp
	WCLAMP                 = 0x00000020,

	// Wrap W mode: Border
	WBORDER                = 0x00000030,
	WSHIFT                 = 4,
	WMASK                  = 0x00000030,

	// Min sampling mode: Point
	MINPOINT               = 0x00000040,

	// Min sampling mode: Anisotropic
	MINANISOTROPIC         = 0x00000080,
	MINSHIFT               = 6,
	MINMASK                = 0x000000c0,

	// Mag sampling mode: Point
	MAGPOINT               = 0x00000100,

	// Mag sampling mode: Anisotropic
	MAGANISOTROPIC         = 0x00000200,
	MAGSHIFT               = 8,
	MAGMASK                = 0x00000300,

	// Mip sampling mode: Point
	MIPPOINT               = 0x00000400,
	MIPSHIFT               = 10,
	MIPMASK                = 0x00000400,

	// Compare when sampling depth texture: less.
	COMPARELESS            = 0x00010000,

	// Compare when sampling depth texture: less or equal.
	COMPARELEQUAL          = 0x00020000,

	// Compare when sampling depth texture: equal.
	COMPAREEQUAL           = 0x00030000,

	// Compare when sampling depth texture: greater or equal.
	COMPAREGEQUAL          = 0x00040000,

	// Compare when sampling depth texture: greater.
	COMPAREGREATER         = 0x00050000,

	// Compare when sampling depth texture: not equal.
	COMPARENOTEQUAL        = 0x00060000,

	// Compare when sampling depth texture: never.
	COMPARENEVER           = 0x00070000,

	// Compare when sampling depth texture: always.
	COMPAREALWAYS          = 0x00080000,
	COMPARESHIFT           = 16,
	COMPAREMASK            = 0x000f0000,
	BORDERCOLORSHIFT       = 24,
	BORDERCOLORMASK        = 0x0f000000,
	RESERVEDSHIFT          = 28,
	RESERVEDMASK           = 0xf0000000,
	NONE                   = 0x00000000,

	// Sample stencil instead of depth.
	SAMPLESTENCIL          = 0x00100000,
	POINT                  = 0x00000540,
	UVWMIRROR              = 0x00000015,
	UVWCLAMP               = 0x0000002a,
	UVWBORDER              = 0x0000003f,
	BITSMASK               = 0x000f07ff,
}

enum ResetFlags : const uint
{
	// Enable 2x MSAA.
	MSAAX2                 = 0x00000010,

	// Enable 4x MSAA.
	MSAAX4                 = 0x00000020,

	// Enable 8x MSAA.
	MSAAX8                 = 0x00000030,

	// Enable 16x MSAA.
	MSAAX16                = 0x00000040,
	MSAASHIFT              = 4,
	MSAAMASK               = 0x00000070,

	// No reset flags.
	NONE                   = 0x00000000,

	// Not supported yet.
	FULLSCREEN             = 0x00000001,

	// Enable V-Sync.
	VSYNC                  = 0x00000080,

	// Turn on/off max anisotropy.
	MAXANISOTROPY          = 0x00000100,

	// Begin screen capture.
	CAPTURE                = 0x00000200,

	// Flush rendering after submitting to GPU.
	FLUSHAFTERRENDER       = 0x00002000,

	// This flag specifies where flip occurs. Default behaviour is that flip occurs
	// before rendering new frame. This flag only has effect when `BGFX_CONFIG_MULTITHREADED=0`.
	FLIPAFTERRENDER        = 0x00004000,

	// Enable sRGB backbuffer.
	SRGBBACKBUFFER         = 0x00008000,

	// Enable HDR10 rendering.
	HDR10                  = 0x00010000,

	// Enable HiDPI rendering.
	HIDPI                  = 0x00020000,

	// Enable depth clamp.
	DEPTHCLAMP             = 0x00040000,

	// Suspend rendering.
	SUSPEND                = 0x00080000,

	// Transparent backbuffer. Availability depends on: `BGFX_CAPS_TRANSPARENT_BACKBUFFER`.
	TRANSPARENTBACKBUFFER  = 0x00100000,
	FULLSCREENSHIFT        = 0,
	FULLSCREENMASK         = 0x00000001,
	RESERVEDSHIFT          = 31,
	RESERVEDMASK           = 0x80000000,
}

enum CapsFlags : const ulong
{
	// Alpha to coverage is supported.
	ALPHATOCOVERAGE        = 0x0000000000000001,

	// Blend independent is supported.
	BLENDINDEPENDENT       = 0x0000000000000002,

	// Compute shaders are supported.
	COMPUTE                = 0x0000000000000004,

	// Conservative rasterization is supported.
	CONSERVATIVERASTER     = 0x0000000000000008,

	// Draw indirect is supported.
	DRAWINDIRECT           = 0x0000000000000010,

	// Draw indirect with indirect count is supported.
	DRAWINDIRECTCOUNT      = 0x0000000000000020,

	// Fragment depth is available in fragment shader.
	FRAGMENTDEPTH          = 0x0000000000000040,

	// Fragment ordering is available in fragment shader.
	FRAGMENTORDERING       = 0x0000000000000080,

	// Graphics debugger is present.
	GRAPHICSDEBUGGER       = 0x0000000000000100,

	// HDR10 rendering is supported.
	HDR10                  = 0x0000000000000200,

	// HiDPI rendering is supported.
	HIDPI                  = 0x0000000000000400,

	// Image Read/Write is supported.
	IMAGERW                = 0x0000000000000800,

	// 32-bit indices are supported.
	INDEX32                = 0x0000000000001000,

	// Instancing is supported.
	INSTANCING             = 0x0000000000002000,

	// Occlusion query is supported.
	OCCLUSIONQUERY         = 0x0000000000004000,

	// PrimitiveID is available in fragment shader.
	PRIMITIVEID            = 0x0000000000008000,

	// Renderer is on separate thread.
	RENDERERMULTITHREADED  = 0x0000000000010000,

	// Multiple windows are supported.
	SWAPCHAIN              = 0x0000000000020000,

	// Texture blit is supported.
	TEXTUREBLIT            = 0x0000000000040000,

	// Texture compare less equal mode is supported.
	TEXTURECOMPARELEQUAL   = 0x0000000000080000,
	TEXTURECOMPARERESERVED = 0x0000000000100000,

	// Cubemap texture array is supported.
	TEXTURECUBEARRAY       = 0x0000000000200000,

	// CPU direct access to GPU texture memory.
	TEXTUREDIRECTACCESS    = 0x0000000000400000,

	// Read-back texture is supported.
	TEXTUREREADBACK        = 0x0000000000800000,

	// 2D texture array is supported.
	TEXTURE_2DARRAY        = 0x0000000001000000,

	// 3D textures are supported.
	TEXTURE_3D             = 0x0000000002000000,

	// Transparent back buffer supported.
	TRANSPARENTBACKBUFFER  = 0x0000000004000000,

	// Vertex attribute half-float is supported.
	VERTEXATTRIBHALF       = 0x0000000008000000,

	// Vertex attribute 10_10_10_2 is supported.
	VERTEXATTRIBUINT10     = 0x0000000010000000,

	// Rendering with VertexID only is supported.
	VERTEXID               = 0x0000000020000000,

	// Viewport layer is available in vertex shader.
	VIEWPORTLAYERARRAY     = 0x0000000040000000,

	// All texture compare modes are supported.
	TEXTURECOMPAREALL      = 0x0000000000180000,
}

enum CapsFormatFlags : const uint
{
	// Texture format is not supported.
	TEXTURENONE            = 0x00000000,

	// Texture format is supported.
	TEXTURE_2D             = 0x00000001,

	// Texture as sRGB format is supported.
	TEXTURE_2DSRGB         = 0x00000002,

	// Texture format is emulated.
	TEXTURE_2DEMULATED     = 0x00000004,

	// Texture format is supported.
	TEXTURE_3D             = 0x00000008,

	// Texture as sRGB format is supported.
	TEXTURE_3DSRGB         = 0x00000010,

	// Texture format is emulated.
	TEXTURE_3DEMULATED     = 0x00000020,

	// Texture format is supported.
	TEXTURECUBE            = 0x00000040,

	// Texture as sRGB format is supported.
	TEXTURECUBESRGB        = 0x00000080,

	// Texture format is emulated.
	TEXTURECUBEEMULATED    = 0x00000100,

	// Texture format can be used from vertex shader.
	TEXTUREVERTEX          = 0x00000200,

	// Texture format can be used as image and read from.
	TEXTUREIMAGEREAD       = 0x00000400,

	// Texture format can be used as image and written to.
	TEXTUREIMAGEWRITE      = 0x00000800,

	// Texture format can be used as frame buffer.
	TEXTUREFRAMEBUFFER     = 0x00001000,

	// Texture format can be used as MSAA frame buffer.
	TEXTUREFRAMEBUFFERMSAA = 0x00002000,

	// Texture can be sampled as MSAA.
	TEXTUREMSAA            = 0x00004000,

	// Texture format supports auto-generated mips.
	TEXTUREMIPAUTOGEN      = 0x00008000,
}

enum ResolveFlags : const uint
{
	// No resolve flags.
	NONE                   = 0x00000000,

	// Auto-generate mip maps on resolve.
	AUTOGENMIPS            = 0x00000001,
}

enum PciIdFlags : const ushort
{
	// Autoselect adapter.
	NONE                   = 0x0000,

	// Software rasterizer.
	SOFTWARERASTERIZER     = 0x0001,

	// AMD adapter.
	AMD                    = 0x1002,

	// Apple adapter.
	APPLE                  = 0x106b,

	// Intel adapter.
	INTEL                  = 0x8086,

	// nVidia adapter.
	NVIDIA                 = 0x10de,

	// Microsoft adapter.
	MICROSOFT              = 0x1414,

	// ARM adapter.
	ARM                    = 0x13b5,
}

enum CubeMapFlags : const uint
{
	// Cubemap +x.
	POSITIVEX              = 0x00000000,

	// Cubemap -x.
	NEGATIVEX              = 0x00000001,

	// Cubemap +y.
	POSITIVEY              = 0x00000002,

	// Cubemap -y.
	NEGATIVEY              = 0x00000003,

	// Cubemap +z.
	POSITIVEZ              = 0x00000004,

	// Cubemap -z.
	NEGATIVEZ              = 0x00000005,
}

enum Fatal : uint
{
	DEBUGCHECK,
	INVALIDSHADER,
	UNABLETOINITIALIZE,
	UNABLETOCREATETEXTURE,
	DEVICELOST,

	COUNT
}

enum RendererType : uint
{
	// No rendering.
	NOOP,

	// AGC
	AGC,

	// Direct3D 11.0
	DIRECT3D11,

	// Direct3D 12.0
	DIRECT3D12,

	// GNM
	GNM,

	// Metal
	METAL,

	// NVN
	NVN,

	// OpenGL ES 2.0+
	OPENGLES,

	// OpenGL 2.1+
	OPENGL,

	// Vulkan
	VULKAN,

	COUNT
}

enum Access : uint
{
	// Read.
	READ,

	// Write.
	WRITE,

	// Read and write.
	READWRITE,

	COUNT
}

enum Attrib : uint
{
	// a_position
	POSITION,

	// a_normal
	NORMAL,

	// a_tangent
	TANGENT,

	// a_bitangent
	BITANGENT,

	// a_color0
	COLOR0,

	// a_color1
	COLOR1,

	// a_color2
	COLOR2,

	// a_color3
	COLOR3,

	// a_indices
	INDICES,

	// a_weight
	WEIGHT,

	// a_texcoord0
	TEXCOORD0,

	// a_texcoord1
	TEXCOORD1,

	// a_texcoord2
	TEXCOORD2,

	// a_texcoord3
	TEXCOORD3,

	// a_texcoord4
	TEXCOORD4,

	// a_texcoord5
	TEXCOORD5,

	// a_texcoord6
	TEXCOORD6,

	// a_texcoord7
	TEXCOORD7,

	COUNT
}

enum AttribType : uint
{
	// Uint8
	UINT8,

	// Uint10, availability depends on: `BGFX_CAPS_VERTEX_ATTRIB_UINT10`.
	UINT10,

	// Int16
	INT16,

	// Half, availability depends on: `BGFX_CAPS_VERTEX_ATTRIB_HALF`.
	HALF,

	// Float
	FLOAT,

	COUNT
}

enum TextureFormat : uint
{
	// DXT1 R5G6B5A1
	BC1,

	// DXT3 R5G6B5A4
	BC2,

	// DXT5 R5G6B5A8
	BC3,

	// LATC1/ATI1 R8
	BC4,

	// LATC2/ATI2 RG8
	BC5,

	// BC6H RGB16F
	BC6H,

	// BC7 RGB 4-7 bits per color channel, 0-8 bits alpha
	BC7,

	// ETC1 RGB8
	ETC1,

	// ETC2 RGB8
	ETC2,

	// ETC2 RGBA8
	ETC2A,

	// ETC2 RGB8A1
	ETC2A1,

	// PVRTC1 RGB 2BPP
	PTC12,

	// PVRTC1 RGB 4BPP
	PTC14,

	// PVRTC1 RGBA 2BPP
	PTC12A,

	// PVRTC1 RGBA 4BPP
	PTC14A,

	// PVRTC2 RGBA 2BPP
	PTC22,

	// PVRTC2 RGBA 4BPP
	PTC24,

	// ATC RGB 4BPP
	ATC,

	// ATCE RGBA 8 BPP explicit alpha
	ATCE,

	// ATCI RGBA 8 BPP interpolated alpha
	ATCI,

	// ASTC 4x4 8.0 BPP
	ASTC4X4,

	// ASTC 5x4 6.40 BPP
	ASTC5X4,

	// ASTC 5x5 5.12 BPP
	ASTC5X5,

	// ASTC 6x5 4.27 BPP
	ASTC6X5,

	// ASTC 6x6 3.56 BPP
	ASTC6X6,

	// ASTC 8x5 3.20 BPP
	ASTC8X5,

	// ASTC 8x6 2.67 BPP
	ASTC8X6,

	// ASTC 8x8 2.00 BPP
	ASTC8X8,

	// ASTC 10x5 2.56 BPP
	ASTC10X5,

	// ASTC 10x6 2.13 BPP
	ASTC10X6,

	// ASTC 10x8 1.60 BPP
	ASTC10X8,

	// ASTC 10x10 1.28 BPP
	ASTC10X10,

	// ASTC 12x10 1.07 BPP
	ASTC12X10,

	// ASTC 12x12 0.89 BPP
	ASTC12X12,

	// Compressed formats above.
	UNKNOWN,
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
	B5G6R5,
	R5G6B5,
	BGRA4,
	RGBA4,
	BGR5A1,
	RGB5A1,
	RGB10A2,
	RG11B10F,

	// Depth formats below.
	UNKNOWNDEPTH,
	D16,
	D24,
	D24S8,
	D32,
	D16F,
	D24F,
	D32F,
	D0S8,

	COUNT
}

enum UniformType : uint
{
	// Sampler.
	SAMPLER,

	// Reserved, do not use.
	END,

	// 4 floats vector.
	VEC4,

	// 3x3 matrix.
	MAT3,

	// 4x4 matrix.
	MAT4,

	COUNT
}

enum BackbufferRatio : uint
{
	// Equal to backbuffer.
	EQUAL,

	// One half size of backbuffer.
	HALF,

	// One quarter size of backbuffer.
	QUARTER,

	// One eighth size of backbuffer.
	EIGHTH,

	// One sixteenth size of backbuffer.
	SIXTEENTH,

	// Double size of backbuffer.
	DOUBLE,

	COUNT
}

enum OcclusionQueryResult : uint
{
	// Query failed test.
	INVISIBLE,

	// Query passed test.
	VISIBLE,

	// Query result is not available yet.
	NORESULT,

	COUNT
}

enum Topology : uint
{
	// Triangle list.
	TRILIST,

	// Triangle strip.
	TRISTRIP,

	// Line list.
	LINELIST,

	// Line strip.
	LINESTRIP,

	// Point list.
	POINTLIST,

	COUNT
}

enum TopologyConvert : uint
{
	// Flip winding order of triangle list.
	TRILISTFLIPWINDING,

	// Flip winding order of triangle strip.
	TRISTRIPFLIPWINDING,

	// Convert triangle list to line list.
	TRILISTTOLINELIST,

	// Convert triangle strip to triangle list.
	TRISTRIPTOTRILIST,

	// Convert line strip to line list.
	LINESTRIPTOLINELIST,

	COUNT
}

enum TopologySort : uint
{
	DIRECTIONFRONTTOBACKMIN,
	DIRECTIONFRONTTOBACKAVG,
	DIRECTIONFRONTTOBACKMAX,
	DIRECTIONBACKTOFRONTMIN,
	DIRECTIONBACKTOFRONTAVG,
	DIRECTIONBACKTOFRONTMAX,
	DISTANCEFRONTTOBACKMIN,
	DISTANCEFRONTTOBACKAVG,
	DISTANCEFRONTTOBACKMAX,
	DISTANCEBACKTOFRONTMIN,
	DISTANCEBACKTOFRONTAVG,
	DISTANCEBACKTOFRONTMAX,

	COUNT
}

enum ViewMode : uint
{
	// Default sort order.
	DEFAULT,

	// Sort in the same order in which submit calls were called.
	SEQUENTIAL,

	// Sort draw call depth in ascending order.
	DEPTHASCENDING,

	// Sort draw call depth in descending order.
	DEPTHDESCENDING,

	COUNT
}

enum NativeWindowHandleType : uint
{
	// Platform default handle type (X11 on Linux).
	DEFAULT,

	// Wayland.
	WAYLAND,

	COUNT
}

enum RenderFrame : uint
{
	// Renderer context is not created yet.
	NOCONTEXT,

	// Renderer context is created and rendering.
	RENDER,

	// Renderer context wait for main thread signal timed out without rendering.
	TIMEOUT,

	// Renderer context is getting destroyed.
	EXITING,

	COUNT
}

// GPU info.
struct CapsGPU
{
	// Vendor PCI id. See `BGFX_PCI_ID_*`.
	ushort vendorId;
	// Device id.
	ushort deviceId;
}

// Renderer runtime limits.
struct CapsLimits
{
	// Maximum number of draw calls.
	uint maxDrawCalls;
	// Maximum number of blit calls.
	uint maxBlits;
	// Maximum texture size.
	uint maxTextureSize;
	// Maximum texture layers.
	uint maxTextureLayers;
	// Maximum number of views.
	uint maxViews;
	// Maximum number of frame buffer handles.
	uint maxFrameBuffers;
	// Maximum number of frame buffer attachments.
	uint maxFBAttachments;
	// Maximum number of program handles.
	uint maxPrograms;
	// Maximum number of shader handles.
	uint maxShaders;
	// Maximum number of texture handles.
	uint maxTextures;
	// Maximum number of texture samplers.
	uint maxTextureSamplers;
	// Maximum number of compute bindings.
	uint maxComputeBindings;
	// Maximum number of vertex format layouts.
	uint maxVertexLayouts;
	// Maximum number of vertex streams.
	uint maxVertexStreams;
	// Maximum number of index buffer handles.
	uint maxIndexBuffers;
	// Maximum number of vertex buffer handles.
	uint maxVertexBuffers;
	// Maximum number of dynamic index buffer handles.
	uint maxDynamicIndexBuffers;
	// Maximum number of dynamic vertex buffer handles.
	uint maxDynamicVertexBuffers;
	// Maximum number of uniform handles.
	uint maxUniforms;
	// Maximum number of occlusion query handles.
	uint maxOcclusionQueries;
	// Maximum number of encoder threads.
	uint maxEncoders;
	// Minimum resource command buffer size.
	uint minResourceCbSize;
	// Maximum transient vertex buffer size.
	uint transientVbSize;
	// Maximum transient index buffer size.
	uint transientIbSize;
}

// Renderer capabilities.
struct Caps
{
	// Renderer backend type. See: `bgfx::RendererType`
	RendererType rendererType;
	// Supported functionality.
	//   @attention See `BGFX_CAPS_*` flags at https://bkaradzic.github.io/bgfx/bgfx.html#available-caps
	ulong supported;
	// Selected GPU vendor PCI id.
	ushort vendorId;
	// Selected GPU device id.
	ushort deviceId;
	// True when NDC depth is in [-1, 1] range, otherwise its [0, 1].
	bool homogeneousDepth;
	// True when NDC origin is at bottom left.
	bool originBottomLeft;
	// Number of enumerated GPUs.
	char numGPUs;
	// Enumerated GPUs.
	uint[4] gpu;
	// Renderer runtime limits.
	CapsLimits limits;
	// Supported texture format capabilities flags:
	//   - `BGFX_CAPS_FORMAT_TEXTURE_NONE` - Texture format is not supported.
	//   - `BGFX_CAPS_FORMAT_TEXTURE_2D` - Texture format is supported.
	//   - `BGFX_CAPS_FORMAT_TEXTURE_2D_SRGB` - Texture as sRGB format is supported.
	//   - `BGFX_CAPS_FORMAT_TEXTURE_2D_EMULATED` - Texture format is emulated.
	//   - `BGFX_CAPS_FORMAT_TEXTURE_3D` - Texture format is supported.
	//   - `BGFX_CAPS_FORMAT_TEXTURE_3D_SRGB` - Texture as sRGB format is supported.
	//   - `BGFX_CAPS_FORMAT_TEXTURE_3D_EMULATED` - Texture format is emulated.
	//   - `BGFX_CAPS_FORMAT_TEXTURE_CUBE` - Texture format is supported.
	//   - `BGFX_CAPS_FORMAT_TEXTURE_CUBE_SRGB` - Texture as sRGB format is supported.
	//   - `BGFX_CAPS_FORMAT_TEXTURE_CUBE_EMULATED` - Texture format is emulated.
	//   - `BGFX_CAPS_FORMAT_TEXTURE_VERTEX` - Texture format can be used from vertex shader.
	//   - `BGFX_CAPS_FORMAT_TEXTURE_IMAGE_READ` - Texture format can be used as image
	//     and read from.
	//   - `BGFX_CAPS_FORMAT_TEXTURE_IMAGE_WRITE` - Texture format can be used as image
	//     and written to.
	//   - `BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER` - Texture format can be used as frame
	//     buffer.
	//   - `BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA` - Texture format can be used as MSAA
	//     frame buffer.
	//   - `BGFX_CAPS_FORMAT_TEXTURE_MSAA` - Texture can be sampled as MSAA.
	//   - `BGFX_CAPS_FORMAT_TEXTURE_MIP_AUTOGEN` - Texture format supports auto-generated
	//     mips.
	ushort[96] formats;
}

// Internal data.
struct InternalData
{
	// Renderer capabilities.
	Caps* caps;
	// GL context, or D3D device.
	void* context;
}

// Platform data.
struct PlatformData
{
	// Native display type (*nix specific).
	void* ndt;
	// Native window handle. If `NULL`, bgfx will create a headless
	// context/device, provided the rendering API supports it.
	void* nwh;
	// GL context, D3D device, or Vulkan device. If `NULL`, bgfx
	// will create context/device.
	void* context;
	// GL back-buffer, or D3D render target view. If `NULL` bgfx will
	// create back-buffer color surface.
	void* backBuffer;
	// Backbuffer depth/stencil. If `NULL`, bgfx will create a back-buffer
	// depth/stencil surface.
	void* backBufferDS;
	// Handle type. Needed for platforms having more than one option.
	NativeWindowHandleType type;
}

// Backbuffer resolution and reset parameters.
struct Resolution
{
	// Backbuffer format.
	TextureFormat format;
	// Backbuffer width.
	uint width;
	// Backbuffer height.
	uint height;
	// Reset parameters.
	uint reset;
	// Number of back buffers.
	char numBackBuffers;
	// Maximum frame latency.
	char maxFrameLatency;
	// Scale factor for debug text.
	char debugTextScale;
}

// Configurable runtime limits parameters.
struct InitLimits
{
	// Maximum number of encoder threads.
	ushort maxEncoders;
	// Minimum resource command buffer size.
	uint minResourceCbSize;
	// Maximum transient vertex buffer size.
	uint transientVbSize;
	// Maximum transient index buffer size.
	uint transientIbSize;
}

// Initialization parameters used by `bgfx::init`.
struct Init
{
	// Select rendering backend. When set to RendererType::Count
	// a default rendering backend will be selected appropriate to the platform.
	// See: `bgfx::RendererType`
	RendererType type;
	// Vendor PCI ID. If set to `BGFX_PCI_ID_NONE`, discrete and integrated
	// GPUs will be prioritised.
	//   - `BGFX_PCI_ID_NONE` - Autoselect adapter.
	//   - `BGFX_PCI_ID_SOFTWARE_RASTERIZER` - Software rasterizer.
	//   - `BGFX_PCI_ID_AMD` - AMD adapter.
	//   - `BGFX_PCI_ID_APPLE` - Apple adapter.
	//   - `BGFX_PCI_ID_INTEL` - Intel adapter.
	//   - `BGFX_PCI_ID_NVIDIA` - NVIDIA adapter.
	//   - `BGFX_PCI_ID_MICROSOFT` - Microsoft adapter.
	ushort vendorId;
	// Device ID. If set to 0 it will select first device, or device with
	// matching ID.
	ushort deviceId;
	// Capabilities initialization mask (default: UINT64_MAX).
	ulong capabilities;
	// Enable device for debugging.
	bool debug;
	// Enable device for profiling.
	bool profile;
	// Platform data.
	PlatformData platformData;
	// Backbuffer resolution and reset parameters. See: `bgfx::Resolution`.
	Resolution resolution;
	// Configurable runtime limits parameters.
	InitLimits limits;
	// Provide application specific callback interface.
	// See: `bgfx::CallbackI`
	void* callback;
	// Custom allocator. When a custom allocator is not
	// specified, bgfx uses the CRT allocator. Bgfx assumes
	// custom allocator is thread safe.
	void* allocator;
}

// Memory must be obtained by calling `bgfx::alloc`, `bgfx::copy`, or `bgfx::makeRef`.
// @attention It is illegal to create this structure on stack and pass it to any bgfx API.
struct Memory
{
	// Pointer to data.
	char* data;
	// Data size.
	uint size;
}

// Transient index buffer.
struct TransientIndexBuffer
{
	// Pointer to data.
	char* data;
	// Data size.
	uint size;
	// First index.
	uint startIndex;
	// Index buffer handle.
	IndexBufferHandle handle;
	// Index buffer format is 16-bits if true, otherwise it is 32-bit.
	bool isIndex16;
}

// Transient vertex buffer.
struct TransientVertexBuffer
{
	// Pointer to data.
	char* data;
	// Data size.
	uint size;
	// First vertex.
	uint startVertex;
	// Vertex stride.
	ushort stride;
	// Vertex buffer handle.
	VertexBufferHandle handle;
	// Vertex layout handle.
	VertexLayoutHandle layoutHandle;
}

// Instance data buffer info.
struct InstanceDataBuffer
{
	// Pointer to data.
	char* data;
	// Data size.
	uint size;
	// Offset in vertex buffer.
	uint offset;
	// Number of instances.
	uint num;
	// Vertex buffer stride.
	ushort stride;
	// Vertex buffer object handle.
	VertexBufferHandle handle;
}

// Texture info.
struct TextureInfo
{
	// Texture format.
	TextureFormat format;
	// Total amount of bytes required to store texture.
	uint storageSize;
	// Texture width.
	ushort width;
	// Texture height.
	ushort height;
	// Texture depth.
	ushort depth;
	// Number of layers in texture array.
	ushort numLayers;
	// Number of MIP maps.
	char numMips;
	// Format bits per pixel.
	char bitsPerPixel;
	// Texture is cubemap.
	bool cubeMap;
}

// Uniform info.
struct UniformInfo
{
	// Uniform name.
	char[256] name;
	// Uniform type.
	UniformType type;
	// Number of elements in array.
	ushort num;
}

// Frame buffer texture attachment info.
struct Attachment
{
	// Attachment access. See `Access::Enum`.
	Access access;
	// Render target texture handle.
	TextureHandle handle;
	// Mip level.
	ushort mip;
	// Cubemap side or depth layer/slice to use.
	ushort layer;
	// Number of texture layer/slice(s) in array to use.
	ushort numLayers;
	// Resolve flags. See: `BGFX_RESOLVE_*`
	char resolve;
}

// Transform data.
struct Transform
{
	// Pointer to first 4x4 matrix.
	float* data;
	// Number of matrices.
	ushort num;
}

// View stats.
struct ViewStats
{
	// View name.
	char[256] name;
	// View id.
	ushort view;
	// CPU (submit) begin time.
	long cpuTimeBegin;
	// CPU (submit) end time.
	long cpuTimeEnd;
	// GPU begin time.
	long gpuTimeBegin;
	// GPU end time.
	long gpuTimeEnd;
	// Frame which generated gpuTimeBegin, gpuTimeEnd.
	uint gpuFrameNum;
}

// Encoder stats.
struct EncoderStats
{
	// Encoder thread CPU submit begin time.
	long cpuTimeBegin;
	// Encoder thread CPU submit end time.
	long cpuTimeEnd;
}

// Renderer statistics data.
// @remarks All time values are high-resolution timestamps, while
// time frequencies define timestamps-per-second for that hardware.
struct Stats
{
	// CPU time between two `bgfx::frame` calls.
	long cpuTimeFrame;
	// Render thread CPU submit begin time.
	long cpuTimeBegin;
	// Render thread CPU submit end time.
	long cpuTimeEnd;
	// CPU timer frequency. Timestamps-per-second
	long cpuTimerFreq;
	// GPU frame begin time.
	long gpuTimeBegin;
	// GPU frame end time.
	long gpuTimeEnd;
	// GPU timer frequency.
	long gpuTimerFreq;
	// Time spent waiting for render backend thread to finish issuing draw commands to underlying graphics API.
	long waitRender;
	// Time spent waiting for submit thread to advance to next frame.
	long waitSubmit;
	// Number of draw calls submitted.
	uint numDraw;
	// Number of compute calls submitted.
	uint numCompute;
	// Number of blit calls submitted.
	uint numBlit;
	// GPU driver latency.
	uint maxGpuLatency;
	// Frame which generated gpuTimeBegin, gpuTimeEnd.
	uint gpuFrameNum;
	// Number of used dynamic index buffers.
	ushort numDynamicIndexBuffers;
	// Number of used dynamic vertex buffers.
	ushort numDynamicVertexBuffers;
	// Number of used frame buffers.
	ushort numFrameBuffers;
	// Number of used index buffers.
	ushort numIndexBuffers;
	// Number of used occlusion queries.
	ushort numOcclusionQueries;
	// Number of used programs.
	ushort numPrograms;
	// Number of used shaders.
	ushort numShaders;
	// Number of used textures.
	ushort numTextures;
	// Number of used uniforms.
	ushort numUniforms;
	// Number of used vertex buffers.
	ushort numVertexBuffers;
	// Number of used vertex layouts.
	ushort numVertexLayouts;
	// Estimate of texture memory used.
	long textureMemoryUsed;
	// Estimate of render target memory used.
	long rtMemoryUsed;
	// Amount of transient vertex buffer used.
	int transientVbUsed;
	// Amount of transient index buffer used.
	int transientIbUsed;
	// Number of primitives rendered.
	uint[5] numPrims;
	// Maximum available GPU memory for application.
	long gpuMemoryMax;
	// Amount of GPU memory used by the application.
	long gpuMemoryUsed;
	// Backbuffer width in pixels.
	ushort width;
	// Backbuffer height in pixels.
	ushort height;
	// Debug text width in characters.
	ushort textWidth;
	// Debug text height in characters.
	ushort textHeight;
	// Number of view stats.
	ushort numViews;
	// Array of View stats.
	ViewStats* viewStats;
	// Number of encoders used during frame.
	char numEncoders;
	// Array of encoder stats.
	EncoderStats* encoderStats;
}

// Vertex layout.
struct VertexLayout
{
	// Hash.
	uint hash;
	// Stride.
	ushort stride;
	// Attribute offsets.
	ushort[18] offset;
	// Used attributes.
	ushort[18] attributes;
}

// Encoders are used for submitting draw calls from multiple threads. Only one encoder
// per thread should be used. Use `bgfx::begin()` to obtain an encoder for a thread.
alias Encoder = any;

struct DynamicIndexBufferHandle {
    ushort idx;
}

struct DynamicVertexBufferHandle {
    ushort idx;
}

struct FrameBufferHandle {
    ushort idx;
}

struct IndexBufferHandle {
    ushort idx;
}

struct IndirectBufferHandle {
    ushort idx;
}

struct OcclusionQueryHandle {
    ushort idx;
}

struct ProgramHandle {
    ushort idx;
}

struct ShaderHandle {
    ushort idx;
}

struct TextureHandle {
    ushort idx;
}

struct UniformHandle {
    ushort idx;
}

struct VertexBufferHandle {
    ushort idx;
}

struct VertexLayoutHandle {
    ushort idx;
}

// Init attachment.
// _handle : `Render target texture handle.`
// _access : `Access. See `Access::Enum`.`
// _layer : `Cubemap side or depth layer/slice to use.`
// _numLayers : `Number of texture layer/slice(s) in array to use.`
// _mip : `Mip level.`
// _resolve : `Resolve flags. See: `BGFX_RESOLVE_*``
extern fn void attachment_init(Attachment* _this, TextureHandle _handle, Access _access, ushort _layer, ushort _numLayers, ushort _mip, char _resolve) @extern("bgfx_attachment_init");

// Start VertexLayout.
// _rendererType : `Renderer backend type. See: `bgfx::RendererType``
extern fn VertexLayout* vertex_layout_begin(VertexLayout* _this, RendererType _rendererType) @extern("bgfx_vertex_layout_begin");

// Add attribute to VertexLayout.
// @remarks Must be called between begin/end.
// _attrib : `Attribute semantics. See: `bgfx::Attrib``
// _num : `Number of elements 1, 2, 3 or 4.`
// _type : `Element type.`
// _normalized : `When using fixed point AttribType (f.e. Uint8) value will be normalized for vertex shader usage. When normalized is set to true, AttribType::Uint8 value in range 0-255 will be in range 0.0-1.0 in vertex shader.`
// _asInt : `Packaging rule for vertexPack, vertexUnpack, and vertexConvert for AttribType::Uint8 and AttribType::Int16. Unpacking code must be implemented inside vertex shader.`
extern fn VertexLayout* vertex_layout_add(VertexLayout* _this, Attrib _attrib, char _num, AttribType _type, bool _normalized, bool _asInt) @extern("bgfx_vertex_layout_add");

// Decode attribute.
// _attrib : `Attribute semantics. See: `bgfx::Attrib``
// _num : `Number of elements.`
// _type : `Element type.`
// _normalized : `Attribute is normalized.`
// _asInt : `Attribute is packed as int.`
extern fn void vertex_layout_decode(VertexLayout* _this, Attrib _attrib, char * _num, AttribType* _type, bool* _normalized, bool* _asInt) @extern("bgfx_vertex_layout_decode");

// Skip `_num` bytes in vertex stream.
// _num : `Number of bytes to skip.`
extern fn VertexLayout* vertex_layout_skip(VertexLayout* _this, char _num) @extern("bgfx_vertex_layout_skip");

// End VertexLayout.
extern fn void vertex_layout_end(VertexLayout* _this) @extern("bgfx_vertex_layout_end");

// Pack vertex attribute into vertex stream format.
// _input : `Value to be packed into vertex stream.`
// _inputNormalized : ``true` if input value is already normalized.`
// _attr : `Attribute to pack.`
// _layout : `Vertex stream layout.`
// _data : `Destination vertex stream where data will be packed.`
// _index : `Vertex index that will be modified.`
extern fn void vertex_pack(float _input, bool _inputNormalized, Attrib _attr, VertexLayout* _layout, void* _data, uint _index) @extern("bgfx_vertex_pack");

// Unpack vertex attribute from vertex stream format.
// _output : `Result of unpacking.`
// _attr : `Attribute to unpack.`
// _layout : `Vertex stream layout.`
// _data : `Source vertex stream from where data will be unpacked.`
// _index : `Vertex index that will be unpacked.`
extern fn void vertex_unpack(float _output, Attrib _attr, VertexLayout* _layout, void* _data, uint _index) @extern("bgfx_vertex_unpack");

// Converts vertex stream data from one vertex stream format to another.
// _dstLayout : `Destination vertex stream layout.`
// _dstData : `Destination vertex stream.`
// _srcLayout : `Source vertex stream layout.`
// _srcData : `Source vertex stream data.`
// _num : `Number of vertices to convert from source to destination.`
extern fn void vertex_convert(VertexLayout* _dstLayout, void* _dstData, VertexLayout* _srcLayout, void* _srcData, uint _num) @extern("bgfx_vertex_convert");

// Weld vertices.
// _output : `Welded vertices remapping table. The size of buffer must be the same as number of vertices.`
// _layout : `Vertex stream layout.`
// _data : `Vertex stream.`
// _num : `Number of vertices in vertex stream.`
// _index32 : `Set to `true` if input indices are 32-bit.`
// _epsilon : `Error tolerance for vertex position comparison.`
extern fn uint weld_vertices(void* _output, VertexLayout* _layout, void* _data, uint _num, bool _index32, float _epsilon) @extern("bgfx_weld_vertices");

// Convert index buffer for use with different primitive topologies.
// _conversion : `Conversion type, see `TopologyConvert::Enum`.`
// _dst : `Destination index buffer. If this argument is NULL function will return number of indices after conversion.`
// _dstSize : `Destination index buffer in bytes. It must be large enough to contain output indices. If destination size is insufficient index buffer will be truncated.`
// _indices : `Source indices.`
// _numIndices : `Number of input indices.`
// _index32 : `Set to `true` if input indices are 32-bit.`
extern fn uint topology_convert(TopologyConvert _conversion, void* _dst, uint _dstSize, void* _indices, uint _numIndices, bool _index32) @extern("bgfx_topology_convert");

// Sort indices.
// _sort : `Sort order, see `TopologySort::Enum`.`
// _dst : `Destination index buffer.`
// _dstSize : `Destination index buffer in bytes. It must be large enough to contain output indices. If destination size is insufficient index buffer will be truncated.`
// _dir : `Direction (vector must be normalized).`
// _pos : `Position.`
// _vertices : `Pointer to first vertex represented as float x, y, z. Must contain at least number of vertices referencende by index buffer.`
// _stride : `Vertex stride.`
// _indices : `Source indices.`
// _numIndices : `Number of input indices.`
// _index32 : `Set to `true` if input indices are 32-bit.`
extern fn void topology_sort_tri_list(TopologySort _sort, void* _dst, uint _dstSize, float _dir, float _pos, void* _vertices, uint _stride, void* _indices, uint _numIndices, bool _index32) @extern("bgfx_topology_sort_tri_list");

// Returns supported backend API renderers.
// _max : `Maximum number of elements in _enum array.`
// _enum : `Array where supported renderers will be written.`
extern fn char get_supported_renderers(char _max, RendererType* _enum) @extern("bgfx_get_supported_renderers");

// Returns name of renderer.
// _type : `Renderer backend type. See: `bgfx::RendererType``
extern fn ZString get_renderer_name(RendererType _type) @extern("bgfx_get_renderer_name");

// Fill bgfx::Init struct with default values, before using it to initialize the library.
// _init : `Pointer to structure to be initialized. See: `bgfx::Init` for more info.`
extern fn void init_ctor(Init* _init) @extern("bgfx_init_ctor");

// Initialize the bgfx library.
// _init : `Initialization parameters. See: `bgfx::Init` for more info.`
extern fn bool init(Init* _init) @extern("bgfx_init");

// Shutdown bgfx library.
extern fn void shutdown() @extern("bgfx_shutdown");

// Reset graphic settings and back-buffer size.
// @attention This call doesn’t change the window size, it just resizes
//   the back-buffer. Your windowing code controls the window size.
// _width : `Back-buffer width.`
// _height : `Back-buffer height.`
// _flags : `See: `BGFX_RESET_*` for more info.   - `BGFX_RESET_NONE` - No reset flags.   - `BGFX_RESET_FULLSCREEN` - Not supported yet.   - `BGFX_RESET_MSAA_X[2/4/8/16]` - Enable 2, 4, 8 or 16 x MSAA.   - `BGFX_RESET_VSYNC` - Enable V-Sync.   - `BGFX_RESET_MAXANISOTROPY` - Turn on/off max anisotropy.   - `BGFX_RESET_CAPTURE` - Begin screen capture.   - `BGFX_RESET_FLUSH_AFTER_RENDER` - Flush rendering after submitting to GPU.   - `BGFX_RESET_FLIP_AFTER_RENDER` - This flag  specifies where flip     occurs. Default behaviour is that flip occurs before rendering new     frame. This flag only has effect when `BGFX_CONFIG_MULTITHREADED=0`.   - `BGFX_RESET_SRGB_BACKBUFFER` - Enable sRGB back-buffer.`
// _format : `Texture format. See: `TextureFormat::Enum`.`
extern fn void reset(uint _width, uint _height, uint _flags, TextureFormat _format) @extern("bgfx_reset");

// Advance to next frame. When using multithreaded renderer, this call
// just swaps internal buffers, kicks render thread, and returns. In
// singlethreaded renderer this call does frame rendering.
// _capture : `Capture frame with graphics debugger.`
extern fn uint frame(bool _capture) @extern("bgfx_frame");

// Returns current renderer backend API type.
// @remarks
//   Library must be initialized.
extern fn RendererType get_renderer_type() @extern("bgfx_get_renderer_type");

// Returns renderer capabilities.
// @remarks
//   Library must be initialized.
extern fn Caps* get_caps() @extern("bgfx_get_caps");

// Returns performance counters.
// @attention Pointer returned is valid until `bgfx::frame` is called.
extern fn Stats* get_stats() @extern("bgfx_get_stats");

// Allocate buffer to pass to bgfx calls. Data will be freed inside bgfx.
// _size : `Size to allocate.`
extern fn Memory* alloc(uint _size) @extern("bgfx_alloc");

// Allocate buffer and copy data into it. Data will be freed inside bgfx.
// _data : `Pointer to data to be copied.`
// _size : `Size of data to be copied.`
extern fn Memory* copy(void* _data, uint _size) @extern("bgfx_copy");

// Make reference to data to pass to bgfx. Unlike `bgfx::alloc`, this call
// doesn't allocate memory for data. It just copies the _data pointer. You
// can pass `ReleaseFn` function pointer to release this memory after it's
// consumed, otherwise you must make sure _data is available for at least 2
// `bgfx::frame` calls. `ReleaseFn` function must be able to be called
// from any thread.
// @attention Data passed must be available for at least 2 `bgfx::frame` calls.
// _data : `Pointer to data.`
// _size : `Size of data.`
extern fn Memory* make_ref(void* _data, uint _size) @extern("bgfx_make_ref");

// Make reference to data to pass to bgfx. Unlike `bgfx::alloc`, this call
// doesn't allocate memory for data. It just copies the _data pointer. You
// can pass `ReleaseFn` function pointer to release this memory after it's
// consumed, otherwise you must make sure _data is available for at least 2
// `bgfx::frame` calls. `ReleaseFn` function must be able to be called
// from any thread.
// @attention Data passed must be available for at least 2 `bgfx::frame` calls.
// _data : `Pointer to data.`
// _size : `Size of data.`
// _releaseFn : `Callback function to release memory after use.`
// _userData : `User data to be passed to callback function.`
extern fn Memory* make_ref_release(void* _data, uint _size, void* _releaseFn, void* _userData) @extern("bgfx_make_ref_release");

// Set debug flags.
// _debug : `Available flags:   - `BGFX_DEBUG_IFH` - Infinitely fast hardware. When this flag is set     all rendering calls will be skipped. This is useful when profiling     to quickly assess potential bottlenecks between CPU and GPU.   - `BGFX_DEBUG_PROFILER` - Enable profiler.   - `BGFX_DEBUG_STATS` - Display internal statistics.   - `BGFX_DEBUG_TEXT` - Display debug text.   - `BGFX_DEBUG_WIREFRAME` - Wireframe rendering. All rendering     primitives will be rendered as lines.`
extern fn void set_debug(uint _debug) @extern("bgfx_set_debug");

// Clear internal debug text buffer.
// _attr : `Background color.`
// _small : `Default 8x16 or 8x8 font.`
extern fn void dbg_text_clear(char _attr, bool _small) @extern("bgfx_dbg_text_clear");

// Print formatted data to internal debug text character-buffer (VGA-compatible text mode).
// _x : `Position x from the left corner of the window.`
// _y : `Position y from the top corner of the window.`
// _attr : `Color palette. Where top 4-bits represent index of background, and bottom 4-bits represent foreground color from standard VGA text palette (ANSI escape codes).`
// _format : ``printf` style format.`
extern fn void dbg_text_printf(ushort _x, ushort _y, char _attr, ZString _format, ... ) @extern("bgfx_dbg_text_printf");

// Print formatted data from variable argument list to internal debug text character-buffer (VGA-compatible text mode).
// _x : `Position x from the left corner of the window.`
// _y : `Position y from the top corner of the window.`
// _attr : `Color palette. Where top 4-bits represent index of background, and bottom 4-bits represent foreground color from standard VGA text palette (ANSI escape codes).`
// _format : ``printf` style format.`
// _argList : `Variable arguments list for format string.`
extern fn void dbg_text_vprintf(ushort _x, ushort _y, char _attr, ZString _format, void* _argList) @extern("bgfx_dbg_text_vprintf");

// Draw image into internal debug text buffer.
// _x : `Position x from the left corner of the window.`
// _y : `Position y from the top corner of the window.`
// _width : `Image width.`
// _height : `Image height.`
// _data : `Raw image data (character/attribute raw encoding).`
// _pitch : `Image pitch in bytes.`
extern fn void dbg_text_image(ushort _x, ushort _y, ushort _width, ushort _height, void* _data, ushort _pitch) @extern("bgfx_dbg_text_image");

// Create static index buffer.
// _mem : `Index buffer data.`
// _flags : `Buffer creation flags.   - `BGFX_BUFFER_NONE` - No flags.   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of       data is passed. If this flag is not specified, and more data is passed on update, the buffer       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic       buffers.   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on       index buffers.`
extern fn IndexBufferHandle create_index_buffer(Memory* _mem, ushort _flags) @extern("bgfx_create_index_buffer");

// Set static index buffer debug name.
// _handle : `Static index buffer handle.`
// _name : `Static index buffer name.`
// _len : `Static index buffer name length (if length is INT32_MAX, it's expected that _name is zero terminated string.`
extern fn void set_index_buffer_name(IndexBufferHandle _handle, ZString _name, int _len) @extern("bgfx_set_index_buffer_name");

// Destroy static index buffer.
// _handle : `Static index buffer handle.`
extern fn void destroy_index_buffer(IndexBufferHandle _handle) @extern("bgfx_destroy_index_buffer");

// Create vertex layout.
// _layout : `Vertex layout.`
extern fn VertexLayoutHandle create_vertex_layout(VertexLayout* _layout) @extern("bgfx_create_vertex_layout");

// Destroy vertex layout.
// _layoutHandle : `Vertex layout handle.`
extern fn void destroy_vertex_layout(VertexLayoutHandle _layoutHandle) @extern("bgfx_destroy_vertex_layout");

// Create static vertex buffer.
// _mem : `Vertex buffer data.`
// _layout : `Vertex layout.`
// _flags : `Buffer creation flags.  - `BGFX_BUFFER_NONE` - No flags.  - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.  - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer      is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.  - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.  - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of      data is passed. If this flag is not specified, and more data is passed on update, the buffer      will be trimmed to fit the existing buffer size. This flag has effect only on dynamic buffers.  - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on index buffers.`
extern fn VertexBufferHandle create_vertex_buffer(Memory* _mem, VertexLayout* _layout, ushort _flags) @extern("bgfx_create_vertex_buffer");

// Set static vertex buffer debug name.
// _handle : `Static vertex buffer handle.`
// _name : `Static vertex buffer name.`
// _len : `Static vertex buffer name length (if length is INT32_MAX, it's expected that _name is zero terminated string.`
extern fn void set_vertex_buffer_name(VertexBufferHandle _handle, ZString _name, int _len) @extern("bgfx_set_vertex_buffer_name");

// Destroy static vertex buffer.
// _handle : `Static vertex buffer handle.`
extern fn void destroy_vertex_buffer(VertexBufferHandle _handle) @extern("bgfx_destroy_vertex_buffer");

// Create empty dynamic index buffer.
// _num : `Number of indices.`
// _flags : `Buffer creation flags.   - `BGFX_BUFFER_NONE` - No flags.   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of       data is passed. If this flag is not specified, and more data is passed on update, the buffer       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic       buffers.   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on       index buffers.`
extern fn DynamicIndexBufferHandle create_dynamic_index_buffer(uint _num, ushort _flags) @extern("bgfx_create_dynamic_index_buffer");

// Create a dynamic index buffer and initialize it.
// _mem : `Index buffer data.`
// _flags : `Buffer creation flags.   - `BGFX_BUFFER_NONE` - No flags.   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of       data is passed. If this flag is not specified, and more data is passed on update, the buffer       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic       buffers.   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on       index buffers.`
extern fn DynamicIndexBufferHandle create_dynamic_index_buffer_mem(Memory* _mem, ushort _flags) @extern("bgfx_create_dynamic_index_buffer_mem");

// Update dynamic index buffer.
// _handle : `Dynamic index buffer handle.`
// _startIndex : `Start index.`
// _mem : `Index buffer data.`
extern fn void update_dynamic_index_buffer(DynamicIndexBufferHandle _handle, uint _startIndex, Memory* _mem) @extern("bgfx_update_dynamic_index_buffer");

// Destroy dynamic index buffer.
// _handle : `Dynamic index buffer handle.`
extern fn void destroy_dynamic_index_buffer(DynamicIndexBufferHandle _handle) @extern("bgfx_destroy_dynamic_index_buffer");

// Create empty dynamic vertex buffer.
// _num : `Number of vertices.`
// _layout : `Vertex layout.`
// _flags : `Buffer creation flags.   - `BGFX_BUFFER_NONE` - No flags.   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of       data is passed. If this flag is not specified, and more data is passed on update, the buffer       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic       buffers.   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on       index buffers.`
extern fn DynamicVertexBufferHandle create_dynamic_vertex_buffer(uint _num, VertexLayout* _layout, ushort _flags) @extern("bgfx_create_dynamic_vertex_buffer");

// Create dynamic vertex buffer and initialize it.
// _mem : `Vertex buffer data.`
// _layout : `Vertex layout.`
// _flags : `Buffer creation flags.   - `BGFX_BUFFER_NONE` - No flags.   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of       data is passed. If this flag is not specified, and more data is passed on update, the buffer       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic       buffers.   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on       index buffers.`
extern fn DynamicVertexBufferHandle create_dynamic_vertex_buffer_mem(Memory* _mem, VertexLayout* _layout, ushort _flags) @extern("bgfx_create_dynamic_vertex_buffer_mem");

// Update dynamic vertex buffer.
// _handle : `Dynamic vertex buffer handle.`
// _startVertex : `Start vertex.`
// _mem : `Vertex buffer data.`
extern fn void update_dynamic_vertex_buffer(DynamicVertexBufferHandle _handle, uint _startVertex, Memory* _mem) @extern("bgfx_update_dynamic_vertex_buffer");

// Destroy dynamic vertex buffer.
// _handle : `Dynamic vertex buffer handle.`
extern fn void destroy_dynamic_vertex_buffer(DynamicVertexBufferHandle _handle) @extern("bgfx_destroy_dynamic_vertex_buffer");

// Returns number of requested or maximum available indices.
// _num : `Number of required indices.`
// _index32 : `Set to `true` if input indices will be 32-bit.`
extern fn uint get_avail_transient_index_buffer(uint _num, bool _index32) @extern("bgfx_get_avail_transient_index_buffer");

// Returns number of requested or maximum available vertices.
// _num : `Number of required vertices.`
// _layout : `Vertex layout.`
extern fn uint get_avail_transient_vertex_buffer(uint _num, VertexLayout* _layout) @extern("bgfx_get_avail_transient_vertex_buffer");

// Returns number of requested or maximum available instance buffer slots.
// _num : `Number of required instances.`
// _stride : `Stride per instance.`
extern fn uint get_avail_instance_data_buffer(uint _num, ushort _stride) @extern("bgfx_get_avail_instance_data_buffer");

// Allocate transient index buffer.
// _tib : `TransientIndexBuffer structure will be filled, and will be valid for the duration of frame, and can be reused for multiple draw calls.`
// _num : `Number of indices to allocate.`
// _index32 : `Set to `true` if input indices will be 32-bit.`
extern fn void alloc_transient_index_buffer(TransientIndexBuffer* _tib, uint _num, bool _index32) @extern("bgfx_alloc_transient_index_buffer");

// Allocate transient vertex buffer.
// _tvb : `TransientVertexBuffer structure will be filled, and will be valid for the duration of frame, and can be reused for multiple draw calls.`
// _num : `Number of vertices to allocate.`
// _layout : `Vertex layout.`
extern fn void alloc_transient_vertex_buffer(TransientVertexBuffer* _tvb, uint _num, VertexLayout* _layout) @extern("bgfx_alloc_transient_vertex_buffer");

// Check for required space and allocate transient vertex and index
// buffers. If both space requirements are satisfied function returns
// true.
// _tvb : `TransientVertexBuffer structure will be filled, and will be valid for the duration of frame, and can be reused for multiple draw calls.`
// _layout : `Vertex layout.`
// _numVertices : `Number of vertices to allocate.`
// _tib : `TransientIndexBuffer structure will be filled, and will be valid for the duration of frame, and can be reused for multiple draw calls.`
// _numIndices : `Number of indices to allocate.`
// _index32 : `Set to `true` if input indices will be 32-bit.`
extern fn bool alloc_transient_buffers(TransientVertexBuffer* _tvb, VertexLayout* _layout, uint _numVertices, TransientIndexBuffer* _tib, uint _numIndices, bool _index32) @extern("bgfx_alloc_transient_buffers");

// Allocate instance data buffer.
// _idb : `InstanceDataBuffer structure will be filled, and will be valid for duration of frame, and can be reused for multiple draw calls.`
// _num : `Number of instances.`
// _stride : `Instance stride. Must be multiple of 16.`
extern fn void alloc_instance_data_buffer(InstanceDataBuffer* _idb, uint _num, ushort _stride) @extern("bgfx_alloc_instance_data_buffer");

// Create draw indirect buffer.
// _num : `Number of indirect calls.`
extern fn IndirectBufferHandle create_indirect_buffer(uint _num) @extern("bgfx_create_indirect_buffer");

// Destroy draw indirect buffer.
// _handle : `Indirect buffer handle.`
extern fn void destroy_indirect_buffer(IndirectBufferHandle _handle) @extern("bgfx_destroy_indirect_buffer");

// Create shader from memory buffer.
// @remarks
//   Shader binary is obtained by compiling shader offline with shaderc command line tool.
// _mem : `Shader binary.`
extern fn ShaderHandle create_shader(Memory* _mem) @extern("bgfx_create_shader");

// Returns the number of uniforms and uniform handles used inside a shader.
// @remarks
//   Only non-predefined uniforms are returned.
// _handle : `Shader handle.`
// _uniforms : `UniformHandle array where data will be stored.`
// _max : `Maximum capacity of array.`
extern fn ushort get_shader_uniforms(ShaderHandle _handle, UniformHandle* _uniforms, ushort _max) @extern("bgfx_get_shader_uniforms");

// Set shader debug name.
// _handle : `Shader handle.`
// _name : `Shader name.`
// _len : `Shader name length (if length is INT32_MAX, it's expected that _name is zero terminated string).`
extern fn void set_shader_name(ShaderHandle _handle, ZString _name, int _len) @extern("bgfx_set_shader_name");

// Destroy shader.
// @remark Once a shader program is created with _handle,
//   it is safe to destroy that shader.
// _handle : `Shader handle.`
extern fn void destroy_shader(ShaderHandle _handle) @extern("bgfx_destroy_shader");

// Create program with vertex and fragment shaders.
// _vsh : `Vertex shader.`
// _fsh : `Fragment shader.`
// _destroyShaders : `If true, shaders will be destroyed when program is destroyed.`
extern fn ProgramHandle create_program(ShaderHandle _vsh, ShaderHandle _fsh, bool _destroyShaders) @extern("bgfx_create_program");

// Create program with compute shader.
// _csh : `Compute shader.`
// _destroyShaders : `If true, shaders will be destroyed when program is destroyed.`
extern fn ProgramHandle create_compute_program(ShaderHandle _csh, bool _destroyShaders) @extern("bgfx_create_compute_program");

// Destroy program.
// _handle : `Program handle.`
extern fn void destroy_program(ProgramHandle _handle) @extern("bgfx_destroy_program");

// Validate texture parameters.
// _depth : `Depth dimension of volume texture.`
// _cubeMap : `Indicates that texture contains cubemap.`
// _numLayers : `Number of layers in texture array.`
// _format : `Texture format. See: `TextureFormat::Enum`.`
// _flags : `Texture flags. See `BGFX_TEXTURE_*`.`
extern fn bool is_texture_valid(ushort _depth, bool _cubeMap, ushort _numLayers, TextureFormat _format, ulong _flags) @extern("bgfx_is_texture_valid");

// Validate frame buffer parameters.
// _num : `Number of attachments.`
// _attachment : `Attachment texture info. See: `bgfx::Attachment`.`
extern fn bool is_frame_buffer_valid(char _num, Attachment* _attachment) @extern("bgfx_is_frame_buffer_valid");

// Calculate amount of memory required for texture.
// _info : `Resulting texture info structure. See: `TextureInfo`.`
// _width : `Width.`
// _height : `Height.`
// _depth : `Depth dimension of volume texture.`
// _cubeMap : `Indicates that texture contains cubemap.`
// _hasMips : `Indicates that texture contains full mip-map chain.`
// _numLayers : `Number of layers in texture array.`
// _format : `Texture format. See: `TextureFormat::Enum`.`
extern fn void calc_texture_size(TextureInfo* _info, ushort _width, ushort _height, ushort _depth, bool _cubeMap, bool _hasMips, ushort _numLayers, TextureFormat _format) @extern("bgfx_calc_texture_size");

// Create texture from memory buffer.
// _mem : `DDS, KTX or PVR texture binary data.`
// _flags : `Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`) flags. Default texture sampling mode is linear, and wrap mode is repeat. - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap   mode. - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic   sampling.`
// _skip : `Skip top level mips when parsing texture.`
// _info : `When non-`NULL` is specified it returns parsed texture information.`
extern fn TextureHandle create_texture(Memory* _mem, ulong _flags, char _skip, TextureInfo* _info) @extern("bgfx_create_texture");

// Create 2D texture.
// _width : `Width.`
// _height : `Height.`
// _hasMips : `Indicates that texture contains full mip-map chain.`
// _numLayers : `Number of layers in texture array. Must be 1 if caps `BGFX_CAPS_TEXTURE_2D_ARRAY` flag is not set.`
// _format : `Texture format. See: `TextureFormat::Enum`.`
// _flags : `Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`) flags. Default texture sampling mode is linear, and wrap mode is repeat. - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap   mode. - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic   sampling.`
// _mem : `Texture data. If `_mem` is non-NULL, created texture will be immutable. If `_mem` is NULL content of the texture is uninitialized. When `_numLayers` is more than 1, expected memory layout is texture and all mips together for each array element.`
extern fn TextureHandle create_texture_2d(ushort _width, ushort _height, bool _hasMips, ushort _numLayers, TextureFormat _format, ulong _flags, Memory* _mem) @extern("bgfx_create_texture_2d");

// Create texture with size based on back-buffer ratio. Texture will maintain ratio
// if back buffer resolution changes.
// _ratio : `Texture size in respect to back-buffer size. See: `BackbufferRatio::Enum`.`
// _hasMips : `Indicates that texture contains full mip-map chain.`
// _numLayers : `Number of layers in texture array. Must be 1 if caps `BGFX_CAPS_TEXTURE_2D_ARRAY` flag is not set.`
// _format : `Texture format. See: `TextureFormat::Enum`.`
// _flags : `Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`) flags. Default texture sampling mode is linear, and wrap mode is repeat. - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap   mode. - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic   sampling.`
extern fn TextureHandle create_texture_2d_scaled(BackbufferRatio _ratio, bool _hasMips, ushort _numLayers, TextureFormat _format, ulong _flags) @extern("bgfx_create_texture_2d_scaled");

// Create 3D texture.
// _width : `Width.`
// _height : `Height.`
// _depth : `Depth.`
// _hasMips : `Indicates that texture contains full mip-map chain.`
// _format : `Texture format. See: `TextureFormat::Enum`.`
// _flags : `Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`) flags. Default texture sampling mode is linear, and wrap mode is repeat. - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap   mode. - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic   sampling.`
// _mem : `Texture data. If `_mem` is non-NULL, created texture will be immutable. If `_mem` is NULL content of the texture is uninitialized. When `_numLayers` is more than 1, expected memory layout is texture and all mips together for each array element.`
extern fn TextureHandle create_texture_3d(ushort _width, ushort _height, ushort _depth, bool _hasMips, TextureFormat _format, ulong _flags, Memory* _mem) @extern("bgfx_create_texture_3d");

// Create Cube texture.
// _size : `Cube side size.`
// _hasMips : `Indicates that texture contains full mip-map chain.`
// _numLayers : `Number of layers in texture array. Must be 1 if caps `BGFX_CAPS_TEXTURE_2D_ARRAY` flag is not set.`
// _format : `Texture format. See: `TextureFormat::Enum`.`
// _flags : `Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`) flags. Default texture sampling mode is linear, and wrap mode is repeat. - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap   mode. - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic   sampling.`
// _mem : `Texture data. If `_mem` is non-NULL, created texture will be immutable. If `_mem` is NULL content of the texture is uninitialized. When `_numLayers` is more than 1, expected memory layout is texture and all mips together for each array element.`
extern fn TextureHandle create_texture_cube(ushort _size, bool _hasMips, ushort _numLayers, TextureFormat _format, ulong _flags, Memory* _mem) @extern("bgfx_create_texture_cube");

// Update 2D texture.
// @attention It's valid to update only mutable texture. See `bgfx::createTexture2D` for more info.
// _handle : `Texture handle.`
// _layer : `Layer in texture array.`
// _mip : `Mip level.`
// _x : `X offset in texture.`
// _y : `Y offset in texture.`
// _width : `Width of texture block.`
// _height : `Height of texture block.`
// _mem : `Texture update data.`
// _pitch : `Pitch of input image (bytes). When _pitch is set to UINT16_MAX, it will be calculated internally based on _width.`
extern fn void update_texture_2d(TextureHandle _handle, ushort _layer, char _mip, ushort _x, ushort _y, ushort _width, ushort _height, Memory* _mem, ushort _pitch) @extern("bgfx_update_texture_2d");

// Update 3D texture.
// @attention It's valid to update only mutable texture. See `bgfx::createTexture3D` for more info.
// _handle : `Texture handle.`
// _mip : `Mip level.`
// _x : `X offset in texture.`
// _y : `Y offset in texture.`
// _z : `Z offset in texture.`
// _width : `Width of texture block.`
// _height : `Height of texture block.`
// _depth : `Depth of texture block.`
// _mem : `Texture update data.`
extern fn void update_texture_3d(TextureHandle _handle, char _mip, ushort _x, ushort _y, ushort _z, ushort _width, ushort _height, ushort _depth, Memory* _mem) @extern("bgfx_update_texture_3d");

// Update Cube texture.
// @attention It's valid to update only mutable texture. See `bgfx::createTextureCube` for more info.
// _handle : `Texture handle.`
// _layer : `Layer in texture array.`
// _side : `Cubemap side `BGFX_CUBE_MAP_<POSITIVE or NEGATIVE>_<X, Y or Z>`,   where 0 is +X, 1 is -X, 2 is +Y, 3 is -Y, 4 is +Z, and 5 is -Z.                  +----------+                  |-z       2|                  | ^  +y    |                  | |        |    Unfolded cube:                  | +---->+x |       +----------+----------+----------+----------+       |+y       1|+y       4|+y       0|+y       5|       | ^  -x    | ^  +z    | ^  +x    | ^  -z    |       | |        | |        | |        | |        |       | +---->+z | +---->+x | +---->-z | +---->-x |       +----------+----------+----------+----------+                  |+z       3|                  | ^  -y    |                  | |        |                  | +---->+x |                  +----------+`
// _mip : `Mip level.`
// _x : `X offset in texture.`
// _y : `Y offset in texture.`
// _width : `Width of texture block.`
// _height : `Height of texture block.`
// _mem : `Texture update data.`
// _pitch : `Pitch of input image (bytes). When _pitch is set to UINT16_MAX, it will be calculated internally based on _width.`
extern fn void update_texture_cube(TextureHandle _handle, ushort _layer, char _side, char _mip, ushort _x, ushort _y, ushort _width, ushort _height, Memory* _mem, ushort _pitch) @extern("bgfx_update_texture_cube");

// Read back texture content.
// @attention Texture must be created with `BGFX_TEXTURE_READ_BACK` flag.
// @attention Availability depends on: `BGFX_CAPS_TEXTURE_READ_BACK`.
// _handle : `Texture handle.`
// _data : `Destination buffer.`
// _mip : `Mip level.`
extern fn uint read_texture(TextureHandle _handle, void* _data, char _mip) @extern("bgfx_read_texture");

// Set texture debug name.
// _handle : `Texture handle.`
// _name : `Texture name.`
// _len : `Texture name length (if length is INT32_MAX, it's expected that _name is zero terminated string.`
extern fn void set_texture_name(TextureHandle _handle, ZString _name, int _len) @extern("bgfx_set_texture_name");

// Returns texture direct access pointer.
// @attention Availability depends on: `BGFX_CAPS_TEXTURE_DIRECT_ACCESS`. This feature
//   is available on GPUs that have unified memory architecture (UMA) support.
// _handle : `Texture handle.`
extern fn void* get_direct_access_ptr(TextureHandle _handle) @extern("bgfx_get_direct_access_ptr");

// Destroy texture.
// _handle : `Texture handle.`
extern fn void destroy_texture(TextureHandle _handle) @extern("bgfx_destroy_texture");

// Create frame buffer (simple).
// _width : `Texture width.`
// _height : `Texture height.`
// _format : `Texture format. See: `TextureFormat::Enum`.`
// _textureFlags : `Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`) flags. Default texture sampling mode is linear, and wrap mode is repeat. - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap   mode. - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic   sampling.`
extern fn FrameBufferHandle create_frame_buffer(ushort _width, ushort _height, TextureFormat _format, ulong _textureFlags) @extern("bgfx_create_frame_buffer");

// Create frame buffer with size based on back-buffer ratio. Frame buffer will maintain ratio
// if back buffer resolution changes.
// _ratio : `Frame buffer size in respect to back-buffer size. See: `BackbufferRatio::Enum`.`
// _format : `Texture format. See: `TextureFormat::Enum`.`
// _textureFlags : `Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`) flags. Default texture sampling mode is linear, and wrap mode is repeat. - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap   mode. - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic   sampling.`
extern fn FrameBufferHandle create_frame_buffer_scaled(BackbufferRatio _ratio, TextureFormat _format, ulong _textureFlags) @extern("bgfx_create_frame_buffer_scaled");

// Create MRT frame buffer from texture handles (simple).
// _num : `Number of texture handles.`
// _handles : `Texture attachments.`
// _destroyTexture : `If true, textures will be destroyed when frame buffer is destroyed.`
extern fn FrameBufferHandle create_frame_buffer_from_handles(char _num, TextureHandle* _handles, bool _destroyTexture) @extern("bgfx_create_frame_buffer_from_handles");

// Create MRT frame buffer from texture handles with specific layer and
// mip level.
// _num : `Number of attachments.`
// _attachment : `Attachment texture info. See: `bgfx::Attachment`.`
// _destroyTexture : `If true, textures will be destroyed when frame buffer is destroyed.`
extern fn FrameBufferHandle create_frame_buffer_from_attachment(char _num, Attachment* _attachment, bool _destroyTexture) @extern("bgfx_create_frame_buffer_from_attachment");

// Create frame buffer for multiple window rendering.
// @remarks
//   Frame buffer cannot be used for sampling.
// @attention Availability depends on: `BGFX_CAPS_SWAP_CHAIN`.
// _nwh : `OS' target native window handle.`
// _width : `Window back buffer width.`
// _height : `Window back buffer height.`
// _format : `Window back buffer color format.`
// _depthFormat : `Window back buffer depth format.`
extern fn FrameBufferHandle create_frame_buffer_from_nwh(void* _nwh, ushort _width, ushort _height, TextureFormat _format, TextureFormat _depthFormat) @extern("bgfx_create_frame_buffer_from_nwh");

// Set frame buffer debug name.
// _handle : `Frame buffer handle.`
// _name : `Frame buffer name.`
// _len : `Frame buffer name length (if length is INT32_MAX, it's expected that _name is zero terminated string.`
extern fn void set_frame_buffer_name(FrameBufferHandle _handle, ZString _name, int _len) @extern("bgfx_set_frame_buffer_name");

// Obtain texture handle of frame buffer attachment.
// _handle : `Frame buffer handle.`
extern fn TextureHandle get_texture(FrameBufferHandle _handle, char _attachment) @extern("bgfx_get_texture");

// Destroy frame buffer.
// _handle : `Frame buffer handle.`
extern fn void destroy_frame_buffer(FrameBufferHandle _handle) @extern("bgfx_destroy_frame_buffer");

// Create shader uniform parameter.
// @remarks
//   1. Uniform names are unique. It's valid to call `bgfx::createUniform`
//      multiple times with the same uniform name. The library will always
//      return the same handle, but the handle reference count will be
//      incremented. This means that the same number of `bgfx::destroyUniform`
//      must be called to properly destroy the uniform.
//   2. Predefined uniforms (declared in `bgfx_shader.sh`):
//      - `u_viewRect vec4(x, y, width, height)` - view rectangle for current
//        view, in pixels.
//      - `u_viewTexel vec4(1.0/width, 1.0/height, undef, undef)` - inverse
//        width and height
//      - `u_view mat4` - view matrix
//      - `u_invView mat4` - inverted view matrix
//      - `u_proj mat4` - projection matrix
//      - `u_invProj mat4` - inverted projection matrix
//      - `u_viewProj mat4` - concatenated view projection matrix
//      - `u_invViewProj mat4` - concatenated inverted view projection matrix
//      - `u_model mat4[BGFX_CONFIG_MAX_BONES]` - array of model matrices.
//      - `u_modelView mat4` - concatenated model view matrix, only first
//        model matrix from array is used.
//      - `u_invModelView mat4` - inverted concatenated model view matrix.
//      - `u_modelViewProj mat4` - concatenated model view projection matrix.
//      - `u_alphaRef float` - alpha reference value for alpha test.
// _name : `Uniform name in shader.`
// _type : `Type of uniform (See: `bgfx::UniformType`).`
// _num : `Number of elements in array.`
extern fn UniformHandle create_uniform(ZString _name, UniformType _type, ushort _num) @extern("bgfx_create_uniform");

// Retrieve uniform info.
// _handle : `Handle to uniform object.`
// _info : `Uniform info.`
extern fn void get_uniform_info(UniformHandle _handle, UniformInfo* _info) @extern("bgfx_get_uniform_info");

// Destroy shader uniform parameter.
// _handle : `Handle to uniform object.`
extern fn void destroy_uniform(UniformHandle _handle) @extern("bgfx_destroy_uniform");

// Create occlusion query.
extern fn OcclusionQueryHandle create_occlusion_query() @extern("bgfx_create_occlusion_query");

// Retrieve occlusion query result from previous frame.
// _handle : `Handle to occlusion query object.`
// _result : `Number of pixels that passed test. This argument can be `NULL` if result of occlusion query is not needed.`
extern fn OcclusionQueryResult get_result(OcclusionQueryHandle _handle, int* _result) @extern("bgfx_get_result");

// Destroy occlusion query.
// _handle : `Handle to occlusion query object.`
extern fn void destroy_occlusion_query(OcclusionQueryHandle _handle) @extern("bgfx_destroy_occlusion_query");

// Set palette color value.
// _index : `Index into palette.`
// _rgba : `RGBA floating point values.`
extern fn void set_palette_color(char _index, float _rgba) @extern("bgfx_set_palette_color");

// Set palette color value.
// _index : `Index into palette.`
// _r : `Red value (RGBA floating point values)`
// _g : `Green value (RGBA floating point values)`
// _b : `Blue value (RGBA floating point values)`
// _a : `Alpha value (RGBA floating point values)`
extern fn void set_palette_color_rgba32f(char _index, float _r, float _g, float _b, float _a) @extern("bgfx_set_palette_color_rgba32f");

// Set palette color value.
// _index : `Index into palette.`
// _rgba : `Packed 32-bit RGBA value.`
extern fn void set_palette_color_rgba8(char _index, uint _rgba) @extern("bgfx_set_palette_color_rgba8");

// Set view name.
// @remarks
//   This is debug only feature.
//   In graphics debugger view name will appear as:
//       "nnnc <view name>"
//        ^  ^ ^
//        |  +--- compute (C)
//        +------ view id
// _id : `View id.`
// _name : `View name.`
// _len : `View name length (if length is INT32_MAX, it's expected that _name is zero terminated string.`
extern fn void set_view_name(ushort _id, ZString _name, int _len) @extern("bgfx_set_view_name");

// Set view rectangle. Draw primitive outside view will be clipped.
// _id : `View id.`
// _x : `Position x from the left corner of the window.`
// _y : `Position y from the top corner of the window.`
// _width : `Width of view port region.`
// _height : `Height of view port region.`
extern fn void set_view_rect(ushort _id, ushort _x, ushort _y, ushort _width, ushort _height) @extern("bgfx_set_view_rect");

// Set view rectangle. Draw primitive outside view will be clipped.
// _id : `View id.`
// _x : `Position x from the left corner of the window.`
// _y : `Position y from the top corner of the window.`
// _ratio : `Width and height will be set in respect to back-buffer size. See: `BackbufferRatio::Enum`.`
extern fn void set_view_rect_ratio(ushort _id, ushort _x, ushort _y, BackbufferRatio _ratio) @extern("bgfx_set_view_rect_ratio");

// Set view scissor. Draw primitive outside view will be clipped. When
// _x, _y, _width and _height are set to 0, scissor will be disabled.
// _id : `View id.`
// _x : `Position x from the left corner of the window.`
// _y : `Position y from the top corner of the window.`
// _width : `Width of view scissor region.`
// _height : `Height of view scissor region.`
extern fn void set_view_scissor(ushort _id, ushort _x, ushort _y, ushort _width, ushort _height) @extern("bgfx_set_view_scissor");

// Set view clear flags.
// _id : `View id.`
// _flags : `Clear flags. Use `BGFX_CLEAR_NONE` to remove any clear operation. See: `BGFX_CLEAR_*`.`
// _rgba : `Color clear value.`
// _depth : `Depth clear value.`
// _stencil : `Stencil clear value.`
extern fn void set_view_clear(ushort _id, ushort _flags, uint _rgba, float _depth, char _stencil) @extern("bgfx_set_view_clear");

// Set view clear flags with different clear color for each
// frame buffer texture. `bgfx::setPaletteColor` must be used to set up a
// clear color palette.
// _id : `View id.`
// _flags : `Clear flags. Use `BGFX_CLEAR_NONE` to remove any clear operation. See: `BGFX_CLEAR_*`.`
// _depth : `Depth clear value.`
// _stencil : `Stencil clear value.`
// _c0 : `Palette index for frame buffer attachment 0.`
// _c1 : `Palette index for frame buffer attachment 1.`
// _c2 : `Palette index for frame buffer attachment 2.`
// _c3 : `Palette index for frame buffer attachment 3.`
// _c4 : `Palette index for frame buffer attachment 4.`
// _c5 : `Palette index for frame buffer attachment 5.`
// _c6 : `Palette index for frame buffer attachment 6.`
// _c7 : `Palette index for frame buffer attachment 7.`
extern fn void set_view_clear_mrt(ushort _id, ushort _flags, float _depth, char _stencil, char _c0, char _c1, char _c2, char _c3, char _c4, char _c5, char _c6, char _c7) @extern("bgfx_set_view_clear_mrt");

// Set view sorting mode.
// @remarks
//   View mode must be set prior calling `bgfx::submit` for the view.
// _id : `View id.`
// _mode : `View sort mode. See `ViewMode::Enum`.`
extern fn void set_view_mode(ushort _id, ViewMode _mode) @extern("bgfx_set_view_mode");

// Set view frame buffer.
// @remarks
//   Not persistent after `bgfx::reset` call.
// _id : `View id.`
// _handle : `Frame buffer handle. Passing `BGFX_INVALID_HANDLE` as frame buffer handle will draw primitives from this view into default back buffer.`
extern fn void set_view_frame_buffer(ushort _id, FrameBufferHandle _handle) @extern("bgfx_set_view_frame_buffer");

// Set view's view matrix and projection matrix,
// all draw primitives in this view will use these two matrices.
// _id : `View id.`
// _view : `View matrix.`
// _proj : `Projection matrix.`
extern fn void set_view_transform(ushort _id, void* _view, void* _proj) @extern("bgfx_set_view_transform");

// Post submit view reordering.
// _id : `First view id.`
// _num : `Number of views to remap.`
// _order : `View remap id table. Passing `NULL` will reset view ids to default state.`
extern fn void set_view_order(ushort _id, ushort _num, ushort* _order) @extern("bgfx_set_view_order");

// Reset all view settings to default.
extern fn void reset_view(ushort _id) @extern("bgfx_reset_view");

// Begin submitting draw calls from thread.
// _forThread : `Explicitly request an encoder for a worker thread.`
extern fn Encoder* encoder_begin(bool _forThread) @extern("bgfx_encoder_begin");

// End submitting draw calls from thread.
// _encoder : `Encoder.`
extern fn void encoder_end(Encoder* _encoder) @extern("bgfx_encoder_end");

// Sets a debug marker. This allows you to group graphics calls together for easy browsing in
// graphics debugging tools.
// _name : `Marker name.`
// _len : `Marker name length (if length is INT32_MAX, it's expected that _name is zero terminated string.`
extern fn void encoder_set_marker(Encoder* _this, ZString _name, int _len) @extern("bgfx_encoder_set_marker");

// Set render states for draw primitive.
// @remarks
//   1. To set up more complex states use:
//      `BGFX_STATE_ALPHA_REF(_ref)`,
//      `BGFX_STATE_POINT_SIZE(_size)`,
//      `BGFX_STATE_BLEND_FUNC(_src, _dst)`,
//      `BGFX_STATE_BLEND_FUNC_SEPARATE(_srcRGB, _dstRGB, _srcA, _dstA)`,
//      `BGFX_STATE_BLEND_EQUATION(_equation)`,
//      `BGFX_STATE_BLEND_EQUATION_SEPARATE(_equationRGB, _equationA)`
//   2. `BGFX_STATE_BLEND_EQUATION_ADD` is set when no other blend
//      equation is specified.
// _state : `State flags. Default state for primitive type is   triangles. See: `BGFX_STATE_DEFAULT`.   - `BGFX_STATE_DEPTH_TEST_*` - Depth test function.   - `BGFX_STATE_BLEND_*` - See remark 1 about BGFX_STATE_BLEND_FUNC.   - `BGFX_STATE_BLEND_EQUATION_*` - See remark 2.   - `BGFX_STATE_CULL_*` - Backface culling mode.   - `BGFX_STATE_WRITE_*` - Enable R, G, B, A or Z write.   - `BGFX_STATE_MSAA` - Enable hardware multisample antialiasing.   - `BGFX_STATE_PT_[TRISTRIP/LINES/POINTS]` - Primitive type.`
// _rgba : `Sets blend factor used by `BGFX_STATE_BLEND_FACTOR` and   `BGFX_STATE_BLEND_INV_FACTOR` blend modes.`
extern fn void encoder_set_state(Encoder* _this, ulong _state, uint _rgba) @extern("bgfx_encoder_set_state");

// Set condition for rendering.
// _handle : `Occlusion query handle.`
// _visible : `Render if occlusion query is visible.`
extern fn void encoder_set_condition(Encoder* _this, OcclusionQueryHandle _handle, bool _visible) @extern("bgfx_encoder_set_condition");

// Set stencil test state.
// _fstencil : `Front stencil state.`
// _bstencil : `Back stencil state. If back is set to `BGFX_STENCIL_NONE` _fstencil is applied to both front and back facing primitives.`
extern fn void encoder_set_stencil(Encoder* _this, uint _fstencil, uint _bstencil) @extern("bgfx_encoder_set_stencil");

// Set scissor for draw primitive.
// @remark
//   To scissor for all primitives in view see `bgfx::setViewScissor`.
// _x : `Position x from the left corner of the window.`
// _y : `Position y from the top corner of the window.`
// _width : `Width of view scissor region.`
// _height : `Height of view scissor region.`
extern fn ushort encoder_set_scissor(Encoder* _this, ushort _x, ushort _y, ushort _width, ushort _height) @extern("bgfx_encoder_set_scissor");

// Set scissor from cache for draw primitive.
// @remark
//   To scissor for all primitives in view see `bgfx::setViewScissor`.
// _cache : `Index in scissor cache.`
extern fn void encoder_set_scissor_cached(Encoder* _this, ushort _cache) @extern("bgfx_encoder_set_scissor_cached");

// Set model matrix for draw primitive. If it is not called,
// the model will be rendered with an identity model matrix.
// _mtx : `Pointer to first matrix in array.`
// _num : `Number of matrices in array.`
extern fn uint encoder_set_transform(Encoder* _this, void* _mtx, ushort _num) @extern("bgfx_encoder_set_transform");

//  Set model matrix from matrix cache for draw primitive.
// _cache : `Index in matrix cache.`
// _num : `Number of matrices from cache.`
extern fn void encoder_set_transform_cached(Encoder* _this, uint _cache, ushort _num) @extern("bgfx_encoder_set_transform_cached");

// Reserve matrices in internal matrix cache.
// @attention Pointer returned can be modified until `bgfx::frame` is called.
// _transform : `Pointer to `Transform` structure.`
// _num : `Number of matrices.`
extern fn uint encoder_alloc_transform(Encoder* _this, Transform* _transform, ushort _num) @extern("bgfx_encoder_alloc_transform");

// Set shader uniform parameter for draw primitive.
// _handle : `Uniform.`
// _value : `Pointer to uniform data.`
// _num : `Number of elements. Passing `UINT16_MAX` will use the _num passed on uniform creation.`
extern fn void encoder_set_uniform(Encoder* _this, UniformHandle _handle, void* _value, ushort _num) @extern("bgfx_encoder_set_uniform");

// Set index buffer for draw primitive.
// _handle : `Index buffer.`
// _firstIndex : `First index to render.`
// _numIndices : `Number of indices to render.`
extern fn void encoder_set_index_buffer(Encoder* _this, IndexBufferHandle _handle, uint _firstIndex, uint _numIndices) @extern("bgfx_encoder_set_index_buffer");

// Set index buffer for draw primitive.
// _handle : `Dynamic index buffer.`
// _firstIndex : `First index to render.`
// _numIndices : `Number of indices to render.`
extern fn void encoder_set_dynamic_index_buffer(Encoder* _this, DynamicIndexBufferHandle _handle, uint _firstIndex, uint _numIndices) @extern("bgfx_encoder_set_dynamic_index_buffer");

// Set index buffer for draw primitive.
// _tib : `Transient index buffer.`
// _firstIndex : `First index to render.`
// _numIndices : `Number of indices to render.`
extern fn void encoder_set_transient_index_buffer(Encoder* _this, TransientIndexBuffer* _tib, uint _firstIndex, uint _numIndices) @extern("bgfx_encoder_set_transient_index_buffer");

// Set vertex buffer for draw primitive.
// _stream : `Vertex stream.`
// _handle : `Vertex buffer.`
// _startVertex : `First vertex to render.`
// _numVertices : `Number of vertices to render.`
extern fn void encoder_set_vertex_buffer(Encoder* _this, char _stream, VertexBufferHandle _handle, uint _startVertex, uint _numVertices) @extern("bgfx_encoder_set_vertex_buffer");

// Set vertex buffer for draw primitive.
// _stream : `Vertex stream.`
// _handle : `Vertex buffer.`
// _startVertex : `First vertex to render.`
// _numVertices : `Number of vertices to render.`
// _layoutHandle : `Vertex layout for aliasing vertex buffer. If invalid handle is used, vertex layout used for creation of vertex buffer will be used.`
extern fn void encoder_set_vertex_buffer_with_layout(Encoder* _this, char _stream, VertexBufferHandle _handle, uint _startVertex, uint _numVertices, VertexLayoutHandle _layoutHandle) @extern("bgfx_encoder_set_vertex_buffer_with_layout");

// Set vertex buffer for draw primitive.
// _stream : `Vertex stream.`
// _handle : `Dynamic vertex buffer.`
// _startVertex : `First vertex to render.`
// _numVertices : `Number of vertices to render.`
extern fn void encoder_set_dynamic_vertex_buffer(Encoder* _this, char _stream, DynamicVertexBufferHandle _handle, uint _startVertex, uint _numVertices) @extern("bgfx_encoder_set_dynamic_vertex_buffer");

extern fn void encoder_set_dynamic_vertex_buffer_with_layout(Encoder* _this, char _stream, DynamicVertexBufferHandle _handle, uint _startVertex, uint _numVertices, VertexLayoutHandle _layoutHandle) @extern("bgfx_encoder_set_dynamic_vertex_buffer_with_layout");

// Set vertex buffer for draw primitive.
// _stream : `Vertex stream.`
// _tvb : `Transient vertex buffer.`
// _startVertex : `First vertex to render.`
// _numVertices : `Number of vertices to render.`
extern fn void encoder_set_transient_vertex_buffer(Encoder* _this, char _stream, TransientVertexBuffer* _tvb, uint _startVertex, uint _numVertices) @extern("bgfx_encoder_set_transient_vertex_buffer");

// Set vertex buffer for draw primitive.
// _stream : `Vertex stream.`
// _tvb : `Transient vertex buffer.`
// _startVertex : `First vertex to render.`
// _numVertices : `Number of vertices to render.`
// _layoutHandle : `Vertex layout for aliasing vertex buffer. If invalid handle is used, vertex layout used for creation of vertex buffer will be used.`
extern fn void encoder_set_transient_vertex_buffer_with_layout(Encoder* _this, char _stream, TransientVertexBuffer* _tvb, uint _startVertex, uint _numVertices, VertexLayoutHandle _layoutHandle) @extern("bgfx_encoder_set_transient_vertex_buffer_with_layout");

// Set number of vertices for auto generated vertices use in conjunction
// with gl_VertexID.
// @attention Availability depends on: `BGFX_CAPS_VERTEX_ID`.
// _numVertices : `Number of vertices.`
extern fn void encoder_set_vertex_count(Encoder* _this, uint _numVertices) @extern("bgfx_encoder_set_vertex_count");

// Set instance data buffer for draw primitive.
// _idb : `Transient instance data buffer.`
// _start : `First instance data.`
// _num : `Number of data instances.`
extern fn void encoder_set_instance_data_buffer(Encoder* _this, InstanceDataBuffer* _idb, uint _start, uint _num) @extern("bgfx_encoder_set_instance_data_buffer");

// Set instance data buffer for draw primitive.
// _handle : `Vertex buffer.`
// _startVertex : `First instance data.`
// _num : `Number of data instances.`
extern fn void encoder_set_instance_data_from_vertex_buffer(Encoder* _this, VertexBufferHandle _handle, uint _startVertex, uint _num) @extern("bgfx_encoder_set_instance_data_from_vertex_buffer");

// Set instance data buffer for draw primitive.
// _handle : `Dynamic vertex buffer.`
// _startVertex : `First instance data.`
// _num : `Number of data instances.`
extern fn void encoder_set_instance_data_from_dynamic_vertex_buffer(Encoder* _this, DynamicVertexBufferHandle _handle, uint _startVertex, uint _num) @extern("bgfx_encoder_set_instance_data_from_dynamic_vertex_buffer");

// Set number of instances for auto generated instances use in conjunction
// with gl_InstanceID.
// @attention Availability depends on: `BGFX_CAPS_VERTEX_ID`.
extern fn void encoder_set_instance_count(Encoder* _this, uint _numInstances) @extern("bgfx_encoder_set_instance_count");

// Set texture stage for draw primitive.
// _stage : `Texture unit.`
// _sampler : `Program sampler.`
// _handle : `Texture handle.`
// _flags : `Texture sampling mode. Default value UINT32_MAX uses   texture sampling settings from the texture.   - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap     mode.   - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic     sampling.`
extern fn void encoder_set_texture(Encoder* _this, char _stage, UniformHandle _sampler, TextureHandle _handle, uint _flags) @extern("bgfx_encoder_set_texture");

// Submit an empty primitive for rendering. Uniforms and draw state
// will be applied but no geometry will be submitted. Useful in cases
// when no other draw/compute primitive is submitted to view, but it's
// desired to execute clear view.
// @remark
//   These empty draw calls will sort before ordinary draw calls.
// _id : `View id.`
extern fn void encoder_touch(Encoder* _this, ushort _id) @extern("bgfx_encoder_touch");

// Submit primitive for rendering.
// _id : `View id.`
// _program : `Program.`
// _depth : `Depth for sorting.`
// _flags : `Discard or preserve states. See `BGFX_DISCARD_*`.`
extern fn void encoder_submit(Encoder* _this, ushort _id, ProgramHandle _program, uint _depth, char _flags) @extern("bgfx_encoder_submit");

// Submit primitive with occlusion query for rendering.
// _id : `View id.`
// _program : `Program.`
// _occlusionQuery : `Occlusion query.`
// _depth : `Depth for sorting.`
// _flags : `Discard or preserve states. See `BGFX_DISCARD_*`.`
extern fn void encoder_submit_occlusion_query(Encoder* _this, ushort _id, ProgramHandle _program, OcclusionQueryHandle _occlusionQuery, uint _depth, char _flags) @extern("bgfx_encoder_submit_occlusion_query");

// Submit primitive for rendering with index and instance data info from
// indirect buffer.
// @attention Availability depends on: `BGFX_CAPS_DRAW_INDIRECT`.
// _id : `View id.`
// _program : `Program.`
// _indirectHandle : `Indirect buffer.`
// _start : `First element in indirect buffer.`
// _num : `Number of draws.`
// _depth : `Depth for sorting.`
// _flags : `Discard or preserve states. See `BGFX_DISCARD_*`.`
extern fn void encoder_submit_indirect(Encoder* _this, ushort _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, uint _start, uint _num, uint _depth, char _flags) @extern("bgfx_encoder_submit_indirect");

// Submit primitive for rendering with index and instance data info and
// draw count from indirect buffers.
// @attention Availability depends on: `BGFX_CAPS_DRAW_INDIRECT_COUNT`.
// _id : `View id.`
// _program : `Program.`
// _indirectHandle : `Indirect buffer.`
// _start : `First element in indirect buffer.`
// _numHandle : `Buffer for number of draws. Must be   created with `BGFX_BUFFER_INDEX32` and `BGFX_BUFFER_DRAW_INDIRECT`.`
// _numIndex : `Element in number buffer.`
// _numMax : `Max number of draws.`
// _depth : `Depth for sorting.`
// _flags : `Discard or preserve states. See `BGFX_DISCARD_*`.`
extern fn void encoder_submit_indirect_count(Encoder* _this, ushort _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, uint _start, IndexBufferHandle _numHandle, uint _numIndex, uint _numMax, uint _depth, char _flags) @extern("bgfx_encoder_submit_indirect_count");

// Set compute index buffer.
// _stage : `Compute stage.`
// _handle : `Index buffer handle.`
// _access : `Buffer access. See `Access::Enum`.`
extern fn void encoder_set_compute_index_buffer(Encoder* _this, char _stage, IndexBufferHandle _handle, Access _access) @extern("bgfx_encoder_set_compute_index_buffer");

// Set compute vertex buffer.
// _stage : `Compute stage.`
// _handle : `Vertex buffer handle.`
// _access : `Buffer access. See `Access::Enum`.`
extern fn void encoder_set_compute_vertex_buffer(Encoder* _this, char _stage, VertexBufferHandle _handle, Access _access) @extern("bgfx_encoder_set_compute_vertex_buffer");

// Set compute dynamic index buffer.
// _stage : `Compute stage.`
// _handle : `Dynamic index buffer handle.`
// _access : `Buffer access. See `Access::Enum`.`
extern fn void encoder_set_compute_dynamic_index_buffer(Encoder* _this, char _stage, DynamicIndexBufferHandle _handle, Access _access) @extern("bgfx_encoder_set_compute_dynamic_index_buffer");

// Set compute dynamic vertex buffer.
// _stage : `Compute stage.`
// _handle : `Dynamic vertex buffer handle.`
// _access : `Buffer access. See `Access::Enum`.`
extern fn void encoder_set_compute_dynamic_vertex_buffer(Encoder* _this, char _stage, DynamicVertexBufferHandle _handle, Access _access) @extern("bgfx_encoder_set_compute_dynamic_vertex_buffer");

// Set compute indirect buffer.
// _stage : `Compute stage.`
// _handle : `Indirect buffer handle.`
// _access : `Buffer access. See `Access::Enum`.`
extern fn void encoder_set_compute_indirect_buffer(Encoder* _this, char _stage, IndirectBufferHandle _handle, Access _access) @extern("bgfx_encoder_set_compute_indirect_buffer");

// Set compute image from texture.
// _stage : `Compute stage.`
// _handle : `Texture handle.`
// _mip : `Mip level.`
// _access : `Image access. See `Access::Enum`.`
// _format : `Texture format. See: `TextureFormat::Enum`.`
extern fn void encoder_set_image(Encoder* _this, char _stage, TextureHandle _handle, char _mip, Access _access, TextureFormat _format) @extern("bgfx_encoder_set_image");

// Dispatch compute.
// _id : `View id.`
// _program : `Compute program.`
// _numX : `Number of groups X.`
// _numY : `Number of groups Y.`
// _numZ : `Number of groups Z.`
// _flags : `Discard or preserve states. See `BGFX_DISCARD_*`.`
extern fn void encoder_dispatch(Encoder* _this, ushort _id, ProgramHandle _program, uint _numX, uint _numY, uint _numZ, char _flags) @extern("bgfx_encoder_dispatch");

// Dispatch compute indirect.
// _id : `View id.`
// _program : `Compute program.`
// _indirectHandle : `Indirect buffer.`
// _start : `First element in indirect buffer.`
// _num : `Number of dispatches.`
// _flags : `Discard or preserve states. See `BGFX_DISCARD_*`.`
extern fn void encoder_dispatch_indirect(Encoder* _this, ushort _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, uint _start, uint _num, char _flags) @extern("bgfx_encoder_dispatch_indirect");

// Discard previously set state for draw or compute call.
// _flags : `Discard or preserve states. See `BGFX_DISCARD_*`.`
extern fn void encoder_discard(Encoder* _this, char _flags) @extern("bgfx_encoder_discard");

// Blit 2D texture region between two 2D textures.
// @attention Destination texture must be created with `BGFX_TEXTURE_BLIT_DST` flag.
// @attention Availability depends on: `BGFX_CAPS_TEXTURE_BLIT`.
// _id : `View id.`
// _dst : `Destination texture handle.`
// _dstMip : `Destination texture mip level.`
// _dstX : `Destination texture X position.`
// _dstY : `Destination texture Y position.`
// _dstZ : `If texture is 2D this argument should be 0. If destination texture is cube this argument represents destination texture cube face. For 3D texture this argument represents destination texture Z position.`
// _src : `Source texture handle.`
// _srcMip : `Source texture mip level.`
// _srcX : `Source texture X position.`
// _srcY : `Source texture Y position.`
// _srcZ : `If texture is 2D this argument should be 0. If source texture is cube this argument represents source texture cube face. For 3D texture this argument represents source texture Z position.`
// _width : `Width of region.`
// _height : `Height of region.`
// _depth : `If texture is 3D this argument represents depth of region, otherwise it's unused.`
extern fn void encoder_blit(Encoder* _this, ushort _id, TextureHandle _dst, char _dstMip, ushort _dstX, ushort _dstY, ushort _dstZ, TextureHandle _src, char _srcMip, ushort _srcX, ushort _srcY, ushort _srcZ, ushort _width, ushort _height, ushort _depth) @extern("bgfx_encoder_blit");

// Request screen shot of window back buffer.
// @remarks
//   `bgfx::CallbackI::screenShot` must be implemented.
// @attention Frame buffer handle must be created with OS' target native window handle.
// _handle : `Frame buffer handle. If handle is `BGFX_INVALID_HANDLE` request will be made for main window back buffer.`
// _filePath : `Will be passed to `bgfx::CallbackI::screenShot` callback.`
extern fn void request_screen_shot(FrameBufferHandle _handle, ZString _filePath) @extern("bgfx_request_screen_shot");

// Render frame.
// @attention `bgfx::renderFrame` is blocking call. It waits for
//   `bgfx::frame` to be called from API thread to process frame.
//   If timeout value is passed call will timeout and return even
//   if `bgfx::frame` is not called.
// @warning This call should be only used on platforms that don't
//   allow creating separate rendering thread. If it is called before
//   to bgfx::init, render thread won't be created by bgfx::init call.
// _msecs : `Timeout in milliseconds.`
extern fn RenderFrame render_frame(int _msecs) @extern("bgfx_render_frame");

// Set platform data.
// @warning Must be called before `bgfx::init`.
// _data : `Platform data.`
extern fn void set_platform_data(PlatformData* _data) @extern("bgfx_set_platform_data");

// Get internal data for interop.
// @attention It's expected you understand some bgfx internals before you
//   use this call.
// @warning Must be called only on render thread.
extern fn InternalData* get_internal_data() @extern("bgfx_get_internal_data");

// Override internal texture with externally created texture. Previously
// created internal texture will released.
// @attention It's expected you understand some bgfx internals before you
//   use this call.
// @warning Must be called only on render thread.
// _handle : `Texture handle.`
// _ptr : `Native API pointer to texture.`
extern fn uptr override_internal_texture_ptr(TextureHandle _handle, uptr _ptr) @extern("bgfx_override_internal_texture_ptr");

// Override internal texture by creating new texture. Previously created
// internal texture will released.
// @attention It's expected you understand some bgfx internals before you
//   use this call.
// @returns Native API pointer to texture. If result is 0, texture is not created yet from the
//   main thread.
// @warning Must be called only on render thread.
// _handle : `Texture handle.`
// _width : `Width.`
// _height : `Height.`
// _numMips : `Number of mip-maps.`
// _format : `Texture format. See: `TextureFormat::Enum`.`
// _flags : `Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`) flags. Default texture sampling mode is linear, and wrap mode is repeat. - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap   mode. - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic   sampling.`
extern fn uptr override_internal_texture(TextureHandle _handle, ushort _width, ushort _height, char _numMips, TextureFormat _format, ulong _flags) @extern("bgfx_override_internal_texture");

// Sets a debug marker. This allows you to group graphics calls together for easy browsing in
// graphics debugging tools.
// _name : `Marker name.`
// _len : `Marker name length (if length is INT32_MAX, it's expected that _name is zero terminated string.`
extern fn void set_marker(ZString _name, int _len) @extern("bgfx_set_marker");

// Set render states for draw primitive.
// @remarks
//   1. To set up more complex states use:
//      `BGFX_STATE_ALPHA_REF(_ref)`,
//      `BGFX_STATE_POINT_SIZE(_size)`,
//      `BGFX_STATE_BLEND_FUNC(_src, _dst)`,
//      `BGFX_STATE_BLEND_FUNC_SEPARATE(_srcRGB, _dstRGB, _srcA, _dstA)`,
//      `BGFX_STATE_BLEND_EQUATION(_equation)`,
//      `BGFX_STATE_BLEND_EQUATION_SEPARATE(_equationRGB, _equationA)`
//   2. `BGFX_STATE_BLEND_EQUATION_ADD` is set when no other blend
//      equation is specified.
// _state : `State flags. Default state for primitive type is   triangles. See: `BGFX_STATE_DEFAULT`.   - `BGFX_STATE_DEPTH_TEST_*` - Depth test function.   - `BGFX_STATE_BLEND_*` - See remark 1 about BGFX_STATE_BLEND_FUNC.   - `BGFX_STATE_BLEND_EQUATION_*` - See remark 2.   - `BGFX_STATE_CULL_*` - Backface culling mode.   - `BGFX_STATE_WRITE_*` - Enable R, G, B, A or Z write.   - `BGFX_STATE_MSAA` - Enable hardware multisample antialiasing.   - `BGFX_STATE_PT_[TRISTRIP/LINES/POINTS]` - Primitive type.`
// _rgba : `Sets blend factor used by `BGFX_STATE_BLEND_FACTOR` and   `BGFX_STATE_BLEND_INV_FACTOR` blend modes.`
extern fn void set_state(ulong _state, uint _rgba) @extern("bgfx_set_state");

// Set condition for rendering.
// _handle : `Occlusion query handle.`
// _visible : `Render if occlusion query is visible.`
extern fn void set_condition(OcclusionQueryHandle _handle, bool _visible) @extern("bgfx_set_condition");

// Set stencil test state.
// _fstencil : `Front stencil state.`
// _bstencil : `Back stencil state. If back is set to `BGFX_STENCIL_NONE` _fstencil is applied to both front and back facing primitives.`
extern fn void set_stencil(uint _fstencil, uint _bstencil) @extern("bgfx_set_stencil");

// Set scissor for draw primitive.
// @remark
//   To scissor for all primitives in view see `bgfx::setViewScissor`.
// _x : `Position x from the left corner of the window.`
// _y : `Position y from the top corner of the window.`
// _width : `Width of view scissor region.`
// _height : `Height of view scissor region.`
extern fn ushort set_scissor(ushort _x, ushort _y, ushort _width, ushort _height) @extern("bgfx_set_scissor");

// Set scissor from cache for draw primitive.
// @remark
//   To scissor for all primitives in view see `bgfx::setViewScissor`.
// _cache : `Index in scissor cache.`
extern fn void set_scissor_cached(ushort _cache) @extern("bgfx_set_scissor_cached");

// Set model matrix for draw primitive. If it is not called,
// the model will be rendered with an identity model matrix.
// _mtx : `Pointer to first matrix in array.`
// _num : `Number of matrices in array.`
extern fn uint set_transform(void* _mtx, ushort _num) @extern("bgfx_set_transform");

//  Set model matrix from matrix cache for draw primitive.
// _cache : `Index in matrix cache.`
// _num : `Number of matrices from cache.`
extern fn void set_transform_cached(uint _cache, ushort _num) @extern("bgfx_set_transform_cached");

// Reserve matrices in internal matrix cache.
// @attention Pointer returned can be modified until `bgfx::frame` is called.
// _transform : `Pointer to `Transform` structure.`
// _num : `Number of matrices.`
extern fn uint alloc_transform(Transform* _transform, ushort _num) @extern("bgfx_alloc_transform");

// Set shader uniform parameter for draw primitive.
// _handle : `Uniform.`
// _value : `Pointer to uniform data.`
// _num : `Number of elements. Passing `UINT16_MAX` will use the _num passed on uniform creation.`
extern fn void set_uniform(UniformHandle _handle, void* _value, ushort _num) @extern("bgfx_set_uniform");

// Set index buffer for draw primitive.
// _handle : `Index buffer.`
// _firstIndex : `First index to render.`
// _numIndices : `Number of indices to render.`
extern fn void set_index_buffer(IndexBufferHandle _handle, uint _firstIndex, uint _numIndices) @extern("bgfx_set_index_buffer");

// Set index buffer for draw primitive.
// _handle : `Dynamic index buffer.`
// _firstIndex : `First index to render.`
// _numIndices : `Number of indices to render.`
extern fn void set_dynamic_index_buffer(DynamicIndexBufferHandle _handle, uint _firstIndex, uint _numIndices) @extern("bgfx_set_dynamic_index_buffer");

// Set index buffer for draw primitive.
// _tib : `Transient index buffer.`
// _firstIndex : `First index to render.`
// _numIndices : `Number of indices to render.`
extern fn void set_transient_index_buffer(TransientIndexBuffer* _tib, uint _firstIndex, uint _numIndices) @extern("bgfx_set_transient_index_buffer");

// Set vertex buffer for draw primitive.
// _stream : `Vertex stream.`
// _handle : `Vertex buffer.`
// _startVertex : `First vertex to render.`
// _numVertices : `Number of vertices to render.`
extern fn void set_vertex_buffer(char _stream, VertexBufferHandle _handle, uint _startVertex, uint _numVertices) @extern("bgfx_set_vertex_buffer");

// Set vertex buffer for draw primitive.
// _stream : `Vertex stream.`
// _handle : `Vertex buffer.`
// _startVertex : `First vertex to render.`
// _numVertices : `Number of vertices to render.`
// _layoutHandle : `Vertex layout for aliasing vertex buffer. If invalid handle is used, vertex layout used for creation of vertex buffer will be used.`
extern fn void set_vertex_buffer_with_layout(char _stream, VertexBufferHandle _handle, uint _startVertex, uint _numVertices, VertexLayoutHandle _layoutHandle) @extern("bgfx_set_vertex_buffer_with_layout");

// Set vertex buffer for draw primitive.
// _stream : `Vertex stream.`
// _handle : `Dynamic vertex buffer.`
// _startVertex : `First vertex to render.`
// _numVertices : `Number of vertices to render.`
extern fn void set_dynamic_vertex_buffer(char _stream, DynamicVertexBufferHandle _handle, uint _startVertex, uint _numVertices) @extern("bgfx_set_dynamic_vertex_buffer");

// Set vertex buffer for draw primitive.
// _stream : `Vertex stream.`
// _handle : `Dynamic vertex buffer.`
// _startVertex : `First vertex to render.`
// _numVertices : `Number of vertices to render.`
// _layoutHandle : `Vertex layout for aliasing vertex buffer. If invalid handle is used, vertex layout used for creation of vertex buffer will be used.`
extern fn void set_dynamic_vertex_buffer_with_layout(char _stream, DynamicVertexBufferHandle _handle, uint _startVertex, uint _numVertices, VertexLayoutHandle _layoutHandle) @extern("bgfx_set_dynamic_vertex_buffer_with_layout");

// Set vertex buffer for draw primitive.
// _stream : `Vertex stream.`
// _tvb : `Transient vertex buffer.`
// _startVertex : `First vertex to render.`
// _numVertices : `Number of vertices to render.`
extern fn void set_transient_vertex_buffer(char _stream, TransientVertexBuffer* _tvb, uint _startVertex, uint _numVertices) @extern("bgfx_set_transient_vertex_buffer");

// Set vertex buffer for draw primitive.
// _stream : `Vertex stream.`
// _tvb : `Transient vertex buffer.`
// _startVertex : `First vertex to render.`
// _numVertices : `Number of vertices to render.`
// _layoutHandle : `Vertex layout for aliasing vertex buffer. If invalid handle is used, vertex layout used for creation of vertex buffer will be used.`
extern fn void set_transient_vertex_buffer_with_layout(char _stream, TransientVertexBuffer* _tvb, uint _startVertex, uint _numVertices, VertexLayoutHandle _layoutHandle) @extern("bgfx_set_transient_vertex_buffer_with_layout");

// Set number of vertices for auto generated vertices use in conjunction
// with gl_VertexID.
// @attention Availability depends on: `BGFX_CAPS_VERTEX_ID`.
// _numVertices : `Number of vertices.`
extern fn void set_vertex_count(uint _numVertices) @extern("bgfx_set_vertex_count");

// Set instance data buffer for draw primitive.
// _idb : `Transient instance data buffer.`
// _start : `First instance data.`
// _num : `Number of data instances.`
extern fn void set_instance_data_buffer(InstanceDataBuffer* _idb, uint _start, uint _num) @extern("bgfx_set_instance_data_buffer");

// Set instance data buffer for draw primitive.
// _handle : `Vertex buffer.`
// _startVertex : `First instance data.`
// _num : `Number of data instances.`
extern fn void set_instance_data_from_vertex_buffer(VertexBufferHandle _handle, uint _startVertex, uint _num) @extern("bgfx_set_instance_data_from_vertex_buffer");

// Set instance data buffer for draw primitive.
// _handle : `Dynamic vertex buffer.`
// _startVertex : `First instance data.`
// _num : `Number of data instances.`
extern fn void set_instance_data_from_dynamic_vertex_buffer(DynamicVertexBufferHandle _handle, uint _startVertex, uint _num) @extern("bgfx_set_instance_data_from_dynamic_vertex_buffer");

// Set number of instances for auto generated instances use in conjunction
// with gl_InstanceID.
// @attention Availability depends on: `BGFX_CAPS_VERTEX_ID`.
extern fn void set_instance_count(uint _numInstances) @extern("bgfx_set_instance_count");

// Set texture stage for draw primitive.
// _stage : `Texture unit.`
// _sampler : `Program sampler.`
// _handle : `Texture handle.`
// _flags : `Texture sampling mode. Default value UINT32_MAX uses   texture sampling settings from the texture.   - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap     mode.   - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic     sampling.`
extern fn void set_texture(char _stage, UniformHandle _sampler, TextureHandle _handle, uint _flags) @extern("bgfx_set_texture");

// Submit an empty primitive for rendering. Uniforms and draw state
// will be applied but no geometry will be submitted.
// @remark
//   These empty draw calls will sort before ordinary draw calls.
// _id : `View id.`
extern fn void touch(ushort _id) @extern("bgfx_touch");

// Submit primitive for rendering.
// _id : `View id.`
// _program : `Program.`
// _depth : `Depth for sorting.`
// _flags : `Which states to discard for next draw. See `BGFX_DISCARD_*`.`
extern fn void submit(ushort _id, ProgramHandle _program, uint _depth, char _flags) @extern("bgfx_submit");

// Submit primitive with occlusion query for rendering.
// _id : `View id.`
// _program : `Program.`
// _occlusionQuery : `Occlusion query.`
// _depth : `Depth for sorting.`
// _flags : `Which states to discard for next draw. See `BGFX_DISCARD_*`.`
extern fn void submit_occlusion_query(ushort _id, ProgramHandle _program, OcclusionQueryHandle _occlusionQuery, uint _depth, char _flags) @extern("bgfx_submit_occlusion_query");

// Submit primitive for rendering with index and instance data info from
// indirect buffer.
// @attention Availability depends on: `BGFX_CAPS_DRAW_INDIRECT`.
// _id : `View id.`
// _program : `Program.`
// _indirectHandle : `Indirect buffer.`
// _start : `First element in indirect buffer.`
// _num : `Number of draws.`
// _depth : `Depth for sorting.`
// _flags : `Which states to discard for next draw. See `BGFX_DISCARD_*`.`
extern fn void submit_indirect(ushort _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, uint _start, uint _num, uint _depth, char _flags) @extern("bgfx_submit_indirect");

// Submit primitive for rendering with index and instance data info and
// draw count from indirect buffers.
// @attention Availability depends on: `BGFX_CAPS_DRAW_INDIRECT_COUNT`.
// _id : `View id.`
// _program : `Program.`
// _indirectHandle : `Indirect buffer.`
// _start : `First element in indirect buffer.`
// _numHandle : `Buffer for number of draws. Must be   created with `BGFX_BUFFER_INDEX32` and `BGFX_BUFFER_DRAW_INDIRECT`.`
// _numIndex : `Element in number buffer.`
// _numMax : `Max number of draws.`
// _depth : `Depth for sorting.`
// _flags : `Which states to discard for next draw. See `BGFX_DISCARD_*`.`
extern fn void submit_indirect_count(ushort _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, uint _start, IndexBufferHandle _numHandle, uint _numIndex, uint _numMax, uint _depth, char _flags) @extern("bgfx_submit_indirect_count");

// Set compute index buffer.
// _stage : `Compute stage.`
// _handle : `Index buffer handle.`
// _access : `Buffer access. See `Access::Enum`.`
extern fn void set_compute_index_buffer(char _stage, IndexBufferHandle _handle, Access _access) @extern("bgfx_set_compute_index_buffer");

// Set compute vertex buffer.
// _stage : `Compute stage.`
// _handle : `Vertex buffer handle.`
// _access : `Buffer access. See `Access::Enum`.`
extern fn void set_compute_vertex_buffer(char _stage, VertexBufferHandle _handle, Access _access) @extern("bgfx_set_compute_vertex_buffer");

// Set compute dynamic index buffer.
// _stage : `Compute stage.`
// _handle : `Dynamic index buffer handle.`
// _access : `Buffer access. See `Access::Enum`.`
extern fn void set_compute_dynamic_index_buffer(char _stage, DynamicIndexBufferHandle _handle, Access _access) @extern("bgfx_set_compute_dynamic_index_buffer");

// Set compute dynamic vertex buffer.
// _stage : `Compute stage.`
// _handle : `Dynamic vertex buffer handle.`
// _access : `Buffer access. See `Access::Enum`.`
extern fn void set_compute_dynamic_vertex_buffer(char _stage, DynamicVertexBufferHandle _handle, Access _access) @extern("bgfx_set_compute_dynamic_vertex_buffer");

// Set compute indirect buffer.
// _stage : `Compute stage.`
// _handle : `Indirect buffer handle.`
// _access : `Buffer access. See `Access::Enum`.`
extern fn void set_compute_indirect_buffer(char _stage, IndirectBufferHandle _handle, Access _access) @extern("bgfx_set_compute_indirect_buffer");

// Set compute image from texture.
// _stage : `Compute stage.`
// _handle : `Texture handle.`
// _mip : `Mip level.`
// _access : `Image access. See `Access::Enum`.`
// _format : `Texture format. See: `TextureFormat::Enum`.`
extern fn void set_image(char _stage, TextureHandle _handle, char _mip, Access _access, TextureFormat _format) @extern("bgfx_set_image");

// Dispatch compute.
// _id : `View id.`
// _program : `Compute program.`
// _numX : `Number of groups X.`
// _numY : `Number of groups Y.`
// _numZ : `Number of groups Z.`
// _flags : `Discard or preserve states. See `BGFX_DISCARD_*`.`
extern fn void dispatch(ushort _id, ProgramHandle _program, uint _numX, uint _numY, uint _numZ, char _flags) @extern("bgfx_dispatch");

// Dispatch compute indirect.
// _id : `View id.`
// _program : `Compute program.`
// _indirectHandle : `Indirect buffer.`
// _start : `First element in indirect buffer.`
// _num : `Number of dispatches.`
// _flags : `Discard or preserve states. See `BGFX_DISCARD_*`.`
extern fn void dispatch_indirect(ushort _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, uint _start, uint _num, char _flags) @extern("bgfx_dispatch_indirect");

// Discard previously set state for draw or compute call.
// _flags : `Draw/compute states to discard.`
extern fn void discard(char _flags) @extern("bgfx_discard");

// Blit 2D texture region between two 2D textures.
// @attention Destination texture must be created with `BGFX_TEXTURE_BLIT_DST` flag.
// @attention Availability depends on: `BGFX_CAPS_TEXTURE_BLIT`.
// _id : `View id.`
// _dst : `Destination texture handle.`
// _dstMip : `Destination texture mip level.`
// _dstX : `Destination texture X position.`
// _dstY : `Destination texture Y position.`
// _dstZ : `If texture is 2D this argument should be 0. If destination texture is cube this argument represents destination texture cube face. For 3D texture this argument represents destination texture Z position.`
// _src : `Source texture handle.`
// _srcMip : `Source texture mip level.`
// _srcX : `Source texture X position.`
// _srcY : `Source texture Y position.`
// _srcZ : `If texture is 2D this argument should be 0. If source texture is cube this argument represents source texture cube face. For 3D texture this argument represents source texture Z position.`
// _width : `Width of region.`
// _height : `Height of region.`
// _depth : `If texture is 3D this argument represents depth of region, otherwise it's unused.`
extern fn void blit(ushort _id, TextureHandle _dst, char _dstMip, ushort _dstX, ushort _dstY, ushort _dstZ, TextureHandle _src, char _srcMip, ushort _srcX, ushort _srcY, ushort _srcZ, ushort _width, ushort _height, ushort _depth) @extern("bgfx_blit");

