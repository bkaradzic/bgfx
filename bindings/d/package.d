/+
+ ┌==============================┐
+ │ AUTO GENERATED! DO NOT EDIT! │
+ └==============================┘
+/
module bgfx;

import bindbc.bgfx.config;

import bindbc.common.types: c_int64, c_uint64, va_list;
static import bgfx.fakeenum;

enum uint apiVersion = 128;

alias ViewID = ushort;

enum invalidHandle(T) = T(ushort.max);

alias ReleaseFn = void function(void* ptr, void* userData);

///Memory release callback.

///Color RGB/alpha/depth write. When it's not specified write will be disabled.
alias StateWrite_ = ulong;
enum StateWrite: StateWrite_{
	r     = 0x0000_0000_0000_0001, ///Enable R write.
	g     = 0x0000_0000_0000_0002, ///Enable G write.
	b     = 0x0000_0000_0000_0004, ///Enable B write.
	a     = 0x0000_0000_0000_0008, ///Enable alpha write.
	z     = 0x0000_0040_0000_0000, ///Enable depth write.
	rgb   = 0x0000_0000_0000_0007, ///Enable RGB write.
	mask  = 0x0000_0040_0000_000F, ///Write all channels mask.
}

///Depth test state. When `BGFX_STATE_DEPTH_` is not specified depth test will be disabled.
alias StateDepthTest_ = ulong;
enum StateDepthTest: StateDepthTest_{
	less      = 0x0000_0000_0000_0010, ///Enable depth test, less.
	lEqual    = 0x0000_0000_0000_0020, ///Enable depth test, less or equal.
	equal     = 0x0000_0000_0000_0030, ///Enable depth test, equal.
	gEqual    = 0x0000_0000_0000_0040, ///Enable depth test, greater or equal.
	greater   = 0x0000_0000_0000_0050, ///Enable depth test, greater.
	notEqual  = 0x0000_0000_0000_0060, ///Enable depth test, not equal.
	never     = 0x0000_0000_0000_0070, ///Enable depth test, never.
	always    = 0x0000_0000_0000_0080, ///Enable depth test, always.
	shift     = 4, ///Depth test state bit shift
	mask      = 0x0000_0000_0000_00F0, ///Depth test state bit mask
}

/**
Use BGFX_STATE_BLEND_FUNC(_src, _dst) or BGFX_STATE_BLEND_FUNC_SEPARATE(_srcRGB, _dstRGB, _srcA, _dstA)
helper macros.
*/
alias StateBlend_ = ulong;
enum StateBlend: StateBlend_{
	zero         = 0x0000_0000_0000_1000, ///0, 0, 0, 0
	one          = 0x0000_0000_0000_2000, ///1, 1, 1, 1
	srcColor     = 0x0000_0000_0000_3000, ///Rs, Gs, Bs, As
	srcColour    = srcColor,
	invSrcColor  = 0x0000_0000_0000_4000, ///1-Rs, 1-Gs, 1-Bs, 1-As
	invSrcColour = invSrcColor,
	srcAlpha     = 0x0000_0000_0000_5000, ///As, As, As, As
	invSrcAlpha  = 0x0000_0000_0000_6000, ///1-As, 1-As, 1-As, 1-As
	dstAlpha     = 0x0000_0000_0000_7000, ///Ad, Ad, Ad, Ad
	invDstAlpha  = 0x0000_0000_0000_8000, ///1-Ad, 1-Ad, 1-Ad ,1-Ad
	dstColor     = 0x0000_0000_0000_9000, ///Rd, Gd, Bd, Ad
	dstColour    = dstColor,
	invDstColor  = 0x0000_0000_0000_A000, ///1-Rd, 1-Gd, 1-Bd, 1-Ad
	invDstColour = invDstColor,
	srcAlphaSat  = 0x0000_0000_0000_B000, ///f, f, f, 1; f = min(As, 1-Ad)
	factor       = 0x0000_0000_0000_C000, ///Blend factor
	invFactor    = 0x0000_0000_0000_D000, ///1-Blend factor
	shift        = 12, ///Blend state bit shift
	mask         = 0x0000_0000_0FFF_F000, ///Blend state bit mask
}

/**
Use BGFX_STATE_BLEND_EQUATION(_equation) or BGFX_STATE_BLEND_EQUATION_SEPARATE(_equationRGB, _equationA)
helper macros.
*/
alias StateBlendEquation_ = ulong;
enum StateBlendEquation: StateBlendEquation_{
	add     = 0x0000_0000_0000_0000, ///Blend add: src + dst.
	sub     = 0x0000_0000_1000_0000, ///Blend subtract: src - dst.
	revSub  = 0x0000_0000_2000_0000, ///Blend reverse subtract: dst - src.
	min     = 0x0000_0000_3000_0000, ///Blend min: min(src, dst).
	max     = 0x0000_0000_4000_0000, ///Blend max: max(src, dst).
	shift   = 28, ///Blend equation bit shift
	mask    = 0x0000_0003_F000_0000, ///Blend equation bit mask
}

///Cull state. When `BGFX_STATE_CULL_*` is not specified culling will be disabled.
alias StateCull_ = ulong;
enum StateCull: StateCull_{
	cw     = 0x0000_0010_0000_0000, ///Cull clockwise triangles.
	ccw    = 0x0000_0020_0000_0000, ///Cull counter-clockwise triangles.
	acw    = ccw,
	shift  = 36, ///Culling mode bit shift
	mask   = 0x0000_0030_0000_0000, ///Culling mode bit mask
}

///Alpha reference value.
alias StateAlphaRef_ = ulong;
enum StateAlphaRef: StateAlphaRef_{
	shift  = 40, ///Alpha reference bit shift
	mask   = 0x0000_FF00_0000_0000, ///Alpha reference bit mask
}
StateAlphaRef_ toStateAlphaRef(ulong v) nothrow @nogc pure @safe{ return (v << StateAlphaRef.shift) & StateAlphaRef.mask; }

alias StatePT_ = ulong;
enum StatePT: StatePT_{
	triStrip   = 0x0001_0000_0000_0000, ///Tristrip.
	lines      = 0x0002_0000_0000_0000, ///Lines.
	lineStrip  = 0x0003_0000_0000_0000, ///Line strip.
	points     = 0x0004_0000_0000_0000, ///Points.
	shift      = 48, ///Primitive type bit shift
	mask       = 0x0007_0000_0000_0000, ///Primitive type bit mask
}

///Point size value.
alias StatePointSize_ = ulong;
enum StatePointSize: StatePointSize_{
	shift  = 52, ///Point size bit shift
	mask   = 0x00F0_0000_0000_0000, ///Point size bit mask
}
StatePointSize_ toStatePointSize(ulong v) nothrow @nogc pure @safe{ return (v << StatePointSize.shift) & StatePointSize.mask; }

/**
Enable MSAA write when writing into MSAA frame buffer.
This flag is ignored when not writing into MSAA frame buffer.
*/
alias State_ = ulong;
enum State: State_{
	msaa                  = 0x0100_0000_0000_0000, ///Enable MSAA rasterization.
	lineAA                = 0x0200_0000_0000_0000, ///Enable line AA rasterization.
	conservativeRaster    = 0x0400_0000_0000_0000, ///Enable conservative rasterization.
	none                  = 0x0000_0000_0000_0000, ///No state.
	frontCCW              = 0x0000_0080_0000_0000, ///Front counter-clockwise (default is clockwise).
	frontACW              = frontCCW,
	blendIndependent      = 0x0000_0004_0000_0000, ///Enable blend independent.
	blendAlphaToCoverage  = 0x0000_0008_0000_0000, ///Enable alpha to coverage.
	/**
	Default state is write to RGB, alpha, and depth with depth test less enabled, with clockwise
	culling and MSAA (when writing into MSAA frame buffer, otherwise this flag is ignored).
	*/
	default_              = StateWrite.rgb | StateWrite.a | StateWrite.z | StateDepthTest.less | StateCull.cw | State.msaa,
	mask                  = 0xFFFF_FFFF_FFFF_FFFF, ///State bit mask
}

///Do not use!
alias StateReserved_ = ulong;
enum StateReserved: StateReserved_{
	shift  = 61,
	mask   = 0xE000_0000_0000_0000,
}

///Set stencil ref value.
alias StencilFuncRef_ = uint;
enum StencilFuncRef: StencilFuncRef_{
	shift  = 0,
	mask   = 0x0000_00FF,
}
StencilFuncRef_ toStencilFuncRef(uint v) nothrow @nogc pure @safe{ return (v << StencilFuncRef.shift) & StencilFuncRef.mask; }

///Set stencil rmask value.
alias StencilFuncRMask_ = uint;
enum StencilFuncRMask: StencilFuncRMask_{
	shift  = 8,
	mask   = 0x0000_FF00,
}
StencilFuncRMask_ toStencilFuncRMask(uint v) nothrow @nogc pure @safe{ return (v << StencilFuncRMask.shift) & StencilFuncRMask.mask; }

alias Stencil_ = uint;
enum Stencil: Stencil_{
	none     = 0x0000_0000,
	mask     = 0xFFFF_FFFF,
	default_ = 0x0000_0000,
}

alias StencilTest_ = uint;
enum StencilTest: StencilTest_{
	less      = 0x0001_0000, ///Enable stencil test, less.
	lEqual    = 0x0002_0000, ///Enable stencil test, less or equal.
	equal     = 0x0003_0000, ///Enable stencil test, equal.
	gEqual    = 0x0004_0000, ///Enable stencil test, greater or equal.
	greater   = 0x0005_0000, ///Enable stencil test, greater.
	notEqual  = 0x0006_0000, ///Enable stencil test, not equal.
	never     = 0x0007_0000, ///Enable stencil test, never.
	always    = 0x0008_0000, ///Enable stencil test, always.
	shift     = 16, ///Stencil test bit shift
	mask      = 0x000F_0000, ///Stencil test bit mask
}

alias StencilOpFailS_ = uint;
enum StencilOpFailS: StencilOpFailS_{
	zero     = 0x0000_0000, ///Zero.
	keep     = 0x0010_0000, ///Keep.
	replace  = 0x0020_0000, ///Replace.
	incr     = 0x0030_0000, ///Increment and wrap.
	incrSat  = 0x0040_0000, ///Increment and clamp.
	decr     = 0x0050_0000, ///Decrement and wrap.
	decrSat  = 0x0060_0000, ///Decrement and clamp.
	invert   = 0x0070_0000, ///Invert.
	shift    = 20, ///Stencil operation fail bit shift
	mask     = 0x00F0_0000, ///Stencil operation fail bit mask
}

alias StencilOpFailZ_ = uint;
enum StencilOpFailZ: StencilOpFailZ_{
	zero     = 0x0000_0000, ///Zero.
	keep     = 0x0100_0000, ///Keep.
	replace  = 0x0200_0000, ///Replace.
	incr     = 0x0300_0000, ///Increment and wrap.
	incrSat  = 0x0400_0000, ///Increment and clamp.
	decr     = 0x0500_0000, ///Decrement and wrap.
	decrSat  = 0x0600_0000, ///Decrement and clamp.
	invert   = 0x0700_0000, ///Invert.
	shift    = 24, ///Stencil operation depth fail bit shift
	mask     = 0x0F00_0000, ///Stencil operation depth fail bit mask
}

alias StencilOpPassZ_ = uint;
enum StencilOpPassZ: StencilOpPassZ_{
	zero     = 0x0000_0000, ///Zero.
	keep     = 0x1000_0000, ///Keep.
	replace  = 0x2000_0000, ///Replace.
	incr     = 0x3000_0000, ///Increment and wrap.
	incrSat  = 0x4000_0000, ///Increment and clamp.
	decr     = 0x5000_0000, ///Decrement and wrap.
	decrSat  = 0x6000_0000, ///Decrement and clamp.
	invert   = 0x7000_0000, ///Invert.
	shift    = 28, ///Stencil operation depth pass bit shift
	mask     = 0xF000_0000, ///Stencil operation depth pass bit mask
}

alias Clear_ = ushort;
enum Clear: Clear_{
	none              = 0x0000, ///No clear flags.
	color             = 0x0001, ///Clear color.
	colour            = color,
	depth             = 0x0002, ///Clear depth.
	stencil           = 0x0004, ///Clear stencil.
	discardColor0     = 0x0008, ///Discard frame buffer attachment 0.
	discardColour0    = discardColor0,
	discardColor1     = 0x0010, ///Discard frame buffer attachment 1.
	discardColour1    = discardColor1,
	discardColor2     = 0x0020, ///Discard frame buffer attachment 2.
	discardColour2    = discardColor2,
	discardColor3     = 0x0040, ///Discard frame buffer attachment 3.
	discardColour3    = discardColor3,
	discardColor4     = 0x0080, ///Discard frame buffer attachment 4.
	discardColour4    = discardColor4,
	discardColor5     = 0x0100, ///Discard frame buffer attachment 5.
	discardColour5    = discardColor5,
	discardColor6     = 0x0200, ///Discard frame buffer attachment 6.
	discardColour6    = discardColor6,
	discardColor7     = 0x0400, ///Discard frame buffer attachment 7.
	discardColour7    = discardColor7,
	discardDepth      = 0x0800, ///Discard frame buffer depth attachment.
	discardStencil    = 0x1000, ///Discard frame buffer stencil attachment.
	discardColorMask  = 0x07F8,
	discardColourMask = discardColorMask,
	discardMask       = 0x1FF8,
}

/**
Rendering state discard. When state is preserved in submit, rendering states can be discarded
on a finer grain.
*/
alias Discard_ = ubyte;
enum Discard: Discard_{
	none           = 0x00, ///Preserve everything.
	bindings       = 0x01, ///Discard texture sampler and buffer bindings.
	indexBuffer    = 0x02, ///Discard index buffer.
	instanceData   = 0x04, ///Discard instance data.
	state          = 0x08, ///Discard state and uniform bindings.
	transform      = 0x10, ///Discard transform.
	vertexStreams  = 0x20, ///Discard vertex streams.
	all            = 0xFF, ///Discard all states.
}

alias Debug_ = uint;
enum Debug: Debug_{
	none       = 0x0000_0000, ///No debug.
	wireframe  = 0x0000_0001, ///Enable wireframe for all primitives.
	/**
	Enable infinitely fast hardware test. No draw calls will be submitted to driver.
	It's useful when profiling to quickly assess bottleneck between CPU and GPU.
	*/
	ifh        = 0x0000_0002,
	stats      = 0x0000_0004, ///Enable statistics display.
	text       = 0x0000_0008, ///Enable debug text display.
	profiler   = 0x0000_0010, ///Enable profiler. This causes per-view statistics to be collected, available through `bgfx::Stats::ViewStats`. This is unrelated to the profiler functions in `bgfx::CallbackI`.
}

alias BufferComputeFormat_ = ushort;
enum BufferComputeFormat: BufferComputeFormat_{
	_8x1   = 0x0001, ///1 8-bit value
	_8x2   = 0x0002, ///2 8-bit values
	_8x4   = 0x0003, ///4 8-bit values
	_16x1  = 0x0004, ///1 16-bit value
	_16x2  = 0x0005, ///2 16-bit values
	_16x4  = 0x0006, ///4 16-bit values
	_32x1  = 0x0007, ///1 32-bit value
	_32x2  = 0x0008, ///2 32-bit values
	_32x4  = 0x0009, ///4 32-bit values
	shift  = 0,
	mask   = 0x000F,
}

alias BufferComputeType_ = ushort;
enum BufferComputeType: BufferComputeType_{
	int_   = 0x0010, ///Type `int`.
	uint_  = 0x0020, ///Type `uint`.
	float_ = 0x0030, ///Type `float`.
	shift  = 4,
	mask   = 0x0030,
}

alias Buffer_ = ushort;
enum Buffer: Buffer_{
	none              = 0x0000,
	computeRead       = 0x0100, ///Buffer will be read by shader.
	computeWrite      = 0x0200, ///Buffer will be used for writing.
	drawIndirect      = 0x0400, ///Buffer will be used for storing draw indirect commands.
	allowResize       = 0x0800, ///Allow dynamic index/vertex buffer resize during update.
	index32           = 0x1000, ///Index buffer contains 32-bit indices.
	computeReadWrite  = 0x0300,
}

alias Texture_ = ulong;
enum Texture: Texture_{
	none          = 0x0000_0000_0000_0000,
	msaaSample    = 0x0000_0008_0000_0000, ///Texture will be used for MSAA sampling.
	rt            = 0x0000_0010_0000_0000, ///Render target no MSAA.
	computeWrite  = 0x0000_1000_0000_0000, ///Texture will be used for compute write.
	srgb          = 0x0000_2000_0000_0000, ///Sample texture as sRGB.
	blitDst       = 0x0000_4000_0000_0000, ///Texture will be used as blit destination.
	readBack      = 0x0000_8000_0000_0000, ///Texture will be used for read back from GPU.
}

alias TextureRTMSAA_ = ulong;
enum TextureRTMSAA: TextureRTMSAA_{
	x2     = 0x0000_0020_0000_0000, ///Render target MSAAx2 mode.
	x4     = 0x0000_0030_0000_0000, ///Render target MSAAx4 mode.
	x8     = 0x0000_0040_0000_0000, ///Render target MSAAx8 mode.
	x16    = 0x0000_0050_0000_0000, ///Render target MSAAx16 mode.
	shift  = 36,
	mask   = 0x0000_0070_0000_0000,
}

alias TextureRT_ = ulong;
enum TextureRT: TextureRT_{
	writeOnly  = 0x0000_0080_0000_0000, ///Render target will be used for writing
	shift      = 36,
	mask       = 0x0000_00F0_0000_0000,
}

///Sampler flags.
alias SamplerU_ = uint;
enum SamplerU: SamplerU_{
	mirror  = 0x0000_0001, ///Wrap U mode: Mirror
	clamp   = 0x0000_0002, ///Wrap U mode: Clamp
	border  = 0x0000_0003, ///Wrap U mode: Border
	shift   = 0,
	mask    = 0x0000_0003,
}

alias SamplerV_ = uint;
enum SamplerV: SamplerV_{
	mirror  = 0x0000_0004, ///Wrap V mode: Mirror
	clamp   = 0x0000_0008, ///Wrap V mode: Clamp
	border  = 0x0000_000C, ///Wrap V mode: Border
	shift   = 2,
	mask    = 0x0000_000C,
}

alias SamplerW_ = uint;
enum SamplerW: SamplerW_{
	mirror  = 0x0000_0010, ///Wrap W mode: Mirror
	clamp   = 0x0000_0020, ///Wrap W mode: Clamp
	border  = 0x0000_0030, ///Wrap W mode: Border
	shift   = 4,
	mask    = 0x0000_0030,
}

alias SamplerMin_ = uint;
enum SamplerMin: SamplerMin_{
	point        = 0x0000_0040, ///Min sampling mode: Point
	anisotropic  = 0x0000_0080, ///Min sampling mode: Anisotropic
	shift        = 6,
	mask         = 0x0000_00C0,
}

alias SamplerMag_ = uint;
enum SamplerMag: SamplerMag_{
	point        = 0x0000_0100, ///Mag sampling mode: Point
	anisotropic  = 0x0000_0200, ///Mag sampling mode: Anisotropic
	shift        = 8,
	mask         = 0x0000_0300,
}

alias SamplerMIP_ = uint;
enum SamplerMIP: SamplerMIP_{
	point  = 0x0000_0400, ///Mip sampling mode: Point
	shift  = 10,
	mask   = 0x0000_0400,
}

alias SamplerCompare_ = uint;
enum SamplerCompare: SamplerCompare_{
	less      = 0x0001_0000, ///Compare when sampling depth texture: less.
	lEqual    = 0x0002_0000, ///Compare when sampling depth texture: less or equal.
	equal     = 0x0003_0000, ///Compare when sampling depth texture: equal.
	gEqual    = 0x0004_0000, ///Compare when sampling depth texture: greater or equal.
	greater   = 0x0005_0000, ///Compare when sampling depth texture: greater.
	notEqual  = 0x0006_0000, ///Compare when sampling depth texture: not equal.
	never     = 0x0007_0000, ///Compare when sampling depth texture: never.
	always    = 0x0008_0000, ///Compare when sampling depth texture: always.
	shift     = 16,
	mask      = 0x000F_0000,
}

