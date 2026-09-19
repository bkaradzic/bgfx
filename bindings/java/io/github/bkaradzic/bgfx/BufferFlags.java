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
 * Constants for Buffer flags.
 */
@NullMarked
public final class BufferFlags {
	private BufferFlags() {
	}

	/**
	 * Buffer flag value {@code None}.
	 */
	public static final short None = (short) 0x0000;

	/**
	 * Buffer will be read by shader.
	 */
	public static final short ComputeRead = (short) 0x0100;

	/**
	 * Buffer will be used for writing.
	 */
	public static final short ComputeWrite = (short) 0x0200;

	/**
	 * Buffer will be used for storing draw indirect commands.
	 */
	public static final short DrawIndirect = (short) 0x0400;

	/**
	 * Allow dynamic index/vertex buffer resize during update.
	 */
	public static final short AllowResize = (short) 0x0800;

	/**
	 * Index buffer contains 32-bit indices.
	 */
	public static final short Index32 = (short) 0x1000;

	/**
	 * Buffer flag value {@code ComputeReadWrite}.
	 */
	public static final short ComputeReadWrite = (short) 0x0300;
}
