# Copyright 2011-2026 Branimir Karadzic. All rights reserved.
# License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE

#
# AUTO GENERATED! DO NOT EDIT!
#

import ctypes
import enum
from typing import Any, Optional, Protocol, TypeVar, Union

ViewId = ctypes.c_uint16

_T = TypeVar("_T", covariant=True)

class _Pointer(Protocol[_T]):
	@property
	def contents(self) -> _T: ...

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
	# Vendor PCI id. See `BGFX_PCI_ID_*`.
	vendorId: int
	# Device id.
	deviceId: int

# Renderer runtime limits.
class CapsLimits(ctypes.Structure):
	# Maximum number of draw calls.
	maxDrawCalls: int
	# Maximum number of blit calls.
	maxBlits: int
	# Maximum texture size.
	maxTextureSize: int
	# Maximum texture layers.
	maxTextureLayers: int
	# Maximum number of views.
	maxViews: int
	# Maximum number of frame buffer handles.
	maxFrameBuffers: int
	# Maximum number of frame buffer attachments.
	maxFBAttachments: int
	# Maximum number of program handles.
	maxPrograms: int
	# Maximum number of shader handles.
	maxShaders: int
	# Maximum number of texture handles.
	maxTextures: int
	# Maximum number of texture samplers.
	maxTextureSamplers: int
	# Maximum number of compute bindings.
	maxComputeBindings: int
	# Maximum number of vertex format layouts.
	maxVertexLayouts: int
	# Maximum number of vertex streams.
	maxVertexStreams: int
	# Maximum number of vertex attributes.
	maxVertexAttributes: int
	# Maximum number of instance data slots.
	maxInstanceData: int
	# Maximum number of index buffer handles.
	maxIndexBuffers: int
	# Maximum number of vertex buffer handles.
	maxVertexBuffers: int
	# Maximum number of dynamic index buffer handles.
	maxDynamicIndexBuffers: int
	# Maximum number of dynamic vertex buffer handles.
	maxDynamicVertexBuffers: int
	# Maximum number of uniform handles.
	maxUniforms: int
	# Maximum number of occlusion query handles.
	maxOcclusionQueries: int
	# Maximum number of encoder threads.
	maxEncoders: int
	# Minimum resource command buffer size.
	minResourceCbSize: int
	# Maximum transient vertex buffer size.
	maxTransientVbSize: int
	# Maximum transient index buffer size.
	maxTransientIbSize: int
	# Mimimum uniform buffer size.
	minUniformBufferSize: int
	# Row pitch alignment, in bytes, that buffer to texture blit copies
	# natively. Any other `BufferRegion::rowPitch` is repacked internally.
	blitRowPitchAlign: int
	# Offset alignment, in bytes, that buffer to texture blit copies
	# natively. Any other `BufferRegion::offset` is repacked internally.
	blitOffsetAlign: int

# Renderer capabilities.
class Caps(ctypes.Structure):
	# Renderer backend type. See: `bgfx::RendererType`
	rendererType: int
	# Supported functionality.
	#   @attention See `BGFX_CAPS_*` flags at https://bkaradzic.github.io/bgfx/bgfx.html#available-caps
	supported: int
	# Selected GPU vendor PCI id.
	vendorId: int
	# Selected GPU device id.
	deviceId: int
	# True when NDC depth is in [-1, 1] range, otherwise its [0, 1].
	homogeneousDepth: bool
	# True when NDC origin is at bottom left.
	originBottomLeft: bool
	# Number of enumerated GPUs.
	numGPUs: int
	# Enumerated GPUs.
	gpu: ctypes.Array
	# Renderer runtime limits.
	limits: CapsLimits
	# Supported texture format capabilities flags:
	#   - `BGFX_CAPS_FORMAT_TEXTURE_NONE` - Texture format is not supported.
	#   - `BGFX_CAPS_FORMAT_TEXTURE_2D` - Texture format is supported.
	#   - `BGFX_CAPS_FORMAT_TEXTURE_2D_SRGB` - Texture as sRGB format is supported.
	#   - `BGFX_CAPS_FORMAT_TEXTURE_2D_EMULATED` - Texture format is emulated.
	#   - `BGFX_CAPS_FORMAT_TEXTURE_3D` - Texture format is supported.
	#   - `BGFX_CAPS_FORMAT_TEXTURE_3D_SRGB` - Texture as sRGB format is supported.
	#   - `BGFX_CAPS_FORMAT_TEXTURE_3D_EMULATED` - Texture format is emulated.
	#   - `BGFX_CAPS_FORMAT_TEXTURE_CUBE` - Texture format is supported.
	#   - `BGFX_CAPS_FORMAT_TEXTURE_CUBE_SRGB` - Texture as sRGB format is supported.
	#   - `BGFX_CAPS_FORMAT_TEXTURE_CUBE_EMULATED` - Texture format is emulated.
	#   - `BGFX_CAPS_FORMAT_TEXTURE_VERTEX` - Texture format can be used from vertex shader.
	#   - `BGFX_CAPS_FORMAT_TEXTURE_IMAGE_READ` - Texture format can be used as image
	#     and read from.
	#   - `BGFX_CAPS_FORMAT_TEXTURE_IMAGE_WRITE` - Texture format can be used as image
	#     and written to.
	#   - `BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER` - Texture format can be used as frame
	#     buffer.
	#   - `BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA` - Texture format can be used as MSAA
	#     frame buffer.
	#   - `BGFX_CAPS_FORMAT_TEXTURE_MSAA` - Texture can be sampled as MSAA.
	#   - `BGFX_CAPS_FORMAT_TEXTURE_MIP_AUTOGEN` - Texture format supports auto-generated
	#     mips.
	#   - `BGFX_CAPS_FORMAT_TEXTURE_BACKBUFFER` - Texture format can be used as back buffer format.
	#   - `BGFX_CAPS_FORMAT_TEXTURE_VIDEO_DECODE_DST` - Texture format can be used as video
	#     decode destination.
	formats: ctypes.Array
	# Supported video codec capabilities flags. A non-zero entry means the codec is
	# supported for hardware decode; bits describe sample depths and chroma
	# subsamplings:
	#   - `BGFX_CAPS_VIDEO_CODEC_NONE` - Video codec is not supported.
	#   - `BGFX_CAPS_VIDEO_CODEC_BIT_8` - 8-bit sample depth is supported.
	#   - `BGFX_CAPS_VIDEO_CODEC_BIT_10` - 10-bit sample depth is supported.
	#   - `BGFX_CAPS_VIDEO_CODEC_BIT_12` - 12-bit sample depth is supported.
	#   - `BGFX_CAPS_VIDEO_CODEC_CHROMA_420` - 4:2:0 chroma subsampling is supported.
	#   - `BGFX_CAPS_VIDEO_CODEC_CHROMA_422` - 4:2:2 chroma subsampling is supported.
	#   - `BGFX_CAPS_VIDEO_CODEC_CHROMA_444` - 4:4:4 chroma subsampling is supported.
	codecs: ctypes.Array

# Internal data.
class InternalData(ctypes.Structure):
	# Renderer capabilities.
	caps: _Pointer[Caps]
	# GL context, or D3D device.
	context: Any

# Platform data.
class PlatformData(ctypes.Structure):
	# Native display type (*nix specific).
	ndt: Any
	# Native window handle. If `NULL`, bgfx will create a headless
	# context/device, provided the rendering API supports it.
	nwh: Any
	# GL context, D3D device, or Vulkan device. If `NULL`, bgfx
	# will create context/device.
	context: Any
	# D3D12 Queue. If `NULL` bgfx will create queue.
	queue: Any
	# GL back-buffer, or D3D render target view. If `NULL` bgfx will
	# create back-buffer color surface.
	backBuffer: Any
	# Backbuffer depth/stencil. If `NULL`, bgfx will create a back-buffer
	# depth/stencil surface.
	backBufferDS: Any
	# Handle type. Needed for platforms having more than one option.
	type: int

# Backbuffer resolution and reset parameters.
class Resolution(ctypes.Structure):
	# Backbuffer color format.
	formatColor: int
	# Backbuffer depth/stencil format.
	formatDepthStencil: int
	# Backbuffer width.
	width: int
	# Backbuffer height.
	height: int
	# Reset parameters.
	reset: int
	# Number of back buffers.
	numBackBuffers: int
	# Maximum frame latency.
	maxFrameLatency: int
	# Scale factor for debug text.
	debugTextScale: int

# Configurable runtime limits parameters.
class InitLimits(ctypes.Structure):
	# Maximum number of encoder threads.
	maxEncoders: int
	# Number of draw calls per frame to reserve storage for. Rounded
	# up to a multiple of `BGFX_CONFIG_DRAW_CALL_BLOCK`, which is also
	# the minimum. This is a reservation, not a limit: submitting more
	# than this grows the storage during the frame, up to
	# `BGFX_CONFIG_MAX_DRAW_CALLS`. With
	# `BGFX_CONFIG_DYNAMIC_FRAME_STORAGE` disabled nothing grows, and
	# this is a hard limit that `Caps::Limits::maxDrawCalls` reports
	# back; submissions past it are dropped. See
	# `Stats::numDrawCallsPeak` to size it.
	numDrawCalls: int
	# Number of frames the draw-call peak (high-water mark) is observed
	# before unused storage is released. Also used for resource command
	# buffers and uniform buffers. Set to 0 to keep whatever has been
	# allocated for the lifetime of the context. With
	# `BGFX_CONFIG_DYNAMIC_FRAME_STORAGE` disabled draw/blit/rect storage
	# is not resized; unused uniform and resource command buffer space
	# is still released.
	numDrawCallPeakFrames: int
	# Minimum resource command buffer size.
	minResourceCbSize: int
	# Maximum transient vertex buffer size.
	maxTransientVbSize: int
	# Maximum transient index buffer size.
	maxTransientIbSize: int
	# Mimimum uniform buffer size.
	minUniformBufferSize: int

# Initialization parameters used by `bgfx::init`.
class Init(ctypes.Structure):
	# Select rendering backend. When set to RendererType::Count
	# a default rendering backend will be selected appropriate to the platform.
	# See: `bgfx::RendererType`
	type: int
	# Vendor PCI ID. If set to `BGFX_PCI_ID_NONE`, discrete and integrated
	# GPUs will be prioritised.
	#   - `BGFX_PCI_ID_NONE` - Autoselect adapter.
	#   - `BGFX_PCI_ID_SOFTWARE_RASTERIZER` - Software rasterizer.
	#   - `BGFX_PCI_ID_AMD` - AMD adapter.
	#   - `BGFX_PCI_ID_APPLE` - Apple adapter.
	#   - `BGFX_PCI_ID_INTEL` - Intel adapter.
	#   - `BGFX_PCI_ID_NVIDIA` - NVIDIA adapter.
	#   - `BGFX_PCI_ID_MICROSOFT` - Microsoft adapter.
	vendorId: int
	# Device ID. If set to 0 it will select first device, or device with
	# matching ID.
	deviceId: int
	# Capabilities initialization mask (default: UINT64_MAX).
	capabilities: int
	# Enable device for debugging.
	debug: bool
	# Enable device for profiling.
	profile: bool
	# Enable fallback to next available renderer.
	fallback: bool
	# Enable video decoding.
	videoDecode: bool
	# Platform data.
	platformData: PlatformData
	# Backbuffer resolution and reset parameters. See: `bgfx::Resolution`.
	resolution: Resolution
	# Configurable runtime limits parameters.
	limits: InitLimits
	# Provide application specific callback interface.
	# See: `bgfx::CallbackI`
	callback: Any
	# Custom allocator. When a custom allocator is not
	# specified, bgfx uses the CRT allocator. Bgfx assumes
	# custom allocator is thread safe.
	allocator: Any

