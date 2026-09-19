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
 * Internal data.
 */
@NullMarked
public final class InternalData extends NativeObject {
	/**
	 * Native C structure layout.
	 */
	public static final StructLayout LAYOUT = cStruct("bgfx_internal_data_t",
		ValueLayout.ADDRESS.withName("caps"),
		ValueLayout.ADDRESS.withName("context"));
	private static final VarHandle VH_CAPS = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("caps"));
	private static final VarHandle VH_CONTEXT = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("context"));
	/**
	 * Wraps an existing native structure.
	 * @param segment native memory segment
	 */
	public InternalData(MemorySegment segment) {
		super(segment, LAYOUT);
	}

	/**
	 * Allocates a native structure.
	 * @param allocator destination allocator
	 */
	public InternalData(SegmentAllocator allocator) {
		super(allocator, LAYOUT);
	}

	/**
	 * Renderer capabilities.
	 * @return the field value
	 */
	public Caps caps() {
		return new Caps((MemorySegment) VH_CAPS.get(segment(), 0L));
	}

	/**
	 * Sets the native {@code caps} field and returns {@code this}.
	 * @param value the new field value
	 */
	public InternalData caps(Caps value) {
		VH_CAPS.set(segment(), 0L, address(value));
		return this;
	}

	/**
	 * GL context, or D3D device.
	 * @return the field value
	 */
	public MemorySegment context() {
		return address((MemorySegment) VH_CONTEXT.get(segment(), 0L));
	}

	/**
	 * Sets the native {@code context} field and returns {@code this}.
	 * @param value the new field value
	 */
	public InternalData context(MemorySegment value) {
		VH_CONTEXT.set(segment(), 0L, address(value));
		return this;
	}
}
