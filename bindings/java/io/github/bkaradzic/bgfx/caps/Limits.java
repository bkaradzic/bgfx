// Copyright 2011-2026 Branimir Karadzic. All rights reserved.
// License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE


//
// AUTO GENERATED! DO NOT EDIT!
//

package io.github.bkaradzic.bgfx.caps;

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
 * Renderer runtime limits.
 */
@NullMarked
public final class Limits extends NativeObject {
	/**
	 * Native C structure layout.
	 */
	public static final StructLayout LAYOUT = cStruct("bgfx_caps_limits_t",
		ValueLayout.JAVA_INT.withName("maxDrawCalls"),
		ValueLayout.JAVA_INT.withName("maxBlits"),
		ValueLayout.JAVA_INT.withName("maxTextureSize"),
		ValueLayout.JAVA_INT.withName("maxTextureLayers"),
		ValueLayout.JAVA_INT.withName("maxViews"),
		ValueLayout.JAVA_INT.withName("maxFrameBuffers"),
		ValueLayout.JAVA_INT.withName("maxFBAttachments"),
		ValueLayout.JAVA_INT.withName("maxPrograms"),
		ValueLayout.JAVA_INT.withName("maxShaders"),
		ValueLayout.JAVA_INT.withName("maxTextures"),
		ValueLayout.JAVA_INT.withName("maxTextureSamplers"),
		ValueLayout.JAVA_INT.withName("maxComputeBindings"),
		ValueLayout.JAVA_INT.withName("maxVertexLayouts"),
		ValueLayout.JAVA_INT.withName("maxVertexStreams"),
		ValueLayout.JAVA_INT.withName("maxVertexAttributes"),
		ValueLayout.JAVA_INT.withName("maxInstanceData"),
		ValueLayout.JAVA_INT.withName("maxIndexBuffers"),
		ValueLayout.JAVA_INT.withName("maxVertexBuffers"),
		ValueLayout.JAVA_INT.withName("maxDynamicIndexBuffers"),
		ValueLayout.JAVA_INT.withName("maxDynamicVertexBuffers"),
		ValueLayout.JAVA_INT.withName("maxUniforms"),
		ValueLayout.JAVA_INT.withName("maxOcclusionQueries"),
		ValueLayout.JAVA_INT.withName("maxEncoders"),
		ValueLayout.JAVA_INT.withName("minResourceCbSize"),
		ValueLayout.JAVA_INT.withName("maxTransientVbSize"),
		ValueLayout.JAVA_INT.withName("maxTransientIbSize"),
		ValueLayout.JAVA_INT.withName("minUniformBufferSize"),
		ValueLayout.JAVA_INT.withName("blitRowPitchAlign"),
		ValueLayout.JAVA_INT.withName("blitOffsetAlign"));
	private static final VarHandle VH_MAXDRAWCALLS = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("maxDrawCalls"));
	private static final VarHandle VH_MAXBLITS = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("maxBlits"));
	private static final VarHandle VH_MAXTEXTURESIZE = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("maxTextureSize"));
	private static final VarHandle VH_MAXTEXTURELAYERS = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("maxTextureLayers"));
	private static final VarHandle VH_MAXVIEWS = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("maxViews"));
	private static final VarHandle VH_MAXFRAMEBUFFERS = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("maxFrameBuffers"));
	private static final VarHandle VH_MAXFBATTACHMENTS = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("maxFBAttachments"));
	private static final VarHandle VH_MAXPROGRAMS = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("maxPrograms"));
	private static final VarHandle VH_MAXSHADERS = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("maxShaders"));
	private static final VarHandle VH_MAXTEXTURES = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("maxTextures"));
	private static final VarHandle VH_MAXTEXTURESAMPLERS = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("maxTextureSamplers"));
	private static final VarHandle VH_MAXCOMPUTEBINDINGS = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("maxComputeBindings"));
	private static final VarHandle VH_MAXVERTEXLAYOUTS = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("maxVertexLayouts"));
	private static final VarHandle VH_MAXVERTEXSTREAMS = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("maxVertexStreams"));
	private static final VarHandle VH_MAXVERTEXATTRIBUTES = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("maxVertexAttributes"));
	private static final VarHandle VH_MAXINSTANCEDATA = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("maxInstanceData"));
	private static final VarHandle VH_MAXINDEXBUFFERS = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("maxIndexBuffers"));
	private static final VarHandle VH_MAXVERTEXBUFFERS = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("maxVertexBuffers"));
	private static final VarHandle VH_MAXDYNAMICINDEXBUFFERS = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("maxDynamicIndexBuffers"));
	private static final VarHandle VH_MAXDYNAMICVERTEXBUFFERS = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("maxDynamicVertexBuffers"));
	private static final VarHandle VH_MAXUNIFORMS = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("maxUniforms"));
	private static final VarHandle VH_MAXOCCLUSIONQUERIES = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("maxOcclusionQueries"));
	private static final VarHandle VH_MAXENCODERS = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("maxEncoders"));
	private static final VarHandle VH_MINRESOURCECBSIZE = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("minResourceCbSize"));
	private static final VarHandle VH_MAXTRANSIENTVBSIZE = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("maxTransientVbSize"));
	private static final VarHandle VH_MAXTRANSIENTIBSIZE = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("maxTransientIbSize"));
	private static final VarHandle VH_MINUNIFORMBUFFERSIZE = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("minUniformBufferSize"));
	private static final VarHandle VH_BLITROWPITCHALIGN = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("blitRowPitchAlign"));
	private static final VarHandle VH_BLITOFFSETALIGN = LAYOUT.varHandle(
		MemoryLayout.PathElement.groupElement("blitOffsetAlign"));
	/**
	 * Wraps an existing native structure.
	 * @param segment native memory segment
	 */
	public Limits(MemorySegment segment) {
		super(segment, LAYOUT);
	}

	/**
	 * Allocates a native structure.
	 * @param allocator destination allocator
	 */
	public Limits(SegmentAllocator allocator) {
		super(allocator, LAYOUT);
	}

	/**
	 * Maximum number of draw calls.
	 * @return the field value
	 */
	public @Unsigned int maxDrawCalls() {
		return (@Unsigned int) VH_MAXDRAWCALLS.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code maxDrawCalls} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Limits maxDrawCalls(@Unsigned int value) {
		VH_MAXDRAWCALLS.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Maximum number of blit calls.
	 * @return the field value
	 */
	public @Unsigned int maxBlits() {
		return (@Unsigned int) VH_MAXBLITS.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code maxBlits} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Limits maxBlits(@Unsigned int value) {
		VH_MAXBLITS.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Maximum texture size.
	 * @return the field value
	 */
	public @Unsigned int maxTextureSize() {
		return (@Unsigned int) VH_MAXTEXTURESIZE.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code maxTextureSize} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Limits maxTextureSize(@Unsigned int value) {
		VH_MAXTEXTURESIZE.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Maximum texture layers.
	 * @return the field value
	 */
	public @Unsigned int maxTextureLayers() {
		return (@Unsigned int) VH_MAXTEXTURELAYERS.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code maxTextureLayers} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Limits maxTextureLayers(@Unsigned int value) {
		VH_MAXTEXTURELAYERS.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Maximum number of views.
	 * @return the field value
	 */
	public @Unsigned int maxViews() {
		return (@Unsigned int) VH_MAXVIEWS.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code maxViews} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Limits maxViews(@Unsigned int value) {
		VH_MAXVIEWS.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Maximum number of frame buffer handles.
	 * @return the field value
	 */
	public @Unsigned int maxFrameBuffers() {
		return (@Unsigned int) VH_MAXFRAMEBUFFERS.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code maxFrameBuffers} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Limits maxFrameBuffers(@Unsigned int value) {
		VH_MAXFRAMEBUFFERS.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Maximum number of frame buffer attachments.
	 * @return the field value
	 */
	public @Unsigned int maxFBAttachments() {
		return (@Unsigned int) VH_MAXFBATTACHMENTS.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code maxFBAttachments} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Limits maxFBAttachments(@Unsigned int value) {
		VH_MAXFBATTACHMENTS.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Maximum number of program handles.
	 * @return the field value
	 */
	public @Unsigned int maxPrograms() {
		return (@Unsigned int) VH_MAXPROGRAMS.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code maxPrograms} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Limits maxPrograms(@Unsigned int value) {
		VH_MAXPROGRAMS.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Maximum number of shader handles.
	 * @return the field value
	 */
	public @Unsigned int maxShaders() {
		return (@Unsigned int) VH_MAXSHADERS.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code maxShaders} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Limits maxShaders(@Unsigned int value) {
		VH_MAXSHADERS.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Maximum number of texture handles.
	 * @return the field value
	 */
	public @Unsigned int maxTextures() {
		return (@Unsigned int) VH_MAXTEXTURES.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code maxTextures} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Limits maxTextures(@Unsigned int value) {
		VH_MAXTEXTURES.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Maximum number of texture samplers.
	 * @return the field value
	 */
	public @Unsigned int maxTextureSamplers() {
		return (@Unsigned int) VH_MAXTEXTURESAMPLERS.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code maxTextureSamplers} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Limits maxTextureSamplers(@Unsigned int value) {
		VH_MAXTEXTURESAMPLERS.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Maximum number of compute bindings.
	 * @return the field value
	 */
	public @Unsigned int maxComputeBindings() {
		return (@Unsigned int) VH_MAXCOMPUTEBINDINGS.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code maxComputeBindings} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Limits maxComputeBindings(@Unsigned int value) {
		VH_MAXCOMPUTEBINDINGS.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Maximum number of vertex format layouts.
	 * @return the field value
	 */
	public @Unsigned int maxVertexLayouts() {
		return (@Unsigned int) VH_MAXVERTEXLAYOUTS.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code maxVertexLayouts} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Limits maxVertexLayouts(@Unsigned int value) {
		VH_MAXVERTEXLAYOUTS.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Maximum number of vertex streams.
	 * @return the field value
	 */
	public @Unsigned int maxVertexStreams() {
		return (@Unsigned int) VH_MAXVERTEXSTREAMS.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code maxVertexStreams} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Limits maxVertexStreams(@Unsigned int value) {
		VH_MAXVERTEXSTREAMS.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Maximum number of vertex attributes.
	 * @return the field value
	 */
	public @Unsigned int maxVertexAttributes() {
		return (@Unsigned int) VH_MAXVERTEXATTRIBUTES.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code maxVertexAttributes} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Limits maxVertexAttributes(@Unsigned int value) {
		VH_MAXVERTEXATTRIBUTES.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Maximum number of instance data slots.
	 * @return the field value
	 */
	public @Unsigned int maxInstanceData() {
		return (@Unsigned int) VH_MAXINSTANCEDATA.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code maxInstanceData} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Limits maxInstanceData(@Unsigned int value) {
		VH_MAXINSTANCEDATA.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Maximum number of index buffer handles.
	 * @return the field value
	 */
	public @Unsigned int maxIndexBuffers() {
		return (@Unsigned int) VH_MAXINDEXBUFFERS.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code maxIndexBuffers} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Limits maxIndexBuffers(@Unsigned int value) {
		VH_MAXINDEXBUFFERS.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Maximum number of vertex buffer handles.
	 * @return the field value
	 */
	public @Unsigned int maxVertexBuffers() {
		return (@Unsigned int) VH_MAXVERTEXBUFFERS.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code maxVertexBuffers} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Limits maxVertexBuffers(@Unsigned int value) {
		VH_MAXVERTEXBUFFERS.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Maximum number of dynamic index buffer handles.
	 * @return the field value
	 */
	public @Unsigned int maxDynamicIndexBuffers() {
		return (@Unsigned int) VH_MAXDYNAMICINDEXBUFFERS.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code maxDynamicIndexBuffers} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Limits maxDynamicIndexBuffers(@Unsigned int value) {
		VH_MAXDYNAMICINDEXBUFFERS.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Maximum number of dynamic vertex buffer handles.
	 * @return the field value
	 */
	public @Unsigned int maxDynamicVertexBuffers() {
		return (@Unsigned int) VH_MAXDYNAMICVERTEXBUFFERS.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code maxDynamicVertexBuffers} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Limits maxDynamicVertexBuffers(@Unsigned int value) {
		VH_MAXDYNAMICVERTEXBUFFERS.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Maximum number of uniform handles.
	 * @return the field value
	 */
	public @Unsigned int maxUniforms() {
		return (@Unsigned int) VH_MAXUNIFORMS.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code maxUniforms} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Limits maxUniforms(@Unsigned int value) {
		VH_MAXUNIFORMS.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Maximum number of occlusion query handles.
	 * @return the field value
	 */
	public @Unsigned int maxOcclusionQueries() {
		return (@Unsigned int) VH_MAXOCCLUSIONQUERIES.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code maxOcclusionQueries} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Limits maxOcclusionQueries(@Unsigned int value) {
		VH_MAXOCCLUSIONQUERIES.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Maximum number of encoder threads.
	 * @return the field value
	 */
	public @Unsigned int maxEncoders() {
		return (@Unsigned int) VH_MAXENCODERS.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code maxEncoders} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Limits maxEncoders(@Unsigned int value) {
		VH_MAXENCODERS.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Minimum resource command buffer size.
	 * @return the field value
	 */
	public @Unsigned int minResourceCbSize() {
		return (@Unsigned int) VH_MINRESOURCECBSIZE.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code minResourceCbSize} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Limits minResourceCbSize(@Unsigned int value) {
		VH_MINRESOURCECBSIZE.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Maximum transient vertex buffer size.
	 * @return the field value
	 */
	public @Unsigned int maxTransientVbSize() {
		return (@Unsigned int) VH_MAXTRANSIENTVBSIZE.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code maxTransientVbSize} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Limits maxTransientVbSize(@Unsigned int value) {
		VH_MAXTRANSIENTVBSIZE.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Maximum transient index buffer size.
	 * @return the field value
	 */
	public @Unsigned int maxTransientIbSize() {
		return (@Unsigned int) VH_MAXTRANSIENTIBSIZE.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code maxTransientIbSize} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Limits maxTransientIbSize(@Unsigned int value) {
		VH_MAXTRANSIENTIBSIZE.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Mimimum uniform buffer size.
	 * @return the field value
	 */
	public @Unsigned int minUniformBufferSize() {
		return (@Unsigned int) VH_MINUNIFORMBUFFERSIZE.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code minUniformBufferSize} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Limits minUniformBufferSize(@Unsigned int value) {
		VH_MINUNIFORMBUFFERSIZE.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Row pitch alignment, in bytes, that buffer to texture blit copies
	 * natively. Any other {@code BufferRegion.rowPitch} is repacked internally.
	 * @return the field value
	 */
	public @Unsigned int blitRowPitchAlign() {
		return (@Unsigned int) VH_BLITROWPITCHALIGN.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code blitRowPitchAlign} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Limits blitRowPitchAlign(@Unsigned int value) {
		VH_BLITROWPITCHALIGN.set(segment(), 0L, value);
		return this;
	}

	/**
	 * Offset alignment, in bytes, that buffer to texture blit copies
	 * natively. Any other {@code BufferRegion.offset} is repacked internally.
	 * @return the field value
	 */
	public @Unsigned int blitOffsetAlign() {
		return (@Unsigned int) VH_BLITOFFSETALIGN.get(segment(), 0L);
	}

	/**
	 * Sets the native {@code blitOffsetAlign} field and returns {@code this}.
	 * @param value the new field value
	 */
	public Limits blitOffsetAlign(@Unsigned int value) {
		VH_BLITOFFSETALIGN.set(segment(), 0L, value);
		return this;
	}
}
