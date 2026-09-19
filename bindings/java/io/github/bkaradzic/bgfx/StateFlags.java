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
 * Constants for State flags.
 */
@NullMarked
public final class StateFlags {
	private StateFlags() {
	}
	/**
	 * Enable R write.
	 */
	public static final long WriteR = 0x0000000000000001L;

	/**
	 * Enable G write.
	 */
	public static final long WriteG = 0x0000000000000002L;

	/**
	 * Enable B write.
	 */
	public static final long WriteB = 0x0000000000000004L;

	/**
	 * Enable alpha write.
	 */
	public static final long WriteA = 0x0000000000000008L;

	/**
	 * Enable depth write.
	 */
	public static final long WriteZ = 0x0000004000000000L;

	/**
	 * Enable RGB write.
	 */
	public static final long WriteRgb = 0x0000000000000007L;

	/**
	 * Write all channels mask.
	 */
	public static final long WriteMask = 0x000000400000000fL;

	/**
	 * Enable depth test, less.
	 */
	public static final long DepthTestLess = 0x0000000000000010L;

	/**
	 * Enable depth test, less or equal.
	 */
	public static final long DepthTestLequal = 0x0000000000000020L;

	/**
	 * Enable depth test, equal.
	 */
	public static final long DepthTestEqual = 0x0000000000000030L;

	/**
	 * Enable depth test, greater or equal.
	 */
	public static final long DepthTestGequal = 0x0000000000000040L;

	/**
	 * Enable depth test, greater.
	 */
	public static final long DepthTestGreater = 0x0000000000000050L;

	/**
	 * Enable depth test, not equal.
	 */
	public static final long DepthTestNotequal = 0x0000000000000060L;

	/**
	 * Enable depth test, never.
	 */
	public static final long DepthTestNever = 0x0000000000000070L;

	/**
	 * Enable depth test, always.
	 */
	public static final long DepthTestAlways = 0x0000000000000080L;

	/**
	 * State flag value {@code DepthTestShift}.
	 */
	public static final long DepthTestShift = 4;

	/**
	 * State flag value {@code DepthTestMask}.
	 */
	public static final long DepthTestMask = 0x00000000000000f0L;

	/**
	 * 0, 0, 0, 0
	 */
	public static final long BlendZero = 0x0000000000001000L;

	/**
	 * 1, 1, 1, 1
	 */
	public static final long BlendOne = 0x0000000000002000L;

	/**
	 * Rs, Gs, Bs, As
	 */
	public static final long BlendSrcColor = 0x0000000000003000L;

	/**
	 * 1-Rs, 1-Gs, 1-Bs, 1-As
	 */
	public static final long BlendInvSrcColor = 0x0000000000004000L;

	/**
	 * As, As, As, As
	 */
	public static final long BlendSrcAlpha = 0x0000000000005000L;

	/**
	 * 1-As, 1-As, 1-As, 1-As
	 */
	public static final long BlendInvSrcAlpha = 0x0000000000006000L;

	/**
	 * Ad, Ad, Ad, Ad
	 */
	public static final long BlendDstAlpha = 0x0000000000007000L;

	/**
	 * 1-Ad, 1-Ad, 1-Ad ,1-Ad
	 */
	public static final long BlendInvDstAlpha = 0x0000000000008000L;

	/**
	 * Rd, Gd, Bd, Ad
	 */
	public static final long BlendDstColor = 0x0000000000009000L;

	/**
	 * 1-Rd, 1-Gd, 1-Bd, 1-Ad
	 */
	public static final long BlendInvDstColor = 0x000000000000a000L;

	/**
	 * f, f, f, 1; f = min(As, 1-Ad)
	 */
	public static final long BlendSrcAlphaSat = 0x000000000000b000L;

	/**
	 * Blend factor
	 */
	public static final long BlendFactor = 0x000000000000c000L;

	/**
	 * 1-Blend factor
	 */
	public static final long BlendInvFactor = 0x000000000000d000L;

	/**
	 * State flag value {@code BlendShift}.
	 */
	public static final long BlendShift = 12;

