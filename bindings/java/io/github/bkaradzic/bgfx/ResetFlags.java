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
 * Constants for Reset flags.
 */
@NullMarked
public final class ResetFlags {
	private ResetFlags() {
	}
	/**
	 * Enable 2x MSAA.
	 */
	public static final int MsaaX2 = 0x00000010;

	/**
	 * Enable 4x MSAA.
	 */
	public static final int MsaaX4 = 0x00000020;

	/**
	 * Enable 8x MSAA.
	 */
	public static final int MsaaX8 = 0x00000030;

	/**
	 * Enable 16x MSAA.
	 */
	public static final int MsaaX16 = 0x00000040;

	/**
	 * Reset flag value {@code MsaaShift}.
	 */
	public static final int MsaaShift = 4;

	/**
	 * Reset flag value {@code MsaaMask}.
	 */
	public static final int MsaaMask = 0x00000070;

	/**
	 * No reset flags.
	 */
	public static final int None = 0x00000000;

	/**
	 * Not supported yet.
	 */
	public static final int Fullscreen = 0x00000001;

	/**
	 * Enable V-Sync.
	 */
	public static final int Vsync = 0x00000080;

	/**
	 * Turn on/off max anisotropy.
	 */
	public static final int Maxanisotropy = 0x00000100;

	/**
	 * Begin screen capture.
	 */
	public static final int Capture = 0x00000200;

	/**
	 * Flush rendering after submitting to GPU.
	 */
	public static final int FlushAfterRender = 0x00002000;

	/**
	 * This flag specifies where flip occurs. Default behaviour is that flip occurs
	 * before rendering new frame. This flag only has effect when {@code BGFX_CONFIG_MULTITHREADED=0}.
	 */
	public static final int FlipAfterRender = 0x00004000;

	/**
	 * Enable sRGB backbuffer.
	 */
	public static final int SrgbBackbuffer = 0x00008000;

	/**
	 * Enable HDR10 rendering.
	 */
	public static final int Hdr10 = 0x00010000;

	/**
	 * Enable HiDPI rendering.
	 */
	public static final int Hidpi = 0x00020000;

	/**
	 * Suspend rendering.
	 */
	public static final int Suspend = 0x00080000;

	/**
	 * Transparent backbuffer. Availability depends on: {@code BGFX_CAPS_TRANSPARENT_BACKBUFFER}.
	 */
	public static final int TransparentBackbuffer = 0x00100000;

	/**
	 * Reset flag value {@code FullscreenShift}.
	 */
	public static final int FullscreenShift = 0;

	/**
	 * Reset flag value {@code FullscreenMask}.
	 */
	public static final int FullscreenMask = 0x00000001;

	/**
	 * Reset flag value {@code ReservedShift}.
	 */
	public static final int ReservedShift = 31;

	/**
	 * Reset flag value {@code ReservedMask}.
	 */
	public static final int ReservedMask = 0x80000000;
}
