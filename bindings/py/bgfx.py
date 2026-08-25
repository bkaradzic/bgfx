# Copyright 2011-2026 Branimir Karadzic. All rights reserved.
# License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE

#
# AUTO GENERATED! DO NOT EDIT!
#

import ctypes
import enum

ViewId = ctypes.c_uint16

class Fatal(enum.IntEnum):
	DebugCheck = 0
	InvalidShader = 1
	UnableToInitialize = 2
	UnableToCreateTexture = 3
	DeviceLost = 4
	Count = 5

class RendererType(enum.IntEnum):
	Noop = 0
	Agc = 1
	Direct3D11 = 2
	Direct3D12 = 3
	Gnm = 4
	Metal = 5
	Nvn = 6
	OpenGLES = 7
	OpenGL = 8
	Vulkan = 9
	WebGPU = 10
	Count = 11

class Access(enum.IntEnum):
	Read = 0
	Write = 1
	ReadWrite = 2
	Count = 3

class Attrib(enum.IntEnum):
	Position = 0
	Normal = 1
	Tangent = 2
	Bitangent = 3
	Color0 = 4
	Color1 = 5
	Color2 = 6
	Color3 = 7
	Indices = 8
	Weight = 9
	TexCoord0 = 10
	TexCoord1 = 11
	TexCoord2 = 12
	TexCoord3 = 13
	TexCoord4 = 14
	TexCoord5 = 15
	TexCoord6 = 16
	TexCoord7 = 17
	TexCoord8 = 18
	TexCoord9 = 19
	TexCoord10 = 20
	TexCoord11 = 21
	TexCoord12 = 22
	TexCoord13 = 23
	TexCoord14 = 24
	TexCoord15 = 25
	Count = 26

class AttribType(enum.IntEnum):
	Int8 = 0
	Uint8 = 1
	Uint10 = 2
	Int16 = 3
	Uint16 = 4
	Half = 5
	Float = 6
	Int32 = 7
	Uint32 = 8
	Count = 9

class TextureFormat(enum.IntEnum):
	BC1 = 0
	BC2 = 1
	BC3 = 2
	BC4 = 3
	BC4S = 4
	BC5 = 5
	BC5S = 6
	BC6H = 7
	BC6HU = 8
	BC7 = 9
	ETC1 = 10
	ETC2 = 11
	ETC2A = 12
	ETC2A1 = 13
	EACR11 = 14
	EACR11S = 15
	EACRG11 = 16
	EACRG11S = 17
	PTC12 = 18
	PTC14 = 19
	PTC12A = 20
	PTC14A = 21
	PTC22 = 22
	PTC24 = 23
	ATC = 24
	ATCE = 25
	ATCI = 26
	ASTC4x4 = 27
	ASTC5x4 = 28
	ASTC5x5 = 29
	ASTC6x5 = 30
	ASTC6x6 = 31
	ASTC8x5 = 32
	ASTC8x6 = 33
	ASTC8x8 = 34
	ASTC10x5 = 35
	ASTC10x6 = 36
	ASTC10x8 = 37
	ASTC10x10 = 38
	ASTC12x10 = 39
	ASTC12x12 = 40
	Unknown = 41
	R1 = 42
	A8 = 43
	R8 = 44
	R8I = 45
	R8U = 46
	R8S = 47
	R16 = 48
	R16I = 49
	R16U = 50
	R16F = 51
	R16S = 52
	R32I = 53
	R32U = 54
	R32F = 55
	RG8 = 56
	RG8I = 57
	RG8U = 58
	RG8S = 59
	RG16 = 60
	RG16I = 61
	RG16U = 62
	RG16F = 63
	RG16S = 64
	RG32I = 65
	RG32U = 66
	RG32F = 67
	RGB8 = 68
	RGB8I = 69
	RGB8U = 70
	RGB8S = 71
	RGB9E5F = 72
	BGRA8 = 73
	RGBA8 = 74
	RGBA8I = 75
	RGBA8U = 76
	RGBA8S = 77
	RGBA16 = 78
	RGBA16I = 79
	RGBA16U = 80
	RGBA16F = 81
	RGBA16S = 82
	RGBA32I = 83
	RGBA32U = 84
	RGBA32F = 85
	B5G6R5 = 86
	R5G6B5 = 87
	BGRA4 = 88
	RGBA4 = 89
	BGR5A1 = 90
	RGB5A1 = 91
	RGB10A2 = 92
	RGB10A2U = 93
	RG11B10F = 94
	UnknownDepth = 95
	D16 = 96
	D24 = 97
	D24S8 = 98
	D32 = 99
	D16F = 100
	D24F = 101
	D32F = 102
	D32FS8 = 103
	D0S8 = 104
	Count = 105

class UniformType(enum.IntEnum):
	Sampler = 0
	End = 1
	Vec4 = 2
	Mat3 = 3
	Mat4 = 4
	Count = 5

class UniformFreq(enum.IntEnum):
	Draw = 0
	View = 1
	Frame = 2
	Count = 3

class BackbufferRatio(enum.IntEnum):
	Equal = 0
	Half = 1
	Quarter = 2
	Eighth = 3
	Sixteenth = 4
	Double = 5
	Count = 6

class OcclusionQueryResult(enum.IntEnum):
	Invisible = 0
	Visible = 1
	NoResult = 2
	Count = 3

class VideoCodec(enum.IntEnum):
	H264 = 0
	H265 = 1
	AV1 = 2
	Count = 3

class Topology(enum.IntEnum):
	TriList = 0
	TriStrip = 1
	LineList = 2
	LineStrip = 3
	PointList = 4
	Count = 5

class TopologyConvert(enum.IntEnum):
	TriListFlipWinding = 0
	TriStripFlipWinding = 1
	TriListToLineList = 2
	TriStripToTriList = 3
	LineStripToLineList = 4
	Count = 5

class TopologySort(enum.IntEnum):
	DirectionFrontToBackMin = 0
	DirectionFrontToBackAvg = 1
	DirectionFrontToBackMax = 2
	DirectionBackToFrontMin = 3
	DirectionBackToFrontAvg = 4
	DirectionBackToFrontMax = 5
	DistanceFrontToBackMin = 6
	DistanceFrontToBackAvg = 7
	DistanceFrontToBackMax = 8
	DistanceBackToFrontMin = 9
	DistanceBackToFrontAvg = 10
	DistanceBackToFrontMax = 11
	Count = 12

class ViewMode(enum.IntEnum):
	Default = 0
	Sequential = 1
	DepthAscending = 2
	DepthDescending = 3
	Count = 4

class ShadingRate(enum.IntEnum):
	Rate1x1 = 0
	Rate1x2 = 1
	Rate2x1 = 2
	Rate2x2 = 3
	Rate2x4 = 4
	Rate4x2 = 5
	Rate4x4 = 6
	Count = 7

class NativeWindowHandleType(enum.IntEnum):
	Default = 0
	Wayland = 1
	Count = 2

class RenderFrame(enum.IntEnum):
	NoContext = 0
	Render = 1
	Timeout = 2
	Exiting = 3
	Count = 4

class StateFlags(enum.IntFlag):
	WriteR = 0x1
	WriteG = 0x2
	WriteB = 0x4
	WriteA = 0x8
	WriteZ = 0x4000000000
	WriteRgb = 0x7
	WriteMask = 0x400000000f
	DepthTestLess = 0x10
	DepthTestLequal = 0x20
	DepthTestEqual = 0x30
	DepthTestGequal = 0x40
	DepthTestGreater = 0x50
	DepthTestNotequal = 0x60
	DepthTestNever = 0x70
	DepthTestAlways = 0x80
	DepthTestShift = 0x4
	DepthTestMask = 0xf0
	BlendZero = 0x1000
	BlendOne = 0x2000
	BlendSrcColor = 0x3000
	BlendInvSrcColor = 0x4000
	BlendSrcAlpha = 0x5000
	BlendInvSrcAlpha = 0x6000
	BlendDstAlpha = 0x7000
	BlendInvDstAlpha = 0x8000
	BlendDstColor = 0x9000
	BlendInvDstColor = 0xa000
	BlendSrcAlphaSat = 0xb000
	BlendFactor = 0xc000
	BlendInvFactor = 0xd000
	BlendShift = 0xc
	BlendMask = 0xffff000
	BlendEquationAdd = 0x0
	BlendEquationSub = 0x10000000
	BlendEquationRevsub = 0x20000000
	BlendEquationMin = 0x30000000
	BlendEquationMax = 0x40000000
	BlendEquationShift = 0x1c
	BlendEquationMask = 0x3f0000000
	CullCw = 0x1000000000
	CullCcw = 0x2000000000
	CullShift = 0x24
	CullMask = 0x3000000000
	AlphaRefShift = 0x28
	AlphaRefMask = 0xff0000000000
	PtTristrip = 0x1000000000000
	PtLines = 0x2000000000000
	PtLinestrip = 0x3000000000000
	PtPoints = 0x4000000000000
	PtShift = 0x30
	PtMask = 0x7000000000000
	PointSizeShift = 0x34
	PointSizeMask = 0xf0000000000000
	Msaa = 0x100000000000000
	Lineaa = 0x200000000000000
	ConservativeRaster = 0x400000000000000
	None_ = 0x0
	FrontCcw = 0x8000000000
	BlendIndependent = 0x400000000
	BlendAlphaToCoverage = 0x800000000
	Default = 0x10000500000001f
	Mask = 0xffffffffffffffff
	ReservedShift = 0x3d
	ReservedMask = 0xe000000000000000

class StencilFlags(enum.IntFlag):
	FuncRefShift = 0x0
	FuncRefMask = 0xff
	FuncRmaskShift = 0x8
	FuncRmaskMask = 0xff00
	None_ = 0xff00
	Mask = 0xffffffff
	TestLess = 0x10000
	TestLequal = 0x20000
	TestEqual = 0x30000
	TestGequal = 0x40000
	TestGreater = 0x50000
	TestNotequal = 0x60000
	TestNever = 0x70000
	TestAlways = 0x80000
	TestShift = 0x10
	TestMask = 0xf0000
	OpFailSZero = 0x0
	OpFailSKeep = 0x100000
	OpFailSReplace = 0x200000
	OpFailSIncr = 0x300000
	OpFailSIncrsat = 0x400000
	OpFailSDecr = 0x500000
	OpFailSDecrsat = 0x600000
	OpFailSInvert = 0x700000
	OpFailSShift = 0x14
	OpFailSMask = 0xf00000
	OpFailZZero = 0x0
	OpFailZKeep = 0x1000000
	OpFailZReplace = 0x2000000
	OpFailZIncr = 0x3000000
	OpFailZIncrsat = 0x4000000
	OpFailZDecr = 0x5000000
	OpFailZDecrsat = 0x6000000
	OpFailZInvert = 0x7000000
	OpFailZShift = 0x18
	OpFailZMask = 0xf000000
	OpPassZZero = 0x0
	OpPassZKeep = 0x10000000
	OpPassZReplace = 0x20000000
	OpPassZIncr = 0x30000000
	OpPassZIncrsat = 0x40000000
	OpPassZDecr = 0x50000000
	OpPassZDecrsat = 0x60000000
	OpPassZInvert = 0x70000000
	OpPassZShift = 0x1c
	OpPassZMask = 0xf0000000

class BufferFlags(enum.IntFlag):
	None_ = 0x0
	ComputeRead = 0x100
	ComputeWrite = 0x200
	DrawIndirect = 0x400
	AllowResize = 0x800
	Index32 = 0x1000
	ComputeReadWrite = 0x300

class TextureFlags(enum.IntFlag):
	None_ = 0x0
	MsaaSample = 0x800000000
	Rt = 0x1000000000
	ComputeWrite = 0x100000000000
	Srgb = 0x200000000000
	BlitDst = 0x400000000000
	ReadBack = 0x800000000000
	ExternalShared = 0x1000000000000
	ReservedShift = 0x3c
	ReservedMask = 0xf000000000000000
	RtMsaaX2 = 0x2000000000
	RtMsaaX4 = 0x3000000000
	RtMsaaX8 = 0x4000000000
	RtMsaaX16 = 0x5000000000
	RtMsaaShift = 0x24
	RtMsaaMask = 0x7000000000
	RtWriteOnly = 0x8000000000
	RtShift = 0x24
	RtMask = 0xf000000000

class SamplerFlags(enum.IntFlag):
	UMirror = 0x1
	UClamp = 0x2
	UBorder = 0x3
	UShift = 0x0
	UMask = 0x3
	VMirror = 0x4
	VClamp = 0x8
	VBorder = 0xc
	VShift = 0x2
	VMask = 0xc
	WMirror = 0x10
	WClamp = 0x20
	WBorder = 0x30
	WShift = 0x4
	WMask = 0x30
	MinPoint = 0x40
	MinAnisotropic = 0x80
	MinShift = 0x6
	MinMask = 0xc0
	MagPoint = 0x100
	MagAnisotropic = 0x200
	MagShift = 0x8
	MagMask = 0x300
	MipPoint = 0x400
	MipShift = 0xa
	MipMask = 0x400
	CompareLess = 0x10000
	CompareLequal = 0x20000
	CompareEqual = 0x30000
	CompareGequal = 0x40000
	CompareGreater = 0x50000
	CompareNotequal = 0x60000
	CompareNever = 0x70000
	CompareAlways = 0x80000
	CompareShift = 0x10
	CompareMask = 0xf0000
	BorderColorShift = 0x18
	BorderColorMask = 0xf000000
	ReservedShift = 0x1c
	ReservedMask = 0xf0000000
	None_ = 0x0
	SampleStencil = 0x100000
	Point = 0x540
	UvwMirror = 0x15
	UvwClamp = 0x2a
	UvwBorder = 0x3f
	BitsMask = 0xf07ff