	/**
	 * State flag value {@code BlendMask}.
	 */
	public static final long BlendMask = 0x000000000ffff000L;

	/**
	 * Blend add: src + dst.
	 */
	public static final long BlendEquationAdd = 0x0000000000000000L;

	/**
	 * Blend subtract: src - dst.
	 */
	public static final long BlendEquationSub = 0x0000000010000000L;

	/**
	 * Blend reverse subtract: dst - src.
	 */
	public static final long BlendEquationRevsub = 0x0000000020000000L;

	/**
	 * Blend min: min(src, dst).
	 */
	public static final long BlendEquationMin = 0x0000000030000000L;

	/**
	 * Blend max: max(src, dst).
	 */
	public static final long BlendEquationMax = 0x0000000040000000L;

	/**
	 * State flag value {@code BlendEquationShift}.
	 */
	public static final long BlendEquationShift = 28;

	/**
	 * State flag value {@code BlendEquationMask}.
	 */
	public static final long BlendEquationMask = 0x00000003f0000000L;

	/**
	 * Cull clockwise triangles.
	 */
	public static final long CullCw = 0x0000001000000000L;

	/**
	 * Cull counter-clockwise triangles.
	 */
	public static final long CullCcw = 0x0000002000000000L;

	/**
	 * State flag value {@code CullShift}.
	 */
	public static final long CullShift = 36;

	/**
	 * State flag value {@code CullMask}.
	 */
	public static final long CullMask = 0x0000003000000000L;

	/**
	 * State flag value {@code AlphaRefShift}.
	 */
	public static final long AlphaRefShift = 40;

	/**
	 * State flag value {@code AlphaRefMask}.
	 */
	public static final long AlphaRefMask = 0x0000ff0000000000L;

	/**
	 * Tristrip.
	 */
	public static final long PtTristrip = 0x0001000000000000L;

	/**
	 * Lines.
	 */
	public static final long PtLines = 0x0002000000000000L;

	/**
	 * Line strip.
	 */
	public static final long PtLinestrip = 0x0003000000000000L;

	/**
	 * Points.
	 */
	public static final long PtPoints = 0x0004000000000000L;

	/**
	 * State flag value {@code PtShift}.
	 */
	public static final long PtShift = 48;

	/**
	 * State flag value {@code PtMask}.
	 */
	public static final long PtMask = 0x0007000000000000L;

	/**
	 * State flag value {@code PointSizeShift}.
	 */
	public static final long PointSizeShift = 52;

	/**
	 * State flag value {@code PointSizeMask}.
	 */
	public static final long PointSizeMask = 0x00f0000000000000L;

	/**
	 * Enable MSAA rasterization.
	 */
	public static final long Msaa = 0x0100000000000000L;

	/**
	 * Enable line AA rasterization.
	 */
	public static final long Lineaa = 0x0200000000000000L;

	/**
	 * Enable conservative rasterization.
	 */
	public static final long ConservativeRaster = 0x0400000000000000L;

	/**
	 * No state.
	 */
	public static final long None = 0x0000000000000000L;

	/**
	 * Front counter-clockwise (default is clockwise).
	 */
	public static final long FrontCcw = 0x0000008000000000L;

	/**
	 * Enable blend independent.
	 */
	public static final long BlendIndependent = 0x0000000400000000L;

	/**
	 * Enable alpha to coverage.
	 */
	public static final long BlendAlphaToCoverage = 0x0000000800000000L;

	/**
	 * Default state is write to RGB, alpha, and depth with depth test less enabled, with clockwise
	 * culling and MSAA (when writing into MSAA frame buffer, otherwise this flag is ignored).
	 */
	public static final long Default = 0x010000500000001fL;

	/**
	 * State flag value {@code Mask}.
	 */
	public static final long Mask = 0xffffffffffffffffL;

	/**
	 * State flag value {@code ReservedShift}.
	 */
	public static final long ReservedShift = 61;

	/**
	 * State flag value {@code ReservedMask}.
	 */
	public static final long ReservedMask = 0xe000000000000000L;
}
