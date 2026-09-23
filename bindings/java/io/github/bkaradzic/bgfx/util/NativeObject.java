// Copyright 2011-2026 Branimir Karadzic. All rights reserved.
// License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE

package io.github.bkaradzic.bgfx.util;

import java.lang.foreign.MemoryLayout;
import java.lang.foreign.MemorySegment;
import java.lang.foreign.SegmentAllocator;
import java.util.Objects;

import org.jspecify.annotations.NullMarked;
import org.jspecify.annotations.NonNull;

/** Base class for native-backed bgfx structures and opaque objects. */
@NullMarked
public abstract class NativeObject {
	private final MemorySegment segment;

	/**
	 * Wraps an opaque native address or an already-sized segment.
	 * @param segment native memory segment
	 */
	protected NativeObject(MemorySegment segment) {
		this.segment = Objects.requireNonNull(segment, "segment");
	}

	/**
	 * Wraps a native segment using the supplied structure layout.
	 * @param segment native memory segment
	 * @param layout native structure layout
	 */
	protected NativeObject(MemorySegment segment, MemoryLayout layout) {
		this(FFMUtil.view(segment, layout));
	}

	/**
	 * Allocates a native structure using the supplied allocator.
	 * @param allocator destination allocator
	 * @param layout native structure layout
	 */
	protected NativeObject(SegmentAllocator allocator, MemoryLayout layout) {
		this(Objects.requireNonNull(allocator, "allocator").allocate(layout), layout);
	}

	/**
	 * Returns the wrapped native memory segment.
	 * @return the wrapped native memory segment
	 */
	public final MemorySegment segment() {
		return segment;
	}

	/**
	 * Reports whether this object wraps the null address.
	 * @return whether this object wraps the null address
	 */
	public final boolean isNull() {
		return segment.address() == 0;
	}

	@Override
	public final boolean equals(Object other) {
		return this == other
			|| other != null
			&& getClass() == other.getClass()
			&& segment.equals(((NativeObject) other).segment);
	}

	@Override
	public final int hashCode() {
		return segment().hashCode();
	}

	@Override
	public String toString() {
		return segment().toString();
	}

	//
	// Helper methods
	//

	protected static @Unsigned short toUnsignedShort(int value) {
		if ((value & ~0xffff) != 0) {
			throw new IllegalArgumentException("value out of range: " + value);
		}
		return (short) value;
	}

	public static @Unsigned byte toUnsignedByte(int value) {
		if ((value & ~0xff) != 0) {
			throw new IllegalArgumentException("value out of range: " + value);
		}
		return (byte) value;
	}
}
