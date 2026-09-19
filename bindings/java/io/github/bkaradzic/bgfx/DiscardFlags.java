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
 * Rendering state discard. When state is preserved in submit, rendering states can be discarded
 * on a finer grain.
 */
@NullMarked
public final class DiscardFlags {
	private DiscardFlags() {
	}
	/**
	 * Preserve everything.
	 */
	public static final int None = 0x00000000;

	/**
	 * Discard texture sampler and buffer bindings.
	 */
	public static final int Bindings = 0x00000001;

	/**
	 * Discard index buffer.
	 */
	public static final int IndexBuffer = 0x00000002;

	/**
	 * Discard instance data.
	 */
	public static final int InstanceData = 0x00000004;

	/**
	 * Discard state and uniform bindings.
	 */
	public static final int State = 0x00000008;

	/**
	 * Discard transform.
	 */
	public static final int Transform = 0x00000010;

	/**
	 * Discard vertex streams.
	 */
	public static final int VertexStreams = 0x00000020;

	/**
	 * Discard all states.
	 */
	public static final int All = 0x000000ff;
}