alias SamplerBorderColor_ = uint;
enum SamplerBorderColor: SamplerBorderColor_{
	shift  = 24,
	mask   = 0x0F00_0000,
}
alias SamplerBorderColour = SamplerBorderColor;
SamplerBorderColor_ toSamplerBorderColor(uint v) nothrow @nogc pure @safe{ return (v << SamplerBorderColor.shift) & SamplerBorderColor.mask; }
alias toSamplerBorderColour = toSamplerBorderColor;

alias SamplerReserved_ = uint;
enum SamplerReserved: SamplerReserved_{
	shift  = 28,
	mask   = 0xF000_0000,
}

alias Sampler_ = uint;
enum Sampler: Sampler_{
	none           = 0x0000_0000,
	sampleStencil  = 0x0010_0000, ///Sample stencil instead of depth.
	point          = SamplerMin.point | SamplerMag.point | SamplerMIP.point,
	uvwMirror      = SamplerU.mirror | SamplerV.mirror | SamplerW.mirror,
	uvwClamp       = SamplerU.clamp | SamplerV.clamp | SamplerW.clamp,
	uvwBorder      = SamplerU.border | SamplerV.border | SamplerW.border,
	bitsMask       = SamplerU.mask | SamplerV.mask | SamplerW.mask | SamplerMin.mask | SamplerMag.mask | SamplerMIP.mask | SamplerCompare.mask,
}

alias ResetMSAA_ = uint;
enum ResetMSAA: ResetMSAA_{
	x2     = 0x0000_0010, ///Enable 2x MSAA.
	x4     = 0x0000_0020, ///Enable 4x MSAA.
	x8     = 0x0000_0030, ///Enable 8x MSAA.
	x16    = 0x0000_0040, ///Enable 16x MSAA.
	shift  = 4,
	mask   = 0x0000_0070,
}

alias Reset_ = uint;
enum Reset: Reset_{
	none                   = 0x0000_0000, ///No reset flags.
	fullscreen             = 0x0000_0001, ///Not supported yet.
	vsync                  = 0x0000_0080, ///Enable V-Sync.
	maxAnisotropy          = 0x0000_0100, ///Turn on/off max anisotropy.
	capture                = 0x0000_0200, ///Begin screen capture.
	flushAfterRender       = 0x0000_2000, ///Flush rendering after submitting to GPU.
	/**
	This flag specifies where flip occurs. Default behaviour is that flip occurs
	before rendering new frame. This flag only has effect when `BGFX_CONFIG_MULTITHREADED=0`.
	*/
	flipAfterRender        = 0x0000_4000,
	srgbBackbuffer         = 0x0000_8000, ///Enable sRGB backbuffer.
	hdr10                  = 0x0001_0000, ///Enable HDR10 rendering.
	hiDPI                  = 0x0002_0000, ///Enable HiDPI rendering.
	depthClamp             = 0x0004_0000, ///Enable depth clamp.
	suspend                = 0x0008_0000, ///Suspend rendering.
	transparentBackbuffer  = 0x0010_0000, ///Transparent backbuffer. Availability depends on: `BGFX_CAPS_TRANSPARENT_BACKBUFFER`.
}

alias ResetFullscreen_ = uint;
enum ResetFullscreen: ResetFullscreen_{
	shift  = 0,
	mask   = 0x0000_0001,
}

alias ResetReserved_ = uint;
enum ResetReserved: ResetReserved_{
	shift  = 31, ///Internal bit shift
	mask   = 0x8000_0000, ///Internal bit mask
}

alias CapFlags_ = ulong;
enum CapFlags: CapFlags_{
	alphaToCoverage         = 0x0000_0000_0000_0001, ///Alpha to coverage is supported.
	blendIndependent        = 0x0000_0000_0000_0002, ///Blend independent is supported.
	compute                 = 0x0000_0000_0000_0004, ///Compute shaders are supported.
	conservativeRaster      = 0x0000_0000_0000_0008, ///Conservative rasterization is supported.
	drawIndirect            = 0x0000_0000_0000_0010, ///Draw indirect is supported.
	drawIndirectCount       = 0x0000_0000_0000_0020, ///Draw indirect with indirect count is supported.
	fragmentDepth           = 0x0000_0000_0000_0040, ///Fragment depth is available in fragment shader.
	fragmentOrdering        = 0x0000_0000_0000_0080, ///Fragment ordering is available in fragment shader.
	graphicsDebugger        = 0x0000_0000_0000_0100, ///Graphics debugger is present.
	hdr10                   = 0x0000_0000_0000_0200, ///HDR10 rendering is supported.
	hiDPI                   = 0x0000_0000_0000_0400, ///HiDPI rendering is supported.
	imageRW                 = 0x0000_0000_0000_0800, ///Image Read/Write is supported.
	index32                 = 0x0000_0000_0000_1000, ///32-bit indices are supported.
	instancing              = 0x0000_0000_0000_2000, ///Instancing is supported.
	occlusionQuery          = 0x0000_0000_0000_4000, ///Occlusion query is supported.
	primitiveID             = 0x0000_0000_0000_8000, ///PrimitiveID is available in fragment shader.
	rendererMultithreaded   = 0x0000_0000_0001_0000, ///Renderer is on separate thread.
	swapChain               = 0x0000_0000_0002_0000, ///Multiple windows are supported.
	textureBlit             = 0x0000_0000_0004_0000, ///Texture blit is supported.
	textureCompareLEqual    = 0x0000_0000_0008_0000, ///Texture compare less equal mode is supported.
	textureCompareReserved  = 0x0000_0000_0010_0000,
	textureCubeArray        = 0x0000_0000_0020_0000, ///Cubemap texture array is supported.
	textureDirectAccess     = 0x0000_0000_0040_0000, ///CPU direct access to GPU texture memory.
	textureReadBack         = 0x0000_0000_0080_0000, ///Read-back texture is supported.
	texture2DArray          = 0x0000_0000_0100_0000, ///2D texture array is supported.
	texture3D               = 0x0000_0000_0200_0000, ///3D textures are supported.
	transparentBackbuffer   = 0x0000_0000_0400_0000, ///Transparent back buffer supported.
	vertexAttribHalf        = 0x0000_0000_0800_0000, ///Vertex attribute half-float is supported.
	vertexAttribUint10      = 0x0000_0000_1000_0000, ///Vertex attribute 10_10_10_2 is supported.
	vertexID                = 0x0000_0000_2000_0000, ///Rendering with VertexID only is supported.
	viewportLayerArray      = 0x0000_0000_4000_0000, ///Viewport layer is available in vertex shader.
	textureCompareAll       = 0x0000_0000_0018_0000, ///All texture compare modes are supported.
}

alias CapsFormat_ = uint;
enum CapsFormat: CapsFormat_{
	textureNone             = 0x0000_0000, ///Texture format is not supported.
	texture2D               = 0x0000_0001, ///Texture format is supported.
	texture2DSRGB           = 0x0000_0002, ///Texture as sRGB format is supported.
	texture2DEmulated       = 0x0000_0004, ///Texture format is emulated.
	texture3D               = 0x0000_0008, ///Texture format is supported.
	texture3DSRGB           = 0x0000_0010, ///Texture as sRGB format is supported.
	texture3DEmulated       = 0x0000_0020, ///Texture format is emulated.
	textureCube             = 0x0000_0040, ///Texture format is supported.
	textureCubeSRGB         = 0x0000_0080, ///Texture as sRGB format is supported.
	textureCubeEmulated     = 0x0000_0100, ///Texture format is emulated.
	textureVertex           = 0x0000_0200, ///Texture format can be used from vertex shader.
	textureImageRead        = 0x0000_0400, ///Texture format can be used as image and read from.
	textureImageWrite       = 0x0000_0800, ///Texture format can be used as image and written to.
	textureFramebuffer      = 0x0000_1000, ///Texture format can be used as frame buffer.
	textureFramebufferMSAA  = 0x0000_2000, ///Texture format can be used as MSAA frame buffer.
	textureMSAA             = 0x0000_4000, ///Texture can be sampled as MSAA.
	textureMIPAutogen       = 0x0000_8000, ///Texture format supports auto-generated mips.
}

alias Resolve_ = ubyte;
enum Resolve: Resolve_{
	none         = 0x00, ///No resolve flags.
	autoGenMIPs  = 0x01, ///Auto-generate mip maps on resolve.
}

alias PCIID_ = ushort;
enum PCIID: PCIID_{
	none                = 0x0000, ///Autoselect adapter.
	softwareRasterizer  = 0x0001, ///Software rasterizer.
	softwareRasteriser  = softwareRasterizer,
	amd                 = 0x1002, ///AMD adapter.
	apple               = 0x106B, ///Apple adapter.
	intel               = 0x8086, ///Intel adapter.
	nvidia              = 0x10DE, ///nVidia adapter.
	microsoft           = 0x1414, ///Microsoft adapter.
	arm                 = 0x13B5, ///ARM adapter.
}

alias CubeMap_ = ubyte;
enum CubeMap: CubeMap_{
	positiveX  = 0x00, ///Cubemap +x.
	negativeX  = 0x01, ///Cubemap -x.
	positiveY  = 0x02, ///Cubemap +y.
	negativeY  = 0x03, ///Cubemap -y.
	positiveZ  = 0x04, ///Cubemap +z.
	negativeZ  = 0x05, ///Cubemap -z.
}

///Fatal error enum.
enum Fatal: bgfx.fakeenum.Fatal.Enum{
	debugCheck = bgfx.fakeenum.Fatal.Enum.debugCheck,
	invalidShader = bgfx.fakeenum.Fatal.Enum.invalidShader,
	unableToInitialize = bgfx.fakeenum.Fatal.Enum.unableToInitialize,
	unableToInitialise = bgfx.fakeenum.Fatal.Enum.unableToInitialize,
	unableToCreateTexture = bgfx.fakeenum.Fatal.Enum.unableToCreateTexture,
	deviceLost = bgfx.fakeenum.Fatal.Enum.deviceLost,
	count = bgfx.fakeenum.Fatal.Enum.count,
}

///Renderer backend type enum.
enum RendererType: bgfx.fakeenum.RendererType.Enum{
	noop = bgfx.fakeenum.RendererType.Enum.noop,
	agc = bgfx.fakeenum.RendererType.Enum.agc,
	direct3D11 = bgfx.fakeenum.RendererType.Enum.direct3D11,
	direct3D12 = bgfx.fakeenum.RendererType.Enum.direct3D12,
	gnm = bgfx.fakeenum.RendererType.Enum.gnm,
	metal = bgfx.fakeenum.RendererType.Enum.metal,
	nvn = bgfx.fakeenum.RendererType.Enum.nvn,
	openGLES = bgfx.fakeenum.RendererType.Enum.openGLES,
	openGL = bgfx.fakeenum.RendererType.Enum.openGL,
	vulkan = bgfx.fakeenum.RendererType.Enum.vulkan,
	count = bgfx.fakeenum.RendererType.Enum.count,
}

///Access mode enum.
enum Access: bgfx.fakeenum.Access.Enum{
	read = bgfx.fakeenum.Access.Enum.read,
	write = bgfx.fakeenum.Access.Enum.write,
	readWrite = bgfx.fakeenum.Access.Enum.readWrite,
	count = bgfx.fakeenum.Access.Enum.count,
}

///Vertex attribute enum.
enum Attrib: bgfx.fakeenum.Attrib.Enum{
	position = bgfx.fakeenum.Attrib.Enum.position,
	normal = bgfx.fakeenum.Attrib.Enum.normal,
	tangent = bgfx.fakeenum.Attrib.Enum.tangent,
	bitangent = bgfx.fakeenum.Attrib.Enum.bitangent,
	color0 = bgfx.fakeenum.Attrib.Enum.color0,
	colour0 = bgfx.fakeenum.Attrib.Enum.color0,
	color1 = bgfx.fakeenum.Attrib.Enum.color1,
	colour1 = bgfx.fakeenum.Attrib.Enum.color1,
	color2 = bgfx.fakeenum.Attrib.Enum.color2,
	colour2 = bgfx.fakeenum.Attrib.Enum.color2,
	color3 = bgfx.fakeenum.Attrib.Enum.color3,
	colour3 = bgfx.fakeenum.Attrib.Enum.color3,
	indices = bgfx.fakeenum.Attrib.Enum.indices,
	weight = bgfx.fakeenum.Attrib.Enum.weight,
	texCoord0 = bgfx.fakeenum.Attrib.Enum.texCoord0,
	texCoord1 = bgfx.fakeenum.Attrib.Enum.texCoord1,
	texCoord2 = bgfx.fakeenum.Attrib.Enum.texCoord2,
	texCoord3 = bgfx.fakeenum.Attrib.Enum.texCoord3,
	texCoord4 = bgfx.fakeenum.Attrib.Enum.texCoord4,
	texCoord5 = bgfx.fakeenum.Attrib.Enum.texCoord5,
	texCoord6 = bgfx.fakeenum.Attrib.Enum.texCoord6,
	texCoord7 = bgfx.fakeenum.Attrib.Enum.texCoord7,
	count = bgfx.fakeenum.Attrib.Enum.count,
}

///Vertex attribute type enum.
enum AttribType: bgfx.fakeenum.AttribType.Enum{
	uint8 = bgfx.fakeenum.AttribType.Enum.uint8,
	uint10 = bgfx.fakeenum.AttribType.Enum.uint10,
	int16 = bgfx.fakeenum.AttribType.Enum.int16,
	half = bgfx.fakeenum.AttribType.Enum.half,
	float_ = bgfx.fakeenum.AttribType.Enum.float_,
	count = bgfx.fakeenum.AttribType.Enum.count,
}

/**
Texture format enum.
Notation:
      RGBA16S
      ^   ^ ^
      |   | +-- [ ]Unorm
      |   |     [F]loat
      |   |     [S]norm
      |   |     [I]nt
      |   |     [U]int
      |   +---- Number of bits per component
      +-------- Components
@attention Availability depends on Caps (see: formats).
*/
enum TextureFormat: bgfx.fakeenum.TextureFormat.Enum{
	bc1 = bgfx.fakeenum.TextureFormat.Enum.bc1,
	bc2 = bgfx.fakeenum.TextureFormat.Enum.bc2,
	bc3 = bgfx.fakeenum.TextureFormat.Enum.bc3,
	bc4 = bgfx.fakeenum.TextureFormat.Enum.bc4,
	bc5 = bgfx.fakeenum.TextureFormat.Enum.bc5,
	bc6h = bgfx.fakeenum.TextureFormat.Enum.bc6h,
	bc7 = bgfx.fakeenum.TextureFormat.Enum.bc7,
	etc1 = bgfx.fakeenum.TextureFormat.Enum.etc1,
	etc2 = bgfx.fakeenum.TextureFormat.Enum.etc2,
	etc2a = bgfx.fakeenum.TextureFormat.Enum.etc2a,
	etc2a1 = bgfx.fakeenum.TextureFormat.Enum.etc2a1,
	ptc12 = bgfx.fakeenum.TextureFormat.Enum.ptc12,
	ptc14 = bgfx.fakeenum.TextureFormat.Enum.ptc14,
	ptc12a = bgfx.fakeenum.TextureFormat.Enum.ptc12a,
	ptc14a = bgfx.fakeenum.TextureFormat.Enum.ptc14a,
	ptc22 = bgfx.fakeenum.TextureFormat.Enum.ptc22,
	ptc24 = bgfx.fakeenum.TextureFormat.Enum.ptc24,
	atc = bgfx.fakeenum.TextureFormat.Enum.atc,
	atce = bgfx.fakeenum.TextureFormat.Enum.atce,
	atci = bgfx.fakeenum.TextureFormat.Enum.atci,
	astc4x4 = bgfx.fakeenum.TextureFormat.Enum.astc4x4,
	astc5x4 = bgfx.fakeenum.TextureFormat.Enum.astc5x4,
	astc5x5 = bgfx.fakeenum.TextureFormat.Enum.astc5x5,
	astc6x5 = bgfx.fakeenum.TextureFormat.Enum.astc6x5,
	astc6x6 = bgfx.fakeenum.TextureFormat.Enum.astc6x6,
	astc8x5 = bgfx.fakeenum.TextureFormat.Enum.astc8x5,
	astc8x6 = bgfx.fakeenum.TextureFormat.Enum.astc8x6,
	astc8x8 = bgfx.fakeenum.TextureFormat.Enum.astc8x8,
	astc10x5 = bgfx.fakeenum.TextureFormat.Enum.astc10x5,
	astc10x6 = bgfx.fakeenum.TextureFormat.Enum.astc10x6,
	astc10x8 = bgfx.fakeenum.TextureFormat.Enum.astc10x8,
	astc10x10 = bgfx.fakeenum.TextureFormat.Enum.astc10x10,
	astc12x10 = bgfx.fakeenum.TextureFormat.Enum.astc12x10,
	astc12x12 = bgfx.fakeenum.TextureFormat.Enum.astc12x12,
	unknown = bgfx.fakeenum.TextureFormat.Enum.unknown,
	r1 = bgfx.fakeenum.TextureFormat.Enum.r1,
	a8 = bgfx.fakeenum.TextureFormat.Enum.a8,
	r8 = bgfx.fakeenum.TextureFormat.Enum.r8,
	r8i = bgfx.fakeenum.TextureFormat.Enum.r8i,
	r8u = bgfx.fakeenum.TextureFormat.Enum.r8u,
	r8s = bgfx.fakeenum.TextureFormat.Enum.r8s,
	r16 = bgfx.fakeenum.TextureFormat.Enum.r16,
	r16i = bgfx.fakeenum.TextureFormat.Enum.r16i,
	r16u = bgfx.fakeenum.TextureFormat.Enum.r16u,
	r16f = bgfx.fakeenum.TextureFormat.Enum.r16f,
	r16s = bgfx.fakeenum.TextureFormat.Enum.r16s,
	r32i = bgfx.fakeenum.TextureFormat.Enum.r32i,
	r32u = bgfx.fakeenum.TextureFormat.Enum.r32u,
	r32f = bgfx.fakeenum.TextureFormat.Enum.r32f,
	rg8 = bgfx.fakeenum.TextureFormat.Enum.rg8,
	rg8i = bgfx.fakeenum.TextureFormat.Enum.rg8i,
	rg8u = bgfx.fakeenum.TextureFormat.Enum.rg8u,
	rg8s = bgfx.fakeenum.TextureFormat.Enum.rg8s,
	rg16 = bgfx.fakeenum.TextureFormat.Enum.rg16,
	rg16i = bgfx.fakeenum.TextureFormat.Enum.rg16i,
	rg16u = bgfx.fakeenum.TextureFormat.Enum.rg16u,
	rg16f = bgfx.fakeenum.TextureFormat.Enum.rg16f,
	rg16s = bgfx.fakeenum.TextureFormat.Enum.rg16s,
	rg32i = bgfx.fakeenum.TextureFormat.Enum.rg32i,
	rg32u = bgfx.fakeenum.TextureFormat.Enum.rg32u,
	rg32f = bgfx.fakeenum.TextureFormat.Enum.rg32f,
	rgb8 = bgfx.fakeenum.TextureFormat.Enum.rgb8,
	rgb8i = bgfx.fakeenum.TextureFormat.Enum.rgb8i,
	rgb8u = bgfx.fakeenum.TextureFormat.Enum.rgb8u,
	rgb8s = bgfx.fakeenum.TextureFormat.Enum.rgb8s,
	rgb9e5f = bgfx.fakeenum.TextureFormat.Enum.rgb9e5f,
	bgra8 = bgfx.fakeenum.TextureFormat.Enum.bgra8,
	rgba8 = bgfx.fakeenum.TextureFormat.Enum.rgba8,
	rgba8i = bgfx.fakeenum.TextureFormat.Enum.rgba8i,
	rgba8u = bgfx.fakeenum.TextureFormat.Enum.rgba8u,
	rgba8s = bgfx.fakeenum.TextureFormat.Enum.rgba8s,
	rgba16 = bgfx.fakeenum.TextureFormat.Enum.rgba16,
	rgba16i = bgfx.fakeenum.TextureFormat.Enum.rgba16i,
	rgba16u = bgfx.fakeenum.TextureFormat.Enum.rgba16u,
	rgba16f = bgfx.fakeenum.TextureFormat.Enum.rgba16f,
	rgba16s = bgfx.fakeenum.TextureFormat.Enum.rgba16s,
	rgba32i = bgfx.fakeenum.TextureFormat.Enum.rgba32i,
	rgba32u = bgfx.fakeenum.TextureFormat.Enum.rgba32u,
	rgba32f = bgfx.fakeenum.TextureFormat.Enum.rgba32f,
	b5g6r5 = bgfx.fakeenum.TextureFormat.Enum.b5g6r5,
	r5g6b5 = bgfx.fakeenum.TextureFormat.Enum.r5g6b5,
	bgra4 = bgfx.fakeenum.TextureFormat.Enum.bgra4,
	rgba4 = bgfx.fakeenum.TextureFormat.Enum.rgba4,
	bgr5a1 = bgfx.fakeenum.TextureFormat.Enum.bgr5a1,
	rgb5a1 = bgfx.fakeenum.TextureFormat.Enum.rgb5a1,
	rgb10a2 = bgfx.fakeenum.TextureFormat.Enum.rgb10a2,
	rg11b10f = bgfx.fakeenum.TextureFormat.Enum.rg11b10f,
	unknownDepth = bgfx.fakeenum.TextureFormat.Enum.unknownDepth,
	d16 = bgfx.fakeenum.TextureFormat.Enum.d16,
	d24 = bgfx.fakeenum.TextureFormat.Enum.d24,
	d24s8 = bgfx.fakeenum.TextureFormat.Enum.d24s8,
	d32 = bgfx.fakeenum.TextureFormat.Enum.d32,
	d16f = bgfx.fakeenum.TextureFormat.Enum.d16f,
	d24f = bgfx.fakeenum.TextureFormat.Enum.d24f,
	d32f = bgfx.fakeenum.TextureFormat.Enum.d32f,
	d0s8 = bgfx.fakeenum.TextureFormat.Enum.d0s8,
	count = bgfx.fakeenum.TextureFormat.Enum.count,
}