# Memory must be obtained by calling `bgfx::alloc`, `bgfx::copy`, or `bgfx::makeRef`.
# 
# @attention It is illegal to create this structure on stack and pass it to any bgfx API.
class Memory(ctypes.Structure):
	# Pointer to data.
	data: Any
	# Data size.
	size: int

# Transient index buffer.
class TransientIndexBuffer(ctypes.Structure):
	# Pointer to data.
	data: Any
	# Data size.
	size: int
	# First index.
	startIndex: int
	# Index buffer handle.
	handle: IndexBufferHandle
	# Index buffer format is 16-bits if true, otherwise it is 32-bit.
	isIndex16: bool

# Transient vertex buffer.
class TransientVertexBuffer(ctypes.Structure):
	# Pointer to data.
	data: Any
	# Data size.
	size: int
	# First vertex.
	startVertex: int
	# Vertex stride.
	stride: int
	# Vertex buffer handle.
	handle: VertexBufferHandle
	# Vertex layout handle.
	layoutHandle: VertexLayoutHandle

# Instance data buffer info.
class InstanceDataBuffer(ctypes.Structure):
	# Pointer to data.
	data: Any
	# Data size.
	size: int
	# Offset in vertex buffer.
	offset: int
	# Number of instances.
	num: int
	# Vertex buffer stride.
	stride: int
	# Vertex buffer object handle.
	handle: VertexBufferHandle

# Region of a texture, used as the source or destination of a blit, or as
# the region handed to `bgfx::read`.
# 
# Every field defaults to zero, and zero always means "the natural whole".
# `{ .handle = tex }` therefore addresses all of mip 0.
class TextureRegion(ctypes.Structure):
	# Texture handle.
	handle: TextureHandle
	# Mip level.
	mip: int
	# X position of the region.
	x: int
	# Y position of the region.
	y: int
	# If texture is 2D this should be 0. If the texture is a cube map
	# this is the cube face, for a 2D array it is the layer, and for a
	# 3D texture it is the Z position.
	z: int
	# Width of the region. 0 uses the rest of the mip from `x`.
	width: int
	# Height of the region. 0 uses the rest of the mip from `y`.
	height: int
	# Depth of the region for a 3D texture, or the number of layers or
	# cube faces otherwise. 0 uses the rest from `z`.
	depth: int

# Region of a buffer, used as the source or destination of a blit, or as the
# region handed to `bgfx::read`.
# 
# `rowPitch` and `slicePitch` describe how texture data is laid out in the
# buffer, and are ignored when the other end of the blit is also a buffer.
# Both are in bytes, and 0 selects the tightly packed layout: a row pitch of
# the region width in blocks multiplied by the block size, and a slice pitch
# of that row pitch multiplied by the region height in blocks.
# 
# A pitch the backend cannot copy natively is repacked by bgfx, which costs
# an extra pass over the data. `Caps::Limits::blitRowPitchAlign` and
# `blitOffsetAlign` report what the backend copies directly, and
# `BufferRegion::init` fills in a layout that matches them.
class BufferRegion(ctypes.Structure):
	# Buffer handle.
	handle: BufferHandle
	# Byte offset into the buffer.
	offset: int
	# Number of bytes. Only used when both ends of a blit are
	# buffers, or by `bgfx::read`. 0 uses the rest of the buffer.
	size: int
	# Distance in bytes between the start of two consecutive rows
	# of blocks. 0 is tightly packed.
	rowPitch: int
	# Distance in bytes between the start of two consecutive
	# slices, layers or cube faces. 0 is tightly packed.
	slicePitch: int

# Texture info.
class TextureInfo(ctypes.Structure):
	# Texture format.
	format: int
	# Total amount of bytes required to store texture.
	storageSize: int
	# Texture width.
	width: int
	# Texture height.
	height: int
	# Texture depth.
	depth: int
	# Number of layers in texture array.
	numLayers: int
	# Number of MIP maps.
	numMips: int
	# Format bits per pixel.
	bitsPerPixel: int
	# Texture is cubemap.
	cubeMap: bool

# Video decoder initialization. Serialized into the Memory passed to
# `createTexture2D`. When the memory blob begins with `magic`, bgfx
# infers the texture is a video decode destination (the caller need not set
# any extra texture flag). Everything else the renderer needs about the
# stream (chroma format, bit depth, profile, level, coded dimensions, DPB
# layout, color metadata) is parsed out of the codec parameter sets at
# create time.
class VideoDecoderInit(ctypes.Structure):
	# Structure magic. Must be `BX_MAKEFOURCC('V', 'D', 'I', 0x0)`.
	magic: int
	# Video codec. See: `VideoCodec::Enum`.
	codec: int
	# Codec parameter sets (Annex B for H.264/H.265, OBUs for AV1).
	parameterSets: Any
	# Parameter sets size in bytes.
	parameterSetsSize: int
	# Soft cap (in bytes) on the streaming access-unit FIFO (when
	# `BGFX_VIDEO_DECODER_INIT_RETAIN` is NOT set). 0 selects the
	# default. Ignored in RETAIN mode (the retain cache is unbounded).
	cachedAuBytes: int
	# Decoder lifetime flags. See: `BGFX_VIDEO_DECODER_INIT_*`.
	flags: int

# One access unit entry inside a `VideoDecoderFrame` batch. The bitstream
# for the AU lives at offset `Σ aus[0..ii].size` inside the frame's
# `bitstream` buffer (access units are stored back-to-back in decode /
# submission order).
class VideoDecoderAu(ctypes.Structure):
	# Access unit size in bytes.
	size: int
	# Presentation timestamp in microseconds for this access unit (container-provided).
	ptsUs: int

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
	# Structure magic. Must be `BX_MAKEFOURCC('V', 'D', 'F', 0x0)`.
	magic: int
	# Concatenated access-unit bitstream (decode order). NULL for presentation-only ticks.
	bitstream: Any
	# Per-AU size and PTS array. NULL when `numAus == 0`.
	aus: _Pointer[VideoDecoderAu]
	# Number of access units in this batch. 0 for presentation-only ticks.
	numAus: int
	# Current playback wall-clock time. Driver dispatches the picture whose `ptsUs`
	# best matches. Must be monotonically non-decreasing between non-`SET` calls.
	presentationTimeUs: int
	# Per-frame submission flags. See: `BGFX_VIDEO_DECODE_FRAME_*`.
	flags: int

# Uniform info.
class UniformInfo(ctypes.Structure):
	# Uniform name.
	name: bytes
	# Uniform type.
	type: int
	# Number of elements in array.
	num: int

# Frame buffer texture attachment info.
class Attachment(ctypes.Structure):
	# Attachment access. See `Access::Enum`.
	access: int
	# Render target texture handle.
	handle: TextureHandle
	# Mip level.
	mip: int
	# Cubemap side or depth layer/slice to use.
	layer: int
	# Number of texture layer/slice(s) in array to use.
	numLayers: int
	# Resolve flags. See: `BGFX_RESOLVE_*`
	resolve: int

# Transform data.
class Transform(ctypes.Structure):
	# Pointer to first 4x4 matrix.
	data: Any
	# Number of matrices.
	num: int

# View stats.
class ViewStats(ctypes.Structure):
	# View name.
	name: bytes
	# View id.
	view: int
	# CPU (submit) begin time.
	cpuTimeBegin: int
	# CPU (submit) end time.
	cpuTimeEnd: int
	# GPU begin time.
	gpuTimeBegin: int
	# GPU end time.
	gpuTimeEnd: int
	# Frame which generated gpuTimeBegin, gpuTimeEnd.
	gpuFrameNum: int

# Encoder stats.
class EncoderStats(ctypes.Structure):
	# Encoder thread CPU submit begin time.
	cpuTimeBegin: int
	# Encoder thread CPU submit end time.
	cpuTimeEnd: int

# Renderer statistics data.
# 
# @remarks All time values are high-resolution timestamps, while
# time frequencies define timestamps-per-second for that hardware.
class Stats(ctypes.Structure):
	# CPU time between two `bgfx::frame` calls.
	cpuTimeFrame: int
	# Render thread CPU submit begin time.
	cpuTimeBegin: int
	# Render thread CPU submit end time.
	cpuTimeEnd: int
	# CPU timer frequency. Timestamps-per-second
	cpuTimerFreq: int
	# GPU frame begin time.
	gpuTimeBegin: int
	# GPU frame end time.
	gpuTimeEnd: int
	# GPU timer frequency.
	gpuTimerFreq: int
	# Time spent waiting for render backend thread to finish issuing draw commands to underlying graphics API.
	waitRender: int
	# Time spent waiting for submit thread to advance to next frame.
	waitSubmit: int
	# Number of draw calls submitted.
	numDraw: int
	# Number of compute calls submitted.
	numCompute: int
	# Number of blit calls submitted.
	numBlit: int
	# Number of buffer to texture blit calls that had to be repacked,
	# because `BufferRegion::rowPitch` or `offset` didn't match
	# `Caps::Limits::blitRowPitchAlign` or `blitOffsetAlign`.
	numBlitRepack: int
	# Highest number of draw+compute calls requested in a single
	# frame so far (peak demand, before any were dropped). Useful
	# to tune `Init::Limits::numDrawCalls`.
	numDrawCallsPeak: int
	# GPU driver latency.
	maxGpuLatency: int
	# Frame which generated gpuTimeBegin, gpuTimeEnd.
	gpuFrameNum: int
	# Number of used dynamic index buffers.
	numDynamicIndexBuffers: int
	# Number of used dynamic vertex buffers.
	numDynamicVertexBuffers: int
	# Number of used frame buffers.
	numFrameBuffers: int
	# Number of used index buffers.
	numIndexBuffers: int
	# Number of used occlusion queries.
	numOcclusionQueries: int
	# Number of used programs.
	numPrograms: int
	# Number of used shaders.
	numShaders: int
	# Number of used textures.
	numTextures: int
	# Number of used uniforms.
	numUniforms: int
	# Number of used vertex buffers.
	numVertexBuffers: int
	# Number of used vertex layouts.
	numVertexLayouts: int
	# Estimate of texture memory used.
	textureMemoryUsed: int
	# Estimate of render target memory used.
	rtMemoryUsed: int
	# Amount of transient vertex buffer used.
	transientVbUsed: int
	# Amount of transient index buffer used.
	transientIbUsed: int
	# Number of primitives rendered.
	numPrims: ctypes.Array
	# Maximum available GPU memory for application.
	gpuMemoryMax: int
	# Amount of GPU memory used by the application.
	gpuMemoryUsed: int
	# Backbuffer width in pixels.
	width: int
	# Backbuffer height in pixels.
	height: int
	# Debug text width in characters.
	textWidth: int
	# Debug text height in characters.
	textHeight: int
	# Number of view stats.
	numViews: int
	# Array of View stats.
	viewStats: _Pointer[ViewStats]
	# Number of encoders used during frame.
	numEncoders: int
	# Array of encoder stats.
	encoderStats: _Pointer[EncoderStats]

# Vertex layout.
class VertexLayout(ctypes.Structure):
	# Hash.
	hash: int
	# Stride.
	stride: int
	# Attribute offsets.
	offset: ctypes.Array
	# Used attributes.
	attributes: ctypes.Array

# Encoders are used for submitting draw calls from multiple threads. Only one encoder
# per thread should be used. Use `bgfx::begin()` to obtain an encoder for a thread.
class Encoder(ctypes.Structure):
	pass

