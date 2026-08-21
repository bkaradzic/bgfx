# Copyright 2011-2026 Branimir Karadzic. All rights reserved.
# License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE

#
# AUTO GENERATED! DO NOT EDIT!
#

import ctypes
import enum

ViewId = ctypes.c_uint16

# Fatal error enum.
class Fatal(enum.IntEnum):
	DebugCheck = 0
	InvalidShader = 1
	UnableToInitialize = 2
	UnableToCreateTexture = 3
	DeviceLost = 4
	Count = 5

# Renderer backend type enum.
class RendererType(enum.IntEnum):
	# No rendering.
	Noop = 0
	# AGC
	Agc = 1
	# Direct3D 11.0
	Direct3D11 = 2
	# Direct3D 12.0
	Direct3D12 = 3
	# GNM
	Gnm = 4
	# Metal
	Metal = 5
	# NVN
	Nvn = 6
	# OpenGL ES 3.0+
	OpenGLES = 7
	# OpenGL 4.3+
	OpenGL = 8
	# Vulkan
	Vulkan = 9
	# WebGPU
	WebGPU = 10
	Count = 11

# Access mode enum.
class Access(enum.IntEnum):
	# Read.
	Read = 0
	# Write.
	Write = 1
	# Read and write.
	ReadWrite = 2
	Count = 3

# Vertex attribute enum.
class Attrib(enum.IntEnum):
	# a_position
	Position = 0
	# a_normal
	Normal = 1
	# a_tangent
	Tangent = 2
	# a_bitangent
	Bitangent = 3
	# a_color0
	Color0 = 4
	# a_color1
	Color1 = 5
	# a_color2
	Color2 = 6
	# a_color3
	Color3 = 7
	# a_indices
	Indices = 8
	# a_weight
	Weight = 9
	# a_texcoord0
	TexCoord0 = 10
	# a_texcoord1
	TexCoord1 = 11
	# a_texcoord2
	TexCoord2 = 12
	# a_texcoord3
	TexCoord3 = 13
	# a_texcoord4
	TexCoord4 = 14
	# a_texcoord5
	TexCoord5 = 15
	# a_texcoord6
	TexCoord6 = 16
	# a_texcoord7
	TexCoord7 = 17
	# a_texcoord8
	TexCoord8 = 18
	# a_texcoord9
	TexCoord9 = 19
	# a_texcoord10
	TexCoord10 = 20
	# a_texcoord11
	TexCoord11 = 21
	# a_texcoord12
	TexCoord12 = 22
	# a_texcoord13
	TexCoord13 = 23
	# a_texcoord14
	TexCoord14 = 24
	# a_texcoord15
	TexCoord15 = 25
	Count = 26

# Vertex attribute type enum.
class AttribType(enum.IntEnum):
	# Int8
	Int8 = 0
	# Uint8
	Uint8 = 1
	# Uint10, availability depends on: `BGFX_CAPS_VERTEX_ATTRIB_UINT10`.
	Uint10 = 2
	# Int16
	Int16 = 3
	# Uint16
	Uint16 = 4
	# Half, availability depends on: `BGFX_CAPS_VERTEX_ATTRIB_HALF`.
	Half = 5
	# Float
	Float = 6
	# Int32
	Int32 = 7
	# Uint32
	Uint32 = 8
	Count = 9

