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
 * Vertex layout.
 */
@NullMarked
public final class VertexLayout extends NativeObject {
	/**
	 * Native C structure layout.
	 */
	public static final StructLayout LAYOUT = cStruct("bgfx_vertex_layout_t",
		ValueLayout.JAVA_INT.withName("hash"),
		ValueLayout.JAVA_SHORT.withName("stride"),
		MemoryLayout.sequenceLayout(26, ValueLayout.JAVA_SHORT).withName("offset"),
		MemoryLayout.sequenceLayout(26, ValueLayout.JAVA_SHORT).withName("attributes"));
	private static final VarHandle VH_HASH = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("hash"));
	private static final VarHandle VH_STRIDE = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("stride"));
	private static final MethodHandle MH_OFFSET = LAYOUT.sliceHandle(
		MemoryLayout.PathElement.groupElement("offset"));
	private static final MethodHandle MH_ATTRIBUTES = LAYOUT.sliceHandle(
		MemoryLayout.PathElement.groupElement("attributes"));
	/**
	 * Wraps an existing native structure.
	 * @param segment native memory segment
	 */
	public VertexLayout(MemorySegment segment) {
		super(segment, LAYOUT);
	}

	/**
	 * Allocates a native structure.
	 * @param allocator destination allocator
	 */
	public VertexLayout(SegmentAllocator allocator) {
		super(allocator, LAYOUT);
	}

	/**
	 * Hash.
	 * @return the field value
	 */
	public @Unsigned int hash() {
		return (@Unsigned int) VH_HASH.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code hash} field and returns {@code this}.
	 * @param value the new field value
	 */
	public VertexLayout hash(@Unsigned int value) {
		VH_HASH.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Stride.
	 * @return the field value
	 */
	public @Unsigned short stride() {
		return (@Unsigned short) VH_STRIDE.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code stride} field and returns {@code this}.
	 * @param value the new field value
	 */
	public VertexLayout stride(@Unsigned short value) {
		VH_STRIDE.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Sets the native {@code stride} field and returns {@code this}.
	 * @param value the new field value
	 */
	public VertexLayout stride(int value) {
		return stride(NativeObject.toUnsignedShort(value));
	}

	/**
	 * Attribute offsets.
	 * @return a segment view of the inline array
	 */
	public MemorySegment offset() {
		return slice(MH_OFFSET, segment());
	}

	/**
	 * Used attributes.
	 * @return a segment view of the inline array
	 */
	public MemorySegment attributes() {
		return slice(MH_ATTRIBUTES, segment());
	}

	/**
	 * Start VertexLayout.
	 * @param _rendererType Renderer backend type. See: {@code RendererType}
	 * @return Returns itself.
	 */
	public final VertexLayout begin(RendererType _rendererType) {
		try {
			return new VertexLayout((MemorySegment) MH_VERTEX_LAYOUT_BEGIN.invokeExact(segment(), _rendererType.ordinal()));
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Add attribute to VertexLayout.
	 * <p>
	 * <strong>Remarks:</strong> Must be called between begin/end.
	 * @param _attrib Attribute semantics. See: {@code Attrib}
	 * @param _num Number of elements 1, 2, 3 or 4.
	 * @param _type Element type.
	 * @param _normalized When using fixed point AttribType (f.e. Uint8) value will be normalized for vertex shader usage. When normalized is set to true, AttribType.UINT8 value in range 0-255 will be in range 0.0-1.0 in vertex shader.
	 * @param _asInt Packaging rule for vertexPack, vertexUnpack, and vertexConvert for AttribType.UINT8 and AttribType.INT16. Unpacking code must be implemented inside vertex shader.
	 * @return Returns itself.
	 */
	public final VertexLayout add(Attrib _attrib, @Unsigned byte _num, AttribType _type, boolean _normalized, boolean _asInt) {
		try {
			return new VertexLayout((MemorySegment) MH_VERTEX_LAYOUT_ADD.invokeExact(segment(), _attrib.ordinal(), _num, _type.ordinal(), _normalized, _asInt));
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Decode attribute.
	 * @param _attrib Attribute semantics. See: {@code Attrib}
	 * @param _num Number of elements.
	 * @param _type Element type.
	 * @param _normalized Attribute is normalized.
	 * @param _asInt Attribute is packed as int.
	 */
	public final void decode(Attrib _attrib, MemorySegment _num, MemorySegment _type, MemorySegment _normalized, MemorySegment _asInt) {
		try {
			MH_VERTEX_LAYOUT_DECODE.invokeExact(segment(), _attrib.ordinal(), address(_num), address(_type), address(_normalized), address(_asInt));
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Returns {@code true} if VertexLayout contains attribute.
	 * @param _attrib Attribute semantics. See: {@code Attrib}
	 * @return True if VertexLayout contains attribute.
	 */
	public final boolean has(Attrib _attrib) {
		try {
			return (boolean) MH_VERTEX_LAYOUT_HAS.invokeExact(segment(), _attrib.ordinal());
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Skip {@code _num} bytes in vertex stream.
	 * @param _num Number of bytes to skip.
	 * @return Returns itself.
	 */
	public final VertexLayout skip(@Unsigned byte _num) {
		try {
			return new VertexLayout((MemorySegment) MH_VERTEX_LAYOUT_SKIP.invokeExact(segment(), _num));
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * End VertexLayout.
	 */
	public final void end() {
		try {
			MH_VERTEX_LAYOUT_END.invokeExact(segment());
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Returns relative attribute offset from the vertex.
	 * @param _attrib Attribute semantics. See: {@code Attrib}
	 * @return Relative attribute offset from the vertex.
	 */
	public final @Unsigned short getOffset(Attrib _attrib) {
		try {
			return (@Unsigned short) MH_VERTEX_LAYOUT_GET_OFFSET.invokeExact(segment(), _attrib.ordinal());
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Returns vertex stride.
	 * @return Vertex stride.
	 */
	public final @Unsigned short getStride() {
		try {
			return (@Unsigned short) MH_VERTEX_LAYOUT_GET_STRIDE.invokeExact(segment());
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Returns size of vertex buffer for number of vertices.
	 * @param _num Number of vertices.
	 * @return Size of vertex buffer for number of vertices.
	 */
	public final @Unsigned int getSize(@Unsigned int _num) {
		try {
			return (@Unsigned int) MH_VERTEX_LAYOUT_GET_SIZE.invokeExact(segment(), _num);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}
}