class DynamicIndexBufferHandle(ctypes.Structure):
	idx: int

	@property
	def valid(self) -> bool: ...

class DynamicVertexBufferHandle(ctypes.Structure):
	idx: int

	@property
	def valid(self) -> bool: ...

class FrameBufferHandle(ctypes.Structure):
	idx: int

	@property
	def valid(self) -> bool: ...

class IndexBufferHandle(ctypes.Structure):
	idx: int

	@property
	def valid(self) -> bool: ...

class IndirectBufferHandle(ctypes.Structure):
	idx: int

	@property
	def valid(self) -> bool: ...

class OcclusionQueryHandle(ctypes.Structure):
	idx: int

	@property
	def valid(self) -> bool: ...

class ProgramHandle(ctypes.Structure):
	idx: int

	@property
	def valid(self) -> bool: ...

class ShaderHandle(ctypes.Structure):
	idx: int

	@property
	def valid(self) -> bool: ...

class TextureHandle(ctypes.Structure):
	idx: int

	@property
	def valid(self) -> bool: ...

class UniformHandle(ctypes.Structure):
	idx: int

	@property
	def valid(self) -> bool: ...

class VertexBufferHandle(ctypes.Structure):
	idx: int

	@property
	def valid(self) -> bool: ...

class VertexLayoutHandle(ctypes.Structure):
	idx: int

	@property
	def valid(self) -> bool: ...

class BufferHandle(ctypes.Structure):
	idx: int
	type: int

	@property
	def valid(self) -> bool: ...

# Memory release callback.
ReleaseFn: Any

def load(path: Union[str, bytes]) -> ctypes.CDLL: ...

# Fill in the region of a plain 2D texture. `mip`, `z` and `depth` are left
# at zero, which addresses mip 0 of the only slice a 2D texture has.
def bgfx_texture_region_init(
	_this: Optional[Union[TextureRegion, _Pointer[TextureRegion], ctypes.Array]],
	_handle: TextureHandle,
	_x: int,
	_y: int,
	_width: int,
	_height: int,
	/,
) -> None: ...

# Fill `rowPitch`, `slicePitch` and `size` with the layout the backend copies
# fastest for `_texture`, and round `offset` up to `Caps::Limits::blitOffsetAlign`.
# `handle` is left untouched, so `size` can be used to create the buffer the
# region will point at.
def bgfx_buffer_region_init_texture(_this: Optional[Union[BufferRegion, _Pointer[BufferRegion], ctypes.Array]], _texture: Optional[Union[TextureRegion, _Pointer[TextureRegion], ctypes.Array]], /) -> None: ...

# Fill in the region a blit between two buffers copies. `rowPitch` and
# `slicePitch` are left at zero, since neither end of such a blit is a
# texture.
def bgfx_buffer_region_init_buffer(_this: Optional[Union[BufferRegion, _Pointer[BufferRegion], ctypes.Array]], _handle: BufferHandle, _offset: int, _size: int, /) -> None: ...

# Init attachment.
def bgfx_attachment_init(
	_this: Optional[Union[Attachment, _Pointer[Attachment], ctypes.Array]],
	_handle: TextureHandle,
	_access: Union[Access, int],
	_layer: int,
	_numLayers: int,
	_mip: int,
	_resolve: int,
	/,
) -> None: ...

# Start VertexLayout.
def bgfx_vertex_layout_begin(_this: Optional[Union[VertexLayout, _Pointer[VertexLayout], ctypes.Array]], _rendererType: Union[RendererType, int], /) -> _Pointer[VertexLayout]: ...

# Add attribute to VertexLayout.
# 
# @remarks Must be called between begin/end.
# 
def bgfx_vertex_layout_add(
	_this: Optional[Union[VertexLayout, _Pointer[VertexLayout], ctypes.Array]],
	_attrib: Union[Attrib, int],
	_num: int,
	_type: Union[AttribType, int],
	_normalized: bool,
	_asInt: bool,
	/,
) -> _Pointer[VertexLayout]: ...

# Decode attribute.
def bgfx_vertex_layout_decode(
	_this: Optional[Union[VertexLayout, _Pointer[VertexLayout], ctypes.Array]],
	_attrib: Union[Attrib, int],
	_num: Any,
	_type: Any,
	_normalized: Any,
	_asInt: Any,
	/,
) -> None: ...

# Skip `_num` bytes in vertex stream.
def bgfx_vertex_layout_skip(_this: Optional[Union[VertexLayout, _Pointer[VertexLayout], ctypes.Array]], _num: int, /) -> _Pointer[VertexLayout]: ...

# End VertexLayout.
def bgfx_vertex_layout_end(_this: Optional[Union[VertexLayout, _Pointer[VertexLayout], ctypes.Array]], /) -> None: ...

# Pack vertex attribute into vertex stream format.
def bgfx_vertex_pack(
	_input: Any,
	_inputNormalized: bool,
	_attr: Union[Attrib, int],
	_layout: Optional[Union[VertexLayout, _Pointer[VertexLayout], ctypes.Array]],
	_data: Any,
	_index: int,
	/,
) -> None: ...

# Unpack vertex attribute from vertex stream format.
def bgfx_vertex_unpack(_output: Any, _attr: Union[Attrib, int], _layout: Optional[Union[VertexLayout, _Pointer[VertexLayout], ctypes.Array]], _data: Any, _index: int, /) -> None: ...

# Converts vertex stream data from one vertex stream format to another.
def bgfx_vertex_convert(_dstLayout: Optional[Union[VertexLayout, _Pointer[VertexLayout], ctypes.Array]], _dstData: Any, _srcLayout: Optional[Union[VertexLayout, _Pointer[VertexLayout], ctypes.Array]], _srcData: Any, _num: int, /) -> None: ...

# Convert index buffer for use with different primitive topologies.
def bgfx_topology_convert(
	_conversion: Union[TopologyConvert, int],
	_dst: Any,
	_dstSize: int,
	_indices: Any,
	_numIndices: int,
	_index32: bool,
	/,
) -> int: ...

# Sort indices.
def bgfx_topology_sort_tri_list(
	_sort: Union[TopologySort, int],
	_dst: Any,
	_dstSize: int,
	_dir: Any,
	_pos: Any,
	_vertices: Any,
	_stride: int,
	_indices: Any,
	_numIndices: int,
	_index32: bool,
	/,
) -> None: ...

# Returns supported backend API renderers.
def bgfx_get_supported_renderers(_max: int, _enum: Any, /) -> int: ...

# Returns name of renderer.
def bgfx_get_renderer_name(_type: Union[RendererType, int], /) -> Optional[bytes]: ...

# Fill bgfx::Init struct with default values, before using it to initialize the library.
def bgfx_init_ctor(_init: Optional[Union[Init, _Pointer[Init], ctypes.Array]], /) -> None: ...

# Initialize the bgfx library.
def bgfx_init(_init: Optional[Union[Init, _Pointer[Init], ctypes.Array]], /) -> bool: ...

# Shutdown bgfx library.
def bgfx_shutdown() -> None: ...

# Reset graphic settings and back-buffer size.
# 
# @attention This call doesn’t change the window size, it just resizes
#   the back-buffer. Your windowing code controls the window size.
# 
def bgfx_reset(_width: int, _height: int, _flags: int, _format: Union[TextureFormat, int], /) -> None: ...

# Advance to next frame. This is the main frame-advancement call on the
# API thread (the thread from which `bgfx::init` was called).
# 
# **Multithreaded renderer** (`BGFX_CONFIG_MULTITHREADED=1`, default):
# This call waits for the render thread to finish processing the previous
# frame, then swaps internal submit/render buffers, signals the render
# thread to begin processing the new frame via `bgfx::renderFrame`, and
# returns immediately. The render thread and API thread then run in
# parallel: the API thread builds the next frame while the render thread
# executes GPU commands for the current frame.
# 
# **Single-threaded renderer** (`BGFX_CONFIG_MULTITHREADED=0`, or when
# `bgfx::renderFrame` and `bgfx::init` are called from the same thread):
# This call swaps internal buffers and performs frame rendering inline
# (internally calls `bgfx::renderFrame`), then returns.
# 
# @remarks
#   Must be called from the API thread (the thread that called
#   `bgfx::init`). In multithreaded mode, this call synchronizes with
#   `bgfx::renderFrame` running on the render thread via semaphores:
#   `bgfx::frame` waits for the render thread to finish, then posts a
#   signal that `bgfx::renderFrame` waits on to begin the next frame.
#   See also: `bgfx::renderFrame`.
# 
def bgfx_frame(_flags: int, /) -> int: ...

# Returns current renderer backend API type.
# 
# @remarks
#   Library must be initialized.
# 
def bgfx_get_renderer_type() -> int: ...

# Returns renderer capabilities.
# 
# @remarks
#   Library must be initialized.
# 
def bgfx_get_caps() -> _Pointer[Caps]: ...

# Returns performance counters.
# 
# @attention Pointer returned is valid until `bgfx::frame` is called.
# 
def bgfx_get_stats() -> _Pointer[Stats]: ...

# Allocate buffer to pass to bgfx calls. Data will be freed inside bgfx.
def bgfx_alloc(_size: int, /) -> _Pointer[Memory]: ...

# Allocate buffer and copy data into it. Data will be freed inside bgfx.
def bgfx_copy(_data: Any, _size: int, /) -> _Pointer[Memory]: ...

# Make reference to data to pass to bgfx. Unlike `bgfx::alloc`, this call
# doesn't allocate memory for data. It just copies the _data pointer. You
# can pass `ReleaseFn` function pointer to release this memory after it's
# consumed, otherwise you must make sure _data is available for at least 2
# `bgfx::frame` calls. `ReleaseFn` function must be able to be called
# from any thread.
# 
# @attention Data passed must be available for at least 2 `bgfx::frame` calls.
# 
def bgfx_make_ref(_data: Any, _size: int, /) -> _Pointer[Memory]: ...

# Make reference to data to pass to bgfx. Unlike `bgfx::alloc`, this call
# doesn't allocate memory for data. It just copies the _data pointer. You
# can pass `ReleaseFn` function pointer to release this memory after it's
# consumed, otherwise you must make sure _data is available for at least 2
# `bgfx::frame` calls. `ReleaseFn` function must be able to be called
# from any thread.
# 
# @attention Data passed must be available for at least 2 `bgfx::frame` calls.
# 
def bgfx_make_ref_release(_data: Any, _size: int, _releaseFn: Any, _userData: Any, /) -> _Pointer[Memory]: ...

# Set debug flags.
def bgfx_set_debug(_debug: int, /) -> None: ...

# Clear internal debug text buffer.
def bgfx_dbg_text_clear(_attr: int, _small: bool, /) -> None: ...

# Print formatted data from variable argument list to internal debug text character-buffer (VGA-compatible text mode).
def bgfx_dbg_text_vprintf(_x: int, _y: int, _attr: int, _format: Optional[bytes], _argList: Any, /) -> None: ...

# Draw image into internal debug text buffer.
def bgfx_dbg_text_image(
	_x: int,
	_y: int,
	_width: int,
	_height: int,
	_data: Any,
	_pitch: int,
	/,
) -> None: ...

# Create static index buffer.
def bgfx_create_index_buffer(_mem: Optional[Union[Memory, _Pointer[Memory], ctypes.Array]], _flags: int, /) -> IndexBufferHandle: ...