# Texture format enum.
# 
# Notation:
# 
#       RGBA16S
#       ^   ^ ^
#       |   | +-- [ ]Unorm
#       |   |     [F]loat
#       |   |     [S]norm
#       |   |     [I]nt
#       |   |     [U]int
#       |   +---- Number of bits per component
#       +-------- Components
# 
# @attention Availability depends on Caps (see: formats).
class TextureFormat(enum.IntEnum):
	# Block Compression 1. 5-bit R, 6-bit G, 5-bit B, 1-bit A. 4 BPP.
	BC1 = 0
	# Block Compression 2. 5-bit R, 6-bit G, 5-bit B, 4-bit explicit A. 8 BPP.
	BC2 = 1
	# Block Compression 3. 5-bit R, 6-bit G, 5-bit B, 8-bit interpolated A. 8 BPP.
	BC3 = 2
	# Block Compression 4. Single 8-bit red channel, unsigned normalized. 4 BPP.
	BC4 = 3
	# Block Compression 4. Single 8-bit red channel, signed normalized. 4 BPP.
	BC4S = 4
	# Block Compression 5. Two 8-bit channels (RG), unsigned normalized. 8 BPP.
	BC5 = 5
	# Block Compression 5. Two 8-bit channels (RG), signed normalized. 8 BPP.
	BC5S = 6
	# Block Compression 6H. Three 16-bit floating-point channels (RGB), HDR. 8 BPP.
	BC6H = 7
	# Block Compression 6H. Three 16-bit unsigned floating-point channels (RGB), HDR. 8 BPP.
	BC6HU = 8
	# RGB 4-7 bits per color channel, 0-8 bits alpha. Block Compression 7. High-quality RGBA, 4-7 bits per color, 0-8 bits alpha. 8 BPP.
	BC7 = 9
	# Ericsson Texture Compression 1. 8-bit per channel RGB. 4 BPP.
	ETC1 = 10
	# Ericsson Texture Compression 2. 8-bit per channel RGB. 4 BPP.
	ETC2 = 11
	# Ericsson Texture Compression 2 with full alpha. 8-bit per channel RGBA. 8 BPP.
	ETC2A = 12
	# Ericsson Texture Compression 2 with 1-bit punch-through alpha. 4 BPP.
	ETC2A1 = 13
	# ETC2 Alpha Compression, single 11-bit red channel, unsigned normalized. 4 BPP.
	EACR11 = 14
	# ETC2 Alpha Compression, single 11-bit red channel, signed normalized. 4 BPP.
	EACR11S = 15
	# ETC2 Alpha Compression, two 11-bit channels (RG), unsigned normalized. 8 BPP.
	EACRG11 = 16
	# ETC2 Alpha Compression, two 11-bit channels (RG), signed normalized. 8 BPP.
	EACRG11S = 17
	# PowerVR Texture Compression v1. 3-channel RGB. 2 BPP.
	PTC12 = 18
	# PowerVR Texture Compression v1. 3-channel RGB. 4 BPP.
	PTC14 = 19
	# PowerVR Texture Compression v1. 4-channel RGBA. 2 BPP.
	PTC12A = 20
	# PowerVR Texture Compression v1. 4-channel RGBA. 4 BPP.
	PTC14A = 21
	# PowerVR Texture Compression v2. 4-channel RGBA. 2 BPP.
	PTC22 = 22
	# PowerVR Texture Compression v2. 4-channel RGBA. 4 BPP.
	PTC24 = 23
	# AMD Texture Compression. 3-channel RGB. 4 BPP.
	ATC = 24
	# AMD Texture Compression with explicit alpha. 4-channel RGBA. 8 BPP.
	ATCE = 25
	# AMD Texture Compression with interpolated alpha. 4-channel RGBA. 8 BPP.
	ATCI = 26
	# Adaptive Scalable Texture Compression, 4x4 block, RGBA. 8.00 BPP.
	ASTC4x4 = 27
	# Adaptive Scalable Texture Compression, 5x4 block, RGBA. 6.40 BPP.
	ASTC5x4 = 28
	# Adaptive Scalable Texture Compression, 5x5 block, RGBA. 5.12 BPP.
	ASTC5x5 = 29
	# Adaptive Scalable Texture Compression, 6x5 block, RGBA. 4.27 BPP.
	ASTC6x5 = 30
	# Adaptive Scalable Texture Compression, 6x6 block, RGBA. 3.56 BPP.
	ASTC6x6 = 31
	# Adaptive Scalable Texture Compression, 8x5 block, RGBA. 3.20 BPP.
	ASTC8x5 = 32
	# Adaptive Scalable Texture Compression, 8x6 block, RGBA. 2.67 BPP.
	ASTC8x6 = 33
	# Adaptive Scalable Texture Compression, 8x8 block, RGBA. 2.00 BPP.
	ASTC8x8 = 34
	# Adaptive Scalable Texture Compression, 10x5 block, RGBA. 2.56 BPP.
	ASTC10x5 = 35
	# Adaptive Scalable Texture Compression, 10x6 block, RGBA. 2.13 BPP.
	ASTC10x6 = 36
	# Adaptive Scalable Texture Compression, 10x8 block, RGBA. 1.60 BPP.
	ASTC10x8 = 37
	# Adaptive Scalable Texture Compression, 10x10 block, RGBA. 1.28 BPP.
	ASTC10x10 = 38
	# Adaptive Scalable Texture Compression, 12x10 block, RGBA. 1.07 BPP.
	ASTC12x10 = 39
	# Adaptive Scalable Texture Compression, 12x12 block, RGBA. 0.89 BPP.
	ASTC12x12 = 40
	# Compressed formats above.
	Unknown = 41
	# 1-bit single-channel red. Monochrome, 1-bit per pixel. 1 BPP.
	R1 = 42
	# 8-bit single-channel alpha, unsigned normalized. 8 BPP.
	A8 = 43
	# 8-bit single-channel red, unsigned normalized. 8 BPP.
	R8 = 44
	# 8-bit single-channel red, signed integer. 8 BPP.
	R8I = 45
	# 8-bit single-channel red, unsigned integer. 8 BPP.
	R8U = 46
	# 8-bit single-channel red, signed normalized. 8 BPP.
	R8S = 47
	# 16-bit single-channel red, unsigned normalized. 16 BPP.
	R16 = 48
	# 16-bit single-channel red, signed integer. 16 BPP.
	R16I = 49
	# 16-bit single-channel red, unsigned integer. 16 BPP.
	R16U = 50
	# 16-bit single-channel red, half-precision floating point. 16 BPP.
	R16F = 51
	# 16-bit single-channel red, signed normalized. 16 BPP.
	R16S = 52
	# 32-bit single-channel red, signed integer. 32 BPP.
	R32I = 53
	# 32-bit single-channel red, unsigned integer. 32 BPP.
	R32U = 54
	# 32-bit single-channel red, full-precision floating point. 32 BPP.
	R32F = 55
	# Two 8-bit channels (red, green), unsigned normalized. 16 BPP.
	RG8 = 56
	# Two 8-bit channels (red, green), signed integer. 16 BPP.
	RG8I = 57
	# Two 8-bit channels (red, green), unsigned integer. 16 BPP.
	RG8U = 58
	# Two 8-bit channels (red, green), signed normalized. 16 BPP.
	RG8S = 59
	# Two 16-bit channels (red, green), unsigned normalized. 32 BPP.
	RG16 = 60
	# Two 16-bit channels (red, green), signed integer. 32 BPP.
	RG16I = 61
	# Two 16-bit channels (red, green), unsigned integer. 32 BPP.
	RG16U = 62
	# Two 16-bit channels (red, green), half-precision floating point. 32 BPP.
	RG16F = 63
	# Two 16-bit channels (red, green), signed normalized. 32 BPP.
	RG16S = 64
	# Two 32-bit channels (red, green), signed integer. 64 BPP.
	RG32I = 65
	# Two 32-bit channels (red, green), unsigned integer. 64 BPP.
	RG32U = 66
	# Two 32-bit channels (red, green), full-precision floating point. 64 BPP.
	RG32F = 67
	# Three 8-bit channels (red, green, blue), unsigned normalized. 24 BPP.
	RGB8 = 68
	# Three 8-bit channels (red, green, blue), signed integer. 24 BPP.
	RGB8I = 69
	# Three 8-bit channels (red, green, blue), unsigned integer. 24 BPP.
	RGB8U = 70
	# Three 8-bit channels (red, green, blue), signed normalized. 24 BPP.
	RGB8S = 71
	# Shared-exponent RGB. 9 bits per RGB channel with a shared 5-bit exponent, floating point. 32 BPP.
	RGB9E5F = 72
	# Four 8-bit channels (blue, green, red, alpha), unsigned normalized. BGRA byte order. 32 BPP.
	BGRA8 = 73
	# Four 8-bit channels (red, green, blue, alpha), unsigned normalized. 32 BPP.
	RGBA8 = 74
	# Four 8-bit channels (red, green, blue, alpha), signed integer. 32 BPP.
	RGBA8I = 75
	# Four 8-bit channels (red, green, blue, alpha), unsigned integer. 32 BPP.
	RGBA8U = 76
	# Four 8-bit channels (red, green, blue, alpha), signed normalized. 32 BPP.
	RGBA8S = 77
	# Four 16-bit channels (red, green, blue, alpha), unsigned normalized. 64 BPP.
	RGBA16 = 78
	# Four 16-bit channels (red, green, blue, alpha), signed integer. 64 BPP.
	RGBA16I = 79
	# Four 16-bit channels (red, green, blue, alpha), unsigned integer. 64 BPP.
	RGBA16U = 80
	# Four 16-bit channels (red, green, blue, alpha), half-precision floating point. 64 BPP.
	RGBA16F = 81
	# Four 16-bit channels (red, green, blue, alpha), signed normalized. 64 BPP.
	RGBA16S = 82
	# Four 32-bit channels (red, green, blue, alpha), signed integer. 128 BPP.
	RGBA32I = 83
	# Four 32-bit channels (red, green, blue, alpha), unsigned integer. 128 BPP.
	RGBA32U = 84
	# Four 32-bit channels (red, green, blue, alpha), full-precision floating point. 128 BPP.
	RGBA32F = 85
	# Packed 16-bit, 5-bit blue, 6-bit green, 5-bit red. BGR byte order, unsigned normalized. 16 BPP.
	B5G6R5 = 86
	# Packed 16-bit, 5-bit red, 6-bit green, 5-bit blue. RGB byte order, unsigned normalized. 16 BPP.
	R5G6B5 = 87
	# Packed 16-bit, 4-bit per channel (blue, green, red, alpha). BGRA byte order, unsigned normalized. 16 BPP.
	BGRA4 = 88
	# Packed 16-bit, 4-bit per channel (red, green, blue, alpha), unsigned normalized. 16 BPP.
	RGBA4 = 89
	# Packed 16-bit, 5-bit blue, 5-bit green, 5-bit red, 1-bit alpha. BGRA byte order, unsigned normalized. 16 BPP.
	BGR5A1 = 90
	# Packed 16-bit, 5-bit red, 5-bit green, 5-bit blue, 1-bit alpha, unsigned normalized. 16 BPP.
	RGB5A1 = 91
	# Packed 32-bit, 10-bit red, 10-bit green, 10-bit blue, 2-bit alpha, unsigned normalized. 32 BPP.
	RGB10A2 = 92
	# Packed 32-bit, 10-bit red, 10-bit green, 10-bit blue, 2-bit alpha, unsigned integer. 32 BPP.
	RGB10A2U = 93
	# Packed 32-bit, 11-bit red, 11-bit green, 10-bit blue, unsigned floating point. No alpha. 32 BPP.
	RG11B10F = 94
	# Depth formats below.
	UnknownDepth = 95
	# 16-bit depth, unsigned normalized. 16 BPP.
	D16 = 96
	# 24-bit depth, unsigned normalized (stored as 32-bit with 8 bits unused). 32 BPP.
	D24 = 97
	# 24-bit depth, unsigned normalized, with 8-bit stencil. 32 BPP.
	D24S8 = 98
	# 32-bit depth, unsigned normalized. 32 BPP.
	D32 = 99
	# 16-bit depth, floating point. 16 BPP.
	D16F = 100
	# 24-bit depth, floating point (stored as 32-bit). 32 BPP.
	D24F = 101
	# 32-bit depth, floating point. 32 BPP.
	D32F = 102
	# 32-bit depth, floating point, with 8-bit stencil (stored as 64-bit). 64 BPP.
	D32FS8 = 103
	# 8-bit stencil only, no depth. 8 BPP.
	D0S8 = 104
	Count = 105

