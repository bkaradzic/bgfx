// Copyright 2011-2026 Branimir Karadzic. All rights reserved.
// License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE


//
// AUTO GENERATED! DO NOT EDIT!
//

package io.github.bkaradzic.bgfx;

import java.lang.AutoCloseable;
import java.lang.foreign.Arena;
import java.lang.foreign.FunctionDescriptor;
import java.lang.foreign.MemoryLayout;
import java.lang.foreign.MemorySegment;
import java.lang.foreign.SegmentAllocator;
import java.lang.foreign.StructLayout;
import java.lang.foreign.ValueLayout;
import java.lang.invoke.MethodHandle;
import java.lang.invoke.MethodType;
import java.lang.invoke.VarHandle;
import java.nio.file.Path;
import java.util.Objects;

import org.jspecify.annotations.NullMarked;
import org.jspecify.annotations.NullUnmarked;
import org.jspecify.annotations.Nullable;

import io.github.bkaradzic.bgfx.*;
import io.github.bkaradzic.bgfx.util.*;
import static io.github.bkaradzic.bgfx.Bgfx.*;
import static io.github.bkaradzic.bgfx.util.FFMUtil.*;

/**
 * Texture format enum.
 * <p>
 * Notation:
 * <p>
 *       RGBA16S
 *       ^   ^ ^
 *       |   | +-- [ ]Unorm
 *       |   |     [F]loat
 *       |   |     [S]norm
 *       |   |     [I]nt
 *       |   |     [U]int
 *       |   +---- Number of bits per component
 *       +-------- Components
 * <p>
 * <strong>Attention:</strong> Availability depends on Caps (see: formats).
 */