# Read back contents of buffer.
# 
# @remarks
#   Read back is asynchronous, and the result is available at the returned frame.
#   A zero `size` reads the rest of the buffer. `rowPitch` and `slicePitch` are
#   unused.
# 
#   Read back is intended for reading GPU written (compute, or draw indirect) buffers
#   back to the CPU. It's not intended to be used in the main render loop, since it
#   stalls the GPU.
# 
# @attention Buffer must be created with one of `BGFX_BUFFER_COMPUTE_*`, or
#   `BGFX_BUFFER_DRAW_INDIRECT` flags.
# 
def bgfx_read_buffer(_src: Optional[Union[BufferRegion, _Pointer[BufferRegion], ctypes.Array]], _data: Any, /) -> int: ...

# Set static index buffer debug name.
def bgfx_set_index_buffer_name(_handle: IndexBufferHandle, _name: Optional[bytes], _len: int, /) -> None: ...

# Destroy static index buffer.
def bgfx_destroy_index_buffer(_handle: IndexBufferHandle, /) -> None: ...

# Create vertex layout. Vertex layouts are used to describe the format of vertex data.
def bgfx_create_vertex_layout(_layout: Optional[Union[VertexLayout, _Pointer[VertexLayout], ctypes.Array]], /) -> VertexLayoutHandle: ...

# Destroy vertex layout.
def bgfx_destroy_vertex_layout(_layoutHandle: VertexLayoutHandle, /) -> None: ...

# Create static vertex buffer.
def bgfx_create_vertex_buffer(_mem: Optional[Union[Memory, _Pointer[Memory], ctypes.Array]], _layout: Optional[Union[VertexLayout, _Pointer[VertexLayout], ctypes.Array]], _flags: int, /) -> VertexBufferHandle: ...

# Set static vertex buffer debug name.
def bgfx_set_vertex_buffer_name(_handle: VertexBufferHandle, _name: Optional[bytes], _len: int, /) -> None: ...

# Destroy static vertex buffer.
def bgfx_destroy_vertex_buffer(_handle: VertexBufferHandle, /) -> None: ...

# Create empty dynamic index buffer.
def bgfx_create_dynamic_index_buffer(_num: int, _flags: int, /) -> DynamicIndexBufferHandle: ...

# Create a dynamic index buffer and initialize it.
def bgfx_create_dynamic_index_buffer_mem(_mem: Optional[Union[Memory, _Pointer[Memory], ctypes.Array]], _flags: int, /) -> DynamicIndexBufferHandle: ...

# Update dynamic index buffer.
def bgfx_update_dynamic_index_buffer(_handle: DynamicIndexBufferHandle, _startIndex: int, _mem: Optional[Union[Memory, _Pointer[Memory], ctypes.Array]], /) -> None: ...

# Destroy dynamic index buffer.
def bgfx_destroy_dynamic_index_buffer(_handle: DynamicIndexBufferHandle, /) -> None: ...

# Create empty dynamic vertex buffer.
def bgfx_create_dynamic_vertex_buffer(_num: int, _layout: Optional[Union[VertexLayout, _Pointer[VertexLayout], ctypes.Array]], _flags: int, /) -> DynamicVertexBufferHandle: ...

# Create dynamic vertex buffer and initialize it.
def bgfx_create_dynamic_vertex_buffer_mem(_mem: Optional[Union[Memory, _Pointer[Memory], ctypes.Array]], _layout: Optional[Union[VertexLayout, _Pointer[VertexLayout], ctypes.Array]], _flags: int, /) -> DynamicVertexBufferHandle: ...

# Update dynamic vertex buffer.
def bgfx_update_dynamic_vertex_buffer(_handle: DynamicVertexBufferHandle, _startVertex: int, _mem: Optional[Union[Memory, _Pointer[Memory], ctypes.Array]], /) -> None: ...

# Destroy dynamic vertex buffer.
def bgfx_destroy_dynamic_vertex_buffer(_handle: DynamicVertexBufferHandle, /) -> None: ...

# Returns number of requested or maximum available indices.
def bgfx_get_avail_transient_index_buffer(_num: int, _index32: bool, /) -> int: ...

# Returns number of requested or maximum available vertices.
def bgfx_get_avail_transient_vertex_buffer(_num: int, _layout: Optional[Union[VertexLayout, _Pointer[VertexLayout], ctypes.Array]], /) -> int: ...

# Returns number of requested or maximum available instance buffer slots.
def bgfx_get_avail_instance_data_buffer(_num: int, _stride: int, /) -> int: ...

# Allocate transient index buffer.
# 
def bgfx_alloc_transient_index_buffer(_tib: Optional[Union[TransientIndexBuffer, _Pointer[TransientIndexBuffer], ctypes.Array]], _num: int, _index32: bool, /) -> None: ...

# Allocate transient vertex buffer.
def bgfx_alloc_transient_vertex_buffer(_tvb: Optional[Union[TransientVertexBuffer, _Pointer[TransientVertexBuffer], ctypes.Array]], _num: int, _layout: Optional[Union[VertexLayout, _Pointer[VertexLayout], ctypes.Array]], /) -> None: ...

# Check for required space and allocate transient vertex and index
# buffers. If both space requirements are satisfied function returns
# true.
# 
def bgfx_alloc_transient_buffers(
	_tvb: Optional[Union[TransientVertexBuffer, _Pointer[TransientVertexBuffer], ctypes.Array]],
	_layout: Optional[Union[VertexLayout, _Pointer[VertexLayout], ctypes.Array]],
	_numVertices: int,
	_tib: Optional[Union[TransientIndexBuffer, _Pointer[TransientIndexBuffer], ctypes.Array]],
	_numIndices: int,
	_index32: bool,
	/,
) -> bool: ...

# Allocate instance data buffer.
def bgfx_alloc_instance_data_buffer(_idb: Optional[Union[InstanceDataBuffer, _Pointer[InstanceDataBuffer], ctypes.Array]], _num: int, _stride: int, /) -> None: ...

# Create draw indirect buffer.
def bgfx_create_indirect_buffer(_num: int, /) -> IndirectBufferHandle: ...

# Destroy draw indirect buffer.
def bgfx_destroy_indirect_buffer(_handle: IndirectBufferHandle, /) -> None: ...

# Create shader from memory buffer.
# 
# @remarks
#   Shader binary is obtained by compiling shader offline with shaderc command line tool.
# 
def bgfx_create_shader(_mem: Optional[Union[Memory, _Pointer[Memory], ctypes.Array]], /) -> ShaderHandle: ...

# Returns the number of uniforms and uniform handles used inside a shader.
# 
# @remarks
#   Only non-predefined uniforms are returned.
# 
def bgfx_get_shader_uniforms(_handle: ShaderHandle, _uniforms: Optional[Union[UniformHandle, _Pointer[UniformHandle], ctypes.Array]], _max: int, /) -> int: ...

# Set shader debug name.
def bgfx_set_shader_name(_handle: ShaderHandle, _name: Optional[bytes], _len: int, /) -> None: ...

# Destroy shader.
# 
# @remark Once a shader program is created with _handle,
#   it is safe to destroy that shader.
# 
def bgfx_destroy_shader(_handle: ShaderHandle, /) -> None: ...

# Create program with vertex and fragment shaders.
def bgfx_create_program(_vsh: ShaderHandle, _fsh: ShaderHandle, _destroyShaders: bool, /) -> ProgramHandle: ...

# Create program with compute shader.
def bgfx_create_compute_program(_csh: ShaderHandle, _destroyShaders: bool, /) -> ProgramHandle: ...

# Destroy program.
def bgfx_destroy_program(_handle: ProgramHandle, /) -> None: ...

# Validate texture parameters.
def bgfx_is_texture_valid(_depth: int, _cubeMap: bool, _numLayers: int, _format: Union[TextureFormat, int], _flags: int, /) -> bool: ...

# Validate video codec parameters. Use to check whether the requested
# combination of codec / bit depth / chroma / dimensions / DPB layout can
# be hardware decoded on the current device. Coarse capability discovery
# is `Caps::supported & BGFX_CAPS_VIDEO_DECODE` and `Caps::codecs[]`.
def bgfx_is_video_codec_valid(
	_codec: Union[VideoCodec, int],
	_chroma: int,
	_bitDepth: int,
	_codedWidth: int,
	_codedHeight: int,
	_maxDpbSlots: int,
	_maxActiveReferences: int,
	/,
) -> bool: ...

# Validate frame buffer parameters.
def bgfx_is_frame_buffer_valid(_num: int, _attachment: Optional[Union[Attachment, _Pointer[Attachment], ctypes.Array]], /) -> bool: ...

# Calculate amount of memory required for texture.
def bgfx_calc_texture_size(
	_info: Optional[Union[TextureInfo, _Pointer[TextureInfo], ctypes.Array]],
	_width: int,
	_height: int,
	_depth: int,
	_cubeMap: bool,
	_hasMips: bool,
	_numLayers: int,
	_format: Union[TextureFormat, int],
	/,
) -> None: ...

# Create texture from memory buffer.
def bgfx_create_texture(_mem: Optional[Union[Memory, _Pointer[Memory], ctypes.Array]], _flags: int, _skip: int, _info: Optional[Union[TextureInfo, _Pointer[TextureInfo], ctypes.Array]], /) -> TextureHandle: ...

# Create 2D texture.
def bgfx_create_texture_2d(
	_width: int,
	_height: int,
	_hasMips: bool,
	_numLayers: int,
	_format: Union[TextureFormat, int],
	_flags: int,
	_mem: Optional[Union[Memory, _Pointer[Memory], ctypes.Array]],
	_external: int,
	/,
) -> TextureHandle: ...

# Create texture with size based on back-buffer ratio. Texture will maintain ratio
# if back buffer resolution changes.
def bgfx_create_texture_2d_scaled(_ratio: Union[BackbufferRatio, int], _hasMips: bool, _numLayers: int, _format: Union[TextureFormat, int], _flags: int, /) -> TextureHandle: ...

# Create 3D texture.
def bgfx_create_texture_3d(
	_width: int,
	_height: int,
	_depth: int,
	_hasMips: bool,
	_format: Union[TextureFormat, int],
	_flags: int,
	_mem: Optional[Union[Memory, _Pointer[Memory], ctypes.Array]],
	_external: int,
	/,
) -> TextureHandle: ...

# Create Cube texture.
def bgfx_create_texture_cube(
	_size: int,
	_hasMips: bool,
	_numLayers: int,
	_format: Union[TextureFormat, int],
	_flags: int,
	_mem: Optional[Union[Memory, _Pointer[Memory], ctypes.Array]],
	_external: int,
	/,
) -> TextureHandle: ...

# Update 2D texture.
# 
# @attention It's valid to update only mutable texture. See `bgfx::createTexture2D` for more info.
# 
def bgfx_update_texture_2d(
	_handle: TextureHandle,
	_layer: int,
	_mip: int,
	_x: int,
	_y: int,
	_width: int,
	_height: int,
	_mem: Optional[Union[Memory, _Pointer[Memory], ctypes.Array]],
	_pitch: int,
	/,
) -> None: ...

# Update 3D texture.
# 
# @attention It's valid to update only mutable texture. See `bgfx::createTexture3D` for more info.
# 
def bgfx_update_texture_3d(
	_handle: TextureHandle,
	_mip: int,
	_x: int,
	_y: int,
	_z: int,
	_width: int,
	_height: int,
	_depth: int,
	_mem: Optional[Union[Memory, _Pointer[Memory], ctypes.Array]],
	/,
) -> None: ...

