/+
+ ┌──────────────────────────────┐
+ │ AUTO GENERATED! DO NOT EDIT! │
+ └──────────────────────────────┘
+/
module bgfx;

import bindbc.bgfx.config;

import bindbc.common.types: va_list;

enum uint apiVersion = 118;

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
	lequal    = 0x0000_0000_0000_0020, ///Enable depth test, less or equal.
	equal     = 0x0000_0000_0000_0030, ///Enable depth test, equal.
	gequal    = 0x0000_0000_0000_0040, ///Enable depth test, greater or equal.
	greater   = 0x0000_0000_0000_0050, ///Enable depth test, greater.
	notequal  = 0x0000_0000_0000_0060, ///Enable depth test, not equal.
	never     = 0x0000_0000_0000_0070, ///Enable depth test, never.
	always    = 0x0000_0000_0000_0080, ///Enable depth test, always.
	shift     = 4, ///Depth test state bit shift
	mask      = 0x0000_0000_0000_00F0, ///Depth test state bit mask
}

/**
* Use BGFX_STATE_BLEND_FUNC(_src, _dst) or BGFX_STATE_BLEND_FUNC_SEPARATE(_srcRGB, _dstRGB, _srcA, _dstA)
* helper macros.
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
* Use BGFX_STATE_BLEND_EQUATION(_equation) or BGFX_STATE_BLEND_EQUATION_SEPARATE(_equationRGB, _equationA)
* helper macros.
*/
alias StateBlendEquation_ = ulong;
enum StateBlendEquation: StateBlendEquation_{
	add     = 0x0000_0000_0000_0000, ///Blend add: src + dst.
	sub     = 0x0000_0000_1000_0000, ///Blend subtract: src - dst.
	revsub  = 0x0000_0000_2000_0000, ///Blend reverse subtract: dst - src.
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
	shift  = 36, ///Culling mode bit shift
	mask   = 0x0000_0030_0000_0000, ///Culling mode bit mask
}

///Alpha reference value.
alias StateAlphaRef_ = ulong;
enum StateAlphaRef: StateAlphaRef_{
	shift  = 40, ///Alpha reference bit shift
	mask   = 0x0000_FF00_0000_0000, ///Alpha reference bit mask
}
StateAlphaRef_ toStateAlphaRef(ulong v){ return (v << shift) & mask; }

alias StatePt_ = ulong;
enum StatePt: StatePt_{
	tristrip   = 0x0001_0000_0000_0000, ///Tristrip.
	lines      = 0x0002_0000_0000_0000, ///Lines.
	linestrip  = 0x0003_0000_0000_0000, ///Line strip.
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
StatePointSize_ toStatePointSize(ulong v){ return (v << shift) & mask; }

/**
* Enable MSAA write when writing into MSAA frame buffer.
* This flag is ignored when not writing into MSAA frame buffer.
*/
alias State_ = ulong;
enum State: State_{
	msaa                  = 0x0100_0000_0000_0000, ///Enable MSAA rasterization.
	lineaa                = 0x0200_0000_0000_0000, ///Enable line AA rasterization.
	conservativeRaster    = 0x0400_0000_0000_0000, ///Enable conservative rasterization.
	none                  = 0x0000_0000_0000_0000, ///No state.
	frontCcw              = 0x0000_0080_0000_0000, ///Front counter-clockwise (default is clockwise).
	blendIndependent      = 0x0000_0004_0000_0000, ///Enable blend independent.
	blendAlphaToCoverage  = 0x0000_0008_0000_0000, ///Enable alpha to coverage.
/**
* Default state is write to RGB, alpha, and depth with depth test less enabled, with clockwise
* culling and MSAA (when writing into MSAA frame buffer, otherwise this flag is ignored).
*/
	default_              = writeRgb | writeA | writeZ | depthTestLess | cullCw | msaa,
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
StencilFuncRef_ toStencilFuncRef(uint v){ return (v << shift) & mask; }

///Set stencil rmask value.
alias StencilFuncRmask_ = uint;
enum StencilFuncRmask: StencilFuncRmask_{
	shift  = 8,
	mask   = 0x0000_FF00,
}
StencilFuncRmask_ toStencilFuncRmask(uint v){ return (v << shift) & mask; }

alias Stencil_ = uint;
enum Stencil: Stencil_{
	none     = 0x0000_0000,
	mask     = 0xFFFF_FFFF,
	default_ = 0x0000_0000,
}

alias StencilTest_ = uint;
enum StencilTest: StencilTest_{
	less      = 0x0001_0000, ///Enable stencil test, less.
	lequal    = 0x0002_0000, ///Enable stencil test, less or equal.
	equal     = 0x0003_0000, ///Enable stencil test, equal.
	gequal    = 0x0004_0000, ///Enable stencil test, greater or equal.
	greater   = 0x0005_0000, ///Enable stencil test, greater.
	notequal  = 0x0006_0000, ///Enable stencil test, not equal.
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
	incrsat  = 0x0040_0000, ///Increment and clamp.
	decr     = 0x0050_0000, ///Decrement and wrap.
	decrsat  = 0x0060_0000, ///Decrement and clamp.
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
	incrsat  = 0x0400_0000, ///Increment and clamp.
	decr     = 0x0500_0000, ///Decrement and wrap.
	decrsat  = 0x0600_0000, ///Decrement and clamp.
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
	incrsat  = 0x4000_0000, ///Increment and clamp.
	decr     = 0x5000_0000, ///Decrement and wrap.
	decrsat  = 0x6000_0000, ///Decrement and clamp.
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
	discardColor_0    = 0x0008, ///Discard frame buffer attachment 0.
	discardColour_0   = discardColor_0,
	discardColor_1    = 0x0010, ///Discard frame buffer attachment 1.
	discardColour_1   = discardColor_1,
	discardColor_2    = 0x0020, ///Discard frame buffer attachment 2.
	discardColour_2   = discardColor_2,
	discardColor_3    = 0x0040, ///Discard frame buffer attachment 3.
	discardColour_3   = discardColor_3,
	discardColor_4    = 0x0080, ///Discard frame buffer attachment 4.
	discardColour_4   = discardColor_4,
	discardColor_5    = 0x0100, ///Discard frame buffer attachment 5.
	discardColour_5   = discardColor_5,
	discardColor_6    = 0x0200, ///Discard frame buffer attachment 6.
	discardColour_6   = discardColor_6,
	discardColor_7    = 0x0400, ///Discard frame buffer attachment 7.
	discardColour_7   = discardColor_7,
	discardDepth      = 0x0800, ///Discard frame buffer depth attachment.
	discardStencil    = 0x1000, ///Discard frame buffer stencil attachment.
	discardColorMask  = 0x07F8,
	discardColourMask = discardColorMask,
	discardMask       = 0x1FF8,
}

/**
* Rendering state discard. When state is preserved in submit, rendering states can be discarded
* on a finer grain.
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
* Enable infinitely fast hardware test. No draw calls will be submitted to driver.
* It's useful when profiling to quickly assess bottleneck between CPU and GPU.
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

alias TextureRtMsaa_ = ulong;
enum TextureRtMsaa: TextureRtMsaa_{
	x2     = 0x0000_0020_0000_0000, ///Render target MSAAx2 mode.
	x4     = 0x0000_0030_0000_0000, ///Render target MSAAx4 mode.
	x8     = 0x0000_0040_0000_0000, ///Render target MSAAx8 mode.
	x16    = 0x0000_0050_0000_0000, ///Render target MSAAx16 mode.
	shift  = 36,
	mask   = 0x0000_0070_0000_0000,
}

alias TextureRt_ = ulong;
enum TextureRt: TextureRt_{
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

alias SamplerMip_ = uint;
enum SamplerMip: SamplerMip_{
	point  = 0x0000_0400, ///Mip sampling mode: Point
	shift  = 10,
	mask   = 0x0000_0400,
}

alias SamplerCompare_ = uint;
enum SamplerCompare: SamplerCompare_{
	less      = 0x0001_0000, ///Compare when sampling depth texture: less.
	lequal    = 0x0002_0000, ///Compare when sampling depth texture: less or equal.
	equal     = 0x0003_0000, ///Compare when sampling depth texture: equal.
	gequal    = 0x0004_0000, ///Compare when sampling depth texture: greater or equal.
	greater   = 0x0005_0000, ///Compare when sampling depth texture: greater.
	notequal  = 0x0006_0000, ///Compare when sampling depth texture: not equal.
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
SamplerBorderColor_ toSamplerBorderColor(uint v){ return (v << shift) & mask; }
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
	point          = minPoint | magPoint | mipPoint,
	uvwMirror      = umirror | vmirror | wmirror,
	uvwClamp       = uclamp | vclamp | wclamp,
	uvwBorder      = uborder | vborder | wborder,
	bitsMask       = umask | vmask | wmask | minMask | magMask | mipMask | compareMask,
}

alias ResetMsaa_ = uint;
enum ResetMsaa: ResetMsaa_{
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
	maxanisotropy          = 0x0000_0100, ///Turn on/off max anisotropy.
	capture                = 0x0000_0200, ///Begin screen capture.
	flushAfterRender       = 0x0000_2000, ///Flush rendering after submitting to GPU.
/**
* This flag specifies where flip occurs. Default behaviour is that flip occurs
* before rendering new frame. This flag only has effect when `BGFX_CONFIG_MULTITHREADED=0`.
*/
	flipAfterRender        = 0x0000_4000,
	srgbBackbuffer         = 0x0000_8000, ///Enable sRGB backbuffer.
	hdr10                  = 0x0001_0000, ///Enable HDR10 rendering.
	hidpi                  = 0x0002_0000, ///Enable HiDPI rendering.
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

alias Caps_ = ulong;
enum Caps: Caps_{
	alphaToCoverage         = 0x0000_0000_0000_0001, ///Alpha to coverage is supported.
	blendIndependent        = 0x0000_0000_0000_0002, ///Blend independent is supported.
	compute                 = 0x0000_0000_0000_0004, ///Compute shaders are supported.
	conservativeRaster      = 0x0000_0000_0000_0008, ///Conservative rasterization is supported.
	drawIndirect            = 0x0000_0000_0000_0010, ///Draw indirect is supported.
	fragmentDepth           = 0x0000_0000_0000_0020, ///Fragment depth is available in fragment shader.
	fragmentOrdering        = 0x0000_0000_0000_0040, ///Fragment ordering is available in fragment shader.
	graphicsDebugger        = 0x0000_0000_0000_0080, ///Graphics debugger is present.
	hdr10                   = 0x0000_0000_0000_0100, ///HDR10 rendering is supported.
	hidpi                   = 0x0000_0000_0000_0200, ///HiDPI rendering is supported.
	imageRw                 = 0x0000_0000_0000_0400, ///Image Read/Write is supported.
	index32                 = 0x0000_0000_0000_0800, ///32-bit indices are supported.
	instancing              = 0x0000_0000_0000_1000, ///Instancing is supported.
	occlusionQuery          = 0x0000_0000_0000_2000, ///Occlusion query is supported.
	rendererMultithreaded   = 0x0000_0000_0000_4000, ///Renderer is on separate thread.
	swapChain               = 0x0000_0000_0000_8000, ///Multiple windows are supported.
	texture_2dArray         = 0x0000_0000_0001_0000, ///2D texture array is supported.
	texture_3d              = 0x0000_0000_0002_0000, ///3D textures are supported.
	textureBlit             = 0x0000_0000_0004_0000, ///Texture blit is supported.
	transparentBackbuffer   = 0x0000_0000_0008_0000, ///Transparent back buffer supported.
	textureCompareReserved  = 0x0000_0000_0010_0000,
	textureCompareLequal    = 0x0000_0000_0020_0000, ///Texture compare less equal mode is supported.
	textureCubeArray        = 0x0000_0000_0040_0000, ///Cubemap texture array is supported.
	textureDirectAccess     = 0x0000_0000_0080_0000, ///CPU direct access to GPU texture memory.
	textureReadBack         = 0x0000_0000_0100_0000, ///Read-back texture is supported.
	vertexAttribHalf        = 0x0000_0000_0200_0000, ///Vertex attribute half-float is supported.
	vertexAttribUint10      = 0x0000_0000_0400_0000, ///Vertex attribute 10_10_10_2 is supported.
	vertexId                = 0x0000_0000_0800_0000, ///Rendering with VertexID only is supported.
	viewportLayerArray      = 0x0000_0000_1000_0000, ///Viewport layer is available in vertex shader.
	drawIndirectCount       = 0x0000_0000_2000_0000, ///Draw indirect with indirect count is supported.
	textureCompareAll       = 0x0000_0000_0030_0000, ///All texture compare modes are supported.
}

alias CapsFormat_ = uint;
enum CapsFormat: CapsFormat_{
	textureNone             = 0x0000_0000, ///Texture format is not supported.
	texture_2d              = 0x0000_0001, ///Texture format is supported.
	texture_2dSrgb          = 0x0000_0002, ///Texture as sRGB format is supported.
	texture_2dEmulated      = 0x0000_0004, ///Texture format is emulated.
	texture_3d              = 0x0000_0008, ///Texture format is supported.
	texture_3dSrgb          = 0x0000_0010, ///Texture as sRGB format is supported.
	texture_3dEmulated      = 0x0000_0020, ///Texture format is emulated.
	textureCube             = 0x0000_0040, ///Texture format is supported.
	textureCubeSrgb         = 0x0000_0080, ///Texture as sRGB format is supported.
	textureCubeEmulated     = 0x0000_0100, ///Texture format is emulated.
	textureVertex           = 0x0000_0200, ///Texture format can be used from vertex shader.
	textureImageRead        = 0x0000_0400, ///Texture format can be used as image and read from.
	textureImageWrite       = 0x0000_0800, ///Texture format can be used as image and written to.
	textureFramebuffer      = 0x0000_1000, ///Texture format can be used as frame buffer.
	textureFramebufferMsaa  = 0x0000_2000, ///Texture format can be used as MSAA frame buffer.
	textureMsaa             = 0x0000_4000, ///Texture can be sampled as MSAA.
	textureMipAutogen       = 0x0000_8000, ///Texture format supports auto-generated mips.
}

alias Resolve_ = ubyte;
enum Resolve: Resolve_{
	none         = 0x00, ///No resolve flags.
	autoGenMips  = 0x01, ///Auto-generate mip maps on resolve.
}

alias PciId_ = ushort;
enum PciId: PciId_{
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
enum Fatal{
	debugCheck,
	invalidShader,
	unableToInitialize,
	unableToInitialise = unableToInitialize,
	unableToCreateTexture,
	deviceLost,
	
	count,
}

///Renderer backend type enum.
enum RendererType{
	noop, ///No rendering.
	agc, ///AGC
	direct3D9, ///Direct3D 9.0
	direct3D11, ///Direct3D 11.0
	direct3D12, ///Direct3D 12.0
	gnm, ///GNM
	metal, ///Metal
	nvn, ///NVN
	openGLES, ///OpenGL ES 2.0+
	openGL, ///OpenGL 2.1+
	vulkan, ///Vulkan
	webGPU, ///WebGPU
	
	count,
}

///Access mode enum.
enum Access{
	read, ///Read.
	write, ///Write.
	readWrite, ///Read and write.
	
	count,
}

///Vertex attribute enum.
enum Attrib{
	position, ///a_position
	normal, ///a_normal
	tangent, ///a_tangent
	bitangent, ///a_bitangent
	color0, ///a_color0
	colour0 = color0,
	color1, ///a_color1
	colour1 = color1,
	color2, ///a_color2
	colour2 = color2,
	color3, ///a_color3
	colour3 = color3,
	indices, ///a_indices
	weight, ///a_weight
	texCoord0, ///a_texcoord0
	texCoord1, ///a_texcoord1
	texCoord2, ///a_texcoord2
	texCoord3, ///a_texcoord3
	texCoord4, ///a_texcoord4
	texCoord5, ///a_texcoord5
	texCoord6, ///a_texcoord6
	texCoord7, ///a_texcoord7
	
	count,
}

///Vertex attribute type enum.
enum AttribType{
	uint8, ///Uint8
	uint10, ///Uint10, availability depends on: `BGFX_CAPS_VERTEX_ATTRIB_UINT10`.
	int16, ///Int16
	half, ///Half, availability depends on: `BGFX_CAPS_VERTEX_ATTRIB_HALF`.
	float_, ///Float
	
