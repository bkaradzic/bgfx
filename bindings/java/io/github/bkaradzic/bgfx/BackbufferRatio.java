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
import org.jspecify.annotations.Nullable;

import io.github.bkaradzic.bgfx.*;
import io.github.bkaradzic.bgfx.util.FFMUtil;
import io.github.bkaradzic.bgfx.util.NativeObject;
import io.github.bkaradzic.bgfx.util.Unsigned;
import static io.github.bkaradzic.bgfx.Bgfx.*;
import static io.github.bkaradzic.bgfx.util.FFMUtil.*;

/**
 * Backbuffer ratio enum.
 * <p>
 * The ratio is always relative to the window bgfx was initialized with, and is
 * re-resolved by {@code reset}. It is not relative to whichever window a texture
 * happens to be rendered to, so on a second window a ratio texture is not
 * meaningfully sized. For that reason a ratio texture cannot be used as
 * {@code SwapChain.depth}.
 */
@NullMarked
public enum BackbufferRatio {
	/**
	 * Equal to the main window's backbuffer.
	 */
	EQUAL,
	/**
	 * One half size of the main window's backbuffer.
	 */
	HALF,
	/**
	 * One quarter size of the main window's backbuffer.
	 */
	QUARTER,
	/**
	 * One eighth size of the main window's backbuffer.
	 */
	EIGHTH,
	/**
	 * One sixteenth size of the main window's backbuffer.
	 */
	SIXTEENTH,
	/**
	 * Double size of the main window's backbuffer.
	 */
	DOUBLE,

	/**
	 * Number of native enum values.
	 */
	COUNT;

	/**
	 * Native C enum layout.
	 */
	public static final ValueLayout.OfInt LAYOUT = ValueLayout.JAVA_INT;
	private static final BackbufferRatio[] VALUES = values();

	/**
	 * Returns the enum constant for a native C enum value.
	 * @param value the native enum value
	 * @return the matching enum constant
	 */
	public static BackbufferRatio fromValue(int value) {
		if (value >= 0 && value < VALUES.length) {
			return VALUES[value];
		}
		throw new IllegalArgumentException("Unknown BackbufferRatio value: " + value);
	}
}