# Update Cube texture.
# 
# @attention It's valid to update only mutable texture. See `bgfx::createTextureCube` for more info.
# 
def bgfx_update_texture_cube(
	_handle: TextureHandle,
	_layer: int,
	_side: int,
	_mip: int,
	_x: int,
	_y: int,
	_width: int,
	_height: int,
	_mem: Optional[Union[Memory, _Pointer[Memory], ctypes.Array]],
	_pitch: int,
	/,
) -> None: ...

# Clear a texture subresource range to zero.
# 
def bgfx_clear_texture(_handle: TextureHandle, _mip: int, _numMips: int, _layer: int, _numLayers: int, /) -> None: ...

# Read back texture content.
# 
# @remarks
#   Read back is asynchronous, and the result is available at the returned frame.
#   `TextureRegion::z` selects cube face, 3D slice, or array layer. The region must
#   cover the whole mip.
# 
#   Read back is not intended to be used in the main render loop, since it stalls
#   the GPU.
# 
# @attention Texture must be created with `BGFX_TEXTURE_READ_BACK` flag.
#            It's a texture for CPU readback, and can't be a GPU resource
#            at the same time. See `examples/30-picking`.
# @attention Availability depends on: `BGFX_CAPS_TEXTURE_READ_BACK`.
# 
def bgfx_read_texture(_src: Optional[Union[TextureRegion, _Pointer[TextureRegion], ctypes.Array]], _data: Any, /) -> int: ...

# Set texture debug name.
def bgfx_set_texture_name(_handle: TextureHandle, _name: Optional[bytes], _len: int, /) -> None: ...

# Returns texture direct access pointer.
# 
# @attention Availability depends on: `BGFX_CAPS_TEXTURE_DIRECT_ACCESS`. This feature
#   is available on GPUs that have unified memory architecture (UMA) support.
# 
def bgfx_get_direct_access_ptr(_handle: TextureHandle, /) -> Any: ...

# Destroy texture.
def bgfx_destroy_texture(_handle: TextureHandle, /) -> None: ...

# Create frame buffer (simple).
def bgfx_create_frame_buffer(_width: int, _height: int, _format: Union[TextureFormat, int], _textureFlags: int, /) -> FrameBufferHandle: ...

# Create frame buffer with size based on back-buffer ratio. Frame buffer will maintain ratio
# if back buffer resolution changes.
def bgfx_create_frame_buffer_scaled(_ratio: Union[BackbufferRatio, int], _format: Union[TextureFormat, int], _textureFlags: int, /) -> FrameBufferHandle: ...

# Create MRT frame buffer from texture handles (simple).
def bgfx_create_frame_buffer_from_handles(_num: int, _handles: Optional[Union[TextureHandle, _Pointer[TextureHandle], ctypes.Array]], _destroyTexture: bool, /) -> FrameBufferHandle: ...

# Create MRT frame buffer from texture handles with specific layer and
# mip level.
def bgfx_create_frame_buffer_from_attachment(_num: int, _attachment: Optional[Union[Attachment, _Pointer[Attachment], ctypes.Array]], _destroyTexture: bool, /) -> FrameBufferHandle: ...

# Create frame buffer for multiple window rendering.
# 
# @remarks
#   Frame buffer cannot be used for sampling.
# 
# @attention Availability depends on: `BGFX_CAPS_SWAP_CHAIN`.
# 
def bgfx_create_frame_buffer_from_nwh(_nwh: Any, _width: int, _height: int, _format: Union[TextureFormat, int], _depthFormat: Union[TextureFormat, int], /) -> FrameBufferHandle: ...

# Set frame buffer debug name.
def bgfx_set_frame_buffer_name(_handle: FrameBufferHandle, _name: Optional[bytes], _len: int, /) -> None: ...

# Obtain texture handle of frame buffer attachment.
def bgfx_get_texture(_handle: FrameBufferHandle, _attachment: int, /) -> TextureHandle: ...

# Destroy frame buffer.
def bgfx_destroy_frame_buffer(_handle: FrameBufferHandle, /) -> None: ...

# Create shader uniform parameter.
# 
# @remarks
#   1. Uniform names are unique. It's valid to call `bgfx::createUniform`
#      multiple times with the same uniform name. The library will always
#      return the same handle, but the handle reference count will be
#      incremented. This means that the same number of `bgfx::destroyUniform`
#      must be called to properly destroy the uniform.
# 
#   2. Predefined uniforms (declared in `bgfx_shader.sh`):
#      - `u_viewRect vec4(x, y, width, height)` - view rectangle for current
#        view, in pixels.
#      - `u_viewTexel vec4(1.0/width, 1.0/height, undef, undef)` - inverse
#        width and height
#      - `u_view mat4` - view matrix
#      - `u_invView mat4` - inverted view matrix
#      - `u_proj mat4` - projection matrix
#      - `u_invProj mat4` - inverted projection matrix
#      - `u_viewProj mat4` - concatenated view projection matrix
#      - `u_invViewProj mat4` - concatenated inverted view projection matrix
#      - `u_model mat4[BGFX_CONFIG_MAX_BONES]` - array of model matrices.
#      - `u_modelView mat4` - concatenated model view matrix, only first
#        model matrix from array is used.
#      - `u_invModelView mat4` - inverted concatenated model view matrix.
#      - `u_modelViewProj mat4` - concatenated model view projection matrix.
#      - `u_alphaRef float` - alpha reference value for alpha test.
# 
def bgfx_create_uniform(_name: Optional[bytes], _type: Union[UniformType, int], _num: int, /) -> UniformHandle: ...

# Create shader uniform parameter.
# 
# @remarks
#   1. Uniform names are unique. It's valid to call `bgfx::createUniform`
#      multiple times with the same uniform name. The library will always
#      return the same handle, but the handle reference count will be
#      incremented. This means that the same number of `bgfx::destroyUniform`
#      must be called to properly destroy the uniform.
# 
#   2. Predefined uniforms (declared in `bgfx_shader.sh`):
#      - `u_viewRect vec4(x, y, width, height)` - view rectangle for current
#        view, in pixels.
#      - `u_viewTexel vec4(1.0/width, 1.0/height, undef, undef)` - inverse
#        width and height
#      - `u_view mat4` - view matrix
#      - `u_invView mat4` - inverted view matrix
#      - `u_proj mat4` - projection matrix
#      - `u_invProj mat4` - inverted projection matrix
#      - `u_viewProj mat4` - concatenated view projection matrix
#      - `u_invViewProj mat4` - concatenated inverted view projection matrix
#      - `u_model mat4[BGFX_CONFIG_MAX_BONES]` - array of model matrices.
#      - `u_modelView mat4` - concatenated model view matrix, only first
#        model matrix from array is used.
#      - `u_invModelView mat4` - inverted concatenated model view matrix.
#      - `u_modelViewProj mat4` - concatenated model view projection matrix.
#      - `u_alphaRef float` - alpha reference value for alpha test.
# 
def bgfx_create_uniform_with_freq(_name: Optional[bytes], _freq: Union[UniformFreq, int], _type: Union[UniformType, int], _num: int, /) -> UniformHandle: ...

# Retrieve uniform info.
def bgfx_get_uniform_info(_handle: UniformHandle, _info: Optional[Union[UniformInfo, _Pointer[UniformInfo], ctypes.Array]], /) -> None: ...

# Destroy shader uniform parameter.
def bgfx_destroy_uniform(_handle: UniformHandle, /) -> None: ...

# Create occlusion query. Occlusion queries allow the GPU to determine
# if any pixels passed the depth test.
def bgfx_create_occlusion_query() -> OcclusionQueryHandle: ...

# Retrieve occlusion query result from previous frame.
def bgfx_get_result(_handle: OcclusionQueryHandle, _result: Any, /) -> int: ...

# Destroy occlusion query.
def bgfx_destroy_occlusion_query(_handle: OcclusionQueryHandle, /) -> None: ...

# Set palette color value.
def bgfx_set_palette_color(_index: int, _rgba: Any, /) -> None: ...

# Set palette color value.
def bgfx_set_palette_color_rgba32f(_index: int, _r: float, _g: float, _b: float, _a: float, /) -> None: ...

# Set palette color value.
def bgfx_set_palette_color_rgba8(_index: int, _rgba: int, /) -> None: ...

# Set view name.
# 
# @remarks
#   This is debug only feature.
# 
#   In graphics debugger view name will appear as:
# 
#       "nnnc <view name>"
#        ^  ^ ^
#        |  +--- compute (C)
#        +------ view id
# 
def bgfx_set_view_name(_id: int, _name: Optional[bytes], _len: int, /) -> None: ...

# Set view rectangle. Draw primitive outside view will be clipped.
def bgfx_set_view_rect(_id: int, _x: int, _y: int, _width: int, _height: int, /) -> None: ...

# Set view rectangle. Draw primitive outside view will be clipped.
def bgfx_set_view_rect_ratio(_id: int, _x: int, _y: int, _ratio: Union[BackbufferRatio, int], /) -> None: ...

# Set view scissor. Draw primitive outside view will be clipped. When
# _x, _y, _width and _height are set to 0, scissor will be disabled.
def bgfx_set_view_scissor(_id: int, _x: int, _y: int, _width: int, _height: int, /) -> None: ...

# Set view clear flags.
def bgfx_set_view_clear(_id: int, _flags: int, _rgba: int, _depth: float, _stencil: int, /) -> None: ...

# Set view clear flags with different clear color for each
# frame buffer texture. `bgfx::setPaletteColor` must be used to set up a
# clear color palette.
def bgfx_set_view_clear_mrt(
	_id: int,
	_flags: int,
	_depth: float,
	_stencil: int,
	_c0: int,
	_c1: int,
	_c2: int,
	_c3: int,
	_c4: int,
	_c5: int,
	_c6: int,
	_c7: int,
	/,
) -> None: ...

# Set view sorting mode.
# 
# @remarks
#   View mode must be set prior calling `bgfx::submit` for the view.
# 
def bgfx_set_view_mode(_id: int, _mode: Union[ViewMode, int], /) -> None: ...

# Set view frame buffer.
# 
# @remarks
#   Not persistent after `bgfx::reset` call.
# 
def bgfx_set_view_frame_buffer(_id: int, _handle: FrameBufferHandle, /) -> None: ...

# Set view's view matrix and projection matrix,
# all draw primitives in this view will use these two matrices.
def bgfx_set_view_transform(_id: int, _view: Any, _proj: Any, /) -> None: ...

# Post submit view reordering.
def bgfx_set_view_order(_id: int, _num: int, _order: Any, /) -> None: ...

# Set view shading rate.
# 
# @attention Availability depends on: `BGFX_CAPS_VARIABLE_RATE_SHADING`.
# 
def bgfx_set_view_shading_rate(_id: int, _shadingRate: Union[ShadingRate, int], /) -> None: ...

# Reset all view settings to default.
def bgfx_reset_view(_id: int, /) -> None: ...

# Begin submitting draw calls from thread. Obtains an encoder that can be
# used to submit draw calls, compute dispatches, and state changes.
# 
# In multithreaded mode (`BGFX_CONFIG_MULTITHREADED=1`), multiple threads
# can each obtain their own encoder and submit draw calls in parallel.
# Each encoder writes into its own uniform buffer, so there is no
# contention between threads. The maximum number of simultaneous encoders
# is configured via `Limits.maxEncoders` in `bgfx::Init` (default: 8).
# 
# When called from the API thread (the thread that called `bgfx::init`)
# with `_forceNewEncoder` set to `false`, the default internal encoder
# (encoder 0) is returned. This is the same encoder used by the legacy
# non-encoder API (`bgfx::setState`, `bgfx::submit`, etc.). When called
# from a worker thread (or with `_forceNewEncoder` set to `true`), a new
# encoder is allocated from the encoder pool.
# 
# @remarks
#   The returned `Encoder` pointer is valid until `bgfx::end` is called
#   with it. All encoders must be ended before `bgfx::frame` is called.
#   If `bgfx::frame` is called while encoders are still active, it will
#   wait for them to finish. Returns `NULL` if no encoder slots are
#   available (all `maxEncoders` slots are in use).
#   See also: `bgfx::end`, `bgfx::frame`.
# 
def bgfx_encoder_begin(_forceNewEncoder: bool, /) -> _Pointer[Encoder]: ...