	count,
}

/**
* Texture format enum.
* Notation:
*       RGBA16S
*       ^   ^ ^
*       |   | +-- [ ]Unorm
*       |   |     [F]loat
*       |   |     [S]norm
*       |   |     [I]nt
*       |   |     [U]int
*       |   +---- Number of bits per component
*       +-------- Components
* @attention Availability depends on Caps (see: formats).
*/
enum TextureFormat{
	bc1, ///DXT1 R5G6B5A1
	bc2, ///DXT3 R5G6B5A4
	bc3, ///DXT5 R5G6B5A8
	bc4, ///LATC1/ATI1 R8
	bc5, ///LATC2/ATI2 RG8
	bc6h, ///BC6H RGB16F
	bc7, ///BC7 RGB 4-7 bits per color channel, 0-8 bits alpha
	etc1, ///ETC1 RGB8
	etc2, ///ETC2 RGB8
	etc2a, ///ETC2 RGBA8
	etc2a1, ///ETC2 RGB8A1
	ptc12, ///PVRTC1 RGB 2BPP
	ptc14, ///PVRTC1 RGB 4BPP
	ptc12a, ///PVRTC1 RGBA 2BPP
	ptc14a, ///PVRTC1 RGBA 4BPP
	ptc22, ///PVRTC2 RGBA 2BPP
	ptc24, ///PVRTC2 RGBA 4BPP
	atc, ///ATC RGB 4BPP
	atce, ///ATCE RGBA 8 BPP explicit alpha
	atci, ///ATCI RGBA 8 BPP interpolated alpha
	astc4x4, ///ASTC 4x4 8.0 BPP
	astc5x4, ///ASTC 5x4 6.40 BPP
	astc5x5, ///ASTC 5x5 5.12 BPP
	astc6x5, ///ASTC 6x5 4.27 BPP
	astc6x6, ///ASTC 6x6 3.56 BPP
	astc8x5, ///ASTC 8x5 3.20 BPP
	astc8x6, ///ASTC 8x6 2.67 BPP
	astc8x8, ///ASTC 8x8 2.00 BPP
	astc10x5, ///ASTC 10x5 2.56 BPP
	astc10x6, ///ASTC 10x6 2.13 BPP
	astc10x8, ///ASTC 10x8 1.60 BPP
	astc10x10, ///ASTC 10x10 1.28 BPP
	astc12x10, ///ASTC 12x10 1.07 BPP
	astc12x12, ///ASTC 12x12 0.89 BPP
	unknown, ///Compressed formats above.
	r1,
	a8,
	r8,
	r8i,
	r8u,
	r8s,
	r16,
	r16i,
	r16u,
	r16f,
	r16s,
	r32i,
	r32u,
	r32f,
	rg8,
	rg8i,
	rg8u,
	rg8s,
	rg16,
	rg16i,
	rg16u,
	rg16f,
	rg16s,
	rg32i,
	rg32u,
	rg32f,
	rgb8,
	rgb8i,
	rgb8u,
	rgb8s,
	rgb9e5f,
	bgra8,
	rgba8,
	rgba8i,
	rgba8u,
	rgba8s,
	rgba16,
	rgba16i,
	rgba16u,
	rgba16f,
	rgba16s,
	rgba32i,
	rgba32u,
	rgba32f,
	b5g6r5,
	r5g6b5,
	bgra4,
	rgba4,
	bgr5a1,
	rgb5a1,
	rgb10a2,
	rg11b10f,
	unknownDepth, ///Depth formats below.
	d16,
	d24,
	d24s8,
	d32,
	d16f,
	d24f,
	d32f,
	d0s8,
	
	count,
}

///Uniform type enum.
enum UniformType{
	sampler, ///Sampler.
	end, ///Reserved, do not use.
	vec4, ///4 floats vector.
	mat3, ///3x3 matrix.
	mat4, ///4x4 matrix.
	
	count,
}

///Backbuffer ratio enum.
enum BackbufferRatio{
	equal, ///Equal to backbuffer.
	half, ///One half size of backbuffer.
	quarter, ///One quarter size of backbuffer.
	eighth, ///One eighth size of backbuffer.
	sixteenth, ///One sixteenth size of backbuffer.
	double_, ///Double size of backbuffer.
	
	count,
}

///Occlusion query result.
enum OcclusionQueryResult{
	invisible, ///Query failed test.
	visible, ///Query passed test.
	noResult, ///Query result is not available yet.
	
	count,
}

///Primitive topology.
enum Topology{
	triList, ///Triangle list.
	triStrip, ///Triangle strip.
	lineList, ///Line list.
	lineStrip, ///Line strip.
	pointList, ///Point list.
	
	count,
}

///Topology conversion function.
enum TopologyConvert{
	triListFlipWinding, ///Flip winding order of triangle list.
	triStripFlipWinding, ///Flip winding order of triangle strip.
	triListToLineList, ///Convert triangle list to line list.
	triStripToTriList, ///Convert triangle strip to triangle list.
	lineStripToLineList, ///Convert line strip to line list.
	
	count,
}

///Topology sort order.
enum TopologySort{
	directionFrontToBackMin,
	directionFrontToBackAvg,
	directionFrontToBackMax,
	directionBackToFrontMin,
	directionBackToFrontAvg,
	directionBackToFrontMax,
	distanceFrontToBackMin,
	distanceFrontToBackAvg,
	distanceFrontToBackMax,
	distanceBackToFrontMin,
	distanceBackToFrontAvg,
	distanceBackToFrontMax,
	
	count,
}

///View mode sets draw call sort order.
enum ViewMode{
	default_, ///Default sort order.
	sequential, ///Sort in the same order in which submit calls were called.
	depthAscending, ///Sort draw call depth in ascending order.
	depthDescending, ///Sort draw call depth in descending order.
	
	count,
}

///Render frame enum.
enum RenderFrame{
	noContext, ///Renderer context is not created yet.
	render, ///Renderer context is created and rendering.
	timeout, ///Renderer context wait for main thread signal timed out without rendering.
	exiting, ///Renderer context is getting destroyed.
	
	count,
}

///GPU info.
struct GPU{
	ushort vendorId; ///Vendor PCI id. See `BGFX_PCI_ID_*`.
	ushort deviceId; ///Device id.
}

///Renderer runtime limits.
struct Limits{
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
	uint minResourceCbSize; ///Minimum resource command buffer size.
	uint transientVbSize; ///Maximum transient vertex buffer size.
	uint transientIbSize; ///Maximum transient index buffer size.
}

///Renderer capabilities.
struct Caps{
	bgfx_renderer_type_t rendererType; ///Renderer backend type. See: `bgfx::RendererType`

	/**
	* Supported functionality.
	*   @attention See `BGFX_CAPS_*` flags at https://bkaradzic.github.io/bgfx/bgfx.html#available-caps
	*/
	ulong supported;
	ushort vendorId; ///Selected GPU vendor PCI id.
	ushort deviceId; ///Selected GPU device id.
	bool homogeneousDepth; ///True when NDC depth is in [-1, 1] range, otherwise its [0, 1].
	bool originBottomLeft; ///True when NDC origin is at bottom left.
	ubyte numGPUs; ///Number of enumerated GPUs.
	bgfx_caps_gpu_t[4] gpu; ///Enumerated GPUs.
	bgfx_caps_limits_t limits; ///Renderer runtime limits.

	/**
	* Supported texture format capabilities flags:
	*   - `BGFX_CAPS_FORMAT_TEXTURE_NONE` - Texture format is not supported.
	*   - `BGFX_CAPS_FORMAT_TEXTURE_2D` - Texture format is supported.
	*   - `BGFX_CAPS_FORMAT_TEXTURE_2D_SRGB` - Texture as sRGB format is supported.
	*   - `BGFX_CAPS_FORMAT_TEXTURE_2D_EMULATED` - Texture format is emulated.
	*   - `BGFX_CAPS_FORMAT_TEXTURE_3D` - Texture format is supported.
	*   - `BGFX_CAPS_FORMAT_TEXTURE_3D_SRGB` - Texture as sRGB format is supported.
	*   - `BGFX_CAPS_FORMAT_TEXTURE_3D_EMULATED` - Texture format is emulated.
	*   - `BGFX_CAPS_FORMAT_TEXTURE_CUBE` - Texture format is supported.
	*   - `BGFX_CAPS_FORMAT_TEXTURE_CUBE_SRGB` - Texture as sRGB format is supported.
	*   - `BGFX_CAPS_FORMAT_TEXTURE_CUBE_EMULATED` - Texture format is emulated.
	*   - `BGFX_CAPS_FORMAT_TEXTURE_VERTEX` - Texture format can be used from vertex shader.
	*   - `BGFX_CAPS_FORMAT_TEXTURE_IMAGE_READ` - Texture format can be used as image
	*     and read from.
	*   - `BGFX_CAPS_FORMAT_TEXTURE_IMAGE_WRITE` - Texture format can be used as image
	*     and written to.
	*   - `BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER` - Texture format can be used as frame
	*     buffer.
	*   - `BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA` - Texture format can be used as MSAA
	*     frame buffer.
	*   - `BGFX_CAPS_FORMAT_TEXTURE_MSAA` - Texture can be sampled as MSAA.
	*   - `BGFX_CAPS_FORMAT_TEXTURE_MIP_AUTOGEN` - Texture format supports auto-generated
	*     mips.
	*/
	ushort[TextureFormat.count] formats;
}

///Internal data.
struct InternalData{
	const(bgfx_caps_t)* caps; ///Renderer capabilities.
	void* context; ///GL context, or D3D device.
}

///Platform data.
struct PlatformData{
	void* ndt; ///Native display type (*nix specific).

	/**
	* Native window handle. If `NULL`, bgfx will create a headless
	* context/device, provided the rendering API supports it.
	*/
	void* nwh;

	/**
	* GL context, D3D device, or Vulkan device. If `NULL`, bgfx
	* will create context/device.
	*/
	void* context;

	/**
	* GL back-buffer, or D3D render target view. If `NULL` bgfx will
	* create back-buffer color surface.
	*/
	void* backBuffer;

	/**
	* Backbuffer depth/stencil. If `NULL`, bgfx will create a back-buffer
	* depth/stencil surface.
	*/
	void* backBufferDS;
}

///Backbuffer resolution and reset parameters.
struct Resolution{
	bgfx_texture_format_t format; ///Backbuffer format.
	uint width; ///Backbuffer width.
	uint height; ///Backbuffer height.
	uint reset; ///Reset parameters.
	ubyte numBackBuffers; ///Number of back buffers.
	ubyte maxFrameLatency; ///Maximum frame latency.
}

///Configurable runtime limits parameters.
struct Limits{
	ushort maxEncoders; ///Maximum number of encoder threads.
	uint minResourceCbSize; ///Minimum resource command buffer size.
	uint transientVbSize; ///Maximum transient vertex buffer size.
	uint transientIbSize; ///Maximum transient index buffer size.
}

///Initialization parameters used by `bgfx::init`.
struct Init{

	/**
	* Select rendering backend. When set to RendererType::Count
	* a default rendering backend will be selected appropriate to the platform.
	* See: `bgfx::RendererType`
	*/
	bgfx_renderer_type_t type;

	/**
	* Vendor PCI ID. If set to `BGFX_PCI_ID_NONE`, discrete and integrated
	* GPUs will be prioritised.
	*   - `BGFX_PCI_ID_NONE` - Autoselect adapter.
	*   - `BGFX_PCI_ID_SOFTWARE_RASTERIZER` - Software rasterizer.
	*   - `BGFX_PCI_ID_AMD` - AMD adapter.
	*   - `BGFX_PCI_ID_APPLE` - Apple adapter.
	*   - `BGFX_PCI_ID_INTEL` - Intel adapter.
	*   - `BGFX_PCI_ID_NVIDIA` - NVIDIA adapter.
	*   - `BGFX_PCI_ID_MICROSOFT` - Microsoft adapter.
	*/
	ushort vendorId;

	/**
	* Device ID. If set to 0 it will select first device, or device with
	* matching ID.
	*/
	ushort deviceId;
	ulong capabilities; ///Capabilities initialization mask (default: UINT64_MAX).
	bool debug_; ///Enable device for debugging.
	bool profile; ///Enable device for profiling.
	bgfx_platform_data_t platformData; ///Platform data.
	bgfx_resolution_t resolution; ///Backbuffer resolution and reset parameters. See: `bgfx::Resolution`.
	bgfx_init_limits_t limits; ///Configurable runtime limits parameters.

	/**
	* Provide application specific callback interface.
	* See: `bgfx::CallbackI`
	*/
	void* callback;