class ResetFlags(enum.IntFlag):
	MsaaX2 = 0x10
	MsaaX4 = 0x20
	MsaaX8 = 0x30
	MsaaX16 = 0x40
	MsaaShift = 0x4
	MsaaMask = 0x70
	None_ = 0x0
	Fullscreen = 0x1
	Vsync = 0x80
	Maxanisotropy = 0x100
	Capture = 0x200
	FlushAfterRender = 0x2000
	FlipAfterRender = 0x4000
	SrgbBackbuffer = 0x8000
	Hdr10 = 0x10000
	Hidpi = 0x20000
	DepthClamp = 0x40000
	Suspend = 0x80000
	TransparentBackbuffer = 0x100000
	FullscreenShift = 0x0
	FullscreenMask = 0x1
	ReservedShift = 0x1f
	ReservedMask = 0x80000000

class ClearFlags(enum.IntFlag):
	None_ = 0x0
	Color = 0x1
	Depth = 0x2
	Stencil = 0x4
	DiscardColor_0 = 0x8
	DiscardColor_1 = 0x10
	DiscardColor_2 = 0x20
	DiscardColor_3 = 0x40
	DiscardColor_4 = 0x80
	DiscardColor_5 = 0x100
	DiscardColor_6 = 0x200
	DiscardColor_7 = 0x400
	DiscardDepth = 0x800
	DiscardStencil = 0x1000
	DiscardColorMask = 0x7f8
	DiscardMask = 0x1ff8

class DiscardFlags(enum.IntFlag):
	None_ = 0x0
	Bindings = 0x1
	IndexBuffer = 0x2
	InstanceData = 0x4
	State = 0x8
	Transform = 0x10
	VertexStreams = 0x20
	All = 0xff

class DebugFlags(enum.IntFlag):
	None_ = 0x0
	Wireframe = 0x1
	Ifh = 0x2
	Stats = 0x4
	Text = 0x8
	Profiler = 0x10

class CapsFlags(enum.IntFlag):
	AlphaToCoverage = 0x1
	BlendIndependent = 0x2
	Compute = 0x4
	ConservativeRaster = 0x8
	DrawIndirect = 0x10
	DrawIndirectCount = 0x20
	FragmentDepth = 0x40
	FragmentOrdering = 0x80
	GraphicsDebugger = 0x100
	Hdr10 = 0x200
	Hidpi = 0x400
	ImageRw = 0x800
	Index32 = 0x1000
	Instancing = 0x2000
	OcclusionQuery = 0x4000
	PrimitiveId = 0x8000
	RendererMultithreaded = 0x10000
	SwapChain = 0x20000
	TextureBlit = 0x40000
	TextureCompareLequal = 0x80000
	TextureCompareReserved = 0x100000
	TextureCubeArray = 0x200000
	TextureDirectAccess = 0x400000
	TextureExternal = 0x800000
	TextureExternalShared = 0x1000000
	TextureReadBack = 0x2000000
	Texture_2dArray = 0x4000000
	Texture_3d = 0x8000000
	TransparentBackbuffer = 0x10000000
	VariableRateShading = 0x20000000
	VertexAttribHalf = 0x40000000
	VertexAttribUint10 = 0x80000000
	VertexId = 0x100000000
	VideoDecode = 0x200000000
	ViewportLayerArray = 0x400000000
	TextureCompareAll = 0x180000

class CapsFormatFlags(enum.IntFlag):
	TextureNone = 0x0
	Texture_2d = 0x1
	Texture_2dSrgb = 0x2
	Texture_2dEmulated = 0x4
	Texture_3d = 0x8
	Texture_3dSrgb = 0x10
	Texture_3dEmulated = 0x20
	TextureCube = 0x40
	TextureCubeSrgb = 0x80
	TextureCubeEmulated = 0x100
	TextureVertex = 0x200
	TextureImageRead = 0x400
	TextureImageWrite = 0x800
	TextureFramebuffer = 0x1000
	TextureFramebufferMsaa = 0x2000
	TextureMsaa = 0x4000
	TextureMipAutogen = 0x8000
	TextureBackbuffer = 0x10000
	TextureVideoDecodeDst = 0x20000

class CapsVideoCodecFlags(enum.IntFlag):
	None_ = 0x0
	Bit_8 = 0x1
	Bit_10 = 0x2
	Bit_12 = 0x4
	Chroma_420 = 0x8
	Chroma_422 = 0x10
	Chroma_444 = 0x20

class VideoDecoderInitFlags(enum.IntFlag):
	None_ = 0x0
	Retain = 0x1

class VideoDecodeFrameFlags(enum.IntFlag):
	None_ = 0x0
	Set = 0x1
	NoBlit = 0x2
	Final = 0x4
	Loop = 0x8

class ResolveFlags(enum.IntFlag):
	None_ = 0x0
	AutoGenMips = 0x1

class PciIdFlags(enum.IntFlag):
	None_ = 0x0
	SoftwareRasterizer = 0x1
	Amd = 0x1002
	Apple = 0x106b
	Intel = 0x8086
	Nvidia = 0x10de
	Microsoft = 0x1414
	Arm = 0x13b5

class CubeMapFlags(enum.IntFlag):
	PositiveX = 0x0
	NegativeX = 0x1
	PositiveY = 0x2
	NegativeY = 0x3
	PositiveZ = 0x4
	NegativeZ = 0x5

class FrameFlags(enum.IntFlag):
	None_ = 0x0
	DebugCapture = 0x1
	Discard = 0x2
	Flush = 0x4

class CapsGPU(ctypes.Structure):
	pass

class CapsLimits(ctypes.Structure):
	pass

class Caps(ctypes.Structure):
	pass

class InternalData(ctypes.Structure):
	pass

class PlatformData(ctypes.Structure):
	pass

class Resolution(ctypes.Structure):
	pass

class InitLimits(ctypes.Structure):
	pass

class Init(ctypes.Structure):
	pass

class Memory(ctypes.Structure):
	pass

class TransientIndexBuffer(ctypes.Structure):
	pass

class TransientVertexBuffer(ctypes.Structure):
	pass

class InstanceDataBuffer(ctypes.Structure):
	pass

class TextureRegion(ctypes.Structure):
	pass

class BufferRegion(ctypes.Structure):
	pass

class TextureInfo(ctypes.Structure):
	pass

class VideoDecoderInit(ctypes.Structure):
	pass

class VideoDecoderAu(ctypes.Structure):
	pass

class VideoDecoderFrame(ctypes.Structure):
	pass

class UniformInfo(ctypes.Structure):
	pass

class Attachment(ctypes.Structure):
	pass

class Transform(ctypes.Structure):
	pass

class ViewStats(ctypes.Structure):
	pass

class EncoderStats(ctypes.Structure):
	pass

class Stats(ctypes.Structure):
	pass

class VertexLayout(ctypes.Structure):
	pass

class Encoder(ctypes.Structure):
	pass

class DynamicIndexBufferHandle(ctypes.Structure):
	_fields_ = [("idx", ctypes.c_uint16)]

	@property
	def valid(self):
		return self.idx != 0xffff

class DynamicVertexBufferHandle(ctypes.Structure):
	_fields_ = [("idx", ctypes.c_uint16)]

	@property
	def valid(self):
		return self.idx != 0xffff

class FrameBufferHandle(ctypes.Structure):
	_fields_ = [("idx", ctypes.c_uint16)]

	@property
	def valid(self):
		return self.idx != 0xffff

class IndexBufferHandle(ctypes.Structure):
	_fields_ = [("idx", ctypes.c_uint16)]

	@property
	def valid(self):
		return self.idx != 0xffff

class IndirectBufferHandle(ctypes.Structure):
	_fields_ = [("idx", ctypes.c_uint16)]

	@property
	def valid(self):
		return self.idx != 0xffff

class OcclusionQueryHandle(ctypes.Structure):
	_fields_ = [("idx", ctypes.c_uint16)]

	@property
	def valid(self):
		return self.idx != 0xffff

class ProgramHandle(ctypes.Structure):
	_fields_ = [("idx", ctypes.c_uint16)]

	@property
	def valid(self):
		return self.idx != 0xffff

class ShaderHandle(ctypes.Structure):
	_fields_ = [("idx", ctypes.c_uint16)]

	@property
	def valid(self):
		return self.idx != 0xffff

class TextureHandle(ctypes.Structure):
	_fields_ = [("idx", ctypes.c_uint16)]

	@property
	def valid(self):
		return self.idx != 0xffff

class UniformHandle(ctypes.Structure):
	_fields_ = [("idx", ctypes.c_uint16)]

	@property
	def valid(self):
		return self.idx != 0xffff

class VertexBufferHandle(ctypes.Structure):
	_fields_ = [("idx", ctypes.c_uint16)]

	@property
	def valid(self):
		return self.idx != 0xffff

class VertexLayoutHandle(ctypes.Structure):
	_fields_ = [("idx", ctypes.c_uint16)]

	@property
	def valid(self):
		return self.idx != 0xffff

class BufferHandle(ctypes.Structure):
	_fields_ = [("idx", ctypes.c_uint16), ("type", ctypes.c_uint16)]

	@property
	def valid(self):
		return self.idx != 0xffff

ReleaseFn = ctypes.CFUNCTYPE(None, ctypes.c_void_p, ctypes.c_void_p)

CapsGPU._fields_ = [
	("vendorId", ctypes.c_uint16),
	("deviceId", ctypes.c_uint16),
]

CapsLimits._fields_ = [
	("maxDrawCalls", ctypes.c_uint32),
	("maxBlits", ctypes.c_uint32),
	("maxTextureSize", ctypes.c_uint32),
	("maxTextureLayers", ctypes.c_uint32),
	("maxViews", ctypes.c_uint32),
	("maxFrameBuffers", ctypes.c_uint32),
	("maxFBAttachments", ctypes.c_uint32),
	("maxPrograms", ctypes.c_uint32),
	("maxShaders", ctypes.c_uint32),
	("maxTextures", ctypes.c_uint32),
	("maxTextureSamplers", ctypes.c_uint32),
	("maxComputeBindings", ctypes.c_uint32),
	("maxVertexLayouts", ctypes.c_uint32),
	("maxVertexStreams", ctypes.c_uint32),
	("maxVertexAttributes", ctypes.c_uint32),
	("maxInstanceData", ctypes.c_uint32),
	("maxIndexBuffers", ctypes.c_uint32),
	("maxVertexBuffers", ctypes.c_uint32),
	("maxDynamicIndexBuffers", ctypes.c_uint32),
	("maxDynamicVertexBuffers", ctypes.c_uint32),
	("maxUniforms", ctypes.c_uint32),
	("maxOcclusionQueries", ctypes.c_uint32),
	("maxEncoders", ctypes.c_uint32),
	("minResourceCbSize", ctypes.c_uint32),
	("maxTransientVbSize", ctypes.c_uint32),
	("maxTransientIbSize", ctypes.c_uint32),
	("minUniformBufferSize", ctypes.c_uint32),
	("blitRowPitchAlign", ctypes.c_uint32),
	("blitOffsetAlign", ctypes.c_uint32),
]

Caps._fields_ = [
	("rendererType", ctypes.c_int),
	("supported", ctypes.c_uint64),
	("vendorId", ctypes.c_uint16),
	("deviceId", ctypes.c_uint16),
	("homogeneousDepth", ctypes.c_bool),
	("originBottomLeft", ctypes.c_bool),
	("numGPUs", ctypes.c_uint8),
	("gpu", (CapsGPU * 4)),
	("limits", CapsLimits),
	("formats", (ctypes.c_uint32 * 105)),
	("codecs", (ctypes.c_uint32 * 3)),
]

InternalData._fields_ = [
	("caps", ctypes.POINTER(Caps)),
	("context", ctypes.c_void_p),
]

PlatformData._fields_ = [
	("ndt", ctypes.c_void_p),
	("nwh", ctypes.c_void_p),
	("context", ctypes.c_void_p),
	("queue", ctypes.c_void_p),
	("backBuffer", ctypes.c_void_p),
	("backBufferDS", ctypes.c_void_p),
	("type", ctypes.c_int),
]

Resolution._fields_ = [
	("formatColor", ctypes.c_int),
	("formatDepthStencil", ctypes.c_int),
	("width", ctypes.c_uint32),
	("height", ctypes.c_uint32),
	("reset", ctypes.c_uint32),
	("numBackBuffers", ctypes.c_uint8),
	("maxFrameLatency", ctypes.c_uint8),
	("debugTextScale", ctypes.c_uint8),
]

