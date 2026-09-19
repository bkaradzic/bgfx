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
 * Encoder stats.
 */
@NullMarked
public final class EncoderStats extends NativeObject {
	/**
	 * Native C structure layout.
	 */
	public static final StructLayout LAYOUT = cStruct("bgfx_encoder_stats_t",
		ValueLayout.JAVA_LONG.withName("cpuTimeBegin"),
		ValueLayout.JAVA_LONG.withName("cpuTimeEnd"));
	private static final VarHandle VH_CPUTIMEBEGIN = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("cpuTimeBegin"));
	private static final VarHandle VH_CPUTIMEEND = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("cpuTimeEnd"));
	/**
	 * Wraps an existing native structure.
	 * @param segment native memory segment
	 */
	public EncoderStats(MemorySegment segment) {
		super(segment, LAYOUT);
	}

	/**
	 * Allocates a native structure.
	 * @param allocator destination allocator
	 */
	public EncoderStats(SegmentAllocator allocator) {
		super(allocator, LAYOUT);
	}

	/**
	 * Encoder thread CPU submit begin time.
	 * @return the field value
	 */
	public long cpuTimeBegin() {
		return (long) VH_CPUTIMEBEGIN.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code cpuTimeBegin} field and returns {@code this}.
	 * @param value the new field value
	 */
	public EncoderStats cpuTimeBegin(long value) {
		VH_CPUTIMEBEGIN.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Encoder thread CPU submit end time.
	 * @return the field value
	 */
	public long cpuTimeEnd() {
		return (long) VH_CPUTIMEEND.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code cpuTimeEnd} field and returns {@code this}.
	 * @param value the new field value
	 */
	public EncoderStats cpuTimeEnd(long value) {
		VH_CPUTIMEEND.set(segment(), 0L, value);
		return this;
	}
}
