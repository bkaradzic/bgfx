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
 * Video decoder initialization. Serialized into the Memory passed to
 * {@code createTexture2D}. When the memory blob begins with {@code magic}, bgfx
 * infers the texture is a video decode destination (the caller need not set
 * any extra texture flag). Everything else the renderer needs about the
 * stream (chroma format, bit depth, profile, level, coded dimensions, DPB
 * layout, color metadata) is parsed out of the codec parameter sets at
 * create time.
 */
@NullMarked
public final class VideoDecoderInit extends NativeObject {
	/**
	 * Native C structure layout.
	 */
	public static final StructLayout LAYOUT = cStruct("bgfx_video_decoder_init_t",
		ValueLayout.JAVA_INT.withName("magic"),
		ValueLayout.JAVA_INT.withName("codec"),
		ValueLayout.ADDRESS.withName("parameterSets"),
		ValueLayout.JAVA_INT.withName("parameterSetsSize"),
		ValueLayout.JAVA_INT.withName("cachedAuBytes"),
		ValueLayout.JAVA_BYTE.withName("flags"));
	private static final VarHandle VH_MAGIC = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("magic"));
	private static final VarHandle VH_CODEC = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("codec"));
	private static final VarHandle VH_PARAMETERSETS = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("parameterSets"));
	private static final VarHandle VH_PARAMETERSETSSIZE = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("parameterSetsSize"));
	private static final VarHandle VH_CACHEDAUBYTES = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("cachedAuBytes"));
	private static final VarHandle VH_FLAGS = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("flags"));
	/**
	 * Wraps an existing native structure.
	 * @param segment native memory segment
	 */
	public VideoDecoderInit(MemorySegment segment) {
		super(segment, LAYOUT);
	}

	/**
	 * Allocates a native structure.
	 * @param allocator destination allocator
	 */
	public VideoDecoderInit(SegmentAllocator allocator) {
		super(allocator, LAYOUT);
	}

	/**
	 * Structure magic. Must be {@code BX_MAKEFOURCC('V', 'D', 'I', 0x0)}.
	 * @return the field value
	 */
	public @Unsigned int magic() {
		return (@Unsigned int) VH_MAGIC.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code magic} field and returns {@code this}.
	 * @param value the new field value
	 */
	public VideoDecoderInit magic(@Unsigned int value) {
		VH_MAGIC.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Video codec. See: {@code VideoCodec}.
	 * @return the field value
	 */
	public VideoCodec codec() {
		return VideoCodec.fromValue((int) VH_CODEC.get(segment(), 0L));
	}

	/**
	 * Sets the native {@code codec} field and returns {@code this}.
	 * @param value the new field value
	 */
	public VideoDecoderInit codec(VideoCodec value) {
		VH_CODEC.set(segment(), 0L, value.ordinal());
		return this;
	}

	/**
	 * Codec parameter sets (Annex B for H.264/H.265, OBUs for AV1).
	 * @return the field value
	 */
	public MemorySegment parameterSets() {
		return address((MemorySegment) VH_PARAMETERSETS.get(segment(), 0L));
	}

	/**
	 * Sets the native {@code parameterSets} field and returns {@code this}.
	 * @param value the new field value
	 */
	public VideoDecoderInit parameterSets(MemorySegment value) {
		VH_PARAMETERSETS.set(segment(), 0L, address(value));
		return this;
	}

	/**
	 * Sets the native {@code parameterSets} field and returns {@code this}.
	 * @param value the new field value
	 */
	public VideoDecoderInit parameterSets(int value) {
		return parameterSets(NativeObject.toUnsignedByte(value));
	}

	/**
	 * Parameter sets size in bytes.
	 * @return the field value
	 */
	public @Unsigned int parameterSetsSize() {
		return (@Unsigned int) VH_PARAMETERSETSSIZE.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code parameterSetsSize} field and returns {@code this}.
	 * @param value the new field value
	 */
	public VideoDecoderInit parameterSetsSize(@Unsigned int value) {
		VH_PARAMETERSETSSIZE.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Soft cap (in bytes) on the streaming access-unit FIFO (when
	 * {@code BGFX_VIDEO_DECODER_INIT_RETAIN} is NOT set). 0 selects the
	 * default. Ignored in RETAIN mode (the retain cache is unbounded).
	 * @return the field value
	 */
	public @Unsigned int cachedAuBytes() {
		return (@Unsigned int) VH_CACHEDAUBYTES.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code cachedAuBytes} field and returns {@code this}.
	 * @param value the new field value
	 */
	public VideoDecoderInit cachedAuBytes(@Unsigned int value) {
		VH_CACHEDAUBYTES.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Decoder lifetime flags. See: {@code BGFX_VIDEO_DECODER_INIT_*}.
	 * @return the field value
	 */
	public @Unsigned byte flags() {
		return (@Unsigned byte) VH_FLAGS.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code flags} field and returns {@code this}.
	 * @param value the new field value
	 */
	public VideoDecoderInit flags(@Unsigned byte value) {
		VH_FLAGS.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Sets the native {@code flags} field and returns {@code this}.
	 * @param value the new field value
	 */
	public VideoDecoderInit flags(int value) {
		return flags(NativeObject.toUnsignedByte(value));
	}
}
