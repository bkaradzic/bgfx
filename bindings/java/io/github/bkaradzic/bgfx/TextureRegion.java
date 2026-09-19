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
 * Region of a texture, used as the source or destination of a blit, or as
 * the region handed to {@code read}.
 * <p>
 * Every field defaults to zero, and zero always means "the natural whole".
 * {@code { .handle = tex }} therefore addresses all of mip 0.
 */
@NullMarked
public final class TextureRegion extends NativeObject {
	/**
	 * Native C structure layout.
	 */
	public static final StructLayout LAYOUT = cStruct("bgfx_texture_region_t",
		TextureHandle.LAYOUT.withName("handle"),
		ValueLayout.JAVA_BYTE.withName("mip"),
		ValueLayout.JAVA_SHORT.withName("x"),
		ValueLayout.JAVA_SHORT.withName("y"),
		ValueLayout.JAVA_SHORT.withName("z"),
		ValueLayout.JAVA_SHORT.withName("width"),
		ValueLayout.JAVA_SHORT.withName("height"),
		ValueLayout.JAVA_SHORT.withName("depth"));
	private static final MethodHandle MH_HANDLE = LAYOUT.sliceHandle(
		MemoryLayout.PathElement.groupElement("handle"));
	private static final VarHandle VH_MIP = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("mip"));
	private static final VarHandle VH_X = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("x"));
	private static final VarHandle VH_Y = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("y"));
	private static final VarHandle VH_Z = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("z"));
	private static final VarHandle VH_WIDTH = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("width"));
	private static final VarHandle VH_HEIGHT = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("height"));
	private static final VarHandle VH_DEPTH = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("depth"));
	/**
	 * Wraps an existing native structure.
	 * @param segment native memory segment
	 */
	public TextureRegion(MemorySegment segment) {
		super(segment, LAYOUT);
	}

	/**
	 * Allocates a native structure.
	 * @param allocator destination allocator
	 */
	public TextureRegion(SegmentAllocator allocator) {
		super(allocator, LAYOUT);
	}

	/**
	 * Texture handle.
	 * @return the field value
	 */
	public TextureHandle handle() {
		return TextureHandle.read(slice(MH_HANDLE, segment()));
	}

	/**
	 * Sets the native {@code handle} field and returns {@code this}.
	 * @param value the new field value
	 */
	public TextureRegion handle(TextureHandle value) {
		value.write(slice(MH_HANDLE, segment()));
		return this;
	}

	/**
	 * Mip level.
	 * @return the field value
	 */
	public @Unsigned byte mip() {
		return (@Unsigned byte) VH_MIP.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code mip} field and returns {@code this}.
	 * @param value the new field value
	 */
	public TextureRegion mip(@Unsigned byte value) {
		VH_MIP.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Sets the native {@code mip} field and returns {@code this}.
	 * @param value the new field value
	 */
	public TextureRegion mip(int value) {
		return mip(NativeObject.toUnsignedByte(value));
	}

	/**
	 * X position of the region.
	 * @return the field value
	 */
	public @Unsigned short x() {
		return (@Unsigned short) VH_X.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code x} field and returns {@code this}.
	 * @param value the new field value
	 */
	public TextureRegion x(@Unsigned short value) {
		VH_X.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Sets the native {@code x} field and returns {@code this}.
	 * @param value the new field value
	 */
	public TextureRegion x(int value) {
		return x(NativeObject.toUnsignedShort(value));
	}

	/**
	 * Y position of the region.
	 * @return the field value
	 */
	public @Unsigned short y() {
		return (@Unsigned short) VH_Y.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code y} field and returns {@code this}.
	 * @param value the new field value
	 */
	public TextureRegion y(@Unsigned short value) {
		VH_Y.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Sets the native {@code y} field and returns {@code this}.
	 * @param value the new field value
	 */
	public TextureRegion y(int value) {
		return y(NativeObject.toUnsignedShort(value));
	}

	/**
	 * If texture is 2D this should be 0. If the texture is a cube map
	 * this is the cube face, for a 2D array it is the layer, and for a
	 * 3D texture it is the Z position.
	 * @return the field value
	 */
	public @Unsigned short z() {
		return (@Unsigned short) VH_Z.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code z} field and returns {@code this}.
	 * @param value the new field value
	 */
	public TextureRegion z(@Unsigned short value) {
		VH_Z.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Sets the native {@code z} field and returns {@code this}.
	 * @param value the new field value
	 */
	public TextureRegion z(int value) {
		return z(NativeObject.toUnsignedShort(value));
	}

	/**
	 * Width of the region. 0 uses the rest of the mip from {@code x}.
	 * @return the field value
	 */
	public @Unsigned short width() {
		return (@Unsigned short) VH_WIDTH.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code width} field and returns {@code this}.
	 * @param value the new field value
	 */
	public TextureRegion width(@Unsigned short value) {
		VH_WIDTH.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Sets the native {@code width} field and returns {@code this}.
	 * @param value the new field value
	 */
	public TextureRegion width(int value) {
		return width(NativeObject.toUnsignedShort(value));
	}

	/**
	 * Height of the region. 0 uses the rest of the mip from {@code y}.
	 * @return the field value
	 */
	public @Unsigned short height() {
		return (@Unsigned short) VH_HEIGHT.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code height} field and returns {@code this}.
	 * @param value the new field value
	 */
	public TextureRegion height(@Unsigned short value) {
		VH_HEIGHT.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Sets the native {@code height} field and returns {@code this}.
	 * @param value the new field value
	 */
	public TextureRegion height(int value) {
		return height(NativeObject.toUnsignedShort(value));
	}

	/**
	 * Depth of the region for a 3D texture, or the number of layers or
	 * cube faces otherwise. 0 uses the rest from {@code z}.
	 * @return the field value
	 */
	public @Unsigned short depth() {
		return (@Unsigned short) VH_DEPTH.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code depth} field and returns {@code this}.
	 * @param value the new field value
	 */
	public TextureRegion depth(@Unsigned short value) {
		VH_DEPTH.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Sets the native {@code depth} field and returns {@code this}.
	 * @param value the new field value
	 */
	public TextureRegion depth(int value) {
		return depth(NativeObject.toUnsignedShort(value));
	}

	/**
	 * Fill in the region of a plain 2D texture. {@code mip}, {@code z} and {@code depth} are left
	 * at zero, which addresses mip 0 of the only slice a 2D texture has.
	 * @param _handle Texture handle.
	 * @param _x X position of the region.
	 * @param _y Y position of the region.
	 * @param _width Width of the region. 0 uses the rest of the mip from {@code _x}.
	 * @param _height Height of the region. 0 uses the rest of the mip from {@code _y}.
	 */
	public final void init(TextureHandle _handle, @Unsigned short _x, @Unsigned short _y, @Unsigned short _width, @Unsigned short _height) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_TEXTURE_REGION_INIT.invokeExact(segment(), _handle.allocate(arena), _x, _y, _width, _height);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}
}