# Uniform type enum.
class UniformType(enum.IntEnum):
	# Sampler.
	Sampler = 0
	# Reserved, do not use.
	End = 1
	# 4 floats vector.
	Vec4 = 2
	# 3x3 matrix.
	Mat3 = 3
	# 4x4 matrix.
	Mat4 = 4
	Count = 5

# Uniform frequency enum.
class UniformFreq(enum.IntEnum):
	# Changing per draw call.
	Draw = 0
	# Changing per view.
	View = 1
	# Changing per frame.
	Frame = 2
	Count = 3

# Backbuffer ratio enum.
class BackbufferRatio(enum.IntEnum):
	# Equal to backbuffer.
	Equal = 0
	# One half size of backbuffer.
	Half = 1
	# One quarter size of backbuffer.
	Quarter = 2
	# One eighth size of backbuffer.
	Eighth = 3
	# One sixteenth size of backbuffer.
	Sixteenth = 4
	# Double size of backbuffer.
	Double = 5
	Count = 6

# Occlusion query result.
class OcclusionQueryResult(enum.IntEnum):
	# Query failed test.
	Invisible = 0
	# Query passed test.
	Visible = 1
	# Query result is not available yet.
	NoResult = 2
	Count = 3

# Video codec enum.
class VideoCodec(enum.IntEnum):
	# H.264 / AVC.
	H264 = 0
	# H.265 / HEVC.
	H265 = 1
	# AV1.
	AV1 = 2
	Count = 3

# Primitive topology.
class Topology(enum.IntEnum):
	# Triangle list.
	TriList = 0
	# Triangle strip.
	TriStrip = 1
	# Line list.
	LineList = 2
	# Line strip.
	LineStrip = 3
	# Point list.
	PointList = 4
	Count = 5

# Topology conversion function.
class TopologyConvert(enum.IntEnum):
	# Flip winding order of triangle list.
	TriListFlipWinding = 0
	# Flip winding order of triangle strip.
	TriStripFlipWinding = 1
	# Convert triangle list to line list.
	TriListToLineList = 2
	# Convert triangle strip to triangle list.
	TriStripToTriList = 3
	# Convert line strip to line list.
	LineStripToLineList = 4
	Count = 5

# Topology sort order.
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

# View mode sets draw call sort order.
class ViewMode(enum.IntEnum):
	# Default sort order.
	Default = 0
	# Sort in the same order in which submit calls were called.
	Sequential = 1
	# Sort draw call depth in ascending order.
	DepthAscending = 2
	# Sort draw call depth in descending order.
	DepthDescending = 3
	Count = 4

