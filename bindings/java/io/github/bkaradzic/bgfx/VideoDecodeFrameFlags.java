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
 * Video decoder per-frame submission flags (per {@code VideoDecoderFrame.flags}).
 */
@NullMarked
public final class VideoDecodeFrameFlags {
	private VideoDecodeFrameFlags() {
	}
	/**
	 * No flags.
	 */
	public static final int None = 0x00000000;

	/**
	 * First batch after a position change. The first access unit must be a clean IDR.
	 * Driver flushes its DPB, queued access units, and reorder pool before decoding;
	 * subsequent {@code presentationTimeUs} values may land anywhere (monotonicity is only
	 * required between non-{@code Set} ticks).
	 */
	public static final int Set = 0x00000001;

	/**
	 * Skip the picker dispatch for this call. Useful while bulk-loading access units
	 * so the displayed picture isn't churned mid-load.
	 */
	public static final int NoBlit = 0x00000002;

	/**
	 * Marks the last access unit of the clip; permits eager pre-decode in idle time
	 * and lets the picker emit the final frame without lookahead stalling.
	 */
	public static final int Final = 0x00000004;

	/**
	 * When {@code presentationTimeUs} runs past the highest cached {@code ptsUs}, the picker
	 * wraps modulo the cached pts range. Without this flag the picker freezes on
	 * the last displayable picture.
	 */
	public static final int Loop = 0x00000008;
}
