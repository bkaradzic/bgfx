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
 * Vertex attribute type enum.
 */
@NullMarked
public enum AttribType {
	/**
	 * Int8
	 */
	INT8,
	/**
	 * Uint8
	 */
	UINT8,
	/**
	 * Uint10, availability depends on: {@code BGFX_CAPS_VERTEX_ATTRIB_UINT10}.
	 */
	UINT10,
	/**
	 * Int16
	 */
	INT16,
	/**
	 * Uint16
	 */
	UINT16,
	/**
	 * Half.
	 */
	HALF,
	/**
	 * Float
	 */
	FLOAT,
	/**
	 * Int32
	 */
	INT32,
	/**
	 * Uint32
	 */
	UINT32,

	/**
	 * Number of native enum values.
	 */
	COUNT;

	/**
	 * Native C enum layout.
	 */
	public static final ValueLayout.OfInt LAYOUT = ValueLayout.JAVA_INT;
	private static final AttribType[] VALUES = values();

	/**
	 * Returns the enum constant for a native C enum value.
	 * @param value the native enum value
	 * @return the matching enum constant
	 */
	public static AttribType fromValue(int value) {
		if (value >= 0 && value < VALUES.length) {
			return VALUES[value];
		}
		throw new IllegalArgumentException("Unknown AttribType value: " + value);
	}
}