# Shading Rate.
class ShadingRate(enum.IntEnum):
	# 1x1
	Rate1x1 = 0
	# 1x2
	Rate1x2 = 1
	# 2x1
	Rate2x1 = 2
	# 2x2
	Rate2x2 = 3
	# 2x4
	Rate2x4 = 4
	# 4x2
	Rate4x2 = 5
	# 4x4
	Rate4x4 = 6
	Count = 7

# Native window handle type.
class NativeWindowHandleType(enum.IntEnum):
	# Platform default handle type (X11 on Linux).
	Default = 0
	# Wayland.
	Wayland = 1
	Count = 2

# Render frame enum.
class RenderFrame(enum.IntEnum):
	# Renderer context is not created yet.
	NoContext = 0
	# Renderer context is created and rendering.
	Render = 1
	# Renderer context wait for main thread signal timed out without rendering.
	Timeout = 2
	# Renderer context is getting destroyed.
	Exiting = 3
	Count = 4

class StateFlags(enum.IntFlag):
	# Enable R write.
	WriteR = 0x1
	# Enable G write.
	WriteG = 0x2
	# Enable B write.
	WriteB = 0x4
	# Enable alpha write.
	WriteA = 0x8
	# Enable depth write.
	WriteZ = 0x4000000000
	# Enable RGB write.
	WriteRgb = 0x7
	# Write all channels mask.
	WriteMask = 0x400000000f
	# Enable depth test, less.
	DepthTestLess = 0x10
	# Enable depth test, less or equal.
	DepthTestLequal = 0x20
	# Enable depth test, equal.
	DepthTestEqual = 0x30
	# Enable depth test, greater or equal.
	DepthTestGequal = 0x40
	# Enable depth test, greater.
	DepthTestGreater = 0x50
	# Enable depth test, not equal.
	DepthTestNotequal = 0x60
	# Enable depth test, never.
	DepthTestNever = 0x70
	# Enable depth test, always.
	DepthTestAlways = 0x80
	# Depth test state. When `BGFX_STATE_DEPTH_` is not specified depth test will be disabled.
	DepthTestShift = 0x4
	# Depth test state. When `BGFX_STATE_DEPTH_` is not specified depth test will be disabled.
	DepthTestMask = 0xf0
	# 0, 0, 0, 0
	BlendZero = 0x1000
	# 1, 1, 1, 1
	BlendOne = 0x2000
	# Rs, Gs, Bs, As
	BlendSrcColor = 0x3000
	# 1-Rs, 1-Gs, 1-Bs, 1-As
	BlendInvSrcColor = 0x4000
	# As, As, As, As
	BlendSrcAlpha = 0x5000
	# 1-As, 1-As, 1-As, 1-As
	BlendInvSrcAlpha = 0x6000
	# Ad, Ad, Ad, Ad
	BlendDstAlpha = 0x7000
	# 1-Ad, 1-Ad, 1-Ad ,1-Ad
	BlendInvDstAlpha = 0x8000
	# Rd, Gd, Bd, Ad
	BlendDstColor = 0x9000
	# 1-Rd, 1-Gd, 1-Bd, 1-Ad
	BlendInvDstColor = 0xa000
	# f, f, f, 1; f = min(As, 1-Ad)
	BlendSrcAlphaSat = 0xb000
	# Blend factor
	BlendFactor = 0xc000
	# 1-Blend factor
	BlendInvFactor = 0xd000
	# Use BGFX_STATE_BLEND_FUNC(_src, _dst) or BGFX_STATE_BLEND_FUNC_SEPARATE(_srcRGB, _dstRGB, _srcA, _dstA)
	# helper macros.
	BlendShift = 0xc
	# Use BGFX_STATE_BLEND_FUNC(_src, _dst) or BGFX_STATE_BLEND_FUNC_SEPARATE(_srcRGB, _dstRGB, _srcA, _dstA)
	# helper macros.
	BlendMask = 0xffff000
	# Blend add: src + dst.
	BlendEquationAdd = 0x0
	# Blend subtract: src - dst.
	BlendEquationSub = 0x10000000
	# Blend reverse subtract: dst - src.
	BlendEquationRevsub = 0x20000000
	# Blend min: min(src, dst).
	BlendEquationMin = 0x30000000
	# Blend max: max(src, dst).
	BlendEquationMax = 0x40000000
	# Use BGFX_STATE_BLEND_EQUATION(_equation) or BGFX_STATE_BLEND_EQUATION_SEPARATE(_equationRGB, _equationA)
	# helper macros.
	BlendEquationShift = 0x1c
	# Use BGFX_STATE_BLEND_EQUATION(_equation) or BGFX_STATE_BLEND_EQUATION_SEPARATE(_equationRGB, _equationA)
	# helper macros.
	BlendEquationMask = 0x3f0000000
	# Cull clockwise triangles.
	CullCw = 0x1000000000
	# Cull counter-clockwise triangles.
	CullCcw = 0x2000000000
	# Cull state. When `BGFX_STATE_CULL_*` is not specified culling will be disabled.
	CullShift = 0x24
	# Cull state. When `BGFX_STATE_CULL_*` is not specified culling will be disabled.
	CullMask = 0x3000000000
	# Alpha reference value.
	AlphaRefShift = 0x28
	# Alpha reference value.
	AlphaRefMask = 0xff0000000000
	# Tristrip.
	PtTristrip = 0x1000000000000
	# Lines.
	PtLines = 0x2000000000000
	# Line strip.
	PtLinestrip = 0x3000000000000
	# Points.
	PtPoints = 0x4000000000000
	PtShift = 0x30
	PtMask = 0x7000000000000
	# Point size value.
	PointSizeShift = 0x34
	# Point size value.
	PointSizeMask = 0xf0000000000000
	# Enable MSAA rasterization.
	Msaa = 0x100000000000000
	# Enable line AA rasterization.
	Lineaa = 0x200000000000000
	# Enable conservative rasterization.
	ConservativeRaster = 0x400000000000000
	# No state.
	None_ = 0x0
	# Front counter-clockwise (default is clockwise).
	FrontCcw = 0x8000000000
	# Enable blend independent.
	BlendIndependent = 0x400000000
	# Enable alpha to coverage.
	BlendAlphaToCoverage = 0x800000000
	# Default state is write to RGB, alpha, and depth with depth test less enabled, with clockwise
	# culling and MSAA (when writing into MSAA frame buffer, otherwise this flag is ignored).
	Default = 0x10000500000001f
	# Enable MSAA write when writing into MSAA frame buffer.
	# This flag is ignored when not writing into MSAA frame buffer.
	Mask = 0xffffffffffffffff
	# Do not use!
	ReservedShift = 0x3d
	# Do not use!
	ReservedMask = 0xe000000000000000

