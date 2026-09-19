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
 * Topology sort order.
 */
@NullMarked
public enum TopologySort {
	/**
	 * TopologySort value {@code DIRECTION_FRONT_TO_BACK_MIN}.
	 */
	DIRECTION_FRONT_TO_BACK_MIN,
	/**
	 * TopologySort value {@code DIRECTION_FRONT_TO_BACK_AVG}.
	 */
	DIRECTION_FRONT_TO_BACK_AVG,
	/**
	 * TopologySort value {@code DIRECTION_FRONT_TO_BACK_MAX}.
	 */
	DIRECTION_FRONT_TO_BACK_MAX,
	/**
	 * TopologySort value {@code DIRECTION_BACK_TO_FRONT_MIN}.
	 */
	DIRECTION_BACK_TO_FRONT_MIN,
	/**
	 * TopologySort value {@code DIRECTION_BACK_TO_FRONT_AVG}.
	 */
	DIRECTION_BACK_TO_FRONT_AVG,
	/**
	 * TopologySort value {@code DIRECTION_BACK_TO_FRONT_MAX}.
	 */
	DIRECTION_BACK_TO_FRONT_MAX,
	/**
	 * TopologySort value {@code DISTANCE_FRONT_TO_BACK_MIN}.
	 */
	DISTANCE_FRONT_TO_BACK_MIN,
	/**
	 * TopologySort value {@code DISTANCE_FRONT_TO_BACK_AVG}.
	 */
	DISTANCE_FRONT_TO_BACK_AVG,
	/**
	 * TopologySort value {@code DISTANCE_FRONT_TO_BACK_MAX}.
	 */
	DISTANCE_FRONT_TO_BACK_MAX,
	/**
	 * TopologySort value {@code DISTANCE_BACK_TO_FRONT_MIN}.
	 */
	DISTANCE_BACK_TO_FRONT_MIN,
	/**
	 * TopologySort value {@code DISTANCE_BACK_TO_FRONT_AVG}.
	 */
	DISTANCE_BACK_TO_FRONT_AVG,
	/**
	 * TopologySort value {@code DISTANCE_BACK_TO_FRONT_MAX}.
	 */
	DISTANCE_BACK_TO_FRONT_MAX,

	/**
	 * Number of native enum values.
	 */
	COUNT;

	/**
	 * Native C enum layout.
	 */
	public static final ValueLayout.OfInt LAYOUT = ValueLayout.JAVA_INT;
	private static final TopologySort[] VALUES = values();

	/**
	 * Returns the enum constant for a native C enum value.
	 * @param value the native enum value
	 * @return the matching enum constant
	 */
	public static TopologySort fromValue(int value) {
		if (value >= 0 && value < VALUES.length) {
			return VALUES[value];
		}
		throw new IllegalArgumentException("Unknown TopologySort value: " + value);
	}
}