# End submitting draw calls from thread. Returns the encoder obtained from
# `bgfx::begin` back to the encoder pool.
# 
# After this call the `Encoder` pointer is no longer valid and must not
# be used. The encoder's recorded draw calls and state changes are finalized
# and will be included in the next frame when `bgfx::frame` is called.
# 
# @remarks
#   Must be called from the same thread that called `bgfx::begin` for
#   this encoder. All encoders must be ended before `bgfx::frame` is
#   called. The default encoder (encoder 0, used by the legacy API) is
#   managed internally and does not need to be passed to `bgfx::end`;
#   passing it is harmless but has no effect.
#   See also: `bgfx::begin`, `bgfx::frame`.
# 
def bgfx_encoder_end(_encoder: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]], /) -> None: ...

# Sets a debug marker. This allows you to group graphics calls together for easy browsing in
# graphics debugging tools.
def bgfx_encoder_set_marker(_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]], _name: Optional[bytes], _len: int, /) -> None: ...

# Set render states for draw primitive.
# 
# @remarks
#   1. To set up more complex states use:
#      `BGFX_STATE_ALPHA_REF(_ref)`,
#      `BGFX_STATE_POINT_SIZE(_size)`,
#      `BGFX_STATE_BLEND_FUNC(_src, _dst)`,
#      `BGFX_STATE_BLEND_FUNC_SEPARATE(_srcRGB, _dstRGB, _srcA, _dstA)`,
#      `BGFX_STATE_BLEND_EQUATION(_equation)`,
#      `BGFX_STATE_BLEND_EQUATION_SEPARATE(_equationRGB, _equationA)`
#   2. `BGFX_STATE_BLEND_EQUATION_ADD` is set when no other blend
#      equation is specified.
# 
def bgfx_encoder_set_state(_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]], _state: int, _rgba: int, /) -> None: ...

# Set condition for rendering.
def bgfx_encoder_set_condition(_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]], _handle: OcclusionQueryHandle, _visible: bool, /) -> None: ...

# Set stencil test state.
def bgfx_encoder_set_stencil(_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]], _fstencil: int, _bstencil: int, /) -> None: ...

# Set scissor for draw primitive.
# 
# @remark
#   To scissor for all primitives in view see `bgfx::setViewScissor`.
# 
def bgfx_encoder_set_scissor(_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]], _x: int, _y: int, _width: int, _height: int, /) -> int: ...

# Set scissor from cache for draw primitive.
# 
# @remark
#   To scissor for all primitives in view see `bgfx::setViewScissor`.
# 
def bgfx_encoder_set_scissor_cached(_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]], _cache: int, /) -> None: ...

# Set model matrix for draw primitive. If it is not called,
# the model will be rendered with an identity model matrix.
def bgfx_encoder_set_transform(_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]], _mtx: Any, _num: int, /) -> int: ...

#  Set model matrix from matrix cache for draw primitive.
def bgfx_encoder_set_transform_cached(_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]], _cache: int, _num: int, /) -> None: ...

# Reserve matrices in internal matrix cache.
# 
# @attention Pointer returned can be modified until `bgfx::frame` is called.
# 
def bgfx_encoder_alloc_transform(_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]], _transform: Optional[Union[Transform, _Pointer[Transform], ctypes.Array]], _num: int, /) -> int: ...

# Set shader uniform parameter for draw primitive.
def bgfx_encoder_set_uniform(_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]], _handle: UniformHandle, _value: Any, _num: int, /) -> None: ...

# Set shader uniform parameter for view.
# 
# @attention Uniform must be created with `bgfx::UniformFreq::View` argument.
# 
def bgfx_set_view_uniform(_id: int, _handle: UniformHandle, _value: Any, _num: int, /) -> None: ...

# Set shader uniform parameter for frame.
# 
# @attention Uniform must be created with `bgfx::UniformFreq::View` argument.
# 
def bgfx_set_frame_uniform(_handle: UniformHandle, _value: Any, _num: int, /) -> None: ...

# Set index buffer for draw primitive.
def bgfx_encoder_set_index_buffer(_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]], _handle: IndexBufferHandle, _firstIndex: int, _numIndices: int, /) -> None: ...

# Set index buffer for draw primitive.
def bgfx_encoder_set_dynamic_index_buffer(_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]], _handle: DynamicIndexBufferHandle, _firstIndex: int, _numIndices: int, /) -> None: ...

# Set index buffer for draw primitive.
def bgfx_encoder_set_transient_index_buffer(_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]], _tib: Optional[Union[TransientIndexBuffer, _Pointer[TransientIndexBuffer], ctypes.Array]], _firstIndex: int, _numIndices: int, /) -> None: ...

# Set vertex buffer for draw primitive.
def bgfx_encoder_set_vertex_buffer(_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]], _stream: int, _handle: VertexBufferHandle, _startVertex: int, _numVertices: int, /) -> None: ...

# Set vertex buffer for draw primitive.
def bgfx_encoder_set_vertex_buffer_with_layout(
	_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]],
	_stream: int,
	_handle: VertexBufferHandle,
	_startVertex: int,
	_numVertices: int,
	_layoutHandle: VertexLayoutHandle,
	/,
) -> None: ...

# Set vertex buffer for draw primitive.
def bgfx_encoder_set_dynamic_vertex_buffer(_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]], _stream: int, _handle: DynamicVertexBufferHandle, _startVertex: int, _numVertices: int, /) -> None: ...

# Set vertex buffer for draw primitive.
def bgfx_encoder_set_dynamic_vertex_buffer_with_layout(
	_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]],
	_stream: int,
	_handle: DynamicVertexBufferHandle,
	_startVertex: int,
	_numVertices: int,
	_layoutHandle: VertexLayoutHandle,
	/,
) -> None: ...

# Set vertex buffer for draw primitive.
def bgfx_encoder_set_transient_vertex_buffer(_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]], _stream: int, _tvb: Optional[Union[TransientVertexBuffer, _Pointer[TransientVertexBuffer], ctypes.Array]], _startVertex: int, _numVertices: int, /) -> None: ...

# Set vertex buffer for draw primitive.
def bgfx_encoder_set_transient_vertex_buffer_with_layout(
	_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]],
	_stream: int,
	_tvb: Optional[Union[TransientVertexBuffer, _Pointer[TransientVertexBuffer], ctypes.Array]],
	_startVertex: int,
	_numVertices: int,
	_layoutHandle: VertexLayoutHandle,
	/,
) -> None: ...

# Set number of vertices for auto generated vertices use in conjunction
# with gl_VertexID.
# 
# @attention Availability depends on: `BGFX_CAPS_VERTEX_ID`.
# 
def bgfx_encoder_set_vertex_count(_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]], _numVertices: int, /) -> None: ...

# Set instance data buffer for draw primitive.
def bgfx_encoder_set_instance_data_buffer(_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]], _idb: Optional[Union[InstanceDataBuffer, _Pointer[InstanceDataBuffer], ctypes.Array]], _start: int, _num: int, /) -> None: ...

# Set instance data buffer for draw primitive.
def bgfx_encoder_set_instance_data_from_vertex_buffer(_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]], _handle: VertexBufferHandle, _startVertex: int, _num: int, /) -> None: ...

# Set instance data buffer for draw primitive.
def bgfx_encoder_set_instance_data_from_dynamic_vertex_buffer(_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]], _handle: DynamicVertexBufferHandle, _startVertex: int, _num: int, /) -> None: ...

# Set number of instances for auto generated instances use in conjunction
# with gl_InstanceID.
# 
# @attention Availability depends on: `BGFX_CAPS_VERTEX_ID`.
# 
def bgfx_encoder_set_instance_count(_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]], _numInstances: int, /) -> None: ...

# Set texture stage for draw primitive.
def bgfx_encoder_set_texture(_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]], _stage: int, _sampler: UniformHandle, _handle: TextureHandle, _flags: int, /) -> None: ...

# Set texture stage for draw primitive, selecting a sub-range of the
# texture's array layers and mip levels.
def bgfx_encoder_set_texture_view(
	_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]],
	_stage: int,
	_sampler: UniformHandle,
	_handle: TextureHandle,
	_firstLayer: int,
	_numLayers: int,
	_firstMip: int,
	_numMips: int,
	_flags: int,
	/,
) -> None: ...

# Submit an empty primitive for rendering. Uniforms and draw state
# will be applied but no geometry will be submitted. Useful in cases
# when no other draw/compute primitive is submitted to view, but it's
# desired to execute clear view.
# 
# @remark
#   These empty draw calls will sort before ordinary draw calls.
# 
def bgfx_encoder_touch(_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]], _id: int, /) -> None: ...

# Submit primitive for rendering.
def bgfx_encoder_submit(_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]], _id: int, _program: ProgramHandle, _depth: int, _flags: int, /) -> None: ...

# Submit primitive with occlusion query for rendering.
def bgfx_encoder_submit_occlusion_query(
	_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]],
	_id: int,
	_program: ProgramHandle,
	_occlusionQuery: OcclusionQueryHandle,
	_depth: int,
	_flags: int,
	/,
) -> None: ...

# Submit primitive for rendering with index and instance data info from
# indirect buffer.
# 
# @attention Availability depends on: `BGFX_CAPS_DRAW_INDIRECT`.
# 
def bgfx_encoder_submit_indirect(
	_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]],
	_id: int,
	_program: ProgramHandle,
	_indirectHandle: IndirectBufferHandle,
	_start: int,
	_num: int,
	_depth: int,
	_flags: int,
	/,
) -> None: ...

# Submit primitive for rendering with index and instance data info and
# draw count from indirect buffers.
# 
# @attention Availability depends on: `BGFX_CAPS_DRAW_INDIRECT_COUNT`.
# 
def bgfx_encoder_submit_indirect_count(
	_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]],
	_id: int,
	_program: ProgramHandle,
	_indirectHandle: IndirectBufferHandle,
	_start: int,
	_numHandle: IndexBufferHandle,
	_numIndex: int,
	_numMax: int,
	_depth: int,
	_flags: int,
	/,
) -> None: ...

# Set compute index buffer.
def bgfx_encoder_set_compute_index_buffer(_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]], _stage: int, _handle: IndexBufferHandle, _access: Union[Access, int], /) -> None: ...

# Set compute vertex buffer.
def bgfx_encoder_set_compute_vertex_buffer(_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]], _stage: int, _handle: VertexBufferHandle, _access: Union[Access, int], /) -> None: ...

# Set compute dynamic index buffer.
def bgfx_encoder_set_compute_dynamic_index_buffer(_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]], _stage: int, _handle: DynamicIndexBufferHandle, _access: Union[Access, int], /) -> None: ...

# Set compute dynamic vertex buffer.
def bgfx_encoder_set_compute_dynamic_vertex_buffer(_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]], _stage: int, _handle: DynamicVertexBufferHandle, _access: Union[Access, int], /) -> None: ...