class StencilFlags(enum.IntFlag):
	# Set stencil ref value.
	FuncRefShift = 0x0
	# Set stencil ref value.
	FuncRefMask = 0xff
	# Set stencil rmask value.
	FuncRmaskShift = 0x8
	# Set stencil rmask value.
	FuncRmaskMask = 0xff00
	# No stencil test.
	None_ = 0xff00
	# Stencil front or back mask.
	Mask = 0xffffffff
	# Enable stencil test, less.
	TestLess = 0x10000
	# Enable stencil test, less or equal.
	TestLequal = 0x20000
	# Enable stencil test, equal.
	TestEqual = 0x30000
	# Enable stencil test, greater or equal.
	TestGequal = 0x40000
	# Enable stencil test, greater.
	TestGreater = 0x50000
	# Enable stencil test, not equal.
	TestNotequal = 0x60000
	# Enable stencil test, never.
	TestNever = 0x70000
	# Enable stencil test, always.
	TestAlways = 0x80000
	TestShift = 0x10
	TestMask = 0xf0000
	# Zero.
	OpFailSZero = 0x0
	# Keep.
	OpFailSKeep = 0x100000
	# Replace.
	OpFailSReplace = 0x200000
	# Increment and wrap.
	OpFailSIncr = 0x300000
	# Increment and clamp.
	OpFailSIncrsat = 0x400000
	# Decrement and wrap.
	OpFailSDecr = 0x500000
	# Decrement and clamp.
	OpFailSDecrsat = 0x600000
	# Invert.
	OpFailSInvert = 0x700000
	OpFailSShift = 0x14
	OpFailSMask = 0xf00000
	# Zero.
	OpFailZZero = 0x0
	# Keep.
	OpFailZKeep = 0x1000000
	# Replace.
	OpFailZReplace = 0x2000000
	# Increment and wrap.
	OpFailZIncr = 0x3000000
	# Increment and clamp.
	OpFailZIncrsat = 0x4000000
	# Decrement and wrap.
	OpFailZDecr = 0x5000000
	# Decrement and clamp.
	OpFailZDecrsat = 0x6000000
	# Invert.
	OpFailZInvert = 0x7000000
	OpFailZShift = 0x18
	OpFailZMask = 0xf000000
	# Zero.
	OpPassZZero = 0x0
	# Keep.
	OpPassZKeep = 0x10000000
	# Replace.
	OpPassZReplace = 0x20000000
	# Increment and wrap.
	OpPassZIncr = 0x30000000
	# Increment and clamp.
	OpPassZIncrsat = 0x40000000
	# Decrement and wrap.
	OpPassZDecr = 0x50000000
	# Decrement and clamp.
	OpPassZDecrsat = 0x60000000
	# Invert.
	OpPassZInvert = 0x70000000
	OpPassZShift = 0x1c
	OpPassZMask = 0xf0000000

class BufferFlags(enum.IntFlag):
	# 1 x 8-bit value
	ComputeFormat8x1 = 0x1
	# 2 x 8-bit values
	ComputeFormat8x2 = 0x2
	# 4 x 8-bit values
	ComputeFormat8x4 = 0x3
	# 1 x 16-bit value
	ComputeFormat16x1 = 0x4
	# 2 x 16-bit values
	ComputeFormat16x2 = 0x5
	# 4 x 16-bit values
	ComputeFormat16x4 = 0x6
	# 1 x 32-bit value
	ComputeFormat32x1 = 0x7
	# 2 x 32-bit values
	ComputeFormat32x2 = 0x8
	# 4 x 32-bit values
	ComputeFormat32x4 = 0x9
	ComputeFormatShift = 0x0
	ComputeFormatMask = 0xf
	# Type `int`.
	ComputeTypeInt = 0x10
	# Type `uint`.
	ComputeTypeUint = 0x20
	# Type `float`.
	ComputeTypeFloat = 0x30
	ComputeTypeShift = 0x4
	ComputeTypeMask = 0x30
	None_ = 0x0
	# Buffer will be read by shader.
	ComputeRead = 0x100
	# Buffer will be used for writing.
	ComputeWrite = 0x200
	# Buffer will be used for storing draw indirect commands.
	DrawIndirect = 0x400
	# Allow dynamic index/vertex buffer resize during update.
	AllowResize = 0x800
	# Index buffer contains 32-bit indices.
	Index32 = 0x1000
	ComputeReadWrite = 0x300

class TextureFlags(enum.IntFlag):
	None_ = 0x0
	# Texture will be used for MSAA sampling.
	MsaaSample = 0x800000000
	# Render target no MSAA.
	Rt = 0x1000000000
	# Texture will be used for compute write.
	ComputeWrite = 0x100000000000
	# Sample texture as sRGB.
	Srgb = 0x200000000000
	# Texture will be used as blit destination.
	BlitDst = 0x400000000000
	# Texture will be used for read back from GPU.
	ReadBack = 0x800000000000
	# Texture is shared with other device or other process.
	ExternalShared = 0x1000000000000
	# Do not use! Top nibble is reserved for internal texture flags (see bgfx_p.h).
	ReservedShift = 0x3c
	# Do not use! Top nibble is reserved for internal texture flags (see bgfx_p.h).
	ReservedMask = 0xf000000000000000
	# Render target MSAAx2 mode.
	RtMsaaX2 = 0x2000000000
	# Render target MSAAx4 mode.
	RtMsaaX4 = 0x3000000000
	# Render target MSAAx8 mode.
	RtMsaaX8 = 0x4000000000
	# Render target MSAAx16 mode.
	RtMsaaX16 = 0x5000000000
	RtMsaaShift = 0x24
	RtMsaaMask = 0x7000000000
	# Render target will be used for writing
	RtWriteOnly = 0x8000000000
	RtShift = 0x24
	RtMask = 0xf000000000

