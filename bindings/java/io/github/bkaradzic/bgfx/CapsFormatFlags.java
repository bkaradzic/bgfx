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
 * Constants for CapsFormat flags.
 */
@NullMarked
public final class CapsFormatFlags {
	private CapsFormatFlags() {
	}
	/**
	 * Texture format is not supported.
	 */
	public static final int TextureNone = 0x00000000;

	/**
	 * Texture format is supported.
	 */
	public static final int Texture2D = 0x00000001;

	/**
	 * Texture as sRGB format is supported.
	 */
	public static final int Texture2DSrgb = 0x00000002;

	/**
	 * Texture format is emulated.
	 */
	public static final int Texture2DEmulated = 0x00000004;

	/**
	 * Texture format is supported.
	 */
	public static final int Texture3D = 0x00000008;

	/**
	 * Texture as sRGB format is supported.
	 */
	public static final int Texture3DSrgb = 0x00000010;

	/**
	 * Texture format is emulated.
	 */
	public static final int Texture3DEmulated = 0x00000020;

	/**
	 * Texture format is supported.
	 */
	public static final int TextureCube = 0x00000040;

	/**
	 * Texture as sRGB format is supported.
	 */
	public static final int TextureCubeSrgb = 0x00000080;

	/**
	 * Texture format is emulated.
	 */
	public static final int TextureCubeEmulated = 0x00000100;

	/**
	 * Texture format can be used from vertex shader.
	 */
	public static final int TextureVertex = 0x00000200;

	/**
	 * Texture format can be used as image and read from.
	 */
	public static final int TextureImageRead = 0x00000400;

	/**
	 * Texture format can be used as image and written to.
	 */
	public static final int TextureImageWrite = 0x00000800;

	/**
	 * Texture format can be used as frame buffer.
	 */
	public static final int TextureFramebuffer = 0x00001000;

	/**
	 * Texture format can be used as MSAA frame buffer.
	 */
	public static final int TextureFramebufferMsaa = 0x00002000;

	/**
	 * Texture can be sampled as MSAA.
	 */
	public static final int TextureMsaa = 0x00004000;

	/**
	 * Texture format supports auto-generated mips.
	 */
	public static final int TextureMipAutogen = 0x00008000;

	/**
	 * Texture format can be used as back buffer format.
	 */
	public static final int TextureBackbuffer = 0x00010000;

	/**
	 * Texture format can be used as video decode destination.
	 */
	public static final int TextureVideoDecodeDst = 0x00020000;
}