///Uniform type enum.
enum UniformType: bgfx.fakeenum.UniformType.Enum{
	sampler = bgfx.fakeenum.UniformType.Enum.sampler,
	end = bgfx.fakeenum.UniformType.Enum.end,
	vec4 = bgfx.fakeenum.UniformType.Enum.vec4,
	mat3 = bgfx.fakeenum.UniformType.Enum.mat3,
	mat4 = bgfx.fakeenum.UniformType.Enum.mat4,
	count = bgfx.fakeenum.UniformType.Enum.count,
}

///Backbuffer ratio enum.
enum BackbufferRatio: bgfx.fakeenum.BackbufferRatio.Enum{
	equal = bgfx.fakeenum.BackbufferRatio.Enum.equal,
	half = bgfx.fakeenum.BackbufferRatio.Enum.half,
	quarter = bgfx.fakeenum.BackbufferRatio.Enum.quarter,
	eighth = bgfx.fakeenum.BackbufferRatio.Enum.eighth,
	sixteenth = bgfx.fakeenum.BackbufferRatio.Enum.sixteenth,
	double_ = bgfx.fakeenum.BackbufferRatio.Enum.double_,
	count = bgfx.fakeenum.BackbufferRatio.Enum.count,
}

///Occlusion query result.
enum OcclusionQueryResult: bgfx.fakeenum.OcclusionQueryResult.Enum{
	invisible = bgfx.fakeenum.OcclusionQueryResult.Enum.invisible,
	visible = bgfx.fakeenum.OcclusionQueryResult.Enum.visible,
	noResult = bgfx.fakeenum.OcclusionQueryResult.Enum.noResult,
	count = bgfx.fakeenum.OcclusionQueryResult.Enum.count,
}

///Primitive topology.
enum Topology: bgfx.fakeenum.Topology.Enum{
	triList = bgfx.fakeenum.Topology.Enum.triList,
	triStrip = bgfx.fakeenum.Topology.Enum.triStrip,
	lineList = bgfx.fakeenum.Topology.Enum.lineList,
	lineStrip = bgfx.fakeenum.Topology.Enum.lineStrip,
	pointList = bgfx.fakeenum.Topology.Enum.pointList,
	count = bgfx.fakeenum.Topology.Enum.count,
}

///Topology conversion function.
enum TopologyConvert: bgfx.fakeenum.TopologyConvert.Enum{
	triListFlipWinding = bgfx.fakeenum.TopologyConvert.Enum.triListFlipWinding,
	triStripFlipWinding = bgfx.fakeenum.TopologyConvert.Enum.triStripFlipWinding,
	triListToLineList = bgfx.fakeenum.TopologyConvert.Enum.triListToLineList,
	triStripToTriList = bgfx.fakeenum.TopologyConvert.Enum.triStripToTriList,
	lineStripToLineList = bgfx.fakeenum.TopologyConvert.Enum.lineStripToLineList,
	count = bgfx.fakeenum.TopologyConvert.Enum.count,
}

///Topology sort order.
enum TopologySort: bgfx.fakeenum.TopologySort.Enum{
	directionFrontToBackMin = bgfx.fakeenum.TopologySort.Enum.directionFrontToBackMin,
	directionFrontToBackAvg = bgfx.fakeenum.TopologySort.Enum.directionFrontToBackAvg,
	directionFrontToBackMax = bgfx.fakeenum.TopologySort.Enum.directionFrontToBackMax,
	directionBackToFrontMin = bgfx.fakeenum.TopologySort.Enum.directionBackToFrontMin,
	directionBackToFrontAvg = bgfx.fakeenum.TopologySort.Enum.directionBackToFrontAvg,
	directionBackToFrontMax = bgfx.fakeenum.TopologySort.Enum.directionBackToFrontMax,
	distanceFrontToBackMin = bgfx.fakeenum.TopologySort.Enum.distanceFrontToBackMin,
	distanceFrontToBackAvg = bgfx.fakeenum.TopologySort.Enum.distanceFrontToBackAvg,
	distanceFrontToBackMax = bgfx.fakeenum.TopologySort.Enum.distanceFrontToBackMax,
	distanceBackToFrontMin = bgfx.fakeenum.TopologySort.Enum.distanceBackToFrontMin,
	distanceBackToFrontAvg = bgfx.fakeenum.TopologySort.Enum.distanceBackToFrontAvg,
	distanceBackToFrontMax = bgfx.fakeenum.TopologySort.Enum.distanceBackToFrontMax,
	count = bgfx.fakeenum.TopologySort.Enum.count,
}

///View mode sets draw call sort order.
enum ViewMode: bgfx.fakeenum.ViewMode.Enum{
	default_ = bgfx.fakeenum.ViewMode.Enum.default_,
	sequential = bgfx.fakeenum.ViewMode.Enum.sequential,
	depthAscending = bgfx.fakeenum.ViewMode.Enum.depthAscending,
	depthDescending = bgfx.fakeenum.ViewMode.Enum.depthDescending,
	count = bgfx.fakeenum.ViewMode.Enum.count,
}

///Native window handle type.
enum NativeWindowHandleType: bgfx.fakeenum.NativeWindowHandleType.Enum{
	default_ = bgfx.fakeenum.NativeWindowHandleType.Enum.default_,
	wayland = bgfx.fakeenum.NativeWindowHandleType.Enum.wayland,
	count = bgfx.fakeenum.NativeWindowHandleType.Enum.count,
}

///Render frame enum.
enum RenderFrame: bgfx.fakeenum.RenderFrame.Enum{
	noContext = bgfx.fakeenum.RenderFrame.Enum.noContext,
	render = bgfx.fakeenum.RenderFrame.Enum.render,
	timeout = bgfx.fakeenum.RenderFrame.Enum.timeout,
	exiting = bgfx.fakeenum.RenderFrame.Enum.exiting,
	count = bgfx.fakeenum.RenderFrame.Enum.count,
}

extern(C++, "bgfx") struct DynamicIndexBufferHandle{
	ushort idx;
}

extern(C++, "bgfx") struct DynamicVertexBufferHandle{
	ushort idx;
}

extern(C++, "bgfx") struct FrameBufferHandle{
	ushort idx;
}

extern(C++, "bgfx") struct IndexBufferHandle{
	ushort idx;
}

extern(C++, "bgfx") struct IndirectBufferHandle{
	ushort idx;
}

extern(C++, "bgfx") struct OcclusionQueryHandle{
	ushort idx;
}

extern(C++, "bgfx") struct ProgramHandle{
	ushort idx;
}

extern(C++, "bgfx") struct ShaderHandle{
	ushort idx;
}

extern(C++, "bgfx") struct TextureHandle{
	ushort idx;
}

extern(C++, "bgfx") struct UniformHandle{
	ushort idx;
}

extern(C++, "bgfx") struct VertexBufferHandle{
	ushort idx;
}

extern(C++, "bgfx") struct VertexLayoutHandle{
	ushort idx;
}

pragma(inline,true) nothrow @nogc pure @safe{
	StateBlend_ blendFuncSeparate(StateBlend_ srcRGB, StateBlend_ dstRGB, StateBlend_ srcA, StateBlend_ dstA){
		return (srcRGB | ((dstRGB) << 4)) | ((srcA | (dstA << 4)) << 8);
	}
	
	///Blend equation separate.
	StateBlendEquation_ blendEquationSeparate(StateBlendEquation_ equationRGB, StateBlendEquation_ equationA){
		return equationRGB | (equationA << 3);
	}
	
	///Blend function.
	StateBlend_ blendFunc(StateBlend_ src, StateBlend_ dst){ return blendFuncSeparate(src, dst, src, dst); }
	
	///Blend equation.
	StateBlendEquation_ blendEquation(StateBlendEquation_ equation){ return blendEquationSeparate(equation, equation); }
	
	///Utility predefined blend modes.
	enum StateBlendFunc: StateBlend_{
		///Additive blending.
		add = blendFunc(StateBlend.one, StateBlend.one),
		
		///Alpha blend.
		alpha = blendFunc(StateBlend.srcAlpha, StateBlend.invSrcAlpha),
		
		///Selects darker color of blend.
		darken = blendFunc(StateBlend.one, StateBlend.one) | blendEquation(StateBlendEquation.min),
		
		///Selects lighter color of blend.
		lighten = blendFunc(StateBlend.one, StateBlend.one) | blendEquation(StateBlendEquation.max),
		
		///Multiplies colors.
		multiply = blendFunc(StateBlend.dstColor, StateBlend.zero),
		
		///Opaque pixels will cover the pixels directly below them without any math or algorithm applied to them.
		normal = blendFunc(StateBlend.one, StateBlend.invSrcAlpha),
		
		///Multiplies the inverse of the blend and base colors.
		screen = blendFunc(StateBlend.one, StateBlend.invSrcColor),
		
		///Decreases the brightness of the base color based on the value of the blend color.
		linearBurn = blendFunc(StateBlend.dstColor, StateBlend.invDstColor) | blendEquation(StateBlendEquation.sub),
	}
	
	StateBlend_ blendFuncRTx(StateBlend_ src, StateBlend_ dst){
		return cast(uint)(src >> StateBlend.shift) | (cast(uint)(dst >> StateBlend.shift) << 4);
	}
	
	StateBlend_ blendFuncRTxE(StateBlend_ src, StateBlend_ dst, StateBlendEquation_ equation){
		return blendFuncRTx(src, dst) | (cast(uint)(equation >> StateBlendEquation.shift) << 8);
	}
	
	StateBlend_ blendFuncRT1(StateBlend_ src, StateBlend_ dst){ return blendFuncRTx(src, dst) <<  0; }
	StateBlend_ blendFuncRT2(StateBlend_ src, StateBlend_ dst){ return blendFuncRTx(src, dst) << 11; }
	StateBlend_ blendFuncRT3(StateBlend_ src, StateBlend_ dst){ return blendFuncRTx(src, dst) << 22; }
	
	StateBlend_ blendFuncRT1E(StateBlend_ src, StateBlend_ dst, StateBlendEquation_ equation){
		return blendFuncRTxE(src, dst, equation) <<  0;
	}
	StateBlend_ blendFuncRT2E(StateBlend_ src, StateBlend_ dst, StateBlendEquation_ equation){
		return blendFuncRTxE(src, dst, equation) << 11;
	}
	StateBlend_ blendFuncRT3E(StateBlend_ src, StateBlend_ dst, StateBlendEquation_ equation){
		return blendFuncRTxE(src, dst, equation) << 22;
	}
}

///Renderer capabilities.
extern(C++, "bgfx") struct Caps{
	///GPU info.
	extern(C++) struct GPU{
		ushort vendorID; ///Vendor PCI id. See `BGFX_PCI_ID_*`.
		ushort deviceID; ///Device id.
	}
	///Renderer runtime limits.
	extern(C++) struct Limits{
		uint maxDrawCalls; ///Maximum number of draw calls.
		uint maxBlits; ///Maximum number of blit calls.
		uint maxTextureSize; ///Maximum texture size.
		uint maxTextureLayers; ///Maximum texture layers.
		uint maxViews; ///Maximum number of views.
		uint maxFrameBuffers; ///Maximum number of frame buffer handles.
		uint maxFBAttachments; ///Maximum number of frame buffer attachments.
		uint maxPrograms; ///Maximum number of program handles.
		uint maxShaders; ///Maximum number of shader handles.
		uint maxTextures; ///Maximum number of texture handles.
		uint maxTextureSamplers; ///Maximum number of texture samplers.
		uint maxComputeBindings; ///Maximum number of compute bindings.
		uint maxVertexLayouts; ///Maximum number of vertex format layouts.
		uint maxVertexStreams; ///Maximum number of vertex streams.
		uint maxIndexBuffers; ///Maximum number of index buffer handles.
		uint maxVertexBuffers; ///Maximum number of vertex buffer handles.
		uint maxDynamicIndexBuffers; ///Maximum number of dynamic index buffer handles.
		uint maxDynamicVertexBuffers; ///Maximum number of dynamic vertex buffer handles.
		uint maxUniforms; ///Maximum number of uniform handles.
		uint maxOcclusionQueries; ///Maximum number of occlusion query handles.
		uint maxEncoders; ///Maximum number of encoder threads.
		uint minResourceCBSize; ///Minimum resource command buffer size.
		uint transientVBSize; ///Maximum transient vertex buffer size.
		uint transientIBSize; ///Maximum transient index buffer size.
	}
	
	RendererType rendererType; ///Renderer backend type. See: `bgfx::RendererType`
	
	/**
	Supported functionality.
	  @attention See `BGFX_CAPS_*` flags at https://bkaradzic.github.io/bgfx/bgfx.html#available-caps
	*/
	c_uint64 supported;
	ushort vendorID; ///Selected GPU vendor PCI id.
	ushort deviceID; ///Selected GPU device id.
	bool homogeneousDepth; ///True when NDC depth is in [-1, 1] range, otherwise its [0, 1].
	bool originBottomLeft; ///True when NDC origin is at bottom left.
	ubyte numGPUs; ///Number of enumerated GPUs.
	GPU[4] gpu; ///Enumerated GPUs.
	Limits limits; ///Renderer runtime limits.
	
	/**
	Supported texture format capabilities flags:
	  - `BGFX_CAPS_FORMAT_TEXTURE_NONE` - Texture format is not supported.
	  - `BGFX_CAPS_FORMAT_TEXTURE_2D` - Texture format is supported.
	  - `BGFX_CAPS_FORMAT_TEXTURE_2D_SRGB` - Texture as sRGB format is supported.
	  - `BGFX_CAPS_FORMAT_TEXTURE_2D_EMULATED` - Texture format is emulated.
	  - `BGFX_CAPS_FORMAT_TEXTURE_3D` - Texture format is supported.
	  - `BGFX_CAPS_FORMAT_TEXTURE_3D_SRGB` - Texture as sRGB format is supported.
	  - `BGFX_CAPS_FORMAT_TEXTURE_3D_EMULATED` - Texture format is emulated.
	  - `BGFX_CAPS_FORMAT_TEXTURE_CUBE` - Texture format is supported.
	  - `BGFX_CAPS_FORMAT_TEXTURE_CUBE_SRGB` - Texture as sRGB format is supported.
	  - `BGFX_CAPS_FORMAT_TEXTURE_CUBE_EMULATED` - Texture format is emulated.
	  - `BGFX_CAPS_FORMAT_TEXTURE_VERTEX` - Texture format can be used from vertex shader.
	  - `BGFX_CAPS_FORMAT_TEXTURE_IMAGE_READ` - Texture format can be used as image
	    and read from.
	  - `BGFX_CAPS_FORMAT_TEXTURE_IMAGE_WRITE` - Texture format can be used as image
	    and written to.
	  - `BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER` - Texture format can be used as frame
	    buffer.
	  - `BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA` - Texture format can be used as MSAA
	    frame buffer.
	  - `BGFX_CAPS_FORMAT_TEXTURE_MSAA` - Texture can be sampled as MSAA.
	  - `BGFX_CAPS_FORMAT_TEXTURE_MIP_AUTOGEN` - Texture format supports auto-generated
	    mips.
	*/
	ushort[TextureFormat.count] formats;
}

///Internal data.
extern(C++, "bgfx") struct InternalData{
	const(Caps)* caps; ///Renderer capabilities.
	void* context; ///GL context, or D3D device.
}

///Platform data.
extern(C++, "bgfx") struct PlatformData{
	void* ndt; ///Native display type (*nix specific).
	
	/**
	Native window handle. If `NULL`, bgfx will create a headless
	context/device, provided the rendering API supports it.
	*/
	void* nwh;
	
	/**
	GL context, D3D device, or Vulkan device. If `NULL`, bgfx
	will create context/device.
	*/
	void* context;
	
	/**
	GL back-buffer, or D3D render target view. If `NULL` bgfx will
	create back-buffer color surface.
	*/
	void* backBuffer;
	
	/**
	Backbuffer depth/stencil. If `NULL`, bgfx will create a back-buffer
	depth/stencil surface.
	*/
	void* backBufferDS;
	NativeWindowHandleType type; ///Handle type. Needed for platforms having more than one option.
}

///Backbuffer resolution and reset parameters.
extern(C++, "bgfx") struct Resolution{
	TextureFormat format; ///Backbuffer format.
	uint width; ///Backbuffer width.
	uint height; ///Backbuffer height.
	uint reset; ///Reset parameters.
	ubyte numBackBuffers; ///Number of back buffers.
	ubyte maxFrameLatency; ///Maximum frame latency.
	ubyte debugTextScale; ///Scale factor for debug text.
	extern(D) mixin(joinFnBinds((){
		FnBind[] ret = [
			{q{void}, q{this}, q{}, ext: `C++`},
		];
		return ret;
	}()));
}

///Initialization parameters used by `bgfx::init`.
extern(C++, "bgfx") struct Init{
	///Configurable runtime limits parameters.
	extern(C++) struct Limits{
		ushort maxEncoders; ///Maximum number of encoder threads.
		uint minResourceCBSize; ///Minimum resource command buffer size.
		uint transientVBSize; ///Maximum transient vertex buffer size.
		uint transientIBSize; ///Maximum transient index buffer size.
	}
	
	/**
	Select rendering backend. When set to RendererType::Count
	a default rendering backend will be selected appropriate to the platform.
	See: `bgfx::RendererType`
	*/
	RendererType type;
	
	/**
	Vendor PCI ID. If set to `BGFX_PCI_ID_NONE`, discrete and integrated
	GPUs will be prioritised.
	  - `BGFX_PCI_ID_NONE` - Autoselect adapter.
	  - `BGFX_PCI_ID_SOFTWARE_RASTERIZER` - Software rasterizer.
	  - `BGFX_PCI_ID_AMD` - AMD adapter.
	  - `BGFX_PCI_ID_APPLE` - Apple adapter.
	  - `BGFX_PCI_ID_INTEL` - Intel adapter.
	  - `BGFX_PCI_ID_NVIDIA` - NVIDIA adapter.
	  - `BGFX_PCI_ID_MICROSOFT` - Microsoft adapter.
	*/
	ushort vendorID;
	
	/**
	Device ID. If set to 0 it will select first device, or device with
	matching ID.
	*/
	ushort deviceID;
	c_uint64 capabilities; ///Capabilities initialization mask (default: UINT64_MAX).
	bool debug_; ///Enable device for debugging.
	bool profile; ///Enable device for profiling.
	PlatformData platformData; ///Platform data.
	Resolution resolution; ///Backbuffer resolution and reset parameters. See: `bgfx::Resolution`.
	Limits limits; ///Configurable runtime limits parameters.
	
	/**
	Provide application specific callback interface.
	See: `bgfx::CallbackI`
	*/
	void* callback;
	
	/**
	Custom allocator. When a custom allocator is not
	specified, bgfx uses the CRT allocator. Bgfx assumes
	custom allocator is thread safe.
	*/
	void* allocator;
	extern(D) mixin(joinFnBinds((){
		FnBind[] ret = [
			{q{void}, q{this}, q{}, ext: `C++`},
		];
		return ret;
	}()));
}

