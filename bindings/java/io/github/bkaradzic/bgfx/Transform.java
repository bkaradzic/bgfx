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
 * Transform data.
 */
@NullMarked
public final class Transform extends NativeObject {
	/**
	 * Native C structure layout.
	 */
	public static final StructLayout LAYOUT = cStruct("bgfx_transform_t",
		ValueLayout.ADDRESS.withName("data"),
		ValueLayout.JAVA_SHORT.withName("num"));
	private static final VarHandle VH_DATA = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("data"));
	private static final VarHandle VH_NUM = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("num"));
	/**
	 * Wraps an existing native structure.
	 * @param segment native memory segment
	 */
	public Transform(MemorySegment segment) {
		super(segment, LAYOUT);
	}

	/**
	 * Allocates a native structure.
	 * @param allocator destination allocator
	 */
	public Transform(SegmentAllocator allocator) {
		super(allocator, LAYOUT);
	}

	/**
	 * Pointer to first 4x4 matrix.
	 * @return the field value
	 */
	public MemorySegment data() {
		return address((MemorySegment) VH_DATA.get(segment(), 0L));
	}

	/**
	 * Sets the native {@code data} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Transform data(MemorySegment value) {
		VH_DATA.set(segment(), 0L, address(value));
		return this;
	}

	/**
	 * Number of matrices.
	 * @return the field value
	 */
	public @Unsigned short num() {
		return (@Unsigned short) VH_NUM.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code num} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Transform num(@Unsigned short value) {
		VH_NUM.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Sets the native {@code num} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Transform num(int value) {
		return num(NativeObject.toUnsignedShort(value));
	}
}