class SamplerFlags(enum.IntFlag):
	# Wrap U mode: Mirror
	UMirror = 0x1
	# Wrap U mode: Clamp
	UClamp = 0x2
	# Wrap U mode: Border
	UBorder = 0x3
	# Sampler flags.
	UShift = 0x0
	# Sampler flags.
	UMask = 0x3
	# Wrap V mode: Mirror
	VMirror = 0x4
	# Wrap V mode: Clamp
	VClamp = 0x8
	# Wrap V mode: Border
	VBorder = 0xc
	VShift = 0x2
	VMask = 0xc
	# Wrap W mode: Mirror
	WMirror = 0x10
	# Wrap W mode: Clamp
	WClamp = 0x20
	# Wrap W mode: Border
	WBorder = 0x30
	WShift = 0x4
	WMask = 0x30
	# Min sampling mode: Point
	MinPoint = 0x40
	# Min sampling mode: Anisotropic
	MinAnisotropic = 0x80
	MinShift = 0x6
	MinMask = 0xc0
	# Mag sampling mode: Point
	MagPoint = 0x100
	# Mag sampling mode: Anisotropic
	MagAnisotropic = 0x200
	MagShift = 0x8
	MagMask = 0x300
	# Mip sampling mode: Point
	MipPoint = 0x400
	MipShift = 0xa
	MipMask = 0x400
	# Compare when sampling depth texture: less.
	CompareLess = 0x10000
	# Compare when sampling depth texture: less or equal.
	CompareLequal = 0x20000
	# Compare when sampling depth texture: equal.
	CompareEqual = 0x30000
	# Compare when sampling depth texture: greater or equal.
	CompareGequal = 0x40000
	# Compare when sampling depth texture: greater.
	CompareGreater = 0x50000
	# Compare when sampling depth texture: not equal.
	CompareNotequal = 0x60000
	# Compare when sampling depth texture: never.
	CompareNever = 0x70000
	# Compare when sampling depth texture: always.
	CompareAlways = 0x80000
	CompareShift = 0x10
	CompareMask = 0xf0000
	BorderColorShift = 0x18
	BorderColorMask = 0xf000000
	ReservedShift = 0x1c
	ReservedMask = 0xf0000000
	None_ = 0x0
	# Sample stencil instead of depth.
	SampleStencil = 0x100000
	Point = 0x540
	UvwMirror = 0x15
	UvwClamp = 0x2a
	UvwBorder = 0x3f
	BitsMask = 0xf07ff

class ResetFlags(enum.IntFlag):
	# Enable 2x MSAA.
	MsaaX2 = 0x10
	# Enable 4x MSAA.
	MsaaX4 = 0x20
	# Enable 8x MSAA.
	MsaaX8 = 0x30
	# Enable 16x MSAA.
	MsaaX16 = 0x40
	MsaaShift = 0x4
	MsaaMask = 0x70
	# No reset flags.
	None_ = 0x0
	# Not supported yet.
	Fullscreen = 0x1
	# Enable V-Sync.
	Vsync = 0x80
	# Turn on/off max anisotropy.
	Maxanisotropy = 0x100
	# Begin screen capture.
	Capture = 0x200
	# Flush rendering after submitting to GPU.
	FlushAfterRender = 0x2000
	# This flag specifies where flip occurs. Default behaviour is that flip occurs
	# before rendering new frame. This flag only has effect when `BGFX_CONFIG_MULTITHREADED=0`.
	FlipAfterRender = 0x4000
	# Enable sRGB backbuffer.
	SrgbBackbuffer = 0x8000
	# Enable HDR10 rendering.
	Hdr10 = 0x10000
	# Enable HiDPI rendering.
	Hidpi = 0x20000
	# Enable depth clamp.
	DepthClamp = 0x40000
	# Suspend rendering.
	Suspend = 0x80000
	# Transparent backbuffer. Availability depends on: `BGFX_CAPS_TRANSPARENT_BACKBUFFER`.
	TransparentBackbuffer = 0x100000
	FullscreenShift = 0x0
	FullscreenMask = 0x1
	ReservedShift = 0x1f
	ReservedMask = 0x80000000

class ClearFlags(enum.IntFlag):
	# No clear flags.
	None_ = 0x0
	# Clear color.
	Color = 0x1
	# Clear depth.
	Depth = 0x2
	# Clear stencil.
	Stencil = 0x4
	# Discard frame buffer attachment 0.
	DiscardColor_0 = 0x8
	# Discard frame buffer attachment 1.
	DiscardColor_1 = 0x10
	# Discard frame buffer attachment 2.
	DiscardColor_2 = 0x20
	# Discard frame buffer attachment 3.
	DiscardColor_3 = 0x40
	# Discard frame buffer attachment 4.
	DiscardColor_4 = 0x80
	# Discard frame buffer attachment 5.
	DiscardColor_5 = 0x100
	# Discard frame buffer attachment 6.
	DiscardColor_6 = 0x200
	# Discard frame buffer attachment 7.
	DiscardColor_7 = 0x400
	# Discard frame buffer depth attachment.
	DiscardDepth = 0x800
	# Discard frame buffer stencil attachment.
	DiscardStencil = 0x1000
	DiscardColorMask = 0x7f8
	DiscardMask = 0x1ff8

class DiscardFlags(enum.IntFlag):
	# Preserve everything.
	None_ = 0x0
	# Discard texture sampler and buffer bindings.
	Bindings = 0x1
	# Discard index buffer.
	IndexBuffer = 0x2
	# Discard instance data.
	InstanceData = 0x4
	# Discard state and uniform bindings.
	State = 0x8
	# Discard transform.
	Transform = 0x10
	# Discard vertex streams.
	VertexStreams = 0x20
	# Discard all states.
	All = 0xff