/**
Memory must be obtained by calling `bgfx::alloc`, `bgfx::copy`, or `bgfx::makeRef`.
@attention It is illegal to create this structure on stack and pass it to any bgfx API.
*/
extern(C++, "bgfx") struct Memory{
	ubyte* data; ///Pointer to data.
	uint size; ///Data size.
}

///Transient index buffer.
extern(C++, "bgfx") struct TransientIndexBuffer{
	ubyte* data; ///Pointer to data.
	uint size; ///Data size.
	uint startIndex; ///First index.
	IndexBufferHandle handle; ///Index buffer handle.
	bool isIndex16; ///Index buffer format is 16-bits if true, otherwise it is 32-bit.
}

///Transient vertex buffer.
extern(C++, "bgfx") struct TransientVertexBuffer{
	ubyte* data; ///Pointer to data.
	uint size; ///Data size.
	uint startVertex; ///First vertex.
	ushort stride; ///Vertex stride.
	VertexBufferHandle handle; ///Vertex buffer handle.
	VertexLayoutHandle layoutHandle; ///Vertex layout handle.
}

///Instance data buffer info.
extern(C++, "bgfx") struct InstanceDataBuffer{
	ubyte* data; ///Pointer to data.
	uint size; ///Data size.
	uint offset; ///Offset in vertex buffer.
	uint num; ///Number of instances.
	ushort stride; ///Vertex buffer stride.
	VertexBufferHandle handle; ///Vertex buffer object handle.
}

///Texture info.
extern(C++, "bgfx") struct TextureInfo{
	TextureFormat format; ///Texture format.
	uint storageSize; ///Total amount of bytes required to store texture.
	ushort width; ///Texture width.
	ushort height; ///Texture height.
	ushort depth; ///Texture depth.
	ushort numLayers; ///Number of layers in texture array.
	ubyte numMIPs; ///Number of MIP maps.
	ubyte bitsPerPixel; ///Format bits per pixel.
	bool cubeMap; ///Texture is cubemap.
}

///Uniform info.
extern(C++, "bgfx") struct UniformInfo{
	char[256] name; ///Uniform name.
	UniformType type; ///Uniform type.
	ushort num; ///Number of elements in array.
}

///Frame buffer texture attachment info.
extern(C++, "bgfx") struct Attachment{
	Access access; ///Attachment access. See `Access::Enum`.
	TextureHandle handle; ///Render target texture handle.
	ushort mip; ///Mip level.
	ushort layer; ///Cubemap side or depth layer/slice to use.
	ushort numLayers; ///Number of texture layer/slice(s) in array to use.
	ubyte resolve; ///Resolve flags. See: `BGFX_RESOLVE_*`
	extern(D) mixin(joinFnBinds((){
		FnBind[] ret = [
			/**
			Init attachment.
			Params:
				handle = Render target texture handle.
				access = Access. See `Access::Enum`.
				layer = Cubemap side or depth layer/slice to use.
				numLayers = Number of texture layer/slice(s) in array to use.
				mip = Mip level.
				resolve = Resolve flags. See: `BGFX_RESOLVE_*`
			*/
			{q{void}, q{init}, q{TextureHandle handle, bgfx.fakeenum.Access.Enum access=Access.write, ushort layer=0, ushort numLayers=1, ushort mip=0, ubyte resolve=Resolve.autoGenMIPs}, ext: `C++`},
		];
		return ret;
	}()));
}

///Transform data.
extern(C++, "bgfx") struct Transform{
	float* data; ///Pointer to first 4x4 matrix.
	ushort num; ///Number of matrices.
}

///View stats.
extern(C++, "bgfx") struct ViewStats{
	char[256] name; ///View name.
	ViewID view; ///View id.
	c_int64 cpuTimeBegin; ///CPU (submit) begin time.
	c_int64 cpuTimeEnd; ///CPU (submit) end time.
	c_int64 gpuTimeBegin; ///GPU begin time.
	c_int64 gpuTimeEnd; ///GPU end time.
	uint gpuFrameNum; ///Frame which generated gpuTimeBegin, gpuTimeEnd.
}

///Encoder stats.
extern(C++, "bgfx") struct EncoderStats{
	c_int64 cpuTimeBegin; ///Encoder thread CPU submit begin time.
	c_int64 cpuTimeEnd; ///Encoder thread CPU submit end time.
}

/**
Renderer statistics data.
@remarks All time values are high-resolution timestamps, while
time frequencies define timestamps-per-second for that hardware.
*/
extern(C++, "bgfx") struct Stats{
	c_int64 cpuTimeFrame; ///CPU time between two `bgfx::frame` calls.
	c_int64 cpuTimeBegin; ///Render thread CPU submit begin time.
	c_int64 cpuTimeEnd; ///Render thread CPU submit end time.
	c_int64 cpuTimerFreq; ///CPU timer frequency. Timestamps-per-second
	c_int64 gpuTimeBegin; ///GPU frame begin time.
	c_int64 gpuTimeEnd; ///GPU frame end time.
	c_int64 gpuTimerFreq; ///GPU timer frequency.
	c_int64 waitRender; ///Time spent waiting for render backend thread to finish issuing draw commands to underlying graphics API.
	c_int64 waitSubmit; ///Time spent waiting for submit thread to advance to next frame.
	uint numDraw; ///Number of draw calls submitted.
	uint numCompute; ///Number of compute calls submitted.
	uint numBlit; ///Number of blit calls submitted.
	uint maxGpuLatency; ///GPU driver latency.
	uint gpuFrameNum; ///Frame which generated gpuTimeBegin, gpuTimeEnd.
	ushort numDynamicIndexBuffers; ///Number of used dynamic index buffers.
	ushort numDynamicVertexBuffers; ///Number of used dynamic vertex buffers.
	ushort numFrameBuffers; ///Number of used frame buffers.
	ushort numIndexBuffers; ///Number of used index buffers.
	ushort numOcclusionQueries; ///Number of used occlusion queries.
	ushort numPrograms; ///Number of used programs.
	ushort numShaders; ///Number of used shaders.
	ushort numTextures; ///Number of used textures.
	ushort numUniforms; ///Number of used uniforms.
	ushort numVertexBuffers; ///Number of used vertex buffers.
	ushort numVertexLayouts; ///Number of used vertex layouts.
	c_int64 textureMemoryUsed; ///Estimate of texture memory used.
	c_int64 rtMemoryUsed; ///Estimate of render target memory used.
	int transientVBUsed; ///Amount of transient vertex buffer used.
	int transientIBUsed; ///Amount of transient index buffer used.
	uint[Topology.count] numPrims; ///Number of primitives rendered.
	c_int64 gpuMemoryMax; ///Maximum available GPU memory for application.
	c_int64 gpuMemoryUsed; ///Amount of GPU memory used by the application.
	ushort width; ///Backbuffer width in pixels.
	ushort height; ///Backbuffer height in pixels.
	ushort textWidth; ///Debug text width in characters.
	ushort textHeight; ///Debug text height in characters.
	ushort numViews; ///Number of view stats.
	ViewStats* viewStats; ///Array of View stats.
	ubyte numEncoders; ///Number of encoders used during frame.
	EncoderStats* encoderStats; ///Array of encoder stats.
}

///Vertex layout.
extern(C++, "bgfx") struct VertexLayout{
	uint hash; ///Hash.
	ushort stride; ///Stride.
	ushort[Attrib.count] offset; ///Attribute offsets.
	ushort[Attrib.count] attributes; ///Used attributes.
	extern(D) mixin(joinFnBinds((){
		FnBind[] ret = [
			{q{void}, q{this}, q{}, ext: `C++`},
			
			/**
			Start VertexLayout.
			Params:
				rendererType = Renderer backend type. See: `bgfx::RendererType`
			*/
			{q{VertexLayout*}, q{begin}, q{bgfx.fakeenum.RendererType.Enum rendererType=RendererType.noop}, ext: `C++`},
			
			/**
			Add attribute to VertexLayout.
			Remarks: Must be called between begin/end.
			Params:
				attrib = Attribute semantics. See: `bgfx::Attrib`
				num = Number of elements 1, 2, 3 or 4.
				type = Element type.
				normalised = When using fixed point AttribType (f.e. Uint8)
			value will be normalized for vertex shader usage. When normalized
			is set to true, AttribType::Uint8 value in range 0-255 will be
			in range 0.0-1.0 in vertex shader.
				asInt = Packaging rule for vertexPack, vertexUnpack, and
			vertexConvert for AttribType::Uint8 and AttribType::Int16.
			Unpacking code must be implemented inside vertex shader.
			*/
			{q{VertexLayout*}, q{add}, q{bgfx.fakeenum.Attrib.Enum attrib, ubyte num, bgfx.fakeenum.AttribType.Enum type, bool normalised=false, bool asInt=false}, ext: `C++`},
			
			/**
			Decode attribute.
			Params:
				attrib = Attribute semantics. See: `bgfx::Attrib`
				num = Number of elements.
				type = Element type.
				normalised = Attribute is normalized.
				asInt = Attribute is packed as int.
			*/
			{q{void}, q{decode}, q{bgfx.fakeenum.Attrib.Enum attrib, ref ubyte num, ref bgfx.fakeenum.AttribType.Enum type, ref bool normalised, ref bool asInt}, ext: `C++`, memAttr: q{const}},
			
			/**
			Skip `_num` bytes in vertex stream.
			Params:
				num = Number of bytes to skip.
			*/
			{q{VertexLayout*}, q{skip}, q{ubyte num}, ext: `C++`},
			
			/**
			End VertexLayout.
			*/
			{q{void}, q{end}, q{}, ext: `C++`},
		];
		return ret;
	}()));
}

/**
Encoders are used for submitting draw calls from multiple threads. Only one encoder
per thread should be used. Use `bgfx::begin()` to obtain an encoder for a thread.
*/
extern(C++, "bgfx") struct Encoder{
	extern(D) mixin(joinFnBinds((){
		FnBind[] ret = [
			/**
			Sets a debug marker. This allows you to group graphics calls together for easy browsing in
			graphics debugging tools.
			Params:
				name = Marker name.
				len = Marker name length (if length is INT32_MAX, it's expected
			that _name is zero terminated string.
			*/
			{q{void}, q{setMarker}, q{const(char)* name, int len=int.max}, ext: `C++`},
			
			/**
			Set render states for draw primitive.
			Remarks:
			  1. To set up more complex states use:
			     `BGFX_STATE_ALPHA_REF(_ref)`,
			     `BGFX_STATE_POINT_SIZE(_size)`,
			     `BGFX_STATE_BLEND_FUNC(_src, _dst)`,
			     `BGFX_STATE_BLEND_FUNC_SEPARATE(_srcRGB, _dstRGB, _srcA, _dstA)`,
			     `BGFX_STATE_BLEND_EQUATION(_equation)`,
			     `BGFX_STATE_BLEND_EQUATION_SEPARATE(_equationRGB, _equationA)`
			  2. `BGFX_STATE_BLEND_EQUATION_ADD` is set when no other blend
			     equation is specified.
			Params:
				state = State flags. Default state for primitive type is
			  triangles. See: `BGFX_STATE_DEFAULT`.
			  - `BGFX_STATE_DEPTH_TEST_*` - Depth test function.
			  - `BGFX_STATE_BLEND_*` - See remark 1 about BGFX_STATE_BLEND_FUNC.
			  - `BGFX_STATE_BLEND_EQUATION_*` - See remark 2.
			  - `BGFX_STATE_CULL_*` - Backface culling mode.
			  - `BGFX_STATE_WRITE_*` - Enable R, G, B, A or Z write.
			  - `BGFX_STATE_MSAA` - Enable hardware multisample antialiasing.
			  - `BGFX_STATE_PT_[TRISTRIP/LINES/POINTS]` - Primitive type.
				rgba = Sets blend factor used by `BGFX_STATE_BLEND_FACTOR` and
			  `BGFX_STATE_BLEND_INV_FACTOR` blend modes.
			*/
			{q{void}, q{setState}, q{c_uint64 state, uint rgba=0}, ext: `C++`},
			
			/**
			Set condition for rendering.
			Params:
				handle = Occlusion query handle.
				visible = Render if occlusion query is visible.
			*/
			{q{void}, q{setCondition}, q{OcclusionQueryHandle handle, bool visible}, ext: `C++`},
			
			/**
			Set stencil test state.
			Params:
				fStencil = Front stencil state.
				bStencil = Back stencil state. If back is set to `BGFX_STENCIL_NONE`
			_fstencil is applied to both front and back facing primitives.
			*/
			{q{void}, q{setStencil}, q{uint fStencil, uint bStencil=Stencil.none}, ext: `C++`},
			
			/**
			Set scissor for draw primitive.
			Remarks:
			  To scissor for all primitives in view see `bgfx::setViewScissor`.
			Params:
				x = Position x from the left corner of the window.
				y = Position y from the top corner of the window.
				width = Width of view scissor region.
				height = Height of view scissor region.
			*/
			{q{ushort}, q{setScissor}, q{ushort x, ushort y, ushort width, ushort height}, ext: `C++`},
			
			/**
			Set scissor from cache for draw primitive.
			Remarks:
			  To scissor for all primitives in view see `bgfx::setViewScissor`.
			Params:
				cache = Index in scissor cache.
			*/
			{q{void}, q{setScissor}, q{ushort cache=ushort.max}, ext: `C++`},
			
			/**
			Set model matrix for draw primitive. If it is not called,
			the model will be rendered with an identity model matrix.
			Params:
				mtx = Pointer to first matrix in array.
				num = Number of matrices in array.
			*/
			{q{uint}, q{setTransform}, q{const(void)* mtx, ushort num=1}, ext: `C++`},
			
			/**
			 Set model matrix from matrix cache for draw primitive.
			Params:
				cache = Index in matrix cache.
				num = Number of matrices from cache.
			*/
			{q{void}, q{setTransform}, q{uint cache, ushort num=1}, ext: `C++`},
			
			/**
			Reserve matrices in internal matrix cache.
			Attention: Pointer returned can be modified until `bgfx::frame` is called.
			Params:
				transform = Pointer to `Transform` structure.
				num = Number of matrices.
			*/
			{q{uint}, q{allocTransform}, q{Transform* transform, ushort num}, ext: `C++`},
			
			/**
			Set shader uniform parameter for draw primitive.
			Params:
				handle = Uniform.
				value = Pointer to uniform data.
				num = Number of elements. Passing `UINT16_MAX` will
			use the _num passed on uniform creation.
			*/
			{q{void}, q{setUniform}, q{UniformHandle handle, const(void)* value, ushort num=1}, ext: `C++`},
			
			/**
			Set index buffer for draw primitive.
			Params:
				handle = Index buffer.
			*/
			{q{void}, q{setIndexBuffer}, q{IndexBufferHandle handle}, ext: `C++`},
			
			/**
			Set index buffer for draw primitive.
			Params:
				handle = Index buffer.
				firstIndex = First index to render.
				numIndices = Number of indices to render.
			*/
			{q{void}, q{setIndexBuffer}, q{IndexBufferHandle handle, uint firstIndex, uint numIndices}, ext: `C++`},
			
			/**
			Set index buffer for draw primitive.
			Params:
				handle = Dynamic index buffer.
			*/
			{q{void}, q{setIndexBuffer}, q{DynamicIndexBufferHandle handle}, ext: `C++`},
			
			/**
			Set index buffer for draw primitive.
			Params:
				handle = Dynamic index buffer.
				firstIndex = First index to render.
				numIndices = Number of indices to render.
			*/
			{q{void}, q{setIndexBuffer}, q{DynamicIndexBufferHandle handle, uint firstIndex, uint numIndices}, ext: `C++`},
			
			/**
			Set index buffer for draw primitive.
			Params:
				tib = Transient index buffer.
			*/
			{q{void}, q{setIndexBuffer}, q{const(TransientIndexBuffer)* tib}, ext: `C++`},
			
			/**
			Set index buffer for draw primitive.
			Params:
				tib = Transient index buffer.
				firstIndex = First index to render.
				numIndices = Number of indices to render.
			*/
			{q{void}, q{setIndexBuffer}, q{const(TransientIndexBuffer)* tib, uint firstIndex, uint numIndices}, ext: `C++`},
			
			/**
			Set vertex buffer for draw primitive.
			Params:
				stream = Vertex stream.
				handle = Vertex buffer.
			*/
			{q{void}, q{setVertexBuffer}, q{ubyte stream, VertexBufferHandle handle}, ext: `C++`},
			
			/**
			Set vertex buffer for draw primitive.
			Params:
				stream = Vertex stream.
				handle = Vertex buffer.
				startVertex = First vertex to render.
				numVertices = Number of vertices to render.
				layoutHandle = Vertex layout for aliasing vertex buffer. If invalid
			handle is used, vertex layout used for creation
			of vertex buffer will be used.
			*/
			{q{void}, q{setVertexBuffer}, q{ubyte stream, VertexBufferHandle handle, uint startVertex, uint numVertices, VertexLayoutHandle layoutHandle=invalidHandle!VertexLayoutHandle}, ext: `C++`},
			
			/**
			Set vertex buffer for draw primitive.
			Params:
				stream = Vertex stream.
				handle = Dynamic vertex buffer.
			*/
			{q{void}, q{setVertexBuffer}, q{ubyte stream, DynamicVertexBufferHandle handle}, ext: `C++`},
			{q{void}, q{setVertexBuffer}, q{ubyte stream, DynamicVertexBufferHandle handle, uint startVertex, uint numVertices, VertexLayoutHandle layoutHandle=invalidHandle!VertexLayoutHandle}, ext: `C++`},
			
			/**
			Set vertex buffer for draw primitive.
			Params:
				stream = Vertex stream.
				tvb = Transient vertex buffer.
			*/
			{q{void}, q{setVertexBuffer}, q{ubyte stream, const(TransientVertexBuffer)* tvb}, ext: `C++`},
			
			/**
			Set vertex buffer for draw primitive.
			Params:
				stream = Vertex stream.
				tvb = Transient vertex buffer.
				startVertex = First vertex to render.
				numVertices = Number of vertices to render.
				layoutHandle = Vertex layout for aliasing vertex buffer. If invalid
			handle is used, vertex layout used for creation
			of vertex buffer will be used.
			*/
			{q{void}, q{setVertexBuffer}, q{ubyte stream, const(TransientVertexBuffer)* tvb, uint startVertex, uint numVertices, VertexLayoutHandle layoutHandle=invalidHandle!VertexLayoutHandle}, ext: `C++`},
			
			/**
			Set number of vertices for auto generated vertices use in conjunction
			with gl_VertexID.
			Attention: Availability depends on: `BGFX_CAPS_VERTEX_ID`.
			Params:
				numVertices = Number of vertices.
			*/
			{q{void}, q{setVertexCount}, q{uint numVertices}, ext: `C++`},
			
			/**
			Set instance data buffer for draw primitive.
			Params:
				idb = Transient instance data buffer.
			*/
			{q{void}, q{setInstanceDataBuffer}, q{const(InstanceDataBuffer)* idb}, ext: `C++`},
			
			/**
			Set instance data buffer for draw primitive.
			Params:
				idb = Transient instance data buffer.
				start = First instance data.
				num = Number of data instances.
			*/
			{q{void}, q{setInstanceDataBuffer}, q{const(InstanceDataBuffer)* idb, uint start, uint num}, ext: `C++`},
			
			/**
			Set instance data buffer for draw primitive.
			Params:
				handle = Vertex buffer.
				startVertex = First instance data.
				num = Number of data instances.
			*/
			{q{void}, q{setInstanceDataBuffer}, q{VertexBufferHandle handle, uint startVertex, uint num}, ext: `C++`},
			
			/**
			Set instance data buffer for draw primitive.
			Params:
				handle = Dynamic vertex buffer.
				startVertex = First instance data.
				num = Number of data instances.
			*/
			{q{void}, q{setInstanceDataBuffer}, q{DynamicVertexBufferHandle handle, uint startVertex, uint num}, ext: `C++`},
			
			/**
			Set number of instances for auto generated instances use in conjunction
			with gl_InstanceID.
			Attention: Availability depends on: `BGFX_CAPS_VERTEX_ID`.
			*/
			{q{void}, q{setInstanceCount}, q{uint numInstances}, ext: `C++`},
			
			/**
			Set texture stage for draw primitive.
			Params:
				stage = Texture unit.
				sampler = Program sampler.
				handle = Texture handle.
				flags = Texture sampling mode. Default value UINT32_MAX uses
			  texture sampling settings from the texture.
			  - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
			    mode.
			  - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
			    sampling.
			*/
			{q{void}, q{setTexture}, q{ubyte stage, UniformHandle sampler, TextureHandle handle, uint flags=uint.max}, ext: `C++`},
			
			/**
			Submit an empty primitive for rendering. Uniforms and draw state
			will be applied but no geometry will be submitted. Useful in cases
			when no other draw/compute primitive is submitted to view, but it's
			desired to execute clear view.
			Remarks:
			  These empty draw calls will sort before ordinary draw calls.
			Params:
				id = View id.
			*/
			{q{void}, q{touch}, q{ViewID id}, ext: `C++`},
			
			/**
			Submit primitive for rendering.
			Params:
				id = View id.
				program = Program.
				depth = Depth for sorting.
				flags = Discard or preserve states. See `BGFX_DISCARD_*`.
			*/
			{q{void}, q{submit}, q{ViewID id, ProgramHandle program, uint depth=0, ubyte flags=Discard.all}, ext: `C++`},
			
			/**
			Submit primitive with occlusion query for rendering.
			Params:
				id = View id.
				program = Program.
				occlusionQuery = Occlusion query.
				depth = Depth for sorting.
				flags = Discard or preserve states. See `BGFX_DISCARD_*`.
			*/
			{q{void}, q{submit}, q{ViewID id, ProgramHandle program, OcclusionQueryHandle occlusionQuery, uint depth=0, ubyte flags=Discard.all}, ext: `C++`},
			
			/**
			Submit primitive for rendering with index and instance data info from
			indirect buffer.
			Attention: Availability depends on: `BGFX_CAPS_DRAW_INDIRECT`.
			Params:
				id = View id.
				program = Program.
				indirectHandle = Indirect buffer.
				start = First element in indirect buffer.
				num = Number of draws.
				depth = Depth for sorting.
				flags = Discard or preserve states. See `BGFX_DISCARD_*`.
			*/
			{q{void}, q{submit}, q{ViewID id, ProgramHandle program, IndirectBufferHandle indirectHandle, uint start=0, uint num=1, uint depth=0, ubyte flags=Discard.all}, ext: `C++`},
			
			/**
			Submit primitive for rendering with index and instance data info and
			draw count from indirect buffers.
			Attention: Availability depends on: `BGFX_CAPS_DRAW_INDIRECT_COUNT`.
			Params:
				id = View id.
				program = Program.
				indirectHandle = Indirect buffer.
				start = First element in indirect buffer.
				numHandle = Buffer for number of draws. Must be
			  created with `BGFX_BUFFER_INDEX32` and `BGFX_BUFFER_DRAW_INDIRECT`.
				numIndex = Element in number buffer.
				numMax = Max number of draws.
				depth = Depth for sorting.
				flags = Discard or preserve states. See `BGFX_DISCARD_*`.
			*/
			{q{void}, q{submit}, q{ViewID id, ProgramHandle program, IndirectBufferHandle indirectHandle, uint start, IndexBufferHandle numHandle, uint numIndex=0, uint numMax=uint.max, uint depth=0, ubyte flags=Discard.all}, ext: `C++`},
			
			/**
			Set compute index buffer.
			Params:
				stage = Compute stage.
				handle = Index buffer handle.
				access = Buffer access. See `Access::Enum`.
			*/
			{q{void}, q{setBuffer}, q{ubyte stage, IndexBufferHandle handle, bgfx.fakeenum.Access.Enum access}, ext: `C++`},
			
			/**
			Set compute vertex buffer.
			Params:
				stage = Compute stage.
				handle = Vertex buffer handle.
				access = Buffer access. See `Access::Enum`.
			*/
			{q{void}, q{setBuffer}, q{ubyte stage, VertexBufferHandle handle, bgfx.fakeenum.Access.Enum access}, ext: `C++`},
			
			/**
			Set compute dynamic index buffer.
			Params:
				stage = Compute stage.
				handle = Dynamic index buffer handle.
				access = Buffer access. See `Access::Enum`.
			*/
			{q{void}, q{setBuffer}, q{ubyte stage, DynamicIndexBufferHandle handle, bgfx.fakeenum.Access.Enum access}, ext: `C++`},
			
			/**
			Set compute dynamic vertex buffer.
			Params:
				stage = Compute stage.
				handle = Dynamic vertex buffer handle.
				access = Buffer access. See `Access::Enum`.
			*/
			{q{void}, q{setBuffer}, q{ubyte stage, DynamicVertexBufferHandle handle, bgfx.fakeenum.Access.Enum access}, ext: `C++`},
			
			/**
			Set compute indirect buffer.
			Params:
				stage = Compute stage.
				handle = Indirect buffer handle.
				access = Buffer access. See `Access::Enum`.
			*/
			{q{void}, q{setBuffer}, q{ubyte stage, IndirectBufferHandle handle, bgfx.fakeenum.Access.Enum access}, ext: `C++`},
			
			/**
			Set compute image from texture.
			Params:
				stage = Compute stage.
				handle = Texture handle.
				mip = Mip level.
				access = Image access. See `Access::Enum`.
				format = Texture format. See: `TextureFormat::Enum`.
			*/
			{q{void}, q{setImage}, q{ubyte stage, TextureHandle handle, ubyte mip, bgfx.fakeenum.Access.Enum access, bgfx.fakeenum.TextureFormat.Enum format=TextureFormat.count}, ext: `C++`},
			
			/**
			Dispatch compute.
			Params:
				id = View id.
				program = Compute program.
				numX = Number of groups X.
				numY = Number of groups Y.
				numZ = Number of groups Z.
				flags = Discard or preserve states. See `BGFX_DISCARD_*`.
			*/
			{q{void}, q{dispatch}, q{ViewID id, ProgramHandle program, uint numX=1, uint numY=1, uint numZ=1, ubyte flags=Discard.all}, ext: `C++`},
			
			/**
			Dispatch compute indirect.
			Params:
				id = View id.
				program = Compute program.
				indirectHandle = Indirect buffer.
				start = First element in indirect buffer.
				num = Number of dispatches.
				flags = Discard or preserve states. See `BGFX_DISCARD_*`.
			*/
			{q{void}, q{dispatch}, q{ViewID id, ProgramHandle program, IndirectBufferHandle indirectHandle, uint start=0, uint num=1, ubyte flags=Discard.all}, ext: `C++`},
			
			/**
			Discard previously set state for draw or compute call.
			Params:
				flags = Discard or preserve states. See `BGFX_DISCARD_*`.
			*/
			{q{void}, q{discard}, q{ubyte flags=Discard.all}, ext: `C++`},
			
			/**
			Blit 2D texture region between two 2D textures.
			Attention: Destination texture must be created with `BGFX_TEXTURE_BLIT_DST` flag.
			Attention: Availability depends on: `BGFX_CAPS_TEXTURE_BLIT`.
			Params:
				id = View id.
				dst = Destination texture handle.
				dstX = Destination texture X position.
				dstY = Destination texture Y position.
				src = Source texture handle.
				srcX = Source texture X position.
				srcY = Source texture Y position.
				width = Width of region.
				height = Height of region.
			*/
			{q{void}, q{blit}, q{ViewID id, TextureHandle dst, ushort dstX, ushort dstY, TextureHandle src, ushort srcX=0, ushort srcY=0, ushort width=ushort.max, ushort height=ushort.max}, ext: `C++`},
			
			/**
			Blit 2D texture region between two 2D textures.
			Attention: Destination texture must be created with `BGFX_TEXTURE_BLIT_DST` flag.
			Attention: Availability depends on: `BGFX_CAPS_TEXTURE_BLIT`.
			Params:
				id = View id.
				dst = Destination texture handle.
				dstMIP = Destination texture mip level.
				dstX = Destination texture X position.
				dstY = Destination texture Y position.
				dstZ = If texture is 2D this argument should be 0. If destination texture is cube
			this argument represents destination texture cube face. For 3D texture this argument
			represents destination texture Z position.
				src = Source texture handle.
				srcMIP = Source texture mip level.
				srcX = Source texture X position.
				srcY = Source texture Y position.
				srcZ = If texture is 2D this argument should be 0. If source texture is cube
			this argument represents source texture cube face. For 3D texture this argument
			represents source texture Z position.
				width = Width of region.
				height = Height of region.
				depth = If texture is 3D this argument represents depth of region, otherwise it's
			unused.
			*/
			{q{void}, q{blit}, q{ViewID id, TextureHandle dst, ubyte dstMIP, ushort dstX, ushort dstY, ushort dstZ, TextureHandle src, ubyte srcMIP=0, ushort srcX=0, ushort srcY=0, ushort srcZ=0, ushort width=ushort.max, ushort height=ushort.max, ushort depth=ushort.max}, ext: `C++`},
		];
		return ret;
	}()));
}