InitLimits._fields_ = [
	("maxEncoders", ctypes.c_uint16),
	("numDrawCalls", ctypes.c_uint32),
	("numDrawCallPeakFrames", ctypes.c_uint32),
	("minResourceCbSize", ctypes.c_uint32),
	("maxTransientVbSize", ctypes.c_uint32),
	("maxTransientIbSize", ctypes.c_uint32),
	("minUniformBufferSize", ctypes.c_uint32),
]

Init._fields_ = [
	("type", ctypes.c_int),
	("vendorId", ctypes.c_uint16),
	("deviceId", ctypes.c_uint16),
	("capabilities", ctypes.c_uint64),
	("debug", ctypes.c_bool),
	("profile", ctypes.c_bool),
	("fallback", ctypes.c_bool),
	("videoDecode", ctypes.c_bool),
	("platformData", PlatformData),
	("resolution", Resolution),
	("limits", InitLimits),
	("callback", ctypes.c_void_p),
	("allocator", ctypes.c_void_p),
]

Memory._fields_ = [
	("data", ctypes.POINTER(ctypes.c_uint8)),
	("size", ctypes.c_uint32),
]

TransientIndexBuffer._fields_ = [
	("data", ctypes.POINTER(ctypes.c_uint8)),
	("size", ctypes.c_uint32),
	("startIndex", ctypes.c_uint32),
	("handle", IndexBufferHandle),
	("isIndex16", ctypes.c_bool),
]

TransientVertexBuffer._fields_ = [
	("data", ctypes.POINTER(ctypes.c_uint8)),
	("size", ctypes.c_uint32),
	("startVertex", ctypes.c_uint32),
	("stride", ctypes.c_uint16),
	("handle", VertexBufferHandle),
	("layoutHandle", VertexLayoutHandle),
]

InstanceDataBuffer._fields_ = [
	("data", ctypes.POINTER(ctypes.c_uint8)),
	("size", ctypes.c_uint32),
	("offset", ctypes.c_uint32),
	("num", ctypes.c_uint32),
	("stride", ctypes.c_uint16),
	("handle", VertexBufferHandle),
]

TextureRegion._fields_ = [
	("handle", TextureHandle),
	("mip", ctypes.c_uint8),
	("x", ctypes.c_uint16),
	("y", ctypes.c_uint16),
	("z", ctypes.c_uint16),
	("width", ctypes.c_uint16),
	("height", ctypes.c_uint16),
	("depth", ctypes.c_uint16),
]

BufferRegion._fields_ = [
	("handle", BufferHandle),
	("offset", ctypes.c_uint32),
	("size", ctypes.c_uint32),
	("rowPitch", ctypes.c_uint32),
	("slicePitch", ctypes.c_uint32),
]

TextureInfo._fields_ = [
	("format", ctypes.c_int),
	("storageSize", ctypes.c_uint32),
	("width", ctypes.c_uint16),
	("height", ctypes.c_uint16),
	("depth", ctypes.c_uint16),
	("numLayers", ctypes.c_uint16),
	("numMips", ctypes.c_uint8),
	("bitsPerPixel", ctypes.c_uint8),
	("cubeMap", ctypes.c_bool),
]

VideoDecoderInit._fields_ = [
	("magic", ctypes.c_uint32),
	("codec", ctypes.c_int),
	("parameterSets", ctypes.POINTER(ctypes.c_uint8)),
	("parameterSetsSize", ctypes.c_uint32),
	("cachedAuBytes", ctypes.c_uint32),
	("flags", ctypes.c_uint8),
]

VideoDecoderAu._fields_ = [
	("size", ctypes.c_uint32),
	("ptsUs", ctypes.c_int64),
]

VideoDecoderFrame._fields_ = [
	("magic", ctypes.c_uint32),
	("bitstream", ctypes.POINTER(ctypes.c_uint8)),
	("aus", ctypes.POINTER(VideoDecoderAu)),
	("numAus", ctypes.c_uint32),
	("presentationTimeUs", ctypes.c_int64),
	("flags", ctypes.c_uint8),
]

UniformInfo._fields_ = [
	("name", (ctypes.c_char * 256)),
	("type", ctypes.c_int),
	("num", ctypes.c_uint16),
]

Attachment._fields_ = [
	("access", ctypes.c_int),
	("handle", TextureHandle),
	("mip", ctypes.c_uint16),
	("layer", ctypes.c_uint16),
	("numLayers", ctypes.c_uint16),
	("resolve", ctypes.c_uint8),
]

Transform._fields_ = [
	("data", ctypes.POINTER(ctypes.c_float)),
	("num", ctypes.c_uint16),
]

ViewStats._fields_ = [
	("name", (ctypes.c_char * 256)),
	("view", ctypes.c_uint16),
	("cpuTimeBegin", ctypes.c_int64),
	("cpuTimeEnd", ctypes.c_int64),
	("gpuTimeBegin", ctypes.c_int64),
	("gpuTimeEnd", ctypes.c_int64),
	("gpuFrameNum", ctypes.c_uint32),
]

EncoderStats._fields_ = [
	("cpuTimeBegin", ctypes.c_int64),
	("cpuTimeEnd", ctypes.c_int64),
]

Stats._fields_ = [
	("cpuTimeFrame", ctypes.c_int64),
	("cpuTimeBegin", ctypes.c_int64),
	("cpuTimeEnd", ctypes.c_int64),
	("cpuTimerFreq", ctypes.c_int64),
	("gpuTimeBegin", ctypes.c_int64),
	("gpuTimeEnd", ctypes.c_int64),
	("gpuTimerFreq", ctypes.c_int64),
	("waitRender", ctypes.c_int64),
	("waitSubmit", ctypes.c_int64),
	("numDraw", ctypes.c_uint32),
	("numCompute", ctypes.c_uint32),
	("numBlit", ctypes.c_uint32),
	("numBlitRepack", ctypes.c_uint32),
	("numDrawCallsPeak", ctypes.c_uint32),
	("maxGpuLatency", ctypes.c_uint32),
	("gpuFrameNum", ctypes.c_uint32),
	("numDynamicIndexBuffers", ctypes.c_uint16),
	("numDynamicVertexBuffers", ctypes.c_uint16),
	("numFrameBuffers", ctypes.c_uint16),
	("numIndexBuffers", ctypes.c_uint16),
	("numOcclusionQueries", ctypes.c_uint16),
	("numPrograms", ctypes.c_uint16),
	("numShaders", ctypes.c_uint16),
	("numTextures", ctypes.c_uint16),
	("numUniforms", ctypes.c_uint16),
	("numVertexBuffers", ctypes.c_uint16),
	("numVertexLayouts", ctypes.c_uint16),
	("textureMemoryUsed", ctypes.c_int64),
	("rtMemoryUsed", ctypes.c_int64),
	("transientVbUsed", ctypes.c_int32),
	("transientIbUsed", ctypes.c_int32),
	("numPrims", (ctypes.c_uint32 * 5)),
	("gpuMemoryMax", ctypes.c_int64),
	("gpuMemoryUsed", ctypes.c_int64),
	("width", ctypes.c_uint16),
	("height", ctypes.c_uint16),
	("textWidth", ctypes.c_uint16),
	("textHeight", ctypes.c_uint16),
	("numViews", ctypes.c_uint16),
	("viewStats", ctypes.POINTER(ViewStats)),
	("numEncoders", ctypes.c_uint8),
	("encoderStats", ctypes.POINTER(EncoderStats)),
]

VertexLayout._fields_ = [
	("hash", ctypes.c_uint32),
	("stride", ctypes.c_uint16),
	("offset", (ctypes.c_uint16 * 26)),
	("attributes", (ctypes.c_uint16 * 26)),
]

_lib = None

def load(path):
	global _lib
	_lib = ctypes.CDLL(path)
	_bind(_lib)
	return _lib

