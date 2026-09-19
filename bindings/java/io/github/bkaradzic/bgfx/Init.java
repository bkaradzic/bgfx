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
 * Initialization parameters used by {@code init}.
 */
@NullMarked
public final class Init extends NativeObject {
	/**
	 * Native C structure layout.
	 */
	public static final StructLayout LAYOUT = cStruct("bgfx_init_t",
		ValueLayout.JAVA_INT.withName("type"),
		ValueLayout.JAVA_SHORT.withName("vendorId"),
		ValueLayout.JAVA_SHORT.withName("deviceId"),
		ValueLayout.JAVA_LONG.withName("capabilities"),
		ValueLayout.JAVA_BOOLEAN.withName("debug"),
		ValueLayout.JAVA_BOOLEAN.withName("profile"),
		ValueLayout.JAVA_BOOLEAN.withName("fallback"),
		ValueLayout.JAVA_BOOLEAN.withName("videoDecode"),
		PlatformData.LAYOUT.withName("platformData"),
		SwapChain.LAYOUT.withName("swapChain"),
		ValueLayout.JAVA_INT.withName("reset"),
		io.github.bkaradzic.bgfx.init.Limits.LAYOUT.withName("limits"),
		ValueLayout.ADDRESS.withName("callback"),
		ValueLayout.ADDRESS.withName("allocator"));
	private static final VarHandle VH_TYPE = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("type"));
	private static final VarHandle VH_VENDORID = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("vendorId"));
	private static final VarHandle VH_DEVICEID = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("deviceId"));
	private static final VarHandle VH_CAPABILITIES = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("capabilities"));
	private static final VarHandle VH_DEBUG = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("debug"));
	private static final VarHandle VH_PROFILE = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("profile"));
	private static final VarHandle VH_FALLBACK = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("fallback"));
	private static final VarHandle VH_VIDEODECODE = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("videoDecode"));
	private static final MethodHandle MH_PLATFORMDATA = LAYOUT.sliceHandle(
		MemoryLayout.PathElement.groupElement("platformData"));
	private static final MethodHandle MH_SWAPCHAIN = LAYOUT.sliceHandle(
		MemoryLayout.PathElement.groupElement("swapChain"));
	private static final VarHandle VH_RESET = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("reset"));
	private static final MethodHandle MH_LIMITS = LAYOUT.sliceHandle(
		MemoryLayout.PathElement.groupElement("limits"));
	private static final VarHandle VH_CALLBACK = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("callback"));
	private static final VarHandle VH_ALLOCATOR = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("allocator"));
	/**
	 * Wraps an existing native structure.
	 * @param segment native memory segment
	 */
	public Init(MemorySegment segment) {
		super(segment, LAYOUT);
	}

	/**
	 * Allocates a native structure.
	 * @param allocator destination allocator
	 */
	public Init(SegmentAllocator allocator) {
		super(allocator, LAYOUT);
	}

	/**
	 * Select rendering backend. When set to RendererType.COUNT
	 * a default rendering backend will be selected appropriate to the platform.
	 * See: {@code RendererType}
	 * @return the field value
	 */
	public RendererType type() {
		return RendererType.fromValue((int) VH_TYPE.get(segment(), 0L));
	}

	/**
	 * Sets the native {@code type} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Init type(RendererType value) {
		VH_TYPE.set(segment(), 0L, value.ordinal());
		return this;
	}

	/**
	 * Vendor PCI ID. If set to {@code BGFX_PCI_ID_NONE}, discrete and integrated
	 * GPUs will be prioritised.
	 *   - {@code BGFX_PCI_ID_NONE} - Autoselect adapter.
	 *   - {@code BGFX_PCI_ID_SOFTWARE_RASTERIZER} - Software rasterizer.
	 *   - {@code BGFX_PCI_ID_AMD} - AMD adapter.
	 *   - {@code BGFX_PCI_ID_APPLE} - Apple adapter.
	 *   - {@code BGFX_PCI_ID_INTEL} - Intel adapter.
	 *   - {@code BGFX_PCI_ID_NVIDIA} - NVIDIA adapter.
	 *   - {@code BGFX_PCI_ID_MICROSOFT} - Microsoft adapter.
	 * @return the field value
	 */
	public @Unsigned short vendorId() {
		return (@Unsigned short) VH_VENDORID.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code vendorId} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Init vendorId(@Unsigned short value) {
		VH_VENDORID.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Sets the native {@code vendorId} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Init vendorId(int value) {
		return vendorId(NativeObject.toUnsignedShort(value));
	}

	/**
	 * Device ID. If set to 0 it will select first device, or device with
	 * matching ID.
	 * @return the field value
	 */
	public @Unsigned short deviceId() {
		return (@Unsigned short) VH_DEVICEID.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code deviceId} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Init deviceId(@Unsigned short value) {
		VH_DEVICEID.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Sets the native {@code deviceId} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Init deviceId(int value) {
		return deviceId(NativeObject.toUnsignedShort(value));
	}

	/**
	 * Capabilities initialization mask (default: UINT64_MAX).
	 * @return the field value
	 */
	public @Unsigned long capabilities() {
		return (@Unsigned long) VH_CAPABILITIES.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code capabilities} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Init capabilities(@Unsigned long value) {
		VH_CAPABILITIES.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Enable device for debugging.
	 * @return the field value
	 */
	public boolean debug() {
		return (boolean) VH_DEBUG.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code debug} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Init debug(boolean value) {
		VH_DEBUG.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Enable device for profiling.
	 * @return the field value
	 */
	public boolean profile() {
		return (boolean) VH_PROFILE.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code profile} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Init profile(boolean value) {
		VH_PROFILE.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Enable fallback to next available renderer.
	 * @return the field value
	 */
	public boolean fallback() {
		return (boolean) VH_FALLBACK.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code fallback} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Init fallback(boolean value) {
		VH_FALLBACK.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Enable video decoding.
	 * @return the field value
	 */
	public boolean videoDecode() {
		return (boolean) VH_VIDEODECODE.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code videoDecode} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Init videoDecode(boolean value) {
		VH_VIDEODECODE.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Platform data.
	 * @return the field value
	 */
	public PlatformData platformData() {
		return new PlatformData(slice(MH_PLATFORMDATA, segment()));
	}

	/**
	 * Sets the native {@code platformData} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Init platformData(PlatformData value) {
		slice(MH_PLATFORMDATA, segment()).copyFrom(value.segment());
		return this;
	}

	/**
	 * Swap chain for the window bgfx creates its device on.
	 * See: {@code SwapChain}.
	 * @return the field value
	 */
	public SwapChain swapChain() {
		return new SwapChain(slice(MH_SWAPCHAIN, segment()));
	}

	/**
	 * Sets the native {@code swapChain} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Init swapChain(SwapChain value) {
		slice(MH_SWAPCHAIN, segment()).copyFrom(value.segment());
		return this;
	}

	/**
	 * Device and frame global settings. Anything that is a
	 * property of one surface belongs in {@code swapChain} instead.
	 * See: {@code BGFX_RESET_*}.
	 * @return the field value
	 */
	public @Unsigned int reset() {
		return (@Unsigned int) VH_RESET.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code reset} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Init reset(@Unsigned int value) {
		VH_RESET.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Configurable runtime limits parameters.
	 * @return the field value
	 */
	public io.github.bkaradzic.bgfx.init.Limits limits() {
		return new io.github.bkaradzic.bgfx.init.Limits(slice(MH_LIMITS, segment()));
	}

	/**
	 * Sets the native {@code limits} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Init limits(io.github.bkaradzic.bgfx.init.Limits value) {
		slice(MH_LIMITS, segment()).copyFrom(value.segment());
		return this;
	}

	/**
	 * Provide application specific callback interface.
	 * See: {@code CallbackI}
	 * @return the field value
	 */
	public MemorySegment callback() {
		return address((MemorySegment) VH_CALLBACK.get(segment(), 0L));
	}

	/**
	 * Sets the native {@code callback} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Init callback(MemorySegment value) {
		VH_CALLBACK.set(segment(), 0L, address(value));
		return this;
	}

	/**
	 * Custom allocator. When a custom allocator is not
	 * specified, bgfx uses the CRT allocator. Bgfx assumes
	 * custom allocator is thread safe.
	 * @return the field value
	 */
	public MemorySegment allocator() {
		return address((MemorySegment) VH_ALLOCATOR.get(segment(), 0L));
	}

	/**
	 * Sets the native {@code allocator} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Init allocator(MemorySegment value) {
		VH_ALLOCATOR.set(segment(), 0L, address(value));
		return this;
	}
}