mixin(joinFnBinds((){
	FnBind[] ret = [
		/**
		* Pack vertex attribute into vertex stream format.
		Params:
			input = Value to be packed into vertex stream.
			inputNormalised = `true` if input value is already normalized.
			attr = Attribute to pack.
			layout = Vertex stream layout.
			data = Destination vertex stream where data will be packed.
			index = Vertex index that will be modified.
		*/
		{q{void}, q{vertexPack}, q{const(float)* input, bool inputNormalised, bgfx.fakeenum.Attrib.Enum attr, ref const VertexLayout layout, void* data, uint index=0}, ext: `C++, "bgfx"`},
		
		/**
		* Unpack vertex attribute from vertex stream format.
		Params:
			output = Result of unpacking.
			attr = Attribute to unpack.
			layout = Vertex stream layout.
			data = Source vertex stream from where data will be unpacked.
			index = Vertex index that will be unpacked.
		*/
		{q{void}, q{vertexUnpack}, q{float* output, bgfx.fakeenum.Attrib.Enum attr, ref const VertexLayout layout, const(void)* data, uint index=0}, ext: `C++, "bgfx"`},
		
		/**
		* Converts vertex stream data from one vertex stream format to another.
		Params:
			dstLayout = Destination vertex stream layout.
			dstData = Destination vertex stream.
			srcLayout = Source vertex stream layout.
			srcData = Source vertex stream data.
			num = Number of vertices to convert from source to destination.
		*/
		{q{void}, q{vertexConvert}, q{ref const VertexLayout dstLayout, void* dstData, ref const VertexLayout srcLayout, const(void)* srcData, uint num=1}, ext: `C++, "bgfx"`},
		
		/**
		* Weld vertices.
		Params:
			output = Welded vertices remapping table. The size of buffer
		must be the same as number of vertices.
			layout = Vertex stream layout.
			data = Vertex stream.
			num = Number of vertices in vertex stream.
			index32 = Set to `true` if input indices are 32-bit.
			epsilon = Error tolerance for vertex position comparison.
		*/
		{q{uint}, q{weldVertices}, q{void* output, ref const VertexLayout layout, const(void)* data, uint num, bool index32, float epsilon=0.001f}, ext: `C++, "bgfx"`},
		
		/**
		* Convert index buffer for use with different primitive topologies.
		Params:
			conversion = Conversion type, see `TopologyConvert::Enum`.
			dst = Destination index buffer. If this argument is NULL
		function will return number of indices after conversion.
			dstSize = Destination index buffer in bytes. It must be
		large enough to contain output indices. If destination size is
		insufficient index buffer will be truncated.
			indices = Source indices.
			numIndices = Number of input indices.
			index32 = Set to `true` if input indices are 32-bit.
		*/
		{q{uint}, q{topologyConvert}, q{bgfx.fakeenum.TopologyConvert.Enum conversion, void* dst, uint dstSize, const(void)* indices, uint numIndices, bool index32}, ext: `C++, "bgfx"`},
		
		/**
		* Sort indices.
		Params:
			sort = Sort order, see `TopologySort::Enum`.
			dst = Destination index buffer.
			dstSize = Destination index buffer in bytes. It must be
		large enough to contain output indices. If destination size is
		insufficient index buffer will be truncated.
			dir = Direction (vector must be normalized).
			pos = Position.
			vertices = Pointer to first vertex represented as
		float x, y, z. Must contain at least number of vertices
		referencende by index buffer.
			stride = Vertex stride.
			indices = Source indices.
			numIndices = Number of input indices.
			index32 = Set to `true` if input indices are 32-bit.
		*/
		{q{void}, q{topologySortTriList}, q{bgfx.fakeenum.TopologySort.Enum sort, void* dst, uint dstSize, const(float)* dir, const(float)* pos, const(void)* vertices, uint stride, const(void)* indices, uint numIndices, bool index32}, ext: `C++, "bgfx"`},
		
		/**
		* Returns supported backend API renderers.
		Params:
			max = Maximum number of elements in _enum array.
			enum_ = Array where supported renderers will be written.
		*/
		{q{ubyte}, q{getSupportedRenderers}, q{ubyte max=0, bgfx.fakeenum.RendererType.Enum* enum_=null}, ext: `C++, "bgfx"`},
		
		/**
		* Returns name of renderer.
		Params:
			type = Renderer backend type. See: `bgfx::RendererType`
		*/
		{q{const(char)*}, q{getRendererName}, q{bgfx.fakeenum.RendererType.Enum type}, ext: `C++, "bgfx"`},
		
		/**
		* Initialize the bgfx library.
		Params:
			init = Initialization parameters. See: `bgfx::Init` for more info.
		*/
		{q{bool}, q{init}, q{ref const Init init}, ext: `C++, "bgfx"`},
		
		/**
		* Shutdown bgfx library.
		*/
		{q{void}, q{shutdown}, q{}, ext: `C++, "bgfx"`},
		
		/**
		* Reset graphic settings and back-buffer size.
		* Attention: This call doesn’t change the window size, it just resizes
		*   the back-buffer. Your windowing code controls the window size.
		Params:
			width = Back-buffer width.
			height = Back-buffer height.
			flags = See: `BGFX_RESET_*` for more info.
		  - `BGFX_RESET_NONE` - No reset flags.
		  - `BGFX_RESET_FULLSCREEN` - Not supported yet.
		  - `BGFX_RESET_MSAA_X[2/4/8/16]` - Enable 2, 4, 8 or 16 x MSAA.
		  - `BGFX_RESET_VSYNC` - Enable V-Sync.
		  - `BGFX_RESET_MAXANISOTROPY` - Turn on/off max anisotropy.
		  - `BGFX_RESET_CAPTURE` - Begin screen capture.
		  - `BGFX_RESET_FLUSH_AFTER_RENDER` - Flush rendering after submitting to GPU.
		  - `BGFX_RESET_FLIP_AFTER_RENDER` - This flag  specifies where flip
		    occurs. Default behaviour is that flip occurs before rendering new
		    frame. This flag only has effect when `BGFX_CONFIG_MULTITHREADED=0`.
		  - `BGFX_RESET_SRGB_BACKBUFFER` - Enable sRGB back-buffer.
			format = Texture format. See: `TextureFormat::Enum`.
		*/
		{q{void}, q{reset}, q{uint width, uint height, uint flags=Reset.none, bgfx.fakeenum.TextureFormat.Enum format=TextureFormat.count}, ext: `C++, "bgfx"`},
		
		/**
		* Advance to next frame. When using multithreaded renderer, this call
		* just swaps internal buffers, kicks render thread, and returns. In
		* singlethreaded renderer this call does frame rendering.
		Params:
			capture = Capture frame with graphics debugger.
		*/
		{q{uint}, q{frame}, q{bool capture=false}, ext: `C++, "bgfx"`},
		
		/**
		* Returns current renderer backend API type.
		* Remarks:
		*   Library must be initialized.
		*/
		{q{RendererType}, q{getRendererType}, q{}, ext: `C++, "bgfx"`},
		
		/**
		* Returns renderer capabilities.
		* Remarks:
		*   Library must be initialized.
		*/
		{q{const(Caps)*}, q{getCaps}, q{}, ext: `C++, "bgfx"`},
		
		/**
		* Returns performance counters.
		* Attention: Pointer returned is valid until `bgfx::frame` is called.
		*/
		{q{const(Stats)*}, q{getStats}, q{}, ext: `C++, "bgfx"`},
		
		/**
		* Allocate buffer to pass to bgfx calls. Data will be freed inside bgfx.
		Params:
			size = Size to allocate.
		*/
		{q{const(Memory)*}, q{alloc}, q{uint size}, ext: `C++, "bgfx"`},
		
		/**
		* Allocate buffer and copy data into it. Data will be freed inside bgfx.
		Params:
			data = Pointer to data to be copied.
			size = Size of data to be copied.
		*/
		{q{const(Memory)*}, q{copy}, q{const(void)* data, uint size}, ext: `C++, "bgfx"`},
		
		/**
		* Make reference to data to pass to bgfx. Unlike `bgfx::alloc`, this call
		* doesn't allocate memory for data. It just copies the _data pointer. You
		* can pass `ReleaseFn` function pointer to release this memory after it's
		* consumed, otherwise you must make sure _data is available for at least 2
		* `bgfx::frame` calls. `ReleaseFn` function must be able to be called
		* from any thread.
		* Attention: Data passed must be available for at least 2 `bgfx::frame` calls.
		Params:
			data = Pointer to data.
			size = Size of data.
			releaseFn = Callback function to release memory after use.
			userData = User data to be passed to callback function.
		*/
		{q{const(Memory)*}, q{makeRef}, q{const(void)* data, uint size, ReleaseFn releaseFn=null, void* userData=null}, ext: `C++, "bgfx"`},
		
		/**
		* Set debug flags.
		Params:
			debug_ = Available flags:
		  - `BGFX_DEBUG_IFH` - Infinitely fast hardware. When this flag is set
		    all rendering calls will be skipped. This is useful when profiling
		    to quickly assess potential bottlenecks between CPU and GPU.
		  - `BGFX_DEBUG_PROFILER` - Enable profiler.
		  - `BGFX_DEBUG_STATS` - Display internal statistics.
		  - `BGFX_DEBUG_TEXT` - Display debug text.
		  - `BGFX_DEBUG_WIREFRAME` - Wireframe rendering. All rendering
		    primitives will be rendered as lines.
		*/
		{q{void}, q{setDebug}, q{uint debug_}, ext: `C++, "bgfx"`},
		
		/**
		* Clear internal debug text buffer.
		Params:
			attr = Background color.
			small = Default 8x16 or 8x8 font.
		*/
		{q{void}, q{dbgTextClear}, q{ubyte attr=0, bool small=false}, ext: `C++, "bgfx"`},
		
		/**
		* Print formatted data to internal debug text character-buffer (VGA-compatible text mode).
		Params:
			x = Position x from the left corner of the window.
			y = Position y from the top corner of the window.
			attr = Color palette. Where top 4-bits represent index of background, and bottom
		4-bits represent foreground color from standard VGA text palette (ANSI escape codes).
			format = `printf` style format.
		*/
		{q{void}, q{dbgTextPrintf}, q{ushort x, ushort y, ubyte attr, const(char)* format, ...}, ext: `C++, "bgfx"`},
		
		/**
		* Print formatted data from variable argument list to internal debug text character-buffer (VGA-compatible text mode).
		Params:
			x = Position x from the left corner of the window.
			y = Position y from the top corner of the window.
			attr = Color palette. Where top 4-bits represent index of background, and bottom
		4-bits represent foreground color from standard VGA text palette (ANSI escape codes).
			format = `printf` style format.
			argList = Variable arguments list for format string.
		*/
		{q{void}, q{dbgTextPrintfVargs}, q{ushort x, ushort y, ubyte attr, const(char)* format, va_list argList}, ext: `C++, "bgfx"`},
		
		/**
		* Draw image into internal debug text buffer.
		Params:
			x = Position x from the left corner of the window.
			y = Position y from the top corner of the window.
			width = Image width.
			height = Image height.
			data = Raw image data (character/attribute raw encoding).
			pitch = Image pitch in bytes.
		*/
		{q{void}, q{dbgTextImage}, q{ushort x, ushort y, ushort width, ushort height, const(void)* data, ushort pitch}, ext: `C++, "bgfx"`},
		
		/**
		* Create static index buffer.
		Params:
			mem = Index buffer data.
			flags = Buffer creation flags.
		  - `BGFX_BUFFER_NONE` - No flags.
		  - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
		  - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
		      is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
		  - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
		  - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of
		      data is passed. If this flag is not specified, and more data is passed on update, the buffer
		      will be trimmed to fit the existing buffer size. This flag has effect only on dynamic
		      buffers.
		  - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on
		      index buffers.
		*/
		{q{IndexBufferHandle}, q{createIndexBuffer}, q{const(Memory)* mem, ushort flags=Buffer.none}, ext: `C++, "bgfx"`},
		
		/**
		* Set static index buffer debug name.
		Params:
			handle = Static index buffer handle.
			name = Static index buffer name.
			len = Static index buffer name length (if length is INT32_MAX, it's expected
		that _name is zero terminated string.
		*/
		{q{void}, q{setName}, q{IndexBufferHandle handle, const(char)* name, int len=int.max}, ext: `C++, "bgfx"`},
		
		/**
		* Destroy static index buffer.
		Params:
			handle = Static index buffer handle.
		*/
		{q{void}, q{destroy}, q{IndexBufferHandle handle}, ext: `C++, "bgfx"`},
		
		/**
		* Create vertex layout.
		Params:
			layout = Vertex layout.
		*/
		{q{VertexLayoutHandle}, q{createVertexLayout}, q{ref const VertexLayout layout}, ext: `C++, "bgfx"`},
		
		/**
		* Destroy vertex layout.
		Params:
			layoutHandle = Vertex layout handle.
		*/
		{q{void}, q{destroy}, q{VertexLayoutHandle layoutHandle}, ext: `C++, "bgfx"`},
		
		/**
		* Create static vertex buffer.
		Params:
			mem = Vertex buffer data.
			layout = Vertex layout.
			flags = Buffer creation flags.
		 - `BGFX_BUFFER_NONE` - No flags.
		 - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
		 - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
		     is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
		 - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
		 - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of
		     data is passed. If this flag is not specified, and more data is passed on update, the buffer
		     will be trimmed to fit the existing buffer size. This flag has effect only on dynamic buffers.
		 - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on index buffers.
		*/
		{q{VertexBufferHandle}, q{createVertexBuffer}, q{const(Memory)* mem, ref const VertexLayout layout, ushort flags=Buffer.none}, ext: `C++, "bgfx"`},
		
		/**
		* Set static vertex buffer debug name.
		Params:
			handle = Static vertex buffer handle.
			name = Static vertex buffer name.
			len = Static vertex buffer name length (if length is INT32_MAX, it's expected
		that _name is zero terminated string.
		*/
		{q{void}, q{setName}, q{VertexBufferHandle handle, const(char)* name, int len=int.max}, ext: `C++, "bgfx"`},
		
		/**
		* Destroy static vertex buffer.
		Params:
			handle = Static vertex buffer handle.
		*/
		{q{void}, q{destroy}, q{VertexBufferHandle handle}, ext: `C++, "bgfx"`},
		
		/**
		* Create empty dynamic index buffer.
		Params:
			num = Number of indices.
			flags = Buffer creation flags.
		  - `BGFX_BUFFER_NONE` - No flags.
		  - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
		  - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
		      is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
		  - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
		  - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of
		      data is passed. If this flag is not specified, and more data is passed on update, the buffer
		      will be trimmed to fit the existing buffer size. This flag has effect only on dynamic
		      buffers.
		  - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on
		      index buffers.
		*/
		{q{DynamicIndexBufferHandle}, q{createDynamicIndexBuffer}, q{uint num, ushort flags=Buffer.none}, ext: `C++, "bgfx"`},
		
		/**
		* Create a dynamic index buffer and initialize it.
		Params:
			mem = Index buffer data.
			flags = Buffer creation flags.
		  - `BGFX_BUFFER_NONE` - No flags.
		  - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
		  - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
		      is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
		  - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
		  - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of
		      data is passed. If this flag is not specified, and more data is passed on update, the buffer
		      will be trimmed to fit the existing buffer size. This flag has effect only on dynamic
		      buffers.
		  - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on
		      index buffers.
		*/
		{q{DynamicIndexBufferHandle}, q{createDynamicIndexBuffer}, q{const(Memory)* mem, ushort flags=Buffer.none}, ext: `C++, "bgfx"`},
		
		/**
		* Update dynamic index buffer.
		Params:
			handle = Dynamic index buffer handle.
			startIndex = Start index.
			mem = Index buffer data.
		*/
		{q{void}, q{update}, q{DynamicIndexBufferHandle handle, uint startIndex, const(Memory)* mem}, ext: `C++, "bgfx"`},
		
		/**
		* Destroy dynamic index buffer.
		Params:
			handle = Dynamic index buffer handle.
		*/
		{q{void}, q{destroy}, q{DynamicIndexBufferHandle handle}, ext: `C++, "bgfx"`},
		
		/**
		* Create empty dynamic vertex buffer.
		Params:
			num = Number of vertices.
			layout = Vertex layout.
			flags = Buffer creation flags.
		  - `BGFX_BUFFER_NONE` - No flags.
		  - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
		  - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
		      is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
		  - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
		  - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of
		      data is passed. If this flag is not specified, and more data is passed on update, the buffer
		      will be trimmed to fit the existing buffer size. This flag has effect only on dynamic
		      buffers.
		  - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on
		      index buffers.
		*/
		{q{DynamicVertexBufferHandle}, q{createDynamicVertexBuffer}, q{uint num, ref const VertexLayout layout, ushort flags=Buffer.none}, ext: `C++, "bgfx"`},
		
		/**
		* Create dynamic vertex buffer and initialize it.
		Params:
			mem = Vertex buffer data.
			layout = Vertex layout.
			flags = Buffer creation flags.
		  - `BGFX_BUFFER_NONE` - No flags.
		  - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
		  - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
		      is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
		  - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
		  - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of
		      data is passed. If this flag is not specified, and more data is passed on update, the buffer
		      will be trimmed to fit the existing buffer size. This flag has effect only on dynamic
		      buffers.
		  - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on
		      index buffers.
		*/
		{q{DynamicVertexBufferHandle}, q{createDynamicVertexBuffer}, q{const(Memory)* mem, ref const VertexLayout layout, ushort flags=Buffer.none}, ext: `C++, "bgfx"`},
		
		/**
		* Update dynamic vertex buffer.
		Params:
			handle = Dynamic vertex buffer handle.
			startVertex = Start vertex.
			mem = Vertex buffer data.
		*/
		{q{void}, q{update}, q{DynamicVertexBufferHandle handle, uint startVertex, const(Memory)* mem}, ext: `C++, "bgfx"`},
		
		/**
		* Destroy dynamic vertex buffer.
		Params:
			handle = Dynamic vertex buffer handle.
		*/
		{q{void}, q{destroy}, q{DynamicVertexBufferHandle handle}, ext: `C++, "bgfx"`},
		
		/**
		* Returns number of requested or maximum available indices.
		Params:
			num = Number of required indices.
			index32 = Set to `true` if input indices will be 32-bit.
		*/
		{q{uint}, q{getAvailTransientIndexBuffer}, q{uint num, bool index32=false}, ext: `C++, "bgfx"`},
		
		/**
		* Returns number of requested or maximum available vertices.
		Params:
			num = Number of required vertices.
			layout = Vertex layout.
		*/
		{q{uint}, q{getAvailTransientVertexBuffer}, q{uint num, ref const VertexLayout layout}, ext: `C++, "bgfx"`},
		
		/**
		* Returns number of requested or maximum available instance buffer slots.
		Params:
			num = Number of required instances.
			stride = Stride per instance.
		*/
		{q{uint}, q{getAvailInstanceDataBuffer}, q{uint num, ushort stride}, ext: `C++, "bgfx"`},
		
		/**
		* Allocate transient index buffer.
		Params:
			tib = TransientIndexBuffer structure will be filled, and will be valid
		for the duration of frame, and can be reused for multiple draw
		calls.
			num = Number of indices to allocate.
			index32 = Set to `true` if input indices will be 32-bit.
		*/
		{q{void}, q{allocTransientIndexBuffer}, q{TransientIndexBuffer* tib, uint num, bool index32=false}, ext: `C++, "bgfx"`},
		
		/**
		* Allocate transient vertex buffer.
		Params:
			tvb = TransientVertexBuffer structure will be filled, and will be valid
		for the duration of frame, and can be reused for multiple draw
		calls.
			num = Number of vertices to allocate.
			layout = Vertex layout.
		*/
		{q{void}, q{allocTransientVertexBuffer}, q{TransientVertexBuffer* tvb, uint num, ref const VertexLayout layout}, ext: `C++, "bgfx"`},
		
		/**
		* Check for required space and allocate transient vertex and index
		* buffers. If both space requirements are satisfied function returns
		* true.
		Params:
			tvb = TransientVertexBuffer structure will be filled, and will be valid
		for the duration of frame, and can be reused for multiple draw
		calls.
			layout = Vertex layout.
			numVertices = Number of vertices to allocate.
			tib = TransientIndexBuffer structure will be filled, and will be valid
		for the duration of frame, and can be reused for multiple draw
		calls.
			numIndices = Number of indices to allocate.
			index32 = Set to `true` if input indices will be 32-bit.
		*/
		{q{bool}, q{allocTransientBuffers}, q{TransientVertexBuffer* tvb, ref const VertexLayout layout, uint numVertices, TransientIndexBuffer* tib, uint numIndices, bool index32=false}, ext: `C++, "bgfx"`},
		
		/**
		* Allocate instance data buffer.
		Params:
			idb = InstanceDataBuffer structure will be filled, and will be valid
		for duration of frame, and can be reused for multiple draw
		calls.
			num = Number of instances.
			stride = Instance stride. Must be multiple of 16.
		*/
		{q{void}, q{allocInstanceDataBuffer}, q{InstanceDataBuffer* idb, uint num, ushort stride}, ext: `C++, "bgfx"`},
		
		/**
		* Create draw indirect buffer.
		Params:
			num = Number of indirect calls.
		*/
		{q{IndirectBufferHandle}, q{createIndirectBuffer}, q{uint num}, ext: `C++, "bgfx"`},
		
		/**
		* Destroy draw indirect buffer.
		Params:
			handle = Indirect buffer handle.
		*/
		{q{void}, q{destroy}, q{IndirectBufferHandle handle}, ext: `C++, "bgfx"`},
		
		/**
		* Create shader from memory buffer.
		* Remarks:
		*   Shader binary is obtained by compiling shader offline with shaderc command line tool.
		Params:
			mem = Shader binary.
		*/
		{q{ShaderHandle}, q{createShader}, q{const(Memory)* mem}, ext: `C++, "bgfx"`},
		
		/**
		* Returns the number of uniforms and uniform handles used inside a shader.
		* Remarks:
		*   Only non-predefined uniforms are returned.
		Params:
			handle = Shader handle.
			uniforms = UniformHandle array where data will be stored.
			max = Maximum capacity of array.
		*/
		{q{ushort}, q{getShaderUniforms}, q{ShaderHandle handle, UniformHandle* uniforms=null, ushort max=0}, ext: `C++, "bgfx"`},
		
		/**
		* Set shader debug name.
		Params:
			handle = Shader handle.
			name = Shader name.
			len = Shader name length (if length is INT32_MAX, it's expected
		that _name is zero terminated string).
		*/
		{q{void}, q{setName}, q{ShaderHandle handle, const(char)* name, int len=int.max}, ext: `C++, "bgfx"`},
		
		/**
		* Destroy shader.
		* Remarks: Once a shader program is created with _handle,
		*   it is safe to destroy that shader.
		Params:
			handle = Shader handle.
		*/
		{q{void}, q{destroy}, q{ShaderHandle handle}, ext: `C++, "bgfx"`},
		
		/**
		* Create program with vertex and fragment shaders.
		Params:
			vsh = Vertex shader.
			fsh = Fragment shader.
			destroyShaders = If true, shaders will be destroyed when program is destroyed.
		*/
		{q{ProgramHandle}, q{createProgram}, q{ShaderHandle vsh, ShaderHandle fsh, bool destroyShaders=false}, ext: `C++, "bgfx"`},
		
		/**
		* Create program with compute shader.
		Params:
			csh = Compute shader.
			destroyShaders = If true, shaders will be destroyed when program is destroyed.
		*/
		{q{ProgramHandle}, q{createProgram}, q{ShaderHandle csh, bool destroyShaders=false}, ext: `C++, "bgfx"`},
		
		/**
		* Destroy program.
		Params:
			handle = Program handle.
		*/
		{q{void}, q{destroy}, q{ProgramHandle handle}, ext: `C++, "bgfx"`},
		
		/**
		* Validate texture parameters.
		Params:
			depth = Depth dimension of volume texture.
			cubeMap = Indicates that texture contains cubemap.
			numLayers = Number of layers in texture array.
			format = Texture format. See: `TextureFormat::Enum`.
			flags = Texture flags. See `BGFX_TEXTURE_*`.
		*/
		{q{bool}, q{isTextureValid}, q{ushort depth, bool cubeMap, ushort numLayers, bgfx.fakeenum.TextureFormat.Enum format, c_uint64 flags}, ext: `C++, "bgfx"`},
		
		/**
		* Validate frame buffer parameters.
		Params:
			num = Number of attachments.
			attachment = Attachment texture info. See: `bgfx::Attachment`.
		*/
		{q{bool}, q{isFrameBufferValid}, q{ubyte num, const(Attachment)* attachment}, ext: `C++, "bgfx"`},
		
		/**
		* Calculate amount of memory required for texture.
		Params:
			info = Resulting texture info structure. See: `TextureInfo`.
			width = Width.
			height = Height.
			depth = Depth dimension of volume texture.
			cubeMap = Indicates that texture contains cubemap.
			hasMIPs = Indicates that texture contains full mip-map chain.
			numLayers = Number of layers in texture array.
			format = Texture format. See: `TextureFormat::Enum`.
		*/
		{q{void}, q{calcTextureSize}, q{ref TextureInfo info, ushort width, ushort height, ushort depth, bool cubeMap, bool hasMIPs, ushort numLayers, bgfx.fakeenum.TextureFormat.Enum format}, ext: `C++, "bgfx"`},
		
		/**
		* Create texture from memory buffer.
		Params:
			mem = DDS, KTX or PVR texture binary data.
			flags = Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
		flags. Default texture sampling mode is linear, and wrap mode is repeat.
		- `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
		  mode.
		- `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
		  sampling.
			skip = Skip top level mips when parsing texture.
			info = When non-`NULL` is specified it returns parsed texture information.
		*/
		{q{TextureHandle}, q{createTexture}, q{const(Memory)* mem, c_uint64 flags, ubyte skip=0, TextureInfo* info=null}, ext: `C++, "bgfx"`},
		
		/**
		* Create 2D texture.
		Params:
			width = Width.
			height = Height.
			hasMIPs = Indicates that texture contains full mip-map chain.
			numLayers = Number of layers in texture array. Must be 1 if caps
		`BGFX_CAPS_TEXTURE_2D_ARRAY` flag is not set.
			format = Texture format. See: `TextureFormat::Enum`.
			flags = Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
		flags. Default texture sampling mode is linear, and wrap mode is repeat.
		- `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
		  mode.
		- `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
		  sampling.
			mem = Texture data. If `_mem` is non-NULL, created texture will be immutable. If
		`_mem` is NULL content of the texture is uninitialized. When `_numLayers` is more than
		1, expected memory layout is texture and all mips together for each array element.
		*/
		{q{TextureHandle}, q{createTexture2D}, q{ushort width, ushort height, bool hasMIPs, ushort numLayers, bgfx.fakeenum.TextureFormat.Enum format, c_uint64 flags, const(Memory)* mem=null}, ext: `C++, "bgfx"`},
		
		/**
		* Create texture with size based on back-buffer ratio. Texture will maintain ratio
		* if back buffer resolution changes.
		Params:
			ratio = Texture size in respect to back-buffer size. See: `BackbufferRatio::Enum`.
			hasMIPs = Indicates that texture contains full mip-map chain.
			numLayers = Number of layers in texture array. Must be 1 if caps
		`BGFX_CAPS_TEXTURE_2D_ARRAY` flag is not set.
			format = Texture format. See: `TextureFormat::Enum`.
			flags = Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
		flags. Default texture sampling mode is linear, and wrap mode is repeat.
		- `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
		  mode.
		- `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
		  sampling.
		*/
		{q{TextureHandle}, q{createTexture2D}, q{bgfx.fakeenum.BackbufferRatio.Enum ratio, bool hasMIPs, ushort numLayers, bgfx.fakeenum.TextureFormat.Enum format, c_uint64 flags=Texture.none|Sampler.none}, ext: `C++, "bgfx"`},
		
		/**
		* Create 3D texture.
		Params:
			width = Width.
			height = Height.
			depth = Depth.
			hasMIPs = Indicates that texture contains full mip-map chain.
			format = Texture format. See: `TextureFormat::Enum`.
			flags = Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
		flags. Default texture sampling mode is linear, and wrap mode is repeat.
		- `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
		  mode.
		- `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
		  sampling.
			mem = Texture data. If `_mem` is non-NULL, created texture will be immutable. If
		`_mem` is NULL content of the texture is uninitialized. When `_numLayers` is more than
		1, expected memory layout is texture and all mips together for each array element.
		*/
		{q{TextureHandle}, q{createTexture3D}, q{ushort width, ushort height, ushort depth, bool hasMIPs, bgfx.fakeenum.TextureFormat.Enum format, c_uint64 flags=Texture.none|Sampler.none, const(Memory)* mem=null}, ext: `C++, "bgfx"`},
		
		/**
		* Create Cube texture.
		Params:
			size = Cube side size.
			hasMIPs = Indicates that texture contains full mip-map chain.
			numLayers = Number of layers in texture array. Must be 1 if caps
		`BGFX_CAPS_TEXTURE_2D_ARRAY` flag is not set.
			format = Texture format. See: `TextureFormat::Enum`.
			flags = Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
		flags. Default texture sampling mode is linear, and wrap mode is repeat.
		- `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
		  mode.
		- `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
		  sampling.
			mem = Texture data. If `_mem` is non-NULL, created texture will be immutable. If
		`_mem` is NULL content of the texture is uninitialized. When `_numLayers` is more than
		1, expected memory layout is texture and all mips together for each array element.
		*/
		{q{TextureHandle}, q{createTextureCube}, q{ushort size, bool hasMIPs, ushort numLayers, bgfx.fakeenum.TextureFormat.Enum format, c_uint64 flags=Texture.none|Sampler.none, const(Memory)* mem=null}, ext: `C++, "bgfx"`},
		
		/**
		* Update 2D texture.
		* Attention: It's valid to update only mutable texture. See `bgfx::createTexture2D` for more info.
		Params:
			handle = Texture handle.
			layer = Layer in texture array.
			mip = Mip level.
			x = X offset in texture.
			y = Y offset in texture.
			width = Width of texture block.
			height = Height of texture block.
			mem = Texture update data.
			pitch = Pitch of input image (bytes). When _pitch is set to
		UINT16_MAX, it will be calculated internally based on _width.
		*/
		{q{void}, q{updateTexture2D}, q{TextureHandle handle, ushort layer, ubyte mip, ushort x, ushort y, ushort width, ushort height, const(Memory)* mem, ushort pitch=ushort.max}, ext: `C++, "bgfx"`},
		
		/**
		* Update 3D texture.
		* Attention: It's valid to update only mutable texture. See `bgfx::createTexture3D` for more info.
		Params:
			handle = Texture handle.
			mip = Mip level.
			x = X offset in texture.
			y = Y offset in texture.
			z = Z offset in texture.
			width = Width of texture block.
			height = Height of texture block.
			depth = Depth of texture block.
			mem = Texture update data.
		*/
		{q{void}, q{updateTexture3D}, q{TextureHandle handle, ubyte mip, ushort x, ushort y, ushort z, ushort width, ushort height, ushort depth, const(Memory)* mem}, ext: `C++, "bgfx"`},
		
		/**
		* Update Cube texture.
		* Attention: It's valid to update only mutable texture. See `bgfx::createTextureCube` for more info.
		Params:
			handle = Texture handle.
			layer = Layer in texture array.
			side = Cubemap side `BGFX_CUBE_MAP_<POSITIVE or NEGATIVE>_<X, Y or Z>`,
		  where 0 is +X, 1 is -X, 2 is +Y, 3 is -Y, 4 is +Z, and 5 is -Z.
		                 +----------+
		                 |-z       2|
		                 | ^  +y    |
		                 | |        |    Unfolded cube:
		                 | +---->+x |
		      +----------+----------+----------+----------+
		      |+y       1|+y       4|+y       0|+y       5|
		      | ^  -x    | ^  +z    | ^  +x    | ^  -z    |
		      | |        | |        | |        | |        |
		      | +---->+z | +---->+x | +---->-z | +---->-x |
		      +----------+----------+----------+----------+
		                 |+z       3|
		                 | ^  -y    |
		                 | |        |
		                 | +---->+x |
		                 +----------+
			mip = Mip level.
			x = X offset in texture.
			y = Y offset in texture.
			width = Width of texture block.
			height = Height of texture block.
			mem = Texture update data.
			pitch = Pitch of input image (bytes). When _pitch is set to
		UINT16_MAX, it will be calculated internally based on _width.
		*/
		{q{void}, q{updateTextureCube}, q{TextureHandle handle, ushort layer, ubyte side, ubyte mip, ushort x, ushort y, ushort width, ushort height, const(Memory)* mem, ushort pitch=ushort.max}, ext: `C++, "bgfx"`},
		
		/**
		* Read back texture content.
		* Attention: Texture must be created with `BGFX_TEXTURE_READ_BACK` flag.
		* Attention: Availability depends on: `BGFX_CAPS_TEXTURE_READ_BACK`.
		Params:
			handle = Texture handle.
			data = Destination buffer.
			mip = Mip level.
		*/
		{q{uint}, q{readTexture}, q{TextureHandle handle, void* data, ubyte mip=0}, ext: `C++, "bgfx"`},
		
		/**
		* Set texture debug name.
		Params:
			handle = Texture handle.
			name = Texture name.
			len = Texture name length (if length is INT32_MAX, it's expected
		that _name is zero terminated string.
		*/
		{q{void}, q{setName}, q{TextureHandle handle, const(char)* name, int len=int.max}, ext: `C++, "bgfx"`},
		
		/**
		* Returns texture direct access pointer.
		* Attention: Availability depends on: `BGFX_CAPS_TEXTURE_DIRECT_ACCESS`. This feature
		*   is available on GPUs that have unified memory architecture (UMA) support.
		Params:
			handle = Texture handle.
		*/
		{q{void*}, q{getDirectAccessPtr}, q{TextureHandle handle}, ext: `C++, "bgfx"`},
		
		/**
		* Destroy texture.
		Params:
			handle = Texture handle.
		*/
		{q{void}, q{destroy}, q{TextureHandle handle}, ext: `C++, "bgfx"`},
		
		/**
		* Create frame buffer (simple).
		Params:
			width = Texture width.
			height = Texture height.
			format = Texture format. See: `TextureFormat::Enum`.
			textureFlags = Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
		flags. Default texture sampling mode is linear, and wrap mode is repeat.
		- `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
		  mode.
		- `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
		  sampling.
		*/
		{q{FrameBufferHandle}, q{createFrameBuffer}, q{ushort width, ushort height, bgfx.fakeenum.TextureFormat.Enum format, c_uint64 textureFlags=SamplerU.clamp|SamplerV.clamp}, ext: `C++, "bgfx"`},
		
		/**
		* Create frame buffer with size based on back-buffer ratio. Frame buffer will maintain ratio
		* if back buffer resolution changes.
		Params:
			ratio = Frame buffer size in respect to back-buffer size. See:
		`BackbufferRatio::Enum`.
			format = Texture format. See: `TextureFormat::Enum`.
			textureFlags = Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
		flags. Default texture sampling mode is linear, and wrap mode is repeat.
		- `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
		  mode.
		- `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
		  sampling.
		*/
		{q{FrameBufferHandle}, q{createFrameBuffer}, q{bgfx.fakeenum.BackbufferRatio.Enum ratio, bgfx.fakeenum.TextureFormat.Enum format, c_uint64 textureFlags=SamplerU.clamp|SamplerV.clamp}, ext: `C++, "bgfx"`},
		
		/**
		* Create MRT frame buffer from texture handles (simple).
		Params:
			num = Number of texture handles.
			handles = Texture attachments.
			destroyTexture = If true, textures will be destroyed when
		frame buffer is destroyed.
		*/
		{q{FrameBufferHandle}, q{createFrameBuffer}, q{ubyte num, const(TextureHandle)* handles, bool destroyTexture=false}, ext: `C++, "bgfx"`},
		
		/**
		* Create MRT frame buffer from texture handles with specific layer and
		* mip level.
		Params:
			num = Number of attachments.
			attachment = Attachment texture info. See: `bgfx::Attachment`.
			destroyTexture = If true, textures will be destroyed when
		frame buffer is destroyed.
		*/
		{q{FrameBufferHandle}, q{createFrameBuffer}, q{ubyte num, const(Attachment)* attachment, bool destroyTexture=false}, ext: `C++, "bgfx"`},
		
		/**
		* Create frame buffer for multiple window rendering.
		* Remarks:
		*   Frame buffer cannot be used for sampling.
		* Attention: Availability depends on: `BGFX_CAPS_SWAP_CHAIN`.
		Params:
			nwh = OS' target native window handle.
			width = Window back buffer width.
			height = Window back buffer height.
			format = Window back buffer color format.
			depthFormat = Window back buffer depth format.
		*/
		{q{FrameBufferHandle}, q{createFrameBuffer}, q{void* nwh, ushort width, ushort height, bgfx.fakeenum.TextureFormat.Enum format=TextureFormat.count, bgfx.fakeenum.TextureFormat.Enum depthFormat=TextureFormat.count}, ext: `C++, "bgfx"`},
		
		/**
		* Set frame buffer debug name.
		Params:
			handle = Frame buffer handle.
			name = Frame buffer name.
			len = Frame buffer name length (if length is INT32_MAX, it's expected
		that _name is zero terminated string.
		*/
		{q{void}, q{setName}, q{FrameBufferHandle handle, const(char)* name, int len=int.max}, ext: `C++, "bgfx"`},
		
		/**
		* Obtain texture handle of frame buffer attachment.
		Params:
			handle = Frame buffer handle.
		*/
		{q{TextureHandle}, q{getTexture}, q{FrameBufferHandle handle, ubyte attachment=0}, ext: `C++, "bgfx"`},
		
		/**
		* Destroy frame buffer.
		Params:
			handle = Frame buffer handle.
		*/
		{q{void}, q{destroy}, q{FrameBufferHandle handle}, ext: `C++, "bgfx"`},
		
		/**
		* Create shader uniform parameter.
		* Remarks:
		*   1. Uniform names are unique. It's valid to call `bgfx::createUniform`
		*      multiple times with the same uniform name. The library will always
		*      return the same handle, but the handle reference count will be
		*      incremented. This means that the same number of `bgfx::destroyUniform`
		*      must be called to properly destroy the uniform.
		*   2. Predefined uniforms (declared in `bgfx_shader.sh`):
		*      - `u_viewRect vec4(x, y, width, height)` - view rectangle for current
		*        view, in pixels.
		*      - `u_viewTexel vec4(1.0/width, 1.0/height, undef, undef)` - inverse
		*        width and height
		*      - `u_view mat4` - view matrix
		*      - `u_invView mat4` - inverted view matrix
		*      - `u_proj mat4` - projection matrix
		*      - `u_invProj mat4` - inverted projection matrix
		*      - `u_viewProj mat4` - concatenated view projection matrix
		*      - `u_invViewProj mat4` - concatenated inverted view projection matrix
		*      - `u_model mat4[BGFX_CONFIG_MAX_BONES]` - array of model matrices.
		*      - `u_modelView mat4` - concatenated model view matrix, only first
		*        model matrix from array is used.
		*      - `u_modelViewProj mat4` - concatenated model view projection matrix.
		*      - `u_alphaRef float` - alpha reference value for alpha test.
		Params:
			name = Uniform name in shader.
			type = Type of uniform (See: `bgfx::UniformType`).
			num = Number of elements in array.
		*/
		{q{UniformHandle}, q{createUniform}, q{const(char)* name, bgfx.fakeenum.UniformType.Enum type, ushort num=1}, ext: `C++, "bgfx"`},
		
		/**
		* Retrieve uniform info.
		Params:
			handle = Handle to uniform object.
			info = Uniform info.
		*/
		{q{void}, q{getUniformInfo}, q{UniformHandle handle, ref UniformInfo info}, ext: `C++, "bgfx"`},
		
		/**
		* Destroy shader uniform parameter.
		Params:
			handle = Handle to uniform object.
		*/
		{q{void}, q{destroy}, q{UniformHandle handle}, ext: `C++, "bgfx"`},
		
		/**
		* Create occlusion query.
		*/
		{q{OcclusionQueryHandle}, q{createOcclusionQuery}, q{}, ext: `C++, "bgfx"`},
		
		/**
		* Retrieve occlusion query result from previous frame.
		Params:
			handle = Handle to occlusion query object.
			result = Number of pixels that passed test. This argument
		can be `NULL` if result of occlusion query is not needed.
		*/
		{q{OcclusionQueryResult}, q{getResult}, q{OcclusionQueryHandle handle, int* result=null}, ext: `C++, "bgfx"`},
		
		/**
		* Destroy occlusion query.
		Params:
			handle = Handle to occlusion query object.
		*/
		{q{void}, q{destroy}, q{OcclusionQueryHandle handle}, ext: `C++, "bgfx"`},
		
		/**
		* Set palette color value.
		Params:
			index = Index into palette.
			rgba = RGBA floating point values.
		*/
		{q{void}, q{setPaletteColor}, q{ubyte index, const(float)* rgba}, ext: `C++, "bgfx"`},
		
		/**
		* Set palette color value.
		Params:
			index = Index into palette.
			rgba = Packed 32-bit RGBA value.
		*/
		{q{void}, q{setPaletteColor}, q{ubyte index, uint rgba}, ext: `C++, "bgfx"`},
		
		/**
		* Set view name.
		* Remarks:
		*   This is debug only feature.
		*   In graphics debugger view name will appear as:
		*       "nnnc <view name>"
		*        ^  ^ ^
		*        |  +--- compute (C)
		*        +------ view id
		Params:
			id = View id.
			name = View name.
			len = View name length (if length is INT32_MAX, it's expected
		that _name is zero terminated string.
		*/
		{q{void}, q{setViewName}, q{ViewID id, const(char)* name, int len=int.max}, ext: `C++, "bgfx"`},
		
		/**
		* Set view rectangle. Draw primitive outside view will be clipped.
		Params:
			id = View id.
			x = Position x from the left corner of the window.
			y = Position y from the top corner of the window.
			width = Width of view port region.
			height = Height of view port region.
		*/
		{q{void}, q{setViewRect}, q{ViewID id, ushort x, ushort y, ushort width, ushort height}, ext: `C++, "bgfx"`},
		
		/**
		* Set view rectangle. Draw primitive outside view will be clipped.
		Params:
			id = View id.
			x = Position x from the left corner of the window.
			y = Position y from the top corner of the window.
			ratio = Width and height will be set in respect to back-buffer size.
		See: `BackbufferRatio::Enum`.
		*/
		{q{void}, q{setViewRect}, q{ViewID id, ushort x, ushort y, bgfx.fakeenum.BackbufferRatio.Enum ratio}, ext: `C++, "bgfx"`},
		
		/**
		* Set view scissor. Draw primitive outside view will be clipped. When
		* _x, _y, _width and _height are set to 0, scissor will be disabled.
		Params:
			id = View id.
			x = Position x from the left corner of the window.
			y = Position y from the top corner of the window.
			width = Width of view scissor region.
			height = Height of view scissor region.
		*/
		{q{void}, q{setViewScissor}, q{ViewID id, ushort x=0, ushort y=0, ushort width=0, ushort height=0}, ext: `C++, "bgfx"`},
		
		/**
		* Set view clear flags.
		Params:
			id = View id.
			flags = Clear flags. Use `BGFX_CLEAR_NONE` to remove any clear
		operation. See: `BGFX_CLEAR_*`.
			rgba = Color clear value.
			depth = Depth clear value.
			stencil = Stencil clear value.
		*/
		{q{void}, q{setViewClear}, q{ViewID id, ushort flags, uint rgba=0x000000ff, float depth=1.0f, ubyte stencil=0}, ext: `C++, "bgfx"`},
		
		/**
		* Set view clear flags with different clear color for each
		* frame buffer texture. `bgfx::setPaletteColor` must be used to set up a
		* clear color palette.
		Params:
			id = View id.
			flags = Clear flags. Use `BGFX_CLEAR_NONE` to remove any clear
		operation. See: `BGFX_CLEAR_*`.
			depth = Depth clear value.
			stencil = Stencil clear value.
			c0 = Palette index for frame buffer attachment 0.
			c1 = Palette index for frame buffer attachment 1.
			c2 = Palette index for frame buffer attachment 2.
			c3 = Palette index for frame buffer attachment 3.
			c4 = Palette index for frame buffer attachment 4.
			c5 = Palette index for frame buffer attachment 5.
			c6 = Palette index for frame buffer attachment 6.
			c7 = Palette index for frame buffer attachment 7.
		*/
		{q{void}, q{setViewClear}, q{ViewID id, ushort flags, float depth, ubyte stencil, ubyte c0=ubyte.max, ubyte c1=ubyte.max, ubyte c2=ubyte.max, ubyte c3=ubyte.max, ubyte c4=ubyte.max, ubyte c5=ubyte.max, ubyte c6=ubyte.max, ubyte c7=ubyte.max}, ext: `C++, "bgfx"`},
		
		/**
		* Set view sorting mode.
		* Remarks:
		*   View mode must be set prior calling `bgfx::submit` for the view.
		Params:
			id = View id.
			mode = View sort mode. See `ViewMode::Enum`.
		*/
		{q{void}, q{setViewMode}, q{ViewID id, bgfx.fakeenum.ViewMode.Enum mode=ViewMode.default_}, ext: `C++, "bgfx"`},
		
		/**
		* Set view frame buffer.
		* Remarks:
		*   Not persistent after `bgfx::reset` call.
		Params:
			id = View id.
			handle = Frame buffer handle. Passing `BGFX_INVALID_HANDLE` as
		frame buffer handle will draw primitives from this view into
		default back buffer.
		*/
		{q{void}, q{setViewFrameBuffer}, q{ViewID id, FrameBufferHandle handle}, ext: `C++, "bgfx"`},
		
		/**
		* Set view's view matrix and projection matrix,
		* all draw primitives in this view will use these two matrices.
		Params:
			id = View id.
			view = View matrix.
			proj = Projection matrix.
		*/
		{q{void}, q{setViewTransform}, q{ViewID id, const(void)* view, const(void)* proj}, ext: `C++, "bgfx"`},
		
		/**
		* Post submit view reordering.
		Params:
			id = First view id.
			num = Number of views to remap.
			order = View remap id table. Passing `NULL` will reset view ids
		to default state.
		*/
		{q{void}, q{setViewOrder}, q{ViewID id=0, ushort num=ushort.max, const(ViewID)* order=null}, ext: `C++, "bgfx"`},
		
		/**
		* Reset all view settings to default.
		*/
		{q{void}, q{resetView}, q{ViewID id}, ext: `C++, "bgfx"`},
		
		/**
		* Begin submitting draw calls from thread.
		Params:
			forThread = Explicitly request an encoder for a worker thread.
		*/
		{q{Encoder*}, q{begin}, q{bool forThread=false}, ext: `C++, "bgfx"`},
		
		/**
		* End submitting draw calls from thread.
		Params:
			encoder = Encoder.
		*/
		{q{void}, q{end}, q{Encoder* encoder}, ext: `C++, "bgfx"`},
		
		/**
		* Request screen shot of window back buffer.
		* Remarks:
		*   `bgfx::CallbackI::screenShot` must be implemented.
		* Attention: Frame buffer handle must be created with OS' target native window handle.
		Params:
			handle = Frame buffer handle. If handle is `BGFX_INVALID_HANDLE` request will be
		made for main window back buffer.
			filePath = Will be passed to `bgfx::CallbackI::screenShot` callback.
		*/
		{q{void}, q{requestScreenShot}, q{FrameBufferHandle handle, const(char)* filePath}, ext: `C++, "bgfx"`},
		
		/**
		* Render frame.
		* Attention: `bgfx::renderFrame` is blocking call. It waits for
		*   `bgfx::frame` to be called from API thread to process frame.
		*   If timeout value is passed call will timeout and return even
		*   if `bgfx::frame` is not called.
		* Warning: This call should be only used on platforms that don't
		*   allow creating separate rendering thread. If it is called before
		*   to bgfx::init, render thread won't be created by bgfx::init call.
		Params:
			msecs = Timeout in milliseconds.
		*/
		{q{RenderFrame}, q{renderFrame}, q{int msecs=-1}, ext: `C++, "bgfx"`},
		
		/**
		* Set platform data.
		* Warning: Must be called before `bgfx::init`.
		Params:
			data = Platform data.
		*/
		{q{void}, q{setPlatformData}, q{ref const PlatformData data}, ext: `C++, "bgfx"`},
		
		/**
		* Get internal data for interop.
		* Attention: It's expected you understand some bgfx internals before you
		*   use this call.
		* Warning: Must be called only on render thread.
		*/
		{q{const(InternalData)*}, q{getInternalData}, q{}, ext: `C++, "bgfx"`},
		
		/**
		* Override internal texture with externally created texture. Previously
		* created internal texture will released.
		* Attention: It's expected you understand some bgfx internals before you
		*   use this call.
		* Warning: Must be called only on render thread.
		Params:
			handle = Texture handle.
			ptr = Native API pointer to texture.
		*/
		{q{size_t}, q{overrideInternal}, q{TextureHandle handle, size_t ptr}, ext: `C++, "bgfx"`},
		
		/**
		* Override internal texture by creating new texture. Previously created
		* internal texture will released.
		* Attention: It's expected you understand some bgfx internals before you
		*   use this call.
		* Returns: Native API pointer to texture. If result is 0, texture is not created yet from the
		*   main thread.
		* Warning: Must be called only on render thread.
		Params:
			handle = Texture handle.
			width = Width.
			height = Height.
			numMIPs = Number of mip-maps.
			format = Texture format. See: `TextureFormat::Enum`.
			flags = Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
		flags. Default texture sampling mode is linear, and wrap mode is repeat.
		- `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
		  mode.
		- `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
		  sampling.
		*/
		{q{size_t}, q{overrideInternal}, q{TextureHandle handle, ushort width, ushort height, ubyte numMIPs, bgfx.fakeenum.TextureFormat.Enum format, c_uint64 flags=Texture.none | Sampler.none}, ext: `C++, "bgfx"`},
		
		/**
		* Sets a debug marker. This allows you to group graphics calls together for easy browsing in
		* graphics debugging tools.
		Params:
			name = Marker name.
			len = Marker name length (if length is INT32_MAX, it's expected
		that _name is zero terminated string.
		*/
		{q{void}, q{setMarker}, q{const(char)* name, int len=int.max}, ext: `C++, "bgfx"`},
		
		/**
		* Set render states for draw primitive.
		* Remarks:
		*   1. To set up more complex states use:
		*      `BGFX_STATE_ALPHA_REF(_ref)`,
		*      `BGFX_STATE_POINT_SIZE(_size)`,
		*      `BGFX_STATE_BLEND_FUNC(_src, _dst)`,
		*      `BGFX_STATE_BLEND_FUNC_SEPARATE(_srcRGB, _dstRGB, _srcA, _dstA)`,
		*      `BGFX_STATE_BLEND_EQUATION(_equation)`,
		*      `BGFX_STATE_BLEND_EQUATION_SEPARATE(_equationRGB, _equationA)`
		*   2. `BGFX_STATE_BLEND_EQUATION_ADD` is set when no other blend
		*      equation is specified.
		Params:
			state = State flags. Default state for primitive type is
		  triangles. See: `BGFX_STATE_DEFAULT`.
		  - `BGFX_STATE_DEPTH_TEST_*` - Depth test function.
		  - `BGFX_STATE_BLEND_*` - See remark 1 about BGFX_STATE_BLEND_FUNC.
		  - `BGFX_STATE_BLEND_EQUATION_*` - See remark 2.
		  - `BGFX_STATE_CULL_*` - Backface culling mode.
		  - `BGFX_STATE_WRITE_*` - Enable R, G, B, A or Z write.
		  - `BGFX_STATE_MSAA` - Enable hardware multisample antialiasing.
		  - `BGFX_STATE_PT_[TRISTRIP/LINES/POINTS]` - Primitive type.
			rgba = Sets blend factor used by `BGFX_STATE_BLEND_FACTOR` and
		  `BGFX_STATE_BLEND_INV_FACTOR` blend modes.
		*/
		{q{void}, q{setState}, q{c_uint64 state, uint rgba=0}, ext: `C++, "bgfx"`},
		
		/**
		* Set condition for rendering.
		Params:
			handle = Occlusion query handle.
			visible = Render if occlusion query is visible.
		*/
		{q{void}, q{setCondition}, q{OcclusionQueryHandle handle, bool visible}, ext: `C++, "bgfx"`},
		
		/**
		* Set stencil test state.
		Params:
			fStencil = Front stencil state.
			bStencil = Back stencil state. If back is set to `BGFX_STENCIL_NONE`
		_fstencil is applied to both front and back facing primitives.
		*/
		{q{void}, q{setStencil}, q{uint fStencil, uint bStencil=Stencil.none}, ext: `C++, "bgfx"`},
		
		/**
		* Set scissor for draw primitive.
		* Remarks:
		*   To scissor for all primitives in view see `bgfx::setViewScissor`.
		Params:
			x = Position x from the left corner of the window.
			y = Position y from the top corner of the window.
			width = Width of view scissor region.
			height = Height of view scissor region.
		*/
		{q{ushort}, q{setScissor}, q{ushort x, ushort y, ushort width, ushort height}, ext: `C++, "bgfx"`},
		
		/**
		* Set scissor from cache for draw primitive.
		* Remarks:
		*   To scissor for all primitives in view see `bgfx::setViewScissor`.
		Params:
			cache = Index in scissor cache.
		*/
		{q{void}, q{setScissor}, q{ushort cache=ushort.max}, ext: `C++, "bgfx"`},
		
		/**
		* Set model matrix for draw primitive. If it is not called,
		* the model will be rendered with an identity model matrix.
		Params:
			mtx = Pointer to first matrix in array.
			num = Number of matrices in array.
		*/
		{q{uint}, q{setTransform}, q{const(void)* mtx, ushort num=1}, ext: `C++, "bgfx"`},
		
		/**
		*  Set model matrix from matrix cache for draw primitive.
		Params:
			cache = Index in matrix cache.
			num = Number of matrices from cache.
		*/
		{q{void}, q{setTransform}, q{uint cache, ushort num=1}, ext: `C++, "bgfx"`},
		
		/**
		* Reserve matrices in internal matrix cache.
		* Attention: Pointer returned can be modified until `bgfx::frame` is called.
		Params:
			transform = Pointer to `Transform` structure.
			num = Number of matrices.
		*/
		{q{uint}, q{allocTransform}, q{Transform* transform, ushort num}, ext: `C++, "bgfx"`},
		
		/**
		* Set shader uniform parameter for draw primitive.
		Params:
			handle = Uniform.
			value = Pointer to uniform data.
			num = Number of elements. Passing `UINT16_MAX` will
		use the _num passed on uniform creation.
		*/
		{q{void}, q{setUniform}, q{UniformHandle handle, const(void)* value, ushort num=1}, ext: `C++, "bgfx"`},
		
		/**
		* Set index buffer for draw primitive.
		Params:
			handle = Index buffer.
		*/
		{q{void}, q{setIndexBuffer}, q{IndexBufferHandle handle}, ext: `C++, "bgfx"`},
		
		/**
		* Set index buffer for draw primitive.
		Params:
			handle = Index buffer.
			firstIndex = First index to render.
			numIndices = Number of indices to render.
		*/
		{q{void}, q{setIndexBuffer}, q{IndexBufferHandle handle, uint firstIndex, uint numIndices}, ext: `C++, "bgfx"`},
		
		/**
		* Set index buffer for draw primitive.
		Params:
			handle = Dynamic index buffer.
		*/
		{q{void}, q{setIndexBuffer}, q{DynamicIndexBufferHandle handle}, ext: `C++, "bgfx"`},
		
		/**
		* Set index buffer for draw primitive.
		Params:
			handle = Dynamic index buffer.
			firstIndex = First index to render.
			numIndices = Number of indices to render.
		*/
		{q{void}, q{setIndexBuffer}, q{DynamicIndexBufferHandle handle, uint firstIndex, uint numIndices}, ext: `C++, "bgfx"`},
		
		/**
		* Set index buffer for draw primitive.
		Params:
			tib = Transient index buffer.
		*/
		{q{void}, q{setIndexBuffer}, q{const(TransientIndexBuffer)* tib}, ext: `C++, "bgfx"`},
		
		/**
		* Set index buffer for draw primitive.
		Params:
			tib = Transient index buffer.
			firstIndex = First index to render.
			numIndices = Number of indices to render.
		*/
		{q{void}, q{setIndexBuffer}, q{const(TransientIndexBuffer)* tib, uint firstIndex, uint numIndices}, ext: `C++, "bgfx"`},
		
		/**
		* Set vertex buffer for draw primitive.
		Params:
			stream = Vertex stream.
			handle = Vertex buffer.
		*/
		{q{void}, q{setVertexBuffer}, q{ubyte stream, VertexBufferHandle handle}, ext: `C++, "bgfx"`},
		
		/**
		* Set vertex buffer for draw primitive.
		Params:
			stream = Vertex stream.
			handle = Vertex buffer.
			startVertex = First vertex to render.
			numVertices = Number of vertices to render.
			layoutHandle = Vertex layout for aliasing vertex buffer. If invalid
		handle is used, vertex layout used for creation
		of vertex buffer will be used.
		*/
		{q{void}, q{setVertexBuffer}, q{ubyte stream, VertexBufferHandle handle, uint startVertex, uint numVertices, VertexLayoutHandle layoutHandle=invalidHandle!VertexLayoutHandle}, ext: `C++, "bgfx"`},
		
		/**
		* Set vertex buffer for draw primitive.
		Params:
			stream = Vertex stream.
			handle = Dynamic vertex buffer.
		*/
		{q{void}, q{setVertexBuffer}, q{ubyte stream, DynamicVertexBufferHandle handle}, ext: `C++, "bgfx"`},
		
		/**
		* Set vertex buffer for draw primitive.
		Params:
			stream = Vertex stream.
			handle = Dynamic vertex buffer.
			startVertex = First vertex to render.
			numVertices = Number of vertices to render.
			layoutHandle = Vertex layout for aliasing vertex buffer. If invalid
		handle is used, vertex layout used for creation
		of vertex buffer will be used.
		*/
		{q{void}, q{setVertexBuffer}, q{ubyte stream, DynamicVertexBufferHandle handle, uint startVertex, uint numVertices, VertexLayoutHandle layoutHandle=invalidHandle!VertexLayoutHandle}, ext: `C++, "bgfx"`},
		
		/**
		* Set vertex buffer for draw primitive.
		Params:
			stream = Vertex stream.
			tvb = Transient vertex buffer.
		*/
		{q{void}, q{setVertexBuffer}, q{ubyte stream, const(TransientVertexBuffer)* tvb}, ext: `C++, "bgfx"`},
		
		/**
		* Set vertex buffer for draw primitive.
		Params:
			stream = Vertex stream.
			tvb = Transient vertex buffer.
			startVertex = First vertex to render.
			numVertices = Number of vertices to render.
			layoutHandle = Vertex layout for aliasing vertex buffer. If invalid
		handle is used, vertex layout used for creation
		of vertex buffer will be used.
		*/
		{q{void}, q{setVertexBuffer}, q{ubyte stream, const(TransientVertexBuffer)* tvb, uint startVertex, uint numVertices, VertexLayoutHandle layoutHandle=invalidHandle!VertexLayoutHandle}, ext: `C++, "bgfx"`},
		
		/**
		* Set number of vertices for auto generated vertices use in conjunction
		* with gl_VertexID.
		* Attention: Availability depends on: `BGFX_CAPS_VERTEX_ID`.
		Params:
			numVertices = Number of vertices.
		*/
		{q{void}, q{setVertexCount}, q{uint numVertices}, ext: `C++, "bgfx"`},
		
		/**
		* Set instance data buffer for draw primitive.
		Params:
			idb = Transient instance data buffer.
		*/
		{q{void}, q{setInstanceDataBuffer}, q{const(InstanceDataBuffer)* idb}, ext: `C++, "bgfx"`},
		
		/**
		* Set instance data buffer for draw primitive.
		Params:
			idb = Transient instance data buffer.
			start = First instance data.
			num = Number of data instances.
		*/
		{q{void}, q{setInstanceDataBuffer}, q{const(InstanceDataBuffer)* idb, uint start, uint num}, ext: `C++, "bgfx"`},
		
		/**
		* Set instance data buffer for draw primitive.
		Params:
			handle = Vertex buffer.
			startVertex = First instance data.
			num = Number of data instances.
		*/
		{q{void}, q{setInstanceDataBuffer}, q{VertexBufferHandle handle, uint startVertex, uint num}, ext: `C++, "bgfx"`},
		
		/**
		* Set instance data buffer for draw primitive.
		Params:
			handle = Dynamic vertex buffer.
			startVertex = First instance data.
			num = Number of data instances.
		*/
		{q{void}, q{setInstanceDataBuffer}, q{DynamicVertexBufferHandle handle, uint startVertex, uint num}, ext: `C++, "bgfx"`},
		
		/**
		* Set number of instances for auto generated instances use in conjunction
		* with gl_InstanceID.
		* Attention: Availability depends on: `BGFX_CAPS_VERTEX_ID`.
		*/
		{q{void}, q{setInstanceCount}, q{uint numInstances}, ext: `C++, "bgfx"`},
		
		/**
		* Set texture stage for draw primitive.
		Params:
			stage = Texture unit.
			sampler = Program sampler.
			handle = Texture handle.
			flags = Texture sampling mode. Default value UINT32_MAX uses
		  texture sampling settings from the texture.
		  - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
		    mode.
		  - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
		    sampling.
		*/
		{q{void}, q{setTexture}, q{ubyte stage, UniformHandle sampler, TextureHandle handle, uint flags=uint.max}, ext: `C++, "bgfx"`},
		
		/**
		* Submit an empty primitive for rendering. Uniforms and draw state
		* will be applied but no geometry will be submitted.
		* Remarks:
		*   These empty draw calls will sort before ordinary draw calls.
		Params:
			id = View id.
		*/
		{q{void}, q{touch}, q{ViewID id}, ext: `C++, "bgfx"`},
		
		/**
		* Submit primitive for rendering.
		Params:
			id = View id.
			program = Program.
			depth = Depth for sorting.
			flags = Which states to discard for next draw. See `BGFX_DISCARD_*`.
		*/
		{q{void}, q{submit}, q{ViewID id, ProgramHandle program, uint depth=0, ubyte flags=Discard.all}, ext: `C++, "bgfx"`},
		
		/**
		* Submit primitive with occlusion query for rendering.
		Params:
			id = View id.
			program = Program.
			occlusionQuery = Occlusion query.
			depth = Depth for sorting.
			flags = Which states to discard for next draw. See `BGFX_DISCARD_*`.
		*/
		{q{void}, q{submit}, q{ViewID id, ProgramHandle program, OcclusionQueryHandle occlusionQuery, uint depth=0, ubyte flags=Discard.all}, ext: `C++, "bgfx"`},
		
		/**
		* Submit primitive for rendering with index and instance data info from
		* indirect buffer.
		* Attention: Availability depends on: `BGFX_CAPS_DRAW_INDIRECT`.
		Params:
			id = View id.
			program = Program.
			indirectHandle = Indirect buffer.
			start = First element in indirect buffer.
			num = Number of draws.
			depth = Depth for sorting.
			flags = Which states to discard for next draw. See `BGFX_DISCARD_*`.
		*/
		{q{void}, q{submit}, q{ViewID id, ProgramHandle program, IndirectBufferHandle indirectHandle, uint start=0, uint num=1, uint depth=0, ubyte flags=Discard.all}, ext: `C++, "bgfx"`},
		
		/**
		* Submit primitive for rendering with index and instance data info and
		* draw count from indirect buffers.
		* Attention: Availability depends on: `BGFX_CAPS_DRAW_INDIRECT_COUNT`.
		Params:
			id = View id.
			program = Program.
			indirectHandle = Indirect buffer.
			start = First element in indirect buffer.
			numHandle = Buffer for number of draws. Must be
		  created with `BGFX_BUFFER_INDEX32` and `BGFX_BUFFER_DRAW_INDIRECT`.
			numIndex = Element in number buffer.
			numMax = Max number of draws.
			depth = Depth for sorting.
			flags = Which states to discard for next draw. See `BGFX_DISCARD_*`.
		*/
		{q{void}, q{submit}, q{ViewID id, ProgramHandle program, IndirectBufferHandle indirectHandle, uint start, IndexBufferHandle numHandle, uint numIndex=0, uint numMax=uint.max, uint depth=0, ubyte flags=Discard.all}, ext: `C++, "bgfx"`},
		
		/**
		* Set compute index buffer.
		Params:
			stage = Compute stage.
			handle = Index buffer handle.
			access = Buffer access. See `Access::Enum`.
		*/
		{q{void}, q{setBuffer}, q{ubyte stage, IndexBufferHandle handle, bgfx.fakeenum.Access.Enum access}, ext: `C++, "bgfx"`},
		
		/**
		* Set compute vertex buffer.
		Params:
			stage = Compute stage.
			handle = Vertex buffer handle.
			access = Buffer access. See `Access::Enum`.
		*/
		{q{void}, q{setBuffer}, q{ubyte stage, VertexBufferHandle handle, bgfx.fakeenum.Access.Enum access}, ext: `C++, "bgfx"`},
		
		/**
		* Set compute dynamic index buffer.
		Params:
			stage = Compute stage.
			handle = Dynamic index buffer handle.
			access = Buffer access. See `Access::Enum`.
		*/
		{q{void}, q{setBuffer}, q{ubyte stage, DynamicIndexBufferHandle handle, bgfx.fakeenum.Access.Enum access}, ext: `C++, "bgfx"`},
		
		/**
		* Set compute dynamic vertex buffer.
		Params:
			stage = Compute stage.
			handle = Dynamic vertex buffer handle.
			access = Buffer access. See `Access::Enum`.
		*/
		{q{void}, q{setBuffer}, q{ubyte stage, DynamicVertexBufferHandle handle, bgfx.fakeenum.Access.Enum access}, ext: `C++, "bgfx"`},
		
		/**
		* Set compute indirect buffer.
		Params:
			stage = Compute stage.
			handle = Indirect buffer handle.
			access = Buffer access. See `Access::Enum`.
		*/
		{q{void}, q{setBuffer}, q{ubyte stage, IndirectBufferHandle handle, bgfx.fakeenum.Access.Enum access}, ext: `C++, "bgfx"`},
		
		/**
		* Set compute image from texture.
		Params:
			stage = Compute stage.
			handle = Texture handle.
			mip = Mip level.
			access = Image access. See `Access::Enum`.
			format = Texture format. See: `TextureFormat::Enum`.
		*/
		{q{void}, q{setImage}, q{ubyte stage, TextureHandle handle, ubyte mip, bgfx.fakeenum.Access.Enum access, bgfx.fakeenum.TextureFormat.Enum format=TextureFormat.count}, ext: `C++, "bgfx"`},
		
		/**
		* Dispatch compute.
		Params:
			id = View id.
			program = Compute program.
			numX = Number of groups X.
			numY = Number of groups Y.
			numZ = Number of groups Z.
			flags = Discard or preserve states. See `BGFX_DISCARD_*`.
		*/
		{q{void}, q{dispatch}, q{ViewID id, ProgramHandle program, uint numX=1, uint numY=1, uint numZ=1, ubyte flags=Discard.all}, ext: `C++, "bgfx"`},
		
		/**
		* Dispatch compute indirect.
		Params:
			id = View id.
			program = Compute program.
			indirectHandle = Indirect buffer.
			start = First element in indirect buffer.
			num = Number of dispatches.
			flags = Discard or preserve states. See `BGFX_DISCARD_*`.
		*/
		{q{void}, q{dispatch}, q{ViewID id, ProgramHandle program, IndirectBufferHandle indirectHandle, uint start=0, uint num=1, ubyte flags=Discard.all}, ext: `C++, "bgfx"`},
		
		/**
		* Discard previously set state for draw or compute call.
		Params:
			flags = Draw/compute states to discard.
		*/
		{q{void}, q{discard}, q{ubyte flags=Discard.all}, ext: `C++, "bgfx"`},
		
		/**
		* Blit 2D texture region between two 2D textures.
		* Attention: Destination texture must be created with `BGFX_TEXTURE_BLIT_DST` flag.
		* Attention: Availability depends on: `BGFX_CAPS_TEXTURE_BLIT`.
		Params:
			id = View id.
			dst = Destination texture handle.
			dstX = Destination texture X position.
			dstY = Destination texture Y position.
			src = Source texture handle.
			srcX = Source texture X position.
			srcY = Source texture Y position.
			width = Width of region.
			height = Height of region.
		*/
		{q{void}, q{blit}, q{ViewID id, TextureHandle dst, ushort dstX, ushort dstY, TextureHandle src, ushort srcX=0, ushort srcY=0, ushort width=ushort.max, ushort height=ushort.max}, ext: `C++, "bgfx"`},
		
		/**
		* Blit 2D texture region between two 2D textures.
		* Attention: Destination texture must be created with `BGFX_TEXTURE_BLIT_DST` flag.
		* Attention: Availability depends on: `BGFX_CAPS_TEXTURE_BLIT`.
		Params:
			id = View id.
			dst = Destination texture handle.
			dstMIP = Destination texture mip level.
			dstX = Destination texture X position.
			dstY = Destination texture Y position.
			dstZ = If texture is 2D this argument should be 0. If destination texture is cube
		this argument represents destination texture cube face. For 3D texture this argument
		represents destination texture Z position.
			src = Source texture handle.
			srcMIP = Source texture mip level.
			srcX = Source texture X position.
			srcY = Source texture Y position.
			srcZ = If texture is 2D this argument should be 0. If source texture is cube
		this argument represents source texture cube face. For 3D texture this argument
		represents source texture Z position.
			width = Width of region.
			height = Height of region.
			depth = If texture is 3D this argument represents depth of region, otherwise it's
		unused.
		*/
		{q{void}, q{blit}, q{ViewID id, TextureHandle dst, ubyte dstMIP, ushort dstX, ushort dstY, ushort dstZ, TextureHandle src, ubyte srcMIP=0, ushort srcX=0, ushort srcY=0, ushort srcZ=0, ushort width=ushort.max, ushort height=ushort.max, ushort depth=ushort.max}, ext: `C++, "bgfx"`},
		
	];
	return ret;
}(), "Resolution, Init, Attachment, VertexLayout, Encoder, "));

static if(!staticBinding):
import bindbc.loader;

debug{
	mixin(makeDynloadFns("Bgfx", makeLibPaths(["bgfx-shared-libDebug", "bgfxDebug", "bgfx"]), [__MODULE__]));
}else{
	mixin(makeDynloadFns("Bgfx", makeLibPaths(["bgfx-shared-libRelease", "bgfxRelease", "bgfx"]), [__MODULE__]));
}
