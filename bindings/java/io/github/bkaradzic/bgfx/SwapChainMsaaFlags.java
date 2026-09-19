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
 * Constants for SwapChainMsaa flags.
 */
@NullMarked
public final class SwapChainMsaaFlags {
	private SwapChainMsaaFlags() {
	}
	/**
	 * Enable 2x MSAA.
	 */
	public static final int X2 = 0x00000010;

	/**
	 * Enable 4x MSAA.
	 */
	public static final int X4 = 0x00000020;

	/**
	 * Enable 8x MSAA.
	 */
	public static final int X8 = 0x00000030;

	/**
	 * Enable 16x MSAA.
	 */
	public static final int X16 = 0x00000040;
	/**
	 * Bit shift for this flag group.
	 */
	public static final int Shift = 4;
	/**
	 * Bit mask for this flag group.
	 */
	public static final int Mask = 0x00000070;
}
