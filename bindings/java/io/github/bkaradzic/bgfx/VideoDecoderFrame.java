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
 * Video decoder per-frame submission. Serialized into the Memory passed
 * to {@code updateTexture2D} for a video decode destination texture. The
 * renderer parses the slice / tile-group header out of the bitstream and
 * translates it to the backend-specific decoder arguments.
 * <p>
 * A single call may submit a batch of access units: {@code bitstream} is the
 * back-to-back concatenation of {@code numAus} access units, and {@code aus[ii]}
 * holds the size and PTS of each. AUs are enqueued in array order
 * (which is the codec's decode order). Set {@code numAus == 0} (and
 * {@code bitstream == NULL}) for a presentation-only tick that only advances
 * the playback clock.
 * <p>
 * The {@code bitstream} and {@code aus} pointers must remain valid until bgfx has
 * consumed the submission ({@code copy} only deep-copies the
 * {@code VideoDecoderFrame} struct itself, not the buffers it references).
 */
@NullMarked
public final class VideoDecoderFrame extends NativeObject {
	/**
	 * Native C structure layout.
	 */
	public static final StructLayout LAYOUT = cStruct("bgfx_video_decoder_frame_t",
		ValueLayout.JAVA_INT.withName("magic"),
		ValueLayout.ADDRESS.withName("bitstream"),
		ValueLayout.ADDRESS.withName("aus"),
		ValueLayout.JAVA_INT.withName("numAus"),
		ValueLayout.JAVA_LONG.withName("presentationTimeUs"),
		ValueLayout.JAVA_BYTE.withName("flags"));
	private static final VarHandle VH_MAGIC = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("magic"));
	private static final VarHandle VH_BITSTREAM = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("bitstream"));
	private static final VarHandle VH_AUS = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("aus"));
	private static final VarHandle VH_NUMAUS = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("numAus"));
	private static final VarHandle VH_PRESENTATIONTIMEUS = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("presentationTimeUs"));
	private static final VarHandle VH_FLAGS = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("flags"));
	/**
	 * Wraps an existing native structure.
	 * @param segment native memory segment
	 */
	public VideoDecoderFrame(MemorySegment segment) {
		super(segment, LAYOUT);
	}

	/**
	 * Allocates a native structure.
	 * @param allocator destination allocator
	 */
	public VideoDecoderFrame(SegmentAllocator allocator) {
		super(allocator, LAYOUT);
	}

	/**
	 * Structure magic. Must be {@code BX_MAKEFOURCC('V', 'D', 'F', 0x0)}.
	 * @return the field value
	 */
	public @Unsigned int magic() {
		return (@Unsigned int) VH_MAGIC.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code magic} field and returns {@code this}.
	 * @param value the new field value
	 */
	public VideoDecoderFrame magic(@Unsigned int value) {
		VH_MAGIC.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Concatenated access-unit bitstream (decode order). NULL for presentation-only ticks.
	 * @return the field value
	 */
	public MemorySegment bitstream() {
		return address((MemorySegment) VH_BITSTREAM.get(segment(), 0L));
	}

	/**
	 * Sets the native {@code bitstream} field and returns {@code this}.
	 * @param value the new field value
	 */
	public VideoDecoderFrame bitstream(MemorySegment value) {
		VH_BITSTREAM.set(segment(), 0L, address(value));
		return this;
	}

	/**
	 * Sets the native {@code bitstream} field and returns {@code this}.
	 * @param value the new field value
	 */
	public VideoDecoderFrame bitstream(int value) {
		return bitstream(NativeObject.toUnsignedByte(value));
	}

	/**
	 * Per-AU size and PTS array. NULL when {@code numAus == 0}.
	 * @return the field value
	 */
	public VideoDecoderAu aus() {
		return new VideoDecoderAu((MemorySegment) VH_AUS.get(segment(), 0L));
	}

	/**
	 * Sets the native {@code aus} field and returns {@code this}.
	 * @param value the new field value
	 */
	public VideoDecoderFrame aus(VideoDecoderAu value) {
		VH_AUS.set(segment(), 0L, address(value));
		return this;
	}

	/**
	 * Number of access units in this batch. 0 for presentation-only ticks.
	 * @return the field value
	 */
	public @Unsigned int numAus() {
		return (@Unsigned int) VH_NUMAUS.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code numAus} field and returns {@code this}.
	 * @param value the new field value
	 */
	public VideoDecoderFrame numAus(@Unsigned int value) {
		VH_NUMAUS.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Current playback wall-clock time. Driver dispatches the picture whose {@code ptsUs}
	 * best matches. Must be monotonically non-decreasing between non-{@code SET} calls.
	 * @return the field value
	 */
	public long presentationTimeUs() {
		return (long) VH_PRESENTATIONTIMEUS.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code presentationTimeUs} field and returns {@code this}.
	 * @param value the new field value
	 */
	public VideoDecoderFrame presentationTimeUs(long value) {
		VH_PRESENTATIONTIMEUS.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Per-frame submission flags. See: {@code BGFX_VIDEO_DECODE_FRAME_*}.
	 * @return the field value
	 */
	public @Unsigned byte flags() {
		return (@Unsigned byte) VH_FLAGS.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code flags} field and returns {@code this}.
	 * @param value the new field value
	 */
	public VideoDecoderFrame flags(@Unsigned byte value) {
		VH_FLAGS.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Sets the native {@code flags} field and returns {@code this}.
	 * @param value the new field value
	 */
	public VideoDecoderFrame flags(int value) {
		return flags(NativeObject.toUnsignedByte(value));
	}
}
