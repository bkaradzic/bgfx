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
 * Native bgfx handle.
 * @param idx native handle index
 */
@NullMarked
public record DynamicVertexBufferHandle(short idx) implements AutoCloseable, BufferHandle {
	/**
	 * Native by-value handle layout.
	 */
	public static final StructLayout LAYOUT = cStruct("bgfx_dynamic_vertex_buffer_handle_t",
		ValueLayout.JAVA_SHORT.withName("idx"));
	private static final VarHandle VH_IDX = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("idx"));
	/**
	 * Invalid handle sentinel.
	 */
	public static final DynamicVertexBufferHandle INVALID = new DynamicVertexBufferHandle((short) 0xffff);

	/**
	 * Returns this handle's native tagged-handle type.
	 * @return the native tagged-handle type
	 */
	@Override
	public short type() {
		return (short) 1;
	}

	/**
	 * Returns whether this handle is valid.
	 * @return {@code true} when the handle index is not {@code UINT16_MAX}
	 */
	public boolean isValid() {
		return idx != (short) 0xffff;
	}

	/**
	 * Allocates and writes the native by-value handle representation.
	 * @param allocator the destination allocator
	 * @return the allocated native segment
	 */
	public MemorySegment allocate(SegmentAllocator allocator) {
		MemorySegment segment = allocator.allocate(LAYOUT);
		write(segment);
		return segment;
	}

	/**
	 * Writes this handle to an existing native segment.
	 * @param segment the destination segment
	 */
	public void write(MemorySegment segment) {
		segment = view(segment, LAYOUT);
		VH_IDX.set(segment, 0L, idx);
	}

	/**
	 * Reads a by-value handle from native memory.
	 * @param segment the source segment
	 * @return the decoded handle
	 */
	public static DynamicVertexBufferHandle read(MemorySegment segment) {
		segment = view(segment, LAYOUT);
		return new DynamicVertexBufferHandle((short) VH_IDX.get(segment, 0L));
	}

	/**
	 * Destroys this native handle.
	 */
	@Override
	public void close() {
		Bgfx.destroyDynamicVertexBuffer(this);
	}
}
