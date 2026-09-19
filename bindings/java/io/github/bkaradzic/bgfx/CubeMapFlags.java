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
 * Constants for CubeMap flags.
 */
@NullMarked
public final class CubeMapFlags {
	private CubeMapFlags() {
	}
	/**
	 * Cubemap +x.
	 */
	public static final int PositiveX = 0x00000000;

	/**
	 * Cubemap -x.
	 */
	public static final int NegativeX = 0x00000001;

	/**
	 * Cubemap +y.
	 */
	public static final int PositiveY = 0x00000002;

	/**
	 * Cubemap -y.
	 */
	public static final int NegativeY = 0x00000003;

	/**
	 * Cubemap +z.
	 */
	public static final int PositiveZ = 0x00000004;

	/**
	 * Cubemap -z.
	 */
	public static final int NegativeZ = 0x00000005;
}
