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
 * Fatal error enum.
 */
@NullMarked
public enum Fatal {
	/**
	 * Fatal value {@code DEBUG_CHECK}.
	 */
	DEBUG_CHECK,
	/**
	 * Fatal value {@code INVALID_SHADER}.
	 */
	INVALID_SHADER,
	/**
	 * Fatal value {@code UNABLE_TO_INITIALIZE}.
	 */
	UNABLE_TO_INITIALIZE,
	/**
	 * Fatal value {@code UNABLE_TO_CREATE_TEXTURE}.
	 */
	UNABLE_TO_CREATE_TEXTURE,
	/**
	 * Fatal value {@code DEVICE_LOST}.
	 */
	DEVICE_LOST,

	/**
	 * Number of native enum values.
	 */
	COUNT;

	/**
	 * Native C enum layout.
	 */
	public static final ValueLayout.OfInt LAYOUT = ValueLayout.JAVA_INT;
	private static final Fatal[] VALUES = values();

	/**
	 * Returns the enum constant for a native C enum value.
	 * @param value the native enum value
	 * @return the matching enum constant
	 */
	public static Fatal fromValue(int value) {
		if (value >= 0 && value < VALUES.length) {
			return VALUES[value];
		}
		throw new IllegalArgumentException("Unknown Fatal value: " + value);
	}
}
