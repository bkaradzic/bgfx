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
 * Constants for Sampler flags.
 */
@NullMarked
public final class SamplerFlags {
	private SamplerFlags() {
	}
	/**
	 * Wrap U mode: Mirror
	 */
	public static final int UMirror = 0x00000001;

	/**
	 * Wrap U mode: Clamp
	 */
	public static final int UClamp = 0x00000002;

	/**
	 * Wrap U mode: Border
	 */
	public static final int UBorder = 0x00000003;

	/**
	 * Sampler flag value {@code UShift}.
	 */
	public static final int UShift = 0;

	/**
	 * Sampler flag value {@code UMask}.
	 */
	public static final int UMask = 0x00000003;

	/**
	 * Wrap V mode: Mirror
	 */
	public static final int VMirror = 0x00000004;

	/**
	 * Wrap V mode: Clamp
	 */
	public static final int VClamp = 0x00000008;

	/**
	 * Wrap V mode: Border
	 */
	public static final int VBorder = 0x0000000c;

	/**
	 * Sampler flag value {@code VShift}.
	 */
	public static final int VShift = 2;

	/**
	 * Sampler flag value {@code VMask}.
	 */
	public static final int VMask = 0x0000000c;

	/**
	 * Wrap W mode: Mirror
	 */
	public static final int WMirror = 0x00000010;

	/**
	 * Wrap W mode: Clamp
	 */
	public static final int WClamp = 0x00000020;

	/**
	 * Wrap W mode: Border
	 */
	public static final int WBorder = 0x00000030;

	/**
	 * Sampler flag value {@code WShift}.
	 */
	public static final int WShift = 4;

	/**
	 * Sampler flag value {@code WMask}.
	 */
	public static final int WMask = 0x00000030;

	/**
	 * Min sampling mode: Point
	 */
	public static final int MinPoint = 0x00000040;

	/**
	 * Min sampling mode: Anisotropic
	 */
	public static final int MinAnisotropic = 0x00000080;

	/**
	 * Sampler flag value {@code MinShift}.
	 */
	public static final int MinShift = 6;

	/**
	 * Sampler flag value {@code MinMask}.
	 */
	public static final int MinMask = 0x000000c0;

	/**
	 * Mag sampling mode: Point
	 */
	public static final int MagPoint = 0x00000100;

	/**
	 * Mag sampling mode: Anisotropic
	 */
	public static final int MagAnisotropic = 0x00000200;

	/**
	 * Sampler flag value {@code MagShift}.
	 */
	public static final int MagShift = 8;

	/**
	 * Sampler flag value {@code MagMask}.
	 */
	public static final int MagMask = 0x00000300;

	/**
	 * Mip sampling mode: Point
	 */
	public static final int MipPoint = 0x00000400;

	/**
	 * Sampler flag value {@code MipShift}.
	 */
	public static final int MipShift = 10;

	/**
	 * Sampler flag value {@code MipMask}.
	 */
	public static final int MipMask = 0x00000400;

	/**
	 * Compare when sampling depth texture: less.
	 */
	public static final int CompareLess = 0x00010000;

	/**
	 * Compare when sampling depth texture: less or equal.
	 */
	public static final int CompareLequal = 0x00020000;

	/**
	 * Compare when sampling depth texture: equal.
	 */
	public static final int CompareEqual = 0x00030000;

	/**
	 * Compare when sampling depth texture: greater or equal.
	 */
	public static final int CompareGequal = 0x00040000;

	/**
	 * Compare when sampling depth texture: greater.
	 */
	public static final int CompareGreater = 0x00050000;

	/**
	 * Compare when sampling depth texture: not equal.
	 */
	public static final int CompareNotequal = 0x00060000;

	/**
	 * Compare when sampling depth texture: never.
	 */
	public static final int CompareNever = 0x00070000;

	/**
	 * Compare when sampling depth texture: always.
	 */
	public static final int CompareAlways = 0x00080000;

	/**
	 * Sampler flag value {@code CompareShift}.
	 */
	public static final int CompareShift = 16;

	/**
	 * Sampler flag value {@code CompareMask}.
	 */
	public static final int CompareMask = 0x000f0000;

	/**
	 * Sampler flag value {@code BorderColorShift}.
	 */
	public static final int BorderColorShift = 24;

	/**
	 * Sampler flag value {@code BorderColorMask}.
	 */
	public static final int BorderColorMask = 0x0f000000;

	/**
	 * Sampler flag value {@code ReservedShift}.
	 */
	public static final int ReservedShift = 28;

	/**
	 * Sampler flag value {@code ReservedMask}.
	 */
	public static final int ReservedMask = 0xf0000000;

	/**
	 * Sampler flag value {@code None}.
	 */
	public static final int None = 0x00000000;

	/**
	 * Sample stencil instead of depth.
	 */
	public static final int SampleStencil = 0x00100000;

	/**
	 * Sampler flag value {@code Point}.
	 */
	public static final int Point = 0x00000540;

	/**
	 * Sampler flag value {@code UvwMirror}.
	 */
	public static final int UvwMirror = 0x00000015;

	/**
	 * Sampler flag value {@code UvwClamp}.
	 */
	public static final int UvwClamp = 0x0000002a;

	/**
	 * Sampler flag value {@code UvwBorder}.
	 */
	public static final int UvwBorder = 0x0000003f;

	/**
	 * Sampler flag value {@code BitsMask}.
	 */
	public static final int BitsMask = 0x000f07ff;
}
