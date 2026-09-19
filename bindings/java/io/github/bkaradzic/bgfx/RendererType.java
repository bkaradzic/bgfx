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
 * Renderer backend type enum.
 */
@NullMarked
public enum RendererType {
	/**
	 * No rendering.
	 */
	NOOP,
	/**
	 * AGC
	 */
	AGC,
	/**
	 * Direct3D 11.0
	 */
	DIRECT3D11,
	/**
	 * Direct3D 12.0
	 */
	DIRECT3D12,
	/**
	 * GNM
	 */
	GNM,
	/**
	 * Metal
	 */
	METAL,
	/**
	 * NVN
	 */
	NVN,
	/**
	 * OpenGL ES 3.0+
	 */
	OPENGLES,
	/**
	 * OpenGL 4.3+
	 */
	OPENGL,
	/**
	 * Vulkan
	 */
	VULKAN,
	/**
	 * WebGPU
	 */
	WEBGPU,

	/**
	 * Number of native enum values.
	 */
	COUNT;

	/**
	 * Native C enum layout.
	 */
	public static final ValueLayout.OfInt LAYOUT = ValueLayout.JAVA_INT;
	private static final RendererType[] VALUES = values();

	/**
	 * Returns the enum constant for a native C enum value.
	 * @param value the native enum value
	 * @return the matching enum constant
	 */
	public static RendererType fromValue(int value) {
		if (value >= 0 && value < VALUES.length) {
			return VALUES[value];
		}
		throw new IllegalArgumentException("Unknown RendererType value: " + value);
	}
}
