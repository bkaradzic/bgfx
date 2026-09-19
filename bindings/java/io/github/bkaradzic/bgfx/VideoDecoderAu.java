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
 * One access unit entry inside a {@code VideoDecoderFrame} batch. The bitstream
 * for the AU lives at offset {@code Σ aus[0..ii].size} inside the frame's
 * {@code bitstream} buffer (access units are stored back-to-back in decode /
 * submission order).
 */
@NullMarked
public final class VideoDecoderAu extends NativeObject {
	/**
	 * Native C structure layout.
	 */
	public static final StructLayout LAYOUT = cStruct("bgfx_video_decoder_au_t",
		ValueLayout.JAVA_INT.withName("size"),
		ValueLayout.JAVA_LONG.withName("ptsUs"));
	private static final VarHandle VH_SIZE = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("size"));
	private static final VarHandle VH_PTSUS = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("ptsUs"));
	/**
	 * Wraps an existing native structure.
	 * @param segment native memory segment
	 */
	public VideoDecoderAu(MemorySegment segment) {
		super(segment, LAYOUT);
	}

	/**
	 * Allocates a native structure.
	 * @param allocator destination allocator
	 */
	public VideoDecoderAu(SegmentAllocator allocator) {
		super(allocator, LAYOUT);
	}

	/**
	 * Access unit size in bytes.
	 * @return the field value
	 */
	public @Unsigned int size() {
		return (@Unsigned int) VH_SIZE.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code size} field and returns {@code this}.
	 * @param value the new field value
	 */
	public VideoDecoderAu size(@Unsigned int value) {
		VH_SIZE.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Presentation timestamp in microseconds for this access unit (container-provided).
	 * @return the field value
	 */
	public long ptsUs() {
		return (long) VH_PTSUS.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code ptsUs} field and returns {@code this}.
	 * @param value the new field value
	 */
	public VideoDecoderAu ptsUs(long value) {
		VH_PTSUS.set(segment(), 0L, value);
		return this;
	}
}
