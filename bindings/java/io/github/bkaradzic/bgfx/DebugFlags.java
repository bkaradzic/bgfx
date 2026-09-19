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
 * Constants for Debug flags.
 */
@NullMarked
public final class DebugFlags {
	private DebugFlags() {
	}
	/**
	 * No debug.
	 */
	public static final int None = 0x00000000;

	/**
	 * Enable wireframe for all primitives.
	 */
	public static final int Wireframe = 0x00000001;

	/**
	 * Enable infinitely fast hardware test. No draw calls will be submitted to driver.
	 * It's useful when profiling to quickly assess bottleneck between CPU and GPU.
	 */
	public static final int Ifh = 0x00000002;

	/**
	 * Enable statistics display.
	 */
	public static final int Stats = 0x00000004;

	/**
	 * Enable debug text display.
	 */
	public static final int Text = 0x00000008;

	/**
	 * Enable profiler. This causes per-view statistics to be collected, available through {@code Stats.ViewStats}. This is unrelated to the profiler functions in {@code CallbackI}.
	 */
	public static final int Profiler = 0x00000010;
}
