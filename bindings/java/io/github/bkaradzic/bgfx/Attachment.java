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
 * Frame buffer texture attachment info.
 */
@NullMarked
public final class Attachment extends NativeObject {
	/**
	 * Native C structure layout.
	 */
	public static final StructLayout LAYOUT = cStruct("bgfx_attachment_t",
		ValueLayout.JAVA_INT.withName("access"),
		TextureHandle.LAYOUT.withName("handle"),
		ValueLayout.JAVA_SHORT.withName("mip"),
		ValueLayout.JAVA_SHORT.withName("layer"),
		ValueLayout.JAVA_SHORT.withName("numLayers"),
		ValueLayout.JAVA_BYTE.withName("resolve"));
	private static final VarHandle VH_ACCESS = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("access"));
	private static final MethodHandle MH_HANDLE = LAYOUT.sliceHandle(
		MemoryLayout.PathElement.groupElement("handle"));
	private static final VarHandle VH_MIP = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("mip"));
	private static final VarHandle VH_LAYER = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("layer"));
	private static final VarHandle VH_NUMLAYERS = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("numLayers"));
	private static final VarHandle VH_RESOLVE = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("resolve"));
	/**
	 * Wraps an existing native structure.
	 * @param segment native memory segment
	 */
	public Attachment(MemorySegment segment) {
		super(segment, LAYOUT);
	}

	/**
	 * Allocates a native structure.
	 * @param allocator destination allocator
	 */
	public Attachment(SegmentAllocator allocator) {
		super(allocator, LAYOUT);
	}

	/**
	 * Attachment access. See {@code Access}.
	 * @return the field value
	 */
	public Access access() {
		return Access.fromValue((int) VH_ACCESS.get(segment(), 0L));
	}

	/**
	 * Sets the native {@code access} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Attachment access(Access value) {
		VH_ACCESS.set(segment(), 0L, value.ordinal());
		return this;
	}

	/**
	 * Render target texture handle.
	 * @return the field value
	 */
	public TextureHandle handle() {
		return TextureHandle.read(slice(MH_HANDLE, segment()));
	}

	/**
	 * Sets the native {@code handle} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Attachment handle(TextureHandle value) {
		value.write(slice(MH_HANDLE, segment()));
		return this;
	}

	/**
	 * Mip level.
	 * @return the field value
	 */
	public @Unsigned short mip() {
		return (@Unsigned short) VH_MIP.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code mip} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Attachment mip(@Unsigned short value) {
		VH_MIP.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Sets the native {@code mip} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Attachment mip(int value) {
		return mip(NativeObject.toUnsignedShort(value));
	}

	/**
	 * Cubemap side or depth layer/slice to use.
	 * @return the field value
	 */
	public @Unsigned short layer() {
		return (@Unsigned short) VH_LAYER.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code layer} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Attachment layer(@Unsigned short value) {
		VH_LAYER.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Sets the native {@code layer} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Attachment layer(int value) {
		return layer(NativeObject.toUnsignedShort(value));
	}

	/**
	 * Number of texture layer/slice(s) in array to use.
	 * @return the field value
	 */
	public @Unsigned short numLayers() {
		return (@Unsigned short) VH_NUMLAYERS.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code numLayers} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Attachment numLayers(@Unsigned short value) {
		VH_NUMLAYERS.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Sets the native {@code numLayers} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Attachment numLayers(int value) {
		return numLayers(NativeObject.toUnsignedShort(value));
	}

	/**
	 * Resolve flags. See: {@code BGFX_RESOLVE_*}
	 * @return the field value
	 */
	public @Unsigned byte resolve() {
		return (@Unsigned byte) VH_RESOLVE.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code resolve} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Attachment resolve(@Unsigned byte value) {
		VH_RESOLVE.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Sets the native {@code resolve} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Attachment resolve(int value) {
		return resolve(NativeObject.toUnsignedByte(value));
	}

	/**
	 * Init attachment.
	 * @param _handle Render target texture handle.
	 * @param _access Access. See {@code Access}.
	 * @param _layer Cubemap side or depth layer/slice to use.
	 * @param _numLayers Number of texture layer/slice(s) in array to use.
	 * @param _mip Mip level.
	 * @param _resolve Resolve flags. See: {@code BGFX_RESOLVE_*}
	 */
	public final void init(TextureHandle _handle, Access _access, @Unsigned short _layer, @Unsigned short _numLayers, @Unsigned short _mip, @Unsigned byte _resolve) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_ATTACHMENT_INIT.invokeExact(segment(), _handle.allocate(arena), _access.ordinal(), _layer, _numLayers, _mip, _resolve);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}
}
