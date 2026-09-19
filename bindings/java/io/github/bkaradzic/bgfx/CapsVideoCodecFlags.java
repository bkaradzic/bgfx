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
 * Constants for CapsVideoCodec flags.
 */
@NullMarked
public final class CapsVideoCodecFlags {
	private CapsVideoCodecFlags() {
	}
	/**
	 * Video codec is not supported.
	 */
	public static final int None = 0x00000000;

	/**
	 * 8-bit sample depth is supported.
	 */
	public static final int Bit8 = 0x00000001;

	/**
	 * 10-bit sample depth is supported.
	 */
	public static final int Bit10 = 0x00000002;

	/**
	 * 12-bit sample depth is supported.
	 */
	public static final int Bit12 = 0x00000004;

	/**
	 * 4:2:0 chroma subsampling is supported.
	 */
	public static final int Chroma420 = 0x00000008;

	/**
	 * 4:2:2 chroma subsampling is supported.
	 */
	public static final int Chroma422 = 0x00000010;

	/**
	 * 4:4:4 chroma subsampling is supported.
	 */
	public static final int Chroma444 = 0x00000020;
}
