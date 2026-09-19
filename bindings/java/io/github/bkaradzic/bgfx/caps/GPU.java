// Copyright 2011-2026 Branimir Karadzic. All rights reserved.
// License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE


//
// AUTO GENERATED! DO NOT EDIT!
//

package io.github.bkaradzic.bgfx.caps;

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
 * GPU info.
 */
@NullMarked
public final class GPU extends NativeObject {
	/**
	 * Native C structure layout.
	 */
	public static final StructLayout LAYOUT = cStruct("bgfx_caps_gpu_t",
		ValueLayout.JAVA_SHORT.withName("vendorId"),
		ValueLayout.JAVA_SHORT.withName("deviceId"));
	private static final VarHandle VH_VENDORID = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("vendorId"));
	private static final VarHandle VH_DEVICEID = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("deviceId"));
	/**
	 * Wraps an existing native structure.
	 * @param segment native memory segment
	 */
	public GPU(MemorySegment segment) {
		super(segment, LAYOUT);
	}

	/**
	 * Allocates a native structure.
	 * @param allocator destination allocator
	 */
	public GPU(SegmentAllocator allocator) {
		super(allocator, LAYOUT);
	}

	/**
	 * Vendor PCI id. See {@code BGFX_PCI_ID_*}.
	 * @return the field value
	 */
	public @Unsigned short vendorId() {
		return (@Unsigned short) VH_VENDORID.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code vendorId} field and returns {@code this}.
	 * @param value the new field value
	 */
	public GPU vendorId(@Unsigned short value) {
		VH_VENDORID.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Sets the native {@code vendorId} field and returns {@code this}.
	 * @param value the new field value
	 */
	public GPU vendorId(int value) {
		return vendorId(NativeObject.toUnsignedShort(value));
	}

	/**
	 * Device id.
	 * @return the field value
	 */
	public @Unsigned short deviceId() {
		return (@Unsigned short) VH_DEVICEID.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code deviceId} field and returns {@code this}.
	 * @param value the new field value
	 */
	public GPU deviceId(@Unsigned short value) {
		VH_DEVICEID.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Sets the native {@code deviceId} field and returns {@code this}.
	 * @param value the new field value
	 */
	public GPU deviceId(int value) {
		return deviceId(NativeObject.toUnsignedShort(value));
	}
}