def _bind(lib):
	global bgfx_texture_region_init
	bgfx_texture_region_init = lib.bgfx_texture_region_init
	bgfx_texture_region_init.argtypes = [ctypes.POINTER(TextureRegion), TextureHandle, ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint16]
	bgfx_texture_region_init.restype = None
	global bgfx_buffer_region_init_texture
	bgfx_buffer_region_init_texture = lib.bgfx_buffer_region_init_texture
	bgfx_buffer_region_init_texture.argtypes = [ctypes.POINTER(BufferRegion), ctypes.POINTER(TextureRegion)]
	bgfx_buffer_region_init_texture.restype = None
	global bgfx_buffer_region_init_buffer
	bgfx_buffer_region_init_buffer = lib.bgfx_buffer_region_init_buffer
	bgfx_buffer_region_init_buffer.argtypes = [ctypes.POINTER(BufferRegion), BufferHandle, ctypes.c_uint32, ctypes.c_uint32]
	bgfx_buffer_region_init_buffer.restype = None
	global bgfx_attachment_init
	bgfx_attachment_init = lib.bgfx_attachment_init
	bgfx_attachment_init.argtypes = [ctypes.POINTER(Attachment), TextureHandle, ctypes.c_int, ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint8]
	bgfx_attachment_init.restype = None
	global bgfx_vertex_layout_begin
	bgfx_vertex_layout_begin = lib.bgfx_vertex_layout_begin
	bgfx_vertex_layout_begin.argtypes = [ctypes.POINTER(VertexLayout), ctypes.c_int]
	bgfx_vertex_layout_begin.restype = ctypes.POINTER(VertexLayout)
	global bgfx_vertex_layout_add
	bgfx_vertex_layout_add = lib.bgfx_vertex_layout_add
	bgfx_vertex_layout_add.argtypes = [ctypes.POINTER(VertexLayout), ctypes.c_int, ctypes.c_uint8, ctypes.c_int, ctypes.c_bool, ctypes.c_bool]
	bgfx_vertex_layout_add.restype = ctypes.POINTER(VertexLayout)
	global bgfx_vertex_layout_decode
	bgfx_vertex_layout_decode = lib.bgfx_vertex_layout_decode
	bgfx_vertex_layout_decode.argtypes = [ctypes.POINTER(VertexLayout), ctypes.c_int, ctypes.POINTER(ctypes.c_uint8), ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_bool), ctypes.POINTER(ctypes.c_bool)]
	bgfx_vertex_layout_decode.restype = None
	global bgfx_vertex_layout_skip
	bgfx_vertex_layout_skip = lib.bgfx_vertex_layout_skip
	bgfx_vertex_layout_skip.argtypes = [ctypes.POINTER(VertexLayout), ctypes.c_uint8]
	bgfx_vertex_layout_skip.restype = ctypes.POINTER(VertexLayout)
	global bgfx_vertex_layout_end
	bgfx_vertex_layout_end = lib.bgfx_vertex_layout_end
	bgfx_vertex_layout_end.argtypes = [ctypes.POINTER(VertexLayout)]
	bgfx_vertex_layout_end.restype = None
	global bgfx_vertex_pack
	bgfx_vertex_pack = lib.bgfx_vertex_pack
	bgfx_vertex_pack.argtypes = [ctypes.POINTER(ctypes.c_float), ctypes.c_bool, ctypes.c_int, ctypes.POINTER(VertexLayout), ctypes.c_void_p, ctypes.c_uint32]
	bgfx_vertex_pack.restype = None
	global bgfx_vertex_unpack
	bgfx_vertex_unpack = lib.bgfx_vertex_unpack
	bgfx_vertex_unpack.argtypes = [ctypes.POINTER(ctypes.c_float), ctypes.c_int, ctypes.POINTER(VertexLayout), ctypes.c_void_p, ctypes.c_uint32]
	bgfx_vertex_unpack.restype = None
	global bgfx_vertex_convert
	bgfx_vertex_convert = lib.bgfx_vertex_convert
	bgfx_vertex_convert.argtypes = [ctypes.POINTER(VertexLayout), ctypes.c_void_p, ctypes.POINTER(VertexLayout), ctypes.c_void_p, ctypes.c_uint32]
	bgfx_vertex_convert.restype = None
	global bgfx_topology_convert
	bgfx_topology_convert = lib.bgfx_topology_convert
	bgfx_topology_convert.argtypes = [ctypes.c_int, ctypes.c_void_p, ctypes.c_uint32, ctypes.c_void_p, ctypes.c_uint32, ctypes.c_bool]
	bgfx_topology_convert.restype = ctypes.c_uint32
	global bgfx_topology_sort_tri_list
	bgfx_topology_sort_tri_list = lib.bgfx_topology_sort_tri_list
	bgfx_topology_sort_tri_list.argtypes = [ctypes.c_int, ctypes.c_void_p, ctypes.c_uint32, ctypes.POINTER(ctypes.c_float), ctypes.POINTER(ctypes.c_float), ctypes.c_void_p, ctypes.c_uint32, ctypes.c_void_p, ctypes.c_uint32, ctypes.c_bool]
	bgfx_topology_sort_tri_list.restype = None
	global bgfx_get_supported_renderers
	bgfx_get_supported_renderers = lib.bgfx_get_supported_renderers
	bgfx_get_supported_renderers.argtypes = [ctypes.c_uint8, ctypes.POINTER(ctypes.c_int)]
	bgfx_get_supported_renderers.restype = ctypes.c_uint8
	global bgfx_get_renderer_name
	bgfx_get_renderer_name = lib.bgfx_get_renderer_name
	bgfx_get_renderer_name.argtypes = [ctypes.c_int]
	bgfx_get_renderer_name.restype = ctypes.c_char_p
	global bgfx_init_ctor
	bgfx_init_ctor = lib.bgfx_init_ctor
	bgfx_init_ctor.argtypes = [ctypes.POINTER(Init)]
	bgfx_init_ctor.restype = None
	global bgfx_init
	bgfx_init = lib.bgfx_init
	bgfx_init.argtypes = [ctypes.POINTER(Init)]
	bgfx_init.restype = ctypes.c_bool
	global bgfx_shutdown
	bgfx_shutdown = lib.bgfx_shutdown
	bgfx_shutdown.argtypes = []
	bgfx_shutdown.restype = None
	global bgfx_reset
	bgfx_reset = lib.bgfx_reset
	bgfx_reset.argtypes = [ctypes.c_uint32, ctypes.c_uint32, ctypes.c_uint32, ctypes.c_int]
	bgfx_reset.restype = None
	global bgfx_frame
	bgfx_frame = lib.bgfx_frame
	bgfx_frame.argtypes = [ctypes.c_uint8]
	bgfx_frame.restype = ctypes.c_uint32
	global bgfx_get_renderer_type
	bgfx_get_renderer_type = lib.bgfx_get_renderer_type
	bgfx_get_renderer_type.argtypes = []
	bgfx_get_renderer_type.restype = ctypes.c_int
	global bgfx_get_caps
	bgfx_get_caps = lib.bgfx_get_caps
	bgfx_get_caps.argtypes = []
	bgfx_get_caps.restype = ctypes.POINTER(Caps)
	global bgfx_get_stats
	bgfx_get_stats = lib.bgfx_get_stats
	bgfx_get_stats.argtypes = []
	bgfx_get_stats.restype = ctypes.POINTER(Stats)
	global bgfx_alloc
	bgfx_alloc = lib.bgfx_alloc
	bgfx_alloc.argtypes = [ctypes.c_uint32]
	bgfx_alloc.restype = ctypes.POINTER(Memory)
	global bgfx_copy
	bgfx_copy = lib.bgfx_copy
	bgfx_copy.argtypes = [ctypes.c_void_p, ctypes.c_uint32]
	bgfx_copy.restype = ctypes.POINTER(Memory)
	global bgfx_make_ref
	bgfx_make_ref = lib.bgfx_make_ref
	bgfx_make_ref.argtypes = [ctypes.c_void_p, ctypes.c_uint32]
	bgfx_make_ref.restype = ctypes.POINTER(Memory)
	global bgfx_make_ref_release
	bgfx_make_ref_release = lib.bgfx_make_ref_release
	bgfx_make_ref_release.argtypes = [ctypes.c_void_p, ctypes.c_uint32, ReleaseFn, ctypes.c_void_p]
	bgfx_make_ref_release.restype = ctypes.POINTER(Memory)
	global bgfx_set_debug
	bgfx_set_debug = lib.bgfx_set_debug
	bgfx_set_debug.argtypes = [ctypes.c_uint32]
	bgfx_set_debug.restype = None
	global bgfx_dbg_text_clear
	bgfx_dbg_text_clear = lib.bgfx_dbg_text_clear
	bgfx_dbg_text_clear.argtypes = [ctypes.c_uint8, ctypes.c_bool]
	bgfx_dbg_text_clear.restype = None
	global bgfx_dbg_text_vprintf
	bgfx_dbg_text_vprintf = lib.bgfx_dbg_text_vprintf
	bgfx_dbg_text_vprintf.argtypes = [ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint8, ctypes.c_char_p, ctypes.c_void_p]
	bgfx_dbg_text_vprintf.restype = None
	global bgfx_dbg_text_image
	bgfx_dbg_text_image = lib.bgfx_dbg_text_image
	bgfx_dbg_text_image.argtypes = [ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint16, ctypes.c_void_p, ctypes.c_uint16]
	bgfx_dbg_text_image.restype = None
	global bgfx_create_index_buffer
	bgfx_create_index_buffer = lib.bgfx_create_index_buffer
	bgfx_create_index_buffer.argtypes = [ctypes.POINTER(Memory), ctypes.c_uint16]
	bgfx_create_index_buffer.restype = IndexBufferHandle
	global bgfx_read_buffer
	bgfx_read_buffer = lib.bgfx_read_buffer
	bgfx_read_buffer.argtypes = [ctypes.POINTER(BufferRegion), ctypes.c_void_p]
	bgfx_read_buffer.restype = ctypes.c_uint32
	global bgfx_set_index_buffer_name
	bgfx_set_index_buffer_name = lib.bgfx_set_index_buffer_name
	bgfx_set_index_buffer_name.argtypes = [IndexBufferHandle, ctypes.c_char_p, ctypes.c_int32]
	bgfx_set_index_buffer_name.restype = None
	global bgfx_destroy_index_buffer
	bgfx_destroy_index_buffer = lib.bgfx_destroy_index_buffer
	bgfx_destroy_index_buffer.argtypes = [IndexBufferHandle]
	bgfx_destroy_index_buffer.restype = None
	global bgfx_create_vertex_layout
	bgfx_create_vertex_layout = lib.bgfx_create_vertex_layout
	bgfx_create_vertex_layout.argtypes = [ctypes.POINTER(VertexLayout)]
	bgfx_create_vertex_layout.restype = VertexLayoutHandle
	global bgfx_destroy_vertex_layout
	bgfx_destroy_vertex_layout = lib.bgfx_destroy_vertex_layout
	bgfx_destroy_vertex_layout.argtypes = [VertexLayoutHandle]
	bgfx_destroy_vertex_layout.restype = None
	global bgfx_create_vertex_buffer
	bgfx_create_vertex_buffer = lib.bgfx_create_vertex_buffer
	bgfx_create_vertex_buffer.argtypes = [ctypes.POINTER(Memory), ctypes.POINTER(VertexLayout), ctypes.c_uint16]
	bgfx_create_vertex_buffer.restype = VertexBufferHandle
	global bgfx_set_vertex_buffer_name
	bgfx_set_vertex_buffer_name = lib.bgfx_set_vertex_buffer_name
	bgfx_set_vertex_buffer_name.argtypes = [VertexBufferHandle, ctypes.c_char_p, ctypes.c_int32]
	bgfx_set_vertex_buffer_name.restype = None
	global bgfx_destroy_vertex_buffer
	bgfx_destroy_vertex_buffer = lib.bgfx_destroy_vertex_buffer
	bgfx_destroy_vertex_buffer.argtypes = [VertexBufferHandle]
	bgfx_destroy_vertex_buffer.restype = None
	global bgfx_create_dynamic_index_buffer
	bgfx_create_dynamic_index_buffer = lib.bgfx_create_dynamic_index_buffer
	bgfx_create_dynamic_index_buffer.argtypes = [ctypes.c_uint32, ctypes.c_uint16]
	bgfx_create_dynamic_index_buffer.restype = DynamicIndexBufferHandle
	global bgfx_create_dynamic_index_buffer_mem
	bgfx_create_dynamic_index_buffer_mem = lib.bgfx_create_dynamic_index_buffer_mem
	bgfx_create_dynamic_index_buffer_mem.argtypes = [ctypes.POINTER(Memory), ctypes.c_uint16]
	bgfx_create_dynamic_index_buffer_mem.restype = DynamicIndexBufferHandle
	global bgfx_update_dynamic_index_buffer
	bgfx_update_dynamic_index_buffer = lib.bgfx_update_dynamic_index_buffer
	bgfx_update_dynamic_index_buffer.argtypes = [DynamicIndexBufferHandle, ctypes.c_uint32, ctypes.POINTER(Memory)]
	bgfx_update_dynamic_index_buffer.restype = None
	global bgfx_destroy_dynamic_index_buffer
	bgfx_destroy_dynamic_index_buffer = lib.bgfx_destroy_dynamic_index_buffer
	bgfx_destroy_dynamic_index_buffer.argtypes = [DynamicIndexBufferHandle]
	bgfx_destroy_dynamic_index_buffer.restype = None
	global bgfx_create_dynamic_vertex_buffer
	bgfx_create_dynamic_vertex_buffer = lib.bgfx_create_dynamic_vertex_buffer
	bgfx_create_dynamic_vertex_buffer.argtypes = [ctypes.c_uint32, ctypes.POINTER(VertexLayout), ctypes.c_uint16]
	bgfx_create_dynamic_vertex_buffer.restype = DynamicVertexBufferHandle
	global bgfx_create_dynamic_vertex_buffer_mem
	bgfx_create_dynamic_vertex_buffer_mem = lib.bgfx_create_dynamic_vertex_buffer_mem
	bgfx_create_dynamic_vertex_buffer_mem.argtypes = [ctypes.POINTER(Memory), ctypes.POINTER(VertexLayout), ctypes.c_uint16]
	bgfx_create_dynamic_vertex_buffer_mem.restype = DynamicVertexBufferHandle
	global bgfx_update_dynamic_vertex_buffer
	bgfx_update_dynamic_vertex_buffer = lib.bgfx_update_dynamic_vertex_buffer
	bgfx_update_dynamic_vertex_buffer.argtypes = [DynamicVertexBufferHandle, ctypes.c_uint32, ctypes.POINTER(Memory)]
	bgfx_update_dynamic_vertex_buffer.restype = None
	global bgfx_destroy_dynamic_vertex_buffer
	bgfx_destroy_dynamic_vertex_buffer = lib.bgfx_destroy_dynamic_vertex_buffer
	bgfx_destroy_dynamic_vertex_buffer.argtypes = [DynamicVertexBufferHandle]
	bgfx_destroy_dynamic_vertex_buffer.restype = None
	global bgfx_get_avail_transient_index_buffer
	bgfx_get_avail_transient_index_buffer = lib.bgfx_get_avail_transient_index_buffer
	bgfx_get_avail_transient_index_buffer.argtypes = [ctypes.c_uint32, ctypes.c_bool]
	bgfx_get_avail_transient_index_buffer.restype = ctypes.c_uint32
	global bgfx_get_avail_transient_vertex_buffer
	bgfx_get_avail_transient_vertex_buffer = lib.bgfx_get_avail_transient_vertex_buffer
	bgfx_get_avail_transient_vertex_buffer.argtypes = [ctypes.c_uint32, ctypes.POINTER(VertexLayout)]
	bgfx_get_avail_transient_vertex_buffer.restype = ctypes.c_uint32
	global bgfx_get_avail_instance_data_buffer
	bgfx_get_avail_instance_data_buffer = lib.bgfx_get_avail_instance_data_buffer
	bgfx_get_avail_instance_data_buffer.argtypes = [ctypes.c_uint32, ctypes.c_uint16]
	bgfx_get_avail_instance_data_buffer.restype = ctypes.c_uint32
	global bgfx_alloc_transient_index_buffer
	bgfx_alloc_transient_index_buffer = lib.bgfx_alloc_transient_index_buffer
	bgfx_alloc_transient_index_buffer.argtypes = [ctypes.POINTER(TransientIndexBuffer), ctypes.c_uint32, ctypes.c_bool]
	bgfx_alloc_transient_index_buffer.restype = None
	global bgfx_alloc_transient_vertex_buffer
	bgfx_alloc_transient_vertex_buffer = lib.bgfx_alloc_transient_vertex_buffer
	bgfx_alloc_transient_vertex_buffer.argtypes = [ctypes.POINTER(TransientVertexBuffer), ctypes.c_uint32, ctypes.POINTER(VertexLayout)]
	bgfx_alloc_transient_vertex_buffer.restype = None
	global bgfx_alloc_transient_buffers
	bgfx_alloc_transient_buffers = lib.bgfx_alloc_transient_buffers
	bgfx_alloc_transient_buffers.argtypes = [ctypes.POINTER(TransientVertexBuffer), ctypes.POINTER(VertexLayout), ctypes.c_uint32, ctypes.POINTER(TransientIndexBuffer), ctypes.c_uint32, ctypes.c_bool]
	bgfx_alloc_transient_buffers.restype = ctypes.c_bool
	global bgfx_alloc_instance_data_buffer
	bgfx_alloc_instance_data_buffer = lib.bgfx_alloc_instance_data_buffer
	bgfx_alloc_instance_data_buffer.argtypes = [ctypes.POINTER(InstanceDataBuffer), ctypes.c_uint32, ctypes.c_uint16]
	bgfx_alloc_instance_data_buffer.restype = None
	global bgfx_create_indirect_buffer
	bgfx_create_indirect_buffer = lib.bgfx_create_indirect_buffer
	bgfx_create_indirect_buffer.argtypes = [ctypes.c_uint32]
	bgfx_create_indirect_buffer.restype = IndirectBufferHandle
	global bgfx_destroy_indirect_buffer
	bgfx_destroy_indirect_buffer = lib.bgfx_destroy_indirect_buffer
	bgfx_destroy_indirect_buffer.argtypes = [IndirectBufferHandle]
	bgfx_destroy_indirect_buffer.restype = None
	global bgfx_create_shader
	bgfx_create_shader = lib.bgfx_create_shader
	bgfx_create_shader.argtypes = [ctypes.POINTER(Memory)]
	bgfx_create_shader.restype = ShaderHandle
	global bgfx_get_shader_uniforms
	bgfx_get_shader_uniforms = lib.bgfx_get_shader_uniforms
	bgfx_get_shader_uniforms.argtypes = [ShaderHandle, ctypes.POINTER(UniformHandle), ctypes.c_uint16]
	bgfx_get_shader_uniforms.restype = ctypes.c_uint16
	global bgfx_set_shader_name
	bgfx_set_shader_name = lib.bgfx_set_shader_name
	bgfx_set_shader_name.argtypes = [ShaderHandle, ctypes.c_char_p, ctypes.c_int32]
	bgfx_set_shader_name.restype = None
	global bgfx_destroy_shader
	bgfx_destroy_shader = lib.bgfx_destroy_shader
	bgfx_destroy_shader.argtypes = [ShaderHandle]
	bgfx_destroy_shader.restype = None
	global bgfx_create_program
	bgfx_create_program = lib.bgfx_create_program
	bgfx_create_program.argtypes = [ShaderHandle, ShaderHandle, ctypes.c_bool]
	bgfx_create_program.restype = ProgramHandle
	global bgfx_create_compute_program
	bgfx_create_compute_program = lib.bgfx_create_compute_program
	bgfx_create_compute_program.argtypes = [ShaderHandle, ctypes.c_bool]
	bgfx_create_compute_program.restype = ProgramHandle
	global bgfx_destroy_program
	bgfx_destroy_program = lib.bgfx_destroy_program
	bgfx_destroy_program.argtypes = [ProgramHandle]
	bgfx_destroy_program.restype = None
	global bgfx_is_texture_valid
	bgfx_is_texture_valid = lib.bgfx_is_texture_valid
	bgfx_is_texture_valid.argtypes = [ctypes.c_uint16, ctypes.c_bool, ctypes.c_uint16, ctypes.c_int, ctypes.c_uint64]
	bgfx_is_texture_valid.restype = ctypes.c_bool
	global bgfx_is_video_codec_valid
	bgfx_is_video_codec_valid = lib.bgfx_is_video_codec_valid
	bgfx_is_video_codec_valid.argtypes = [ctypes.c_int, ctypes.c_uint8, ctypes.c_uint8, ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint8, ctypes.c_uint8]
	bgfx_is_video_codec_valid.restype = ctypes.c_bool
	global bgfx_is_frame_buffer_valid
	bgfx_is_frame_buffer_valid = lib.bgfx_is_frame_buffer_valid
	bgfx_is_frame_buffer_valid.argtypes = [ctypes.c_uint8, ctypes.POINTER(Attachment)]
	bgfx_is_frame_buffer_valid.restype = ctypes.c_bool
	global bgfx_calc_texture_size
	bgfx_calc_texture_size = lib.bgfx_calc_texture_size
	bgfx_calc_texture_size.argtypes = [ctypes.POINTER(TextureInfo), ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint16, ctypes.c_bool, ctypes.c_bool, ctypes.c_uint16, ctypes.c_int]
	bgfx_calc_texture_size.restype = None
	global bgfx_create_texture
	bgfx_create_texture = lib.bgfx_create_texture
	bgfx_create_texture.argtypes = [ctypes.POINTER(Memory), ctypes.c_uint64, ctypes.c_uint8, ctypes.POINTER(TextureInfo)]
	bgfx_create_texture.restype = TextureHandle
	global bgfx_create_texture_2d
	bgfx_create_texture_2d = lib.bgfx_create_texture_2d
	bgfx_create_texture_2d.argtypes = [ctypes.c_uint16, ctypes.c_uint16, ctypes.c_bool, ctypes.c_uint16, ctypes.c_int, ctypes.c_uint64, ctypes.POINTER(Memory), ctypes.c_uint64]
	bgfx_create_texture_2d.restype = TextureHandle
	global bgfx_create_texture_2d_scaled
	bgfx_create_texture_2d_scaled = lib.bgfx_create_texture_2d_scaled
	bgfx_create_texture_2d_scaled.argtypes = [ctypes.c_int, ctypes.c_bool, ctypes.c_uint16, ctypes.c_int, ctypes.c_uint64]
	bgfx_create_texture_2d_scaled.restype = TextureHandle
	global bgfx_create_texture_3d
	bgfx_create_texture_3d = lib.bgfx_create_texture_3d
	bgfx_create_texture_3d.argtypes = [ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint16, ctypes.c_bool, ctypes.c_int, ctypes.c_uint64, ctypes.POINTER(Memory), ctypes.c_uint64]
	bgfx_create_texture_3d.restype = TextureHandle
	global bgfx_create_texture_cube
	bgfx_create_texture_cube = lib.bgfx_create_texture_cube
	bgfx_create_texture_cube.argtypes = [ctypes.c_uint16, ctypes.c_bool, ctypes.c_uint16, ctypes.c_int, ctypes.c_uint64, ctypes.POINTER(Memory), ctypes.c_uint64]
	bgfx_create_texture_cube.restype = TextureHandle
	global bgfx_update_texture_2d
	bgfx_update_texture_2d = lib.bgfx_update_texture_2d
	bgfx_update_texture_2d.argtypes = [TextureHandle, ctypes.c_uint16, ctypes.c_uint8, ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint16, ctypes.POINTER(Memory), ctypes.c_uint16]
	bgfx_update_texture_2d.restype = None
	global bgfx_update_texture_3d
	bgfx_update_texture_3d = lib.bgfx_update_texture_3d
	bgfx_update_texture_3d.argtypes = [TextureHandle, ctypes.c_uint8, ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint16, ctypes.POINTER(Memory)]
	bgfx_update_texture_3d.restype = None
	global bgfx_update_texture_cube
	bgfx_update_texture_cube = lib.bgfx_update_texture_cube
	bgfx_update_texture_cube.argtypes = [TextureHandle, ctypes.c_uint16, ctypes.c_uint8, ctypes.c_uint8, ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint16, ctypes.POINTER(Memory), ctypes.c_uint16]
	bgfx_update_texture_cube.restype = None
	global bgfx_clear_texture
	bgfx_clear_texture = lib.bgfx_clear_texture
	bgfx_clear_texture.argtypes = [TextureHandle, ctypes.c_uint8, ctypes.c_uint8, ctypes.c_uint16, ctypes.c_uint16]
	bgfx_clear_texture.restype = None
	global bgfx_read_texture
	bgfx_read_texture = lib.bgfx_read_texture
	bgfx_read_texture.argtypes = [ctypes.POINTER(TextureRegion), ctypes.c_void_p]
	bgfx_read_texture.restype = ctypes.c_uint32
	global bgfx_set_texture_name
	bgfx_set_texture_name = lib.bgfx_set_texture_name
	bgfx_set_texture_name.argtypes = [TextureHandle, ctypes.c_char_p, ctypes.c_int32]
	bgfx_set_texture_name.restype = None
	global bgfx_get_direct_access_ptr
	bgfx_get_direct_access_ptr = lib.bgfx_get_direct_access_ptr
	bgfx_get_direct_access_ptr.argtypes = [TextureHandle]
	bgfx_get_direct_access_ptr.restype = ctypes.c_void_p
	global bgfx_destroy_texture
	bgfx_destroy_texture = lib.bgfx_destroy_texture
	bgfx_destroy_texture.argtypes = [TextureHandle]
	bgfx_destroy_texture.restype = None
	global bgfx_create_frame_buffer
	bgfx_create_frame_buffer = lib.bgfx_create_frame_buffer
	bgfx_create_frame_buffer.argtypes = [ctypes.c_uint16, ctypes.c_uint16, ctypes.c_int, ctypes.c_uint64]
	bgfx_create_frame_buffer.restype = FrameBufferHandle
	global bgfx_create_frame_buffer_scaled
	bgfx_create_frame_buffer_scaled = lib.bgfx_create_frame_buffer_scaled
	bgfx_create_frame_buffer_scaled.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_uint64]
	bgfx_create_frame_buffer_scaled.restype = FrameBufferHandle
	global bgfx_create_frame_buffer_from_handles
	bgfx_create_frame_buffer_from_handles = lib.bgfx_create_frame_buffer_from_handles
	bgfx_create_frame_buffer_from_handles.argtypes = [ctypes.c_uint8, ctypes.POINTER(TextureHandle), ctypes.c_bool]
	bgfx_create_frame_buffer_from_handles.restype = FrameBufferHandle
	global bgfx_create_frame_buffer_from_attachment
	bgfx_create_frame_buffer_from_attachment = lib.bgfx_create_frame_buffer_from_attachment
	bgfx_create_frame_buffer_from_attachment.argtypes = [ctypes.c_uint8, ctypes.POINTER(Attachment), ctypes.c_bool]
	bgfx_create_frame_buffer_from_attachment.restype = FrameBufferHandle
	global bgfx_create_frame_buffer_from_nwh
	bgfx_create_frame_buffer_from_nwh = lib.bgfx_create_frame_buffer_from_nwh
	bgfx_create_frame_buffer_from_nwh.argtypes = [ctypes.c_void_p, ctypes.c_uint16, ctypes.c_uint16, ctypes.c_int, ctypes.c_int]
	bgfx_create_frame_buffer_from_nwh.restype = FrameBufferHandle
	global bgfx_set_frame_buffer_name
	bgfx_set_frame_buffer_name = lib.bgfx_set_frame_buffer_name
	bgfx_set_frame_buffer_name.argtypes = [FrameBufferHandle, ctypes.c_char_p, ctypes.c_int32]
	bgfx_set_frame_buffer_name.restype = None
	global bgfx_get_texture
	bgfx_get_texture = lib.bgfx_get_texture
	bgfx_get_texture.argtypes = [FrameBufferHandle, ctypes.c_uint8]
	bgfx_get_texture.restype = TextureHandle
	global bgfx_destroy_frame_buffer
	bgfx_destroy_frame_buffer = lib.bgfx_destroy_frame_buffer
	bgfx_destroy_frame_buffer.argtypes = [FrameBufferHandle]
	bgfx_destroy_frame_buffer.restype = None
	global bgfx_create_uniform
	bgfx_create_uniform = lib.bgfx_create_uniform
	bgfx_create_uniform.argtypes = [ctypes.c_char_p, ctypes.c_int, ctypes.c_uint16]
	bgfx_create_uniform.restype = UniformHandle
	global bgfx_create_uniform_with_freq
	bgfx_create_uniform_with_freq = lib.bgfx_create_uniform_with_freq
	bgfx_create_uniform_with_freq.argtypes = [ctypes.c_char_p, ctypes.c_int, ctypes.c_int, ctypes.c_uint16]
	bgfx_create_uniform_with_freq.restype = UniformHandle
	global bgfx_get_uniform_info
	bgfx_get_uniform_info = lib.bgfx_get_uniform_info
	bgfx_get_uniform_info.argtypes = [UniformHandle, ctypes.POINTER(UniformInfo)]
	bgfx_get_uniform_info.restype = None
	global bgfx_destroy_uniform
	bgfx_destroy_uniform = lib.bgfx_destroy_uniform
	bgfx_destroy_uniform.argtypes = [UniformHandle]
	bgfx_destroy_uniform.restype = None
	global bgfx_create_occlusion_query
	bgfx_create_occlusion_query = lib.bgfx_create_occlusion_query
	bgfx_create_occlusion_query.argtypes = []
	bgfx_create_occlusion_query.restype = OcclusionQueryHandle
	global bgfx_get_result
	bgfx_get_result = lib.bgfx_get_result
	bgfx_get_result.argtypes = [OcclusionQueryHandle, ctypes.POINTER(ctypes.c_int32)]
	bgfx_get_result.restype = ctypes.c_int
	global bgfx_destroy_occlusion_query
	bgfx_destroy_occlusion_query = lib.bgfx_destroy_occlusion_query
	bgfx_destroy_occlusion_query.argtypes = [OcclusionQueryHandle]
	bgfx_destroy_occlusion_query.restype = None
	global bgfx_set_palette_color
	bgfx_set_palette_color = lib.bgfx_set_palette_color
	bgfx_set_palette_color.argtypes = [ctypes.c_uint8, ctypes.POINTER(ctypes.c_float)]
	bgfx_set_palette_color.restype = None
	global bgfx_set_palette_color_rgba32f
	bgfx_set_palette_color_rgba32f = lib.bgfx_set_palette_color_rgba32f
	bgfx_set_palette_color_rgba32f.argtypes = [ctypes.c_uint8, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float]
	bgfx_set_palette_color_rgba32f.restype = None
	global bgfx_set_palette_color_rgba8
	bgfx_set_palette_color_rgba8 = lib.bgfx_set_palette_color_rgba8
	bgfx_set_palette_color_rgba8.argtypes = [ctypes.c_uint8, ctypes.c_uint32]
	bgfx_set_palette_color_rgba8.restype = None
	global bgfx_set_view_name
	bgfx_set_view_name = lib.bgfx_set_view_name
	bgfx_set_view_name.argtypes = [ctypes.c_uint16, ctypes.c_char_p, ctypes.c_int32]
	bgfx_set_view_name.restype = None
	global bgfx_set_view_rect
	bgfx_set_view_rect = lib.bgfx_set_view_rect
	bgfx_set_view_rect.argtypes = [ctypes.c_uint16, ctypes.c_int16, ctypes.c_int16, ctypes.c_uint16, ctypes.c_uint16]
	bgfx_set_view_rect.restype = None
	global bgfx_set_view_rect_ratio
	bgfx_set_view_rect_ratio = lib.bgfx_set_view_rect_ratio
	bgfx_set_view_rect_ratio.argtypes = [ctypes.c_uint16, ctypes.c_int16, ctypes.c_int16, ctypes.c_int]
	bgfx_set_view_rect_ratio.restype = None
	global bgfx_set_view_scissor
	bgfx_set_view_scissor = lib.bgfx_set_view_scissor
	bgfx_set_view_scissor.argtypes = [ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint16]
	bgfx_set_view_scissor.restype = None
	global bgfx_set_view_clear
	bgfx_set_view_clear = lib.bgfx_set_view_clear
	bgfx_set_view_clear.argtypes = [ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint32, ctypes.c_float, ctypes.c_uint8]
	bgfx_set_view_clear.restype = None
	global bgfx_set_view_clear_mrt
	bgfx_set_view_clear_mrt = lib.bgfx_set_view_clear_mrt
	bgfx_set_view_clear_mrt.argtypes = [ctypes.c_uint16, ctypes.c_uint16, ctypes.c_float, ctypes.c_uint8, ctypes.c_uint8, ctypes.c_uint8, ctypes.c_uint8, ctypes.c_uint8, ctypes.c_uint8, ctypes.c_uint8, ctypes.c_uint8, ctypes.c_uint8]
	bgfx_set_view_clear_mrt.restype = None
	global bgfx_set_view_mode
	bgfx_set_view_mode = lib.bgfx_set_view_mode
	bgfx_set_view_mode.argtypes = [ctypes.c_uint16, ctypes.c_int]
	bgfx_set_view_mode.restype = None
	global bgfx_set_view_frame_buffer
	bgfx_set_view_frame_buffer = lib.bgfx_set_view_frame_buffer
	bgfx_set_view_frame_buffer.argtypes = [ctypes.c_uint16, FrameBufferHandle]
	bgfx_set_view_frame_buffer.restype = None
	global bgfx_set_view_transform
	bgfx_set_view_transform = lib.bgfx_set_view_transform
	bgfx_set_view_transform.argtypes = [ctypes.c_uint16, ctypes.c_void_p, ctypes.c_void_p]
	bgfx_set_view_transform.restype = None
	global bgfx_set_view_order
	bgfx_set_view_order = lib.bgfx_set_view_order
	bgfx_set_view_order.argtypes = [ctypes.c_uint16, ctypes.c_uint16, ctypes.POINTER(ctypes.c_uint16)]
	bgfx_set_view_order.restype = None
	global bgfx_set_view_shading_rate
	bgfx_set_view_shading_rate = lib.bgfx_set_view_shading_rate
	bgfx_set_view_shading_rate.argtypes = [ctypes.c_uint16, ctypes.c_int]
	bgfx_set_view_shading_rate.restype = None
	global bgfx_reset_view
	bgfx_reset_view = lib.bgfx_reset_view
	bgfx_reset_view.argtypes = [ctypes.c_uint16]
	bgfx_reset_view.restype = None
	global bgfx_encoder_begin
	bgfx_encoder_begin = lib.bgfx_encoder_begin
	bgfx_encoder_begin.argtypes = [ctypes.c_bool]
	bgfx_encoder_begin.restype = ctypes.POINTER(Encoder)
	global bgfx_encoder_end
	bgfx_encoder_end = lib.bgfx_encoder_end
	bgfx_encoder_end.argtypes = [ctypes.POINTER(Encoder)]
	bgfx_encoder_end.restype = None
	global bgfx_encoder_set_marker
	bgfx_encoder_set_marker = lib.bgfx_encoder_set_marker
	bgfx_encoder_set_marker.argtypes = [ctypes.POINTER(Encoder), ctypes.c_char_p, ctypes.c_int32]
	bgfx_encoder_set_marker.restype = None
	global bgfx_encoder_set_state
	bgfx_encoder_set_state = lib.bgfx_encoder_set_state
	bgfx_encoder_set_state.argtypes = [ctypes.POINTER(Encoder), ctypes.c_uint64, ctypes.c_uint32]
	bgfx_encoder_set_state.restype = None
	global bgfx_encoder_set_condition
	bgfx_encoder_set_condition = lib.bgfx_encoder_set_condition
	bgfx_encoder_set_condition.argtypes = [ctypes.POINTER(Encoder), OcclusionQueryHandle, ctypes.c_bool]
	bgfx_encoder_set_condition.restype = None
	global bgfx_encoder_set_stencil
	bgfx_encoder_set_stencil = lib.bgfx_encoder_set_stencil
	bgfx_encoder_set_stencil.argtypes = [ctypes.POINTER(Encoder), ctypes.c_uint32, ctypes.c_uint32]
	bgfx_encoder_set_stencil.restype = None
	global bgfx_encoder_set_scissor
	bgfx_encoder_set_scissor = lib.bgfx_encoder_set_scissor
	bgfx_encoder_set_scissor.argtypes = [ctypes.POINTER(Encoder), ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint16]
	bgfx_encoder_set_scissor.restype = ctypes.c_uint16
	global bgfx_encoder_set_scissor_cached
	bgfx_encoder_set_scissor_cached = lib.bgfx_encoder_set_scissor_cached
	bgfx_encoder_set_scissor_cached.argtypes = [ctypes.POINTER(Encoder), ctypes.c_uint16]
	bgfx_encoder_set_scissor_cached.restype = None
	global bgfx_encoder_set_transform
	bgfx_encoder_set_transform = lib.bgfx_encoder_set_transform
	bgfx_encoder_set_transform.argtypes = [ctypes.POINTER(Encoder), ctypes.c_void_p, ctypes.c_uint16]
	bgfx_encoder_set_transform.restype = ctypes.c_uint32
	global bgfx_encoder_set_transform_cached
	bgfx_encoder_set_transform_cached = lib.bgfx_encoder_set_transform_cached
	bgfx_encoder_set_transform_cached.argtypes = [ctypes.POINTER(Encoder), ctypes.c_uint32, ctypes.c_uint16]
	bgfx_encoder_set_transform_cached.restype = None
	global bgfx_encoder_alloc_transform
	bgfx_encoder_alloc_transform = lib.bgfx_encoder_alloc_transform
	bgfx_encoder_alloc_transform.argtypes = [ctypes.POINTER(Encoder), ctypes.POINTER(Transform), ctypes.c_uint16]
	bgfx_encoder_alloc_transform.restype = ctypes.c_uint32
	global bgfx_encoder_set_uniform
	bgfx_encoder_set_uniform = lib.bgfx_encoder_set_uniform
	bgfx_encoder_set_uniform.argtypes = [ctypes.POINTER(Encoder), UniformHandle, ctypes.c_void_p, ctypes.c_uint16]
	bgfx_encoder_set_uniform.restype = None
	global bgfx_set_view_uniform
	bgfx_set_view_uniform = lib.bgfx_set_view_uniform
	bgfx_set_view_uniform.argtypes = [ctypes.c_uint16, UniformHandle, ctypes.c_void_p, ctypes.c_uint16]
	bgfx_set_view_uniform.restype = None
	global bgfx_set_frame_uniform
	bgfx_set_frame_uniform = lib.bgfx_set_frame_uniform
	bgfx_set_frame_uniform.argtypes = [UniformHandle, ctypes.c_void_p, ctypes.c_uint16]
	bgfx_set_frame_uniform.restype = None
	global bgfx_encoder_set_index_buffer
	bgfx_encoder_set_index_buffer = lib.bgfx_encoder_set_index_buffer
	bgfx_encoder_set_index_buffer.argtypes = [ctypes.POINTER(Encoder), IndexBufferHandle, ctypes.c_uint32, ctypes.c_uint32]
	bgfx_encoder_set_index_buffer.restype = None
	global bgfx_encoder_set_dynamic_index_buffer
	bgfx_encoder_set_dynamic_index_buffer = lib.bgfx_encoder_set_dynamic_index_buffer
	bgfx_encoder_set_dynamic_index_buffer.argtypes = [ctypes.POINTER(Encoder), DynamicIndexBufferHandle, ctypes.c_uint32, ctypes.c_uint32]
	bgfx_encoder_set_dynamic_index_buffer.restype = None
	global bgfx_encoder_set_transient_index_buffer
	bgfx_encoder_set_transient_index_buffer = lib.bgfx_encoder_set_transient_index_buffer
	bgfx_encoder_set_transient_index_buffer.argtypes = [ctypes.POINTER(Encoder), ctypes.POINTER(TransientIndexBuffer), ctypes.c_uint32, ctypes.c_uint32]
	bgfx_encoder_set_transient_index_buffer.restype = None
	global bgfx_encoder_set_vertex_buffer
	bgfx_encoder_set_vertex_buffer = lib.bgfx_encoder_set_vertex_buffer
	bgfx_encoder_set_vertex_buffer.argtypes = [ctypes.POINTER(Encoder), ctypes.c_uint8, VertexBufferHandle, ctypes.c_uint32, ctypes.c_uint32]
	bgfx_encoder_set_vertex_buffer.restype = None
	global bgfx_encoder_set_vertex_buffer_with_layout
	bgfx_encoder_set_vertex_buffer_with_layout = lib.bgfx_encoder_set_vertex_buffer_with_layout
	bgfx_encoder_set_vertex_buffer_with_layout.argtypes = [ctypes.POINTER(Encoder), ctypes.c_uint8, VertexBufferHandle, ctypes.c_uint32, ctypes.c_uint32, VertexLayoutHandle]
	bgfx_encoder_set_vertex_buffer_with_layout.restype = None
	global bgfx_encoder_set_dynamic_vertex_buffer
	bgfx_encoder_set_dynamic_vertex_buffer = lib.bgfx_encoder_set_dynamic_vertex_buffer
	bgfx_encoder_set_dynamic_vertex_buffer.argtypes = [ctypes.POINTER(Encoder), ctypes.c_uint8, DynamicVertexBufferHandle, ctypes.c_uint32, ctypes.c_uint32]
	bgfx_encoder_set_dynamic_vertex_buffer.restype = None
	global bgfx_encoder_set_dynamic_vertex_buffer_with_layout
	bgfx_encoder_set_dynamic_vertex_buffer_with_layout = lib.bgfx_encoder_set_dynamic_vertex_buffer_with_layout
	bgfx_encoder_set_dynamic_vertex_buffer_with_layout.argtypes = [ctypes.POINTER(Encoder), ctypes.c_uint8, DynamicVertexBufferHandle, ctypes.c_uint32, ctypes.c_uint32, VertexLayoutHandle]
	bgfx_encoder_set_dynamic_vertex_buffer_with_layout.restype = None
	global bgfx_encoder_set_transient_vertex_buffer
	bgfx_encoder_set_transient_vertex_buffer = lib.bgfx_encoder_set_transient_vertex_buffer
	bgfx_encoder_set_transient_vertex_buffer.argtypes = [ctypes.POINTER(Encoder), ctypes.c_uint8, ctypes.POINTER(TransientVertexBuffer), ctypes.c_uint32, ctypes.c_uint32]
	bgfx_encoder_set_transient_vertex_buffer.restype = None
	global bgfx_encoder_set_transient_vertex_buffer_with_layout
	bgfx_encoder_set_transient_vertex_buffer_with_layout = lib.bgfx_encoder_set_transient_vertex_buffer_with_layout
	bgfx_encoder_set_transient_vertex_buffer_with_layout.argtypes = [ctypes.POINTER(Encoder), ctypes.c_uint8, ctypes.POINTER(TransientVertexBuffer), ctypes.c_uint32, ctypes.c_uint32, VertexLayoutHandle]
	bgfx_encoder_set_transient_vertex_buffer_with_layout.restype = None
	global bgfx_encoder_set_vertex_count
	bgfx_encoder_set_vertex_count = lib.bgfx_encoder_set_vertex_count
	bgfx_encoder_set_vertex_count.argtypes = [ctypes.POINTER(Encoder), ctypes.c_uint32]
	bgfx_encoder_set_vertex_count.restype = None
	global bgfx_encoder_set_instance_data_buffer
	bgfx_encoder_set_instance_data_buffer = lib.bgfx_encoder_set_instance_data_buffer
	bgfx_encoder_set_instance_data_buffer.argtypes = [ctypes.POINTER(Encoder), ctypes.POINTER(InstanceDataBuffer), ctypes.c_uint32, ctypes.c_uint32]
	bgfx_encoder_set_instance_data_buffer.restype = None
	global bgfx_encoder_set_instance_data_from_vertex_buffer
	bgfx_encoder_set_instance_data_from_vertex_buffer = lib.bgfx_encoder_set_instance_data_from_vertex_buffer
	bgfx_encoder_set_instance_data_from_vertex_buffer.argtypes = [ctypes.POINTER(Encoder), VertexBufferHandle, ctypes.c_uint32, ctypes.c_uint32]
	bgfx_encoder_set_instance_data_from_vertex_buffer.restype = None
	global bgfx_encoder_set_instance_data_from_dynamic_vertex_buffer
	bgfx_encoder_set_instance_data_from_dynamic_vertex_buffer = lib.bgfx_encoder_set_instance_data_from_dynamic_vertex_buffer
	bgfx_encoder_set_instance_data_from_dynamic_vertex_buffer.argtypes = [ctypes.POINTER(Encoder), DynamicVertexBufferHandle, ctypes.c_uint32, ctypes.c_uint32]
	bgfx_encoder_set_instance_data_from_dynamic_vertex_buffer.restype = None
	global bgfx_encoder_set_instance_count
	bgfx_encoder_set_instance_count = lib.bgfx_encoder_set_instance_count
	bgfx_encoder_set_instance_count.argtypes = [ctypes.POINTER(Encoder), ctypes.c_uint32]
	bgfx_encoder_set_instance_count.restype = None
	global bgfx_encoder_set_texture
	bgfx_encoder_set_texture = lib.bgfx_encoder_set_texture
	bgfx_encoder_set_texture.argtypes = [ctypes.POINTER(Encoder), ctypes.c_uint8, UniformHandle, TextureHandle, ctypes.c_uint32]
	bgfx_encoder_set_texture.restype = None
	global bgfx_encoder_set_texture_view
	bgfx_encoder_set_texture_view = lib.bgfx_encoder_set_texture_view
	bgfx_encoder_set_texture_view.argtypes = [ctypes.POINTER(Encoder), ctypes.c_uint8, UniformHandle, TextureHandle, ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint8, ctypes.c_uint8, ctypes.c_uint32]
	bgfx_encoder_set_texture_view.restype = None
	global bgfx_encoder_touch
	bgfx_encoder_touch = lib.bgfx_encoder_touch
	bgfx_encoder_touch.argtypes = [ctypes.POINTER(Encoder), ctypes.c_uint16]
	bgfx_encoder_touch.restype = None
	global bgfx_encoder_submit
	bgfx_encoder_submit = lib.bgfx_encoder_submit
	bgfx_encoder_submit.argtypes = [ctypes.POINTER(Encoder), ctypes.c_uint16, ProgramHandle, ctypes.c_uint32, ctypes.c_uint8]
	bgfx_encoder_submit.restype = None
	global bgfx_encoder_submit_occlusion_query
	bgfx_encoder_submit_occlusion_query = lib.bgfx_encoder_submit_occlusion_query
	bgfx_encoder_submit_occlusion_query.argtypes = [ctypes.POINTER(Encoder), ctypes.c_uint16, ProgramHandle, OcclusionQueryHandle, ctypes.c_uint32, ctypes.c_uint8]
	bgfx_encoder_submit_occlusion_query.restype = None
	global bgfx_encoder_submit_indirect
	bgfx_encoder_submit_indirect = lib.bgfx_encoder_submit_indirect
	bgfx_encoder_submit_indirect.argtypes = [ctypes.POINTER(Encoder), ctypes.c_uint16, ProgramHandle, IndirectBufferHandle, ctypes.c_uint32, ctypes.c_uint32, ctypes.c_uint32, ctypes.c_uint8]
	bgfx_encoder_submit_indirect.restype = None
	global bgfx_encoder_submit_indirect_count
	bgfx_encoder_submit_indirect_count = lib.bgfx_encoder_submit_indirect_count
	bgfx_encoder_submit_indirect_count.argtypes = [ctypes.POINTER(Encoder), ctypes.c_uint16, ProgramHandle, IndirectBufferHandle, ctypes.c_uint32, IndexBufferHandle, ctypes.c_uint32, ctypes.c_uint32, ctypes.c_uint32, ctypes.c_uint8]
	bgfx_encoder_submit_indirect_count.restype = None
	global bgfx_encoder_set_compute_index_buffer
	bgfx_encoder_set_compute_index_buffer = lib.bgfx_encoder_set_compute_index_buffer
	bgfx_encoder_set_compute_index_buffer.argtypes = [ctypes.POINTER(Encoder), ctypes.c_uint8, IndexBufferHandle, ctypes.c_int]
	bgfx_encoder_set_compute_index_buffer.restype = None
	global bgfx_encoder_set_compute_vertex_buffer
	bgfx_encoder_set_compute_vertex_buffer = lib.bgfx_encoder_set_compute_vertex_buffer
	bgfx_encoder_set_compute_vertex_buffer.argtypes = [ctypes.POINTER(Encoder), ctypes.c_uint8, VertexBufferHandle, ctypes.c_int]
	bgfx_encoder_set_compute_vertex_buffer.restype = None
	global bgfx_encoder_set_compute_dynamic_index_buffer
	bgfx_encoder_set_compute_dynamic_index_buffer = lib.bgfx_encoder_set_compute_dynamic_index_buffer
	bgfx_encoder_set_compute_dynamic_index_buffer.argtypes = [ctypes.POINTER(Encoder), ctypes.c_uint8, DynamicIndexBufferHandle, ctypes.c_int]
	bgfx_encoder_set_compute_dynamic_index_buffer.restype = None
	global bgfx_encoder_set_compute_dynamic_vertex_buffer
	bgfx_encoder_set_compute_dynamic_vertex_buffer = lib.bgfx_encoder_set_compute_dynamic_vertex_buffer
	bgfx_encoder_set_compute_dynamic_vertex_buffer.argtypes = [ctypes.POINTER(Encoder), ctypes.c_uint8, DynamicVertexBufferHandle, ctypes.c_int]
	bgfx_encoder_set_compute_dynamic_vertex_buffer.restype = None
	global bgfx_encoder_set_compute_indirect_buffer
	bgfx_encoder_set_compute_indirect_buffer = lib.bgfx_encoder_set_compute_indirect_buffer
	bgfx_encoder_set_compute_indirect_buffer.argtypes = [ctypes.POINTER(Encoder), ctypes.c_uint8, IndirectBufferHandle, ctypes.c_int]
	bgfx_encoder_set_compute_indirect_buffer.restype = None
	global bgfx_encoder_set_image
	bgfx_encoder_set_image = lib.bgfx_encoder_set_image
	bgfx_encoder_set_image.argtypes = [ctypes.POINTER(Encoder), ctypes.c_uint8, TextureHandle, ctypes.c_uint8, ctypes.c_int, ctypes.c_int]
	bgfx_encoder_set_image.restype = None
	global bgfx_encoder_set_image_view
	bgfx_encoder_set_image_view = lib.bgfx_encoder_set_image_view
	bgfx_encoder_set_image_view.argtypes = [ctypes.POINTER(Encoder), ctypes.c_uint8, TextureHandle, ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint8, ctypes.c_int, ctypes.c_int]
	bgfx_encoder_set_image_view.restype = None
	global bgfx_encoder_dispatch
	bgfx_encoder_dispatch = lib.bgfx_encoder_dispatch
	bgfx_encoder_dispatch.argtypes = [ctypes.POINTER(Encoder), ctypes.c_uint16, ProgramHandle, ctypes.c_uint32, ctypes.c_uint32, ctypes.c_uint32, ctypes.c_uint8]
	bgfx_encoder_dispatch.restype = None
	global bgfx_encoder_dispatch_indirect
	bgfx_encoder_dispatch_indirect = lib.bgfx_encoder_dispatch_indirect
	bgfx_encoder_dispatch_indirect.argtypes = [ctypes.POINTER(Encoder), ctypes.c_uint16, ProgramHandle, IndirectBufferHandle, ctypes.c_uint32, ctypes.c_uint32, ctypes.c_uint8]
	bgfx_encoder_dispatch_indirect.restype = None
	global bgfx_encoder_discard
	bgfx_encoder_discard = lib.bgfx_encoder_discard
	bgfx_encoder_discard.argtypes = [ctypes.POINTER(Encoder), ctypes.c_uint8]
	bgfx_encoder_discard.restype = None
	global bgfx_encoder_blit
	bgfx_encoder_blit = lib.bgfx_encoder_blit
	bgfx_encoder_blit.argtypes = [ctypes.POINTER(Encoder), ctypes.c_uint16, ctypes.POINTER(TextureRegion), ctypes.POINTER(TextureRegion)]
	bgfx_encoder_blit.restype = None
	global bgfx_encoder_blit_buffer
	bgfx_encoder_blit_buffer = lib.bgfx_encoder_blit_buffer
	bgfx_encoder_blit_buffer.argtypes = [ctypes.POINTER(Encoder), ctypes.c_uint16, ctypes.POINTER(BufferRegion), ctypes.POINTER(BufferRegion)]
	bgfx_encoder_blit_buffer.restype = None
	global bgfx_encoder_blit_to_buffer
	bgfx_encoder_blit_to_buffer = lib.bgfx_encoder_blit_to_buffer
	bgfx_encoder_blit_to_buffer.argtypes = [ctypes.POINTER(Encoder), ctypes.c_uint16, ctypes.POINTER(BufferRegion), ctypes.POINTER(TextureRegion)]
	bgfx_encoder_blit_to_buffer.restype = None
	global bgfx_encoder_blit_from_buffer
	bgfx_encoder_blit_from_buffer = lib.bgfx_encoder_blit_from_buffer
	bgfx_encoder_blit_from_buffer.argtypes = [ctypes.POINTER(Encoder), ctypes.c_uint16, ctypes.POINTER(TextureRegion), ctypes.POINTER(BufferRegion)]
	bgfx_encoder_blit_from_buffer.restype = None
	global bgfx_request_screen_shot
	bgfx_request_screen_shot = lib.bgfx_request_screen_shot
	bgfx_request_screen_shot.argtypes = [FrameBufferHandle, ctypes.c_char_p]
	bgfx_request_screen_shot.restype = None
	global bgfx_render_frame
	bgfx_render_frame = lib.bgfx_render_frame
	bgfx_render_frame.argtypes = [ctypes.c_int32]
	bgfx_render_frame.restype = ctypes.c_int
	global bgfx_set_platform_data
	bgfx_set_platform_data = lib.bgfx_set_platform_data
	bgfx_set_platform_data.argtypes = [ctypes.POINTER(PlatformData)]
	bgfx_set_platform_data.restype = None
	global bgfx_get_internal_data
	bgfx_get_internal_data = lib.bgfx_get_internal_data
	bgfx_get_internal_data.argtypes = []
	bgfx_get_internal_data.restype = ctypes.POINTER(InternalData)
	global bgfx_override_internal_texture_ptr
	bgfx_override_internal_texture_ptr = lib.bgfx_override_internal_texture_ptr
	bgfx_override_internal_texture_ptr.argtypes = [TextureHandle, ctypes.c_size_t, ctypes.c_uint16]
	bgfx_override_internal_texture_ptr.restype = ctypes.c_size_t
	global bgfx_override_internal_texture
	bgfx_override_internal_texture = lib.bgfx_override_internal_texture
	bgfx_override_internal_texture.argtypes = [TextureHandle, ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint8, ctypes.c_int, ctypes.c_uint64]
	bgfx_override_internal_texture.restype = ctypes.c_size_t
	global bgfx_set_marker
	bgfx_set_marker = lib.bgfx_set_marker
	bgfx_set_marker.argtypes = [ctypes.c_char_p, ctypes.c_int32]
	bgfx_set_marker.restype = None
	global bgfx_set_state
	bgfx_set_state = lib.bgfx_set_state
	bgfx_set_state.argtypes = [ctypes.c_uint64, ctypes.c_uint32]
	bgfx_set_state.restype = None
	global bgfx_set_condition
	bgfx_set_condition = lib.bgfx_set_condition
	bgfx_set_condition.argtypes = [OcclusionQueryHandle, ctypes.c_bool]
	bgfx_set_condition.restype = None
	global bgfx_set_stencil
	bgfx_set_stencil = lib.bgfx_set_stencil
	bgfx_set_stencil.argtypes = [ctypes.c_uint32, ctypes.c_uint32]
	bgfx_set_stencil.restype = None
	global bgfx_set_scissor
	bgfx_set_scissor = lib.bgfx_set_scissor
	bgfx_set_scissor.argtypes = [ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint16]
	bgfx_set_scissor.restype = ctypes.c_uint16
	global bgfx_set_scissor_cached
	bgfx_set_scissor_cached = lib.bgfx_set_scissor_cached
	bgfx_set_scissor_cached.argtypes = [ctypes.c_uint16]
	bgfx_set_scissor_cached.restype = None
	global bgfx_set_transform
	bgfx_set_transform = lib.bgfx_set_transform
	bgfx_set_transform.argtypes = [ctypes.c_void_p, ctypes.c_uint16]
	bgfx_set_transform.restype = ctypes.c_uint32
	global bgfx_set_transform_cached
	bgfx_set_transform_cached = lib.bgfx_set_transform_cached
	bgfx_set_transform_cached.argtypes = [ctypes.c_uint32, ctypes.c_uint16]
	bgfx_set_transform_cached.restype = None
	global bgfx_alloc_transform
	bgfx_alloc_transform = lib.bgfx_alloc_transform
	bgfx_alloc_transform.argtypes = [ctypes.POINTER(Transform), ctypes.c_uint16]
	bgfx_alloc_transform.restype = ctypes.c_uint32
	global bgfx_set_uniform
	bgfx_set_uniform = lib.bgfx_set_uniform
	bgfx_set_uniform.argtypes = [UniformHandle, ctypes.c_void_p, ctypes.c_uint16]
	bgfx_set_uniform.restype = None
	global bgfx_set_index_buffer
	bgfx_set_index_buffer = lib.bgfx_set_index_buffer
	bgfx_set_index_buffer.argtypes = [IndexBufferHandle, ctypes.c_uint32, ctypes.c_uint32]
	bgfx_set_index_buffer.restype = None
	global bgfx_set_dynamic_index_buffer
	bgfx_set_dynamic_index_buffer = lib.bgfx_set_dynamic_index_buffer
	bgfx_set_dynamic_index_buffer.argtypes = [DynamicIndexBufferHandle, ctypes.c_uint32, ctypes.c_uint32]
	bgfx_set_dynamic_index_buffer.restype = None
	global bgfx_set_transient_index_buffer
	bgfx_set_transient_index_buffer = lib.bgfx_set_transient_index_buffer
	bgfx_set_transient_index_buffer.argtypes = [ctypes.POINTER(TransientIndexBuffer), ctypes.c_uint32, ctypes.c_uint32]
	bgfx_set_transient_index_buffer.restype = None
	global bgfx_set_vertex_buffer
	bgfx_set_vertex_buffer = lib.bgfx_set_vertex_buffer
	bgfx_set_vertex_buffer.argtypes = [ctypes.c_uint8, VertexBufferHandle, ctypes.c_uint32, ctypes.c_uint32]
	bgfx_set_vertex_buffer.restype = None
	global bgfx_set_vertex_buffer_with_layout
	bgfx_set_vertex_buffer_with_layout = lib.bgfx_set_vertex_buffer_with_layout
	bgfx_set_vertex_buffer_with_layout.argtypes = [ctypes.c_uint8, VertexBufferHandle, ctypes.c_uint32, ctypes.c_uint32, VertexLayoutHandle]
	bgfx_set_vertex_buffer_with_layout.restype = None
	global bgfx_set_dynamic_vertex_buffer
	bgfx_set_dynamic_vertex_buffer = lib.bgfx_set_dynamic_vertex_buffer
	bgfx_set_dynamic_vertex_buffer.argtypes = [ctypes.c_uint8, DynamicVertexBufferHandle, ctypes.c_uint32, ctypes.c_uint32]
	bgfx_set_dynamic_vertex_buffer.restype = None
	global bgfx_set_dynamic_vertex_buffer_with_layout
	bgfx_set_dynamic_vertex_buffer_with_layout = lib.bgfx_set_dynamic_vertex_buffer_with_layout
	bgfx_set_dynamic_vertex_buffer_with_layout.argtypes = [ctypes.c_uint8, DynamicVertexBufferHandle, ctypes.c_uint32, ctypes.c_uint32, VertexLayoutHandle]
	bgfx_set_dynamic_vertex_buffer_with_layout.restype = None
	global bgfx_set_transient_vertex_buffer
	bgfx_set_transient_vertex_buffer = lib.bgfx_set_transient_vertex_buffer
	bgfx_set_transient_vertex_buffer.argtypes = [ctypes.c_uint8, ctypes.POINTER(TransientVertexBuffer), ctypes.c_uint32, ctypes.c_uint32]
	bgfx_set_transient_vertex_buffer.restype = None
	global bgfx_set_transient_vertex_buffer_with_layout
	bgfx_set_transient_vertex_buffer_with_layout = lib.bgfx_set_transient_vertex_buffer_with_layout
	bgfx_set_transient_vertex_buffer_with_layout.argtypes = [ctypes.c_uint8, ctypes.POINTER(TransientVertexBuffer), ctypes.c_uint32, ctypes.c_uint32, VertexLayoutHandle]
	bgfx_set_transient_vertex_buffer_with_layout.restype = None
	global bgfx_set_vertex_count
	bgfx_set_vertex_count = lib.bgfx_set_vertex_count
	bgfx_set_vertex_count.argtypes = [ctypes.c_uint32]
	bgfx_set_vertex_count.restype = None
	global bgfx_set_instance_data_buffer
	bgfx_set_instance_data_buffer = lib.bgfx_set_instance_data_buffer
	bgfx_set_instance_data_buffer.argtypes = [ctypes.POINTER(InstanceDataBuffer), ctypes.c_uint32, ctypes.c_uint32]
	bgfx_set_instance_data_buffer.restype = None
	global bgfx_set_instance_data_from_vertex_buffer
	bgfx_set_instance_data_from_vertex_buffer = lib.bgfx_set_instance_data_from_vertex_buffer
	bgfx_set_instance_data_from_vertex_buffer.argtypes = [VertexBufferHandle, ctypes.c_uint32, ctypes.c_uint32]
	bgfx_set_instance_data_from_vertex_buffer.restype = None
	global bgfx_set_instance_data_from_dynamic_vertex_buffer
	bgfx_set_instance_data_from_dynamic_vertex_buffer = lib.bgfx_set_instance_data_from_dynamic_vertex_buffer
	bgfx_set_instance_data_from_dynamic_vertex_buffer.argtypes = [DynamicVertexBufferHandle, ctypes.c_uint32, ctypes.c_uint32]
	bgfx_set_instance_data_from_dynamic_vertex_buffer.restype = None
	global bgfx_set_instance_count
	bgfx_set_instance_count = lib.bgfx_set_instance_count
	bgfx_set_instance_count.argtypes = [ctypes.c_uint32]
	bgfx_set_instance_count.restype = None
	global bgfx_set_texture
	bgfx_set_texture = lib.bgfx_set_texture
	bgfx_set_texture.argtypes = [ctypes.c_uint8, UniformHandle, TextureHandle, ctypes.c_uint32]
	bgfx_set_texture.restype = None
	global bgfx_set_texture_view
	bgfx_set_texture_view = lib.bgfx_set_texture_view
	bgfx_set_texture_view.argtypes = [ctypes.c_uint8, UniformHandle, TextureHandle, ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint8, ctypes.c_uint8, ctypes.c_uint32]
	bgfx_set_texture_view.restype = None
	global bgfx_touch
	bgfx_touch = lib.bgfx_touch
	bgfx_touch.argtypes = [ctypes.c_uint16]
	bgfx_touch.restype = None
	global bgfx_submit
	bgfx_submit = lib.bgfx_submit
	bgfx_submit.argtypes = [ctypes.c_uint16, ProgramHandle, ctypes.c_uint32, ctypes.c_uint8]
	bgfx_submit.restype = None
	global bgfx_submit_occlusion_query
	bgfx_submit_occlusion_query = lib.bgfx_submit_occlusion_query
	bgfx_submit_occlusion_query.argtypes = [ctypes.c_uint16, ProgramHandle, OcclusionQueryHandle, ctypes.c_uint32, ctypes.c_uint8]
	bgfx_submit_occlusion_query.restype = None
	global bgfx_submit_indirect
	bgfx_submit_indirect = lib.bgfx_submit_indirect
	bgfx_submit_indirect.argtypes = [ctypes.c_uint16, ProgramHandle, IndirectBufferHandle, ctypes.c_uint32, ctypes.c_uint32, ctypes.c_uint32, ctypes.c_uint8]
	bgfx_submit_indirect.restype = None
	global bgfx_submit_indirect_count
	bgfx_submit_indirect_count = lib.bgfx_submit_indirect_count
	bgfx_submit_indirect_count.argtypes = [ctypes.c_uint16, ProgramHandle, IndirectBufferHandle, ctypes.c_uint32, IndexBufferHandle, ctypes.c_uint32, ctypes.c_uint32, ctypes.c_uint32, ctypes.c_uint8]
	bgfx_submit_indirect_count.restype = None
	global bgfx_set_compute_index_buffer
	bgfx_set_compute_index_buffer = lib.bgfx_set_compute_index_buffer
	bgfx_set_compute_index_buffer.argtypes = [ctypes.c_uint8, IndexBufferHandle, ctypes.c_int]
	bgfx_set_compute_index_buffer.restype = None
	global bgfx_set_compute_vertex_buffer
	bgfx_set_compute_vertex_buffer = lib.bgfx_set_compute_vertex_buffer
	bgfx_set_compute_vertex_buffer.argtypes = [ctypes.c_uint8, VertexBufferHandle, ctypes.c_int]
	bgfx_set_compute_vertex_buffer.restype = None
	global bgfx_set_compute_dynamic_index_buffer
	bgfx_set_compute_dynamic_index_buffer = lib.bgfx_set_compute_dynamic_index_buffer
	bgfx_set_compute_dynamic_index_buffer.argtypes = [ctypes.c_uint8, DynamicIndexBufferHandle, ctypes.c_int]
	bgfx_set_compute_dynamic_index_buffer.restype = None
	global bgfx_set_compute_dynamic_vertex_buffer
	bgfx_set_compute_dynamic_vertex_buffer = lib.bgfx_set_compute_dynamic_vertex_buffer
	bgfx_set_compute_dynamic_vertex_buffer.argtypes = [ctypes.c_uint8, DynamicVertexBufferHandle, ctypes.c_int]
	bgfx_set_compute_dynamic_vertex_buffer.restype = None
	global bgfx_set_compute_indirect_buffer
	bgfx_set_compute_indirect_buffer = lib.bgfx_set_compute_indirect_buffer
	bgfx_set_compute_indirect_buffer.argtypes = [ctypes.c_uint8, IndirectBufferHandle, ctypes.c_int]
	bgfx_set_compute_indirect_buffer.restype = None
	global bgfx_set_image
	bgfx_set_image = lib.bgfx_set_image
	bgfx_set_image.argtypes = [ctypes.c_uint8, TextureHandle, ctypes.c_uint8, ctypes.c_int, ctypes.c_int]
	bgfx_set_image.restype = None
	global bgfx_set_image_view
	bgfx_set_image_view = lib.bgfx_set_image_view
	bgfx_set_image_view.argtypes = [ctypes.c_uint8, TextureHandle, ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint8, ctypes.c_int, ctypes.c_int]
	bgfx_set_image_view.restype = None
	global bgfx_dispatch
	bgfx_dispatch = lib.bgfx_dispatch
	bgfx_dispatch.argtypes = [ctypes.c_uint16, ProgramHandle, ctypes.c_uint32, ctypes.c_uint32, ctypes.c_uint32, ctypes.c_uint8]
	bgfx_dispatch.restype = None
	global bgfx_dispatch_indirect
	bgfx_dispatch_indirect = lib.bgfx_dispatch_indirect
	bgfx_dispatch_indirect.argtypes = [ctypes.c_uint16, ProgramHandle, IndirectBufferHandle, ctypes.c_uint32, ctypes.c_uint32, ctypes.c_uint8]
	bgfx_dispatch_indirect.restype = None
	global bgfx_discard
	bgfx_discard = lib.bgfx_discard
	bgfx_discard.argtypes = [ctypes.c_uint8]
	bgfx_discard.restype = None
	global bgfx_blit
	bgfx_blit = lib.bgfx_blit
	bgfx_blit.argtypes = [ctypes.c_uint16, ctypes.POINTER(TextureRegion), ctypes.POINTER(TextureRegion)]
	bgfx_blit.restype = None
	global bgfx_blit_buffer
	bgfx_blit_buffer = lib.bgfx_blit_buffer
	bgfx_blit_buffer.argtypes = [ctypes.c_uint16, ctypes.POINTER(BufferRegion), ctypes.POINTER(BufferRegion)]
	bgfx_blit_buffer.restype = None
	global bgfx_blit_to_buffer
	bgfx_blit_to_buffer = lib.bgfx_blit_to_buffer
	bgfx_blit_to_buffer.argtypes = [ctypes.c_uint16, ctypes.POINTER(BufferRegion), ctypes.POINTER(TextureRegion)]
	bgfx_blit_to_buffer.restype = None
	global bgfx_blit_from_buffer
	bgfx_blit_from_buffer = lib.bgfx_blit_from_buffer
	bgfx_blit_from_buffer.argtypes = [ctypes.c_uint16, ctypes.POINTER(TextureRegion), ctypes.POINTER(BufferRegion)]
	bgfx_blit_from_buffer.restype = None