class DebugFlags(enum.IntFlag):
	# No debug.
	None_ = 0x0
	# Enable wireframe for all primitives.
	Wireframe = 0x1
	# Enable infinitely fast hardware test. No draw calls will be submitted to driver.
	# It's useful when profiling to quickly assess bottleneck between CPU and GPU.
	Ifh = 0x2
	# Enable statistics display.
	Stats = 0x4
	# Enable debug text display.
	Text = 0x8
	# Enable profiler. This causes per-view statistics to be collected, available through `bgfx::Stats::ViewStats`. This is unrelated to the profiler functions in `bgfx::CallbackI`.
	Profiler = 0x10

class CapsFlags(enum.IntFlag):
	# Alpha to coverage is supported.
	AlphaToCoverage = 0x1
	# Blend independent is supported.
	BlendIndependent = 0x2
	# Compute shaders are supported.
	Compute = 0x4
	# Conservative rasterization is supported.
	ConservativeRaster = 0x8
	# Draw indirect is supported.
	DrawIndirect = 0x10
	# Draw indirect with indirect count is supported.
	DrawIndirectCount = 0x20
	# Fragment depth is available in fragment shader.
	FragmentDepth = 0x40
	# Fragment ordering is available in fragment shader.
	FragmentOrdering = 0x80
	# Graphics debugger is present.
	GraphicsDebugger = 0x100
	# HDR10 rendering is supported.
	Hdr10 = 0x200
	# HiDPI rendering is supported.
	Hidpi = 0x400
	# Image Read/Write is supported.
	ImageRw = 0x800
	# 32-bit indices are supported.
	Index32 = 0x1000
	# Instancing is supported.
	Instancing = 0x2000
	# Occlusion query is supported.
	OcclusionQuery = 0x4000
	# PrimitiveID is available in fragment shader.
	PrimitiveId = 0x8000
	# Renderer is on separate thread.
	RendererMultithreaded = 0x10000
	# Multiple windows are supported.
	SwapChain = 0x20000
	# Texture blit is supported.
	TextureBlit = 0x40000
	# Texture compare less equal mode is supported.
	TextureCompareLequal = 0x80000
	TextureCompareReserved = 0x100000
	# Cubemap texture array is supported.
	TextureCubeArray = 0x200000
	# CPU direct access to GPU texture memory.
	TextureDirectAccess = 0x400000
	# External texture is supported.
	TextureExternal = 0x800000
	# External shared texture is supported.
	TextureExternalShared = 0x1000000
	# Read-back texture is supported.
	TextureReadBack = 0x2000000
	# 2D texture array is supported.
	Texture_2dArray = 0x4000000
	# 3D textures are supported.
	Texture_3d = 0x8000000
	# Transparent back buffer supported.
	TransparentBackbuffer = 0x10000000
	# Variable Rate Shading
	VariableRateShading = 0x20000000
	# Vertex attribute half-float is supported.
	VertexAttribHalf = 0x40000000
	# Vertex attribute 10_10_10_2 is supported.
	VertexAttribUint10 = 0x80000000
	# Rendering with VertexID only is supported.
	VertexId = 0x100000000
	# Hardware video decode is supported.
	VideoDecode = 0x200000000
	# Viewport layer is available in vertex shader.
	ViewportLayerArray = 0x400000000
	# All texture compare modes are supported.
	TextureCompareAll = 0x180000

class CapsFormatFlags(enum.IntFlag):
	# Texture format is not supported.
	TextureNone = 0x0
	# Texture format is supported.
	Texture_2d = 0x1
	# Texture as sRGB format is supported.
	Texture_2dSrgb = 0x2
	# Texture format is emulated.
	Texture_2dEmulated = 0x4
	# Texture format is supported.
	Texture_3d = 0x8
	# Texture as sRGB format is supported.
	Texture_3dSrgb = 0x10
	# Texture format is emulated.
	Texture_3dEmulated = 0x20
	# Texture format is supported.
	TextureCube = 0x40
	# Texture as sRGB format is supported.
	TextureCubeSrgb = 0x80
	# Texture format is emulated.
	TextureCubeEmulated = 0x100
	# Texture format can be used from vertex shader.
	TextureVertex = 0x200
	# Texture format can be used as image and read from.
	TextureImageRead = 0x400
	# Texture format can be used as image and written to.
	TextureImageWrite = 0x800
	# Texture format can be used as frame buffer.
	TextureFramebuffer = 0x1000
	# Texture format can be used as MSAA frame buffer.
	TextureFramebufferMsaa = 0x2000
	# Texture can be sampled as MSAA.
	TextureMsaa = 0x4000
	# Texture format supports auto-generated mips.
	TextureMipAutogen = 0x8000
	# Texture format can be used as back buffer format.
	TextureBackbuffer = 0x10000
	# Texture format can be used as video decode destination.
	TextureVideoDecodeDst = 0x20000

class CapsVideoCodecFlags(enum.IntFlag):
	# Video codec is not supported.
	None_ = 0x0
	# 8-bit sample depth is supported.
	Bit_8 = 0x1
	# 10-bit sample depth is supported.
	Bit_10 = 0x2
	# 12-bit sample depth is supported.
	Bit_12 = 0x4
	# 4:2:0 chroma subsampling is supported.
	Chroma_420 = 0x8
	# 4:2:2 chroma subsampling is supported.
	Chroma_422 = 0x10
	# 4:4:4 chroma subsampling is supported.
	Chroma_444 = 0x20

class VideoDecoderInitFlags(enum.IntFlag):
	# No flags.
	None_ = 0x0
	# Cache submitted access units in driver-managed memory keyed by `ptsUs` so the
	# presentation clock can revisit / loop without re-streaming. The cache is
	# unbounded: the app picks the total cache size implicitly by choosing how
	# many access units to submit. Without this flag access units are decoded once
	# and dropped (streaming default).
	Retain = 0x1

