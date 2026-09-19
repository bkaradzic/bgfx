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
 * Renderer capabilities.
 */
@NullMarked
public final class Caps extends NativeObject {
	/**
	 * Native C structure layout.
	 */
	public static final StructLayout LAYOUT = cStruct("bgfx_caps_t",
		ValueLayout.JAVA_INT.withName("rendererType"),
		ValueLayout.JAVA_LONG.withName("supported"),
		ValueLayout.JAVA_SHORT.withName("vendorId"),
		ValueLayout.JAVA_SHORT.withName("deviceId"),
		ValueLayout.JAVA_BOOLEAN.withName("homogeneousDepth"),
		ValueLayout.JAVA_BOOLEAN.withName("originBottomLeft"),
		ValueLayout.JAVA_BYTE.withName("numGPUs"),
		MemoryLayout.sequenceLayout(4, io.github.bkaradzic.bgfx.caps.GPU.LAYOUT).withName("gpu"),
		io.github.bkaradzic.bgfx.caps.Limits.LAYOUT.withName("limits"),
		MemoryLayout.sequenceLayout(105, ValueLayout.JAVA_INT).withName("formats"),
		MemoryLayout.sequenceLayout(3, ValueLayout.JAVA_INT).withName("codecs"));
	private static final VarHandle VH_RENDERERTYPE = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("rendererType"));
	private static final VarHandle VH_SUPPORTED = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("supported"));
	private static final VarHandle VH_VENDORID = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("vendorId"));
	private static final VarHandle VH_DEVICEID = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("deviceId"));
	private static final VarHandle VH_HOMOGENEOUSDEPTH = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("homogeneousDepth"));
	private static final VarHandle VH_ORIGINBOTTOMLEFT = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("originBottomLeft"));
	private static final VarHandle VH_NUMGPUS = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("numGPUs"));
	private static final MethodHandle MH_GPU = LAYOUT.sliceHandle(
		MemoryLayout.PathElement.groupElement("gpu"));
	private static final MethodHandle MH_LIMITS = LAYOUT.sliceHandle(
		MemoryLayout.PathElement.groupElement("limits"));
	private static final MethodHandle MH_FORMATS = LAYOUT.sliceHandle(
		MemoryLayout.PathElement.groupElement("formats"));
	private static final MethodHandle MH_CODECS = LAYOUT.sliceHandle(
		MemoryLayout.PathElement.groupElement("codecs"));
	/**
	 * Wraps an existing native structure.
	 * @param segment native memory segment
	 */
	public Caps(MemorySegment segment) {
		super(segment, LAYOUT);
	}

	/**
	 * Allocates a native structure.
	 * @param allocator destination allocator
	 */
	public Caps(SegmentAllocator allocator) {
		super(allocator, LAYOUT);
	}

	/**
	 * Renderer backend type. See: {@code RendererType}
	 * @return the field value
	 */
	public RendererType rendererType() {
		return RendererType.fromValue((int) VH_RENDERERTYPE.get(segment(), 0L));
	}

	/**
	 * Sets the native {@code rendererType} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Caps rendererType(RendererType value) {
		VH_RENDERERTYPE.set(segment(), 0L, value.ordinal());
		return this;
	}

	/**
	 * Supported functionality.
	 * <strong>Attention:</strong> See {@code BGFX_CAPS_*} flags at https://bkaradzic.github.io/bgfx/bgfx.html#available-caps
	 * @return the field value
	 */
	public @Unsigned long supported() {
		return (@Unsigned long) VH_SUPPORTED.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code supported} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Caps supported(@Unsigned long value) {
		VH_SUPPORTED.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Selected GPU vendor PCI id.
	 * @return the field value
	 */
	public @Unsigned short vendorId() {
		return (@Unsigned short) VH_VENDORID.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code vendorId} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Caps vendorId(@Unsigned short value) {
		VH_VENDORID.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Sets the native {@code vendorId} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Caps vendorId(int value) {
		return vendorId(NativeObject.toUnsignedShort(value));
	}

	/**
	 * Selected GPU device id.
	 * @return the field value
	 */
	public @Unsigned short deviceId() {
		return (@Unsigned short) VH_DEVICEID.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code deviceId} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Caps deviceId(@Unsigned short value) {
		VH_DEVICEID.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Sets the native {@code deviceId} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Caps deviceId(int value) {
		return deviceId(NativeObject.toUnsignedShort(value));
	}

	/**
	 * True when NDC depth is in [-1, 1] range, otherwise its [0, 1].
	 * @return the field value
	 */
	public boolean homogeneousDepth() {
		return (boolean) VH_HOMOGENEOUSDEPTH.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code homogeneousDepth} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Caps homogeneousDepth(boolean value) {
		VH_HOMOGENEOUSDEPTH.set(segment(), 0L, value);
		return this;
	}

	/**
	 * True when NDC origin is at bottom left.
	 * @return the field value
	 */
	public boolean originBottomLeft() {
		return (boolean) VH_ORIGINBOTTOMLEFT.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code originBottomLeft} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Caps originBottomLeft(boolean value) {
		VH_ORIGINBOTTOMLEFT.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Number of enumerated GPUs.
	 * @return the field value
	 */
	public @Unsigned byte numGPUs() {
		return (@Unsigned byte) VH_NUMGPUS.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code numGPUs} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Caps numGPUs(@Unsigned byte value) {
		VH_NUMGPUS.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Sets the native {@code numGPUs} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Caps numGPUs(int value) {
		return numGPUs(NativeObject.toUnsignedByte(value));
	}

	/**
	 * Enumerated GPUs.
	 * @return a segment view of the inline array
	 */
	public MemorySegment gpu() {
		return slice(MH_GPU, segment());
	}

	/**
	 * Renderer runtime limits.
	 * @return the field value
	 */
	public io.github.bkaradzic.bgfx.caps.Limits limits() {
		return new io.github.bkaradzic.bgfx.caps.Limits(slice(MH_LIMITS, segment()));
	}

	/**
	 * Sets the native {@code limits} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Caps limits(io.github.bkaradzic.bgfx.caps.Limits value) {
		slice(MH_LIMITS, segment()).copyFrom(value.segment());
		return this;
	}

	/**
	 * Supported texture format capabilities flags:
	 *   - {@code BGFX_CAPS_FORMAT_TEXTURE_NONE} - Texture format is not supported.
	 *   - {@code BGFX_CAPS_FORMAT_TEXTURE_2D} - Texture format is supported.
	 *   - {@code BGFX_CAPS_FORMAT_TEXTURE_2D_SRGB} - Texture as sRGB format is supported.
	 *   - {@code BGFX_CAPS_FORMAT_TEXTURE_2D_EMULATED} - Texture format is emulated.
	 *   - {@code BGFX_CAPS_FORMAT_TEXTURE_3D} - Texture format is supported.
	 *   - {@code BGFX_CAPS_FORMAT_TEXTURE_3D_SRGB} - Texture as sRGB format is supported.
	 *   - {@code BGFX_CAPS_FORMAT_TEXTURE_3D_EMULATED} - Texture format is emulated.
	 *   - {@code BGFX_CAPS_FORMAT_TEXTURE_CUBE} - Texture format is supported.
	 *   - {@code BGFX_CAPS_FORMAT_TEXTURE_CUBE_SRGB} - Texture as sRGB format is supported.
	 *   - {@code BGFX_CAPS_FORMAT_TEXTURE_CUBE_EMULATED} - Texture format is emulated.
	 *   - {@code BGFX_CAPS_FORMAT_TEXTURE_VERTEX} - Texture format can be used from vertex shader.
	 *   - {@code BGFX_CAPS_FORMAT_TEXTURE_IMAGE_READ} - Texture format can be used as image
	 *     and read from.
	 *   - {@code BGFX_CAPS_FORMAT_TEXTURE_IMAGE_WRITE} - Texture format can be used as image
	 *     and written to.
	 *   - {@code BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER} - Texture format can be used as frame
	 *     buffer.
	 *   - {@code BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA} - Texture format can be used as MSAA
	 *     frame buffer.
	 *   - {@code BGFX_CAPS_FORMAT_TEXTURE_MSAA} - Texture can be sampled as MSAA.
	 *   - {@code BGFX_CAPS_FORMAT_TEXTURE_MIP_AUTOGEN} - Texture format supports auto-generated
	 *     mips.
	 *   - {@code BGFX_CAPS_FORMAT_TEXTURE_BACKBUFFER} - Texture format can be used as back buffer format.
	 *   - {@code BGFX_CAPS_FORMAT_TEXTURE_VIDEO_DECODE_DST} - Texture format can be used as video
	 *     decode destination.
	 * @return a segment view of the inline array
	 */
	public MemorySegment formats() {
		return slice(MH_FORMATS, segment());
	}

	/**
	 * Supported video codec capabilities flags. A non-zero entry means the codec is
	 * supported for hardware decode; bits describe sample depths and chroma
	 * subsamplings:
	 *   - {@code BGFX_CAPS_VIDEO_CODEC_NONE} - Video codec is not supported.
	 *   - {@code BGFX_CAPS_VIDEO_CODEC_BIT_8} - 8-bit sample depth is supported.
	 *   - {@code BGFX_CAPS_VIDEO_CODEC_BIT_10} - 10-bit sample depth is supported.
	 *   - {@code BGFX_CAPS_VIDEO_CODEC_BIT_12} - 12-bit sample depth is supported.
	 *   - {@code BGFX_CAPS_VIDEO_CODEC_CHROMA_420} - 4:2:0 chroma subsampling is supported.
	 *   - {@code BGFX_CAPS_VIDEO_CODEC_CHROMA_422} - 4:2:2 chroma subsampling is supported.
	 *   - {@code BGFX_CAPS_VIDEO_CODEC_CHROMA_444} - 4:4:4 chroma subsampling is supported.
	 * @return a segment view of the inline array
	 */
	public MemorySegment codecs() {
		return slice(MH_CODECS, segment());
	}
}
