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
 * Constants for Caps flags.
 */
@NullMarked
public final class CapsFlags {
	private CapsFlags() {
	}
	/**
	 * Blend independent is supported.
	 */
	public static final long BlendIndependent = 0x0000000000000001L;

	/**
	 * Compute shaders are supported.
	 */
	public static final long Compute = 0x0000000000000002L;

	/**
	 * Conservative rasterization is supported.
	 */
	public static final long ConservativeRaster = 0x0000000000000004L;

	/**
	 * Draw indirect is supported.
	 */
	public static final long DrawIndirect = 0x0000000000000008L;

	/**
	 * Draw indirect with indirect count is supported.
	 */
	public static final long DrawIndirectCount = 0x0000000000000010L;

	/**
	 * Fragment ordering is available in fragment shader.
	 */
	public static final long FragmentOrdering = 0x0000000000000020L;

	/**
	 * Graphics debugger is present.
	 */
	public static final long GraphicsDebugger = 0x0000000000000040L;

	/**
	 * HDR10 rendering is supported.
	 */
	public static final long Hdr10 = 0x0000000000000080L;

	/**
	 * Image Read/Write is supported.
	 */
	public static final long ImageRw = 0x0000000000000100L;

	/**
	 * 32-bit indices are supported.
	 */
	public static final long Index32 = 0x0000000000000200L;

	/**
	 * PrimitiveID is available in fragment shader.
	 */
	public static final long PrimitiveId = 0x0000000000000400L;

	/**
	 * Renderer is on separate thread.
	 */
	public static final long RendererMultithreaded = 0x0000000000000800L;

	/**
	 * Multiple windows are supported.
	 */
	public static final long SwapChain = 0x0000000000001000L;

	/**
	 * Cubemap texture array is supported.
	 */
	public static final long TextureCubeArray = 0x0000000000002000L;

	/**
	 * CPU direct access to GPU texture memory.
	 */
	public static final long TextureDirectAccess = 0x0000000000004000L;

	/**
	 * External texture is supported.
	 */
	public static final long TextureExternal = 0x0000000000008000L;

	/**
	 * External shared texture is supported.
	 */
	public static final long TextureExternalShared = 0x0000000000010000L;

	/**
	 * Transparent back buffer supported.
	 */
	public static final long TransparentBackbuffer = 0x0000000000020000L;

	/**
	 * Variable Rate Shading
	 */
	public static final long VariableRateShading = 0x0000000000040000L;

	/**
	 * Vertex attribute 10_10_10_2 is supported.
	 */
	public static final long VertexAttribUint10 = 0x0000000000080000L;

	/**
	 * Hardware video decode is supported.
	 */
	public static final long VideoDecode = 0x0000000000100000L;

	/**
	 * Viewport layer is available in vertex shader.
	 */
	public static final long ViewportLayerArray = 0x0000000000200000L;
}
