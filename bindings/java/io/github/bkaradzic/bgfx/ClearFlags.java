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
 * Constants for Clear flags.
 */
@NullMarked
public final class ClearFlags {
	private ClearFlags() {
	}
	/**
	 * No clear flags.
	 */
	public static final short None = (short) 0x0000;

	/**
	 * Clear color.
	 */
	public static final short Color = (short) 0x0001;

	/**
	 * Clear depth.
	 */
	public static final short Depth = (short) 0x0002;

	/**
	 * Clear stencil.
	 */
	public static final short Stencil = (short) 0x0004;

	/**
	 * Discard frame buffer attachment 0.
	 */
	public static final short DiscardColor0 = (short) 0x0008;

	/**
	 * Discard frame buffer attachment 1.
	 */
	public static final short DiscardColor1 = (short) 0x0010;

	/**
	 * Discard frame buffer attachment 2.
	 */
	public static final short DiscardColor2 = (short) 0x0020;

	/**
	 * Discard frame buffer attachment 3.
	 */
	public static final short DiscardColor3 = (short) 0x0040;

	/**
	 * Discard frame buffer attachment 4.
	 */
	public static final short DiscardColor4 = (short) 0x0080;

	/**
	 * Discard frame buffer attachment 5.
	 */
	public static final short DiscardColor5 = (short) 0x0100;

	/**
	 * Discard frame buffer attachment 6.
	 */
	public static final short DiscardColor6 = (short) 0x0200;

	/**
	 * Discard frame buffer attachment 7.
	 */
	public static final short DiscardColor7 = (short) 0x0400;

	/**
	 * Discard frame buffer depth attachment.
	 */
	public static final short DiscardDepth = (short) 0x0800;

	/**
	 * Discard frame buffer stencil attachment.
	 */
	public static final short DiscardStencil = (short) 0x1000;

	/**
	 * Clear flag value {@code DiscardColorMask}.
	 */
	public static final short DiscardColorMask = (short) 0x07f8;

	/**
	 * Clear flag value {@code DiscardMask}.
	 */
	public static final short DiscardMask = (short) 0x1ff8;
}
