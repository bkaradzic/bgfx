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
 * Texture info.
 */
@NullMarked
public final class TextureInfo extends NativeObject {
	/**
	 * Native C structure layout.
	 */
	public static final StructLayout LAYOUT = cStruct("bgfx_texture_info_t",
		ValueLayout.JAVA_INT.withName("format"),
		ValueLayout.JAVA_INT.withName("storageSize"),
		ValueLayout.JAVA_SHORT.withName("width"),
		ValueLayout.JAVA_SHORT.withName("height"),
		ValueLayout.JAVA_SHORT.withName("depth"),
		ValueLayout.JAVA_SHORT.withName("numLayers"),
		ValueLayout.JAVA_BYTE.withName("numMips"),
		ValueLayout.JAVA_BYTE.withName("bitsPerPixel"),
		ValueLayout.JAVA_BOOLEAN.withName("cubeMap"));
	private static final VarHandle VH_FORMAT = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("format"));
	private static final VarHandle VH_STORAGESIZE = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("storageSize"));
	private static final VarHandle VH_WIDTH = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("width"));
	private static final VarHandle VH_HEIGHT = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("height"));
	private static final VarHandle VH_DEPTH = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("depth"));
	private static final VarHandle VH_NUMLAYERS = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("numLayers"));
	private static final VarHandle VH_NUMMIPS = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("numMips"));
	private static final VarHandle VH_BITSPERPIXEL = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("bitsPerPixel"));
	private static final VarHandle VH_CUBEMAP = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("cubeMap"));
	/**
	 * Wraps an existing native structure.
	 * @param segment native memory segment
	 */
	public TextureInfo(MemorySegment segment) {
		super(segment, LAYOUT);
	}

	/**
	 * Allocates a native structure.
	 * @param allocator destination allocator
	 */
	public TextureInfo(SegmentAllocator allocator) {
		super(allocator, LAYOUT);
	}

	/**
	 * Texture format.
	 * @return the field value
	 */
	public TextureFormat format() {
		return TextureFormat.fromValue((int) VH_FORMAT.get(segment(), 0L));
	}

	/**
	 * Sets the native {@code format} field and returns {@code this}.
	 * @param value the new field value
	 */
	public TextureInfo format(TextureFormat value) {
		VH_FORMAT.set(segment(), 0L, value.ordinal());
		return this;
	}

	/**
	 * Total amount of bytes required to store texture.
	 * @return the field value
	 */
	public @Unsigned int storageSize() {
		return (@Unsigned int) VH_STORAGESIZE.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code storageSize} field and returns {@code this}.
	 * @param value the new field value
	 */
	public TextureInfo storageSize(@Unsigned int value) {
		VH_STORAGESIZE.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Texture width.
	 * @return the field value
	 */
	public @Unsigned short width() {
		return (@Unsigned short) VH_WIDTH.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code width} field and returns {@code this}.
	 * @param value the new field value
	 */
	public TextureInfo width(@Unsigned short value) {
		VH_WIDTH.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Sets the native {@code width} field and returns {@code this}.
	 * @param value the new field value
	 */
	public TextureInfo width(int value) {
		return width(NativeObject.toUnsignedShort(value));
	}

	/**
	 * Texture height.
	 * @return the field value
	 */
	public @Unsigned short height() {
		return (@Unsigned short) VH_HEIGHT.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code height} field and returns {@code this}.
	 * @param value the new field value
	 */
	public TextureInfo height(@Unsigned short value) {
		VH_HEIGHT.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Sets the native {@code height} field and returns {@code this}.
	 * @param value the new field value
	 */
	public TextureInfo height(int value) {
		return height(NativeObject.toUnsignedShort(value));
	}

	/**
	 * Texture depth.
	 * @return the field value
	 */
	public @Unsigned short depth() {
		return (@Unsigned short) VH_DEPTH.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code depth} field and returns {@code this}.
	 * @param value the new field value
	 */
	public TextureInfo depth(@Unsigned short value) {
		VH_DEPTH.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Sets the native {@code depth} field and returns {@code this}.
	 * @param value the new field value
	 */
	public TextureInfo depth(int value) {
		return depth(NativeObject.toUnsignedShort(value));
	}

	/**
	 * Number of layers in texture array.
	 * @return the field value
	 */
	public @Unsigned short numLayers() {
		return (@Unsigned short) VH_NUMLAYERS.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code numLayers} field and returns {@code this}.
	 * @param value the new field value
	 */
	public TextureInfo numLayers(@Unsigned short value) {
		VH_NUMLAYERS.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Sets the native {@code numLayers} field and returns {@code this}.
	 * @param value the new field value
	 */
	public TextureInfo numLayers(int value) {
		return numLayers(NativeObject.toUnsignedShort(value));
	}

	/**
	 * Number of MIP maps.
	 * @return the field value
	 */
	public @Unsigned byte numMips() {
		return (@Unsigned byte) VH_NUMMIPS.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code numMips} field and returns {@code this}.
	 * @param value the new field value
	 */
	public TextureInfo numMips(@Unsigned byte value) {
		VH_NUMMIPS.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Sets the native {@code numMips} field and returns {@code this}.
	 * @param value the new field value
	 */
	public TextureInfo numMips(int value) {
		return numMips(NativeObject.toUnsignedByte(value));
	}

	/**
	 * Format bits per pixel.
	 * @return the field value
	 */
	public @Unsigned byte bitsPerPixel() {
		return (@Unsigned byte) VH_BITSPERPIXEL.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code bitsPerPixel} field and returns {@code this}.
	 * @param value the new field value
	 */
	public TextureInfo bitsPerPixel(@Unsigned byte value) {
		VH_BITSPERPIXEL.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Sets the native {@code bitsPerPixel} field and returns {@code this}.
	 * @param value the new field value
	 */
	public TextureInfo bitsPerPixel(int value) {
		return bitsPerPixel(NativeObject.toUnsignedByte(value));
	}

	/**
	 * Texture is cubemap.
	 * @return the field value
	 */
	public boolean cubeMap() {
		return (boolean) VH_CUBEMAP.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code cubeMap} field and returns {@code this}.
	 * @param value the new field value
	 */
	public TextureInfo cubeMap(boolean value) {
		VH_CUBEMAP.set(segment(), 0L, value);
		return this;
	}
}
