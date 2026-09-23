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
 * Constants for Attachment flags.
 */
@NullMarked
public final class AttachmentFlags {
	private AttachmentFlags() {
	}
	/**
	 * No attachment flags.
	 */
	public static final int None = 0x00000000;

	/**
	 * Auto-generate mip maps on resolve.
	 */
	public static final int AutoGenMips = 0x00000001;

	/**
	 * Bind the depth aspect read-only (read-only depth-stencil view) so the
	 * attachment can be sampled as a texture in the same pass.
	 */
	public static final int ReadOnlyDepth = 0x00000002;

	/**
	 * Bind the stencil aspect read-only.
	 */
	public static final int ReadOnlyStencil = 0x00000004;

	/**
	 * Render with sRGB conversion; absence of this flag renders without
	 * it. Only affects textures created {@code BGFX_TEXTURE_SRGB_MUTABLE},
	 * which must state the encoding explicitly on every attachment;
	 * ignored for any other texture.
	 */
	public static final int Srgb = 0x00000008;
}