# Set compute indirect buffer.
def bgfx_encoder_set_compute_indirect_buffer(_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]], _stage: int, _handle: IndirectBufferHandle, _access: Union[Access, int], /) -> None: ...

# Set compute image from texture.
def bgfx_encoder_set_image(
	_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]],
	_stage: int,
	_handle: TextureHandle,
	_mip: int,
	_access: Union[Access, int],
	_format: Union[TextureFormat, int],
	/,
) -> None: ...

# Set compute image stage for draw primitive, selecting a sub-range of the
# texture's array layers and mip levels.
def bgfx_encoder_set_image_view(
	_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]],
	_stage: int,
	_handle: TextureHandle,
	_firstLayer: int,
	_numLayers: int,
	_mip: int,
	_access: Union[Access, int],
	_format: Union[TextureFormat, int],
	/,
) -> None: ...

# Dispatch compute.
def bgfx_encoder_dispatch(
	_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]],
	_id: int,
	_program: ProgramHandle,
	_numX: int,
	_numY: int,
	_numZ: int,
	_flags: int,
	/,
) -> None: ...

# Dispatch compute indirect.
def bgfx_encoder_dispatch_indirect(
	_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]],
	_id: int,
	_program: ProgramHandle,
	_indirectHandle: IndirectBufferHandle,
	_start: int,
	_num: int,
	_flags: int,
	/,
) -> None: ...

# Discard previously set state for draw or compute call.
def bgfx_encoder_discard(_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]], _flags: int, /) -> None: ...

# Blit texture region between two textures.
# 
# @remarks
#   The copy covers the region the two sides have in common: each side gives
#   the origin it starts at, and the size is the smaller of the two extents.
#   A zero `width`, `height` or `depth` extends to the rest of that mip.
# 
#   Blit is performed on GPU, and it is ordered within the view. In views, all
#   draw commands are executed after blit and compute commands.
# 
# @attention Destination texture must be created with `BGFX_TEXTURE_BLIT_DST` flag.
# @attention Availability depends on: `BGFX_CAPS_TEXTURE_BLIT`.
# 
def bgfx_encoder_blit(_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]], _id: int, _dst: Optional[Union[TextureRegion, _Pointer[TextureRegion], ctypes.Array]], _src: Optional[Union[TextureRegion, _Pointer[TextureRegion], ctypes.Array]], /) -> None: ...

# Blit buffer region between two buffers.
# 
# @remarks
#   The source region gives the number of bytes copied, and the destination
#   region gives only the offset they land at. A zero `size` copies the rest of
#   the source buffer. `rowPitch` and `slicePitch` are unused.
# 
#   Buffer blit is performed on GPU, and it is ordered within the view, same as
#   texture blit. In views, all draw commands are executed after blit and compute
#   commands.
# 
# @attention Source buffer must be created with one of `BGFX_BUFFER_COMPUTE_*`, or
#   `BGFX_BUFFER_DRAW_INDIRECT` flags.
# @attention Destination buffer must be created with `BGFX_BUFFER_COMPUTE_WRITE`, or
#   `BGFX_BUFFER_DRAW_INDIRECT` flag.
# @attention Source and destination buffer must be different.
# 
def bgfx_encoder_blit_buffer(_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]], _id: int, _dst: Optional[Union[BufferRegion, _Pointer[BufferRegion], ctypes.Array]], _src: Optional[Union[BufferRegion, _Pointer[BufferRegion], ctypes.Array]], /) -> None: ...

# Blit texture region into buffer.
# 
# @remarks
#   The texture region gives the size of the copy. `BufferRegion::rowPitch` and
#   `slicePitch` choose how the texels are laid out in the buffer, and 0 packs
#   them tightly. `BufferRegion::init` fills in the layout the backend copies
#   fastest, and bgfx repacks internally for any other layout.
# 
#   Blit is performed on GPU, and it is ordered within the view, same as texture
#   blit. In views, all draw commands are executed after blit and compute commands.
# 
# @attention Destination buffer must be created with `BGFX_BUFFER_COMPUTE_WRITE`, or
#   `BGFX_BUFFER_DRAW_INDIRECT` flag.
# @attention Availability depends on: `BGFX_CAPS_TEXTURE_BLIT`.
# 
def bgfx_encoder_blit_to_buffer(_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]], _id: int, _dst: Optional[Union[BufferRegion, _Pointer[BufferRegion], ctypes.Array]], _src: Optional[Union[TextureRegion, _Pointer[TextureRegion], ctypes.Array]], /) -> None: ...

# Blit buffer contents into texture region.
# 
# @remarks
#   The texture region gives the size of the copy. `BufferRegion::rowPitch` and
#   `slicePitch` describe how the texels are laid out in the buffer, and 0 reads
#   them tightly packed. `BufferRegion::init` fills in the layout the backend
#   copies fastest, and bgfx repacks internally for any other layout.
# 
#   Blit is performed on GPU, and it is ordered within the view, same as texture
#   blit. In views, all draw commands are executed after blit and compute commands.
# 
# @attention Source buffer must be created with one of `BGFX_BUFFER_COMPUTE_*`, or
#   `BGFX_BUFFER_DRAW_INDIRECT` flags.
# @attention Destination texture must be created with `BGFX_TEXTURE_BLIT_DST` flag.
# @attention Availability depends on: `BGFX_CAPS_TEXTURE_BLIT`.
# 
def bgfx_encoder_blit_from_buffer(_this: Optional[Union[Encoder, _Pointer[Encoder], ctypes.Array]], _id: int, _dst: Optional[Union[TextureRegion, _Pointer[TextureRegion], ctypes.Array]], _src: Optional[Union[BufferRegion, _Pointer[BufferRegion], ctypes.Array]], /) -> None: ...

# Request screen shot of window back buffer.
# 
# @remarks
#   `bgfx::CallbackI::screenShot` must be implemented.
# @attention Frame buffer handle must be created with OS' target native window handle.
# 
def bgfx_request_screen_shot(_handle: FrameBufferHandle, _filePath: Optional[bytes], /) -> None: ...

# Render frame. Executes the actual GPU rendering work for one frame.
# 
# In the default **multithreaded** configuration, `bgfx::renderFrame` runs
# on the **render thread** while `bgfx::frame` runs on the **API thread**.
# Their interaction is as follows:
# 
#   1. The render thread calls `bgfx::renderFrame`, which blocks waiting
#      for the API thread to signal that a new frame is ready.
#   2. On the API thread, `bgfx::frame` finishes building the frame,
#      swaps internal submit/render buffers, and signals the render thread.
#   3. `bgfx::renderFrame` wakes up, executes pre-render commands,
#      submits GPU draw calls, executes post-render commands, flips the
#      back buffer, then signals back to the API thread that rendering
#      is complete.
#   4. The API thread's next `bgfx::frame` call waits for this completion
#      signal before swapping buffers again.
# 
# This double-buffered semaphore handshake allows the API thread and
# render thread to run in parallel, overlapping CPU frame building with
# GPU rendering.
# 
# @attention `bgfx::renderFrame` is a blocking call. It waits for
#   `bgfx::frame` to be called from the API thread to process the frame.
#   If a timeout value is passed, the call will return
#   `RenderFrame::Timeout` even if `bgfx::frame` has not been called.
#   A value of -1 (default) means wait indefinitely (up to
#   `BGFX_CONFIG_API_SEMAPHORE_TIMEOUT`).
# 
# @warning This call should only be used on platforms that don't allow
#   creating a separate rendering thread. If it is called before
#   `bgfx::init`, the internal render thread won't be created by the
#   `bgfx::init` call, and the user is responsible for calling
#   `bgfx::renderFrame` on the render thread each frame. If both
#   `bgfx::renderFrame` and `bgfx::init` are called from the same
#   thread, bgfx operates in single-threaded mode and `bgfx::frame`
#   will internally invoke `bgfx::renderFrame` automatically.
#   See also: `bgfx::frame`.
# 
def bgfx_render_frame(_msecs: int, /) -> int: ...

# Set platform data.
# 
# @warning Must be called before `bgfx::init`.
# 
def bgfx_set_platform_data(_data: Optional[Union[PlatformData, _Pointer[PlatformData], ctypes.Array]], /) -> None: ...

# Get internal data for interop.
# 
# @attention It's expected you understand some bgfx internals before you
#   use this call.
# 
# @warning Must be called only on render thread.
# 
def bgfx_get_internal_data() -> _Pointer[InternalData]: ...

# Override internal texture with externally created texture. Previously
# created internal texture will released.
# 
# @attention It's expected you understand some bgfx internals before you
#   use this call.
# 
# @warning Must be called only on render thread.
# 
def bgfx_override_internal_texture_ptr(_handle: TextureHandle, _ptr: int, _layerIndex: int, /) -> int: ...

# Override internal texture by creating new texture. Previously created
# internal texture will released.
# 
# @attention It's expected you understand some bgfx internals before you
#   use this call.
# 
# @returns Native API pointer to texture. If result is 0, texture is not created yet from the
#   main thread.
# 
# @warning Must be called only on render thread.
# 
def bgfx_override_internal_texture(
	_handle: TextureHandle,
	_width: int,
	_height: int,
	_numMips: int,
	_format: Union[TextureFormat, int],
	_flags: int,
	/,
) -> int: ...

# Sets a debug marker. This allows you to group graphics calls together for easy browsing in
# graphics debugging tools.
def bgfx_set_marker(_name: Optional[bytes], _len: int, /) -> None: ...

# Set render states for draw primitive.
# 
# @remarks
#   1. To set up more complex states use:
#      `BGFX_STATE_ALPHA_REF(_ref)`,
#      `BGFX_STATE_POINT_SIZE(_size)`,
#      `BGFX_STATE_BLEND_FUNC(_src, _dst)`,
#      `BGFX_STATE_BLEND_FUNC_SEPARATE(_srcRGB, _dstRGB, _srcA, _dstA)`,
#      `BGFX_STATE_BLEND_EQUATION(_equation)`,
#      `BGFX_STATE_BLEND_EQUATION_SEPARATE(_equationRGB, _equationA)`
#   2. `BGFX_STATE_BLEND_EQUATION_ADD` is set when no other blend
#      equation is specified.
# 
def bgfx_set_state(_state: int, _rgba: int, /) -> None: ...

# Set condition for rendering.
def bgfx_set_condition(_handle: OcclusionQueryHandle, _visible: bool, /) -> None: ...

# Set stencil test state.
def bgfx_set_stencil(_fstencil: int, _bstencil: int, /) -> None: ...

# Set scissor for draw primitive.
# 
# @remark
#   To scissor for all primitives in view see `bgfx::setViewScissor`.
# 
def bgfx_set_scissor(_x: int, _y: int, _width: int, _height: int, /) -> int: ...

# Set scissor from cache for draw primitive.
# 
# @remark
#   To scissor for all primitives in view see `bgfx::setViewScissor`.
# 
def bgfx_set_scissor_cached(_cache: int, /) -> None: ...

# Set model matrix for draw primitive. If it is not called,
# the model will be rendered with an identity model matrix.
def bgfx_set_transform(_mtx: Any, _num: int, /) -> int: ...

#  Set model matrix from matrix cache for draw primitive.
def bgfx_set_transform_cached(_cache: int, _num: int, /) -> None: ...

# Reserve matrices in internal matrix cache.
# 
# @attention Pointer returned can be modified until `bgfx::frame` is called.
# 
def bgfx_alloc_transform(_transform: Optional[Union[Transform, _Pointer[Transform], ctypes.Array]], _num: int, /) -> int: ...

# Set shader uniform parameter for draw primitive.
def bgfx_set_uniform(_handle: UniformHandle, _value: Any, _num: int, /) -> None: ...

