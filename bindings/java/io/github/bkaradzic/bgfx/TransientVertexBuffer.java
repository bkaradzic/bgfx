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
 * Transient vertex buffer.
 */
@NullMarked
public final class TransientVertexBuffer extends NativeObject {
	/**
	 * Native C structure layout.
	 */
	public static final StructLayout LAYOUT = cStruct("bgfx_transient_vertex_buffer_t",
		ValueLayout.ADDRESS.withName("data"),
		ValueLayout.JAVA_INT.withName("size"),
		ValueLayout.JAVA_INT.withName("startVertex"),
		ValueLayout.JAVA_SHORT.withName("stride"),
		VertexBufferHandle.LAYOUT.withName("handle"),
		VertexLayoutHandle.LAYOUT.withName("layoutHandle"));
	private static final VarHandle VH_DATA = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("data"));
	private static final VarHandle VH_SIZE = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("size"));
	private static final VarHandle VH_STARTVERTEX = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("startVertex"));
	private static final VarHandle VH_STRIDE = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("stride"));
	private static final MethodHandle MH_HANDLE = LAYOUT.sliceHandle(
		MemoryLayout.PathElement.groupElement("handle"));
	private static final MethodHandle MH_LAYOUTHANDLE = LAYOUT.sliceHandle(
		MemoryLayout.PathElement.groupElement("layoutHandle"));
	/**
	 * Wraps an existing native structure.
	 * @param segment native memory segment
	 */
	public TransientVertexBuffer(MemorySegment segment) {
		super(segment, LAYOUT);
	}

	/**
	 * Allocates a native structure.
	 * @param allocator destination allocator
	 */
	public TransientVertexBuffer(SegmentAllocator allocator) {
		super(allocator, LAYOUT);
	}

	/**
	 * Pointer to data.
	 * @return the field value
	 */
	public MemorySegment data() {
		return address((MemorySegment) VH_DATA.get(segment(), 0L));
	}

	/**
	 * Sets the native {@code data} field and returns {@code this}.
	 * @param value the new field value
	 */
	public TransientVertexBuffer data(MemorySegment value) {
		VH_DATA.set(segment(), 0L, address(value));
		return this;
	}

	/**
	 * Data size.
	 * @return the field value
	 */
	public @Unsigned int size() {
		return (@Unsigned int) VH_SIZE.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code size} field and returns {@code this}.
	 * @param value the new field value
	 */
	public TransientVertexBuffer size(@Unsigned int value) {
		VH_SIZE.set(segment(), 0L, value);
		return this;
	}

	/**
	 * First vertex.
	 * @return the field value
	 */
	public @Unsigned int startVertex() {
		return (@Unsigned int) VH_STARTVERTEX.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code startVertex} field and returns {@code this}.
	 * @param value the new field value
	 */
	public TransientVertexBuffer startVertex(@Unsigned int value) {
		VH_STARTVERTEX.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Vertex stride.
	 * @return the field value
	 */
	public @Unsigned short stride() {
		return (@Unsigned short) VH_STRIDE.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code stride} field and returns {@code this}.
	 * @param value the new field value
	 */
	public TransientVertexBuffer stride(@Unsigned short value) {
		VH_STRIDE.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Sets the native {@code stride} field and returns {@code this}.
	 * @param value the new field value
	 */
	public TransientVertexBuffer stride(int value) {
		return stride(NativeObject.toUnsignedShort(value));
	}

	/**
	 * Vertex buffer handle.
	 * @return the field value
	 */
	public VertexBufferHandle handle() {
		return VertexBufferHandle.read(slice(MH_HANDLE, segment()));
	}

	/**
	 * Sets the native {@code handle} field and returns {@code this}.
	 * @param value the new field value
	 */
	public TransientVertexBuffer handle(VertexBufferHandle value) {
		value.write(slice(MH_HANDLE, segment()));
		return this;
	}

	/**
	 * Vertex layout handle.
	 * @return the field value
	 */
	public VertexLayoutHandle layoutHandle() {
		return VertexLayoutHandle.read(slice(MH_LAYOUTHANDLE, segment()));
	}

	/**
	 * Sets the native {@code layoutHandle} field and returns {@code this}.
	 * @param value the new field value
	 */
	public TransientVertexBuffer layoutHandle(VertexLayoutHandle value) {
		value.write(slice(MH_LAYOUTHANDLE, segment()));
		return this;
	}
}
