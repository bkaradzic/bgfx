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
 * Constants for Texture flags.
 */
@NullMarked
public final class TextureFlags {
	private TextureFlags() {
	}

	/**
	 * Texture flag value {@code None}.
	 */
	public static final long None = 0x0000000000000000L;

	/**
	 * Texture will be used for MSAA sampling.
	 */
	public static final long MsaaSample = 0x0000000800000000L;

	/**
	 * Render target no MSAA.
	 */
	public static final long Rt = 0x0000001000000000L;

	/**
	 * Texture will be used for compute write.
	 */
	public static final long ComputeWrite = 0x0000100000000000L;

	/**
	 * Sample texture as sRGB.
	 */
	public static final long Srgb = 0x0000200000000000L;

	/**
	 * Texture will be used as blit destination.
	 */
	public static final long BlitDst = 0x0000400000000000L;

	/**
	 * Texture will be used for read back from GPU.
	 */
	public static final long ReadBack = 0x0000800000000000L;

	/**
	 * Texture is shared with other device or other process.
	 */
	public static final long ExternalShared = 0x0001000000000000L;

	/**
	 * Texture flag value {@code ReservedShift}.
	 */
	public static final long ReservedShift = 60;

	/**
	 * Texture flag value {@code ReservedMask}.
	 */
	public static final long ReservedMask = 0xf000000000000000L;

	/**
	 * Render target MSAAx2 mode.
	 */
	public static final long RtMsaaX2 = 0x0000002000000000L;

	/**
	 * Render target MSAAx4 mode.
	 */
	public static final long RtMsaaX4 = 0x0000003000000000L;

	/**
	 * Render target MSAAx8 mode.
	 */
	public static final long RtMsaaX8 = 0x0000004000000000L;

	/**
	 * Render target MSAAx16 mode.
	 */
	public static final long RtMsaaX16 = 0x0000005000000000L;

	/**
	 * Texture flag value {@code RtMsaaShift}.
	 */
	public static final long RtMsaaShift = 36;

	/**
	 * Texture flag value {@code RtMsaaMask}.
	 */
	public static final long RtMsaaMask = 0x0000007000000000L;

	/**
	 * Render target will be used for writing
	 */
	public static final long RtWriteOnly = 0x0000008000000000L;

	/**
	 * Texture flag value {@code RtShift}.
	 */
	public static final long RtShift = 36;

	/**
	 * Texture flag value {@code RtMask}.
	 */
	public static final long RtMask = 0x000000f000000000L;
}
