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
 * Region of a buffer, used as the source or destination of a blit, or as the
 * region handed to {@code read}.
 * <p>
 * {@code rowPitch} and {@code slicePitch} describe how texture data is laid out in the
 * buffer, and are ignored when the other end of the blit is also a buffer.
 * Both are in bytes, and 0 selects the tightly packed layout: a row pitch of
 * the region width in blocks multiplied by the block size, and a slice pitch
 * of that row pitch multiplied by the region height in blocks.
 * <p>
 * A pitch the backend cannot copy natively is repacked by bgfx, which costs
 * an extra pass over the data. {@code Caps.Limits.blitRowPitchAlign} and
 * {@code blitOffsetAlign} report what the backend copies directly, and
 * {@code BufferRegion.init} fills in a layout that matches them.
 */
@NullMarked
public final class BufferRegion extends NativeObject {
	/**
	 * Native C structure layout.
	 */
	public static final StructLayout LAYOUT = cStruct("bgfx_buffer_region_t",
		BufferHandle.LAYOUT.withName("handle"),
		ValueLayout.JAVA_INT.withName("offset"),
		ValueLayout.JAVA_INT.withName("size"),
		ValueLayout.JAVA_INT.withName("rowPitch"),
		ValueLayout.JAVA_INT.withName("slicePitch"));
	private static final MethodHandle MH_HANDLE = LAYOUT.sliceHandle(
		MemoryLayout.PathElement.groupElement("handle"));
	private static final VarHandle VH_OFFSET = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("offset"));
	private static final VarHandle VH_SIZE = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("size"));
	private static final VarHandle VH_ROWPITCH = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("rowPitch"));
	private static final VarHandle VH_SLICEPITCH = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("slicePitch"));
	/**
	 * Wraps an existing native structure.
	 * @param segment native memory segment
	 */
	public BufferRegion(MemorySegment segment) {
		super(segment, LAYOUT);
	}

	/**
	 * Allocates a native structure.
	 * @param allocator destination allocator
	 */
	public BufferRegion(SegmentAllocator allocator) {
		super(allocator, LAYOUT);
	}

	/**
	 * Buffer handle.
	 * @return the field value
	 */
	public BufferHandle handle() {
		return BufferHandle.read(slice(MH_HANDLE, segment()));
	}

	/**
	 * Sets the native {@code handle} field and returns {@code this}.
	 * @param value the new field value
	 */
	public BufferRegion handle(BufferHandle value) {
		value.writeTagged(slice(MH_HANDLE, segment()));
		return this;
	}

	/**
	 * Byte offset into the buffer.
	 * @return the field value
	 */
	public @Unsigned int offset() {
		return (@Unsigned int) VH_OFFSET.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code offset} field and returns {@code this}.
	 * @param value the new field value
	 */
	public BufferRegion offset(@Unsigned int value) {
		VH_OFFSET.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Number of bytes. Only used when both ends of a blit are
	 * buffers, or by {@code read}. 0 uses the rest of the buffer.
	 * @return the field value
	 */
	public @Unsigned int size() {
		return (@Unsigned int) VH_SIZE.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code size} field and returns {@code this}.
	 * @param value the new field value
	 */
	public BufferRegion size(@Unsigned int value) {
		VH_SIZE.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Distance in bytes between the start of two consecutive rows
	 * of blocks. 0 is tightly packed.
	 * @return the field value
	 */
	public @Unsigned int rowPitch() {
		return (@Unsigned int) VH_ROWPITCH.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code rowPitch} field and returns {@code this}.
	 * @param value the new field value
	 */
	public BufferRegion rowPitch(@Unsigned int value) {
		VH_ROWPITCH.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Distance in bytes between the start of two consecutive
	 * slices, layers or cube faces. 0 is tightly packed.
	 * @return the field value
	 */
	public @Unsigned int slicePitch() {
		return (@Unsigned int) VH_SLICEPITCH.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code slicePitch} field and returns {@code this}.
	 * @param value the new field value
	 */
	public BufferRegion slicePitch(@Unsigned int value) {
		VH_SLICEPITCH.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Fill {@code rowPitch}, {@code slicePitch} and {@code size} with the layout the backend copies
	 * fastest for {@code _texture}, and round {@code offset} up to {@code Caps.Limits.blitOffsetAlign}.
	 * {@code handle} is left untouched, so {@code size} can be used to create the buffer the
	 * region will point at.
	 * @param _texture Texture region the buffer is copied to or from.
	 */
	public final void initTexture(TextureRegion _texture) {
		try {
			MH_BUFFER_REGION_INIT_TEXTURE.invokeExact(segment(), address(_texture));
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Fill in the region a blit between two buffers copies. {@code rowPitch} and
	 * {@code slicePitch} are left at zero, since neither end of such a blit is a
	 * texture.
	 * @param _handle Buffer handle.
	 * @param _offset Byte offset into the buffer.
	 * @param _size Number of bytes. 0 uses the rest of the buffer.
	 */
	public final void initBuffer(BufferHandle _handle, @Unsigned int _offset, @Unsigned int _size) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_BUFFER_REGION_INIT_BUFFER.invokeExact(segment(), _handle.allocateTagged(arena), _offset, _size);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}
}
