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
 * Memory release callback.
 */
@NullMarked
@FunctionalInterface
@SuppressWarnings("restricted")
public interface ReleaseFn {
	/**
	 * Native callback function descriptor.
	 */
	FunctionDescriptor DESCRIPTOR = FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.ADDRESS);
	/**
	 * Bound callback target used to create upcall stubs.
	 */
	MethodHandle TARGET = upcallTarget(
		ReleaseFn.class, "invoke", MethodType.methodType(
			void.class, MemorySegment.class, MemorySegment.class));

	/**
	 * Invoked by native bgfx code. Implementations must not throw.
	 * @param _ptr Pointer to allocated data.
	 * @param _userData User defined data if needed.
	 */
	void invoke(MemorySegment _ptr, MemorySegment _userData);

	/**
	 * Creates an upcall stub for this callback.
	 * The arena must remain alive until bgfx can no longer invoke the callback.
	 * @param arena a caller-owned, long-lived arena
	 * @return the native function pointer
	 */
	default MemorySegment upcall(Arena arena) {
		Objects.requireNonNull(arena, "arena");
		return LINKER.upcallStub(TARGET.bindTo(this), DESCRIPTOR, arena);
	}
}
