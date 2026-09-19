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
 * Vertex attribute enum.
 */
@NullMarked
public enum Attrib {
	/**
	 * a_position
	 */
	POSITION,
	/**
	 * a_normal
	 */
	NORMAL,
	/**
	 * a_tangent
	 */
	TANGENT,
	/**
	 * a_bitangent
	 */
	BITANGENT,
	/**
	 * a_color0
	 */
	COLOR0,
	/**
	 * a_color1
	 */
	COLOR1,
	/**
	 * a_color2
	 */
	COLOR2,
	/**
	 * a_color3
	 */
	COLOR3,
	/**
	 * a_indices
	 */
	INDICES,
	/**
	 * a_weight
	 */
	WEIGHT,
	/**
	 * a_texcoord0
	 */
	TEXCOORD0,
	/**
	 * a_texcoord1
	 */
	TEXCOORD1,
	/**
	 * a_texcoord2
	 */
	TEXCOORD2,
	/**
	 * a_texcoord3
	 */
	TEXCOORD3,
	/**
	 * a_texcoord4
	 */
	TEXCOORD4,
	/**
	 * a_texcoord5
	 */
	TEXCOORD5,
	/**
	 * a_texcoord6
	 */
	TEXCOORD6,
	/**
	 * a_texcoord7
	 */
	TEXCOORD7,
	/**
	 * a_texcoord8
	 */
	TEXCOORD8,
	/**
	 * a_texcoord9
	 */
	TEXCOORD9,
	/**
	 * a_texcoord10
	 */
	TEXCOORD10,
	/**
	 * a_texcoord11
	 */
	TEXCOORD11,
	/**
	 * a_texcoord12
	 */
	TEXCOORD12,
	/**
	 * a_texcoord13
	 */
	TEXCOORD13,
	/**
	 * a_texcoord14
	 */
	TEXCOORD14,
	/**
	 * a_texcoord15
	 */
	TEXCOORD15,

	/**
	 * Number of native enum values.
	 */
	COUNT;

	/**
	 * Native C enum layout.
	 */
	public static final ValueLayout.OfInt LAYOUT = ValueLayout.JAVA_INT;
	private static final Attrib[] VALUES = values();

	/**
	 * Returns the enum constant for a native C enum value.
	 * @param value the native enum value
	 * @return the matching enum constant
	 */
	public static Attrib fromValue(int value) {
		if (value >= 0 && value < VALUES.length) {
			return VALUES[value];
		}
		throw new IllegalArgumentException("Unknown Attrib value: " + value);
	}
}
