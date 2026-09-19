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
 * Constants for Stencil flags.
 */
@NullMarked
public final class StencilFlags {
	private StencilFlags() {
	}

	/**
	 * Stencil flag value {@code FuncRefShift}.
	 */
	public static final int FuncRefShift = 0;

	/**
	 * Stencil flag value {@code FuncRefMask}.
	 */
	public static final int FuncRefMask = 0x000000ff;

	/**
	 * Stencil flag value {@code FuncRmaskShift}.
	 */
	public static final int FuncRmaskShift = 8;

	/**
	 * Stencil flag value {@code FuncRmaskMask}.
	 */
	public static final int FuncRmaskMask = 0x0000ff00;

	/**
	 * No stencil test.
	 */
	public static final int None = 0x0000ff00;

	/**
	 * Stencil front or back mask.
	 */
	public static final int Mask = 0xffffffff;

	/**
	 * Enable stencil test, less.
	 */
	public static final int TestLess = 0x00010000;

	/**
	 * Enable stencil test, less or equal.
	 */
	public static final int TestLequal = 0x00020000;

	/**
	 * Enable stencil test, equal.
	 */
	public static final int TestEqual = 0x00030000;

	/**
	 * Enable stencil test, greater or equal.
	 */
	public static final int TestGequal = 0x00040000;

	/**
	 * Enable stencil test, greater.
	 */
	public static final int TestGreater = 0x00050000;

	/**
	 * Enable stencil test, not equal.
	 */
	public static final int TestNotequal = 0x00060000;

	/**
	 * Enable stencil test, never.
	 */
	public static final int TestNever = 0x00070000;

	/**
	 * Enable stencil test, always.
	 */
	public static final int TestAlways = 0x00080000;

	/**
	 * Stencil flag value {@code TestShift}.
	 */
	public static final int TestShift = 16;

	/**
	 * Stencil flag value {@code TestMask}.
	 */
	public static final int TestMask = 0x000f0000;

	/**
	 * Zero.
	 */
	public static final int OpFailSZero = 0x00000000;

	/**
	 * Keep.
	 */
	public static final int OpFailSKeep = 0x00100000;

	/**
	 * Replace.
	 */
	public static final int OpFailSReplace = 0x00200000;

	/**
	 * Increment and wrap.
	 */
	public static final int OpFailSIncr = 0x00300000;

	/**
	 * Increment and clamp.
	 */
	public static final int OpFailSIncrsat = 0x00400000;

	/**
	 * Decrement and wrap.
	 */
	public static final int OpFailSDecr = 0x00500000;

	/**
	 * Decrement and clamp.
	 */
	public static final int OpFailSDecrsat = 0x00600000;

	/**
	 * Invert.
	 */
	public static final int OpFailSInvert = 0x00700000;

	/**
	 * Stencil flag value {@code OpFailSShift}.
	 */
	public static final int OpFailSShift = 20;

	/**
	 * Stencil flag value {@code OpFailSMask}.
	 */
	public static final int OpFailSMask = 0x00f00000;

	/**
	 * Zero.
	 */
	public static final int OpFailZZero = 0x00000000;

	/**
	 * Keep.
	 */
	public static final int OpFailZKeep = 0x01000000;

	/**
	 * Replace.
	 */
	public static final int OpFailZReplace = 0x02000000;

	/**
	 * Increment and wrap.
	 */
	public static final int OpFailZIncr = 0x03000000;

	/**
	 * Increment and clamp.
	 */
	public static final int OpFailZIncrsat = 0x04000000;

	/**
	 * Decrement and wrap.
	 */
	public static final int OpFailZDecr = 0x05000000;

	/**
	 * Decrement and clamp.
	 */
	public static final int OpFailZDecrsat = 0x06000000;

	/**
	 * Invert.
	 */
	public static final int OpFailZInvert = 0x07000000;

	/**
	 * Stencil flag value {@code OpFailZShift}.
	 */
	public static final int OpFailZShift = 24;

	/**
	 * Stencil flag value {@code OpFailZMask}.
	 */
	public static final int OpFailZMask = 0x0f000000;

	/**
	 * Zero.
	 */
	public static final int OpPassZZero = 0x00000000;

	/**
	 * Keep.
	 */
	public static final int OpPassZKeep = 0x10000000;

	/**
	 * Replace.
	 */
	public static final int OpPassZReplace = 0x20000000;

	/**
	 * Increment and wrap.
	 */
	public static final int OpPassZIncr = 0x30000000;

	/**
	 * Increment and clamp.
	 */
	public static final int OpPassZIncrsat = 0x40000000;

	/**
	 * Decrement and wrap.
	 */
	public static final int OpPassZDecr = 0x50000000;

	/**
	 * Decrement and clamp.
	 */
	public static final int OpPassZDecrsat = 0x60000000;

	/**
	 * Invert.
	 */
	public static final int OpPassZInvert = 0x70000000;

	/**
	 * Stencil flag value {@code OpPassZShift}.
	 */
	public static final int OpPassZShift = 28;

	/**
	 * Stencil flag value {@code OpPassZMask}.
	 */
	public static final int OpPassZMask = 0xf0000000;
}
