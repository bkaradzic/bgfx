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
 * Tagged buffer handle. All buffer handle types implicitly convert to it, and the tag
 * keeps track of which type the handle originally was.
 */
@NullMarked
public sealed interface BufferHandle
	permits DynamicIndexBufferHandle, DynamicVertexBufferHandle, IndexBufferHandle, IndirectBufferHandle, VertexBufferHandle {
	/**
	 * Native by-value handle layout.
	 */
	StructLayout LAYOUT = cStruct("bgfx_buffer_handle_t",
		ValueLayout.JAVA_SHORT.withName("idx"),
		ValueLayout.JAVA_SHORT.withName("type"));
	/**
	 * Native handle-index field accessor.
	 */
	VarHandle VH_IDX = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("idx"));
	/**
	 * Native handle-type field accessor.
	 */
	VarHandle VH_TYPE = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("type"));

	/**
	 * Invalid handle sentinel.
	 */
	BufferHandle INVALID = DynamicIndexBufferHandle.INVALID;

	/**
	 * Returns the native handle index.
	 * @return the native handle index
	 */
	short idx();

	/**
	 * Returns the native handle type tag.
	 * @return the native handle type tag
	 */
	short type();

	/**
	 * Returns whether this handle is valid.
	 * @return {@code true} when the handle index is not {@code UINT16_MAX}
	 */
	default boolean isValid() {
		return idx() != (short) 0xffff;
	}

	/**
	 * Allocates and writes the native tagged handle representation.
	 * @param allocator the destination allocator
	 * @return the allocated native segment
	 */
	default MemorySegment allocateTagged(SegmentAllocator allocator) {
		MemorySegment segment = allocator.allocate(LAYOUT);
		writeTagged(segment);
		return segment;
	}

	/**
	 * Writes this handle to an existing native tagged handle segment.
	 * @param segment the destination segment
	 */
	default void writeTagged(MemorySegment segment) {
		segment = view(segment, LAYOUT);
		VH_IDX.set(segment, 0L, idx());
		VH_TYPE.set(segment, 0L, type());
	}

	/**
	 * Reads a tagged handle from native memory.
	 * @param segment the source segment
	 * @return the decoded handle
	 */
	static BufferHandle read(MemorySegment segment) {
		segment = view(segment, LAYOUT);
		short idx = (short) VH_IDX.get(segment, 0L);
		short type = (short) VH_TYPE.get(segment, 0L);
		return switch (type) {
			case 0 -> new DynamicIndexBufferHandle(idx);
			case 1 -> new DynamicVertexBufferHandle(idx);
			case 2 -> new IndexBufferHandle(idx);
			case 3 -> new IndirectBufferHandle(idx);
			case 4 -> new VertexBufferHandle(idx);
			default -> throw new IllegalArgumentException("Unknown BufferHandle type tag: " + Short.toUnsignedInt(type));
		};
	}
}
