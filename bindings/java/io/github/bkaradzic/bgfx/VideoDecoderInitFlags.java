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
 * Video decoder lifetime flags (per {@code VideoDecoderInit.flags}).
 */
@NullMarked
public final class VideoDecoderInitFlags {
	private VideoDecoderInitFlags() {
	}
	/**
	 * No flags.
	 */
	public static final int None = 0x00000000;

	/**
	 * Cache submitted access units in driver-managed memory keyed by {@code ptsUs} so the
	 * presentation clock can revisit / loop without re-streaming. The cache is
	 * unbounded: the app picks the total cache size implicitly by choosing how
	 * many access units to submit. Without this flag access units are decoded once
	 * and dropped (streaming default).
	 */
	public static final int Retain = 0x00000001;
}