class VideoDecodeFrameFlags(enum.IntFlag):
	# No flags.
	None_ = 0x0
	# First batch after a position change. The first access unit must be a clean IDR.
	# Driver flushes its DPB, queued access units, and reorder pool before decoding;
	# subsequent `presentationTimeUs` values may land anywhere (monotonicity is only
	# required between non-`Set` ticks).
	Set = 0x1
	# Skip the picker dispatch for this call. Useful while bulk-loading access units
	# so the displayed picture isn't churned mid-load.
	NoBlit = 0x2
	# Marks the last access unit of the clip; permits eager pre-decode in idle time
	# and lets the picker emit the final frame without lookahead stalling.
	Final = 0x4
	# When `presentationTimeUs` runs past the highest cached `ptsUs`, the picker
	# wraps modulo the cached pts range. Without this flag the picker freezes on
	# the last displayable picture.
	Loop = 0x8

class ResolveFlags(enum.IntFlag):
	# No resolve flags.
	None_ = 0x0
	# Auto-generate mip maps on resolve.
	AutoGenMips = 0x1

class PciIdFlags(enum.IntFlag):
	# Autoselect adapter.
	None_ = 0x0
	# Software rasterizer.
	SoftwareRasterizer = 0x1
	# AMD adapter.
	Amd = 0x1002
	# Apple adapter.
	Apple = 0x106b
	# Intel adapter.
	Intel = 0x8086
	# nVidia adapter.
	Nvidia = 0x10de
	# Microsoft adapter.
	Microsoft = 0x1414
	# ARM adapter.
	Arm = 0x13b5

class CubeMapFlags(enum.IntFlag):
	# Cubemap +x.
	PositiveX = 0x0
	# Cubemap -x.
	NegativeX = 0x1
	# Cubemap +y.
	PositiveY = 0x2
	# Cubemap -y.
	NegativeY = 0x3
	# Cubemap +z.
	PositiveZ = 0x4
	# Cubemap -z.
	NegativeZ = 0x5

class FrameFlags(enum.IntFlag):
	# No frame flags.
	None_ = 0x0
	# Capture frame with graphics debugger.
	DebugCapture = 0x1
	# Discard all draw calls.
	Discard = 0x2
	# Execute all rendering commands without presenting the backbuffer.
	Flush = 0x4

# GPU info.
class CapsGPU(ctypes.Structure):
	pass

# Renderer runtime limits.
class CapsLimits(ctypes.Structure):
	pass

# Renderer capabilities.
class Caps(ctypes.Structure):
	pass

# Internal data.
class InternalData(ctypes.Structure):
	pass

# Platform data.
class PlatformData(ctypes.Structure):
	pass

# Backbuffer resolution and reset parameters.
class Resolution(ctypes.Structure):
	pass

# Configurable runtime limits parameters.
class InitLimits(ctypes.Structure):
	pass

# Initialization parameters used by `bgfx::init`.
class Init(ctypes.Structure):
	pass

# Memory must be obtained by calling `bgfx::alloc`, `bgfx::copy`, or `bgfx::makeRef`.
# 
# @attention It is illegal to create this structure on stack and pass it to any bgfx API.
class Memory(ctypes.Structure):
	pass

# Transient index buffer.
class TransientIndexBuffer(ctypes.Structure):
	pass

# Transient vertex buffer.
class TransientVertexBuffer(ctypes.Structure):
	pass

# Instance data buffer info.
class InstanceDataBuffer(ctypes.Structure):
	pass

# Texture info.
class TextureInfo(ctypes.Structure):
	pass

# Video decoder initialization. Serialized into the Memory passed to
# `createTexture2D`. When the memory blob begins with `magic`, bgfx
# infers the texture is a video decode destination (the caller need not set
# any extra texture flag). Everything else the renderer needs about the
# stream (chroma format, bit depth, profile, level, coded dimensions, DPB
# layout, color metadata) is parsed out of the codec parameter sets at
# create time.
class VideoDecoderInit(ctypes.Structure):
	pass

# One access unit entry inside a `VideoDecoderFrame` batch. The bitstream
# for the AU lives at offset `Σ aus[0..ii].size` inside the frame's
# `bitstream` buffer (access units are stored back-to-back in decode /
# submission order).
class VideoDecoderAu(ctypes.Structure):
	pass

# Video decoder per-frame submission. Serialized into the Memory passed
# to `updateTexture2D` for a video decode destination texture. The
# renderer parses the slice / tile-group header out of the bitstream and
# translates it to the backend-specific decoder arguments.
# 
# A single call may submit a batch of access units: `bitstream` is the
# back-to-back concatenation of `numAus` access units, and `aus[ii]`
# holds the size and PTS of each. AUs are enqueued in array order
# (which is the codec's decode order). Set `numAus == 0` (and
# `bitstream == NULL`) for a presentation-only tick that only advances
# the playback clock.
# 
# The `bitstream` and `aus` pointers must remain valid until bgfx has
# consumed the submission (`bgfx::copy` only deep-copies the
# `VideoDecoderFrame` struct itself, not the buffers it references).
class VideoDecoderFrame(ctypes.Structure):
	pass

# Uniform info.
class UniformInfo(ctypes.Structure):
	pass

# Frame buffer texture attachment info.
class Attachment(ctypes.Structure):
	pass

# Transform data.
class Transform(ctypes.Structure):
	pass

# View stats.
class ViewStats(ctypes.Structure):
	pass

# Encoder stats.
class EncoderStats(ctypes.Structure):
	pass

# Renderer statistics data.
# 
# @remarks All time values are high-resolution timestamps, while
# time frequencies define timestamps-per-second for that hardware.
class Stats(ctypes.Structure):
	pass

# Vertex layout.
class VertexLayout(ctypes.Structure):
	pass

# Encoders are used for submitting draw calls from multiple threads. Only one encoder
# per thread should be used. Use `bgfx::begin()` to obtain an encoder for a thread.
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
	bgfx_read_texture.argtypes = [TextureHandle, ctypes.c_void_p, ctypes.c_uint16, ctypes.c_uint8]
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
	bgfx_encoder_blit.argtypes = [ctypes.POINTER(Encoder), ctypes.c_uint16, TextureHandle, ctypes.c_uint8, ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint16, TextureHandle, ctypes.c_uint8, ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint16]
	bgfx_encoder_blit.restype = None
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
	bgfx_blit.argtypes = [ctypes.c_uint16, TextureHandle, ctypes.c_uint8, ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint16, TextureHandle, ctypes.c_uint8, ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint16]
	bgfx_blit.restype = None
