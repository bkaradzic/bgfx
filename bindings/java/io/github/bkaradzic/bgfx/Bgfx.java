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
 * Java FFM bindings for the bgfx C99 API.
 * <p>
 * Call {@link #load(Path)}, {@link #load(String)}, or {@link #link()} before
 * invoking a native method. Linking resolves every native entry point eagerly.
 */
@NullMarked
@SuppressWarnings("restricted")
public final class Bgfx {

	private Bgfx() {
	}

	static final MethodHandle MH_TEXTURE_REGION_INIT = downcall(
		"bgfx_texture_region_init", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, TextureHandle.LAYOUT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_BUFFER_REGION_INIT_TEXTURE = downcall(
		"bgfx_buffer_region_init_texture", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.ADDRESS));
	static final MethodHandle MH_BUFFER_REGION_INIT_BUFFER = downcall(
		"bgfx_buffer_region_init_buffer", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, BufferHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_ATTACHMENT_INIT = downcall(
		"bgfx_attachment_init", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, TextureHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_BYTE));
	static final MethodHandle MH_VERTEX_LAYOUT_BEGIN = downcall(
		"bgfx_vertex_layout_begin", FunctionDescriptor.of(ValueLayout.ADDRESS, ValueLayout.ADDRESS, ValueLayout.JAVA_INT));
	static final MethodHandle MH_VERTEX_LAYOUT_ADD = downcall(
		"bgfx_vertex_layout_add", FunctionDescriptor.of(ValueLayout.ADDRESS, ValueLayout.ADDRESS, ValueLayout.JAVA_INT, ValueLayout.JAVA_BYTE, ValueLayout.JAVA_INT, ValueLayout.JAVA_BOOLEAN, ValueLayout.JAVA_BOOLEAN));
	static final MethodHandle MH_VERTEX_LAYOUT_DECODE = downcall(
		"bgfx_vertex_layout_decode", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_INT, ValueLayout.ADDRESS, ValueLayout.ADDRESS, ValueLayout.ADDRESS, ValueLayout.ADDRESS));
	static final MethodHandle MH_VERTEX_LAYOUT_HAS = downcall(
		"bgfx_vertex_layout_has", FunctionDescriptor.of(ValueLayout.JAVA_BOOLEAN, ValueLayout.ADDRESS, ValueLayout.JAVA_INT));
	static final MethodHandle MH_VERTEX_LAYOUT_SKIP = downcall(
		"bgfx_vertex_layout_skip", FunctionDescriptor.of(ValueLayout.ADDRESS, ValueLayout.ADDRESS, ValueLayout.JAVA_BYTE));
	static final MethodHandle MH_VERTEX_LAYOUT_END = downcall(
		"bgfx_vertex_layout_end", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS));
	static final MethodHandle MH_VERTEX_LAYOUT_GET_OFFSET = downcall(
		"bgfx_vertex_layout_get_offset", FunctionDescriptor.of(ValueLayout.JAVA_SHORT, ValueLayout.ADDRESS, ValueLayout.JAVA_INT));
	static final MethodHandle MH_VERTEX_LAYOUT_GET_STRIDE = downcall(
		"bgfx_vertex_layout_get_stride", FunctionDescriptor.of(ValueLayout.JAVA_SHORT, ValueLayout.ADDRESS));
	static final MethodHandle MH_VERTEX_LAYOUT_GET_SIZE = downcall(
		"bgfx_vertex_layout_get_size", FunctionDescriptor.of(ValueLayout.JAVA_INT, ValueLayout.ADDRESS, ValueLayout.JAVA_INT));
	static final MethodHandle MH_VERTEX_PACK = downcall(
		"bgfx_vertex_pack", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_BOOLEAN, ValueLayout.JAVA_INT, ValueLayout.ADDRESS, ValueLayout.ADDRESS, ValueLayout.JAVA_INT));
	static final MethodHandle MH_VERTEX_UNPACK = downcall(
		"bgfx_vertex_unpack", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_INT, ValueLayout.ADDRESS, ValueLayout.ADDRESS, ValueLayout.JAVA_INT));
	static final MethodHandle MH_VERTEX_CONVERT = downcall(
		"bgfx_vertex_convert", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.ADDRESS, ValueLayout.ADDRESS, ValueLayout.ADDRESS, ValueLayout.JAVA_INT));
	static final MethodHandle MH_TOPOLOGY_CONVERT = downcall(
		"bgfx_topology_convert", FunctionDescriptor.of(ValueLayout.JAVA_INT, ValueLayout.JAVA_INT, ValueLayout.ADDRESS, ValueLayout.JAVA_INT, ValueLayout.ADDRESS, ValueLayout.JAVA_INT, ValueLayout.JAVA_BOOLEAN));
	static final MethodHandle MH_TOPOLOGY_SORT_TRI_LIST = downcall(
		"bgfx_topology_sort_tri_list", FunctionDescriptor.ofVoid(ValueLayout.JAVA_INT, ValueLayout.ADDRESS, ValueLayout.JAVA_INT, ValueLayout.ADDRESS, ValueLayout.ADDRESS, ValueLayout.ADDRESS, ValueLayout.JAVA_INT, ValueLayout.ADDRESS, ValueLayout.JAVA_INT, ValueLayout.JAVA_BOOLEAN));
	static final MethodHandle MH_GET_SUPPORTED_RENDERERS = downcall(
		"bgfx_get_supported_renderers", FunctionDescriptor.of(ValueLayout.JAVA_BYTE, ValueLayout.JAVA_BYTE, ValueLayout.ADDRESS));
	static final MethodHandle MH_GET_RENDERER_NAME = downcall(
		"bgfx_get_renderer_name", FunctionDescriptor.of(ValueLayout.ADDRESS, ValueLayout.JAVA_INT));
	static final MethodHandle MH_INIT_CTOR = downcall(
		"bgfx_init_ctor", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS));
	static final MethodHandle MH_INIT = downcall(
		"bgfx_init", FunctionDescriptor.of(ValueLayout.JAVA_BOOLEAN, ValueLayout.ADDRESS));
	static final MethodHandle MH_SHUTDOWN = downcall(
		"bgfx_shutdown", FunctionDescriptor.ofVoid());
	static final MethodHandle MH_RESET = downcall(
		"bgfx_reset", FunctionDescriptor.ofVoid(ValueLayout.JAVA_INT, ValueLayout.ADDRESS));
	static final MethodHandle MH_FRAME = downcall(
		"bgfx_frame", FunctionDescriptor.of(ValueLayout.JAVA_INT, ValueLayout.JAVA_BYTE));
	static final MethodHandle MH_GET_RENDERER_TYPE = downcall(
		"bgfx_get_renderer_type", FunctionDescriptor.of(ValueLayout.JAVA_INT));
	static final MethodHandle MH_GET_CAPS = downcall(
		"bgfx_get_caps", FunctionDescriptor.of(ValueLayout.ADDRESS));
	static final MethodHandle MH_GET_STATS = downcall(
		"bgfx_get_stats", FunctionDescriptor.of(ValueLayout.ADDRESS));
	static final MethodHandle MH_ALLOC = downcall(
		"bgfx_alloc", FunctionDescriptor.of(ValueLayout.ADDRESS, ValueLayout.JAVA_INT));
	static final MethodHandle MH_COPY = downcall(
		"bgfx_copy", FunctionDescriptor.of(ValueLayout.ADDRESS, ValueLayout.ADDRESS, ValueLayout.JAVA_INT));
	static final MethodHandle MH_MAKE_REF = downcall(
		"bgfx_make_ref", FunctionDescriptor.of(ValueLayout.ADDRESS, ValueLayout.ADDRESS, ValueLayout.JAVA_INT));
	static final MethodHandle MH_MAKE_REF_RELEASE = downcall(
		"bgfx_make_ref_release", FunctionDescriptor.of(ValueLayout.ADDRESS, ValueLayout.ADDRESS, ValueLayout.JAVA_INT, ValueLayout.ADDRESS, ValueLayout.ADDRESS));
	static final MethodHandle MH_SET_DEBUG = downcall(
		"bgfx_set_debug", FunctionDescriptor.ofVoid(ValueLayout.JAVA_INT, FrameBufferHandle.LAYOUT, ValueLayout.JAVA_BYTE));
	static final MethodHandle MH_DBG_TEXT_CLEAR = downcall(
		"bgfx_dbg_text_clear", FunctionDescriptor.ofVoid(ValueLayout.JAVA_BYTE, ValueLayout.JAVA_BOOLEAN));
	static final MethodHandle MH_DBG_TEXT_VPRINTF = downcall(
		"bgfx_dbg_text_vprintf", FunctionDescriptor.ofVoid(ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_BYTE, ValueLayout.ADDRESS, ValueLayout.ADDRESS));
	static final MethodHandle MH_DBG_TEXT_IMAGE = downcall(
		"bgfx_dbg_text_image", FunctionDescriptor.ofVoid(ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_CREATE_INDEX_BUFFER = downcall(
		"bgfx_create_index_buffer", FunctionDescriptor.of(IndexBufferHandle.LAYOUT, ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_READ_BUFFER = downcall(
		"bgfx_read_buffer", FunctionDescriptor.of(ValueLayout.JAVA_INT, ValueLayout.ADDRESS, ValueLayout.ADDRESS));
	static final MethodHandle MH_SET_INDEX_BUFFER_NAME = downcall(
		"bgfx_set_index_buffer_name", FunctionDescriptor.ofVoid(IndexBufferHandle.LAYOUT, ValueLayout.ADDRESS, ValueLayout.JAVA_INT));
	static final MethodHandle MH_DESTROY_INDEX_BUFFER = downcall(
		"bgfx_destroy_index_buffer", FunctionDescriptor.ofVoid(IndexBufferHandle.LAYOUT));
	static final MethodHandle MH_CREATE_VERTEX_LAYOUT = downcall(
		"bgfx_create_vertex_layout", FunctionDescriptor.of(VertexLayoutHandle.LAYOUT, ValueLayout.ADDRESS));
	static final MethodHandle MH_DESTROY_VERTEX_LAYOUT = downcall(
		"bgfx_destroy_vertex_layout", FunctionDescriptor.ofVoid(VertexLayoutHandle.LAYOUT));
	static final MethodHandle MH_CREATE_VERTEX_BUFFER = downcall(
		"bgfx_create_vertex_buffer", FunctionDescriptor.of(VertexBufferHandle.LAYOUT, ValueLayout.ADDRESS, ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_SET_VERTEX_BUFFER_NAME = downcall(
		"bgfx_set_vertex_buffer_name", FunctionDescriptor.ofVoid(VertexBufferHandle.LAYOUT, ValueLayout.ADDRESS, ValueLayout.JAVA_INT));
	static final MethodHandle MH_DESTROY_VERTEX_BUFFER = downcall(
		"bgfx_destroy_vertex_buffer", FunctionDescriptor.ofVoid(VertexBufferHandle.LAYOUT));
	static final MethodHandle MH_CREATE_DYNAMIC_INDEX_BUFFER = downcall(
		"bgfx_create_dynamic_index_buffer", FunctionDescriptor.of(DynamicIndexBufferHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_CREATE_DYNAMIC_INDEX_BUFFER_MEM = downcall(
		"bgfx_create_dynamic_index_buffer_mem", FunctionDescriptor.of(DynamicIndexBufferHandle.LAYOUT, ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_UPDATE_DYNAMIC_INDEX_BUFFER = downcall(
		"bgfx_update_dynamic_index_buffer", FunctionDescriptor.ofVoid(DynamicIndexBufferHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.ADDRESS));
	static final MethodHandle MH_DESTROY_DYNAMIC_INDEX_BUFFER = downcall(
		"bgfx_destroy_dynamic_index_buffer", FunctionDescriptor.ofVoid(DynamicIndexBufferHandle.LAYOUT));
	static final MethodHandle MH_CREATE_DYNAMIC_VERTEX_BUFFER = downcall(
		"bgfx_create_dynamic_vertex_buffer", FunctionDescriptor.of(DynamicVertexBufferHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_CREATE_DYNAMIC_VERTEX_BUFFER_MEM = downcall(
		"bgfx_create_dynamic_vertex_buffer_mem", FunctionDescriptor.of(DynamicVertexBufferHandle.LAYOUT, ValueLayout.ADDRESS, ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_UPDATE_DYNAMIC_VERTEX_BUFFER = downcall(
		"bgfx_update_dynamic_vertex_buffer", FunctionDescriptor.ofVoid(DynamicVertexBufferHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.ADDRESS));
	static final MethodHandle MH_DESTROY_DYNAMIC_VERTEX_BUFFER = downcall(
		"bgfx_destroy_dynamic_vertex_buffer", FunctionDescriptor.ofVoid(DynamicVertexBufferHandle.LAYOUT));
	static final MethodHandle MH_GET_AVAIL_TRANSIENT_INDEX_BUFFER = downcall(
		"bgfx_get_avail_transient_index_buffer", FunctionDescriptor.of(ValueLayout.JAVA_INT, ValueLayout.JAVA_INT, ValueLayout.JAVA_BOOLEAN));
	static final MethodHandle MH_GET_AVAIL_TRANSIENT_VERTEX_BUFFER = downcall(
		"bgfx_get_avail_transient_vertex_buffer", FunctionDescriptor.of(ValueLayout.JAVA_INT, ValueLayout.JAVA_INT, ValueLayout.ADDRESS));
	static final MethodHandle MH_GET_AVAIL_INSTANCE_DATA_BUFFER = downcall(
		"bgfx_get_avail_instance_data_buffer", FunctionDescriptor.of(ValueLayout.JAVA_INT, ValueLayout.JAVA_INT, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_ALLOC_TRANSIENT_INDEX_BUFFER = downcall(
		"bgfx_alloc_transient_index_buffer", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_INT, ValueLayout.JAVA_BOOLEAN));
	static final MethodHandle MH_ALLOC_TRANSIENT_VERTEX_BUFFER = downcall(
		"bgfx_alloc_transient_vertex_buffer", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_INT, ValueLayout.ADDRESS));
	static final MethodHandle MH_ALLOC_TRANSIENT_BUFFERS = downcall(
		"bgfx_alloc_transient_buffers", FunctionDescriptor.of(ValueLayout.JAVA_BOOLEAN, ValueLayout.ADDRESS, ValueLayout.ADDRESS, ValueLayout.JAVA_INT, ValueLayout.ADDRESS, ValueLayout.JAVA_INT, ValueLayout.JAVA_BOOLEAN));
	static final MethodHandle MH_ALLOC_INSTANCE_DATA_BUFFER = downcall(
		"bgfx_alloc_instance_data_buffer", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_INT, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_CREATE_INDIRECT_BUFFER = downcall(
		"bgfx_create_indirect_buffer", FunctionDescriptor.of(IndirectBufferHandle.LAYOUT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_DESTROY_INDIRECT_BUFFER = downcall(
		"bgfx_destroy_indirect_buffer", FunctionDescriptor.ofVoid(IndirectBufferHandle.LAYOUT));
	static final MethodHandle MH_CREATE_SHADER = downcall(
		"bgfx_create_shader", FunctionDescriptor.of(ShaderHandle.LAYOUT, ValueLayout.ADDRESS));
	static final MethodHandle MH_GET_SHADER_UNIFORMS = downcall(
		"bgfx_get_shader_uniforms", FunctionDescriptor.of(ValueLayout.JAVA_SHORT, ShaderHandle.LAYOUT, ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_SET_SHADER_NAME = downcall(
		"bgfx_set_shader_name", FunctionDescriptor.ofVoid(ShaderHandle.LAYOUT, ValueLayout.ADDRESS, ValueLayout.JAVA_INT));
	static final MethodHandle MH_DESTROY_SHADER = downcall(
		"bgfx_destroy_shader", FunctionDescriptor.ofVoid(ShaderHandle.LAYOUT));
	static final MethodHandle MH_CREATE_PROGRAM = downcall(
		"bgfx_create_program", FunctionDescriptor.of(ProgramHandle.LAYOUT, ShaderHandle.LAYOUT, ShaderHandle.LAYOUT, ValueLayout.JAVA_BOOLEAN));
	static final MethodHandle MH_CREATE_COMPUTE_PROGRAM = downcall(
		"bgfx_create_compute_program", FunctionDescriptor.of(ProgramHandle.LAYOUT, ShaderHandle.LAYOUT, ValueLayout.JAVA_BOOLEAN));
	static final MethodHandle MH_DESTROY_PROGRAM = downcall(
		"bgfx_destroy_program", FunctionDescriptor.ofVoid(ProgramHandle.LAYOUT));
	static final MethodHandle MH_IS_TEXTURE_VALID = downcall(
		"bgfx_is_texture_valid", FunctionDescriptor.of(ValueLayout.JAVA_BOOLEAN, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_BOOLEAN, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_INT, ValueLayout.JAVA_LONG));
	static final MethodHandle MH_IS_VIDEO_CODEC_VALID = downcall(
		"bgfx_is_video_codec_valid", FunctionDescriptor.of(ValueLayout.JAVA_BOOLEAN, ValueLayout.JAVA_INT, ValueLayout.JAVA_BYTE, ValueLayout.JAVA_BYTE, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_BYTE, ValueLayout.JAVA_BYTE));
	static final MethodHandle MH_IS_FRAME_BUFFER_VALID = downcall(
		"bgfx_is_frame_buffer_valid", FunctionDescriptor.of(ValueLayout.JAVA_BOOLEAN, ValueLayout.JAVA_BYTE, ValueLayout.ADDRESS));
	static final MethodHandle MH_CALC_TEXTURE_SIZE = downcall(
		"bgfx_calc_texture_size", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_BOOLEAN, ValueLayout.JAVA_BOOLEAN, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_CREATE_TEXTURE = downcall(
		"bgfx_create_texture", FunctionDescriptor.of(TextureHandle.LAYOUT, ValueLayout.ADDRESS, ValueLayout.JAVA_LONG, ValueLayout.JAVA_BYTE, ValueLayout.ADDRESS));
	static final MethodHandle MH_CREATE_TEXTURE_2D = downcall(
		"bgfx_create_texture_2d", FunctionDescriptor.of(TextureHandle.LAYOUT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_BOOLEAN, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_INT, ValueLayout.JAVA_LONG, ValueLayout.ADDRESS, ValueLayout.JAVA_LONG));
	static final MethodHandle MH_CREATE_TEXTURE_2D_SCALED = downcall(
		"bgfx_create_texture_2d_scaled", FunctionDescriptor.of(TextureHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_BOOLEAN, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_INT, ValueLayout.JAVA_LONG));
	static final MethodHandle MH_CREATE_TEXTURE_3D = downcall(
		"bgfx_create_texture_3d", FunctionDescriptor.of(TextureHandle.LAYOUT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_BOOLEAN, ValueLayout.JAVA_INT, ValueLayout.JAVA_LONG, ValueLayout.ADDRESS, ValueLayout.JAVA_LONG));
	static final MethodHandle MH_CREATE_TEXTURE_CUBE = downcall(
		"bgfx_create_texture_cube", FunctionDescriptor.of(TextureHandle.LAYOUT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_BOOLEAN, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_INT, ValueLayout.JAVA_LONG, ValueLayout.ADDRESS, ValueLayout.JAVA_LONG));
	static final MethodHandle MH_UPDATE_TEXTURE_2D = downcall(
		"bgfx_update_texture_2d", FunctionDescriptor.ofVoid(TextureHandle.LAYOUT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_BYTE, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_UPDATE_TEXTURE_3D = downcall(
		"bgfx_update_texture_3d", FunctionDescriptor.ofVoid(TextureHandle.LAYOUT, ValueLayout.JAVA_BYTE, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.ADDRESS));
	static final MethodHandle MH_UPDATE_TEXTURE_CUBE = downcall(
		"bgfx_update_texture_cube", FunctionDescriptor.ofVoid(TextureHandle.LAYOUT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_BYTE, ValueLayout.JAVA_BYTE, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_CLEAR_TEXTURE = downcall(
		"bgfx_clear_texture", FunctionDescriptor.ofVoid(TextureHandle.LAYOUT, ValueLayout.JAVA_BYTE, ValueLayout.JAVA_BYTE, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_READ_TEXTURE = downcall(
		"bgfx_read_texture", FunctionDescriptor.of(ValueLayout.JAVA_INT, ValueLayout.ADDRESS, ValueLayout.ADDRESS));
	static final MethodHandle MH_SET_TEXTURE_NAME = downcall(
		"bgfx_set_texture_name", FunctionDescriptor.ofVoid(TextureHandle.LAYOUT, ValueLayout.ADDRESS, ValueLayout.JAVA_INT));
	static final MethodHandle MH_GET_DIRECT_ACCESS_PTR = downcall(
		"bgfx_get_direct_access_ptr", FunctionDescriptor.of(ValueLayout.ADDRESS, TextureHandle.LAYOUT));
	static final MethodHandle MH_DESTROY_TEXTURE = downcall(
		"bgfx_destroy_texture", FunctionDescriptor.ofVoid(TextureHandle.LAYOUT));
	static final MethodHandle MH_CREATE_FRAME_BUFFER = downcall(
		"bgfx_create_frame_buffer", FunctionDescriptor.of(FrameBufferHandle.LAYOUT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_INT, ValueLayout.JAVA_LONG));
	static final MethodHandle MH_CREATE_FRAME_BUFFER_SCALED = downcall(
		"bgfx_create_frame_buffer_scaled", FunctionDescriptor.of(FrameBufferHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT, ValueLayout.JAVA_LONG));
	static final MethodHandle MH_CREATE_FRAME_BUFFER_FROM_HANDLES = downcall(
		"bgfx_create_frame_buffer_from_handles", FunctionDescriptor.of(FrameBufferHandle.LAYOUT, ValueLayout.JAVA_BYTE, ValueLayout.ADDRESS, ValueLayout.JAVA_BOOLEAN));
	static final MethodHandle MH_CREATE_FRAME_BUFFER_FROM_ATTACHMENT = downcall(
		"bgfx_create_frame_buffer_from_attachment", FunctionDescriptor.of(FrameBufferHandle.LAYOUT, ValueLayout.JAVA_BYTE, ValueLayout.ADDRESS, ValueLayout.JAVA_BOOLEAN));
	static final MethodHandle MH_CREATE_FRAME_BUFFER_FROM_SWAP_CHAIN = downcall(
		"bgfx_create_frame_buffer_from_swap_chain", FunctionDescriptor.of(FrameBufferHandle.LAYOUT, ValueLayout.ADDRESS));
	static final MethodHandle MH_UPDATE_SWAP_CHAIN = downcall(
		"bgfx_update_swap_chain", FunctionDescriptor.ofVoid(FrameBufferHandle.LAYOUT, ValueLayout.ADDRESS));
	static final MethodHandle MH_SET_FRAME_BUFFER_NAME = downcall(
		"bgfx_set_frame_buffer_name", FunctionDescriptor.ofVoid(FrameBufferHandle.LAYOUT, ValueLayout.ADDRESS, ValueLayout.JAVA_INT));
	static final MethodHandle MH_GET_TEXTURE = downcall(
		"bgfx_get_texture", FunctionDescriptor.of(TextureHandle.LAYOUT, FrameBufferHandle.LAYOUT, ValueLayout.JAVA_BYTE));
	static final MethodHandle MH_DESTROY_FRAME_BUFFER = downcall(
		"bgfx_destroy_frame_buffer", FunctionDescriptor.ofVoid(FrameBufferHandle.LAYOUT));
	static final MethodHandle MH_CREATE_UNIFORM = downcall(
		"bgfx_create_uniform", FunctionDescriptor.of(UniformHandle.LAYOUT, ValueLayout.ADDRESS, ValueLayout.JAVA_INT, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_CREATE_UNIFORM_WITH_FREQ = downcall(
		"bgfx_create_uniform_with_freq", FunctionDescriptor.of(UniformHandle.LAYOUT, ValueLayout.ADDRESS, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_GET_UNIFORM_INFO = downcall(
		"bgfx_get_uniform_info", FunctionDescriptor.ofVoid(UniformHandle.LAYOUT, ValueLayout.ADDRESS));
	static final MethodHandle MH_DESTROY_UNIFORM = downcall(
		"bgfx_destroy_uniform", FunctionDescriptor.ofVoid(UniformHandle.LAYOUT));
	static final MethodHandle MH_CREATE_OCCLUSION_QUERY = downcall(
		"bgfx_create_occlusion_query", FunctionDescriptor.of(OcclusionQueryHandle.LAYOUT));
	static final MethodHandle MH_GET_RESULT = downcall(
		"bgfx_get_result", FunctionDescriptor.of(ValueLayout.JAVA_INT, OcclusionQueryHandle.LAYOUT, ValueLayout.ADDRESS));
	static final MethodHandle MH_DESTROY_OCCLUSION_QUERY = downcall(
		"bgfx_destroy_occlusion_query", FunctionDescriptor.ofVoid(OcclusionQueryHandle.LAYOUT));
	static final MethodHandle MH_SET_PALETTE_COLOR = downcall(
		"bgfx_set_palette_color", FunctionDescriptor.ofVoid(ValueLayout.JAVA_BYTE, ValueLayout.ADDRESS));
	static final MethodHandle MH_SET_PALETTE_COLOR_RGBA32F = downcall(
		"bgfx_set_palette_color_rgba32f", FunctionDescriptor.ofVoid(ValueLayout.JAVA_BYTE, ValueLayout.JAVA_FLOAT, ValueLayout.JAVA_FLOAT, ValueLayout.JAVA_FLOAT, ValueLayout.JAVA_FLOAT));
	static final MethodHandle MH_SET_PALETTE_COLOR_RGBA8 = downcall(
		"bgfx_set_palette_color_rgba8", FunctionDescriptor.ofVoid(ValueLayout.JAVA_BYTE, ValueLayout.JAVA_INT));
	static final MethodHandle MH_SET_VIEW_NAME = downcall(
		"bgfx_set_view_name", FunctionDescriptor.ofVoid(ValueLayout.JAVA_SHORT, ValueLayout.ADDRESS, ValueLayout.JAVA_INT));
	static final MethodHandle MH_SET_VIEW_RECT = downcall(
		"bgfx_set_view_rect", FunctionDescriptor.ofVoid(ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_SET_VIEW_RECT_RATIO = downcall(
		"bgfx_set_view_rect_ratio", FunctionDescriptor.ofVoid(ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_SET_VIEW_SCISSOR = downcall(
		"bgfx_set_view_scissor", FunctionDescriptor.ofVoid(ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_SET_VIEW_CLEAR = downcall(
		"bgfx_set_view_clear", FunctionDescriptor.ofVoid(ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_INT, ValueLayout.JAVA_FLOAT, ValueLayout.JAVA_BYTE));
	static final MethodHandle MH_SET_VIEW_CLEAR_MRT = downcall(
		"bgfx_set_view_clear_mrt", FunctionDescriptor.ofVoid(ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_FLOAT, ValueLayout.JAVA_BYTE, ValueLayout.JAVA_BYTE, ValueLayout.JAVA_BYTE, ValueLayout.JAVA_BYTE, ValueLayout.JAVA_BYTE, ValueLayout.JAVA_BYTE, ValueLayout.JAVA_BYTE, ValueLayout.JAVA_BYTE, ValueLayout.JAVA_BYTE));
	static final MethodHandle MH_SET_VIEW_MODE = downcall(
		"bgfx_set_view_mode", FunctionDescriptor.ofVoid(ValueLayout.JAVA_SHORT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_SET_VIEW_FRAME_BUFFER = downcall(
		"bgfx_set_view_frame_buffer", FunctionDescriptor.ofVoid(ValueLayout.JAVA_SHORT, FrameBufferHandle.LAYOUT));
	static final MethodHandle MH_SET_VIEW_TRANSFORM = downcall(
		"bgfx_set_view_transform", FunctionDescriptor.ofVoid(ValueLayout.JAVA_SHORT, ValueLayout.ADDRESS, ValueLayout.ADDRESS));
	static final MethodHandle MH_SET_VIEW_ORDER = downcall(
		"bgfx_set_view_order", FunctionDescriptor.ofVoid(ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.ADDRESS));
	static final MethodHandle MH_SET_VIEW_SHADING_RATE = downcall(
		"bgfx_set_view_shading_rate", FunctionDescriptor.ofVoid(ValueLayout.JAVA_SHORT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_RESET_VIEW = downcall(
		"bgfx_reset_view", FunctionDescriptor.ofVoid(ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_ENCODER_BEGIN = downcall(
		"bgfx_encoder_begin", FunctionDescriptor.of(ValueLayout.ADDRESS, ValueLayout.JAVA_BOOLEAN));
	static final MethodHandle MH_ENCODER_END = downcall(
		"bgfx_encoder_end", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS));
	static final MethodHandle MH_ENCODER_SET_MARKER = downcall(
		"bgfx_encoder_set_marker", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.ADDRESS, ValueLayout.JAVA_INT));
	static final MethodHandle MH_ENCODER_SET_STATE = downcall(
		"bgfx_encoder_set_state", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_LONG, ValueLayout.JAVA_INT));
	static final MethodHandle MH_ENCODER_SET_CONDITION = downcall(
		"bgfx_encoder_set_condition", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, OcclusionQueryHandle.LAYOUT, ValueLayout.JAVA_BOOLEAN));
	static final MethodHandle MH_ENCODER_SET_STENCIL = downcall(
		"bgfx_encoder_set_stencil", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_ENCODER_SET_SCISSOR = downcall(
		"bgfx_encoder_set_scissor", FunctionDescriptor.of(ValueLayout.JAVA_SHORT, ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_ENCODER_SET_SCISSOR_CACHED = downcall(
		"bgfx_encoder_set_scissor_cached", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_ENCODER_SET_TRANSFORM = downcall(
		"bgfx_encoder_set_transform", FunctionDescriptor.of(ValueLayout.JAVA_INT, ValueLayout.ADDRESS, ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_ENCODER_SET_TRANSFORM_CACHED = downcall(
		"bgfx_encoder_set_transform_cached", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_INT, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_ENCODER_ALLOC_TRANSFORM = downcall(
		"bgfx_encoder_alloc_transform", FunctionDescriptor.of(ValueLayout.JAVA_INT, ValueLayout.ADDRESS, ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_ENCODER_SET_UNIFORM = downcall(
		"bgfx_encoder_set_uniform", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, UniformHandle.LAYOUT, ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_SET_VIEW_UNIFORM = downcall(
		"bgfx_set_view_uniform", FunctionDescriptor.ofVoid(ValueLayout.JAVA_SHORT, UniformHandle.LAYOUT, ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_SET_FRAME_UNIFORM = downcall(
		"bgfx_set_frame_uniform", FunctionDescriptor.ofVoid(UniformHandle.LAYOUT, ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_ENCODER_SET_INDEX_BUFFER = downcall(
		"bgfx_encoder_set_index_buffer", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, IndexBufferHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_ENCODER_SET_DYNAMIC_INDEX_BUFFER = downcall(
		"bgfx_encoder_set_dynamic_index_buffer", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, DynamicIndexBufferHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_ENCODER_SET_TRANSIENT_INDEX_BUFFER = downcall(
		"bgfx_encoder_set_transient_index_buffer", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.ADDRESS, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_ENCODER_SET_VERTEX_BUFFER = downcall(
		"bgfx_encoder_set_vertex_buffer", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_BYTE, VertexBufferHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_ENCODER_SET_VERTEX_BUFFER_WITH_LAYOUT = downcall(
		"bgfx_encoder_set_vertex_buffer_with_layout", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_BYTE, VertexBufferHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT, VertexLayoutHandle.LAYOUT));
	static final MethodHandle MH_ENCODER_SET_DYNAMIC_VERTEX_BUFFER = downcall(
		"bgfx_encoder_set_dynamic_vertex_buffer", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_BYTE, DynamicVertexBufferHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_ENCODER_SET_DYNAMIC_VERTEX_BUFFER_WITH_LAYOUT = downcall(
		"bgfx_encoder_set_dynamic_vertex_buffer_with_layout", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_BYTE, DynamicVertexBufferHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT, VertexLayoutHandle.LAYOUT));
	static final MethodHandle MH_ENCODER_SET_TRANSIENT_VERTEX_BUFFER = downcall(
		"bgfx_encoder_set_transient_vertex_buffer", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_BYTE, ValueLayout.ADDRESS, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_ENCODER_SET_TRANSIENT_VERTEX_BUFFER_WITH_LAYOUT = downcall(
		"bgfx_encoder_set_transient_vertex_buffer_with_layout", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_BYTE, ValueLayout.ADDRESS, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT, VertexLayoutHandle.LAYOUT));
	static final MethodHandle MH_ENCODER_SET_VERTEX_COUNT = downcall(
		"bgfx_encoder_set_vertex_count", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_INT));
	static final MethodHandle MH_ENCODER_SET_INSTANCE_DATA_BUFFER = downcall(
		"bgfx_encoder_set_instance_data_buffer", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.ADDRESS, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_ENCODER_SET_INSTANCE_DATA_FROM_VERTEX_BUFFER = downcall(
		"bgfx_encoder_set_instance_data_from_vertex_buffer", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, VertexBufferHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_ENCODER_SET_INSTANCE_DATA_FROM_DYNAMIC_VERTEX_BUFFER = downcall(
		"bgfx_encoder_set_instance_data_from_dynamic_vertex_buffer", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, DynamicVertexBufferHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_ENCODER_SET_INSTANCE_COUNT = downcall(
		"bgfx_encoder_set_instance_count", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_INT));
	static final MethodHandle MH_ENCODER_SET_TEXTURE = downcall(
		"bgfx_encoder_set_texture", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_BYTE, UniformHandle.LAYOUT, TextureHandle.LAYOUT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_ENCODER_SET_TEXTURE_VIEW = downcall(
		"bgfx_encoder_set_texture_view", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_BYTE, UniformHandle.LAYOUT, TextureHandle.LAYOUT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_BYTE, ValueLayout.JAVA_BYTE, ValueLayout.JAVA_INT));
	static final MethodHandle MH_ENCODER_TOUCH = downcall(
		"bgfx_encoder_touch", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_ENCODER_SUBMIT = downcall(
		"bgfx_encoder_submit", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT, ProgramHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_BYTE));
	static final MethodHandle MH_ENCODER_SUBMIT_OCCLUSION_QUERY = downcall(
		"bgfx_encoder_submit_occlusion_query", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT, ProgramHandle.LAYOUT, OcclusionQueryHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_BYTE));
	static final MethodHandle MH_ENCODER_SUBMIT_INDIRECT = downcall(
		"bgfx_encoder_submit_indirect", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT, ProgramHandle.LAYOUT, IndirectBufferHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT, ValueLayout.JAVA_BYTE));
	static final MethodHandle MH_ENCODER_SUBMIT_INDIRECT_COUNT = downcall(
		"bgfx_encoder_submit_indirect_count", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT, ProgramHandle.LAYOUT, IndirectBufferHandle.LAYOUT, ValueLayout.JAVA_INT, IndexBufferHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT, ValueLayout.JAVA_BYTE));
	static final MethodHandle MH_ENCODER_SET_COMPUTE_INDEX_BUFFER = downcall(
		"bgfx_encoder_set_compute_index_buffer", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_BYTE, IndexBufferHandle.LAYOUT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_ENCODER_SET_COMPUTE_VERTEX_BUFFER = downcall(
		"bgfx_encoder_set_compute_vertex_buffer", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_BYTE, VertexBufferHandle.LAYOUT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_ENCODER_SET_COMPUTE_DYNAMIC_INDEX_BUFFER = downcall(
		"bgfx_encoder_set_compute_dynamic_index_buffer", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_BYTE, DynamicIndexBufferHandle.LAYOUT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_ENCODER_SET_COMPUTE_DYNAMIC_VERTEX_BUFFER = downcall(
		"bgfx_encoder_set_compute_dynamic_vertex_buffer", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_BYTE, DynamicVertexBufferHandle.LAYOUT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_ENCODER_SET_COMPUTE_INDIRECT_BUFFER = downcall(
		"bgfx_encoder_set_compute_indirect_buffer", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_BYTE, IndirectBufferHandle.LAYOUT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_ENCODER_SET_IMAGE = downcall(
		"bgfx_encoder_set_image", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_BYTE, TextureHandle.LAYOUT, ValueLayout.JAVA_BYTE, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_ENCODER_SET_IMAGE_VIEW = downcall(
		"bgfx_encoder_set_image_view", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_BYTE, TextureHandle.LAYOUT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_BYTE, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_ENCODER_DISPATCH = downcall(
		"bgfx_encoder_dispatch", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT, ProgramHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT, ValueLayout.JAVA_BYTE));
	static final MethodHandle MH_ENCODER_DISPATCH_INDIRECT = downcall(
		"bgfx_encoder_dispatch_indirect", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT, ProgramHandle.LAYOUT, IndirectBufferHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT, ValueLayout.JAVA_BYTE));
	static final MethodHandle MH_ENCODER_DISCARD = downcall(
		"bgfx_encoder_discard", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_BYTE));
	static final MethodHandle MH_ENCODER_BLIT = downcall(
		"bgfx_encoder_blit", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT, ValueLayout.ADDRESS, ValueLayout.ADDRESS));
	static final MethodHandle MH_ENCODER_BLIT_BUFFER = downcall(
		"bgfx_encoder_blit_buffer", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT, ValueLayout.ADDRESS, ValueLayout.ADDRESS));
	static final MethodHandle MH_ENCODER_BLIT_TO_BUFFER = downcall(
		"bgfx_encoder_blit_to_buffer", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT, ValueLayout.ADDRESS, ValueLayout.ADDRESS));
	static final MethodHandle MH_ENCODER_BLIT_FROM_BUFFER = downcall(
		"bgfx_encoder_blit_from_buffer", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT, ValueLayout.ADDRESS, ValueLayout.ADDRESS));
	static final MethodHandle MH_REQUEST_SCREEN_SHOT = downcall(
		"bgfx_request_screen_shot", FunctionDescriptor.ofVoid(FrameBufferHandle.LAYOUT, ValueLayout.ADDRESS));
	static final MethodHandle MH_RENDER_FRAME = downcall(
		"bgfx_render_frame", FunctionDescriptor.of(ValueLayout.JAVA_INT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_GET_INTERNAL_DATA = downcall(
		"bgfx_get_internal_data", FunctionDescriptor.of(ValueLayout.ADDRESS));
	static final MethodHandle MH_SET_MARKER = downcall(
		"bgfx_set_marker", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_INT));
	static final MethodHandle MH_SET_STATE = downcall(
		"bgfx_set_state", FunctionDescriptor.ofVoid(ValueLayout.JAVA_LONG, ValueLayout.JAVA_INT));
	static final MethodHandle MH_SET_CONDITION = downcall(
		"bgfx_set_condition", FunctionDescriptor.ofVoid(OcclusionQueryHandle.LAYOUT, ValueLayout.JAVA_BOOLEAN));
	static final MethodHandle MH_SET_STENCIL = downcall(
		"bgfx_set_stencil", FunctionDescriptor.ofVoid(ValueLayout.JAVA_INT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_SET_SCISSOR = downcall(
		"bgfx_set_scissor", FunctionDescriptor.of(ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_SET_SCISSOR_CACHED = downcall(
		"bgfx_set_scissor_cached", FunctionDescriptor.ofVoid(ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_SET_TRANSFORM = downcall(
		"bgfx_set_transform", FunctionDescriptor.of(ValueLayout.JAVA_INT, ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_SET_TRANSFORM_CACHED = downcall(
		"bgfx_set_transform_cached", FunctionDescriptor.ofVoid(ValueLayout.JAVA_INT, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_ALLOC_TRANSFORM = downcall(
		"bgfx_alloc_transform", FunctionDescriptor.of(ValueLayout.JAVA_INT, ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_SET_UNIFORM = downcall(
		"bgfx_set_uniform", FunctionDescriptor.ofVoid(UniformHandle.LAYOUT, ValueLayout.ADDRESS, ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_SET_INDEX_BUFFER = downcall(
		"bgfx_set_index_buffer", FunctionDescriptor.ofVoid(IndexBufferHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_SET_DYNAMIC_INDEX_BUFFER = downcall(
		"bgfx_set_dynamic_index_buffer", FunctionDescriptor.ofVoid(DynamicIndexBufferHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_SET_TRANSIENT_INDEX_BUFFER = downcall(
		"bgfx_set_transient_index_buffer", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_SET_VERTEX_BUFFER = downcall(
		"bgfx_set_vertex_buffer", FunctionDescriptor.ofVoid(ValueLayout.JAVA_BYTE, VertexBufferHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_SET_VERTEX_BUFFER_WITH_LAYOUT = downcall(
		"bgfx_set_vertex_buffer_with_layout", FunctionDescriptor.ofVoid(ValueLayout.JAVA_BYTE, VertexBufferHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT, VertexLayoutHandle.LAYOUT));
	static final MethodHandle MH_SET_DYNAMIC_VERTEX_BUFFER = downcall(
		"bgfx_set_dynamic_vertex_buffer", FunctionDescriptor.ofVoid(ValueLayout.JAVA_BYTE, DynamicVertexBufferHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_SET_DYNAMIC_VERTEX_BUFFER_WITH_LAYOUT = downcall(
		"bgfx_set_dynamic_vertex_buffer_with_layout", FunctionDescriptor.ofVoid(ValueLayout.JAVA_BYTE, DynamicVertexBufferHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT, VertexLayoutHandle.LAYOUT));
	static final MethodHandle MH_SET_TRANSIENT_VERTEX_BUFFER = downcall(
		"bgfx_set_transient_vertex_buffer", FunctionDescriptor.ofVoid(ValueLayout.JAVA_BYTE, ValueLayout.ADDRESS, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_SET_TRANSIENT_VERTEX_BUFFER_WITH_LAYOUT = downcall(
		"bgfx_set_transient_vertex_buffer_with_layout", FunctionDescriptor.ofVoid(ValueLayout.JAVA_BYTE, ValueLayout.ADDRESS, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT, VertexLayoutHandle.LAYOUT));
	static final MethodHandle MH_SET_VERTEX_COUNT = downcall(
		"bgfx_set_vertex_count", FunctionDescriptor.ofVoid(ValueLayout.JAVA_INT));
	static final MethodHandle MH_SET_INSTANCE_DATA_BUFFER = downcall(
		"bgfx_set_instance_data_buffer", FunctionDescriptor.ofVoid(ValueLayout.ADDRESS, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_SET_INSTANCE_DATA_FROM_VERTEX_BUFFER = downcall(
		"bgfx_set_instance_data_from_vertex_buffer", FunctionDescriptor.ofVoid(VertexBufferHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_SET_INSTANCE_DATA_FROM_DYNAMIC_VERTEX_BUFFER = downcall(
		"bgfx_set_instance_data_from_dynamic_vertex_buffer", FunctionDescriptor.ofVoid(DynamicVertexBufferHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_SET_INSTANCE_COUNT = downcall(
		"bgfx_set_instance_count", FunctionDescriptor.ofVoid(ValueLayout.JAVA_INT));
	static final MethodHandle MH_SET_TEXTURE = downcall(
		"bgfx_set_texture", FunctionDescriptor.ofVoid(ValueLayout.JAVA_BYTE, UniformHandle.LAYOUT, TextureHandle.LAYOUT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_SET_TEXTURE_VIEW = downcall(
		"bgfx_set_texture_view", FunctionDescriptor.ofVoid(ValueLayout.JAVA_BYTE, UniformHandle.LAYOUT, TextureHandle.LAYOUT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_BYTE, ValueLayout.JAVA_BYTE, ValueLayout.JAVA_INT));
	static final MethodHandle MH_TOUCH = downcall(
		"bgfx_touch", FunctionDescriptor.ofVoid(ValueLayout.JAVA_SHORT));
	static final MethodHandle MH_SUBMIT = downcall(
		"bgfx_submit", FunctionDescriptor.ofVoid(ValueLayout.JAVA_SHORT, ProgramHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_BYTE));
	static final MethodHandle MH_SUBMIT_OCCLUSION_QUERY = downcall(
		"bgfx_submit_occlusion_query", FunctionDescriptor.ofVoid(ValueLayout.JAVA_SHORT, ProgramHandle.LAYOUT, OcclusionQueryHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_BYTE));
	static final MethodHandle MH_SUBMIT_INDIRECT = downcall(
		"bgfx_submit_indirect", FunctionDescriptor.ofVoid(ValueLayout.JAVA_SHORT, ProgramHandle.LAYOUT, IndirectBufferHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT, ValueLayout.JAVA_BYTE));
	static final MethodHandle MH_SUBMIT_INDIRECT_COUNT = downcall(
		"bgfx_submit_indirect_count", FunctionDescriptor.ofVoid(ValueLayout.JAVA_SHORT, ProgramHandle.LAYOUT, IndirectBufferHandle.LAYOUT, ValueLayout.JAVA_INT, IndexBufferHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT, ValueLayout.JAVA_BYTE));
	static final MethodHandle MH_SET_COMPUTE_INDEX_BUFFER = downcall(
		"bgfx_set_compute_index_buffer", FunctionDescriptor.ofVoid(ValueLayout.JAVA_BYTE, IndexBufferHandle.LAYOUT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_SET_COMPUTE_VERTEX_BUFFER = downcall(
		"bgfx_set_compute_vertex_buffer", FunctionDescriptor.ofVoid(ValueLayout.JAVA_BYTE, VertexBufferHandle.LAYOUT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_SET_COMPUTE_DYNAMIC_INDEX_BUFFER = downcall(
		"bgfx_set_compute_dynamic_index_buffer", FunctionDescriptor.ofVoid(ValueLayout.JAVA_BYTE, DynamicIndexBufferHandle.LAYOUT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_SET_COMPUTE_DYNAMIC_VERTEX_BUFFER = downcall(
		"bgfx_set_compute_dynamic_vertex_buffer", FunctionDescriptor.ofVoid(ValueLayout.JAVA_BYTE, DynamicVertexBufferHandle.LAYOUT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_SET_COMPUTE_INDIRECT_BUFFER = downcall(
		"bgfx_set_compute_indirect_buffer", FunctionDescriptor.ofVoid(ValueLayout.JAVA_BYTE, IndirectBufferHandle.LAYOUT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_SET_IMAGE = downcall(
		"bgfx_set_image", FunctionDescriptor.ofVoid(ValueLayout.JAVA_BYTE, TextureHandle.LAYOUT, ValueLayout.JAVA_BYTE, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_SET_IMAGE_VIEW = downcall(
		"bgfx_set_image_view", FunctionDescriptor.ofVoid(ValueLayout.JAVA_BYTE, TextureHandle.LAYOUT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_BYTE, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT));
	static final MethodHandle MH_DISPATCH = downcall(
		"bgfx_dispatch", FunctionDescriptor.ofVoid(ValueLayout.JAVA_SHORT, ProgramHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT, ValueLayout.JAVA_BYTE));
	static final MethodHandle MH_DISPATCH_INDIRECT = downcall(
		"bgfx_dispatch_indirect", FunctionDescriptor.ofVoid(ValueLayout.JAVA_SHORT, ProgramHandle.LAYOUT, IndirectBufferHandle.LAYOUT, ValueLayout.JAVA_INT, ValueLayout.JAVA_INT, ValueLayout.JAVA_BYTE));
	static final MethodHandle MH_DISCARD = downcall(
		"bgfx_discard", FunctionDescriptor.ofVoid(ValueLayout.JAVA_BYTE));
	static final MethodHandle MH_BLIT = downcall(
		"bgfx_blit", FunctionDescriptor.ofVoid(ValueLayout.JAVA_SHORT, ValueLayout.ADDRESS, ValueLayout.ADDRESS));
	static final MethodHandle MH_BLIT_BUFFER = downcall(
		"bgfx_blit_buffer", FunctionDescriptor.ofVoid(ValueLayout.JAVA_SHORT, ValueLayout.ADDRESS, ValueLayout.ADDRESS));
	static final MethodHandle MH_BLIT_TO_BUFFER = downcall(
		"bgfx_blit_to_buffer", FunctionDescriptor.ofVoid(ValueLayout.JAVA_SHORT, ValueLayout.ADDRESS, ValueLayout.ADDRESS));
	static final MethodHandle MH_BLIT_FROM_BUFFER = downcall(
		"bgfx_blit_from_buffer", FunctionDescriptor.ofVoid(ValueLayout.JAVA_SHORT, ValueLayout.ADDRESS, ValueLayout.ADDRESS));
	static final MethodHandle VS_DBG_TEXT_PRINTF = variadicSymbol("bgfx_dbg_text_printf");

	/**
	 * Pack vertex attribute into vertex stream format.
	 * @param _input Value to be packed into vertex stream.
	 * @param _inputNormalized {@code true} if input value is already normalized.
	 * @param _attr Attribute to pack.
	 * @param _layout Vertex stream layout.
	 * @param _data Destination vertex stream where data will be packed.
	 * @param _index Vertex index that will be modified.
	 */
	public static void vertexPack(MemorySegment _input, boolean _inputNormalized, Attrib _attr, VertexLayout _layout, MemorySegment _data, @Unsigned int _index) {
		try {
			MH_VERTEX_PACK.invokeExact(address(_input), _inputNormalized, _attr.ordinal(), address(_layout), address(_data), _index);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Unpack vertex attribute from vertex stream format.
	 * @param _output Result of unpacking.
	 * @param _attr Attribute to unpack.
	 * @param _layout Vertex stream layout.
	 * @param _data Source vertex stream from where data will be unpacked.
	 * @param _index Vertex index that will be unpacked.
	 */
	public static void vertexUnpack(MemorySegment _output, Attrib _attr, VertexLayout _layout, MemorySegment _data, @Unsigned int _index) {
		try {
			MH_VERTEX_UNPACK.invokeExact(address(_output), _attr.ordinal(), address(_layout), address(_data), _index);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Converts vertex stream data from one vertex stream format to another.
	 * @param _dstLayout Destination vertex stream layout.
	 * @param _dstData Destination vertex stream.
	 * @param _srcLayout Source vertex stream layout.
	 * @param _srcData Source vertex stream data.
	 * @param _num Number of vertices to convert from source to destination.
	 */
	public static void vertexConvert(VertexLayout _dstLayout, MemorySegment _dstData, VertexLayout _srcLayout, MemorySegment _srcData, @Unsigned int _num) {
		try {
			MH_VERTEX_CONVERT.invokeExact(address(_dstLayout), address(_dstData), address(_srcLayout), address(_srcData), _num);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Convert index buffer for use with different primitive topologies.
	 * @param _conversion Conversion type, see {@code TopologyConvert}.
	 * @param _dst Destination index buffer. If this argument is NULL function will return number of indices after conversion.
	 * @param _dstSize Destination index buffer in bytes. It must be large enough to contain output indices. If destination size is insufficient index buffer will be truncated.
	 * @param _indices Source indices.
	 * @param _numIndices Number of input indices.
	 * @param _index32 Set to {@code true} if input indices are 32-bit.
	 * @return Number of output indices after conversion.
	 */
	public static @Unsigned int topologyConvert(TopologyConvert _conversion, MemorySegment _dst, @Unsigned int _dstSize, MemorySegment _indices, @Unsigned int _numIndices, boolean _index32) {
		try {
			return (@Unsigned int) MH_TOPOLOGY_CONVERT.invokeExact(_conversion.ordinal(), address(_dst), _dstSize, address(_indices), _numIndices, _index32);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Sort indices.
	 * @param _sort Sort order, see {@code TopologySort}.
	 * @param _dst Destination index buffer.
	 * @param _dstSize Destination index buffer in bytes. It must be large enough to contain output indices. If destination size is insufficient index buffer will be truncated.
	 * @param _dir Direction (vector must be normalized).
	 * @param _pos Position.
	 * @param _vertices Pointer to first vertex represented as float x, y, z. Must contain at least number of vertices referencende by index buffer.
	 * @param _stride Vertex stride.
	 * @param _indices Source indices.
	 * @param _numIndices Number of input indices.
	 * @param _index32 Set to {@code true} if input indices are 32-bit.
	 */
	public static void topologySortTriList(TopologySort _sort, MemorySegment _dst, @Unsigned int _dstSize, MemorySegment _dir, MemorySegment _pos, MemorySegment _vertices, @Unsigned int _stride, MemorySegment _indices, @Unsigned int _numIndices, boolean _index32) {
		try {
			MH_TOPOLOGY_SORT_TRI_LIST.invokeExact(_sort.ordinal(), address(_dst), _dstSize, address(_dir), address(_pos), address(_vertices), _stride, address(_indices), _numIndices, _index32);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Returns supported backend API renderers.
	 * @param _max Maximum number of elements in _enum array.
	 * @param _enum Array where supported renderers will be written.
	 * @return Number of supported renderers.
	 */
	public static @Unsigned byte getSupportedRenderers(@Unsigned byte _max, @Nullable MemorySegment _enum) {
		try {
			return (@Unsigned byte) MH_GET_SUPPORTED_RENDERERS.invokeExact(_max, address(_enum));
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Returns name of renderer.
	 * @param _type Renderer backend type. See: {@code RendererType}
	 * @return Name of renderer.
	 */
	public static @Nullable String getRendererName(RendererType _type) {
		try {
			return readString((MemorySegment) MH_GET_RENDERER_NAME.invokeExact(_type.ordinal()));
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Fill Init struct with default values, before using it to initialize the library.
	 * @param _init Pointer to structure to be initialized. See: {@code Init} for more info.
	 */
	public static void initCtor(Init _init) {
		try {
			MH_INIT_CTOR.invokeExact(address(_init));
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Initialize the bgfx library.
	 * @param _init Initialization parameters. See: {@code Init} for more info.
	 * @return {@code true} if initialization was successful.
	 */
	public static boolean init(Init _init) {
		try {
			return (boolean) MH_INIT.invokeExact(address(_init));
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Shutdown bgfx library.
	 */
	public static void shutdown() {
		try {
			MH_SHUTDOWN.invokeExact();
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Reset graphic settings and back-buffer size.
	 * <p>
	 * <strong>Attention:</strong> This call doesn’t change the window size, it just resizes
	 *   the back-buffer. Your windowing code controls the window size.
	 * @param _flags See: {@code BGFX_RESET_*} for more info.   - {@code BGFX_RESET_NONE} - No reset flags.   - {@code BGFX_RESET_VSYNC} - Enable V-Sync.   - {@code BGFX_RESET_MAXANISOTROPY} - Turn on/off max anisotropy.   - {@code BGFX_RESET_CAPTURE} - Begin screen capture.   - {@code BGFX_RESET_FLUSH_AFTER_RENDER} - Flush rendering after submitting to GPU.   - {@code BGFX_RESET_FLIP_AFTER_RENDER} - This flag  specifies where flip     occurs. Default behaviour is that flip occurs before rendering new     frame. This flag only has effect when {@code BGFX_CONFIG_MULTITHREADED=0}. Per-surface settings are not here. {@code BGFX_SWAP_CHAIN_*} flags belong on {@code SwapChain.flags}, and are ignored if passed here.
	 * @param _swapChain Main window swap chain. When {@code NULL} the main window is left untouched and only the device and frame globals above are applied, which is what an application driving its own swap chains wants. Otherwise the main window takes on this description: resize it, change its format, or change its per-surface flags. Fields left neutral keep their current value, and {@code nwh}/{@code ndt} are ignored -- main's are bgfx's own. Must be {@code NULL} when {@code init} created no main window.
	 */
	public static void reset(@Unsigned int _flags, @Nullable SwapChain _swapChain) {
		try {
			MH_RESET.invokeExact(_flags, address(_swapChain));
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Advance to next frame. This is the main frame-advancement call on the
	 * API thread (the thread from which {@code init} was called).
	 * <p>
	 * **Multithreaded renderer** ({@code BGFX_CONFIG_MULTITHREADED=1}, default):
	 * This call waits for the render thread to finish processing the previous
	 * frame, then swaps internal submit/render buffers, signals the render
	 * thread to begin processing the new frame via {@code renderFrame}, and
	 * returns immediately. The render thread and API thread then run in
	 * parallel: the API thread builds the next frame while the render thread
	 * executes GPU commands for the current frame.
	 * <p>
	 * **Single-threaded renderer** ({@code BGFX_CONFIG_MULTITHREADED=0}, or when
	 * {@code renderFrame} and {@code init} are called from the same thread):
	 * This call swaps internal buffers and performs frame rendering inline
	 * (internally calls {@code renderFrame}), then returns.
	 * <p>
	 * <strong>Remarks:</strong> 
	 *   Must be called from the API thread (the thread that called
	 *   {@code init}). In multithreaded mode, this call synchronizes with
	 *   {@code renderFrame} running on the render thread via semaphores:
	 *   {@code frame} waits for the render thread to finish, then posts a
	 *   signal that {@code renderFrame} waits on to begin the next frame.
	 *   See also: {@code renderFrame}.
	 * @param _flags Frame flags. See: {@code BGFX_FRAME_*} for more info.   - {@code BGFX_FRAME_NONE} - No frame flag.   - {@code BGFX_FRAME_DEBUG_CAPTURE} - Capture frame with graphics debugger.   - {@code BGFX_FRAME_DISCARD} - Discard all draw calls.   - {@code BGFX_FRAME_FLUSH} - Execute all rendering commands     without presenting the backbuffer.
	 * @return Current frame number. This might be used in conjunction with double/multi buffering data outside the library and passing it to library via {@code makeRef} calls.
	 */
	public static @Unsigned int frame(@Unsigned byte _flags) {
		try {
			return (@Unsigned int) MH_FRAME.invokeExact(_flags);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Returns current renderer backend API type.
	 * <p>
	 * <strong>Remarks:</strong> 
	 *   Library must be initialized.
	 * @return Renderer backend type. See: {@code RendererType}
	 */
	public static RendererType getRendererType() {
		try {
			return RendererType.fromValue((int) MH_GET_RENDERER_TYPE.invokeExact());
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Returns renderer capabilities.
	 * <p>
	 * <strong>Remarks:</strong> 
	 *   Library must be initialized.
	 * @return Pointer to static {@code Caps} structure.
	 */
	public static Caps getCaps() {
		try {
			return new Caps((MemorySegment) MH_GET_CAPS.invokeExact());
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Returns performance counters.
	 * <p>
	 * <strong>Attention:</strong> Pointer returned is valid until {@code frame} is called.
	 * @return Performance counters.
	 */
	public static Stats getStats() {
		try {
			return new Stats((MemorySegment) MH_GET_STATS.invokeExact());
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Allocate buffer to pass to bgfx calls. Data will be freed inside bgfx.
	 * @param _size Size to allocate.
	 * @return Allocated memory.
	 */
	public static Memory alloc(@Unsigned int _size) {
		try {
			return new Memory((MemorySegment) MH_ALLOC.invokeExact(_size));
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Allocate buffer and copy data into it. Data will be freed inside bgfx.
	 * @param _data Pointer to data to be copied.
	 * @param _size Size of data to be copied.
	 * @return Allocated memory.
	 */
	public static Memory copy(MemorySegment _data, @Unsigned int _size) {
		try {
			return new Memory((MemorySegment) MH_COPY.invokeExact(address(_data), _size));
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Make reference to data to pass to bgfx. Unlike {@code alloc}, this call
	 * doesn't allocate memory for data. It just copies the _data pointer. You
	 * can pass {@code ReleaseFn} function pointer to release this memory after it's
	 * consumed, otherwise you must make sure _data is available for at least 2
	 * {@code frame} calls. {@code ReleaseFn} function must be able to be called
	 * from any thread.
	 * <p>
	 * <strong>Attention:</strong> Data passed must be available for at least 2 {@code frame} calls.
	 * @param _data Pointer to data.
	 * @param _size Size of data.
	 * @return Referenced memory.
	 */
	public static Memory makeRef(MemorySegment _data, @Unsigned int _size) {
		try {
			return new Memory((MemorySegment) MH_MAKE_REF.invokeExact(address(_data), _size));
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Make reference to data to pass to bgfx. Unlike {@code alloc}, this call
	 * doesn't allocate memory for data. It just copies the _data pointer. You
	 * can pass {@code ReleaseFn} function pointer to release this memory after it's
	 * consumed, otherwise you must make sure _data is available for at least 2
	 * {@code frame} calls. {@code ReleaseFn} function must be able to be called
	 * from any thread.
	 * <p>
	 * <strong>Attention:</strong> Data passed must be available for at least 2 {@code frame} calls.
	 * @param _data Pointer to data.
	 * @param _size Size of data.
	 * @param _releaseFn Callback function to release memory after use.
	 * @param _userData User data to be passed to callback function.
	 * @return Referenced memory.
	 */
	public static Memory makeRefRelease(MemorySegment _data, @Unsigned int _size, @Nullable MemorySegment _releaseFn, @Nullable MemorySegment _userData) {
		try {
			return new Memory((MemorySegment) MH_MAKE_REF_RELEASE.invokeExact(address(_data), _size, address(_releaseFn), address(_userData)));
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set debug flags.
	 * @param _debug Available flags:   - {@code BGFX_DEBUG_IFH} - Infinitely fast hardware. When this flag is set     all rendering calls will be skipped. This is useful when profiling     to quickly assess potential bottlenecks between CPU and GPU.   - {@code BGFX_DEBUG_PROFILER} - Enable profiler.   - {@code BGFX_DEBUG_STATS} - Display internal statistics.   - {@code BGFX_DEBUG_TEXT} - Display debug text.   - {@code BGFX_DEBUG_WIREFRAME} - Wireframe rendering. All rendering     primitives will be rendered as lines.
	 * @param _handle Frame buffer the debug text and statistics are drawn on. Invalid handle selects the window bgfx was initialized with.
	 * @param _scale Debug text scale factor. 0 is the same as 1.
	 */
	public static void setDebug(@Unsigned int _debug, FrameBufferHandle _handle, @Unsigned byte _scale) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SET_DEBUG.invokeExact(_debug, _handle.allocate(arena), _scale);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Clear internal debug text buffer.
	 * @param _attr Background color.
	 * @param _small Default 8x16 or 8x8 font.
	 */
	public static void dbgTextClear(@Unsigned byte _attr, boolean _small) {
		try {
			MH_DBG_TEXT_CLEAR.invokeExact(_attr, _small);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Print formatted data to internal debug text character-buffer (VGA-compatible text mode).
	 * @param _x Position x from the left corner of the window.
	 * @param _y Position y from the top corner of the window.
	 * @param _attr Color palette. Where top 4-bits represent index of background, and bottom 4-bits represent foreground color from standard VGA text palette (ANSI escape codes).
	 * @param _format {@code printf} style format.
	 * @param _args variadic arguments; C default argument promotions are applied automatically
	 */
	public static final void dbgTextPrintf(@Unsigned short _x, @Unsigned short _y, @Unsigned byte _attr, String _format, Object... _args) {
		try (Arena arena = Arena.ofConfined()) {
			Object[] nativeArgs = new Object[4];
			nativeArgs[0] = _x;
			nativeArgs[1] = _y;
			nativeArgs[2] = _attr;
			nativeArgs[3] = cString(arena, _format);
			invokeVariadic(VS_DBG_TEXT_PRINTF, FunctionDescriptor.ofVoid(ValueLayout.JAVA_SHORT, ValueLayout.JAVA_SHORT, ValueLayout.JAVA_BYTE, ValueLayout.ADDRESS), nativeArgs, _args);
		}
	}

	/**
	 * Print formatted data from variable argument list to internal debug text character-buffer (VGA-compatible text mode).
	 * @param _x Position x from the left corner of the window.
	 * @param _y Position y from the top corner of the window.
	 * @param _attr Color palette. Where top 4-bits represent index of background, and bottom 4-bits represent foreground color from standard VGA text palette (ANSI escape codes).
	 * @param _format {@code printf} style format.
	 * @param _argList Variable arguments list for format string.
	 */
	public static void dbgTextVprintf(@Unsigned short _x, @Unsigned short _y, @Unsigned byte _attr, String _format, MemorySegment _argList) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_DBG_TEXT_VPRINTF.invokeExact(_x, _y, _attr, cString(arena, _format), address(_argList));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Draw image into internal debug text buffer.
	 * @param _x Position x from the left corner of the window.
	 * @param _y Position y from the top corner of the window.
	 * @param _width Image width.
	 * @param _height Image height.
	 * @param _data Raw image data (character/attribute raw encoding).
	 * @param _pitch Image pitch in bytes.
	 */
	public static void dbgTextImage(@Unsigned short _x, @Unsigned short _y, @Unsigned short _width, @Unsigned short _height, MemorySegment _data, @Unsigned short _pitch) {
		try {
			MH_DBG_TEXT_IMAGE.invokeExact(_x, _y, _width, _height, address(_data), _pitch);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Create static index buffer.
	 * @param _mem Index buffer data.
	 * @param _flags Buffer creation flags.   - {@code BGFX_BUFFER_NONE} - No flags.   - {@code BGFX_BUFFER_COMPUTE_READ} - Buffer will be read from by compute shader.   - {@code BGFX_BUFFER_COMPUTE_WRITE} - Buffer will be written into by compute shader. When buffer       is created with {@code BGFX_BUFFER_COMPUTE_WRITE} flag it cannot be updated from CPU.   - {@code BGFX_BUFFER_COMPUTE_READ_WRITE} - Buffer will be used for read/write by compute shader.   - {@code BGFX_BUFFER_ALLOW_RESIZE} - Buffer will resize on buffer update if a different amount of       data is passed. If this flag is not specified, and more data is passed on update, the buffer       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic       buffers.   - {@code BGFX_BUFFER_INDEX32} - Buffer is using 32-bit indices. This flag has effect only on       index buffers.
	 * @return the native function result
	 */
	public static IndexBufferHandle createIndexBuffer(Memory _mem, @Unsigned short _flags) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				return IndexBufferHandle.read((MemorySegment) MH_CREATE_INDEX_BUFFER.invokeExact((SegmentAllocator) arena, address(_mem), _flags));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Read back contents of buffer.
	 * <p>
	 * <strong>Remarks:</strong> 
	 *   Read back is asynchronous, and the result is available at the returned frame.
	 *   A zero {@code size} reads the rest of the buffer. {@code rowPitch} and {@code slicePitch} are
	 *   unused.
	 * <p>
	 *   Read back is intended for reading GPU written (compute, or draw indirect) buffers
	 *   back to the CPU. It's not intended to be used in the main render loop, since it
	 *   stalls the GPU.
	 * <p>
	 * <strong>Attention:</strong> Buffer must be created with one of {@code BGFX_BUFFER_COMPUTE_*}, or
	 *   {@code BGFX_BUFFER_DRAW_INDIRECT} flags.
	 * @param _src Source buffer region.
	 * @param _data Destination buffer.
	 * @return Frame number when the result will be available. See: {@code frame}.
	 */
	public static @Unsigned int readBuffer(BufferRegion _src, MemorySegment _data) {
		try {
			return (@Unsigned int) MH_READ_BUFFER.invokeExact(address(_src), address(_data));
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set static index buffer debug name.
	 * @param _handle Static index buffer handle.
	 * @param _name Static index buffer name.
	 * @param _len Static index buffer name length (if length is INT32_MAX, it's expected that _name is zero terminated string.
	 */
	public static void setIndexBufferName(IndexBufferHandle _handle, String _name, int _len) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SET_INDEX_BUFFER_NAME.invokeExact(_handle.allocate(arena), cString(arena, _name), _len);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Destroy static index buffer.
	 * @param _handle Static index buffer handle.
	 */
	public static void destroyIndexBuffer(IndexBufferHandle _handle) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_DESTROY_INDEX_BUFFER.invokeExact(_handle.allocate(arena));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Create vertex layout. Vertex layouts are used to describe the format of vertex data.
	 * @param _layout Vertex layout.
	 * @return the native function result
	 */
	public static VertexLayoutHandle createVertexLayout(VertexLayout _layout) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				return VertexLayoutHandle.read((MemorySegment) MH_CREATE_VERTEX_LAYOUT.invokeExact((SegmentAllocator) arena, address(_layout)));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Destroy vertex layout.
	 * @param _layoutHandle Vertex layout handle.
	 */
	public static void destroyVertexLayout(VertexLayoutHandle _layoutHandle) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_DESTROY_VERTEX_LAYOUT.invokeExact(_layoutHandle.allocate(arena));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Create static vertex buffer.
	 * @param _mem Vertex buffer data.
	 * @param _layout Vertex layout.
	 * @param _flags Buffer creation flags.  - {@code BGFX_BUFFER_NONE} - No flags.  - {@code BGFX_BUFFER_COMPUTE_READ} - Buffer will be read from by compute shader.  - {@code BGFX_BUFFER_COMPUTE_WRITE} - Buffer will be written into by compute shader. When buffer      is created with {@code BGFX_BUFFER_COMPUTE_WRITE} flag it cannot be updated from CPU.  - {@code BGFX_BUFFER_COMPUTE_READ_WRITE} - Buffer will be used for read/write by compute shader.  - {@code BGFX_BUFFER_ALLOW_RESIZE} - Buffer will resize on buffer update if a different amount of      data is passed. If this flag is not specified, and more data is passed on update, the buffer      will be trimmed to fit the existing buffer size. This flag has effect only on dynamic buffers.  - {@code BGFX_BUFFER_INDEX32} - Buffer is using 32-bit indices. This flag has effect only on index buffers.
	 * @return Static vertex buffer handle.
	 */
	public static VertexBufferHandle createVertexBuffer(Memory _mem, VertexLayout _layout, @Unsigned short _flags) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				return VertexBufferHandle.read((MemorySegment) MH_CREATE_VERTEX_BUFFER.invokeExact((SegmentAllocator) arena, address(_mem), address(_layout), _flags));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set static vertex buffer debug name.
	 * @param _handle Static vertex buffer handle.
	 * @param _name Static vertex buffer name.
	 * @param _len Static vertex buffer name length (if length is INT32_MAX, it's expected that _name is zero terminated string.
	 */
	public static void setVertexBufferName(VertexBufferHandle _handle, String _name, int _len) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SET_VERTEX_BUFFER_NAME.invokeExact(_handle.allocate(arena), cString(arena, _name), _len);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Destroy static vertex buffer.
	 * @param _handle Static vertex buffer handle.
	 */
	public static void destroyVertexBuffer(VertexBufferHandle _handle) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_DESTROY_VERTEX_BUFFER.invokeExact(_handle.allocate(arena));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Create empty dynamic index buffer.
	 * @param _num Number of indices.
	 * @param _flags Buffer creation flags.   - {@code BGFX_BUFFER_NONE} - No flags.   - {@code BGFX_BUFFER_COMPUTE_READ} - Buffer will be read from by compute shader.   - {@code BGFX_BUFFER_COMPUTE_WRITE} - Buffer will be written into by compute shader. When buffer       is created with {@code BGFX_BUFFER_COMPUTE_WRITE} flag it cannot be updated from CPU.   - {@code BGFX_BUFFER_COMPUTE_READ_WRITE} - Buffer will be used for read/write by compute shader.   - {@code BGFX_BUFFER_ALLOW_RESIZE} - Buffer will resize on buffer update if a different amount of       data is passed. If this flag is not specified, and more data is passed on update, the buffer       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic       buffers.   - {@code BGFX_BUFFER_INDEX32} - Buffer is using 32-bit indices. This flag has effect only on       index buffers.
	 * @return Dynamic index buffer handle.
	 */
	public static DynamicIndexBufferHandle createDynamicIndexBuffer(@Unsigned int _num, @Unsigned short _flags) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				return DynamicIndexBufferHandle.read((MemorySegment) MH_CREATE_DYNAMIC_INDEX_BUFFER.invokeExact((SegmentAllocator) arena, _num, _flags));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Create a dynamic index buffer and initialize it.
	 * @param _mem Index buffer data.
	 * @param _flags Buffer creation flags.   - {@code BGFX_BUFFER_NONE} - No flags.   - {@code BGFX_BUFFER_COMPUTE_READ} - Buffer will be read from by compute shader.   - {@code BGFX_BUFFER_COMPUTE_WRITE} - Buffer will be written into by compute shader. When buffer       is created with {@code BGFX_BUFFER_COMPUTE_WRITE} flag it cannot be updated from CPU.   - {@code BGFX_BUFFER_COMPUTE_READ_WRITE} - Buffer will be used for read/write by compute shader.   - {@code BGFX_BUFFER_ALLOW_RESIZE} - Buffer will resize on buffer update if a different amount of       data is passed. If this flag is not specified, and more data is passed on update, the buffer       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic       buffers.   - {@code BGFX_BUFFER_INDEX32} - Buffer is using 32-bit indices. This flag has effect only on       index buffers.
	 * @return Dynamic index buffer handle.
	 */
	public static DynamicIndexBufferHandle createDynamicIndexBufferMem(Memory _mem, @Unsigned short _flags) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				return DynamicIndexBufferHandle.read((MemorySegment) MH_CREATE_DYNAMIC_INDEX_BUFFER_MEM.invokeExact((SegmentAllocator) arena, address(_mem), _flags));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Update dynamic index buffer.
	 * @param _handle Dynamic index buffer handle.
	 * @param _startIndex Start index.
	 * @param _mem Index buffer data.
	 */
	public static void updateDynamicIndexBuffer(DynamicIndexBufferHandle _handle, @Unsigned int _startIndex, Memory _mem) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_UPDATE_DYNAMIC_INDEX_BUFFER.invokeExact(_handle.allocate(arena), _startIndex, address(_mem));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Destroy dynamic index buffer.
	 * @param _handle Dynamic index buffer handle.
	 */
	public static void destroyDynamicIndexBuffer(DynamicIndexBufferHandle _handle) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_DESTROY_DYNAMIC_INDEX_BUFFER.invokeExact(_handle.allocate(arena));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Create empty dynamic vertex buffer.
	 * @param _num Number of vertices.
	 * @param _layout Vertex layout.
	 * @param _flags Buffer creation flags.   - {@code BGFX_BUFFER_NONE} - No flags.   - {@code BGFX_BUFFER_COMPUTE_READ} - Buffer will be read from by compute shader.   - {@code BGFX_BUFFER_COMPUTE_WRITE} - Buffer will be written into by compute shader. When buffer       is created with {@code BGFX_BUFFER_COMPUTE_WRITE} flag it cannot be updated from CPU.   - {@code BGFX_BUFFER_COMPUTE_READ_WRITE} - Buffer will be used for read/write by compute shader.   - {@code BGFX_BUFFER_ALLOW_RESIZE} - Buffer will resize on buffer update if a different amount of       data is passed. If this flag is not specified, and more data is passed on update, the buffer       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic       buffers.   - {@code BGFX_BUFFER_INDEX32} - Buffer is using 32-bit indices. This flag has effect only on       index buffers.
	 * @return Dynamic vertex buffer handle.
	 */
	public static DynamicVertexBufferHandle createDynamicVertexBuffer(@Unsigned int _num, VertexLayout _layout, @Unsigned short _flags) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				return DynamicVertexBufferHandle.read((MemorySegment) MH_CREATE_DYNAMIC_VERTEX_BUFFER.invokeExact((SegmentAllocator) arena, _num, address(_layout), _flags));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Create dynamic vertex buffer and initialize it.
	 * @param _mem Vertex buffer data.
	 * @param _layout Vertex layout.
	 * @param _flags Buffer creation flags.   - {@code BGFX_BUFFER_NONE} - No flags.   - {@code BGFX_BUFFER_COMPUTE_READ} - Buffer will be read from by compute shader.   - {@code BGFX_BUFFER_COMPUTE_WRITE} - Buffer will be written into by compute shader. When buffer       is created with {@code BGFX_BUFFER_COMPUTE_WRITE} flag it cannot be updated from CPU.   - {@code BGFX_BUFFER_COMPUTE_READ_WRITE} - Buffer will be used for read/write by compute shader.   - {@code BGFX_BUFFER_ALLOW_RESIZE} - Buffer will resize on buffer update if a different amount of       data is passed. If this flag is not specified, and more data is passed on update, the buffer       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic       buffers.   - {@code BGFX_BUFFER_INDEX32} - Buffer is using 32-bit indices. This flag has effect only on       index buffers.
	 * @return Dynamic vertex buffer handle.
	 */
	public static DynamicVertexBufferHandle createDynamicVertexBufferMem(Memory _mem, VertexLayout _layout, @Unsigned short _flags) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				return DynamicVertexBufferHandle.read((MemorySegment) MH_CREATE_DYNAMIC_VERTEX_BUFFER_MEM.invokeExact((SegmentAllocator) arena, address(_mem), address(_layout), _flags));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Update dynamic vertex buffer.
	 * @param _handle Dynamic vertex buffer handle.
	 * @param _startVertex Start vertex.
	 * @param _mem Vertex buffer data.
	 */
	public static void updateDynamicVertexBuffer(DynamicVertexBufferHandle _handle, @Unsigned int _startVertex, Memory _mem) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_UPDATE_DYNAMIC_VERTEX_BUFFER.invokeExact(_handle.allocate(arena), _startVertex, address(_mem));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Destroy dynamic vertex buffer.
	 * @param _handle Dynamic vertex buffer handle.
	 */
	public static void destroyDynamicVertexBuffer(DynamicVertexBufferHandle _handle) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_DESTROY_DYNAMIC_VERTEX_BUFFER.invokeExact(_handle.allocate(arena));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Returns number of requested or maximum available indices.
	 * @param _num Number of required indices.
	 * @param _index32 Set to {@code true} if input indices will be 32-bit.
	 * @return Number of requested or maximum available indices.
	 */
	public static @Unsigned int getAvailTransientIndexBuffer(@Unsigned int _num, boolean _index32) {
		try {
			return (@Unsigned int) MH_GET_AVAIL_TRANSIENT_INDEX_BUFFER.invokeExact(_num, _index32);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Returns number of requested or maximum available vertices.
	 * @param _num Number of required vertices.
	 * @param _layout Vertex layout.
	 * @return Number of requested or maximum available vertices.
	 */
	public static @Unsigned int getAvailTransientVertexBuffer(@Unsigned int _num, VertexLayout _layout) {
		try {
			return (@Unsigned int) MH_GET_AVAIL_TRANSIENT_VERTEX_BUFFER.invokeExact(_num, address(_layout));
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Returns number of requested or maximum available instance buffer slots.
	 * @param _num Number of required instances.
	 * @param _stride Stride per instance.
	 * @return Number of requested or maximum available instance buffer slots.
	 */
	public static @Unsigned int getAvailInstanceDataBuffer(@Unsigned int _num, @Unsigned short _stride) {
		try {
			return (@Unsigned int) MH_GET_AVAIL_INSTANCE_DATA_BUFFER.invokeExact(_num, _stride);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Allocate transient index buffer.
	 * @param _tib TransientIndexBuffer structure will be filled, and will be valid for the duration of frame, and can be reused for multiple draw calls.
	 * @param _num Number of indices to allocate.
	 * @param _index32 Set to {@code true} if input indices will be 32-bit.
	 */
	public static void allocTransientIndexBuffer(TransientIndexBuffer _tib, @Unsigned int _num, boolean _index32) {
		try {
			MH_ALLOC_TRANSIENT_INDEX_BUFFER.invokeExact(address(_tib), _num, _index32);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Allocate transient vertex buffer.
	 * @param _tvb TransientVertexBuffer structure will be filled, and will be valid for the duration of frame, and can be reused for multiple draw calls.
	 * @param _num Number of vertices to allocate.
	 * @param _layout Vertex layout.
	 */
	public static void allocTransientVertexBuffer(TransientVertexBuffer _tvb, @Unsigned int _num, VertexLayout _layout) {
		try {
			MH_ALLOC_TRANSIENT_VERTEX_BUFFER.invokeExact(address(_tvb), _num, address(_layout));
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Check for required space and allocate transient vertex and index
	 * buffers. If both space requirements are satisfied function returns
	 * true.
	 * @param _tvb TransientVertexBuffer structure will be filled, and will be valid for the duration of frame, and can be reused for multiple draw calls.
	 * @param _layout Vertex layout.
	 * @param _numVertices Number of vertices to allocate.
	 * @param _tib TransientIndexBuffer structure will be filled, and will be valid for the duration of frame, and can be reused for multiple draw calls.
	 * @param _numIndices Number of indices to allocate.
	 * @param _index32 Set to {@code true} if input indices will be 32-bit.
	 * @return the native function result
	 */
	public static boolean allocTransientBuffers(TransientVertexBuffer _tvb, VertexLayout _layout, @Unsigned int _numVertices, TransientIndexBuffer _tib, @Unsigned int _numIndices, boolean _index32) {
		try {
			return (boolean) MH_ALLOC_TRANSIENT_BUFFERS.invokeExact(address(_tvb), address(_layout), _numVertices, address(_tib), _numIndices, _index32);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Allocate instance data buffer.
	 * @param _idb InstanceDataBuffer structure will be filled, and will be valid for duration of frame, and can be reused for multiple draw calls.
	 * @param _num Number of instances.
	 * @param _stride Instance stride. Must be multiple of 16.
	 */
	public static void allocInstanceDataBuffer(InstanceDataBuffer _idb, @Unsigned int _num, @Unsigned short _stride) {
		try {
			MH_ALLOC_INSTANCE_DATA_BUFFER.invokeExact(address(_idb), _num, _stride);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Create draw indirect buffer.
	 * @param _num Number of indirect calls.
	 * @return Indirect buffer handle.
	 */
	public static IndirectBufferHandle createIndirectBuffer(@Unsigned int _num) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				return IndirectBufferHandle.read((MemorySegment) MH_CREATE_INDIRECT_BUFFER.invokeExact((SegmentAllocator) arena, _num));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Destroy draw indirect buffer.
	 * @param _handle Indirect buffer handle.
	 */
	public static void destroyIndirectBuffer(IndirectBufferHandle _handle) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_DESTROY_INDIRECT_BUFFER.invokeExact(_handle.allocate(arena));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Create shader from memory buffer.
	 * <p>
	 * <strong>Remarks:</strong> 
	 *   Shader binary is obtained by compiling shader offline with shaderc command line tool.
	 * @param _mem Shader binary.
	 * @return Shader handle.
	 */
	public static ShaderHandle createShader(Memory _mem) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				return ShaderHandle.read((MemorySegment) MH_CREATE_SHADER.invokeExact((SegmentAllocator) arena, address(_mem)));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Returns the number of uniforms and uniform handles used inside a shader.
	 * <p>
	 * <strong>Remarks:</strong> 
	 *   Only non-predefined uniforms are returned.
	 * @param _handle Shader handle.
	 * @param _uniforms UniformHandle array where data will be stored.
	 * @param _max Maximum capacity of array.
	 * @return Number of uniforms used by shader.
	 */
	public static @Unsigned short getShaderUniforms(ShaderHandle _handle, @Nullable MemorySegment _uniforms, @Unsigned short _max) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				return (@Unsigned short) MH_GET_SHADER_UNIFORMS.invokeExact(_handle.allocate(arena), address(_uniforms), _max);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set shader debug name.
	 * @param _handle Shader handle.
	 * @param _name Shader name.
	 * @param _len Shader name length (if length is INT32_MAX, it's expected that _name is zero terminated string).
	 */
	public static void setShaderName(ShaderHandle _handle, String _name, int _len) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SET_SHADER_NAME.invokeExact(_handle.allocate(arena), cString(arena, _name), _len);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Destroy shader.
	 * <p>
	 * <strong>Remarks:</strong> Once a shader program is created with _handle,
	 *   it is safe to destroy that shader.
	 * @param _handle Shader handle.
	 */
	public static void destroyShader(ShaderHandle _handle) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_DESTROY_SHADER.invokeExact(_handle.allocate(arena));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Create program with vertex and fragment shaders.
	 * @param _vsh Vertex shader.
	 * @param _fsh Fragment shader.
	 * @param _destroyShaders If true, shaders will be destroyed when program is destroyed.
	 * @return Program handle if vertex shader output and fragment shader input are matching, otherwise returns invalid program handle.
	 */
	public static ProgramHandle createProgram(ShaderHandle _vsh, ShaderHandle _fsh, boolean _destroyShaders) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				return ProgramHandle.read((MemorySegment) MH_CREATE_PROGRAM.invokeExact((SegmentAllocator) arena, _vsh.allocate(arena), _fsh.allocate(arena), _destroyShaders));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Create program with compute shader.
	 * @param _csh Compute shader.
	 * @param _destroyShaders If true, shaders will be destroyed when program is destroyed.
	 * @return Program handle.
	 */
	public static ProgramHandle createComputeProgram(ShaderHandle _csh, boolean _destroyShaders) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				return ProgramHandle.read((MemorySegment) MH_CREATE_COMPUTE_PROGRAM.invokeExact((SegmentAllocator) arena, _csh.allocate(arena), _destroyShaders));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Destroy program.
	 * @param _handle Program handle.
	 */
	public static void destroyProgram(ProgramHandle _handle) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_DESTROY_PROGRAM.invokeExact(_handle.allocate(arena));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Validate texture parameters.
	 * @param _depth Depth dimension of volume texture.
	 * @param _cubeMap Indicates that texture contains cubemap.
	 * @param _numLayers Number of layers in texture array.
	 * @param _format Texture format. See: {@code TextureFormat}.
	 * @param _flags Texture flags. See {@code BGFX_TEXTURE_*}.
	 * @return True if a texture with the same parameters can be created.
	 */
	public static boolean isTextureValid(@Unsigned short _depth, boolean _cubeMap, @Unsigned short _numLayers, TextureFormat _format, @Unsigned long _flags) {
		try {
			return (boolean) MH_IS_TEXTURE_VALID.invokeExact(_depth, _cubeMap, _numLayers, _format.ordinal(), _flags);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Validate video codec parameters. Use to check whether the requested
	 * combination of codec / bit depth / chroma / dimensions / DPB layout can
	 * be hardware decoded on the current device. Coarse capability discovery
	 * is {@code Caps.supported &amp; BGFX_CAPS_VIDEO_DECODE} and {@code Caps.codecs[]}.
	 * @param _codec Video codec. See: {@code VideoCodec}.
	 * @param _chroma Chroma subsampling. 0 = 4:2:0, 2 = 4:2:2, 4 = 4:4:4.
	 * @param _bitDepth Bit depth per component. 8, 10 or 12.
	 * @param _codedWidth Coded picture width (macroblock / CTU / superblock aligned).
	 * @param _codedHeight Coded picture height.
	 * @param _maxDpbSlots Maximum decoded picture buffer slot count.
	 * @param _maxActiveReferences Maximum number of reference frames active at once.
	 * @return True if a video decoder with the same parameters can be created.
	 */
	public static boolean isVideoCodecValid(VideoCodec _codec, @Unsigned byte _chroma, @Unsigned byte _bitDepth, @Unsigned short _codedWidth, @Unsigned short _codedHeight, @Unsigned byte _maxDpbSlots, @Unsigned byte _maxActiveReferences) {
		try {
			return (boolean) MH_IS_VIDEO_CODEC_VALID.invokeExact(_codec.ordinal(), _chroma, _bitDepth, _codedWidth, _codedHeight, _maxDpbSlots, _maxActiveReferences);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Validate frame buffer parameters.
	 * @param _num Number of attachments.
	 * @param _attachment Attachment texture info. See: {@code Attachment}.
	 * @return True if a frame buffer with the same parameters can be created.
	 */
	public static boolean isFrameBufferValid(@Unsigned byte _num, Attachment _attachment) {
		try {
			return (boolean) MH_IS_FRAME_BUFFER_VALID.invokeExact(_num, address(_attachment));
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Calculate amount of memory required for texture.
	 * @param _info Resulting texture info structure. See: {@code TextureInfo}.
	 * @param _width Width.
	 * @param _height Height.
	 * @param _depth Depth dimension of volume texture.
	 * @param _cubeMap Indicates that texture contains cubemap.
	 * @param _hasMips Indicates that texture contains full mip-map chain.
	 * @param _numLayers Number of layers in texture array.
	 * @param _format Texture format. See: {@code TextureFormat}.
	 */
	public static void calcTextureSize(TextureInfo _info, @Unsigned short _width, @Unsigned short _height, @Unsigned short _depth, boolean _cubeMap, boolean _hasMips, @Unsigned short _numLayers, TextureFormat _format) {
		try {
			MH_CALC_TEXTURE_SIZE.invokeExact(address(_info), _width, _height, _depth, _cubeMap, _hasMips, _numLayers, _format.ordinal());
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Create texture from memory buffer.
	 * @param _mem DDS, KTX or PVR texture binary data.
	 * @param _flags Texture creation (see {@code BGFX_TEXTURE_*}.), and sampler (see {@code BGFX_SAMPLER_*}) flags. Default texture sampling mode is linear, and wrap mode is repeat. - {@code BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]} - Mirror or clamp to edge wrap   mode. - {@code BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]} - Point or anisotropic   sampling.
	 * @param _skip Skip top level mips when parsing texture.
	 * @param _info When non-{@code NULL} is specified it returns parsed texture information.
	 * @return Texture handle.
	 */
	public static TextureHandle createTexture(Memory _mem, @Unsigned long _flags, @Unsigned byte _skip, @Nullable TextureInfo _info) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				return TextureHandle.read((MemorySegment) MH_CREATE_TEXTURE.invokeExact((SegmentAllocator) arena, address(_mem), _flags, _skip, address(_info)));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Create 2D texture.
	 * @param _width Width.
	 * @param _height Height.
	 * @param _hasMips Indicates that texture contains full mip-map chain.
	 * @param _numLayers Number of layers in texture array.
	 * @param _format Texture format. See: {@code TextureFormat}.
	 * @param _flags Texture creation (see {@code BGFX_TEXTURE_*}.), and sampler (see {@code BGFX_SAMPLER_*}) flags. Default texture sampling mode is linear, and wrap mode is repeat. - {@code BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]} - Mirror or clamp to edge wrap   mode. - {@code BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]} - Point or anisotropic   sampling.
	 * @param _mem Texture data. If {@code _mem} is non-NULL, created texture will be immutable. If {@code _mem} is NULL content of the texture is uninitialized. When {@code _numLayers} is more than 1, expected memory layout is texture and all mips together for each array element.
	 * @param _external Native API pointer to texture.
	 * @return Texture handle.
	 */
	public static TextureHandle createTexture2D(@Unsigned short _width, @Unsigned short _height, boolean _hasMips, @Unsigned short _numLayers, TextureFormat _format, @Unsigned long _flags, @Nullable Memory _mem, @Unsigned long _external) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				return TextureHandle.read((MemorySegment) MH_CREATE_TEXTURE_2D.invokeExact((SegmentAllocator) arena, _width, _height, _hasMips, _numLayers, _format.ordinal(), _flags, address(_mem), _external));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Create texture with size based on back-buffer ratio. Texture will maintain ratio
	 * if back buffer resolution changes.
	 * @param _ratio Texture size in respect to back-buffer size. See: {@code BackbufferRatio}.
	 * @param _hasMips Indicates that texture contains full mip-map chain.
	 * @param _numLayers Number of layers in texture array.
	 * @param _format Texture format. See: {@code TextureFormat}.
	 * @param _flags Texture creation (see {@code BGFX_TEXTURE_*}.), and sampler (see {@code BGFX_SAMPLER_*}) flags. Default texture sampling mode is linear, and wrap mode is repeat. - {@code BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]} - Mirror or clamp to edge wrap   mode. - {@code BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]} - Point or anisotropic   sampling.
	 * @return Texture handle.
	 */
	public static TextureHandle createTexture2DScaled(BackbufferRatio _ratio, boolean _hasMips, @Unsigned short _numLayers, TextureFormat _format, @Unsigned long _flags) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				return TextureHandle.read((MemorySegment) MH_CREATE_TEXTURE_2D_SCALED.invokeExact((SegmentAllocator) arena, _ratio.ordinal(), _hasMips, _numLayers, _format.ordinal(), _flags));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Create 3D texture.
	 * @param _width Width.
	 * @param _height Height.
	 * @param _depth Depth.
	 * @param _hasMips Indicates that texture contains full mip-map chain.
	 * @param _format Texture format. See: {@code TextureFormat}.
	 * @param _flags Texture creation (see {@code BGFX_TEXTURE_*}.), and sampler (see {@code BGFX_SAMPLER_*}) flags. Default texture sampling mode is linear, and wrap mode is repeat. - {@code BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]} - Mirror or clamp to edge wrap   mode. - {@code BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]} - Point or anisotropic   sampling.
	 * @param _mem Texture data. If {@code _mem} is non-NULL, created texture will be immutable. If {@code _mem} is NULL content of the texture is uninitialized. When {@code _numLayers} is more than 1, expected memory layout is texture and all mips together for each array element.
	 * @param _external Native API pointer to texture.
	 * @return Texture handle.
	 */
	public static TextureHandle createTexture3D(@Unsigned short _width, @Unsigned short _height, @Unsigned short _depth, boolean _hasMips, TextureFormat _format, @Unsigned long _flags, @Nullable Memory _mem, @Unsigned long _external) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				return TextureHandle.read((MemorySegment) MH_CREATE_TEXTURE_3D.invokeExact((SegmentAllocator) arena, _width, _height, _depth, _hasMips, _format.ordinal(), _flags, address(_mem), _external));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Create Cube texture.
	 * @param _size Cube side size.
	 * @param _hasMips Indicates that texture contains full mip-map chain.
	 * @param _numLayers Number of layers in texture array.
	 * @param _format Texture format. See: {@code TextureFormat}.
	 * @param _flags Texture creation (see {@code BGFX_TEXTURE_*}.), and sampler (see {@code BGFX_SAMPLER_*}) flags. Default texture sampling mode is linear, and wrap mode is repeat. - {@code BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]} - Mirror or clamp to edge wrap   mode. - {@code BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]} - Point or anisotropic   sampling.
	 * @param _mem Texture data. If {@code _mem} is non-NULL, created texture will be immutable. If {@code _mem} is NULL content of the texture is uninitialized. When {@code _numLayers} is more than
	 * @param _external Native API pointer to texture.
	 * @return Texture handle.
	 */
	public static TextureHandle createTextureCube(@Unsigned short _size, boolean _hasMips, @Unsigned short _numLayers, TextureFormat _format, @Unsigned long _flags, @Nullable Memory _mem, @Unsigned long _external) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				return TextureHandle.read((MemorySegment) MH_CREATE_TEXTURE_CUBE.invokeExact((SegmentAllocator) arena, _size, _hasMips, _numLayers, _format.ordinal(), _flags, address(_mem), _external));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Update 2D texture.
	 * <p>
	 * <strong>Attention:</strong> It's valid to update only mutable texture. See {@code createTexture2D} for more info.
	 * @param _handle Texture handle.
	 * @param _layer Layer in texture array.
	 * @param _mip Mip level.
	 * @param _x X offset in texture.
	 * @param _y Y offset in texture.
	 * @param _width Width of texture block.
	 * @param _height Height of texture block.
	 * @param _mem Texture update data.
	 * @param _pitch Pitch of input image (bytes). When _pitch is set to UINT16_MAX, it will be calculated internally based on _width.
	 */
	public static void updateTexture2D(TextureHandle _handle, @Unsigned short _layer, @Unsigned byte _mip, @Unsigned short _x, @Unsigned short _y, @Unsigned short _width, @Unsigned short _height, Memory _mem, @Unsigned short _pitch) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_UPDATE_TEXTURE_2D.invokeExact(_handle.allocate(arena), _layer, _mip, _x, _y, _width, _height, address(_mem), _pitch);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Update 3D texture.
	 * <p>
	 * <strong>Attention:</strong> It's valid to update only mutable texture. See {@code createTexture3D} for more info.
	 * @param _handle Texture handle.
	 * @param _mip Mip level.
	 * @param _x X offset in texture.
	 * @param _y Y offset in texture.
	 * @param _z Z offset in texture.
	 * @param _width Width of texture block.
	 * @param _height Height of texture block.
	 * @param _depth Depth of texture block.
	 * @param _mem Texture update data.
	 */
	public static void updateTexture3D(TextureHandle _handle, @Unsigned byte _mip, @Unsigned short _x, @Unsigned short _y, @Unsigned short _z, @Unsigned short _width, @Unsigned short _height, @Unsigned short _depth, Memory _mem) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_UPDATE_TEXTURE_3D.invokeExact(_handle.allocate(arena), _mip, _x, _y, _z, _width, _height, _depth, address(_mem));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Update Cube texture.
	 * <p>
	 * <strong>Attention:</strong> It's valid to update only mutable texture. See {@code createTextureCube} for more info.
	 * @param _handle Texture handle.
	 * @param _layer Layer in texture array.
	 * @param _side Cubemap side {@code BGFX_CUBE_MAP_&lt;POSITIVE or NEGATIVE&gt;_&lt;X, Y or Z&gt;},   where 0 is +X, 1 is -X, 2 is +Y, 3 is -Y, 4 is +Z, and 5 is -Z.                  +----------+                  |-z       2|                  | ^  +y    |                  | |        |    Unfolded cube:                  | +----&gt;+x |       +----------+----------+----------+----------+       |+y       1|+y       4|+y       0|+y       5|       | ^  -x    | ^  +z    | ^  +x    | ^  -z    |       | |        | |        | |        | |        |       | +----&gt;+z | +----&gt;+x | +----&gt;-z | +----&gt;-x |       +----------+----------+----------+----------+                  |+z       3|                  | ^  -y    |                  | |        |                  | +----&gt;+x |                  +----------+
	 * @param _mip Mip level.
	 * @param _x X offset in texture.
	 * @param _y Y offset in texture.
	 * @param _width Width of texture block.
	 * @param _height Height of texture block.
	 * @param _mem Texture update data.
	 * @param _pitch Pitch of input image (bytes). When _pitch is set to UINT16_MAX, it will be calculated internally based on _width.
	 */
	public static void updateTextureCube(TextureHandle _handle, @Unsigned short _layer, @Unsigned byte _side, @Unsigned byte _mip, @Unsigned short _x, @Unsigned short _y, @Unsigned short _width, @Unsigned short _height, Memory _mem, @Unsigned short _pitch) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_UPDATE_TEXTURE_CUBE.invokeExact(_handle.allocate(arena), _layer, _side, _mip, _x, _y, _width, _height, address(_mem), _pitch);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Clear a texture subresource range to zero.
	 * @param _handle Texture handle.
	 * @param _mip First mip level.
	 * @param _numMips Number of mip levels.
	 * @param _layer First array layer (or 3D depth slice base).
	 * @param _numLayers Number of layers.
	 */
	public static void clearTexture(TextureHandle _handle, @Unsigned byte _mip, @Unsigned byte _numMips, @Unsigned short _layer, @Unsigned short _numLayers) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_CLEAR_TEXTURE.invokeExact(_handle.allocate(arena), _mip, _numMips, _layer, _numLayers);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Read back texture content.
	 * <p>
	 * <strong>Remarks:</strong> 
	 *   Read back is asynchronous, and the result is available at the returned frame.
	 *   {@code TextureRegion.z} selects cube face, 3D slice, or array layer. The region must
	 *   cover the whole mip.
	 * <p>
	 *   Read back is not intended to be used in the main render loop, since it stalls
	 *   the GPU.
	 * <p>
	 * <strong>Attention:</strong> Texture must be created with {@code BGFX_TEXTURE_READ_BACK} flag.
	 *            It's a texture for CPU readback, and can't be a GPU resource
	 *            at the same time. See {@code examples/30-picking}.
	 * @param _src Source texture region.
	 * @param _data Destination buffer.
	 * @return Frame number when the result will be available. See: {@code frame}.
	 */
	public static @Unsigned int readTexture(TextureRegion _src, MemorySegment _data) {
		try {
			return (@Unsigned int) MH_READ_TEXTURE.invokeExact(address(_src), address(_data));
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set texture debug name.
	 * @param _handle Texture handle.
	 * @param _name Texture name.
	 * @param _len Texture name length (if length is INT32_MAX, it's expected that _name is zero terminated string.
	 */
	public static void setTextureName(TextureHandle _handle, String _name, int _len) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SET_TEXTURE_NAME.invokeExact(_handle.allocate(arena), cString(arena, _name), _len);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Returns texture direct access pointer.
	 * <p>
	 * <strong>Attention:</strong> Availability depends on: {@code BGFX_CAPS_TEXTURE_DIRECT_ACCESS}. This feature
	 *   is available on GPUs that have unified memory architecture (UMA) support.
	 * @param _handle Texture handle.
	 * @return Pointer to texture memory. If returned pointer is {@code NULL} direct access is not available for this texture. If pointer is {@code UINTPTR_MAX} sentinel value it means texture is pending creation. Pointer returned can be cached and it will be valid until texture is destroyed.
	 */
	public static MemorySegment getDirectAccessPtr(TextureHandle _handle) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				return address((MemorySegment) MH_GET_DIRECT_ACCESS_PTR.invokeExact(_handle.allocate(arena)));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Destroy texture.
	 * @param _handle Texture handle.
	 */
	public static void destroyTexture(TextureHandle _handle) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_DESTROY_TEXTURE.invokeExact(_handle.allocate(arena));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Create frame buffer (simple).
	 * @param _width Texture width.
	 * @param _height Texture height.
	 * @param _format Texture format. See: {@code TextureFormat}.
	 * @param _textureFlags Texture creation (see {@code BGFX_TEXTURE_*}.), and sampler (see {@code BGFX_SAMPLER_*}) flags. Default texture sampling mode is linear, and wrap mode is repeat. - {@code BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]} - Mirror or clamp to edge wrap   mode. - {@code BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]} - Point or anisotropic   sampling.
	 * @return Frame buffer handle.
	 */
	public static FrameBufferHandle createFrameBuffer(@Unsigned short _width, @Unsigned short _height, TextureFormat _format, @Unsigned long _textureFlags) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				return FrameBufferHandle.read((MemorySegment) MH_CREATE_FRAME_BUFFER.invokeExact((SegmentAllocator) arena, _width, _height, _format.ordinal(), _textureFlags));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Create frame buffer with size based on back-buffer ratio. Frame buffer will maintain ratio
	 * if back buffer resolution changes.
	 * @param _ratio Frame buffer size in respect to back-buffer size. See: {@code BackbufferRatio}.
	 * @param _format Texture format. See: {@code TextureFormat}.
	 * @param _textureFlags Texture creation (see {@code BGFX_TEXTURE_*}.), and sampler (see {@code BGFX_SAMPLER_*}) flags. Default texture sampling mode is linear, and wrap mode is repeat. - {@code BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]} - Mirror or clamp to edge wrap   mode. - {@code BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]} - Point or anisotropic   sampling.
	 * @return Frame buffer handle.
	 */
	public static FrameBufferHandle createFrameBufferScaled(BackbufferRatio _ratio, TextureFormat _format, @Unsigned long _textureFlags) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				return FrameBufferHandle.read((MemorySegment) MH_CREATE_FRAME_BUFFER_SCALED.invokeExact((SegmentAllocator) arena, _ratio.ordinal(), _format.ordinal(), _textureFlags));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Create MRT frame buffer from texture handles (simple).
	 * @param _num Number of texture handles.
	 * @param _handles Texture attachments.
	 * @param _destroyTexture If true, textures will be destroyed when frame buffer is destroyed.
	 * @return Frame buffer handle.
	 */
	public static FrameBufferHandle createFrameBufferFromHandles(@Unsigned byte _num, MemorySegment _handles, boolean _destroyTexture) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				return FrameBufferHandle.read((MemorySegment) MH_CREATE_FRAME_BUFFER_FROM_HANDLES.invokeExact((SegmentAllocator) arena, _num, address(_handles), _destroyTexture));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Create MRT frame buffer from texture handles with specific layer and
	 * mip level.
	 * @param _num Number of attachments.
	 * @param _attachment Attachment texture info. See: {@code Attachment}.
	 * @param _destroyTexture If true, textures will be destroyed when frame buffer is destroyed.
	 * @return Frame buffer handle.
	 */
	public static FrameBufferHandle createFrameBufferFromAttachment(@Unsigned byte _num, Attachment _attachment, boolean _destroyTexture) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				return FrameBufferHandle.read((MemorySegment) MH_CREATE_FRAME_BUFFER_FROM_ATTACHMENT.invokeExact((SegmentAllocator) arena, _num, address(_attachment), _destroyTexture));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Create a frame buffer for a window, from a full swap chain description.
	 * <p>
	 * <strong>Remarks:</strong> 
	 *   Frame buffer cannot be used for sampling.
	 * <p>
	 * <strong>Attention:</strong> Availability depends on: {@code BGFX_CAPS_SWAP_CHAIN}.
	 * @param _desc Swap chain description. See: {@code SwapChain}.
	 * @return Frame buffer handle.
	 */
	public static FrameBufferHandle createFrameBufferFromSwapChain(SwapChain _desc) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				return FrameBufferHandle.read((MemorySegment) MH_CREATE_FRAME_BUFFER_FROM_SWAP_CHAIN.invokeExact((SegmentAllocator) arena, address(_desc)));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Change a swap chain's size, format or per-surface flags, in place.
	 * <p>
	 * The frame buffer handle stays valid, so nothing that refers to it has to be
	 * rebuilt. Pass {@code BGFX_INVALID_HANDLE} to address the window bgfx was
	 * initialized with.
	 * <p>
	 * <strong>Attention:</strong> Availability depends on: {@code BGFX_CAPS_SWAP_CHAIN}.
	 * @param _handle Window frame buffer handle. The window bgfx was initialized with is not addressed here; it is {@code reset}'s swap chain.
	 * @param _desc Swap chain description. See: {@code SwapChain}.
	 */
	public static void updateSwapChain(FrameBufferHandle _handle, SwapChain _desc) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_UPDATE_SWAP_CHAIN.invokeExact(_handle.allocate(arena), address(_desc));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set frame buffer debug name.
	 * @param _handle Frame buffer handle.
	 * @param _name Frame buffer name.
	 * @param _len Frame buffer name length (if length is INT32_MAX, it's expected that _name is zero terminated string.
	 */
	public static void setFrameBufferName(FrameBufferHandle _handle, String _name, int _len) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SET_FRAME_BUFFER_NAME.invokeExact(_handle.allocate(arena), cString(arena, _name), _len);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Obtain texture handle of frame buffer attachment.
	 * @param _handle Frame buffer handle.
	 * @param _attachment native function argument
	 * @return the native function result
	 */
	public static TextureHandle getTexture(FrameBufferHandle _handle, @Unsigned byte _attachment) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				return TextureHandle.read((MemorySegment) MH_GET_TEXTURE.invokeExact((SegmentAllocator) arena, _handle.allocate(arena), _attachment));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Destroy frame buffer.
	 * @param _handle Frame buffer handle.
	 */
	public static void destroyFrameBuffer(FrameBufferHandle _handle) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_DESTROY_FRAME_BUFFER.invokeExact(_handle.allocate(arena));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Create shader uniform parameter.
	 * <p>
	 * <strong>Remarks:</strong> 
	 *   1. Uniform names are unique. It's valid to call {@code createUniform}
	 *      multiple times with the same uniform name. The library will always
	 *      return the same handle, but the handle reference count will be
	 *      incremented. This means that the same number of {@code destroyUniform}
	 *      must be called to properly destroy the uniform.
	 * <p>
	 *   2. Predefined uniforms (declared in {@code bgfx_shader.sh}):
	 *      - {@code u_viewRect vec4(x, y, width, height)} - view rectangle for current
	 *        view, in pixels.
	 *      - {@code u_viewTexel vec4(1.0/width, 1.0/height, undef, undef)} - inverse
	 *        width and height
	 *      - {@code u_view mat4} - view matrix
	 *      - {@code u_invView mat4} - inverted view matrix
	 *      - {@code u_proj mat4} - projection matrix
	 *      - {@code u_invProj mat4} - inverted projection matrix
	 *      - {@code u_viewProj mat4} - concatenated view projection matrix
	 *      - {@code u_invViewProj mat4} - concatenated inverted view projection matrix
	 *      - {@code u_model mat4[BGFX_CONFIG_MAX_BONES]} - array of model matrices.
	 *      - {@code u_modelView mat4} - concatenated model view matrix, only first
	 *        model matrix from array is used.
	 *      - {@code u_invModelView mat4} - inverted concatenated model view matrix.
	 *      - {@code u_modelViewProj mat4} - concatenated model view projection matrix.
	 *      - {@code u_alphaRef float} - alpha reference value for alpha test.
	 * @param _name Uniform name in shader.
	 * @param _type Type of uniform (See: {@code UniformType}).
	 * @param _num Number of elements in array.
	 * @return Handle to uniform object.
	 */
	public static UniformHandle createUniform(String _name, UniformType _type, @Unsigned short _num) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				return UniformHandle.read((MemorySegment) MH_CREATE_UNIFORM.invokeExact((SegmentAllocator) arena, cString(arena, _name), _type.ordinal(), _num));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Create shader uniform parameter.
	 * <p>
	 * <strong>Remarks:</strong> 
	 *   1. Uniform names are unique. It's valid to call {@code createUniform}
	 *      multiple times with the same uniform name. The library will always
	 *      return the same handle, but the handle reference count will be
	 *      incremented. This means that the same number of {@code destroyUniform}
	 *      must be called to properly destroy the uniform.
	 * <p>
	 *   2. Predefined uniforms (declared in {@code bgfx_shader.sh}):
	 *      - {@code u_viewRect vec4(x, y, width, height)} - view rectangle for current
	 *        view, in pixels.
	 *      - {@code u_viewTexel vec4(1.0/width, 1.0/height, undef, undef)} - inverse
	 *        width and height
	 *      - {@code u_view mat4} - view matrix
	 *      - {@code u_invView mat4} - inverted view matrix
	 *      - {@code u_proj mat4} - projection matrix
	 *      - {@code u_invProj mat4} - inverted projection matrix
	 *      - {@code u_viewProj mat4} - concatenated view projection matrix
	 *      - {@code u_invViewProj mat4} - concatenated inverted view projection matrix
	 *      - {@code u_model mat4[BGFX_CONFIG_MAX_BONES]} - array of model matrices.
	 *      - {@code u_modelView mat4} - concatenated model view matrix, only first
	 *        model matrix from array is used.
	 *      - {@code u_invModelView mat4} - inverted concatenated model view matrix.
	 *      - {@code u_modelViewProj mat4} - concatenated model view projection matrix.
	 *      - {@code u_alphaRef float} - alpha reference value for alpha test.
	 * @param _name Uniform name in shader.
	 * @param _freq Uniform change frequency (See: {@code UniformFreq}).
	 * @param _type Type of uniform (See: {@code UniformType}).
	 * @param _num Number of elements in array.
	 * @return Handle to uniform object.
	 */
	public static UniformHandle createUniformWithFreq(String _name, UniformFreq _freq, UniformType _type, @Unsigned short _num) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				return UniformHandle.read((MemorySegment) MH_CREATE_UNIFORM_WITH_FREQ.invokeExact((SegmentAllocator) arena, cString(arena, _name), _freq.ordinal(), _type.ordinal(), _num));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Retrieve uniform info.
	 * @param _handle Handle to uniform object.
	 * @param _info Uniform info.
	 */
	public static void getUniformInfo(UniformHandle _handle, UniformInfo _info) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_GET_UNIFORM_INFO.invokeExact(_handle.allocate(arena), address(_info));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Destroy shader uniform parameter.
	 * @param _handle Handle to uniform object.
	 */
	public static void destroyUniform(UniformHandle _handle) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_DESTROY_UNIFORM.invokeExact(_handle.allocate(arena));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Create occlusion query. Occlusion queries allow the GPU to determine
	 * if any pixels passed the depth test.
	 * @return Handle to occlusion query object.
	 */
	public static OcclusionQueryHandle createOcclusionQuery() {
		try {
			try (Arena arena = Arena.ofConfined()) {
				return OcclusionQueryHandle.read((MemorySegment) MH_CREATE_OCCLUSION_QUERY.invokeExact((SegmentAllocator) arena));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Retrieve occlusion query result from previous frame.
	 * @param _handle Handle to occlusion query object.
	 * @param _result Number of pixels that passed test. This argument can be {@code NULL} if result of occlusion query is not needed.
	 * @return Occlusion query result.
	 */
	public static OcclusionQueryResult getResult(OcclusionQueryHandle _handle, @Nullable MemorySegment _result) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				return OcclusionQueryResult.fromValue((int) MH_GET_RESULT.invokeExact(_handle.allocate(arena), address(_result)));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Destroy occlusion query.
	 * @param _handle Handle to occlusion query object.
	 */
	public static void destroyOcclusionQuery(OcclusionQueryHandle _handle) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_DESTROY_OCCLUSION_QUERY.invokeExact(_handle.allocate(arena));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set palette color value.
	 * @param _index Index into palette.
	 * @param _rgba RGBA floating point values.
	 */
	public static void setPaletteColor(@Unsigned byte _index, MemorySegment _rgba) {
		try {
			MH_SET_PALETTE_COLOR.invokeExact(_index, address(_rgba));
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set palette color value.
	 * @param _index Index into palette.
	 * @param _r Red value (RGBA floating point values)
	 * @param _g Green value (RGBA floating point values)
	 * @param _b Blue value (RGBA floating point values)
	 * @param _a Alpha value (RGBA floating point values)
	 */
	public static void setPaletteColorRgba32f(@Unsigned byte _index, float _r, float _g, float _b, float _a) {
		try {
			MH_SET_PALETTE_COLOR_RGBA32F.invokeExact(_index, _r, _g, _b, _a);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set palette color value.
	 * @param _index Index into palette.
	 * @param _rgba Packed 32-bit RGBA value.
	 */
	public static void setPaletteColorRgba8(@Unsigned byte _index, @Unsigned int _rgba) {
		try {
			MH_SET_PALETTE_COLOR_RGBA8.invokeExact(_index, _rgba);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set view name.
	 * <p>
	 * <strong>Remarks:</strong> 
	 *   This is debug only feature.
	 * <p>
	 *   In graphics debugger view name will appear as:
	 * <p>
	 *       "nnnc &lt;view name&gt;"
	 *        ^  ^ ^
	 *        |  +--- compute (C)
	 *        +------ view id
	 * @param _id View id.
	 * @param _name View name.
	 * @param _len View name length (if length is INT32_MAX, it's expected that _name is zero terminated string.
	 */
	public static void setViewName(short _id, String _name, int _len) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SET_VIEW_NAME.invokeExact(_id, cString(arena, _name), _len);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set view rectangle. Draw primitive outside view will be clipped.
	 * @param _id View id.
	 * @param _x Position x from the left corner of the window. Can be negative to place view origin outside of the window.
	 * @param _y Position y from the top corner of the window. Can be negative to place view origin outside of the window.
	 * @param _width Width of view port region.
	 * @param _height Height of view port region.
	 */
	public static void setViewRect(short _id, short _x, short _y, @Unsigned short _width, @Unsigned short _height) {
		try {
			MH_SET_VIEW_RECT.invokeExact(_id, _x, _y, _width, _height);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set view rectangle. Draw primitive outside view will be clipped.
	 * @param _id View id.
	 * @param _x Position x from the left corner of the window. Can be negative to place view origin outside of the window.
	 * @param _y Position y from the top corner of the window. Can be negative to place view origin outside of the window.
	 * @param _ratio Width and height will be set in respect to back-buffer size. See: {@code BackbufferRatio}.
	 */
	public static void setViewRectRatio(short _id, short _x, short _y, BackbufferRatio _ratio) {
		try {
			MH_SET_VIEW_RECT_RATIO.invokeExact(_id, _x, _y, _ratio.ordinal());
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set view scissor. Draw primitive outside view will be clipped. When
	 * _x, _y, _width and _height are set to 0, scissor will be disabled.
	 * @param _id View id.
	 * @param _x Position x from the left corner of the window.
	 * @param _y Position y from the top corner of the window.
	 * @param _width Width of view scissor region.
	 * @param _height Height of view scissor region.
	 */
	public static void setViewScissor(short _id, @Unsigned short _x, @Unsigned short _y, @Unsigned short _width, @Unsigned short _height) {
		try {
			MH_SET_VIEW_SCISSOR.invokeExact(_id, _x, _y, _width, _height);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set view clear flags.
	 * @param _id View id.
	 * @param _flags Clear flags. Use {@code BGFX_CLEAR_NONE} to remove any clear operation. See: {@code BGFX_CLEAR_*}.
	 * @param _rgba Color clear value.
	 * @param _depth Depth clear value.
	 * @param _stencil Stencil clear value.
	 */
	public static void setViewClear(short _id, @Unsigned short _flags, @Unsigned int _rgba, float _depth, @Unsigned byte _stencil) {
		try {
			MH_SET_VIEW_CLEAR.invokeExact(_id, _flags, _rgba, _depth, _stencil);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set view clear flags with different clear color for each
	 * frame buffer texture. {@code setPaletteColor} must be used to set up a
	 * clear color palette.
	 * @param _id View id.
	 * @param _flags Clear flags. Use {@code BGFX_CLEAR_NONE} to remove any clear operation. See: {@code BGFX_CLEAR_*}.
	 * @param _depth Depth clear value.
	 * @param _stencil Stencil clear value.
	 * @param _c0 Palette index for frame buffer attachment 0.
	 * @param _c1 Palette index for frame buffer attachment 1.
	 * @param _c2 Palette index for frame buffer attachment 2.
	 * @param _c3 Palette index for frame buffer attachment 3.
	 * @param _c4 Palette index for frame buffer attachment 4.
	 * @param _c5 Palette index for frame buffer attachment 5.
	 * @param _c6 Palette index for frame buffer attachment 6.
	 * @param _c7 Palette index for frame buffer attachment 7.
	 */
	public static void setViewClearMrt(short _id, @Unsigned short _flags, float _depth, @Unsigned byte _stencil, @Unsigned byte _c0, @Unsigned byte _c1, @Unsigned byte _c2, @Unsigned byte _c3, @Unsigned byte _c4, @Unsigned byte _c5, @Unsigned byte _c6, @Unsigned byte _c7) {
		try {
			MH_SET_VIEW_CLEAR_MRT.invokeExact(_id, _flags, _depth, _stencil, _c0, _c1, _c2, _c3, _c4, _c5, _c6, _c7);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set view sorting mode.
	 * <p>
	 * <strong>Remarks:</strong> 
	 *   View mode must be set prior calling {@code submit} for the view.
	 * @param _id View id.
	 * @param _mode View sort mode. See {@code ViewMode}.
	 */
	public static void setViewMode(short _id, ViewMode _mode) {
		try {
			MH_SET_VIEW_MODE.invokeExact(_id, _mode.ordinal());
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set view frame buffer.
	 * <p>
	 * <strong>Remarks:</strong> 
	 *   Not persistent after {@code reset} call.
	 * @param _id View id.
	 * @param _handle Frame buffer handle. Passing {@code BGFX_INVALID_HANDLE} as frame buffer handle will draw primitives from this view into default back buffer.
	 */
	public static void setViewFrameBuffer(short _id, FrameBufferHandle _handle) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SET_VIEW_FRAME_BUFFER.invokeExact(_id, _handle.allocate(arena));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set view's view matrix and projection matrix,
	 * all draw primitives in this view will use these two matrices.
	 * @param _id View id.
	 * @param _view View matrix.
	 * @param _proj Projection matrix.
	 */
	public static void setViewTransform(short _id, MemorySegment _view, MemorySegment _proj) {
		try {
			MH_SET_VIEW_TRANSFORM.invokeExact(_id, address(_view), address(_proj));
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Post submit view reordering.
	 * @param _id First view id.
	 * @param _num Number of views to remap.
	 * @param _order View remap id table. Passing {@code NULL} will reset view ids to default state.
	 */
	public static void setViewOrder(short _id, @Unsigned short _num, @Nullable MemorySegment _order) {
		try {
			MH_SET_VIEW_ORDER.invokeExact(_id, _num, address(_order));
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set view shading rate.
	 * <p>
	 * <strong>Attention:</strong> Availability depends on: {@code BGFX_CAPS_VARIABLE_RATE_SHADING}.
	 * @param _id View id.
	 * @param _shadingRate Shading rate.
	 */
	public static void setViewShadingRate(short _id, ShadingRate _shadingRate) {
		try {
			MH_SET_VIEW_SHADING_RATE.invokeExact(_id, _shadingRate.ordinal());
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Reset all view settings to default.
	 * @param _id _id View id.
	 */
	public static void resetView(short _id) {
		try {
			MH_RESET_VIEW.invokeExact(_id);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Begin submitting draw calls from thread. Obtains an encoder that can be
	 * used to submit draw calls, compute dispatches, and state changes.
	 * <p>
	 * In multithreaded mode ({@code BGFX_CONFIG_MULTITHREADED=1}), multiple threads
	 * can each obtain their own encoder and submit draw calls in parallel.
	 * Each encoder writes into its own uniform buffer, so there is no
	 * contention between threads. The maximum number of simultaneous encoders
	 * is configured via {@code Limits.maxEncoders} in {@code Init} (default: 8).
	 * <p>
	 * When called from the API thread (the thread that called {@code init})
	 * with {@code _forceNewEncoder} set to {@code false}, the default internal encoder
	 * (encoder 0) is returned. This is the same encoder used by the legacy
	 * non-encoder API ({@code setState}, {@code submit}, etc.). When called
	 * from a worker thread (or with {@code _forceNewEncoder} set to {@code true}), a new
	 * encoder is allocated from the encoder pool.
	 * <p>
	 * <strong>Remarks:</strong> 
	 *   The returned {@code Encoder} pointer is valid until {@code end} is called
	 *   with it. All encoders must be ended before {@code frame} is called.
	 *   If {@code frame} is called while encoders are still active, it will
	 *   wait for them to finish. Returns {@code NULL} if no encoder slots are
	 *   available (all {@code maxEncoders} slots are in use).
	 *   See also: {@code end}, {@code frame}.
	 * @param _forceNewEncoder Force allocation of a new encoder from the pool, even when called from the API thread.
	 * @return Encoder.
	 */
	public static Encoder encoderBegin(boolean _forceNewEncoder) {
		try {
			return new Encoder((MemorySegment) MH_ENCODER_BEGIN.invokeExact(_forceNewEncoder));
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * End submitting draw calls from thread. Returns the encoder obtained from
	 * {@code begin} back to the encoder pool.
	 * <p>
	 * After this call the {@code Encoder} pointer is no longer valid and must not
	 * be used. The encoder's recorded draw calls and state changes are finalized
	 * and will be included in the next frame when {@code frame} is called.
	 * <p>
	 * <strong>Remarks:</strong> 
	 *   Must be called from the same thread that called {@code begin} for
	 *   this encoder. All encoders must be ended before {@code frame} is
	 *   called. The default encoder (encoder 0, used by the legacy API) is
	 *   managed internally and does not need to be passed to {@code end};
	 *   passing it is harmless but has no effect.
	 *   See also: {@code begin}, {@code frame}.
	 * @param _encoder Encoder.
	 */
	public static void encoderEnd(Encoder _encoder) {
		try {
			MH_ENCODER_END.invokeExact(address(_encoder));
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set shader uniform parameter for view.
	 * <p>
	 * <strong>Attention:</strong> Uniform must be created with {@code UniformFreq.VIEW} argument.
	 * @param _id View id.
	 * @param _handle Uniform.
	 * @param _value Pointer to uniform data.
	 * @param _num Number of elements. Passing {@code UINT16_MAX} will use the _num passed on uniform creation.
	 */
	public static void setViewUniform(short _id, UniformHandle _handle, MemorySegment _value, @Unsigned short _num) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SET_VIEW_UNIFORM.invokeExact(_id, _handle.allocate(arena), address(_value), _num);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set shader uniform parameter for frame.
	 * <p>
	 * <strong>Attention:</strong> Uniform must be created with {@code UniformFreq.VIEW} argument.
	 * @param _handle Uniform.
	 * @param _value Pointer to uniform data.
	 * @param _num Number of elements. Passing {@code UINT16_MAX} will use the _num passed on uniform creation.
	 */
	public static void setFrameUniform(UniformHandle _handle, MemorySegment _value, @Unsigned short _num) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SET_FRAME_UNIFORM.invokeExact(_handle.allocate(arena), address(_value), _num);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Request screen shot of window back buffer.
	 * <p>
	 * <strong>Remarks:</strong> 
	 *   {@code CallbackI.screenShot} must be implemented.
	 * <strong>Attention:</strong> Frame buffer handle must be created with OS' target native window handle.
	 * @param _handle Frame buffer handle. If handle is {@code BGFX_INVALID_HANDLE} request will be made for main window back buffer.
	 * @param _filePath Will be passed to {@code CallbackI.screenShot} callback.
	 */
	public static void requestScreenShot(FrameBufferHandle _handle, String _filePath) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_REQUEST_SCREEN_SHOT.invokeExact(_handle.allocate(arena), cString(arena, _filePath));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Render frame. Executes the actual GPU rendering work for one frame.
	 * <p>
	 * In the default **multithreaded** configuration, {@code renderFrame} runs
	 * on the **render thread** while {@code frame} runs on the **API thread**.
	 * Their interaction is as follows:
	 * <p>
	 *   1. The render thread calls {@code renderFrame}, which blocks waiting
	 *      for the API thread to signal that a new frame is ready.
	 *   2. On the API thread, {@code frame} finishes building the frame,
	 *      swaps internal submit/render buffers, and signals the render thread.
	 *   3. {@code renderFrame} wakes up, executes pre-render commands,
	 *      submits GPU draw calls, executes post-render commands, flips the
	 *      back buffer, then signals back to the API thread that rendering
	 *      is complete.
	 *   4. The API thread's next {@code frame} call waits for this completion
	 *      signal before swapping buffers again.
	 * <p>
	 * This double-buffered semaphore handshake allows the API thread and
	 * render thread to run in parallel, overlapping CPU frame building with
	 * GPU rendering.
	 * <p>
	 * <strong>Attention:</strong> {@code renderFrame} is a blocking call. It waits for
	 *   {@code frame} to be called from the API thread to process the frame.
	 *   If a timeout value is passed, the call will return
	 *   {@code RenderFrame.TIMEOUT} even if {@code frame} has not been called.
	 *   A value of -1 (default) means wait indefinitely (up to
	 *   {@code BGFX_CONFIG_API_SEMAPHORE_TIMEOUT}).
	 * <p>
	 * <strong>Warning:</strong> This call should only be used on platforms that don't allow
	 *   creating a separate rendering thread. If it is called before
	 *   {@code init}, the internal render thread won't be created by the
	 *   {@code init} call, and the user is responsible for calling
	 *   {@code renderFrame} on the render thread each frame. If both
	 *   {@code renderFrame} and {@code init} are called from the same
	 *   thread, bgfx operates in single-threaded mode and {@code frame}
	 *   will internally invoke {@code renderFrame} automatically.
	 *   See also: {@code frame}.
	 * @param _msecs Timeout in milliseconds.
	 * @return Current renderer context state. See: {@code RenderFrame}.
	 */
	public static RenderFrame renderFrame(int _msecs) {
		try {
			return RenderFrame.fromValue((int) MH_RENDER_FRAME.invokeExact(_msecs));
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Get internal data for interop.
	 * <p>
	 * <strong>Attention:</strong> It's expected you understand some bgfx internals before you
	 *   use this call.
	 * <p>
	 * <strong>Warning:</strong> Must be called only on render thread.
	 * @return Internal data.
	 */
	public static InternalData getInternalData() {
		try {
			return new InternalData((MemorySegment) MH_GET_INTERNAL_DATA.invokeExact());
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Sets a debug marker. This allows you to group graphics calls together for easy browsing in
	 * graphics debugging tools.
	 * @param _name Marker name.
	 * @param _len Marker name length (if length is INT32_MAX, it's expected that _name is zero terminated string.
	 */
	public static void setMarker(String _name, int _len) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SET_MARKER.invokeExact(cString(arena, _name), _len);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set render states for draw primitive.
	 * <p>
	 * <strong>Remarks:</strong> 
	 *   1. To set up more complex states use:
	 *      {@code BGFX_STATE_ALPHA_REF(_ref)},
	 *      {@code BGFX_STATE_POINT_SIZE(_size)},
	 *      {@code BGFX_STATE_BLEND_FUNC(_src, _dst)},
	 *      {@code BGFX_STATE_BLEND_FUNC_SEPARATE(_srcRGB, _dstRGB, _srcA, _dstA)},
	 *      {@code BGFX_STATE_BLEND_EQUATION(_equation)},
	 *      {@code BGFX_STATE_BLEND_EQUATION_SEPARATE(_equationRGB, _equationA)}
	 *   2. {@code BGFX_STATE_BLEND_EQUATION_ADD} is set when no other blend
	 *      equation is specified.
	 * @param _state State flags. Default state for primitive type is   triangles. See: {@code BGFX_STATE_DEFAULT}.   - {@code BGFX_STATE_DEPTH_TEST_*} - Depth test function.   - {@code BGFX_STATE_BLEND_*} - See remark 1 about BGFX_STATE_BLEND_FUNC.   - {@code BGFX_STATE_BLEND_EQUATION_*} - See remark 2.   - {@code BGFX_STATE_CULL_*} - Backface culling mode.   - {@code BGFX_STATE_WRITE_*} - Enable R, G, B, A or Z write.   - {@code BGFX_STATE_MSAA} - Enable hardware multisample antialiasing.   - {@code BGFX_STATE_PT_[TRISTRIP/LINES/POINTS]} - Primitive type.
	 * @param _rgba Sets blend factor used by {@code BGFX_STATE_BLEND_FACTOR} and   {@code BGFX_STATE_BLEND_INV_FACTOR} blend modes.
	 */
	public static void setState(@Unsigned long _state, @Unsigned int _rgba) {
		try {
			MH_SET_STATE.invokeExact(_state, _rgba);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set condition for rendering.
	 * @param _handle Occlusion query handle.
	 * @param _visible Render if occlusion query is visible.
	 */
	public static void setCondition(OcclusionQueryHandle _handle, boolean _visible) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SET_CONDITION.invokeExact(_handle.allocate(arena), _visible);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set stencil test state.
	 * @param _fstencil Front stencil state.
	 * @param _bstencil Back stencil state. If back is set to {@code BGFX_STENCIL_NONE} _fstencil is applied to both front and back facing primitives.
	 */
	public static void setStencil(@Unsigned int _fstencil, @Unsigned int _bstencil) {
		try {
			MH_SET_STENCIL.invokeExact(_fstencil, _bstencil);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set scissor for draw primitive.
	 * <p>
	 * <strong>Remarks:</strong> 
	 *   To scissor for all primitives in view see {@code setViewScissor}.
	 * @param _x Position x from the left corner of the window.
	 * @param _y Position y from the top corner of the window.
	 * @param _width Width of view scissor region.
	 * @param _height Height of view scissor region.
	 * @return Scissor cache index.
	 */
	public static @Unsigned short setScissor(@Unsigned short _x, @Unsigned short _y, @Unsigned short _width, @Unsigned short _height) {
		try {
			return (@Unsigned short) MH_SET_SCISSOR.invokeExact(_x, _y, _width, _height);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set scissor from cache for draw primitive.
	 * <p>
	 * <strong>Remarks:</strong> 
	 *   To scissor for all primitives in view see {@code setViewScissor}.
	 * @param _cache Index in scissor cache.
	 */
	public static void setScissorCached(@Unsigned short _cache) {
		try {
			MH_SET_SCISSOR_CACHED.invokeExact(_cache);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set model matrix for draw primitive. If it is not called,
	 * the model will be rendered with an identity model matrix.
	 * @param _mtx Pointer to first matrix in array.
	 * @param _num Number of matrices in array.
	 * @return Index into matrix cache in case the same model matrix has to be used for other draw primitive call.
	 */
	public static @Unsigned int setTransform(MemorySegment _mtx, @Unsigned short _num) {
		try {
			return (@Unsigned int) MH_SET_TRANSFORM.invokeExact(address(_mtx), _num);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 *  Set model matrix from matrix cache for draw primitive.
	 * @param _cache Index in matrix cache.
	 * @param _num Number of matrices from cache.
	 */
	public static void setTransformCached(@Unsigned int _cache, @Unsigned short _num) {
		try {
			MH_SET_TRANSFORM_CACHED.invokeExact(_cache, _num);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Reserve matrices in internal matrix cache.
	 * <p>
	 * <strong>Attention:</strong> Pointer returned can be modified until {@code frame} is called.
	 * @param _transform Pointer to {@code Transform} structure.
	 * @param _num Number of matrices.
	 * @return Index in matrix cache.
	 */
	public static @Unsigned int allocTransform(Transform _transform, @Unsigned short _num) {
		try {
			return (@Unsigned int) MH_ALLOC_TRANSFORM.invokeExact(address(_transform), _num);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set shader uniform parameter for draw primitive.
	 * @param _handle Uniform.
	 * @param _value Pointer to uniform data.
	 * @param _num Number of elements. Passing {@code UINT16_MAX} will use the _num passed on uniform creation.
	 */
	public static void setUniform(UniformHandle _handle, MemorySegment _value, @Unsigned short _num) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SET_UNIFORM.invokeExact(_handle.allocate(arena), address(_value), _num);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set index buffer for draw primitive.
	 * @param _handle Index buffer.
	 * @param _firstIndex First index to render.
	 * @param _numIndices Number of indices to render.
	 */
	public static void setIndexBuffer(IndexBufferHandle _handle, @Unsigned int _firstIndex, @Unsigned int _numIndices) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SET_INDEX_BUFFER.invokeExact(_handle.allocate(arena), _firstIndex, _numIndices);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set index buffer for draw primitive.
	 * @param _handle Dynamic index buffer.
	 * @param _firstIndex First index to render.
	 * @param _numIndices Number of indices to render.
	 */
	public static void setDynamicIndexBuffer(DynamicIndexBufferHandle _handle, @Unsigned int _firstIndex, @Unsigned int _numIndices) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SET_DYNAMIC_INDEX_BUFFER.invokeExact(_handle.allocate(arena), _firstIndex, _numIndices);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set index buffer for draw primitive.
	 * @param _tib Transient index buffer.
	 * @param _firstIndex First index to render.
	 * @param _numIndices Number of indices to render.
	 */
	public static void setTransientIndexBuffer(TransientIndexBuffer _tib, @Unsigned int _firstIndex, @Unsigned int _numIndices) {
		try {
			MH_SET_TRANSIENT_INDEX_BUFFER.invokeExact(address(_tib), _firstIndex, _numIndices);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set vertex buffer for draw primitive.
	 * @param _stream Vertex stream.
	 * @param _handle Vertex buffer.
	 * @param _startVertex First vertex to render.
	 * @param _numVertices Number of vertices to render.
	 */
	public static void setVertexBuffer(@Unsigned byte _stream, VertexBufferHandle _handle, @Unsigned int _startVertex, @Unsigned int _numVertices) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SET_VERTEX_BUFFER.invokeExact(_stream, _handle.allocate(arena), _startVertex, _numVertices);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set vertex buffer for draw primitive.
	 * @param _stream Vertex stream.
	 * @param _handle Vertex buffer.
	 * @param _startVertex First vertex to render.
	 * @param _numVertices Number of vertices to render.
	 * @param _layoutHandle Vertex layout for aliasing vertex buffer. If invalid handle is used, vertex layout used for creation of vertex buffer will be used.
	 */
	public static void setVertexBufferWithLayout(@Unsigned byte _stream, VertexBufferHandle _handle, @Unsigned int _startVertex, @Unsigned int _numVertices, VertexLayoutHandle _layoutHandle) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SET_VERTEX_BUFFER_WITH_LAYOUT.invokeExact(_stream, _handle.allocate(arena), _startVertex, _numVertices, _layoutHandle.allocate(arena));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set vertex buffer for draw primitive.
	 * @param _stream Vertex stream.
	 * @param _handle Dynamic vertex buffer.
	 * @param _startVertex First vertex to render.
	 * @param _numVertices Number of vertices to render.
	 */
	public static void setDynamicVertexBuffer(@Unsigned byte _stream, DynamicVertexBufferHandle _handle, @Unsigned int _startVertex, @Unsigned int _numVertices) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SET_DYNAMIC_VERTEX_BUFFER.invokeExact(_stream, _handle.allocate(arena), _startVertex, _numVertices);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set vertex buffer for draw primitive.
	 * @param _stream Vertex stream.
	 * @param _handle Dynamic vertex buffer.
	 * @param _startVertex First vertex to render.
	 * @param _numVertices Number of vertices to render.
	 * @param _layoutHandle Vertex layout for aliasing vertex buffer. If invalid handle is used, vertex layout used for creation of vertex buffer will be used.
	 */
	public static void setDynamicVertexBufferWithLayout(@Unsigned byte _stream, DynamicVertexBufferHandle _handle, @Unsigned int _startVertex, @Unsigned int _numVertices, VertexLayoutHandle _layoutHandle) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SET_DYNAMIC_VERTEX_BUFFER_WITH_LAYOUT.invokeExact(_stream, _handle.allocate(arena), _startVertex, _numVertices, _layoutHandle.allocate(arena));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set vertex buffer for draw primitive.
	 * @param _stream Vertex stream.
	 * @param _tvb Transient vertex buffer.
	 * @param _startVertex First vertex to render.
	 * @param _numVertices Number of vertices to render.
	 */
	public static void setTransientVertexBuffer(@Unsigned byte _stream, TransientVertexBuffer _tvb, @Unsigned int _startVertex, @Unsigned int _numVertices) {
		try {
			MH_SET_TRANSIENT_VERTEX_BUFFER.invokeExact(_stream, address(_tvb), _startVertex, _numVertices);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set vertex buffer for draw primitive.
	 * @param _stream Vertex stream.
	 * @param _tvb Transient vertex buffer.
	 * @param _startVertex First vertex to render.
	 * @param _numVertices Number of vertices to render.
	 * @param _layoutHandle Vertex layout for aliasing vertex buffer. If invalid handle is used, vertex layout used for creation of vertex buffer will be used.
	 */
	public static void setTransientVertexBufferWithLayout(@Unsigned byte _stream, TransientVertexBuffer _tvb, @Unsigned int _startVertex, @Unsigned int _numVertices, VertexLayoutHandle _layoutHandle) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SET_TRANSIENT_VERTEX_BUFFER_WITH_LAYOUT.invokeExact(_stream, address(_tvb), _startVertex, _numVertices, _layoutHandle.allocate(arena));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set number of vertices for auto generated vertices use in conjunction
	 * with gl_VertexID.
	 * @param _numVertices Number of vertices.
	 */
	public static void setVertexCount(@Unsigned int _numVertices) {
		try {
			MH_SET_VERTEX_COUNT.invokeExact(_numVertices);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set instance data buffer for draw primitive.
	 * @param _idb Transient instance data buffer.
	 * @param _start First instance data.
	 * @param _num Number of data instances.
	 */
	public static void setInstanceDataBuffer(InstanceDataBuffer _idb, @Unsigned int _start, @Unsigned int _num) {
		try {
			MH_SET_INSTANCE_DATA_BUFFER.invokeExact(address(_idb), _start, _num);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set instance data buffer for draw primitive.
	 * @param _handle Vertex buffer.
	 * @param _startVertex First instance data.
	 * @param _num Number of data instances.
	 */
	public static void setInstanceDataFromVertexBuffer(VertexBufferHandle _handle, @Unsigned int _startVertex, @Unsigned int _num) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SET_INSTANCE_DATA_FROM_VERTEX_BUFFER.invokeExact(_handle.allocate(arena), _startVertex, _num);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set instance data buffer for draw primitive.
	 * @param _handle Dynamic vertex buffer.
	 * @param _startVertex First instance data.
	 * @param _num Number of data instances.
	 */
	public static void setInstanceDataFromDynamicVertexBuffer(DynamicVertexBufferHandle _handle, @Unsigned int _startVertex, @Unsigned int _num) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SET_INSTANCE_DATA_FROM_DYNAMIC_VERTEX_BUFFER.invokeExact(_handle.allocate(arena), _startVertex, _num);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set number of instances for auto generated instances use in conjunction
	 * with gl_InstanceID.
	 * @param _numInstances Number of instances.
	 */
	public static void setInstanceCount(@Unsigned int _numInstances) {
		try {
			MH_SET_INSTANCE_COUNT.invokeExact(_numInstances);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set texture stage for draw primitive.
	 * @param _stage Texture unit.
	 * @param _sampler Program sampler.
	 * @param _handle Texture handle.
	 * @param _flags Texture sampling mode. Default value UINT32_MAX uses   texture sampling settings from the texture.   - {@code BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]} - Mirror or clamp to edge wrap     mode.   - {@code BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]} - Point or anisotropic     sampling.
	 */
	public static void setTexture(@Unsigned byte _stage, UniformHandle _sampler, TextureHandle _handle, @Unsigned int _flags) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SET_TEXTURE.invokeExact(_stage, _sampler.allocate(arena), _handle.allocate(arena), _flags);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set texture stage for draw primitive, selecting a sub-range of the
	 * texture's array layers and mip levels.
	 * @param _stage Texture unit.
	 * @param _sampler Program sampler.
	 * @param _handle Texture handle.
	 * @param _firstLayer First array layer.
	 * @param _numLayers Number of array layers.
	 * @param _firstMip First (most detailed) mip level.
	 * @param _numMips Number of mip levels.
	 * @param _flags Texture sampling mode. Default value UINT32_MAX uses   texture sampling settings from the texture.   - {@code BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]} - Mirror or clamp to edge wrap     mode.   - {@code BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]} - Point or anisotropic     sampling.
	 */
	public static void setTextureView(@Unsigned byte _stage, UniformHandle _sampler, TextureHandle _handle, @Unsigned short _firstLayer, @Unsigned short _numLayers, @Unsigned byte _firstMip, @Unsigned byte _numMips, @Unsigned int _flags) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SET_TEXTURE_VIEW.invokeExact(_stage, _sampler.allocate(arena), _handle.allocate(arena), _firstLayer, _numLayers, _firstMip, _numMips, _flags);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Submit an empty primitive for rendering. Uniforms and draw state
	 * will be applied but no geometry will be submitted.
	 * <p>
	 * <strong>Remarks:</strong> 
	 *   These empty draw calls will sort before ordinary draw calls.
	 * @param _id View id.
	 */
	public static void touch(short _id) {
		try {
			MH_TOUCH.invokeExact(_id);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Submit primitive for rendering.
	 * @param _id View id.
	 * @param _program Program.
	 * @param _depth Depth for sorting.
	 * @param _flags Which states to discard for next draw. See {@code BGFX_DISCARD_*}.
	 */
	public static void submit(short _id, ProgramHandle _program, @Unsigned int _depth, @Unsigned byte _flags) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SUBMIT.invokeExact(_id, _program.allocate(arena), _depth, _flags);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Submit primitive with occlusion query for rendering.
	 * @param _id View id.
	 * @param _program Program.
	 * @param _occlusionQuery Occlusion query.
	 * @param _depth Depth for sorting.
	 * @param _flags Which states to discard for next draw. See {@code BGFX_DISCARD_*}.
	 */
	public static void submitOcclusionQuery(short _id, ProgramHandle _program, OcclusionQueryHandle _occlusionQuery, @Unsigned int _depth, @Unsigned byte _flags) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SUBMIT_OCCLUSION_QUERY.invokeExact(_id, _program.allocate(arena), _occlusionQuery.allocate(arena), _depth, _flags);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Submit primitive for rendering with index and instance data info from
	 * indirect buffer.
	 * <p>
	 * <strong>Attention:</strong> Availability depends on: {@code BGFX_CAPS_DRAW_INDIRECT}.
	 * @param _id View id.
	 * @param _program Program.
	 * @param _indirectHandle Indirect buffer.
	 * @param _start First element in indirect buffer.
	 * @param _num Number of draws.
	 * @param _depth Depth for sorting.
	 * @param _flags Which states to discard for next draw. See {@code BGFX_DISCARD_*}.
	 */
	public static void submitIndirect(short _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, @Unsigned int _start, @Unsigned int _num, @Unsigned int _depth, @Unsigned byte _flags) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SUBMIT_INDIRECT.invokeExact(_id, _program.allocate(arena), _indirectHandle.allocate(arena), _start, _num, _depth, _flags);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Submit primitive for rendering with index and instance data info and
	 * draw count from indirect buffers.
	 * <p>
	 * <strong>Attention:</strong> Availability depends on: {@code BGFX_CAPS_DRAW_INDIRECT_COUNT}.
	 * @param _id View id.
	 * @param _program Program.
	 * @param _indirectHandle Indirect buffer.
	 * @param _start First element in indirect buffer.
	 * @param _numHandle Buffer for number of draws. Must be   created with {@code BGFX_BUFFER_INDEX32} and {@code BGFX_BUFFER_DRAW_INDIRECT}.
	 * @param _numIndex Element in number buffer.
	 * @param _numMax Max number of draws.
	 * @param _depth Depth for sorting.
	 * @param _flags Which states to discard for next draw. See {@code BGFX_DISCARD_*}.
	 */
	public static void submitIndirectCount(short _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, @Unsigned int _start, IndexBufferHandle _numHandle, @Unsigned int _numIndex, @Unsigned int _numMax, @Unsigned int _depth, @Unsigned byte _flags) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SUBMIT_INDIRECT_COUNT.invokeExact(_id, _program.allocate(arena), _indirectHandle.allocate(arena), _start, _numHandle.allocate(arena), _numIndex, _numMax, _depth, _flags);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set compute index buffer.
	 * @param _stage Compute stage.
	 * @param _handle Index buffer handle.
	 * @param _access Buffer access. See {@code Access}.
	 */
	public static void setComputeIndexBuffer(@Unsigned byte _stage, IndexBufferHandle _handle, Access _access) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SET_COMPUTE_INDEX_BUFFER.invokeExact(_stage, _handle.allocate(arena), _access.ordinal());
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set compute vertex buffer.
	 * @param _stage Compute stage.
	 * @param _handle Vertex buffer handle.
	 * @param _access Buffer access. See {@code Access}.
	 */
	public static void setComputeVertexBuffer(@Unsigned byte _stage, VertexBufferHandle _handle, Access _access) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SET_COMPUTE_VERTEX_BUFFER.invokeExact(_stage, _handle.allocate(arena), _access.ordinal());
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set compute dynamic index buffer.
	 * @param _stage Compute stage.
	 * @param _handle Dynamic index buffer handle.
	 * @param _access Buffer access. See {@code Access}.
	 */
	public static void setComputeDynamicIndexBuffer(@Unsigned byte _stage, DynamicIndexBufferHandle _handle, Access _access) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SET_COMPUTE_DYNAMIC_INDEX_BUFFER.invokeExact(_stage, _handle.allocate(arena), _access.ordinal());
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set compute dynamic vertex buffer.
	 * @param _stage Compute stage.
	 * @param _handle Dynamic vertex buffer handle.
	 * @param _access Buffer access. See {@code Access}.
	 */
	public static void setComputeDynamicVertexBuffer(@Unsigned byte _stage, DynamicVertexBufferHandle _handle, Access _access) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SET_COMPUTE_DYNAMIC_VERTEX_BUFFER.invokeExact(_stage, _handle.allocate(arena), _access.ordinal());
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set compute indirect buffer.
	 * @param _stage Compute stage.
	 * @param _handle Indirect buffer handle.
	 * @param _access Buffer access. See {@code Access}.
	 */
	public static void setComputeIndirectBuffer(@Unsigned byte _stage, IndirectBufferHandle _handle, Access _access) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SET_COMPUTE_INDIRECT_BUFFER.invokeExact(_stage, _handle.allocate(arena), _access.ordinal());
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set compute image from texture.
	 * @param _stage Compute stage.
	 * @param _handle Texture handle.
	 * @param _mip Mip level.
	 * @param _access Image access. See {@code Access}.
	 * @param _format Texture format. See: {@code TextureFormat}.
	 */
	public static void setImage(@Unsigned byte _stage, TextureHandle _handle, @Unsigned byte _mip, Access _access, TextureFormat _format) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SET_IMAGE.invokeExact(_stage, _handle.allocate(arena), _mip, _access.ordinal(), _format.ordinal());
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set compute image stage for draw primitive, selecting a sub-range of the
	 * texture's array layers and mip levels.
	 * @param _stage Compute stage.
	 * @param _handle Texture handle.
	 * @param _firstLayer First array layer.
	 * @param _numLayers Number of array layers.
	 * @param _mip Mip level.
	 * @param _access Image access. See {@code Access}.
	 * @param _format Texture format. See: {@code TextureFormat}.
	 */
	public static void setImageView(@Unsigned byte _stage, TextureHandle _handle, @Unsigned short _firstLayer, @Unsigned short _numLayers, @Unsigned byte _mip, Access _access, TextureFormat _format) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_SET_IMAGE_VIEW.invokeExact(_stage, _handle.allocate(arena), _firstLayer, _numLayers, _mip, _access.ordinal(), _format.ordinal());
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Dispatch compute.
	 * @param _id View id.
	 * @param _program Compute program.
	 * @param _numX Number of groups X.
	 * @param _numY Number of groups Y.
	 * @param _numZ Number of groups Z.
	 * @param _flags Discard or preserve states. See {@code BGFX_DISCARD_*}.
	 */
	public static void dispatch(short _id, ProgramHandle _program, @Unsigned int _numX, @Unsigned int _numY, @Unsigned int _numZ, @Unsigned byte _flags) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_DISPATCH.invokeExact(_id, _program.allocate(arena), _numX, _numY, _numZ, _flags);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Dispatch compute indirect.
	 * @param _id View id.
	 * @param _program Compute program.
	 * @param _indirectHandle Indirect buffer.
	 * @param _start First element in indirect buffer.
	 * @param _num Number of dispatches.
	 * @param _flags Discard or preserve states. See {@code BGFX_DISCARD_*}.
	 */
	public static void dispatchIndirect(short _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, @Unsigned int _start, @Unsigned int _num, @Unsigned byte _flags) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_DISPATCH_INDIRECT.invokeExact(_id, _program.allocate(arena), _indirectHandle.allocate(arena), _start, _num, _flags);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Discard previously set state for draw or compute call.
	 * @param _flags Draw/compute states to discard.
	 */
	public static void discard(@Unsigned byte _flags) {
		try {
			MH_DISCARD.invokeExact(_flags);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Blit texture region between two textures.
	 * <p>
	 * <strong>Remarks:</strong> 
	 *   The copy covers the region the two sides have in common: each side gives
	 *   the origin it starts at, and the size is the smaller of the two extents.
	 *   A zero {@code width}, {@code height} or {@code depth} extends to the rest of that mip.
	 * <p>
	 *   Blit is performed on GPU, and it is ordered within the view. In views, all
	 *   draw commands are executed after blit and compute commands.
	 * <p>
	 * <strong>Attention:</strong> Destination texture must be created with {@code BGFX_TEXTURE_BLIT_DST} flag.
	 * @param _id View id.
	 * @param _dst Destination texture region.
	 * @param _src Source texture region.
	 */
	public static void blit(short _id, TextureRegion _dst, TextureRegion _src) {
		try {
			MH_BLIT.invokeExact(_id, address(_dst), address(_src));
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Blit buffer region between two buffers.
	 * <p>
	 * <strong>Remarks:</strong> 
	 *   The source region gives the number of bytes copied, and the destination
	 *   region gives only the offset they land at. A zero {@code size} copies the rest of
	 *   the source buffer. {@code rowPitch} and {@code slicePitch} are unused.
	 * <p>
	 *   Buffer blit is performed on GPU, and it is ordered within the view, same as
	 *   texture blit. In views, all draw commands are executed after blit and compute
	 *   commands.
	 * <p>
	 * <strong>Attention:</strong> Source buffer must be created with one of {@code BGFX_BUFFER_COMPUTE_*}, or
	 *   {@code BGFX_BUFFER_DRAW_INDIRECT} flags.
	 * <strong>Attention:</strong> Destination buffer must be created with {@code BGFX_BUFFER_COMPUTE_WRITE}, or
	 *   {@code BGFX_BUFFER_DRAW_INDIRECT} flag.
	 * <strong>Attention:</strong> Source and destination buffer must be different.
	 * @param _id View id.
	 * @param _dst Destination buffer region.
	 * @param _src Source buffer region.
	 */
	public static void blitBuffer(short _id, BufferRegion _dst, BufferRegion _src) {
		try {
			MH_BLIT_BUFFER.invokeExact(_id, address(_dst), address(_src));
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Blit texture region into buffer.
	 * <p>
	 * <strong>Remarks:</strong> 
	 *   The texture region gives the size of the copy. {@code BufferRegion.rowPitch} and
	 *   {@code slicePitch} choose how the texels are laid out in the buffer, and 0 packs
	 *   them tightly. {@code BufferRegion.init} fills in the layout the backend copies
	 *   fastest, and bgfx repacks internally for any other layout.
	 * <p>
	 *   Blit is performed on GPU, and it is ordered within the view, same as texture
	 *   blit. In views, all draw commands are executed after blit and compute commands.
	 * <p>
	 * <strong>Attention:</strong> Destination buffer must be created with {@code BGFX_BUFFER_COMPUTE_WRITE}, or
	 *   {@code BGFX_BUFFER_DRAW_INDIRECT} flag.
	 * @param _id View id.
	 * @param _dst Destination buffer region.
	 * @param _src Source texture region.
	 */
	public static void blitToBuffer(short _id, BufferRegion _dst, TextureRegion _src) {
		try {
			MH_BLIT_TO_BUFFER.invokeExact(_id, address(_dst), address(_src));
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Blit buffer contents into texture region.
	 * <p>
	 * <strong>Remarks:</strong> 
	 *   The texture region gives the size of the copy. {@code BufferRegion.rowPitch} and
	 *   {@code slicePitch} describe how the texels are laid out in the buffer, and 0 reads
	 *   them tightly packed. {@code BufferRegion.init} fills in the layout the backend
	 *   copies fastest, and bgfx repacks internally for any other layout.
	 * <p>
	 *   Blit is performed on GPU, and it is ordered within the view, same as texture
	 *   blit. In views, all draw commands are executed after blit and compute commands.
	 * <p>
	 * <strong>Attention:</strong> Source buffer must be created with one of {@code BGFX_BUFFER_COMPUTE_*}, or
	 *   {@code BGFX_BUFFER_DRAW_INDIRECT} flags.
	 * <strong>Attention:</strong> Destination texture must be created with {@code BGFX_TEXTURE_BLIT_DST} flag.
	 * @param _id View id.
	 * @param _dst Destination texture region.
	 * @param _src Source buffer region.
	 */
	public static void blitFromBuffer(short _id, TextureRegion _dst, BufferRegion _src) {
		try {
			MH_BLIT_FROM_BUFFER.invokeExact(_id, address(_dst), address(_src));
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}


}
