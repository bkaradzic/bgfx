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
 * Constants for PciId flags.
 */
@NullMarked
public final class PciIdFlags {
	private PciIdFlags() {
	}
	/**
	 * Autoselect adapter.
	 */
	public static final short None = (short) 0x0000;

	/**
	 * Software rasterizer.
	 */
	public static final short SoftwareRasterizer = (short) 0x0001;

	/**
	 * AMD adapter.
	 */
	public static final short Amd = (short) 0x1002;

	/**
	 * Apple adapter.
	 */
	public static final short Apple = (short) 0x106b;

	/**
	 * Intel adapter.
	 */
	public static final short Intel = (short) 0x8086;

	/**
	 * NVIDIA adapter.
	 */
	public static final short Nvidia = (short) 0x10de;

	/**
	 * Microsoft adapter.
	 */
	public static final short Microsoft = (short) 0x1414;

	/**
	 * ARM adapter.
	 */
	public static final short Arm = (short) 0x13b5;
}
