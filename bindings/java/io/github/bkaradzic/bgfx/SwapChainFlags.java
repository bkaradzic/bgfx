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
 * Constants for SwapChain flags.
 */
@NullMarked
public final class SwapChainFlags {
	private SwapChainFlags() {
	}
	/**
	 * No swap chain flags.
	 */
	public static final int None = 0x00000000;

	/**
	 * Not supported yet.
	 */
	public static final int Fullscreen = 0x00000001;

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
	 * Transparent backbuffer. Availability depends on: {@code BGFX_CAPS_TRANSPARENT_BACKBUFFER}.
	 */
	public static final int TransparentBackbuffer = 0x00100000;
}
