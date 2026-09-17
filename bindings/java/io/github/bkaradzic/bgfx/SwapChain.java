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
import org.jspecify.annotations.Nullable;

import io.github.bkaradzic.bgfx.*;
import io.github.bkaradzic.bgfx.util.FFMUtil;
import io.github.bkaradzic.bgfx.util.NativeObject;
import io.github.bkaradzic.bgfx.util.Unsigned;
import static io.github.bkaradzic.bgfx.Bgfx.*;
import static io.github.bkaradzic.bgfx.util.FFMUtil.*;

/**
 * Swap chain description.
 */
@NullMarked
public final class SwapChain extends NativeObject {
	/**
	 * Native C structure layout.
	 */
	public static final StructLayout LAYOUT = cStruct("bgfx_swap_chain_t",
		ValueLayout.ADDRESS.withName("nwh"),
		ValueLayout.ADDRESS.withName("ndt"),
		ValueLayout.JAVA_INT.withName("width"),
		ValueLayout.JAVA_INT.withName("height"),
		ValueLayout.JAVA_INT.withName("flags"),
		ValueLayout.JAVA_INT.withName("formatColor"),
		ValueLayout.JAVA_INT.withName("formatDepthStencil"),
		TextureHandle.LAYOUT.withName("depth"),
		ValueLayout.JAVA_BYTE.withName("numBackBuffers"),
		ValueLayout.JAVA_BYTE.withName("maxFrameLatency"));
	private static final VarHandle VH_NWH = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("nwh"));
	private static final VarHandle VH_NDT = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("ndt"));
	private static final VarHandle VH_WIDTH = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("width"));
	private static final VarHandle VH_HEIGHT = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("height"));
	private static final VarHandle VH_FLAGS = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("flags"));
	private static final VarHandle VH_FORMATCOLOR = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("formatColor"));
	private static final VarHandle VH_FORMATDEPTHSTENCIL = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("formatDepthStencil"));
	private static final MethodHandle MH_DEPTH = LAYOUT.sliceHandle(
		MemoryLayout.PathElement.groupElement("depth"));
	private static final VarHandle VH_NUMBACKBUFFERS = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("numBackBuffers"));
	private static final VarHandle VH_MAXFRAMELATENCY = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("maxFrameLatency"));
	/**
	 * Wraps an existing native structure.
	 * @param segment native memory segment
	 */
	public SwapChain(MemorySegment segment) {
		super(segment, LAYOUT);
	}

	/**
	 * Allocates a native structure.
	 * @param allocator destination allocator
	 */
	public SwapChain(SegmentAllocator allocator) {
		super(allocator, LAYOUT);
	}

	/**
	 * Native window handle. If {@code NULL}, bgfx will create a headless
	 * context/device, provided the rendering API supports it.
	 * @return the field value
	 */
	public MemorySegment nwh() {
		return address((MemorySegment) VH_NWH.get(segment(), 0L));
	}

	/**
	 * Sets the native {@code nwh} field and returns {@code this}.
	 * @param value the new field value
	 */
	public SwapChain nwh(MemorySegment value) {
		VH_NWH.set(segment(), 0L, address(value));
		return this;
	}

	/**
	 * Native display type (*nix specific). A window that leaves this
	 * {@code NULL} uses the one the main window was initialized with.
	 * @return the field value
	 */
	public MemorySegment ndt() {
		return address((MemorySegment) VH_NDT.get(segment(), 0L));
	}

	/**
	 * Sets the native {@code ndt} field and returns {@code this}.
	 * @param value the new field value
	 */
	public SwapChain ndt(MemorySegment value) {
		VH_NDT.set(segment(), 0L, address(value));
		return this;
	}

	/**
	 * Swap chain width.
	 * @return the field value
	 */
	public @Unsigned int width() {
		return (@Unsigned int) VH_WIDTH.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code width} field and returns {@code this}.
	 * @param value the new field value
	 */
	public SwapChain width(@Unsigned int value) {
		VH_WIDTH.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Swap chain height.
	 * @return the field value
	 */
	public @Unsigned int height() {
		return (@Unsigned int) VH_HEIGHT.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code height} field and returns {@code this}.
	 * @param value the new field value
	 */
	public SwapChain height(@Unsigned int value) {
		VH_HEIGHT.set(segment(), 0L, value);
		return this;
	}

	/**
	 * See: {@code BGFX_SWAP_CHAIN_*}.
	 * @return the field value
	 */
	public @Unsigned int flags() {
		return (@Unsigned int) VH_FLAGS.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code flags} field and returns {@code this}.
	 * @param value the new field value
	 */
	public SwapChain flags(@Unsigned int value) {
		VH_FLAGS.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Color format.
	 * @return the field value
	 */
	public TextureFormat formatColor() {
		return TextureFormat.fromValue((int) VH_FORMATCOLOR.get(segment(), 0L));
	}

	/**
	 * Sets the native {@code formatColor} field and returns {@code this}.
	 * @param value the new field value
	 */
	public SwapChain formatColor(TextureFormat value) {
		VH_FORMATCOLOR.set(segment(), 0L, value.ordinal());
		return this;
	}

	/**
	 * Depth/stencil format, or {@code TextureFormat.COUNT} for no depth. Ignored
	 * when {@code depth} is valid.
	 * @return the field value
	 */
	public TextureFormat formatDepthStencil() {
		return TextureFormat.fromValue((int) VH_FORMATDEPTHSTENCIL.get(segment(), 0L));
	}

	/**
	 * Sets the native {@code formatDepthStencil} field and returns {@code this}.
	 * @param value the new field value
	 */
	public SwapChain formatDepthStencil(TextureFormat value) {
		VH_FORMATDEPTHSTENCIL.set(segment(), 0L, value.ordinal());
		return this;
	}

	/**
	 * Depth attachment. Must be created with {@code BGFX_TEXTURE_RT}, and match the
	 * swap chain width, height and sample count. When invalid, bgfx creates and
	 * owns a depth surface per {@code formatDepthStencil}. A texture supplied here is
	 * never destroyed by bgfx, and may be shared by several same-size swap chains.
	 * @return the field value
	 */
	public TextureHandle depth() {
		return TextureHandle.read(slice(MH_DEPTH, segment()));
	}

	/**
	 * Sets the native {@code depth} field and returns {@code this}.
	 * @param value the new field value
	 */
	public SwapChain depth(TextureHandle value) {
		value.write(slice(MH_DEPTH, segment()));
		return this;
	}

	/**
	 * Number of back buffers.
	 * @return the field value
	 */
	public @Unsigned byte numBackBuffers() {
		return (@Unsigned byte) VH_NUMBACKBUFFERS.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code numBackBuffers} field and returns {@code this}.
	 * @param value the new field value
	 */
	public SwapChain numBackBuffers(@Unsigned byte value) {
		VH_NUMBACKBUFFERS.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Sets the native {@code numBackBuffers} field and returns {@code this}.
	 * @param value the new field value
	 */
	public SwapChain numBackBuffers(int value) {
		return numBackBuffers(NativeObject.toUnsignedByte(value));
	}

	/**
	 * Maximum frame latency.
	 * @return the field value
	 */
	public @Unsigned byte maxFrameLatency() {
		return (@Unsigned byte) VH_MAXFRAMELATENCY.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code maxFrameLatency} field and returns {@code this}.
	 * @param value the new field value
	 */
	public SwapChain maxFrameLatency(@Unsigned byte value) {
		VH_MAXFRAMELATENCY.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Sets the native {@code maxFrameLatency} field and returns {@code this}.
	 * @param value the new field value
	 */
	public SwapChain maxFrameLatency(int value) {
		return maxFrameLatency(NativeObject.toUnsignedByte(value));
	}
}