@NullMarked
public enum TextureFormat {
	/**
	 * Block Compression 1. 5-bit R, 6-bit G, 5-bit B, 1-bit A. 4 BPP.
	 */
	BC1,
	/**
	 * Block Compression 2. 5-bit R, 6-bit G, 5-bit B, 4-bit explicit A. 8 BPP.
	 */
	BC2,
	/**
	 * Block Compression 3. 5-bit R, 6-bit G, 5-bit B, 8-bit interpolated A. 8 BPP.
	 */
	BC3,
	/**
	 * Block Compression 4. Single 8-bit red channel, unsigned normalized. 4 BPP.
	 */
	BC4,
	/**
	 * Block Compression 4. Single 8-bit red channel, signed normalized. 4 BPP.
	 */
	BC4S,
	/**
	 * Block Compression 5. Two 8-bit channels (RG), unsigned normalized. 8 BPP.
	 */
	BC5,
	/**
	 * Block Compression 5. Two 8-bit channels (RG), signed normalized. 8 BPP.
	 */
	BC5S,
	/**
	 * Block Compression 6H. Three 16-bit floating-point channels (RGB), HDR. 8 BPP.
	 */
	BC6H,
	/**
	 * Block Compression 6H. Three 16-bit unsigned floating-point channels (RGB), HDR. 8 BPP.
	 */
	BC6HU,
	/**
	 * RGB 4-7 bits per color channel, 0-8 bits alpha. Block Compression 7. High-quality RGBA, 4-7 bits per color, 0-8 bits alpha. 8 BPP.
	 */
	BC7,
	/**
	 * Ericsson Texture Compression 1. 8-bit per channel RGB. 4 BPP.
	 */
	ETC1,
	/**
	 * Ericsson Texture Compression 2. 8-bit per channel RGB. 4 BPP.
	 */
	ETC2,
	/**
	 * Ericsson Texture Compression 2 with full alpha. 8-bit per channel RGBA. 8 BPP.
	 */
	ETC2A,
	/**
	 * Ericsson Texture Compression 2 with 1-bit punch-through alpha. 4 BPP.
	 */
	ETC2A1,
	/**
	 * ETC2 Alpha Compression, single 11-bit red channel, unsigned normalized. 4 BPP.
	 */
	EACR11,
	/**
	 * ETC2 Alpha Compression, single 11-bit red channel, signed normalized. 4 BPP.
	 */
	EACR11S,
	/**
	 * ETC2 Alpha Compression, two 11-bit channels (RG), unsigned normalized. 8 BPP.
	 */
	EACRG11,
	/**
	 * ETC2 Alpha Compression, two 11-bit channels (RG), signed normalized. 8 BPP.
	 */
	EACRG11S,
	/**
	 * PowerVR Texture Compression v1. 3-channel RGB. 2 BPP.
	 */
	PTC12,
	/**
	 * PowerVR Texture Compression v1. 3-channel RGB. 4 BPP.
	 */
	PTC14,
	/**
	 * PowerVR Texture Compression v1. 4-channel RGBA. 2 BPP.
	 */
	PTC12A,
	/**
	 * PowerVR Texture Compression v1. 4-channel RGBA. 4 BPP.
	 */
	PTC14A,
	/**
	 * PowerVR Texture Compression v2. 4-channel RGBA. 2 BPP.
	 */
	PTC22,
	/**
	 * PowerVR Texture Compression v2. 4-channel RGBA. 4 BPP.
	 */
	PTC24,
	/**
	 * AMD Texture Compression. 3-channel RGB. 4 BPP.
	 */
	ATC,
	/**
	 * AMD Texture Compression with explicit alpha. 4-channel RGBA. 8 BPP.
	 */
	ATCE,
	/**
	 * AMD Texture Compression with interpolated alpha. 4-channel RGBA. 8 BPP.
	 */
	ATCI,
	/**
	 * Adaptive Scalable Texture Compression, 4x4 block, RGBA. 8.00 BPP.
	 */
	ASTC4X4,
	/**
	 * Adaptive Scalable Texture Compression, 5x4 block, RGBA. 6.40 BPP.
	 */
	ASTC5X4,
	/**
	 * Adaptive Scalable Texture Compression, 5x5 block, RGBA. 5.12 BPP.
	 */
	ASTC5X5,
	/**
	 * Adaptive Scalable Texture Compression, 6x5 block, RGBA. 4.27 BPP.
	 */
	ASTC6X5,
	/**
	 * Adaptive Scalable Texture Compression, 6x6 block, RGBA. 3.56 BPP.
	 */
	ASTC6X6,
	/**
	 * Adaptive Scalable Texture Compression, 8x5 block, RGBA. 3.20 BPP.
	 */
	ASTC8X5,
	/**
	 * Adaptive Scalable Texture Compression, 8x6 block, RGBA. 2.67 BPP.
	 */
	ASTC8X6,
	/**
	 * Adaptive Scalable Texture Compression, 8x8 block, RGBA. 2.00 BPP.
	 */
	ASTC8X8,
	/**
	 * Adaptive Scalable Texture Compression, 10x5 block, RGBA. 2.56 BPP.
	 */
	ASTC10X5,
	/**
	 * Adaptive Scalable Texture Compression, 10x6 block, RGBA. 2.13 BPP.
	 */
	ASTC10X6,
	/**
	 * Adaptive Scalable Texture Compression, 10x8 block, RGBA. 1.60 BPP.
	 */
	ASTC10X8,
	/**
	 * Adaptive Scalable Texture Compression, 10x10 block, RGBA. 1.28 BPP.
	 */
	ASTC10X10,
	/**
	 * Adaptive Scalable Texture Compression, 12x10 block, RGBA. 1.07 BPP.
	 */
	ASTC12X10,
	/**
	 * Adaptive Scalable Texture Compression, 12x12 block, RGBA. 0.89 BPP.
	 */
	ASTC12X12,
	/**
	 * Compressed formats above.
	 */
	UNKNOWN,
	/**
	 * 1-bit single-channel red. Monochrome, 1-bit per pixel. 1 BPP.
	 */
	R1,
	/**
	 * 8-bit single-channel alpha, unsigned normalized. 8 BPP.
	 */
	A8,
	/**
	 * 8-bit single-channel red, unsigned normalized. 8 BPP.
	 */
	R8,
	/**
	 * 8-bit single-channel red, signed integer. 8 BPP.
	 */
	R8I,
	/**
	 * 8-bit single-channel red, unsigned integer. 8 BPP.
	 */
	R8U,
	/**
	 * 8-bit single-channel red, signed normalized. 8 BPP.
	 */
	R8S,
	/**
	 * 16-bit single-channel red, unsigned normalized. 16 BPP.
	 */
	R16,
	/**
	 * 16-bit single-channel red, signed integer. 16 BPP.
	 */
	R16I,
	/**
	 * 16-bit single-channel red, unsigned integer. 16 BPP.
	 */
	R16U,
	/**
	 * 16-bit single-channel red, half-precision floating point. 16 BPP.
	 */
	R16F,
	/**
	 * 16-bit single-channel red, signed normalized. 16 BPP.
	 */
	R16S,
	/**
	 * 32-bit single-channel red, signed integer. 32 BPP.
	 */
	R32I,
	/**
	 * 32-bit single-channel red, unsigned integer. 32 BPP.
	 */
	R32U,
	/**
	 * 32-bit single-channel red, full-precision floating point. 32 BPP.
	 */
	R32F,
	/**
	 * Two 8-bit channels (red, green), unsigned normalized. 16 BPP.
	 */
	RG8,
	/**
	 * Two 8-bit channels (red, green), signed integer. 16 BPP.
	 */
	RG8I,
	/**
	 * Two 8-bit channels (red, green), unsigned integer. 16 BPP.
	 */
	RG8U,
	/**
	 * Two 8-bit channels (red, green), signed normalized. 16 BPP.
	 */
	RG8S,
	/**
	 * Two 16-bit channels (red, green), unsigned normalized. 32 BPP.
	 */
	RG16,
	/**
	 * Two 16-bit channels (red, green), signed integer. 32 BPP.
	 */
	RG16I,
	/**
	 * Two 16-bit channels (red, green), unsigned integer. 32 BPP.
	 */
	RG16U,
	/**
	 * Two 16-bit channels (red, green), half-precision floating point. 32 BPP.
	 */
	RG16F,
	/**
	 * Two 16-bit channels (red, green), signed normalized. 32 BPP.
	 */
	RG16S,
	/**
	 * Two 32-bit channels (red, green), signed integer. 64 BPP.
	 */
	RG32I,
	/**
	 * Two 32-bit channels (red, green), unsigned integer. 64 BPP.
	 */
	RG32U,
	/**
	 * Two 32-bit channels (red, green), full-precision floating point. 64 BPP.
	 */
	RG32F,
	/**
	 * Three 8-bit channels (red, green, blue), unsigned normalized. 24 BPP.
	 */
	RGB8,
	/**
	 * Three 8-bit channels (red, green, blue), signed integer. 24 BPP.
	 */
	RGB8I,
	/**
	 * Three 8-bit channels (red, green, blue), unsigned integer. 24 BPP.
	 */
	RGB8U,
	/**
	 * Three 8-bit channels (red, green, blue), signed normalized. 24 BPP.
	 */
	RGB8S,
	/**
	 * Shared-exponent RGB. 9 bits per RGB channel with a shared 5-bit exponent, floating point. 32 BPP.
	 */
	RGB9E5F,
	/**
	 * Four 8-bit channels (blue, green, red, alpha), unsigned normalized. BGRA byte order. 32 BPP.
	 */
	BGRA8,
	/**
	 * Four 8-bit channels (red, green, blue, alpha), unsigned normalized. 32 BPP.
	 */
	RGBA8,
	/**
	 * Four 8-bit channels (red, green, blue, alpha), signed integer. 32 BPP.
	 */
	RGBA8I,
	/**
	 * Four 8-bit channels (red, green, blue, alpha), unsigned integer. 32 BPP.
	 */
	RGBA8U,
	/**
	 * Four 8-bit channels (red, green, blue, alpha), signed normalized. 32 BPP.
	 */
	RGBA8S,
	/**
	 * Four 16-bit channels (red, green, blue, alpha), unsigned normalized. 64 BPP.
	 */
	RGBA16,
	/**
	 * Four 16-bit channels (red, green, blue, alpha), signed integer. 64 BPP.
	 */
	RGBA16I,
	/**
	 * Four 16-bit channels (red, green, blue, alpha), unsigned integer. 64 BPP.
	 */
	RGBA16U,
	/**
	 * Four 16-bit channels (red, green, blue, alpha), half-precision floating point. 64 BPP.
	 */
	RGBA16F,
	/**
	 * Four 16-bit channels (red, green, blue, alpha), signed normalized. 64 BPP.
	 */
	RGBA16S,
	/**
	 * Four 32-bit channels (red, green, blue, alpha), signed integer. 128 BPP.
	 */
	RGBA32I,
	/**
	 * Four 32-bit channels (red, green, blue, alpha), unsigned integer. 128 BPP.
	 */
	RGBA32U,
	/**
	 * Four 32-bit channels (red, green, blue, alpha), full-precision floating point. 128 BPP.
	 */
	RGBA32F,
	/**
	 * Packed 16-bit, 5-bit blue, 6-bit green, 5-bit red. BGR byte order, unsigned normalized. 16 BPP.
	 */
	B5G6R5,
	/**
	 * Packed 16-bit, 5-bit red, 6-bit green, 5-bit blue. RGB byte order, unsigned normalized. 16 BPP.
	 */
	R5G6B5,
	/**
	 * Packed 16-bit, 4-bit per channel (blue, green, red, alpha). BGRA byte order, unsigned normalized. 16 BPP.
	 */
	BGRA4,
	/**
	 * Packed 16-bit, 4-bit per channel (red, green, blue, alpha), unsigned normalized. 16 BPP.
	 */
	RGBA4,
	/**
	 * Packed 16-bit, 5-bit blue, 5-bit green, 5-bit red, 1-bit alpha. BGRA byte order, unsigned normalized. 16 BPP.
	 */
	BGR5A1,
	/**
	 * Packed 16-bit, 5-bit red, 5-bit green, 5-bit blue, 1-bit alpha, unsigned normalized. 16 BPP.
	 */
	RGB5A1,
	/**
	 * Packed 32-bit, 10-bit red, 10-bit green, 10-bit blue, 2-bit alpha, unsigned normalized. 32 BPP.
	 */
	RGB10A2,
	/**
	 * Packed 32-bit, 10-bit red, 10-bit green, 10-bit blue, 2-bit alpha, unsigned integer. 32 BPP.
	 */
	RGB10A2U,
	/**
	 * Packed 32-bit, 11-bit red, 11-bit green, 10-bit blue, unsigned floating point. No alpha. 32 BPP.
	 */
	RG11B10F,
	/**
	 * Depth formats below.
	 */
	UNKNOWNDEPTH,
	/**
	 * 16-bit depth, unsigned normalized. 16 BPP.
	 */
	D16,
	/**
	 * 24-bit depth, unsigned normalized (stored as 32-bit with 8 bits unused). 32 BPP.
	 */
	D24,
	/**
	 * 24-bit depth, unsigned normalized, with 8-bit stencil. 32 BPP.
	 */
	D24S8,
	/**
	 * 32-bit depth, unsigned normalized. 32 BPP.
	 */
	D32,
	/**
	 * 16-bit depth, floating point. 16 BPP.
	 */
	D16F,
	/**
	 * 24-bit depth, floating point (stored as 32-bit). 32 BPP.
	 */
	D24F,
	/**
	 * 32-bit depth, floating point. 32 BPP.
	 */
	D32F,
	/**
	 * 32-bit depth, floating point, with 8-bit stencil (stored as 64-bit). 64 BPP.
	 */
	D32FS8,
	/**
	 * 8-bit stencil only, no depth. 8 BPP.
	 */
	D0S8,

	/**
	 * Number of native enum values.
	 */
	COUNT;

	/**
	 * Native C enum layout.
	 */
	public static final ValueLayout.OfInt LAYOUT = ValueLayout.JAVA_INT;
	private static final TextureFormat[] VALUES = values();

	/**
	 * Returns the enum constant for a native C enum value.
	 * @param value the native enum value
	 * @return the matching enum constant
	 */
	public static TextureFormat fromValue(int value) {
		if (value >= 0 && value < VALUES.length) {
			return VALUES[value];
		}
		throw new IllegalArgumentException("Unknown TextureFormat value: " + value);
	}
}