# Set index buffer for draw primitive.
def bgfx_set_index_buffer(_handle: IndexBufferHandle, _firstIndex: int, _numIndices: int, /) -> None: ...

# Set index buffer for draw primitive.
def bgfx_set_dynamic_index_buffer(_handle: DynamicIndexBufferHandle, _firstIndex: int, _numIndices: int, /) -> None: ...

# Set index buffer for draw primitive.
def bgfx_set_transient_index_buffer(_tib: Optional[Union[TransientIndexBuffer, _Pointer[TransientIndexBuffer], ctypes.Array]], _firstIndex: int, _numIndices: int, /) -> None: ...

# Set vertex buffer for draw primitive.
def bgfx_set_vertex_buffer(_stream: int, _handle: VertexBufferHandle, _startVertex: int, _numVertices: int, /) -> None: ...

# Set vertex buffer for draw primitive.
def bgfx_set_vertex_buffer_with_layout(_stream: int, _handle: VertexBufferHandle, _startVertex: int, _numVertices: int, _layoutHandle: VertexLayoutHandle, /) -> None: ...

# Set vertex buffer for draw primitive.
def bgfx_set_dynamic_vertex_buffer(_stream: int, _handle: DynamicVertexBufferHandle, _startVertex: int, _numVertices: int, /) -> None: ...

# Set vertex buffer for draw primitive.
def bgfx_set_dynamic_vertex_buffer_with_layout(_stream: int, _handle: DynamicVertexBufferHandle, _startVertex: int, _numVertices: int, _layoutHandle: VertexLayoutHandle, /) -> None: ...

# Set vertex buffer for draw primitive.
def bgfx_set_transient_vertex_buffer(_stream: int, _tvb: Optional[Union[TransientVertexBuffer, _Pointer[TransientVertexBuffer], ctypes.Array]], _startVertex: int, _numVertices: int, /) -> None: ...

# Set vertex buffer for draw primitive.
def bgfx_set_transient_vertex_buffer_with_layout(_stream: int, _tvb: Optional[Union[TransientVertexBuffer, _Pointer[TransientVertexBuffer], ctypes.Array]], _startVertex: int, _numVertices: int, _layoutHandle: VertexLayoutHandle, /) -> None: ...

# Set number of vertices for auto generated vertices use in conjunction
# with gl_VertexID.
# 
# @attention Availability depends on: `BGFX_CAPS_VERTEX_ID`.
# 
def bgfx_set_vertex_count(_numVertices: int, /) -> None: ...

# Set instance data buffer for draw primitive.
def bgfx_set_instance_data_buffer(_idb: Optional[Union[InstanceDataBuffer, _Pointer[InstanceDataBuffer], ctypes.Array]], _start: int, _num: int, /) -> None: ...

# Set instance data buffer for draw primitive.
def bgfx_set_instance_data_from_vertex_buffer(_handle: VertexBufferHandle, _startVertex: int, _num: int, /) -> None: ...

# Set instance data buffer for draw primitive.
def bgfx_set_instance_data_from_dynamic_vertex_buffer(_handle: DynamicVertexBufferHandle, _startVertex: int, _num: int, /) -> None: ...

# Set number of instances for auto generated instances use in conjunction
# with gl_InstanceID.
# 
# @attention Availability depends on: `BGFX_CAPS_VERTEX_ID`.
# 
def bgfx_set_instance_count(_numInstances: int, /) -> None: ...

# Set texture stage for draw primitive.
def bgfx_set_texture(_stage: int, _sampler: UniformHandle, _handle: TextureHandle, _flags: int, /) -> None: ...

# Set texture stage for draw primitive, selecting a sub-range of the
# texture's array layers and mip levels.
def bgfx_set_texture_view(
	_stage: int,
	_sampler: UniformHandle,
	_handle: TextureHandle,
	_firstLayer: int,
	_numLayers: int,
	_firstMip: int,
	_numMips: int,
	_flags: int,
	/,
) -> None: ...

# Submit an empty primitive for rendering. Uniforms and draw state
# will be applied but no geometry will be submitted.
# 
# @remark
#   These empty draw calls will sort before ordinary draw calls.
# 
def bgfx_touch(_id: int, /) -> None: ...

# Submit primitive for rendering.
def bgfx_submit(_id: int, _program: ProgramHandle, _depth: int, _flags: int, /) -> None: ...

# Submit primitive with occlusion query for rendering.
def bgfx_submit_occlusion_query(_id: int, _program: ProgramHandle, _occlusionQuery: OcclusionQueryHandle, _depth: int, _flags: int, /) -> None: ...

# Submit primitive for rendering with index and instance data info from
# indirect buffer.
# 
# @attention Availability depends on: `BGFX_CAPS_DRAW_INDIRECT`.
# 
def bgfx_submit_indirect(
	_id: int,
	_program: ProgramHandle,
	_indirectHandle: IndirectBufferHandle,
	_start: int,
	_num: int,
	_depth: int,
	_flags: int,
	/,
) -> None: ...

# Submit primitive for rendering with index and instance data info and
# draw count from indirect buffers.
# 
# @attention Availability depends on: `BGFX_CAPS_DRAW_INDIRECT_COUNT`.
# 
def bgfx_submit_indirect_count(
	_id: int,
	_program: ProgramHandle,
	_indirectHandle: IndirectBufferHandle,
	_start: int,
	_numHandle: IndexBufferHandle,
	_numIndex: int,
	_numMax: int,
	_depth: int,
	_flags: int,
	/,
) -> None: ...

# Set compute index buffer.
def bgfx_set_compute_index_buffer(_stage: int, _handle: IndexBufferHandle, _access: Union[Access, int], /) -> None: ...

# Set compute vertex buffer.
def bgfx_set_compute_vertex_buffer(_stage: int, _handle: VertexBufferHandle, _access: Union[Access, int], /) -> None: ...

# Set compute dynamic index buffer.
def bgfx_set_compute_dynamic_index_buffer(_stage: int, _handle: DynamicIndexBufferHandle, _access: Union[Access, int], /) -> None: ...

# Set compute dynamic vertex buffer.
def bgfx_set_compute_dynamic_vertex_buffer(_stage: int, _handle: DynamicVertexBufferHandle, _access: Union[Access, int], /) -> None: ...

# Set compute indirect buffer.
def bgfx_set_compute_indirect_buffer(_stage: int, _handle: IndirectBufferHandle, _access: Union[Access, int], /) -> None: ...

# Set compute image from texture.
def bgfx_set_image(_stage: int, _handle: TextureHandle, _mip: int, _access: Union[Access, int], _format: Union[TextureFormat, int], /) -> None: ...

# Set compute image stage for draw primitive, selecting a sub-range of the
# texture's array layers and mip levels.
def bgfx_set_image_view(
	_stage: int,
	_handle: TextureHandle,
	_firstLayer: int,
	_numLayers: int,
	_mip: int,
	_access: Union[Access, int],
	_format: Union[TextureFormat, int],
	/,
) -> None: ...

# Dispatch compute.
def bgfx_dispatch(
	_id: int,
	_program: ProgramHandle,
	_numX: int,
	_numY: int,
	_numZ: int,
	_flags: int,
	/,
) -> None: ...

# Dispatch compute indirect.
def bgfx_dispatch_indirect(
	_id: int,
	_program: ProgramHandle,
	_indirectHandle: IndirectBufferHandle,
	_start: int,
	_num: int,
	_flags: int,
	/,
) -> None: ...

# Discard previously set state for draw or compute call.
def bgfx_discard(_flags: int, /) -> None: ...

# Blit texture region between two textures.
# 
# @remarks
#   The copy covers the region the two sides have in common: each side gives
#   the origin it starts at, and the size is the smaller of the two extents.
#   A zero `width`, `height` or `depth` extends to the rest of that mip.
# 
#   Blit is performed on GPU, and it is ordered within the view. In views, all
#   draw commands are executed after blit and compute commands.
# 
# @attention Destination texture must be created with `BGFX_TEXTURE_BLIT_DST` flag.
# @attention Availability depends on: `BGFX_CAPS_TEXTURE_BLIT`.
# 
def bgfx_blit(_id: int, _dst: Optional[Union[TextureRegion, _Pointer[TextureRegion], ctypes.Array]], _src: Optional[Union[TextureRegion, _Pointer[TextureRegion], ctypes.Array]], /) -> None: ...

# Blit buffer region between two buffers.
# 
# @remarks
#   The source region gives the number of bytes copied, and the destination
#   region gives only the offset they land at. A zero `size` copies the rest of
#   the source buffer. `rowPitch` and `slicePitch` are unused.
# 
#   Buffer blit is performed on GPU, and it is ordered within the view, same as
#   texture blit. In views, all draw commands are executed after blit and compute
#   commands.
# 
# @attention Source buffer must be created with one of `BGFX_BUFFER_COMPUTE_*`, or
#   `BGFX_BUFFER_DRAW_INDIRECT` flags.
# @attention Destination buffer must be created with `BGFX_BUFFER_COMPUTE_WRITE`, or
#   `BGFX_BUFFER_DRAW_INDIRECT` flag.
# @attention Source and destination buffer must be different.
# 
def bgfx_blit_buffer(_id: int, _dst: Optional[Union[BufferRegion, _Pointer[BufferRegion], ctypes.Array]], _src: Optional[Union[BufferRegion, _Pointer[BufferRegion], ctypes.Array]], /) -> None: ...

# Blit texture region into buffer.
# 
# @remarks
#   The texture region gives the size of the copy. `BufferRegion::rowPitch` and
#   `slicePitch` choose how the texels are laid out in the buffer, and 0 packs
#   them tightly. `BufferRegion::init` fills in the layout the backend copies
#   fastest, and bgfx repacks internally for any other layout.
# 
#   Blit is performed on GPU, and it is ordered within the view, same as texture
#   blit. In views, all draw commands are executed after blit and compute commands.
# 
# @attention Destination buffer must be created with `BGFX_BUFFER_COMPUTE_WRITE`, or
#   `BGFX_BUFFER_DRAW_INDIRECT` flag.
# @attention Availability depends on: `BGFX_CAPS_TEXTURE_BLIT`.
# 
def bgfx_blit_to_buffer(_id: int, _dst: Optional[Union[BufferRegion, _Pointer[BufferRegion], ctypes.Array]], _src: Optional[Union[TextureRegion, _Pointer[TextureRegion], ctypes.Array]], /) -> None: ...

# Blit buffer contents into texture region.
# 
# @remarks
#   The texture region gives the size of the copy. `BufferRegion::rowPitch` and
#   `slicePitch` describe how the texels are laid out in the buffer, and 0 reads
#   them tightly packed. `BufferRegion::init` fills in the layout the backend
#   copies fastest, and bgfx repacks internally for any other layout.
# 
#   Blit is performed on GPU, and it is ordered within the view, same as texture
#   blit. In views, all draw commands are executed after blit and compute commands.
# 
# @attention Source buffer must be created with one of `BGFX_BUFFER_COMPUTE_*`, or
#   `BGFX_BUFFER_DRAW_INDIRECT` flags.
# @attention Destination texture must be created with `BGFX_TEXTURE_BLIT_DST` flag.
# @attention Availability depends on: `BGFX_CAPS_TEXTURE_BLIT`.
# 
def bgfx_blit_from_buffer(_id: int, _dst: Optional[Union[TextureRegion, _Pointer[TextureRegion], ctypes.Array]], _src: Optional[Union[BufferRegion, _Pointer[BufferRegion], ctypes.Array]], /) -> None: ...