	/**
	* Custom allocator. When a custom allocator is not
	* specified, bgfx uses the CRT allocator. Bgfx assumes
	* custom allocator is thread safe.
	*/
	void* allocator;
}

/**
* Memory must be obtained by calling `bgfx::alloc`, `bgfx::copy`, or `bgfx::makeRef`.
* @attention It is illegal to create this structure on stack and pass it to any bgfx API.
*/
struct Memory{
	ubyte* data; ///Pointer to data.
	uint size; ///Data size.
}

///Transient index buffer.
struct TransientIndexBuffer{
	ubyte* data; ///Pointer to data.
	uint size; ///Data size.
	uint startIndex; ///First index.
	bgfx_index_buffer_handle_t handle; ///Index buffer handle.
	bool isIndex16; ///Index buffer format is 16-bits if true, otherwise it is 32-bit.
}

///Transient vertex buffer.
struct TransientVertexBuffer{
	ubyte* data; ///Pointer to data.
	uint size; ///Data size.
	uint startVertex; ///First vertex.
	ushort stride; ///Vertex stride.
	bgfx_vertex_buffer_handle_t handle; ///Vertex buffer handle.
	bgfx_vertex_layout_handle_t layoutHandle; ///Vertex layout handle.
}

///Instance data buffer info.
struct InstanceDataBuffer{
	ubyte* data; ///Pointer to data.
	uint size; ///Data size.
	uint offset; ///Offset in vertex buffer.
	uint num; ///Number of instances.
	ushort stride; ///Vertex buffer stride.
	bgfx_vertex_buffer_handle_t handle; ///Vertex buffer object handle.
}

///Texture info.
struct TextureInfo{
	bgfx_texture_format_t format; ///Texture format.
	uint storageSize; ///Total amount of bytes required to store texture.
	ushort width; ///Texture width.
	ushort height; ///Texture height.
	ushort depth; ///Texture depth.
	ushort numLayers; ///Number of layers in texture array.
	ubyte numMips; ///Number of MIP maps.
	ubyte bitsPerPixel; ///Format bits per pixel.
	bool cubeMap; ///Texture is cubemap.
}

///Uniform info.
struct UniformInfo{
	char[256] name; ///Uniform name.
	bgfx_uniform_type_t type; ///Uniform type.
	ushort num; ///Number of elements in array.
}

///Frame buffer texture attachment info.
struct Attachment{
	bgfx_access_t access; ///Attachment access. See `Access::Enum`.
	bgfx_texture_handle_t handle; ///Render target texture handle.
	ushort mip; ///Mip level.
	ushort layer; ///Cubemap side or depth layer/slice to use.
	ushort numLayers; ///Number of texture layer/slice(s) in array to use.
	ubyte resolve; ///Resolve flags. See: `BGFX_RESOLVE_*`
}

///Transform data.
struct Transform{
	float* data; ///Pointer to first 4x4 matrix.
	ushort num; ///Number of matrices.
}

///View stats.
struct ViewStats{
	char[256] name; ///View name.
	bgfx_view_id_t view; ///View id.
	long cpuTimeBegin; ///CPU (submit) begin time.
	long cpuTimeEnd; ///CPU (submit) end time.
	long gpuTimeBegin; ///GPU begin time.
	long gpuTimeEnd; ///GPU end time.
	uint gpuFrameNum; ///Frame which generated gpuTimeBegin, gpuTimeEnd.
}

///Encoder stats.
struct EncoderStats{
	long cpuTimeBegin; ///Encoder thread CPU submit begin time.
	long cpuTimeEnd; ///Encoder thread CPU submit end time.
}

/**
* Renderer statistics data.
* @remarks All time values are high-resolution timestamps, while
* time frequencies define timestamps-per-second for that hardware.
*/
struct Stats{
	long cpuTimeFrame; ///CPU time between two `bgfx::frame` calls.
	long cpuTimeBegin; ///Render thread CPU submit begin time.
	long cpuTimeEnd; ///Render thread CPU submit end time.
	long cpuTimerFreq; ///CPU timer frequency. Timestamps-per-second
	long gpuTimeBegin; ///GPU frame begin time.
	long gpuTimeEnd; ///GPU frame end time.
	long gpuTimerFreq; ///GPU timer frequency.
	long waitRender; ///Time spent waiting for render backend thread to finish issuing draw commands to underlying graphics API.
	long waitSubmit; ///Time spent waiting for submit thread to advance to next frame.
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
	long textureMemoryUsed; ///Estimate of texture memory used.
	long rtMemoryUsed; ///Estimate of render target memory used.
	int transientVbUsed; ///Amount of transient vertex buffer used.
	int transientIbUsed; ///Amount of transient index buffer used.
	uint[Topology.count] numPrims; ///Number of primitives rendered.
	long gpuMemoryMax; ///Maximum available GPU memory for application.
	long gpuMemoryUsed; ///Amount of GPU memory used by the application.
	ushort width; ///Backbuffer width in pixels.
	ushort height; ///Backbuffer height in pixels.
	ushort textWidth; ///Debug text width in characters.
	ushort textHeight; ///Debug text height in characters.
	ushort numViews; ///Number of view stats.
	bgfx_view_stats_t* viewStats; ///Array of View stats.
	ubyte numEncoders; ///Number of encoders used during frame.
	bgfx_encoder_stats_t* encoderStats; ///Array of encoder stats.
}

///Vertex layout.
struct VertexLayout{
	uint hash; ///Hash.
	ushort stride; ///Stride.
	ushort[Attrib.count] offset; ///Attribute offsets.
	ushort[Attrib.count] attributes; ///Used attributes.
}

/**
* Encoders are used for submitting draw calls from multiple threads. Only one encoder
* per thread should be used. Use `bgfx::begin()` to obtain an encoder for a thread.
*/
struct Encoder{
}

struct DynamicIndexBufferHandle{
	ushort idx;
}

struct DynamicVertexBufferHandle{
	ushort idx;
}

struct FrameBufferHandle{
	ushort idx;
}

struct IndexBufferHandle{
	ushort idx;
}

struct IndirectBufferHandle{
	ushort idx;
}

struct OcclusionQueryHandle{
	ushort idx;
}

struct ProgramHandle{
	ushort idx;
}

struct ShaderHandle{
	ushort idx;
}

struct TextureHandle{
	ushort idx;
}

struct UniformHandle{
	ushort idx;
}

struct VertexBufferHandle{
	ushort idx;
}

struct VertexLayoutHandle{
	ushort idx;
}

mixin(joinFnBinds((){
	string[][] ret;
	ret ~= makeFnBinds([
		/**
		* Init attachment.
		* Params:
		* _handle = Render target texture handle.
		* _access = Access. See `Access::Enum`.
		* _layer = Cubemap side or depth layer/slice to use.
		* _numLayers = Number of texture layer/slice(s) in array to use.
		* _mip = Mip level.
		* _resolve = Resolve flags. See: `BGFX_RESOLVE_*`
		*/
		[q{void}, q{init}, q{bgfx_texture_handle_t _handle, bgfx_access_t _access, ushort _layer, ushort _numLayers, ushort _mip, ubyte _resolve}, `C++`],
		
		/**
		* Start VertexLayout.
		* Params:
		* _rendererType = Renderer backend type. See: `bgfx::RendererType`
		*/
		[q{bgfx_vertex_layout_t*}, q{begin}, q{bgfx_renderer_type_t _rendererType}, `C++`],
		
		/**
		* Add attribute to VertexLayout.
		* Remarks: Must be called between begin/end.
		* Params:
		* _attrib = Attribute semantics. See: `bgfx::Attrib`
		* _num = Number of elements 1, 2, 3 or 4.
		* _type = Element type.
		* _normalized = When using fixed point AttribType (f.e. Uint8)
		* value will be normalized for vertex shader usage. When normalized
		* is set to true, AttribType::Uint8 value in range 0-255 will be
		* in range 0.0-1.0 in vertex shader.
		* _asInt = Packaging rule for vertexPack, vertexUnpack, and
		* vertexConvert for AttribType::Uint8 and AttribType::Int16.
		* Unpacking code must be implemented inside vertex shader.
		*/
		[q{bgfx_vertex_layout_t*}, q{add}, q{bgfx_attrib_t _attrib, ubyte _num, bgfx_attrib_type_t _type, bool _normalized, bool _asInt}, `C++`],
		
		/**
		* Decode attribute.
		* Params:
		* _attrib = Attribute semantics. See: `bgfx::Attrib`
		* _num = Number of elements.
		* _type = Element type.
		* _normalized = Attribute is normalized.
		* _asInt = Attribute is packed as int.
		*/
		[q{void}, q{decode}, q{bgfx_attrib_t _attrib, ubyte* _num, bgfx_attrib_type_t* _type, bool* _normalized, bool* _asInt}, `C++`],
		
		/**
		* Returns `true` if VertexLayout contains attribute.
		* Params:
		* _attrib = Attribute semantics. See: `bgfx::Attrib`
		*/
		[q{bool}, q{has}, q{bgfx_attrib_t _attrib}, `C++`],
		
		/**
		* Skip `_num` bytes in vertex stream.
		* Params:
		* _num = Number of bytes to skip.
		*/
		[q{bgfx_vertex_layout_t*}, q{skip}, q{ubyte _num}, `C++`],
		
		/**
		* End VertexLayout.
		*/
		[q{void}, q{end}, q{}, `C++`],
		
		/**
		* Returns relative attribute offset from the vertex.
		* Params:
		* _attrib = Attribute semantics. See: `bgfx::Attrib`
		*/
		[q{ushort}, q{getOffset}, q{bgfx_attrib_t _attrib}, `C++`],
		
		/**
		* Returns vertex stride.
		*/
		[q{ushort}, q{getStride}, q{}, `C++`],
		
		/**
		* Returns size of vertex buffer for number of vertices.
		* Params:
		* _num = Number of vertices.
		*/
		[q{uint}, q{getSize}, q{uint _num}, `C++`],
		
		/**
		* Pack vertex attribute into vertex stream format.
		* Params:
		* _input = Value to be packed into vertex stream.
		* _inputNormalized = `true` if input value is already normalized.
		* _attr = Attribute to pack.
		* _layout = Vertex stream layout.
		* _data = Destination vertex stream where data will be packed.
		* _index = Vertex index that will be modified.
		*/
		[q{void}, q{vertexPack}, q{const float[4] _input, bool _inputNormalized, bgfx_attrib_t _attr, const(bgfx_vertex_layout_t)* _layout, void* _data, uint _index}, `C++`],
		
		/**
		* Unpack vertex attribute from vertex stream format.
		* Params:
		* _output = Result of unpacking.
		* _attr = Attribute to unpack.
		* _layout = Vertex stream layout.
		* _data = Source vertex stream from where data will be unpacked.
		* _index = Vertex index that will be unpacked.
		*/
		[q{void}, q{vertexUnpack}, q{float[4] _output, bgfx_attrib_t _attr, const(bgfx_vertex_layout_t)* _layout, const(void)* _data, uint _index}, `C++`],
		
		/**
		* Converts vertex stream data from one vertex stream format to another.
		* Params:
		* _dstLayout = Destination vertex stream layout.
		* _dstData = Destination vertex stream.
		* _srcLayout = Source vertex stream layout.
		* _srcData = Source vertex stream data.
		* _num = Number of vertices to convert from source to destination.
		*/
		[q{void}, q{vertexConvert}, q{const(bgfx_vertex_layout_t)* _dstLayout, void* _dstData, const(bgfx_vertex_layout_t)* _srcLayout, const(void)* _srcData, uint _num}, `C++`],
		
		/**
		* Weld vertices.
		* Params:
		* _output = Welded vertices remapping table. The size of buffer
		* must be the same as number of vertices.
		* _layout = Vertex stream layout.
		* _data = Vertex stream.
		* _num = Number of vertices in vertex stream.
		* _index32 = Set to `true` if input indices are 32-bit.
		* _epsilon = Error tolerance for vertex position comparison.
		*/
		[q{uint}, q{weldVertices}, q{void* _output, const(bgfx_vertex_layout_t)* _layout, const(void)* _data, uint _num, bool _index32, float _epsilon}, `C++`],
		
		/**
		* Convert index buffer for use with different primitive topologies.
		* Params:
		* _conversion = Conversion type, see `TopologyConvert::Enum`.
		* _dst = Destination index buffer. If this argument is NULL
		* function will return number of indices after conversion.
		* _dstSize = Destination index buffer in bytes. It must be
		* large enough to contain output indices. If destination size is
		* insufficient index buffer will be truncated.
		* _indices = Source indices.
		* _numIndices = Number of input indices.
		* _index32 = Set to `true` if input indices are 32-bit.
		*/
		[q{uint}, q{topologyConvert}, q{bgfx_topology_convert_t _conversion, void* _dst, uint _dstSize, const(void)* _indices, uint _numIndices, bool _index32}, `C++`],
		
		/**
		* Sort indices.
		* Params:
		* _sort = Sort order, see `TopologySort::Enum`.
		* _dst = Destination index buffer.
		* _dstSize = Destination index buffer in bytes. It must be
		* large enough to contain output indices. If destination size is
		* insufficient index buffer will be truncated.
		* _dir = Direction (vector must be normalized).
		* _pos = Position.
		* _vertices = Pointer to first vertex represented as
		* float x, y, z. Must contain at least number of vertices
		* referencende by index buffer.
		* _stride = Vertex stride.
		* _indices = Source indices.
		* _numIndices = Number of input indices.
		* _index32 = Set to `true` if input indices are 32-bit.
		*/
		[q{void}, q{topologySortTriList}, q{bgfx_topology_sort_t _sort, void* _dst, uint _dstSize, const float[3] _dir, const float[3] _pos, const(void)* _vertices, uint _stride, const(void)* _indices, uint _numIndices, bool _index32}, `C++`],
		
		/**
		* Returns supported backend API renderers.
		* Params:
		* _max = Maximum number of elements in _enum array.
		* _enum = Array where supported renderers will be written.
		*/
		[q{ubyte}, q{getSupportedRenderers}, q{ubyte _max, bgfx_renderer_type_t* _enum}, `C++`],
		
		/**
		* Returns name of renderer.
		* Params:
		* _type = Renderer backend type. See: `bgfx::RendererType`
		*/
		[q{const(char)*}, q{getRendererName}, q{bgfx_renderer_type_t _type}, `C++`],
		
		[q{void}, q{initCtor}, q{bgfx_init_t* _init}, `C++`],
		
		/**
		* Initialize the bgfx library.
		* Params:
		* _init = Initialization parameters. See: `bgfx::Init` for more info.
		*/
		[q{bool}, q{init}, q{const(bgfx_init_t)* _init}, `C++`],
		
		/**
		* Shutdown bgfx library.
		*/
		[q{void}, q{shutdown}, q{}, `C++`],
		
		/**
		* Reset graphic settings and back-buffer size.
		* Attention: This call doesn’t change the window size, it just resizes
		*   the back-buffer. Your windowing code controls the window size.
		* Params:
		* _width = Back-buffer width.
		* _height = Back-buffer height.
		* _flags = See: `BGFX_RESET_*` for more info.
		*   - `BGFX_RESET_NONE` - No reset flags.
		*   - `BGFX_RESET_FULLSCREEN` - Not supported yet.
		*   - `BGFX_RESET_MSAA_X[2/4/8/16]` - Enable 2, 4, 8 or 16 x MSAA.
		*   - `BGFX_RESET_VSYNC` - Enable V-Sync.
		*   - `BGFX_RESET_MAXANISOTROPY` - Turn on/off max anisotropy.
		*   - `BGFX_RESET_CAPTURE` - Begin screen capture.
		*   - `BGFX_RESET_FLUSH_AFTER_RENDER` - Flush rendering after submitting to GPU.
		*   - `BGFX_RESET_FLIP_AFTER_RENDER` - This flag  specifies where flip
		*     occurs. Default behaviour is that flip occurs before rendering new
		*     frame. This flag only has effect when `BGFX_CONFIG_MULTITHREADED=0`.
		*   - `BGFX_RESET_SRGB_BACKBUFFER` - Enable sRGB back-buffer.
		* _format = Texture format. See: `TextureFormat::Enum`.
		*/
		[q{void}, q{reset}, q{uint _width, uint _height, uint _flags, bgfx_texture_format_t _format}, `C++`],
		
		/**
		* Advance to next frame. When using multithreaded renderer, this call
		* just swaps internal buffers, kicks render thread, and returns. In
		* singlethreaded renderer this call does frame rendering.
		* Params:
		* _capture = Capture frame with graphics debugger.
		*/
		[q{uint}, q{frame}, q{bool _capture}, `C++`],
		
		/**
		* Returns current renderer backend API type.
		* Remarks:
		*   Library must be initialized.
		*/
		[q{bgfx_renderer_type_t}, q{getRendererType}, q{}, `C++`],
		
		/**
		* Returns renderer capabilities.
		* Remarks:
		*   Library must be initialized.
		*/
		[q{const(bgfx_caps_t)*}, q{getCaps}, q{}, `C++`],
		
		/**
		* Returns performance counters.
		* Attention: Pointer returned is valid until `bgfx::frame` is called.
		*/
		[q{const(bgfx_stats_t)*}, q{getStats}, q{}, `C++`],
		
		/**
		* Allocate buffer to pass to bgfx calls. Data will be freed inside bgfx.
		* Params:
		* _size = Size to allocate.
		*/
		[q{const(bgfx_memory_t)*}, q{alloc}, q{uint _size}, `C++`],
		
		/**
		* Allocate buffer and copy data into it. Data will be freed inside bgfx.
		* Params:
		* _data = Pointer to data to be copied.
		* _size = Size of data to be copied.
		*/
		[q{const(bgfx_memory_t)*}, q{copy}, q{const(void)* _data, uint _size}, `C++`],
		
		/**
		* Make reference to data to pass to bgfx. Unlike `bgfx::alloc`, this call
		* doesn't allocate memory for data. It just copies the _data pointer. You
		* can pass `ReleaseFn` function pointer to release this memory after it's
		* consumed, otherwise you must make sure _data is available for at least 2
		* `bgfx::frame` calls. `ReleaseFn` function must be able to be called
		* from any thread.
		* Attention: Data passed must be available for at least 2 `bgfx::frame` calls.
		* Params:
		* _data = Pointer to data.
		* _size = Size of data.
		*/
		[q{const(bgfx_memory_t)*}, q{makeRef}, q{const(void)* _data, uint _size}, `C++`],
		
		/**
		* Make reference to data to pass to bgfx. Unlike `bgfx::alloc`, this call
		* doesn't allocate memory for data. It just copies the _data pointer. You
		* can pass `ReleaseFn` function pointer to release this memory after it's
		* consumed, otherwise you must make sure _data is available for at least 2
		* `bgfx::frame` calls. `ReleaseFn` function must be able to be called
		* from any thread.
		* Attention: Data passed must be available for at least 2 `bgfx::frame` calls.
		* Params:
		* _data = Pointer to data.
		* _size = Size of data.
		* _releaseFn = Callback function to release memory after use.
		* _userData = User data to be passed to callback function.
		*/
		[q{const(bgfx_memory_t)*}, q{makeRef}, q{const(void)* _data, uint _size, bgfx_release_fn_t _releaseFn, void* _userData}, `C++`],
		
		/**
		* Set debug flags.
		* Params:
		* _debug = Available flags:
		*   - `BGFX_DEBUG_IFH` - Infinitely fast hardware. When this flag is set
		*     all rendering calls will be skipped. This is useful when profiling
		*     to quickly assess potential bottlenecks between CPU and GPU.
		*   - `BGFX_DEBUG_PROFILER` - Enable profiler.
		*   - `BGFX_DEBUG_STATS` - Display internal statistics.
		*   - `BGFX_DEBUG_TEXT` - Display debug text.
		*   - `BGFX_DEBUG_WIREFRAME` - Wireframe rendering. All rendering
		*     primitives will be rendered as lines.
		*/
		[q{void}, q{setDebug}, q{uint _debug}, `C++`],
		
		/**
		* Clear internal debug text buffer.
		* Params:
		* _attr = Background color.
		* _small = Default 8x16 or 8x8 font.
		*/
		[q{void}, q{dbgTextClear}, q{ubyte _attr, bool _small}, `C++`],
		
		/**
		* Print formatted data to internal debug text character-buffer (VGA-compatible text mode).
		* Params:
		* _x = Position x from the left corner of the window.
		* _y = Position y from the top corner of the window.
		* _attr = Color palette. Where top 4-bits represent index of background, and bottom
		* 4-bits represent foreground color from standard VGA text palette (ANSI escape codes).
		* _format = `printf` style format.
		*/
		[q{void}, q{dbgTextPrintf}, q{ushort _x, ushort _y, ubyte _attr, const(char)* _format, ... }, `C++`],
		
		/**
		* Print formatted data from variable argument list to internal debug text character-buffer (VGA-compatible text mode).
		* Params:
		* _x = Position x from the left corner of the window.
		* _y = Position y from the top corner of the window.
		* _attr = Color palette. Where top 4-bits represent index of background, and bottom
		* 4-bits represent foreground color from standard VGA text palette (ANSI escape codes).
		* _format = `printf` style format.
		* _argList = Variable arguments list for format string.
		*/
		[q{void}, q{dbgTextPrintfVargs}, q{ushort _x, ushort _y, ubyte _attr, const(char)* _format, va_list _argList}, `C++`],
		
		/**
		* Draw image into internal debug text buffer.
		* Params:
		* _x = Position x from the left corner of the window.
		* _y = Position y from the top corner of the window.
		* _width = Image width.
		* _height = Image height.
		* _data = Raw image data (character/attribute raw encoding).
		* _pitch = Image pitch in bytes.
		*/
		[q{void}, q{dbgTextImage}, q{ushort _x, ushort _y, ushort _width, ushort _height, const(void)* _data, ushort _pitch}, `C++`],
		
		/**
		* Create static index buffer.
		* Params:
		* _mem = Index buffer data.
		* _flags = Buffer creation flags.
		*   - `BGFX_BUFFER_NONE` - No flags.
		*   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
		*   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
		*       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
		*   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
		*   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of
		*       data is passed. If this flag is not specified, and more data is passed on update, the buffer
		*       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic
		*       buffers.
		*   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on
		*       index buffers.
		*/
		[q{bgfx_index_buffer_handle_t}, q{createIndexBuffer}, q{const(bgfx_memory_t)* _mem, ushort _flags}, `C++`],
		
		/**
		* Set static index buffer debug name.
		* Params:
		* _handle = Static index buffer handle.
		* _name = Static index buffer name.
		* _len = Static index buffer name length (if length is INT32_MAX, it's expected
		* that _name is zero terminated string.
		*/
		[q{void}, q{setName}, q{bgfx_index_buffer_handle_t _handle, const(char)* _name, int _len}, `C++`],
		
		/**
		* Destroy static index buffer.
		* Params:
		* _handle = Static index buffer handle.
		*/
		[q{void}, q{destroy}, q{bgfx_index_buffer_handle_t _handle}, `C++`],
		
		/**
		* Create vertex layout.
		* Params:
		* _layout = Vertex layout.
		*/
		[q{bgfx_vertex_layout_handle_t}, q{createVertexLayout}, q{const(bgfx_vertex_layout_t)* _layout}, `C++`],
		
		/**
		* Destroy vertex layout.
		* Params:
		* _layoutHandle = Vertex layout handle.
		*/
		[q{void}, q{destroy}, q{bgfx_vertex_layout_handle_t _layoutHandle}, `C++`],
		
		/**
		* Create static vertex buffer.
		* Params:
		* _mem = Vertex buffer data.
		* _layout = Vertex layout.
		* _flags = Buffer creation flags.
		*  - `BGFX_BUFFER_NONE` - No flags.
		*  - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
		*  - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
		*      is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
		*  - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
		*  - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of
		*      data is passed. If this flag is not specified, and more data is passed on update, the buffer
		*      will be trimmed to fit the existing buffer size. This flag has effect only on dynamic buffers.
		*  - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on index buffers.
		*/
		[q{bgfx_vertex_buffer_handle_t}, q{createVertexBuffer}, q{const(bgfx_memory_t)* _mem, const(bgfx_vertex_layout_t)* _layout, ushort _flags}, `C++`],
		
		/**
		* Set static vertex buffer debug name.
		* Params:
		* _handle = Static vertex buffer handle.
		* _name = Static vertex buffer name.
		* _len = Static vertex buffer name length (if length is INT32_MAX, it's expected
		* that _name is zero terminated string.
		*/
		[q{void}, q{setName}, q{bgfx_vertex_buffer_handle_t _handle, const(char)* _name, int _len}, `C++`],
		
		/**
		* Destroy static vertex buffer.
		* Params:
		* _handle = Static vertex buffer handle.
		*/
		[q{void}, q{destroy}, q{bgfx_vertex_buffer_handle_t _handle}, `C++`],
		
		/**
		* Create empty dynamic index buffer.
		* Params:
		* _num = Number of indices.
		* _flags = Buffer creation flags.
		*   - `BGFX_BUFFER_NONE` - No flags.
		*   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
		*   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
		*       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
		*   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
		*   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of
		*       data is passed. If this flag is not specified, and more data is passed on update, the buffer
		*       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic
		*       buffers.
		*   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on
		*       index buffers.
		*/
		[q{bgfx_dynamic_index_buffer_handle_t}, q{createDynamicIndexBuffer}, q{uint _num, ushort _flags}, `C++`],
		
		/**
		* Create a dynamic index buffer and initialize it.
		* Params:
		* _mem = Index buffer data.
		* _flags = Buffer creation flags.
		*   - `BGFX_BUFFER_NONE` - No flags.
		*   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
		*   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
		*       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
		*   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
		*   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of
		*       data is passed. If this flag is not specified, and more data is passed on update, the buffer
		*       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic
		*       buffers.
		*   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on
		*       index buffers.
		*/
		[q{bgfx_dynamic_index_buffer_handle_t}, q{createDynamicIndexBuffer}, q{const(bgfx_memory_t)* _mem, ushort _flags}, `C++`],
		
		/**
		* Update dynamic index buffer.
		* Params:
		* _handle = Dynamic index buffer handle.
		* _startIndex = Start index.
		* _mem = Index buffer data.
		*/
		[q{void}, q{update}, q{bgfx_dynamic_index_buffer_handle_t _handle, uint _startIndex, const(bgfx_memory_t)* _mem}, `C++`],
		
		/**
		* Destroy dynamic index buffer.
		* Params:
		* _handle = Dynamic index buffer handle.
		*/
		[q{void}, q{destroy}, q{bgfx_dynamic_index_buffer_handle_t _handle}, `C++`],
		
		/**
		* Create empty dynamic vertex buffer.
		* Params:
		* _num = Number of vertices.
		* _layout = Vertex layout.
		* _flags = Buffer creation flags.
		*   - `BGFX_BUFFER_NONE` - No flags.
		*   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
		*   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
		*       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
		*   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
		*   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of
		*       data is passed. If this flag is not specified, and more data is passed on update, the buffer
		*       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic
		*       buffers.
		*   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on
		*       index buffers.
		*/
		[q{bgfx_dynamic_vertex_buffer_handle_t}, q{createDynamicVertexBuffer}, q{uint _num, const(bgfx_vertex_layout_t)* _layout, ushort _flags}, `C++`],
		
		/**
		* Create dynamic vertex buffer and initialize it.
		* Params:
		* _mem = Vertex buffer data.
		* _layout = Vertex layout.
		* _flags = Buffer creation flags.
		*   - `BGFX_BUFFER_NONE` - No flags.
		*   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
		*   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
		*       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
		*   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
		*   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of
		*       data is passed. If this flag is not specified, and more data is passed on update, the buffer
		*       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic
		*       buffers.
		*   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on
		*       index buffers.
		*/
		[q{bgfx_dynamic_vertex_buffer_handle_t}, q{createDynamicVertexBuffer}, q{const(bgfx_memory_t)* _mem, const(bgfx_vertex_layout_t)* _layout, ushort _flags}, `C++`],
		
		/**
		* Update dynamic vertex buffer.
		* Params:
		* _handle = Dynamic vertex buffer handle.
		* _startVertex = Start vertex.
		* _mem = Vertex buffer data.
		*/
		[q{void}, q{update}, q{bgfx_dynamic_vertex_buffer_handle_t _handle, uint _startVertex, const(bgfx_memory_t)* _mem}, `C++`],
		
		/**
		* Destroy dynamic vertex buffer.
		* Params:
		* _handle = Dynamic vertex buffer handle.
		*/
		[q{void}, q{destroy}, q{bgfx_dynamic_vertex_buffer_handle_t _handle}, `C++`],
		
		/**
		* Returns number of requested or maximum available indices.
		* Params:
		* _num = Number of required indices.
		* _index32 = Set to `true` if input indices will be 32-bit.
		*/
		[q{uint}, q{getAvailTransientIndexBuffer}, q{uint _num, bool _index32}, `C++`],
		
		/**
		* Returns number of requested or maximum available vertices.
		* Params:
		* _num = Number of required vertices.
		* _layout = Vertex layout.
		*/
		[q{uint}, q{getAvailTransientVertexBuffer}, q{uint _num, const(bgfx_vertex_layout_t)* _layout}, `C++`],
		
		/**
		* Returns number of requested or maximum available instance buffer slots.
		* Params:
		* _num = Number of required instances.
		* _stride = Stride per instance.
		*/
		[q{uint}, q{getAvailInstanceDataBuffer}, q{uint _num, ushort _stride}, `C++`],
		
		/**
		* Allocate transient index buffer.
		* Params:
		* _tib = TransientIndexBuffer structure will be filled, and will be valid
		* for the duration of frame, and can be reused for multiple draw
		* calls.
		* _num = Number of indices to allocate.
		* _index32 = Set to `true` if input indices will be 32-bit.
		*/
		[q{void}, q{allocTransientIndexBuffer}, q{bgfx_transient_index_buffer_t* _tib, uint _num, bool _index32}, `C++`],
		
		/**
		* Allocate transient vertex buffer.
		* Params:
		* _tvb = TransientVertexBuffer structure will be filled, and will be valid
		* for the duration of frame, and can be reused for multiple draw
		* calls.
		* _num = Number of vertices to allocate.
		* _layout = Vertex layout.
		*/
		[q{void}, q{allocTransientVertexBuffer}, q{bgfx_transient_vertex_buffer_t* _tvb, uint _num, const(bgfx_vertex_layout_t)* _layout}, `C++`],
		
		/**
		* Check for required space and allocate transient vertex and index
		* buffers. If both space requirements are satisfied function returns
		* true.
		* Params:
		* _tvb = TransientVertexBuffer structure will be filled, and will be valid
		* for the duration of frame, and can be reused for multiple draw
		* calls.
		* _layout = Vertex layout.
		* _numVertices = Number of vertices to allocate.
		* _tib = TransientIndexBuffer structure will be filled, and will be valid
		* for the duration of frame, and can be reused for multiple draw
		* calls.
		* _numIndices = Number of indices to allocate.
		* _index32 = Set to `true` if input indices will be 32-bit.
		*/
		[q{bool}, q{allocTransientBuffers}, q{bgfx_transient_vertex_buffer_t* _tvb, const(bgfx_vertex_layout_t)* _layout, uint _numVertices, bgfx_transient_index_buffer_t* _tib, uint _numIndices, bool _index32}, `C++`],
		
		/**
		* Allocate instance data buffer.
		* Params:
		* _idb = InstanceDataBuffer structure will be filled, and will be valid
		* for duration of frame, and can be reused for multiple draw
		* calls.
		* _num = Number of instances.
		* _stride = Instance stride. Must be multiple of 16.
		*/
		[q{void}, q{allocInstanceDataBuffer}, q{bgfx_instance_data_buffer_t* _idb, uint _num, ushort _stride}, `C++`],
		
		/**
		* Create draw indirect buffer.
		* Params:
		* _num = Number of indirect calls.
		*/
		[q{bgfx_indirect_buffer_handle_t}, q{createIndirectBuffer}, q{uint _num}, `C++`],
		
		/**
		* Destroy draw indirect buffer.
		* Params:
		* _handle = Indirect buffer handle.
		*/
		[q{void}, q{destroy}, q{bgfx_indirect_buffer_handle_t _handle}, `C++`],
		
		/**
		* Create shader from memory buffer.
		* Params:
		* _mem = Shader binary.
		*/
		[q{bgfx_shader_handle_t}, q{createShader}, q{const(bgfx_memory_t)* _mem}, `C++`],
		
		/**
		* Returns the number of uniforms and uniform handles used inside a shader.
		* Remarks:
		*   Only non-predefined uniforms are returned.
		* Params:
		* _handle = Shader handle.
		* _uniforms = UniformHandle array where data will be stored.
		* _max = Maximum capacity of array.
		*/
		[q{ushort}, q{getShaderUniforms}, q{bgfx_shader_handle_t _handle, bgfx_uniform_handle_t* _uniforms, ushort _max}, `C++`],
		
		/**
		* Set shader debug name.
		* Params:
		* _handle = Shader handle.
		* _name = Shader name.
		* _len = Shader name length (if length is INT32_MAX, it's expected
		* that _name is zero terminated string).
		*/
		[q{void}, q{setName}, q{bgfx_shader_handle_t _handle, const(char)* _name, int _len}, `C++`],
		
		/**
		* Destroy shader.
		* Remarks: Once a shader program is created with _handle,
		*   it is safe to destroy that shader.
		* Params:
		* _handle = Shader handle.
		*/
		[q{void}, q{destroy}, q{bgfx_shader_handle_t _handle}, `C++`],
		
		/**
		* Create program with vertex and fragment shaders.
		* Params:
		* _vsh = Vertex shader.
		* _fsh = Fragment shader.
		* _destroyShaders = If true, shaders will be destroyed when program is destroyed.
		*/
		[q{bgfx_program_handle_t}, q{createProgram}, q{bgfx_shader_handle_t _vsh, bgfx_shader_handle_t _fsh, bool _destroyShaders}, `C++`],
		
		/**
		* Create program with compute shader.
		* Params:
		* _csh = Compute shader.
		* _destroyShaders = If true, shaders will be destroyed when program is destroyed.
		*/
		[q{bgfx_program_handle_t}, q{createProgram}, q{bgfx_shader_handle_t _csh, bool _destroyShaders}, `C++`],
		
		/**
		* Destroy program.
		* Params:
		* _handle = Program handle.
		*/
		[q{void}, q{destroy}, q{bgfx_program_handle_t _handle}, `C++`],
		
		/**
		* Validate texture parameters.
		* Params:
		* _depth = Depth dimension of volume texture.
		* _cubeMap = Indicates that texture contains cubemap.
		* _numLayers = Number of layers in texture array.
		* _format = Texture format. See: `TextureFormat::Enum`.
		* _flags = Texture flags. See `BGFX_TEXTURE_*`.
		*/
		[q{bool}, q{isTextureValid}, q{ushort _depth, bool _cubeMap, ushort _numLayers, bgfx_texture_format_t _format, ulong _flags}, `C++`],
		
		/**
		* Validate frame buffer parameters.
		* Params:
		* _num = Number of attachments.
		* _attachment = Attachment texture info. See: `bgfx::Attachment`.
		*/
		[q{bool}, q{isFrameBufferValid}, q{ubyte _num, const(bgfx_attachment_t)* _attachment}, `C++`],
		
		/**
		* Calculate amount of memory required for texture.
		* Params:
		* _info = Resulting texture info structure. See: `TextureInfo`.
		* _width = Width.
		* _height = Height.
		* _depth = Depth dimension of volume texture.
		* _cubeMap = Indicates that texture contains cubemap.
		* _hasMips = Indicates that texture contains full mip-map chain.
		* _numLayers = Number of layers in texture array.
		* _format = Texture format. See: `TextureFormat::Enum`.
		*/
		[q{void}, q{calcTextureSize}, q{bgfx_texture_info_t* _info, ushort _width, ushort _height, ushort _depth, bool _cubeMap, bool _hasMips, ushort _numLayers, bgfx_texture_format_t _format}, `C++`],
		
		/**
		* Create texture from memory buffer.
		* Params:
		* _mem = DDS, KTX or PVR texture binary data.
		* _flags = Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
		* flags. Default texture sampling mode is linear, and wrap mode is repeat.
		* - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
		*   mode.
		* - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
		*   sampling.
		* _skip = Skip top level mips when parsing texture.
		* _info = When non-`NULL` is specified it returns parsed texture information.
		*/
		[q{bgfx_texture_handle_t}, q{createTexture}, q{const(bgfx_memory_t)* _mem, ulong _flags, ubyte _skip, bgfx_texture_info_t* _info}, `C++`],
		
		/**
		* Create 2D texture.
		* Params:
		* _width = Width.
		* _height = Height.
		* _hasMips = Indicates that texture contains full mip-map chain.
		* _numLayers = Number of layers in texture array. Must be 1 if caps
		* `BGFX_CAPS_TEXTURE_2D_ARRAY` flag is not set.
		* _format = Texture format. See: `TextureFormat::Enum`.
		* _flags = Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
		* flags. Default texture sampling mode is linear, and wrap mode is repeat.
		* - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
		*   mode.
		* - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
		*   sampling.
		* _mem = Texture data. If `_mem` is non-NULL, created texture will be immutable. If
		* `_mem` is NULL content of the texture is uninitialized. When `_numLayers` is more than
		* 1, expected memory layout is texture and all mips together for each array element.
		*/
		[q{bgfx_texture_handle_t}, q{createTexture2D}, q{ushort _width, ushort _height, bool _hasMips, ushort _numLayers, bgfx_texture_format_t _format, ulong _flags, const(bgfx_memory_t)* _mem}, `C++`],
		
		/**
		* Create texture with size based on back-buffer ratio. Texture will maintain ratio
		* if back buffer resolution changes.
		* Params:
		* _ratio = Texture size in respect to back-buffer size. See: `BackbufferRatio::Enum`.
		* _hasMips = Indicates that texture contains full mip-map chain.
		* _numLayers = Number of layers in texture array. Must be 1 if caps
		* `BGFX_CAPS_TEXTURE_2D_ARRAY` flag is not set.
		* _format = Texture format. See: `TextureFormat::Enum`.
		* _flags = Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
		* flags. Default texture sampling mode is linear, and wrap mode is repeat.
		* - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
		*   mode.
		* - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
		*   sampling.
		*/
		[q{bgfx_texture_handle_t}, q{createTexture2D}, q{bgfx_backbuffer_ratio_t _ratio, bool _hasMips, ushort _numLayers, bgfx_texture_format_t _format, ulong _flags}, `C++`],
		
		/**
		* Create 3D texture.
		* Params:
		* _width = Width.
		* _height = Height.
		* _depth = Depth.
		* _hasMips = Indicates that texture contains full mip-map chain.
		* _format = Texture format. See: `TextureFormat::Enum`.
		* _flags = Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
		* flags. Default texture sampling mode is linear, and wrap mode is repeat.
		* - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
		*   mode.
		* - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
		*   sampling.
		* _mem = Texture data. If `_mem` is non-NULL, created texture will be immutable. If
		* `_mem` is NULL content of the texture is uninitialized. When `_numLayers` is more than
		* 1, expected memory layout is texture and all mips together for each array element.
		*/
		[q{bgfx_texture_handle_t}, q{createTexture3D}, q{ushort _width, ushort _height, ushort _depth, bool _hasMips, bgfx_texture_format_t _format, ulong _flags, const(bgfx_memory_t)* _mem}, `C++`],
		
		/**
		* Create Cube texture.
		* Params:
		* _size = Cube side size.
		* _hasMips = Indicates that texture contains full mip-map chain.
		* _numLayers = Number of layers in texture array. Must be 1 if caps
		* `BGFX_CAPS_TEXTURE_2D_ARRAY` flag is not set.
		* _format = Texture format. See: `TextureFormat::Enum`.
		* _flags = Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
		* flags. Default texture sampling mode is linear, and wrap mode is repeat.
		* - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
		*   mode.
		* - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
		*   sampling.
		* _mem = Texture data. If `_mem` is non-NULL, created texture will be immutable. If
		* `_mem` is NULL content of the texture is uninitialized. When `_numLayers` is more than
		* 1, expected memory layout is texture and all mips together for each array element.
		*/
		[q{bgfx_texture_handle_t}, q{createTextureCube}, q{ushort _size, bool _hasMips, ushort _numLayers, bgfx_texture_format_t _format, ulong _flags, const(bgfx_memory_t)* _mem}, `C++`],
		
		/**
		* Update 2D texture.
		* Attention: It's valid to update only mutable texture. See `bgfx::createTexture2D` for more info.
		* Params:
		* _handle = Texture handle.
		* _layer = Layer in texture array.
		* _mip = Mip level.
		* _x = X offset in texture.
		* _y = Y offset in texture.
		* _width = Width of texture block.
		* _height = Height of texture block.
		* _mem = Texture update data.
		* _pitch = Pitch of input image (bytes). When _pitch is set to
		* UINT16_MAX, it will be calculated internally based on _width.
		*/
		[q{void}, q{updateTexture2D}, q{bgfx_texture_handle_t _handle, ushort _layer, ubyte _mip, ushort _x, ushort _y, ushort _width, ushort _height, const(bgfx_memory_t)* _mem, ushort _pitch}, `C++`],
		
		/**
		* Update 3D texture.
		* Attention: It's valid to update only mutable texture. See `bgfx::createTexture3D` for more info.
		* Params:
		* _handle = Texture handle.
		* _mip = Mip level.
		* _x = X offset in texture.
		* _y = Y offset in texture.
		* _z = Z offset in texture.
		* _width = Width of texture block.
		* _height = Height of texture block.
		* _depth = Depth of texture block.
		* _mem = Texture update data.
		*/
		[q{void}, q{updateTexture3D}, q{bgfx_texture_handle_t _handle, ubyte _mip, ushort _x, ushort _y, ushort _z, ushort _width, ushort _height, ushort _depth, const(bgfx_memory_t)* _mem}, `C++`],
		
		/**
		* Update Cube texture.
		* Attention: It's valid to update only mutable texture. See `bgfx::createTextureCube` for more info.
		* Params:
		* _handle = Texture handle.
		* _layer = Layer in texture array.
		* _side = Cubemap side `BGFX_CUBE_MAP_<POSITIVE or NEGATIVE>_<X, Y or Z>`,
		*   where 0 is +X, 1 is -X, 2 is +Y, 3 is -Y, 4 is +Z, and 5 is -Z.
		*                  +----------+
		*                  |-z       2|
		*                  | ^  +y    |
		*                  | |        |    Unfolded cube:
		*                  | +---->+x |
		*       +----------+----------+----------+----------+
		*       |+y       1|+y       4|+y       0|+y       5|
		*       | ^  -x    | ^  +z    | ^  +x    | ^  -z    |
		*       | |        | |        | |        | |        |
		*       | +---->+z | +---->+x | +---->-z | +---->-x |
		*       +----------+----------+----------+----------+
		*                  |+z       3|
		*                  | ^  -y    |
		*                  | |        |
		*                  | +---->+x |
		*                  +----------+
		* _mip = Mip level.
		* _x = X offset in texture.
		* _y = Y offset in texture.
		* _width = Width of texture block.
		* _height = Height of texture block.
		* _mem = Texture update data.
		* _pitch = Pitch of input image (bytes). When _pitch is set to
		* UINT16_MAX, it will be calculated internally based on _width.
		*/
		[q{void}, q{updateTextureCube}, q{bgfx_texture_handle_t _handle, ushort _layer, ubyte _side, ubyte _mip, ushort _x, ushort _y, ushort _width, ushort _height, const(bgfx_memory_t)* _mem, ushort _pitch}, `C++`],
		
		/**
		* Read back texture content.
		* Attention: Texture must be created with `BGFX_TEXTURE_READ_BACK` flag.
		* Attention: Availability depends on: `BGFX_CAPS_TEXTURE_READ_BACK`.
		* Params:
		* _handle = Texture handle.
		* _data = Destination buffer.
		* _mip = Mip level.
		*/
		[q{uint}, q{readTexture}, q{bgfx_texture_handle_t _handle, void* _data, ubyte _mip}, `C++`],
		
		/**
		* Set texture debug name.
		* Params:
		* _handle = Texture handle.
		* _name = Texture name.
		* _len = Texture name length (if length is INT32_MAX, it's expected
		* that _name is zero terminated string.
		*/
		[q{void}, q{setName}, q{bgfx_texture_handle_t _handle, const(char)* _name, int _len}, `C++`],
		
		/**
		* Returns texture direct access pointer.
		* Attention: Availability depends on: `BGFX_CAPS_TEXTURE_DIRECT_ACCESS`. This feature
		*   is available on GPUs that have unified memory architecture (UMA) support.
		* Params:
		* _handle = Texture handle.
		*/
		[q{void*}, q{getDirectAccessPtr}, q{bgfx_texture_handle_t _handle}, `C++`],
		
		/**
		* Destroy texture.
		* Params:
		* _handle = Texture handle.
		*/
		[q{void}, q{destroy}, q{bgfx_texture_handle_t _handle}, `C++`],
		
		/**
		* Create frame buffer (simple).
		* Params:
		* _width = Texture width.
		* _height = Texture height.
		* _format = Texture format. See: `TextureFormat::Enum`.
		* _textureFlags = Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
		* flags. Default texture sampling mode is linear, and wrap mode is repeat.
		* - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
		*   mode.
		* - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
		*   sampling.
		*/
		[q{bgfx_frame_buffer_handle_t}, q{createFrameBuffer}, q{ushort _width, ushort _height, bgfx_texture_format_t _format, ulong _textureFlags}, `C++`],
		
		/**
		* Create frame buffer with size based on back-buffer ratio. Frame buffer will maintain ratio
		* if back buffer resolution changes.
		* Params:
		* _ratio = Frame buffer size in respect to back-buffer size. See:
		* `BackbufferRatio::Enum`.
		* _format = Texture format. See: `TextureFormat::Enum`.
		* _textureFlags = Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
		* flags. Default texture sampling mode is linear, and wrap mode is repeat.
		* - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
		*   mode.
		* - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
		*   sampling.
		*/
		[q{bgfx_frame_buffer_handle_t}, q{createFrameBuffer}, q{bgfx_backbuffer_ratio_t _ratio, bgfx_texture_format_t _format, ulong _textureFlags}, `C++`],
		
		/**
		* Create MRT frame buffer from texture handles (simple).
		* Params:
		* _num = Number of texture handles.
		* _handles = Texture attachments.
		* _destroyTexture = If true, textures will be destroyed when
		* frame buffer is destroyed.
		*/
		[q{bgfx_frame_buffer_handle_t}, q{createFrameBuffer}, q{ubyte _num, const(bgfx_texture_handle_t)* _handles, bool _destroyTexture}, `C++`],
		
		/**
		* Create MRT frame buffer from texture handles with specific layer and
		* mip level.
		* Params:
		* _num = Number of attachments.
		* _attachment = Attachment texture info. See: `bgfx::Attachment`.
		* _destroyTexture = If true, textures will be destroyed when
		* frame buffer is destroyed.
		*/
		[q{bgfx_frame_buffer_handle_t}, q{createFrameBuffer}, q{ubyte _num, const(bgfx_attachment_t)* _attachment, bool _destroyTexture}, `C++`],
		
		/**
		* Create frame buffer for multiple window rendering.
		* Remarks:
		*   Frame buffer cannot be used for sampling.
		* Attention: Availability depends on: `BGFX_CAPS_SWAP_CHAIN`.
		* Params:
		* _nwh = OS' target native window handle.
		* _width = Window back buffer width.
		* _height = Window back buffer height.
		* _format = Window back buffer color format.
		* _depthFormat = Window back buffer depth format.
		*/
		[q{bgfx_frame_buffer_handle_t}, q{createFrameBuffer}, q{void* _nwh, ushort _width, ushort _height, bgfx_texture_format_t _format, bgfx_texture_format_t _depthFormat}, `C++`],
		
		/**
		* Set frame buffer debug name.
		* Params:
		* _handle = Frame buffer handle.
		* _name = Frame buffer name.
		* _len = Frame buffer name length (if length is INT32_MAX, it's expected
		* that _name is zero terminated string.
		*/
		[q{void}, q{setName}, q{bgfx_frame_buffer_handle_t _handle, const(char)* _name, int _len}, `C++`],
		
		/**
		* Obtain texture handle of frame buffer attachment.
		* Params:
		* _handle = Frame buffer handle.
		*/
		[q{bgfx_texture_handle_t}, q{getTexture}, q{bgfx_frame_buffer_handle_t _handle, ubyte _attachment}, `C++`],
		
		/**
		* Destroy frame buffer.
		* Params:
		* _handle = Frame buffer handle.
		*/
		[q{void}, q{destroy}, q{bgfx_frame_buffer_handle_t _handle}, `C++`],
		
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
		* Params:
		* _name = Uniform name in shader.
		* _type = Type of uniform (See: `bgfx::UniformType`).
		* _num = Number of elements in array.
		*/
		[q{bgfx_uniform_handle_t}, q{createUniform}, q{const(char)* _name, bgfx_uniform_type_t _type, ushort _num}, `C++`],
		
		/**
		* Retrieve uniform info.
		* Params:
		* _handle = Handle to uniform object.
		* _info = Uniform info.
		*/
		[q{void}, q{getUniformInfo}, q{bgfx_uniform_handle_t _handle, bgfx_uniform_info_t* _info}, `C++`],
		
		/**
		* Destroy shader uniform parameter.
		* Params:
		* _handle = Handle to uniform object.
		*/
		[q{void}, q{destroy}, q{bgfx_uniform_handle_t _handle}, `C++`],
		
		/**
		* Create occlusion query.
		*/
		[q{bgfx_occlusion_query_handle_t}, q{createOcclusionQuery}, q{}, `C++`],
		
		/**
		* Retrieve occlusion query result from previous frame.
		* Params:
		* _handle = Handle to occlusion query object.
		* _result = Number of pixels that passed test. This argument
		* can be `NULL` if result of occlusion query is not needed.
		*/
		[q{bgfx_occlusion_query_result_t}, q{getResult}, q{bgfx_occlusion_query_handle_t _handle, int* _result}, `C++`],
		
		/**
		* Destroy occlusion query.
		* Params:
		* _handle = Handle to occlusion query object.
		*/
		[q{void}, q{destroy}, q{bgfx_occlusion_query_handle_t _handle}, `C++`],
		
		/**
		* Set palette color value.
		* Params:
		* _index = Index into palette.
		* _rgba = RGBA floating point values.
		*/
		[q{void}, q{setPaletteColor}, q{ubyte _index, const float[4] _rgba}, `C++`],
		
		/**
		* Set palette color value.
		* Params:
		* _index = Index into palette.
		* _rgba = Packed 32-bit RGBA value.
		*/
		[q{void}, q{setPaletteColor}, q{ubyte _index, uint _rgba}, `C++`],
		
		/**
		* Set view name.
		* Remarks:
		*   This is debug only feature.
		*   In graphics debugger view name will appear as:
		*       "nnnc <view name>"
		*        ^  ^ ^
		*        |  +--- compute (C)
		*        +------ view id
		* Params:
		* _id = View id.
		* _name = View name.
		*/
		[q{void}, q{setViewName}, q{bgfx_view_id_t _id, const(char)* _name}, `C++`],
		
		/**
		* Set view rectangle. Draw primitive outside view will be clipped.
		* Params:
		* _id = View id.
		* _x = Position x from the left corner of the window.
		* _y = Position y from the top corner of the window.
		* _width = Width of view port region.
		* _height = Height of view port region.
		*/
		[q{void}, q{setViewRect}, q{bgfx_view_id_t _id, ushort _x, ushort _y, ushort _width, ushort _height}, `C++`],
		
		/**
		* Set view rectangle. Draw primitive outside view will be clipped.
		* Params:
		* _id = View id.
		* _x = Position x from the left corner of the window.
		* _y = Position y from the top corner of the window.
		* _ratio = Width and height will be set in respect to back-buffer size.
		* See: `BackbufferRatio::Enum`.
		*/
		[q{void}, q{setViewRect}, q{bgfx_view_id_t _id, ushort _x, ushort _y, bgfx_backbuffer_ratio_t _ratio}, `C++`],
		
		/**
		* Set view scissor. Draw primitive outside view will be clipped. When
		* _x, _y, _width and _height are set to 0, scissor will be disabled.
		* Params:
		* _id = View id.
		* _x = Position x from the left corner of the window.
		* _y = Position y from the top corner of the window.
		* _width = Width of view scissor region.
		* _height = Height of view scissor region.
		*/
		[q{void}, q{setViewScissor}, q{bgfx_view_id_t _id, ushort _x, ushort _y, ushort _width, ushort _height}, `C++`],
		
		/**
		* Set view clear flags.
		* Params:
		* _id = View id.
		* _flags = Clear flags. Use `BGFX_CLEAR_NONE` to remove any clear
		* operation. See: `BGFX_CLEAR_*`.
		* _rgba = Color clear value.
		* _depth = Depth clear value.
		* _stencil = Stencil clear value.
		*/
		[q{void}, q{setViewClear}, q{bgfx_view_id_t _id, ushort _flags, uint _rgba, float _depth, ubyte _stencil}, `C++`],
		
		/**
		* Set view clear flags with different clear color for each
		* frame buffer texture. `bgfx::setPaletteColor` must be used to set up a
		* clear color palette.
		* Params:
		* _id = View id.
		* _flags = Clear flags. Use `BGFX_CLEAR_NONE` to remove any clear
		* operation. See: `BGFX_CLEAR_*`.
		* _depth = Depth clear value.
		* _stencil = Stencil clear value.
		* _c0 = Palette index for frame buffer attachment 0.
		* _c1 = Palette index for frame buffer attachment 1.
		* _c2 = Palette index for frame buffer attachment 2.
		* _c3 = Palette index for frame buffer attachment 3.
		* _c4 = Palette index for frame buffer attachment 4.
		* _c5 = Palette index for frame buffer attachment 5.
		* _c6 = Palette index for frame buffer attachment 6.
		* _c7 = Palette index for frame buffer attachment 7.
		*/
		[q{void}, q{setViewClear}, q{bgfx_view_id_t _id, ushort _flags, float _depth, ubyte _stencil, ubyte _c0, ubyte _c1, ubyte _c2, ubyte _c3, ubyte _c4, ubyte _c5, ubyte _c6, ubyte _c7}, `C++`],
		
		/**
		* Set view sorting mode.
		* Remarks:
		*   View mode must be set prior calling `bgfx::submit` for the view.
		* Params:
		* _id = View id.
		* _mode = View sort mode. See `ViewMode::Enum`.
		*/
		[q{void}, q{setViewMode}, q{bgfx_view_id_t _id, bgfx_view_mode_t _mode}, `C++`],
		
		/**
		* Set view frame buffer.
		* Remarks:
		*   Not persistent after `bgfx::reset` call.
		* Params:
		* _id = View id.
		* _handle = Frame buffer handle. Passing `BGFX_INVALID_HANDLE` as
		* frame buffer handle will draw primitives from this view into
		* default back buffer.
		*/
		[q{void}, q{setViewFrameBuffer}, q{bgfx_view_id_t _id, bgfx_frame_buffer_handle_t _handle}, `C++`],
		
		/**
		* Set view's view matrix and projection matrix,
		* all draw primitives in this view will use these two matrices.
		* Params:
		* _id = View id.
		* _view = View matrix.
		* _proj = Projection matrix.
		*/
		[q{void}, q{setViewTransform}, q{bgfx_view_id_t _id, const(void)* _view, const(void)* _proj}, `C++`],
		
		/**
		* Post submit view reordering.
		* Params:
		* _id = First view id.
		* _num = Number of views to remap.
		* _order = View remap id table. Passing `NULL` will reset view ids
		* to default state.
		*/
		[q{void}, q{setViewOrder}, q{bgfx_view_id_t _id, ushort _num, const(bgfx_view_id_t)* _order}, `C++`],
		
		/**
		* Reset all view settings to default.
		*/
		[q{void}, q{resetView}, q{bgfx_view_id_t _id}, `C++`],
		
		/**
		* Begin submitting draw calls from thread.
		* Params:
		* _forThread = Explicitly request an encoder for a worker thread.
		*/
		[q{bgfx_encoder_t*}, q{begin}, q{bool _forThread}, `C++`],
		
		/**
		* End submitting draw calls from thread.
		* Params:
		* _encoder = Encoder.
		*/
		[q{void}, q{end}, q{bgfx_encoder_t* _encoder}, `C++`],
		
		/**
		* Sets a debug marker. This allows you to group graphics calls together for easy browsing in
		* graphics debugging tools.
		* Params:
		* _marker = Marker string.
		*/
		[q{void}, q{setMarker}, q{const(char)* _marker}, `C++`],
		
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
		* Params:
		* _state = State flags. Default state for primitive type is
		*   triangles. See: `BGFX_STATE_DEFAULT`.
		*   - `BGFX_STATE_DEPTH_TEST_*` - Depth test function.
		*   - `BGFX_STATE_BLEND_*` - See remark 1 about BGFX_STATE_BLEND_FUNC.
		*   - `BGFX_STATE_BLEND_EQUATION_*` - See remark 2.
		*   - `BGFX_STATE_CULL_*` - Backface culling mode.
		*   - `BGFX_STATE_WRITE_*` - Enable R, G, B, A or Z write.
		*   - `BGFX_STATE_MSAA` - Enable hardware multisample antialiasing.
		*   - `BGFX_STATE_PT_[TRISTRIP/LINES/POINTS]` - Primitive type.
		* _rgba = Sets blend factor used by `BGFX_STATE_BLEND_FACTOR` and
		*   `BGFX_STATE_BLEND_INV_FACTOR` blend modes.
		*/
		[q{void}, q{setState}, q{ulong _state, uint _rgba}, `C++`],
		
		/**
		* Set condition for rendering.
		* Params:
		* _handle = Occlusion query handle.
		* _visible = Render if occlusion query is visible.
		*/
		[q{void}, q{setCondition}, q{bgfx_occlusion_query_handle_t _handle, bool _visible}, `C++`],
		
		/**
		* Set stencil test state.
		* Params:
		* _fstencil = Front stencil state.
		* _bstencil = Back stencil state. If back is set to `BGFX_STENCIL_NONE`
		* _fstencil is applied to both front and back facing primitives.
		*/
		[q{void}, q{setStencil}, q{uint _fstencil, uint _bstencil}, `C++`],
		
		/**
		* Set scissor for draw primitive.
		* Remarks:
		*   To scissor for all primitives in view see `bgfx::setViewScissor`.
		* Params:
		* _x = Position x from the left corner of the window.
		* _y = Position y from the top corner of the window.
		* _width = Width of view scissor region.
		* _height = Height of view scissor region.
		*/
		[q{ushort}, q{setScissor}, q{ushort _x, ushort _y, ushort _width, ushort _height}, `C++`],
		
		/**
		* Set scissor from cache for draw primitive.
		* Remarks:
		*   To scissor for all primitives in view see `bgfx::setViewScissor`.
		* Params:
		* _cache = Index in scissor cache.
		*/
		[q{void}, q{setScissor}, q{ushort _cache}, `C++`],
		
		/**
		* Set model matrix for draw primitive. If it is not called,
		* the model will be rendered with an identity model matrix.
		* Params:
		* _mtx = Pointer to first matrix in array.
		* _num = Number of matrices in array.
		*/
		[q{uint}, q{setTransform}, q{const(void)* _mtx, ushort _num}, `C++`],
		
		/**
		*  Set model matrix from matrix cache for draw primitive.
		* Params:
		* _cache = Index in matrix cache.
		* _num = Number of matrices from cache.
		*/
		[q{void}, q{setTransform}, q{uint _cache, ushort _num}, `C++`],
		
		/**
		* Reserve matrices in internal matrix cache.
		* Attention: Pointer returned can be modified until `bgfx::frame` is called.
		* Params:
		* _transform = Pointer to `Transform` structure.
		* _num = Number of matrices.
		*/
		[q{uint}, q{allocTransform}, q{bgfx_transform_t* _transform, ushort _num}, `C++`],
		
		/**
		* Set shader uniform parameter for draw primitive.
		* Params:
		* _handle = Uniform.
		* _value = Pointer to uniform data.
		* _num = Number of elements. Passing `UINT16_MAX` will
		* use the _num passed on uniform creation.
		*/
		[q{void}, q{setUniform}, q{bgfx_uniform_handle_t _handle, const(void)* _value, ushort _num}, `C++`],
		
		/**
		* Set index buffer for draw primitive.
		* Params:
		* _handle = Index buffer.
		*/
		[q{void}, q{setIndexBuffer}, q{bgfx_index_buffer_handle_t _handle}, `C++`],
		
		/**
		* Set index buffer for draw primitive.
		* Params:
		* _handle = Index buffer.
		* _firstIndex = First index to render.
		* _numIndices = Number of indices to render.
		*/
		[q{void}, q{setIndexBuffer}, q{bgfx_index_buffer_handle_t _handle, uint _firstIndex, uint _numIndices}, `C++`],
		
		/**
		* Set index buffer for draw primitive.
		* Params:
		* _handle = Dynamic index buffer.
		*/
		[q{void}, q{setIndexBuffer}, q{bgfx_dynamic_index_buffer_handle_t _handle}, `C++`],
		
		/**
		* Set index buffer for draw primitive.
		* Params:
		* _handle = Dynamic index buffer.
		* _firstIndex = First index to render.
		* _numIndices = Number of indices to render.
		*/
		[q{void}, q{setIndexBuffer}, q{bgfx_dynamic_index_buffer_handle_t _handle, uint _firstIndex, uint _numIndices}, `C++`],
		
		/**
		* Set index buffer for draw primitive.
		* Params:
		* _tib = Transient index buffer.
		*/
		[q{void}, q{setIndexBuffer}, q{const(bgfx_transient_index_buffer_t)* _tib}, `C++`],
		
		/**
		* Set index buffer for draw primitive.
		* Params:
		* _tib = Transient index buffer.
		* _firstIndex = First index to render.
		* _numIndices = Number of indices to render.
		*/
		[q{void}, q{setIndexBuffer}, q{const(bgfx_transient_index_buffer_t)* _tib, uint _firstIndex, uint _numIndices}, `C++`],
		
		/**
		* Set vertex buffer for draw primitive.
		* Params:
		* _stream = Vertex stream.
		* _handle = Vertex buffer.
		*/
		[q{void}, q{setVertexBuffer}, q{ubyte _stream, bgfx_vertex_buffer_handle_t _handle}, `C++`],
		
		/**
		* Set vertex buffer for draw primitive.
		* Params:
		* _stream = Vertex stream.
		* _handle = Vertex buffer.
		* _startVertex = First vertex to render.
		* _numVertices = Number of vertices to render.
		*/
		[q{void}, q{setVertexBuffer}, q{ubyte _stream, bgfx_vertex_buffer_handle_t _handle, uint _startVertex, uint _numVertices}, `C++`],
		
		/**
		* Set vertex buffer for draw primitive.
		* Params:
		* _stream = Vertex stream.
		* _handle = Vertex buffer.
		* _startVertex = First vertex to render.
		* _numVertices = Number of vertices to render.
		* _layoutHandle = Vertex layout for aliasing vertex buffer. If invalid
		* handle is used, vertex layout used for creation
		* of vertex buffer will be used.
		*/
		[q{void}, q{setVertexBuffer}, q{ubyte _stream, bgfx_vertex_buffer_handle_t _handle, uint _startVertex, uint _numVertices, bgfx_vertex_layout_handle_t _layoutHandle}, `C++`],
		
		/**
		* Set vertex buffer for draw primitive.
		* Params:
		* _stream = Vertex stream.
		* _handle = Dynamic vertex buffer.
		*/
		[q{void}, q{setVertexBuffer}, q{ubyte _stream, bgfx_dynamic_vertex_buffer_handle_t _handle}, `C++`],
		
		/**
		* Set vertex buffer for draw primitive.
		* Params:
		* _stream = Vertex stream.
		* _handle = Dynamic vertex buffer.
		* _startVertex = First vertex to render.
		* _numVertices = Number of vertices to render.
		*/
		[q{void}, q{setVertexBuffer}, q{ubyte _stream, bgfx_dynamic_vertex_buffer_handle_t _handle, uint _startVertex, uint _numVertices}, `C++`],
		
		[q{void}, q{setVertexBuffer}, q{ubyte _stream, bgfx_dynamic_vertex_buffer_handle_t _handle, uint _startVertex, uint _numVertices, bgfx_vertex_layout_handle_t _layoutHandle}, `C++`],
		
		/**
		* Set vertex buffer for draw primitive.
		* Params:
		* _stream = Vertex stream.
		* _tvb = Transient vertex buffer.
		*/
		[q{void}, q{setVertexBuffer}, q{ubyte _stream, const(bgfx_transient_vertex_buffer_t)* _tvb}, `C++`],
		
		/**
		* Set vertex buffer for draw primitive.
		* Params:
		* _stream = Vertex stream.
		* _tvb = Transient vertex buffer.
		* _startVertex = First vertex to render.
		* _numVertices = Number of vertices to render.
		*/
		[q{void}, q{setVertexBuffer}, q{ubyte _stream, const(bgfx_transient_vertex_buffer_t)* _tvb, uint _startVertex, uint _numVertices}, `C++`],
		
		/**
		* Set vertex buffer for draw primitive.
		* Params:
		* _stream = Vertex stream.
		* _tvb = Transient vertex buffer.
		* _startVertex = First vertex to render.
		* _numVertices = Number of vertices to render.
		* _layoutHandle = Vertex layout for aliasing vertex buffer. If invalid
		* handle is used, vertex layout used for creation
		* of vertex buffer will be used.
		*/
		[q{void}, q{setVertexBuffer}, q{ubyte _stream, const(bgfx_transient_vertex_buffer_t)* _tvb, uint _startVertex, uint _numVertices, bgfx_vertex_layout_handle_t _layoutHandle}, `C++`],
		
		/**
		* Set number of vertices for auto generated vertices use in conjunction
		* with gl_VertexID.
		* Attention: Availability depends on: `BGFX_CAPS_VERTEX_ID`.
		* Params:
		* _numVertices = Number of vertices.
		*/
		[q{void}, q{setVertexCount}, q{uint _numVertices}, `C++`],
		
		/**
		* Set instance data buffer for draw primitive.
		* Params:
		* _idb = Transient instance data buffer.
		*/
		[q{void}, q{setInstanceDataBuffer}, q{const(bgfx_instance_data_buffer_t)* _idb}, `C++`],
		
		/**
		* Set instance data buffer for draw primitive.
		* Params:
		* _idb = Transient instance data buffer.
		* _start = First instance data.
		* _num = Number of data instances.
		*/
		[q{void}, q{setInstanceDataBuffer}, q{const(bgfx_instance_data_buffer_t)* _idb, uint _start, uint _num}, `C++`],
		
		/**
		* Set instance data buffer for draw primitive.
		* Params:
		* _handle = Vertex buffer.
		*/
		[q{void}, q{setInstanceDataBuffer}, q{bgfx_vertex_buffer_handle_t _handle}, `C++`],
		
		/**
		* Set instance data buffer for draw primitive.
		* Params:
		* _handle = Vertex buffer.
		* _startVertex = First instance data.
		* _num = Number of data instances.
		* Set instance data buffer for draw primitive.
		*/
		[q{void}, q{setInstanceDataBuffer}, q{bgfx_vertex_buffer_handle_t _handle, uint _startVertex, uint _num}, `C++`],
		
		[q{void}, q{setInstanceDataBuffer}, q{bgfx_dynamic_vertex_buffer_handle_t _handle}, `C++`],
		
		/**
		* Set instance data buffer for draw primitive.
		* Params:
		* _handle = Dynamic vertex buffer.
		* _startVertex = First instance data.
		* _num = Number of data instances.
		*/
		[q{void}, q{setInstanceDataBuffer}, q{bgfx_dynamic_vertex_buffer_handle_t _handle, uint _startVertex, uint _num}, `C++`],
		
		/**
		* Set number of instances for auto generated instances use in conjunction
		* with gl_InstanceID.
		* Attention: Availability depends on: `BGFX_CAPS_VERTEX_ID`.
		*/
		[q{void}, q{setInstanceCount}, q{uint _numInstances}, `C++`],
		
		/**
		* Set texture stage for draw primitive.
		* Params:
		* _stage = Texture unit.
		* _sampler = Program sampler.
		* _handle = Texture handle.
		* _flags = Texture sampling mode. Default value UINT32_MAX uses
		*   texture sampling settings from the texture.
		*   - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
		*     mode.
		*   - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
		*     sampling.
		*/
		[q{void}, q{setTexture}, q{ubyte _stage, bgfx_uniform_handle_t _sampler, bgfx_texture_handle_t _handle, uint _flags}, `C++`],
		
		/**
		* Submit an empty primitive for rendering. Uniforms and draw state
		* will be applied but no geometry will be submitted. Useful in cases
		* when no other draw/compute primitive is submitted to view, but it's
		* desired to execute clear view.
		* Remarks:
		*   These empty draw calls will sort before ordinary draw calls.
		* Params:
		* _id = View id.
		*/
		[q{void}, q{touch}, q{bgfx_view_id_t _id}, `C++`],
		
		/**
		* Submit primitive for rendering.
		* Params:
		* _id = View id.
		* _program = Program.
		* _depth = Depth for sorting.
		* _flags = Discard or preserve states. See `BGFX_DISCARD_*`.
		*/
		[q{void}, q{submit}, q{bgfx_view_id_t _id, bgfx_program_handle_t _program, uint _depth, ubyte _flags}, `C++`],
		
		/**
		* Submit primitive with occlusion query for rendering.
		* Params:
		* _id = View id.
		* _program = Program.
		* _occlusionQuery = Occlusion query.
		* _depth = Depth for sorting.
		* _flags = Discard or preserve states. See `BGFX_DISCARD_*`.
		*/
		[q{void}, q{submit}, q{bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_occlusion_query_handle_t _occlusionQuery, uint _depth, ubyte _flags}, `C++`],
		
		/**
		* Submit primitive for rendering with index and instance data info from
		* indirect buffer.
		* Attention: Availability depends on: `BGFX_CAPS_DRAW_INDIRECT`.
		* Params:
		* _id = View id.
		* _program = Program.
		* _indirectHandle = Indirect buffer.
		* _start = First element in indirect buffer.
		* _num = Number of draws.
		* _depth = Depth for sorting.
		* _flags = Discard or preserve states. See `BGFX_DISCARD_*`.
		*/
		[q{void}, q{submit}, q{bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_indirect_buffer_handle_t _indirectHandle, ushort _start, ushort _num, uint _depth, ubyte _flags}, `C++`],
		
		/**
		* Submit primitive for rendering with index and instance data info and
		* draw count from indirect buffers.
		* Attention: Availability depends on: `BGFX_CAPS_DRAW_INDIRECT_COUNT`.
		* Params:
		* _id = View id.
		* _program = Program.
		* _indirectHandle = Indirect buffer.
		* _start = First element in indirect buffer.
		* _numHandle = Buffer for number of draws. Must be
		*   created with `BGFX_BUFFER_INDEX32` and `BGFX_BUFFER_DRAW_INDIRECT`.
		* _numIndex = Element in number buffer.
		* _numMax = Max number of draws.
		* _depth = Depth for sorting.
		* _flags = Discard or preserve states. See `BGFX_DISCARD_*`.
		*/
		[q{void}, q{submit}, q{bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_indirect_buffer_handle_t _indirectHandle, ushort _start, bgfx_index_buffer_handle_t _numHandle, uint _numIndex, ushort _numMax, uint _depth, ubyte _flags}, `C++`],
		
		/**
		* Set compute index buffer.
		* Params:
		* _stage = Compute stage.
		* _handle = Index buffer handle.
		* _access = Buffer access. See `Access::Enum`.
		*/
		[q{void}, q{setBuffer}, q{ubyte _stage, bgfx_index_buffer_handle_t _handle, bgfx_access_t _access}, `C++`],
		
		/**
		* Set compute vertex buffer.
		* Params:
		* _stage = Compute stage.
		* _handle = Vertex buffer handle.
		* _access = Buffer access. See `Access::Enum`.
		*/
		[q{void}, q{setBuffer}, q{ubyte _stage, bgfx_vertex_buffer_handle_t _handle, bgfx_access_t _access}, `C++`],
		
		/**
		* Set compute dynamic index buffer.
		* Params:
		* _stage = Compute stage.
		* _handle = Dynamic index buffer handle.
		* _access = Buffer access. See `Access::Enum`.
		*/
		[q{void}, q{setBuffer}, q{ubyte _stage, bgfx_dynamic_index_buffer_handle_t _handle, bgfx_access_t _access}, `C++`],
		
		/**
		* Set compute dynamic vertex buffer.
		* Params:
		* _stage = Compute stage.
		* _handle = Dynamic vertex buffer handle.
		* _access = Buffer access. See `Access::Enum`.
		*/
		[q{void}, q{setBuffer}, q{ubyte _stage, bgfx_dynamic_vertex_buffer_handle_t _handle, bgfx_access_t _access}, `C++`],
		
		/**
		* Set compute indirect buffer.
		* Params:
		* _stage = Compute stage.
		* _handle = Indirect buffer handle.
		* _access = Buffer access. See `Access::Enum`.
		*/
		[q{void}, q{setBuffer}, q{ubyte _stage, bgfx_indirect_buffer_handle_t _handle, bgfx_access_t _access}, `C++`],
		
		/**
		* Set compute image from texture.
		* Params:
		* _stage = Compute stage.
		* _handle = Texture handle.
		* _mip = Mip level.
		* _access = Image access. See `Access::Enum`.
		* _format = Texture format. See: `TextureFormat::Enum`.
		*/
		[q{void}, q{setImage}, q{ubyte _stage, bgfx_texture_handle_t _handle, ubyte _mip, bgfx_access_t _access, bgfx_texture_format_t _format}, `C++`],
		
		/**
		* Dispatch compute.
		* Params:
		* _id = View id.
		* _program = Compute program.
		* _numX = Number of groups X.
		* _numY = Number of groups Y.
		* _numZ = Number of groups Z.
		* _flags = Discard or preserve states. See `BGFX_DISCARD_*`.
		*/
		[q{void}, q{dispatch}, q{bgfx_view_id_t _id, bgfx_program_handle_t _program, uint _numX, uint _numY, uint _numZ, ubyte _flags}, `C++`],
		
		/**
		* Dispatch compute indirect.
		* Params:
		* _id = View id.
		* _program = Compute program.
		* _indirectHandle = Indirect buffer.
		* _start = First element in indirect buffer.
		* _num = Number of dispatches.
		* _flags = Discard or preserve states. See `BGFX_DISCARD_*`.
		*/
		[q{void}, q{dispatch}, q{bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_indirect_buffer_handle_t _indirectHandle, ushort _start, ushort _num, ubyte _flags}, `C++`],
		
		/**
		* Discard previously set state for draw or compute call.
		* Params:
		* _flags = Discard or preserve states. See `BGFX_DISCARD_*`.
		*/
		[q{void}, q{discard}, q{ubyte _flags}, `C++`],
		
		/**
		* Blit 2D texture region between two 2D textures.
		* Attention: Destination texture must be created with `BGFX_TEXTURE_BLIT_DST` flag.
		* Attention: Availability depends on: `BGFX_CAPS_TEXTURE_BLIT`.
		* Params:
		* _id = View id.
		* _dst = Destination texture handle.
		* _dstX = Destination texture X position.
		* _dstY = Destination texture Y position.
		* _src = Source texture handle.
		* _srcX = Source texture X position.
		* _srcY = Source texture Y position.
		* _width = Width of region.
		* _height = Height of region.
		*/
		[q{void}, q{blit}, q{bgfx_view_id_t _id, bgfx_texture_handle_t _dst, ushort _dstX, ushort _dstY, bgfx_texture_handle_t _src, ushort _srcX, ushort _srcY, ushort _width, ushort _height}, `C++`],
		
		/**
		* Blit 2D texture region between two 2D textures.
		* Attention: Destination texture must be created with `BGFX_TEXTURE_BLIT_DST` flag.
		* Attention: Availability depends on: `BGFX_CAPS_TEXTURE_BLIT`.
		* Params:
		* _id = View id.
		* _dst = Destination texture handle.
		* _dstMip = Destination texture mip level.
		* _dstX = Destination texture X position.
		* _dstY = Destination texture Y position.
		* _dstZ = If texture is 2D this argument should be 0. If destination texture is cube
		* this argument represents destination texture cube face. For 3D texture this argument
		* represents destination texture Z position.
		* _src = Source texture handle.
		* _srcMip = Source texture mip level.
		* _srcX = Source texture X position.
		* _srcY = Source texture Y position.
		* _srcZ = If texture is 2D this argument should be 0. If source texture is cube
		* this argument represents source texture cube face. For 3D texture this argument
		* represents source texture Z position.
		* _width = Width of region.
		* _height = Height of region.
		* _depth = If texture is 3D this argument represents depth of region, otherwise it's
		* unused.
		*/
		[q{void}, q{blit}, q{bgfx_view_id_t _id, bgfx_texture_handle_t _dst, ubyte _dstMip, ushort _dstX, ushort _dstY, ushort _dstZ, bgfx_texture_handle_t _src, ubyte _srcMip, ushort _srcX, ushort _srcY, ushort _srcZ, ushort _width, ushort _height, ushort _depth}, `C++`],
		
		/**
		* Request screen shot of window back buffer.
		* Remarks:
		*   `bgfx::CallbackI::screenShot` must be implemented.
		* Attention: Frame buffer handle must be created with OS' target native window handle.
		* Params:
		* _handle = Frame buffer handle. If handle is `BGFX_INVALID_HANDLE` request will be
		* made for main window back buffer.
		* _filePath = Will be passed to `bgfx::CallbackI::screenShot` callback.
		*/
		[q{void}, q{requestScreenShot}, q{bgfx_frame_buffer_handle_t _handle, const(char)* _filePath}, `C++`],
		
		/**
		* Render frame.
		* Attention: `bgfx::renderFrame` is blocking call. It waits for
		*   `bgfx::frame` to be called from API thread to process frame.
		*   If timeout value is passed call will timeout and return even
		*   if `bgfx::frame` is not called.
		* Warning: This call should be only used on platforms that don't
		*   allow creating separate rendering thread. If it is called before
		*   to bgfx::init, render thread won't be created by bgfx::init call.
		* Params:
		* _msecs = Timeout in milliseconds.
		*/
		[q{bgfx_render_frame_t}, q{renderFrame}, q{int _msecs}, `C++`],
		
		/**
		* Set platform data.
		* Warning: Must be called before `bgfx::init`.
		* Params:
		* _data = Platform data.
		*/
		[q{void}, q{setPlatformData}, q{const(bgfx_platform_data_t)* _data}, `C++`],
		
		/**
		* Get internal data for interop.
		* Attention: It's expected you understand some bgfx internals before you
		*   use this call.
		* Warning: Must be called only on render thread.
		*/
		[q{const(bgfx_internal_data_t)*}, q{getInternalData}, q{}, `C++`],
		
		/**
		* Override internal texture with externally created texture. Previously
		* created internal texture will released.
		* Attention: It's expected you understand some bgfx internals before you
		*   use this call.
		* Warning: Must be called only on render thread.
		* Params:
		* _handle = Texture handle.
		* _ptr = Native API pointer to texture.
		*/
		[q{size_t}, q{overrideInternal}, q{bgfx_texture_handle_t _handle, size_t _ptr}, `C++`],
		
		/**
		* Override internal texture by creating new texture. Previously created
		* internal texture will released.
		* Attention: It's expected you understand some bgfx internals before you
		*   use this call.
		* Returns: Native API pointer to texture. If result is 0, texture is not created yet from the
		*   main thread.
		* Warning: Must be called only on render thread.
		* Params:
		* _handle = Texture handle.
		* _width = Width.
		* _height = Height.
		* _numMips = Number of mip-maps.
		* _format = Texture format. See: `TextureFormat::Enum`.
		* _flags = Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
		* flags. Default texture sampling mode is linear, and wrap mode is repeat.
		* - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
		*   mode.
		* - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
		*   sampling.
		*/
		[q{size_t}, q{overrideInternal}, q{bgfx_texture_handle_t _handle, ushort _width, ushort _height, ubyte _numMips, bgfx_texture_format_t _format, ulong _flags}, `C++`],
		
		/**
		* Sets a debug marker. This allows you to group graphics calls together for easy browsing in
		* graphics debugging tools.
		* Params:
		* _marker = Marker string.
		*/
		[q{void}, q{setMarker}, q{const(char)* _marker}, `C++`],
		
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
		* Params:
		* _state = State flags. Default state for primitive type is
		*   triangles. See: `BGFX_STATE_DEFAULT`.
		*   - `BGFX_STATE_DEPTH_TEST_*` - Depth test function.
		*   - `BGFX_STATE_BLEND_*` - See remark 1 about BGFX_STATE_BLEND_FUNC.
		*   - `BGFX_STATE_BLEND_EQUATION_*` - See remark 2.
		*   - `BGFX_STATE_CULL_*` - Backface culling mode.
		*   - `BGFX_STATE_WRITE_*` - Enable R, G, B, A or Z write.
		*   - `BGFX_STATE_MSAA` - Enable hardware multisample antialiasing.
		*   - `BGFX_STATE_PT_[TRISTRIP/LINES/POINTS]` - Primitive type.
		* _rgba = Sets blend factor used by `BGFX_STATE_BLEND_FACTOR` and
		*   `BGFX_STATE_BLEND_INV_FACTOR` blend modes.
		*/
		[q{void}, q{setState}, q{ulong _state, uint _rgba}, `C++`],
		
		/**
		* Set condition for rendering.
		* Params:
		* _handle = Occlusion query handle.
		* _visible = Render if occlusion query is visible.
		*/
		[q{void}, q{setCondition}, q{bgfx_occlusion_query_handle_t _handle, bool _visible}, `C++`],
		
		/**
		* Set stencil test state.
		* Params:
		* _fstencil = Front stencil state.
		* _bstencil = Back stencil state. If back is set to `BGFX_STENCIL_NONE`
		* _fstencil is applied to both front and back facing primitives.
		*/
		[q{void}, q{setStencil}, q{uint _fstencil, uint _bstencil}, `C++`],
		
		/**
		* Set scissor for draw primitive.
		* Remarks:
		*   To scissor for all primitives in view see `bgfx::setViewScissor`.
		* Params:
		* _x = Position x from the left corner of the window.
		* _y = Position y from the top corner of the window.
		* _width = Width of view scissor region.
		* _height = Height of view scissor region.
		*/
		[q{ushort}, q{setScissor}, q{ushort _x, ushort _y, ushort _width, ushort _height}, `C++`],
		
		/**
		* Set scissor from cache for draw primitive.
		* Remarks:
		*   To scissor for all primitives in view see `bgfx::setViewScissor`.
		* Params:
		* _cache = Index in scissor cache.
		*/
		[q{void}, q{setScissor}, q{ushort _cache}, `C++`],
		
		/**
		* Set model matrix for draw primitive. If it is not called,
		* the model will be rendered with an identity model matrix.
		* Params:
		* _mtx = Pointer to first matrix in array.
		* _num = Number of matrices in array.
		*/
		[q{uint}, q{setTransform}, q{const(void)* _mtx, ushort _num}, `C++`],
		
		/**
		*  Set model matrix from matrix cache for draw primitive.
		* Params:
		* _cache = Index in matrix cache.
		* _num = Number of matrices from cache.
		*/
		[q{void}, q{setTransform}, q{uint _cache, ushort _num}, `C++`],
		
		/**
		* Reserve matrices in internal matrix cache.
		* Attention: Pointer returned can be modified until `bgfx::frame` is called.
		* Params:
		* _transform = Pointer to `Transform` structure.
		* _num = Number of matrices.
		*/
		[q{uint}, q{allocTransform}, q{bgfx_transform_t* _transform, ushort _num}, `C++`],
		
		/**
		* Set shader uniform parameter for draw primitive.
		* Params:
		* _handle = Uniform.
		* _value = Pointer to uniform data.
		* _num = Number of elements. Passing `UINT16_MAX` will
		* use the _num passed on uniform creation.
		*/
		[q{void}, q{setUniform}, q{bgfx_uniform_handle_t _handle, const(void)* _value, ushort _num}, `C++`],
		
		/**
		* Set index buffer for draw primitive.
		* Params:
		* _handle = Index buffer.
		*/
		[q{void}, q{setIndexBuffer}, q{bgfx_index_buffer_handle_t _handle}, `C++`],
		
		/**
		* Set index buffer for draw primitive.
		* Params:
		* _handle = Index buffer.
		* _firstIndex = First index to render.
		* _numIndices = Number of indices to render.
		*/
		[q{void}, q{setIndexBuffer}, q{bgfx_index_buffer_handle_t _handle, uint _firstIndex, uint _numIndices}, `C++`],
		
		/**
		* Set index buffer for draw primitive.
		* Params:
		* _handle = Dynamic index buffer.
		*/
		[q{void}, q{setIndexBuffer}, q{bgfx_dynamic_index_buffer_handle_t _handle}, `C++`],
		
		/**
		* Set index buffer for draw primitive.
		* Params:
		* _handle = Dynamic index buffer.
		* _firstIndex = First index to render.
		* _numIndices = Number of indices to render.
		*/
		[q{void}, q{setIndexBuffer}, q{bgfx_dynamic_index_buffer_handle_t _handle, uint _firstIndex, uint _numIndices}, `C++`],
		
		/**
		* Set index buffer for draw primitive.
		* Params:
		* _tib = Transient index buffer.
		*/
		[q{void}, q{setIndexBuffer}, q{const(bgfx_transient_index_buffer_t)* _tib}, `C++`],
		
		/**
		* Set index buffer for draw primitive.
		* Params:
		* _tib = Transient index buffer.
		* _firstIndex = First index to render.
		* _numIndices = Number of indices to render.
		*/
		[q{void}, q{setIndexBuffer}, q{const(bgfx_transient_index_buffer_t)* _tib, uint _firstIndex, uint _numIndices}, `C++`],
		
		/**
		* Set vertex buffer for draw primitive.
		* Params:
		* _stream = Vertex stream.
		* _handle = Vertex buffer.
		*/
		[q{void}, q{setVertexBuffer}, q{ubyte _stream, bgfx_vertex_buffer_handle_t _handle}, `C++`],
		
		/**
		* Set vertex buffer for draw primitive.
		* Params:
		* _stream = Vertex stream.
		* _handle = Vertex buffer.
		* _startVertex = First vertex to render.
		* _numVertices = Number of vertices to render.
		*/
		[q{void}, q{setVertexBuffer}, q{ubyte _stream, bgfx_vertex_buffer_handle_t _handle, uint _startVertex, uint _numVertices}, `C++`],
		
		/**
		* Set vertex buffer for draw primitive.
		* Params:
		* _stream = Vertex stream.
		* _handle = Vertex buffer.
		* _startVertex = First vertex to render.
		* _numVertices = Number of vertices to render.
		* _layoutHandle = Vertex layout for aliasing vertex buffer. If invalid
		* handle is used, vertex layout used for creation
		* of vertex buffer will be used.
		*/
		[q{void}, q{setVertexBuffer}, q{ubyte _stream, bgfx_vertex_buffer_handle_t _handle, uint _startVertex, uint _numVertices, bgfx_vertex_layout_handle_t _layoutHandle}, `C++`],
		
		/**
		* Set vertex buffer for draw primitive.
		* Params:
		* _stream = Vertex stream.
		* _handle = Dynamic vertex buffer.
		*/
		[q{void}, q{setVertexBuffer}, q{ubyte _stream, bgfx_dynamic_vertex_buffer_handle_t _handle}, `C++`],
		
		/**
		* Set vertex buffer for draw primitive.
		* Params:
		* _stream = Vertex stream.
		* _handle = Dynamic vertex buffer.
		* _startVertex = First vertex to render.
		* _numVertices = Number of vertices to render.
		*/
		[q{void}, q{setVertexBuffer}, q{ubyte _stream, bgfx_dynamic_vertex_buffer_handle_t _handle, uint _startVertex, uint _numVertices}, `C++`],
		
		/**
		* Set vertex buffer for draw primitive.
		* Params:
		* _stream = Vertex stream.
		* _handle = Dynamic vertex buffer.
		* _startVertex = First vertex to render.
		* _numVertices = Number of vertices to render.
		* _layoutHandle = Vertex layout for aliasing vertex buffer. If invalid
		* handle is used, vertex layout used for creation
		* of vertex buffer will be used.
		*/
		[q{void}, q{setVertexBuffer}, q{ubyte _stream, bgfx_dynamic_vertex_buffer_handle_t _handle, uint _startVertex, uint _numVertices, bgfx_vertex_layout_handle_t _layoutHandle}, `C++`],
		
		/**
		* Set vertex buffer for draw primitive.
		* Params:
		* _stream = Vertex stream.
		* _tvb = Transient vertex buffer.
		*/
		[q{void}, q{setVertexBuffer}, q{ubyte _stream, const(bgfx_transient_vertex_buffer_t)* _tvb}, `C++`],
		
		/**
		* Set vertex buffer for draw primitive.
		* Params:
		* _stream = Vertex stream.
		* _tvb = Transient vertex buffer.
		* _startVertex = First vertex to render.
		* _numVertices = Number of vertices to render.
		*/
		[q{void}, q{setVertexBuffer}, q{ubyte _stream, const(bgfx_transient_vertex_buffer_t)* _tvb, uint _startVertex, uint _numVertices}, `C++`],
		
		/**
		* Set vertex buffer for draw primitive.
		* Params:
		* _stream = Vertex stream.
		* _tvb = Transient vertex buffer.
		* _startVertex = First vertex to render.
		* _numVertices = Number of vertices to render.
		* _layoutHandle = Vertex layout for aliasing vertex buffer. If invalid
		* handle is used, vertex layout used for creation
		* of vertex buffer will be used.
		*/
		[q{void}, q{setVertexBuffer}, q{ubyte _stream, const(bgfx_transient_vertex_buffer_t)* _tvb, uint _startVertex, uint _numVertices, bgfx_vertex_layout_handle_t _layoutHandle}, `C++`],
		
		/**
		* Set number of vertices for auto generated vertices use in conjunction
		* with gl_VertexID.
		* Attention: Availability depends on: `BGFX_CAPS_VERTEX_ID`.
		* Params:
		* _numVertices = Number of vertices.
		*/
		[q{void}, q{setVertexCount}, q{uint _numVertices}, `C++`],
		
		/**
		* Set instance data buffer for draw primitive.
		* Params:
		* _idb = Transient instance data buffer.
		*/
		[q{void}, q{setInstanceDataBuffer}, q{const(bgfx_instance_data_buffer_t)* _idb}, `C++`],
		
		/**
		* Set instance data buffer for draw primitive.
		* Params:
		* _idb = Transient instance data buffer.
		* _start = First instance data.
		* _num = Number of data instances.
		*/
		[q{void}, q{setInstanceDataBuffer}, q{const(bgfx_instance_data_buffer_t)* _idb, uint _start, uint _num}, `C++`],
		
		/**
		* Set instance data buffer for draw primitive.
		* Params:
		* _handle = Vertex buffer.
		*/
		[q{void}, q{setInstanceDataBuffer}, q{bgfx_vertex_buffer_handle_t _handle}, `C++`],
		
		/**
		* Set instance data buffer for draw primitive.
		* Params:
		* _handle = Vertex buffer.
		* _startVertex = First instance data.
		* _num = Number of data instances.
		* Set instance data buffer for draw primitive.
		*/
		[q{void}, q{setInstanceDataBuffer}, q{bgfx_vertex_buffer_handle_t _handle, uint _startVertex, uint _num}, `C++`],
		
		[q{void}, q{setInstanceDataBuffer}, q{bgfx_dynamic_vertex_buffer_handle_t _handle}, `C++`],
		
		/**
		* Set instance data buffer for draw primitive.
		* Params:
		* _handle = Dynamic vertex buffer.
		* _startVertex = First instance data.
		* _num = Number of data instances.
		*/
		[q{void}, q{setInstanceDataBuffer}, q{bgfx_dynamic_vertex_buffer_handle_t _handle, uint _startVertex, uint _num}, `C++`],
		
		/**
		* Set number of instances for auto generated instances use in conjunction
		* with gl_InstanceID.
		* Attention: Availability depends on: `BGFX_CAPS_VERTEX_ID`.
		*/
		[q{void}, q{setInstanceCount}, q{uint _numInstances}, `C++`],
		
		/**
		* Set texture stage for draw primitive.
		* Params:
		* _stage = Texture unit.
		* _sampler = Program sampler.
		* _handle = Texture handle.
		* _flags = Texture sampling mode. Default value UINT32_MAX uses
		*   texture sampling settings from the texture.
		*   - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
		*     mode.
		*   - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
		*     sampling.
		*/
		[q{void}, q{setTexture}, q{ubyte _stage, bgfx_uniform_handle_t _sampler, bgfx_texture_handle_t _handle, uint _flags}, `C++`],
		
		/**
		* Submit an empty primitive for rendering. Uniforms and draw state
		* will be applied but no geometry will be submitted.
		* Remarks:
		*   These empty draw calls will sort before ordinary draw calls.
		* Params:
		* _id = View id.
		*/
		[q{void}, q{touch}, q{bgfx_view_id_t _id}, `C++`],
		
		/**
		* Submit primitive for rendering.
		* Params:
		* _id = View id.
		* _program = Program.
		* _depth = Depth for sorting.
		* _flags = Which states to discard for next draw. See `BGFX_DISCARD_*`.
		*/
		[q{void}, q{submit}, q{bgfx_view_id_t _id, bgfx_program_handle_t _program, uint _depth, ubyte _flags}, `C++`],
		
		/**
		* Submit primitive with occlusion query for rendering.
		* Params:
		* _id = View id.
		* _program = Program.
		* _occlusionQuery = Occlusion query.
		* _depth = Depth for sorting.
		* _flags = Which states to discard for next draw. See `BGFX_DISCARD_*`.
		*/
		[q{void}, q{submit}, q{bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_occlusion_query_handle_t _occlusionQuery, uint _depth, ubyte _flags}, `C++`],
		
		/**
		* Submit primitive for rendering with index and instance data info from
		* indirect buffer.
		* Attention: Availability depends on: `BGFX_CAPS_DRAW_INDIRECT`.
		* Params:
		* _id = View id.
		* _program = Program.
		* _indirectHandle = Indirect buffer.
		* _start = First element in indirect buffer.
		* _num = Number of draws.
		* _depth = Depth for sorting.
		* _flags = Which states to discard for next draw. See `BGFX_DISCARD_*`.
		*/
		[q{void}, q{submit}, q{bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_indirect_buffer_handle_t _indirectHandle, ushort _start, ushort _num, uint _depth, ubyte _flags}, `C++`],
		
		/**
		* Submit primitive for rendering with index and instance data info and
		* draw count from indirect buffers.
		* Attention: Availability depends on: `BGFX_CAPS_DRAW_INDIRECT_COUNT`.
		* Params:
		* _id = View id.
		* _program = Program.
		* _indirectHandle = Indirect buffer.
		* _start = First element in indirect buffer.
		* _numHandle = Buffer for number of draws. Must be
		*   created with `BGFX_BUFFER_INDEX32` and `BGFX_BUFFER_DRAW_INDIRECT`.
		* _numIndex = Element in number buffer.
		* _numMax = Max number of draws.
		* _depth = Depth for sorting.
		* _flags = Which states to discard for next draw. See `BGFX_DISCARD_*`.
		*/
		[q{void}, q{submit}, q{bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_indirect_buffer_handle_t _indirectHandle, ushort _start, bgfx_index_buffer_handle_t _numHandle, uint _numIndex, ushort _numMax, uint _depth, ubyte _flags}, `C++`],
		
		/**
		* Set compute index buffer.
		* Params:
		* _stage = Compute stage.
		* _handle = Index buffer handle.
		* _access = Buffer access. See `Access::Enum`.
		*/
		[q{void}, q{setBuffer}, q{ubyte _stage, bgfx_index_buffer_handle_t _handle, bgfx_access_t _access}, `C++`],
		
		/**
		* Set compute vertex buffer.
		* Params:
		* _stage = Compute stage.
		* _handle = Vertex buffer handle.
		* _access = Buffer access. See `Access::Enum`.
		*/
		[q{void}, q{setBuffer}, q{ubyte _stage, bgfx_vertex_buffer_handle_t _handle, bgfx_access_t _access}, `C++`],
		
		/**
		* Set compute dynamic index buffer.
		* Params:
		* _stage = Compute stage.
		* _handle = Dynamic index buffer handle.
		* _access = Buffer access. See `Access::Enum`.
		*/
		[q{void}, q{setBuffer}, q{ubyte _stage, bgfx_dynamic_index_buffer_handle_t _handle, bgfx_access_t _access}, `C++`],
		
		/**
		* Set compute dynamic vertex buffer.
		* Params:
		* _stage = Compute stage.
		* _handle = Dynamic vertex buffer handle.
		* _access = Buffer access. See `Access::Enum`.
		*/
		[q{void}, q{setBuffer}, q{ubyte _stage, bgfx_dynamic_vertex_buffer_handle_t _handle, bgfx_access_t _access}, `C++`],
		
		/**
		* Set compute indirect buffer.
		* Params:
		* _stage = Compute stage.
		* _handle = Indirect buffer handle.
		* _access = Buffer access. See `Access::Enum`.
		*/
		[q{void}, q{setBuffer}, q{ubyte _stage, bgfx_indirect_buffer_handle_t _handle, bgfx_access_t _access}, `C++`],
		
		/**
		* Set compute image from texture.
		* Params:
		* _stage = Compute stage.
		* _handle = Texture handle.
		* _mip = Mip level.
		* _access = Image access. See `Access::Enum`.
		* _format = Texture format. See: `TextureFormat::Enum`.
		*/
		[q{void}, q{setImage}, q{ubyte _stage, bgfx_texture_handle_t _handle, ubyte _mip, bgfx_access_t _access, bgfx_texture_format_t _format}, `C++`],
		
		/**
		* Dispatch compute.
		* Params:
		* _id = View id.
		* _program = Compute program.
		* _numX = Number of groups X.
		* _numY = Number of groups Y.
		* _numZ = Number of groups Z.
		* _flags = Discard or preserve states. See `BGFX_DISCARD_*`.
		*/
		[q{void}, q{dispatch}, q{bgfx_view_id_t _id, bgfx_program_handle_t _program, uint _numX, uint _numY, uint _numZ, ubyte _flags}, `C++`],
		
		/**
		* Dispatch compute indirect.
		* Params:
		* _id = View id.
		* _program = Compute program.
		* _indirectHandle = Indirect buffer.
		* _start = First element in indirect buffer.
		* _num = Number of dispatches.
		* _flags = Discard or preserve states. See `BGFX_DISCARD_*`.
		*/
		[q{void}, q{dispatch}, q{bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_indirect_buffer_handle_t _indirectHandle, ushort _start, ushort _num, ubyte _flags}, `C++`],
		
		/**
		* Discard previously set state for draw or compute call.
		* Params:
		* _flags = Draw/compute states to discard.
		*/
		[q{void}, q{discard}, q{ubyte _flags}, `C++`],
		
		/**
		* Blit 2D texture region between two 2D textures.
		* Attention: Destination texture must be created with `BGFX_TEXTURE_BLIT_DST` flag.
		* Attention: Availability depends on: `BGFX_CAPS_TEXTURE_BLIT`.
		* Params:
		* _id = View id.
		* _dst = Destination texture handle.
		* _dstX = Destination texture X position.
		* _dstY = Destination texture Y position.
		* _src = Source texture handle.
		* _srcX = Source texture X position.
		* _srcY = Source texture Y position.
		* _width = Width of region.
		* _height = Height of region.
		*/
		[q{void}, q{blit}, q{bgfx_view_id_t _id, bgfx_texture_handle_t _dst, ushort _dstX, ushort _dstY, bgfx_texture_handle_t _src, ushort _srcX, ushort _srcY, ushort _width, ushort _height}, `C++`],
		
		/**
		* Blit 2D texture region between two 2D textures.
		* Attention: Destination texture must be created with `BGFX_TEXTURE_BLIT_DST` flag.
		* Attention: Availability depends on: `BGFX_CAPS_TEXTURE_BLIT`.
		* Params:
		* _id = View id.
		* _dst = Destination texture handle.
		* _dstMip = Destination texture mip level.
		* _dstX = Destination texture X position.
		* _dstY = Destination texture Y position.
		* _dstZ = If texture is 2D this argument should be 0. If destination texture is cube
		* this argument represents destination texture cube face. For 3D texture this argument
		* represents destination texture Z position.
		* _src = Source texture handle.
		* _srcMip = Source texture mip level.
		* _srcX = Source texture X position.
		* _srcY = Source texture Y position.
		* _srcZ = If texture is 2D this argument should be 0. If source texture is cube
		* this argument represents source texture cube face. For 3D texture this argument
		* represents source texture Z position.
		* _width = Width of region.
		* _height = Height of region.
		* _depth = If texture is 3D this argument represents depth of region, otherwise it's
		* unused.
		*/
		[q{void}, q{blit}, q{bgfx_view_id_t _id, bgfx_texture_handle_t _dst, ubyte _dstMip, ushort _dstX, ushort _dstY, ushort _dstZ, bgfx_texture_handle_t _src, ubyte _srcMip, ushort _srcX, ushort _srcY, ushort _srcZ, ushort _width, ushort _height, ushort _depth}, `C++`],
		
	]);
	return ret;
}()));

static if(!staticBinding):
import bindbc.loader;

mixin(makeDynloadFns("Bgfx", makeLibPaths(["bgfx", "bgfxRelease", "bgfxDebug"]), [__MODULE__]));
